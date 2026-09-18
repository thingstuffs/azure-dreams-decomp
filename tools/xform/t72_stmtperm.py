"""T72: the statement order around a pin searched as a permutation, screened by the cc1 listing.

APPEARS     a keep, register or barrier pin inside a run of simple statements (assignments, updates, call
            statements) at one brace depth; erasing the pin moves one or two instructions (the near band's
            MOVED classes: `-move +move`, `-addiu +addiu`, `-li +li`).
MECHANISM   gcc 2.x sched.c fills each block in reverse and breaks priority ties by original insn order
            (rank_for_schedule -> INSN_LUID); insns between two calls that touch call-clobbered registers tie
            at the call's priority, so the SOURCE statement order decides the instruction order.  The
            decompiler recovered its statement order from the scheduled bytes, which is the original order
            only where the scheduler moved nothing; the pin holds the difference.  T71 is the special case
            of loop updates written after a call (a pseudo crossing a call has no dependence on it and is
            hoisted); this generator searches every dependence-preserving order of the run instead.
CANDIDATES  per pin site: the run of simple statements around it (the RUN statements nearest the pin, pin
            lines excluded), the run's pins erased, and every linear extension of the run's dependence order
            (identifier read/write sets; memory accesses and calls stay ordered among themselves, a statement
            over locals only may cross a call) compiled to the cc1 listing at the row's recipe and compared
            with the pinned text's listing (retail's order).  Listing-exact orders go to `vf` (the byte
            scorer); the first exact one lands.  A permutation that changes the program cannot produce
            retail's bytes where the compiler keeps dependent statements in order; the dependence guard
            prunes, the scorer decides.
"""
import difflib, itertools, re, sys
from pathlib import Path
sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
from pin_census import sites_of, asm_blocker
try:
    from .t29_addrsym import mask_comments
    from .t36_paramwidth import functions
    from . import screen
except ImportError:
    from t29_addrsym import mask_comments
    from t36_paramwidth import functions
    import screen

RUN = 8                 # statements per run at most; the run shrinks until its orders fit MAX_ORDERS
MAX_ORDERS = 1000
MAX_LISTINGS = 1500     # per row
MAX_VERIFY = 6          # byte-scorer calls per row
MAX_SITES = 6
KEYWORDS = {"if", "for", "while", "do", "return", "goto", "switch", "case", "default", "break", "continue",
            "else", "sizeof", "NULL"}
TYPEWORDS = {"s8", "u8", "s16", "u16", "s32", "u32", "s64", "u64", "int", "char", "short", "long", "void",
             "unsigned", "signed", "float", "double", "struct", "union", "enum", "register", "static", "const",
             "volatile", "M2C_UNK", "typedef", "extern", "Vec3s", "Vec3i"}
IDENT = re.compile(r"\b[A-Za-z_]\w*\b")
PIN_LINE = re.compile(r"^[ \t]*ASM_[A-Z0-9_]+\s*\(")
CONTROL = re.compile(r"^[ \t]*(?:(?:else\s+)?if\b|else\b|for\b|while\b|do\b|switch\b|return\b|goto\b|break\b|continue\b|case\b|default\b)")
CAST = re.compile(r"(?<![\w)\]])\(\s*(?:(?:unsigned|signed|const|struct|union|enum)\s+)*[A-Za-z_]\w*\s*\**\s*\)(?=\s*[\w(&*-])")


def ids(x):
    x = re.sub(r"&\s*[A-Za-z_]\w*", " ", x)           # &name is an address constant, not a read
    return {i for i in IDENT.findall(x) if i not in KEYWORDS and i not in TYPEWORDS}


def decl_names(masked_body):
    names, bad = set(), set()
    for m in re.finditer(r"^[ \t]*(?P<q>(?:(?:register|const|volatile|static|unsigned|signed|struct|union|enum)[ \t]+)*)"
                         r"[A-Za-z_]\w*(?:[ \t]+long)?[ \t]*\**[ \t]*(?P<rest>[A-Za-z_]\w*(?:[ \t]*\[[^\]]*\])?"
                         r"(?:[ \t]*ASM_REG\([^()]*\))?(?:[ \t]*=[^;]*)?(?:[ \t]*,[ \t]*\**[ \t]*[A-Za-z_]\w*(?:[ \t]*\[[^\]]*\])?(?:[ \t]*=[^;]*)?)*)[ \t]*;",
                         masked_body, re.M):
        if re.match(r"[ \t]*(?:return|goto|else)\b", m.group(0)):
            continue
        arr = "[" in m.group("rest")
        for part in m.group("rest").split(","):
            n = re.match(r"[ \t\*]*([A-Za-z_]\w*)", part)
            if n:
                (bad if ("volatile" in m.group("q") or "static" in m.group("q") or arr) else names).add(n.group(1))
    return names - bad


