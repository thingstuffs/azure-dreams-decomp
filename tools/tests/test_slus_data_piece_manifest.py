"""Portable opt-in named-section contract for SLUS module data pieces."""

import copy
import json
import sys
import tempfile
import unittest
from pathlib import Path


ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools/build"))
import slus_modules as sm  # noqa: E402


def fixture_module(raw):
    def datum(symbol, start, size, section):
        return {"symbol": symbol, "asset": "assets/000800.bin", "offset": start,
                "size": size, "vram": 0x80000000 + start,
                "bytes": raw[start:start + size].hex(), "section": section}

    return {
        "name": "piece_owner", "source": "src/piece_owner.c",
        "members": [{"id": "slus/piece_member", "source": "src/piece_member.c",
                     "functions": ["func_piece_member"]}],
        "headers": ["include/piece_owner.h"],
        "recipe": {"ccver": "2.7.2-cdk", "ccflags": "", "asflags": ""},
        "data": [datum("D_ALPHA", 2, 1, ".sdata.D_ALPHA"),
                 datum("D_BETA", 8, 2, ".sdata.D_BETA"),
                 datum("D_GAMMA", 16, 4, ".sbss.D_GAMMA")],
        "data_pieces": [{"symbol": "D_ALPHA", "source_section": ".sdata", "alignment": 1},
                        {"symbol": "D_BETA", "source_section": ".sdata", "alignment": 2},
                        {"symbol": "D_GAMMA", "source_section": ".sbss", "alignment": 4}],
        "evidence": "docs/evidence/piece_owner.md",
    }


