"""entity.py - the hand-recovered entity record (supersedes include/records/Rec_D_800E3D7C.h) and the row rewrite.

    python3 tools/entity.py header > inc/shared/entity.h
    import entity; entity.rewrite(text) -> (text, notes) | (None, reason)

FIELDS is the one source: (offset, C type, name, size, signed, evidence).  A Fixed1616 is the 16.16 fixed-point
word the census shows read both whole (lw, at00_s32) and as its integer half (lh at +2, at02_s16).
Every Rec_D_800E3D7C member spelling a row uses (`->unk_2A.as_s16`, `->unk_00.at02_s16.v`, `->unk_28`) is mapped
to the field at that byte offset:
    same size + sign      -> base->field
    other sign, read      -> ((T)base->field)
    other size / pointer  -> (*(T *)((u8 *)&base->field + d))     (a union site: a view at the use)
    volatile variants     -> refused (hidden scaffolding in the generated header; the row keeps the Rec view)"""
import re, sys
from pathlib import Path
sys.path.insert(0, str(Path(__file__).parent))
from consolidate import code_spans

FIELDS = [
 (0x00, "Fixed1616", "x", 4, True, "world x, 16.16: lw 26 / integer half lh+2 91 (tile*64+32 in func_800A08A0)"),
 (0x04, "Fixed1616", "y", 4, True, "world y (the second ground axis; dirStepY pairs with it)"),
 (0x08, "Fixed1616", "z", 4, True, "height: compared with the ground height func_800BCB04 returns (func_807B0110)"),
 (0x0C, "int", "unk_0C", 4, True, "as_s32 176+366 / u32 1"),
 (0x10, "int", "unk_10", 4, True, "at00_s32 369; bytes +1/+2/+3 read singly (views)"),
 (0x14, "int", "flags14", 4, True, "as_s32 219: bit tests (& 0x4000, & 0x20000000 in func_80CC266C)"),
 (0x18, "int", "unk_18", 4, True, ""),
 (0x1C, "int", "flags1C", 4, True, "as_s32 125 / u32 74: bit sets/clears (|= 0x80000, &= ~0x10000, >> 19 & 1 in slus/w_80042BDC)"),
 (0x20, "short", "unk_20", 2, True, ""),
 (0x22, "unsigned char", "pad_22[2]", 2, False, ""),
 (0x24, "unsigned char", "tileX", 1, False, "map-grid x byte: func_8009FB34(tileX + dirStepX[d], ...), func_8009A3D0(tileX, tileY, ...)"),
 (0x25, "unsigned char", "tileY", 1, False, "map-grid y byte (pair read as one s16 at 0x24 by some rows: a view)"),
 (0x26, "unsigned char", "unk_26", 1, False, ""),
 (0x27, "unsigned char", "unk_27", 1, False, ""),
 (0x28, "unsigned char", "unk_28", 1, False, "101 uses"),
 (0x29, "unsigned char", "unk_29", 1, False, ""),
 (0x2A, "short", "facing", 2, True, "as_s16 692: `(viewAngle + facing + 0x100) >> 9 & 7` picks the 8-way sprite; set to direction << 9"),
 (0x2C, "short", "unk_2C", 2, True, ""),
 (0x2E, "unsigned char", "pad_2E[4]", 4, False, ""),
 (0x32, "short", "unk_32", 2, True, ""),
 (0x34, "unsigned char", "pad_34[13]", 13, False, ""),
 (0x41, "signed char", "unk_41", 1, True, ""),
 (0x42, "signed char", "unk_42", 1, True, ""),
 (0x43, "unsigned char", "unk_43", 1, False, ""),
 (0x44, "unsigned short", "unk_44", 2, False, "whole word read 3x (view)"),
 (0x46, "unsigned short", "unk_46", 2, False, "at02_u16 282: bit 15 cleared (&= 0x7FFF)"),
 (0x48, "unsigned char", "unk_48", 1, False, "s32/s8/u8 views"),
 (0x49, "unsigned char", "unk_49", 1, False, ""),
 (0x4A, "unsigned char", "unk_4A", 1, False, ""),
 (0x4B, "unsigned char", "unk_4B", 1, False, ""),
 (0x4C, "void *", "unk_4C", 4, False, "as_pv 4 / s32 3"),
 (0x50, "unsigned short", "unk_50", 2, False, "u16 / pointer / s32 views"),
 (0x52, "unsigned short", "unk_52", 2, False, ""),
 (0x54, "int", "unk_54", 4, True, ""),
 (0x58, "void *", "unk_58", 4, False, ""),
 (0x5C, "int", "unk_5C", 4, True, ""),
 (0x60, "void *", "target", 4, False, "as_pv 41: the entity an action targets (func_80CC266C stores the chosen neighbour)"),
 (0x64, "short", "unk_64", 2, True, "as_s16 63 / u16 3"),
 (0x66, "unsigned char", "pad_66[2]", 2, False, ""),
 (0x68, "unsigned char", "unk_68", 1, False, ""),
 (0x69, "unsigned char", "unk_69", 1, False, ""),
 (0x6A, "unsigned short", "unk_6A", 2, False, "as_u16 93 / s16 7: (unk_6A >> 9) & 7 is a direction"),
 (0x6C, "unsigned char", "pad_6C[1]", 1, False, ""),
 (0x6D, "signed char", "unk_6D", 1, True, "as_s8 74+65 / u8 47+80 (A/B in REPORT)"),
 (0x6E, "unsigned char", "pad_6E[3]", 3, False, ""),
 (0x71, "unsigned char", "unk_71", 1, False, "as_u8 50+78 / s8 2"),
 (0x72, "signed char", "unk_72", 1, True, ""),
 (0x73, "signed char", "unk_73", 1, True, ""),
 (0x74, "unsigned char", "pad_74[16]", 16, False, ""),
 (0x84, "signed char", "unk_84", 1, True, ""),
 (0x85, "signed char", "unk_85", 1, True, ""),
 (0x86, "unsigned char", "pad_86[2]", 2, False, ""),
 (0x88, "short", "unk_88", 2, True, ""),
 (0x8A, "short", "unk_8A", 2, True, ""),
 (0x8C, "unsigned char", "pad_8C[10]", 10, False, ""),
 (0x96, "unsigned short", "unk_96", 2, False, ""),
 (0x98, "unsigned short", "unk_98", 2, False, ""),
 (0x9A, "unsigned char", "unk_9A", 1, False, ""),
 (0x9B, "unsigned char", "unk_9B", 1, False, ""),
 (0x9C, "unsigned char", "pad_9C[8]", 8, False, ""),
 (0xA4, "int", "unk_A4", 4, True, "s32 / s16+2 / u16+2 views (Rec_D_800814A8 reads +2 as u16)"),
 (0xA8, "unsigned char", "unk_A8", 1, False, "Rec_D_800814A8"),
 (0xA9, "unsigned char", "pad_A9[1]", 1, False, ""),
 (0xAA, "short", "unk_AA", 2, True, ""),
 (0xAC, "void *", "unk_AC", 4, False, "Rec_D_800814A8"),
 (0xB0, "void *", "unk_B0", 4, False, "Rec_D_800814A8"),
 (0xB4, "unsigned char", "pad_B4[20]", 20, False, ""),
 (0xC8, "void *", "unk_C8", 4, False, ""),
 (0xCC, "unsigned char", "pad_CC[6]", 6, False, ""),
 (0xD2, "unsigned char", "unk_D2", 1, False, ""),
 (0xD3, "unsigned char", "pad_D3[5]", 5, False, ""),
 (0xD8, "int", "unk_D8", 4, True, ""),
 (0xDC, "unsigned char", "pad_DC[24]", 24, False, ""),
 (0xF4, "int", "unk_F4", 4, True, "Rec_D_800814A8"),
 (0xF8, "unsigned char", "pad_F8[10]", 10, False, ""),
 (0x102, "unsigned char", "unk_102", 1, False, "Rec_D_800814A8"),
 (0x103, "unsigned char", "pad_103[1]", 1, False, ""),
 (0x104, "int", "unk_104", 4, True, ""),
 (0x108, "unsigned char", "pad_108[4]", 4, False, ""),
 (0x10C, "unsigned short", "unk_10C", 2, False, "Rec_D_800814A8"),
 (0x10E, "unsigned char", "pad_10E[2]", 2, False, ""),
 (0x110, "int", "unk_110", 4, True, ""),
 (0x114, "unsigned char", "pad_114[20]", 20, False, ""),
 (0x128, "int", "unk_128", 4, True, ""),
]
SIZE = 0x12C
T = {"s8": (1, True, "signed char"), "u8": (1, False, "unsigned char"), "s16": (2, True, "short"), "u16": (2, False, "unsigned short"),
     "s32": (4, True, "int"), "u32": (4, False, "unsigned int"), "pv": (4, None, "void *"), "pu8": (4, None, "unsigned char *"),
     "pu16": (4, None, "unsigned short *"), "vs32": (4, True, "volatile int")}
