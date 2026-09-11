"""T9: a load-bearing register pin becomes the pin-free C shape that produces the same colouring.

`work/exp_pins/REPORT.md` measured 20 rows whose every pin is load-bearing.  Four went pin-free
through their window gate, and all four are pure register-colouring residues: gcc's local-alloc
priority is a function of how many distinct locals a function has and how long each lives, and
both are writable in C.  This plugin is that measurement turned into a fixed menu; nothing else
is attempted, because the other 16 rows were decided by a copy cse deletes, a dead value parked
in a delay slot, or a fence position no statement boundary reproduces - none of them reachable
from C, all of them 0/3 per census class in the sample.

Eligible (`eligible`): every live pin site of the row is `ASM_REG` in census class `reg-rename`,
or `ASM_REG` in class `broad` with a pure-colouring signature (no indels, no length change - the
`func_8008E850` site that fell), or `ASM_SCHED_BARRIER` in class `length-drift` (the one barrier
shape that fell).  Rows carrying any other macro or class are refused with the class named:
`addressing`, `block-order`, `code-motion` and `reorder-only` were 0/3 rows each in the
experiment and must not spend probes.  `_pre` structs, inline asm bodies and `NON_MATCHING` arms
are refused outright.

The menu, in the experiment's order, one verified candidate per step, first exact wins, at most
`BUDGET` verify runs per row (a candidate erases every live pin of the row, because every
single-pin-drop probe on the experiment's six multi-pin rows failed; if all of those miss and the
row has several pins, the same menu is retried erasing the target pin alone, and an exact result
there is re-entered greedily for the pins that are left):

  s1 a **parameter** that is reassigned and then counted/accumulated moves into a fresh local
     declared first at function scope, initialised in the same statement slot  (row 809211BC)
  s2 a local written in two independent groups splits into one local per group  (row 800AC708)
  s3 a declaration in an inner block is hoisted to function scope - a bare block is dissolved,
     a control-flow body keeps its braces and loses the declaration  (row 8008E850)
  s4 widen a `u8`/`u16` temporary to `s32`; collapse a `t = *p; t op= k; *p = t;` temporary into
     the memory operand; fold a temporary written once and read once into its use; keep
     `register` without the asm binding  (row 8008E850's other exact spellings)
  sb `ASM_SCHED_BARRIER`: a loop-counter increment standing before the fence sinks to the end of
     the loop body and the fence goes  (row 81337B68)

Declaration-order permutation, an explicit temporary for a subexpression, merging two locals and
polarity flips are deliberately absent: 0/9, 0/9, 0/5 and 0/8 in the experiment.

Three rules the experiment's 20 rows did not settle, added here and measured in
`work/t9_build/REPORT.md`:
  * the class a site is gated on comes from the T2 journal (what broke when that pin alone was
    erased from the *current* text), not from `ledger/pins.jsonl` (the same erasure from the
    original pinned text).  They disagree on ~1,700 live sites, nearly all of them census
    `match` that T2 had to keep because pins interact; the census is the fallback.
  * s1 only moves a parameter whose reassignment neither reads the parameter itself nor sits
    below a label - otherwise the fresh local would start undefined or be re-entered.
  * a pinned declaration may carry an initialiser (`register T v ASM_REG("$4") = arg0;`); the
    initialiser rides along through every step.
"""
import json, re, sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
if str(ROOT / "tools") not in sys.path:
    sys.path.insert(0, str(ROOT / "tools"))
from pin_census import sites_of, erase, asm_blocker   # the census' own definition of a pin site

try:                                            # the shared C-shape parser lives in T8
    from .t8_passthru import find_defs, matching_paren, split_params, param_type
except ImportError:                             # pragma: no cover - direct import
    from t8_passthru import find_defs, matching_paren, split_params, param_type

BUDGET = 8
STMT_KW = {"return", "goto", "break", "continue", "else", "do", "case", "default", "if", "while",
           "for", "switch", "typedef", "sizeof"}
NARROW = {"u8", "s8", "u16", "s16", "char", "short"}
NOTE_RE = re.compile(r"[ \t]*/\*\s*MATCH pin:.*?\*/")


