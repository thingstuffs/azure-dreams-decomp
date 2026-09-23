#!/usr/bin/env python3
"""Run a POOL of codex lanes concurrently and land them in ONE transaction when the pool drains.

    python3 tools/lanes/pool.py <name> --model sol --concurrency 3 --lanes r68_sol_big1,r68_sol_big2
    python3 tools/lanes/pool.py big --model astra --concurrency 2 --rows-json rows.json \\
            --paragraphs big_rows,new_findings --exemplars 6 --dry-run
    nohup python3 tools/lanes/pool.py big --model sol -c 3 --rows-json rows.json > pool_big.log 2>&1 &

Why a tool (round 68).  Rounds 59-67 ran this as `codex59f.sh ... codex59m.sh`, `pool.sh`,
`astra_loop.sh`, `land_item.sh` - a new copy in the session scratchpad every few hours, each with its
own capacity probe, its own EXTRA_T list and its own landing loop, all lost when the session ended.
This is that shape once: build the packs, probe, launch up to N at a time, wait on OUR OWN PIDs,
journal each lane's candidate count, land every winner together through tools/lanes/land_gap.sh.

The pool
  --lanes A,B,C          lanes to run, in order.  A lane that already has last_message.txt is skipped
                         (it ran); a lane without PROMPT.txt is BUILT first when --rows-json has it.
  --rows-json FILE       {"lane": ["container/func_...", ...]} - build_class_pack.py --rows --duck
                         builds each missing lane from its row list, with --classes/--exemplars/
                         --paragraphs.  With no --lanes, every key of the file is the lane list.
  --concurrency N        lanes in flight.  Per pool: two pools launched separately both run N.
  --model KEY            astra|sol|luna|sol6|luna6: model for every lane of the pool (launch_lane.sh holds
                         the canonical ids; sol6/luna6 = gpt-6-sol/-luna, compare with tools/lanes/ab_report.py).
  --served-guard G       tier (default) | ever | off: the served guard the pool passes to the builders (round 76,
                         tools/lanes/served.py): `tier` refuses only rows a launched lane of the pool's model tier
                         already served at the same text; a refused build skips that lane.
  --kit                  after build_class_pack.py builds a lane, run tools/lanes/kit_pack.py on it (v2 brief +
                         lane kit), with the pool's --paragraphs.  Only lanes the pool builds; a built pack is
                         never re-kitted.

Waiting
  --wait-for-sentinel F:TOKEN   wait until TOKEN appears in file F (chain the pool after another one)
  --wait-for-pid PID            wait until that process exits
  --poll SECONDS                how often anything is re-checked (default 60)

Capacity
  A one-word `codex exec` probe before each launch (the way a lane is found to be rate-limited
  without burning the pack).  --probe-retries R x --probe-wait S before the pool gives up launching.
  Every finished lane appends one line to ledger/model_capacity.jsonl: pack, model, candidates.
  --stop-after-zero N stops launching after N consecutive FINISHED lanes produced no candidate
  (round 63's rule; meaningful at --concurrency 1, advisory above it).

Landing
  At drain, every lane with a candidate goes to tools/lanes/land_gap.sh <tag> <lane>... : one wait
  for a codex gap, one landing transaction, the cascade from tools/lanes/cascade_extra.txt, then the
  arm_restore twins.  --no-land leaves the candidates staged.

THE SELF-MATCH TRAP.  This tool waits on PIDs it launched (`os.kill(pid, 0)`), never on a pattern.
`pgrep -f`/`pkill -f` match the whole command line of every process, including this one and the
`bash -c "... > pool_sweep.py.log"` wrapper that started it - a `while pgrep -f sweep.py` loop inside
its own shell never exits, and a `pkill -f codex` from the orchestrator's shell kills the
orchestrator (three lost shells on 2026-09-19/21).  The only pattern matching here is the bracket
trick for FOREIGN processes (`[g]ate_all.py` ...), and it is read-only.
"""
from __future__ import annotations

