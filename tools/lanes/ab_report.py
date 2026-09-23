#!/usr/bin/env python3
"""Per-model A/B readout over codex lanes: rows, byte-exact rows, pins removed, minutes, tokens.

    python3 tools/lanes/ab_report.py --glob 'r72_kit_*'
    python3 tools/lanes/ab_report.py --lanes r73_sol6_1,r73_sol6_2 --glob 'r73_kit_sol*' [--json]

Compare models on the same KIND of rows (same builder, same brief, same pin band): the r70/r71/r72 kit
lanes are the gpt-6-astra / gpt-5.6-sol baseline for the gpt-6-sol / gpt-6-luna lanes.

What is read, per lane directory work/native_lane/<lane> (--glob matches directory NAMES only; nothing
is searched recursively - only the files below are opened):
  codex.log      header line `model: <id>` (codex >= 0.154 wraps the key in ANSI bold, stripped here) and
                 the `tokens used` line near the end, whose NEXT line is the figure ("376,901").
  lane.pid       launch time = its mtime (launch_lane.sh writes it at launch).  PROMPT.txt is NOT used
                 as the start: it is stamped when the pack is built, which in a pool can be hours before
                 the launch (r71_kit_sol1: 88 min).  Fallback when lane.pid is missing: PROMPT.txt.
  last_message.txt  end time = its mtime (codex -o writes it on a normal exit).  A lane cut by a
                 PROVIDER quota/capacity error (round 76, tools/lanes/lane_limit.py: codex "at capacity" /
                 "usage limit" / "rate limit" as a leading `ERROR:` line in codex.log; agy/Gemini
                 RESOURCE_EXHAUSTED / code 429 / quota in agy.log) is status `limit` REGARDLESS of
                 last_message.txt -- the agy runner can still write one on a quota error, and codex's may
                 be missing.  Its end is codex.log's or agy.log's mtime, whichever exists.
                 status: cap | limit | ok | ended (exited, no message, no limit/cap) | running (live lane.pid).
                 Compare models on `ok` lanes: a limit-cut (or capped) lane stopped early, not by choice.
                 `--ok-only` excludes `limit` and `cap` lanes from the aggregate.
  base/*/*.c     rows served; pins before = live ASM_ pin sites (tools/pin_census.py sites_of).
  out/*/*.c      a row is EXACT when out/<c>/<name>.c has a sibling .base_sha (the kit's lab.py writes
                 it for byte-exact candidates only); pins after = sites in that file.
  ledger/model_capacity.jsonl  joined by pack name: the pool's journalled candidate count and note; the
                 model comes from it when codex.log has none.
  usage.json     (round 76, tools/lanes/record_usage.py) an Agent-tool (Claude) lane's MEASURED usage: tokens,
                 tool_uses, duration_ms from the Agent result.  It wins over codex.log: its model, its tokens
                 (`tokens_source` = its source) and its duration as the lane's minutes.  A claude-* lane with a
                 `tokens used` figure in codex.log and no usage.json is a hand/self estimate (round 73's lanes
                 typed their own guess, one of them 22,000,000): `estimated` = true, shown as `~N`, and left out
                 of mean tokens, tokens/exact and the weighted cost.  So is a usage.json with estimated = true.
  cap.txt        (round 76) the lane was killed at a wall-time cap (launch_lane.sh LANE_WALL_CAP / pool.py
                 --wall-cap): status `cap`.

Cost (round 76).  Tokens are not cost: the owner puts gpt-6-luna at ~10x less draining than gpt-6-sol.
config/model_cost_weights.json holds the per-token weight of each model (luna 1, sol 10; the others null =
TODO, never invented).  Weighted cost of a lane = tokens x weight / 1e6; the aggregate reports weighted cost
per exact row and per pin removed (over lanes with a measured figure and a known weight), and wall-minutes
per exact row.  --weight MODEL=W sets a what-if weight for one run, marked `*` (assumed) in the table.
"""
import argparse
import fnmatch
import json
import os
import re
import sys
from pathlib import Path

ROOT = next(p for p in Path(__file__).resolve().parents if (p / "tools/common.py").is_file())
sys.path.insert(0, str(ROOT / "tools"))
sys.path.insert(0, str(Path(__file__).resolve().parent))
from pin_census import sites_of  # noqa: E402
import lane_limit  # noqa: E402

LANES = "work/native_lane"
CAPACITY = "ledger/model_capacity.jsonl"
WEIGHTS = "config/model_cost_weights.json"
BRACKET_RE = re.compile(r"\[[^\]]*\]$")
ANSI_RE = re.compile(r"\x1b\[[0-9;]*m")


