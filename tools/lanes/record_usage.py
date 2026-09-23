#!/usr/bin/env python3
"""Record what a Claude (Agent-tool) lane really used, as work/native_lane/<lane>/usage.json.

    # at completion: the orchestrator copies the figures the Agent tool reported (the task-notification's
    # <usage><subagent_tokens>N</subagent_tokens><tool_uses>T</tool_uses><duration_ms>D</duration_ms></usage>,
    # or a foreground Agent result's total tokens / tool uses / duration)
    python3 tools/lanes/record_usage.py r76_opus_a1 --tokens 328384 --tool-uses 129 --duration-ms 2233693 \
            --model claude-opus-5-5
    # afterwards, mechanically, from the orchestrating session's transcript (every lane it launched):
    python3 tools/lanes/record_usage.py --backfill ~/.claude/projects/-home-david-azure-clean/<session>.jsonl
    # a figure nobody measured (kept, but flagged; tools/lanes/ab_report.py leaves it out of tokens/exact)
    python3 tools/lanes/record_usage.py r76_opus_a1 --estimate 300000
    # the standard Agent-tool lane prompt, filled in for a lane (the codex lane prompt + the Claude rules)
    python3 tools/lanes/record_usage.py --prompt r76_opus_a1

Why (2026-09-23).  Round 73's 43 Opus lanes ran through the Agent tool, which writes no codex.log.  Their prompt
asked the lane to append `tokens used` and "your best estimate" to a codex.log it created itself: the figures are
round numbers (215000 ... 850000) and one is 22000000 (r73_opus_s9).  ab_report.py read them as measurements.
The harness DOES measure every subagent: the task-notification that ends a background Agent call carries
<usage> (subagent_tokens, tool_uses, duration_ms), and the subagent's own transcript
(<session>/subagents/agent-<id>.jsonl, with agent-<id>.meta.json naming the description "Opus lane <lane> ...")
carries each API call's usage.  This script records those, never a model's guess.

usage.json (schema azure-clean.lane-usage.v1):
  lane, model, source          source: agent-tool-result (figures typed from the Agent result at completion),
                               agent-tool-result:task-notification (--backfill), estimate (--estimate)
  estimated                    true only for --estimate: ab_report marks the figure `~` and excludes it
  tokens                       the Agent tool's own figure (subagent_tokens / totalTokens).  Measured on r73_opus_s5
                               it is ~ the subagent's FINAL context size (328,384 against a last call of
                               326,038 in context), not the sum over calls.  It is not the same unit as codex's
                               `tokens used`; compare models on weighted cost (config/model_cost_weights.json).
  tool_uses, duration_ms       from the same result; ab_report takes minutes from duration_ms
  transcript                   (--backfill) summed API usage of the subagent's calls, deduplicated by message id:
                               api_calls, input, output, cache_creation, cache_read, and
                               blended = input + cache_creation + output (uncached input + output: the nearest
                               analogue of codex's `tokens used`, which excludes cached input); first/last timestamps.
                               Caveat: `output` is what the transcript logged per message (streaming start values):
                               it under-counts - 2,061 for r73_opus_s9, which wrote a 33 KB report - so `blended` is
                               a floor.  `tokens` stays the primary figure.
  agent_id, session, recorded_at

--backfill never overwrites a usage.json whose source is agent-tool-result (typed at completion) unless --force;
it does replace an `estimate`.  It only writes lanes that exist under work/native_lane/.
"""
import argparse
import json
import re
import sys
from datetime import datetime, timezone
from pathlib import Path

ROOT = next(p for p in Path(__file__).resolve().parents if (p / "tools/common.py").is_file())
LANES = "work/native_lane"
SCHEMA = "azure-clean.lane-usage.v1"
LANE_RE = re.compile(r"\b(r\d+_[A-Za-z0-9_]+)")
NOTE_RE = re.compile(r"<task-id>(\w+)</task-id>.*?<usage><subagent_tokens>(\d+)</subagent_tokens>"
                     r"<tool_uses>(\d+)</tool_uses><duration_ms>(\d+)</duration_ms></usage>", re.S)
PROMPT_TEMPLATE = Path(__file__).resolve().parent / "agent_lane_prompt.md"


def now():
    return datetime.now(timezone.utc).strftime("%Y-%m-%dT%H:%M:%SZ")


def write_usage(lane_dir, rec):
    rec = dict(rec, schema=SCHEMA, lane=Path(lane_dir).name, recorded_at=now())
    (Path(lane_dir) / "usage.json").write_text(json.dumps(rec, indent=1, sort_keys=True) + "\n")
    return rec


def read_usage(lane_dir):
    try:
        return json.loads((Path(lane_dir) / "usage.json").read_text())
    except (OSError, ValueError):
        return None


def _strings(o):
    if isinstance(o, str):
        yield o
    elif isinstance(o, dict):
        for v in o.values():
            yield from _strings(v)
    elif isinstance(o, list):
        for v in o:
            yield from _strings(v)


def notifications(session_jsonl):
    """{agent id: (subagent_tokens, tool_uses, duration_ms, timestamp)}; the LAST notification of an id wins
    (a resumed agent notifies again with its running totals)."""
    out = {}
    with open(session_jsonl, errors="replace") as fh:
        for line in fh:
            if "<subagent_tokens>" not in line:
                continue
            try:
                d = json.loads(line)
            except ValueError:
                continue
            ts = d.get("timestamp") or ""
            for s in _strings(d):
                for m in NOTE_RE.finditer(s):
                    aid = m.group(1)
                    if aid not in out or ts >= out[aid][3]:
                        out[aid] = (int(m.group(2)), int(m.group(3)), int(m.group(4)), ts)
    return out


