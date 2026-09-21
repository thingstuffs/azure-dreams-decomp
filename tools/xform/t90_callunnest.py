"""T90b: a nested call argument given a name - the dead CALL-RESULT local of the same function.

APPEARS     a pinned statement whose argument is itself a call, with an earlier call-result local of
            the function already dead at that point (dungeon/func_80089CC8, the round-63 astra lane
            work/native_lane/r63_astra_recolour):

                register s32 effect_id ASM_REG("$5");        <- the pin

                effect_result = func_800990FC();             <- the host's only value ...
                target = ((S_8008F428_0 *)effect_state)->unk_11C;
                effect_id = effect_result;                   <- ... read here for the last time
                saved_effect_id = effect_id;
                func_80099290(func_80099194(D_800E0683,
                    func_80099734(target, effect_id)));      <- the nested call, never named

RESOLVES    dungeon/func_80089CC8 byte-exact: the inner call's result written into `effect_result`,
            the outer call reading it, and `saved_effect_id = effect_id;` delayed past the new
            statement - the `register s32 effect_id ASM_REG("$5")` binding then goes.

                effect_id = effect_result;
                effect_result = func_80099734(target, effect_id);
                saved_effect_id = effect_id;
                func_80099290(func_80099194(D_800E0683, effect_result));

            MECHANISM: two things move together.  The host pseudo now has TWO sets, so gcc 2.x stops
            treating it as a single-assignment pseudo - no `birthing_insn_p` boost in sched.c's first
            pass and no preferred fresh colour in local-alloc - and the inner call's return value is
            no longer an anonymous temporary that the outer call's argument setup is free to place
            where it likes: it is a named pseudo that coalesces with $2 and is copied into the
            argument register at the point the source names.  Between them they reproduce retail's
            call sequence, which is what the `$5` binding on `effect_id` was emulating.
WHY THE ANCESTORS MISS IT
            t87_lifetimemerge's `split` form names an unnamed call result, but only where the call is
            a WHOLE right-hand side (`lvalue = call(...);`) standing next to the pin - never a call
            inside another call's argument list.  t80_derivecall and t74_multiset both work on
            assignments, not on nested calls.  natural's dropcopy only removes copies.
CANDIDATES  per statement holding a call inside another call's argument list, innermost first: the
            inner call assigned to each dead call-result host - a plain local of the function whose
            every mention stands on a line strictly BEFORE this statement (so the merge cannot lose a
            value), word-sized or a pointer, not address-taken, volatile, const, static, an array, a
            parameter or a multi-declarator.  Two placements, both offered: the new assignment
            immediately before the statement, and immediately after the host's last mention (the
            exemplar's - it delays whatever stood in between past the new call).  The statement is
            rewritten to read the host and folded onto one line.  Each text is screened with the
            pins erased - the statement's window, then every single pin of the row, then all of them
            - by the cc1 listing against the pinned text, and only listing-exact texts reach `vf`.
"""
import difflib
import os
import re
import sys
from collections import Counter
from pathlib import Path

ROOT = next(p for p in Path(__file__).resolve().parents if (p / "tools/common.py").is_file())
if str(ROOT / "tools") not in sys.path:
    sys.path.insert(0, str(ROOT / "tools"))

from pin_census import sites_of, asm_blocker
from pin_sites import erase_many
from xform import varset as V
from xform import screen
from xform.t29_addrsym import mask_comments
from xform.t36_paramwidth import functions

MAX_SITES = 6
MAX_HOSTS = 4
MAX_CANDS = 24
MAX_LISTINGS = 200
MAX_VERIFY = 6
ID = r"[A-Za-z_]\w*"
CALL_RE = re.compile(r"(?<![\w.])(?<!->)(?P<f>%s)\s*\(" % ID)
WORDY = ("s32", "u32", "int", "unsigned", "long", "s16", "u16")
KEYWORDS = {"if", "for", "while", "switch", "return", "sizeof", "do", "else"}


