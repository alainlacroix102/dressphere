#!/usr/bin/env python3
"""Draft C for a function with m2c, using its TU's C file as type context.

    tools/m2c_draft.py func_0012AE98 [extra m2c args...]
"""
import re
import subprocess
import sys
import tempfile
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
M2C = ROOT / ".venv/bin/m2c"


def find_asm(func: str) -> Path:
    hits = list((ROOT / "asm/nonmatchings").rglob(f"{func}.s"))
    if not hits:
        sys.exit(f"no asm/nonmatchings/**/{func}.s (is it inside a `c` subsegment?)")
    return hits[0]


def main() -> None:
    func, extra = sys.argv[1], sys.argv[2:]
    asm = find_asm(func)
    tu = ROOT / "src" / (asm.parent.relative_to(ROOT / "asm/nonmatchings").as_posix() + ".c")
    with tempfile.TemporaryDirectory() as td:
        ctx = Path(td) / "ctx.c"
        src = tu if tu.exists() else ROOT / "include/common.h"
        pre = subprocess.run(["cpp", "-P", "-undef", "-DM2CTX", "-D__attribute__(x)=",
                              "-Iinclude", "-Isrc", str(src)],
                             capture_output=True, text=True, check=True).stdout
        ctx.write_text(pre)
        # m2c doesn't know splat's `nonmatching` / `endlabel` macros
        body = "\n".join(l for l in asm.read_text().splitlines()
                         if not re.match(r"\s*(nonmatching|endlabel|\.align)\b", l))
        s = Path(td) / "f.s"
        s.write_text(body + "\n")
        r = subprocess.run([str(M2C), "-t", "mipsee-gcc-c", "--context", str(ctx),
                            *extra, str(s)], capture_output=True, text=True)
        sys.stdout.write(r.stdout)
        sys.stderr.write(r.stderr)


if __name__ == "__main__":
    main()
