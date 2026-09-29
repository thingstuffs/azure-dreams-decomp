"""T123: a goto into the function's final `L: return E; }` written as `return E;` (readability; pins untouched).

APPEARS     m2c funnels every exit of a function through one label that ends it: `goto L; ... L: return E; }`.
            Round-80 census: 1,784 forward gotos in ~400 rows target such a return tail (the largest single
            class of the 7,778 forward gotos).
RESOLVES    `return E;` at each goto.  Nothing runs between the jump and E's evaluation, so this is the
            same program; gcc 2.x's jump2 cross-jumping usually merges the duplicated tails back, which the
            verifier decides.  E is copied only while it is short (T123_MAXE characters, default 48) so the
            rewrite reads better, not worse.  When every goto to L went, L is removed (the fall-through into
            the final return stays).  Candidates: every tail at once, then per label, then per goto,
            greedily keeping what stays exact.  The t48 generator did the pin-removing version of this move.
"""
import os, re, sys
from pathlib import Path
sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
from pin_census import sites_of
try:
    from .t122_gotowhile import mask, LABEL, KEYWORDS, gotos
except ImportError:
    from t122_gotowhile import mask, LABEL, KEYWORDS, gotos

MAX_VERIFY = int(os.environ.get("T123_MAX", "16"))
MAXE = int(os.environ.get("T123_MAXE", "48"))
TAIL = re.compile(r"[ \t\n]*(return\b[^;{}]*;)[ \t]*\n?[ \t\n]*\}")


def tails(text):
    """{label: (label_start, label_end, return_stmt)} for labels followed by the function's last `return E; }`."""
    m = mask(text); out = {}
    for lm in LABEL.finditer(m):
        L = lm.group(1)
        if L in KEYWORDS: continue
        r = TAIL.match(m, lm.end())
        if not r: continue
        # the `}` must close a FUNCTION: nothing but whitespace/preprocessor/declarations until the next top level
        close = r.end() - 1; d = 0
        for ch in m[:close]:
            if ch == "{": d += 1
            elif ch == "}": d -= 1
        if d != 1: continue
        stmt = re.sub(r"\s+", " ", text[r.start(1):r.end(1)]).strip()
        if len(stmt) - len("return ;") > MAXE: continue
        out[L] = (lm.start(), lm.end(), stmt)
    return out


def sites(text):
    """[(goto_start, goto_end, label)] for forward gotos into a return tail."""
    m = mask(text); tl = tails(text); out = []
    for g in re.finditer(r"\bgoto[ \t]+(\w+)[ \t]*;", m):
        L = g.group(1)
        if L in tl and tl[L][0] > g.start():
            out.append((g.start(), g.end(), L))
    return out


def rewrite(text, chosen):
    """Replace the gotos at indices `chosen` of sites(text); drop a tail label nothing targets any more."""
    ss = sites(text); tl = tails(text); t = text
    edits = [(ss[i][0], ss[i][1], tl[ss[i][2]][2]) for i in chosen]
    left = {L for j, (_, _, L) in enumerate(ss) if j not in set(chosen)}
    for L in {ss[i][2] for i in chosen} - left:
        s, e, _ = tl[L]
        other = re.findall(r"\bgoto[ \t]+%s[ \t]*;" % re.escape(L), mask(text))
        if len(other) == sum(1 for i in chosen if ss[i][2] == L):
            edits.append((s, e, ""))
    for s, e, rep in sorted(edits, key=lambda x: -x[0]):
        t = t[:s] + rep + t[e:]
    return t


class T:
    name = "t123_returntail"; level = 1
    needs_verify = True

    @staticmethod
    def eligible(text, row, census):
        return None if sites(text) else "no goto into a final return tail"

    @staticmethod
    def apply_verified(text, row, census, vf):
        ss = sites(text)
        if not ss:
            return None, {"refused": ["no goto into a final return tail"]}
        n0, g0 = len(sites_of(text)), gotos(text); budget = [MAX_VERIFY]; tried = []

        def ok(t):
            if t == text or len(sites_of(t)) != n0 or gotos(t) >= g0 or budget[0] <= 0: return False
            budget[0] -= 1; tried.append(1)
            return bool(vf(t).get("exact"))

        allidx = list(range(len(ss)))
        if ok(rewrite(text, allidx)):
            return rewrite(text, allidx), {"gotos": len(ss), "verifies": len(tried)}
        keep = []
        labels = sorted({L for _, _, L in ss}, key=lambda L: -sum(1 for x in ss if x[2] == L))
        if len(labels) > 1:
            for L in labels:
                grp = [i for i, x in enumerate(ss) if x[2] == L]
                if ok(rewrite(text, keep + grp)): keep += grp
        for i in allidx:
            if i not in keep and ok(rewrite(text, keep + [i])): keep.append(i)
        if keep:
            return rewrite(text, keep), {"gotos": len(keep), "of": len(ss), "verifies": len(tried)}
        return None, {"refused": ["no return-tail rewrite exact (%d verifies)" % len(tried)]}
