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
  last_message.txt  end time = its mtime (codex -o writes it on a normal exit).  A lane cut by the
                 usage limit ("You've hit your usage limit" in the log tail) has no last_message.txt but
                 still prints `tokens used`: its end is codex.log's mtime and its status is `limit`.
                 status: ok | limit | ended (exited, no message, no limit line) | running (live lane.pid).
                 Compare models on `ok` lanes: a limit-cut lane stopped early, not by choice.
  base/*/*.c     rows served; pins before = live ASM_ pin sites (tools/pin_census.py sites_of).
  out/*/*.c      a row is EXACT when out/<c>/<name>.c has a sibling .base_sha (the kit's lab.py writes
                 it for byte-exact candidates only); pins after = sites in that file.
  ledger/model_capacity.jsonl  joined by pack name: the pool's journalled candidate count and note; the
                 model comes from it when codex.log has none.
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
from pin_census import sites_of  # noqa: E402

LANES = "work/native_lane"
CAPACITY = "ledger/model_capacity.jsonl"
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


def scan(d, cap=None):
    """One record for lane directory d."""
    d = Path(d)
    model = tokens = None
    limit = False
    log = d / "codex.log"
    if log.is_file():
        with log.open("rb") as fh:
            model = parse_model(fh.read(8192).decode("utf-8", "replace"))
            size = fh.seek(0, os.SEEK_END)
            fh.seek(max(0, size - 65536))
            tail = fh.read().decode("utf-8", "replace")
        tokens = parse_tokens(tail)
        limit = "hit your usage limit" in tail[-4096:]
    cap = cap or {}
    if model is None:
        model = (cap.get("codex") or {}).get("model")
    start = _mtime(d / "lane.pid", d / "PROMPT.txt")
    if (d / "last_message.txt").exists():
        status, end = "ok", _mtime(d / "last_message.txt")
    elif _alive(d / "lane.pid"):
        status, end = "running", None
    elif log.is_file():
        status, end = "limit" if limit else "ended", _mtime(log)
    else:
        status, end = "unlaunched", None
    minutes = round((end - start) / 60, 1) if start and end and end >= start else None
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
            "minutes": minutes, "tokens": tokens, "status": status,
            "journal_candidates": (cap.get("codex") or {}).get("candidates"), "note": cap.get("note")}


def aggregate(recs):
    by = {}
    for r in recs:
        by.setdefault(r["model"], []).append(r)
    out = []
    for model, rs in sorted(by.items()):
        mins = [r["minutes"] for r in rs if r["minutes"] is not None]
        toks = [r["tokens"] for r in rs if r["tokens"] is not None]
        rows = sum(r["rows"] for r in rs)
        exact = sum(r["exact"] for r in rs)
        tok_lanes_exact = sum(r["exact"] for r in rs if r["tokens"] is not None)
        out.append({"model": model, "lanes": len(rs), "ok": sum(r["status"] == "ok" for r in rs),
                    "limit": sum(r["status"] == "limit" for r in rs), "rows": rows, "exact": exact,
                    "exact_rate": round(exact / rows, 3) if rows else None,
                    "pins_removed": sum(r["pins_removed"] for r in rs),
                    "mean_minutes": round(sum(mins) / len(mins), 1) if mins else None,
                    "mean_tokens": round(sum(toks) / len(toks)) if toks else None,
                    # over the lanes that report tokens only, so a missing figure does not flatter a model
                    "tokens_per_exact": round(sum(toks) / tok_lanes_exact) if tok_lanes_exact else None})
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


def markdown(recs, agg):
    out = ["| lane | model | status | rows | exact | pins before -> after (exact rows) | minutes | tokens | journal |",
           "|---|---|---|---:|---:|---|---:|---:|---:|"]
    for r in recs:
        out.append("| %s | %s | %s | %d | %d | %s | %s | %s | %s |" % (
            r["lane"], r["model"], r["status"], r["rows"], r["exact"],
            "%d -> %d" % (r["pins_before"], r["pins_after"]) if r["exact"] else "-",
            _f(r["minutes"]), "-" if r["tokens"] is None else "{:,}".format(r["tokens"]),
            _f(r["journal_candidates"])))
    out += ["", "| model | lanes (ok/limit) | rows | exact | exact rate | pins removed | mean min | mean tokens | tokens/exact |",
            "|---|---|---:|---:|---:|---:|---:|---:|---:|"]
    for a in agg:
        out.append("| %s | %d (%d/%d) | %d | %d | %s | %d | %s | %s | %s |" % (
            a["model"], a["lanes"], a["ok"], a["limit"], a["rows"], a["exact"], "-" if a["exact_rate"] is None else "%.1f%%" % (100 * a["exact_rate"]),
            a["pins_removed"], _f(a["mean_minutes"]), "-" if a["mean_tokens"] is None else "{:,}".format(a["mean_tokens"]),
            "-" if a["tokens_per_exact"] is None else "{:,}".format(a["tokens_per_exact"])))
    return "\n".join(out)


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    ap.add_argument("--lanes", default="", type=lambda s: [x for x in s.replace(",", " ").split() if x])
    ap.add_argument("--glob", action="append", default=[], help="fnmatch on lane directory names (repeatable)")
    ap.add_argument("--ok-only", action="store_true", help="aggregate only lanes that exited normally (status ok)")
    ap.add_argument("--json", action="store_true")
    ap.add_argument("--root", default=str(ROOT))
    a = ap.parse_args(argv)
    if not a.lanes and not a.glob:
        ap.error("give --lanes and/or --glob")
    cap = capacity(a.root)
    recs = [scan(d, cap.get(d.name)) for d in lane_dirs(a.root, a.lanes, a.glob)]
    agg = aggregate([r for r in recs if r["status"] == "ok"] if a.ok_only else recs)
    if a.json:
        print(json.dumps({"lanes": recs, "models": agg}, indent=1))
    else:
        print(markdown(recs, agg) if recs else "no lanes matched")
    return 0


if __name__ == "__main__":
    sys.exit(main())
