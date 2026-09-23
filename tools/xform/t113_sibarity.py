"""T113: a call's surplus arguments dropped to the callee's arity as a SIBLING translation unit declares it.

APPEARS     a call passing more arguments than the callee takes, the extras being whatever the previous
            statements left in `$a1-$a3`, held there by pins (the decompiler saw live argument registers and
            invented arguments; a file-local prototype was then written to match):

                extern void func_800A4ACC(void *, s32, s32);
                ...
                if (mode == 0) {
                    ASM_KEEP(mode);
                    func_800A4ACC(saved_entity, mode, raw_mode);

            dungeon/func_80D40744 (claude-opus-5-5, work/native_lane/r73_opus_a6: `func_800A4ACC(void *)` as
            every other TU declares it), dungeon/func_80BEE4EC (r73_opus_a6: `func_800498A0(effect_model)`,
            jointly with a symbol store for the page pinned to `$5`), dungeon/func_80DE6884 (r73_opus_a5:
            `func_80064584(s32)`, jointly with an aggregate copy).

RESOLVES    opus (func_80BEE4EC): "APPEARS: an unprototyped callee called with extra arguments that are exactly
            the registers the previous statements left in a1-a3 ... RESOLVES: call with the arity used elsewhere
            in the same TU and store through the symbol (t76_arity + t86_symaddr jointly)."  opus (func_80D40744):
            "callee arity from a sibling TU's prototype removes keeps on arguments cse would constant-fold."
            opus (func_80DE6884): "one aggregate copy from the parameter plus the real callee arity."

WHY THE OWNERS MISS IT (measured 2026-09-23, work/native_lane/r73_h2_t76_arity_check)
            t76_arity refuses all three "no call with pinned fake arguments": it drops only arguments that are
            NEVER ASSIGNED (`ASM_SET`-only locals); here the surplus arguments are real, assigned locals whose
            values the callee never reads, and the evidence for the true arity is another TU's prototype.

CANDIDATES  arity index (built once per process): the callee's own DEFINITION's arity when a row defines
            it, else the strict-majority arity of its typed prototypes `T func_X(params);` across the rows.  Per call statement in a pinned function to a callee with a declared arity m below the
            call's argument count (or another call of it in the same file passes fewer): the call truncated
            to m arguments (alone, and with every call of the callee in the file), the file's own prototype
            of the callee rewritten with a sibling's parameter list (K&R `()` when only a same-file call
            attests the arity) x pin plans (the pins naming a dropped argument, those plus the pins within
            three lines of the call, every pin of the function).  Ranked by cc1 listing distance to the
            pinned text; the listing-exact candidates and the two nearest go to `vf`.
"""
import collections
import difflib
import os
import re
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
from pin_census import sites_of, asm_blocker, unscored_text
from pin_sites import erase_many
try:
    from .t29_addrsym import mask_comments
    from .t36_paramwidth import functions
    from . import screen
except ImportError:
    from t29_addrsym import mask_comments
    from t36_paramwidth import functions
    import screen

MAX_SITES = 6
MAX_LISTINGS = 60
MAX_VERIFY = 4
PROTO_RE = re.compile(r"^[ \t]*(?:extern[ \t]+)?(?:static[ \t]+)?[A-Za-z_][\w \t\*]*?\b(?P<f>func_[0-9A-Fa-f]{8})[ \t]*"
                      r"\((?P<ps>[^;{}()]*)\)[ \t]*;", re.M)
CALL_RE = re.compile(r"(?<![\w.>])(?P<f>func_[0-9A-Fa-f]{8})[ \t]*\(")
_INDEX = None


def index():
    """{callee: {arity: parameter-list text}} - the arity the tree SETTLES on for each callee (cached):
    the callee's own definition when a row defines it, else the strict-majority arity of its typed
    prototypes.  A minority prototype is no evidence (func_800352FC: 0 x11 vs 4 x18)."""
    global _INDEX
    if _INDEX is None:
        from common import rows, clean_path
        protos = collections.defaultdict(collections.Counter)
        text_of = collections.defaultdict(dict)
        defs = {}
        for r in rows():
            p = clean_path(r)
            if not p.exists():
                continue
            t = p.read_text(errors="replace")
            masked = mask_comments(t)
            for m in PROTO_RE.finditer(masked):
                ps = m.group("ps").strip()
                if not ps:
                    continue                            # K&R: no arity evidence
                n = 0 if ps == "void" else len(ps.split(","))
                protos[m.group("f")][n] += 1
                text_of[m.group("f")].setdefault(n, ps)
            for name, params, b0, b1 in functions(t):
                dm = re.search(r"^[ \t]*#[ \t]*define[ \t]+%s[ \t]+(func_[0-9A-Fa-f]{8})" % re.escape(name), t, re.M)
                real = dm.group(1) if dm else name
                if re.fullmatch(r"func_[0-9A-Fa-f]{8}", real):
                    head = masked[:b0].rsplit("(", 1)[-1]
                    ps = ", ".join(ty for _p, ty, _a, _b in params) if params else "void"
                    if params or re.match(r"\s*void\s*\)", head):
                        defs[real] = (len(params), ps)
        idx = {}
        for f in set(protos) | set(defs):
            if f in defs:
                idx[f] = {defs[f][0]: text_of[f].get(defs[f][0], defs[f][1])}
                continue
            tot = sum(protos[f].values())
            n, c = protos[f].most_common(1)[0]
            if 2 * c > tot:
                idx[f] = {n: text_of[f][n]}
        _INDEX = idx
    return _INDEX


