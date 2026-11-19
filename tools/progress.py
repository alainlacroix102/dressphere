#!/usr/bin/env python3
"""Report decompilation progress: functions/bytes of .text written as C.

A function counts as decompiled when it is defined in a src/*.c file and is not
pulled in with INCLUDE_ASM (NON_MATCHING drafts don't count). Sizes come from
the compiled objects in build/src, so run `ninja` first.
"""
import re
import subprocess
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
TEXT_SIZE = 0x25141C   # retail .text
TOTAL_FUNCS = 12570    # functions found by splat/spimdisasm


def main() -> None:
    done_funcs = done_bytes = 0
    for c in sorted((ROOT / "src").rglob("*.c")):
        obj = ROOT / "build" / c.relative_to(ROOT).with_suffix(".o")
        if not obj.exists():
            raise SystemExit(f"{obj} missing: run ninja first")
        raw = subprocess.run(["cpp", "-P", "-Iinclude", "-DINCLUDE_ASM(a,b)=__ASMFUNC__ b",
                              str(c)], cwd=ROOT, capture_output=True, text=True).stdout
        asm_funcs = set(re.findall(r"__ASMFUNC__\s+(\w+)", raw))
        nm = subprocess.run(["mips-linux-gnu-nm", "-S", "--defined-only", str(obj)],
                            capture_output=True, text=True, check=True).stdout
        for line in nm.splitlines():
            parts = line.split()
            name = parts[-1]
            if len(parts) == 4 and parts[2] in "Tt" and "." not in name and name not in asm_funcs:
                done_funcs += 1
                done_bytes += int(parts[1], 16)
    print(f"Functions: {done_funcs} / {TOTAL_FUNCS} ({100 * done_funcs / TOTAL_FUNCS:.3f}%)")
    print(f".text:     0x{done_bytes:X} / 0x{TEXT_SIZE:X} bytes ({100 * done_bytes / TEXT_SIZE:.3f}%)")


if __name__ == "__main__":
    main()