REC_T = {"s8": "s8", "u8": "u8", "s16": "s16", "u16": "u16", "s32": "s32", "u32": "u32", "pv": "void *", "pu8": "u8 *", "pu16": "u16 *"}

def header(overrides=None):
    fields = [dict(zip(("off", "ty", "name", "size", "signed", "ev"), f)) for f in FIELDS]
    for f in fields:
        if overrides and f["name"] in overrides: f["ty"], f["signed"] = overrides[f["name"]]
    out = ['#ifndef SHARED_ENTITY_H', '#define SHARED_ENTITY_H', '',
           '/* EntityRec: the actor/entity record of the DUNGEON (and TOWN) object system, hand-recovered (r78 phase 5).',
           ' * It supersedes the generated include/records/Rec_D_800E3D7C.h: same 0x12C-byte layout, its "accessed as both"',
           ' * unions resolved to one field type each (the majority retail access; the minority reads keep a cast or a view',
           ' * at the use).  Instances: the pointee of D_800E3D7C (record_ptrs.h), the 537 functions that take one as a',
           ' * parameter (Rec census), and the records the census rooted at D_80083780 / D_80083498.',
           ' * Objects carry a 0x20-byte header BEFORE the record (callers pass `record - 0x20` to the object system and',
           ' * mark `((u16 *)record)[-1] |= 0x8000` when it finishes); that header is not part of this type.',
           ' * Names only where every use agrees (tileX/tileY, facing, x/y/z, target, flags words); the rest stay unk_. */',
           '', 'typedef union Fixed1616 {', '    int v;                          /* the whole 16.16 word (lw/sw) */',
           '    struct { unsigned short frac; short i; } w;   /* w.i: the integer half (lh at +2) */', '} Fixed1616;', '',
           'typedef struct EntityRec {']
    for f in fields:
        decl = "%s %s;" % (f["ty"], f["name"])
        out.append("    /* 0x%03X */ %-34s%s" % (f["off"], decl, ("/* %s */" % f["ev"]) if f["ev"] else ""))
    out += ['} EntityRec;', '', '#endif', '']
    return "\n".join(out)

