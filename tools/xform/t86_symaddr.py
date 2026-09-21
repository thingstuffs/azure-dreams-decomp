"""T86: an address constant respelled as the symbol at that address - at the place, in the type and
at the cell that make the retail HIGH/LO_SUM pair, the local kept or dropped as the shape allows.

APPEARS     a pinned page/base local, parameter or port-arm variable holding an address
            (`base = (u8 *)0x800E0000;`, `base = 0x80080000;`, `base = (u8 *)&D_X + K;`) read later as
            `p = (T *)(base + K);`, `p = (T *)base + K;`, `base += K;` or in operand position
            (`func(..., (u8 *)(base + 0x2E80))`, `((S *)((u8 *)base))->f`).  The lone-erasure census of
            2026-09-21 (`addrconst`, 209 pin sites in 119 rows) shows one residue class: retail's
            `lui %hi` + `addiu %lo` (or a second `addiu` off a held page register) against the erased
            build's `lui`+`ori` / `move`+`ori` - `CHANGED|3-4|-addiu,lui +lui,ori` 89 sites,
            `CHANGED|1-2|-addiu +ori` 62, `-move,ori +ori` 25, `-addiu +move,ori` 19, `-addiu +lui,ori` 14.
RESOLVES    with the keep gone, cse's `fold_rtx` folds the page CONST_INT and the offset into ONE integer
            address, which the MIPS splitter materialises as `lui`+`ori` (t59's `-da` probe: one deciding
            pass in 20 of 20).  Retail's `addiu` is what a RELOCATABLE operand produces: `(const (plus
            (symbol_ref) (const_int K)))` is not an integer cse can fold, so the back end emits `%hi`/`%lo`.
            Naming the symbol is therefore the repair, and three things decide whether it lands:
              * the PLACE - the HIGH register of gcc's HIGH/LO_SUM pair is fixed by the statement's LUID,
                so the symbol statement must stand where the page definition stood (the Opus r58 lane,
                `dungeon/func_800C96AC`: `state = (u16 *)D_80083460;` at the page definition's line, the
                derived statement and the keep gone);
              * the TYPE - the cast the use carries (`(s32 *)base + 0x13` steps 4 bytes, `(s32 *)(base +
                0x13)` steps 1), and whether the local is kept (t54: allocation moves when it is not);
              * the CELL - 2.7.2-cdk / 2.8.x / 2.9x ALWAYS split a symbol address into `lui`+`addiu`,
                FSF 2.7.2 and 2.6.3 emit the atomic `la` macro (measured over all seven stock cells,
                2026-09-21), which can never match a split pair separated by other instructions.  A row
                recorded at a non-splitting cell is therefore screened at 2.7.2-cdk too and, when its
                candidate is byte-exact there, staged as a recipe switch under tools/pin_cells_land.py's
                rules (the CURRENT text must be exact at the new cell as well, or the row is `cell-bound`;
                with T86_STAGE_CELLBOUND=1 a cell-bound row is staged anyway, for the coherence path of
                tools/lanes/land_coherence.sh, which waives that rule and records the trade).
            t29_addrsym deletes the variable and substitutes every use (allocation changes, parameters and
            port-arm variables refused); t54_pagebase respells the definition only; t59_offsetsym respells
            one use only; t77_symplace adds the place but keeps t54's menu and one cell.
CANDIDATES  per base (pinned first) and per use: the derived statement respelled as the symbol at its
            effective address and MOVED to the page definition's slot, one statement earlier, or left in
            place; the definition itself respelled (exact address, or an anchor symbol plus a delta); the
            whole variable substituted (t29's control).  Each text is offered with its window pins erased
            jointly, then singly, then the function's pins jointly; every text is screened by the cc1
            listing against the pinned text's, a listing carrying more `la` than retail's is bucketed for
            the cell phase instead of scored, and only listing-exact texts go to `vf` (at most six a row).
"""
import difflib, os, re, sys, threading, time
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
from common import LEDGER, is_stock_cfg, parse_cfg, read_jsonl, sha_text
from pin_census import sites_of, asm_blocker, unscored_text
from pin_sites import erase_many, fn_bounds, params_of

try:
    from . import t29_addrsym as A
    from .t54_pagebase import definitions, add_externs, masked
    from . import screen
except ImportError:                                    # run as a plain module (tests, gen_drive)
    import t29_addrsym as A
    from t54_pagebase import definitions, add_externs, masked
    import screen

