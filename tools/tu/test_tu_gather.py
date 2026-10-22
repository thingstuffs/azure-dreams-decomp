import sys
from pathlib import Path
import unittest
import tempfile
from unittest.mock import patch

sys.path.insert(0, str(Path(__file__).resolve().parent))
import view_merge as V
import tu_merge as M


class GatherTests(unittest.TestCase):
    def tables(self):
        images = {}
        for name, start, size in [('parent', 0, 1000), ('child', 100, 100), ('remote', 300, 100)]:
            images['town/' + name] = dict(image='town/' + name, container='town', schema=V.L.SCHEMA,
                                         foff=start, size=size, vma=start + 1000, symbols={})
        entries = {}
        for rid, home, offset, image in [('h', 'h', 110, 'child'), ('x', 'x', 120, 'child'),
                                         ('hc', 'h', 310, 'remote'), ('xc', 'x', 320, 'remote')]:
            entries['town/' + rid] = dict(row='town/' + rid, home='town/' + home,
                foff=offset, vma=offset + 1000, size=4, bindings={}, image='town/' + image)
        local = { 'town/remote': {1110: [('town/child', 1310)], 1120: [('town/child', 1320)]}}
        return images, {}, entries, local

    def test_moved_home_preserves_both_kinds_of_remote_reference(self):
        with patch.object(V.L, 'load', return_value=self.tables()), \
                patch.object(V, 'home_symbols', return_value=[1110, 1120]) as symbols:
            result = V.preserve(Path('.'), {'town/h': 'town/parent'}, Path('.'))
        self.assertEqual(result['refused'], [])
        self.assertEqual(result['changed_homes'], ['town/h'])
        self.assertEqual(result['bindings']['town/hc']['0x00000460'], '0x00000528')
        self.assertEqual(result['bindings']['town/xc']['0x00000456'], '0x0000051E')
        self.assertIn('town/remote', result['touched'])
        self.assertEqual({call.args[1] for call in symbols.call_args_list}, {'town/h'})

    def test_invalid_load_or_extent_refuses_before_symbol_work(self):
        for change in [dict(vma=999), dict(size=100), dict(schema='v1'), dict(container='dungeon')]:
            tables = self.tables()
            tables[0]['town/parent'].update(change)
            with patch.object(V.L, 'load', return_value=tables), patch.object(V, 'home_symbols') as symbols:
                with self.assertRaisesRegex(ValueError, 'same-delta'):
                    V.preserve(Path('.'), {'town/h': 'town/parent'}, Path('.'))
                symbols.assert_not_called()

    def test_unknown_move_and_unresolved_plan_refuse_without_writes(self):
        with patch.object(V.L, 'load', return_value=self.tables()):
            with self.assertRaises(ValueError):
                V.preserve(Path('.'), {'town/missing': 'town/parent'}, Path('.'))
        with patch.object(V.L, 'files') as files:
            with self.assertRaisesRegex(ValueError, 'unresolved refusals'):
                V.apply(Path('.'), dict(moves={}, bindings={}, refused=['failed proof']))
            files.assert_not_called()

    def test_already_gathered_is_idempotent_and_needs_no_compiler(self):
        with patch.object(V.L, 'load', return_value=self.tables()), patch.object(V, 'home_symbols') as symbols:
            result = V.preserve(Path('.'), {'town/h': 'town/child'}, Path('.'))
        self.assertEqual(result['moves'], {})
        self.assertEqual(result['bindings'], {})
        symbols.assert_not_called()

    def test_nested_freezer_handles_keep_the_original_backup_and_absent_paths(self):
        with tempfile.TemporaryDirectory() as td:
            root = Path(td)
            (root / 'first').write_text('original first')
            (root / 'second').write_text('original second')
            outer = M.Freezer(root, root / 'base')
            outer.write('first', 'outer change')
            inner = M.Freezer(root, root / 'base')
            inner.write('second', 'inner change')
            inner.write('created', 'new file')
            outer.write('second', 'another outer change')
            self.assertEqual((root / 'base/files/second').read_text(), 'original second')
            self.assertIn('created', outer.patch())
            M.restore(root, root / 'base')
            self.assertEqual((root / 'first').read_text(), 'original first')
            self.assertEqual((root / 'second').read_text(), 'original second')
            self.assertFalse((root / 'created').exists())


if __name__ == '__main__':
    unittest.main()
