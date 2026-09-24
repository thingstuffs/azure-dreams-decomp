"""Portable ELF data-piece integration and refusal tests using GNU MIPS tools."""

from __future__ import annotations

import json
from pathlib import Path
import shutil
import struct
import subprocess
import sys
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[2]
BUILD = ROOT / "tools/build"
sys.path.insert(0, str(BUILD))
sys.path.insert(0, str(ROOT / "tools"))
from fidelity.objread import read_elf  # noqa: E402
from slus_data_pieces import _parse, apply_data_pieces, split_elf, verify_data_pieces  # noqa: E402


ASM = """.set noreorder
.text
.globl probe
.ent probe
probe:
lw $2,%gp_rel(alpha)($28)
lw $3,%gp_rel(beta+4)($28)
lui $4,%hi(beta+4)
addiu $4,$4,%lo(beta+4)
jr $31
nop
.end probe
.sdata
.globl alpha
.type alpha,@object
alpha: .word 0x12345678
.size alpha,4
.globl beta
.type beta,@object
beta: .word 0x90abcdef,0x76543210
.size beta,8
.data
.globl pointer
pointer: .word alpha
"""

SBSS_ASM = """.set noreorder
.text
.globl zero_probe
.ent zero_probe
zero_probe:
lw $2,%gp_rel(gamma)($28)
sw $2,%gp_rel(delta)($28)
jr $31
nop
.end zero_probe
.section .sbss,"aw",@nobits
.align 2
.globl gamma
.type gamma,@object
gamma: .space 4
.size gamma,4
.globl delta
.type delta,@object
delta: .space 4
.size delta,4
"""

PIECES = [dict(symbol=name, size=size, source_section=".sdata",
               section=f".sdata.{name}", alignment=4)
          for name, size in (("alpha", 4), ("beta", 8))]
SBSS_PIECES = [dict(symbol=name, size=4, source_section=".sbss",
                    section=f".sbss.{name}", alignment=4)
               for name in ("gamma", "delta")]


def module_for(pieces):
    data = []
    for index, piece in enumerate(pieces):
        data.append(dict(symbol=piece["symbol"], asset="assets/1000.bin",
                         offset=index * 8, size=piece["size"],
                         vram=0x80010000 + index * 8,
                         bytes="00" * piece["size"], section=piece["section"]))
    return {"name": "synthetic_split", "data": data,
            "data_pieces": [{key: piece[key] for key in
                             ("symbol", "source_section", "alignment")} for piece in pieces]}


def changed_section_word(raw, section, word_offset, value):
    parsed = _parse(raw)
    index = parsed["names"].index(section)
    shoff = struct.unpack_from("<I", raw, 0x20)[0]
    output = bytearray(raw)
    struct.pack_into("<I", output, shoff + index * 40 + word_offset, value)
    return bytes(output)


@unittest.skipUnless(all(shutil.which(name) for name in
                         ("mipsel-linux-gnu-as", "mipsel-linux-gnu-ld")),
                     "GNU MIPS assembler/linker unavailable")
