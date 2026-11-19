# Matching notes (ee-gcc 2.9-ee-991111, `-O2 -G0`)

These are patterns that turned a near-match into an exact match. Add to this list as
you find more.

## Workflow

```bash
.venv/bin/python tools/m2c_draft.py func_XXXXXXXX     # first draft
.venv/bin/python tools/matchcheck.py src/tu.c         # per-function MATCH/DIFF
.venv/bin/python tools/matchcheck.py src/tu.c -d func_XXXXXXXX   # side-by-side
.venv/bin/python tools/variants.py src/tu.c func_XXXXXXXX variants.c  # try many bodies
.venv/bin/python tools/permute.py src/tu.c func_XXXXXXXX FIRST LAST   # reorder lines FIRST..LAST
.venv/bin/python tools/permute.py --climb src/tu.c func_XXXXXXXX FIRST LAST  # >7 lines: hill-climb
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
- **Inlined helpers:** when one function's body appears inside another, the helper was a
  `static inline` that both call. A plain `inline` function is emitted at the end of the
  file, not in place. Pass shared pointers (`List *l`) into the helper so caller and
  helper use one base register.
- **Store order is scheduled:** consecutive stores can come out in a different order than
  the source. Try permutations; `func_0012E7D8` needed `count, head, cur, unk8`.
- **128-bit copies:** `lq`/`sq` come from `*(u128 *)dst = *(u128 *)src` (`u128` is
  `mode(TI)` in `common.h`). Strict aliasing lets that load move ahead of an earlier `s32`
  store, as in retail `func_0012D2B8`. Struct copies with 8-byte alignment use `ld`/`sd`.
  With 4-byte alignment they use `ldl`/`ldr`. Put `__attribute__((aligned(N)))` between
  `struct {...}` and the typedef name; after the name it's ignored.
- **One `if` per condition:** a chain of separate `if (...) return 1;` statements gives a
  different block layout from one `||` condition.
- **`return f();` is not a tail call:** this gcc emits `j f` only for a call whose value is
  not returned. If retail does `jal f` and then returns `$v0`, write `return f(...);` with a
  non-void return type (`func_001308C8`, `func_00130A40`).
- **Casting a call result:** `D_x = (u8)f();` loads `%hi(D_x)` into a saved register before
  the call. Plain `D_x = f();` loads it after.
- **Handwritten modules:** splat marks some functions `/* Handwritten function */`. These
  use VU0 macro instructions, `addi`, and `$at` stores. Leave them as an `asm` segment.
  Their segment may start on a 4-byte boundary; `configure.py` then gives the object
  4-byte alignment.
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

- **Loop exits with `||`:** `if (a || b) break;` shares one branch target. Retail's
  `beqz` straight to the epilogue (`ld $ra` in the delay slot) came from two separate
  `if (a) break; if (b) break;` statements (`func_00130AE0`).
- **Error path placed last:** if retail tests `bltzl` and the error call sits at the end of
  the function, write the success path first: `if (fd >= 0) { ... } else { error(); }`.
  An early `if (fd < 0) { error(); return; }` puts the error block first
  (`func_00130CD8`).

- **`sync` after `FlushCache`:** retail's `sync; sync.p` pair is inline asm,
  `__asm__ volatile("sync.l\n\tsync.p");` (`func_00131210`).
- **`u16` parameters:** an `andi $aN,0xFFFF` on an incoming argument means the callee
  declared it `u16` (`func_001312E0`).

- **Indirect calls are never tail calls:** `f->sync(a);` at the end of a void function
  stays `jalr` + epilogue (`func_00131748`).
- **Local arrays declared late:** if the `ldl`/`ldr` copy of an initializer happens after
  a call, the array was declared inside the `if` block that follows that call
  (`char *names[3]` in `func_00131AF8`). The initializer's strings come before the
  table in `.rodata`.

- **Register choice after a call:** if a loop compare uses `$v1` where ours uses `$v0`, a
  callee in the loop returns a value (declare it `s32`, even when the result is ignored).
  `func_00131DF0` matched once `func_002534E0` returned `s32`.
- **Defaults in the `else`:** `if (load) { buf = ...; size = ...; } else { buf = 0; size = 0; }`
  puts `buf = 0` in the branch delay slot. Setting the defaults before the `if` hoists them
  (`func_00131E68`).
- **Empty string defaults:** an 8-byte zero entry in `.rodata` just before a function's
  strings is a `""` literal (`char *name = "";` in `func_001320F8`). gcc reuses one copy for
  every `""` in the function.

- **Counting loops are reversed:** gcc turns `for (i = 0; i < N; i++)` into a count-down
  `li N-1 ... addiu -1; bgez` loop when `i` is not needed in order. If retail counts down
  but steps a pointer, try the up-counting `for` first (`func_00132400`, the `unkAC` loop
  in `func_001321D0`). A down-counting source loop over an array also counts down but
  indexes with `addu` instead of stepping a pointer.
- **Divisor in a register:** `beql $aN,$aM` (with `$aM` = 0) before `break 7` means the
  divisor was a variable, not a constant (`s32 d = 10;` in `func_00132400`).
- **Short loops:** gas pads integer loops shorter than 6 instructions with `nop`s for the
  r5900 erratum just like the old assembler did, so `INCLUDE_ASM`-style padding needs no
  special handling.
- **Long store sequences:** `tools/permute.py --climb` finds the source order of 10–20
  independent stores. `func_001321D0` only needed one store moved to the end.

- **One variable, one register:** gcc 2.9 gives each local a single register for its
  whole life. If retail keeps a pointer in a temp register in one stretch and a saved
  register in another, use a separate variable for each (`w`/`c`/`g` in
  `func_00132490`).
- **Call results as arguments:** `printf(fmt, f())` loads `fmt` into a saved register before
  the call (gcc may hoist it far up). `r = f(); printf(fmt, r);` loads it after. Retail
  `func_00132490` uses both forms.
- **Signed range checks:** `r >= 0 && r < 7` is folded into one `sltiu`. Retail's
  `bltz` + `slti` came from a `switch` with `case 1: ... case 6:`.
- **`__DATE__`/`__TIME__`:** spell the retail string out (`"Aug 29 2003  20:13:32"`);
  the host preprocessor would substitute today's date.

## Assembler differences (handled in `tools/eecc.py`)

- `move` encodes as `daddu`, not `or`.
- No hazard `nop` between an FP compare and `bc1t`/`bc1f` in reorder mode.
- `cvt.w.s` is emitted as a raw `.word`, because modern gas rejects it for r5900.
- `li.d` into a GPR becomes `.rodata` plus `lui $1`/`ld`.
- No hazard `nop` after `mtc1`/`mfc1`. FP compare loops shorter than 6 instructions get
  padding `nop`s.
- See `docs/COMPILER.md` for the full list.
