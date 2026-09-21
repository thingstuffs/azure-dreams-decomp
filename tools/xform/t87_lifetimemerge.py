"""T87: two consecutive, non-overlapping lifetimes merged into one variable (the second value inherits
the first one's pseudo, and the ordering dependence that comes with overwriting it).

APPEARS     a pinned run in which one local dies and the next one is born on the following statement:

                node = func_800A05A4(object, ...);           <- A's last value
                (*(void * volatile *)((u8 *)object + 0x60)) = node;
                ASM_KEEP(node);                              <- the pin
                x = (*(s8 *)((u8 *)object + 0x72));          <- B, first written here
                y = (*(s8 *)((u8 *)object + 0x73));
                ... abs(x), abs(y), stored back ...

            and the register-pinned staging variant, a wide local holding a narrow volatile read while
            an existing narrow local of the function is dead over that stretch:

                register u32 raw_height ASM_REG("$3");
                u16 part_flags;                              <- dead from here on
                ...
                raw_height = *(volatile u16 *)((u8 *)object_arg + 0x92);
                height_adjust = raw_height - 8;

RESOLVES    five rows byte-exact in the round-62 astra lane (work/native_lane/r62_astra_families/REPORT.md):
            dungeon/func_80A9D4E8, func_80DBBFC8, func_810318E4 (item-target family) and func_80D66164,
            func_80E0D2E8 (raw-height pair).  Mechanism, from that lane's RTL dumps: when B's first value
            is written into A's storage, the return copy and the first coordinate load SET THE SAME PSEUDO,
            so the load carries `REG_DEP_OUTPUT` on the copy and `REG_DEP_ANTI` on the store that consumes
            it; sched.c can no longer hoist the loads above the store, which is exactly what the ASM_KEEP
            was buying, and the copy still coalesces with the call result ($2).  In the narrow form the
            merged pseudo gains the host's references (10 refs / 18 insns against 5 / 9), so global.c's
            `floor_log2(refs) * refs / live_length` priority ranks it ABOVE the signed height and the two
            global registers swap into retail's order - width and allocation priority move together.
            t81_reuselocal is the narrower ancestor: it hosts an arm-confined local on a dead local of the
            SAME declared type, so it sees neither a call-result pointer as the dying variable nor a merge
            across two declared types; natural.host_candidates only fires where the pin is an ASM_REG on
            the variable's own declaration and only onto word-sized hosts.
CANDIDATES  per pin, pairs (A, B) of plain scalar locals where A's last mention is at the pin (or within
            three lines of it), A's last plain write opens its tail, nothing but pins, braces, comments and
            declarations stands between A's last mention and B's first assignment, that assignment is a
            plain write, B is not mentioned before it, and neither is address-taken, volatile, static,
            const or an array (A may be a parameter that is never mentioned again).  A's tail is renamed to
            B - forms cheapest first: `rename` (same declared type), `retype` (same-width integer types,
            B's declaration winning), `cast` (pointer <-> integer, with `(tyB)` on the write and `(tyA)` at
            the pointer reads) and `union` (a one-word union with a field per meaning, the form the lane
            shipped); A's declaration is dropped when its every mention was in the tail.  Two more forms:
            `split`, where the dying value was never named at all (`lvalue = call(...);` next to the pin
            becomes `B = (tyB)call(...); lvalue = (tyA)B;`), and `narrow`, a register-pinned wide local
            whose writes are `V = *(volatile u16 *)...` renamed onto an existing local of that narrow
            type, its declaration (and with it the pin) dropped.  B may itself carry an `ASM_REG` on its
            declaration - then the pin is not next to A's death but on B, and every erase plan must take
            it.  The window's pins are erased jointly and singly, then the function's jointly; candidates
            are ranked by cc1 listing distance to the pinned text and only the nearest reach `vf`.
            Refused: a kept pin whose text would change, a rewrite that leaves the tail's pins standing, an
            A mentioned after its tail by anything but a plain write, a B mentioned before its birth or
            declared with an initialiser, and (for the narrow form) a host of a different width.
            LIVENESS is textual: A dead after its tail is proved from the text, but the narrow form's host
            cannot be (dungeon/func_80D66164's `part_flags` is read on the OTHER side of the branch that
            writes the merged value - only the CFG says the two lifetimes are disjoint).  The byte gate is
            what settles it: a candidate that compiles to retail's bytes has not changed the program.
"""
import difflib, os, re, sys
from collections import Counter
from pathlib import Path
sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
from pin_census import sites_of, asm_blocker
from pin_sites import erase_many
try:
    from . import natural as N
    from . import screen
    from .t81_reuselocal import WRITE_RE, NOSHARE
