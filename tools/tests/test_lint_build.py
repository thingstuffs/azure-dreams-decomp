"""Native lint must preserve diagnostics and refuse misleading baseline passes."""
import copy
import csv
import json
import os
from pathlib import Path
import shutil
import subprocess
import sys
import tempfile
import unittest
from unittest.mock import patch

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / 'tools/lint'))
import lint_build as L


class LintBuildTest(unittest.TestCase):
    def setUp(self):
        self.tmp = tempfile.TemporaryDirectory()
        self.addCleanup(self.tmp.cleanup)
        self.root = Path(self.tmp.name) / 'game'
        self.port = self.root / 'private port'
        for path in ('src/slus', 'include', 'ledger'):
            (self.root / path).mkdir(parents=True)
        for path in ('tools', 'include'):
            (self.port / path).mkdir(parents=True)
        self.builder = self.port / 'tools/build.py'
        self.builder.write_text(
            'raise RuntimeError("the builder must never execute")\n'
            'CFLAGS = ["-m32", "-O1", "-w", "-fno-pie", '
            '"-I" + str(PORT / "include"), "-I" + str(GEN / "include")]\n'
            'CFLAGS += ["-fwrapv"]\n'
            'if ARGS.coverage:\n CFLAGS += ["--coverage"]\n')
        self.source = self.root / 'src/slus/a.c'
        self.source.write_text('int a(void) { return 1; }\n')
        self.rows = [dict(id='slus/a', container='slus', c_path='src/a.c'),
                     dict(id='slus/alias', container='slus', source_row='slus/a'),
                     dict(id='slus/absent', container='slus', c_path='src/absent.c')]
        (self.root / 'ledger/rows.jsonl').write_text(
            ''.join(json.dumps(r) + '\n' for r in self.rows))

    def summary(self, findings=()):
        return dict(schema_version=1, compiler='fixture GCC', units=1, compiler_jobs=4,
                    modes=list(L.MODES), phases=list(L.PHASES), flags=['-O1'],
                    limited=False, failed_jobs=0, **L.counts(findings))

    def diagnostic(self, **overrides):
        row = dict(file='src/slus/a.c', function='a', line=2, column=3,
                   severity='warning', warning='-Wreturn-type', message='missing return',
                   tu='src/slus/a.c', mode='m32', phase='syntax')
        row.update(overrides)
        return row

    def test_native_flags_preserve_order_without_executing_builder(self):
        flags = L.native_flags(self.port, self.root)
        self.assertNotIn('-w', flags)
        self.assertNotIn('-m32', flags)
        self.assertNotIn('--coverage', flags)
        self.assertEqual([f for f in flags if f.startswith('-I')],
                         ['-I' + str(self.port / 'include'), '-I' + str(self.root / 'include')])
        self.assertLess(flags.index('-fno-pie'), flags.index('-fwrapv'))
        self.assertIn('-Wmaybe-uninitialized', flags)
        self.assertEqual([f for f in flags if f.startswith('-O')][-1], '-O1')

    def test_unknown_flag_expressions_are_rejected(self):
        for expression in ('get_flags()', '__import__("os").getcwd()', 'PORT.read_text()'):
            with self.subTest(expression=expression):
                self.builder.write_text('CFLAGS = ' + expression + '\n')
                with self.assertRaisesRegex(ValueError, 'unsupported native CFLAGS'):
                    L.native_flags(self.port, self.root)

    def test_native_tus_skip_placements_missing_files_and_deduplicate(self):
        self.assertEqual(L.units(self.root), {'src/slus/a.c': ['slus/a']})
        extra = dict(id='slus/other', container='slus', c_path='src/a.c')
        with patch.object(L.source_layout, 'registry', return_value={
                r['id']: r for r in [*self.rows, extra]}):
            self.assertEqual(L.units(self.root)['src/slus/a.c'], ['slus/a', 'slus/other'])

    def test_parser_function_global_context_options_and_private_paths(self):
        log = (f"{self.source}: In function 'a':\n"
               f'{self.root}/include/shared/inline.h:5:8: warning: bad access [-Warray-bounds=]\n'
               f'{self.source}: At top level:\n'
               f'{self.source}:9:2: warning: pointer conversion [-Wint-conversion]\n'
               f'{self.port}/include/port.h:3:1: fatal error: missing header\n'
               'cc1: error: command line failure\n')
        rows = L.parse_diagnostics(log, self.root, self.port, 'src/slus/a.c', 'm64', 'flow')
        self.assertEqual(len(rows), 3)
        self.assertEqual((rows[0]['file'], rows[0]['function'], rows[0]['warning']),
                         ('include/shared/inline.h', 'a', '-Warray-bounds'))
        self.assertEqual(rows[1]['function'], '<global>')
        self.assertEqual(rows[2]['file'], '$PORT/include/port.h')
        self.assertNotIn(str(self.root), json.dumps(rows))
        unicode_context = L.parse_diagnostics(
            "src/slus/a.c: In function ‘b’:\n"
            'src/slus/a.c:1:2: warning: bad [-Wreturn-type]',
            self.root, self.port, 'src/slus/a.c', 'm32', 'syntax')
        self.assertEqual(unicode_context[0]['function'], 'b')

    def test_groups_union_widths_phases_tus_and_sites_but_keep_functions(self):
        diagnostics = [self.diagnostic(), self.diagnostic(phase='flow'),
                       self.diagnostic(mode='m64'), self.diagnostic(line=4),
                       self.diagnostic(tu='src/slus/b.c'), self.diagnostic(function='b'),
                       self.diagnostic(file='$PORT/include/a.h'),
                       self.diagnostic(severity='error'), self.diagnostic(warning='-Wunused-variable')]
        findings = L.group_findings(diagnostics)
        self.assertEqual(len(findings), 2)
        self.assertEqual(findings, L.group_findings(reversed(diagnostics)))
        first = findings[0]
        self.assertEqual(first['count'], 4)
        self.assertEqual(first['tu_count'], 2)
        self.assertEqual(first['modes'], 'm32,m64')
        self.assertEqual(first['phases'], 'flow,syntax')
        self.assertEqual(first['sites'], 'src/slus/a.c:2:3;src/slus/a.c:4:3')
        totals = L.counts(findings)
        self.assertEqual(totals['by_class']['-Wreturn-type'], 2)
        self.assertEqual(totals['by_mode']['m64']['-Wreturn-type'], 1)
        self.assertEqual(totals['by_subsystem']['slus']['-Wreturn-type'], 2)
        self.assertEqual(totals['by_class']['-Wshadow'], 0)
        self.assertIn('-Wreturn-type\t2\t2', L.format_summary(self.summary(findings)))

    def test_baseline_compares_each_class_even_if_total_decreases(self):
        previous = self.summary()
        previous['by_class']['-Wreturn-type'] = 20
        current = self.summary()
        current['by_class']['-Wshadow'] = 1
        self.assertEqual(L.check_baseline(current, L.baseline_record(previous)),
                         ['-Wshadow: 1 > baseline 0'])
        self.assertEqual(L.check_baseline(self.summary(), L.baseline_record(previous)), [])

    def test_baseline_rejects_failed_partial_and_changed_compiler_coverage(self):
        original = self.summary()
        baseline = L.baseline_record(original)
        for key, value in [('failed_jobs', 1), ('limited', True), ('compiler', 'other GCC'),
                           ('units', 0), ('compiler_jobs', 2), ('flags', ['-w']),
                           ('phases', ['syntax']), ('modes', ['m32'])]:
            with self.subTest(key=key):
                changed = dict(original, **{key: value})
                self.assertTrue(L.check_baseline(changed, baseline))

    def test_baseline_rejects_missing_classes_and_invalid_counts(self):
        summary = self.summary()
        for mutation in ('missing', 'negative', 'bool', 'string', 'null'):
            with self.subTest(mutation=mutation):
                baseline = copy.deepcopy(L.baseline_record(summary))
                if mutation == 'missing':
                    del baseline['by_class']['-Wshadow']
                elif mutation == 'null':
                    baseline['by_class'] = None
                else:
                    baseline['by_class']['-Wshadow'] = {
                        'negative': -1, 'bool': True, 'string': '1'}[mutation]
                self.assertTrue(L.check_baseline(summary, baseline))

    def cli(self, *arguments):
        return subprocess.run([sys.executable, str(ROOT / 'tools/lint/lint_build.py'),
                               '--root', str(self.root), '--port', str(self.port),
                               '--out', str(self.root / 'output'), *arguments],
                              capture_output=True, text=True, env=dict(os.environ, JOBS='2'))

    def test_cli_rejects_partial_baseline_and_unknown_tu(self):
        for action in ('--check', '--write-baseline'):
            result = self.cli('--only', 'src/slus/a.c', action)
            self.assertEqual(result.returncode, 2, result.stderr)
            self.assertIn('--only cannot', result.stderr)
        result = self.cli('--only', 'src/slus/no.c')
        self.assertEqual(result.returncode, 2, result.stderr)
        self.assertIn('unregistered', result.stderr)
        self.assertFalse((self.root / 'output').exists())

    @unittest.skipUnless(shutil.which('gcc'), 'GCC is required for the integration test')
    def test_real_gcc_two_width_census_baseline_and_regression(self):
        self.source.write_text('int a(void *p) { return (int)p; }\n'
                               'int flow(void) { int missing; return missing; }\n')
        baseline = self.root / 'baseline.json'
        result = self.cli('--summary', '--baseline', str(baseline), '--write-baseline')
        self.assertEqual(result.returncode, 0, result.stderr)
        summary = json.loads((self.root / 'output/lint_summary.json').read_text())
        self.assertEqual(summary['compiler_jobs'], 4)
        self.assertEqual(summary['failed_jobs'], 0)
        self.assertEqual(summary['by_class']['-Wpointer-to-int-cast'], 1)
        self.assertEqual(summary['by_class']['-Wuninitialized'], 1)
        self.assertEqual(summary['by_mode']['m32']['-Wpointer-to-int-cast'], 0)
        self.assertIn('slus', result.stdout)
        recorded = baseline.read_bytes()
        result = self.cli('--baseline', str(baseline), '--check')
        self.assertEqual(result.returncode, 0, result.stderr)
        self.assertIn('Baseline check passed', result.stdout)
        self.source.write_text('int a(void *p) { return p; }\n')
        result = self.cli('--baseline', str(baseline), '--check')
        self.assertEqual(result.returncode, 1, result.stderr)
        self.assertIn('-Wint-conversion: 1 > baseline 0', result.stderr)
        self.assertEqual(baseline.read_bytes(), recorded)

    @unittest.skipUnless(shutil.which('gcc'), 'GCC is required for the integration test')
    def test_failed_jobs_are_reported_and_cannot_overwrite_baseline(self):
        self.source.write_text('#include "absent.h"\n')
        baseline = self.root / 'baseline.json'
        baseline.write_text('keep this baseline\n')
        result = self.cli('--baseline', str(baseline), '--write-baseline')
        self.assertEqual(result.returncode, 1, result.stderr)
        self.assertEqual(baseline.read_text(), 'keep this baseline\n')
        with (self.root / 'output/lint_compile_failures.tsv').open() as stream:
            failures = list(csv.DictReader(stream, delimiter='\t'))
        self.assertEqual(len(failures), 4)
        self.assertEqual({f['mode'] for f in failures}, {'m32', 'm64'})
        self.assertEqual({f['phase'] for f in failures}, {'syntax', 'flow'})
        for failure in failures:
            log = (self.root / 'output' / failure['log']).read_text()
            self.assertIn('absent.h', log)
            self.assertNotIn(str(self.root), log)


if __name__ == '__main__':
    unittest.main()
