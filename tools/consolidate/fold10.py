"""fold10.py: fold local m2c views onto the shared types (r78 phase 10).
   A. local pointers: `V *p = (V *)((u8 *)&gameWork + 476);` / `u8 *p = (u8 *)&gameWork.view;` / `void *p = D_800814A8;`
      whose EVERY assignment resolves to one shared sub-object (object + offset, or any EntityRec for the pointer
      globals) -> `S *p = &obj.path;` (S = the shared type at that offset) and every view access through p
      (`((V *)p)->m.u`, `p->m` for a view-typed p, `*(T *)((u8 *)p + k)`, `((T *)p)[k]`, `p[k]`, `*p`) -> `p->field`.
   B. direct casts: `((V *)&obj)->m`, `((V *)(&obj.path))->m`, `((V *)D_800814A8)->m` -> `obj.field` / `D_800814A8->field`.
   A field is used only where one starts at the exact offset with the exact size; sign / pointer disagreement keeps a
   cast at the use (rvalue) or a view (compound lvalue).  Anything else refuses the row (reason recorded: `pad 0x..`
   = the view reaches bytes the shared header does not name yet).  Unused local views are dropped afterwards.
   fold(text) -> (new_text | None, notes, refusals)"""
import re, sys
from pathlib import Path
sys.path.insert(0, str(Path(__file__).parent))
import views10 as V10
import shtypes as ST
from consolidate import code_spans, _bodies
NUM = r"(?:0x[0-9A-Fa-f]+|\d+)"
AGG = {"gameWork": "GameWork", "dungeonStatus": "DungeonGlobalStatus", "D_80082E80": "TileObject", "D_80083780": "EntityRec",
       "objectFlagBlock": "ObjectFlagBlock", "D_80083498": "ObjectNodeHeader"}
PTRG = {"D_800814A8": "EntityRec", "D_800E3D7C": "EntityRec"}
HDR = {"GameWork": "shared/game_work.h", "GameView": "shared/game_work.h", "ViewSlot": "shared/game_work.h", "MapGrid": "shared/game_work.h",
       "DungeonGlobalStatus": "shared/dungeon_status.h", "TileObject": "shared/tile_object.h", "EntityRec": "shared/entity.h",
       "ObjectFlagBlock": "shared/object_flags.h", "ObjectNodeHeader": "shared/object_node.h"}
OBJHDR = {"D_80083780": "shared/entity_objects.h", "D_800814A8": "shared/record_ptrs.h", "D_800E3D7C": "shared/record_ptrs.h"}
CASTRX = r"\(\s*(?:const\s+)?(?:struct\s+|union\s+)?(?:unsigned\s+|signed\s+)?\w+(?:\s+int)?\s*\*+\s*\)"

class Refuse(Exception): pass

def _unparen(e):
    e = e.strip()
    while e.startswith("(") and e.endswith(")"):
        d = 0; ok = True
        for i, ch in enumerate(e):
            if ch == "(": d += 1
            elif ch == ")":
                d -= 1
                if d == 0 and i != len(e) - 1: ok = False; break
        if not ok: break
        e = e[1:-1].strip()
    return e

def resolve(expr):
    """-> (key, T, off, canon) : key identifies the object ('gameWork' / 'EntityRec*'), T the shared type AT off
       (the sub-object the pointer addresses), canon the clean spelling of that address.  None if not an object address."""
    e = _unparen(expr)
    m = re.fullmatch(r"\(\s*(?:u8|s8|char|unsigned char|signed char)\s*\*\s*\)\s*(.+?)\s*([+-])\s*(%s)" % NUM, e, re.S)
    if m:
        r = resolve(m.group(1))
        if r is None or r[0].endswith("*"): return None
        k = int(m.group(3), 0) * (1 if m.group(2) == "+" else -1)
        return _sub(r[0], r[2] + k)
    m = re.match(CASTRX, e)
    if m: return resolve(e[m.end():])
    m = re.fullmatch(r"&\s*\(?\s*(\w+)\s*\)?((?:\s*\.\s*\w+|\s*\[\s*%s\s*\])*)" % NUM, e)
    if m and m.group(1) in AGG:
        path = re.sub(r"\s+", "", m.group(2)).lstrip(".")
        po = ST.path_off(AGG[m.group(1)], path)
        if po is None: return None
        return _sub(m.group(1), po[0])
    if e in PTRG: return ("EntityRec*", PTRG[e], 0, e)
    return None

