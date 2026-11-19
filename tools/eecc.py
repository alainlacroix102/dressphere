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
import struct
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
AS_FLAGS = ["-EL", "-march=r5900", "-mabi=32", "-G8", "-no-pad-sections",
            "-Iinclude", "-I."]

MOVE_RE = re.compile(r"^(\s*)move\s+(\$\w+),\s*(\$\w+)\s*$")


def cc1_path(name: str) -> Path:
    found = sorted((COMPILERS / name / "lib/gcc-lib/ee").glob("*/cc1"))
    if not found:
        raise SystemExit(f"eecc: no cc1 for compiler {name}")
    return found[0]


# real (non-macro) instructions safe to place under noreorder
SIMPLE_RE = re.compile(r"^\s*(cvt\.\w+\.\w+|mov\.s|add\.s|sub\.s|mul\.s|neg\.s|abs\.s|"
                       r"c\.\w+\.s|swc1|lwc1|addu|subu|daddu|sll|srl|sra|and|or|xor|nor|"
                       r"andi|ori|xori|addiu|lui|sw|lw|sh|lh|sb|lb|sd|ld|move)\s")
BRANCH_RE = re.compile(r"^\s*(b\w*|j|jal|jr|jalr)\s")
MTC1_RE = re.compile(r"^\s*(mtc1|mfc1)\s")
LID_RE = re.compile(r"^(\s*)li\.d\s+(\$\d+),\s*(\S+)\s*$")
LIS_RE = re.compile(r"^(\s*)li\.s\s+(\$f\d+),\s*(\S+)\s*$")
FDIV_RE = re.compile(r"^(\s*)(div|rsqrt)\.s\s")
SQRTS_RE = re.compile(r"^(\s*)sqrt\.s\s+\$f(\d+),\s*\$f(\d+)\s*$")
BREAK_RE = re.compile(r"^(\s*)break\s+(\d+)\s*$")
CVTWS_RE = re.compile(r"^(\s*)cvt\.w\.s\s+\$f(\d+),\s*\$f(\d+)\s*$")
FCMP_RE = re.compile(r"^\s*c\.\w+\.s\s")
BC1_RE = re.compile(r"^\s*bc1[tf]l?\s")


LABEL_RE = re.compile(r"^(\$?\w+):")
INSN_RE = re.compile(r"^\s+[a-z][\w.]*(\s|$)")


def short_loop_pad(out: list[str], branch: str) -> int:
    """EE short-loop erratum: the 1999 assembler padded a backward branch with
    nops so that the loop (label .. branch inclusive) is at least 6 insns."""
    target = branch.split(",")[-1].strip()
    count = 1  # the compare
    for prev in reversed(out):
        m = LABEL_RE.match(prev)
        if m:
            if m.group(1) == target:
                return max(0, 6 - (count + 1))
            continue
        if INSN_RE.match(prev) and not prev.strip().startswith("."):
            count += 1
            if count > 6:
                return 0
    return 0


