"""Semantic validation tests for the evidence-led pin research ledger."""
import contextlib
import hashlib
import io
import json
from pathlib import Path
import sys
import tempfile
import unittest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import pin_research as research


def digest(text):
    return hashlib.sha256(text.encode()).hexdigest()


def review(state="pending", *refs):
    return {"state": state, "evidence_refs": list(refs)}


def case_for(text):
    return {
        "id": "test/func",
        "title": "test case",
        "status": "unresolved",
        "claim": {"level": "unresolved", "summary": "The cause is still open."},
        "source": {"path": "src/test.c", "sha256": digest(text)},
        "retail": {
            "identity": {"value": "test/func", "confidence": "high", "basis": "fixture"},
            "recipe": {"value": "2.7.2 -G0", "confidence": "high", "basis": "fixture"},
        },
        "causal": {
            "question": "Which source fact creates the retail order?",
            "prediction": "The candidate changes the first divergent pass in the predicted way.",
        },
        "evidence": [],
        "next_experiment": {
            "action": "Compile the bounded candidate pair.",
            "measurement": "Compare exact bytes and the first divergent RTL pass.",
            "success_criterion": "The candidate is exact at the fixed recipe.",
            "failure_criterion": "Both candidates retain the original residue.",
            "bounds": "Two candidates at one fixed recipe.",
        },
        "verification": {
            "exact_bytes": review(),
            "semantic_review": review(),
            "caller_review": review(),
            "publication_gate": {**review(), "kind": "overlay_window"},
        },
        "transfer": {"enabled": False},
    }


def ledger(case):
    return {
        "schema_version": 1,
        "baseline": {"pins": 6103, "pinned_rows": 1284, "target_pins": 0},
        "cases": [case],
    }


