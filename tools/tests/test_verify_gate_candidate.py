"""verify.gate_candidate: the row's window gate must be skipped by the SAME predicate promote.py
uses to decide whether landing pays for it -- not a second, independent `true_name`-only test.

    python3 -m unittest tools/tests/test_verify_gate_candidate.py

Regression (2026-09-22): gate_candidate short-circuited on `row.get("true_name")` alone.  promote's
needs_gate had already been corrected to require true_name AND a `proven` rowbase delta (a row
landed against a `solved` region is scorer-exact at its true base while the window gate still links
it synthetic).  `verify.py --gate` kept using the stale test and green-lit three rows that
promote.py then reverted as gate-mismatch -- the two checks had drifted apart.  Fixed by moving
`needs_gate` into verify.py as the single implementation; promote.py now imports it, so
`promote.needs_gate is verify.needs_gate` is true by construction (Identity, below) and can never
drift again.  GateCandidate exercises the two behaviours the bug conflated: a `solved` region does
NOT skip the gate, a `proven` one does.

No compiler and no real gate run: verify.run_window_gate / verify.window_lock are stubbed and
common.clean_path is redirected to a tempfile.mkdtemp() path, so the candidate never touches src/.
"""
import contextlib
import importlib.util
import sys
import tempfile
import unittest
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))
_spec = importlib.util.spec_from_file_location("promote_under_test", ROOT / "tools/promote.py")
promote = importlib.util.module_from_spec(_spec)
_spec.loader.exec_module(promote)
verify = sys.modules["verify"]          # promote's own `from verify import ...` registers it here
common = sys.modules["common"]


class FakeRowbase:
    """rowbase.delta_for with the proven_only switch the gate uses (same fake as
    test_promote_needs_gate.py)."""

    def __init__(self, regions):
        self.regions = regions          # [(start, end, delta, confidence)]

    def delta_for(self, family, foff, *, proven_only=False):
        for start, end, delta, conf in self.regions:
            if start <= foff < end:
                if proven_only and conf != "proven":
                    return None
                return delta
        return None


FOFF = 0x188E800
DELTA = 0x7E795800
TRUE = "func_%08X" % (FOFF + DELTA)


def row(**kw):
    base = dict(id="dungeon/func_8186E800", kind="overlay", container="dungeon",
                func="func_8186E800", true_name=TRUE, foff=FOFF, size=364,
                gate_config="dungeon.window7.overlay.yaml", c_path="func_8186E800.c")
    base.update(kw)
    return base


@contextlib.contextmanager
def rowbase(*regions):
    saved = verify._ROWBASE
    verify._ROWBASE = FakeRowbase(list(regions))
    try:
        yield
    finally:
        verify._ROWBASE = saved


@contextlib.contextmanager
def stubbed_gate(results=None):
    """Replace the compiler/gate machinery gate_candidate calls with recorders: no real window
    build, no write under the repo's real src/."""
    calls = []
    results = results or {}
    saved_run, saved_lock, saved_clean, saved_cov = (
        verify.run_window_gate, verify.window_lock, common.clean_path, common.covering_windows)

    def fake_run_window_gate(name, raw=False):
        calls.append(name)
        return results.get(name, "MATCH"), "msg"

    tmp = Path(tempfile.mkdtemp())

    verify.run_window_gate = fake_run_window_gate
    verify.window_lock = lambda name, raw=False: contextlib.nullcontext()
    common.clean_path = lambda r: tmp / Path(r["c_path"]).name
    common.covering_windows = lambda container, foff, size, wm=None: []
    try:
        yield calls, tmp
    finally:
        verify.run_window_gate, verify.window_lock = saved_run, saved_lock
        common.clean_path, common.covering_windows = saved_clean, saved_cov


class Identity(unittest.TestCase):
    """The fix in one sentence: there is exactly one predicate, not two copies that can drift."""

    def test_promote_needs_gate_is_verify_needs_gate(self):
        self.assertIs(promote.needs_gate, verify.needs_gate)

    def test_agree_on_a_small_table_of_rows(self):
        cases = [row(), row(true_name=None), row(true_name="func_80099999"),
                  row(foff=None), row(kind="slus", true_name=None)]
        for conf in ("proven", "solved"):
            with rowbase((FOFF, FOFF + 364, DELTA, conf)):
                for r in cases:
                    self.assertEqual(promote.needs_gate(r), verify.needs_gate(r), (conf, r["id"], r.get("true_name")))


class GateCandidate(unittest.TestCase):
    def setUp(self):
        self._saved = verify._ROWBASE
        self.addCleanup(lambda: setattr(verify, "_ROWBASE", self._saved))

    def test_true_name_with_only_a_solved_region_does_not_skip(self):
        """The bug: true_name registered against a `solved` (not proven) region used to short-
        circuit gate_candidate on `true_name` alone.  It must now actually run the window gate."""
        verify._ROWBASE = FakeRowbase([(FOFF, FOFF + 364, DELTA, "solved")])
        with stubbed_gate() as (calls, tmp):
            r = row()
            cp = tmp / r["c_path"]
            cp.parent.mkdir(parents=True, exist_ok=True)
            cp.write_text("/* before */\n")
            cand = tmp / "cand.c"
            cand.write_text("/* candidate */\n")
            res = verify.gate_candidate(r, str(cand))
        self.assertNotIn("not needed", res.get("gate", ""))
        self.assertEqual(res["gate"], "MATCH")
        self.assertEqual(calls, [r["gate_config"]], "the window gate must actually run for a solved region")
        self.assertEqual(cp.read_text(), "/* before */\n", "the row's text is restored after gating")

    def test_true_name_with_a_proven_region_skips(self):
        verify._ROWBASE = FakeRowbase([(FOFF, FOFF + 364, DELTA, "proven")])
        with stubbed_gate() as (calls, tmp):
            res = verify.gate_candidate(row(), "unused.c")
        self.assertEqual(res, {"gate": "not needed: true_name registered AND rowbase region proven (scorer and gate agree)"})
        self.assertEqual(calls, [], "no window may be compiled when the predicate says skip")


if __name__ == "__main__":
    unittest.main()
