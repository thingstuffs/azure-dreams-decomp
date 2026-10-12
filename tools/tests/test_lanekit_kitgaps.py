"""Permutation dependency/safety controls and native physical-context controls."""
import json
import struct
import sys
import tempfile
import unittest
from concurrent.futures import ThreadPoolExecutor
from pathlib import Path
from types import SimpleNamespace
from unittest.mock import patch

ROOT = next(p for p in Path(__file__).resolve().parents if (p / 'tools/common.py').is_file())
sys.path.insert(0, str(ROOT / 'tools/lanes/lanekit'))
import kitlib
import native_member as N
import permute as P


class PermutationTests(unittest.TestCase):
    def items(self, body):
        return P.parse_statements('void f(void) {\n' + body + '\n}')

    def test_raw_war_and_waw(self):
        items = self.items('x = 1; y = x; x = 2;')
        self.assertEqual(P.dependency_edges(items), {(0, 1), (0, 2), (1, 2)})
        self.assertEqual(list(P.orders(3, P.dependency_edges(items))), [(0, 1, 2)])

    def test_pointer_assignment_precedes_member_access(self):
        items = self.items('p = q; p->a = 1; p->b = 2;')
        self.assertEqual(set(P.orders(3, P.dependency_edges(items))), {(0, 1, 2), (0, 2, 1)})

    def test_same_field_aliases_other_base(self):
        items = self.items('p->a = 1; q->a = 2; p->b = 3;')
        self.assertIn((0, 1), P.dependency_edges(items))
        self.assertNotIn((0, 2), P.dependency_edges(items))

    def test_rmw_chain_and_sibling_store(self):
        items = self.items('p->a |= 1; p->a |= 2; p->b |= 4;')
        self.assertEqual(len(list(P.orders(3, P.dependency_edges(items)))), 3)

    def test_call_declaration_and_dereference_barriers(self):
        for fixed in ['g();', 'int x = 0;', '*p = 0;', 'x = *p;', 'x = a[i];', 'return x;', 'x = ++y;', 'x = (y = 2);']:
            with self.subTest(fixed=fixed):
                self.assertIsNone(P.effects(fixed))
                items = self.items('a = 1; ' + fixed + ' b = 2;')
                self.assertEqual(list(P.orders(3, P.dependency_edges(items))), [(0, 1, 2)])

    def test_declared_reverse_edge(self):
        items = self.items('a = 1; b = 2;')
        self.assertEqual(list(P.orders(2, P.dependency_edges(items, [(1, 0)]))), [(1, 0)])

    def test_cyclic_and_bad_dependencies_fail(self):
        items = self.items('a = 1; b = a;')
        for edges in [[(1, 0)], [(0, 2)], [(0, 0)], [('0', 1)]]:
            with self.assertRaises(ValueError):
                P.dependency_edges(items, edges)

    def test_comments_strings_and_for_header(self):
        text = 'void f() { for(i=0;i<2;i++) { a = 1; /* ;{} */ b = 2; } g(";{}"); }'
        items = P.parse_statements(text)
        self.assertEqual(len(items), 3)
        self.assertEqual(items[0].block, items[1].block)
        self.assertNotEqual(items[1].block, items[2].block)
        self.assertIn('/* ;{} */', items[1].text)

    def test_group_must_be_adjacent_and_same_block(self):
        for text in ['void f() { a=1; c=3; b=2; }', 'void f() { a=1; { b=2; } }']:
            with self.assertRaises(ValueError):
                P.select_groups(text, [{'statements': ['a=1;', 'b=2;']}])

    def test_ambiguous_and_overlapping_groups_fail(self):
        text = 'void f() { a=1; b=2; a=1; }'
        with self.assertRaises(ValueError):
            P.select_groups(text, [{'statements': ['a=1;', 'b=2;']}])
        text = 'void f() { a=1; b=2; }'
        group = {'statements': ['a=1;', 'b=2;']}
        with self.assertRaises(ValueError):
            P.select_groups(text, [group, group])

    def test_line_ranges_and_whole_statements(self):
        text = 'void f() {\n a=1;\n b=2;\n}\n'
        groups = P.select_groups(text, [{'lines': [[2, 2], [3, 3]]}])
        self.assertEqual(len(list(P.variants(text, groups, 10))), 2)
        with self.assertRaises(ValueError):
            P.select_groups(text, [{'lines': [[2, 3], [3, 3]]}])

    def test_lazy_cap_multiple_groups(self):
        text = 'void f() { a=1; b=2; { c=3; d=4; } }'
        groups = P.select_groups(text)
        results = list(P.variants(text, groups, 3))
        self.assertEqual(len(results), 3)
        self.assertEqual(results[0][0], text)
        self.assertEqual(len({t for t, _ in results}), 3)

    def test_automatic_parser_holds_control_flow(self):
        text = 'void f() { a=1; b=2; if (a) b=3; c=4; d=5; }'
        self.assertEqual([len(items) for items, _ in P.select_groups(text)], [2, 2])

    def test_compound_direct_and_split(self):
        self.assertEqual(P.compound_rewrite('void f(){p->a = p->a | 4;}'), 'void f(){p->a |= 4;}')
        t = 'typedef struct { u16 a; u16 b; } T;\nvoid f(){\n u16 tmp;\n tmp = p->a;\n p->b = 2;\n p->a = tmp | 4;\n}'
        out = P.compound_rewrite(t)
        self.assertNotIn('tmp', out)
        self.assertIn('p->a |= 4;', out)

    def test_compound_rewrite_refuses_surviving_use_or_alias_write(self):
        for middle in ['q = tmp;', 'g();', 'p->a = 3;', 'p = q;']:
            t = 'typedef struct { u16 a; u16 b; } T;\nvoid f(){\n u16 tmp;\n tmp = p->a;\n ' + middle + '\n p->a = tmp | 4;\n}'
            self.assertEqual(P.compound_rewrite(t), t)

    def test_compound_refuses_type_truncation(self):
        text = 'typedef struct { u32 a; } T; void f(){u16 tmp; tmp=p->a; p->a=tmp | 4;}'
        self.assertEqual(P.compound_rewrite(text), text)

    def test_compound_resolves_field_type_in_pointer_struct(self):
        text = 'typedef struct A {u16 flags;} A; typedef struct B {u32 flags;} B;\nvoid f(){\n A *p;\n u16 tmp;\n tmp=p->flags;\n p->flags=tmp | 4;\n}'
        out = P.compound_rewrite(text)
        self.assertIn('p->flags |= 4;', out)
        self.assertNotIn('tmp', out)

    def test_preprocessor_boundary_is_fixed(self):
        text = 'void f(){\n a=1;\n#if FLAG\n b=2;\n#endif\n}'
        self.assertEqual(P.select_groups(text), [])
        with self.assertRaises(ValueError):
            P.select_groups(text, [{'statements': ['a=1;', 'b=2;']}])

    def test_bounded_pool_order(self):
        with ThreadPoolExecutor(max_workers=2) as pool:
            self.assertEqual(list(P.bounded_map(pool, lambda i: i * i, range(10), 4)), [i * i for i in range(10)])


