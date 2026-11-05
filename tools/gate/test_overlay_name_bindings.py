"""Module-local source names bind only the reviewed entry in that module."""
import unittest

from overlay_module_gate import bind_native_entries


class ModuleLocalNameTests(unittest.TestCase):
    def setUp(self):
        self.row_id = 'dungeon/func_81960CD4'
        self.module = {
            'members': [{'id': self.row_id, 'function': 'func_800264D4'}],
            'source_names': {self.row_id: 'update_rotating_fading_tile_quad'},
        }
        self.registry = {self.row_id: {
            'func': 'func_81960CD4', 'true_name': 'func_800264D4',
        }}

    def test_local_name_binds_entry_and_references(self):
        raw = b'.ent update_rotating_fading_tile_quad\njal update_rotating_fading_tile_quad\n.end update_rotating_fading_tile_quad\n'
        changed, bindings = bind_native_entries(self.module, raw, self.registry, {})
        self.assertEqual(bindings, {'update_rotating_fading_tile_quad': 'func_800264D4'})
        self.assertEqual(changed, b'.ent func_800264D4\njal func_800264D4\n.end func_800264D4\n')

    def test_wrong_entry_and_global_shadow_fail_closed(self):
        wrong = b'.ent create_linked_objects\n.end create_linked_objects\n'
        with self.assertRaisesRegex(ValueError, 'module-local source name differs'):
            bind_native_entries(self.module, wrong, self.registry, {})
        right = b'.ent update_rotating_fading_tile_quad\n.end update_rotating_fading_tile_quad\n'
        with self.assertRaisesRegex(ValueError, 'module-local source name differs'):
            bind_native_entries(self.module, right, self.registry,
                                {'update_rotating_fading_tile_quad': 'func_80024500'})


if __name__ == '__main__':
    unittest.main()
