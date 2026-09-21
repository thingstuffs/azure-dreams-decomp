"""T95: grouping logic is textual (run/block/macro/function shapes, same-variable skip); the cc1
screen and `vf` are not exercised."""
import os, sys, unittest
sys.path.insert(0, os.path.join(os.path.dirname(__file__), "..", "xform")); sys.path.insert(0, os.path.join(os.path.dirname(__file__), ".."))
import t95_runjoint as M  # noqa: E402
from pin_census import sites_of  # noqa: E402

# The round-63 shape: three different-variable KEEP_NV pins, one ordinary store between each pair,
# an unrelated ASM_KEEP and an ASM_SCHED_BARRIER held off by >3 statement lines on each side (as in
# the real dungeon/func_81008664: attempts/the barrier tie at a different priority and never join).
RUN_SHAPE = '''#include "common.h"
void f(s32 a) {
    s32 x;
    s32 y;
    s32 z;
    s32 w;
    attempts += 1;
    ASM_KEEP(attempts);
    x = a;
    y = a + 1;
    z = a + 2;
    w = a + 3;
    ASM_SCHED_BARRIER();
    x = a;
    y = a;
    z = a;
    w = a;
    x = a;
    ASM_KEEP_NV(x);
    y = x + 1;
    ASM_KEEP_NV(y);
    z = y + 1;
    ASM_KEEP_NV(z);
    a = x + y + z + w;
}
'''

# A same-variable run (joint_scan's job): must be generated as a "run" but then filtered.
SAMEVAR = '''#include "common.h"
void g(s32 a) {
    s32 v;
    v = a;
    ASM_KEEP_NV(v);
    v += 1;
    ASM_KEEP_NV(v);
}
'''

# A block shape: two pins on different vars inside one if-block, one pin outside it.
BLOCK_SHAPE = '''#include "common.h"
void h(s32 a, s32 b) {
    s32 p;
    s32 q;
    if (a) {
        p = a;
        ASM_KEEP_NV(p);
        q = b;
        ASM_KEEP_NV(q);
    }
    b += 1;
    ASM_KEEP(b);
}
'''


class VarOf(unittest.TestCase):
    def test_stmt_site(self):
        sites = sites_of(RUN_SHAPE)
        keep_nv = [s for s in sites if s[1] == "ASM_KEEP_NV"]
        self.assertEqual([M.var_of(s) for s in keep_nv], ["x", "y", "z"])

    def test_reg_site(self):
        text = '#include "common.h"\nvoid f(void) {\n    register s32 idx ASM_REG("$16");\n    idx = 1;\n}\n'
        sites = sites_of(text)
        self.assertEqual(M.var_of(sites[0]), "idx")

    def test_barrier_has_no_var(self):
        sites = sites_of(RUN_SHAPE)
        barrier = [s for s in sites if s[1] == "ASM_SCHED_BARRIER"][0]
        self.assertEqual(M.var_of(barrier), "")

    def test_same_var(self):
        sites = sites_of(SAMEVAR)
        self.assertTrue(M.same_var(tuple(sites)))
        keep_nv = [s for s in sites_of(RUN_SHAPE) if s[1] == "ASM_KEEP_NV"]
        self.assertFalse(M.same_var(tuple(keep_nv)))

    def test_same_var_false_for_barriers(self):
        # two no-argument pins never count as "the same variable" (there is none)
        text = '#include "common.h"\nvoid f(void) {\n    ASM_SCHED_BARRIER();\n    ASM_MEM_BARRIER();\n}\n'
        self.assertFalse(M.same_var(tuple(sites_of(text))))


