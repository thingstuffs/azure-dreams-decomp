"""Separate an already proved native prefix without fabricating code membership.

The original first member keeps its logical identity and complete code body;
new data identities inherit ownership only from the unchanged native allocation
and its complete pointer/switch/alignment proof. Historical levels remain intact.
"""
import json

def enabled(m):
 return 'prefix_provenance' in m

def validate(m,rows,root):
 path=m['prefix_provenance']
 if path not in m['review_inputs'] or not m.get('owned_data') or not m.get('data_members') or not m.get('membership_evidence'):
  raise ValueError('separated native prefix lacks complete provenance')
 p=json.loads((root/path).read_text())
 if p.get('schema')!='native-prefix-separation-v1' or p.get('module')!=m['key'] or p.get('membership_evidence')!=m['membership_evidence']:
  raise ValueError('native prefix provenance identity differs')
 before=p['original_member'];first=m['members'][0];prefix=sum(d['size'] for d in m['owned_data'])
 if before.get('body_offset')!=prefix or before['id']!=first['id'] or before['source']!=first['source'] or before['function']!=first['function'] or first['foff']!=before['foff']+prefix or first['vma']!=before['vma']+prefix or first['size']!=before['size']-prefix or first.get('body_offset') or not p.get('basis'):
  raise ValueError('native prefix separation changed its complete code body')
 if len(m['data_members'])!=len(m['owned_data']):raise ValueError('native prefix record count differs')
 if m['data_members'][0]['foff']!=before['foff'] or m['data_members'][0]['vma']!=before['vma']:
  raise ValueError('native prefix beginning differs')
 functions={a['function']:a['id'] for a in m['members']}
 for index,(member,data) in enumerate(zip(m['data_members'],m['owned_data'])):
  if data['kind']=='typed_function_pointer':owner=functions[data['target']]
  elif data['kind']=='switch_table':owner=functions[data['owner']]
  elif data['kind']=='alignment':owner=functions[m['owned_data'][index+1]['owner']]
  else:raise ValueError('unsupported separated native prefix record')
  row=rows[member['id']]
  if (row.get('row_kind'),row.get('data_kind'),row.get('ownership_status'),row.get('owner'))!=('data','native_prefix','evidenced',owner):
   raise ValueError('native prefix registry owner differs')

def data_member(root,family,row):
 import overlay_module_gate as G
 rid=family+'/'+row['func_vram'] if family else None
 found=[(m,a) for m in G.load_modules(root) if enabled(m) for a in m['data_members'] if a['id']==rid]
 if len(found)!=1:raise ValueError('native prefix row lacks one complete native owner')
 m,a=found[0]
 if (a['foff'],a['size'],a['symbol'])!=(row['foff'],row['size'],row.get('true_name')):raise ValueError('native prefix match extent/identity differs')
 return m,a
