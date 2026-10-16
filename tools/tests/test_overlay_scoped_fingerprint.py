"""Dependency-class mutation matrix, using real CDK preprocessing.

Run with repository toolchain installed. Each mutation is restored; fixture
reviews remain pending. These are dependency tests, not byte-proof receipts.
"""
import contextlib, copy, hashlib, json, os, shutil, sys, tempfile, unittest
from pathlib import Path
ROOT=Path(__file__).resolve().parents[2]
sys.path[:0]=[str(ROOT/'tools'),str(ROOT/'tools/gate')]
import overlay_module_gate as G
import overlay_scoped_fingerprint as F

class ScopedFingerprint(unittest.TestCase):
 @classmethod
 def setUpClass(cls):
  cls.tmp=tempfile.TemporaryDirectory(prefix='certfp-');cls.r=Path(cls.tmp.name)
  r=cls.r
  for n in ['tools/gate','tools/fidelity','tools/build','include','src/dungeon','raw/dungeon','config/overlays','ledger/splits','work/disc/containers','overlays/dungeon']:(r/n).mkdir(parents=True,exist_ok=True)
  gd=ROOT/'tools/gate' if (ROOT/'tools/gate').exists() else ROOT/'tools'
  for p in gd.iterdir():
   if p.is_file() and p.suffix in ('.py','.sh') and p.name!='overlay_module_evidence.py':shutil.copy2(p,r/'tools/gate'/p.name)
  for n in ['tools/fidelity/aspsx_diff.py','tools/fidelity/objread.py','tools/fidelity/certify_overlay_module.py','tools/build/slus_rodata_trim.py','tools/overlay_module_evidence.py']:shutil.copy2(ROOT/n,r/n)
  # Mutable executable copies: mutations never write through toolchain links.
  shutil.copytree(ROOT/'toolchain/compilers/gcc-2.7.2-cdk',r/'toolchain/compilers/gcc-2.7.2-cdk',symlinks=False)
  shutil.copytree(ROOT/'toolchain/maspsx',r/'toolchain/maspsx',symlinks=False,ignore=shutil.ignore_patterns('__pycache__'))
  for n in ['toolchain/genuine/bin/wibo','toolchain/genuine/psyq/psyq4.4/ASPSX.EXE','.venv/bin/python']:
   (r/n).parent.mkdir(parents=True,exist_ok=True);shutil.copy2(ROOT/n,r/n)
  (r/'overlays/dungeon/first_pass_matched').symlink_to(r/'src/dungeon',target_is_directory=True)
  for n in ['names.tsv','slus_006.14.symbols.txt','sibcall_syms.dungeon.txt']:(r/'config'/n).write_text('')
  (r/'config/noreturn_false_members.jsonl').write_text('')
  (r/'ledger/splits/dungeon_engine.jsonl').write_text('')
  (r/'config/overlays/abs_syms.txt').write_text('')
  (r/'config/overlays/dungeon.as_flags.jsonl').write_text('')
  (r/'include/labels.inc').write_text('');(r/'include/shared.h').write_text('typedef int value;\n')
  (r/'include/dep.h').write_text('/* indirect */\n')
  (r/'include/local.h').write_text('#include "shared.h"\n#define NEXT "dep.h"\n#include NEXT\n')
  rows=[];splits=[];mods=[];assign=[];levels=[];regions=[]
  for i,(off,size) in enumerate([(0,32),(32,32),(128,32),(64,32)]):
   name='func_%08X'%(0x80024000+off);rid='dungeon/'+name;source='src/dungeon/'+name+'.c'
   (r/source).write_text('#include "local.h"\nint '+name+'(void){return 1;}\n')
   (r/'raw/dungeon'/Path(source).name).write_text('/* frozen */\n')
   row={'id':rid,'kind':'overlay','container':'dungeon','c_path':source,'func':name,'true_name':name,'foff':off,'size':size,'cfg':'2.7.2-cdk-G0','cell':'2.7.2-cdk','gate_config':'config/overlays/dungeon_test.overlay.yaml' if off<96 else 'config/overlays/dungeon_other.overlay.yaml'}
   rows.append(row);splits.append({'foff':off,'size':size,'result':'MATCH','func_vram':name,'c_path':source,'config':'2.7.2-cdk-G0'})
   assign.append({'id':rid,'container':'dungeon','module':'bank'+str(i),'module_index':i,'confidence':'strong'})
   levels.append({'id':rid,'level':3,'pins_left':0,'tail_jumps':0,'l4_residue':['not_in_module']})
  for i,span in enumerate([(0,112),(128,160)]):
   regions.append({'schema':'azure-clean.rowbase.v1','region':'bank'+str(i),'foff_start':hex(span[0]),'foff_end':hex(span[1]),'delta':hex(0x80024000),'base_confidence':'proven','proof':'fixture'})
  for i,rs in enumerate([rows[:2],rows[2:3]]):
   source='src/dungeon/module'+str(i)+'.c';(r/source).write_text('\n'.join('#include "'+Path(x['c_path']).name+'"' for x in rs)+'\n')
   mods.append({'key':'dungeon_test'+str(i),'container':'dungeon','region':'bank'+str(i),'source':source,'headers':['include/local.h'],'review_inputs':['include/shared.h'],'review':{'membership':'pending','types':'pending','ownership':'pending','reviewer':'pending'},'recipe':{'cfg':'2.7.2-cdk-G0','row_asflags':''},'members':[{'id':x['id'],'source':x['c_path'],'function':x['func'],'foff':x['foff'],'vma':x['foff']+0x80024000,'size':x['size']} for x in rs],'owned_data':[],'imports':[]})
  (r/'include/neighbor.h').write_text('/* neighbor only */\n')
  (r/'src/dungeon/func_80024040.c').write_text('#include "neighbor.h"\nint func_80024040(void){return 1;}\n')
  assign[1].update(module='bank0',module_index=0)
  assign[2].update(module='bank1',module_index=1)
  m=mods[0];m['membership_evidence']='membership.json';m['review_inputs'].append('membership.json')
  cls.write('membership.json',{'ledger_group':{'container':'dungeon','module':'bank0','module_index':0},'members':[x['id'] for x in rows[:2]],'confidence':'strong','basis':'fixture','coverage_complete':True},True)
  m['members'][0].update(function='func_80024004',body_offset=4)
  m['owned_data']=[{'kind':'typed_function_pointer','section':'.rodata','foff':0,'vma':0x80024000,'size':4,'target':'func_80024004','symbol':'D_80024000'}]
  m['imports']=[{'symbol':'D_80024050','kind':'data','foff':80,'vma':0x80024050,'view_bytes':4,'owner':'retail_asset:dungeon:bank0'}, {'symbol':'external_function','kind':'function','vma':0x80010000}]
  runtime={'symbol':'runtime_obj','kind':'runtime_data','vma':0x80030000,'view_bytes':4,'owner':'resident_runtime:slus','declaration':'include/storage.h','evidence':'storage.json'}
  m['imports'].append(runtime);m['review_inputs'].append('storage.json')
  (r/'include/storage.h').write_text('extern int runtime_obj;\n')
  cls.write('storage.json',{'runtime_views':{'runtime_obj':runtime}},True)
  asset={'symbol':'asset_obj','kind':'data','foff':80,'vma':0x80024050,'view_bytes':4,'owner':'retail_asset:work/disc/containers/TOWN_TOWN.BIN','asset':'work/disc/containers/TOWN_TOWN.BIN','evidence':'asset.json','map':'fixture'}
  m['imports'].append(asset);m['review_inputs'].append('asset.json')
  (r/'work/disc/containers/TOWN_TOWN.BIN').write_bytes(bytes(112))
  cls.write('config/overlays/town.rowbase.jsonl',[{'schema':'azure-clean.rowbase.v1','region':'external_town','foff_start':'0x0','foff_end':'0x70','delta':'0x80024000','base_confidence':'proven','proof':'fixture'}])
  cls.write('asset.json',{'views':{'asset_obj':asset},'maps':{'fixture':{'asset':'work/disc/containers/TOWN_TOWN.BIN','container':'town','delta':0x80024000,'file_start':0,'file_end':112,'basis':'fixture','kind':'rowbase','region':'external_town'}}},True)
  cls.write('ledger/rows.jsonl',rows);cls.write('ledger/modules.jsonl',assign);cls.write('ledger/levels.jsonl',levels);cls.write('ledger/splits/dungeon.jsonl',splits);cls.write('config/overlays/dungeon.rowbase.jsonl',regions);cls.write('config/overlays/dungeon.rodata_owners.jsonl',[])
  cls.write('config/overlays/modules.json',{'schema':G.SCHEMA,'modules':mods},True)
  import yaml
  for name,start,end in [('test',0,112),('other',128,160)]:
   cfg={'name':'dungeon_'+name,'options':{'symbol_addrs_path':'config/overlays/abs_syms.txt'},'standalone_build':{'window':{'file_start':start,'file_end':end,'vram_start':0x80024000+start},'split_results':'overlays/dungeon/overlay_first_pass_results.json','matched_sources':[{'results':'overlays/dungeon/overlay_first_pass_results.json','source_dir':'overlays/dungeon/first_pass_matched'}]}}
   (r/'config/overlays'/('dungeon_'+name+'.overlay.yaml')).write_text(yaml.safe_dump(cfg))
  (r/'work/disc/containers/DUNGEON_DUNGEON.BIN').write_bytes(bytes(256))
  cfgfile=r/'config/overlays/dungeon_test.overlay.yaml'
  cfg=yaml.safe_load(cfgfile.read_text());cfg['standalone_build']['matched_sources'].append({'results':'overlays/dungeon_engine/overlay_first_pass_results.json','source_dir':'overlays/dungeon_engine/first_pass_matched','skip_rerun':True,'only_if_missing':True})
  cfgfile.write_text(yaml.safe_dump(cfg))
  cls.refresh();cls.m=G.load_modules(r)[0]
  (r/F.SWITCH).write_text(F.SCHEMA+'\n')
  cls.baseline=G.fingerprint(cls.m,r)
 @classmethod
 def tearDownClass(cls):
  # rmtree uses fd-relative opens for the real compiler's bin directory.
  # Anchor relative audit-hook paths inside the private temp tree, rather
  # than an unrelated canonical bin facade at the test runner's cwd.
  with contextlib.chdir(cls.r.parent):cls.tmp.cleanup()
 @classmethod
 def write(cls,name,v,obj=False):
  (cls.r/name).write_text((json.dumps(v)+'\n') if obj else ''.join(json.dumps(x)+'\n' for x in v))
 @classmethod
 def refresh(cls):
  cls.write('ledger/splits/overlay_modules.build.json',G.graph(cls.r),True)
  for p in (cls.r/'ledger/splits').glob('*.jsonl'):
   (cls.r/'overlays'/p.stem).mkdir(exist_ok=True)
   cls.write('overlays/'+p.stem+'/overlay_first_pass_results.json',F.records(p),True)
 @contextlib.contextmanager
 def mutate(self,name,change,refresh=False):
  paths=[self.r/name,self.r/'ledger/splits/overlay_modules.build.json',*self.r.glob('overlays/*/overlay_first_pass_results.json')];backup={p:p.read_bytes() if p.exists() else None for p in paths}
  try:
   paths[0].parent.mkdir(parents=True,exist_ok=True)
   change(paths[0])
   if refresh:self.refresh()
   yield
  finally:
   for p,b in backup.items():
    if b is None:p.unlink(missing_ok=True)
    else:p.write_bytes(b)
 def fp(self):
  current=json.loads((self.r/'config/overlays/modules.json').read_text())['modules'][0]
  return G.fingerprint(current,self.r)
 def changed(self):
  self.assertNotEqual(self.fp()['sha256'],self.baseline['sha256'])
 def edit(self,name,fn,obj=False,refresh=False):
  def change(p):
   v=json.loads(p.read_text()) if obj else F.records(p);fn(v);self.write(name,v,obj)
  return self.mutate(name,change,refresh)
 def test_default_off_and_bad_flag(self):
  with self.mutate(F.SWITCH,lambda p:p.write_text('legacy\n')):self.assertFalse(F.enabled(self.r))
  with self.mutate(F.SWITCH,lambda p:p.write_text('bad\n')):
   with self.assertRaisesRegex(ValueError,'unsupported tracked fingerprint schema'):F.enabled(self.r)
  with mock.patch.dict(os.environ,{F.FLAG:'1'}):
   with self.assertRaisesRegex(ValueError,'environment schema flag retired'):F.enabled(self.r)
 def test_manifest_review(self):
  with self.edit('config/overlays/modules.json',lambda v:v['modules'][0]['review'].update(types='pending-change'),True):self.changed()
 def test_own_registry(self):
  with self.edit('ledger/rows.jsonl',lambda v:v[0].update(note='mutation'),refresh=True):self.changed()
 def test_own_assignment(self):
  with self.edit('ledger/modules.jsonl',lambda v:v[0].update(note='own assignment note')):self.changed()
 def test_own_split(self):
  with self.edit('ledger/splits/dungeon.jsonl',lambda v:v[0].update(note='mutation'),refresh=True):self.changed()
 def test_source(self):
  with self.mutate(self.m['members'][0]['source'],lambda p:p.write_text(p.read_text()+'/* mutation */\n')):self.changed()
 def test_indirect_macro_include(self):
  with self.mutate('include/dep.h',lambda p:p.write_text('/* changed indirect */\n')):self.changed()
 def test_header(self):
  with self.mutate('include/local.h',lambda p:p.write_text(p.read_text()+'/* change */\n')):self.changed()
 def test_review_evidence(self):
  with self.mutate('include/shared.h',lambda p:p.write_text(p.read_text()+'/* evidence */\n')):self.changed()
 def test_retail(self):
  with self.mutate('work/disc/containers/DUNGEON_DUNGEON.BIN',lambda p:p.write_bytes(b'1'+p.read_bytes()[1:])):self.changed()
 def test_window_retail_neighbor(self):
  with self.mutate('work/disc/containers/DUNGEON_DUNGEON.BIN',lambda p:p.write_bytes(p.read_bytes()[:63]+b'1'+p.read_bytes()[64:])):self.changed()
 def test_region(self):
  with self.edit('config/overlays/dungeon.rowbase.jsonl',lambda v:v[0].update(proof='different evidence')):self.changed()
 def test_noreturn_bytes(self):
  with self.mutate('raw/dungeon/'+Path(self.m['members'][0]['source']).name,lambda p:p.write_text('/* frozen edit with unchanged names */\n')):self.changed()
 def test_noreturn_missing_presence(self):
  p=self.r/'raw/dungeon'/Path(self.m['members'][0]['source']).name
  with self.mutate(str(p.relative_to(self.r)),lambda p:p.unlink()):self.changed()
 def test_false_members(self):
  with self.edit('config/noreturn_false_members.jsonl',lambda v:v.append({'schema':'azure-clean.noreturn-false-member.v1','family':'dungeon','func':'func_80024000','proof':'fixture'})):self.changed()
 def test_symbol_table(self):
  with self.mutate('config/overlays/abs_syms.txt',lambda p:p.write_text('D_80024000 = 0x80024000;\n')):self.changed()
 def test_flags_table(self):
  with self.edit('config/overlays/dungeon.as_flags.jsonl',lambda v:v.append({'func':'func_80024000','as_flags':'--expand-div','proof':'fixture'})):self.changed()
 def test_tool(self):
  with self.mutate('tools/gate/ccproc.py',lambda p:p.write_text(p.read_text()+'\n# mutation\n')):self.changed()
 def test_new_tool(self):
  with self.mutate('tools/gate/new_dependency.py',lambda p:p.write_text('# new\n')):self.changed()
 def test_duplicate_registry(self):
  with self.edit('ledger/rows.jsonl',lambda v:v.append(copy.deepcopy(v[2]))):
   with self.assertRaisesRegex(ValueError,'duplicate registry'):self.fp()
 def test_duplicate_assignment(self):
  with self.edit('ledger/modules.jsonl',lambda v:v.append(copy.deepcopy(v[2]))):
   with self.assertRaisesRegex(ValueError,'duplicate assignment'):self.fp()
 def test_overlapping_split_outside_scope(self):
  with self.edit('ledger/splits/dungeon.jsonl',lambda v:v.append(dict(v[2],foff=132)),refresh=False):
   with self.assertRaisesRegex(ValueError,'overlapping split'):self.fp()
 def test_competing_owner(self):
  with self.edit('config/overlays/dungeon.rodata_owners.jsonl',lambda v:v.append({'schema':'azure-clean.rodata_owner.v1','foff':'0x84','rodata_size':4,'id':'dungeon/wrong'})):
   with self.assertRaisesRegex(ValueError,'competing'):self.fp()
 def test_duplicate_member(self):
  with self.edit('config/overlays/modules.json',lambda v:v['modules'].append(dict(copy.deepcopy(v['modules'][0]),key='dungeon_duplicate')),True):
   with self.assertRaisesRegex(ValueError,'duplicate member'):self.fp()
 def test_stale_graph(self):
  with self.edit('ledger/splits/overlay_modules.build.json',lambda v:v['edges'].pop(),True):
   with self.assertRaisesRegex(ValueError,'graph stale'):self.fp()
 def test_missing_window(self):
  with self.mutate('config/overlays/dungeon_other.overlay.yaml',lambda p:p.unlink()):
   with self.assertRaisesRegex(ValueError,'missing production'):self.fp()
 def test_new_window(self):
  with self.mutate('config/overlays/dungeon_extra.overlay.yaml',lambda p:p.write_text((self.r/'config/overlays/dungeon_test.overlay.yaml').read_text().replace('name: dungeon_test','name: dungeon_extra'))):self.changed()
 def test_region_bounds(self):
  with self.edit('config/overlays/dungeon.rowbase.jsonl',lambda v:v[0].update(foff_end='0x3C')):
   with self.assertRaisesRegex(ValueError,'module outside proven load map'):self.fp()
 def test_unrelated_bank_registry_retained(self):
  with self.edit('ledger/rows.jsonl',lambda v:v[2].update(note='unrelated edit'),refresh=True):self.assertEqual(self.fp(),self.baseline)
 def test_unrelated_bank_source_retained(self):
  with self.mutate('src/dungeon/func_80024080.c',lambda p:p.write_text(p.read_text()+'/* unrelated */\n')):self.assertEqual(self.fp(),self.baseline)
 def test_unrelated_bank_split_retained(self):
  with self.edit('ledger/splits/dungeon.jsonl',lambda v:v[2].update(note='unrelated split'),refresh=True):self.assertEqual(self.fp(),self.baseline)
 def test_unrelated_manifest_review_retained(self):
  with self.edit('config/overlays/modules.json',lambda v:v['modules'][1]['review'].update(types='other pending'),True):self.assertEqual(self.fp(),self.baseline)
 def test_unrelated_assignment_retained(self):
  with self.edit('ledger/modules.jsonl',lambda v:v[2].update(confidence='weak')):self.assertEqual(self.fp(),self.baseline)
 def test_unrelated_raw_retained(self):
  with self.mutate('raw/dungeon/func_80024080.c',lambda p:p.write_text('/* unrelated raw */\n')):self.assertEqual(self.fp(),self.baseline)
 def test_unrelated_row_still_validated(self):
  with self.edit('ledger/rows.jsonl',lambda v:v[2].update(gate_config='missing'),refresh=True):
   with self.assertRaisesRegex(ValueError,'missing production'):self.fp()
 def test_import_map(self):
  with self.edit('config/overlays/modules.json',lambda v:v['modules'][0]['imports'][1].update(vma=0x80010004),True):self.changed()
 def test_import_storage_bytes(self):
  with self.mutate('work/disc/containers/DUNGEON_DUNGEON.BIN',lambda p:p.write_bytes(p.read_bytes()[:80]+b'1'+p.read_bytes()[81:])):self.changed()
 def test_external_asset_bytes(self):
  with self.mutate('work/disc/containers/TOWN_TOWN.BIN',lambda p:p.write_bytes(p.read_bytes()[:80]+b'1'+p.read_bytes()[81:])):self.changed()
 def test_runtime_declaration(self):
  with self.mutate('include/storage.h',lambda p:p.write_text(p.read_text()+'/* storage */\n')):self.changed()
 def test_runtime_evidence(self):
  with self.edit('storage.json',lambda v:v.update(note='mutation'),True):self.changed()
 def test_asset_map_evidence(self):
  with self.edit('asset.json',lambda v:v['maps']['fixture'].update(basis='other'),True):self.changed()
 def test_owned_data(self):
  with self.edit('config/overlays/modules.json',lambda v:v['modules'][0]['owned_data'][0].update(target='func_80024020'),True):self.changed()
 def test_owned_data_owner_record(self):
  with self.edit('config/overlays/dungeon.rodata_owners.jsonl',lambda v:v.append({'schema':'azure-clean.rodata_owner.v1','foff':'0x0','rodata_size':4,'id':self.m['members'][0]['id'],'proof':'fixture'})):self.changed()
 def test_complete_cohort_competitor(self):
  with self.edit('ledger/modules.jsonl',lambda v:v[2].update(module='bank0',module_index=0)):
   with self.assertRaisesRegex(ValueError,'cohort'):self.fp()
 def test_eligibility(self):
  with self.edit('ledger/levels.jsonl',lambda v:v[0].update(pins_left=1)):
   with self.assertRaisesRegex(ValueError,'placement screen'):self.fp()
 def test_placement_level_cycle_retained(self):
  with self.edit('ledger/levels.jsonl',lambda v:v[0].update(level=4,l4_residue=[])):self.assertEqual(self.fp(),self.baseline)
 def test_compiler_identity(self):
  with self.mutate('toolchain/compilers/gcc-2.7.2-cdk/cc1',lambda p:p.write_bytes(p.read_bytes()+b'\0')):self.changed()
 def test_assembler_identity(self):
  # Host tool selected by PATH: copy and mutate a lane-local executable.
  with tempfile.TemporaryDirectory(dir=self.r) as td:
   p=Path(td)/'mipsel-linux-gnu-as';shutil.copy2(shutil.which('mipsel-linux-gnu-as'),p)
   with mock.patch.dict(os.environ,{'PATH':td+os.pathsep+os.environ['PATH']}):
    self.assertEqual(self.fp(),self.baseline)
    p.write_bytes(p.read_bytes()+b'\0');self.changed()
 def test_genuine_identity(self):
  with self.mutate('toolchain/genuine/psyq/psyq4.4/ASPSX.EXE',lambda p:p.write_bytes(p.read_bytes()+b'\0')):self.changed()
 def test_interpreter_identity(self):
  with self.mutate('.venv/bin/python',lambda p:p.write_bytes(p.read_bytes()+b'\0')):self.changed()
 def test_maspsx_identity(self):
  with self.mutate('toolchain/maspsx/maspsx.py',lambda p:p.write_text(p.read_text()+'\n# mutation\n')):self.changed()
 def test_stale_caller_manifest(self):
  with self.edit('config/overlays/modules.json',lambda v:v['modules'][0]['review'].update(types='other pending'),True):
   with self.assertRaisesRegex(ValueError,'stale supplied'):G.fingerprint(self.m,self.r)
 def test_header_shadow_addition(self):
  with self.mutate('src/dungeon/local.h',lambda p:p.write_text('/* shadow */\n')):self.changed()
 def test_reject_unmodelled_environment(self):
  with mock.patch.dict(os.environ,{'CPATH':'extra'}):
   with self.assertRaisesRegex(ValueError,'unmodelled'):F.reject_environment()
   F._M_CACHE.clear()
   with mock.patch.object(F.subprocess,'run',wraps=F.subprocess.run) as commands:
    self.assertEqual(self.fp(),self.baseline)
   preprocessing=[c for c in commands.call_args_list if '-M' in c.args[0]]
   self.assertTrue(preprocessing)
   self.assertTrue(all('CPATH' not in c.kwargs['env'] for c in preprocessing))
 def test_canonical_evidence_import_from_flat_view_context(self):
  with mock.patch.object(sys,'path',[str(ROOT/'tools/gate'),*[p for p in sys.path if p!=str(self.r/'tools')]]):
   self.assertTrue(F.noreturn(self.r,'dungeon',[0],{}, {},G)['frozen_sources'])
 def test_comment_jsonl_cache_replacement_and_copy(self):
  from gate_read_cache import read_records
  p=self.r/'cache-records.jsonl'
  p.write_text('# comment\n{"a":1}\n');v=read_records(p);v[0]['a']=5
  self.assertEqual(read_records(p)[0]['a'],1)
  old=p.stat();q=p.with_suffix('.tmp');q.write_text('# comment\n{"a":2}\n');os.utime(q,ns=(old.st_atime_ns,old.st_mtime_ns));q.replace(p)
  self.assertEqual(read_records(p)[0]['a'],2);p.unlink()
 def assert_window_only_change(self):
  changed=self.fp()
  self.assertEqual(changed['module'],self.baseline['module'])
  self.assertNotEqual(changed['windows'],self.baseline['windows'])
 def test_neighbor_source_is_window_dependency(self):
  with self.mutate('src/dungeon/func_80024040.c',lambda p:p.write_text(p.read_text()+'/* neighbor */\n')):self.assert_window_only_change()
 def test_neighbor_include_is_window_dependency(self):
  with self.mutate('include/neighbor.h',lambda p:p.write_text('/* neighbor changed */\n')):self.assert_window_only_change()
 def test_neighbor_registry_is_window_dependency(self):
  with self.edit('ledger/rows.jsonl',lambda v:v[3].update(note='neighbor'),refresh=True):self.assert_window_only_change()
 def test_neighbor_recipe_is_window_dependency(self):
  with self.edit('ledger/splits/dungeon.jsonl',lambda v:v[3].update(config='2.7.2-cdk-G0 -fno-schedule-insns'),refresh=True):self.assert_window_only_change()
 def test_missing_neighbor_roster_is_window_dependency(self):
  with self.edit('ledger/splits/dungeon.jsonl',lambda v:v.pop(3),refresh=True):self.changed()
 def test_shared_header_invalidates_module_and_window(self):
  with self.mutate('include/shared.h',lambda p:p.write_text(p.read_text()+'/* shared ABI */\n')):
   changed=self.fp();self.assertNotEqual(changed['module'],self.baseline['module']);self.assertNotEqual(changed['windows'],self.baseline['windows'])
 def test_validation_input_reuse_refreshes_same_call(self):
  p=self.r/'validation-read.json';p.write_text('{"v":1}')
  token=G._LOAD_READS.set({})
  try:
   self.assertEqual(G.read_json(p)['v'],1)
   p.write_text('{"v":2}');self.assertEqual(G.read_json(p)['v'],2)
  finally:G._LOAD_READS.reset(token);p.unlink()
 def test_validation_inputs_independent_between_calls(self):
  one=G.ranges(self.r,'dungeon');one[0]['proof']='local mutation'
  self.assertEqual(G.ranges(self.r,'dungeon')[0]['proof'],'fixture')
 def test_storage_checks_run_again(self):
  # Without the per-process memo every fingerprint re-runs every check.
  with mock.patch.dict(os.environ,{'AZ_FP_MEMO':'0'}),mock.patch.object(G,'validate_asset',wraps=G.validate_asset) as validate:
   self.fp();first=validate.call_count;self.fp()
   self.assertGreater(first,0);self.assertEqual(validate.call_count,2*first)
  # With it, an unchanged tree reuses the value and any input edit re-runs every check.
  with mock.patch.object(G,'validate_asset',wraps=G.validate_asset) as validate:
   self.fp();first=validate.call_count;self.fp();self.assertEqual(validate.call_count,first)
   with self.mutate('ledger/levels.jsonl',lambda p:p.write_text(p.read_text()+'\n')):
    self.fp();self.assertGreater(validate.call_count,first)
 def test_canonical_checkout_without_view_facade(self):
  alias=self.r/'overlays/dungeon/first_pass_matched'
  alias.unlink()
  try:self.assertEqual(self.fp(),self.baseline)
  finally:alias.symlink_to(self.r/'src/dungeon',target_is_directory=True)
 def test_engine_facade_without_canonical_alias(self):
  alias=self.r/'overlays/dungeon_engine/first_pass_matched'
  alias.parent.mkdir(exist_ok=True)
  import yaml
  def change(p):
   cfg=yaml.safe_load(p.read_text());cfg['standalone_build']['matched_sources'][0]['source_dir']='overlays/dungeon_engine/first_pass_matched';p.write_text(yaml.safe_dump(cfg))
  with self.mutate('config/overlays/dungeon_test.overlay.yaml',change):
   alias.symlink_to(self.r/'src/dungeon',target_is_directory=True)
   try:with_facade=self.fp()
   finally:alias.unlink()
   self.assertEqual(self.fp(),with_facade)
 def test_nonbanked_families_fail_closed(self):
  for container in ['main','unknown']:
   m=dict(self.m,container=container)
   with self.assertRaisesRegex(ValueError,'does not model this container evidence'):F.fingerprint(m,self.r,G)
 def test_mutation_restoration(self):self.assertEqual(self.fp(),self.baseline)

 def test_sibcall_is_module_and_window_dependency(self):
  with self.mutate('config/sibcall_syms.dungeon.txt',lambda p:p.write_text('func_80024020\n')):
   changed=self.fp();self.assertNotEqual(changed['module'],self.baseline['module']);self.assertNotEqual(changed['windows'],self.baseline['windows'])
 def test_names_table_is_bound(self):
  with self.mutate('config/names.tsv',lambda p:p.write_text('func_80024040\tneighbor_name\n')):self.changed()
 def test_slus_symbols_are_window_dependency(self):
  with self.mutate('config/slus_006.14.symbols.txt',lambda p:p.write_text('D_80000000 = 0x80000000;\n')):self.assert_window_only_change()
 def test_full_environment_refusals(self):
  for key in ['AZURE_MASPSX','AZURE_MASPSX_COMPANION','AZURE_MASPSX_FUTURE','MASPSX_SHAPE_D_MANIFEST','MASPSX_NO_CDK_LO_FOLD','MASPSX_NO_SELFINC_LA_FOLD','MASPSX_NO_FUTURE_FOLD','MASPSX_NORETURN_FILE','MASPSX_SIBCALL_FILE','MASPSX_UNKNOWN','CPLUS_INCLUDE_PATH','OBJC_INCLUDE_PATH']:
   for value in ['unbound', '']:
    with self.subTest(key=key,value=value),mock.patch.dict(os.environ,{key:value}):
     with self.assertRaisesRegex(ValueError,'unmodelled compiler environment: '+key+'$'):F.reject_environment()
     out=self.r/'refused-producer'
     with self.assertRaisesRegex(ValueError,'unmodelled compiler environment: '+key+'$'):G.build(self.m,out,self.r)
     self.assertFalse(out.exists())
     self.assertEqual(self.fp(),self.baseline)
 def test_new_row_in_window_is_bound(self):
  def add(v):
   r=copy.deepcopy(v[3]);r.update(id='dungeon/new_row',foff=96,size=16,func='new_row',true_name='new_row');v.append(r)
  with self.edit('ledger/rows.jsonl',add,refresh=True):self.assert_window_only_change()
 def test_cross_container_competitor_refused(self):
  def add(v):
   r=copy.deepcopy(v[0]);r.update(id='dungeon_engine/competing_row',container='dungeon_engine');v.append(r)
  # Regenerated graph does not make a competing physical owner safe.
  with self.edit('ledger/rows.jsonl',add,refresh=True):
   with self.assertRaisesRegex(ValueError,'overlapping registry spans dungeon:'):self.fp()
 def test_cross_container_new_row_in_window_is_bound(self):
  def add(v):
   r=copy.deepcopy(v[3]);r.update(id='dungeon_engine/new_row',container='dungeon_engine',foff=96,size=16,func='new_row',true_name='new_row');v.append(r)
  with self.edit('ledger/rows.jsonl',add,refresh=True):self.assert_window_only_change()
 def test_misleading_comment_window_is_required(self):
  p='config/overlays/dungeon_comment.overlay.yaml'
  def add(p):p.write_text('# old file_start: 0xFFF; file_end: 0xFFFF\n'+(self.r/'config/overlays/dungeon_test.overlay.yaml').read_text().replace('name: dungeon_test','name: dungeon_comment'))
  with self.mutate(p,add):
   changed=self.fp();self.assertIn(p,changed['required_windows']);self.assertNotEqual(changed['sha256'],self.baseline['sha256'])
 def test_misnamed_window_is_required(self):
  p='config/overlays/neutral.overlay.yaml'
  with self.mutate(p,lambda p:p.write_text((self.r/'config/overlays/dungeon_test.overlay.yaml').read_text().replace('name: dungeon_test','name: dungeon_neutral'))):
   changed=self.fp();self.assertIn(p,changed['required_windows']);self.assertEqual(changed['required_windows'],G.affected_windows(self.m,self.r));self.assertNotEqual(changed['sha256'],self.baseline['sha256'])
 def test_required_window_disagreement_refused(self):
  parsed=F.windows(self.r)
  with mock.patch.object(F,'required_windows',side_effect=AssertionError('dependent derivation')):
   self.assertEqual(G.affected_windows(self.m,self.r,parsed_windows=parsed),self.baseline['required_windows'])
  # If the aggregate-TU selection regresses, the per-member selection must
  # stay unchanged and the fingerprint must refuse the disagreement.
  with mock.patch.object(F,'required_windows',return_value=[]),mock.patch.dict(os.environ,{'AZ_FP_MEMO':'0'}):
   with self.assertRaisesRegex(ValueError,'parsed required windows differ'):self.fp()
 def test_neighbor_levels_eligibility_is_bound(self):
  with self.edit('ledger/levels.jsonl',lambda v:v[3].update(level=2)):self.assert_window_only_change()
 def test_neighbor_levels_promotion_retained(self):
  with self.edit('ledger/levels.jsonl',lambda v:v[3].update(level=4,l4_residue=[])):self.assertEqual(self.fp(),self.baseline)
 def test_rerun_duplicate_split_is_bound(self):
  with self.edit('ledger/splits/dungeon.jsonl',lambda v:v.append(dict(v[3],rerun=True)),refresh=True):self.assert_window_only_change()
 def test_skip_rerun_false_is_bound(self):
  import yaml
  def change(p):
   cfg=yaml.safe_load(p.read_text());cfg['standalone_build']['matched_sources'][0]['skip_rerun']=False;p.write_text(yaml.safe_dump(cfg))
  with self.edit('ledger/splits/dungeon.jsonl',lambda v:v.append(dict(v[3],rerun=True)),refresh=True),self.mutate('config/overlays/dungeon_test.overlay.yaml',change):self.assert_window_only_change()
 def test_straddling_split_is_bound(self):
  # A raw/unknown fragment can straddle a window boundary. Intersect it,
  # rather than requiring its entire span to be contained by the window.
  with self.edit('ledger/splits/dungeon.jsonl',lambda v:v.append({'foff':96,'size':32,'result':'NO_MATCH','note':'straddles end'}),refresh=True):self.assert_window_only_change()
 def test_exported_roster_mismatch_refused(self):
  with self.edit('overlays/dungeon/overlay_first_pass_results.json',lambda v:v.pop(),True):
   with self.assertRaisesRegex(ValueError,'exported split roster differs:'):self.fp()
 def test_configure_binds_as_flags_only(self):
  # configure.py is the SLUS build graph; the gate reads only its AS_FLAGS literal.
  name='tools/gate/configure.py'
  def sub(old,new):
   def change(p):
    t=p.read_text();self.assertIn(old,t);p.write_text(t.replace(old,new,1))
   return change
  def append(text):return lambda p:p.write_text(p.read_text()+text)
  with self.mutate(name,sub('CC_VER = {','CC_VER = {\n    "src/w_DEADBEEF.c": ("2.7.2-cdk", ""),')):self.assertEqual(self.fp(),self.baseline)
  with self.mutate(name,append('\n# comment / non-AS_FLAGS edit\n')):self.assertEqual(self.fp(),self.baseline)
  def as_value(p):
   t=p.read_text();k=t.index('AS_FLAGS = {');i=t.index('": "',k)+4
   p.write_text(t[:i]+'-mutation '+t[i:])
  with self.subTest('value'),self.mutate(name,as_value):self.changed()
  with self.subTest('key'),self.mutate(name,sub('AS_FLAGS = {','AS_FLAGS = {\n    "src/w_DEADBEEF.c": "--mutation",')):self.changed()
  # match maps src/w_X.c and src/func_X.c to one function, the later entry winning: order is content.
  with self.mutate(name,sub('AS_FLAGS = {','AS_FLAGS = {\n    "src/w_DEADBEEF.c": "",\n    "src/func_DEADBEEF.c": "--expand-div",')):
   before=self.fp()
   with self.subTest('order'),self.mutate(name,sub('    "src/w_DEADBEEF.c": "",\n    "src/func_DEADBEEF.c": "--expand-div",','    "src/func_DEADBEEF.c": "--expand-div",\n    "src/w_DEADBEEF.c": "",')):
    self.assertNotEqual(self.fp()['sha256'],before['sha256'])
  with self.subTest('second'),self.mutate(name,append('\nAS_FLAGS = {}\n')):
   with self.assertRaisesRegex(ValueError,'one AS_FLAGS'):self.fp()
  with self.subTest('literal'),self.mutate(name,sub('AS_FLAGS = {','AS_FLAGS = DEFAULT_AS_FLAGS | {')):
   with self.assertRaisesRegex(ValueError,'not a literal'):self.fp()
  def as_list(p):
   sub('AS_FLAGS = {','AS_FLAGS = [{')(p);sub('}\n# Explicit partition','}]\n# Explicit partition')(p)
  with self.subTest('dict'),self.mutate(name,as_list):
   with self.assertRaisesRegex(ValueError,'not a dict'):self.fp()
  with self.subTest('missing'),self.mutate(name,lambda p:p.unlink()):self.changed()
 def test_fidelity_tool_identities(self):
  for name in ['tools/fidelity/aspsx_diff.py','tools/fidelity/objread.py','tools/fidelity/certify_overlay_module.py','tools/build/slus_rodata_trim.py']:
   with self.subTest(name=name),self.mutate(name,lambda p:p.write_text(p.read_text()+'\n# dependency mutation\n')):self.changed()
 def test_assembler_source_and_include_are_bound(self):
  (self.r/'asm/nonmatchings').mkdir(parents=True,exist_ok=True)
  (self.r/'asm/nonmatchings/neighbor.s').write_text('.include "include/labels.inc"\n')
  with self.edit('ledger/splits/dungeon.jsonl',lambda v:v[3].update(source_kind='game_asm',asm_path='asm/nonmatchings/neighbor.s'),refresh=True):
   baseline=self.fp()
   for name in ['asm/nonmatchings/neighbor.s','include/labels.inc']:
    with self.subTest(name=name),self.mutate(name,lambda p:p.write_text(p.read_text()+'# assembly mutation\n')):
     self.assertNotEqual(self.fp()['sha256'],baseline['sha256'])
 def test_non_cdk_neighbor_compiler_is_bound(self):
  shutil.copytree(ROOT/'toolchain/compilers/gcc-2.7.2',self.r/'toolchain/compilers/gcc-2.7.2',symlinks=False,dirs_exist_ok=True)
  with self.edit('ledger/splits/dungeon.jsonl',lambda v:v[3].update(config='2.7.2+-G0'),refresh=True):
   before=self.fp()
   with self.mutate('toolchain/compilers/gcc-2.7.2/cc1',lambda p:p.write_bytes(p.read_bytes()+b'\0')):
    after=self.fp();self.assertEqual(after['module'],before['module']);self.assertNotEqual(after['windows'],before['windows'])
 def test_engine_results_unit_source_is_bound(self):
  (self.r/'src/dungeon/func_80024060.c').write_text('#include "neighbor.h"\nint engine_neighbor(void){return 1;}\n')
  with self.edit('ledger/splits/dungeon_engine.jsonl',lambda v:v.append({'foff':96,'size':16,'func_vram':'func_80024060','result':'MATCH','config':'2.7.2-cdk-G0'}),refresh=True):
   before=self.fp()
   with self.mutate('src/dungeon/func_80024060.c',lambda p:p.write_text(p.read_text()+'/* engine mutation */\n')):self.assertNotEqual(self.fp()['windows'],before['windows'])
 def test_neighbor_genuine_evidence_is_bound(self):
  # Add a separate full TU inside this module's window, with valid -0
  # evidence, so its genuine recipe input is a genuine neighbor dependency.
  m=copy.deepcopy(json.loads((self.r/'config/overlays/modules.json').read_text())['modules'][1]);r=F.records(self.r/'ledger/rows.jsonl')[3]
  m.update(key='dungeon_neighbor',region='bank0',source=r['c_path'],members=[{'id':r['id'],'source':r['c_path'],'function':r['func'],'foff':64,'vma':0x80024040,'size':32}],imports=[],owned_data=[],genuine_aspsx={'flags':['-0'],'evidence':'neighbor-genuine.json'})
  m['review_inputs'].append('neighbor-genuine.json')
  ev={'module':m['key'],'scope':'whole_tu','flags':['-q','-G0','-0'],'recipe':m['recipe'],'basis':'fixture receipt'}
  with self.mutate('neighbor-genuine.json',lambda p:p.write_text(json.dumps(ev))),self.edit('config/overlays/modules.json',lambda v:v['modules'].append(m),True,refresh=True):
   before=self.fp()
   with self.edit('neighbor-genuine.json',lambda v:v.update(basis='new receipt'),True):
    after=self.fp();self.assertEqual(after['module'],before['module']);self.assertNotEqual(after['windows'],before['windows'])
 def test_load_modules_once_per_fingerprint(self):
  with mock.patch.object(G,'load_modules',wraps=G.load_modules) as load:self.fp();self.assertEqual(load.call_count,1)
 def test_digest_only_envelope(self):
  fp=self.fp();self.assertEqual(set(fp),{'schema','sha256','module','windows','required_windows'})
  self.assertEqual(set(fp['module']),{'sha256'})
  for window in fp['windows'].values():self.assertEqual(set(window),{'sha256'})
  self.assertLess(len(json.dumps(fp)),4096)
 def test_parser_canonical_dialects(self):
  for label,result in [('2.7.2-cdk-G0',('2.7.2-cdk','-G0')),('2.8.1+-G0 -fno-schedule-insns',('2.8.1','-G0 -fno-schedule-insns')),('2.7.2-cdk -G0',('2.7.2-cdk','-G0')),('',('2.7.2',''))]:
   with self.subTest(label=label):self.assertEqual(F.parse_config_label(self.r,label,G),result)
 def test_config_parser_errors_reported_invalid(self):
  import overlay_module_evidence as E
  import yaml
  name='ledger/modules/overlay_'+self.m['key']+'.json'
  cases=[('def parse_config_label(label):\n return unknown_parser_global(label)\n','NameError'),
   ('def parse_config_label(label=unknown_parser_default):\n return label\n','NameError'),
   ('def parse_config_label(\n','SyntaxError')]
  for text,kind in cases:
   with self.subTest(kind=kind,text=text),self.mutate('tools/gate/match.py',lambda p:p.write_text(text)),self.mutate(name,lambda p:p.write_text('{}')):
    with self.assertRaisesRegex(ValueError,'invalid canonical config parser: '+kind):self.fp()
    with mock.patch.object(E,'load_modules',return_value=[self.m]),mock.patch.object(E,'certificate_reason',side_effect=lambda m,c,r:G.fingerprint(m,r)):
     result=E.module_status(self.r)
    self.assertFalse(result[0]['valid']);self.assertIn('invalid canonical config parser: '+kind,result[0]['reason'])
  # The boundary also handles raw errors from future reader dependencies.
  for exc in [NameError('reader global absent'),yaml.YAMLError('reader YAML invalid')]:
   with self.subTest(error=type(exc).__name__),self.mutate(name,lambda p:p.write_text('{}')):
    with mock.patch.object(E,'load_modules',return_value=[self.m]),mock.patch.object(E,'certificate_reason',side_effect=exc):result=E.module_status(self.r)
    self.assertFalse(result[0]['valid']);self.assertIn(type(exc).__name__,result[0]['reason'])
 def test_malformed_yaml_reported_invalid(self):
  import overlay_module_evidence as E
  name='ledger/modules/overlay_'+self.m['key']+'.json'
  with self.mutate('config/overlays/dungeon_test.overlay.yaml',lambda p:p.write_text('standalone_build: [\n')),self.mutate(name,lambda p:p.write_text('{}')):
   with self.assertRaisesRegex(ValueError,'invalid production window YAML: dungeon_test'):self.fp()
   with mock.patch.object(E,'load_modules',return_value=[self.m]),mock.patch.object(E,'certificate_reason',side_effect=lambda m,c,r:G.fingerprint(m,r)):result=E.module_status(self.r)
   self.assertFalse(result[0]['valid']);self.assertIn('invalid production window YAML: dungeon_test',result[0]['reason'])
 def test_no_flat_tools_in_canonical_fixture(self):
  self.assertFalse((self.r/'tools/match.py').exists());self.assertFalse((self.r/'tools/configure.py').exists())
  with mock.patch.dict(sys.modules,{'match':None}):self.assertEqual(self.fp(),self.baseline)
 def test_optional_compiler_specs_is_bound(self):
  # A comment-only specs file remains accepted by the actual driver and
  # exercises digest change, not a compiler subprocess exception.
  with self.mutate('toolchain/compilers/gcc-2.7.2-cdk/specs',lambda p:p.write_text('# changed driver side input\n')):self.changed()
 def test_inline_asm_macro_is_bound(self):
  with self.mutate('include/macro.inc',lambda p:p.write_text('# optional inline assembly dependency\n')):self.changed()

 def test_assignment_confidence_is_bound(self):
  with self.edit('ledger/modules.jsonl',lambda v:v[0].update(confidence='weak')):self.changed()
 def test_data_prefix_members_and_eligibility(self):
  # Exercise the separated prefix contract added at the rebase HEAD. A
  # prefix's L2 -> L4 placement must not invalidate its own certificate.
  paths=['config/overlays/modules.json','membership.json','ledger/rows.jsonl','ledger/modules.jsonl','ledger/levels.jsonl','ledger/baseline.jsonl','ledger/splits/dungeon.jsonl','ledger/splits/overlay_modules.build.json','overlays/dungeon/overlay_first_pass_results.json','src/dungeon/module0.c']
  backup={self.r/n:((self.r/n).read_bytes() if (self.r/n).exists() else None) for n in paths}
  try:
   doc=json.loads((self.r/paths[0]).read_text());m=doc['modules'][0]
   old=m['members'][0]['id'];fnid='dungeon/func_80024004';dataid='dungeon/D_80024000'
   first=m['members'][0];first.update(id=fnid,source='src/dungeon/func_80024004.c',foff=4,vma=0x80024004,size=28);first.pop('body_offset')
   m['data_members']=[{'id':dataid,'source':'src/dungeon/D_80024000.c','symbol':'D_80024000','foff':0,'vma':0x80024000,'size':4}]
   (self.r/first['source']).write_text('#include "local.h"\nint func_80024004(void){return 1;}\n')
   (self.r/m['data_members'][0]['source']).write_text('int D_80024000;\n')
   (self.r/m['source']).write_text('#include "D_80024000.c"\n#include "func_80024004.c"\n#include "func_80024020.c"\n')
   rows=F.records(self.r/'ledger/rows.jsonl');rows[0].update(id=fnid,c_path=first['source'],func=first['function'],true_name=first['function'],foff=4,size=28)
   rows.append(dict(rows[0],id=dataid,c_path=m['data_members'][0]['source'],func='D_80024000',true_name='D_80024000',foff=0,size=4,row_kind='data'))
   assignments=F.records(self.r/'ledger/modules.jsonl');assignments[0]['id']=fnid;assignments.append(dict(assignments[0],id=dataid))
   levels=F.records(self.r/'ledger/levels.jsonl');levels[0]['id']=fnid;levels.append(dict(levels[0],id=dataid,level=2))
   ev=json.loads((self.r/'membership.json').read_text());ev['members']=[a['id'] for a in G.all_members(m)]
   splits=F.records(self.r/'ledger/splits/dungeon.jsonl');splits[0].update(foff=4,size=28,func_vram=first['function'],c_path=first['source']);splits.append({'foff':0,'size':4,'result':'MATCH','func_vram':'D_80024000','c_path':m['data_members'][0]['source'],'config':'2.7.2-cdk-G0'})
   for n,v,obj in [('config/overlays/modules.json',doc,True),('membership.json',ev,True),('ledger/rows.jsonl',rows,False),('ledger/modules.jsonl',assignments,False),('ledger/levels.jsonl',levels,False),('ledger/baseline.jsonl',[{'id':dataid,'exact':True}],False),('ledger/splits/dungeon.jsonl',splits,False)]:self.write(n,v,obj)
   self.refresh();before=self.fp()
   levels[-1].update(level=4,l4_residue=[]);self.write('ledger/levels.jsonl',levels)
   self.assertEqual(self.fp(),before)
   with self.edit('ledger/baseline.jsonl',lambda v:v[0].update(exact=False)):
    with self.assertRaisesRegex(ValueError,'data prefix eligibility failed'):self.fp()
   with self.mutate('src/dungeon/D_80024000.c',lambda p:p.write_text('int D_80024000 = 1;\n')):self.assertNotEqual(self.fp()['module'],before['module'])
  finally:
   for p,data in backup.items():
    if data is None:p.unlink(missing_ok=True)
    else:p.write_bytes(data)

 def test_preprocessor_cache_reuses_actual_dependency_set(self):
  F._M_CACHE.clear()
  with mock.patch.object(F.subprocess,'run',wraps=F.subprocess.run) as run:
   self.fp();first=run.call_count
   self.fp();self.assertGreater(first,0);self.assertEqual(run.call_count,first)

 def test_custom_include_search_shadow_is_bound(self):
  (self.r/'extra').mkdir(exist_ok=True)
  with self.edit('ledger/splits/dungeon.jsonl',lambda v:v[3].update(config='2.7.2-cdk-G0 -Iextra'),refresh=True):
   before=self.fp();self.assertEqual(self.fp(),before)
   with self.mutate('extra/neighbor.h',lambda p:p.write_text('/* custom path shadow */\n')):self.assertNotEqual(self.fp()['windows'],before['windows'])
 def test_driver_recipe_override_refused(self):
  with self.edit('ledger/splits/dungeon.jsonl',lambda v:v[3].update(config='2.7.2-cdk-G0 -Bextra'),refresh=True):
   with self.assertRaisesRegex(ValueError,'unmodelled compiler recipe override: -Bextra'):self.fp()

