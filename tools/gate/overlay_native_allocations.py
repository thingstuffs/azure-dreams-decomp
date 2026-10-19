"""Strict native objects with separated text, literal strings and writable words.

One compiler stream, natural order within each allocation, all emitted bytes
accounted for. Only zero GNU section-end alignment padding may be removed.
"""
import ast,hashlib,json,re,struct,sys,shutil,tempfile,os,dataclasses
from pathlib import Path
import overlay_switch_allocations as X
MODEL='separated-literal-allocations-v1'
def switches(m):return X.enabled(m)
def enabled(m):return m.get('allocation_model')==MODEL or switches(m)
def spans(m):return [(a['foff'],a['foff']+a['size']) for a in m['allocations']]
def offset(m,foff,size):
 total=0
 for a in sorted(m['allocations'],key=lambda a:a['foff']):
  if a['foff']<=foff and foff+size<=a['foff']+a['size']:return total+foff-a['foff']
  total+=a['size']
 raise ValueError('projection outside an owned allocation')
def literal_words(text):
 values=[]
 for word in text.split(','):
  if not word.strip():continue
  if not re.fullmatch(r'\s*(?:0[xX][0-9a-fA-F]+|[0-9]+)[uUlL]*\s*',word):raise ValueError('nonliteral word initializer')
  value=int(re.sub('[uUlL]+$','',word.strip()),0)
  if not 0<=value<=0xffffffff:raise ValueError('word initializer outside u32')
  values.append(value)
 return struct.pack('<'+'I'*len(values),*values)
def slot_literal(slot,root):
 p=Path(slot['source'])
 if p.is_absolute() or '..' in p.parts:raise ValueError('unsafe storage source')
 text=(root/p).read_text();text=re.sub(r'/\*.*?\*/|//[^\n]*','',text,flags=re.S)
 name=re.escape(slot['symbol']);kind=slot['kind']
 if kind=='typed_string':
  found=re.findall(r'\bstatic\s+const\s+char\s+'+name+r'\s*\[\s*\]\s*=\s*("(?:\\.|[^"\\])*")\s*;',text)
  if len(found)!=1:raise ValueError('string ownership declaration differs')
  data=ast.literal_eval(found[0]).encode('latin1')+b'\0'
  if b'\0' in data[:-1]:raise ValueError('embedded NUL in typed string')
 elif kind=='u32_words':
  found=re.findall(r'\bstatic\s+u32\s+'+name+r'\s*\[\s*([0-9]+)\s*\]\s*=\s*\{([^{}]*)\}\s*;',text)
  if len(found)!=1:raise ValueError('word-array ownership declaration differs')
  data=literal_words(found[0][1])
  if len(data)!=4*int(found[0][0]):raise ValueError('word-array initializer extent differs')
 elif kind=='u32_record':
  found=re.findall(r'\bstatic\s+struct\s+(\w+)\s+'+name+r'\s*=\s*\{([^{}]*)\}\s*;',text)
  if len(found)!=1:raise ValueError('record ownership declaration differs')
  record=re.findall(r'\bstruct\s+'+re.escape(found[0][0])+r'\s*\{([^{}]*)\}\s*;',text)
  if len(record)!=1 or not re.fullmatch(r'(?:\s*u32\s+\w+\s*;)+\s*',record[0]):raise ValueError('record is not a plain u32 record')
  data=literal_words(found[0][1])
  if len(data)!=4*len(re.findall(r'\bu32\b',record[0])):raise ValueError('record initializer extent differs')
 elif kind=='device_pointer':
  found=re.findall(r'\bstatic\s+(?:s32|u32)\s*\*\s*'+name+r'\s*=\s*\((?:s32|u32)\s*\*\)\s*(0x[0-9a-fA-F]+)\s*;',text)
  if len(found)!=1:raise ValueError('device-pointer ownership declaration differs')
  address=int(found[0],16)
  if not 0x1f801000<=address<0x1f802000 or address%4:raise ValueError('pointer is outside aligned PSX hardware registers')
  data=struct.pack('<I',address)
 else:raise ValueError('unsupported literal allocation kind')
 if len(data)!=slot['size']:raise ValueError('literal slot extent differs')
 return data
