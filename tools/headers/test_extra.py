"""Regression coverage for evidence routing, exact data views and reruns."""
import sys
from pathlib import Path
import unittest
sys.path.insert(0, str(Path(__file__).resolve().parent))
from test_headers import mkroot, COMMON
import plan as P
import rewrite as R
import extra

class ExtraTests(unittest.TestCase):
    def run_plan(self, files, data=True):
        td, root = mkroot({'include/common.h': COMMON, **files})
        self.addCleanup(td.cleanup)
        return root, P.build(root, scope=['src'], include_data=data)

    def edit_all(self, root, pl):
        for h in pl.headers:
            p=root/h; p.parent.mkdir(parents=True, exist_ok=True); p.write_text(R.header_text(pl,h))
        for rel,tp in pl.tus.items():
            p=root/rel; p.write_text(R.edit_tu(p.read_text(),R.tu_edit(tp,lambda r: pl.fn_for_def(r.definition).header)))

    def test_sdk_link_layout_and_alias(self):
        root, pl=self.run_plan({
            'config/slus_006.14.yaml':'  - [0x37cb8, asm, psyq/libgte/GEO_00]\n  - [0x37d84, bin]\n',
            'config/slus_006.14.symbols.txt':'rsin = 0x800644B8; // type:func\n',
            'src/engine/a.c':'#include "common.h"\nextern s32 func_800644B8(s32);\ns32 a(void) { return func_800644B8(2); }\n'})
        self.assertEqual(pl.sdk_census[0][3:6],('psyq_library','libgte','rsin'))
        self.assertIn('include/sdk/libgte.h',pl.tus['src/engine/a.c'].add)
        self.assertIn('Stand-in declarations for the Psy-Q SDK library libgte.',R.header_text(pl,'include/sdk/libgte.h'))

    def test_unknown_is_held(self):
        _,pl=self.run_plan({'src/engine/a.c':'#include "common.h"\nextern s32 mystery(s32);\n'})
        self.assertEqual(pl.sdk_census[0][7:9],('hold','no_link_or_definition_evidence'))
        self.assertEqual(pl.tus['src/engine/a.c'].remove,[])

    def test_renamed_game_alias_owner(self):
        _,pl=self.run_plan({'config/names.tsv':'0x80000000\tfunc_80000000\trenamed\tevidence\n',
            'src/engine/a.c':'#include "common.h"\ns32 renamed(s32 a) { return a; }\n',
            'src/town/b.c':'#include "common.h"\nextern s32 func_80000000(s32);\n'})
        self.assertEqual(pl.sdk_census[0][3],'game_c_alias')
        self.assertIn('include/engine.h',pl.tus['src/town/b.c'].add)

    def test_resident_link_alias_has_c_owner(self):
        _,pl=self.run_plan({
            'config/slus_006.14.yaml':' - [0x102c4, c, code]\n - [0x33618, bin]\n',
            'config/slus_006.14.symbols.txt':'old_link_name = 0x80040000; // type:func\n',
            'src/engine/a.c':'#include "common.h"\ns32 func_80040000(s32 value) { return value; }\n',
            'src/main/b.c':'#include "common.h"\nextern s32 old_link_name(s32);\n'})
        self.assertEqual(pl.sdk_census[0][3],'game_c_alias')
        self.assertIn('include/engine.h',pl.tus['src/main/b.c'].add)

    def test_data_owned_and_imported_per_image(self):
        _,pl=self.run_plan({
            'src/engine/a.c':'#include "common.h"\ns32 owned;\n',
            'src/town/b.c':'#include "common.h"\nextern s32 owned;\nextern u8 imported[4];\n',
            'src/dungeon/c.c':'#include "common.h"\nextern u8 imported[4];\n'})
        self.assertEqual(pl.tus['src/town/b.c'].add,['include/engine.h','include/town/data.h'])
        self.assertIn('extern s32 owned;',R.header_text(pl,'include/engine.h'))
        self.assertIn('include/dungeon/data.h',pl.headers)
        self.assertEqual(pl.tus['src/dungeon/c.c'].add,['include/dungeon/data.h'])

    def test_all_differing_views_hold_including_no_definition(self):
        _,pl=self.run_plan({'src/engine/a.c':'#include "common.h"\nextern u8 imported[];\n',
            'src/town/b.c':'#include "common.h"\nextern u8 imported[4];\n'})
        self.assertEqual(pl.data_census[0][2],'data_views_differ')
        self.assertNotIn('include/slus/data.h',pl.headers)

    def test_definition_extent_mismatch_holds(self):
        _,pl=self.run_plan({'src/engine/a.c':'#include "common.h"\nu8 owned[4];\n',
            'src/town/b.c':'#include "common.h"\nextern u8 owned[];\n'})
        self.assertEqual(pl.data_census[0][2],'data_definition_view_differs')

    def test_data_int_and_long_are_different_c_types(self):
        _,pl=self.run_plan({'src/engine/a.c':'#include "common.h"\nextern int imported;\n',
            'src/town/b.c':'#include "common.h"\nextern long imported;\n'})
        self.assertEqual(pl.data_census[0][2],'data_views_differ')

    def test_array_typedef_extents_are_not_erased(self):
        _,pl=self.run_plan({'include/shared/arrays.h':'typedef u8 Four[4];\ntypedef u8 Eight[8];\n',
            'src/engine/a.c':'#include "common.h"\n#include "shared/arrays.h"\nextern Four imported;\n',
            'src/town/b.c':'#include "common.h"\n#include "shared/arrays.h"\nextern Eight imported;\n'})
        self.assertEqual(pl.data_census[0][2],'data_views_differ')

    def test_callback_typedef_return_views_conflict(self):
        _,pl=self.run_plan({'include/shared/callback.h':'typedef void (*VoidFn)(s32);\ntypedef s32 (*WordFn)(s32);\n',
            'src/engine/a.c':'#include "common.h"\n#include "shared/callback.h"\nextern VoidFn imported;\n',
            'src/town/b.c':'#include "common.h"\n#include "shared/callback.h"\nextern WordFn imported;\n'})
        self.assertEqual(pl.data_census[0][2],'data_views_differ')

    def test_function_address_is_never_published_as_imported_data(self):
        _, pl = self.run_plan({
            'config/names.tsv': '0x80041000\tfunc_80041000\tupdate_object\tevidence\n'
                                '0x80041000\tD_80041000\tupdate_address\tevidence\n',
            'src/engine/a.c': '#include "common.h"\nvoid update_object(void *a) {}\n',
            'src/town/b.c': '#include "common.h"\nextern u8 update_address[];\n'
                            'void *b(void) { return update_address; }\n'})
        row = next(r for r in pl.data_census if r[0] == 'update_address')
        self.assertEqual(row[1:3], ('hold', 'data_is_function_address'))
        self.assertNotIn('include/town/data.h', pl.headers)
        self.assertIn('extern u8 update_address[];',
                      R.edit_tu(pl.corpus.text('src/town/b.c'),
                                R.tu_edit(pl.tus['src/town/b.c'], lambda r: pl.fn_for_def(r.definition).header)))

    def test_functions_only_does_not_republish_legacy_function_data(self):
        root, _ = self.run_plan({
            'config/names.tsv': '0x80041000\tfunc_80041000\tupdate_object\tevidence\n',
            'include/town/data.h': '/* maintained by tools/headers */\n'
                                   '#include "common.h"\nextern u8 D_80041000[];\n',
            'src/engine/a.c': '#include "common.h"\nvoid update_object(void *a) {}\n',
            'src/town/b.c': '#include "common.h"\n#include "town/data.h"\n'
                            'void *b(void) { return D_80041000; }\n'})
        again = P.build(root, scope=['src'], include_data=False)
        self.assertNotIn('include/town/data.h', again.headers)
        self.assertEqual(next(r for r in again.data_census if r[0] == 'D_80041000')[2],
                         'data_is_function_address')

    def test_coincident_other_overlay_entry_is_not_a_function_address(self):
        _, pl = self.run_plan({
            'src/dungeon/a.c': '#include "common.h"\nvoid func_80024000(void *a) {}\n',
            'src/town/b.c': '#include "common.h"\nextern u8 D_80024000[];\n'
                            'void *b(void) { return D_80024000; }\n'})
        row = next(r for r in pl.data_census if r[0] == 'D_80024000')
        self.assertEqual(row[1:3], ('candidate', ''))

    def test_data_rerun_retains_import_owner(self):
        root,pl=self.run_plan({'src/engine/a.c':'#include "common.h"\nextern u8 imported[4];\ns32 a(void) { return imported[0]; }\n'})
        self.edit_all(root,pl)
        before=(root/'src/engine/a.c').read_text()
        again=P.build(root,scope=['src'],include_data=True)
        self.assertIn('include/slus/data.h',again.headers)
        self.assertEqual(R.edit_tu(before,R.tu_edit(again.tus['src/engine/a.c'],lambda r:again.fn_for_def(r.definition).header)),before)
        for h in again.headers:
            self.assertEqual(R.header_text(again,h),(root/h).read_text())

    def test_sdk_rerun_retains_owner(self):
        root,pl=self.run_plan({'src/engine/a.c':'#include "common.h"\nextern s32 abs(s32);\ns32 a(s32 x) { return abs(x); }\n'})
        self.edit_all(root,pl)
        before=(root/'src/engine/a.c').read_text()
        again=P.build(root,scope=['src'],include_data=True)
        self.assertEqual(R.edit_tu(before,R.tu_edit(again.tus['src/engine/a.c'],lambda r:again.fn_for_def(r.definition).header)),before)

    def test_unused_declaration_rerun_is_stable(self):
        root,pl=self.run_plan({'src/engine/a.c':'#include "common.h"\nextern s32 abs(s32);\nextern u8 imported[4];\n'})
        self.edit_all(root,pl)
        before=(root/'src/engine/a.c').read_text()
        again=P.build(root,scope=['src'],include_data=True)
        self.assertEqual(R.edit_tu(before,R.tu_edit(again.tus['src/engine/a.c'],lambda r:again.fn_for_def(r.definition).header)),before)

    def test_functions_only_retains_published_data_without_new_data_moves(self):
        root,pl=self.run_plan({
            'src/engine/a.c':'#include "common.h"\ns32 owned;\ns32 a(void) { return owned; }\n',
            'src/town/b.c':'#include "common.h"\nextern s32 owned;\nextern u8 imported[4];\ns32 b(void) { return owned + imported[0]; }\n'})
        self.edit_all(root,pl)
        before=(root/'src/town/b.c').read_text()
        owner=(root/'include/engine.h').read_text()
        imported=(root/'include/town/data.h').read_text()
        (root/'src/town/c.c').write_text('#include "common.h"\nextern u8 imported[4];\ns32 c(void) { return imported[0]; }\n')
        again=P.build(root,scope=['src'],include_data=False)
        self.assertEqual(R.header_text(again,'include/engine.h'),owner)
        self.assertEqual(R.header_text(again,'include/town/data.h'),imported)
        edit=lambda rel:R.edit_tu((root/rel).read_text(),R.tu_edit(again.tus[rel],lambda r:again.fn_for_def(r.definition).header))
        self.assertEqual(edit('src/town/b.c'),before)
        self.assertIn('extern u8 imported[4];',edit('src/town/c.c'))
        self.assertNotIn('#include "town/data.h"',edit('src/town/c.c'))

    def test_functions_only_retains_an_unused_data_only_header(self):
        root,pl=self.run_plan({'src/engine/a.c':'#include "common.h"\nextern u8 imported[4];\n'})
        self.edit_all(root,pl)
        before=(root/'src/engine/a.c').read_text()
        again=P.build(root,scope=['src'],include_data=False)
        self.assertIn('include/slus/data.h',again.headers)
        self.assertEqual(R.header_text(again,'include/slus/data.h'),(root/'include/slus/data.h').read_text())
        self.assertEqual(R.edit_tu(before,R.tu_edit(again.tus['src/engine/a.c'],lambda r:again.fn_for_def(r.definition).header)),before)

    def test_legacy_header_declaration_is_reported_after_local_moves(self):
        root,pl=self.run_plan({
            'include/shared/legacy.h':'#include "common.h"\nextern s32 owned;\n',
            'src/engine/a.c':'#include "common.h"\ns32 owned;\ns32 a(void) { return owned; }\n',
            'src/engine/b.c':'#include "common.h"\n#include "shared/legacy.h"\ns32 b(void) { return owned; }\n'})
        self.edit_all(root,pl)
        again=P.build(root,scope=['src'],include_data=True)
        rows=extra.legacy_data_census(again)
        self.assertEqual(len(rows),1)
        self.assertEqual(rows[0][0:2],('owned','include/shared/legacy.h'))
        self.assertEqual(rows[0][5:7],('include/engine.h','include/engine.h'))
        self.assertIn('extern s32 owned;',(root/'include/shared/legacy.h').read_text())

if __name__=='__main__': unittest.main()
