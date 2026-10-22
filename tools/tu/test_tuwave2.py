"""Regression tests for whole-module absorption, table admission and destinations."""
import json
import sys
import tempfile
import unittest
from pathlib import Path
from unittest.mock import patch

sys.path.insert(0, str(Path(__file__).resolve().parent))
import tu_merge as M
import group_status as S
import subprocess


class AbsorptionTests(unittest.TestCase):
    def fixture(self, root):
        (root/'config/overlays').mkdir(parents=True)
        (root/'src').mkdir()
        (root/'config/names.tsv').write_text('')
        old = dict(key='old', container='town', source='src/old.c', headers=[], review_inputs=[],
                   recipe=dict(cfg='2.7.2-cdk-G0',row_asflags=''),
                   members=[dict(id='town/a',function='a'),dict(id='town/b',function='b')])
        (root/'config/overlays/modules.json').write_text(json.dumps(dict(modules=[old])))
        (root/'src/old.c').write_text('int a(void) { return 1; }\nint b(void) { return 2; }\n')
        spec=dict(container='town',header='include/new.h',modules=[dict(key='new',source='src/new.c',
                  members=['town/a','town/b'],absorb_modules=['old'])])
        rows={rid:dict(container='town',cfg='2.7.2-cdk-G0',foff=i*4,size=4,func=rid[5:])
              for i,rid in enumerate(['town/a','town/b'])}
        return old,spec,rows

    def test_explicit_complete_cohort_and_allocations(self):
        with tempfile.TemporaryDirectory() as td:
            root=Path(td);old,spec,rows=self.fixture(root)
            self.assertEqual(M.absorption_plan(root,spec),{'old':old})
            spec['modules'][0]['members']=['town/a']
            with self.assertRaisesRegex(M.Refused,'complete module'):M.absorption_plan(root,spec)
            spec['modules'][0]['members']=['town/a','town/b']
            spec['modules'][0]['absorb_modules']=[]
            with self.assertRaisesRegex(M.Refused,'explicit absorb_modules'):M.absorption_plan(root,spec)
            spec['modules'][0]['absorb_modules']=['old']
            old['allocations']=[{}]
            (root/'config/overlays/modules.json').write_text(json.dumps(dict(modules=[old])))
            with self.assertRaisesRegex(M.Refused,'allocated data'):M.absorption_plan(root,spec)

    def test_retired_physical_tu_alias_follows_the_merged_source(self):
        aliases=[dict(old='src/town/modules/old.c',new='src/town/old.c')]
        self.assertEqual(M.rewrite_tu_aliases(aliases,{'src/town/old.c':'src/town/new.c'}),
                         [dict(old='src/town/modules/old.c',new='src/town/new.c')])
        aliases.append(dict(old='src/town/modules/other.c',new='src/town/new.c'))
        with self.assertRaisesRegex(M.Refused,'alias consolidation proof'):
            M.rewrite_tu_aliases(aliases,{'src/town/old.c':'src/town/new.c'})

    def test_physical_graph_uses_its_producer_and_remains_reversible(self):
        from types import SimpleNamespace
        with tempfile.TemporaryDirectory() as td:
            root=Path(td);graph=root/'config/link_graph';graph.mkdir(parents=True)
            (graph/'graph.json').write_text('old graph')
            (graph/'retired.000.jsonl').write_text('old shard')
            work=root/'work';work.mkdir()
            def capture(argv,**kwargs):
                self.assertEqual(argv[-1],'capture')
                target=Path(argv[argv.index('--graph')+1])
                (target/'graph.json').write_text('new graph')
                (target/'tus.000.jsonl').write_text('new shard')
                return SimpleNamespace(returncode=0,stdout='{"tus":1}',stderr='')
            with patch.object(M.subprocess,'run',side_effect=capture):
                result=M.refresh_link_graph(root,work,M.Freezer(root,work/'base'))
            self.assertEqual(result,{'tus':1})
            self.assertFalse((graph/'retired.000.jsonl').exists())
            self.assertEqual((graph/'tus.000.jsonl').read_text(),'new shard')
            M.restore(root,work/'base')
            self.assertEqual((graph/'graph.json').read_text(),'old graph')
            self.assertTrue((graph/'retired.000.jsonl').exists())
            self.assertFalse((graph/'tus.000.jsonl').exists())

    def test_existing_placements_are_not_silently_dropped(self):
        with tempfile.TemporaryDirectory() as td:
            root=Path(td);old,spec,rows=self.fixture(root)
            (root/'config/overlays/module_placements.json').write_text(json.dumps(dict(placements=[dict(module='old')])))
            with self.assertRaisesRegex(M.Refused,'existing placements'):M.absorption_plan(root,spec)

    def test_draft_extracts_all_members_and_proves_old_tu_once(self):
        with tempfile.TemporaryDirectory() as td:
            root=Path(td);old,spec,rows=self.fixture(root);work=root/'draft'
            with patch.object(M,'load_repo',return_value=(rows,{rid:'src/old.c' for rid in rows})), \
                 patch.object(M,'compile_obj',return_value=(root/'unused.o','')):
                members,conflicts,blocking=M.draft(root,spec,work)
            self.assertFalse(blocking)
            text=(work/'tree/src/new.c').read_text()
            self.assertEqual([f[0] for f in M.definitions(text)[0]],['a','b'])
            with patch.object(M,'compile_obj',return_value=(root/'unused.o','')) as cc, \
                 patch.object(M,'text_and_relocs',return_value=(b'12345678',[],{})):
                ok,proof=M.prove(root,work)
            self.assertTrue(ok)
            self.assertEqual(cc.call_count,2)  # complete old TU once + new TU once
            self.assertEqual(proof['new']['proof_units'][0]['members'],['town/a','town/b'])
            self.assertEqual(json.loads((work/'absorption.json').read_text())['modules'],[old])

    def test_absorbed_private_prototypes_are_reconciled(self):
        with tempfile.TemporaryDirectory() as td:
            root=Path(td);old,spec,rows=self.fixture(root)
            (root/'include').mkdir()
            (root/'include/old.h').write_text('#ifndef OLD_H\n#define OLD_H\nint a();\nint b();\n#endif\n')
            old['headers']=['include/old.h']
            (root/'config/overlays/modules.json').write_text(json.dumps(dict(modules=[old])))
            source=root/'src/old.c';source.write_text('#include "old.h"\n'+source.read_text())
            with patch.object(M,'load_repo',return_value=(rows,{rid:'src/old.c' for rid in rows})), \
                 patch.object(M,'compile_obj',return_value=(root/'unused.o','')):
                M.draft(root,spec,root/'draft')
            header=(root/'draft/tree/include/new.h').read_text()
            self.assertNotIn('#include "old.h"',header)
            self.assertIn('int a(void);',header)
            self.assertNotIn('int a();',header)

    def test_rebased_source_contract_exists_in_the_frozen_draft_tree(self):
        with tempfile.TemporaryDirectory() as td:
            root=Path(td);old,spec,rows=self.fixture(root)
            (root/'include').mkdir()
            (root/'src/contract.h').write_text('typedef int Counter;\n')
            (root/'include/old.h').write_text('#ifndef OLD_H\n#define OLD_H\n#include "../src/contract.h"\nint a();\nint b();\n#endif\n')
            old['headers']=['include/old.h'];spec['header']='include/nested/new.h'
            (root/'config/overlays/modules.json').write_text(json.dumps(dict(modules=[old])))
            source=root/'src/old.c';source.write_text('#include "old.h"\n'+source.read_text())
            with patch.object(M,'load_repo',return_value=(rows,{rid:'src/old.c' for rid in rows})), \
                 patch.object(M,'compile_obj',return_value=(root/'unused.o','')):
                M.draft(root,spec,root/'draft')
            header=root/'draft/tree/include/nested/new.h'
            self.assertIn('#include "../../src/contract.h"',header.read_text())
            self.assertEqual((header.parent/'../../src/contract.h').read_text(),'typedef int Counter;\n')
            self.assertEqual((root/'draft/pre/src/contract.h').read_text(),'typedef int Counter;\n')

    def test_unexpected_install_exception_restores_every_write(self):
        with tempfile.TemporaryDirectory() as td:
            root=Path(td);(root/'old').write_text('before')
            def fail(*args):
                fr=M.Freezer(root,root/'base');fr.write('old','after');fr.write('new','new')
                raise RuntimeError('injected graph failure')
            with patch.object(M,'_install',side_effect=fail):
                with self.assertRaises(RuntimeError):M.install(root,root/'work',root/'base')
            self.assertEqual((root/'old').read_text(),'before')
            self.assertFalse((root/'new').exists())

    def test_switch_admits_only_one_exact_evidenced_owner(self):
        with tempfile.TemporaryDirectory() as td:
            root=Path(td);rows={'table':dict(id='table',row_kind='data',data_kind='jump_table',
                ownership_status='evidenced',owner='town/a',foff=0,size=8)}
            members=[dict(id='town/a',module='new',foff=16,size=4)]
            res=dict(switch_tables=[dict(id='town/a',bytes=8)])
            args=(root,root,{},members,'new',res,rows)
            self.assertEqual(M.switch_row(*args)['id'],'table')
            rows['table']['ownership_status']='inferred'
            with self.assertRaisesRegex(M.Refused,'no evidenced registered'):M.switch_row(*args)
            rows['table']['ownership_status']='evidenced';rows['duplicate']=dict(rows['table'],id='duplicate')
            with self.assertRaises(M.Refused):M.switch_row(*args)


