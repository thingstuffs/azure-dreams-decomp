"""T19: m2c's spelling of gcc's signed remainder by a power of two, written back as the `%`.

APPEARS     a bias `if (t < 0)` (no else arm) whose arm is `b = x + K;`, `b += K;` or
            `b = (x + K) >> n;` with K = 2^n - 1, and, within a few statements, a remainder that
            subtracts the rounded quotient from the dividend: `x - ((b >> n) << n)`, or
            `x - (q << n)` / `x - q * 2^n` once the quotient q is shifted (`b >>= n`, `q = b >> n`,
            or the arm's own shift).  x is the tested value, or what b was copied from.
RESOLVES    expand_divmod (expmed.c) lowers `x % 2^n` as `t1 = copy_to_mode_reg (x); if (t1 < 0)
            t1 += 2^n-1; q = t1 >> n; r = x - (q << n)`: its copy is a fresh pseudo cse cannot
            collapse into x.  Where the hand spelling's arm READS A COPY (the lane's
            `q = rand(); x = q; if (x < 0) q = (x + 3) >> 2;`, or `r = s; if (r < 0) r += 7;`),
            cse folds that copy and a pin puts it back; written as `%`, gcc re-emits its own.  Two
            rows fell to this by hand in the reg-rename lane (dungeon/func_8184A800, func_8108809C).
            Where the arm reads the SOURCE, t17 predicts the text already reproduces retail.
POPULATION  2026-09-11, pinned rows: 42 remainder idioms in 28 rows (the matcher; 47 raw
            `x - (q << n)` shapes), the arm reading a copy in 18 of them / 13 rows.
RESULT      2 rows, 2 pins (dry run of all 28): dungeon/func_81934928 - the lane's own form
            (`q = rand(); x = q; q >>= n; if (x < 0) q = (x + m) >> n`), jointly with the pins -
            and town/func_808B2D90, a SOURCE-reading arm whose rewrite left an ASM_REG with
            nothing to hold.  In 16 more rows the `%` spelling is byte-identical and frees
            nothing, as t17's `/` was in 64.  So the arm-reads-the-copy test does NOT separate
            the winners here (1 of 13 copy rows, 1 of 15 source rows): it explains t16 against
            t17, it is not a sufficient condition.  The byte-neutral `%` rewrites are clean
            source for a readability pass (the journal's `rewrote` field names them).

Spellings, in order: `%` with the bias and the hand shift gone (the quotient, if still used,
becomes `q = x / 2^n`), then `%` at the remainder only, the hand quotient left in place.  The
search is t16's `idiom_search`.
"""
import re, sys
from pathlib import Path
sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
from pin_census import sites_of, asm_blocker
try:
    from .t12_stmtorder import mask
    from .t16_absidiom import idiom_search, last_copy_source
except ImportError:
    from t12_stmtorder import mask
    from t16_absidiom import idiom_search, last_copy_source

POW = {(1 << n) - 1: n for n in range(2, 16)}      # x % 2 is branch-free in gcc: not this idiom
NUM = r"(?:0x[0-9A-Fa-f]+|\d+)"
ID = r"[A-Za-z_]\w*"
IF_RE = re.compile(r"\bif\s*\(\s*(?:\(\s*s32\s*\)\s*)?(?P<t>%s)\s*<\s*0\s*\)\s*(?:\{(?P<inner>[^{}]*)\}|(?P<bare>[^{};]*;))" % ID)
ARM_RE = re.compile(r"^(?P<b>{id})\s*(?:\+=\s*(?P<k1>{n})|=\s*(?P<x2>{id})\s*\+\s*(?P<k2>{n})"
                    r"|=\s*\(\s*(?P<x3>{id})\s*\+\s*(?P<k3>{n})\s*\)\s*>>\s*(?P<n3>{n}))$".format(id=ID, n=NUM))
