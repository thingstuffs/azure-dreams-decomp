#!/bin/bash
# EXTEND arm of the cut-off experiment (tools/lanes/cutoff_report.py): resume a capped/cut codex lane's OWN
# session for a bounded increment, instead of a fresh-context continuation pack (the FRESH arm, CONTINUES.txt).
#   bash tools/lanes/extend_lane.sh <lane> <extra_tokens> <wall_minutes> "<reason: the concrete residual hypothesis>"
# Writes <lane>/extension.json BEFORE launch (arm, reason, lab trials and staged pins so far, the prior cap
# figure) so the report can split the lane's trials into before/after.  The previous cap.txt moves to
# cap_<n>.txt; the new token cap is the old session total + <extra_tokens> (a resumed session keeps counting
# in its rollout).  A lane is extended at most once without a new reason (plan: no automatic relaunch).
set -u
cd "$(dirname "$0")/../.."
N=${1:?lane}; EXTRA=${2:?extra tokens}; WALL=${3:?wall minutes}; WHY=${4:?reason}
D=work/native_lane/$N
[ -f $D/rollout.txt ] || { echo "no rollout.txt: not a codex lane the cap watcher tracked"; exit 1; }
[ -f $D/extension.json ] && { echo "$D was already extended once (extension.json)"; exit 1; }
P=$(cat $D/lane.pid 2>/dev/null); [ -n "$P" ] && kill -0 "$P" 2>/dev/null && { echo "lane still running"; exit 1; }
SID=$(basename "$(cat $D/rollout.txt)" .jsonl | grep -oE '[0-9a-f]{8}-[0-9a-f]{4}-[0-9a-f]{4}-[0-9a-f]{4}-[0-9a-f]{12}$')
[ -n "$SID" ] || { echo "cannot read the session id from rollout.txt"; exit 1; }
PRIOR=$(python3 tools/lanes/lane_cap.py tokens "$N" 2>/dev/null | grep -oE '[0-9]+' | tail -1); PRIOR=${PRIOR:-0}
MODEL=$(python3 -c "import sys; sys.path.insert(0,'tools/lanes'); import served; print(served.lane_model('$D') or '')")
python3 - "$D" "$WHY" "$EXTRA" "$WALL" "$PRIOR" "$MODEL" "$SID" <<'PY'
import sys, json, glob, os, datetime
sys.path.insert(0, 'tools'); from pin_census import sites_of
d, why, extra, wall, prior, model, sid = sys.argv[1:]
n = lambda f: sum(1 for s in sites_of(open(f, errors='replace').read()) if s[1].startswith('ASM_'))
staged = {'/'.join(f.split('/')[-2:])[:-2]: n(f) for f in glob.glob(d + '/out/*/*.c')}
trials = sum(1 for _ in open(d + '/lab_log.jsonl')) if os.path.exists(d + '/lab_log.jsonl') else 0
json.dump({'arm': 'extend', 'at': datetime.datetime.now(datetime.timezone.utc).strftime('%Y-%m-%dT%H:%M:%SZ'),
           'reason': why, 'extra_tokens': int(extra), 'wall_minutes': float(wall), 'prior_tokens': int(prior),
           'model': model, 'session': sid, 'lab_trials_before': trials, 'staged_before': staged,
           'ended_before': 'cap' if os.path.exists(d + '/cap.txt') else 'other'},
          open(d + '/extension.json', 'w'), indent=1)
PY
for i in 1 2 3 4 5; do [ -f $D/cap_$i.txt ] || { [ -f $D/cap.txt ] && mv $D/cap.txt $D/cap_$i.txt; break; }; done
[ -f $D/last_message.txt ] && mv $D/last_message.txt $D/last_message_before_extension.txt
PROMPT="You were stopped by the orchestrator's token cap, not because the work was done. Your lane directory, lab_log.jsonl and out/ are as you left them. $WHY
First stage anything byte-exact you have not staged (out/<container>/<name>.c with lab.py's .base_sha). Then continue only on rows where you have a concrete next discriminator; the same hard rules apply. You have about $EXTRA more tokens: at 80% of that, stop, stage, and write REPORT.md and the per-row lines as the brief asks."
cp $D/codex.log $D/codex_before_extension.log
nohup setsid codex exec resume "$SID" -m "${MODEL:-gpt-6-sol}" --dangerously-bypass-approvals-and-sandbox --skip-git-repo-check \
    -c 'model_reasoning_effort="xhigh"' -o $D/last_message.txt "$PROMPT" > $D/codex.log 2>&1 < /dev/null &
echo $! > $D/lane.pid
CAP=$((PRIOR + EXTRA))
nohup python3 tools/lanes/lane_cap.py watch "$N" --tokens "$CAP" --minutes "$WALL" > $D/cap_watch_ext.log 2>&1 &
echo "extended $N session $SID model ${MODEL:-?} pid $(cat $D/lane.pid); token cap $CAP (prior $PRIOR + $EXTRA), wall $WALL min"