class SwitchProofTests(unittest.TestCase):
    def test_switch_padding_requires_a_complete_word_relocation_table(self):
        relocs=[(off,'R_MIPS_32','.text.owner') for off in range(0,20,4)]
        self.assertEqual(M.switch_payload_bytes(b'\0'*24,relocs),20)
        self.assertEqual(M.switch_payload_bytes(b'\0'*23+b'X',relocs),24)
        self.assertEqual(M.switch_payload_bytes(b'\0'*24,relocs[:2]+relocs[3:]),24)
        self.assertEqual(M.switch_payload_bytes(b'\0'*36,relocs),36)
        with tempfile.TemporaryDirectory() as td:
            data=dict(id='table',row_kind='data',data_kind='jump_table',ownership_status='evidenced',owner='town/a',size=20)
            res=dict(switch_tables=[dict(id='town/a',bytes=24,payload_bytes=20,end_padding=4)])
            self.assertEqual(M.switch_row(Path(td),Path(td),{},[],'new',res,{'table':data}),data)

    def test_emitted_allocation_passes_the_production_validator(self):
        import overlay_switch_allocations as X
        source='src/town/merged.c'
        members=[dict(id='town/'+n,function=n,foff=0x200+4*i,size=4,source=source)
                 for i,n in enumerate(['a','b','c'])]
        data=dict(id='town/table',func='D_80000100',foff=0x100,size=8,owner='town/b')
        model=dict(M.switch_allocation(data,members,source,0x80000000),members=[
            dict(m,vma=m['foff']+0x80000000) for m in members],owned_data=[],review_inputs=[source])
        X.validate(model)
        self.assertEqual(model['section_order'],['.text.a','.text.b','.rodata','.text.c'])
        self.assertEqual(model['allocations'][0]['slots'][0]['owner'],'b')
        X.validate_ownership(model,{'town/table':dict(row_kind='data',data_kind='jump_table',
            ownership_status='evidenced',owner='town/b')})

    def test_table_bytes_and_relocations_are_both_required(self):
        for changed_bytes in (False,True):
            with self.subTest(changed_bytes=changed_bytes),tempfile.TemporaryDirectory() as td:
                root=Path(td);work=root/'work';work.mkdir()
                spec=dict(modules=[dict(key='new',source='src/new.c')])
                ms=[dict(id='town/a',module='new',path='src/a.c',cfg='2.7.2-cdk-G0',size=4),
                    dict(id='town/b',module='new',path='src/b.c',cfg='2.7.2-cdk-G0',size=4)]
                (work/'spec.json').write_text(json.dumps(spec));(work/'members.json').write_text(json.dumps(ms))
                def cc(root,source,cfg,tdp,name,**kwargs):return Path(tdp)/(name+'.o'),''
                def text(obj):
                    if obj.stem.endswith('m00'):return b'aaaa',[],{'.rodata':8}
                    if obj.stem.endswith('m01'):return b'bbbb',[],{}
                    return b'aaaabbbb',[],{'.rodata':8}
                def section(obj,name):
                    if obj.stem.endswith('m00'):return b'12345678',[(0,'R_MIPS_32','.text.a')]
                    return (b'87654321' if changed_bytes else b'12345678',
                            [(0,'R_MIPS_32','.text.a' if changed_bytes else '.text.b')])
                with patch.object(M,'compile_obj',side_effect=cc),patch.object(M,'text_and_relocs',side_effect=text), \
                     patch.object(M,'section_data',side_effect=section):
                    ok,res=M.prove(root,work)
                self.assertFalse(ok)
                self.assertTrue(res['new']['text_equal'])
                self.assertTrue(res['new']['merged_other_sections']['rodata_differs'])


