"""T102: a labelled join tail duplicated into its `goto` predecessors, and the label retired.

APPEARS     m2c's goto soup writes a shared tail once and jumps to it, where the original C had the
            statements in each arm.  Two shapes from the harvest lanes:

              (a) the tail ends the block, so the duplicate needs a label of its own PAST it
                  (dungeon/func_800C9858, work/native_lane/r63_astra_big2 - round 67's move F):
                      edge_coord -= axis_extent;
                      goto axis_y_join;
                      ...
                      edge_coord += axis_extent;
                  axis_y_join:
                      SP16(0x8A) = edge_coord;  SP16(0x82) = edge_coord;
                  ->  the arm gets its own `SP16(0x8A) = ...; SP16(0x82) = ...; goto axis_y_done;`,
                      the label moves below the fall-through copy and five ASM_SCHED_BARRIER pins
                      fall with the join.

              (b) the tail ends in an unconditional transfer, so the duplicate needs no label at all
                  (dungeon/func_80977E0C, work/native_lane/r71_kit_astra9): states 1 and 2 reach
                  `effect_common:` - seven statements ending `goto store_state;` - which READS the
                  page-staged `effect_table`.  Because three states share that tail, three different
                  symbols cannot flow into it, which is why t92_pagerun and t97_pagesym stop at
                  listing distance 2 on the row (measured, round-72 move table C): the page runs are
                  all found, and the spelling is refused by the SHARING, not by the spelling.

RESOLVES    the duplication is the machinery round 67 (move F, 6 pins / 2 rows), round 71 and round
            72 (move #9, the t82 `dup` extension) all asked for, on the goto side that t82 does not
            reach: t82 duplicates the statement after an exhaustive braced if/else chain, never a
            tail a `goto` jumps to.  Mechanism: with the join gone, each arm's values die in the arm
            and the scheduler no longer has to hold a live value across the join edge - the
            ASM_SCHED_BARRIER pins that stood on those edges stop being needed.  As the round-72
            table asked, the page-run family composes on top: every candidate is offered again with
            t92_pagerun's runs respelled over the DUPLICATED text, so a run whose consumer was the
            shared tail can be spelled as its own symbol.

CANDIDATES  per (label, tail length, predecessor set): every `goto L;` at a point where the tail's
            names are all in scope is replaced by a copy of the tail (re-indented), followed by a
            jump past the tail when the tail does not itself end in `goto`/`return`; the label is
            dropped when nothing jumps to it any more.  Tail lengths run from one statement to the
            run of simple statements under the label (at most eight), and the predecessors are
            taken all together and one at a time.  Each duplication is then tried with every single
            pin of the row erased, with all of them, and with t92_pagerun's own candidates over it;
            everything is ranked by cc1 listing distance to the pinned text and only the nearest
            reach the byte verifier.
            Refused: a tail holding a pin, a declaration, a label, a brace or a preprocessor line; a
            tail naming a local declared in a block the `goto` site is not inside; a label whose
            name is `case`/`default`; and a duplication that leaves the pin count unchanged.
"""
import difflib
import re
import sys
from pathlib import Path

ROOT = next(p for p in Path(__file__).resolve().parents if (p / "tools/common.py").is_file())
if str(ROOT / "tools") not in sys.path:
    sys.path.insert(0, str(ROOT / "tools"))

from pin_census import sites_of, asm_blocker, unscored_text
from pin_sites import erase_many
from xform import natural as N
from xform import screen
from xform import t87_lifetimemerge as T87
from xform import t92_pagerun as t92

