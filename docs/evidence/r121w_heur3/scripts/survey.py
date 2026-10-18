from pathlib import Path
import collections,csv,hashlib,json,re,sys,struct
LANE=Path(__file__).resolve().parents[1];ROOT=LANE.parents[2]
sys.path.insert(0,str(ROOT/'tools'))
import coverage as cv

def write_tsv(path,rs,fields):
 with path.open('w') as f:
  w=csv.DictWriter(f,fields,delimiter='\t',lineterminator='\n');w.writeheader();w.writerows(rs)

def get_parts():
 regs=cv.records(ROOT/'ledger/coverage_regions.jsonl');rows=cv.records(ROOT/'ledger/rows.jsonl');ins=cv.records(ROOT/'ledger/instances.jsonl')
 latest={}
 for r in regs:latest[(r['container'],r['foff'],r['size'],r['category'])]=r
 regs=[r for r in latest.values() if r.get('active',True)]
 latest={}
 for r in ins:latest[(r['container'],r['foff'],r['size'])]=r
 blocked={(r['container'],r['foff'],r['size']) for r in regs if r['category']=='instance_excluded'}
 ins=[r for r in latest.values() if r.get('result')=='proven' and (r['container'],r['foff'],r['size']) not in blocked]
 parts={};segments={}
 for c in ['main','town','dungeon','ovmovie']:
  cats=collections.defaultdict(list)
  for r in regs:
   if r['container']==c:cats[r['category']].append(cv.extent(r))
  C=cv.merge([cv.extent(r) for r in rows if r['container']==c and r.get('foff') is not None and (r.get('func') or '').startswith('func_')])
  data=cv.merge(cats['data_excluded']+[cv.extent(r) for r in rows if r['container']==c and r.get('foff') is not None and not (r.get('func') or '').startswith('func_')])
  cop=cv.subtract([cv.extent(r) for r in ins if r['container']==c],C+data)
  ss=[];ds=[];spans=[]
  for key in [c]+(['dungeon_engine'] if c=='dungeon' else []):
   for sp in cv.records(ROOT/f'ledger/splits/{key}.jsonl'):
    if sp.get('foff') is None:continue
    e=cv.extent(sp)
    if sp.get('data_segment') or sp.get('result')=='data':ds.append(e);continue
    if sp.get('result')=='MERGE_FAIL':continue
    if sp.get('result') in ('CFAIL','M2C_FAIL') and sp['size']>8192:continue
    ss.append(e);spans.append(sp)
  data=cv.merge(data+ds)
  # All outstanding small split rows here lie in registered windows.
  raw=cv.subtract(ss,C+data+cop+cats['sdk_asm'])
  occ=cv.merge(C+cop+raw); p={'in_c':C,'copies':cop,'split':raw,'data':data}
  for cat in ['unported','sdk_asm','estimated_code']:
   p[cat]=cv.subtract(cats[cat],occ+data);occ=cv.merge(occ+p[cat])
  parts[c]=p;segments[c]=spans
 return rows,parts,segments

def masked(w):
 op=w>>26
 if op in (2,3):return w&0xfc000000
 if op in (9,13,15,32,33,35,36,37,40,41,43):return w&0xffff0000
 return w