# Measured 2026-09-21 with `p = D_80083460; p += k;` at every stock cell: these emit `lui`+`addiu`
# for a symbol address, 2.6.3 / 2.7.2 (and 2.8.x with -mno-split-addresses) emit the atomic `la`.
SPLIT_CELLS = {"2.7.2-cdk", "2.8.0", "2.8.1", "2.91.66", "2.95.2"}
CDK = "2.7.2-cdk"

MAX_BASES = 6
MAX_USES = 6
MAX_TEXTS = 64
MAX_LISTINGS = int(os.environ.get("T86_LISTINGS", "240"))
MAX_CELL_LISTINGS = int(os.environ.get("T86_CELL_LISTINGS", "50"))
MAX_VERIFY = int(os.environ.get("T86_VERIFY", "6"))
MAX_SECS = float(os.environ.get("T86_SECS", "200"))
# A row whose CURRENT text is not exact at the splitting cell is `cell-bound` under
# tools/pin_cells_land.py rule 2.  tools/lanes/land_coherence.sh lands exactly those (the owner's
# 2026-09-18 rationale: a recipe deviation repaid by a text that is byte-exact at the new recipe,
# every row recorded in ledger/recipe_trades.jsonl), so the switch stages them for THAT lander only.
# Default off: the landing cascade's behaviour is unchanged.
STAGE_CELLBOUND = os.environ.get("T86_STAGE_CELLBOUND", "0") not in ("", "0")

NUM = A.NUM
CAST = r"(?:\(\s*(?:const\s+|volatile\s+|unsigned\s+|signed\s+|struct\s+|union\s+)*[A-Za-z_]\w*(?:\s+long)?\s*\**\s*\)\s*)"
CASTS = r"(?P<cast>%s*)" % CAST
PIN_LINE = re.compile(r"^\s*(?:ASM_[A-Z0-9_]+\s*\(|/\*)")
LABEL_LINE = re.compile(r"^\s*(?:[A-Za-z_]\w*\s*:(?!:)|case\b|default\s*:)")
INT_TYPES = {"u32", "s32", "int", "long", "unsigned", "unsigned int", "unsigned long", "u16", "s16", "u8", "s8"}


# ------------------------------------------------------------------ cells

def splits(cfg):
    """True when this recipe's cc1 splits a symbol address into lui/addiu."""
    cell, flags = parse_cfg(cfg)
    return cell in SPLIT_CELLS and "-mno-split-addresses" not in flags


def cdk_cfg(cfg):
    """The 2.7.2-cdk recipe with this row's flags (the ledger's own dialect)."""
    _, flags = parse_cfg(cfg)
    rest = [f for f in flags if f != "-G0"]
    head = CDK + ("-G0" if "-G0" in flags else "")
    return head + ((" " + " ".join(rest)) if rest else "")


_MODREC = None
_MODLOCK = threading.Lock()


def module_recipe(row_id):
    """The recipe the row's MODULE is proven at (ledger/module_recipe_census.jsonl `best_recipe`,
    round-55 census): what tools/lanes/land_coherence.sh repays a per-row deviation against."""
    global _MODREC
    with _MODLOCK:
        if _MODREC is None:
            mods = {r["id"]: r.get("module") for r in read_jsonl(LEDGER / "modules.jsonl")}
            best = {(r.get("container"), r.get("module")): r.get("best_recipe")
                    for r in read_jsonl(LEDGER / "module_recipe_census.jsonl")}
            _MODREC = {rid: best.get((rid.split("/")[0], m)) for rid, m in mods.items() if m}
    return _MODREC.get(row_id)


def target_cells(row):
    """The splitting recipes to screen a non-splitting row's candidates at: 2.7.2-cdk with the row's
    own flags, and (for the coherence path) the module's own proven recipe."""
    out = [cdk_cfg(row["cfg"])]
    if STAGE_CELLBOUND:
        m = module_recipe(row["id"])
        if m and m != row["cfg"] and m not in out and is_stock_cfg(m) and splits(m):
            out.append(m)
    return out


def at_cfg(row, cfg):
    """A copy of the row recorded at `cfg` (verify reads cfg for overlays, cell/flags for slus)."""
    cell, flags = parse_cfg(cfg)
    return dict(row, cfg=cfg, cell=cell, flags=" ".join(flags))


