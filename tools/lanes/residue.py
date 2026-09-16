#!/usr/bin/env python3
"""The residue FINGERPRINT of one screen diff, read the same way on both sides of round 33.

    from residue import fingerprint
    fp = fingerprint(ref, cand)          # two `xform.screen.compile_s` listings (cand None -> NOBUILD)

`ref` is always RETAIL's listing and `cand` the other one, on both sides:

  * the census side (`erase_census.py --fp`): ref = the PINNED text's listing (= retail), cand = the
    text with one pin site erased.  The residue is what the pin holds in place.
  * the catalogue side (`perturb_catalog.py`): ref = a PIN-FREE row's listing (= retail, the row is
    byte-exact), cand = the same text with one m2c-style perturbation applied.  The residue is what
    that C move costs.

So in both diffs the `-` lines are retail's and the `+` lines are the m2c-like text's, and a census
fingerprint may be looked up directly among the catalogue's.

Fields
  d       `screen.sdiff` - the number of changed listing lines (None when cand does not build)
  cls     INVISIBLE   d == 0: cc1's listing cannot see the move at all
          MOVED       the same lines in another order (sorted listings equal)
          RECOLOURED  register-anonymised lines equal AND in the same order: only registers differ
          BOTH        register-anonymised MULTISETS equal, order differs (recoloured and moved)
          CHANGED     anything else
          NOBUILD     cand (or ref) is None
  band    "0" | "1-2" | "3-4" | "5-8" | "9-16" | "17-32" | "33+" | "none" (NOBUILD)
  shape   the opcode multiset of the `-` lines then the `+` lines, `dropreg_residue.py`'s format
          (`-move,sw +move,sw`), computed exactly while the diff has at most 8 changed lines and as
          the top-4 opcodes a side, `far:`-prefixed, beyond that
  regs    the (from, to) register pairs of a recolour, at most 6, [] for MOVED/CHANGED/NOBUILD
  regfam  the same pairs by register family (a, v, t, s, sp, ra, gp, fp, at, k, zero, other)
  L0/L1/L2  the three nested keys: cls|band, L0|shape, L1|regfam

The register regex is the HARD-REGISTER one (`rev_residue_check.py`'s), never `\\$\\w+`: `screen.py`
renumbers `$L` labels, and `\\$\\w+` blanks a label exactly like a register, so a pure label renumber
would read as a recolour.  `$L3 -> $L4` is CHANGED here, and a test proves it.
"""
import collections
import difflib
import re

# Hard registers only: `$L12` / `$LC0` are labels and must NOT be anonymised (see the docstring).
HARDREG = re.compile(r"\$(?:zero|at|sp|fp|gp|ra|v[01]|a[0-3]|t\d|s\d|k[01]|f\d+|\d+)\b")
OPC = re.compile(r"^([.\w]+)")
BANDS = ((2, "1-2"), (4, "3-4"), (8, "5-8"), (16, "9-16"), (32, "17-32"))
SHAPE_EXACT_MAX = 8          # changed lines up to which the opcode multiset is exact
MAX_REGS = 6

_NUMFAM = ["zero", "at", "v", "v", "a", "a", "a", "a", "t", "t", "t", "t", "t", "t", "t", "t",
           "s", "s", "s", "s", "s", "s", "s", "s", "t", "t", "k", "k", "gp", "sp", "fp", "ra"]


def anon(lines):
    """The listing with every HARD register replaced by `$R` (labels untouched)."""
    return [HARDREG.sub("$R", l) for l in lines]


def regfamily(r):
    """The register family of one operand token: `$19` -> 's', `$a0` -> 'a', `$f4` -> 'other'."""
    t = r[1:] if r.startswith("$") else r
    if t.isdigit():
        n = int(t)
        return _NUMFAM[n] if 0 <= n < 32 else "other"
    if t in ("zero", "at", "sp", "fp", "gp", "ra"):
        return t
    if len(t) >= 2 and t[0] in "vatsk" and t[1:].isdigit():
        return t[0]
    return "other"


def band_of(d):
    if d is None:
        return "none"
    if d == 0:
        return "0"
    for hi, name in BANDS:
        if d <= hi:
            return name
    return "33+"


