#!/usr/bin/env python3
"""Pin evidence: what earlier searches learned about a live pin, kept where the next pass finds it.

    python3 tools/pin_evidence.py --build      (re)derive ledger/pin_evidence.jsonl from the journals
    python3 tools/pin_evidence.py <row_id>     print a row's evidence

A pin that a search could remove only by trading it for scaffolding census now counts (a fake
dependency: t15's `depinject` `x = (e) + a; x -= a;`, `livetie` `f(arg + v - v)`, `deadstore` a dead
`x = 0;`) stays in the code - the debt is the same either way, and a labelled pin reads better and
is re-tested by every pin tool.  But the trade was byte-exact, and that is evidence: it says the pin
holds an ORDERING or LIVENESS dependency on one particular value.  This ledger keeps it per pin, and
tools/pin_facts.py shows it in the FACTS block every lane pack carries, so the next pass on the
function starts from "a fake dependency on `a` matched here" instead of from nothing.

One record per (row, pin site at the text the evidence was measured on):
  id, in_sha, site, macro, arg, line, kind, op, detail, found_by, verdict, step
"""
import argparse, json, re, subprocess, sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "tools"))
from common import LEDGER, rows, sha_text
from pin_census import sites_of

OUT = LEDGER / "pin_evidence.jsonl"
FAKE = {
    "depinject": "an injected dependency `{x} = (...) + {a}; {x} -= {a};` matched: the pin orders or keeps a "
                 "value against `{a}`",
    "livetie": "tying `{v}` into a call argument (`arg + {v} - {v}`) matched: the pin keeps `{v}` live "
               "across that call",
    "deadstore": "a dead store `{v} = 0;` after `{v}`'s last use matched: the pin stops `{v}`'s register "
                 "being reused before that point",
}


def _detail(op, body):
    if op == "depinject":
        x, _, a = body.partition("^")
        return {"x": x, "a": a}
    if op == "livetie":
        v, _, rest = body.partition("^")
        return {"v": v, "call": rest}
    if op == "deadstore":
        v, _, line = body.partition("@")
        return {"v": v, "line": line}
    return {}


def _text_at(rel, want_sha):
    """The row's text as the evidence saw it: the working tree if it still is that text, else HEAD's."""
    p = ROOT / rel
    if p.exists():
        t = p.read_text(errors="replace")
        if sha_text(t) == want_sha:
            return t
    r = subprocess.run(["git", "show", "HEAD:" + rel], cwd=ROOT, capture_output=True, text=True)
    return r.stdout if r.returncode == 0 and sha_text(r.stdout) == want_sha else None


def build():
    """Re-derive the ledger.  A record whose text is no longer in the working tree or HEAD (the row
    has moved on) keeps the site fields and the `reproduced` verdict it already had."""
    old = {}
    if OUT.exists():
        for l in OUT.read_text().splitlines():
            if l.strip():
                r = json.loads(l)
                old[(r["id"], r.get("in_sha"), r.get("site"), r.get("op"))] = r
    out = _derive({r["id"]: r for r in rows()})
    for r in out:
        o = old.get((r["id"], r.get("in_sha"), r.get("site"), r.get("op")))
        if o:
            if r.get("macro") is None:
                r.update({k: o.get(k) for k in ("macro", "arg", "line")})
            if "reproduced" in o:
                r["reproduced"] = o["reproduced"]
    OUT.write_text("".join(json.dumps(r) + "\n" for r in out))
    return out


def _derive(by):
    recs = [json.loads(l) for l in open(LEDGER / "sweeps" / "t18_groups.jsonl")]
    applied = {(r["id"], r.get("in_sha")): r for r in recs if r.get("outcome") == "applied"}
    out = []
    for rv in recs:
        if rv.get("outcome") != "reverted":
            continue
        ap = applied.get((rv["id"], rv.get("out_sha")))
        if not ap or rv["id"] not in by:
            continue
        row = by[rv["id"]]
        text = _text_at("src/%s/%s" % (row["container"], Path(row["c_path"]).name), rv.get("out_sha"))
        sites = sites_of(text) if text is not None else None
        for tok in (ap.get("step") or "").split():
            m = re.match(r"g([\d+]+):(.*)$", tok)
            if not m:
                continue
            idx = [int(i) for i in m.group(1).split("+")]
            for part in m.group(2).split("+"):
                op, _, body = part.partition(":")
                if op not in FAKE:
                    continue
                det = _detail(op, body)
                for i in idx:
                    s = sites[i] if sites is not None and i < len(sites) else None
                    out.append({
                        "id": rv["id"], "in_sha": rv.get("out_sha"), "site": i,
                        "macro": s[1] if s else None, "arg": (s[2] if s else None), "line": s[5] if s else None,
                        "kind": "fake-dependency", "op": op, "detail": det,
                        "found_by": "t18_groups deep fence-free pass, %s" % (ap.get("at", "")[:10]),
                        "verdict": "byte-exact with the fake construct; pin kept by policy 2026-09-12 (a fake "
                                   "dependency is scaffolding, not source)",
                        "hint": FAKE[op].format(**{k: (v or "?") for k, v in {"x": det.get("x"), "a": det.get("a"), "v": det.get("v")}.items()}),
                        "step": ap.get("step")})
    # t15's older landings of the same constructs (2026-09-10/11), reverted by the same policy on
    # 2026-09-12.  t15's step names no site, so the revert record carries the pins the landing had
    # removed, resolved on the restored text; the fake op is joint evidence for all of them.
    for l in open(LEDGER / "sweeps" / "t15_shapes.jsonl"):
        rv = json.loads(l)
        if rv.get("outcome") != "reverted" or not rv.get("removed_sites"):
            continue
        for part in (rv.get("step") or "").split("+"):
            op, _, body = part.partition(":")
            if op not in FAKE:
                continue
            det = _detail(op, body)
            for i, macro, arg, line in rv["removed_sites"]:
                out.append({
                    "id": rv["id"], "in_sha": rv.get("out_sha"), "site": i, "macro": macro, "arg": arg,
                    "line": line, "kind": "fake-dependency", "op": op, "detail": det,
                    "found_by": "t15_shapes, landed %s and reverted by policy 2026-09-12" % rv.get("landed_at", "")[:10],
                    "verdict": "byte-exact with the fake construct (removing %d pin(s) jointly: step `%s`); "
                               "pins restored" % (len(rv["removed_sites"]), rv.get("step")),
                    "hint": FAKE[op].format(**{k: (v or "?") for k, v in {"x": det.get("x"), "a": det.get("a"), "v": det.get("v")}.items()}),
                    "step": rv.get("step")})
    return out


def for_row(row_id, text=None):
    """The row's evidence records; `current` marks those measured on exactly this text."""
    if not OUT.exists():
        return []
    h = sha_text(text) if text is not None else None
    out = []
    for l in OUT.read_text().splitlines():
        if l.strip():
            r = json.loads(l)
            if r["id"] == row_id:
                out.append(dict(r, current=(h is None or r.get("in_sha") == h)))
    return out


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("row", nargs="?")
    ap.add_argument("--build", action="store_true")
    a = ap.parse_args()
    if a.build:
        recs = build()
        print("%d evidence records for %d rows -> %s" % (len(recs), len({r["id"] for r in recs}), OUT.relative_to(ROOT)))
    if a.row:
        for r in for_row(a.row):
            print("site %s %s(%s) line %s: %s [%s]" % (r["site"], r["macro"], r["arg"], r["line"], r["hint"], r["found_by"]))


if __name__ == "__main__":
    main()