def family(label):
    """The form family a candidate label belongs to ('v:move@def/one32' -> 'move@def')."""
    form = label.split(":", 1)[1] if ":" in label else label
    return re.sub(r"@\d+$", "", form.split("/")[0])


def la_count(listing):
    return sum(1 for l in listing if l.startswith("la "))


# ------------------------------------------------------------------ types

def var_type(text, var, pos):
    """(base type, pointer depth) of a local or parameter, or (None, 0)."""
    decl = A.decls_of(text, var)
    if decl:
        ty, ptr, _ = decl[0]
        return ty, ptr
    t = masked(text)
    fb = fn_bounds(t, min(pos, len(t) - 1))
    if fb:
        p = params_of(t, fb[0]).get(var)
        if p:
            return p[0], 1 if p[1] else 0
    return None, 0


def type_str(ty, ptr):
    if ty is None:
        return None
    return ty + (" " + "*" * ptr if ptr else "")


def scale_of(ty, ptr):
    if ptr == 1:
        return A.ELEMSIZE.get(ty, 1)
    if ptr >= 2:
        return 4
    return 1


def cast_type(cast):
    """The innermost cast written in front of a use ('(u16 *)' -> ('u16', 1))."""
    if not cast:
        return None, 0
    m = list(re.finditer(r"\(\s*((?:const\s+|volatile\s+|unsigned\s+|signed\s+|struct\s+|union\s+)*[A-Za-z_]\w*(?:\s+long)?)\s*(\**)\s*\)", cast))
    if not m:
        return None, 0
    last = m[-1]
    return re.sub(r"\s+", " ", last.group(1).strip()), len(last.group(2))


def sym_as(text, addr, ty, ptr, ext):
    """The symbol at `addr` spelled as type (ty, ptr): a pointer type casts, an integer type casts too."""
    want = type_str(ty, ptr)
    if ptr:
        return A.sym_expr(text, addr, want, ext)
    base = A.sym_expr(text, addr, None, ext)
    if ty in INT_TYPES:
        return "(%s)%s" % (ty, base)
    return base


# ------------------------------------------------------------------ bases and uses

def pinned_names(text):
    out = set()
    for s in sites_of(text):
        out.update(re.findall(r"\b[A-Za-z_]\w*\b", text[s[3]:s[4]]))
    return out


def bases(text):
    """Address bases defined in the scored arm and reachable by a pin: literals and symbol pages."""
    t = masked(text)
    pins = pinned_names(text)
    out, seen = [], set()
    for d in definitions(text):                                   # `v = <cast>*0x8XXXXXXX;`
        if (d["var"], d["pos"]) in seen:
            continue
        seen.add((d["var"], d["pos"]))
        out.append(dict(d, kind="literal"))
    for m in re.finditer(A.SYMDEF_ANY_RE, t, re.M):               # `v = (u8 *)&D_X + K;`
        val = A.sym_value(text, m.group(2))
        if val is None or (m.group(1), m.start()) in seen:
            continue
        seen.add((m.group(1), m.start()))
        out.append(dict(var=m.group(1), value=val, start=m.start(2), end=m.end(2), pos=m.start(), kind="symbol"))
    keep = []
    for b in out:
        v = b["var"]
        if v in pins:
            b["pinned"] = True
        else:
            near = [ln for ln in t.split("\n") if re.search(r"\b%s\b" % re.escape(v), ln)]
            b["pinned"] = any(n in pins for ln in near for n in re.findall(r"\b[A-Za-z_]\w*\b", ln) if n != v)
        if b["pinned"]:
            keep.append(b)
    keep.sort(key=lambda b: (b["var"] not in pins, b["pos"]))
    return keep[:MAX_BASES]


def _deriv_res(V):
    return [
        ("paren", re.compile(r"^(?P<ind>[ \t]*)(?P<x>[A-Za-z_]\w*)\s*=\s*%s\(\s*%s%s\s*(?P<op>[-+])\s*(?P<k>%s)\s*\)\s*;[ \t]*$"
                             % (CASTS, CAST + "*", V, NUM))),
        ("flat", re.compile(r"^(?P<ind>[ \t]*)(?P<x>[A-Za-z_]\w*)\s*=\s*%s%s\s*(?P<op>[-+])\s*(?P<k>%s)\s*;[ \t]*$" % (CASTS, V, NUM))),
        ("copy", re.compile(r"^(?P<ind>[ \t]*)(?P<x>[A-Za-z_]\w*)\s*=\s*%s\(?\s*%s\s*\)?\s*;[ \t]*$" % (CASTS, V))),
    ]