class Refusal(Exception):
    pass


# --------------------------------------------------------------------------- census

_CENSUS = None
_T2 = None

def t2_verdicts():
    """row id -> [(macro, arg prefix, breakage class)] for the pins T2's greedy pass kept.

    This is the live measurement: what broke when that pin alone was erased from the *reduced*
    text, in the order the pins stand in it.  `ledger/pins.jsonl` measures the same erasure from
    the original pinned text, so for 1,700 sites the two disagree - most of them census `match`
    (dead on its own) that T2 nevertheless had to keep because pins interact.  T6 already reads
    this journal to write the pin notes; T9 gates on it for the same reason, and falls back to
    the census ordinal when a row has no usable verdict (T2 truncates its list at 40 sites).
    """
    global _T2
    if _T2 is None:
        _T2 = {}
        p = ROOT / "ledger/sweeps/t2_pins.jsonl"
        if p.exists():
            for line in p.read_text().splitlines():
                if not line.strip():
                    continue
                j = json.loads(line)
                if j.get("outcome") in ("applied", "noop"):
                    _T2[j["id"]] = [tuple(k) for k in (j.get("kept") or [])]
    return _T2


def census_pins():
    """row id -> [pin record], in site order (ledger/pins.jsonl: one record per pin site)."""
    global _CENSUS
    if _CENSUS is None:
        idx = {}
        for line in (ROOT / "ledger/pins.jsonl").read_text().splitlines():
            if not line.strip():
                continue
            r = json.loads(line)
            idx.setdefault(r["id"], []).append(r)
        for v in idx.values():
            v.sort(key=lambda r: r.get("site", 0))
        _CENSUS = idx
    return _CENSUS


def tractable(macro, rec):
    """None when the experiment's menu covers this site, else why it does not."""
    cls = rec.get("class")
    if macro == "ASM_REG":
        if cls == "reg-rename":
            return None
        if cls == "broad":
            if rec.get("indels") == 0 and rec.get("dwords") == 0:
                return None                    # a pure colouring permutation, same length
            return "pin class broad without a colouring signature"
        return "pin class %s not tractable (ASM_REG)" % cls
    if macro == "ASM_SCHED_BARRIER":
        if cls == "length-drift":
            return None
        return "pin class %s not tractable (ASM_SCHED_BARRIER)" % cls
    return "pin macro %s outside the menu" % macro


# --------------------------------------------------------------------------- text utilities

def mask(text):
    """A same-length copy with comment and string bodies blanked, for safe regex scanning."""
    out = list(text)
    i, n = 0, len(text)
    while i < n:
        c = text[i]
        if c == "/" and text[i + 1:i + 2] == "*":
            j = text.find("*/", i + 2)
            j = n if j < 0 else j + 2
        elif c == "/" and text[i + 1:i + 2] == "/":
            j = text.find("\n", i)
            j = n if j < 0 else j
        elif c in "\"'":
            j = i + 1
            while j < n and text[j] != c:
                j += 2 if text[j] == "\\" else 1
            j = min(j + 1, n)
        else:
            i += 1
            continue
        for k in range(i, j):
            if out[k] != "\n":
                out[k] = " "
        i = j
    return "".join(out)


def strip_notes(text):
    """A `/* MATCH pin: ... */` note whose pin is gone goes with it."""
    out = []
    for ln in text.splitlines(True):
        if "MATCH pin:" in ln and "ASM_" not in ln:
            nl = "\n" if ln.endswith("\n") else ""
            body = NOTE_RE.sub("", ln[:len(ln) - len(nl)]).rstrip()
            if not body.strip():
                continue
            ln = body + nl
        out.append(ln)
    return "".join(out)


def erase_indices(text, idxs):
    """Erase the pin sites at these `sites_of` indices (offsets re-derived from `text`)."""
    sites = sites_of(text)
    for i in sorted(idxs, reverse=True):
        text = erase(text, sites[i])
    return strip_notes(text)


def replace_spans(text, spans, new):
    for s, e in sorted(spans, reverse=True):
        text = text[:s] + new + text[e:]
    return text


