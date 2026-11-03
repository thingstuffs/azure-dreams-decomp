"""Regression tests for runtime identity repair and gap classification (unittest)."""
import csv
import gzip
import json
from pathlib import Path
import shutil
import sys
import tempfile
from types import SimpleNamespace
import unittest

HERE = Path(__file__).resolve().parent
sys.path.insert(0, str(HERE))
from rt_linemap import LineMap, build
from rt_rekey import rekey, table_rows
from test_type_flow_runtime import RuntimeFixture
import type_flow_gaps as gaps
import type_flow_solve as flow


class LineMapTests(unittest.TestCase):
    def test_insert_replace_delete_missing_and_roundtrip(self):
        scratch = HERE.parents[1] / 'tmp'
        scratch.mkdir(exist_ok=True)
        with tempfile.TemporaryDirectory(dir=scratch) as name:
            root = Path(name)
            old, new = root / 'old', root / 'new'
            for tree in (old, new):
                (tree / 'src').mkdir(parents=True)
            (old / 'src/a.c').write_text('first\nreplace me\nlast\ndeleted\n')
            (new / 'src/a.c').write_text('inserted\nfirst\nreplaced\nlast\n')
            (old / 'src/missing.c').write_text('gone\n')
            mapping = build(old, new)
            self.assertEqual(mapping.line('src/a.c', 1), 2)
            self.assertEqual(mapping.line('src/a.c', 2), 3)
            self.assertIsNone(mapping.line('src/a.c', 4))
            self.assertIsNone(mapping.line('src/missing.c', 1))
            self.assertEqual(mapping.line('src/unchanged.c', 7), 7)
            path = root / 'map.json.gz'
            mapping.write(path)
            restored = LineMap.read(path)
            self.assertEqual(restored.maps, mapping.maps)
            self.assertEqual(restored.missing, mapping.missing)