def _args(masked, open_paren):
    """[(a, b)] spans of the top-level arguments of the call whose `(` is at open_paren, or None."""
    d, i, start, out = 0, open_paren, open_paren + 1, []
    while i < len(masked):
        c = masked[i]
        if c in "([":
            d += 1
        elif c in ")]":
            d -= 1
            if d == 0:
                if masked[start:i].strip():
                    out.append((start, i))
                return out, i
        elif c == "," and d == 1:
            out.append((start, i)); start = i + 1
        elif c in ";{}":
            return None
        i += 1
    return None


def calls(text):
    """[{f, open, args, close, line}] of calls (not prototypes) in pinned functions."""
    masked = mask_comments(text)
    pins = sites_of(text)
    out = []
    for fname, params, b0, b1 in functions(text):
        if not any(b0 < p[3] < b1 for p in pins):
            continue
        for m in CALL_RE.finditer(masked, b0, b1):
            r = _args(masked, m.end() - 1)
            if not r:
                continue
            args, close = r
            out.append({"f": m.group("f"), "open": m.end() - 1, "args": args, "close": close, "fn": fname,
                        "line": masked.count("\n", 0, m.start()), "b": (b0, b1)})
    return out


def sites(text, idx=None):
    idx = index() if idx is None else idx
    out = []
    cs = calls(text)
    for c in cs:
        ar = set(idx.get(c["f"], {}))
        ar |= {len(o["args"]) for o in cs if o["f"] == c["f"]}          # the arity used elsewhere in the TU
        lower = sorted(n for n in ar if n < len(c["args"]))
        if lower:
            out.append(dict(c, arities=lower))
            if len(out) >= MAX_SITES:
                break
    return out


def truncate(text, c, m):
    """The call cut to its first m arguments."""
    args = c["args"]
    if m == 0:
        return text[:c["open"] + 1] + text[c["close"]:]
    return text[:args[m - 1][1]] + text[c["close"]:]


def reproto(text, f, ps):
    """Every typed file-local prototype of f given the parameter list ps (None if there is none)."""
    masked = mask_comments(text)
    edits = []
    for m in PROTO_RE.finditer(masked):
        if m.group("f") == f and m.group("ps").strip():
            edits.append((m.start("ps"), m.end("ps")))
    if not edits:
        return text
    for a, b in reversed(edits):
        text = text[:a] + ps + text[b:]
    return text


def candidates(text, idx=None):
    idx = index() if idx is None else idx
    sig, n0 = unscored_text(text), len(sites_of(text))
    out, seen = [], {text}
    masked = mask_comments(text)
    allcalls = calls(text)
    for st in sites(text, idx):
        for m in st["arities"]:
            dropped = set()
            for a, b in st["args"][m:]:
                dropped.update(re.findall(r"\b[A-Za-z_]\w*\b", masked[a:b]))
            for scope in ("one", "file"):
                group = [st] if scope == "one" else [c for c in allcalls if c["f"] == st["f"] and len(c["args"]) > m]
                if scope == "file" and len(group) < 2:
                    continue
                # pins first (offsets of the original text), then the calls from the bottom up
                pins = [p for p in sites_of(text) if st["b"][0] < p[3] < st["b"][1]]
                def seg(p):
                    return text[p[3]:p[4]] if p[0] == "stmt" else text[text.rfind("\n", 0, p[3]) + 1:text.find("\n", p[4])]
                named = [p for p in pins if any(re.search(r"\b%s\b" % re.escape(d), seg(p)) for d in dropped)]
                window = [p for p in pins if abs(p[5] - 1 - st["line"]) <= 3]
                for ptag, grp in (("named", named), ("named+window", named + window), ("all", pins)):
                    grp = list({(p[3], p[4]): p for p in grp}.values())
                    if not grp:
                        continue
                    # truncate on the original text (bottom-up), map pins by re-finding them afterwards
                    cur = text
                    for c in sorted(group, key=lambda c: -c["open"]):
                        cur = truncate(cur, c, m)
                    keys = {(g[1], g[2], g[5]) for g in grp}
                    # the calls sit on their own lines, so pin line numbers and texts survive the truncation
                    grp2 = [p for p in sites_of(cur) if (p[1], p[2], p[5]) in keys]
                    if len(grp2) != len(grp):
                        continue
                    cur = erase_many(cur, grp2, clean_notes=True)
                    ps = idx.get(st["f"], {}).get(m)
                    cur = reproto(cur, st["f"], ps if ps is not None else "")
                    if cur in seen or unscored_text(cur) != sig or len(sites_of(cur)) >= n0:
                        continue
                    seen.add(cur)
                    out.append(("%s@%d:%d->%d:%s:%s" % (st["f"], st["line"] + 1, len(st["args"]), m, scope, ptag), cur))
    if os.getenv("T113_ADDRCARRIER", "1") == "1":
        # round 76: dungeon/func_8009A61C needs the arity drop AND the address argument passed directly
        # (t115's addrcarrier_candidates), with the pins erased - neither generator alone reaches it
        try:
            from .t115_carrierfold import addrcarrier_candidates
        except ImportError:
            from t115_carrierfold import addrcarrier_candidates
        for label, cur in list(out):
            for l2, t2, _v in addrcarrier_candidates(cur):
                if t2 not in seen and unscored_text(t2) == sig and len(sites_of(t2)) < n0:
                    seen.add(t2)
                    out.append((label + "+" + l2, t2))
    return out


def _dist(a, b):
    return sum(1 for y in difflib.unified_diff(a, b, lineterm="", n=0)
               if y[:1] in "+-" and not y.startswith(("---", "+++")))


class T:
    name = "t113_sibarity"
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
            return "no call in a pinned function above a declared arity of its callee"
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
