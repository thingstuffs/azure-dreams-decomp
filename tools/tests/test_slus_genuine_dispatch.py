"""Dispatch contract for the private genuine-ASPSX candidate harness.

The tests stub every compile/measure entry point. They cover only process_row's
routing decision and harness-error record, using a temporary project root.
"""
from __future__ import annotations

import importlib.util
import os
import sys
import tempfile
import types
import unittest
from pathlib import Path
from unittest.mock import Mock, patch

HERE = Path(__file__).resolve().parent
REPO = HERE.parents[2] if (HERE / "aspsx_diff.py").exists() else HERE.parents[1]
CANDIDATE = HERE / "aspsx_diff.py" if (HERE / "aspsx_diff.py").exists() else REPO / "tools/fidelity/aspsx_diff.py"
sys.path[:0] = [str(REPO / "tools"), str(REPO / "tools/fidelity")]
_spec = importlib.util.spec_from_file_location("private_aspsx_diff_dispatch", CANDIDATE)
A = importlib.util.module_from_spec(_spec)
assert _spec.loader is not None
_spec.loader.exec_module(A)


class ProcessRowDispatchTests(unittest.TestCase):
    def setUp(self):
        self.temp = tempfile.TemporaryDirectory(prefix="aspsx_dispatch_")
        self.addCleanup(self.temp.cleanup)
        self.root = Path(self.temp.name)
        for relative in ("src/slus", "raw/slus", "tmp"):
            (self.root / relative).mkdir(parents=True)
        (self.root / "src/slus/code.c").write_text("int live_code(void) { return 1; }\n")
        (self.root / "raw/slus/code.c").write_text("int frozen_code(void) { return 2; }\n")
        (self.root / "src/slus/plain.c").write_text("int plain(void) { return 3; }\n")
        self.old_tmpdir = os.environ.get("TMPDIR")
        self.old_tempfile_tempdir = tempfile.tempdir
        self.addCleanup(self._restore_temp_settings)

    def _restore_temp_settings(self):
        if self.old_tmpdir is None:
            os.environ.pop("TMPDIR", None)
        else:
            os.environ["TMPDIR"] = self.old_tmpdir
        tempfile.tempdir = self.old_tempfile_tempdir

    def _row(self, stem: str, *, partitioned: bool = False):
        return {
            "id": f"slus/{stem}",
            "container": "slus",
            "kind": "slus",
            "c_path": f"src/{stem}.c",
            "cfg": "2.7.2",
            "row_asflags": "-G0",
            "partitioned": partitioned,
        }

    def _run_with_mocks(self, row, cfile, partition_context, *, partition_result=None):
        context_mod = types.ModuleType("slus_module_context")
        context_mod.fingerprint = Mock(return_value="fixture-fingerprint")
        context_mod.partition_context = partition_context
        pin_mod = types.ModuleType("pin_census")
        pin_mod.sites_of = Mock(return_value=[])
        prepare = Mock(return_value=({"kind": "slus", "fixture": True}, None))
        partition = Mock(return_value=partition_result or {"row": row["id"], "status": "partitioned"})

        def measure(_row, _ctx, _td, _fingerprint, rec, **_kwargs):
            rec["measured_by_test"] = True
            return rec

        measure_mock = Mock(side_effect=measure)
        with (
            patch.object(A, "ROOT", self.root),
            patch.object(A, "TMP", self.root / "tmp"),
            patch.object(A, "prepare_slus", prepare),
            patch.object(A, "process_partition", partition),
            patch.object(A, "_measure_context", measure_mock),
            patch.dict(sys.modules, {"slus_module_context": context_mod, "pin_census": pin_mod}),
        ):
            result = A.process_row(row, cfile=cfile)
        return result, prepare, partition, measure_mock, partition_context

    def test_connected_live_slus_dispatches_to_partition(self):
        row = self._row("code", partitioned=True)
        cfile = self.root / "src/slus/code.c"
        partition_context = Mock(return_value=([{"id": row["id"]}], [], None))
        partition_result = {"row": row["id"], "status": "partition-result"}

        result, prepare, partition, measure, _ = self._run_with_mocks(
            row, cfile, partition_context, partition_result=partition_result)

        self.assertEqual(result, partition_result)
        partition_context.assert_called_once_with(row)
        partition.assert_called_once()
        args = partition.call_args.args
        self.assertEqual(args[:4], (row, cfile, row["cfg"], row["row_asflags"]))
        self.assertEqual(Path(args[4]).parent, self.root / "tmp")
        self.assertEqual(args[5]["row"], row["id"])
        prepare.assert_not_called()
        measure.assert_not_called()

    def test_frozen_raw_slus_same_basename_stays_standalone(self):
        row = self._row("code", partitioned=True)
        cfile = self.root / "raw/slus/code.c"
        partition_context = Mock(return_value=([{"id": row["id"]}], [], None))

        result, prepare, partition, measure, _ = self._run_with_mocks(row, cfile, partition_context)

        partition_context.assert_not_called()
        partition.assert_not_called()
        prepare.assert_called_once()
        self.assertEqual(prepare.call_args.args[:4],
                         (row, cfile, row["cfg"], row["row_asflags"]))
        self.assertTrue(result["measured_by_test"])
        self.assertEqual(result["status"], "ok")
        measure.assert_called_once()

    def test_unconnected_live_slus_keeps_standalone_path(self):
        row = self._row("plain")
        cfile = self.root / "src/slus/plain.c"
        partition_context = Mock(return_value=([], [], None))

        result, prepare, partition, measure, _ = self._run_with_mocks(row, cfile, partition_context)

        partition_context.assert_called_once_with(row)
        prepare.assert_called_once()
        partition.assert_not_called()
        measure.assert_called_once()
        self.assertTrue(result["measured_by_test"])
        self.assertEqual(result["status"], "ok")

    def test_partition_context_exception_is_returned_as_error_record(self):
        row = self._row("code", partitioned=True)
        cfile = self.root / "src/slus/code.c"
        partition_context = Mock(side_effect=RuntimeError("partition lookup failed"))

        result, prepare, partition, measure, _ = self._run_with_mocks(row, cfile, partition_context)

        self.assertEqual(result["row"], row["id"])
        self.assertEqual(result["status"], "error")
        self.assertIn("harness: RuntimeError: partition lookup failed", result["err"])
        prepare.assert_not_called()
        partition.assert_not_called()
        measure.assert_not_called()


if __name__ == "__main__":
    unittest.main()
