"""T29: a pinned local holding an address literal, where retail references a SYMBOL.

APPEARS     `V = 0x800E0000;` (any cast, U suffix, do{}while(0) wrapper, the one-line split idiom
            `(V) = PAGE; ASM_KEEP(V); (V) -= OFF;`, or PAGE / keeps / `V += OFF;` across lines, or a
            symbol-spelled page `V = (u8 *)&D_X + K;`), pins on V, and uses `V +/- K`,
            `(T *)(V +/- K)`, `(u8 *)V + K`, `(T *)V` or a bare `V` in operand position.
RESOLVES    retail's `lui` into a scratch register then `addiu` into the destination (or a lone `lui`
            in a delay slot) is gcc splitting a SYMBOL address into HIGH/LO_SUM. The CDK build
            (2.7.2-cdk) splits; FSF 2.7.2 and 2.6.3 emit the one-insn `la` macro. Upstream matched these
            rows at a non-splitting cell and emulated the split with an integer page plus pins.
            Written as the symbol, the row is exact at the recorded cell or at a CDK cell where its
            pinned text is exact too (tools/pin_cells_land.py rules 1-2: the shipped bytes never
            depend on the switch).
POPULATION  2026-09-12 atlas: 975 pins / 336 functions on address-literal variables; this generator
            reaches 431 of them in 199 rows. First harvest: 52 rows / 113 pins, 32 of them via a CDK
            cell. An attribution control put 27 of those 32 on the pair (symbol AND cell): erasing
            the pins at the CDK cell without the rewrite was exact for only two.

Each use becomes the symbol at its effective address, spelled from the file's own declaration
(an array decays, a scalar takes `&`, a missing symbol gets `extern u8 D_X[];`); V's definitions,
its pins and every declaration of V go. Candidates: every variable alone, then all together.
Where the only use is a macro base or a struct view, the symbol named is the page itself
(`S32(D_80080000, 0x346C)`), the spelling the earlier litsym landings used.
"""
import re, sys, collections
from pathlib import Path
sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
from pin_census import sites_of
from pin_sites import erase_many

CDK = ("2.7.2-cdk", "2.7.2-cdk-G0")
CAST = r"(?:\(\s*(?:const\s+|volatile\s+|unsigned\s+|signed\s+)*[A-Za-z_]\w*(?:\s+long)?\s*\**\s*\)\s*)"
LIT = r"\(?\s*" + CAST + r"*0x(?P<a>8[0-9A-Fa-f]{7})[Uu]?[Ll]?\s*\)?"
NUM = r"(?:0x[0-9A-Fa-f]+|\d+)"
BYTEPTR = {"u8", "s8", "char", "void", "unsigned char", "signed char"}
INTTY = {"u32", "s32", "int", "unsigned int", "unsigned long", "long", "unsigned", "signed"}
ELEMSIZE = dict({t: 1 for t in BYTEPTR}, u16=2, s16=2, u32=4, s32=4, int=4, **{"unsigned int": 4})
NOTE_RE = re.compile(r"^[ \t]*/\*[^\n]*(?:\(pin\)|\bPin:|Byte-exact pin|MATCH:)[^\n]*\*/[ \t]*\n", re.M)
LOCAL_SYM_RE = re.compile(r"^[ \t]+(?:register[ \t]+)?(?!(?:return|else|case|goto|do|sizeof)\b)"
                          r"[A-Za-z_][\w \t]*[\s*]\**\s*D_[0-9A-F]{8}\s*[;=,\[]", re.M)
NOT_TYPES = {"return", "else", "goto", "case", "do", "if", "while", "for", "switch", "sizeof"}


def mask_comments(t):
    return re.sub(r"/\*.*?\*/", lambda m: re.sub(r"[^\n]", " ", m.group(0)), t, flags=re.S)


def decls_of(t, v):
    """Every local declaration of V: [(type, pointer depth, span)]; block-scoped redeclarations too."""
    rx = re.compile(r"^[ \t]*(?:register[ \t]+)?(?P<ty>(?:unsigned[ \t]+|signed[ \t]+|const[ \t]+)*[A-Za-z_]\w*(?:[ \t]+long)?)"
                    r"[ \t]*(?P<p>\**)[ \t]*\b%s\b[ \t]*(?:ASM_REG\([^)]*\))?[ \t]*(?:=[^;]*)?;[^\n]*\n" % re.escape(v), re.M)
    return [(m.group("ty").strip(), len(m.group("p")), (m.start(), m.end()))
            for m in rx.finditer(t) if m.group("ty").strip() not in NOT_TYPES]