def fresh(masked, *bases):
    for base in bases:
        for cand in [base] + ["%s%d" % (base, k) for k in range(2, 10)]:
            if not re.search(r"\b%s\b" % re.escape(cand), masked):
                return cand
    return None


def decl_text(indent, typ, name):
    return "%s%s%s;\n" % (indent, typ, name) if typ.endswith("*") else "%s%s %s;\n" % (indent, typ, name)


def parse_decl_line(line):
    """{indent,type,name,arr,init} for one declaration line (an initialiser is kept), else None."""
    body = re.sub(r"/\*.*?\*/", " ", line).split("//")[0].rstrip()
    s = body.strip()
    if not s.endswith(";"):
        return None
    core = s[:-1].strip()
    init = None
    eq = core.find("=")
    if eq == 0:
        return None
    if eq > 0:
        if core[eq + 1:eq + 2] == "=" or core[eq - 1:eq] in "=!<>+-*/&|^%":
            return None
        init = core[eq + 1:].strip()
        core = core[:eq].strip()
        if not init:
            return None
    if not core or any(ch in core for ch in "()+-{}<>?:!&|%/,\"'.;"):
        return None
    m = re.match(r"^([A-Za-z_][\w \t]*?)([ \t*]+)([A-Za-z_]\w*)((?:\[[^\]]*\])*)$", core)
    if not m:
        return None
    tname = m.group(1).strip()
    if tname.split()[0] in STMT_KW:
        return None
    stars = m.group(2).strip()
    return {"indent": line[:len(line) - len(line.lstrip())], "type": (tname + " " + stars).strip(),
            "name": m.group(3), "arr": m.group(4), "init": init}


def render_decl(dec, typ=None, name=None, indent=None):
    """The declaration line again, optionally with another type, name or indent; initialiser kept."""
    typ = dec["type"] if typ is None else typ
    name = (dec["name"] if name is None else name) + dec["arr"]
    ind = dec["indent"] if indent is None else indent
    head = "%s%s%s" % (ind, typ, name) if typ.endswith("*") else "%s%s %s" % (ind, typ, name)
    return head + (" = %s;\n" % dec["init"] if dec.get("init") else ";\n")


def def_by_name(text, name):
    for d in find_defs(text):
        if d["name"] == name:
            return d
    return None


def enclosing_def(text, pos):
    for d in find_defs(text):
        if d["bstart"] < pos < d["bend"]:
            return d
    return None


def decl_block(text, d):
    """(start, end, [decl]) over the leading declaration lines of a function body."""
    nl = text.find("\n", d["bstart"])
    if nl < 0 or nl > d["bend"]:
        return d["bstart"] + 1, d["bstart"] + 1, []
    start = pos = nl + 1
    end = start
    decls = []
    while pos < d["bend"]:
        eol = text.find("\n", pos)
        if eol < 0 or eol > d["bend"]:
            break
        line = text[pos:eol + 1]
        if not line.strip():
            pos = eol + 1
            continue
        p = parse_decl_line(line)
        if not p:
            break
        p["span"] = (pos, eol + 1)
        decls.append(p)
        pos = end = eol + 1
    return start, end, decls


def body_decl(text, d, name):
    """The declaration line of `name` anywhere in the body (with its span), or None."""
    pos = text.find("\n", d["bstart"]) + 1
    while 0 < pos < d["bend"]:
        eol = text.find("\n", pos)
        if eol < 0 or eol > d["bend"]:
            break
        p = parse_decl_line(text[pos:eol + 1])
        if p and p["name"] == name:
            p["span"] = (pos, eol + 1)
            return p
        pos = eol + 1
    return None


def enclosing_block(masked, pos, lo):
    """(open, close) offsets of the innermost `{}` containing pos, or (None, None)."""
    dep = 0
    i = pos - 1
    while i > lo:
        c = masked[i]
        if c == "}":
            dep += 1
        elif c == "{":
            if dep == 0:
                break
            dep -= 1
        i -= 1
    else:
        return None, None
    dep = 0
    for j in range(i, len(masked)):
        if masked[j] == "{":
            dep += 1
        elif masked[j] == "}":
            dep -= 1
            if dep == 0:
                return i, j
    return None, None


