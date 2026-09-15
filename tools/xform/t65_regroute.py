"""T65: probe-directed register routing - create the suggestion, or change the allocno order.

MECHANISM (read from toolchain/gcc-src/2.7.2, not assumed).

`local-alloc.c combine_regs()` (the qty_phys_sugg block, 2.7.2 lines ~1792-1834, reached from
`block_alloc`'s copy handling) is the ONLY producer of a local suggestion: when one side of a copy
insn is a HARD register R and the other a pseudo, the pseudo's quantity gets `qty_phys_sugg[q] |= R`
(`qty_phys_copy_sugg` when the copy may be saved).  `block_alloc` then runs a first allocation pass
over the suggested quantities only (`find_free_reg(..., just_try_suggested=1)`, local-alloc.c
~1469-1477), so a suggested quantity is allocated BEFORE the priority order and tries R first.
`global.c allocno_compare` orders global allocnos by
`floor_log2(n_refs) * n_refs / live_length * size`, ties by allocno number.

So the two probe knobs have exactly two C levers:

  sugg        a REAL copy between the variable and a hard register.  Before reload this port's RTL
              names a hard GPR in only three places: `(reg:SI 4 a0)`..`(reg:SI 7 a3)` for the
              parameters at entry and for call-argument setup (`FUNCTION_ARG`, mips.h), and
              `(reg:SI 2 v0)` for a call's result and for the function's own return value
              (`GP_RETURN = GP_REG_FIRST + 2`, mips.h 1876; `STATIC_CHAIN_REGNUM` is also 2 but this
              port never nests functions).  Therefore the C moves are: make the variable BE the
              returned value, BE the value a call returns, or BE the k-th argument / the k-th
              parameter.
  order-swap  one fewer or one more REAL reference, or a shorter or longer lifetime, on the target
              (inline a single-use definition, hoist a repeated expression into the variable, split
              at a redefinition, sink a definition to its first use, merge a disjoint neighbour).
              Never a fake use: a reference that exists only to move the sort is scaffolding.

THE $3 FINDING (measured, work/native_lane/r28_probe/scratch/fix, gcc-2.7.2 -O2 -G0 -da).  NO insn
in any dump, before OR after reload, names hard register 3.  `$3` (v1) exists only as the second
word of a `(reg:DI 2 v0)` pair - a 64-bit value in the return register - and `combine_regs` strips
the SUBREG and records the suggestion at the FIRST regno (`ureg`), which is 2.  A `sugg $3` site is
therefore unreachable by any C edit: no copy that C can write sets bit 3 of `qty_phys_sugg`.  The
same holds for every register this port never names before reload ($8-$15, $16-$23, $24-$25): they
appear first at reload.  Only $2 and $4-$7 are nameable, and a DImode parameter or return value
occupies a PAIR, so the odd half of such a pair ($5 behind a DImode $4, $7 behind a DImode $6, $3
behind a DImode $2) is unreachable too.  Such a site is skipped with the reason
`sugg-register-never-named-pre-reload` UNLESS the probe recorded another sufficient knob
(`order-swap`, `refs-1`, `shorten-*`), in which case it is routed to the order-swap moves and
journalled as `fallback:<knob>`.

WHAT THE PROBE GIVES US.  `work/alloc_probe/reg_all/<container>_<func>.json` (tools/alloc_probe.py)
carries, per ASM_REG site, `var`, `register`, `owner`, `minimal_knob`, `sufficient` and
`competitor`/`competitor_names`.  `minimal_knob` is the EARLIEST sufficient knob in the probe's
order, not the only one, so `sufficient` is read too.  The report is used only when its `sha`
equals the current text's (a stale report describes a text that no longer exists).

CANDIDATES.  Per eligible site, with that site's pin erased (only that one: an erasure that lands on
its own is pin_search's win, so the bare erasure is measured and never verified), the targeted moves
above, each screened with `xform.screen.compile_s`/`sdiff` against the PINNED listing; `vf` is called
only at distance 0, on a candidate that passes `pin_search_engine.improves`, keeps `unscored_text`
and passes `t60_alloc_inputs.allowed` (the shared scaffolding refusal).  Budgets `T65_SCREENS` (400)
and `T65_VERIFY` (6) per row; the search restarts on the new text after a win.

Every candidate label carries its origin so the evaluation can separate this generator's DELTA from
the menu that was already replayed: `t65:*` are new moves, `t51:*`, `nat:*` and `t60:*` are imported
(t51.candidates' single-set / fuse / move, natural's splitcursor / host / hostwide / unhost /
declorder, t60.reuse_candidates).  Imported moves are offered only on the order-swap class, where
the lever is a lifetime or a reference count; the sugg class is entirely `t65:*`.

No scaffolding is ever emitted, no qualifier is dropped or added, and every substitution that could
change a width or a signedness carries the variable's own type as a cast.

VALUE PRESERVATION (round 28 review; every rule below is a refusal, never a repair).

  1. `Ctx.standalone(i)` - no move expands, deletes or inserts before a line that is the brace-less
     controlled statement of an `if`/`else`/`for`/`while`/`do`, or that carries a label.  Without it
     `if (a) return g(a);` became `if (a) v = g(a); return v;` - the second statement escapes the
     conditional and the tail of the function goes unreachable.
  2. `Ctx.occ` skips a member reference (`s->v`, `s.v`): `\bv\b` does not distinguish a local from a
     struct member, and a rename or a substitution at such a position writes a DIFFERENT object at a
     different offset.  `param_merge`'s rename now walks those positions in the MASKED text, so it
     can no longer rewrite a comment either.
  3. A value substitution is emitted only where both sides' types are KNOWN and hold the same 32
     bits (`same_word`: the identical type, or two 32-bit integer/pointer types of the same
     pointer-ness).  `hoist` replaces the defining expression only where it is the WHOLE right-hand
     side of an assignment whose destination's type passes that test (`lvalue_type` resolves a
     local, a parameter and a `->member` through the row's own typedefs), or the whole `return`
     expression of a function whose return type does.  `call-via` requires the callee's in-file
     return type: a `void` callee used to produce `v = h(...);`, an `f32` one a truncated float, and
     an undeclared callee is refused outright.  `arg-via`, `arg-sub` and `arg-hoist` require V's
     type to be a full machine word AND the routed expression to carry no in-file evidence of a
     floating or 64-bit type (`narrow_expr`: no such literal or cast, and no identifier that
     `wide_names` saw declared that way anywhere in the row).  m2c prototypes are EMPTY - they
     declare no parameter types at all - so the argument's own spelling is the only thing there is
     to check, and the test is evidence, not proof: an identifier the row never declares is assumed
     narrow.
  4. A replacement position must be a whole token (`\b` on both ends) and a whole subexpression; the
     old substring match turned `xa + b` into `xv` and `a + b * 2` into `v * 2`.
"""
import collections
import json
import os
import re
import sys
from pathlib import Path

ROOT = next(p for p in Path(__file__).resolve().parents if (p / "tools/common.py").is_file())
if str(ROOT / "tools") not in sys.path:
    sys.path.insert(0, str(ROOT / "tools"))

from common import sha_text
from pin_census import sites_of, unscored_text, asm_blocker, arm_labels, HAS_PP_RE
from pin_sites import erase_many
from pin_search_engine import improves
from alloc_trace import hard_number, var_name
from xform.screen import compile_s, sdiff
from xform.t12_stmtorder import mask
from xform import t51_sched_order as S
from xform import natural as N
from xform import t60_alloc_inputs as A

