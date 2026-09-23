"""T118: a variable updated in place (`v = E; v op= F;`) written as ONE set - the set-exactly-once family.

APPEARS     a local built up by a run of statements, next to keeps that "reorder the instructions":

                ASM_KEEP(effect_state);
                scaled_y = grid_y << 16;
                scaled_y >>= 10;
            ->  scaled_y = (grid_y << 16) >> 10;          (the keep, and two keeps 100 lines up, erased)

            dungeon/func_80CE7A1C (claude-opus-5-5, work/native_lane/r76_opus_b37_2, 3 of 5 pins), and an
            accumulator whose pinned argument register is set three times:

                register s32 dst_index ASM_REG("$4");
                dst_index = rect->unk_00;  dst_index += col;  ...  dst_index += row_offset;
            ->  col_index = rect->unk_00;  col_index += col;  ...  dst_index = col_index + row_offset;

            town/func_8032FD1C (r76o_opus_b37, 1 of 3).
MECHANISM   every ASM pin is a SET of its variable, and so is every `v op= F`.  gcc 2.x gives two boosts
            only to a pseudo with REG_N_SETS == 1: sched.c's `birthing_insn_p` raises the producer to
            LAUNCH_PRIORITY (so the backward scheduler emits it LAST in its block), and local-alloc.c's
            `update_equiv_regs` records REG_EQUIV and DOUBLES the register's live length (global.c's
            allocno priority is refs * log2(refs) / live_length, so the doubling halves it).  A variable
            written twice gets neither - the lanes kept such rows exact with a keep, a register pin or a
            one-trip block.  Written ONCE, the pseudo is born at its only set and the pins become
            unnecessary.  The opus lanes: "an `ASM_KEEP(v)` whose lone erasure is a same-opcode reorder
            ... fold `v <<= k; v >>= m;` into one expression, so each pseudo in the block is set once"
            (80CE7A1C); "the three-times-set `dst_index` (18 refs / 17 live) avoided $a0 ... single-set it
            is 6 refs / 5 live and takes $a0" (8032FD1C).
WHY THE OWNERS MISS IT  t100_rmwfold / t107_incstore / t115_carrierfold fold FIELD read-modify-writes and
            carriers into stores; nothing folds a local's own update chain or moves its prefix to a fresh
            local.  t85's split (b) splits two MEANINGS of a variable, not the steps of one value.
CANDIDATES  per chain - a single-line `v = E;` followed (pin lines and blank lines skipped) by one to three
            single-line `v op= F;` (F free of v) or `v = H(v);` (v read once) statements in the same block:
              fold    the chain as one set, `v = (E) op F`, by substitution;
              fold2   only the first two statements, when the chain is longer;
              split   (the accumulator) `v = E; v op= F; ...; v op= G;` whose LAST update is further down the
                      same block with no other write of v between: the prefix goes to a fresh local
                      `<v>_part` of v's type (declared after v), its reads in between renamed, and the last
                      update becomes `v = <v>_part op G;`.
            Only chains on a pinned variable (an ASM_REG declaration or a pin naming it) or within 8 lines
            of a pin.  Each text is taken with the pins naming v erased, and then GREEDILY: the remaining
            pins, those naming v first and then by line distance, are erased one at a time and an erasure
            is kept while the cc1 listing distance to the pinned text does not grow.  Ranked by listing
            distance; the listing-exact candidates (and the two nearest) go to `vf`.
"""
import difflib
import re
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
from pin_census import sites_of, asm_blocker, unscored_text
from pin_sites import erase_many
try:
    from .t29_addrsym import mask_comments, decls_of
    from .t36_paramwidth import functions
    from . import screen
except ImportError:
    from t29_addrsym import mask_comments, decls_of
    from t36_paramwidth import functions
    import screen

ID = r"[A-Za-z_]\w*"
MAX_SITES = 10
MAX_LISTINGS = 70
MAX_VERIFY = 4
GREEDY_TOP = 3
NEAR_LINES = 8
OPS = ("<<", ">>", "+", "-", "&", "|", "^", "*", "/", "%")
SET_RE = re.compile(r"^(?P<ind>[ \t]*)(?P<v>%s)[ \t]*=(?!=)[ \t]*(?P<rhs>[^;{}\n]+?)[ \t]*;[ \t]*(?P<tail>/\*.*\*/)?[ \t]*$" % ID)
UPD_RE = re.compile(r"^(?P<ind>[ \t]*)(?P<v>%s)[ \t]*(?P<op><<|>>|[-+&|^*/%%])=[ \t]*(?P<rhs>[^;{}\n]+?)[ \t]*;[ \t]*(?P<tail>/\*.*\*/)?[ \t]*$" % ID)
PIN_LINE = re.compile(r"^[ \t]*ASM_\w+[ \t]*\([^;]*\)[ \t]*;[ \t]*(?:/\*.*\*/)?[ \t]*$")
KEYW = {"if", "while", "for", "switch", "return", "case", "do", "else", "goto", "sizeof"}