def sym_decl(t, s):
    m = re.search(r"^extern\s+(?P<ty>[\w ]+?)\s*(?P<p>\**)\s*\b%s\b\s*(?P<arr>\[[^\]]*\])?\s*;" % s, t, re.M)
    if not m:
        return None
    return m.group("ty").strip() + "*" * len(m.group("p")), bool(m.group("arr"))


def sym_expr(t, addr, want, externs):
    """The symbol at `addr` as an expression of pointer type `want` ('u16 *' / None = natural)."""
    s = "D_%08X" % addr
    d = sym_decl(t, s)
    if d is None:
        externs.add("extern u8 %s[];\n" % s)
        elem, arr = "u8", True
    else:
        elem, arr = d
    base = s if arr else "&" + s
    if want is None:
        return base
    w = re.sub(r"\s+", " ", want.replace("*", "").strip())
    if w == elem and want.count("*") == 1:
        return base
    return "(%s)%s" % (want.strip(), base)


def sym_value(t, e):
    """Address of a symbol-spelled page: `(u8 *)&D_X + K`, `(u8 *)D_X - K`, `&D_X`, `D_X` (byte offsets only)."""
    m = re.fullmatch(r"\s*(?:\(\s*(?P<c>[A-Za-z_][\w ]*)\s*\*\s*\)\s*)?&?\s*D_(?P<x>[0-9A-Fa-f]{8})\s*"
                     r"(?:(?P<op>[-+])\s*(?P<k>%s))?\s*" % NUM, e)
    if not m:
        return None
    x = int(m.group("x"), 16)
    if not m.group("k"):
        return x
    if not m.group("c") or re.sub(r"\s+", " ", m.group("c").strip()) not in BYTEPTR:
        d = sym_decl(t, "D_" + m.group("x").upper())
        if not d or d[0] not in BYTEPTR:
            return None                          # a scaled offset: leave it alone
    k = int(m.group("k"), 0)
    return x + k if m.group("op") == "+" else x - k


def operand_lead(masked, pos):
    """True when the token before `pos` puts it in operand position (not a declarator)."""
    before = masked[:pos].rstrip()
    if before.endswith("return"):
        return True
    ch = before[-1:]
    if ch in ("(", "=", "+", "-", "?", ":", "[", "|", "&", "^", "<", ">", "!", "~"):
        return not before.endswith(("++", "--"))
    if ch == ",":
        stmt = re.split(r"[;{}]", before)[-1]
        return stmt.count("(") > stmt.count(")")         # inside an argument list
    return False


