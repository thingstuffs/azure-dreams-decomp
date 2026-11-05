"""debt_check --macro-casts: a report of the casts file-local macro bodies add at each use site.

    python3 -m unittest tools/lint/test_debt_check.py
"""
from pathlib import Path
import json
import sys
import tempfile
import unittest

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
                              'address_named_types': 0,
                              'source_local_single_function_types': 0})
            D.validate_baseline(json.loads(D.baseline_text(baseline)))
            D.write_outputs(root / 'out', report)
            rows = (root / 'out/debt_header_macro_casts.tsv').read_text().splitlines()
            self.assertEqual(len(rows), 2)
            self.assertIn('NODE_HEADER=2', rows[1])


class SignViewRatchet(unittest.TestCase):
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
                             {'include/views.h::inverted#1', 'include/views.h::repeated#1'})
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

    def test_relabelling_retires_a_known_bad_site(self):
        text = 'typedef struct V { union { u16 s; s16 u; } field; } V;'
        _, bad = D.union_sites('include/test.h', text)
        self.assertEqual(len(bad), 1)
        _, fixed = D.union_sites('include/test.h', text.replace('u16 s; s16 u', 'u16 u; s16 s'))
        self.assertEqual(fixed, [])

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
                         {'include/test.h::data#1', 'include/test.h::callback#1',
                          'include/test.h::signed_pointers#1', 'include/test.h::ribbon#1'})
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


if __name__ == '__main__':
    unittest.main()
