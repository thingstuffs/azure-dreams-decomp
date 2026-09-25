"""Partition-only build contracts against this repository's installed tools."""

from __future__ import annotations

import copy
import hashlib
import json
from pathlib import Path
import subprocess
import sys
import tempfile
import unittest

REPO = Path(__file__).resolve().parents[2]
TOOLS = REPO / "tools/build"
sys.path.insert(0, str(TOOLS))
import slus_modules as M  # noqa: E402
import slus_partitions as P  # noqa: E402

assert Path(M.__file__).resolve() == (TOOLS / "slus_modules.py").resolve()
assert Path(P.__file__).resolve() == (TOOLS / "slus_partitions.py").resolve()

RECIPE = {"ccver": "2.7.2-cdk", "ccflags": "", "asflags": ""}
PARENT_RECIPES = {"code.c": {"ccver": "2.7.2", "ccflags": "", "asflags": ""},
                  "code2.c": {"ccver": "2.8.1", "ccflags": "", "asflags": ""}}
CODE_A, CODE_B = "func_80030000", "func_80030010"
CODE2_A, CODE2_B = "func_80040000", "func_80040010"
SOURCE = {
    "code.c": f"int {CODE_A}(void) {{ return 1; }}\nint {CODE_B}(void) {{ return 2; }}\n",
    "code2.c": f"int {CODE2_A}(void) {{ return 3; }}\nint {CODE2_B}(void) {{ return 4; }}\n",
}


def owner() -> dict:
    return {"name": "partition_owner", "source": "src/partition_owner.c",
            "partition_only": True, "members": [], "headers": [],
            "recipe": dict(RECIPE), "data": [],
            "evidence": "docs/evidence/partition_owner.md"}


def parents() -> list[dict]:
    result = []
    for filename, moved, remaining in (("code.c", CODE_A, CODE_B),
                                       ("code2.c", CODE2_A, CODE2_B)):
        result.append({"id": "slus/" + Path(filename).stem,
                       "source": "src/" + filename,
                       "raw_sha256": hashlib.sha256(SOURCE[filename].encode()).hexdigest(),
                       "recipe": dict(PARENT_RECIPES[filename]),
                       "functions": [moved, remaining],
                       "parts": [{"module": "partition_owner", "functions": [moved]}]})
    return result


def edge(source: str) -> dict:
    recipe = RECIPE if source == "src/partition_owner.c" else PARENT_RECIPES[Path(source).name]
    return {"src": source, "out": "build/" + source[:-2] + ".o", **recipe}


