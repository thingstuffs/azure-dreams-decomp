#!/usr/bin/env python3
"""Preserve reviewed module imports in ordinary placements of their member functions.

A module inventory binds H to X. An ordinary member placement previously bound
X to Y; its new H reference must keep that same Y. Require one callee instance
in every production load view, including a home instance, and retain old keys.
"""
import argparse
import csv
import json
from pathlib import Path
import sys


def review(pair, entry, tables, linklist):
    home_symbol, old_symbol = pair['link'].split('>')
    home, old = int(home_symbol[-8:],16), int(old_symbol[-8:],16)
    callee = linklist.callee_home(tables,home)
    views = linklist.caller_images(tables,entry['container'],entry['foff'])
    if not views:
        raise ValueError('member placement has no production load view')
    targets=set()
    for name in views:
        image=tables[0][name]
        instances=[item for item in tables[2].values()
                   if item['home']==callee['row'] and item['container']==image['container']
                   and image['foff']<=item['foff']<image['foff']+image['size']]
        if len(instances)!=1:
            raise ValueError('member placement has %d callee instances in %s' % (len(instances),name))
        instance=instances[0]
        # A synthetic diagnostic home VMA is not its production load address.
        target=image['vma']+instance['foff']-image['foff']+instance.get('body_offset',0)
        if linklist._binding(tables,entry,old)!=target:
            raise ValueError('old member import misses the unique callee instance in '+name)
        targets.add(target)
    if len(targets)!=1:
        raise ValueError('member import reaches different addresses across load views')
    target=targets.pop();current=linklist._binding(tables,entry,home)
    if current==target:
        return None
    return dict(image=entry['image'],row=entry['row'],key='0x%08X'%home,
                before='0x%08X'%current,after='0x%08X'%target,old_key='0x%08X'%old,
                production_images=views)


def member_callers(text, pair, module, canonical):
    """Only the member whose body imports this name needs the new binding."""
    import cscan
    result=set();sc=cscan.scan(text)
    members={symbol:item['id'] for item in module['members'] if item['source']==pair['file']
             for symbol in (item['function'],item['id'].split('/')[-1])}
    for item in sc.items:
        if item.kind!='def':continue
        tokens=set(cscan.tokens(sc.masked[item.body[0]:item.body[1]]))
        if not tokens.intersection({pair['old'],pair['new']}):continue
        name=item.decls[0].name;symbol=canonical.get(name,name)
        if symbol not in members:
            raise ValueError('import use in a non-member helper requires review: '+name)
        result.add(members[symbol])
    if not result:raise ValueError('no module member uses the reviewed import')
    return result


def main():
    parser=argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--root',type=Path,default=Path(__file__).resolve().parents[2])
    parser.add_argument('--application',type=Path,required=True)
    parser.add_argument('--out',type=Path,required=True)
    parser.add_argument('--apply',action='store_true')
    args=parser.parse_args();root=args.root.resolve()
    sys.path[:0]=[str(root/'tools/gate'),str(root/'tools/tu')]
    import linklist as L
    import copy_place as C
    import address_names as AN
    canonical=AN.names_table(root)
    tables=L.load(root)
    screened={(row['file'],row['old']) for row in csv.DictReader((args.application/'screen/screen.tsv').open(),delimiter='\t') if row['verdict']=='pass'}
    accepted={row['module'] for row in json.loads((args.application/'results.json').read_text()) if row['status']=='applied'}
    pairs=[row for row in json.loads((args.application/'review.json').read_text())
           if row['status']=='candidate' and row.get('module') in accepted and (row['file'],row['old']) in screened]
    modules={row['key']:row for row in json.loads((root/'config/overlays/modules.json').read_text())['modules']}
    reports=[];changes={}
    for pair in pairs:
        member_ids=member_callers((root/pair['file']).read_text(),pair,modules[pair['module']],canonical)
        placements=[entry for entry in tables[2].values() if entry['home'] in member_ids and entry['row']!=entry['home']]
        for entry in placements:
            try:
                change=review(pair,entry,tables,L)
            except ValueError as error:
                reports.append(dict(file=pair['file'],link=pair['link'],row=entry['row'],status='hold',reason=str(error)))
                continue
            reports.append(dict(file=pair['file'],link=pair['link'],row=entry['row'],status='ready' if change else 'already',change=change))
            if change:
                key=(change['image'],change['row'],change['key'])
                if key in changes and changes[key]['after']!=change['after']:
                    raise ValueError('conflicting member re-key requests')
                changes[key]=change
    args.out.parent.mkdir(parents=True,exist_ok=True)
    args.out.write_text(json.dumps(dict(applied=args.apply,reviews=reports,changes=list(changes.values())),indent=1)+'\n')
    holds=[row for row in reports if row['status']=='hold']
    if holds:
        print('MEMBER PLACEMENT HOLDS',json.dumps(holds),file=sys.stderr)
        if args.apply:raise SystemExit('resolve all member-placement holds before applying re-keys')
    if args.apply:
        docs={}
        for (image,row,key),change in sorted(changes.items()):
            path=C._image_path(root,image)
            if path not in docs:docs[path]=C._load_doc(path)
            entry=next(item for item in docs[path]['entries'] if item.get('row')==row)
            entry.setdefault('bindings',{})[key]=change['after']
        for path,doc in docs.items():C._dump_doc(path,doc)
    print('MEMBER PLACEMENT RE-KEY',len(reports),'reviews',len(changes),'changes')


if __name__=='__main__':main()
