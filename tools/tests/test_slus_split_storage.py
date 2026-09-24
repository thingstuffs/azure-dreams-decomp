"""Contracts for one SLUS module owning separated .sdata and .sbss slots."""

import copy
import json
import shutil
import subprocess
import sys
import tempfile
import unittest
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / "build"))
import slus_modules as sm  # noqa: E402


class SplitStorageTest(unittest.TestCase):
    def setUp(self):
        self.tmp = tempfile.TemporaryDirectory()
        self.addCleanup(self.tmp.cleanup)
        self.root = Path(self.tmp.name)
        (self.root / "assets").mkdir()
        (self.root / "config").mkdir()
        (self.root / "src").mkdir()
        self.asset = b"ABCD\x12\x34uvwxyz\x00\x00YZ"
        (self.root / "assets/54240.bin").write_bytes(self.asset)
        self.module = {
            "name": "split", "source": "src/split.c",
            "members": [{"id": "slus/row", "source": "src/row.c", "functions": ["func_row"]}],
            "headers": [], "recipe": {"ccver": "2.7.2-cdk", "ccflags": "", "asflags": ""},
            "data": [
                {"symbol": "D_SMALL", "asset": "assets/54240.bin", "offset": 4,
                 "size": 2, "vram": 0x80000004, "bytes": "1234", "section": ".sdata"},
                {"symbol": "D_ZERO", "asset": "assets/54240.bin", "offset": 12,
                 "size": 2, "vram": 0x8000000C, "bytes": "0000", "section": ".sbss"},
            ],
            "evidence": "docs/evidence/split.md",
        }
        self.manifest = self.root / "config/slus_modules.json"
        self.save()

    def save(self):
        self.manifest.write_text(json.dumps({"version": 1, "modules": [self.module]}))

    def plan(self):
        return sm.plan_asset_carves(sm.load_manifest(self.manifest), self.root)

    def test_sections_carve_separate_spans_and_filter_both_symbols(self):
        modules = sm.load_manifest(self.manifest)
        self.assertEqual([d["section"] for d in modules[0]["data"]], [".sdata", ".sbss"])
        plan = sm.plan_asset_carves(modules, self.root)
        slots = plan[0]["slots"]
        owned = [s for s in slots if s["kind"] == "module_data"]
        self.assertEqual([(s["start"], s["end"], s["section"]) for s in owned],
                         [(4, 6, ".sdata"), (12, 14, ".sbss")])
        self.assertEqual([s["object"] for s in owned], ["build/src/split.o"] * 2)
        ordered = sm.rewrite_ordered_linker_script(
            "SECTIONS {\n .all 0x1000 : SUBALIGN(4)\n {\n"
            "        build/assets/54240.o(.data);\n }\n /DISCARD/ : { *(*) }\n}\n", plan)
        self.assertEqual(ordered.count("build/src/split.o(.sdata);"), 1)
        self.assertEqual(ordered.count("build/src/split.o(.sbss);"), 1)
        self.assertLess(ordered.index("split.o(.sdata)"), ordered.index("split.o(.sbss)"))
        self.assertIn("SUBALIGN(1)", ordered)
        self.assertEqual(sm.filter_owned_symbols(
            "D_SMALL = 0x80000004;\nD_ZERO = 0x8000000C;\nD_OTHER = 0x1;\n", modules),
            "D_OTHER = 0x1;\n")

    def test_nonzero_sbss_rejected_in_manifest_and_asset(self):
        self.module["data"][1]["bytes"] = "0100"
        self.save()
        with self.assertRaisesRegex(sm.ModuleError, "zero|nonzero"):
            sm.load_manifest(self.manifest)
        self.module["data"][1]["bytes"] = "0000"
        self.save()
        changed = bytearray(self.asset)
        changed[12] = 1
        (self.root / "assets/54240.bin").write_bytes(changed)
        with self.assertRaises(sm.ModuleError):
            self.plan()

    def test_same_section_gap_and_cross_section_overlap_rejected(self):
        added = copy.deepcopy(self.module["data"][0])
        added.update(symbol="D_SECOND", offset=8, vram=0x80000008, bytes="7778")
        self.module["data"].insert(1, added)
        self.save()
        with self.assertRaisesRegex(sm.ModuleError, "contiguous|ordered"):
            self.plan()
        self.module["data"].pop(1)
        (self.root / "assets/54240.bin").write_bytes(b"\x00" * len(self.asset))
        self.module["data"][0]["bytes"] = "0000"
        self.module["data"][1].update(offset=5, vram=0x80000005)
        self.save()
        with self.assertRaisesRegex(sm.ModuleError, "overlap"):
            self.plan()

    def test_each_section_has_one_asset_but_sections_may_use_different_assets(self):
        (self.root / "assets/60000.bin").write_bytes(b"xxxx\x00\x00yyyy")
        self.module["data"][1].update(asset="assets/60000.bin", offset=4, vram=0x80010004)
        self.save()
        plans = self.plan()
        self.assertEqual({p["asset"] for p in plans}, {"assets/54240.bin", "assets/60000.bin"})
        added = copy.deepcopy(self.module["data"][0])
        added.update(symbol="D_OTHER", asset="assets/60000.bin", offset=6,
                     vram=0x80010006, bytes="7979")
        self.module["data"].insert(1, added)
        self.save()
        with self.assertRaisesRegex(sm.ModuleError, "asset"):
            self.plan()

    def test_unsupported_storage_section_rejected(self):
        self.module["data"][1]["section"] = ".bss"
        self.save()
        with self.assertRaisesRegex(sm.ModuleError, "unsupported data section"):
            sm.load_manifest(self.manifest)

    @unittest.skipUnless(all(shutil.which(x) for x in
                             ("mipsel-linux-gnu-as", "mipsel-linux-gnu-ld", "mipsel-linux-gnu-objcopy",
                              "mipsel-linux-gnu-readelf", "mipsel-linux-gnu-nm")),
                         "MIPS binutils unavailable")
    def test_real_mips_sections_reproduce_asset_including_nobits_span(self):
        plan = self.plan()
        chunks = sm.materialize_asset_chunks(plan, self.root, assemble=True)
        (self.root / "build/src").mkdir(parents=True)
        asm = self.root / "src/split.s"
        asm.write_text(
            '.section .sdata,"aw",@progbits\n.globl D_SMALL\nD_SMALL: .byte 0x12, 0x34\n'
            '.section .sbss,"aw",@nobits\n.globl D_ZERO\nD_ZERO: .space 2\n')
        obj = self.root / "build/src/split.o"
        subprocess.run(("mipsel-linux-gnu-as", "-EL", "-o", str(obj), str(asm)), check=True)
        sections = subprocess.check_output(("mipsel-linux-gnu-readelf", "-SW", str(obj)), text=True)
        self.assertRegex(sections, r"\.sdata\s+PROGBITS")
        self.assertRegex(sections, r"\.sbss\s+NOBITS")
        script = self.root / "build/ordered.ld"
        script.write_text(sm.rewrite_ordered_linker_script(
            "SECTIONS {\n .all 0x1000 : SUBALIGN(4)\n {\n"
            "        build/assets/54240.o(.data);\n }\n /DISCARD/ : { *(*) }\n}\n", plan))
        elf = self.root / "build/result.elf"
        objects = [s["object"] for s in chunks] + ["build/src/split.o"]
        subprocess.run(("mipsel-linux-gnu-ld", "-EL", "-T", str(script), "-o", str(elf), *objects),
                       cwd=self.root, check=True)
        output = self.root / "build/result.bin"
        subprocess.run(("mipsel-linux-gnu-objcopy", "-O", "binary", str(elf), str(output)), check=True)
        self.assertEqual(output.read_bytes(), self.asset)
        symbols = subprocess.check_output(("mipsel-linux-gnu-nm", "-n", str(elf)), text=True)
        self.assertRegex(symbols, r"(?m)^00001004\s+\w\s+D_SMALL$")
        self.assertRegex(symbols, r"(?m)^0000100c\s+\w\s+D_ZERO$")


if __name__ == "__main__":
    unittest.main()
