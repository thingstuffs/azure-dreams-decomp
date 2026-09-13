"""T49: a do-while counter's tail update moved into the loop test, with the pin it freed erased.

APPEARS     `do { ...; v -= 1; } while (v >= 0);` - m2c writes the counter update as the body's last
            statement. 2026-09-13: 162 such loops in 114 pinned rows.
RESOLVES    the fences4 luna lane: in dungeon/func_818B1484 `sample_index -= 1;` (an ASM_SCHED_BARRIER
            before it) became `} while (--sample_index >= 0);` and the fence went. The update written in
            the test is expanded with the loop's exit test, in the loop's last block, so the first
            scheduler orders the body's tail differently; the fence had pinned that order.
            xform/loop_test_increment.py (fence search only) is the narrow case: an increment of a
            counter the body never reads.
SAFE        the update is the body's last statement (only steps of OTHER variables may follow it), the
            test reads v, the body has no `continue` (it would now run the update) and no label; the
            loop's semantics are unchanged.
SEARCH      per loop, in text order: the update moved (pre-increment / pre-decrement in the test), paired
            with one pin erased - a fence first, then by distance from the update (at most T49_NEAR); then
            every qualifying loop of the function moved at once, paired the same way. The first
            byte-exact candidate with fewer live pins wins; the cascade and T2 take it further.
"""
import os, re, sys
from pathlib import Path
sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
from pin_census import sites_of
from pin_sites import erase_many
try:
    from .t29_addrsym import mask_comments
except ImportError:
    from t29_addrsym import mask_comments

MAX_CANDS = int(os.environ.get("T49_MAX", "40"))
NEAR = int(os.environ.get("T49_NEAR", "6"))
ID = r"[A-Za-z_]\w*"
UPD = re.compile(r"[ \t]*(?:(%s)\s*(\+=|-=)\s*1|(%s)\s*(\+\+|--)|(\+\+|--)\s*(%s))\s*;[^\n]*\n" % (ID, ID, ID))
STEP = re.compile(r"[ \t]*(%s)\s*(?:\+\+|--|[+-]=\s*(?:0x[0-9A-Fa-f]+|\d+))\s*;[^\n]*\n" % ID)


def _close(m, i):
    """Index of the `}` matching the `{` at m[i]."""
    d = 0
    for j in range(i, len(m)):
        if m[j] == "{": d += 1
        elif m[j] == "}":
            d -= 1
            if d == 0: return j
    return None


def loops(text):
    """(update_start, update_end, test_start, test_end, var, op) for every movable counter update."""
    m, out = mask_comments(text), []
    for dm in re.finditer(r"\bdo\s*\{", m):
        ob = dm.end() - 1; cb = _close(m, ob)
        if cb is None: continue
        tm = re.match(r"\}\s*while\s*\((.*?)\)\s*;", m[cb:], re.S)
        if not tm: continue
        body = m[ob + 1:cb]
        if re.search(r"\bcontinue\b|^\s*%s\s*:(?!:)" % ID, body, re.M): continue
        lines = [(lm.start() + ob + 1, lm.end() + ob + 1) for lm in re.finditer(r"[^\n]*\n", body)]
        code = [(a, b) for a, b in lines if m[a:b].strip()]
        test = tm.group(1)
        if re.search(r"[-+]{2}|\(", test.replace(" ", "")):
            continue                                       # keep to a plain comparison
        tail, k = [], len(code) - 1                        # the trailing +-1 updates and constant steps
        while k >= 0:
            seg = m[code[k][0]:code[k][1]]
            um, sm = UPD.fullmatch(seg), STEP.fullmatch(seg)
            if not (um or sm):
                break
            if um:
                tail.append((k, um.group(1) or um.group(3) or um.group(6), um.group(2) or um.group(4) or um.group(5)))
            else:
                tail.append((k, sm.group(1), None))
            k -= 1
        for j, (k, v, op) in enumerate(tail):              # nearest the end first
            if op is None or len(re.findall(r"\b%s\b" % re.escape(v), test)) != 1:
                continue
            if any(w == v for _, w, _ in tail[:j]):
                break                                      # a later line steps the same variable
            ts = cb + tm.start(1); te = cb + tm.end(1)
            out.append((code[k][0], code[k][1], ts, te, v, "++" if op in ("+=", "++") else "--"))
            break
    return out


def moved(text, sel):
    t = text
    for us, ue, ts, te, v, op in sorted(sel, key=lambda x: -x[0]):
        test = t[ts:te]
        new_test = re.sub(r"\b%s\b" % re.escape(v), lambda _: op + v, test, count=1)
        t = t[:ts] + new_test + t[te:]                     # the test sits after the update: edit it first
        t = t[:us] + t[ue:]
    return t


def candidates(text):
    out, seen = [], set()
    ls = loops(text)
    groups = [[x] for x in ls] + ([ls] if len(ls) > 1 else [])
    for sel in groups:
        t1 = moved(text, sel)
        at = sel[0][0]
        near = sorted(sites_of(t1), key=lambda s: (s[1] != "ASM_SCHED_BARRIER", abs(s[3] - at)))[:NEAR]
        for s in near:
            t = erase_many(t1, [s], clean_notes=True)
            if t not in seen:
                seen.add(t); out.append(("looptest:%s:%s" % ("+".join(x[4] for x in sel), s[1]), t))
            if len(out) >= MAX_CANDS:
                return out
    return out


class T:
    name = "t49_looptest"; level = 1
    needs_verify = True

    @staticmethod
    def eligible(text, row, census):
        if not sites_of(text):
            return "no pin sites"
        if not loops(text):
            return "no do-while whose last statement updates the counter its test reads"
        return None

    @staticmethod
    def apply_verified(text, row, census, vf):
        n0 = len(sites_of(text))
        cands = [c for c in candidates(text) if len(sites_of(c[1])) < n0]
        if not cands:
            return None, {"refused": ["no candidate with fewer pins"]}
        for label, t in cands:
            if vf(t).get("exact"):
                return t, {"label": label}
        return None, {"refused": ["no candidate exact at the recorded cell"]}
