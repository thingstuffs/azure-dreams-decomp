"""T95: pins erased TOGETHER as a group because they sit close together in the text - no C rewrite.

APPEARS     several ASM_KEEP*/ASM_REG/ASM_SCHED_BARRIER/ASM_MEM_BARRIER pins on DIFFERENT locals, close
            together in one statement run, one brace block, one function's uses of one macro, or one
            whole function - none exact erased alone (t2_pins), and not a same-variable subset
            (tools/lanes/joint_scan.py's job, which erases subsets grouped by the pinned variable):
                search_step_offset = (s32)((u32)((u8 *)((u32) locals.sp18)));
                ASM_KEEP_NV(search_step_offset);
                landing_y = partner_sprite->unk_25;
                ASM_KEEP_NV(landing_y);
                landing_x = sprite->unk_24;
                ASM_KEEP_NV(landing_x);
RESOLVES    dungeon/func_81008664 (round-63 astra big3, work/native_lane/r63_astra_big3): three
            ASM_KEEP_NV pins on three different locals, interleaved one-for-one with an ordinary store
            each, exact only when all three are erased together - none of them alone, and no C changed.
            gcc 2.x's old list scheduler (sched.c, rank_for_schedule) ties priority across a short run
            of independent stmts near a call/branch boundary and breaks the tie by original insn order;
            a KEEP pin that looks single-variable from the census is really one mechanism shared with
            its textual neighbours, and only falls when the whole neighbourhood goes with it.
CANDIDATES  four group shapes, each pin set taken as ONE joint erasure of the ORIGINAL pinned text (no
            statement is moved or rewritten):
              (a) run     every maximal run of pins (within one function) with at most 3 qualifying
                          non-pin statement lines between consecutive pins, plus every contiguous
                          sub-run of size 2..5 inside it (sliding window)
              (b) block   every pin's innermost enclosing {...} brace block, grouped
              (c) macro   every function's pins of one ASM_* macro kind, grouped
              (d) function  every function's pins, all together
            Groups of size 1 are t2's job; a group whose pins all name the SAME variable is
            joint_scan's job and is skipped here.  Groups are ranked by the cc1 listing distance to
            the pinned text's own listing (tools/xform/screen.py, as t74_multiset.py ranks): listing-
            exact groups go to `vf` first, largest group first, then the 2 nearest non-exact groups;
            at most 6 vf calls and ~60 listings per row (t74's budget).
"""
import difflib, re, sys
from pathlib import Path
sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
from pin_census import sites_of, asm_blocker
from pin_sites import erase_many
try:
    from .t29_addrsym import mask_comments
    from .t36_paramwidth import functions
    from . import screen
except ImportError:
    from t29_addrsym import mask_comments
    from t36_paramwidth import functions
    import screen

MAX_LISTINGS = 60
MAX_VERIFY = 6
RUN_GAP = 3            # at most this many qualifying statement lines between consecutive run pins
RUN_MAX = 5             # widest sliding sub-run window taken inside a maximal run


def var_of(site):
    """The variable a site pins (KEEP/USE/etc take it as the macro argument; REG names it in the
    declaration the erasure leaves behind), or "" for a no-argument pin (a barrier)."""
    kind, macro, arg = site[0], site[1], site[2]
    if kind == "reg" and len(site) > 6 and site[6]:
        return site[6].replace("*", " ").split()[-1]
    return (arg or "").strip()


def same_var(group):
    """True when every pin in the group names the same single variable - joint_scan's job."""
    names = {var_of(s) for s in group}
    return len(names) == 1 and "" not in names


def _stmt_line(line, pinlines, lineno):
    """A line that counts toward the run gap: not blank, not a bare brace, not a directive, not
    itself one of the row's own pin lines (that is a pin, not a statement)."""
    if lineno in pinlines:
        return False
    s = line.strip()
    if not s or s in ("{", "}"):
        return False
    if s.startswith("#"):
        return False
    return True


def runs_of(text, sites):
    """[[site, ...]] every maximal run, per function, of >=2 pins with <=RUN_GAP qualifying
    statement lines between each consecutive pair (source order, by 1-based pin line)."""
    lines = text.split("\n")
    pinlines = {s[5] for s in sites}
    out = []
    for fname, params, b0, b1 in functions(text):
        fn_sites = sorted((s for s in sites if b0 <= s[3] < b1), key=lambda s: s[5])
        if len(fn_sites) < 2:
            continue
        run = [fn_sites[0]]
        for prev, cur in zip(fn_sites, fn_sites[1:]):
            lo, hi = prev[5], cur[5]
            gap = sum(1 for ln in range(lo + 1, hi) if _stmt_line(lines[ln - 1], pinlines, ln))
            if gap <= RUN_GAP:
                run.append(cur)
                continue
            if len(run) >= 2:
                out.append(run)
            run = [cur]
        if len(run) >= 2:
            out.append(run)
    return out


