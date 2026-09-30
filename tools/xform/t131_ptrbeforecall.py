"""T131: a pointer local assigned AFTER a call, written above the preceding call - the unfolded `addiu` rule.

APPEARS     a work pointer set from a base and a constant, after a call, right before its first use

                func_8004491C(obj, fn);  ...
                p = (u8 *)obj + 0x20;   ASM_KEEP(p);   (or ASM_USE(p), `register .. p ASM_REG`, or a raw
                *(s16 *)(p + 0xE) = 4;                  `__asm__ __volatile__` barrier next to it)

            and the pin's lone erasure FOLDS the offset into the store (`sh $3,46($18)` instead of retail's
            `addiu $t,$18,32; sh $3,14($t)`).  Also `p = &x->field;`, `p = x + K;`, `T *p = (T *)x + K;`.
RESOLVES    r80_opus_earlyconst2 (2026-09-30, rule 1): combine.c:924-929 never combines across a CALL_INSN.  So the
            assignment written ABOVE the previous call is never folded into the store's displacement, and sched1
            launches the single-set pointer (birthing boost) right at its only consumer: retail's unfolded
            `addiu` directly before the store.  Solved the ASM_USE(owner_data) pin of dungeon/func_800B4204 and
            the ASM_KEEP(component_work) pin of dungeon/func_80EB751C.
CANDIDATES  per assignment S (a statement `v = E;` or a declaration `T *v = E;` whose E is a pure address
            expression of one LOCAL base x - a parameter or a local whose address is never taken - plus a constant
            or a member path) and per hoist position P (before each preceding statement that holds a call, nearest
            first, climbing out of enclosing blocks; never across a label, a preprocessor line, an assignment to
            x, a mention of v, or - when leaving a loop - an assignment to x anywhere in the loop):
              named     the pins naming v erased
              +1        named (or nothing) plus ONE other pin of the region erased, last first
              joint     every pin and raw `__asm__ __volatile__` barrier between P and the end of S's block
            Each is checked (unscored arm unchanged, pins strictly fewer) and put to the byte verifier;
            the first exact wins.  A declaration `T *v = E;` becomes a function-scope `T *v;` plus the hoisted
            assignment (refused when v is declared more than once in the function).
"""
import os, re, sys
from pathlib import Path

_HERE = Path(__file__).resolve()
for _cand in (_HERE.parents[1],):
    if (_cand / "pin_census.py").exists():
        sys.path.insert(0, str(_cand))
        break
from pin_census import sites_of
from pin_sites import erase_many
import xform.t29_addrsym as A
from xform.t36_paramwidth import functions
try:
    from . import screen
except ImportError:
    from xform import screen

MAX_VERIFY = int(os.environ.get("T131_MAX", "16"))
MAX_LISTINGS = int(os.environ.get("T131_LIST", "70"))
MAX_POS = int(os.environ.get("T131_POS", "6"))
mask_comments = A.mask_comments

PP_LINE = re.compile(r"(?:[ \t]*#[^\n]*\n|[ \t\n])*")
LABEL = re.compile(r"(?:(?:case\b[^:;{}]*|default)[ \t\n]*:|(?!(?:case|default)\b)[A-Za-z_]\w*[ \t]*:(?!:))")
NOT_CALL = {"if", "while", "for", "switch", "return", "sizeof", "do", "else"}
CALL = re.compile(r"(?<![\w.>])([A-Za-z_]\w*)[ \t\n]*\(")
RAW_ASM = re.compile(r"__asm__[ \t\n]+__volatile__[ \t\n]*\((?:[^;]|\n)*?\)[ \t]*;")
CAST = r"\([ \t]*(?:const[ \t]+|unsigned[ \t]+|signed[ \t]+)*[A-Za-z_]\w*(?:[ \t]+long)?[ \t]*\**[ \t]*\)"
IDENT = r"[A-Za-z_]\w*"
ADDR_EXPR = re.compile(r"^&?[ \t]*\(*[ \t]*(?P<x>%s)(?:[ \t]*(?:->|\.)[ \t]*%s)*[ \t]*\)*"
                       r"(?:[ \t]*[+-][ \t]*(?:0x[0-9A-Fa-f]+|\d+)[Uu]?[Ll]?)?[ \t]*\)*$" % (IDENT, IDENT))
