"""Contract tests for the partition-aware isolated SLUS link gate.

The fixture uses the real partition routing code and a fake Ninja boundary.  It
checks what the gate asks Ninja to build and whether the isolated view returns
to its pristine state after every result.  MIPS linking is tested separately.
"""

from __future__ import annotations

import os
import sys
import tempfile
import unittest
from pathlib import Path
from types import SimpleNamespace
from unittest.mock import Mock, patch

REPO = Path(__file__).resolve().parents[2]
sys.path[:0] = [str(REPO / "tools"), str(REPO / "tools/build")]
import slus_module_context as CONTEXT  # noqa: E402
from fidelity import slus_iso as ISO
import verify as VERIFY

PARENT = {"ccver": "2.7.2", "ccflags": "-G0", "asflags": ""}
OWNER = {"ccver": "2.8.1", "ccflags": "-O2", "asflags": ""}
OLD = b"PRISTINE\n"
EDIT = "int func_80030000(void) { return 2; }\nint func_80030010(void) { return 3; }\n"


def edge(stem, source, recipe):
    return (f"build build/src/{stem}.o: cc {source}\n"
            f"  ccver = {recipe['ccver']}\n"
            f"  ccflags = {recipe['ccflags']}\n")


class PartitionGateTests(unittest.TestCase):
    def setUp(self):
        temp = tempfile.TemporaryDirectory(prefix="slus_gate_contract_")
        self.addCleanup(temp.cleanup)
        self.root = Path(temp.name)
        self.canonical = self.root / "canonical"
        self.dest = self.root / "view"
        for directory in (self.canonical, self.dest / "src", self.dest / "build/src",
                          self.dest / "build/partition_sources", self.dest / "build",
                          self.root / "baserom"):
            directory.mkdir(parents=True, exist_ok=True)
        self.parent = {
            "id": "slus/code", "source": "src/code.c", "recipe": PARENT,
            "functions": ["func_80030000", "func_80030010"],
            "parts": [{"module": "alpha", "functions": ["func_80030000"]}],
        }
        self.module = {
            "name": "alpha", "source": "src/alpha.c", "recipe": OWNER,
            "members": [{"id": "slus/a", "source": "src/a.c",
                         "functions": ["func_80030020"]}],
        }
        self.ninja_text = (
            edge("code", "build/partition_sources/code.c", PARENT)
            + edge("alpha", "src/alpha.c", OWNER)
            + edge("plain", "src/plain.c", PARENT)
        )
        (self.dest / "build.ninja").write_text(self.ninja_text)
        for stem in ("code", "a", "plain"):
            (self.canonical / f"{stem}.c").write_bytes(OLD)
            (self.dest / "src" / f"{stem}.c").symlink_to(self.canonical / f"{stem}.c")
        for stem in ("code", "alpha"):
            (self.dest / "build/src" / f"{stem}.o").write_bytes(b"stock " + stem.encode())
        self.generated = self.dest / "build/partition_sources/code.c"
        self.fragment = self.dest / "build/partition_sources/code__alpha.c"
        self.generated.write_bytes(b"stock remainder")
        self.fragment.write_bytes(b"stock fragment")
        (self.dest / ISO.IMAGE).write_bytes(b"ABCD")
        (self.root / "baserom/slus_006.14").write_bytes(b"ABCD")
        self.root_patch = patch.object(ISO, "ROOT", self.root)
        self.root_patch.start()
        self.addCleanup(self.root_patch.stop)

        view = object.__new__(ISO.SlusView)
        view.dest = self.dest
        view.src_real = self.canonical
        view.pristine = self.ninja_text
        view.modules = [self.module]
        view.partitions = [self.parent]
        view.aliases = {}
        view._pristine_syms = {}
        view.tu_functions = Mock(return_value=[])
        view._partition_coverage = Mock()
        self.view = view
        self.calls = []
        self.failure = None
        self.image = b"ABCD"
        self.expected_targets = ["build/src/code.o", "build/src/alpha.o"]
        view._ninja = Mock(side_effect=self.fake_ninja)

    def fake_ninja(self, targets, env=None):
        self.calls.append(tuple(targets))
        pristine = ((self.dest / "build.ninja").read_text() == self.ninja_text
                    and all((self.dest / "src" / f"{stem}.c").read_bytes() == OLD
                            for stem in ("code", "a")))
        if targets != [ISO.IMAGE]:
            self.assertEqual(targets, self.expected_targets)
            self.assertIn("ccver = 2.7.2\n  ccflags = -G0", (self.dest / "build.ninja").read_text())
            self.assertIn("ccver = 2.8.1\n  ccflags = -O2", (self.dest / "build.ninja").read_text())
            if "build/src/code.o" in targets:
                self.generated.write_bytes(b"candidate remainder")
                self.fragment.write_bytes(b"candidate fragment")
            for stem in (Path(target).stem for target in targets):
                (self.dest / "build/src" / f"{stem}.o").write_bytes(b"candidate " + stem.encode())
            return (1, "synthetic compile failure") if self.failure == "compile" else (0, "")
        if pristine:
            # Ninja's restoration build regenerates the affected generated views,
            # both objects, and the retail image from canonical sources.
            self.generated.write_bytes(b"stock remainder")
            self.fragment.write_bytes(b"stock fragment")
            for stem in ("code", "alpha"):
                (self.dest / "build/src" / f"{stem}.o").write_bytes(b"stock " + stem.encode())
            (self.dest / ISO.IMAGE).write_bytes(b"ABCD")
            return 0, ""
        if self.failure == "link":
            return 1, "synthetic link failure"
        (self.dest / ISO.IMAGE).write_bytes(self.image)
        return 0, ""

    def assert_pristine(self):
        self.assertEqual((self.dest / "build.ninja").read_text(), self.ninja_text)
        self.assertTrue((self.dest / "src/code.c").is_symlink())
        self.assertEqual((self.dest / "src/code.c").resolve(), self.canonical / "code.c")
        self.assertEqual((self.canonical / "code.c").read_bytes(), OLD)
        self.assertEqual(self.generated.read_bytes(), b"stock remainder")
        self.assertEqual(self.fragment.read_bytes(), b"stock fragment")
        for stem in ("code", "alpha"):
            self.assertEqual((self.dest / "build/src" / f"{stem}.o").read_bytes(),
                             b"stock " + stem.encode())
        self.assertEqual((self.dest / ISO.IMAGE).read_bytes(), b"ABCD")

    def test_recipe_edge_is_selected_by_object_when_source_is_generated(self):
        changed = ISO.set_tu_recipe(self.ninja_text, "code", "2.7.2-cdk", "-G8")
        self.assertIn(edge("code", "build/partition_sources/code.c",
                           {"ccver": "2.7.2-cdk", "ccflags": "-G8"}), changed)
        self.assertIn(edge("alpha", "src/alpha.c", OWNER), changed)
        self.assertIn(edge("plain", "src/plain.c", PARENT), changed)
        with self.assertRaises(ValueError):
            ISO.set_tu_recipe(changed, "absent", "2.7.2", "")

    def test_connected_stems_are_plural_and_implicit_recipe_trial_is_refused(self):
        self.assertEqual(self.view.physical_stems("code"), ["code", "alpha"])
        self.assertEqual(self.view.physical_stems("a"), ["alpha"])
        self.assertEqual(self.view.physical_stems("plain"), ["plain"])
        with self.assertRaises(ValueError):
            self.view.physical_stem("code")
        with self.assertRaises(ValueError):
            self.view.physical_stem("a")
        self.assertEqual(self.view.physical_stem("plain"), "plain")
        result = self.view.gate({"code": (EDIT, "2.7.2-cdk", "-G0")})
        self.assertEqual(result["result"], "ERROR")
        self.assertIn("explicit physical-owner plan", result["detail"])
        self.view._ninja.assert_not_called()
        self.assert_pristine()

    def test_connected_parent_routes_owner_recipes_and_restores_both_results(self):
        for image, expected in ((b"ABCD", "MATCH"), (b"ABCE", "NO MATCH")):
            with self.subTest(expected=expected):
                self.image = image
                self.calls.clear()
                result = self.view.gate({"code": (EDIT, "2.7.2", "-G0")})
                self.assertEqual(result["result"], expected)
                self.assertEqual(self.calls, [("build/src/code.o", "build/src/alpha.o"),
                                              (ISO.IMAGE,), (ISO.IMAGE,)])
                self.assertEqual(self.view._partition_coverage.call_count, 2)
                self.view._partition_coverage.reset_mock()
                self.assert_pristine()

    def test_connected_whole_member_edits_only_its_owner_object(self):
        self.expected_targets = ["build/src/alpha.o"]
        result = self.view.gate({"a": ("int func_80030020(void) { return 8; }\n",
                                       "2.8.1", "-O2")})
        self.assertEqual(result["result"], "MATCH")
        self.assertEqual(self.calls, [("build/src/alpha.o",), (ISO.IMAGE,), (ISO.IMAGE,)])
        self.assertTrue((self.dest / "src/a.c").is_symlink())
        self.assertEqual((self.canonical / "a.c").read_bytes(), OLD)
        self.assert_pristine()

    def test_coverage_precedes_image_comparison_and_all_failures_restore(self):
        for failure, detail in (("compile", "compile:"),
                                ("coverage", "partition coverage:"),
                                ("link", "link:")):
            with self.subTest(failure=failure):
                self.failure = failure
                self.calls.clear()
                if failure == "coverage":
                    self.view._partition_coverage.side_effect = [ValueError("extra emitted function"), None]
                else:
                    self.view._partition_coverage.side_effect = None
                result = self.view.gate({"code": (EDIT, "2.7.2", "-G0")})
                self.assertEqual(result["result"], "ERROR")
                self.assertIn(detail, result["detail"])
                if failure == "coverage":
                    self.assertIn("extra emitted function", result["detail"])
                    self.assertEqual(self.calls, [("build/src/code.o", "build/src/alpha.o"),
                                                  (ISO.IMAGE,)])
                self.assert_pristine()
                self.view._partition_coverage.reset_mock(side_effect=True)
                self.failure = None

    def test_whole_module_recipe_change_still_requires_every_member(self):
        module = {
            "name": "whole", "source": "src/whole.c", "recipe": OWNER,
            "members": [{"id": "slus/x", "source": "src/x.c", "functions": ["func_80030100"]},
                        {"id": "slus/y", "source": "src/y.c", "functions": ["func_80030110"]}],
        }
        self.view.modules.append(module)
        result = self.view.gate({"x": ("int x;", "2.7.2", "")})
        self.assertEqual(result["result"], "ERROR")
        self.assertIn("every member of module whole", result["detail"])
        self.view._ninja.assert_not_called()

    def test_emitted_coverage_reads_complete_partition_owner_object(self):
        # The moved function alone is insufficient: alpha must also emit its
        # whole-member function even when only the parent text changes.
        self.view._partition_coverage = ISO.SlusView._partition_coverage.__get__(self.view)
        emitted = {
            b"stock code": ["func_80030010"],
            b"stock alpha": ["func_80030000", "func_80030020"],
        }
        def read_object(blob):
            return SimpleNamespace(symbols={name: (".text", 4, "func")
                                            for name in emitted[blob]})
        with patch.object(ISO, "read_elf", side_effect=read_object) as reader:
            self.view._partition_coverage()
            self.assertEqual(reader.call_count, 2)
            emitted[b"stock alpha"] = ["func_80030000"]
            with self.assertRaisesRegex(ValueError, "emitted function coverage differs"):
                self.view._partition_coverage()
            emitted[b"stock alpha"] = ["func_80030000", "func_80030020", "func_80030999"]
            with self.assertRaisesRegex(ValueError, "emitted function coverage differs"):
                self.view._partition_coverage()

    def test_regular_source_snapshot_restores_bytes_mode_and_time_on_error(self):
        source = self.dest / "src/code.c"
        source.unlink()
        source.write_bytes(OLD)
        source.chmod(0o640)
        os.utime(source, ns=(1_500_000_000_000_000_000, 1_500_000_000_000_000_000))
        before = source.stat()
        self.failure = "compile"
        result = self.view.gate({"code": (EDIT, "2.7.2", "-G0")})
        self.assertEqual(result["result"], "ERROR")
        self.assertFalse(source.is_symlink())
        self.assertEqual(source.read_bytes(), OLD)
        after = source.stat()
        self.assertEqual(after.st_mode & 0o777, before.st_mode & 0o777)
        self.assertEqual(after.st_mtime_ns, before.st_mtime_ns)
        self.assertEqual(self.generated.read_bytes(), b"stock remainder")
        self.assertEqual(self.fragment.read_bytes(), b"stock fragment")
        self.assertEqual((self.dest / "build.ninja").read_text(), self.ninja_text)

    def test_public_verify_routes_connected_canonical_row_to_image_gate(self):
        row = {"id": "slus/code", "kind": "slus", "c_path": "src/code.c",
               "cell": "2.7.2", "flags": "-G0"}
        raw = self.root / "raw.c"
        candidate = self.root / "candidate.c"
        with (patch.object(VERIFY, "raw_path", return_value=raw),
              patch.object(CONTEXT, "partition_context", return_value=([self.parent], [self.module], {})),
              patch.object(CONTEXT, "membership", side_effect=AssertionError("singular module path reached")),
              patch.object(VERIFY, "verify_slus_partition", return_value={"exact": True}) as gate):
            self.assertEqual(VERIFY.verify_slus(row, candidate), {"exact": True})
            gate.assert_called_once_with(row, candidate, include_root=None, regions=False, diff=False)

    def test_public_verify_keeps_frozen_raw_row_on_historical_standalone_path(self):
        row = {"id": "slus/code", "kind": "slus", "c_path": "src/code.c",
               "cell": "2.7.2", "flags": "-G0"}
        raw = self.root / "raw.c"
        with (patch.object(VERIFY, "raw_path", return_value=raw),
              patch.object(CONTEXT, "partition_context", side_effect=AssertionError("live partition path reached")),
              patch.object(CONTEXT, "membership", side_effect=AssertionError("live module path reached")),
              patch.object(VERIFY, "read_baseline_slus", return_value={}),
              patch.object(VERIFY, "compile_slus", return_value=(None, "raw sentinel"))):
            result = VERIFY.verify_slus(row, raw)
        self.assertEqual(result["status"], "failed")
        self.assertEqual(result["err"], "raw sentinel")


if __name__ == "__main__":
    unittest.main()
