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
                             {'file_local_macro_casts': 0, 'header_macro_casts': 6})
            D.validate_baseline(json.loads(D.baseline_text(baseline)))
            D.write_outputs(root / 'out', report)
            rows = (root / 'out/debt_header_macro_casts.tsv').read_text().splitlines()
            self.assertEqual(len(rows), 2)
            self.assertIn('NODE_HEADER=2', rows[1])


if __name__ == '__main__':
    unittest.main()
