#!/usr/bin/env python3
"""Explain one ASM_REG allocation as RTL values and chronological allocator events.

This is the small causal layer above :mod:`alloc_trace`.  It does not run a new kind of
experiment: the baseline uses ``diagnose_site`` and an optional natural-C candidate uses the
same ``observe``/``bind``/``trace`` APIs.  Its contribution is to join compile-local quantities
to function-scoped RTL definitions and uses, and to explain an unavailable hard register only
when an earlier allocation attempt in the same function and block actually claimed it.

    # Replay the round-39 diagnosis after its source/recipe repair has landed:
    python3 tools/alloc_explain.py dungeon/func_81811388 --site 0 \
        --source work/native_lane/r39_allocator/base/dungeon/func_81811388.c \
        --baseline-cfg 2.7.2 --candidate src/dungeon/func_81811388.c --cfg 2.7.2-cdk
The JSON deliberately treats pseudo, quantity and allocno numbers as compile-local evidence.
Candidate graphs are rebound from the pinned observation and compared by RTL shape and allocator
properties; numeric pseudo identity is never carried from one compile to another.  Global allocnos
are explicitly reported as unsupported here rather than receiving a local-quantity diagnosis.
"""
import argparse
import collections
import json
from pathlib import Path
import re
import sys

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "tools"))

from alloc_trace import (REG, attempt_reason, bind, diagnose_site, observe, reg_name,
                         target_reason, trace)
from common import clean_path, parse_cfg, rows, sha_text
from pin_census import sites_of
from pin_sites import erase_many


SCHEMA = "alloc-explain/v1"
SET_DEST = re.compile(r"\(set\s+\(reg(?:/\w+)?:[A-Z0-9]+\s+(\d+)(?:\s+[^)]*)?\)")
SYMBOL = re.compile(r'\(symbol_ref:[A-Z0-9]+\s+\(\"([^\"]+)\"\)\)')
REG_EXPR = r"\(reg(?:/\w+)?:[A-Z0-9]+\s+\d+(?:\s+[^)]*)?\)"
PLAIN_REG_SET = re.compile(r"^\(set\s+" + REG_EXPR + r"\s+" + REG_EXPR + r"\)$")
SET_RHS_OP = re.compile(r"^\(set\s+" + REG_EXPR + r"\s+\((?P<op>[A-Za-z_][A-Za-z0-9_]*)")


def recipe_provenance(row, override=None):
    """Effective recipe plus the row recipe it came from, for replay after row config changes."""
    effective = override if override is not None else row["cfg"]
    cell, flags = parse_cfg(effective)
    return {"cfg": effective, "cell": cell, "flags": flags,
            "recorded_row_cfg": row["cfg"],
            "cfg_source": "command-line-override" if override is not None else "row-record"}


def _trusted(rec):
    """The stricter alloc_trace trust predicate, repeated at the consumption boundary."""
    tr = rec.get("trace") or {}
    return bool(rec.get("valid") is True and rec.get("assembly_equal") is True
                and not rec.get("error") and not rec.get("trace_errors")
                and tr.get("assembly_equal") is True and not tr.get("error")
                and not tr.get("errors"))


def _canonical_rtl(pattern, pseudo, first_pseudo):
    """A cross-compile RTL shape: the selected value is @value, other pseudos are anonymous.

    Hard-register numbers remain because they are target facts.  This representation, rather than
    a pseudo number, is what graph comparison is allowed to carry between compiler recipes.
    """
    def replace(m):
        n = int(m[3])
        if n == pseudo:
            label = "@value"
        elif n >= first_pseudo:
            label = "@pseudo"
        else:
            label = "@hard:%s" % reg_name(n)
        flags = m["flags"] or ""
        return "(reg%s:%s %s)" % (flags, m[2], label)
    return REG.sub(replace, pattern)