import argparse
import json
import os
import subprocess
import sys
import time
from datetime import datetime, timezone
from pathlib import Path

ROOT = next(p for p in Path(__file__).resolve().parents if (p / "tools/common.py").is_file())

# launch_lane.sh is canonical for these ids; repeated here only for the capacity probe.
MODELS = {"astra": "gpt-6-astra", "sol": "gpt-5.6-sol", "luna": "gpt-5.6-luna",
          "sol6": "gpt-6-sol", "luna6": "gpt-6-luna"}
# the served-guard tier of each model key (tools/lanes/served.py, ledger.tier_of_model)
TIER_OF = {"astra": "astra", "sol": "sol", "luna": "luna", "sol6": "sol6", "luna6": "luna6"}
CAPACITY = "ledger/model_capacity.jsonl"
DEFAULT_CLASSES = "CHANGED|17-32,BOTH|17-32,CHANGED|3-4,MOVED|1-2"

# Foreign processes that must not overlap a lane: verify.py scores inside build_ovl, which
# mk_ovl_root.sh replaces under it (launch_lane.sh's rule).  Bracket trick: see the docstring.
BUSY_PAT = "[g]ate_all.py|[a]pply_candidates.py|[m]k_ovl_root.sh|[b]uild_slus.sh|[l]and_lanes.sh"


def utc():
    return datetime.now(timezone.utc).strftime("%Y-%m-%dT%H:%M:%SZ")


def log(msg):
    print("%s %s" % (utc(), msg), flush=True)


# ---------------------------------------------------------------- planning (pure, unit tested)

def lane_pid(root, lane):
    """The pid launch_lane.sh recorded for the lane, when that process is still alive.

    A lane left running by an earlier pool (or by hand) is ADOPTED: never launched again, but waited
    on and landed with the pool.  Pid reuse is possible in principle; in practice lane.pid is minutes
    old and the alternative - launching a second codex on the same pack - costs a pack and a model
    hour."""
    try:
        pid = int((Path(root) / "work/native_lane" / lane / "lane.pid").read_text().strip())
    except (OSError, ValueError):
        return None
    return pid if alive(pid) else None


def lane_state(root, lane):
    """'ran' (last_message.txt), 'running' (a live lane.pid), 'built' (pack, never launched),
    or 'missing'."""
    d = Path(root) / "work/native_lane" / lane
    if (d / "last_message.txt").exists():
        return "ran"
    if lane_pid(root, lane) is not None:
        return "running"
    if (d / "PROMPT.txt").exists() and (d / "BRIEF.md").exists():
        return "built"
    return "missing"


def candidates(root, lane):
    """How many byte-exact candidates the lane staged (out/<container>/<name>.c)."""
    out = Path(root) / "work/native_lane" / lane / "out"
    if not out.is_dir():
        return 0
    n = 0
    for c in os.scandir(out):
        if c.is_dir():
            n += sum(1 for f in os.scandir(c.path) if f.name.endswith(".c"))
    return n


