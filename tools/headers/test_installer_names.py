"""Safety and rewrite coverage for reviewed callback installs."""
from pathlib import Path
import re
import sys
import tempfile
import unittest
from unittest.mock import patch

sys.path.insert(0, str(Path(__file__).resolve().parent))
import installer_names as I


class RewriteTest(unittest.TestCase):
    def test_address_of_zero_array_element_is_the_function_entry(self):
        text = 'extern int alias[4];\nvoid f(void) { slot = &alias[0]; other = &(alias[0]); }\n'
        out, counts = I.rewrite(text, [('alias', 'tick', 'include/town.h')])
        self.assertIn('slot = tick; other = tick;', out)
        self.assertNotIn('tick[0]', out)
        self.assertEqual(counts, dict(alias=2))
        self.assertIsNone(re.search(I.address_pattern('alias'), '&alias[1]'))

    def test_frozen_data_spelling_rebases_only_in_the_reviewed_installer(self):
        text = 'void install(void) { slot = &named_address; }\n'
        names = dict(named_address='D_80010000')
        self.assertEqual(I.current_spelling(text, 'install', 'D_80010000', 'tick', names), 'named_address')
        self.assertEqual(I.current_spelling(text, 'other', 'D_80010000', 'tick', names), 'D_80010000')

    def test_scalar_array_comparison_and_cast(self):
        text = '''#include "common.h"
extern int scalar_alias;
extern unsigned char array_alias[];
/* scalar_alias and &array_alias are comments */
void install(void) {
    slot = &scalar_alias;
    if (slot == (void *)& (scalar_alias)) slot = array_alias;
    say("&scalar_alias");
}
'''
        pairs = [('scalar_alias', 'tick', 'include/town/object.h'),
                 ('array_alias', 'advance', 'include/town/object.h')]
        out, counts = I.rewrite(text, pairs)
        self.assertNotIn('extern int', out)
        self.assertNotIn('extern unsigned', out)
        self.assertIn('slot = tick;', out)
        self.assertIn('(void *)tick', out)
        self.assertIn('slot = advance;', out)
        self.assertIn('/* scalar_alias and &array_alias are comments */', out)
        self.assertIn('say("&scalar_alias")', out)
        self.assertEqual(out.count('#include "town/object.h"'), 1)
        self.assertEqual(counts, dict(scalar_alias=2, array_alias=1))
        again, counts = I.rewrite(out, pairs)
        self.assertEqual(out, again)
        self.assertEqual(counts, {})

    def test_declarations_do_not_remove_storage_or_multiple_names(self):
        self.assertEqual(I.declarations('int alias = 3;\n', 'alias'), [])
        self.assertEqual(I.declarations('extern int alias, other;\n', 'alias'), [])
        self.assertTrue(I.declarations('extern void alias(void);\n', 'alias'))
        self.assertTrue(I.declarations('void alias(void);\n', 'alias'))
        self.assertEqual(I.declarations('static void alias(void);\n', 'alias'), [])

    def test_logical_and_is_not_address_of(self):
        out, _ = I.rewrite('void f(void) { if (ok && alias) use(); }\n',
                           [('alias', 'tick', 'include/town.h')])
        self.assertIn('ok && tick', out)