def _origin(pattern, pseudo, first_pseudo):
    """Describe only what an RTL definition proves; never manufacture a C variable name."""
    destinations = {int(n) for n in SET_DEST.findall(pattern)}
    if pseudo not in destinations:
        return None
    regs = [m for m in REG.finditer(pattern)]
    symbols = SYMBOL.findall(pattern)
    # Only classify a top-level set.  Looking for substrings would call a call's address MEM a
    # memory load, or call `(plus (reg a0) (const_int 1))` a plain incoming-register copy.
    rhs = SET_RHS_OP.match(pattern)
    if rhs is None:
        return {"kind": "rtl-definition"}
    op = rhs["op"]
    if op == "high" and symbols:
        return {"kind": "symbol-high-part", "symbol": symbols[0]}
    if op == "lo_sum" and symbols:
        return {"kind": "symbol-low-part", "symbol": symbols[0]}
    if op == "symbol_ref" and symbols:
        return {"kind": "symbol-address", "symbol": symbols[0]}
    if op == "reg" and PLAIN_REG_SET.fullmatch(pattern) and len(regs) == 2:
        source = int(regs[1][3])
        if source < first_pseudo:
            return {"kind": "hard-register-copy", "register": reg_name(source),
                    "hard": source}
        return {"kind": "pseudo-copy"}
    kinds = {"mem": "memory-load", "plus": "addition", "zero_extend": "zero-extension",
             "call": "call-result"}
    if op in kinds:
        out = {"kind": kinds[op]}
        if symbols:
            out["symbol"] = symbols[0]
        return out
    return {"kind": "rtl-definition"}


def rtl_value(observation, function, pseudo, phase="rtl"):
    """Function-scoped definitions and uses of one compile-local pseudo.

    The function lookup happens before the pseudo lookup.  This is intentional: old GCC restarts
    pseudo numbering per function, so a file-wide search silently joins unrelated values.
    """
    state = (observation.get("state") or {}).get(function) or {}
    first = state.get("first_pseudo", 68)
    patterns = (((observation.get("patterns") or {}).get(function) or {}).get(phase) or [])
    definitions, uses = [], []
    for index, pattern in enumerate(patterns):
        occurrences = [m for m in REG.finditer(pattern) if int(m[3]) == pseudo]
        if not occurrences:
            continue
        destinations = [int(n) for n in SET_DEST.findall(pattern)]
        item = {"rtl_index": index, "pattern": pattern,
                "shape": _canonical_rtl(pattern, pseudo, first)}
        if pseudo in destinations:
            d = dict(item)
            d["origin"] = _origin(pattern, pseudo, first)
            definitions.append(d)
        # A self-update is both a definition and a use.  Otherwise the destination occurrence is
        # excluded, leaving ordinary RHS occurrences as uses.
        use_count = len(occurrences) - (1 if pseudo in destinations else 0)
        if use_count:
            u = dict(item)
            u["occurrences"] = use_count
            uses.append(u)
    origin = next((d["origin"] for d in definitions if d.get("origin")), None)
    return {"function": function, "pseudo": pseudo, "id_scope": "this-compile-only",
            "origin": origin or {"kind": "no-rtl-definition-found"},
            "definitions": definitions, "uses": uses}


def _quantity_node(observation, function, quantity):
    values = [rtl_value(observation, function, p) for p in quantity.get("pseudos") or []]
    q = {"quantity": quantity.get("qty"), "pseudos": quantity.get("pseudos") or [],
         "id_scope": "this-compile-only",
         "allocator": {"birth": quantity.get("birth"), "death": quantity.get("death"),
                       "live_length": (quantity.get("death", 0) - quantity.get("birth", 0)),
                       "refs": quantity.get("n_refs"), "size": quantity.get("size"),
                       "calls_crossed": quantity.get("n_calls_crossed"),
                       "priority": quantity.get("priority"),
                       "suggestions": [reg_name(n) for n in quantity.get("phys_sugg") or []],
                       "copy_suggestions": [reg_name(n)
                                            for n in quantity.get("phys_copy_sugg") or []]},
         "rtl_values": values}
    return q


