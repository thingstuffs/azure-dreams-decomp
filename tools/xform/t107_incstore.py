"""T107: a staged increment `v++; LV = v;` folded into the store (`LV = v + 1;`) or into the load (`v = LV++;`).

APPEARS     a counter read from a field, pinned, stepped in a local and stored back - m2c's scalarised
            spelling of one post-increment - in two lanes of two models:

              astra (dungeon/func_813385D8, work/native_lane/r74_astra_a1, 4 pins with a register pin):
                  slow_count = state->unk_9E;
                  ASM_KEEP(slow_count);
                  signed_count = slow_count;  phase = signed_count * 0xAA;
                  slow_count++;
                  state->unk_9E = slow_count;
              ->  slow_count = state->unk_9E++;          (twice), and for the third site
                  ASM_KEEP(fast_count); fast_count++; state->unk_9E = fast_count;
              ->  state->unk_9E = fast_count + 1;

              gpt-6-sol (dungeon/func_80D3B9B0, work/native_lane/r73_sol6_a8, 2 of its 3 pins):
                  ASM_KEEP_DEP_NV(bob_step, bob_phase);
                  bob_step++;
                  (*(u16 *)((u8 *)object_arg + (0x9E))) = bob_step;
              ->  (*(u16 *)((u8 *)object_arg + (0x9E))) = bob_step + 1;       (twice)

RESOLVES    sol's rule: "APPEARS when a post-incremented narrow field is written back before a call ...
            RESOLVES by storing the increment expression to the field ..."; astra's (r74_astra_a1
            REPORT): the post-increment at the load.  Mechanism: `v++; LV = v;` gives the incremented
            value its own set of v, so v is set twice and loses sched.c's one-set birthing priority
            (`reg_n_sets == 1`), and the store reads the second set; written as one expression the
            increment is a temporary consumed by the store and v keeps a single set - the pin was
            holding the order that single set gives.  This is the statement-granularity family of the
            combined ranking (r67 D, r71 D+E, r72 #5 / t100_rmwfold) in its one-variable spelling.

WHY THE OWNER MISSES IT (measured 2026-09-23, work/native_lane/r73_h_probe2_t100_rmwfold_*)
            t100_rmwfold refuses both rows "no scalarised read-modify-write": it looks for SIBLING
            load/op/store triples over distinct lvalues with the op a compound assignment by a
            constant, not `v++` and not an increment whose loaded value is read in between.

CANDIDATES  per `v++;` (or `++v;`, `v += 1;`) followed by `LV = v;`: (plus) the increment dropped and the
            store written `LV = v + 1;`; (postinc) when the nearest earlier statement of the block
            assigning v is `v = LV;` (same lvalue text, no call and no mention of LV between):
            `v = LV++;` with the increment and the store dropped; (early) the store written `LV = v + 1;`
            straight after that load and the increment kept, for a v read again later (astra's third
            site).  Every site alone, and all sites
            together in every assignment of the two forms (labels `a` plus / `p` postinc / `e` early;
            the load forms only where they apply, at most four sites); each
            with no pin erased, with the pins naming v in the site's window, with every pin in the
            window, and with every pin of the row.  Ranked by cc1 listing distance to the pinned text; the
            listing-exact candidates and the two nearest go to `vf`.
"""
import difflib
import itertools
import re
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
from pin_census import sites_of, asm_blocker, unscored_text
from pin_sites import erase_many
try:
    from .t29_addrsym import mask_comments
    from .t72_stmtperm import CAST
    from . import screen
except ImportError:
    from t29_addrsym import mask_comments
    from t72_stmtperm import CAST
    import screen

MAX_SITES = 8
MAX_LISTINGS = 120
MAX_VERIFY = 4
INC = re.compile(r"^(?P<ind>[ \t]*)(?:(?P<v1>[A-Za-z_]\w*)[ \t]*\+\+|\+\+[ \t]*(?P<v2>[A-Za-z_]\w*)|(?P<v3>[A-Za-z_]\w*)[ \t]*\+=[ \t]*1)[ \t]*;[ \t]*$")
STORE = r"^(?P<ind>[ \t]*)(?P<lv>[^=;{}]*?[^=!<>+\-*/%&|^ \t])[ \t]*=[ \t]*@V@[ \t]*;[ \t]*$"
PIN_RE = re.compile(r"^[ \t]*ASM_[A-Z0-9_]+\s*\(")
CALL_RE = re.compile(r"\b[A-Za-z_]\w*\s*\(")


def _norm(s):
    return re.sub(r"\s+", "", s)