class DataPieceManifest(unittest.TestCase):
    def setUp(self):
        self.tmp = tempfile.TemporaryDirectory()
        self.addCleanup(self.tmp.cleanup)
        self.root = Path(self.tmp.name)
        (self.root / "assets").mkdir()
        (self.root / "config").mkdir()
        self.raw = b"ab\x7fcdefg\x34\x12hijklm" + b"\0" * 4 + b"pqrs"
        self.assertEqual(len(self.raw), 24)
        (self.root / "assets/000800.bin").write_bytes(self.raw)
        self.module = fixture_module(self.raw)
        self.manifest = self.root / "config/slus_modules.json"

    def load(self, module=None):
        self.manifest.write_text(json.dumps({"version": 1,
                                             "modules": [module if module is not None else self.module]}))
        return sm.load_manifest(self.manifest)

    def reject(self, change, message, *, direct=True):
        module = copy.deepcopy(self.module)
        change(module)
        if direct:
            with self.assertRaisesRegex(sm.ModuleError, message):
                sm.data_piece_plan(module)
        with self.assertRaisesRegex(sm.ModuleError, message):
            self.load(module)

    def test_legacy_module_keeps_exact_decoded_shape_and_contiguous_carve(self):
        legacy = copy.deepcopy(self.module)
        del legacy["data_pieces"]
        legacy["data"] = [
            {"symbol": "D_ALPHA", "asset": "assets/000800.bin", "offset": 2,
             "size": 1, "vram": 0x80000002, "bytes": "7f", "section": ".sdata"},
            {"symbol": "D_NEXT", "asset": "assets/000800.bin", "offset": 3,
             "size": 2, "vram": 0x80000003, "bytes": "6364", "section": ".sdata"},
        ]
        parsed = self.load(legacy)
        self.assertEqual(parsed, [legacy])
        self.assertEqual(sm.data_piece_plan(parsed[0]), [])
        self.assertEqual(sm.data_sections(parsed[0]), {".sdata": legacy["data"]})
        plans = sm.plan_asset_carves(parsed, self.root)
        self.assertEqual(len(plans), 1)
        slots = plans[0]["slots"]
        self.assertEqual([(s["kind"], s["start"], s["end"]) for s in slots],
                         [("chunk", 0, 2), ("module_data", 2, 5), ("chunk", 5, 24)])
        self.assertEqual(slots[1]["section"], ".sdata")
        self.assertEqual(slots[1]["symbols"], ["D_ALPHA", "D_NEXT"])
        self.assertEqual(slots[1]["object"], "build/src/piece_owner.o")
        chunks = sm.materialize_asset_chunks(plans, self.root)
        self.assertEqual([(self.root / c["input"]).read_bytes() for c in chunks],
                         [b"ab", self.raw[5:]])
        linked = sm.rewrite_ordered_linker_script(
            "    build/assets/000800.o(.data);\n", plans)
        self.assertEqual(linked.count("build/src/piece_owner.o(.sdata);"), 1)
        self.assertNotIn(".sdata.D_ALPHA", linked)

    def test_named_piece_plan_and_real_nonzero_gap_carve(self):
        modules = self.load()
        module = modules[0]
        self.assertEqual(sm.data_piece_plan(module), [
            {"symbol": "D_ALPHA", "size": 1, "section": ".sdata.D_ALPHA", "alignment": 1,
             "source_section": ".sdata"},
            {"symbol": "D_BETA", "size": 2, "section": ".sdata.D_BETA", "alignment": 2,
             "source_section": ".sdata"},
            {"symbol": "D_GAMMA", "size": 4, "section": ".sbss.D_GAMMA", "alignment": 4,
             "source_section": ".sbss"}])
        sections = sm.data_sections(module)
        self.assertEqual(list(sections), [".sdata.D_ALPHA", ".sdata.D_BETA", ".sbss.D_GAMMA"])
        self.assertTrue(all(len(records) == 1 for records in sections.values()))
        plans = sm.plan_asset_carves(modules, self.root)
        slots = plans[0]["slots"]
        self.assertEqual([s["kind"] for s in slots],
                         ["chunk", "module_data", "chunk", "module_data", "chunk", "module_data", "chunk"])
        self.assertEqual([(s["start"], s["end"]) for s in slots],
                         [(0, 2), (2, 3), (3, 8), (8, 10), (10, 16), (16, 20), (20, 24)])
        self.assertEqual([s["section"] for s in slots if s["kind"] == "module_data"],
                         [".sdata.D_ALPHA", ".sdata.D_BETA", ".sbss.D_GAMMA"])
        chunks = sm.materialize_asset_chunks(plans, self.root)
        self.assertEqual(b"".join((self.root / c["input"]).read_bytes() for c in chunks),
                         self.raw[:2] + self.raw[3:8] + self.raw[10:16] + self.raw[20:])
        self.assertEqual([(self.root / c["input"]).read_bytes() for c in chunks],
                         [b"ab", b"cdefg", b"hijklm", b"pqrs"])
        base = "SECTIONS {\n  .payload : SUBALIGN(1)\n  {\n    build/assets/000800.o(.data);\n  }\n}\n"
        linked = sm.rewrite_ordered_linker_script(base, plans)
        self.assertNotIn("build/assets/000800.o(.data);", linked)
        for section in (".sdata.D_ALPHA", ".sdata.D_BETA", ".sbss.D_GAMMA"):
            self.assertEqual(linked.count(f"build/src/piece_owner.o({section});"), 1)
        self.assertLess(linked.index("000000_000002"), linked.index(".sdata.D_ALPHA"))
        self.assertLess(linked.index(".sdata.D_ALPHA"), linked.index("000003_000008"))
        self.assertLess(linked.index("000003_000008"), linked.index(".sdata.D_BETA"))
        self.assertEqual(sm.filter_owned_symbols(
            "D_ALPHA = 0x80000002;\nD_BETA = 0x80000008;\nD_GAMMA = 0x80000010;\nD_NEIGHBOR = 0x80000003;\n",
            modules), "D_NEIGHBOR = 0x80000003;\n")

    def test_missing_duplicate_or_extra_piece_rejected(self):
        self.reject(lambda m: m.update(data_pieces=[]), "nonempty")
        self.reject(lambda m: m["data_pieces"].pop(), "missing data piece")
        self.reject(lambda m: m["data_pieces"].append(copy.deepcopy(m["data_pieces"][0])), "duplicate piece")
        self.reject(lambda m: m["data_pieces"][0].update(symbol="D_UNKNOWN"), "no data record")
        self.reject(lambda m: m["data"].append(copy.deepcopy(m["data"][0])), "duplicate .*symbol")
        self.reject(lambda m: m["data_pieces"][0].update(extra=1), "expected keys")
        self.reject(lambda m: m["data_pieces"][0].pop("alignment"), "expected keys")
        self.reject(lambda m: m["data_pieces"][0].update(symbol="bad-name"), "invalid identifier")
        self.reject(lambda m: m.update(name="bad/name"), "invalid.*name")

    def test_bad_sections_and_alignments_rejected(self):
        self.reject(lambda m: m["data_pieces"][0].update(source_section=".data"), "source_section")
        self.reject(lambda m: m["data"][0].update(section=".sdata.D_OTHER"), "destination section")
        self.reject(lambda m: m["data"][0].update(section=".sdata_bad.D_ALPHA"), "unsupported data section")
        self.reject(lambda m: m["data"][2].update(bytes="01000000"), "sbss storage must be zero")
        for alignment in (0, 3, 0x2000, True, "2"):
            self.reject(lambda m, a=alignment: m["data_pieces"][0].update(alignment=a), "alignment")
        self.reject(lambda m: m["data_pieces"][0].update(alignment=4), "not aligned")

    def test_named_section_without_opt_in_and_unknown_keys_rejected(self):
        module = copy.deepcopy(self.module)
        del module["data_pieces"]
        with self.assertRaisesRegex(sm.ModuleError, "unsupported data section"):
            sm.data_sections(module)
        with self.assertRaisesRegex(sm.ModuleError, "unsupported data section"):
            self.load(module)
        self.reject(lambda m: m["data"][0].update(extra=1), "expected keys")
        module = copy.deepcopy(self.module)
        module["unexpected"] = 1
        with self.assertRaisesRegex(sm.ModuleError, "unexpected keys"):
            sm.data_piece_plan(module)
        with self.assertRaisesRegex(sm.ModuleError, "expected keys"):
            self.load(module)

    def test_duplicate_ownership_is_rejected_by_direct_carver_and_filter(self):
        first = self.load()[0]
        second = copy.deepcopy(first)
        second["name"] = "other_owner"
        second["source"] = "src/other_owner.c"
        with self.assertRaisesRegex(sm.ModuleError, "duplicate data ownership"):
            sm.plan_asset_carves([first, second], self.root)
        with self.assertRaisesRegex(sm.ModuleError, "duplicate data ownership"):
            sm.filter_owned_symbols("D_ALPHA = 0x80000002;\n", [first, second])
        second["members"] = [{"id": "slus/other_member", "source": "src/other_member.c",
                              "functions": ["func_other_member"]}]
        self.manifest.write_text(json.dumps({"version": 1, "modules": [first, second]}))
        with self.assertRaisesRegex(sm.ModuleError, "duplicate symbol"):
            sm.load_manifest(self.manifest)


if __name__ == "__main__":
    unittest.main()
