"""debt_check --macro-casts: a report of the casts file-local macro bodies add at each use site.

    python3 -m unittest tools/lint/test_debt_check.py
"""
from pathlib import Path
import contextlib
import io
import json
import os
import sys
import tempfile
import unittest
from unittest.mock import patch

HERE = Path(__file__).resolve().parent
sys.path.insert(0, str(HERE))
import debt_check as D  # noqa: E402

SOURCE = r'''
#define U8(p, o) (*(u8 *)((u8 *)(p) + (o)))
#define F(p, t, o) (*(t)((u8 *)(p) + (o)))
#define LIMIT 4
#define BASE ((u8 *)0x1F800000)
#define HEADER_FLAGS(p) U8(p, -2)

void use(ActorRecord *body, u8 *raw)
{
    U8(body, 0x9B) = 1;
    F(body, s16 *, 0x2A) = F((u8 *)raw, u16 *, 4);
    body->x = (s32)LIMIT;
    HEADER_FLAGS(body) |= 1;
    *(BASE + 4) = 0;
    body->U8 = 0;
}
#undef U8
#define U8 plain
void after(void)
{
    s32 U8 = 0;
}
'''


class MacroCastReport(unittest.TestCase):
    def test_cached_access_sites_summary(self):
        with tempfile.TemporaryDirectory() as td:
            path = Path(td) / 'access_sites.tsv'
            path.write_text('base_kind\tstatus\tagreement\n'
                            'named record\tmapped\t1\n'
                            'named record\tunmapped\t0\n'
                            'view\tmapped\t0\n')
            report = D.access_summary_from_sites(path)
        self.assertEqual((report['source_sites'], report['mapped'], report['agreement']),
                         (3, 2, 1))
        self.assertEqual(report['source_by_kind']['named record'], 2)
        self.assertIn('1/2\t50.00%', D.access_report_lines(report)[0])

    def test_access_summary_is_report_only(self):
        lines = D.access_report_lines({'source_sites': 8, 'mapped': 4, 'agreement': 3,
                                       'by_kind': {'view': 1, 'named record': 3},
                                       'source_by_kind': {'view': 4, 'named record': 4}})
        self.assertIn('3/4\t75.00%', lines[0])
        self.assertIn('4/8', lines[1])
        self.assertIn('1/4\t25.00%', next(line for line in lines if 'view coverage' in line))

    def scopes(self, text, flag):
        return D.analyze('src/test/example.c', text, flag)['scopes']

    def test_counts_per_use(self):
        use = self.scopes(SOURCE, True)['use#1']
        hidden = use['macro_casts']
        # U8: 2; F twice: 2 each (the type argument is a pointer cast once substituted);
        # HEADER_FLAGS: 0 of its own + nested U8 2; BASE: 1; LIMIT and member `->U8` add nothing
        self.assertEqual(hidden['macro:U8'], 2)
        self.assertEqual(hidden['macro:F'], 4)
        self.assertEqual(hidden['macro:HEADER_FLAGS'], 2)
        self.assertEqual(hidden['macro:BASE'], 1)
        self.assertEqual(hidden['macro_casts'], 9)
        self.assertEqual(hidden['macro_uses'], 5)
        # `(u8 *)raw` is written at the use site: a counted cast, not a hidden one
        self.assertEqual(use['counts']['pointer_casts'], 1)

    def test_undef_and_redefinition(self):
        after = self.scopes(SOURCE, True)['after#1']
        self.assertEqual(after['macro_casts'], {})

    def test_counted_classes_unchanged(self):
        plain = self.scopes(SOURCE, False)
        report = self.scopes(SOURCE, True)
        for key in plain:
            self.assertEqual(plain[key]['counts'], report[key]['counts'])
            self.assertNotIn('macro_casts', plain[key])

    def test_census_outputs(self):
        with tempfile.TemporaryDirectory() as td:
            root = Path(td)
            (root / 'src/test').mkdir(parents=True)
            (root / 'src/test/example.c').write_text(SOURCE)
            plain = D.census(root)
            report = D.census(root, macro_casts=True)
            self.assertEqual(plain['by_class'], report['by_class'])
            self.assertNotIn('macro_casts_report', plain)
            self.assertEqual(report['macro_casts_report']['casts'], 9)
            self.assertEqual(report['macro_casts_report']['uses'], 5)
            D.write_outputs(root / 'out', report)
            rows = (root / 'out/debt_macro_casts.tsv').read_text().splitlines()
            self.assertEqual(rows[1].split('\t')[:6], ['src/test/example.c', 'use#1', '8', '1', '9', '5'])
            D.write_outputs(root / 'plain', plain)
            self.assertFalse((root / 'plain/debt_macro_casts.tsv').exists())

    def test_summary_cache_uses_content_and_invalidates_on_header_change(self):
        with tempfile.TemporaryDirectory() as td:
            root = Path(td)
            (root / 'src/test').mkdir(parents=True)
            (root / 'include').mkdir()
            source = root / 'src/test/example.c'
            header = root / 'include/example.h'
            source.write_text('#include "example.h"\nvoid f(void) { }\n')
            header.write_text('#define MARK 1\n')
            cache = root / 'out/cache'
            original = D.analyze
            with patch.object(D, 'analyze', wraps=original) as analyze:
                first = D.census(root, ['src/test/example.c'], True, cache)
                second = D.census(root, ['src/test/example.c'], True, cache)
                self.assertEqual(first, second)
                self.assertEqual(analyze.call_count, 1)
                header.write_text('#define MARK 2\n')
                D.census(root, ['src/test/example.c'], True, cache)
                self.assertEqual(analyze.call_count, 2)
                source.write_text('#include "example.h"\nvoid f(void) { int x; }\n')
                D.census(root, ['src/test/example.c'], True, cache)
                self.assertEqual(analyze.call_count, 3)

    def test_reachable_header_macros_and_local_shadow(self):
        with tempfile.TemporaryDirectory() as td:
            root = Path(td)
            (root / 'include/shared').mkdir(parents=True)
            (root / 'src/test').mkdir(parents=True)
            (root / 'include/shared/object_node.h').write_text('''
#define NODE_HEADER(body) ((ObjectNodeHeader *)(body) - 1)
#define NODE_BODY(node) ((void *)((ObjectNodeHeader *)(node) + 1))
#define H_FWD(body) NODE_HEADER(body)
#define HEADER_BASE ((u8 *)0)
''')
            (root / 'include/nested.h').write_text('#include "shared/object_node.h"\n')
            (root / 'src/test/example.c').write_text('''
#include "nested.h"
#define WRAP(body) H_FWD(body)
void use(void *body, void *node) {
    NODE_HEADER(body);
    NODE_BODY(node);
    WRAP(body);
    HEADER_BASE;
    NODE_HEADER((u8 *)body);
}
#undef NODE_HEADER
#define NODE_HEADER(body) (body)
void shadow(void *body) { NODE_HEADER(body); }
''')
            report = D.census(root, macro_casts=True)
            self.assertEqual(report['header_macro_casts_report']['casts'], 6)
            self.assertEqual(report['header_macro_casts_report']['uses'], 5)
            self.assertEqual(report['macro_casts_report']['casts'], 0)
            self.assertEqual(report['by_class']['pointer_casts'], 1)
            self.assertEqual(report['by_function']['src/test/example.c']['shadow#1']['header_macro_casts'], {})
            baseline = D.baseline_record(report)
            self.assertEqual(baseline['report_counts'],
                             {'file_local_macro_casts': 0, 'header_macro_casts': 6,
                              'signedness_unions': 0, 'unions_total': 0,
                              'generic_index_views': 0,
                              'address_named_types': 0,
                              'source_local_single_function_types': 0})
            D.validate_baseline(json.loads(D.baseline_text(baseline)))
            D.write_outputs(root / 'out', report)
            rows = (root / 'out/debt_header_macro_casts.tsv').read_text().splitlines()
            self.assertEqual(len(rows), 2)
            self.assertIn('NODE_HEADER=2', rows[1])