SCREEN = compile_s                      # module-level hook: the unit tests replace it
PROBE_DIR = ROOT / "work/alloc_probe/reg_all"
KNOBS = ("sugg", "order-swap")
FALLBACK_KNOBS = ("order-swap", "refs-1", "refs+1", "shorten-birth", "shorten-death",
                  "competitor-refs-1")
# The only hard GPRs this port's RTL names before reload (see the module docstring).
NAMEABLE = {2, 4, 5, 6, 7}
ARG_FIRST = 4
IMPORT_CAP = int(os.getenv("T65_IMPORT_CAP", "8"))
CALLS_PER_SITE = 6
ID = r"[A-Za-z_]\w*"
CONTROL = re.compile(r"\b(if|else|for|while|return|goto|case|switch|break|continue|default)\b")
CALL = re.compile(r"\b(?!sizeof\b|return\b|if\b|while\b|for\b|switch\b)" + ID + r"\s*\(")
# A definition's `{` sits on the header line in most rows and on the next line in many others.
FUNC_DEF = re.compile(r"^(?P<ret>[A-Za-z_][\w \t]*?[ \t*])(?P<name>" + ID + r")[ \t]*"
                      r"\((?P<params>[^()]*)\)[ \t]*\n?[ \t]*\{", re.M)
WIDE = re.compile(r"\b(float|double|f32|f64|long\s+long|s64|u64)\b")
BIN_OP = r"(?:<<|>>|[-+*/%&|^])"


# --------------------------------------------------------------------------- probe report

def probe_path(row):
    return Path(os.getenv("T65_PROBE_DIR", str(PROBE_DIR))) / (row["id"].replace("/", "_") + ".json")


def probe_report(text, row):
    """(report, None) when a fresh report exists for this exact text, else (None, reason)."""
    p = probe_path(row)
    if not p.is_file():
        return None, "no probe report"
    try:
        rep = json.loads(p.read_text())
    except Exception as e:
        return None, "probe report unreadable: %r" % (e,)
    if rep.get("sha") != sha_text(text):
        return None, "probe report stale"
    return rep, None


def plan_sites(rep, skips=None):
    """The probe sites this generator targets, each with its route and its refusal reason.

    [(record, route, note)] where route is 'sugg' or 'order' and note names a fallback or None.
    A site with an unusable knob is counted in `skips` and dropped."""
    out = []
    for rec in rep.get("sites") or []:
        knob = rec.get("minimal_knob")
        if knob not in KNOBS:
            if skips is not None:
                skips["knob-not-targeted:%s" % (knob,)] += 1
            continue
        if rec.get("status") not in (None, "ok"):
            if skips is not None:
                skips["site-status:%s" % rec.get("status")] += 1
            continue
        try:
            reg = int(str(rec.get("register")))
        except (TypeError, ValueError):
            if skips is not None:
                skips["register-unparsed"] += 1
            continue
        if knob == "order-swap":
            out.append((rec, "order", None))
            continue
        if reg in NAMEABLE:
            out.append((rec, "sugg", None))
            continue
        other = [k for k in (rec.get("sufficient") or []) if k in FALLBACK_KNOBS]
        if other:
            out.append((rec, "order", "fallback:" + other[0]))
        elif skips is not None:
            skips["sugg-register-never-named-pre-reload"] += 1
    return out


def live_site(text, rec):
    """The live ASM_REG site tuple in `text` matching the probe record, or None."""
    want = str(rec.get("register")).strip("$\"")
    var = rec.get("var")
    best = None
    for s in sites_of(text):
        if s[0] != "reg":
            continue
        if hard_number(s[2]) != hard_number(want) or var_name(s[6]) != var:
            continue
        if best is None or abs(s[5] - (rec.get("line") or s[5])) < abs(best[5] - (rec.get("line") or best[5])):
            best = s
    return best


# --------------------------------------------------------------------------- text model

def norm_type(t):
    """'unsigned  char *' -> 'unsigned char*': one spelling per type, qualifiers kept."""
    return re.sub(r"\s*\*\s*", "*", " ".join((t or "").split()))


# A floating or 64-bit literal: `1.5`, `.5f`, `2e3`, `1.0f`, `3LL`.
FLOAT_LIT = re.compile(r"(?:\b\d+\.\d*|\.\d+|\b\d+(?:\.\d*)?[eE][-+]?\d+)[fFlL]*|\b\d+[fF]\b"
                       r"|\b\d+[uU]?(?:LL|ll)\b")
DECL_ANY = re.compile(r"\b(?P<type>float|double|f32|f64|s64|u64|long\s+long)\b[\s*]*(?P<name>"
                      + r"[A-Za-z_]\w*" + r")\s*(?=[;,\[\)=({])")
PROTO = re.compile(r"^[ \t]*(?P<ret>(?:extern[ \t]+)?[A-Za-z_][\w \t*]*?)(?<=[ \t*])"
                   r"(?P<name>[A-Za-z_]\w*)[ \t]*\((?P<params>[^;{)]*)\)[ \t]*;", re.M)
TYPEDEF_STRUCT = re.compile(r"\btypedef\s+struct\s+(?:[A-Za-z_]\w*)?\s*\{(?P<body>[^{}]*)\}\s*"
                            r"(?P<name>[A-Za-z_]\w*)\s*;", re.S)
FIELD = re.compile(r"(?P<type>[A-Za-z_][\w \t]*?[\s*])(?P<name>[A-Za-z_]\w*)\s*"
                   r"(?:\[[^\]]*\])?\s*;")
MEMBER_BEFORE = re.compile(r"(?:->|(?<![.\d])\.)\s*$")


def wide_names(masked):
    """Every identifier the file ever declares with a floating or 64-bit type.

    m2c prototypes are empty (`s32 func_700750E0();`), so a call argument's type can never be read
    off the callee.  The only check available is the argument's own spelling, and this set is what
    makes it possible: a name declared `f32` anywhere in the row - local, parameter, global, struct
    member or function return - makes every expression naming it unroutable."""
    return {m["name"] for m in DECL_ANY.finditer(masked)}


def prototypes(masked):
    """callee name -> its declared return type (m2c writes one line per extern)."""
    out = {}
    for m in PROTO.finditer(masked):
        if re.search(r"\b(register|ASM_REG|return|if|while|for|switch)\b", m.group(0)):
            continue                              # a pinned declaration, not a prototype
        ret = re.sub(r"\bextern\b", "", m["ret"]).strip()
        if ret and ret not in ("return", "goto", "typedef", "else"):
            out.setdefault(m["name"], ret)
    return out


def struct_fields(masked):
    """struct typedef name -> {member: type} (the row's own typedefs, one nesting level)."""
    out = {}
    for m in TYPEDEF_STRUCT.finditer(masked):
        out[m["name"]] = {f["name"]: f["type"].strip() for f in FIELD.finditer(m["body"])}
    return out


def split_args(s):
    """Top-level comma split of an argument list body; [(start, end)] into `s`."""
    out, depth, start = [], 0, 0
    for i, c in enumerate(s):
        if c in "([":
            depth += 1
        elif c in ")]":
            depth -= 1
        elif c == "," and depth == 0:
            out.append((start, i))
            start = i + 1
    if s.strip():
        out.append((start, len(s)))
    return out


