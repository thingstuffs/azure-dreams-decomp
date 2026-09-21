"""T92: run detection and the symbol rewrite are textual; the screen and `vf` are not exercised."""
import os, sys, unittest
sys.path.insert(0, os.path.join(os.path.dirname(__file__), "..", "xform")); sys.path.insert(0, os.path.join(os.path.dirname(__file__), ".."))
import t92_pagerun as M  # noqa: E402
from pin_census import sites_of, unscored_text  # noqa: E402

ONELINE = '''#include "common.h"
extern s16 D_8006CCD8[];
extern s16 D_8006CCE8[];
void f(S *action, s32 *grid_x) {
    s32 table_work;
    s16 *table;
    u16 *update_x_entry;
    u16 *update_y_entry;
    (table_work) = 0x80070000; ASM_KEEP(table_work); (table_work) -= 0x3328;
    table = (s16 *)((s16)action->angle);
    update_x_entry = (u16 *)((s32)table + table_work);
    (table_work) = 0x80070000; ASM_KEEP(table_work); (table_work) -= 0x3318;
    update_y_entry = (u16 *)((s32)table + table_work);
    ASM_KEEP(update_y_entry);
    *grid_x = *update_x_entry + *update_y_entry;
}
'''

DECLINIT = '''#include "common.h"
extern u32 D_800E3DF0[];
void g(S *donor) {
    u32 dead_base = 0x800E0000;
    s32 dead_index;
    ASM_KEEP_NV(dead_base);
    dead_index = donor->unk_03;
    ASM_KEEP(dead_index);
    dead_base += 0x3DF0;
    ASM_KEEP_NV(dead_base);
    *(u32 *)(dead_base + ((dead_index & 0x1F) * 4)) = 0;
}
'''

PORTARM = '''#include "common.h"
extern s16 D_8006CCE8[];
void h(s32 offset_addr, s16 *out) {
    register s16 *y_offsets ASM_REG("$8");
#ifdef NON_MATCHING
    y_offsets = D_8006CCE8;
#else
    y_offsets = (s16 *)0x80070000;
    ASM_KEEP_NV(y_offsets);
    y_offsets = (s16 *)((u8 *)y_offsets - 0x3318);
#endif
    *out = *(s16 *)((u8 *)y_offsets + offset_addr);
}
'''

SCALED = '''#include "common.h"
void k(s16 *out) {
    s16 *page;
    page = (s16 *)0x80070000;
    ASM_KEEP(page);
    page -= 0x10;
    *out = *page;
}
'''

NOSTEP = '''#include "common.h"
void m(u8 *out) {
    u8 *page;
    page = (u8 *)0x80080000;
    ASM_KEEP(page);
    *out = page[0x20];
}
'''


class Runs(unittest.TestCase):
    def test_oneline_runs(self):
        rs = M.runs(ONELINE)
        self.assertEqual([(r["v"], hex(r["addr"])) for r in rs],
                         [("table_work", "0x8006ccd8"), ("table_work", "0x8006cce8")])
        # the window of the second run swallows the pin statement that follows the last step
        second = rs[1]
        win = [s for s in sites_of(ONELINE) if second["lo"] <= s[3] < second["hi"]]
        self.assertEqual(sorted(s[2] for s in win), ["table_work"])
        wide = [s for s in sites_of(ONELINE) if second["lo"] <= s[3] < second["wide"]]
        self.assertEqual(sorted(s[2] for s in wide), ["table_work", "update_y_entry"])

    def test_declaration_initialiser_and_intervening_statements(self):
        rs = M.runs(DECLINIT)
        self.assertEqual([(r["v"], hex(r["addr"])) for r in rs], [("dead_base", "0x800e3df0")])
        win = [s for s in sites_of(DECLINIT) if rs[0]["lo"] <= s[3] < rs[0]["hi"]]
        self.assertEqual(sorted(s[2] for s in win), ["dead_base", "dead_base", "dead_index"])

    def test_pointer_step_scaling(self):
        # `page -= 0x10` on an `s16 *` is 0x20 BYTES; the byte-viewed step is not scaled
        self.assertEqual([hex(r["addr"]) for r in M.runs(SCALED)], ["0x8006ffe0"])
        self.assertEqual([hex(r["addr"]) for r in M.runs(PORTARM)], ["0x8006cce8"])

    def test_refusals(self):
        self.assertEqual(M.runs(NOSTEP), [])                     # a page with no bias step is t54's
        self.assertEqual(M.T.eligible(NOSTEP, None, {}), "no staged page run")
        self.assertIsNone(M.T.eligible(ONELINE, None, {}))


class Rewrite(unittest.TestCase):
    def test_oneline(self):
        labels = [l for l, _ in M.candidates(ONELINE)]
        self.assertTrue(any(l.endswith("table_work:win") for l in labels))
        by = dict(M.candidates(ONELINE))
        one = next(v for k, v in by.items() if k.startswith("run@") and k.endswith(":win"))
        self.assertIn("table_work = (s32)D_8006CCD8;", one)      # the integer local keeps its cast
        self.assertNotIn("0x3328", one)
        self.assertNotIn("(table_work) = 0x80070000; ASM_KEEP(table_work); (table_work) -= 0x3328;", one)
        allruns = next(v for k, v in by.items() if k.startswith("runs2") and k.endswith(":wide"))
        self.assertIn("table_work = (s32)D_8006CCE8;", allruns)
        self.assertEqual(len(sites_of(allruns)), 0)              # all three pins fall with the two runs
        narrow = next(v for k, v in by.items() if k.startswith("runs2") and k.endswith(":win"))
        self.assertEqual([s[2] for s in sites_of(narrow)], ["update_y_entry"])

    def test_declaration_initialiser_keeps_the_declaration(self):
        by = dict(M.candidates(DECLINIT))
        win = next(v for k, v in by.items() if k.endswith(":win"))
        self.assertIn("u32 dead_base = (u32)D_800E3DF0;", win)
        self.assertNotIn("dead_base += 0x3DF0;", win)
        self.assertEqual(len(sites_of(win)), 0)                  # the pin on `dead_index` goes too
        var = next(v for k, v in by.items() if k.endswith(":var"))
        self.assertEqual([s[2] for s in sites_of(var)], ["dead_index"])

    def test_port_arm_is_never_touched(self):
        by = dict(M.candidates(PORTARM))
        self.assertTrue(by)
        for new in by.values():
            self.assertEqual(unscored_text(new), unscored_text(PORTARM))
            self.assertIn("#ifdef NON_MATCHING", new)
            self.assertNotIn("0x80070000", new)
            self.assertIn("y_offsets = D_8006CCE8;\n#endif", new)

    def test_missing_symbol_gets_an_extern(self):
        by = dict(M.candidates(SCALED))
        new = next(iter(by.values()))
        self.assertIn("extern u8 D_8006FFE0[];", new)
        self.assertIn("page = (s16 *)D_8006FFE0;", new)


if __name__ == "__main__":
    unittest.main()