except ImportError:
    import natural as N
    import screen
    from t81_reuselocal import WRITE_RE, NOSHARE

MAX_CANDS = 24
MAX_LISTINGS = 300
MAX_VERIFY = 6
GAP = 10                       # lines between A's death and B's birth
PIN_NEAR = 3                   # A's last mention must be this close to a pin

ID = r"[A-Za-z_]\w*"
WORD = N.WORD_S | N.WORD_U
SMALL = N.SMALL
FORM_RANK = {"rename": 0, "retype": 1, "cast": 2, "split": 3, "hoist": 4, "union": 5, "narrow": 6}
FILLER_RE = re.compile(r"^[ \t]*(?:[{}]|/\*.*|//.*)?[ \t]*$")
VOLREAD_RE = re.compile(r"\*[ \t]*\([ \t]*volatile[ \t]+(?P<ty>%s)[ \t]*\*[ \t]*\)" % ID)
# natural.VDECL_RE lets the pointer run be empty, so `dx = -dx;` reads as a declaration of `x` of type
# `d`: this generator's rescan insists on a real separator between the base type and the name.
DECL_RE = re.compile(r"^(?P<i>[ \t]*)(?P<q>(?:(?:register|const|volatile|static|unsigned|signed|struct"
                     r"|union|enum)[ \t]+)*)(?P<base>%s)(?P<ptr>(?:[ \t]*\*)+[ \t]*|[ \t]+)(?P<n>%s)"
                     r"[ \t]*(?P<arr>\[[^\]]*\][ \t]*)?(?P<asm>ASM_REG[ \t]*\([^)]*\)[ \t]*)?"
                     r"(?:=[ \t]*(?P<init>[^;]*?))?[ \t]*;[ \t]*$" % (ID, ID))
CALLSTART_RE = re.compile(r"^[ \t]*%s[ \t]*\(" % ID)
PINONLY_RE = re.compile(r"^[ \t]*ASM_\w+[ \t]*\([^;]*\)[ \t]*;[ \t]*$")
CALL_RE = re.compile(r"(?<![\w.])(?<!->)%s[ \t]*\(" % ID)


# ------------------------------------------------------------------ text helpers

def scope_decls(fn):
    """Every declaration of the function.

    This used to rescan the whole body for single-line declarations, because natural's reader
    stopped a block's prologue at the first line it could not parse (`static void *const
    item_targets[7] = {` in the item family) and hid every declaration below it.  natural reads
    those shapes itself since round 68, and the rescan then only ADDED wrong ones: a declaration
    in a `#ifdef NON_MATCHING` arm no scored build compiles, and a multiplication statement
    (`second_quotient * limit_units;`) that a declarator regex cannot tell from a declaration.
    Measured over the 1,123 pinned rows, the rescan's remaining 67 entries were all of those two
    kinds, so it is gone."""
    out = [dict(d) for ds in fn.decls.values() for d in ds]
    for d in fn.params:
        out.append(dict(d))
    return out


def _resolve(decls, name, k):
    """The declaration a mention of `name` on line k refers to (None: a global)."""
    best = None
    for d in decls:
        if d["name"] != name:
            continue
        if d.get("param"):
            best = best or d
            continue
        o, c = d["block"]
        if o < k < c and d["line"] < k and (best is None or best.get("param") or o > best["block"][0]):
            best = d
    return best