def fix_asm(text: str, inline_lis: bool = False) -> str:
    """Make modern gas output what the 1999 EE assembler did.

    - Hazards: the old assembler treated the EE as interlocked inside
      `.set reorder` code: no nop after mtc1/mfc1 or between an FP compare
      and bc1t/bc1f. We emit those under noreorder so modern gas can't add
      them. (It still flushed an FP-compare hazard with a nop when gcc itself
      switched to noreorder right after a compare; modern gas does the same.)
      Short backward loops were padded to 6 insns (EE short-loop erratum).
    - `move` -> `daddu` (old binutils' 64-bit encoding)
    - `cvt.w.s` -> raw .word (modern gas refuses it for r5900)
    - `break N` -> `break 0,N` (old gas put a lone code in the low field)
    - `sqrt.s` -> two nops + raw .word in the EE encoding (source in ft)
    - two nops before `div.s`/`rsqrt.s` in reorder code, as the old assembler did
    - `li.d $gpr` -> .rodata constant + ld (modern gas refuses it for r5900)
    - with `inline_lis` (files assembled -G0): `li.s` -> lui/ori/mtc1 under
      noreorder, so no hazard nops follow the mtc1
    """
    lines = text.splitlines()
    out = ["\t.set gp=64"]
    reorder = True
    last_insn = ""
    n_dbl = 0
    i = 0
    while i < len(lines):
        line = lines[i]
        stripped = line.strip()
        if stripped in (".set\tnoreorder", ".set noreorder"):
            reorder = False
        elif stripped in (".set\treorder", ".set reorder"):
            reorder = True
        m = MOVE_RE.match(line)
        if m:
            line = f"{m.group(1)}daddu\t{m.group(2)},{m.group(3)},$0"
        m = LID_RE.match(line)
        if m and reorder:
            lab = f"$LIDC{n_dbl}"
            n_dbl += 1
            out += ["\t.pushsection .rodata", "\t.align 3", f"{lab}:",
                    f"\t.double\t{m.group(3)}", "\t.popsection"]
            out += ["\t.set noat", f"{m.group(1)}lui\t$1,%hi({lab})"]
            line = f"{m.group(1)}ld\t{m.group(2)},%lo({lab})($1)\n\t.set at"
        m = LIS_RE.match(line)
        if m and reorder and inline_lis:
            bits = struct.unpack("<I", struct.pack("<f", float(m.group(3))))[0]
            ind, freg = m.group(1), m.group(2)
            if bits == 0:
                seq = [f"{ind}mtc1\t$0,{freg}"]
            else:
                seq = [f"{ind}lui\t$1,{bits >> 16:#x}"]
                if bits & 0xFFFF:
                    seq.append(f"{ind}ori\t$1,$1,{bits & 0xFFFF:#x}")
                seq.append(f"{ind}mtc1\t$1,{freg}")
            # Keep the next instruction (and any labels before it) in the
            # noreorder block too, or gas pads the mtc1 hazard with nops.
            j = i + 1
            tail = []
            while j < len(lines) and (LABEL_RE.match(lines[j]) or not lines[j].strip()
                                      or lines[j].strip().startswith(("#", ".p2align"))):
                tail.append(lines[j])
                j += 1
            if j < len(lines) and SIMPLE_RE.match(lines[j]):
                nxt = MOVE_RE.sub(lambda mm: f"{mm.group(1)}daddu\t{mm.group(2)},{mm.group(3)},$0",
                                  lines[j])
                tail.append(nxt)
                j += 1
            else:
                tail, j = [], i + 1
            out += ["\t.set noreorder", "\t.set noat", *seq, "\t.set at", *tail,
                    "\t.set reorder"]
            last_insn = tail[-1] if tail else seq[-1]
            i = j
            continue
        m = SQRTS_RE.match(line)
        if m:
            # EE sqrt.s takes its source in the ft field; the old assembler
            # also always put two nops in front of it (all 61 in retail).
            fd, fs = int(m.group(2)), int(m.group(3))
            out += [f"{m.group(1)}nop", f"{m.group(1)}nop"]
            line = f"{m.group(1)}.word\t{0x46000004 | (fs << 16) | (fd << 6):#010x}  # sqrt.s"
        m = FDIV_RE.match(line)
        if m and reorder:
            # likewise two nops before every div.s/rsqrt.s (7008 of 7096 in
            # retail; the rest are handwritten or in delay slots)
            out += [f"{m.group(1)}nop", f"{m.group(1)}nop"]
        m = BREAK_RE.match(line)
        if m:
            line = f"{m.group(1)}break\t0,{m.group(2)}"
        m = CVTWS_RE.match(line)
        if m:
            fd, fs = int(m.group(2)), int(m.group(3))
            line = f"{m.group(1)}.word\t{0x46000024 | (fs << 11) | (fd << 6):#010x}  # cvt.w.s"
        if reorder and FCMP_RE.match(line):
            j = i + 1
            while j < len(lines) and lines[j].strip().startswith("#"):
                j += 1
            if j < len(lines) and BC1_RE.match(lines[j]):
                pad = short_loop_pad(out, lines[j])
                out += ["\t.set noreorder", line, *["\tnop"] * pad, lines[j],
                        "\tnop", "\t.set reorder"]
                last_insn = lines[j]
                i = j + 1
                continue
        # cop1 moves: modern gas adds a hazard nop before the next use; the EE
        # assembler did not (the EE interlocks)
        if reorder and MTC1_RE.match(line):
            j = i + 1
            while j < len(lines) and lines[j].strip().startswith("#"):
                j += 1
            nxt = lines[j] if j < len(lines) else ""
            if SIMPLE_RE.match(nxt) and not BRANCH_RE.match(nxt):
                nxt = MOVE_RE.sub(lambda m: f"{m.group(1)}daddu\t{m.group(2)},{m.group(3)},$0", nxt)
                out += ["\t.set noreorder", line, nxt, "\t.set reorder"]
                last_insn = nxt
                i = j + 1
                continue
        if INSN_RE.match(line) and not stripped.startswith((".", "#")):
            last_insn = line
        out.append(line)
        i += 1
    return "\n".join(out) + "\n"


def compile_c(src: Path, out_o: Path, compiler: str = DEFAULT_CC,
              flags: str = DEFAULT_FLAGS, keep_asm: Path | None = None,
              defines: tuple[str, ...] = ()) -> None:
    pre = subprocess.run(["cpp", *CPP_FLAGS, *(f"-D{d}" for d in defines), str(src)], cwd=ROOT,
                         capture_output=True, text=True)
    if pre.returncode:
        sys.exit(pre.stderr)
    cc = subprocess.run(
        [str(I386 / "ld-linux.so.2"), "--library-path", str(I386),
         str(cc1_path(compiler)), "-quiet", *flags.split(), "-o", "-"],
        input=pre.stdout, cwd=ROOT, capture_output=True, text=True)
    if cc.returncode:
        sys.exit(f"{src}: cc1 failed\n{cc.stderr}")
    # Per-file assembler flags, e.g. `/* eecc-asflags: -G0 */` for modules
    # whose float constants are built with lui/ori instead of loaded from .lit4.
    extra = re.findall(r"/\*\s*eecc-asflags:\s*(.*?)\s*\*/", src.read_text())
    as_flags = AS_FLAGS + [f for e in extra for f in e.split()]
    asm = fix_asm(cc.stdout, inline_lis="-G0" in as_flags)
    if keep_asm:
        keep_asm.write_text(asm)
    out_o.parent.mkdir(parents=True, exist_ok=True)
    gas = subprocess.run(["mips-linux-gnu-as", *as_flags, "-o", str(out_o)],
                         input=asm, cwd=ROOT, capture_output=True, text=True)
    if gas.returncode:
        sys.exit(f"{src}: as failed\n{gas.stderr}")
    # MIPS gas forces 16-byte section alignment; retail objects were packed
    # tighter (.text 8, .rodata 8, .lit4 4).
    subprocess.run(["mips-linux-gnu-objcopy",
                    "--set-section-alignment", ".text=8",
                    "--set-section-alignment", ".rodata=8",
                    "--set-section-alignment", ".lit4=4", str(out_o)], check=True)


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