def _split(ref, cand):
    """The `-` lines and the `+` lines of the n=0 unified diff, in diff order."""
    minus, plus = [], []
    for ln in difflib.unified_diff(ref, cand, n=0, lineterm=""):
        if ln.startswith(("---", "+++")):
            continue
        if ln[:1] == "-":
            minus.append(ln[1:])
        elif ln[:1] == "+":
            plus.append(ln[1:])
    return minus, plus


def _ops(lines, top=None):
    c = collections.Counter(OPC.match(l).group(1) if OPC.match(l) else "?" for l in lines)
    items = sorted(c.items())
    if top is not None:
        items = sorted(sorted(c.items(), key=lambda kv: (-kv[1], kv[0]))[:top])
    return ",".join("%s%s" % (k, "x%d" % v if v > 1 else "") for k, v in items)[:60]


def _shape(minus, plus, d):
    if not minus and not plus:
        return ""
    if d is not None and d <= SHAPE_EXACT_MAX:
        return "-%s +%s" % (_ops(minus), _ops(plus))
    return "far:-%s +%s" % (_ops(minus, 4), _ops(plus, 4))


def _pairs_from(a, b):
    """The (from, to) register pairs of two corresponding lines, index by index."""
    ra, rb = HARDREG.findall(a), HARDREG.findall(b)
    if len(ra) != len(rb):
        return []
    return [(x, y) for x, y in zip(ra, rb) if x != y]


def _regs(cls, minus, plus):
    """The recolour's register pairs.

    RECOLOURED: the two listings agree line for line once anonymised, so the i-th `-` line and the
    i-th `+` line are the same instruction and the pairs are exact.  BOTH: the order differs, so the
    lines are bucketed by their anonymised form first and paired inside each bucket (a positional
    zip across all of them, as `dropreg_residue.py` does, is noise when the lines are not aligned).
    """
    pairs = []
    if cls == "RECOLOURED":
        for a, b in zip(minus, plus):
            pairs += _pairs_from(a, b)
    elif cls == "BOTH":
        bucket = collections.defaultdict(lambda: ([], []))
        for l in minus:
            bucket[HARDREG.sub("$R", l)][0].append(l)
        for l in plus:
            bucket[HARDREG.sub("$R", l)][1].append(l)
        for key in sorted(bucket):
            m, p = bucket[key]
            for a, b in zip(m, p):
                pairs += _pairs_from(a, b)
    out = []
    for p in pairs:
        if p not in out:
            out.append(p)
    return out[:MAX_REGS]


def _fam(pairs):
    out = []
    for a, b in pairs:
        f = (regfamily(a), regfamily(b))
        if f not in out:
            out.append(f)
    return out[:MAX_REGS]


def classify(ref, cand, d):
    if ref is None or cand is None:
        return "NOBUILD"
    if d == 0:
        return "INVISIBLE"
    if len(ref) == len(cand):
        if sorted(ref) == sorted(cand):
            return "MOVED"
        aref, acand = anon(ref), anon(cand)
        if aref == acand:
            return "RECOLOURED"
        if sorted(aref) == sorted(acand):
            return "BOTH"
    return "CHANGED"


def fingerprint(ref, cand):
    """The residue fingerprint of `cand` against `ref` (both `compile_s` listings)."""
    if ref is None or cand is None:
        return dict(d=None, cls="NOBUILD", band="none", shape="", regs=[], regfam=[],
                    L0="NOBUILD|none", L1="NOBUILD|none|", L2="NOBUILD|none||")
    d = sum(1 for x in difflib.unified_diff(ref, cand, lineterm="", n=0)
            if x[:1] in "+-" and not x.startswith(("+++", "---")))
    cls = classify(ref, cand, d)
    minus, plus = _split(ref, cand)
    shape = _shape(minus, plus, d)
    regs = _regs(cls, minus, plus)
    fam = _fam(regs)
    band = band_of(d)
    L0 = "%s|%s" % (cls, band)
    L1 = "%s|%s" % (L0, shape)
    L2 = "%s|%s" % (L1, ",".join("%s>%s" % f for f in fam))
    return dict(d=d, cls=cls, band=band, shape=shape, regs=[list(r) for r in regs],
                regfam=[list(f) for f in fam], L0=L0, L1=L1, L2=L2)
