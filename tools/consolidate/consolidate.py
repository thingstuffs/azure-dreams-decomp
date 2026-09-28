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
    for m in re.finditer(r"typedef\s+struct\s*\w*\s*\{(.*?)\}\s*(\w+)\s*;", text, re.S):
        body, name = m.group(1), m.group(2); off = 0; mem = {}; ok = True
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
        if ok: views[name] = (mem, m.start(), m.end())
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
    def lvalue_after(s, end):
        return re.match(r"\s*(=(?!=)|[-+*/%&|^]=|<<=|>>=|\+\+|--)", s[end:]) is not None
    def lvalue_before(s, start):
        return re.search(r"(\+\+|--)\s*$", s[:start]) is not None
    for sym, (ty, star, arr) in decls.items():
        off0 = int(sym[2:], 16) - obj["base"]
        esz = 4 if star else TSIZE.get(ty)
        esigned = (ty in SIGNED) and not star
        tyname = ty + (" *" if star else "")
        def emit(off, size, signed, cty, s, start, end, addr=False):
            fx, f = field_at(obj, off, size)
            lv = lvalue_after(s, end) or lvalue_before(s, start)
            if f is None:
                # no field of this size here: a view at the containing field (union site)
                fx2, f2 = None, None
                for g in obj["fields"]:
                    if g[0] <= off < g[0] + g[3]: f2 = g
                if f2 is None: raise ValueError("offset 0x%X outside every field" % off)
                at = "&%s" % var if f2[1] == "" else "&%s.%s" % (var, f2[1])
                inner = "(u8 *)%s + %d" % (at, off - f2[0]) if off != f2[0] else at
                notes.append("0x%X:%s view (size %d at field %s)" % (off, cty, size, f2[1]))
                return ("((%s *)(%s))" % (cty, inner)) if addr else ("*(%s *)(%s)" % (cty, inner))
            fexpr = var if fx == "" else "%s.%s" % (var, fx)   # a scalar object: its one "field" is the object
            same = (f[2] == "ptr" and cty.endswith("*")) or (f[2] != "ptr" and not cty.endswith("*") and (f[4] == signed))
            if addr:
                return ("&" + fexpr) if same else "((%s *)&%s)" % (cty, fexpr)
            if same:
                notes.append("0x%X:%s" % (off, fx)); return fexpr
            if lv:
                simple = re.match(r"\s*=(?!=)", s[end:]) is not None
                if (f[2] == "ptr") != cty.endswith("*") and not simple:   # int<->pointer compound op: the declared view
                    notes.append("0x%X:*(%s *)&%s" % (off, cty, fx)); return "*(%s *)&%s" % (cty, fexpr)
                notes.append("0x%X:%s" % (off, fx)); return fexpr
            notes.append("0x%X:(%s)%s" % (off, cty, fx)); return "((%s)%s)" % (cty, fexpr)
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
        if esz is None: return None, "unknown element type %s for %s" % (ty, sym)
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
    for name, (mem, a, b) in sorted(parse_views(text).items(), key=lambda x: -x[1][1]):
        if name in {d[0] for d in decls.values()} and len(re.findall(r"\b%s\b" % name, text)) == 1:
            text = text[:a] + text[b:].lstrip("\n")
            notes.append("dropped view typedef " + name)
    inc = '#include "%s"\n' % obj["header"]
    if inc not in text:
        m = re.search(r'^#include "common.h"[^\n]*\n', text, re.M)
        pos = m.end() if m else 0
        text = text[:pos] + inc + text[pos:]
    return text, "; ".join(dict.fromkeys(notes))