def line_span(text, pos):
    s = text.rfind("\n", 0, pos) + 1
    e = text.find("\n", pos)
    return s, (len(text) if e < 0 else e + 1)


def is_bare_block(masked, open_i):
    """A block that is not a control-flow body / function body: `{` after `;`, `{`, `}` or a label."""
    j = open_i - 1
    while j >= 0 and masked[j] in " \t\n":
        j -= 1
    return j < 0 or masked[j] in ";{}:"


def loop_cond(masked, open_i, close_i):
    """The controlling expression of the loop whose body is this block, else None."""
    head = masked[:open_i].rstrip()
    if head.endswith(")"):
        i = head.rfind("(")
        dep = 0
        for k in range(len(head) - 1, -1, -1):
            if head[k] == ")":
                dep += 1
            elif head[k] == "(":
                dep -= 1
                if dep == 0:
                    i = k
                    break
        kw = head[:i].rstrip()
        m = re.search(r"\b(while|for|if|switch)\s*$", kw)
        if not m:
            return None
        if m.group(1) == "for":
            parts = head[i + 1:-1].split(";")
            return parts[1] if len(parts) == 3 else None
        if m.group(1) == "while":
            return head[i + 1:-1]
        return None
    if re.search(r"\bdo\s*$", head):
        m = re.match(r"\s*while\s*\(", masked[close_i + 1:])
        if not m:
            return None
        s = close_i + 1 + m.end() - 1
        e = matching_paren(masked, s)
        return masked[s + 1:e]
    return None


def calls_between(masked, lo, hi):
    for m in re.finditer(r"\b([A-Za-z_]\w*)\s*\(", masked[lo:hi]):
        if m.group(1) not in STMT_KW:
            return True
    return False


# --------------------------------------------------------------------------- eligibility

def guards(text):
    # NON_MATCHING arms and asm LABELS (`__asm__("func_...")`, the tail-call spelling) are not
    # refusals any more: see pin_census.arm_labels / asm_blocker.
    if re.search(r"\b\w+_pre\b", text):
        return "_pre struct"
    return asm_blocker(text)


def live_pins(text, row):
    """[{site, rec, macro, cls, var, fn}] for every live pin, or Refusal naming the blocker."""
    sites = sites_of(text)
    if not sites:
        raise Refusal("no live pin site")
    why = guards(text)
    if why:
        raise Refusal(why)
    kept = t2_verdicts().get(row["id"]) or []
    live = None
    if len(kept) == len(sites) and all(k[0] == s[1] and (s[2] or "").strip().startswith(k[1][:20])
                                       for k, s in zip(kept, sites)):
        live = [{"class": k[2], "indels": None, "dwords": None} for k in kept]
    recs = census_pins().get(row["id"], [])
    bykey = {}
    for r in recs:
        bykey.setdefault((r["macro"], (r.get("arg") or "").strip()), []).append(r)
    seen = {}
    out = []
    for idx, s in enumerate(sites):
        key = (s[1], (s[2] or "").strip())
        i = seen.get(key, 0)
        seen[key] = i + 1
        lst = bykey.get(key) or []
        cen = lst[i] if i < len(lst) else None
        rec = live[idx] if live else cen
        if rec is None:
            raise Refusal("pin site %s(%s) not in the census" % key)
        if rec.get("indels") is None and cen is not None and rec["class"] == cen.get("class"):
            rec = cen                                   # the same verdict: keep the census detail
        bad = tractable(s[1], rec)
        if bad:
            raise Refusal(bad)
        d = enclosing_def(text, s[3])
        if d is None:
            raise Refusal("pin outside a function body")
        var = None
        if s[1] == "ASM_REG":
            m = re.search(r"([A-Za-z_]\w*)\s*(?:\[[^\]]*\])*\s*$", s[6])
            if not m:
                raise Refusal("register pin declarator not parsed")
            var = m.group(1)
        out.append({"i": idx, "site": s, "rec": rec, "macro": s[1], "cls": rec.get("class"),
                    "var": var, "fn": d["name"]})
    return out