def field_table(overrides=None):
    tab = []
    for off, ty, name, size, signed, ev in FIELDS:
        if overrides and name in overrides: ty, signed = overrides[name]
        if name.startswith("pad_"): continue
        tab.append((off, ty, name, size, signed))
    return tab

def parse_rec(path):
    """{member: [(path, abs_off, key)]} from the generated header; key in T."""
    text = open(path).read(); mem = {}
    for line in text.splitlines():
        m = re.match(r"\s*union \{(.*)\} (unk_[0-9A-F]+);", line)
        if m:
            base = int(m.group(2)[4:], 16); vs = []
            for v in re.finditer(r"struct \{ (?:u8 pad\[0x([0-9A-F]+)\]; )?([\w ]+?)(\s*\*)? v; \} (at\d\d_\w+)|((?:volatile )?[\w]+)(\s*\*)? (as_\w+);", m.group(1)):
                if v.group(4):
                    d = int(v.group(1) or "0", 16); key = v.group(4).split("_", 1)[1]; vs.append(("." + v.group(4) + ".v", base + d, key))
                else:
                    key = v.group(7)[3:]; vs.append(("." + v.group(7), base, key))
            mem[m.group(2)] = vs; continue
        m = re.match(r"\s*(u8|s8|u16|s16|s32|u32|void \*)\s*(unk_[0-9A-F]+);", line)
        if m:
            key = {"void *": "pv"}.get(m.group(1), m.group(1)); mem[m.group(2)] = [("", int(m.group(2)[4:], 16), key)]
    return mem

RECS = {}
def _base_start(s, i):
    """start index of the postfix expression that ends at s[i-1] (before `->` or `.`)."""
    j = i
    while True:
        while j > 0 and s[j - 1].isspace(): j -= 1
        if j > 0 and s[j - 1] in ")]":
            close = s[j - 1]; opn = "(" if close == ")" else "["; d = 0; k = j - 1
            while k >= 0:
                if s[k] == close: d += 1
                elif s[k] == opn:
                    d -= 1
                    if d == 0: break
                k -= 1
            j = k
            if close == "]": continue
            # a call or cast-free paren group: keep walking if an identifier precedes (function call)
            if j > 0 and (s[j - 1].isalnum() or s[j - 1] == "_"): continue
            return j
        k = j
        while k > 0 and (s[k - 1].isalnum() or s[k - 1] == "_"): k -= 1
        if k > 1 and s[k - 2:k] == "->" or (k > 0 and s[k - 1] == "." ):
            j = k - (2 if s[k - 2:k] == "->" else 1); continue
        return k

