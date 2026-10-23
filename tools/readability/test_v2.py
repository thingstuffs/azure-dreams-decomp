"""Meaningful detector, registry and end-to-end regression contracts for v2."""
import contextlib
import csv
import io
import json
from pathlib import Path
import subprocess
import sys
import tempfile
import unittest

HERE = Path(__file__).resolve().parent
sys.path.insert(0, str(HERE))
import score as v1
import v2

REGISTRY_PATH = HERE.parents[1] / 'ledger/readability_oddities.jsonl'
REGISTRY = v2.load_registry(REGISTRY_PATH)


def source(text, path='src/test/example.c', registry=REGISTRY):
    return v2.analyze_source(path, text.encode(), registry)


def block(prefix='a', count=8):
    return '\n'.join(f'{prefix}{i} = step({i + 2});' for i in range(count))


def output_bytes(folder):
    return {p.relative_to(folder).as_posix(): p.read_bytes() for p in folder.rglob('*.tsv')}


class DetectorTests(unittest.TestCase):
    def test_fixture_every_category(self):
        s = v2.analyze_source('src/test/debt.c', (HERE / 'fixtures/debt_v2.c').read_bytes(), REGISTRY)
        self.assertFalse(s.warnings)
        self.assertEqual([f.symbol for f in s.functions], ['debt', 'uses_types'])
        f, g = s.functions
        expected = dict(macro_offsets=10, member_byte_views=1, fixed_address_casts=4,
                        local_type_users=1, sign_extension_idioms=2, do_while_wrappers=1,
                        double_scalar_casts=1, hex_state_literals=2, hex_timer_literals=2,
                        duplicate_lines=0, offset_macros_score=80, byte_views_score=8,
                        fixed_addresses_score=32, local_types_score=12, sign_extension_score=6,
                        wrappers_score=3, double_casts_score=3, hex_states_score=8)
        for key, value in expected.items():
            self.assertEqual(f.metrics[key], value, key)
        self.assertEqual(g.metrics['local_type_users'], 3)
        self.assertEqual(len(s.type_debts), 4)
        self.assertEqual(sum(f.metrics[c + '_score'] for c in REGISTRY.categories), f.metrics['score'])
        legacy = v1.analyze_source(s.path, (HERE / 'fixtures/debt_v2.c').read_bytes()).functions[0]
        for key in v1.METRICS + v1.SCORES[:-1]:
            self.assertEqual(f.metrics[key], legacy.metrics[key], key)
        self.assertEqual(f.metrics['v1_score'], legacy.metrics['score'])
        scratch = [h for h in f.oddities if h['pattern_id'] == 'fixed_address' and h['detail'].startswith('scratchpad')]
        self.assertEqual(len(scratch), 2)
        for h in f.oddities:
            self.assertLessEqual(h['line'], h['end_line'])

    def test_literals_comments_directives_and_member_calls_excluded(self):
        s = source('''#define WRAP do { U8(p, 0x20); } while (0)
#define CONT \\\nF(p, u8, 0x30)
/* typedef struct { u8 pad[4]; } Entity; */
void f(void) {
 char *s = "U8(p,0x20) (x << 16) >> 16 state=0x14 (u8 *)0x1F800000";
 char c = '}';
 object->U8(p, 0x40);
 // PTR(p,0x60); do {} while (0);
}
''')
        self.assertEqual(len(s.functions), 1)
        for p in REGISTRY.patterns:
            self.assertEqual(s.functions[0].metrics[p.metric], 0, p.metric)
        self.assertEqual(s.type_debts, [])

    def test_macro_argument_parser_not_substring_matching(self):
        f = source('''void f(void) {
 a=F(owner(a,b),u8,(-0x20UL)); b=U8(p, 0); c=PTR(p, +24);
 d=U32_AT(p, ((0x24))); e=NOT_U8(p,0x20); f=U8(p,n+0x20);
 g=F(p,u8,offset); h=U8(p); i=PTR(p,0x20,extra);
}''').functions[0]
        self.assertEqual(f.metrics['macro_offsets'], 4)

    def test_fixed_address_boundaries_and_non_addresses(self):
        f = source('''void f(void) {
 p=(u8 *)(0x1F800000U); p=(u8 *)0x1F8003FF;
 p=(u8 *)0x1F800400; p=(u8 *)0x1F7FFFFF; p=(u8 *)-0x1F800020;
 p=(void *)0; p=(void *)1; p=(void *)-1;
 n=sizeof(s32 *); p=(u8 *)(base+0x20); p=(u8 *)2.0;
}''').functions[0]
        self.assertEqual(f.metrics['fixed_address_casts'], 5)
        hits = [h for h in f.oddities if h['pattern_id'] == 'fixed_address']
        self.assertEqual(sum(h['detail'].startswith('scratchpad') for h in hits), 2)

    def test_byte_view_counted_once_with_or_without_offset(self):
        f = source('''void f(void *p) {
 a=(u8 *)&x->unk_10+1; b=((unsigned char *)&x->word)-3;
 c=(u8 *)&(x->word); d=(u16 *)&x->word; e=(u8 *)p+0x20;
 f=(u8 *)&p; g=(u8 *)x->word;
}''').functions[0]
        self.assertEqual(f.metrics['member_byte_views'], 3)
        self.assertEqual(f.metrics['raw_offsets'], 3)

    def test_shift_and_cast_noise_exclusions_and_hex(self):
        f = source('''void f(void) {
 a=((x<<0x10UL))>>16; b=(x<<16)>>8; c=(x<<16)+y>>16;
 x <<= 16; x >>= 0x10; y=x<<16; z>>=16;
 x=(s32)(s16)y; x=(signed int)(signed short int)y;
 x=(int32_t)(int16_t)y; x=(u32)(u16)y;
 do {} while ((0U)); do {} while (false); do {} while (x==0);
}''').functions[0]
        self.assertEqual(f.metrics['sign_extension_idioms'], 2)
        self.assertEqual(f.metrics['double_scalar_casts'], 3)
        self.assertEqual(f.metrics['do_while_wrappers'], 1)

    def test_local_types_forward_aliases_and_per_function_count(self):
        s = source('''typedef struct Entity Entity;
struct Entity { u8 pad[8]; s32 unk_08; };
typedef struct { s32 x; } Actor;
typedef struct { s32 padding; } Position;
typedef struct { s32 unk_00; } Rec_unused;
void f(Entity *a) { Entity *b = a; Entity *c = b; }
void g(void) { typedef struct { u8 pad[4]; } Rec_inside; Rec_inside x; }
void h(void) { Rec_inside(); }
''')
        self.assertEqual(len(s.type_debts), 3)
        self.assertEqual([f.metrics['local_type_users'] for f in s.functions], [1, 1, 0])
        self.assertEqual(sum(not d['users'] for d in s.type_debts), 1)
        self.assertEqual([f.symbol for f in s.functions], ['f', 'g', 'h'])

    def test_local_type_member_not_array_expression_or_string(self):
        s = source('''typedef struct { s32 array[unk_size]; const char *name; s32 unknown; } Entity;
void f(Entity *p) { const char *s="pad_00"; }
''')
        self.assertEqual(s.type_debts, [])
        self.assertEqual(s.functions[0].metrics['local_type_users'], 0)

    def test_hex_states_timers_separate_and_no_correctness_judgment(self):
        f = source('''void f(void) {
 p->state=0x14; state = 0x0; currentState=0x1; if(timer>=0x79) {}
 if (0x40 <= p->countdown) {} if (TIMEr == (0x20U)) {}
 flag=0x14; lifetime=0x79; state=20; timer=121;
 state=0x14+1; timer=(mask&0x80); state_mask&=0x10;
}''').functions[0]
        self.assertEqual(f.metrics['hex_state_literals'], 3)
        self.assertEqual(f.metrics['hex_timer_literals'], 3)
        self.assertEqual(f.metrics['hex_states_score'], 12)

    def test_hex_named_operand_not_names_in_indices_calls_or_other_fields(self):
        f = source('''void f(void) {
 state->flags=0x20; table[state]=0x14; call(timer)==0x79;
 if (state+mask==0x14) {} if ((timer) >= (0x79)) {}
 if ((p->state) == 0x14) {} p->timer[index]=0x20;
}''').functions[0]
        self.assertEqual(f.metrics['hex_state_literals'], 1)
        self.assertEqual(f.metrics['hex_timer_literals'], 2)

    def test_hex_named_initializers_and_nested_assignments(self):
        f = source('''void f(void) {
 s16 state = 0x14; const unsigned int timer = 0x79;
 p->state = next_state = 0x20; if (state == (timer = 0x10)) {}
}''').functions[0]
        self.assertEqual(f.metrics['hex_state_literals'], 2)
        self.assertEqual(f.metrics['hex_timer_literals'], 2)

    def test_corridor_fixture_partial_third_loop_and_evidence_spans(self):
        data = (HERE / 'fixtures/clones_v2.c').read_bytes()
        s = v2.analyze_source('src/test/clones.c', data, REGISTRY)
        f = s.functions[0]
        rows = v2.count_duplicates([f], REGISTRY)
        self.assertEqual(f.metrics['duplicate_lines'], 34)
        self.assertTrue(all(r['function_id'] == f.key == r['reference_id'] for r in rows))
        lines = data.decode().splitlines()
        for r in rows:
            actual = ' '.join(t.value for t in v1.lex('\n'.join(lines[r['line'] - 1:r['end_line']])))
            reference = ' '.join(t.value for t in v1.lex('\n'.join(lines[r['reference_line'] - 1:r['reference_end_line']])))
            self.assertEqual(actual, reference)

    def test_duplicate_threshold_and_single_function_union(self):
        for size, expected in ((7, 0), (8, 8), (12, 12)):
            text = 'void f(void) {\n' + block(count=size) + '\nseparator();\n' + block(count=size) + '\n}'
            f = source(text).functions[0]
            rows = v2.count_duplicates([f], REGISTRY)
            self.assertEqual(f.metrics['duplicate_lines'], expected)
            self.assertEqual(f.metrics['duplicates_score'], 2 * expected)
            if expected:
                self.assertTrue(rows)
                self.assertTrue(all(r['matched_lines'] >= 8 for r in rows))

    def test_cross_file_clones_canonical_first_and_whitespace_comments(self):
        a = source('void a(void) {\n' + block(count=12) + '\n}', 'src/a/a.c').functions[0]
        b = source('void b(void) {\n/* ignored */\n' + block(count=12).replace(' = ', '=') + '\n}', 'src/b/b.c').functions[0]
        c = source('void c(void) {\n' + block(count=12) + '\n}', 'src/c/c.c').functions[0]
        rows = v2.count_duplicates([c, b, a], REGISTRY)
        self.assertEqual([f.metrics['duplicate_lines'] for f in (a, b, c)], [0, 12, 12])
        self.assertTrue(all(r['reference_id'] == a.key for r in rows))

    def test_duplicate_literals_and_identifiers_retained_braces_excluded(self):
        a = source('void a(void) {\n' + block(count=8) + '\n}').functions[0]
        b = source('void b(void) {\n' + block('b', count=8) + '\n}').functions[0]
        c = source('void c(void) {\n' + block(count=8).replace('step(5)', 'step(99)') + '\n}').functions[0]
        d = source('void d(void) {\n' + '\n'.join('{\n}' for _ in range(9)) + '\n}').functions[0]
        self.assertFalse(v2.count_duplicates([a, b, c, d], REGISTRY))
        self.assertTrue(all(f.metrics['duplicate_lines'] == 0 for f in (a, b, c, d)))

    def test_overlapping_repetitions_do_not_multiply_lines(self):
        f = source('void f(void) {\n' + '\n'.join('step();' for _ in range(24)) + '\n}').functions[0]
        v2.count_duplicates([f], REGISTRY)
        self.assertEqual(f.metrics['duplicate_lines'], 16)