def _bump_res(V):
    return [
        ("bump", re.compile(r"^(?P<ind>[ \t]*)\(?%s\)?\s*(?P<op>[-+])=\s*(?P<k>%s)\s*;[ \t]*$" % (V, NUM))),
        ("self", re.compile(r"^(?P<ind>[ \t]*)\(?%s\)?\s*=\s*%s\(?\s*%s\s*\)?\s*(?P<op>[-+])\s*(?P<k>%s)\s*;[ \t]*$" % (V, CASTS, V, NUM))),
    ]


def uses(text, b):
    """Every read of the base after its definition, until it is written again or its function ends."""
    t = masked(text)
    lines = t.split("\n")
    V = re.escape(b["var"])
    fb = fn_bounds(t, min(b["pos"], len(t) - 1))
    l0 = t.count("\n", 0, b["pos"])
    lend = t.count("\n", 0, fb[1]) if fb else len(lines) - 1
    bty, bptr = var_type(text, b["var"], b["pos"])
    bscale = scale_of(bty, bptr)
    derivs, bumps = _deriv_res(V), _bump_res(V)
    out = []
    for i in range(l0 + 1, min(lend, len(lines))):
        ln = lines[i]
        if not re.search(r"\b%s\b" % V, ln) or PIN_LINE.match(ln):
            continue
        hit = None
        for tag, rx in derivs:
            m = rx.match(ln)
            if not m:
                continue
            k = int(m.group("k"), 0) if "k" in m.groupdict() and m.group("k") else 0
            sgn = -1 if (m.groupdict().get("op") == "-") else 1
            cty, cptr = cast_type(m.group("cast"))
            step = scale_of(cty, cptr) if (tag == "flat" and cptr) else bscale
            ty, ptr = (cty, cptr) if cty else var_type(text, m.group("x"), b["pos"])
            hit = dict(kind="deriv", form=tag, line=i, ind=m.group("ind"), lhs=m.group("x"),
                       addr=(b["value"] + sgn * k * step) & 0xFFFFFFFF, ty=ty, ptr=ptr, stmt=ln)
            break
        if hit is None:
            for tag, rx in bumps:
                m = rx.match(ln)
                if not m:
                    continue
                k = int(m.group("k"), 0)
                sgn = -1 if m.group("op") == "-" else 1
                hit = dict(kind="bump", form=tag, line=i, ind=m.group("ind"), lhs=b["var"],
                           addr=(b["value"] + sgn * k * bscale) & 0xFFFFFFFF, ty=bty, ptr=bptr, stmt=ln)
                break
        if hit is None:                                        # an operand use inside a larger expression
            m = re.search(r"\(\s*%s\s*(?P<op>[-+])\s*(?P<k>%s)\s*\)|\b%s\b\s*(?P<op2>[-+])\s*(?P<k2>%s)|\b%s\b"
                          % (V, NUM, V, NUM, V), ln)
            if not m:
                continue
            k = int(m.group("k") or m.group("k2") or "0", 0)
            sgn = -1 if (m.group("op") or m.group("op2")) == "-" else 1
            hit = dict(kind="operand", form="operand", line=i, ind="", lhs=None, span=(m.start(), m.end()),
                       addr=(b["value"] + sgn * k * bscale) & 0xFFFFFFFF, ty=bty, ptr=bptr, stmt=ln)
        out.append(hit)
        if hit["kind"] == "bump" or re.match(r"^\s*\(?%s\)?\s*=" % V, ln):
            break                                              # the base is written again: stop here
        if len(out) >= MAX_USES:
            break
    return out


# ------------------------------------------------------------------ candidate texts

def _stmt_line(lines, i):
    s = lines[i].strip()
    return bool(s) and s.endswith(";") and "{" not in s and "}" not in s and not s.startswith("#")


def _balanced(lines, a, b):
    """The two lines sit in the same block: braces between them balance and never close past it."""
    depth = 0
    for i in range(min(a, b), max(a, b)):
        for ch in lines[i]:
            if ch == "{":
                depth += 1
            elif ch == "}":
                depth -= 1
                if depth < 0:
                    return False
        if LABEL_LINE.match(lines[i]):
            return False
    return depth == 0