ASSIGN_S = re.compile(r"^(?P<lead>(?:\([ \t]*)?)(?P<v>%s)[ \t]*=(?!=)[ \t]*(?P<rhs>[^;]+);$" % IDENT)
DECL_S = re.compile(r"^(?:register[ \t]+)?(?P<ty>(?:unsigned[ \t]+|signed[ \t]+|const[ \t]+)*%s(?:[ \t]+long)?)[ \t]*"
                    r"(?P<p>\*+)[ \t]*(?P<v>%s)[ \t]*=(?!=)[ \t]*(?P<rhs>[^;]+);$" % (IDENT, IDENT))


# ------------------------------------------------------------------ a small statement tree
class Item:
    __slots__ = ("a", "b", "kids", "hdrs", "label")

    def __init__(self, a):
        self.a, self.b, self.kids, self.hdrs, self.label = a, a, [], [], False


def _skip(m, i, n):
    return PP_LINE.match(m, i, n).end()


def _peek_word(m, i, n, w):
    j = _skip(m, i, n)
    return re.match(r"%s\b" % w, m[j:j + len(w) + 1]) is not None


def parse_block(m, i, n):
    """Items of the block whose text starts at `i` (just after `{`) -> (items, index of the closing brace)."""
    items = []
    while True:
        i = _skip(m, i, n)
        if i >= n:
            return items, n
        if m[i] == "}":
            return items, i
        it = Item(i)
        depth = 0
        j = i
        while j < n:
            c = m[j]
            if c in "([":
                depth += 1
            elif c in ")]":
                depth -= 1
            elif depth == 0 and c == ";":
                j += 1
                if _peek_word(m, j, n, "else"):
                    continue
                break
            elif depth == 0 and c == "{":
                hdr = (it.hdrs[-1][1] if it.hdrs else it.a, j)
                it.hdrs.append((hdr[0], hdr[1]))
                kids, e = parse_block(m, j + 1, n)
                it.kids.append((j, e, kids))
                j = e + 1
                if _peek_word(m, j, n, "else"):
                    j = _skip(m, j, n)
                    continue
                if re.match(r"do\b", m[it.a:it.a + 3]):
                    while j < n and m[j] != ";":
                        j += 1
                    j += 1
                break
            elif depth == 0 and c == "}":
                break
            j += 1
        it.b = j
        it.label = LABEL.match(m, it.a, it.b) is not None
        items.append(it)
        i = j
    return items, n


def _call_in(masked_seg):
    for mm in CALL.finditer(masked_seg):
        name = mm.group(1)
        if name in NOT_CALL or name.startswith("ASM_") or name == "__asm__" or name == "__volatile__":
            continue
        if re.fullmatch(r"[A-Z_][A-Z0-9_]*", name):
            continue                                     # a macro (PTR, KSEG..), not a call
        return True
    return False


def find_path(items, pos):
    """[(items_list, index)] from the function body down to the item that is a simple statement starting at pos."""
    for k, it in enumerate(items):
        if it.a <= pos < it.b:
            if it.a == pos and not it.kids:
                return [(items, k)]
            for (bs, be, kids) in it.kids:
                if bs < pos < be:
                    sub = find_path(kids, pos)
                    if sub:
                        return [(items, k)] + sub
            return None
    return None


# ------------------------------------------------------------------ candidate assignments
def _mentions(v, seg):
    return re.search(r"(?<![.>\w])\b%s\b" % re.escape(v), seg) is not None


def _modifies(x, seg):
    """x itself changes (a store THROUGH x does not)."""
    xs = re.escape(x)
    if re.search(r"(?<![.>\w])\b%s\b[ \t]*(?:=(?!=)|[-+*/|&^%%]=|<<=|>>=|\+\+|--)" % xs, seg):
        return True
    if re.search(r"(?:\+\+|--)[ \t]*%s\b" % xs, seg):
        return True
    if re.search(r"&[ \t]*%s\b(?![ \t]*->)" % xs, seg):
        return True
    return False


def _is_local(fn_text, params, x):
    if any(p[0] == x for p in params):
        return True
    return bool(A.decls_of(fn_text, x))


