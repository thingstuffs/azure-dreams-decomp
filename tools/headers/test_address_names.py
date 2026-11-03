"""Unit coverage for address_names.py (the TU rewrite) and extern_bulk.py's --names filter."""
import argparse
import csv
import sqlite3
from unittest.mock import patch
import sys
import tempfile
import unittest
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import address_names as A   # noqa: E402
import extern_bulk as B     # noqa: E402

TU = '''#include "common.h"

extern s16 func_80069EF8(void); /* random */
extern void func_8003E188(s32 index, s32 flag);

/* calls func_80069EF8 in a comment and "func_80069EF8" in a string stay */
void f(void) {
    s16 value = func_80069EF8();
    extern_like(value);
    func_8003E188(value, 0);
}
'''


class ApplyTest(unittest.TestCase):
    def run_apply(self, text, pairs, header=None):
        with tempfile.TemporaryDirectory() as d:
            root = Path(d)
            (root / 'include').mkdir()
            (root / 'include/common.h').write_text(header or '/* empty */\n')
            (root / 'src').mkdir()
            (root / 'src/a.c').write_text(text)
            log = []
            A._CORPUS.clear()
            A.apply_one(root, 'src/a.c', pairs, log)
            return (root / 'src/a.c').read_text(), log

    def test_respell_declaration_and_calls(self):
        out, log = self.run_apply(TU, [('func_80069EF8', 'rand', ''), ('func_8003E188', 'set_packed_2bit_flag', '')])
        self.assertIn('extern s16 rand(void); /* random */', out)
        self.assertIn('s16 value = rand();', out)
        self.assertIn('set_packed_2bit_flag(value, 0);', out)
        self.assertIn('extern void set_packed_2bit_flag(s32 index, s32 flag);', out)
        # comments and strings untouched
        self.assertIn('calls func_80069EF8 in a comment and "func_80069EF8"', out)
        self.assertEqual([r[4] for r in log], ['respelled', 'respelled'])

    def test_block_statement_is_not_a_declaration(self):
        out, _ = self.run_apply(TU, [('func_80069EF8', 'rand', '')])
        self.assertIn('    s16 value = rand();\n', out)

    def test_visible_declaration_deletes_local_one(self):
        out, log = self.run_apply(TU, [('func_80069EF8', 'rand', '')], header='s32 rand(void);\n')
        self.assertNotIn('extern s16', out)
        self.assertIn('s16 value = rand();', out)
        self.assertTrue(log[0][4].startswith('deleted_declaration'))

    def test_tu_that_declares_the_new_name_keeps_one_declaration(self):
        text = TU.replace('#include "common.h"\n', '#include "common.h"\nextern s32 rand(void);\n')
        out, log = self.run_apply(text, [('func_80069EF8', 'rand', '')])
        self.assertEqual(out.count('rand(void);'), 1)

    def test_no_declaration_and_nothing_visible_holds(self):
        text = 'void g(void) { func_80042640(0, 1); }\n'
        out, log = self.run_apply(text, [('func_80042640', 'init_monster_from_stats', 'include/engine/entity.h')])
        self.assertEqual(out, text)
        self.assertEqual(log[0][4], 'hold:no_visible_prototype')

    def test_existing_call_does_not_supply_a_prototype(self):
        text='void g(void) {\n    old();\n    real();\n}\n'
        out,log=self.run_apply(text,[('old','real','')])
        self.assertEqual(out,text)
        self.assertEqual(log[0][4],'hold:no_visible_prototype')

    def test_screen_reports_rewrite_hold_before_compiling(self):
        with tempfile.TemporaryDirectory() as folder:
            root=Path(folder);(root/'src').mkdir();(root/'include').mkdir()
            (root/'src/a.c').write_text('void f(void) { old(); }\n')
            db=sqlite3.connect(root/'map.db');db.execute('create table recipe(source text,args text)');db.commit();db.close()
            plan=root/'plan.tsv';plan.write_text('file\told\tnew\tnew_header\nsrc/a.c\told\treal\t\n')
            A._CORPUS.clear()
            with patch.object(A,'lib_symbol_names',return_value={}):
                with patch('subprocess.run') as compiler:
                    A.screen(root,root/'map.db',plan,root/'out',workers=1)
                    compiler.assert_not_called()
            rows=list(csv.DictReader((root/'out/screen.tsv').open(),delimiter='\t'))
            self.assertEqual(rows[0]['verdict'],'hold')
            self.assertEqual(rows[0]['why'],'hold:no_visible_prototype')

    def test_idempotent(self):
        once, _ = self.run_apply(TU, [('func_80069EF8', 'rand', '')])
        twice, log = self.run_apply(once, [('func_80069EF8', 'rand', '')])
        self.assertEqual(once, twice)
        self.assertEqual(log, [])