class NativeTests(unittest.TestCase):
    def test_relocated_tu_preserves_order_and_substitutes_once(self):
        with tempfile.TemporaryDirectory() as td:
            root = Path(td); (root / 'src/modules').mkdir(parents=True)
            (root / 'src/a.c').write_text('a'); (root / 'src/b.c').write_text('b')
            (root / 'src/modules/m.c').write_text('#include "contract.h"\n#include "../a.c"\n#include "../b.c"\n')
            with patch.object(kitlib, 'ROOT', root):
                text = N.source_text({'source': 'src/modules/m.c'}, 'src/a.c', root / 'candidate.c')
            self.assertLess(text.index('candidate.c'), text.index('b.c'))
            self.assertIn('#include "contract.h"', text)
            self.assertIn(str(root / 'src/b.c'), text)

    def test_missing_duplicate_and_escaping_include_fail(self):
        with tempfile.TemporaryDirectory() as td:
            root = Path(td); (root / 'src').mkdir(); (root / 'a.c').write_text('a')
            m = {'source': 'src/m.c'}
            for text in ['#include "x.h"', '#include "../a.c"\n#include "../a.c"']:
                (root / 'src/m.c').write_text(text)
                with patch.object(kitlib, 'ROOT', root), self.assertRaises(ValueError):
                    N.source_text(m, 'a.c', root / 'candidate.c')

    def test_unlisted_overlay_is_ordinary(self):
        with tempfile.TemporaryDirectory() as td:
            root = Path(td); (root / 'config/overlays').mkdir(parents=True)
            (root / 'config/overlays/modules.json').write_text('{"modules": []}')
            with patch.object(kitlib, 'ROOT', root):
                self.assertIsNone(N.membership({'id': 'dungeon/x', 'kind': 'overlay'}))

    def test_module_cfg_trial_fails_closed(self):
        with patch.object(N, 'membership', return_value={'key': 'm'}), self.assertRaises(SystemExit):
            kitlib.row_at_cfg({'id': 'dungeon/x', 'kind': 'overlay', 'cfg': '2.7.2-cdk-G0'}, '2.8.1-G0')

    def test_native_nojtbl_refused(self):
        with patch.object(N, 'membership', return_value={'key': 'm'}), self.assertRaises(ValueError):
            kitlib.score_at({'id': 'dungeon/x', 'kind': 'overlay', 'cfg': '2.7.2-cdk-G0'}, 'x', no_jtbl=True)

    def test_kit_screen_and_score_dispatch(self):
        row = {'id': 'dungeon/x', 'kind': 'overlay', 'cfg': '2.7.2-cdk-G0'}
        with patch.object(N, 'membership', return_value={'key': 'm'}), patch.object(N, 'Screen', return_value='native'), patch.object(N, 'score', return_value={'exact': True}):
            self.assertEqual(kitlib.screen_for(row, 'x'), 'native')
            self.assertTrue(kitlib.score_at(row, 'x')['exact'])

    def test_durable_score_fields_keep_collateral(self):
        score = {'exact': False, 'module': 'm', 'member_exact': True, 'other_members_changed': [{'id': 'b'}], 'owned_data_exact': False, 'artifacts': 'tmp/score'}
        self.assertEqual(kitlib.score_fields(score)['other_members_changed'], [{'id': 'b'}])
        self.assertFalse(kitlib.score_fields(score)['owned_data_exact'])

    def test_stale_screen_refused(self):
        screen = object.__new__(N.Screen); screen.row = {}; screen.context_fingerprint = 'before'
        with patch.object(N, 'fingerprint', return_value='after'), self.assertRaises(RuntimeError):
            screen._fresh()

    def score_fixture(self, change=False, shift=False, fail=False, mutate=False):
        with tempfile.TemporaryDirectory() as td:
            root = Path(td); (root / 'tmp').mkdir(); (root / 'work/disc/containers').mkdir(parents=True)
            retail = struct.pack('<3I', 0x80024004, 0x11223344, 0x55667788)
            (root / 'work/disc/containers/test.bin').write_bytes(retail)
            m = {'key': 'test', 'container': 'dungeon', 'owned_data': [{'size': 4}], 'members': [
                {'id': 'a', 'function': 'a', 'foff': 0, 'vma': 0x80024000, 'size': 8, 'body_offset': 4},
                {'id': 'b', 'function': 'b', 'foff': 8, 'vma': 0x80024008, 'size': 4}]}
            data = retail[:8] + (struct.pack('<I', 0xDEADBEEF) if change else retail[8:])
            g = SimpleNamespace(CONTAINERS={'dungeon': 'test.bin'}, module_first=lambda m: m['members'][0], all_members=lambda m: m['members'])
            # Metric mock preserves byte equality; the actual scorer is exercised by real proofs.
            def stats(a, b):
                return {'exact': a == b, 'total': 0 if a == b else 1, 'subs': int(a != b), 'indels': 0}
            fp = ['base', 'changed'] if mutate else ['base', 'base']
            with patch.object(kitlib, 'ROOT', root), patch.object(kitlib, 'bootstrap', return_value=root), patch.object(N, 'gate', return_value=g), patch.object(N, 'fingerprint', side_effect=fp), patch.object(N, 'byte_stats', side_effect=stats), patch.object(N, 'compile_object', side_effect=ValueError('compile control') if fail else None, return_value=(data, {'a': (0x80024004, 4), 'b': (0x8002400C if shift else 0x80024008, 4)}, None)):
                rec = N.score({'id': 'a'}, 'candidate', m)
                self.assertTrue((Path(rec['artifacts']) / 'score.json').is_file())
                return rec

    def test_prefix_in_selected_span(self):
        rec = self.score_fixture()
        self.assertTrue(rec['exact'])
        self.assertTrue(rec['owned_data_exact'])
        self.assertEqual(rec['other_members_changed'], [])

    def test_sibling_change_prevents_stageable_exact(self):
        rec = self.score_fixture(change=True)
        self.assertTrue(rec['member_exact'])
        self.assertFalse(rec['exact'])
        self.assertEqual(rec['status'], 'native-collateral-change')
        self.assertEqual(rec['other_members_changed'][0]['id'], 'b')

    def test_natural_layout_shift_is_reported(self):
        self.assertFalse(self.score_fixture(shift=True)['exact'])

    def test_compile_failure_keeps_receipt(self):
        self.assertEqual(self.score_fixture(fail=True)['status'], 'native-build-failed')

    def test_mutated_context_discards_score(self):
        with self.assertRaises(RuntimeError):
            self.score_fixture(mutate=True)


if __name__ == '__main__':
    unittest.main()