class RekeyTests(unittest.TestCase):
    def setUp(self):
        scratch = HERE.parents[1] / 'tmp'
        scratch.mkdir(exist_ok=True)
        self.tmp = tempfile.TemporaryDirectory(dir=scratch)
        self.addCleanup(self.tmp.cleanup)
        self.root = Path(self.tmp.name)
        self.runtime = self.root / 'old'
        self.runtime.mkdir()
        self.output = self.root / 'new'
        (self.root / 'src').mkdir()
        (self.root / 'src/a.c').write_text('\n\nvoid renamed(void) {\n}\n\nvoid caller(void) {\n\n\n}\n')
        self.graph = SimpleNamespace(root=self.root, functions={
            'renamed': [dict(file='src/a.c', name='renamed', key='renamed', line=3)],
            'caller': [dict(file='src/a.c', name='caller', key='caller', line=6)],
            'actual@src/b.c': [dict(file='src/b.c', name='actual', key='actual@src/b.c', line=1)],
            'actual@src/c.c': [dict(file='src/c.c', name='actual', key='actual@src/c.c', line=1)]},
            calls=[dict(file='src/a.c', caller='caller', callee='actual@src/b.c', mode='direct', line=8)])
        self.table('sites.tsv', ['address', 'file', 'function', 'line'], [['1', 'src/a.c', 'old', '10']])
        self.table('fn_args.tsv', ['file', 'function', 'arg', 'values'], [['src/a.c', 'old', '0', 'rk1+0x20=7']])
        self.table('callsite_args.tsv.gz', ['callee_file', 'callee', 'arg', 'caller_file', 'caller', 'line', 'cells', 'calls'],
                   [['src/legacy.c', 'legacy', '0', 'src/a.c', 'caller', '20', 'rk1+0x20=7', '7']])
        self.table('pointees.tsv.gz', ['file', 'function', 'line', 'value_class', 'value_target', 'count'],
                   [['src/a.c', 'old', '10', 'func', 'src/a.c:old', '7']])
        (self.runtime / 'kinds_rt.json').write_text(json.dumps(dict(kinds=[dict(
            id='rk1', receivers=[dict(file='src/a.c', function='old', line=10)],
            body_receivers=[dict(file='src/a.c', function='old')])], unrelated='preserve')))
        (self.runtime / 'untouched.bin').write_bytes(b'unchanged')
        self.mapping = LineMap({'src/a.c': [None] * 21})
        self.mapping.maps['src/a.c'][10] = 3
        self.mapping.maps['src/a.c'][20] = 8

    def table(self, name, columns, rows):
        path = self.runtime / name
        op = gzip.open if path.suffix == '.gz' else open
        with op(path, 'wt') as stream:
            writer = csv.writer(stream, delimiter='\t')
            writer.writerow(columns)
            writer.writerows(rows)

    def test_rekeys_all_tables_and_preserves_input(self):
        before = {path.name: path.read_bytes() for path in self.runtime.iterdir()}
        summary = rekey(self.graph, self.mapping, self.runtime, self.output)
        entry = next(table_rows(self.output / 'fn_args.tsv'))
        self.assertEqual((entry['function'], entry['values']), ('renamed', 'rk1+0x20=7'))
        site = next(table_rows(self.output / 'sites.tsv'))
        self.assertEqual((site['function'], site['line']), ('renamed', '3'))
        call = next(table_rows(self.output / 'callsite_args.tsv.gz'))
        self.assertEqual((call['callee'], call['callee_file'], call['line'], call['cells']),
                         ('actual', 'src/b.c', '8', 'rk1+0x20=7'))
        pointer = next(table_rows(self.output / 'pointees.tsv.gz'))
        self.assertEqual((pointer['function'], pointer['line'], pointer['value_target']), ('renamed', '3', 'src/a.c:renamed'))
        kind = json.loads((self.output / 'kinds_rt.json').read_text())['kinds'][0]
        self.assertEqual(kind['body_receivers'][0]['function'], 'renamed')
        self.assertEqual(kind['receivers'][0]['line'], 3)
        self.assertTrue((self.output / 'untouched.bin').is_symlink())
        self.assertEqual(before, {path.name: path.read_bytes() for path in self.runtime.iterdir()})
        self.assertEqual(summary['stats']['fn_args.tsv_rows'], 1)

    def test_refuses_existing_or_nested_outputs(self):
        self.output.mkdir()
        with self.assertRaisesRegex(ValueError, 'new directory'):
            rekey(self.graph, self.mapping, self.runtime, self.output)
        with self.assertRaisesRegex(ValueError, 'outside'):
            rekey(self.graph, self.mapping, self.runtime, self.runtime / 'nested')
        self.assertEqual(list(self.output.iterdir()), [])

    def test_failed_write_leaves_no_partial_destination(self):
        (self.runtime / 'kinds_rt.json').write_text('{broken')
        with self.assertRaises(json.JSONDecodeError):
            rekey(self.graph, self.mapping, self.runtime, self.output)
        self.assertFalse(self.output.exists())
        self.assertFalse(list(self.root.glob('new.tmp-*')))

    def test_deleted_function_anchor_cannot_rename_to_previous_body(self):
        self.mapping.maps['src/a.c'][10] = 5  # between the two definitions
        rekey(self.graph, self.mapping, self.runtime, self.output)
        self.assertEqual(next(table_rows(self.output / 'fn_args.tsv'))['function'], 'old')

    def test_unmapped_lines_are_reported(self):
        summary = rekey(self.graph, LineMap({'src/a.c': [None] * 21}), self.runtime, self.output)
        call = next(table_rows(self.output / 'callsite_args.tsv.gz'))
        self.assertEqual(call['line'], '20')
        self.assertEqual(summary['stats']['callsite_lines_unmapped'], 1)