def arg_slots(params):
    """[(type, name)] indexed by hard register slot ($4 + i), or None if the ABI slot is unclear.

    o32 gives each scalar or pointer one slot; a 64-bit or floating parameter takes a pair (and a
    float in slot 0/1 goes to the FPU), so a prototype holding one is refused outright."""
    body = params.strip()
    if body in ("", "void"):
        return []
    if "(" in body:
        return None
    out = []
    for a, b in split_args(body):
        piece = body[a:b].strip()
        if not piece or WIDE.search(piece):
            return None
        m = re.match(r"(?P<type>.*?[\s*])(?P<name>" + ID + r")\s*(?:\[\s*\d*\s*\])?$", piece)
        if not m:
            return None
        out.append((m["type"].strip(), m["name"]))
    return out


class Ctx:
    """One erased text, the variable the pin named, and the enclosing function."""

    def __init__(self, text, var, reg, site_line):
        self.text = text
        self.m = mask(text)
        self.lines = text.splitlines(True)
        self.ml = self.m.splitlines(True)
        self.off, o = [], 0
        for ln in self.lines:
            self.off.append(o)
            o += len(ln)
        self.labels = arm_labels(text) if HAS_PP_RE.search(text) else None
        self.var, self.reg, self.site_line = var, reg, site_line
        self.decl = S.declarations(text)
        self.scopes, stack = {}, []
        for i, c in enumerate(self.m):
            if c == "{":
                stack.append(i)
            elif c == "}" and stack:
                self.scopes[stack.pop()] = i
        self.fn = self._function()
        self.params = arg_slots(self.fn["params"]) if self.fn else None
        self.wide = wide_names(self.m)
        self.protos = prototypes(self.m)
        self.fields = struct_fields(self.m)

    def _function(self):
        anchor = self.off[min(max(self.site_line - 1, 0), len(self.off) - 1)]
        best = None
        for m in FUNC_DEF.finditer(self.m):
            b = self.m.find("{", m.end() - 1)
            depth, e = 0, None
            for i in range(b, len(self.m)):
                if self.m[i] == "{":
                    depth += 1
                elif self.m[i] == "}":
                    depth -= 1
                    if depth == 0:
                        e = i
                        break
            if e is None or not (b <= anchor <= e):
                continue
            best = {"ret": m["ret"].strip(), "name": m["name"], "params": m["params"],
                    "head": m.start(), "params_start": m.start("params"),
                    "params_end": m.end("params"), "body": b, "end": e}
        return best

    # -- line helpers -------------------------------------------------------
    def in_scope(self, name, pos):
        """`name`'s declaration block contains `pos`.

        Row files declare locals in nested blocks (`if (..) { register s8 *p ASM_REG(..); .. }`),
        and S.declarations is flat, so without this a move happily writes the variable where the
        compiler cannot see it."""
        d = self.decl.get(name)
        if not d:
            return False
        span = next(((a, b) for a, b in sorted(self.scopes.items(), reverse=True)
                     if a < d["start"] < b), None)
        return span is not None and span[0] < pos < span[1]

    def line_of(self, pos):
        lo, hi = 0, len(self.off) - 1
        while lo < hi:
            mid = (lo + hi + 1) // 2
            if self.off[mid] <= pos:
                lo = mid
            else:
                hi = mid - 1
        return lo

    def arm_ok(self, i):
        return self.labels is None or i >= len(self.labels) or self.labels[i] not in ("port", "dead")

    def simple(self, i):
        """An editable one-line statement INSIDE the target function: no control, brace, label, pin.

        The body restriction matters: a row file opens with `extern` prototypes, which are
        statements by every other test here and must never be rewritten."""
        s = self.ml[i]
        t = s.strip()
        if not t or not self.arm_ok(i):
            return False
        if self.fn is None or not (self.fn["body"] <= self.off[i] < self.fn["end"]):
            return False
        if any(c in s for c in "{}#") or CONTROL.search(s) or t.startswith("ASM_"):
            return False
        if re.match(r"^\s*" + ID + r"\s*:\s*$", s) or "ASM_" in s:
            return False
        return t.endswith(";")

    def straight(self, a, b):
        """Every line strictly between a and b is a plain one-line statement (no control flow)."""
        return all(self.simple(i) or not self.ml[i].strip() for i in range(a + 1, b))

    def member_ref(self, pos):
        """`pos` is the member half of `x->name` / `x.name` - a different object, not the local."""
        return bool(MEMBER_BEFORE.search(self.m[max(0, pos - 24):pos]))

    def occ(self, name, lo=None, hi=None):
        """Occurrences of `name` in the masked function body, declarations included.

        A `->name` / `.name` member reference is NOT an occurrence of the local: rewriting one
        writes a different object at a different offset (round 28 review, defect 2)."""
        lo = self.fn["body"] if lo is None and self.fn else (lo or 0)
        hi = self.fn["end"] if hi is None and self.fn else (hi or len(self.m))
        return [mm for mm in re.finditer(r"\b" + re.escape(name) + r"\b", self.m)
                if lo <= mm.start() < hi and not self.member_ref(mm.start())]

    def standalone(self, i):
        """Line i may be expanded into two, deleted, or have a statement inserted before it.

        False when the line is the brace-less controlled statement of an `if`/`else`/`for`/`while`/
        `do`, or when a label sits in front of it: in either case a second statement (or the loss of
        this one) changes which statements the control transfer covers."""
        head = self.m[:self.off[i]].rstrip()
        if not head:
            return True
        if re.search(r"\b(?:else|do)$", head) or head.endswith(":"):
            return False
        if head.endswith(")"):
            depth = 0
            for k in range(len(head) - 1, -1, -1):
                if head[k] == ")":
                    depth += 1
                elif head[k] == "(":
                    depth -= 1
                    if depth == 0:
                        return not re.search(r"\b(if|for|while|switch)$", head[:k].rstrip())
            return True
        return True

    def lvalue_type(self, s):
        """The declared type of a simple lvalue, or None when it cannot be resolved.

        Handles a local, a parameter, `((T *)E)->m` and `p->m` / `p.m` where `p`'s own type names a
        typedef the row defines.  Anything else is unknown, and an unknown type refuses the move."""
        s = (s or "").strip()
        if re.fullmatch(ID, s):
            return self.dtype(s) or next((t for t, n in (self.params or []) if n == s), None)
        m = re.fullmatch(r"\(\s*\(\s*(?:struct\s+)?(?P<t>" + ID + r")\s*\*\s*\)\s*[^()]+\)\s*"
                         r"(?:->|\.)\s*(?P<m>" + ID + r")", s)
        if not m:
            b = re.fullmatch(r"(?P<p>" + ID + r")\s*(?:->|\.)\s*(?P<m>" + ID + r")", s)
            if not b:
                return None
            base = self.dtype(b["p"]) or next((t for t, n in (self.params or [])
                                               if n == b["p"]), None)
            if not base:
                return None
            bt = re.fullmatch(r"(?:struct\s+)?(" + ID + r")\s*\**",
                              norm_type(base).replace("*", " *").strip())
            if not bt:
                return None
            return (self.fields.get(bt.group(1)) or {}).get(b["m"])
        return (self.fields.get(m["t"]) or {}).get(m["m"])

    def written_at(self, pos, name):
        """The occurrence of `name` at `pos` is assigned or incremented, not read.

        Substituting an expression for such an occurrence produces `(s32)(a + b) = 1;` - not a
        semantic change (it does not compile) but a wasted screen, and the guard is one line."""
        after = self.m[pos + len(name):pos + len(name) + 4]
        if re.match(r"\s*(?:\+\+|--|<<=|>>=|[-+*/%&|^]?=(?!=))", after):
            return True
        return bool(re.search(r"(?:\+\+|--)\s*$", self.m[max(0, pos - 3):pos]))

    def narrow_expr(self, expr):
        """`expr` is certainly a 32-bit integral or pointer value (see the module docstring, 3)."""
        if WIDE.search(expr) or FLOAT_LIT.search(expr):
            return False
        return not (set(re.findall(ID, expr)) & self.wide)

    def dtype(self, name):
        d = self.decl.get(name)
        return d["type"] if d else None

    def writable(self, name):
        """A plain local or parameter this generator may assign to."""
        d = self.decl.get(name)
        ty = d["type"] if d else next((t for t, n in (self.params or []) if n == name), None)
        if ty is None:
            return False
        if re.search(r"\b(const|volatile|static)\b", ty):
            return False
        if re.search(r"&\s*" + re.escape(name) + r"\b", self.m):
            return False
        return True

    def uses_between(self, name, a, b):
        return any(a < mm.start() < b for mm in self.occ(name))

    def writes_between(self, names, a, b):
        """Any identifier of `names` assigned, incremented or address-taken strictly between."""
        seg = self.m[a:b]
        for n in names:
            if re.search(r"\b" + re.escape(n) + r"\b\s*(?:\[[^\]]*\])?\s*(?:[-+*/%&|^]?=(?!=)|\+\+|--)", seg):
                return True
            if re.search(r"(?:\+\+|--)\s*\b" + re.escape(n) + r"\b", seg):
                return True
            if re.search(r"&\s*\b" + re.escape(n) + r"\b", seg):
                return True
        return True if re.search(r"\b(goto|case|default)\b|:\s*$", seg, re.M) else False

    def assigns(self, name):
        """[(line index, rhs)] for every `name = rhs;` plain assignment statement."""
        out = []
        for i in range(len(self.ml)):
            if not self.simple(i):
                continue
            a = S.ASSIGN.match(self.ml[i])
            if a and a["lhs"].strip() == name:
                out.append((i, self.lines[i][a.start("rhs"):a.end("rhs")]))
        return out

    def indent(self, i):
        return re.match(r"[ \t]*", self.lines[i])[0]

    def replace_lines(self, edits):
        """edits: {line index: replacement text (may be '' to drop the line)} -> new text."""
        out = list(self.lines)
        for i, v in edits.items():
            out[i] = v
        return "".join(out)


