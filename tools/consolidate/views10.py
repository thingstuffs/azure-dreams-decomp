"""views10.py: union-aware parser of a row's local struct/union typedefs (the m2c view types).
   parse(text) -> {Name: View}; View = {"size", "align", "members": {m: Mem}, "span": (start, end)}
   Mem = {"off", "size", "signed", "ptr", "cty", "cnt", "sub"}   sub = a nested View (inline or named struct/union).
   leaf(views, V, chain) resolves `->m.s[2].t` to (off, size, signed, ptr, cty) or raises ValueError."""
import re
PRIM = {"s8": (1, True), "u8": (1, False), "char": (1, True), "signed char": (1, True), "unsigned char": (1, False),
        "s16": (2, True), "u16": (2, False), "short": (2, True), "signed short": (2, True), "unsigned short": (2, False),
        "short int": (2, True), "unsigned short int": (2, False),
        "s32": (4, True), "u32": (4, False), "int": (4, True), "signed int": (4, True), "unsigned int": (4, False),
        "long": (4, True), "unsigned long": (4, False), "unsigned": (4, False), "signed": (4, True), "M2C_UNK": (4, True),
        "f32": (4, True), "uptr": (4, False), "intptr_t": (4, True), "size_t": (4, False), "s64": (8, True), "u64": (8, False)}
CANON = {"char": "s8", "signed char": "s8", "unsigned char": "u8", "short": "s16", "signed short": "s16", "unsigned short": "u16",
         "short int": "s16", "unsigned short int": "u16", "int": "s32", "signed int": "s32", "unsigned int": "u32", "long": "s32",
         "unsigned long": "u32", "unsigned": "u32", "signed": "s32", "M2C_UNK": "s32", "uptr": "u32", "intptr_t": "s32", "size_t": "u32"}
STRIP = re.compile(r'"(?:[^"\\\n]|\\.)*"|/\*.*?\*/|//[^\n]*', re.S)

def _blank(text):
    return STRIP.sub(lambda m: " " * len(m.group(0)), text)

def _match_brace(t, i):
    d = 0
    for j in range(i, len(t)):
        if t[j] == "{": d += 1
        elif t[j] == "}":
            d -= 1
            if d == 0: return j
    raise ValueError("unbalanced")

def _split_decls(body):
    """top-level `;`-separated declarations of a struct body (nested braces kept)."""
    out, d, cur = [], 0, []
    for ch in body:
        if ch == "{": d += 1
        elif ch == "}": d -= 1
        if ch == ";" and d == 0: out.append("".join(cur).strip()); cur = []
        else: cur.append(ch)
    if "".join(cur).strip(): out.append("".join(cur).strip())
    return [x for x in out if x]

def _body(kind, body, views):
    mems = {}; off = 0; align = 1; size = 0
    for d in _split_decls(body):
        d = re.sub(r"\s+", " ", d).strip()
        sub = None
        m = re.match(r"^(struct|union)\s*(\w*)\s*\{(.*)\}\s*(\w+)\s*(?:\[\s*([^\]]+)\s*\])?$", d, re.S)
        if m:
            sub = _body(m.group(1), m.group(3), views); name = m.group(4); cnt = m.group(5)
            sz, al, sg, ptr, cty = sub["size"], sub["align"], False, False, None
        else:
            fp = re.match(r"^[\w ]+\(\s*\*\s*(\w+)\s*\)\s*\(.*\)$", d)
            if fp: name, cnt, sz, al, sg, ptr, cty = fp.group(1), None, 4, 4, False, True, "void *"
            else:
                mm = re.match(r"^((?:const |volatile )*(?:unsigned |signed )?(?:struct |union )?\w+(?: int)?)\s*(\*+)?\s*(\w+)\s*(?:\[\s*([^\]]+)\s*\])?$", d)
                if not mm: raise ValueError("member " + d)
                base = re.sub(r"\b(const|volatile)\b\s*", "", mm.group(1)).strip(); star = mm.group(2); name = mm.group(3); cnt = mm.group(4)
                if star: sz, al, sg, ptr, cty = 4, 4, False, True, base + " " + star
                elif base in PRIM: (sz, sg), ptr, cty = PRIM[base], False, CANON.get(base, base); al = min(sz, 4)
                elif base in views or base.replace("struct ", "").replace("union ", "") in views:
                    sub = views.get(base) or views[base.replace("struct ", "").replace("union ", "")]
                    sz, al, sg, ptr, cty = sub["size"], sub["align"], False, False, None
                else: raise ValueError("type " + base)
        n = 1
        if cnt is not None:
            try: n = int(eval(cnt, {}, {}))
            except Exception: raise ValueError("count " + cnt)
        o = 0 if kind == "union" else (off + al - 1) // al * al
        mems[name] = {"off": o, "size": sz, "signed": sg, "ptr": ptr, "cty": cty, "cnt": n if cnt is not None else None, "sub": sub}
        align = max(align, al)
        if kind == "union": size = max(size, sz * n)
        else: off = o + sz * n; size = off
    size = (size + align - 1) // align * align
    return {"kind": kind, "size": size, "align": align, "members": mems}

def parse(text, known=None):
    """every typedef struct/union (and plain `struct Tag {..};`) of the text, in order."""
    t = _blank(text); views = dict(known or {})
    for m in re.finditer(r"(typedef\s+)?\b(struct|union)\s*(\w*)\s*\{", t):
        if not m.group(1) and not m.group(3): continue
        # skip nested ones (inside another struct body): the enclosing parse handles them
        if re.search(r"\{[^{}]*$", t[max(0, m.start() - 200):m.start()]) and not m.group(1): continue
        try:
            j = _match_brace(t, m.end() - 1)
            v = _body(m.group(2), t[m.end():j], views)
        except ValueError:
            continue
        tail = re.match(r"\s*(\w+)?\s*;", t[j + 1:])
        if not tail: continue
        end = j + 1 + tail.end()
        v["span"] = (m.start(), end)
        if m.group(1) and tail.group(1): views[tail.group(1)] = v
        if m.group(3): views[m.group(2) + " " + m.group(3)] = v; views.setdefault(m.group(3), v) if not m.group(1) else None
    return views

def leaf(view, chain):
    """chain: ['m', '.s', '[2]', '.t'] after `->`.  -> (off, size, signed, ptr, cty, whole_sub)"""
    off = 0; cur = view; mem = None
    i = 0
    while i < len(chain):
        c = chain[i]
        if c.startswith("["):
            if mem is None or mem["cnt"] is None: raise ValueError("index on non-array")
            k = c[1:-1].strip()
            if not re.fullmatch(r"0x[0-9A-Fa-f]+|\d+", k): raise ValueError("non-constant index")
            off += int(k, 0) * mem["size"]; mem = dict(mem, cnt=None); cur = mem["sub"]; i += 1; continue
        name = c.lstrip(".")
        if cur is None or name not in cur["members"]: raise ValueError("member %s unknown" % name)
        mem = cur["members"][name]; off += mem["off"]; cur = mem["sub"]; i += 1
    if mem is None: raise ValueError("empty chain")
    if mem["cnt"] is not None: raise ValueError("array member used whole")
    if mem["sub"] is not None:
        return (off, mem["size"], False, False, None, True)
    return (off, mem["size"], mem["signed"], mem["ptr"], mem["cty"], False)
