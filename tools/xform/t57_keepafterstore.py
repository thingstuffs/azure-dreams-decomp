"""T57: a slot keep moved after the store it guards, and the fence above the run dropped.

APPEARS     a fenced slot computation kept before its direct store:
                ASM_SCHED_BARRIER();
                slot = base - 1031;
                ASM_KEEP(slot);
                base[-1031] = value;
RESOLVES    the fences19 lane (round 19) on four copies of one transfer function (`dungeon/func_80E91000`,
            `80E9D000`, `80EA3000`, `80EAF000`): keeping the slot live THROUGH the store (the keep after
            it) restores retail's item-load / slot-address order, which the fence was holding. The fence
            goes; the keep stays, relocated. That is a weaker win than a pin removed outright - nothing
            is added and a fence is gone - so it lands under the usual rule (pins fall, no kind grows).
Each site alone and all sites jointly are tried; only `vf` accepts.
RESULT      2026-09-13: the four transfer copies each held a second fenced slot of the same shape; swept
            over them, 4 applied, one fence each. The shape occurs nowhere else in the tree.
"""
import re, sys
from pathlib import Path
sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
from pin_census import sites_of, asm_blocker
from pin_sites import erase_many

FENCES = ("ASM_SCHED_BARRIER", "ASM_MEM_BARRIER")
SITE = re.compile(r"^(?P<ind>[ \t]*)(?P<slot>\w+)\s*=\s*(?P<base>\w+)\s*[-+]\s*(?P<n>\d+)\s*;[^\n]*\n"
                  r"(?P<keep>[ \t]*ASM_KEEP(?:_NV)?\(\s*(?P=slot)\s*\)\s*;[^\n]*\n)"
                  r"(?P<store>[ \t]*(?P=base)\s*\[\s*-?\s*(?P=n)\s*\]\s*=\s*[^;\n]+;[^\n]*\n)", re.M)


def find(text):
    """[(keep_start, keep_end, store_end, fence_line)] for each fenced keep-then-store slot."""
    pins = sites_of(text)
    out = []
    for m in SITE.finditer(text):
        line = text.count("\n", 0, m.start()) + 1
        fence = [s for s in pins if s[1] in FENCES and line - 3 <= s[5] < line]
        if fence:
            out.append((m.start("keep"), m.end("keep"), m.end("store"), fence[-1][5]))
    return out


def rewrite(text, sites):
    """Move each chosen keep after its store (last first), then erase the fences above them."""
    fence_lines = {f for _, _, _, f in sites}
    for ks, ke, se, _ in sorted(sites, reverse=True):
        text = text[:ks] + text[ke:se] + text[ks:ke] + text[se:]
    # the moves keep line numbers (lines are only swapped), so the fences are found by line
    drop = [s for s in sites_of(text) if s[1] in FENCES and s[5] in fence_lines]
    return erase_many(text, drop, clean_notes=True)


class T:
    name = "t57_keepafterstore"
    level = 1
    needs_verify = True

    @staticmethod
    def eligible(text, row, census):
        why = asm_blocker(text)
        if why:
            return why
        return None if find(text) else "no fenced keep-then-store slot"

    find_sites = staticmethod(find)        # t57b_keepafternext overrides the site finder

    @classmethod
    def apply_verified(cls, text, row, census, vf):
        pins_in, sites, tried = len(sites_of(text)), cls.find_sites(text), 0
        trials = ([("all", sites)] if len(sites) > 1 else []) + [("site%d" % i, [s]) for i, s in reversed(list(enumerate(sites)))]
        cur, steps = text, []
        for label, chosen in trials:
            live = [s for s in cls.find_sites(cur) if any(s[3] == c[3] for c in chosen)]
            if not live:
                continue
            cand = rewrite(cur, live)
            if len(sites_of(cand)) >= len(sites_of(cur)):
                continue
            tried += 1
            if vf(cand).get("exact"):
                cur = cand
                steps.append(label)
                if label == "all":
                    break
        if not steps:
            return None, {"tried": tried, "pins_in": pins_in, "pins_out": pins_in, "sites": len(sites)}
        return cur, {"step": "+".join(steps), "tried": tried, "pins_in": pins_in,
                     "pins_out": len(sites_of(cur)), "sites": len(sites)}
