"""T100: a scalarised read-modify-write folded back into one field expression.

APPEARS     m2c's three-statement form of `p->field |= K;` - a load into a local, the operation on
            the local, and a store back to the same lvalue - with a pin inside the run:

                actor_flags_14 = ((S *)actor)->unk_14;
                actor_flags_1c = ((S *)actor)->unk_1C;
                ASM_SCHED_BARRIER();
                action_mode = 0;
                actor_flags_14 |= 0x2000;
                actor_flags_1c |= 0x2000;
                ((S *)actor)->unk_14 = actor_flags_14;
                ((S *)actor)->unk_1C = actor_flags_1c;
            ->  ((S *)actor)->unk_14 |= 0x2000;
                ((S *)actor)->unk_1C |= 0x2000;

RESOLVES    move #5 of docs/evidence/pin_research_round72_move_table.md - dungeon/func_800C5028
            (6 pins: the barrier, two `ASM_REG` declarations, two keeps and a dead local, all falling
            with the fold) and dungeon/func_80E07054 (1, in the half-folded `flags0 = *(u32 *)(v_s0 +
            0x14) | 0x2000;` form the lane kept the store for).  The lane's rule: "RESOLVES by writing
            direct field updates with fresh expression results and combining them with independently
            justified context/argument-role erasures" (work/native_lane/r71_kit_astra10/REPORT.md).

            Mechanism: written out, the load, the operation and the store are three insns over a
            pseudo whose live range spans everything between them, so the allocator must colour it
            and sched.c may move the load away from its store - which is what the barrier and the
            register pins were holding.  Folded, combine sees one `(mem) op K` pattern, the value
            never becomes a separate quantity, and the whole group is unnecessary.  This is the
            direction t94_castsplit does not have: t94 SPLITS one assignment into two (round 67 move
            D, round 71 moves D and E); here two or three statements become one.

CANDIDATES  per function: every (load, op, store) triple over a local used nowhere else, alone and
            all the triples of one run jointly, in two forms - the full fold (`LV op= K;` where the
            store was, the local's declaration dropped) and the birth form (`V = LV op K;` at the
            load, the store kept, which is what dungeon/func_80E07054 needed).  Refused when a CALL
            sits between the load and the store (memory could alias), when the same lvalue text is
            assigned in between, when the local is read anywhere else, or when a label sits inside
            the run.  Pin plans: the run's window jointly, the pins naming the local, and both.
            Ranked by the cc1 listing distance to the pinned text; `vf` sees the listing-exact
            candidates and the two nearest.
"""
import difflib, re, sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
from pin_census import sites_of, asm_blocker, unscored_text
from pin_sites import erase_many
try:
    from .t29_addrsym import mask_comments
    from .t36_paramwidth import functions
    from . import screen
except ImportError:
    from t29_addrsym import mask_comments
    from t36_paramwidth import functions
    import screen

OPS = ("|", "&", "^", "+", "-", "<<", ">>", "*")
LOAD = re.compile(r"^(?P<ind>[ \t]*)(?P<v>[A-Za-z_]\w*)[ \t]*=[ \t]*(?P<lv>[^;=][^;]*?)[ \t]*;[ \t]*$")
OP = re.compile(r"^(?P<ind>[ \t]*)(?P<v>[A-Za-z_]\w*)[ \t]*(?P<op>\||&|\^|\+|-|<<|>>|\*)=[ \t]*"
                r"(?P<k>[^;]+?)[ \t]*;[ \t]*$")
STORE = re.compile(r"^(?P<ind>[ \t]*)(?P<lv>[^;=][^;]*?)[ \t]*=[ \t]*(?P<v>[A-Za-z_]\w*)[ \t]*;[ \t]*$")
CALL = re.compile(r"(?<![\w.>])(?P<n>[A-Za-z_]\w*)[ \t]*\(")
LABEL = re.compile(r"^[ \t]*[A-Za-z_]\w*[ \t]*:(?!:)")
DECL = re.compile(r"^[ \t]*(?:register[ \t]+)?[A-Za-z_][\w \t\*]*?\b%s[ \t]*"
                  r"(?:ASM_REG\([^()]*\)[ \t]*)?;[ \t]*$")
