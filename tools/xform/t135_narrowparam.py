"""T135: a parameter declared `s32` whose every use is narrow - declare it `s16`/`u16`, drop its register copies and pins.

MECHANISM   r81_opus_fc4 (dungeon/func_8009A734, 2 -> 0) and r81_opus_fc6 (dungeon/func_81875B38, 4 -> 0).
            assign_parms (function.c) gives a parameter narrower than its passing mode a REAL pseudo with a conversion
            copy at entry (PROMOTE_PROTOTYPES) instead of a REG_EQUIV memory it can be reloaded from; a stack
            parameter (arg 5+) that is never written carries REG_EQUIV to its slot and is reloaded at each use.  m2c
            sees the retail registers and writes the effect as copies: `register s32 raw ASM_REG("$6") = x0;`,
            `held = loaded = y1;` next to `(s16)x0` casts and `x0 & 0xFFFF` arguments.  Declaring the PARAMETER at its
            real width makes assign_parms create those pseudos; the copies and their ASM_REG / ASM_KEEP pins were only
            imitating them.

WHAT T135 ADDS  over t36_paramwidth (which goes the other way: it WIDENS a narrow parameter that a pinned narrow local
            copies, with the copy kept) and over t84_narrowparams (the real sibling: it narrows `s32` parameters, but
            only when every parameter is `s32` and each copy is a declaration-line `register s32 x ASM_REG = param;`,
            groups s16/u16 blindly, verifies only listing-exact candidates at the row's own cell, retypes one plain
            prototype, and erases pins all-or-nothing):
            1. copy shapes: any local written ONCE from a parameter or from another copy (decl initialiser or a
               deferred `R = P;`, also through a same-width cast `R = (s16)P;`) - `u16 raw_y0 = y0;`, `held_x1 = x1;`,
               `loaded_y1 = y1; held_y1 = loaded_y1;`; pins may stand on the declaration or as a later ASM_KEEP;
            2. the width comes from the evidence: `(s16)X` -> s16, `(u16)X` / `X & 0xFFFF` -> u16 (`s8`/`u8` for
               0xFF); each parameter is offered at its own evidence width, then all s16, then all u16;
            3. the parameter groups: every evident parameter together, each singly, plus the s32 parameters before
               the first of them (t84's prev/all groups);
            4. the section-attribute forward declaration and file-local prototypes follow the definition (t132's
               sync_attr_protos + t36's prototype retype);
            5. the remaining pins are erased JOINTLY through t132's menu (singly, nearest pairs, all ASM_REG, all
               keeps, all), not only "all" and "none";
            6. the casts of the now-narrow parameter (`(s16)x0`) are offered stripped and kept;
            7. cell menu: a candidate is verified at the row's own cfg, without its `-fno-*` crutch flags, and at
               `2.7.2-cdk-G0` (both fc rows went exact only after a cell move); a hit at another cell reports
               info["cfg"].
            NOT done: rewriting callee prototypes to `u16` (fc4 did on 8009A734) and the u16 locals of 81875B38.
A signature change: info["signature_change"] names the function (review textual callers at landing).
Only `vf` accepts; the first exact candidate with strictly fewer pins wins.
Env: T135_VERIFY (verify budget per cfg, default 40), T135_CFGS (extra stock cells).
"""
import itertools
import os
import re
import sys
from pathlib import Path

_HERE = Path(__file__).resolve()
for _cand in (_HERE.parents[1], _HERE.parents[2] / "tools"):
    if (_cand / "pin_census.py").exists():
        sys.path.insert(0, str(_cand))
        break
from pin_census import sites_of, unscored_text
from pin_sites import erase_many
from xform import t69_prologue as P
from xform.t36_paramwidth import functions, build
import xform.t132_paramequiv as Q
import xform.t134_givrecover as G

VERIFY = int(os.environ.get("T135_VERIFY", "40"))
WIDE = ("s32", "u32", "int")
TYPES = "s8|u8|s16|u16|s32|u32|int"
IDENT = r"[A-Za-z_]\w*"


