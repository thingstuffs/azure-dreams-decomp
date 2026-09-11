"""T17: m2c's spelling of gcc's signed division by a power of two, written back as the `/`.

APPEARS     `if (t < 0) { d += 2^n-1; }` or `if (t < 0) { d = t + 2^n-1; }` (d copied from t just
            above, or d is t), no else arm, and the first later statement that mentions d shifts
            it right by n: `... d >> n ...` or `d >>= n;`.  Usually with pins on d.
RESOLVES    expand_divmod (expmed.c) lowers a signed `x / 2^n` (2^n > 2, BRANCH_COST < 3) as
            `t1 = copy_to_mode_reg (x); if (t1 < 0) t1 += 2^n - 1; q = t1 >> n` - the copy is a
            fresh pseudo of its own.  Spelled out by hand, cse collapses `d = x;` into x and the
            allocator loses the second register retail keeps, which is what the pins stood in for.
            Written as `x / 2^n`, gcc re-emits its own copy.  Same family as t16 (abssi2) and the
            `%` idiom the reg-rename lane closed two rows with.
POPULATION  2026-09-11: 246 bias sites in 129 pinned rows.  Consumer = the first later statement
            naming d: `d >> n` inside an expression 209 (165 of them the very next statement),
            `d >>= n;` 30 - 243 of the 249 classified.  x / 2 is branch-free in gcc
            (`(x + ((u32)x >> 31)) >> 1`, 4 spellings in pinned rows) and is not handled here.

The rewrite deletes the bias `if` and turns the shift into the division - `(d / 4096)` in an
expression, `d /= 4096;` as a statement - leaving any copy above in place (cse propagates it).
The search is t16's `idiom_search`: jointly first, then one idiom at a time, then each pin alone.
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

POW = {(1 << n) - 1: n for n in range(2, 16)}
NUM = r"(?:0x[0-9A-Fa-f]+|\d+)"
IF_RE = re.compile(r"\bif\s*\(\s*(?P<t>[A-Za-z_]\w*)\s*<\s*0\s*\)\s*(?:\{(?P<inner>[^{}]*)\}|(?P<bare>[^{};]*;))")
ASG_RE = re.compile(r"^(?P<d>[A-Za-z_]\w*)\s*(?:\+=\s*(?P<k1>" + NUM + r")|=\s*(?P<t>[A-Za-z_]\w*)\s*\+\s*(?P<k2>" + NUM + r"))$")
PIN_STMT_RE = re.compile(r"^ASM_[A-Z0-9_]+\([^;]*\)\s*;?$")
PIECE_RE = re.compile(r"[^;{}]*[;{}]")
MAX_GAP = 6                     # statements between the bias and its shift (measured: 243/249 inside)


def idioms(text):
    """[{start, end, d, cons: (start, end, replacement)}] - the bias `if` and the shift it feeds."""
    masked = mask(text)
    out = []
    for m in IF_RE.finditer(masked):
        if re.match(r"\s*else\b", masked[m.end():]):
            continue
        body = m.group("inner") if m.group("inner") is not None else m.group("bare")
        stmts = [s.strip() for s in body.split(";") if s.strip()]
        asg = [s for s in stmts if ASG_RE.match(s)]
        if len(asg) != 1 or any(s not in asg and not PIN_STMT_RE.match(s) for s in stmts):
            continue
        a = ASG_RE.match(asg[0])
        d, t = a.group("d"), m.group("t")
        k = int(a.group("k1") or a.group("k2"), 0)
        if k not in POW or (a.group("t") and a.group("t") != t):
            continue
        if d != t and last_copy_source(masked, m.start(), d) != t:
            continue
        n, cons, gap = POW[k], None, 0
        for p in PIECE_RE.finditer(masked, m.end()):
            core = p.group(0).strip()
            if not core or core in "{}" or PIN_STMT_RE.match(core):
                continue
            if re.search(r"(?<![.>\w])\b%s\b" % re.escape(d), core):
                cons = p
                break
            gap += 1
            if gap > MAX_GAP:
                break
        if cons is None:
            continue
        seg = masked[cons.start():cons.end()]
        whole = re.fullmatch(r"(\s*)%s\s*>>=\s*(%s)\s*;" % (re.escape(d), NUM), seg)
        if whole:
            if int(whole.group(2), 0) != n:
                continue
            edit = (cons.start() + len(whole.group(1)), cons.end(), f"{d} /= {k + 1};")
        else:
            sm = re.search(r"(?<![.>\w])\b%s\s*>>\s*(\(\s*%s\s*\)|%s)" % (re.escape(d), NUM, NUM), seg)
            if not sm or int(sm.group(1).strip("() \t"), 0) != n:
                continue
            before, after = seg[:sm.start()].rstrip(), seg[sm.end():].lstrip()
            # `a + d >> n` is `(a + d) >> n`, and `d >> n + 1` shifts by n+1: not this idiom
            if re.search(r"(?<![+-])[-+*/%]$|<<$|>>$", before) or after[:1] in ("+", "-", "*", "/", "%"):
                continue
            edit = (cons.start() + sm.start(), cons.start() + sm.end(), f"({d} / {k + 1})")
        out.append({"start": m.start(), "end": m.end(), "d": d, "cons": edit})
    return out


def _cut(text, s, e):
    """Widen [s, e) to whole lines when the statement has its lines to itself."""
    ls = text.rfind("\n", 0, s) + 1
    le = text.find("\n", e)
    if text[ls:s].strip() == "" and le >= 0 and text[e:le].strip() == "":
        return ls, le + 1
    return s, e


def _apply(text, its):
    edits = []
    for it in its:
        edits.append(it["cons"])
        s, e = _cut(text, it["start"], it["end"])
        edits.append((s, e, ""))
    for s, e, rep in sorted(edits, key=lambda x: x[0], reverse=True):
        text = text[:s] + rep + text[e:]
    return text


def spell_one(text, it):
    return [("div", _apply(text, [it]))]


def spell_all(text, its):
    return _apply(text, its)


class T:
    name = "t17_divpow2"
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
            return "no signed power-of-two division idiom"
        return None

    @staticmethod
    def apply_verified(text, row, census, verify_fn):
        return idiom_search(text, idioms, spell_one, spell_all, verify_fn)