def _mentions(fn, d, decls=None):
    """Lines of the function that mention declaration `d` (its own declaration excluded)."""
    decls = decls if decls is not None else scope_decls(fn)
    rx = N._occ(d["name"])
    o, c = d["block"]
    start = (fn.a + 1) if d.get("param") else d["end"] + 1
    own = {k for x in decls if x["name"] == d["name"] for k in range(x["line"], x["end"] + 1)}
    out = []
    for k in range(start, min(c, fn.b)):
        if k in own or not rx.search(fn.ml[k]):
            continue
        if _resolve(decls, d["name"], k) is not d:
            continue
        out.append(k)
    return out


def _plain_write(ml, k, name):
    m = WRITE_RE.match(ml[k])
    return bool(m and m.group("n") == name)


def _usable(fn, d, text_masked):
    """A plain scalar local this generator may rename or drop."""
    return (d.get("single") and d.get("ty") and not d.get("arr") and not (d["quals"] & NOSHARE)
            and not N._addr_taken(text_masked, d["name"]))


def _whole_operand(line, s, e):
    """True when the mention at [s, e) is a whole operand: a cast needs no parentheses round it."""
    before, after = line[:s].rstrip(), line[e:].lstrip()
    return (before.endswith(("=", "(", ",", "return")) and not before.endswith(("==", "!=", ">=", "<="))
            and (after.startswith((";", ")", ",")) or after == ""))


def _spell(ty):
    """`void*` written as a cast: `void *`."""
    return re.sub(r"(?<=\w)\*", " *", ty)


def _cast_write(line, m, bname, tyb):
    """`A = rhs;` -> `B = (tyB)rhs;` (parenthesised unless the right-hand side is a call or a term)."""
    eq = line.find("=", m.end())
    if eq < 0:
        return None
    rhs = line[eq + 1:]
    body = rhs.strip()
    semi = body.endswith(";")
    inner = body[:-1].strip() if semi else body
    if not inner:
        return None
    if semi and not (CALLSTART_RE.match(inner) or N._term(inner)):
        new_rhs = " (%s)(%s);" % (_spell(tyb), inner)
    else:
        if not semi and not CALLSTART_RE.match(inner):
            return None                                   # a multi-line right-hand side we cannot bracket
        new_rhs = " (%s)%s" % (_spell(tyb), rhs.strip() if semi else rhs.lstrip())
    return line[:m.start()] + bname + line[m.end():eq] + "=" + new_rhs


def _rename_lines(fn, lines, name, repl, edits, skip=()):
    """`name` replaced by `repl` on each of `lines` (text lines, masked positions)."""
    rx = N._occ(name)
    for k in lines:
        if k in skip:
            continue
        ln = edits.get(k, N._nl(fn.t.lines[k]))
        for m in reversed(list(rx.finditer(fn.ml[k]))):
            ln = ln[:m.start()] + repl + ln[m.end():]
        edits[k] = ln
    return edits


# ------------------------------------------------------------------ the pair finder

def _tyclass(ty):
    if ty.endswith("*"):
        return "p"
    if ty in WORD:
        return "w"
    if ty in SMALL:
        return "n"
    return "?"


def _forms(tya, tyb):
    """The merge forms available for a dying `tya` hosted in `tyb`, cheapest first."""
    ca, cb = _tyclass(tya), _tyclass(tyb)
    if tya == tyb:
        return ["rename"]
    if ca == cb == "w":
        return ["retype"]
    if {ca, cb} == {"p", "w"}:
        return ["cast", "union"]
    if ca == "w" and cb == "n":
        return ["retype"]
    return []


