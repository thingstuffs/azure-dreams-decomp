#!/usr/bin/env python3
"""Complete-TU overlay gate, first stage: contiguous text, reviewed external storage.

No payload may be discarded or supplied from retail. Every invocation compiles the
whole cohort once, compares genuine ASPSX, links its natural order at the proven
load address and checks all bytes. The window adapter projects only these bytes.
Native rodata heads require explicit complete coverage and strong membership.
COMMON, mixed-recipe and unsupported allocations fail closed.
"""
from __future__ import annotations
import argparse, dataclasses, hashlib, importlib.util, json, os, re, shlex, shutil, struct, subprocess, sys, tempfile, time
from pathlib import Path
ROOT=Path(__file__).resolve().parents[1]
if ROOT.name=='tools': ROOT=ROOT.parent
SCHEMA='overlay-module-native-v4'
sys.path.insert(0, str(Path(__file__).resolve().parent))  # sibling import when loaded as gate.overlay_module_gate
import overlay_native_rodata as N
CONTAINERS={'dungeon':'DUNGEON_DUNGEON.BIN','town':'TOWN_TOWN.BIN','main':'MAIN_MAIN.BIN','ovmovie':'OVMOVIE.BIN'}
META={'.reginfo','.MIPS.abiflags'}
def sha(p): return hashlib.sha256(Path(p).read_bytes()).hexdigest()
def hashed(v): return hashlib.sha256(json.dumps(v,sort_keys=True,separators=(',',':')).encode()).hexdigest()
def local(root,name):
 p=Path(name)
 if p.is_absolute() or '..' in p.parts or not name: raise ValueError('unsafe relative path: '+str(name))
 return Path(root)/p

def rows(root):
 return {r['id']:r for l in (root/'ledger/rows.jsonl').read_text().splitlines() if l.strip() for r in [json.loads(l)] if r['kind']=='overlay'}

def ranges(root,family):
 return [json.loads(l) for l in (root/'config/overlays'/f'{family}.rowbase.jsonl').read_text().splitlines() if l.startswith('{')]

def load_modules(root=ROOT):
 root=Path(root);path=root/'config/overlays/modules.json'
 if (root/'config/overlay_modules_disabled').exists() or not path.exists(): return []
 doc=json.loads(path.read_text())
 if doc['schema'] not in (SCHEMA,'overlay-module-native-v3','overlay-module-text-v2'):raise ValueError('unsupported manifest')
 reg=rows(root);seen=set();keys=set()
 for m in doc['modules']:
  if not re.fullmatch('[a-z][a-z0-9_]*',m['key']) or m['key'] in keys:raise ValueError('duplicate/invalid key')
  keys.add(m['key'])
  if m['owned_data']:validate_owned_layout(m)
  genuine_flags(m,root)
  if not m['members'] or m['recipe']!={'cfg':'2.7.2-cdk-G0','row_asflags':''}:raise ValueError('unsupported recipe/empty cohort')
  if not m['headers'] or not m['review_inputs']:raise ValueError('missing shared contract or review inputs')
  for p in [m['source'],*m['headers'],*m['review_inputs']]:local(root,p)
  rr=[r for r in ranges(root,m['container']) if r['region']==m['region'] and r['base_confidence']=='proven']
  if len(rr)!=1:raise ValueError('missing unique proven load region')
  region=rr[0];delta=int(region['delta'],0);cursor=m['members'][0]['foff']
  for a in m['members']:
   r=reg[a['id']]
   if a['id'] in seen:raise ValueError('duplicate member')
   seen.add(a['id'])
   expected={'id':r['id'],'source':f"src/{r['container']}/{Path(r['c_path']).name}",'function':('func_%08X' % (r['foff']+delta+a['body_offset'])) if 'body_offset' in a else (r.get('true_name') or r['func']),'foff':r['foff'],'vma':r['foff']+delta,'size':r['size']}
   if 'body_offset' in a:expected['body_offset']=a['body_offset']
   if a!=expected or a['foff']!=cursor or r['container']!=m['container'] or r['cfg']!=m['recipe']['cfg'] or (r.get('row_asflags') or '')!=m['recipe']['row_asflags']:raise ValueError('member identity, contiguity or recipe differs: '+a['id'])
   cursor+=a['size']
  if not int(region['foff_start'],0)<=m['members'][0]['foff']<cursor<=int(region['foff_end'],0):raise ValueError('module outside proven load map')
  if m.get('membership_evidence'):
   ev=json.loads(local(root,m['membership_evidence']).read_text())
   if m['membership_evidence'] not in m['review_inputs']:raise ValueError('membership evidence not fingerprinted')
   group=ev['ledger_group']
   assignments=[json.loads(l) for l in (root/'ledger/modules.jsonl').read_text().splitlines() if l.strip()]
   cohort=sorted([x['id'] for x in assignments if all(x[k]==v for k,v in group.items())],key=lambda rid:reg[rid]['foff'])
   if cohort!=[a['id'] for a in m['members']]:raise ValueError('complete ledger cohort differs')
   levels={x['id']:x for l in (root/'ledger/levels.jsonl').read_text().splitlines() for x in [json.loads(l)]}
   for a in m['members']:
    level=levels[a['id']]
    if level['level']<3 or level['pins_left'] or level['tail_jumps'] or set(level['l4_residue'])-{'not_in_module'}:raise ValueError('L3/placement screen failed')
   if ev['members']!=[a['id'] for a in m['members']] or ev['confidence']!='strong' or not ev['basis'] or not ev['coverage_complete']:raise ValueError('strong membership screen failed')
  im=m['imports']
  if any(d.get('evidence') and d['evidence'] not in m['review_inputs'] for d in im):raise ValueError('import evidence not fingerprinted')
  if len({x['symbol'] for x in im})!=len(im):raise ValueError('duplicate import')
  for d in im:
   if d['kind']=='data':
    if 'asset' in d:
     validate_asset(root,d);continue
    if d['owner']!='retail_asset:'+m['container']+':'+m['region'] or d['foff']+delta!=d['vma'] or d['view_bytes']<=0:raise ValueError('external storage ownership/load map differs')
    if not int(region['foff_start'],0)<=d['foff']<d['foff']+d['view_bytes']<=int(region['foff_end'],0):raise ValueError('external view outside resident asset')
   elif d['kind']=='runtime_data':
    validate_runtime(root,d)
   elif d['kind']!='function':raise ValueError('unknown import kind')
 return doc['modules']