def _other_refs(text, t, var, skip_lines):
    """Non-pin READS of the base outside the given lines (its declarations are not readers)."""
    decl = {t.count("\n", 0, a) for _ty, _p, (a, _b) in A.decls_of(text, var)}
    n = 0
    for i, ln in enumerate(t.split("\n")):
        if i in skip_lines or i in decl or PIN_LINE.match(ln):
            continue
        n += len(re.findall(r"\b%s\b" % re.escape(var), ln))
    return n


def use_texts(text, b, u):
    """Texts where one use names the symbol, at each position on the axis."""
    t = masked(text)
    lines = text.split("\n")
    mlines = t.split("\n")
    dline = t.count("\n", 0, b["pos"])
    out = []
    ext = set()
    if u["kind"] == "operand":
        expr = sym_as(text, u["addr"], u["ty"], u["ptr"], ext)
        ln = lines[u["line"]]
        a, z = u["span"]
        new_line = ln[:a] + expr + ln[z:]
        body = lines[:u["line"]] + [new_line] + lines[u["line"] + 1:]
        out.append(("opsym@%d" % (u["line"] + 1), add_externs("\n".join(body), ext), [b["var"]], [u["line"]]))
        return out

    expr = sym_as(text, u["addr"], u["ty"], u["ptr"], ext)
    stmt_body = "%s = %s;" % (u["lhs"], expr)
    keep_def = _other_refs(text, t, b["var"], {dline, u["line"]}) > 0 or u["kind"] == "bump"
    def_own_line = mlines[dline].strip().endswith(";") and mlines[dline].strip().startswith(("(", b["var"]))

    # in place (the local kept), and in place with the definition dropped when nothing else reads it
    here = lines[:u["line"]] + [u["ind"] + stmt_body] + lines[u["line"] + 1:]
    out.append(("inplace@%d" % (u["line"] + 1), add_externs("\n".join(here), ext), [b["var"], u["lhs"]], [u["line"]]))
    if not keep_def and def_own_line:
        drop = [l for i, l in enumerate(here) if i != dline]
        out.append(("inplace-nodef@%d" % (u["line"] + 1), add_externs("\n".join(drop), ext), [b["var"], u["lhs"]], [dline]))

    if not def_own_line or u["line"] <= dline or not _balanced(mlines, dline, u["line"]):
        return out
    # the LHS must not be read between the definition and the use (moving it up would change it)
    if u["lhs"] != b["var"] and any(re.search(r"\b%s\b" % re.escape(u["lhs"]), mlines[i]) for i in range(dline, u["line"])):
        return out
    ind = mlines[dline][:len(mlines[dline]) - len(mlines[dline].lstrip())]
    moved = ind + stmt_body
    # at the definition's own slot: the definition goes when nothing else reads it, else it stays
    body = list(lines)
    del body[u["line"]]
    if keep_def:
        body.insert(dline + 1, moved)
    else:
        body[dline] = moved
    out.append(("move@def", add_externs("\n".join(body), ext), [b["var"], u["lhs"]], [dline]))
    # one statement earlier
    if dline - 1 >= 0 and _stmt_line(mlines, dline - 1) and not re.search(
            r"\b(?:%s|%s)\b" % (re.escape(b["var"]), re.escape(u["lhs"])), mlines[dline - 1]):
        body = list(lines)
        del body[u["line"]]
        if not keep_def:
            del body[dline]
            body.insert(dline - 1, moved)
        else:
            body.insert(dline - 1, moved)
        out.append(("move@def-1", add_externs("\n".join(body), ext), [b["var"], u["lhs"]], [dline - 1]))
    return out


def def_texts(text, b, us):
    """Texts where the base's DEFINITION names a symbol, the local kept (t54's move, exact and anchored)."""
    out = []
    ty, ptr = var_type(text, b["var"], b["pos"])
    if ty is None:
        return out
    ext = set()
    expr = sym_as(text, b["value"], ty, ptr, ext)
    new = text[:b["start"]] + expr + text[b["end"]:]
    dline = text.count("\n", 0, b["pos"])
    out.append(("defsym", add_externs(new, ext), [b["var"]], [dline]))
    seen = set()
    for u in us[:2]:
        a = u["addr"]
        if a == b["value"] or a in seen:
            continue
        seen.add(a)
        ext = set()
        sym = A.sym_expr(text, a, "u8 *", ext)
        delta = (a - b["value"]) & 0xFFFFFFFF
        if delta > 0x7FFF:
            continue
        e = "(%s)(%s - 0x%X)" % (type_str(ty, ptr), sym, delta) if ptr else "(%s)((u8 *)%s - 0x%X)" % (ty, sym, delta)
        out.append(("defanchor-%08X" % a, add_externs(text[:b["start"]] + e + text[b["end"]:], ext), [b["var"]], [dline]))
    return out


