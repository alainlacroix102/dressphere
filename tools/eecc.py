#!/usr/bin/env python3
"""Compile one C file the way the retail build did.

    tools/eecc.py [-c COMPILER] [-f FLAGS] -o out.o in.c

Pipeline: host cpp -> original EE cc1 (32-bit, run through the bundled i386
loader in tools/i386) -> modern GNU as for the r5900.

The cc1 output is assembled with modern gas so that INCLUDE_ASM'd splat output
(which uses o32 register names + `.set gp=64`) works in the same file. Modern
gas differs from the 1999 EE binutils in one way that matters here: it encodes
`move` as `or`, the old one as `daddu`. We rewrite `move` before assembling.
"""
from __future__ import annotations

import argparse
import re
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
I386 = ROOT / "tools/i386/usr/lib32"
COMPILERS = ROOT / "tools/compilers"
DEFAULT_CC = "ee-gcc2.9-991111"
DEFAULT_FLAGS = "-O2 -G0"
CPP_FLAGS = [
    "-P", "-undef", "-nostdinc", "-Iinclude", "-Isrc", "-Iasm",
    "-D__GNUC__=2", "-D__GNUC_MINOR__=9", "-Dmips", "-D__mips__", "-D__MIPSEL__",
    "-D_R5900", "-D__R5900__", "-D__ee__", "-D_LANGUAGE_C", "-DLANGUAGE_C",
    "-D__mips_single_float", "-D__mips64", "-D__mips_eabi",
]
AS_FLAGS = ["-EL", "-march=r5900", "-mabi=32", "-G0", "-no-pad-sections",
            "-Iinclude", "-I."]

MOVE_RE = re.compile(r"^(\s*)move\s+(\$\w+),\s*(\$\w+)\s*$")


def cc1_path(name: str) -> Path:
    found = sorted((COMPILERS / name / "lib/gcc-lib/ee").glob("*/cc1"))
    if not found:
        raise SystemExit(f"eecc: no cc1 for compiler {name}")
    return found[0]


def fix_asm(text: str) -> str:
    out = ["\t.set gp=64"]
    for line in text.splitlines():
        m = MOVE_RE.match(line)
        if m:
            line = f"{m.group(1)}daddu\t{m.group(2)},{m.group(3)},$0"
        out.append(line)
    return "\n".join(out) + "\n"


def compile_c(src: Path, out_o: Path, compiler: str = DEFAULT_CC,
              flags: str = DEFAULT_FLAGS, keep_asm: Path | None = None) -> None:
    pre = subprocess.run(["cpp", *CPP_FLAGS, str(src)], cwd=ROOT,
                         capture_output=True, text=True)
    if pre.returncode:
        sys.exit(pre.stderr)
    cc = subprocess.run(
        [str(I386 / "ld-linux.so.2"), "--library-path", str(I386),
         str(cc1_path(compiler)), "-quiet", *flags.split(), "-o", "-"],
        input=pre.stdout, cwd=ROOT, capture_output=True, text=True)
    if cc.returncode:
        sys.exit(f"{src}: cc1 failed\n{cc.stderr}")
    asm = fix_asm(cc.stdout)
    if keep_asm:
        keep_asm.write_text(asm)
    out_o.parent.mkdir(parents=True, exist_ok=True)
    gas = subprocess.run(["mips-linux-gnu-as", *AS_FLAGS, "-o", str(out_o)],
                         input=asm, cwd=ROOT, capture_output=True, text=True)
    if gas.returncode:
        sys.exit(f"{src}: as failed\n{gas.stderr}")
    # MIPS gas forces .text to 16-byte alignment; the retail objects were 8.
    subprocess.run(["mips-linux-gnu-objcopy", "--set-section-alignment",
                    ".text=8", str(out_o)], check=True)


def main() -> None:
    ap = argparse.ArgumentParser()
    ap.add_argument("src", type=Path)
    ap.add_argument("-o", "--out", type=Path, required=True)
    ap.add_argument("-c", "--compiler", default=DEFAULT_CC)
    ap.add_argument("-f", "--flags", default=DEFAULT_FLAGS)
    ap.add_argument("-S", "--keep-asm", type=Path)
    a = ap.parse_args()
    compile_c(a.src.resolve(), a.out.resolve(), a.compiler, a.flags, a.keep_asm)


if __name__ == "__main__":
    main()
