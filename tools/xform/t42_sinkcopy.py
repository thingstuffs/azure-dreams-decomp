"""T42: a pinned copy of a parameter, assigned in the block that uses it.

APPEARS     `saved = param;` (or `T saved = param;`) near the function top, with pins on `saved`,
            while every other use of `saved` lies inside one later block.
RESOLVES    argconst luna lane, 2026-09-12. In town/func_800BEE14, `saved_angle = angle` moved into
            the successful-effect branch and its ASM_KEEP went (the ASM_REG stayed). In
            dungeon/func_8028C354 the same happened for `saved_render_param`. The shorter live range
            reproduces retail's placement of the argument constants before the allocation call; the
            pin had emulated it.
RESULT      first sweep (2026-09-12): 125 of 1,468 pinned rows have a sinkable copy; 9 rows exact, each
            with the copy assigned exactly once. The unit test reproduced dungeon/func_8028C354; for
            town/func_800BEE14 the lane had chosen another branch, and the lane's candidate landed.
Candidates: the assignment moved to the start of the innermost block holding every use (after that
block's declarations), with the copy's keep pins erased, then each single pin of the copy, then all
of them. Safe only when the parameter is never written and the copy has no other assignment; both
are required. switch bodies are skipped.
"""
import re, sys
from pathlib import Path
sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
from pin_census import sites_of, unscored_text
from pin_sites import erase_many
try:
    from .t29_addrsym import mask_comments
    from .t36_paramwidth import functions
except ImportError:
    from t29_addrsym import mask_comments
    from t36_paramwidth import functions

MAX_CANDS = 30
KEYWORDS = {"if", "for", "while", "do", "return", "goto", "switch", "case", "default", "break",
            "continue", "else"}
DECL_LINE = re.compile(r"^[ \t]*(?:(?:register|const|volatile|static)[ \t]+)*([A-Za-z_]\w*)[ \t\*]+[A-Za-z_]\w*"
                       r"[ \t]*(?:\[[^\]]*\][ \t]*)?(?:ASM_REG\([^()]*\)[ \t]*)?(?:=[^;]*)?;[^\n]*\n")
CAST = r"(?:\(\s*[A-Za-z_][\w\s\*]*\)\s*)?"


def written(m, name, a, b, skip=()):
    """Does the masked span [a, b) write `name` outside the spans in `skip`?"""
    N = re.escape(name)
    for w in re.finditer(r"(?<![\w.>])%s\s*(?:[-+*/%%&|^]|<<|>>)?=(?!=)|(?:\+\+|--)\s*%s\b|\b%s\s*(?:\+\+|--)|&\s*%s\b"
                         % (N, N, N, N), m[a:b]):
        p = a + w.start()
        if not any(s <= p < e for s, e in skip):
            return True
    return False


