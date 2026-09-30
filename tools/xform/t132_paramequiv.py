"""T132: the REG_EQUIV parameter rule - a never-written parameter ranks half as high in global.c, so parameter
copies and pinned parameters trade places, each with the pins that stood behind the old shape erased.

MECHANISM   r81_opus_lc2 (2026-09-30, rule 1; dungeon/func_81934928, dungeon/func_818E6800).  An unmodified
            parameter is set once from its incoming slot and carries REG_EQUIV (mem (reg 0)); local-alloc.c:1064
            DOUBLES the REG_LIVE_LENGTH of every REG_EQUIV pseudo, so its allocno_compare priority
            (refs / live * floor_log2(refs)) halves.  A local copy (`u8 *effect = (u8 *)effect_arg;`) or a
            reassigned parameter has no REG_EQUIV and ranks about twice as high.  The same holds for a set-once
            constant address (`tbl = &D_80082E80`, REG_EQUIV to the symbol).  So the choice "parameter used
            directly" against "copy in a local" moves a pseudo across its neighbours in the colouring order, and
            an ASM_REG / ASM_KEEP on a nearby callee-saved pointer is often only the scaffolding for that order.

DIRECT      `T *x = (T *)param;` (or `x = param;`) with x never reassigned and param never written -> the
            parameter carries x's name and type, the copy goes (t69's `entry_copies` + `merge`), and ANY nearby pin
            may go with it: the pins on the copy itself, then each other pin of the function one at a time
            (ASM_REG first, then the keeps, nearest the top of the function - where the copies stand - first), the pairs of the nearest few, all
            ASM_REG pins, all keeps, every pin.  Solved 818E6800's `actor` pin (copies dropped, ASM_REG($20) erased).
COPY        a never-written parameter that a keep pins directly (`ASM_KEEP(param)`; T132_ALL=1: every unwritten
            parameter) -> `T local = param;` in a local, every use renamed to the local (the parameter keeps the
            name `<name>_arg`, the local takes the old name), the keeps on it erased, then the same pin menu.  The
            copy is offered at the top of the declarations and after the last one (pseudo numbers differ).
            A parameter that the code already REASSIGNS is not touched: it has no REG_EQUIV to give up, and a
            fabricated `param = param` is not offered.

WHAT T132 ADDS TO t69_prologue  (both are refusals of t69 that this generator opens; t69's code is reused, not copied)
            1. cast copies `T *x = (T *)param;` are enumerated (t69 needs T69_CAST_COPY=1, default off) - the
               m2c shape of `void *effect_arg` -> `u8 *effect`;
            2. the copy needs NOT carry a pin: t69 refuses `no-pin-removed` for a copy whose scaffolding sits on a
               DIFFERENT local (818E6800: three plain copies, the pin on `actor`);
            3. the remaining pins are erased JOINTLY with the drop in every candidate (t69 does that only for the
               top-3 screened candidates and only when at most 6 pins remain);
            4. direction COPY (a parameter is turned into a copy) does not exist in t69.
Only `vf` accepts; the first exact candidate with strictly fewer pins wins (screen order).
Env: T132_KINDS (`direct,copy`, default both), T132_VERIFY (verify budget, default 10), T132_MAX (candidates screened, 200), T132_ALL, T132_CFGS
(comma list of extra STOCK cells to try after the row's own cell; a hit reports info["cfg"] - the cell-move
lanes decide whether to land it, the sweep driver would switch the row's cell).
"""
import itertools
import os
import re
import sys
import threading
from pathlib import Path

_HERE = Path(__file__).resolve()
for _cand in (_HERE.parents[1], _HERE.parents[2] / "tools"):
    if (_cand / "pin_census.py").exists():
        sys.path.insert(0, str(_cand))
        break
from pin_census import sites_of, unscored_text
from pin_sites import erase_many
from xform import t69_prologue as P
from xform.t36_paramwidth import functions
import xform.t131_ptrbeforecall as H
try:
    from . import screen
