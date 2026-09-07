"""T4: replace M2C_FIELD(base, T *, off) raw offset accesses with typed struct members.

For every distinct base expression in a function, the set of (offset, type) accesses becomes a
local, address-named struct with explicit `unk_XX` members and `pad_XX[]` gaps (upstream
STYLE.md convention).  Sites become `((S *)base)->unk_XX`; when the base is a parameter or
local declared exactly `void *name`, the declaration is retyped and the casts dropped.

Refusals (journalled, never guessed): two different widths or signedness at one offset;
overlapping members; negative offsets; a base whose text cannot be parsed.
"""
import re, collections

FIELD = re.compile(r"M2C_FIELD\(\s*(?P<base>(?:[^(),]|\([^()]*\))+?)\s*,\s*(?P<ty>(?:[^(),]|\([^()]*\))+?)\s*,\s*(?P<off>[^(),]+?)\s*\)")
UNION_TAG = ["s", "u", "p", "q"]
def union_tags(types):
    """Meaningful view names: signed/unsigned -> s/u, volatile/plain -> v/n, pointer/int -> p/i."""
    tags = []
    widths = {width(t) for t in types}
    for t in types:
        base = re.sub(r"\b(volatile|const)\b", "", t).strip()
        if len(widths) > 1:
            w = width(t) or 4
            tag = ("p" if (base.endswith("*") or "(*)" in base) else ("u" if base.startswith("u") else "s")) + str(w * 8)
        elif "volatile" in t: tag = "v"
        elif any("volatile" in o for o in types if o != t): tag = "n"
        elif base.endswith("*") or "(*)" in base: tag = "p"
        elif any((o.endswith("*") or "(*)" in o) for o in types if o != t): tag = "i"
        elif base.startswith("u"): tag = "u"
        elif base.startswith("s"): tag = "s"
        else: tag = UNION_TAG[len(tags)]
        while tag in tags: tag += "2"
        tags.append(tag)
    return tags
def OVERLAP_TAG(rel, i): return f"at{rel:02X}" + ("" if i == 0 else UNION_TAG[i])
WIDTH = {"u8": 1, "s8": 1, "char": 1, "u16": 2, "s16": 2, "short": 2, "u32": 4, "s32": 4, "int": 4, "f32": 4, "M2C_UNK": 4,
         "s64": 8, "u64": 8, "f64": 8, "M2C_UNK8": 1, "M2C_UNK16": 2, "M2C_UNK32": 4, "M2C_UNK64": 8}

FPTR = re.compile(r"^(?P<ret>[A-Za-z_][A-Za-z0-9_ \*]*?)\s*\(\*\*\)\s*\((?P<args>[^()]*)\)$")

def elem_type(ty):
    """'u16 *' -> 'u16';  'void **' -> 'void *';  'T (**)(args)' -> 'T (*)(args)' (function pointer)."""
    ty = ty.strip()
    m = FPTR.match(ty)
    if m:
        return f"{m.group('ret').strip()} (*)({m.group('args').strip()})"
    if not ty.endswith("*"):
        return None
    return ty[:-1].strip()

def member_decl(t, name):
    m = re.match(r"^(.*?)\s*\(\*\)\((.*)\)$", t)
    if m:
        return f"{m.group(1)} (*{name})({m.group(2)});"
    return f"{t} {name};"

def width(t):
    if t.endswith("*") or "(*)" in t:
        return 4
    return WIDTH.get(re.sub(r"\b(volatile|const)\b", "", t).strip())

def parse_off(s):
    s = s.strip()
    try:
        return int(s, 0)
    except ValueError:
        return None

SITE_HEAD = re.compile(r"(?<![A-Za-z0-9_])(M2C_FIELD|FIELD)\(")

