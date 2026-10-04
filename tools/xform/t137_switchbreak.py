"""T137: `goto L;` that leaves a switch / loop (or jumps to the next statement) written as `break;` / nothing (readability; pins untouched).

APPEARS     (a) `goto L;` inside a `switch` body (not inside a loop or a nested switch) where `L:` labels the first
                statement after the switch's closing brace;
            (b) `goto L;` inside a loop body (for/while/do-while, not inside a nested switch/loop) where `L:` labels
                the first statement after the loop (an infinite loop `for (;;)` / `while (1)` is tried last: jump.c
                rotates the exit test, r93 80286AF8 dist 161, but 818D4800 / 81978428 were exact);
            (c) `goto L;` (bare, `if (c) goto L;`, `else goto L;`, `else if (c) goto L;`, braced or not) where `L:`
                labels the very next statement.
RESOLVES    (a)/(b) `break;`; (c) the goto (with its if/else wrapper; a condition with side effects stays as `c;`).
            A label no goto targets any more is removed (its statement stays).  Candidates are verified like
            t123/t136: all sites at once, then per label, then per goto greedily (budget T137_MAX, default 16),
            then the rewrite is re-detected (chains `if (a) goto L; if (b) goto L; L:` fall in rounds).  Pins must
            be unchanged and gotos strictly fewer.
SAFETY      refused: rows with computed gotos (`goto *`, `&&label`), sites / labels inside #if regions, statement
            parse failures (the row is skipped).  Pins are never touched.
POPULATION  see the round-93 REPORT of lane r93_sonnet_t137 (census over src/*/*.c).
"""
import os, re, sys
from pathlib import Path
sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
from pin_census import sites_of
try:
    from .t122_gotowhile import mask, gotos, match_close
except ImportError:
    from t122_gotowhile import mask, gotos, match_close

MAX_VERIFY = int(os.environ.get("T137_MAX", "16"))
IDENT = re.compile(r"[A-Za-z_]\w*")
NOT_LABEL = {"case", "default", "return", "goto", "else", "break", "continue", "sizeof", "do", "if", "while",
             "for", "switch"}


def pp_depth(text):
    flag = bytearray(len(text)); d = 0; pos = 0
    for line in text.split("\n"):
        s = line.strip()
        if re.match(r"#\s*if", s): d += 1
        if d > 0:
            for k in range(pos, min(pos + len(line) + 1, len(flag))): flag[k] = 1
        if re.match(r"#\s*endif", s): d = max(0, d - 1)
        pos += len(line) + 1
    return flag


def blank_pp(m):
    """Preprocessor lines blanked (same length) for the statement parser."""
    return re.sub(r"(?m)^[ \t]*#(?:[^\n\\]|\\\n|\\.)*", lambda x: re.sub(r"[^\n]", " ", x.group(0)), m)


class Bail(Exception):
    pass


