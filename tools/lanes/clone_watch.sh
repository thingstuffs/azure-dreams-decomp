#!/bin/bash
# Clone-transfer watcher:  nohup bash tools/lanes/clone_watch.sh > clone_watch.log 2>&1 &
#
#   Every CW_INTERVAL seconds: replay every finished model lane's base->out edit on its still-pinned
#   CLONE SIBLINGS (tools/lanes/clone_transfer.py), and land whatever came out byte-exact in the next
#   codex gap (tools/lanes/land_gap.sh, so it queues behind any other lander instead of racing it).
#   A model lane solves one member of a clone family; the siblings stay pinned until someone ports
#   the same move with their identifiers, and this is that someone, once an hour, for free.
#
#   Each pass is its own lane, work/native_lane/<CW_LANE_PREFIX><n>; a pass with no candidate removes
#   its lane directory again.  Sentinel CLONE_WATCH_END.
#
# Environment
#   CW_INTERVAL   seconds between passes (default 1500)
#   CW_WORKERS    clone_transfer workers (default 4)
#   CW_PASSES     stop after N passes (default 0 = until stopped)
#   CW_UNTIL      "FILE:TOKEN" - after TOKEN appears in FILE, run ONE more pass and stop (the way the
#                 round-67 watcher followed the astra chain's own sentinel)
#   CW_STOP       stop file; when it exists the watcher finishes the current pass and exits
#                 (default build_ovl/work/clone_watch.stop) - the way to stop it without pkill
#   CW_LANES      lane list for clone_transfer --lanes (default: every finished r5*/r6* model lane
#                 with base/, out/ and last_message.txt, minus the clone, _arms, _check and _base
#                 directories)
#   CW_LANE_PREFIX  lane name prefix for the passes (default r68_clone_w)
#   CW_ROOT       repo root (default: this script's ../..)
#
# Moved out of the session scratchpad in round 68.  Never wait on a pattern: the self-match trap is
# documented in tools/lanes/land_gap.sh - this script waits only through land_gap.sh's own check.
set -u
cd "${CW_ROOT:-$(dirname "$0")/../..}"
INTERVAL=${CW_INTERVAL:-1500}
WORKERS=${CW_WORKERS:-4}
PASSES=${CW_PASSES:-0}
PREFIX=${CW_LANE_PREFIX:-r68_clone_w}
STOP=${CW_STOP:-build_ovl/work/clone_watch.stop}

lane_list() {
  if [ -n "${CW_LANES:-}" ]; then echo "$CW_LANES"; return; fi
  for d in work/native_lane/r5[0-9]_* work/native_lane/r6[0-9]_*; do
    b=$(basename "$d")
    case $b in ${PREFIX}*|*_arms|*_check*|*_base) continue;; esac
    [ -d "$d/base" ] && [ -d "$d/out" ] && [ -f "$d/last_message.txt" ] && printf '%s,' "$b"
  done
}

n=0; last=0
while true; do
  n=$((n + 1)); L=${PREFIX}${n}
  LANES=$(lane_list); LANES=${LANES%,}
  echo "== pass $n: $L over $(echo "$LANES" | tr ',' '\n' | grep -c .) lanes $(date -u +%FT%TZ)"
  python3 tools/lanes/clone_transfer.py --lane "$L" --lanes "$LANES" --workers "$WORKERS" 2>&1 | tail -2
  if ls work/native_lane/$L/out/*/*.c >/dev/null 2>&1; then
    bash tools/lanes/land_gap.sh "${L//_/}" "$L"
  else
    echo "== $L: nothing new $(date -u +%FT%TZ)"; rm -rf work/native_lane/$L
  fi
  [ "$last" = 1 ] && break
  [ -f "$STOP" ] && { echo "== stop file $STOP"; break; }
  [ "$PASSES" != 0 ] && [ "$n" -ge "$PASSES" ] && break
  if [ -n "${CW_UNTIL:-}" ]; then
    F=${CW_UNTIL%%:*}; T=${CW_UNTIL#*:}
    grep -q "$T" "$F" 2>/dev/null && { echo "== $T seen in $F: one last pass"; last=1; }
  fi
  [ "$last" = 1 ] || sleep "$INTERVAL"
done
echo CLONE_WATCH_END
