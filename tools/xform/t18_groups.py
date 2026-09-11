"""T18: a pin GROUP, not a pin - erasure and t15's shape menu against the pins that hold the
same instructions, on rows t15's whole-row band never admits.

APPEARS     a row whose per-site census (`ledger/pins_site.jsonl`) and pair census
            (`ledger/pins_subsets.jsonl`) are current for its text, with a group of pins whose
            joint damage is within T18_BAND words.  A group is `pin_sites.pin_groups`: pins whose
            pair erasure shares (almost) all of the smaller one's residue, and whose retail word
            ranges meet; a pin linked to nothing is a group of one.
RESOLVES    the same mechanisms t15's menu already carries (fence, narrow, dup_after_if, ...), but
            applied where the residue is: t15 strips EVERY pin of a row and so only ever sees rows
            whose whole-row strip is near-clean (T15_BAND), and T2 erases one pin at a time with no
            shape at all.  A row with ten pins and a strip cost of 60 can still hold a pair that
            falls to one fence - 40 % of pin pairs hold the same instructions (PIN_PATTERNS.md
            section 4), and 29 pairs fall only together, invisible to both.
POPULATION  2026-09-11, pinned rows at their current text (pins_site.jsonl + pins_subsets.jsonl,
            the 6..10-pin rows by pairs): 1,378 rows grouped; 980 multi-pin groups, 417 of them
            within 12 words (66 at <= 2, 119 at 3-5, 232 at 6-12); rows of 11+ pins group by
            singles only (no pair census).  Eligible at T18_BAND=12: ~1,400 rows.
RESULT      2026-09-11, first pass, stopped by the owner at ~4,200 of 6,767 rows for a fence study:
            164 rows landed and gated; of its steps, 232 were fences and ~20 real shapes (narrow,
            group erasure, dup_after_if, dead pins).  census.py counts a fence like a pin, so the
            figure is the NET: with t19, the t2 dead-pin pass and t20's fence-free rewrites, 339
            pins out, 224 fences in, -115.  The study (docs/PIN_PATTERNS.md section 9) found half
            the sampled fences hide a natural shape: those shapes go ahead of the fence family
            before this plugin runs again.

Search, per row, cheapest group first and within T18_BUDGET verifies:
  1. erase the group (every candidate is cut from the current text, and the census's own
     measurement stands in for the first verify while the text is the one it measured);
  2. inside the band, t15's menu against that erasure - candidates nearest the group's pins
     first - greedily for T18_ROUNDS rounds, within T18_GROUP_BUDGET verifies;
  3. once something landed, every remaining pin alone (a group gone can leave a pin nothing to
     hold, as t16's `dead:` steps showed).
"""
import os, sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
if str(ROOT / "tools") not in sys.path:
    sys.path.insert(0, str(ROOT / "tools"))
from common import sha_text
from pin_census import sites_of, asm_blocker
from pin_sites import pin_groups, erase_many

try:
    from .t15_shapes import T as T15
except ImportError:                       # pragma: no cover - direct import
    from t15_shapes import T as T15

BAND = int(os.environ.get("T18_BAND", "12"))                 # a group's joint damage must be within
BUDGET = int(os.environ.get("T18_BUDGET", "80"))             # verify runs per row
# menu verifies per group.  The dry run (24 rows, 5 gained) found every win within 7 menu verifies,
# because the menu is ordered nearest the group's pins first; 24 per group spent a row's budget
# on its first three groups without moving a single residue.
GROUP_BUDGET = int(os.environ.get("T18_GROUP_BUDGET", "10"))
ROUNDS = int(os.environ.get("T18_ROUNDS", "2"))              # greedy hill-climb rounds per group
MULTI_ONLY = os.environ.get("T18_MULTI_ONLY") == "1"         # groups of two or more pins only


def _sig(s):
    kind, macro, arg, start, end, line_no, repl = s
    return kind, macro, arg, repl


def _edit_line(a, b):
    """The 1-based line in `a` of the first character where `b` differs from it."""
    lo, hi = 0, min(len(a), len(b))
    while lo < hi:                        # a bisection over prefix equality: texts are tens of KB
        mid = (lo + hi + 1) // 2
        if a[:mid] == b[:mid]:
            lo = mid
        else:
            hi = mid - 1
    return a.count("\n", 0, lo) + 1


