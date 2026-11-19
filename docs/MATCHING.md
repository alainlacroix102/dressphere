# Matching notes (ee-gcc 2.9-ee-991111, `-O2 -G0`)

These are patterns that turned a near-match into an exact match. Add to this list as
you find more.

## Workflow

```bash
.venv/bin/python tools/m2c_draft.py func_XXXXXXXX     # first draft
.venv/bin/python tools/matchcheck.py src/tu.c         # per-function MATCH/DIFF
.venv/bin/python tools/matchcheck.py src/tu.c -d func_XXXXXXXX   # side-by-side
.venv/bin/python tools/variants.py src/tu.c func_XXXXXXXX variants.c  # try many bodies
.venv/bin/python tools/xref.py --rodata 0x47B100 0x47B300   # rodata users (TU order)
ninja                                                 # whole image must still match
```

Functions that won't match stay `INCLUDE_ASM`. Keep the best C draft under
`#ifdef NON_MATCHING`, since functionally correct C still helps the native port.

## Compiler behaviour

- **Loops:** `while`/`for` loops get loop-invariant hoisting, with constants moved into
  registers before the loop. If retail reloads constants on every iteration, the original
  used a `goto` loop.
- **Switch decision trees:** gcc builds a balanced compare tree over the case values. If
  retail compares `<0x40` then `>=0x30` as separate steps, there's a **GNU case range**
  (`case 0x30 ... 0x3F:`).
- **Separate case bodies:** if retail's dispatch tree splits cases that run identical code,
  write them as separate bodies. Cross-jumping merges them later, but the tree is built
  first.
- **Block order:** case bodies are laid out in source order. Reorder the `case`s to match
  retail's layout.
- **`ret = 1; if (cond) ret = 0; return ret;`** gives `movz` with the constant kept in a
  saved register. `return !cond` gives `xor`/`sltiu`.
- **Booleans and early returns:** `s32 ok = f() == K; ... if (!ok) return 0;` gives
  `xori`/`bnez`, and the early returns share one exit.
- **Globals read at the top:** if retail loads a global before a test that comes first in
  the source, it was read into a local at the start (`s32 flag = D_x & 0x40;`).
- **Unused return values:** when retail avoids `$v0` for a constant after a call, the call's
  return value is live. The function probably returns it.
- **Bit tests on 64-bit fields:** `ld; dsll N; dsra32 0; andi 1` is `(s32)(x >> (32-N)) & 1`
  on an `s64` field.
- **Byte-sized booleans:** `nor; andi 1` computed in place in a saved register comes from
  storing `~a & 1` into a `u8` local. An `s32` local gets a different register.
- **`movz` vs branch after a call:** `c = f() ? w >> 17 : K` with an `s32`/`u32` `c` gives
  `movz`. Retail's `bnez` (shift in the delay slot, then `li K`) needs a 16-bit `c`
  (`s16 col`). The narrowing stops if-conversion. A signed `s16` also gives the `sra` that
  later shifts need.
- **Rodata finds file boundaries:** `tools/xref.py --rodata` shows where one TU's rodata
  ends and the next one's starts (e.g. `D_0047B1B0` is used first by `func_0012BCB0`). That
  places the next TU's first function.
- **Asserts:** retail asserts call `func_0012A130(1, "#cond", "src/...c", line, msg, ra)`.
  The caller's `$ra` is stored through `$t7` (`register void **p asm("$15")` plus an
  inline `sw $31,0(%0)`). The strings give real file and function names. See the
  `SG_ASSERT` macro in `src/id/map_id.c`.
- **No `do { } while (0)` in macros:** its loop notes make gcc emit `.p2align 3` on the
  label after it. Use a bare `if` or `{ }` block.
- **`return c ? 8 : 9`** gives `movz` with the constants swapped. `if (c) return 8; return 9;`
  gives retail's `movn`.
- **`sqrtf()`** is inlined as `sqrt.s`, a NaN check (`c.eq.s f0,f0`) and a fallback call
  to the library `sqrtf` (0x32CF10). In splat output, `c1 0x....0004` is EE `sqrt.s`.
- **FP compare operand order:** `c.le.s $a,$b` follows how the C condition is written.
  `x[min] >= x[j]` and `x[j] <= x[min]` give different code, so try both.
- **Field update order:** the order of `+=` statements decides the load and store order
  (`Sg_IdInit` matched only once `entries` came before `unk18`).
- **`ABS()` macro:** `d < 0 ? -d : d` gives retail's duplicated compare branches.
- **Local `const` tables:** a local `s8 tbl[] = {...}` puts the initializer in the TU's
  `.rodata` (`ldl`/`ldr` + `sdl`/`sdr` copy to the stack). Give the TU a `.rodata`
  subsegment in `ffx2.yaml`, and use `INCLUDE_RODATA` for rodata of functions still in asm.
- **Tail calls:** a call directly followed by the epilogue becomes `j func`. The compiler
  can also duplicate the epilogue to tail-call from a branch, which retail sometimes did
  not. Unsolved, see `func_0012B000`.

- **Float constants in double expressions:** `atan2(...) + 1.570796f` stores
  `(double)1.570796f` (`0x3FF921FB00000000`) in `.rodata`. If a `.double` constant's low word
  is zero, the source wrote a float literal.
- **Statement order sets the stack layout:** the order of the stores into a local array
  decides which values gcc computes first. `func_0012AC70` matched only once `v[2]` was
  assigned before `v[0]`.
- **Extra stack space:** a frame larger than the locals need means there's an unused or
  padded local. Add a dummy array (`f32 pad[8];`) until the offsets agree.

- **64-bit arguments:** if a constant argument is built with `lui`/`ori` before the other
  arguments and not in the delay slot, the parameter may be `u64`. GS register writes
  (`func_002EBCC0(0x47, ...)`) take a `u64`.
- **Arrays at an offset:** if retail steps a pointer that starts at `a + 10` but ours indexes
  from `a`, the data is a struct with an array member at that offset. Use the struct.
- **Constants via `lui`/`ori` instead of `$gp`:** the file was assembled with `-G0`. Add
  `/* eecc-asflags: -G0 */` to it.

## Assembler differences (handled in `tools/eecc.py`)

- `move` encodes as `daddu`, not `or`.
- No hazard `nop` between an FP compare and `bc1t`/`bc1f` in reorder mode.
- `cvt.w.s` is emitted as a raw `.word`, because modern gas rejects it for r5900.
- `li.d` into a GPR becomes `.rodata` plus `lui $1`/`ld`.
- No hazard `nop` after `mtc1`/`mfc1`. FP compare loops shorter than 6 instructions get
  padding `nop`s.
- See `docs/COMPILER.md` for the full list.
