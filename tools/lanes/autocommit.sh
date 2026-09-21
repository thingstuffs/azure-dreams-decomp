#!/bin/bash
# Snapshot committer:  nohup bash tools/lanes/autocommit.sh > autocommit.log 2>&1 &
#
#   A landing transaction (tools/lanes/land_lanes.sh) rewrites src/, STATUS.md and ledger/ and then
#   gates; the session that started it is usually asleep or busy elsewhere when it finishes, and a
#   round's worth of landings used to sit uncommitted until someone looked.  This commits them as
#   soon as it is SAFE to: no gate/apply/build process running and the landing lock free (land_lanes
#   holds build_ovl/work/land.lock from apply through gate and status), so a commit never captures a
#   half-applied tree.  Nothing else is committed: src, STATUS.md and ledger only, tracked files only.
#
#   It does not decide anything - it is the snapshot, not the review.  The session still reads the
#   gate output and writes the real commit message for anything it wants described.
#
# Environment
#   AC_INTERVAL   seconds between checks (default 600)
#   AC_PATHS      what to commit (default "src STATUS.md ledger")
#   AC_COAUTHOR   the Co-Authored-By line, e.g. "Claude Opus 5 (1M context) <noreply@anthropic.com>";
#                 empty (the default) writes no trailer.  The orchestrating session sets its own.
#   AC_ONCE       1 = one check, then exit (what the test and a manual catch-up use)
#   AC_ROOT       repo root (default: this script's ../..)
#
# Moved out of the session scratchpad in round 68 (it had run there since 2026-09-19).
# Never wait on a pattern: see the trap documented in tools/lanes/land_gap.sh.
set -u
cd "${AC_ROOT:-$(dirname "$0")/../..}"
INTERVAL=${AC_INTERVAL:-600}
PATHSPEC=${AC_PATHS:-"src STATUS.md ledger"}

commit_if_idle() {
  if pgrep -f "[g]ate_all.py|[a]pply_candidates.py|[m]k_ovl_root.sh|[b]uild_slus.sh|[l]and_lanes.sh" >/dev/null; then
    return 0
  fi
  flock -n build_ovl/work/land.lock true 2>/dev/null || return 0
  [ -n "$(git status --short -- $PATHSPEC | grep -v '^??')" ] || return 0
  P=$(grep -o "Pin sites now: [0-9,]* in [0-9,]* rows" STATUS.md)
  MSG="auto: landed lanes snapshot ($P; gates in the lane logs)"
  [ -n "${AC_COAUTHOR:-}" ] && MSG="$MSG

Co-Authored-By: $AC_COAUTHOR"
  git add $PATHSPEC && git commit -q -m "$MSG" && echo "$(date -u +%FT%TZ) committed: $P"
}

if [ "${AC_ONCE:-0}" = 1 ]; then commit_if_idle; exit 0; fi
while true; do
  sleep "$INTERVAL"
  commit_if_idle
done