class DestinationTests(unittest.TestCase):
    def tables(self):
        images={'town/img':dict(foff=0, vma=0x80000000, size=0x1000)}
        reg={rid:dict(id=rid,container='town',foff=off,size=4)
             for rid,off in [('town/a',0x100),('town/b',0x104)]}
        entries={rid:dict(row=rid,home=rid,image='town/img',foff=r['foff'],vma=r['foff']+0x80000000,size=4)
                 for rid,r in reg.items()}
        for home,off in [('town/a',0x200),('town/b',0x204)]:
            rid=home+'_copy';reg[rid]=dict(id=rid,source_row=home,foff=off,size=4)
            entries[rid]=dict(row=rid,home=home,image='town/img',foff=off,vma=off+0x80000000,size=4)
        group=dict(group_id='G1',image='town/img',container='town',member_rows='town/a;town/b',
                   blockers='member_has_in_image_placement_copy')
        return group,images,entries,reg

    def test_no_destinations_requires_accounting_for_registry_copies(self):
        g,images,entries,reg=self.tables()
        fact=S.destination_facts(g,images,{},reg)
        self.assertIn('registry copy lacks link-list entry town/a_copy',fact['missing_facts'])
        del reg['town/a_copy'];del reg['town/b_copy']
        fact=S.destination_facts(g,{}, {},reg,[(0,0x1000,0x80000000,'proven','engine')])
        self.assertFalse(fact['missing_facts'])
        self.assertIn('engine:delta=0x80000000',fact['home_regions'])

    def status(self,g,images,entries,reg):
        with patch.object(S,'copy_homes',return_value={}),patch.object(S.L,'load',return_value=(images,{},entries,{})), \
             patch.object(S,'own_file_rows',return_value=(reg,{})), \
             patch.object(S,'rowbase',return_value=[(0,0x1000,0x80000000,'proven','engine')]):
            return S.status(Path('.'),[g])

    def test_decision75_complete_same_image_cohort_is_admitted(self):
        g,images,entries,reg=self.tables();groups,placements=self.status(g,images,entries,reg)
        self.assertEqual(groups[0]['mergeable_now'],'yes')
        self.assertEqual(placements[0]['state'],'complete')
        del entries['town/b_copy'];groups,placements=self.status(g,images,entries,reg)
        self.assertEqual(groups[0]['mergeable_now'],'no')
        self.assertIn('town/b',placements[0]['detail'])

    def test_duplicate_home_copy_never_overwrites_another_cohort(self):
        g,images,entries,reg=self.tables()
        entries['town/a_again']=dict(entries['town/a_copy'],row='town/a_again',foff=0x300)
        groups,placements=self.status(g,images,entries,reg)
        self.assertEqual(groups[0]['mergeable_now'],'no')
        self.assertEqual([p['state'] for p in placements],['complete','in_image_copy'])
        self.assertIn('town/b',placements[1]['detail'])
        self.assertNotEqual(placements[0]['cohort_foff'],placements[1]['cohort_foff'])