def _stable_node(node):
    """Quantity graph content with every compile-local numeric identity removed."""
    values = []
    for value in node.get("rtl_values") or []:
        values.append({"origin": value.get("origin"),
                       "definition_shapes": [d["shape"] for d in value.get("definitions") or []],
                       "use_shapes": [u["shape"] for u in value.get("uses") or []]})
    return {"allocator": node.get("allocator"), "rtl_values": values}


def _block_for(rec, reason):
    tr = rec.get("trace") or {}
    return next((b for b in tr.get("blocks") or []
                 if b.get("function") == reason.get("function")
                 and b.get("block") == reason.get("block")), None)


def _quantity(block, qty):
    return next((q for q in block.get("quantities") or [] if q.get("qty") == qty), None)


def _overlap(a, b):
    return max(a.get("birth", 0), b.get("birth", 0)) < min(a.get("death", 0), b.get("death", 0))


def _earlier_claim(block, target_qty, attempt_index, desired):
    """The last strictly earlier overlapping attempt that successfully claimed ``desired``."""
    target = _quantity(block, target_qty)
    if target is None:
        return None
    found = None
    for index, attempt in enumerate((block.get("attempts") or [])[:attempt_index]):
        if attempt.get("qty") == target_qty or attempt.get("result") != desired:
            continue
        q = _quantity(block, attempt.get("qty"))
        if q is not None and _overlap(q, target):
            found = {"attempt_index": index, "attempt": attempt, "quantity": q}
    return found


def local_timeline(block, target_qty, desired):
    """All actual attempts in order, annotated without looking ahead for a competitor."""
    out = []
    for index, attempt in enumerate(block.get("attempts") or []):
        q = _quantity(block, attempt.get("qty")) or {}
        initial = (block.get("initial_occupied") or {}).get(str(attempt.get("qty")), [])
        claim = _earlier_claim(block, attempt.get("qty"), index, desired)
        if desired in (block.get("fixed") or []):
            availability = "fixed-register-exclusion"
        elif (q.get("n_calls_crossed") and desired in (block.get("call_used") or [])
              and not attempt.get("accept_call_clobbered")):
            availability = "call-clobber-exclusion"
        elif desired in initial:
            availability = "preexisting-hard-conflict"
        elif desired in (attempt.get("occupied") or []) and claim:
            availability = "occupied-by-earlier-attempt"
        elif desired in (attempt.get("occupied") or []):
            availability = "occupied-source-unresolved"
        else:
            availability = "available-in-live-set"
        item = {"index": index, "quantity": attempt.get("qty"),
                "pseudos": q.get("pseudos") or [], "id_scope": "this-compile-only",
                "pass": "suggestion" if attempt.get("suggestions_only") else "priority",
                "priority": q.get("priority"), "result": attempt.get("result"),
                "result_register": (reg_name(attempt["result"])
                                    if attempt.get("result", -1) >= 0 else None),
                "occupied": [reg_name(n) for n in attempt.get("occupied") or []],
                "desired_suggested": desired in set((q.get("phys_sugg") or [])
                                                     + (q.get("phys_copy_sugg") or [])),
                "desired_register_state": availability}
        if claim:
            item["desired_register_claimed_at"] = claim["attempt_index"]
            item["desired_register_claimed_by_quantity"] = claim["quantity"].get("qty")
        out.append(item)
    return out


def _decisive_attempt_index(block, target_qty):
    indexes = [i for i, a in enumerate(block.get("attempts") or [])
               if a.get("qty") == target_qty and a.get("result", -1) >= 0]
    return indexes[-1] if indexes else None


def _ordering_basis(claim, target_attempt, target_q):
    cq = claim["quantity"]
    ca = claim["attempt"]
    if ca.get("suggestions_only") and not target_attempt.get("suggestions_only"):
        return "suggestion-pass-precedes-priority-pass"
    if not ca.get("suggestions_only") and not target_attempt.get("suggestions_only"):
        cp, tp = cq.get("priority"), target_q.get("priority")
        if cp is not None and tp is not None and cp > tp:
            return "higher-priority-earlier-in-priority-pass"
        if cp == tp:
            return "observed-earlier-with-equal-priority"
    return "observed-earlier-attempt"


