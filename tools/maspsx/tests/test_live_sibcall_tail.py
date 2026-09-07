import unittest

from maspsx import MaspsxProcessor


SIB = "func_80098488"


def body(*, marker=True, member=True, delay="nop", store=True,
         predecessor=True, branchy=False):
    target = SIB if member else "func_80011111"
    value = "li\t$3,1179648" if predecessor else "nop"
    mark = ["#maspsx_live_sibcall_pin $3,1179648"] if marker else []
    tail = ["lw\t$2,4($17)", "li\t$3,-1179648"]
    if branchy:
        tail += ["beq\t$2,$0,$L2", "nop"]
    if store:
        tail += ["addu\t$2,$2,$3", "sw\t$2,4($17)"]
    return [
        ".ent\tfunc_TEST", "beq\t$4,$0,$L7", value, "j\t$L1", "nop",
        "$L7:", "lw\t$2,4($17)", *mark, f"jal\t{target}", delay,
        *tail, "$L1:", "lw\t$31,28($sp)", "lw\t$18,24($sp)",
        "addu\t$sp,$sp,32", "j\t$31", "nop", ".end\tfunc_TEST",
    ]


def rewrite(lines, *, enabled=True):
    p = MaspsxProcessor([], live_sibcall_tail=enabled)
    p.sibcall_syms = frozenset((SIB,))
    return p._rewrite_marked_live_sibcall_tail(lines)


class TestLiveSibcallTail(unittest.TestCase):
    def test_positive_moves_entry_value_and_keeps_continuation(self):
        out = rewrite(body())
        self.assertTrue(any(x.startswith("j\t" + SIB) for x in out))
        self.assertTrue(any("marked live sibcall delay value" in x for x in out))
        self.assertTrue(any("value moved from entry delay" in x for x in out))
        self.assertIn("sw\t$2,4($17)", out)

    def test_flag_off(self):
        src = body()
        self.assertEqual(rewrite(src, enabled=False), src)

    def test_nonmember(self):
        src = body(member=False)
        self.assertEqual(rewrite(src), src)

    def test_missing_marker(self):
        src = body(marker=False)
        self.assertEqual(rewrite(src), src)

    def test_filled_call_slot(self):
        src = body(delay="lw\t$2,4($17)")
        self.assertEqual(rewrite(src), src)

    def test_missing_matching_predecessor_value(self):
        src = body(predecessor=False)
        self.assertEqual(rewrite(src), src)

    def test_no_store_continuation(self):
        src = body(store=False)
        self.assertEqual(rewrite(src), src)

    def test_branchy_continuation(self):
        src = body(branchy=True)
        self.assertEqual(rewrite(src), src)


if __name__ == "__main__":
    unittest.main()