class Runs(unittest.TestCase):
    def test_run_merges_close_pins_and_excludes_attempts(self):
        sites = sites_of(RUN_SHAPE)
        runs = M.runs_of(RUN_SHAPE, sites)
        self.assertEqual(len(runs), 1)
        macros = [s[1] for s in runs[0]]
        self.assertEqual(macros, ["ASM_KEEP_NV", "ASM_KEEP_NV", "ASM_KEEP_NV"])
        # attempts/ASM_KEEP and the barrier sit too many statement lines away to join the run
        self.assertNotIn("attempts", [M.var_of(s) for s in runs[0]])

    def test_sub_runs_include_pairs_and_full(self):
        # run_groups is the raw (undeduped) generator: the full run of 3 and its lone size-3 sliding
        # window coincide, so it appears twice here; candidate_groups (below) dedupes it to one.
        sites = sites_of(RUN_SHAPE)
        groups = [g for label, g in M.run_groups(RUN_SHAPE, sites) if label == "run"]
        sizes = sorted(len(g) for g in groups)
        self.assertEqual(sizes, [2, 2, 3, 3])                         # two pairs + the full run, twice

    def test_dedupe_collapses_duplicate_full_run(self):
        sites = sites_of(RUN_SHAPE)
        groups = M.candidate_groups(RUN_SHAPE, sites)
        full_run = [g for label, g in groups if label == "run" and len(g) == 3]
        self.assertEqual(len(full_run), 1)

    def test_no_run_when_only_one_pin_in_function(self):
        text = '#include "common.h"\nvoid f(void) {\n    s32 x = 1;\n    ASM_KEEP(x);\n}\n'
        self.assertEqual(M.runs_of(text, sites_of(text)), [])


class Blocks(unittest.TestCase):
    def test_block_groups_inside_brace_only(self):
        sites = sites_of(BLOCK_SHAPE)
        groups = M.block_groups(BLOCK_SHAPE, sites)
        self.assertEqual(len(groups), 1)
        self.assertEqual(sorted(M.var_of(s) for s in groups[0][1]), ["p", "q"])

    def test_outside_pin_not_grouped(self):
        sites = sites_of(BLOCK_SHAPE)
        groups = M.block_groups(BLOCK_SHAPE, sites)
        names = {M.var_of(s) for g in groups for s in g[1]}
        self.assertNotIn("b", names)


class MacroAndFunction(unittest.TestCase):
    def test_macro_groups_same_macro_same_function(self):
        sites = sites_of(RUN_SHAPE)
        groups = M.macro_groups(RUN_SHAPE, sites)
        by_macro = {}
        for label, g in groups:
            by_macro.setdefault(g[0][1], []).append(g)
        self.assertIn("ASM_KEEP_NV", by_macro)
        self.assertEqual(len(by_macro["ASM_KEEP_NV"][0]), 3)
        self.assertNotIn("ASM_SCHED_BARRIER", by_macro)               # only one site: not a group

    def test_function_group_is_every_pin(self):
        sites = sites_of(RUN_SHAPE)
        groups = M.function_groups(RUN_SHAPE, sites)
        self.assertEqual(len(groups), 1)
        self.assertEqual(len(groups[0][1]), len(sites))


class CandidateGroups(unittest.TestCase):
    def test_samevar_run_is_filtered_out(self):
        sites = sites_of(SAMEVAR)
        groups = M.candidate_groups(SAMEVAR, sites)
        self.assertEqual(groups, [])                                   # every shape here is same-variable

    def test_exemplar_run_survives_the_samevar_filter(self):
        sites = sites_of(RUN_SHAPE)
        groups = M.candidate_groups(RUN_SHAPE, sites)
        full_run = [g for label, g in groups if label == "run" and len(g) == 3]
        self.assertEqual(len(full_run), 1)
        self.assertEqual(sorted(M.var_of(s) for s in full_run[0]), ["x", "y", "z"])

    def test_singletons_never_offered(self):
        sites = sites_of(RUN_SHAPE)
        groups = M.candidate_groups(RUN_SHAPE, sites)
        self.assertTrue(all(len(g) >= 2 for _, g in groups))

    def test_eligible_refuses_under_two_pins(self):
        text = '#include "common.h"\nvoid f(void) {\n    s32 x = 1;\n    ASM_KEEP(x);\n}\n'
        self.assertIsNotNone(M.T.eligible(text, {}, {}))

    def test_eligible_refuses_all_samevar(self):
        self.assertIsNotNone(M.T.eligible(SAMEVAR, {}, {}))

    def test_eligible_accepts_run_shape(self):
        self.assertIsNone(M.T.eligible(RUN_SHAPE, {}, {}))


if __name__ == "__main__":
    unittest.main()
