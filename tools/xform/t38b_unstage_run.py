"""T38b: t38 generalised - a value staged through ANY pinned local and stored one or more times in a run.

APPEARS     `X = E;` followed, within a run of staging and pin lines, by one or more stores `LHS = (cast)X;`,
            where X is a pinned local (an `ASM_REG` declaration, or named by an `ASM_KEEP*`), E names no X, and the
            staged value has no other reader before X is next assigned:
                texture_id = 0x7DCF;
                texture_v = 0x40;
                ASM_KEEP_NV(texture_v);
                packet->unk_0E = texture_id;
                packet->unk_0C = texture_u;
                packet->unk_0D = texture_v;
                packet->unk_19 = texture_v;
RESOLVES    Gemini pack r58_order2 (round 58), `dungeon/func_818B6F90`: the constants stored directly, both pins
            gone. t38 needs the store to follow the staging IMMEDIATELY and X to be `ASM_REG`-pinned; here the
            stagings interleave, a keep sits between, and a value is stored twice. Every staging in the run is
            inlined into all its stores (jointly, then each staging alone), the staging lines dropped, then the
            pins nearest the run erased singly (t38's pairing), and jointly.
"""
import re, sys
from pathlib import Path
sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
from pin_census import sites_of, unscored_text
from pin_sites import erase_many
try:
    from .t29_addrsym import mask_comments
    from .t38_unstage import drop_unused
except ImportError:
    from t29_addrsym import mask_comments
    from t38_unstage import drop_unused

MAX_CANDS = 40
PINS_PER_SITE = 8
STAGE_LINE = re.compile(r"^(?P<ind>[ \t]*)(?P<x>[A-Za-z_]\w*)\s*=(?!=)\s*(?P<e>[^;=]+);[ \t]*$")
STORE_LINE = re.compile(r"^(?P<ind>[ \t]*)(?P<lhs>[^;=\n]+?)\s*=(?!=)\s*(?P<cast>\([^()]*\)\s*)?(?P<x>[A-Za-z_]\w*)\s*;[ \t]*$")
PIN_LINE = re.compile(r"^[ \t]*ASM_[A-Z0-9_]+\s*\(")


def pinned_locals(masked):
    out = set(re.findall(r"register\s+[\w\s\*]+?\b(\w+)\s+ASM_REG\(", masked))
    for m in re.finditer(r"ASM_KEEP[A-Z_]*\(\s*([^()]*)\)", masked):
        out.update(re.findall(r"[A-Za-z_]\w*", m.group(1)))
    return out


def runs(text):
    """[(first_line, last_line, {X: (E, [store_lines])})] for each staging run with at least one pinned staging."""
    m = mask_comments(text)
    ls = m.split("\n")
    pl = pinned_locals(m)
    out, i = [], 0
    while i < len(ls):
        sm = STAGE_LINE.match(ls[i])
        if not sm or sm.group("x") not in pl or "(" in sm.group("e") and re.search(r"\w\s*\(", sm.group("e")):
            i += 1
            continue
        stages, stores, j = {}, {}, i
        while j < len(ls):
            s = ls[j]
            sm = STAGE_LINE.match(s); st = STORE_LINE.match(s)
            if st and st.group("x") in stages and not re.search(r"[-+*/%&|^<>!]$", st.group("lhs").strip()) \
                    and not re.search(r"\b%s\b" % re.escape(st.group("x")), st.group("lhs")):
                stores.setdefault(st.group("x"), []).append(j); j += 1; continue
            if sm and (sm.group("x") in pl or stages) and not re.search(r"\w\s*\(", sm.group("e")) \
                    and not any(re.search(r"\b%s\b" % re.escape(x), sm.group("e")) for x in stages):
                if sm.group("x") in stages:
                    break                                          # X reassigned: the run ends before it
                stages[sm.group("x")] = (sm.group("e").strip(), j); j += 1; continue
            if PIN_LINE.match(s) or not s.strip():
                j += 1; continue
            # any other simple statement that names no staged value may sit inside the run (it reads none of them)
            if s.rstrip().endswith(";") and "{" not in s and "}" not in s and not re.match(r"^[ \t]*(?:if|for|while|do|switch|return|goto|case|default|else)\b", s) \
                    and not any(re.search(r"\b%s\b" % re.escape(x), s) for x in stages):
                j += 1; continue
            break
        good = {}
        for x, (e, line) in stages.items():
            if x not in stores or x not in pl:
                continue
            rest = "\n".join(ls[max(stores[x]) + 1:])
            nxt = re.search(r"\b%s\b" % re.escape(x), rest)
            if nxt and not re.match(r"\s*=(?!=)", rest[nxt.end():]):
                continue                                           # read again later
            good[x] = (e, line, stores[x])
        if good:
            out.append((i, j - 1, good))
        i = max(j, i + 1)
    return out


def inline_run(text, run, which):
    """Text with the stagings in `which` inlined into their stores and their staging lines removed."""
    ls = text.split("\n")
    a, b, stages = run
    drop = set()
    for x in which:
        e, line, store_lines = stages[x]
        unary = re.fullmatch(r"(?:\(\s*[A-Za-z_][\w\s\*]*\)\s*)*(?:[A-Za-z_][\w.\[\]>-]*|-?(?:0x[0-9A-Fa-f]+|\d+)[UuLl]*)", e)
        for sl in store_lines:
            st = STORE_LINE.match(mask_comments(ls[sl]) if "/*" in ls[sl] else ls[sl])
            cast = (st.group("cast") or "").strip()
            rhs = cast + e if (not cast or unary) else cast + "(" + e + ")"
            ls[sl] = st.group("ind") + st.group("lhs").strip() + " = " + rhs + ";"
        drop.add(line)
    return "\n".join(l for k, l in enumerate(ls) if k not in drop)


