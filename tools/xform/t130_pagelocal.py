"""T130: page fold with a BLOCK-LOCAL symbol - the staged integer page whose uses sit in one basic block.

APPEARS     a staged integer page (a literal 0x8XXX0000, then pins, then a byte-offset bias step)

                V = (u8 *)0x80170000;  ASM_KEEP(V);  V += 0x4E44;   (or  V = 0x80170000; ...; V += 0x5E88;)

            whose value is consumed in ONE block: from the bias step to the block's terminal statement
            (`return`, `break`, the closing brace, or a `goto L`), with no label in between.

RESOLVES    r80_opus_cl_ori (2026-09-29): at a splitting cell movsi emits (set TEM (high SYM)) into a fresh
            pseudo and (set DEST (lo_sum TEM SYM)); local-alloc combine_regs ties TEM to DEST, which gives
            retail's `lui R; addiu R,R,lo` (ONE register), only when DEST is a pseudo referenced in a single
            basic block.  A symbol substituted into the FUNCTION-SCOPE variable the integer lived in
            (t29 / t54 / t92 / t97) can never tie: `lui $2; addiu $5,$2`.  So the symbol has to be written
            where the value is USED:

              (a) every use in one block: the uses become the typed symbol directly
                      PTR(s, 0x2C) = D_80175E88;   p = &D_80175E88[idx];
                  and the page set, its keeps and the bias step go (and V's declaration once unused);
              (b) the block ends in `goto L` into a shared tail: the tail is written out IN PLACE with the
                  symbol used directly (up to MAX_TAIL_LINES lines, the NON_MATCHING arm of any #ifdef
                  dropped, an explicit `return;` when the tail runs to the end of the function), and jump2
                  cross-jumps it back into retail's `lui $5; j L; addiu $5,$5,lo`.  The original tail stays for
                  the paths that still reach the label; the label goes only when no goto to it is left.

            Fixtures: dungeon/func_80AC5F28 (rule b), dungeon/func_809A1A8C and func_812A85D4 (rule a).

CANDIDATES  per staged run: the block-local spellings `fold` (`(E + V)` -> `&SYM[E]` when the file declares
            the symbol a byte array) and `plain` (V -> SYM), and for a goto tail also the copy WITH and
            WITHOUT the pin statements the tail carries.  Each is checked (unscored arm unchanged, pins strictly
            fewer) and put to the byte verifier; the first exact wins, then the row is re-scanned for the next
            run.  Refuses rather than guesses: a label between the step and the block end, V assigned again in
            the block, a keep naming V next to other arguments, a tail with an inner goto, an unbalanced tail.
"""
import re, sys
from pathlib import Path

_HERE = Path(__file__).resolve()
for _cand in (_HERE.parents[1],):
    if (_cand / "pin_census.py").exists():
        sys.path.insert(0, str(_cand))
        break
from pin_census import sites_of, asm_blocker, unscored_text
from pin_sites import erase_many
import xform.t29_addrsym as A
import xform.t92_pagerun as t92
from xform.t36_paramwidth import functions

MAX_VERIFY = 12
MAX_TAIL_LINES = 20
MAX_SEED_CHUNKS = 24
NUM = t92.NUM
mask_comments = A.mask_comments

MACRO_SEED_RE = re.compile(r"(?:^|[;{}:])(?P<lead>[ \t\n]*(?:%s)?)\(?(?P<v>[A-Za-z_]\w*)\)?[ \t]*=[ \t]*"
                           r"(?P<rhs>(?:\([^()]*\)[ \t]*)*[A-Z_][A-Z0-9_]*[ \t]*\([^;]*\))[ \t]*;" % t92.TYPE, re.M)
