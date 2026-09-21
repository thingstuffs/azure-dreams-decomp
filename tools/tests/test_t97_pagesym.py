"""T97: the neighbour-symbol spelling and the cross-variable tail are textual; the screen and `vf` are not run."""
import os, re, sys, unittest
sys.path.insert(0, os.path.join(os.path.dirname(__file__), "..", "xform")); sys.path.insert(0, os.path.join(os.path.dirname(__file__), ".."))
import t97_pagesym as M  # noqa: E402
from pin_census import sites_of, unscored_text  # noqa: E402

RUN = '''#include "common.h"
extern u8 D_8006CCE8[];
void f(s32 *out) {
    u8 *camera_state;
    s32 depth;

    depth = out[0];
    camera_state = (u8 *) 0x80070000;
    ASM_KEEP_NV(camera_state);
    camera_state -= 13008;
    ASM_USE_NV(camera_state);
    *((s32 *) (((s8 *) camera_state) + 0x1C)) = depth;
}
'''

TAIL = '''#include "common.h"
void g(s32 *out) {
    register u8 *table_page ASM_REG("$2");
    register u8 *table ASM_REG("$22");

    table_page = (u8 *)0x80150000;
    ASM_KEEP(table_page);
    table = table_page + 0x1168;
    out[0] = (s32)table;
}
'''

NOTHING = '''#include "common.h"
void h(s32 *out) {
    s32 v;
    v = out[0];
    ASM_KEEP(v);
    out[1] = v;
}
'''


class TestSpellings(unittest.TestCase):
    def test_pointer_local_is_byte_scaled_off_a_neighbour(self):
        sp = dict((t, e) for t, e, _x in M.spellings(RUN, 0x8006CD30, "u8", 1))
        self.assertIn("new+0x20", sp)
        self.assertEqual(sp["new+0x20"], "D_8006CD10 + 0x20")   # the invented extern is an array
        self.assertEqual(sp["exact"], "D_8006CD30")

    def test_integer_local_casts_the_symbol_before_the_offset(self):
        sp = dict((t, e) for t, e, _x in M.spellings(RUN, 0x8006CCD8, "s32", 0))
        self.assertEqual(sp["file-16"], "(s32)D_8006CCE8 - 0x10")

    def test_a_symbol_the_file_names_is_offered_before_an_invented_one(self):
        tags = [t for t, _e, _x in M.spellings(RUN, 0x8006CCD8, "s32", 0)]
        self.assertTrue(tags[0].startswith("file"), tags)

    def test_an_undeclared_symbol_brings_its_extern(self):
        sp = dict((t, x) for t, _e, x in M.spellings(RUN, 0x8006CD30, "u8", 1))
        self.assertTrue(any("extern u8 D_8006CD10[];" in x for x in sp["new+0x20"]), sp["new+0x20"])
        self.assertEqual(sp["file+72"], set())                  # D_8006CCE8 is already declared


class TestTails(unittest.TestCase):
    def test_the_cross_variable_tail_is_found_with_the_destination_type(self):
        ts = M.tails(TAIL)
        self.assertEqual([(t["v"], t["w"], t["addr"], t["ty"], t["ptr"]) for t in ts],
                         [("table_page", "table", 0x80151168, "u8", 1)])

    def test_a_seed_local_read_after_the_tail_is_refused(self):
        live = TAIL.replace("    out[0] = (s32)table;", "    out[0] = (s32)table + (s32)table_page;")
        self.assertEqual(M.tails(live), [])

    def test_a_plain_run_is_not_a_tail(self):
        self.assertEqual(M.tails(RUN), [])

    def test_a_row_with_neither_is_refused(self):
        self.assertTrue(M.T.eligible(NOTHING, {}, {}))


class TestMenu(unittest.TestCase):
    def test_the_run_menu_offers_several_symbols_and_drops_pins(self):
        menu = M.candidates(RUN)
        self.assertTrue(menu)
        tags = {l.split(":")[1] for l, _c in menu}
        self.assertIn("exact", tags)
        self.assertTrue(any(t.startswith("new+") for t in tags), tags)
        for label, cand in menu:
            self.assertLess(len(sites_of(cand)), len(sites_of(RUN)), label)
            self.assertEqual(unscored_text(cand), unscored_text(RUN), label)
            self.assertNotIn("0x80070000", cand)

    def test_the_core_plan_keeps_the_use_pin_the_window_swallows(self):
        menu = dict((l, c) for l, c in M.candidates(RUN))
        core = [c for l, c in menu.items() if l.endswith(":core")]
        self.assertTrue(core)
        self.assertTrue(all("ASM_USE_NV" in c for c in core))
        self.assertTrue(all("ASM_KEEP_NV" not in c for c in core))

    def test_the_tail_collapses_the_seed_and_the_keep_into_one_statement(self):
        menu = M.candidates(TAIL)
        self.assertTrue(menu)
        exact = [c for l, c in menu if ":exact:" in l][0]
        self.assertIn("table = D_80151168;", exact)
        self.assertNotIn("0x80150000", exact)
        self.assertNotIn("ASM_KEEP(table_page)", exact)


if __name__ == "__main__":
    unittest.main()
