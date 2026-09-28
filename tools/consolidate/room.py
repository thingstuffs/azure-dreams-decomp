"""room.py - rewrite a row's local D_800E2970 declaration/views onto shared/dungeon_floor.h's DungeonRoom array.
   rewrite(text) -> (text, notes) | (None, reason).  Semantics-preserving by construction: element accesses through
   a 0x14-byte view become `D_800E2970[i].field` (a cast at the use where the view's width/sign differs from the
   field), every other use keeps the old element type through a cast `((T *)D_800E2970)`."""
import re, sys
from pathlib import Path
sys.path.insert(0, str(Path(__file__).parent))
import consolidate as C
SYM = "D_800E2970"; HDR = '#include "shared/dungeon_floor.h"'
FIELDS = [(0, "x", 2, False, "unsigned short"), (2, "y", 2, False, "unsigned short"), (4, "w", 2, True, "short"),
          (6, "h", 2, True, "short"), (8, "unk_08", 2, True, "short"), (0xA, "unk_0A", 2, True, "short"),
          (0xC, "flags", 2, False, "unsigned short"), (0xE, "unk_0E", 2, True, "short"), (0x10, "unk_10", 4, True, "int")]
BY = {f[0]: f for f in FIELDS}; RSIZE = 0x14

def close(s, i, o="[", c="]"):
    d = 0
    for j in range(i, len(s)):
        if s[j] == o: d += 1
        elif s[j] == c:
            d -= 1
            if d == 0: return j
    return -1

def member_expr(views, V, m, idx):
    mem = views[V][0].get(m)
    if mem is None: return None
    off, sz, sg, cty, cnt, sub = mem
    if cnt or sub or "*" in cty: return None
    f = BY.get(off)
    if f is None: return None
    base = "%s[%s].%s" % (SYM, idx, f[1])
    if f[2] == sz and f[3] == sg: return base
    return "(*(%s *)&%s)" % (cty, base)

def rewrite(text):
    decls = list(re.finditer(r"^[ \t]*extern\s+([^;]*?)\b%s\b\s*(\[[^\]]*\])?\s*;[^\n]*\n" % SYM, text, re.M))
    if not decls: return None, "no local declaration"
    if len({(d.group(1).strip(), d.group(2)) for d in decls}) > 1: return None, "differing local declarations"
    if "__asm__(\"%s\")" % SYM in text: return None, "asm alias"
    T = C.ctype_of(decls[0].group(1)); arr = decls[0].group(2) is not None
    for d in reversed(decls): text = text[:d.start()] + text[d.end():]
    views = C.parse_views(text)
    refd = lambda t, n: bool(re.search(r"\b%s\b" % re.escape(n), "".join(t[x:y] for x, y in C.code_spans(t))))
    before_refs = {V for V, (mem, a, b, size, al) in parse_local(text).items() if refd(text[:a] + text[b:], V.split()[-1])}
    notes = []
    out = []; i = 0
    rx = re.compile(r"\(\(\s*(\w+(?:\s+\w+)?)\s*\*\s*\)\s*&?\s*%s\s*\)\s*\[|\b%s\b" % (SYM, SYM))
    code = C.code_spans(text)
    incode = lambda p: any(a <= p < b for a, b in code)
    while True:
        m = rx.search(text, i)
        if not m: out.append(text[i:]); break
        out.append(text[i:m.start()])
        if not incode(m.start()): out.append(m.group(0)); i = m.end(); continue
        if m.group(1):          # ((V *)D_800E2970)[idx].m
            V = m.group(1); j = close(text, m.end() - 1); idx = text[m.end():j]
            mm = re.match(r"\s*\.\s*(\w+)", text[j + 1:])
            if V in views and views[V][3] == RSIZE and mm:
                e = member_expr(views, V, mm.group(1), idx)
                if e: out.append(e); i = j + 1 + mm.end(); notes.append("cast-view %s.%s" % (V, mm.group(1))); continue
            out.append(m.group(0)); i = m.end(); continue   # (V *)D_800E2970 cast kept: pointer value unchanged
        # bare D_800E2970
        after = text[m.end():]
        before = text[:m.start()].rstrip()
        if T in views and arr and views[T][3] == RSIZE:
            if after.lstrip().startswith("["):
                k = m.end() + (len(after) - len(after.lstrip())); j = close(text, k); idx = text[k + 1:j]
                mm = re.match(r"\s*\.\s*(\w+)", text[j + 1:])
                if mm:
                    e = member_expr(views, T, mm.group(1), idx)
                    if e: out.append(e); i = j + 1 + mm.end(); notes.append("view %s.%s" % (T, mm.group(1))); continue
                    return None, "member %s.%s has no matching field" % (T, mm.group(1))
            out.append(SYM); i = m.end(); continue        # same element size: &D[i], D decays to the same address
        if before.endswith("&") and not before.endswith("&&"):
            # &D_800E2970 -> the old pointer type
            out[-1] = out[-1].rstrip()[:-1]
            if after.lstrip()[:1] in (";", ",", ")"):
                out.append(SYM); i = m.end(); notes.append("address value"); continue
            out.append("((%s *)%s)" % (T, SYM)); i = m.end(); notes.append("addr as %s *" % T); continue
        nxt = after.lstrip()[:1]; prv = before[-1:]
        if arr and nxt in (";", ",", ")") and (prv in ("=", "(", ",") or re.search(r"\(\s*[\w ]+\*\s*\)$", before)) and not before.endswith("=="):
            out.append(SYM); i = m.end(); notes.append("pointer value"); continue   # value only: same address, no arithmetic
        if arr: out.append("((%s *)%s)" % (T, SYM))
        else: out.append("(*(%s *)%s)" % (T, SYM))
        i = m.end(); notes.append("kept as %s%s" % (T, "[]" if arr else ""))
    text = "".join(out)
    # drop view typedefs nothing references any more
    for V, (mem, a, b, size, al) in sorted(parse_local(text).items(), key=lambda x: -x[1][1]):
        name = V.split()[-1]
        e = re.match(r"[ \t]*(/\*[^\n]*?\*/)?[ \t]*\n", text[b:]); b2 = b + (e.end() if e else 0)
        rest = text[:a] + text[b2:]
        if V in before_refs and not refd(rest, name):
            text = rest; notes.append("dropped view %s" % V)
    if HDR not in text:
        m = re.search(r'^#include "common.h"[^\n]*\n', text, re.M)
        if not m: return None, "no common.h include"
        text = text[:m.end()] + HDR + "\n" + text[m.end():]
    return text, "; ".join(dict.fromkeys(notes)) or "decl only"

def parse_local(text):
    v = C.parse_views(text)
    return {k: x for k, x in v.items() if not k.startswith("struct ") or k.split()[-1] not in v}