class PinResearchTests(unittest.TestCase):
    def setUp(self):
        self.temp = tempfile.TemporaryDirectory()
        self.root = Path(self.temp.name)
        (self.root / "src").mkdir()
        self.text = "void f(void) {}\n"
        (self.root / "src/test.c").write_text(self.text)
        (self.root / "receipt.txt").write_text("receipt\n")

    def tearDown(self):
        self.temp.cleanup()

    def artifact(self):
        return {"path": "receipt.txt"}

    def bind_candidate(self, case):
        (self.root / "candidate.c").write_text(self.text)
        case["candidate"] = {
            "path": "candidate.c",
            "sha256": digest(self.text),
            "base_source_sha256": case["source"]["sha256"],
            "recipe": "2.7.2 -G0",
        }

    def test_valid_open_case_and_stale_source_detection(self):
        data = ledger(case_for(self.text))
        self.assertEqual(research.validate_ledger(data, self.root), [])
        (self.root / "src/test.c").write_text("void f(void) { return; }\n")
        errors = research.validate_ledger(data, self.root)
        self.assertTrue(any("stale source hash" in error for error in errors), errors)

    def test_historical_baseline_can_advance_without_code_change(self):
        data = ledger(case_for(self.text))
        data["baseline"].update({"pins": 42, "pinned_rows": 7})
        self.assertEqual(research.validate_ledger(data, self.root), [])

    def test_evidence_artifact_must_exist(self):
        case = case_for(self.text)
        case["evidence"] = [{
            "id": "missing",
            "kind": "observation",
            "summary": "Claim with no durable receipt.",
            "artifact": {"path": "missing.txt"},
        }]
        errors = research.validate_ledger(ledger(case), self.root)
        self.assertTrue(any("missing artifact" in error for error in errors), errors)

    def test_bounded_negative_requires_tested_and_untested_scope(self):
        case = case_for(self.text)
        case["evidence"] = [{
            "id": "neg",
            "kind": "bounded_negative",
            "summary": "No exact result.",
            "artifact": self.artifact(),
            "bounds": {"tested": "four spellings"},
        }]
        errors = research.validate_ledger(ledger(case), self.root)
        self.assertTrue(any("bounds.untested" in error for error in errors), errors)
        case["evidence"][0]["bounds"]["untested"] = "whole-region reconstruction"
        self.assertEqual(research.validate_ledger(ledger(case), self.root), [])

    def test_bounded_negative_cannot_support_impossibility(self):
        case = case_for(self.text)
        case["claim"] = {"level": "impossibility", "summary": "Claimed impossible."}
        case["evidence"] = [{
            "id": "neg",
            "kind": "bounded_negative",
            "summary": "A finite menu failed.",
            "artifact": self.artifact(),
            "bounds": {"tested": "ten forms", "untested": "other source shapes"},
        }]
        errors = research.validate_ledger(ledger(case), self.root)
        self.assertTrue(any("bounded negatives remain unresolved" in error for error in errors), errors)

    def test_repair_verified_requires_exact_semantic_and_caller_reviews(self):
        case = case_for(self.text)
        case["status"] = "repair_verified"
        self.bind_candidate(case)
        case["evidence"] = [{
            "id": "candidate",
            "kind": "positive_candidate",
            "summary": "The candidate matched.",
            "artifact": self.artifact(),
            "candidate": {
                "source_change": "remove one pin",
                "recipe": "2.7.2 -G0",
                "result": "exact",
                "remaining_question": "semantic review",
            },
        }]
        errors = research.validate_ledger(ledger(case), self.root)
        self.assertTrue(any("requires exact_bytes=pass" in error for error in errors), errors)
        self.assertTrue(any("requires semantic_review=pass" in error for error in errors), errors)
        self.assertTrue(any("requires caller_review=pass/not_applicable" in error for error in errors), errors)
        case["verification"].update({
            "exact_bytes": review("pass", "candidate"),
            "semantic_review": review("pass", "candidate"),
            "caller_review": review("not_applicable"),
        })
        self.assertEqual(research.validate_ledger(ledger(case), self.root), [])
        (self.root / "candidate.c").write_text("changed candidate\n")
        errors = research.validate_ledger(ledger(case), self.root)
        self.assertTrue(any("stale candidate hash" in error for error in errors), errors)

    def test_transfer_needs_distinct_independent_controls(self):
        case = case_for(self.text)
        case["status"] = "transfer_testing"
        self.bind_candidate(case)
        case["evidence"] = [{
            "id": "repair",
            "kind": "positive_candidate",
            "summary": "Origin repair is exact and reviewed.",
            "artifact": self.artifact(),
            "candidate": {
                "source_change": "repair",
                "recipe": "2.7.2 -G0",
                "result": "exact",
                "remaining_question": "family transfer",
            },
        }]
        case["verification"].update({
            "exact_bytes": review("pass", "repair"),
            "semantic_review": review("pass", "repair"),
            "caller_review": review("not_applicable"),
        })
        control = {
            "case_id": "test/func",
            "independent": False,
            "expected": "outcome",
            "source_path": "src/test.c",
            "source_sha256": digest(self.text),
            "result": "pending",
            "baseline_exact_bytes": "pending",
            "observed": "pending",
            "evidence_refs": [],
        }
        case["transfer"] = {
            "enabled": True,
            "family": "fixture family",
            "rule": "same source relation",
            "controls": {"positive": dict(control), "negative": dict(control)},
        }
        errors = research.validate_ledger(ledger(case), self.root)
        self.assertTrue(any("independent: must be true" in error for error in errors), errors)
        self.assertTrue(any("must be distinct" in error for error in errors), errors)
        self.assertTrue(any("must differ from the exemplar" in error for error in errors), errors)

    def test_resolved_transfer_is_landable_only_after_all_gates(self):
        case = case_for(self.text)
        case["status"] = "resolved"
        case["next_experiment"] = None
        self.bind_candidate(case)
        case["claim"] = {"level": "verified_repair", "summary": "Resolved by a verified repair."}
        case["evidence"] = [{
            "id": "repair",
            "kind": "positive_candidate",
            "summary": "Exact repair with review receipts.",
            "artifact": self.artifact(),
            "candidate": {
                "source_change": "repair",
                "recipe": "2.7.2 -G0",
                "result": "exact",
                "remaining_question": "none",
            },
        }]
        case["verification"] = {
            "exact_bytes": review("pass", "repair"),
            "semantic_review": review("pass", "repair"),
            "caller_review": review("not_applicable"),
            "publication_gate": {**review("pass", "repair"), "kind": "overlay_window"},
        }
        def control(case_id, observed):
            return {
                "case_id": case_id,
                "independent": True,
                "expected": "measured outcome",
                "source_path": "src/test.c",
                "source_sha256": digest(self.text),
                "result": "pass",
                "baseline_exact_bytes": "pass",
                "observed": observed,
                "evidence_refs": ["repair"],
            }
        case["transfer"] = {
            "enabled": True,
            "family": "fixture family",
            "rule": "verified rule",
            "controls": {
                "positive": control("test/positive", "repair_exact"),
                "negative": control("test/negative", "mismatch_as_predicted"),
            },
        }
        self.assertEqual(research.validate_ledger(ledger(case), self.root), [])
        self.assertTrue(research.is_landable(case))
        case["transfer"]["controls"]["negative"]["baseline_exact_bytes"] = "pending"
        errors = research.validate_ledger(ledger(case), self.root)
        self.assertTrue(any("resolved transfer requires" in error for error in errors), errors)
        self.assertFalse(research.is_landable(case))

    def test_cli_returns_failure_for_stale_ledger(self):
        data = ledger(case_for(self.text))
        path = self.root / "cases.json"
        path.write_text(json.dumps(data))
        (self.root / "src/test.c").write_text("changed\n")
        stderr = io.StringIO()
        with contextlib.redirect_stderr(stderr):
            rc = research.main(["--ledger", str(path), "--root", str(self.root), "validate"])
        self.assertEqual(rc, 1)
        self.assertIn("stale source hash", stderr.getvalue())

    def test_seed_ledger_is_semantically_valid(self):
        if not research.DEFAULT_LEDGER.exists():
            self.skipTest("seed ledger not written yet")
        data = research.load_ledger(research.DEFAULT_LEDGER)
        self.assertEqual(research.validate_ledger(data, research.ROOT), [])


if __name__ == "__main__":
    unittest.main()