def pairs(text):
    """[(fn, A decl, B decl, LW, LA, LB, forms)] for every consecutive-lifetime pair near a pin."""
    t = N._T(text)
    out = []
    sites = sites_of(text)
    for fn in N._functions(t):
        pinlines = [s[5] - 1 for s in sites if fn.a < s[5] - 1 < fn.b]
        if not pinlines:
            continue
        masked = "\n".join(fn.ml[fn.a:fn.b + 1])
        scope = scope_decls(fn)
        decl_lines = {d["line"] for d in scope}
        pinnames = {n for s in sites if s[0] == "stmt" and fn.a < s[5] - 1 < fn.b
                    for n in re.findall(ID, s[2] or "")}
        info = {}
        for d in scope:
            if not _usable(fn, d, masked):
                continue
            ms = _mentions(fn, d, scope)
            if ms:
                info[id(d)] = (d, ms)
        for d, ms in info.values():
            LA = max(ms)
            near_pin = any(abs(p - LA) <= PIN_NEAR for p in pinlines)
            writes = [k for k in ms if _plain_write(fn.ml, k, d["name"])]
            LW = max([k for k in writes if k <= LA] or [-1])
            if LW < 0 or (d.get("init") is not None and LW < d["end"]):
                continue
            if any(LW < k <= LA and k in writes for k in ms):
                continue                                          # a second write inside the tail
            wl = fn.ml[LW]
            if len(list(N._occ(d["name"]).finditer(wl))) > 1:
                continue                                          # `A = f(A)`: the tail reads A's own
            tail = [k for k in ms if LW <= k <= LA]
            outside = [k for k in ms if k < LW]
            if [k for k in ms if k > LA]:
                continue                                          # A is not dead after its tail
            for e, msb in info.values():
                if e is d or e.get("param") or e["name"] == d["name"]:
                    continue
                if (min(msb) == LA and near_pin and _plain_write(fn.ml, LA, e["name"])
                        and e.get("init") is None and not e["pinned"]
                        and e["block"][0] < LA and max(msb) < e["block"][1]
                        and d["block"][0] < LA and max(msb) < d["block"][1]):
                    # `B = f(A);` on A's last line: the value's own source hosts it, so B is the one
                    # renamed away (dungeon/func_80E8D490, `target_coord = tile_coord << 6`).
                    rev = _forms(e["ty"], d["ty"])
                    if rev and not [k for k in msb if _plain_write(fn.ml, k, e["name"]) and k > LA]:
                        out.append((fn, scope, e, d, LA, max(msb), LA, msb, [], rev))
                if e["name"] in pinnames or e.get("init") is not None:
                    continue
                if not near_pin and not e["pinned"]:
                    continue            # the pin is either where A dies or on B's own declaration
                if not (e["line"] < LW and e["block"][0] < LW and LA < e["block"][1]):
                    continue            # B's declaration must be in scope over the whole of A's tail
                LB = min(msb)
                if not (LA < LB <= LA + GAP) or not _plain_write(fn.ml, LB, e["name"]):
                    continue
                if N._occ(d["name"]).search(fn.ml[LB]):
                    continue                                      # `B = A;` is a copy, not a merge
                if any(not (FILLER_RE.match(fn.ml[k]) or k in pinlines or k in decl_lines)
                       for k in range(LA + 1, LB)):
                    continue                                      # a statement stands in between
                forms = _forms(d["ty"], e["ty"])
                if e["pinned"]:
                    # B is register-pinned on its own declaration: hosting A in it only pays with that
                    # ASM_REG gone, so the plan must erase it, and the union form (which rewrites the
                    # declaration) is out.
                    forms = [f for f in forms if f != "union"]
                if forms:
                    out.append((fn, scope, d, e, LW, LA, LB, tail, outside, forms))
    return out


