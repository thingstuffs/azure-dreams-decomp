import unittest
from unittest import mock

import maspsx
from maspsx import MaspsxProcessor

from .util import strip_comments


class TestCasesiJumpTableLoad(unittest.TestCase):
    """LEAD 13/F6: compiler-generated switch jump-table loads use ASPSX's
    normal-register base materialisation instead of GNU as's `$at` macro.
    """

    def _run(self, lines, preserve_casesi_at=False):
        mp = MaspsxProcessor(
            lines,
            sdata_limit=8,
            preserve_casesi_at=preserve_casesi_at,
        )
        return strip_comments(mp.process_lines())

    def test_local_jumptable_dispatch_expands_to_base_materialize_form(self):
        lines = [
            ".set\tnoreorder",
            "beq\t$2,$0,$Ldefault",
            "sll\t$2,$3,2",
            "lw\t$2,$Ltable($2)",
            "j\t$2",
            "nop",
        ]

        out = self._run(lines)

        self.assertEqual(
            [
                "beq\t$2,$0,$Ldefault",
                "lui\t$2,%hi($Ltable)",
                "addiu\t$2,$2,%lo($Ltable)",
                "sll\t$3,$3,2",
                "addu\t$3,$3,$2",
                "lw\t$2,0($3)",
                "nop",
                "j\t$2",
                "nop",
            ],
            out,
        )

    def test_distinct_index_temp_keeps_temp_as_index_register(self):
        lines = [
            ".set\tnoreorder",
            "sll\t$4,$3,2",
            "lw\t$2,$Ltable($4)",
            "j\t$2",
            "nop",
        ]

        out = self._run(lines)

        self.assertIn("lui\t$2,%hi($Ltable)", out)
        self.assertIn("addiu\t$2,$2,%lo($Ltable)", out)
        self.assertIn("sll\t$4,$3,2", out)
        self.assertIn("addu\t$4,$4,$2", out)
        self.assertIn("lw\t$2,0($4)", out)

    def test_data_symbol_indexed_load_stays_at_macro(self):
        lines = [
            ".set\tnoreorder",
            "sll\t$2,$3,2",
            "lw\t$2,D_80070000($2)",
            "j\t$2",
            "nop",
        ]

        out = self._run(lines)

        self.assertIn("lui\t$at,%hi(D_80070000)", out)
        self.assertIn("addu\t$at,$at,$2", out)
        self.assertIn("lw\t$2,%lo(D_80070000)($at)", out)
        self.assertNotIn("addiu\t$2,$2,%lo(D_80070000)", out)

    def test_local_table_probe_not_feeding_dispatch_stays_at_macro(self):
        lines = [
            ".set\tnoreorder",
            "sll\t$2,$3,2",
            "lw\t$2,$Ltable($2)",
            "addu\t$4,$2,$5",
        ]

        out = self._run(lines)

        self.assertIn("lui\t$at,%hi($Ltable)", out)
        self.assertIn("lw\t$2,%lo($Ltable)($at)", out)
        self.assertNotIn("addiu\t$2,$2,%lo($Ltable)", out)

    def test_ambiguous_in_place_index_is_left_unchanged(self):
        lines = [
            ".set\tnoreorder",
            "sll\t$2,$2,2",
            "lw\t$2,$Ltable($2)",
            "j\t$2",
            "nop",
        ]

        out = self._run(lines)

        self.assertIn("sll\t$2,$2,2", out)
        self.assertIn("lui\t$at,%hi($Ltable)", out)
        self.assertIn("lw\t$2,%lo($Ltable)($at)", out)

    def test_per_tu_preserve_keeps_at_macro_form(self):
        lines = [
            ".set\tnoreorder",
            "sll\t$2,$3,2",
            "lw\t$2,$Ltable($2)",
            "j\t$2",
            "nop",
        ]

        out = self._run(lines, preserve_casesi_at=True)

        self.assertIn("lui\t$at,%hi($Ltable)", out)
        self.assertIn("addu\t$at,$at,$2", out)
        self.assertIn("lw\t$2,%lo($Ltable)($at)", out)
        self.assertNotIn("addiu\t$2,$2,%lo($Ltable)", out)