def _word(v):
    return re.compile(r"(?<![\w.>])%s\b" % re.escape(v))


def _reads(expr, v):
    return len(_word(v).findall(expr))


def _balanced_outer(e):
    if not (e.startswith("(") and e.endswith(")")):
        return False
    d = 0
    for i, c in enumerate(e):
        d += (c == "(") - (c == ")")
        if d == 0 and i < len(e) - 1:
            return False
    return True


def _paren(e):
    """e as an operand: bare when it is a name, literal, member/array access, call or already wrapped."""
    e = e.strip()
    if re.fullmatch(r"[\w.\[\]]+(?:->[\w.\[\]]+)*", e) or re.fullmatch(r"%s\([^()]*\)" % ID, e) \
            or _balanced_outer(e):
        return e
    return "(" + e + ")"


MAX_SKIP = 2
TARGET_RE = re.compile(r"^[ \t]*(?P<t>%s)[ \t]*(?:<<|>>|[-+&|^*/%%])?=(?!=)" % ID)


def _target(line):
    m = TARGET_RE.match(line)
    return m.group("t") if m else None


def _pure(e):
    """No memory access, call or side effect: names, literals, casts and arithmetic only."""
    return not re.search(r"->|\[|\+\+|--|=|\b%s\s*\(" % ID, e.replace("<=", "").replace(">=", "")
                         .replace("==", "").replace("!=", "")) and "*" not in re.sub(r"\w\s*\*\s*\w", "", e)


def _indep(line, v, ind):
    """A single-line statement at the chain's indentation that neither reads nor writes v."""
    s = line.strip()
    if not s.endswith(";") or not line.startswith(ind) or line[len(ind):][:1] in (" ", "\t"):
        return False
    if re.match(r"^(?:%s\s*:|case\b|default\b|return\b|goto\b|break\b|continue\b)" % ID, s) or "{" in s or "}" in s:
        return False
    return not _reads(line, v) and _target(line) is not None


def _is_pin_or_blank(line):
    s = line.strip()
    return not s or PIN_LINE.match(line) or (s.startswith("/*") and s.endswith("*/"))


def _step(line, v):
    """One chain step on v: ('upd', op, rhs) / ('sub', rhs-with-v) / None."""
    m = UPD_RE.match(line)
    if m and m.group("v") == v and not _reads(m.group("rhs"), v):
        return ("upd", m.group("op"), m.group("rhs"))
    m = SET_RE.match(line)
    if m and m.group("v") == v and _reads(m.group("rhs"), v) == 1 and "(" + v + ")" != m.group("rhs").strip():
        if re.search(r"(\+\+|--)", m.group("rhs")):
            return None
        return ("sub", m.group("rhs"))
    return None


def _apply(expr, step, v):
    if step[0] == "upd":
        return "%s %s %s" % (_paren(expr), step[1], _paren(step[2]))
    return _word(v).sub(lambda _m: _paren(expr), step[1], count=1)


def _pinned_names(text):
    names = set()
    for s in sites_of(text):
        if s[0] == "expand":
            continue
        seg = text[s[3]:s[4]]
        names |= set(re.findall(ID, seg))
    return names


def _site_line(text, s):
    return text.count("\n", 0, s[3])


def _decl_line(lines, v, lo, hi):
    rx = re.compile(r"^[ \t]*(?:register[ \t]+)?(?P<ty>(?:(?:unsigned|signed|const)[ \t]+)*%s(?:[ \t]+long)?)[ \t]*(?P<p>\**)[ \t]*%s\b[^;]*;" % (ID, re.escape(v)))
    for i in range(lo, hi):
        m = rx.match(lines[i])
        if m and m.group("ty").split()[-1] not in KEYW | {"return"}:
            return i, (m.group("ty") + " " + m.group("p")).strip()
    return None, None


