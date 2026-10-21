"""T1 adapter: in-place inline (layout_apply) and the span-aware placement projection."""
import json
import os
from pathlib import Path
import sys
import tempfile
import unittest
from unittest.mock import patch

ROOT = Path(__file__).resolve().parents[2]
sys.path[:0] = [str(ROOT / 'tools'), str(ROOT / 'tools/gate')]
import guarded_package as P
import layout_apply as A
import source_layout as L
from gate import source_layout as GL

MEMBER = '#include "shared.h"\nint member(void) { return helper(); }\n'
SIBLING = '#include "shared.h"\nint sibling(void) { return 2; }\n'


class InPlaceInline(unittest.TestCase):
    def setUp(self):
        self.tmp = tempfile.TemporaryDirectory()
        self.addCleanup(self.tmp.cleanup)
        self.root = Path(self.tmp.name) / 'root'
        self.tree = Path(self.tmp.name) / 'tree.tsv'
        self.inline = Path(self.tmp.name) / 'inline.tsv'
        rows = [{'id': 'dungeon/func_80000000', 'container': 'dungeon', 'c_path': 'src/func_80000000.c'},
                {'id': 'dungeon/func_80000100', 'container': 'dungeon', 'c_path': 'src/func_80000100.c'},
                {'id': 'dungeon/func_80900000', 'container': 'dungeon', 'c_path': 'src/func_80900000.c',
                 'source_row': 'dungeon/func_80000000'}]
        self.write('ledger/rows.jsonl', ''.join(json.dumps(r) + '\n' for r in rows))
        self.write('src/dungeon/func_80000000.c', MEMBER)
        self.write('src/dungeon/func_80000100.c', SIBLING)
        self.write('include/shared.h', '#ifndef SHARED_H\n#define SHARED_H\nint helper(void);\n#endif\n')
        self.write('src/dungeon/level/owner.c', '#include "shared.h"\n/* entry table */\n'
                   'int (*const owner_entry)(void) = member;\n'
                   '#include "../func_80000000.c"\n#include "../func_80000100.c"\n')
        self.write('ledger/tu_layout.jsonl', json.dumps({'old': 'src/dungeon/modules/owner.c',
                                                        'new': 'src/dungeon/level/owner.c'}) + '\n')
        self.write('config/overlays/modules.json', json.dumps({'modules': [{
            'key': 'owner', 'container': 'dungeon', 'source': 'src/dungeon/level/owner.c',
            'members': [{'id': 'dungeon/func_80000000', 'source': 'src/dungeon/func_80000000.c',
                         'foff': 0, 'size': 4},
                        {'id': 'dungeon/func_80000100', 'source': 'src/dungeon/func_80000100.c',
                         'foff': 0x100, 'size': 4}]}]}) + '\n')
        self.tree.write_text('current_path\tproposed_path\nsrc/dungeon/level/owner.c\tsrc/dungeon/level/owner.c\n')
        self.inline.write_text(
            'tu_current\tinclude_line\tinclude_token\tmember_source\tmember_id\tmanifest_key\tmember_order\t'
            'condition_depth\thold\n'
            'src/dungeon/level/owner.c\t4\t../func_80000000.c\tsrc/dungeon/func_80000000.c\t'
            'dungeon/func_80000000\towner\t1\t0\t\n'
            'src/dungeon/level/owner.c\t5\t../func_80000100.c\tsrc/dungeon/func_80000100.c\t'
            'dungeon/func_80000100\towner\t2\t0\t\n')

    def write(self, rel, content):
        p = self.root / rel
        p.parent.mkdir(parents=True, exist_ok=True)
        p.write_text(content)

    def apply(self):
        changes, report = A.plan(self.root, self.tree, inline=self.inline)
        package = Path(self.tmp.name) / 'package'
        P.export(package, self.root, changes)
        P.apply(package, self.root, live=True)
        return report

    def test_in_place_inline_keeps_path_and_history(self):
        self.assertIsNone(GL.member_projection('dungeon/func_80000000', self.root))
        report = self.apply()
        self.assertEqual(report['moves'], {'src/dungeon/level/owner.c': 'src/dungeon/level/owner.c'})
        self.assertEqual(report['inline_members'], 2)
        owner = (self.root / 'src/dungeon/level/owner.c').read_text()
        self.assertIn('int member(void)', owner)
        self.assertIn('int sibling(void)', owner)
        self.assertFalse((self.root / 'src/dungeon/func_80000000.c').exists())
        # No identity record joins the existing TU history (it would collide with old -> new).
        self.assertEqual((self.root / 'ledger/tu_layout.jsonl').read_text().strip(),
                         json.dumps({'old': 'src/dungeon/modules/owner.c', 'new': 'src/dungeon/level/owner.c'},
                                    separators=(',', ':')))
        self.assertEqual(L.row_relative('dungeon/func_80900000', self.root), 'src/dungeon/level/owner.c')
        self.assertEqual(len(L.inline_records(self.root)), 2)
        modules = json.loads((self.root / 'config/overlays/modules.json').read_text())
        self.assertEqual({m['source'] for m in modules['modules'][0]['members']}, {'src/dungeon/level/owner.c'})
        # Re-planning an applied in-place inline is a no-op, not a second inline.
        changes, again = A.plan(self.root, self.tree, inline=self.inline)
        self.assertEqual((changes, again['moves']), ({}, {}))

    def test_projection_is_prefix_includes_plus_own_span(self):
        self.apply()
        unit = GL.member_projection('dungeon/func_80000000', self.root).decode()
        self.assertEqual(unit, '#include "shared.h"\n' + MEMBER)
        self.assertNotIn('sibling', unit)
        self.assertNotIn('owner_entry', unit)
        sibling = GL.member_projection('dungeon/func_80000100', self.root).decode()
        self.assertEqual(sibling, '#include "shared.h"\n' + SIBLING)
        # The facade re-exports the gate implementation (the gate imports either name).
        self.assertIs(L.member_projection, GL.member_projection)
        # A placement row is not itself an inlined member.
        self.assertIsNone(GL.member_projection('dungeon/func_80900000', self.root))

    def test_projection_fails_closed(self):
        self.apply()
        owner = self.root / 'src/dungeon/level/owner.c'
        good = owner.read_text()
        owner.write_text(good.replace('return 2;', 'return 3;'))
        with self.assertRaisesRegex(ValueError, 'source_sha256 mismatch'):
            GL.member_projection('dungeon/func_80000100', self.root)
        owner.write_text('#define X 1\n' + good)
        records = [json.loads(x) for x in (self.root / 'ledger/layout_inline.jsonl').read_text().splitlines()]
        shifted = [dict(r, offset=r['offset'] + len('#define X 1\n')) for r in records]
        (self.root / 'ledger/layout_inline.jsonl').write_text(''.join(json.dumps(r) + '\n' for r in shifted))
        with self.assertRaisesRegex(ValueError, 'prefix directive needs review'):
            GL.member_projection('dungeon/func_80000000', self.root)
        owner.write_text(good)
        (self.root / 'ledger/layout_inline.jsonl').write_text(''.join(json.dumps(r) + '\n' for r in records))
        self.write('src/dungeon/level/shared.h', '/* would shadow include/shared.h next to the owner */\n')
        with self.assertRaisesRegex(ValueError, 'owner-relative include'):
            GL.member_projection('dungeon/func_80000000', self.root)

    def test_cached_provenance_detects_duplicate_with_restored_mtime(self):
        self.apply()
        rid = 'dungeon/func_80000000'
        GL.member_projection(rid, self.root)
        ledger = self.root/'ledger/layout_inline.jsonl'
        data, st = ledger.read_bytes(), ledger.stat()
        ledger.write_bytes(data + data.splitlines(keepends=True)[0])
        os.utime(ledger, ns=(st.st_atime_ns, st.st_mtime_ns))
        with self.assertRaisesRegex(ValueError, 'duplicate inline provenance'):
            GL.member_projection(rid, self.root)

    def test_provenance_reuse_still_checks_current_owner_bytes(self):
        self.apply()
        rid = 'dungeon/func_80000000'
        good = GL.member_projection(rid, self.root)
        with patch.object(GL.json, 'loads', wraps=json.loads) as loads:
            self.assertEqual(GL.member_projection(rid, self.root), good)
            self.assertEqual(loads.call_count, 0)
        owner = self.root/'src/dungeon/level/owner.c'
        st = owner.stat()
        owner.write_text(owner.read_text().replace('return helper();', 'return danger();'))
        os.utime(owner, ns=(st.st_atime_ns, st.st_mtime_ns))
        with self.assertRaisesRegex(ValueError, 'source_sha256 mismatch'):
            GL.member_projection(rid, self.root)


    def test_row_source_module_copy_supersedes_row_file(self):
        """Decision 70: the module copy is inlined; the row's own file is retired with it."""
        self.write('src/dungeon/copies/func_80000000.c', MEMBER.replace('helper()', 'helper() /* module copy */'))
        self.write('src/dungeon/level/owner.c', (self.root / 'src/dungeon/level/owner.c').read_text()
                   .replace('../func_80000000.c', '../copies/func_80000000.c'))
        self.inline.write_text(self.inline.read_text()
                               .replace('condition_depth\thold\n', 'condition_depth\thold\trow_source\n')
                               .replace('\t../func_80000000.c\tsrc/dungeon/func_80000000.c\t',
                                        '\t../copies/func_80000000.c\tsrc/dungeon/copies/func_80000000.c\t')
                               .replace('owner\t1\t0\t\n', 'owner\t1\t0\t\tsrc/dungeon/func_80000000.c\n')
                               .replace('owner\t2\t0\t\n', 'owner\t2\t0\t\t\n'))
        changes, report = A.plan(self.root, self.tree, inline=self.inline)
        self.assertIsNone(changes['src/dungeon/func_80000000.c'])
        self.assertIsNone(changes['src/dungeon/copies/func_80000000.c'])
        self.assertIn(b'module copy', changes['src/dungeon/level/owner.c'])
        self.assertIn(b'src/dungeon/level/owner.c', changes['config/overlays/modules.json'])
        self.assertNotIn(b'src/dungeon/func_80000000.c', changes['config/overlays/modules.json'])
        bad = Path(self.tmp.name) / 'bad.tsv'
        bad.write_text(self.inline.read_text().replace('\tsrc/dungeon/func_80000000.c\n', '\tsrc/dungeon/func_80000200.c\n'))
        with self.assertRaisesRegex(ValueError, 'inline row identity differs'):
            A.plan(self.root, self.tree, inline=bad)


