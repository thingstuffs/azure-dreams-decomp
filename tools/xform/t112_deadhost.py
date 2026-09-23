"""T112: a DEAD parameter or local hosts a later constant - `H = K; f(H, ...)` / `H = 0; v = H;`.

APPEARS     a parameter (or a local) whose last use is behind the statement, next to pins that hold the
            register an allocation-call argument or a zero init takes.  Harvest-1 named it "the next build in
            this family" (docs/evidence/pin_research_round73_move_table.md, move #2; astra, 5 rows):
              dungeon/func_80FB1000 (r74_astra_a2)  `arg1 = 0x112; created = func_8003FD64(arg1, D_80083498);`
                                                    (arg1 declared s32 in both declarations of BODY_NAME);
              dungeon/func_80FF3000 (r74_astra_a2)  `pos_y = 0; object_state = (void *)pos_y; pos_x = 0x112;
                                                    object = func_8003FD64(pos_x, &D_80083498);`;
              dungeon/func_80283F70 (r74_astra_a4)  the dead `page` local: `page = 0; type1_count = page;`;
              dungeon/func_80DE9000 (r73_astra_h2), func_80D91070 (r74_astra_a2): call RESULTS hosted on a dead
                                                    parameter / local (not on this menu: a restructured `&&`).
            and the opus form on dungeon/func_81059F68 (r73_opus_a3, rule (b)): "host `p` on an already
            multi-set local of the right register class (not a fresh single-set local)".

RESOLVES    astra (func_80FF3000): "reuse the consumed parameters for the actual allocation code and
            null-result value".  opus (func_81059F68): "The move defeats `birthing_insn_p`" - a constant
            written into a pseudo that already has a set is no longer a single-set birthing insn, so sched1
            keeps it at its source position, and local-alloc/global give it the parameter's (or dead local's)
            register instead of a fresh one: the register the pin forced.

WHY THE OWNERS MISS IT  t66/t101 merge two LOCALS whose lives do not overlap; no generator writes a
            constant through a parameter, and none offers a dead local as the host of an unrelated constant.

SAFETY      the host H is a scalar or pointer parameter/local of the function whose every mention (other
            than its declaration and pins) lies textually BEFORE the statement, and the statement is not inside
            a loop that also mentions H, so the new value cannot reach an old use.  `vf` is the oracle.

CANDIDATES  per site (an integer-literal argument of a call statement; the literal right-hand side of
            `v = K;`) x host (dead parameters first, then dead locals; at most four) x spelling (`H = K;`
            before the statement and H in the literal's place; for a narrow parameter also H retyped s32 in
            every declaration) x pin plans (the pins in the statement's window, those plus H's register
            binding, the pins naming H, window + named, every pin of the function).  Ranked by cc1 listing
            distance to the pinned text; the listing-exact candidates and the two nearest go to `vf`.
"""
import difflib
import re
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
from pin_census import sites_of, asm_blocker, unscored_text
from pin_sites import erase_many
try:
    from .t29_addrsym import mask_comments, decls_of
    from .t36_paramwidth import functions
    from .t98_paramcell import _scalar, retype
    from . import screen
except ImportError:
    from t29_addrsym import mask_comments, decls_of
    from t36_paramwidth import functions
    from t98_paramcell import _scalar, retype
    import screen

MAX_SITES = 6
MAX_HOSTS = 4
MAX_LISTINGS = 90
MAX_VERIFY = 4
LIT = r"(?:0[xX][0-9A-Fa-f]+|\d+|NULL)"
PIN_LINE = re.compile(r"^[ \t]*ASM_[A-Z0-9_]+\s*\(")
CALLSTMT_RE = re.compile(r"^(?P<ind>[ \t]*)(?:[A-Za-z_][\w.\->\[\]]*[ \t]*=[ \t]*(?:\([^()]*\)[ \t]*)?)?"
                         r"(?P<fn>[A-Za-z_]\w*)[ \t]*\((?P<args>[^;{}\n]*)\)[ \t]*;[^\n]*$", re.M)
LITASSIGN_RE = re.compile(r"^(?P<ind>[ \t]*)(?P<v>[A-Za-z_]\w*)[ \t]*=[ \t]*(?P<k>%s)[ \t]*;[^\n]*$" % LIT, re.M)
KEYWORDS = {"if", "while", "for", "switch", "return", "sizeof"}
LOOP_RE = re.compile(r"\b(?:do|for|while)\b[^;{]*\{")


