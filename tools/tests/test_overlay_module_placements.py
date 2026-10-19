"""LL5 negative fixtures; all bytes here are synthetic, never retail payload."""
import copy
import json
import os
from pathlib import Path
import shutil
import struct
import subprocess
import sys
import tempfile
import unittest
from unittest.mock import patch

TOOLS = Path(__file__).resolve().parents[1]
sys.path[:0] = [str(TOOLS / 'gate'), str(TOOLS), str(TOOLS / 'fidelity')]
import overlay_module_gate as G
import overlay_module_placements as P
import linklist


class PlacementContract(unittest.TestCase):
    def setUp(self):
        self.tmp = tempfile.TemporaryDirectory(dir=os.environ.get('TMPDIR'))
        self.addCleanup(self.tmp.cleanup)
        self.root = Path(self.tmp.name)
        for name in ('config/link/dungeon', 'config/overlays', 'ledger/splits', 'docs'):
            (self.root / name).mkdir(parents=True, exist_ok=True)
        self.m = dict(key='test_module', container='dungeon', source='src/dungeon/modules/test.c',
                      recipe=dict(cfg='2.7.2-cdk-G0', row_asflags=''), owned_data=[], imports=[],
                      members=[dict(id='dungeon/func_80000100', source='src/dungeon/func_80000100.c', function='func_80100100', foff=0x100, vma=0x80100100, size=8),
                               dict(id='dungeon/func_80000108', source='src/dungeon/func_80000108.c', function='func_80100108', foff=0x108, vma=0x80100108, size=8)])
        self.rows = []; home = []; dest = []; members = []; splits = []
        for a in self.m['members']:
            rid = a['id'].replace('800001', '800002'); members.append(dict(home=a['id'], row=rid))
            home.append(dict(row=a['id'], home=a['id'], tu=a['source'], foff=a['foff'], vma=a['vma'], size=a['size']))
            dest.append(dict(row=rid, home=a['id'], tu=a['source'], foff=a['foff']+0x100, vma=a['vma']-0x1000, size=a['size']))
            self.rows.extend([dict(id=a['id'], kind='overlay', container='dungeon', foff=a['foff'], size=a['size'], cfg='2.7.2-cdk-G0'),
                              dict(id=rid, kind='overlay', container='dungeon', foff=a['foff']+0x100, size=a['size'], cfg='2.7.2-cdk-G0', source_row=a['id'])])
            splits.append(dict(func_vram=rid.split('/')[1], foff=a['foff']+0x100, size=a['size'], true_vram=a['vma']-0x1000, result='MATCH'))
        self.image('home', 0x100, 0x80100100, home)
        self.image('dest', 0x200, 0x800ff100, dest)
        self.write('ledger/rows.jsonl', self.rows, lines=True)
        self.write('ledger/splits/dungeon.jsonl', splits, lines=True)
        (self.root/'docs/review.json').write_text('{}')
        self.p = dict(key='test_module_dest', module='test_module', image='dungeon/dest', home_image='dungeon/home',
                      recipe=self.m['recipe'], members=members, imports=[], review_inputs=['docs/review.json'],
                      review=dict(membership='reviewed', types='reviewed', ownership='reviewed', reviewer='fixture'))
        self.manifest()
        self.m['review']=self.p['review']
        self.region = dict(foff_start='0x200', foff_end='0x210', delta=hex(0x800ff100-0x200), base_confidence='proven')
        self.addCleanup(patch.stopall)
        patch.object(G, 'load_modules', return_value=[self.m]).start()
        patch.object(G, 'ranges', return_value=[self.region]).start()

    def write(self, name, value, lines=False):
        (self.root/name).write_text(''.join(json.dumps(v)+'\n' for v in value) if lines else json.dumps(value))

    def image(self, name, foff, vma, entries):
        self.write('config/link/dungeon/'+name+'.json', dict(schema=linklist.SCHEMA, image='dungeon/'+name,
                   container='dungeon', foff=foff, vma=vma, size=16, layout='same_family', entries=entries))

    def manifest(self, ps=None):
        self.write(P.MANIFEST, dict(schema=P.SCHEMA, placements=[self.p] if ps is None else ps))
        self.write('docs/review.json',dict(schema='azure-clean.module-placement-review.v2',module=self.p['module'],placement=self.p['key'],
                   placement_descriptor=self.p,review=self.p['review'],basis='synthetic exact destination review'))

    def test_complete_tuple_and_owner(self):
        empty=self.root/'empty';empty.mkdir()
        subprocess.run([sys.executable,'-c','from pathlib import Path; import sys; from source_layout import physical_owner; assert physical_owner("dungeon/unknown",Path(sys.argv[1])) is None',str(empty)],cwd=empty,
                       env=dict(os.environ,PYTHONPATH=str(TOOLS),PYTHONDONTWRITEBYTECODE='1'),check=True,capture_output=True)
        p, = P.load(self.root)
        self.assertEqual([a['foff'] for a in p['projected']], [0x200, 0x208])
        self.assertEqual(P.owner(self.root, self.p['members'][1]['row'])['source'], self.m['source'])

    def test_public_owner_resolves_home_without_admitting_a_copy(self):
        import importlib.util
        spec=importlib.util.spec_from_file_location('public_layout_fixture',TOOLS/'source_layout.py')
        facade=importlib.util.module_from_spec(spec);spec.loader.exec_module(facade)
        rid='dungeon/unadmitted';home=self.m['members'][0]['id']
        # Ownership is the physical home TU; this supplies no placement proof.
        with patch.object(facade,'registry',return_value={rid:dict(source_row=home)}),patch.object(facade,'row_relative',return_value=self.m['members'][0]['source']):
            self.assertEqual(facade.physical_owner(rid,self.root)['key'],self.m['key'])
        self.assertEqual(P.valid_placements(self.root),{})

    def test_unadmitted_fileless_staging_is_rejected_before_ordinary_deferral(self):
        from lanes import native_package as NP
        lane=self.root/'lane';out=lane/'out/dungeon';out.mkdir(parents=True)
        (out/'unadmitted.c').write_text('/* synthetic staged row */')
        rid='dungeon/unadmitted';rows={rid:dict(id=rid,source_row=self.m['members'][0]['id'])}
        self.write('config/overlays/modules.json',dict(modules=[self.m]))
        self.manifest([])
        with patch.object(NP,'ROOT',self.root),patch.object(NP.A,'context',return_value=(rows,{})):
            with self.assertRaisesRegex(ValueError,'fileless placement'):
                NP.collect([lane])
        # A link-list copy of an ordinary (non-module) home keeps the ordinary deferral.
        (out/'unadmitted.c').unlink();(out/'plain_copy.c').write_text('/* synthetic staged row */')
        rows={'dungeon/plain_copy':dict(id='dungeon/plain_copy',source_row='dungeon/plain_home')}
        with patch.object(NP,'ROOT',self.root),patch.object(NP.A,'context',return_value=(rows,{})):
            self.assertEqual(NP.collect([lane]),({},[],['dungeon/plain_copy'],False))

    def test_membership_recipe_and_projection_rejections(self):
        cases = [lambda p:p['members'].pop(), lambda p:p['members'].reverse(),
                 lambda p:p['members'].append(p['members'][0]),
                 lambda p:p['recipe'].update(cfg='2.7.2-G0'),
                 lambda p:p['members'][0].update(row=p['members'][1]['row']),
                 lambda p:p.update(home_image='dungeon/dest')]
        for change in cases:
            with self.subTest(change=change):
                p=copy.deepcopy(self.p);change(p);self.manifest([p])
                with self.assertRaises((ValueError, KeyError)):
                    P.load(self.root)

    def test_duplicate_ownership_rejected(self):
        self.manifest([self.p, dict(self.p, key='another')])
        with self.assertRaisesRegex(ValueError, 'duplicate module placement ownership'):
            P.load(self.root)

    def test_unowned_prefix_and_separated_allocations_rejected(self):
        for change in (dict(owned_data=[dict(size=4)]), dict(data_members=[dict(id='dungeon/prefix',size=4)]),
                       dict(members=[dict(self.m['members'][0], body_offset=4), self.m['members'][1]])):
            with self.subTest(change=change):
                with patch.object(G, 'load_modules', return_value=[dict(self.m, **change)]):
                    with self.assertRaises((ValueError, KeyError)):
                        P.load(self.root)
        with patch.object(G, 'load_modules', return_value=[dict(self.m, allocation_model=G.Z.MODEL)]):
            with self.assertRaises((ValueError, KeyError)):
                P.load(self.root)

    def test_complete_composite_prefix_keeps_every_native_byte(self):
        m=copy.deepcopy(self.m)
        m['members'][0]['body_offset']=4
        m['owned_data']=[dict(section='.rodata',foff=0x100,vma=0x80100100,size=4,
                              kind='typed_function_pointer',symbol='entry',target=m['members'][1]['function'])]
        m['membership_evidence']='docs/review.json'
        with patch.object(G, 'load_modules', return_value=[m]):
            p,=P.load(self.root)
            self.assertEqual(p['projected'][0]['size'],8)
            self.assertEqual(p['projected'][0]['body_offset'],4)
            self.assertEqual(sum(a['size'] for a in p['projected']),16)

    def test_separated_allocations_require_complete_destination_and_load_coverage(self):
        m=copy.deepcopy(self.m);m['allocation_model']=G.Z.MODEL
        m['allocations']=[dict(section='.text.*',foff=0x100,vma=0x80100100,size=16,link_alignment=4),
                          dict(section='.data',foff=0x180,vma=0x80100180,size=4,link_alignment=4,slots=[])]
        for image in ('home','dest'):
            path=self.root/('config/link/dungeon/'+image+'.json');doc=json.loads(path.read_text());doc['size']=0x100;path.write_text(json.dumps(doc))
        self.region['foff_end']='0x300'
        self.p['allocations']=[dict(a,foff=a['foff']+0x100,vma=a['vma']-0x1000) for a in m['allocations']]
        self.manifest()
        with patch.object(G,'load_modules',return_value=[m]):
            p,=P.load(self.root)
            self.assertTrue(P.intersects(p,0x280,0x284))
            self.assertFalse(P.intersects(p,0x240,0x250))
            self.p['allocations'].pop();self.manifest()
            with self.assertRaisesRegex(ValueError,'allocations differ'):
                P.load(self.root)
            self.p['allocations']=p['allocations'];self.manifest()
            self.region['foff_end']='0x210'
            with self.assertRaisesRegex(ValueError,'rowbase incomplete'):
                P.load(self.root)

    def test_destination_storage_must_contain_code_and_share_its_load_map(self):
        view=dict(symbol='data',vma=0x800ff108,foff=0x208,view_bytes=8,owner='retail_asset:work/disc/containers/DUNGEON_DUNGEON.BIN',
                  asset='work/disc/containers/DUNGEON_DUNGEON.BIN',evidence='docs/storage.json',map='bank')
        mp=dict(kind='link_image',image='dungeon/dest',link_list='config/link/dungeon/dest.json',asset=view['asset'],
                file_start=0x200,file_end=0x210,delta=0x800ff100-0x200,basis='synthetic reviewed load map')
        proof=dict(maps=dict(bank=mp),views=dict(data=view));self.write('docs/storage.json',proof)
        P.validate_storage(self.root,view,self.p)
        mp['image']='dungeon/home';mp['link_list']='config/link/dungeon/home.json';self.write('docs/storage.json',proof)
        with self.assertRaisesRegex(ValueError,'storage view/load image'):
            P.validate_storage(self.root,view,self.p)

    def test_rowbase_and_source_row_fail_closed(self):
        self.region['delta']='0x1'
        with self.assertRaisesRegex(ValueError, 'rowbase'):
            P.load(self.root)
        self.region['delta']=hex(0x800ff100-0x200)
        self.rows[1]['source_row']=self.m['members'][1]['id'];self.write('ledger/rows.jsonl', self.rows, lines=True)
        with self.assertRaisesRegex(ValueError, 'identity differs'):
            P.load(self.root)

    def test_partial_and_changed_split_rejected(self):
        self.write('ledger/splits/dungeon.jsonl', [], lines=True)
        with self.assertRaisesRegex(ValueError, 'split identity'):
            P.load(self.root)

    def test_review_pending_and_scratch_never_grant_rows(self):
        p,=P.load(self.root)
        p['review']['reviewer']='pending';self.p['review']['reviewer']='pending';self.manifest()
        self.assertIn('review incomplete', P.certificate_reason(p, {}, self.root))
        self.assertEqual(P.valid_placements(self.root), {})
        self.assertFalse(P.review_complete(p['review']))

    def test_review_cannot_be_reused_for_another_tuple_or_descriptor_only_signature(self):
        p,=P.load(self.root)
        self.assertIsNone(P.review_reason(p,self.root))
        p['imports']=[dict(symbol='changed',kind='function',vma=1)]
        self.assertIn('review tuple differs',P.review_reason(p,self.root))
        proof=json.loads((self.root/'docs/review.json').read_text());proof['review']['reviewer']='pending'
        self.write('docs/review.json',proof)
        p,=P.load(self.root)
        self.assertIn('review tuple differs',P.review_reason(p,self.root))

    def test_stale_shard_and_missing_windows_rejected(self):
        p,=P.load(self.root)
        cert=dict(schema=P.SHARD_SCHEMA,kind='overlay_module_link_placement',placement=p['key'],module=p['module'],
                  image=p['image'],members=p['members'],reviewer='fixture',fingerprint={'old':1})
        with patch.object(P, 'fingerprint', return_value={'new':2}):
            self.assertIn('inputs changed',P.certificate_reason(p, cert, self.root))
        with patch.object(P, 'windows', return_value=['a','b']), patch.object(G,'affected_windows',return_value=['home']):
            self.assertEqual(P.affected_windows(self.m,self.root),['a','b','home'])

    def window_certificate(self):
        p,=P.load(self.root);before=dict(schema=P.SHARD_SCHEMA,sha256='fp',inputs=dict(windows={'window.yaml':{'sha256':'window-digest'}}))
        self.write('window.yaml',dict(standalone_build=dict(window=dict(file_start=0x200,file_end=0x210))))
        out=self.root/'proof';out.mkdir();(out/'module').mkdir()
        receipt=dict(fingerprint=before,artifact_sha256='artifact')
        self.write('proof/receipt.json',receipt);self.write('proof/module/receipt.json',receipt)
        (out/'window.bin').write_bytes(bytes(16));(out/'gate.log').write_text('MATCH\n')
        self.write('proof/manifest.json',dict(c_segments=[dict(file_start=hex(a['foff']),size=a['size'],module=p['module'],module_placement=p['key'],module_artifact_sha256='artifact') for a in p['projected']]))
        projection=dict(module=p['module'],placement=p['key'],image=p['image'],projected_rows=[a['id'] for a in p['projected']],
                        fingerprint='fp',artifact_sha256='artifact',receipt_sha256=G.sha(out/'module/receipt.json'))
        self.write('proof/projection.json',projection)
        w=dict(config='window.yaml',result='MATCH',digest='window-digest',proof_dir='proof',artifacts={name:G.sha(out/name) for name in
               ('window.bin','manifest.json','projection.json','gate.log','module/receipt.json')})
        cert=dict(schema=P.SHARD_SCHEMA,kind='overlay_module_link_placement',placement=p['key'],module=p['module'],image=p['image'],
                  members=p['members'],reviewer='fixture',fingerprint=before,proof_dir='proof',receipt_sha256=G.sha(out/'receipt.json'),
                  artifact_sha256='artifact',windows=[w])
        container=self.root/'work/disc/containers'/G.CONTAINERS['dungeon'];container.parent.mkdir(parents=True);container.write_bytes(bytes(0x210))
        return p,before,cert,projection

    def test_window_shards_missing_stale_shuffled_and_changed_neighbors(self):
        p,before,cert,projection=self.window_certificate()
        with patch.object(P,'fingerprint',return_value=before),patch.object(P,'receipt_reason',return_value=None),patch.object(P,'windows',return_value=['window.yaml']):
            self.assertIsNone(P.certificate_reason(p,cert,self.root))
            bad=copy.deepcopy(cert);bad['windows']=[]
            self.assertIn('not every',P.certificate_reason(p,bad,self.root))
            bad=copy.deepcopy(cert);bad['windows'][0]['digest']='old'
            self.assertIn('digest',P.certificate_reason(p,bad,self.root))
            projection['projected_rows'].reverse();self.write('proof/projection.json',projection)
            cert['windows'][0]['artifacts']['projection.json']=G.sha(self.root/'proof/projection.json')
            self.assertIn('shuffled',P.certificate_reason(p,cert,self.root))
        with patch.object(P,'fingerprint',return_value=dict(before,sha256='neighbor-changed')):
            self.assertIn('inputs changed',P.certificate_reason(p,cert,self.root))

    def test_no_certificate_can_grant_without_its_receipt(self):
        p,before,cert,_=self.window_certificate()
        (self.root/'ledger/modules').mkdir()
        self.write('ledger/modules/placement_'+p['key']+'.json',cert)
        (self.root/'proof/receipt.json').unlink()
        with patch.object(P,'fingerprint',return_value=before):
            self.assertEqual(P.valid_placements(self.root),{})

    def test_reader_only_grants_successful_complete_shards_with_proof_identity(self):
        p,=P.load(self.root)
        cert=dict(fingerprint={'sha256':'fp'},artifact_sha256='artifact',receipt_sha256='receipt',windows=[dict(config='a')])
        entries=[dict(placement=p,certificate=cert,valid=True),dict(placement=dict(p,projected=[dict(id='dungeon/failed')]),certificate=cert,valid=False)]
        with patch.object(P,'statuses',return_value=entries):
            grants=P.valid_placements(self.root)
        self.assertEqual(set(grants),{a['id'] for a in p['projected']})
        self.assertTrue(all(g['placement']==p['key'] and g['artifact_sha256']=='artifact' and g['window_proof_sha256'] for g in grants.values()))

    def test_changed_image_binding_invalidates_cached_descriptor(self):
        P.load(self.root)
        path=self.root/'config/link/dungeon/dest.json';doc=json.loads(path.read_text());doc['vma']+=4;path.write_text(json.dumps(doc))
        with self.assertRaisesRegex(ValueError,'image vma'):
            P.load(self.root)

    def test_pending_intent_is_not_a_renewal_obligation_and_removed_issued_rows_reject(self):
        self.assertEqual(P.recorded_statuses(self.root),[])
        folder=self.root/'ledger/modules';folder.mkdir()
        self.write('ledger/modules/placement_removed.json',dict(placement='removed',module=self.m['key']))
        with self.assertRaisesRegex(ValueError,'absent from intended roster'):
            P.recorded_statuses(self.root)

    def test_batch_renewal_includes_invalid_recorded_shards(self):
        from lanes import certify_batch as B
        p,=P.load(self.root)
        status=dict(placement=p,valid=False,reason='stale destination map')
        (self.root/'ledger/modules').mkdir()
        (self.root/'ledger/modules/placement_fixture.json').write_text('{}')
        with patch.object(B,'_statuses',return_value=[dict(module={'key':self.m['key']},valid=True)]),patch.object(P,'recorded_statuses',return_value=[status]):
            invalid=B.invalid_certificates(self.root,{self.m['key']:'fixture'})
            self.assertIn('stale destination map',invalid[self.m['key']])
            with self.assertRaisesRegex(ValueError,'no managed home certificate'):
                B.invalid_certificates(self.root,{})

    def test_shared_context_excludes_siblings_and_projects_to_copy_rows(self):
        import overlay_module_evidence as E
        self.m['headers']=['include/module.h']
        names={self.m['source'],*self.m['headers'],*(a['source'] for a in self.m['members'])}
        for name in names:
            path=self.root/name;path.parent.mkdir(parents=True,exist_ok=True)
            path.write_text('/* shared context '+name+' */')
        def closure(root,starts):
            return {'include/common.h'} if starts==['include/common.h','include/m2c_compat.h'] else names
        with patch.object(E,'load_modules',return_value=[self.m]),patch.object(E,'closure',side_effect=closure):
            contexts=E.source_contexts(self.root)
        shared={self.m['source'],*self.m['headers']}
        for member in self.p['members']:
            self.assertEqual(contexts[member['row']],contexts[member['home']])
            source=next(a['source'] for a in self.m['members'] if a['id']==member['home'])
            combined=(self.root/source).read_text()+'\n'+contexts[member['row']]
            # glue + headers enter every member and copy; sibling bodies keep their own
            # logical row checks (B16 home semantics: no sibling pins/asm leak into a row)
            self.assertTrue(all(('/* shared context '+name+' */') in combined for name in shared))
            self.assertTrue(all(('/* shared context '+a['source']+' */') not in contexts[member['row']] for a in self.m['members']))
            self.assertEqual(combined.count('/* shared context '+source+' */'),1)

    def test_portable_placement_inventory_round_trip_and_scratch_rejection(self):
        from lanes import proof_receipts as R
        p,=P.load(self.root);key=p['key'];folder=self.root/'ledger/modules';folder.mkdir()
        names=['work/module_placement_proofs/'+key+'/fixture/module','work/module_placement_proofs/'+key+'/fixture/window']
        for name in names:
            (self.root/name).mkdir(parents=True);(self.root/name/'synthetic-proof').write_text('fixture')
        cert=dict(placement=key,module=p['module'],proof_dir=names[0],windows=[dict(proof_dir=names[1])])
        self.write('ledger/modules/placement_'+key+'.json',cert)
        inputs=lambda *a:dict(review=R.sha(self.root/'docs/review.json'))
        with patch.object(R,'inputs',side_effect=inputs),patch.object(P,'certificate_reason',return_value=None):
            R.export_placement(self.root,key,self.root/'portable')
            self.assertEqual(R.verify(self.root,self.root/'portable')['kind'],'overlay-module-placement')
            R.import_placement(self.root,self.root/'portable')
            (self.root/'portable/proofs/0/synthetic-proof').write_text('changed')
            with self.assertRaisesRegex(ValueError,'artifacts changed'):
                R.import_placement(self.root,self.root/'portable')
        cert['kind']='overlay_module_link_placement_scratch';self.write('ledger/modules/placement_'+key+'.json',cert)
        with patch.object(R,'inputs',side_effect=inputs):
            with self.assertRaisesRegex(ValueError,'invalid placement certificate'):
                R.export_placement(self.root,key,self.root/'forbidden')


