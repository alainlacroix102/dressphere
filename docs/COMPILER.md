# Compiler

**Sony EE GCC 2.9 (`2.9-ee-991111`), flags `-O2 -G0`.**

It matches every function tried so far byte for byte. The other 2.9 builds on decomp.me
(`990721`, `991111-01`, `991111a`) produce identical output on these functions. We
standardise on `991111` and will revisit if a function only matches with another build.

## Build pipeline (`tools/eecc.py`)

1. Host `cpp -P -undef -nostdinc` with the EE predefines
2. Original `cc1`, a 32-bit i386 Linux binary, run through a locally unpacked glibc loader
   (`tools/i386`, from Ubuntu's `libc6-i386`), so no root or multiarch setup is needed
3. Output fix-ups:
   - prepend `.set gp=64`
   - rewrite `move a,b` as `daddu a,b,$0`. The 1999 EE binutils encoded `move` that way;
     modern gas emits `or`
   - in `.set reorder` code, emit an FP compare directly followed by `bc1t`/`bc1f` as an
     explicit noreorder `c.cond; bc1x; nop`. Modern gas inserts a compare→branch hazard
     `nop` for r5900 that the EE assembler did not. When the branch closes a loop shorter
     than 6 instructions, pad with `nop`s up to 6, as the old assembler did (the EE
     short-loop erratum)
   - put `mtc1`/`mfc1` and the next simple instruction under noreorder, so gas adds no
     hazard `nop` between them
   - emit `cvt.w.s` as a raw `.word`, because modern gas rejects it for r5900
   - rewrite gcc's divide-by-zero trap `break 7` as `break 0,7`. The old assembler put a
     single code in the low field (`0x000001CD`); modern gas puts it in the high field
   - emit `sqrt.s fd,fs` as two `nop`s plus a raw `.word` in the EE encoding (source in
     the `ft` field). All 61 `sqrt.s` in retail have the two `nop`s in front
   - put two `nop`s before every `div.s`/`rsqrt.s` in `.set reorder` code. 7008 of the
     7096 in retail have them; the rest are handwritten or sit in delay slots
   - turn `li.d $gpr,val` (soft-float double constants) into a `.double` in `.rodata` that
     is loaded with `lui $1,%hi; ld $r,%lo($1)`, as the old assembler expanded it. Modern
     gas rejects `li.d` into a GPR for r5900
   - `.set mips4` is **not** used. It changes how `c.lt.s` is encoded and leaks into the
     `INCLUDE_ASM` code in the same file
4. Modern `mips-linux-gnu-as -march=r5900 -mabi=32 -G8`. `-G8` sends `li.s` constants to
   `.lit4`, addressed gp-relative and not deduplicated, which matches retail. The same assembler handles splat's
   `INCLUDE_ASM` output in the same file
   Some modules were assembled with `-G0` instead. Their float constants are built inline
   with `lui`/`ori`/`mtc1`, not loaded from `.lit4`. Mark such a file with
   `/* eecc-asflags: -G0 */`. eecc then also expands `li.s` itself under noreorder, so gas
   adds no hazard `nop`s after the `mtc1`.
5. `objcopy --set-section-alignment` `.text=8 .rodata=8 .lit4=4`. Modern MIPS gas forces
   16-byte section alignment, but retail objects are packed tighter

## Library calls

Under `-msingle-float`, `double` is soft-float. This cc1 calls the helpers by Sony's old
libgcc names: `fptodp` (float→double), `dptofp`, `dpadd`, `dpsub`, `dpmul`, `dpdiv`,
`dpcmp`. Name them that way in `symbol_addrs.txt` so C objects link against the retail
code.

```bash
(cd /tmp && apt-get download libc6-i386) && dpkg-deb -x /tmp/libc6-i386_*.deb tools/i386
mkdir -p tools/compilers/ee-gcc2.9-991111
curl -L https://github.com/decompme/compilers/releases/download/compilers/ee-gcc2.9-991111.tar.xz \
  | tar -xJ -C tools/compilers/ee-gcc2.9-991111
```

## Checking a function

`tools/matchcheck.py src/foo.c` compiles the file and compares every `func_XXXXXXXX` it
defines against the retail binary, instruction by instruction, with relocated fields masked.
`--all-compilers` runs every installed `ee-gcc*`.

Functions still pulled in through `INCLUDE_ASM` always report MATCH. Only C definitions are
real tests. Other options:

- `-d FUNC`: side-by-side disassembly
- `-D NON_MATCHING`: test parked drafts

`tools/variants.py` tries alternative bodies for one function. `tools/m2c_draft.py FUNC`
drafts C with m2c, using the TU as context.

## How the compiler was identified

Reference function `func_0012AE10`:

```c
void func_0012AE10(void *p) {
    func_00117838(p);
    func_00117160(p, func_0011D748(2));
    func_0011BD10(p, 1);
}
```

The retail code has three telling traits: a 32-byte frame with `sd` saves in **16-byte slots**,
a **sibling (tail) call** `j func_0011BD10`, and both restores scheduled before the final
argument setup.

| Compiler | Result |
|---|---|
| **ee-gcc 2.9-ee-990721 / 991111 / 991111-01 / 991111a** | **exact match** (5/5 test functions) |
| ee-gcc 2.96-ee-001003-1 | tail call and `sd` correct, but 8-byte slots and 16-byte frame |
| ee-gcc 3.2-ee-030926 / 040921 | 8-byte slots, different scheduling, redundant `move` |
| SN ee-gcc 2.95.2-273a / 2.95.3-136 (wine) | no tail calls, `sq` saves |
| mwcps2 2.4 / 3.0.1b74 (wine) | hangs under wine (license manager). Not needed now |

The SN Windows builds split arguments on spaces, so run them through a symlink whose path
has no spaces.
