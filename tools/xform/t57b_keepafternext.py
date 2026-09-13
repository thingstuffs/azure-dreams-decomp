"""T57b: t57 generalised - a keep moved past the statement after it, and the fence above the run dropped.

APPEARS     a fence over a value and its keep, with one ordinary statement after them:
                ASM_SCHED_BARRIER();
                table_page = 0x80070000;
                ASM_KEEP(table_page);
                tile_x = U8_AT(tile_node, 0x24);
RESOLVES    the fences27 lane (round 21) three times (`dungeon/func_818BDEBC`, `func_818C3B90`, `func_8197C800`)
            and t57's slot case four times: the keep placed after the next real statement keeps the value
            live through it, which restores retail's order between the value's producer and that
            statement - the order the fence was holding. The keep does not change the value, so the move
            is semantics-preserving wherever it lands; only `vf` decides. The fence goes and the keep stays,
            relocated: nothing is added.
POPULATION  2026-09-13: 44 such sites in 34 rows (the lanes' 5 included).
RESULT      2026-09-13: reproduces the three fences27 outputs (identical assembly). Swept over its 34
            eligible rows outside the lane rows: 7 applied, one fence each (a third fenced site in each of
            the four transfer copies, dungeon/func_818B1664, func_81978428, func_819835AC); 1 more in the
            harvest cascade.
Each site alone, then all jointly, as t57; t57's rewrite moves the keep line after the next statement.
"""
import re, sys
from pathlib import Path
sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
from pin_census import sites_of, asm_blocker
try:
    from . import t57_keepafterstore as K
except ImportError:
    import t57_keepafterstore as K

SITE = re.compile(r"^(?P<ind>[ \t]*)(?P<v>\w+)\s*=\s*[^;\n]+;[^\n]*\n"
                  r"(?P<keep>[ \t]*ASM_KEEP(?:_NV)?\(\s*(?P=v)\s*\)\s*;[^\n]*\n)"
                  r"(?P<store>[ \t]*(?!ASM_|if\b|for\b|while\b|do\b|switch\b|return\b|goto\b|case\b|default\b)"
                  r"[^\n#{}]*;[^\n]*\n)", re.M)


def find(text):
    """[(keep_start, keep_end, next_end, fence_line)] for each fenced value-keep-statement run."""
    pins = sites_of(text)
    out = []
    for m in SITE.finditer(text):
        line = text.count("\n", 0, m.start()) + 1
        fence = [s for s in pins if s[1] in K.FENCES and line - 3 <= s[5] < line]
        if fence:
            out.append((m.start("keep"), m.end("keep"), m.end("store"), fence[-1][5]))
    return out


class T(K.T):
    name = "t57b_keepafternext"
    find_sites = staticmethod(find)        # t57's search and rewrite, over this module's sites

    @staticmethod
    def eligible(text, row, census):
        why = asm_blocker(text)
        if why:
            return why
        return None if find(text) else "no fenced value-keep-statement run"
