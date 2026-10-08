"""Region-aware incremental SHA regression tests, with lane-independent temp roots."""
import importlib.util
import json
import tempfile
import unittest
from pathlib import Path
from unittest.mock import patch

REPO = Path(__file__).resolve().parents[2]
spec = importlib.util.spec_from_file_location('gate_all_scoped_test', REPO/'tools/build/gate_all.py')
G = importlib.util.module_from_spec(spec)
spec.loader.exec_module(G)
import common
from gate import gen_noreturn_syms as C


class ScopedInputsFixture(unittest.TestCase):
    def setUp(self):
        self.tmp = tempfile.TemporaryDirectory()
        self.addCleanup(self.tmp.cleanup)
        self.root = Path(self.tmp.name)
        for n in ['config/overlays', 'ledger/splits', 'raw/dungeon', 'raw/town',
                  'src/dungeon', 'src/dungeon_engine', 'src/town', 'src/main',
                  'src/slus', 'src/ovmovie']:
            (self.root/n).mkdir(parents=True)
        for obj, attr, value in [(G,'ROOT',self.root), (G,'_WROWS',None),
                (G,'_WMODULES',None), (G,'_SPLITS',{}),
                (common,'ROOT',self.root), (common,'_WM',None)]:
            ctx=patch.object(obj,attr,value);ctx.start();self.addCleanup(ctx.stop)
        self.regions = [{'region':'a','foff_start':'0x100','foff_end':'0x200'},
                        {'region':'b','foff_start':'0x300','foff_end':'0x400'}]
        self.reg=[]
        for fam in ['town','dungeon']:
            self.write(f'config/overlays/{fam}.rowbase.jsonl',self.regions)
            splits=[]
            for off, matched in [(0x100,True),(0x110,False),(0x300,True),
                                 (0x310,False),(0x500,True),(0x510,False)]:
                name=f'func_{off:08X}.c'
                splits.append({'foff':off,'size':16,'func_vram':name[:-2],
                    'c_path':name,'result':'MATCH' if matched else 'CFAIL'})
                (self.root/f'raw/{fam}/{name}').write_text(self.decl(f'{fam}_{off:X}'))
                if matched:self.row(fam,off,name)
            self.write(f'ledger/splits/{fam}.jsonl',splits)
        engine={'foff':0x150,'size':16,'func_vram':'engine','c_path':'engine.c','result':'MATCH'}
        self.write('ledger/splits/dungeon_engine.jsonl',[engine])
        (self.root/'raw/dungeon/engine.c').write_text(self.decl('engine_evidence'))
        self.row('dungeon_engine',0x150,'engine.c')
        for fam in ['main','slus','ovmovie']:self.write(f'ledger/splits/{fam}.jsonl',[])
        self.write('ledger/rows.jsonl',self.reg)
        self.write(C.FALSE_MEMBERS_PATH,[])
        self.windows={}
        for name,fs,fe,cont in [('dungeon_a',0x100,0x110,'dungeon'),
                ('dungeon_b',0x300,0x310,'dungeon'),
                ('dungeon_cross',0x100,0x400,'dungeon'),
                ('dungeon_isolated',0x500,0x510,'dungeon'),
                ('dungeon_empty',0x310,0x320,'dungeon'),
                ('dungeon_engine',0x150,0x160,'dungeon'),
                ('town_a',0x100,0x110,'town'),
                ('town_b',0x300,0x310,'town'),
                ('main_boot',0x100,0x110,'main'),
                ('slus_test',0x100,0x110,'slus'),
                ('ovmovie_test',0x100,0x110,'ovmovie')]:
            p=self.root/f'config/overlays/{name}.overlay.yaml'
            p.write_text(f'name: {name}\noptions:\n  target_path: work/{cont.upper()}_{cont.upper()}.BIN\n'
                         f'standalone_build:\n  window:\n    file_start: {fs:#x}\n    file_end: {fe:#x}\n')
            self.windows[name]=p

    @staticmethod
    def decl(name):return f'extern void {name}(void) __attribute__((noreturn));\n'

    def row(self,fam,off,name):
        (self.root/f'src/{fam}/{name}').write_text('void caller(void) {}\n')
        self.reg.append({'id':f'{fam}/{name[:-2]}','kind':'overlay','container':fam,
                         'foff':off,'size':16,'c_path':name})

    def write(self,name,records):
        (self.root/name).write_text(''.join(json.dumps(r)+'\n' for r in records))

    def shas(self):return {n:G.inputs_sha(p) for n,p in self.windows.items()}

    def changed(self,before):
        after=self.shas()
        return {n for n in before if not G.gate_current(
            {'result':'MATCH','inputs_sha':before[n]},after[n])}