class TestCasesiExternDispatchTable(unittest.TestCase):
    """The LANDING idiom's dispatch: a computed goto through an EXTERN table.

    A row whose retail jump table lives in the data blob is landed as
    `goto *jtbl_XXXX[i]` through an absolute (src/w_800595C0.c and friends), so
    the TU emits no `.rodata` table of its own and therefore LINKS.  Those five
    rows compile at the default `-mgas`, where gcc splits the table address
    itself and this pass never sees them; under `-mmips-as` the same source
    arrives as exactly the `$at` indexed-load macro a `$L` table does.  Retail's
    bytes are the base-materialised form either way, so the symbol is admitted --
    by NAME, because the shape alone cannot tell it from a data-symbol indexed
    load (see `test_data_symbol_indexed_load_stays_at_macro`).
    """

    SYM = "jtbl_8002D5C0"

    def _run(self, lines, table=None):
        with mock.patch.object(
            maspsx,
            "casesi_extern_dispatch_tables",
            {self.SYM} if table is None else table,
        ):
            mp = MaspsxProcessor(lines, sdata_limit=8)
            return strip_comments(mp.process_lines())

    def _body(self, sym=None):
        sym = sym or self.SYM
        return [
            ".set\tnoreorder",
            "beq\t$2,$0,$Ldefault",
            "sll\t$2,$3,2",
            f"lw\t$2,{sym}($2)",
            "j\t$2",
            "nop",
        ]

    def test_opted_in_extern_table_expands_to_base_materialize_form(self):
        out = self._run(self._body())
        self.assertEqual(
            [
                "beq\t$2,$0,$Ldefault",
                f"lui\t$2,%hi({self.SYM})",
                f"addiu\t$2,$2,%lo({self.SYM})",
                "sll\t$3,$3,2",
                "addu\t$3,$3,$2",
                "lw\t$2,0($3)",
                "nop",
                "j\t$2",
                "nop",
            ],
            [line for line in out if line and not line.startswith((".", "#"))],
        )

    def test_the_lui_lands_in_the_branch_delay_slot(self):
        """Retail word 442 is the `lui`, in the `beqz`'s slot."""
        out = [l for l in self._run(self._body()) if l and not l.startswith((".", "#"))]
        self.assertEqual("beq\t$2,$0,$Ldefault", out[0])
        self.assertEqual(f"lui\t$2,%hi({self.SYM})", out[1])

    def test_word_count_is_unchanged_by_the_admission(self):
        """The `$at` macro is 3 words + the `sll`; the rewrite is 5 words for the
        same 4 -- one MORE, which is exactly the word retail has."""
        before = [l for l in self._run(self._body(), table=set())
                  if l and not l.startswith((".", "#"))]
        after = [l for l in self._run(self._body())
                 if l and not l.startswith((".", "#"))]
        self.assertEqual(len(before) + 1, len(after))

    def test_unlisted_extern_symbol_stays_at_macro(self):
        out = self._run(self._body(), table=set())
        self.assertIn(f"lui\t$at,%hi({self.SYM})", out)
        self.assertIn(f"lw\t$2,%lo({self.SYM})($at)", out)
        self.assertNotIn(f"addiu\t$2,$2,%lo({self.SYM})", out)

    def test_a_different_extern_symbol_is_not_admitted_by_a_listed_one(self):
        out = self._run(self._body(sym="jtbl_DEADBEEF"))
        self.assertIn("lui\t$at,%hi(jtbl_DEADBEEF)", out)

    def test_local_tables_still_fire_with_an_empty_table(self):
        lines = [
            ".set\tnoreorder",
            "beq\t$2,$0,$Ldefault",
            "sll\t$2,$3,2",
            "lw\t$2,$Ltable($2)",
            "j\t$2",
            "nop",
        ]
        out = self._run(lines, table=set())
        self.assertIn("lui\t$2,%hi($Ltable)", out)
        self.assertIn("addiu\t$2,$2,%lo($Ltable)", out)


if __name__ == "__main__":
    unittest.main()
