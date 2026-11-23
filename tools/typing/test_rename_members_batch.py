"""Batch member rename on a small private tree: typed-site accuracy, collisions, macros, aliases, atomic restore."""
from pathlib import Path
import shutil
import tempfile
import unittest

from tools.typing import rename_members_batch as B

HEADER = '''#ifndef REC_H
#define REC_H
typedef struct Actor {
    /* 0x00 */ int unk_00;
    /* 0x04 */ int unk_04;
    /* 0x08 */ int kind;
} Actor;
typedef struct Other {
    /* 0x00 */ int unk_00;
    /* 0x04 */ int unk_04;
} Other;
typedef Actor ActorAlias;
typedef struct Node { int link; char body[8]; } Node;
#define NODE_BODY(n, T) ((T *)((char *)(n) + 4))
#define ACTOR_ID(a) ((a)->unk_00)
#endif
'''
SRC = '''#include "rec.h"
int f(Actor *a, Other *o, ActorAlias *al, Node *n) {
    Actor init = { .unk_04 = 1 };
    int x = a->unk_00 + o->unk_00 + al->unk_04 + o->unk_04;
    x += ACTOR_ID(a) + NODE_BODY(n, Actor)->unk_04;
    /* a->unk_00 in a comment stays */
    return x + init.unk_04;
}
'''

try:
    import subprocess
    HAVE_CLANG = subprocess.run(['clang', '--version'], capture_output=True).returncode == 0
except OSError:
    HAVE_CLANG = False


def row(old, new, record='Actor', offset=None):
    return B.Row(record, 'include/rec.h', old, new, offset)