PP_LINE = re.compile(r"(?:[ \t]*#[^\n]*\n|[ \t\n])*")
PIN_STMT = re.compile(r"[ \t\n]*ASM_[A-Z0-9_]+[ \t]*\((?P<args>[^;]*)\)[ \t]*;[ \t]*\Z")
PIN_ANY = re.compile(r"\bASM_[A-Z0-9_]+[ \t]*\([^;]*\)[ \t]*;")
LABEL = re.compile(r"(?:(?P<case>(?:case\b[^:;{}]*|default))[ \t\n]*:|(?P<lab>(?!(?:case|default)\b)[A-Za-z_]\w*)[ \t]*:(?!:))")
TERMINAL = re.compile(r"(?P<kw>return|break|continue|goto)\b[ \t]*(?P<lab>[A-Za-z_]\w*)?")
STEP_ASSIGN = r"(?<![.>\w])\b%s\b[ \t]*(?:=(?!=)|\+\+|--|[-+*/|&^%%]=|<<=|>>=)"
PLAIN_ASSIGN = r"(?<![.>\w])\b%s\b[ \t]*=(?!=)"
MENTION = r"(?<![.>\w])\b%s\b"


# ------------------------------------------------------------------ text helpers
def _split(masked, a, b):
    """(body start, body end) of a chunk without its leading preprocessor lines / blanks."""
    m = PP_LINE.match(masked, a, b)
    return m.end(), b


def _labelled(body):
    """The label a chunk body starts with ('case' for case/default), else None."""
    m = LABEL.match(body)
    if not m:
        return None
    return "case" if m.group("case") else m.group("lab")


def _inner_label(body):
    """A label (not case/default) at the start of any line of `body`."""
    for m in re.finditer(r"(?m)^[ \t]*(?P<w>[A-Za-z_]\w*)[ \t]*:(?!:)", body):
        if m.group("w") not in ("case", "default"):
            return True
    return False


def _blank_pins(s):
    return PIN_ANY.sub(lambda m: " " * len(m.group(0)), s)


def _fn_of(text, pos):
    return next(((x, y) for _f, _p, x, y in functions(text) if x <= pos < y), None)


def _line_span(text, a, b):
    """[a,b) widened over the whole line(s) when only blanks share them."""
    ls = text.rfind("\n", 0, a) + 1
    if not text[ls:a].strip():
        a = ls
    le = text.find("\n", b)
    le = len(text) if le < 0 else le
    if not text[b:le].strip():
        b = min(len(text), le + 1)
    return a, b


def _brace_split(s):
    """Top-level '+' terms of `s` (parenthesis aware)."""
    out, depth, cur = [], 0, ""
    for ch in s:
        if ch in "([":
            depth += 1
        elif ch in ")]":
            depth -= 1
        if ch == "+" and depth == 0:
            out.append(cur)
            cur = ""
        else:
            cur += ch
    out.append(cur)
    return out



def _stmts(masked, start, stop):
    """Statement spans [(a, b, chunk)] from `start`: split on a top-level `;`, and after a `}` that closes a
    compound statement (unless `else` follows).  Returns (spans, 'end' | 'brace') where 'brace' means an
    unmatched `}` was met at masked[spans[-1][1]] (the closing brace of the enclosing block)."""
    out, depth, a, i = [], 0, start, start
    while i < stop:
        c = masked[i]
        if c in "([{":
            depth += 1
        elif c in ")]}":
            depth -= 1
            if depth < 0:
                out.append((a, i, masked[a:i]))
                return out, "brace"
            if c == "}" and depth == 0:
                nxt = re.match(r"\s*(?:#[^\n]*\n\s*)*else\b", masked[i + 1:i + 200])
                if not nxt:
                    out.append((a, i + 1, masked[a:i + 1]))
                    a = i + 1
        elif c == ";" and depth == 0:
            nxt = re.match(r"\s*(?:#[^\n]*\n\s*)*else\b", masked[i + 1:i + 200])
            if not nxt:
                out.append((a, i + 1, masked[a:i + 1]))
                a = i + 1
        i += 1
    return out, "end"


