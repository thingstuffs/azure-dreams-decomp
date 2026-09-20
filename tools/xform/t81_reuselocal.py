"""T81: an arm-local value hosted on a dead same-typed local of the function (disjoint-lifetime reuse).

APPEARS     a pinned block (a switch case, an if arm, a goto-state block) holding a local `v` that is
            mentioned only inside it, while another local `w` of the SAME declared type is untouched in
            the block and is next mentioned after it by a plain write:
                s32 reward;
                s32 divisor = 1;
                ...
            state0:
                {
                    ASM_CLOBBER("$5");
                    ...
                    divisor = 10;                    <- only this block mentions `divisor`
                    scaled_count = ...->unk_1E / divisor;
                }
                ...
                reward = ((s32 *)&reward_units)[...] * 100;    <- `reward` is dead until here
RESOLVES    town/func_8081DED0 byte-exact (lane r59_sol_large5, 2026-09-20): `s32 reward; s32 divisor = 1;`
            became `s32 reward = 1;`, every `divisor` in the state-0 arm was renamed to `reward`, and the
            `ASM_CLOBBER("$5")` went.  Mechanism: the two pseudos have disjoint lifetimes, so coalescing
            them into the variable the rest of the function already uses gives the arm's value a life that
            reaches outside the arm.  local-alloc only allocates a quantity whose life is inside one basic
            block, so the merged pseudo falls to global-alloc, where its (longer) life and higher priority
            pick retail's register - the colour the ASM_CLOBBER was buying with a hard-register
            perturbation.  The same rule near-missed twice in that lane (dungeon/func_81325EF0, listing
            19 -> 16, and town/func_8081791C, listing 18 -> 8).
            natural.host_candidates is the narrower ancestor: it renames onto an existing local too, but
            fires only where the pin is an ASM_REG ON the variable's own declaration, so it never saw this
            shape (the pin here is an ASM_CLOBBER three lines above).
WINDOWS     round 61: the window a value is confined to need not be braced.  418 of the r60 sweep's
            refusals had no braced window at all - the pin stands directly in the function body, or in
            an unbraced `case X:` region of a switch - so two more windows are read from the text:
            the CASE REGION of a pin inside a switch (from its `case X:` / `default:` label to the next
            depth-0 `case` / `default`, its depth-0 `break;`, or the switch's closing brace), and, for a
            pin standing in the function body, the STATEMENT RUN around it (the maximal run of lines
            between the control-flow boundaries on either side - a label, a `case`, a control head, a
            jump or a brace - never reaching above the body's declarations, so `v` stays function-scope
            and its initialiser merges into the host as before).  The rule on top of a window is
            unchanged: `v` mentioned only inside it, the host of the same declared type not named in it
            and next mentioned after it by a plain write or not at all.  Braced windows are offered
            first, so a row that had one is screened exactly as in r60.
CANDIDATES  per pinned window, each (v, host w) pair - hosts in declaration order as host_candidates orders
            them, at most six: `v` renamed to `w` throughout the window, `v`'s declaration deleted, and
            `v`'s initialiser merged into `w`'s declaration (a function-scope `v`) or left behind as a
            plain assignment (a block-scope `v`); then the block's pins erased jointly, then singly.
            Candidates are ranked by cc1 listing distance to the pinned text and only the nearest reach
            `vf` (at most MAX_VERIFY a row).  Refused: `v` or `w` address-taken, volatile, static, const,
            an array, a parameter, a different declared type, a `w` mentioned inside the block or read
            (not written) after it, two initialisers, and any rewrite that would change another pin's text.
"""
import os
import difflib, re, sys
from pathlib import Path
sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
from pin_census import sites_of, asm_blocker
from pin_sites import erase_many
try:
    from . import natural as N
    from . import screen
except ImportError:
    import natural as N
    import screen

MAX_WINDOWS = 6
MAX_VARS = 4
MAX_HOSTS = 6
MAX_LISTINGS = 120
MAX_VERIFY = 6

ID = r"[A-Za-z_]\w*"
KEYWORDS = {"if", "for", "while", "do", "return", "goto", "switch", "case", "default", "break", "continue",
            "else", "sizeof", "typedef"}
