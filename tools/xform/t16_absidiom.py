"""T16: m2c's spelling of gcc's MIPS `abssi2`, written back as the `abs()` it came from.

APPEARS     an in-place conditional negate with no else arm - `if (t < 0) { d = -d; }` - where
            the guard tests d itself or the value d was last copied from (`d = t;` above it), and
            the block holds nothing but that negate and pins.  Usually an ASM_REG / ASM_KEEP on d.
RESOLVES    gcc 2.x's MIPS backend has an `abssi2` insn: `bgez %1,1f; move %0,%1; subu %0,$0,%0`
            - the copy and the negate are ONE insn.  Spelled as a copy plus a negate, cse folds
            the copy (`-d` becomes `-t`), so gcc emits `negu d,t` where retail has `negu d,d`:
            the one-word 'rename' residue those pins were holding.  `abs()` goes through
            expand_abs -> abssi2, which cse cannot see into, so the copy survives with no pin.
            Same family as m2c's hand-expanded `x % (1 << n)` (expand_divmod's own
            copy_to_mode_reg), found on the reg-rename lane.
POPULATION  2026-09-11, pinned rows: 97 adjacent copy+negate sites in 55 rows (43 pins naming the
            destination), 269 in-place negates on one variable, 39 guarded on the source; 142
            pinned rows eligible.  Hand test before this was written: town/func_80097648 exact
            with 4 of its 5 pins gone, town/func_80091F04 with 3 of 29 (141 words from pin-free -
            a row t15's damage band never looks at).

NOT EVERY conditional negate is an abs: a plain `if (x < 0) x = -x;` that retail compiled as a
branch around a negate must stay as written.  So the search is greedy, one idiom at a time, last
first, each in two spellings - `d = abs(d);` (the copy above stays, and cse propagates it into the
operand) and, when the copy is the statement right above, `d = abs(t);` with the copy folded in -
first with the pins naming d erased, then keeping them.  Whatever stays exact is kept.  Then every
pin left is tried once on its own, because a rewrite can leave another pin with nothing to hold.
The result lands only if it carries fewer pins than it started with.
"""
import re, sys
from pathlib import Path
sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
from pin_census import sites_of, erase, asm_blocker
from pin_sites import erase_many               # erases the pins' own notes with them
try:
    from .t12_stmtorder import mask
except ImportError:
    from t12_stmtorder import mask

BUDGET = 60
# `if (t < 0) { pins; d = -x; }` or the braceless `if (t < 0) d = -x;` - over the MASKED text
IF_RE = re.compile(r"\bif\s*\(\s*(?P<t>[A-Za-z_]\w*)\s*<\s*0\s*\)\s*"
                   r"(?:\{(?P<inner>[^{}]*)\}|(?P<bare>[A-Za-z_]\w*\s*=\s*-\s*[A-Za-z_]\w*\s*;))")
NEG_RE = re.compile(r"^(?P<d>[A-Za-z_]\w*)\s*=\s*-\s*(?P<x>[A-Za-z_]\w*)$")
PIN_STMT_RE = re.compile(r"^ASM_[A-Z0-9_]+\([^;]*\)$")
ELSE_RE = re.compile(r"\s*else\b")
# the statement right above the if (pins between allowed): `d = <ident>;`
COPY_RE = re.compile(r"(?P<d>[A-Za-z_]\w*)\s*=\s*(?P<s>[A-Za-z_]\w*)\s*;(?P<pins>(?:\s*ASM_[A-Z0-9_]+\([^;]*\)\s*;)*)\s*$")


def last_copy_source(masked, pos, d):
    """The right-hand side of the last plain `d = <ident>;` before pos, or None."""
    src = None
    for m in re.finditer(r"(?<![.>\w])\b%s\s*=\s*(?!=)([^;]+);" % re.escape(d), masked[:pos]):
        rhs = m.group(1).strip()
        src = rhs if re.fullmatch(r"[A-Za-z_]\w*", rhs) else None
    return src


