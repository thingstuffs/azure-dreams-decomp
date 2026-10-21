#!/usr/bin/env python3
"""Unit tests for the tu7 additions (no compiler, no disc): run with
    python3 -m pytest tools/tu/test_tu_tools.py      or      python3 tools/tu/test_tu_tools.py
"""
import ast
import json
import shutil
import sys
import tempfile
import unittest
from collections import defaultdict
from pathlib import Path

HERE = Path(__file__).resolve().parent
sys.path.insert(0, str(HERE))
import infer_groups as I  # noqa: E402
import tu_merge as M  # noqa: E402


def fn(i, foff, size, home, calls=(), drefs=(), rdata=(), vma_delta=0x80000000):
    return dict(i=i, foff=foff, end=foff + size, vma=foff + vma_delta, row=home, home=home, origin='row', group='',
                rdata=list(rdata), data=len(drefs), calls=['%08X' % c for c in calls],
                drefs=['%08X' % d for d in drefs], brefs=[], xrefs=[])


def unit(name, fns, groups=(), edges=()):
    return dict(summary=dict(unit=name, image=name, container=name.split('/')[0], rdata=['0x0', '0x0'],
                             data=['0x0', '0x100000'], delta='0x80000000'),
                functions=fns, groups=list(groups), edges=list(edges), jump_tables={}, data_fills=[])


class FakeRepo:
    def __init__(self):
        self.rows, self.layout, self.module_of, self.inlined = {}, {}, {}, set()
        self.root = Path('.')

    def blob(self, c):
        return b'\0' * 0x100000


class InferTests(unittest.TestCase):
    def model(self, units, **kw):
        return I.Model(None, '.', units=units, repo=FakeRepo(), **kw)

    def test_call_locality_join_and_strong_width(self):
        # f0 is a static-looking helper called only by its neighbour f1 (width 1 -> strong under pd4_cl2)
        fs = [fn(0, 0x100, 0x40, 'u/a'), fn(1, 0x140, 0x40, 'u/b', calls=[0x80000100]), fn(2, 0x180, 0x40, 'u/c')]
        m = self.model({'town/v1': unit('town/v1', fs)})
        ev = m.gap_evidence()
        dec = m.decide(ev)
        self.assertEqual(dec[('u/a', 'u/b')][:2], ('join', 'inferred-strong'))
        self.assertEqual(dec[('u/b', 'u/c')][0], 'none')

    def test_cross_image_reorder_is_a_cut_and_wins_conservatively(self):
        a = [fn(0, 0x100, 0x40, 'u/a'), fn(1, 0x140, 0x40, 'u/b'), fn(2, 0x180, 0x40, 'u/c')]
        b = [fn(0, 0x200, 0x40, 'u/b'), fn(1, 0x240, 0x40, 'u/a'), fn(2, 0x280, 0x40, 'u/c')]
        m = self.model({'town/v1': unit('town/v1', a), 'town/v2': unit('town/v2', b)})
        ev = m.gap_evidence()
        self.assertTrue(any(x.startswith('CX:') for x in ev[('u/a', 'u/b')]['cut']))
        self.assertEqual(m.decide(ev)[('u/a', 'u/b')][0], 'cut')

    def test_bank_order_is_only_a_weak_cut(self):
        a = [fn(0, 0x100, 0x40, 'd/a'), fn(1, 0x140, 0x40, 'd/b')]
        b = [fn(0, 0x200, 0x40, 'd/b'), fn(1, 0x240, 0x40, 'd/a')]
        m = self.model({'dungeon/bank_1': unit('dungeon/bank_1', a), 'dungeon/bank_2': unit('dungeon/bank_2', b)})
        ev = m.gap_evidence()
        self.assertFalse(ev[('d/a', 'd/b')]['cut'])
        self.assertTrue(any(x.startswith('CXB') for x in ev[('d/a', 'd/b')]['weakcut']))

    def test_proven_edges_are_hard(self):
        fs = [fn(0, 0x100, 0x40, 'u/a'), fn(1, 0x140, 0x40, 'u/b', calls=[0x80000100])]
        u = unit('town/v1', fs, edges=[dict(kind='B2', left=0, right=1, at='0x0')])
        m = self.model({'town/v1': u})
        dec = m.decide(m.gap_evidence())
        self.assertEqual(dec[('u/a', 'u/b')][:2], ('cut', 'proven'))

    def test_interval_edge_drops_inferred_joins(self):
        fs = [fn(0, 0x100, 0x40, 'u/a'), fn(1, 0x140, 0x40, 'u/b', calls=[0x80000100]),
              fn(2, 0x180, 0x40, 'u/c', calls=[0x80000140])]
        u = unit('town/v1', fs, edges=[dict(kind='B1', left=0, right=2, at='0x0')])
        m = self.model({'town/v1': u})
        ev = m.gap_evidence()
        gs = m.groups(ev, m.decide(ev), 'inferred-weak')['town/v1']
        self.assertFalse(any(lo <= 0 and 2 <= hi for lo, hi, _, _ in gs))

    def test_bayes_projection(self):
        b = I.bayes(47, 3, 150, 218)
        self.assertGreater(b['p_cut_0.1'], b['p_cut_0.6'])