NOSHARE = {"static", "volatile", "const", "extern"}
DECL_RE = re.compile(r"^(?P<i>[ \t]*)(?P<q>(?:(?:register|const|volatile|static|unsigned|signed|struct|union|enum)[ \t]+)*)"
                     r"(?P<base>%s)(?P<ptr>(?:[ \t]*\*)+[ \t]*|[ \t]+)(?P<n>%s)(?P<arr>[ \t]*\[[^\]]*\])?"
                     r"(?P<asm>[ \t]*ASM_REG[ \t]*\([^)]*\))?[ \t]*(?:=[ \t]*(?P<init>[^;]*?))?[ \t]*;[ \t]*$" % (ID, ID))
DECLISH_RE = re.compile(r"^[ \t]*(?:(?:register|const|volatile|static|unsigned|signed|struct|union|enum)[ \t]+)*"
                        r"%s(?:[ \t]*\*+[ \t]*|[ \t]+)\**%s" % (ID, ID))
WRITE_RE = re.compile(r"^[ \t]*(?P<n>%s)[ \t]*=(?!=)" % ID)
CASE_RE = re.compile(r"^[ \t]*(?:case\b[^:]*|default[ \t]*):")
BREAK_RE = re.compile(r"^[ \t]*break[ \t]*;[ \t]*$")
LABEL_RE = re.compile(r"^[ \t]*%s[ \t]*:[ \t]*;?[ \t]*$" % ID)
BOUNDARY_RE = re.compile(r"^[ \t]*(?:goto|return|break|continue|case|default|if|while|for|do|switch|else)\b")


def _depth0(t, o, c):
    """The lines of block (o, c) at the block's own nesting depth (not inside a nested brace)."""
    out, depth = [], 0
    for k in range(o + 1, c):
        if depth == 0:
            out.append(k)
        depth = max(0, depth + t.m[k].count("{") - t.m[k].count("}"))
    return out


def first_statement(t, o, c):
    """The first line of block (o, c) that is not a declaration (where block_decls stops)."""
    k = o + 1
    while k < c:
        ln = t.m[k]
        if not ln.strip() or ln.lstrip().startswith("#"):
            k += 1
            continue
        m = DECL_RE.match(ln)
        if m and m.group("base") not in KEYWORDS:
            k += 1
            continue
        if DECLISH_RE.match(ln) and not ln.rstrip().endswith(";") and "(" not in ln.split("=")[0]:
            while k < c and not t.m[k].rstrip().endswith(";"):
                k += 1
            k += 1
            continue
        break
    return k


def case_window(t, blk, k):
    """(o, c) of the unbraced `case` region of a switch body holding line k: from its label to the next
    depth-0 `case` / `default`, its depth-0 `break;`, or the switch's closing brace."""
    o, c = blk
    lines = _depth0(t, o, c)
    if not any(CASE_RE.match(t.m[j]) for j in lines):
        return None                                                  # not a switch body
    start = max([j for j in lines if j < k and CASE_RE.match(t.m[j])] + [-1])
    if start < 0:
        return None
    end = min([j for j in lines if j > k and (CASE_RE.match(t.m[j]) or BREAK_RE.match(t.m[j]))] + [c])
    return (start, end) if start < k < end else None


def run_window(t, blk, k):
    """(o, c) of the statement run around line k in block (o, c): the maximal run between the
    control-flow boundaries on either side, never reaching above the block's declarations."""
    o, c = blk

    def boundary(j):
        ln = t.m[j]
        return bool(BOUNDARY_RE.match(ln) or LABEL_RE.match(ln) or "{" in ln or "}" in ln)

    lines = _depth0(t, o, c)
    start = max([j for j in lines if j < k and boundary(j)] + [o, first_statement(t, o, c) - 1])
    end = min([j for j in lines if j > k and boundary(j)] + [c])
    return (start, end) if start < k < end else None