def cast_of(ctx, ty, expr):
    """`expr` given `ty`'s value exactly: the variable's own cast, never doubled."""
    e = expr.strip()
    already = re.fullmatch(r"\(\s*" + re.escape(ty).replace(r"\ ", r"\s*") +
                           r"\s*\)\s*[&*]?\s*" + ID + r"(?:(?:->|\.)\w+|\[[^\[\]]*\])*", e)
    return "(" + e + ")" if already else "((" + ty + ")(" + e + "))"


# --------------------------------------------------------------------------- sugg $2 moves

def return_moves(ctx, skips):
    """(i) `return E;` -> `V = E; return V;`  and  (iii) `return V op K;` -> the op through V."""
    V, fn = ctx.var, ctx.fn
    if not fn:
        skips["no-enclosing-function"] += 1
        return
    if not ctx.writable(V):
        skips["target-not-writable"] += 1
        return
    rty, vty = norm_type(fn["ret"]), norm_type(ctx.dtype(V) or "")
    for i in range(len(ctx.ml)):
        if not ctx.arm_ok(i) or "ASM_" in ctx.ml[i]:
            continue
        m = re.match(r"^(?P<ind>[ \t]*)return\s+(?P<e>.+);\s*$", ctx.ml[i])
        if not m or ctx.off[i] < fn["body"] or ctx.off[i] > fn["end"]:
            continue
        expr = ctx.lines[i][m.start("e"):m.end("e")].strip()
        if expr == V:
            continue
        if rty != vty or not vty:
            skips["return-type-mismatch"] += 1
            continue
        if not ctx.in_scope(V, ctx.off[i]):
            skips["target-out-of-scope-at-the-return"] += 1
            continue
        if not ctx.standalone(i):
            skips["return-is-a-brace-less-controlled-statement"] += 1
            continue
        ind = m["ind"]
        op = re.fullmatch(r"\s*" + re.escape(V) + r"\s*(?P<op>" + BIN_OP + r")\s*(?P<k>.+?)\s*", expr)
        if op:
            yield ("t65:ret-op:%d" % (i + 1),
                   ctx.replace_lines({i: "%s%s = %s %s %s;\n%sreturn %s;\n" %
                                      (ind, V, V, op["op"], op["k"], ind, V)}))
        if re.search(r"\b" + re.escape(V) + r"\b", expr):
            continue
        if re.search(r"(?<![=!<>])=(?!=)|\+\+|--", expr):
            skips["return-expression-has-a-side-effect"] += 1
            continue
        yield ("t65:ret-via:%d" % (i + 1),
               ctx.replace_lines({i: "%s%s = %s;\n%sreturn %s;\n" % (ind, V, expr, ind, V)}))


def call_result_moves(ctx, skips):
    """(ii)/(iv) `W = f(..); V = W op K;` -> `V = f(..); V = V op K;` (the copy goes when W does)."""
    V = ctx.var
    if not ctx.writable(V):
        skips["target-not-writable"] += 1
        return
    vty = ctx.dtype(V)
    if not vty:
        skips["target-not-declared-local"] += 1
        return
    for i in range(len(ctx.ml)):
        if not ctx.simple(i):
            continue
        a = S.ASSIGN.match(ctx.ml[i])
        if not a:
            continue
        W = a["lhs"].strip()
        rhs = ctx.lines[i][a.start("rhs"):a.end("rhs")].strip()
        if W == V or not re.fullmatch(ID, W) or not CALL.match(rhs):
            continue
        if norm_type(ctx.dtype(W) or "") != norm_type(vty):
            continue
        d = ctx.decl.get(W)
        if not d:
            continue
        outside = [mm for mm in ctx.occ(W) if not (d["start"] <= mm.start() < d["end"])]
        if len(outside) != 2:
            skips["call-result-not-single-use"] += 1
            continue
        use = outside[1]
        j = ctx.line_of(use.start())
        if j <= i or not ctx.simple(j) or not ctx.straight(i, j):
            skips["call-result-use-not-straight-line"] += 1
            continue
        b = S.ASSIGN.match(ctx.ml[j])
        if not b or b["lhs"].strip() != V:
            skips["call-result-use-not-a-definition-of-the-target"] += 1
            continue
        if ctx.uses_between(V, ctx.off[i], ctx.off[j]):
            skips["target-read-between-call-and-use"] += 1
            continue
        if not ctx.in_scope(V, ctx.off[i]):
            skips["target-out-of-scope-at-the-call"] += 1
            continue
        use_rhs = ctx.lines[j][b.start("rhs"):b.end("rhs")].strip()
        if len(re.findall(r"\b" + re.escape(W) + r"\b", use_rhs)) != 1:
            continue
        if use_rhs == W and not ctx.standalone(j):
            skips["copy-line-is-a-brace-less-controlled-statement"] += 1
            continue
        new_i = "%s%s = %s;\n" % (ctx.indent(i), V, rhs)
        edits = {i: new_i}
        if use_rhs == W:
            edits[j] = ""
        else:
            edits[j] = "%s%s = %s;\n" % (ctx.indent(j),
                                         V, re.sub(r"\b" + re.escape(W) + r"\b", V, use_rhs))
        drop_decl(ctx, W, edits)
        yield "t65:call-into:%s:%d" % (W, i + 1), ctx.replace_lines(edits)


