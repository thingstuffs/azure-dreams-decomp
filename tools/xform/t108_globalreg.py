"""T108: a FILE-SCOPE global register variable (`register T v ASM_REG("$n");` outside any function) turned
into an ordinary local of the one function that uses it.

APPEARS     m2c's output for a value retail keeps in a fixed register across a function's arms is sometimes
            staged by the matching pass through a GCC global register variable declared at file scope -
            the "carrier in $2/$4/$7" of four round-73/74 rows, one per model:

                #ifndef NON_MATCHING
                register s32 state ASM_REG("$7");       <- file scope, a pin
                #else
                static s32 state;
                #endif
                void func_800BF4CC(S0 *self, s32 *position, S1 *target) {
            ->  the file-scope line gone, and at the top of the function
                #ifndef NON_MATCHING
                    register s32 state;
                #endif

            town/func_800C1D6C (gpt-6-sol v3, work/native_lane/r74_sol6v3_a1, 2 pins with a keep);
            town/func_8032CE94 (astra, r73_astra_a2), town/func_8032BD34 (gpt-6-luna, r73_luna6_s3) and
            main/func_80012848 (claude-opus-5-5, r73_opus_s2) remove the same kind of declaration while
            also rewriting the function by hand (t106_nmpromote covers the last).

RESOLVES    sol's rule (r74_sol6v3_a1/REPORT.md, func_800C1D6C): "APPEARS when a file-scope `ASM_REG`
            variable is used only by one function to hold a dispatch field. RESOLVES by declaring the value
            inside that function in the scored arm and re-censusing nearby keeps, since the new local
            pseudo can change scheduler dependencies."  A global register variable is not a pseudo at all
            - every read and write is a hard-register access the scheduler must keep in order - so a
            local declaration gives the allocator back a value it can colour and sched a value it can
            move; the keeps that were standing in for the lost freedom can then go.

WHY NOTHING MISSES IT TODAY: no generator reads a file-scope declaration.  `sites_of` counts the line as
            an ordinary `ASM_REG` pin, and every register-pin generator (t9, t26, t37, t62, t66) walks the
            DECLARATIONS OF A FUNCTION, so the line is invisible to all of them; erasing it in place
            leaves `register T v;` at file scope, which is not valid C.

CANDIDATES  all such declarations of the file moved together, then each alone - per file-scope register
            declaration used by exactly one function (and, when it sits in a
            file-scope `#ifndef NON_MATCHING` arm, never named by that function's NON_MATCHING arm): the
            declaration moved to the top of the function as `register T v;` and as `T v;` (guarded by
            `#ifndef NON_MATCHING` when the original was); each with no other pin erased, with every other
            pin of the function erased on its own, and with all of them erased.  Ranked by the cc1 listing
            distance to the pinned text; the listing-exact candidates and the two nearest go to `vf`.
            The NON_MATCHING arms are never edited.
"""
import difflib
import re
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
from pin_census import sites_of, asm_blocker, unscored_text
from pin_sites import erase_many
try:
    from .t29_addrsym import mask_comments
    from .t36_paramwidth import functions
    from . import screen
except ImportError:
    from t29_addrsym import mask_comments
    from t36_paramwidth import functions
    import screen

MAX_LISTINGS = 40
MAX_VERIFY = 4
MAX_SINGLES = 8
GDECL = re.compile(r"^register[ \t]+(?P<ty>[A-Za-z_][\w \t]*?)(?P<ptr>[ \t\*]*?)\b(?P<v>[A-Za-z_]\w*)[ \t]*"
                   r"ASM_REG\([ \t]*\"\$\w+\"[ \t]*\)[ \t]*;[^\n]*$", re.M)


def _guard(lines, k):
    """'m' if line k sits in the matching arm of a file-scope NON_MATCHING split, 'n' in the other, '' outside."""
    stack = []
    for q in range(k):
        s = lines[q].strip()
        if re.match(r"#\s*ifndef\s+NON_MATCHING\b", s):
            stack.append("m")
        elif re.match(r"#\s*ifdef\s+NON_MATCHING\b", s):
            stack.append("n")
        elif re.match(r"#\s*if", s):
            stack.append("?")
        elif re.match(r"#\s*else\b", s) and stack:
            stack[-1] = {"m": "n", "n": "m"}.get(stack[-1], "?")
        elif re.match(r"#\s*endif\b", s) and stack:
            stack.pop()
    return "" if not stack else stack[-1]


