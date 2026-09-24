"""Contract tests for build-side SLUS module ownership and linker inputs."""

import contextlib
import copy
import io
import json
import shutil
import sys
import tempfile
import unittest
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / "build"))
import slus_modules as sm  # noqa: E402


def pilot():
    return {
        "name": "runtime_directory",
        "source": "src/konami_runtime_directory.c",
        "members": [
            {"id": f"slus/konami_runtime_w_8003C{x}",
             "source": f"src/konami_runtime_w_8003C{x}.c",
             "functions": [f"func_8003C{x}"]}
            for x in ("634", "758", "920")
        ],
        "headers": ["include/slus/runtime_directory.h"],
        "recipe": {"ccver": "2.7.2-cdk", "ccflags": "", "asflags": ""},
        "data": [{"symbol": "D_80080A6C", "asset": "assets/54240.bin", "offset": 4,
                  "size": 4, "vram": 0x80080A6C, "bytes": "04000000", "section": ".sdata"}],
        "evidence": "docs/evidence/runtime_directory.md",
    }


class SlusModulesTest(unittest.TestCase):
    def setUp(self):
        self.tmp = tempfile.TemporaryDirectory()
        self.addCleanup(self.tmp.cleanup)
        self.root = Path(self.tmp.name)
        (self.root / "assets").mkdir()
        (self.root / "assets/54240.bin").write_bytes(b"\xAA" * 4 + b"\x04\x00\x00\x00" + b"\xBB" * 12)
        self.module = pilot()
        self.manifest = self.root / "config/slus_modules.json"
        self.manifest.parent.mkdir()
        self.save()

    def save(self, modules=None):
        self.manifest.write_text(json.dumps({"version": 1, "modules": modules if modules is not None else [self.module]}))

    def test_absent_manifest_is_noop(self):
        modules = sm.load_manifest(self.root / "config/missing.json")
        self.assertEqual(modules, [])
        self.assertEqual(sm.plan_asset_carves(modules, self.root), [])
        self.assertEqual(sm.rewrite_ordered_linker_script("X", []), "X")
        self.assertEqual(sm.filter_owned_symbols("D_X = 0x1;\n", modules), "D_X = 0x1;\n")

    def test_load_lookup_and_logical_edges(self):
        modules = sm.load_manifest(self.manifest)
        self.assertEqual(sm.module_for_row(modules, "slus/konami_runtime_w_8003C758")["name"], "runtime_directory")
        self.assertIsNone(sm.module_for_row(modules, "slus/unrelated"))
        physical = [{"src": "src/other.c", "out": "build/src/other.o", "ccver": "2.8.1", "ccflags": "-G0", "asflags": ""},
                    {"src": self.module["source"], "out": "build/src/konami_runtime_directory.o", **self.module["recipe"]}]
        logical = sm.logical_edges(physical, modules)
        self.assertEqual(len(logical), 4)
        self.assertEqual(logical, sorted(logical, key=lambda e: e["src"]))
        self.assertEqual(logical[0], {"src": "src/konami_runtime_w_8003C634.c",
                                      "out": "build/src/konami_runtime_w_8003C634.o", **self.module["recipe"]})
        self.assertEqual(logical[-1], physical[0])
        self.assertTrue(all(set(e) == set(sm.EDGE_KEYS) for e in logical))

    def test_recipe_mismatch_and_missing_physical_module_refused(self):
        modules = sm.load_manifest(self.manifest)
        edge = {"src": self.module["source"], "out": "build/src/konami_runtime_directory.o",
                "ccver": "2.8.1", "ccflags": "", "asflags": ""}
        with self.assertRaisesRegex(sm.ModuleError, "recipe"):
            sm.logical_edges([edge], modules)
        with self.assertRaisesRegex(sm.ModuleError, "missing physical"):
            sm.logical_edges([], modules)

    def test_unsafe_paths_and_duplicate_ids_symbols_sources(self):
        bad = copy.deepcopy(self.module)
        bad["source"] = "src/../escape.c"
        self.save([bad])
        with self.assertRaisesRegex(sm.ModuleError, "unsafe path"):
            sm.load_manifest(self.manifest)
        for field in ("id", "source"):
            bad = copy.deepcopy(self.module)
            bad["members"][1][field] = bad["members"][0][field]
            self.save([bad])
            with self.assertRaises(sm.ModuleError):
                sm.load_manifest(self.manifest)
        bad = copy.deepcopy(self.module)
        bad["data"].append(dict(bad["data"][0]))
        self.save([bad])
        with self.assertRaisesRegex(sm.ModuleError, "duplicate symbol"):
            sm.load_manifest(self.manifest)
        bad = copy.deepcopy(self.module)
        bad["members"][1]["id"] = "slus/wrong_row"
        self.save([bad])
        with self.assertRaisesRegex(sm.ModuleError, "row id must match source stem"):
            sm.load_manifest(self.manifest)
        bad = copy.deepcopy(self.module)
        bad["source"] = "src/subdir/konami_runtime_w_8003C634.c"
        self.save([bad])
        with self.assertRaisesRegex(sm.ModuleError, "duplicate generated object stem"):
            sm.load_manifest(self.manifest)

    def test_carve_plan_materialization_rewrite_and_symbol_filter(self):
        modules = sm.load_manifest(self.manifest)
        plan = sm.plan_asset_carves(modules, self.root)
        self.assertEqual(plan[0]["asset_object"], "build/assets/54240.o")
        self.assertEqual([s["kind"] for s in plan[0]["slots"]], ["chunk", "module_data", "chunk"])
        self.assertEqual(plan[0]["slots"][1]["object"], "build/src/konami_runtime_directory.o")
        self.assertEqual(plan[0]["slots"][1]["symbols"], ["D_80080A6C"])
        made = sm.materialize_asset_chunks(plan, self.root)
        self.assertEqual(len(made), 2)
        self.assertEqual((self.root / made[0]["input"]).read_bytes(), b"\xAA" * 4)
        self.assertEqual((self.root / made[1]["input"]).read_bytes(), b"\xBB" * 12)
        linker = "head\n        build/assets/54240.o(.data);\ntail\n"
        new = sm.rewrite_ordered_linker_script(linker, plan)
        self.assertEqual(new.count("build/src/konami_runtime_directory.o(.sdata);"), 1)
        self.assertLess(new.index(made[0]["object"]), new.index("build/src/konami_runtime_directory.o"))
        self.assertLess(new.index("build/src/konami_runtime_directory.o"), new.index(made[1]["object"]))
        self.assertNotIn("build/assets/54240.o(.data);", new)
        self.assertEqual(sm.filter_owned_symbols("D_OTHER = 0x10;\nD_80080A6C = 0x80080A6C;\n", modules),
                         "D_OTHER = 0x10;\n")

    def test_overlap_wrong_bytes_and_ambiguous_slot_refused(self):
        other = copy.deepcopy(self.module)
        other["name"] = "other"
        other["source"] = "src/other.c"
        other["members"] = [{"id": "slus/other_row", "source": "src/other_row.c", "functions": ["func_other"]}]
        other["data"][0].update(symbol="D_OTHER", offset=6, bytes="0000bbbb", vram=0x80080A6E)
        self.save([self.module, other])
        with self.assertRaisesRegex(sm.ModuleError, "overlapping"):
            sm.plan_asset_carves(sm.load_manifest(self.manifest), self.root)
        self.save()
        (self.root / "assets/54240.bin").write_bytes(b"\xAA" * 20)
        with self.assertRaisesRegex(sm.ModuleError, "initializer bytes differ"):
            sm.plan_asset_carves(sm.load_manifest(self.manifest), self.root)
        (self.root / "assets/54240.bin").write_bytes(b"\xAA" * 4 + b"\x04\x00\x00\x00" + b"\xBB" * 12)
        plan = sm.plan_asset_carves(sm.load_manifest(self.manifest), self.root)
        with self.assertRaisesRegex(sm.ModuleError, "unambiguous slot"):
            sm.rewrite_ordered_linker_script("no matching slot", plan)
        wrong_object = "prefixbuild/assets/54240.o(.data);\n"
        with self.assertRaisesRegex(sm.ModuleError, "unambiguous slot"):
            sm.rewrite_ordered_linker_script(wrong_object, plan)
        existing_module = "build/src/konami_runtime_directory.o(.sdata);\n        build/assets/54240.o(.data);\n"
        with self.assertRaisesRegex(sm.ModuleError, "already contains module data slot"):
            sm.rewrite_ordered_linker_script(existing_module, plan)

    def test_two_modules_can_carve_one_asset_without_overlap(self):
        other = copy.deepcopy(self.module)
        other["name"] = "other"
        other["source"] = "src/other.c"
        other["members"] = [{"id": "slus/other_row", "source": "src/other_row.c", "functions": ["func_other"]}]
        other["data"][0].update(symbol="D_80080A74", offset=12, bytes="bbbbbbbb", vram=0x80080A74)
        self.save([self.module, other])
        plan = sm.plan_asset_carves(sm.load_manifest(self.manifest), self.root)
        self.assertEqual(len(plan), 1)
        self.assertEqual([s["kind"] for s in plan[0]["slots"]],
                         ["chunk", "module_data", "chunk", "module_data", "chunk"])
        self.assertEqual([s["module"] for s in plan[0]["slots"] if s["kind"] == "module_data"],
                         ["runtime_directory", "other"])

    def test_asset_change_after_plan_and_exe_vram_mismatch_refused(self):
        plan = sm.plan_asset_carves(sm.load_manifest(self.manifest), self.root)
        (self.root / "assets/54240.bin").write_bytes(b"\xAB" * 4 + b"\x04\x00\x00\x00" + b"\xBB" * 12)
        with self.assertRaisesRegex(sm.ModuleError, "changed since planning"):
            sm.materialize_asset_chunks(plan, self.root)
        (self.root / "assets/54240.bin").write_bytes(b"\xAA" * 4 + b"\x04\x00\x00\x00" + b"\xBB" * 12)
        (self.root / "baserom").mkdir()
        header = bytearray(0x20)
        header[:8] = b"PS-X EXE"
        header[0x18:0x1C] = (0x8002D000).to_bytes(4, "little")
        (self.root / "baserom/slus_006.14").write_bytes(header)
        with self.assertRaisesRegex(sm.ModuleError, "EXE mapping"):
            sm.plan_asset_carves(sm.load_manifest(self.manifest), self.root)

    def test_generated_output_symlink_cannot_escape_root(self):
        plan = sm.plan_asset_carves(sm.load_manifest(self.manifest), self.root)
        with tempfile.TemporaryDirectory() as outside:
            (self.root / "build").symlink_to(outside, target_is_directory=True)
            with self.assertRaisesRegex(sm.ModuleError, "output escapes root"):
                sm.materialize_asset_chunks(plan, self.root)
            self.assertEqual(list(Path(outside).iterdir()), [])

    def test_multiple_contiguous_data_in_one_module_only(self):
        second = {"symbol": "D_NEXT", "asset": "assets/54240.bin", "offset": 8,
                  "size": 4, "vram": 0x80080A70, "bytes": "bbbbbbbb", "section": ".sdata"}
        self.module["data"].append(second)
        self.save()
        plan = sm.plan_asset_carves(sm.load_manifest(self.manifest), self.root)
        self.assertEqual([s["kind"] for s in plan[0]["slots"]], ["chunk", "module_data", "chunk"])
        self.assertEqual(plan[0]["slots"][1]["symbols"], ["D_80080A6C", "D_NEXT"])
        self.module["data"][1]["offset"] = 12
        self.save()
        with self.assertRaisesRegex(sm.ModuleError, "contiguous and ordered"):
            sm.plan_asset_carves(sm.load_manifest(self.manifest), self.root)

    def test_unknown_or_missing_owned_symbol_refused(self):
        modules = sm.load_manifest(self.manifest)
        with self.assertRaisesRegex(sm.ModuleError, "missing owned"):
            sm.filter_owned_symbols("D_OTHER = 0x1;\n", modules)
        with self.assertRaisesRegex(sm.ModuleError, "wrong-address"):
            sm.filter_owned_symbols("D_80080A6C = 0x80080A70;\n", modules)
        bad = copy.deepcopy(self.module)
        bad["data"][0]["symbol"] = "not-a-symbol"
        self.save([bad])
        with self.assertRaisesRegex(sm.ModuleError, "invalid identifier"):
            sm.load_manifest(self.manifest)
        bad = copy.deepcopy(self.module)
        bad["data"][0]["section"] = ".sbss"
        self.save([bad])
        with self.assertRaisesRegex(sm.ModuleError, "unsupported data section"):
            sm.load_manifest(self.manifest)

    def test_cli_absent_manifest_noop_and_assets_plan(self):
        source = self.root / "base.ld"
        source.write_text("unchanged\n")
        sink = self.root / "ordered.ld"
        with contextlib.redirect_stdout(io.StringIO()):
            sm.main(["orderld", "--root", str(self.root), "--manifest", "config/missing.json",
                     "--input", "base.ld", "--output", "ordered.ld"])
        self.assertEqual(sink.read_text(), source.read_text())
        with contextlib.redirect_stdout(io.StringIO()):
            sm.main(["assets", "--root", str(self.root), "--manifest", "config/slus_modules.json"])
        self.assertTrue((self.root / "build/module_assets/54240_000000_000004.bin").exists())

    @unittest.skipUnless(shutil.which("mipsel-linux-gnu-ld"), "MIPS linker unavailable")
    def test_optional_stock_binary_object_generation(self):
        plan = sm.plan_asset_carves(sm.load_manifest(self.manifest), self.root)
        made = sm.materialize_asset_chunks(plan, self.root, assemble=True)
        self.assertTrue(all((self.root / s["object"]).is_file() for s in made))


if __name__ == "__main__":
    unittest.main()