def sites(text):
    """[{fn, v, lines: [chain line numbers], steps, first_rhs, ind, split_at}] (0-based lines)."""
    masked = mask_comments(text)
    ml = masked.split("\n")
    tl = text.split("\n")
    pinl = sorted(_site_line(text, s) for s in sites_of(text) if s[0] != "expand")
    pnames = _pinned_names(text)
    out = []
    for fname, params, b0, b1 in functions(text):
        l0, l1 = masked.count("\n", 0, b0), masked.count("\n", 0, b1)
        i = l0
        while i <= l1 and len(out) < MAX_SITES:
            m = SET_RE.match(ml[i])
            if not m or m.group("v") in KEYW or _reads(m.group("rhs"), m.group("v")):
                i += 1
                continue
            v = m.group("v")
            chain, steps, j = [i], [], i + 1
            while j <= l1 and len(steps) < 3:
                k = j
                while k <= l1 and _is_pin_or_blank(ml[k]):
                    k += 1
                if k > l1:
                    break
                skipped = []
                while k <= l1 and len(skipped) < MAX_SKIP and not _step(ml[k], v) and _indep(ml[k], v, m.group("ind")):
                    skipped.append(k)
                    k += 1
                    while k <= l1 and _is_pin_or_blank(ml[k]):
                        k += 1
                if k > l1:
                    break
                st = _step(ml[k], v)
                if not st or not ml[k].startswith(m.group("ind")) or ml[k][len(m.group("ind")):][:1] in (" ", "\t"):
                    break
                if skipped:
                    # the step moves UP past the skipped statements: its operand must be pure and
                    # nothing skipped may write a name it reads
                    opnd = st[2] if st[0] == "upd" else st[1]
                    if not _pure(opnd) or any(_target(ml[q]) in set(re.findall(ID, opnd)) for q in skipped):
                        break
                chain.append(k)
                steps.append(st)
                j = k + 1
            near = v in pnames or any(abs(p - i) <= NEAR_LINES for p in pinl)
            if steps and near:
                site = {"fn": fname, "v": v, "lines": chain, "steps": steps, "first_rhs": m.group("rhs"),
                        "ind": m.group("ind"), "split_at": None, "l0": l0, "l1": l1}
                # split: the NEXT write of v further down the same block is a compound update
                depth, k = 0, chain[-1] + 1
                while k <= l1:
                    ln = ml[k]
                    depth += ln.count("{") - ln.count("}")
                    if depth < 0:
                        break
                    um = UPD_RE.match(ln)
                    if depth == 0 and um and um.group("v") == v and ln.startswith(m.group("ind")) \
                            and not _reads(um.group("rhs"), v):
                        site["split_at"] = k
                        break
                    if re.search(r"(?<![\w.>])%s\s*(?:=(?!=)|\+\+|--|[-+*/%%&|^]=|<<=|>>=)|(?:\+\+|--)\s*%s\b|&\s*%s\b"
                                 % ((re.escape(v),) * 3), ln):
                        break
                    if re.match(r"^\s*(?:%s\s*:|case\b|default\s*:)" % ID, ln):
                        break
                    k += 1
                out.append(site)
            i = chain[-1] + 1
    return out


def _fold_lines(tl, st, n):
    """The chain's first n+1 statements as one set (n steps)."""
    expr = st["first_rhs"].strip()
    for s in st["steps"][:n]:
        expr = _apply(expr, s, st["v"])
    return "%s%s = %s;" % (st["ind"], st["v"], expr)


def rewrite(text, st, form):
    tl = text.split("\n")
    v = st["v"]
    if form in ("fold", "fold2"):
        n = len(st["steps"]) if form == "fold" else 1
        keep = st["lines"][:n + 1]
        new = list(tl)
        new[keep[0]] = _fold_lines(tl, st, n)
        for k in keep[1:]:
            new[k] = None
        return "\n".join(x for x in new if x is not None)
    if form == "split":
        s_at = st["split_at"]
        if s_at is None:
            return None
        dl, ty = _decl_line(tl, v, st["l0"], st["lines"][0])
        if dl is None:
            return None
        fresh = v + "_part"
        if re.search(r"\b%s\b" % re.escape(fresh), text):
            return None
        new = list(tl)
        w = _word(v)
        for k in range(st["lines"][0], s_at):
            if PIN_LINE.match(new[k]):
                continue
            new[k] = w.sub(fresh, new[k])
        um = UPD_RE.match(tl[s_at])
        new[s_at] = "%s%s = %s %s %s;" % (um.group("ind"), v, fresh, um.group("op"), _paren(um.group("rhs")))
        ind = re.match(r"[ \t]*", tl[dl]).group(0)
        ty = re.sub(r"\bregister\s+", "", ty)
        new.insert(dl + 1, "%s%s %s;" % (ind, ty, fresh) if not ty.endswith("*") else "%s%s%s;" % (ind, ty, fresh))
        return "\n".join(new)
    return None


