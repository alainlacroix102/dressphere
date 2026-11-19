"""splat segment type for the EE ELF's `.vutext` section (VU1 microcode).

Emitted as an opaque binary blob in its own `.vutext` section so the linker
places it after `.rodata` exactly like the retail link did.
"""
from typing import Optional

from splat.segtypes.common.textbin import CommonSegTextbin


class PS2SegVutext(CommonSegTextbin):
    def get_linker_section(self) -> str:
        return ".vutext"

    def get_section_flags(self) -> Optional[str]:
        return "ax"
