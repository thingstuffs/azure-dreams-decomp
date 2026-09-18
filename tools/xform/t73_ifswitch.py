"""T73: a decompiled switch tree written back as the switch.

APPEARS     two or more consecutive tests of one variable against constants, each dispatching by `goto` or `return`,
            with nothing but labels, gotos, returns and pin lines between them (a fence often sits on an inner label):
                if (state == 1) { goto state_1; }
                if (state >= 2) { goto state_ge_2; }
                if (state == 0) { goto state_0; }
                return;
            state_ge_2:
                ASM_SCHED_BARRIER();
                if (state == 2) { goto update_sprite; }
                return;
MECHANISM   gcc's `expand_case` (stmt.c) lowers a switch to a balanced comparison tree (`emit_case_nodes`) or a
            jump table, and the decompiler wrote that tree back as nested tests in retail's order; written as ifs the
            compiler builds a different tree, and the fence was holding the branch layout. Gemini pack r58_order2
            (round 58), `dungeon/func_81839358`: the tree as a `switch` is byte-exact.
CANDIDATES  per tree: the tree is interpreted for every integer (the constants and their neighbours stand for every
            interval), giving a target per value; targets reached by finitely many values become `case` labels, the
            one target reached by an infinite set becomes `default` (a `return`, a `goto`, or the fall-through when
            it is the code after the tree); two infinite classes, an inner label used from outside the tree, or a
            test on anything but a plain identifier refuse. The tree's pins are erased jointly, then singly; then the
            function's pins jointly. `vf` decides.
"""
import re, sys
from pathlib import Path
sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
from pin_census import sites_of, asm_blocker
try:
    from .t29_addrsym import mask_comments
except ImportError:
    from t29_addrsym import mask_comments

MAX_TREES = 6
MAX_VERIFY = 12
TEST = re.compile(r"^(?P<ind>[ \t]*)if \((?P<v>[A-Za-z_]\w*) (?P<op>==|!=|<|>=|>|<=) (?P<k>-?(?:0x[0-9A-Fa-f]+|\d+))\)\s*(?:\{\s*)?$")
TEST1 = re.compile(r"^(?P<ind>[ \t]*)if \((?P<v>[A-Za-z_]\w*) (?P<op>==|!=|<|>=|>|<=) (?P<k>-?(?:0x[0-9A-Fa-f]+|\d+))\)\s*(?:\{\s*)?(?P<act>goto [A-Za-z_]\w*;|return;)\s*\}?\s*$")
GOTO = re.compile(r"^[ \t]*goto ([A-Za-z_]\w*);\s*$")
RET = re.compile(r"^[ \t]*return;\s*$")
LABEL = re.compile(r"^[ \t]*([A-Za-z_]\w*):\s*$")
PIN = re.compile(r"^[ \t]*ASM_[A-Z0-9_]+\s*\(")
CLOSE = re.compile(r"^[ \t]*\}\s*$")


def parse_tree(ls, i):
    """The pure test tree starting at line i: (last_line, v, [(kind, ...)] items) or None."""
    m = TEST.match(ls[i]) or TEST1.match(ls[i])
    if not m:
        return None
    v, ind = m.group("v"), m.group("ind")
    items, j, ntests = [], i, 0
    while j < len(ls):
        s = ls[j]
        t1 = TEST1.match(s); t = TEST.match(s)
        if t1 and t1.group("v") == v and t1.group("ind") == ind:
            items.append(("test", t1.group("op"), int(t1.group("k"), 0), t1.group("act"))); ntests += 1; j += 1; continue
        if t and t.group("v") == v and t.group("ind") == ind:
            # `if (...) {` NL `goto L;` NL `}`  or  `if (...)` NL `goto L;`
            act = ls[j + 1].strip() if j + 1 < len(ls) else ""
            braced = s.rstrip().endswith("{")
            if not (GOTO.match(act) or RET.match(act)) or (braced and not (j + 2 < len(ls) and CLOSE.match(ls[j + 2]))):
                break
            items.append(("test", t.group("op"), int(t.group("k"), 0), act)); ntests += 1; j += 3 if braced else 2; continue
        if (t or t1) and (t or t1).group("v") != v:
            break
        if not s.strip() or PIN.match(s):
            items.append(("pin", j)); j += 1; continue
        if RET.match(s):
            items.append(("return",)); j += 1; continue
        g = GOTO.match(s)
        if g:
            items.append(("goto", g.group(1))); j += 1; continue
        lb = LABEL.match(s)
        if lb:
            items.append(("label", lb.group(1))); j += 1; continue
        break
    # trim trailing non-test items that are not returns/gotos (a label opening the code after the tree)
    while items and items[-1][0] in ("label", "pin"):
        items.pop(); j -= 1
    if ntests < 2:
        return None
    return j - 1, v, items