def top_assign(s):
    """(lhs, op, rhs) of the outermost assignment in s, or None."""
    depth = 0
    for i, ch in enumerate(s):
        if ch in "([":
            depth += 1
        elif ch in ")]":
            depth -= 1
        elif ch == "=" and depth == 0:
            prev, nxt = s[i - 1] if i else "", s[i + 1] if i + 1 < len(s) else ""
            if nxt == "=" or prev in "=!<>":
                continue
            j = i
            op = ""
            while j > 0 and s[j - 1] in "+-*/%&|^<>":
                j -= 1; op = s[j] + op
            return s[:j].strip(), op, s[i + 1:].strip()
    return None


class Stmt:
    """One statement: lines, identifier writes/reads, memory and call flags, purity."""

    def __init__(self, lines, first, last, locals_, taken):
        self.lines, self.first, self.last = lines, first, last
        s = " ".join(l.strip() for l in lines).strip()
        if s.endswith(";"):
            s = s[:-1].rstrip()
        self.text = s
        nocast = CAST.sub(" ", s)
        self.call = bool(re.search(r"\b[A-Za-z_]\w*\s*\(", nocast))
        deref = bool(re.search(r"->|\.|\[|(?<![\w)\]])\s*\*", nocast))
        self.w, self.r, self.memw, self.memr = set(), set(), False, False
        a = top_assign(s)
        u = re.fullmatch(r"(?:\+\+|--)\s*([A-Za-z_]\w*)|([A-Za-z_]\w*)\s*(?:\+\+|--)", s)
        if a and not self.call:
            lhs, op, rhs = a
            if re.fullmatch(r"[A-Za-z_]\w*", lhs):
                self.w = {lhs}
                self.r = ids(rhs) | ({lhs} if op else set())
                self.memr = bool(re.search(r"->|\.|\[|(?<![\w)\]])\s*\*", CAST.sub(" ", rhs)))
            else:
                self.memw, self.memr = True, True
                self.r = ids(lhs) | ids(rhs)
                if re.search(r"(?<![\w])(?:\+\+|--)\s*[A-Za-z_]|[A-Za-z_]\w*\s*(?:\+\+|--)", rhs):
                    self.w |= ids(rhs)
        elif u and not self.call:
            v = u.group(1) or u.group(2)
            self.w, self.r = {v}, {v}
        else:
            self.call = True                      # a call, or an expression statement: treat as a call
            self.r = ids(s); self.memw = self.memr = True
            if a and re.fullmatch(r"[A-Za-z_]\w*", a[0]):
                self.w = {a[0]}
            if re.search(r"(?<![\w])(?:\+\+|--)\s*[A-Za-z_]|[A-Za-z_]\w*\s*(?:\+\+|--)", s):
                self.w |= ids(s)
        used = self.r | self.w
        self.pure = (not self.call and not self.memw and not self.memr and used <= locals_ and not (used & taken)
                     and not deref)
        # field keys: (base, field) of every `base->field` / `base.field` access; the store's key first
        self.stores, self.loads = set(), set()
        if not self.call:
            keys = [(re.sub(r"[()\s]", "", b), f) for b, f in re.findall(r"([A-Za-z_][\w\)\(\*\s]*?)\s*(?:->|\.)\s*([A-Za-z_]\w*)", nocast)]
            if a and self.memw:
                lk = [(re.sub(r"[()\s]", "", b), f) for b, f in re.findall(r"([A-Za-z_][\w\)\(\*\s]*?)\s*(?:->|\.)\s*([A-Za-z_]\w*)", CAST.sub(" ", a[0]))]
                self.stores = set(lk[-1:]) if lk and re.fullmatch(r"[\w\s\(\)\*]*(?:->|\.)\s*[A-Za-z_]\w*", CAST.sub(" ", a[0]).strip()) else set()
                self.loads = set(keys) - self.stores
            else:
                self.loads = set(keys)
            self.fielded = bool(self.stores) if self.memw else (bool(self.loads) and not re.search(r"\[|(?<![\w)\]])\s*\*", nocast))
        else:
            self.fielded = False


