"""T39: a sign test on a flags word, written as a mask test with an in-place OR.

APPEARS     `if (X >= 0) { ... F = (cast)(X | 0x80000000); ... }`, sometimes through a temporary
            (`sign_bit = 0x80000000; F = X | sign_bit;`), in a row with pins. 2026-09-12: 12 rows.
RESOLVES    fakedep4 lane, dungeon/func_800A57A0: `if (!(X & 0x80000000)) { X |= 0x80000000; F = X; }`
            keeps the loaded value live through its real store; the `$2` pin on X went (pin-free).
Candidates: the mask test with the in-place update, the mask test alone, the in-place update
alone; each with X's (and the temporary's) pins erased, else paired with each of the nearest
single pin erasures. The byte verifier decides.
"""
import re, sys
from pathlib import Path
sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
from pin_census import sites_of, unscored_text
from pin_sites import erase_many
try:
    from .t29_addrsym import mask_comments
    from .t38_unstage import drop_unused
except ImportError:
    from t29_addrsym import mask_comments
    from t38_unstage import drop_unused

TEST = re.compile(r"if\s*\(\s*(?P<x>[A-Za-z_]\w*)\s*>=\s*0\s*\)\s*\{")
SIGN = "0x80000000"
NEAREST = 6
MAX_CANDS = 30


def shapes(text):
    """(x, test span, block end, store match, temp name or None) for each sign test with a sign store."""
    m, out = mask_comments(text), []
    for tm in TEST.finditer(m):
        x = tm.group("x"); X = re.escape(x)
        depth, i = 0, tm.end() - 1
        while i < len(m):
            depth += (m[i] == "{") - (m[i] == "}")
            if depth == 0:
                break
            i += 1
        body = m[tm.end():i]
        temps = set(re.findall(r"\b([A-Za-z_]\w*)\s*=\s*%s\s*;" % SIGN, body))
        k = "|".join([SIGN] + [re.escape(t) for t in temps])
        sm = re.search(r"^(?P<ind>[ \t]*)(?P<lhs>[^;=\n]+?)\s*=\s*(?P<cast>\([^()]*\)\s*)?\(?\s*%s\s*\|\s*(?P<k>%s)\s*\)?\s*;"
                       % (X, k), body, re.M)
        if not sm or re.search(r"[-+*/%&|^<>!]$", sm.group("lhs").strip()):
            continue
        temp = sm.group("k") if sm.group("k") != SIGN else None
        out.append((x, (tm.start(), tm.end()), tm.end() + sm.start(), tm.end() + sm.end(), sm, temp))
    return out


def rewrite(text, sh, test, update):
    x, (ta, tb), sa, sb, sm, temp = sh
    t = text
    if update:
        ind, lhs, cast = sm.group("ind"), sm.group("lhs").strip(), (sm.group("cast") or "").strip()
        rep = "%s%s |= %s;\n%s%s = %s%s;" % (ind, x, SIGN, ind, lhs, cast, x)
    else:
        rep = t[sa:sb].replace(sm.group("k"), SIGN) if temp else t[sa:sb]
    t = t[:sa] + rep + t[sb:]
    if test:
        t = t[:ta] + "if (!(%s & %s)) {" % (x, SIGN) + t[tb:]
    if temp:
        t = re.sub(r"\n[ \t]*%s\s*=\s*%s\s*;[^\n]*(?=\n)" % (re.escape(temp), SIGN), "", t, count=1)
        t = drop_unused(t, temp)
    return t


def candidates(text):
    out, seen = [], set()
    for sh in shapes(text):
        names = [sh[0]] + ([sh[5]] if sh[5] else [])
        for test, update in ((True, True), (True, False), (False, True)):
            t1 = rewrite(text, sh, test, update)
            if unscored_text(t1) != unscored_text(text):
                continue
            own = [s for s in sites_of(t1) if any(re.search(r"\b%s\b" % re.escape(n), t1[s[3]:s[4]]) for n in names)]
            if own:
                pairs = [erase_many(t1, own, clean_notes=True)]
            else:
                near = sorted(sites_of(t1), key=lambda s: abs(s[3] - sh[1][0]))[:NEAREST]
                pairs = [erase_many(t1, [p], clean_notes=True) for p in near]
            for t in pairs:
                t = drop_unused(t, sh[5]) if sh[5] else t
                if t not in seen and unscored_text(t) == unscored_text(text):
                    seen.add(t); out.append(("signbit:%s:%s%s" % (sh[0], "T" if test else "", "U" if update else ""), t))
    return out[:MAX_CANDS]


class T:
    name = "t39_signbit"; level = 1
    needs_verify = True

    @staticmethod
    def eligible(text, row, census):
        if not sites_of(text):
            return "no pin sites"
        if not shapes(text):
            return "no sign test with a sign-bit store"
        return None

    @staticmethod
    def apply_verified(text, row, census, vf):
        cands = [c for c in candidates(text) if len(sites_of(c[1])) < len(sites_of(text))]
        if not cands:
            return None, {"refused": ["no buildable candidate"]}
        for label, t in cands:
            if vf(t).get("exact"):
                return t, {"label": label}
        return None, {"refused": ["no candidate exact at the recorded cell"]}