def _sub(key, off):
    T = AGG[key]
    if off == 0: return (key, T, 0, "&" + key)
    for o, ty, p in ST.structs_at(T):
        if o == off: return (key, ty, off, "&%s.%s" % (key, p))
    return (key, None, off, None)

# ---------------------------------------------------------------- emission
def _lv(s, st, en):
    return re.match(r"\s*(=(?!=)|[-+*/%&|^]=|<<=|>>=|\+\+|--)", s[en:]) is not None or re.search(r"(\+\+|--)\s*$", s[:st]) is not None

def _cty(size, signed, ptr, cty):
    if ptr: return cty or "void *"
    return {(1, True): "s8", (1, False): "u8", (2, True): "s16", (2, False): "u16", (4, True): "s32", (4, False): "u32"}[(size, signed)]

def emit(prefix, T, off, size, signed, ptr, cty, s, st, en, addr, notes, whole_sub=False):
    L = ST.leaves(T)
    if whole_sub:
        raise Refuse("union/struct member used whole at 0x%X" % off)
    c = [l for l in L if l[0] == off and l[1] == size]
    if not c:
        cover = [l for l in L if l[0] <= off < l[0] + l[1]]
        if cover: raise Refuse("0x%X size %d inside %s.%s" % (off, size, T, cover[0][4]))
        raise Refuse("pad %s 0x%X size %d" % (T, off, size))
    best = [l for l in c if l[3] == ptr and (ptr or l[2] == signed)] or [l for l in c if l[3] == ptr] or c
    f = best[0]; fexpr = prefix + f[4]
    same = f[3] == ptr and (ptr or f[2] == signed)
    vty = _cty(size, signed, ptr, cty)
    if ptr and f[3] and cty and re.sub(r"\s", "", cty) not in ("void*", re.sub(r"\s", "", f[5])): same = False
    if addr:
        notes.append("&" + f[4])
        return ("&" + fexpr) if same else "((%s *)&%s)" % (vty, fexpr)
    lv = _lv(s, st, en)
    if same: notes.append(f[4]); return fexpr
    if lv:
        if re.match(r"\s*=(?!=)", s[en:]): notes.append(f[4]); return fexpr
        notes.append("view " + f[4]); return "(*(%s *)&%s)" % (vty, fexpr)
    notes.append("(%s)%s" % (vty, f[4])); return "((%s)%s)" % (vty, fexpr)

CHAIN = r"((?:\s*(?:\.|->)\s*\w+|\s*\[\s*[^\]\[]*\])*)"
def _chain(txt):
    return re.findall(r"\.\s*\w+|->\s*\w+|\[[^\]]*\]", txt)

def _vleaf(views, vname, chain):
    vn = re.sub(r"\b(struct|union)\s+", "", vname).strip()
    if vn in ST.S:          # a cast to the shared type itself
        return ("shared", vn, chain)
    v = views.get(vname) or views.get(vn) or views.get("struct " + vn)
    if v is None: raise Refuse("view %s unknown" % vn)
    c = [x.replace(" ", "") for x in chain]
    if not c or not c[0].startswith("->"): raise Refuse("view %s not dereferenced" % vn)
    return V10.leaf(v, [c[0][2:]] + c[1:])