class PartitionOnlyBuildTest(unittest.TestCase):
    def setUp(self) -> None:
        self.tmp = tempfile.TemporaryDirectory(prefix="partition_only_build_")
        self.addCleanup(self.tmp.cleanup)
        self.root = Path(self.tmp.name)
        for directory in ("config/generated", "src", "raw/slus", "build", "assets"):
            (self.root / directory).mkdir(parents=True, exist_ok=True)
        (self.root / "tools").symlink_to(TOOLS, target_is_directory=True)
        for filename, body in SOURCE.items():
            (self.root / "src" / filename).write_text(body)
            (self.root / "raw/slus" / filename).write_text(body)
        (self.root / "src/partition_owner.c").write_text("/* includes generated parts */\n")
        (self.root / "config/names.tsv").write_text("")
        (self.root / "build/slus_006.14.ld").write_text("SECTIONS { .text : { build/src/code.o(.text); } }\n")
        (self.root / "config/generated/slus_006.14.undefined_funcs.txt").write_text("")
        (self.root / "config/generated/slus_006.14.undefined_syms.txt").write_text("")
        self.manifest = self.root / "config/slus_modules.json"
        self.plan = self.root / "config/slus_partitions.json"
        self.save()

    def save(self, modules=None, plan=None) -> None:
        self.manifest.write_text(json.dumps({"version": 1, "modules":
                                             [owner()] if modules is None else modules}))
        if plan is None:
            plan = parents()
        self.plan.write_text(json.dumps({"version": 1, "parents": plan}))

    def configure(self) -> subprocess.CompletedProcess:
        return subprocess.run((sys.executable, "tools/configure.py"), cwd=self.root,
                              capture_output=True, text=True)

    def test_two_parent_parts_have_no_fake_logical_anchor(self) -> None:
        modules = M.load_manifest(self.manifest)
        plan = P.load_plan(self.plan)
        self.assertEqual(modules[0]["partition_only"], True)
        self.assertEqual(modules[0]["members"], [])
        logical = [edge("src/code.c"), edge("src/code2.c")]
        self.assertTrue(P.validate_context(plan, modules, logical, self.root / "raw/slus"))
        expected = P.expected_units(plan, modules)
        self.assertEqual(expected["src/partition_owner.c"], {CODE_A, CODE2_A})
        self.assertEqual(expected["src/code.c"], {CODE_B})
        self.assertEqual(expected["src/code2.c"], {CODE2_B})
        P.check_emitted(expected, {source: sorted(funcs) for source, funcs in expected.items()})
        physical = [edge("src/partition_owner.c"), *logical]
        projected = M.logical_edges(physical, modules)
        self.assertEqual(projected, sorted(logical, key=lambda e: e["src"]))
        self.assertNotIn("src/partition_owner.c", {row["src"] for row in projected})
        result = self.configure()
        self.assertEqual(result.returncode, 0, result.stderr)
        ninja = (self.root / "build.ninja").read_text()
        self.assertIn("build build/src/partition_owner.o: cc src/partition_owner.c", ninja)
        self.assertIn("build/partition_sources/code__partition_owner.c", ninja)
        self.assertIn("build/partition_sources/code2__partition_owner.c", ninja)

    def test_schema_requires_true_and_exactly_empty_members(self) -> None:
        bad_values = (False, 0, 1, "true", None, [])
        for value in bad_values:
            with self.subTest(value=value):
                module = owner(); module["partition_only"] = value
                self.save(modules=[module])
                with self.assertRaisesRegex(M.ModuleError, "partition_only must be true"):
                    M.load_manifest(self.manifest)
                with self.assertRaisesRegex(M.ModuleError, "partition_only must be true"):
                    M.data_piece_plan(module)
        module = owner(); del module["partition_only"]
        self.save(modules=[module])
        with self.assertRaisesRegex(M.ModuleError, "members must be nonempty"):
            M.load_manifest(self.manifest)
        module = owner(); module["members"] = [
            {"id": "slus/w_80030000", "source": "src/w_80030000.c", "functions": [CODE_A]}]
        self.save(modules=[module])
        with self.assertRaisesRegex(M.ModuleError, "must have no whole members"):
            M.load_manifest(self.manifest)
        del module["partition_only"]
        self.save(modules=[module])
        self.assertEqual(len(M.load_manifest(self.manifest)[0]["members"]), 1)

    def test_partition_only_data_piece_plan_remains_valid(self) -> None:
        module = owner()
        module["data"] = [{"symbol": "D_80080A68", "asset": "assets/54240.bin",
                           "offset": 0, "size": 4, "vram": 0x80080A68,
                           "bytes": "01020304", "section": ".sdata.D_80080A68"}]
        module["data_pieces"] = [{"symbol": "D_80080A68", "source_section": ".sdata",
                                  "alignment": 4}]
        self.save(modules=[module])
        parsed = M.load_manifest(self.manifest)[0]
        self.assertEqual(M.data_piece_plan(parsed), [{"symbol": "D_80080A68", "size": 4,
                                                      "section": ".sdata.D_80080A68",
                                                      "alignment": 4,
                                                      "source_section": ".sdata"}])

    def test_empty_plan_and_orphan_are_refused_in_context_and_configure(self) -> None:
        self.save(plan=[])
        modules = M.load_manifest(self.manifest)
        with self.assertRaisesRegex(P.PartitionError, "no incoming"):
            P.validate_context([], modules, [], self.root / "raw/slus")
        with self.assertRaisesRegex(P.PartitionError, "no incoming"):
            P.expected_units([], modules)
        result = self.configure()
        self.assertNotEqual(result.returncode, 0)
        self.assertIn("no incoming", result.stderr)
        orphan = owner(); orphan["name"] = "orphan"; orphan["source"] = "src/orphan.c"
        self.save(modules=[owner(), orphan])
        with self.assertRaisesRegex(P.PartitionError, "orphan"):
            P.validate_context(P.load_plan(self.plan), M.load_manifest(self.manifest),
                               [edge("src/code.c"), edge("src/code2.c")],
                               self.root / "raw/slus")

    def test_unknown_duplicate_and_fake_logical_coverage_are_refused(self) -> None:
        modules = M.load_manifest(self.manifest)
        logical = [edge("src/code.c"), edge("src/code2.c")]
        bad = parents(); bad[0]["parts"][0]["module"] = "unknown"
        with self.assertRaisesRegex(P.PartitionError, "unknown destination"):
            P.validate_context(bad, modules, logical, self.root / "raw/slus")
        bad = parents(); bad[0]["parts"][0]["functions"] = [CODE_A, CODE_A]
        with self.assertRaisesRegex(P.PartitionError, "unique canonical functions"):
            P.validate_context(bad, modules, logical, self.root / "raw/slus")
        bad = parents(); bad[0]["parts"].append({"module": "partition_owner", "functions": [CODE_B]})
        with self.assertRaisesRegex(P.PartitionError, "duplicate partition destination"):
            P.validate_context(bad, modules, logical, self.root / "raw/slus")
        with self.assertRaisesRegex(P.PartitionError, "fake logical row"):
            P.validate_context(parents(), modules, logical + [edge("src/partition_owner.c")],
                               self.root / "raw/slus")


if __name__ == "__main__":
    unittest.main()