def _evidence(body, names):
    """{name: set of narrow types} from casts and masks of any alias name."""
    ev = {}
    for x in names:
        X = re.escape(x)
        for m in re.finditer(r"\((s16|u16|s8|u8)\)\s*\(?\s*%s\b" % X, body):
            ev.setdefault(x, set()).add(m.group(1))
        if re.search(r"(?<![\w.])%s\s*&\s*0[xX][Ff]{4}\b" % X, body):
            ev.setdefault(x, set()).add("u16")
        if re.search(r"(?<![\w.])%s\s*&\s*0[xX][Ff]{2}\b(?![Ff])" % X, body):
            ev.setdefault(x, set()).add("u8")
    return ev


def copies_of(masked, body, b0, params):
    """{local: (root param, decl_span or None, assign_span or None)} - locals written once from a parameter / copy."""
    alias = {p: p for p, _, _, _ in params}
    info = {}
    decl_re = r"(?m)^[ \t]*(?:register[ \t]+)?(?:%s)[ \t]+(%s)[ \t]*(?:ASM_REG\([^)]*\))?[ \t]*(?:=[ \t]*([^;]+))?;[^\n]*\n?" % (TYPES, IDENT)
    decls = {m.group(1): m for m in re.finditer(decl_re, body)}
    changed = True
    while changed:
        changed = False
        for R, dm in decls.items():
            if R in alias:
                continue
            writes = G._writes_of(masked, R, b0, b0 + len(body))
            if re.search(r"&\s*%s\b" % re.escape(R), body):
                continue
            src, span_d, span_a = None, None, None
            if dm.group(2):
                writes = [w for w in writes if not (b0 + dm.start() <= w[0] < b0 + dm.end())]
                if writes:
                    continue
                src, span_d = dm.group(2).strip(), (dm.start(), dm.end())
            else:
                if len(writes) != 1:
                    continue
                w = writes[0]
                am = re.match(r"(?m)^[ \t]*%s[ \t]*=(?!=)[ \t]*([^;]+);[^\n]*\n?" % re.escape(R),
                              masked[masked.rfind("\n", 0, w[0]) + 1:])
                if not am or masked.rfind("\n", 0, w[0]) + 1 + am.start() != masked.rfind("\n", 0, w[0]) + 1:
                    continue
                ls = masked.rfind("\n", 0, w[0]) + 1
                src, span_d, span_a = am.group(1).strip(), (dm.start(), dm.end()), (ls - b0, ls - b0 + am.end())
            sm = re.fullmatch(r"(?:\((%s)\)\s*)?(%s)" % (TYPES, IDENT), src)
            if not sm or sm.group(2) not in alias:
                continue
            alias[R] = alias[sm.group(2)]
            info[R] = (alias[R], span_d, span_a)
            changed = True
    return info


def analyses(text):
    """[(fname, params, {param: types}, copies)] for functions with a wide parameter of narrow evidence."""
    masked = P._mask(text)
    out = []
    for fname, params, b0, b1 in functions(text):
        body = masked[b0:b1]
        wide = [p for p, ty, _, _ in params if ty in WIDE]
        if not wide:
            continue
        cp = copies_of(masked, body, b0, params)
        alias = {p: p for p in wide}
        for R, (root, _, _) in cp.items():
            if root in alias:
                alias[R] = root
        ev = _evidence(body, list(alias))
        per = {}
        for x, tys in ev.items():
            per.setdefault(alias[x], set()).update(tys)
        # t84's evidence: a PINNED copy of a wide parameter, whatever its uses (stack parameters held in s-registers)
        pinned = [text[x[3]:x[4]] for x in sites_of(text) if x[0] != "expand" and b0 < x[3] < b1]
        for R, (root, _, _) in cp.items():
            if root in wide and any(re.search(r"\b%s\b" % re.escape(R), z) for z in pinned):
                per.setdefault(root, set()).update(("s16", "u16"))
        per = {p: t for p, t in per.items() if p in wide}
        if not per:
            continue
        out.append((fname, params, per, {R: v for R, v in cp.items() if v[0] in wide}))
    return out


def _pick(tys, primary=True):
    for t in (("s16", "u16", "s8", "u8") if primary else ("u16", "s16", "u8", "s8")):
        if t in tys:
            return t
    return "s16"


