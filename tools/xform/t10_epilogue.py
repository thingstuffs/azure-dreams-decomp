"""T10: EPILOGUE label-as-call sites become the ordinary C the epilogue jump stands for.

m2c renders a function's own `j <return block>` as a call to a pseudo-function it declares
`__attribute__((noreturn))` (an `ASM_SET`/asm-aliased tail is the same spelling by another name).
`ledger/cache/audit.json` records the site as `cls == LABEL_AS_CALL, kind == "epilogue"`.  The
honest C is a `return`.  Which return is decided by the shape at the site, and whether it is
reachable at all is decided by the cell:

    gcc 2.6.3 / 2.7.2 / 2.7.2-cdk keep the `j <return label>` in every shape;
    gcc >= 2.8.0 collapses it into an inline `jr ra` whenever the function is FRAMELESS
    (`mips_can_use_return_insn()`: frame size 0, no `ra` save).

So a framed row - and any row on a 2.7.2-family cell - takes the plain return, while a frameless
row pinned to 2.8.x cannot express the jump in C at that cell at all.  For those the pin itself is
the artefact: the label-as-call spelling made our assembler front end elide the frame, so the
config search never saw the contradiction.  The same pin-free C is byte-exact at a 2.7.2-family
cell, and the plugin reports that cell in `info["cfg"]` for the sweep to correct the row database
(work/lac_lane/epi_pilot/REPORT.md, rows 4 and 11).

The menu, tried in order until `verify_fn` says exact (at most MAX_RUNS runs for the row, every
epilogue site of the row rewritten together, mid-row sites of the same row left untouched):

  drop        delete the pseudo-call where a `return` already follows it
  ret-void    `return;`                              (a void function, or a `return target();`)
  ret-imm     `return N;`                            (N from the audit's `v0=imm:N` - a hint only:
                                                      the pilot found it names an unrelated branch
                                                      delay-slot constant as often as the result)
  ret-prev    `return <the preceding statement's expression>;`, that statement deleted and, when
              it is a call the file declares `void`, its declaration retyped `s32`.  This is the
              `v0=call:ADDR` case and also the `return target() != 0;` shape, where the pseudo-call
              stands inside the expression the preceding statement computed
  fall        delete the statement so control falls into the tail
  cell        the same candidate at a 2.7.2-family cell (frameless 2.8.x rows only, <=3 cells)

An exact candidate also deletes the target's declaration once nothing references it.  Refusals are
named: no epilogue site, a target outside the row's own extent (a jump to a resident or foreign
tail must stay a call), a site inside a macro, a target that also carries mid-row sites (the
ordinal is ambiguous), a shape at the site the menu does not cover, and "no candidate is exact".
"""
import json, re
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
AUDIT = ROOT / "ledger/cache/audit.json"

MAX_RUNS = 10          # verify runs per row
MAX_CELLS = 3          # alternative cells tried for a frameless 2.8.x row
COLLAPSE_CELLS = {"2.8.0", "2.8.1", "2.91.66", "2.95.2"}
ALT_CELLS = ("2.7.2-cdk", "2.7.2", "2.6.3")
# residues a frameless collapse leaves behind: the row loses a word (the `j`), the final `jr ra`
# steals the preceding instruction into its slot and every displacement downstream moves
COLLAPSE_CLASSES = {"length-drift", "code-motion", "delay-slot", "slot-rotation", "linked-target",
                    "block-order", "dead-code-retention", "extent-prefix", "broad"}
COLLAPSE_MAX_TOTAL = 16

KW = {"if", "while", "for", "switch", "return", "sizeof", "do", "else", "case", "default",
      "goto", "break", "continue", "defined", "__attribute__", "__asm__", "asm"}


class Refusal(Exception):
    pass


# --- audit index --------------------------------------------------------------------------------

_IDX = None