def run_groups(text, sites):
    groups = []
    for run in runs_of(text, sites):
        n = len(run)
        groups.append(("run", tuple(run)))
        for size in range(2, min(RUN_MAX, n) + 1):
            for start in range(0, n - size + 1):
                groups.append(("run", tuple(run[start:start + size])))
    return groups


def pin_blocks(text, sites):
    """The innermost enclosing brace-span start offset for each site (None if at file scope)."""
    masked = mask_comments(text)
    pin_pos = {s[3]: i for i, s in enumerate(sites)}
    stack, block_id = [], [None] * len(sites)
    for i, ch in enumerate(masked):
        if ch == "{":
            stack.append(i)
        elif ch == "}" and stack:
            stack.pop()
        if i in pin_pos:
            block_id[pin_pos[i]] = stack[-1] if stack else None
    return block_id


def block_groups(text, sites):
    ids = pin_blocks(text, sites)
    by_block = {}
    for site, bid in zip(sites, ids):
        if bid is not None:
            by_block.setdefault(bid, []).append(site)
    return [("block", tuple(g)) for g in by_block.values() if len(g) >= 2]


def macro_groups(text, sites):
    out = []
    for fname, params, b0, b1 in functions(text):
        by_macro = {}
        for s in sites:
            if b0 <= s[3] < b1:
                by_macro.setdefault(s[1], []).append(s)
        out.extend(("macro", tuple(g)) for g in by_macro.values() if len(g) >= 2)
    return out


def function_groups(text, sites):
    out = []
    for fname, params, b0, b1 in functions(text):
        fn_sites = [s for s in sites if b0 <= s[3] < b1]
        if len(fn_sites) >= 2:
            out.append(("function", tuple(fn_sites)))
    return out


def candidate_groups(text, sites):
    """[(kind, group)] every joint-erasure group worth trying: size >= 2, not all-same-variable."""
    raw = run_groups(text, sites) + block_groups(text, sites) + macro_groups(text, sites) + function_groups(text, sites)
    out, seen = [], set()
    for label, group in raw:
        if len(group) < 2 or same_var(group):
            continue
        key = frozenset(s[3] for s in group)
        if key in seen:
            continue
        seen.add(key)
        out.append((label, group))
    return out


class T:
    name = "t95_runjoint"
    level = 1
    needs_verify = True

    @staticmethod
    def eligible(text, row, census):
        why = asm_blocker(text)
        if why:
            return why
        sites = sites_of(text)
        if len(sites) < 2:
            return "fewer than 2 pins"
        if not candidate_groups(text, sites):
            return "no joint-erasure group (run/block/macro/function) beyond t2/joint_scan"
        return None

    @classmethod
    def apply_verified(cls, text, row, census, vf):
        sites = sites_of(text)
        pins_in = len(sites)
        groups = candidate_groups(text, sites)
        if not groups:
            return None, {"refused": ["no joint-erasure group"], "pins_in": pins_in, "pins_out": pins_in}
        target = screen.compile_s(row, text)
        if target is None:
            return None, {"refused": ["pinned text does not build to a listing"], "pins_in": pins_in, "pins_out": pins_in}
        ordered = sorted(groups, key=lambda lg: -len(lg[1]))[:MAX_LISTINGS]
        exact, near, listings = [], [], 0
        for label, group in ordered:
            cand = erase_many(text, group, clean_notes=True)
            lst = screen.compile_s(row, cand)
            listings += 1
            if lst is None:
                continue
            d = sum(1 for y in difflib.unified_diff(target, lst, lineterm="", n=0) if y[:1] in "+-" and not y.startswith(("---", "+++")))
            (exact if d == 0 else near).append((d, label, group))
        exact.sort(key=lambda x: -len(x[2]))            # listing-exact: largest group first
        near.sort(key=lambda x: x[0])                    # then the 2 nearest non-exact
        verifies = 0
        for d, label, group in exact + near[:2]:
            if verifies >= MAX_VERIFY:
                break
            cand = erase_many(text, group, clean_notes=True)
            verifies += 1
            if vf(cand).get("exact"):
                return cand, {"label": "%s%d@%d" % (label, len(group), group[0][5]), "kind": label,
                              "group_size": len(group), "listings": listings, "tried": verifies,
                              "pins_in": pins_in, "pins_out": pins_in - len(group), "groups": len(ordered)}
        return None, {"listings": listings, "tried": verifies, "pins_in": pins_in, "pins_out": pins_in,
                      "groups": len(ordered)}
