# Compiler identification (in progress)

Not identified yet. These are the results of testing so far.

## Reference function

`func_0012AE10` (0x40 bytes), with a plausible source:

```c
void func_0012AE10(void *p) {
    func_00117838(p);
    func_00117160(p, func_0011D748(2));
    func_0011BD10(p, 1);
}
```

Retail output, with the traits a candidate must reproduce marked:

```
addiu  sp, sp, -0x20      # 32-byte frame
sd     s0, 0x0(sp)        # 64-bit sd (not sq), 16-byte save slots
sd     ra, 0x10(sp)
jal    func_00117838
 daddu s0, a0, zero
jal    func_0011D748
 addiu a0, zero, 2
daddu  a0, s0, zero
jal    func_00117160
 mov.s f12, f0
daddu  a0, s0, zero
ld     ra, 0x10(sp)
ld     s0, 0x0(sp)        # both restores before the arg setup
addiu  a1, zero, 1
j      func_0011BD10      # sibling (tail) call
 addiu sp, sp, 0x20
```

## Results

| Compiler | Tail call | Save insn | Slot stride | Verdict |
|---|---|---|---|---|
| ee-gcc 2.95.2-273a (SN) | no | `sq` | 16 | ✗ |
| ee-gcc 2.95.3-136 (SN) | no | `sq` s0 / `sd` ra | 16 | ✗ |
| **ee-gcc 2.96-ee-001003-1** | **yes** | **`sd`** | 8 | closest: frame and epilogue order differ |
| ee-gcc 3.2-ee-030926 | yes | `sd` | 8 | ✗ (scheduling, redundant `move`) |
| ee-gcc 3.2-ee-040921 | yes | `sd` | 8 | ✗ (same as 030926) |
| mwcps2 2.4 / 3.0.1b74 | — | — | — | hangs under wine; still to test |

Next things to try:
- Flag sweeps on 2.96 (`-O1`/`-O2`/`-O3`, `-fno-schedule-insns{,2}`, `-mno-...` target switches)
- Get CodeWarrior running (hangs on license manager `LMGR326B.DLL`; decomp.me runs it with
  specific wine env vars)
- Check whether `.gcc_except_table` / `.lit4` imply a GNU toolchain for the game code, or only
  for the SDK libraries

## Running the Linux compilers without root

The decomp.me Linux builds are 32-bit i386 and need only `libc.so.6`. Unpack Ubuntu's
`libc6-i386` locally and run `cc1` through its loader:

```bash
(cd /tmp && apt-get download libc6-i386) && dpkg-deb -x /tmp/libc6-i386_*.deb tools/i386
L=tools/i386/usr/lib32
cpp -P foo.c | $L/ld-linux.so.2 --library-path $L \
  tools/compilers/ee-gcc2.96/lib/gcc-lib/ee/2.96-ee-001003-1/cc1 -quiet -O2 -G0 -o foo.s
```

The Windows (SN) builds run under wine, but their driver splits arguments on spaces, so
call them through a symlink whose path has no spaces.