def validate(m,root=None,region=None):
 if switches(m):return X.validate(m,root,region)
 if not enabled(m) or m.get('owned_data') or m.get('data_members') or any(a.get('body_offset') for a in m['members']):raise ValueError('mixed/unsupported separated allocation model')
 allocations=m['allocations']
 if not allocations or len({a['section'] for a in allocations})!=len(allocations):raise ValueError('duplicate or absent allocation')
 for i,(lo,hi) in enumerate(sorted(spans(m))):
  if lo>=hi or i and lo<sorted(spans(m))[i-1][1]:raise ValueError('allocation overlap/empty extent')
 text=[a for a in allocations if a['section']=='.text.*']
 if len(text)!=1:raise ValueError('one natural text allocation required')
 code=text[0];members=m['members']
 if code['foff']!=members[0]['foff'] or code['vma']!=members[0]['vma'] or code['size']!=sum(a['size'] for a in members):raise ValueError('text allocation differs from complete cohort')
 if any(a['foff']!=code['foff']+sum(b['size'] for b in members[:i]) or a['vma']!=code['vma']+a['foff']-code['foff'] for i,a in enumerate(members)):raise ValueError('text order/placement differs')
 for a in allocations:
  if a['vma']-a['foff']!=code['vma']-code['foff'] or a['link_alignment']!=4 or a['vma']%4:raise ValueError('allocation load map/alignment differs')
  if region and not int(region['foff_start'],0)<=a['foff']<a['foff']+a['size']<=int(region['foff_end'],0):raise ValueError('allocation outside proven resident region')
  if a['section']=='.text.*':continue
  if a['section'] not in ('.data','.rodata') or not a['slots']:raise ValueError('unsupported storage section')
  cursor=0;names=set()
  for slot in a['slots']:
   if slot['symbol'] in names or slot['offset']!=(cursor+3)&~3:raise ValueError('slot order/alignment differs')
   names.add(slot['symbol'])
   if slot['kind']=='typed_string' and a['section']!='.rodata' or slot['kind']!='typed_string' and a['section']!='.data':raise ValueError('slot section/type differs')
   if slot['source'] not in m['review_inputs']:raise ValueError('storage source is not fingerprinted')
   if root:slot_literal(slot,root)
   cursor=slot['offset']+slot['size']
  if cursor!=a['size']:raise ValueError('unaccounted semantic storage bytes')
 if sorted(m['section_order'])!=sorted([a['section'] for a in allocations if a['section']!='.text.*']+['.text.'+a['function'] for a in members]):raise ValueError('incomplete section-order inventory')
def elf_headers(blob):
 offset=struct.unpack_from('<I',blob,32)[0];stride,count,strings=struct.unpack_from('<HHH',blob,46)
 headers=[struct.unpack_from('<10I',blob,offset+i*stride) for i in range(count)];names=blob[headers[strings][4]:headers[strings][4]+headers[strings][5]]
 return offset,stride,{names[h[0]:].split(b'\0',1)[0].decode():(i,h) for i,h in enumerate(headers)}
def prepare(m,blob,root):
 if switches(m):return X.prepare(m,blob,root)
 validate(m,root);table,stride,headers=elf_headers(blob);out=bytearray(blob);proof=[]
 for a in m['allocations']:
  if a['section']=='.text.*':continue
  index,h=headers[a['section']];body=blob[h[4]:h[4]+h[5]];semantic=a['size'];align=h[8]
  if not align or align&(align-1) or len(body)!=(semantic+align-1)&~(align-1) or any(body[semantic:]):raise ValueError('noncanonical GNU end padding')
  expected=bytearray(semantic)
  for slot in a['slots']:expected[slot['offset']:slot['offset']+slot['size']]=slot_literal(slot,root)
  if body[:semantic]!=expected:raise ValueError('compiled literal storage differs from declarations')
  struct.pack_into('<I',out,table+index*stride+20,semantic)
  proof.append(dict(section=a['section'],semantic_bytes=semantic,padding_bytes=len(body)-semantic,padding_hex=body[semantic:].hex(),elf_alignment=align))
 return bytes(out),proof