def index():
    """(container, row_key) -> [LABEL_AS_CALL record] (every kind: mid-row sites decide ordinals)."""
    global _IDX
    if _IDX is None:
        idx = {}                      # filled locally: the sweep calls this from several threads
        for r in json.load(open(AUDIT))["records"]:
            if r.get("cls") == "LABEL_AS_CALL":
                idx.setdefault((r["container"], r["row_key"]), []).append(r)
        _IDX = idx
    return _IDX

def records_for(row):
    idx = index()
    keys = [row["id"].split("/", 1)[1]] + list(row.get("defs") or []) + [row["func"]]
    if row.get("true_name"):
        keys.append(row["true_name"])
    out = []
    seen = set()
    for k in keys:
        for rec in idx.get((row["container"], k), []):
            if rec["site_id"] not in seen:
                seen.add(rec["site_id"]); out.append(rec)
    return out


# --- text scaffolding ---------------------------------------------------------------------------

def mask(t):
    """A copy with comments and string/char literals blanked, so indices still line up."""
    out = list(t); i = 0; n = len(t)
    while i < n:
        c = t[i]
        if c == "/" and t[i + 1:i + 2] == "/":
            j = t.find("\n", i); j = n if j < 0 else j
            for k in range(i, j): out[k] = " "
            i = j
        elif c == "/" and t[i + 1:i + 2] == "*":
            j = t.find("*/", i + 2); j = n if j < 0 else j + 2
            for k in range(i, j):
                if t[k] != "\n": out[k] = " "
            i = j
        elif c in "\"'":
            j = i + 1
            while j < n and t[j] != c:
                j += 2 if t[j] == "\\" else 1
            for k in range(i, min(j + 1, n)): out[k] = " "
            i = min(j + 1, n)
        else:
            i += 1
    return "".join(out)

DEF_RE = re.compile(r"(^|\n)([A-Za-z_][\w\s\*]*?)\b([A-Za-z_]\w*)\s*\(([^;{)]*)\)\s*"
                    r"(?:__attribute__\s*\(\([^)]*\)\)\s*)?\{")

def find_defs(m):
    """[{name, rtype, bstart, bend}] for every function definition (positions in the masked text)."""
    defs = []
    for mm in DEF_RE.finditer(m):
        if mm.group(3) in KW:
            continue
        i = m.index("{", mm.end() - 1)
        depth = 0
        for j in range(i, len(m)):
            if m[j] == "{":
                depth += 1
            elif m[j] == "}":
                depth -= 1
                if depth == 0:
                    break
        defs.append({"name": mm.group(3), "rtype": " ".join(mm.group(2).split()),
                     "bstart": i, "bend": j})
    return defs

def matching_paren(m, i):
    d = 0
    for j in range(i, len(m)):
        if m[j] == "(":
            d += 1
        elif m[j] == ")":
            d -= 1
            if d == 0:
                return j
    raise Refusal("unbalanced parentheses")

def line_start(t, i):
    return t.rfind("\n", 0, i) + 1

def in_macro(t, m, i):
    """The site sits in a `#define` body (possibly a continued one)."""
    ls = line_start(t, i)
    while True:
        line = t[ls:t.find("\n", ls) if t.find("\n", ls) >= 0 else len(t)]
        if line.lstrip().startswith("#"):
            return line.lstrip().startswith("#define")
        if ls == 0 or not t[:ls - 1].rstrip("\n").endswith("\\"):
            return False
        ls = line_start(t, ls - 1)

def next_significant(m, i):
    """The first non-blank text at or after i (comments are already blanked)."""
    while i < len(m) and m[i] in " \t\r\n":
        i += 1
    return i

def stmt_bounds(m, pos, end):
    """(start, semi) - start is the index of the delimiter before the statement, semi the index of
    the `;` that ends it."""
    start = max(m.rfind(";", 0, pos), m.rfind("{", 0, pos), m.rfind("}", 0, pos),
                m.rfind(":", 0, pos))
    d = 0
    semi = -1
    for j in range(end, len(m)):
        if m[j] == "(":
            d += 1
        elif m[j] == ")":
            d -= 1
        elif m[j] == ";" and d <= 0:
            semi = j; break
    if semi < 0:
        raise Refusal("statement is not terminated")
    return start, semi


