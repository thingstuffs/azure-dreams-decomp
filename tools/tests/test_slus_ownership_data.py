"""Ownership proof must account for each initialized and zero-filled input section."""

import shutil
import subprocess
import sys
import tempfile
import unittest
from pathlib import Path
from unittest.mock import patch

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))
from fidelity import aspsx_diff as A
from fidelity import prove_slus_ownership as prover
from fidelity.objread import Obj


def datum(symbol, offset, vram, raw, section):
    return {"symbol": symbol, "asset": "assets/800.bin", "offset": offset,
            "size": len(raw), "vram": vram, "bytes": raw.hex(), "section": section}


class DataProof(unittest.TestCase):
    def setUp(self):
        self.module = {"name": "mixed_storage", "data": [
            datum("D_INIT", 4, 0x8002D004, b"\x34\x12", ".sdata"),
            datum("D_ZERO", 6, 0x8002D006, b"\x00\x00", ".sbss"),
        ]}
        self.obj = Obj("elf")
        self.obj.sections = {".sdata": b"\x34\x12", ".sbss": b"\x00\x00"}
        self.obj.symbols = {"D_INIT": (".sdata", 0, "global", 2),
                            "D_ZERO": (".sbss", 0, "local", 2)}
        self.linked = {"D_INIT": {"address": 0x8002D004, "kind": "T"},
                       "D_ZERO": {"address": 0x8002D006, "kind": "t"}}
        self.image = bytearray(0x808)
        self.image[0x804:0x806] = b"\x34\x12"

    def prove(self):
        return prover.prove_data(self.module, self.obj, self.linked, bytes(self.image))

    def test_exact_initialized_and_local_nobits_sections(self):
        proof = self.prove()["sections"]
        self.assertEqual(proof[".sdata"]["size"], 2)
        self.assertEqual(proof[".sdata"]["bytes"], "3412")
        self.assertEqual(proof[".sbss"]["size"], 2)
        self.assertEqual(proof[".sbss"]["bytes"], "0000")
        self.assertEqual(proof[".sbss"]["symbols"][0]["object_binding"], "local")

    def test_missing_or_wrong_input_section_is_rejected(self):
        del self.obj.sections[".sbss"]
        with self.assertRaisesRegex(ValueError, "section bytes or size"):
            self.prove()
        self.obj.sections[".sbss"] = b"\x00\x00"
        self.obj.symbols["D_ZERO"] = (".sdata", 0, "local", 2)
        with self.assertRaisesRegex(ValueError, "object ownership/section/offset"):
            self.prove()

    def test_each_section_must_have_exact_size_and_payload(self):
        for section, wrong in ((".sdata", b"\x34"), (".sdata", b"\x35\x12"),
                               (".sbss", b"\x00"), (".sbss", b"\x00" * 4),
                               (".sbss", b"\x01\x00")):
            with self.subTest(section=section, wrong=wrong):
                original = self.obj.sections[section]
                self.obj.sections[section] = wrong
                with self.assertRaisesRegex(ValueError, "section bytes or size"):
                    self.prove()
                self.obj.sections[section] = original

    def test_symbol_offset_and_undefined_common_absolute_claims_are_rejected(self):
        original = self.obj.symbols["D_ZERO"]
        for claim in ((".sbss", 1, "local", 2), (None, 0, "common", 2),
                      (None, 0x8002D006, "abs", 2)):
            with self.subTest(claim=claim):
                self.obj.symbols["D_ZERO"] = claim
                with self.assertRaisesRegex(ValueError, "object ownership/section/offset"):
                    self.prove()
        self.obj.symbols["D_ZERO"] = original
        for kind in ("A", "C", "U"):
            with self.subTest(linked_kind=kind):
                self.linked["D_ZERO"]["kind"] = kind
                with self.assertRaisesRegex(ValueError, "linked ownership/address"):
                    self.prove()

    def test_missing_or_wrong_linked_vma_and_image_bytes_are_rejected(self):
        self.linked["D_ZERO"]["address"] += 2
        with self.assertRaisesRegex(ValueError, "linked ownership/address"):
            self.prove()
        self.linked["D_ZERO"]["address"] -= 2
        del self.linked["D_ZERO"]
        with self.assertRaisesRegex(ValueError, "linked ownership/address"):
            self.prove()
        self.linked["D_ZERO"] = {"address": 0x8002D006, "kind": "t"}
        self.image[0x806] = 1
        with self.assertRaisesRegex(ValueError, "linked data bytes"):
            self.prove()
        self.image[0x806] = 0
        self.image = self.image[:-1]
        with self.assertRaisesRegex(ValueError, "linked data bytes"):
            self.prove()

    def test_nonzero_declared_sbss_is_rejected_even_if_image_agrees(self):
        self.module["data"][1]["bytes"] = "0100"
        self.obj.sections[".sbss"] = b"\x01\x00"
        self.image[0x806:0x808] = b"\x01\x00"
        with self.assertRaisesRegex(ValueError, "sbss storage must be zero"):
            self.prove()

    def test_ambiguous_nm_name_is_rejected_before_obj_symbol_map_can_collapse_it(self):
        output = "00000000 T D_INIT\n00000002 t D_INIT\n"
        with patch.object(prover.subprocess, "check_output", return_value=output):
            with self.assertRaisesRegex(ValueError, "ambiguous linked owned symbol"):
                prover.symbols(Path("some.o"), {"D_INIT"})

    @unittest.skipUnless(shutil.which("mipsel-linux-gnu-as"), "MIPS assembler unavailable")
    def test_real_elf_nobits_is_materialized_as_zero_storage(self):
        with tempfile.TemporaryDirectory() as temp:
            root = Path(temp)
            source = root / "owner.s"
            obj = root / "owner.o"
            source.write_text('.section .sdata,"aw"\n.globl D_INIT\nD_INIT:\n.hword 0x1234\n'
                              '.section .sbss,"aw",@nobits\nD_ZERO:\n.space 2\n')
            subprocess.run(("mipsel-linux-gnu-as", "-EL", "-march=r3000", "-o", str(obj), str(source)),
                           check=True, capture_output=True, text=True)
            parsed = A.read_elf(obj.read_bytes())
            self.assertEqual(parsed.sections[".sbss"], b"\x00\x00")
            self.assertEqual(parsed.symbols["D_ZERO"][:3], (".sbss", 0, "local"))
            self.obj = parsed
            self.assertEqual(self.prove()["sections"][".sbss"]["bytes"], "0000")


if __name__ == "__main__":
    unittest.main()
