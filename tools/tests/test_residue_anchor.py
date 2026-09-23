"""tools/lanes/residue_anchor.py: the -g listing parse, residue localisation, anchor tuples and the sites_of /
erase hook (no compiler runs: screen._listing is stubbed)."""
import sys
import types
import unittest
from pathlib import Path

ROOT = next(p for p in Path(__file__).resolve().parents if (p / "tools/common.py").is_file())
sys.path.insert(0, str(ROOT / "tools/lanes"))
import residue_anchor as RA                                                 # noqa: E402

TEXT = """void f(
    s16 a, s32 b)
{
    s32 x = a;
    /* note */
    x += b;
    g(x);
}
"""

RAW_REF = ['\t.file\t1 "f.c"', '\t.file\t2 "common.h"', '\t.ent\tf', 'f:', '\t.loc\t1 3',
           '\tlw\t$4,16($sp)', '$LM2:', '\t.loc\t1 4', '\t.def\tx;\t.val\t4;\t.endef', '\tmove\t$16,$4',
           '\t.loc\t2 9', '\tnop', '\t.loc\t1 6', '\taddu\t$16,$16,$5', '\t.loc\t1 7', '\tjal\tg', '\t.end\tf']
RAW_CAND = [x.replace("lw\t$4", "lh\t$4") for x in RAW_REF]


class Localiser(unittest.TestCase):
    def setUp(self):
        self._orig = RA.XS._listing
        RA._GCACHE.clear()
        RA.XS._listing = lambda row, text: RAW_REF if text == "ref" else RAW_CAND

    def tearDown(self):
        RA.XS._listing = self._orig
        RA._GCACHE.clear()

    def test_tagged_drops_debug_lines_and_keeps_own_file_lines(self):
        lines, locs = RA.tagged({"id": "x/f", "cfg": "2.7.2", "c_path": "src/x/f.c"}, "ref")
        self.assertEqual(lines[0], ".ent")
        self.assertNotIn("LM2:", " ".join(lines))
        self.assertFalse(any(ln.startswith(".def") for ln in lines))
        self.assertEqual(locs[lines.index("nop")], None)            # a header (.file 2) line has no C line
        self.assertEqual(locs[lines.index("addu $16,$16,$5")], 6)

    def test_residue_is_the_changed_instructions_line(self):
        row = {"id": "x/f", "cfg": "2.7.2", "c_path": "src/x/f.c"}
        self.assertEqual(RA.residue_lines(row, "ref", "cand"), [(3, 1)])


class Anchors(unittest.TestCase):
    def test_brace_line_falls_back_to_the_signature(self):
        s = RA.anchor_sites(TEXT, [(3, 5), (6, 2), (5, 1)])
        self.assertEqual([x[5] for x in s], [2, 6])                   # `{` -> signature; the comment line is skipped
        self.assertEqual(s[0][2], "s16 a, s32 b)")
        self.assertEqual(TEXT[s[1][3]:s[1][4]], "x += b;")
        self.assertTrue(all(x[0] == "stmt" and x[1] == RA.MACRO for x in s))

    def test_changed_lines_is_the_first_move(self):
        cand = TEXT.replace("    x += b;\n", "    x = x + b;\n").replace("    /* note */\n", "")
        self.assertEqual(RA.changed_lines(TEXT, cand), [(5, 1)])
        self.assertEqual(RA.changed_lines(TEXT, TEXT.replace("    g(x);\n", "")), [(6, 1), (7, 1)])   # the lines flanking a deletion

    def test_cap_and_dedupe(self):
        s = RA.anchor_sites(TEXT, [(4, 3), (4, 2), (6, 1), (7, 1)], maxn=2)
        self.assertEqual([x[5] for x in s], [4, 6])


class Hook(unittest.TestCase):
    def test_install_patches_xform_bindings_and_anchors_only_the_registered_text(self):
        m = types.ModuleType("xform.t_fake")
        m.__file__ = str(ROOT / "tools/xform/t_fake.py")
        m.sites_of, m.erase_many, m.erase = RA._REAL_SITES, RA._REAL_ERASE_MANY, RA._REAL_ERASE
        other = types.ModuleType("not_xform"); other.__file__ = str(ROOT / "tools/lanes/compose2.py")
        other.sites_of = RA._REAL_SITES
        sys.modules["xform.t_fake"], sys.modules["not_xform"] = m, other
        try:
            RA.install()
            self.assertIs(m.sites_of, RA.sites_of)
            self.assertIs(other.sites_of, RA._REAL_SITES)             # compose2's win check stays real
            sites = RA.anchor_sites(TEXT, [(6, 1)])
            with RA.anchored(TEXT, sites):
                self.assertEqual(m.sites_of(TEXT), sites)
                self.assertEqual(m.sites_of(TEXT + "\n"), [])          # any other pin-free text: the real census
                self.assertEqual(m.erase_many(TEXT, sites, clean_notes=True), TEXT)   # never erased
            self.assertEqual(m.sites_of(TEXT), [])
            pinned = TEXT.replace("    g(x);\n", "    ASM_KEEP(x);\n    g(x);\n")
            real = m.sites_of(pinned)
            self.assertEqual(len(real), 1)
            self.assertNotIn("ASM_KEEP", m.erase_many(pinned, real + sites, clean_notes=True))
        finally:
            sys.modules.pop("xform.t_fake"); sys.modules.pop("not_xform")


if __name__ == "__main__":
    unittest.main()
