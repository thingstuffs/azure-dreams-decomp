"""T127: a `goto L;` whose very next statement is `L:` - the jump goes nowhere (readability; pins untouched).

APPEARS     `goto L;` followed (blank lines aside) directly by its own label `L:` - m2c's rendering of a branch to the
            next block, left behind when the code between them was rewritten (17 sites / 16 rows on 2026-09-30;
            r80_sonnet_gd29 deleted two by hand, both exact).
RESOLVES    the goto deleted; the label deleted too when nothing else jumps to it.  Sites in `#if` arms are never
            touched.  All sites at once, then one by one, keeping what stays exact.
ACCEPTANCE  pins never change; the goto count strictly falls.
"""
import os, re, sys
from pathlib import Path
sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
from pin_census import sites_of, arm_labels, HAS_PP_RE
try:
    from .t122_gotowhile import mask, gotos
except ImportError:
    from t122_gotowhile import mask, gotos

MAX_VERIFY = int(os.environ.get("T127_MAX", "12"))
SITE = re.compile(r"[ \t]*\bgoto[ \t]+(\w+)[ \t]*;[ \t]*\n(?:[ \t]*\n)*([ \t]*)\1[ \t]*:[ \t]*;?[ \t]*\n")


def sites(text):
    m = mask(text); out = []
    labels = arm_labels(text) if HAS_PP_RE.search(text) else None
    for s in SITE.finditer(m):
        if labels is not None:
            a = text.count("\n", 0, s.start()); b = text.count("\n", 0, s.end())
            if any(labels[i] != "both" for i in range(a, min(b, len(labels)))):
                continue
        out.append((s.start(), s.end(), s.group(1)))
    return out


def rewrite(text, chosen):
    ss = sites(text); t = text
    for i in sorted(chosen, key=lambda i: -ss[i][0]):
        s, e, L = ss[i]
        seg = t[s:e]
        others = len(re.findall(r"\bgoto[ \t]+%s[ \t]*;" % re.escape(L), mask(t))) - 1
        if others > 0 or re.search(r"&&\s*%s\b" % re.escape(L), t):
            # keep the label: drop only the goto line (and blank lines before the label)
            lab = re.search(r"\n(?:[ \t]*\n)*([ \t]*%s[ \t]*:[ \t]*;?[ \t]*\n)$" % re.escape(L), seg)
            t = t[:s] + lab.group(1) + t[e:]
        else:
            t = t[:s] + t[e:]
    return t


class T:
    name = "t127_gotonext"; level = 1
    needs_verify = True

    @staticmethod
    def eligible(text, row, census):
        return None if sites(text) else "no goto-to-next-label"

    @staticmethod
    def apply_verified(text, row, census, vf):
        ss = sites(text)
        if not ss:
            return None, {"refused": ["no goto-to-next-label"]}
        n0, g0 = len(sites_of(text)), gotos(text); budget = [MAX_VERIFY]; tried = []

        def ok(t):
            if t == text or len(sites_of(t)) != n0 or gotos(t) >= g0 or budget[0] <= 0:
                return False
            budget[0] -= 1; tried.append(1)
            return bool(vf(t).get("exact"))

        allt = rewrite(text, range(len(ss)))
        if ok(allt):
            return allt, {"gotos": g0 - gotos(allt), "verifies": len(tried)}
        keep = []
        for i in sorted(range(len(ss)), key=lambda i: -ss[i][0]):
            if ok(rewrite(text, keep + [i])):
                keep.append(i)
        if keep:
            t = rewrite(text, keep)
            return t, {"gotos": g0 - gotos(t), "verifies": len(tried)}
        return None, {"refused": ["no goto-to-next-label drop exact (%d verifies)" % len(tried)]}
