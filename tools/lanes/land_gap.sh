#!/bin/bash
# Land lanes in a codex GAP:  bash tools/lanes/land_gap.sh <tag> <lane>...
#
#   land_lanes.sh refuses to run while any `codex exec` lane or any sweep is running (it shares
#   build_ovl with verify.py, and a landing rewrites src/ under the lane's feet).  So every landing
#   of a lane whose siblings are still thinking has to WAIT for a gap.  Rounds 63-68 grew one
#   throw-away waiter per landing in the session scratchpad (land_r63.sh ... land_r68.sh, land_t91.sh,
#   land_t95.sh, the gapland() inside pool.sh, land_retry() inside codex59j.sh, the block inside
#   clone_watch.sh): all the same loop, each with its own poll interval and its own stale copy of the
#   EXTRA_T generator list.  This is that loop, once, with the list in tools/lanes/cascade_extra.txt.
#
# What it does
#   1. takes the gap-lander QUEUE lock (build_ovl/work/land_gap.lock) so two landers queue instead of
#      racing for the same gap and refusing each other (round 61's chain H lanes were refused under
#      contention and had to be re-landed by hand, with a scratchpad reland_watch.sh);
#   2. waits, up to GAP_MAX_WAIT seconds, for no `codex exec` and no landing/gate/sweep;
#   3. runs land_lanes.sh <tag> <lane>... with EXTRA_T from cascade_extra.txt;
#   4. arm_restore.py on every landed lane and, when a twin has candidates, lands the twins in the
#      next gap as <tag>a  (a model lane routinely flattens a NON_MATCHING arm, which the landing rule
#      refuses; the twin is the same candidate with the arm put back);
#   5. prints the STATUS.md pin line and the sentinel LAND_GAP_END <tag>.
#
# Environment
#   GAP_MAX_WAIT  seconds to wait for a gap, lock included (default 54000 = 15 h)
#   GAP_POLL      seconds between checks (default 60)
#   GAP_ARMS      0 to skip step 4 (default 1)
#   GAP_BUSY_CMD  command deciding "busy" (exit 0 = busy); default = the pgrep check below.  Used by
#                 tools/tests/test_land_gap.py, which must not consult the real machine.
#   EXTRA_T       overrides the cascade_extra.txt list (empty string = no extra generators)
#   LAND_GAP_ROOT repo root (default: this script's ../..)
#   LAND_ISOLATED 1 = land WITHOUT waiting for a gap (the gate runs in build_ovl_gate; passed
#                 through to land_lanes.sh, which queues on the land lock); default unset = today's
#                 behaviour, wait for a gap
#
# THE SELF-MATCH TRAP (three lost orchestrator shells, 2026-09-19/21).  `pgrep -f`/`pkill -f` match
# the WHOLE command line of every process - including the waiting shell itself, and including the
# wrapper `bash -c "... > some_sweep.py.log"` that started it, because the redirect is part of that
# wrapper's command line.  A waiter written as `while pgrep -f "sweep.py"; do sleep 5; done` never
# exits, and `pkill -f land_lanes.sh` from a shell whose own command line says land_lanes.sh kills
# itself.  Rules, obeyed here: (a) the bracket trick, "[s]weep.py", so the pattern cannot match the
# text of the pattern; (b) never name a log file after a process this script greps for; (c) wait on
# OUR OWN children by PID with `kill -0`, never by pattern (see tools/lanes/pool.py).
set -u
cd "${LAND_GAP_ROOT:-$(dirname "$0")/../..}"

TAG=${1:?usage: land_gap.sh <tag> <lane>...}; shift
LANES="$*"; [ -n "$LANES" ] || { echo "usage: land_gap.sh <tag> <lane>..."; exit 1; }
POLL=${GAP_POLL:-60}
MAXW=${GAP_MAX_WAIT:-54000}
if [ -z "${EXTRA_T+x}" ]; then
  EXTRA_T=$(grep -v '^[[:space:]]*#' tools/lanes/cascade_extra.txt 2>/dev/null | tr '\n' ' ')
fi
export EXTRA_T

busy() {
  if [ -n "${GAP_BUSY_CMD:-}" ]; then eval "$GAP_BUSY_CMD"; return $?; fi
  # LAND_ISOLATED=1: there is no gap to wait for.  land_lanes.sh gates in its own view root
  # (build_ovl_gate), so lanes keep scoring through the landing, and two landings queue on
  # build_ovl/work/land.lock instead of refusing each other (docs/LANE_KIT.md).
  [ "${LAND_ISOLATED:-0}" = 1 ] && return 1
  pgrep -f "[c]odex exec" >/dev/null && return 0
  pgrep -f "[l]and_lanes.sh|[g]ate_all.py|[a]pply_candidates.py|[s]weep.py " >/dev/null && return 0
  return 1
}

START=$(date +%s)
left() { echo $(( MAXW - ($(date +%s) - START) )); }

mkdir -p build_ovl/work
exec 9>build_ovl/work/land_gap.lock
if ! flock -w "$MAXW" 9; then
  echo "== $TAG: another gap lander held the queue for ${MAXW}s; giving up"; echo "LAND_GAP_END $TAG"; exit 3
fi

# land <tag> <lane>... : wait for a gap, then one landing transaction, RETRYING a refusal until the
# deadline.  land_lanes.sh does its own pgrep check after taking the land lock, so a codex lane that
# starts in the window between busy() and that check (or a sweep whose command line busy() does not
# match) makes it exit 1 with the lanes still staged - every scratchpad lander therefore wrote
# `land_lanes.sh ... && break` inside its wait loop, and so does this.
land() {
  local t=$1 rc=2; shift
  while [ "$(left)" -gt 0 ]; do
    if ! busy; then
      echo "== land $t $* $(date -u +%FT%TZ)"
      bash tools/lanes/land_lanes.sh "$t" "$@"; rc=$?
      [ $rc = 0 ] && return 0
      echo "== $t: land_lanes.sh refused (rc $rc); retrying in ${POLL}s"
    fi
    sleep "$POLL"
  done
  echo "== $t: no landing within ${MAXW}s (rc $rc); lanes still staged: $*"
  return $rc
}

land "$TAG" $LANES; RC=$?
grep -o "Pin sites now: [0-9,]* in [0-9,]* rows" STATUS.md 2>/dev/null

if [ "$RC" = 0 ] && [ "${GAP_ARMS:-1}" = 1 ]; then
  ARMS=""
  for L in $LANES; do
    python3 tools/lanes/arm_restore.py "$L" 2>&1 | tail -1
    ls work/native_lane/${L}_arms/out/*/*.c >/dev/null 2>&1 && ARMS="$ARMS ${L}_arms"
  done
  if [ -n "$ARMS" ]; then
    land "${TAG}a" $ARMS
    grep -o "Pin sites now: [0-9,]* in [0-9,]* rows" STATUS.md 2>/dev/null
  fi
fi
echo "LAND_GAP_END $TAG"
exit $RC