def plan(root, lanes, rows_json=None, classes=DEFAULT_CLASSES, exemplars=6, paragraphs=(),
         pins="1-2", npack=5, kit=False, served_guard="off", tier=None):
    """[{lane, action, rows, build, kit}] - what the pool would do, without doing any of it.
    kit: the kit_pack.py command run after a successful build (only with kit=True and action build+run).

    action: 'skip' (already ran), 'run' (pack is built), 'build+run' (pack must be built first),
    'no-rows' (nothing to build it from)."""
    rows_map = {}
    if rows_json:
        rows_map = json.loads(Path(rows_json).read_text())
    if lanes is None:
        lanes = list(rows_map)
    steps = []
    for lane in lanes:
        st = lane_state(root, lane)
        ids = list(rows_map.get(lane, []))
        kitcmd = None
        if st == "ran":
            action, build = "skip", None
        elif st == "running":
            action, build = "adopt", None
        elif st == "built":
            action, build = "run", None
        elif ids:
            action = "build+run"
            build = ["python3", "tools/lanes/build_class_pack.py", lane, classes, str(npack),
                     "--pins", pins, "--rows", ",".join(ids), "--duck"]
            if exemplars:
                build += ["--exemplars", str(exemplars)]
            if paragraphs:
                build += ["--paragraphs", ",".join(paragraphs)]
            if served_guard != "off":
                build += ["--served-guard", served_guard] + (["--tier", tier] if tier else [])
            if kit:
                kitcmd = ["python3", "tools/lanes/kit_pack.py", lane]
                if paragraphs:
                    kitcmd += ["--paragraphs", ",".join(paragraphs)]
                if served_guard == "tier" and tier:
                    kitcmd += ["--tier", tier]
        else:
            action, build = "no-rows", None
        steps.append({"lane": lane, "action": action, "rows": len(ids), "build": build,
                      "kit": kitcmd, "candidates": candidates(root, lane)})
    return steps


def plan_text(name, model, concurrency, steps, tag, land=True):
    out = ["pool %s: model %s, concurrency %d, %d lane(s)" % (name, MODELS.get(model, model), concurrency, len(steps))]
    for s in steps:
        out.append("  %-28s %-9s rows %-3d %s" % (s["lane"], s["action"], s["rows"],
                                                  s["build"] and " ".join(s["build"][2:]) or ""))
        if s.get("kit"):
            out.append("  %-28s then %s" % ("", " ".join(s["kit"][1:])))
    runnable = [s["lane"] for s in steps if s["action"] in ("run", "build+run")]
    adopted = [s["lane"] for s in steps if s["action"] == "adopt"]
    out.append("  would launch: %s" % (", ".join(runnable) or "(nothing)"))
    if adopted:
        out.append("  already running, adopted (waited on and landed, not relaunched): %s" % ", ".join(adopted))
    if land:
        out.append("  at drain: bash tools/lanes/land_gap.sh pool%s <lanes with candidates>  (+ _arms twins)" % tag)
    else:
        out.append("  at drain: --no-land, candidates left staged")
    out.append("POOL_%s_END" % name)
    return "\n".join(out)


# ---------------------------------------------------------------- running

def probe(model_id, timeout=300):
    """One cheap codex call: is there capacity for this model right now?"""
    try:
        p = subprocess.run(["timeout", str(timeout), "codex", "exec", "-C", str(ROOT),
                            "--skip-git-repo-check", "-m", model_id,
                            "-c", 'model_reasoning_effort="low"', "Reply with the single word OK"],
                           capture_output=True, text=True)
    except Exception as e:                                      # codex missing: the pool stops, it does not crash
        log("probe failed: %r" % (e,))
        return False
    return "OK" in "\n".join(p.stdout.splitlines()[-3:])


def alive(pid):
    try:
        os.kill(pid, 0)
    except OSError:
        return False
    return True


def foreign_busy():
    # isolated landings (LAND_ISOLATED=1, round 68) gate in their own root: a landing no longer holds lane launches
    if os.environ.get("LAND_ISOLATED") == "1":
        return False
    return subprocess.run(["pgrep", "-f", BUSY_PAT], capture_output=True).returncode == 0


def wait_sentinel(spec, poll):
    path, _, token = spec.partition(":")
    log("waiting for %r in %s" % (token, path))
    while True:
        try:
            if token in Path(path).read_text(errors="replace"):
                return
        except OSError:
            pass
        time.sleep(poll)


def journal(root, lane, model_id, n, note):
    rec = {"date": datetime.now(timezone.utc).strftime("%Y-%m-%dT%H:%MZ"),
           "codex": {"pack": lane, "model": model_id, "candidates": n}, "note": note}
    with (Path(root) / CAPACITY).open("a") as fh:
        fh.write(json.dumps(rec) + "\n")