def _loops(masked, b0, b1):
    """[(open, close)] brace spans of do/for/while bodies inside the function."""
    out = []
    for m in LOOP_RE.finditer(masked, b0, b1):
        o = m.end() - 1
        d = 0
        for j in range(o, b1):
            d += (masked[j] == "{") - (masked[j] == "}")
            if d == 0:
                out.append((o, j)); break
    return out


def _mentions(masked, name, b0, b1):
    """Offsets of every mention of `name` in the body except declaration and pin lines."""
    out = []
    for m in re.finditer(r"(?<![\w.>])%s\b" % re.escape(name), masked[b0:b1]):
        pos = b0 + m.start()
        ls = masked.rfind("\n", 0, pos) + 1
        le = masked.find("\n", pos)
        line = masked[ls:le]
        if PIN_LINE.match(line) or re.match(r"^[ \t]*(?:register[ \t]+)?[A-Za-z_][\w \t]*\**[ \t]*\b%s\b[^=;]*(?:=[^;]*)?;"
                                            % re.escape(name), line):
            continue
        out.append(pos)
    return out


def hosts(text, params, b0, b1, at):
    """Dead-by-`at` parameters then locals: [(name, type, is_param)]."""
    masked = mask_comments(text)
    loops = [l for l in _loops(masked, b0, b1) if l[0] < at < l[1]]
    out = []
    cands = [(p, t, True) for p, t, _a, _b in params]
    body = masked[b0:b1]
    for m in re.finditer(r"^[ \t]*(?:register[ \t]+)?(?P<ty>(?:unsigned[ \t]+|signed[ \t]+)?[A-Za-z_]\w*)[ \t]*(?P<p>\**)[ \t]*"
                         r"(?P<n>[A-Za-z_]\w*)[ \t]*(?:ASM_REG\([^)]*\))?[ \t]*(?:=[^;]*)?;", body, re.M):
        ty = m.group("ty")
        if ty in ("return", "goto", "else", "case") or m.group("n") in {p for p, _t, _x in cands}:
            continue
        if _scalar(ty) or m.group("p"):
            cands.append((m.group("n"), ty + (" " + m.group("p") if m.group("p") else ""), False))
    for name, ty, is_param in cands:
        if not (_scalar(ty) or "*" in ty):
            continue
        ms = _mentions(masked, name, b0 + 1, b1)
        if not ms and not is_param:
            continue
        if any(p >= at for p in ms):
            continue
        if any(any(l[0] < p < l[1] for p in ms) for l in loops):
            continue
        out.append((name, ty, is_param, max(ms) if ms else b0))
    out.sort(key=lambda h: (not h[2], -h[3]))
    return [(n, t, p) for n, t, p, _l in out[:MAX_HOSTS]]


def sites(text):
    """[{fn, params, line, kind, lit_span, ind}] - 0-based lines; lit_span is the literal's text offsets."""
    masked = mask_comments(text)
    line_of = lambda pos: masked.count("\n", 0, pos)
    out = []
    pins = sites_of(text)
    for fname, params, b0, b1 in functions(text):
        if not any(b0 < p[3] < b1 for p in pins):
            continue
        for m in CALLSTMT_RE.finditer(masked, b0, b1):
            if m.group("fn") in KEYWORDS or m.group("fn").startswith("ASM_"):
                continue
            a0 = m.start("args")
            for lm in re.finditer(r"(?:^|(?<=,))[ \t]*(?P<k>%s)[ \t]*(?=,|$)" % LIT, m.group("args")):
                out.append({"fn": fname, "line": line_of(m.start()), "kind": "arg", "ind": m.group("ind"),
                            "lit": (a0 + lm.start("k"), a0 + lm.end("k")), "k": lm.group("k"), "at": m.start()})
        for m in LITASSIGN_RE.finditer(masked, b0, b1):
            out.append({"fn": fname, "line": line_of(m.start()), "kind": "assign", "ind": m.group("ind"),
                        "lit": (m.start("k"), m.end("k")), "k": m.group("k"), "at": m.start(), "v": m.group("v")})
    out.sort(key=lambda s: s["at"])
    return out[:MAX_SITES * 4]


def _span(text, fname):
    return next(((p, x, y) for n, p, x, y in functions(text) if n == fname), None)


def rewrite(text, st, host, hty):
    """Insert `H = K;` above the statement and read H in place of the literal."""
    a, b = st["lit"]
    k = st["k"] if st["k"] != "NULL" else "0"
    use = host if "*" not in hty or st["kind"] == "arg" else host
    t = text[:a] + use + text[b:]
    ls = t.rfind("\n", 0, a) + 1
    return t[:ls] + st["ind"] + "%s = %s;\n" % (host, ("(%s)%s" % (hty, k)) if "*" in hty else k) + t[ls:]