# --------------------------------------------------------------------------- the menu
# Each builder takes the pin-free (or pin-reduced) text and returns (label, candidate) or None.

def s1_param_counter(base, target):
    """A reassigned, then counted/accumulated parameter moves into a fresh local."""
    d = def_by_name(base, target["fn"])
    if d is None:
        return None
    mb = mask(base)
    i = base.index("(", d["dstart"])
    j = matching_paren(base, i)
    blk_start, blk_end, decls = decl_block(base, d)
    bs = d["bstart"] + 1                            # inside the body brace
    seg = mb[bs:d["bend"]]
    jump = min([m.start() for m in re.finditer(r"\bgoto\b", seg)] +
               [m.start() for m in re.finditer(r"(?m)^[ \t]*[A-Za-z_]\w*:[ \t]*$", seg)] + [len(seg)])
    for p in split_params(base[i + 1:j]):
        typ, nm = param_type(p)
        if not nm or not typ or typ == "void":
            continue
        if re.search(r"&\s*%s\b" % re.escape(nm), seg):
            continue
        asn = re.search(r"(?m)^[ \t]*%s\s*=(?!=)([^;\n]*);" % re.escape(nm), seg)
        if not asn or asn.start() > jump:
            continue                                   # a jump could re-enter above the new local
        if re.search(r"\b%s\b" % re.escape(nm), asn.group(1)):
            continue                                   # a self-update, not a re-initialisation
        if seg.count("{", 0, asn.start()) != seg.count("}", 0, asn.start()):
            continue                                   # nested: an outer iteration would re-read it
        after = seg[asn.end():]
        if not re.search(r"\b%s\s*(?:\+\+|--|[-+*/&|^]=)|(?:\+\+|--)\s*%s\b" % (re.escape(nm), re.escape(nm)), after):
            continue                                   # reassigned but not counted: not the shape
        new = fresh(mb, "n", "ctr")
        if new is None:
            continue
        start = bs + asn.start()
        spans = [(m.start(), m.end()) for m in re.finditer(r"\b%s\b" % re.escape(nm), mb)
                 if start <= m.start() < d["bend"]]
        if not spans:
            continue
        cand = replace_spans(base, spans, new)
        at = decls[0]["span"][0] if decls else blk_start
        indent = decls[0]["indent"] if decls else "    "
        cand = cand[:at] + decl_text(indent, typ, new) + cand[at:]
        return "s1_param_counter(%s->%s)" % (nm, new), cand
    return None


def s2_split_groups(base, target):
    """A local written in two independent groups becomes one local per group."""
    v = target.get("var")
    if not v:
        return None
    d = def_by_name(base, target["fn"])
    if d is None:
        return None
    blk_start, blk_end, decls = decl_block(base, d)
    dec = next((x for x in decls if x["name"] == v), None)
    if dec is None or dec["arr"]:
        return None
    mb = mask(base)
    seg = mb[d["bstart"]:d["bend"]]
    if re.search(r"\bgoto\b", seg) or re.search(r"^[ \t]*[A-Za-z_]\w*:[ \t]*$", seg, re.M):
        return None                                    # a jump can re-enter either group
    asns = [m for m in re.finditer(r"(?m)^[ \t]*%s\s*=(?!=)" % re.escape(v), mb[:d["bend"]])
            if m.start() >= blk_end]
    if len(asns) != 2:
        return None
    a1, a2 = asns
    uses = [m for m in re.finditer(r"\b%s\b" % re.escape(v), mb[:d["bend"]]) if m.start() >= blk_end]
    if any(u.start() < a1.start() for u in uses):
        return None                                    # read before the first group's write
    mid = mb[a1.end():a2.start()]
    dep = 0
    for ch in mid:
        if ch == "{":
            dep += 1
        elif ch == "}":
            dep -= 1
            if dep < 0:
                return None                            # the groups sit in different blocks
    if dep != 0 or re.search(r"\b(while|for|do|switch|case)\b", mid):
        return None
    g1 = [u for u in uses if u.start() < a2.start()]
    g2 = [u for u in uses if u.start() >= a2.start()]
    if len(g1) < 2 or len(g2) < 2:
        return None
    def across_call(g):
        return calls_between(mb, g[0].end(), g[-1].start())
    if across_call(g1) and across_call(g2):
        return None                                    # live across a call in both groups
    v2 = fresh(mb, v + "2", v + "_b")
    if v2 is None:
        return None
    cand = replace_spans(base, [(u.start(), u.end()) for u in g2], v2)
    at = dec["span"][1]
    cand = cand[:at] + decl_text(dec["indent"], dec["type"], v2) + cand[at:]
    return "s2_split_groups(%s/%s)" % (v, v2), cand


