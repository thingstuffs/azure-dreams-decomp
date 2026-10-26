"""Symbolic function-pointer tables in an existing complete native TU.

The manifest contains symbol identities, never address-word payloads. Source
initializers, registry code ownership and every relocation must agree. Both
assemblers resolve the entire allocation with zero masks before retail proof.
"""
import re,struct
import overlay_descriptor_allocations as D
MODEL='separated-symbolic-allocations-v1'
def enabled(m):return m.get('allocation_model')==MODEL

def slots(m):
 return [(a,s) for a in m['allocations'] for s in a.get('slots',[]) if s['kind'] in ('function_pointers','typed_records')]

def source_words(slot,root):
 if slot['kind']=='typed_records':return D.source_words(slot,root)
 text=(root/slot['source']).read_text();text=re.sub(r'/\*.*?\*/|//[^\n]*','',text,flags=re.S)
 typ=slot['type'];symbol=slot['symbol']
 if not re.fullmatch(r'[A-Za-z_]\w*',typ):raise ValueError('invalid pointer element type')
 from overlay_native_allocations import source_symbol_pattern
 found=re.findall(r'\b(?:const\s+)?'+re.escape(typ)+r'\s+'+source_symbol_pattern(symbol,root)+r'\s*\[\s*([0-9]+)\s*\]\s*=\s*\{([^{}]*)\}\s*;',text)
 if len(found)!=1:raise ValueError('symbolic table ownership declaration differs')
 count,body=found[0];targets=[x.strip() for x in body.split(',') if x.strip()]
 if len(targets)!=int(count) or len(targets)*4!=slot['size']:raise ValueError('symbolic table initializer extent differs')
 if any(not re.fullmatch(source_symbol_pattern(expected,root),actual) for actual,expected in zip(targets,slot['targets'])) or len(targets)!=len(slot['targets']):raise ValueError('symbolic table source target differs')
 header=(root/slot['declaration']).read_text()
 if not re.search(r'\btypedef\s+void\s*\(\s*\*\s*'+re.escape(typ)+r'\s*\)\s*\(\s*[^()]+\)\s*;',header):raise ValueError('table lacks a typed callback contract')
 return bytes(slot['size'])

def validate(m,root=None):
 data=m.get('data_members',[]);ss=slots(m)
 if not ss or len(data)!=len(ss):raise ValueError('one data row per symbolic table required')
 imports={d['symbol'] for d in m['imports'] if d['kind']=='function'};local={a['function'] for a in m['members']}
 for allocation,slot in ss:
  if slot['kind']=='typed_records':D.validate(slot,m,root)
  elif set(slot)!={'kind','symbol','offset','size','source','type','declaration','targets','owner'}:raise ValueError('unsupported symbolic slot fields')
  if slot['source']!=m['source'] or slot['source'] not in m['review_inputs'] or slot['declaration'] not in m['headers']:raise ValueError('symbolic table must belong to fingerprinted owning TU')
  if slot['owner'] not in {a['id'] for a in m['members']}:raise ValueError('symbolic table has a foreign code owner')
  if slot['kind']=='function_pointers' and (len(slot['targets'])*4!=slot['size'] or any(t not in imports|local for t in slot['targets'])):raise ValueError('symbolic target lacks a code binding')
  expected=dict(source=m['source'],symbol=slot['symbol'],foff=allocation['foff']+slot['offset'],vma=allocation['vma']+slot['offset'],size=slot['size'])
  rows=[a for a in data if all(a.get(k)==v for k,v in expected.items())]
  if len(rows)!=1:raise ValueError('symbolic data row extent/owner differs')
  if root:source_words(slot,root)
 if any(s['kind'] not in ('function_pointers','typed_records') for a in m['allocations'] for s in a.get('slots',[])):raise ValueError('mixed symbolic/literal ownership')

def validate_ownership(m,rows):
 validate(m)
 for allocation,slot in slots(m):
  member=next(a for a in m['data_members'] if a['symbol']==slot['symbol']);row=rows[member['id']]
  if (row.get('row_kind'),row.get('data_kind'),row.get('ownership_status'),row.get('owner'))!=('data','descriptor_table' if slot['kind']=='typed_records' else 'function_table','evidenced',slot['owner']):raise ValueError('symbolic table registry ownership differs')
 # Address equality alone cannot turn a data row or a function interior into
 # an executable target. Every target binds an exact registered code entry.
 by_address={}
 for row in rows.values():
  if row.get('row_kind')!='data':by_address.setdefault(row.get('true_name') or row['func'],[]).append(row)
 bindings={d['symbol']:d['vma'] for d in m['imports'] if d['kind']=='function'}
 bindings.update({a['function']:a['vma'] for a in m['members']})
 for _,slot in slots(m):
  for target in function_targets(slot):
   delta=m['members'][0]['vma']-m['members'][0]['foff']
   owners=[r for r in by_address.get(target,[]) if r.get('container')==m['container'] and r.get('foff')==bindings[target]-delta]
   if len(owners)!=1:raise ValueError('symbolic target is not a registered code entry in this load map: '+target)
   address=re.fullmatch(r'func_([0-9A-Fa-f]{8})',target)
   if address and bindings[target]!=int(address[1],16):raise ValueError('symbolic code binding differs from canonical entry')

