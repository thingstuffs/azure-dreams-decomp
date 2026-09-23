"""T103: the redundant parameter copies dropped (t69) AND the statements that last read them moved.

APPEARS     callee-saved `register T held ASM_REG("$s") = param;` copies of STACK or register
            parameters, with `ASM_KEEP(held)` at the end of the function, whose t69 erasure leaves a
            residue that is a pure rotation of the $s-sequence among values of equal reference count
            (dungeon/func_819C0A6C, claude-opus-5-5 lane work/native_lane/r73_opus_a1, 4 pins):

                register s32 held_offset_x ASM_REG("$22") = offset_x;      (and held_offset_y, $23)
                ...
                effect_state->unk_88 = (s32) (0 - ((s32) (held_offset_x << 0x10) >> 7));
                effect_state->unk_8C = (s32) (0 - ((s32) (held_offset_y << 0x10) >> 7));
                effect_state->unk_2C = (s16) base_x;
                effect_state->unk_2E = (s16) base_y;
                effect_state->unk_30 = (s16) base_z;
                ...
                ASM_KEEP(held_offset_x);  ASM_KEEP(held_offset_y);
            ->  both copies and both keeps gone, offset_x/offset_y read directly, and the unk_88/unk_8C
                stores written AFTER the three base stores.

RESOLVES    the lane's rule (r73_opus_a1/REPORT.md, func_819C0A6C): "APPEARS: callee-saved ASM_REG pins
            on stack-argument copies whose erase residue is a pure rotation of the $s-sequence among
            values with equal refs. RESOLVES: move the last use of the values that should rank lower
            past the last use of the values that should rank higher (a permutation of independent
            stores in one block), so live_length decides the order."  Mechanism: global.c ranks
            allocnos by `floor_log2(refs) * refs / live_length`; with the copies gone the parameters
            tie with base_x..base_z on refs, and the live length - which ends at the LAST use - breaks
            the tie.  Retail's order ends offset_x/offset_y after the bases, which is what the keeps at
            the function's end were standing in for.

WHY THE OWNERS MISS IT (measured 2026-09-23, work/native_lane/r73_h_probe_t69_prologue_o)
            t69_prologue is eligible and builds the exact copy set, but its best listing is 26 lines
            from the pinned text: it never moves a statement.  t72_stmtperm permutes only runs that
            hold a PIN, and after the drop there is no pin left near the stores.

CANDIDATES  t69's candidates (the copy set and its subsets), screened; for the nearest TOPK of them,
            every run of simple statements (t72's tokeniser and dependence test) holding a statement
            that mentions a dropped name, and in it: each such statement moved alone to every legal
            position, and every subset of two to four of them moved as one block (order kept) to every
            legal position.  A move is
            legal when every dependent pair of t72's `depends` keeps its order.  Ranked by the cc1
            listing distance to the pinned text; the listing-exact candidates and the two nearest go
            to `vf`.  No scaffolding is added: the text only loses copies and pins and has statements
            reordered inside one block.
"""
import collections
import difflib
import itertools
import re
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
from pin_census import sites_of, asm_blocker, unscored_text
try:
    from . import t69_prologue as P
    from . import t72_stmtperm as S
    from .t29_addrsym import mask_comments
    from .t36_paramwidth import functions
    from . import screen
except ImportError:
    import t69_prologue as P
    import t72_stmtperm as S
    from t29_addrsym import mask_comments
    from t36_paramwidth import functions
    import screen

TOPK = 4                 # t69 candidates carried into the move search
RUN = 10                 # statements per run at most (nearest to the anchor)
MAX_LISTINGS = 400       # per row
MAX_VERIFY = 5


def dropped_names(text, label):
    """The copy names in a t69 label, and the parameters they copied."""
    names = set(label.rsplit(":", 1)[-1].split("+"))
    out = set(names)
    for fn in functions(text):
        for ec in P.entry_copies(text, fn) or []:
            if ec[3] in names:
                out.add(ec[0])
    return out