def _shared_leaf(T, chain):
    """a shared-type member chain -> (off, size, signed, ptr, cty, whole)"""
    path = "".join(chain).replace(" ", "")[2:]
    for o, sz, sg, ptr, p, ty in ST.leaves(T):
        if p == path: return (o, sz, sg, ptr, ty, False)
    po = ST.path_off(T, path)
    if po: return (po[0], ST.size_of(po[1]), False, False, None, True)
    raise Refuse("%s.%s unknown" % (T, path))

def fold_access(new, pat, prefix_of, views, notes, T_of):
    """replace every `pat` match (group 'cast' = view name, group 'ch' = member chain) by the shared field."""
    out = []; last = 0; spans = code_spans(new)
    for m in re.finditer(pat, new):
        if not any(a <= m.start() < b for a, b in spans): continue
        ch = _chain(m.group("ch"))
        if not ch: continue
        base_off, T, prefix = prefix_of(m)
        lf = _vleaf(views, m.group("cast"), ch)
        if lf[0] == "shared":
            if lf[1] == T and base_off == 0:
                rep = prefix + "".join(x.replace(" ", "") for x in ch)[2:]; notes.append("cast")
                out.append(new[last:m.start()]); out.append(("&" if m.group("amp") else "") + rep); last = m.end(); continue
            lf = _shared_leaf(lf[1], ch)
        off, size, sg, ptr, cty, whole = lf
        rep = emit(prefix, T, base_off + off, size, sg, ptr, cty, new, m.start(), m.end(), bool(m.group("amp")), notes, whole)
        out.append(new[last:m.start()]); out.append(rep); last = m.end()
    out.append(new[last:]); return "".join(out)

# ---------------------------------------------------------------- A. local pointers
def _decl(body, p):
    rx = re.compile(r"^([ \t]*)((?:register\s+)?(?:const\s+)?(?:struct\s+|union\s+)?(?:unsigned\s+|signed\s+)?\w+)\s*\*\s*(%s)\b(\s*ASM_REG\([^)]*\))?\s*(=\s*[^;]+)?;" % p, re.M)
    return list(rx.finditer(body))

