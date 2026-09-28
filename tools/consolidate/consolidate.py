"""consolidate.py - rewrite a row's address-named spellings of ONE global object onto its shared,
named declaration (the phase-2 generator; reusable for any object).

Object spec (objects/<name>.json):
  {"base": "0x80083460", "var": "dungeonStatus", "header": "shared/dungeon_status.h",
   "syms": "D_800834[67][0-9A-F]",            # every address-named symbol inside the object
   "fields": [[off, "name", "ctype", size, signed], ...]}     # ctype: s8 u8 s16 u16 s32 u32 ptr

For every local `extern T S[...]` / `extern T S;` / `extern T *S;` of a symbol S inside the object,
each USE of S becomes the field it addresses, computed as addr(S) - base + k*sizeof(T):
    S[k] (k a literal), S (scalar), S.member (a local view typedef, laid out here), &S..., ->
    `var.field`            same size; a read of a differently-signed view gets `(T)var.field`
    `var.field[k']`        field is an array of the same element size
    `*(T *)&var.field`     size mismatch (a union site: a wider or narrower read at a field)
    `((T *)&var.field)`    decayed array / non-literal index (the VIEW spelling - may miss the %hi form)
The local declarations are removed, a local view typedef nothing else uses is removed, and the header is
included after common.h.  Returns (text, notes) or (None, reason)."""
import json, re
TSIZE = {"s8": 1, "u8": 1, "char": 1, "signed char": 1, "unsigned char": 1, "s16": 2, "u16": 2, "short": 2,
         "unsigned short": 2, "signed short": 2, "s32": 4, "u32": 4, "int": 4, "unsigned int": 4, "long": 4,
         "unsigned long": 4, "M2C_UNK": 4, "unsigned": 4, "f32": 4}
SIGNED = {"s8", "char", "signed char", "s16", "short", "signed short", "s32", "int", "long", "M2C_UNK"}
STR = re.compile(r'"(?:[^"\\\n]|\\.)*"|/\*.*?\*/|//[^\n]*', re.S)
NUM = r"(0x[0-9A-Fa-f]+|\d+)"

def load(path):
    o = json.load(open(path)); o["base"] = int(o["base"], 16); return o

def code_spans(text):
    """[(start, end)] of the text outside strings and comments."""
    out, last = [], 0
    for m in STR.finditer(text):
        out.append((last, m.start())); last = m.end()
    out.append((last, len(text))); return out

def sub_code(pat, fn, text):
    rx = re.compile(pat); res, last = [], 0
    for a, b in code_spans(text):
        res.append(text[last:a]); res.append(rx.sub(fn, text[a:b])); last = b
    res.append(text[last:]); return "".join(res)

def ctype_of(t):
    t = re.sub(r"\b(const|volatile|extern|static)\b", "", t).strip()
    t = re.sub(r"\s+", " ", t)
    return t

def parse_views(text):
    """local `typedef struct [tag] { ... } Name;` -> {Name: {member: (off, size, signed, ctype, count)}}"""
    views = {}
    for m in re.finditer(r"typedef\s+struct\s*(\w*)\s*\{(.*?)\}\s*(\w+)\s*;", text, re.S):
        tag, body, name = m.group(1), m.group(2), m.group(3); off = 0; mem = {}; ok = True
        for d in re.sub(r"/\*.*?\*/|//[^\n]*", "", body, flags=re.S).split(";"):
            d = d.strip()
            if not d: continue
            mm = re.match(r"^((?:unsigned |signed )?\w+)\s*(\*?)\s*(\w+)\s*(?:\[\s*([^\]]+)\s*\])?$", d)
            if not mm: ok = False; break
            base, star, mname, cnt = mm.groups()
            try: n = eval(cnt, {}, {}) if cnt else 1
            except Exception: ok = False; break
            sz = 4 if star else TSIZE.get(base)
            if sz is None: ok = False; break
            off = (off + sz - 1) // sz * sz
            mem[mname] = (off, sz, base in SIGNED and not star, (base + " *") if star else base, n if cnt else None)
            off += sz * n
        if ok:
            views[name] = (mem, m.start(), m.end())
            if tag: views["struct " + tag] = (mem, m.start(), m.end())
    # plain `struct Tag { ... };` definitions are views too, keyed "struct Tag"
    for m in re.finditer(r"^struct\s+(\w+)\s*\{(.*?)\}\s*;", text, re.S | re.M):
        sub = parse_views("typedef struct {%s} %s;" % (m.group(2), m.group(1)))
        if m.group(1) in sub: views["struct " + m.group(1)] = (sub[m.group(1)][0], m.start(), m.end())
    return views