except ImportError:
    from xform import screen

VERIFY = int(os.environ.get("T132_VERIFY", "10"))
MAX_CANDS = int(os.environ.get("T132_MAX", "200"))
NEAR = 6                       # pins used for pair menus
_LOCK = threading.Lock()       # T69_CAST_COPY is read from os.environ at call time
ID = P.ID


# ------------------------------------------------------------------ t69 with the cast-copy opening
def _with_cast_open(fn, *a, **k):
    with _LOCK:
        old = os.environ.get("T69_CAST_COPY")
        os.environ["T69_CAST_COPY"] = "1"
        try:
            return fn(*a, **k)
        finally:
            if old is None:
                del os.environ["T69_CAST_COPY"]
            else:
                os.environ["T69_CAST_COPY"] = old


def _fn_of(text, name):
    return next((f for f in functions(text) if f[0] == name), None)


def _pin_free(text, fn, chosen):
    """`text` with a throw-away `ASM_KEEP(local);` after each chosen copy that lacks a pin, so that t69.merge
    (which refuses a merge that removes no pin) accepts it; merge erases the fake keep with the copy."""
    ins = []
    for p, pty, ps, v, lty, dspan, cspan in chosen:
        at = (cspan or dspan)[1]
        ins.append((at, "    ASM_KEEP(%s);\n" % v))
    t = text
    for at, s in sorted(ins, reverse=True):
        nl = t.find("\n", at - 1) + 1 if t[at - 1] != "\n" else at
        t = t[:nl] + s + t[nl:]
    return t


def sync_attr_protos(t, fname):
    """t69 retypes plain prototypes only; the `void f(args)\n__attribute__((section(..)));` forward declaration
    that the overlay files carry must follow the definition's parameter list (arity equal, outside #if arms)."""
    masked = P._mask(t)
    dep, ppd = P._depths(masked), P._pp_depth(masked)
    dm = re.search(r"\b%s\s*\(([^()]*)\)\s*\{" % re.escape(fname), masked)
    if not dm:
        return t
    sig = t[dm.start(1):dm.end(1)]
    edits = []
    for m in re.finditer(r"\b%s\s*\(([^;{}()]*)\)\s*__attribute__" % re.escape(fname), masked):
        if dep[m.start()] != 0 or ppd[m.start()] or m.start() == dm.start():
            continue
        if len(m.group(1).split(",")) == len(sig.split(",")) and m.group(1) != sig:
            edits.append((m.start(1), m.end(1)))
    for a, b in sorted(edits, reverse=True):
        t = t[:a] + sig + t[b:]
    return t


ROLE = "__role"
PP_LINE = re.compile(r"(?m)^[ \t]*#[ \t]*(?:if|ifdef|ifndef|else|elif|endif)\b[^\n]*$")


def shield(text):
    """(text', restore) - each conditional directive line INSIDE a function body becomes a plain statement
    `__PPn__;`, so t69's preprocessor-region refusal (a `#ifdef NON_MATCHING` arm inside the body, as on every
    pinned row with a split-address pin) does not hide the row.  `restore` puts the directives back.  Refused
    (None) when an arm mentions a name in `names`: an edit there is an unscored-arm edit no verify can see."""
    spans = [(f[2], f[3]) for f in functions(text)]
    marks = {}

    def sub(m):
        if not any(a < m.start() < b for a, b in spans):
            return m.group(0)
        k = "__PP%d__;" % len(marks)
        marks[k] = m.group(0)
        return k
    t = PP_LINE.sub(sub, text)

    def restore(x):
        for k, v in marks.items():
            x = x.replace(k, v)
        return x
    return t, restore, bool(marks)


