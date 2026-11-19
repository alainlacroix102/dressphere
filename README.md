# Final Fantasy X-2 Decompilation (SLUS-20672)

A work-in-progress **matching decompilation** of *Final Fantasy X-2* (PS2, USA/Canada).
The goal is C source that recompiles, with the original compiler, into a byte-identical
`SLUS_206.72`. Long-term it should become the basis for a native port to any platform
(see [docs/ROADMAP.md](docs/ROADMAP.md)).

This repository contains **no game data**. You need your own disc image.

## Target

| File | SHA1 |
|---|---|
| `SLUS_206.72` (retail ELF) | `1cde3cd6d36e0a6ff6ac3d10b2ff6b4d74a6073e` |
| `SLUS_206.72.rom` (objcopy'd loadable image) | `183475f01ab99b5760dd7160614f4da6ec2ff87f` |

- EE code, `.text` at `0x00100000`, size `0x25141C`, about 12,570 functions
- PS2 SDK libraries are version 2.3.0–2.3.4 (`PsIIlibgraph2300`, `PsIIlibkernl2340`, …)
- `$gp` = `0x0049EDF0`
- Source paths seen in asserts include `src/main/*.c`, `src/chr/*.c`, `src/id/map_id.c`, `tklib.c` and `tex_anim.c`

## Setup

Requirements: `mips-linux-gnu-binutils`, `ninja`, `python3`, `chdman` (MAME tools), `7z`.

```bash
# 1. Extract the disc (CHD -> ISO -> ELF)
mkdir -p iso/files
chdman extractdvd -i "Final Fantasy X-2 (USA, Canada).chd" -o iso/ffx2.iso
7z e -oiso/files iso/ffx2.iso SLUS_206.72 SYSTEM.CNF
mips-linux-gnu-objcopy -O binary --gap-fill=0x00 iso/files/SLUS_206.72 iso/SLUS_206.72.rom

# 2. Python tooling
python3 -m venv .venv
.venv/bin/pip install "splat64[mips]" spimdisasm "git+https://github.com/matt-kempster/m2c.git"

# 3. Candidate original compiler (decomp.me's archive; not final, see docs/COMPILER.md,
#    which also covers running these 32-bit binaries without root)
mkdir -p tools/compilers/ee-gcc2.96
curl -L https://github.com/decompme/compilers/releases/download/compilers/ee-gcc2.96.tar.xz \
  | tar -xJ -C tools/compilers/ee-gcc2.96

# 4. Split + build + verify
.venv/bin/python configure.py
ninja            # prints nothing on success; build/SLUS_206.72.ok = "OK: matches retail"
```

## Layout

| Path | Contents |
|---|---|
| `ffx2.yaml` | splat configuration (segments, section order, options) |
| `symbol_addrs.txt` | named symbols (`name = 0xADDR; // type:func`) |
| `configure.py` | runs splat, patches the linker script, writes `build.ninja` |
| `src/` | decompiled C |
| `include/` | headers (`include_asm.h`, `macro.inc`, SDK headers) |
| `tools/splat_ext/` | custom splat segment types (`vutext` for VU1 microcode) |
| `asm/`, `assets/`, `build/` | generated, not committed |

## Notes on the build

- Assembled with GNU `as -march=r5900 -mabi=32`; splat emits `.set gp=64` so 64-bit
  `ld`/`sd`/`daddu` stay real instructions.
- The retail link aligns `.sbss` to 128 and `.bss` to 256; `configure.py` patches this into
  splat's generated linker script.
- `.vutext` (VU1 microcode, 0x6750 bytes) is kept as a binary blob in its own section.
- The ELF's `.DVP.overlay*` sections are not part of the loaded image. They aren't
  covered yet.
