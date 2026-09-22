"""promote.needs_gate: when landing a row has to pay for a window gate.

    python3 -m unittest tools/tests/test_promote_needs_gate.py

Synthetic rows only, with the rowbase table injected -- no config/ read, no compiler, no writes.

The rule under test is the disagreement between two linkers.  The per-row scorer links a row at its
true base as soon as ANY rowbase record covers it (rowbase.link_vram, owner decision C); the window
gate links there only when the row also carries a registered `true_name` AND its region is `proven`
(overlay_local_gate._rowbase_proven_delta).  A landing may skip the gate only where both agree.

Regression: the old test was `not row["true_name"]` alone.  On 2026-09-22 fifteen rows landed with a
true_name registered against a region that was still `solved`; the scorer used the true base, the
gate kept using the synthetic one, and four dungeon windows went NO MATCH.  test_solved_region_gates
is that case.

The predicate itself now lives in tools/verify.py (verify.gate_candidate needs the identical rule,
and verify.py must not import promote.py -- promote already imports verify); `promote.needs_gate` is
that same function object, imported by reference (see test_verify_gate_candidate.py's identity
check).  Its rowbase-table injection point (`_ROWBASE`) moved with it, so this test patches
`verify._ROWBASE`, reached via sys.modules after loading promote (promote's own `from verify
import ...` is what puts the real verify module there) -- every assertion below still reads
`promote.needs_gate(...)`.
"""
import importlib.util
import sys
import unittest
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))
_spec = importlib.util.spec_from_file_location("promote_under_test", ROOT / "tools/promote.py")
promote = importlib.util.module_from_spec(_spec)
_spec.loader.exec_module(promote)
verify = sys.modules["verify"]         # promote's own `from verify import ...` registers it here


class FakeRowbase:
    """rowbase.delta_for with the proven_only switch the gate uses."""

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
                func="func_8186E800", true_name=TRUE, foff=FOFF, size=364)
    base.update(kw)
    return base


class NeedsGate(unittest.TestCase):
    def setUp(self):
        self._saved = verify._ROWBASE
        self.addCleanup(lambda: setattr(verify, "_ROWBASE", self._saved))

    def use(self, *regions):
        verify._ROWBASE = FakeRowbase(list(regions))

    # --- the two linkers agree: no gate -------------------------------------------------
    def test_proven_region_and_matching_true_name_skips_gate(self):
        self.use((FOFF, FOFF + 364, DELTA, "proven"))
        self.assertFalse(promote.needs_gate(row()))

    # --- the regression this test exists for --------------------------------------------
    def test_solved_region_gates(self):
        """true_name registered but the region is only `solved`: the gate still links synthetic."""
        self.use((FOFF, FOFF + 364, DELTA, "solved"))
        self.assertTrue(promote.needs_gate(row()))

    def test_no_region_gates(self):
        self.use()
        self.assertTrue(promote.needs_gate(row()))

    # --- the legacy population -----------------------------------------------------------
    def test_no_true_name_gates_even_in_a_proven_region(self):
        self.use((FOFF, FOFF + 364, DELTA, "proven"))
        self.assertTrue(promote.needs_gate(row(true_name=None)))

    # --- corruption: the gate's WINDOW-LINK DIVERGENCE abort ------------------------------
    def test_true_name_contradicting_the_proven_delta_gates(self):
        self.use((FOFF, FOFF + 364, DELTA, "proven"))
        self.assertTrue(promote.needs_gate(row(true_name="func_80099999")))

    # --- everything unknown falls through to gating --------------------------------------
    def test_missing_foff_gates(self):
        self.use((FOFF, FOFF + 364, DELTA, "proven"))
        self.assertTrue(promote.needs_gate(row(foff=None)))

    def test_unreadable_rowbase_gates(self):
        class Boom:
            def delta_for(self, *a, **k):
                raise OSError("no rowbase table")
        verify._ROWBASE = Boom()
        self.assertTrue(promote.needs_gate(row()))

    # --- slus rows have no window at all --------------------------------------------------
    def test_non_overlay_never_gates(self):
        self.use()
        self.assertFalse(promote.needs_gate(row(kind="slus", true_name=None)))


if __name__ == "__main__":
    unittest.main()
