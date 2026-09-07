import unittest

from maspsx import MaspsxProcessor

from .util import strip_comments


# gcc emits `.extern SYM, size` for DATA objects (used by `as -G8` to pick $gp vs
# %hi/%lo) but NEVER for function symbols, so the size-gate that drives the
# data-address delay-fill can't classify a function address. ASPSX/retail still
# split a `la $R,FUNC` that supplies a call argument: the `lui %hi` is hoisted to
# just after the frame prologue and the `addiu %lo` tail is scheduled into the
# jal's delay slot. See func_80041AB0, func_80043CD0.


class TestFuncAddrSplit(unittest.TestCase):
    def _run(self, lines, sdata_limit=8):
        mp = MaspsxProcessor(lines, sdata_limit=sdata_limit)
        return strip_comments(mp.process_lines())

    def test_funcaddr_arg_split_over_store(self):
        # void func(void) { D_80081480[0] = D_8008148C[0]; call((int)func_80041AE4); }
        # gcc (default -O2 schedule) puts the data store right before the jal; the
        # funcaddr `la` must claim the delay slot instead, and the store stays an
        # in-place ($at) macro.
        lines = [
            ".extern	D_8008148C, 12",
            ".extern	D_80081480, 12",
            "subu	$sp,$sp,24",
            "lw	$2,D_8008148C",
            "la	$4,func_80041AE4",
            "sw	$31,16($sp)",
            "sw	$2,D_80081480",
            "jal	func_80040A88",
            "lw	$31,16($sp)",
            "addu	$sp,$sp,24",
            "j	$31",
        ]
        expected = [
            ".extern	D_8008148C, 12",
            ".extern	D_80081480, 12",
            "subu	$sp,$sp,24",
            "lui	$4,%hi(func_80041AE4)",   # hoisted to just after the prologue
            "lw	$2,D_8008148C",
            "sw	$31,16($sp)",
            "sw	$2,D_80081480",            # kept in place (not in the delay slot)
            "jal	func_80040A88",
            "addiu	$4,$4,%lo(func_80041AE4)",  # %lo tail in the delay slot
            "lw	$31,16($sp)",
            "addu	$sp,$sp,24",
            "j	$31",
            "nop",
        ]
        self.assertEqual(expected, self._run(lines))

    def test_data_store_into_delay_unaffected_without_funcaddr(self):
        # Guard: with NO pending funcaddr, a data store still claims the jal delay
        # slot exactly as before (the gate must not perturb existing behaviour).
        lines = [
            ".extern	D_80081480, 12",
            "subu	$sp,$sp,24",
            "sw	$31,16($sp)",
            "sw	$2,D_80081480",
            "jal	func_80040A88",
            "lw	$31,16($sp)",
            "addu	$sp,$sp,24",
            "j	$31",
        ]
        out = self._run(lines)
        # the store is scheduled into the jal delay slot via a caller-saved temp
        self.assertIn("jal	func_80040A88", out)
        j = out.index("jal	func_80040A88")
        self.assertRegex(out[j + 1], r"^s[whb]\t\$2,%lo\(D_80081480\)\(\$\d+\)$")

    def test_non_func_la_not_split(self):
        # A `la` to a data symbol is not a funcaddr arg -> our split must not fire,
        # and the data store still claims the delay slot.
        lines = [
            ".extern	D_8008148C, 12",
            ".extern	D_80081480, 12",
            "subu	$sp,$sp,24",
            "la	$4,D_8008148C",
            "sw	$31,16($sp)",
            "sw	$2,D_80081480",
            "jal	func_80040A88",
            "lw	$31,16($sp)",
            "addu	$sp,$sp,24",
            "j	$31",
        ]
        out = self._run(lines)
        # no funcaddr %lo tail appears in the jal delay slot
        j = out.index("jal	func_80040A88")
        self.assertNotIn("%hi(func_", "".join(out))
        self.assertRegex(out[j + 1], r"^s[whb]\t\$2,%lo\(D_80081480\)\(\$\d+\)$")


if __name__ == "__main__":
    unittest.main()
