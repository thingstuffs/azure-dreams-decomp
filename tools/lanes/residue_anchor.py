#!/usr/bin/env python3
"""Residue anchors: let a pin-anchored generator run on a PIN-FREE, not-yet-exact text (round 76).

    import residue_anchor as RA
    RA.install()                                   # once, after the generators are imported
    lines = RA.residue_lines(row, t0, cand)        # [(C line of cand, weight)], heaviest first
    sites = RA.anchor_sites(cand, lines)           # synthetic site tuples at those statements
    with RA.anchored(cand, sites):
        B.T.eligible(cand, ...); B.T.apply_verified(cand, ...)

Why.  Every generator's detector anchors on a pin site (`sites_of(text)`: the variables named in a pin's span, the
lines near a pin, a pinned declaration).  A generator whose menu is whole-function plans (t110_paramfold, t113, t116)
hands a PIN-FREE intermediate that still misses retail; the second move it needs (a width, a symbol spelling, a
statement split) is one a width / symbol / multiset generator makes - but those refuse pin-free text.  This module
gives such a text a stand-in for the pin: the C statements the listing diff against retail localises.

LOCALISER.  Both texts are compiled with `-g` (cc1 only, `screen._listing`; never the verifier, never a landing):
every cell's cc1 emits `.loc FILE LINE` before the instructions of each source line (checked on 2.6.3, 2.7.2,
2.7.2-cdk, 2.8.0, 2.8.1, 2.91.66, 2.95.2).  The instruction lines are normalised the way `screen.normalise` does
(debug directives - `.def/.begin/.bend/LMn:` - dropped, only lines of the row's own .c file keep a C line) with a
parallel C-line array; `difflib` opcodes between the ORIGINAL pinned text's listing (= retail) and the candidate's
give the candidate instructions that differ, and their C lines are the residue.  A block only retail has is charged
to the candidate lines on either side of the gap.  Weight = changed instructions attributed to the line.

ANCHOR.  `anchor_sites` turns the heaviest residue lines into `("stmt", "RESIDUE", <statement>, start, end, line,
"")` tuples spanning the statement text - detectors read variable names from `text[s[3]:s[4]]` and lines from
`s[5]`.  `install()` patches, in every loaded tools/xform module and in pin_sites, the `sites_of` binding (returns the
anchors for exactly the registered text, the real census for every other text, so a generator's "candidate has fewer
pins" filters see 0 < n) and the `erase_many` / `erase` bindings (a RESIDUE tuple is never erased: it is not a pin).
compose2's own `sites_of` (the win check) and pin_census itself stay unpatched.
"""
import contextlib, difflib, re, sys, threading
from collections import Counter
from pathlib import Path

ROOT = next(p for p in Path(__file__).resolve().parents if (p / "tools/common.py").is_file())
for _p in (ROOT / "tools", ROOT / "tools/xform"):
    if str(_p) not in sys.path:
        sys.path.insert(0, str(_p))
import pin_census                                                            # noqa: E402
import pin_sites                                                             # noqa: E402
import xform.screen as XS                                                    # noqa: E402
from common import sha_text                                                  # noqa: E402

MACRO = "RESIDUE"
MAX_ANCHORS = 6
_REAL_SITES, _REAL_ERASE, _REAL_ERASE_MANY = pin_census.sites_of, pin_census.erase, pin_sites.erase_many
ANCHOR = {}                     # sha(text) -> [synthetic site tuples]
_LOCK = threading.Lock()
_GCACHE = {}                    # (row id, cfg, sha) -> tagged -g listing

_DEBUG = re.compile(r"^(?:\.(?:loc|def|begin|bend|file|stabs|stabn|stabd)\b|\$?L[Mbe]\d+:)")
_SKIP = (".loc", ".frame", ".mask", ".fmask", ".set")
_NOOP_MOVE = re.compile(r"^move (\$\w+),\1$")


# ------------------------------------------------------------------ localiser

def tagged(row, text):
    """(normalised instruction lines, parallel C line of the row's own file or None) of `text`'s -g listing."""
    key = (row["id"], row["cfg"], sha_text(text))
    with _LOCK:
        if key in _GCACHE:
            return _GCACHE[key]
    raw = XS._listing(dict(row, cfg=row["cfg"] + " -g"), text)
    out = None
    if raw is not None:
        base = Path(row["c_path"]).name
        files, cur, inside, lines, locs = set(), None, False, [], []
        for ln in raw:
            s = ln.split("#")[0].strip()
            m = re.match(r'\.file\s+(\d+)\s+"([^"]*)"', s)
            if m:
                if Path(m.group(2)).name == base:
                    files.add(m.group(1))
                continue
            m = re.match(r"\.loc\s+(\d+)\s+(\d+)", s)
            if m:
                cur = int(m.group(2)) if m.group(1) in files else None
                continue
            if not s or _DEBUG.match(s):
                continue
            if s.startswith(".ent"):
                inside = True; lines.append(".ent"); locs.append(None); continue
            if s.startswith(".end"):
                inside = False; continue
            if not inside or s.startswith(_SKIP):
                continue
            s = re.sub(r"\s+", " ", s)
            if _NOOP_MOVE.match(s):
                continue
            lines.append(XS._addr(s)); locs.append(cur)
        out = (XS._labels(lines), locs)
    with _LOCK:
        _GCACHE[key] = out
    return out


