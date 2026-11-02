"""address_respell.py / dead_externs.py on small fixtures (no compiler)."""
import sys
from pathlib import Path
import unittest
sys.path.insert(0, str(Path(__file__).resolve().parent))
import address_respell as AR
import dead_externs as DE
import rebase_placeholder_rows as RB


class Respell(unittest.TestCase):
    def test_rename_keeps_local_declaration_when_nothing_visible(self):
        text = ('#include "common.h"\n'
                'extern void D_80092320();\n'
                'void f(Record *record) {\n'
                '    record->callback = &D_80092320;\n'
                '}\n')
        out, action = AR.respell_text(text, 'D_80092320', 'update_actor_movement_actions', False)
        self.assertEqual(action, 'rename')
        self.assertIn('extern void update_actor_movement_actions();\n', out)
        self.assertIn('&update_actor_movement_actions;', out)
        self.assertNotIn('D_80092320', out)

    def test_delete_when_header_declares_it(self):
        text = 'extern void D_800A7548();\nvoid g(T *d) {\n    d->f = &D_800A7548;\n}\n'
        out, action = AR.respell_text(text, 'D_800A7548', 'update_effect_bounce_and_fade', True)
        self.assertEqual(action, 'delete_decl')
        self.assertEqual(out, 'void g(T *d) {\n    d->f = &update_effect_bounce_and_fade;\n}\n')

    def test_data_shaped_declaration_becomes_a_function(self):
        text = 'extern u8 D_800C27F0[];\nvoid h(void) { use(&D_800C27F0); }\n'
        out, action = AR.respell_text(text, 'D_800C27F0', 'create_and_store_pending_actor_fade', False)
        self.assertEqual(action, 'data_decl_as_function')
        self.assertTrue(out.startswith('extern void create_and_store_pending_actor_fade();\n'))

    def test_function_pointer_variable_is_not_a_declaration_of_the_name(self):
        text = 'void (*hook)(void) = D_80091AF0;\nextern void D_80091AF0(void);\n'
        out, action = AR.respell_text(text, 'D_80091AF0', 'tick', False)
        self.assertEqual(out, 'void (*hook)(void) = tick;\nextern void tick(void);\n')

    def test_mapping_takes_only_canonical_c_same_rows(self):
        import tempfile
        with tempfile.NamedTemporaryFile('w', suffix='.tsv', delete=False) as fh:
            fh.write('name\tgroup\tclass\tcallers\tdetail\n'
                     'D_80092320\tnever_called\tC_SAME\t\ttown/engine func_80092320 -> update_actor_movement_actions rows x\n'
                     'D_80098104\tnever_called\tC_COPY\t\ttown/engine func_80097EC0 -> tick_countdown rows y\n'
                     'func_8003fc64\tbound_other\tC_SAME\t\tslus func_8003FC64 -> allocate_flagged_object_node\n')
        self.assertEqual(AR.mapping(fh.name), {'D_80092320': 'update_actor_movement_actions',
                                               'func_8003fc64': 'allocate_flagged_object_node'})


class Holds(unittest.TestCase):
    class FakeDB:
        def __init__(self, ret):
            self.ret = ret

        def execute(self, sql, args=()):
            class R:
                def __init__(self, row):
                    self.row = row

                def fetchone(self):
                    return self.row
            return R((self.ret,) if 'ret' in sql else None)

    def test_return_conflict(self):
        void_db = self.FakeDB('void')
        self.assertTrue(AR.return_conflict(void_db, 'extern s32 func_804075A8(s32 context);\n', 'func_804075A8', 'x'))
        self.assertFalse(AR.return_conflict(void_db, 'extern void func_804075A8(s32 context);\n', 'func_804075A8', 'x'))
        self.assertFalse(AR.return_conflict(self.FakeDB('s32'), 'extern s32 func_804075A8(s32);\n', 'func_804075A8', 'x'))

    def test_delete_held_when_an_include_follows(self):
        text = 'extern void D_800A7CC4();\n#include "dungeon/effect.h"\nvoid f(T *t) { t->cb = &D_800A7CC4; }\n'
        self.assertEqual(AR.respell_text(text, 'D_800A7CC4', 'render_floor_items', True), (text, None))

    def test_placeholder_detail_parsing(self):
        import tempfile
        with tempfile.NamedTemporaryFile('w', suffix='.tsv', delete=False) as fh:
            fh.write('name\tgroup\tclass\tcallers\tdetail\n'
                     'func_80400908\tunresolved\tC_PLACEHOLDER\tmain/func_8001A9B4\tfunc_80019908 linked at 0x80019908 '
                     '(row main/func_80019908, canonical reset_card_selection_state); true address 0x80400908 in region '
                     '0x269000@0x80400000\n'
                     'func_80065320\tbound_other\tLIB\t\tRotTransSV (asm/psyq/libgte/SMP_01_1.o)\n')
        self.assertEqual(RB.placeholders(fh.name), [dict(name='func_80400908', symbol='func_80019908',
                                                        row='main/func_80019908',
                                                        canonical='reset_card_selection_state', true=0x80400908)])


class DeadExterns(unittest.TestCase):
    def test_only_unused_single_line_declarations(self):
        text = ('extern s32 D_80010234;\n'               # dead object
                'extern u8 used_table[];\n'
                'void unused_proto(void *work);                /* extern */\n'   # dead prototype
                'u8 tentative[4];\n'                     # tentative definition: never touched
                'static void helper(void);\n'            # static prototype: never touched
                'extern void mentioned(void);\n'         # kept: a comment mentions it
                '/* mentioned() is called by the loader */\n'
                'void f(void) { used_table[0] = 1; }\n')
        hits = [name for _, _, name in DE.dead_in(text)]
        self.assertEqual(hits, ['D_80010234', 'unused_proto'])

    def test_names_filter(self):
        text = 'extern s32 a_dead;\nextern s32 b_dead;\n'
        self.assertEqual([n for _, _, n in DE.dead_in(text, {'b_dead'})], ['b_dead'])


if __name__ == '__main__':
    unittest.main()
