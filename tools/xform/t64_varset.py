"""T64: the variable-set search - a pin erased, then the declaration-level move the lane would make.

WHY.  Round 28's reachability replay (`work/native_lane/r28_dev/tools/reach2.py`, rename-invariant,
depth 2, oracle-ranked) put the CURRENT menu within reach of about one lane-won register text in nine:
of 118 replayed rows, depth-1 exact 7 and depth-2 exact 6.  The declaration-level move inventory of the
same 403 diffs (`ex/reg/lane_won.txt.declmoves.json`) says why: RETYPE-int 50, SPLIT 43, INLINE 31+47,
MERGE-local 24, MERGE-param 8, and the menu only carried the straight-line corner of each (t51 fuse
takes the NEXT statement's sole use, t51 single-set a run of <= 10 statements, natural dropcopy an
`x = y` copy, t60 reuse two straight-line lifetimes).  `xform/varset.py` adds the general moves on a
statement CFG with reaching definitions; this generator searches them.

THE SEARCH.  For each live `ASM_REG` / `ASM_KEEP` / `ASM_KEEP_NV` site, in source order, with the
pin's own variable as the focus:

  * erase that one site (`erase_many(..., clean_notes=True)`) and re-read `sites_of` on the new text -
    every line number, declaration offset and arm label below an erasure has moved, so nothing is
    carried over from the pinned text;
  * depth 1 = `varset.MOVES` on the focus variable and its neighbours, plus the existing menu
    (`natural.GENERATORS`, `t51.candidates` at the mapped site line, `t53.extra_candidates`,
    `t60.reuse_candidates`), round-robin so no family starves another;
  * every candidate is screened with `xform.screen.compile_s`/`sdiff` against the CURRENT pinned
    listing.  The pinned text is byte-exact, so screen distance 0 means identical cc1 output;
  * `vf` is called ONLY on distance-0 candidates that pass `pin_search_engine.improves` - t53's
    finding, re-measured in round 27: every win was accepted on its first, assembly-identical vf call,
    and scoring non-identical candidates never won while spending the whole budget;
  * depth 2 = the same menu on the 8 nearest depth-1 texts, ranked by screen distance and then by the
    `reg_state.metrics` pass-stream distance on the row's deciding pass (combine and greg as t53 does).

Budgets `T64_SCREENS` (600) and `T64_VERIFY` (6) per row; a pass-stream observation costs
`PASS_COST` screens.  The search restarts on the new text after a win.

NO SCAFFOLDING, NO QUALIFIER DRIFT.  `varset` rebuilds every declaration it rewrites from the original
declaration text, and `allowed()` below refuses any candidate - whatever menu produced it - that adds
an `ASM_*` macro, `__asm__`, `volatile`, a fake dependency, a one-trip block or a statement expression,
or that changes the unscored (`port`/`dead`) arms.

`varset_candidates(text)` exposes the same moves as a bounded search menu (<= 48, nearest a live pin
first, the nearest pin's variable as the focus).
"""
import collections
import difflib
import os
import re
import sys
from pathlib import Path

ROOT = next(p for p in Path(__file__).resolve().parents if (p / "tools/common.py").is_file())
if str(ROOT / "tools") not in sys.path:
    sys.path.insert(0, str(ROOT / "tools"))

from common import sha_text
from pin_census import sites_of, unscored_text, asm_blocker
from pin_sites import erase_many
from pin_search_engine import improves
from xform import varset as V
from xform import natural as N
from xform import t51_sched_order as S
from xform import t53_reg_state as T53
from xform import t60_alloc_inputs as T60
from xform.screen import compile_s, sdiff
from xform.reg_state import observe, comparison, metrics
from xform.t12_stmtorder import mask

