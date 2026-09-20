"""T82: a value staged through a join local is consumed inside the arms, or a statement duplicated in
every arm is hoisted out of the branch chain.

APPEARS     a local written once per arm of an if/else (or if/else-if) chain and read exactly once below it,
            with a fence between the arms or a register/keep pin on the local:
                if (target_delta >= 17) {
                    ASM_SCHED_BARRIER();
                    z_accel = 0x10000;
                } else {
                    z_accel = 0x1000;
                }
                ...
                S32_AT(motion, 0x54) = z_accel;
            and its mirror, one statement written identically at the head (or tail) of every arm:
                if (sprite->unk_14.at00_u16.v & 0x8000) {
                    effect = (u8 *)effect_obj + 0x20;
                    ...
                } else {
                    effect = (u8 *)effect_obj + 0x20;
                    ASM_KEEP(effect);
                    ...
                }
RESOLVES    three round-59 lane rows, byte-exact at their recorded recipes.  dungeon/func_8008D084
            (r59_sol_mid4): `effect = (u8 *)effect_obj + 0x20;` hoisted out of both arms to before the flag
            branch, the ASM_KEEP that held the address form dropped.  dungeon/func_8008BCD0 (r59_sol_mid4):
            the arm-selected `message` consumed once by `func_8004DD2C(message);` - the call written into each
            of the three arms instead, and the block-scoped `register void *message ASM_REG("$4")` declaration
            with the braces that only held it removed.  dungeon/func_80EDF8B8 (r59_sol_large6): `z_accel = K;`
            in four arms consumed once by `S32_AT(motion, 0x54) = z_accel;` - the store written into each arm,
            both ASM_SCHED_BARRIER fences and the `s32 z_accel;` declaration gone.
            Mechanism: the join pseudo IS what needed the pin.  A pseudo set in several arms and read once
            below is live across the whole chain, so gcc 2.7.2's allocator must give it a colour that survives
            every arm (local-alloc refuses the cheap arm-local register) and sched.c cannot move the arm's
            producer past the join - retail instead computes or consumes the value inside the arm, where the
            block ends in the store/call that cross-jumping and the delay-slot filler then share.  With the
            value produced or consumed in the arms there is no join pseudo left to colour, and the fence and
            the register binding become unnecessary.
CANDIDATES  per branch chain, nearest a pin first (a pin inside the chain's span counts as distance 0): the
            SINK (the consumer statement written into every leaf arm, with the local's declaration and its bare
            block removed) and the two HOISTs (the common leading statement moved before the chain, the common
            trailing statement moved after it - neither has to be the arm's first or last statement,
            only the one no other statement in the arm before (or after) it names).  Each move is then screened with the window's pins erased -
            jointly with the pins that name the local, then singly, then the whole function's - by the cc1
            listing against the pinned text (screen.compile_s), and only listing-exact texts go to `vf`.
            Refusals, never guesses: arms that are not brace-delimited, a chain without a final `else`, a
            multi-line leaf statement, `goto`/`return`/`break`/`continue`/`case`/a label inside an arm, an
            address-taken local, a local mentioned anywhere but its declaration, its arm assignments and the
            one consumer, a consumer carrying a call other than the consumer itself (ALL-CAPS accessor macros
            such as `S32_AT` are not calls), a comma at the top level of a substituted expression, and any
            preprocessor line inside the span (an `#ifdef NON_MATCHING` arm must stay byte-identical).
"""
import difflib, re, sys
from pathlib import Path
sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
from pin_census import sites_of, asm_blocker
from pin_sites import erase_many
try:
    from .t29_addrsym import mask_comments
    from .t36_paramwidth import functions
    from .t72_stmtperm import decl_names
    from . import screen
except ImportError:
    from t29_addrsym import mask_comments
    from t36_paramwidth import functions
    from t72_stmtperm import decl_names
    import screen

