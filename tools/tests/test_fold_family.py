"""Exact-range folds: macro evaluation, signed loads, and pointer-table access."""
import gzip
import json
from pathlib import Path
import shutil
import sys
import tempfile
import unittest

TOOLS = Path(__file__).resolve().parents[1]
sys.path[:0] = [str(TOOLS / 'typing'), str(TOOLS)]
import field_census as C
import fold_family as F


@unittest.skipUnless(shutil.which('clang'), 'clang required')
class FoldTest(unittest.TestCase):
    def test_range_and_representation(self):
        with tempfile.TemporaryDirectory(prefix='fold-family-') as temp:
            root = Path(temp)
            (root / 'include/shared').mkdir(parents=True)
            (root / 'src').mkdir()
            (root / 'include/shared/part.h').write_text('''
typedef unsigned char u8; typedef signed short s16; typedef unsigned short u16;
typedef struct Part { u16 flags; u16 pad; void *table; } Part;
''')
            text = '''/* UTF-8 range: é */
#include "shared/part.h"
#define GET(p, t, o) (*(t *)((u8 *)(p) + (o)))
typedef struct S_80000000 { s16 unk_00; u16 pad; u8 *unk_04; } S_80000000;
int use(Part *anchor, void *p) {
    S_80000000 *view;
    view = (S_80000000 *)anchor;
    GET(view, u16, 0)++;
    return view->unk_00 + view->unk_04[2];
}
'''
            (root / 'src/a.c').write_text(text)
            C.run(root, root / 'census', tus=['src/a.c'], workers=1)
            with gzip.open(root / 'census/sites.jsonl.gz', 'rt') as fh:
                sites = [json.loads(line) for line in fh]
            fam = {'type': 'Part', 'header': 'shared/part.h', 'labels': ['Part'],
                   'fields': {'0x0:2': 'flags:u', '0x4:4': 'table:p'}}
            result = F.plan_file(root, 'src/a.c', sites, fam)
            self.assertFalse(result['refused'])
            out = F.apply(text, result['plans'], fam['header'])
            self.assertIn('Part *view;', out)
            self.assertIn('view->flags++', out)
            self.assertIn('return *(s16 *)&view->flags +', out)
            self.assertIn('(*(u8 * *)&view->table)[2]', out)
            self.assertNotIn('GET(view', out)
            # The same spelling through a pointer into the middle of the
            # object must not be treated as an object-start pointer.
            shifted = text.replace('view = (S_80000000 *)anchor;',
                'view = (S_80000000 *)((u8 *)anchor + 4);')
            (root / 'src/a.c').write_text(shifted)
            C.run(root, root / 'shifted', tus=['src/a.c'], workers=1)
            with gzip.open(root / 'shifted/sites.jsonl.gz', 'rt') as fh:
                shifted_sites = [json.loads(line) for line in fh]
            held = F.plan_file(root, 'src/a.c', shifted_sites, fam)
            self.assertFalse(held['plans'])
            self.assertIn('base_offset_not_zero', [r['reason'] for r in held['refused']])

    def test_aggregate_copy_keeps_complete_extent(self):
        with tempfile.TemporaryDirectory(prefix='fold-copy-') as temp:
            root = Path(temp)
            (root / 'include/shared').mkdir(parents=True)
            (root / 'src').mkdir()
            (root / 'include/shared/part.h').write_text(
                'typedef struct Part { unsigned short flags, other; } Part;\n')
            text = '''#include "shared/part.h"
typedef struct Copy { unsigned words[1]; } Copy;
void use(Part *anchor, void *p) {
    p = anchor;
    *(Copy *)p = *(Copy *)anchor;
}
'''
            (root / 'src/a.c').write_text(text)
            C.run(root, root / 'census', tus=['src/a.c'], workers=1)
            with gzip.open(root / 'census/sites.jsonl.gz', 'rt') as fh:
                sites = [json.loads(line) for line in fh]
            fam = {'type': 'Part', 'header': 'shared/part.h', 'labels': ['Part'],
                   'fields': {}, 'aggregate_size': 4}
            result = F.plan_file(root, 'src/a.c', sites, fam)
            self.assertFalse(result['refused'])
            out = F.apply(text, result['plans'], fam['header'])
            self.assertIn('*(Part *)p = *(Part *)anchor;', out)

    def test_embedded_array_and_loaded_pointer_have_distinct_bases(self):
        with tempfile.TemporaryDirectory(prefix='fold-array-') as temp:
            root = Path(temp)
            (root / 'include/shared').mkdir(parents=True)
            (root / 'src').mkdir()
            (root / 'include/shared/part.h').write_text('''
typedef unsigned char u8;
typedef struct Part { unsigned pad[3]; struct { u8 r, g, b, code; } color; } Part;
typedef struct Node { Part *part; } Node;
''')
            text = '''#include "shared/part.h"
typedef struct S_80000000 { unsigned pad[3]; u8 rgb[3]; } S_80000000;
void use(Part *p, Node *node) {
    S_80000000 *view;
    view = (S_80000000 *)p;
    view->rgb[2] = 128;
    ((S_80000000 *)node->part)->rgb[0] = 64;
}
'''
            (root / 'src/a.c').write_text(text)
            C.run(root, root / 'census', tus=['src/a.c'], workers=1)
            with gzip.open(root / 'census/sites.jsonl.gz', 'rt') as fh:
                sites = [json.loads(line) for line in fh]
            fam = {'type': 'Part', 'header': 'shared/part.h', 'labels': ['Part', 'Node->[0x0]'],
                   'fields': {'0xc:1': 'color.r:u', '0xe:1': 'color.b:u'},
                   'preserve_accesses': ['0xc:3']}
            result = F.plan_file(root, 'src/a.c', sites, fam)
            self.assertFalse(result['refused'])
            out = F.apply(text, result['plans'], fam['header'])
            self.assertIn('Part *view;', out)
            self.assertIn('view->color.b = 128;', out)
            self.assertIn('((Part *)node->part)->color.r = 64;', out)


class SourceCleanupTest(unittest.TestCase):
    def test_precedence_wrappers(self):
        import retype_family as R
        self.assertEqual(R.access_spelling('p->flags', '++'), 'p->flags')
        self.assertEqual(R.access_spelling('*(s16 *)&p->flags', ' + 1'), '*(s16 *)&p->flags')
        self.assertEqual(R.access_spelling('*(s16 *)&p->flags', '++'), '(*(s16 *)&p->flags)')
        self.assertEqual(R.access_spelling('*(u8 **)&p->table', '[2]'), '(*(u8 **)&p->table)')
        self.assertEqual(R.access_spelling('*(u8 **)&p->table', '\n /* table entry */ [2]'), '(*(u8 **)&p->table)')

    def test_multiline_pointer_table_cleanup(self):
        import retype_family as R
        self.assertEqual(R.access_spelling('*(u8 **)&p->table', '\n    [index]'), '(*(u8 **)&p->table)')

    def test_multiline_typedef_comment_is_removed_whole(self):
        text = 'typedef struct S_80000000 { int a; } S_80000000; /* explanation\ncontinued */\nint keep;\n'
        self.assertEqual(F.remove_unused_views(text), 'int keep;\n')
        self.assertEqual(F.remove_unused_views(text + 'S_80000000 used;\n'), text + 'S_80000000 used;\n')


if __name__ == '__main__':
    unittest.main()