def table_tokens(view,section,size):
 name='__symbolic_storage__'
 if name in view.funcs:raise ValueError('reserved symbolic proof name')
 view.funcs[name]=(section,0,size)
 try:return view.tokens(name)
 finally:del view.funcs[name]

def function_targets(slot):
 if slot['kind']=='function_pointers':return slot['targets']
 return [target for offset,target,kind in D.inventory(slot)[1] if kind=='function']

def slot_inventory(slot):
 if slot['kind']=='function_pointers':return bytes(slot['size']),[(i*4,t,'function') for i,t in enumerate(slot['targets'])]
 return D.inventory(slot)

def check_view(m,allocation,view):
 section=allocation['section'];section='.rdata' if section=='.rodata' and '.rdata' in view.obj.sections else section
 tokens=table_tokens(view,section,allocation['size']);expected=[];packed=bytearray(allocation['size'])
 for slot in allocation['slots']:
  data,ptrs=slot_inventory(slot);packed[slot['offset']:slot['offset']+slot['size']]=data
  expected.extend((slot['offset']+i,target) for i,target,kind in ptrs)
 if len(tokens)*4!=allocation['size'] or len(view.obj.sections.get(section,b''))!=allocation['size']:raise ValueError('symbolic storage extent differs')
 relocs=[r for r in view.obj.relocs if r[0]==section]
 if len(relocs)!=len(expected) or sorted(r[1] for r in relocs)!=[p for p,t in expected]:raise ValueError('missing/extra symbolic relocation')
 bindings={d['symbol']:d['vma'] for d in m['imports']}
 bindings.update({a['function']:a['vma'] for a in m['members']})
 by_offset={r[1]:r for r in relocs}
 for offset,target in expected:
  word,kind,key=tokens[offset//4];raw=by_offset[offset]
  canonical=key in [('sym',target,0),('fn',target,0)]
  if key==('addr',None,bindings[target]):canonical=raw[3]==('sym',target) and raw[4]==0
  if word!=0 or kind!='32' or not canonical:raise ValueError('symbolic relocation target/type/addend differs')
 for offset,token in enumerate(tokens):
  if offset*4 not in by_offset and token!=(struct.unpack_from('<I',packed,offset*4)[0],None,None):raise ValueError('descriptor scalar bytes differ')
 return tokens

def check_relocations(m,allocation,blob,root):
 # GNU may carry zero section-end padding at this stage; prepare trims it
 # after checking that it is canonical. Validate the semantic view only.
 import sys
 sys.path.insert(0,str(root/'tools/fidelity'));import aspsx_diff as A
 view=A.View(A.read_elf(blob));view.obj.sections[allocation['section']]=view.obj.sections[allocation['section']][:allocation['size']]
 check_view(m,allocation,view)

def check_views(m,allocation,ma,ge):
 if check_view(m,allocation,ma)!=check_view(m,allocation,ge):raise ValueError('genuine symbolic relocation inventory differs')

def resolve_storage(m,view,allocation,addresses,A):
 section=allocation['section'];section='.rdata' if section=='.rodata' and '.rdata' in view.obj.sections else section
 name='__symbolic_storage__';view.funcs[name]=(section,0,allocation['size'])
 try:words,masked=A.resolve_tokens(view,name,allocation['vma'],addresses.get,0x80080994)
 finally:del view.funcs[name]
 if masked:raise ValueError('unresolved symbolic table relocation')
 return struct.pack('<'+'I'*len(words),*words)

def proof(m,ma,ge):
 return [dict(symbol=s['symbol'],entries=len(s['records']) if s['kind']=='typed_records' else len(s['targets']),targets=function_targets(s),relocations='exact R_MIPS_32, zero addends',maspsx_genuine_equal=check_view(m,a,ma)==check_view(m,a,ge)) for a,s in slots(m)]


def data_member(root,family,row):
 """Match selection may expose data only through its complete native owner."""
 import overlay_module_gate as G
 rid=family+'/'+row['func_vram'] if family else None
 found=[(m,a) for m in G.load_modules(root) if enabled(m) for a in m.get('data_members',[]) if a['id']==rid]
 if len(found)!=1:raise ValueError('symbolic data row lacks one complete native owner')
 m,a=found[0]
 if (a['foff'],a['size'],a['symbol'])!=(row['foff'],row['size'],row.get('true_name')):raise ValueError('symbolic data match extent/identity differs')
 return m,a