def retail_bytes(m,root,G):
 raw=root/'work/disc/containers'/G.CONTAINERS[m['container']];result=bytearray()
 with raw.open('rb') as f:
  for a in sorted(m['allocations'],key=lambda a:a['foff']):
   f.seek(a['foff']);data=f.read(a['size'])
   if len(data)!=a['size']:raise ValueError('short allocation retail read')
   result.extend(data)
 return bytes(result)
def expected_payload(m):
 sizes={a['section']:a['size'] for a in m['allocations'] if a['section']!='.text.*'};sizes.update({'.text.'+a['function']:a['size'] for a in m['members']})
 return [(name,sizes[name]) for name in m['section_order']]
def check_views(m,ma,ge,addresses):
 if switches(m):return X.check_views(m,ma,ge,addresses)
 expected={a['function'] for a in m['members']}
 if set(ma.funcs)!=expected or set(ge.funcs)!=expected or ma.obj.unknown or ge.obj.unknown:raise ValueError('complete known function/record inventory differs')
 allowed={'.text','.data','.rdata','.rodata'}
 if any(body for name,body in ge.obj.sections.items() if name not in allowed):raise ValueError('unowned genuine allocation')
 if any(v[2]=='common' for v in ge.obj.symbols.values()):raise ValueError('genuine COMMON')
 code=next(a for a in m['allocations'] if a['section']=='.text.*');cursor=0
 for a in m['members']:
  if ma.funcs[a['function']]!=('.text.'+a['function'],0,a['size']) or ge.funcs[a['function']]!=('.text',cursor,cursor+a['size']):raise ValueError('natural function extent/order differs')
  cursor+=a['size']
 if len(ge.obj.sections['.text'])!=code['size']:raise ValueError('unaccounted genuine text bytes')
 for a in m['allocations']:
  if a['section']=='.text.*':continue
  gn=a['section'];sn='.rdata' if gn=='.rodata' else gn
  if ma.obj.sections.get(gn)!=ge.obj.sections.get(sn) or len(ma.obj.sections.get(gn,b''))!=a['size']:raise ValueError('genuine storage extent/content differs')
  if any(r[0]==gn for r in ma.obj.relocs) or any(r[0]==sn for r in ge.obj.relocs):raise ValueError('literal allocation has a relocation')
  expected_symbols={slot['symbol'] for slot in a['slots']}
  actual_symbols={name for name,symbol in ma.obj.symbols.items() if symbol[0]==gn}
  if actual_symbols!=expected_symbols:raise ValueError('unaccounted GNU storage symbol')
  genuine_symbols={name for name,symbol in ge.obj.symbols.items() if symbol[0]==sn}
  if genuine_symbols-expected_symbols:raise ValueError('unaccounted genuine storage symbol')
  for slot in a['slots']:
   for view,section in [(ma,gn),(ge,sn)]:
    symbol=view.obj.symbols.get(slot['symbol'])
    # Production LNK omits local data labels. Their offsets are checked through
    # the complete literal section and fully resolved code relocations. An
    # exported GNU object cannot use this local-label omission rule.
    if symbol is None and view is ge and ma.obj.symbols[slot['symbol']][2]=='local':continue
    if not symbol or tuple(symbol[:2])!=(section,slot['offset']):raise ValueError('owned symbol placement differs')
   addresses[slot['symbol']]=a['vma']+slot['offset']
