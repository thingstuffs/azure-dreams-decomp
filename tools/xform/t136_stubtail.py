"""T136: `goto L;` into a short return stub written as the stub itself (readability; pins untouched).

APPEARS     m2c funnels several exits through one label inside a switch arm / if arm / mid-function:
              `goto L; ... L: func_X(a, b); return;`        (or `L: D = 0; func_Y(p); return 1;`)
            t123_returntail only handles the function's FINAL `L: return E; }`; this is the same move for a
            stub of at most 3 simple statements (no braces/labels/declarations/goto) that ends in
            `return;` / `return E;` wherever the label sits.  Round-93 hand lanes (Sonnet g7-g9) removed
            these gotos on 18 of 18 rows byte-exact.  A `goto L;` whose label is the very next statement is
            the same family (the goto is deleted).
RESOLVES    the stub's statements copied verbatim in place of each `goto L;` (wrapped in braces when the
            goto was the unbraced body of an if/else/loop).  Nothing runs between the jump and the stub, so
            it is the same program; gcc 2.x cross-jumping usually re-merges the copies, the verifier
            decides.  When no goto targets L any more only the `L:` label is removed (the stub stays, code
            falls into it).  Candidates: every site at once, then per label, then per goto, greedily
            keeping what stays exact (budget T136_MAX, default 16); pins must be unchanged, gotos fewer.
SAFETY      a copied identifier must resolve to the same declaration at the goto and at the label (a name
            declared in a block that does not enclose both refuses that stub).  Refused: stubs / gotos in
            #if regions, rows with computed gotos (`goto *`, `&&label`), stubs holding ASM_ pins.
POPULATION  no-compile census over src/*/*.c (6,808 rows, round 93): 134 rows eligible, 289 gotos targeted, 18 of the rows carry pins.  Test: 24 hand-lane texts, 14 rows exact (47 gotos removed).
"""
import os, re, sys
from pathlib import Path
sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
from pin_census import sites_of
try:
    from .t122_gotowhile import mask, KEYWORDS, gotos
except ImportError:
    from t122_gotowhile import mask, KEYWORDS, gotos

MAX_VERIFY = int(os.environ.get("T136_MAX", "16"))
MAX_STMTS = 3
MAX_CHARS = int(os.environ.get("T136_MAXC", "200"))
LABEL_AT = re.compile(r"[ \t]*([A-Za-z_]\w*)[ \t]*:(?!:)[ \t]*")
LABEL_LINE = re.compile(r"^[ \t]*([A-Za-z_]\w*)[ \t]*:(?!:)", re.M)
BAD_START = {"if", "else", "for", "while", "do", "switch", "goto", "break", "continue", "case", "default",
             "return_", "typedef", "struct", "union", "enum"}
NOT_TYPE = {"return", "goto", "else", "case", "default", "break", "continue", "sizeof", "do", "if", "while",
            "for", "switch"}
DECL = re.compile(r"^[ \t]*(?:(?:register|static|const|volatile|unsigned|signed|struct|union|extern)[ \t]+)*"
                  r"([A-Za-z_]\w*)[ \t]+(?:\*[ \t]*)*([A-Za-z_]\w*)[ \t]*(?:\[[^\]\n]*\][ \t]*)*(?:=|;|,)", re.M)
IDENT = re.compile(r"[A-Za-z_]\w*")


def blocks(m):
    """[(open, close)] of every {...} in the masked text."""
    st, out = [], []
    for i, ch in enumerate(m):
        if ch == "{": st.append(i)
        elif ch == "}" and st: out.append((st.pop(), i))
    return out


def pp_depth(text):
    """Per-offset flag: inside an #if...#endif region."""
    flag = bytearray(len(text)); d = 0; pos = 0
    for line in text.split("\n"):
        s = line.strip()
        if re.match(r"#\s*if", s): d += 1
        if d > 0:
            for k in range(pos, pos + len(line) + 1):
                if k < len(flag): flag[k] = 1
        if re.match(r"#\s*endif", s): d = max(0, d - 1)
        pos += len(line) + 1
    return flag


