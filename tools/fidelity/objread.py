"""Object readers for the genuine-ASPSX differential (tools/fidelity/aspsx_diff.py).

Two relocatable formats, one normalised view:

  * ELF32 little-endian MIPS (GNU as behind maspsx): sections, symtab, REL relocations.
  * SN "LNK" v2 (genuine ASPSX.EXE): the full record grammar (psyq-obj-parser, extended from
    work/tailslot_aspsx/ts_harness.py and the sibling decomp repo's tools/genuine_pipeline.py), this
    time DECODING the relocation expressions instead of skipping them.

Both readers return an `Obj`: section payloads by name, symbols {name: (section, offset, kind)},
and relocations [(section, offset, rtype, target, addend)], where

    rtype   in {"32", "26", "HI16", "LO16", "GPREL16"}
    target  = ("sym", name)            an undefined/external or common symbol
            | ("sec", section_name)    a section base (local labels, static data, text)
    addend  = the FULL addend (for ELF REL: read back from the instruction field; HI16 paired with
              its LO16 as the MIPS ABI does)

`normalise()` in aspsx_diff.py then maps both onto the same canonical relocation keys, so a
word comparison can mask relocation fields and compare relocations symbolically: two objects
whose non-relocation bits and canonical relocations agree link to the same bytes.
"""
from __future__ import annotations

import struct
from dataclasses import dataclass, field

R_TYPES_ELF = {2: "32", 4: "26", 5: "HI16", 6: "LO16", 7: "GPREL16"}


@dataclass
class Obj:
    fmt: str
    sections: dict = field(default_factory=dict)      # name -> bytes
    symbols: dict = field(default_factory=dict)       # name -> (section|None, offset, kind)
    relocs: list = field(default_factory=list)        # (section, offset, rtype, target, addend)
    unknown: list = field(default_factory=list)       # diagnostics (unknown reloc types etc.)
    func_extents: dict = field(default_factory=dict)  # LNK: name -> (section, start, end) from FUNCTION records


def _sext16(v):
    v &= 0xFFFF
    return v - 0x10000 if v & 0x8000 else v


# ------------------------------------------------------------------------------------------ ELF
def read_elf(data: bytes) -> Obj:
    if data[:4] != b"\x7fELF" or data[4] != 1 or data[5] != 1:
        raise ValueError("not an ELF32 LE object")
    (e_shoff,) = struct.unpack_from("<I", data, 0x20)
    e_shentsize, e_shnum, e_shstrndx = struct.unpack_from("<HHH", data, 0x2E)
    shdrs = []
    for i in range(e_shnum):
        shdrs.append(struct.unpack_from("<IIIIIIIIII", data, e_shoff + i * e_shentsize))
    def secdata(sh):
        name, typ, flags, addr, off, size = sh[:6]
        return b"" if typ == 8 else data[off:off + size]          # SHT_NOBITS
    shstr = secdata(shdrs[e_shstrndx])
    def cstr(tab, o):
        return tab[o:tab.index(b"\0", o)].decode("latin1")
    names = [cstr(shstr, sh[0]) for sh in shdrs]
    obj = Obj("elf")
    for i, sh in enumerate(shdrs):
        typ, flags = sh[1], sh[2]
        if typ in (1, 8) and (flags & 2):                            # PROGBITS/NOBITS, SHF_ALLOC
            obj.sections[names[i]] = secdata(sh) if typ == 1 else b"\0" * sh[5]
    # symbol table
    syms = []
    for i, sh in enumerate(shdrs):
        if sh[1] != 2:                                               # SHT_SYMTAB
            continue
        strtab = secdata(shdrs[sh[6]])
        raw = secdata(sh)
        for k in range(0, len(raw), 16):
            st_name, st_value, st_size, st_info, st_other, st_shndx = struct.unpack_from("<IIIBBH", raw, k)
            nm = cstr(strtab, st_name) if st_name else ""
            typ = st_info & 0xF; bind = st_info >> 4
            sec = names[st_shndx] if 0 < st_shndx < 0xFF00 else None
            syms.append((nm, st_value, st_size, typ, bind, st_shndx, sec))
            if nm and typ != 3 and typ != 4:                         # not SECTION / FILE
                if sec is not None:
                    obj.symbols[nm] = (sec, st_value, "func" if typ == 2 else ("global" if bind else "local"), st_size)
                elif st_shndx == 0xFFF2:                             # SHN_COMMON
                    obj.symbols[nm] = (None, st_value, "common", st_size)
                elif st_shndx == 0xFFF1:                             # SHN_ABS: an equate (`.set D_X, 0x...`)
                    obj.symbols[nm] = (None, st_value, "abs", st_size)
    # relocations (REL only; GNU as for o32)
    for i, sh in enumerate(shdrs):
        if sh[1] != 9:                                               # SHT_REL
            continue
        target_sec = names[sh[7]]
        if target_sec not in obj.sections:
            continue
        body = obj.sections[target_sec]
        raw = secdata(sh)
        rels = []
        for k in range(0, len(raw), 8):
            r_off, r_info = struct.unpack_from("<II", raw, k)
            rels.append((r_off, r_info >> 8, r_info & 0xFF))
        pending_hi = []
        for idx, (r_off, si, rt) in enumerate(rels):
            nm, val, size, typ, bind, shndx, sec = syms[si]
            if typ == 3:                                             # STT_SECTION
                target = ("sec", sec)
            elif sec is not None and bind == 0:                      # local defined symbol
                target = ("sec", sec);
            elif sec is not None:
                target = ("sym", nm)
            else:
                target = ("sym", nm)
            base = val if (typ != 3 and sec is not None and bind == 0) else 0
            w = struct.unpack_from("<I", body, r_off)[0] if r_off + 4 <= len(body) else 0
            rtype = R_TYPES_ELF.get(rt)
            if rtype is None:
                obj.unknown.append(f"elf reloc type {rt} at {target_sec}+{r_off:#x}")
                rtype = f"T{rt}"
            if rtype == "32":
                a = w
            elif rtype == "26":
                a = (w & 0x3FFFFFF) << 2
            elif rtype == "HI16":
                # MIPS REL: the addend is AHL = (hi << 16) + sext(lo of the next LO16 on the same symbol)
                lo = None
                for r2_off, si2, rt2 in rels[idx + 1:]:
                    if rt2 == 6 and si2 == si:
                        lo = struct.unpack_from("<I", body, r2_off)[0] & 0xFFFF
                        break
                a = ((w & 0xFFFF) << 16) + (_sext16(lo) if lo is not None else 0)
            elif rtype in ("LO16", "GPREL16"):
                a = _sext16(w)
            else:
                a = 0
            obj.relocs.append((target_sec, r_off, rtype, target, (a + base) & 0xFFFFFFFF))
    return obj