MENU_CAP = 48
# The round-28 hard rule: a candidate may never change a width or a signedness.  t53's `width:` and
# t15's `narrow` levers do exactly that, so they are dropped from this generator's menu even though
# they are part of the established search.  T64_NO_WIDTH=0 puts them back for an experiment only.
WIDTH_FAMILIES = ("width", "narrow")
PASS_COST = 3               # a -da observation is worth about this many plain screens
BEAM = 8                    # depth-1 texts expanded at depth 2
PIN_MACROS = ("ASM_REG", "ASM_KEEP", "ASM_KEEP_NV")
FORBIDDEN = (r"\bASM_[A-Z0-9_]+", r"\b__asm__\b", r"\bdo\s*\{", r"\bwhile\s*\(\s*0\s*\)",
             r"\bfor\s*\([^;]*;\s*0\s*;", r"\bif\s*\(\s*1\s*\)", r"\(\s*\{")
# a qualifier may not move in EITHER direction: neither the screen nor vf reliably sees a dropped
# `volatile` (round 27's blocking defect), so the count has to be identical, not merely no larger.
QUALIFIERS = (r"\bvolatile\b", r"\bconst\b")


def site_var(s):
    """The variable a pin site names, or None."""
    if s[0] == "reg" and s[6]:
        return s[6].split()[-1].lstrip("*")
    if s[1].startswith("ASM_KEEP") and s[2]:
        v = s[2].split(",")[0].strip().lstrip("*&")
        return v if re.fullmatch(r"[A-Za-z_]\w*", v) else None
    return None


def allowed(original, candidate, signature, npins):
    """No scaffolding may enter a candidate, whichever menu produced it."""
    if unscored_text(candidate) != signature or len(sites_of(candidate)) >= npins:
        return False
    for pat in FORBIDDEN:
        if len(re.findall(pat, candidate)) > len(re.findall(pat, original)):
            return False
    # on the MASKED text: a pin note that mentions `volatile` goes with its erased pin, and a
    # comment must not make a legitimate candidate look like a dropped qualifier
    mo, mc = mask(original), mask(candidate)
    for pat in QUALIFIERS:
        if len(re.findall(pat, mc)) != len(re.findall(pat, mo)):
            return False
    return True


def map_line(old, new, line):
    """Map a 1-based line of `old` onto `new` (erase_many deletes whole lines)."""
    a, b = old.splitlines(), new.splitlines()
    if a == b:
        return line
    sm = difflib.SequenceMatcher(None, a, b, autojunk=False)
    i = line - 1
    for tag, i1, i2, j1, j2 in sm.get_opcodes():
        if i1 <= i < i2:
            return (j1 + (i - i1) if tag == "equal" else j1) + 1
    return max(1, len(b))


def varset_candidates(text):
    """Menu generator: <= MENU_CAP varset moves, the nearest live pin's variable as the focus."""
    pins = sites_of(text)
    focus = next((site_var(s) for s in pins if site_var(s)), None)
    try:
        got = V.candidates(text, focus)
    except Exception:
        return []
    return [("varset:" + label, cand) for label, cand in got[:MENU_CAP]]


def menu(text, line, var, skips=None):
    """The depth-1 menu on an erased text: varset first, then the established families."""
    skips = collections.Counter() if skips is None else skips
    no_width = os.getenv("T64_NO_WIDTH", "1") != "0"
    groups = collections.OrderedDict()
    for move in V.MOVES:
        name = move.__name__.removesuffix("_candidates")
        try:
            groups["varset:" + name] = [("varset:" + l, c) for l, c in move(text, var, skips)]
        except Exception as e:
            skips["error:%s:%s" % (name, type(e).__name__)] += 1
            groups["varset:" + name] = []
    rest = collections.defaultdict(list)
    for gen in N.GENERATORS:
        try:
            for l, c in gen(text):
                rest[l.split(":")[0]].append((l, c))
        except Exception:
            skips["error:natural:" + gen.__name__] += 1
    try:
        for l, c in S.candidates(text, line, var):
            rest["t51:" + l.split(":")[0]].append((l, c))
    except Exception:
        skips["error:t51"] += 1
    if var:
        try:
            for l, c in T53.extra_candidates(text, var):
                rest["t53:" + l.split(":")[0]].append((l, c))
        except Exception:
            skips["error:t53"] += 1
        try:
            for l, c in T60.reuse_candidates(text, var):
                rest["t60:reuse"].append((l, c))
        except Exception:
            skips["error:t60"] += 1
    for k in sorted(rest):
        if no_width and k.split(":")[-1] in WIDTH_FAMILIES:
            skips["width-or-signedness-change"] += len(rest[k])
            continue
        groups[k] = rest[k]
    seen = set()
    out = []
    for level in range(4000):
        left = False
        for k, items in groups.items():
            if level >= len(items):
                continue
            left = True
            label, cand = items[level]
            h = sha_text(cand)
            if h not in seen:
                seen.add(h)
                out.append((k, label, cand))
        if not left:
            break
    return out


