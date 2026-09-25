"""Fail-closed tests for a part-only owner's real collector and full-TU proof."""
from __future__ import annotations

import copy
import sys
import tempfile
import unittest
from pathlib import Path
from unittest.mock import patch

REPO = Path(__file__).resolve().parents[2]
TOOLS = REPO / "tools"
sys.path[:0] = [str(TOOLS), str(TOOLS / "build")]

import slus_modules as M  # noqa: E402
import slus_partitions as P  # noqa: E402
import slus_module_context as C  # noqa: E402
import slus_module_evidence as E  # noqa: E402
from fidelity import prove_slus_ownership as O  # noqa: E402
from fidelity import certify_slus_module as CERT  # noqa: E402
from fidelity import slus_iso as ISO  # noqa: E402
import row_db as DB  # noqa: E402

for module, path in (
    (M, TOOLS / "build/slus_modules.py"),
    (P, TOOLS / "build/slus_partitions.py"),
    (C, TOOLS / "slus_module_context.py"),
    (E, TOOLS / "slus_module_evidence.py"),
    (O, TOOLS / "fidelity/prove_slus_ownership.py"),
    (CERT, TOOLS / "fidelity/certify_slus_module.py"),
    (ISO, TOOLS / "fidelity/slus_iso.py"),
    (DB, TOOLS / "row_db.py"),
):
    assert Path(module.__file__).resolve() == path.resolve()

F_A = "func_80030000"
F_B = "func_80030010"
F_C = "func_80030020"
F_D = "func_80030030"
FP = "fresh-connected-fingerprint"
OWNER = "src/part_owner.c"
RECIPE = {"ccver": "2.7.2-cdk", "ccflags": "-G32", "asflags": ""}


