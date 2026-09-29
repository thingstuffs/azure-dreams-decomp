#!/usr/bin/env python3
"""Trim GNU-as section-end padding from a SLUS rodata owner's .rodata (ELF32 MIPS REL, in place).

mipsel-linux-gnu-as rounds every section's size up to its alignment (md_section_align:
non-"elf" TARGET_OS -> min(2**align, 16)).  ASPSX/psylink did not: retail w_8005F134's two
jump tables (60 bytes, internally .align 3 padded) are followed at +60 by LIBETC VSYNC's
"VSync: timeout" string.  With SUBALIGN(1) placement the padded tail would overwrite the next
TU's retail bytes, so an owner's .rodata is cut back to exactly its manifest span.

Fail-closed: the object must have exactly one .rodata; the new size must equal the sum of the
module's `.rodata` data records; the cut bytes must be zero, shorter than the section
alignment (i.e. end padding only), and hold no relocation offset and no symbol.
No byte of section content, relocation or symbol is rewritten; only sh_size changes.
"""
from __future__ import annotations
import argparse, json, struct, sys
from pathlib import Path

EH = struct.Struct("<16sHHIIIIIHHHHHH")
SH = struct.Struct("<IIIIIIIIII")
SYM = struct.Struct("<IIIBBH")
SHT_SYMTAB, SHT_REL, SHT_RELA = 2, 9, 4


def trim(data: bytearray, want: int) -> dict:
    h = EH.unpack_from(data)
    if h[0][:4] != b"\x7fELF" or h[0][4] != 1 or h[0][5] != 1 or h[1] != 1 or h[2] != 8:
        raise ValueError("not an ELF32 little-endian MIPS relocatable")
    shoff, shentsize, shnum, shstrndx = h[6], h[11], h[12], h[13]
    secs = [list(SH.unpack_from(data, shoff + i * shentsize)) for i in range(shnum)]
    strtab = secs[shstrndx]
    def name(s):
        off = strtab[4] + s[0]
        return bytes(data[off:data.index(b"\0", off)]).decode()
    idx = [i for i, s in enumerate(secs) if name(s) == ".rodata"]
    if len(idx) != 1:
        raise ValueError(f"expected one .rodata, found {len(idx)}")
    ri = idx[0]
    ro = secs[ri]
    size, align = ro[5], max(ro[8], 1)
    if want > size:
        raise ValueError(f".rodata is {size} B, smaller than the owned span {want} B")
    if want == size:
        return {"rodata_size": size, "trimmed": 0}
    cut = bytes(data[ro[4] + want:ro[4] + size])
    if any(cut):
        raise ValueError(f"cut tail {cut.hex()} is not zero padding")
    if size - want >= min(align, 16) or (size % min(align, 16)):
        raise ValueError(f"cut of {size - want} B is not section-end alignment padding (align {align})")
    for s in secs:
        if s[1] in (SHT_REL, SHT_RELA) and s[7] == ri:
            ent = 8 if s[1] == SHT_REL else 12
            for k in range(s[5] // ent):
                off = struct.unpack_from("<I", data, s[4] + k * ent)[0]
                if off + 4 > want:
                    raise ValueError(f"relocation at .rodata+{off:#x} lies in the cut tail")
        if s[1] == SHT_SYMTAB:
            for k in range(s[5] // SYM.size):
                v, sz, _, _, _, shn = SYM.unpack_from(data, s[4] + k * SYM.size)
                if shn == ri and (v > want or v + sz > want):
                    raise ValueError(f"symbol at .rodata+{v:#x} lies in the cut tail")
    ro[5] = want
    SH.pack_into(data, shoff + ri * shentsize, *ro)
    return {"rodata_size": size, "trimmed": size - want, "owned": want}


def owned_size(manifest: Path, module: str) -> int:
    doc = json.loads(manifest.read_text())
    m = next(m for m in doc["modules"] if m["name"] == module)
    recs = [d for d in m["data"] if d["section"] == ".rodata"]
    if not recs:
        raise ValueError(f"{module}: no .rodata records")
    return recs[-1]["vram"] + recs[-1]["size"] - recs[0]["vram"]


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("--manifest", required=True)
    ap.add_argument("--module", required=True)
    ap.add_argument("--object", required=True)
    a = ap.parse_args(argv)
    p = Path(a.object)
    data = bytearray(p.read_bytes())
    res = trim(data, owned_size(Path(a.manifest), a.module))
    p.write_bytes(data)
    print(json.dumps(dict(res, module=a.module, object=a.object)), file=sys.stderr)


if __name__ == "__main__":
    main()