def run(args):
    root = Path(args.root)
    model_id = MODELS.get(args.model, args.model)
    steps = plan(root, args.lanes, args.rows_json, args.classes, args.exemplars,
                 args.paragraphs, args.pins, args.pack_rows, args.kit, args.served_guard, TIER_OF.get(args.model))
    tag = args.tag or args.name
    if args.dry_run:
        print(plan_text(args.name, args.model, args.concurrency, steps, tag, not args.no_land))
        return 0
    if args.wait_for_sentinel:
        wait_sentinel(args.wait_for_sentinel, args.poll)
    if args.wait_for_pid:
        log("waiting for pid %d" % args.wait_for_pid)
        while alive(args.wait_for_pid):
            time.sleep(args.poll)

    started = []                                                # [(lane, pid)] - ours, never a pattern
    zero_streak = 0
    finished = set()

    def running():
        return [(l, p) for l, p in started if alive(p) and l not in finished]

    def reap():
        nonlocal zero_streak
        for lane, pid in started:
            if lane in finished or alive(pid):
                continue
            finished.add(lane)
            n = candidates(root, lane)
            log("== %s exited, %d candidate(s)" % (lane, n))
            journal(root, lane, model_id, n, args.note)
            zero_streak = zero_streak + 1 if n == 0 else 0

    for s in steps:
        if s["action"] == "skip":
            log("== %s already ran, skipped" % s["lane"])
            continue
        if s["action"] == "no-rows":
            log("== %s has no pack and no rows, skipped" % s["lane"])
            continue
        if s["action"] == "adopt":
            pid = lane_pid(root, s["lane"])
            if pid is None:                                     # it exited between the plan and here
                log("== %s finished while the pool was planning" % s["lane"])
                continue
            log("== %s is already running (pid %d): adopted, not relaunched" % (s["lane"], pid))
            started.append((s["lane"], pid))
            continue
        if s["build"]:
            log("== build %s (%d rows)" % (s["lane"], s["rows"]))
            r = subprocess.run(s["build"], cwd=root, capture_output=True, text=True)
            print((r.stdout or "").strip()[-2000:], flush=True)
            if r.returncode != 0 or lane_state(root, s["lane"]) != "built":
                log("== %s: pack build failed, skipped\n%s" % (s["lane"], (r.stderr or "")[-2000:]))
                continue
        if s.get("kit"):
            log("== kit %s" % s["lane"])
            r = subprocess.run(s["kit"], cwd=root, capture_output=True, text=True)
            print((r.stdout or "").strip()[-2000:], flush=True)
            # kit_pack.py prints and skips (exit 0) on a lane it cannot kit: its "kit pack:" line is the proof
            if r.returncode != 0 or "kit pack:" not in (r.stdout or "") or lane_state(root, s["lane"]) != "built":
                log("== %s: kit_pack failed, skipped\n%s" % (s["lane"], (r.stderr or "")[-2000:]))
                continue
        while True:
            reap()
            if args.stop_after_zero and zero_streak >= args.stop_after_zero:
                log("== %d finished lanes in a row without a candidate: the pool stops launching"
                    % zero_streak)
                break
            if len(running()) < args.concurrency and not foreign_busy():
                break
            time.sleep(args.poll)
        if args.stop_after_zero and zero_streak >= args.stop_after_zero:
            break
        ok = False
        for attempt in range(1, args.probe_retries + 1):
            if probe(model_id):
                ok = True
                break
            log("no %s capacity before %s (attempt %d/%d); waiting %ds"
                % (args.model, s["lane"], attempt, args.probe_retries, args.probe_wait))
            time.sleep(args.probe_wait)
        if not ok:
            log("== no %s capacity; the pool stops launching" % args.model)
            break
        log("== launch %s on %s" % (s["lane"], args.model))
        r = subprocess.run(["bash", "tools/lanes/launch_lane.sh", s["lane"], args.model],
                           cwd=root, capture_output=True, text=True)
        print((r.stdout or r.stderr or "").strip(), flush=True)
        time.sleep(5)
        try:
            pid = int((root / "work/native_lane" / s["lane"] / "lane.pid").read_text().strip())
        except (OSError, ValueError):
            log("== %s: no lane.pid, not launched" % s["lane"])
            continue
        started.append((s["lane"], pid))
        time.sleep(args.launch_gap)

    while running():
        time.sleep(args.poll)
        reap()
    reap()
    log("== all lanes exited")

    winners = [l for l, _ in started if candidates(root, l) > 0]
    for lane, _ in started:
        log("%s candidates %d" % (lane, candidates(root, lane)))
    if winners and not args.no_land:
        cmd = ["bash", "tools/lanes/land_gap.sh", "pool" + tag] + winners
        log("== " + " ".join(cmd))
        subprocess.run(cmd, cwd=root)
    elif winners:
        log("== --no-land: %s left staged" % ", ".join(winners))
    else:
        log("== no candidates in this pool; nothing to land")
    print("POOL_%s_END" % args.name, flush=True)
    return 0