MAX_SITES = 6
MAX_LISTINGS = 140
MAX_VERIFY = 6
MAX_NEAR = 6
NEAR_D = 3
MAX_DEPTH = 4
MAX_POS = 4

IF_START = re.compile(r"^(?P<ind>[ \t]*)if[ \t]*\(")
ELSE_IF = re.compile(r"^[ \t]*\}[ \t]*else[ \t]+if[ \t]*\(")
ELSE_OPEN = re.compile(r"^[ \t]*\}[ \t]*else[ \t]*\{[ \t]*$")
CLOSE_ONLY = re.compile(r"^[ \t]*\}[ \t]*$")
PIN_STMT = re.compile(r"^[ \t]*ASM_[A-Z0-9_]+[ \t]*\([^;]*\)[ \t]*;")
CAST = re.compile(r"^\([ \t]*(?:(?:unsigned|signed|const|volatile|struct|union|enum)[ \t]+)*"
                  r"[A-Za-z_]\w*(?:[ \t]+long)?[ \t]*\**[ \t]*\)[ \t]*")
IDENT_CALL = re.compile(r"\b([A-Za-z_]\w*)[ \t]*\(")
ATOMIC = re.compile(r"(?:[A-Za-z_]\w*|-?(?:0x[0-9A-Fa-f]+|\d+)|&[ \t]*[A-Za-z_]\w*)")
LABEL = re.compile(r"^[ \t]*[A-Za-z_]\w*[ \t]*:(?!:)", re.M)
CTRL = re.compile(r"^[ \t]*(?:if|else|for|while|do|switch|case|default|return|goto|break|continue)\b")
STRINGS = re.compile(r'"(?:[^"\\\n]|\\.)*"' r"|'(?:[^'\\\n]|\\.)*'")
KEYWORDS = {"if", "for", "while", "do", "switch", "return", "sizeof", "else"}


def mask(text):
    """Comments and string/char literal bodies blanked: brace and paren counting is then safe."""
    t = mask_comments(text)
    return STRINGS.sub(lambda m: m.group(0)[0] + " " * (len(m.group(0)) - 2) + m.group(0)[-1], t)


def _bal(s):
    return s.count("(") - s.count(")")


# ------------------------------------------------------------------------------- chain parsing

def _header_brace(ml, i, last):
    """Line index holding the `{` that opens the arm whose `if (` starts on line i, or None."""
    m = IF_START.match(ml[i]) or ELSE_IF.match(ml[i])
    if not m:
        return None
    depth, pos, j = 1, ml[i].index("(", m.end() - 1) + 1, i
    while j <= last and j < i + 10:
        line = ml[j]
        while pos < len(line):
            if line[pos] == "(":
                depth += 1
            elif line[pos] == ")":
                depth -= 1
                if depth == 0:
                    return j if line[pos + 1:].strip() == "{" else None
            pos += 1
        j += 1
        pos = 0
    return None


def _close(ml, j, last):
    """Line index of the `}` closing the block whose `{` ends line j.

    Counted character by character: a `} else {` line is brace-neutral, so a per-line net count walks
    straight past the brace that ends the arm."""
    depth = 1
    for k in range(j + 1, last + 1):
        for ch in ml[k]:
            if ch == "{":
                depth += 1
            elif ch == "}":
                depth -= 1
                if depth == 0:
                    return k
    return None


def chain_at(ml, i, last):
    """{start, arms: [(b0, b1)], heads: [(h0, h1)], end} for the if/else chain starting on line i.

    Every arm must be brace-delimited and the chain must end in a plain `else` (so every path through it
    runs exactly one arm); anything else is refused."""
    if not IF_START.match(ml[i]):
        return None
    arms, heads, j = [], [], i
    while True:
        h = _header_brace(ml, j, last)
        if h is None:
            return None
        c = _close(ml, h, last)
        if c is None:
            return None
        heads.append((j, h))
        arms.append((h + 1, c - 1))
        if ELSE_OPEN.match(ml[c]):
            c2 = _close(ml, c, last)
            if c2 is None:
                return None
            heads.append((c, c))
            arms.append((c + 1, c2 - 1))
            return {"start": i, "arms": arms, "heads": heads, "end": c2}
        if ELSE_IF.match(ml[c]):
            j = c
            continue
        return None                                    # no final `else` (or `else` on its own line)


