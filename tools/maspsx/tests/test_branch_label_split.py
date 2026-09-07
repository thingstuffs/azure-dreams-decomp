import unittest

from maspsx import MaspsxProcessor


def rewrite(lines):
    processor = MaspsxProcessor([], sdata_limit=8)
    return processor._split_marked_branch_label(list(lines))


class TestMarkedBranchLabelSplit(unittest.TestCase):
    def site(self, *, marker="#maspsx_branch_label_split $3",
             slt="slt\t$2,$3,33", branch="bne\t$2,$0,$L6",
             target=("la\t$2,D_800B7E78",)):
        lines = []
        if marker is not None:
            lines.append(marker)
        lines.extend([
            slt,
            branch,
            "beq\t$4,$0,$L6",
            "$L6:",
            *target,
            "sw\t$2,16($4)",
        ])
        return lines

    def test_marked_edge_only_splits_la(self):
        out = rewrite(self.site())
        self.assertIn("bne\t$2,$0,$L6__maspsx_branch_split_0", out)
        self.assertIn("beq\t$4,$0,$L6", out)
        label_i = out.index("$L6:")
        self.assertEqual(out[label_i + 1:label_i + 4], [
            "lui\t$2,%hi(D_800B7E78)",
            "$L6__maspsx_branch_split_0:",
            "addiu\t$2,$2,%lo(D_800B7E78)",
        ])

    def test_explicit_pair_is_split_without_rewriting_words(self):
        out = rewrite(self.site(target=(
            "lui\t$2,%hi(D_800B7E78)",
            "addiu\t$2,$2,%lo(D_800B7E78)",
        )))
        label_i = out.index("$L6:")
        self.assertEqual(out[label_i + 1:label_i + 4], [
            "lui\t$2,%hi(D_800B7E78)",
            "$L6__maspsx_branch_split_0:",
            "addiu\t$2,$2,%lo(D_800B7E78)",
        ])

    def test_no_marker_is_identity(self):
        source = self.site(marker=None)
        self.assertEqual(rewrite(source), source)

    def test_marker_register_must_feed_slt(self):
        source = self.site(slt="slt\t$2,$4,33")
        self.assertEqual(rewrite(source), source)

    def test_slt_result_must_feed_zero_test_branch(self):
        source = self.site(branch="bne\t$5,$0,$L6")
        self.assertEqual(rewrite(source), source)

    def test_target_must_be_forward(self):
        source = [
            "$L6:",
            "la\t$2,D_800B7E78",
            "#maspsx_branch_label_split $3",
            "slt\t$2,$3,33",
            "bne\t$2,$0,$L6",
        ]
        self.assertEqual(rewrite(source), source)

    def test_target_must_start_with_direct_address(self):
        source = self.site(target=("addu\t$2,$2,$3",))
        self.assertEqual(rewrite(source), source)

    def test_explicit_pair_register_and_symbol_must_match(self):
        source = self.site(target=(
            "lui\t$2,%hi(D_800B7E78)",
            "addiu\t$3,$3,%lo(D_800B7E78)",
        ))
        self.assertEqual(rewrite(source), source)

    def test_branch_comment_is_preserved(self):
        out = rewrite(self.site(branch="bne\t$2,$0,$L6 # retail edge"))
        self.assertIn(
            "bne\t$2,$0,$L6__maspsx_branch_split_0 # retail edge", out
        )

    def test_marker_survives_process_lines(self):
        processor = MaspsxProcessor([
            ".ent\tfunc_TEST",
            "#maspsx_branch_label_split $3",
            "addu\t$2,$2,$3",
            ".end\tfunc_TEST",
        ], sdata_limit=8)
        out = processor.process_lines()
        self.assertTrue(any("maspsx_branch_label_split $3" in line for line in out))

    def test_duplicate_local_label_in_next_function_is_not_selected(self):
        source = [
            ".ent\tfunc_ONE",
            "#maspsx_branch_label_split $3",
            "slt\t$2,$3,33",
            "bne\t$2,$0,$L6",
            "$L6:",
            "la\t$2,D_800B7E78",
            ".end\tfunc_ONE",
            ".ent\tfunc_TWO",
            "$L6:",
            "la\t$2,D_OTHER",
            ".end\tfunc_TWO",
        ]
        out = rewrite(source)
        first_label_i = out.index("$L6:")
        self.assertEqual(out[first_label_i + 1:first_label_i + 4], [
            "lui\t$2,%hi(D_800B7E78)",
            "$L6__maspsx_branch_split_0:",
            "addiu\t$2,$2,%lo(D_800B7E78)",
        ])
        second_label_i = out.index("$L6:", first_label_i + 1)
        self.assertEqual(out[second_label_i + 1], "la\t$2,D_OTHER")


if __name__ == "__main__":
    unittest.main()