def depends(a, b):
    """Must a stay before b?  (a is written first in the text.)"""
    if a.w & (b.r | b.w) or b.w & a.r:
        return True
    if a.pure or b.pure:
        return False
    if a.call or b.call:
        return True
    conflict = (a.memw and (b.memr or b.memw)) or (b.memw and a.memr)
    if conflict and a.fielded and b.fielded:
        # both are field accesses: stores to different fields of the same base do not conflict
        def clash(x, y):
            return any(bx == by and fx == fy or bx != by for (bx, fx) in x for (by, fy) in y)
        conflict = clash(a.stores, b.stores | b.loads) or clash(b.stores, a.loads)
    return bool(conflict)


def statement_end(lines, i):
    depth = 0
    for j in range(i, min(len(lines), i + 10)):
        depth += lines[j].count("(") - lines[j].count(")")
        if depth <= 0 and lines[j].rstrip().endswith(";"):
            return j
        if depth <= 0 and j > i:
            return None
    return None


TYPE_START = re.compile(r"^[ \t]*(?:%s)\b" % "|".join(sorted(TYPEWORDS)))


def tokens(ml, first, last):
    """[(kind, i, j, indent)] over body lines: 'stmt' (i..j), 'pin', 'blank', 'other'."""
    out, i = [], first + 1
    while i < last:
        ln = ml[i]
        if not ln.strip():
            out.append(("blank", i, i, None)); i += 1; continue
        if PIN_LINE.match(ln) and ln.rstrip().endswith(";"):
            out.append(("pin", i, i, len(ln) - len(ln.lstrip()))); i += 1; continue
        if "{" in ln or "}" in ln or CONTROL.match(ln) or re.match(r"^[ \t]*\w+\s*:\s*$", ln) or ln.lstrip().startswith("#") \
                or TYPE_START.match(ln) or "ASM_" in ln:
            out.append(("other", i, i, None)); i += 1; continue
        j = statement_end(ml, i)
        if j is None:
            out.append(("other", i, i, None)); i += 1; continue
        out.append(("stmt", i, j, len(ln) - len(ln.lstrip()))); i = j + 1
    return out


def runs(text):
    """[(pin_lines, [Stmt])] per pin that sits inside a run of simple statements."""
    masked = mask_comments(text)
    ml, lines, out = masked.split("\n"), text.split("\n"), []
    pins = [s for s in sites_of(text) if PIN_LINE.match(ml[s[5] - 1]) and ml[s[5] - 1].rstrip().endswith(";")]
    for fname, params, b0, b1 in functions(text):
        body = masked[b0:b1]
        locals_ = decl_names(body) | {p for p, _, _, _ in params}
        taken = set(re.findall(r"&\s*([A-Za-z_]\w*)", body))
        first, last = masked.count("\n", 0, b0), masked.count("\n", 0, b1)
        toks = tokens(ml, first, last)
        idx = {t[1]: n for n, t in enumerate(toks)}
        for p in pins:
            pl = p[5] - 1
            if pl not in idx or toks[idx[pl]][0] != "pin":
                continue
            ind = toks[idx[pl]][3]
            n = idx[pl]
            lo = n
            while lo > 0 and (toks[lo - 1][0] in ("blank", "pin") or (toks[lo - 1][0] == "stmt" and toks[lo - 1][3] == ind)):
                lo -= 1
            hi = n
            while hi + 1 < len(toks) and (toks[hi + 1][0] in ("blank", "pin") or (toks[hi + 1][0] == "stmt" and toks[hi + 1][3] == ind)):
                hi += 1
            group = [t for t in toks[lo:hi + 1] if t[0] == "stmt"]
            if len(group) < 2:
                continue
            group.sort(key=lambda t: (abs(t[1] - pl), t[1]))
            pool = group[:RUN]
            while True:
                g = sorted(pool, key=lambda t: t[1])
                run = [Stmt(lines[t[1]:t[2] + 1], t[1], t[2], locals_, taken) for t in g]
                if len(run) < 2 or sum(1 for _ in orders(run, MAX_ORDERS + 1)) <= MAX_ORDERS:
                    break
                # too many orders: drop the farthest statement that is not a call (calls anchor the mechanism)
                by_stmt = {s.first: s for s in run}
                drop = next((t for t in reversed(pool) if not by_stmt[t[1]].call), pool[-1])
                pool = [t for t in pool if t is not drop]
            if len(run) < 2:
                continue
            span = (g[0][1], g[-1][2])
            window = [q[5] - 1 for q in pins if span[0] <= q[5] - 1 <= span[1]]
            out.append((window, run))
    return out