def windows(t, fn, pinlines):
    """[(o, c, kind)] for one function, braced first: the innermost braced block of each pin, then the
    unbraced case region of a pin in a switch, then the statement run of a pin in the function body."""
    braced, extra, seen = [], [], set()
    for k in pinlines:
        if not (fn.a < k < fn.b):
            continue
        blk = fn.inner.get(k) or fn.body
        if blk != fn.body and blk not in seen:
            seen.add(blk)
            braced.append((blk[0], blk[1], "braced"))
        win, kind = case_window(t, blk, k), "case"
        if win is None and blk == fn.body:
            win, kind = run_window(t, blk, k), "run"
        if win and win not in seen:
            seen.add(win)
            extra.append((win[0], win[1], kind))
    return braced + extra


def block_decls(t, o, c):
    """The declarations of block (o, c): [(line, name, ty, init, quals, ok)] - `ok` is False for a
    declaration this generator may not touch (multi-line, array, comma list, shared qualifier)."""
    out, k = [], o + 1
    while k < c:
        ln = t.m[k]
        if not ln.strip() or ln.lstrip().startswith("#"):
            k += 1
            continue
        m = DECL_RE.match(ln)
        if m and m.group("base") not in KEYWORDS:
            q = set(m.group("q").split())
            out.append(dict(line=k, name=m.group("n"), ind=m.group("i"),
                            ty=N._ptype(m.group("q").split(), m.group("base"), m.group("ptr")),
                            init=(m.group("init") or "").strip() or None, quals=q,
                            pinned=bool(m.group("asm")),
                            ok=not (q & NOSHARE) and not m.group("arr")))
            k += 1
            continue
        if DECLISH_RE.match(ln) and not ln.rstrip().endswith(";") and "(" not in ln.split("=")[0]:
            while k < c and not t.m[k].rstrip().endswith(";"):           # a multi-line declaration
                k += 1
            k += 1
            continue
        break                                                            # the first statement ends the prologue
    return out


def _mentions(t, name, lo, hi, skip=()):
    rx = N._occ(name)
    return [k for k in range(lo, hi + 1) if k not in skip and rx.search(t.m[k])]


def candidates(text):
    """[(window, v, w, new_text)] for every admissible rename of an arm-local onto a dead host."""
    t = N._T(text)
    out = []
    for fn in N._functions(t):
        body = fn.body
        taken = set(re.findall(r"&[ \t]*(%s)" % ID, "\n".join(t.m[fn.a:fn.b + 1])))
        decls = {}
        for blk in {body} | {fn.inner.get(s[5] - 1) for s in sites_of(text) if fn.a < s[5] - 1 < fn.b}:
            if blk:
                decls[blk] = block_decls(t, *blk)
        params = {d["name"] for d in fn.params}
        wins = windows(t, fn, [s[5] - 1 for s in sites_of(text)])
        for o, c, kind in wins[:MAX_WINDOWS]:
            win = (o, c)
            scope = [d for d in decls.get(body, ()) if d["ok"]] + [d for d in decls.get(win, ()) if d["ok"]]
            free = [d for d in scope if d["name"] not in taken and d["name"] not in params]
            vs = []
            for d in free:
                ms = _mentions(t, d["name"], fn.a, fn.b, skip={d["line"]})
                if ms and all(o < k < c for k in ms):
                    vs.append((d, ms))
            for v, ms in vs[:MAX_VARS]:
                # a statement run holds no control flow, so `v` is live only over its own mentions: the
                # host must be dead over THAT much of the run, not over the whole of it
                lo, hi = (max(o, min(ms) - 1), min(c, max(ms) + 1)) if kind == "run" else (o, c)
                hosts = []
                for w in free:
                    if w["name"] == v["name"] or w["ty"] != v["ty"] or w["pinned"]:
                        continue
                    if _mentions(t, w["name"], lo, hi, skip={w["line"]}):
                        continue
                    after = _mentions(t, w["name"], hi, fn.b, skip={w["line"]})
                    if after and not (WRITE_RE.match(t.m[after[0]]) and WRITE_RE.match(t.m[after[0]]).group("n") == w["name"]):
                        continue
                    if v["init"] and w["init"]:
                        continue
                    hosts.append(w)
                for w in hosts[:MAX_HOSTS]:
                    cand = rewrite(t, win, v, w)
                    if cand is None:
                        continue
                    want = [(x[1], x[2]) for x in sites_of(text) if x[5] - 1 != v["line"]]
                    if [(x[1], x[2]) for x in sites_of(cand)] != want:
                        continue                                        # a kept pin names v: its text would change
                    out.append((win, v["name"], w["name"], cand))
    return out