# Value-preserving destinations for a routed expression: a full machine word, or any pointer
# (every pointer on this target is one 32-bit word, so no bit of the value is lost).
WORD_TYPE = re.compile(r"^(?:s32|u32|int|signed|unsigned|signed int|unsigned int|long|"
                       r"signed long|unsigned long|M2C_UNK|M2C_UNK32|.*\*)$")


def same_word(a, b):
    """Two types that hold the identical 32 bits: the same type, or two full machine words.

    Every 32-bit integer/pointer conversion on this ABI is bit-preserving, so a value that makes
    the round trip through such a local comes back unchanged; `u8`, `s16`, `f32`, a 64-bit type and
    `void` are NOT such types and are refused wherever this is the test."""
    a, b = norm_type(a or ""), norm_type(b or "")
    if not a or not b:
        return False
    if a == b:
        return True
    if a.endswith("*") != b.endswith("*"):
        return False                              # `u8 *v = f();` needs a cast; the screen only
    return bool(WORD_TYPE.match(a) and WORD_TYPE.match(b))   # ever saw it as a build failure


def route_through(ctx, i, a, b, tag, skips, want_type=None):
    """`... E ...` on line i -> `V = E;` before it and V in E's place, when V is dead there.

    Value preservation.  The routed expression is evaluated into V and read back, so the move is the
    identity only when `(V's type)E == E`.  `want_type` carries the routed expression's own type
    when it is knowable (a call's in-file return type) and must then equal V's type exactly;
    otherwise - an argument of an m2c prototype, which declares no parameter types at all - V's type
    must be a full machine word AND the expression must carry no in-file evidence of a floating or
    64-bit type, because such an expression assigned to an `s32` is truncated before the callee ever
    sees it."""
    V = ctx.var
    line, ml = ctx.lines[i], ctx.ml[i]
    expr = line[a:b].strip()
    if not expr or expr == V or not ctx.writable(V):
        skips["route-target-not-writable"] += 1
        return
    if not ctx.in_scope(V, ctx.off[i]):
        skips["route-target-out-of-scope-there"] += 1
        return
    vty = ctx.dtype(V)
    if not vty:
        skips["target-not-declared-local"] += 1
        return
    if re.search(r"\b" + re.escape(V) + r"\b", ml):
        skips["route-target-already-on-the-line"] += 1
        return
    if re.search(r"(?<![=!<>])=(?!=)|\+\+|--|\?", expr):
        skips["route-expression-has-a-side-effect"] += 1
        return
    if not ctx.standalone(i):
        skips["route-line-is-a-brace-less-controlled-statement"] += 1
        return
    if want_type is not None:
        # Exactly the same type, or two full machine words: every 32-bit integer/pointer
        # conversion on this ABI keeps all 32 bits, so `V = E` and `E` are the same value.  A
        # narrower (`u8`, `s16`), floating or `void` result is refused - those do convert.
        if not same_word(want_type, vty):
            skips["route-expression-type-differs-from-the-target"] += 1
            return
        if norm_type(want_type) != norm_type(vty) and not ctx.narrow_expr(expr):
            skips["route-expression-may-be-floating-or-64-bit"] += 1
            return
    else:
        if not WORD_TYPE.match(norm_type(vty)):
            skips["route-would-change-the-value-width"] += 1
            return
        if not ctx.narrow_expr(expr):
            skips["route-expression-may-be-floating-or-64-bit"] += 1
            return
    tail = "".join(mask(x) for x in ctx.lines[i + 1:])
    if not S.later_dead(tail, V):
        skips["route-target-live-after"] += 1
        return
    raw = line[a:b]
    a += len(raw) - len(raw.lstrip())
    b -= len(raw) - len(raw.rstrip())
    new = "%s%s = %s;\n%s" % (ctx.indent(i), V, expr, line[:a] + V + line[b:])
    yield tag, ctx.replace_lines({i: new})


def call_via_moves(ctx, skips):
    """$2: a call's result routed through V (`h(g(x));` -> `V = g(x); h(V);`)."""
    for i, callee, astart, args, close in calls_in(ctx):
        mm = re.search(r"\b" + re.escape(callee) + r"\s*\(", ctx.ml[i])
        if not mm:
            continue
        a, b = mm.start(), close + 1
        asn = S.ASSIGN.match(ctx.ml[i])
        if asn and asn["rhs"].strip() == ctx.ml[i][a:b].strip() and asn["lhs"].strip() == ctx.var:
            continue
        ret = ctx.protos.get(callee)
        if not ret:
            skips["call-via-callee-return-type-unknown"] += 1
            continue
        yield from route_through(ctx, i, a, b, "t65:call-via:%s:%d" % (callee, i + 1), skips,
                                 want_type=ret)


def arg_via_moves(ctx, skips):
    """$4-$7: the k-th argument of a call computed through V (`f(E)` -> `V = E; f(V)`)."""
    slot = ctx.reg - ARG_FIRST
    if ctx.params is None:
        skips["parameter-slots-unresolved"] += 1
        return
    for i, callee, astart, args, close in sorted(calls_in(ctx),
                                                 key=lambda c: abs(c[0] + 1 - ctx.site_line))[:CALLS_PER_SITE]:
        if slot >= len(args):
            skips["call-has-fewer-arguments-than-the-slot"] += 1
            continue
        a, b = args[slot]
        yield from route_through(ctx, i, astart + a, astart + b,
                                 "t65:arg-via:%d:%d" % (slot, i + 1), skips)


def unshare_moves(ctx, skips, var=None):
    """One fewer reference, the variable kept: one use respelled as its defining expression."""
    V = var or ctx.var
    d = ctx.decl.get(V)
    if not d:
        return
    defs = ctx.assigns(V)
    if len(defs) != 1:
        skips["unshare-not-single-definition"] += 1
        return
    i, rhs = defs[0]
    e = rhs.strip()
    if re.search(r"(?<![=!<>])=(?!=)|\+\+|--", e) or CALL.search(e):
        skips["unshare-definition-not-repeatable"] += 1
        return
    ids = set(re.findall(ID, e))
    uses = [mm for mm in ctx.occ(V)
            if not (d["start"] <= mm.start() < d["end"]) and mm.start() > ctx.off[i] + len(ctx.lines[i])]
    if len(uses) < 2:
        skips["unshare-would-leave-a-dead-store"] += 1
        return
    n = 0
    for mm in uses:
        j = ctx.line_of(mm.start())
        if not ctx.simple(j) or not ctx.straight(i, j):
            continue
        if ctx.writes_between(ids | {V}, ctx.off[i] + len(ctx.lines[i]), mm.start()):
            continue
        if ctx.m[max(0, mm.start() - 1):mm.start()] == "&":
            continue
        if ctx.written_at(mm.start(), V):
            skips["unshare-use-is-a-write"] += 1
            continue
        k = mm.start() - ctx.off[j]
        yield ("t65:unshare:%s:%d" % (V, j + 1),
               ctx.replace_lines({j: ctx.lines[j][:k] + cast_of(ctx, d["type"], e) +
                                  ctx.lines[j][k + len(V):]}))
        n += 1
        if n >= 3:
            return


def drop_decl(ctx, name, edits):
    """Remove `name`'s declaration line when the edits leave it unused (t60's whole-line rule)."""
    d = ctx.decl.get(name)
    if not d:
        return
    i = ctx.line_of(d["start"])
    if ctx.ml[i].strip().rstrip(";") != ctx.text[d["start"]:d["end"]].strip().rstrip(";"):
        return                                    # more than one declarator on the line: leave it
    if "ASM_" in ctx.ml[i] or "=" in ctx.ml[i]:
        return
    edits[i] = ""


