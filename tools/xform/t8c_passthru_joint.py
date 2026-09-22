"""T8c: the t8/t8b pass-through repair applied JOINTLY to every site of a row at once.

`t8_passthru` and `t8b_passthru_params` both refuse a row that holds more than one
`PASSTHRU_NO_ARGS` site (`plan()`: *"several PASSTHRU_NO_ARGS sites in the file"*), so on the 122
multi-site rows of `docs/evidence/l0_blocked_20260922.json` **no candidate has ever been offered**
- the row stays L0-blocked because a one-site-at-a-time generator cannot express the move
(docs/L0_BLOCKED_PLAN_20260922.md sec 2 item 1; round 31's lesson: a move that only works jointly
is invisible to a per-site generator).  This plugin lifts exactly that refusal and nothing else:

    every live PASSTHRU_NO_ARGS site in the row is rewritten together
      * one argument list per distinct target: `f()` -> `f(arg0, ..., argK)`, K = the highest
        `a0..a3` index in the audit's `need` over ALL of that target's sites (so every site of one
        target gets the SAME list and the rewrite does not depend on which call is which ordinal)
      * one prototype per distinct target, declared once: its existing top-level declaration is
        edited in place, or - when the file has none - a single `extern` is inserted in front of
        the earliest enclosing definition (t8's relocation rule applies to all of them at once:
        a declaration naming a type the file typedefs below it is moved instead of edited)
      * the enclosing definition's parameter list is extended once, to the highest K of any target
        called in it (t8b's rule); a position is typed from the callee that reads it, through
        `t8b.portable_type`

Refused, with a named reason: a target called with no arguments MORE often than the audit lists
sites for it (the ordinal is genuinely ambiguous - PT-C2), a caller with more than four positional
parameters, a parameter written or address-taken before any one of the sites, a target whose sites
disagree on K while the call count is short (the per-site argument lists would differ and one
prototype cannot serve them).

Parsing runs on a same-length copy of the text with comments and string literals blanked: these
rows carry MECHANISM notes that spell `func_X()`, and a commented call would otherwise be counted
as a site and refuse the row as ordinal-ambiguous (the same gap `census.live_sites` has).  Offsets
are preserved, so the edits apply to the original text.

Eligibility and every helper are t8's and t8b's, imported - this plugin only joins them up.
"""
import re
from pathlib import Path

from xform import t8_passthru as t8
from xform import t8b_passthru_params as t8b

ROOT = Path(__file__).resolve().parents[2]

_COMMENT = re.compile(r"/\*.*?\*/|//[^\n]*|\"(?:\\.|[^\"\\])*\"", re.S)


def blank(text):
    """A same-length copy with comments and string literals replaced by spaces (newlines kept),
    so every offset found in it is an offset into the original text."""
    return _COMMENT.sub(lambda m: re.sub(r"[^\n]", " ", m.group(0)), text)


def _need_idx(rec):
    return sorted({t8.REG[x.strip()] for x in rec["need"].split(",") if x.strip() in t8.REG})


def call_arities(code, defs, name):
    """Argument counts of every call of `name` inside a function body (0 for an empty-paren one).

    One prototype has to serve every call in the file: a row where an earlier pass already gave
    the same target a call with a different arity (`func_800A6D30(obj)` next to `func_800A6D30()`
    - 12 of the PT-C2 rows) cannot compile with the joint prototype, so it is refused by name
    rather than offered as a candidate the build rejects."""
    out = []
    for m in re.finditer(r"(?<![A-Za-z0-9_])%s\s*\(" % re.escape(name), code):
        s = m.end() - 1
        if not any(d["bstart"] < s < d["bend"] for d in defs):
            continue                      # a top-level declaration, not a call
        inner = code[s + 1:t8.matching_paren(code, s)].strip()
        out.append(len(t8.split_params(inner)) if inner else 0)
    return out


