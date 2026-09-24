"""Raw-asset carves must not gain linker SUBALIGN padding at a halfword boundary."""

import shutil
import subprocess
import sys
import tempfile
import unittest
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / "build"))
import slus_modules as modules  # noqa: E402


ASSET = "assets/000800.bin"
SLOT = "build/assets/000800.o(.data);"


def owner(raw, *, size, offset=4):
    return {"name": "owner", "source": "src/owner.c",
            "data": [{"symbol": "D_HALF", "asset": ASSET, "offset": offset,
                      "size": size, "vram": 0x80000000 + offset,
                      "bytes": raw[offset:offset + size].hex(), "section": ".sdata"}]}


def linker_script():
    return ("SECTIONS\n{\n"
            "  .before 0x80000100 : SUBALIGN(8)\n  {\n    *(.before)\n  }\n"
            "  .payload 0x80000000 : SUBALIGN(4)\n  {\n"
            f"    {SLOT}\n"
            "  }\n"
            "  .after 0x80000200 : SUBALIGN(16)\n  {\n    *(.after)\n  }\n"
            "}\n")


class CarveAlignment(unittest.TestCase):
    def setUp(self):
        self.tmp = tempfile.TemporaryDirectory()
        self.addCleanup(self.tmp.cleanup)
        self.root = Path(self.tmp.name)
        (self.root / "assets").mkdir()

    def plan(self, raw, size):
        (self.root / ASSET).write_bytes(raw)
        return modules.plan_asset_carves([owner(raw, size=size)], self.root)

    def test_absent_and_word_aligned_carves_do_not_change_subalign(self):
        script = linker_script()
        self.assertEqual(modules.rewrite_ordered_linker_script(script, []), script)
        plan = self.plan(b"ABCD" + b"1234" + b"e" * 12, 4)
        changed = modules.rewrite_ordered_linker_script(script, plan)
        self.assertEqual(changed.count("SUBALIGN(4)"), 1)
        self.assertNotIn("SUBALIGN(1)", changed)
        self.assertEqual(changed.count("build/src/owner.o(.sdata);"), 1)

    def test_halfword_carve_relaxes_only_containing_output_section(self):
        script = linker_script()
        plan = self.plan(b"ABCD" + b"\x34\x12" + b"e" * 14, 2)
        changed = modules.rewrite_ordered_linker_script(script, plan)
        self.assertIn(".before 0x80000100 : SUBALIGN(8)", changed)
        self.assertIn(".payload 0x80000000 : SUBALIGN(1)", changed)
        self.assertIn(".after 0x80000200 : SUBALIGN(16)", changed)
        self.assertEqual(changed.count("SUBALIGN(1)"), 1)
        self.assertNotIn(SLOT, changed)
        self.assertEqual([s["start"] for s in plan[0]["slots"]], [0, 4, 6])

    @unittest.skipUnless(all(shutil.which(tool) for tool in
                             ("mipsel-linux-gnu-as", "mipsel-linux-gnu-ld", "mipsel-linux-gnu-objcopy")),
                         "MIPS GNU binutils unavailable")
    def test_real_link_shifts_suffix_with_subalign_four_but_exact_with_one(self):
        raw = b"ABCD" + b"\x34\x12" + bytes(range(14))
        plan = self.plan(raw, 2)
        chunks = modules.materialize_asset_chunks(plan, self.root, assemble=True)
        self.assertEqual([((self.root / s["input"]).read_bytes(), s["end"] - s["start"])
                          for s in chunks], [(raw[:4], 4), (raw[6:], 14)])

        (self.root / "src").mkdir()
        (self.root / "build/src").mkdir(parents=True)
        (self.root / "src/owner.s").write_text(
            '.section .sdata,"aw"\n.globl D_HALF\nD_HALF:\n.hword 0x1234\n')
        subprocess.run(("mipsel-linux-gnu-as", "-EL", "-march=r3000", "-o",
                        "build/src/owner.o", "src/owner.s"), cwd=self.root, check=True,
                       capture_output=True, text=True)
        # The assembler must provide exactly the two initialized bytes, without
        # a padding definition or fabricated global to compensate for the linker.
        subsection = subprocess.run(("mipsel-linux-gnu-objcopy", "-O", "binary", "-j", ".sdata",
                                     "build/src/owner.o", "build/src/owner.sdata.bin"),
                                    cwd=self.root, check=True, capture_output=True, text=True)
        self.assertEqual(subsection.returncode, 0)
        self.assertEqual((self.root / "build/src/owner.sdata.bin").read_bytes(), raw[4:6])

        base = linker_script()
        repaired = modules.rewrite_ordered_linker_script(base, plan)
        # Compare the same three real input objects under only the output
        # section's SUBALIGN choice, isolating the linker alignment effect.
        stock = repaired.replace(".payload 0x80000000 : SUBALIGN(1)",
                                 ".payload 0x80000000 : SUBALIGN(4)")
        inputs = [s["object"] for s in plan[0]["slots"] if s["kind"] == "chunk"]
        inputs.append("build/src/owner.o")

        def link(name, script):
            (self.root / f"{name}.ld").write_text(script)
            subprocess.run(("mipsel-linux-gnu-ld", "-EL", "-T", f"{name}.ld", "-o", f"{name}.elf",
                            *inputs), cwd=self.root, check=True, capture_output=True, text=True)
            subprocess.run(("mipsel-linux-gnu-objcopy", "-O", "binary", "-j", ".payload",
                            f"{name}.elf", f"{name}.bin"), cwd=self.root, check=True,
                           capture_output=True, text=True)
            return (self.root / f"{name}.bin").read_bytes()

        shifted = link("stock", stock)
        exact = link("repaired", repaired)
        self.assertEqual(shifted, raw[:6] + b"\x00\x00" + raw[6:])
        self.assertEqual(exact, raw)


if __name__ == "__main__":
    unittest.main()