def top_stmts(ml, b0, b1):
    """[(first_line, last_line)] of every top-level statement between b0 and b1, or None."""
    out, k = [], b0
    while k <= b1:
        if not ml[k].strip():
            k += 1
            continue
        start, par, br = k, 0, 0
        while k <= b1:
            par += _bal(ml[k])
            br += ml[k].count("{") - ml[k].count("}")
            if par < 0 or br < 0:
                return None
            t = ml[k].rstrip()
            if par == 0 and br == 0 and t.endswith((";", "}", ":")):
                break
            k += 1
        if k > b1:
            return None
        out.append((start, k))
        k += 1
    return out


def body_stmts(ml, b0, b1):
    """Top-level statements of an arm, the pin statements dropped (None if unparseable)."""
    st = top_stmts(ml, b0, b1)
    if st is None:
        return None
    return [s for s in st if not PIN_STMT.match(ml[s[0]])]


def no_label(ml, b0, b1):
    """No label between two lines, so no path can enter the region anywhere but at its head.

    A `goto`/`return`/`break` INSIDE an arm is harmless to both moves: such a path left the chain before
    the arm's last statement, so it ran neither the old copy nor the moved one.  What would break them is
    a jump INTO the region past the moved statement, and that needs a label inside it."""
    return not LABEL.search("\n".join(ml[b0:b1 + 1]))


def chains_in(ml, first, last):
    """Every if/else chain in a line range, outermost first."""
    out = []
    for i in range(first, last + 1):
        if IF_START.match(ml[i]):
            c = chain_at(ml, i, last)
            if c:
                out.append(c)
    return out


# ------------------------------------------------------------------------------ consumer parsing

def top_eq(s):
    """Offset of the outermost plain `=` in s, or None."""
    depth = 0
    for i, ch in enumerate(s):
        if ch in "([":
            depth += 1
        elif ch in ")]":
            depth -= 1
        elif ch == "=" and depth == 0:
            if s[i + 1:i + 2] == "=" or (i and s[i - 1] in "=!<>+-*/%&|^"):
                continue
            return i
    return None


def split_args(s):
    """[(offset, text)] of the top-level comma-separated pieces of s."""
    out, depth, start = [], 0, 0
    for i, ch in enumerate(s):
        if ch in "([":
            depth += 1
        elif ch in ")]":
            depth -= 1
        elif ch == "," and depth == 0:
            out.append((start, s[start:i]))
            start = i + 1
    out.append((start, s[start:]))
    return out


def _calls(s):
    return [m.group(1) for m in IDENT_CALL.finditer(s)
            if m.group(1) not in KEYWORDS and m.group(1).upper() != m.group(1)]


def consumers(line):
    """[(name, offset_in_inner, casted, inner, indent)] - every way `line` reads one local once.

    A store `LHS = m;` / `LHS = (T)m;` or a call `f(..., m, ...)` / `f((T)m)`, with no other call in it."""
    ind = line[:len(line) - len(line.lstrip())]
    body = line.strip()
    if not body.endswith(";"):
        return []
    inner = body[:-1].rstrip()
    out, eq = [], top_eq(inner)
    if eq is not None:
        lhs, rhs = inner[:eq], inner[eq + 1:]
        if _calls(lhs) or _calls(rhs):
            return []
        c = CAST.match(rhs.strip())
        off = eq + 1 + (len(rhs) - len(rhs.lstrip()))
        name = rhs.strip()[c.end():].strip() if c else rhs.strip()
        if c:
            off += c.end()
        if re.fullmatch(r"[A-Za-z_]\w*", name):
            out.append((name, off, bool(c), inner, ind))
        return out
    m = re.fullmatch(r"([A-Za-z_]\w*)[ \t]*\((.*)\)", inner, re.S)
    if not m or m.group(1) in KEYWORDS:
        return []
    args = m.group(2)
    base = m.start(2)
    if [c for c in _calls(args)]:
        return []
    for off, a in split_args(args):
        lead = len(a) - len(a.lstrip())
        c = CAST.match(a.strip())
        name = a.strip()[c.end():].strip() if c else a.strip()
        if re.fullmatch(r"[A-Za-z_]\w*", name):
            out.append((name, base + off + lead + (c.end() if c else 0), bool(c), inner, ind))
    return out