def plan(text, row):
    """A joint plan for every live site in the row, or raise t8.Refusal with a named reason.

    Returns a dict: code (the blanked text), targets {name: {...}}, defs [{...}], sites [...]"""
    code = blank(text)
    recs = t8.live_recs(code, row)
    if not recs:
        raise t8.Refusal("no PASSTHRU_NO_ARGS site")

    # --- one entry per distinct target -----------------------------------------------------
    targets = {}
    for rec in recs:
        need = _need_idx(rec)
        if not need:
            raise t8.Refusal("no a0-a3 register in `need` (%s)" % rec["target"])
        t = targets.setdefault(rec["target"], {"recs": [], "needs": set(), "ks": set()})
        t["recs"].append(rec)
        t["needs"].update(need)
        t["ks"].add(max(need))

    defs = t8.find_defs(code)
    all_calls = t8.empty_calls(code, defs)
    for name, t in sorted(targets.items()):
        t["K"] = max(t["ks"])
        t["calls"] = [c for c in all_calls if c["name"] == name]
        n_calls, n_sites = len(t["calls"]), len(t["recs"])
        if n_calls == 0:
            raise t8.Refusal("%s is no longer called with no arguments" % name)
        if n_calls > n_sites:
            raise t8.Refusal("%s: %d empty-paren calls but %d audited sites (ordinal ambiguous)"
                             % (name, n_calls, n_sites))
        other = sorted({n for n in call_arities(code, defs, name) if n and n != t["K"] + 1})
        if other:
            raise t8.Refusal("%s is also called with %s argument(s) in this file: one prototype "
                             "cannot serve that and %d" % (name, "/".join(str(n) for n in other), t["K"] + 1))
        t["ordinal_unified"] = n_calls < n_sites
        if t["ordinal_unified"] and len(t["ks"]) > 1:
            # fewer calls than sites AND the sites disagree on the argument list: which call is
            # which site decides the rewrite, and nothing in the text says.
            raise t8.Refusal("%s: %d empty-paren calls, %d sites with different K (ordinal ambiguous)"
                             % (name, n_calls, n_sites))

    # --- one parameter-list extension per enclosing definition -----------------------------
    by_encl = {}
    for name, t in sorted(targets.items()):
        for c in t["calls"]:
            by_encl.setdefault(c["encl"]["dstart"], {"encl": c["encl"], "targets": set()})["targets"].add(name)
    plans = []
    for dstart in sorted(by_encl):
        encl = by_encl[dstart]["encl"]
        tn = sorted(by_encl[dstart]["targets"])
        kmax = max(targets[n]["K"] for n in tn)
        params, span = t8b.positional_params(code, encl)
        if len(params) > 4:
            raise t8.Refusal("more than four positional parameters (%s)" % encl["name"])
        new_params = list(params)
        for k in range(len(params), kmax + 1):
            ty = None
            for prefer_reader in (True, False):      # the callee that READS position k types it
                for n in tn:
                    if prefer_reader and k not in targets[n]["needs"]:
                        continue
                    ct = t8b.callee_types(row["container"], n)
                    if k < len(ct) and ct[k]:
                        ty = ct[k]
                        break
                if ty:
                    break
            new_params.append((t8b.portable_type(code, ty or "s32"), "arg%d" % k))
        if len(new_params) > 4:
            raise t8.Refusal("caller would need more than four positional parameters (%s)" % encl["name"])
        plans.append({"encl": encl, "params": params, "new_params": new_params, "span": span,
                      "targets": tn, "kmax": kmax})
        # no passed parameter may be written or address-taken before any site in this definition
        for n in tn:
            names = [nm for _, nm in new_params[:targets[n]["K"] + 1]]
            for c in targets[n]["calls"]:
                if c["encl"]["dstart"] != dstart:
                    continue
                bad = t8b.assigned_before(code, encl, c["pos"], names)
                if bad:
                    raise t8.Refusal("parameter reassigned (%s) before %s" % (bad, n))
    return {"code": code, "targets": targets, "defs": plans}


