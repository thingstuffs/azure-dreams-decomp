"""Conservative family runner. Every staged row must be a complete donor-row twin.
No heuristic discovery result is a proof: ordinary compiler and full-window gates decide.
"""
import os,sys,json,re,struct,hashlib,subprocess,shutil,csv,collections,argparse,tempfile,functools,gzip
from pathlib import Path
from concurrent.futures import ThreadPoolExecutor
R=Path(__file__).resolve().parents[3];BASE=R
HOME_LANE=R/'work/native_lane/r121_sdk'
L=Path(os.environ.get('TWINS_LANE',HOME_LANE));PY=str(R/'.venv/bin/python')
WORKERS=int(os.environ.get('TWINS_WORKERS','8'))
os.environ['PYTHONDONTWRITEBYTECODE']='1';sys.dont_write_bytecode=True
os.environ['TMPDIR']=str(L/'tmp');tempfile.tempdir=str(L/'tmp')
sys.path.insert(0,str(R/'tools'))

def save(p,v):
 p=Path(p);p.parent.mkdir(parents=True,exist_ok=True)
 temporary=p.with_name(p.name+'.twins-tmp');temporary.write_text(json.dumps(v,indent=1)+'\n');temporary.replace(p)
def jl(p):return [json.loads(s) for s in Path(p).read_text().splitlines() if s and not s.startswith('#')]
def sha(p):return hashlib.sha256(Path(p).read_bytes()).hexdigest()
def command(args,cwd=R,log=None,timeout=900):
 p=subprocess.run(['nice','-n','15']+list(map(str,args)),cwd=cwd,capture_output=True,text=True,timeout=timeout)
 if log:Path(log).write_text(p.stdout+p.stderr)
 return p
LOW=(9,32,33,34,35,36,37,38,40,41,42,43,46)
WRITES=(8,9,10,11,12,13,14,32,33,34,35,36,37,38)
def references(ws):
 state={};out={};hi={}
 for i,w in enumerate(ws):
  op=w>>26;rs=w>>21&31;rt=w>>16&31;rd=w>>11&31;imm=w&65535;si=imm-(65536 if imm&32768 else 0)
  if op in (2,3):out[i]=dict(kind='jal' if op==3 else 'j',address=0x80000000|((w&0x3ffffff)<<2),hi=None)
  elif op==15:state[rt]=(i,imm<<16);continue
  elif op in LOW and rs in state:
   j,upper=state[rs];out[i]=dict(kind='absolute',address=(upper+si)&0xffffffff,hi=j);hi.setdefault(j,[]).append(i)
  if op in WRITES:state.pop(rt,None)
  if op==0 and (w&63) not in (8,12,13,17,19,24,25,26,27):state.pop(rd,None)
 return out,hi

def proof(a,b):
 if len(a)!=len(b):return None
 differences=[];needs_pairs=False
 for i,(x,y) in enumerate(zip(a,b)):
  if x==y:continue
  op=x>>26
  if op in (2,3):
   if y>>26!=op:return None
  elif x>>16!=y>>16 or op not in (15,)+LOW:return None
  else:needs_pairs=True
  differences.append((i,x,y))
 if not differences:return []
 if needs_pairs:ar,ah=references(a);br,bh=references(b)
 ds=[]
 for i,x,y in differences:
  op=x>>26
  if op in (2,3):ds.append(dict(word=i,kind='jal' if op==3 else 'j',before=hex(x),after=hex(y)));continue
  if op==15:
   paired=set(ah.get(i,[]))&set(bh.get(i,[]))
   if not any(0x80000000<=ar[k]['address']<0x82000000 and 0x80000000<=br[k]['address']<0x82000000 for k in paired):return None
  elif op in LOW:
   if i not in ar or i not in br or ar[i]['hi']!=br[i]['hi']:return None
   if not (0x80000000<=ar[i]['address']<0x82000000 and 0x80000000<=br[i]['address']<0x82000000):return None
  ds.append(dict(word=i,kind='lui' if op==15 else 'paired-lo16',before=hex(x),after=hex(y)))
 return ds

def mask(w):
 op=w>>26
 return w&0xfc000000 if op in (2,3) else w&0xffff0000 if op in (15,)+LOW else w
