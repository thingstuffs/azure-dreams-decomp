from pathlib import Path
import collections,concurrent.futures,hashlib,json,os,re,shutil,subprocess,sys,datetime
from replay import Probe,LANE,ROOT,VIEW,G,ws,sha
sys.path.insert(0,str(ROOT/'tools'))
import common,registry,verify
EVIDENCE='docs/evidence/r121w_heur3/receipts.json'

def freeze(rel):
 p=ROOT/rel;q=LANE/'scratch/preimage'/rel
 if not q.exists() and p.exists():q.parent.mkdir(parents=True,exist_ok=True);shutil.copyfile(p,q)
def write(rel,text):
 freeze(rel);p=ROOT/rel;p.parent.mkdir(parents=True,exist_ok=True);p.write_text(text)
def append(rel,r):
 freeze(rel)
 with (ROOT/rel).open('a') as f:f.write(json.dumps(r,separators=(',',':'))+'\n')
def relpath(p):return str(p.relative_to(ROOT))
def cmd(argv):
 p=subprocess.run(list(map(str,argv)),cwd=ROOT,capture_output=True,text=True)
 return p

def audit_contracts(P,p):
 c=p['container'];a=int(p['foff'],0);v=int(p['base'],0);n=p['size'];r=P.byid[p['donor']];iv=P.compile(r)['vma']
 sc=P.context(c,r['foff'],r['size'],iv);tc=P.context(c,a,n,v);proof=[]
 for i,(sw,tw) in enumerate(zip(ws(P.data(c,r['foff'],n)),ws(P.data(c,a,n)))):
  if sw>>26!=3:continue
  old=(iv&0xf0000000)|((sw&0x3ffffff)<<2);new=(v&0xf0000000)|((tw&0x3ffffff)<<2)
  if old==new and (sc==tc or not tc[0]+tc[2]<=new<tc[1]+tc[2]):
   proof.append(dict(offset=i*4,source=hex(old),target=hex(new),authority='unchanged inherited donor call outside aliased target image' if sc!=tc else 'same physical matched call image'));continue
  oldoff=old-sc[2];newoff=new-tc[2]
  if not(sc[0]<=oldoff<sc[1] and tc[0]<=newoff<tc[1]):raise ValueError('callee lies outside independently bounded source or target context')
  callees=[rr for rr in P.rows if rr['container']==c and rr.get('foff')==oldoff and not rr.get('row_kind')=='data']
  if len(callees)!=1:raise ValueError('no complete matched source callee at '+hex(old))
  cr=callees[0];bs=P.data(c,oldoff,cr['size']);bt=P.data(c,newoff,cr['size'])
  if bs!=bt:
   # Every differing callee word must be an actual native relocation with unchanged opcode/register lanes.
   ci=P.compile(cr);offs={x['offset'] for x in ci['rels']}
   for j,(x,y) in enumerate(zip(ws(bs),ws(bt))):
    if x==y:continue
    if j*4 not in offs or (x>>26 not in(2,3) and x>>16!=y>>16) or x>>26!=y>>26:raise ValueError('callee complete-body native twin proof fails')
  proof.append(dict(offset=i*4,source=hex(old),target=hex(new),authority='complete registered source callee and full target twin',row=cr['id'],source_foff=hex(oldoff),target_foff=hex(newoff),size=cr['size'],source_sha256=sha(ROOT/'src'/c/Path(cr['c_path']).name),source_body_sha256=hashlib.sha256(bs).hexdigest(),target_body_sha256=hashlib.sha256(bt).hexdigest()))
 return proof

