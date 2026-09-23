"""T120: a `volatile` qualifier dropped together with the register pins it was propping up.

APPEARS     a lane-made volatile access next to a register pin on the value it produces:

                register s32 old_base ASM_REG("$6");
                old_base = *(volatile u8 *)(initial_stats + 5);
            ->  s32 old_base;
                old_base = initial_stats[5];              (the t120 spelling: `*(u8 *)(initial_stats + 5)`)

            dungeon/func_8009C5EC (astra, work/native_lane/r76_astra_b37_1, 1 of 4): "APPEARS: a pinned wide local
            receives a volatile byte load, and erasing the binding introduces a redundant extension/mask. RESOLVES:
            remove the recovered volatile access together with the register binding, allowing `combine` to form a
            zero-extending memory load";  and a volatile stack slot (dungeon/func_813236DC, claude-opus-5-5,
            r76o_opus_b37, 4 of 4 with the parameter narrowed): "make the slot a plain local of its store width (the
            allocator spills it by itself)".
MECHANISM   a volatile MEM is never combined, cse'd or scheduled across another volatile access, so it pins a
            load's form and order by itself - and a register pin was then needed to undo the side effects
            (the `andi` a volatile byte load keeps, the extra copy).  Plain, combine folds the zero extension into
            the `lbu` and the value is a single-set pseudo again (the set-exactly-once family): the pin is not
            needed.  `volatile` is scaffolding under charter rule 3; this move only ever removes it.
WHY THE OWNERS MISS IT  no generator edits a qualifier: every menu keeps the volatile the lanes added.
CANDIDATES  per volatile site in a function body - a `volatile` in a local declaration, or a `(volatile T *)`
            cast - the qualifier dropped (a declaration's `*(T *)&v = X` store spelled `v = X`), singly and all
            the function's sites jointly; each text GREEDILY loses pins - those naming the variable the site
            reads or declares first, then by line distance - an erasure kept while the cc1 listing distance to
            the pinned text does not grow.  Ranked by listing distance; listing-exact candidates (and the two
            nearest) go to `vf`.  A candidate must remove at least one pin site.
"""
import re
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
from pin_census import sites_of, asm_blocker, unscored_text
from pin_sites import erase_many
try:
    from .t36_paramwidth import functions
    from . import screen
except ImportError:
    from t36_paramwidth import functions
    import screen

ID = r"[A-Za-z_]\w*"
MAX_SITES = 8
MAX_LISTINGS = 60
MAX_VERIFY = 4
GREEDY_TOP = 3
DECL_V = re.compile(r"^(?P<ind>[ \t]+)(?P<pre>(?:(?:static|register|unsigned|signed|const)[ \t]+)*)volatile[ \t]+"
                    r"(?P<rest>[A-Za-z_]\w*[ \t\*]*(?P<v>%s)[^;\n]*;)" % ID, re.M)
CAST_V = re.compile(r"\([ \t]*volatile[ \t]+(?P<t>[A-Za-z_][\w \t]*\*+)[ \t]*\)")


def sites(text):
    """[{fn, kind, span, line, names}] - volatile qualifiers inside function bodies (0-based line)."""
    out = []
    for fname, _params, b0, b1 in functions(text):
        for m in DECL_V.finditer(text, b0, b1):
            out.append({"fn": fname, "kind": "decl", "span": (m.start(), m.end()), "v": m.group("v"),
                        "line": text.count("\n", 0, m.start()), "names": {m.group("v")}})
        for m in CAST_V.finditer(text, b0, b1):
            ls = text.rfind("\n", 0, m.start()) + 1
            le = text.find("\n", m.end())
            stmt = text[ls:le]
            lhs = re.match(r"^[ \t]*(%s)[ \t]*=" % ID, stmt)
            names = set(re.findall(ID, stmt[m.end() - ls:])) - {"volatile"}
            if lhs:
                names.add(lhs.group(1))
            out.append({"fn": fname, "kind": "cast", "span": (m.start(), m.end()), "v": lhs.group(1) if lhs else None,
                        "line": text.count("\n", 0, m.start()), "names": names})
        if len(out) >= MAX_SITES:
            break
    return out[:MAX_SITES]