def _is_ptr(fn_text, params, x):
    for p in params:
        if p[0] == x:
            return "*" in p[1]
    return any(d[1] >= 1 for d in A.decls_of(fn_text, x))


def assignments(text):
    """[{v, x, s:(a,b), stmt, kind, ty, fn, path, rhs}] - address assignments that could be hoisted."""
    masked = mask_comments(text)
    out = []
    for name, params, bs, be in functions(text):
        fn_text = masked[bs:be + 1]
        items, _e = parse_block(masked, bs + 1, be)
        ptrs = _scan(masked, items, [])
        for it, path in ptrs:
            seg = masked[it.a:it.b]
            mm, kind = ASSIGN_S.match(seg), "assign"
            if not mm or mm.group("lead"):
                mm, kind = DECL_S.match(seg), "decl"
            if not mm:
                continue
            v, rhs = mm.group("v"), mm.group("rhs").strip()
            core = re.sub(CAST, "", rhs)
            am = ADDR_EXPR.match(core.strip())
            if not am:
                continue
            x = am.group("x")
            if x == v or _call_in(rhs):
                continue
            has_member = re.search(r"->|\.", core) is not None
            if has_member and not core.lstrip().startswith("&"):
                continue                                  # `x->f` is a load, not an address
            if not has_member and not re.search(r"[+\-][ \t]*(?:0x[0-9A-Fa-f]+|\d+)", core):
                continue
            if not _is_local(fn_text, params, x) or not _is_ptr(fn_text, params, x) or re.search(r"&[ \t]*%s\b(?![ \t]*->)" % re.escape(x), fn_text):
                continue
            ty = None
            if kind == "decl":
                if len(A.decls_of(fn_text, v)) != 1:
                    continue
                ty = mm.group("ty") + " " + mm.group("p")
            elif not A.decls_of(fn_text, v) and not any(p[0] == v for p in params):
                continue
            out.append({"v": v, "x": x, "s": (it.a, it.b), "kind": kind, "ty": ty, "rhs": rhs,
                        "fn": (bs, be), "path": path, "items": items})
    return out


def _scan(masked, items, path):
    out = []
    for k, it in enumerate(items):
        if it.kids:
            for (_bs, _be, kids) in it.kids:
                out += _scan(masked, kids, path + [(items, k)])
        else:
            out.append((it, path + [(items, k)]))
    return out


def positions(masked, a):
    """Hoist positions for the statement `a`: start offsets of the preceding statements that hold a call, nearest
    first (at most MAX_POS), climbing out of enclosing blocks (a compound's own header stays put), plus the top
    of each block that holds a call above the statement; never past a label."""
    out, tops = [], []
    for items, idx in reversed(a["path"]):
        hit = False
        for k in range(idx - 1, -1, -1):
            u = items[k]
            if u.label:
                return out + [t for t in tops if t not in out]
            if _call_in(masked[u.a:u.b]):
                hit = True
                if len(out) < MAX_POS:
                    out.append(u.a)
        if hit and idx > 0 and items[0].a not in out and not items[0].label:
            tops.append(items[0].a)
    return out + [t for t in tops if t not in out]


def hoist_ok(masked, a, P, fn, check_v=True):
    """Is moving `v = E;` from a['s'] up to P legal for the bytes' sake (region checks)?"""
    v, x, S = a["v"], a["x"], a["s"]
    reg = masked[P:S[0]]
    if re.search(r"(?m)^[ \t]*#", reg):
        return False
    if (check_v and _mentions(v, reg)) or _modifies(x, reg):
        return False
    if not check_v:
        return True
    # compounds that S leaves (P sits above their head): a loop must not change x anywhere; v may be
    # mentioned in them only at S and after S inside S's own block
    for items, idx in a["path"][:-1]:
        comp = items[idx]
        if comp.a < P:
            continue
        if re.match(r"(?:for|while|do)\b", masked[comp.a:comp.a + 6]) and _modifies(x, masked[comp.a:comp.b]):
            return False
        for mm in re.finditer(r"(?<![.>\w])\b%s\b" % re.escape(v), masked[comp.a:comp.b]):
            pos = comp.a + mm.start()
            if S[0] <= pos < S[1]:
                continue
            if not (pos > S[1] and _same_block_after(a, pos)):
                return False
    return True