class SymbolicRelocations(unittest.TestCase):
    def native_artifact(self, root, directory, storage):
        """Real GNU ELF and genuine PsyQ LNK, built from synthetic assembly."""
        import aspsx_diff as A
        code='.globl func_80100104\n.type func_80100104,@function\nfunc_80100104:\n jr $31\n nop\n.size func_80100104,.-func_80100104\n'
        source='.set noreorder\n'+storage+'\n.section .text.func_80100104,"ax"\n'+code
        (directory/'test.s').write_text(source)
        subprocess.run(['mipsel-linux-gnu-as','-EL','-march=r3000','-o',directory/'module.o',directory/'test.s'],check=True,capture_output=True)
        genuine=source.replace('.section .rodata','.rdata').replace('.section .data','.data').replace('.section .text.func_80100104,"ax"','.text')
        # The short working directory also exercises the genuine tool's path limit.
        with tempfile.TemporaryDirectory(prefix='p',dir=root/'work') as td:
            temp=Path(td);(temp/'IN.S').write_bytes(A.aspsx_input(genuine))
            subprocess.run([root/'toolchain/genuine/bin/wibo',root/'toolchain/genuine/psyq/psyq4.4/ASPSX.EXE',
                            '-q','-G0','-o','OUT.OBJ','IN.S'],cwd=temp,check=True,capture_output=True)
            shutil.copy2(temp/'OUT.OBJ',directory/'OUT.OBJ')
        (directory/'receipt.json').write_text('{"synthetic":true}')

    @unittest.skipUnless(shutil.which('mipsel-linux-gnu-as') and (TOOLS.parent/'toolchain/genuine/bin/wibo').exists(), 'genuine MIPS tools required')
    def test_real_composite_and_separate_native_pointer_heads(self):
        root=TOOLS.parent
        with tempfile.TemporaryDirectory(dir=os.environ.get('TMPDIR')) as td:
            d=Path(td);home=d/'home';home.mkdir()
            self.native_artifact(root,home,'.section .rodata\n.globl entry\nentry:\n.word func_80100104\n')
            for separate in (False,True):
                a=dict(id='dungeon/home',source='function.c',function='func_80100104',foff=0x100,vma=0x80100100,size=12,body_offset=4)
                m=dict(key='synthetic_native',container='dungeon',owned_data=[dict(symbol='entry',kind='typed_function_pointer',
                       target=a['function'],section='.rodata',foff=0x100,vma=0x80100100,size=4)],members=[a],imports=[])
                if separate:
                    m['data_members']=[dict(id='dungeon/head',source='head.c',symbol='entry',foff=0x100,vma=0x80100100,size=4)]
                    a.update(foff=0x104,vma=0x80100104,size=8);a.pop('body_offset')
                projected=[dict(a,id=a['id']+'_copy',foff=a['foff']+0x100,vma=a['vma']-0x11000) for a in G.all_members(m)]
                p=dict(key='synthetic_dest',module=m['key'],image='dungeon/dest',projected=projected,members=[],imports=[])
                expected=struct.pack('<III',0x800ef104,0x03e00008,0)
                with patch.object(P,'artifact',return_value=home),patch.object(P,'load',return_value=[p]),patch.object(P,'fingerprint',return_value={'sha256':'fixture'}),patch.object(P,'retail',return_value=expected):
                    receipt,binary=P.build(p,m,d/('separate' if separate else 'composite'),root)
                self.assertEqual(binary.read_bytes(),expected)
                self.assertEqual(receipt['gate'],dict(result='MATCH',bytes=12,masked=0,raw_substitution_bytes=0))

    @unittest.skipUnless(shutil.which('mipsel-linux-gnu-as') and (TOOLS.parent/'toolchain/genuine/bin/wibo').exists(), 'genuine MIPS tools required')
    def test_real_separated_literal_allocations_preserve_gaps_and_reject_changed_bytes(self):
        root=TOOLS.parent
        with tempfile.TemporaryDirectory(dir=os.environ.get('TMPDIR')) as td:
            d=Path(td);home=d/'home';home.mkdir()
            self.native_artifact(root,home,'.section .data\n.globl words\nwords:\n.word 0x12345678\n')
            # GNU .data ends at its natural 16-byte alignment; bind the semantic
            # extent already verified by the home backend, without payload edits.
            blob=bytearray((home/'module.o').read_bytes());_,_,headers=G.Z.elf_headers(blob)
            section_index,_=headers['.data'];offset,stride,_=G.Z.elf_headers(blob)
            struct.pack_into('<I',blob,offset+section_index*stride+20,4);(home/'module.o').write_bytes(blob)
            a=dict(id='dungeon/home',source='function.c',function='func_80100104',foff=0x100,vma=0x80100104,size=8)
            allocations=[dict(section='.text.*',foff=0x100,vma=0x80100104,size=8,link_alignment=4),
                         dict(section='.data',foff=0x200,vma=0x80100204,size=4,link_alignment=4,
                              slots=[dict(symbol='words',offset=0,size=4,kind='u32_words',source='storage.c')])]
            m=dict(key='synthetic_allocations',container='dungeon',allocation_model=G.Z.MODEL,owned_data=[],members=[a],imports=[],allocations=allocations)
            p=dict(key='synthetic_dest',module=m['key'],image='dungeon/dest',members=[],imports=[],
                   projected=[dict(a,id='dungeon/copy',foff=0x300,vma=0x800f0104)],
                   allocations=[dict(a,foff=a['foff']+0x200,vma=a['vma']-0x10000) for a in allocations])
            expected=struct.pack('<III',0x03e00008,0,0x12345678)
            with patch.object(P,'artifact',return_value=home),patch.object(P,'load',return_value=[p]),patch.object(P,'fingerprint',return_value={'sha256':'fixture'}),patch.object(P,'retail',return_value=expected):
                receipt,binary=P.build(p,m,d/'placed',root)
                self.assertEqual(binary.read_bytes(),expected)
                with patch.object(P,'retail',return_value=expected[:-1]+b'!'):
                    with self.assertRaisesRegex(ValueError,'retail mismatch'):
                        P.build(p,m,d/'changed',root)

    @unittest.skipUnless(shutil.which('mipsel-linux-gnu-as'), 'MIPS binutils required')
    def test_paired_addend_survives_and_external_aliases_link(self):
        with tempfile.TemporaryDirectory(dir=os.environ.get('TMPDIR')) as td:
            d=Path(td);src=d/'test.s';obj=d/'test.o'
            src.write_text('.set noreorder\n.section .text.func_80100100,"ax"\n.globl func_80100100\n.type func_80100100,@function\nfunc_80100100:\n lui $2,%hi(D_80100000+0x12348000)\n addiu $2,$2,%lo(D_80100000+0x12348000)\n lui $3,%hi(D_80100004)\n addiu $3,$3,%lo(D_80100004)\n.size func_80100100,.-func_80100100\n')
            subprocess.run(['mipsel-linux-gnu-as','-EL','-march=r3000','-o',obj,src],check=True,capture_output=True)
            import aspsx_diff as A
            parsed=A.read_elf(obj.read_bytes())
            # Feed the actual ELF through both sides to inspect the production
            # placed adapter without needing an ASPSX installation in this fixture.
            with patch.object(A, 'read_lnk', return_value=parsed):
                _,ma,_=P.placed_views(TOOLS.parent,obj.read_bytes(),b'fixture')
            keys=[k for _,rt,k in ma.tokens('func_80100100') if rt]
            self.assertIn(('sym','D_80100000',0x12348000),keys)
            vals={'D_80100000':0x80008000,'D_80100004':0x80008000}
            words,masked=A.resolve_tokens(ma,'func_80100100',0x80010000,vals.get,0x80080994)
            self.assertEqual(masked,[])
            self.assertEqual(words[0]&0xffff,((0x80008000+0x12348000+0x8000)>>16)&0xffff)
            self.assertEqual(words[1]&0xffff,(0x80008000+0x12348000)&0xffff)
            script=d/'test.ld';elf=d/'test.elf';binary=d/'test.bin'
            script.write_text('D_80100000 = 0x80008000; D_80100004 = 0x80008000; SECTIONS { .text 0x80010000 : { *(.text.func_80100100) } /DISCARD/ : { *(*) } }')
            subprocess.run(['mipsel-linux-gnu-ld','-EL','-T',script,'-o',elf,obj],check=True,capture_output=True)
            subprocess.run(['mipsel-linux-gnu-objcopy','-O','binary',elf,binary],check=True,capture_output=True)
            self.assertEqual(binary.read_bytes(),struct.pack('<4I',*words))


if __name__ == '__main__':
    unittest.main()