def rewrite(t, win, v, w):
    """`v` renamed to `w` inside the window, `v`'s declaration gone, its initialiser rehoused."""
    o, c = win
    rx, edits, drop = N._occ(v["name"]), {}, {v["line"]}
    for k in range(o + 1, c):
        if k == v["line"]:
            continue
        ln = N._nl(t.lines[k])
        hits = list(rx.finditer(ln))
        if hits:
            for h in reversed(hits):
                ln = ln[:h.start()] + w["name"] + ln[h.end():]
            edits[k] = ln
    if v["init"]:
        if rx.search(v["init"]):
            return None
        if o < v["line"] < c:                                            # a block-scope v: keep the value here
            edits[v["line"]] = "%s%s = %s;" % (v["ind"], w["name"], v["init"])
            drop = set()
        else:                                                            # a function-scope v: merge into w
            wl = N._nl(t.lines[w["line"]])
            m = re.match(r"^(?P<head>.*?)(?P<semi>[ \t]*;[ \t]*)$", wl)
            if not m or w["init"]:
                return None
            edits[w["line"]] = "%s = %s;" % (m.group("head").rstrip(), v["init"])
    return t.build(edits, drop)


class T:
    name = "t81_reuselocal"
    level = 1
    needs_verify = True

    @staticmethod
    def eligible(text, row, census):
        why = asm_blocker(text)
        if why:
            return why
        if not sites_of(text):
            return "no pins"
        return None if candidates(text) else "no arm-local with a dead same-typed host"

    @classmethod
    def apply_verified(cls, text, row, census, vf):
        pins_in = len(sites_of(text))
        target = screen.compile_s(row, text)
        if target is None:
            return None, {"refused": "pinned text does not build to a listing", "pins_in": pins_in,
                          "pins_out": pins_in}
        sites = sites_of(text)
        listings = verifies = 0
        best, near, rest = None, None, []
        for win, v, w, renamed in candidates(text):
            if listings >= MAX_LISTINGS or verifies >= MAX_VERIFY:
                break
            rs = sites_of(renamed)
            lo, hi = win[0] + 1, win[1] + 1
            wpins = [i for i, s in enumerate(rs) if lo <= s[5] <= hi]
            plans = ([[]] if len(rs) < len(sites) else []) + \
                    ([wpins] if len(wpins) > 1 else []) + [[i] for i in wpins]
            for g in plans:
                if listings >= MAX_LISTINGS or verifies >= MAX_VERIFY:
                    break
                cand = erase_many(renamed, [rs[i] for i in g], clean_notes=True) if g else renamed
                if len(sites_of(cand)) >= len(sites):
                    continue
                lst = screen.compile_s(row, cand)
                listings += 1
                if lst is None:
                    continue
                d = sum(1 for y in difflib.unified_diff(target, lst, lineterm="", n=0)
                        if y[:1] in "+-" and not y.startswith(("---", "+++")))
                near = d if near is None else min(near, d)
                label = "%s->%s@%d-erase%d" % (v, w, win[0] + 1, len(g))
                if d == 0:
                    verifies += 1
                    if vf(cand).get("exact"):
                        best = (cand, label)
                        break
                else:
                    rest.append((d, len(rest), cand, label))
            if best:
                break
        if best is None:
            rest.sort(key=lambda x: (x[0], x[1]))
            NEAR_VERIFY = int(os.environ.get('NEAR_VERIFY', '4'))        # round 61: the near band (d <= 2) gets four scorer runs
            for d, _, cand, label in [x for x in rest if x[0] <= 2][:NEAR_VERIFY]:
                if verifies >= min(MAX_VERIFY, NEAR_VERIFY):
                    break
                verifies += 1
                if vf(cand).get("exact"):
                    best = (cand, label)
                    break
        info = {"listings": listings, "tried": verifies, "pins_in": pins_in, "near": near}
        if best is None:
            return None, dict(info, pins_out=pins_in)
        return best[0], dict(info, pins_out=len(sites_of(best[0])), step=best[1])
