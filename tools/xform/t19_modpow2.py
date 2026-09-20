"""T19: m2c's spelling of gcc's signed remainder by a power of two, written back as the `%`.

APPEARS     a bias `if (t < 0)` (no else arm) whose arm is `b = x + K;`, `b += K;` or
            `b = (x + K) >> n;` with K = 2^n - 1, and, within a few statements, a remainder that
            subtracts the rounded quotient from the dividend: `x - ((b >> n) << n)`, or
            `x - (q << n)` / `x - q * 2^n` once the quotient q is shifted (`b >>= n`, `q = b >> n`,
            or the arm's own shift).  x is the tested value, or what b was copied from.  Since round
            60 also the NAMED-quotient spelling, where the rounded quotient lands in a local of its
            own and a later statement subtracts it (dungeon/func_800D5794, lane r59_sol_large7):
                roll_remainder = offset_roll_a;
                if (offset_roll_a < 0) { roll_remainder = offset_roll_a + 63; }
                offset_sum = (roll_remainder >> 6) << 6;        <- s = (b >> n) << n
                roll_remainder = offset_roll_a - offset_sum;    <- r = x - s, read once below
            The rounded local must be dead after the subtraction, and where the remainder is the
            whole right-hand side of `r = x - s;` and r is read exactly once at the same brace depth
            with x unchanged in between, the `%` FOLDS into that reader and `r = ...;` goes - that
            fold is what makes func_800D5794 byte-exact (`offset_sum = (offset_roll_a % 64) +
            (offset_roll_b % 64) - 64;`, both idioms jointly, the `$5` ASM_REG erased, the `$2` kept).
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


def _remainder(seg, d, q, n, shifted, named=None):
    """(start, end) inside seg of `d - (q << n)` (shifted), `d - ((q >> n) << n)`, or - once the
    rounded quotient has landed in a named local s (`s = (q >> n) << n;`) - of `d - s`."""
    k = 1 << n
    if named:
        for m in re.finditer(r"(?<![.>\w])%s\s*-\s*%s(?![\w])" % (re.escape(d), re.escape(named)), seg):
            if not OK_BEFORE.search(seg[:m.start()]) or re.match(r"\s*[*/%]", seg[m.end():]):
                continue
            return m.start(), m.end()
        return None
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


def _named_dead(masked, named, rem_piece, skip):
    """Is the rounded value dead after the statement that consumes it (its own statement rewrites
    it, or nothing reads it before the next plain assignment)?"""
    head = re.match(r"^(%s)\s*=(?!=)" % ID, rem_piece[2])
    return bool(head and head.group(1) == named) or not _uses(masked, rem_piece[1], named, skip)


def _fold_use(masked, d, rem, rem_piece):
    """(start, end) of the single later read of `r` when the remainder is the whole right-hand side
    of `r = <remainder>;` - the reader takes the `%` and the statement goes."""
    head = re.fullmatch(r"\s*([A-Za-z_]\w*)\s*=\s*", masked[rem_piece[0]:rem[0]])
    if not head or masked[rem[1]:rem_piece[1]].strip() != ";":
        return None
    r = head.group(1)
    if r == d:
        return None
    for p in PIECE_RE.finditer(masked, rem_piece[1]):
        core = p.group(0).strip()
        if not core or core in "{}" or PIN_STMT_RE.match(core):
            continue
        hits = [u for u in re.finditer(r"(?<![.>\w])%s\b" % re.escape(r), p.group(0))]
        if not hits:
            if re.search(r"(?<![.>\w])%s\s*(?:[-+*/%%&|^]|<<|>>)?=(?!=)|&\s*%s\b|\b%s\s*(?:\+\+|--)"
                         % ((re.escape(d),) * 3), p.group(0)):
                return None                # d changes before the read: the `%` cannot move down
            continue
        if len(hits) != 1 or re.match(r"^%s\s*(?:[-+*/%%&|^]|<<|>>)?=(?!=)" % re.escape(r), core) or \
                re.search(r"&\s*%s\b|\b%s\s*(?:\+\+|--)" % ((re.escape(r),) * 2), p.group(0)):
            return None
        between = masked[rem_piece[1]:p.start() + hits[0].start()]
        if between.count("{") != between.count("}") or "goto" in between:
            return None                    # the read must sit in the same block, at the same depth
        if _uses(masked, p.end(), r, []):
            return None                    # read again later: the statement has to stay
        return p.start() + hits[0].start(), p.start() + hits[0].end()
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
        named, round_stmt, rem_piece = None, None, None
        for p in PIECE_RE.finditer(masked, m.end()):
            core = p.group(0).strip()
            if not core or core in "{}" or PIN_STMT_RE.match(core):
                continue
            if not shifted and named is None:
                # the rounded quotient in a NAMED local: `s = (b >> n) << n;` (dungeon/func_800D5794)
                nm = re.fullmatch(r"(%s)\s*=\s*\(\s*%s\s*>>\s*(%s)\s*\)\s*<<\s*(%s)\s*;"
                                  % (ID, re.escape(q), NUM, NUM), core)
                if nm and _num(nm.group(2)) == n and _num(nm.group(3)) == n and nm.group(1) not in (b, d, t):
                    named = nm.group(1)
                    round_stmt = (p.start() + p.group(0).index(core[0]), p.end())
                    skip.append(round_stmt)
                    continue
                sm = re.fullmatch(r"(%s)\s*>>=\s*(%s)\s*;" % (re.escape(q), NUM), core) or \
                    re.fullmatch(r"(%s)\s*=\s*%s\s*>>\s*(%s)\s*;" % (ID, re.escape(q), NUM), core)
                if sm and _num(sm.group(2)) == n:
                    shift_stmt, q, shifted = (p.start() + p.group(0).index(core[0]), p.end()), sm.group(1), True
                    skip.append(shift_stmt)
                    continue
            r = _remainder(p.group(0), d, q, n, shifted, named)
            if r:
                rem = (p.start() + r[0], p.start() + r[1])
                rem_piece = (p.start() + p.group(0).index(core[0]), p.end(), core)
                break
            gap += 1
            if gap > MAX_GAP:
                break
        if rem is None:
            continue
        if named and not _named_dead(masked, named, rem_piece, skip):
            continue                       # the rounded value is read again: its statement must stay
        if named:                          # `(x - s)` -> `(x % 2^n)`: the spare parentheses go too
            lhs, rhs = masked[:rem[0]].rstrip(), masked[rem[1]:]
            if lhs.endswith("(") and rhs.lstrip().startswith(")"):
                rem = (len(lhs) - 1, rem[1] + len(rhs) - len(rhs.lstrip()) + 1)
        mod = [(rem[0], rem[1], f"({d} % {1 << n})")]
        skip.append(rem)
        full = list(mod) + [(m.start(), m.end(), "")]
        q_live = _uses(masked, m.end(), q, skip + [(m.start(), m.end())])
        for span in ([pre[:2]] if pre else []) + ([shift_stmt] if shift_stmt else []) + ([round_stmt] if named else []):
            full.append((span[0], span[1], f"{q} = {d} / {1 << n};" if q_live and span is not round_stmt else ""))
        plain = list(full)
        use = _fold_use(masked, d, rem, rem_piece) if named else None
        if use:                            # `r = x - s;` read once below: the `%` goes to the reader
            full = [(m.start(), m.end(), ""), (rem_piece[0], rem_piece[1], ""),
                    (use[0], use[1], f"({d} % {1 << n})"), (round_stmt[0], round_stmt[1], "")]
        out.append({"start": m.start(), "end": m.end(), "d": b, "vars": {b, d, q, t}, "arm": arm,
                    "n": n, "named": named, "full": full, "plain": plain, "mod": mod})
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
    out = [("mod", _apply(text, it["full"]))]
    if it.get("plain") and it["plain"] != it["full"]:
        out.append(("nofold", _apply(text, it["plain"])))
    return out + [("modonly", _apply(text, it["mod"]))]


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
