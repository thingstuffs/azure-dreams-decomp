"""Contract tests for SLUS partition-connected plural compilation."""

from __future__ import annotations

import copy
import hashlib
import json
import shutil
import subprocess
import sys
import tempfile
import unittest
from pathlib import Path

REPO = Path(__file__).resolve().parents[2]
sys.path[:0] = [str(REPO / "tools"), str(REPO / "tools/build")]
import slus_partitions as P  # noqa: E402

import slus_module_context as C  # noqa: E402

F = {key: f"func_80030{index:03X}" for key, index in
     (("a", 0), ("b", 0x10), ("c", 0x20), ("x", 0x30),
      ("y", 0x40), ("d", 0x50), ("e", 0x60))}
PARENT_RECIPE = {"ccver": "2.7.2", "ccflags": "", "asflags": ""}
ALPHA_RECIPE = {"ccver": "2.8.1", "ccflags": "", "asflags": ""}
BETA_RECIPE = {"ccver": "2.7.2-cdk", "ccflags": "", "asflags": ""}


def body(key: str, value: int) -> str:
    return f"int {F[key]}(void) {{ return {value}; }}\n"


def row(stem: str, recipe: dict | None = None) -> dict:
    recipe = recipe or PARENT_RECIPE
    return {"kind": "slus", "id": "slus/" + stem, "c_path": f"src/{stem}.c",
            "cell": recipe["ccver"], "cfg": recipe["ccver"],
            "flags": recipe["ccflags"], "row_asflags": recipe["asflags"]}


