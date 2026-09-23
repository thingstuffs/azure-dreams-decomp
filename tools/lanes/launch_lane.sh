#!/bin/bash
# Launch a codex lane:  bash tools/lanes/launch_lane.sh <lane directory name under work/native_lane> [luna|sol|luna6|sol6|astra|agy]
# luna/sol = gpt-5.6-luna/-sol, luna6/sol6 = gpt-6-luna/-sol (cheaper than astra; A/B them with tools/lanes/ab_report.py).
# Lanes escalate luna -> sol -> astra (astra sparingly: docs/LANE_KIT.md). Only when no gate or publish will run
# while it scores (verify.py scores inside build_ovl, which mk_ovl_root.sh replaces); sweeps must skip its rows.
# The PID goes to work/native_lane/<lane>/lane.pid: wait on it with kill -0 (or the Monitor tool), never with
# pgrep -f on a pattern your own command line contains. Moved from the session scratchpad in round 24.
# Round 76: codex runs under setsid (pid == its process group, so a cap can kill the lane's whole tree), and two
# OPTIONAL runaway caps start tools/lanes/lane_cap.py watch beside it: LANE_TOKEN_CAP=<codex tokens> (read live from
# the codex session rollout) and LANE_WALL_CAP=<minutes>. A capped lane is killed and gets cap.txt (status `cap`).
set -u
cd "$(dirname "$0")/../.."
N=${1:?lane name}; D=work/native_lane/$N
case "${2:-luna}" in astra) M=gpt-6-astra;; luna) M=gpt-5.6-luna;; sol) M=gpt-5.6-sol;;
  luna6) M=gpt-6-luna;; sol6) M=gpt-6-sol;;
  agy) M=${AGY_MODEL:-gemini-3.8-flash-high};; *) echo "model? luna|sol|luna6|sol6|astra|agy"; exit 1;; esac
[ -f $D/BRIEF.md ] && [ -f $D/PROMPT.txt ] || { echo "pack incomplete: $D needs BRIEF.md and PROMPT.txt"; exit 1; }
[ -f $D/last_message.txt ] && { echo "$D already ran (last_message.txt exists)"; exit 1; }
if [ "$2" = agy ]; then
  # Google Antigravity CLI (round 25): print mode with edit permission, the prompt on the command line, the
  # repo as the workspace; the brief is read by the model from the lane directory as codex does.
  nohup setsid bash -c "agy --print \"\$(cat $D/PROMPT.txt)\" --model $M --mode accept-edits --print-timeout ${AGY_TIMEOUT:-90m} \
      --dangerously-skip-permissions > $D/agy.out 2> $D/agy.log; mv -f $D/agy.out $D/last_message.txt" > /dev/null 2>&1 &
  # (round 76) stdout goes to agy.out and becomes last_message.txt only at exit: a last_message.txt that exists
  # from the launch made every running agy lane look finished to pool.py, ab_report.py and land_finished2.
else
  nohup setsid codex exec -C "$PWD" --dangerously-bypass-approvals-and-sandbox --skip-git-repo-check -m $M \
      -c 'model_reasoning_effort="xhigh"' -o $D/last_message.txt < $D/PROMPT.txt > $D/codex.log 2>&1 &
fi
echo $! > $D/lane.pid
echo "lane $N model $M pid $(cat $D/lane.pid) started $(date -u +%H:%M)"
if [ "${LANE_TOKEN_CAP:-0}" != 0 ] || [ "${LANE_WALL_CAP:-0}" != 0 ]; then
  nohup python3 tools/lanes/lane_cap.py watch "$N" --tokens "${LANE_TOKEN_CAP:-0}" --minutes "${LANE_WALL_CAP:-0}" \
      > $D/cap_watch.log 2>&1 &
  echo "cap watch: tokens ${LANE_TOKEN_CAP:-0} wall ${LANE_WALL_CAP:-0} min (pid $!)"
fi