KEYWORDS = {"if", "while", "for", "switch", "return", "sizeof", "else", "do", "goto", "case"}
UPPER = re.compile(r"^[A-Z][A-Z0-9_]*$")
MAX_RUNS = 4
MAX_LISTINGS = 120
MAX_VERIFY = 4
LEAD = 3                           # a pin just ABOVE the load run belongs to it
MAX_FN_PINS = 8                    # the whole-function plan, only on a small row
SPAN = 14                          # how many lines a triple may span


def _norm(s):
    return " ".join(s.split())


def _calls(s):
    return [m.group("n") for m in CALL.finditer(s)
            if m.group("n") not in KEYWORDS and not UPPER.match(m.group("n"))]


def _lvalue(e):
    """An lvalue this generator will fold onto: a field, an index or a dereference, call-free."""
    e = e.strip()
    if _calls(e) or "?" in e or "," in e:
        return False
    return bool(re.search(r"->|\[|^\*|\)\s*\*", e)) or "." in e


def _decl_line(lines, fn, v):
    rx = re.compile(DECL.pattern % re.escape(v))
    hits = [i for i in range(fn[0], min(fn[1] + 1, len(lines))) if rx.match(lines[i])]
    return hits[0] if len(hits) == 1 else None


def triples(text):
    """[{v, lv, op, k, load, opl, store, fn}] for every scalarised read-modify-write."""
    masked = mask_comments(text)
    lines = masked.split("\n")
    out = []
    for _fn, _p, b0, b1 in functions(text):
        first, last = masked.count("\n", 0, b0), masked.count("\n", 0, b1)
        body = "\n".join(lines[first:last + 1])
        for i in range(first, min(last, len(lines)) + 1):
            ml = LOAD.match(lines[i])
            if not ml or not _lvalue(ml.group("lv")) or ml.group("v") in KEYWORDS:
                continue
            v, lv = ml.group("v"), _norm(ml.group("lv"))
            d = _decl_line(lines, (first, last), v)
            n = len(re.findall(r"(?<![\w.>])%s\b" % re.escape(v), body))
            if n - (1 if d is not None else 0) != 3:
                continue                                  # load, op and store are its only uses
            op_at = store_at = None
            for j in range(i + 1, min(i + 1 + SPAN, last + 1)):
                if LABEL.match(lines[j]):
                    break
                mo = OP.match(lines[j])
                if mo and mo.group("v") == v and op_at is None:
                    op_at = j
                    continue
                ms = STORE.match(lines[j])
                if ms and ms.group("v") == v and _norm(ms.group("lv")) == lv:
                    store_at = j
                    break
                if re.search(r"(?<![\w.>])%s\b" % re.escape(v), lines[j]):
                    break                                 # another use before the store
            if op_at is None or store_at is None or op_at > store_at:
                continue
            between = "\n".join(lines[i + 1:store_at])
            if _calls(between):
                continue                                  # a call could alias the lvalue
            if any(_norm(m.group("lv")) == lv for m in
                   (STORE.match(lines[j]) for j in range(i + 1, store_at)) if m):
                continue                                  # the same lvalue written in between
            mo = OP.match(lines[op_at])
            out.append({"v": v, "lv": ml.group("lv").strip(), "op": mo.group("op"),
                        "k": mo.group("k").strip(), "load": i, "opl": op_at, "store": store_at,
                        "ind": ml.group("ind"), "fn": (first, last)})
    return out


def rewrite(text, group, form):
    """The triples of `group` folded; `form` is 'full' (one statement) or 'birth' (load + op)."""
    lines, ml = text.split("\n"), mask_comments(text).split("\n")
    drop, put = set(), {}
    for t in group:
        if form == "full":
            drop.add(t["load"]); drop.add(t["opl"])
            put[t["store"]] = "%s%s %s= %s;" % (lines[t["store"]][:len(lines[t["store"]]) -
                                                                   len(lines[t["store"]].lstrip())],
                                                t["lv"], t["op"], t["k"])
            d = _decl_line(ml, t["fn"], t["v"])
            if d is not None:
                drop.add(d)
        else:
            put[t["load"]] = "%s%s = %s %s %s;" % (t["ind"], t["v"], t["lv"], t["op"], t["k"])
            drop.add(t["opl"])
    out = []
    for i, ln in enumerate(lines):
        if i in drop:
            continue
        out.append(put.get(i, ln))
    return "\n".join(out)