def substitute(cons, expr, ind=None):
    """The consumer statement, at `ind`, with the local replaced by one arm's expression."""
    name, off, casted, inner, own = cons
    ind = own if ind is None else ind
    e = expr.strip()
    if casted and not ATOMIC.fullmatch(e) and not (e.startswith("(") and e.endswith(")") and _bal(e[1:-1]) == 0):
        e = "(%s)" % e
    return ind + inner[:off] + e + inner[off + len(name):] + ";"


# ------------------------------------------------------------------------------------ site finding

ASSIGN = re.compile(r"^[ \t]*(?P<v>[A-Za-z_]\w*)[ \t]*=(?!=)[ \t]*(?P<e>[^;]+);[ \t]*$")


def leaves_of(ml, chain, m, depth=0):
    """Line index of every `m = expr;` that ends a leaf arm of the chain, or None."""
    res = []
    for b0, b1 in chain["arms"]:
        st = body_stmts(ml, b0, b1)
        if not st:
            return None
        s0, s1 = st[-1]
        if s0 != s1 or not ASSIGN.match(ml[s0]):
            sub = chain_at(ml, s0, b1) if depth < MAX_DEPTH else None
            if not sub or sub["end"] != s1:
                return None
            r = leaves_of(ml, sub, m, depth + 1)
            if r is None:
                return None
            res += r
            continue
        a = ASSIGN.match(ml[s0])
        if a.group("v") != m or re.search(r"\b%s\b" % re.escape(m), a.group("e")):
            return None
        res.append(s0)
    return res


def decl_line_of(ml, first, last, m):
    """The single line declaring m (exactly one declarator), (index, single) or None."""
    rx = re.compile(r"^[ \t]*(?:register[ \t]+)?(?:(?:unsigned|signed|const|struct|union|enum)[ \t]+)*"
                    r"[A-Za-z_]\w*(?:[ \t]+long)?[ \t]*\**[ \t]*%s\b" % re.escape(m))
    hits = [k for k in range(first, last + 1) if rx.match(ml[k])]
    if len(hits) != 1:
        return None
    k = hits[0]
    single = re.match(r"^[ \t]*(?:register[ \t]+)?(?:(?:unsigned|signed|const|struct|union|enum)[ \t]+)*"
                      r"[A-Za-z_]\w*(?:[ \t]+long)?[ \t]*\**[ \t]*%s[ \t]*(?:ASM_REG\([^()]*\))?[ \t]*;[ \t]*$"
                      % re.escape(m), ml[k]) is not None
    return k, single


