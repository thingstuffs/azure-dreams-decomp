"""sweep._window_gate: an exact candidate that reaches src/ still has to pass the row's window.

    python3 -m unittest tools/tests/test_sweep_window_gate.py

No compiler and no writes: `promote` and `verify` are replaced in sys.modules, so the hook is
exercised without gating anything.  Regression: tools/sweep.py used to write src/ on the per-row
scorer alone, and on 2026-09-22 two town rows landed that way failed their windows and had to be
reverted by hand -- the same hazard tools/promote.py gates for.
"""
import contextlib
import importlib.util
import sys
import types
import unittest
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))
_spec = importlib.util.spec_from_file_location("sweep_under_test", ROOT / "tools/sweep.py")
sweep = importlib.util.module_from_spec(_spec)
_spec.loader.exec_module(sweep)

ROW = {"id": "dungeon/func_8186E800", "kind": "overlay", "container": "dungeon",
       "func": "func_8186E800", "true_name": "func_80024000", "foff": 0x188E800, "size": 364}


@contextlib.contextmanager
def fake(needs_gate, windows, results):
    """Stand in for the `promote` and `verify` modules sweep._window_gate imports lazily."""
    calls = []
    promote = types.ModuleType("promote")
    promote.needs_gate = lambda row: needs_gate
    promote.windows_of = lambda row: list(windows)
    verify = types.ModuleType("verify")

    def run_window_gate(name):
        calls.append(name)
        return (results.get(name, "MATCH"), "msg")

    verify.run_window_gate = run_window_gate
    verify.window_lock = lambda name: contextlib.nullcontext()
    saved = {k: sys.modules.get(k) for k in ("promote", "verify")}
    sys.modules["promote"], sys.modules["verify"] = promote, verify
    try:
        yield calls
    finally:
        for k, v in saved.items():
            if v is None:
                sys.modules.pop(k, None)
            else:
                sys.modules[k] = v


class WindowGateHook(unittest.TestCase):
    def test_row_that_needs_no_gate_takes_the_fast_path(self):
        with fake(False, ["w1.overlay.yaml"], {}) as calls:
            self.assertIsNone(sweep._window_gate(ROW))
        self.assertEqual(calls, [], "no window may be compiled for a row promote.needs_gate clears")

    def test_all_windows_match(self):
        with fake(True, ["w1.overlay.yaml", "w2.overlay.yaml"], {}) as calls:
            self.assertIsNone(sweep._window_gate(ROW))
        self.assertEqual(calls, ["w1.overlay.yaml", "w2.overlay.yaml"])

    def test_first_failing_window_is_returned(self):
        results = {"w2.overlay.yaml": "NO MATCH"}
        with fake(True, ["w1.overlay.yaml", "w2.overlay.yaml", "w3.overlay.yaml"], results) as calls:
            self.assertEqual(sweep._window_gate(ROW), "w2.overlay.yaml")
        self.assertEqual(calls, ["w1.overlay.yaml", "w2.overlay.yaml"], "stop at the first failure")


if __name__ == "__main__":
    unittest.main()
