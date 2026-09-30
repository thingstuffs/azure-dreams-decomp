"""T134: giv recovery - a user variable that shadows a loop.c induction variable is replaced by `i * STEP`.

MECHANISM   r81_opus_fc4 (2026-09-30, dungeon/func_81959E04, 3 -> 0).  m2c renders a reduced giv of the loop counter
            as a user variable: `angle = i;` before the loop, `angle += 0x80;` next to `i += 1;` in the latch.
            Retail's source wrote `i * 0x80` at each use; loop.c strength reduction then CREATES the reduced register
            itself (initialised by a copy of i, bumped by 0x80 in the latch).  That loop-created pseudo ranks above
            `part` in global.c, while the user variable (REG_N_SETS == 2, live from the prologue) ranks below it -
            so the colour pins ($22/$23/$4) were holding the allocation of a variable that never existed.

APPEARS     a local V, an integer counter I with `I += 1` (also `I++`, `++I`, `I = I + 1`, or the `for` header step),
            and exactly two writes of V: an initialiser before the loop (`V = I;`, `V = 0;`, `V = <int>;`,
            `V = I * K;`, also as a declaration initialiser) and ONE constant step `V += K;` (`V = V + K;`).
            The value of V at a use is then `I * K + d` with d a constant folded from the initialisers (the counter's
            own literal initialiser `I = c;` is read from the text; anything unproven is refused).
            All reads of V lie before both steps (a do/while latch or a `for` header step), V is not
            address-taken, the loop has no `continue`.
RESOLVES    every read of V spelled `I * K` (`(I * K + d)` when d != 0), V's declaration (pin included), its
            initialiser and its step gone.  Variants: the giv rewrite alone; plus t132's DIRECT parameter-copy drop
            (the fix on 81959E04 also used the s16 parameters directly); plus t127's `goto L; L:` clean-up; each with
            the remaining pins of the function erased through t132's menu (none, singly, nearest pairs, groups, all).
            The cell menu is part of the candidate: the fc lane's fix was a cell move (`-fno-schedule-insns` was the
            pin-era crutch), so a candidate is verified at the row's own cfg, at that cell with the `-fno-*` crutch
            flags dropped, and at `2.7.2-cdk-G0`; a hit at another cell reports info["cfg"] (the sweep driver
            switches the row's cell, the cell-move lanes review it).
Only `vf` accepts; the first exact candidate with strictly fewer pins wins.
Env: T134_VERIFY (verify budget per cfg, default 40), T134_CFGS (extra comma list of stock cells).
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
from xform.t36_paramwidth import functions
import xform.t132_paramequiv as Q

VERIFY = int(os.environ.get("T134_VERIFY", "40"))
INT_TYPES = ("s32", "u32", "int", "unsigned int", "s16", "u16")
NUM = r"(?:0[xX][0-9A-Fa-f]+|\d+)"
IDENT = r"[A-Za-z_]\w*"


def _num(s):
    return int(s, 16) if s.lower().startswith("0x") else int(s)


def _lineno_free(masked, a, b):
    return masked[a:b]


def _statement_span(masked, pos):
    """[start, end) of the whole source lines that hold offset `pos` (a statement per line)."""
    s = masked.rfind("\n", 0, pos) + 1
    e = masked.find("\n", pos)
    return s, (len(masked) if e < 0 else e + 1)


def _counter_steps(masked, I, b0, b1):
    """[(pos_start, pos_end, in_for_header)] of the counter's +1 steps."""
    out = []
    pats = [r"(?<![\w.])%s\+\+" % I, r"\+\+%s\b" % I, r"(?<![\w.])%s\s*\+=\s*1\b" % I,
            r"(?<![\w.])%s\s*=\s*%s\s*\+\s*1\b" % (I, I)]
    hdrs = [(m.start(), m.end()) for m in re.finditer(r"\bfor\s*\(([^;{}]*;[^;{}]*;[^{}]*?)\)\s*[{\n]", masked[b0:b1])]
    for pat in pats:
        for m in re.finditer(pat, masked[b0:b1]):
            a = b0 + m.start()
            hdr = any(x <= m.start() < y for x, y in hdrs)
            out.append((a, b0 + m.end(), hdr))
    return sorted(out)