def menu(text):
    """(label, text, names, edit_lines) in priority order: the place first, then the spelling."""
    seen = {sha_text(text)}
    usig = unscored_text(text)
    n = 0
    bs = bases(text)
    plan = []
    for b in bs:
        us = uses(text, b)
        for u in us:
            plan.append(("use", b, u, us))
        plan.append(("def", b, None, us))
        plan.append(("all", b, None, us))
    # the moves first (position), then the definition spellings, then the whole-variable control
    order = {"use": 0, "def": 1, "all": 2}
    plan.sort(key=lambda p: (order[p[0]], p[1]["var"] not in pinned_names(text)))
    for kind, b, u, us in plan:
        if n >= MAX_TEXTS:
            return
        try:
            if kind == "use":
                texts = use_texts(text, b, u)
            elif kind == "def":
                texts = def_texts(text, b, us)
            else:
                new, _info = A.rewrite_var(text, b["var"])
                texts = [("allsym", new, [b["var"]], [text.count("\n", 0, b["pos"])])] if new else []
        except Exception:
            continue
        for label, new, names, lines in texts:
            if new is None:
                continue
            h = sha_text(new)
            if h in seen or unscored_text(new) != usig:
                continue
            seen.add(h)
            n += 1
            yield ("%s:%s" % (b["var"], label), new, [x for x in names if x], lines)


# ------------------------------------------------------------------ erasure plans

def pin_plans(newtext, names, edit_lines):
    """The window's pins jointly, then singly, then the function's pins jointly (t71/t74's ladder)."""
    pins = sites_of(newtext)
    if not pins:
        return []
    win = [s for s in pins if any(re.search(r"\b%s\b" % re.escape(n), newtext[s[3]:s[4]]) for n in names)]
    if not win:
        win = [s for s in pins if min(abs(s[5] - 1 - l) for l in edit_lines) <= 3]
    out = []
    if len(win) > 1:
        out.append(("win", win))
    out += [("one%d" % s[5], [s]) for s in win[:3]]
    if len(pins) > len(win):
        out.append(("all", pins))
    elif not win:
        out.append(("all", pins))
    return out


# ------------------------------------------------------------------ the generator

