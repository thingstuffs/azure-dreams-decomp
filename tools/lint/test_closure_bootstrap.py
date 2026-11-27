"""Bootstrap tests on synthetic worlds (no retail bytes): its lines pass the check, and it acknowledges nothing.

    python3 -m unittest tools.lint.test_closure_bootstrap
"""
import json
import sys
import unittest
from pathlib import Path

HERE = Path(__file__).resolve().parent
sys.path.insert(0, str(HERE))
import closure as C  # noqa: E402
import closure_bootstrap as B  # noqa: E402
import closure_detect as D  # noqa: E402
from test_closure import World, base_world, SIZE  # noqa: E402
from test_closure_detect import DATA, frame_fn, leaf_fn, pack  # noqa: E402


def census_none():
    return dict(streams=[])


def link_parts(w):
    for fam in C.FILES:
        d = w.root / 'link' / fam
        d.mkdir(parents=True, exist_ok=True)
        (d / ('%s_bin.tsv' % fam)).write_text('#{}\no\tn\tk\tr\th\tx\n0\t%d\td\tcensus:x\t\t0\n' % SIZE)
    (w.root / 'link/physical_roots.json').write_text(json.dumps([f + '/' + f + '_bin' for f in C.FILES]))
    (w.root / 'ledger').mkdir(exist_ok=True)
    (w.root / 'ledger/sdk_objects.jsonl').write_text(json.dumps(dict(id='town/func_x')) + '\n')
    (w.root / 'ledger/rows.jsonl').write_text('')


def labelled(w, data=(), code=(), padding=(), unknown=()):
    for fam in C.FILES:
        w.labels[fam] = dict(code=[list(x) for x in code] if fam == 'town' else [], unknown=[list(x) for x in unknown] if fam == 'town' else [],
                             library=[], data=[list(x) for x in data] if fam == 'town' else [],
                             padding=[list(x) for x in padding] if fam == 'town' else [])


class PartRangeFormatTests(unittest.TestCase):
    """The physical byte map parts are read in the current format (some offsets and sizes are JSON-quoted hex strings,
    the others decimal) and in the plain decimal format."""

    def parts(self, rows, names=('town_bin.000.tsv', 'town_bin.001.tsv')):
        import tempfile
        tmp = tempfile.TemporaryDirectory()
        self.addCleanup(tmp.cleanup)
        root = Path(tmp.name)
        (root / 'link/town').mkdir(parents=True)
        for name, body in zip(names, rows):
            (root / 'link/town' / name).write_text('#{"meta": 1}\no\tn\tk\tr\th\tx\n' + body)
        return root

    def test_quoted_hex_and_decimal_cells_read_the_same_extent(self):
        root = self.parts(['"0x0"\t60\td\tcensus:x\t\t0\n60\t96\td\tcensus:y\t\t1\n"0x9c"\t"0x14"\td\tcensus:z\t\t0\n',
                           '176\t16\td\tcensus:x\t\t0\n'])
        self.assertEqual(B.part_ranges(root, 'town'),
                         [(0, 176, 'link/town/town_bin.000.tsv'), (176, 192, 'link/town/town_bin.001.tsv')])

    def test_plain_decimal_parts_still_read(self):
        root = self.parts(['0\t32\td\tcensus:x\t\t0\n'])
        self.assertEqual(B.part_ranges(root, 'town'), [(0, 32, 'link/town/town_bin.000.tsv')])


class DecodedPlanTests(unittest.TestCase):
    def test_compiled_c_data_of_a_decoded_image_is_not_claimed_by_a_line(self):
        from types import SimpleNamespace
        unit = SimpleNamespace(size=0x100, data=bytes([1]) * 0x100, c_code=[[0x10, 0x30]], c_data=[[0x40, 0x50]],
                               zero_all=[], manifest={})
        plan = B.decoded_plan(unit)
        taken = D.merge([[a, b] for a, b, _, _ in plan.lines])
        self.assertEqual(D.intersect(taken, [[0x10, 0x30], [0x40, 0x50]]), [])
        self.assertEqual(D.merge(taken + [[0x10, 0x30], [0x40, 0x50]]), [[0, 0x100]])


class BootstrapTests(unittest.TestCase):
    def build(self, hidden=None):
        w = base_world()
        w.put('town', 0x700, pack(leaf_fn(2)))                 # census: code
        w.put('town', 0x7F0, b'\xff' * 8)                       # census: padding ending on a boundary
        if hidden:
            hidden(w)
        w.write()
        link_parts(w)
        self.addCleanup(w.close)
        return w

    def test_lines_import_every_class_and_the_check_accepts_them(self):
        w = self.build()
        labelled(w, data=[(0x400, 0x420), (0x500, 0x514)], code=[(0x700, 0x714)], padding=[(0x7F8, 0x800)])
        w.put('town', 0x7F8, b'\xff' * 8)
        w.write() if False else None
        units, plans, written, carved, census = B.run(w.root, labels=w.labels, census=census_none())
        classes = {cls for merged in written.values() for _, _, cls, _ in merged}
        self.assertTrue({'own:code', 'own:data'} <= classes)
        self.assertFalse([c for c in classes if c.startswith('ack:')])
        res = w.run()
        self.assertEqual([f for f in res['findings'] if f[0] not in ('unknown',)], [], res['findings'])
        self.assertEqual(res['headline'][1], 0x14)

    def test_generated_short_lines_carry_a_window_never_their_own_digest(self):
        w = self.build()
        labelled(w, data=[(0x400, 0x420), (0x500, 0x514)], code=[(0x700, 0x714)], padding=[(0x7F8, 0x800)])
        B.run(w.root, labels=w.labels, census=census_none())
        rows = [r.split('\t') for r in (w.root / 'config/closure/town.tsv').read_text().splitlines() if r.startswith('0x')]
        short = [r for r in rows if int(r[1], 16) - int(r[0], 16) < C.DIGEST_LEAST]
        self.assertTrue(short)
        for r in rows:
            self.assertEqual(r[4].startswith('w0x'), r in short, r)
        self.assertEqual(w.run()['findings'] and [f for f in w.run()['findings'] if f[0] in ('sha', 'schema')], [])

    def test_a_hit_inside_a_data_range_stays_an_open_hit_and_nothing_is_acknowledged(self):
        body = pack(leaf_fn(3))

        def hide(w):
            w.put('town', 0x900, body)
        w = self.build(hide)
        labelled(w, data=[(0x400, 0x420), (0x500, 0x514), (0x900, 0x940)], code=[(0x700, 0x714)])
        units, plans, written, carved, census = B.run(w.root, labels=w.labels, census=census_none())
        res = w.run()
        self.assertEqual([h[2] for h in res['open']['town']], ['D1'])
        self.assertFalse(any(cls.startswith('ack:') for merged in written.values() for _, _, cls, _ in merged))

    def test_unknown_label_becomes_own_untyped_and_stays_out_of_the_headline(self):
        def hide(w):
            w.put('town', 0xB00, pack(DATA))
        w = self.build(hide)
        labelled(w, data=[(0x400, 0x420), (0x500, 0x514)], code=[(0x700, 0x714)], unknown=[(0xB00, 0xB10)])
        B.run(w.root, labels=w.labels, census=census_none())
        res = w.run()
        classes = {ln.cls for ln in res['units']['town'].lines}
        self.assertIn('own:untyped', classes)
        self.assertEqual(res['headline'][0], 0x14)


if __name__ == '__main__':
    unittest.main()
