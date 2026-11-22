"""tools/prepublish_scan.py rule `provenance` (R12): no lane/run/batch ids or internal paths in public text.
All fixtures are synthetic."""
import os
import sys
import tempfile
import unittest
from pathlib import Path
from unittest import mock

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))
import prepublish_scan as ps  # noqa: E402


def findings(files):
    """scan a throwaway tree holding `files` ({relpath: text}); return the provenance texts reported."""
    with tempfile.TemporaryDirectory() as d:
        for rel, text in files.items():
            p = Path(d) / rel
            p.parent.mkdir(parents=True, exist_ok=True)
            p.write_text(text)
        out = []
        for rel in files:
            out += [t for r, _l, t in ps.scan_file(d, rel, 1 << 20) if r == "provenance"]
        return out


SHAPES = [
    "disc LBA (r900_sample_a1 loader_receipt.json).",
    "(lane r901w_sample; slus/w_80000000)",
    "a bare r902 tag split it out:",
    "Reconstruction from r903_sample continuation 5;",
    "/* Recovered twin; complete-function proof is in the lane receipt. */",
    "/* micro-lane E 2026-01-01: true base */",
    "the prior lane's size pins",
    "measured on AC999 against 2,842 parameters",
    "see work/sample_lane/_x/y.json",
    "see work/sample_wave/y.json",
    "see BRIEF3 for the order",
    "output of run90 is kept",
]


class ProvenanceRule(unittest.TestCase):
    def test_each_generic_shape_is_caught_in_src_include_and_docs(self):
        for line in SHAPES:
            for rel in ("src/a.c", "include/a.h", "docs/A.md"):
                with self.subTest(line=line, rel=rel):
                    self.assertTrue(findings({rel: "/* " + line + " */\n"}), line)

    def test_code_tokens_and_plain_words_pass(self):
        ok = ("/* terrain height, BriefRandomParticleBody, briefly changes the palette; the lane index "
              "(lane = actor->lane) in the race track */\n#ifndef R108_BANK42_H\n#define R108_BANK42_H\n"
              "create_brief_randomized_particle(); runner = run9;\n")
        self.assertEqual(findings({"src/a.c": ok}), [])

    def test_existing_evidence_citation_is_allowed_missing_one_is_not(self):
        cite = "Evidence: docs/evidence/r900_sample_notes.md.\n"
        self.assertEqual(findings({"src/a.c": "/* " + cite + " */", "docs/evidence/r900_sample_notes.md": "x"}), [])
        self.assertTrue(findings({"src/a.c": "/* " + cite + " */"}))
        self.assertTrue(findings({"src/a.c": "/* see docs/evidence/foo_receipt.json */"}))
        self.assertEqual(findings({"src/a.c": "/* see docs/evidence/foo_receipt.json */",
                                   "docs/evidence/foo_receipt.json": "{}"}), [])

    def test_scope_is_src_include_docs_only(self):
        self.assertEqual(findings({"tools/lanes/x.py": "# BRIEF3, lane r901w_sample, run90\n"}), [])
        self.assertEqual(findings({"ledger/a.jsonl": "r901w_sample\n"}), [])

    def test_allowlist_hides_text_with_regex(self):
        with tempfile.TemporaryDirectory() as d:
            al = Path(d) / "al.txt"
            al.write_text("src/a.c provenance ~ ^run90$\n")
            ents = ps.load_allowlist(str(al))
            self.assertTrue(ps.allowed(ents, "provenance", "src/a.c", "run90"))
            self.assertFalse(ps.allowed(ents, "provenance", "src/a.c", "run91"))
            self.assertFalse(ps.allowed(ents, "provenance", "src/b.c", "run90"))

    def test_main_exits_1_on_finding(self):
        with tempfile.TemporaryDirectory() as d:
            (Path(d) / "src").mkdir()
            (Path(d) / "src/a.c").write_text("/* (lane r901w_sample) */\n")
            self.assertEqual(ps.main(["--root", d, "--no-allowlist"]), 1)
            (Path(d) / "src/a.c").write_text("/* nothing */\n")
            self.assertEqual(ps.main(["--root", d, "--no-allowlist"]), 0)


class ExtraPatterns(unittest.TestCase):
    def run_with(self, patterns, text):
        with tempfile.TemporaryDirectory() as d:
            f = Path(d) / "extra.txt"
            f.write_text(patterns)
            with mock.patch.dict(os.environ, {"PREPUBLISH_EXTRA_PATTERNS": str(f)}):
                return findings({"src/a.c": text})

    def test_hit_and_miss(self):
        pats = "# made-up words\n\n(?<![A-Za-z0-9])modelword(?![a-z0-9])\n"
        self.assertEqual(self.run_with(pats, "/* found by ModelWord_x */"), ["ModelWord"])
        self.assertEqual(self.run_with(pats, "/* modelwords and amodelword */"), [])

    def test_unset_or_missing_file_adds_nothing(self):
        with mock.patch.dict(os.environ, {}, clear=False):
            os.environ.pop("PREPUBLISH_EXTRA_PATTERNS", None)
            self.assertEqual(findings({"src/a.c": "/* modelword */"}), [])
        with mock.patch.dict(os.environ, {"PREPUBLISH_EXTRA_PATTERNS": "/nonexistent/none.txt"}):
            self.assertEqual(findings({"src/a.c": "/* modelword */"}), [])

    def test_bad_regex_is_an_error_with_line_number(self):
        with tempfile.TemporaryDirectory() as d:
            f = Path(d) / "extra.txt"
            f.write_text("# c\nokword\n(unclosed\n")
            with mock.patch.dict(os.environ, {"PREPUBLISH_EXTRA_PATTERNS": str(f)}):
                with self.assertRaises(SystemExit) as cm:
                    ps.extra_patterns()
            self.assertEqual(cm.exception.code, 2)


if __name__ == "__main__":
    unittest.main()