class T:
    name = "t64_varset"
    level = 1
    needs_verify = True

    @staticmethod
    def eligible(text, row, census):
        why = asm_blocker(text)
        if why:
            return why
        pins = sites_of(text)
        if not pins:
            return "no live pins"
        if not any(s[1] in PIN_MACROS for s in pins):
            return "no register or keep pins"
        if not row.get("cfg"):
            return "missing compiler recipe"
        return None

    @classmethod
    def apply_verified(cls, text, row, census, vf):
        screens = max(1, int(os.getenv("T64_SCREENS", "600")))
        verifies = max(1, int(os.getenv("T64_VERIFY", "6")))
        passrank = os.getenv("T64_PASSRANK", "1") != "0"
        pins_in = len(sites_of(text))
        usig = unscored_text(text)
        skips = collections.Counter()
        log = dict(pins_in=pins_in, pins_out=pins_in, screen_budget=screens, vf_budget=verifies,
                   screened=0, tried=0, candidates_n=0, compile_failures=0, steps=[], nearest=[],
                   plans=0, erasures=[], moves={}, depth2=0, passobs=0, skips={})
        cur = text
        near, dead, moves = [], set(), collections.Counter()
        try:
            while True:                         # the screen budget bounds this; a win restarts
                won = False
                ref = compile_s(row, cur)
                if ref is None:
                    log["error"] = "reference-build-error"
                    break
                pins = sites_of(cur)
                plans = [(i, s) for i, s in enumerate(pins) if s[1] in PIN_MACROS]
                log["plans"] = len(plans)
                target = None
                seen_cand = set()
                for pi, (idx, site) in enumerate(plans):
                    if log["screened"] >= screens:
                        skips["budget"] += 1
                        break
                    allowance = max(8, (screens - log["screened"]) // max(1, len(plans) - pi))
                    spent0 = log["screened"]
                    var = site_var(site)
                    base = erase_many(cur, [site], clean_notes=True)
                    if unscored_text(base) != usig:
                        skips["in-unscored-arm"] += 1
                        continue
                    log["screened"] += 1
                    erased = compile_s(row, base)
                    if erased is None:
                        log["compile_failures"] += 1
                        skips["erasure-compile-fail"] += 1
                        continue
                    d0 = sdiff(ref, erased)
                    log["erasures"].append({"plan": "pin%d" % idx, "macro": site[1], "var": var, "d0": d0})
                    line = map_line(cur, base, site[5])
                    # ---- depth 1
                    depth1 = []
                    for fam, label, cand in menu(base, line - 1, var, skips):
                        h = sha_text(cand)
                        if h in seen_cand:
                            continue
                        seen_cand.add(h)
                        log["candidates_n"] += 1
                        if not allowed(cur, cand, usig, len(pins)):
                            skips["scaffolding-or-arm"] += 1
                            continue
                        if log["screened"] - spent0 >= allowance * 3 // 4 or log["screened"] >= screens:
                            skips["budget"] += 1
                            break
                        log["screened"] += 1
                        got = compile_s(row, cand)
                        if got is None:
                            log["compile_failures"] += 1
                            skips["compile-fail"] += 1
                            continue
                        d = sdiff(ref, got)
                        moves[fam] += 1
                        near.append((d, "pin%d+%s" % (idx, label), d0))
                        depth1.append((d, fam, label, cand, got))
                        if d != 0:
                            continue
                        won = cls._try(cur, cand, got, vf, log, dead, skips, verifies,
                                       "pin%d+%s" % (idx, label))
                        if won:
                            cur = cand
                            break
                    if won:
                        break
                    # ---- depth 2: the BEAM nearest depth-1 texts
                    depth1.sort(key=lambda z: (z[0], z[2]))
                    seeds = depth1[:max(BEAM * 2, 12)]
                    if passrank and seeds and log["screened"] + PASS_COST * (len(seeds) + 2) < screens:
                        if target is None:
                            target = observe(row, cur)
                            log["screened"] += PASS_COST
                            log["passobs"] += 1
                        phase = "greg"
                        if target and target.get("assembly") is not None:
                            a = observe(row, base)
                            log["screened"] += PASS_COST
                            log["passobs"] += 1
                            if a.get("assembly") is not None:
                                phase = comparison(target, a)["first"]["abs"] or "greg"
                            ranked = []
                            for d, fam, label, cand, got in seeds:
                                if log["screened"] + PASS_COST >= screens:
                                    break
                                o = observe(row, cand, phases=(phase, "combine", "greg"))
                                log["screened"] += PASS_COST
                                log["passobs"] += 1
                                if o.get("assembly") is None:
                                    ranked.append((d, 10 ** 9, fam, label, cand))
                                    continue
                                m = metrics(target, o, phase)
                                ranked.append((d, T53.state_rank(m), fam, label, cand))
                            ranked.sort(key=lambda z: (z[0], z[1], z[3]))
                            seeds = [(z[0], z[2], z[3], z[4], None) for z in ranked]
                    for d, fam, label, seed, _ in seeds[:BEAM]:
                        if log["screened"] - spent0 >= allowance or log["screened"] >= screens:
                            skips["budget"] += 1
                            break
                        sline = map_line(base, seed, line)
                        for fam2, label2, cand in menu(seed, sline - 1, var, skips):
                            h = sha_text(cand)
                            if h in seen_cand:
                                continue
                            seen_cand.add(h)
                            log["candidates_n"] += 1
                            if not allowed(cur, cand, usig, len(pins)):
                                skips["scaffolding-or-arm"] += 1
                                continue
                            if log["screened"] - spent0 >= allowance or log["screened"] >= screens:
                                skips["budget"] += 1
                                break
                            log["screened"] += 1
                            log["depth2"] += 1
                            got = compile_s(row, cand)
                            if got is None:
                                log["compile_failures"] += 1
                                skips["compile-fail"] += 1
                                continue
                            dd = sdiff(ref, got)
                            moves[fam2] += 1
                            step = "pin%d+%s / %s" % (idx, label, label2)
                            near.append((dd, step, d0))
                            if dd != 0:
                                continue
                            won = cls._try(cur, cand, got, vf, log, dead, skips, verifies, step)
                            if won:
                                cur = cand
                                break
                        if won:
                            break
                    if won:
                        break
                if not won:
                    break
        except Exception as e:                  # a parse fault must not fail a sweep row
            log["error"] = repr(e)
        log["skips"] = dict(sorted(skips.items()))
        log["moves"] = dict(sorted(moves.items()))
        log["nearest"] = [{"d": d, "d0": z, "label": l}
                          for d, l, z in sorted(near, key=lambda x: (x[0] is None, x[0]))[:12]]
        log["erasures"] = sorted(log["erasures"], key=lambda e: (e["d0"] is None, e["d0"]))[:8]
        log["pins_out"] = len(sites_of(cur))
        if not log["steps"]:
            return None, log
        return cur, log

    @staticmethod
    def _try(cur, cand, got, vf, log, dead, skips, verifies, step):
        """vf a distance-0 candidate once, deduplicated by (cc1 listing, surviving macros)."""
        if not improves(cur, cand):
            skips["no-improvement"] += 1
            return False
        listing = (sha_text("\n".join(got)), tuple(sorted(s[1] for s in sites_of(cand))))
        if listing in dead:
            skips["same-listing-as-a-failed-verify"] += 1
            return False
        if log["tried"] >= verifies:
            skips["budget"] += 1
            return False
        log["tried"] += 1
        if not vf(cand).get("exact"):
            dead.add(listing)
            return False
        log["steps"].append(step)
        return True
