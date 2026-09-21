"""T82, round-72 KIT addition: the join statement written into every arm (textual detection only)."""
import os, sys, unittest
sys.path.insert(0, os.path.join(os.path.dirname(__file__), "..", "xform")); sys.path.insert(0, os.path.join(os.path.dirname(__file__), ".."))
import t82_armsink as M  # noqa: E402

CHAIN = '''#include "common.h"
void f(s32 mode, S *result, S *partB) {
    u32 slot2;

    if (mode == 1) {
        result->unk8C = 1;
        slot2 = (unsigned long)D_80150ED8;
    } else if (mode >= 2) {
        result->unk8C = 2;
        slot2 = (unsigned long)D_80150ED8;
        ASM_KEEP_NV(slot2);
    } else {
        slot2 = (unsigned long)D_80150ED8;
    }

    partB->unk2C = (void *)slot2;
    ASM_KEEP(partB);
    result->unk10 = 3;
}
'''

NO_ELSE = CHAIN.replace("    } else {\n        slot2 = (unsigned long)D_80150ED8;\n    }\n", "    }\n")

CALL_TAIL = CHAIN.replace("    partB->unk2C = (void *)slot2;", "    g(partB, slot2);")


def _dups(text):
    return [s for s in M.sites_in(text) if s["kind"] == "dup"]


class TestDupDetection(unittest.TestCase):
    def test_the_join_statement_after_an_exhaustive_chain_is_a_site(self):
        got = [s["stmt"] for s in _dups(CHAIN)]
        self.assertIn("partB->unk2C = (void *)slot2;", got)

    def test_a_chain_without_a_final_else_is_refused(self):
        self.assertEqual([s["stmt"] for s in _dups(NO_ELSE)
                          if s["stmt"].startswith("partB")], [])

    def test_a_call_after_the_chain_is_refused(self):
        self.assertEqual([s["stmt"] for s in _dups(CALL_TAIL) if "g(" in s["stmt"]], [])

    def test_the_window_reaches_the_pin_on_the_join_statement(self):
        s = [x for x in _dups(CHAIN) if x["stmt"].startswith("partB")][0]
        lines = CHAIN.split("\n")
        self.assertTrue(any("ASM_KEEP(partB)" in lines[i] for i in range(s["lo"], s["hi"] + 1)))


class TestDupRewrite(unittest.TestCase):
    def test_every_arm_gets_a_copy_and_the_join_loses_its(self):
        s = [x for x in _dups(CHAIN) if x["stmt"].startswith("partB")][0]
        new, win, touched = M.build(CHAIN, s)
        self.assertIsNotNone(new)
        self.assertEqual(new.count("partB->unk2C = (void *)slot2;"), 3)
        body = new.split("}\n\n")[0]
        self.assertNotIn("\n    partB->unk2C", new)          # not at the join indent any more
        self.assertIn("ASM_KEEP(partB);", new)               # the pin plan, not the move, erases it

    def test_the_signature_round_trips_through_a_rebuild(self):
        s = [x for x in _dups(CHAIN) if x["stmt"].startswith("partB")][0]
        new, _w, _t = M.build(CHAIN, s)
        self.assertNotIn(M._sig(s), [M._sig(x) for x in _dups(new)])


if __name__ == "__main__":
    unittest.main()
