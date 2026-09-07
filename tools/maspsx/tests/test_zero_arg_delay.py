import unittest

from maspsx import MaspsxProcessor

from .util import strip_comments


class TestZeroArgDelay(unittest.TestCase):
    def _run(self, lines, sdata_limit=8):
        mp = MaspsxProcessor(lines, sdata_limit=sdata_limit)
        return strip_comments(mp.process_lines())

    def test_hoists_zero_arg_before_two_global_clears(self):
        lines = [
            ".ent\tx",
            ".set\tnoreorder",
            "sw\t$0,D_80079990",
            "sw\t$0,D_80079994",
            "jal\tfunc_8005D798",
            "move\t$4,$0",
            ".end\tx",
        ]
        expected = [
            ".ent\tx",
            ".set\tnoreorder",
            "addu\t$4,$0,$zero",
            "sw\t$0,D_80079990",
            "sw\t$0,D_80079994",
            "jal\tfunc_8005D798",
            "nop",
            ".end\tx",
        ]
        self.assertEqual(expected, self._run(lines))

    def test_one_global_clear_is_untouched(self):
        lines = [
            ".ent\tx",
            ".set\tnoreorder",
            "sw\t$0,D_80079990",
            "jal\tfunc_8005D798",
            "move\t$4,$0",
            ".end\tx",
        ]
        out = self._run(lines)
        i = out.index("jal\tfunc_8005D798")
        self.assertEqual("addu\t$4,$0,$zero", out[i + 1])

    def test_label_boundary_is_untouched(self):
        lines = [
            ".ent\tx",
            ".set\tnoreorder",
            "sw\t$0,D_80079990",
            "$L1:",
            "sw\t$0,D_80079994",
            "jal\tfunc_8005D798",
            "move\t$4,$0",
            ".end\tx",
        ]
        out = self._run(lines)
        i = out.index("jal\tfunc_8005D798")
        self.assertEqual("addu\t$4,$0,$zero", out[i + 1])

    def test_three_global_clears_are_untouched(self):
        lines = [
            ".ent\tx",
            ".set\tnoreorder",
            "sw\t$0,D_8007998C",
            "sw\t$0,D_80079990",
            "sw\t$0,D_80079994",
            "jal\tfunc_8005D798",
            "move\t$4,$0",
            ".end\tx",
        ]
        out = self._run(lines)
        i = out.index("jal\tfunc_8005D798")
        self.assertEqual("addu\t$4,$0,$zero", out[i + 1])

    def test_nonzero_arg_move_is_untouched(self):
        lines = [
            ".ent\tx",
            ".set\tnoreorder",
            "sw\t$0,D_80079990",
            "sw\t$0,D_80079994",
            "jal\tfunc_8005D798",
            "move\t$4,$5",
            ".end\tx",
        ]
        out = self._run(lines)
        i = out.index("jal\tfunc_8005D798")
        self.assertEqual("addu\t$4,$5,$zero", out[i + 1])


if __name__ == "__main__":
    unittest.main()
