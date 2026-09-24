"""Private contract tests for a connected SLUS destination certificate.

The positive genuine record is a fresh private measurement copied to durable
evidence.  Certificate files, plan mutations, and Ninja/retail bytes are small
temporary fixtures; no production certificate is written.
"""

from __future__ import annotations

import copy
import hashlib
import importlib.util
import json
import sys
import tempfile
import unittest
from pathlib import Path
from unittest.mock import patch

HERE = Path(__file__).resolve().parent
REPO = next(parent for parent in HERE.parents if (parent / "tools/slus_module_evidence.py").is_file())
sys.path[:0] = [str(REPO / "tools"), str(REPO / "tools/build")]


def load_candidate(name, local_name, production_name):
    path = HERE / local_name
    if not path.is_file():
        path = REPO / production_name
    spec = importlib.util.spec_from_file_location(name, path)
    module = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(module)
    return module


E = load_candidate("private_physical_evidence", "slus_module_evidence.py",
                   "tools/slus_module_evidence.py")
_previous_evidence = sys.modules.get("slus_module_evidence")
sys.modules["slus_module_evidence"] = E
try:
    O = load_candidate("private_physical_ownership", "prove_slus_ownership.py",
                       "tools/fidelity/prove_slus_ownership.py")
finally:
    if _previous_evidence is None:
        del sys.modules["slus_module_evidence"]
    else:
        sys.modules["slus_module_evidence"] = _previous_evidence

MEMBER_ID = "slus/w_80041134"
PARENT_ID = "slus/code"
SOURCE = "src/w_80041134_owned.c"
MEMBER_FUNCTION = "func_80041134"
INCOMING = ["func_800410FC", "func_80041110"]
MEASURED = json.loads((REPO / "docs/evidence/slus_partitions/genuine_w_80041134.json").read_text())


