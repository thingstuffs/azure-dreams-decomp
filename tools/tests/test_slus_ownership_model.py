"""Explicit compiler-model ownership proof: row selection and evidence gates."""

import sys
import tempfile
import unittest
from pathlib import Path
from types import SimpleNamespace
from unittest.mock import patch

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))
from fidelity import prove_slus_ownership as P


def fn(name, mask="c0ff0000"):
    return (f"\t.ent\t{name}\n{name}:\n\t.frame\t$sp,32,$31\n\t.mask\t0x{mask},-8\n"
            "\t.fmask\t0x00000000,0\n\tlw\t$31,24($sp)\n\tlw\t$16,16($sp)\n"
            "\t.set\tnoreorder\n\t.set\tnomacro\n\tj\t$31\n\taddu\t$sp,$sp,32\n"
            f"\t.set\tmacro\n\t.set\treorder\n\n\t.end\t{name}\n")


class SelectionAndDirectEvidence(unittest.TestCase):
    def setUp(self):
        self.member = {"id": "slus/a", "functions": ["f"]}
        self.modules = [{"members": [self.member]}]
        self.record = {"row": "slus/a", "status": "ok", "maspsx_exact": True,
                       "selfcheck": True, "maspsx_retail": {"diff": 0, "masked": 0, "checked": 1},
                       "module_fingerprint": "fp",
                       "genuine": {"2.79": {"exact": False, "diff": 1, "retail": [1, 0]}}}

    def test_only_explicit_selected_member_is_eligible(self):
        self.assertEqual(P.selected_model_rows(self.modules, ["slus/a"]), {"slus/a"})
        with self.assertRaisesRegex(ValueError, "not a selected member"):
            P.selected_model_rows(self.modules, ["slus/other"])
        with self.assertRaisesRegex(ValueError, "duplicate"):
            P.selected_model_rows(self.modules, ["slus/a", "slus/a"])
        # No selected model: the unchanged direct-genuine rule rejects this row.
        with self.assertRaisesRegex(ValueError, "direct-genuine"):
            P.check_member_record(self.record, self.member, "fp")
        P.check_member_record(self.record, self.member, "fp", modeled=True)

    def test_selected_row_needs_successful_unmasked_direct_discrepancy(self):
        for genuine in ({}, {"err": "open failed"}, {"exact": True, "diff": 0, "retail": [0, 0]},
                        {"exact": False, "diff": 1, "retail": [1, 1]},
                        {"exact": False, "diff": 0, "retail": [1, 0]},
                        {"exact": False, "diff": 1, "retail": [0, 0]},
                        {"exact": False, "diff": 1, "retail": [1, 0], "missing": ["f"]},
                        {"exact": False, "diff": 1, "retail": [1, 0], "lnk_unknown": ["record"]}):
            with self.subTest(genuine=genuine):
                record = dict(self.record, genuine={"2.79": genuine})
                with self.assertRaisesRegex(ValueError, "unmasked measured direct discrepancy"):
                    P.check_member_record(record, self.member, "fp", modeled=True)

    def test_model_never_bypasses_existing_pipeline_retail_or_fingerprint_gates(self):
        bad = [dict(self.record, maspsx_exact=False), dict(self.record, selfcheck=False),
               dict(self.record, module_fingerprint="changed"),
               dict(self.record, maspsx_retail={"diff": 0, "masked": 1, "checked": 1})]
        for record in bad:
            with self.subTest(record=record):
                with self.assertRaisesRegex(ValueError, "pipeline/retail"):
                    P.check_member_record(record, self.member, "fp", modeled=True)