def interpret(items, x):
    """Target for value x: ('goto', L) / ('return',) / ('fall',)."""
    labels = {it[1]: n for n, it in enumerate(items) if it[0] == "label"}
    n, steps = 0, 0
    while n < len(items) and steps < 200:
        it = items[n]; steps += 1
        if it[0] == "test":
            op, k, act = it[1], it[2], it[3]
            hit = {"==": x == k, "!=": x != k, "<": x < k, ">=": x >= k, ">": x > k, "<=": x <= k}[op]
            if hit:
                if act.startswith("return"):
                    return ("return",)
                L = act[5:-1]
                if L in labels:
                    n = labels[L] + 1; continue
                return ("goto", L)
            n += 1; continue
        if it[0] == "return":
            return ("return",)
        if it[0] == "goto":
            if it[1] in labels:
                n = labels[it[1]] + 1; continue
            return ("goto", it[1])
        n += 1
    return ("fall",)


def build_switch(text, tree):
    """The switch text for a tree, or None when no switch expresses it."""
    ls = text.split("\n")
    first_line = None
    for n in range(len(ls)):
        pass
    last, v, items = tree
    consts = sorted({it[2] for it in items if it[0] == "test"})
    probes = sorted({c + d for c in consts for d in (-1, 0, 1)} | {min(consts) - 1000, max(consts) + 1000})
    lo, hi = min(consts) - 1000, max(consts) + 1000
    targets = {}
    for x in probes:
        targets.setdefault(interpret(items, x), set()).add(x)
    # a target is finite iff it is not reached at either far probe and every reached x is a constant
    finite, infinite = {}, []
    for tg, xs in targets.items():
        if lo in xs or hi in xs or any(x not in consts for x in xs):
            infinite.append(tg)
        else:
            finite[tg] = sorted(xs)
    if len(infinite) != 1 or not finite:
        return None
    default = infinite[0]
    return v, finite, default


def rewrite(text, start, tree):
    ls = text.split("\n")
    last, v, items = tree
    sw = build_switch(text, tree)
    if sw is None:
        return None, None
    v, finite, default = sw
    labels_inside = {it[1] for it in items if it[0] == "label"}
    masked = mask_comments(text)
    outside = "\n".join(ls[:start] + ls[last + 1:])
    for L in labels_inside:
        if re.search(r"\bgoto %s;" % re.escape(L), outside):
            return None, None
    ind = re.match(r"[ \t]*", ls[start]).group(0)
    out = [ind + "switch (%s) {" % v]
    order = sorted(finite.items(), key=lambda kv: min(kv[1]))
    for tg, xs in order:
        for x in xs:
            out.append(ind + "case %d:" % x if x < 0 or x < 10 else ind + "case 0x%X:" % x)
        out.append(ind + "    " + ("return;" if tg[0] == "return" else "goto %s;" % tg[1]))
    if default[0] != "fall":
        out.append(ind + "default:")
        out.append(ind + "    " + ("return;" if default[0] == "return" else "goto %s;" % default[1]))
    out.append(ind + "}")
    pins_in_tree = [s for s in sites_of(text) if start + 1 <= s[5] <= last + 1]
    new = "\n".join(ls[:start] + out + ls[last + 1:])
    return new, pins_in_tree


def trees(text):
    masked = mask_comments(text)
    ls = masked.split("\n")
    out, i = [], 0
    while i < len(ls):
        tr = parse_tree(ls, i)
        if tr:
            out.append((i, tr)); i = tr[0] + 1
        else:
            i += 1
    return out


class T:
    name = "t73_ifswitch"
    level = 1
    needs_verify = True

    @staticmethod
    def eligible(text, row, census):
        why = asm_blocker(text)
        if why:
            return why
        if not sites_of(text):
            return "no pins"
        for start, tr in trees(text):
            if build_switch(text, tr) is not None:
                return None
        return "no decompiled switch tree expressible as a switch"

    @classmethod
    def apply_verified(cls, text, row, census, vf):
        pins_in, tried, steps, cur = len(sites_of(text)), 0, [], text
        for start, tr in trees(text)[:MAX_TREES]:
            # re-find the tree on the current text (earlier rewrites shift lines)
            live = [(s, t) for s, t in trees(cur) if t[1] == tr[1] and [it for it in t[2] if it[0] == "test"] == [it for it in tr[2] if it[0] == "test"]]
            if not live:
                continue
            start, tr = live[0]
            new, tree_pins = rewrite(cur, start, tr)
            if new is None:
                continue
            base_pins = len(sites_of(cur))
            # the switch text has no pins inside the tree any more (its lines are gone): try as is, then erase more
            plans = [[]] + [[p] for p in sites_of(new)][:8] + ([sites_of(new)] if sites_of(new) else [])
            done = False
            for group in plans:
                if tried >= MAX_VERIFY:
                    break
                from pin_sites import erase_many
                cand = erase_many(new, group, clean_notes=True) if group else new
                if len(sites_of(cand)) >= base_pins:
                    continue
                tried += 1
                if vf(cand).get("exact"):
                    cur, done = cand, True
                    steps.append("switch@%d-erase%d" % (start + 1, len(group)))
                    break
            if done:
                continue
        info = {"tried": tried, "pins_in": pins_in, "pins_out": len(sites_of(cur))}
        if not steps:
            return None, info
        return cur, dict(info, step="+".join(steps))