def candidates(text):
    sig, n0 = unscored_text(text), len(sites_of(text))
    out, seen = [], {text}
    used = 0
    for st in sites(text):
        sp = _span(text, st["fn"])
        if sp is None:
            continue
        params, b0, b1 = sp
        hs = [h for h in hosts(text, params, b0, b1, st["at"]) if h[0] != st.get("v")]
        if not hs:
            continue
        used += 1
        if used > MAX_SITES:
            break
        for host, hty, is_param in hs:
            if st["k"] == "NULL" and "*" not in hty and not _scalar(hty):
                continue
            base = rewrite(text, st, host, hty)
            variants = [("plain", base)]
            if is_param and _scalar(hty) in ("s8", "u8", "s16", "u16"):
                idx = [i for i, p in enumerate(params) if p[0] == host][0]
                rt = retype(base, st["fn"], params, {idx: "s32"})
                for m in re.finditer(r"^[ \t]*#[ \t]*define[ \t]+%s[ \t]+([A-Za-z_]\w*)" % re.escape(st["fn"]),
                                     rt or "", re.M):
                    rt = retype(rt, m.group(1), params, {idx: "s32"}) or rt
                if rt:
                    variants.append(("s32", rt))
            for vtag, cur in variants:
                pins = sites_of(cur)
                _p, c0, c1 = _span(cur, st["fn"])
                mine = [p for p in pins if c0 < p[3] < c1]
                ln = st["line"] + 1                     # the statement moved down one line
                window = [p for p in mine if ln - 4 <= p[5] - 1 <= ln + 1]
                def names(p):
                    seg = cur[p[3]:p[4]] if p[0] == "stmt" else cur[cur.rfind("\n", 0, p[3]) + 1:cur.find("\n", p[4])]
                    return re.search(r"\b%s\b" % re.escape(host), seg)
                named = [p for p in mine if names(p)]
                hreg = [p for p in named if p[0] == "reg"]
                for ptag, grp in (("window", window), ("window+hreg", window + hreg), ("named", named),
                                  ("window+named", window + named), ("all", mine)):
                    grp = list({(p[3], p[4]): p for p in grp}.values())
                    if not grp:
                        continue
                    cand = erase_many(cur, grp, clean_notes=True)
                    if cand in seen or unscored_text(cand) != sig or len(sites_of(cand)) >= n0:
                        continue
                    seen.add(cand)
                    out.append(("%s@%d:%s<-%s:%s:%s" % (st["kind"], st["line"] + 1, host, st["k"], vtag, ptag), cand))
    return out


def _dist(a, b):
    return sum(1 for y in difflib.unified_diff(a, b, lineterm="", n=0)
               if y[:1] in "+-" and not y.startswith(("---", "+++")))


class T:
    name = "t112_deadhost"
    level = 1
    needs_verify = True

    @staticmethod
    def eligible(text, row, census):
        why = asm_blocker(text)
        if why:
            return why
        if not sites_of(text):
            return "no pin sites"
        for st in sites(text):
            sp = _span(text, st["fn"])
            if sp and [h for h in hosts(text, sp[0], sp[1], sp[2], st["at"]) if h[0] != st.get("v")]:
                return None
        return "no literal argument/assignment with a dead parameter or local to host it"

    @classmethod
    def apply_verified(cls, text, row, census, vf):
        pins_in = len(sites_of(text))
        info = {"pins_in": pins_in, "pins_out": pins_in}
        menu = candidates(text)
        if not menu:
            return None, dict(info, refused=["no buildable candidate"])
        target = screen.compile_s(row, text)
        if target is None:
            return None, dict(info, refused=["pinned text does not build to a listing"])
        ranked, listings = [], 0
        for label, cand in menu:
            if listings >= MAX_LISTINGS:
                break
            lst = screen.compile_s(row, cand); listings += 1
            if lst is None:
                continue
            ranked.append((_dist(target, lst), len(sites_of(cand)), label, cand))
        ranked.sort(key=lambda x: (x[0], x[1]))
        info.update(listings=listings, menu=len(menu))
        tried = 0
        for d, pins, label, cand in ranked:
            if tried >= MAX_VERIFY or (d and tried >= 2):
                break
            tried += 1
            if vf(cand).get("exact"):
                return cand, dict(info, step="%s|d%d" % (label, d), pins_out=pins, tried=tried)
        return None, dict(info, tried=tried,
                          nearest=[{"distance": d, "label": l} for d, _p, l, _c in ranked[:6]])