class GateHook(unittest.TestCase):
    """compile_c_segments compiles the projection, and self-serves evidence from its text only."""

    def test_placement_compiles_projection_text(self):
        import overlay_local_gate as G
        tmp = tempfile.TemporaryDirectory()
        self.addCleanup(tmp.cleanup)
        d = Path(tmp.name)
        whole = d / 'func_80900000.c'
        whole.write_text('void f(void) __attribute__((noreturn));\nint sibling(void) { f(); }\n')
        match = G.MatchEntry(start=0x100, size=4, func='func_80900000', source=whole,
                             config='2.7.2', source_group='test', link_vram=None)
        seg = G.Segment(index=0, kind='c', start=0x100, end=0x104, vram=0x80900000,
                        section='.text.func_80900000', name='func_80900000', match=match)
        place = {'row': 'main/func_80900000', 'home': 'main/func_80000000', 'size': 4}
        calls, seen = [], []
        with patch('linklist.placement', return_value=place), \
                patch('linklist.rebind_object', return_value={}), \
                patch('source_layout.member_projection', return_value=b'int member(void) { return 1; }\n'), \
                patch.object(G, 'run', side_effect=lambda argv, env=None: calls.append(argv)), \
                patch.object(G, 'default_as_flags', return_value=''), \
                patch.object(G, 'config_to_flags', return_value=('2.7.2', '')), \
                patch.object(G, 'candidate_noreturn_syms', side_effect=lambda t: seen.append(t) or set()):
            G.compile_c_segments([seg], d / 'obj', overlay='main_test')
        compiled = Path(calls[0][1])
        self.assertEqual(compiled, d / 'obj/func_80900000.member/func_80000000.c')
        self.assertEqual(compiled.read_bytes(), b'int member(void) { return 1; }\n')
        self.assertEqual(seen, ['int member(void) { return 1; }\n'])
        calls.clear(); seen.clear()
        with patch('linklist.placement', return_value=place), \
                patch('linklist.rebind_object', return_value={}), \
                patch('source_layout.member_projection', return_value=None), \
                patch.object(G, 'run', side_effect=lambda argv, env=None: calls.append(argv)), \
                patch.object(G, 'default_as_flags', return_value=''), \
                patch.object(G, 'config_to_flags', return_value=('2.7.2', '')), \
                patch.object(G, 'candidate_noreturn_syms', side_effect=lambda t: seen.append(t) or set()):
            G.compile_c_segments([seg], d / 'obj2', overlay='main_test')
        # No inline record: the legacy source and text, unchanged.
        self.assertEqual(Path(calls[0][1]), whole)
        self.assertEqual(seen, [whole.read_text()])


if __name__ == '__main__':
    unittest.main()