def parse(argv=None):
    ap = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    ap.add_argument("name", help="pool name; the sentinel is POOL_<name>_END")
    # only what launch_lane.sh accepts: a raw model id would probe fine and then fail every launch
    ap.add_argument("--model", default="sol", choices=sorted(MODELS))
    ap.add_argument("-c", "--concurrency", type=int, default=2)
    ap.add_argument("--lanes", type=lambda s: [x for x in s.replace(",", " ").split() if x])
    ap.add_argument("--rows-json", help='{"lane": ["container/func_...", ...]}')
    ap.add_argument("--classes", default=DEFAULT_CLASSES, help="class list passed to build_class_pack.py")
    ap.add_argument("--pins", default="1-2", help="pin band passed to build_class_pack.py (ignored with --rows)")
    ap.add_argument("--pack-rows", type=int, default=5, help="pack size passed to build_class_pack.py")
    ap.add_argument("--exemplars", type=int, default=6)
    ap.add_argument("--paragraphs", default="", type=lambda s: [x for x in s.replace(",", " ").split() if x],
                    help="tools/lanes/brief_paragraphs/<name>.md to append to each BRIEF.md")
    ap.add_argument("--kit", action="store_true",
                    help="run tools/lanes/kit_pack.py (with --paragraphs) on each lane the pool builds")
    ap.add_argument("--served-guard", default="tier", choices=("tier", "ever", "off"),
                    help="guard passed to build_class_pack.py/kit_pack.py for lanes the pool builds: tier (default) "
                         "refuses rows a lane of the SAME tier served at the SAME text; ever = any lane ever; off")
    ap.add_argument("--tag", help="landing tag (default: the pool name)")
    ap.add_argument("--no-land", action="store_true")
    ap.add_argument("--dry-run", action="store_true", help="print the plan and exit")
    ap.add_argument("--poll", type=int, default=60)
    ap.add_argument("--launch-gap", type=int, default=20, help="seconds between launches")
    ap.add_argument("--probe-retries", type=int, default=2)
    ap.add_argument("--probe-wait", type=int, default=1800)
    ap.add_argument("--stop-after-zero", type=int, default=0)
    ap.add_argument("--wait-for-sentinel", default="", help="FILE:TOKEN - start only once TOKEN appears in FILE")
    ap.add_argument("--wait-for-pid", type=int, default=0, help="start only once this pid has exited")
    ap.add_argument("--note", default="duck-briefed pool (tools/lanes/pool.py)")
    ap.add_argument("--root", default=str(ROOT))
    return ap.parse_args(argv)


if __name__ == "__main__":
    sys.exit(run(parse()))