def _emit(text, st, mend, base, off, key, tab, notes):
    """the Entity spelling of an access of type `key` at byte `off` through `base` (text[st:mend] is the old access)."""
    m_end = mend
    size, signed, cty = T[key]
    # the field at/around off
    f = next((x for x in tab if x[0] <= off < x[0] + x[3]), None)
    if f is None: raise ValueError("offset 0x%X outside every field" % off)
    foff, fty, fname, fsize, fsigned = f
    tail = text[m_end:]
    lv = re.match(r"\s*(=(?!=)|[-+*/%&|^]=|<<=|>>=|\+\+|--)", tail) is not None or re.search(r"(\+\+|--)\s*$", text[:st]) is not None
    simple = re.match(r"\s*=(?!=)", tail) is not None
    if fty == "Fixed1616":
        if off == foff and size == 4 and key in ("s32", "u32"): acc, aty, asg = fname + ".v", "int", True
        elif off == foff + 2 and size == 2: acc, aty, asg = fname + ".w.i", "short", True
        else: acc = None
    elif off == foff and size == fsize: acc, aty, asg = fname, fty, fsigned
    else: acc = None
    ptr_f = fty.endswith("*"); ptr_a = key.startswith("p")
    if acc is not None and (ptr_f == ptr_a) and (ptr_f or asg == signed):
        rep = "%s->%s" % (base, acc); notes.append(fname)
    elif acc is not None and not ptr_f and not ptr_a and lv and asg != signed and size == (4 if fty == "Fixed1616" and acc.endswith(".v") else (2 if acc.endswith(".w.i") else fsize)) \
            and text[:st].rstrip()[-1:] in (";", "{", "}"):
        # a statement-level compound assignment: the stored bits do not depend on the view's sign
        rep = "%s->%s" % (base, acc); notes.append(fname)
    elif acc is not None and not ptr_f and not ptr_a and (not lv or simple):
        rep = ("%s->%s" % (base, acc)) if lv else "((%s)%s->%s)" % (REC_T[key], base, acc); notes.append("(%s)%s" % (key, fname))
    elif acc is not None and ptr_f != ptr_a and not lv:
        rep = "((%s)%s->%s)" % (REC_T[key], base, acc); notes.append("(%s)%s" % (key, fname))
    elif acc is not None and ptr_f != ptr_a and simple:
        rep = "%s->%s" % (base, acc); notes.append(fname)
    else:
        d = off - foff; fexpr = "%s->%s" % (base, fname)
        rep = "(*(%s *)((u8 *)&%s + %d))" % (REC_T[key], fexpr, d) if d else "(*(%s *)&%s)" % (REC_T[key], fexpr)
        notes.append("view %s@0x%X" % (key, off))
    return rep