class PluralContextTests(unittest.TestCase):
    def setUp(self):
        temp = tempfile.TemporaryDirectory(prefix="slus_plural_")
        self.addCleanup(temp.cleanup)
        self.root = Path(temp.name)
        for directory in ("config", "ledger/splits", "src/slus", "raw/slus",
                          "include/slus", "scratch"):
            (self.root / directory).mkdir(parents=True)

        self.original = {
            "code": '#include "shared.h"\n' + body("a", 10) + body("b", 20) + body("c", 30),
            "code2": '#include "shared.h"\n' + body("d", 40) + body("e", 50),
            "a": body("x", 100),
            "b": body("y", 200),
            "plain": "int plain(void) { return 9; }\n",
        }
        for stem, source in self.original.items():
            (self.root / "src/slus" / (stem + ".c")).write_text(source)
            (self.root / "raw/slus" / (stem + ".c")).write_text(source)
        header = "\n".join(f"int {name}(void);" for name in F.values()) + "\n"
        (self.root / "include/slus/shared.h").write_text(header)
        (self.root / "src/slus/alpha.c").write_text(
            '#include "shared.h"\n'
            '#include "../build/partition_sources/code__alpha.c"\n'
            '#include "a.c"\n')
        (self.root / "src/slus/beta.c").write_text(
            '#include "shared.h"\n'
            '#include "../build/partition_sources/code__beta.c"\n'
            '#include "../build/partition_sources/code2__beta.c"\n'
            '#include "b.c"\n')

        self.modules = [
            {"name": "alpha", "source": "src/alpha.c", "headers": ["include/slus/shared.h"],
             "members": [{"id": "slus/a", "source": "src/a.c", "functions": [F["x"]]}],
             "recipe": ALPHA_RECIPE, "data": [], "evidence": "docs/evidence/alpha.md"},
            {"name": "beta", "source": "src/beta.c", "headers": ["include/slus/shared.h"],
             "members": [{"id": "slus/b", "source": "src/b.c", "functions": [F["y"]]}],
             "recipe": BETA_RECIPE, "data": [], "evidence": "docs/evidence/beta.md"},
        ]
        self.parents = [
            {"id": "slus/code", "source": "src/code.c",
             "raw_sha256": hashlib.sha256(self.original["code"].encode()).hexdigest(),
             "recipe": PARENT_RECIPE, "functions": [F["a"], F["b"], F["c"]],
             "parts": [{"module": "alpha", "functions": [F["a"]]},
                       {"module": "beta", "functions": [F["b"]]}]},
            {"id": "slus/code2", "source": "src/code2.c",
             "raw_sha256": hashlib.sha256(self.original["code2"].encode()).hexdigest(),
             "recipe": PARENT_RECIPE, "functions": [F["d"], F["e"]],
             "parts": [{"module": "beta", "functions": [F["d"]]}]},
        ]
        self._write_json("config/slus_modules.json", {"version": 1, "modules": self.modules})
        self._write_json("config/slus_partitions.json", {"version": 1, "parents": self.parents})
        (self.root / "config/names.tsv").write_text("0\tfunc_80030900\talias_900\n")
        edges = [
            {"src": "src/code.c", "out": "build/src/code.o", **PARENT_RECIPE},
            {"src": "src/code2.c", "out": "build/src/code2.o", **PARENT_RECIPE},
            {"src": "src/a.c", "out": "build/src/a.o", **ALPHA_RECIPE},
            {"src": "src/b.c", "out": "build/src/b.o", **BETA_RECIPE},
            {"src": "src/plain.c", "out": "build/src/plain.o", **PARENT_RECIPE},
        ]
        (self.root / "ledger/splits/slus.jsonl").write_text(
            "".join(json.dumps(edge) + "\n" for edge in edges))
        self.assertTrue(P.validate_context(P.load_plan(self.root / "config/slus_partitions.json"),
                                           C.modules(self.root), edges, self.root / "raw/slus",
                                           P.read_aliases(self.root / "config/names.tsv")))

    def _write_json(self, relative: str, value):
        (self.root / relative).write_text(json.dumps(value, indent=2) + "\n")

    def _units(self, stem: str, candidate: Path | None = None, folder: str | None = None):
        return C.compilation_sources(row(stem, {"a": ALPHA_RECIPE, "b": BETA_RECIPE}.get(stem)),
                                     candidate or self.root / "src/slus" / (stem + ".c"),
                                     self.root / "scratch" / (folder or stem), self.root)

    def test_parent_and_whole_member_scopes_are_explicit(self):
        code = {unit["source"]: unit for unit in self._units("code")}
        self.assertEqual(set(code), {"src/code.c", "src/alpha.c", "src/beta.c"})
        expected = {
            "src/code.c": ("remainder", {F["c"]}, {F["c"]}, PARENT_RECIPE),
            "src/alpha.c": ("module", {F["a"]}, {F["a"], F["x"]}, ALPHA_RECIPE),
            "src/beta.c": ("module", {F["b"]}, {F["b"], F["d"], F["y"]}, BETA_RECIPE),
        }
        for source, (role, subset, whole, recipe) in expected.items():
            unit = code[source]
            self.assertEqual(unit["role"], role)
            self.assertEqual(set(unit["functions"]), subset)
            self.assertEqual(set(unit["expected_functions"]), whole)
            self.assertEqual(unit["recipe"], recipe)
            self.assertIsInstance(unit["cfile"], Path)
            self.assertTrue(unit["cfile"].is_file())
        code2 = {unit["source"]: unit for unit in self._units("code2")}
        self.assertEqual(set(code2), {"src/code2.c", "src/beta.c"})
        self.assertEqual(set(code2["src/beta.c"]["functions"]), {F["d"]})
        member = self._units("b")[0]
        self.assertEqual(member["source"], "src/beta.c")
        self.assertEqual(member["role"], "module")
        self.assertEqual(set(member["functions"]), {F["y"]})
        self.assertEqual(set(member["expected_functions"]), {F["b"], F["d"], F["y"]})

    @unittest.skipUnless(shutil.which("cc"), "host C compiler unavailable")
    def test_parent_candidate_updates_moved_and_remainder_bodies(self):
        candidate = self.root / "scratch/candidate_code.c"
        candidate.write_text('#include "shared.h"\n' + body("a", 11) + body("b", 21) + body("c", 31))
        outdir = self.root / "scratch/candidate_out"
        units = self._units("code", candidate, "candidate_out")
        by_source = {unit["source"]: unit["cfile"] for unit in units}
        code2_remainder = outdir / "partition_context/build/partition_sources/code2.c"
        self.assertTrue(code2_remainder.is_file())
        generated = [p.read_text() for p in (outdir / "partition_context").rglob("*.c")]
        for number in (11, 21, 31):
            self.assertTrue(any(f"return {number};" in text for text in generated))
        for stem, source in self.original.items():
            self.assertEqual((self.root / "src/slus" / (stem + ".c")).read_text(), source)
        main = self.root / "scratch/main.c"
        names = [F[key] for key in ("a", "b", "c", "x", "y", "d", "e")]
        main.write_text('#include "shared.h"\nint main(void) { return (' +
                        " + ".join(name + "()" for name in names) + ') != 453; }\n')
        exe = self.root / "scratch/program"
        subprocess.run(["cc", "-std=c99", "-I", str(self.root / "include/slus"),
                        *(str(by_source[source]) for source in ("src/code.c", "src/alpha.c", "src/beta.c")),
                        str(code2_remainder), str(main), "-o", str(exe)], check=True,
                       text=True, capture_output=True)
        self.assertEqual(subprocess.run([str(exe)], check=False).returncode, 0)

    @unittest.skipUnless(shutil.which("cc"), "host C compiler unavailable")
    def test_connected_whole_member_candidate_keeps_moved_parent_scope(self):
        candidate = self.root / "scratch/candidate_a.c"
        candidate.write_text(body("x", 101))
        unit = self._units("a", candidate, "member_out")[0]
        self.assertEqual(unit["source"], "src/alpha.c")
        self.assertEqual(set(unit["functions"]), {F["x"]})
        self.assertEqual(set(unit["expected_functions"]), {F["a"], F["x"]})
        main = self.root / "scratch/member_main.c"
        main.write_text('#include "shared.h"\nint main(void) { return (' +
                        F["a"] + '() + ' + F["x"] + '()) != 111; }\n')
        exe = self.root / "scratch/member_program"
        subprocess.run(["cc", "-std=c99", "-I", str(self.root / "include/slus"),
                        str(unit["cfile"]), str(main), "-o", str(exe)], check=True,
                       text=True, capture_output=True)
        self.assertEqual(subprocess.run([str(exe)], check=False).returncode, 0)
        self.assertEqual((self.root / "src/slus/a.c").read_text(), self.original["a"])

    def test_connected_fingerprint_tracks_every_input_class(self):
        rows = [row(stem, {"a": ALPHA_RECIPE, "b": BETA_RECIPE}.get(stem))
                for stem in ("code", "code2", "a", "b")]
        original = C.fingerprint(rows[0], self.root)
        self.assertTrue(original)
        for item in rows[1:]:
            self.assertEqual(C.fingerprint(item, self.root), original)
        for relative in ("src/slus/code.c", "src/slus/code2.c", "src/slus/a.c", "src/slus/b.c",
                         "src/slus/alpha.c", "src/slus/beta.c", "include/slus/shared.h"):
            path = self.root / relative
            old = path.read_text()
            with self.subTest(relative=relative):
                path.write_text(old + "\n/* fingerprint edit */\n")
                self.assertNotEqual(C.fingerprint(rows[0], self.root), original)
                path.write_text(old)
        self.assertEqual(C.fingerprint(rows[0], self.root), original)
        names = self.root / "config/names.tsv"
        names.write_text("0\tfunc_80030900\talias_901\n")
        self.assertNotEqual(C.fingerprint(rows[0], self.root), original)
        names.write_text("0\tfunc_80030900\talias_900\n")
        changed = copy.deepcopy(self.parents)
        changed[0]["parts"][0]["functions"] = [F["b"]]
        changed[0]["parts"][1]["functions"] = [F["a"]]
        self._write_json("config/slus_partitions.json", {"version": 1, "parents": changed})
        self.assertNotEqual(C.fingerprint(rows[0], self.root), original)

    def test_singular_apis_refuse_connected_rows_but_raw_is_standalone(self):
        for stem in ("code", "code2", "a", "b"):
            item = row(stem, {"a": ALPHA_RECIPE, "b": BETA_RECIPE}.get(stem))
            with self.subTest(stem=stem):
                with self.assertRaises(ValueError):
                    C.membership(item, self.root)
                with self.assertRaises(ValueError):
                    C.physical_stem(stem, self.root)
                with self.assertRaises(ValueError):
                    C.require_individual_recipe(item, self.root)
                with self.assertRaises(ValueError):
                    C.compilation_source(item, self.root / "src/slus" / (stem + ".c"),
                                         self.root / "scratch/singular", self.root)
                raw = self.root / "raw/slus" / (stem + ".c")
                self.assertEqual(C.compilation_source(item, raw, self.root / "scratch", self.root), raw)
                unit = C.compilation_sources(item, raw, self.root / "scratch/raw", self.root)[0]
                self.assertEqual(unit["role"], "raw")
                self.assertEqual(unit["cfile"], raw)

    def test_unconnected_row_keeps_standalone_behavior(self):
        plain = row("plain")
        candidate = self.root / "src/slus/plain.c"
        self.assertIsNone(C.membership(plain, self.root))
        self.assertIsNone(C.fingerprint(plain, self.root))
        self.assertEqual(C.physical_stem("plain", self.root), "plain")
        self.assertIsNone(C.require_individual_recipe(plain, self.root))
        self.assertEqual(C.compilation_source(plain, candidate, self.root / "scratch", self.root), candidate)
        units = self._units("plain")
        self.assertEqual(len(units), 1)
        self.assertEqual(units[0]["role"], "standalone")
        self.assertEqual(units[0]["cfile"], candidate)


if __name__ == "__main__":
    unittest.main()