def _close(s, i):
    """Index just past the `)` that closes the `(` at s[i]."""
    depth = 0
    while i < len(s):
        if s[i] == "(":
            depth += 1
        elif s[i] == ")":
            depth -= 1
            if depth == 0:
                return i + 1
        i += 1
    return None


def statements(m, b0, b1):
    """[(start, end)] of the top-level statements of one function body (masked text offsets)."""
    out, start, paren = [], b0 + 1, 0
    for i in range(b0 + 1, b1):
        c = m[i]
        if c == "(":
            paren += 1
        elif c == ")":
            paren = max(0, paren - 1)
        elif c in "{}:":
            start, paren = i + 1, 0
        elif c == ";" and paren == 0:
            out.append((start, i + 1))
            start = i + 1
    return out


def nested_calls(m, s, e):
    """[(call start, call end)] for calls that stand inside another call's argument list and hold
    no call of their own - the innermost anonymous results of the statement."""
    spans = []
    for cm in CALL_RE.finditer(m, s, e):
        if cm.group("f") in KEYWORDS:
            continue
        c = _close(m, cm.end() - 1)
        if c is None or c > e:
            continue
        spans.append((cm.start(), c, cm.end()))
    out = []
    for a, b, argstart in spans:
        if not any(x < a and b <= y for x, y, _ in spans):
            continue                              # not inside another call
        if any(a < x and y <= b for x, y, _ in spans):
            continue                              # holds a call of its own
        if re.search(r"[^=<>!+\-*/%&|^]=[^=]", m[argstart:b - 1]):
            continue                              # an assignment in the arguments
        out.append((a, b))
    return out


def _hosts(vfn, text, first_line):
    """[(name, decl)] - plain locals of the function whose whole range stands above `first_line`."""
    out = []
    locs = V.usable_locals(vfn, Counter())
    for v, d in sorted(locs.items()):
        ty = (d["base"] + d["stars"]).strip()
        if not (d["stars"] or ty in WORDY or d["base"] in WORDY):
            continue
        kinds = vfn.kinds(v)
        if not kinds:
            continue
        lines = [vfn.nodes[i].line for i in kinds]
        if max(lines) >= first_line:
            continue
        out.append((v, d, max(lines)))
    out.sort(key=lambda z: -z[2])
    return out[:MAX_HOSTS]


def candidates(text):
    """[(label, cand, window, must)] for every admissible naming of a nested call result."""
    m = mask_comments(text)
    sites = sites_of(text)
    lines = text.splitlines(True)
    starts = [0]
    for ln in lines:
        starts.append(starts[-1] + len(ln))

    def line_of(off):
        lo, hi = 0, len(lines) - 1
        while lo < hi:
            mid = (lo + hi + 1) // 2
            if starts[mid] <= off:
                lo = mid
            else:
                hi = mid - 1
        return lo

    out, seen = [], set()
    vfns = {}
    for vfn in V.functions(text, Counter()):
        vfns[(vfn.lo, vfn.hi)] = vfn
    for fname, _params, b0, b1 in functions(text):
        fa, fb = line_of(b0), line_of(b1)
        vfn = next((v for (lo, hi), v in vfns.items() if fa <= lo - 1 and hi <= fb + 1), None)
        if vfn is None:
            continue
        if not [s for s in sites if fa < s[5] - 1 <= fb]:
            continue
        used = 0
        for s, e in statements(m, b0, b1):
            if used >= MAX_SITES:
                break
            calls = nested_calls(m, s, e)
            if not calls:
                continue
            l0, l1 = line_of(s + (len(m[s:e]) - len(m[s:e].lstrip()))), line_of(e - 1)
            hosts = _hosts(vfn, text, l0)
            if not hosts:
                continue
            used += 1
            ind = re.match(r"[ \t]*", lines[l0]).group(0)
            head = starts[l0]
            stmt_raw = text[head:starts[l1] + len(lines[l1])]
            tail = starts[l1] + len(lines[l1])
            for a, b in calls[:2]:
                call_text = " ".join(text[a:b].split())
                new_stmt = ind + " ".join((text[head:a] + "@HOST@" + text[b:tail]).split()) + "\n"
                for v, _d, last in hosts:
                    assign = "%s%s = %s;\n" % (ind, v, call_text)
                    for tag, at in (("before", l0), ("afterhost", last + 1)):
                        if at > l0:
                            continue
                        cand = ("".join(lines[:at]) + assign + "".join(lines[at:l0])
                                + new_stmt.replace("@HOST@", v) + "".join(lines[l1 + 1:]))
                        if cand == text or cand in seen:
                            continue
                        seen.add(cand)
                        out.append(("unnest:%s>%s@%d:%s" % (call_text.split("(")[0], v, l0 + 1, tag),
                                    cand, (at, l1), ()))
    return out[:MAX_CANDS]


