"""T119 and tools/dead_init.py: the dead zero initializer lever (owner ruling 2026-09-23); textual, nothing compiles."""
import os, sys, unittest
sys.path.insert(0, os.path.join(os.path.dirname(__file__), "..", "xform")); sys.path.insert(0, os.path.join(os.path.dirname(__file__), ".."))
import t119_deadinit as M  # noqa: E402
import dead_init  # noqa: E402
from pin_census import sites_of  # noqa: E402

ADD = '''#include "common.h"
void f(void *action) {
    void *allocated_effect;
    void *effect;

    allocated_effect = func_8003FD64(0x112);
    effect = allocated_effect;
    ASM_KEEP(allocated_effect);
    ((S_0 *)action)->unk_A4 = allocated_effect;
    if (effect != 0) {
        func_80001000(effect);
    }
}
'''

REMOVE = '''#include "common.h"
void g(s32 a) {
    s32 total = 0;

    total = a * 3;
    ASM_KEEP(total);
    func_80001000(total);
}
'''


class TestMenu(unittest.TestCase):
    def test_add_on_the_copy_with_the_copy_sunk(self):
        mn = dict(M.menu(ADD))
        self.assertIn("add:effect@8:sink", mn)
        t = mn["add:effect@8:sink"]
        self.assertIn("void *effect = 0;", t)
        self.assertNotIn("ASM_KEEP", t)
        self.assertLess(t.index("unk_A4 = allocated_effect;"), t.index("effect = allocated_effect;"))

    def test_no_sink_past_a_reader_of_the_destination(self):
        t = ADD.replace("((S_0 *)action)->unk_A4 = allocated_effect;", "((S_0 *)action)->unk_A4 = effect;")
        self.assertFalse([l for l, _c in M.menu(t) if l.endswith(":sink")])

    def test_remove_drops_the_initializer_with_the_pin(self):
        mn = dict(M.menu(REMOVE))
        self.assertIn("remove:total:named", mn)
        self.assertIn("    s32 total;", mn["remove:total:named"])
        self.assertEqual(len(sites_of(mn["remove:total:named"])), 0)


class TestDeadInitRecord(unittest.TestCase):
    def test_gained_initializer_is_a_trade(self):
        new = dict(M.menu(ADD))["add:effect@8:sink"]
        rec = dead_init.record("dungeon/x", ADD, new, "lane", "T")
        self.assertEqual(rec["kind"], "dead_init")
        self.assertEqual(rec["init"], "void *effect = 0;")
        self.assertIn("ASM_KEEP(allocated_effect);", rec["site"])

    def test_removed_initializer_is_not_a_trade(self):
        new = dict(M.menu(REMOVE))["remove:total:named"]
        self.assertIsNone(dead_init.record("dungeon/y", REMOVE, new, "lane", "T"))


if __name__ == "__main__":
    unittest.main()