class MergeTests(unittest.TestCase):
    def test_c_string_round_trips(self):
        for raw in (b'a"b\\c\n%d', b'\x82\x60\x82\x61', b'x\x011'):
            lit = M.c_string(raw)
            self.assertEqual(ast.literal_eval(lit).encode('latin1'), raw)

    def test_evidence_line_levels(self):
        self.assertIn('proven (string literals)', M.evidence_line(dict(evidence_level='proven', evidence=['J1:x'])))
        self.assertIn('inferred (adjacency/recipe/locality)',
                      M.evidence_line(dict(evidence_level='inferred-strong', evidence=['CL:x'])))
        self.assertEqual(M.evidence_line({}), '')

    def _root(self):
        root = Path(tempfile.mkdtemp(prefix='tu7-test-'))
        (root / 'config/link/main').mkdir(parents=True)
        (root / 'config/overlays').mkdir(parents=True)
        (root / 'config/link/main/img.json').write_text(json.dumps(dict(
            schema='azure-clean.linklist.v0', image='main/img', container='main', foff='0x1000', size='0x1000',
            vma='0x80401000', entries=[], evidence='test')))
        recs = [dict(schema='azure-clean.rowbase.v1', region='r1', foff_start='0x1100', foff_end='0x1200',
                     delta='0x80400000', base_confidence='proven', proof='p1'),
                dict(schema='azure-clean.rowbase.v1', region='r2', foff_start='0x1400', foff_end='0x1500',
                     delta='0x80400000', base_confidence='solved', proof='p2'),
                dict(schema='azure-clean.rowbase.v1', region='other', foff_start='0x5000', foff_end='0x5100',
                     delta='0x1', base_confidence='proven', proof='p3')]
        (root / 'config/overlays/main.rowbase.jsonl').write_text(
            '# header\n' + ''.join(json.dumps(r) + '\n' for r in recs))
        return root

    def test_consolidate_region_embeds_and_restores(self):
        root = self._root()
        try:
            base = root / 'base'
            out = M.consolidate_region(root, base, 'main/img')
            self.assertEqual(sorted(out['consolidated']), ['r1', 'r2'])
            recs = M.jl(root / 'config/overlays/main.rowbase.jsonl')
            self.assertEqual(len(recs), 2)
            new = next(r for r in recs if r['region'] == 'link_img')
            self.assertEqual((new['foff_start'], new['foff_end']), ('0x1000', '0x2000'))
            self.assertEqual([r['region'] for r in new['consolidated']], ['r1', 'r2'])
            M.restore(root, base)
            self.assertEqual(len(M.jl(root / 'config/overlays/main.rowbase.jsonl')), 3)
        finally:
            shutil.rmtree(root)

    def test_consolidate_region_refuses_foreign_delta(self):
        root = self._root()
        try:
            p = root / 'config/overlays/main.rowbase.jsonl'
            p.write_text(p.read_text().replace('"0x5000"', '"0x1800"').replace('"0x5100"', '"0x1900"'))
            with self.assertRaises(M.Refused):
                M.consolidate_region(root, root / 'base', 'main/img')
        finally:
            shutil.rmtree(root)

    def test_reattribute_updates_split_ledger_and_rows(self):
        root = Path(tempfile.mkdtemp(prefix='tu7-test-'))
        try:
            (root / 'ledger/splits').mkdir(parents=True)
            (root / 'ledger/splits/main.jsonl').write_text(
                json.dumps(dict(func_vram='func_1', result='MATCH', config='2.7.2')) + '\n' +
                json.dumps(dict(func_vram='func_2', result='MATCH', config='2.6.3-G0')) + '\n')
            (root / 'ledger/rows.jsonl').write_text(
                json.dumps(dict(id='main/func_1', cfg='2.7.2', cell='2.7.2', flags='')) + '\n' +
                json.dumps(dict(id='main/func_2', cfg='2.6.3-G0', cell='2.6.3', flags='-G0')) + '\n')
            fr = M.Freezer(root, root / 'base')
            members = [dict(id='main/func_1', cfg='2.7.2', registered_cfg='2.7.2'),
                       dict(id='main/func_2', cfg='2.6.3-G0', registered_cfg='2.6.3-G0')]
            changed = M.reattribute(root, fr, 'main', members, '2.6.3-G0', 'test')
            self.assertEqual(changed, ['main/func_1'])
            sp = M.jl(root / 'ledger/splits/main.jsonl')
            self.assertEqual((sp[0]['config'], sp[0]['config_was']), ('2.6.3-G0', '2.7.2'))
            self.assertIn('72(c)', sp[0]['config_note'])
            rows = M.jl(root / 'ledger/rows.jsonl')
            self.assertEqual((rows[0]['cfg'], rows[0]['cell'], rows[0]['flags']), ('2.6.3-G0', '2.6.3', '-G0'))
        finally:
            shutil.rmtree(root)


if __name__ == '__main__':
    unittest.main()