@unittest.skipUnless(shutil.which('clang'), 'clang not installed')
class GapTests(RuntimeFixture):
    def setup_classifier(self):
        self.unit('src/a.c', '#include "flow.h"\nvoid typed(Body *p) {}\nvoid weak(void *p) {}\n'
                  'void unknown(void *p) {}\nvoid never(void *p) {}\n', 'typedef struct Body { int a; } Body;\n')
        self.rows = [('src/a.c', 'typed', 0, 'rk1+0x0=3'), ('src/a.c', 'weak', 0, 'scalar=3, null=1'),
                     ('src/a.c', 'unknown', 0, 'rk2+0x0=3')]
        graph = flow.Graph(self.graph_dir)
        runtime = self.runtime(graph)
        return graph, runtime, gaps.Classifier(graph, runtime, self.rt_dir)

    def cast(self, source, evidence='unproven'):
        return dict(src=source, dst='P:typed#0', fn='weak', file='src/a.c', line=3, edge='assign',
                    off=0, cast='Body *', evidence=evidence, new=True)

    def test_capture_structural_scalar_vote_and_contradiction_causes(self):
        _, _, classifier = self.setup_classifier()
        for source, evidence, expected in (
                ('P:never#0', 'unproven', 'fn_never_run'),
                ('P:weak#0', 'unproven', 'observed_scalar'),
                ('P:unknown#0', 'unproven', 'vote_gap'),
                ('L:weak:x@3', 'unproven', 'local_unlabelled'),
                ('G:holder', 'unproven', 'site_not_reached'),
                ('P:typed#0', 'wrong', 'contradicted'),
                ('P:typed#0', 'view_member_missing', 'contradicted'),
                ('P:typed#0', 'unproven', 'evidence_mismatch')):
            with self.subTest(source=source, evidence=evidence):
                self.assertEqual(classifier.classify(self.cast(source, evidence), {})[0], expected)

    def test_same_name_in_another_file_does_not_count_as_execution(self):
        header = 'typedef struct Body { int a; } Body;\n'
        for label in ('a', 'b'):
            self.unit('src/' + label + '.c', '#include "flow.h"\nvoid same(void *p) {}\n', header)
        self.rows = [('src/a.c', 'same', 0, 'rk1+0x0=3')]
        graph = flow.Graph(self.graph_dir)
        classifier = gaps.Classifier(graph, self.runtime(graph), self.rt_dir)
        cast = self.cast('P:same@src/b.c#0')
        cast.update(file='src/b.c', fn='same@src/b.c')
        self.assertEqual(classifier.classify(cast, {})[0], 'fn_never_run')

    def test_h9_line_drift_uses_mapped_caller_file(self):
        self.unit('src/a.c', '#include "flow.h"\nvoid target(Body *p) {}\n'
                  'void caller(void *p) { target(p); }\n', 'typedef struct Body { int a; } Body;\n')
        self.sites = [('src/a.c', 'target', 0, 'src/a.c', 'caller', 10, 'rk1+0x0=3'),
                      ('src/a.c', 'target', 0, 'src/a.c', 'caller', 20, 'rk1+0x0=3')]
        graph = flow.Graph(self.graph_dir)
        runtime = self.runtime(graph)
        mapping = LineMap({'src/a.c': [None] * 21})
        mapping.maps['src/a.c'][10] = 3
        classifier = gaps.Classifier(graph, runtime, self.rt_dir, mapping)
        cast = self.cast('P:caller#0')
        cast.update(dst='P:target#0', fn='caller', edge='arg')
        self.assertEqual(classifier.classify(cast, {})[0], 'line_drift')

    def test_h9_gap_does_not_apply_source_offset_twice(self):
        self.unit('src/a.c', '#include "flow.h"\nvoid target(Body *p) {}\n'
                  'void caller(void *p) { target((Body *)((char *)p - 32)); }\n',
                  'typedef struct Body { int a; } Body;\n')
        self.sites = [('src/a.c', 'target', 0, 'src/a.c', 'caller', 3, 'rk1+0x0=3')]
        graph = flow.Graph(self.graph_dir)
        classifier = gaps.Classifier(graph, self.runtime(graph), self.rt_dir)
        cast = self.cast('P:caller#0')
        cast.update(dst='P:target#0', fn='caller', edge='arg', off=-32)
        cause, detail, _ = classifier.classify(cast, {})
        self.assertEqual(cause, 'vote_gap')
        self.assertIn('rk1+0', detail)
        self.assertNotIn('rk1-32', detail)

    def test_report_counts_every_blocker_and_has_empty_schema(self):
        graph, runtime, _ = self.setup_classifier()
        directory = self.root / 'solve'
        (directory / 'components').mkdir(parents=True)
        flow.write_tsv(directory / 'components.tsv', [dict(component='C1', verdict='bridge', net=-3)])
        casts = [self.cast('P:never#0'), self.cast('P:unknown#0'), self.cast('P:typed#0', 'wrong')]
        (directory / 'components/C1.json').write_text(json.dumps(dict(comp={}, casts=casts)))
        output = self.root / 'gaps'
        summary = gaps.analyze(graph, runtime, self.rt_dir, directory, output)
        self.assertEqual(summary['blocking_casts'], 3)
        self.assertEqual(sum(summary['casts_by_cause'].values()), 3)
        self.assertEqual(len(list(table_rows(output / 'gaps.tsv'))), 3)
        empty = self.root / 'empty'
        summary = gaps.analyze(graph, runtime, self.rt_dir, directory, empty, verdicts=['whole'])
        self.assertEqual(summary['blocking_casts'], 0)
        self.assertEqual((empty / 'gaps.tsv').read_text().strip().split('\t'), gaps.GAP_COLUMNS)


if __name__ == '__main__':
    unittest.main()