def build(m,out,root,G,substitutions=None,*,artifact_only=False):
 validate(m,root);out.mkdir(parents=True,exist_ok=True);before=G.fingerprint(m,root,windows=not artifact_only);env=dict(os.environ,TMPDIR=str(out),PYTHONDONTWRITEBYTECODE='1')
 source=root/m['source'];candidate_hashes={}
 if substitutions:
  if set(substitutions)-{a['source'] for a in m['members']}:raise ValueError('candidate is not a function member')
  text=source.read_text();replaced=set()
  for line in text.splitlines():
   hit=re.fullmatch(r'\s*#include "([^"]+)"\s*',line)
   if not hit:continue
   target=Path(os.path.abspath(source.parent/hit[1]))
   if not target.is_file() or not target.is_relative_to(root):raise ValueError('TU include outside root')
   name=str(target.relative_to(root));replacement=Path(substitutions.get(name,target)).absolute()
   if name in substitutions:
    original_includes=re.findall(r'^\s*#include[^\n]*',target.read_text(),re.M)
    candidate_includes=re.findall(r'^\s*#include[^\n]*',replacement.read_text(),re.M)
    if original_includes!=candidate_includes:raise ValueError('candidate changes the shared include contract')
    replaced.add(name)
   text=text.replace(line,'#include "'+str(replacement)+'"')
  if replaced!=set(substitutions):raise ValueError('member source is not directly included by TU')
  source=out/'candidate.c';source.write_text(text);candidate_hashes={k:G.sha(v) for k,v in substitutions.items()}
 for key in ['AZURE_MASPSX','AZURE_MASPSX_COMPANION','MASPSX_NORETURN_FILE','MASPSX_SIBCALL_FILE']:env.pop(key,None)
 for kind in ['NORETURN','SIBCALL']:env['MASPSX_'+kind+'_FILE']=str(root/'config'/f'{kind.lower()}_syms.{m["container"]}.txt')
 gcc=root/'toolchain/compilers'/('gcc-'+G.module_compiler(m))
 def run(cmd,name,stdin=None,cwd=root):return G.command(cmd,cwd,env,out/(name+'.log'),stdin)
 member_dirs=sorted({str((root/a['source']).parent) for a in m['members']})
 run([gcc/'gcc','-B'+str(gcc)+'/', '-S',*G.module_cflags(m),'-I'+str(root/'include'),*['-I'+p for p in member_dirs],'-w',source,'-o',out/'module.s'],'compile')
 raw=(out/'module.s').read_bytes();processed=run([sys.executable,G.gate_tool(root,'ccproc.py'),'--names-tsv',root/'config/names.tsv'],'ccproc',raw);(out/'sectioned.s').write_bytes(processed)
 run([root/'.venv/bin/python',root/'toolchain/maspsx/maspsx.py','--aspsx-version=2.79','--dont-force-G0','--run-assembler','--gnu-as-path=mipsel-linux-gnu-as','-I'+str(root),'-I'+str(root/'include'),'-EL','-march=r3000','-G8','-o',out/'module.o'],'assemble',processed)
 original=(out/'module.o').read_bytes();(out/'module.untrimmed.o').write_bytes(original);cooked,padding=prepare(m,original,root);(out/'module.o').write_bytes(cooked)
 payload=[s for s in G.sections(out/'module.o') if s['flags']&2 and s['size'] and s['name'] not in G.META]
 if [(s['name'],s['size']) for s in payload]!=expected_payload(m):raise ValueError('unaccounted or reordered GNU allocated payload')
 nm=run(['mipsel-linux-gnu-nm','-S',out/'module.o'],'object_symbols').decode();lines=[l.split() for l in nm.splitlines()]
 if any(len(p)>=2 and p[-2].upper()=='C' for p in lines):raise ValueError('GNU COMMON')
 imports={d['symbol']:d['vma'] for d in m['imports']};undefined={p[-1] for p in lines if len(p)==2 and p[0]=='U'}
 if undefined!=set(imports):raise ValueError('exact import inventory differs')
 addresses=dict(imports,**{a['function']:a['vma'] for a in m['members']});anchors={a['section']:a['vma'] for a in m['allocations'] if a['section']!='.text.*'}
 linker='OUTPUT_FORMAT("elf32-tradlittlemips")\nOUTPUT_ARCH(mips)\n_gp = 0x80080994;\n'+''.join(f'{n} = 0x{v:X};\n' for n,v in imports.items())+'SECTIONS {\n'
 for i,a in enumerate(sorted(m['allocations'],key=lambda a:a['foff'])):linker+=f' .allocation_{i} 0x{a["vma"]:X} : SUBALIGN(4) {{ "{out/"module.o"}"({a["section"]}) }}\n ASSERT(SIZEOF(.allocation_{i}) == {a["size"]}, "allocation extent")\n'
 linker+=' /DISCARD/ : { *(.text) *(.reginfo) *(.MIPS.abiflags) *(.pdr) *(.comment) *(.note*) *(.mdebug*) *(.gnu.attributes) }\n}\n';(out/'module.ld').write_text(linker)
 run(['mipsel-linux-gnu-ld','-EL','-T',out/'module.ld','-Map',out/'module.map','-o',out/'module.elf',out/'module.o'],'link')
 placed={p[-1]:int(p[0],16) for l in run(['mipsel-linux-gnu-nm','-n','-S',out/'module.elf'],'linked_symbols').decode().splitlines() if len(p:=l.split())>=3}
 packed=bytearray()
 for i,a in enumerate(sorted(m['allocations'],key=lambda a:a['foff'])):
  run(['mipsel-linux-gnu-objcopy','-O','binary','-j',f'.allocation_{i}',out/'module.elf',out/f'allocation_{i}.bin'],'allocation_'+str(i));data=(out/f'allocation_{i}.bin').read_bytes()
  if len(data)!=a['size']:raise ValueError('linked allocation extent differs')
  packed.extend(data)
  for slot in a.get('slots',[]):
   if 'symbol' in slot and placed.get(slot['symbol'])!=a['vma']+slot['offset']:raise ValueError('natural linked storage address differs')
 if any(placed.get(a['function'])!=a['vma'] for a in m['members']):raise ValueError('natural linked code address differs')
 retail=retail_bytes(m,root,G);(out/'module.bin').write_bytes(packed);(out/'retail.bin').write_bytes(retail)
 if packed!=retail:raise ValueError('complete allocation retail mismatch')
 canonical=run([sys.executable,G.gate_tool(root,'ccproc.py'),'--names-only','--names-tsv',root/'config/names.tsv'],'names',raw)
 sys.path.insert(0,str(root/'tools/fidelity'));import aspsx_diff as A
 (out/'IN.S').write_bytes(A.aspsx_input(canonical.decode()))
 # ASPSX has a DOS path-length limit; keep its working directory short.
 with tempfile.TemporaryDirectory(prefix='g',dir='/tmp') as td:
  td=Path(td);shutil.copy2(out/'IN.S',td/'IN.S')
  G.command([root/'toolchain/genuine/bin/wibo',root/'toolchain/genuine/psyq/psyq4.4/ASPSX.EXE','-q','-G0',*G.genuine_flags(m,root),'-o','OUT.OBJ','IN.S'],td,dict(env,TMPDIR=str(td),TMP=str(td),TEMP=str(td)),out/'genuine.log')
  shutil.copy2(td/'OUT.OBJ',out/'OUT.OBJ')
 ma=A.View(A.read_elf(cooked));ge=A.View(A.read_lnk((out/'OUT.OBJ').read_bytes()),ref=ma);check_views(m,ma,ge,addresses)
 genuine=bytearray()
 for allocation in sorted(m['allocations'],key=lambda a:a['foff']):
  if allocation['section']!='.text.*':genuine.extend(X.resolve_storage(m,ge,allocation,addresses,A) if switches(m) else ge.obj.sections['.rdata' if allocation['section']=='.rodata' else allocation['section']]);continue
  for member in m['members']:
   words,masked=A.resolve_tokens(ge,member['function'],member['vma'],addresses.get,0x80080994,section_anchors=anchors)
   if masked:raise ValueError('unresolved genuine code relocation')
   genuine.extend(struct.pack('<'+'I'*len(words),*words))
 if genuine!=packed or not A.compare_units(ma,ge)['exact']:raise ValueError('whole-object genuine mismatch')
 (out/'genuine.bin').write_bytes(genuine);(out/'rodata_proof.json').write_text(json.dumps(proof_record(m,padding,original,cooked,ma,ge,(out/'IN.S').read_text(),root,out),indent=2)+'\n')
 after=G.fingerprint(m,root,windows=not artifact_only)
 if before!=after or any(G.sha(substitutions[k])!=h for k,h in candidate_hashes.items()):raise ValueError('inputs changed during complete-object build')
 first=min(m['allocations'],key=lambda a:a['foff']);h=hashlib.sha256(packed).hexdigest()
 receipt=dict(schema=G.SCHEMA,module=m['key'],fingerprint=before,members=[a['id'] for a in G.all_members(m)],physical=dict(compile_edges=1,functions=[a['function'] for a in m['members']],payload=payload,owned_data=[],imports=m['imports'],allocation_model=m['allocation_model'],allocations=m['allocations']),gate=dict(result='MATCH',foff=first['foff'],vma=first['vma'],bytes=len(packed),rebuilt_sha256=h,retail_sha256=h,masked=0,raw_substitution_bytes=0),genuine=dict(result='MATCH',version='2.79',whole_tu=True,flags=['-q','-G0']+G.genuine_flags(m,root),bytes=len(genuine),masked=0,sha256=h),candidates=candidate_hashes,candidate_paths={k:str(Path(v).absolute()) for k,v in (substitutions or {}).items()})
 receipt['artifacts']={n:G.sha(out/n) for n in ['module.s','sectioned.s','module.untrimmed.o','rodata_proof.json','module.o','module.ld','module.elf','module.bin','retail.bin','IN.S','OUT.OBJ','genuine.bin']};(out/'receipt.json').write_text(json.dumps(receipt,indent=2)+'\n');return receipt,out/'module.bin'