class Parser:
    def __init__(s, m):
        s.m = m; s.n = len(m); s.gotos = []; s.labels = {}

    def ws(s, i):
        m = s.m
        while i < s.n and m[i] in " \t\r\n": i += 1
        return i

    def word_at(s, i, w):
        return s.m.startswith(w, i) and not (i + len(w) < s.n and (s.m[i + len(w)].isalnum() or s.m[i + len(w)] == "_"))

    def simple_end(s, i):
        m = s.m; d = 0
        while i < s.n:
            c = m[i]
            if c in "([{": d += 1
            elif c in ")]}":
                d -= 1
                if d < 0: raise Bail("unbalanced in simple stmt")
            elif c == ";" and d == 0: return i + 1
            i += 1
        raise Bail("eof in simple stmt")

    def block(s, i, stack):
        """i at '{' -> (index after '}', info)."""
        j = i + 1; infos = []
        while True:
            j = s.ws(j)
            if j >= s.n: raise Bail("eof in block")
            if s.m[j] == "}": break
            j, inf = s.stmt(j, stack, True); infos.append(inf)
        info = None
        if len(infos) == 1 and infos[0] and infos[0][0] == "goto": info = ("goto", infos[0][1])
        return j + 1, info

    def stmt(s, i, stack, safe):
        m = s.m; i = s.ws(i)
        if i >= s.n: raise Bail("eof")
        c = m[i]
        if c == "{": return s.block(i, stack)
        if c == ";": return i + 1, None
        if c == "}": return i, None                       # a label right before '}' (caller sees it)
        mm = IDENT.match(m, i); w = mm.group(0) if mm else ""
        k = s.ws(mm.end()) if mm else i
        if w in ("case", "default"):
            j = i + len(w)
            if w == "case":
                # first ':' not part of '?:' / '::'
                q = 0; j = i + 4
                while j < s.n:
                    if m[j] == "?": q += 1
                    elif m[j] == ":":
                        if q == 0: break
                        q -= 1
                    j += 1
            else:
                j = m.index(":", i)
            return s.stmt_after_label(j + 1, stack, safe)
        if w and w not in NOT_LABEL and k < s.n and m[k] == ":" and m[k + 1:k + 2] != ":":
            s.labels.setdefault(w, []).append((i, k + 1))
            return s.stmt_after_label(k + 1, stack, safe)
        if w == "if":
            if m[k] != "(": raise Bail("if")
            cl = match_close(m, k)
            e, inf = s.stmt(cl + 1, stack, False)
            gid = inf[1] if inf and inf[0] == "goto" else None
            jj = s.ws(e)
            if s.word_at(jj, "else"):
                e2, inf2 = s.stmt(jj + 4, stack, False)
                if inf2 and inf2[0] == "goto":
                    s.gotos[inf2[1]]["wrap"].append(("else", jj, e2, None, True))
                if inf2 and inf2[0] == "wrapif":
                    s.gotos[inf2[1]]["wrap"].append(("elseif", jj, e2, inf2[2], True))
                return e2, None
            if gid is not None:
                s.gotos[gid]["wrap"].append(("if", i, e, (k + 1, cl), safe))
                return e, ("wrapif", gid, (k + 1, cl))
            return e, None
        if w in ("while", "for"):
            if m[k] != "(": raise Bail("loop")
            cl = match_close(m, k)
            inner = re.sub(r"\s+", "", m[k + 1:cl])
            node = {"kind": "loop", "inf": (inner == ";;" if w == "for" else inner in ("1", "(1)"))}
            e, _ = s.stmt(cl + 1, stack + [node], False)
            node["end"] = e
            return e, None
        if w == "do":
            node = {"kind": "loop"}
            e, _ = s.stmt(k, stack + [node], False)
            e = s.ws(e)
            if not s.word_at(e, "while"): raise Bail("do-while")
            p = s.ws(e + 5); cl = match_close(m, p)
            node["inf"] = re.sub(r"\s+", "", m[p + 1:cl]) in ("1", "(1)")
            e = s.ws(cl + 1)
            if m[e] != ";": raise Bail("do-while ;")
            node["end"] = e + 1
            return e + 1, None
        if w == "switch":
            cl = match_close(m, k)
            node = {"kind": "switch"}
            e, _ = s.stmt(cl + 1, stack + [node], False)
            node["end"] = e
            return e, None
        if w == "else":
            raise Bail("stray else")
        if w == "goto":
            g = re.compile(r"goto[ \t\n]+(\w+)[ \t\n]*;").match(m, i)
            if not g: raise Bail("computed goto")
            rec = {"gs": i, "ge": g.end(), "L": g.group(1), "node": stack[-1] if stack else None, "wrap": []}
            if safe: rec["wrap"].append(("bare", i, g.end(), None, True))
            s.gotos.append(rec)
            return g.end(), ("goto", len(s.gotos) - 1)
        return s.simple_end(i), None

    def stmt_after_label(s, j, stack, safe):
        j2 = s.ws(j)
        if j2 < s.n and s.m[j2] == "}": return j2, None
        e, _inf = s.stmt(j, stack, safe)
        return e, None

    def function(s, i):
        return s.block(i, [])[0]


def parse(text):
    """-> (Parser, masked) or None when the text does not parse cleanly."""
    m = blank_pp(mask(text))
    p = Parser(m); i = 0; d = 0
    try:
        while i < len(m):
            c = m[i]
            if c == "{" and d == 0:
                pre = m[:i].rstrip()
                if pre and pre[-1] in ");":
                    i = p.function(i); continue
                d += 1
            elif c == "{": d += 1
            elif c == "}": d -= 1
            i += 1
    except (Bail, IndexError, ValueError):
        return None
    return p, m


def follows(m, i, L):
    """Is the next statement after index i labelled L (only whitespace / ';' / other labels between)?"""
    n = len(m)
    while True:
        while i < n and m[i] in " \t\r\n;": i += 1
        mm = re.compile(r"([A-Za-z_]\w*)[ \t\n]*:(?!:)").match(m, i)
        if not mm or mm.group(1) in NOT_LABEL: return False
        if mm.group(1) == L: return True
        i = mm.end()


SIDE = re.compile(r"\w\s*\(|\+\+|--|(?<![=<>!])=(?!=)")