def _nm_ranges(lines, a, b):
    """Line ranges [a, b) of the function that sit in a NON_MATCHING arm."""
    out, stack = set(), []
    for q in range(a, b):
        s = lines[q].strip()
        if re.match(r"#\s*ifndef\s+NON_MATCHING\b", s):
            stack.append("m")
        elif re.match(r"#\s*ifdef\s+NON_MATCHING\b", s):
            stack.append("n")
        elif re.match(r"#\s*if", s):
            stack.append("?")
        elif re.match(r"#\s*else\b", s) and stack:
            stack[-1] = {"m": "n", "n": "m"}.get(stack[-1], "?")
        elif re.match(r"#\s*endif\b", s) and stack:
            stack.pop()
        elif "n" in stack:
            out.add(q)
    return out


def sites(text):
    """[{v, line, decl, guard, fn_open}] - file-scope register variables used by exactly one function."""
    masked = mask_comments(text)
    lines, mlines = text.split("\n"), masked.split("\n")
    fns = functions(text)
    out = []
    for m in GDECL.finditer(masked):
        k = masked.count("\n", 0, m.start())
        if any(b0 <= m.start() < b1 for _, _, b0, b1 in fns):
            continue
        g = _guard(mlines, k)
        if g == "n" or g == "?":
            continue
        v = m.group("v")
        users = [f for f in fns if re.search(r"\b%s\b" % re.escape(v), masked[f[2]:f[3]])]
        if len(users) != 1:
            continue
        f = users[0]
        a, b = masked.count("\n", 0, f[2]), masked.count("\n", 0, f[3])
        if g == "m" and any(re.search(r"\b%s\b" % re.escape(v), mlines[q]) for q in _nm_ranges(mlines, a, b + 1)):
            continue
        ty = (m.group("ty").strip() + " " + m.group("ptr").replace(" ", "").replace("\t", "")).strip()
        out.append({"v": v, "line": k, "ty": ty, "guard": g, "open": a, "close": b})
    return out


def move(text, st, reg):
    lines = text.split("\n")
    decl = "    %s%s%s%s;" % ("register " if reg else "", st["ty"], "" if st["ty"].endswith("*") else " ", st["v"])
    ins = ["#ifndef NON_MATCHING", decl, "#endif"] if st["guard"] == "m" else [decl]
    out = []
    for q, l in enumerate(lines):
        if q == st["line"]:
            continue
        out.append(l)
        if q == st["open"]:
            out.extend(ins)
    return "\n".join(out)


def move_all(text, names, reg):
    """Every named site moved, one after another (line numbers are re-read after each move)."""
    for v in names:
        st = next((x for x in sites(text) if x["v"] == v), None)
        if st is None:
            return None
        text = move(text, st, reg)
    return text


def candidates(text):
    sig, n0 = unscored_text(text), len(sites_of(text))
    out, seen = [], {text}
    ss = sites(text)
    groups = ([("+".join(x["v"] for x in ss), ss)] if len(ss) > 1 else []) + [(x["v"], [x]) for x in ss]
    for gname, grp in groups:
        for reg in (True, False):
            base = move_all(text, [x["v"] for x in grp], reg)
            if base is None:
                continue
            # the function's pins in the moved text (the file-scope lines are gone, lines were added)
            lo = min(x["open"] for x in grp) - len(grp)
            hi = max(x["close"] for x in grp) + 3 * len(grp)
            fpins = [p for p in sites_of(base) if lo <= p[5] - 1 <= hi]
            plans = [("none", [])] + [("one%d" % (p[5]), [p]) for p in fpins[:MAX_SINGLES]]
            if len(fpins) > 1:
                plans.append(("all", fpins))
            for ptag, group in plans:
                cand = erase_many(base, group, clean_notes=True) if group else base
                if cand in seen or unscored_text(cand) != sig or len(sites_of(cand)) >= n0:
                    continue
                seen.add(cand)
                out.append(("%s:%s:%s" % (gname, "reg" if reg else "plain", ptag), cand))
    return out


def _dist(a, b):
    return sum(1 for y in difflib.unified_diff(a, b, lineterm="", n=0)
               if y[:1] in "+-" and not y.startswith(("---", "+++")))


class T:
    name = "t108_globalreg"
    level = 1
    needs_verify = True

    @staticmethod
    def eligible(text, row, census):
        why = asm_blocker(text)
        if why:
            return why
        if not sites_of(text):
            return "no pin sites"
        if not GDECL.search(mask_comments(text)):
            return "no file-scope register variable"
        if not sites(text):
            return "no file-scope register variable used by exactly one function's scored arm"
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
            tried += 1
            if vf(cand).get("exact"):
                return cand, dict(info, step="%s|d%d" % (label, d), pins_out=pins, tried=tried)
        return None, dict(info, tried=tried,
                          nearest=[{"distance": d, "label": l} for d, _p, l, _c in ranked[:6]])