# --- the row's extent ---------------------------------------------------------------------------

def row_bases(row, defs):
    """Every address the row's code can be addressed by: its rowbase symbol, its true-space name,
    and the `func_XXXXXXXX` the file actually defines."""
    names = [row.get("func"), row.get("true_name")] + [d["name"] for d in defs]
    out = []
    for n in names:
        if n and re.fullmatch(r"func_[0-9A-Fa-f]{8}", n):
            out.append(int(n[5:], 16))
    return sorted(set(out))

def in_row(row, bases, target):
    try:
        ta = int(target[5:], 16)
    except (TypeError, ValueError):
        return False
    return any(b <= ta < b + row["size"] for b in bases)


# --- planning -----------------------------------------------------------------------------------

def prev_statement(t, m, delim):
    """(start, end) of the expression statement immediately before the site's statement (`delim` is
    the index of the delimiter that opens it), or None."""
    if delim < 0 or m[delim] != ";":
        return None                       # the site opens the block: nothing precedes it
    p0 = max(m.rfind(";", 0, delim), m.rfind("{", 0, delim), m.rfind("}", 0, delim),
             m.rfind(":", 0, delim))
    pa = next_significant(m, p0 + 1)
    s = m[pa:delim].strip()
    if not s:
        return None
    first = re.match(r"[A-Za-z_]\w*", s)
    if first and first.group(0) in KW:
        return None                       # a control statement, not an expression
    if re.search(r"[{}]", s) or re.match(r"^#", s):
        return None
    if re.match(r"^(?:const|volatile|static|register|unsigned|signed)\b", s) or \
       re.match(r"^[A-Za-z_]\w*(?:\s*\*)*\s+\**[A-Za-z_]\w*\s*(?:=|\[|$)", s):
        return None                       # a declaration, not an expression
    return pa, delim

def plan_sites(text, row):
    """[site dict] for every epilogue site of the row, or raise Refusal."""
    recs = records_for(row)
    epi = [r for r in recs if r.get("kind") == "epilogue"]
    if not epi:
        raise Refusal("no epilogue LABEL_AS_CALL site")
    m = mask(text)
    defs = find_defs(m)
    if not defs:
        raise Refusal("no function definition in the file")
    bases = row_bases(row, defs)
    for r in epi:
        if not in_row(row, bases, r["target"]):
            raise Refusal("target %s outside the row extent" % r["target"])
    own = {n for n in [row.get("func"), row.get("true_name")] + list(row.get("defs") or []) if n}
    other = {r["target"] for r in recs if r.get("kind") != "epilogue"}
    targets = {}
    for r in epi:
        targets.setdefault(r["target"], []).append(r)
    sites = []
    for tgt, rs in sorted(targets.items()):
        if tgt in other:
            raise Refusal("target %s also has mid-row sites" % tgt)
        occ = [mm.start() for mm in re.finditer(r"\b" + re.escape(tgt) + r"\s*\(", m)
               if any(d["bstart"] < mm.start() < d["bend"] for d in defs)]
        if not occ:
            raise Refusal("no call to %s in the text" % tgt)
        v0s = [r.get("v0") for r in rs]
        for k, pos in enumerate(occ):
            if in_macro(text, m, pos):
                raise Refusal("site inside a macro")
            encl = next((d for d in defs if d["bstart"] < pos < d["bend"]), None)
            if encl is None:
                raise Refusal("call to %s outside any function body" % tgt)
            if len(defs) > 1 and encl["name"] not in own:
                raise Refusal("site sits in %s, not the row's function" % encl["name"])
            call_end = matching_paren(m, m.index("(", pos))
            delim, semi = stmt_bounds(m, pos, call_end)
            start = next_significant(m, delim + 1)   # the statement itself: any comment before it stays
            core = m[start:semi + 1].strip()         # masked: a trailing comment is not part of the shape
            if core.startswith("#") or "\n#" in core:
                raise Refusal("site inside a preprocessor conditional")
            if re.fullmatch(re.escape(tgt) + r"\s*\([^;]*\)\s*;", core, re.S):
                kind = "standalone"
            elif core.startswith("return"):
                rest = core[len("return"):].strip()
                kind = "return-call" if re.fullmatch(re.escape(tgt) + r"\s*\([^;]*\)\s*;", rest, re.S) \
                    else "return-expr"
            else:
                raise Refusal("unhandled shape at the site: %s" % core.split("\n")[0][:60])
            sites.append({"target": tgt, "v0": v0s[k] if k < len(v0s) else v0s[-1],
                          "pos": pos, "call_end": call_end, "start": start, "semi": semi,
                          "kind": kind, "rtype": encl["rtype"], "encl": encl,
                          "prev": prev_statement(text, m, delim),
                          "next": text[next_significant(m, semi + 1):next_significant(m, semi + 1) + 8]})
    sites.sort(key=lambda s: s["pos"])
    return sites, m, defs