# ------------------------------------------------------------------ finding the staged runs
def runs(text):
    """[{v, addr, page, ty, ptr, seed:(a,b), steps:[(a,b)], rs, fn}] - `V = page; pins; ...; V += K;`."""
    masked = mask_comments(text)
    fns = [(x, y) for _f, _p, x, y in functions(text)]
    out = []
    macros = {mm.group(1): int(mm.group(2), 16) for mm in re.finditer(
        r"(?m)^[ \t]*#[ \t]*define[ \t]+([A-Z_]\w*)\([^)]*\)[ \t]+\(?(0x8[0-9A-Fa-f]{3}0000)[UuLl]*\)?[ \t]*$", masked)}
    seeds = list(t92.SEED_RE.finditer(masked))
    if macros:
        seeds += list(MACRO_SEED_RE.finditer(masked))
    for m in sorted(seeds, key=lambda x: x.start()):
        v = m.group("v")
        if v in t92.KEYWORDS:
            continue
        if m.group("lead").strip():
            continue                                        # a declaration with an initialiser
        lit = re.fullmatch(r"\(?\s*(?:%s)*0x(8[0-9A-Fa-f]{3}0000)[Uu]?[Ll]?\s*\)?" % A.CAST, m.group("rhs").strip())
        if lit:
            page = int(lit.group(1), 16)
        else:
            mc = re.match(r"(?:\([^()]*\)\s*)*([A-Z_]\w*)\s*\(", m.group("rhs").strip())
            if not mc or mc.group(1) not in macros:
                continue
            page = macros[mc.group(1)]
        fn = next(((x, y) for x, y in fns if x <= m.start() < y), None)
        if fn is None:
            continue
        decls = A.decls_of(masked[fn[0]:fn[1]], v)
        tys = {(t, p) for t, p, _ in decls}
        if len(tys) != 1:
            continue
        ty, ptr = next(iter(tys))
        cs, _ = _stmts(masked, m.end(), fn[1])
        addr, steps, seen = page, [], 0
        seed_stmt = (m.start("v"), m.end())
        bad = False
        for a, b, chunk in cs:
            if seen >= MAX_SEED_CHUNKS:
                break
            ba, bb = _split(masked, a, b)
            body = masked[ba:bb]
            if not body.strip():
                continue
            seen += 1
            if _labelled(body) or _inner_label(body):
                break
            if ("{" in body or "}" in body) and not PIN_STMT.match(body):
                if re.search(MENTION % re.escape(v), body):
                    break                                   # V used inside a compound statement: not a run
                continue
            if PIN_STMT.match(body):
                if re.search(MENTION % re.escape(v), body) and "," in PIN_STMT.match(body).group("args"):
                    bad = True
                    break
                continue
            d = t92._step(body, v, ty, ptr)
            if d is not None:
                addr = (addr + d) & 0xFFFFFFFF
                steps.append((ba, bb))
                continue
            if re.search(MENTION % re.escape(v), body):
                break                                       # V read: the run is over
        if bad or not steps or addr == page or not (0x80000000 <= addr <= 0x81FFFFFF):
            continue
        out.append({"v": v, "addr": addr, "page": page, "ty": ty, "ptr": ptr, "seed": seed_stmt,
                    "steps": steps, "rs": steps[-1][1], "fn": fn})
    return out


def region(masked, rs, fn_end):
    """Where the block that consumes the staged value ends.

    -> {end, kind ('return'|'break'|'continue'|'goto'|'brace'|'label'|'fnend'), label, stmt:(a,b)|None}"""
    cs, why = _stmts(masked, rs, fn_end)
    for a, b, chunk in cs:
        ba, bb = _split(masked, a, b)
        body = masked[ba:bb]
        if _labelled(body) or _inner_label(body):
            return {"end": ba, "kind": "label", "label": None, "stmt": None}
        t = TERMINAL.match(body)
        if t:
            return {"end": bb, "kind": t.group("kw"), "label": t.group("lab"), "stmt": (ba, bb)}
    if why == "brace" and cs:
        return {"end": cs[-1][1], "kind": "brace", "label": None, "stmt": None}
    return {"end": fn_end, "kind": "fnend", "label": None, "stmt": None}