def rewrite_var(text, v):
    """Return (new_text, info) with every use of V turned into symbols, or (None, reason)."""
    V = re.escape(v)
    decs = decls_of(text, v)
    if not decs:
        return None, "no-decl"
    if len({(ty, p) for ty, p, _ in decs}) != 1:
        return None, "mixed-decl"
    ty, ptr, _ = decs[0]
    # `V + K` on a pointer steps K elements: scale to bytes (void * steps bytes, a GNU extension)
    if ptr == 0 and ty in INTTY:
        scale = 1
    elif ptr == 1 and ty in ELEMSIZE:
        scale = ELEMSIZE[ty]
    elif ptr == 2:
        scale = 4
    else:
        return None, "type:%s%s" % (ty, "*" * ptr)
    t = text
    split = re.compile(r"^[ \t]*\(?%s\)?\s*=\s*%s\s*;\s*ASM_\w+\(\s*%s\s*\)\s*;\s*\(?%s\)?\s*(?P<op>[-+])=\s*(?P<k>%s)\s*;[^\n]*\n"
                       r"(?:[ \t]*/\*[^\n]*\*/[ \t]*\n)?" % (V, LIT, V, V, NUM), re.M)
    dow = re.compile(r"^[ \t]*do\s*\{\s*%s\s*=\s*%s\s*;\s*\}\s*while\s*\(\s*0\s*\)\s*;[^\n]*\n" % (V, LIT), re.M)
    plain = re.compile(r"^[ \t]*\(?%s\)?\s*=\s*%s\s*;[^\n]*\n" % (V, LIT), re.M)
    symdef = re.compile(r"^[ \t]*\(?%s\)?\s*=\s*(?P<e>[^;=\n]*\bD_[0-9A-Fa-f]{8}\b[^;=\n]*)\s*;[^\n]*\n" % V, re.M)
    rawkeep = re.compile(r"^[ \t]*__asm__\s+__volatile__\s*\(\s*\"\"\s*:\s*\"=r\"\s*\(\s*%s\s*\)\s*:\s*\"0\"\s*\(\s*%s\s*\)\s*\)\s*;[^\n]*\n"
                         % (V, V), re.M)
    keepline = re.compile(r"^[ \t]*(?:ASM_\w+\([^;\n]*\b%s\b[^;\n]*\)\s*;|__asm__\s+__volatile__\s*\([^;\n]*\b%s\b[^;\n]*\)\s*;)[^\n]*\n"
                          r"|^[ \t]*/\*[^\n]*\*/[ \t]*\n" % (V, V), re.M)
    bump = re.compile(r"[ \t]*\(?%s\)?\s*(?P<op>[-+])=\s*(?P<k>-?\s*%s)\s*;[^\n]*\n" % (V, NUM))
    marks = []
    for rx, kind in ((split, "split"), (dow, "dowhile"), (plain, "plain"), (symdef, "symdef")):
        for m in rx.finditer(t):
            if any(a < m.end() and m.start() < b for a, b, _ in marks):
                continue
            end = m.end()
            if kind == "symdef":
                val = sym_value(t, m.group("e"))
                if val is None:
                    continue
            else:
                val = int(m.group("a"), 16)
            if kind == "split":
                k = int(m.group("k"), 0)
                val = val - k if m.group("op") == "-" else val + k
            elif kind in ("plain", "symdef"):
                # PAGE; keeps of V (pins or raw empty asm); `V +/-= OFF;` - one definition across lines
                p = end
                while True:
                    k2 = keepline.match(t, p)
                    if not k2:
                        break
                    p = k2.end()
                b2 = bump.match(t, p)
                if b2:
                    k = int(b2.group("k").replace(" ", ""), 0)
                    val = val - k if b2.group("op") == "-" else val + k
                    end = b2.end()
            marks.append((m.start(), end, val))
    for m in rawkeep.finditer(t):                 # stray empty-asm keeps of V: scaffolding like the pins
        if not any(a <= m.start() < b for a, b, _ in marks):
            marks.append((m.start(), m.end(), None))
    dspans = [sp for _, _, sp in decs]
    for a, b in dspans:
        dm = re.search(r"=\s*%s\s*;" % LIT, text[a:b])
        if dm:
            marks.append((a, b, int(dm.group("a"), 16)))
        elif "=" in mask_comments(text[a:b]):
            return None, "decl-init"
    if not marks:
        return None, "no-literal-def"
    marks.sort()
    masked = mask_comments(t)
    pins = [s for s in sites_of(t) if re.search(r"\b%s\b" % V, t[s[3]:s[4]])]
    pin_spans = [(s[3], s[4]) for s in pins]
    def inside(pos, spans):
        return any(a <= pos < b for a, b in spans)
    fixed = [(a, b) for a, b, _ in marks] + pin_spans + dspans
    # statements that change V: `V +/-= K` and `V++` fold while the literal is known; anything else
    # (`V = load`, `V += x`) ends the literal's range and stays - V keeps its other role (CONFINED)
    chg_rx = re.compile(r"^[ \t]*\(?%s\)?\s*(?P<op>[-+*/|&^]?=(?!=)|\+\+|--)\s*(?P<rhs>[^;]*);[^\n]*\n" % V, re.M)
    changes = [m for m in chg_rx.finditer(masked) if not inside(m.start(), fixed)]
    lhs = [(m.start(), m.start("op")) for m in changes]
    use_rx = re.compile(
        r"(?P<c1>\(\s*(?P<t1>[A-Za-z_][\w ]*\*)\s*\)\s*\(\s*%s\s*(?P<o1>[-+])\s*(?P<k1>%s)\s*\))"   # (T *)(V + K)
        r"|(?P<c2>\(\s*(?P<t2>[A-Za-z_][\w ]*\*)\s*\)\s*%s\s*(?P<o2>[-+])\s*(?P<k2>%s))"            # (T *)V + K
        r"|(?P<c3>\b%s\s*(?P<o3>[-+])\s*(?P<k3>%s))"                                               # V + K
        r"|(?P<c4>\(\s*(?P<t4>[A-Za-z_][\w ]*\*)\s*\)\s*%s\b)"                                     # (T *)V
        r"|(?P<c6>\(\s*(?P<t6>(?:unsigned\s+|signed\s+)?(?:u32|s32|int|long))\s*\)\s*%s\b)"          # (u32)V
        r"|(?P<c5>\b%s\b)" % (V, NUM, V, NUM, V, NUM, V, V, V))
    uses = [m for m in use_rx.finditer(masked) if not inside(m.start(), fixed + lhs)]
    events = sorted([(a, 0, "def", val) for a, b, val in marks if val is not None]
                    + [(m.end(), 1, "chg", m) for m in changes]      # a change takes effect after its RHS
                    + [(m.start(), 2, "use", m) for m in uses], key=lambda e: (e[0], e[1]))
    externs, edits, drops, known = set(), [], [], []
    cur = start = None; confined = False
    for pos, _, kind, x in events:
        if kind == "def":
            if cur is not None:
                known.append((start, pos))
            cur, start = x, pos
            continue
        if kind == "chg":
            op, rhs = x.group("op"), x.group("rhs").strip()
            step = scale if op in ("++", "--") and not rhs else \
                int(rhs.replace(" ", ""), 0) * scale if op in ("+=", "-=") and re.fullmatch(r"-?\s*%s" % NUM, rhs) else None
            if cur is not None and step is not None:
                cur = cur + step if op in ("+=", "++") else cur - step
                drops.append((x.start(), x.end()))
                continue
            if cur is not None and op != "=":
                return None, "modified"                 # reads the literal in a way that does not fold
            if cur is not None:
                known.append((start, x.end()))
            cur = start = None; confined = True
            continue
        m = x
        if cur is None:
            confined = True                             # V's other role (or a read before any literal): left alone
            continue
        val = cur
        after = masked[m.end():].lstrip()
        tail = after[:1]
        deref = after.startswith(("->", "["))
        if m.group("c1"):
            k = int(m.group("k1"), 0) * scale; a = val + k if m.group("o1") == "+" else val - k
            if tail not in (")", ";", ",", "]") and not deref:
                return None, "operand-context"
            rep = sym_expr(t, a, m.group("t1"), externs)
            if deref:
                rep = "(" + rep + ")"
        elif m.group("c2"):
            if re.sub(r"\s+", " ", m.group("t2").replace("*", "").strip()) not in BYTEPTR:
                return None, "scaled-cast"
            k = int(m.group("k2"), 0); a = val + k if m.group("o2") == "+" else val - k
            if tail not in (")", ";", ","):
                return None, "operand-context"
            rep = sym_expr(t, a, m.group("t2"), externs)
        elif m.group("c3"):
            k = int(m.group("k3"), 0) * scale; a = val + k if m.group("o3") == "+" else val - k
            if tail not in (")", ";", ",") or not operand_lead(masked, m.start()):
                return None, "operand-context"
            rep = sym_expr(t, a, (ty + " *") if ptr else None, externs)
        elif m.group("c4"):
            rep = sym_expr(t, val, m.group("t4"), externs)
            if deref and not re.fullmatch(r"D_[0-9A-F]{8}", rep):
                rep = "(" + rep + ")"                  # a bare array symbol indexes as it stands
        elif m.group("c6"):
            rep = "(%s)%s" % (m.group("t6"), sym_expr(t, val, None, externs))
        else:
            if re.match(r"(\+\+|--|[-+*/|&^]?=(?!=))", after) or masked[:m.start()].rstrip().endswith(("++", "--")):
                return None, "modified"
            if after.startswith("."):
                return None, "deref"
            if after.startswith(("->", "[")):
                if not ptr:
                    return None, "deref"
                # a view of the symbol with V's own pointer type: `((T *)D_X)->f`, `D_X[i]`
                rep = sym_expr(t, val, ty + " " + "*" * ptr, externs)
                if not re.fullmatch(r"D_[0-9A-F]{8}", rep):
                    rep = "(" + rep + ")"
                edits.append((m.start(), m.end(), rep))
                continue
            if not operand_lead(masked, m.start()):
                return None, "not-operand"
            rep = sym_expr(t, val, (ty + " *") if ptr else None, externs)
        edits.append((m.start(), m.end(), rep))
    if cur is not None:
        known.append((start, len(t)))
    if not edits:
        return None, "no-uses"
    if confined and any("=" in mask_comments(text[a:b]) for a, b in dspans):
        return None, "decl-init-confined"
    # one pass, last first: use edits; definitions and folded steps cut; the declarations too
    # unless V keeps another role
    cuts = set(edits) | {(a, b, "") for a, b, _ in marks} | {(a, b, "") for a, b in drops}
    if not confined:
        cuts |= {(a, b, "") for a, b in dspans}
    gone = [(a, b) for a, b, _ in marks] + drops + ([] if confined else dspans)
    kept_pins = [s for s in pins if not inside(s[3], gone)]
    # full elimination: every pin of V goes; confined: statement pins inside a literal's range go,
    # the declaration's register pin and pins on V's other role stay
    kill_pin = [not confined or (s[0] == "stmt" and inside(s[3], known)) for s in kept_pins]
    for a, b, rep in sorted(cuts, key=lambda c: c[0], reverse=True):
        t = t[:a] + rep + t[b:]
    left = [s for s in sites_of(t) if re.search(r"\b%s\b" % V, t[s[3]:s[4]])]
    if len(left) != len(kept_pins):
        return None, "pin-drift"
    chosen = [s for s, k in zip(left, kill_pin) if k]
    if chosen:
        t = erase_many(t, chosen, clean_notes=True)
    if not confined and re.search(r"\b%s\b" % V, mask_comments(t)):
        return None, "still-mentioned"
    # pin notes the edit left standing alone on their own line go too (the original's stay)
    orig_notes = collections.Counter(m.group(0).strip() for m in NOTE_RE.finditer(text))
    def drop_new_orphans(m):
        k = m.group(0).strip()
        if orig_notes[k] > 0:
            orig_notes[k] -= 1; return m.group(0)
        return ""
    t = NOTE_RE.sub(drop_new_orphans, t)
    # `(T *)((u8 *)D_X)` is `(T *)D_X`: the byte view was only there for the offset that is gone
    t = re.sub(r"\((\s*[A-Za-z_][\w ]*\*+\s*)\)\s*\(\s*\((?:u8|s8|char|unsigned char|signed char) \*\)(&?D_[0-9A-F]{8})\s*\)",
               r"(\1)\2", t)
    # and a cast of a parenthesised lone symbol drops the parentheses: `(void **)(D_X)` -> `(void **)D_X`
    t = re.sub(r"\((\s*[A-Za-z_][\w ]*\*+\s*)\)\s*\(\s*(&?D_[0-9A-F]{8})\s*\)", r"(\1)\2", t)
    for e in sorted(externs):
        if e.strip() in t:
            continue
        # after the top-level includes, never after the last extern: that one can sit inside an
        # #ifdef arm, where the -DNON_MATCHING port build would not see the new declaration
        L = t.splitlines(True)
        at = max((i for i, l in enumerate(L) if l.startswith("#include")), default=-1)
        L.insert(at + 1, e); t = "".join(L)
    if LOCAL_SYM_RE.search(mask_comments(t)) and not LOCAL_SYM_RE.search(mask_comments(text)):
        return None, "local-named-like-a-symbol"
    from pin_census import unscored_text
    if unscored_text(t) != unscored_text(text):
        return None, "port-arm"                 # V lives in a NON_MATCHING / #if 0 arm too: leave it
    return t, {"var": v, "uses": len(uses), "defs": len(marks), "pins": len(pins)}


