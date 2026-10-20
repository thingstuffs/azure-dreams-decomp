"""Field census: spellings, offsets, widths, chains, header shifts and cross-call typing on a synthetic tree."""
import gzip
import json
from pathlib import Path
import shutil
import sys
import tempfile
import unittest

TOOLS = Path(__file__).resolve().parents[1]
sys.path[:0] = [str(TOOLS / 'typing')]
import field_census as FC

HEADER = r'''
#ifndef SHARED_NODE_H
#define SHARED_NODE_H
typedef unsigned char u8; typedef signed short s16; typedef unsigned short u16; typedef int s32;
typedef struct Node {            /* 0x20-byte header before the record */
    struct Node *next;
    void *pos;                   /* 0x08 below */
    int pad04;
    void *part;                  /* 0x0C */
    u8 pad10[0xE];
    u16 flags;                   /* 0x1E */
} Node;
typedef struct Rec { int x, y, z; s16 unk_0C; s16 facing; } Rec;
#endif
'''

SOURCE = r'''
#include "shared/node.h"
#define F(p, t, o) (*(t *)((u8 *)(p) + (o)))
typedef struct S_80012345_0 { u8 pad[4]; s32 unk_04; } S_80012345_0;
Node *alloc_node(s32 flags);
void use_part(void *part);
void link_node(Node *node);

void use_part(void *part)
{
    *((s16 *) (((u8 *) part) + 0x1C)) = 0x1000;
}

void spawn(void *record, S_80012345_0 *view)
{
    void *owner;
    void *node;
    void *part;
    s32 x;
    owner = ((u8 *) record) - 0x20;
    link_node(owner);
    x = *((s32 *) (((u8 *) (*((void **) (((u8 *) owner) + 8)))) + 4));
    node = alloc_node(0x312);
    part = *((void **) (((u8 *) node) + 0xC));
    *((s32 *) (((u8 *) part) + 0xC)) = 0x80FF;
    F(part, u16, 0x14) |= 0xC;
    use_part(part);
    ((Rec *) record)->facing = x;
    view->unk_04 = x;
    (*((u16 *) (((u8 *) record) + (-2))))++;
}
'''


@unittest.skipUnless(shutil.which('clang'), 'clang required')
class FieldCensusTest(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.tmp = Path(tempfile.mkdtemp(prefix='field-census-'))
        (cls.tmp / 'include/shared').mkdir(parents=True)
        (cls.tmp / 'src').mkdir()
        (cls.tmp / 'include/shared/node.h').write_text(HEADER)
        (cls.tmp / 'src/a.c').write_text(SOURCE)
        cls.summary = FC.run(cls.tmp, cls.tmp / 'out', tus=['src/a.c'], workers=1)
        with gzip.open(cls.tmp / 'out/sites.jsonl.gz', 'rt') as fh:
            cls.sites = [json.loads(l) for l in fh]

    @classmethod
    def tearDownClass(cls):
        shutil.rmtree(cls.tmp)

    def find(self, func, line_text):
        lines = SOURCE.splitlines()
        # clang lines are 1-based in the file, SOURCE starts with a newline
        line = next(i for i, l in enumerate(lines, 1) if line_text in l)
        return [s for s in self.sites if s['func'] == func and s['line'] == line]

    def test_raw_cast_write_constant(self):
        s, = self.find('spawn', '0x80FF')
        self.assertEqual((s['spell'], s['width'], s['sign'], s['rw'], s['const']), ('raw_cast', 4, 's', 'w', 0x80FF))
        self.assertEqual((s['label'], s['off']), ('Node->[0xc]', 0xC))

    def test_macro_spelling_and_rw(self):
        s, = self.find('spawn', 'F(part')
        self.assertEqual((s['spell'], s['width'], s['sign'], s['rw']), ('F_macro', 2, 'u', 'rw'))
        self.assertEqual((s['label'], s['off']), ('Node->[0xc]', 0x14))

    def test_header_shift_and_pointer_chain(self):
        sites = self.find('spawn', 'x = *((s32 *)')
        by_off = {(s['label'], s['off']) for s in sites}
        # owner = record - 0x20; owner + 8 is Node.pos; its pointee's +4 is a chain site
        self.assertIn(('Node', 8), by_off)
        self.assertIn(('Node->[0x8]', 4), by_off)
        chain = [s for s in sites if s['label'] == 'Node->[0x8]'][0]
        self.assertTrue(chain['chain'])

    def test_negative_offset_is_header_flags(self):
        s, = self.find('spawn', '(-2)')
        self.assertEqual((s['label'], s['off'], s['rw']), ('Node', 0x1E, 'rw'))

    def test_member_spellings(self):
        rec, = self.find('spawn', '->facing')
        self.assertEqual((rec['spell'], rec['label'], rec['off']), ('member_named', 'Rec', 0xE))
        view, = self.find('spawn', 'view->unk_04')
        self.assertEqual((view['spell'], view['off'], view['width']), ('member_view', 4, 4))
        self.assertTrue(view['label'].startswith('view:'))

    def test_parameter_inherits_callers_anchor(self):
        s, = self.find('use_part', '0x1C')
        self.assertEqual((s['label'], s['off'], s['const']), ('Node->[0xc]', 0x1C, 0x1000))

    def test_layout_aggregation(self):
        rows = [json.loads(l) for l in (self.tmp / 'out/layouts.jsonl').read_text().splitlines()]
        part = next(r for r in rows if r['label'] == 'Node->[0xc]')
        self.assertEqual(set(part['fields']), {'0xc', '0x14', '0x1c'})
        self.assertEqual(part['fields']['0x1c']['consts'], {'0x1000': 1})
        self.assertEqual(self.summary['tu_errors'], 0)


class LayoutParseTest(unittest.TestCase):
    def test_parse_nested_and_unnamed(self):
        text = '''
*** Dumping AST Record Layout
         0 | struct Outer
         0 |   struct Inner in
         0 |     int a
         4 |   short b
           | [sizeof=8, align=4]

*** Dumping AST Record Layout
         0 | struct (unnamed at include/x.h:3:9)
         0 |   unsigned char[24] data
           | [sizeof=24, align=1]
'''
        lay = FC.parse_layouts(text)
        self.assertEqual(lay['Outer']['fields'], {'in': (0, 'struct Inner'), 'b': (4, 'short')})
        self.assertEqual(lay['Outer']['size'], 8)
        self.assertEqual(lay['@include/x.h:3:9']['fields']['data'], (0, 'unsigned char[24]'))


if __name__ == '__main__':
    unittest.main()
