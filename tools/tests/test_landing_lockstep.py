#!/usr/bin/env python3
"""landing_refusal's LOCKSTEP DECLARATION rule (pin_census._arm_lockstep_decls, 2026-09-27)."""
import sys
import unittest
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
from pin_census import _arm_lockstep_decls  # noqa: E402

CUR = """void f(u8 *a) {
    s16 n;
#ifndef NON_MATCHING
    register u8 *fin ASM_REG("$18");
    s32 keep;
#else
    u8 *fin;
    s32 keep;
#endif
    fin = a;
    g(fin, keep);
}
"""
NEW = """void f(u8 *a) {
    s16 n;
#ifndef NON_MATCHING
    s32 keep;
#else
    s32 keep;
#endif
    g(a, keep);
}
"""


class LockstepDecls(unittest.TestCase):
    def test_removed_everywhere_declaration_may_go(self):
        self.assertTrue(_arm_lockstep_decls(NEW, CUR))

    def test_declaration_still_used_is_refused(self):
        new = NEW.replace("g(a, keep);", "g(a, keep); fin = 0;")
        self.assertFalse(_arm_lockstep_decls(new, CUR))

    def test_edited_port_line_is_refused(self):
        new = NEW.replace("#else\n    s32 keep;", "#else\n    s16 keep;")
        self.assertFalse(_arm_lockstep_decls(new, CUR))

    def test_added_port_line_is_refused(self):
        new = NEW.replace("#else\n    s32 keep;", "#else\n    s32 keep;\n    s32 extra;")
        self.assertFalse(_arm_lockstep_decls(new, CUR))

    def test_removed_statement_is_refused(self):
        cur = CUR.replace("    u8 *fin;\n", "    u8 *fin;\n    keep = 0;\n")
        self.assertFalse(_arm_lockstep_decls(NEW, cur))

    def test_initialized_declaration_is_refused(self):
        cur = CUR.replace("    u8 *fin;\n", "    u8 *fin = 0;\n")
        self.assertFalse(_arm_lockstep_decls(NEW, cur))

    def test_mirrored_statement_edit_may_land(self):
        cur = CUR.replace("    fin = a;\n", "#ifndef NON_MATCHING\n    t = 1;\n#else\n    t = 1;\n#endif\n    fin = a;\n")
        new = NEW.replace("    g(a, keep);", "#ifndef NON_MATCHING\n    a[4] = 1;\n#else\n    a[4] = 1;\n#endif\n    g(a, keep);")
        self.assertTrue(_arm_lockstep_decls(new, cur))

    def test_unmirrored_statement_edit_is_refused(self):
        cur = CUR.replace("    fin = a;\n", "#ifndef NON_MATCHING\n    t = 1;\n#else\n    t = 1;\n#endif\n    fin = a;\n")
        new = NEW.replace("    g(a, keep);", "#ifndef NON_MATCHING\n    t = 1;\n#else\n    a[4] = 1;\n#endif\n    g(a, keep);")
        self.assertFalse(_arm_lockstep_decls(new, cur))

    def test_no_port_change_is_not_this_rule(self):
        self.assertFalse(_arm_lockstep_decls(CUR, CUR))


if __name__ == "__main__":
    unittest.main()