class RegistryTests(unittest.TestCase):
    def write_registry(self, root, records):
        path = root / 'patterns.jsonl'
        path.write_text(''.join(json.dumps(r) + '\n' for r in records))
        return path

    def custom(self):
        return dict(id='future_pattern', category='future', metric='future_uses', weight=7,
                    regex=r'\bOBSCURE\s*\(', example='OBSCURE(p)', why='Review this new spelling.', owner_decision=None)

    def test_append_regex_automatically_scores_documents_and_queues(self):
        with tempfile.TemporaryDirectory(dir=HERE) as tmp:
            root = Path(tmp)
            records = [json.loads(r) for r in REGISTRY_PATH.read_text().splitlines()]
            registry = v2.load_registry(self.write_registry(root, records + [self.custom()]))
            s = source('void f(void) { OBSCURE(p); /* OBSCURE(p) */ s="OBSCURE(p)"; }', registry=registry)
            f = s.functions[0]
            self.assertEqual(f.metrics['future_uses'], 1)
            self.assertEqual(f.metrics['future_score'], 7)
            v2.write_outputs(root / 'out', 'fixture', [s], [f], [], [], [], registry)
            self.assertIn('future', (root / 'out/trend.tsv').read_text())
            self.assertIn('future_pattern', (root / 'out/oddities.tsv').read_text())
            self.assertEqual(len((root / 'out/queue/future.tsv').read_text().splitlines()), 2)
            self.assertIn('future_pattern', v2.render_docs('fixture', [s], [f], [], [], registry))

    def test_registry_validation_rejects_malformed_or_ambiguous_records(self):
        base = self.custom()
        variants = [dict(base, weight=0), dict(base, weight=True), dict(base, detector='eval'),
                    dict(base, regex='.*'), dict(base, regex='['), dict(base, category='offsets'),
                    dict(base, metric='score'), dict(base, id='Bad Name'), dict(base, options={'exec':'bad'}),
                    {k: v for k, v in base.items() if k != 'owner_decision'}, dict(base, extra='bad')]
        with tempfile.TemporaryDirectory(dir=HERE) as tmp:
            root = Path(tmp)
            for rec in variants:
                with self.subTest(rec=rec), self.assertRaises(ValueError):
                    v2.load_registry(self.write_registry(root, [rec]))
            with self.assertRaisesRegex(ValueError, 'duplicate id'):
                v2.load_registry(self.write_registry(root, [base, base]))
            with self.assertRaisesRegex(ValueError, 'one metric'):
                v2.load_registry(self.write_registry(root, [base, dict(base, id='other', weight=3)]))
            with self.assertRaisesRegex(ValueError, 'empty'):
                v2.load_registry(self.write_registry(root, []))