def runs_mentioning(text, names):
    """[run] - each a list of t72 `Stmt`s at one brace depth holding a statement that mentions a name."""
    masked = mask_comments(text)
    ml, lines, out, seen = masked.split("\n"), text.split("\n"), [], set()
    rx = re.compile(r"\b(?:%s)\b" % "|".join(sorted(map(re.escape, names)))) if names else None
    if rx is None:
        return out
    for fname, params, b0, b1 in functions(text):
        body = masked[b0:b1]
        locals_ = S.decl_names(body) | {p for p, _, _, _ in params}
        taken = set(re.findall(r"&\s*([A-Za-z_]\w*)", body))
        first, last = masked.count("\n", 0, b0), masked.count("\n", 0, b1)
        toks = S.tokens(ml, first, last)
        for n, t in enumerate(toks):
            if t[0] != "stmt" or not any(rx.search(ml[q]) for q in range(t[1], t[2] + 1)):
                continue
            ind = t[3]
            lo = n
            while lo > 0 and (toks[lo - 1][0] == "blank" or (toks[lo - 1][0] == "stmt" and toks[lo - 1][3] == ind)):
                lo -= 1
            hi = n
            while hi + 1 < len(toks) and (toks[hi + 1][0] == "blank" or (toks[hi + 1][0] == "stmt" and toks[hi + 1][3] == ind)):
                hi += 1
            group = [x for x in toks[lo:hi + 1] if x[0] == "stmt"]
            if len(group) < 2:
                continue
            group.sort(key=lambda x: (abs(x[1] - t[1]), x[1]))
            g = sorted(group[:RUN], key=lambda x: x[1])
            key = tuple(x[1] for x in g)
            if key in seen:
                continue
            seen.add(key)
            run = [S.Stmt(lines[x[1]:x[2] + 1], x[1], x[2], locals_, taken) for x in g]
            # the run must be contiguous in the text apart from blank lines: t72.build keeps the gaps
            out.append(run)
    return out


def _legal(run, perm):
    pos = {p: i for i, p in enumerate(perm)}
    n = len(run)
    return all(not S.depends(run[a], run[b]) or pos[a] < pos[b]
               for a in range(n) for b in range(a + 1, n))


def moves(run, names):
    """[(tag, perm)] - the mentioning statements moved, alone and together, to every legal position."""
    rx = re.compile(r"\b(?:%s)\b" % "|".join(sorted(map(re.escape, names))))
    n = len(run)
    hot = [i for i, s in enumerate(run) if rx.search(s.text)]
    out, seen = [], {tuple(range(n))}
    groups = [("one%d" % i, [i]) for i in hot]
    for k in range(2, min(len(hot), 4) + 1):          # every subset moved as one block, order kept
        groups += [("grp" + "_".join(map(str, c)), list(c)) for c in itertools.combinations(hot[:6], k)]
    for tag, grp in groups:
        rest = [i for i in range(n) if i not in grp]
        for k in range(len(rest) + 1):
            perm = tuple(rest[:k] + grp + rest[k:])
            if perm in seen or not _legal(run, perm):
                continue
            seen.add(perm)
            out.append(("%s@%d" % (tag, k), perm))
    return out


def _dist(a, b):
    return sum(1 for y in difflib.unified_diff(a, b, lineterm="", n=0)
               if y[:1] in "+-" and not y.startswith(("---", "+++")))


class T:
    name = "t103_dropsink"
    level = 1
    needs_verify = True

    @staticmethod
    def eligible(text, row, census):
        why = asm_blocker(text)
        if why:
            return why
        if not sites_of(text):
            return "no pin sites"
        if not any(P.entry_copies(text, fn) for fn in functions(text)):
            return "no redundant parameter copy"
        return None

    @classmethod
    def apply_verified(cls, text, row, census, vf):
        pins_in = len(sites_of(text))
        info = {"pins_in": pins_in, "pins_out": pins_in}
        base_c = P.prologue_candidates(text)
        if not base_c:
            return None, dict(info, refused=["no buildable t69 candidate"])
        target = screen.compile_s(row, text)
        if target is None:
            return None, dict(info, refused=["pinned text does not build to a listing"])
        sig = unscored_text(text)
        listings, ranked, first, built = 0, [], [], set()
        for label, c in base_c:
            lst = screen.compile_s(row, c); listings += 1
            if lst is not None:
                first.append((_dist(target, lst), label, c))
        first.sort(key=lambda x: (x[0], len(sites_of(x[2]))))
        ranked.extend((d, len(sites_of(c)), lab + "|asis", c) for d, lab, c in first[:TOPK])
        for d0, label, c in first[:TOPK]:
            if d0 == 0:
                continue
            names = dropped_names(text, label)
            for run in runs_mentioning(c, names):
                for tag, perm in moves(run, names):
                    if listings >= MAX_LISTINGS:
                        break
                    cand = S.build(c, run, perm, set())
                    if cand in built or unscored_text(cand) != sig:
                        continue
                    built.add(cand)
                    lst = screen.compile_s(row, cand); listings += 1
                    if lst is None:
                        continue
                    ranked.append((_dist(target, lst), len(sites_of(cand)),
                                   "%s|run@%d:%s" % (label, run[0].first + 1, tag), cand))
        ranked.sort(key=lambda x: (x[0], x[1]))
        info.update(listings=listings, menu=len(ranked))
        tried = 0
        for d, pins, label, cand in ranked:
            if tried >= MAX_VERIFY or (d and tried >= 2):
                break
            if pins >= pins_in:
                continue
            tried += 1
            if vf(cand).get("exact"):
                return cand, dict(info, step="%s|d%d" % (label, d), pins_out=pins, tried=tried)
        return None, dict(info, tried=tried,
                          nearest=[{"distance": d, "label": l} for d, _p, l, _c in ranked[:6]])