# ------------------------------------------------------------------------------------------ LNK
LNK_RTYPES = {16: "32", 74: "26", 82: "HI16", 84: "LO16", 100: "GPREL16"}


def _lnk_expr(d, p):
    """-> (value, new_ptr) where value is ("const", c) | ("sym", idx) | ("sect", idx) |
    ("sstart", idx) | ("send", idx) | (op, a, b)."""
    op = d[p]; p += 1
    if op == 0:
        return ("const", int.from_bytes(d[p:p + 4], "little")), p + 4
    if op == 2:
        return ("sym", int.from_bytes(d[p:p + 2], "little")), p + 2
    if op == 4:
        return ("sect", int.from_bytes(d[p:p + 2], "little")), p + 2
    if op == 12:
        return ("sstart", int.from_bytes(d[p:p + 2], "little")), p + 2
    if op == 22:
        return ("send", int.from_bytes(d[p:p + 2], "little")), p + 2
    if op in (44, 46, 50):
        a, p = _lnk_expr(d, p)
        b, p = _lnk_expr(d, p)
        return ({44: "add", 46: "sub", 50: "div"}[op], a, b), p
    raise ValueError(f"unknown LNK expression op {op} at {p - 1}")


def read_lnk(data: bytes) -> Obj:
    if data[:3] != b"LNK" or data[3] != 2:
        raise ValueError("not an LNK v2 object")
    u16 = lambda p: int.from_bytes(data[p:p + 2], "little")   # noqa: E731
    u32 = lambda p: int.from_bytes(data[p:p + 4], "little")   # noqa: E731
    sect_names, cur = {}, None
    blobs = {}
    chunk_start = {}         # section idx -> offset of the latest BYTES record
    sym_by_idx = {}          # XDEF/XREF/XBSS index -> name
    xdefs = {}               # name -> (sect idx, off)
    locals_ = {}             # name -> (sect idx, off)
    xbss = {}                # name -> (sect idx, size)
    raw_patches = []         # (sect idx, off, type, expr)
    funcs = []               # (sect idx, off, name) FUNCTION records
    fends = []               # (sect idx, off) FUNCTION_END records
    ptr = 4
    while ptr < len(data):
        op = data[ptr]; ptr += 1
        if op == 0:
            break
        elif op == 2:
            n = u16(ptr); ptr += 2
            if cur is not None:
                b = blobs.setdefault(cur, bytearray())
                chunk_start[cur] = len(b)
                b.extend(data[ptr:ptr + n])
            ptr += n
        elif op == 6:
            cur = u16(ptr); ptr += 2
        elif op == 8:
            if cur is not None:
                blobs.setdefault(cur, bytearray()).extend(b"\0" * u32(ptr))
            ptr += 4
        elif op == 10:
            typ = data[ptr]; off = u16(ptr + 1)
            expr, ptr = _lnk_expr(data, ptr + 3)
            # a PATCH follows the BYTES record it patches and its offset is relative to the START OF
            # THAT RECORD (measured: a 3.4 KB function arrives in several BYTES chunks and every
            # chunk's patches restart at 0), not to the section
            raw_patches.append((cur, chunk_start.get(cur, 0) + off, typ, expr, 0))
        elif op == 12:
            idx, sect, val = u16(ptr), u16(ptr + 2), u32(ptr + 4)
            ptr += 8; n = data[ptr]; ptr += 1
            nm = data[ptr:ptr + n].decode("latin1"); ptr += n
            sym_by_idx[idx] = nm; xdefs[nm] = (sect, val)
        elif op == 14:
            idx = u16(ptr); ptr += 2; n = data[ptr]; ptr += 1
            sym_by_idx[idx] = data[ptr:ptr + n].decode("latin1"); ptr += n
        elif op == 16:
            idx = u16(ptr); ptr += 5; n = data[ptr]; ptr += 1
            sect_names[idx] = data[ptr:ptr + n].decode("latin1"); ptr += n
        elif op == 18:
            sect, val = u16(ptr), u32(ptr + 2); ptr += 6
            n = data[ptr]; ptr += 1
            locals_.setdefault(data[ptr:ptr + n].decode("latin1"), (sect, val)); ptr += n
        elif op == 28:
            ptr += 2; ptr += 1 + data[ptr]
        elif op == 46:
            ptr += 1
        elif op == 48:
            idx, sect, size = u16(ptr), u16(ptr + 2), u32(ptr + 4)
            ptr += 8; n = data[ptr]; ptr += 1
            nm = data[ptr:ptr + n].decode("latin1"); ptr += n
            sym_by_idx[idx] = nm; xbss[nm] = (sect, size)
        elif op in (50, 52, 54, 56, 58, 60):
            ptr += {50: 2, 52: 3, 54: 4, 56: 6, 58: 8, 60: 2}[op]
        elif op == 74:
            sect, off = u16(ptr), u32(ptr + 2)
            ptr += 28; n = data[ptr]; ptr += 1
            funcs.append((sect, off, data[ptr:ptr + n].decode("latin1"))); ptr += n
        elif op == 76:
            fends.append((u16(ptr), u32(ptr + 2))); ptr += 10
        elif op in (78, 80):
            ptr += 10
        else:
            raise ValueError(f"unknown LNK opcode {op} at offset {ptr - 1}")
    obj = Obj("lnk")
    for idx, nm in sect_names.items():
        obj.sections[nm] = bytes(blobs.get(idx, b""))
    for nm, (s, v) in xdefs.items():
        obj.symbols[nm] = (sect_names.get(s), v, "global", None)
    for nm, (s, v) in locals_.items():
        obj.symbols.setdefault(nm, (sect_names.get(s), v, "local", None))
    for nm, (s, size) in xbss.items():
        obj.symbols[nm] = (None, 0, "common", size)
    for s, off, nm in funcs:
        end = next((e for (es, e) in fends if es == s and e > off), None)
        obj.func_extents[nm] = (sect_names.get(s), off, end)

    def ev(e):
        """-> ({term: coefficient}, constant).  psyq SUB(a, b) is b - a (checked: `sym-4` is
        SUB(const 4, sym)); a gp-relative patch is SUB(section_start(gp group), term)."""
        k = e[0]
        if k == "const":
            return {}, e[1]
        if k == "sym":
            nm = sym_by_idx.get(e[1], f"#{e[1]}")
            if nm in xdefs:                                  # defined here: section-relative
                s, v = xdefs[nm]
                return {("sec", sect_names.get(s)): 1}, v
            return {("sym", nm): 1}, 0
        if k == "sect":
            return {("sec", sect_names.get(e[1])): 1}, 0
        if k in ("sstart", "send"):
            return {(k, sect_names.get(e[1])): 1}, 0
        at, ac = ev(e[1]); bt, bc = ev(e[2])
        if k == "add":
            sign = 1
        elif k == "sub":
            at, ac, bt, bc = bt, bc, at, ac              # b - a
            sign = -1
        else:
            raise ValueError(f"LNK expression op {k} not evaluable")
        terms = dict(at)
        for t, c in bt.items():
            terms[t] = terms.get(t, 0) + sign * c
        return {t: c for t, c in terms.items() if c}, (ac + sign * bc) & 0xFFFFFFFF

    for sidx, off, typ, expr, _pos in raw_patches:
        sec = sect_names.get(sidx)
        rtype = LNK_RTYPES.get(typ)
        try:
            terms, const = ev(expr)
        except ValueError as exc:
            obj.unknown.append(f"lnk expr at {sec}+{off:#x}: {exc}")
            continue
        gp_base = [t for t, c in terms.items() if t[0] == "sstart" and c == -1]
        if typ == 30 or (gp_base and rtype is None):
            rtype = "GPREL16"                            # 2.56-2.81: SUB(sectstart(gp group), term)
        for t in gp_base:
            del terms[t]
        if rtype is None:
            obj.unknown.append(f"lnk patch type {typ} at {sec}+{off:#x}")
            rtype = f"T{typ}"
        pos = [t for t, c in terms.items() if c == 1]
        if len(terms) > 1 or (terms and not pos):
            obj.unknown.append(f"lnk expr at {sec}+{off:#x}: terms {terms}")
            continue
        target = pos[0] if pos else ("abs", None)
        obj.relocs.append((sec, off, rtype, target, const))
    return obj
