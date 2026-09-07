"""T2: erase dead ASM_* pin sites (greedy, each erasure verified byte-exact).

Pass 1 walks the sites in source order and keeps every erasure that stays exact.  Pass 2
retries the refused sites once, because pins interact (one pin's necessity can depend on
another).  Sites inside NON_MATCHING #else arms are left alone.  Reports which sites stayed
and why (breakage class) into the journal so the census can learn from it.
"""
import re, tempfile
from pathlib import Path
import sys
sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
from pin_census import sites_of, erase

class T:
    name = "t2_pins"; level = 1
    needs_verify = True
    @staticmethod
    def eligible(text, row, census):
        if not sites_of(text):
            return "no pin sites"
        return None
    @staticmethod
    def apply_verified(text, row, census, verify_fn):
        cur = text
        kept = []      # sites that stayed: (macro, arg, class)
        erased = 0
        tried = 0
        def attempt(site):
            nonlocal cur, erased, tried
            cand = erase(cur, site)
            tried += 1
            v = verify_fn(cand)
            if v.get("exact"):
                cur = cand; erased += 1; return True, v
            return False, v
        # pass 1
        refused = []
        i = 0
        while True:
            sites = sites_of(cur)
            if i >= len(sites): break
            ok, v = attempt(sites[i])
            if not ok:
                refused.append((i, v)); i += 1
        # pass 2: retry refused in the now-smaller text
        if erased and refused:
            still = []
            sites = sites_of(cur)
            # map refused by (macro,arg,line-ish) is fragile; simply retry every remaining site once
            j = 0
            while True:
                sites = sites_of(cur)
                if j >= len(sites): break
                ok, v = attempt(sites[j])
                if not ok:
                    still.append((sites[j][1], sites[j][2][:40], v.get("class"))); j += 1
            kept = still
        else:
            sites = sites_of(cur)
            kept = [(s[1], s[2][:40], v.get("class")) for (k, v), s in zip(refused, sites)]
        info = {"erased": erased, "tried": tried, "left": len(sites_of(cur)), "kept": kept[:40]}
        return (cur if erased else None), info