class TownScopedFingerprint(unittest.TestCase):
 write=ScopedFingerprint.__dict__['write']
 refresh=ScopedFingerprint.__dict__['refresh']
 tearDownClass=ScopedFingerprint.__dict__['tearDownClass']
 mutate=ScopedFingerprint.mutate
 fp=ScopedFingerprint.fp
 changed=ScopedFingerprint.changed
 edit=ScopedFingerprint.edit
 @classmethod
 def setUpClass(cls):
  ScopedFingerprint.setUpClass.__func__(cls)
  r=cls.r
  (r/'overlays/dungeon/first_pass_matched').unlink()
  for prefix in ['src','raw','overlays']:(r/prefix/'dungeon').rename(r/prefix/'town')
  for p in [*list((r/'config').glob('*dungeon*')),*list((r/'config/overlays').glob('*dungeon*')),*list((r/'ledger/splits').glob('dungeon.*'))]:p.rename(p.with_name(p.name.replace('dungeon','town')))
  (r/'overlays/town/first_pass_matched').symlink_to(r/'src/town',target_is_directory=True)
  for p in [r/'membership.json',*list((r/'ledger').glob('*.jsonl')),*list((r/'ledger/splits').glob('*.jsonl')),*list((r/'config/overlays').glob('*.json*')),*list((r/'config/overlays').glob('*.yaml'))]:
   if p.is_file():p.write_text(p.read_text().replace('dungeon','town'))
  (r/'work/disc/containers/DUNGEON_DUNGEON.BIN').rename(r/'work/disc/containers/TOWN_TOWN.BIN')
  # Empty engine unit remains a valid results input, but belongs to dungeon,
  # so remove it from the town window's matched groups.
  import yaml
  p=r/'config/overlays/town_test.overlay.yaml';cfg=yaml.safe_load(p.read_text());cfg['standalone_build']['matched_sources']=cfg['standalone_build']['matched_sources'][:1];p.write_text(yaml.safe_dump(cfg))
  doc=json.loads((r/'config/overlays/modules.json').read_text())
  for m in doc['modules']:
   m['imports']=[d for d in m['imports'] if 'asset' not in d]
  cls.write('config/overlays/modules.json',doc,True)
  cls.refresh();cls.m=G.load_modules(r)[0];cls.baseline=G.fingerprint(cls.m,r)
 def test_town_source_invalidates(self):
  with self.mutate(self.m['members'][0]['source'],lambda p:p.write_text(p.read_text()+'/* town mutation */\n')):self.changed()
 def test_town_unrelated_registry_retained(self):
  with self.edit('ledger/rows.jsonl',lambda v:v[2].update(note='town other bank'),refresh=True):self.assertEqual(self.fp(),self.baseline)
 def test_town_sibcall_bound(self):
  with self.mutate('config/sibcall_syms.town.txt',lambda p:p.write_text('func_80024020\n')):self.changed()
 def test_town_parsed_window_required(self):
  name='config/overlays/neutral_town.overlay.yaml'
  with self.mutate(name,lambda p:p.write_text((self.r/'config/overlays/town_test.overlay.yaml').read_text().replace('name: town_test','name: town_extra'))):self.assertIn(name,self.fp()['required_windows'])

from unittest import mock
if __name__=='__main__':unittest.main()

class WindowModulesFamily(unittest.TestCase):
    def test_foreign_container_module_is_not_in_window(self):
        import overlay_scoped_fingerprint as S
        class G:
            @staticmethod
            def module_extents(m): return m['ext']
        mods = [{'key': 'town_a', 'container': 'town', 'ext': [(0x100, 0x200)]},
                {'key': 'ovm', 'container': 'ovmovie', 'ext': [(0x0, 0x1b88)]},
                {'key': 'eng', 'container': 'dungeon_engine', 'ext': [(0x10, 0x20)]}]
        self.assertEqual([m['key'] for m in S.window_modules(mods, 'town', 0x0, 0x52000, G)], ['town_a'])
        self.assertEqual([m['key'] for m in S.window_modules(mods, 'dungeon', 0x0, 0x100, G)], ['eng'])
        self.assertEqual(S.window_modules(mods, 'town', 0x300, 0x400, G), [])
