"""Rewrite a row's local D_ declarations of a consolidated object onto the shared readable symbol.
   spec: {sym: (new_name, new_elem_type, header)}.  Each local `extern T D_x[...]`/`extern T D_x;`
   is removed; uses are rewritten so every expression keeps the TYPE the old declaration gave it:
     same element type, array     -> new_name
     other element type, array    -> ((T *)new_name)          (a byte/u16 view of the table)
     scalar T                     -> (*(T *)new_name), &D_x -> ((T *)new_name)
   plain=True drops the view casts on u16/s16 arrays (the natural spelling; measured separately)."""
import re
DECL = r"^[ \t]*extern[ \t]+((?:(?:const|volatile|unsigned|signed|struct)[ \t]+)*[A-Za-z_][A-Za-z0-9_]*)[ \t]*(\*?)[ \t]*{sym}[ \t]*(\[[^\]]*\])?[ \t]*;[^\n]*\n"
STR = re.compile(r'"(?:[^"\\\n]|\\.)*"')
def sub_code(pat, repl, text):
    """re.sub outside string literals (asm strings keep the D_ spelling: it still links)."""
    out = []; last = 0
    for m in STR.finditer(text):
        out.append(re.sub(pat, repl, text[last:m.start()])); out.append(m.group(0)); last = m.end()
    out.append(re.sub(pat, repl, text[last:])); return "".join(out)
def rewrite(text, spec, plain=False):
    notes = []; headers = []
    for sym, (new, etype, header) in spec.items():
        rx = re.compile(DECL.format(sym=sym), re.M)
        decls = list(rx.finditer(text))
        if not decls:
            if re.search(r"\b%s\b" % sym, text): return None, "no local declaration of %s" % sym
            continue
        typ, star, arr = decls[0].group(1), decls[0].group(2), decls[0].group(3)
        if len({(d.group(1), d.group(2), d.group(3)) for d in decls}) > 1: return None, "conflicting local declarations"
        text = rx.sub("", text)
        if star: return None, "%s declared as a pointer (%s *)" % (sym, typ)
        if arr is not None:
            if typ == etype or (plain and typ in ("s16", "u16", "short", "unsigned short")):
                text = sub_code(r"&\s*%s\b(?!\s*\[)" % sym, "&" + new, text)
                text = sub_code(r"\b%s\b" % sym, new, text); notes.append("%s %s[]: plain" % (sym, typ))
            else:
                text = sub_code(r"&\s*%s\b(?!\s*\[)" % sym, "((%s *)%s)" % (typ, new), text)
                text = sub_code(r"\b%s\b" % sym, "((%s *)%s)" % (typ, new), text); notes.append("%s %s[]: view cast" % (sym, typ))
        else:
            text = sub_code(r"&\s*%s\b" % sym, "((%s *)%s)" % (typ, new), text)
            text = sub_code(r"\b%s\b" % sym, "(*(%s *)%s)" % (typ, new), text); notes.append("%s %s scalar: view cast" % (sym, typ))
        if header not in headers: headers.append(header)
    for h in headers:
        inc = '#include "%s"\n' % h
        m = re.search(r'^#include "common.h"[^\n]*\n', text, re.M)
        pos = m.end() if m else 0
        text = text[:pos] + inc + text[pos:]
    return text, "; ".join(notes)

# ------------------------------------------------------------------ target 2: the 0x80083460 block
BLK_BASE = 0x80083460
import os
BLK_FIELDS = [(0x00, "unk_00", "s16"), (0x02, "flags", "u16"), (0x04, "unk_04", "s16"), (0x06, "unk_06", "s16"),
              (0x08, "unk_08", "s16"), (0x0A, "unk_0A", os.environ.get("F0A", "s16")), (0x0C, "unk_0C", "void*"), (0x10, "unk_10", "void*"),
              (0x14, "unk_14", "s16"), (0x16, "unk_16", "s16"), (0x18, "unk_18", "u8*"), (0x1C, "unk_1C", "s16"), (0x1E, "unk_1E", "u16")]
CANON = {"short": "s16", "signed short": "s16", "unsigned short": "u16", "int": "s32", "long": "s32", "unsigned int": "u32",
         "unsigned char": "u8", "char": "s8", "signed char": "s8"}
BLK_DECL = re.compile(r"^[ \t]*extern[ \t]+((?:(?:const|volatile|unsigned|signed|struct)[ \t]+)*[A-Za-z_][A-Za-z0-9_]*)[ \t]*(\*?)[ \t]*(D_800834[67][0-9A-F])[ \t]*(\[[^\]]*\])?[ \t]*;[^\n]*\n", re.M)
def rewrite_blk(text, header="shared/dungeon_status.h", var="dungeonStatus", loose=False):
    """view mode: every expression keeps the type its old declaration gave it; a declaration whose type
    equals the field's becomes the plain field (`dungeonStatus.flags`)."""
    notes = []
    decls = list(BLK_DECL.finditer(text))
    if not decls: return None, "no local declaration in the block"
    seen = {}
    for d in decls:
        k = (d.group(1), d.group(2), d.group(4))
        if d.group(3) in seen and seen[d.group(3)] != k: return None, "conflicting local declarations of " + d.group(3)
        seen[d.group(3)] = k
    for sym in re.findall(r"\bD_800834[67][0-9A-F]\b", STR.sub("", text)):
        if sym not in seen: return None, "no local declaration of " + sym
    text = BLK_DECL.sub("", text)
    for sym, (typ, star, arr) in seen.items():
        off = int(sym[2:], 16) - BLK_BASE
        f = [x for x in BLK_FIELDS if x[0] == off]
        t = CANON.get(typ, typ) + ("*" if star else "")
        if off == 0:
            lv, fty = var, "DungeonGlobalStatus"
        elif f:
            lv, fty = "%s.%s" % (var, f[0][1]), f[0][2]
        else:
            return None, "%s is not at a field boundary" % sym
        ptr = " *" if star else ""
        if arr is None and (t == fty or (star and fty.endswith("*")) or (loose and fty == "void*" and t in ("s32", "u32")) or (loose and fty in ("s16", "u16") and t in ("s16", "u16"))):
            text = sub_code(r"\b%s\b" % sym, lv, text); notes.append("%s %s%s: plain field" % (sym, typ, ptr))
        elif arr is not None:
            text = sub_code(r"&\s*%s\b(?!\s*\[)" % sym, "((%s%s *)&%s)" % (typ, ptr, lv), text)
            text = sub_code(r"\b%s\b" % sym, "((%s%s *)&%s)" % (typ, ptr, lv), text); notes.append("%s %s%s[]: view cast" % (sym, typ, ptr))
        else:
            text = sub_code(r"&\s*%s\b" % sym, "((%s%s *)&%s)" % (typ, ptr, lv), text)
            text = sub_code(r"\b%s\b" % sym, "(*(%s%s *)&%s)" % (typ, ptr, lv), text); notes.append("%s %s%s: view cast" % (sym, typ, ptr))
    inc = '#include "%s"\n' % header
    m = re.search(r'^#include "common.h"[^\n]*\n', text, re.M)
    pos = m.end() if m else 0
    return text[:pos] + inc + text[pos:], "; ".join(notes)
