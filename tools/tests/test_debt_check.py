"""Debt cannot migrate between functions/classes or hide behind unrelated BYTES comments."""
import copy
import csv
import json
from pathlib import Path
import subprocess
import sys
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / 'tools/lint'))
import debt_check as D


class DebtCheckTest(unittest.TestCase):
    def setUp(self):
        (ROOT / 'build_ovl').mkdir(exist_ok=True)
        self.tmp = tempfile.TemporaryDirectory(dir=ROOT / 'build_ovl')
        self.addCleanup(self.tmp.cleanup)
        self.root = Path(self.tmp.name)
        (self.root / 'src').mkdir()
        self.path = self.root / 'src/a.c'
        self.path.write_text('int a(void) { return 0; }\n')

    def counts(self, text, scope='f#1'):
        source = D.analyze('src/a.c', text)
        self.assertEqual(source['errors'], [])
        return source['scopes'][scope]['counts']

    def test_detectors_ignore_strings_comments_static_prototypes_and_real_definitions(self):
        text = ('#define M2C_FIELD(x) (x)\n'
                'void helper(int); /* extern */\nextern int data;\n'
                'static void private_helper(void);\n'
                'typedef struct S_1234ABCD { int x; } S_1234ABCD;\n'
                'void f(void *p) {\nextern int nested;\n'
                'volatile int x; S_1234ABCD *v = (S_1234ABCD *)p;\n'
                'M2C_FIELD(v); goto done; done:;\n'
                '/* volatile goto M2C_FAKE (int *) */\n'
                'const char *s = "goto volatile M2C_STRING";\n}\n')
        source = D.analyze('src/a.c', text)
        self.assertEqual(source['errors'], [])
        self.assertEqual(source['scopes']['<global>']['counts'], dict(
            local_externs=2, generated_layouts=1, m2c_macros=1,
            goto=0, volatile=0, pointer_casts=0))
        self.assertEqual(source['scopes']['f#1']['counts'], dict(
            local_externs=1, generated_layouts=1, m2c_macros=1,
            goto=1, volatile=1, pointer_casts=1))

    def test_extern_definitions_are_excluded_but_mixed_declarations_count(self):
        text = ('extern int defined = 1, also_defined = 2;\n'
                'extern int array[] = {1, 2, 3};\n'
                'extern int declared, initialized = 3;\n'
                'extern void f(void) { extern int used; }\n')
        source = D.analyze('src/a.c', text)
        self.assertEqual(source['errors'], [])
        self.assertEqual(source['scopes']['<global>']['counts']['local_externs'], 1)
        self.assertEqual(source['scopes']['f#1']['counts']['local_externs'], 1)

    def test_function_pointer_variable_is_not_a_prototype_and_merged_functions_have_scopes(self):
        text = ('void (*callback)(void); int f(void) { return 0; }\n'
                'int f(void) { extern int x; return x; }')
        source = D.analyze('src/a.c', text)
        self.assertEqual(source['scopes']['<global>']['counts']['local_externs'], 0)
        self.assertEqual(source['scopes']['f#1']['counts']['local_externs'], 0)
        self.assertEqual(source['scopes']['f#2']['counts']['local_externs'], 1)

    def test_bytes_exempts_only_adjacent_site_not_entire_function(self):
        text = ('void f(void *p) {\n'
                ' /* BYTES: recorded dead arm. */\n'
                ' if (p) { volatile int *v = (int *)p; goto exit; }\n'
                ' volatile int *w = (int *)p;\n'
                ' goto exit; exit:;\n}\n')
        counts = self.counts(text)
        self.assertEqual(counts['volatile'], 1)
        self.assertEqual(counts['goto'], 1)
        self.assertEqual(counts['pointer_casts'], 1)
        self.assertEqual(D.analyze('src/a.c', text)['markers'], 1)

    def test_trailing_marker_applies_to_previous_statement_and_do_body_remains_checked(self):
        text = ('void f(void *p) {\n'
                ' volatile int *v = (int *)p; /* BYTES: recorded store. */\n'
                ' /* BYTES: recorded loop-note barrier. */\n'
                ' do { volatile int *w = (int *)p; } while (0);\n'
                ' volatile int remaining;\n}\n')
        counts = self.counts(text)
        self.assertEqual(counts['volatile'], 2)
        self.assertEqual(counts['pointer_casts'], 1)

    def test_function_wide_marker_cannot_hide_an_entire_debt_scope(self):
        source = D.analyze('src/a.c',
            '/* BYTES: recorded reason. */\nvoid f(void) { volatile int x; }')
        self.assertTrue(any('whole function' in message for message in source['errors']))

    def test_case_marker_binds_to_its_label_and_does_not_exempt_following_code(self):
        text = ('void f(int n) { switch (n) {\n'
                'case 5: /* BYTES: unrecoverable in-range label. */\n'
                'volatile int x; break; } }')
        self.assertEqual(self.counts(text)['volatile'], 1)

    def test_malformed_marker_and_unbalanced_c_fail_closed(self):
        for text in ('void f(void) { /* BYTES: reason\n */ goto x; }',
                     'void f(void) {\n/* BYTES: reason */\n}',
                     'void f(void) {'):
            self.assertTrue(D.analyze('src/a.c', text)['errors'])
        self.assertEqual(self.counts('void f(void) { const char *s = "BYTES:"; }')['goto'], 0)

    def test_ratchet_rejects_per_class_per_file_and_per_function_tradeoffs(self):
        self.path.write_text('void a(void) { volatile int x; } void b(void) { }')
        before = D.census(self.root)
        baseline = D.baseline_record(before)
        self.path.write_text('void a(void) { } void b(void) { volatile int x; }')
        problems = D.check_baseline(D.census(self.root), baseline)
        self.assertTrue(any('::b#1: volatile' in p for p in problems))
        self.path.write_text('void a(void) { goto end; end:; } void b(void) { }')
        problems = D.check_baseline(D.census(self.root), baseline)
        self.assertTrue(any('all: goto' in p for p in problems))
        self.assertTrue(any('src/a.c: goto' in p for p in problems))

    def test_density_increase_with_same_cast_count_passes_and_is_reported(self):
        self.path.write_text('int a(void *p) { int x = 1; x += 2; return *(int *)p; }')
        before = D.census(self.root)
        self.path.write_text('int a(void *p) { return *(int *)p; }')
        after = D.census(self.root)
        baseline = D.baseline_record(before)
        self.assertEqual(D.check_baseline(after, baseline), [])
        D.write_outputs(self.root / 'out', after, baseline)
        with (self.root / 'out/debt_functions.tsv').open() as stream:
            row = next(r for r in csv.DictReader(stream, delimiter='\t')
                       if r['function'] == 'a#1')
        self.assertEqual(row['status'], 'PASS')
        self.assertGreater(float(row['pointer_casts_per_1000_tokens']),
                           1000 / before['by_function']['src/a.c']['a#1']['tokens'])

    def test_density_increase_with_fewer_casts_passes(self):
        self.path.write_text('int a(void *p, void *q) { int x = 1; x += 2; x += 3; '
                             'x += 4; return *(int *)p + *(int *)q + x; }')
        before = D.census(self.root)
        self.path.write_text('int a(void *p, void *q) { return *(int *)p; }')
        after = D.census(self.root)
        for rows in ('by_file', 'by_function'):
            old, new = before[rows]['src/a.c'], after[rows]['src/a.c']
            if rows == 'by_function':
                old, new = old['a#1'], new['a#1']
            self.assertLess(new['counts']['pointer_casts'], old['counts']['pointer_casts'])
            self.assertGreater(new['counts']['pointer_casts'] * old['tokens'],
                               old['counts']['pointer_casts'] * new['tokens'])
        self.assertEqual(D.check_baseline(after, D.baseline_record(before)), [])

    def test_added_cast_fails_even_when_density_decreases(self):
        self.path.write_text('int a(void *p) { return *(int *)p; }')
        before = D.census(self.root)
        self.path.write_text('int a(void *p) { int x = 1; x += 2; x += 3; x += 4; '
                             'x += 5; return *(int *)p + *(short *)p + x; }')
        after = D.census(self.root)
        old, new = before['by_function']['src/a.c']['a#1'], after['by_function']['src/a.c']['a#1']
        self.assertLess(new['counts']['pointer_casts'] * old['tokens'],
                        old['counts']['pointer_casts'] * new['tokens'])
        self.assertEqual(D.check_baseline(after, D.baseline_record(before)), [
            'all: pointer_casts 2 > baseline 1',
            'src/a.c: pointer_casts 2 > baseline 1',
            'src/a.c::a#1: pointer_casts 2 > baseline 1'])

    def test_baseline_rejects_corruption_partial_runs_and_new_debt(self):
        self.path.write_text('void a(void) { volatile int x; }')
        before = D.census(self.root)
        baseline = D.baseline_record(before)
        self.assertEqual(D.check_baseline(before, baseline), [])
        for value in (True, -1, '0'):
            broken = copy.deepcopy(baseline)
            broken['by_class']['goto'] = value
            with self.assertRaises(ValueError):
                D.validate_baseline(broken)
        broken = copy.deepcopy(baseline)
        broken['by_file']['src']['a.c'][1]['a#1'][-1] = 10
        with self.assertRaises(ValueError):
            D.validate_baseline(broken)
        self.assertTrue(D.check_baseline(dict(before, limited=True), baseline))
        (self.root / 'src/new.c').write_text('void new(void) { volatile int x; }')
        self.assertTrue(D.check_baseline(D.census(self.root), baseline))

    def test_absent_file_function_and_class_entries_mean_zero(self):
        baseline = D.baseline_record(D.census(self.root))
        self.assertEqual(baseline['by_file'], {})
        (self.root / 'src/new.c').write_text('void new(void) { }')
        self.assertEqual(D.check_baseline(D.census(self.root), baseline), [])
        self.path.write_text('void a(void) { volatile int x; } void clean(void) { }')
        baseline = D.baseline_record(D.census(self.root))
        packed = baseline['by_file']['src']['a.c'][1]
        self.assertEqual(set(packed), {'a#1'})
        self.assertEqual(len(packed['a#1']), 6)  # No trailing pointer-cast count.
        self.path.write_text('void a(void) { volatile int x; } void other_clean(void) { }')
        self.assertEqual(D.check_baseline(D.census(self.root), baseline), [])
        self.path.write_text('void a(void) { goto end; end:; }')
        self.assertTrue(any('::a#1: goto 1 > baseline 0' in p
                            for p in D.check_baseline(D.census(self.root), baseline)))

    def test_new_nonzero_function_fails_even_if_file_and_class_totals_do_not_grow(self):
        self.path.write_text('void a(void) { volatile int x; }')
        baseline = D.baseline_record(D.census(self.root))
        self.path.write_text('void a(void) { } void added(void) { volatile int x; }')
        problems = D.check_baseline(D.census(self.root), baseline)
        self.assertEqual(problems, ['src/a.c::added#1: volatile 1 > baseline 0'])

    def test_sparse_file_tokens_include_omitted_zero_debt_scopes(self):
        self.path.write_text('int a(void *p) { return *(int *)p; }\n'
                             'int clean(void) { int x = 1; x += 2; return x; }')
        before = D.census(self.root)
        baseline = D.baseline_record(before)
        expanded = D.validate_baseline(baseline)
        self.assertEqual(expanded['by_file'], before['by_file'])
        self.assertEqual(set(expanded['by_function']['src/a.c']), {'a#1'})
        self.path.write_text('int a(void *p) { return *(int *)p; }')
        after = D.census(self.root)
        self.assertLess(after['by_file']['src/a.c']['tokens'], before['by_file']['src/a.c']['tokens'])
        self.assertEqual(D.check_baseline(after, baseline), [])

    def test_sparse_serialization_is_deterministic_and_round_trips(self):
        self.path.write_text('void z(void) { volatile int x; } void a(void) { goto end; end:; }')
        (self.root / 'src/z.c').write_text('extern int x;')
        summary = D.census(self.root)
        baseline = D.baseline_record(summary)
        encoded = D.baseline_text(baseline)
        shuffled = copy.deepcopy(baseline)
        for entries in shuffled['by_file'].values():
            for row in entries.values():
                row[1] = dict(reversed(list(row[1].items())))
        shuffled['by_file'] = {k: dict(reversed(list(v.items())))
                               for k, v in reversed(list(shuffled['by_file'].items()))}
        self.assertEqual(D.baseline_text(shuffled), encoded)
        decoded = json.loads(encoded)
        self.assertEqual(decoded, baseline)
        self.assertEqual(D.check_baseline(summary, decoded), [])

    def test_sparse_validator_rejects_bad_vectors_tokens_and_totals(self):
        self.path.write_text('void a(void) { volatile int x; }')
        baseline = D.baseline_record(D.census(self.root))
        for vector in ([], [1], [1, 0], [1, -1], [1, True], [1, '1'],
                       [1] * 8, [1, 1, 0]):
            broken = copy.deepcopy(baseline)
            broken['by_file']['src']['a.c'][1]['a#1'] = vector
            with self.assertRaises(ValueError):
                D.validate_baseline(broken)
        broken = copy.deepcopy(baseline)
        broken['by_file']['src']['a.c'][0] = 0
        with self.assertRaises(ValueError):
            D.validate_baseline(broken)
        for scopes in ({}, []):
            broken = copy.deepcopy(baseline)
            broken['by_file']['src']['a.c'][1] = scopes
            with self.assertRaises(ValueError):
                D.validate_baseline(broken)

    def cli(self, *args):
        return subprocess.run([sys.executable, str(ROOT / 'tools/lint/debt_check.py'),
            '--root', str(self.root), '--out', str(self.root / 'out'),
            '--baseline', str(self.root / 'baseline.json'), *args], text=True, capture_output=True)

    def test_cli_write_check_regression_and_partial_refusal(self):
        r = self.cli('--write-baseline')
        self.assertEqual(r.returncode, 0, r.stderr)
        r = self.cli('--check')
        self.assertEqual(r.returncode, 0, r.stderr)
        self.assertIn('Baseline check passed', r.stdout)
        self.path.write_text('void a(void) { volatile int x; }')
        r = self.cli('--check')
        self.assertEqual(r.returncode, 1, r.stderr)
        self.assertIn('volatile', r.stderr)
        for action in ('--check', '--write-baseline'):
            r = self.cli('--only', 'src/a.c', action)
            self.assertEqual(r.returncode, 2)
        self.assertTrue((self.root / 'out/debt_functions.tsv').is_file())


if __name__ == '__main__':
    unittest.main()
