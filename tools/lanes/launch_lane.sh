#!/bin/bash
# Launch a codex lane:  bash tools/lanes/launch_lane.sh <lane directory name under work/native_lane> [luna|sol|astra]
# Lanes escalate luna -> sol -> astra (astra sparingly: docs/LANE_KIT.md). Only when no gate or publish will run
# while it scores (verify.py scores inside build_ovl, which mk_ovl_root.sh replaces); sweeps must skip its rows.
# The PID goes to work/native_lane/<lane>/lane.pid: wait on it with kill -0 (or the Monitor tool), never with
# pgrep -f on a pattern your own command line contains. Moved from the session scratchpad in round 24.
set -u
cd "$(dirname "$0")/../.."
N=${1:?lane name}; D=work/native_lane/$N
case "${2:-luna}" in astra) M=gpt-6-astra;; luna) M=gpt-5.6-luna;; sol) M=gpt-5.6-sol;; *) echo "model? luna|sol|astra"; exit 1;; esac
[ -f $D/BRIEF.md ] && [ -f $D/PROMPT.txt ] || { echo "pack incomplete: $D needs BRIEF.md and PROMPT.txt"; exit 1; }
[ -f $D/last_message.txt ] && { echo "$D already ran (last_message.txt exists)"; exit 1; }
nohup codex exec -C "$PWD" --dangerously-bypass-approvals-and-sandbox --skip-git-repo-check -m $M \
    -c 'model_reasoning_effort="xhigh"' -o $D/last_message.txt < $D/PROMPT.txt > $D/codex.log 2>&1 &
echo $! > $D/lane.pid
echo "lane $N model $M pid $(cat $D/lane.pid) started $(date -u +%H:%M)"