def candidates(text):
    out, seen = [], set()
    usig = unscored_text(text)
    for run in runs(text):
        a, b, stages = run
        plans = [list(stages)] + ([[x] for x in stages] if len(stages) > 1 else [])
        for which in plans:
            t1 = inline_run(text, run, which)
            if unscored_text(t1) != usig:
                continue
            for x in which:
                t1 = drop_unused(t1, x)
            pins = sorted(sites_of(t1), key=lambda s: abs(s[5] - a))[:PINS_PER_SITE]
            trials = [[p] for p in pins] + ([pins] if len(pins) > 1 else [])
            for group in trials:
                t = erase_many(t1, group, clean_notes=True)
                for x in which:
                    t = drop_unused(t, x)
                if t not in seen and unscored_text(t) == usig and len(sites_of(t)) < len(sites_of(text)):
                    seen.add(t); out.append(("unstage_run:%s@%d-%d" % ("+".join(which), a + 1, len(group)), t))
            if len(out) >= MAX_CANDS:
                return out[:MAX_CANDS]
    return out


class T:
    name = "t38b_unstage_run"; level = 1
    needs_verify = True

    @staticmethod
    def eligible(text, row, census):
        if not sites_of(text):
            return "no pin sites"
        if not runs(text):
            return "no staging run through a pinned local"
        return None

    @staticmethod
    def apply_verified(text, row, census, vf):
        cands = candidates(text)
        if not cands:
            return None, {"refused": ["no buildable candidate"]}
        for label, t in cands:
            if vf(t).get("exact"):
                return t, {"label": label, "tried": cands.index((label, t)) + 1}
        # the inlining alone is not exact: the stores may also sit in another order (Gemini's func_818B6F90 moved two
        # stores past the inlined ones), so each inlined text, its run's pins erased, goes through an order search of
        # the run's statements screened by the cc1 listing (t72's machinery), the pinned text's listing as retail
        try:
            from . import t72_stmtperm as P
            from . import screen
        except ImportError:
            import t72_stmtperm as P
            import screen
        target = screen.compile_s(row, text)
        usig, seen, tried, listings = unscored_text(text), set(), len(cands), 0
        if target is None:
            return None, {"refused": ["no candidate exact at the recorded cell; pinned text has no listing"], "tried": tried}
        m_all = mask_comments(text)
        locals_ = P.decl_names(m_all) | set(re.findall(r"\b(\w+)\s*[,)]", m_all[:m_all.find("{")] if "{" in m_all else ""))
        taken = set(re.findall(r"&\s*([A-Za-z_]\w*)", m_all))
        for run in runs(text):
            a, b, stages = run
            for which in [list(stages)] + ([[x] for x in stages] if len(stages) > 1 else []):
                t1 = inline_run(text, run, which)
                for x in which:
                    t1 = drop_unused(t1, x)
                if unscored_text(t1) != usig:
                    continue
                # erase the pins of the inlined values (they name dropped locals) and the run's other pins
                ls1 = t1.split("\n")
                shift = len(which)                                    # staging lines removed above the stores
                pins = [s for s in sites_of(t1) if a - 2 <= s[5] - 1 <= b + 2 or any(re.search(r"\b%s\b" % re.escape(x), s[2] or "") for x in which)]
                t2 = erase_many(t1, pins, clean_notes=True) if pins else t1
                if t2 in seen or len(sites_of(t2)) >= len(sites_of(text)):
                    continue
                seen.add(t2)
                ml = mask_comments(t2).split("\n")
                lo, hi = max(0, a - 3), min(len(ml) - 1, b - len(pins) - shift + 3)
                toks = [tk for tk in P.tokens(ml, lo - 1, hi + 1) if tk[0] == "stmt"]
                ind = None
                # the statements at the run's indentation, contiguous
                cands2 = []
                for tk in toks:
                    if ind is None:
                        ind = tk[3]
                    if tk[3] == ind:
                        cands2.append(tk)
                if len(cands2) < 2:
                    continue
                stmts = [P.Stmt(t2.split("\n")[tk[1]:tk[2] + 1], tk[1], tk[2], locals_, taken) for tk in cands2][:P.RUN]
                exact = []
                for perm in P.orders(stmts, P.MAX_ORDERS):
                    if listings >= P.MAX_LISTINGS:
                        break
                    cand = P.build(t2, stmts, perm, set())
                    lst = screen.compile_s(row, cand); listings += 1
                    if lst is not None and P.dist(target, lst) == 0:
                        exact.append((perm, cand))
                for perm, cand in exact[:6]:
                    tried += 1
                    if vf(cand).get("exact"):
                        return cand, {"label": "unstage_run+order:%s@%d perm%s" % ("+".join(which), a + 1, "".join(map(str, perm))), "tried": tried, "listings": listings}
        return None, {"refused": ["no candidate exact at the recorded cell"], "tried": tried}