def parse_model(head):
    for line in head.splitlines()[:40]:
        line = ANSI_RE.sub("", line).strip()
        if line.startswith("model:"):
            return line.split(":", 1)[1].strip() or None
        if line == "user":
            break
    return None


def parse_tokens(tail):
    """The figure on the line after the LAST `tokens used` line, or None."""
    lines = [ANSI_RE.sub("", l).strip() for l in tail.splitlines()]
    for i in range(len(lines) - 2, -1, -1):
        if lines[i] == "tokens used":
            digits = lines[i + 1].replace(",", "")
            return int(digits) if digits.isdigit() else None
    return None


def _mtime(*paths):
    for p in paths:
        try:
            return p.stat().st_mtime
        except OSError:
            pass
    return None


def _alive(pidfile):
    try:
        os.kill(int(pidfile.read_text().strip()), 0)
    except (OSError, ValueError):
        return False
    return True


def _pins(path):
    try:
        return len(sites_of(path.read_text(errors="replace")))
    except OSError:
        return None


def capacity(root):
    out = {}
    try:
        with (Path(root) / CAPACITY).open(errors="replace") as fh:
            for line in fh:
                try:
                    rec = json.loads(line)
                except ValueError:
                    continue
                c = rec.get("codex") or {}
                if c.get("pack"):
                    out[c["pack"]] = rec                        # the latest journal line wins
    except OSError:
        pass
    return out


def model_key(model):
    """The weights-table key of a model id: `claude-opus-5-5[1m]` -> `claude-opus-5-5`."""
    return BRACKET_RE.sub("", (model or "").strip())


def load_weights(root, overrides=()):
    """({model key: weight or None}, {model key: True when assumed via --weight, or (lo, hi) for a null weight
    with a `range` in the config})."""
    try:
        cfg = json.loads((Path(root) / WEIGHTS).read_text())
    except (OSError, ValueError):
        cfg = {}
    w = dict(cfg.get("weights") or {})
    assumed = {k: tuple(v) for k, v in (cfg.get("range") or {}).items() if w.get(k) is None}
    for o in overrides:
        k, _, v = o.partition("=")
        w[model_key(k)] = float(v)
        assumed[model_key(k)] = True
    return w, assumed


def read_usage(d):
    try:
        return json.loads((Path(d) / "usage.json").read_text())
    except (OSError, ValueError):
        return None


def scan(d, cap=None):
    """One record for lane directory d."""
    d = Path(d)
    model = tokens = None
    tail = ""
    usage = read_usage(d)
    log = d / "codex.log"
    if log.is_file():
        with log.open("rb") as fh:
            model = parse_model(fh.read(8192).decode("utf-8", "replace"))
            size = fh.seek(0, os.SEEK_END)
            fh.seek(max(0, size - 65536))
            tail = fh.read().decode("utf-8", "replace")
        tokens = parse_tokens(tail)
    agy_log = d / "agy.log"
    agy_tail = lane_limit._tail(agy_log) if agy_log.is_file() else ""
    # round 76: a provider quota/capacity cut (agy RESOURCE_EXHAUSTED/429, codex "at capacity"/usage
    # limit/rate limit) is a lane cut off, not a normal finish -- checked ahead of last_message.txt below
    # because the agy runner can still write one even on a quota error.
    limit = lane_limit.codex_hit_limit(tail) or lane_limit.agy_hit_limit(agy_tail)
    cap = cap or {}
    tokens_source = "codex-log" if tokens is not None else None
    estimated = False
    if usage:
        model = usage.get("model") or model
        if usage.get("tokens") is not None:
            tokens, tokens_source = int(usage["tokens"]), usage.get("source") or "usage.json"
        estimated = bool(usage.get("estimated"))
    elif tokens is not None and (model or "").lower().startswith("claude"):
        estimated, tokens_source = True, "codex-log (self-reported by an Agent-tool lane)"
    if model is None:
        model = (cap.get("codex") or {}).get("model")
    start = _mtime(d / "lane.pid", d / "PROMPT.txt")
    if (d / "cap.txt").exists():                           # killed at a cap, even if a message was written
        status, end = "cap", _mtime(d / "cap.txt")
    elif limit:                                             # a provider cut it off, whatever else was written
        status, end = "limit", _mtime(log, agy_log)
    elif (d / "last_message.txt").exists():
        status, end = "ok", _mtime(d / "last_message.txt")
    elif _alive(d / "lane.pid"):
        status, end = "running", None
    elif log.is_file():
        status, end = "ended", _mtime(log)
    else:
        status, end = "unlaunched", None
    minutes = round((end - start) / 60, 1) if start and end and end >= start else None
    if usage and usage.get("duration_ms"):
        minutes = round(usage["duration_ms"] / 60000, 1)   # the Agent tool's own clock (no lane.pid for these)
    rows, exact = [], []
    for base in sorted((d / "base").glob("*/*.c")):
        rid = base.parent.name + "/" + base.stem
        rows.append(rid)
        out = d / "out" / base.parent.name / base.name
        if out.is_file() and Path(str(out) + ".base_sha").is_file():
            exact.append({"row": rid, "before": _pins(base), "after": _pins(out)})
    removed = sum(e["before"] - e["after"] for e in exact if e["before"] is not None and e["after"] is not None)
    return {"lane": d.name, "model": model or "?", "rows": len(rows), "exact": len(exact),
            "exact_rows": exact, "pins_before": sum(e["before"] or 0 for e in exact),
            "pins_after": sum(e["after"] or 0 for e in exact), "pins_removed": removed,
            "minutes": minutes, "tokens": tokens, "tokens_source": tokens_source, "estimated": estimated,
            "status": status,
            "journal_candidates": (cap.get("codex") or {}).get("candidates"), "note": cap.get("note")}