class EntryTest(unittest.TestCase):
    def check(self, contexts, entries, before=0x80010000, after=0x80010000):
        return I.check_entry(contexts, entries, 'src/town/tick.c', 'tick', 0x80010000,
                             before, after, (), {})

    def test_same_address_in_other_bank_cannot_prove_entry(self):
        entries = {'town/bank_b': {0x80010000: ({'src/town/tick.c'}, 'tick')}}
        self.assertEqual(self.check([('town/bank_a', [], 0)], entries)[0],
                         'callback_not_entry_in_installer_image')

    def test_exact_name_and_file_are_required_in_every_image(self):
        entries = {'town/a': {0x80010000: ({'src/town/tick.c'}, 'tick')},
                   'town/b': {0x80010000: ({'src/town/other.c'}, 'tick')}}
        self.assertEqual(self.check([('town/a', [], 0)], entries)[0], '')
        self.assertTrue(self.check([('town/a', [], 0), ('town/b', [], 0)], entries)[0])
        self.assertEqual(self.check([], entries)[0], 'no_installer_image')

    def test_home_copy_requires_copy_link_record(self):
        entries = {'town/a': {0x80010000: ({'src/town/tick.c'}, 'tick')}}
        with patch('linklist.copy_link_target', return_value=0x80010000):
            result = self.check([('town/a', ['town/installer'], 0)], entries, after=0x80020000)
        self.assertEqual(result[0], '')
        self.assertEqual(result[2], ['town/installer'])
        with patch('linklist.copy_link_target', side_effect=ValueError('ambiguous')):
            self.assertEqual(self.check([('town/a', [], 0)], entries, after=0x80020000)[0],
                             'unproved_copy_binding')


class MeasureTest(unittest.TestCase):
    def test_install_identity_and_comparisons_are_counted_separately(self):
        import gzip
        import json
        import sqlite3
        with tempfile.TemporaryDirectory() as directory:
            path = Path(directory) / 'codemap.db'
            db = sqlite3.connect(path)
            db.executescript('CREATE TABLE recipe(id,source,physical); CREATE TABLE tu_dep(recipe,path); '
                             'CREATE TABLE flow_tu(tu,blob);')
            edges = [dict(k=kind, file='src/town/install.c', fn=fn, src='FN:tick', dst='G:slot', line=line)
                     for kind, fn, line in [('assign', 'install', 2), ('cmp', 'install', 3),
                                            ('assign', 'other', 4)]]
            edges.append(dict(k='cmp', file='src/town/install.c', fn='install', src='G:slot', dst='FN:tick', line=5))
            db.execute('INSERT INTO flow_tu VALUES (?,?)',
                       ('src/town/install.c', gzip.compress(json.dumps(dict(edges=edges)).encode())))
            db.commit()
            db.close()
            result = I.measure(path, [dict(file='src/town/install.c', installer='install', new='tick')])
            self.assertEqual(result[0]['install_sites'], 1)
            self.assertEqual(result[0]['comparison_sites'], 2)


class RetirementTest(unittest.TestCase):
    def fixture(self, root):
        for directory in ('src/town', 'src/dungeon/actor', 'include/town', 'config'):
            (root / directory).mkdir(parents=True)
        (root / 'config/names.tsv').write_text(
            '0x80010000\tD_80010000\talias\tcallback address\n'
            '0x80010000\tfunc_80010000\ttick\tfunction\n')
        (root / 'include/town/data.h').write_text('extern int alias;\n')

    def test_last_user_retires_data_alias_but_keeps_function(self):
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            self.fixture(root)
            (root / 'src/town/install.c').write_text('void install(void) { slot = tick; }\n')
            result = I.retire(root, [dict(old='alias')])
            self.assertEqual(result['names_retired'], ['alias'])
            self.assertEqual((root / 'include/town/data.h').read_text(), '\n')
            self.assertIn('\ttick\t', (root / 'config/names.tsv').read_text())
            self.assertNotIn('\talias\t', (root / 'config/names.tsv').read_text())

    def test_live_excluded_user_and_real_storage_keep_alias(self):
        for text in ('void f(void) { slot = &alias; }\n', 'int alias;\n', 'extern int alias;\n'):
            with self.subTest(text=text), tempfile.TemporaryDirectory() as directory:
                root = Path(directory)
                self.fixture(root)
                (root / 'src/dungeon/actor/f.c').write_text(text)
                self.assertEqual(I.retire(root, [dict(old='alias')])['names_retired'], [])
                self.assertIn('alias', (root / 'include/town/data.h').read_text())


