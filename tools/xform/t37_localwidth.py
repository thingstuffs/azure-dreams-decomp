"""T37: a pinned integer local declared at another width.

APPEARS     a pinned local of integer type: `register s8 saved ASM_REG("$17");`, or `s16 v;` with
            `ASM_KEEP(v);` somewhere, declared once as a single variable.
RESOLVES    m2c types a local from the width it sees used; the original may have declared it wider,
            narrower or with the other signedness. The declared width sets the pseudo's mode, whether
            a copy into it coalesces with its source, and so its register and schedule. This is the dual
            of t36_paramwidth, which retypes the parameter a pinned local copies (t36 found that lever
            on 57 rows).
POPULATION  pinned integer locals across the tree. First sweep (2026-09-12, 1,456 pinned rows):
            21 rows byte-exact, about 1.4%. Mostly `s32` locals declared `s16`/`u16` (counts, flags,
            directions) and `u16` locals declared `s32` (coordinates, ticks). That sweep's
            declaration regex skipped every `ASM_REG`-bound local. With it fixed, 3,298 pinned
            integer locals are eligible and a `--force` rerun landed 60 more rows (81 in total).

Candidates: for each pinned local (most pins first), every other width in INT_TYPES, with that
local's pins erased. The byte verifier decides.
"""
import re, sys
from pathlib import Path
sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
from pin_census import sites_of, unscored_text
from pin_sites import erase_many
try:
    from .t29_addrsym import mask_comments
except ImportError:
    from t29_addrsym import mask_comments

INT_TYPES = ["s32", "s16", "u16", "u8", "s8", "u32"]
ALIAS = {"M2C_UNK": "s32", "M2C_UNK8": "s8", "M2C_UNK16": "s16", "M2C_UNK32": "s32", "int": "s32",
         "short": "s16", "char": "s8"}
MAX_CANDS = 40


def decl_re(v):
    # `register u32 color_b ASM_REG("$7") = x;` must match too: the first sweep's regex stopped at the
    # macro's parenthesis and skipped every register-bound local (2026-09-12 fix)
    return re.compile(r"^[ \t]*(?:register[ \t]+)?(?P<ty>\w+)[ \t]+%s\b[ \t]*(?:\[[^\]]*\][ \t]*)?"
                      r"(?:ASM_REG\([^()]*\)[ \t]*)?(?:=[^;]*)?;" % re.escape(v), re.M)


def pinned_locals(text):
    """(var, declared type, pin count) for pinned locals with one single-variable integer declaration."""
    masked, count = mask_comments(text), {}
    for s in sites_of(text):
        for v in set(re.findall(r"\b([A-Za-z_]\w*)\b", text[s[3]:s[4]])):
            count[v] = count.get(v, 0) + 1
    out = []
    for v, n in count.items():
        ds = list(decl_re(v).finditer(masked))
        if len(ds) != 1:
            continue
        ty = ds[0].group("ty")
        if ty in INT_TYPES or ty in ALIAS:
            out.append((v, ty, n))
    return sorted(out, key=lambda x: -x[2])


def retype(text, v, new):
    pins = [s for s in sites_of(text) if re.search(r"\b%s\b" % re.escape(v), text[s[3]:s[4]])]
    t = erase_many(text, pins, clean_notes=True) if pins else text
    ds = list(decl_re(v).finditer(mask_comments(t)))
    if len(ds) != 1:
        return None
    a, b = ds[0].span("ty")
    t = t[:a] + new + t[b:]
    if unscored_text(t) != unscored_text(text):
        return None
    return t


def candidates(text):
    out, seen = [], set()
    for v, ty, _ in pinned_locals(text):
        cur = ALIAS.get(ty, ty)
        for new in INT_TYPES:
            if new == cur:
                continue
            t = retype(text, v, new)
            if t is not None and t not in seen:
                seen.add(t); out.append(("localwidth:%s:%s>%s" % (v, ty, new), t))
    return out[:MAX_CANDS]


class T:
    name = "t37_localwidth"; level = 1
    needs_verify = True

    @staticmethod
    def eligible(text, row, census):
        if not sites_of(text):
            return "no pin sites"
        if not pinned_locals(text):
            return "no pinned integer local"
        return None

    @staticmethod
    def apply_verified(text, row, census, vf):
        cands = candidates(text)
        if not cands:
            return None, {"refused": ["no buildable candidate"]}
        cands.sort(key=lambda c: len(sites_of(c[1])))              # most pins removed first
        for label, t in cands:
            if vf(t).get("exact"):
                return t, {"label": label}
        return None, {"refused": ["no candidate exact at the recorded cell"]}
