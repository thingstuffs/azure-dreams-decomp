"""T8: a call the decompiler emitted with no arguments regains the arguments the callee reads.

`PASSTHRU_NO_ARGS` (ledger/cache/audit.json) marks a `jal` whose callee reads registers `a0..a3`
that the caller never wrote: m2c printed `func_X()` while the hardware passed the caller's own
incoming arguments straight through.  This plugin repairs the *local* case measured in
`work/exp_passthru/REPORT.md` (13/20 byte-exact through the window gate, the per-row scorer
agreeing with the gate on all 20):

    the caller declares `arg0..argK` (K = highest needed register index) and reassigns none of them
    before the call, and the file holds exactly one empty-paren call, which is the target
      ->  `func_X()`            becomes  `func_X(arg0, ..., argK)`
          `T func_X(void);`     becomes  `T func_X(<caller's types for those positions>);`
          (no declaration       ->  one is inserted just before the enclosing definition)

Everything else is refused with a named reason: several audited sites in one file, several
empty-paren calls (the ordinal is ambiguous), a caller without `arg0..argK`, a parameter assigned
before the call.  One rule the experiment's 20 rows never exercised: where the file typedefs a
parameter's struct type *below* the declaration, the new prototype does not compile in place, so a
second candidate moves that same declaration in front of the enclosing definition (17 of the 20
rows that hit this are byte-exact once it moves).  Both candidates are verified per row; a
non-exact result writes nothing.
The experiment's predictor is `nfill` (= K+1 - |need|, the positions passed only to line the ABI up):
`nfill<=1` passed 11/12, `nfill>=2` passed 2/8 - so the sweep's own verify is the filter, not a
shape heuristic, and `nfill` is journalled for every attempt.
"""
import json, re
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
REG = {"a0": 0, "a1": 1, "a2": 2, "a3": 3}
KW = {"if", "while", "for", "switch", "return", "sizeof", "do", "else", "case", "defined",
      "ASM_SET", "M2C_UNK", "OR_ZERO", "__attribute__"}

_SITES = None

def sites():
    """row id -> [PASSTHRU_NO_ARGS record].  slus rows key their records by function name."""
    global _SITES
    if _SITES is None:
        ids = set(); fmap = {}
        for line in (ROOT / "ledger/rows.jsonl").read_text().splitlines():
            if not line.strip():
                continue
            r = json.loads(line)
            ids.add(r["id"])
            for d in r.get("defs") or []:
                fmap[(r["container"], d)] = r["id"]
        idx = {}
        for rec in json.load(open(ROOT / "ledger/cache/audit.json"))["records"]:
            if rec.get("cls") != "PASSTHRU_NO_ARGS":
                continue
            rid = f"{rec['container']}/{rec['row_key']}"
            if rid not in ids:
                rid = fmap.get((rec["container"], rec["row_key"]))
            if rid is None:      # a scratch file, not a registered row
                continue
            idx.setdefault(rid, []).append(rec)
        _SITES = idx
    return _SITES

# --- parsing (work/exp_passthru/scan.py, rewrite.py) -------------------------------------------

def find_defs(txt):
    """[{name, params, bstart, bend, dstart, dend}] for every function definition in the file."""
    defs = []
    for m in re.finditer(r"(^|\n)([A-Za-z_][\w\s\*]*?)\b([A-Za-z_]\w*)\s*\(([^;{)]*)\)\s*(?:__attribute__\s*\(\([^)]*\)\)\s*)?\{", txt):
        if m.group(3) in KW:
            continue
        i = txt.index("{", m.end() - 1)
        depth = 0
        for j in range(i, len(txt)):
            if txt[j] == "{":
                depth += 1
            elif txt[j] == "}":
                depth -= 1
                if depth == 0:
                    break
        defs.append({"name": m.group(3), "params": m.group(4), "bstart": i, "bend": j,
                     "dstart": m.start(2), "dend": m.end(0)})
    return defs