MAX_JOINS = 6
MAX_TAIL = 8
MAX_PREDS = 3
MAX_CANDS = 40
MAX_LISTINGS = 300
MAX_VERIFY = 6
ID = r"[A-Za-z_]\w*"
LABEL_RE = re.compile(r"^[ \t]*(?P<n>[A-Za-z_]\w*)[ \t]*:[ \t]*$")
GOTO_RE = re.compile(r"^(?P<ind>[ \t]*)goto[ \t]+(?P<n>[A-Za-z_]\w*)[ \t]*;[ \t]*$")
END_RE = re.compile(r"^[ \t]*(?:goto[ \t]+%s[ \t]*;|return\b[^;]*;)[ \t]*$" % ID)
SIMPLE_RE = re.compile(r"^[ \t]*[^{}#]*;[ \t]*$")
NOT_LABELS = {"case", "default", "else", "do", "public", "private"}


def _fn_of(t, k):
    return next(((a, b) for a, b in t.spans if a <= k <= b), None)


def _is_decl(line):
    return N.VDECL_RE.match(line) is not None or N._DECL_START_RE.match(line.strip()) is not None


def joins(text):
    """[{'label','line','gotos','tail_end','fn'}] - a label with at least one `goto` predecessor."""
    t = N._T(text)
    ml = t.m
    out = []
    labels = {}
    for k, ln in enumerate(ml):
        m = LABEL_RE.match(ln)
        if m and m.group("n") not in NOT_LABELS and not t.dead(k):
            labels.setdefault(m.group("n"), []).append(k)
    for name, lines in labels.items():
        if len(lines) != 1:
            continue
        k = lines[0]
        fn = _fn_of(t, k)
        if fn is None:
            continue
        gotos = [g for g, ln in enumerate(ml)
                 if GOTO_RE.match(ln) and GOTO_RE.match(ln).group("n") == name
                 and fn[0] <= g <= fn[1] and not t.dead(g)]
        if not gotos:
            continue
        out.append({"label": name, "line": k, "gotos": gotos, "fn": fn})
    return out[:MAX_JOINS]


def tails(text, j):
    """[(last line, ends in a transfer)] - the runs of simple statements under the label."""
    t = N._T(text)
    ml = t.m
    out, k = [], j["line"] + 1
    while k <= j["fn"][1] and len(out) < MAX_TAIL:
        ln = ml[k]
        if not ln.strip():
            k += 1
            continue
        if not SIMPLE_RE.match(ln) or LABEL_RE.match(ln) or _is_decl(ln) or ln.lstrip().startswith("#"):
            break
        if re.search(r"\bASM_[A-Z0-9_]+[ \t]*\(", ln):
            break                                   # a pin inside the tail: not this generator's
        done = bool(END_RE.match(ln))
        out.append((k, done))
        if done:
            break
        k += 1
    return out


def _in_scope(text, j, end):
    """Every local the tail names resolves to the SAME declaration at each `goto` site.

    Checking the name against every declaration of that name is not enough: two sibling blocks of
    dungeon/func_800C9858 each declare their own `s16 edge_coord`, so the y-block's tail looked
    out of scope at the y-block's own goto because the x-block's declaration does not contain it.
    """
    t = N._T(text)
    body = "\n".join(t.m[j["line"] + 1:end + 1])
    names = set(re.findall(ID, body))
    for fn in N._functions(t):
        if not (fn.a <= j["line"] <= fn.b):
            continue
        scope = T87.scope_decls(fn)
        for name in names:
            d = T87._resolve(scope, name, end)
            if d is None or d.get("param"):
                continue                            # a global, a parameter or not a variable
            if any(T87._resolve(scope, name, g) is not d for g in j["gotos"]):
                return False
    return True


def _fresh(text, base):
    name, i = base, 1
    while re.search(r"\b%s\b" % re.escape(name), text):
        i += 1
        name = "%s%d" % (base, i)
    return name