def validate_owned_layout(m):
 N.validate_layout(m)

def genuine_flags(m,root):
 prop=m.get('genuine_aspsx')
 if prop is None:return []
 if set(prop)!={'flags','evidence'} or prop['flags']!=['-0']:raise ValueError('unsupported whole-TU genuine recipe')
 if prop['evidence'] not in m['review_inputs']:raise ValueError('genuine recipe evidence not fingerprinted')
 ev=json.loads(local(root,prop['evidence']).read_text())
 if (ev.get('module')!=m['key'] or ev.get('scope')!='whole_tu' or ev.get('flags')!=['-q','-G0','-0']
  or ev.get('recipe')!=m['recipe'] or not ev.get('basis')):raise ValueError('whole-TU genuine recipe evidence differs')
 return prop['flags']


def payload_spec(m):
 ds=[('.rodata',sum(d['size'] for d in m['owned_data']))] if m['owned_data'] else []
 return ds+[('.text.'+a['function'],a['size']-a.get('body_offset',0)) for a in m['members']]

def validate_asset(root,d):
 # Cross-resident imports remain external views. The load map and view are
 # explicit evidence inputs, separate from the owning module's code range.
 local(root,d['asset']);e=local(root,d['evidence'])
 proof=json.loads(e.read_text());v=proof['views'][d['symbol']]
 if v!=d or d['view_bytes']<=0 or d['owner']!='retail_asset:'+d['asset']:raise ValueError('external asset evidence differs')
 mp=proof['maps'][d['map']]
 if mp['asset']!=d['asset'] or d['foff']+mp['delta']!=d['vma'] or not mp['file_start']<=d['foff']<d['foff']+d['view_bytes']<=mp['file_end']:raise ValueError('external asset load map differs')
 if not mp.get('basis'):raise ValueError('missing external asset map basis')
 if mp['kind']=='psx_exe':
  with (root/d['asset']).open('rb') as f:head=f.read(0x800)
  if head[:8]!=b'PS-X EXE':raise ValueError('invalid PS-X EXE asset')
  load,size=struct.unpack_from('<II',head,0x18)
  if (mp['file_start'],mp['file_end'],mp['delta'])!=(0x800,0x800+size,load-0x800):raise ValueError('PS-X EXE map differs')
 elif mp['kind']=='rowbase':
  match=[r for r in ranges(root,'dungeon') if r['region']==mp['region'] and r['base_confidence']=='proven']
  if len(match)!=1 or tuple(int(match[0][k],0) for k in ('foff_start','foff_end','delta'))!=(mp['file_start'],mp['file_end'],mp['delta']):raise ValueError('resident load-map evidence differs')
 else:raise ValueError('unsupported external asset map')