# ------------------------------------------------------------------ the symbol spellings
class Speller:
    def __init__(self, text, addr, v_ty, v_ptr):
        self.text, self.addr, self.ty, self.ptr = text, addr, v_ty, v_ptr
        self.ext = set()
        self.name = "D_%08X" % addr
        d = A.sym_decl(text, self.name)
        self.elem, self.arr = d if d else ("u8", True)
        self.base = A.sym_expr(text, addr, None, self.ext)
        self.byte_array = self.arr and A.ELEMSIZE.get(self.elem) == 1

    def plain(self, castprefix):
        if castprefix:
            return self.base
        if self.ptr:
            return A.sym_expr(self.text, self.addr, "%s %s" % (self.ty, "*" * self.ptr), self.ext)
        return "(%s)%s" % (self.ty, self.base)

    def fold(self, e):
        return "&%s[%s]" % (self.name, e.strip())


def _mention_edits(masked, text, lo, hi, v, sp, mode):
    """Edits replacing every non-pin mention of V in masked[lo:hi]; None = not expressible."""
    work = _blank_pins(masked[lo:hi])
    rx = re.compile(MENTION % re.escape(v))
    edits, covered = [], -1
    ms = [lo + m.start() for m in rx.finditer(work)]
    for p in ms:
        if p < covered:
            continue
        if mode == "fold" and sp.byte_array:
            g = _fold_group(masked, lo, hi, p, v)
            if g is not None:
                g0, g1, e = g
                edits.append((g0, g1, sp.fold(e)))
                covered = g1
                continue
        pre = masked[max(lo, p - 40):p]
        cast = re.search(r"\(\s*(?:const\s+|volatile\s+|unsigned\s+|signed\s+)*[A-Za-z_]\w*(?:\s+long)?\s*\**\s*\)\s*\Z", pre)
        edits.append((p, p + len(v), sp.plain(bool(cast))))
        covered = p + len(v)
    return edits


def _fold_group(masked, lo, hi, p, v):
    """The parenthesised sum `( E + [cast]V )` around the mention at `p`: (start, end, E) or None."""
    q, start = p, p
    m = re.search(r"\(\s*(?:const\s+|volatile\s+|unsigned\s+|signed\s+)*[A-Za-z_]\w*(?:\s+long)?\s*\**\s*\)\s*\Z",
                  masked[lo:p])
    if m:
        start = lo + m.start()                              # `(u32)V` counts as the term
    depth, i = 0, start - 1
    while i >= lo:
        c = masked[i]
        if c == ")":
            depth += 1
        elif c == "(":
            if depth == 0:
                break
            depth -= 1
        i -= 1
    if i < lo:
        return None
    j, depth = i + 1, 0
    while j < hi:
        c = masked[j]
        if c == "(":
            depth += 1
        elif c == ")":
            if depth == 0:
                break
            depth -= 1
        j += 1
    if j >= hi:
        return None
    inner = masked[i + 1:j]
    terms = _brace_split(inner)
    vt = [k for k, t in enumerate(terms) if re.fullmatch(r"\s*(?:\([^()]*\)\s*)?%s\s*" % re.escape(v), t)]
    if len(terms) < 2 or len(vt) != 1 or len(re.findall(MENTION % re.escape(v), inner)) != 1:
        return None
    rest = [t for k, t in enumerate(terms) if k != vt[0]]
    e = "+".join(rest).strip()
    if not e or re.search(r"\?|[<>=!]=?|&&|\|\|", e.replace("->", "")) and not e.startswith("("):
        return None
    # the group's own leading cast (`(u8 *)(E + V)`) stays; only the parentheses are consumed
    return i, j + 1, e


# ------------------------------------------------------------------ tail copy for rule (b)
def _resolve_pp(s):
    """`s` with each `#ifdef NON_MATCHING ... #else A #endif` reduced to A (the scored arm)."""
    out, stack, live = [], [], True
    for line in s.splitlines(True):
        t = line.strip()
        if re.match(r"#\s*ifdef\s+NON_MATCHING\b", t):
            stack.append("nm"); live = False; continue
        if re.match(r"#\s*ifndef\s+NON_MATCHING\b", t):
            stack.append("nnm"); live = True; continue
        if t.startswith("#") and re.match(r"#\s*(if|ifdef|ifndef)\b", t):
            return None                                    # some other conditional: not understood
        if re.match(r"#\s*else\b", t) and stack:
            live = (stack[-1] == "nm")
            stack[-1] = "else"; continue
        if re.match(r"#\s*endif\b", t) and stack:
            stack.pop(); live = True; continue
        if live:
            out.append(line)
    if stack:
        return None
    return "".join(out)