class GraphAttestationTests(unittest.TestCase):
    def test_placement_cell_is_guarded_independently_of_home_cell(self):
        from types import SimpleNamespace
        sys.path.insert(0,str(Path(__file__).resolve().parents[2]))
        from tools.build import mkbuild as B
        import gate.source_layout as SL
        with tempfile.TemporaryDirectory() as td:
            root=Path(td);(root/'src').mkdir();(root/'src/home.c').write_text('int f(void) { return 0; }')
            home='town/home';copy='dungeon/copy'
            rows={home:dict(id=home,cfg='2.7.2-cdk-G0 -O1',path='src/home.c'),
                  copy:dict(id=copy,source_row=home,cfg='2.7.2-cdk-G0',foff=0x200,size=8,row_asflags=None)}
            inputs={k:'fixed' for k in ['ledger/containers.jsonl','ledger/splits/slus.jsonl','ledger/instance_load_regions.jsonl']}
            entry=dict(kind='tu',tu=home,attributes=dict(row=copy,foff=0x200,size=8),
                       recipe_witness=dict(cfg='2.7.2-cdk-G0',row_asflags=None))
            graph=SimpleNamespace(manifest=dict(inputs=inputs),
                tus={home:dict(recipe_witness=dict(cfg='2.7.2-cdk-G0 -O1'))},entries={'placement':entry})
            with patch.object(B,'ROOT',root),patch.object(B,'hash_inputs',return_value=inputs), \
                 patch.object(B,'read',return_value=dict(modules=[])),patch.object(SL,'row_relative',side_effect=lambda row,root:row['path']):
                result=B.attest_graph(graph,rows)
                self.assertEqual(result['placements']['placement']['cfg'],'2.7.2-cdk-G0')
                rows[copy]['cfg']='2.6.3-G0'
                with self.assertRaisesRegex(ValueError,'live registry differs'):B.attest_graph(graph,rows)
                rows[copy]['cfg']='2.7.2-cdk-G0';rows[copy]['row_asflags']='--foreign'
                with self.assertRaisesRegex(ValueError,'assembler flags differ'):B.attest_graph(graph,rows)


class NamingTests(unittest.TestCase):
    def test_load_address_name_map_preserves_both_g00738_sections(self):
        ccproc=Path(__file__).resolve().parents[1]/'build/ccproc.py'
        with tempfile.TemporaryDirectory() as td:
            names=Path(td)/'names.tsv'
            names.write_text('0x8001627C\tfunc_8001627C\tinvoke_state_callback\treviewed\n'
                             '0x800162DC\tfunc_800162DC\tpass_four_byte_request_1\treviewed\n')
            assembly=('.ent invoke_state_callback\ninvoke_state_callback:\n.end invoke_state_callback\n'
                      '.ent pass_four_byte_request_1\npass_four_byte_request_1:\n.end pass_four_byte_request_1\n'
                      '.ascii "invoke_state_callback"\n')
            out=subprocess.check_output([sys.executable,str(ccproc),'--names-tsv',str(names)],input=assembly,text=True)
            self.assertIn('.text.func_8001627C',out)
            self.assertIn('.text.func_800162DC',out)
            self.assertIn('.ascii "invoke_state_callback"',out)
            self.assertNotIn('.ent invoke_state_callback',out)


if __name__=='__main__':unittest.main()
