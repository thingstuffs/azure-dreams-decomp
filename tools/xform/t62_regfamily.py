"""T62: erase a row's whole same-hard-register ASM_REG family at once.

APPEARS: a row carries two or more live ASM_REG pins naming the SAME hard register, and each of
them erased alone gives a small pure reg-rename residue (the value moves to some other free
register while its siblings stay correct).

RESOLVES: those pins are not independent. A pin is a hard-register USE, so it puts its register
into the competition as an occupied resource for every other allocno on the row: gcc 2.x
global.c find_reg masks regs_someone_prefers on pass 0 and local-alloc.c find_free_reg masks
regs_live_at over the quantity's range, so while ANY sibling still holds register R the allocator
cannot hand R to the value just un-pinned - an exclusion, never a mere preference, and priority
can never beat it. The erasure unit is therefore the whole family, not the site. Erase every pin
on that register together and the allocator reproduces retail for all of them at once; siblings
on OTHER registers then often come free one by one, because the freed register is back in the
pool for them too.

Built by the alloc35 opus pack (work/native_lane/alloc35/REPORT.md, "The general rule this pack
produced", 2026-09-14). On dungeon/func_80AF3470 the four $7 (*_product) pins are 2 subs each
alone and collectively exact; with them gone four more pins fell singly, 10 -> 2.

Scope and limits. Current text only; no atlas/row-name lookup, no flags, no added statements,
asm or volatile, no edit that changes an unscored (port/dead) arm - unscored_text is compared on
every candidate before a vf call is spent. Default budget 8 vf calls per row (T62_VERIFY), which
covers the observed shape "one large family + the singles it frees". Families are tried largest
first, then by register number; every family erasure that verifies exact is KEPT, and the search
continues from that text, so the returned text is the one with the fewest pins that verified.
The single-site pass runs only when at least one family fell: on an untouched row single erasures
are t2's greedy pass again and would spend the whole budget re-proving its misses.
"""
import os
from pathlib import Path
import sys

ROOT = next(p for p in Path(__file__).resolve().parents if (p / "tools/common.py").is_file())
if str(ROOT / "tools") not in sys.path:
    sys.path.insert(0, str(ROOT / "tools"))
from common import sha_text
from pin_census import sites_of, unscored_text, asm_blocker
from pin_sites import erase_many

VERIFY_BUDGET = 8

# $N and the MIPS ABI names, the o32 spellings a pin can carry. sites_of() has already
# stripped the '$' (pin_census.REG_RE group 2), so a site argument reads "7" or "a3".
NAMES = {"zero": 0, "at": 1, "v0": 2, "v1": 3, "a0": 4, "a1": 5, "a2": 6, "a3": 7,
         "t0": 8, "t1": 9, "t2": 10, "t3": 11, "t4": 12, "t5": 13, "t6": 14, "t7": 15,
         "s0": 16, "s1": 17, "s2": 18, "s3": 19, "s4": 20, "s5": 21, "s6": 22, "s7": 23,
         "t8": 24, "t9": 25, "k0": 26, "k1": 27, "gp": 28, "sp": 29, "fp": 30, "s8": 30,
         "ra": 31, "hi": 64, "lo": 65}


def hard_register(arg):
    """The register a pin argument names, as a number. An unrecognised spelling keeps its own
    text as its key, so two odd spellings still group with themselves and never with a number."""
    s = str(arg).strip().strip('"').lstrip("$").lower()
    if s.isdigit():
        return int(s)
    return NAMES.get(s, s)


def reg_sites(text_or_sites):
    """The live ASM_REG sites of a text (or of an already-taken sites_of list)."""
    sites = sites_of(text_or_sites) if isinstance(text_or_sites, str) else text_or_sites
    return [s for s in sites if s[1] == "ASM_REG"]


def pinned_var(site):
    """The variable a register pin holds: the last word of its declaration prefix ('s32 *p')."""
    decl = (site[6] or "").split()
    return decl[-1].lstrip("*") if decl else None