# --------------------------------------------------------------------------- sugg $4-$7 moves

def calls_in(ctx):
    """[(line index, callee, args_start, [(a, b)])] for every one-line statement holding a call."""
    out = []
    for i in range(len(ctx.ml)):
        if not ctx.simple(i):
            continue
        for mm in CALL.finditer(ctx.ml[i]):
            open_at = mm.end() - 1
            depth, close = 0, None
            for k in range(open_at, len(ctx.ml[i])):
                if ctx.ml[i][k] == "(":
                    depth += 1
                elif ctx.ml[i][k] == ")":
                    depth -= 1
                    if depth == 0:
                        close = k
                        break
            if close is None:
                continue
            body = ctx.ml[i][open_at + 1:close]
            if "(" in body and ")" not in body:
                continue
            out.append((i, mm.group(0)[:-1].strip(), open_at + 1, split_args(body), close))
    return out


def argument_moves(ctx, skips):
    """(i) an argument that already is V's value -> V; (ii) `f(.., V op K, ..)` -> hoisted."""
    V = ctx.var
    slot = ctx.reg - ARG_FIRST
    if ctx.params is None:
        skips["parameter-slots-unresolved"] += 1
        return
    defs = ctx.assigns(V)
    ranked = sorted(calls_in(ctx), key=lambda c: abs(c[0] + 1 - ctx.site_line))[:CALLS_PER_SITE]
    for i, callee, astart, args, close in ranked:
        if slot >= len(args):
            skips["call-has-fewer-arguments-than-the-slot"] += 1
            continue
        a, b = args[slot]
        raw = ctx.lines[i][astart + a:astart + b]
        argk = raw.strip()
        others = [ctx.ml[i][astart + x:astart + y] for k, (x, y) in enumerate(args) if k != slot]
        # (i) the argument already spells V's value
        for di, drhs in defs:
            if di >= i or drhs.strip() != argk or argk == V:
                continue
            if ctx.uses_between(V, ctx.off[di] + len(ctx.lines[di]), ctx.off[i]) or \
                    not ctx.straight(di, i):
                skips["target-redefined-between-definition-and-call"] += 1
                continue
            if ctx.writes_between(set(re.findall(ID, argk)) | {V},
                                  ctx.off[di] + len(ctx.lines[di]), ctx.off[i]):
                skips["argument-operand-changed-before-the-call"] += 1
                continue
            # `f(E)` passes the promoted E; `f(V)` passes the promoted (V's type)E.  Equal only
            # when V is a full word and E cannot be floating or 64-bit (the prototype is empty).
            if not (WORD_TYPE.match(norm_type(ctx.dtype(V) or "")) and ctx.narrow_expr(argk)):
                skips["argument-substitution-may-change-the-value-width"] += 1
                continue
            new = ctx.lines[i][:astart + a] + raw.replace(argk, V, 1) + ctx.lines[i][astart + b:]
            yield "t65:arg-sub:%d:%d" % (slot, i + 1), ctx.replace_lines({i: new})
            break
        # (ii) the argument is V op K and V is dead after the call
        op = re.fullmatch(r"\s*" + re.escape(V) + r"\s*(?P<op>" + BIN_OP + r")\s*(?P<k>.+?)\s*", argk)
        if not op:
            continue
        if not ctx.writable(V):
            skips["target-not-writable"] += 1
            continue
        if ctx.uses_between(V, ctx.off[i] + len(ctx.lines[i]), ctx.fn["end"] if ctx.fn else len(ctx.m)):
            skips["target-live-after-the-call"] += 1
            continue
        if any(CALL.search(o) or re.search(r"(?<![=!<>])=(?!=)|\+\+|--", o) for o in others):
            skips["another-argument-has-a-side-effect"] += 1
            continue
        if not ctx.in_scope(V, ctx.off[i]):
            skips["target-out-of-scope-at-the-call"] += 1
            continue
        if not ctx.standalone(i):
            skips["call-line-is-a-brace-less-controlled-statement"] += 1
            continue
        if not (WORD_TYPE.match(norm_type(ctx.dtype(V) or "")) and ctx.narrow_expr(argk)):
            skips["argument-hoist-may-change-the-value-width"] += 1
            continue
        new = ctx.lines[i][:astart + a] + raw.replace(argk, V, 1) + ctx.lines[i][astart + b:]
        yield ("t65:arg-hoist:%d:%d" % (slot, i + 1),
               ctx.replace_lines({i: "%s%s = %s %s %s;\n%s" %
                                  (ctx.indent(i), V, V, op["op"], op["k"], new)}))


def param_merge_moves(ctx, skips):
    """(iii)/(iv) `V = param_k;` merged, in both naming directions."""
    V = ctx.var
    slot = ctx.reg - ARG_FIRST
    if ctx.params is None:
        skips["parameter-slots-unresolved"] += 1
        return
    if slot >= len(ctx.params):
        skips["function-has-fewer-parameters-than-the-slot"] += 1
        return
    pty, P = ctx.params[slot]
    d = ctx.decl.get(V)
    if not d:
        skips["target-not-declared-local"] += 1
        return
    if norm_type(pty) != norm_type(d["type"]):
        skips["parameter-type-differs"] += 1
        return
    copies = [(i, r) for i, r in ctx.assigns(V) if r.strip() == P]
    if not copies:
        skips["no-copy-of-the-parameter-into-the-target"] += 1
        return
    i, _ = copies[0]
    vuses = [mm for mm in ctx.occ(V) if not (d["start"] <= mm.start() < d["end"])]
    if any(mm.start() < ctx.off[i] for mm in vuses):
        skips["target-used-before-the-copy"] += 1
        return
    puses = [mm for mm in ctx.occ(P) if mm.start() > ctx.off[i] + len(ctx.lines[i])]
    if puses:
        skips["parameter-used-after-the-merge-point"] += 1
        return
    if not ctx.writable(V) or re.search(r"&\s*" + re.escape(P) + r"\b", ctx.m):
        skips["merge-operand-address-taken"] += 1
        return
    if not ctx.standalone(i):
        skips["copy-is-a-brace-less-controlled-statement"] += 1
        return
    # A rename adds no line, so line indices are stable across both directions.
    decl_line = ctx.line_of(d["start"])
    head = ctx.fn["head"]
    end = ctx.fn["end"]

    def rebuilt(rename_from, rename_to):
        """Rename at MASKED, member-free, whole-token positions only.

        The raw-line `re.sub` this replaces rewrote comments and, worse, `s->v` - a struct member
        that merely shares the name, at a different offset (round 28 review, defect 2)."""
        out = list(ctx.lines)
        spots = collections.defaultdict(list)
        for mm in ctx.occ(rename_from, head, end + 1):
            spots[ctx.line_of(mm.start())].append(mm.start() - ctx.off[ctx.line_of(mm.start())])
        for k, cols in spots.items():
            for c in sorted(cols, reverse=True):
                out[k] = out[k][:c] + rename_to + out[k][c + len(rename_from):]
        out[i] = ""
        out[decl_line] = ""
        return "".join(out)

    # direction A: the target's uses become the parameter's; V's declaration and the copy go.
    yield "t65:merge-to-param:%s:%d" % (P, i + 1), rebuilt(V, P)
    # direction B: the parameter takes the target's name (one fewer declaration, the same order).
    # Refused when the target's name already appears outside the body (a prototype names it).
    if not re.search(r"\b" + re.escape(V) + r"\b", ctx.m[:ctx.fn["body"]]):
        yield "t65:merge-to-local:%s:%d" % (V, i + 1), rebuilt(P, V)


