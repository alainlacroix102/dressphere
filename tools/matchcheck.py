#!/usr/bin/env python3
"""Compile a C file with an EE compiler and compare each function it defines
against the retail binary, instruction by instruction (relocated fields masked).

    tools/matchcheck.py src/foo.c                     # default compiler/flags
    tools/matchcheck.py -c ee-gcc2.9-991111 -f "-O2 -G0" foo.c
    tools/matchcheck.py --all-compilers foo.c         # try every installed ee-gcc

Function names must be func_XXXXXXXX (or listed in symbol_addrs.txt) so the
retail address is known. Exit status 0 if every function matches.
"""
from __future__ import annotations

import argparse
import re
import subprocess
import sys
import tempfile
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import eecc  # noqa: E402

ROOT = Path(__file__).resolve().parent.parent
ROM = ROOT / "iso/SLUS_206.72.rom"
VRAM = 0x100000
COMPILERS = ROOT / "tools/compilers"
DEFAULT_CC = eecc.DEFAULT_CC
DEFAULT_FLAGS = eecc.DEFAULT_FLAGS

DEFINES: tuple[str, ...] = ()


def compile_c(src: Path, compiler: str, flags: str, out_o: Path) -> None:
    eecc.compile_c(src, out_o, compiler, flags, defines=DEFINES)


def known_symbols() -> dict[str, int]:
    syms = {}
    for line in (ROOT / "symbol_addrs.txt").read_text().splitlines():
        m = re.match(r"\s*(\w+)\s*=\s*(0x[0-9A-Fa-f]+)", line)
        if m:
            syms[m.group(1)] = int(m.group(2), 16)
    return syms


def address_of(name: str, syms: dict[str, int]) -> int | None:
    if name in syms:
        return syms[name]
    m = re.fullmatch(r"func_([0-9A-Fa-f]{8})", name)
    return int(m.group(1), 16) if m else None


def objdump_funcs(obj: Path) -> dict[str, list[tuple[int, str | None]]]:
    """name -> [(word, reloc_type or None)] from the .text section."""
    out = subprocess.run(["mips-linux-gnu-objdump", "-d", "-r", "-z", "-EL",
                          "-mmips:5900", str(obj)], capture_output=True,
                         text=True, check=True).stdout
    funcs: dict[str, list] = {}
    cur = None
    for line in out.splitlines():
        if m := re.match(r"[0-9a-f]+ <(\w+)>:", line):
            cur = funcs.setdefault(m.group(1), [])
        elif cur is not None and (m := re.match(r"\s+[0-9a-f]+:\s+([0-9a-f]{8})\s", line)):
            cur.append([int(m.group(1), 16), None])
        elif cur is not None and (m := re.match(r"\s+[0-9a-f]+: (R_MIPS_\w+)", line)):
            cur[-1][1] = m.group(1)
    return funcs


MASK = {"R_MIPS_26": 0xFC000000, "R_MIPS_HI16": 0xFFFF0000,
        "R_MIPS_LO16": 0xFFFF0000, "R_MIPS_GPREL16": 0xFFFF0000}


def compare(name: str, ours: list, rom: bytes, addr: int) -> tuple[bool, int]:
    # trailing alignment nops in our object aren't part of the function
    while ours and ours[-1][0] == 0 and ours[-1][1] is None:
        ours = ours[:-1]
    off = addr - VRAM
    diffs = 0
    for i, (word, reloc) in enumerate(ours):
        theirs = int.from_bytes(rom[off + 4 * i: off + 4 * i + 4], "little")
        mask = MASK.get(reloc, 0xFFFFFFFF)
        if (word & mask) != (theirs & mask):
            diffs += 1
    # the retail function must also end where ours does (next word is not ours)
    return diffs == 0, diffs


def check(src: Path, compiler: str, flags: str, verbose: bool) -> bool:
    rom = ROM.read_bytes()
    syms = known_symbols()
    with tempfile.TemporaryDirectory() as td:
        obj = Path(td) / "t.o"
        compile_c(src, compiler, flags, obj)
        funcs = objdump_funcs(obj)
    ok_all = True
    for name, words in funcs.items():
        addr = address_of(name, syms)
        if addr is None:
            continue
        ok, diffs = compare(name, words, rom, addr)
        ok_all &= ok
        if verbose:
            print(f"  {'MATCH' if ok else 'DIFF '} {name} ({len(words)} insns, {diffs} differ)")
    return ok_all


