"""codemap typing facts: cast rows, record layouts, flow blobs, incremental stamps, runtime and flow joins."""
import csv
import gzip
import json
from pathlib import Path
import shutil
import sys
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[3]
sys.path[:0] = [str(ROOT / 'tools/codemap'), str(ROOT / 'tools/build'), str(ROOT / 'tools/typing'), str(ROOT / 'tools')]
import codemap as CM        # noqa: E402
import typing_facts as TF   # noqa: E402
import typing_query as T    # noqa: E402

CLANG = shutil.which('clang')
HEADER = '''typedef short s16;
typedef int s32;
typedef unsigned char u8;
typedef struct Body { s32 a; s16 b; s16 c; void *next; } Body;
typedef struct S_800A0000_0 { u8 pad[4]; s16 w; } S_800A0000_0;
'''
SOURCE = '''#include "h.h"
s32 read_b(Body *p) { return *(s16 *)((u8 *)p + 4); }
s32 read_void(void *q) { return *(s16 *)((u8 *)q + 6) + ((S_800A0000_0 *)q)->w; }
void store(Body *p, void *q) { p->next = q; }
'''


@unittest.skipUnless(CLANG, 'clang not installed')
class TypingFacts(unittest.TestCase):
    def setUp(self):
        (ROOT / 'tmp').mkdir(exist_ok=True)
        self.dir = Path(tempfile.mkdtemp(dir=ROOT / 'tmp'))
        (self.dir / 'include').mkdir()
        (self.dir / 'src').mkdir()
        (self.dir / 'include/h.h').write_text(HEADER)
        (self.dir / 'src/a.c').write_text(SOURCE)
        self.map = CM.CodeMap(self.dir, self.dir / 'build/codemap.db', workers=1, log=lambda m: None, typing=False)
        self.physical = {'src/a.c': {'kind': 'row'}}

    def tearDown(self):
        shutil.rmtree(self.dir, ignore_errors=True)

    def refresh(self):
        self.map.refresh()
        return TF.refresh(self.map, physical=self.physical)

    def test_extract_incremental_and_queries(self):
        self.map.open(fresh=True)
        self.assertEqual(self.refresh(), 1)
        db = self.map.db
        rows, errors = T.cast_rows(db, 'src')
        self.assertFalse(errors)
        by_func = {}
        for r in rows.values():
            by_func.setdefault(r['func'], set()).add((r['cls'], r['sub']))
        self.assertIn(('n', 'fold_now'), by_func['read_b'])          # typed base with an exact member
        self.assertTrue(any(c == 'a' for c, _ in by_func['read_void']))  # void * base
        self.assertTrue(any(c == 'c' for c, _ in by_func['read_void']))  # generated view
        lay = {r[0]: r for r in db.execute('SELECT record, def_file, size, family FROM record_layout')}
        self.assertEqual(lay['Body'][1:], ('include/h.h', 12, 'shared'))
        self.assertEqual(lay['S_800A0000_0'][3], 'S_')
        members = db.execute("SELECT off, name FROM record_member WHERE record='Body' AND depth=0 ORDER BY off").fetchall()
        self.assertEqual(members, [(0, 'a'), (4, 'b'), (6, 'c'), (8, 'next')])
        flow = json.loads(gzip.decompress(T.flow_blob(db, 'src/a.c')))
        self.assertIsInstance(flow, dict)
        # unchanged: nothing re-extracted; a header edit re-extracts the TU that includes it
        self.assertEqual(self.refresh(), 0)
        (self.dir / 'include/h.h').write_text(HEADER + 'extern s32 g;\n')
        self.assertEqual(self.refresh(), 1)
        self.assertEqual(db.execute('SELECT COUNT(*) FROM record_layout WHERE record = "Body"').fetchone()[0], 1)
        # a TU leaving the graph drops its facts
        self.physical = {}
        self.refresh()
        self.assertEqual(db.execute('SELECT COUNT(*) FROM cast_site').fetchone()[0], 0)
        self.assertEqual(db.execute('SELECT COUNT(*) FROM record_layout').fetchone()[0], 0)

    def test_queries_and_runtime_join(self):
        self.map.open(fresh=True)
        self.refresh()
        db = self.map.db
        q = T.q_casts(db, folder='src', by='func')
        self.assertEqual({g['func'] for g in q['groups']}, {'read_b', 'read_void'})
        views = T.q_views(db, 'S_800A0000_0')
        self.assertEqual(views['records'][0]['members'][-1]['name'], 'w')
        self.assertGreaterEqual(views['records'][0]['cast_sites'], 1)
        rt = self.dir / 'rt'
        rt.mkdir()
        (rt / 'fn_args.tsv').write_text('file\tfunction\tcalls\tnparams\targ\tparam_type\tobservations\theap_kinds\tvalues\n'
                                        'src/a.c\tread_void\t5\t1\t0\tvoid *\t5\t1\trk7+0x20=5\n')
        (rt / 'kinds_rt.json').write_text(json.dumps({'kinds': [{'id': 'rk7', 'role': 'pool', 'creator': {
            'file': 'src/a.c', 'function': 'make'}, 'size': 292, 'allocs': 3, 'body_receivers': [
            {'file': 'src/a.c', 'function': 'read_void'}]}]}))
        with gzip.open(rt / 'pointees.tsv.gz', 'wt') as w:
            w.write('file\tline\tfunction\taccess\tclass\ttarget\toffset\tvalue_class\tvalue_target\tvalue_offset\tcount\n'
                    'src/a.c\t9\tinstall\tstore\theap\trk7\t0x10\tfunc\tsrc/a.c:read_void\t\t3\n')
        with gzip.open(rt / 'callsite_args.tsv.gz', 'wt') as w:
            w.write('callee_file\tcallee\targ\tcaller_file\tcaller\tline\tcells\tcalls\n'
                    'src/a.c\tread_void\t0\tsrc/b.c\tcaller\t12\trk7+0x20=5\t5\n')
        counts = T.load_runtime(db, rt, 'abc123', log=lambda m: None)
        self.assertEqual(counts, {'rt_fn_arg': 1, 'rt_kind': 1, 'rt_pointee': 1, 'rt_callsite': 1})
        items = self.dir / 'item_status.tsv'
        items.write_text('transaction\tseeds\tseed_rows\tverdict\tpredicted_delta\tstatus\treason\n'
                         'C0001\t1\tread_void#0\thold\t0\thold\tno runtime or seed target\n')
        self.assertEqual(T.load_flow(db, items, log=lambda m: None), 1)
        p = T.q_param(db, 'src/a.c::read_void::0')
        self.assertEqual(p['declared'], {'src/a.c': 'void *'})
        self.assertEqual(p['runtime'][0]['cells'], 'rk7+0x20=5')
        self.assertEqual(p['callsites'][0]['caller'], 'caller')
        self.assertEqual(p['flow'][0]['reason'], 'no runtime or seed target')
        self.assertEqual(p['pointee_stores'][0]['offset'], '0x10')
        self.assertTrue(p['casts']['src/a.c'])
        self.assertEqual(T.q_slots(db)[0]['function'], 'src/a.c:read_void')
        self.assertEqual(T.q_holds(db)[0]['seeds'], 1)


if __name__ == '__main__':
    unittest.main()