def field_at(obj, off, size):
    """(expr_suffix, field) for the object offset; exact field, or an element of an array field."""
    for f in obj["fields"]:
        foff, name, fty, fsz = f[0], f[1], f[2], f[3]
        cnt = f[5] if len(f) > 5 else None
        if cnt:
            esz = fsz // cnt
            if foff <= off < foff + fsz and (off - foff) % esz == 0 and esz == size:
                return "%s[%d]" % (name, (off - foff) // esz), f
        elif foff == off:
            return name, f
    return None, None

def lvalue_after(s, end):
    return re.match(r"\s*(=(?!=)|[-+*/%&|^]=|<<=|>>=|\+\+|--)", s[end:]) is not None
def lvalue_before(s, start):
    return re.search(r"(\+\+|--)\s*$", s[:start]) is not None

def emit_field(obj, base, sep, off, size, signed, cty, s, start, end, addr, notes):
    """the spelling of an access of `size` bytes at object offset `off` read as C type `cty`.
    base/sep: ("dungeonStatus", ".") for the object itself, ("p", "->") through a typed pointer."""
    whole = ("&" + base) if sep == "." else base
    fx, f = field_at(obj, off, size)
    lv = lvalue_after(s, end) or lvalue_before(s, start)
    if f is None:
        f2 = None
        for g in obj["fields"]:
            if g[0] <= off < g[0] + g[3]: f2 = g
        if f2 is None: raise ValueError("offset 0x%X outside every field" % off)
        at = whole if f2[1] == "" else "&%s%s%s" % (base, sep, f2[1])
        inner = "(u8 *)%s + %d" % (at, off - f2[0]) if off != f2[0] else at
        notes.append("0x%X:%s view (size %d at field %s)" % (off, cty, size, f2[1]))
        return ("((%s *)(%s))" % (cty, inner)) if addr else ("*(%s *)(%s)" % (cty, inner))
    fexpr = ("*" + base if sep == "->" else base) if fx == "" else "%s%s%s" % (base, sep, fx)
    same = (f[2] == "ptr" and cty.endswith("*")) or (f[2] != "ptr" and not cty.endswith("*") and (f[4] == signed))
    if addr:
        return ("&" + fexpr) if same else "((%s *)&%s)" % (cty, fexpr)
    if same:
        notes.append("0x%X:%s" % (off, fx)); return fexpr
    if lv:
        simple = re.match(r"\s*=(?!=)", s[end:]) is not None
        if (f[2] == "ptr") != cty.endswith("*") and not simple:
            notes.append("0x%X:*(%s *)&%s" % (off, cty, fx)); return "*(%s *)&%s" % (cty, fexpr)
        notes.append("0x%X:%s" % (off, fx)); return fexpr
    notes.append("0x%X:(%s)%s" % (off, cty, fx)); return "((%s)%s)" % (cty, fexpr)

def rewrite(text, obj):
    var = obj["var"]; notes = []; symrx = obj["syms"]
    DECL = re.compile(r"^[ \t]*extern[ \t]+((?:(?:const|volatile|unsigned|signed|struct)[ \t]+)*[A-Za-z_]\w*)[ \t]*(\*?)[ \t]*(%s)\b[ \t]*(\[[^\]]*\])?[ \t]*;[^\n]*\n" % symrx, re.M)
    decls = {}
    for d in DECL.finditer(text):
        k = (ctype_of(d.group(1)), d.group(2), d.group(4))
        if decls.get(d.group(3), k) != k: return None, "conflicting declarations of " + d.group(3)
        decls[d.group(3)] = k
    code = "".join(text[a:b] for a, b in code_spans(text))
    used = set(re.findall(r"\b(%s)\b" % symrx, code))
    if not used: return None, "object not referenced in code"
    if used - set(decls): return None, "no local declaration of " + ",".join(sorted(used - set(decls)))
    if re.search(r"__asm__[^;]*\b(%s)\b" % symrx, text): notes.append("asm string keeps its D_ spelling")
    text = DECL.sub("", text)
    views = parse_views(text)
    for sym, (ty, star, arr) in decls.items():
        off0 = int(sym[2:], 16) - obj["base"]
        esz = 4 if star else TSIZE.get(ty)
        esigned = (ty in SIGNED) and not star
        tyname = ty + (" *" if star else "")
        def emit(off, size, signed, cty, s, start, end, addr=False):
            return emit_field(obj, var, ".", off, size, signed, cty, s, start, end, addr, notes)
        # S.member / S->member through a local view typedef (only for a scalar struct-typed declaration)
        if ty in views and not star and arr is None:
            mem = views[ty][0]
            def mfix(m):
                mm = mem.get(m.group(3))
                if mm is None: raise ValueError("member %s not in view %s" % (m.group(3), ty))
                o, sz, sg, cty, cnt = mm
                if cnt: return "((%s *)((u8 *)&%s + %d))" % (cty, var, off0 + o)
                return emit(off0 + o, sz, sg, cty, m.string, m.start(), m.end(), addr=bool(m.group(1)))
            try:
                text = sub_code(r"(&\s*)?\b(%s)\s*\.\s*(\w+)\b" % sym, mfix, text)
            except ValueError as e:
                return None, str(e)
            text = sub_code(r"&\s*%s\b" % sym, lambda m: "((%s *)&%s)" % (ty, var) if off0 == 0 else "((%s *)((u8 *)&%s + %d))" % (ty, var, off0), text)
            if re.search(r"\b%s\b" % sym, "".join(text[a:b] for a, b in code_spans(text))):
                return None, "whole-view use of " + sym
            continue
        if esz is None:
            code_now = "".join(text[a:b] for a, b in code_spans(text))
            if not star and arr is None and off0 == 0 and len(re.findall(r"\b%s\b" % sym, code_now)) == len(re.findall(r"&\s*%s\b" % sym, code_now)):
                # an opaque (incomplete / foreign) view whose address is all the row takes
                text = sub_code(r"&\s*%s\b" % sym, "((%s *)&%s)" % (ty, var), text); notes.append("opaque view %s" % ty); continue
            return None, "unknown element type %s for %s" % (ty, sym)
        def ifix(m):
            k = int(m.group(3), 0)
            return emit(off0 + k * esz, esz, esigned, tyname, m.string, m.start(), m.end(), addr=bool(m.group(1)))
        try:
            if arr is not None or star == "":
                text = sub_code(r"(&\s*)?\b(%s)\s*\[\s*%s\s*\]" % (sym, NUM), ifix, text)
            if arr is not None:
                # `*S` on a decayed array is S[0] (not a multiplication: nothing value-like right before the *)
                def dfix(m):
                    before = m.string[:m.start()].rstrip()
                    if before and (before[-1].isalnum() or before[-1] in "_)]"): return m.group(0)
                    return emit(off0, esz, esigned, tyname, m.string, m.start(), m.end())
                text = sub_code(r"\*\s*\b%s\b(?!\s*\[)" % sym, dfix, text)
            if arr is None:
                text = sub_code(r"(&\s*)?\b(%s)\b(?!\s*\[)" % sym,
                                lambda m: emit(off0, esz, esigned, tyname, m.string, m.start(), m.end(), addr=bool(m.group(1))), text)
            else:
                # decayed array or a computed index: the view spelling
                fx, f = field_at(obj, off0, esz)
                at = "&%s" % var if off0 == 0 else ("&%s.%s" % (var, fx) if f else "(u8 *)&%s + %d" % (var, off0))
                if f is not None and f[1] == "": at = "&%s" % var
                def vfix(m):
                    notes.append("0x%X:view %s[]" % (off0, ty)); return "((%s *)(%s))" % (tyname, at)
                text = sub_code(r"&\s*\b%s\b(?!\s*\[)" % sym, vfix, text)
                text = sub_code(r"\b%s\b" % sym, vfix, text)
        except ValueError as e:
            return None, str(e)
    # drop local view typedefs nothing uses any more
    for name, (mem, a, b) in sorted(((k, v) for k, v in parse_views(text).items() if not k.startswith("struct ")), key=lambda x: -x[1][1]):
        if name in {d[0] for d in decls.values()} and len(re.findall(r"\b%s\b" % name, text)) == 1:
            text = text[:a] + text[b:].lstrip("\n")
            notes.append("dropped view typedef " + name)
    inc = '#include "%s"\n' % obj["header"]
    if inc not in text:
        m = re.search(r'^#include "common.h"[^\n]*\n', text, re.M)
        pos = m.end() if m else 0
        text = text[:pos] + inc + text[pos:]
    return text, "; ".join(dict.fromkeys(notes))

# ------------------------------------------------------------------ phase 3: m2c's local-pointer idiom
CAST = r"\(\s*(?:struct\s+)?[A-Za-z_]\w*(?:\s+[A-Za-z_]\w*)?\s*\*+\s*\)"
def _strip_casts(e):
    e = e.strip()
    while True:
        n = re.sub(r"^\(\s*(.*)\s*\)$", r"\1", e, flags=re.S).strip() if _balanced_outer(e) else e
        n = re.sub(r"^" + CAST + r"\s*", "", n).strip()
        if n == e: return e
        e = n
def _balanced_outer(e):
    if not (e.startswith("(") and e.endswith(")")): return False
    d = 0
    for i, ch in enumerate(e):
        d += ch == "("; d -= ch == ")"
        if d == 0 and i < len(e) - 1: return False
    return True
def _bodies(text):
    """(start, end) of each top-level {...} function body."""
    out, d, st = [], 0, None
    for a, b in code_spans(text):
        for i in range(a, b):
            ch = text[i]
            if ch == "{":
                if d == 0: st = i
                d += 1
            elif ch == "}":
                d -= 1
                if d == 0 and st is not None and re.search(r"\)\s*$", text[:st]): out.append((st, i + 1))
    return out
def _addr_off(obj, rhs):
    """object offset if rhs (casts stripped) is &var or &var.field, else None"""
    e = _strip_casts(rhs)
    m = re.fullmatch(r"&\s*\(?\s*%s\s*\)?(?:\.(\w+))?" % re.escape(obj["var"]), e)
    if not m: return None
    if not m.group(1): return 0
    for f in obj["fields"]:
        if f[1] == m.group(1): return f[0]
    return None

def rewrite_pointers(text, obj, mode="direct", allow_pinned=False):
    """`T *p = &var; ... ((V *)p)->m ...` -> `var.field` (mode direct: p removed) or `Type *p = &var; p->field`
    (mode typed).  Every use of p must be a recognised object access, p must not be a pinned register variable,
    and every assignment to p must be the same object address.  Returns (text, notes) or (None, reason)."""
    notes = []; views = parse_views(text); var = obj["var"]; changed = False
    for bs, be in reversed(_bodies(text)):
        body = text[bs:be]
        cands = {}
        for m in re.finditer(r"\b([A-Za-z_]\w*)\s*=\s*([^;=][^;]*);", body):
            off = _addr_off(obj, m.group(2))
            if off is not None: cands.setdefault(m.group(1), set()).add(off)
        for p, offs in cands.items():
            if len(offs) != 1: return None, "%s assigned two different addresses" % p
            base_off = offs.pop()
            dm = list(re.finditer(r"^([ \t]*)((?:register\s+)?(?:struct\s+)?[A-Za-z_][\w ]*?)\s*\*\s*%s\b([^;,]*)?;[^\n]*\n" % p, body, re.M))
            if not dm or len({x.group(0).strip() for x in dm}) != 1:
                return None, "declaration of %s not found (or not a single declarator)" % p
            d = dm[0]   # several identical declarations = the matching and NON_MATCHING arms, edited in lockstep
            all_assign = re.findall(r"(?<![\w.>])%s\s*(?:=(?!=)|\+=|-=|\+\+|--)\s*([^;]*);" % p, body) + re.findall(r"(?:\+\+|--)\s*%s\b" % p, body)
            if any(isinstance(a, str) and _addr_off(obj, a) is None for a in all_assign) or re.search(r"&\s*%s\b" % p, body):
                return None, "%s is also assigned something else (or its address is taken)" % p
            if ("ASM_REG" in d.group(0) or "asm(" in d.group(0)) and not allow_pinned: return None, "%s is a pinned register variable" % p
            ptype = re.sub(r"\b(register|struct)\b", "", d.group(2)).strip()
            init = d.group(3) or ""
            if init.strip() and _addr_off(obj, init.strip().lstrip("=")) is None: return None, "%s initialised to something else" % p
            psize = TSIZE.get(ptype, 1 if ptype in ("void",) else None)
            pview = views.get(ptype, (None,))[0] if ptype in views else None
            if ptype == obj.get("type"): pview = {f[1]: (f[0], f[3], f[4], {"s16": "s16", "u16": "u16", "s32": "s32", "u8": "u8", "s8": "s8", "ptr": "void *"}[f[2]], None) for f in obj["fields"] if f[1]}
            prefix, sep = (var, ".") if mode == "direct" else (p, "->")
            loc = []
            def em(off, size, signed, cty, s, st, en, addr=False):
                return emit_field(obj, prefix, sep, base_off + off, size, signed, cty, s, st, en, addr, loc)
            def vmember(vname, member, s, st, en, addr):
                vn = vname.replace("struct", "").strip()
                vw = (views.get(vn) or (None,))[0]
                if vn == obj.get("type"): vw = pview
                if vw is None or member not in vw: raise ValueError("view %s.%s unknown" % (vn, member))
                o, sz, sg, cty, cnt = vw[member]
                if cnt: raise ValueError("array member %s" % member)
                return em(o, sz, sg, cty.replace(" *", "*").replace("*", " *") if "*" in cty else cty, s, st, en, addr)
            def cty_of(T):
                T = re.sub(r"\s+", " ", T.strip())
                if T.endswith("*"): return T.rstrip("* ").strip() + " *", 4, False
                if T not in TSIZE: raise ValueError("type " + T)
                return T, TSIZE[T], T in SIGNED
            new = body
            if mode == "direct":
                for x in reversed(dm): new = new[:x.start()] + new[x.end():]
            if mode == "typed":
                if base_off != 0 or "type" not in obj: return None, "typed mode needs the object start"
                new = new.replace(d.group(0), "%s%s *%s%s;\n" % (d.group(1), obj["type"], p, init.rstrip()))
            # assignments: removed (direct) or respelled &var (typed)
            def afix(m):
                if _addr_off(obj, m.group(2)) is None: return m.group(0)
                return "" if mode == "direct" else "%s = &%s;" % (p, var)
            if mode == "direct":   # a whole-line assignment goes with its line
                new = re.sub(r"^[ \t]*(%s)\s*=\s*([^;=][^;]*);[ \t]*\n" % p, lambda m: "" if _addr_off(obj, m.group(2)) is not None else m.group(0), new, flags=re.M)
            new = re.sub(r"(?<![\w.>])(%s)\s*=\s*([^;=][^;]*);" % p, lambda m: afix(m) if _addr_off(obj, m.group(2)) is not None else m.group(0), new)
            try:
                # 1. ((V *)p)->m      2. p->m
                new = sub_code(r"(&\s*)?\(\s*\(\s*((?:struct\s+)?\w+)\s*\*\s*\)\s*%s\s*\)\s*->\s*(\w+)" % p,
                               lambda m: vmember(m.group(2), m.group(3), m.string, m.start(), m.end(), bool(m.group(1))), new)
                if pview is not None:
                    new = sub_code(r"(&\s*)?(?<![\w.>])%s\s*->\s*(\w+)" % p,
                                   lambda m: vmember(ptype, m.group(2), m.string, m.start(), m.end(), bool(m.group(1))), new) if mode == "direct" else new
                # 3. *(T *)(p + k) / *(T *)((u8 *)p + k) / *(T *)p
                def arith(m):
                    cty, sz, sg = cty_of(m.group(1)); inner = m.group(2).strip()
                    mm = re.fullmatch(r"(?:\(\s*(?:u8|s8|char|unsigned char)\s*\*\s*\)\s*)?%s(?:\s*([+-])\s*%s)?" % (p, NUM), inner)
                    if not mm: raise ValueError("pointer arithmetic " + inner)
                    scale = 1 if "*)" in inner.replace(" ", "") or psize is None else psize
                    k = int(mm.group(2), 0) if mm.group(2) else 0
                    if mm.group(1) == "-": k = -k
                    return em(k * scale, sz, sg, cty, m.string, m.start(), m.end())
                new = sub_code(r"\*\s*\(\s*((?:unsigned |signed )?\w+\s*\**)\s*\*\s*\)\s*\(\s*((?:\([^()]*\)\s*)?%s(?:\s*[+-]\s*%s)?)\s*\)" % (p, NUM), arith, new)
                new = sub_code(r"\*\s*\(\s*((?:unsigned |signed )?\w+\s*\**)\s*\*\s*\)\s*%s\b(?!\s*[\[+-])" % p,
                               lambda m: em(0, *cty_of(m.group(1))[1:], cty_of(m.group(1))[0], m.string, m.start(), m.end()), new)
                # 4. ((T *)p)[k]    5. p[k]    6. *p
                def tidx(m):
                    cty, sz, sg = cty_of(m.group(2)); return em(int(m.group(3), 0) * sz, sz, sg, cty, m.string, m.start(), m.end(), bool(m.group(1)))
                new = sub_code(r"(&\s*)?\(\s*\(\s*((?:unsigned |signed )?\w+\s*\**)\s*\*\s*\)\s*%s\s*\)\s*\[\s*%s\s*\]" % (p, NUM), tidx, new)
                if psize:
                    pty = ptype
                    new = sub_code(r"(&\s*)?(?<![\w.>])%s\s*\[\s*%s\s*\]" % (p, NUM),
                                   lambda m: em(int(m.group(2), 0) * psize, psize, pty in SIGNED, pty, m.string, m.start(), m.end(), bool(m.group(1))), new)
                    def dref(m):
                        before = m.string[:m.start()].rstrip()
                        if before and (before[-1].isalnum() or before[-1] in "_)]"): return m.group(0)
                        return em(0, psize, pty in SIGNED, pty, m.string, m.start(), m.end())
                    new = sub_code(r"\*\s*%s\b(?!\s*[\[+-])" % p, dref, new)
            except ValueError as e:
                return None, "%s: %s" % (p, e)
            left = [m.start() for a, b in code_spans(new) for m in re.finditer(r"\b%s\b" % p, new[a:b])]
            if mode == "direct" and left: return None, "%s has uses the rewrite does not understand" % p
            if mode == "typed" and re.search(r"\(\s*\(\s*\w+\s*\*\s*\)\s*%s\s*\)" % p, new): return None, "%s: casts left" % p
            body = new; changed = True; notes.append("%s: %s" % (p, ", ".join(dict.fromkeys(loc))))
        text = text[:bs] + body + text[be:]
    if not changed: return None, "no local pointer to the object"
    for name, (mem, a, b) in sorted(((k, v) for k, v in parse_views(text).items() if not k.startswith("struct ")), key=lambda x: -x[1][1]):
        if len(re.findall(r"\b%s\b" % name, text)) == 1 and re.search(r"/\*[^*]*in func_", text[b:b + 120]):
            text = text[:a] + text[b:].lstrip("\n"); notes.append("dropped view " + name)
    return text, "; ".join(notes)

# ------------------------------------------------------------------ phase 3: a CODE address declared as data
def rewrite_funcaddr(text, obj):
    """obj {"function": "func_X", "syms": "D_X", "header": ...}: the row declares a function's address as a data
    object and only ever takes its address (census: no load or store through it).  `&D_X` / decayed `D_X` become
    the function designator; the local data declaration goes; the header carries the prototype."""
    sym, fn = obj["syms"], obj["function"]
    DECL = re.compile(r"^[ \t]*extern[ \t]+[^;(,]*?\b%s\b[ \t]*(\[[^\]]*\])?[ \t]*;[^\n]*\n" % sym, re.M)
    decls = list(DECL.finditer(text))
    code = "".join(text[a:b] for a, b in code_spans(text))
    if not re.search(r"\b%s\b" % sym, code): return None, "object not referenced in code"
    if not decls: return None, "no local declaration of " + sym
    code = "".join(DECL.sub("", text)[a:b] for a, b in code_spans(DECL.sub("", text)))
    if re.search(r"\b%s\s*\[" % sym, code) or re.search(r"\b%s\b\s*(?:[-+]|\.|->)" % sym, code): return None, "indexed / arithmetic use"
    if re.search(r"\b%s\b" % fn, code): return None, "row already declares " + fn
    text = DECL.sub("", text)
    text = sub_code(r"&\s*%s\b" % sym, fn, text)
    text = sub_code(r"\(\s*[\w ]+\*\s*\)\s*%s\b" % sym, fn, text)   # (void *)D_X -> the designator (pointer either way)
    text = sub_code(r"\b%s\b" % sym, fn, text)
    inc = '#include "%s"\n' % obj["header"]
    m = re.search(r'^#include "common.h"[^\n]*\n', text, re.M)
    pos = m.end() if m else 0
    return text[:pos] + inc + text[pos:], "D_X -> " + fn