def tail_copy(text, masked, label, fn, v, sp, mode, keep_pins):
    """(copy text, mentions) for the block that follows `label:`, or None."""
    lm = re.search(r"(?m)^[ \t]*%s[ \t]*:(?!:)" % re.escape(label), masked[fn[0]:fn[1]])
    if not lm:
        return None
    start = fn[0] + lm.end()
    cs, why = _stmts(masked, start, fn[1])
    end, need_return = None, False
    for a, b, chunk in cs:
        ba, bb = _split(masked, a, b)
        body = masked[ba:bb]
        while True:
            lab = _labelled(body)
            if not lab or lab == "case":
                break
            body = body[LABEL.match(body).end():]
        if _labelled(body):
            return None                                     # a case label in the tail
        t = TERMINAL.match(body)
        if t:
            if t.group("kw") not in ("return", "break"):
                return None                                 # goto/continue inside the tail: refuse
            end = bb
            break
    if end is None:
        if why == "end" and cs and not masked[cs[-1][1]:fn[1]].strip():
            end = fn[1]                                     # the tail runs to the function's closing brace
            need_return = True
        else:
            return None
    # an `}` inside the tail that closes a block opened before it means the label sits in a nested scope
    seg_m = masked[start:end]
    depth = 0
    for ch in seg_m:
        depth += (ch == "{") - (ch == "}")
        if depth < 0:
            return None
    if depth != 0:
        return None
    raw = text[start:end]
    raw = _resolve_pp(raw)
    if raw is None:
        return None
    # strip a leading label line that remained, inner labels, and (optionally) pin statements
    raw = re.sub(r"(?m)^[ \t]*(?!case\b|default\b)[A-Za-z_]\w*[ \t]*:(?!:)[ \t]*(?:/\*.*?\*/)?[ \t]*\n?", "", raw)
    if not keep_pins:
        raw = re.sub(r"(?m)^[ \t]*ASM_[A-Z0-9_]+[ \t]*\([^;]*\)[ \t]*;[^\n]*\n?", "", raw)
    raw = raw.strip("\n")
    if need_return:
        raw += "\nreturn;"
    lines = [l for l in raw.split("\n")]
    if len([l for l in lines if l.strip()]) > MAX_TAIL_LINES:
        return None
    return raw


def _dedent(raw, indent):
    lines = raw.split("\n")
    ind = next((len(l) - len(l.lstrip()) for l in lines if l.strip()), 0)
    return "\n".join((indent + l[min(ind, len(l) - len(l.lstrip())):]) if l.strip() else "" for l in lines).lstrip()


def _copy_with_symbol(raw, v, sp, mode):
    """Mentions of V in the copy replaced (the copy is comment-free enough to mask again)."""
    m2 = mask_comments(raw)
    edits = _mention_edits(m2, raw, 0, len(raw), v, sp, mode)
    if not edits:
        return None
    for a, b, rep in sorted(edits, reverse=True):
        raw = raw[:a] + rep + raw[b:]
    return raw



# ------------------------------------------------------------------ companions of the fold (post-passes on a candidate)
KNOWN_MEMBERS = {                       # address -> (C type, member spelling, header the file must include)
    0x80083228: ("s16", "gameWork.view.viewAngle", "shared/game_work.h"),
}