class InputsShaBankScopes(ScopedInputsFixture):
    def test_raw_edit_regates_region_including_engine_and_crossing_window_only(self):
        before=self.shas()
        (self.root/'raw/dungeon/func_00000110.c').write_text(self.decl('new_callee'))
        self.assertEqual(self.changed(before),{'dungeon_a','dungeon_engine','dungeon_cross'})

    def test_other_region_raw_edit_does_not_regate_a(self):
        before=self.shas()
        (self.root/'raw/dungeon/func_00000310.c').write_text(self.decl('new_callee'))
        self.assertEqual(self.changed(before),{'dungeon_b','dungeon_cross'})

    def test_rowbase_extent_edit_regates_affected_regions(self):
        before=self.shas()
        self.regions[0]['foff_start']='0x110'
        self.write('config/overlays/dungeon.rowbase.jsonl',self.regions)
        self.assertEqual(self.changed(before),{'dungeon_a','dungeon_engine','dungeon_cross'})

    def test_scope_identity_edit_is_local_even_when_names_are_unchanged(self):
        before=self.shas()
        self.regions[1]['region']='b_renamed'
        self.write('config/overlays/dungeon.rowbase.jsonl',self.regions)
        self.assertEqual(self.changed(before),{'dungeon_b','dungeon_cross'})

    def test_false_member_edit_regates_its_family_even_if_not_in_region(self):
        before=self.shas()
        self.write(C.FALSE_MEMBERS_PATH,[{'schema':C.FALSE_MEMBER_SCHEMA,'family':'dungeon',
                   'func':'outside_all_scopes','proof':'test evidence'}])
        self.assertEqual(self.changed(before),{n for n in before if n.startswith('dungeon')})

    def test_town_false_member_does_not_regate_dungeon_or_nonbanked_families(self):
        before=self.shas()
        self.write(C.FALSE_MEMBERS_PATH,[{'schema':C.FALSE_MEMBER_SCHEMA,'family':'town',
                   'func':'town_110','proof':'test evidence'}])
        self.assertEqual(self.changed(before),{'town_a','town_b'})

    def test_unmapped_raw_edit_is_isolated_and_neighbor_does_not_leak(self):
        before=self.shas()
        (self.root/'raw/dungeon/func_00000510.c').write_text(self.decl('neighbor_change'))
        self.assertEqual(self.changed(before),set())
        (self.root/'raw/dungeon/func_00000500.c').write_text(self.decl('own_change'))
        self.assertEqual(self.changed(before),{'dungeon_isolated'})

    def test_comments_and_duplicate_declarations_do_not_change_evidence(self):
        before=self.shas()
        p=self.root/'raw/dungeon/func_00000110.c'
        p.write_text(p.read_text()+'/* comment */\n'+self.decl('dungeon_110'))
        self.assertEqual(self.changed(before),set())

    def test_both_readers_select_identical_names_and_distinct_scopes_are_deduped(self):
        inp=C.scoped_inputs('dungeon',[0x100,0x150,0x100,0x300,0x500],root=self.root)
        self.assertEqual(len(inp['scopes']),3)
        expected=[sorted(C.scoped_census('dungeon',off,root=self.root)['names'])
                  for off in [0x100,0x300,0x500]]
        self.assertEqual([x['names'] for x in inp['scopes']],expected)

    def test_overlapping_regions_fail_closed_in_hashing(self):
        self.regions[1]['foff_start']='0x180'
        self.write('config/overlays/dungeon.rowbase.jsonl',self.regions)
        with self.assertRaisesRegex(ValueError,'overlapping'):self.shas()


if __name__=='__main__':unittest.main()

class InputsShaSnapshots(ScopedInputsFixture):
    def test_snapshot_matches_fresh_hashes_and_refreshes_on_next_sweep(self):
        before=self.shas()
        with G.inputs_snapshot():self.assertEqual(before,self.shas())
        (self.root/'raw/dungeon/func_00000110.c').write_text(self.decl('new_callee'))
        with G.inputs_snapshot():after=self.shas()
        self.assertNotEqual(before['dungeon_a'],after['dungeon_a'])
        self.assertEqual(after,self.shas())

    def test_snapshot_is_discarded_on_exception(self):
        with self.assertRaisesRegex(RuntimeError,'abort'):
            with G.inputs_snapshot():
                self.shas()
                raise RuntimeError('abort')
        (self.root/'raw/dungeon/func_00000110.c').write_text(self.decl('new_callee'))
        self.assertEqual(C.scoped_inputs('dungeon',[0x100],root=self.root)['scopes'][0]['names'],
                         sorted(C.scoped_census('dungeon',0x100,root=self.root)['names']))

    def test_snapshot_does_not_leak_to_worker_thread(self):
        from concurrent.futures import ThreadPoolExecutor
        with G.inputs_snapshot():
            before=G.inputs_sha(self.windows['dungeon_a'])
            (self.root/'raw/dungeon/func_00000110.c').write_text(self.decl('new_callee'))
            with ThreadPoolExecutor(max_workers=1) as pool:
                after=pool.submit(G.inputs_sha,self.windows['dungeon_a']).result()
        self.assertNotEqual(before,after)
        self.assertEqual(after,G.inputs_sha(self.windows['dungeon_a']))

    def test_split_index_preserves_ledger_order_and_inclusive_zero_size_boundary(self):
        records=[{'foff':0x110,'size':0,'marker':'end'},
                 {'foff':0x100,'size':16,'marker':'first'},
                 {'foff':0x105,'size':32,'marker':'overrun'},
                 {'foff':0x100,'size':8,'marker':'duplicate'}]
        G._SPLITS['dungeon']=records
        self.assertEqual(G.split_records('dungeon','dungeon_a.overlay.yaml'),
                         [records[i] for i in [0,1,3]])

class InputsShaRegionMoves(ScopedInputsFixture):
    def test_rowbase_transfer_regates_both_affected_regions(self):
        before=self.shas()
        self.regions[0]['foff_end']='0x110'
        self.regions[1]['foff_start']='0x110'
        self.write('config/overlays/dungeon.rowbase.jsonl',self.regions)
        self.assertEqual(self.changed(before),{'dungeon_a','dungeon_b','dungeon_engine','dungeon_cross'})

    def test_town_raw_change_is_confined_to_town_region(self):
        before=self.shas()
        (self.root/'raw/town/func_00000110.c').write_text(self.decl('town_new'))
        self.assertEqual(self.changed(before),{'town_a'})
