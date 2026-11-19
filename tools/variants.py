#!/usr/bin/env python3
"""Try alternative bodies for one function and report the diff count of each.

    tools/variants.py src/tu.c func_name variants.c

variants.c holds candidate definitions separated by lines of `//---`.
The TU is restored afterwards; the best variant is printed (apply by hand).
"""
import re
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent


def func_span(text: str, name: str) -> tuple[int, int]:
    m = re.search(rf"^[^\n;]*\b{name}\s*\([^;{{]*\)\s*\{{", text, re.M)
    if not m:
        a = re.search(rf"^INCLUDE_ASM\([^)]*\b{name}\);", text, re.M)
        if not a:
            sys.exit(f"{name} not found (neither C nor INCLUDE_ASM) in this TU")
        return a.start(), a.end()
    depth, i = 0, m.end() - 1
    while True:
        if text[i] == "{":
            depth += 1
        elif text[i] == "}":
            depth -= 1
            if depth == 0:
                return m.start(), i + 1
        i += 1


def main() -> None:
    tu, name, vfile = Path(sys.argv[1]), sys.argv[2], Path(sys.argv[3])
    base = tu.read_text()
    s, e = func_span(base, name)
    variants = [v.strip() for v in vfile.read_text().split("//---") if v.strip()]
    try:
        for i, v in enumerate(variants):
            tu.write_text(base[:s] + v + base[e:])
            out = subprocess.run([sys.executable, str(ROOT / "tools/matchcheck.py"), str(tu)],
                                 capture_output=True, text=True).stdout + ""
            line = next((l for l in out.splitlines() if f" {name} " in l), "compile error")
            print(f"variant {i}: {line.strip()}")
    finally:
        tu.write_text(base)


if __name__ == "__main__":
    main()
