from pathlib import Path
import collections,json,re,sys
from replay import Probe,LANE,ROOT,G,mini,object_info,ws,sha
P=Probe();out=[]
for p in json.loads((LANE/'evidence/proven_donor_candidates.json').read_text()):
 c=p['container'];a=int(p['foff'],0);n=p['size'];v=int(p['base'],0)
 if c!='town' or n not in (100,112,212,220) or a==0x47260:continue
 entry=P.entry(c,a,n,v)
 if not entry:continue
 r=P.byid[p['donor']];ci=P.compile(r);target=ws(P.data(c,a,n));source=(ROOT/'src'/c/Path(r['c_path']).name).read_text()
 source=re.sub(r'/\*.*?\*/|//[^\n]*','',source,flags=re.S);defs=re.findall(r'\bvoid\s+(\w+)\s*\([^;]*?\)\s*\{',source,re.S)
 if len(defs)!=1:continue
 source=re.sub(r'\b'+defs[0]+r'\b',f'func_{v:08X}',source)
 aliases={}
 for ln in (ROOT/'config/names.tsv').read_text().splitlines():
  z=ln.split('\t')
  if len(z)>=3:aliases[z[2]]=z[1]
 mp={};pending=collections.defaultdict(list)
 for z in ci['rels']:
  i=z['offset']//4;s=z['symbol'];t=z['type']
  if t==5:pending[s].append(i)
  elif t==6:
   for j in pending.pop(s,[]):mp[s]=(((target[j]&65535)<<16)+(target[i]&65535)-(65536 if target[i]&32768 else 0))&0xffffffff
  elif t==4:mp[s]=(v&0xf0000000)|((target[i]&0x3ffffff)<<2)
 sub={}
 for s,value in mp.items():
  m=re.fullmatch(r'(func|D)_([0-9A-F]{8})',s)
  if not m:continue
  sub[s]=f'{m[1]}_{value:08X}'
  for alias,canonical in aliases.items():
   if canonical==s:sub[alias]=sub[s]
 if sub:source=re.sub(r'\b(?:'+'|'.join(map(re.escape,sub))+r')\b',lambda m:sub[m[0]],source)
 if n==100:
  off=target[6]&65535;val=target[18]&65535;field=target[19]&65535
  source=source.replace('objectData + 8',f'objectData + 0x{off:X}').replace('+ 0x6C',f'+ 0x{field:X}').replace('= 0x20;',f'= 0x{val:X};')
  name=f'reset_object_handler_field_{field:x}_value_{val:x}'
 elif n==112:
  source=source.replace('* 128 + 88','* 128 - 48').replace('* 16 + 136','* 16 + 22');name='arrange_ten_objects_in_menu_columns'
 elif n==212:
  source=source.replace('pad00[0x10]','pad00[0x1C]').replace('register State *state','State *state').replace('clear_mask','flag_bits');name='update_alternate_menu_page_bounds'
 elif n==220:
  source=source.replace('#include "records/Rec_func_800AF254_arg1.h"','''typedef struct MenuDisplay {
    void *unk_00;
    u8 pad04[0x58];
    struct { void *as_pv; } unk_A8;
} MenuDisplay;''').replace('Rec_func_800AF254_arg1','MenuDisplay')
  source=source.replace('u8 pad_00[0x18];\n    s32 unk_18;','u8 pad_00[0x34];\n    s32 unk_18;');name='set_alternate_menu_entry_coordinates'
 source=source.strip()+'\n';od=LANE/'scratch/extra_variants'/f'{c}_{a:x}';od.mkdir(parents=True,exist_ok=True);src=od/f'func_{v:08X}.c';src.write_text(source)
 result=dict(p,entry_evidence=entry,alias=name,source=str(src.relative_to(LANE)),status='HOLD')
 try:
  m=G.MatchEntry(a,n,f'func_{v:08X}',r['cfg'],src,'new-C',link_vram=v);seg=G.Segment(0,'c',a,a+n,v,'.text.'+m.func,m.func,m)
  obj=G.compile_c_segments([seg],od,overlay=c)[0];sym,raw,rels=object_info(obj);b=mini(obj,sym,v,n,od/'linked')
  if b!=P.data(c,a,n):raise ValueError('new layout variant native replay differs')
  result.update(status='EXACT_NEW_C',source_sha256=sha(src),native_object_sha256=sha(obj),target_sha256=__import__('hashlib').sha256(b).hexdigest(),cfg=r['cfg'])
 except (ValueError,SystemExit) as e:result['reason']=str(e)
 out.append(result);print(hex(a),n,result['status'],result.get('reason',''),flush=True)
 (LANE/'evidence/extra_variants.json').write_text(json.dumps(out,indent=1)+'\n')
