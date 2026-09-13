"""T48: a goto into a shared return tail, written as its own return, with the pin it freed erased.

APPEARS     m2c renders a function with several exits as `goto L;` into one `L: [v = E;] return v;`
            tail. 2026-09-13: 1,549 such gotos in 305 pinned rows, 86 of them carrying a fence.
RESOLVES    the fences2 luna lane (work/native_lane/fences2/REPORT.md): in town/func_800B3834 the
            gotos written as direct early returns restored retail's block order and the
            `ASM_SCHED_BARRIER` before the goto went; town/func_8009AA74 the same with its return and
            clamp edges made explicit. An exit written in place is its own basic block with its own
            epilogue jump, which changes block order, delay-slot filling and the first scheduler's
            blocks; the fence had pinned what that shape produces. t21_crossjump sinks shared tails
            too, but for register-pinned pointers only, and it never erases a fence.
SEARCH      per goto with a return tail, in text order: the tail sunk into this goto, then into every
            goto to the same label; each paired with one pin erased, fences first, then by distance
            from the goto (at most T48_NEAR pins). The first byte-exact candidate with fewer live pins
            wins; the cascade and T2 take it further. A label nothing jumps to any more is removed, its
            statements kept (a fall-through still reaches them).
"""
import os, re, sys
from pathlib import Path
sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
from pin_census import sites_of
from pin_sites import erase_many
try:
    from .t29_addrsym import mask_comments
    from .t36_paramwidth import functions
except ImportError:
    from t29_addrsym import mask_comments
    from t36_paramwidth import functions

MAX_CANDS = int(os.environ.get("T48_MAX", "40"))
NEAR = int(os.environ.get("T48_NEAR", "6"))
SIMPLE = re.compile(r"[ \t]*[A-Za-z_][\w.\->\[\]]*[ \t]*=[^=;][^;]*;[ \t]*\n")
PINLINE = re.compile(r"[ \t]*ASM_[A-Z0-9_]+\([^;\n]*\)[ \t]*;[^\n]*\n")


def tails(m, b0, b1):
    """{label: (label_start, label_end, tail_text)} for labels whose statements run straight to a return."""
    out = {}
    for lm in re.finditer(r"^[ \t]*([A-Za-z_]\w*):[ \t]*\n", m[b0:b1], re.M):
        name = lm.group(1)
        if name in ("default",):
            continue
        p = b0 + lm.end(); stmts = []
        while PINLINE.match(m, p):          # `L: ASM_SCHED_BARRIER(); return 0;` - the pins stay at the label
            p = PINLINE.match(m, p).end()
        while True:
            sm = SIMPLE.match(m, p)
            if sm and not re.match(r"[ \t]*(?:case\b|default\b)", m[p:]):
                stmts.append(m[p:sm.end()].strip()); p = sm.end(); continue
            break
        rm = re.match(r"[ \t]*(return\b[^;]*;)[ \t]*\n", m[p:])
        if not rm:
            continue
        out[name] = (b0 + lm.start(), b0 + lm.end(), " ".join(stmts + [rm.group(1)]))
    return out


def sunk(text, m, gotos, label, tail):
    """text with each goto in `gotos` replaced by the tail; the label line removed if unused after."""
    t = text
    for g in sorted(gotos, key=lambda g: -g.start()):
        line0 = t.rfind("\n", 0, g.start()) + 1
        alone = not t[line0:g.start()].strip()
        rep = tail if (alone or tail.count(";") == 1) else "{ %s }" % tail
        t = t[:g.start()] + rep + t[g.end():]
    mm = mask_comments(t)
    if not re.search(r"\bgoto\s+%s\s*;" % re.escape(label), mm) and not re.search(r"&&\s*%s\b" % re.escape(label), mm):
        t = re.sub(r"^[ \t]*%s:[ \t]*\n" % re.escape(label), "", t, count=1, flags=re.M)
    return t


def candidates(text):
    m = mask_comments(text)
    out, seen = [], set()
    for fname, params, b0, b1 in functions(text):
        tl = tails(m, b0, b1)
        if not tl:
            continue
        for g in re.finditer(r"\bgoto\s+([A-Za-z_]\w*)\s*;", m[b0:b1]):      # offsets relative to b0
            label = g.group(1)
            if label not in tl:
                continue
            gs = re.compile(r"\bgoto\s+%s\s*;" % re.escape(label))
            one = [gm for gm in gs.finditer(text) if gm.start() == b0 + g.start()]
            every = [gm for gm in gs.finditer(text) if b0 <= gm.start() < b1]
            for group in ([one] + ([every] if len(every) > 1 else [])):
                if not group:
                    continue
                t1 = sunk(text, m, group, label, tl[label][2])
                ss = sites_of(t1)
                at = group[0].start()
                near = sorted([s for s in ss if b0 <= s[3] < b1 + (len(t1) - len(text))],
                              key=lambda s: (s[1] != "ASM_SCHED_BARRIER", abs(s[3] - at)))[:NEAR]
                for s in near:
                    t = erase_many(t1, [s], clean_notes=True)
                    if t not in seen:
                        seen.add(t); out.append(("gotoreturn:%s:%s:%s" % (label, "all" if len(group) > 1 else "one", s[1]), t))
                    if len(out) >= MAX_CANDS:
                        return out
    return out


class T:
    name = "t48_gotoreturn"; level = 1
    needs_verify = True

    @staticmethod
    def eligible(text, row, census):
        if not sites_of(text):
            return "no pin sites"
        m = mask_comments(text)
        for fname, params, b0, b1 in functions(text):
            tl = tails(m, b0, b1)
            if tl and re.search(r"\bgoto\s+(%s)\s*;" % "|".join(map(re.escape, tl)), m[b0:b1]):
                return None
        return "no goto into a return tail"

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