def sites(text):
    """[{v, inc, store, lv, load}] - 0-based line numbers; `load` is None when only `plus` applies."""
    ml = mask_comments(text).split("\n")
    out = []
    for i, l in enumerate(ml):
        m = INC.match(l)
        if not m:
            continue
        v = m.group("v1") or m.group("v2") or m.group("v3")
        j = i + 1
        while j < len(ml) and (not ml[j].strip() or PIN_RE.match(ml[j])):
            j += 1
        if j >= len(ml):
            continue
        s = re.match(STORE.replace("@V@", re.escape(v)), ml[j])
        if not s or CALL_RE.search(CAST.sub(" ", s.group("lv"))) \
                or re.search(r"\b%s\b" % re.escape(v), s.group("lv")):
            continue
        lv = s.group("lv").strip()
        load = None
        k = i - 1
        while k >= 0:
            t = ml[k]
            if "{" in t or "}" in t or re.match(r"^[ \t]*(?:case\b|default\b|\w+:)", t):
                break
            a = re.match(r"^[ \t]*%s[ \t]*=(?!=)[ \t]*(?P<rhs>[^;]*);[ \t]*$" % re.escape(v), t)
            if a:
                if _norm(a.group("rhs")) == _norm(lv):
                    load = k
                break
            if not PIN_RE.match(t) and (CALL_RE.search(CAST.sub(" ", t))
                                        or _norm(lv) in _norm(t)):
                break
            k -= 1
        out.append({"v": v, "inc": i, "store": j, "lv": lv, "load": load})
        if len(out) >= MAX_SITES:
            break
    return out


def rewrite(text, pairs):
    """`pairs` = [(site, form)] with form 'plus' or 'postinc'."""
    lines = text.split("\n")
    drop, repl = set(), {}
    for st, form in pairs:
        ind = re.match(r"^[ \t]*", lines[st["store"]]).group(0)
        tail = lines[st["store"]][lines[st["store"]].rfind(";") + 1:]
        if form == "plus":
            drop.add(st["inc"])
            repl[st["store"]] = "%s%s = %s + 1;%s" % (ind, st["lv"], st["v"], tail)
        elif form == "early":
            if st["load"] is None:
                return None
            lind = re.match(r"^[ \t]*", lines[st["load"]]).group(0)
            repl[st["load"]] = lines[st["load"]] + "\n%s%s = %s + 1;" % (lind, st["lv"], st["v"])
            drop.add(st["store"])
        else:
            if st["load"] is None:
                return None
            lind = re.match(r"^[ \t]*", lines[st["load"]]).group(0)
            ltail = lines[st["load"]][lines[st["load"]].rfind(";") + 1:]
            repl[st["load"]] = "%s%s = %s++;%s" % (lind, st["v"], st["lv"], ltail)
            drop.update((st["inc"], st["store"]))
    return "\n".join(repl.get(q, l) for q, l in enumerate(lines) if q not in drop)


def candidates(text):
    sig, n0 = unscored_text(text), len(sites_of(text))
    ss = sites(text)
    out, seen = [], {text}
    plans = []
    # every site together, in every assignment of the two forms (the load form only where there is a
    # load; at most 16 assignments), then each site alone in each form
    opts = [("plus", "postinc", "early") if s["load"] is not None else ("plus",) for s in ss[:4]]
    if len(ss) > 1:
        for combo in itertools.product(*opts):
            plans.append(("".join(f[0] if f != "plus" else "a" for f in combo), "all", list(zip(ss[:4], combo))))
    for s_ in ss:
        for f in (("plus", "postinc", "early") if s_["load"] is not None else ("plus",)):
            plans.append((f, "%d" % (s_["inc"] + 1), [(s_, f)]))
    for form, tag, pairs in plans:
        chosen = [p for p, _ in pairs]
        base = rewrite(text, pairs)
        if base is None:
            continue
        pins = sites_of(base)
        rx = re.compile(r"\b(?:%s)\b" % "|".join(sorted({re.escape(s["v"]) for s in chosen})))
        los = [min(s["inc"], s["load"] if s["load"] is not None else s["inc"]) - 2 for s in chosen]
        his = [s["store"] + 1 for s in chosen]
        win = [p for p in pins if any(lo <= p[5] - 1 <= hi for lo, hi in zip(los, his))]
        named = [p for p in win if rx.search(base[p[3]:p[4]])]
        for ptag, group in (("none", []), ("named", named), ("win", win), ("all", pins)):
            cand = erase_many(base, group, clean_notes=True) if group else base
            if cand in seen or unscored_text(cand) != sig or (ptag != "none" and len(sites_of(cand)) >= n0):
                continue
            seen.add(cand)
            out.append(("%s@%s:%s" % (form, tag, ptag), cand))
    return out


def _dist(a, b):
    return sum(1 for y in difflib.unified_diff(a, b, lineterm="", n=0)
               if y[:1] in "+-" and not y.startswith(("---", "+++")))


class T:
    name = "t107_incstore"
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
            return "no staged increment stored back"
        return None

    @classmethod
    def apply_verified(cls, text, row, census, vf):
        pins_in = len(sites_of(text))
        info = {"pins_in": pins_in, "pins_out": pins_in, "sites": len(sites(text))}
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
            lst = screen.compile_s(row, cand); listings += 1
            if lst is None:
                continue
            ranked.append((_dist(target, lst), len(sites_of(cand)), label, cand))
        ranked.sort(key=lambda x: (x[0], x[1]))
        info.update(listings=listings, menu=len(menu))
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