class PhysicalCertificateTests(unittest.TestCase):
    def setUp(self):
        temp = tempfile.TemporaryDirectory(prefix="slus_physical_cert_")
        self.addCleanup(temp.cleanup)
        self.root = Path(temp.name)
        for directory in ("docs/evidence", "ledger/splits", "baserom"):
            (self.root / directory).mkdir(parents=True)
        self.review = "docs/evidence/list_cursor_e0.md"
        (self.root / self.review).write_text("reviewed source and shared types\n")
        (self.root / "ledger/splits/slus.build.ninja").write_text("pinned recipe\n")
        (self.root / "baserom/slus_006.14").write_bytes(b"retail bytes")
        self.module = {
            "name": "list_cursor_e0", "source": SOURCE,
            "recipe": {"ccver": "2.8.1", "ccflags": "", "asflags": ""},
            "members": [{"id": MEMBER_ID, "source": "src/w_80041134.c",
                         "functions": [MEMBER_FUNCTION]}],
            "evidence": self.review,
        }
        # Provenance is deliberately synthetic: the descriptor must distinguish
        # the incoming collector functions from the one module member.
        self.parent = {
            "id": PARENT_ID, "source": "src/code.c",
            "parts": [{"module": self.module["name"], "functions": list(INCOMING)}],
        }
        self.fingerprint = MEASURED["module_fingerprint"]
        self.context = patch.object(E, "partition_context",
                                    side_effect=lambda row, root: ([self.parent], [self.module], {}))
        self.context.start()
        self.addCleanup(self.context.stop)
        self.descriptor = E.physical_descriptor(self.module, self.root)
        self.record = copy.deepcopy(MEASURED)

    def certificate(self):
        return {
            "schema": 2, "module": self.module["name"], "members": [MEMBER_ID],
            "physical": copy.deepcopy(self.descriptor),
            "module_fingerprint": self.fingerprint, "tool_fingerprint": "test-tool-fingerprint",
            "review": {"path": self.review, "sha256": E.digest(self.root / self.review),
                       "reviewer": "fixture-reviewer"},
            "gate": {"result": "MATCH",
                     "recipe_sha256": E.digest(self.root / "ledger/splits/slus.build.ninja")},
            "image_sha1": hashlib.sha1(b"retail bytes").hexdigest(),
            "rows": {MEMBER_ID: copy.deepcopy(self.record)},
        }

    def assert_record_rejected(self, mutation, reason=None):
        record = copy.deepcopy(self.record)
        mutation(record)
        with self.assertRaises(ValueError) as caught:
            E.check_physical_record(record, self.module["members"][0],
                                    self.descriptor, self.fingerprint)
        if reason:
            self.assertIn(reason, str(caught.exception))

    def test_descriptor_names_entire_owner_and_distinguishes_incoming_parts(self):
        self.assertEqual(self.descriptor["source"], SOURCE)
        self.assertEqual(self.descriptor["recipe"], self.module["recipe"])
        self.assertEqual(self.descriptor["functions"], sorted(INCOMING + [MEMBER_FUNCTION]))
        contributors = self.descriptor["contributors"]
        self.assertEqual([(c["row"], c["kind"], c["functions"]) for c in contributors],
                         [(MEMBER_ID, "member", [MEMBER_FUNCTION]),
                          (PARENT_ID, "part", INCOMING)])
        self.assertEqual(self.record["functions"], [MEMBER_FUNCTION])
        self.assertEqual(self.record["physical_units"][0]["expected_functions"],
                         self.descriptor["functions"])
        self.assertIs(E.check_physical_record(self.record, self.module["members"][0],
                                              self.descriptor, self.fingerprint),
                      self.record["physical_units"][0])

    def test_duplicate_or_missing_incoming_descriptor_function_is_refused(self):
        self.parent["parts"][0]["functions"].append(MEMBER_FUNCTION)
        with self.assertRaisesRegex(ValueError, "duplicate contributor coverage"):
            E.physical_descriptor(self.module, self.root)
        self.parent["parts"][0]["functions"] = [INCOMING[0]]
        shorter = E.physical_descriptor(self.module, self.root)
        self.assertNotEqual(shorter, self.descriptor)
        with self.assertRaisesRegex(ValueError, "destination physical context"):
            E.check_physical_record(self.record, self.module["members"][0], shorter, self.fingerprint)

    def test_context_recipe_fingerprint_row_and_extra_unit_must_match(self):
        mutations = [
            (lambda r: r["physical_units"][0].update(source="src/other.c"), "physical context"),
            (lambda r: r["physical_units"][0]["recipe"].update(ccver="2.7.2"), "physical context"),
            (lambda r: r["physical_units"][0].update(cfg="2.7.2"), "physical context"),
            (lambda r: r.update(module_fingerprint="stale"), "member lacks"),
            (lambda r: r["physical_units"][0].update(module_fingerprint="stale"), "physical context"),
            (lambda r: r.update(row=PARENT_ID), "member lacks"),
            (lambda r: r["physical_units"][0].update(row=PARENT_ID), "physical context"),
            (lambda r: r["physical_units"].append(copy.deepcopy(r["physical_units"][0])), "member lacks"),
            (lambda r: r["physical_units"][0].update(expected_functions=[MEMBER_FUNCTION]), "physical context"),
        ]
        for index, (mutation, reason) in enumerate(mutations):
            with self.subTest(case=index):
                self.assert_record_rejected(mutation, reason)

    def test_subset_exact_cannot_hide_full_physical_mismatch_or_mask(self):
        mutations = [
            lambda r: r["physical_units"][0]["genuine"]["2.79"]["physical"].update(exact=False, diff=1),
            lambda r: r["physical_units"][0]["genuine"]["2.79"]["physical"]["retail"].update(masked=1),
            lambda r: r["physical_units"][0]["genuine"]["2.79"]["physical"].update(missing=[INCOMING[0]]),
            lambda r: r["physical_units"][0]["genuine"]["2.79"].update(lnk_unknown=["unknown LNK"]),
            lambda r: r["physical_units"][0]["maspsx_physical_retail"].update(checked=1),
            lambda r: r["physical_units"][0]["maspsx_physical_retail"].update(masked=1),
        ]
        for index, mutation in enumerate(mutations):
            with self.subTest(case=index):
                self.assert_record_rejected(mutation)

    def test_genuine_mode_must_be_same_for_subset_and_full_owner(self):
        self.assert_record_rejected(
            lambda r: r["genuine"]["2.79"]["modes"].update({SOURCE: "-0"}),
            "full-TU direct genuine")
        self.assert_record_rejected(
            lambda r: r["physical_units"][0]["genuine"]["2.79"].update(mode="-0"),
            "full-TU direct genuine")

    def test_modeled_record_is_not_direct_physical_proof(self):
        self.assert_record_rejected(lambda r: r.update(compiler_model={"name": "t272"}),
                                    "physical context")
        self.assert_record_rejected(lambda r: r["physical_units"][0].update(model="t272"),
                                    "physical context")

    def test_connected_schema2_validator_and_descriptor_freshness(self):
        cert = self.certificate()
        with patch.object(E, "fingerprint", return_value=self.fingerprint):
            self.assertIsNone(E.certificate_reason(self.module, cert, self.root,
                                                   tool_fp="test-tool-fingerprint"))
            old = copy.deepcopy(cert)
            old["schema"] = 1
            self.assertIn("certificate does not describe", E.certificate_reason(
                self.module, old, self.root, tool_fp="test-tool-fingerprint"))
            for mutation in (
                lambda c: c["physical"]["functions"].remove(INCOMING[0]),
                lambda c: c["physical"]["contributors"][1].update(row="slus/other"),
                lambda c: c["physical"]["recipe"].update(ccver="2.7.2"),
                lambda c: c["physical"].update(source="src/other.c"),
            ):
                changed = copy.deepcopy(cert)
                mutation(changed)
                self.assertIn("physical contributors or destination changed",
                              E.certificate_reason(self.module, changed, self.root,
                                                   tool_fp="test-tool-fingerprint"))
            self.parent["parts"][0]["functions"] = [INCOMING[0]]
            self.assertIn("physical contributors or destination changed",
                          E.certificate_reason(self.module, cert, self.root,
                                               tool_fp="test-tool-fingerprint"))

    def test_placement_list_grants_only_whole_members(self):
        cert = self.certificate()
        with patch.object(E, "module_status", return_value=[
            {"module": self.module, "certificate": cert, "valid": True, "reason": None}]):
            grants = E.valid_placements(self.root)
        self.assertEqual(set(grants), {MEMBER_ID})
        self.assertNotIn(PARENT_ID, grants)

    def test_connected_ownership_refuses_individual_compiler_model_before_io(self):
        with (patch.object(O, "modules", return_value=[self.module]),
              patch.object(O, "physical_descriptor", return_value=self.descriptor),
              patch.object(O, "rows", side_effect=AssertionError("row IO reached"))):
            with self.assertRaisesRegex(ValueError, "individual compiler-model row is insufficient"):
                O.prove([self.module["name"]], compiler_model_rows=[MEMBER_ID])


if __name__ == "__main__":
    unittest.main()