def sink_sites(ml, first, last, locals_):
    """[dict] for every branch chain whose arms all end in `m = e;` with one consumer below."""
    out = []
    for chain in chains_in(ml, first, last):
        k = chain["end"] + 1
        while k <= last and (not ml[k].strip() or PIN_STMT.match(ml[k])):
            k += 1
        if k > last:
            continue
        if top_stmts(ml, k, k) != [(k, k)]:
            continue                                       # the consumer must be one whole line
        for cons in consumers(ml[k]):
            m = cons[0]
            if m not in locals_:
                continue
            leaves = leaves_of(ml, chain, m)
            if not leaves or len(leaves) < 2:
                continue
            body = "\n".join(ml[first:last + 1])
            if re.search(r"&[ \t]*%s\b" % re.escape(m), body):
                continue
            d = decl_line_of(ml, first, last, m)
            if d is None or d[0] > chain["start"]:
                continue
            allowed = {d[0]: 1, k: 1}
            allowed.update({ln: 1 for ln in leaves})
            forced, bad = [], False
            for j in range(first, last + 1):
                n = len(re.findall(r"\b%s\b" % re.escape(m), ml[j]))
                if not n:
                    continue
                if PIN_STMT.match(ml[j]):
                    forced.append(j)
                elif allowed.get(j) != n:
                    bad = True
                    break
            if bad:
                continue
            out.append({"kind": "sink", "chain": chain, "m": m, "cons": cons, "cons_line": k,
                        "leaves": leaves, "decl": d[0], "decl_single": d[1],
                        "lo": min(d[0], chain["start"]), "hi": k,
                        "focus": leaves + [k], "span": (chain["start"], k)})
            break
    return out


def _idents(s):
    return set(re.findall(r"[A-Za-z_]\w*", s))


def _text(ml, st):
    return "\n".join("\n".join(ml[a:b + 1]) for a, b in st)


def hoist_sites(ml, first, last):
    """[dict] for every branch chain with one statement written identically in every arm.

    The statement need not be the arm's first (or last): a leading hoist is admissible as long as no
    statement before it in any arm names anything the statement names, a trailing one as long as none
    after it does - which is the brief's `names nothing assigned earlier in any arm`, read strictly."""
    out = []
    for chain in chains_in(ml, first, last):
        arms = chain["arms"]
        if len(arms) < 2:
            continue
        sts = [body_stmts(ml, b0, b1) for b0, b1 in arms]
        if any(not st for st in sts):
            continue
        norm = [[" ".join(ml[a].split()) if a == b else None for a, b in st] for st in sts]
        conds = "\n".join("\n".join(ml[h0:h1 + 1]) for h0, h1 in chain["heads"])
        cond_writes = top_eq(conds) is not None or re.search(r"\+\+|--", conds)
        seen = set()
        for where in ("lead", "tail"):
            for one in (norm[0][:MAX_POS] if where == "lead" else norm[0][-MAX_POS:]):
                if not one or (where, one) in seen:
                    continue
                seen.add((where, one))
                if not one.endswith(";") or "{" in one or "}" in one or CTRL.match(one) or ":" in one.split("(")[0]:
                    continue
                if any(g.count(one) != 1 for g in norm):
                    continue
                at = [g.index(one) for g in norm]
                names = _idents(one)
                rest = [_text(ml, st[:j] if where == "lead" else st[j + 1:]) for st, j in zip(sts, at)]
                if any(names & _idents(r) for r in rest):
                    continue
                if where == "lead":
                    a = ASSIGN.match(ml[sts[0][at[0]][0]])
                    if not a or _calls(a.group("e")) or cond_writes:
                        continue
                    if re.search(r"\b%s\b" % re.escape(a.group("v")), conds):
                        continue                          # the hoisted value decides a condition below it
                copies = [st[j][0] for st, j in zip(sts, at)]
                out.append({"kind": "hoist", "where": where, "chain": chain, "stmt": ml[copies[0]].strip(),
                            "copies": copies, "lo": chain["start"], "hi": chain["end"], "focus": copies,
                            "span": (chain["start"], chain["end"])})
    return out


def sites_in(text):
    """Every t82 site in every function of `text`."""
    ml = mask(text).split("\n")
    out = []
    for fname, params, b0, b1 in functions(text):
        masked = mask(text)
        first, last = masked.count("\n", 0, b0), masked.count("\n", 0, b1)
        locals_ = decl_names(masked[b0:b1]) | {p for p, _, _, _ in params}
        for s in sink_sites(ml, first, last, locals_) + hoist_sites(ml, first, last):
            if any(ml[j].lstrip().startswith("#") for j in range(s["lo"], s["hi"] + 1)):
                continue                                   # a preprocessor arm inside the span: refuse
            if not no_label(ml, *s["span"]):
                continue                                   # something can jump into the moved region
            out.append(s)
    return out