def aggregate(recs, weights=None, assumed=None):
    """Per-model totals.  Token figures count only MEASURED lanes (estimated ones are listed, not summed);
    weighted cost = tokens x weight / 1e6 over measured lanes whose model has a weight."""
    weights, assumed = weights or {}, assumed or {}
    by = {}
    for r in recs:
        by.setdefault(r["model"], []).append(r)
    out = []
    for model, rs in sorted(by.items()):
        mins = [r["minutes"] for r in rs if r["minutes"] is not None]
        meas = [r for r in rs if r["tokens"] is not None and not r.get("estimated")]
        toks = [r["tokens"] for r in meas]
        rows = sum(r["rows"] for r in rs)
        exact = sum(r["exact"] for r in rs)
        tok_lanes_exact = sum(r["exact"] for r in meas)
        w = weights.get(model_key(model))
        rng = assumed.get(model_key(model)) if isinstance(assumed.get(model_key(model)), tuple) else None
        wcost = sum(r["tokens"] for r in meas) * w / 1e6 if (w is not None and meas) else None
        if w == 0:                                         # a free window: zero cost even with no token figure
            wcost, meas_exact = 0.0, exact
        else:
            meas_exact = tok_lanes_exact
        w_pins = sum(r["pins_removed"] for r in meas)
        min_exact = sum(r["exact"] for r in rs if r["minutes"] is not None)
        out.append({"model": model, "lanes": len(rs), "ok": sum(r["status"] == "ok" for r in rs),
                    "limit": sum(r["status"] == "limit" for r in rs), "cap": sum(r["status"] == "cap" for r in rs),
                    "rows": rows, "exact": exact,
                    "exact_rate": round(exact / rows, 3) if rows else None,
                    "pins_removed": sum(r["pins_removed"] for r in rs),
                    "mean_minutes": round(sum(mins) / len(mins), 1) if mins else None,
                    "minutes_per_exact": round(sum(mins) / min_exact, 1) if min_exact else None,
                    "mean_tokens": round(sum(toks) / len(toks)) if toks else None,
                    "measured_lanes": len(meas), "estimated_lanes": sum(1 for r in rs if r.get("estimated")),
                    # over the lanes that report tokens only, so a missing figure does not flatter a model
                    "tokens_per_exact": round(sum(toks) / tok_lanes_exact) if tok_lanes_exact else None,
                    "weight": w, "weight_assumed": assumed.get(model_key(model)) is True, "weight_range": rng,
                    "weighted_cost": round(wcost, 3) if wcost is not None else None,
                    "wcost_per_exact": round(wcost / meas_exact, 3) if wcost is not None and meas_exact else None,
                    "wcost_per_pin": round(wcost / (w_pins if w else sum(r["pins_removed"] for r in rs)), 3)
                    if wcost is not None and (w_pins if w else sum(r["pins_removed"] for r in rs)) else None,
                    "wcost_per_exact_range": [round(sum(toks) * x / 1e6 / tok_lanes_exact, 3) for x in rng]
                    if rng and tok_lanes_exact else None,
                    "wcost_per_pin_range": [round(sum(toks) * x / 1e6 / w_pins, 3) for x in rng]
                    if rng and w_pins else None})
    return out