def expected_storage_projection(m,start,end):
 result=[]
 for a in sorted(m['allocations'],key=lambda a:a['foff']):
  if a['section']=='.text.*':continue
  lo=max(start,a['foff']);hi=min(end,a['foff']+a['size'])
  if lo<hi:result.append(dict(section=a['section'],foff=lo,size=hi-lo))
 return result
def project_storage(m,segments,blob,out,root=None):
 """Replace raw storage or the exact registered switch-data context row."""
 if not segments:return []
 start=min(s.start for s in segments);end=max(s.end for s in segments)
 projected=expected_storage_projection(m,start,end)
 for piece in projected:
  lo=piece['foff'];hi=lo+piece['size'];overlaps=[(i,s) for i,s in enumerate(segments) if s.start<hi and lo<s.end]
  if len(overlaps)!=1 or not overlaps[0][1].start<=lo<hi<=overlaps[0][1].end:raise ValueError('owned storage is not one complete raw projection source')
  index,original=overlaps[0];chunks=[]
  if original.kind!='raw':
   row=m['data_members'][0] if switches(m) else None
   if not row or root is None or original.kind!='c' or (original.start,original.end)!=(row['foff'],row['foff']+row['size']) or (lo,hi)!=(original.start,original.end) or not original.match or original.match.config not in [m['recipe']['cfg'],m['recipe']['cfg'].replace('-G0',' -G0')] or Path(original.match.source).resolve()!=(Path(root)/row['source']).resolve():raise ValueError('owned storage is not the complete canonical switch-data context row')
  if original.start<lo:chunks.append(dataclasses.replace(original,end=lo))
  allocation=next(a for a in m['allocations'] if a['section']==piece['section'])
  target=out/('owned_'+piece['section'].lstrip('.')+'_'+format(lo,'x')+'.bin');position=offset(m,lo,hi-lo);target.write_bytes(blob[position:position+hi-lo])
  # These are already linked bytes. Window assembly keeps its own dashboard
  # coordinates; the runtime addresses are proven by the whole-object link.
  chunks.append(dataclasses.replace(original,kind='rowbase',start=lo,end=hi,vram=original.vram+lo-original.start,bytes_path=target,name='owned_'+piece['section'].lstrip('.'),match=None,module_key=m['key']))
  if hi<original.end:chunks.append(dataclasses.replace(original,start=hi,vram=original.vram+hi-original.start,name=f'L_raw_{hi:06X}'))
  segments[index:index+1]=chunks
 for i,s in enumerate(segments):segments[i]=dataclasses.replace(s,index=i,section=f'.ovlseg_{i:04d}')
 return projected
