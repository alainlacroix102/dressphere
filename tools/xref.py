#!/usr/bin/env python3
"""Cross-reference data symbols <-> functions across all generated asm.

    tools/xref.py D_0047B198            # which functions reference this symbol
    tools/xref.py --rodata 0x47B100 0x47B300
        # for each .rodata symbol in the range: its users (shows TU ordering,
        # since rodata is laid out in the same order as the text of each TU)
"""
import re
import sys
from collections import defaultdict
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
FUNC_RE = re.compile(r"^glabel (\w+)")
SYM_RE = re.compile(r"%(?:hi|lo|gp_rel)\((D_[0-9A-F]{8})\)|\b(D_[0-9A-F]{8})\b")


def build_index() -> dict[str, set[str]]:
    users: dict[str, set[str]] = defaultdict(set)
    files = list((ROOT / "asm").rglob("*.s"))
    for f in files:
        if "/data/" in f.as_posix():
            continue
        func = None
        for line in f.open():
            m = FUNC_RE.match(line)
            if m:
                func = m.group(1)
                continue
            if func and "D_" in line:
                for a, b in SYM_RE.findall(line):
                    users[a or b].add(func)
    # C sources reference symbols too
    for c in (ROOT / "src").rglob("*.c"):
        text = c.read_text()
        for m in re.finditer(r"^\w[^;{]*\b(func_[0-9A-F]{8})\s*\([^;]*\)\s*\{", text, re.M):
            pass
        cur = None
        for line in text.splitlines():
            m = re.match(r"^\w[\w\s\*]*\b(func_[0-9A-F]{8})\s*\(.*\)\s*\{", line)
            if m:
                cur = m.group(1)
            for s in re.findall(r"\b(D_[0-9A-F]{8})\b", line):
                if cur:
                    users[s].add(cur)
    return users


def main() -> None:
    users = build_index()
    if sys.argv[1] == "--rodata":
        lo, hi = int(sys.argv[2], 16), int(sys.argv[3], 16)
        for sym in sorted(s for s in users if lo <= int(s[2:], 16) < hi):
            print(f"{sym}: {' '.join(sorted(users[sym]))}")
        return
    for sym in sys.argv[1:]:
        print(f"{sym}: {' '.join(sorted(users.get(sym, ()))) or '(no users)'}")


if __name__ == "__main__":
    main()