def _build(fn, scope, d, e, LW, LA, tail, outside, form, pinlines):
    """The merged text for one (pair, form), or None."""
    t, edits, drop = fn.t, {}, set()
    # a line that is nothing but a statement pin disappears with the erase, so it is left alone; a pin
    # ON a declaration keeps its text when erased, so a mention of A there must still be renamed
    # (dungeon/func_818B0E10: `register s32 shade_scale ASM_REG("$4") = color_scale;`).
    skip = {k for k in pinlines if PINONLY_RE.match(fn.ml[k])}
    tail_lines = [k for k in tail if k not in skip]
    if form in ("rename", "retype"):
        _rename_lines(fn, tail_lines, d["name"], e["name"], edits)
    elif form == "cast":
        for k in tail_lines:
            ln = N._nl(t.lines[k])
            hits = list(N._occ(d["name"]).finditer(fn.ml[k]))
            if not hits:
                continue
            if _plain_write(fn.ml, k, d["name"]):
                if len(hits) != 1:
                    return None                        # a cast may never land on the left of an `=`
                new = _cast_write(ln, hits[0], e["name"], e["ty"])
                if new is None:
                    return None
                edits[k] = new
                continue
            for m in reversed(hits):
                rep = "(%s)%s" % (_spell(d["ty"]), e["name"])
                if not _whole_operand(fn.ml[k], m.start(), m.end()):
                    rep = "(%s)" % rep
                ln = ln[:m.start()] + rep + ln[m.end():]
            edits[k] = ln
    elif form == "union":
        ptr, val = (d, e) if d["ty"].endswith("*") else (e, d)
        uln = "%sunion { %s pointer; %s value; } %s;" % (e["ind"], _spell(ptr["ty"]), val["ty"], e["name"])
        edits[e["line"]] = uln
        pfield = "%s.pointer" % e["name"]
        vfield = "%s.value" % e["name"]
        _rename_lines(fn, tail_lines, d["name"], pfield if d is ptr else vfield, edits)
        body = [k for k in _mentions(fn, e, scope) if k != e["line"]]
        _rename_lines(fn, body, e["name"], vfield if d is ptr else pfield, edits, skip=skip)
    else:
        return None
    if not edits:
        return None
    if not outside and d["single"] and d["line"] == d["end"] and d.get("init") is None:
        drop.add(d["line"])                                        # A was only ever the tail
    return t.build(edits, drop)


def merge_candidates(text):
    """[(label, cand, (LW, LA), form, must)] for every admissible consecutive-lifetime merge."""
    sites = sites_of(text)
    out = []
    for fn, scope, d, e, LW, LA, LB, tail, outside, forms in pairs(text):
        pinlines = [s[5] - 1 for s in sites if fn.a < s[5] - 1 < fn.b]
        must = [e["line"] + 1] if e["pinned"] else []
        for form in forms:
            cand = _build(fn, scope, d, e, LW, LA, tail, outside, form, pinlines)
            if cand is None:
                continue
            label = "%s:%s->%s@%d" % (form, d["name"], e["name"], LW + 1)
            out.append((label, cand, (LW, LA), form, must))
    return out


# ------------------------------------------------------------------ the unnamed call result

def split_candidates(text):
    """[(label, cand, window, 'split', must)]: `lvalue = call(...);` next to a pin, with the call
    result named as the local the next statement writes - `B = (tyB)call(...); lvalue = (tyA)B;` -
    so the stored value and B's first value share one pseudo (the item-target rows whose call result
    was never given a name: dungeon/func_80F89240, func_80A1F0C4, func_810AF0B4)."""
    t = N._T(text)
    sites = sites_of(text)
    out = []
    for fn in N._functions(t):
        pinlines = [s[5] - 1 for s in sites if fn.a < s[5] - 1 < fn.b]
        if not pinlines:
            continue
        scope = scope_decls(fn)
        decl_lines = {d["line"] for d in scope}
        masked = "\n".join(fn.ml[fn.a:fn.b + 1])
        pinnames = {n for s in sites if s[0] == "stmt" and fn.a < s[5] - 1 < fn.b
                    for n in re.findall(ID, s[2] or "")}
        for LS, LE, lv, rhs in _stores(fn):
            near_pin = any(LE <= p <= LE + PIN_NEAR for p in pinlines)
            for e in scope:
                if e.get("param") or not _usable(fn, e, masked) or e.get("init") is not None:
                    continue
                if e["name"] in pinnames or N._occ(e["name"]).search("\n".join(fn.ml[LS:LE + 1])):
                    continue
                if not near_pin and not e["pinned"]:
                    continue
                ms = _mentions(fn, e, scope)
                if not ms:
                    continue
                LB = min(ms)
                if not (LE < LB <= LE + GAP) or not _plain_write(fn.ml, LB, e["name"]):
                    continue
                if not (e["line"] < LS and e["block"][0] < LS and LE < e["block"][1]):
                    continue            # B must be in scope where the call now lands
                if any(not (FILLER_RE.match(fn.ml[k]) or k in pinlines or k in decl_lines)
                       for k in range(LE + 1, LB)):
                    continue
                cls = _tyclass(e["ty"])
                if cls not in ("w", "p"):
                    continue
                ind = N._ind(fn.t.lines[LS])
                head = "%s%s = %s%s" % (ind, e["name"], "" if cls == "p" else "(%s)" % e["ty"],
                                        rhs.lstrip())
                for cast in (["(void *)", ""] if cls == "w" else [""]):
                    tail_line = "%s%s = %s%s;" % (ind, lv.strip(), cast, e["name"])
                    edits = {LS: head + "\n" + tail_line}
                    cand = t.build(edits, set(range(LS + 1, LE + 1)))
                    out.append(("split:%s@%d%s" % (e["name"], LS + 1, "-cast" if cast else ""),
                                cand, (LS, LE), "split", [e["line"] + 1] if e["pinned"] else []))
    return out


