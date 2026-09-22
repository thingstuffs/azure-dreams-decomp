"""T101: two values of DIFFERENT types merged into one storage - the cross-type half of the merge.

APPEARS     a pinned function in which a value that dies early and a value born later are one pseudo
            in retail but two differently-typed names in the recovered C, so the second one needs a
            pin to reach retail's colour.  Four spellings from the round-71 kit wave (the round-72
            move table's move A2, 64 pins over three rounds, the top line of the combined ranking):

              (a) POINTER into a NARROW integer, the storage widened to a word
                  (dungeon/func_80A1FBBC, work/native_lane/r71_kit_astra3):
                      void *projectile_callback;      u16 frames_left;
                      projectile_callback = D_801741A4;  ASM_KEEP(projectile_callback);
                      ((S_801733BC_2 *)spawned_object)->unk_10 = projectile_callback;
                  ->  u32 frames_left;
                      frames_left = (u32)D_801741A4;
                      ((S_801733BC_2 *)spawned_object)->unk_10 = (void *)frames_left;

              (b) WORD into a NARROW integer, the storage widened, no cast anywhere
                  (dungeon/func_800B8F90: `s32 selected_entity` into `u8 spawn_type` -> `s32`).

              (c) POINTER into a narrow integer with the pin on the pointer's DECLARATION
                  (dungeon/func_8008F228: `register S_800E3E48 *entries ASM_REG("$17")` into
                  `s16 var_s1` -> `u32`, every use cast).

              (d) POINTER into a pointer of ANOTHER pointee type
                  (dungeon/func_81984754: `register Object *prev_object ASM_REG("$5")` in a nested
                  block into the function-level `u8 *allocation_data`, retyped `Object *`, the
                  host's own write cast).

RESOLVES    the merge takes gcc 2.x's one-set pseudo treatment away from both values and hands the
            merged pseudo the union of their references - the same lever t87/t90 document
            (`reg_n_sets == 1` in sched.c `birthing_insn_p`, the `floor_log2(refs) * refs /
            live_length` rank in global.c) - so the allocation order and the schedule move to
            retail's without the pin.  Measured on the four lane rows above.

WHY THE ANCESTORS MISS IT (measured 2026-09-21 on the five round-72 A2 rows)
            t93_scopemerge refuses outright on three of them ("no pinned register declaration in a
            nested block": the declaration is at FUNCTION level) and offers an EMPTY cross-type menu
            on the rest - its donor must have the donee's exact type and pointer depth.
            t87/t90 DO pair function-level declarations over varset's CFG, but
            `t87._forms(tya, tyb)` answers `[]` for a pointer against a narrow integer (shapes a, c)
            and for two pointers of different pointee type (shape d), and its `retype` form never
            retypes the surviving DECLARATION, so shape (b)'s word value would be stored in a `u8`.
            This module keeps t90's pair finder (varset's Chaitin interference test, definition edge
            included, with the text-disjoint fallback) and replaces the form table with a MERGED
            TYPE: the storage is declared as the guest's type, the host's type or a word integer,
            whichever can hold both roles, and a cast is written only where C needs one - where the
            pointer-ness of a role differs from the storage, or two pointer types differ.  An
            integer role never gets a cast: C converts at the assignment, and the widening is the
            whole point of the move.

CANDIDATES  per function with pins, each ordered pair (guest, host) of usable locals whose live
            ranges do not interfere, whose declared types DIFFER, and for which a merged type exists
            that is at least as wide as both roles; the guest's mentions renamed into the host's
            declaration (or the host's into the guest's name, when a surviving statement pin names
            the guest); the host's declaration is ALWAYS respelled, which takes a `register ...
            ASM_REG(...)` on it with the merge - so a pair whose host must KEEP its register pin is
            not on this menu; then the erase ladder - the pins the merge orphans (the guest's own),
            then one more pin, then the guest's window, then every pin of the row - ranked by cc1
            listing distance to the pinned text, with only listing-exact candidates (plus the two
            nearest) sent to the byte verifier.
            `eligible()` builds the whole menu, so a sweep pays about 0.3 s per row before any
            listing: a cascade should test `pairs(text)` instead.
            Refused: a role that is read-modified-written while it needs casts (`p += 4` is not
            expressible through a differently-typed storage), a line mentioning both roles (the
            two rewrites would fight over the same offsets), a multi-line right-hand side under a
            cast, every pair varset's CFG says interferes, and everything t87's `_usable` refuses
            (address-taken, array, volatile/const/static, multi-declarator, initialised).
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

from pin_census import sites_of, asm_blocker, unscored_text
from pin_sites import erase_many
from xform import varset as V
from xform import natural as N
from xform import screen
from xform import t87_lifetimemerge as T87
from xform import t90_lifetimemerge_far as T90

MAX_PAIRS = 140
MAX_LOCALS = 90
HOSTS_PER_GUEST = 14
MAX_TYPES = 3
MAX_CANDS = 400
MAX_LISTINGS = 900
MAX_EXPAND = 4                 # merges whose every erase plan is screened, best listing first
MAX_VERIFY = 6
ID = r"[A-Za-z_]\w*"
WORDS = ("u32", "s32")


# ------------------------------------------------------------------ types

def _cls(ty):
    if not ty:
        return "?"
    if ty.endswith("*"):
        return "p"
    if ty in N.WORD_S or ty in N.WORD_U:
        return "w"
    if ty in N.SMALL:
        return "n"
    return "?"


def _width(ty):
    c = _cls(ty)
    if c in ("p", "w"):
        return 4
    if c == "n":
        return 2 if re.search(r"(?:16|short)", ty) else 1
    return 0


def _needs_cast(role_ty, tm):
    """C needs a cast between the role's meaning and the storage: pointer-ness differs, or two
    pointer types differ.  An integer role in a wider integer storage needs none."""
    a, b = _cls(role_ty), _cls(tm)
    if (a == "p") != (b == "p"):
        return True
    return a == b == "p" and role_ty != tm


def merged_types(tyg, tyh):
    """The storages that can hold both roles, cheapest rewrite first."""
    if tyg == tyh or _cls(tyg) == "?" or _cls(tyh) == "?":
        return []
    need = max(_width(tyg), _width(tyh))
    out = []
    for ty in (tyh, tyg) + WORDS:
        if ty in out or _width(ty) < need:
            continue
        if _cls(ty) == "?":
            continue
        out.append(ty)
    return out[:MAX_TYPES]


# ------------------------------------------------------------------ pairs

def _loop_local(fn, vfn, spans, ms_a, ms_b, name_a, name_b):
    """The last tier: both ranges inside ONE loop body, each value born there before it is read.

    varset's CFG sprays liveness over a node it cannot classify (a `#ifdef` arm, a fragment longer
    than its run limit), and t90's text fallback then refuses every pair inside a common loop
    because a value could in principle be carried across the back edge.  When each role's FIRST
    mention in the loop body is a plain write and neither is mentioned outside it, no value crosses
    the back edge and the two ranges cannot overlap - the argument the CFG would have made.
    Refused when the body holds a label or a goto: control may then re-enter between the ranges.
    """
    lo = min(min(ms_a), min(ms_b))
    hi = max(max(ms_a), max(ms_b))
    body = [(s, e) for s, e in spans if s <= lo and hi <= e]
    if not body:
        return False
    s0, e0 = max(body)                                 # the innermost loop holding both
    if any(k < s0 or k > e0 for k in list(ms_a) + list(ms_b)):
        return False
    for k in range(s0, min(e0 + 1, len(fn.ml))):
        if re.match(r"^[ \t]*(?:goto\b|%s[ \t]*:(?!:))" % ID, fn.ml[k]):
            return False
    return (T87._plain_write(fn.ml, min(ms_a), name_a)
            and T87._plain_write(fn.ml, min(ms_b), name_b))

def pairs(text):
    """[(fn, scope, guest, host, guest mentions, host mentions, kinds, pinnames, pinlines, tier)]."""
    out = []
    sites = sites_of(text)
    for vfn, fn in T90._align(text):
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
            d = T90._decl_of(scope, v)
            if not k or d is None or d.get("init") is not None:
                continue
            if not T87._usable(fn, d, masked) or _cls(d["ty"]) == "?":
                continue
            ms = T87._mentions(fn, d, scope)
            if ms:
                info[v] = (d, k, ms)
        if len(info) > MAX_LOCALS:
            continue
        live = T90._live(vfn, {v: info[v][1] for v in info})
        spans = T90._loop_spans(vfn)
        for a, (da, ka, ms) in info.items():
            lo, hi = min(ms), max(ms)
            for b, (db, kb, msb) in info.items():
                if a == b or da["ty"] == db["ty"]:
                    continue                      # the same-type merge is t87/t90/t93's
                if not merged_types(da["ty"], db["ty"]):
                    continue
                if not (db["line"] < lo and db["block"][0] < lo and hi < db["block"][1]):
                    continue                      # the host is not in scope over the guest's range
                if set(ms) & set(msb):
                    continue                      # one line names both roles: the rewrites collide
                if not T90._interferes(vfn, ka, kb, live[a], live[b]):
                    tier = 0
                elif T90._text_disjoint_spans(spans, ms, msb):
                    tier = 1
                elif _loop_local(fn, vfn, spans, ms, msb, a, b):
                    tier = 2
                else:
                    continue
                pinned_guest = da["pinned"] or a in pinnames
                near = min([abs(p - lo) for p in pinlines] + [abs(p - hi) for p in pinlines])
                gap = min(abs(min(msb) - hi), abs(lo - max(msb)))
                out.append((0 if pinned_guest else (1 if (db["pinned"] or b in pinnames) else 2),
                            tier, near, lo, gap, a, b,
                            (fn, scope, da, db, ms, msb, (ka, kb), pinnames, pinlines, tier)))
    out.sort(key=lambda z: z[:7])
    kept, per = [], Counter()
    for z in out:
        if per[z[5]] >= HOSTS_PER_GUEST:
            continue
        per[z[5]] += 1
        kept.append(z[7])
        if len(kept) >= MAX_PAIRS:
            break
    return kept


# ------------------------------------------------------------------ the rewrite

def _decl_text(d, tm, name):
    """The surviving declaration, retyped (its `register`/ASM_REG dropped when the type changes)."""
    base = T87._spell(tm)
    sep = "" if base.endswith("*") else " "
    reg = "register " if ("register" in d["quals"] and not d["pinned"]) else ""
    return "%s%s%s%s%s;" % (d["ind"], reg, base, sep, name)


def _rewrite(fn, lines, name, keep, role_ty, tm, edits, skip):
    """Every mention of `name` on `lines` renamed to `keep`, cast to/from the storage as C needs."""
    need = _needs_cast(role_ty, tm)
    for k in lines:
        if k in skip:
            continue
        hits = list(N._occ(name).finditer(fn.ml[k]))
        if not hits:
            continue
        ln = edits.get(k, N._nl(fn.t.lines[k]))
        if not need:
            if name != keep:
                for m in reversed(hits):
                    ln = ln[:m.start()] + keep + ln[m.end():]
                edits[k] = ln
            continue
        if T87._plain_write(fn.ml, k, name):
            if len(hits) != 1:
                return False                       # a cast may never land on the left of an `=`
            new = T87._cast_write(ln, hits[0], keep, tm)
            if new is None:
                return False
            edits[k] = new
            continue
        for m in reversed(hits):
            rep = "(%s)%s" % (T87._spell(role_ty), keep)
            if not T87._whole_operand(fn.ml[k], m.start(), m.end()):
                rep = "(%s)" % rep
            ln = ln[:m.start()] + rep + ln[m.end():]
        edits[k] = ln
    return True


def _build(fn, scope, da, db, ms, msb, kinds, pinnames, pinlines, tm):
    """The merged text for one (pair, storage type), or None."""
    ka, kb = kinds
    for d, k in ((da, ka), (db, kb)):
        if _needs_cast(d["ty"], tm) and any(x == "rmw" for x in k.values()):
            return None                            # `p += 4` is not expressible through a cast
    # the surviving NAME is the one a statement pin mentions: renaming it would rewrite a pin this
    # plan may want to keep (dungeon/func_81984754 keeps `ASM_KEEP(prev_object)` over the merge)
    keep = da["name"] if (da["name"] in pinnames and db["name"] not in pinnames) else db["name"]
    skip = {k for k in pinlines if T87.PINONLY_RE.match(fn.ml[k])}
    # a pin standing alone on its own line is never rewritten (t87's convention).  Two kinds of
    # them must be erased by the plan: one naming the side whose NAME the merge drops (the text
    # would not compile), and the guest's own pin, which is the site the move is there to free.
    # `must` is in the line numbering the dropped declaration leaves behind.
    must = sorted((k + 1) - (1 if k > da["line"] else 0) for k in skip
                  if (N._occ(da["name"]).search(fn.ml[k]) and (keep != da["name"] or k in ms))
                  or (N._occ(db["name"]).search(fn.ml[k]) and keep != db["name"]))
    edits = {}
    if not _rewrite(fn, [k for k in ms if k not in skip], da["name"], keep, da["ty"], tm, edits, ()):
        return None
    if not _rewrite(fn, [k for k in msb if k not in skip], db["name"], keep, db["ty"], tm, edits, ()):
        return None
    if da["line"] != da["end"] or db["line"] != db["end"]:
        return None
    edits[db["line"]] = _decl_text(db, tm, keep)
    drop = {da["line"]}
    if not edits:
        return None
    return fn.t.build(edits, drop), must


def candidates(text):
    """[(label, cand, window, must)] for every admissible cross-type merge."""
    out, seen = [], set()
    sig = unscored_text(text)
    for fn, scope, da, db, ms, msb, kinds, pinnames, pinlines, tier in pairs(text):
        lo, hi = min(ms), max(ms)
        for tm in merged_types(da["ty"], db["ty"]):
            built = _build(fn, scope, da, db, ms, msb, kinds, pinnames, pinlines, tm)
            if built is None:
                continue
            cand, must = built
            if cand == text or cand in seen or unscored_text(cand) != sig:
                continue
            seen.add(cand)
            out.append(("%s:%s->%s@%d" % (re.sub(r"\s*\*", "*", tm), da["name"], db["name"], lo + 1),
                        cand, (min(lo, da["line"]), hi), tuple(must)))
            if len(out) >= MAX_CANDS:
                return out
    return out


def plans(rs, must, win):
    """The erase ladder: the pins the merge orphans, then one more, then the guest's window, then
    every pin of the row.  t90's ladder leads with the WINDOW, which on a function-level guest spans
    the whole body and erases every pin at once (measured on dungeon/func_80A1FBBC: the window plan
    took all eight pins and landed at listing distance 26, where the lane's single-pin erase is
    listing-exact)."""
    req = [i for i, s in enumerate(rs) if s[5] in must]
    out = [req]
    for i in range(len(rs)):
        g = sorted(set(req) | {i})
        if g not in out:
            out.append(g)
    wide = sorted(set(req) | {i for i, s in enumerate(rs) if win[0] + 1 <= s[5] <= win[1] + 1})
    if wide not in out:
        out.append(wide)
    allp = list(range(len(rs)))
    if allp not in out:
        out.append(allp)
    return out


# ------------------------------------------------------------------ the generator

class T:
    name = "t101_crossmerge"
    level = 1
    needs_verify = True

    @staticmethod
    def eligible(text, row, census):
        why = asm_blocker(text)
        if why:
            return why
        if not sites_of(text):
            return "no pins"
        return None if pairs(text) else "no cross-type disjoint pair in a pinned function"   # cheap: the menu is built in apply_verified

    @classmethod
    def apply_verified(cls, text, row, census, vf):
        """Two phases, because the erase plans multiply the listings: every merge is screened ONCE
        with its window plan (the pins standing in the guest's range), and only the three nearest
        merges have their remaining plans - each single pin of the row, then all of them - screened
        as well.  A row with sixty candidate merges and seven pins would otherwise ask for five
        hundred listings; this asks for about a hundred."""
        sites = sites_of(text)
        pins_in = len(sites)
        target = screen.compile_s(row, text)
        if target is None:
            return None, {"refused": "pinned text does not build to a listing", "pins_in": pins_in,
                          "pins_out": pins_in}
        listings = verifies = 0
        near, rest, screened = None, [], []

        def score(cand):
            nonlocal listings, near
            lst = screen.compile_s(row, cand)
            listings += 1
            if lst is None:
                return None
            d = sum(1 for y in difflib.unified_diff(target, lst, lineterm="", n=0)
                    if y[:1] in "+-" and not y.startswith(("---", "+++")))
            near = d if near is None else min(near, d)
            return d

        cands = candidates(text)
        for label, merged, win, must in cands:                      # phase 1: one listing each
            if listings >= MAX_LISTINGS:
                break
            rs = sites_of(merged)
            first = plans(rs, must, win)[0]
            cand = erase_many(merged, [rs[i] for i in first], clean_notes=True) if first else merged
            if len(sites_of(cand)) >= pins_in or not T87._kept_ok(sites, cand):
                continue
            d = score(cand)
            if d is None:
                continue
            tag = "%s-erase%d" % (label, len(first))
            rest.append((d, len(rest), cand, tag))
            screened.append((d, label, merged, win, must, cand))
        screened.sort(key=lambda x: (x[0], x[1]))
        for _d, label, merged, win, must, done in screened[:MAX_EXPAND]:   # phase 2: every plan
            rs = sites_of(merged)
            for g in plans(rs, must, win):
                if listings >= MAX_LISTINGS:
                    break
                cand = erase_many(merged, [rs[i] for i in g], clean_notes=True) if g else merged
                if cand == done or len(sites_of(cand)) >= pins_in or not T87._kept_ok(sites, cand):
                    continue
                d = score(cand)
                if d is None:
                    continue
                rest.append((d, len(rest), cand, "%s-erase%d" % (label, len(g))))
        best = None
        rest.sort(key=lambda x: (x[0], x[1]))
        seen, uniq = set(), []
        for x in rest:
            if x[2] in seen:
                continue
            seen.add(x[2])
            uniq.append(x)
        order = ([x for x in uniq if x[0] == 0][:MAX_VERIFY - 2]
                 + [x for x in uniq if 0 < x[0] <= 2][:int(os.environ.get("NEAR_VERIFY", "2"))])
        for d, _i, cand, tag in order:
            if verifies >= MAX_VERIFY:
                break
            verifies += 1
            if vf(cand).get("exact"):
                best = (cand, tag)
                break
        if best is None:
            return None, {"pins_in": pins_in, "pins_out": pins_in, "listings": listings,
                          "verifies": verifies, "nearest": near, "tried": len(cands)}
        cand, tag = best
        return cand, {"pins_in": pins_in, "pins_out": len(sites_of(cand)), "move": tag,
                      "listings": listings, "verifies": verifies, "nearest": 0}
