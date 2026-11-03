"""Runtime identities and layout votes; run with python3 -m unittest."""
import collections
import csv
import gzip
import json
from pathlib import Path
import shutil
import sys
import tempfile
import unittest
from unittest import mock

HERE = Path(__file__).resolve().parent
sys.path[:0] = [str(HERE), str(HERE.parent)]
import cast_ast as ast
import type_flow as flow
import type_flow_solve as solve


class RuntimeFixture(unittest.TestCase):
    def setUp(self):
        scratch = HERE.parents[1] / 'tmp'
        scratch.mkdir(exist_ok=True)
        self.tmp = tempfile.TemporaryDirectory(dir=scratch)
        self.addCleanup(self.tmp.cleanup)
        self.root = Path(self.tmp.name)
        (self.root / 'include').mkdir()
        (self.root / 'src').mkdir()
        self.graph_dir = self.root / 'graph'
        (self.graph_dir / 'tu').mkdir(parents=True)
        self.rt_dir = self.root / 'rt'
        self.rt_dir.mkdir()
        self.rows = []
        self.sites = []
        self.kinds = []

    def unit(self, file, source, header=''):
        (self.root / 'include/flow.h').write_text(header)
        (self.root / file).write_text(source)
        unit, error = ast.clang_unit(self.root, file)
        self.assertIsNotNone(unit, error)
        data = flow.Extract(unit).run().dump()
        with gzip.open(self.graph_dir / 'tu' / (Path(file).stem + '.json.gz'), 'wt') as stream:
            json.dump(data, stream)
        return data

    def runtime(self, graph):
        with (self.rt_dir / 'fn_args.tsv').open('w') as stream:
            writer = csv.writer(stream, delimiter='\t', lineterminator='\n')
            writer.writerow(['file', 'function', 'arg', 'values'])
            writer.writerows(self.rows)
        (self.rt_dir / 'kinds_rt.json').write_text(json.dumps({'kinds': self.kinds}))
        if self.sites:
            with gzip.open(self.rt_dir / 'callsite_args.tsv.gz', 'wt') as stream:
                writer = csv.writer(stream, delimiter='\t', lineterminator='\n')
                writer.writerow(['callee_file', 'callee', 'arg', 'caller_file', 'caller', 'line', 'cells'])
                writer.writerows(self.sites)
        return solve.Runtime(self.rt_dir, graph)


@unittest.skipUnless(shutil.which('clang'), 'clang not installed')
class FunctionIdentityTests(RuntimeFixture):
    def same_name_case(self, static):
        header = 'typedef struct A { int a; } A; typedef struct B { int b; } B;\n'
        for label, record in (('a', 'A'), ('b', 'B')):
            file = 'src/' + label + '.c'
            source = '#include "flow.h"\n' + static + 'void same(' + record + ' *p) {}\n'
            source += 'void caller_' + label + '(' + record + ' *p) { same(p); }\n'
            self.unit(file, source, header)
            self.rows.append((file, 'same', 0, 'rk' + str(ord(label) - 96) + '+0x0=3'))
            self.sites.append((file, 'same', 0, file, 'caller_' + label, 3, 'rk' + str(ord(label) - 96) + '+0x0=3'))
        graph = solve.Graph(self.graph_dir)
        runtime = self.runtime(graph)
        for label, record in (('a', 'A'), ('b', 'B')):
            key = 'same@src/' + label + '.c'
            self.assertEqual(graph.declared('P:' + key + '#0'), record + ' *')
            self.assertEqual(runtime.winner(('heap', 'rk' + str(ord(label) - 96), 0))[0], 'rec:' + record + '*')
            edge = next(e for e in graph.edges if e['fn'] == 'caller_' + label and e['k'] == 'arg')
            self.assertEqual(edge['dst'], 'P:' + key + '#0')
            self.assertEqual(runtime.edge_cells(edge), {('heap', 'rk' + str(ord(label) - 96), 0): 3})
        self.assertFalse(runtime.pointer_cells('P:same#0'))
        self.assertEqual(solve.node_for(graph, dict(function='same', file='src/b.c', arg=0)),
                         'P:same@src/b.c#0')
        return graph

    def test_same_name_static_functions(self):
        self.same_name_case('static ')

    def test_same_name_external_definitions_in_banks(self):
        graph = self.same_name_case('')
        self.assertTrue(graph.ambiguous_function('same'))
        self.assertFalse(graph.ambiguous_function('same@src/a.c'))
        self.assertEqual(solve.fn_key(graph, 'same', 'src/missing.c'), 'same')

    def test_unique_names_keep_graph_and_solve_output(self):
        self.unit('src/a.c', '#include "flow.h"\nvoid typed(A *p) {}\nvoid weak(void *p) { typed(p); }\n',
                  'typedef struct A { int a; } A;\n')
        self.rows = [('src/a.c', 'typed', 0, 'rk1+0x0=3'), ('src/a.c', 'weak', 0, 'rk1+0x0=3')]
        graph = solve.Graph(self.graph_dir)
        runtime = self.runtime(graph)
        self.assertIn('typed', graph.functions)
        self.assertIn('weak', graph.functions)
        self.assertNotIn('typed@src/a.c', graph.functions)
        self.assertEqual(solve.fn_key(graph, 'typed', 'src/a.c'), 'typed')
        seeds = [dict(src='test', file='src/a.c', function='weak', arg='0', target='A *', hold='test')]
        first = solve.solve_all(graph, runtime, seeds)[1]
        # Disabling the identity normalization reproduces the pre-change graph loader.
        with mock.patch('type_flow_solve.FunctionKeys.rewrite', side_effect=lambda unit: unit):
            old_graph = solve.Graph(self.graph_dir)
        second = solve.solve_all(old_graph, self.runtime(old_graph),
                                 [dict(src='test', file='src/a.c', function='weak', arg='0', target='A *', hold='test')])[1]
        self.assertEqual(first, second)