# --------------------------------------------------------------------------- order-swap moves

def inline_moves(ctx, skips, var=None):
    """One fewer reference: a single-definition, single-use local folded into its use."""
    V = var or ctx.var
    d = ctx.decl.get(V)
    if not d:
        skips["inline-target-not-a-local"] += 1
        return
    if "ASM_" in ctx.ml[ctx.line_of(d["start"])]:
        return
    defs = ctx.assigns(V)
    outside = [mm for mm in ctx.occ(V) if not (d["start"] <= mm.start() < d["end"])]
    if len(defs) != 1 or len(outside) != 2:
        skips["inline-not-single-definition-single-use"] += 1
        return
    i, rhs = defs[0]
    use = outside[1]
    j = ctx.line_of(use.start())
    if j <= i or not ctx.simple(j) or not ctx.straight(i, j):
        skips["inline-use-not-straight-line"] += 1
        return
    e = rhs.strip()
    if re.search(r"(?<![=!<>])=(?!=)|\+\+|--", e):
        skips["inline-definition-has-a-side-effect"] += 1
        return
    if ctx.writes_between(set(re.findall(ID, e)), ctx.off[i] + len(ctx.lines[i]), ctx.off[j]):
        skips["inline-operand-changed-between"] += 1
        return
    if CALL.search(e) and j != i + 1:
        skips["inline-would-move-a-call"] += 1
        return
    if ctx.m[max(0, use.start() - 1):use.start()] == "&":
        return
    if ctx.written_at(use.start(), V):
        skips["inline-use-is-a-write"] += 1
        return
    if not ctx.standalone(i):
        skips["definition-is-a-brace-less-controlled-statement"] += 1
        return
    repl = cast_of(ctx, d["type"], e)
    line = ctx.lines[j]
    k = use.start() - ctx.off[j]
    new = line[:k] + repl + line[k + len(V):]
    edits = {i: "", j: new}
    drop_decl(ctx, V, edits)
    yield "t65:inline:%s:%d" % (V, i + 1), ctx.replace_lines(edits)


def hoist_positions(ctx, e, i):
    """Whole-subexpression, type-checked repeats of `e` after line i: [(line, column, why)].

    A repeat is usable only where it is (a) the ENTIRE right-hand side of an assignment whose
    destination's type is known and holds the same 32 bits as V's (`same_word`), or (b) the ENTIRE
    expression of a `return` in a function whose return type does.  Then `L = e;` and `L = V;`
    compute `(L's type)e` either way, and the move is exactly one more reference to V.

    Everything the old substring scan accepted is refused here: an occurrence on the LEFT of an
    assignment (which deleted the store), one inside a larger identifier (`xa + b` -> `xv`), one
    that is only part of an expression (`a + b * 2` -> `v * 2`, a precedence change), one under `&`
    (the address of a field became the address of a local) and one in a declaration."""
    vty = norm_type(ctx.dtype(ctx.var) or "")
    rty = norm_type(ctx.fn["ret"]) if ctx.fn else None
    out = []
    for j in range(i + 1, len(ctx.ml)):
        if not ctx.arm_ok(j) or "ASM_" in ctx.ml[j]:
            continue
        if ctx.fn is None or not (ctx.fn["body"] <= ctx.off[j] < ctx.fn["end"]):
            continue
        raw, ml = ctx.lines[j], ctx.ml[j]
        asn = S.ASSIGN.match(ml) if ctx.simple(j) else None
        if asn:
            a, b = asn.span("rhs")
            dest = asn["lhs"].strip()
            if raw[a:b].strip() != e:
                continue
            dty = ctx.lvalue_type(dest)
            if dty is None:
                skips_note = "hoist-destination-type-unknown"
            elif not same_word(dty, vty):
                skips_note = "hoist-destination-type-differs"
            elif norm_type(dty) != vty and not ctx.narrow_expr(e):
                # Two DIFFERENT 32-bit types: `(u32)e` and `(u32)(s32)e` are the same value only
                # while `e` is integral, so the source needs the narrow test too.
                skips_note = "hoist-source-may-be-floating-or-64-bit"
            else:
                skips_note = None
            out.append((j, a + (len(raw[a:b]) - len(raw[a:b].lstrip())), skips_note))
            continue
        r = re.match(r"^[ \t]*return\s+(?P<e>.+);[ \t]*$", ml)
        if r and raw[r.start("e"):r.end("e")].strip() == e:
            if not same_word(rty, vty):
                why = "hoist-return-type-differs"
            elif rty != vty and not ctx.narrow_expr(e):
                why = "hoist-source-may-be-floating-or-64-bit"
            else:
                why = None
            out.append((j, r.start("e"), why))
    return out


def hoist_moves(ctx, skips, var=None):
    """One more reference: a later verbatim repeat of V's defining expression spelled as V."""
    V = var or ctx.var
    d = ctx.decl.get(V)
    if not d:
        return
    if var and var != ctx.var:
        return                                     # the type check below is written for the target
    defs = ctx.assigns(V)
    if len(defs) != 1:
        skips["hoist-not-single-definition"] += 1
        return
    i, rhs = defs[0]
    e = rhs.strip()
    if len(e) < 3 or re.search(r"(?<![=!<>])=(?!=)|\+\+|--", e) or CALL.search(e):
        skips["hoist-expression-not-repeatable"] += 1
        return
    ids = set(re.findall(ID, e))
    n = 0
    for j, k, why in hoist_positions(ctx, e, i):
        if why:
            skips[why] += 1
            continue
        if ctx.writes_between(ids | {V}, ctx.off[i] + len(ctx.lines[i]), ctx.off[j]):
            skips["hoist-operand-changed-between"] += 1
            continue
        if not ctx.in_scope(V, ctx.off[j]):
            skips["hoist-target-out-of-scope-there"] += 1
            continue
        line = ctx.lines[j]
        yield ("t65:hoist:%s:%d" % (V, j + 1),
               ctx.replace_lines({j: line[:k] + V + line[k + len(e):]}))
        n += 1
        if n >= 3:
            return


def sink_moves(ctx, skips, var=None):
    """A shorter lifetime: V's definition moved down to just before its first use."""
    V = var or ctx.var
    d = ctx.decl.get(V)
    if not d:
        return
    defs = ctx.assigns(V)
    if len(defs) != 1:
        skips["sink-not-single-definition"] += 1
        return
    i, _ = defs[0]
    if not ctx.simple(i):
        return
    later = [mm for mm in ctx.occ(V) if mm.start() > ctx.off[i] + len(ctx.lines[i])]
    if not later:
        skips["sink-no-later-use"] += 1
        return
    j = ctx.line_of(later[0].start())
    if j <= i + 1 or not ctx.straight(i, j):
        skips["sink-nothing-to-cross"] += 1
        return
    crossed = [k for k in range(i + 1, j) if ctx.ml[k].strip()]
    if not all(S.independent(ctx.ml[i], ctx.ml[k]) for k in crossed):
        skips["sink-crosses-a-dependence"] += 1
        return
    if not (ctx.standalone(i) and ctx.standalone(j)):
        skips["sink-endpoint-is-a-brace-less-controlled-statement"] += 1
        return
    moved = ctx.indent(j) + ctx.lines[i].strip() + "\n"
    yield ("t65:sink:%s:%d->%d" % (V, i + 1, j + 1),
           ctx.replace_lines({i: "", j: moved + ctx.lines[j]}))


