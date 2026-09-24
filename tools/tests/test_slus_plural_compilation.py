"""Fail-closed tests for verify.compile_slus_units."""

from __future__ import annotations

import sys
import tempfile
import unittest
from pathlib import Path
from types import SimpleNamespace
from unittest.mock import patch

REPO = Path(__file__).resolve().parents[2]
sys.path[:0] = [str(REPO / "tools"), str(REPO / "tools/build")]
import verify as V  # noqa: E402

A = "func_80030000"
B = "func_80030010"
C = "func_80030020"
EXTRA = "func_80030030"


class PluralCompilationTests(unittest.TestCase):
    def setUp(self):
        temp = tempfile.TemporaryDirectory(prefix="slus_plural_compile_")
        self.addCleanup(temp.cleanup)
        self.root = Path(temp.name)
        for folder in ("config", "include", "raw/include", "out"):
            (self.root / folder).mkdir(parents=True)
        (self.root / "config/names.tsv").write_text("")
        self.candidate = self.root / "candidate.c"
        self.candidate.write_text("int candidate(void) { return 1; }\n")
        self.code_file = self.root / "remainder.c"
        self.code_file.write_text("int remainder(void) { return 1; }\n")
        self.owner_file = self.root / "owner.c"
        self.owner_file.write_text("int owner(void) { return 2; }\n")
        self.row = {"id": "slus/code", "kind": "slus", "c_path": "src/code.c",
                    "cell": "2.7.2", "flags": "", "row_asflags": ""}
        self.units = [
            {"source": "src/code.c", "cfile": self.code_file,
             "recipe": {"ccver": "2.7.2", "ccflags": "-G0", "asflags": ""},
             "functions": [C], "expected_functions": [C], "role": "remainder"},
            {"source": "src/owner.c", "cfile": self.owner_file,
             "recipe": {"ccver": "2.8.1", "ccflags": "-fno-schedule-insns", "asflags": "-q"},
             "functions": [A], "expected_functions": [A, B], "role": "module"},
        ]

    def invoke(self, emitted=None, *, aliases=None, fail_on=None, fingerprints=None,
               include_root=None, mutate_candidate=False):
        emitted = emitted or {"remainder.c": [C], "owner.c": [A, B]}
        aliases = aliases or {}
        seen = []

        def compile_one(physical_row, cfile, outdir, inc, root):
            name = Path(cfile).name
            seen.append({"source": name, "cell": physical_row["cell"],
                         "flags": physical_row["flags"],
                         "asflags": physical_row["row_asflags"],
                         "include": Path(inc), "root": Path(root)})
            if name == fail_on:
                return None, "gcc: simulated failure"
            output = Path(outdir) / "a.o"
            output.parent.mkdir(parents=True, exist_ok=True)
            output.write_bytes(name.encode())
            if mutate_candidate and name == "owner.c":
                self.candidate.write_text(self.candidate.read_text() + "/* drift */\n")
            return output, None

        def read_one(blob):
            names = emitted[blob.decode()]
            return SimpleNamespace(symbols={name: (".text", i + 1, "func", 0)
                                            for i, name in enumerate(names)})

        fp = ["fp-stable", "fp-stable"] if fingerprints is None else fingerprints
        with patch("slus_module_context.compilation_sources", return_value=self.units), \
             patch("slus_module_context.fingerprint", side_effect=fp), \
             patch("slus_partitions.read_aliases", return_value=aliases), \
             patch.object(V, "_compile_slus_source", side_effect=compile_one), \
             patch("fidelity.objread.read_elf", side_effect=read_one):
            result = V.compile_slus_units(self.row, self.candidate, self.root / "out",
                                          include_root=include_root, root=self.root)
        return result, seen

    def test_complete_scopes_use_each_physical_recipe_and_current_headers(self):
        (results, error), seen = self.invoke()
        self.assertIsNone(error)
        self.assertEqual([unit["source"] for unit in results], ["src/code.c", "src/owner.c"])
        self.assertEqual([unit["functions"] for unit in results], [[C], [A]])
        self.assertEqual([unit["expected_functions"] for unit in results], [[C], [A, B]])
        self.assertEqual([unit["module_fingerprint"] for unit in results], ["fp-stable"] * 2)
        self.assertEqual([(x["cell"], x["flags"], x["asflags"]) for x in seen],
                         [("2.7.2", "-G0", ""), ("2.8.1", "-fno-schedule-insns", "-q")])
        self.assertEqual([x["include"] for x in seen], [self.root / "include"] * 2)
        self.assertEqual([x["root"] for x in seen], [self.root] * 2)

    def test_extra_missing_and_alias_duplicate_emission_are_refused(self):
        cases = [
            ("extra", {"remainder.c": [C, EXTRA], "owner.c": [A, B]}, {}),
            ("missing", {"remainder.c": [C], "owner.c": [A]}, {}),
            ("duplicate", {"remainder.c": [C], "owner.c": [A, "alias_a", B]},
             {"alias_a": A}),
        ]
        for label, emitted, aliases in cases:
            with self.subTest(label=label):
                (results, error), seen = self.invoke(emitted, aliases=aliases)
                self.assertIsNone(results)
                self.assertIn("emitted function coverage differs", error)
                self.assertEqual(len(seen), 2)

    def test_noncurrent_headers_are_rejected_before_compilation(self):
        (results, error), seen = self.invoke(include_root=self.root / "raw/include")
        self.assertIsNone(results)
        self.assertIn("current shared headers", error)
        self.assertEqual(seen, [])

    def test_fingerprint_and_candidate_drift_discard_compiled_results(self):
        for label, kwargs in (("fingerprint", {"fingerprints": ["before", "after"]}),
                              ("candidate", {"mutate_candidate": True})):
            with self.subTest(label=label):
                self.candidate.write_text("int candidate(void) { return 1; }\n")
                (results, error), seen = self.invoke(**kwargs)
                self.assertIsNone(results)
                self.assertIn("compilation inputs changed", error)
                self.assertEqual(len(seen), 2)

    def test_second_compiler_failure_returns_no_partial_success(self):
        (results, error), seen = self.invoke(fail_on="owner.c")
        self.assertIsNone(results)
        self.assertIn("src/owner.c: gcc: simulated failure", error)
        self.assertEqual([x["source"] for x in seen], ["remainder.c", "owner.c"])


if __name__ == "__main__":
    unittest.main()
