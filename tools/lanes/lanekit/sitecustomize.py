"""Auto-imported by every Python started with this directory (or the lane) on PYTHONPATH.

It installs the compiler-cwd shim (`lane_shim.install`) and points `tempfile` at `<lane>/tmp`, so a
`gcc -da` launched anywhere under this process writes its dumps inside the lane.  Outside a lane -
no `LANEKIT_LANE`, or a current directory that is the repository root - it does nothing at all.

`env.sh` in the lane sets `LANEKIT_LANE` and `PYTHONPATH`; `kitlib.bootstrap()` does the same for a
tool started without it.  Keep both: the lane's shell commands and the kit's Python entry points
must land in the same place.
"""
import os
import sys
import tempfile
from pathlib import Path

try:
    _lane = Path(os.environ.get("LANEKIT_LANE") or Path.cwd()).resolve()
    _here = Path(__file__).resolve().parent
    if str(_here) not in sys.path:
        sys.path.insert(0, str(_here))
    import lane_shim                                                      # noqa: E402

    if lane_shim.install(_lane):
        (_lane / "tmp").mkdir(exist_ok=True)
        os.environ.setdefault("TMPDIR", str(_lane / "tmp"))
        tempfile.tempdir = os.environ["TMPDIR"]
except Exception:                      # never break an unrelated interpreter
    pass
