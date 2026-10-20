"""Expanded image selection, owned definitions and private preparation integrity."""
import json
from pathlib import Path
import shutil
import subprocess
import tempfile
from types import SimpleNamespace
import sys
import unittest
from unittest.mock import patch

from tools.link import combined as C
from tools.link.prepare import compile_cache, linklist_snapshot

ROOT = Path(__file__).resolve().parents[2]


class CombinedTests(unittest.TestCase):
    def setUp(self):
        self.tmp = tempfile.TemporaryDirectory(dir=ROOT/'work', prefix='test-one-link-')
        self.addCleanup(self.tmp.cleanup)
        self.root = Path(self.tmp.name)

    def test_interior_owner_uses_declared_extent_and_excludes_boundaries(self):
        spans = [(0x80090000,0x80090008,'whole'),(0x80090002,0x80090006,'narrow')]
        self.assertEqual(C.containing_owner(0x80090004,spans),(0x80090002,0x80090006,'narrow'))
        self.assertIsNone(C.containing_owner(0x80090000,spans))
        self.assertIsNone(C.containing_owner(0x80090008,spans))
        self.assertIsNone(C.containing_owner(None,spans))

    def test_equal_addresses_do_not_choose_between_distinct_emitting_instances(self):
        first = dict(prefix='first_instance_')
        second = dict(prefix='second_instance_')
        self.assertEqual(C.unique_owner([('readable_name',first),('func_80090000',first)]),('func_80090000',first))
        self.assertIsNone(C.unique_owner([('func_80090000',first),('func_80090000',second)]))
        self.assertIsNone(C.unique_owner([]))

    def test_complete_load_images_exclude_diagnostic_windows(self):
        docs = {'town/image_a': dict(vma='0x80016000'),
                'town/ll34_b_80016000': dict(vma=0x80016000),
                'town/heur_c': dict(vma='0x80017200'),
                'dungeon/bank_c': dict(vma='0x80170800'),
                'dungeon/ll34_d': dict(vma='0x80170800')}
        self.assertEqual(C.selected_images(docs), ['dungeon/bank_c', 'town/image_a', 'town/ll34_b_80016000'])

    def test_gate_scope_is_bounded_and_covers_placement_rows(self):
        (self.root/'ledger').mkdir()
        (self.root/'config/overlays').mkdir(parents=True)
        rows = [dict(id='town/a',gate_config='config/overlays/shared.overlay.yaml'),
                dict(id='town/b',gate_config='config/overlays/other.overlay.yaml')]
        (self.root/'ledger/rows.jsonl').write_text(''.join(json.dumps(r)+'\n' for r in rows))
        for window in ('shared','other'):
            (self.root/f'config/overlays/{window}.overlay.yaml').touch()
        docs = {'town/a': dict(entries=[dict(row='town/a')]),
                'town/b': dict(entries=[dict(row='town/a')]),
                'town/c': dict(entries=[dict(row='town/b')])}
        self.assertEqual(C.select_windows(self.root,docs,list(docs),['baseline'],2), ['baseline','shared'])
        self.assertEqual(len(C.select_windows(self.root,docs,list(docs),['baseline'],60)), 3)
        for limit in (0,61):
            with self.assertRaisesRegex(ValueError,'between 1 and 60'):
                C.select_windows(self.root,docs,list(docs),[],limit)

    def test_prepared_artifact_changes_are_rejected(self):
        work = self.root/'prepared'; work.mkdir()
        (work/'x.o').write_bytes(b'object fixture')
        receipt = self.root/'index.json'
        with patch.object(C,'preparation_digest',return_value='inputs'):
            C.save_prepared(self.root,None,receipt,{'town/a':work},[],{})
            got,holds,stats = C.load_prepared(self.root,None,receipt)
            self.assertEqual(got, {'town/a':work})
            (work/'x.o').write_bytes(b'changed object')
            with self.assertRaisesRegex(ValueError,'objects or their inputs changed'):
                C.load_prepared(self.root,None,receipt)

    def test_compile_reuse_precedes_rebinding_and_keys_evidence_and_flags(self):
        source = self.root/'source.c'; source.write_text('int f(void) { return 1; }')
        evidence = self.root/'evidence.txt'; evidence.write_text('callee_a\n')
        calls = []
        def compiler(argv, **kwargs):
            calls.append(argv)
            Path(argv[2]).write_bytes(b'pristine ET_REL fixture')
        gate = SimpleNamespace(run=compiler)
        original, stats = compile_cache(gate,self.root/'cache')
        first,second = self.root/'a.o',self.root/'b.o'
        argv = ['cc.sh',str(source),str(first),'2.7.2','-G0','']
        gate.run(argv,env={'MASPSX_NORETURN_FILE':str(evidence)})
        first.write_bytes(b'placement-specific rebound fixture')
        argv[2] = str(second)
        gate.run(argv,env={'MASPSX_NORETURN_FILE':str(evidence)})
        self.assertEqual(second.read_bytes(),b'pristine ET_REL fixture')
        self.assertEqual(stats,dict(compiles=1,reused=1))
        evidence.write_text('callee_b\n')
        gate.run(argv,env={'MASPSX_NORETURN_FILE':str(evidence)})
        argv[4] = '-G8'
        gate.run(argv,env={'MASPSX_NORETURN_FILE':str(evidence)})
        self.assertEqual(stats,dict(compiles=3,reused=1))

    def test_input_change_during_frozen_recipe_snapshot_is_rejected(self):
        config = self.root/'lists.json'; config.write_text('original')
        loader = lambda root: ('validated input tables',)
        lists = SimpleNamespace(load=loader,files=lambda root:[config],
                                _stamp=lambda paths:tuple(p.read_bytes() for p in paths))
        modules = SimpleNamespace(ROOT=self.root,load_modules=lambda root:[],rows=lambda root:{})
        placements = SimpleNamespace(load=lambda root,modules=None:[])
        with patch.dict(sys.modules,dict(linklist=lists,overlay_module_gate=modules,overlay_module_placements=placements)):
            with self.assertRaisesRegex(ValueError,'link lists changed'):
                with linklist_snapshot(SimpleNamespace(ROOT=self.root)):
                    self.assertEqual(lists.load(self.root),('validated input tables',))
                    config.write_text('changed input')
            self.assertIs(lists.load,loader)

    @unittest.skipUnless(shutil.which('mipsel-linux-gnu-as'), 'MIPS binutils unavailable')
    def test_loader_bound_invariant_placement_rejects_self_address_and_missing_evidence(self):
        from tools.link.placement import prove_invariant_placement
        import hashlib
        record = dict(schema='azure-clean.instance-load-region.v1',container='town',foff=0,size=4096,
                      base=0x80016000,delta=0x80016000,method='validated fixture load',evidence='fixture loader tuple')
        ledger = self.root/'load.jsonl'; ledger.write_text(json.dumps(record)+'\n')
        sha = hashlib.sha256(json.dumps(record,sort_keys=True,separators=(',',':')).encode()).hexdigest()
        doc = dict(container='town',foff=0,size=4096,vma=0x80016000,
                   load_evidence=dict(path='load.jsonl',record_sha256=sha))
        source,obj = self.root/'placement.s',self.root/'placement.o'
        rules = 'external = 0x80090000;\nSECTIONS {\n .out_0000 0x80018104 : { KEEP("'+str(obj)+'"(.text.*)) }\n /DISCARD/ : { *(*) }\n}\n'
        def build(target):
            source.write_text('.section .text.f,"ax"\n.globl f\nf:\n.word '+target+'\n')
            subprocess.run(['mipsel-linux-gnu-as','-no-pad-sections','-o',str(obj),str(source)],check=True)
        build('external')
        result = prove_invariant_placement(self.root,doc,obj,rules,0x80018104,0x800160c0,
                    (0x80090000).to_bytes(4,'little'),self.root/'independent')
        self.assertIsNotNone(result)
        self.assertEqual(result['recipe_bytes_sha256'],result['selected_bytes_sha256'])
        self.assertIsNone(prove_invariant_placement(self.root,dict(doc,load_evidence=None),obj,rules,
                    0x80018104,0x800160c0,(0x80090000).to_bytes(4,'little'),self.root/'missing'))
        build('f')
        self.assertIsNone(prove_invariant_placement(self.root,doc,obj,rules,0x80018104,0x800160c0,
                    (0x80018104).to_bytes(4,'little'),self.root/'self_address'))

    @unittest.skipUnless(shutil.which('mipsel-linux-gnu-as'), 'MIPS binutils unavailable')
    def test_convergent_owner_aliases_link_and_retain_nocrossrefs(self):
        from tools.link.graph import emit_global
        for name, body in [('a','.globl caller\ncaller:\n.word one\n.word two\n'),
                           ('b','.globl owner\nowner:\n.word 0\n.word 0\n')]:
            source = self.root/(name+'.s'); source.write_text('.text\n'+body)
            subprocess.run(['mipsel-linux-gnu-as','-no-pad-sections','-o',str(self.root/(name+'.o')),str(source)],check=True)
        symbols = []
        renames = C.qualified_redefinitions('qualified_', [('caller','T','caller'),('one','U','owner'),('two','U','owner')],symbols)
        symbols = [line.replace('qualified_two = owner;', 'qualified_two = owner + 0x4;') for line in symbols]
        names = self.root/'renames.txt'; names.write_text(renames)
        subprocess.run(['mipsel-linux-gnu-objcopy','--redefine-syms='+str(names),str(self.root/'a.o'),str(self.root/'placed.o')],check=True)
        bank = ('town/a',0x80016000,8,['KEEP(placed.o(.text))'])
        script = emit_global('SECTIONS { .resident 0x80090000 : { KEEP(b.o(.text)) } }',[],[bank],symbols)
        (self.root/'all.ld').write_text(script)
        argv = ['mipsel-linux-gnu-ld','-EL','-T','all.ld','-o','all.elf','placed.o','b.o']
        subprocess.run(argv,cwd=self.root,check=True)
        with patch.object(C,'ROOT',self.root):
            linked = {n:(k,v) for n,k,v in C.nm(self.root/'all.elf')}
        self.assertEqual(linked['qualified_one'],('T',0x80090000))
        self.assertEqual(linked['qualified_two'],('T',0x80090004))
        script = emit_global('',[],[bank,('town/b',0x80016000,8,['KEEP(b.o(.text))'])],symbols)
        (self.root/'all.ld').write_text(script)
        result = subprocess.run(argv,cwd=self.root,capture_output=True,text=True)
        self.assertNotEqual(result.returncode,0)
        self.assertIn('prohibited cross reference',result.stderr)

    @unittest.skipUnless(shutil.which('mipsel-linux-gnu-as'), 'MIPS binutils unavailable')
    def test_fast_object_metadata_agrees_with_binutils_and_rejects_complex_bindings(self):
        source = self.root/'metadata.s'; obj = self.root/'metadata.o'
        source.write_text('.section .text.first,"ax"\n.globl first\nfirst:\n.word external\n'
                          '.local local_label\nlocal_label:\n.word 0\n'
                          '.data\n.globl data_owner\ndata_owner:\n.word first\n'
                          '.section .rodata\n.local literal\nliteral:\n.word 7\n'
                          '.bss\n.globl storage\nstorage:\n.space 8\n'
                          '.globl absolute\n.set absolute,0x80090000\n')
        subprocess.run(['mipsel-linux-gnu-as','-o',str(obj),str(source)],check=True)
        metadata = C.object_metadata(obj)
        with patch.object(C,'ROOT',self.root):
            self.assertEqual(metadata['values'],sorted(C.nm(obj)))
        self.assertIn(('.text.first',8),metadata['sections'])
        self.assertIn(('data_owner','.data',0),metadata['symbols'])
        self.assertIn(('external','U',0),metadata['values'])
        source.write_text('.text\n.weak weak_definition\nweak_definition:\n.word 0\n')
        subprocess.run(['mipsel-linux-gnu-as','-o',str(obj),str(source)],check=True)
        self.assertIsNone(C.object_metadata(obj))
        obj.write_bytes(b'truncated ELF fixture')
        self.assertIsNone(C.object_metadata(obj))

    @unittest.skipUnless(shutil.which('mipsel-linux-gnu-as'), 'MIPS binutils unavailable')
    def test_resident_owner_requires_a_defining_input_even_above_old_cutoff(self):
        build = self.root/'build_slus'; build.mkdir()
        (build/'owner.s').write_text('.data\n.globl real_owner\n.type real_owner,@object\nreal_owner:\n.word 0\n.size real_owner,4\n'
                                   '.local local_only\nlocal_only:\n.word 0\n.globl _binary_fixture_start\n_binary_fixture_start:\n.word 0\n')
        subprocess.run(['mipsel-linux-gnu-as','-o','owner.o','owner.s'],cwd=build,check=True)
        (build/'owner.ld').write_text('catalogue_alias = 0x80090000; SECTIONS { .data 0x80090000 : { *(.data) } /DISCARD/ : { *(*) } }')
        subprocess.run(['mipsel-linux-gnu-ld','-EL','-T','owner.ld','-o','owner.elf','owner.o'],cwd=build,check=True)
        (build/'build.ninja').write_text('build owner.elf: link owner.o\n')
        with patch.object(C,'ROOT',self.root):
            resident,owners = C.owned_resident(build/'owner.elf',dict(ninja='build_slus/build.ninja'))
            spans = C.resident_spans(build/'owner.elf',resident,owners)
            self.assertEqual(C.containing_owner(0x80090001,spans),(0x80090000,0x80090004,'real_owner'))
            self.assertIsNone(C.containing_owner(0x80090004,spans))
            source = build/'owner.s'
            source.write_text(source.read_text().replace('.size real_owner,4','.size real_owner,64'))
            subprocess.run(['mipsel-linux-gnu-as','-o','owner.o','owner.s'],cwd=build,check=True)
            subprocess.run(['mipsel-linux-gnu-ld','-EL','-T','owner.ld','-o','owner.elf','owner.o'],cwd=build,check=True)
            self.assertIsNone(C.containing_owner(0x80090001,C.resident_spans(build/'owner.elf',resident,owners)))
        self.assertEqual(resident['real_owner'],0x80090000)
        self.assertEqual(owners['real_owner'],'build_slus/owner.o')
        self.assertNotIn('catalogue_alias',resident)
        self.assertNotIn('local_only',resident)
        self.assertNotIn('_binary_fixture_start',resident)


if __name__ == '__main__':
    unittest.main()
