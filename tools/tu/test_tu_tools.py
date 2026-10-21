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
from unittest.mock import patch
from collections import defaultdict
from pathlib import Path

HERE = Path(__file__).resolve().parent
sys.path.insert(0, str(HERE))
import infer_groups as I  # noqa: E402
import tu_merge as M  # noqa: E402
import tu_placements as P  # noqa: E402


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
    def test_identifier_list_definition_extents(self):
        source = ('s32 narrowed(s32 value);\n'
                  's32 narrowed(value)\ns16 value;\n{\n'
                  '    if (value) { return value; }\n    return 0;\n}\n'
                  's32 next(void) { return 1; }\n')
        found, _, _ = M.definitions(source)
        self.assertEqual([f[0] for f in found], ['narrowed', 'next'])
        self.assertEqual(source[found[0][1]:found[0][2]],
                         's32 narrowed(value)\ns16 value;\n')
        self.assertEqual(source[found[0][3]-1], '}')
        for malformed in ('s32 bad(x)\ns16 y;\n{ return 0; }',
                          's32 bad(x, x)\ns16 x;\n{ return 0; }'):
            self.assertEqual(M.definitions(malformed)[0], [])

    def test_body_macro_requires_exact_review_and_refuses_conditionals(self):
        with tempfile.TemporaryDirectory(prefix='tu-macro-') as td:
            root = Path(td)
            (root / 'src').mkdir()
            (root / 'config').mkdir()
            (root / 'config/names.tsv').write_text('')
            row = dict(container='dungeon', cfg='2.7.2-cdk-G0', foff=0, size=4, func='helper')
            spec = dict(container='dungeon', header='include/merged.h', modules=[
                dict(key='test_macro', source='src/merged.c', members=['dungeon/helper'])])
            directive = '#define BODY_VALUE 1'
            with patch.object(M, 'load_repo', return_value=(
                    {'dungeon/helper': row}, {'dungeon/helper': 'src/member.c'})), \
                    patch.object(M, 'compile_obj', return_value=(root / 'unused.o', '')):
                for text, allowed, succeeds in (
                        (directive, [], False),
                        (directive, [directive], True),
                        ('#define BODY_VALUE 2', [directive], False),
                        ('#if BODY_VALUE\n#endif', ['#if BODY_VALUE', '#endif'], False)):
                    (root / 'src/member.c').write_text('int helper(void) {\n' + text + '\nreturn 1;\n}\n')
                    spec['body_directives'] = allowed
                    if succeeds:
                        M.draft(root, spec, root / 'draft', force=True)
                        self.assertIn(directive, (root / 'draft/tree/src/merged.c').read_text())
                    else:
                        with self.assertRaises(M.Refused):
                            M.draft(root, spec, root / 'draft', force=True)

    def test_promoted_c89_definition_extent(self):
        source = ('void shade(s32);\n'
                  'void shade(value)\n    u16 value;\n{\n    sink(value);\n}\n'
                  'void next(void) { shade(1); }\n')
        found, _, _ = M.definitions(source)
        self.assertEqual([f[0] for f in found], ['shade', 'next'])
        self.assertTrue(source[found[0][1]:found[0][3]].startswith('void shade(value)'))
        self.assertTrue(source[found[0][1]:found[0][3]].endswith('sink(value);\n}'))

    def test_unindexed_census_home_needs_no_placements_only_without_copies(self):
        module = dict(container='town', members=[dict(id='town/a', foff=0x1100, vma=0x80001100, size=32)])
        images = {'town/image_1000': dict(foff=0x1000, vma=0x80001000, size=0x1000),
                  'town/ll34_1000': dict(foff=0x1000, vma=0x80001000, size=0x1000),
                  'town/wrong_delta': dict(foff=0x1100, vma=0x80011100, size=32),
                  'town/file_view': dict(foff=0, vma=None, size=0x100000)}
        self.assertEqual(P.unindexed_home_image(module, images, {'town/a': dict(id='town/a')}), 'town/image_1000')
        with self.assertRaises(ValueError):
            P.unindexed_home_image(module, {'town/file_view': images['town/file_view']}, {})
        with self.assertRaises(ValueError):
            P.unindexed_home_image(module, images, {'town/b': dict(id='town/b', source_row='town/a')})
        with self.assertRaises(ValueError):
            P.unindexed_home_image(module, {'town/wrong_delta': images['town/wrong_delta']}, {})

    def test_registered_storage_alias_keeps_data_ownership(self):
        self.assertEqual(M.data_address('D_80100E24_R'), 0x80100E24)
        self.assertEqual(M.data_address('D_80100E24'), M.data_address('D_80100E24_R'))
        self.assertEqual(M.data_address('D_80100E24_1'), 0x80100E24)
        self.assertIsNone(M.data_address('func_80100E24'))

    def test_consolidate_preserves_installed_module_region(self):
        root = self._root()
        try:
            (root / 'config/overlays/modules.json').write_text(json.dumps(dict(modules=[
                dict(container='main', region='r1')])))
            out = M.consolidate_region(root, root / 'base', 'main/img')
            self.assertEqual(out['region'], 'r1')
            rec = next(r for r in M.jl(root / 'config/overlays/main.rowbase.jsonl') if r['region'] == 'r1')
            self.assertEqual([r['region'] for r in rec['consolidated']], ['r1', 'r2'])
        finally:
            shutil.rmtree(root)

    def test_consolidate_refuses_to_orphan_several_module_regions(self):
        root = self._root()
        try:
            (root / 'config/overlays/modules.json').write_text(json.dumps(dict(modules=[
                dict(container='main', region='r1'), dict(container='main', region='r2')])))
            path = root / 'config/overlays/main.rowbase.jsonl'
            before = path.read_bytes()
            with self.assertRaises(M.Refused):
                M.consolidate_region(root, root / 'base', 'main/img')
            self.assertEqual(path.read_bytes(), before)
        finally:
            shutil.rmtree(root)

    def test_consolidate_region_retains_existing_module_name(self):
        root = self._root()
        try:
            (root / 'config/overlays/modules.json').write_text(json.dumps(dict(modules=[
                dict(container='main', region='r1'), dict(container='main', region='r1')])) )
            out = M.consolidate_region(root, root / 'base', 'main/img')
            self.assertEqual(out['region'], 'r1')
            rec = next(r for r in M.jl(root / 'config/overlays/main.rowbase.jsonl') if r['region'] == 'r1')
            self.assertEqual((rec['foff_start'], rec['foff_end']), ('0x1000', '0x2000'))
            self.assertEqual([r['region'] for r in rec['consolidated']], ['r1', 'r2'])
        finally:
            shutil.rmtree(root)

    def test_consolidate_region_refuses_multiple_module_names_without_writing(self):
        root = self._root()
        try:
            p = root / 'config/overlays/main.rowbase.jsonl'
            before = p.read_bytes()
            (root / 'config/overlays/modules.json').write_text(json.dumps(dict(modules=[
                dict(container='main', region='r1'), dict(container='main', region='r2')])) )
            with self.assertRaises(M.Refused):
                M.consolidate_region(root, root / 'base', 'main/img')
            self.assertEqual(p.read_bytes(), before)
        finally:
            shutil.rmtree(root)

    def test_placement_preserves_a_resident_asset_map(self):
        sys.path.insert(0, str(HERE.parent / 'gate'))
        import tu_placements as P
        root = Path(tempfile.mkdtemp(prefix='tu11-test-'))
        try:
            (root / 'docs').mkdir()
            mp = dict(kind='rowbase', container='dungeon', region='engine',
                      asset='work/disc/containers/DUNGEON_DUNGEON.BIN',
                      file_start=0xA3000, file_end=0x100000, delta=0x7FFE5760, basis='resident engine')
            old = dict(symbol='D_800E3D7C', kind='data', vma=0x800E3D7C, foff=0xFE61C,
                       view_bytes=4, owner='retail_asset:work/disc/containers/DUNGEON_DUNGEON.BIN',
                       asset=mp['asset'], map='resident_engine', evidence='docs/home.json')
            (root / 'docs/home.json').write_text(json.dumps(dict(maps={'resident_engine': mp})))
            m = dict(key='test_g00259', container='dungeon', recipe=dict(cfg='2.7.2-cdk-G0', row_asflags=''), imports=[old])
            image = dict(image='dungeon/bank_dest', foff=0xE5D000, size=0x6000, vma=0x8016A800)
            entries = [dict(home='dungeon/home', row='dungeon/copy')]
            with patch('linklist._binding', return_value=old['vma']), patch.object(P, 'storage_image', side_effect=AssertionError):
                desc, evidence_path, proof = P.descriptor(root, m, 'dungeon/home', {'dungeon/bank_dest': image}, None, 'dungeon/bank_dest', entries)
            self.assertEqual(desc['imports'], [dict(old, evidence=evidence_path)])
            self.assertEqual(proof['maps']['resident_engine'], mp)
            self.assertEqual(proof['views'][old['symbol']], desc['imports'][0])
            with patch('linklist._binding', return_value=old['vma'] + 4):
                with self.assertRaisesRegex(ValueError, 'moves without a destination proof'):
                    P.descriptor(root, m, 'dungeon/home', {'dungeon/bank_dest': image}, None, 'dungeon/bank_dest', entries)
        finally:
            shutil.rmtree(root)

    def test_include_facade_replaces_members_once_and_keeps_order(self):
        source = '#include "game.h"\n#include "../one.c"\n#include "../two.c"\n#include "../three.c"\n'
        paths = {'src/ovmovie/one.c': 'src/ovmovie/merged.c',
                 'src/ovmovie/two.c': 'src/ovmovie/merged.c'}
        self.assertEqual(M.rewrite_include_facade(source, 'src/ovmovie/modules/all.c', paths),
                         '#include "game.h"\n#include "../merged.c"\n#include "../three.c"\n')

    def test_c89_grouped_parameter_declarations(self):
        source = ('void project(a, b, c, d, shade)\n'
                  '    Coord8 a, b;\n    Packed8 c, d;\n    u16 shade;\n'
                  '{\n    sink(shade);\n}\nvoid next(void) { }\n')
        found, _, _ = M.definitions(source)
        self.assertEqual([f[0] for f in found], ['project', 'next'])
        self.assertTrue(source[found[0][1]:found[0][3]].endswith('sink(shade);\n}'))
        self.assertEqual(M.definitions(source.replace('Coord8 a, b;', 'Coord8 a, missing;'))[0][0][0], 'next')

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

    def test_consolidation_keeps_a_live_module_region_name(self):
        root = self._root()
        try:
            (root / 'config/overlays/modules.json').write_text(json.dumps(dict(
                modules=[dict(container='main', region='r1')])) )
            result = M.consolidate_region(root, root / 'base', 'main/img')
            self.assertEqual(result['region'], 'r1')
            record = next(r for r in M.jl(root / 'config/overlays/main.rowbase.jsonl') if r['region'] == 'r1')
            self.assertEqual([r['proof'] for r in record['consolidated']], ['p1', 'p2'])
        finally:
            shutil.rmtree(root)

    def test_header_closure_follows_source_relative_shared_contract(self):
        root = self._root()
        try:
            for directory in ('include/ovmovie', 'include/shared', 'src/ovmovie/modules'):
                (root / directory).mkdir(parents=True, exist_ok=True)
            (root / 'include/ovmovie/merged.h').write_text('#include "../../src/ovmovie/modules/game.h"\n')
            (root / 'src/ovmovie/modules/game.h').write_text('#include "shared/state.h"\n')
            (root / 'include/shared/state.h').write_text('extern int state;\n')
            self.assertEqual(M.header_closure(root, 'include/ovmovie/merged.h'),
                             ['include/ovmovie/merged.h', 'src/ovmovie/modules/game.h', 'include/shared/state.h'])
        finally:
            shutil.rmtree(root)

    def test_file_view_requires_extent_and_derives_only_proven_delta(self):
        root = self._root()
        try:
            sys.path.insert(0, str(HERE.parent))
            from byte_map_format import write, LABELS
            write(root / 'link/ovmovie', dict(schema='azure-clean.linklist.v1',
                image='ovmovie/ovmovie_bin', container='ovmovie', foff=0, size=0x300000,
                vma=None, evidence='Physical file only', census={k: 0 for k in LABELS},
                entries=[dict(kind='padding', foff=0, size=0x300000, evidence='test')]))
            record = dict(schema='azure-clean.rowbase.v1', region='resident', foff_start='0x0',
                          foff_end='0x1B88', delta='0x80176800', base_confidence='proven', proof='prior proof')
            (root / 'config/overlays/ovmovie.rowbase.jsonl').write_text(json.dumps(record) + '\n')
            with self.assertRaises(M.Refused):
                M.consolidate_region(root, root / 'base', 'ovmovie/ovmovie_bin')
            result = M.consolidate_region(root, root / 'base', 'ovmovie/ovmovie_bin', 0, 0x1B88)
            self.assertEqual((result['foff_end'], result['delta']), ('0x1B88', '0x80176800'))
        finally:
            shutil.rmtree(root)

    def _data_hypothesis_root(self, label='proven_data', confidence='solved', registered=False):
        root = self._root()
        (root / 'ledger').mkdir()
        rows = [dict(id='main/registered', container='main', foff=0x1800, size=4)] if registered else []
        (root / 'ledger/rows.jsonl').write_text(''.join(json.dumps(r) + '\n' for r in rows))
        record = dict(region='foreign_guess', foff_start='0x1800', foff_end='0x2100',
                      delta='0x80410000', base_confidence=confidence, proof='old j-solve hypothesis')
        with (root / 'config/overlays/main.rowbase.jsonl').open('a') as f:
            f.write(json.dumps(record) + '\n')
        sys.path.insert(0, str(HERE.parent))
        from byte_map_format import write, LABELS
        write(root / 'link/main', dict(schema='azure-clean.linklist.v1', image='main/img', container='main',
            foff=0x1000, size=0x1000, vma=0x80401000, evidence='test image', census={k: 0 for k in LABELS},
            entries=[dict(kind='asset', foff=0x1800, size=0x800, evidence='census:audit+noncode_confirmed',
                          census_label=label, sha256='a' * 64)]))
        return root, record

    def test_data_hypothesis_supersession_is_explicit_and_preserves_remainder(self):
        root, original = self._data_hypothesis_root()
        try:
            with self.assertRaises(M.Refused):
                M.consolidate_region(root, root / 'strict', 'main/img')
            result = M.consolidate_region(root, root / 'base', 'main/img', supersede_data_hypotheses=True)
            self.assertEqual(result['superseded_data_hypotheses'], ['foreign_guess'])
            records = M.jl(root / 'config/overlays/main.rowbase.jsonl')
            remnant = next(r for r in records if r['region'] == 'foreign_guess')
            self.assertEqual((remnant['foff_start'], remnant['foff_end']), ('0x2000', '0x2100'))
            merged = next(r for r in records if r['region'] == 'link_img')
            self.assertEqual(merged['superseded_data_hypotheses'][0]['original_hypothesis'], original)
            M.restore(root, root / 'base')
            self.assertIn(original, M.jl(root / 'config/overlays/main.rowbase.jsonl'))
        finally:
            shutil.rmtree(root)

    def test_data_hypothesis_supersession_refuses_code_proven_regions_and_registered_rows(self):
        for opts in (dict(label='proven_code'), dict(confidence='proven'), dict(registered=True)):
            with self.subTest(opts=opts):
                root, original = self._data_hypothesis_root(**opts)
                try:
                    before = (root / 'config/overlays/main.rowbase.jsonl').read_bytes()
                    with self.assertRaises(M.Refused):
                        M.consolidate_region(root, root / 'base', 'main/img', supersede_data_hypotheses=True)
                    self.assertEqual((root / 'config/overlays/main.rowbase.jsonl').read_bytes(), before)
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
