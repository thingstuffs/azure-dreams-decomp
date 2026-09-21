"""T90: two variables whose live ranges never overlap merged into one - however far apart they stand.

APPEARS     a pinned function holding two locals that are alive at no common point of the program,
            with a whole stretch of unrelated code between them.  Three shapes from the round-63/64
            astra lanes:

              (a) A DEAD-ON-ARRIVAL POINTER and a later integer, nineteen lines apart
                  (dungeon/func_818A4CA0, work/native_lane/r63_astra_moveli):
                      s32 random_value;
                      void *callback;
                      ...
                      callback = &D_80024340;
                      ASM_KEEP(callback);                        <- the pin
                      ((S_818A4CA0_0 *)effect)->unk_10 = callback;
                      ... eighteen statements ...
                      random_value = rand();                     <- the host's own range starts here

              (b) A COUNTER SHARED BETWEEN TWO TRAVERSALS (dungeon/func_813238E8,
                  work/native_lane/r64_astra_bivhide): `actor_index` counts the first do-while,
                  `register s32 actors_left ASM_REG("$16")` counts the second - one retail variable
                  that m2c gave two names, and the second name needed a pin to reach retail's colour.

              (c) the same with the pin standing on the SURVIVING declaration rather than the dying
                  one, which the erase plans reach because every single pin of the row is tried.

RESOLVES    dungeon/func_818A4CA0 (`random_value` carries the callback address first, cast both ways)
            and dungeon/func_813238E8 (`actor_index` counts both loops, the `ASM_REG("$16")`
            declaration gone with it), byte-exact at their recorded recipes.
            MECHANISM, the same one t87 documents and t74 uses from the other side: gcc 2.x gives a
            pseudo with exactly one set (`reg_n_sets == 1`) a priority boost in sched.c's
            `birthing_insn_p`, a preferred fresh colour in local-alloc/global and cse's promotion.
            Merging two values into one variable takes that treatment away from BOTH of them and
            hands the merged pseudo the union of their references, which is what
            `floor_log2(refs) * refs / live_length` in global.c ranks - so the allocation order and
            the schedule move to retail's without any pin.  Where the dying variable's declaration
            CARRIED the pin, the pin does not have to be re-decided at all: the pseudo stops
            existing.
WHY THE ANCESTORS MISS IT
            t87_lifetimemerge asks the two ranges to be CONSECUTIVE: B's first assignment must stand
            within ten lines of A's death (`GAP`) with nothing but pins, braces, comments and
            declarations in between.  Shape (a) has eighteen statements in between and shape (b) has
            a whole loop, so neither is ever offered a pair.  t81_reuselocal needs the guest confined
            to one braced/case/run window and the two declared types to be spelled alike, so it
            cannot see (b)'s `register s32 ... ASM_REG("$16")` against a plain `s32`.
            t66_sameregmerge does have a real CFG, but only pairs two `ASM_REG` declarations naming
            the SAME hard register.  varset.merge_local_candidates has the CFG too and refuses on
            type spelling (`_same_type`), on a register-pinned declaration and on different block
            depths.  This module keeps varset's interference oracle and drops those three refusals,
            taking t87's four rewrite forms to spell the merge.
CANDIDATES  per function with pins, each ORDERED pair (guest, host) of usable locals whose live
            ranges do not interfere on varset's statement CFG (the Chaitin test, definition edge
            included), whose types admit one of t87's forms - `rename` (identical types), `retype`
            (two word-sized integer types), `cast` (pointer <-> word, casts on the writes and the
            reads) or `union` (a one-word union with a field per meaning) - and where the host's
            declaration is in scope over the whole of the guest's range.  The guest's mentions are
            rewritten to the host and its declaration dropped; a pin standing alone on its own line
            is left for the erase plan, which tries the guest's own window, then every single pin of
            the row, then all of them, ranking the results by cc1 listing distance to the pinned text
            and sending only listing-exact ones to `vf`.
            Pairs are ordered so that a guest whose own declaration carries the pin comes first - the
            merge then removes a pin without asking the allocator any new question.
            Refused: a guest or host that is address-taken, volatile, const, static, an array, a
            parameter, a multi-declarator, shadowed, initialised at its declaration, written in a
            loop header, mentioned in a preprocessor arm or on a CFG node this module cannot
            classify; a host named by a statement pin's argument; a rewrite that changes the text of
            a surviving pin (`_kept_ok`); and every pair whose ranges interfere.
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
from xform import natural as N
from xform import screen
from xform import t87_lifetimemerge as T87

MAX_PAIRS = 16
MAX_LOCALS = 90
HOSTS_PER_GUEST = 3
MAX_CANDS = 30
MAX_LISTINGS = 220
MAX_VERIFY = 6
ID = r"[A-Za-z_]\w*"


def _align(text):
    """[(varset Fn, t87/natural fn)] - the two models of the same function, matched by line range."""
    t = N._T(text)
    nats = list(N._functions(t))
    out = []
    for vfn in V.functions(text, Counter()):
        best = None
        for fn in nats:
            if fn.a <= vfn.lo - 1 and vfn.hi <= fn.b:
                if best is None or fn.a > best.a:
                    best = fn
        if best is not None:
            out.append((vfn, best))
    return out


def _decl_of(scope, name):
    for d in scope:
        if d["name"] == name and not d.get("param"):
            return d
    return None


def _loop_spans(vfn):
    """[(first line, last line)] of every loop of the function (a `for`/`while`/`do` block)."""
    out = []
    for i, n in enumerate(vfn.nodes):
        if n.kind not in ("loop", "do"):
            continue
        c = vfn._match_close(i)
        if c is not None:
            out.append((n.line, vfn.nodes[c].line))
    return out


def _text_disjoint(vfn, ms_a, ms_b):
    """The fallback when the CFG refuses: the two ranges do not overlap IN THE TEXT and no loop
    encloses both, so no iteration can carry one value across the other's range.

    The statement CFG is deliberately conservative - an `unknown` node has an edge to every later
    node AND to every label, so one unparsed construct makes a value that dies in the first loop of
    a labelled function look live in the second (dungeon/func_813238E8: `actor_index` and
    `actors_left` count two separate do-whiles forty lines apart and `_interfere` still says yes).
    A text-separated pair outside any common loop is offered as a lower-ranked candidate; the byte
    gate, not this test, is what accepts it.
    """
    return _text_disjoint_spans(_loop_spans(vfn), ms_a, ms_b)


def _text_disjoint_spans(spans, ms_a, ms_b):
    """`_text_disjoint` with the function's loop spans already in hand."""
    la, ha = min(ms_a), max(ms_a)
    lb, hb = min(ms_b), max(ms_b)
    if not (ha < lb or hb < la):
        return False
    lo, hi = min(la, lb), max(ha, hb)
    return not any(s <= lo and hi <= e for s, e in spans)