def validate_runtime(root,d):
 proof=json.loads(local(root,d['evidence']).read_text())
 if proof['runtime_views'].get(d['symbol'])!=d or d['owner']!='resident_runtime:slus' or d['view_bytes']<=0:raise ValueError('runtime storage evidence differs')
 if not local(root,d['declaration']).is_file():raise ValueError('missing runtime storage declaration')
 # This grants no allocation or initialization claim: the module imports an
 # existing runtime object. Definitions/byte ownership remain external.


def graph(root=ROOT):
 root=Path(root);reg=rows(root);mods=load_modules(root);taken={a['id'] for m in mods for a in m['members']}
 edges=[{'module':m['key'],'source':m['source'],'recipe':m['recipe'],'rows':[a['id'] for a in m['members']]} for m in mods]
 edges += [{'source':f"src/{r['container']}/{Path(r['c_path']).name}",'recipe':{'cfg':r['cfg'],'row_asflags':r.get('row_asflags') or ''},'rows':[rid]} for rid,r in sorted(reg.items()) if rid not in taken]
 return {'schema':SCHEMA,'logical_rows':len(reg),'edges':edges}

def affected_windows(m,root=ROOT):
 first=m['members'][0]['foff'];end=m['members'][-1]['foff']+m['members'][-1]['size'];out=[]
 for p in sorted((root/'config/overlays').glob(m['container']+'*.overlay.yaml')):
  t=p.read_text();a=re.search(r'file_start:\s*(0x[\da-fA-F]+|\d+)',t);b=re.search(r'file_end:\s*(0x[\da-fA-F]+|\d+)',t)
  if a and b and int(a[1],0)<end and first<int(b[1],0):out.append(str(p.relative_to(root)))
 if not out:raise ValueError('module has no production window')
 return out

def closure(root,starts):
 pending=list(starts);found=set();resolved={}
 while pending:
  n=pending.pop()
  if n in found:continue
  p=local(root,n);t=p.read_text();found.add(n)
  for line in t.splitlines():
   if not re.match(r'\s*(?:#\s*include|\.include)\b',line):continue
   hit=re.match(r'\s*(?:#\s*include|\.include)\s+"([^"]+)"',line)
   if not hit:
    # Ask the actual preprocessor about conditional/system includes; inactive
    # NON_MATCHING headers are not build dependencies.
    gcc=root/'toolchain/compilers/gcc-2.7.2-cdk'
    pdep=subprocess.run([str(gcc/'gcc'),'-B'+str(gcc)+'/', '-M','-G0','-I'+str(root/'include'),str(p)],capture_output=True,text=True,check=True)
    for dep in pdep.stdout.replace('\\\n',' ').split(':',1)[1].split():
     dest=Path(dep).absolute()
     if not dest.is_relative_to(root):raise ValueError('system dependency outside fingerprint root: '+dep)
     found.add(str(dest.relative_to(root)))
    continue
   key=(p.parent,hit[1])
   target=resolved.get(key)
   if target is None:
    opts=[p.parent/hit[1],root/'include'/hit[1],root/hit[1]]
    dest=next((Path(os.path.abspath(o)) for o in opts if o.is_file()),None)
    if dest is None or not dest.is_relative_to(root):raise ValueError('include escapes build root: '+line)
    target=str(dest.relative_to(root));resolved[key]=target
   pending.append(target)
 return found

def gate_tool(root,name):
 p=root/'tools/gate'/name
 return p if p.exists() else root/'tools'/name