def post_inline(t, sym):
    """`T = X; T &= 7; ... &SYM[T]` -> `&SYM[((X) & 7)]` when T is a temp read only there (r80_opus_cl_ori)."""
    m = re.search(r"&%s\[(?P<t>[A-Za-z_]\w*)\]" % re.escape(sym), t)
    if not m:
        return None
    var = m.group("t")
    lines_before = t[:m.start()].split("\n")[:-1]
    ops, first, cut = [], None, None
    for k in range(len(lines_before) - 1, max(-1, len(lines_before) - 6), -1):
        ln = lines_before[k].strip()
        a = re.fullmatch(r"%s\s*(?P<op>[&|^+-])=\s*(?P<k>[^;=]+);" % re.escape(var), ln)
        b = re.fullmatch(r"%s\s*=\s*(?P<x>[^;]+);" % re.escape(var), ln)
        if a:
            ops.insert(0, (a.group("op"), a.group("k").strip()))
        elif b:
            first, cut = b.group("x").strip(), k
            break
        elif ln:
            if re.search(MENTION % re.escape(var), ln):
                return None
            # an unrelated statement between the temp's steps: keep going only across simple ones
            continue
    if first is None:
        return None
    fn = _fn_of(t, m.start())
    if fn is None:
        return None
    later = mask_comments(t)[m.end():fn[1]]
    nxt = re.search(MENTION % re.escape(var), later)
    if nxt and not re.match(r"[ \t]*=(?!=)", later[nxt.end():]):
        return None
    expr = "(%s)" % first
    for op, k in ops:
        expr = "(%s %s %s)" % (expr, op, k)
    # drop the temp's own statements (lines cut..k that assign it) and use the expression
    keep = []
    for k, ln in enumerate(lines_before):
        if k >= cut and re.match(r"\s*%s\s*(?:[&|^+-]?=)\s*[^;=]+;" % re.escape(var), ln) and \
                not re.search(MENTION % re.escape(var), ln.split("=", 1)[1]):
            if k == cut or re.match(r"\s*%s\s*[&|^+-]=" % re.escape(var), ln):
                continue
        keep.append(ln)
    out = "\n".join(keep) + "\n" + t[t.rfind("\n", 0, m.start()) + 1:m.start()] + "&%s[%s]" % (sym, expr) + t[m.end():]
    return out


def post_page(t, sym=None):
    """`P = (u8 *)D_80080000; ... *(s16 *)(P + 0x3228)` -> the member's own spelling when its address is known."""
    at = t.find("&%s[" % sym) if sym else -1
    hits = list(re.finditer(r"(?m)^(?P<ind>[ \t]*)(?P<p>[A-Za-z_]\w*)[ \t]*=[ \t]*(?:\(\s*u8\s*\*\s*\)\s*)?D_(?P<a>8[0-9A-Fa-f]{3}0000)\s*;[ \t]*\n", t))
    if at >= 0:
        hits = [h for h in hits if h.end() <= at and at - h.end() < 800][-1:]
    for m in hits:
        page = int(m.group("a"), 16)
        pv = m.group("p")
        fn = _fn_of(t, m.start())
        if fn is None:
            continue
        masked = mask_comments(t)
        rest = masked[m.end():fn[1]]
        nxt = re.search(PLAIN_ASSIGN % re.escape(pv), rest)
        scope = rest[:rest.find(";", nxt.start()) + 1] if nxt else rest   # the next set's own right side still reads P
        subs, ok = [], True
        for u in re.finditer(MENTION % re.escape(pv), scope):
            if re.match(r"[ \t]*=(?!=)", scope[u.end():]):
                continue                                    # the next set of P itself
            g = re.match(r"\s*\+\s*(0x[0-9A-Fa-f]+|\d+)\s*\)", scope[u.end():])
            pre = scope[max(0, u.start() - 12):u.start()]
            ty = re.search(r"\*\(\s*(\w+)\s*\*\s*\)\(\s*\Z", pre)
            if not g or not ty:
                ok = False; break
            k = int(g.group(1), 0)
            mem = KNOWN_MEMBERS.get(page + k)
            if not mem or mem[0] != ty.group(1) or ("#include \"%s\"" % mem[2]) not in t:
                ok = False; break
            a0 = m.end() + u.start() - len(ty.group(0))
            subs.append((a0 - 1 if False else m.end() + u.start() - len(ty.group(0)) - 1, m.end() + u.end() + g.end(), mem[1]))
        if not ok or not subs:
            continue
        # `*(s16 *)(` starts one char before the captured lookbehind (the star); rebuild spans exactly
        subs2 = []
        for a, b, rep in subs:
            subs2.append((a + 1, b, rep))
        out = t
        for a, b, rep in sorted(subs2, reverse=True):
            out = out[:a] + rep + out[b:]
        out = out[:m.start()] + out[m.end():]
        return out
    return None