class BytesMarkerScope(unittest.TestCase):
    def test_control_statement_marker_exempts_only_its_condition(self):
        text = ('int f(int *p, int **q) {\n'
                '    /* BYTES: retail compares the pair as one halfword */\n'
                '    if (*(unsigned short *)p == 1) {\n'
                '        *(char **)q = 0;\n'
                '        goto done;\n'
                '    }\n'
                'done:\n'
                '    return 0;\n'
                '}\n')
        result = D.analyze('src/test/example.c', text)
        counts = result['scopes']['f#1']['counts']
        self.assertEqual(counts.get('pointer_casts', 0), 1)  # the body cast still counts; the condition cast is exempt
        self.assertEqual(counts.get('goto', 0), 1)
        self.assertEqual(result['markers'], 1)


class SignViewRatchet(unittest.TestCase):
    def test_generic_index_views_are_code_only_and_ratchet(self):
        source = '''
void use(ScratchPad *p, Record *r) {
    p->sw[2] = p->h[1];
    r->bytes[0] = 1;
    // p->b[0]
    const char *s = "r->bytes[3]";
}
'''
        with tempfile.TemporaryDirectory() as td:
            root = Path(td)
            (root / 'src/test').mkdir(parents=True)
            path = root / 'src/test/views.c'
            path.write_text(source)
            report = D.census(root, macro_casts=True)
            self.assertEqual(report['generic_index_views_report']['count'], 3)
            baseline = D.baseline_record(report)
            self.assertEqual(D.check_baseline(report, baseline), [])
            path.write_text(source.replace('p->sw[2]', 'p->sw[2] + p->b[0]'))
            changed = D.census(root)
            self.assertTrue(any('generic_index_views 4 > baseline 3' in p
                                for p in D.check_baseline(changed, baseline)))

    def test_generic_index_covers_dot_members_and_ints(self):
        source = 'p.b[0] = p.w[1] + p.Ints[2] + Ints[3]; // p.b[4]\n'
        self.assertEqual(D.generic_index_views(source), 4)
        self.assertEqual(D.generic_index_views('a->unk_B4.signed_bytes[2] = p.signed_halves[1];\n'), 2)

    def test_named_signedness_views_count(self):
        with tempfile.TemporaryDirectory() as td:
            root = Path(td)
            (root / 'src/test').mkdir(parents=True)
            (root / 'include').mkdir()
            (root / 'src/test/named.c').write_text('''
void use(Pos *p) {
    p->x.unsigned_parts.integer = 1;
    p->y.signed_halves.low = p->z.unsigned_word;
    p->parts.camera = 2;
    // p->x.unsigned_parts.fraction
}
''')
            report = D.census(root)
            self.assertEqual(report['by_class']['sign_views'], 3)
            self.assertEqual(report['sign_views_report']['named_sign_views'], 3)

    def test_local_externs_split(self):
        text = ('extern s32 named_value;\nextern s32 D_80012345;\nextern void named_call(s32 x);\n'
                'extern void func_80012345();\nvoid unqualified_proto(void);\nextern void (*callback)(void);\n'
                'extern s32 mixed_value, mixed_call(void);\nextern s32 defined_here = 1;\n'
                'extern u8 aligned_table[4] __attribute__((aligned(4)));\n'
                'void body(void)\n{\n    extern s32 D_80099999;\n    named_call(0);\n}\n')
        res = D.analyze('src/a.c', text)
        self.assertEqual(sum(r['counts']['local_externs'] for r in res['scopes'].values()), 9)
        self.assertEqual(res['extern_split'], dict(named_data=3, D_data=2, named_functions=2, func_functions=1,
                                                   mixed=1))
        with tempfile.TemporaryDirectory() as td:
            root = Path(td)
            (root / 'src').mkdir()
            (root / 'src/a.c').write_text(text)
            summary = D.census(root)
            self.assertEqual(summary['local_externs_split_report']['named_data'], 3)
            self.assertEqual(sum(v for k, v in summary['local_externs_split_report'].items() if k != 'note'),
                             summary['by_class']['local_externs'])
            self.assertNotIn('local_externs_split_report', D.baseline_record(summary))

    def test_report_cache_dir_is_outside_tracked_out(self):
        root = Path('/r')
        with patch.dict(os.environ, {}, clear=False):
            os.environ.pop('XDG_CACHE_HOME', None)
            self.assertEqual(D.report_cache_dir(root), root / 'build/debt_report_cache')
            self.assertEqual(D.report_cache_dir(root, Path('/c')), Path('/c'))
            os.environ['XDG_CACHE_HOME'] = '/xdg'
            self.assertEqual(D.report_cache_dir(root).parent, Path('/xdg/debt_check'))

    def test_summary_does_not_create_out(self):
        with tempfile.TemporaryDirectory() as td:
            root = Path(td)
            (root / 'src/test').mkdir(parents=True)
            (root / 'include').mkdir()
            (root / 'src/test/a.c').write_text('void f(void) { }\n')
            with patch.dict(os.environ, {}, clear=False):
                os.environ.pop('XDG_CACHE_HOME', None)
                with contextlib.redirect_stdout(io.StringIO()):
                    D.main(['--root', str(root), '--out', str(root / 'build/debt'), '--summary'])
            self.assertFalse((root / 'out').exists())
            self.assertTrue((root / 'build/debt_report_cache').is_dir())

    def test_views_union_labels_and_new_site(self):
        with tempfile.TemporaryDirectory() as td:
            root = Path(td)
            (root / 'src/test').mkdir(parents=True)
            (root / 'include').mkdir()
            (root / 'src/test/views.c').write_text('''
void use(View *v) {
    v->a.s = v->a.u;
    v->as_s16 = v->whole;
    v->halves = v->signed_bytes;
    // v->not_code.s
}
''')
            header = root / 'include/views.h'
            header.write_text('''
typedef struct V {
    union { u16 s; s16 u; } inverted;
    union { s16 s; s16 u; } repeated;
    union { s16 s; u16 u; } correct;
} V;
''')
            report = D.census(root, macro_casts=True)
            self.assertEqual(report['by_class']['sign_views'], 6)
            self.assertEqual(report['sign_views_report']['s_u'], 2)
            self.assertEqual(report['sign_views_report']['as_signedness'], 1)
            self.assertEqual(report['sign_views_report']['other_width_views'], 3)
            self.assertEqual(report['signedness_unions_report']['count'], 2)
            self.assertEqual(report['union_definitions_report']['count'], 3)
            self.assertEqual({r['site'] for r in report['bad_label_unions']},
                             {'include/views.h::V.inverted#1', 'include/views.h::V.repeated#1'})
            baseline = D.baseline_record(report)
            self.assertEqual(D.check_baseline(report, baseline), [])
            header.write_text(header.read_text().replace('} V;',
                              '    union { u16 s; s16 u; } newly_bad;\n} V;'))
            changed = D.census(root)
            self.assertTrue(any('newly_bad' in p for p in D.check_baseline(changed, baseline)))
            self.assertTrue(any('signedness_unions 3 > baseline 2' in p
                                for p in D.check_baseline(changed, baseline)))
            self.assertTrue(any('unions_total 4 > baseline 3' in p
                                for p in D.check_baseline(changed, baseline)))

    def test_char_spelled_unions_are_signedness_unions(self):
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            (root / 'src/test').mkdir(parents=True)
            (root / 'include').mkdir()
            (root / 'src/test/use.c').write_text('void f(void) {}\n')
            (root / 'include/chars.h').write_text('''
typedef struct C {
    union { char s; unsigned char u; } plain;
    union { signed char s; u8 u; } spelled;
    union { unsigned char a; u8 b; } same;
} C;
''')
            report = D.census(root)
            self.assertEqual(report['signedness_unions_report']['count'], 2)
            self.assertEqual(report['union_definitions_report']['count'], 3)

    def test_relabelling_retires_a_known_bad_site(self):
        text = 'typedef struct V { union { u16 s; s16 u; } field; } V;'
        _, bad = D.union_sites('include/test.h', text)
        self.assertEqual(len(bad), 1)
        _, fixed = D.union_sites('include/test.h', text.replace('u16 s; s16 u', 'u16 u; s16 s'))
        self.assertEqual(fixed, [])

    def test_bad_label_key_survives_earlier_same_named_retirement(self):
        text = '''
typedef struct First { union { u16 s; s16 u; } field; } First;
typedef struct Second { union { u16 s; s16 u; } field; } Second;
'''
        _, before = D.union_sites('include/test.h', text)
        _, after = D.union_sites('include/test.h', text.replace(
            'typedef struct First { union { u16 s; s16 u; } field; } First;',
            'typedef struct First { u16 field; } First;'))
        self.assertEqual(before[1]['site'], after[0]['site'])
        self.assertEqual(after[0]['site'], 'include/test.h::Second.field#1')

    def test_bad_label_key_includes_nested_member_path(self):
        text = '''
typedef struct Outer {
    struct { union { u16 s; s16 u; } field; } first;
    struct { union { u16 s; s16 u; } field; } second;
} Outer;
'''
        _, before = D.union_sites('include/test.h', text)
        _, after = D.union_sites('include/test.h', text.replace(
            'struct { union { u16 s; s16 u; } field; } first;',
            'struct { u16 field; } first;'))
        self.assertEqual(before[1]['site'], after[0]['site'])
        self.assertEqual(after[0]['site'], 'include/test.h::Outer.second.field#1')

    def test_different_array_types_are_not_duplicates(self):
        text = 'union { u8 small[2]; u8 large[4]; } bytes;'
        _, bad = D.union_sites('include/test.h', text)
        self.assertEqual(bad, [])

    def test_pointer_and_function_pointer_labels(self):
        text = '''
union { void *s; u8 *u; } data;
union { void (*s)(); void (*handler)(); } callback;
union { s16 *s; u16 *u; } signed_pointers;
union { u8 *p; u32 *p2; } ribbon;
'''
        _, bad = D.union_sites('include/test.h', text)
        self.assertEqual({row['site'] for row in bad},
                         {'include/test.h::test.data#1', 'include/test.h::test.callback#1',
                          'include/test.h::test.signed_pointers#1', 'include/test.h::test.ribbon#1'})
        self.assertIn('pointer_s', bad[0]['reasons'])
        self.assertIn('pointer_pun', bad[-1]['reasons'])

    def test_view_inventory_counts_aliases_and_function_users(self):
        with tempfile.TemporaryDirectory() as td:
            root = Path(td)
            (root / 'src/test').mkdir(parents=True)
            (root / 'include').mkdir()
            (root / 'include/types.h').write_text('typedef struct { int x; } Rec_D_80001234;\n')
            (root / 'src/test/views.c').write_text('''
typedef struct { int x; } LocalView;
typedef union { int x; float f; } SharedView;
typedef struct { int x; } B22_8000ABCD;
void first(void) { LocalView a; SharedView b; B22_8000ABCD c; }
void second(void) { SharedView b; }
''')
            report = D.census(root)
            self.assertEqual(report['view_inventory_report']['address_named_types'], 2)
            self.assertEqual(report['view_inventory_report']['source_local_single_function_types'], 1)
            by_name = {row['name']: row for row in report['typedef_view_sites']}
            self.assertEqual(by_name['LocalView']['users'], ['first#1'])
            self.assertEqual(by_name['SharedView']['users'], ['first#1', 'second#1'])


