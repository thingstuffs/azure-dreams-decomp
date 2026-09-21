"""T89: one local (or parameter) reused for two unrelated values, split into two - the inverse of t87.

APPEARS     a pinned function in which ONE name carries several disjoint value ranges, because the
            decompiler folded what retail wrote as two variables into one:

                S_80024100_2 *element;                  <- written in three successive loops
                ...
                do { ... element = (u8 *)object + 0x20; ...  } while (column >= 0);   /* first  */
                do { ... element = (u8 *)object + 0x20; ...  } while (column >= 0);   /* second */
                do {
                    object = func_8003FD64(1, D_80083498);
                    if (object != NULL) {
                        render_data = &D_80053A88;
                        ASM_KEEP(render_data);          <- the pin
                        element = (u8 *)object + 0x20;  /* third: a range of its own */

            and its parameter form, a parameter whose incoming value is read once and whose name is
            then reused as a scratch pointer for the rest of the body:

                register s32 saved_arg3 ASM_REG("$18");  <- the pin, 27 lines above
                ...
                saved_arg3 = arg3;                       <- arg3's entry range ends here
                ...
                arg3 = (s32)(*(void * *)((u8 *)object + 0xC));   <- a second, unrelated range
                (*(u8 *)((u8 *)((void *)arg3) + 0x25)) = saved_arg2;

RESOLVES    two rows of the round-63 astra lanes byte-exact.  town/func_8081A100
            (work/native_lane/r63_astra_moveli): the third loop's element pointer declared for itself
            inside the loop's `if`, and `ASM_KEEP(render_data)` gone.  dungeon/func_8105F098
            (work/native_lane/r63_astra_prologue): `arg3`'s second range moved to a local of its own,
            and the `register s32 saved_arg3 ASM_REG("$18")` binding gone.
            MECHANISM.  gcc 2.x treats a pseudo with exactly one set specially: `reg_n_sets == 1`
            lets sched.c's `birthing_insn_p` give the insn that first sets it a priority boost in the
            first scheduling pass, lets local-alloc/global prefer a fresh colour for it, and lets cse
            promote it.  A name written twice has two sets, so none of that applies - and the pin was
            standing in for the placement or the colour the single-set treatment would have produced.
            Splitting the ranges gives each value exactly one set and the decision comes back by
            itself.  This is the exact inverse of t74_multiset (which SPLITS a chained assignment to
            reach two sets) and of t87_lifetimemerge (which MERGES two variables into one, for the
            rows where the pin is bought by the extra set).  The nearest ancestors miss it:
            t64_varset calls `varset.split_def_candidates`, which refuses the WHOLE variable when any
            one of its webs is degenerate (`element`'s `default:` arm gives a use-without-def web, so
            the clean third-loop web is never offered) and never splits a PARAMETER at all; t51's
            single-set split only walks a straight run of <= 10 statements.
CANDIDATES  per function with pins, per usable name, the definition WEBS of `varset.webs` (reaching
            definitions on the statement CFG, union-find over {def, use} nodes).  Each web after the
            first that has a definition of its own, crosses no back edge and stands on no `unknown`
            or preprocessor node is renamed to a fresh `V_2`, declared in four places - after `V`'s
            own declaration, at the top of the innermost block that encloses the whole web, at the
            end of the function's declaration block, and (as a rename with no new declaration) onto
            an unused local of the same declared type.  Declaration PLACEMENT is a lever, not a
            spelling: gcc 2.x makes pseudos in `expand_decl` order, so where the split local is
            declared decides its number and with it several priority ties.
            Each rewrite is then screened with the pins erased - the web's own window jointly, then
            EVERY single pin of the function (the parameter form's pin sits in the declaration block,
            far above the web), then all of them - by the cc1 listing against the pinned text
            (`screen.compile_s`), and only listing-exact texts reach `vf`.
            Refused: a variable that is address-taken, volatile/const, an array, a multi-declarator,
            shadowed, declared with an `ASM_REG` pin of its own (t90's business), written in a loop
            header, mentioned inside a preprocessor arm or on a CFG node this module could not
            classify; a web with no definition, a web that crosses a back edge (a loop-carried
            value is ONE range however it is written), and any rewrite that changes the text of a
            surviving pin.
            THE PAIRED FORM, not built here.  town/func_8009A370 and town/func_800AB1FC need the
            split of `angle_component`'s first trig range AND the removal of a proven-unused trailing
            argument of `func_80064584` - neither alone is exact.  t76_arity can only prove an
            argument fake when the argument is a local that is never assigned and only `ASM_SET`/
            `ASM_USE`-pinned; here it is a live value (`y`), so the arity evidence would have to come
            from the callee's definition or from every textual prototype of it, which this module
            has no census for.  `arity_review` in a miss record names the calls that would need it.
"""
import difflib
import os
import re
import sys
from collections import Counter
from pathlib import Path

