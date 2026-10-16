"""Explain production failures without modifying another lane's C holds."""
import hashlib,re
from twins import R

def classify(world,transactions,scope):
    out=[];seen=set()
    for result in transactions:
        for bank in result['banks']:
            for gate in bank.get('gates',[]):
                if gate['ok']:continue
                text=gate.get('stdout','')+'\n'+gate.get('stderr','')
                c=gate['window'].split('_')[0]
                matches=re.findall(r'\b(func_[0-9A-Fa-f]{8})\.c\b',text)
                row=world.byid.get(c+'/'+matches[-1]) if matches else None
                if not row:
                    match=re.search(r'foff (0x[0-9A-Fa-f]+)',text)
                    if match:
                        rows=[r for r in world.rows if r['container']==c and r.get('foff')==int(match[1],0)]
                        if len(rows)==1:row=rows[0]
                kind=('existing-matched-source-compile-failure' if row else 'production-gate-failure')
                if 'pre-linked bytes' in text:kind='existing-matched-extent-length-drift' if row else 'production-extent-length-drift'
                overlap=[]
                if row:
                    overlap=[dict(foff=o,size=n,reason=reason) for o,n,reason in scope.get(c,[]) if o<row['foff']+row['size'] and row['foff']<o+n]
                key=(gate['window'],row['id'] if row else '',kind)
                if key in seen:continue
                seen.add(key)
                record=dict(window=gate['window'],classification=kind,existing_row=row['id'] if row else None,overlaps_twins2_scope=overlap,details=text[-1800:])
                if row:
                    path=R/'src'/(row['id']+'.c')
                    record.update(foff=row['foff'],size=row['size'],source='src/'+row['id']+'.c',source_sha256=hashlib.sha256(path.read_bytes()).hexdigest(),cfg=row['cfg'])
                out.append(record)
    return out
