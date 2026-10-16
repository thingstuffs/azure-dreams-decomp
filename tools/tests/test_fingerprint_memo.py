"""Scoped-fingerprint memo: reuse only while every probed input identity is unchanged."""
import os
from pathlib import Path
import sys
import tempfile
import unittest
from unittest.mock import patch
REPO = Path(__file__).resolve().parents[2]
sys.path[:0] = [str(REPO/'tools'), str(REPO/'tools/gate')]
import gate_read_cache as R
import overlay_scoped_fingerprint as S


class MemoTests(unittest.TestCase):
    def setUp(self):
        self.temp = tempfile.TemporaryDirectory(dir=os.environ.get('TMPDIR')); self.addCleanup(self.temp.cleanup)
        self.root = Path(self.temp.name); S._MEMO.clear(); self.addCleanup(S._MEMO.clear)
        self.calls = 0
        env = patch.dict(os.environ, {'AZ_FP_MEMO': '1'}); env.start(); self.addCleanup(env.stop)

    def touch(self, rel, text):
        p = self.root/rel; p.parent.mkdir(parents=True, exist_ok=True)
        before = R.stamp_of(p)
        p.write_text(text)
        # Same-size rewrites inside one mtime tick still change ctime_ns/ino only if the
        # filesystem says so; force a distinct identity like any real edit does.
        while R.stamp_of(p) == before:
            os.utime(p, ns=(p.stat().st_atime_ns, p.stat().st_mtime_ns + 1))
        return p

    def value(self, key='k'):
        def compute():
            self.calls += 1
            a = R.read_text(self.root/'a.txt')                                  # cached reader
            b = (self.root/'b.txt').read_text() if S._exists(self.root/'b.txt') else None  # probe + plain read
            listed = sorted(p.name for p in (self.root/'d').glob('*'))         # listing (audit net)
            return {'a': a, 'b': b, 'listed': listed}
        return S.memo(key, compute)

    def test_reuse_while_unchanged_and_copies_are_independent(self):
        self.touch('a.txt', 'A'); (self.root/'d').mkdir()
        v = self.value(); v['a'] = 'mutated'
        self.assertEqual(self.value(), {'a': 'A', 'b': None, 'listed': []})
        self.assertEqual(self.calls, 1)

    def test_content_edit_through_cached_reader_invalidates(self):
        self.touch('a.txt', 'A'); (self.root/'d').mkdir()
        self.value(); self.touch('a.txt', 'B')
        self.assertEqual(self.value()['a'], 'B'); self.assertEqual(self.calls, 2)

    def test_absent_optional_input_appearing_invalidates(self):
        self.touch('a.txt', 'A'); (self.root/'d').mkdir()
        self.assertIsNone(self.value()['b']); self.touch('b.txt', 'new')
        self.assertEqual(self.value()['b'], 'new'); self.assertEqual(self.calls, 2)

    def test_listing_change_invalidates(self):
        self.touch('a.txt', 'A'); (self.root/'d').mkdir()
        self.value(); self.touch('d/new.h', 'x')
        self.assertEqual(self.value()['listed'], ['new.h']); self.assertEqual(self.calls, 2)

    def test_plain_open_read_is_recorded_by_the_net(self):
        p = self.touch('plain.txt', 'one')
        def compute():
            self.calls += 1
            with open(p) as f: return f.read()
        self.assertEqual(S.memo('plain', compute), 'one'); self.touch('plain.txt', 'two')
        self.assertEqual(S.memo('plain', compute), 'two'); self.assertEqual(self.calls, 2)

    def test_inner_hit_propagates_identities_to_outer(self):
        self.touch('a.txt', 'A'); (self.root/'d').mkdir()
        self.value('inner')                                        # inner cached first
        outer = lambda: S.memo('outer', lambda: self.value('inner'))
        outer(); self.touch('a.txt', 'C')
        self.assertEqual(outer()['a'], 'C')                        # outer must not hide the inner change

    def test_nested_value_is_seeded_with_callers_inputs(self):
        self.touch('a.txt', 'A'); self.touch('c.txt', 'c1'); (self.root/'d').mkdir()
        def outer():                                                 # like _fingerprint around _window_digest
            seed = R.read_text(self.root/'c.txt')                   # read by the caller, used by the inner value
            return S.memo('nested', lambda: seed + self.value('leaf')['a'])
        self.assertEqual(S.memo('caller', outer), 'c1A'); self.touch('c.txt', 'c2')
        self.assertEqual(S.memo('nested', lambda: 'stale'), 'stale')  # caller's input is in the entry

    def test_switch_off_recomputes(self):
        self.touch('a.txt', 'A'); (self.root/'d').mkdir()
        with patch.dict(os.environ, {'AZ_FP_MEMO': '0'}):
            self.value(); self.value()
        self.assertEqual(self.calls, 2)

    def test_no_observer_outside_memo(self):
        self.assertEqual(R.observers(), [])
        R.observe(self.root/'anything')                            # no-op without an observer


class RodataOwnerBisectionTests(unittest.TestCase):
    """The bisection must select exactly the rows the old full scan selected, in registry order."""
    def test_matches_scan(self):
        import random
        rng = random.Random(7)
        for trial in range(200):
            reg, off = {}, 0
            for i in range(rng.randint(0, 30)):
                off += rng.randint(0, 40); size = rng.randint(1, 40)
                reg['r%d' % i] = {'container': rng.choice(['dungeon', 'dungeon_engine', 'town']), 'foff': off, 'size': size}
                off += size
            items = list(reg.items()); rng.shuffle(items); reg = dict(items)
            spans = S.family_spans(reg)
            for _ in range(20):
                fam = rng.choice(['dungeon', 'town']); o = rng.randint(0, off+10); s = rng.randint(0, 50)
                scan = [x for x in reg.values() if S.family(x['container']) == fam and x['foff'] < o+s and o < x['foff']+x['size']]
                self.assertEqual(S.overlapping(spans, fam, o, s), scan)


if __name__ == '__main__':
    unittest.main()