# ------------------------------------------------------------------ candidate construction
def build(text, run, mode, keep_pins=False):
    """New text for one run, or (None, why)."""
    masked = mask_comments(text)
    v, fn = run["v"], run["fn"]
    reg = region(masked, run["rs"], fn[1])
    if reg["kind"] == "label":
        return None, "label between the step and the block end"
    if reg["kind"] == "goto" and not reg["label"]:
        return None, "computed goto"
    end = reg["end"]
    sp = Speller(text, run["addr"], run["ty"], run["ptr"])
    body = masked[run["rs"]:end]
    if re.search(STEP_ASSIGN % re.escape(v), _blank_pins(body)):
        return None, "V assigned again in the block"
    for pm in PIN_ANY.finditer(body):
        if re.search(MENTION % re.escape(v), pm.group(0)) and "," in pm.group(0):
            return None, "keep names V beside other arguments"
    edits = _mention_edits(masked, text, run["rs"], end, v, sp, mode)
    uses = len(edits)
    tail_text = None
    if reg["kind"] == "goto":
        lab = reg["label"]
        lm = re.search(r"(?m)^[ \t]*%s[ \t]*:(?!:)" % re.escape(lab), masked[fn[0]:fn[1]])
        if lm is None:
            return None, "goto target not found"
        tail_reads_v = False
        raw = tail_copy(text, masked, lab, fn, v, sp, mode, keep_pins)
        if raw is not None:
            tail_reads_v = bool(re.search(MENTION % re.escape(v), mask_comments(raw)))
        if tail_reads_v:
            done = _copy_with_symbol(raw, v, sp, mode)
            if done is None:
                return None, "tail copy not expressible"
            tail_text = done
            uses += 1
        else:
            if raw is None:
                # is V read in the shared tail at all?  then the copy failing is a refusal
                seg = masked[fn[0] + lm.end():fn[1]]
                if re.search(MENTION % re.escape(v), seg):
                    later = re.search(PLAIN_ASSIGN % re.escape(v), seg)
                    first = re.search(MENTION % re.escape(v), seg)
                    if not later or first.start() < later.start():
                        return None, "tail unsuitable for an in-place copy"
    else:
        rest = masked[end:fn[1]]
        first = re.search(MENTION % re.escape(v), _blank_pins(rest))
        if first and not re.match(r"[ \t]*=(?!=)", rest[first.end():]):
            return None, "V read after the block before it is set again"
    if uses == 0:
        return None, "no use of V in the block"
    # ---- assemble the edits
    ed = list(edits)
    seed_a, seed_b = run["seed"]
    sa, sb = _line_span(text, seed_a, seed_b)
    ed.append((sa, sb, ""))
    for a, b in run["steps"]:
        ea, eb = _line_span(text, a, b)
        ed.append((ea, eb, ""))
    if tail_text is not None:
        a, b = reg["stmt"]
        ls = text.rfind("\n", 0, a) + 1
        indent = re.match(r"[ \t]*", text[ls:a]).group(0) if not text[ls:a].strip() else ""
        ed.append((a, b, _dedent(tail_text, indent)))
        lab = reg["label"]
        still = [g for g in re.finditer(r"\bgoto[ \t]+%s\s*;" % re.escape(lab), masked[fn[0]:fn[1]])
                 if fn[0] + g.start() != a]
        if not still:
            lm = re.search(r"(?m)^[ \t]*%s[ \t]*:(?!:)[ \t]*\n" % re.escape(lab), masked[fn[0]:fn[1]])
            if lm:
                ed.append((fn[0] + lm.start(), fn[0] + lm.end(), ""))
    # ---- pins that name V inside the run
    sites = sites_of(text)
    drop = [s for s in sites
            if seed_a <= s[3] < (reg["stmt"][1] if reg["stmt"] else end)
            and re.search(MENTION % re.escape(v), mask_comments(text[s[3]:s[4]]))]
    # ---- the declaration goes with its last mention
    dm = A.decls_of(masked[fn[0]:fn[1]], v)
    removed = [(a, b) for a, b, _ in ed] + [(s[3], s[4]) for s in drop]
    left = [m.start() + fn[0] for m in re.finditer(MENTION % re.escape(v), masked[fn[0]:fn[1]])]
    dspans = [(fn[0] + sp_[0], fn[0] + sp_[1]) for _t, _p, sp_ in dm]
    live = [p for p in left if not any(a <= p < b for a, b in removed + dspans)]
    repl = [p for a, b, r in ed for p in [a] if r and re.search(MENTION % re.escape(v), r)]
    if not live and not repl and len(dspans) == 1:
        ed.append((dspans[0][0], dspans[0][1], ""))
    ed = _disjoint(ed)
    if ed is None:
        return None, "overlapping edits"
    t = text
    for a, b, rep in sorted(ed, reverse=True):
        t = t[:a] + rep + t[b:]
    if sp.ext:
        t = t92._externs(t, sp.ext)
    if drop:
        before, after = sites, sites_of(t)
        if len(after) != len(before):
            return None, "an edit changed the pin count"
        order = {s[3]: i for i, s in enumerate(before)}
        moved = [after[order[s[3]]] for s in drop if s[3] in order]
        if len(moved) != len(drop):
            return None, "pin ordinals lost"
        t = erase_many(t, moved, clean_notes=True)
    return re.sub(r"[ \t]+$", "", t, flags=re.M), "%s/%s" % (reg["kind"], mode)


