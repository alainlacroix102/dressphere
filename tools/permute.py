#!/usr/bin/env python3
"""Try orders of some statements until a function matches.

    tools/permute.py src/tu.c func_XXXXXXXX FIRST LAST
    tools/permute.py --climb src/tu.c func_XXXXXXXX FIRST LAST

FIRST and LAST are 1-based source line numbers (inclusive). Each line in
that range is one statement to reorder. Each candidate order is compiled and
checked with matchcheck. The first matching order is written back;
otherwise the file is restored. The scheduler often emits independent
stores in an order unrelated to the source.

Default mode tries every permutation (up to 7 lines = 5040 tries).
--climb handles longer blocks: it moves one line at a time to any other
position and keeps a move whenever the number of differing instructions
drops, until it matches or no single move helps. The best order found is
written back even if it doesn't match.
"""
import itertools
import re
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent


def score(src: Path, func: str) -> int:
    """Number of differing instructions (0 = match)."""
    out = subprocess.run([sys.executable, str(ROOT / "tools/matchcheck.py"), str(src)],
                         cwd=ROOT, capture_output=True, text=True).stdout
    row = next((l for l in out.splitlines() if f" {func} " in l), "")
    if "MATCH" in row:
        return 0
    m = re.search(r"(\d+) differ", row)
    return int(m.group(1)) if m else 10**6


def exhaustive(src: Path, func: str, lines: list[str], first: int, last: int) -> None:
    block = lines[first - 1:last]
    if len(block) > 7:
        sys.exit("too many lines to permute (max 7); use --climb")
    best = None
    orig = "".join(lines)
    try:
        for n, perm in enumerate(itertools.permutations(block)):
            if n == 0:
                continue  # the original order was already tried by the user
            src.write_text("".join(lines[:first - 1] + list(perm) + lines[last:]))
            if score(src, func) == 0:
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


def climb(src: Path, func: str, lines: list[str], first: int, last: int) -> None:
    head, block, tail = lines[:first - 1], lines[first - 1:last], lines[last:]

    def build(b: list[str]) -> str:
        return "".join(head + b + tail)

    src.write_text(build(block))
    best = score(src, func)
    print(f"start: {best} differ", flush=True)
    improved = True
    while best and improved:
        improved = False
        for i in range(len(block)):
            for j in range(len(block)):
                if i == j:
                    continue
                cand = block[:]
                cand.insert(j, cand.pop(i))
                src.write_text(build(cand))
                s = score(src, func)
                if s < best:
                    best, block, improved = s, cand, True
                    print(f"  {best} differ", flush=True)
                    break
            if improved or not best:
                break
    src.write_text(build(block))
    print(f"{func}: {'MATCH' if best == 0 else f'best {best} differ'} with order:")
    print("".join(block), end="")


def main() -> None:
    args = sys.argv[1:]
    mode = exhaustive
    if args and args[0] == "--climb":
        mode = climb
        args = args[1:]
    src, func, first, last = Path(args[0]), args[1], int(args[2]), int(args[3])
    mode(src, func, src.read_text().splitlines(keepends=True), first, last)


if __name__ == "__main__":
    main()
