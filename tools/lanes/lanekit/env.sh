# Source this from a lane directory, ONCE, before anything else:
#
#     cd work/native_lane/<lane>
#     source <REPO>/tools/lanes/lanekit/env.sh
#
# It does four things, and then `lab`, `erase` and `why` are commands:
#
#   LANEKIT_LANE   this directory - every kit tool writes here and nowhere else
#   PYTHONPATH     the kit first (so `sitecustomize.py` is auto-imported by every python,
#                  including the ones the scorer starts), then the lane
#   TMPDIR         <lane>/tmp - every shared tool compiles inside a TemporaryDirectory, so this
#                  is what puts every `gcc -da` dump inside the lane BY CONSTRUCTION
#   PYTHONDONTWRITEBYTECODE   no __pycache__ scattered through the repository
#
# Sourcing is optional: each tool calls kitlib.bootstrap() and sets the same things for itself.
# Source it anyway - it also covers the shell commands you run by hand.

LANEKIT="$( cd "$( dirname "${BASH_SOURCE[0]:-$0}" )" && pwd )"
LANEKIT_REPO="$( cd "$LANEKIT/../../.." && pwd )"
LANEKIT_LANE="$( pwd )"

if [ "$LANEKIT_LANE" = "$LANEKIT_REPO" ]; then
    echo "lanekit: source this from inside a lane directory, not from the repository root" >&2
else
    export LANEKIT LANEKIT_REPO LANEKIT_LANE
    export PYTHONPATH="$LANEKIT:$LANEKIT_LANE${PYTHONPATH:+:$PYTHONPATH}"
    export TMPDIR="$LANEKIT_LANE/tmp"
    export PYTHONDONTWRITEBYTECODE=1
    mkdir -p "$TMPDIR"

    lab()   { python3 "$LANEKIT/lab.py"   "$@"; }
    erase() { python3 "$LANEKIT/erase.py" "$@"; }
    why()   { python3 "$LANEKIT/why.py"   "$@"; }

    echo "lanekit: lane $LANEKIT_LANE   (lab / erase / why are now commands; see $LANEKIT/README.md)"
fi