class NamesFilterTest(unittest.TestCase):
    def test_names_file_tsv_and_list(self):
        with tempfile.TemporaryDirectory() as d:
            tsv = Path(d) / 'plan.tsv'
            tsv.write_text('file\told\tnew\tkind\nsrc/a.c\tfunc_1\trand\tlibrary_alias\n')
            a = argparse.Namespace(names=['abs'], names_from=None, names_file=tsv)
            self.assertEqual(B.load_names(a), {'abs', 'rand'})
            lst = Path(d) / 'names.txt'
            lst.write_text('rsin\nrcos\n')
            a = argparse.Namespace(names=None, names_from=None, names_file=lst)
            self.assertEqual(B.load_names(a), {'rsin', 'rcos'})
            a = argparse.Namespace(names=None, names_from=None, names_file=None)
            self.assertIsNone(B.load_names(a))

    def test_names_from_sdk_includes_kernel_entry_points(self):
        a = argparse.Namespace(names=None, names_from='sdk', names_file=None)
        got = B.load_names(a)
        for n in ('OpenEvent', 'EnterCriticalSection', 'SetRCnt', 'rindex', 'rsin'):
            self.assertIn(n, got)


if __name__ == '__main__':
    unittest.main()


class LinkRecordsTest(unittest.TestCase):
    """placed_copy writes the copy-link record; home_self points the name at the true symbol and retires
    other names of that symbol that nothing spells any more."""

    def test_home_self_names_and_placed_copy_record(self):
        import json
        with tempfile.TemporaryDirectory() as d:
            root = Path(d)
            for sub in ('src', 'include', 'config/link', 'tools/link'):
                (root / sub).mkdir(parents=True)
            (root / 'config/names.tsv').write_text(
                '# header\n'
                '0x818BD1C4\tfunc_818BD1C4\tcreate_tinted\tshard:dungeon\n'
                '0x800249C4\tfunc_800249C4\tcreate_colored\tsrc/dungeon/func_818BD1C4.c:47 call-site alias\n'
                '0x800249C4\tfunc_800249C4\tstill_used\tother alias\n'
                '0x800249C4\tfunc_800249C4\tother_slot_fn\tsrc/dungeon/func_81900000.c:6 another row at this slot\n')
            (root / 'src/a.c').write_text('void g(void) { create_tinted(); still_used(); }\n')
            # graph producer stand-in: record the call instead of projecting onto a graph
            (root / 'tools/link/graph.py').write_text(
                'import sys, pathlib\npathlib.Path(sys.argv[sys.argv.index("--root") + 1], "synced").write_text("1")\n')
            rows = [dict(kind='home_self', file='src/a.c', old='create_colored', new='create_tinted',
                         link='func_818BD1C4>func_800249C4', evidence=''),
                    dict(kind='placed_copy', file='src/a.c', old='func_8016B438', new='advance',
                         link='func_80171570>func_8016B438', evidence='same-image copy; rows dungeon/func_80FE16A8')]
            A.link_records(root, rows)
            names = (root / 'config/names.tsv').read_text().splitlines()
            self.assertIn('0x800249C4\tfunc_800249C4\tcreate_tinted\tshard:dungeon | true symbol: the definition runs '
                          'at func_800249C4 (home_self, same-image copy lane)', names)
            self.assertFalse(any('\tcreate_colored\t' in line for line in names))
            self.assertTrue(any('\tstill_used\t' in line for line in names))
            self.assertTrue(any('\tother_slot_fn\t' in line for line in names))   # another row's name stays
            record = json.loads((root / 'config/link/copy_links.json').read_text())
            self.assertEqual(record['units'], {'dungeon/func_80FE16A8': {'func_80171570': 'func_8016B438'}})
            self.assertTrue((root / 'synced').exists())