ROOT = next(p for p in Path(__file__).resolve().parents if (p / "tools/common.py").is_file())
if str(ROOT / "tools") not in sys.path:
    sys.path.insert(0, str(ROOT / "tools"))

from pin_census import sites_of, asm_blocker
from pin_sites import erase_many
from xform import varset as V
from xform import screen
from xform.t29_addrsym import mask_comments

MAX_CANDS = 24
MAX_LISTINGS = 200
MAX_VERIFY = 6
OPENERS = ("if", "elseif", "elseopen", "loop", "do", "switch")
ID = r"[A-Za-z_]\w*"
PROTO_RE = re.compile(r"^[ \t]*(?:extern[ \t]+)?[A-Za-z_][\w \t*]*?(?P<f>%s)[ \t]*\((?P<ps>[^;()]*)\)[ \t]*;"
                      % ID, re.M)


# ------------------------------------------------------------------ text helpers

def _norm_ty(d):
    """A declaration's type as a comparable string (`register` is not part of the type)."""
    return re.sub(r"\s+", " ", d["decl_text"].replace("register", "").strip()) + d["stars"]


def _param_decl(ind, ty, name):
    core = re.sub(r"\s+", " ", ty).strip()
    return "%s%s%s%s;" % (ind, core, "" if core.endswith("*") else " ", name)


def _decl_block_end(fn):
    """(line, indent) after the function's last top-level declaration - where a new local may go."""
    top = min((fn.nodes[x["node"]].depth for ds in fn.decls.values() for x in ds), default=None)
    best, ind = None, "    "
    for ds in fn.decls.values():
        for x in ds:
            if fn.nodes[x["node"]].depth == top and (best is None or x["line"] > best):
                best, ind = x["line"], x["ind"]
    return (best, ind) if best is not None else (fn.lo - 1, "    ")


def _enclosing_open(fn, nodes):
    """The innermost block opener whose block contains every node of the web, or None."""
    first, last = min(nodes), max(nodes)
    mind = min(fn.nodes[i].depth for i in nodes)
    for j in range(first - 1, -1, -1):
        n = fn.nodes[j]
        if n.kind not in OPENERS or n.depth >= mind:
            continue
        c = fn._match_close(j)
        if c is None or c <= last:
            return None
        return n
    return None


def _dead_locals(fn, locs):
    """Locals of the function that are declared and never mentioned again (a free declaration slot)."""
    out = []
    for v, d in sorted(locs.items()):
        if d["init"] or d["pin"] or d["arr"]:
            continue
        if not fn.kinds(v):
            out.append((v, d))
    return out


# ------------------------------------------------------------------ the web finder

def _usable(fn, text):
    """[(name, decl or None)] - the locals and parameters whose ranges this generator may split."""
    skips = Counter()
    out = [(v, d) for v, d in sorted(V.usable_locals(fn, skips).items())]
    body = "\n".join(fn.m[fn.lo:fn.hi])
    declared = set(fn.decls)
    for p, ty in fn.params:
        if p in declared or not ty:
            continue
        if re.search(r"(?:^|[^\w)\]&])&[ \t]*" + re.escape(p) + r"\b", body, re.M):
            continue
        placed, stray = fn.occurrences(p)
        if stray or any(fn.pp[fn.nodes[i].line] for i, _ in placed):
            continue
        if any(fn.nodes[i].kind == "unknown" for i, _ in placed):
            continue
        if any(V.COMMA_DECL_RE.match(fn.nodes[i].masked) for i, _ in placed):
            continue
        if any(fn.nodes[i].kind in ("loop", "dowhile", "switch", "if", "elseif")
               and V.write_re(p).search(fn.nodes[i].masked) for i, _ in placed):
            continue
        out.append((p, None))
    return out