def scan_sites(text):
    """Every M2C_FIELD(base, T *, off) or FIELD(base, T, off) call as (start, end, base, ty, off)
    with ty normalised to the pointer spelling `T *`; balanced parens."""
    out = []; i = 0
    while True:
        m = SITE_HEAD.search(text, i)
        if not m: break
        i = m.start(); kind = m.group(1)
        j = m.end(); depth = 1; args = []; cur = ""
        while j < len(text) and depth:
            c = text[j]
            if c == "(": depth += 1; cur += c
            elif c == ")":
                depth -= 1
                if depth: cur += c
            elif c == "," and depth == 1: args.append(cur); cur = ""
            else: cur += c
            j += 1
        args.append(cur)
        if depth == 0 and len(args) == 3:
            ty = args[1].strip()
            if kind == "FIELD":
                ty = ty + " *" if "(*)" not in ty else re.sub(r"\(\*\)", "(**)", ty, count=1)
            out.append((i, j, args[0].strip(), ty, args[2].strip()))
        i = m.end()
    return out

DEF_HEAD = re.compile(r"^[ \t]*[A-Za-z_][A-Za-z0-9_ \*]*?\b\**(func_[0-9A-F]{8}|[A-Za-z_][A-Za-z0-9_]*)\s*\([^;{]*\)\s*\{", re.M)

def bodies(text):
    """Yield (start, end, name) of every top-level function body `name(...) { ... }`."""
    out = []
    for m in DEF_HEAD.finditer(text):
        ls = text.rfind("\n", 0, m.start()) + 1
        if text[ls:m.start()].strip():        # not at the start of a line: a call inside a body
            continue
        depth = 0; i = m.end() - 1
        while i < len(text):
            c = text[i]
            if c == "{": depth += 1
            elif c == "}":
                depth -= 1
                if depth == 0: break
            i += 1
        out.append((m.start(), i + 1, m.group(1)))
    return out