class UnionInventory(unittest.TestCase):
    def setUp(self):
        self.row = {'id': 'src/test.c::V.x', 'members': [{'name': 's', 'type': 's16'}],
                    'status': 'unproven', 'evidence': 'lexical'}
        self.base = {'count': 1, 'ids': [self.row['id']]}

    def test_baseline_ids_length(self):
        bad = dict(self.base, ids=[])
        self.assertTrue(any('ids length' in p for p in D.check_union_inventory([self.row], [self.row], bad)))

    def test_missing_nonretired_and_orphan(self):
        self.assertTrue(any('orphan non-retired' in p
                            for p in D.check_union_inventory([], [self.row], self.base)))
        retired = dict(self.row, status='retired')
        self.assertEqual(D.check_union_inventory([], [retired], self.base), [])

    def test_live_candidate_and_missing_candidate(self):
        candidate = dict(self.row, status='retire_candidate')
        self.assertEqual(D.check_union_inventory([self.row], [candidate], self.base), [])
        self.assertTrue(any('orphan non-retired' in p for p in
                            D.check_union_inventory([], [candidate], self.base)))

    def test_reintroduction_uses_status_and_baseline_membership(self):
        retired = dict(self.row, status='retired', evidence='wording unrelated to retirement')
        self.assertTrue(any('retired union definition still present' in p for p in
                            D.check_union_inventory([self.row], [retired], self.base)))
        bad = {'count': 1, 'ids': ['src/test.c::Other.x']}
        self.assertTrue(any('retired union reintroduced' in p
                            for p in D.check_union_inventory([self.row], [retired], bad)))


if __name__ == '__main__':
    unittest.main()