def s3_hoist(base, target):
    """A declaration in an inner block moves to function scope (a bare block is dissolved)."""
    v = target.get("var")
    if not v:
        return None
    d = def_by_name(base, target["fn"])
    if d is None:
        return None
    blk_start, blk_end, decls = decl_block(base, d)
    if any(x["name"] == v for x in decls):
        return None                                    # already at function scope
    dec = body_decl(base, d, v)
    if dec is None:
        return None
    mb = mask(base)
    open_i, close_i = enclosing_block(mb, dec["span"][0], d["bstart"])
    if open_i is None or open_i == d["bstart"]:
        return None
    at = decls[-1]["span"][1] if decls else blk_start
    if not is_bare_block(mb, open_i):
        # a control-flow body: lift the declaration alone, leave the braces alone
        cand = base[:dec["span"][0]] + base[dec["span"][1]:]
        cand = cand[:at] + render_decl(dec, indent=decls[-1]["indent"] if decls else "    ") + cand[at:]
        return "s3_hoist_decl(%s)" % v, cand
    # a bare block: hoist its declarations and dissolve it
    os_, oe = line_span(base, open_i)
    cs, ce = line_span(base, close_i)
    if base[os_:oe].strip() != "{" or base[cs:ce].strip() != "}":
        return None
    inner = base[oe:cs]
    lines = inner.splitlines(True)
    hoisted, rest, k = [], [], 0
    while k < len(lines):
        if not lines[k].strip():
            break
        p = parse_decl_line(lines[k])
        if not p:
            break
        hoisted.append(p)
        k += 1
    if not any(p["name"] == v for p in hoisted):
        return None
    rest = lines[k:]
    outer = base[os_:oe]
    block_indent = outer[:len(outer) - len(outer.lstrip())]
    unit = None
    for ln in lines:
        if ln.strip():
            ind = ln[:len(ln) - len(ln.lstrip())]
            if not ind.startswith(block_indent):
                return None
            extra = ind[len(block_indent):]
            unit = extra if unit is None or len(extra) < len(unit) else unit
    if not unit:
        return None
    ded, cut = [], block_indent + unit
    for ln in rest:
        ded.append(block_indent + ln[len(cut):] if ln.startswith(cut) else ln)
    newdecls = "".join(render_decl(p, indent=block_indent) for p in hoisted)
    cand = base[:os_] + "".join(ded) + base[ce:]
    cand = cand[:at] + newdecls + cand[at:]
    return "s3_dissolve_block(%s)" % v, cand


def s4_widen(base, target):
    """A narrow temporary becomes `s32`."""
    v = target.get("var")
    d = def_by_name(base, target["fn"]) if v else None
    if d is None:
        return None
    dec = body_decl(base, d, v)
    if dec is None or dec["arr"] or "*" in dec["type"] or dec["type"] not in NARROW:
        return None
    s, e = dec["span"]
    cand = base[:s] + render_decl(dec, typ="s32") + base[e:]
    return "s4_widen(%s:%s->s32)" % (v, dec["type"]), cand


RMW = re.compile(r"(?m)^([ \t]*)([A-Za-z_]\w*) = (.+);\n[ \t]*\2 ([-+*/&|^]|<<|>>)= (.+);\n[ \t]*(.+) = \2;\n")