def transcript_usage(agent_jsonl):
    """Summed API usage of one subagent transcript, deduplicated by message id (a streamed message is
    logged once per content block with the same usage)."""
    by, model, first, last = {}, None, None, None
    try:
        fh = open(agent_jsonl, errors="replace")
    except OSError:
        return None
    with fh:
        for line in fh:
            try:
                d = json.loads(line)
            except ValueError:
                continue
            ts = d.get("timestamp")
            if ts:
                first = first or ts
                last = ts
            m = d.get("message")
            if d.get("type") == "assistant" and isinstance(m, dict) and m.get("usage"):
                by[m.get("id") or len(by)] = m["usage"]
                model = m.get("model") or model
    if not by:
        return None
    s = {k: sum(int(u.get(k) or 0) for u in by.values())
         for k in ("input_tokens", "output_tokens", "cache_creation_input_tokens", "cache_read_input_tokens")}
    return {"api_calls": len(by), "input": s["input_tokens"], "output": s["output_tokens"],
            "cache_creation": s["cache_creation_input_tokens"], "cache_read": s["cache_read_input_tokens"],
            "blended": s["input_tokens"] + s["cache_creation_input_tokens"] + s["output_tokens"],
            "model": model, "first": first, "last": last}


def _codex_log_model(lane_dir):
    try:
        for line in (Path(lane_dir) / "codex.log").read_text(errors="replace").splitlines()[:5]:
            if line.startswith("model:"):
                return line.split(":", 1)[1].strip() or None
    except OSError:
        pass
    return None


def backfill(session_jsonl, root=ROOT, force=False, dry_run=False, lane_glob=None):
    """[(lane, action, record)] for every Agent-tool lane of one orchestrating session."""
    import fnmatch
    session_jsonl = Path(session_jsonl)
    subdir = session_jsonl.with_suffix("") / "subagents"
    notes = notifications(session_jsonl)
    done = []
    for meta in sorted(subdir.glob("agent-*.meta.json")):
        try:
            m = json.loads(meta.read_text())
        except (OSError, ValueError):
            continue
        aid = meta.name[len("agent-"):-len(".meta.json")]
        hit = LANE_RE.search(m.get("description") or "")
        if not hit or aid not in notes:
            continue
        lane = hit.group(1)
        if lane_glob and not fnmatch.fnmatch(lane, lane_glob):
            continue
        d = Path(root) / LANES / lane
        if not d.is_dir():
            continue
        old = read_usage(d)
        if old and old.get("source", "").startswith("agent-tool-result") and not old.get("estimated") and not force:
            done.append((lane, "kept", old))
            continue
        tok, uses, ms, ts = notes[aid]
        tr = transcript_usage(subdir / ("agent-%s.jsonl" % aid))
        model = _codex_log_model(d) or (tr or {}).get("model") or m.get("model")
        rec = {"model": model, "source": "agent-tool-result:task-notification", "estimated": False,
               "tokens": tok, "tool_uses": uses, "duration_ms": ms, "transcript": tr, "agent_id": aid,
               "session": session_jsonl.stem, "notified_at": ts,
               "description": m.get("description")}
        if not dry_run:
            rec = write_usage(d, rec)
        done.append((lane, "written" if not dry_run else "would write", rec))
    return done


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    ap.add_argument("lane", nargs="?")
    ap.add_argument("--tokens", type=int, help="the Agent tool's reported total tokens")
    ap.add_argument("--tool-uses", type=int)
    ap.add_argument("--duration-ms", type=int)
    ap.add_argument("--model", help="model id (default: the lane's codex.log header)")
    ap.add_argument("--source", default="agent-tool-result")
    ap.add_argument("--estimate", type=int, help="a hand estimate: recorded, flagged estimated")
    ap.add_argument("--backfill", metavar="SESSION_JSONL")
    ap.add_argument("--lane-glob", help="--backfill: only lanes matching this fnmatch pattern")
    ap.add_argument("--force", action="store_true")
    ap.add_argument("--dry-run", action="store_true")
    ap.add_argument("--prompt", metavar="LANE", help="print the Agent-tool lane prompt for LANE")
    ap.add_argument("--root", default=str(ROOT))
    a = ap.parse_args(argv)
    if a.prompt:
        d = Path(a.root) / LANES / a.prompt
        print(PROMPT_TEMPLATE.read_text().replace("<LANE_DIR>", str(d)).replace("<LANE>", a.prompt)
              .replace("<REPO>", str(Path(a.root).resolve())))
        return 0
    if a.backfill:
        res = backfill(a.backfill, a.root, a.force, a.dry_run, a.lane_glob)
        for lane, action, rec in res:
            tr = rec.get("transcript") or {}
            print("%-22s %-11s tokens %9s  tool_uses %4s  min %6.1f  blended %s" % (
                lane, action, rec.get("tokens"), rec.get("tool_uses"), (rec.get("duration_ms") or 0) / 60000,
                tr.get("blended", "-")))
        print("%d lane(s)" % len(res))
        return 0
    if not a.lane:
        ap.error("give a lane, --backfill or --prompt")
    d = Path(a.root) / LANES / a.lane
    if not d.is_dir():
        ap.error("no lane directory %s" % d)
    model = a.model or _codex_log_model(d)
    if a.estimate is not None:
        rec = {"model": model, "source": "estimate", "estimated": True, "tokens": a.estimate}
    elif a.tokens is not None:
        rec = {"model": model, "source": a.source, "estimated": False, "tokens": a.tokens,
               "tool_uses": a.tool_uses, "duration_ms": a.duration_ms}
    else:
        ap.error("give --tokens (measured) or --estimate")
    print(json.dumps(write_usage(d, rec), sort_keys=True))
    return 0


if __name__ == "__main__":
    sys.exit(main())