def drop(text, chosen):
    """The qualifiers of `chosen` dropped, last first (spans stay valid)."""
    t = text
    for st in sorted(chosen, key=lambda s: -s["span"][0]):
        a, b = st["span"]
        seg = t[a:b]
        if st["kind"] == "decl":
            seg = re.sub(r"\bvolatile[ \t]+", "", seg, count=1)
        else:
            seg = CAST_V.sub(lambda m: "(" + m.group("t").strip() + ")", seg, count=1)
        t = t[:a] + seg + t[b:]
        if st["kind"] == "decl":
            v = re.escape(st["v"])
            # the lanes' volatile-slot store spelling, `*(T *)&v = X;`, back to a plain assignment
            t = re.sub(r"\*[ \t]*\([ \t]*[A-Za-z_][\w \t]*\*[ \t]*\)[ \t]*&[ \t]*%s\b(?=[ \t]*=(?!=))" % v, st["v"], t)
    return t


def menu(text):
    sig = unscored_text(text)
    out, seen = [], {text}
    sts = sites(text)
    plans = [("%s@%d" % (st["kind"], st["line"] + 1), [st]) for st in sts]
    byfn = {}
    for st in sts:
        byfn.setdefault(st["fn"], []).append(st)
    for fn, ch in byfn.items():
        if len(ch) > 1:
            plans.append(("joint:%s" % fn, ch))
    for label, ch in plans:
        t = drop(text, ch)
        if t in seen or unscored_text(t) != sig:
            continue
        seen.add(t)
        names = set().union(*(st["names"] for st in ch))
        out.append((label, t, names, min(st["line"] for st in ch)))
    return out


class T:
    name = "t120_unvolatile"
    level = 1
    needs_verify = True

    @staticmethod
    def eligible(text, row, census):
        why = asm_blocker(text)
        if why:
            return why
        if not sites_of(text):
            return "no pin sites"
        if not sites(text):
            return "no volatile qualifier in a function body"
        return None

    @classmethod
    def apply_verified(cls, text, row, census, vf):
        pins_in = len(sites_of(text))
        info = {"pins_in": pins_in, "pins_out": pins_in}
        mn = menu(text)
        if not mn:
            return None, dict(info, refused=["no buildable candidate"])
        target = screen.compile_s(row, text)
        if target is None:
            return None, dict(info, refused=["pinned text does not build to a listing"])
        listings, ranked = 0, []
        for label, cand, names, anchor in mn:
            if listings >= MAX_LISTINGS:
                break
            lst = screen.compile_s(row, cand); listings += 1
            if lst is None:
                continue
            ranked.append((screen.sdiff(target, lst), label, cand, names, anchor))
        ranked.sort(key=lambda x: x[0])
        found = []
        for d0, label, cand, names, anchor in ranked[:GREEDY_TOP]:
            cur, dcur, steps = cand, d0, 0
            order = sorted((s for s in sites_of(cand) if s[0] != "expand"),
                           key=lambda s: (not any(re.search(r"\b%s\b" % re.escape(v), cand[s[3]:s[4]]) for v in names),
                                          abs(cand.count("\n", 0, s[3]) - anchor)))
            for s0 in order:
                if listings >= MAX_LISTINGS:
                    break
                seg = cand[s0[3]:s0[4]]
                live = [s for s in sites_of(cur) if s[0] != "expand" and cur[s[3]:s[4]] == seg]
                if not live:
                    continue
                s = min(live, key=lambda s: abs(s[3] - s0[3]))
                t2 = erase_many(cur, [s], clean_notes=True)
                lst = screen.compile_s(row, t2); listings += 1
                dd = screen.sdiff(target, lst)
                if dd is not None and dd <= dcur:
                    cur, dcur, steps = t2, dd, steps + 1
            if steps:
                found.append((dcur, len(sites_of(cur)), label + ":greedy%d" % steps, cur))
        found.sort(key=lambda x: (x[0], x[1]))
        info.update(listings=listings, menu=len(mn))
        tried = 0
        for d, pins, label, cand in found:
            if tried >= MAX_VERIFY or (d and tried >= 2):
                break
            tried += 1
            if vf(cand).get("exact"):
                return cand, dict(info, step="%s|d%d" % (label, d), pins_out=pins, tried=tried)
        return None, dict(info, tried=tried,
                          nearest=[{"distance": d, "pins": p, "label": l} for d, p, l, _c in found[:6]])
