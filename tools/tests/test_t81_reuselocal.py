"""T81: the (v, host) search, the rename text and the refusals are textual; the screen and `vf` are not exercised."""
import os, sys, unittest
sys.path.insert(0, os.path.join(os.path.dirname(__file__), "..", "xform")); sys.path.insert(0, os.path.join(os.path.dirname(__file__), ".."))
import t81_reuselocal as M  # noqa: E402


def body(decls, arm, tail="    reward = 5;\n"):
    return ('#include "common.h"\nvoid f(void *pickup)\n{\n' + decls +
            "\n    if (((S *)pickup)->unk_00) {\n" + arm + "    }\n\n" + tail + "}\n")


DECLS = "    s32 timer;\n    s32 reward;\n    s32 divisor = 1;\n    u32 state;\n"
ARM = ('        ASM_CLOBBER("$5");\n'
       "        divisor = 10;\n"
       "        ((S *)pickup)->unk_56 = ((S *)pickup)->unk_1E / divisor;\n")
T = body(DECLS, ARM)


class Candidates(unittest.TestCase):
    def test_finds_the_host(self):
        cs = M.candidates(T)
        self.assertIn(("divisor", "reward"), [(v, w) for _, v, w, _ in cs])
        self.assertIsNone(M.T.eligible(T, {}, {}))

    def test_host_order_is_declaration_order(self):
        hosts = [w for _, v, w, _ in M.candidates(T) if v == "divisor"]
        self.assertEqual(hosts, ["timer", "reward"])                   # `state` is a u32: a different type
        self.assertLessEqual(len(hosts), M.MAX_HOSTS)

    def test_rename_and_initialiser_merge(self):
        new = [c for c in M.candidates(T) if (c[1], c[2]) == ("divisor", "reward")][0][3]
        self.assertIn("    s32 reward = 1;\n", new)                    # the initialiser moved to the host
        self.assertNotIn("divisor", new)                               # the declaration and every mention went
        self.assertIn("        reward = 10;\n", new)
        self.assertIn("    s32 timer;\n", new)
        self.assertEqual(len(new.split("\n")), len(T.split("\n")) - 1)
        self.assertIn('        ASM_CLOBBER("$5");\n', new)             # the pin is erased by the driver, not here

    def test_block_scope_initialiser_stays_as_an_assignment(self):
        t = body("    s32 timer;\n    s32 reward;\n",
                 '        s32 divisor = 1;\n\n        ASM_CLOBBER("$5");\n'
                 "        ((S *)pickup)->unk_56 = ((S *)pickup)->unk_1E / divisor;\n")
        new = [c for c in M.candidates(t) if (c[1], c[2]) == ("divisor", "reward")][0][3]
        self.assertIn("        reward = 1;\n", new)
        self.assertIn("    s32 reward;\n", new)


class Refusals(unittest.TestCase):
    def test_two_initialisers(self):
        t = T.replace("    s32 reward;\n", "    s32 reward = 3;\n")
        self.assertNotIn(("divisor", "reward"), [(v, w) for _, v, w, _ in M.candidates(t)])

    def test_host_mentioned_in_the_block(self):
        t = body(DECLS, ARM + "        reward = 2;\n")
        self.assertNotIn(("divisor", "reward"), [(v, w) for _, v, w, _ in M.candidates(t)])

    def test_host_read_after_the_block(self):
        t = body(DECLS, ARM, tail="    ((S *)pickup)->unk_58 = reward;\n")
        self.assertNotIn(("divisor", "reward"), [(v, w) for _, v, w, _ in M.candidates(t)])

    def test_address_taken(self):
        t = body(DECLS, ARM, tail="    reward = 5;\n    func_80024610(&reward);\n")
        self.assertNotIn(("divisor", "reward"), [(v, w) for _, v, w, _ in M.candidates(t)])
        t2 = body(DECLS, ARM + "        func_80024610(&divisor);\n")
        self.assertNotIn(("divisor", "reward"), [(v, w) for _, v, w, _ in M.candidates(t2)])

    def test_qualified_or_array_declarations(self):
        for spell in ("    volatile s32 reward;\n", "    static s32 reward;\n", "    s32 reward[2];\n"):
            t = T.replace("    s32 reward;\n", spell)
            self.assertNotIn(("divisor", "reward"), [(v, w) for _, v, w, _ in M.candidates(t)])

    def test_parameter_is_not_a_host(self):
        t = T.replace("void f(void *pickup)", "void f(void *pickup, s32 reward)").replace("    s32 reward;\n", "")
        self.assertNotIn(("divisor", "reward"), [(v, w) for _, v, w, _ in M.candidates(t)])

    def test_variable_mentioned_outside_the_block(self):
        t = body(DECLS, ARM, tail="    reward = 5;\n    divisor = 2;\n")
        self.assertEqual([(v, w) for _, v, w, _ in M.candidates(t) if v == "divisor"], [])

    def test_different_type_is_not_a_host(self):
        t = T.replace("    s32 timer;\n    s32 reward;\n", "    u16 timer;\n    s16 reward;\n")
        self.assertEqual(M.T.eligible(t, {}, {}), "no arm-local with a dead same-typed host")

    def test_rename_that_changes_a_pin_text(self):
        t = T.replace('        ASM_CLOBBER("$5");\n', "        ASM_KEEP(divisor);\n")
        self.assertEqual([(v, w) for _, v, w, _ in M.candidates(t) if v == "divisor"], [])

    def test_no_pins(self):
        self.assertEqual(M.T.eligible(T.replace('        ASM_CLOBBER("$5");\n', ""), {}, {}), "no pins")


if __name__ == "__main__":
    unittest.main()