def _same_block_after(a, pos):
    """pos lies after S inside the block that holds S (or a block nested in the rest of it)."""
    items, idx = a["path"][-1]
    last = items[-1].b if items else 0
    return a["s"][1] <= pos <= last


def _has_use_after(masked, a):
    fb, fe = a["fn"]
    return _mentions(a["v"], masked[a["s"][1]:fe])


# ------------------------------------------------------------------ the rewrite
def _line_start(text, p):
    ls = text.rfind("\n", 0, p) + 1
    return ls if not text[ls:p].strip() else None


DECL_LINE = re.compile(r"^[ \t]+(?:register[ \t]+)?[A-Za-z_][\w \t]*?[ \t*]+\**\w+(?:\[[^\]]*\])?[ \t]*(?:ASM_REG\([^)]*\))?[ \t]*(?:=[^;(]*)?;")


def _put_decl(t, bs, decl, where):
    """Insert the declaration line at the top of the function's declarations, or after the last of them."""
    nl = t.find("\n", bs)
    if where == "top":
        return t[:nl + 1] + decl + t[nl + 1:]
    pos = nl + 1
    at = pos
    while pos < len(t):
        le = t.find("\n", pos)
        le = len(t) if le < 0 else le
        line = t[pos:le]
        if DECL_LINE.match(line):
            at = min(len(t), le + 1)
        elif line.strip() and not line.strip().startswith(("/*", "*", "//")):
            break
        pos = le + 1
    return t[:at] + decl + t[at:]


def move(text, a, P, where="top"):
    """text with S removed and `v = E;` (declaration hoisted to function scope) inserted before P."""
    v, rhs = a["v"], a["rhs"]
    sa, sb = a["s"]
    stmt = "%s = %s;" % (v, rhs)
    ls = _line_start(text, P)
    indent = text[ls:P] if ls is not None else ""
    ins = (indent + stmt + "\n") if ls is not None else (stmt + " ")
    at = ls if ls is not None else P
    # remove S (whole line when alone on it)
    ra, rb = sa, sb
    l0 = text.rfind("\n", 0, ra) + 1
    l1 = text.find("\n", rb)
    l1 = len(text) if l1 < 0 else l1
    if not text[l0:ra].strip() and not text[rb:l1].strip():
        ra, rb = l0, min(len(text), l1 + 1)
    if at >= ra:
        return None
    t = text[:at] + ins + text[at:ra] + text[rb:]
    if a["kind"] == "decl":
        bs = a["fn"][0]
        decl = "    %s%s;\n" % (a["ty"].rstrip(), v) if a["ty"].endswith("*") else "    %s %s;\n" % (a["ty"], v)
        t = _put_decl(t, bs, decl, where)
    return t


def _live_end(masked, a):
    """End offset of the role S starts: up to the next plain `v = ..;` statement of S's block, else the block end.
    None when the role cannot be delimited (an assignment nested in a compound, or a mention past the block)."""
    v = a["v"]
    items, idx = a["path"][-1]
    for it in items[idx + 1:]:
        seg = masked[it.a:it.b]
        if it.kids:
            if re.search(r"(?<![.>\w])\b%s\b[ \t]*(?:=(?!=)|[-+*/|&^%%]=|<<=|>>=|\+\+|--)" % re.escape(v), seg):
                return None
            continue
        if re.match(r"\(?[ \t]*%s[ \t]*=(?!=)" % re.escape(v), seg):
            return it.a
    end = items[-1].b if items else a["s"][1]
    if _mentions(v, masked[end:a["fn"][1]]):
        return None
    return end