def fingerprint(m,root=ROOT,windows=True):
 root=Path(root).absolute();wins=affected_windows(m,root);compiler_versions={'2.7.2-cdk'}
 evidence_foffs={a['foff'] for a in m['members']}
 source_starts=[m['source'],*m['headers'],*(a['source'] for a in m['members']),'include/labels.inc',*(p for p in m['review_inputs'] if p.endswith(('.c','.h')))]
 names=set()
 names.update(['config/overlays/modules.json','ledger/rows.jsonl','ledger/splits/overlay_modules.build.json',f"config/overlays/{m['container']}.rowbase.jsonl",'config/names.tsv',*m['review_inputs']])
 names.update(wins)
 if m.get('membership_evidence'):names.add('ledger/modules.jsonl')
 names.update(d['declaration'] for d in m['imports'] if d['kind']=='runtime_data')
 suffix='.'+m['container'] if m['container']!='main' else ''
 names.update('config/'+k+suffix+'.txt' for k in ['noreturn_syms','sibcall_syms'])
 for p in ['config/overlays/abs_syms.txt','config/slus_006.14.symbols.txt','config/noreturn_false_members.jsonl',f"config/overlays/{m['container']}.as_flags.jsonl",f"config/overlays/{m['container']}.rodata_owners.jsonl"]:
  if (root/p).exists():names.add(p)
 # Bind every neighbouring C/header and split record consumed by the affected windows.
 if windows:
  import yaml
  for wn in wins:
   y=yaml.safe_load((root/wn).read_text());sb=y['standalone_build'];fs=int(sb['window']['file_start']);fe=int(sb['window']['file_end'])
   sp=y['options'].get('symbol_addrs_path')
   if sp:names.add(sp)
   for grp in [{'results':sb['split_results']},*sb.get('matched_sources',[])]:
    # Canonical split ledgers are authoritative; exported JSON is also bound in a view.
    path=root/grp['results']
    if m['container'] in {'town','dungeon'}:
     family=Path(grp['results']).parts[1]
     ledger=root/'ledger/splits'/f'{family}.jsonl'
     if ledger.exists():
      evidence_foffs.update(r['foff'] for l in ledger.read_text().splitlines() if l.strip() for r in [json.loads(l)]
                           if r.get('result')=='MATCH' and not r.get('rerun') and r.get('source_kind','c')=='c'
                           and isinstance(r.get('foff'),int) and fs<=r['foff'] and r['foff']+(r.get('size') or 0)<=fe)
    # Generated view inputs must agree on EVERY fingerprint, including
    # after module/window builds. Bind their normalized canonical contents.
    if path.exists():
     family=Path(grp['results']).parts[1]
     ledger=root/'ledger/splits'/f'{family}.jsonl'
     expected=[json.loads(l) for l in ledger.read_text().splitlines() if l.strip()]
     if json.loads(path.read_text())!=expected:raise ValueError('exported split roster differs: '+grp['results'])
   for r in rows(root).values():
    if r['container'] in ({'dungeon','dungeon_engine'} if m['container']=='dungeon' else {m['container']}) and fs<=r['foff'] and r['foff']+r['size']<=fe and r.get('source_kind','c')=='c':
     evidence_foffs.add(r['foff'])
    if r['container']==m['container'] and fs<=r['foff'] and r['foff']+r['size']<=fe:
     compiler_versions.add(r['cell'])
     p=f"src/{r['container']}/{Path(r['c_path']).name}"
     if (root/p).exists():source_starts.append(p)
  for f in [m['container'], 'dungeon_engine' if m['container']=='dungeon' else m['container']]:
   p=f'ledger/splits/{f}.jsonl'
   if (root/p).exists():names.add(p)
 # Resolve the combined include closure once; shared headers are read once.
 names.update(closure(root,source_starts))
 gate_names=['overlay_native_rodata.py','cc.sh','ccproc.py','overlay_local_gate.py','overlay_module_gate.py','overlay_evidence.py','overlay_as_flags.py','gen_noreturn_syms.py','rowbase_naming_debt.py','match.py','rowbase_identity.py','configure.py','live_truth.py','rowbase.py','az_target.py','residue_class.py','overlay_func_compare.py','oracle_scoring.py']
 tools=[gate_tool(root,n) for n in gate_names]
 tools += [root/'tools/fidelity'/n for n in ['aspsx_diff.py','objread.py','certify_overlay_module.py']]
 tools += [root/'tools/overlay_module_evidence.py',root/'tools/build/slus_rodata_trim.py']
 tools += [root/'toolchain/compilers'/('gcc-'+version)/n for version in sorted(compiler_versions) for n in ['gcc','cc1','cpp']]
 tools += [root/'toolchain/genuine/bin/wibo',root/'toolchain/genuine/psyq/psyq4.4/ASPSX.EXE',root/'.venv/bin/python']
 tools += sorted((root/'toolchain/maspsx').rglob('*.py'))
 tools += [Path(shutil.which(n)) for n in ['python3','bash','mipsel-linux-gnu-as','mipsel-linux-gnu-ld','mipsel-linux-gnu-objcopy','mipsel-linux-gnu-nm']]
 # Path-independent identities permit the canonical tree and its exported build view.
 inp={n:sha(root/n) for n in sorted(names)}
 tool_inputs={('gate/'+p.name if p in tools[:len(gate_names)] else str(p.relative_to(root)) if p.is_relative_to(root) else str(p)):sha(p) for p in tools}
 container=root/'work/disc/containers'/CONTAINERS[m['container']]
 asset={}
 with container.open('rb') as f:
  for d in m['imports']:
   if d['kind']=='data':
    if 'asset' in d:
     with (root/d['asset']).open('rb') as af:af.seek(d['foff']);b=af.read(d['view_bytes'])
    else:f.seek(d['foff']);b=f.read(d['view_bytes'])
    if len(b)!=d['view_bytes']:raise ValueError('truncated external data view')
    asset[d['symbol']]=hashlib.sha256(b).hexdigest()
  a=m['members'][0];f.seek(a['foff']);b=f.read(sum(x['size'] for x in m['members']));asset['module_text']=hashlib.sha256(b).hexdigest()
 screening={}
 if m.get('membership_evidence'):
  # Do not bind the level number or not_in_module: placement itself changes
  # those outputs. Bind all eligibility inputs without a certificate cycle.
  levels={x['id']:x for l in (root/'ledger/levels.jsonl').read_text().splitlines() for x in [json.loads(l)]}
  screening={a['id']:{'l3':levels[a['id']]['level']>=3,'pins':levels[a['id']]['pins_left'],'tail_jumps':levels[a['id']]['tail_jumps'],'residue':sorted(set(levels[a['id']]['l4_residue'])-{'not_in_module'})} for a in m['members']}
 # Certificates bind the same frozen bank evidence consumed by module and
 # neighbouring C compiles; rowbase/census audit files alone miss raw edits.
 bank_inputs={}
 if m['container'] in {'town','dungeon'}:
  # Canonical package when present, flat tool in exported build views.
  if (root/'tools/gate/gen_noreturn_syms.py').exists():
   sys.path.insert(0,str(root/'tools'))
   from gate.gen_noreturn_syms import scoped_inputs,_find_root
  else:
   from gen_noreturn_syms import scoped_inputs,_find_root
  # the compile's evidence root: a view root (build_ovl_gate) has no raw/ and its compiles read the enclosing repo's
  bank_inputs=scoped_inputs(m['container'],evidence_foffs,root=_find_root(Path(root).resolve()/'tools'/'_'))
 payload={'module':m,'inputs':inp,'tools':tool_inputs,'retail':asset,'screening':screening}
 if bank_inputs:payload['bank_noreturn']=bank_inputs
 result={'sha256':hashed(payload),'inputs':inp,'tools':tool_inputs,'retail':asset,'screening':screening}
 if bank_inputs:result['bank_noreturn']=bank_inputs
 return result