def idioms(text):
    """[{start, end, d, t, copy: (start, end) | None}] for every rewritable conditional negate."""
    masked = mask(text)
    out = []
    for m in IF_RE.finditer(masked):
        if ELSE_RE.match(masked, m.end()):
            continue
        body = m.group("inner") if m.group("inner") is not None else m.group("bare")
        stmts = [s.strip() for s in body.split(";") if s.strip()]
        negs = [s for s in stmts if NEG_RE.match(s)]
        if len(negs) != 1 or any(s not in negs and not PIN_STMT_RE.match(s) for s in stmts):
            continue
        n = NEG_RE.match(negs[0])
        d, x, t = n.group("d"), n.group("x"), m.group("t")
        # the negated value must be d itself (in place) or the tested value, and the test must be
        # on d or on what d was last copied from - otherwise this is not an absolute value
        if x not in (d, t):
            continue
        if t != d and last_copy_source(masked, m.start(), d) != t:
            continue
        # the statement immediately above (back to the previous `;`, `{` or `}`)
        lo = max(masked.rfind(";", 0, m.start() - 1), masked.rfind("{", 0, m.start()), masked.rfind("}", 0, m.start()))
        lo2 = max(masked.rfind(";", 0, lo), masked.rfind("{", 0, lo), masked.rfind("}", 0, lo))
        c = COPY_RE.search(masked[lo2 + 1:m.start()]) if lo >= 0 else None
        copy = None
        if c and c.group("d") == d and not c.group("pins").strip() and (t in (d, c.group("s"))):
            copy = (lo2 + 1 + c.start(), lo2 + 1 + c.end("s") + masked[lo2 + 1 + c.end("s"):].find(";") + 1, c.group("s"))
        out.append({"start": m.start(), "end": m.end(), "d": d, "t": t, "copy": copy})
    return out


def with_abs_decl(text):
    if re.search(r"\babs\s*\(\s*int\s*\)|<stdlib\.h>", text):
        return text
    incs = list(re.finditer(r"^#include[^\n]*\n", text, re.M))
    at = incs[-1].end() if incs else 0
    return text[:at] + "extern int abs(int);\n" + text[at:]


def spellings(text, it):
    """[(label, text)] for one idiom: in place, then with its copy folded in."""
    d = it["d"]
    out = [("inplace", text[:it["start"]] + f"{d} = abs({d});" + text[it["end"]:])]
    if it["copy"]:
        cs, ce, src = it["copy"]           # the copy statement becomes the abs; the if goes
        out.append(("fold", text[:cs] + f"{d} = abs({src});" + text[it["end"]:]))
    return [(l, with_abs_decl(t)) for l, t in out]


def names_var(site, names):
    kind, macro, arg, start, end, line_no, repl = site
    if kind == "reg":
        return bool(repl) and repl.split()[-1].lstrip("*") in names
    return any(a.strip() in names for a in arg.split(","))


class T:
    name = "t16_absidiom"
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
            return "no conditional-negate idiom"
        return None

    @staticmethod
    def apply_verified(text, row, census, verify_fn):
        pins_in = len(sites_of(text))
        n = n_found = len(idioms(text))
        cur, steps, tried = text, [], 0

        def attempt(cand):
            nonlocal tried
            tried += 1
            return verify_fn(cand).get("exact")

        # 0. every idiom at once with every pin naming one of them: some rows only fall JOINTLY
        #    (town/func_803300DC: both idioms and their pins together, neither alone)
        if n > 1:
            its, new = idioms(cur), cur
            for it in reversed(its):            # last first: earlier offsets stay valid
                new = new[:it["start"]] + f"{it['d']} = abs({it['d']});" + new[it["end"]:]
            new = with_abs_decl(new)            # once, at the end: it shifts every offset below it
            names = {it["d"] for it in its}
            on = [s for s in sites_of(new) if names_var(s, names)]
            if on and attempt(erase_many(new, on, clean_notes=True)):
                cur = erase_many(new, on, clean_notes=True)
                steps.append("all+unpin")
                n = 0                      # nothing left to rewrite
        # 1. each idiom, last first (a rewrite never moves an earlier idiom's position in the list)
        for idx in reversed(range(n)):
            found = idioms(cur)
            if idx >= len(found) or tried >= BUDGET:
                continue
            it = found[idx]
            done = False
            for label, new in spellings(cur, it):
                on = [s for s in sites_of(new) if names_var(s, {it["d"]})]
                for cand, tag in ((erase_many(new, on, clean_notes=True), "+unpin") if on else (None, ""), (new, "")):
                    if cand is None or tried >= BUDGET:
                        continue
                    if attempt(cand):
                        cur, done = cand, True
                        steps.append(f"{label}:{it['d']}{tag}")
                        break
                if done:
                    break
        if not steps:
            return None, {"tried": tried, "pins_in": pins_in, "pins_out": pins_in, "idioms": n_found}
        # 2. every pin still standing, once on its own
        i = 0
        while tried < BUDGET:
            live = sites_of(cur)
            if i >= len(live):
                break
            cand = erase_many(cur, [live[i]], clean_notes=True)
            if attempt(cand):
                cur = cand
                steps.append("dead:" + live[i][1])
            else:
                i += 1
        pins_out = len(sites_of(cur))
        if pins_out >= pins_in:
            return None, {"tried": tried, "pins_in": pins_in, "pins_out": pins_in, "idioms": n_found,
                          "rewrote": "+".join(steps)}
        return cur, {"step": "+".join(steps), "tried": tried, "pins_in": pins_in, "pins_out": pins_out, "idioms": n_found}
