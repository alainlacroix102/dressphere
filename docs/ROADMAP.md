# Roadmap

## Phase 0 — Foundation ✅
- [x] Extract the ISO from the CHD and pull out `SLUS_206.72`
- [x] splat config; full disassembly (about 12,570 functions)
- [x] Reassemble and relink to a **byte-identical** image (SHA1 checked by `ninja`)

## Phase 1 — Compiler identification ✅ (see [COMPILER.md](COMPILER.md))
- [x] Download candidate EE compilers and get them running (see [COMPILER.md](COMPILER.md))
- [x] Find the exact compiler and flags: **ee-gcc 2.9-ee-991111, `-O2 -G0`**
- [x] Byte-level checker (`tools/matchcheck.py`) and build driver (`tools/eecc.py`)
- [x] First functions decompiled; full image still matches (`tools/progress.py`)
- [ ] Wire up asm-differ (`diff_settings.py`) and m2c context generation

## Phase 2 — Structure
- [ ] Identify statically linked libraries (Sony libkernl/libgraph/libdma/libpad/libmc/libcdvd/
      libipu/libmpeg/libsd, newlib libc, libgcc, libm) and name their symbols
- [ ] Find translation-unit boundaries (rodata grouping, assert file names, call graphs)
      and split `.text` into `c` subsegments that use `INCLUDE_ASM`
- [ ] Split `.data`/`.rodata`/`.bss` per TU

## Phase 3 — Decompilation loop (most of the work)
Each iteration:
1. Pick an unmatched function (smallest/leaf first, or finish a TU)
2. Generate a draft with m2c, plus context from headers
3. Iterate against asm-differ until the diff is 0
4. Swap `INCLUDE_ASM` for the C, run `ninja`, and the SHA1 must still match
5. Name symbols and types, update headers, commit

Track progress with `tools/progress.py` (matched bytes / total `.text`).

## Phase 4 — Toward a native port
A matching decomp is the source of truth. Running natively also needs:
- Replacing PS2 hardware access (GS/GIF/VIF/VU1 DMA chains, IOP RPC, SPU2, IPU/MPEG, CDVD)
  with a platform layer, e.g. a GS-to-modern-GPU translator plus SDL audio/input
- Rewriting the VU1 microcode (`.vutext`, `.DVP.overlay*`) as CPU or shader code
- Making 64-/128-bit EE-specific code (MMI, `sq`/`lq`) portable, and fixing endianness and
  pointer-size assumptions so it builds as a 64-bit host program
- Reading data from the user's own disc image (the disc's hidden file table)

A static recompiler (e.g. the ps2recomp approach) can run the game natively much
sooner. It is a useful parallel track for testing the platform layer while the
decomp continues.