def parse_stub(m, text, p):
    """Statements after a label's colon at index p of the masked text -> (stmts, end) or None."""
    stmts = []
    i = p
    while True:                                   # stacked plain labels are skipped
        mm = LABEL_AT.match(m, i)
        if mm and mm.group(1) not in KEYWORDS and mm.group(1) not in NOT_TYPE and m[mm.end():mm.end() + 1] != ":":
            i = mm.end(); continue
        break
    while len(stmts) < MAX_STMTS:
        while i < len(m) and m[i] in " \t\n\r": i += 1
        if i >= len(m): return None
        mm = IDENT.match(m, i)
        first = mm.group(0) if mm else ""
        if m[i] in "{};#" or first in BAD_START or first in KEYWORDS: return None
        if LABEL_AT.match(m, i) and first: return None
        j = m.find(";", i)
        if j < 0: return None
        body = m[i:j]
        if "{" in body or "}" in body or "\n#" in body: return None
        # declaration-looking statement (`s32 x;`) is not a simple statement
        if DECL.match(m[i:j + 1]) and first not in ("return",) and not re.match(r"\w+[ \t]*=", m[i:j]): return None
        stmts.append(re.sub(r"[ \t]*\n[ \t]*", " ", text[i:j + 1]).strip())
        i = j + 1
        if first == "return":
            return stmts, i
    return None


def decl_map(m):
    """{name: [(open, close)]} blocks that declare name (top level = (-1, len))."""
    bl = blocks(m); out = {}
    for d in DECL.finditer(m):
        if d.group(1) in NOT_TYPE: continue
        names = [d.group(2)]
        end = m.find(";", d.end() - 1)
        if end > 0 and m[d.end() - 1] == ",":
            depth = 0; k = d.end()
            for q in range(d.end(), end):
                c = m[q]
                if c in "([": depth += 1
                elif c in ")]": depth -= 1
                elif c == "," and depth == 0:
                    n = IDENT.match(m, q + 1 + (len(m[q + 1:]) - len(m[q + 1:].lstrip(" \t*"))))
                    if n: names.append(n.group(0))
        inner = [b for b in bl if b[0] < d.start() < b[1]]
        blk = max(inner, key=lambda b: b[0]) if inner else (-1, len(m))
        for n in names: out.setdefault(n, []).append(blk)
    return out


def resolve(dm, name, pos):
    c = [b for b in dm.get(name, []) if b[0] < pos < b[1]]
    return max(c, key=lambda b: b[0]) if c else None


def labels_and_stubs(text, m):
    out = {}
    for lm in LABEL_LINE.finditer(m):
        L = lm.group(1)
        if L in KEYWORDS or L in NOT_TYPE: continue
        out[L] = lm
    return out


def sites(text):
    """[(goto_start, goto_end, label, replacement_stmts or None)]; None = goto to the next statement."""
    m = mask(text)
    if re.search(r"\bgoto[ \t]*\*|[=,({][ \t\n]*&&[ \t]*[A-Za-z_]", m): return []
    pp = pp_depth(text); lbl = labels_and_stubs(text, m); dm = None; out = []
    stubs = {}
    for L, lm in lbl.items():
        if pp[lm.start()]: continue
        st = parse_stub(m, text, lm.end())
        if st and sum(len(s) for s in st[0]) <= MAX_CHARS and not any("ASM_" in s for s in st[0]):
            stubs[L] = (lm.start(), lm.end(), st[0])
    for g in re.finditer(r"\bgoto[ \t]+(\w+)[ \t]*;", m):
        L = g.group(1)
        if L not in lbl or pp[g.start()]: continue
        ls = m.rfind("\n", 0, g.start()) + 1; le = m.find("\n", g.end()); le = len(m) if le < 0 else le
        if m[ls:le].lstrip().startswith("#") or m[ls:le].rstrip().endswith("\\"): continue
        # goto to the next statement: only whitespace / ';' between goto and `L:`
        lm = lbl[L]
        if lm.start() > g.end() and not re.sub(r"[ \t\n;]", "", m[g.end():lm.start()]) and \
                re.search(r"[;{}:]\s*$", m[:g.start()]):
            out.append((g.start(), g.end(), L, None)); continue
        if L in stubs:
            if dm is None: dm = decl_map(m)
            ok = True
            for s in stubs[L][2]:
                for idn in IDENT.findall(re.sub(r"\s+", " ", s)):
                    if idn in dm and resolve(dm, idn, g.start()) != resolve(dm, idn, stubs[L][0]): ok = False
            if ok: out.append((g.start(), g.end(), L, stubs[L][2]))
    return out


