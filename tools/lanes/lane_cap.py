#!/usr/bin/env python3
"""Per-lane runaway caps and the per-band stop rule (round 76).  Everything here is OFF unless asked for.

    # watch one launched lane; kill it past a token or wall cap (launch_lane.sh starts this when
    # LANE_TOKEN_CAP / LANE_WALL_CAP is set; pool.py does the same checks in-process with --token-cap/--wall-cap)
    python3 tools/lanes/lane_cap.py watch r76_sol6_a1 --tokens 3000000 --minutes 120
    python3 tools/lanes/lane_cap.py tokens r76_sol6_a1          # the lane's live codex token figure, if any

Caps.  A capped lane is killed (SIGTERM to its process group when launch_lane.sh made it a group leader with
setsid, else to its pid) and gets `cap.txt` (what fired, the figure, the time): ab_report.py reports it as status
`cap`, pool.lane_state treats it as ran (never relaunched), and candidates it staged in out/ still land.
  wall   minutes since lane.pid was written (launch_lane.sh writes it at launch)
  tokens codex prints `tokens used` only at exit, but its session rollout (~/.codex/sessions/YYYY/MM/DD/
         rollout-*.jsonl) logs a `token_count` event per turn with total_token_usage.  live_tokens() finds
         the lane's rollout (created after the launch, first user message naming the lane directory; the path
         is cached in <lane>/rollout.txt) and returns input - cached_input + output: exactly the figure codex
         prints at exit (r75_astra_p5: 14,813,611 - 14,100,864 + 116,104 = 828,851).  Agent-tool (Claude)
         lanes have no rollout: their cap is the orchestrator's (the Agent call), not this tool's.

Band stop.  band_stop(history, window, threshold, weight): the last `window` finished lanes of one pin band
(served.band_of of the lane's largest base row), pins removed per weighted-cost unit (tokens x weight / 1e6,
config/model_cost_weights.json).  Below `threshold` the pool stops feeding that band.  A model whose weight is
null (TODO) never triggers it: the rule does not act on an invented number.  Fewer than `window` finished
lanes, or no measured tokens: no decision.
"""
import argparse
import json
import os
import signal
import sys
import time
from datetime import datetime, timezone
from pathlib import Path

ROOT = next(p for p in Path(__file__).resolve().parents if (p / "tools/common.py").is_file())
sys.path.insert(0, str(Path(__file__).resolve().parent))
LANES = "work/native_lane"
SESSIONS = Path(os.environ.get("CODEX_HOME", str(Path.home() / ".codex"))) / "sessions"


def lane_dir(root, lane):
    return Path(root) / LANES / lane


def lane_start(root, lane):
    try:
        return (lane_dir(root, lane) / "lane.pid").stat().st_mtime
    except OSError:
        return None


def over_wall(start, now, cap_minutes):
    return bool(cap_minutes) and start is not None and (now - start) > cap_minutes * 60


def _rollout_tokens(path):
    """input - cached + output of the LAST token_count event in a rollout file, or None."""
    try:
        with open(path, "rb") as fh:
            size = fh.seek(0, os.SEEK_END)
            fh.seek(max(0, size - 262144))
            tail = fh.read().decode("utf-8", "replace")
    except OSError:
        return None
    for line in reversed(tail.splitlines()):
        if '"token_count"' not in line:
            continue
        try:
            info = (json.loads(line).get("payload") or {}).get("info") or {}
        except ValueError:
            continue
        t = info.get("total_token_usage")
        if t:
            return int(t.get("input_tokens", 0)) - int(t.get("cached_input_tokens", 0)) + int(t.get("output_tokens", 0))
    return None


def _name_times(name):
    """(as UTC, as local time) epoch seconds of a rollout name's start stamp, or () if unparsable."""
    try:
        dt = datetime.strptime(name[len("rollout-"):len("rollout-") + 19], "%Y-%m-%dT%H-%M-%S")
    except ValueError:
        return ()
    return dt.replace(tzinfo=timezone.utc).timestamp(), time.mktime(dt.timetuple())


def find_rollout(root, lane, sessions=SESSIONS):
    """The codex rollout file of a launched lane (cached in <lane>/rollout.txt), or None."""
    d = lane_dir(root, lane)
    cache = d / "rollout.txt"
    try:
        p = Path(cache.read_text().strip())
        if p.is_file():
            return p
    except OSError:
        pass
    start = lane_start(root, lane)
    if start is None:
        return None
    needle = str(d.resolve())
    days = {datetime.fromtimestamp(t, timezone.utc).strftime("%Y/%m/%d") for t in (start, time.time())}
    days |= {datetime.fromtimestamp(t).strftime("%Y/%m/%d") for t in (start, time.time())}
    for day in sorted(days):
        dd = Path(sessions) / day
        if not dd.is_dir():
            continue
        for e in os.scandir(dd):                       # one day directory, not a recursive search
            if not e.name.startswith("rollout-") or e.stat().st_mtime < start - 5:
                continue
            born = _name_times(e.name)                 # rollout-2026-09-23T06-04-28-<id>.jsonl
            if born and not any(start - 120 <= b <= start + 1800 for b in born):
                continue
            try:
                with open(e.path, "rb") as fh:
                    head = fh.read(262144).decode("utf-8", "replace")   # the prompt follows ~100 KB of instructions
            except OSError:
                continue
            if needle in head:
                try:
                    cache.write_text(e.path + "\n")
                except OSError:
                    pass
                return Path(e.path)
    return None


