from pathlib import Path
import collections,json,struct,sys
from survey import masked,get_parts,LANE,ROOT
rows,parts,segments=get_parts();B={c:(ROOT/'work/disc/containers'/n).read_bytes() for c,n in dict(main='MAIN_MAIN.BIN',town='TOWN_TOWN.BIN',dungeon='DUNGEON_DUNGEON.BIN').items()}
def words(c,a,n):return struct.unpack_from('<'+'I'*(n//4),B[c],a)
index=collections.defaultdict(list)
for r in rows:
 c=r['container'];a=r.get('foff');n=r['size']
 if c not in B or a is None or n%4 or n<32 or r.get('source_row') or r.get('row_kind')=='data':continue
 index[c,tuple(map(masked,words(c,a,min(n,16))))].append(r)
q=[r for r in json.load(open(LANE/'evidence/input_reconciliation.json')) if r['queue']=='handoff_code' and r['remaining']]
out=[]
for r in q:
 c=r['container'];start=int(r['foff'],0);end=start+r['size']
 for a in range(start-12,start+4,4):
  key=c,tuple(map(masked,words(c,a,16)))
  for donor in index.get(key,[]):
   n=donor['size']
   if not end-12<=a+n<=end+12:continue
   if tuple(map(masked,words(c,a,n)))!=tuple(map(masked,words(c,donor['foff'],n))):continue
   if any(x<a+n and a<y for x,y in parts[c]['in_c']):continue
   out.append(dict(queue='handoff_complete_body',container=c,foff=hex(a),size=n,handoff_foff=r['foff'],handoff_size=r['size'],donor=donor['id'],donor_foff=donor['foff'],diff_words=sum(x!=y for x,y in zip(words(c,a,n),words(c,donor['foff'],n)))))
(LANE/'evidence/prefix_donor_leads.json').write_text(json.dumps(out,indent=1)+'\n')
for r in sorted(out,key=lambda x:-x['size'])[:35]:print(r)
print('leads',len(out),'unique sites',len({(r['container'],r['foff'],r['size']) for r in out}))