def fold_pointers(text, views, notes, refusals):
    changed = False
    for bs, be in reversed(_bodies(text)):
        body = text[bs:be]
        cands = {}
        for m in re.finditer(r"(?<![\w.>])([A-Za-z_]\w*)\s*=(?!=)\s*([^;]+);", body):
            r = resolve(m.group(2))
            if r is not None: cands.setdefault(m.group(1), []).append(r)
        for p, rs in cands.items():
            try:
                keys = {(r[0], r[2]) for r in rs} if rs[0][0] != "EntityRec*" else {("EntityRec*", 0)}
                if len({(r[0] if r[0] != "EntityRec*" and r[1] != "EntityRec" else "E", r[2]) for r in rs}) != 1:
                    raise Refuse("%s: several objects/offsets" % p)
                r0 = rs[0]; T = r0[1]
                if T is None: raise Refuse("%s: no shared sub-object at %s+0x%X" % (p, r0[0], r0[2]))
                dm = _decl(body, p)
                if not dm: raise Refuse("%s: declaration not found" % p)
                d = dm[0]
                olds = {re.sub(r"\b(register|const|struct|union)\s+", "", x.group(2)).strip() for x in dm}
                old = olds.pop() if len(olds) == 1 else "void"      # several arms (NON_MATCHING lockstep) with different types
                code = "".join(body[a:b] for a, b in code_spans(body))
                if re.search(r"&\s*%s\b(?!\s*(->|\[|\.))" % p, code): raise Refuse("%s: address taken" % p)
                if re.search(r"(?<![\w.>])%s\s*(\+\+|--|\+=|-=)|(\+\+|--)\s*%s\b" % (p, p), code): raise Refuse("%s: stepped" % p)
                for m in re.finditer(r"(?<![\w.>=!<>])%s\s*=(?!=)\s*([^;]+);" % p, body):
                    if resolve(m.group(1)) is None: raise Refuse("%s: also assigned %s" % (p, m.group(1).strip()[:40]))
                if d.group(5) and resolve(d.group(5).lstrip("= ")) is None: raise Refuse("%s: initialised to something else" % p)
                new = body; loc = []
                # declaration
                def mkdecl(d):
                    reg = "register " if d.group(2).lstrip().startswith("register") else ""
                    init = ""
                    if d.group(5):
                        rr = resolve(d.group(5).lstrip("= ")); init = " = " + (rr[3] if rr[0] != "EntityRec*" else d.group(5).lstrip("= ").strip())
                        if rr[0] == "EntityRec*": init = " = " + _unparen(re.sub(r"^\s*" + CASTRX, "", d.group(5).lstrip("= ").strip()))
                    return "%s%s%s *%s%s%s;" % (d.group(1), reg, T, p, d.group(4) or "", init)
                for x in reversed(dm): new = new[:x.start()] + mkdecl(x) + new[x.end():]
                # assignments
                def afix(m):
                    rr = resolve(m.group(2))
                    if rr is None: return m.group(0)
                    rhs = rr[3] if rr[0] != "EntityRec*" else _unparen(re.sub(r"^\s*" + CASTRX, "", _unparen(m.group(2))))
                    return "%s = %s;" % (m.group(1), rhs)
                new = re.sub(r"(?<![\w.>=!<>])(%s)\s*=(?!=)\s*([^;]+);" % p, afix, new)
                pv = views.get(old) if old not in V10.PRIM and old != "void" else None
                psize = V10.PRIM.get(old, (1,))[0] if old in V10.PRIM else (1 if old == "void" else None)
                # 1. ((V *)p)->chain
                new = fold_access(new, r"(?P<amp>&\s*)?\(\s*\(\s*(?P<cast>(?:struct\s+|union\s+)?\w+)\s*\*\s*\)\s*\(?\s*%s\s*\)?\s*\)(?P<ch>%s)" % (p, CHAIN),
                                  lambda m: (0, T, p + "->"), views, loc, None)
                # 2. p->chain for a view-typed p
                if pv is not None:
                    def pvsub(m):
                        ch = _chain(m.group(2)); lf = V10.leaf(pv, [ch[0].replace(" ", "")[2:]] + [x.replace(" ", "") for x in ch[1:]])
                        return emit(p + "->", T, lf[0], lf[1], lf[2], lf[3], lf[4], m.string, m.start(), m.end(), bool(m.group(1)), loc, lf[5])
                    spans = code_spans(new)
                    new = re.sub(r"(&\s*)?(?<![\w.>])%s((?:\s*->\s*\w+)(?:\s*(?:\.)\s*\w+|\s*\[\s*%s\s*\])*)" % (p, NUM),
                                 lambda m: pvsub(m) if any(a <= m.start() < b for a, b in spans) else m.group(0), new)
                elif old in ST.S:
                    pass
                # 3. *(T *)((u8 *)p + k) / *(T *)(p + k) / *(T *)p
                def arith(m):
                    ty = re.sub(r"\s+", " ", m.group(1)).strip(); star = ty.endswith("*")
                    base = ty.rstrip("* ").strip()
                    if star: size, sg, ptr, cty = 4, False, True, ty
                    elif base in V10.PRIM: (size, sg), ptr, cty = V10.PRIM[base], False, None
                    else: raise Refuse("arith type " + ty)
                    inner = _unparen(m.group(2) or p)
                    mm = re.fullmatch(r"(\(\s*(?:u8|s8|char|unsigned char)\s*\*\s*\)\s*)?\(?\s*%s\s*\)?(?:\s*([+-])\s*(%s))?" % (p, NUM), inner)
                    if not mm: raise Refuse("arith " + inner[:40])
                    k = int(mm.group(3), 0) if mm.group(3) else 0
                    if mm.group(2) == "-": k = -k
                    if k and not mm.group(1) and psize != 1: raise Refuse("arith scale")
                    return emit(p + "->", T, k, size, sg, ptr, cty, m.string, m.start(), m.end(), False, loc)
                spans = code_spans(new)
                new = re.sub(r"\*\s*\(\s*((?:unsigned |signed )?\w+(?: int)?\s*\**)\s*\*\s*\)\s*(\((?:[^()]|\([^()]*\))*\)|%s\b)" % p,
                             lambda m: arith(m) if any(a <= m.start() < b for a, b in spans) and re.search(r"\b%s\b" % p, m.group(2)) else m.group(0), new)
                # 4. ((T *)p)[k]
                def tidx(m):
                    ty = re.sub(r"\s+", " ", m.group(2)).strip()
                    if ty not in V10.PRIM: raise Refuse("index type " + ty)
                    size, sg = V10.PRIM[ty]
                    return emit(p + "->", T, int(m.group(3), 0) * size, size, sg, False, None, m.string, m.start(), m.end(), bool(m.group(1)), loc)
                new = re.sub(r"(&\s*)?\(\s*\(\s*((?:unsigned |signed )?\w+)\s*\*\s*\)\s*%s\s*\)\s*\[\s*(%s)\s*\]" % (p, NUM), tidx, new)
                # 5. p[k] / *p for a primitive-typed p
                if old in V10.PRIM:
                    size, sg = V10.PRIM[old]
                    new = re.sub(r"(&\s*)?(?<![\w.>])%s\s*\[\s*(%s)\s*\]" % (p, NUM),
                                 lambda m: emit(p + "->", T, int(m.group(2), 0) * size, size, sg, False, None, m.string, m.start(), m.end(), bool(m.group(1)), loc), new)
                    def dref(m):
                        before = m.string[:m.start()].rstrip()
                        if before and (before[-1].isalnum() or before[-1] in "_)]"): return m.group(0)
                        return emit(p + "->", T, 0, size, sg, False, None, m.string, m.start(), m.end(), False, loc)
                    new = re.sub(r"\*\s*%s\b(?!\s*[\[+-])" % p, dref, new)
                # leftovers that depend on p's own type
                code = "".join(new[a:b] for a, b in code_spans(new))
                code = re.sub(r"\b%s\s*=(?!=)[^;]*;" % p, "", code)
                if re.search(r"(?<![\w.>])%s\s*(\[|[+-](?![>=]))" % p, code) or re.search(r"[+-]\s*%s\b(?!\s*->)" % p, code): raise Refuse("%s: pointer arithmetic left" % p)
                c2 = re.sub(r"\(\s*[\w ]+\*+\s*\)", "", code)
                for mm in re.finditer(r"\*\s*%s\b(?!\s*->)" % p, c2):
                    b4 = c2[:mm.start()].rstrip()
                    if old in V10.PRIM and not (b4 and (b4[-1].isalnum() or b4[-1] in "_)]")): raise Refuse("%s: deref left" % p)
                ocode = "".join(body[a:b] for a, b in code_spans(body))
                if pv is None and old not in ST.S and re.search(r"(?<![\w.>])%s\s*->" % p, ocode):
                    raise Refuse("%s: -> through a non-view pointer" % p)
                if not loc and not re.search(r"\(\s*\(\s*\w+\s*\*\s*\)\s*%s\s*\)" % p, body): raise Refuse("%s: nothing folded" % p)
                body = new; changed = True; notes.append("%s:%s{%s}" % (p, T, ",".join(dict.fromkeys(loc))))
            except (Refuse, ValueError) as e:
                refusals.append(str(e))
        text = text[:bs] + body + text[be:]
    return text, changed

