#!/usr/bin/env python3
"""List functions found by splat in the big .text asm: name, vram, size, padding after."""
import re, sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent

def load(path=ROOT / "asm/cod/000000.s"):
    funcs = []
    pat = re.compile(r"^nonmatching (\S+), 0x([0-9A-F]+)")
    addr = re.compile(r"/\* [0-9A-F]+ ([0-9A-F]{8}) ")
    pending = None
    for line in open(path):
        m = pat.match(line)
        if m:
            pending = [m.group(1), None, int(m.group(2), 16)]
            continue
        if pending and pending[1] is None:
            a = addr.search(line)
            if a:
                pending[1] = int(a.group(1), 16)
                funcs.append(tuple(pending))
                pending = None
    return funcs

if __name__ == "__main__":
    for name, va, size in load():
        print(f"{va:08X} {size:6X} {name}")
