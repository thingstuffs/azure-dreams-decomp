"""T53k: t53_reg_state's search seeded from ASM_KEEP-family erasures instead of ASM_REG ones.

APPEARS     a row with a live keep pin (`ASM_KEEP(v)`, `ASM_KEEP_NV(v)`, `ASM_KEEP_DEP_NV(v, ...)`, ...:
            an empty asm with a tied register output, include/common.h).
RESOLVES    the round-19 census (250 keep erasures, one per row, page-base rows excluded) put 61 in the
            wiring class at combine and 73 in the late class (54 of them first differ at sched); t53's
            levers (lifetime split, statement move, width, fusion, allocation host/unhost, declaration
            order, the two-rewrite beam) act on those. The focus variable is the keep's first argument.
            Page-base keeps are t54_pagebase's.
RESULT      2026-09-13, all 1,003 keep rows (--processes, 8 workers, 41 min): 16 rows, 16 pins (1.6%):
            moves 6, widths 5, single-set 2, unhost, splitcursor, fuse. Its per-site erasures (2,958 keeps)
            put 1,434 in ops at combine and 1,217 first differing at cse: most keeps hide a value from CSE,
            which allocation and order levers do not reach (work/native_lane/keep_astra).
Budgets and screens are t53's (T53_COMPILERS, T53_VERIFY). Sweep with --processes (the search parses
compiler dumps and is Python-bound).
"""
import re

from xform.t53_reg_state import T as T53, sites_of, asm_blocker

IDENT = re.compile(r"[A-Za-z_]\w*")


class T(T53):
    name = 't53k_keep'

    @staticmethod
    def eligible(text, row, census):
        if not any(s[1].startswith('ASM_KEEP') for s in sites_of(text)):
            return 'no live keep pins'
        return asm_blocker(text) or (None if row.get('cfg') else 'missing compiler recipe')

    @staticmethod
    def sites(pins):
        """Every keep-family site, with the first identifier of its argument as the focus variable."""
        out = []
        for i, s in enumerate(pins):
            m = IDENT.search(s[2]) if s[1].startswith('ASM_KEEP') else None
            if m: out.append((i, m.group(0)))
        return out