# ---------------------------------------------------------------- B. direct casts on an object
def fold_direct(text, views, notes, refusals):
    objs = "|".join(list(AGG) + list(PTRG))
    pat = r"(?P<amp>&\s*)?\(\s*\(\s*(?P<cast>(?:struct\s+|union\s+)?\w+)\s*\*\s*\)\s*(?P<e>\(?\s*&?\s*\(?\s*(?:%s)\b(?:\s*\.\s*\w+|\s*\[\s*%s\s*\])*\s*\)?\s*\)?)\s*\)(?P<ch>%s)" % (objs, NUM, CHAIN)
    def prefix_of(m):
        r = resolve(m.group("e"))
        if r is None: raise Refuse("direct: %s" % m.group("e")[:40])
        if r[0] == "EntityRec*": return (0, "EntityRec", _unparen(m.group("e")) + "->")
        return (r[2], AGG[r[0]], r[0] + ".")
    try:
        new = fold_access(text, pat, prefix_of, views, notes, None)
    except (Refuse, ValueError) as e:
        refusals.append("direct: " + str(e)); return text, False
    return new, new != text

# ---------------------------------------------------------------- tidy + includes
def tidy(text, notes):
    for _ in range(8):
        vs = V10.parse(text); hit = False
        for name, v in sorted(vs.items(), key=lambda kv: -kv[1]["span"][0] if "span" in kv[1] else 0):
            if "span" not in v or name.startswith(("struct ", "union ")): continue
            a, b = v["span"]
            rest = text[:a] + text[b:]
            code = "".join(rest[x:y] for x, y in code_spans(rest))
            tag = re.match(r"typedef\s+(?:struct|union)\s*(\w*)", text[a:b])
            names = {name} | ({tag.group(1)} if tag and tag.group(1) else set())
            if any(re.search(r"\b%s\b" % re.escape(n), code) for n in names): continue
            # the line's trailing comment goes too
            e = b; mm = re.match(r"[ \t]*/\*[^\n]*?\*/[ \t]*\n|[ \t]*\n", text[b:])
            if mm: e = b + mm.end()
            if text[e:e + 1] == "\n" and (a == 0 or text[a - 2:a] == "\n\n"): e += 1     # the blank line after it
            text = text[:a] + text[e:]; notes.append("drop " + name); hit = True; break
        if not hit:
            for m in re.finditer(r"^struct (\w+);\s*typedef struct \1 \1;[ \t]*\n", text, re.M):
                rest = text[:m.start()] + text[m.end():]
                code = "".join(rest[x:y] for x, y in code_spans(rest))
                if not re.search(r"\b%s\b" % m.group(1), code):
                    text = rest; notes.append("drop fwd " + m.group(1)); hit = True; break
        if not hit: break
    return text