def families(text_or_sites):
    """Same-hard-register groups of the live ASM_REG sites, largest family first, then by
    register number (unrecognised spellings last, alphabetically). Every group is returned,
    singletons included: a lone pin whose register appears nowhere else has no family, so it
    carries no lever here - it is only ever tried in the single-site pass."""
    groups = {}
    for s in reg_sites(text_or_sites):
        groups.setdefault(hard_register(s[2]), []).append(s)
    def order(key):
        num = isinstance(key, int)
        return (-len(groups[key]), 0 if num else 1, key if num else 0, str(key))
    return [(k, groups[k]) for k in sorted(groups, key=order)]


def label(key):
    return "$%s" % key


class T:
    name = "t62_regfamily"
    level = 1
    needs_verify = True

    @staticmethod
    def eligible(text, row, census):
        why = asm_blocker(text)
        if why:
            return why
        if not any(len(g) >= 2 for _, g in families(text)):
            return "no same-register pin family"
        if not row.get("cfg"):
            return "missing compiler recipe"
        return None

    @classmethod
    def apply_verified(cls, text, row, census, vf):
        vbudget = max(1, int(os.getenv("T62_VERIFY", str(VERIFY_BUDGET))))
        pins_in = len(sites_of(text))
        usig = unscored_text(text)
        scores = {}
        log = {"pins_in": pins_in, "vf_budget": vbudget, "tried": 0,
               "families": [], "singles": [], "steps": [], "skipped": 0}

        def allowed(cand, cur):
            """Never add, never edit an arm no byte gate compiles."""
            return len(sites_of(cand)) < len(sites_of(cur)) and unscored_text(cand) == usig

        def score(cand):
            h = sha_text(cand)
            if h not in scores:
                if log["tried"] >= vbudget:
                    return False
                log["tried"] += 1
                scores[h] = vf(cand) or {}
            return scores[h].get("exact") is True

        cur = text
        # Pass 1 - the families. Largest first: the biggest exclusion set is the one whose
        # removal frees its register for the whole function. Each acceptance re-reads the
        # sites of the NEW text (erase_many takes tuples from one sites_of call on its input).
        done = set()
        while True:
            pick = next(((k, g) for k, g in families(cur) if len(g) >= 2 and k not in done), None)
            if pick is None:
                break
            key, group = pick
            done.add(key)
            rec = {"reg": label(key), "n": len(group), "vars": [pinned_var(s) for s in group],
                   "lines": [s[5] for s in group], "exact": False}
            log["families"].append(rec)
            cand = erase_many(cur, group, clean_notes=True)
            if not allowed(cand, cur):
                rec["skipped"] = "guard"
                log["skipped"] += 1
                continue
            if log["tried"] >= vbudget:
                rec["skipped"] = "budget"
                continue
            if score(cand):
                rec["exact"] = True
                cur = cand
                log["steps"].append("family:%s x%d" % (rec["reg"], rec["n"]))

        # Pass 2 - the siblings the freed register may have released, each tried once, in text
        # order, on the text the families left behind. Only run it when a family actually fell:
        # otherwise this is a plain greedy single-pin pass and spends the budget re-proving it.
        if any(r["exact"] for r in log["families"]):
            i = 0
            while log["tried"] < vbudget:
                live = reg_sites(cur)
                if i >= len(live):
                    break
                s = live[i]
                rec = {"reg": label(hard_register(s[2])), "var": pinned_var(s), "line": s[5],
                       "exact": False}
                log["singles"].append(rec)
                cand = erase_many(cur, [s], clean_notes=True)
                if allowed(cand, cur) and score(cand):
                    rec["exact"] = True
                    cur = cand
                    log["steps"].append("single:%s:%s" % (rec["reg"], rec["var"]))
                    continue                      # the list shrank; index i is the next site
                i += 1

        pins_out = len(sites_of(cur))
        log.update(pins_out=pins_out, pins_removed=pins_in - pins_out,
                   families_fallen=sum(1 for r in log["families"] if r["exact"]),
                   singles_fallen=sum(1 for r in log["singles"] if r["exact"]))
        return (cur if pins_out < pins_in else None), log
