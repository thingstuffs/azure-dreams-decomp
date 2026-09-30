"""tools/gate/overlay_local_gate.py: local_table_mismatches must compare the CONTENTS of a placed
compiler-local jump table with retail, not only its address.

Bug (2026-09-29): Option-D placements are NOLOAD - they resolve the switch's %hi/%lo table base and
nothing else, so a real `switch` whose case->label mapping differs from retail (same text bytes, a
different table) passed every window.  68 rows were found that way (func_81862ED8: retail routes
index 6 to the case-0..5 body, the C labelled it `case 6:` on the next body).

Hermetic: a tiny hand-written object (one function, one 3-entry jump table in .rodata) is assembled
with mipsel-linux-gnu-as into a temp dir, and a throw-away "container" file stands in for retail.
Nothing under the repo is read or written except the module under test.

    ./.venv/bin/python3 -m pytest tools/tests/test_local_table_mismatches.py -q
"""
import importlib.util
import shutil
import subprocess
import sys
import tempfile
import unittest
from pathlib import Path

REPO = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(REPO / "tools/gate"))
_spec = importlib.util.spec_from_file_location("olg_under_test", REPO / "tools/gate/overlay_local_gate.py")
olg = importlib.util.module_from_spec(_spec)
sys.modules[_spec.name] = olg   # dataclasses resolve the module by name
_spec.loader.exec_module(olg)

VRAM = 0x80100000          # where the function is linked
FOFF = 0x1000              # the row's file offset in the fake container
BASE = 0x800FFF00          # where retail keeps the table -> file 0xF00
TFOFF = BASE - (VRAM - FOFF)
# .text: lui/addiu/jr/nop = 16 bytes, then three one-word "case bodies"
CASES = [VRAM + 16, VRAM + 20, VRAM + 24]


def _asm(keepalive: bool) -> str:
    ka = "    .word .LB\n    .word 0\n" if keepalive else ""
    return f""".set noreorder
    .section .text.func_80100000,"ax",@progbits
    .globl func_80100000
func_80100000:
    lui $2,%hi(.LT)
    addiu $2,$2,%lo(.LT)
    jr $31
    nop
.LA: nop
.LB: nop
.LC: nop
    .section .rodata
    .align 3
{ka}.LT:
    .word .LA
    .word .LB
    .word .LC
"""


@unittest.skipUnless(shutil.which("mipsel-linux-gnu-as") and shutil.which("mipsel-linux-gnu-ld"), "needs binutils")
class LocalTableContents(unittest.TestCase):
    def setUp(self):
        self._td = tempfile.TemporaryDirectory()
        self.tmp = Path(self._td.name)

    def tearDown(self):
        self._td.cleanup()

    def _run(self, retail_words, keepalive=False, container_len=0x2000, retail_at=TFOFF):
        s = self.tmp / "t.s"; o = self.tmp / "t.o"; s.write_text(_asm(keepalive))
        subprocess.run(["mipsel-linux-gnu-as", "-EL", "-march=r3000", "-G0", "-o", str(o), str(s)], check=True)
        cont = bytearray(container_len)
        at = retail_at
        for w in retail_words:
            if 0 <= at and at + 4 <= len(cont):
                cont[at:at + 4] = w.to_bytes(4, "little")
            at += 4
        cpath = self.tmp / "CONT.BIN"; cpath.write_bytes(bytes(cont))
        seg = olg.Segment(index=0, kind="c", start=FOFF, end=FOFF + 28, vram=VRAM,
                          section=".text.func_80100000", name="func_80100000")
        # the placement the gate derives: the %lo site's table address, minus its offset in .rodata
        place = BASE - (8 if keepalive else 0)
        return olg.local_table_mismatches(o, {".rodata": place}, seg, VRAM, cpath, 0x80080000, [],
                                          self.tmp / "probe", "func_80100000")

    def test_equal_table_passes_and_gnu_as_padding_is_exempt(self):
        # retail's next datum (0x1) follows the 3-entry table directly; GNU as pads .rodata to 8
        self.assertEqual(self._run(CASES + [0x1]), [])

    def test_permuted_table_fails(self):
        errs = self._run([CASES[0], CASES[2], CASES[1], 0x1])
        self.assertEqual(len(errs), 1)
        self.assertIn("word 1", errs[0])
        self.assertIn("2 of 3 words differ", errs[0])

    def test_keepalive_array_beside_the_table_is_strict(self):
        # table entries equal retail, but the TU carries 8 bytes of phantom keep-alive data where
        # retail keeps something else (town/func_80813E14's shape): strict -> fail
        retail = [0x3020, 0x1] + CASES
        errs = self._run(retail, keepalive=True, retail_at=TFOFF - 8)
        self.assertEqual(len(errs), 1)
        self.assertIn("word 0", errs[0])
        # control: the same object passes when retail really has that data there
        self.assertEqual(self._run([CASES[1], 0] + CASES, keepalive=True, retail_at=TFOFF - 8), [])

    def test_table_outside_container_fails(self):
        errs = self._run(CASES, container_len=0x800)
        self.assertEqual(len(errs), 1)
        self.assertIn("outside the container", errs[0])


if __name__ == "__main__":
    unittest.main()