# --- the per-site menu ---------------------------------------------------------------------------

def imm_of(v0):
    if isinstance(v0, str) and v0.startswith("imm:"):
        v = v0[4:].strip()
        try:
            return str(int(v, 0))
        except ValueError:
            return None
    return None

def call_of(v0):
    if isinstance(v0, str) and v0.startswith("call:"):
        a = v0[5:].strip().lower()
        if a.startswith("0x"):
            return "func_%08X" % int(a, 16)
    return None

def prev_is_the_v0_call(site, text):
    """The preceding statement is the call the audit says left its result in $v0."""
    f = call_of(site["v0"])
    return bool(f and site["prev"] and re.match(r"\s*" + re.escape(f) + r"\s*\(", text[site["prev"][0]:site["prev"][1]]))

def actions_for(site, text):
    """The ordered menu for one site."""
    void = site["rtype"].replace("*", "").strip() in ("void", "")
    imm = imm_of(site["v0"])
    prev = bool(site["prev"]) and not void          # a value: never in a void function
    acts = []
    nxt = site["next"].lstrip()
    if site["kind"] == "standalone":
        if re.match(r"return\b", nxt):
            acts.append("drop")                     # (1) the return that follows already says it
        if void:
            acts.append("ret-void")                 # (2)
        if prev and prev_is_the_v0_call(site, text):
            acts.append("ret-prev")                 # (4) v0 = the preceding call's result
        if imm is not None and not void:
            acts.append("ret-imm")                  # (3) the audit's imm is a hint only
        if prev:
            acts.append("ret-prev")
        acts.append("fall")                         # (5)
        if not void:
            acts.append("ret-void")
    elif site["kind"] == "return-call":
        if void:
            acts.append("ret-void")
        if prev:
            acts.append("ret-prev")
        if imm is not None and not void:
            acts.append("ret-imm")
        if not void:
            acts.append("ret-void")
    else:                                   # return-expr: the call stands inside the expression
        if prev:
            acts.append("ret-prev")
        if imm is not None:
            acts.append("subst-imm")
        if void:
            acts.append("ret-void")
    out = []
    for a in acts:                          # keep the order, drop duplicates
        if a not in out:
            out.append(a)
    return out

def strip_void_cast(expr):
    e = expr.strip().rstrip(";").strip()
    mm = re.match(r"\(\s*void\s*\)\s*", e)
    if mm:
        e = e[mm.end():].strip()
    return e

def cut(text, m, a, b):
    """Delete text[a:b], taking the whole line when only blanks and comments share it."""
    ls = line_start(text, a)
    le = m.find("\n", b)
    le = len(text) if le < 0 else le + 1
    if m[ls:a].strip() == "" and m[b:le].strip() == "":
        return ls, le, ""
    return a, b, ""

