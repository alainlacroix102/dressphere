#!/usr/bin/env python3
"""Try every order of some statements until a function matches.

    tools/permute.py src/tu.c func_XXXXXXXX FIRST LAST

FIRST and LAST are 1-based source line numbers (inclusive). Each line in
that range is one statement to reorder. Every permutation is compiled and
checked with matchcheck. The first matching order is written back;
otherwise the file is restored. The scheduler often emits independent
stores in an order unrelated to the source, which this finds quickly
(up to 7 lines = 5040 tries).
"""
import itertools
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent


def main() -> None:
    src, func, first, last = Path(sys.argv[1]), sys.argv[2], int(sys.argv[3]), int(sys.argv[4])
    orig = src.read_text()
    lines = orig.splitlines(keepends=True)
    block = lines[first - 1:last]
    if len(block) > 7:
        sys.exit("too many lines to permute (max 7)")
    best = None
    try:
        for n, perm in enumerate(itertools.permutations(block)):
            if n == 0:
                continue  # the original order was already tried by the user
            src.write_text("".join(lines[:first - 1] + list(perm) + lines[last:]))
            out = subprocess.run([sys.executable, str(ROOT / "tools/matchcheck.py"), str(src)],
                                 cwd=ROOT, capture_output=True, text=True).stdout
            row = next((l for l in out.splitlines() if f" {func} " in l), "")
            if "MATCH" in row:
                best = perm
                break
    finally:
        if best is None:
            src.write_text(orig)
    if best is None:
        print(f"{func}: no order matches")
    else:
        print(f"{func}: MATCH with order:")
        print("".join(best), end="")


if __name__ == "__main__":
    main()