def _writes_of(masked, V, b0, b1):
    return [(b0 + m.start(), b0 + m.end(), m) for m in re.finditer(
        r"(?<![\w.])%s\s*(?:[-+*/&|^]|<<|>>)?=(?!=)" % re.escape(V), masked[b0:b1])] + \
           [(b0 + m.start(), b0 + m.end(), m) for m in re.finditer(
               r"(?:\+\+|--)%s\b|(?<![\w.])%s(?:\+\+|--)" % (re.escape(V), re.escape(V)), masked[b0:b1])]


def givs(text):
    """[(fname, V, I, K, d)] for every function; every entry is a rewrite candidate."""
    masked = P._mask(text)
    out = []
    for fn in functions(text):
        name, params, b0, b1 = fn
        body = masked[b0:b1]
        if re.search(r"\bcontinue\b", body):
            continue
        locals_ = []
        for m in re.finditer(r"(?m)^[ \t]*(?:register[ \t]+)?(?:%s)[ \t]+(%s)[ \t]*(?:ASM_REG\([^)]*\))?[ \t]*(?:=[ \t]*([^;]+))?;"
                             % ("|".join(INT_TYPES), IDENT), body):
            locals_.append((m.group(1), m.group(2), b0 + m.start()))
        names = {v for v, _, _ in locals_}
        for V, dinit, dpos in locals_:
            steps = list(re.finditer(r"(?<![\w.])%s\s*(?:\+=\s*(%s)|=\s*%s\s*\+\s*(%s))\s*;" % (re.escape(V), NUM, re.escape(V), NUM), body))
            if len(steps) != 1:
                continue
            K = steps[0].group(1) or steps[0].group(2)
            if _num(K) == 0:
                continue
            sstart, send = b0 + steps[0].start(), b0 + steps[0].end()
            ws = _writes_of(masked, V, b0, b1)
            dend = dpos + len(body[dpos - b0:].split(";", 1)[0]) + 1
            inits = [w for w in ws if not (w[0] == sstart) and not (dinit and dpos <= w[0] < dend)]
            init_expr, init_pos = None, None
            if dinit:
                if len(inits) != 0:
                    continue
                init_expr, init_pos = dinit.strip(), dpos
            else:
                if len(inits) != 1:
                    continue
                m2 = re.match(r"(?<![\w.])%s\s*=\s*([^;]+);" % re.escape(V), masked[inits[0][0]:b1])
                if not m2:
                    continue
                init_expr, init_pos = m2.group(1).strip(), inits[0][0]
            if init_pos > sstart:
                continue
            if re.search(r"&\s*%s\b" % re.escape(V), body):
                continue
            # the counter and its literal start
            for I in sorted(names - {V}) + [p for p, _, _, _ in params]:
                steps_i = _counter_steps(masked, I, b0, b1)
                if not steps_i or len(_writes_of(masked, I, b0, b1)) > 3:
                    continue
                c_i = _init_literal(masked, I, b0, b1, init_pos, steps_i)
                if c_i is None:
                    continue
                cv = _init_value(init_expr, I, c_i)
                if cv is None:
                    continue
                d = cv - c_i * _num(K)
                # the reads of V lie before the latch steps
                reads = [m3.start() + b0 for m3 in re.finditer(r"(?<![\w.])%s\b" % re.escape(V), body)]
                reads = [r for r in reads if not (sstart <= r < send) and r != init_pos and not
                         (dpos <= r < dpos + 1 + len(dinit or "") + 60 and r <= init_pos + 200 and dinit and r < init_pos + len(dinit) + 60 and False)]
                reads = [r for r in reads if not _in_decl_or_init(masked, r, V, dpos if dinit else None, init_pos)]
                if not reads:
                    continue
                latch = min([sstart] + [s[0] for s in steps_i if not s[2]])
                ok = all(r < latch for r in reads)
                if not ok:
                    continue
                if any(s[0] < init_pos and not s[2] for s in steps_i):
                    continue
                out.append((name, V, I, K, d))
                break
    return out


def _in_decl_or_init(masked, r, V, dpos, init_pos):
    ls, le = _statement_span(masked, r)
    line = masked[ls:le]
    if re.match(r"[ \t]*(?:register[ \t]+)?(?:%s)[ \t]+%s\b" % ("|".join(INT_TYPES), re.escape(V)), line):
        return True
    if re.match(r"[ \t]*%s\s*=(?!=)" % re.escape(V), line) and ls <= init_pos < le:
        return True
    return False