def imported_moves(ctx, skips):
    """The menu that already existed, labelled by origin so the DELTA can be measured."""
    var, line = ctx.var, ctx.site_line - 1
    try:
        n = 0
        for tag, cand in S.candidates(ctx.text, line, var):
            head = tag.split(":")[0]
            if head not in ("single-set", "fuse", "move"):
                continue
            yield "t51:" + tag, cand
            n += 1
            if n >= IMPORT_CAP * 3:
                break
    except Exception as e:
        skips["t51-menu-error:%r" % (e,)] += 1
    for gen, name in ((N.splitcursor_candidates, "splitcursor"), (N.host_candidates, "host"),
                      (N.hostwide_candidates, "hostwide"), (N.unhost_candidates, "unhost"),
                      (N.declorder_candidates, "declorder")):
        try:
            for k, (tag, cand) in enumerate(gen(ctx.text)):
                if k >= IMPORT_CAP:
                    break
                yield "nat:" + tag, cand
        except Exception as e:
            skips["nat-%s-error:%r" % (name, e)] += 1
    try:
        for k, (tag, cand) in enumerate(A.reuse_candidates(ctx.text, var)):
            if k >= IMPORT_CAP:
                break
            yield "t60:" + tag, cand
    except Exception as e:
        skips["t60-reuse-error:%r" % (e,)] += 1


SUGG_MOVES = {2: (return_moves, call_result_moves, call_via_moves),
              4: (argument_moves, param_merge_moves, arg_via_moves)}
ORDER_MOVES = (inline_moves, sink_moves, unshare_moves, hoist_moves)


def site_candidates(text, rec, route, skips):
    """Every candidate for one probe site on the already-erased text, targeted moves first."""
    var, reg = rec.get("var"), hard_number(str(rec.get("register")))
    line = rec.get("line") or 1
    try:
        ctx = Ctx(text, var, reg, line)
    except Exception as e:
        skips["context-error:%r" % (e,)] += 1
        return
    if ctx.fn is None:
        skips["no-enclosing-function"] += 1
        return
    if route == "sugg":
        for gen in SUGG_MOVES[2 if reg == 2 else 4]:
            try:
                yield from gen(ctx, skips)
            except Exception as e:
                skips["move-error:%s:%r" % (gen.__name__, e)] += 1
        return
    for gen in ORDER_MOVES:
        try:
            yield from gen(ctx, skips)
        except Exception as e:
            skips["move-error:%s:%r" % (gen.__name__, e)] += 1
    yield from imported_moves(ctx, skips)


# --------------------------------------------------------------------------- the generator

class T:
    name = "t65_regroute"
    level = 1
    needs_verify = True

    @staticmethod
    def eligible(text, row, census):
        why = asm_blocker(text)
        if why:
            return why
        if not sites_of(text):
            return "no live pins"
        if not row.get("cfg"):
            return "missing compiler recipe"
        rep, why = probe_report(text, row)
        if why:
            return why
        plans = plan_sites(rep, collections.Counter())
        if not plans:
            return "no sugg or order-swap site with a C lever"
        return None

    @classmethod
    def apply_verified(cls, text, row, census, vf):
        screens = max(1, int(os.getenv("T65_SCREENS", "400")))
        verifies = max(1, int(os.getenv("T65_VERIFY", "6")))
        pins_in = len(sites_of(text))
        usig = unscored_text(text)
        skips = collections.Counter()
        log = dict(pins_in=pins_in, pins_out=pins_in, screen_budget=screens, vf_budget=verifies,
                   screened=0, tried=0, candidates_n=0, compile_failures=0, steps=[],
                   sites=[], nearest=[], moves={}, skips={}, exact=[])
        rep, why = probe_report(text, row)
        if why:
            log["error"] = why
            return None, log
        plans = plan_sites(rep, skips)
        log["plan_sites"] = len(plans)
        cur, dead, near = text, set(), []
        moves = collections.Counter()
        try:
            while True:                     # the screen budget bounds this; a win restarts
                won = False
                ref = SCREEN(row, cur)
                if ref is None:
                    log["error"] = "reference-build-error"
                    break
                for rec, route, note in plans:
                    site = live_site(cur, rec)
                    if site is None:
                        skips["site-not-live"] += 1
                        continue
                    base = erase_many(cur, [site], clean_notes=True)
                    if unscored_text(base) != usig:
                        skips["erasure-touches-an-unscored-arm"] += 1
                        continue
                    d0 = None
                    if log["screened"] < screens:
                        log["screened"] += 1
                        erased = SCREEN(row, base)
                        if erased is None:
                            log["compile_failures"] += 1
                        d0 = sdiff(ref, erased)
                    srec = dict(site=rec.get("site"), knob=rec.get("minimal_knob"), route=route,
                                note=note, register=rec.get("register"), var=rec.get("var"),
                                owner=rec.get("owner"), line=site[5], d0=d0, candidates=0,
                                by_move={}, nearest=None, nearest_label=None)
                    seen = set()
                    per_move = collections.Counter()
                    for label, cand in site_candidates(base, rec, route, skips):
                        h = sha_text(cand)
                        if h in seen or cand == base:
                            continue
                        seen.add(h)
                        head = ":".join(label.split(":")[:2])
                        per_move[head] += 1
                        moves[head] += 1
                        srec["candidates"] += 1
                        log["candidates_n"] += 1
                        if not A.allowed(cur, cand, usig, len(sites_of(cur))):
                            skips["refused-by-the-scaffolding-guard"] += 1
                            continue
                        if log["screened"] >= screens:
                            skips["screen-budget"] += 1
                            continue
                        log["screened"] += 1
                        got = SCREEN(row, cand)
                        if got is None:
                            log["compile_failures"] += 1
                            skips["candidate-does-not-compile"] += 1
                            continue
                        d = sdiff(ref, got)
                        near.append((d, label, d0))
                        if srec["nearest"] is None or d < srec["nearest"]:
                            srec["nearest"], srec["nearest_label"] = d, label
                        if d != 0:
                            continue
                        if not improves(cur, cand):
                            skips["no-pin-debt-improvement"] += 1
                            continue
                        listing = (sha_text("\n".join(got)),
                                   tuple(sorted(s[1] for s in sites_of(cand))))
                        if listing in dead:
                            skips["same-listing-as-a-failed-verify"] += 1
                            continue
                        if log["tried"] >= verifies:
                            skips["verify-budget"] += 1
                            continue
                        log["tried"] += 1
                        if not vf(cand).get("exact"):
                            dead.add(listing)
                        else:
                            log["steps"].append(label)
                            log["exact"].append(dict(site=rec.get("site"), knob=rec.get("minimal_knob"),
                                                     register=rec.get("register"), var=rec.get("var"),
                                                     label=label, route=route, note=note,
                                                     pins_before=len(sites_of(cur)),
                                                     pins_after=len(sites_of(cand))))
                            cur = cand
                            won = True
                            break
                    srec["by_move"] = dict(per_move)
                    log["sites"].append(srec)
                    if won:
                        break
                if not won:
                    break
        except Exception as e:                       # a parse fault must not fail a sweep row
            log["error"] = repr(e)
        log["moves"] = dict(sorted(moves.items()))
        log["skips"] = dict(sorted(skips.items()))
        log["nearest"] = [{"d": d, "label": l, "d0": z}
                          for d, l, z in sorted(near, key=lambda x: (x[0] is None, x[0]))[:12]]
        log["pins_out"] = len(sites_of(cur))
        if not log["steps"]:
            return None, log
        return cur, log
