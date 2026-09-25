"""Row database membership accepts registered aliases, without hiding omissions."""
import sys
import tempfile
import unittest
from pathlib import Path

sys.path[:0] = [str(Path(__file__).resolve().parents[1]),
                str(Path(__file__).resolve().parents[1] / "build")]
from row_db import slus_member_definitions


class SlusRowDbAliasTest(unittest.TestCase):
    def test_registered_alias_and_canonical_definitions(self):
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            names = root / "names.tsv"
            names.write_text("0x80047E30\tfunc_80047E30\tadvanceEffectState\tevidence\n")
            raw = root / "member.c"
            raw.write_text("void advanceEffectState(void) {}\n"
                           "void func_80047DF0(void) {}\n")
            self.assertEqual(slus_member_definitions(raw, names),
                             ["func_80047DF0", "func_80047E30"])
            raw.write_text("void advanceEffectState(void);\n"
                           "/* void func_80047E30(void) {} */\n"
                           "void unrelated(void) {}\n")
            self.assertEqual(slus_member_definitions(raw, names), [])
            self.assertEqual(slus_member_definitions(root / "missing.c", names), [])


if __name__ == "__main__":
    unittest.main()
