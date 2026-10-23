"""Native entry names must bind to registered homes without C relocation text."""
import importlib.util
import json
from pathlib import Path
import sys
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[2]
sys.path[:0] = [str(ROOT / 'tools'), str(ROOT / 'tools/gate'), str(ROOT / 'tools/build')]
import overlay_module_gate as G
import name_inputs as N


class NativeEntryNames(unittest.TestCase):
    def setUp(self):
        self.members = dict(members=[
            dict(id='town/func_80500000', function='func_80016000'),
            dict(id='town/func_80500020', function='func_80016020')])
        self.registry = {a['id']: dict(func=a['id'].split('/')[1], true_name=a['function'])
                         for a in self.members['members']}
        self.names = dict(first='func_80500000', second='func_80500020', external='func_80040000')
        self.raw = (b'.ent first\nfirst:\n jal second\n jal external\n.end first\n'
                    b'.ent second\nsecond:\n jr $ra\n.end second\n'
                    b'.ascii "first second external"\n.word first\n')

    def test_registered_entries_and_references_only(self):
        cooked, aliases = G.bind_native_entries(self.members, self.raw, self.registry, self.names)
        self.assertEqual(aliases, dict(first='func_80016000', second='func_80016020'))
        self.assertIn(b'jal func_80016020\n jal external', cooked)
        self.assertIn(b'.ascii "first second external"', cooked)
        self.assertIn(b'.word func_80016000', cooked)
        self.assertIn(b'jr $ra', cooked)
        self.assertNotIn(b'.ent first', cooked)

    def test_already_canonical_stream_is_unchanged(self):
        raw = self.raw.replace(b'first', b'func_80016000').replace(b'second', b'func_80016020')
        self.assertEqual(G.bind_native_entries(self.members, raw, self.registry, self.names), (raw, {}))

    def test_existing_global_entry_binding_is_unchanged(self):
        names = dict(self.names, first='func_80016000', second='func_80016020')
        self.assertEqual(G.bind_native_entries(self.members, self.raw, self.registry, names), (self.raw, {}))

    def test_wrong_order_or_unknown_entry_is_refused(self):
        for raw in [self.raw.replace(b'.ent first', b'.ent second', 1),
                    self.raw.replace(b'.ent first', b'.ent unknown', 1),
                    self.raw + b'.ent helper\nhelper:\n.end helper\n']:
            with self.subTest(raw=raw):
                with self.assertRaises(ValueError):
                    G.bind_native_entries(self.members, raw, self.registry, self.names)

    def test_raw_identity_and_canonical_target_overlap_is_simultaneous(self):
        self.registry['town/func_80500020']['func'] = 'func_80016000'
        self.names['second'] = 'func_80016000'
        cooked, _ = G.bind_native_entries(self.members, self.raw, self.registry, self.names)
        self.assertIn(b'.ent func_80016000', cooked)
        self.assertIn(b'.ent func_80016020', cooked)

    def test_ambiguous_target_is_refused(self):
        self.names['func_80016000'] = 'func_80040000'
        with self.assertRaises(ValueError):
            G.bind_native_entries(self.members, self.raw, self.registry, self.names)

    def test_original_name_dependencies_survive_binding(self):
        (ROOT / 'tmp').mkdir(exist_ok=True)
        with tempfile.TemporaryDirectory(prefix='native-entry-', dir=ROOT / 'tmp') as td:
            root = Path(td)
            trace = root / 'trace.json'
            (root / 'config').mkdir()
            cfg = 'config/sibcall_syms.town.txt'
            (root / cfg).write_text('func_80500000\nfunc_80016000\n')
            cooked, aliases = G.bind_native_entries(self.members, self.raw, self.registry, self.names)
            N.write(trace, N.witness(cooked.decode().splitlines(True), self.names,
                                   N.evidence_at(root, [cfg]), sections=False))
            G.retain_native_name_lookups(dict(CCPROC_NAMES_TRACE=str(trace), CCPROC_CONFIG_ROOT=str(root)),
                                        aliases, self.names, N)
            value = N.verify(trace, self.names, root)
            self.assertEqual(value['rows']['first'], 'func_80500000')
            changed = dict(self.names, first='func_80500100')
            with self.assertRaisesRegex(ValueError, 'stale name-input'):
                N.verify(trace, changed, root)


if __name__ == '__main__':
    unittest.main()
