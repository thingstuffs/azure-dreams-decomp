"""T8b: the pass-through repair for callers that do not declare the parameters they pass on.

`t8_passthru` repairs `f()` -> `f(arg0..argK)` only when the caller already declares `arg0..argK`
by those names (the experiment's local case).  Its refusals on the single-site rows are dominated
by two named reasons this plugin lifts, with the same verification (the per-row scorer, then the
window gate through the sweep's normal path):

* `caller has no arg0..argK`: the caller declares fewer positional parameters than the callee
  reads, or names them differently (often none at all: `void f(void) { g(); }` where retail's `g`
  reads `a0`).  The incoming registers are the caller's own arguments whether or not m2c declared
  them, so the caller's parameter list is extended to K+1 positions: existing positional
  parameters keep their names and types, the missing ones are added as `argN` typed from the
  callee's own definition when the callee is a row in the tree (else `s32`), and the call passes
  all K+1 positions by name.
* `ambiguous call ordinal`: t8 counted every empty-paren call in the file; the audit names the
  target, so the call is resolved by name and refused only when the target itself is called with
  no arguments more than once.

Everything else is as in t8: one audited site per file, no reassignment or address-taking of a
passed parameter before the call, the callee's prototype edited in place or moved in front of the
definition when it names a type typedef'd further down.
"""
import json, re
from pathlib import Path
from xform import t8_passthru as t8

ROOT = Path(__file__).resolve().parents[2]
_CALLEE_TYPES = {}
_ROWFILE = None

def row_file(container, name):
    """The src file of the row defining `name` (true name or row name) in `container`, else in slus."""
    global _ROWFILE
    if _ROWFILE is None:
        _ROWFILE = {}
        for line in (ROOT / "ledger/rows.jsonl").read_text().splitlines():
            if not line.strip():
                continue
            r = json.loads(line)
            p = ROOT / "src" / r["container"] / Path(r["c_path"]).name
            for n in {r["func"], r.get("true_name")} | set(r.get("defs") or []):
                if n:
                    _ROWFILE.setdefault((r["container"], n), p)
    return _ROWFILE.get((container, name)) or _ROWFILE.get(("slus", name))

def callee_types(container, callee):
    """Positional parameter types of the callee's own definition, [] when unknown."""
    key = (container, callee)
    if key not in _CALLEE_TYPES:
        types = []
        p = row_file(container, callee)
        if p and p.exists():
            txt = p.read_text(errors="replace")
            for d in t8.find_defs(txt):
                if d["name"] == callee:
                    ps = d["params"].strip()
                    if ps and ps != "void":
                        for prm in t8.split_params(ps):
                            t, nm = t8.param_type(prm)
                            types.append(t or "s32")
                    break
        _CALLEE_TYPES[key] = types
    return _CALLEE_TYPES[key]

BUILTIN = {"s8", "u8", "s16", "u16", "s32", "u32", "s64", "u64", "f32", "void", "char", "short", "int", "long", "unsigned", "signed",
           "float", "double", "M2C_UNK", "const", "volatile", "struct", "union", "enum"}

def portable_type(text, t):
    """A callee's parameter type is reused only when the caller's file can see it (a builtin, a
    typedef/struct declared in the text, or a record header it includes); otherwise the position
    is typed `void *` (pointer) or `s32`."""
    words = set(re.findall(r"[A-Za-z_][A-Za-z0-9_]*", t))
    for w in words - BUILTIN:
        if not re.search(r"\b(?:typedef\b[^;]*\b%s\b|struct\s+%s\b|union\s+%s\b|enum\s+%s\b)" % ((re.escape(w),) * 4), text) \
                and not re.search(r'#include\s+"records/%s\.h"' % re.escape(w), text):
            return "void *" if "*" in t else "s32"
    return t

def positional_params(text, encl):
    """[(type, name)] of the enclosing definition's parameters, [] for `()` / `(void)`."""
    i = text.index("(", encl["dstart"]); j = t8.matching_paren(text, i)
    inner = text[i + 1:j].strip()
    if not inner or inner == "void":
        return [], (i + 1, j)
    out = []
    for prm in t8.split_params(inner):
        t, nm = t8.param_type(prm)
        if not nm or not t:
            raise t8.Refusal("unparsed parameter %r" % prm)
        out.append((t, nm))
    return out, (i + 1, j)

def assigned_before(text, encl, pos, names):
    seg = text[encl["bstart"]:pos]
    for nm in names:
        n = re.escape(nm)
        if re.search(r"\b%s\s*(=[^=]|\+\+|--|[-+*/%%&|^]=|<<=|>>=)" % n, seg) or re.search(r"(\+\+|--)\s*%s\b" % n, seg):
            return nm
        for m in re.finditer(r"&\s*%s\b" % n, seg):
            if seg[:m.start()].rstrip().endswith("&"):
                continue
            return "&" + nm
    return None