def _init_literal(masked, I, b0, b1, before, steps_i):
    """The literal the counter holds when V is initialised: the last `I = <int>;` (or for-header init) before it."""
    best = None
    for m in re.finditer(r"(?<![\w.])%s\s*=(?!=)\s*(%s)\s*[;)]" % (re.escape(I), NUM), masked[b0:b1]):
        if b0 + m.start() <= before + 200:
            best = (b0 + m.start(), _num(m.group(1)))
    hdr = None
    for m in re.finditer(r"\bfor\s*\(\s*%s\s*=\s*(%s)\s*;" % (re.escape(I), NUM), masked[b0:b1]):
        hdr = (b0 + m.start(), _num(m.group(1)))
    if best is None and hdr is None:
        return None
    cand = max([c for c in (best, hdr) if c], key=lambda c: c[0])
    # nothing else writes I between that literal and the step
    for w in _writes_of(masked, I, b0, b1):
        if w[0] != cand[0] and cand[0] < w[0] and not any(w[0] <= s[0] < w[1] + 4 for s in steps_i):
            return None
    return cand[1]


def _init_value(expr, I, c_i):
    e = re.sub(r"\s+", " ", expr.strip())
    while e.startswith("(") and e.endswith(")") and e.count("(") == 1:
        e = e[1:-1].strip()
    if re.fullmatch(NUM, e):
        return _num(e)
    if e == I:
        return c_i
    m = re.fullmatch(r"%s \* (%s)|(%s) \* %s" % (re.escape(I), NUM, NUM, re.escape(I)), e)
    if m:
        return c_i * _num(m.group(1) or m.group(2))
    return None


def _put(text, fname, V, I, K, d):
    """Rewrite one giv: reads -> `I * K`, drop decl/init/step; None when the edit is not clean."""
    masked = P._mask(text)
    fn = next((f for f in functions(text) if f[0] == fname), None)
    if fn is None:
        return None
    b0, b1 = fn[2], fn[3]
    body = masked[b0:b1]
    rep = "%s * %s" % (I, K) if d == 0 else "%s * %s %s %d" % (I, K, "+" if d > 0 else "-", abs(d))
    kill, edits = [], []
    # step / init statements (whole lines when they are alone on the line)
    for m in re.finditer(r"(?<![\w.])%s\s*(?:\+=\s*%s|=\s*%s\s*\+\s*%s)\s*;" % (re.escape(V), NUM, re.escape(V), NUM), body):
        kill.append((b0 + m.start(), b0 + m.end()))
    decl = re.search(r"(?m)^[ \t]*(?:register[ \t]+)?(?:%s)[ \t]+%s[ \t]*(?:ASM_REG\([^)]*\))?[ \t]*(?:=[ \t]*[^;]+)?;" % ("|".join(INT_TYPES), re.escape(V)), body)
    if not decl:
        return None
    kill.append((b0 + decl.start(), b0 + decl.end()))
    has_init_in_decl = "=" in body[decl.start():decl.end()].split("ASM_REG")[-1]
    if not has_init_in_decl:
        m = re.search(r"(?m)^[ \t]*%s[ \t]*=(?!=)[^;]*;" % re.escape(V), body)
        if not m:
            return None
        kill.append((b0 + m.start(), b0 + m.end()))
    for m in re.finditer(r"(?<![\w.])%s\b" % re.escape(V), body):
        a = b0 + m.start()
        if any(x <= a < y for x, y in kill):
            continue
        # a struct member `->V` / `.V` is a different name
        pre = masked[max(0, a - 2):a]
        if pre.endswith((".", ">")) and pre.endswith(("->", ".")):
            continue
        b = b0 + m.end()
        before = masked[:a].rstrip()[-1:]
        after = masked[b:].lstrip()[:1]
        plain = before in "(,=" and after in "),;"
        edits.append((a, b, rep if plain else "(" + rep + ")"))
    if not edits:
        return None
    ed = [(x, y, "") for x, y in kill] + edits
    t = text
    for x, y, r in sorted(ed, key=lambda e: -e[0]):
        if r == "":                      # drop the whole line when nothing else stands on it
            ls = t.rfind("\n", 0, x) + 1
            le = t.find("\n", y)
            le = len(t) if le < 0 else le
            rest = (t[ls:x] + t[y:le]).strip()
            if not rest or re.fullmatch(r"/\*.*\*/", rest):
                x, y = ls, min(len(t), le + 1)
        t = t[:x] + r + t[y:]
    return t