def hoist_candidates(text):
    """[(label, cand, window, 'hoist', must)]: the same unnamed call result, where the coordinates are
    a braced block's initialised declarations (dungeon/func_80D13E4C, func_80AF1A80).  The call moves
    into the block as the first declaration's initialiser, the store follows it, and every declaration
    keeps its value as a plain assignment so no load rises above the store."""
    t = N._T(text)
    sites = sites_of(text)
    out = []
    for fn in N._functions(t):
        pinlines = [x[5] - 1 for x in sites if fn.a < x[5] - 1 < fn.b]
        if not pinlines:
            continue
        scope = scope_decls(fn)
        masked = "\n".join(fn.ml[fn.a:fn.b + 1])
        for LS, LE, lv, rhs in _stores(fn):
            if not any(LE <= p <= LE + PIN_NEAR for p in pinlines):
                continue
            k = LE + 1
            while k < fn.b and (FILLER_RE.match(fn.ml[k]) and "{" not in fn.ml[k] or k in pinlines):
                k += 1
            if k >= fn.b or fn.ml[k].strip() != "{":
                continue
            blk = (k, N._close(fn.ml, k))
            if blk[1] is None or blk[1] >= fn.b:
                continue
            decls = [d for d in scope if d["block"] == blk and d["line"] < first_stmt(fn, blk)]
            if not decls or any(not d["single"] or d["arr"] or d["pinned"] or (d["quals"] & NOSHARE)
                                or d["line"] != d["end"] for d in decls):
                continue
            inits = [d for d in decls if d["init"] is not None]
            if not inits or any(CALL_RE.search(d["init"]) for d in inits):
                continue
            b = inits[0]
            cls = _tyclass(b["ty"])
            if cls not in ("w", "p") or N._addr_taken(masked, b["name"]):
                continue
            body = first_stmt(fn, blk)
            for cast in (["(void *)", ""] if cls == "w" else [""]):
                edits, ins = {}, []
                for d in inits:
                    line = N._nl(t.lines[d["line"]])
                    edits[d["line"]] = line[:line.index("=")].rstrip() + ";"
                if b is inits[0]:
                    line = N._nl(t.lines[b["line"]])
                    edits[b["line"]] = "%s %s%s" % (line[:line.index("=")].rstrip() + " =",
                                                    "" if cls == "p" else "(%s)" % b["ty"],
                                                    rhs.strip())
                ind = b["ind"]
                ins = ["%s%s = %s%s;" % (ind, lv.strip(), cast, b["name"])]
                ins += ["%s%s = %s;" % (ind, d["name"], d["init"]) for d in inits]
                cand = t.build(edits, set(range(LS, LE + 1)), {body - 1: ins})
                out.append(("hoist:%s@%d%s" % (b["name"], LS + 1, "-cast" if cast else ""),
                            cand, (LS, blk[1]), "hoist", []))
    return out


def first_stmt(fn, blk):
    """The first line of `blk` that is not a declaration."""
    o, c = blk
    k = o + 1
    while k < c:
        s = fn.ml[k]
        if s.strip() and not s.lstrip().startswith("#") and not DECL_RE.match(s):
            return k
        k += 1
    return c