# ------------------------------------------------------------------------------------- rewriting

def _unwrap(keys, texts, decl_key, ml):
    """Drop the bare `{ }` block that only held the declaration (keys/texts are edited in place)."""
    stack = []
    for k in range(len(ml)):
        if k == decl_key:
            break
        for ch in ml[k]:
            if ch == "{":
                stack.append(k)
            elif ch == "}" and stack:
                stack.pop()
    if not stack:
        return
    open_line = stack[-1]
    if ml[open_line].strip() != "{":
        return
    prev = next((ml[q] for q in range(open_line - 1, -1, -1) if ml[q].strip()), "")
    if not prev.rstrip().endswith((";", "}")) or re.match(r"^[ \t]*(?:else|do)\b", prev):
        return
    close_line = _close(ml, open_line, len(ml) - 1)
    if close_line is None or not CLOSE_ONLY.match(ml[close_line]):
        return
    inner = [i for i, k in enumerate(keys) if isinstance(k, int) and open_line < k < close_line]
    if not inner:
        return
    if decl_names(mask("\n".join(texts[i] for i in inner))):
        return                                             # a declaration still needs the block
    ind = len(ml[open_line]) - len(ml[open_line].lstrip())
    body = [texts[i] for i in inner if texts[i].strip()]
    delta = min(len(x) - len(x.lstrip(" ")) for x in body) - ind if body else 0
    if delta > 0 and all(x.startswith(" " * delta) or not x.strip() for x in (texts[i] for i in inner)):
        for i in inner:
            if texts[i].strip():
                texts[i] = texts[i][delta:]
    for i in sorted([j for j, k in enumerate(keys) if k in (open_line, close_line)], reverse=True):
        del keys[i]
        del texts[i]


def build(text, site):
    """(new_text, [line indices of the new text the move touched]) or (None, None)."""
    lines, ml = text.split("\n"), mask(text).split("\n")
    keys, texts, touched = [], [], set()
    if site["kind"] == "sink":
        drop = {site["cons_line"]}
        if site["decl_single"]:
            drop.add(site["decl"])
        sub = {ln: substitute(site["cons"], ASSIGN.match(ml[ln]).group("e"),
                              lines[ln][:len(lines[ln]) - len(lines[ln].lstrip())])
               for ln in site["leaves"]}
        for i, ln in enumerate(lines):
            if i in drop:
                continue
            keys.append(i)
            texts.append(sub.get(i, ln))
            if i in sub:
                touched.add(len(texts) - 1)
        if site["decl_single"]:
            _unwrap(keys, texts, site["decl"], ml)
    else:
        copies, stmt = set(site["copies"]), site["stmt"]
        ind = lines[site["chain"]["start"]][:len(lines[site["chain"]["start"]]) -
                                            len(lines[site["chain"]["start"]].lstrip())]
        for i, ln in enumerate(lines):
            if i in copies:
                continue
            if i == site["chain"]["start"] and site["where"] == "lead":
                keys.append(("new", i))
                texts.append(ind + stmt)
                touched.add(len(texts) - 1)
            keys.append(i)
            texts.append(ln)
            if i == site["chain"]["end"] and site["where"] == "tail":
                keys.append(("new", i))
                texts.append(ind + stmt)
                touched.add(len(texts) - 1)
    span = set(range(site["lo"], site["hi"] + 1))
    win = sorted(touched | {i for i, k in enumerate(keys) if isinstance(k, int) and k in span})
    if not win:
        return None, None, None
    return "\n".join(texts), win, sorted(touched)