class DataPieceElfTest(unittest.TestCase):
    def setUp(self):
        self.tmp = tempfile.TemporaryDirectory()
        self.addCleanup(self.tmp.cleanup)
        self.dir = Path(self.tmp.name)

    def run_tool(self, *args):
        result = subprocess.run(args, cwd=self.dir, capture_output=True, text=True)
        self.assertEqual(result.returncode, 0, result.stdout + result.stderr)
        return result.stdout

    def assemble(self, name, source):
        (self.dir / f"{name}.s").write_text(source)
        self.run_tool("mipsel-linux-gnu-as", "-EL", "-march=r3000", "-G8",
                      "-o", f"{name}.o", f"{name}.s")
        return (self.dir / f"{name}.o").read_bytes()

    def link(self, name, obj, selector):
        script = ("SECTIONS { _gp = 0x18000; .text 0x1000 : { *(.text) } "
                  ".data 0x2000 : { *(.data) } " + selector +
                  " /DISCARD/ : { *(.reginfo) *(.MIPS.abiflags) *(.pdr) "
                  "*(.gnu.attributes) } }")
        (self.dir / f"{name}.ld").write_text(script)
        self.run_tool("mipsel-linux-gnu-ld", "-EL", "-T", f"{name}.ld",
                      "-o", f"{name}.elf", obj)
        return read_elf((self.dir / f"{name}.elf").read_bytes())

    def test_sparse_gnu_link_preserves_gp_hi_lo_r32_and_nonzero_data(self):
        original = self.assemble("original", ASM)
        transformed, proof = split_elf(original, PIECES)
        (self.dir / "split.o").write_bytes(transformed)
        raw, split = read_elf(original), read_elf(transformed)
        self.assertEqual(raw.sections[".text"], split.sections[".text"])
        self.assertEqual(raw.relocs, split.relocs)
        self.assertEqual(proof["relocation_entries"], 6)
        self.assertEqual(split.sections[".sdata.alpha"], bytes.fromhex("78563412"))
        self.assertEqual(split.sections[".sdata.beta"], bytes.fromhex("efcdab9010325476"))

        old = self.link("old", "original.o", ".owned 0x10000 : { *(.sdata) }")
        contiguous = self.link("contiguous", "split.o",
                               ".owned 0x10000 : { *(.sdata.alpha) *(.sdata.beta) }")
        self.assertEqual(old.sections[".text"], contiguous.sections[".text"])
        self.assertEqual(old.sections[".data"], contiguous.sections[".data"])
        self.assertEqual(old.sections[".owned"][:12], contiguous.sections[".owned"][:12])

        scattered = self.link("scattered", "split.o",
                              ".beta 0x11000 : { *(.sdata.beta) } "
                              ".alpha 0x11020 : { *(.sdata.alpha) }")
        words = struct.unpack("<6I", scattered.sections[".text"][:24])
        self.assertEqual(words[0] & 0xFFFF, (0x11020 - 0x18000) & 0xFFFF)
        self.assertEqual(words[1] & 0xFFFF, (0x11004 - 0x18000) & 0xFFFF)
        self.assertEqual(((words[2] & 0xFFFF) << 16) +
                         struct.unpack("<h", struct.pack("<H", words[3] & 0xFFFF))[0], 0x11004)
        self.assertEqual(struct.unpack_from("<I", scattered.sections[".data"])[0], 0x11020)
        self.assertEqual(scattered.sections[".alpha"], bytes.fromhex("78563412"))
        self.assertEqual(scattered.sections[".beta"], bytes.fromhex("efcdab9010325476"))

    def test_sbss_nobits_pieces_and_gnu_link(self):
        original = self.assemble("zero", SBSS_ASM)
        transformed, proof = split_elf(original, SBSS_PIECES)
        (self.dir / "zero_split.o").write_bytes(transformed)
        parsed = read_elf(transformed)
        self.assertEqual(parsed.sections[".sbss.gamma"], bytes(4))
        self.assertEqual(parsed.sections[".sbss.delta"], bytes(4))
        self.assertEqual(proof["emptied_source_sections"][".sbss"]["kind"], "NOBITS")
        linked = self.link("zero_scattered", "zero_split.o",
                           ".gamma 0x11040 (NOLOAD) : { *(.sbss.gamma) } "
                           ".delta 0x11060 (NOLOAD) : { *(.sbss.delta) }")
        words = struct.unpack("<4I", linked.sections[".text"][:16])
        self.assertEqual(words[0] & 0xFFFF, (0x11040 - 0x18000) & 0xFFFF)
        self.assertEqual(words[1] & 0xFFFF, (0x11060 - 0x18000) & 0xFFFF)
        self.assertEqual(linked.sections[".gamma"], bytes(4))
        self.assertEqual(linked.sections[".delta"], bytes(4))

    def test_apply_verify_and_tamper_refusals(self):
        original = self.assemble("module", ASM)
        path = self.dir / "module.o"
        module = module_for(PIECES)
        receipt = apply_data_pieces(path, module)
        self.assertEqual(path.with_suffix(".unsplit.o").read_bytes(), original)
        self.assertEqual(verify_data_pieces(path, module), receipt)
        self.assertEqual(receipt["pre_object_sha256"], receipt["split_elf"]["input_sha256"])
        self.assertEqual(receipt["post_object_sha256"], receipt["split_elf"]["output_sha256"])
        with self.assertRaises(ValueError):
            apply_data_pieces(path, module)
        sidecar = path.with_suffix(".data-pieces.json")
        recorded = sidecar.read_bytes()
        changed = json.loads(recorded)
        changed["split_elf"]["relocation_entries_unchanged"] = False
        sidecar.write_text(json.dumps(changed))
        with self.assertRaisesRegex(ValueError, "receipt differs"):
            verify_data_pieces(path, module)
        sidecar.write_bytes(recorded)
        path.write_bytes(path.read_bytes() + b"X")
        with self.assertRaisesRegex(ValueError, "object differs"):
            verify_data_pieces(path, module)

    def test_recompile_replaces_generated_sidecars_but_rejects_double_apply(self):
        first_raw = self.assemble("epoch", ASM)
        path = self.dir / "epoch.o"
        module = module_for(PIECES)
        first_receipt = apply_data_pieces(path, module)
        with self.assertRaises(ValueError):
            apply_data_pieces(path, module)

        second_source = (ASM.replace("0x12345678", "0x2468ace0")
                         .replace("lw $2,%gp_rel(alpha)($28)", "lw $5,%gp_rel(alpha)($28)"))
        second_raw = self.assemble("epoch", second_source)
        self.assertNotEqual(first_raw, second_raw)
        second_receipt = apply_data_pieces(path, module)
        self.assertNotEqual(first_receipt["pre_object_sha256"], second_receipt["pre_object_sha256"])
        self.assertEqual(path.with_suffix(".unsplit.o").read_bytes(), second_raw)
        self.assertEqual(verify_data_pieces(path, module), second_receipt)
        self.assertEqual(json.loads(path.with_suffix(".data-pieces.json").read_text()), second_receipt)
        with self.assertRaises(ValueError):
            apply_data_pieces(path, module)

    def test_cli_verify_stamp_requires_valid_receipt(self):
        self.assemble("cli", ASM)
        path = self.dir / "cli.o"
        module = module_for(PIECES)
        module.update(source="src/synthetic_split_owned.c",
                      members=[{"id": "slus/w_00000000", "source": "src/w_00000000.c",
                                "functions": ["probe"]}], headers=[],
                      recipe={"ccver": "2.7.2-cdk", "ccflags": "", "asflags": ""},
                      evidence="docs/evidence/synthetic_split.md")
        manifest = self.dir / "manifest.json"
        manifest.write_text(json.dumps({"version": 1, "modules": [module]}))
        tool = BUILD / "slus_data_pieces.py"
        self.run_tool(sys.executable, str(tool), "--manifest", str(manifest),
                      "--module", module["name"], "--object", str(path))
        stamp = self.dir / "stamps/cli.verified"
        self.run_tool(sys.executable, str(tool), "--manifest", str(manifest),
                      "--module", module["name"], "--object", str(path),
                      "--verify", "--stamp", str(stamp))
        stamped = json.loads(stamp.read_text())
        self.assertTrue(stamped["verified"])
        self.assertEqual(stamped["post_object_sha256"], verify_data_pieces(path, module)["post_object_sha256"])
        stamp.unlink()
        path.with_suffix(".data-pieces.json").write_text("{}")
        failed = subprocess.run([sys.executable, str(tool), "--manifest", str(manifest),
                                 "--module", module["name"], "--object", str(path),
                                 "--verify", "--stamp", str(stamp)],
                                cwd=self.dir, capture_output=True, text=True)
        self.assertNotEqual(failed.returncode, 0)
        self.assertFalse(stamp.exists())

    def test_empty_plan_is_noop_and_symlink_output_refused(self):
        original = self.assemble("plain", ASM)
        path = self.dir / "plain.o"
        module = {"name": "plain", "data": []}
        self.assertIsNone(apply_data_pieces(path, module))
        self.assertIsNone(verify_data_pieces(path, module))
        self.assertEqual(path.read_bytes(), original)
        self.assertFalse(path.with_suffix(".unsplit.o").exists())
        alias = self.dir / "alias.o"
        alias.symlink_to(path)
        with self.assertRaisesRegex(ValueError, "symlink"):
            apply_data_pieces(alias, module_for(PIECES))

    def test_refuses_unsafe_data_and_section_plans_without_writes(self):
        original = self.assemble("unsafe", ASM)
        cases = [
            ("source mismatch", ASM, [dict(PIECES[0], source_section=".sbss"), PIECES[1]]),
            ("missing symbol", ASM, [dict(PIECES[0], symbol="absent"), PIECES[1]]),
            ("omitted owner", ASM, PIECES[:1]),
            ("bad alignment", ASM, [dict(PIECES[0], alignment=3), PIECES[1]]),
            ("size mismatch", ASM, [dict(PIECES[0], size=3), PIECES[1]]),
            ("destination collision", ASM, [dict(PIECES[0], section=PIECES[1]["section"]), PIECES[1]]),
            ("nonzero gap", ASM.replace(".globl beta", ".byte 0x5a\n.align 2\n.globl beta"), PIECES),
            ("relocation from data", ASM.replace("alpha: .word 0x12345678", "alpha: .word pointer"), PIECES),
            ("cross-object addend", ASM.replace("%gp_rel(alpha)", "%gp_rel(alpha+4)"), PIECES),
            ("local base", ASM.replace(".globl beta\n", ""), PIECES),
        ]
        for index, (label, source, pieces) in enumerate(cases):
            with self.subTest(label=label):
                raw = original if source == ASM else self.assemble(f"bad{index}", source)
                with self.assertRaises(ValueError):
                    split_elf(raw, pieces)
        path = self.dir / "unsafe.o"
        module = module_for(PIECES)
        original_path = path.read_bytes()
        module["data_pieces"][0]["source_section"] = ".sbss"
        with self.assertRaises(ValueError):
            apply_data_pieces(path, module)
        self.assertEqual(path.read_bytes(), original_path)
        self.assertFalse(path.with_suffix(".unsplit.o").exists())
        self.assertFalse(path.with_suffix(".data-pieces.json").exists())

    def test_rejects_unsupported_source_flags_metadata_and_huge_nobits(self):
        original = self.assemble("malformed", ASM)
        parsed = _parse(original)
        source = parsed["sections"][parsed["names"].index(".sdata")]
        self.assertEqual(source[2], 0x10000003)
        for name, field_offset, value, error in (
                ("group", 8, source[2] | 0x200, "unsupported source section flags"),
                ("merge", 8, source[2] | 0x10, "unsupported source section flags"),
                ("tls", 8, source[2] | 0x400, "unsupported source section flags"),
                ("link_order", 8, source[2] | 0x80, "unsupported source section flags"),
                ("missing_gp", 8, source[2] & ~0x10000000, "unsupported source section flags"),
                ("sh_link", 24, 1, "unsupported source sh_link/sh_info/sh_entsize"),
                ("sh_info", 28, 1, "unsupported source sh_link/sh_info/sh_entsize"),
                ("sh_entsize", 36, 4, "unsupported source sh_link/sh_info/sh_entsize")):
            with self.subTest(name=name):
                malformed = changed_section_word(original, ".sdata", field_offset, value)
                with self.assertRaisesRegex(ValueError, error):
                    split_elf(malformed, PIECES)
        huge_bss = changed_section_word(original, ".bss", 20, 0x40000000)
        with self.assertRaisesRegex(ValueError, "NOBITS extent exceeds"):
            split_elf(huge_bss, PIECES)


if __name__ == "__main__":
    unittest.main()
