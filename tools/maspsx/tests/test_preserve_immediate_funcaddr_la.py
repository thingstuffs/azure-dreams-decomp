import unittest

from maspsx import MaspsxProcessor

from .util import strip_comments


class TestPreserveImmediateFuncaddrLa(unittest.TestCase):
    def _run(self, lines, enabled=True):
        processor = MaspsxProcessor(
            lines, preserve_immediate_funcaddr_la=enabled
        )
        return strip_comments(processor.process_lines())

    def test_immediate_consumer_is_preserved_when_enabled(self):
        lines = [
            "subu\t$sp,$sp,24", "lw\t$2,D_8008148C",
            "la\t$4,func_80041AE4", "jal\tfunc_80040A88", "j\t$31",
        ]
        out = self._run(lines)
        la_i = out.index("la\t$4,func_80041AE4")
        self.assertEqual("jal\tfunc_80040A88", out[la_i + 1])
        self.assertEqual("nop", out[la_i + 2])
        self.assertNotIn("%hi(func_80041AE4)", "".join(out))

    def test_flag_off_retains_established_split(self):
        lines = [
            "subu\t$sp,$sp,24", "lw\t$2,D_8008148C",
            "la\t$4,func_80041AE4", "jal\tfunc_80040A88", "j\t$31",
        ]
        out = self._run(lines, enabled=False)
        self.assertIn("lui\t$4,%hi(func_80041AE4)", out)
        jal_i = out.index("jal\tfunc_80040A88")
        self.assertEqual("addiu\t$4,$4,%lo(func_80041AE4)", out[jal_i + 1])

    def test_comments_and_directives_are_tolerated(self):
        lines = [
            "subu\t$sp,$sp,24", "la\t$4,func_80041AE4", "# comment",
            ".set\tpush", ".set\tpop", "jal\tfunc_80040A88", "j\t$31",
        ]
        out = self._run(lines)
        self.assertIn("la\t$4,func_80041AE4", out)
        self.assertNotIn("%hi(func_80041AE4)", "".join(out))

    def test_intervening_setup_retains_split(self):
        lines = [
            "subu\t$sp,$sp,24", "lw\t$2,D_8008148C",
            "la\t$4,func_80041AE4", "sw\t$31,16($sp)",
            "jal\tfunc_80040A88", "j\t$31",
        ]
        out = self._run(lines)
        self.assertIn("lui\t$4,%hi(func_80041AE4)", out)
        jal_i = out.index("jal\tfunc_80040A88")
        self.assertEqual("addiu\t$4,$4,%lo(func_80041AE4)", out[jal_i + 1])

    def test_intervening_register_consumer_is_rejected(self):
        lines = [
            "subu\t$sp,$sp,24", "la\t$4,func_80041AE4",
            "move\t$5,$4", "jal\tfunc_80040A88", "j\t$31",
        ]
        out = self._run(lines)
        self.assertIn("la\t$4,func_80041AE4", out)
        self.assertNotIn("%hi(func_80041AE4)", "".join(out))

    def test_label_boundary_is_rejected(self):
        lines = [
            "subu\t$sp,$sp,24", "la\t$4,func_80041AE4", "$Ledge:",
            "jal\tfunc_80040A88", "j\t$31",
        ]
        out = self._run(lines)
        self.assertIn("la\t$4,func_80041AE4", out)
        self.assertNotIn("%hi(func_80041AE4)", "".join(out))

    def test_branch_boundary_is_rejected(self):
        lines = [
            "subu\t$sp,$sp,24", "la\t$4,func_80041AE4", "b\t$Ledge",
            "nop", "$Ledge:", "jal\tfunc_80040A88", "j\t$31",
        ]
        out = self._run(lines)
        self.assertIn("la\t$4,func_80041AE4", out)
        self.assertNotIn("%hi(func_80041AE4)", "".join(out))


if __name__ == "__main__":
    unittest.main()
