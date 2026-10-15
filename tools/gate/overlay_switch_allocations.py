"""One compiler-generated switch table and one natural contiguous text allocation.

The table has its own existing logical data row. It is never copied from retail
or supplied by C literals; native rodata emission and relocation checks own it.
"""
import json,struct
import overlay_native_rodata as N
MODEL='separated-switch-allocations-v1'
def enabled(m):return m.get('allocation_model')==MODEL

def validate_ownership(m,rows):
 validate(m)
 data=m['data_members'][0];slot=next(a for a in m['allocations'] if a['section']=='.rodata')['slots'][0]
 owner=next(a for a in m['members'] if a['function']==slot['owner'])
 r=rows[data['id']]
 if (r.get('row_kind'),r.get('data_kind'),r.get('ownership_status'),r.get('owner'))!=('data','jump_table','evidenced',owner['id']):raise ValueError('switch row ownership is not evidenced by the registry')

def validate(m,root=None,region=None):
 if not enabled(m) or m.get('owned_data') or len(m.get('data_members',[]))!=1 or not m.get('members') or any(a.get('body_offset') for a in m['members']):raise ValueError('unsupported separated switch cohort')
 allocations=m.get('allocations',[])
 if len(allocations)!=2 or {a['section'] for a in allocations}!={'.rodata','.text.*'}:raise ValueError('one switch and one text allocation required')
 data=next(a for a in allocations if a['section']=='.rodata');code=next(a for a in allocations if a['section']=='.text.*');row=m['data_members'][0];members=m['members']
 if any(type(a[k]) is not int for a in allocations for k in ['foff','vma','size','link_alignment']) or any(a['size']<=0 or a['size']%4 or a['foff']%4 or a['vma']%4 or a['link_alignment']!=4 for a in allocations):raise ValueError('unaligned/empty switch allocation')
 if data['foff']+data['size']>code['foff'] or data['vma']-data['foff']!=code['vma']-code['foff']:raise ValueError('overlapping/inconsistent switch allocations')
 if tuple(row[k] for k in ['foff','vma','size'])!=tuple(data[k] for k in ['foff','vma','size']):raise ValueError('logical data row does not cover switch allocation')
 if any(a['foff']!=code['foff']+sum(b['size'] for b in members[:i]) or a['vma']!=code['vma']+a['foff']-code['foff'] for i,a in enumerate(members)) or code['size']!=sum(a['size'] for a in members):raise ValueError('text allocation is not the complete natural cohort')
 slots=data.get('slots',[])
 if len(slots)!=1:raise ValueError('one complete compiler switch required')
 slot=slots[0];owners={a['function']:a for a in members}
 if set(slot)!={'kind','offset','size','owner','source'} or slot['kind']!='switch_table' or slot['offset']!=0 or slot['size']!=data['size'] or slot['owner'] not in owners or slot['source']!=owners[slot['owner']]['source'] or slot['source'] not in m['review_inputs']:raise ValueError('switch ownership/source differs')
 if code.get('slots'):raise ValueError('text does not contain literal storage slots')
 names=['.text.'+a['function'] for a in members];cut=next(i+1 for i,a in enumerate(members) if a['function']==slot['owner'])
 if m['section_order']!=names[:cut]+['.rodata']+names[cut:]:raise ValueError('switch section creation order differs')
 if region and any(not int(region['foff_start'],0)<=a['foff']<a['foff']+a['size']<=int(region['foff_end'],0) for a in allocations):raise ValueError('switch allocation outside proven region')

def native_manifest(m):
 validate(m);data=next(a for a in m['allocations'] if a['section']=='.rodata');slot=data['slots'][0]
 return dict(m,owned_data=[dict(kind='switch_table',section='.rodata',foff=data['foff'],vma=data['vma'],size=data['size'],owner=slot['owner'])])

def prepare(m,blob,root):
 validate(m,root);cooked,padding=N.prepare_object(native_manifest(m),blob,root/'tools/build/slus_rodata_trim.py')
 return cooked,[] if padding is None else [padding]

def check_views(m,ma,ge,addresses):
 validate(m);expected={a['function'] for a in m['members']}
 if set(ma.funcs)!=expected or set(ge.funcs)!=expected or ma.obj.unknown or ge.obj.unknown:raise ValueError('complete switch function inventory differs')
 if any(body for name,body in ge.obj.sections.items() if name not in {'.text','.rdata','.rodata'}) or any(v[2]=='common' for v in ge.obj.symbols.values()):raise ValueError('unowned genuine switch allocation')
 cursor=0
 for a in m['members']:
  if ma.funcs[a['function']]!=('.text.'+a['function'],0,a['size']) or ge.funcs[a['function']]!=('.text',cursor,cursor+a['size']):raise ValueError('switch text extent/order differs')
  cursor+=a['size']
 if len(ge.obj.sections['.text'])!=cursor:raise ValueError('unaccounted genuine switch text')
 native=native_manifest(m)
 if N.validate_relocations(native,ma)!=N.validate_relocations(native,ge):raise ValueError('genuine switch ownership differs')

def resolve_storage(m,view,allocation,addresses,A):
 if allocation['section']!='.rodata':raise ValueError('unsupported switch storage')
 name='__native_switch_allocation__';assert name not in view.funcs
 section=next(s for s in ['.rdata','.rodata'] if view.obj.sections.get(s));view.funcs[name]=(section,0,allocation['size'])
 try:words,masked=A.resolve_tokens(view,name,allocation['vma'],addresses.get,0x80080994,section_anchors={'.rodata':allocation['vma']})
 finally:del view.funcs[name]
 if masked:raise ValueError('unresolved genuine switch table')
 return struct.pack('<'+'I'*len(words),*words)

def proof(m,raw,cooked,ma,ge,assembly,root,artifacts):
 return N.make_proof(native_manifest(m),raw,cooked,ma,ge,assembly,root/'tools/build/slus_rodata_trim.py',artifacts)