class PartitionOnlyEvidence(unittest.TestCase):
    def setUp(self):
        temp = tempfile.TemporaryDirectory(prefix="partition_only_evidence_")
        self.addCleanup(temp.cleanup)
        self.root = Path(temp.name)
        self.module = {"name": "part_owner", "source": OWNER, "recipe": copy.deepcopy(RECIPE),
                       "members": [], "partition_only": True, "data": []}
        self.parents = [
            {"id": "slus/code", "source": "src/code.c", "recipe": copy.deepcopy(RECIPE),
             "functions": [F_A, F_B],
             "parts": [{"module": "part_owner", "functions": [F_B]}]},
            {"id": "slus/code2", "source": "src/code2.c", "recipe": copy.deepcopy(RECIPE),
             "functions": [F_C, F_D],
             "parts": [{"module": "part_owner", "functions": [F_D]}]},
        ]
        self.owner_context = patch.object(E, "partition_context",
                                          side_effect=lambda row, root: (self.parents, [self.module], {}))
        self.owner_context.start()
        self.addCleanup(self.owner_context.stop)
        with patch.object(E, "module_anchor", return_value={"kind": "slus", "id": "slus/code"}):
            self.descriptor = E.physical_descriptor(self.module, self.root)
        self.records = {p["id"]: self.record(p) for p in self.parents}

    def record(self, parent):
        emitted = P.expected_units(self.parents, [self.module])
        units = []
        for unit in P.row_units(parent["id"], self.parents, [self.module]):
            part = dict(unit)
            part.update(row=parent["id"], status="ok", selfcheck=True, maspsx_exact=True,
                        module_fingerprint=FP, funcs=len(unit["functions"]),
                        cfg="2.7.2-cdk -G32",
                        expected_functions=sorted(emitted[unit["source"]]),
                        maspsx_retail={"diff": 0, "masked": 0,
                                       "checked": len(unit["functions"])})
            if unit["source"] == OWNER:
                part["maspsx_physical_retail"] = {"diff": 0, "masked": 0, "checked": 2}
                part["genuine"] = {"2.79": {
                    "exact": True, "retail": [0, 0], "retail_checked": 1, "mode": "-q",
                    "missing": [], "lnk_unknown": [],
                    "physical": {"exact": True, "diff": 0, "missing": [],
                                 "retail": {"diff": 0, "masked": 0, "checked": 2},
                                 "len_m": 42, "len_g": 42}}}
            else:
                # The unrelated remainder is pipeline/retail exact, but its
                # direct genuine comparison is deliberately not exact.
                part["genuine"] = {"2.79": {"exact": False, "retail": [1, 0],
                                               "retail_checked": 1, "mode": "-q"}}
            units.append(part)
        return {"row": parent["id"], "status": "ok", "selfcheck": True,
                "maspsx_exact": True, "functions": list(parent["functions"]),
                "funcs": len(parent["functions"]), "module_fingerprint": FP,
                "maspsx_retail": {"diff": 0, "masked": 0,
                                   "checked": len(parent["functions"])},
                "physical_units": units,
                "genuine": {"2.79": {"exact": False, "retail": [1, 0],
                                      "retail_checked": len(parent["functions"])}}}

    def check(self, record=None, contributor=None, descriptor=None):
        return E.check_partition_record(
            self.records["slus/code"] if record is None else record,
            self.descriptor["contributors"][0] if contributor is None else contributor,
            self.descriptor if descriptor is None else descriptor, FP, self.root)

    def test_real_part_anchor_and_complete_descriptor(self):
        with (patch.object(C.partitions, "load_plan", return_value=self.parents),
              patch.object(C, "partition_context",
                           return_value=(self.parents, [self.module], {}))):
            self.assertEqual(C.module_anchor(self.module, self.root),
                             {"kind": "slus", "id": "slus/code"})
        self.assertEqual(self.descriptor["functions"], [F_B, F_D])
        self.assertEqual([(c["row"], c["kind"], c["functions"])
                          for c in self.descriptor["contributors"]],
                         [("slus/code", "part", [F_B]),
                          ("slus/code2", "part", [F_D])])
        with patch.object(C.partitions, "load_plan", return_value=[]):
            with self.assertRaisesRegex(P.PartitionError, "no incoming functions"):
                C.module_anchor(self.module, self.root)

    def test_selected_complete_owner_passes_despite_remainder_genuine_mismatch(self):
        for contributor in self.descriptor["contributors"]:
            record = self.records[contributor["row"]]
            self.assertFalse(record["genuine"]["2.79"]["exact"])
            self.assertIs(E.check_partition_record(record, contributor, self.descriptor,
                                                   FP, self.root), record["physical_units"][1])

    def test_missing_incoming_function_or_full_tu_discrepancy_is_rejected(self):
        for mutation in (
            lambda r: r["physical_units"][1]["expected_functions"].remove(F_D),
            lambda r: r["physical_units"][1]["maspsx_physical_retail"].update(checked=1),
            lambda r: r["physical_units"][1]["genuine"]["2.79"]["physical"].update(exact=False, diff=1),
            lambda r: r["physical_units"][1]["genuine"]["2.79"]["physical"].update(len_g=41),
            lambda r: r["physical_units"][1]["genuine"]["2.79"]["physical"].update(missing=[F_D]),
        ):
            with self.subTest(mutation=mutation):
                record = copy.deepcopy(self.records["slus/code"])
                mutation(record)
                with self.assertRaises(ValueError):
                    self.check(record)
        descriptor = copy.deepcopy(self.descriptor)
        descriptor["functions"].remove(F_D)
        descriptor["contributors"].pop()
        with self.assertRaises(ValueError):
            self.check(descriptor=descriptor)

    def test_mask_unknown_lnk_fingerprint_recipe_and_scope_are_rejected(self):
        for mutation in (
            lambda r: r["maspsx_retail"].update(masked=1),
            lambda r: r["physical_units"][0]["maspsx_retail"].update(masked=1),
            lambda r: r["physical_units"][1]["maspsx_physical_retail"].update(masked=1),
            lambda r: r["physical_units"][1]["genuine"]["2.79"]["physical"]["retail"].update(masked=1),
            lambda r: r["physical_units"][1]["genuine"]["2.79"].update(lnk_unknown=["unknown"]),
            lambda r: r.update(module_fingerprint="stale"),
            lambda r: r["physical_units"][1].update(module_fingerprint="stale"),
            lambda r: r["physical_units"][1]["recipe"].update(ccflags="-G0"),
            lambda r: r["physical_units"][1].update(cfg="2.7.2-cdk -G0"),
            lambda r: r["physical_units"][1].update(functions=[F_D]),
        ):
            with self.subTest(mutation=mutation):
                record = copy.deepcopy(self.records["slus/code"])
                mutation(record)
                with self.assertRaises(ValueError):
                    self.check(record)

    def test_duplicate_unit_missing_remainder_and_forged_contributor_rejected(self):
        for mutation in (
            lambda r: r["physical_units"].append(copy.deepcopy(r["physical_units"][1])),
            lambda r: r["physical_units"].pop(0),
            lambda r: r["physical_units"].reverse(),
        ):
            record = copy.deepcopy(self.records["slus/code"])
            mutation(record)
            with self.assertRaises(ValueError):
                self.check(record)
        forged = copy.deepcopy(self.descriptor["contributors"][0])
        forged["row"] = "slus/forged"
        with self.assertRaisesRegex(ValueError, "declared contributor"):
            self.check(contributor=forged)
        descriptor = copy.deepcopy(self.descriptor)
        descriptor["contributors"][0] = forged
        with self.assertRaisesRegex(ValueError, "matching collector"):
            self.check(contributor=forged, descriptor=descriptor)

    def test_partition_owner_never_receives_whole_row_placement(self):
        self.assertIn("no whole-row placement", E.certificate_reason(self.module, {}, self.root))
        with (patch.object(CERT, "modules", return_value=[self.module]),
              patch.object(CERT, "SlusView", side_effect=AssertionError("build started"))):
            with self.assertRaisesRegex(ValueError, "no whole-row placement"):
                CERT.certify("part_owner", "reviewer")
        with patch.object(E, "module_status", return_value=[{
            "module": self.module, "certificate": {"module_fingerprint": FP},
            "valid": True, "reason": None}]):
            self.assertEqual(E.valid_placements(self.root), {})

    def test_ownership_processes_real_parent_rows_with_empty_members(self):
        (self.root / "ledger/splits").mkdir(parents=True)
        (self.root / "ledger/splits/slus.build.ninja").write_bytes(b"fixture recipe\n")

        class View:
            def __init__(inner, dest):
                inner.dest = Path(dest)
                (inner.dest / "build/src").mkdir(parents=True)
                (inner.dest / "build.ninja").write_bytes(b"fixture recipe\n")
                (inner.dest / "build/slus_006.14").write_bytes(b"retail image")
                (inner.dest / "build/src/part_owner.o").write_bytes(b"object")

            def calibrate(inner):
                return {"result": "MATCH"}

        rows = [{"kind": "slus", "id": p["id"]} for p in self.parents]
        processed = []

        def process(row):
            processed.append(row["id"])
            return copy.deepcopy(self.records[row["id"]])

        with (patch.object(O, "ROOT", self.root),
              patch.object(O, "modules", return_value=[self.module]),
              patch.object(O, "physical_descriptor", return_value=self.descriptor),
              patch.object(O, "rows", return_value=rows),
              patch.object(O, "fingerprint", return_value=FP),
              patch.object(O, "verifier_fingerprint", return_value="tool-v1"),
              patch.object(O, "SlusView", View),
              patch.object(O, "symbols", return_value={}),
              patch.object(O, "prove_data", return_value={"sections": {}}),
              patch.object(O.A, "read_elf", return_value=object()),
              patch.object(O.A, "process_row", side_effect=process)):
            receipt = O.prove(["part_owner"])
        self.assertEqual(processed, ["slus/code", "slus/code2"])
        self.assertEqual(receipt["schema"], 5)
        self.assertEqual(set(receipt["rows"]), set(processed))
        self.assertEqual(receipt["partition_only_modules"], ["part_owner"])
        self.assertNotIn("placement", receipt["purpose"].replace("no L4/L5 certificate", ""))

    def test_isolated_gate_validates_orphan_partition_owner_even_with_empty_plan(self):
        source = self.root / "source_build"
        (source / "build").mkdir(parents=True)
        (source / "build.ninja").write_text("fixture recipe\n")
        (source / "build/slus_006.14").write_bytes(b"retail image")
        (self.root / "ledger/splits").mkdir(parents=True)
        (self.root / "ledger/splits/slus.jsonl").write_text("")
        with (patch.object(ISO, "ROOT", self.root),
              patch.object(ISO, "load_manifest", return_value=[self.module]),
              patch.object(ISO.partitions, "load_plan", return_value=[]),
              patch.object(ISO.partitions, "read_aliases", return_value={}),
              patch.object(ISO, "edges_of", return_value=[]),
              patch.object(ISO.partitions, "project_edges", return_value=[]),
              patch.object(ISO, "logical_edges", return_value=[]),
              patch.object(ISO.partitions, "validate_context",
                           side_effect=P.PartitionError("orphan owner validated")) as validate):
            with self.assertRaisesRegex(P.PartitionError, "orphan owner validated"):
                ISO.SlusView(self.root / "isolated", source)
        validate.assert_called_once()

    def test_row_database_rejects_orphan_partition_owner_with_empty_plan(self):
        (self.root / "config").mkdir()
        (self.root / "config/names.tsv").write_text("")
        plan = self.root / "config/slus_partitions.json"
        for present in (False, True):
            with self.subTest(explicit_empty_plan=present):
                if present:
                    plan.write_text('{"version": 1, "parents": []}\n')
                with self.assertRaisesRegex(P.PartitionError, "no incoming nonempty part"):
                    DB.check_slus_partition_plan(self.root, [self.module], [])
                self.assertEqual(DB.check_slus_partition_plan(self.root, [], []), [])


if __name__ == "__main__":
    unittest.main()