def _names(text, span, V):
    return re.search(r"\b%s\b" % re.escape(V), text[span[0]:span[1]]) is not None


def giv_bases(text):
    """[(label, text')] - each giv rewritten, the pins that name V erased first."""
    out, seen = [], set()
    for fname, V, I, K, d in givs(text):
        F = next((f for f in functions(text) if f[0] == fname), None)
        pins = [s for s in sites_of(text) if s[0] != "expand" and F[2] < s[3] < F[3] and _names(text, (s[3], s[4]), V)]
        t0 = erase_many(text, pins, clean_notes=True) if pins else text
        t = _put(t0, fname, V, I, K, d)
        if t is None or t in seen:
            continue
        seen.add(t)
        out.append(("giv:%s:%s=%s*%s%+d" % (fname, V, I, K, d), t, fname))
    return out


def _gotoclean(t):
    try:
        from xform import t127_gotonext as G
    except ImportError:
        return None
    n = len(G.sites(t))
    return G.rewrite(t, list(range(n))) if n else None


def stack(text, pins_in):
    """[(label, text)] for the whole menu."""
    cands, seen = [], {text}
    for label, base, fname in giv_bases(text):
        variants = [(label, base)]
        g = _gotoclean(base)
        if g and g != base:
            variants.append((label + "+goto", g))
        more = []
        for lab, b in variants:
            try:
                for l2, b2, _ in Q.direct_bases(b):
                    more.append((lab + ">" + l2, b2))
            except Exception:
                pass
        for lab, b in variants + more:
            F = Q._fn_of(b, fname)
            for tag, t in Q._menu(b, pins_in, fname, F[2] if F else 0):
                if t in seen or len(sites_of(t)) >= pins_in:
                    continue
                seen.add(t)
                cands.append((lab + tag, t))
    return cands


def cfg_menu(row):
    """[cfg, ...] - own cfg, own cell without the -fno-* crutch flags, then 2.7.2-cdk-G0, stock cells only."""
    try:
        from common import parse_cfg, is_stock_cfg
    except ImportError:
        return [None]
    own = row.get("cfg")
    out = [None]
    if own:
        head, flags = parse_cfg(own)
        keep = [f for f in flags if not f.startswith("-fno-")]
        out.append(" ".join([head + ("-G0" if "-G0" in keep else "")] + [f for f in keep if f != "-G0"]))
    out.append("2.7.2-cdk-G0")
    out += [c.strip() for c in os.environ.get("T134_CFGS", "").split(",") if c.strip()]
    res = []
    for c in out:
        if c is not None and (c == own or not is_stock_cfg(c) or c in res):
            continue
        if c not in res:
            res.append(c)
    return res


def first_exact(row, cands, vf, budget):
    """Fewest pins first: for each pin count (ascending) every candidate is verified at every cell of the menu
    (own cfg first); the first exact one wins.  `budget` caps the verifies per cell over all levels."""
    levels = {}
    for k, (_l, t) in enumerate(cands):
        levels.setdefault(len(sites_of(t)), []).append(k)
    cfgs = cfg_menu(row)
    used = {c: 0 for c in cfgs}
    tried = 0
    for n in sorted(levels):
        for cfg in cfgs:
            for k in levels[n]:
                if used[cfg] >= budget:
                    break
                used[cfg] += 1
                tried += 1
                label, t = cands[k]
                r = vf(t, cfg) if cfg else vf(t)
                if r.get("exact"):
                    return t, label, cfg, tried
    return None, None, None, tried


class T:
    name = "t134_givrecover"
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
            return None if givs(text) else "no user variable stepped by a constant beside the loop counter"
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
        t, label, cfg, tried = first_exact(row, cands, vf, VERIFY)
        if t is None:
            info.update(tried=tried, refused=["no exact candidate (%d verifies of %d candidates)" % (tried, len(cands))])
            return None, info
        info.update(label=label, tried=tried, pins_out=len(sites_of(t)))
        if cfg:
            info["cfg"] = cfg
        return t, info
