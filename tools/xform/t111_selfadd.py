"""T111: `p = base + K; ASM_KEEP(p);` written as a self-referential add - `p = base; p = p + K;`.

APPEARS     a pointer formed as a constant offset from another pointer and kept at once, the keep's residue
            being the address FORM (retail addresses the fields off `p`, the erased build folds `K` into every
            field offset off `base`):

                result = (u8 *)object + 0x20;
                ASM_KEEP(result);
                ((S_80170E74_0 *)object)->unk_10 = D_8017103C;
                result->unk_13 = 42;

            dungeon/func_8102F674 (claude-opus-5-5, work/native_lane/r73_opus_s6, 1 of its 2 pins),
            dungeon/func_809753B0 (r73_opus_s10, 1 of 2, `actor = (u8 *)object + 0x20`), and the in-place
            spelling on dungeon/func_80285464 (r73_opus_s10, 2 pins):
                data = (u8 *)(room_header + 4);  ASM_KEEP_NV(room_header);
            ->  room_header += 4;  data = (u8 *)room_header;

RESOLVES    opus (func_8102F674): "APPEARS: `p = base + K; ASM_KEEP(p);` where the fields of p are addressed
            off p in retail. RESOLVES: `p = base; p = p + K;` (the self-referential SET blocks the cse
            equivalence). The same move applies to sibling rows dungeon/func_809753B0 and dungeon/func_80AC5958".
            opus (func_809753B0): "APPEARS: `ASM_KEEP(p)` after `p = base + K` with a residue of `off+K(base)`
            addressing; RESOLVES: `p = base; p = (T *)((u8 *)p + K);`."  opus (func_80285464): "APPEARS: an
            `ASM_KEEP[_NV](p)` right after `q = (T *)(p + k)` where the listing residue is `lbu/lhu/lw N+k($p)`
            replacing `0($q)` (address-form class); RESOLVES: rewrite as `p += k; q = (T *)p;` (or `q = p; q +=
            k;`) when p is dead or reassigned before its next use."
            Mechanism: cse records `p == base + K` for a SET whose source does not mention its destination and
            then folds `K` into each `off(p)` as `off+K(base)`; a set whose source reads `p` itself records no
            such equivalence, so the fields stay addressed off `p`.

WHY THE OWNERS MISS IT  no generator rewrites the keep's own statement: t105/t82 move statements, t69 drops
            copies, t104/t86 respell page constants.

CANDIDATES  per `NAME = RHS;` whose RHS is `BASE + K` / `BASE - K` under casts (BASE an identifier, K an
            integer literal) and whose next statement is a keep naming NAME or BASE: (split)
            `NAME = BASE; NAME = (T)(RHS with BASE -> NAME);` (T = NAME's declared type), also with `(T)BASE`;
            (inplace) `BASE += K; NAME = (cast)BASE;` and `NAME = BASE; NAME += K;` for a same-typed NAME;
            each with the keep erased, and with every pin naming NAME erased.  Ranked by cc1 listing distance
            to the pinned text; the listing-exact candidates and the two nearest go to `vf`.
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
    from . import screen
except ImportError:
    from t29_addrsym import mask_comments, decls_of
    from t36_paramwidth import functions
    import screen

MAX_SITES = 8
MAX_LISTINGS = 60
MAX_VERIFY = 4
CAST = r"(?:\(\s*(?:(?:unsigned|signed|const|struct|union|volatile)\s+)*[A-Za-z_]\w*[ \t]*\**\s*\)\s*)"
LIT = r"(?:0[xX][0-9A-Fa-f]+|\d+)"
ASSIGN_RE = re.compile(r"^(?P<ind>[ \t]*)(?P<n>[A-Za-z_]\w*)[ \t]*=(?!=)[ \t]*(?P<rhs>[^;{}\n]*);[^\n]*$", re.M)
# RHS forms: [cast]BASE +/- K, [cast](BASE +/- K), [cast]([cast]BASE +/- K)
RHS_RE = re.compile(r"^(?P<outer>%s?)(?P<open>\(\s*)?(?P<inner>%s?)(?P<base>[A-Za-z_]\w*)\s*(?P<op>[-+])\s*(?P<k>%s)\s*(?(open)\))$"
                    % (CAST, CAST, LIT))
KEEP_RE = re.compile(r"^[ \t]*ASM_(?:KEEP|KEEP_NV|USE|USE_NV)\s*\((?P<args>[^;]*)\)\s*;")


def _decl_type(text, b0, b1, name, params):
    for p, t, _a, _b in params:
        if p == name:
            return re.sub(r"\s+", " ", t.strip())
    ds = [d for d in decls_of(text, name) if b0 < d[2][0] < b1]
    if len(ds) == 1:
        return (ds[0][0] + " " + "*" * ds[0][1]).strip()
    return None


def sites(text):
    """[{fn, line, name, base, rhs, keep_line, type, base_type}] - 0-based line numbers."""
    masked = mask_comments(text)
    ml = masked.split("\n")
    line_of = lambda pos: masked.count("\n", 0, pos)
    out = []
    for fname, params, b0, b1 in functions(text):
        for m in ASSIGN_RE.finditer(masked, b0, b1):
            rm = RHS_RE.match(m.group("rhs").strip())
            if not rm:
                continue
            n, base = m.group("n"), rm.group("base")
            if n == base or base in ("sizeof",):
                continue
            ln = line_of(m.start("n"))
            k = ln + 1
            while k < len(ml) and not ml[k].strip():
                k += 1
            km = KEEP_RE.match(ml[k]) if k < len(ml) else None
            if not km or not ({n, base} & set(re.findall(r"[A-Za-z_]\w*", km.group("args")))):
                continue
            ty = _decl_type(text, b0, b1, n, params)
            bty = _decl_type(text, b0, b1, base, params)
            if not ty or "*" not in ty and not bty:
                continue
            out.append({"fn": fname, "line": ln, "name": n, "base": base, "rm": rm, "ind": m.group("ind"),
                        "keep_line": k, "type": ty, "base_type": bty})
            if len(out) >= MAX_SITES:
                return out
    return out


def rewrites(text, st):
    """{tag: [new lines for the assignment]}."""
    rm, n, b, ind, ty = st["rm"], st["name"], st["base"], st["ind"], st["type"]
    rhs_self = rm.group(0)[:rm.start("base")] + n + rm.group(0)[rm.end("base"):]
    outs = {"split": [ind + "%s = %s;" % (n, b), ind + "%s = (%s)(%s);" % (n, ty, rhs_self)],
            "splitcast": [ind + "%s = (%s)%s;" % (n, ty, b), ind + "%s = (%s)(%s);" % (n, ty, rhs_self)]}
    k, op = rm.group("k"), rm.group("op")
    bty = st["base_type"]
    if bty and "*" in bty and not rm.group("inner").strip():
        # the add in BASE's own units, through NAME: `NAME = (T)((BT)NAME + K)`
        outs["splitbase"] = [ind + "%s = (%s)%s;" % (n, ty, b),
                             ind + "%s = (%s)((%s)%s %s %s);" % (n, ty, bty, n, op, k)]
    cast = rm.group("outer").strip() or ("(%s)" % ty)
    if not rm.group("inner").strip():
        outs["inplace"] = [ind + "%s %s= %s;" % (b, op, k), ind + "%s = %s%s;" % (n, cast, b)]
    if bty and re.sub(r"\s", "", bty) == re.sub(r"\s", "", ty):
        outs["copyadd"] = [ind + "%s = %s;" % (n, b), ind + "%s %s= %s;" % (n, op, k)]
    return outs


def build(text, chosen, ptag):
    """Rewrite every (site, new lines) in `chosen`, then erase the sites' keeps (and, for 'named', every pin
    naming a rewritten NAME)."""
    lines = text.split("\n")
    for st, new in sorted(chosen, key=lambda c: -c[0]["line"]):
        lines[st["line"]:st["line"] + 1] = new
    t2 = "\n".join(lines)
    keeps = set()
    for st, new in chosen:
        keeps.add(st["keep_line"] + sum(len(nw) - 1 for s2, nw in chosen if s2["line"] <= st["keep_line"]))
    names = {st["name"] for st, _n in chosen}
    grp = []
    for p in sites_of(t2):
        seg = t2[p[3]:p[4]] if p[0] == "stmt" else t2[t2.rfind("\n", 0, p[3]) + 1:t2.find("\n", p[4])]
        if p[5] - 1 in keeps or (ptag == "named" and any(re.search(r"\b%s\b" % re.escape(x), seg) for x in names)):
            grp.append(p)
    if not grp:
        return None
    return erase_many(t2, grp, clean_notes=True)


def candidates(text):
    sig, n0 = unscored_text(text), len(sites_of(text))
    out, seen = [], {text}
    sts = sites(text)
    per = [(st, rewrites(text, st)) for st in sts]
    plans = []
    for st, rw in per:
        for tag, new in rw.items():
            plans.append(("%s@%d:%s" % (st["name"], st["line"] + 1, tag), [(st, new)]))
    if len(per) > 1:                                    # every site at once, one spelling
        for tag in ("split", "splitcast", "splitbase", "inplace", "copyadd"):
            ch = [(st, rw[tag]) for st, rw in per if tag in rw]
            if len(ch) > 1:
                plans.append(("joint:%s" % tag, ch))
    for label, ch in plans:
        for ptag in ("keep", "named"):
            cand = build(text, ch, ptag)
            if not cand or cand in seen or unscored_text(cand) != sig or len(sites_of(cand)) >= n0:
                continue
            seen.add(cand)
            out.append(("%s:%s" % (label, ptag), cand))
    return out


def _dist(a, b):
    return sum(1 for y in difflib.unified_diff(a, b, lineterm="", n=0)
               if y[:1] in "+-" and not y.startswith(("---", "+++")))


class T:
    name = "t111_selfadd"
    level = 1
    needs_verify = True

    @staticmethod
    def eligible(text, row, census):
        why = asm_blocker(text)
        if why:
            return why
        if not sites_of(text):
            return "no pin sites"
        if not sites(text):
            return "no `p = base + K;` followed by a keep on p or base"
        return None

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
