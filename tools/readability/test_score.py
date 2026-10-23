"""Small lexical fixtures and end-to-end contracts, with no game build dependency."""
import csv
import importlib.util
from pathlib import Path
import sys
import tempfile
import unittest

HERE = Path(__file__).resolve().parent
spec = importlib.util.spec_from_file_location('readability_score', HERE / 'score.py')
score = importlib.util.module_from_spec(spec)
sys.modules[spec.name] = score
spec.loader.exec_module(score)


def source(text, path='src/test/example.c'):
    return score.analyze_source(path, text.encode())


class CensusTests(unittest.TestCase):
    def test_fixture_metrics_and_weights(self):
        s = score.analyze_source('src/test/mixed.c', (HERE / 'fixtures/mixed.c').read_bytes())
        self.assertFalse(s.warnings)
        self.assertEqual([f.symbol for f in s.functions], ['func_80002000'])
        f = s.functions[0]
        expected = dict(raw_offsets=1, pointer_casts=2, m2c=1, gotos=1, address_self=1,
                        address_func_refs=1, address_data_refs=0, address_unknown_refs=0,
                        temporary_refs=9, temporary_unique=2, magic_numbers=2, max_nesting=3,
                        offsets_score=8, casts_score=6, names_score=16, magic_score=4,
                        structure_score=24, score=58)
        for k, v in expected.items():
            self.assertEqual(f.metrics[k], v, k)
        self.assertEqual(f.calls, {'func_80001000'})

    def test_merged_data_declarations_attributes_and_variants(self):
        s = score.analyze_source('src/test/merged.c', (HERE / 'fixtures/merged.c').read_bytes())
        self.assertFalse(s.warnings)
        self.assertEqual([f.symbol for f in s.functions], ['helper', 'first', 'second', 'variant', 'variant'])
        self.assertEqual([f.occurrence for f in s.functions[-2:]], [1, 2])
        self.assertTrue(s.functions[0].static)
        edges, unresolved = score.resolve_calls(s.functions)
        self.assertEqual(len(s.functions[0].callers), 1)  # Three calls, one distinct caller.
        self.assertEqual(len(edges), 3)
        self.assertFalse(unresolved)
        self.assertNotEqual(s.functions[-2].key, s.functions[-1].key)

    def test_comments_strings_characters_and_continued_directives(self):
        s = source('''#define DEF \\\nvoid phantom(void) { goto bad; }
/* void fake(void) { } */
int real(void) {
 const char *s = "goto M2C_BAD var_v0 D_12345678 }";
 char c = '}'; // goto comment;
 return 0;
}''')
        self.assertEqual([f.symbol for f in s.functions], ['real'])
        for key in ('m2c', 'gotos', 'temporary_refs', 'address_data_refs', 'magic_numbers'):
            self.assertEqual(s.functions[0].metrics[key], 0, key)
        self.assertFalse(s.warnings)

    def test_pointer_casts_not_multiplication_sizeof_or_prototypes(self):
        f = source('''void work(void *p) {
 int x = (a * b); unsigned n = sizeof(int *);
 extern void declared(int *);
 p = (const struct Node * const)p;
 p = (void **)&p;
 ((void (*)(int))p)(3);
}''').functions[0]
        self.assertEqual(f.metrics['pointer_casts'], 3)
        self.assertNotIn('declared', f.calls)

    def test_byte_offsets_signed_grouped_members_and_one(self):
        f = source('''void work(void *p) {
 a = (u8 *)p + 0x20;
 b = ((char *)p) - 12;
 c = (s8 *)p + -2;
 d = (unsigned char *)p->next + 1;
 e = (u16 *)p + 0x20;
 f = (u8 *)p + dynamic;
}''').functions[0]
        self.assertEqual(f.metrics['raw_offsets'], 4)
        self.assertEqual(f.metrics['pointer_casts'], 6)

    def test_magic_context_union_suffixes_and_exclusions(self):
        f = source('''int work(void) {
 int a[7];
 x = (thing + 42) < 0x20;
 y = -1; z = 0UL; a = 1.0f;
 if ((bits & 0x80) != 0 && f(99)) { x += f(23); }
 standalone(12);
 switch(x) { case 37: break; }
 return 88;
}''').functions[0]
        self.assertEqual(f.metrics['magic_numbers'], 4)

    def test_initializer_lists_and_chained_assignment(self):
        f = source('void work(void) { int a[] = {3, 4, 5}; x = y = 6; }').functions[0]
        self.assertEqual(f.metrics['magic_numbers'], 4)

    def test_address_names_and_temporaries(self):
        f = source('int func_ABCD(int arg12) { int spA0 = D_1234; temp_x = var_y + p->unk_14; return arg12; }').functions[0]
        self.assertEqual(f.metrics['address_self'], 1)
        self.assertEqual(f.metrics['address_data_refs'], 1)
        self.assertEqual(f.metrics['address_unknown_refs'], 1)
        self.assertEqual(f.metrics['temporary_refs'], 5)
        self.assertEqual(f.metrics['temporary_unique'], 4)

    def test_static_visibility_ambiguity_and_recursion(self):
        sources = [source('static int helper(void) { return helper(); } int a(void) { return helper(); }', 'src/a/a.c'),
                   source('static int helper(void) { return 0; } int b(void) { return helper(); }', 'src/b/b.c'),
                   source('int shared(void) { return 0; }', 'src/a/c.c'),
                   source('int shared(void) { return 0; }', 'src/b/d.c'),
                   source('int c(void) { shared(); helper(); external(); return 0; }', 'src/c/e.c')]
        fs = [f for s in sources for f in s.functions]
        edges, unknown = score.resolve_calls(fs)
        self.assertEqual(len(edges), 3)  # Includes recursion but does not boost its caller count.
        self.assertEqual(len(fs[0].callers), 1)
        self.assertEqual(len(fs[2].callers), 1)
        self.assertEqual({r['reason'] for r in unknown}, {'ambiguous', 'external_or_indirect'})
        self.assertEqual(len(unknown), 3)

    def test_length_uses_code_lines_and_brace_depth(self):
        a = source('void f(void) {\n' + '\n'.join('/* comment */' for _ in range(80)) + '\n}').functions[0]
        self.assertEqual(a.metrics['code_lines'], 2)
        self.assertEqual(a.metrics['structure_score'], 0)
        b = source('void f(void) {\n' + '\n'.join('f();' for _ in range(40)) + '\n}').functions[0]
        self.assertEqual(b.metrics['code_lines'], 42)
        self.assertEqual(b.metrics['structure_score'], 2)

    def test_delimiter_warnings_are_explicit(self):
        self.assertTrue(source('void broken(void) { if (x) { }').warnings)

    def test_summaries_include_data_only_files_and_use_max_depth(self):
        a = source('int a = 3;', 'src/test/data.c')
        b = source('void f(void) { if(x) { if(y) { } } }', 'src/test/code.c')
        rows = list(score.summarize([a, b], b.functions, lambda p: 'test'))
        self.assertEqual(rows[0]['files'], 2)
        self.assertEqual(rows[0]['functions'], 1)
        self.assertEqual(rows[0]['max_nesting'], 2)

    def test_output_determinism_queue_payoff_and_trend_conservation(self):
        with tempfile.TemporaryDirectory(dir=HERE) as tmp:
            root = Path(tmp)
            (root / 'src/test').mkdir(parents=True)
            (root / 'src/test/a.c').write_text('void f(void *p) { x = (u8 *)p + 24; } void g(void) { f(); f(); } void h(void) { f(); }')
            (root / 'src/test/data.c').write_text('int data = 3;')
            outputs = []
            for label in ('one', 'two'):
                ss, fs, edges, unknown = score.scan(root)
                score.write_outputs(root / label, 'fixture', ss, fs, edges, unknown)
                outputs.append({p.relative_to(root / label): p.read_bytes() for p in (root / label).rglob('*.tsv')})
            self.assertEqual(outputs[0], outputs[1])
            with (root / 'one/queue/offsets.tsv').open() as stream:
                row = next(csv.DictReader(stream, delimiter='\t'))
            self.assertEqual(row['payoff'], '16')
            self.assertEqual(row['known_callers'], '2')
            self.assertEqual(row['category_score'], '8')
            with (root / 'one/trend.tsv').open() as stream:
                total = sum(int(r['weighted_debt']) for r in csv.DictReader(stream, delimiter='\t'))
            self.assertEqual(total, sum(f.metrics['score'] for f in fs))
            self.assertNotIn(str(root), score.render_docs('fixture', ss, fs, edges, unknown))

    def test_knr_headers_do_not_hide_later_merged_definitions(self):
        s = source("int legacy(arg0, value)\n s16 arg0;\n char *value;\n { return arg0; }\n"
                   "int following(void) { return legacy(0, 0); }\n"
                   "implicit() { return 0; }\n int declared(arg0);\n int final(void) { return 0; }")
        self.assertEqual([f.symbol for f in s.functions], ['legacy', 'following', 'implicit', 'final'])
        self.assertEqual(s.functions[0].header_style, 'knr')
        self.assertEqual(s.functions[0].metrics['temporary_refs'], 3)
        self.assertEqual(s.functions[1].calls, {'legacy'})

    def test_headers_under_src_are_scanned_once(self):
        with tempfile.TemporaryDirectory(dir=HERE) as tmp:
            root = Path(tmp)
            (root / 'src').mkdir()
            (root / 'src/local.h').write_text('static inline int header_helper(void) { return 0; }')
            (root / 'src/a.c').write_text('#include "local.h"\nvoid f(void) {}')
            ss, fs, _, _ = score.scan(root)
            self.assertEqual(len(ss), 2)
            self.assertEqual([f.symbol for f in fs], ['f', 'header_helper'])

    def test_source_symlink_refused(self):
        with tempfile.TemporaryDirectory(dir=HERE) as tmp:
            root = Path(tmp)
            (root / 'src').mkdir()
            (root / 'real.c').write_text('void f(void) {}')
            (root / 'src/link.c').symlink_to(root / 'real.c')
            with self.assertRaisesRegex(ValueError, 'symlink refused'):
                score.scan(root)

    def test_cli_nonzero_for_bad_delimiters(self):
        with tempfile.TemporaryDirectory(dir=HERE) as tmp:
            root = Path(tmp)
            (root / 'src').mkdir()
            (root / 'src/bad.c').write_text('void broken(void) {')
            self.assertEqual(score.main(['--schema', 'v1', '--root', str(root), '--out', 'out', '--workers', '1']), 1)


if __name__ == '__main__':
    unittest.main()