def rewrite(text, row, pl, relocate=False):
    """Apply the joint plan.  `relocate` moves EVERY found declaration in front of the earliest
    enclosing definition instead of editing it in place (t8's typedef-below-the-declaration rule,
    applied to all targets at once)."""
    code = pl["code"]
    defs = t8.find_defs(code)
    edits = []
    inserts = []
    decls_found = 0
    for name, t in sorted(pl["targets"].items()):
        argnames = None
        for d in pl["defs"]:
            if name in d["targets"]:
                argnames = [nm for _, nm in d["new_params"][:t["K"] + 1]]
                argtypes = [ty for ty, _ in d["new_params"][:t["K"] + 1]]
                break
        t["argtypes"] = argtypes
        newcall = "%s(%s)" % (name, ", ".join(argnames))
        for c in t["calls"]:
            edits.append((c["m"].start(), c["m"].end(), newcall))
        proto = ", ".join(argtypes)
        decl_params, whole, head = t8.decl_span(code, defs, name)
        rt = "void" if all(t8.is_statement_call(code, c["m"]) for c in t["calls"]) else "s32"
        if decl_params:
            decls_found += 1
            if not relocate:
                edits.append((decl_params[0], decl_params[1], proto))
            else:
                if whole is None:
                    raise t8.Refusal("declaration shares its line with other code (%s)" % name)
                edits.append((whole[0], whole[1], ""))
                inserts.append("%s %s(%s);\n" % (head, name, proto))
        else:
            inserts.append("extern %s %s(%s);\n" % (rt, name, proto))
    for d in pl["defs"]:
        if len(d["new_params"]) != len(d["params"]):
            edits.append((d["span"][0], d["span"][1],
                          ", ".join(("%s%s" if ty.endswith("*") else "%s %s") % (ty, nm)
                                    for ty, nm in d["new_params"])))
    out = text
    for s, e, rep in sorted(edits, reverse=True):
        out = out[:s] + rep + out[e:]
    if inserts:
        # in front of the EARLIEST enclosing definition, so one declaration serves every site and
        # any type it names is already in scope
        first = min(d["encl"]["dstart"] for d in pl["defs"])
        shift = sum(len(rep) - (e - s) for s, e, rep in edits if s < first)
        pos = out.rfind("\n", 0, first + shift) + 1
        out = out[:pos] + "\n" + "".join(inserts) + out[pos:]
    return out, decls_found


def _info(row, pl):
    tg = sorted(pl["targets"].items())
    return {
        "n_sites": sum(len(t["recs"]) for _, t in tg),
        "n_targets": len(tg),
        "targets": [n for n, _ in tg],
        "need": ";".join("%s=%s" % (n, ",".join("a%d" % k for k in sorted(t["needs"]))) for n, t in tg),
        "K": {n: t["K"] for n, t in tg},
        "nfill": {n: t["K"] + 1 - len(t["needs"]) for n, t in tg},
        "calls": {n: len(t["calls"]) for n, t in tg},
        "k_per_site": {n: sorted(t["ks"]) for n, t in tg if len(t["ks"]) > 1} or None,
        "ordinal_unified": sorted(n for n, t in tg if t["ordinal_unified"]) or None,
        "params_in": {d["encl"]["name"]: len(d["params"]) for d in pl["defs"]},
        "params_added": {d["encl"]["name"]: len(d["new_params"]) - len(d["params"]) for d in pl["defs"]},
        "argtypes": {n: t.get("argtypes") for n, t in tg},
    }


class T:
    name = "t8c_passthru_joint"; level = 1
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
            pl = plan(text, row)
            cand, decls = rewrite(text, row, pl)
        except t8.Refusal as e:
            return None, {"refused": [str(e)]}
        info = _info(row, pl)
        info["decls_found"] = decls
        v = verify_fn(cand)
        if v.get("exact"):
            return cand, info
        if v.get("status") != "ok" and decls:
            # the prototype names a type the file typedefs below the declaration: same prototypes,
            # all moved in front of the definition (t8's second candidate, jointly)
            try:
                cand2, _ = rewrite(text, row, pl, relocate=True)
            except t8.Refusal as e:
                return None, dict(info, refused=["build-fail; " + str(e)])
            v2 = verify_fn(cand2)
            if v2.get("exact"):
                return cand2, dict(info, decl_moved=True)
            return None, dict(info, decl_moved=True,
                              refused=["not exact after moving the declarations: %s/%s"
                                       % (v2.get("class"), v2.get("total"))])
        return None, dict(info, refused=["not exact: %s/%s" % (v.get("class"), v.get("total"))])

    @staticmethod
    def apply(text, row, census):
        try:
            pl = plan(text, row)
        except t8.Refusal:
            return None
        return rewrite(text, row, pl)[0]
