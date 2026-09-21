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

KIT WAVE (round 72) - move D of docs/evidence/pin_research_round72_move_table.md, which round 71
            measured and left unbuilt ("t37 verifies up to 40 candidates with `vf` and has no listing
            screen"):  the pin comes off AT THE LOCAL'S OWN WIDTH, paired with an UNPINNED local of
            the same function declared narrower.  dungeon/func_80CBD2E0 `register s32 direction_copy
            ASM_REG("$21")` -> `s16 direction_copy` with the unpinned `s32 direction_index` -> `s16`;
            func_80BC1BA8 / func_80BD9BA8 de-register `register s16 old_state ASM_REG("$16")` and
            `register u8 old_state_byte ASM_REG("$2")` at their own widths while the unpinned
            `u32 height_bits` becomes `u16`; func_80BC7BA8 the same shape one local over.
            Both additions were unreachable before: `candidates()` skipped `new == cur`, so "erase the
            register pin and change nothing else" was not a candidate, and `pinned_locals()` only ever
            listed locals a pin NAMES, so the second local was invisible.  The pair menu is what needs
            the screen: it is ranked by the cc1 listing distance to the pinned text and only the
            listing-exact candidates (plus the two nearest) reach the byte verifier.
            TRADE (recorded, not hidden): before the screen this generator called `vf` on up to 40
            candidates per row in pin-count order; it now calls it at most 5 times, so a candidate
            that is byte-exact at a listing distance above the two nearest is no longer reached.
            That is what makes a 766-row sweep of the bigger menu cost eleven minutes; when the
            pinned text does not compile to a listing the old unscreened path still runs, on the
            base menu only.

Candidates: for each pinned local (most pins first), every other width in INT_TYPES, with that
local's pins erased. The byte verifier decides.
"""
import difflib, re, sys
from pathlib import Path
sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
from pin_census import sites_of, unscored_text
from pin_sites import erase_many
try:
    from .t29_addrsym import mask_comments
    from . import screen
except ImportError:
    from t29_addrsym import mask_comments
    import screen

INT_TYPES = ["s32", "s16", "u16", "u8", "s8", "u32"]
ALIAS = {"M2C_UNK": "s32", "M2C_UNK8": "s8", "M2C_UNK16": "s16", "M2C_UNK32": "s32", "int": "s32",
         "short": "s16", "char": "s8"}
MAX_CANDS = 40
MAX_PAIR_HOSTS = 2             # pinned locals that get a paired partner
MAX_PARTNERS = 3               # unpinned locals offered per host
MAX_PAIRS = 60
MAX_LISTINGS = 110
MAX_VERIFY = 5
DECL_ANY = re.compile(r"^[ \t]*(?:register[ \t]+)?(?P<ty>\w+)[ \t]+(?P<v>[A-Za-z_]\w*)[ \t]*"
                      r"(?:ASM_REG\([^()]*\)[ \t]*)?(?:=[^;]*)?;[ \t]*$", re.M)


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


def retype_only(text, v, new):
    """The declaration of `v` retyped, with no pin erasure (the paired unpinned local)."""
    ds = list(decl_re(v).finditer(mask_comments(text)))
    if len(ds) != 1:
        return None
    a, b = ds[0].span("ty")
    t = text[:a] + new + text[b:]
    return t if unscored_text(t) == unscored_text(text) else None


def partners(text, v):
    """[(name, type)] - integer locals NO pin names, nearest the pinned local `v` first.

    Nearest means: named in a statement that also names `v` (the round-72 rows' pairs all are),
    then by declaration distance."""
    masked = mask_comments(text)
    pinned = set()
    for s in sites_of(text):
        pinned.update(re.findall(r"\b([A-Za-z_]\w*)\b", text[s[3]:s[4]]))
    V = re.compile(r"\b%s\b" % re.escape(v))
    with_v = {u for line in masked.split("\n") if V.search(line)
              for u in re.findall(r"\b([A-Za-z_]\w*)\b", line)}
    home = next((m.start() for m in decl_re(v).finditer(masked)), 0)
    out = []
    for m in DECL_ANY.finditer(masked):
        u, ty = m.group("v"), m.group("ty")
        if u == v or u in pinned or (ty not in INT_TYPES and ty not in ALIAS):
            continue
        if len(list(decl_re(u).finditer(masked))) != 1:
            continue
        out.append(((0 if u in with_v else 1, abs(m.start() - home)), u, ty))
    seen, ranked = set(), []
    for _k, u, ty in sorted(out):
        if u in seen:
            continue
        seen.add(u); ranked.append((u, ty))
    return ranked[:MAX_PARTNERS]


def kit_candidates(text):
    """[(label, text)] - the same-width de-register, and it (or a retype) paired with a partner."""
    out, seen = [], {text}
    pl = pinned_locals(text)
    for v, ty, _n in pl[:MAX_PAIR_HOSTS + 2]:
        cur = ALIAS.get(ty, ty)
        t = retype(text, v, cur)
        if t is not None and t not in seen:
            seen.add(t); out.append(("localwidth:%s:%s>keep" % (v, ty), t))
    allkeep = text                                     # every pinned integer local de-registered
    for v, ty, _n in pl:
        t = retype(allkeep, v, ALIAS.get(ty, ty))
        if t is not None:
            allkeep = t
    if allkeep not in seen:
        seen.add(allkeep); out.append(("localwidth:all>keep", allkeep))
    if pl:
        for u, uty in partners(allkeep, pl[0][0]):
            ucur = ALIAS.get(uty, uty)
            for nw in INT_TYPES:
                if nw == ucur:
                    continue
                cand = retype_only(allkeep, u, nw)
                if cand is None or cand in seen:
                    continue
                seen.add(cand)
                out.append(("pair:all>keep+%s:%s>%s" % (u, uty, nw), cand))
    for v, ty, _n in pl[:MAX_PAIR_HOSTS]:
        cur = ALIAS.get(ty, ty)
        bases = [("keep", cur)] + [(w, w) for w in INT_TYPES if w != cur]
        for btag, w in bases:
            base = retype(text, v, w)
            if base is None:
                continue
            for u, uty in partners(base, v):
                ucur = ALIAS.get(uty, uty)
                for nw in INT_TYPES:
                    if nw == ucur:
                        continue
                    cand = retype_only(base, u, nw)
                    if cand is None or cand in seen:
                        continue
                    seen.add(cand)
                    out.append(("pair:%s>%s+%s:%s>%s" % (v, btag, u, uty, nw), cand))
                    if len(out) >= MAX_PAIRS:
                        return out
    return out


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
        pins_in = len(sites_of(text))
        info = {"pins_in": pins_in, "pins_out": pins_in}
        base = candidates(text)
        base.sort(key=lambda c: len(sites_of(c[1])))               # most pins removed first
        menu, seen = [], {t for _l, t in base}
        menu += base
        menu += [(l, t) for l, t in kit_candidates(text) if t not in seen]
        if not menu:
            return None, dict(info, refused=["no buildable candidate"])
        target = screen.compile_s(row, text)
        if target is None:
            # no listing to rank against: the pre-round-72 behaviour, on the base menu only
            for label, t in base[:MAX_VERIFY]:
                if vf(t).get("exact"):
                    return t, dict(info, label=label, pins_out=len(sites_of(t)))
            return None, dict(info, refused=["no candidate exact at the recorded cell"])
        ranked, listings = [], 0
        for label, cand in menu:
            if listings >= MAX_LISTINGS:
                break
            lst = screen.compile_s(row, cand)
            listings += 1
            if lst is None:
                continue
            d = sum(1 for y in difflib.unified_diff(target, lst, lineterm="", n=0)
                    if y[:1] in "+-" and not y.startswith(("---", "+++")))
            ranked.append((d, len(sites_of(cand)), label, cand))
        ranked.sort(key=lambda x: (x[0], x[1]))
        info.update(listings=listings, menu=len(menu))
        tried = 0
        for d, pins, label, cand in ranked:
            if tried >= MAX_VERIFY or (d and tried >= 2):
                break
            tried += 1
            if vf(cand).get("exact"):
                return cand, dict(info, label=label, step="%s|d%d" % (label, d), pins_out=pins,
                                  tried=tried)
        return None, dict(info, tried=tried,
                          nearest=[{"distance": d, "label": l} for d, _p, l, _c in ranked[:6]])