def _is_fence(label):
    """t15 menu labels whose candidate adds a `do { } while (0)` barrier."""
    return label.split(":")[0] in ("fence", "fence2", "fencestore", "efence", "fence-return")


def usable(groups):
    return [g for g in groups or [] if g["cost"] is not None and g["cost"] <= BAND
            and (len(g["sites"]) > 1 or not MULTI_ONLY)]


class T:
    name = "t18_groups"
    level = 1
    needs_verify = True

    @staticmethod
    def eligible(text, row, census):
        sites = sites_of(text)
        if not sites:
            return "no live pin site"
        why = asm_blocker(text)
        if why:
            return why
        groups = pin_groups(row["id"], sha_text(text), len(sites))
        if groups is None:
            return "no per-site census at this text"
        if not usable(groups):
            return f"no pin group within band {BAND}"
        return None

    @staticmethod
    def apply_verified(text, row, census, verify_fn):
        sites0 = sites_of(text)
        n = len(sites0)
        groups = usable(pin_groups(row["id"], sha_text(text), n))
        cur, alive = text, list(range(n))     # alive[k] = census index of the k-th live pin in cur
        tried, steps, log = 0, [], []

        def attempt(cand):
            nonlocal tried
            tried += 1
            return verify_fn(cand)

        for g in groups:
            if tried >= BUDGET:
                break
            live = sites_of(cur)
            if [_sig(s) for s in live] != [_sig(sites0[i]) for i in alive]:
                break                         # the pins no longer line up with the census: stop here
            chosen = [live[alive.index(i)] for i in g["sites"]]
            lines = [s[5] for s in chosen]
            base = erase_many(cur, chosen, clean_notes=True)
            rec = {"sites": g["sites"], "est": g["cost"]}
            if cur is text and (len(g["sites"]) == 1 or g["pairs"] and len(g["sites"]) == 2):
                t = g["cost"]                 # measured by the census on exactly this erasure
            else:
                v = attempt(base)
                if v.get("exact"):
                    cur, alive = base, [i for i in alive if i not in g["sites"]]
                    steps.append(f"g{'+'.join(map(str, g['sites']))}:erase")
                    log.append(dict(rec, joint=0))
                    continue
                t = v.get("total")
            rec["joint"] = t
            if t is None or t > BAND:
                log.append(rec)
                continue
            here, here_total, gb, seen, climb, won = base, t, 0, {sha_text(base)}, [], None
            for _ in range(ROUNDS):
                cands = T15._menu(here)
                # real shapes before fences, then nearest the group's pins.  A fence is scaffolding
                # the census counts like a pin: the first full pass removed 236 pins and added 185
                # fences (net -51), so a shape that frees the group without one is tried first.
                cands.sort(key=lambda lc: (_is_fence(lc[0]), min(abs(_edit_line(here, lc[1]) - l) for l in lines)))
                best = None
                for label, cand in cands:
                    if gb >= GROUP_BUDGET or tried >= BUDGET:
                        break
                    h = sha_text(cand)
                    if h in seen:
                        continue
                    seen.add(h)
                    w = attempt(cand)
                    gb += 1
                    if w.get("exact"):
                        won, here = climb + [label], cand
                        break
                    wt = w.get("total")
                    if wt is not None and wt < here_total and (best is None or wt < best[0]):
                        best = (wt, label, cand)
                if won or best is None or gb >= GROUP_BUDGET or tried >= BUDGET:
                    break
                here_total, here = best[0], best[2]
                climb.append(best[1])
            rec.update({"menu": gb, "best": 0 if won else here_total, "climb": "+".join(won or climb) or None})
            log.append(rec)
            if won:
                cur, alive = here, [i for i in alive if i not in g["sites"]]
                steps.append(f"g{'+'.join(map(str, g['sites']))}:" + "+".join(won))
        if not steps:
            return None, {"tried": tried, "pins_in": n, "pins_out": n, "groups": log[:16]}
        i = 0
        while tried < BUDGET:
            live = sites_of(cur)
            if i >= len(live):
                break
            cand = erase_many(cur, [live[i]], clean_notes=True)
            if attempt(cand).get("exact"):
                cur = cand
                steps.append("dead:" + live[i][1])
            else:
                i += 1
        pins_out = len(sites_of(cur))
        return cur, {"step": " ".join(steps), "tried": tried, "pins_in": n, "pins_out": pins_out,
                     "fence": "fence" in " ".join(steps), "groups": log[:16]}