def plan(text, row):
    recs = t8.sites().get(row["id"]) or []
    if not recs:
        raise t8.Refusal("no PASSTHRU_NO_ARGS site")
    if len(recs) > 1:
        raise t8.Refusal("several PASSTHRU_NO_ARGS sites in the file")
    rec = recs[0]
    need = sorted({t8.REG[x.strip()] for x in rec["need"].split(",") if x.strip() in t8.REG})
    if not need:
        raise t8.Refusal("no a0-a3 register in `need`")
    K = max(need)
    defs = t8.find_defs(text)
    calls = [c for c in t8.empty_calls(text, defs) if c["name"] == rec["target"]]
    if len(calls) != 1:
        raise t8.Refusal("target called with no arguments %d times" % len(calls))
    call = calls[0]; encl = call["encl"]
    params, span = positional_params(text, encl)
    if len(params) > 4:
        raise t8.Refusal("more than four positional parameters")
    ctypes = callee_types(row["container"], rec["target"])
    new_params = list(params)
    for k in range(len(params), K + 1):
        new_params.append((portable_type(text, ctypes[k] if k < len(ctypes) else "s32"), "arg%d" % k))
    bad = assigned_before(text, encl, call["pos"], [nm for _, nm in new_params[:K + 1]])
    if bad:
        raise t8.Refusal("parameter reassigned (%s)" % bad)
    return rec, need, K, call, encl, params, new_params, span

def rewrite(text, rec, K, call, encl, params, new_params, span, relocate=False):
    callee = rec["target"]
    argtypes = [t for t, _ in new_params[:K + 1]]
    proto = ", ".join(argtypes)
    newcall = "%s(%s)" % (callee, ", ".join(nm for _, nm in new_params[:K + 1]))
    cs, ce = call["m"].start(), call["m"].end()
    decl_params, whole, head = t8.decl_span(text, t8.find_defs(text), callee)
    rt = "void" if t8.is_statement_call(text, call["m"]) else "s32"
    edits = [(cs, ce, newcall)]
    if len(new_params) != len(params):
        edits.append((span[0], span[1], ", ".join(("%s%s" if t.endswith("*") else "%s %s") % (t, nm) for t, nm in new_params)))
    insert = None
    if decl_params and not relocate:
        edits.append((decl_params[0], decl_params[1], proto))
    elif decl_params:
        if whole is None:
            raise t8.Refusal("declaration shares its line with other code")
        edits.append((whole[0], whole[1], ""))
        insert = "%s %s(%s);\n" % (head, callee, proto)
    else:
        insert = "extern %s %s(%s);\n" % (rt, callee, proto)
    for s, e, rep in sorted(edits, reverse=True):
        text = text[:s] + rep + text[e:]
    if insert:
        shift = sum(len(rep) - (e - s) for s, e, rep in edits if s < encl["dstart"])
        pos = text.rfind("\n", 0, encl["dstart"] + shift) + 1
        text = text[:pos] + "\n" + insert + text[pos:]
    return text, argtypes, decl_params is not None

class T:
    name = "t8b_passthru_params"; level = 1
    needs_verify = True

    @staticmethod
    def eligible(text, row, census):
        try:
            plan(text, row)
        except t8.Refusal as e:
            return str(e)
        except Exception as e:
            return "parse error: %r" % (e,)
        return None

    @staticmethod
    def apply_verified(text, row, census, verify_fn):
        try:
            rec, need, K, call, encl, params, new_params, span = plan(text, row)
            cand, argtypes, had_decl = rewrite(text, rec, K, call, encl, params, new_params, span)
        except t8.Refusal as e:
            return None, {"refused": [str(e)]}
        info = {"target": rec["target"], "need": rec["need"], "K": K, "nfill": K + 1 - len(need), "params_in": len(params),
                "params_added": len(new_params) - len(params), "argtypes": argtypes, "decl_found": had_decl}
        v = verify_fn(cand)
        if v.get("exact"):
            return cand, info
        if v.get("status") != "ok" and had_decl:
            try:
                cand2, _, _ = rewrite(text, rec, K, call, encl, params, new_params, span, relocate=True)
            except t8.Refusal as e:
                return None, dict(info, refused=["build-fail; " + str(e)])
            v2 = verify_fn(cand2)
            if v2.get("exact"):
                return cand2, dict(info, decl_moved=True)
            return None, dict(info, decl_moved=True, refused=["not exact after moving the declaration: %s/%s" % (v2.get("class"), v2.get("total"))])
        return None, dict(info, refused=["not exact: %s/%s" % (v.get("class"), v.get("total"))])

    @staticmethod
    def apply(text, row, census):
        try:
            rec, need, K, call, encl, params, new_params, span = plan(text, row)
        except t8.Refusal:
            return None
        return rewrite(text, rec, K, call, encl, params, new_params, span)[0]