def sites(text):
    """[dict(gs, ge, L, shape, edit=(s, e, repl))]  shape in {'c', 'a', 'b', 'binf'}."""
    pr = parse(text)
    if pr is None: return []
    p, m = pr
    if re.search(r"\bgoto[ \t]*\*|[=,({][ \t\n]*&&[ \t]*[A-Za-z_]", m): return []
    pp = pp_depth(text); out = []
    for r in p.gotos:
        L = r["L"]
        defs = p.labels.get(L, [])
        if len(defs) != 1 or pp[r["gs"]] or pp[defs[0][0]]: continue
        ls = m.rfind("\n", 0, r["gs"]) + 1
        if m[ls:r["gs"]].lstrip().startswith("#"): continue
        site = None
        for kind, s, e, cond, safe in r["wrap"]:
            if not safe or not follows(m, e, L) or pp[s]: continue
            if kind == "if":
                c = text[cond[0]:cond[1]].strip()
                repl = "" if not SIDE.search(re.sub(r"\s+", " ", c)) else re.sub(r"\s*\n\s*", " ", c) + ";"
                site = ("c", (s, e, repl))
            elif kind == "elseif":
                c = text[cond[0]:cond[1]].strip()
                site = ("c", (s, e, ""))      # `else if (c) goto L; L:` - condition side effects: refuse
                if SIDE.search(re.sub(r"\s+", " ", c)): site = None; continue
            else:
                site = ("c", (s, e, ""))
            break
        if site is None:
            nd = r["node"]
            if nd is not None and follows(m, nd["end"], L):
                shape = "a" if nd["kind"] == "switch" else ("binf" if nd.get("inf") else "b")
                site = (shape, (r["gs"], r["ge"], "break;"))
        if site is None: continue
        out.append({"gs": r["gs"], "ge": r["ge"], "L": L, "shape": site[0], "edit": site[1]})
    return out


def rewrite(text, chosen_sites, all_sites):
    """chosen_sites: indices into all_sites."""
    pr = parse(text); p, m = pr; t = text; edits = []
    for i in chosen_sites:
        s, e, rep = all_sites[i]["edit"]
        if rep == "":
            # a line holding only the removed span goes away entirely; else trim blanks before the span
            ls = m.rfind("\n", 0, s) + 1; le = m.find("\n", e); le = len(m) if le < 0 else le
            if not text[ls:s].strip() and not text[e:le].strip(): s, e = ls, min(le + 1, len(text))
            else:
                while s > 0 and text[s - 1] in " \t": s -= 1
                if not text[e:le].strip(): pass
                elif text[s:s + 0] == "" and s > 0 and text[s - 1] not in "\n": rep = " " if False else ""
        edits.append((s, e, rep))
    chosen_L = {all_sites[i]["L"] for i in chosen_sites}
    for L in chosen_L:
        total = len(re.findall(r"\bgoto[ \t\n]+%s[ \t\n]*;" % re.escape(L), m))
        if total == sum(1 for i in chosen_sites if all_sites[i]["L"] == L):
            ls0, le0 = p.labels[L][0]
            ls = m.rfind("\n", 0, ls0) + 1; lend = m.find("\n", le0); lend = len(m) if lend < 0 else lend
            if not m[ls:ls0].strip() and not m[le0:lend].strip(): s, e = ls, min(lend + 1, len(text))
            else:
                s, e = ls0, le0
                while e < len(text) and text[e] in " \t": e += 1
            edits.append((s, e, ""))
    edits.sort(key=lambda x: -x[0])
    for a, b, rep in edits:
        t = t[:a] + rep + t[b:]
    return t


class T:
    name = "t137_switchbreak"; level = 1
    needs_verify = True

    @staticmethod
    def eligible(text, row, census):
        return None if sites(text) else "no goto leaving a switch/loop or to the next statement"

    @staticmethod
    def apply_verified(text, row, census, vf):
        if not sites(text):
            return None, {"refused": ["no goto leaving a switch/loop or to the next statement"]}
        n0, G0 = len(sites_of(text)), gotos(text); budget = [MAX_VERIFY]; tried = []
        cur = text; done = 0

        def ok(base, t):
            if t == base or len(sites_of(t)) != n0 or gotos(t) >= gotos(base) or budget[0] <= 0: return False
            budget[0] -= 1; tried.append(1)
            return bool(vf(t).get("exact"))

        for _round in range(4):
            ss = sites(cur)
            if not ss or budget[0] <= 0: break
            base = cur; keep = []
            noinf = [i for i, x in enumerate(ss) if x["shape"] != "binf"]
            inf = [i for i, x in enumerate(ss) if x["shape"] == "binf"]
            if noinf and ok(base, rewrite(base, noinf, ss)): keep = list(noinf)
            else:
                labels = sorted({ss[i]["L"] for i in noinf}, key=lambda L: -sum(1 for i in noinf if ss[i]["L"] == L))
                if len(labels) > 1:
                    for L in labels:
                        grp = [i for i in noinf if ss[i]["L"] == L]
                        if ok(base, rewrite(base, keep + grp, ss)): keep += grp
                for i in noinf:
                    if i not in keep and ok(base, rewrite(base, keep + [i], ss)): keep.append(i)
            for i in inf:                                  # infinite loops last
                if ok(base, rewrite(base, keep + [i], ss)): keep.append(i)
            if not keep: break
            cur = rewrite(base, keep, ss); done += len(keep)
        if cur != text and gotos(cur) < G0:
            return cur, {"gotos": G0 - gotos(cur), "verifies": len(tried)}
        return None, {"refused": ["no break/next-statement rewrite exact (%d verifies)" % len(tried)]}