def rewrite(text, rec_path, overrides=None, recname="Rec_D_800E3D7C"):
    if rec_path not in RECS: RECS[rec_path] = parse_rec(rec_path)
    REC = RECS[rec_path]
    tab = field_table(overrides); notes = []
    if recname not in text: return None, "no " + recname
    # which expressions are Rec-typed: casts `(Rec_D_800E3D7C *)` and identifiers declared `Rec_D_800E3D7C *name`
    rec_vars = set(re.findall(r"\b%s\s*\*\s*(?:const\s+)?(\w+)" % recname, text))
    mrx = re.compile(r"(->|\.)\s*(unk_[0-9A-F]+)((?:\.(?:as_\w+|at\d\d_\w+\.v))?)\b")
    out = []; last = 0; spans = code_spans(text); changed = 0
    def in_code(i): return any(a <= i < b for a, b in spans)
    for m in mrx.finditer(text):
        if not in_code(m.start()): continue
        member, path = m.group(2), m.group(3)
        if member not in REC: continue
        st = _base_start(text, m.start())
        base = text[st:m.start()].strip()
        is_rec = base in rec_vars or bool(re.match(r"^\(\s*\(\s*(?:struct\s+)?%s\s*\*\s*\)" % recname, base))
        if not is_rec: continue
        if m.group(1) == ".": return None, "record by value (%s)" % base[:30]
        v = [x for x in REC[member] if x[0] == path]
        if not v: return None, "unknown spelling %s%s" % (member, path)
        _, off, key = v[0]
        if key == "vs32": return None, "volatile view %s%s (hidden scaffolding in the generated record)" % (member, path)
        try:
            rep = _emit(text, st, m.end(), base, off, key, tab, notes)
        except ValueError as e:
            return None, str(e)
        out.append(text[last:st]); out.append(rep); last = m.end(); changed += 1
    out.append(text[last:]); text = "".join(out)
    if not changed: return None, "no Rec member access"
    from consolidate import sub_code
    text = sub_code(r"\b%s\b" % recname, "EntityRec", text)     # code only: comments and the include path keep the old name
    if re.search(r"\.(as_\w+|at\d\d_\w+)\b", re.sub(r"/\*.*?\*/", "", text, flags=re.S)) and "Entity" in text:
        pass
    if '#include "shared/entity.h"' not in text:
        m = re.search(r'^#include "records/%s.h"[^\n]*\n' % recname, text, re.M)
        code_now = "".join(text[a:b] for a, b in code_spans(text))
        ptrsym = recname.replace("Rec_", "")
        if m and not re.search(r"\b%s\b|\b%s\b" % (recname, ptrsym), code_now.replace('"records/%s.h"' % recname, "")):
            text = text[:m.start()] + '#include "shared/entity.h"\n' + text[m.end():]
        else:
            m = re.search(r'^#include "common.h"[^\n]*\n', text, re.M); pos = m.end() if m else 0
            text = text[:pos] + '#include "shared/entity.h"\n' + text[pos:]
    return text, "%d accesses; " % changed + ", ".join(dict.fromkeys(notes))

if __name__ == "__main__" and sys.argv[1:] == ["header"]:
    print(header())


KEY_OF = {"s8": "s8", "signed char": "s8", "char": "s8", "u8": "u8", "unsigned char": "u8", "s16": "s16", "short": "s16",
          "u16": "u16", "unsigned short": "u16", "s32": "s32", "int": "s32", "long": "s32", "M2C_UNK": "s32",
          "u32": "u32", "unsigned int": "u32"}
def fold_views(text, overrides=None):
    """((V *)X)->m where the SAME base X is also used as ((Entity *)X) in the row: V is a slice of the entity, so
    its member becomes the Entity field at V's member offset.  V's typedef goes when nothing else uses it."""
    from consolidate import parse_views, sub_code
    views = parse_views(text); tab = field_table(overrides); notes = []
    code = "".join(text[a:b] for a, b in code_spans(text))
    bases = set(b.strip() for b in re.findall(r"\(\s*\(\s*EntityRec\s*\*\s*\)\s*([A-Za-z_]\w*)\s*\)", code))
    if not bases: return None, "no Entity-cast base"
    rx = re.compile(r"\(\s*\(\s*((?:struct\s+)?\w+)\s*\*\s*\)\s*(%s)\s*\)\s*->\s*(\w+)" % "|".join(sorted(map(re.escape, bases))))
    out = []; last = 0; n = 0; used_views = set()
    spans = code_spans(text)
    for m in rx.finditer(text):
        if not any(a <= m.start() < b for a, b in spans): continue
        v = views.get(m.group(1))
        if v is None or m.group(1) == "EntityRec": continue
        mm = v[0].get(m.group(3))
        if mm is None or mm[4] or mm[5]: continue
        o, sz, sg, cty = mm[:4]
        key = "pv" if cty.endswith("*") else KEY_OF.get(cty)
        if key is None: continue
        base = "((EntityRec *)%s)" % m.group(2)
        try: rep = _emit(text, m.start(), m.end(), base, o, key, tab, notes)
        except ValueError: continue
        out.append(text[last:m.start()]); out.append(rep); last = m.end(); n += 1; used_views.add(m.group(1))
    out.append(text[last:]); text = "".join(out)
    if not n: return None, "no co-cast view"
    for name in used_views:
        vv = parse_views(text).get(name)
        if vv and not name.startswith("struct ") and len(re.findall(r"\b%s\b" % name, "".join(text[a:b] for a, b in code_spans(text)))) == 1:
            text = text[:vv[1]] + text[vv[2]:].lstrip("\n"); notes.append("dropped " + name)
    return text, "%d view accesses; %s" % (n, ", ".join(dict.fromkeys(notes)))