class ModeledStream(unittest.TestCase):
    def test_t272_rewrites_only_named_function_and_rejects_unknown_model(self):
        source = fn("selected") + fn("neighbour")
        changed = P.rewrite_selected_functions(source, ["selected"])
        self.assertIn("\taddu\t$sp,$sp,32\n\tj\t$31\n", changed)
        self.assertIn(fn("neighbour"), changed)
        self.assertNotIn(fn("selected"), changed)
        with self.assertRaisesRegex(ValueError, "unsupported compiler model"):
            P.rewrite_selected_functions(source, ["selected"], model="all")
        with self.assertRaisesRegex(ValueError, "missing or ambiguous"):
            P.rewrite_selected_functions(source, ["missing"])

    def run_modeled_proof(self, *, compare_exact=True, pipeline_retail=None,
                          genuine_retail=None, unknown=(), missing=()):
        source = fn("f") + fn("neighbour")
        row = {"id": "slus/a", "cfg": "2.8.1", "row_asflags": ""}
        member = {"id": "slus/a", "functions": ["f"]}
        expected = {"diff": 0, "masked": 0, "checked": 1}
        pipeline_retail = expected if pipeline_retail is None else pipeline_retail
        genuine_retail = expected if genuine_retail is None else genuine_retail
        with tempfile.TemporaryDirectory() as td:
            cfile = Path(td) / "a.c"
            cfile.write_text("int f(void) { return 1; }\n")
            context = {"maspsx_exact": True, "g_src": source, "pipeline_obj": b"pipeline",
                       "flags": []}
            def view(obj, *args):
                return SimpleNamespace(obj=obj, funcs={"f": (".text", 0, 4)},
                                       add_unit=lambda *a: None)
            def retail(v, scope, kind):
                return pipeline_retail if v.obj.kind == "pipeline" else genuine_retail
            comparison = {"exact": compare_exact, "diff": 0 if compare_exact else 2,
                          "len_m": 1, "len_g": 1, "missing": list(missing), "regions": []}
            captured = []
            def run(src, version, flags, temp):
                captured.append(src.decode())
                return b"genuine", None
            with patch.object(P, "clean_path", return_value=cfile), \
                 patch.object(P.A, "prepare_slus", return_value=(context, None)), \
                 patch.object(P.A, "read_elf", return_value=SimpleNamespace(kind="pipeline", unknown=[])), \
                 patch.object(P.A, "read_lnk", return_value=SimpleNamespace(kind="genuine", unknown=list(unknown))), \
                 patch.object(P.A, "View", side_effect=view), \
                 patch.object(P.A, "retail_compare", side_effect=retail), \
                 patch.object(P.A, "compare_units", return_value=comparison), \
                 patch.object(P.A, "genuine_modes", return_value=([(["-q"], False)], False)), \
                 patch.object(P.A, "aspsx_input", side_effect=lambda s, equ=False: s.encode()), \
                 patch.object(P.A, "run_aspsx", side_effect=run), \
                 patch.object(P.A, "aliases", return_value={}):
                return P.prove_compiler_model(row, member), captured

    def test_fresh_selected_stream_proves_and_preserves_neighbour(self):
        proof, sources = self.run_modeled_proof()
        self.assertEqual(proof["model"], "t272")
        self.assertEqual(proof["functions"], ["f"])
        self.assertTrue(proof["comparison"]["exact"])
        self.assertEqual(proof["genuine_retail"], {"diff": 0, "masked": 0, "checked": 1})
        self.assertIn(fn("neighbour"), sources[0])
        self.assertNotIn(fn("f"), sources[0])

    def test_wrong_or_unknown_genuine_object_is_rejected(self):
        for kwargs in ({"compare_exact": False}, {"unknown": ("bad-record",)}, {"missing": ("f",)}):
            with self.subTest(kwargs=kwargs):
                with self.assertRaisesRegex(ValueError, "did not prove"):
                    self.run_modeled_proof(**kwargs)

    def test_masked_or_nonretail_output_is_rejected_on_both_legs(self):
        for kwargs in ({"pipeline_retail": {"diff": 0, "masked": 1, "checked": 1}},
                       {"pipeline_retail": {"diff": 1, "masked": 0, "checked": 1}},
                       {"genuine_retail": {"diff": 0, "masked": 1, "checked": 1}},
                       {"genuine_retail": {"diff": 1, "masked": 0, "checked": 1}}):
            with self.subTest(kwargs=kwargs):
                with self.assertRaisesRegex(ValueError, "masked or not retail-exact|did not prove"):
                    self.run_modeled_proof(**kwargs)


if __name__ == "__main__":
    unittest.main()