def retype_void_decl(text, callee):
    """`extern void f(...);` -> `extern s32 f(...);` (the value is used now)."""
    pat = re.compile(r"(^[ \t]*(?:extern[ \t]+)?)void([ \t]+\**" + re.escape(callee) + r"[ \t]*\()", re.M)
    return pat.sub(lambda mm: mm.group(1) + "s32" + mm.group(2), text, count=1)

def apply_site(text, m, site, action, edits):
    """Append (start, end, replacement) edits for one site."""
    stmt_a, stmt_b = site["start"], site["semi"] + 1
    if action in ("drop", "fall"):
        edits.append(cut(text, m, stmt_a, stmt_b))
    elif action == "ret-void":
        edits.append((stmt_a, stmt_b, "return;"))
    elif action == "ret-imm":
        edits.append((stmt_a, stmt_b, "return %s;" % imm_of(site["v0"])))
    elif action == "subst-imm":
        edits.append((site["pos"], site["call_end"] + 1, imm_of(site["v0"])))
    elif action == "ret-prev":
        pa, pb = site["prev"]
        expr = strip_void_cast(text[pa:pb])
        if not expr:
            raise Refusal("empty preceding statement")
        if not re.fullmatch(r"[\w\.\->\[\]]+|\(.*\)|[A-Za-z_]\w*\s*\(.*\)", expr, re.S):
            expr = "(%s)" % expr
        edits.append(cut(text, m, pa, pb + 1))                     # the preceding statement, with its `;`
        if site["kind"] == "standalone":
            edits.append((stmt_a, stmt_b, "return %s;" % expr))
        else:
            edits.append((site["pos"], site["call_end"] + 1, expr))
        mm = re.fullmatch(r"\(?\s*([A-Za-z_]\w*)\s*\(.*", expr, re.S)
        return mm.group(1) if mm else None
    else:
        raise Refusal("unknown action %s" % action)
    return None

def drop_declaration(text, target):
    """Remove the target's declaration once nothing calls it any more."""
    m = mask(text)
    defs = find_defs(m)
    for mm in re.finditer(r"\b" + re.escape(target) + r"\s*\(", m):
        if any(d["bstart"] < mm.start() < d["bend"] for d in defs):
            return text                              # still referenced
    out = text
    for _ in range(4):
        m = mask(out)
        mm = re.search(r"\b" + re.escape(target) + r"\b", m)
        if not mm:
            break
        ls = line_start(out, mm.start())
        semi = m.find(";", mm.start())
        if semi < 0:
            break
        le = out.find("\n", semi)
        le = len(out) if le < 0 else le + 1
        head = out[ls:mm.start()]
        if ";" in head or "{" in head or "}" in head:      # shares its line with real code
            break
        out = out[:ls] + out[le:]
        while out[:ls].endswith("\n\n") and out[ls:ls + 1] == "\n":
            out = out[:ls] + out[ls + 1:]
    return out

def build(text, sites, choice):
    """The candidate for one strategy index: `choice[i]` names site i's action."""
    edits = []
    retype = []
    m = mask(text)
    for site, action in zip(sites, choice):
        r = apply_site(text, m, site, action, edits)
        if r:
            retype.append(r)
    out = text
    edits.sort(key=lambda e: -e[0])
    for (a, b, _), (c, d, _) in zip(edits[1:], edits):
        if b > c:
            raise Refusal("two sites want the same text")
    for a, b, rep in edits:
        out = out[:a] + rep + out[b:]
    for callee in retype:
        if re.search(r"^[ \t]*(?:extern[ \t]+)?void[ \t]+\**" + re.escape(callee) + r"[ \t]*\(", out, re.M):
            out = retype_void_decl(out, callee)
    for tgt in sorted({s["target"] for s in sites}):
        out = drop_declaration(out, tgt)
    # `return;` immediately followed by another `return;` at the same depth is redundant
    out = re.sub(r"([ \t]*)return;\n\1return;\n", r"\1return;\n", out)
    return out


