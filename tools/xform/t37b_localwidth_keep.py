"""T37b: a pinned integer local declared at another width, with ONE of its pins erased.

APPEARS     a pinned local with two or more pins, e.g. `register u32 color_b ASM_REG("$7");` plus
            `ASM_KEEP(color_b);`.
RESOLVES    template1 luna lane, 2026-09-12: `register u8 color_b ASM_REG("$7")` without the
            `ASM_KEEP` is byte-exact in dungeon/func_800D0360. The same holds for `blue` in
            dungeon/func_80AC5000; each row is a template for other overlays. The declared width
            makes the keep unnecessary while the register binding stays. t37 erases every pin of
            the retyped local and so never tried this.
POPULATION  717 pinned integer locals with 2+ pins; the first sweep (2026-09-12, after t37's rerun)
            landed 37 rows. The unit test reproduces the lane's `color_b` edit.
Candidates: for each pinned local with 2+ pins (most pins first), every other width in
t37.INT_TYPES, crossed with each single pin of that local. The byte verifier decides.
"""
import re, sys
from pathlib import Path
sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
from pin_census import sites_of, unscored_text
from pin_sites import erase_many
try:
    from .t29_addrsym import mask_comments
    from .t37_localwidth import INT_TYPES, ALIAS, decl_re, pinned_locals
except ImportError:
    from t29_addrsym import mask_comments
    from t37_localwidth import INT_TYPES, ALIAS, decl_re, pinned_locals

MAX_CANDS = 48


def retype_one(text, v, new, pin):
    t = erase_many(text, [pin], clean_notes=True)
    ds = list(decl_re(v).finditer(mask_comments(t)))
    if len(ds) != 1:
        return None
    a, b = ds[0].span("ty")
    t = t[:a] + new + t[b:]
    return t if unscored_text(t) == unscored_text(text) else None


def candidates(text):
    out, seen = [], set()
    sites = sites_of(text)
    for v, ty, n in pinned_locals(text):
        if n < 2:
            continue
        own = [s for s in sites if re.search(r"\b%s\b" % re.escape(v), text[s[3]:s[4]])]
        cur = ALIAS.get(ty, ty)
        for new in INT_TYPES:
            if new == cur:
                continue
            for p in own:
                t = retype_one(text, v, new, p)
                if t is not None and t not in seen:
                    seen.add(t); out.append(("localwidth1:%s:%s>%s-%s" % (v, ty, new, p[1]), t))
        if len(out) >= MAX_CANDS:
            break
    return out[:MAX_CANDS]


class T:
    name = "t37b_localwidth_keep"; level = 1
    needs_verify = True

    @staticmethod
    def eligible(text, row, census):
        if not sites_of(text):
            return "no pin sites"
        if not any(n >= 2 for _, _, n in pinned_locals(text)):
            return "no pinned integer local with two or more pins"
        return None

    @staticmethod
    def apply_verified(text, row, census, vf):
        cands = candidates(text)
        if not cands:
            return None, {"refused": ["no buildable candidate"]}
        for label, t in cands:
            if vf(t).get("exact"):
                return t, {"label": label}
        return None, {"refused": ["no candidate exact at the recorded cell"]}