def split_roles(text):
    """[(label, text')] - a parameter that is COPIED (`T v = p;`, v never written) and afterwards REASSIGNED as a
    second role (`p = ...;` the first mention after the copy, a plain statement of the function's own block, no
    goto above it) has its later role renamed to a fresh local `p__role`; the parameter is then written no more
    and the DIRECT machinery may fold the copy into it.  The caller renames `p__role` back to `p` on the merged
    text.  (r81_opus_lc2 dungeon/func_81934928: `void *self = effect; ... effect = self->unk_00;`.)"""
    out = []
    masked = P._mask(text)
    dep = P._depths(masked)
    for fn in functions(text):
        name, params, b0, b1 = fn
        body = masked[b0:b1]
        for p, pty, _a, _b in params:
            if not P._writes(body, p) or "register" in pty or "(" in pty:
                continue
            cm = re.search(r"(?m)^[ \t]+(?:register[ \t]+)?[\w \t\*]*?(?<![\w])(?P<v>%s)[ \t]*=[ \t]*(?:\([^()\n]*\)[ \t]*)?%s[ \t]*;[ \t]*$"
                           % (ID, re.escape(p)), masked[b0:b1])
            if not cm:
                continue
            v = cm.group("v")
            if v == p or P._writes(body, v) != 1:
                continue
            end = b0 + cm.end()
            if any(a < end for a, _ in P._occurrences(masked, p, b0 + 1, b1) if b0 + cm.start() > a):
                continue                                # the parameter is read before the copy
            occ = [(a, b) for a, b in P._occurrences(masked, p, end, b1)]
            if not occ:
                continue
            a0 = occ[0][0]
            m2 = re.match(r"%s[ \t]*=(?!=)" % re.escape(p), masked[a0:])
            ls = masked.rfind("\n", 0, a0) + 1
            if not m2 or masked[ls:a0].strip() or dep[a0] != dep[b0] + 1:
                continue
            if re.search(r"\bgoto\b", masked[b0:a0]):
                continue
            q = p + ROLE
            t = text
            for a, b in sorted(occ, reverse=True):
                t = t[:a] + q + t[b:]
            F = _fn_of(t, name)
            for where in ("top", "end"):
                tt = H._put_decl(t, F[2], _decl_line(pty, q, "0").replace(" = 0", ""), where)
                if unscored_text(tt) == unscored_text(text):
                    out.append(("split:%s:%s@%s" % (name, p, where), tt, p, q))
    return out


def _unsplit(t, q, p):
    return re.sub(r"(?<![\w.])%s\b" % re.escape(q), p, t)


def direct_bases(text):
    """The DIRECT bases of the text itself and of each role-split variant of it."""
    out, seen = [], set()
    for label, base, fname in _direct_bases(text):
        seen.add(base)
        out.append((label, base, fname))
    for lab, t2, p, q in split_roles(text):
        for label, base, fname in _direct_bases(t2):
            b = _unsplit(base, q, p)
            if b in seen or unscored_text(b) != unscored_text(text):
                continue
            seen.add(b)
            out.append((lab + ">" + label, b, fname))
    return out


def _direct_bases(text):
    """[(label, merged text)] - the copy sets dropped (whole set first, then subsets), pins on the copies gone."""
    text0 = text
    text, restore, _arms = shield(text0)
    out, seen = [], set()
    for fn in functions(text):
        ec = _with_cast_open(P.entry_copies, text, fn)
        if not ec:
            continue
        n = len(ec)
        subs = [tuple(range(n))] + [s for k in range(n - 1, 0, -1) for s in itertools.combinations(range(n), k)]
        for sel in subs[:24]:
            chosen = [ec[i] for i in sel]
            t2 = _pin_free(text, fn, chosen)
            fn2 = _fn_of(t2, fn[0])
            ec2 = _with_cast_open(P.entry_copies, t2, fn2)
            ch2 = [r for r in ec2 if any(r[0] == c[0] and r[3] == c[3] for c in chosen)]
            if len(ch2) != len(chosen):
                continue
            m = P.merge(t2, fn2, ch2)
            if m is None:
                continue
            m = restore(sync_attr_protos(m, fn[0]))
            if m in seen or unscored_text(m) != unscored_text(text0):
                continue
            seen.add(m)
            out.append(("direct:%s:%s" % (fn[0], "+".join(c[3] for c in chosen)), m, fn[0]))
    return out


