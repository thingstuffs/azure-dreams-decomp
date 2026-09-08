#!/usr/bin/env python3
"""Campaign controller: run the Layer-2 lane over a list of tiers, one agent_task launch at a time, commit each launch's
output, relaunch the same tier while it still prints rows, back off on quota, then move to the next tier.

    python3 tools/campaign.py --plan work/campaign_plan.json [--dry-run]

plan.json: {"model": "gpt-6-astra", "effort": "high", "workers": 3, "limit": 900,
            "tiers": [{"min": 0, "max": 100, "mode": "readability", "batch": 10}, {"min": 100, "max": 1000, "mode": "full"}],
            "reserve": [{"rows_file": "work/evidence_rows.txt", "mode": "readability", "batch": 10}]}
Each launch: `agent_task.py --all --min-size A --max-size B --workers W --limit L --commit --tag campaign [--mode M --batch N]`.
State: work/campaign_state.json (tier index, launch count, last outcome); PID of the running launch in work/campaign.pid.
Stop it by killing this controller's PID (work/campaign_controller.pid); the running launch finishes its in-flight rows.
Quota: agent_task stops itself after three consecutive quota failures and prints QUOTA; the controller waits `quota_wait_s`
(default 3600) and relaunches the same tier. Commits: `git add ledger/agents ledger/promotions.jsonl src && git commit`.
"""
import argparse, json, os, subprocess, sys, time
from pathlib import Path
sys.path.insert(0, str(Path(__file__).resolve().parent))
from common import ROOT

WORK = ROOT / "work"
def log(msg):
    line = f"{time.strftime('%Y-%m-%dT%H:%M:%SZ', time.gmtime())} {msg}"
    print(line, flush=True)
    with (WORK / "campaign_controller.log").open("a") as f: f.write(line + "\n")

def commit(msg):
    r = subprocess.run(["git", "add", "ledger/agents", "ledger/promotions.jsonl", "src"], cwd=ROOT, capture_output=True, text=True)
    r = subprocess.run(["git", "commit", "-q", "-m", msg], cwd=ROOT, capture_output=True, text=True)
    if r.returncode == 0:
        subprocess.run(["git", "push", "-q"], cwd=ROOT, capture_output=True, text=True); log("committed: " + msg[:80])
    else:
        out = r.stdout + r.stderr
        log("nothing to commit" if ("nothing to commit" in out or "nothing added to commit" in out) else "commit failed: " + out[-200:])

def launch(plan, tier, n, dry_run):
    cmd = [sys.executable, str(ROOT / "tools/agent_task.py"), "--model", plan["model"], "--effort", plan.get("effort", "high"),
           "--workers", str(plan.get("workers", 3)), "--limit", str(plan.get("limit", 900)), "--commit", "--tag", "campaign"]
    if "rows_file" in tier:
        ids = ",".join(Path(ROOT / tier["rows_file"]).read_text().split()); cmd += ["--rows", ids]
    else:
        cmd += ["--all", "--min-size", str(tier["min"]), "--max-size", str(tier["max"])]
    if tier.get("mode"): cmd += ["--mode", tier["mode"]]
    if tier.get("batch"): cmd += ["--batch", str(tier["batch"])]
    logf = WORK / f"astra_campaign_c{n:03d}.log"
    log(f"launch {n}: {' '.join(cmd[2:])} -> {logf.name}")
    if dry_run: return "dry"
    with logf.open("w") as f:
        p = subprocess.Popen(cmd, cwd=ROOT, stdout=f, stderr=subprocess.STDOUT, stdin=subprocess.DEVNULL, start_new_session=True)
    (WORK / "campaign.pid").write_text(str(p.pid))
    p.wait(); (WORK / "campaign.pid").unlink(missing_ok=True)
    text = logf.read_text(errors="replace")
    if "QUOTA" in text: return "quota"
    import re
    m = re.search(r"^(\d+) rows in \d+ unit", text, re.M) or re.search(r"^(\d+) rows,", text, re.M)
    served = text.count('"outcome"')
    if (m and int(m.group(1)) == 0) or served == 0: return "empty"   # nothing to serve (a 'rows skipped' notice may precede the count)
    return "done"

def main():
    ap = argparse.ArgumentParser(); ap.add_argument("--plan", required=True); ap.add_argument("--dry-run", action="store_true")
    ap.add_argument("--quota-wait", type=int, default=3600)
    a = ap.parse_args()
    plan = json.loads(Path(a.plan).read_text()); tiers = plan["tiers"] + plan.get("reserve", [])
    state_p = WORK / "campaign_state.json"
    state = json.loads(state_p.read_text()) if state_p.exists() else {"tier": 0, "launch": 0}
    (WORK / "campaign_controller.pid").write_text(str(os.getpid()))
    while state["tier"] < len(tiers):
        tier = tiers[state["tier"]]; state["launch"] += 1; state_p.write_text(json.dumps(state))
        res = launch(plan, tier, state["launch"], a.dry_run)
        log(f"launch {state['launch']} -> {res}")
        if a.dry_run: state["tier"] += 1; continue
        commit(f"campaign: launch {state['launch']} tier {tier.get('min', 'rows')}-{tier.get('max', '')} {tier.get('mode', 'full')} ({res})")
        if res == "quota":
            log(f"quota: waiting {a.quota_wait}s"); time.sleep(a.quota_wait)
        elif res == "empty" or "rows_file" in tier:
            state["tier"] += 1
        state.setdefault("same_tier", 0)
        state["same_tier"] = 0 if res in ("empty",) or "rows_file" in tier else state["same_tier"] + 1
        if state["same_tier"] > 12:   # a tier that keeps returning 'done' without emptying is a harness fault, not progress
            log("stopping: the same tier relaunched 12 times without emptying"); break
        state_p.write_text(json.dumps(state))
    log("plan complete"); (WORK / "campaign_controller.pid").unlink(missing_ok=True)

if __name__ == "__main__":
    main()