def plans(cand_sites, win_lo, win_hi, forced, touched):
    """Pin groups to try: the forced ones with the window's jointly, the forced alone, then singles.

    A window can be most of a function (a sink's runs from the declaration to the consumer), so the
    window's pins are ranked by their distance to the lines the move actually rewrote - never to the
    window's edges, which would drop the pins between the arms first on a row with many pins."""
    near = sorted([s for s in cand_sites if win_lo <= s[5] <= win_hi and s not in forced],
                  key=lambda s: min(abs(s[5] - 1 - t) for t in touched))[:MAX_NEAR]
    out, seen = [], set()
    for g in ([forced + near] if near else []) + [forced] + [forced + [p] for p in near] + [list(cand_sites)]:
        key = tuple(sorted(s[3] for s in g))
        if key in seen:
            continue
        seen.add(key)
        out.append(g)
    return out


def _sig(site):
    if site["kind"] == "sink":
        return ("sink", site["m"], site["cons"][3])
    return ("hoist", site["where"], site["stmt"], site["chain"]["start"] - site["chain"]["end"])


class T:
    name = "t82_armsink"
    level = 1
    needs_verify = True

    @staticmethod
    def eligible(text, row, census):
        why = asm_blocker(text)
        if why:
            return why
        if not sites_of(text):
            return "no pins"
        return None if sites_in(text) else "no join local or duplicated arm statement in a braced if/else"

    @classmethod
    def apply_verified(cls, text, row, census, vf):
        pins_in, listings, verifies, steps, cur = len(sites_of(text)), 0, 0, [], text
        target = screen.compile_s(row, text)
        if target is None:
            return None, {"refused": "pinned text does not build to a listing", "pins_in": pins_in,
                          "pins_out": pins_in}
        pin_lines = [s[5] - 1 for s in sites_of(text)]

        def dist(s):
            span = 0 if any(s["lo"] <= p <= s["hi"] for p in pin_lines) else \
                min(min(abs(p - s["lo"]), abs(p - s["hi"])) for p in pin_lines)
            return span, min(abs(p - f) for p in pin_lines for f in s["focus"])

        cands = sorted(sites_in(text), key=dist)[:MAX_SITES]
        best_d, fallback = None, None
        for site in cands:
            live = [s for s in sites_in(cur) if _sig(s) == _sig(site)]
            if not live:
                continue
            site = live[0]
            moved, win, touched = build(cur, site)
            if moved is None:
                continue
            all_sites = sites_of(moved)
            forced = [s for s in all_sites if re.search(r"\b%s\b" % re.escape(site.get("m") or "\x00"), s[2] or "")]
            done = False
            for group in plans(all_sites, win[0] - 1, win[-1] + 3, forced, touched):
                if listings >= MAX_LISTINGS or verifies >= MAX_VERIFY:
                    break
                cand = erase_many(moved, group, clean_notes=True)
                if len(sites_of(cand)) >= len(sites_of(cur)):
                    continue
                lst = screen.compile_s(row, cand)
                listings += 1
                if lst is None:
                    continue
                d = sum(1 for y in difflib.unified_diff(target, lst, lineterm="", n=0)
                        if y[:1] in "+-" and not y.startswith(("---", "+++")))
                if best_d is None or d < best_d:
                    best_d, fallback = d, cand
                if d:
                    continue
                verifies += 1
                if vf(cand).get("exact"):
                    cur, done = cand, True
                    steps.append("%s%s@%d-erase%d" % (site["kind"], "/" + site["where"] if site.get("where") else "",
                                                     win[0] + 1, len(group)))
                    break
            if done:
                continue
        if not steps and fallback is not None and best_d and best_d <= NEAR_D and verifies < 2:
            verifies += 1        # the screen is a heuristic, not a proof: try one near miss (t74 never does)
            if vf(fallback).get("exact"):
                cur, steps = fallback, ["nearest@d%d" % best_d]
        info = {"listings": listings, "tried": verifies, "pins_in": pins_in, "pins_out": len(sites_of(cur)),
                "sites": len(cands), "best_d": best_d}
        if not steps:
            return None, info
        return cur, dict(info, step="+".join(steps))