def _drop(text, fname, drop):
    """Remove the copies in `drop` {local: root}: pins on them erased, statements deleted, uses renamed."""
    F = next((f for f in functions(text) if f[0] == fname), None)
    if F is None:
        return None
    pins = [s for s in sites_of(text) if s[0] != "expand" and F[2] < s[3] < F[3]
            and any(re.search(r"\b%s\b" % re.escape(R), text[s[3]:s[4]]) for R in drop)]
    t = erase_many(text, pins, clean_notes=True) if pins else text
    F = next((f for f in functions(t) if f[0] == fname), None)
    masked = P._mask(t)
    body = masked[F[2]:F[3]]
    cp = copies_of(masked, body, F[2], F[1])
    kill = []
    for R in drop:
        if R not in cp:
            return None
        _, sd, sa = cp[R]
        kill.append((F[2] + sd[0], F[2] + sd[1]))
        if sa:
            kill.append((F[2] + sa[0], F[2] + sa[1]))
    kill.sort()
    for (a, b), (c, d) in zip(kill, kill[1:]):
        if c < b:
            return None
    edits = [(a, b, "") for a, b in kill]
    for R, root in drop.items():
        for m in re.finditer(r"(?<![\w.>])%s\b" % re.escape(R), body):
            a = F[2] + m.start()
            if any(x <= a < y for x, y in kill):
                continue
            edits.append((a, a + len(R), root))
    for a, b, r in sorted(edits, key=lambda e: -e[0]):
        t = t[:a] + r + t[b:]
    return t


def _strip_casts(text, fname, narrow):
    F = next((f for f in functions(text) if f[0] == fname), None)
    t = text
    body = t[F[2]:F[3]]
    for p, ty in narrow.items():
        body = re.sub(r"\(%s\)\s*(?=%s\b)" % (ty, re.escape(p)), "", body)
        body = re.sub(r"\(%s\)\s*\(\s*%s\s*\)" % (ty, re.escape(p)), p, body)
    return t[:F[2]] + body + t[F[3]:]


def _split_args(masked, open_pos):
    """(close_pos, [(start, end)]) of the top-level arguments of the call whose `(` is at open_pos."""
    depth, i, start, out = 0, open_pos, open_pos + 1, []
    while i < len(masked):
        c = masked[i]
        if c in "([{":
            depth += 1
        elif c in ")]}":
            depth -= 1
            if depth == 0:
                out.append((start, i))
                return i, out
        elif c == "," and depth == 1:
            out.append((start, i)); start = i + 1
        i += 1
    return None, []


MASK = re.compile(r"^(\s*)(.*?)\s*&\s*0[xX][Ff]{4}\s*$", re.S)


def callee_u16(text, fname):
    """Every file-local `s32` prototype parameter that ALL calls fill with a `& 0xFFFF` mask: the prototype says
    u16 and the mask goes (the fc4 spelling of dungeon/func_8009A734's callee).  None when nothing qualifies."""
    masked = P._mask(text)
    F = next((f for f in functions(text) if f[0] == fname), None)
    if F is None:
        return None
    edits, seen = [], set()
    for pm in re.finditer(r"(?m)^(?:extern[ \t]+)?[\w \t\*]*?\b(%s)[ \t]*\(([^;{}()]*)\)[ \t]*;" % IDENT, masked):
        callee = pm.group(1)
        if callee == fname or callee in seen or callee in ("if", "while", "for", "switch", "return"):
            continue
        seen.add(callee)
        parts = pm.group(2).split(",")
        calls = []
        for cm in re.finditer(r"(?<![\w.>])%s[ \t]*\(" % re.escape(callee), masked):
            if cm.start() in range(pm.start(), pm.end()) or masked[max(0, cm.start() - 3):cm.start()].strip().endswith(("s32", "u16", "void")):
                continue
            close, args = _split_args(masked, cm.end() - 1)
            if close is None or len(args) != len(parts):
                calls = None
                break
            calls.append(args)
        if not calls:
            continue
        pos = pm.start(2)
        starts = []
        for part in parts:
            starts.append((pos, pos + len(part))); pos += len(part) + 1
        for i, part in enumerate(parts):
            if not re.fullmatch(r"\s*(?:s32|int|u32)\s*(?:%s)?\s*" % IDENT, part):
                continue
            if all(MASK.match(masked[c[i][0]:c[i][1]]) for c in calls):
                tm = re.search(r"\b(?:s32|int|u32)\b", part)
                edits.append((starts[i][0] + tm.start(), starts[i][0] + tm.end(), "u16"))
                for c in calls:
                    a, b = c[i]
                    mm = MASK.match(masked[a:b])
                    edits.append((a + mm.start(2), b, mm.group(2)))
    if not edits:
        return None
    t = text
    for a, b, r in sorted(edits, key=lambda e: -e[0]):
        t = t[:a] + r + t[b:]
    return t


