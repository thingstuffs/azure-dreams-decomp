import csv
from pathlib import Path
import sqlite3
import tempfile
import unittest

from macro_base_provenance import Function, classify, functions, mask_noncode, report, source_index


class ProvenanceTest(unittest.TestCase):
    def test_function_extraction_ignores_comments_and_table(self):
        source = '''#include "x.h"
/* void fake(void) { } */
void first(Body *state) { state->x = 1; }
void (*table[])(void) = { first };
void second(void) { first(0); }
'''
        self.assertEqual([f.name for f in functions('src/a.c', source)], ['first', 'second'])
        self.assertNotIn('fake', mask_noncode(source))

    def test_multiline_definition_is_not_a_dispatcher_reference(self):
        with tempfile.TemporaryDirectory() as temp:
            root = Path(temp)
            src = root / 'src'
            src.mkdir()
            (src / 'a.c').write_text('void\nupdate\n(void *state)\n{ state = 0; }\n')
            _, _, refs = source_index(root, {'update'})
            self.assertEqual(refs['update'], [])

    def test_report_keeps_site_count_and_requires_body_identity(self):
        with tempfile.TemporaryDirectory() as temp:
            root = Path(temp)
            src = root / 'src' / 'dungeon'
            src.mkdir(parents=True)
            (src / 'creator.c').write_text('''
void create(void) {
  ObjectNodeHeader *node = allocate_flagged_object_node(0x12);
  Body *body;
  body = NODE_BODY(node);
  node->update_callback = update;
  node->update_callback = typed_sibling;
}
''')
            (src / 'update.c').write_text('''
void typed_sibling(Body *body) { body->state = 1; }
void update(void *state, void *sprite) { F(state, 0); F(sprite, 2); }
''')
            build = root / 'build'
            build.mkdir()
            with sqlite3.connect(build / 'codemap.db') as db:
                db.execute('CREATE TABLE call_site(caller TEXT, callee TEXT, file TEXT, line INTEGER)')
                db.execute('INSERT INTO call_site VALUES (?,?,?,?)',
                           ('create', 'update', 'src/dungeon/creator.c', 5))
            inventory = root / 'inventory.tsv'
            with inventory.open('w', newline='') as fh:
                writer = csv.DictWriter(fh, fieldnames=['file', 'function', 'line', 'macro', 'use',
                                                        'base_expr', 'class', 'reason'], delimiter='\t')
                writer.writeheader()
                for base, line in [('state', 3), ('sprite', 3)]:
                    writer.writerow(dict(file='src/dungeon/update.c', function='update', line=line,
                                         macro='F', use=f'F({base}, 0)', base_expr=base,
                                         **{'class': 'base_untyped'}, reason='void'))
            out = root / 'out'
            counts, families = report(root, inventory, out)
            with (out / 'provenance_sites.tsv').open() as fh:
                sites = list(csv.DictReader(fh, delimiter='\t'))
            self.assertEqual(len(sites), 2)
            self.assertEqual(sites[0]['creator'], 'create@src/dungeon/creator.c')
            self.assertEqual(sites[0]['record_type'], 'Body')
            self.assertEqual(sites[0]['confidence'], 'installer+creator typed')
            self.assertIn('direct_call_codemap:create@src/dungeon/creator.c', sites[0]['reach_paths'])
            self.assertEqual(sites[0]['creator_candidates'], 'create@src/dungeon/creator.c')
            self.assertEqual(sites[1]['record_type'], '')
            self.assertEqual(sites[1]['confidence'], 'installer only')
            self.assertEqual(sum(counts.values()), 2)
            self.assertEqual(families, 1)

    def test_draw_registration_and_ambiguous_installers_are_not_typed(self):
        cb = Function('src/cb.c', 'update', 'void *state', '', 1)
        a = Function('src/a.c', 'create_a', '',
                     'ObjectNodeHeader *node = allocate_list_node(0x12, 0);\n'
                     'A *body; body = NODE_BODY(node); node->update_callback = update;', 1)
        b = Function('src/b.c', 'create_b', '',
                     'ObjectNodeHeader *node = allocate_list_node(0x12, 0);\n'
                     'B *body; body = NODE_BODY(node); node->update_callback = update;', 1)
        row = dict(file='src/cb.c', function='update', base_expr='state')
        ambiguous = classify(row, cb, [(a, 'callback_store', 3), (b, 'callback_store', 3)], {})
        self.assertEqual(ambiguous['confidence'], 'installer only')
        self.assertEqual(ambiguous['record_type'], '')
        draw = classify(row, cb, [(a, 'draw_registration', 3), (b, 'draw_registration', 3)], {})
        self.assertEqual(draw['confidence'], 'installer only')
        self.assertEqual(draw['creator'], '')

    def test_draw_alias_and_cast_body_are_linked(self):
        cb = Function('src/cb.c', 'draw', 'void *state', '', 1)
        creator = Function('src/creator.c', 'create', '', '''
          ObjectNodeHeader *node = allocate_list_node(0x211, head);
          Colored *body;
          void *handler;
          handler = draw;
          body = (Colored *)((u8 *)node + 0x20);
          register_node(node, handler);
        ''', 1)
        self.assertEqual(__import__('macro_base_provenance').body_types(creator), {'body': 'Colored'})
        result = classify(dict(file=cb.file, function=cb.name, base_expr='state'), cb,
                          [(creator, 'draw_registration_alias', 4)], {})
        self.assertEqual(result['confidence'], 'installer+creator typed')
        self.assertEqual(result['record_type'], 'Colored')

    def test_typed_callback_alone_does_not_type_creator(self):
        cb = Function('src/cb.c', 'update', 'Body *state', '', 1)
        creator = Function('src/create.c', 'create', '',
                           'node = allocate_list_node(0x12, head); node->update_callback = update;', 1)
        result = classify(dict(file=cb.file, function=cb.name, base_expr='state'), cb,
                          [(creator, 'callback_store', 2)], {})
        self.assertEqual(result['record_type'], 'Body')
        self.assertEqual(result['confidence'], 'installer only')


if __name__ == '__main__':
    unittest.main()