def splits(text):
    """[(fn, name, decl or None, web index, web nodes, kinds)] for every splittable range near a pin."""
    out = []
    sites = sites_of(text)
    for fn in V.functions(text, Counter()):
        if not [s for s in sites if fn.lo <= s[5] - 1 <= fn.hi]:
            continue
        for v, d in _usable(fn, text):
            kinds = fn.kinds(v)
            if not kinds or V._multi_occurrence(fn, v, kinds):
                continue
            ws = V.webs(fn, v, kinds)
            if len(ws) < 2:
                continue
            for wi, (ds, us, back) in enumerate(ws):
                if wi == 0 or back or not ds:
                    continue
                nodes = sorted(set(ds) | set(us))
                if any(fn.nodes[i].kind == "unknown" or fn.pp[fn.nodes[i].line] for i in nodes):
                    continue
                out.append((fn, v, d, wi, nodes, kinds))
    return out


def _placements(fn, text, v, d, name, nodes, locs):
    """[(tag, new name, inserts dict, drops)] - where the split local's declaration goes."""
    out = []
    if d is not None and not d["pin"] and not d["arr"]:
        out.append(("afterdecl", name, {d["line"]: [V._decl_line(d, name)]}, ()))
    op = _enclosing_open(fn, nodes)
    if op is not None:
        ind = re.match(r"[ \t]*", fn.lines[fn.nodes[min(nodes)].line]).group(0)
        line = (V._decl_line(d, name) if d is not None
                else _param_decl(ind, dict(fn.params)[v], name))
        line = re.sub(r"^[ \t]*", ind, line)
        out.append(("inblock", name, {op.line: [line]}, ()))
    end, ind = _decl_block_end(fn)
    line = (re.sub(r"^[ \t]*", ind, V._decl_line(d, name)) if d is not None
            else _param_decl(ind, dict(fn.params)[v], name))
    out.append(("declend", name, {end: [line]}, ()))
    want = _norm_ty(d) if d is not None else None
    if want is not None:
        for u, du in _dead_locals(fn, locs):
            if u != v and _norm_ty(du) == want:
                out.append(("deadslot:" + u, u, {}, ()))
                break
    return out


def candidates(text):
    """[(label, cand, window, must)] for every admissible split of a value range."""
    out, seen = [], set()
    per_fn = {}
    for fn, v, d, wi, nodes, kinds in splits(text):
        if id(fn) not in per_fn:
            per_fn[id(fn)] = V.usable_locals(fn, Counter())
        locs = per_fn[id(fn)]
        name = V._fresh(text, v)
        if name is None:
            continue
        lines = sorted({fn.nodes[i].line for i in nodes})
        for tag, nm, inserts, drops in _placements(fn, text, v, d, name, nodes, locs):
            edits = {}
            for ln in lines:
                edits[ln] = V._rename_line(fn, ln, v, nm, edits.get(ln))
            cand = V._apply(text, edits, drops, inserts)
            if cand == text or cand in seen:
                continue
            seen.add(cand)
            label = "split:%s>%s@%d:%s" % (v, nm, lines[0] + 1, tag)
            out.append((label, cand, (lines[0], lines[-1]), ()))
    return out[:MAX_CANDS]


# ------------------------------------------------------------------ the arity note (not built)