def _stores(fn):
    """[(first line, last line, lvalue, right-hand side)] of every `<lvalue> = <call>(...);` statement
    whose destination is memory (not a plain local) and whose right-hand side is one call."""
    out = []
    k = fn.a + 1
    while k < fn.b:
        s = fn.ml[k]
        if "=" not in s or s.lstrip().startswith(("#", "}")) or N.CONTROL_RE.match(s):
            k += 1
            continue
        end = k
        while end < fn.b and not fn.ml[end].rstrip().endswith(";"):
            end += 1
            if end - k > 8:
                break
        if end >= fn.b or not fn.ml[end].rstrip().endswith(";"):
            k += 1
            continue
        stmt = "\n".join(fn.ml[k:end + 1])
        if fn.inner.get(k) != fn.inner.get(end):
            k = end + 1
            continue
        eq = _top_eq(stmt)
        if eq is not None:
            lv, rhs = stmt[:eq], stmt[eq + 1:]
            body = rhs.strip()
            if (re.search(r"[\[\]>.*]", lv) and not re.search(r"[=<>!+\-*/%&|^]", lv.strip()[-1:])
                    and CALLSTART_RE.match(body) and body.endswith(";")
                    and not re.match(r"^[ \t]*%s[ \t]*$" % ID, lv)
                    and _paired(body) and _paired(lv)):
                real = "\n".join(N._nl(x) for x in fn.t.lines[k:end + 1])
                out.append((k, end, lv, real[eq + 1:]))
        k = end + 1
    return out


def _top_eq(stmt):
    """Index of the statement's top-level `=` (None when there is none)."""
    depth = 0
    for i, ch in enumerate(stmt):
        if ch in "([":
            depth += 1
        elif ch in ")]":
            depth -= 1
        elif ch == "=" and depth == 0 and stmt[i + 1:i + 2] != "=" and stmt[i - 1:i] not in (
                "=", "!", "<", ">", "+", "-", "*", "/", "%", "&", "|", "^"):
            return i
    return None


def _paired(s):
    return s.count("(") == s.count(")") and s.count("[") == s.count("]")


# ------------------------------------------------------------------ the narrow staging form

def narrow_candidates(text):
    """[(label, cand, window, 'narrow')]: a register-pinned wide local staging a narrow volatile read,
    renamed onto an existing local of that narrow type (its declaration, and with it the pin, dropped)."""
    t = N._T(text)
    out = []
    for s in sites_of(text):
        if s[0] != "reg":
            continue
        k = s[5] - 1
        for fn in N._functions(t):
            if not (fn.a < k < fn.b):
                continue
            masked = "\n".join(fn.ml[fn.a:fn.b + 1])
            scope = scope_decls(fn)
            v = next((x for x in scope if x["line"] == k and x.get("single") and x.get("ty")), None)
            if v is None or v["ty"] not in WORD or v.get("init") is not None or v["line"] != v["end"]:
                continue
            ms = _mentions(fn, v, scope)
            writes = [x for x in ms if _plain_write(fn.ml, x, v["name"])]
            if not writes or N._addr_taken(masked, v["name"]):
                continue
            tys = {m.group("ty") for w in writes for m in [VOLREAD_RE.search(fn.ml[w])] if m}
            if len(tys) != 1:
                continue
            nt = tys.pop()
            if nt not in SMALL or len(tys) > 0:
                continue
            if len(writes) != len(set(writes)) or any(not VOLREAD_RE.search(fn.ml[w]) for w in writes):
                continue
            pinnames = {n for s2 in sites_of(text) if s2[0] == "stmt" and fn.a < s2[5] - 1 < fn.b
                        for n in re.findall(ID, s2[2] or "")}
            hosts = [x for x in scope
                     if x is not v and not x.get("param") and x.get("single") and x.get("ty") == nt
                     and not x.get("arr") and not (x["quals"] & NOSHARE) and not x["pinned"]
                     and x.get("init") is None and x["name"] not in pinnames
                     and not N._addr_taken(masked, x["name"]) and _mentions(fn, x, scope)]
            for h in hosts[:4]:
                edits = _rename_lines(fn, ms, v["name"], h["name"], {})
                cand = t.build(edits, {v["line"]})
                out.append(("narrow:%s->%s" % (v["name"], h["name"]), cand,
                            (min(ms), max(ms)), "narrow", []))
    return out