def _disjoint(ed):
    ed = sorted(set(ed))
    for (a1, b1, _r1), (a2, b2, _r2) in zip(ed, ed[1:]):
        if a2 < b1:
            return None
    return ed


def candidates(text):
    """[(label, new_text)] over every staged run; pins must strictly fall."""
    out, seen = [], {text}
    sig, n0 = unscored_text(text), len(sites_of(text))

    def add(label, new):
        if new is None or new in seen:
            return
        if unscored_text(new) != sig or len(sites_of(new)) >= n0:
            return
        seen.add(new)
        out.append((label, new))

    for r in runs(text):
        sym = "D_%08X" % r["addr"]
        for mode in ("fold", "plain"):
            for keep_pins in (False, True):
                new, why = build(text, r, mode, keep_pins)
                lab = "%s@%d:%s%s" % (r["v"], r["seed"][0], why, "+pins" if keep_pins else "")
                add(lab, new)
                if new is not None and mode == "fold" and not keep_pins:
                    inl = post_inline(new, sym)
                    pg = post_page(new, sym)
                    add(lab + "+inline", inl)
                    add(lab + "+page", pg)
                    if inl is not None:
                        add(lab + "+inline+page", post_page(inl, sym))
    return out


class T:
    name = "t130_pagelocal"
    level = 1
    needs_verify = True

    @staticmethod
    def eligible(text, row, census):
        why = asm_blocker(text)
        if why:
            return why
        if not sites_of(text):
            return "no live pin site"
        if not runs(text):
            return "no staged page run"
        return None

    @classmethod
    def apply_verified(cls, text, row, census, vf):
        pins_in = len(sites_of(text))
        info = {"pins_in": pins_in, "pins_out": pins_in, "runs": len(runs(text))}
        cur, steps, verifies, spent = text, [], 0, set()
        while verifies < MAX_VERIFY:
            moved = False
            for label, cand in candidates(cur):
                if cand in spent:
                    continue
                if verifies >= MAX_VERIFY:
                    break
                spent.add(cand)
                verifies += 1
                if vf(cand).get("exact"):
                    cur, moved = cand, True
                    steps.append(label)
                    break
            if not moved:
                break
        info["tried"] = verifies
        if not steps:
            return None, dict(info, refused=["no exact block-local spelling (%d verifies)" % verifies])
        return cur, dict(info, step="+".join(steps), pins_out=len(sites_of(cur)))