def move_fresh(text, masked, a, P, where="top"):
    """S becomes a fresh function-scope pointer `<x>_work` set at P; the uses of S's role are renamed."""
    if a["kind"] != "assign":
        return None
    end = _live_end(masked, a)
    if end is None:
        return None
    fn_text = masked[a["fn"][0]:a["fn"][1] + 1]
    base = a["x"] + "_work"
    new, k = base, 2
    while re.search(r"\b%s\b" % re.escape(new), fn_text):
        new, k = "%s%d" % (base, k), k + 1
    dm = A.decls_of(fn_text, a["v"])
    ty = "u8 *"
    if dm and dm[0][1] >= 1:
        ty = dm[0][0] + " " + "*" * dm[0][1]
    rhs = a["rhs"]
    cm = re.match(CAST, rhs)
    if cm and "*" not in cm.group(0):
        rhs = "(u8 *)" + rhs[cm.end():].lstrip()
    sa, sb = a["s"]
    body = text[sb:end]
    mb = masked[sb:end]
    out, last = [], 0
    for m in re.finditer(r"(?<![.>\w])\b%s\b" % re.escape(a["v"]), mb):
        out.append(body[last:m.start()]); out.append(new); last = m.end()
    out.append(body[last:])
    renamed = "".join(out)
    t = text[:sb] + renamed + text[end:]
    a2 = dict(a, v=new, rhs=rhs, kind="assign")
    # remove S and insert `new = rhs;` before P by the plain mover on the renamed text
    t = move(t, a2, P)
    if t is None:
        return None
    # `move` located S by its span, which is unchanged (renames start after S); S's text must be the old one:
    t = _put_decl(t, a["fn"][0], "    %s%s;\n" % (ty, new), where)
    return t, new


def _pin_menu(text_moved, v, lo, hi, fn=None):
    """[named sites], [other sites in [lo,hi)] (last first), [raw barrier spans in [lo,hi)]."""
    sts = [s for s in sites_of(text_moved) if s[0] != "expand"]
    named = [s for s in sts if _mentions(v, text_moved[s[3]:s[4]])]
    other = [s for s in sts if lo <= s[3] < hi and s not in named]
    other.sort(key=lambda s: -s[3])
    if fn:                                            # then the rest of the function, nearest to the region first
        rest = [s for s in sts if fn[0] <= s[3] <= fn[1] and s not in named and s not in other]
        rest.sort(key=lambda s: min(abs(s[3] - lo), abs(s[3] - hi)))
        other += rest
    raw = [(m.start(), m.end()) for m in RAW_ASM.finditer(text_moved) if lo <= m.start() < hi]
    return named, other, raw


def _erase_raw(t, spans):
    for a, b in sorted(spans, reverse=True):
        l0 = t.rfind("\n", 0, a) + 1
        l1 = t.find("\n", b)
        l1 = len(t) if l1 < 0 else l1
        if not t[l0:a].strip() and not t[b:l1].strip():
            a, b = l0, min(len(t), l1 + 1)
        t = t[:a] + t[b:]
    return t


def _one(text, masked, a, P, pi, where, mv, fresh, tiers):
    """The erasure variants of one moved text, appended to `tiers`."""
    av = dict(a, v=fresh) if fresh else a
    fb, fe = a["fn"]
    delta = len(mv) - len(text)
    hs = "%s = %s;" % (av["v"], av["rhs"])
    lo = mv.rfind("\n", 0, mv.find(hs, max(0, P - 1))) + 1
    # end of S's block in the moved text: the block's closing brace shifted by the edit
    bl_end = (a["path"][-1][0][-1].b if a["path"][-1][0] else a["s"][1]) + delta
    named, other, raw = _pin_menu(mv, av["v"], lo, bl_end, (fb, fe + delta))
    tag = "%s@%d>P%d%s" % (av["v"], text.count("\n", 0, a["s"][0]) + 1, pi, "" if where == "top" else "@declend")
    if named:
        tiers[0].append((tag + ":named", erase_many(mv, named, clean_notes=True)))
    for s in other[:8]:
        base = erase_many(mv, named, clean_notes=True) if named else mv
        # locate the same pin in the (possibly edited) text by its statement text
        seg = mv[s[3]:s[4]]
        live = [q for q in sites_of(base) if q[0] != "expand" and base[q[3]:q[4]] == seg]
        if live:
            q = min(live, key=lambda q: abs(q[3] - s[3]))
            tiers[1].append((tag + ":+1@%d" % s[5], erase_many(base, [q], clean_notes=True)))
    if named or other or raw:
        allp = erase_many(mv, named + other, clean_notes=True)
        if raw:
            allp = _erase_raw(allp, [(x, y) for x, y in _reloc_raw(allp, mv, lo, bl_end)])
        tiers[2].append((tag + ":joint", allp))
        fnall = [q for q in sites_of(mv) if q[0] != "expand" and fb <= q[3] <= fe + delta]
        fj = erase_many(mv, fnall, clean_notes=True)
        fraw = [(m.start(), m.end()) for m in RAW_ASM.finditer(fj) if fb <= m.start() <= fe + delta]
        tiers[3].append((tag + ":fnjoint", _erase_raw(fj, fraw)))
        if raw:
            tiers[3].append((tag + ":named+raw", _erase_raw(erase_many(mv, named, clean_notes=True),
                                                              list(_reloc_raw(erase_many(mv, named, clean_notes=True), mv, lo, bl_end)))))


