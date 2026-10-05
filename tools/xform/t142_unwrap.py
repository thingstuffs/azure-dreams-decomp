"""T142: a one-trip `do { ... } while (0);` block unwrapped where the bytes do not depend on it (scaffolding; pins untouched).

APPEARS     `do { body } while (0);` in scored code.  A one-trip block emits loop notes (sched region barrier, loop-depth
            ref weighting, calls.c pre-copies), so earlier passes used it to hold an order or a colour.  Round 93's Sonnet
            one-trip lanes (r93_sonnet_ot3-ot14, ~45 blocks) found ~1 in 3 of them held NOTHING any more: the plain
            unwrap was exact (ot14: 6 of 8).
RESOLVES    the body without the wrapper.  The body keeps its braces only when it declares a local (scope); a body
            with a `break`/`continue` that belongs to this one-trip, a macro body (`#define` line) or an unscored
            preprocessor arm is never touched.
SEARCH      every site at once, then each site alone (last first), greedily keeping what stays exact, within T142_MAX
            verifies.
ACCEPTANCE  pins never change; the one-trip count strictly falls; byte-exact.
"""
import os, re, sys
from pathlib import Path
sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
from pin_census import sites_of, arm_labels, HAS_PP_RE

MAX_VERIFY = int(os.environ.get("T142_MAX", "16"))
DO = re.compile(r"\bdo\s*\{")
DECL = re.compile(r"^\s*(?:register\s+|static\s+|const\s+|volatile\s+|unsigned\s+|signed\s+)*"
                  r"(?:[su](?:8|16|32|64)|int|char|short|long|void|f32|[A-Z][A-Za-z0-9_]*|struct\s+\w+|union\s+\w+)\b[\s\*]*\w+\s*(?:\[[^\]]*\]\s*)*(?:=|;)",
                  re.M)


def _mask(text):
    def blank(m):
        return re.sub(r"[^\n]", " ", m.group(0))
    return re.sub(r'/\*.*?\*/|//[^\n]*|"(?:\\.|[^"\\])*"|\'(?:\\.|[^\'\\])*\'', blank, text, flags=re.S)


def _close(m, i):
    """Index of the `}` matching the `{` at i in masked text m, or -1."""
    depth = 0
    for j in range(i, len(m)):
        if m[j] == "{":
            depth += 1
        elif m[j] == "}":
            depth -= 1
            if depth == 0:
                return j
    return -1


def _own_jump(body):
    """True when the body has a break/continue at this one-trip's level (not inside a nested loop or switch)."""
    b = body
    # drop nested loop/switch bodies
    while True:
        mm = re.search(r"\b(?:for|while|switch|do)\b[^{;]*\{", b)
        if not mm:
            break
        c = _close(b, mm.end() - 1)
        if c < 0:
            return True
        b = b[:mm.start()] + b[c + 1:]
    return bool(re.search(r"\b(?:break|continue)\s*;", b))


def sites(text):
    """(start, end, replacement) for each unwrappable one-trip in scored code."""
    m = _mask(text)
    labels = arm_labels(text) if HAS_PP_RE.search(text) else None
    starts = [0] + [i + 1 for i, ch in enumerate(text) if ch == "\n"]
    out = []
    for mm in DO.finditer(m):
        ob = mm.end() - 1
        cb = _close(m, ob)
        if cb < 0:
            continue
        tail = re.match(r"\s*while\s*\(\s*0\s*\)\s*;", m[cb + 1:])
        if not tail:
            continue
        ls = text.rfind("\n", 0, mm.start()) + 1
        if text[ls:mm.start()].lstrip().startswith("#") or text[ls:mm.start()].rstrip().endswith("\\"):
            continue
        if labels is not None:
            ln = max(0, sum(1 for s in starts if s <= mm.start()) - 1)
            if ln < len(labels) and labels[ln] in ("port", "dead"):
                continue
        body_m = m[ob + 1:cb]
        if _own_jump(body_m):
            continue
        body = text[ob + 1:cb]
        end = cb + 1 + tail.end()
        if DECL.search(body_m):
            rep = "{" + body + "}"
        else:
            rep = body.strip("\n")
            # re-indent: drop one level (4 spaces) from the body lines
            rep = "\n".join(l[4:] if l.startswith("    ") else l for l in rep.split("\n")).strip()
            if not rep:
                rep = ""
        out.append((mm.start(), end, rep))
    # keep only outermost sites (a one-trip inside another is handled after its parent)
    res = []
    for s in out:
        if not any(o[0] < s[0] and s[1] <= o[1] for o in out):
            res.append(s)
    return res


def rewrite(text, chosen):
    ss = sites(text); t = text
    for i in sorted(chosen, key=lambda i: -ss[i][0]):
        s, e, rep = ss[i]
        t = t[:s] + rep + t[e:]
    t = re.sub(r"\n[ \t]*\n[ \t]*\n", "\n\n", t)
    return t


def nonetrip(text):
    return len(re.findall(r"while\s*\(\s*0\s*\)", _mask(text)))


class T:
    name = "t142_unwrap"; level = 1
    needs_verify = True

    @staticmethod
    def eligible(text, row, census):
        return None if sites(text) else "no unwrappable one-trip"

    @staticmethod
    def apply_verified(text, row, census, vf):
        ss = sites(text)
        if not ss:
            return None, {"refused": ["no unwrappable one-trip"]}
        n0, o0 = len(sites_of(text)), nonetrip(text); budget = [MAX_VERIFY]; tried = []

        def ok(t):
            if t == text or len(sites_of(t)) != n0 or nonetrip(t) >= o0 or budget[0] <= 0:
                return False
            budget[0] -= 1; tried.append(1)
            return bool(vf(t).get("exact"))

        allidx = list(range(len(ss)))
        allt = rewrite(text, allidx)
        if ok(allt):
            return allt, {"unwrapped": len(ss), "verifies": len(tried)}
        keep = []
        for i in sorted(allidx, key=lambda i: -ss[i][0]):
            if ok(rewrite(text, keep + [i])):
                keep.append(i)
        if keep:
            return rewrite(text, keep), {"unwrapped": len(keep), "of": len(ss), "verifies": len(tried)}
        return None, {"refused": ["no unwrap exact (%d verifies)" % len(tried)]}