def main():
 if (LANE/'inventory.tsv').exists():raise SystemExit('inventory is frozen; start a new incremental lane and base for a new survey')
 rows,parts,segments=get_parts(); inv=[]
 for c,p in parts.items():
  print(c,{k:cv.size(v) for k,v in p.items()})
  for cat in ['estimated_code','split','unported']:
   for a,b in p[cat]:inv.append(dict(queue='status_'+cat,container=c,foff=hex(a),size=b-a))
 write_tsv(LANE/'inventory.tsv',inv,['queue','container','foff','size'])
 current=[]
 for fn in ['holds2','handoff_code','next']:
  for i,r in enumerate(csv.DictReader((LANE/f'refs/{fn}.tsv').open(),delimiter='\t')):
   if not r.get('foff'):continue
   c=r['container'];a=int(r['foff'],0);n=int(r.get('bytes',r.get('size',0)));b=a+n
   if fn=='next' and 'terminal' in r['status']:continue
   if fn=='handoff_code' and r['status']=='delivered C':continue
   if fn=='next' and r['item'] in ('C','2'):pass
   remain=cv.subtract([[a,b]],parts.get(c,{}).get('in_c',[]))
   current.append(dict(queue=fn,item=i,container=c,foff=hex(a),size=n,current_c=n-cv.size(remain),remaining=cv.size(remain),residuals=remain,reason=r.get('reason',r.get('donor_review',r.get('status',''))),evidence=r.get('evidence',''),base=r.get('base','')))
 (LANE/'evidence/input_reconciliation.json').write_text(json.dumps(current,indent=1)+'\n')
 # Retail bytes remain scratch-only. No disassembly is emitted by this survey.
 files={'main':'MAIN_MAIN.BIN','town':'TOWN_TOWN.BIN','dungeon':'DUNGEON_DUNGEON.BIN','ovmovie':'OVMOVIE.BIN'}
 blobs={c:(ROOT/'work/disc/containers'/n).read_bytes() for c,n in files.items()}
 bins={c:list(struct.unpack('<'+'I'*(len(b)//4),b[:len(b)//4*4])) for c,b in blobs.items()}
 index=collections.defaultdict(list);stats=collections.Counter();donors={}
 for r in rows:
  c=r['container'];n=r['size'];a=r.get('foff')
  if c not in bins or a is None or a%4 or n%4 or n<8 or r.get('source_row') or r.get('row_kind')=='data':continue
  src=ROOT/'src'/c/Path(r['c_path']).name
  if not src.is_file():continue
  s=src.read_text()
  if 'Relink of' in s or re.search(r'^#define\s+\w+\s+(?:func|D)_',s,re.M):continue
  ws=bins[c][a//4:(a+n)//4];ms=tuple(map(masked,ws));debt=','.join(x for x,pat in [('volatile',r'\bvolatile\b'),('asm',r'\b(?:asm|__asm__)\s*\('),('goto',r'\bgoto\b'),('pin',r'ASM_(?:REG|KEEP|USE|SET)')] if re.search(pat,s))
  donor=dict(row=r,mask=ms,words=ws,debt=debt,src=str(src.relative_to(ROOT)))
  donors[r['id']]=donor;index[(c,ms[:min(4,len(ms))])].append(donor)
 targets={}
 for r in inv:
  c=r['container'];a=int(r['foff'],0);b=a+r['size']
  targets[(c,a,b)]=r['queue']
 for r in current:
  if r['queue']=='next':continue
  for a,b in r['residuals']:targets.setdefault((r['container'],a,b),r['queue'])
 leads=[]
 for (c,a,b),queue in targets.items():
  if c not in bins:continue
  for off in range((a+3)//4*4,b,4):
   ws=bins[c][off//4:off//4+4];key=(c,tuple(map(masked,ws)))
   cand=index.get(key,[])
   # Tiny donors have their own shorter lookup.
   cand=cand+index.get((c,key[1][:2]),[])+index.get((c,key[1][:3]),[])
   for d in cand:
    n=d['row']['size'];ts=bins[c][off//4:(off+n)//4]
    if len(ts)!=len(d['mask']) or tuple(map(masked,ts))!=d['mask']:continue
    if off+n>b:continue
    dif=[i*4 for i,(x,y) in enumerate(zip(d['words'],ts)) if x!=y]
    leads.append(dict(queue=queue,container=c,span=hex(a),span_size=b-a,foff=hex(off),size=n,donor=d['row']['id'],donor_foff=d['row']['foff'],debt=d['debt'],diff_words=len(dif),diff_offsets=dif))
 (LANE/'scratch/donor_leads.json').write_text(json.dumps(leads,indent=1)+'\n')
 print('inventory',len(inv),sum(r['size'] for r in inv),'donors',len(donors),'leads',len(leads))
 for r in sorted(leads,key=lambda r:-r['size'])[:45]:print({k:v for k,v in r.items() if k!='diff_offsets'})
 print('uncovered input bytes',[(q,sum(r['remaining'] for r in current if r['queue']==q)) for q in ['holds2','handoff_code','next']])

if __name__=='__main__':main()