@unittest.skipUnless(HAVE_CLANG, 'clang not installed')
class BatchTests(unittest.TestCase):
    def setUp(self):
        self.tmp = Path(tempfile.mkdtemp())
        (self.tmp / 'include').mkdir()
        (self.tmp / 'src').mkdir()
        (self.tmp / 'include/rec.h').write_text(HEADER)
        (self.tmp / 'src/a.c').write_text(SRC)

    def tearDown(self):
        shutil.rmtree(self.tmp)

    def run_rows(self, rows, dry=False):
        return B.run_batch(self.tmp, rows, tus=['src/a.c'], dry_run=dry, workers=1)

    def test_two_members_one_record_other_record_untouched(self):
        rows = [row('unk_00', 'actor_id', offset=0), row('unk_04', 'state', offset=4)]
        self.run_rows(rows)
        self.assertEqual([r.status for r in rows], ['renamed', 'renamed'])
        hdr = (self.tmp / 'include/rec.h').read_text()
        self.assertIn('/* 0x00 */ int actor_id;', hdr)
        self.assertIn('/* 0x04 */ int state;', hdr)
        self.assertIn('typedef struct Other {\n    /* 0x00 */ int unk_00;\n    /* 0x04 */ int unk_04;', hdr)
        src = (self.tmp / 'src/a.c').read_text()
        self.assertIn('a->actor_id + o->unk_00 + al->state + o->unk_04', src)  # alias renamed, Other untouched
        self.assertIn('.state = 1', src)                                      # designated initializer
        self.assertIn('init.state', src)
        self.assertIn('/* a->unk_00 in a comment stays */', src)              # comment untouched
        self.assertEqual(len(rows[0].sites), 2)  # a->unk_00 and the ACTOR_ID macro body token

    def test_macro_body_and_accessor_macro_use(self):
        rows = [row('unk_00', 'actor_id'), row('unk_04', 'state')]
        self.run_rows(rows)
        hdr = (self.tmp / 'include/rec.h').read_text()
        self.assertIn('#define ACTOR_ID(a) ((a)->actor_id)', hdr)       # macro body rewritten at its spelling
        self.assertIn('NODE_BODY(n, Actor)->state', (self.tmp / 'src/a.c').read_text())  # accessor-macro typed site
        self.assertEqual(len(rows[0].macro_sites), 1)

    def test_dry_run_counts_and_leaves_tree(self):
        rows = [row('unk_04', 'state')]
        before = {p: p.read_bytes() for p in self.tmp.rglob('*') if p.is_file()}
        self.run_rows(rows, dry=True)
        self.assertEqual(rows[0].status, 'would_rename')
        self.assertEqual(len(rows[0].sites), 4)  # designator, al->, NODE_BODY(...)->, init.
        self.assertEqual(before, {p: p.read_bytes() for p in self.tmp.rglob('*') if p.is_file()})

    def test_collisions_and_absent_members_refused(self):
        rows = [row('unk_00', 'kind'),                 # new name exists
                row('unk_04', 'a'), row('unk_04', 'b'),  # two rows for one member
                row('nothing', 'x'),                   # absent
                row('unk_00', 'wrong_off', offset=8),  # offset mismatch (duplicate of row 1 member, too)
                row('kind', 'unk_04')]                 # new name exists
        self.run_rows(rows)
        self.assertTrue(all(r.status == 'refused' for r in rows), [(r.old, r.status, r.detail) for r in rows])
        self.assertIn('already a member', rows[0].detail)
        self.assertIn('two rows', rows[1].detail)
        self.assertIn('absent', rows[3].detail)
        self.assertEqual((self.tmp / 'include/rec.h').read_text(), HEADER)

    def test_offset_mismatch_refused_and_rest_applied(self):
        rows = [row('unk_00', 'actor_id', offset=4), row('unk_04', 'state', offset=4)]
        self.run_rows(rows)
        self.assertEqual([r.status for r in rows], ['refused', 'renamed'])
        self.assertIn('offset', rows[0].detail)
        self.assertIn('int unk_00;', (self.tmp / 'include/rec.h').read_text())

    def test_macro_shared_with_other_record_drops_only_that_row(self):
        (self.tmp / 'src/a.c').write_text(SRC + 'int g(Other *o) { return ACTOR_ID(o); }\n')
        rows = [row('unk_00', 'actor_id'), row('unk_04', 'state')]
        self.run_rows(rows)
        self.assertEqual([r.status for r in rows], ['refused', 'renamed'])
        self.assertIn('int unk_00;', (self.tmp / 'include/rec.h').read_text())
        self.assertIn('ACTOR_ID(o)', (self.tmp / 'src/a.c').read_text())

    def test_blame_is_limited_to_the_record_the_diagnostic_names(self):
        # an access the tool cannot locate (token pasting) in Other must refuse only Other's row,
        # not Actor's row that shares the member name
        (self.tmp / 'src/a.c').write_text(SRC + '#define PASTE(p) ((p)->unk_ ## 04)\nint g(Other *o) { return PASTE(o); }\n')
        rows = [row('unk_04', 'state'), row('unk_04', 'tag', record='Other')]
        self.run_rows(rows)
        self.assertEqual([r.status for r in rows], ['renamed', 'refused'])

    def test_unexplained_error_aborts_and_restores_everything(self):
        # a macro that swallows the new spelling: the compiler error names no row
        (self.tmp / 'src/a.c').write_text('#define state 1\n' + SRC)
        rows = [row('unk_04', 'state')]
        with self.assertRaises(RuntimeError):
            self.run_rows(rows)
        self.assertEqual((self.tmp / 'include/rec.h').read_text(), HEADER)
        self.assertEqual((self.tmp / 'src/a.c').read_text(), '#define state 1\n' + SRC)

    def test_load_rows_member_pack_and_simple_format(self):
        p = self.tmp / 'rows.tsv'
        p.write_text('record\theader\toffset\told_member\taction\tnew_name\ttype\tconfidence\n'
                     'Actor\tinclude/rec.h\t0x0\tunk_00\trename\tactor_id\t-\tproven\n'
                     'Actor\tinclude/rec.h\t0x4\tunk_04\tkeep\t-\t-\tunknown\n'
                     'Actor\tinclude/rec.h\t0x8\tkind\trename\tk\t-\tlikely\n'
                     'Actor\tinclude/rec.h\t0x8\tkind\trename\tk2\tu8\tlikely\n')
        rows = B.load_rows([p])
        self.assertEqual([r.status for r in rows], ['pending', 'skipped', 'pending', 'skipped'])
        q = self.tmp / 'simple.tsv'
        q.write_text('old_member\tnew_member\toffset\nunk_20\tattack_power\t0x20\n')
        rows = B.load_rows([q], record='ActorRecord', default_header='include/shared/entity.h')
        self.assertEqual((rows[0].record, rows[0].header, rows[0].offset), ('ActorRecord', 'include/shared/entity.h', 0x20))


if __name__ == '__main__':
    unittest.main()