def s4_fold(base, target):
    """`t = *p; t op= k; *p = t;` collapses into the memory operand and the temporary goes."""
    d = def_by_name(base, target["fn"])
    if d is None:
        return None
    mb = mask(base)
    for m in RMW.finditer(base):
        if not (d["bstart"] < m.start() < d["bend"]):
            continue
        w, lhs, op, k, store = m.group(2), m.group(3), m.group(4), m.group(5), m.group(6)
        if lhs.strip() != store.strip():
            continue
        uses = [u for u in re.finditer(r"\b%s\b" % re.escape(w), mb) if d["bstart"] < u.start() < d["bend"]]
        dec = body_decl(base, d, w)
        if dec is None or len(uses) != 4:               # the declaration and the three statements
            continue
        cand = base[:m.start()] + "%s%s %s= %s;\n" % (m.group(1), lhs, op, k) + base[m.end():]
        s, e = dec["span"]
        cand = cand[:s] + cand[e:]
        return "s4_fold_rmw(%s)" % w, cand
    return None


def s4_register(base, target):
    """Keep the storage class, drop the asm binding."""
    v = target.get("var")
    d = def_by_name(base, target["fn"]) if v else None
    if d is None:
        return None
    dec = body_decl(base, d, v)
    if dec is None or dec["type"].startswith("register"):
        return None
    s, e = dec["span"]
    cand = base[:s] + render_decl(dec, typ="register " + dec["type"]) + base[e:]
    return "s4_register(%s)" % v, cand


PRIMARY = re.compile(r"^&?[A-Za-z_]\w*(?:\[[^\[\]]*\]|\.\w+|->\w+)*$|^[-+]?(?:0[xX])?[0-9A-Fa-f]+$")

def s4_fold_use(base, target):
    """A temporary written once and read once folds into its use and the declaration goes."""
    v = target.get("var")
    d = def_by_name(base, target["fn"]) if v else None
    if d is None:
        return None
    dec = body_decl(base, d, v)
    if dec is None or dec["arr"]:
        return None
    mb = mask(base)
    uses = [u for u in re.finditer(r"\b%s\b" % re.escape(v), mb)
            if d["bstart"] < u.start() < d["bend"] and not dec["span"][0] <= u.start() < dec["span"][1]]
    if dec["init"]:
        if len(uses) != 1:
            return None
        expr, kill, read = dec["init"], dec["span"], uses[0]
    else:
        if len(uses) != 2:
            return None
        write, read = uses
        ls, le = line_span(base, write.start())
        m = re.match(r"^[ \t]*%s\s*=(?!=)([^;\n]*);[ \t]*$" % re.escape(v), base[ls:le].rstrip("\n"))
        if not m:
            return None
        expr, kill = m.group(1).strip(), (ls, le)
    if not expr or calls_between(mask(expr), 0, len(expr)):
        return None                                    # a call would move across statements
    if read.start() < kill[1]:
        return None                                    # the read comes first
    sub = expr if PRIMARY.match(expr) else "(%s)" % expr
    cand = base[:read.start()] + sub + base[read.end():]
    cand = cand[:kill[0]] + cand[kill[1]:]
    return "s4_fold_use(%s)" % v, cand


INC = re.compile(r"^[ \t]*([A-Za-z_]\w*)[ \t]*(?:\+= 1|\+\+|-= 1|--)[ \t]*;[ \t]*$")

def sb_sink_increment(text, base, target):
    """A loop-counter increment standing before the fence sinks to the end of the loop body."""
    mt = mask(text)
    open_i, close_i = enclosing_block(mt, target["site"][3], 0)
    if open_i is None:
        return None
    cond = loop_cond(mt, open_i, close_i)
    if cond is None:
        return None
    counters = set(re.findall(r"\b[A-Za-z_]\w*\b", cond))
    head = text[open_i:target["site"][3]]
    inc = None
    for ln in head.splitlines():
        m = INC.match(ln)
        if m and m.group(1) in counters:
            inc = ln
    if inc is None:
        return None
    lines = base.splitlines(True)
    hits = [i for i, ln in enumerate(lines) if ln.rstrip("\n") == inc]
    if len(hits) != 1:
        return None
    i = hits[0]
    del lines[i]
    dep = 0
    end = None
    for j in range(i, len(lines)):
        dep += lines[j].count("{") - lines[j].count("}")
        if dep < 0:
            end = j
            break
    if end is None:
        return None
    lines.insert(end, inc + "\n")
    return "sb_sink_increment(%s)" % INC.match(inc).group(1), "".join(lines)


