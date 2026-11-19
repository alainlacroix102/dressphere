#!/usr/bin/env python3
"""Report decompilation progress: functions/bytes of .text written as C.

A function counts as decompiled when it lives in a `c` subsegment and is not
pulled in with INCLUDE_ASM. Sizes come from splat's asm/nonmatchings output.
"""
import re
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
TEXT_SIZE = 0x25141C   # retail .text
TOTAL_FUNCS = 12570    # functions found by splat/spimdisasm


def main() -> None:
    done_funcs = done_bytes = 0
    for c in sorted((ROOT / "src").rglob("*.c")):
        text = c.read_text()
        asm_funcs = set(re.findall(r"INCLUDE_ASM\(\s*\"[^\"]+\"\s*,\s*(\w+)\s*\)", text))
        tu = c.relative_to(ROOT / "src").with_suffix("")
        for s in sorted((ROOT / "asm/nonmatchings" / tu).glob("*.s")):
            if s.stem in asm_funcs:
                continue
            m = re.search(r"nonmatching \S+, 0x([0-9A-Fa-f]+)", s.read_text())
            if m:
                done_funcs += 1
                done_bytes += int(m.group(1), 16)
    print(f"Functions: {done_funcs} / {TOTAL_FUNCS} ({100 * done_funcs / TOTAL_FUNCS:.3f}%)")
    print(f".text:     0x{done_bytes:X} / 0x{TEXT_SIZE:X} bytes ({100 * done_bytes / TEXT_SIZE:.3f}%)")


if __name__ == "__main__":
    main()