def addrvars(text):
    """Variables assigned an address literal that carry at least one pin."""
    masked = mask_comments(text)
    names = {m.group(1) for m in re.finditer(r"\(?\b([A-Za-z_]\w*)\)?\s*=\s*%s\s*;" % LIT, masked)}
    pinned = set()
    for s in sites_of(text):
        pinned.update(re.findall(r"\b([A-Za-z_]\w*)\b", text[s[3]:s[4]]))
    return sorted(n for n in names if n in pinned)


def candidates(text):
    out, cur, used, skipped = [], text, [], {}
    for v in addrvars(text):
        new, info = rewrite_var(text, v)
        if new is None:
            skipped[v] = info; continue
        out.append(("addrsym:" + v, new))
        nxt, _ = rewrite_var(cur, v)
        if nxt is not None:
            cur = nxt; used.append(v)
    if len(used) > 1:
        out.insert(0, ("addrsym:*" + "+".join(used), cur))
    return out, skipped


class T:
    name = "t29_addrsym"; level = 1
    needs_verify = True

    @staticmethod
    def eligible(text, row, census):
        if not sites_of(text):
            return "no pin sites"
        if not addrvars(text):
            return "no pinned address-literal variable"
        return None

    @staticmethod
    def apply_verified(text, row, census, vf):
        cands, skipped = candidates(text)
        if not cands:
            return None, {"refused": ["no rewritable variable: " + ", ".join("%s %s" % kv for kv in sorted(skipped.items()))]}
        cands.sort(key=lambda c: len(sites_of(c[1])))              # most pins removed first
        for label, t in cands:
            if vf(t).get("exact"):
                return t, {"label": label}
        # rule 1 holds from here: no candidate is exact at the recorded cell
        g0 = "-G0" in row["cfg"]
        for cell in sorted(CDK, key=lambda c: ("-G0" in c) != g0):
            if cell == row["cfg"] or not vf(text, cell).get("exact"):
                continue                                             # rule 2: the pinned text must be exact there too
            for label, t in cands:
                if vf(t, cell).get("exact"):
                    return t, {"label": label, "cfg": cell}
        return None, {"refused": ["no candidate exact at the recorded cell or at a CDK cell that admits the pinned text"]}