def live_tokens(root, lane, sessions=SESSIONS):
    p = find_rollout(root, lane, sessions)
    return _rollout_tokens(p) if p else None


def kill_lane(pid):
    """SIGTERM the lane's process group when it leads one (launch_lane.sh uses setsid), else the pid."""
    try:
        if os.getpgid(pid) == pid:
            os.killpg(pid, signal.SIGTERM)
        else:
            os.kill(pid, signal.SIGTERM)
        return True
    except OSError:
        return False


def write_cap(root, lane, what, figure, limit):
    rec = {"cap": what, "figure": figure, "limit": limit,
           "at": datetime.now(timezone.utc).strftime("%Y-%m-%dT%H:%M:%SZ")}
    (lane_dir(root, lane) / "cap.txt").write_text(json.dumps(rec) + "\n")
    return rec


def check(root, lane, pid, token_cap=0, wall_cap=0, now=None, sessions=SESSIONS, tokens_fn=None):
    """None, or the cap record after killing the lane.  tokens_fn(root, lane) -> live tokens (tests)."""
    now = time.time() if now is None else now
    if wall_cap and over_wall(lane_start(root, lane), now, wall_cap):
        kill_lane(pid)
        return write_cap(root, lane, "wall", round((now - lane_start(root, lane)) / 60, 1), wall_cap)
    if token_cap:
        tok = (tokens_fn or (lambda r, l: live_tokens(r, l, sessions)))(root, lane)
        if tok is not None and tok > token_cap:
            kill_lane(pid)
            return write_cap(root, lane, "tokens", tok, token_cap)
    return None


# ---------------------------------------------------------------- the band stop rule

def lane_band(root, lane):
    """served.band_of(the largest live pin count among the lane's base rows), or None."""
    from served import band_of
    sys.path.insert(0, str(Path(root) / "tools"))
    from pin_census import sites_of
    ks = [len(sites_of(f.read_text(errors="replace"))) for f in lane_dir(root, lane).glob("base/*/*.c")]
    return band_of(max(ks)) if ks else None


def band_stop(history, window, threshold, weight):
    """(stop?, pins per weighted unit or None, reason).  history: [{pins_removed, tokens, estimated}] of ONE
    band's finished lanes, oldest first."""
    if not window or not threshold:
        return False, None, "off"
    if weight is None:
        return False, None, "no weight for this model (TODO in config/model_cost_weights.json): never stops"
    last = history[-window:]
    if len(last) < window:
        return False, None, "%d of %d lanes finished" % (len(last), window)
    meas = [h for h in last if h.get("tokens") is not None and not h.get("estimated")]
    if not meas:
        return False, None, "no measured tokens"
    cost = sum(h["tokens"] for h in meas) * weight / 1e6
    rate = sum(h["pins_removed"] for h in meas) / cost if cost else None
    if rate is None:
        return False, None, "zero cost"
    return rate < threshold, round(rate, 3), "%.3f pins per weighted unit over the last %d lanes (threshold %g)" % (
        rate, len(meas), threshold)


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    ap.add_argument("cmd", choices=("watch", "tokens"))
    ap.add_argument("lane")
    ap.add_argument("--tokens", type=int, default=0, help="token cap (codex figure)")
    ap.add_argument("--minutes", type=float, default=0, help="wall cap in minutes")
    ap.add_argument("--poll", type=int, default=60)
    ap.add_argument("--root", default=str(ROOT))
    a = ap.parse_args(argv)
    if a.cmd == "tokens":
        print(live_tokens(a.root, a.lane))
        return 0
    try:
        pid = int((lane_dir(a.root, a.lane) / "lane.pid").read_text().strip())
    except (OSError, ValueError):
        print("no lane.pid for", a.lane)
        return 1
    while True:
        try:
            os.kill(pid, 0)
        except OSError:
            return 0                                    # the lane exited on its own
        rec = check(a.root, a.lane, pid, a.tokens, a.minutes)
        if rec:
            print("capped", a.lane, json.dumps(rec), flush=True)
            return 0
        time.sleep(a.poll)


if __name__ == "__main__":
    sys.exit(main())