def sinkable(text):
    """(v, param, cast, def_span, def_is_decl, block_open, insert_at, indent) per candidate copy."""
    m, sites, out = mask_comments(text), sites_of(text), []
    for fname, params, b0, b1 in functions(text):
        pnames = {p for p, _, _, _ in params}
        pinned = set()
        for s in sites:
            if b0 < s[3] < b1:
                pinned.update(re.findall(r"\b([A-Za-z_]\w*)\b", text[s[3]:s[4]]))
        for v in sorted(pinned - pnames):
            V = re.escape(v)
            st = [x for x in re.finditer(r"^[ \t]*%s\s*=\s*(%s)(\w+)\s*;[^\n]*\n" % (V, CAST), m[b0:b1], re.M)]
            dc = [x for x in re.finditer(r"^[ \t]*(?:register[ \t]+)?[A-Za-z_][\w \t\*]*?\b%s\b[ \t]*"
                                         r"(?:ASM_REG\([^()]*\)[ \t]*)?(=\s*(%s)(\w+))\s*;" % (V, CAST), m[b0:b1], re.M)]
            defs = [(b0 + x.start(), b0 + x.end(), x.group(1), x.group(2), False) for x in st if x.group(2) in pnames] + \
                   [(b0 + x.start(1), b0 + x.end(1), x.group(2), x.group(3), True) for x in dc if x.group(3) in pnames]
            if len(defs) != 1:
                continue
            da, db, cast, p, is_decl = defs[0]
            if written(m, p, b0, b1) or written(m, v, b0, b1, skip=[(da, db)]):
                continue
            pin_spans = [(s[3], s[4]) for s in sites if b0 < s[3] < b1]
            uses = [u.start() + b0 for u in re.finditer(r"\b%s\b" % V, m[b0:b1])
                    if not (da <= u.start() + b0 < db) and not any(s <= u.start() + b0 < e for s, e in pin_spans)]
            decl = re.search(r"^[ \t]*(?:register[ \t]+)?[A-Za-z_][\w \t\*]*?\b%s\b" % V, m[b0:b1], re.M)
            if decl:
                uses = [u for u in uses if not (b0 + decl.start() <= u < b0 + decl.end())]
            if not uses or any(u < da for u in uses):
                continue                                          # no use, or the copy is read before it is set
            best = None                                          # the innermost brace block holding every use
            stack = []
            for i in range(b0 + 1, b1):
                if m[i] == "{":
                    stack.append(i)
                elif m[i] == "}" and stack:
                    o = stack.pop()
                    if o > db and o < min(uses) and i > max(uses) and (best is None or o > best[0]):
                        best = (o, i)
            if best is None or re.search(r"switch\s*\([^{}]*\)\s*$", m[b0:best[0]]):
                continue
            ins = best[0] + 1
            nl = m.find("\n", ins)
            ins = nl + 1 if nl >= 0 and not m[ins:nl].strip() else ins
            while True:                                          # past the block's declarations (C89)
                dm = DECL_LINE.match(m, ins)
                if not dm or dm.group(1) in KEYWORDS:
                    break
                ins = dm.end()
            ind = re.match(r"[ \t]*", text[ins:]).group(0) or "    "
            out.append((v, p, cast.strip(), (da, db), is_decl, best[0], ins, ind))
    return out


def moved(text, c):
    v, p, cast, (da, db), is_decl, _, ins, ind = c
    line = "%s%s = %s%s;\n" % (ind, v, cast, p)
    t = text[:ins] + line + text[ins:]                            # ins lies after the definition
    return t[:da] + ("" if is_decl else "") + t[db:] if not is_decl else t[:da] + t[db:]


def candidates(text):
    out, seen = [], set()
    for c in sinkable(text):
        t1 = moved(text, c)
        V = re.escape(c[0])
        ss = sites_of(t1)
        own = [s for s in ss if re.search(r"\b%s\b" % V, t1[s[3]:s[4]])]
        keeps = [s for s in own if s[1] != "ASM_REG"]
        sets = ([keeps] if keeps else []) + [[s] for s in own] + ([own] if len(own) > 1 else [])
        for chosen in sets:
            t = erase_many(t1, chosen, clean_notes=True)
            if t not in seen and unscored_text(t) == unscored_text(text):
                seen.add(t); out.append(("sinkcopy:%s:%s" % (c[0], "+".join(s[1] for s in chosen)), t))
        if len(out) >= MAX_CANDS:
            break
    return out[:MAX_CANDS]


class T:
    name = "t42_sinkcopy"; level = 1
    needs_verify = True

    @staticmethod
    def eligible(text, row, census):
        if not sites_of(text):
            return "no pin sites"
        if not sinkable(text):
            return "no pinned parameter copy used only inside one later block"
        return None

    @staticmethod
    def apply_verified(text, row, census, vf):
        n0 = len(sites_of(text))
        cands = [c for c in candidates(text) if len(sites_of(c[1])) < n0]
        if not cands:
            return None, {"refused": ["no buildable candidate"]}
        for label, t in cands:
            if vf(t).get("exact"):
                return t, {"label": label}
        return None, {"refused": ["no candidate exact at the recorded cell"]}