def _origin_phrase(node):
    origins = [v.get("origin") or {} for v in node.get("rtl_values") or []]
    o = origins[0] if origins else {}
    if o.get("kind") == "hard-register-copy":
        return "the RTL value copied from %s" % o.get("register")
    if o.get("symbol"):
        return "the RTL %s for %s" % (o.get("kind", "value"), o["symbol"])
    return "the RTL value with origin %s" % o.get("kind", "unknown")


def _local_entry(rec, reason, observation):
    block = _block_for(rec, reason)
    if block is None:
        return {"status": "local-trace-unmapped", "scope": "local",
                "function": reason.get("function"), "pseudo": reason.get("pseudo")}
    target_q = _quantity(block, (reason.get("quantity") or {}).get("qty"))
    if target_q is None:
        return {"status": "local-trace-unmapped", "scope": "local",
                "function": reason.get("function"), "pseudo": reason.get("pseudo")}
    desired = rec["hard"]
    decisive_index = _decisive_attempt_index(block, target_q["qty"])
    timeline = local_timeline(block, target_q["qty"], desired)
    target_node = _quantity_node(observation, reason["function"], target_q)
    graph_nodes = [_quantity_node(observation, reason["function"], q)
                   for q in block.get("quantities") or []]
    cause = None
    competitor_node = None
    if decisive_index is not None:
        target_attempt = block["attempts"][decisive_index]
        claim = _earlier_claim(block, target_q["qty"], decisive_index, desired)
        initial = (block.get("initial_occupied") or {}).get(str(target_q["qty"]), [])
        if desired in target_attempt.get("occupied", []) and desired not in initial and claim:
            competitor_node = _quantity_node(observation, reason["function"], claim["quantity"])
            cause = {"kind": "desired-register-taken-by-earlier-local-quantity",
                     "desired_register": reg_name(desired), "target_attempt": decisive_index,
                     "competitor_attempt": claim["attempt_index"],
                     "ordering": _ordering_basis(claim, target_attempt, target_q)}
        elif desired in initial:
            cause = {"kind": "preexisting-hard-conflict", "desired_register": reg_name(desired),
                     "target_attempt": decisive_index}
        elif desired in (block.get("fixed") or []):
            cause = {"kind": "fixed-register-exclusion", "desired_register": reg_name(desired),
                     "target_attempt": decisive_index}
        elif target_attempt.get("result") == desired:
            cause = {"kind": "desired-register-selected", "desired_register": reg_name(desired),
                     "target_attempt": decisive_index}
        else:
            cause = {"kind": "no-earlier-claim-proven", "desired_register": reg_name(desired),
                     "target_attempt": decisive_index}
    result = {"status": "ok", "scope": "local", "function": reason["function"],
              "block": reason.get("block"), "desired_register": reg_name(desired),
              "target": target_node, "chronology": timeline, "cause": cause,
              "quantity_graph": graph_nodes}
    if competitor_node:
        result["competitor"] = competitor_node
        result["natural_c_counterfactual"] = {
            "question": "What C shape or compiler recipe makes %s stop claiming %s before %s is allocated?"
                        % (_origin_phrase(competitor_node), reg_name(desired), _origin_phrase(target_node)),
            "evidence_boundary": "Change RTL origin/lifetime/order and re-observe; numeric pseudo and "
                                 "quantity IDs cannot be carried into the candidate compile."}
    elif cause and cause["kind"] == "desired-register-selected":
        result["natural_c_counterfactual"] = {
            "question": "%s already receives %s in this recipe."
                        % (_origin_phrase(target_node), reg_name(desired)),
            "evidence_boundary": "Confirm final assembly separately; allocation alone is not byte identity."}
    return result