def _indent(text, pos):
    ls = text.rfind("\n", 0, pos) + 1
    return re.match(r"[ \t]*", text[ls:]).group(0)


def _replacement(text, m, s, e, stmts):
    if stmts is None: return ""
    pre = m[:s].rstrip()
    unbraced = bool(pre) and (pre[-1] == ")" or re.search(r"\belse$", pre) or re.search(r"\bdo$", pre))
    ind = _indent(text, s)
    alone = not text[text.rfind("\n", 0, s) + 1:s].strip()
    if unbraced:
        return "{\n" + "".join(ind + "    " + x + "\n" for x in stmts) + ind + "}"
    if len(stmts) == 1: return stmts[0]
    sep = "\n" + (ind if alone else ind)
    return stmts[0] + "".join(sep + x for x in stmts[1:])


def rewrite(text, chosen):
    ss = sites(text); m = mask(text); lbl = labels_and_stubs(text, m); t = text
    edits = []
    for i in chosen:
        s, e, L, stmts = ss[i]
        edits.append((s, e, _replacement(text, m, s, e, stmts)))
    for L in {ss[i][2] for i in chosen}:
        total = len(re.findall(r"\bgoto[ \t]+%s[ \t]*;" % re.escape(L), m))
        if total == sum(1 for i in chosen if ss[i][2] == L):
            lm = lbl[L]; s = lm.start(); e = lm.end()
            # remove `L:` (plus trailing blanks); a line holding only the label goes away entirely
            ls = m.rfind("\n", 0, s) + 1; le = m.find("\n", e); le = len(m) if le < 0 else le
            rest = m[e:le].strip()
            if not rest and not m[ls:s].strip(): s, e = ls, min(le + 1, len(text))
            else: s = m.index(L, s) if False else s
            edits.append((s, e, ""))
    for s, e, rep in sorted(edits, key=lambda x: -x[0]):
        t = t[:s] + rep + t[e:]
    return t


class T:
    name = "t136_stubtail"; level = 1
    needs_verify = True

    @staticmethod
    def eligible(text, row, census):
        return None if sites(text) else "no goto into a short return stub"

    @staticmethod
    def apply_verified(text, row, census, vf):
        ss = sites(text)
        if not ss:
            return None, {"refused": ["no goto into a short return stub"]}
        n0, g0 = len(sites_of(text)), gotos(text); budget = [MAX_VERIFY]; tried = []

        def ok(t):
            if t == text or len(sites_of(t)) != n0 or gotos(t) >= g0 or budget[0] <= 0: return False
            budget[0] -= 1; tried.append(1)
            return bool(vf(t).get("exact"))

        allidx = list(range(len(ss)))
        if ok(rewrite(text, allidx)):
            return rewrite(text, allidx), {"gotos": len(ss), "verifies": len(tried)}
        keep = []
        labels = sorted({L for _, _, L, _ in ss}, key=lambda L: -sum(1 for x in ss if x[2] == L))
        if len(labels) > 1:
            for L in labels:
                grp = [i for i, x in enumerate(ss) if x[2] == L]
                if ok(rewrite(text, keep + grp)): keep += grp
        for i in allidx:
            if i not in keep and ok(rewrite(text, keep + [i])): keep.append(i)
        if keep:
            return rewrite(text, keep), {"gotos": len(keep), "of": len(ss), "verifies": len(tried)}
        return None, {"refused": ["no stub-tail rewrite exact (%d verifies)" % len(tried)]}