def _live(vfn, kinds):
    """Cached (live-in, live-out) per variable: `varset._interfere` recomputes both sides for every
    pair, which is a liveness fixpoint per ORDERED PAIR - quadratic where this module is quadratic."""
    return {v: V.liveness(vfn, None, k) for v, k in kinds.items() if k}


def _interferes(vfn, ka, kb, la, lb):
    """varset's Chaitin test, definition edge included, on cached liveness."""
    lia, loa = la
    lib, lob = lb
    for i in range(len(vfn.nodes)):
        if (lia[i] and lib[i]) or (loa[i] and lob[i]):
            return True
        if (ka.get(i) in ("plain", "rmw") and lob[i]) or (kb.get(i) in ("plain", "rmw") and loa[i]):
            return True
    return False


def pairs(text):
    """[(fn, scope, guest decl, host decl, mentions, forms, pinlines, tier)] per disjoint pair."""
    out = []
    sites = sites_of(text)
    for vfn, fn in _align(text):
        pinlines = [s[5] - 1 for s in sites if fn.a < s[5] - 1 < fn.b]
        if not pinlines:
            continue
        masked = "\n".join(fn.ml[fn.a:fn.b + 1])
        scope = T87.scope_decls(fn)
        pinnames = {n for s in sites if s[0] == "stmt" and fn.a < s[5] - 1 < fn.b
                    for n in re.findall(ID, s[2] or "")}
        locs = V.usable_locals(vfn, Counter(), allow_register_pin=True)
        info = {}
        for v in sorted(locs):
            k = vfn.kinds(v)
            d = _decl_of(scope, v)
            if not k or d is None or d.get("init") is not None:
                continue
            if not T87._usable(fn, d, masked):
                continue
            ms = T87._mentions(fn, d, scope)
            if not ms:
                continue
            info[v] = (d, k, ms)
        if len(info) > MAX_LOCALS:
            continue                      # a body this wide is not worth a quadratic pass
        live = _live(vfn, {v: info[v][1] for v in info})
        spans = _loop_spans(vfn)
        for a, (da, ka, ms) in info.items():
            lo, hi = min(ms), max(ms)
            for b, (db, kb, msb) in info.items():
                if a == b or b in pinnames:
                    continue
                forms = T87._forms(da["ty"], db["ty"])
                if db["pinned"]:
                    forms = [f for f in forms if f != "union"]
                if not forms:
                    continue
                if not (db["line"] < lo and db["block"][0] < lo and hi < db["block"][1]):
                    continue                  # the host is not in scope over the guest's range
                if not _interferes(vfn, ka, kb, live[a], live[b]):
                    tier = 0
                elif _text_disjoint_spans(spans, ms, msb):
                    tier = 1
                else:
                    continue
                near = min([abs(p - lo) for p in pinlines] + [abs(p - hi) for p in pinlines])
                out.append((0 if da["pinned"] else (1 if db["pinned"] else 2), tier, near, lo, a, b,
                            fn, scope, da, db, ms, forms, pinlines, tier))
    out.sort(key=lambda z: z[:6])
    # at most HOSTS_PER_GUEST hosts for any one guest, so a single well-placed guest with a dozen
    # same-typed hosts cannot crowd every other dying variable out of the menu
    kept, per = [], Counter()
    for z in out:
        if per[z[4]] >= HOSTS_PER_GUEST:
            continue
        per[z[4]] += 1
        kept.append(z)
        if len(kept) >= MAX_PAIRS:
            break
    return [z[6:] for z in kept]


