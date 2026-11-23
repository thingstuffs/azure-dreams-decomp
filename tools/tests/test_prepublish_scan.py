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


def disasm_findings(rel, text):
    """scan one throwaway file; return the (rule, text) pairs of the retail-disasm rule."""
    with tempfile.TemporaryDirectory() as d:
        p = Path(d) / rel
        p.parent.mkdir(parents=True, exist_ok=True)
        p.write_text(text)
        return [(r, t) for r, _l, t in ps.scan_file(d, rel, 1 << 20) if r == "retail-disasm"]


def objdump_text(n=6, base=0x1000, header=True):
    """invented objdump -D lines: offset, a made-up word, a mnemonic."""
    ops = ["addiu\tsp,sp,-8", "sw\tra,4(sp)", "move\ta0,a1", "nop", "jr\tra", "nop"]
    lines = ["", "synthetic.bin:     file format binary", "", "Disassembly of section .data:", ""] if header else []
    for i in range(n):
        lines.append(f"{base + 4 * i:x}:\t{0x10000000 + i * 0x111:08x} \t{ops[i % len(ops)]}")
    return "\n".join(lines) + "\n"


def glabel_text(n=5, addr=0x7F000000):
    lines = [".set noat", ".text", "glabel sample_fn"]
    for i in range(n):
        lines.append(f"/* {addr + 4 * i:08X} {0x20000000 + i * 0x101:08X} */ nop")
    return "\n".join(lines) + "\n"


COMPILER_S = (
    '\t.file\t1 "sample.c"\n\n # -G value = 32, Cpu = 3000, ISA = 1\n\t.comm\tsample_var,40\n'
    "\t.text\n\t.globl\tsample_fn\nsample_fn:\n\tlw\t$2,sample_var\n\taddu\t$3,$2,$4\n\tj\t$31\n\tnop\n"
)


class DisassemblyRule(unittest.TestCase):
    def test_objdump_listing_in_disasm_txt_is_caught(self):
        for rel in ("docs/evidence/x.disasm.txt", "docs/evidence/sub/y.disasm.txt", "tools/z.disasm.txt"):
            self.assertEqual([r for r, _t in disasm_findings(rel, objdump_text())], ["retail-disasm"], rel)

    def test_objdump_header_alone_is_caught(self):
        self.assertTrue(disasm_findings("docs/a.disasm.txt", "x.bin:     file format elf32-tradlittlemips\n"))

    def test_short_or_plain_disasm_txt_passes(self):
        self.assertEqual(disasm_findings("docs/a.disasm.txt", objdump_text(n=2, header=False)), [])
        self.assertEqual(disasm_findings("docs/a.disasm.txt", "notes about a listing\n"), [])
        self.assertEqual(disasm_findings("docs/a.txt", objdump_text()), [])      # rule keys on the .disasm.txt name

    def test_glabel_word_listing_in_s_file_is_caught(self):
        self.assertEqual([r for r, _t in disasm_findings("docs/evidence/a.s", glabel_text())], ["retail-disasm"])
        self.assertEqual([r for r, _t in disasm_findings("src/b.S", glabel_text(n=3))], ["retail-disasm"])
        wide = ".text\n" + "".join(f"/* {0x40 + 4 * i:X} {0x80000000 + 4 * i:08X} {0x30000000 + i:08X} */ nop\n" for i in range(4))
        self.assertTrue(disasm_findings("docs/w.s", wide))

    def test_compiler_output_of_our_own_c_passes(self):
        self.assertEqual(disasm_findings("docs/evidence/c.s", COMPILER_S), [])
        self.assertEqual(disasm_findings("tools/x/ASM/PROBE.S", "\tlh\t$2,32767($2)\n\tnop\n"), [])
        self.assertEqual(disasm_findings("docs/evidence/c.s", glabel_text(n=2)), [])     # fewer than three words

    def test_glabel_listing_outside_s_files_is_not_this_rule(self):
        self.assertEqual(disasm_findings("docs/a.md", glabel_text()), [])

    def test_main_reports_the_kind_and_exits_1(self):
        with tempfile.TemporaryDirectory() as d:
            (Path(d) / "docs").mkdir()
            (Path(d) / "docs/q.disasm.txt").write_text(objdump_text())
            self.assertEqual(ps.main(["--root", d, "--no-allowlist"]), 1)
            (Path(d) / "docs/q.disasm.txt").unlink()
            (Path(d) / "docs/q.s").write_text(COMPILER_S)
            self.assertEqual(ps.main(["--root", d, "--no-allowlist"]), 0)


if __name__ == "__main__":
    unittest.main()
