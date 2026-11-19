# Related work and symbol sources

Leads for naming functions that FFX-2 shares with other games, either through Sony's SDK
or through Square's in-house PS2 libraries. Checked November 2026. Nothing here has been
imported yet.

## Unstripped executables from Square titles of the same era

[RetroReversing's list of unstripped PS2 games](https://retroreversing.com/ps2-unstripped)
includes these Square / Square Enix releases. Their ELFs still carry symbol tables:

| Game | Serial | Released | Why it matters |
|---|---|---|---|
| Unlimited SaGa (USA) | SLUS-20678 | 2003 | Square, same period and serial range as FFX-2 (SLUS-20672) |
| Unlimited SaGa (JP/EU) | SLPS-25185, SLPS-25199, SLES-51606 | 2002–2003 | as above |
| Final Fantasy XI (JP, USA, betas, Zilart) | SLPS-25200, SCUS-97266, SLPM-62135, SCUS-97271, SLPM-65287/8 | 2001–2003 | Square PS2 code, same SDK generation |
| Dragon Quest VIII Premium Disc (JP) | SLPM-62490 | 2004 | Square Enix-era SDK libraries |
| Torneko no Daibouken 3 (JP) | SLPM-62199 | 2002 | |
| Kingdom Hearts Re:Chain of Memories (preview) | – | 2008 | later, but Square Enix |

How to use them: matching works on code, not addresses, because addresses differ between
games ([PS2Recomp notes](https://raw.githubusercontent.com/ran-j/PS2Recomp/main/README.md)).
Hash each function in an unstripped ELF with relocation fields masked (as
`tools/matchcheck.py` does) and look the hashes up in FFX-2. Sony library functions (libc,
libgraph, libdma, libpad, libmc, libcdvd, libsd) and any shared Square middleware should
match exactly when the library version is the same. Unlimited SaGa is the best first
candidate.

## Prototype builds

- [Final Fantasy X-2 (Aug 20, 2003 "Preview")](https://hiddenpalace.org/Final_Fantasy_X-2_(Aug_20,_2003_prototype)):
  nine days before our retail build (`Aug 29 2003  20:13:32`, see `func_00132908`). It
  boots into a debug menu. Hidden Palace doesn't say whether the ELF has symbols; check
  the executable for a `.symtab` or leftover map files.
- [Final Fantasy X prototypes (Sep 28 and Oct 26, 2001)](https://hiddenpalace.org/Final_Fantasy_X_(Oct_26,_2001_prototype)),
  [TCRF](https://www.tcrf.net/Proto:Final_Fantasy_X): English builds with debug features.
  FFX-2 reuses the FFX engine, so any symbols there would name many of our functions.

## Tools

- [ghidra-emotionengine-reloaded](https://github.com/chaoticgd/ghidra-emotionengine-reloaded)
  and its companion ghidra-ps2sdk: PS2 support for Ghidra, including type databases for the
  Sony SDK and an analyzer that applies SDK function signatures to an EE executable.
- [Karifean/FFXDataParser](https://github.com/Karifean/FFXDataParser): reads, edits and
  recompiles FFX (Remaster) data, including ATEL event, battle and monster scripts. Its
  script decoding should help name the handlers in `src/code_132918.c`: opcodes map to
  handlers popping int/float arguments via `func_0014A470`/`func_0014A538`.

## Not found (yet)

- No public decompilation of FFX or FFX-2 for PS2 turned up. The searches were cut short
  by a usage limit, so a Kingdom Hearts decomp and other Square PS2 projects still need
  checking.
- No FFX-specific ATEL opcode reference other than FFXDataParser's source.
