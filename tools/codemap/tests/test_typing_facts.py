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
        self.assertEqual({k: v for k, v in counts.items() if k != 'rt_fn_map'},
                         {'rt_fn_arg': 1, 'rt_kind': 1, 'rt_pointee': 1, 'rt_callsite': 1})
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


    def test_file_qualified_runtime_join(self):
        self.map.open(fresh=True)
        self.refresh()
        db = self.map.db
        for file, cell in (('src/a.c', 'rk1+0x0=1'), ('src/b.c', 'rk2+0x0=1')):
            db.execute('INSERT INTO rt_fn_arg VALUES (?,?,?,?,?,?,?,?,?)',
                       (file, 'same', 0, 1, 1, 'void *', 1, 1, cell))
            db.execute('INSERT INTO rt_callsite VALUES (?,?,?,?,?,?,?,?)',
                       (file, 'same', 0, file, 'caller', 1, cell, 1))
            db.execute('INSERT INTO rt_pointee VALUES (?,?,?,?,?,?,?,?,?,?)',
                       (file, 1, 'install', 'store', 'rk1', '0x10', 'func', file + ':same', '', 1))
            db.execute('INSERT INTO flow_item VALUES (?,?,?,?,?,?,?,?,?)',
                       ('C1', 'same', file, 0, 'hold', 'hold', file, 0, 'items.tsv'))
        p = T.q_param(db, 'src/b.c::same::0')
        self.assertEqual([r['cells'] for r in p['runtime']], ['rk2+0x0=1'])
        self.assertEqual([r['caller_file'] for r in p['callsites']], ['src/b.c'])
        self.assertEqual([r['reason'] for r in p['flow']], ['src/b.c'])
        self.assertEqual([r['value_target'] for r in p['pointee_stores']], ['src/b.c:same'])


class RuntimeIdentity(unittest.TestCase):
    """rt_fn_map: runtime (file, function) pairs of an older revision bound by address to the current tree."""

    def setUp(self):
        import sqlite3
        self.db = db = sqlite3.connect(':memory:')
        db.executescript('''
            CREATE TABLE retail_fn(recipe TEXT, symbol TEXT, name TEXT);
            CREATE TABLE recipe(id TEXT, source TEXT);
            CREATE TABLE defn(name TEXT, file TEXT);
            CREATE TABLE image_unit(image TEXT, recipe TEXT);
            CREATE TABLE rt_fn_arg(file TEXT, function TEXT);
            CREATE TABLE rt_kind(creator_file TEXT, creator_function TEXT, body_receivers TEXT);
        ''')
        for rid, sym, name, src, image in (
                ('r1', 'func_80100000', 'move_actor', 'src/a/move_actor.c', 'dungeon/bank_1'),
                ('r2', 'func_80100000', 'move_actor', 'src/a/move_actor.c', 'dungeon/bank_2'),
                # the same address in two images holds two different functions now (per-image names)
                ('r3', 'func_80200000', 'open_door', 'src/town/open_door.c', 'town/main'),
                ('r4', 'func_80200000', 'close_lid', 'src/card/close_lid.c', 'card/main'),
                ('r5', 'func_80300000', 'func_80300000', 'src/x/func_80300000.c', 'slus'),
                ('r6', 'zero_words', 'zero_words', 'src/engine/zero_words.c', 'slus')):
            db.execute('INSERT INTO retail_fn VALUES (?,?,?)', (rid, sym, name))
            db.execute('INSERT INTO recipe VALUES (?,?)', (rid, src))
            db.execute('INSERT INTO image_unit VALUES (?,?)', (image, rid))
            db.execute('INSERT INTO defn VALUES (?,?)', (name, src))
        db.executemany('INSERT INTO rt_fn_arg VALUES (?,?)', [
            ('src/a/old_move.c', 'step_actor'),            # renamed function and file since the runtime
            ('src/town/door.c', 'update_thing'),           # address shared by two names: the file decides
            ('src/gone.c', 'update_thing'),                # ... and without a file match it is ambiguous
            ('src/x/func_80300000.c', 'func_80300000'),     # an address name
            ('src/engine/zero_words.c', 'zero_words'),     # a library name with no names.tsv row
            ('src/none.c', 'never_defined')])
        db.execute('INSERT INTO rt_kind VALUES (?,?,?)', ('src/a/old_move.c', 'step_actor', '[]'))
        names = ('# header\n0x80100000\tfunc_80100000\tstep_actor\tevidence\n'
                 '0x80200000\tfunc_80200000\tupdate_thing\tevidence\n')
        self.old = T.old_name_addresses(names)
        self.renames = {'src/a/old_move.c': 'src/a/move_actor.c', 'src/town/door.c': 'src/town/open_door.c'}

    def test_address_join(self):
        got = T.map_runtime_identity(self.db, T.runtime_pairs(self.db), self.old, self.renames)
        r = got[('src/a/old_move.c', 'step_actor')]
        self.assertEqual((r['cur_function'], r['cur_file'], r['address'], r['how']),
                         ('move_actor', 'src/a/move_actor.c', '0x80100000', 'address+file'))
        self.assertEqual(r['images'], 'dungeon/bank_1,dungeon/bank_2')
        self.assertEqual(got[('src/town/door.c', 'update_thing')]['cur_function'], 'open_door')
        self.assertEqual(got[('src/gone.c', 'update_thing')]['how'], 'ambiguous')
        self.assertIsNone(got[('src/gone.c', 'update_thing')]['cur_function'])
        self.assertEqual(got[('src/x/func_80300000.c', 'func_80300000')]['how'], 'address+file')
        self.assertEqual(got[('src/engine/zero_words.c', 'zero_words')]['how'], 'name+file')
        self.assertEqual(got[('src/none.c', 'never_defined')]['how'], 'unmapped')

    def test_map_table(self):
        counts = T.load_runtime_map(self.db, self.old, self.renames, log=lambda m: None)
        self.assertEqual(counts['renamed'], 2)
        row = self.db.execute("SELECT cur_function FROM rt_fn_map WHERE function='step_actor'").fetchone()
        self.assertEqual(row, ('move_actor',))


if __name__ == '__main__':
    unittest.main()