def lane_dirs(root, lanes, globs):
    base = Path(root) / LANES
    names = list(lanes)
    if globs:
        every = sorted(e.name for e in os.scandir(base) if e.is_dir())
        for g in globs:
            names += [n for n in every if fnmatch.fnmatch(n, g) and n not in names]
    return [base / n for n in names if (base / n).is_dir()]


def _f(v, fmt="%s"):
    return "-" if v is None else fmt % v


def _tok(r):
    if r["tokens"] is None:
        return "-"
    return ("~" if r.get("estimated") else "") + "{:,}".format(r["tokens"])


def markdown(recs, agg):
    out = ["| lane | model | status | rows | exact | pins before -> after (exact rows) | minutes | tokens | journal |",
           "|---|---|---|---:|---:|---|---:|---:|---:|"]
    for r in recs:
        out.append("| %s | %s | %s | %d | %d | %s | %s | %s | %s |" % (
            r["lane"], r["model"], r["status"], r["rows"], r["exact"],
            "%d -> %d" % (r["pins_before"], r["pins_after"]) if r["exact"] else "-",
            _f(r["minutes"]), _tok(r), _f(r["journal_candidates"])))
    out += ["", "| model | lanes (ok/limit/cap) | rows | exact | exact rate | pins removed | mean min | min/exact "
            "| mean tokens (measured lanes) | tokens/exact | weight | wcost/exact | wcost/pin |",
            "|---|---|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|"]
    for a in agg:
        est = " +%d est." % a["estimated_lanes"] if a["estimated_lanes"] else ""
        out.append("| %s | %d (%d/%d/%d) | %d | %d | %s | %d | %s | %s | %s (%d%s) | %s | %s | %s | %s |" % (
            a["model"], a["lanes"], a["ok"], a["limit"], a["cap"], a["rows"], a["exact"],
            "-" if a["exact_rate"] is None else "%.1f%%" % (100 * a["exact_rate"]),
            a["pins_removed"], _f(a["mean_minutes"]), _f(a["minutes_per_exact"]),
            "-" if a["mean_tokens"] is None else "{:,}".format(a["mean_tokens"]), a["measured_lanes"], est,
            "-" if a["tokens_per_exact"] is None else "{:,}".format(a["tokens_per_exact"]),
            ("%g-%g" % tuple(a["weight_range"]) if a["weight_range"] else "TODO") if a["weight"] is None
            else ("%g%s" % (a["weight"], "*" if a["weight_assumed"] else "")),
            "%.3f-%.3f" % tuple(a["wcost_per_exact_range"]) if a["wcost_per_exact_range"] else _f(a["wcost_per_exact"], "%.3f"),
            "%.3f-%.3f" % tuple(a["wcost_per_pin_range"]) if a["wcost_per_pin_range"] else _f(a["wcost_per_pin"], "%.3f")))
    out += ["", "tokens `~N` = an estimate (self-reported, not measured): excluded from mean tokens, tokens/exact and "
            "weighted cost.  wcost = tokens x weight / 1e6 (config/model_cost_weights.json; `*` = --weight what-if, "
            "TODO = no weight stated).  Codex and Agent-tool token figures are different units (see the docstring)."]
    return "\n".join(out)


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    ap.add_argument("--lanes", default="", type=lambda s: [x for x in s.replace(",", " ").split() if x])
    ap.add_argument("--glob", action="append", default=[], help="fnmatch on lane directory names (repeatable)")
    ap.add_argument("--ok-only", action="store_true", help="aggregate only lanes that exited normally (status ok)")
    ap.add_argument("--json", action="store_true")
    ap.add_argument("--weight", action="append", default=[], metavar="MODEL=W",
                    help="what-if cost weight for one model (repeatable), marked * in the table")
    ap.add_argument("--root", default=str(ROOT))
    a = ap.parse_args(argv)
    if not a.lanes and not a.glob:
        ap.error("give --lanes and/or --glob")
    cap = capacity(a.root)
    recs = [scan(d, cap.get(d.name)) for d in lane_dirs(a.root, a.lanes, a.glob)]
    weights, assumed = load_weights(a.root, a.weight)
    agg = aggregate([r for r in recs if r["status"] == "ok"] if a.ok_only else recs, weights, assumed)
    if a.json:
        print(json.dumps({"lanes": recs, "models": agg}, indent=1))
    else:
        print(markdown(recs, agg) if recs else "no lanes matched")
    return 0


if __name__ == "__main__":
    sys.exit(main())