PIN_STMT_RE = re.compile(r"^ASM_[A-Z0-9_]+\([^;]*\)\s*;?$")
PIECE_RE = re.compile(r"[^;{}]*[;{}]")
MAX_GAP = 6
# a remainder may only be cut out of an expression where `x - (...)` is a whole operand
OK_BEFORE = re.compile(r"(?:^|[(=,?:<>|^{;]|\breturn)\s*$")


def _num(s):
    return int(s, 0)


def _stmt_before(masked, pos):
    """(start, end, text) of the statement right before pos, pins skipped, or None."""
    end = pos
    while True:
        lo = max(masked.rfind(";", 0, end - 1), masked.rfind("{", 0, end), masked.rfind("}", 0, end))
        if lo < 0:
            return None
        lo2 = max(masked.rfind(";", 0, lo), masked.rfind("{", 0, lo), masked.rfind("}", 0, lo))
        seg = masked[lo2 + 1:lo + 1]
        core = seg.strip()
        if PIN_STMT_RE.match(core):
            end = lo2 + 1
            continue
        return lo2 + 1 + (len(seg) - len(seg.lstrip())), lo + 1, core


def _uses(masked, pos, var, skip):
    """Is var read from pos on, outside the spans in skip, before a plain reassignment kills it?"""
    for p in PIECE_RE.finditer(masked, pos):
        if any(s <= p.start() < e for s, e in skip):
            continue
        core = p.group(0).strip()
        if not re.search(r"(?<![.>\w])\b%s\b" % re.escape(var), core):
            continue
        m = re.match(r"^%s\s*=(?!=)(.*);$" % re.escape(var), core)
        if m and not re.search(r"(?<![.>\w])\b%s\b" % re.escape(var), m.group(1)):
            return False
        return True
    return False


def _remainder(seg, d, q, n, shifted):
    """(start, end) inside seg of `d - (q << n)` (shifted) or `d - ((q >> n) << n)`, or None."""
    k = 1 << n
    if shifted:
        pat = r"(?<![.>\w])%s\s*-\s*\(\s*%s\s*(?:<<\s*(?P<a>%s)|\*\s*(?P<m>%s))\s*\)" % (re.escape(d), re.escape(q), NUM, NUM)
    else:
        pat = r"(?<![.>\w])%s\s*-\s*\(\s*\(\s*%s\s*>>\s*(?P<s>%s)\s*\)\s*<<\s*(?P<a>%s)\s*\)" % (re.escape(d), re.escape(q), NUM, NUM)
    for m in re.finditer(pat, seg):
        if m.groupdict().get("s") and _num(m.group("s")) != n:
            continue
        if m.group("a") and _num(m.group("a")) != n or m.groupdict().get("m") and _num(m.group("m")) != k:
            continue
        if not OK_BEFORE.search(seg[:m.start()]) or re.match(r"\s*[*/%]", seg[m.end():]):
            continue                       # `a + x - (...)` is `(a + x) - (...)`: not a whole operand
        return m.start(), m.end()
    return None