def candidates(text):
    cands = (merge_candidates(text) + split_candidates(text) + hoist_candidates(text)
             + narrow_candidates(text))
    cands.sort(key=lambda c: FORM_RANK.get(c[3], 9))
    seen, out = set(), []
    for label, cand, win, form, must in cands:
        if cand in seen or cand == text:
            continue
        seen.add(cand)
        out.append((label, cand, win, form, must))
    return out[:MAX_CANDS]


# ------------------------------------------------------------------ the generator

def _plans(sites, rs, win, must=()):
    """Erase plans for a rewritten text: the tail's pins (which must go), the window's, then all."""
    lo, hi = win[0] + 1, win[1] + 1
    req = [i for i, s in enumerate(rs) if lo <= s[5] <= hi or s[5] in must]
    near = [i for i, s in enumerate(rs) if lo - 6 <= s[5] <= hi + 6]
    out = []
    if len(rs) < len(sites):
        out.append([])                                             # the rewrite itself dropped a pin
    if req:
        out.append(req)
    if sorted(set(near) | set(req)) not in out and near:
        out.append(sorted(set(near) | set(req)))
    for i in near:
        g = sorted(set(req) | {i})
        if g not in out:
            out.append(g)
    allp = list(range(len(rs)))
    if allp and allp not in out:
        out.append(allp)
    return out


def _kept_ok(sites, cand):
    """No surviving pin's text changed (a kept pin naming a renamed variable is refused)."""
    want, got = Counter((s[1], s[2]) for s in sites), Counter((s[1], s[2]) for s in sites_of(cand))
    return not (got - want)


class T:
    name = "t87_lifetimemerge"
    level = 1
    needs_verify = True

    @staticmethod
    def eligible(text, row, census):
        why = asm_blocker(text)
        if why:
            return why
        if not sites_of(text):
            return "no pins"
        return None if candidates(text) else "no consecutive-lifetime pair near a pin"

    @classmethod
    def apply_verified(cls, text, row, census, vf):
        sites = sites_of(text)
        pins_in = len(sites)
        target = screen.compile_s(row, text)
        if target is None:
            return None, {"refused": "pinned text does not build to a listing", "pins_in": pins_in,
                          "pins_out": pins_in}
        listings = verifies = 0
        best, near, rest, forms = None, None, [], []
        for label, renamed, win, form, must in candidates(text):
            if listings >= MAX_LISTINGS or verifies >= MAX_VERIFY:
                break
            forms.append(form)
            rs = sites_of(renamed)
            for g in _plans(sites, rs, win, must):
                if listings >= MAX_LISTINGS or verifies >= MAX_VERIFY:
                    break
                cand = erase_many(renamed, [rs[i] for i in g], clean_notes=True) if g else renamed
                if len(sites_of(cand)) >= pins_in or not _kept_ok(sites, cand):
                    continue
                lst = screen.compile_s(row, cand)
                listings += 1
                if lst is None:
                    continue
                d = sum(1 for y in difflib.unified_diff(target, lst, lineterm="", n=0)
                        if y[:1] in "+-" and not y.startswith(("---", "+++")))
                near = d if near is None else min(near, d)
                tag = "%s-erase%d" % (label, len(g))
                if d == 0:
                    verifies += 1
                    if vf(cand).get("exact"):
                        best = (cand, tag)
                        break
                else:
                    rest.append((d, len(rest), cand, tag))
            if best:
                break
        if best is None:
            rest.sort(key=lambda x: (x[0], x[1]))
            NEAR_VERIFY = int(os.environ.get("NEAR_VERIFY", "3"))
            for d, _, cand, tag in [x for x in rest if x[0] <= 2][:NEAR_VERIFY]:
                if verifies >= MAX_VERIFY:
                    break
                verifies += 1
                if vf(cand).get("exact"):
                    best = (cand, tag)
                    break
        info = {"listings": listings, "tried": verifies, "pins_in": pins_in, "near": near,
                "forms": ",".join(sorted(set(forms)))}
        if best is None:
            return None, dict(info, pins_out=pins_in)
        return best[0], dict(info, pins_out=len(sites_of(best[0])), step=best[1],
                             form=best[1].split(":")[0])
