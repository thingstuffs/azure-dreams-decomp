"""T125: `volatile` qualifiers dropped where the bytes do not depend on them (readability; pins untouched).

APPEARS     a `volatile` keyword in scored code: a cast `*(volatile T *)p`, a union member `volatile T u`, an
            `extern volatile` declaration, a struct field or a local.  Round-80 goto lanes removed ~40 such sites
            by hand (6 of 9 tries exact): many were m2c/lane scaffolding that no longer holds anything.
RESOLVES    the same text without that one `volatile` token.  A volatile MEM is never combined, cse'd or scheduled
            across another volatile access; where retail's order/form does not need that, plain C is the source.
SEARCH      every site at once, then each site alone (last first), greedily keeping what stays exact, within
            T125_MAX verifies.  Sites in code no byte gate compiles (NON_MATCHING / #if 0 arms) and lines that address PS1
            hardware I/O (0x1F801xxx/0x1F802xxx, 0xBF80xxxx) are never touched: volatile is real semantics there.
ACCEPTANCE  pins never change; the volatile count strictly falls.
"""
import os, re, sys
from pathlib import Path
sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
from pin_census import sites_of, arm_labels, HAS_PP_RE

MAX_VERIFY = int(os.environ.get("T125_MAX", "24"))
VOL = re.compile(r"\bvolatile\b[ \t]*")
# PS1 I/O registers (0x1F801000-0x1F802FFF, and their KSEG1 mirror 0xBF80xxxx): never de-volatilised
HW_IO = re.compile(r"0x(?:1[fF]|[bB][fF])80[12][0-9a-fA-F]{3}\b|\bD_(?:1F|BF)80[12][0-9A-F]{3}\b")


def _mask(text):
    """Comments and string literals blanked (same length), so matches only hit code."""
    def blank(m):
        return re.sub(r"[^\n]", " ", m.group(0))
    return re.sub(r'/\*.*?\*/|//[^\n]*|"(?:\\.|[^"\\])*"', blank, text, flags=re.S)


def sites(text):
    """Offsets of `volatile` tokens in scored code (not in comments, strings or unscored preprocessor arms)."""
    m = _mask(text)
    labels = arm_labels(text) if HAS_PP_RE.search(text) else None
    starts = [0]
    for i, ch in enumerate(text):
        if ch == "\n":
            starts.append(i + 1)
    out = []
    for mm in VOL.finditer(m):
        if labels is not None:
            ln = max(0, sum(1 for s in starts if s <= mm.start()) - 1)
            if ln < len(labels) and labels[ln] in ("port", "dead"):
                continue
        # never inside an asm statement or a macro definition line
        ls = text.rfind("\n", 0, mm.start()) + 1
        if text[ls:mm.start()].lstrip().startswith("#"):
            continue
        le = text.find("\n", mm.end()); le = len(text) if le < 0 else le
        if HW_IO.search(text[ls:le]):
            continue                      # hardware I/O stays volatile: the qualifier is real semantics there
        out.append((mm.start(), mm.end()))
    return out


def rewrite(text, chosen):
    ss = sites(text); t = text
    for i in sorted(chosen, key=lambda i: -ss[i][0]):
        s, e = ss[i]
        t = t[:s] + t[e:]
    return t


def nvol(text):
    return len(sites(text))


class T:
    name = "t125_dropvolatile"; level = 1
    needs_verify = True

    @staticmethod
    def eligible(text, row, census):
        return None if sites(text) else "no volatile in scored code"

    @staticmethod
    def apply_verified(text, row, census, vf):
        ss = sites(text)
        if not ss:
            return None, {"refused": ["no volatile in scored code"]}
        n0, v0 = len(sites_of(text)), len(ss); budget = [MAX_VERIFY]; tried = []

        def ok(t):
            if t == text or len(sites_of(t)) != n0 or nvol(t) >= v0 or budget[0] <= 0:
                return False
            budget[0] -= 1; tried.append(1)
            return bool(vf(t).get("exact"))

        allidx = list(range(len(ss)))
        allt = rewrite(text, allidx)
        if ok(allt):
            return allt, {"volatile": v0, "verifies": len(tried)}
        keep = []
        for i in sorted(allidx, key=lambda i: -ss[i][0]):
            if ok(rewrite(text, keep + [i])):
                keep.append(i)
        if keep:
            t = rewrite(text, keep)
            return t, {"volatile": len(keep), "of": v0, "verifies": len(tried)}
        return None, {"refused": ["no volatile drop exact (%d verifies)" % len(tried)]}