class T:
    name = "t86_symaddr"
    level = 1
    needs_verify = True

    @staticmethod
    def eligible(text, row, census):
        why = asm_blocker(text)
        if why:
            return why
        if not sites_of(text):
            return "no pins"
        bs = bases(text)
        if not bs:
            return "no pin-reachable address base in the scored arm"
        return None

    @classmethod
    def apply_verified(cls, text, row, census, vf):
        t0 = time.time()
        pins_in = len(sites_of(text))
        info = {"pins_in": pins_in, "pins_out": pins_in, "listings": 0, "tried": 0}
        target = screen.compile_s(row, text)
        if target is None:
            return None, dict(info, refused=["pinned text does not build to a listing"])
        la_target = la_count(target)
        seen_txt, seen_lst = set(), {}
        near, la_bucket, best = [], [], {}
        for label, newtext, names, lines in menu(text):
            if info["listings"] >= MAX_LISTINGS or time.time() - t0 > MAX_SECS:
                break
            for tag, group in pin_plans(newtext, names, lines):
                if info["listings"] >= MAX_LISTINGS or time.time() - t0 > MAX_SECS:
                    break
                cand = erase_many(newtext, group, clean_notes=True)
                if len(sites_of(cand)) >= pins_in:
                    continue
                h = sha_text(cand)
                if h in seen_txt:
                    continue
                seen_txt.add(h)
                lst = screen.compile_s(row, cand)
                info["listings"] += 1
                if lst is None:
                    continue
                full = "%s/%s" % (label, tag)
                fam = family(label)
                if la_count(lst) > la_target:
                    la_bucket.append((full, cand))
                    best[fam] = min(best.get(fam, 999), 998)
                    continue
                d = screen.sdiff(target, lst)
                best[fam] = min(best.get(fam, 999), d)
                key = tuple(lst)
                prev = seen_lst.get(key)
                if prev is not None and prev <= len(sites_of(cand)):
                    continue
                seen_lst[key] = len(sites_of(cand))
                near.append((d, len(sites_of(cand)), full, cand))
        info["best"] = best
        info["la_bucket"] = len(la_bucket)
        near.sort(key=lambda q: (q[0], q[1]))
        info["nearest"] = [{"d": d, "label": lab} for d, _p, lab, _c in near[:6]]
        for d, _p, lab, cand in near:
            if d or info["tried"] >= MAX_VERIFY:
                break
            info["tried"] += 1
            if vf(cand).get("exact"):
                return cand, dict(info, step=lab, pins_out=len(sites_of(cand)))
        # equal listings are not proof and unequal ones are not a refutation (screen.py's docstring
        # keeps a moved-`sw` false negative): the nearest two are scored as well, with the cell
        # phase's two verifies held back.
        for d, _p, lab, cand in near:
            if d == 0 or d > 2 or info["tried"] >= MAX_VERIFY - 3:
                continue
            info["tried"] += 1
            if vf(cand).get("exact"):
                return cand, dict(info, step="%s(near%d)" % (lab, d), pins_out=len(sites_of(cand)))

        # ---- the cell phase: an atomic `la` where retail splits (a row at a non-splitting cell)
        if not la_bucket or splits(row["cfg"]):
            info["cell"] = "not-tried" if not la_bucket else "cell-already-splits"
            return None, info
        pool0 = la_bucket + [(lab, c) for d, _p, lab, c in near if d <= 6]
        last = info
        for to in target_cells(row):
            if time.time() - t0 > MAX_SECS or info["tried"] >= MAX_VERIFY:
                break
            rr = at_cfg(row, to)
            tgt = screen.compile_s(rr, text)
            if tgt is None:
                last = dict(info, cell="target-none", cell_to=to)
                continue
            cell_exact, cell_near = [], []
            n = 0
            for lab, cand in pool0:
                if n >= MAX_CELL_LISTINGS or time.time() - t0 > MAX_SECS:
                    break
                lst = screen.compile_s(rr, cand)
                n += 1
                info["listings"] += 1
                if lst is None:
                    continue
                d = screen.sdiff(tgt, lst)
                k = "%s:%s" % (to, family(lab.rsplit("/", 1)[0]))
                best[k] = min(best.get(k, 999), d)
                if d == 0:
                    cell_exact.append((lab, cand))
                elif d <= 3:
                    cell_near.append((d, lab, cand))
            cell_near.sort(key=lambda q: q[0])
            if not cell_exact and not (cell_near and STAGE_CELLBOUND):
                last = dict(info, cell="no-listing-exact", cell_to=to)
                continue
            if info["tried"] >= MAX_VERIFY:
                last = dict(info, cell="verify-budget", cell_to=to)
                break
            info["tried"] += 1
            # pin_cells_land rule 2: the CURRENT text must be exact at the new recipe too.  When it is
            # not, the row is `cell-bound` - landable only through tools/lanes/land_coherence.sh, which
            # waives that rule (owner 2026-09-18) and records the trade; T86_STAGE_CELLBOUND stages those.
            coherent = bool(vf(text, to).get("exact"))
            if not coherent and not STAGE_CELLBOUND:
                last = dict(info, cell="cell-bound: current text not exact at %s" % to, cell_to=to)
                continue
            # a cell-bound row's listing target is a text that is NOT retail at `to`, so listing
            # exactness there proves nothing: the near band is scored as well when the switch is on.
            cands = cell_exact + ([(lab, c) for _d, lab, c in cell_near] if not coherent else [])
            for lab, cand in cands:
                if info["tried"] >= MAX_VERIFY:
                    break
                info["tried"] += 1
                v = vf(cand, to)
                if v.get("total") is not None:
                    info["cell_best_total"] = min(info.get("cell_best_total", 1 << 30), v["total"])
                if v.get("exact"):
                    return cand, dict(info, step=lab, cell="switch" if coherent else "switch-cellbound",
                                      cfg=to, cfg_was=row["cfg"], coherent=coherent,
                                      pins_out=len(sites_of(cand)))
            last = dict(info, cell=("vf-miss" if coherent else "cell-bound-vf-miss"), cell_to=to)
        return None, last