@unittest.skipUnless(shutil.which('clang'), 'clang not installed')
class AmbiguousReferenceTests(RuntimeFixture):
    def test_external_reference_without_definition_stays_held(self):
        header = 'typedef struct A { int a; } A;\n'
        for label in ('a', 'b'):
            self.unit('src/' + label + '.c', '#include "flow.h"\nvoid same(A *p) {}\n', header)
        self.unit('src/c.c', '#include "flow.h"\nvoid same(A *p);\nvoid caller(void *p) { same(p); }\n', header)
        graph = solve.Graph(self.graph_dir)
        edge = next(e for e in graph.edges if e['fn'] == 'caller')
        self.assertEqual(edge['dst'], 'P:same#0')
        self.assertTrue(graph.ambiguous_function('same'))
        self.assertIsNone(graph.fn_def('same'))
        self.rows = [('src/a.c', 'same', 0, 'rk1+0x0=3')]
        self.kinds = [dict(id='rk2', receivers=[dict(function='same', arg=0, offset=0)])]
        runtime = self.runtime(graph)
        self.assertEqual(runtime.winner(('heap', 'rk1', 0))[0], 'rec:A*')
        self.assertEqual(runtime.winner(('heap', 'rk2', 0)), (None, 0.0))


@unittest.skipUnless(shutil.which('clang'), 'clang not installed')
class OffsetVoteTests(RuntimeFixture):
    header = """
typedef unsigned char u8;
typedef struct ObjectNodeHeader { int words[8]; } ObjectNodeHeader;
typedef struct Body { int value; } Body;
typedef struct Node { ObjectNodeHeader header; Body body; } Node;
typedef struct ActorRecord { u8 pad[0x8C]; Body embedded; Body *pointer; } ActorRecord;
"""

    def test_header_to_body_uses_existing_wrapper_layout(self):
        self.unit('src/a.c', '#include "flow.h"\nvoid root(Node *p) {}\nvoid weak(void *p) {}\n', self.header)
        self.rows = [('src/a.c', 'root', 0, 'rk1+0x0=3'), ('src/a.c', 'weak', 0, 'rk1+0x20=3')]
        runtime = self.runtime(solve.Graph(self.graph_dir))
        self.assertEqual(runtime.node_type('P:weak#0')[0], 'rec:Body*')
        self.assertEqual(runtime.cast_ok(runtime.pointer_cells('P:root#0'), 0x20, 'Body *'), 'correct')
        self.assertEqual(runtime.cast_ok(runtime.pointer_cells('P:root#0'), 0x24, 'Body *'), 'unproven')

    def test_embedded_record_and_containing_view_at_member_offset(self):
        self.unit('src/a.c', '#include "flow.h"\nvoid actor(ActorRecord *p) {}\nvoid weak(void *p) {}\n', self.header)
        self.rows = [('src/a.c', 'actor', 0, 'rk1+0x20=3'),
                     ('src/a.c', 'weak', 0, 'rk1+0xAC=3, rk1+0xB0=3, rk1+0xB1=3, rk1+0x24=3')]
        runtime = self.runtime(solve.Graph(self.graph_dir))
        self.assertEqual(runtime.winner(('heap', 'rk1', 0xAC))[0], 'rec:Body*')
        self.assertEqual(runtime.winner(('heap', 'rk1', 0xB0))[0], 'rec:ActorRecord*')
        self.assertEqual(runtime.winner(('heap', 'rk1', 0xB1)), (None, 0.0))
        self.assertEqual(runtime.winner(('heap', 'rk1', 0x24)), (None, 0.0))
        # A pointer member is storage for an address, not an embedded Body.
        self.assertEqual(runtime.cast_ok([('heap', 'rk1', 0xB0)], 0, 'Body *'), 'wrong')

    def test_header_alone_does_not_invent_a_body(self):
        self.unit('src/a.c', '#include "flow.h"\nvoid header(ObjectNodeHeader *p) {}\nvoid weak(void *p) {}\n', self.header)
        self.rows = [('src/a.c', 'header', 0, 'rk1+0x0=3'), ('src/a.c', 'weak', 0, 'rk1+0x20=3')]
        runtime = self.runtime(solve.Graph(self.graph_dir))
        self.assertEqual(runtime.winner(('heap', 'rk1', 0x20)), (None, 0.0))

    def test_h9_offset_is_applied_once(self):
        self.unit('src/a.c', '#include "flow.h"\nvoid take(ObjectNodeHeader *p) {}\n'
                  'void send(void *p) { take((ObjectNodeHeader *)((u8 *)p - 0x20)); }\n', self.header)
        self.rows = [('src/a.c', 'take', 0, 'rk1+0x0=3'), ('src/a.c', 'send', 0, 'rk1+0x20=3')]
        self.sites = [('src/a.c', 'take', 0, 'src/a.c', 'send', 3, 'rk1+0x0=3')]
        graph = solve.Graph(self.graph_dir)
        runtime = self.runtime(graph)
        comp = {'P:send#0': dict(t='Body *', st='retype', seed='P:send#0', **{'from': 'void *'})}
        result = solve.Solver(graph, runtime).evaluate(comp, [])
        cast = next(c for c in result['casts'] if c['dst'] == 'P:take#0')
        self.assertEqual(cast['evidence'], 'correct')
        self.assertEqual(cast['off'], -0x20)
        self.assertEqual(cast['cell_off'], 0)

    def test_h9_holder_cells_undo_argument_offset(self):
        self.unit('src/a.c', '#include "flow.h"\nvoid take(Body *p) {}\n'
                  'void send(void *p) { Node *holder = p; take((Body *)((u8 *)holder + 0x20)); }\n', self.header)
        self.sites = [('src/a.c', 'take', 0, 'src/a.c', 'send', 3, 'rk1+0x20=3')]
        graph = solve.Graph(self.graph_dir)
        runtime = self.runtime(graph)
        local = next(n for n in runtime.derived if n.startswith('L:send:holder'))
        self.assertEqual(runtime.pointer_cells(local), {('heap', 'rk1', 0): 3})
        self.assertEqual(runtime.winner(('heap', 'rk1', 0))[0], 'rec:Node*')
        self.assertEqual(runtime.winner(('heap', 'rk1', 0x20))[0], 'rec:Body*')



class ApplyIdentityTests(unittest.TestCase):
    def test_static_declarations_stay_in_the_defining_file(self):
        from types import SimpleNamespace
        from type_flow_apply import parameter_declaration_files
        graph = SimpleNamespace(fn_def=lambda key: dict(file='src/a.c', static=True))
        index = SimpleNamespace(typed={'same': {'src/a.c', 'src/b.c'}})
        self.assertEqual(parameter_declaration_files(graph, index, 'same@src/a.c'), ['src/a.c'])

    def test_duplicate_external_declarations_require_ownership(self):
        from types import SimpleNamespace
        from type_flow_apply import parameter_declaration_files
        graph = SimpleNamespace(fn_def=lambda key: dict(file='src/a.c', static=False), ambiguous_function=lambda key: True)
        index = SimpleNamespace(typed={'same': {'src/a.c', 'src/b.c'}})
        with self.assertRaisesRegex(ValueError, 'ambiguous_declaration_ownership'):
            parameter_declaration_files(graph, index, 'same@src/a.c')


if __name__ == '__main__':
    unittest.main()