def arity_review(text):
    """Calls whose trailing argument a split may also need dropped, and whose only evidence would be
    the callee's prototype - the town/func_8009A370 shape t76_arity cannot prove (see the docstring)."""
    m = mask_comments(text)
    protos = {}
    for pm in PROTO_RE.finditer(m):
        ps = [x.strip() for x in pm.group("ps").split(",") if x.strip()]
        if len(ps) >= 2 and all(re.search(ID + r"\s*$", p) for p in ps):
            protos[pm.group("f")] = len(ps)
    out = []
    for f, n in sorted(protos.items()):
        for cm in re.finditer(r"(?<![\w.])(?<!->)%s\s*\(([^;()]*)\)" % re.escape(f), m):
            args = [x.strip() for x in cm.group(1).split(",") if x.strip()]
            if len(args) == n and re.fullmatch(ID, args[-1]):
                out.append("%s/%d" % (f, n))
                break
    return sorted(set(out))


# ------------------------------------------------------------------ the generator

def _plans(sites, rs, win):
    """Erase plans: the web's own window, then every single pin of the row, then all of them."""
    lo, hi = win[0] + 1, win[1] + 1
    req = [i for i, s in enumerate(rs) if lo <= s[5] <= hi]
    out = []
    if len(rs) < len(sites):
        out.append([])                                     # the rewrite itself dropped a pin
    if req:
        out.append(req)
    for i in range(len(rs)):
        g = sorted(set(req) | {i})
        if g not in out:
            out.append(g)
    allp = list(range(len(rs)))
    if allp and allp not in out:
        out.append(allp)
    return out


def _kept_ok(sites, cand):
    """No surviving pin's text changed (a kept pin naming a renamed variable is refused)."""
    want = Counter((s[1], s[2]) for s in sites)
    got = Counter((s[1], s[2]) for s in sites_of(cand))
    return not (got - want)


class T:
    name = "t89_lifetimesplit"
    level = 1
    needs_verify = True

    @staticmethod
    def eligible(text, row, census):
        why = asm_blocker(text)
        if why:
            return why
        if not sites_of(text):
            return "no pins"
        return None if candidates(text) else "no splittable value range in a pinned function"

    @classmethod
    def apply_verified(cls, text, row, census, vf):
        sites = sites_of(text)
        pins_in = len(sites)
        target = screen.compile_s(row, text)
        if target is None:
            return None, {"refused": "pinned text does not build to a listing", "pins_in": pins_in,
                          "pins_out": pins_in}
        listings = verifies = 0
        best, near, rest, tried = None, None, [], []
        for label, split, win, _must in candidates(text):
            if listings >= MAX_LISTINGS or verifies >= MAX_VERIFY:
                break
            tried.append(label)
            rs = sites_of(split)
            for g in _plans(sites, rs, win):
                if listings >= MAX_LISTINGS or verifies >= MAX_VERIFY:
                    break
                cand = erase_many(split, [rs[i] for i in g], clean_notes=True) if g else split
                if len(sites_of(cand)) >= pins_in or not _kept_ok(sites, cand):
                    continue
                lst = screen.compile_s(row, cand)
                listings += 1
                if lst is None:
                    continue
                d = sum(1 for y in difflib.unified_diff(target, lst, lineterm="", n=0)
                        if y[:1] in "+-" and not y.startswith(("---", "+++")))
                near = d if near is None else min(near, d)
                tag = "%s-erase%d" % (label, len(g))
                if d == 0:
                    verifies += 1
                    if vf(cand).get("exact"):
                        best = (cand, tag)
                        break
                else:
                    rest.append((d, len(rest), cand, tag))
            if best:
                break
        if best is None:
            rest.sort(key=lambda x: (x[0], x[1]))
            for d, _, cand, tag in [x for x in rest if x[0] <= 2][:int(os.environ.get("NEAR_VERIFY", "3"))]:
                if verifies >= MAX_VERIFY:
                    break
                verifies += 1
                if vf(cand).get("exact"):
                    best = (cand, tag)
                    break
        if best is None:
            info = {"pins_in": pins_in, "pins_out": pins_in, "listings": listings,
                    "verifies": verifies, "nearest": near, "tried": len(tried)}
            ar = arity_review(text)
            if ar:
                info["arity_review"] = ar
            return None, info
        cand, tag = best
        return cand, {"pins_in": pins_in, "pins_out": len(sites_of(cand)), "move": tag,
                      "listings": listings, "verifies": verifies, "nearest": 0}