def explain_site(rec, observation):
    """Turn one diagnose_site-like record into compact causal entries."""
    if not _trusted(rec):
        return {"site": rec.get("site"), "status": "untrusted-trace",
                "trust": {"valid": rec.get("valid"),
                          "assembly_equal": rec.get("assembly_equal"),
                          "error": rec.get("error"), "trace_errors": rec.get("trace_errors")}}
    entries = []
    reasons = rec.get("reasons") or []
    for bound in rec.get("bound") or []:
        fn, pseudo, owner = bound.get("function"), bound.get("pseudo"), bound.get("owner")
        matching = next((r for r in reasons if r.get("function") == fn
                         and r.get("pseudo") == pseudo and r.get("owner") == owner), None)
        if owner == "global":
            entries.append({"status": "unsupported-global", "scope": "global", "function": fn,
                            "target_rtl": rtl_value(observation, fn, pseudo),
                            "reason": "This tool explains local quantities. Use alloc_trace/alloc_probe "
                                      "for global allocnos; no local chronology was inferred."})
        elif owner == "local" and matching:
            entries.append(_local_entry(rec, matching, observation))
        else:
            entries.append({"status": "unsupported-owner", "scope": owner, "function": fn,
                            "target_rtl": rtl_value(observation, fn, pseudo)})
    status = "ok" if any(e.get("status") == "ok" for e in entries) else (
        entries[0]["status"] if len(entries) == 1 else "no-local-explanation")
    return {"site": rec.get("site"), "line": rec.get("line"),
            "site_declaration_name": rec.get("var"),
            "name_evidence": "ASM_REG declaration syntax, not inferred from a pseudo",
            "status": status, "entries": entries}


def compare_entries(baseline, candidate):
    """Compare local quantity graphs by stable content, never by pseudo/quantity number."""
    if baseline.get("status") != "ok" or candidate.get("status") != "ok":
        return {"status": "not-comparable", "baseline_status": baseline.get("status"),
                "candidate_status": candidate.get("status"), "pseudo_ids_compared": False}
    bes = [e for e in baseline.get("entries") or [] if e.get("status") == "ok"]
    ces = [e for e in candidate.get("entries") or [] if e.get("status") == "ok"]
    if len(bes) != 1 or len(ces) != 1:
        return {"status": "ambiguous-binding", "baseline_local_entries": len(bes),
                "candidate_local_entries": len(ces), "pseudo_ids_compared": False,
                "reason": "Per-compile entries remain available, but there is no unique safe "
                          "cross-compile value pairing."}
    be, ce = bes[0], ces[0]
    if not be or not ce:
        return {"status": "not-comparable", "pseudo_ids_compared": False}
    bc = collections.Counter(json.dumps(_stable_node(n), sort_keys=True, separators=(",", ":"))
                             for n in be.get("quantity_graph") or [])
    cc = collections.Counter(json.dumps(_stable_node(n), sort_keys=True, separators=(",", ":"))
                             for n in ce.get("quantity_graph") or [])
    removed, added = list((bc - cc).elements()), list((cc - bc).elements())
    return {"status": "changed" if removed or added else "unchanged",
            "pseudo_ids_compared": False,
            "binding": "each compile rebound independently from the pinned hard-register observation",
            "baseline_cause": (be.get("cause") or {}).get("kind"),
            "candidate_cause": (ce.get("cause") or {}).get("kind"),
            "removed_nodes": [json.loads(x) for x in removed],
            "added_nodes": [json.loads(x) for x in added]}


def _candidate_record(row, text, pinned_observation, hard, site):
    """Observe and trace an already-natural candidate (there is no pin to erase here)."""
    obs = observe(row, text)
    rec = {"site": site, "hard": hard, "bound": [], "reasons": [], "attempt_reasons": []}
    if obs.get("error"):
        rec.update(valid=False, assembly_equal=False, error="candidate-compile: " + obs["error"],
                   trace_errors=[])
        return rec, obs
    rec["bound"] = bind(pinned_observation, obs, hard)
    if not rec["bound"]:
        rec.update(valid=False, assembly_equal=False, error="candidate-unmapped-binding", trace_errors=[])
        return rec, obs
    tr = trace(row, text, obs["assembly"])
    rec["trace"] = tr
    rec["assembly_equal"] = bool(tr.get("assembly_equal"))
    rec["trace_errors"] = tr.get("errors")
    rec["error"] = tr.get("error")
    rec["valid"] = bool(tr.get("assembly_equal") and not tr.get("error") and not tr.get("errors"))
    if rec["valid"]:
        rec["reasons"] = [r for b in rec["bound"] for r in target_reason(tr, b, hard)]
        rec["attempt_reasons"] = [attempt_reason(tr, b, hard) for b in rec["bound"]
                                  if b.get("owner") == "global"]
    return rec, obs