def empty_calls(txt, defs):
    """Empty-paren call sites inside function bodies (top-level declarations are not calls)."""
    out = []
    for m in re.finditer(r"\b([A-Za-z_]\w*)\s*\(\s*\)", txt):
        if m.group(1) in KW:
            continue
        for d in defs:
            if d["bstart"] < m.start() < d["bend"]:
                out.append({"name": m.group(1), "pos": m.start(), "encl": d, "m": m})
                break
    return out

def matching_paren(txt, i):
    d = 0
    for j in range(i, len(txt)):
        if txt[j] == "(":
            d += 1
        elif txt[j] == ")":
            d -= 1
            if d == 0:
                return j
    raise ValueError("unbalanced parentheses")

def split_params(s):
    out = []; d = 0; cur = ""
    for ch in s:
        if ch in "(<[":
            d += 1
        elif ch in ")>]":
            d -= 1
        if ch == "," and d == 0:
            out.append(cur); cur = ""
        else:
            cur += ch
    if cur.strip():
        out.append(cur)
    return [x.strip() for x in out]

def param_type(p):
    m = re.match(r"^(.*?)\b(arg\d+|\w+)\s*(\[\s*\])?$", p.strip())
    if not m:
        return None, None
    t = m.group(1).strip()
    if m.group(3):
        t = t + " *"
    return t, m.group(2)

def caller_types(txt, encl):
    """{index: type} for the enclosing definition's `argN` parameters."""
    i = txt.index("(", encl["dstart"]); j = matching_paren(txt, i)
    types = {}
    for p in split_params(txt[i + 1:j]):
        t, nm = param_type(p)
        if nm and re.fullmatch(r"arg\d+", nm):
            types[int(nm[3:])] = t
    return types

def assigned_before(txt, encl, pos, upto):
    """The `argN` (N <= upto) written, incremented or address-taken between the body start and the call."""
    seg = txt[encl["bstart"]:pos]
    for k in range(upto + 1):
        if re.search(r"\barg%d\s*(=[^=]|\+\+|--|[-+*/%%&|^]=|<<=|>>=)" % k, seg):
            return "arg%d" % k
        if re.search(r"(\+\+|--)\s*arg%d\b" % k, seg):
            return "arg%d" % k
        for m in re.finditer(r"&\s*arg%d\b" % k, seg):
            if seg[:m.start()].rstrip().endswith("&"):      # `x && arg0`, a logical and
                continue
            # `&arg0` and, conservatively, `&arg0->m` too: the experiment's funnel refused both
            return "&arg%d" % k
    return None

def is_statement_call(txt, m):
    """True when the call stands alone as `func();` - the site then implies a `void` return."""
    b = txt[:m.start()].rstrip()
    if b and b[-1] not in ";{}:":
        return False
    a = txt[m.end():].lstrip()
    return a.startswith(";")

# --- the transform ------------------------------------------------------------------------------

class Refusal(Exception):
    pass

def plan(text, row):
    """(record, need, K, call, encl, types) or raise Refusal with a named reason."""
    recs = sites().get(row["id"]) or []
    if not recs:
        raise Refusal("no PASSTHRU_NO_ARGS site")
    if len(recs) > 1:
        raise Refusal("several PASSTHRU_NO_ARGS sites in the file")
    rec = recs[0]
    need = sorted({REG[x.strip()] for x in rec["need"].split(",") if x.strip() in REG})
    if not need:
        raise Refusal("no a0-a3 register in `need`")
    K = max(need)
    defs = find_defs(text)
    calls = empty_calls(text, defs)
    if len(calls) != 1 or calls[0]["name"] != rec["target"]:
        raise Refusal("ambiguous call ordinal")
    call = calls[0]; encl = call["encl"]
    types = caller_types(text, encl)
    if not all(k in types for k in range(K + 1)):
        raise Refusal("caller has no arg0..arg%d" % K)
    bad = assigned_before(text, encl, call["pos"], K)
    if bad:
        raise Refusal("parameter reassigned (%s)" % bad)
    return rec, need, K, call, encl, types