def _named(text, v):
    out = []
    for s in sites_of(text):
        if s[0] == "expand":
            continue
        seg = text[s[3]:s[4]]
        if re.search(r"\b%s\b" % re.escape(v), seg):
            out.append(s)
    return out


def menu(text):
    """[(label, text, names, anchor line)] - rewritten texts with the pins naming the variable erased
    (and, as a second entry, with them kept)."""
    sig, out, seen = unscored_text(text), [], {text}
    sts = sites(text)
    per = []
    for st in sts:
        forms = ["fold"] + (["fold2"] if len(st["steps"]) > 1 else []) + (["split"] if st["split_at"] else [])
        for f in forms:
            per.append((st, f))
    plans = [("%s@%d:%s" % (st["v"], st["lines"][0] + 1, f), [(st, f)]) for st, f in per]
    folds = [(st, "fold") for st in sts]
    if len(folds) > 1:
        plans.append(("joint:fold", folds))
    for label, ch in plans:
        cur = text
        ok = True
        for st, f in sorted(ch, key=lambda c: -c[0]["lines"][0]):
            # later sites first: earlier line numbers stay valid (split inserts ONE line after the decl,
            # which sits above every chain, so a later chain's lines are rewritten before it moves)
            nxt = rewrite(cur, st, f)
            if nxt is None:
                ok = False
                break
            cur = nxt
        if not ok or cur in seen or unscored_text(cur) != sig:
            continue
        names = {st["v"] for st, _f in ch}
        anchor = min(st["lines"][0] for st, _f in ch)
        for tag, t2 in (("named", erase_many(cur, [s for v in names for s in _named(cur, v)], clean_notes=True)),
                        ("kept", cur)):
            if t2 in seen:
                continue
            seen.add(t2)
            out.append(("%s:%s" % (label, tag), t2, names, anchor))
    return out


class T:
    name = "t118_setonce"
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
            return "no in-place update chain (`v = E; v op= F;`) on a pinned variable or near a pin"
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
        listings = 0
        ranked = []
        for label, cand, names, anchor in mn:
            if listings >= MAX_LISTINGS:
                break
            lst = screen.compile_s(row, cand); listings += 1
            if lst is None:
                continue
            ranked.append((screen.sdiff(target, lst), len(sites_of(cand)), label, cand, names, anchor))
        ranked.sort(key=lambda x: (x[0], x[1]))
        # greedy joint erasure on the nearest rewrites
        extra = []
        for d0, _p, label, cand, names, anchor in ranked[:GREEDY_TOP]:
            cur, dcur, steps = cand, d0, 0
            order = sorted((s for s in sites_of(cand) if s[0] != "expand"),
                           key=lambda s: (not any(re.search(r"\b%s\b" % re.escape(v), cand[s[3]:s[4]]) for v in names),
                                          abs(_site_line(cand, s) - anchor)))
            keys = [(s[3], cand[s[3]:s[4]]) for s in order]
            for off, seg in keys:
                if listings >= MAX_LISTINGS:
                    break
                live = [s for s in sites_of(cur) if s[0] != "expand" and cur[s[3]:s[4]] == seg
                        and abs(s[3] - off) < 4000]
                if not live:
                    continue
                s = min(live, key=lambda s: abs(s[3] - off))
                t2 = erase_many(cur, [s], clean_notes=True)
                lst = screen.compile_s(row, t2); listings += 1
                dd = screen.sdiff(target, lst)
                if dd is not None and dd <= dcur:
                    cur, dcur, steps = t2, dd, steps + 1
            if steps:
                extra.append((dcur, len(sites_of(cur)), label + ":greedy%d" % steps, cur, names, anchor))
        ranked += extra
        ranked = [r for r in ranked if r[1] < pins_in]
        ranked.sort(key=lambda x: (x[0], x[1]))
        info.update(listings=listings, menu=len(mn))
        tried, seen = 0, set()
        for d, pins, label, cand, _n, _a in ranked:
            if cand in seen:
                continue
            seen.add(cand)
            if tried >= MAX_VERIFY or (d and tried >= 2):
                break
            tried += 1
            if vf(cand).get("exact"):
                return cand, dict(info, step="%s|d%d" % (label, d), pins_out=pins, tried=tried)
        return None, dict(info, tried=tried,
                          nearest=[{"distance": d, "pins": p, "label": l} for d, p, l, *_ in ranked[:6]])