DEF=re.compile(r'^[ \t]*([A-Za-z_][A-Za-z0-9_ \*]*?)\b([A-Za-z_]\w*)\s*\(([^;{}]*)\)\s*\{',re.M)
SYM=re.compile(r'\b(?:func|D)_[0-9A-Fa-f]{8}\b')
def strip(s):return re.sub(r'/\*.*?\*/|//[^\n]*','',s,flags=re.S)
class World:
 def __init__(self):
  self.rows=[json.loads(line) for line in gzip.open(L/'state/base_rows.json.gz','rt') if line.strip()];self.byid={r['id']:r for r in self.rows}
  self.B={c:(R/f'work/disc/containers/{c.upper()}_{c.upper()}.BIN').read_bytes() for c in ('dungeon','town','main','ovmovie')}
  self.splits={c:jl(BASE/f'ledger/splits/{c}.jsonl') for c in self.B};self.alias={}
  for line in (R/'config/names.tsv').read_text().splitlines():
   p=line.split('\t')
   if len(p)>=3:
    try:self.alias[p[2]]=int(p[0],16)
    except ValueError:pass
  self.defs=collections.defaultdict(list);self.byrow={};self.text={};self.index=collections.defaultdict(list);self.definition_authorities={}
  for r in self.rows:
   c=r['container'];p=R/'src'/c/(r['id'].split('/')[-1]+'.c')
   if not p.is_file():continue
   t=p.read_text();self.text[r['id']]=t
   dd=[]
   for m in DEF.finditer(strip(t)):
    n=m[2];a=int(n[5:],16) if re.fullmatch(r'func_[\da-fA-F]{8}',n) else self.alias.get(n)
    d=dict(row=r['id'],source=str(p.relative_to(R)),name=n,definition=' '.join((m[1]+n+'('+m[3]+')').split()))
    if a is not None:self.defs[a].append(d)
    dd.append(d)
   identities={int(r[key][5:],16) for key in ('func','true_name') if r.get(key) and re.fullmatch(r'func_[\da-fA-F]{8}',r[key])}
   self.byrow[r['id']]=[d for d in dd if d['name'] in (r.get('func'),r.get('true_name')) or self.alias.get(d['name']) in identities] if c!='slus' else dd
   if not self.byrow[r['id']] and not r.get('true_name') and r.get('row_kind')!='data' and len(dd)==1 and re.fullmatch(r'func_[\da-fA-F]{8}',dd[0]['name']) and not dd[0]['definition'].startswith(('static ','inline ')):
    self.byrow[r['id']]=dd
    self.definition_authorities[r['id']]=dict(binding='sole-exported-definition-in-matched-C-row',row=r['id'],source=dd[0]['source'],source_sha256=sha(p),definition=dd[0]['definition'])
   if c in self.B and r.get('foff') is not None and r['size']>=8 and r['size']%4==0 and not r.get('row_kind')=='data':
    a=self.words(c,r['foff'],r['size']);self.index[tuple(mask(w) for w in a[:4])].append(r)
  from sdk_contracts import SDK
  self.sdk=SDK(self,BASE)
  self.module_headers={}
  for module in json.loads((BASE/'config/overlays/modules.json').read_text()).get('modules',[]):
   for member in module.get('members',[]):self.module_headers[member['id']]=module.get('headers',[])
  self.base_regions={c:jl(BASE/f'config/overlays/{c}.rowbase.jsonl') for c in self.B if (BASE/f'config/overlays/{c}.rowbase.jsonl').exists()}
 def source_link_vram(self,row):
  hits=[r for r in self.base_regions.get(row['container'],[]) if int(r['foff_start'],0)<=row['foff'] and row['foff']+row['size']<=int(r['foff_end'],0) and r.get('base_confidence')=='proven']
  region_vram=row['foff']+int(hits[0]['delta'],0) if len(hits)==1 else None
  named=int(row['true_name'][5:],16) if row.get('true_name') and re.fullmatch(r'func_[\da-fA-F]{8}',row['true_name']) else None
  if named is not None and region_vram is not None and named!=region_vram:return None
  return named if named is not None else region_vram
 def words(self,c,o,n):return struct.unpack('<%dI'%(n//4),self.B[c][o:o+n])
 def twins_at(self,c,o):
  if o<0 or o+8>len(self.B[c]):return []
  out=[];available=min(4,(len(self.B[c])-o)//4)
  head=self.words(c,o,available*4)
  # The index stores min(4, body_words) words. Eight- and twelve-byte
  # complete leaf bodies therefore require their own prefix lengths.
  for prefix in range(available,1,-1):
   for r in self.index.get(tuple(mask(w) for w in head[:prefix]),[]):
    n=r['size']
    if o+n>len(self.B[c]):continue
    pr=proof(self.words(r['container'],r['foff'],n),self.words(c,o,n))
    if pr is not None:out.append((r,pr))
  return out
 @functools.lru_cache(maxsize=None)
 def contract(self,c,addr,donor_start,donor_vram,extent):
  if addr in self.sdk.symbols:return self.sdk.get(addr)
  if donor_vram<=addr<donor_vram+extent:
   o=donor_start+addr-donor_vram
   exact=[r for r in self.rows if r['container']==c and r.get('foff')==o]
   twins=self.twins_at(c,o)
   for r in exact+[r for r,pr in sorted(twins,key=lambda t:-t[0]['size'])]:
    dd=self.byrow.get(r['id'],[])
    if len(dd)==1:return dict(dd[0],binding='local-complete-retail-twin',callee_foff=hex(o))
  ds=self.defs.get(addr,[])
  # Existing definitions provide ABI contracts; duplicate slot names must agree.
  if ds:
   ds=sorted(ds,key=lambda d: (not d['row'].startswith(c+'/'),d['row']))
   return dict(ds[0],binding='matched-definition-at-encoded-source-target')
  return None
 def flow_target_contract_proof(self,c,addr,start,vram,extent,contract):
  cr=self.byid.get(contract.get('row'))
  if not cr or cr['container'] not in self.B or cr.get('foff') is None or cr.get('row_kind')=='data' or contract.get('inherited_literal_replacements'):return None
  o=start+addr-vram;n=cr['size'];source_vram=self.source_link_vram(cr)
  if n<8 or n%4 or source_vram is None or not vram<=addr or o+n>start+extent:return None
  from flow_relocations import prove
  result=prove(self.words(cr['container'],cr['foff'],n),self.words(c,o,n),source_vram,addr)
  if result is None:return None
  return dict(binding='complete-target-callee-flow-retail-twin',row=cr['id'],foff=hex(o),bytes=n,
   differences=result[0],source_vram=source_vram,target_vram=addr,
   reaching_pairs=[dict(word=i,source=result[1][i],target=result[2][i]) for i in sorted(set(result[1])&set(result[2]))])
 def target_contract_proof(self,c,addr,start,vram,extent,contract,oldaddr=None,recorded=None):
  if recorded and recorded.get('binding')=='complete-target-callee-flow-retail-twin' and 'source_vram' in recorded:
   return self.flow_target_contract_proof(c,addr,start,vram,extent,contract)
  if contract.get('binding')=='psyq-sdk-matched-header':
   return self.sdk.proof(addr,oldaddr,contract) if not vram<=addr<vram+extent else None
  if not vram<=addr<vram+extent:
   if oldaddr is not None and oldaddr!=addr:return None
   return dict(binding='unchanged-resident-definition',row=contract['row'])
  cr=self.byid[contract['row']];o=start+addr-vram;n=cr['size']
  if cr['container'] not in self.B or cr.get('foff') is None:return None
  callee_words=list(self.words(cr['container'],cr['foff'],n))
  literal=contract.get('inherited_literal_replacements',[])
  if literal:
   if contract.get('inherited_container')!=c or contract.get('inherited_foff')!=o:return None
   for change in literal:
    if callee_words[change['word']]!=int(change['before'],0):return None
    callee_words[change['word']]=int(change['after'],0)
  pr=proof(callee_words,self.words(c,o,n))
  if literal and pr is not None:return dict(binding='complete-target-callee-literal-variant',row=cr['id'],foff=hex(o),bytes=n,
   differences=pr,literal_replacements=literal,inherited_row=contract['inherited_row'],inherited_source_sha256=contract['inherited_source_sha256'])
  if pr is not None:return dict(binding='complete-target-callee-retail-twin',row=cr['id'],foff=hex(o),bytes=n,differences=pr)
  inherited=contract.get('inherited_flow_relocation')
  if inherited and contract.get('inherited_container')==c and contract.get('inherited_foff')==o:
   from flow_relocations import prove
   result=prove(callee_words,self.words(c,o,n),inherited['source_vram'],addr)
   if result is not None:
    return dict(binding='complete-target-callee-flow-retail-twin',row=cr['id'],foff=hex(o),bytes=n,
     differences=result[0],inherited_row=contract['inherited_row'],inherited_source_sha256=contract['inherited_source_sha256'])
  # Some bank variants edit a callee while retaining its ABI. Accept only a
  # second matched COMPLETE body whose body-derived prototype agrees exactly.
  from contracts import declaration
  try:expected=declaration(contract,'callee')
  except ValueError:return None
  for twin,pr in self.twins_at(c,o):
   for definition in self.byrow.get(twin['id'],[]):
    try:actual=declaration(definition,'callee')
    except ValueError:continue
    if actual==expected:return dict(binding='complete-target-callee-variant-twin',row=twin['id'],foff=hex(o),bytes=twin['size'],differences=pr,definition=definition['definition'],derived_prototype=actual)
  return self.flow_target_contract_proof(c,addr,start,vram,extent,contract)
 def generate(self,r,c,o,n,v):
  a=self.words(r['container'],r['foff'],n);b=self.words(c,o,n);pr=proof(a,b)
  flow=None
  if pr is None and os.environ.get('TWINS_FLOW_RELOCATIONS')=='1':
   from flow_relocations import prove
   dd=self.byrow.get(r['id'],[])
   source_vram=int(r['true_name'][5:],16) if r.get('true_name') else int(dd[0]['name'][5:],16) if len(dd)==1 and re.fullmatch(r'func_[\dA-Fa-f]{8}',dd[0]['name']) else None
   if source_vram is not None:flow=prove(a,b,source_vram,v)
   if flow is not None:
    pr=flow[0];self.generation_flow=getattr(self,'generation_flow',{})
    self.generation_flow[(r['id'],c,o)]=dict(source_vram=source_vram,target_vram=v,
     reaching_pairs=[dict(word=i,source=flow[1][i],target=flow[2][i]) for i in sorted(set(flow[1])&set(flow[2]))])
  if pr is None:raise ValueError('nonrelocation word difference')
  ar,_=references(a);br,_=references(b);mp={}
  if flow is not None:
   for i in sorted(set(flow[1])&set(flow[2])):ar[i]=flow[1][i];br[i]=flow[2][i]
  for i,x in ar.items():
   if i not in br:continue
   old=x['address'];new=br[i]['address']
   if old in mp and mp[old]!=new:raise ValueError('ambiguous relocation mapping')
   mp[old]=new
  t=self.text[r['id']];bare=strip(t)
  from pin_census import sites_of
  if sites_of(t) or re.search(r'\b(?:ASM_\w+|NON_MATCHING|__asm__|asm|volatile)\b',bare):raise ValueError('template has pins/asm/volatile')
  if os.environ.get('TWINS_CONTINUE3_ITEM') is not None and re.search(r'\bgoto\b',bare):raise ValueError('template has goto: CONTINUE3 hold')
  if os.environ.get('TWINS_CONTINUE3_ITEM') in ('1','2'):
   from source_relocation import prepare
   t,edits=prepare(t,mp,os.environ.get('TWINS_ADDRESS_MODE','basic'))
   for header in reversed(self.module_headers.get(r['id'],[])):
    name=header.removeprefix('include/')
    if not re.search(r'#\s*include\s*"'+re.escape(name)+r'"',t):
     t='#include "'+name+'"\n'+t
     edits.append(dict(kind='retain-matched-module-header',source=header))
   self.generation_evidence=getattr(self,'generation_evidence',{})
   self.generation_evidence[(r['id'],c,o)]=edits
   bare=strip(t)
  dd=self.byrow[r['id']]
  if len(dd)!=1:raise ValueError('not singleton function definition')
  orig=dd[0]['name'];symbols={s:int(s.split('_')[1],16) for s in set(SYM.findall(t))}
  identifiers=set(re.findall(r'\b[A-Za-z_]\w*\b',bare))
  symbols.update({s:self.alias[s] for s in identifiers if s in self.alias})
  # Preserve the historical spelling rule for any non-C linker aliases.
  symbols.update({s:a for s,a in self.alias.items() if not re.fullmatch(r'[A-Za-z_]\w*',s)
    and re.search(r'\b'+re.escape(s)+r'\b',bare)})
  changes={}
  direct_addresses={ref['address'] for ref in ar.values() if ref['kind'] in ('j','jal')}
  for s,addr in symbols.items():
   if s==orig:continue
   new=mp.get(addr)
   if new is None:
    near=sorted((k-addr,val-k) for k,val in mp.items() if 0<=k-addr<0x200 and (k>>16)==(addr>>16))
    if near:new=addr+near[0][1]
   if new is not None and new!=addr:
    function=s.startswith('func_') or (addr in direct_addresses and addr in self.defs and
      re.search(r'\b'+re.escape(s)+r'\s*\(',bare))
    changes[s]=('func_' if function else 'D_')+f'{new:08X}'
  t=SYM.sub(lambda m:f'func_{v:08X}' if m[0]==orig else changes.get(m[0],m[0]),t)
  # Rewrite named direct callees in this translation unit. Shared headers
  # keep their original declarations; bind() derives a new local declaration
  # from the complete matched callee body when one is required.
  for s,val in changes.items():
   if val.startswith('func_') and not re.fullmatch(r'func_[\da-fA-F]{8}',s):
    t=re.sub(r'\b'+re.escape(s)+r'\b',val,t)
  if not re.fullmatch(r'func_[0-9A-Fa-f]{8}',orig):t=re.sub(r'\b'+re.escape(orig)+r'\b',f'func_{v:08X}',t)
  t=re.sub(r'0x[89aA][0-9a-fA-F]{7}\b',lambda m:hex(mp[int(m[0],16)]) if int(m[0],16) in mp else m[0],t)
  # Aliases and symbolic declarations from shared includes move together.
  prefix='/* Relink of matched '+r['id']+'; every changed retail word is a paired relocation. */\n'
  if orig in self.alias:prefix+=f'#define {orig} func_{v:08X}\n'
  # Function addresses retain the matched source's existing declaration,
  # including declarations supplied by shared headers. They assert no call
  # target or runtime reachability. Direct callees instead get body-backed
  # local prototypes from bind(), so do not rewrite their shared declarations.
  prefix+=''.join(f'#define {s} {val}\n' for s,val in sorted(changes.items())
    if not val.startswith('func_') or symbols[s] not in direct_addresses)
  return prefix+t,pr,mp

def load_families():return json.loads((L/'evidence/families.json').read_text())
def bank_plan(w,W,donor):
 c=w['container'];start=w['start'];end=w['end'];v=w['vram'];extent=end-start
 # The preceding current-link bank is a source of independently registered complete extents.
 donors=[r for r in W.rows if r['container']==c and donor<=r.get('foff',-1)<donor+extent and r['foff']+r['size']<=donor+extent and r.get('kind')=='overlay']
 if not donors:return [],[dict(reason='no matched complete donor rows at preceding 0x6000 bank')]
 # Link base follows from matched donor row true identities, corroborated by production truebase window.
 dvs={int(r['true_name'][5:],16)-(r['foff']-donor) for r in donors if r.get('true_name')}
 if len(dvs)!=1:return [],[dict(reason='donor true-base identity is not constant',deltas=list(dvs))]
 dv=dvs.pop();out=[];holds=[]
 for r in donors:
  o=start+r['foff']-donor;n=r['size'];f=f'func_{o+0x7ffe0000:08X}'
  if any(s['foff']<o+n and o<s['foff']+s['size'] for s in W.splits[c]):
   holds.append(dict(foff=hex(o),size=n,reason='existing split extent: no overlapping append'));continue
  try:t,pr,mp=W.generate(r,c,o,n,v+o-start)
  except ValueError as e:holds.append(dict(foff=hex(o),size=n,template=r['id'],reason=str(e)));continue
  contracts=[];unresolved=[]
  for i,x in references(W.words(c,donor+o-start,n))[0].items():
   body_start=dv+o-start
   if x['kind']!='jal' and not (x['kind']=='j' and not body_start<=x['address']<body_start+n):continue
   hit=W.contract(c,x['address'],donor,dv,extent)
   target=references(W.words(c,o,n))[0][i]['address']
   target_proof=W.target_contract_proof(c,target,start,v,extent,hit,x['address']) if hit else None
   item=dict(call_foff=hex(o+i*4),source_callee=hex(x['address']),encoded_callee=hex(target),contract=hit,target_body_proof=target_proof)
   contracts.append(item)
   if not hit or not target_proof:unresolved.append(item['encoded_callee'])
  if unresolved:
   holds.append(dict(foff=hex(o),size=n,template=r['id'],reason='unresolved matched callee bodies',callees=unresolved));continue
  from contracts import bind
  try:t=bind(t,contracts)
  except ValueError as e:
   holds.append(dict(foff=hex(o),size=n,template=r['id'],reason=str(e)));continue
  p=L/'evidence/candidates'/c/(f+'.c');p.parent.mkdir(parents=True,exist_ok=True);p.write_text(t)
  out.append(dict(container=c,func=f,id=c+'/'+f,foff=o,size=n,true_name=f'func_{v+o-start:08X}',delta=v-start,cfg=r['cfg'],cell=r['cell'],flags=r['flags'],kind='overlay',c_path=f'overlays/{c}/first_pass_matched/{f}.c',template=r['id'],template_foff=r['foff'],donor_bank=donor,donor_vram=dv,window=w['window'],src=str(p.relative_to(L)),relocation_proof=pr,paired_addresses={hex(k):hex(val) for k,val in mp.items() if k!=val},contracts=contracts))
 return out,holds

def plan(f,W):
 if f['kind']=='single-window':
  from single_plan import runner_plan
  out,holds=runner_plan(f,W)
  save(L/'evidence'/f['id']/'plan.json',out);save(L/'evidence'/f['id']/'holds.json',holds)
  print(f['id'],'anchored candidates',len(out),sum(r['size'] for r in out),'holds',len(holds),collections.Counter(h['reason'] for h in holds),flush=True)
  return out
 out=[];holds=[]
 for w in f['banks']:
  rr,hh=bank_plan(w,W,f['banks'][0]['start']-0x6000);out.extend(rr);holds.extend(dict(window=w['window'],**h) for h in hh)
 save(L/'evidence'/f['id']/'plan.json',out);save(L/'evidence'/f['id']/'holds.json',holds)
 print(f['id'],'candidates',len(out),sum(r['size'] for r in out),'holds',len(holds),collections.Counter(h['reason'] for h in holds),flush=True)
 return out

def split_record(r,result='M2C_FAIL'):
 record=dict(func_vram=r['func'],true_name=r['true_name'],vram=int(r['func'][5:],16),true_vram=r['foff']+r['delta'],foff=r['foff'],size=r['size'],result=result,config=r['cfg'],c_path=r['c_path'],gate_config='config/overlays/'+r['window'],gate_verified=result=='MATCH',instances=1,base_confidence='proven',load_base=r['delta'],evidence='docs/evidence/r121_sdk.md',clone_template=r['template'],clone_binding_mode='address-relocation')
 if r.get('mirror_split_ledgers'):record['mirror_split_ledgers']=r['mirror_split_ledgers']
 return record
def export():
 from mirror_splits import sync
 sync(R)
 p=command([PY,'tools/row_db.py','export','build_ovl']);assert p.returncode==0,p.stderr

def raw_context(r,od,assembly,previous):
 # Recover switch context using the disassembler's own jtbl symbols and the
 # existing bank window. Assembly and C remain unedited generator output.
 t=Path(assembly).read_text();addrs=[int(x,16) for x in re.findall(r'jtbl_([0-9A-Fa-f]{8})',t)]
 cfg=(R/'config/overlays'/r['window']).read_text()
 lo=int(re.search(r'file_start:\s*(0x[0-9a-fA-F]+)',cfg)[1],16);hi=int(re.search(r'file_end:\s*(0x[0-9a-fA-F]+)',cfg)[1],16)
 header=[a-r['delta'] for a in addrs if lo-0x1000<=a-r['delta']<lo]
 if not header:return previous
 start=min(header);context=od/'bank_context';context.mkdir(exist_ok=True);csvpath=context/'splits.csv'
 csvpath.write_text(f"offset,vram,.rodata\n{start:X},{start+r['delta']:X},bank_header\noffset,vram,.text\n{lo:X},{lo+r['delta']:X},bank_text\n{hi:X},{hi+r['delta']:X},.end\n")
 cmd=[PY,'-m','spimdisasm','singleFileDisasm',str(R/f"work/disc/containers/{r['container'].upper()}_{r['container'].upper()}.BIN"),str(context),'--file-splits',str(csvpath),'--endian','little','--arch-level','MIPS1','--instr-category','r3000gte','--compiler','GCC','--no-nuke-pointers','--no-filter-low-addresses','--no-filter-high-addresses']
 p=command(cmd,log=context/'disasm.log')
 if p.returncode:return previous
 cmd2=[PY,str(R/'toolchain/genuine/m2c/m2c.py'),'--target','mipsel-gcc-c','--valid-syntax','-f',r['true_name'],str(context/'bank_text.text.s'),str(context/'bank_header.rodata.s')]
 p=command(cmd2,log=context/'m2c.log');raw=context/'raw.c';raw.write_text('#include "common.h"\n#include "m2c_compat.h"\n\n'+p.stdout)
 return dict(id=r['id'],ok=p.returncode==0 and bool(p.stdout.strip()) and 'Decompilation failure' not in p.stdout,raw=str(raw.relative_to(L)),sha256=sha(raw),disasm_command=cmd,m2c_command=cmd2,function_only_attempt=previous)

def raw_one(r):
 od=L/'evidence/first_pass'/r['container']/r['func'];od.mkdir(parents=True,exist_ok=True)
 cmd=[PY,'-m','spimdisasm','singleFileDisasm',str(R/f"work/disc/containers/{r['container'].upper()}_{r['container'].upper()}.BIN"),str(od),'--start',hex(r['foff']),'--end',hex(r['foff']+r['size']),'--vram',hex(r['foff']+r['delta']),'--endian','little','--arch-level','MIPS1','--instr-category','r3000gte','--compiler','GCC','--no-nuke-pointers','--no-filter-low-addresses','--no-filter-high-addresses']
 p=command(cmd,log=od/'disasm.log');asm=list(od.glob('*.text.s'))
 if p.returncode or len(asm)!=1:return dict(id=r['id'],ok=False,reason='disasm failed',disasm_command=cmd)
 cmd2=[PY,str(R/'toolchain/genuine/m2c/m2c.py'),'--target','mipsel-gcc-c','--valid-syntax',str(asm[0])]
 p=command(cmd2,log=od/'m2c.log');raw=od/'raw.c';raw.write_text('#include "common.h"\n#include "m2c_compat.h"\n\n'+p.stdout)
 result=dict(id=r['id'],ok=p.returncode==0 and bool(p.stdout.strip()) and 'Decompilation failure' not in p.stdout,raw=str(raw.relative_to(L)),sha256=sha(raw),disasm_command=cmd,m2c_command=cmd2)
 return result if result['ok'] else raw_context(r,od,asm[0],result)

def run(f,W):
 from verify import verify_overlay
 d=L/'evidence'/f['id'];d.mkdir(exist_ok=True)
 if (d/'result.json').exists():
  cached=json.loads((d/'result.json').read_text())
  for b in cached['banks']:
   for r in b['rows']:
    for sub,key in [('src','source_sha256'),('raw','raw_sha256')]:assert sha(R/sub/r['container']/(r['func']+'.c'))==r[key],'completed source drift'
  for args in [[PY,'tools/registry.py'],[PY,'tools/gate/overlay_module_gate.py','--root','.','--graph'],[PY,'tools/row_db.py','check']]:
   p=command(args,log=d/('resume_'+Path(args[1]).stem+'.log'));assert p.returncode==0,p.stdout+p.stderr
  print(f['id'],'already processed; hashes and normal checks pass',flush=True);return
 prior_holds=json.loads((d/'holds.json').read_text()) if (d/'checkpoint.json').exists() and (d/'holds.json').exists() else []
 rs=plan(f,W);by=collections.defaultdict(list)
 for r in rs:by[r['window']].append(r)
 holds=json.loads((d/'holds.json').read_text());results=json.loads((d/'checkpoint.json').read_text()) if (d/'checkpoint.json').exists() else []
 holds=list({json.dumps(h,sort_keys=True):h for h in holds+prior_holds}.values())
 completed={b['window'] for b in results}
 for b in results:
  for r in b['rows']:
   for sub,key in [('src','source_sha256'),('raw','raw_sha256')]:assert sha(R/sub/r['container']/(r['func']+'.c'))==r[key],'checkpoint source drift'

 for w in f['banks']:
  window=w['window'];rr=by[window];bd=d/window.removesuffix('.overlay.yaml');bd.mkdir(exist_ok=True)
  if window in completed:continue
  if not rr:
   results.append(dict(window=window,status='HOLD',reason='no admitted candidate plan',rows=[]));continue
  c=w['container'];sp=R/f'ledger/splits/{c}.jsonl';rb=R/f'config/overlays/{c}.rowbase.jsonl'
  snapshot=bd/'active_snapshot.json.gz'
  if snapshot.exists():
   state=json.load(gzip.open(snapshot,'rt'));sp.write_text(state['split']);rb.write_text(state['rowbase'])
   for r in state.get('candidates',rr):
    for sub in ['src','raw']:(R/sub/c/(r['func']+'.c')).unlink(missing_ok=True)
   export()
  live=jl(sp);available=[]
  for r in rr:
   if any(s['foff']<r['foff']+r['size'] and r['foff']<s['foff']+s['size'] for s in live):holds.append(dict(window=window,foff=hex(r['foff']),size=r['size'],reason='extent already occupied by an earlier admitted family'))
   else:
    from object_relocations import split_preflight
    missing=split_preflight(r)
    if missing:holds.append(dict(window=window,foff=hex(r['foff']),size=r['size'],reason='production split source lacks the exact C extent',failures=missing))
    else:available.append(r)
  rr=available
  original=sp.read_bytes();rb_before=rb.read_bytes();created=[]
  with gzip.open(snapshot,'wt') as fp:json.dump(dict(split=original.decode(),rowbase=rb_before.decode(),candidates=[dict(container=r['container'],func=r['func']) for r in rr]),fp)

  with sp.open('a') as fp:
   for r in rr:fp.write(json.dumps(split_record(r))+'\n')
  export()
  def score(r):
   v=verify_overlay(r,L/r['src']);print(r['func'],'src',v.get('exact'),v.get('total'),v.get('err'),flush=True);return dict(id=r['id'],score=v)
  with ThreadPoolExecutor(max_workers=WORKERS) as pool:scores=list(pool.map(score,rr))
  save(bd/'source_scores.json',scores);sc={x['id']:x['score'] for x in scores};kept=[r for r in rr if sc[r['id']].get('exact') and sc[r['id']].get('total')==0]
  for r in rr:
   if r not in kept:holds.append(dict(window=window,foff=hex(r['foff']),size=r['size'],reason='source score not exact',score=sc[r['id']]))
  with ThreadPoolExecutor(max_workers=WORKERS) as pool:raws=list(pool.map(raw_one,kept))
  save(bd/'first_pass.json',raws);raw={x['id']:x for x in raws}
  for r in list(kept):
   if not raw[r['id']]['ok']:
    holds.append(dict(window=window,foff=hex(r['foff']),size=r['size'],reason='m2c first pass failed',record=raw[r['id']]));kept.remove(r)
  sp.write_bytes(original)
  for r in kept:
   r.update(source_sha256=sha(L/r['src']),raw_sha256=raw[r['id']]['sha256'],retail_sha256=hashlib.sha256(W.B[c][r['foff']:r['foff']+r['size']]).hexdigest(),source_score=sc[r['id']],first_pass=raw[r['id']])
  # Keep new candidates provisional and outside first_pass_matched while the
  # normal promotion hook checks every previously landed member in the region.
  with sp.open('a') as fp:
   for r in kept:fp.write(json.dumps(split_record(r))+'\n')
  export()
  promotes=[];ok=bool(kept);reason='no source/raw pairs survived'
  regions=jl(rb)
  grouped=collections.defaultdict(list)
  for r in kept:
   reg=next((x for x in regions if int(x['foff_start'],0)<=r['foff']<int(x['foff_end'],0)),None)
   if reg is None:ok=False;reason='no existing rowbase region';break
   grouped[reg['region']].append(r)
  if ok:
   for region,members in grouped.items():
    r=min(members,key=lambda r:r['size'])
    cmd=[PY,'tools/rowbase.py','promote','--family',c,'--func',r['func'],'--candidate',str(L/r['src']),'--config',r['cfg']]
    p=command(cmd,cwd=R/'build_ovl',log=bd/('promote_'+region+'.log'));promotes.append(dict(region=region,command=cmd,returncode=p.returncode,stdout=p.stdout,stderr=p.stderr))
    if p.returncode:ok=False;reason='rowbase promotion refused: '+p.stderr[-350:];break
  save(bd/'rowbase_promotions.json',promotes)
  gates=[]
  if ok:
   for r in kept:
    for sub,source in [('src',L/r['src']),('raw',L/raw[r['id']]['raw'])]:
     target=R/sub/c/(r['func']+'.c');assert not target.exists(),target;shutil.copyfile(source,target);created.append(target)
   sp.write_bytes(original)
   with sp.open('a') as fp:
    for r in kept:fp.write(json.dumps(split_record(r,'MATCH'))+'\n')
   export()
   from common import covering_windows
   windows=sorted({window}|{w[0] for r in kept for w in covering_windows(c,r['foff'],r['size'])})
   for name in windows:
    cmd=[PY,'tools/overlay_local_gate.py','--config','config/overlays/'+name,'--clean']
    p=command(cmd,cwd=R/'build_ovl',log=bd/('gate_'+name+'.log'),timeout=3600)
    good=p.returncode==0 and any(line.startswith('MATCH') for line in p.stdout.splitlines())
    gates.append(dict(window=name,ok=good,returncode=p.returncode,command=cmd,stdout=p.stdout[-1800:],stderr=p.stderr[-1800:]))
    print(name,'GATE',good,flush=True)
    if not good:ok=False;reason='production window gate failed: '+name;break
  if ok:
   from object_relocations import row_failures
   rejected=[(r,row_failures(r)) for r in kept];rejected=[(r,bad) for r,bad in rejected if bad]
   if rejected:
    for r,bad in rejected:
     holds.append(dict(window=window,foff=hex(r['foff']),size=r['size'],reason='differing word lacks production ELF relocation',failures=bad));kept.remove(r)
     for sub in ['src','raw']:(R/sub/c/(r['func']+'.c')).unlink()
    sp.write_bytes(original)
    with sp.open('a') as fp:
     for r in kept:fp.write(json.dumps(split_record(r,'MATCH'))+'\n')
    export();ok=bool(kept);reason='no rows survived production ELF relocation audit'
    if ok:
     for g in gates:
      p=command(g['command'],cwd=R/'build_ovl',log=bd/('native_relocation_gate_'+g['window']+'.log'),timeout=3600)
      g.update(ok=p.returncode==0 and any(s.startswith('MATCH') for s in p.stdout.splitlines()),returncode=p.returncode,stdout=p.stdout[-1800:],stderr=p.stderr[-1800:]);ok&=g['ok']
      if not ok:reason='production window gate failed after native relocation audit';break
  save(bd/'window_gates.json',gates)
  if ok:
   def raw_score(r):return dict(id=r['id'],score=verify_overlay(r,R/'raw'/c/(r['func']+'.c')))
   with ThreadPoolExecutor(max_workers=WORKERS) as pool:rawsc=list(pool.map(raw_score,kept))
   save(bd/'raw_scores.json',rawsc);rscores={x['id']:x['score'] for x in rawsc}
   for r in kept:r['raw_score']=rscores[r['id']]
   results.append(dict(window=window,status='MATCH',rows=kept,gates=gates,promotions=promotes))
  else:
   sp.write_bytes(original);rb.write_bytes(rb_before)
   for p in created:p.unlink(missing_ok=True)
   export();results.append(dict(window=window,status='HOLD',reason=reason,rows=[],attempted_rows=len(kept),gates=gates,promotions=promotes))
  save(d/'checkpoint.json',results);save(d/'holds.json',holds);snapshot.unlink(missing_ok=True)
  print('BANK',window,results[-1]['status'],len(results[-1]['rows']),results[-1].get('reason',''),flush=True)
 save(d/'result.json',dict(family=f['id'],banks=results,holds=holds))
 # Generate the normal registry and physical graph from the resulting admitted set.
 for cmd in [[PY,'tools/registry.py'],[PY,'tools/gate/overlay_module_gate.py','--root','.','--graph'],[PY,'tools/row_db.py','check']]:
  p=command(cmd,log=d/(Path(cmd[1]).stem+'.log'));assert p.returncode==0,p.stdout+p.stderr
 print('FAMILY',f['id'],'complete',sum(len(b['rows']) for b in results),'rows',flush=True)
 count=sum((L/'evidence'/x['id']/'result.json').exists() for x in load_families())
 if not os.environ.get('TWINS_NO_PACKAGE') and count in (2,5,8,11,14,17):
  p=command([PY,L/'scripts/package.py'],cwd=L);print(p.stdout,p.stderr,flush=True);assert p.returncode==0

def main():
 p=argparse.ArgumentParser();p.add_argument('action',choices=['plan','run']);p.add_argument('families',nargs='+');a=p.parse_args();W=World()
 for key in a.families:
  f=next(f for f in load_families() if f['id']==key)
  if a.action=='plan':plan(f,W)
  else:run(f,W)
if __name__=='__main__':main()