def decl_span(text, defs, callee):
    """(span of the whole declaration statement, span of its parameter list, the head before the
    name) for the file's top-level `T callee(...);`, or (None, None, None)."""
    for m in re.finditer(r"\b" + re.escape(callee) + r"\s*\(", text):
        s = m.end() - 1
        if any(d["bstart"] < s < d["bend"] for d in defs):
            continue
        e = matching_paren(text, s)
        k = e + 1
        while k < len(text) and text[k] in " \t":
            k += 1
        if text[k:k + 1] != ";" and text[k:k + 2] != "__":
            continue                       # a definition, or a call in file scope: not a declaration
        ls = text.rfind("\n", 0, m.start()) + 1
        le = k + 1
        while le < len(text) and text[le] in " \t":
            le += 1
        if text[le:le + 1] == "\n":
            le += 1
        head = text[ls:m.start()].strip()
        whole = (ls, le) if (head and ";" not in head and text[k:k + 1] == ";") else None
        return (s + 1, e), whole, head
    return None, None, None

def rewrite(text, rec, K, call, encl, types, relocate=False):
    """(new text, argtypes, whether a declaration was found).

    `relocate` moves the declaration to just before the enclosing definition instead of editing it
    where it stands - the repair for a prototype that names a type the file typedefs further down.
    """
    callee = rec["target"]
    argtypes = [types.get(k, "s32") for k in range(K + 1)]
    proto = ", ".join(argtypes)
    newcall = "%s(%s)" % (callee, ", ".join("arg%d" % k for k in range(K + 1)))
    cs, ce = call["m"].start(), call["m"].end()
    params, whole, head = decl_span(text, find_defs(text), callee)
    rt = "void" if is_statement_call(text, call["m"]) else "s32"
    edits = [(cs, ce, newcall)]
    insert = None
    if params and not relocate:
        edits.append((params[0], params[1], proto))
    elif params:
        if whole is None:
            raise Refusal("declaration shares its line with other code")
        edits.append((whole[0], whole[1], ""))
        insert = "%s %s(%s);\n" % (head, callee, proto)
    else:
        insert = "extern %s %s(%s);\n" % (rt, callee, proto)
    for s, e, rep in sorted(edits, reverse=True):
        text = text[:s] + rep + text[e:]
    if insert:
        # in front of the enclosing definition, so any type named in the prototype is in scope
        shift = sum(len(rep) - (e - s) for s, e, rep in edits if s < encl["dstart"])
        pos = text.rfind("\n", 0, encl["dstart"] + shift) + 1
        text = text[:pos] + "\n" + insert + text[pos:]
    return text, argtypes, params is not None

class T:
    name = "t8_passthru"; level = 1
    needs_verify = True

    @staticmethod
    def eligible(text, row, census):
        try:
            plan(text, row)
        except Refusal as e:
            return str(e)
        except Exception as e:
            return "parse error: %r" % (e,)
        return None

    @staticmethod
    def apply_verified(text, row, census, verify_fn):
        try:
            rec, need, K, call, encl, types = plan(text, row)
            cand, argtypes, had_decl = rewrite(text, rec, K, call, encl, types)
        except Refusal as e:
            return None, {"refused": [str(e)]}
        info = {"target": rec["target"], "need": rec["need"], "K": K, "nfill": K + 1 - len(need),
                "argtypes": argtypes, "decl_found": had_decl}
        v = verify_fn(cand)
        if v.get("exact"):
            return cand, info
        if v.get("status") != "ok" and had_decl:
            # the prototype names a type the file typedefs below the declaration: same prototype,
            # moved in front of the definition.  17 of the 20 rows that fail to build this way
            # are byte-exact once the declaration moves.
            try:
                cand2, _, _ = rewrite(text, rec, K, call, encl, types, relocate=True)
            except Refusal as e:
                return None, dict(info, refused=["build-fail; " + str(e)])
            v2 = verify_fn(cand2)
            if v2.get("exact"):
                return cand2, dict(info, decl_moved=True)
            return None, dict(info, decl_moved=True,
                              refused=["not exact after moving the declaration: %s/%s" % (v2.get("class"), v2.get("total"))])
        return None, dict(info, refused=["not exact: %s/%s" % (v.get("class"), v.get("total"))])

    @staticmethod
    def apply(text, row, census):
        try:
            rec, need, K, call, encl, types = plan(text, row)
        except Refusal:
            return None
        return rewrite(text, rec, K, call, encl, types)[0]
