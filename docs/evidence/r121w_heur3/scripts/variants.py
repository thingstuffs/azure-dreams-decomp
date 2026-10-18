from pathlib import Path
import collections,json,re,struct,sys
from replay import Probe,LANE,ROOT,G,mini,object_info,ws,sha

def main():
 P=Probe();allp=json.loads((LANE/'evidence/proven_donor_candidates.json').read_text());out=[]
 for p in sorted(allp,key=lambda x:-x['size']):
  c=p['container'];a=int(p['foff'],0);n=p['size'];v=int(p['base'],0)
  if n<24 or n>348:continue
  ep=P.entry(c,a,n,v)
  if not ep:continue
  r=P.byid[p['donor']];info=P.compile(r);target=ws(P.data(c,a,n));home=ws(P.data(c,r['foff'],n));relocs=info['rels'];mp={};pending=collections.defaultdict(list)
  for z in relocs:
   i=z['offset']//4;s=z['symbol'];t=z['type']
   if t==5:pending[s].append(i)
   elif t==6:
    for j in pending.pop(s,[]):
     addr=(((target[j]&65535)<<16)+((target[i]&65535)-(65536 if target[i]&32768 else 0)))&0xffffffff
     if s in mp and mp[s]!=addr:raise ValueError('incompatible source symbol')
     mp[s]=addr
   elif t==4:mp[s]=(v&0xf0000000)|((target[i]&0x3ffffff)<<2)
  source=(ROOT/'src'/c/Path(r['c_path']).name).read_text()
  source=re.sub(r'/\*.*?\*/|//[^\n]*','',source,flags=re.S)
  # The canonical preprocessor aliases the donor names. Recover the primary definition name.
  defs=re.findall(r'\bvoid\s+(\w+)\s*\([^;]*?\)\s*\{',source,re.S)
  if len(defs)!=1:continue
  old=defs[0];symbol=f'func_{v:08X}'
  aliases={}
  for ln in (ROOT/'config/names.tsv').read_text().splitlines():
   cols=ln.split('\t')
   if len(cols)>=3:aliases[cols[2]]=cols[1]
  source=re.sub(r'\b'+re.escape(old)+r'\b',symbol,source)
  # Symbol substitutions are simultaneous and use actual ELF sites.
  sub={}
  for s,addr in mp.items():
   m=re.fullmatch(r'(func|D)_([0-9A-F]{8})',s)
   if not m:continue
   new=f'{m[1]}_{addr:08X}';sub[s]=new
   for alias,canonical in aliases.items():
    if canonical==s:sub[alias]=new
  source=re.sub(r'\b(?:'+'|'.join(map(re.escape,sub))+r')\b',lambda m:sub[m[0]],source) if sub else source
  dif=[(i,x,y) for i,(x,y) in enumerate(zip(home,target)) if x!=y and i*4 not in {z['offset'] for z in relocs}]
  edits=[]
  for i,x,y in dif:
   if (x>>26)!=(y>>26) or x>>16!=y>>16:break
   ox=x&65535;ny=y&65535
   # These families differ only in one call mode and/or an immediate state value.
   if x>>26==9 and (x>>21&31)==0:
    if ox>=32768:ox-=65536
    if ny>=32768:ny-=65536
    edits.append((ox,ny))
   else:break
  else:
   if not edits:continue
   good=True
   for ox,ny in edits:
    pat=r'(?<![\w])(?:0[xX]'+f'{ox:X}'+r'|'+str(ox)+r')(?![\w])'
    # Restrict mode updates to the call's slot argument and state writes to the assignment value.
    if n in (72,104,92) and any((x>>16&31)==5 and x&65535==(ox&65535) for i,x,y in dif):
     pat=r'(?<=, )'+pat
    hits=list(re.finditer(pat,source,re.I))
    if len(hits)!=1:good=False;break
    m=hits[0];source=source[:m.start()]+('0x%X'%ny if ny>=0 else str(ny))+source[m.end():]
   if not good:continue
   # Clean comments are written for the new behavior, preserving the template's types and accesses.
   source=re.sub(r'/\*.*?\*/|//[^\n]*','',source,flags=re.S)
   mode=next((y&65535 for i,x,y in dif if (x>>16&31)==5),None)
   name=(f'configure_actor_slot_{mode}' if mode is not None else f'reset_actor_handler_{a:x}')
   if n not in (72,92,104,100):
    name=re.sub(r'[^a-z0-9_]','_',old.lower())+'_variant_'+f'{a:x}'
   if n==104:name+= '_and_render_state'
   if n==92:name+='_and_copy_global'
   source=source.strip()+'\n'
   od=LANE/'scratch/variants'/f'{c}_{a:x}';od.mkdir(parents=True,exist_ok=True);src=od/(symbol+'.c');src.write_text(source)
   result=dict(p,entry_evidence=ep,semantic_immediates=[dict(offset=i*4,before=x&65535,after=y&65535) for i,x,y in dif],alias=name,source=str(src.relative_to(LANE)),status='HOLD')
   try:
    m=G.MatchEntry(a,n,symbol,r['cfg'],src,'new-C',link_vram=v);seg=G.Segment(0,'c',a,a+n,v,'.text.'+symbol,symbol,m)
    obj=G.compile_c_segments([seg],od,overlay=c)[0];name2,raw,rels=object_info(obj)
    got=mini(obj,name2,v,n,od/'linked')
    if got!=P.data(c,a,n):raise ValueError('new semantic variant native replay differs')
    result.update(status='EXACT_NEW_C',source_sha256=sha(src),native_object_sha256=sha(obj),target_sha256=__import__('hashlib').sha256(got).hexdigest(),cfg=r['cfg'])
   except (ValueError,SystemExit) as e:result['reason']=str(e)
   out.append(result);print(c,hex(a),n,result['status'],result.get('reason',''),flush=True)
   (LANE/'evidence/semantic_variants.json').write_text(json.dumps(out,indent=1)+'\n')
 print('COUNTS',collections.Counter(x['status'] for x in out))

if __name__=='__main__':main()