def raw_one(p):
 c=p['container'];a=int(p['foff'],0);v=int(p['base'],0);n=p['size'];od=LANE/'scratch/raw'/f'{c}_{a:x}';od.mkdir(parents=True,exist_ok=True)
 command=[str(ROOT/'.venv/bin/python'),'-m','spimdisasm','singleFileDisasm',str(ROOT/'work/disc/containers'/('TOWN_TOWN.BIN' if c=='town' else 'MAIN_MAIN.BIN')),str(od),'--start',hex(a),'--end',hex(a+n),'--vram',hex(v),'--endian','little','--arch-level','MIPS1','--instr-category','r3000gte','--compiler','GCC','--no-nuke-pointers','--no-filter-low-addresses','--no-filter-high-addresses']
 d=cmd(command);(od/'disasm.log').write_text(d.stdout+d.stderr)
 asm=list(od.glob('*.text.s'))
 if d.returncode or len(asm)!=1:raise ValueError('genuine first-pass disassembly failed')
 command2=[str(ROOT/'.venv/bin/python'),str(ROOT/'toolchain/genuine/m2c/m2c.py'),'--target','mipsel-gcc-c','--valid-syntax',str(asm[0])]
 m=cmd(command2);(od/'m2c.log').write_text(m.stderr);(od/'m2c_stdout.c').write_text(m.stdout)
 if m.returncode or not m.stdout.strip() or 'Decompilation failure' in m.stdout:raise ValueError('genuine m2c first pass failed')
 raw=od/'raw.c';raw.write_text('#include "common.h"\n#include "m2c_compat.h"\n\n'+m.stdout)
 return dict(raw=str(raw.relative_to(LANE)),raw_sha256=sha(raw),m2c_stdout_sha256=sha(od/'m2c_stdout.c'),generator_sha256=sha(ROOT/'toolchain/genuine/m2c/m2c.py'),disassembler='spimdisasm singleFileDisasm, MIPS1, r3000gte, GCC, little endian',generator_options=['--target','mipsel-gcc-c','--valid-syntax'])

