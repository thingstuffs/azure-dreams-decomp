import unittest

from maspsx import MaspsxProcessor


def rewrite(lines, enabled=True):
    p = MaspsxProcessor([], prefer_target_arg_setup=enabled)
    return p._prefer_marked_target_arg_setup(lines)


def shape(*, delay="li\t$16,-2147352576", first="addu\t$16,$16,18048",
          second="addu\t$4,$sp,16", third="addu\t$5,$16,$zero"):
    return [
        ".ent\tfunc_TEST", "beq\t$4,$2,$L11", delay, "j\t$L9", "nop",
        "$L11:", first, second, third, "jal\tfunc_800672D8", "nop",
        ".end\tfunc_TEST",
    ]


class TestTargetArgSetup(unittest.TestCase):
    def test_positive_swaps_only_target_pair(self):
        src = shape()
        out = rewrite(src)
        label = out.index("$L11:")
        self.assertEqual(out[label + 1], "addu\t$4,$sp,16")
        self.assertEqual(out[label + 2], "addu\t$16,$16,18048")

    def test_flag_off(self):
        src = shape()
        self.assertEqual(rewrite(src, False), src)

    def test_delay_low_half_nonzero(self):
        src = shape(delay="li\t$16,0x80020001")
        self.assertEqual(rewrite(src), src)

    def test_wrong_target_first(self):
        src = shape(first="addu\t$17,$17,18048")
        self.assertEqual(rewrite(src), src)

    def test_wrong_arg_setup(self):
        src = shape(second="addu\t$5,$sp,16")
        self.assertEqual(rewrite(src), src)

    def test_target_does_not_consume_base(self):
        src = shape(third="addu\t$5,$17,$zero")
        self.assertEqual(rewrite(src), src)


if __name__ == "__main__":
    unittest.main()