def command(args,cwd,env,log,stdin=None,timeout=300):
 p=subprocess.run([str(a) for a in args],cwd=cwd,env=env,input=stdin,capture_output=True,timeout=timeout)
 Path(log).write_text('$ '+shlex.join(map(str,args))+'\n'+p.stdout.decode(errors='replace')+p.stderr.decode(errors='replace'))
 if p.returncode:raise ValueError('command failed: '+str(log))
 return p.stdout

def sections(path):
 b=path.read_bytes();off=struct.unpack_from('<I',b,32)[0];ent,num,ni=struct.unpack_from('<HHH',b,46);hs=[struct.unpack_from('<10I',b,off+i*ent) for i in range(num)];s=b[hs[ni][4]:hs[ni][4]+hs[ni][5]]
 return [{'name':s[h[0]:].split(b'\0',1)[0].decode(),'type':h[1],'flags':h[2],'size':h[5]} for h in hs]

def build(m,out,root=ROOT,substitutions=None):
 root=Path(root).absolute();out=Path(out).absolute();out.mkdir(parents=True,exist_ok=True)
 if json.loads((root/'ledger/splits/overlay_modules.build.json').read_text())!=graph(root):raise ValueError('physical graph stale or incomplete')
 before=fingerprint(m,root);env=dict(os.environ,TMPDIR=str(out),PYTHONDONTWRITEBYTECODE='1')
 for k in ['AZURE_MASPSX','AZURE_MASPSX_COMPANION','MASPSX_NORETURN_FILE','MASPSX_SIBCALL_FILE']:env.pop(k,None)
 suffix='.'+m['container'] if m['container']!='main' else ''
 for kind in ['NORETURN','SIBCALL']:env['MASPSX_'+kind+'_FILE']=str(root/'config'/(kind.lower()+'_syms'+suffix+'.txt'))
 source=root/m['source'];candidate_hashes={}
 if substitutions:
  # A private C preprocessor include overlay replaces a member, keeping the full TU.
  allowed={a['source'] for a in m['members']}
  if set(substitutions)-allowed:raise ValueError('candidate is not a member')
  text=source.read_text()
  for line in text.splitlines():
   hit=re.fullmatch(r'\s*#include "([^"]+)"\s*',line)
   if not hit:continue
   target=Path(os.path.abspath(source.parent/hit[1]))
   if target.is_file() and target.is_relative_to(root):
    name=str(target.relative_to(root));replacement=Path(substitutions.get(name,target)).absolute()
    text=text.replace(line,'#include "'+str(replacement)+'"')
  # Headers are resolved through -I root/include below. Every replaced source is bound.
  source=out/'candidate.c';source.write_text(text)
  candidate_hashes={k:sha(v) for k,v in substitutions.items()}
 # Native cohorts are one TU in one validated load region. They must use
 # the same bank scope as ordinary row compiles, never the family union.
 if m['container'] in {'town','dungeon'}:
  spec=importlib.util.spec_from_file_location('module_bank_census',gate_tool(root,'gen_noreturn_syms.py'))
  census=importlib.util.module_from_spec(spec);spec.loader.exec_module(census)
  names=set(census.scoped_census(m['container'],m['members'][0]['foff'],root=root)['names'])
  names.update(census.scan_text(source.read_text()))
  for member in m['members']:
   path=Path((substitutions or {}).get(member['source'],root/member['source']))
   names.update(census.scan_text(path.read_text()))
  evidence=out/'noreturn_syms.bank.txt';evidence.write_text(census.render(sorted(names)))
  env['MASPSX_NORETURN_FILE']=str(evidence)
 gcc=root/'toolchain/compilers/gcc-2.7.2-cdk';asm=out/'module.s';obj=out/'module.o'
 command([gcc/'gcc','-B'+str(gcc)+'/', '-S','-O2','-G0','-I'+str(root/'include'),'-w',source,'-o',asm],root,env,out/'compile.log')
 raw=asm.read_bytes();proc=command([sys.executable,gate_tool(root,'ccproc.py'),'--names-tsv',root/'config/names.tsv'],root,env,out/'ccproc.log',raw);(out/'sectioned.s').write_bytes(proc)
 command([root/'.venv/bin/python',root/'toolchain/maspsx/maspsx.py','--aspsx-version=2.79','--dont-force-G0','--run-assembler','--gnu-as-path=mipsel-linux-gnu-as','-I'+str(root),'-I'+str(root/'include'),'-EL','-march=r3000','-G8','-o',obj],root,env,out/'assemble.log',proc)
 shutil.copy2(obj,out/'module.untrimmed.o')
 cooked,_=N.prepare_object(m,obj.read_bytes(),root/'tools/build/slus_rodata_trim.py');obj.write_bytes(cooked)
 expected=payload_spec(m);secs=sections(obj);payload=[s for s in secs if s['flags']&2 and s['size'] and s['name'] not in META]
 if [(s['name'],s['size']) for s in payload]!=expected:raise ValueError('complete allocated payload/order/extent differs: '+str(payload))
 nm=command(['mipsel-linux-gnu-nm','-S',obj],root,env,out/'object_symbols.log').decode()
 if any(l.split()[-2].upper()=='C' for l in nm.splitlines() if len(l.split())>=2):raise ValueError('unowned COMMON')
 undefined={l.split()[-1] for l in nm.splitlines() if len(l.split())==2 and l.split()[0]=='U'}
 imports={d['symbol']:d['vma'] for d in m['imports']}
 if undefined!=set(imports):raise ValueError('import inventory differs: '+str(undefined^set(imports)))
 addresses=dict(imports,**{a['function']:a['vma']+a.get('body_offset',0) for a in m['members']})
 addresses.update({d['symbol']:d['vma'] for d in m['owned_data'] if d.get('symbol')})
 # One natural-order placement; never a separate address directive per member.
 ld=out/'module.ld';ld.write_text('OUTPUT_FORMAT("elf32-tradlittlemips")\nOUTPUT_ARCH(mips)\n_gp = 0x80080994;\n'+''.join(f'{s} = 0x{v:X};\n' for s,v in imports.items())+'SECTIONS {\n'+f' .module 0x{m["members"][0]["vma"]:X} : {{ "{obj}"(.rodata .text.*) }}\n'+f' ASSERT(SIZEOF(.module) == {sum(a["size"] for a in m["members"])}, "module extent")\n /DISCARD/ : {{ *(.text) *(.reginfo) *(.MIPS.abiflags) *(.pdr) *(.comment) *(.note*) *(.mdebug*) *(.gnu.attributes) }}\n}}\n')
 elf=out/'module.elf';binary=out/'module.bin'
 command(['mipsel-linux-gnu-ld','-EL','-T',ld,'-Map',out/'module.map','-o',elf,obj],root,env,out/'link.log')
 command(['mipsel-linux-gnu-objcopy','-O','binary',elf,binary],root,env,out/'objcopy.log')
 syms=command(['mipsel-linux-gnu-nm','-n','-S',elf],root,env,out/'linked_symbols.log').decode()
 placed={p[-1]:int(p[0],16) for l in syms.splitlines() if len(p:=l.split())>=3}
 if any(placed.get(a['function'])!=a['vma']+a.get('body_offset',0) for a in m['members']) or any(placed.get(d['symbol'])!=d['vma'] for d in m['owned_data'] if d.get('symbol')):raise ValueError('natural linked addresses differ')
 data=binary.read_bytes();first=m['members'][0]
 with (root/'work/disc/containers'/CONTAINERS[m['container']]).open('rb') as f:f.seek(first['foff']);retail=f.read(len(data))
 (out/'retail.bin').write_bytes(retail)
 if data!=retail:raise ValueError('whole-module retail mismatch')
 # Assemble the very same gcc stream, canonical names but no GAS section split.
 canon=command([sys.executable,gate_tool(root,'ccproc.py'),'--names-only','--names-tsv',root/'config/names.tsv'],root,env,out/'names.log',raw)
 sys.path.insert(0,str(root/'tools/fidelity'));import aspsx_diff as A
 (out/'IN.S').write_bytes(A.aspsx_input(canon.decode()))
 # ASPSX has a DOS path-length limit; keep its working directory short.
 (root/'work').mkdir(exist_ok=True)
 with tempfile.TemporaryDirectory(prefix='g',dir=root/'work') as td:
  td=Path(td);shutil.copy2(out/'IN.S',td/'IN.S')
  command([root/'toolchain/genuine/bin/wibo',root/'toolchain/genuine/psyq/psyq4.4/ASPSX.EXE','-q','-G0',*genuine_flags(m,root),'-o','OUT.OBJ','IN.S'],td,dict(env,TMPDIR=str(td),TMP=str(td),TEMP=str(td)),out/'genuine.log')
  shutil.copy2(td/'OUT.OBJ',out/'OUT.OBJ')
 ma=A.View(A.read_elf(obj.read_bytes()));ge=A.View(A.read_lnk((out/'OUT.OBJ').read_bytes()),ref=ma)
 if ma.obj.unknown or ge.obj.unknown:raise ValueError('unknown object record/relocation')
 if set(ma.funcs)!={a['function'] for a in m['members']} or set(ge.funcs)!=set(ma.funcs):raise ValueError('complete function set differs')
 if any(v for k,v in ge.obj.sections.items() if k not in ('.text','.rdata','.rodata')):raise ValueError('unowned genuine allocated section')
 if any(v[2]=='common' for v in ge.obj.symbols.values()):raise ValueError('genuine COMMON')
 for a in m['members']:
  if ma.funcs[a['function']]!=('.text.'+a['function'],0,a['size']-a.get('body_offset',0)):raise ValueError('maspsx function extent differs')
 comp=A.compare_units(ma,ge)
 if not comp['exact']:raise ValueError('whole-TU genuine mismatch: '+str(comp))
 proof_artifacts={n:(out/n).read_bytes() for n in ['module.s','sectioned.s','module.untrimmed.o','module.o','IN.S','OUT.OBJ']}
 native=N.make_proof(m,(out/'module.untrimmed.o').read_bytes(),obj.read_bytes(),ma,ge,canon.decode(),root/'tools/build/slus_rodata_trim.py',proof_artifacts)
 (out/'rodata_proof.json').write_text(json.dumps(native,indent=2)+'\n')
 genuine=bytearray()
 prefix=sum(d['size'] for d in m['owned_data'])
 anchors={'.rodata':m['members'][0]['vma']} if prefix else {}
 for view in (ma,ge):
  rosec=next((k for k in ('.rdata','.rodata') if view.obj.sections.get(k)),None)
  if bool(rosec)!=bool(prefix) or (rosec and len(view.obj.sections[rosec])!=prefix):raise ValueError('genuine/maspsx data extent differs')
  if rosec:
   view.funcs['__owned_rodata']=(rosec,0,prefix)
   words,masked=A.resolve_tokens(view,'__owned_rodata',m['members'][0]['vma'],addresses.get,0x80080994,section_anchors=anchors)
   if masked:raise ValueError('unresolved owned-data relocation')
   resolved=struct.pack('<'+'I'*len(words),*words)
   if resolved!=data[:prefix]:raise ValueError('owned-data bytes differ')
   if view is ge:genuine.extend(resolved)
 for a in m['members']:
  sec,begin,end=ge.funcs[a['function']]
  if sec!='.text' or begin!=len(genuine)-prefix or end-begin!=a['size']-a.get('body_offset',0):raise ValueError('genuine layout/padding differs')
  words,masked=A.resolve_tokens(ge,a['function'],a['vma']+a.get('body_offset',0),addresses.get,0x80080994,section_anchors=anchors)
  if masked:raise ValueError('unresolved genuine relocation')
  genuine.extend(struct.pack('<'+'I'*len(words),*words))
 if len(ge.obj.sections['.text'])+prefix!=len(genuine) or genuine!=data:raise ValueError('unaccounted genuine bytes or resolved mismatch')
 (out/'genuine.bin').write_bytes(genuine)
 after=fingerprint(m,root)
 if before!=after or any(sha(substitutions[k])!=h for k,h in candidate_hashes.items()):raise ValueError('inputs changed during module build')
 receipt={'schema':SCHEMA,'module':m['key'],'fingerprint':before,'members':[a['id'] for a in m['members']],'physical':{'compile_edges':1,'functions':[a['function'] for a in m['members']],'payload':payload,'owned_data':m['owned_data'],'imports':m['imports']},'gate':{'result':'MATCH','foff':first['foff'],'vma':first['vma'],'bytes':len(data),'rebuilt_sha256':sha(binary),'retail_sha256':sha(out/'retail.bin'),'masked':0,'raw_substitution_bytes':0},'genuine':{'result':'MATCH','version':'2.79','whole_tu':True,'flags':['-q','-G0']+genuine_flags(m,root),'bytes':len(genuine),'masked':0,'sha256':sha(out/'genuine.bin')},'candidates':candidate_hashes,'candidate_paths':{k:str(Path(v).absolute()) for k,v in (substitutions or {}).items()}}
 receipt['artifacts']={n:sha(out/n) for n in ['module.s','sectioned.s','module.untrimmed.o','rodata_proof.json','module.o','module.ld','module.elf','module.bin','retail.bin','IN.S','OUT.OBJ','genuine.bin']};(out/'receipt.json').write_text(json.dumps(receipt,indent=2)+'\n')
 return receipt,binary

