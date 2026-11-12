"""debt_check --summary readability and prototype-gap counts (report only).

    python3 -m unittest tools/lint/test_readcounts.py
"""
from pathlib import Path
import sys
import tempfile
import unittest

HERE = Path(__file__).resolve().parent
sys.path.insert(0, str(HERE))
import debt_check as D  # noqa: E402
import readcounts as R  # noqa: E402

HEADER = '''
typedef unsigned char u8;
typedef int s32;
void shared(void *a, u8 b);
s32 only_header(s32 x);
'''
A = '''#include "x.h"
#include "x.h"
#include <stdint.h>
/* cfail-repair: tf7-phase1-cache-v3 */
/* arg0 and func_80012345 in a comment, "unk_9" in a string below */
typedef struct { s32 a; s32 b; } Pair;
typedef struct Tag { s32 a; s32 b; } Twin;
typedef struct { s32 q; } Odd;
extern void shared(void *a, unsigned char b);
void dup(s32 x) { func_80012345(x); D_80001234 = 1; }
void same(s32 x) { x++; }
void use(void)
{
    char *s = "unk_9 pad_1 D_80099999";
    p->unk_1C = 1;
    p->pad_2 = 2;
    shared(0, 1);
}
'''
B = '''typedef struct { s32 a; s32 b; } Pair;
typedef struct { s32 q; s32 r; } Odd;
void shared(s32 *a, s32 b) { }
void dup(s32 x) { x += 2; }
void same(s32 x) { x++; }
static void hidden(void) { }
'''
C = 'static void hidden(s32 z) { }\nvoid other(void) { var_8 = temp_s0; }\n'


class ReadCounts(unittest.TestCase):
    def setUp(self):
        self.tmp = tempfile.TemporaryDirectory()
        root = Path(self.tmp.name)
        (root / 'src/m').mkdir(parents=True)
        (root / 'include').mkdir()
        (root / 'include/x.h').write_text(HEADER)
        (root / 'src/m/a.c').write_text(A)
        (root / 'src/m/b.c').write_text(B)
        (root / 'src/m/c.c').write_text(C)
        self.root = root

    def tearDown(self):
        self.tmp.cleanup()

    def report(self, cache_dir=None):
        return R.report(self.root, cache_dir, D.cache_value)

    def test_signatures_and_sites(self):
        s = self.report()['signatures']
        # shared: header (void*, u8), a.c (void*, unsigned char) agree; b.c (s32*, u8) differs.
        self.assertEqual(s['names_multi_signature'], 1)
        self.assertEqual(s['names_incompatible'], 1)
        self.assertEqual(s['sites_of_those'], 3)
        self.assertEqual(s['top'][0], ['shared', 3])
        self.assertGreater(s['mean_sites'], 1)

    def test_static_functions_are_not_cross_file_names(self):
        d = self.report()['definitions']
        self.assertEqual((d['multiple'], d['identical'], d['differing']), (2, 1, 1))

    def test_address_tokens_skip_comments_and_strings(self):
        a = self.report()['addresses']
        self.assertEqual((a['func_tokens'], a['func_distinct'], a['data_tokens']), (1, 1, 1))
        self.assertEqual((a['unk'], a['pad']), (1, 1))
        self.assertEqual(a['func_in_comments'], 1)

    def test_struct_typedefs(self):
        t = self.report()['structs']
        self.assertEqual(t['total'], 5)
        self.assertEqual((t['duplicate_copies'], t['duplicate_bodies']), (3, 1))   # Pair x2 and Twin share one body
        self.assertEqual(t['names_with_several_bodies'], 1)                          # Odd

    def test_small_views(self):
        t = self.report()['structs']
        # Pair x2, Twin, Odd { q } and Odd { q; r }: every view has at most two non-pad fields
        self.assertEqual(t['small_views'], 5)
        self.assertEqual(t['small_by_fields'], {'1': 1, '2': 4})
        self.assertEqual((t['small_duplicate_copies'], t['small_duplicate_bodies']), (3, 1))

    def test_member_names_and_pads(self):
        self.assertEqual(R.member_names('u8 pad_00[0x2A]; u16 unk_2A;'), ['pad_00', 'unk_2A'])
        self.assertEqual(R.non_pad_members('u8 pad_00[0x2A]; u16 unk_2A;'), 1)
        self.assertEqual(R.member_names('union { s16 s; u16 u; }; u8 pad[2];'), ['', 'pad'])
        self.assertEqual(R.member_names('union { s16 s; u16 u; } v; struct Bar { s32 x; }; s32 y;'),
                         ['v', None, 'y'])
        self.assertEqual(R.member_names('struct Foo *next; void (*cb)(void); s32 : 3; u8 reserved_1;'),
                         ['next', 'cb', None, 'reserved_1'])
        self.assertEqual(R.non_pad_members('struct Foo *next; void (*cb)(void); s32 : 3; u8 reserved_1;'), 2)
        self.assertEqual(R.member_names('struct { s16 a; } pos[4], *q; s32 x[2], pad_10;'),
                         ['pos', 'q', 'x', 'pad_10'])

    def test_hygiene(self):
        h = self.report()['hygiene']
        self.assertEqual(h['include_dups'], 1)
        self.assertEqual(h['tags'], {'cfail-repair/tf7-phase': 1})
        self.assertEqual(h['placeholders']['var_'], 1)
        self.assertEqual(h['placeholders']['temp_'], 1)
        self.assertEqual(h['placeholders']['in_comments'], 1)

    def test_cache_round_trip_and_invalidation(self):
        cache = self.root / 'cache'
        first = self.report(cache)
        self.assertEqual(self.report(cache)['signatures'], first['signatures'])
        (self.root / 'src/m/c.c').write_text(C + 'void extra(void) { }\n')
        self.assertEqual(self.report(cache)['signatures']['declared_names'],
                         first['signatures']['declared_names'] + 1)

    def test_lines_and_lists(self):
        rep = self.report()
        lines = R.summary_lines(rep)
        self.assertTrue(all('(report only)' in line for line in lines))
        self.assertEqual(len(lines), 10)
        self.assertTrue(any(line.startswith('local views with <=2 non-pad fields') for line in lines))
        R.write_lists(self.root / 'lists', rep)
        self.assertTrue((self.root / 'lists/signature_conflicts.tsv').read_text().startswith('name\t'))
        self.assertIn('shared', (self.root / 'lists/signature_conflicts.tsv').read_text())

    def test_summary_never_fails_check(self):
        summary = D.census(self.root, readcounts=True)
        self.assertIn('readcounts', summary)
        self.assertEqual(D.check_baseline.__name__, 'check_baseline')
        self.assertNotIn('readcounts', {k for k in D.CLASSES})


if __name__ == '__main__':
    unittest.main()
