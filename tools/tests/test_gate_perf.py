"""Correctness controls for persistent gate workers and stamped read caches."""
import hashlib
import importlib.util
import json
import math
import os
import sys
import tempfile
import unittest
from pathlib import Path
from unittest.mock import patch

REPO=Path(__file__).resolve().parents[2]
sys.path.insert(0,str(REPO/'tools/gate'))
import gate_read_cache as R
from test_gate_all_scoped_inputs import ScopedInputsFixture, C, G

class ReadCache(unittest.TestCase):
    def setUp(self):
        t=tempfile.TemporaryDirectory();self.addCleanup(t.cleanup)
        self.path=Path(t.name)/'input';R._CACHE.clear()

    def test_digest_invalidates_even_if_size_and_mtime_are_restored(self):
        self.path.write_bytes(b'old');st=self.path.stat();before=R.digest(self.path)
        self.path.write_bytes(b'new');os.utime(self.path,ns=(st.st_atime_ns,st.st_mtime_ns))
        self.assertNotEqual(before,R.digest(self.path))
        self.assertEqual(R.digest(self.path),hashlib.sha256(b'new').hexdigest())

    def test_replacement_with_same_size_and_mtime_invalidates(self):
        self.path.write_bytes(b'old');st=self.path.stat();before=R.digest(self.path)
        other=self.path.with_suffix('.replacement');other.write_bytes(b'new')
        os.utime(other,ns=(st.st_atime_ns,st.st_mtime_ns));other.replace(self.path)
        self.assertNotEqual(before,R.digest(self.path))

    def test_removed_file_fails_instead_of_serving_cached_input(self):
        self.path.write_bytes(b'old');R.digest(self.path);self.path.unlink()
        with self.assertRaises(FileNotFoundError):R.digest(self.path)

    def test_decoded_mutations_cannot_poison_next_reader(self):
        self.path.write_text('{"nested":{"rows":[1]}}\n')
        first=R.read_json(self.path);first['nested']['rows'].append(2)
        self.assertEqual(R.read_json(self.path),{'nested':{'rows':[1]}})
        first=R.read_jsonl(self.path);first[0]['nested']['rows'].append(2)
        self.assertEqual(R.read_jsonl(self.path),({'nested':{'rows':[1]}},))

    def test_invalid_json_after_edit_still_fails(self):
        self.path.write_text('{}');R.read_json(self.path);self.path.write_text('bad')
        with self.assertRaises(json.JSONDecodeError):R.read_json(self.path)

    def test_cache_bound_and_only_latest_stamp_retained(self):
        with patch.object(R,'_LIMIT',2):
            for i in range(4):
                self.path.write_text(str(i));R.digest(self.path)
            self.assertEqual(len(R._CACHE),1)
            for i in range(3):
                p=self.path.with_suffix('.'+str(i));p.write_text('x');R.digest(p)
            self.assertEqual(len(R._CACHE),2)

class CensusSnapshots(ScopedInputsFixture):
    def test_sources_statted_once_for_two_rows_in_one_region(self):
        original=C._stamp
        with patch.object(C,'_stamp',wraps=original) as stamps:
            with C.scoped_census_snapshot():
                a=C.scoped_census('dungeon',0x100,root=self.root)
                n=stamps.call_count
                b=C.scoped_census('dungeon',0x150,root=self.root)
                self.assertEqual(stamps.call_count,n)
        self.assertEqual(a,b)
        self.assertEqual(a,C.scoped_census('dungeon',0x100,root=self.root))

    def test_snapshot_ends_at_compile_batch_and_returns_independent_values(self):
        p=self.root/'raw/dungeon/func_00000110.c'
        with C.scoped_census_snapshot():
            a=C.scoped_census('dungeon',0x100,root=self.root)
            C.scoped_census('dungeon',0x100,root=self.root)['names'].clear()
            p.write_text(self.decl('replacement'))
            self.assertEqual(a,C.scoped_census('dungeon',0x100,root=self.root))
        with C.scoped_census_snapshot():
            b=C.scoped_census('dungeon',0x100,root=self.root)
        self.assertNotEqual(a,b)
        self.assertEqual(b,C.scoped_census('dungeon',0x100,root=self.root))

    def test_raw_edit_with_restored_mtime_refreshes_next_batch(self):
        p=self.root/'raw/dungeon/func_00000110.c'
        with C.scoped_census_snapshot():before=C.scoped_census('dungeon',0x100,root=self.root)
        st=p.stat();p.write_text(p.read_text().replace('dungeon_110','altered_110'))
        os.utime(p,ns=(st.st_atime_ns,st.st_mtime_ns))
        with C.scoped_census_snapshot():after=C.scoped_census('dungeon',0x100,root=self.root)
        self.assertNotEqual(before,after)
        self.assertIn('altered_110',after['names'])

    def test_exception_discards_snapshot(self):
        with self.assertRaises(RuntimeError):
            with C.scoped_census_snapshot():
                C.scoped_census('dungeon',0x100,root=self.root)
                raise RuntimeError('abort')
        self.assertIsNone(C._CENSUS_SNAPSHOT.get())

    def test_new_thread_gets_fresh_evidence(self):
        from concurrent.futures import ThreadPoolExecutor
        with C.scoped_census_snapshot():
            before=C.scoped_census('dungeon',0x100,root=self.root)
            (self.root/'raw/dungeon/func_00000110.c').write_text(self.decl('replacement'))
            with ThreadPoolExecutor(max_workers=1) as pool:
                after=pool.submit(C.scoped_census,'dungeon',0x100,root=self.root).result()
        self.assertNotEqual(before,after)

    def test_input_fingerprint_does_not_share_compile_snapshot(self):
        with C.scoped_census_snapshot():
            C.scoped_census('dungeon',0x100,root=self.root)
            before=C.scoped_inputs('dungeon',[0x100],root=self.root)
            (self.root/'raw/dungeon/func_00000110.c').write_text(self.decl('replacement'))
            self.assertNotEqual(before,C.scoped_inputs('dungeon',[0x100],root=self.root))

class Scheduling(unittest.TestCase):
    def test_unknown_invalid_longest_first_with_stable_ties(self):
        names=['a','b','c','d','e','f','g']
        paths=[Path(n+'.overlay.yaml') for n in names]
        prior={n:{'secs':s} for n,s in [('a',1),('b',200),('d',float('nan')),('e',-1),('f',200),('g','bad')]}
        self.assertEqual([p.stem.replace('.overlay','') for p in G.schedule_windows(paths,prior)],['c','d','e','g','b','f','a'])
        self.assertEqual(paths,[Path(n+'.overlay.yaml') for n in names])

if __name__=='__main__':unittest.main()