# ------------------------------------------------------------------ direction COPY
def _decl_line(pty, name, init):
    ty = pty.strip()
    return "    %s%s = %s;\n" % (ty if ty.endswith("*") else ty + " ", name, init)


def _ident_free(text, name):
    return re.search(r"(?<![\w.])%s\b" % re.escape(name), text) is None


def copy_bases(text):
    """[(label, text)] - never-written parameters turned into a local copy, pins on them erased."""
    out, seen = [], set()
    take_all = os.environ.get("T132_ALL", "0") == "1"
    text0 = text
    text, restore, _arms = shield(text0)
    masked = P._mask(text)
    dnames, pasting, ppd = P._directive_names(masked), P._pasting_macros(masked), P._pp_depth(masked)
    for fn in functions(text):
        name, params, b0, b1 = fn
        if not params or ppd[b0] or ppd[b1] or max(ppd[min(a for _, _, a, _ in params):b1] or [0]):
            continue
        body = masked[b0:b1]
        pinned = {s[2] for s in sites_of(text) if s[0] == "stmt" and s[1] in P.ERASABLE and b0 < s[3] < b1}
        cand = []
        for p, pty, ps_a, ps_b in params:
            if p in dnames or "register" in pty or "(" in pty:
                continue
            if not (p in pinned or take_all):
                continue
            if P._writes(body, p) or P._address_taken(body, {p: P._bare(pty)}, None):
                continue
            if not any(True for _ in P._occurrences(masked, p, b0 + 1, b1)):
                continue
            if any(P._enclosing_callee(masked, a, b0) in pasting for a, _ in P._occurrences(masked, p, b0 + 1, b1)):
                continue
            cand.append((p, pty))
        if not cand:
            continue
        subs = [s for k in range(len(cand), 0, -1) for s in itertools.combinations(cand, k)][:15]
        for sel in subs:
            for where in ("top", "end"):
                t = _turn_into_copies(text, masked, fn, sel, where)
                t = restore(t) if t is not None else None
                if t is None or t in seen or unscored_text(t) != unscored_text(text0):
                    continue
                seen.add(t)
                out.append(("copy:%s:%s@%s" % (name, "+".join(p for p, _ in sel), where), t, name))
    return out


def _turn_into_copies(text, masked, fn, sel, where):
    name, params, b0, b1 = fn
    sig_lo = min(a for _, _, a, _ in params)
    edits, decls, ren = [], [], {}
    for p, pty in sel:
        arg = p + "_arg"
        if not _ident_free(text, arg):
            arg = p + "_in"
            if not _ident_free(text, arg):
                return None
        ren[p] = arg
        decls.append(_decl_line(pty, p, arg))
        for a, b in P._occurrences(masked, p, sig_lo, b0):
            edits.append((a, b, arg))                 # the definition's parameter name
    # the body keeps the old name: it now reads the LOCAL; only the signature's parameter name changes
    for (x, y, _), (x2, _y2, _) in zip(sorted(edits), sorted(edits)[1:]):
        if x2 < y:
            return None
    t = text
    for x, y, r in sorted(edits, reverse=True):
        t = t[:x] + r + t[y:]
    F = _fn_of(t, name)
    if F is None:
        return None
    for d in reversed(decls):
        t = H._put_decl(t, F[2], d, where)
    # the keeps on the (now local) names go
    F = _fn_of(t, name)
    locs = {p for p, _ in sel}
    pins = [s for s in sites_of(t) if s[0] == "stmt" and s[1] in P.ERASABLE and s[2] in locs and F[2] < s[3] < F[3]]
    if not pins:
        return None
    t = erase_many(t, pins, clean_notes=True)
    if unscored_text(t) != unscored_text(text):
        return None
    return t