# --- cells --------------------------------------------------------------------------------------

def parse_cfg(cfg):
    parts = cfg.split()
    head, flags = parts[0], parts[1:]
    if "+" in head:
        head, plus = head.split("+", 1)
        if plus:
            flags.insert(0, plus)
    if head.endswith("-G0"):
        head = head[:-3]; flags.insert(0, "-G0")
    return head, flags

def fmt_cfg(cell, flags):
    if flags and flags[0] == "-G0":
        return (cell + "-G0" + (" " + " ".join(flags[1:]) if len(flags) > 1 else "")).strip()
    return (cell + (" " + " ".join(flags) if flags else "")).strip()

def alt_cfgs(cfg):
    cell, flags = parse_cfg(cfg)
    if cell not in COLLAPSE_CELLS:
        return []
    return [fmt_cfg(c, flags) for c in ALT_CELLS][:MAX_CELLS]

def suggests_collapse(v):
    if v.get("status") not in ("ok", None) or v.get("exact"):
        return False
    tot = v.get("total")
    return (v.get("class") in COLLAPSE_CLASSES) and (tot is None or tot <= COLLAPSE_MAX_TOTAL)


# --- the plugin -----------------------------------------------------------------------------------

class T:
    name = "t10_epilogue"; level = 1
    needs_verify = True

    @staticmethod
    def eligible(text, row, census):
        try:
            plan_sites(text, row)
        except Refusal as e:
            return str(e)
        except Exception as e:
            return "parse error: %r" % (e,)
        return None

    @staticmethod
    def apply_verified(text, row, census, verify_fn):
        try:
            sites, _m, _defs = plan_sites(text, row)
        except Refusal as e:
            return None, {"refused": [str(e)]}
        except Exception as e:
            return None, {"refused": ["parse error: %r" % (e,)]}
        menus = [actions_for(s, text) for s in sites]
        if any(not mu for mu in menus):
            return None, {"sites": len(sites), "refused": ["no menu entry for the site's shape"]}
        info = {"sites": len(sites), "targets": sorted({s["target"] for s in sites}),
                "kinds": [s["kind"] for s in sites], "menu": [",".join(mu) for mu in menus]}
        runs = 0; tried = []; last = {}
        best = None
        for k in range(max(len(mu) for mu in menus)):
            choice = [mu[min(k, len(mu) - 1)] for mu in menus]
            if choice in tried:
                continue
            tried.append(choice)
            try:
                cand = build(text, sites, choice)
            except Refusal as e:
                info.setdefault("skipped", []).append("%s: %s" % ("+".join(choice), e))
                continue
            if cand == text:
                continue
            if runs >= MAX_RUNS:
                break
            v = verify_fn(cand); runs += 1; last = v
            if v.get("exact"):
                return cand, dict(info, action="+".join(choice), runs=runs)
            if best is None and suggests_collapse(v):
                best = (choice, cand, v)
        # frameless 2.8.x: the same C at a cell that keeps the epilogue jump
        if best is not None:
            choice, cand, v = best
            for cfg in alt_cfgs(row["cfg"]):
                if runs >= MAX_RUNS:
                    break
                v2 = verify_fn(cand, cfg=cfg); runs += 1
                if v2.get("exact"):
                    return cand, dict(info, action="+".join(choice), runs=runs, cfg=cfg,
                                      cfg_was=row["cfg"])
            last = v
        return None, dict(info, runs=runs,
                          refused=["no candidate is exact (%s/%s after %d runs)"
                                   % (last.get("class") or last.get("status"), last.get("total"), runs)])

    @staticmethod
    def apply(text, row, census):
        """Unverified: the first menu choice only (the sweep always uses apply_verified)."""
        try:
            sites, _m, _defs = plan_sites(text, row)
            menus = [actions_for(s, text) for s in sites]
            if any(not mu for mu in menus):
                return None
            return build(text, sites, [mu[0] for mu in menus])
        except Refusal:
            return None