def project_segments(segments,build_dir,overlay,root=ROOT):
 """Called before ordinary row compilation. A single touched row rebuilds all siblings."""
 root=Path(root).absolute();family=overlay.split('_')[0];receipts=[]
 for m in load_modules(root):
  if m['container']!=family:continue
  hits=[(i,s,a) for i,s in enumerate(segments) for a in m['members'] if s.start<a['foff']+a['size'] and a['foff']<s.end]
  if not hits:continue
  substitutions={}
  for i,s,a in hits:
   if s.start!=a['foff'] or s.size!=a['size'] or s.kind!='c' or not s.match:raise ValueError('module member missing, raw, partial or multiply covered')
   if s.match.config!=m['recipe']['cfg']:
    # Gate-export labels may use the equivalent space spelling.
    if s.match.config!='2.7.2-cdk -G0':raise ValueError('per-row recipe move forbidden inside module')
   if Path(s.match.source).resolve()!=(root/a['source']).resolve():substitutions[a['source']]=str(s.match.source)
  receipt,binary=build(m,build_dir/'modules'/m['key'],root,substitutions);blob=binary.read_bytes()
  for i,s,a in hits:
   target=binary.parent/(a['function']+'.bin');offset=a['foff']-m['members'][0]['foff'];target.write_bytes(blob[offset:offset+a['size']]);segments[i]=dataclasses.replace(s,kind='rowbase',bytes_path=target,module_key=m['key'],section=f'.ovlseg_{s.index:04d}')
  receipts.append({'module':m['key'],'receipt':str(binary.parent/'receipt.json'),'receipt_sha256':sha(binary.parent/'receipt.json'),'fingerprint':receipt['fingerprint']['sha256'],'projected_rows':[a['id'] for _,_,a in hits]})
 return receipts