def duplicate(text, j, end, preds):
    """`goto L;` at each of `preds` replaced by the tail, the label dropped when nothing needs it."""
    t = N._T(text)
    lines = text.splitlines(True)
    tail = [N._nl(lines[k]) for k in range(j["line"] + 1, end + 1) if lines[k].strip()]
    if not tail:
        return None
    closed = bool(END_RE.match(t.m[end]))
    after = _fresh(text, j["label"] + "_done") if not closed else None
    body = "\n".join(t.m[j["line"] + 1:end + 1])
    if re.search(r"\bgoto[ \t]+%s\b" % re.escape(j["label"]), body):
        return None                                 # the tail jumps back to its own label
    out, left = [], [g for g in j["gotos"] if g not in preds]
    for k, ln in enumerate(lines):
        nl = "\n" if ln.endswith("\n") else ""
        if k in preds:
            ind = GOTO_RE.match(t.m[k]).group("ind")
            for x in tail:
                out.append(ind + x.strip() + "\n")
            if not closed:
                out.append("%sgoto %s;%s" % (ind, after, nl))
            continue
        if k == j["line"] and not left:
            continue                                # nothing jumps to the label any more
        out.append(ln)
        if k == end and not closed:
            out.append("%s%s:\n%s;%s" % (N._ind(ln), after, N._ind(ln), nl))
    return "".join(out)


def candidates(text):
    """[(label, new_text)] - each (join, tail length, predecessor set)."""
    out, seen, sig = [], {text}, unscored_text(text)
    for j in joins(text):
        for end, _closed in tails(text, j):
            if not _in_scope(text, j, end):
                continue
            groups = [j["gotos"]] if len(j["gotos"]) == 1 else \
                [j["gotos"]] + [[g] for g in j["gotos"][:MAX_PREDS]]
            for preds in groups:
                cand = duplicate(text, j, end, set(preds))
                if cand is None or cand in seen or unscored_text(cand) != sig:
                    continue
                seen.add(cand)
                out.append(("dup:%s@%d+%d/%d" % (j["label"], j["line"] + 1,
                                                 end - j["line"], len(preds)), cand))
                if len(out) >= MAX_CANDS:
                    return out
    return out


def plans(text, dup):
    """[(tag, text)] - the duplication with pins erased, and t92_pagerun's runs over it."""
    rs = sites_of(dup)
    out = []
    for i, s in enumerate(rs):
        out.append(("erase1@%d" % s[5], erase_many(dup, [s], clean_notes=True)))
    if len(rs) > 1:
        out.append(("eraseall", erase_many(dup, rs, clean_notes=True)))
    for lab, cand in t92.candidates(dup)[:8]:
        out.append(("t92:" + lab, cand))
    return out


class T:
    name = "t102_gotojoin"
    level = 1
    needs_verify = True

    @staticmethod
    def eligible(text, row, census):
        why = asm_blocker(text)
        if why:
            return why
        if not sites_of(text):
            return "no pins"
        if not joins(text):
            return "no label with a goto predecessor"
        return None if candidates(text) else "no duplicable join tail"

    @classmethod
    def apply_verified(cls, text, row, census, vf):
        sites = sites_of(text)
        pins_in = len(sites)
        target = screen.compile_s(row, text)
        if target is None:
            return None, {"refused": "pinned text does not build to a listing", "pins_in": pins_in,
                          "pins_out": pins_in}
        listings = verifies = 0
        near, rest = None, []
        cands = candidates(text)
        for label, dup in cands:
            if listings >= MAX_LISTINGS:
                break
            for tag, cand in plans(text, dup):
                if listings >= MAX_LISTINGS:
                    break
                if len(sites_of(cand)) >= pins_in or not T87._kept_ok(sites, cand):
                    continue
                if unscored_text(cand) != unscored_text(text):
                    continue
                lst = screen.compile_s(row, cand)
                listings += 1
                if lst is None:
                    continue
                d = sum(1 for y in difflib.unified_diff(target, lst, lineterm="", n=0)
                        if y[:1] in "+-" and not y.startswith(("---", "+++")))
                near = d if near is None else min(near, d)
                rest.append((d, len(rest), cand, "%s|%s" % (label, tag)))
        rest.sort(key=lambda x: (x[0], x[1]))
        best = None
        order = [x for x in rest if x[0] == 0][:MAX_VERIFY - 2] + [x for x in rest if 0 < x[0] <= 2][:2]
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