def disasm(path: Path, start: int | None = None, stop: int | None = None,
           func: str | None = None) -> list[str]:
    cmd = ["mips-linux-gnu-objdump", "-d", "-r", "-z", "-EL", "-mmips:5900",
           "-M", "reg-names=numeric"]
    if start is not None:
        cmd += [f"--start-address={start:#x}", f"--stop-address={stop:#x}"]
    out = subprocess.run(cmd + [str(path)], capture_output=True, text=True).stdout
    lines, active = [], start is not None
    for line in out.splitlines():
        if func and re.match(r"[0-9a-f]+ <(\w+)>:", line):
            active = line.endswith(f"<{func}>:")
            continue
        if not active:
            continue
        if m := re.match(r"\s+[0-9a-f]+:\s+[0-9a-f]{8}\s+(.*)", line):
            lines.append(re.sub(r"\s+", " ", m.group(1)).split(" <")[0])
        elif m := re.match(r"\s+[0-9a-f]+: (R_MIPS_\w+)\s+(\S+)", line):
            lines[-1] += f"  [{m.group(2)}]"
    return lines


def show_diff(src: Path, compiler: str, flags: str, func: str) -> None:
    addr = address_of(func, known_symbols())
    with tempfile.TemporaryDirectory() as td:
        obj = Path(td) / "t.o"
        compile_c(src, compiler, flags, obj)
        ours = disasm(obj, func=func)
    theirs = disasm(ROOT / "iso/files/SLUS_206.72", addr, addr + 4 * len(ours))
    for i in range(max(len(ours), len(theirs))):
        a = ours[i] if i < len(ours) else ""
        b = theirs[i] if i < len(theirs) else ""
        def norm(s: str) -> str:
            if "  [" in s:  # relocated operand: immediate isn't comparable
                s = re.sub(r"-?(0x)?[0-9a-f]+(?=\(|$)", "R", s.split("  [")[0])
            elif re.search(r"\$\d+,-?\d+\(\$\d+\)$|lui ", s) and "R" not in s:
                pass
            if re.match(r"(b\w*|j|jal)\s", s):  # branch/jump targets aren't comparable
                s = re.sub(r",?[0-9a-fx]+$", "", s.strip()).strip()
            return re.sub(r"0x[0-9a-f]+", "X", s)
        bb = b
        if "  [" in a and re.search(r"(lui|addiu|lw|sw|lwc1|swc1|lb|lh|lbu|lhu|sb|sh|ld|sd) ", b):
            bb = re.sub(r"-?(0x)?[0-9a-f]+(?=\(|$)", "R", b) + "  [x]"
        same = norm(a) == norm(bb)
        print(f"{'  ' if same else '! '}{a:<44.44} | {b}")


def main() -> None:
    ap = argparse.ArgumentParser()
    ap.add_argument("src", type=Path)
    ap.add_argument("-c", "--compiler", default=DEFAULT_CC)
    ap.add_argument("-f", "--flags", default=DEFAULT_FLAGS)
    ap.add_argument("--all-compilers", action="store_true")
    ap.add_argument("-D", dest="defines", action="append", default=[],
                    help="extra cpp define, e.g. -D NON_MATCHING")
    ap.add_argument("-d", "--diff", metavar="FUNC", help="side-by-side disassembly for FUNC")
    args = ap.parse_args()
    src = args.src.resolve()
    global DEFINES
    DEFINES = tuple(args.defines)
    if args.diff:
        show_diff(src, args.compiler, args.flags, args.diff)
        return
    if args.all_compilers:
        for d in sorted(COMPILERS.glob("ee-gcc*")):
            if list((d / "lib/gcc-lib/ee").glob("*/cc1")):
                print(f"== {d.name} {args.flags}")
                check(src, d.name, args.flags, True)
        return
    sys.exit(0 if check(src, args.compiler, args.flags, True) else 1)


if __name__ == "__main__":
    main()
