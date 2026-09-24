"""Private consumer regressions for plural genuine-ASPSX records."""

from __future__ import annotations

import contextlib
import importlib.util
import io
import json
import subprocess
import sys
import tempfile
import types
import unittest
from pathlib import Path
from unittest.mock import patch

HERE = Path(__file__).resolve().parent
CANDIDATES = HERE if (HERE / "aspsx_report.py").is_file() else HERE.parents[1] / "tools/fidelity"


def load(name):
    spec = importlib.util.spec_from_file_location(name, CANDIDATES / (name + ".py"))
    module = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(module)
    return module


R = load("aspsx_report")
C = load("cell_retail_check")
VERSIONS = ("2.56", "2.67", "2.77", "2.79", "2.81", "2.86")


def unit(source, exact, fix=(), model=None):
    genuine = {version: {"exact": version in exact, "diff": 0 if version in exact else 1}
               for version in VERSIONS}
    return {"source": source, "role": "remainder" if source.endswith("code.c") else "module",
            "module": None if source.endswith("code.c") else "owner",
            "recipe": {"ccver": "2.7.2" if source.endswith("code.c") else "2.8.1",
                       "ccflags": "", "asflags": ""},
            "functions": ["func_80041000"], "exact_versions": exact,
            "best": exact[0] if exact else "2.79", "genuine": genuine,
            "attrib": {"2.79": {"fix": list(fix)}} if not exact else {},
            "fired": ["_fold_selfinc_la"],
            "gp_externs": ["D_X"] if fix else [], "compiler_model": model}


def record(row, units=None, exact=(), ownerwise=False, fix=()):
    genuine = {version: {"exact": version in exact, "diff": 0 if version in exact else 1,
                         "retail": [0 if version in exact else 1, 0], "mode": "-0"}
               for version in VERSIONS}
    value = {"row": row, "container": "slus", "kind": "slus", "status": "ok",
             "cfg": "2.7.2", "cell": "mixed" if units else "2.7.2", "asflags": "",
             "pins": 0, "maspsx_exact": True, "selfcheck": True,
             "maspsx_retail": {"diff": 0, "masked": 0}, "words": 3,
             "exact_versions": list(exact), "best": "2.79",
             "genuine": genuine,
             "fired": ["_fold_selfinc_la"], "gp_externs": [], "n_gp_externs": 0,
             "attrib": {"2.79": {"fix": list(fix)}}}
    if units is not None:
        value["physical_units"] = units
        value["ownerwise_exact_versions"] = ownerwise
    return value


class ReportConsumer(unittest.TestCase):
    def test_ownerwise_version_gap_is_not_maspsx_dependence(self):
        ownerwise = record("slus/ownerwise", [unit("src/code.c", ["2.79"]),
                                              unit("src/owner.c", ["2.81"], model="t272")],
                           ownerwise=True)
        dependent = record("slus/dependent", [unit("src/code.c", [], ["no:_fold_selfinc_la"]),
                                                unit("src/owner.c", ["2.79"])],
                           ownerwise=False, fix=["no:_wrong_top_level"])
        dependent["gp_externs"] = ["D_X"]
        dependent["n_gp_externs"] = 1
        legacy = record("slus/legacy", fix=["no:_maybe_unfill_return_delay"])
        with tempfile.TemporaryDirectory() as td:
            journal = Path(td) / "journal.jsonl"
            out = Path(td) / "out"
            out.mkdir()
            journal.write_text("\n".join(json.dumps(r) for r in (ownerwise, dependent, legacy)) + "\n")
            p = subprocess.run([sys.executable, str(CANDIDATES / "aspsx_report.py"),
                                "--journal", str(journal), "--out-dir", str(out)],
                               text=True, capture_output=True, check=True)
            self.assertIn("ownerwise genuine-exact with no common version: 1", p.stdout)
            self.assertIn("maspsx-dependent in at least one physical unit: 2", p.stdout)
            self.assertIn("Rows with a compiler-modelled physical stream: 1", p.stdout)
            dep = (out / "maspsx_dependent.tsv").read_text()
            self.assertNotIn("slus/ownerwise", dep)
            self.assertIn("slus/dependent", dep)
            self.assertIn("owner-specific", dep)
            self.assertNotIn("no:_wrong_top_level", dep)
            whole = (out / "pass_dependents.tsv").read_text()
            owner = (out / "pass_dependents_physical.tsv").read_text()
            self.assertIn("slus/legacy", whole)
            self.assertNotIn("slus/dependent", whole)
            self.assertIn("_fold_selfinc_la\tslus/dependent\tsrc/code.c\towner-only", owner)
            self.assertIn("t272", (out / "physical_units.tsv").read_text())

    def test_inconsistent_ownerwise_claim_is_rejected(self):
        bad = record("slus/bad", [unit("src/code.c", ["2.79"]),
                                  unit("src/owner.c", ["2.81"])], ownerwise=False)
        with self.assertRaisesRegex(ValueError, "disagrees"):
            R.ownerwise_exact(bad)

    def test_common_version_claim_must_equal_owner_intersection(self):
        common_missing = record("slus/missing", [unit("src/code.c", ["2.79"]),
                                                  unit("src/owner.c", ["2.79"])], ownerwise=True)
        common_extra = record("slus/extra", [unit("src/code.c", ["2.79"]),
                                              unit("src/owner.c", ["2.81"])],
                              exact=["2.79"], ownerwise=True)
        for bad in (common_missing, common_extra):
            with self.subTest(row=bad["row"]), self.assertRaisesRegex(ValueError, "common genuine versions"):
                R.ownerwise_exact(bad)


class CellTrialBoundary(unittest.TestCase):
    def setUp(self):
        self.row = {"id": "slus/code", "kind": "slus", "cfg": "2.7.2", "func": "code"}
        self.context = types.SimpleNamespace(partition_context=lambda row: (
            [{"source": "src/code.c"}], [{"source": "src/owner.c"}], {}))

    def test_direct_worker_refuses_before_measurement(self):
        fake_aspsx = types.SimpleNamespace(process_row=lambda *a, **k: self.fail("measured"))
        fake_common = types.SimpleNamespace(rows=lambda: [self.row])
        with patch.dict(sys.modules, {"slus_module_context": self.context,
                                      "aspsx_diff": fake_aspsx, "common": fake_common}):
            with self.assertRaisesRegex(ValueError, "explicit per-unit recipe trial"):
                C.check_row("slus/code", "2.8.1", False)

    def test_cli_preflight_refuses_before_output_file(self):
        fake_common = types.SimpleNamespace(rows=lambda: [self.row])
        with tempfile.TemporaryDirectory() as td:
            output = Path(td) / "trial.jsonl"
            for opts in (["--registered"], ["--cell", "2.8.1"],
                         ["--cfg", "2.8.1", "--asflags-variants"]):
                with self.subTest(opts=opts), patch.dict(sys.modules, {
                    "slus_module_context": self.context, "common": fake_common}), \
                        patch.object(sys, "argv", ["cell_retail_check.py", "--rows", "slus/code",
                                                   "--out", str(output), *opts]), \
                        contextlib.redirect_stderr(io.StringIO()):
                    with self.assertRaises(SystemExit) as raised:
                        C.main()
                    self.assertEqual(raised.exception.code, 2)
                    self.assertFalse(output.exists())


if __name__ == "__main__":
    unittest.main()