def _retype(text, fname, widen):
    t = build(text, fname, widen, None)
    if t is None:
        return None
    return Q.sync_attr_protos(t, fname)


def bases(text):
    out, seen = [], set()
    for fname, params, per, cp in analyses(text):
        evp = [p for p, ty, _, _ in params if p in per]
        wide = [p for p, ty, _, _ in params if ty in WIDE]
        first = min([i for i, (p, _, _, _) in enumerate(params) if p in per] or [0])
        groups = [("ev", evp)] + [("only-" + p, [p]) for p in evp if len(evp) > 1]
        if first > 0 and params[first - 1][0] in wide:
            groups.append(("prev+ev", [params[first - 1][0]] + evp))
        groups.append(("wide", wide))
        for gl, grp in groups:
            grp = [p for p in grp if p in wide]
            if not grp:
                continue
            assign = {}
            for kind in ("own", "s16", "u16"):
                m = {}
                for p in grp:
                    m[p] = _pick(per[p]) if p in per and kind == "own" else \
                        (kind if kind != "own" else "s16")
                    if kind != "own" and p in per and per[p] & {"s8", "u8"}:
                        m[p] = _pick(per[p])
                key = tuple(sorted(m.items()))
                if key in assign:
                    continue
                assign[key] = (kind, m)
            for key, (kind, m) in assign.items():
                t1 = _retype(text, fname, m)
                if t1 is None:
                    continue
                drop = {R: v[0] for R, v in cp.items() if v[0] in m}
                variants = []
                if drop:
                    t2 = _drop(t1, fname, drop)
                    if t2 is not None:
                        variants.append(("drop", t2))
                    # copies kept, pins on them erased
                    F = next(f for f in functions(t1) if f[0] == fname)
                    pins = [s for s in sites_of(t1) if s[0] != "expand" and F[2] < s[3] < F[3]
                            and any(re.search(r"\b%s\b" % re.escape(R), t1[s[3]:s[4]]) for R in drop)]
                    if pins:
                        variants.append(("keepcopies", erase_many(t1, pins, clean_notes=True)))
                else:
                    variants.append(("retype", t1))
                for vl, v in list(variants):
                    if vl == "drop":
                        variants.append(("drop+nocast", _strip_casts(v, fname, m)))
                        cu = callee_u16(v, fname)
                        if cu:
                            variants.append(("drop+u16proto", cu))
                            variants.append(("drop+u16proto+nocast", _strip_casts(cu, fname, m)))
                for vl, v in variants:
                    if v in seen or unscored_text(v) != unscored_text(text):
                        continue
                    seen.add(v)
                    out.append(("narrow:%s:%s:%s:%s" % (fname, gl, kind, vl), v, fname))
    return out


def stack(text, pins_in):
    cands, seen = [], {text}
    for label, base, fname in bases(text):
        F = Q._fn_of(base, fname)
        for tag, t in Q._menu(base, pins_in, fname, F[2] if F else 0):
            if t in seen or len(sites_of(t)) >= pins_in:
                continue
            seen.add(t)
            cands.append((label + tag, t, fname))
    return cands


class T:
    name = "t135_narrowparam"
    level = 1
    needs_verify = True

    @staticmethod
    def eligible(text, row, census):
        if not sites_of(text):
            return "no pin sites"
        why = P.asm_blocker(text)
        if why:
            return why
        try:
            return None if analyses(text) else "no wide parameter with narrow-use evidence"
        except Exception as e:
            return "parse: %r" % (e,)

    @staticmethod
    def apply_verified(text, row, census, vf):
        n0 = len(sites_of(text))
        cands = stack(text, n0)
        info = {"pins_in": n0, "candidates": len(cands)}
        if not cands:
            info["refused"] = ["no candidate with strictly fewer pins"]
            return None, info
        t, label, cfg, tried = G.first_exact(row, [(a, b) for a, b, _ in cands], vf, VERIFY)
        if t is None:
            info.update(tried=tried, refused=["no exact candidate (%d verifies of %d candidates)" % (tried, len(cands))])
            return None, info
        info.update(label=label, tried=tried, pins_out=len(sites_of(t)), signature_change=label.split(":")[1])
        if cfg:
            info["cfg"] = cfg
        return t, info