MENU = [s1_param_counter, s2_split_groups, s3_hoist, s4_widen, s4_fold, s4_fold_use, s4_register]

def candidates(text, pins, keep, problems=None):
    """[(label, candidate text)], menu step by menu step; `keep` = the pins that stay."""
    drop = [p for p in pins if p not in keep]
    if not drop:
        return []
    base = erase_indices(text, [p["i"] for p in drop])
    out = []
    seen = {base, text}
    for fn in MENU:                                    # step by step, pins in source order
        for target in drop:
            if target["macro"] == "ASM_SCHED_BARRIER":
                continue
            try:
                got = fn(base, target)
            except Exception as e:                     # a shape the parser cannot express
                if problems is not None:
                    problems.append("%s: %r" % (fn.__name__, e))
                got = None
            if not got or got[1] in seen:
                continue
            seen.add(got[1])
            out.append(got)
    for target in drop:
        if target["macro"] != "ASM_SCHED_BARRIER":
            continue
        try:
            got = sb_sink_increment(text, base, target)
        except Exception as e:
            if problems is not None:
                problems.append("sb_sink_increment: %r" % (e,))
            got = None
        if got and got[1] not in seen:
            seen.add(got[1])
            out.append(got)
    return out


class T:
    name = "t9_regpins"; level = 5
    needs_verify = True

    @staticmethod
    def eligible(text, row, census):
        try:
            live_pins(text, row)
        except Refusal as e:
            return str(e)
        except Exception as e:                          # a plugin bug is a refusal, never a crash
            return "parse error: %r" % (e,)
        return None

    @staticmethod
    def apply_verified(text, row, census, verify_fn):
        try:
            pins = live_pins(text, row)
        except Refusal as e:
            return None, {"refused": [str(e)]}
        except Exception as e:
            return None, {"refused": ["parse error: %r" % (e,)]}
        info = {"pins": len(pins), "classes": [p["cls"] for p in pins],
                "macros": [p["macro"] for p in pins], "tried": [], "steps": [], "runs": 0}
        cur, npins = text, len(pins)
        refused = []
        while True:
            try:
                pins = live_pins(cur, row)
            except Refusal as e:
                refused.append("after a step: " + str(e))
                break
            if not pins:
                break
            rounds = [[]] if len(pins) == 1 else [[], "single"]
            hit = None
            for phase in rounds:
                if phase == "single":
                    cands = []
                    for p in pins:                      # erase this pin alone: pin-reduction
                        cands += candidates(cur, pins, [q for q in pins if q is not p], refused)
                else:
                    cands = candidates(cur, pins, [], refused)
                for label, cand in cands:
                    if info["runs"] >= BUDGET:
                        refused.append("verify budget (%d) spent" % BUDGET)
                        break
                    info["runs"] += 1
                    info["tried"].append(label)
                    v = verify_fn(cand)
                    if v.get("exact"):
                        hit = (label, cand)
                        break
                    if v.get("status") != "ok":
                        refused.append("%s build-failed" % label)
                if hit or info["runs"] >= BUDGET:
                    break
            if not hit:
                if not info["tried"]:
                    refused.append("no candidate: the menu does not express this row's shape")
                break
            info["steps"].append(hit[0])
            cur = hit[1]
        left = len(sites_of(cur))
        info.update({"pins_left": left, "pins_removed": npins - left})
        if cur == text or not info["steps"]:
            return None, dict(info, refused=(refused or ["no exact candidate"])[:6])
        if refused:
            info["refused"] = refused[:6]
        return cur, info

    @staticmethod
    def apply(text, row, census):
        """Unverified first candidate - for inspection only; the sweep always verifies."""
        try:
            pins = live_pins(text, row)
        except Refusal:
            return None
        cands = candidates(text, pins, [])
        return cands[0][1] if cands else None