def candidates(text):
    """[(label, text)] in verify order (the hoist alone never lowers pins, so each carries an erasure)."""
    masked = mask_comments(text)
    n0 = len(sites_of(text))
    cands, seen = [], {text}
    tiers = {0: [], 1: [], 2: [], 3: []}
    for a in assignments(text):
        if not _has_use_after(masked, a):
            continue
        for pi, P in enumerate(positions(masked, a)):
            for where in ("top", "end"):
                fresh = None
                if hoist_ok(masked, a, P, a["fn"]):
                    mv = move(text, a, P, where)
                    needs_decl = a["kind"] == "decl"
                elif a["kind"] == "assign" and hoist_ok(masked, a, P, a["fn"], check_v=False):
                    r = move_fresh(text, masked, a, P, where)
                    mv, fresh = (r if r else (None, None))
                    needs_decl = True
                else:
                    mv, needs_decl = None, False
                if mv is None or (where == "end" and not needs_decl):
                    continue
                _one(text, masked, a, P, pi, where, mv, fresh, tiers)
    for k in sorted(tiers):
        for label, t in tiers[k]:
            if t in seen or len(sites_of(t)) >= n0:
                continue
            seen.add(t)
            cands.append((label, t))
    return cands


def _reloc_raw(t, orig, lo, hi):
    """Raw barrier spans of `t` that correspond to the ones of `orig` in [lo,hi) (same statement text, in order)."""
    want = [orig[m.start():m.end()] for m in RAW_ASM.finditer(orig) if lo <= m.start() < hi]
    out = []
    for m in RAW_ASM.finditer(t):
        if t[m.start():m.end()] in want:
            out.append((m.start(), m.end()))
    return out


class T:
    name = "t131_ptrbeforecall"
    level = 1
    needs_verify = True

    @staticmethod
    def eligible(text, row, census):
        if not sites_of(text):
            return "no pin sites"
        masked = mask_comments(text)
        try:
            asg = [a for a in assignments(text) if _has_use_after(masked, a)]
        except Exception as e:
            return "parse: %r" % (e,)
        if not asg:
            return "no local pointer assigned `v = base + K` / `&x->f` with a later use"
        return None

    @staticmethod
    def apply_verified(text, row, census, vf):
        cands = candidates(text)
        if not cands:
            return None, {"refused": ["no hoistable pointer assignment (call above, x unchanged, v unused before)"]}
        n0 = len(sites_of(text))
        tried = 0
        if len(cands) > 3:
            # rank by the distance of the cc1 listing from the pinned text's (which is retail-exact)
            target = screen.compile_s(row, text)
            if target is not None:
                ranked = []
                for k, (label, cand) in enumerate(cands[:MAX_LISTINGS]):
                    lst = screen.compile_s(row, cand)
                    d = screen.sdiff(target, lst) if lst is not None else None
                    ranked.append((10 ** 6 if d is None else d, k, label, cand))
                ranked.sort()
                cands = [(l, c) for _d, _k, l, c in ranked] + cands[MAX_LISTINGS:]
        for label, cand in cands:
            if tried >= MAX_VERIFY:
                break
            tried += 1
            if vf(cand).get("exact"):
                return cand, {"step": label, "pins_in": n0, "pins_out": len(sites_of(cand)), "verifies": tried}
        return None, {"refused": ["no exact hoist + pin erasure (%d verifies of %d candidates)" % (tried, len(cands))]}