def add_inc(text, hdr):
    line = '#include "%s"\n' % hdr
    if line in text: return text
    incs = list(re.finditer(r'^#include "[^"]+"[^\n]*\n', text, re.M))
    if not incs: return line + text
    i = incs[-1].end() if not any('"common.h"' in x.group(0) for x in incs) else next(x.end() for x in incs if '"common.h"' in x.group(0))
    # after the last shared/ include that follows common.h, else right after common.h
    sh = [x for x in incs if x.start() >= i and '"shared/' in x.group(0)]
    if sh: i = sh[-1].end()
    return text[:i] + line + text[i:]

def fold(text):
    views = V10.parse(text); notes = []; refusals = []
    t1, a = fold_pointers(text, views, notes, refusals)
    t2, b = fold_direct(t1, V10.parse(t1), notes, refusals)
    if not (a or b): return None, notes, refusals
    for T in re.findall(r"\b(GameWork|GameView|ViewSlot|MapGrid|DungeonGlobalStatus|TileObject|EntityRec|ObjectFlagBlock|ObjectNodeHeader)\s*\*", t2):
        t2 = add_inc(t2, HDR[T])
    for o, h in OBJHDR.items():
        if re.search(r"\b%s\b" % o, t2) and not re.search(r"^\s*extern[^;]*\b%s\b" % o, t2, re.M): t2 = add_inc(t2, h)
    if "D_80083780." in t2 or "D_800814A8->" in t2 or "D_800E3D7C->" in t2: t2 = add_inc(t2, "shared/entity.h")
    t2 = tidy(t2, notes)
    return t2, notes, refusals