# ------------------------------------------------------------------ the pin menu of one base
def _menu(base, n0, anchor_fn, near_pos):
    """[(tag, text)] - `base` with further pins erased: none, each singly, pairs of the nearest, groups, all."""
    F = _fn_of(base, anchor_fn)
    ss = [s for s in sites_of(base) if s[0] != "expand" and F and F[2] <= s[3] <= F[3]]
    ss.sort(key=lambda s: (0 if s[0] != "stmt" else 1, abs(s[3] - near_pos)))    # ASM_REG decls first
    out = []
    if len(sites_of(base)) < n0:
        out.append(("base", base))
    if not ss:
        return out
    for i, s in enumerate(ss[:12]):
        out.append(("-%s@%d" % (s[1], s[5]), erase_many(base, [s], clean_notes=True)))
    near = ss[:NEAR]
    for a, b in itertools.combinations(near, 2):
        out.append(("-%s@%d-%s@%d" % (a[1], a[5], b[1], b[5]), erase_many(base, [a, b], clean_notes=True)))
    regs = [s for s in ss if s[0] != "stmt"]
    keeps = [s for s in ss if s[0] == "stmt"]
    if len(regs) > 1:
        out.append(("-allreg", erase_many(base, regs, clean_notes=True)))
    if len(keeps) > 1:
        out.append(("-allkeeps", erase_many(base, keeps, clean_notes=True)))
    if len(ss) > 1:
        out.append(("-allpins", erase_many(base, ss, clean_notes=True)))
    return out


def candidates(text):
    n0 = len(sites_of(text))
    cands, seen = [], {text}
    kinds = os.environ.get("T132_KINDS", "direct,copy").split(",")
    bases = (direct_bases(text) if "direct" in kinds else []) + (copy_bases(text) if "copy" in kinds else [])
    for label, base, fname in bases:
        F = _fn_of(base, fname)
        near = F[2] if F else 0
        for tag, t in _menu(base, n0, fname, near):
            if t in seen or len(sites_of(t)) >= n0:
                continue
            seen.add(t)
            cands.append((label + tag, t))
    return cands, n0


# ------------------------------------------------------------------ plugin
class T:
    name = "t132_paramequiv"
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
            ok = bool(direct_bases(text)) or bool(copy_bases(text))
        except Exception as e:
            return "parse: %r" % (e,)
        return None if ok else "no parameter copy to drop and no pinned unwritten parameter to copy"

    @staticmethod
    def apply_verified(text, row, census, vf):
        cands, n0 = candidates(text)
        info = {"pins_in": n0, "candidates": len(cands)}
        if not cands:
            info["refused"] = ["no candidate with strictly fewer pins"]
            return None, info
        base = screen.compile_s(row, text)
        ranked = []
        for k, (label, t) in enumerate(cands[:MAX_CANDS]):
            lst = screen.compile_s(row, t)
            d = screen.sdiff(base, lst) if base is not None and lst is not None else None
            ranked.append((10 ** 6 if d is None else d, len(sites_of(t)), k, label, t))
        ranked.sort(key=lambda r: (r[0], r[1], r[2]))
        info["screen"] = [[r[0], r[3]] for r in ranked[:8]]
        cfgs = [None] + [c.strip() for c in os.environ.get("T132_CFGS", "").split(",") if c.strip()]
        tried = 0
        for cfg in cfgs:
            for d, _n, _k, label, t in ranked[:VERIFY]:
                if d >= 10 ** 6:
                    continue
                tried += 1
                r = vf(t, cfg) if cfg else vf(t)
                if r.get("exact"):
                    info.update(label=label, tried=tried, screen_distance=d, pins_out=len(sites_of(t)))
                    if cfg:
                        info["cfg"] = cfg
                    return t, info
        info.update(tried=tried, refused=["no exact candidate (%d verifies of %d candidates)" % (tried, len(cands))])
        return None, info
