"""Rodata owners: .rodata manifest records and GNU-as section-end padding trim (lane r80_opus_slusrodata).

Drop into tools/tests/ with the patched tools/build/{slus_modules,configure,slus_rodata_trim}.py.
"""
import json
import shutil
import subprocess
import sys
import tempfile
import unittest
from pathlib import Path

BUILD = Path(__file__).resolve().parents[1] / "build"
sys.path.insert(0, str(BUILD))
import slus_modules as sm  # noqa: E402
import slus_rodata_trim as trim  # noqa: E402

AS = shutil.which("mipsel-linux-gnu-as")


def assemble(td, words, tail_words=()):
    """A .rodata of `words` label-address words (R_MIPS_32) then `tail_words` literal words."""
    src = ["\t.text", "f:", "\tnop"] + ["\t.rdata", "\t.align 3"]
    src += ["\t.word f"] * words + [f"\t.word {w}" for w in tail_words]
    s = Path(td) / "t.s"
    s.write_text("\n".join(src) + "\n")
    o = Path(td) / "t.o"
    subprocess.run([AS, "-EL", "-march=r3000", str(s), "-o", str(o)], check=True)
    return o


def rodata_size(o):
    out = subprocess.run(["mipsel-linux-gnu-objdump", "-h", str(o)], capture_output=True, text=True, check=True).stdout
    for line in out.splitlines():
        parts = line.split()
        if len(parts) > 2 and parts[1] == ".rodata":
            return int(parts[2], 16)
    return None


@unittest.skipUnless(AS, "mipsel binutils unavailable")
class RodataTrimTest(unittest.TestCase):
    def test_trims_zero_end_padding_only(self):
        with tempfile.TemporaryDirectory() as td:
            o = assemble(td, 7)                       # 28 B of table, as pads to 32
            self.assertEqual(rodata_size(o), 32)
            data = bytearray(o.read_bytes())
            res = trim.trim(data, 28)
            self.assertEqual(res["trimmed"], 4)
            o.write_bytes(data)
            self.assertEqual(rodata_size(o), 28)
            relocs = subprocess.run(["mipsel-linux-gnu-objdump", "-r", "-j", ".rodata", str(o)],
                                    capture_output=True, text=True, check=True).stdout
            self.assertEqual(relocs.count("R_MIPS_32"), 7)

    def test_no_op_when_already_exact(self):
        with tempfile.TemporaryDirectory() as td:
            data = bytearray(assemble(td, 8).read_bytes())
            self.assertEqual(trim.trim(data, 32)["trimmed"], 0)

    def test_refuses_relocated_or_nonzero_tail(self):
        with tempfile.TemporaryDirectory() as td:
            data = bytearray(assemble(td, 7).read_bytes())
            with self.assertRaisesRegex(ValueError, "relocation"):
                trim.trim(data, 24)                   # would cut a table word
        with tempfile.TemporaryDirectory() as td:
            data = bytearray(assemble(td, 6, tail_words=(0x1234,)).read_bytes())
            with self.assertRaisesRegex(ValueError, "not zero padding"):
                trim.trim(data, 24)

    def test_refuses_more_than_alignment_padding(self):
        with tempfile.TemporaryDirectory() as td:
            data = bytearray(assemble(td, 5, tail_words=(0,) * 5).read_bytes())   # 40 B -> 48, last 28 zero
            with self.assertRaisesRegex(ValueError, "alignment padding"):
                trim.trim(data, 20)

    def test_refuses_growth(self):
        with tempfile.TemporaryDirectory() as td:
            data = bytearray(assemble(td, 7).read_bytes())
            with self.assertRaisesRegex(ValueError, "smaller than the owned span"):
                trim.trim(data, 40)


class RodataManifestTest(unittest.TestCase):
    def setUp(self):
        self.td = tempfile.TemporaryDirectory()
        self.root = Path(self.td.name)
        (self.root / "assets").mkdir()
        self.blob = bytes(range(64))
        (self.root / "assets/800.bin").write_bytes(self.blob)
        self.module = {"name": "jtbl_row", "source": "src/w_row_jtbl_owned.c",
                       "members": [{"id": "slus/w_row", "source": "src/w_row.c", "functions": ["func_row"]}],
                       "headers": ["include/common.h"], "recipe": {"ccver": "2.7.2", "ccflags": "", "asflags": ""},
                       "data": [{"symbol": "jtbl_8002D010", "asset": "assets/800.bin", "offset": 16, "size": 12,
                                 "vram": 0x8002D010, "bytes": self.blob[16:28].hex(), "section": ".rodata"}],
                       "evidence": "docs/evidence/slus_rodata_migration.md"}
        self.manifest = self.root / "m.json"

    def tearDown(self):
        self.td.cleanup()

    def save(self, module):
        self.manifest.write_text(json.dumps({"version": 1, "modules": [module]}))

    def test_rodata_record_carves_the_rdata_blob(self):
        self.save(self.module)
        mods = sm.load_manifest(self.manifest)
        plan = sm.plan_asset_carves(mods, self.root)
        slots = [(s["kind"], s["start"], s["end"], s["section"]) for s in plan[0]["slots"]]
        self.assertEqual(slots, [("chunk", 0, 16, ".data"), ("module_data", 16, 28, ".rodata"),
                                 ("chunk", 28, 64, ".data")])
        text = sm.rewrite_ordered_linker_script("    build/assets/800.o(.data);\n", plan)
        self.assertIn("build/src/w_row_jtbl_owned.o(.rodata);", text)
        self.assertEqual(sm.filter_owned_symbols("jtbl_8002D010 = 0x8002D010;\nkeep = 0x1;\n", mods), "keep = 0x1;\n")

    def test_rodata_bytes_must_match_the_blob(self):
        bad = json.loads(json.dumps(self.module))
        bad["data"][0]["bytes"] = "00" * 12
        self.save(bad)
        with self.assertRaisesRegex(sm.ModuleError, "initializer bytes differ"):
            sm.plan_asset_carves(sm.load_manifest(self.manifest), self.root)

    def test_named_rodata_and_other_sections_still_rejected(self):
        for section in (".rodata.jtbl", ".rdata", ".data"):
            bad = json.loads(json.dumps(self.module))
            bad["data"][0]["section"] = section
            self.save(bad)
            with self.assertRaisesRegex(sm.ModuleError, "unsupported data section"):
                sm.load_manifest(self.manifest)


if __name__ == "__main__":
    unittest.main()