def _plans(sites, rs, win):
    lo, hi = win[0] + 1, win[1] + 2
    req = [i for i, s in enumerate(rs) if lo <= s[5] <= hi]
    out = []
    if len(rs) < len(sites):
        out.append([])
    if req:
        out.append(req)
    for i in range(len(rs)):
        g = sorted(set(req) | {i})
        if g not in out:
            out.append(g)
    allp = list(range(len(rs)))
    if allp and allp not in out:
        out.append(allp)
    return out


def _kept_ok(sites, cand):
    want = Counter((s[1], s[2]) for s in sites)
    got = Counter((s[1], s[2]) for s in sites_of(cand))
    return not (got - want)


class T:
    name = "t90_callunnest"
    level = 1
    needs_verify = True

    @staticmethod
    def eligible(text, row, census):
        why = asm_blocker(text)
        if why:
            return why
        if not sites_of(text):
            return "no pins"
        return None if candidates(text) else "no nested call with a dead call-result host"

    @classmethod
    def apply_verified(cls, text, row, census, vf):
        sites = sites_of(text)
        pins_in = len(sites)
        target = screen.compile_s(row, text)
        if target is None:
            return None, {"refused": "pinned text does not build to a listing", "pins_in": pins_in,
                          "pins_out": pins_in}
        listings = verifies = 0
        best, near, rest, tried = None, None, [], 0
        for label, unnested, win, _must in candidates(text):
            if listings >= MAX_LISTINGS or verifies >= MAX_VERIFY:
                break
            tried += 1
            rs = sites_of(unnested)
            for g in _plans(sites, rs, win):
                if listings >= MAX_LISTINGS or verifies >= MAX_VERIFY:
                    break
                cand = erase_many(unnested, [rs[i] for i in g], clean_notes=True) if g else unnested
                if len(sites_of(cand)) >= pins_in or not _kept_ok(sites, cand):
                    continue
                lst = screen.compile_s(row, cand)
                listings += 1
                if lst is None:
                    continue
                d = sum(1 for y in difflib.unified_diff(target, lst, lineterm="", n=0)
                        if y[:1] in "+-" and not y.startswith(("---", "+++")))
                near = d if near is None else min(near, d)
                tag = "%s-erase%d" % (label, len(g))
                if d == 0:
                    verifies += 1
                    if vf(cand).get("exact"):
                        best = (cand, tag)
                        break
                else:
                    rest.append((d, len(rest), cand, tag))
            if best:
                break
        if best is None:
            rest.sort(key=lambda x: (x[0], x[1]))
            for d, _, cand, tag in [x for x in rest if x[0] <= 2][:int(os.environ.get("NEAR_VERIFY", "3"))]:
                if verifies >= MAX_VERIFY:
                    break
                verifies += 1
                if vf(cand).get("exact"):
                    best = (cand, tag)
                    break
        if best is None:
            return None, {"pins_in": pins_in, "pins_out": pins_in, "listings": listings,
                          "verifies": verifies, "nearest": near, "tried": tried}
        cand, tag = best
        return cand, {"pins_in": pins_in, "pins_out": len(sites_of(cand)), "move": tag,
                      "listings": listings, "verifies": verifies, "nearest": 0}
