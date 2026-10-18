"""Native-object proposals only. Retail bytes and objects remain under ignored scratch/."""
from pathlib import Path
import collections,dataclasses,hashlib,json,os,re,shutil,struct,subprocess,sys
LANE=Path(__file__).resolve().parents[1];ROOT=LANE.parents[2];VIEW=ROOT/'build_ovl'
sys.path[:0]=[str(VIEW/'tools'),str(ROOT/'tools')]
import overlay_local_gate as G, rowbase,linklist

def sha(p):return hashlib.sha256(p.read_bytes()).hexdigest()
def ws(b):return list(struct.unpack('<'+'I'*(len(b)//4),b))
def signed(x):return (x&65535)-(65536 if x&32768 else 0)
def run(cmd):
 p=subprocess.run(list(map(str,cmd)),cwd=VIEW,capture_output=True,text=True)
 if p.returncode:raise ValueError(p.stderr.strip()[-1500:])
 return p.stdout

def mini(obj,symbol,vma,n,out,overrides=None):
 m=G.MatchEntry(0,n,symbol,'',obj,'probe',link_vram=vma)
 seg=G.Segment(0,'c',0,n,vma,'.text.'+symbol,symbol,m)
 symbols=[]
 if overrides:
  p=out.with_suffix('.symbols');p.write_text(''.join(f'{k} = 0x{v:08X};\n' for k,v in sorted(overrides.items())));symbols=[p]
 G.write_linker_script([seg],[obj],0x80080994,symbols,out.with_suffix('.ld'),obj_paths={0:obj})
 run(['mipsel-linux-gnu-ld','-EL','--no-check-sections','-T',out.with_suffix('.ld'),'-o',out.with_suffix('.elf'),obj])
 run(['mipsel-linux-gnu-objcopy','-O','binary',out.with_suffix('.elf'),out.with_suffix('.bin')])
 b=out.with_suffix('.bin').read_bytes()
 if len(b)<n or any(b[n:]):raise ValueError(f'object length {len(b)} does not cover {n} with zero alignment only')
 return b[:n]

def object_info(obj):
 b=obj.read_bytes()
 if b[:6]!=b'\x7fELF\x01\x01':raise ValueError('not ELF32 little endian')
 off=struct.unpack_from('<I',b,0x20)[0];ent,num,ss=struct.unpack_from('<HHH',b,0x2e)
 sec=[struct.unpack_from('<10I',b,off+i*ent) for i in range(num)]
 strings=b[sec[ss][4]:sec[ss][4]+sec[ss][5]]
 def name(z):return strings[z[0]:].split(b'\0',1)[0].decode()
 sects=[(i,z) for i,z in enumerate(sec) if name(z).startswith('.text.') and z[5]]
 if len(sects)!=1:raise ValueError('native object has multiple text sections')
 idx,z=sects[0];rr=[]
 for rel in sec:
  if rel[1]!=9 or rel[7]!=idx:continue
  syms=sec[rel[6]];st=sec[syms[6]];snames=b[st[4]:st[4]+st[5]]
  for pos in range(rel[4],rel[4]+rel[5],rel[9]):
   loc,info=struct.unpack_from('<II',b,pos)
   sym=struct.unpack_from('<IIIBBH',b,syms[4]+(info>>8)*syms[9])
   rr.append(dict(offset=loc,type=info&255,symbol=snames[sym[0]:].split(b'\0',1)[0].decode(),shndx=sym[5]))
 return name(z)[len('.text.'):],b[z[4]:z[4]+z[5]],rr

class Probe:
 def __init__(self):
  self.rows=[json.loads(s) for s in (ROOT/'ledger/rows.jsonl').read_text().splitlines() if s];self.byid={r['id']:r for r in self.rows}
  self.regions={c:rowbase._records(c) for c in ['main','town','dungeon','ovmovie']}
  self.B={c:(ROOT/'work/disc/containers'/n).read_bytes() for c,n in dict(main='MAIN_MAIN.BIN',town='TOWN_TOWN.BIN',dungeon='DUNGEON_DUNGEON.BIN',ovmovie='OVMOVIE.BIN').items()}
  self.images=linklist.load(ROOT)[0];self.compiled={}
  self.windows={}
  for c in self.B:
   for p in (ROOT/'config/overlays').glob(c+'*.overlay.yaml'):
    t=p.read_text();fs=re.search(r'file_start:\s*(0x\w+)',t);fe=re.search(r'file_end:\s*(0x\w+)',t)
    if fs and fe:self.windows[p.name]=(c,int(fs[1],0),int(fe[1],0))
 def data(self,c,a,n):return self.B[c][a:a+n]
 def context(self,c,a,n,v):
  imgs=[im for im in self.images.values() if im['container']==c and im['vma'] is not None and im['foff']<=a and a+n<=im['foff']+im['size'] and im['vma']-im['foff']==v-a]
  imgs.sort(key=lambda im:-im['size'])
  for im in imgs:
   lo,hi=im['foff'],im['foff']+im['size'];d=v-a
   if all(r['delta']==d for r in self.regions[c] if r['rec'].get('base_confidence')=='proven' and r['start']<hi and r['end']>lo):return lo,hi,d,im['image']
  r=next((r for r in self.regions[c] if r['start']<=a and a+n<=r['end'] and r['delta']==v-a),None)
  if r:return r['start'],r['end'],r['delta'],r['rec']['region']
  raise ValueError('no independently bounded load context')
 def entry(self,c,a,n,v):
  lo,hi,d,authority=self.context(c,a,n,v);proof=[]
  # Only independently registered C instructions establish call entry witnesses.
  for r in self.rows:
   if r['container']!=c or r.get('foff') is None or r.get('row_kind')=='data':continue
   s=r['foff'];e=s+r['size']
   if not lo<=s<e<=hi or s==a:continue
   for i,w in enumerate(ws(self.data(c,s,r['size']))):
    if w>>26==3 and ((v&0xf0000000)|((w&0x3ffffff)<<2))==v:proof.append(dict(kind='matched-C-jal',row=r['id'],foff=hex(s+i*4),context=authority))
  # Complete adjacent pointer-table entry, with a code pointer on both sides, in the same image.
  pattern=struct.pack('<I',v);b=self.B[c];pos=b.find(pattern,lo,hi)
  while pos>=0:
   if pos%4==0 and not a<=pos<a+n and pos>=lo+4 and pos+8<=hi:
    left,right=struct.unpack_from('<I',b,pos-4)[0],struct.unpack_from('<I',b,pos+4)[0]
    if all(lo+d<=p<hi+d and p%4==0 for p in (left,right)):
     proof.append(dict(kind='interior-code-pointer-table',foff=hex(pos),context=authority))
   pos=b.find(pattern,pos+1,hi)
  return proof
 def compile(self,r):
  if r['id'] in self.compiled:
   x=self.compiled[r['id']]
   if isinstance(x,str):raise ValueError(x)
   return x
  out=LANE/'scratch/native'/r['container']/r['func'];out.mkdir(parents=True,exist_ok=True)
  try:
   src=ROOT/'src'/r['container']/Path(r['c_path']).name
   v=rowbase.link_vram(r['container'],r['foff'],int((r.get('true_name') or r['func'])[5:],16),proven_only=True)
   symbol=f'func_{v:08X}'
   m=G.MatchEntry(r['foff'],r['size'],symbol,r['cfg'],src,'home',link_vram=v)
   seg=G.Segment(0,'c',r['foff'],r['foff']+r['size'],v,'.text.'+symbol,symbol,m)
   objs=G.compile_c_segments([seg],out,overlay=r['container']);obj=objs[0]
   name,raw,rels=object_info(obj)
   if name!=symbol:raise ValueError('native definition does not carry the home true address')
   data=mini(obj,name,v,r['size'],out/'home')
   if data!=self.data(r['container'],r['foff'],r['size']):raise ValueError('home standalone native replay differs')
   info=dict(obj=obj,name=name,raw=raw,rels=rels,vma=v,sha256=sha(obj),source_sha256=sha(src),size=r['size'])
   self.compiled[r['id']]=info;return info
  except (ValueError,SystemExit,OSError) as e:
   self.compiled[r['id']]=str(e);raise ValueError(str(e))
 def proposal(self,p):
  c=p['container'];a=int(p['foff'],0);n=p['size'];v=int(p['base'],0);r=self.byid[p['donor']]
  entry=self.entry(c,a,n,v)
  if not entry:raise ValueError('complete twin lacks independent matched caller or pointer-table entry')
  info=self.compile(r);target=ws(self.data(c,a,n));raw=ws(info['raw']);home=ws(self.data(c,r['foff'],n));rels=info['rels']
  if len(raw)*4<n:raise ValueError('native text too short')
  offsets={z['offset'] for z in rels};diff=[i*4 for i,(x,y) in enumerate(zip(home,target)) if x!=y]
  if any(i not in offsets for i in diff):raise ValueError('retail difference lacks native ELF relocation')
  vals=collections.defaultdict(list);pending=collections.defaultdict(list);proved=[]
  for z in rels:
   i=z['offset']//4;t=z['type'];s=z['symbol']
   if z['offset']>=n:continue
   if t==4:
    value=(((v&0xf0000000)|((target[i]&0x3ffffff)<<2))-((raw[i]&0x3ffffff)<<2))&0xffffffff
    vals[s].append(value);proved.append(dict(offset=i*4,type=t,symbol=s,address=hex(value)))
   elif t==5:pending[s].append(i)
   elif t==6:
    if not pending[s]:raise ValueError('LO16 without pending HI16')
    for j in pending.pop(s):
     value=(((target[j]&65535)<<16)+signed(target[i])-(((raw[j]&65535)<<16)+signed(raw[i])))&0xffffffff
     vals[s].append(value);proved.extend([dict(offset=j*4,type=5,symbol=s,address=hex(value)),dict(offset=i*4,type=6,symbol=s,address=hex(value))])
   elif t==2:vals[s].append((target[i]-raw[i])&0xffffffff)
   else:raise ValueError('unsupported native ELF relocation type '+str(t))
  if pending:raise ValueError('unpaired native HI16')
  if any(len(set(vs))!=1 for vs in vals.values()):raise ValueError('one native symbol requires incompatible target addresses')
  overrides={k:vs[0] for k,vs in vals.items()}
  bindings={}
  for k,new in overrides.items():
   m=re.fullmatch(r'(func|D)_([0-9A-F]{8})',k)
   if not m:raise ValueError('native symbol is not address-bindable: '+k)
   old=int(m[2],16)
   if old==info['vma']:
    if new!=v:raise ValueError('home self reference conflicts with target entry')
   elif old in bindings and bindings[old]!=new:raise ValueError('native address alias binding conflict')
   else:bindings[old]=new
  # Replay the exact native object with address assignments only.
  od=LANE/'scratch/replay'/c/f'{a:x}_{n:x}';od.mkdir(parents=True,exist_ok=True)
  b=mini(info['obj'],info['name'],v,n,od/'target',overrides)
  if b!=self.data(c,a,n):raise ValueError('unmasked native replay differs despite relocation constraints')
  return dict(p,entry_evidence=entry,bindings={hex(k):hex(v) for k,v in bindings.items()},native_relocations=proved,home_native_sha256=info['sha256'],source_sha256=info['source_sha256'],target_sha256=hashlib.sha256(b).hexdigest(),status='EXACT_NATIVE_REPLAY')

def main():
 P=Probe();ps=json.loads((LANE/'evidence/proven_donor_candidates.json').read_text());out=[]
 # Prefer largest complete candidates, then work toward tiny leaves.
 for p in sorted(ps,key=lambda r:-r['size']):
  try:r=P.proposal(p)
  except ValueError as e:r=dict(p,status='HOLD',reason=str(e))
  out.append(r)
  print(r['container'],r['foff'],r['size'],r['status'],r.get('reason',''),flush=True)
  (LANE/'evidence/native_replay.json').write_text(json.dumps(out,indent=1)+'\n')
 print('COUNTS',collections.Counter(r['status'] for r in out),flush=True)

if __name__=='__main__':main()