def explain_row(row, site, source=None, candidate=None, candidate_cfg=None, baseline_cfg=None):
    source_path = Path(source) if source else clean_path(row)
    text = source_path.read_text()
    pins = sites_of(text)
    if site < 0 or site >= len(pins):
        raise SystemExit("alloc_explain: site %d out of range (%d pins)" % (site, len(pins)))
    if pins[site][1] != "ASM_REG":
        raise SystemExit("alloc_explain: site %d is %s, not ASM_REG" % (site, pins[site][1]))

    baseline_row = dict(row)
    if baseline_cfg is not None:
        baseline_row["cfg"] = baseline_cfg
    pinned_observation = observe(baseline_row, text)
    baseline_rec = diagnose_site(baseline_row, text, pins, site, target=pinned_observation)
    erased = erase_many(text, [pins[site]], clean_notes=True)
    erased_observation = observe(baseline_row, erased)
    baseline = explain_site(baseline_rec, erased_observation)
    report = {"schema": SCHEMA, "row": row["id"], "site": site,
              "provenance": {"baseline": {"source": str(source_path), "source_sha256": sha_text(text),
                                            "natural_source_sha256": sha_text(erased),
                                            "recipe": recipe_provenance(row, baseline_cfg),
                                            "operations": ["observe pinned source",
                                                           "erase selected ASM_REG site",
                                                           "observe erased source",
                                                           "trace erased source"]},
                             "identity_rule": "pseudo, quantity and allocno IDs are compile-local"},
              "baseline": baseline}

    if candidate is not None or candidate_cfg is not None:
        candidate_path = Path(candidate) if candidate else None
        candidate_text = candidate_path.read_text() if candidate_path else erased
        crow = dict(row)
        if candidate_cfg:
            crow["cfg"] = candidate_cfg
        candidate_rec, candidate_observation = _candidate_record(
            crow, candidate_text, pinned_observation, baseline_rec.get("hard"), site)
        candidate_explanation = explain_site(candidate_rec, candidate_observation)
        report["provenance"]["candidate"] = {
            "source": str(candidate_path) if candidate_path else "baseline source with selected site erased",
            "source_sha256": sha_text(candidate_text),
            "recipe": recipe_provenance(row, candidate_cfg),
            "operations": ["observe candidate", "rebind from pinned hard-register observation",
                           "trace candidate"]}
        report["candidate"] = candidate_explanation
        report["comparison"] = compare_entries(baseline, candidate_explanation)
    return report


def main():
    ap = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    ap.add_argument("row", help="row id, e.g. dungeon/func_81811388")
    ap.add_argument("--site", required=True, type=int,
                    help="site index from tools/pin_census.sites_of")
    ap.add_argument("--source", help="pinned baseline source (default: current row source)")
    ap.add_argument("--baseline-cfg",
                    help="baseline compiler recipe/config label (default: row's recorded cfg)")
    ap.add_argument("--candidate", help="natural-C candidate source to compare")
    ap.add_argument("--cfg",
                    help="candidate compiler recipe/config label (default: row's recorded cfg)")
    ap.add_argument("--out", help="also write compact JSON to this path")
    args = ap.parse_args()
    row = next((r for r in rows() if r["id"] == args.row), None)
    if row is None:
        raise SystemExit("alloc_explain: unknown row %s" % args.row)
    report = explain_row(row, args.site, args.source, args.candidate, args.cfg, args.baseline_cfg)
    payload = json.dumps(report, separators=(",", ":")) + "\n"
    if args.out:
        Path(args.out).write_text(payload)
    sys.stdout.write(payload)


if __name__ == "__main__":
    main()
