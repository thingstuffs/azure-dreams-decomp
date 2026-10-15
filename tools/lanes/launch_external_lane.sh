#!/bin/bash
# Launch a codex (or agy) lane in a private repo copy OUTSIDE the live checkout, so a live landing never waits for it
# (tools/lanes/land_packages.py --isolated treats a process as unrelated when its cwd, argv and descriptors all stay
# outside the live root; see docs in work/native_lane/_r120/busyfix/README.md).
#
#   bash tools/lanes/launch_external_lane.sh <lane> [luna|sol|luna6|sol6|sol61|daybreak|astra|agy|agyopus|agysonnet]
#
# Environment (all optional):
#   EXT_BASE     parent of the lane roots           (default: <live repo parent>/azure-lanes)
#   EXT_ROOT     the private root                   (default $EXT_BASE/<lane>/root)
#   EXT_SHA      commit the root is built from      (default: the live HEAD; ignored when EXT_ROOT already exists)
#   LANE_SRC     directory holding the lane pack    (default <live>/work/native_lane/<lane>); copied to
#                $EXT_ROOT/work/native_lane/<lane>, and any live-root absolute path in its top-level *.md/*.txt/*.json is
#                rewritten to $EXT_ROOT (packs are written with $PWD paths). An existing lane dir in the root is kept.
#   LANE_EFFORT, LANE_TOKEN_CAP, LANE_WALL_CAP, AGY_MODEL, AGY_TIMEOUT   passed through to launch_lane.sh unchanged
#
# The root is built by work/native_lane/_r113/mk_scratch_root.sh (git archive of a COMMITTED sha; toolchain, .venv and
# baserom are symlinks to the live repo and are read-only shared inputs). The launch itself is the root's OWN
# tools/lanes/launch_lane.sh (same model table, setsid, cap watcher from config/lane_caps.json), run with cwd = the root
# so every path it writes is inside the root. The lane's REPORT.md, out/ and last_message.txt stay there.
set -eu
LIVE=$(cd "$(dirname "$0")/../.." && pwd)
N=${1:?lane name}; MODEL=${2:-luna}
EXT_BASE=${EXT_BASE:-$(dirname "$LIVE")/azure-lanes}
R=${EXT_ROOT:-$EXT_BASE/$N/root}
case "$R" in "$LIVE"|"$LIVE"/*) echo "EXT_ROOT must be outside the live checkout ($LIVE)"; exit 1;; esac
case "$N" in */*|"") echo "lane name must be a bare directory name"; exit 1;; esac
if [ ! -e "$R/SCRATCH_HEAD" ]; then
  SHA=${EXT_SHA:-$(git -C "$LIVE" rev-parse HEAD)}
  SHA=$(git -C "$LIVE" rev-parse --verify "$SHA^{commit}")
  bash "${MK_SCRATCH_ROOT:-$LIVE/work/native_lane/_r113/mk_scratch_root.sh}" "$SHA" "$R" || exit 1
  [ -e "$R/SCRATCH_HEAD" ] || { echo "root build failed: $R"; exit 1; }
else
  echo "reusing root $R at $(cat "$R/SCRATCH_HEAD")"
fi
D=$R/work/native_lane/$N
if [ ! -d "$D" ]; then
  SRC=${LANE_SRC:-$LIVE/work/native_lane/$N}
  [ -d "$SRC" ] || { echo "no lane pack: $SRC (set LANE_SRC)"; exit 1; }
  mkdir -p "$R/work/native_lane"; cp -a "$SRC" "$D"
  for f in "$D"/*.md "$D"/*.txt "$D"/*.json; do
    [ -f "$f" ] && grep -q -F "$LIVE" "$f" && sed -i "s#$LIVE#$R#g" "$f"
  done
fi
[ -f "$D/BRIEF.md" ] && [ -f "$D/PROMPT.txt" ] || { echo "pack incomplete: $D needs BRIEF.md and PROMPT.txt"; exit 1; }
[ -x "$R/tools/lanes/launch_lane.sh" ] || [ -f "$R/tools/lanes/launch_lane.sh" ] || { echo "root has no launch_lane.sh (sha too old)"; exit 1; }
# cwd = the private root: launch_lane.sh cds there itself; codex then starts from the lane dir (r117), never the live root.
cd "$R" && exec bash "$R/tools/lanes/launch_lane.sh" "$N" "$MODEL"