def receipt_reason(m,r,root,out,G):
 """Replay literal ownership, exact padding and both object legs at certification."""
 try:
  validate(m,root)
  funcs=[a['function'] for a in m['members']];ids=[a['id'] for a in G.all_members(m)];ph=r.get('physical',{})
  if r.get('schema')!=G.SCHEMA or r.get('module')!=m['key'] or r.get('members')!=ids or r.get('candidates')!={}:raise ValueError('not canonical complete separated TU')
  if ph.get('compile_edges')!=1 or ph.get('functions')!=funcs or ph.get('imports')!=m['imports'] or ph.get('owned_data')!=[] or ph.get('allocations')!=m['allocations'] or ph.get('allocation_model')!=m['allocation_model']:raise ValueError('incomplete physical allocation inventory')
  if [(s['name'],s['size']) for s in ph.get('payload',[])]!=expected_payload(m):raise ValueError('allocated payload differs')
  artifacts=['module.s','sectioned.s','module.untrimmed.o','rodata_proof.json','module.o','module.ld','module.elf','module.bin','retail.bin','IN.S','OUT.OBJ','genuine.bin']
  if set(r.get('artifacts',{}))!=set(artifacts):raise ValueError('missing object artifacts')
  for n,h in r['artifacts'].items():
   if G.sha(out/n)!=h:raise ValueError('changed object artifact: '+n)
  cooked,padding=prepare(m,(out/'module.untrimmed.o').read_bytes(),root)
  if cooked!=(out/'module.o').read_bytes():raise ValueError('padding replay differs')
  sys.path.insert(0,str(root/'tools/fidelity'));import aspsx_diff as A
  ma=A.View(A.read_elf(cooked));ge=A.View(A.read_lnk((out/'OUT.OBJ').read_bytes()),ref=ma)
  addresses={d['symbol']:d['vma'] for d in m['imports']};addresses.update({a['function']:a['vma'] for a in m['members']});check_views(m,ma,ge,addresses)
  if not A.compare_units(ma,ge)['exact']:raise ValueError('genuine object differs')
  if json.loads((out/'rodata_proof.json').read_text())!=proof_record(m,padding,(out/'module.untrimmed.o').read_bytes(),cooked,ma,ge,(out/'IN.S').read_text(),root,out):raise ValueError('storage proof replay differs')
  anchors={a['section']:a['vma'] for a in m['allocations'] if a['section']!='.text.*'};rebuilt=bytearray()
  for allocation in sorted(m['allocations'],key=lambda a:a['foff']):
   if allocation['section']!='.text.*':rebuilt.extend(X.resolve_storage(m,ge,allocation,addresses,A) if switches(m) else ge.obj.sections['.rdata' if allocation['section']=='.rodata' else allocation['section']]);continue
   for member in m['members']:
    words,masked=A.resolve_tokens(ge,member['function'],member['vma'],addresses.get,0x80080994,section_anchors=anchors)
    if masked:raise ValueError('masked code relocation')
    rebuilt.extend(struct.pack('<'+'I'*len(words),*words))
  ret=retail_bytes(m,root,G);digest=hashlib.sha256(ret).hexdigest();first=min(m['allocations'],key=lambda a:a['foff']);gate=r.get('gate',{});genuine=r.get('genuine',{})
  if any(gate.get(k)!=v for k,v in dict(result='MATCH',foff=first['foff'],vma=first['vma'],bytes=len(ret),masked=0,raw_substitution_bytes=0,rebuilt_sha256=digest,retail_sha256=digest).items()):raise ValueError('incomplete retail proof')
  if any(genuine.get(k)!=v for k,v in dict(result='MATCH',version='2.79',whole_tu=True,flags=['-q','-G0']+G.genuine_flags(m,root),bytes=len(ret),masked=0,sha256=digest).items()):raise ValueError('incomplete genuine proof')
  if rebuilt!=ret or any((out/n).read_bytes()!=ret for n in ['module.bin','retail.bin','genuine.bin']):raise ValueError('complete allocation bytes differ')
 except (OSError,ValueError,KeyError,TypeError,IndexError) as e:return 'invalid separated-allocation proof: '+str(e)
 return None


def proof_record(m,padding,original,cooked,ma,ge,assembly,root,out):
 record=dict(model=m['allocation_model'],padding=padding,allocations=m['allocations'])
 if switches(m):
  artifacts={name:(out/name).read_bytes() for name in ['module.s','sectioned.s','module.untrimmed.o','module.o','IN.S','OUT.OBJ']}
  record['native']=X.proof(m,original,cooked,ma,ge,assembly,root,artifacts)
 return record