def verify_window_modules(receipts,root=ROOT):
 for projection in receipts:
  m=next(m for m in load_modules(root) if m['key']==projection['module'])
  p=Path(projection['receipt']);r=json.loads(p.read_text())
  if sha(p)!=projection['receipt_sha256'] or fingerprint(m,root)!=r['fingerprint']:
   raise ValueError('module inputs changed during window gate')
  for name,h in r['candidates'].items():
   if sha(r['candidate_paths'][name])!=h:raise ValueError('candidate changed during window gate')

def main():
 ap=argparse.ArgumentParser(description=__doc__);ap.add_argument('--root',type=Path,default=ROOT);ap.add_argument('--graph',action='store_true');ap.add_argument('--module');ap.add_argument('--out',type=Path);args=ap.parse_args()
 if args.graph:
  p=args.root/'ledger/splits/overlay_modules.build.json';p.parent.mkdir(parents=True,exist_ok=True);p.write_text(json.dumps(graph(args.root),indent=2)+'\n');print('graph',p)
 else:
  m=next(m for m in load_modules(args.root) if m['key']==args.module);r,b=build(m,args.out,args.root);print(json.dumps({'module':m['key'],'gate':r['gate'],'genuine':r['genuine']},indent=2))
if __name__=='__main__':main()