class EndToEndTests(unittest.TestCase):
    def make_root(self, root):
        (root / 'src/test').mkdir(parents=True)
        (root / 'ledger').mkdir()
        (root / 'ledger/readability_oddities.jsonl').write_bytes(REGISTRY_PATH.read_bytes())
        (root / 'src/test/a.c').write_text('void f(void *p) { U8(p,0x24); }\nvoid g(void) { f(); f(); }')
        (root / 'src/test/b.c').write_text('void h(void) {\n' + block() + '\n}')
        (root / 'src/test/c.c').write_text('void j(void) {\n' + block() + '\n}')
        (root / 'src/test/data.c').write_text('int data = 3;')
        (root / 'src/test/local.h').write_text('static int helper(void) { return 0; }')

    def test_worker_determinism_conservation_and_v1_field_equivalence(self):
        with tempfile.TemporaryDirectory(dir=HERE) as tmp:
            root = Path(tmp)
            self.make_root(root)
            results = []
            for workers in (1, 2):
                ss, fs, edges, unresolved, clones = v2.scan(root, REGISTRY, workers)
                out = root / f'v2_{workers}'
                v2.write_outputs(out, 'fixture', ss, fs, edges, unresolved, clones, REGISTRY)
                results.append(output_bytes(out))
            self.assertEqual(results[0], results[1])
            legacy_sources, legacy_fs, legacy_edges, legacy_unresolved = v1.scan(root)
            self.assertEqual(edges, legacy_edges)
            self.assertEqual(unresolved, legacy_unresolved)
            self.assertEqual([(s.path, s.sha256) for s in ss], [(s.path, s.sha256) for s in legacy_sources])
            for f, legacy in zip(fs, legacy_fs):
                self.assertEqual(f.key, legacy.key)
                self.assertEqual(f.anchor, legacy.anchor)
                self.assertEqual(f.metrics['v1_score'], legacy.metrics['score'])
                for metric in v1.METRICS + v1.SCORES[:-1]:
                    self.assertEqual(f.metrics[metric], legacy.metrics[metric], metric)
            with (out / 'trend.tsv').open() as stream:
                trend = list(csv.DictReader(stream, delimiter='\t'))
            self.assertEqual(sum(int(r['weighted_debt']) for r in trend), sum(f.metrics['score'] for f in fs))
            self.assertEqual(sum(r['score'] for r in v2.summarize(ss, fs, lambda p:p.split('/')[1], REGISTRY)),
                             sum(f.metrics['score'] for f in fs))
            with (out / 'queue/offset_macros.tsv').open() as stream:
                row = next(csv.DictReader(stream, delimiter='\t'))
            self.assertEqual((row['category_score'], row['known_callers'], row['payoff']), ('8', '1', '8'))
            self.assertNotIn(str(root), v2.render_docs('fixture', ss, fs, edges, unresolved, REGISTRY))

    def test_cli_default_v2_and_explicit_v1(self):
        with tempfile.TemporaryDirectory(dir=HERE) as tmp:
            root = Path(tmp)
            self.make_root(root)
            for schema in ('v1', 'v2'):
                cmd = [sys.executable, str(HERE / 'score.py'), '--schema', schema, '--root', str(root),
                       '--out', schema, '--workers', '1', '--revision', 'fixture', '--docs', schema + '.md']
                run = subprocess.run(cmd, text=True, capture_output=True)
                self.assertEqual(run.returncode, 0, run.stderr)
                self.assertIn('readability-' + schema, run.stdout)
            ss, fs, edges, unresolved = v1.scan(root)
            v1.write_outputs(root / 'direct', 'fixture', ss, fs, edges, unresolved)
            self.assertEqual(output_bytes(root / 'v1'), output_bytes(root / 'direct'))
            self.assertEqual((root / 'v1.md').read_text(), v1.render_docs('fixture', ss, fs, edges, unresolved))
            self.assertIn('score.py --schema v1 --root', (root / 'v1.md').read_text())
            with contextlib.redirect_stdout(io.StringIO()):
                self.assertEqual(v1.main(['--root', str(root), '--out', 'default', '--workers', '1']), 0)
            self.assertIn('readability-v2', (root / 'default/metadata.tsv').read_text())

    def test_invalid_registry_fails_instead_of_silent_undercount(self):
        with tempfile.TemporaryDirectory(dir=HERE) as tmp:
            root = Path(tmp)
            (root / 'src').mkdir()
            with contextlib.redirect_stderr(io.StringIO()):
                self.assertEqual(v2.main(['--root', str(root), '--workers', '1']), 2)

    def test_v2_warnings_and_symlinks(self):
        with tempfile.TemporaryDirectory(dir=HERE) as tmp:
            root = Path(tmp)
            self.make_root(root)
            (root / 'src/test/bad.c').write_text('void broken(void) {')
            with contextlib.redirect_stdout(io.StringIO()):
                self.assertEqual(v2.main(['--root', str(root), '--out', 'out', '--workers', '1']), 1)
            (root / 'src/test/link.c').symlink_to(root / 'src/test/a.c')
            with self.assertRaisesRegex(ValueError, 'symlink refused'):
                v2.scan(root, REGISTRY)

    def test_tidy_selection_is_absolute_and_deterministic(self):
        fs = [source('void f(void) { U8(p,0x20); }', path=f'src/test/{name}.c').functions[0]
              for name in ('b', 'a')]
        for f in fs:
            f.metrics['code_lines'] = 80
            f.metrics['v1_score'] = 100
            f.metrics['score'] = 108
        self.assertEqual([f.path for f in v2.tidy_misses(fs)], ['src/test/a.c', 'src/test/b.c'])
        fs[0].metrics['v1_score'] = 101
        self.assertEqual(len(v2.tidy_misses(fs)), 1)


if __name__ == '__main__':
    unittest.main()