def idioms(text):
    """[{start, end, d, vars, arm, full: [edits], mod: [edits]}] - edits are (start, end, text)."""
    masked = mask(text)
    out = []
    for m in IF_RE.finditer(masked):
        if re.match(r"\s*else\b", masked[m.end():]):
            continue
        body = m.group("inner") if m.group("inner") is not None else m.group("bare")
        stmts = [s.strip() for s in body.split(";") if s.strip()]
        arms = [s for s in stmts if ARM_RE.match(s)]
        if len(arms) != 1 or any(s not in arms and not PIN_STMT_RE.match(s) for s in stmts):
            continue
        a = ARM_RE.match(arms[0])
        b, t = a.group("b"), m.group("t")
        k = _num(a.group("k1") or a.group("k2") or a.group("k3"))
        if k not in POW:
            continue
        n = POW[k]
        x = a.group("x2") or a.group("x3")
        src_b = last_copy_source(masked, m.start(), b)
        if x:                              # b = x + K / b = (x + K) >> n: the test is on x itself
            if x != t:
                continue
            d = x
            reads = x
        else:                              # b += K: b is the tested value or a copy of it
            if t != b and src_b != t:
                continue
            d = src_b if t == b else t
            reads = b
            if d is None:
                continue
        arm = "copy" if last_copy_source(masked, m.start(), reads) or reads == b and src_b else "source"
        skip, edits_full, pre = [], [], None
        q, shifted = b, bool(a.group("n3"))
        if shifted:
            if _num(a.group("n3")) != n:
                continue
            pre = _stmt_before(masked, m.start())   # the lane form shifts b BEFORE the test
            if not pre or not re.fullmatch(r"%s\s*>>=\s*(%s)\s*;" % (re.escape(b), NUM), pre[2]) or \
                    _num(re.fullmatch(r"%s\s*>>=\s*(%s)\s*;" % (re.escape(b), NUM), pre[2]).group(1)) != n:
                continue
            skip.append((pre[0], pre[1]))
        shift_stmt, rem, gap = None, None, 0
        for p in PIECE_RE.finditer(masked, m.end()):
            core = p.group(0).strip()
            if not core or core in "{}" or PIN_STMT_RE.match(core):
                continue
            if not shifted:
                sm = re.fullmatch(r"(%s)\s*>>=\s*(%s)\s*;" % (re.escape(q), NUM), core) or \
                    re.fullmatch(r"(%s)\s*=\s*%s\s*>>\s*(%s)\s*;" % (ID, re.escape(q), NUM), core)
                if sm and _num(sm.group(2)) == n:
                    shift_stmt, q, shifted = (p.start() + p.group(0).index(core[0]), p.end()), sm.group(1), True
                    skip.append(shift_stmt)
                    continue
            r = _remainder(p.group(0), d, q, n, shifted)
            if r:
                rem = (p.start() + r[0], p.start() + r[1])
                break
            gap += 1
            if gap > MAX_GAP:
                break
        if rem is None:
            continue
        mod = [(rem[0], rem[1], f"({d} % {1 << n})")]
        skip.append(rem)
        full = list(mod) + [(m.start(), m.end(), "")]
        q_live = _uses(masked, m.end(), q, skip + [(m.start(), m.end())])
        for span in ([pre[:2]] if pre else []) + ([shift_stmt] if shift_stmt else []):
            full.append((span[0], span[1], f"{q} = {d} / {1 << n};" if q_live else ""))
        out.append({"start": m.start(), "end": m.end(), "d": b, "vars": {b, d, q, t}, "arm": arm,
                    "n": n, "full": full, "mod": mod})
    return out


def _cut(text, s, e):
    """Widen [s, e) to whole lines when the statement has its lines to itself."""
    ls = text.rfind("\n", 0, s) + 1
    le = text.find("\n", e)
    if text[ls:s].strip() == "" and le >= 0 and text[e:le].strip() == "":
        return ls, le + 1
    return s, e


def _apply(text, edits):
    out = []
    for s, e, rep in edits:
        out.append(_cut(text, s, e) + (rep,) if rep == "" else (s, e, rep))
    for s, e, rep in sorted(out, key=lambda x: x[0], reverse=True):
        text = text[:s] + rep + text[e:]
    return text


def spell_one(text, it):
    return [("mod", _apply(text, it["full"])), ("modonly", _apply(text, it["mod"]))]


def spell_all(text, its):
    return _apply(text, [e for it in its for e in it["full"]])


class T:
    name = "t19_modpow2"
    level = 1
    needs_verify = True

    @staticmethod
    def eligible(text, row, census):
        if not sites_of(text):
            return "no live pin site"
        why = asm_blocker(text)
        if why:
            return why
        if not idioms(text):
            return "no signed power-of-two remainder idiom"
        return None

    @staticmethod
    def apply_verified(text, row, census, verify_fn):
        new, info = idiom_search(text, idioms, spell_one, spell_all, verify_fn)
        info["arms"] = ",".join(it["arm"] for it in idioms(text))
        return new, info
