"""Production and standalone SLUS measurements must see identical canonical names."""
import subprocess
import sys
import tempfile
import unittest
from pathlib import Path
from unittest.mock import patch

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))
import verify


class CanonicalInputTests(unittest.TestCase):
    def test_source_and_exported_entry_points_agree(self):
        asm = '\t.ent setPacked2bitFlag\nsetPacked2bitFlag:\n\tjal setPacked2bitFlag\n\tla $2,setPacked2bitFlag\n\t.ascii "setPacked2bitFlag"\n\t.end setPacked2bitFlag\n'
        with tempfile.TemporaryDirectory() as td:
            root = Path(td)
            (root / "tools").mkdir()
            (root / "config").mkdir()
            (root / "tools/ccproc.py").symlink_to(ROOT / "tools/build/ccproc.py")
            (root / "config/names.tsv").symlink_to(ROOT / "config/names.tsv")
            def run(path):
                return subprocess.run([sys.executable, str(path)], input=asm, text=True,
                                      capture_output=True, check=True).stdout
            self.assertEqual(run(ROOT / "tools/build/ccproc.py"), run(root / "tools/ccproc.py"))
        processed = verify.postprocess_slus(asm)
        genuine = verify.postprocess_slus(asm, names_only=True)
        self.assertIn('.section .text.func_8003E188', processed)
        self.assertNotIn('.section', genuine)
        for text in (processed, genuine):
            self.assertIn('jal func_8003E188', text)
            self.assertIn('la $2,func_8003E188', text)
            self.assertIn('.ascii "setPacked2bitFlag"', text)
            self.assertIn('.ent func_8003E188', text)

    def test_missing_explicit_table_is_an_error(self):
        with tempfile.TemporaryDirectory() as td, patch.object(verify, "ROOT", Path(td)):
            with self.assertRaisesRegex(ValueError, "name table does not exist"):
                verify.postprocess_slus('\t.ent f\nf:\n\t.end f\n')

    def test_genuine_keeps_the_compilers_text_resumption(self):
        asm = '\t.ent f\nf:\n\t.rdata\n\t.word 4\n\t.text\n\tjr $31\n\t.end f\n'
        self.assertEqual(verify.postprocess_slus(asm, names_only=True), asm)
        self.assertIn('\t.section .text.f,"ax",@progbits\n\tjr', verify.postprocess_slus(asm))


if __name__ == "__main__":
    unittest.main()