def candidates(text):
    """[(label, new_text)] - each triple and each run, in both forms, x three pin plans."""
    ts = triples(text)
    if not ts:
        return []
    runs, cur = [], []
    for t in sorted(ts, key=lambda t: t["load"]):
        if cur and t["load"] - cur[-1]["store"] <= 3 and t["fn"] == cur[-1]["fn"]:
            cur.append(t)
        else:
            if cur:
                runs.append(cur)
            cur = [t]
    if cur:
        runs.append(cur)
    groups = [g for g in runs if len(g) > 1][:MAX_RUNS] + [[t] for t in ts][:MAX_RUNS * 2]
    out, seen, sig = [], {text}, unscored_text(text)
    pins, n0 = sites_of(text), len(sites_of(text))
    for group in groups:
        lo = min(t["load"] for t in group)
        hi = max(t["store"] for t in group)
        names = {t["v"] for t in group}
        keys = [(t["v"], _norm(t["lv"]), t["op"], _norm(t["k"])) for t in group]
        win = [s for s in pins if lo - LEAD <= s[5] - 1 <= hi + 1]
        named = [s for s in pins
                 if any(re.search(r"\b%s\b" % re.escape(n), text[s[3]:s[4]]) for n in names)]
        both = win + [s for s in named if s not in win]
        fn = group[0]["fn"]
        whole = [s for s in pins if fn[0] <= s[5] - 1 <= fn[1]]
        for ptag, grp in (("win", win), ("var", named), ("win+var", both),
                          ("fn", whole if len(whole) <= MAX_FN_PINS else [])):
            if not grp:
                continue
            # the pins are erased FIRST and the triples re-found in the erased text: a site tuple
            # carries offsets into the text it came from, and the fold shifts every one of them
            base = erase_many(text, grp, clean_notes=True)
            here, pool = [], triples(base)
            for k in keys:
                hit = next((t for t in pool
                            if (t["v"], _norm(t["lv"]), t["op"], _norm(t["k"])) == k), None)
                if hit is None:
                    break
                pool.remove(hit); here.append(hit)
            if len(here) != len(keys):
                continue
            for form in ("full", "birth"):
                cand = rewrite(base, here, form)
                if cand in seen or unscored_text(cand) != sig or len(sites_of(cand)) >= n0:
                    continue
                seen.add(cand)
                out.append(("rmw%d@%d:%s:%s" % (len(group), lo + 1, form, ptag), cand))
    return out


class T:
    name = "t100_rmwfold"
    level = 1
    needs_verify = True

    @staticmethod
    def eligible(text, row, census):
        why = asm_blocker(text)
        if why:
            return why
        if not sites_of(text):
            return "no live pin site"
        if not triples(text):
            return "no scalarised read-modify-write"
        return None

    @classmethod
    def apply_verified(cls, text, row, census, vf):
        pins_in = len(sites_of(text))
        info = {"pins_in": pins_in, "pins_out": pins_in, "triples": len(triples(text))}
        menu = candidates(text)
        if not menu:
            return None, dict(info, refused=["no buildable candidate"])
        target = screen.compile_s(row, text)
        if target is None:
            return None, dict(info, refused=["pinned text does not build to a listing"])
        ranked, listings = [], 0
        for label, cand in menu:
            if listings >= MAX_LISTINGS:
                break
            lst = screen.compile_s(row, cand)
            listings += 1
            if lst is None:
                continue
            d = sum(1 for y in difflib.unified_diff(target, lst, lineterm="", n=0)
                    if y[:1] in "+-" and not y.startswith(("---", "+++")))
            ranked.append((d, len(sites_of(cand)), label, cand))
        ranked.sort(key=lambda x: (x[0], x[1]))
        info.update(listings=listings, menu=len(menu))
        tried = 0
        for d, pins, label, cand in ranked:
            if tried >= MAX_VERIFY or (d and tried >= 2):
                break
            tried += 1
            if vf(cand).get("exact"):
                return cand, dict(info, step="%s|d%d" % (label, d), pins_out=pins, tried=tried)
        return None, dict(info, tried=tried,
                          nearest=[{"distance": d, "label": l} for d, _p, l, _c in ranked[:6]])