class OwnerTest(unittest.TestCase):
    def test_missing_prototype_is_appended_to_owner_and_never_local(self):
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            (root / 'include/town').mkdir(parents=True)
            (root / 'src/town').mkdir(parents=True)
            (root / 'include/town/object.h').write_text('#ifndef OBJECT_H\n#define OBJECT_H\n#endif\n')
            (root / 'src/town/install.c').write_text('extern int alias;\nvoid install(void) { slot = &alias; }\n')
            row = dict(file='src/town/install.c', old='alias', new='tick', header='include/town/object.h',
                       prototype='void tick(struct Object *object);', type_headers='', tags='struct Object', link='')
            I.apply(root, [row])
            header = (root / 'include/town/object.h').read_text()
            self.assertIn('struct Object;', header)
            self.assertIn(row['prototype'], header)
            source = (root / 'src/town/install.c').read_text()
            self.assertIn('#include "town/object.h"', source)
            self.assertNotIn('extern', source)
            self.assertIn('slot = tick;', source)
            self.assertEqual(I.apply(root, [row]), [])
            self.assertEqual((root / 'include/town/object.h').read_text(), header)

    def test_module_inventory_reclassifies_external_and_removes_self_import(self):
        import json
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            (root / 'config/overlays').mkdir(parents=True)
            (root / 'src/town').mkdir(parents=True)
            (root / 'config/names.tsv').write_text(
                '0x80010000\tfunc_80010000\ttick\tentry\n'
                '0x80020000\tfunc_80020000\tdraw\tentry\n')
            source = 'src/town/tick.c'
            (root / source).write_text('void tick(void) { slot = tick; draw_slot = draw; }\n')
            path = root / 'config/overlays/modules.json'
            path.write_text(json.dumps(dict(modules=[dict(source=source,
                members=[dict(function='func_80010000')], imports=[
                    dict(symbol='D_80010000', kind='data', vma=0x80010000),
                    dict(symbol='D_80020000', kind='data', vma=0x80020000)])])))
            rows = [dict(file=source, old='D_80010000', new='tick'),
                    dict(file=source, old='D_80020000', new='draw')]
            I.module_imports(root, rows)
            imports = json.loads(path.read_text())['modules'][0]['imports']
            self.assertEqual(imports, [dict(symbol='func_80020000', kind='function', vma=0x80020000)])


    def test_function_shaped_data_alias_reclassifies_or_removes_same_symbol(self):
        import json
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            (root / 'config/overlays').mkdir(parents=True)
            (root / 'src/town').mkdir(parents=True)
            (root / 'config/names.tsv').write_text(
                '0x80010000\tfunc_80010000\ttick\tentry\n'
                '0x80020000\tfunc_80020000\tdraw\tentry\n')
            source = 'src/town/tick.c'
            (root / source).write_text('void tick(void) { slot = tick; draw_slot = draw; }\n')
            path = root / 'config/overlays/modules.json'
            path.write_text(json.dumps(dict(modules=[dict(source=source,
                members=[dict(function='func_80010000')], imports=[
                    dict(symbol='func_80010000', kind='data', vma=0x80010000),
                    dict(symbol='func_80020000', kind='data', vma=0x80020000)])])))
            rows = [dict(file=source, old='func_80010000', new='tick'),
                    dict(file=source, old='func_80020000', new='draw')]
            I.module_imports(root, rows)
            imports = json.loads(path.read_text())['modules'][0]['imports']
            self.assertEqual(imports, [dict(symbol='func_80020000', kind='function', vma=0x80020000)])


    def test_owner_api_is_preferred_only_from_exact_header_candidates(self):
        owner = 'include/town/motion.h'
        api = 'include/town/motion_callbacks_api.h'
        private_api = 'include/town/motion/update_api.h'
        self.assertEqual(I.choose_owner_header(owner, {owner, api}), api)
        self.assertEqual(I.choose_owner_header(owner, {owner, private_api}), private_api)
        self.assertEqual(I.choose_owner_header(owner, {owner}), owner)
        self.assertEqual(I.choose_owner_header(owner, {private_api}), private_api)
        self.assertEqual(I.choose_owner_header(owner, {'include/town/a.h', 'include/town/b.h'}), '')
        self.assertEqual(I.choose_owner_header(owner, set()), '')


if __name__ == '__main__':
    unittest.main()