class T:
    name = "t4_fields"; level = 2
    needs_verify = True
    MAX_SEARCH = 160
    @staticmethod
    def eligible(text, row, census):
        if not SITE_HEAD.search(text):
            return "no M2C_FIELD/FIELD"
        return None
    @staticmethod
    def apply_verified(text, row, census, verify_fn):
        """Full struct form first; on a mismatch, greedily keep individual sites as explicit
        casts (`*(T *)((u8 *)base + off)`) while that lowers the aligned distance."""
        full = T.apply(text, row, census)
        if full is None:
            return None, {}
        v = verify_fn(full)
        bases_raw = dict(getattr(T, "last_bad", {}) or {})
        if v.get("exact"):
            return full, {"raw_sites": 0, "bases_raw": bases_raw}
        n = T._count_sites(text)
        if n > T.MAX_SEARCH or v.get("status") != "ok":
            return None, {"raw_sites": None, "first_class": v.get("class"), "first_total": v.get("total"), "sites": n}
        # delta debugging over the site set: applied sites A grow chunk by chunk; a chunk that
        # breaks exactness is halved; a single breaking site stays an explicit cast.
        tried = [0]
        def ok(applied):
            tried[0] += 1
            raw = set(range(n)) - applied
            return verify_fn(T.apply(text, row, census, raw=raw)).get("exact")
        A = set(); offending = set()
        work = [list(range(n))]
        while work:
            chunk = work.pop()
            if ok(A | set(chunk)):
                A |= set(chunk)
            elif len(chunk) == 1:
                offending |= set(chunk)
            else:
                h = len(chunk) // 2
                work.append(chunk[h:]); work.append(chunk[:h])
            if tried[0] > T.MAX_SEARCH:
                return None, {"raw_sites": None, "tried": tried[0], "first_class": v.get("class"), "first_total": v.get("total"), "sites": n, "reason": "search budget"}
        if not A:
            return None, {"raw_sites": None, "tried": tried[0], "first_class": v.get("class"), "first_total": v.get("total"), "sites": n}
        cand = T.apply(text, row, census, raw=set(range(n)) - A)
        return cand, {"raw_sites": len(offending), "tried": tried[0], "first_class": v.get("class"), "sites": n, "bases_raw": bases_raw}
    @staticmethod
    def _count_sites(text):
        return sum(1 for st, en, b, ty, off in scan_sites(text) if not text[text.rfind("\n", 0, st) + 1:st].lstrip().startswith("#"))
    @staticmethod
    def apply(text, row, census, raw=frozenset()):
        bs = bodies(text)
        if len(bs) <= 1:
            return T.apply_one(text, row, census, raw)
        # multi-definition TU: derive per body (right to left so offsets stay valid), hoist all typedefs
        cur = text; all_defs = []; counter = [0]
        seen = collections.Counter(b[2] for b in bs)
        for k, (start, end, name) in reversed(list(enumerate(bs))):
            body = cur[start:end]
            if not SITE_HEAD.search(body):
                continue
            alias = f"{name}_b{k}" if seen[name] > 1 else name
            new_body, defs = T.derive(body, row, name, retype=False, raw=raw, counter=counter, alias=alias)   # a file-level prototype could conflict
            cur = cur[:start] + new_body + cur[end:]
            all_defs = defs + all_defs
        if not all_defs:
            return None
        return T.place_defs(cur, all_defs, bs[0][2])
    @staticmethod
    def apply_one(text, row, census, raw=frozenset()):
        m = DEF_HEAD.search(text)
        if not m:
            raise ValueError("no function definition found")
        cur, defs = T.derive(text, row, m.group(1), raw=raw)
        if not defs:
            return None
        return T.place_defs(cur, defs, m.group(1))
    @staticmethod
    def _clusters(st, shift):
        out = []
        for off in sorted(st):
            o = off + shift; w = max(width(t) for t in st[off])
            if out and o < out[-1][1]:
                lo, hi, mem = out[-1]; mem[off] = st[off]; out[-1] = (lo, max(hi, o + w), mem)
            else:
                out.append((o, o + w, {off: st[off]}))
        return out
    @staticmethod
    def derive(text, row, fname, retype=True, raw=frozenset(), counter=None, alias=None):
        known_bad = {}
        for _ in range(4):
            c0 = list(counter) if counter is not None else None
            out = T.derive_core(text, row, fname, retype, raw, list(c0) if c0 is not None else None, alias, known_bad)
            found = getattr(T, "last_bad", {})
            if set(found) <= set(known_bad):
                if counter is not None: counter[0] = T._counter_end
                return out
            known_bad.update(found)
        raise ValueError("bad-base discovery did not converge")
    @staticmethod
    def derive_core(text, row, fname, retype=True, raw=frozenset(), counter=None, alias=None, known_bad=None):
        counter = counter if counter is not None else [0]
        sbase = (alias or fname).replace("func_", "")
        if sbase.startswith("BODY_NAME"):
            sbase = row["func"].replace("func_", "") + sbase[len("BODY_NAME"):]
        # a file transformed earlier may already declare S_<sbase>_<n>: continue the numbering
        nbase = len(set(re.findall(r"typedef struct (S_" + re.escape(sbase) + r"_\d+)\b", text)))
        # iterate innermost-first: rewrite until no M2C_FIELD with a non-nested argument list remains
        structs = {}          # base text -> {off: type}
        order = []
        cur = text
        bad = dict(known_bad or {})   # base -> reason: its sites keep the explicit-cast form
        class _F:
            def __init__(self, st, en, base, ty, off): self._s, self._e, self._g = st, en, {"base": base, "ty": ty, "off": off}
            def start(self): return self._s
            def end(self): return self._e
            def group(self, k): return cur[self._s:self._e] if k == 0 else self._g[k]
        def real(f):
            ls = cur.rfind("\n", 0, f.start()) + 1
            inner = cur[f.start() + 6:f.end()]          # skip the site's own head
            return not cur[ls:f.start()].lstrip().startswith("#") and not SITE_HEAD.search(inner)
        for _ in range(12):
            changed = False
            pass_sites = [f for f in [_F(*x) for x in scan_sites(cur)] if real(f)]
            c0 = counter[0]
            for k, f in enumerate(pass_sites):
                if c0 + k in raw:
                    continue
                base = f.group("base").strip()
                if base in bad:
                    continue
                t = elem_type(f.group("ty")); off = parse_off(f.group("off"))
                if t is None or off is None or width(t) is None:
                    bad[base] = f"unparsed site {f.group(0)[:50]}"      # this base stays as explicit casts
                    continue
                st = structs.setdefault(base, {})
                if base not in order: order.append(base)
                if off in st and t not in st[off]:
                    st[off].append(t)          # another view of the same bytes -> union (any width; overlaps cluster)
                elif off not in st:
                    st[off] = [t]
            # rewrite all non-nested sites in one pass (right to left keeps offsets valid)
            sites = [f for f in [_F(*x) for x in scan_sites(cur)] if real(f)]
            ids = {}
            for f in sites:                      # stable identity: rewrite order over the whole derivation
                ids[f.start()] = counter[0]; counter[0] += 1
            for f in reversed(sites):
                base = f.group("base").strip(); off = parse_off(f.group("off")); t = elem_type(f.group("ty"))
                if ids[f.start()] in raw or base in bad:
                    b = base if re.fullmatch(r"[A-Za-z_][A-Za-z0-9_]*", base) else f"({base})"
                    cur = cur[:f.start()] + f"(*({f.group('ty').strip()})((u8 *){b} + ({f.group('off').strip()})))" + cur[f.end():]
                    changed = True
                    continue
                sname = f"S_{sbase}_{order.index(base) + nbase}"
                lo = min(structs[base])
                b = base if re.fullmatch(r"[A-Za-z_][A-Za-z0-9_]*", base) else f"({base})"
                st_all = structs[base]
                shift = -lo if lo < 0 else 0
                part = {o2: ts for o2, ts in st_all.items() if (o2 < 0) == (off < 0)}
                cl = [c for c in T._clusters(part, shift if off < 0 else 0) if c[0] <= off + (shift if off < 0 else 0) < c[1]][0]
                if len(cl[2]) == 1:
                    mem = f"unk_{off + (shift if off < 0 else 0):02X}"
                    if len(st_all[off]) > 1: mem += "." + union_tags(st_all[off])[st_all[off].index(t)]
                else:
                    o = off + (shift if off < 0 else 0)
                    mem = f"unk_{cl[0]:02X}." + OVERLAP_TAG(o - cl[0], st_all[off].index(t)) + ".v"
                acc = (f"(({sname}_pre *){b})[-1].{mem}" if off < 0 else f"(({sname} *){b})->{mem}")
                cur = cur[:f.start()] + acc + cur[f.end():]
                changed = True
            if not changed:
                break
        if any(real(f) for f in [_F(*x) for x in scan_sites(cur)]):
            raise ValueError("sites remain after 12 passes")
        # drop the local accessor macro once nothing uses it
        if not re.search(r"(?<![A-Za-z0-9_])FIELD\(", re.sub(r"^[ \t]*#define[^\n]*\n", "", cur, flags=re.M)):
            cur = re.sub(r"^[ \t]*#define[ \t]+FIELD\([^\n]*\n", "", cur, flags=re.M)
        for b in list(bad):
            structs.pop(b, None)          # index in `order` stays reserved so names never shift
        # overlap check + struct text
        defs = []
        def clusters(st, shift):
            """Group members into maximal overlapping spans: [(lo, hi, {off: [types]})]."""
            out = []
            for off in sorted(st):
                o = off + shift; w = max(width(t) for t in st[off])
                if out and o < out[-1][1]:
                    lo, hi, mem = out[-1]; mem[off] = st[off]; out[-1] = (lo, max(hi, o + w), mem)
                else:
                    out.append((o, o + w, {off: st[off]}))
            return out
        def layout(st, shift, total=None):
            pos = 0; members = []
            for lo, hi, mem in clusters(st, shift):
                if lo > pos:
                    members.append(f"    u8 pad_{pos:02X}[0x{lo - pos:X}];")
                if len(mem) == 1:
                    off = next(iter(mem)); o = off + shift
                    if len(st[off]) == 1:
                        members.append("    " + member_decl(st[off][0], f"unk_{o:02X}"))
                    else:
                        tg = union_tags(st[off])
                        members.append(f"    union {{ " + " ".join(member_decl(t, tg[i]) for i, t in enumerate(st[off])) + f" }} unk_{o:02X};   /* accessed as both */")
                else:
                    # overlapping span: every access gets its own view inside one union at `lo`
                    views = []
                    for k, off in enumerate(sorted(mem)):
                        o = off + shift
                        for i, t in enumerate(mem[off]):
                            inner = (f"u8 pad[0x{o - lo:X}]; " if o > lo else "") + member_decl(t, "v")
                            views.append(f"struct {{ {inner} }} {OVERLAP_TAG(o - lo, i)};")
                    members.append(f"    union {{ " + " ".join(views) + f" }} unk_{lo:02X};   /* overlapping accesses */")
                pos = hi
            if total is not None and pos < total:      # a prefix record must be exactly the span before the pointer
                members.append(f"    u8 pad_{pos:02X}[0x{total - pos:X}];")
            return members
        for base in order:
            if base not in structs:
                continue
            st = structs[base]; sname = f"S_{sbase}_{order.index(base) + nbase}"
            lo = min(st)
            neg = {o: t for o, t in st.items() if o < 0}; pos_ = {o: t for o, t in st.items() if o >= 0}
            if neg:
                defs.append(f"typedef struct {sname}_pre {{\n" + "\n".join(layout(neg, -lo, total=-lo)) + f"\n}} {sname}_pre;   /* the 0x{-lo:X} bytes before {base} in {fname}, addressed as {base}[-1] */\n")
            if pos_:
                defs.append(f"typedef struct {sname} {{\n" + "\n".join(layout(pos_, 0)) + f"\n}} {sname};   /* {base} in {fname} */\n")
        # retype `void *base` parameters / locals where the base is a plain identifier
        for base in (order if retype and not raw else []):
            if base not in structs or not re.fullmatch(r"[A-Za-z_][A-Za-z0-9_]*", base) or min(structs[base]) < 0 or not any(o >= 0 for o in structs[base]):
                continue
            sname = f"S_{sbase}_{order.index(base) + nbase}"
            if re.search(r"^[ \t]*#define[ \t]+" + re.escape(base) + r"\b", cur, re.M):
                continue        # the name is a macro alias; keep the cast form
            decl = re.compile(r"\bvoid\s*\*\s*" + re.escape(base) + r"\b(?!\s*\()")
            # only the function's own parameter list / local declarations may be retyped
            head = re.search(r"^[ \t]*[A-Za-z_][A-Za-z0-9_ \*]*?\b\**" + re.escape(fname) + r"\s*\(([^;{]*)\)\s*\{", cur, re.M)
            if not head:
                continue
            body_end = cur.find("\n}", head.end())
            span = cur[head.start(1):head.end(1)]
            locals_ = cur[head.end():body_end if body_end > 0 else len(cur)]
            in_params = len(decl.findall(span)); in_locals = len(re.findall(r"^[ \t]*void\s*\*\s*" + re.escape(base) + r"\s*[;=]", locals_, re.M))
            if in_params + in_locals == 1 and not any(re.search(re.escape(base) + r"\s*[\+\-\[]", l) for l in cur.splitlines()):
                if in_params:
                    cur = cur[:head.start(1)] + decl.sub(f"{sname} *{base}", span, count=1) + cur[head.end(1):]
                else:
                    cur = cur[:head.end()] + re.sub(r"^([ \t]*)void\s*\*\s*" + re.escape(base) + r"\b", lambda mm: mm.group(1) + f"{sname} *{base}", locals_, count=1, flags=re.M) + cur[head.end() + len(locals_):]
                cur = cur.replace(f"(({sname} *){base})->", f"{base}->")
        T.last_bad = dict(bad); T._counter_end = counter[0]
        return cur, defs
    @staticmethod
    def place_defs(cur, defs, fname):
        # place struct definitions after the last #include (a prototype above the definition may
        # already name them); if there is no include, before the first line that names the base type
        # immediately before the first function definition: every file-level typedef the members may
        # name precedes it, and prototypes never name the new structs (only definition heads are retyped)
        first_def = None
        for m in DEF_HEAD.finditer(cur):
            ls = cur.rfind("\n", 0, m.start()) + 1
            if not cur[ls:m.start()].strip():
                first_def = m; break
        at = (cur.rfind("\n", 0, first_def.start()) + 1) if first_def else len(cur)
        # keep a doc comment that sits directly above the definition attached to it
        prev = cur[:at].rstrip("\n")
        if prev.endswith("*/"):
            cstart = prev.rfind("/*")
            if cstart >= 0 and "\n\n" not in prev[cstart:]:
                at = cstart
        cur = cur[:at] + "\n" + "\n".join(defs) + "\n" + cur[at:]
        return cur