def residue_lines(row, ref_text, cand_text):
    """[(1-based C line of cand_text, weight)] where cand's -g listing differs from ref's, heaviest first; None if
    either does not build."""
    a, b = tagged(row, ref_text), tagged(row, cand_text)
    if a is None or b is None:
        return None
    (la, ca), (lb, cb) = a, b
    # C-line map ref -> cand (for a block only the reference listing has)
    cmap = {}
    for tag, i1, i2, j1, j2 in difflib.SequenceMatcher(None, ref_text.split("\n"), cand_text.split("\n"),
                                                       autojunk=False).get_opcodes():
        if tag == "equal":
            for k in range(i2 - i1):
                cmap[i1 + k + 1] = j1 + k + 1
    w = Counter()
    for tag, i1, i2, j1, j2 in difflib.SequenceMatcher(None, la, lb, autojunk=False).get_opcodes():
        if tag == "equal":
            continue
        n = max(i2 - i1, j2 - j1)
        if j2 > j1:
            for j in range(j1, j2):
                if cb[j] is not None:
                    w[cb[j]] += 1
        else:                                 # retail-only block: charge the ref lines' images and the gap's sides
            for i in range(i1, i2):
                if ca[i] is not None and ca[i] in cmap:
                    w[cmap[ca[i]]] += 1
            for j in (j1 - 1, j1):
                if 0 <= j < len(cb) and cb[j] is not None:
                    w[cb[j]] += max(1, n // 2)
    return sorted(w.items(), key=lambda x: (-x[1], x[0]))


def changed_lines(ref_text, cand_text):
    """[(1-based line of cand_text, 1)] the C text diff ref -> cand touches (a deletion: the lines on either side).
    The fallback anchor when the listings agree (d0 - the residue is past cc1, e.g. in the assembler): the only
    localisation left is the first move itself."""
    out = []
    for tag, i1, i2, j1, j2 in difflib.SequenceMatcher(None, ref_text.split("\n"), cand_text.split("\n"),
                                                       autojunk=False).get_opcodes():
        if tag == "equal":
            continue
        out += [(j + 1, 1) for j in range(j1, j2)] if j2 > j1 else [(j1, 1), (j1 + 1, 1)]
    seen = set()
    return [x for x in out if not (x[0] in seen or seen.add(x[0]))]


def _is_stmt(t):
    return bool(t) and t not in ("{", "}", "};") and not t.startswith(("#", "//", "/*")) and bool(re.search(r"[A-Za-z_]", t))


def _statement_line(text, ln):
    """(start, end, line) of the statement on 1-based line `ln`; a `{`/`}` line (a function's entry: the parameter
    loads carry the `{` line note) falls back to the nearest statement line up to 3 lines above (the signature)."""
    ls = text.split("\n")
    if not 1 <= ln <= len(ls):
        return None
    for k in (ln, ln - 1, ln - 2, ln - 3):
        if k < 1:
            break
        s = ls[k - 1]
        if _is_stmt(s.strip()):
            start = sum(len(x) + 1 for x in ls[:k - 1]) + (len(s) - len(s.lstrip()))
            return start, start + len(s.strip()), k
        if k == ln and s.strip() not in ("{", "}", "};"):
            return None
    return None


def anchor_sites(text, lines, maxn=MAX_ANCHORS):
    """Synthetic site tuples for the heaviest residue lines that are statements (in text order)."""
    out, seen = [], set()
    for ln, _w in lines or []:
        span = _statement_line(text, ln)
        if span is None or span[2] in seen:
            continue
        seen.add(span[2])
        out.append(("stmt", MACRO, text[span[0]:span[1]], span[0], span[1], span[2], ""))
        if len(out) >= maxn:
            break
    return sorted(out, key=lambda s: s[3])


# ------------------------------------------------------------------ the hook

def sites_of(text):
    if ANCHOR:
        v = ANCHOR.get(sha_text(text))
        if v is not None:
            return list(v)
    return _REAL_SITES(text)


def erase(text, site, *a, **k):
    if site[1] == MACRO:
        return text
    return _REAL_ERASE(text, site, *a, **k)


def erase_many(text, chosen, clean_notes=False):
    return _REAL_ERASE_MANY(text, [s for s in chosen if s[1] != MACRO], clean_notes=clean_notes)


def install():
    """Patch every loaded tools/xform module (and pin_sites, dead_init) - never pin_census, never compose2."""
    xf = str(ROOT / "tools/xform")
    swap = {id(_REAL_SITES): sites_of, id(_REAL_ERASE): erase, id(_REAL_ERASE_MANY): erase_many}
    n = 0
    for m in list(sys.modules.values()):
        f = getattr(m, "__file__", None) or ""
        if not (f.startswith(xf) or Path(f).name in ("pin_sites.py", "dead_init.py")):
            continue
        for name in ("sites_of", "erase", "erase_many"):
            g = getattr(m, name, None)
            if g is not None and id(g) in swap:
                setattr(m, name, swap[id(g)]); n += 1
    return n


@contextlib.contextmanager
def anchored(text, sites):
    h = sha_text(text)
    ANCHOR[h] = list(sites)
    try:
        yield
    finally:
        ANCHOR.pop(h, None)