def main():
 more=len(sys.argv)>1 and sys.argv[1]=='more'
 if (LANE/'evidence/staged.json').exists() and not more:raise SystemExit('staging already complete; refusing duplicate mutation')
 previous=json.loads((LANE/'evidence/staged.json').read_text()) if more else []
 P=Probe();candidate_file='extra_variants.json' if more else 'semantic_variants.json'
 ps=[p for p in json.loads((LANE/'evidence'/candidate_file).read_text()) if p['status']=='EXACT_NEW_C' and (p['container'],p['foff']) not in {(r['container'],r['foff']) for r in previous}];accepted=[];holds=[]
 for p in ps:
  try:
   p['call_contracts']=audit_contracts(P,p)
   symbol=f'func_{int(p["base"],0):08X}'
   if re.search(r'\t'+symbol+r'\t',(ROOT/'config/names.tsv').read_text()):raise ValueError('true-address name already names another scene function; region-specific readable naming needed')
   accepted.append(p)
  except ValueError as e:holds.append(dict(p,reason=str(e)))
 print('contracts',len(accepted),'accepted',len(holds),'held',flush=True)
 hp=LANE/'evidence/contract_holds.json'
 prior_holds=json.loads(hp.read_text()) if more else []
 hp.write_text(json.dumps(prior_holds+holds,indent=1)+'\n')
 with concurrent.futures.ThreadPoolExecutor(max_workers=4) as pool:
  for p,r in zip(accepted,pool.map(raw_one,accepted)):p.update(r)
 oldids=set(P.byid);names=(ROOT/'config/names.tsv').read_text();used_names=set()
 splits={c:common.read_jsonl(ROOT/f'ledger/splits/{c}.jsonl') for c in ['town','main']}
 for p in accepted:
  c=p['container'];a=int(p['foff'],0);v=int(p['base'],0);n=p['size'];ident=f'func_{0x80000000+a:08X}'
  if c+'/'+ident in oldids:raise ValueError('new row identity conflict')
  if any(sp.get('foff') is not None and sp['foff']<a+n and a<sp['foff']+sp['size'] and not sp.get('rerun') for sp in splits[c]):raise ValueError('live split overlap')
  wins=common.covering_windows(c,a,n)
  if not wins:raise ValueError('no production window')
  wins.sort(key=lambda w:w[2]-w[1]);window='config/overlays/'+wins[0][0]
  symbol=f'func_{v:08X}';alias=p['alias']
  if alias in used_names or re.search(r'\t'+re.escape(alias)+r'\t',names):alias+='_'+f'{a:x}'
  if re.search(r'\t'+symbol+r'\t',names):raise ValueError('new alias true symbol is already named')
  used_names.add(alias);names+=f'0x{v:08X}\t{symbol}\t{alias}\t{EVIDENCE}: complete native C, callback entry and inherited matched interface\n'
  src=(LANE/p['source']).read_text();src=re.sub(r'\b'+symbol+r'\b',alias,src)
  src='/* '+alias.replace('_',' ').capitalize()+'. */\n'+src
  write(f'src/{c}/{ident}.c',src);write(f'raw/{c}/{ident}.c',(LANE/p['raw']).read_text())
  rec=dict(func_vram=ident,true_name=symbol,vram=int(ident[5:],16),true_vram=v,foff=a,size=n,result='MATCH',config=p['cfg'],c_path=f'overlays/{c}/first_pass_matched/{ident}.c',gate_config=window,gate_verified=True,instances=1,base_confidence='proven',load_base=v-a,evidence=EVIDENCE)
  append(f'ledger/splits/{c}.jsonl',rec)
  p.update(id=c+'/'+ident,func=ident,true_name=symbol,alias=alias,gate_config=window,covering_windows=['config/overlays/'+w[0] for w in wins],clean_source=f'src/{c}/{ident}.c',raw_source=f'raw/{c}/{ident}.c',clean_sha256=sha(ROOT/f'src/{c}/{ident}.c'))
 write('config/names.tsv',names)
 # Refresh registry with its normal derivation while preserving the exact previous prefix.
 freeze('ledger/rows.jsonl');old=(ROOT/'ledger/rows.jsonl').read_bytes();generated=registry.overlay_rows()+registry.slus_rows();new={r['id']:r for r in generated}
 assert all(new.get(r['id'])==r for r in P.rows),'old registry facts changed'
 write('ledger/rows.jsonl',old.decode()+''.join(json.dumps(r,separators=(',',':'))+'\n' for r in generated if r['id'] not in oldids))
 cmd1=cmd(['bash','tools/build/mk_ovl_root.sh']);(LANE/'evidence/view_refresh.log').write_text((cmd1.stdout+cmd1.stderr).replace(str(ROOT),'<root>'))
 if cmd1.returncode:raise ValueError('view refresh failed')
 (LANE/'evidence/staged.json').write_text(json.dumps(previous+accepted,indent=1)+'\n')
 print('STAGED',len(accepted),sum(p['size'] for p in accepted),'bytes',flush=True)

def scores():
 ps=json.loads((LANE/'evidence/staged.json').read_text());rr={r['id']:r for r in common.rows()};out=[]
 def one(p):
  r=rr[p['id']];s=verify.verify_overlay(r,ROOT/p['clean_source'],include_root=ROOT/'include');raw=verify.verify_overlay(r,ROOT/p['raw_source'],include_root=ROOT/'include')
  return dict(id=p['id'],source=s,raw=raw,source_sha256=p['clean_sha256'],raw_sha256=p['raw_sha256'])
 with concurrent.futures.ThreadPoolExecutor(max_workers=4) as pool:
  for x in pool.map(one,ps):
   print(x['id'],'source',x['source'].get('exact'),'raw',x['raw'].get('exact'),x['raw'].get('status'),flush=True);out.append(x)
   (LANE/'evidence/scores.json').write_text(json.dumps(out,indent=1)+'\n')
 if not all(x['source']['exact'] for x in out):raise ValueError('some canonical source scores are not exact')
 print('SOURCE SCORES EXACT',len(out),flush=True)

if __name__=='__main__':
 if len(sys.argv)>1 and sys.argv[1]=='scores':scores()
 else:main()