def orders(run, cap=None):
    """Every order of the run that keeps each dependent pair (in text order) in order; the identity first."""
    n = len(run)
    dep = [[a < b and depends(run[a], run[b]) for b in range(n)] for a in range(n)]
    k = 0
    for perm in itertools.permutations(range(n)):
        pos = {p: i for i, p in enumerate(perm)}
        if all(not dep[a][b] or pos[a] < pos[b] for a in range(n) for b in range(a + 1, n)):
            yield perm
            k += 1
            if cap and k >= cap:
                return


def build(text, run, perm, erase_lines):
    """Text with the run's statements in `perm` order; the pin lines in erase_lines dropped."""
    lines = text.split("\n")
    a, b = run[0].first, run[-1].last
    inner, out, pos, k = list(range(a, b + 1)), [], a, 0
    for s in run:
        out.extend(l for q in range(pos, s.first) for l in [lines[q]] if q not in erase_lines)
        out.extend(run[perm[k]].lines); k += 1
        pos = s.last + 1
    out.extend(lines[q] for q in range(pos, b + 1) if q not in erase_lines)
    return "\n".join(lines[:a] + out + lines[b + 1:])


def dist(a, b):
    return sum(1 for y in difflib.unified_diff(a, b, lineterm="", n=0) if y[:1] in "+-" and not y.startswith(("---", "+++")))


class T:
    name = "t72_stmtperm"
    level = 1
    needs_verify = True

    @staticmethod
    def eligible(text, row, census):
        why = asm_blocker(text)
        if why:
            return why
        if not sites_of(text):
            return "no pins"
        return None if any(w for w, _ in runs(text)) else "no pin inside a run of simple statements"

    @classmethod
    def apply_verified(cls, text, row, census, vf):
        pins_in, listings, verifies, steps, cur = len(sites_of(text)), 0, 0, [], text
        best = None                                   # (distance, perm) of the nearest non-exact order seen
        target = screen.compile_s(row, text)
        if target is None:
            return None, {"refused": ["pinned text does not build to a listing"], "pins_in": pins_in, "pins_out": pins_in}
        seen_runs = set()
        for _ in range(MAX_SITES):
            if listings >= MAX_LISTINGS or verifies >= MAX_VERIFY:
                break
            nxt = next(((w, r) for w, r in runs(cur) if w and tuple(s.text for s in r) not in seen_runs), None)
            if nxt is None:
                break
            window, run = nxt
            seen_runs.add(tuple(s.text for s in run))
            found = False
            for erase in [window] + ([[p] for p in window] if len(window) > 1 else []):
                exact = []
                for perm in orders(run):
                    if perm == tuple(range(len(run))) or listings >= MAX_LISTINGS:
                        continue
                    cand = build(cur, run, perm, set(erase))
                    lst = screen.compile_s(row, cand); listings += 1
                    if lst is None:
                        continue
                    d = dist(target, lst)
                    if d == 0:
                        exact.append((perm, cand))
                    elif best is None or d < best[0]:
                        best = (d, "".join(map(str, perm)), run[0].first + 1)
                for perm, cand in exact:
                    if verifies >= MAX_VERIFY:
                        break
                    if len(sites_of(cand)) >= len(sites_of(cur)):
                        continue
                    verifies += 1
                    if vf(cand).get("exact"):
                        cur, found = cand, True
                        steps.append("perm%s-erase%d" % ("".join(map(str, perm)), len(erase)))
                        break
                if found:
                    break
        info = {"listings": listings, "tried": verifies, "pins_in": pins_in, "pins_out": len(sites_of(cur)), "best": best}
        if not steps:
            return None, info
        return cur, dict(info, step="+".join(steps))