def candidates(text):
    """[(label, cand, window, must)] for every admissible non-adjacent merge."""
    out, seen = [], set()
    for fn, scope, da, db, ms, forms, pinlines, tier in pairs(text):
        lo, hi = min(ms), max(ms)
        for form in forms:
            cand = T87._build(fn, scope, da, db, lo, hi, ms, [], form, pinlines)
            if cand is None or cand == text or cand in seen:
                continue
            seen.add(cand)
            out.append(("%s-%s:%s->%s@%d" % ("far" if tier == 0 else "text", form, da["name"],
                                             db["name"], lo + 1), cand,
                        (min(lo, da["line"]), hi), (da["line"] + 1,)))
    return out[:MAX_CANDS]


# ------------------------------------------------------------------ the generator

def _plans(sites, rs, win, must=()):
    """The guest's window, then every single pin of the row, then all of them."""
    lo, hi = win[0] + 1, win[1] + 1
    req = [i for i, s in enumerate(rs) if lo <= s[5] <= hi or s[5] in must]
    out = []
    if len(rs) < len(sites):
        out.append([])                                     # the dropped declaration took a pin
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


class T:
    name = "t90_lifetimemerge_far"
    level = 1
    needs_verify = True

    @staticmethod
    def eligible(text, row, census):
        why = asm_blocker(text)
        if why:
            return why
        if not sites_of(text):
            return "no pins"
        return None if candidates(text) else "no disjoint pair in a pinned function"

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
        for label, merged, win, must in candidates(text):
            if listings >= MAX_LISTINGS or verifies >= MAX_VERIFY:
                break
            tried += 1
            rs = sites_of(merged)
            for g in _plans(sites, rs, win, must):
                if listings >= MAX_LISTINGS or verifies >= MAX_VERIFY:
                    break
                cand = erase_many(merged, [rs[i] for i in g], clean_notes=True) if g else merged
                if len(sites_of(cand)) >= pins_in or not T87._kept_ok(sites, cand):
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
