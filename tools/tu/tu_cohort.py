#!/usr/bin/env python3
"""Resolve a byte-inferred file containing shared placements (decision 75).

A site list is ordered evidence, never a list of independent new definitions.
Resolve each site to its one registered home and enumerate EVERY use of each
home, including same-image copies. Partition uses by (image, start, load delta),
not just image: two complete copies in an image are two distinct cohorts.
Missing siblings and registry-only uses are explicit holds. A clean geometry
plan is only a prerequisite for whole-object, binding and destination proofs.

    tu_cohort.py --groups groups.tsv --out cohorts.tsv --details details/
"""
from __future__ import annotations
import argparse
from collections import defaultdict
import copy
import csv
import json
from pathlib import Path
import sys

HERE=Path(__file__).resolve().parent
sys.path[:0]=[str(HERE), str(HERE.parent/'gate')]
import linklist as L
import group_status as S


def ultimate_home(rid, rows):
    seen=set()
    while True:
        if rid in seen:
            raise ValueError('cyclic source_row: '+rid)
        seen.add(rid)
        if rid not in rows:
            raise ValueError('unregistered home: '+rid)
        nxt=rows[rid].get('source_row')
        if not nxt:
            return rid
        rid=nxt


def plan(sites, images, entries, rows, regions):
    """Pure geometry census. Never invent a row, link binding or storage claim."""
    sites=list(sites)
    result=dict(sites=sites, homes=[], cohorts=[], holds=[])
    def hold(reason, **facts):
        result['holds'].append(dict(reason=reason, **facts))
    if len(sites)<2 or len(set(sites))!=len(sites):
        hold('ordered_membership_required');return result
    try:
        homes=[ultimate_home(rid, rows) for rid in sites]
    except ValueError as exc:
        hold('missing_home', detail=str(exc));return result
    result['homes']=homes
    if len(set(homes))!=len(homes):
        hold('repeated_definition', detail='one home occurs more than once in the proposed file');return result
    if any(rows[rid].get('row_kind')=='data' for rid in sites):
        hold('function_sites_required');return result
    start=rows[sites[0]]['foff'];cursor=start
    offsets=[]
    container=rows[sites[0]]['container']
    for rid, home in zip(sites,homes):
        r=rows[rid];offsets.append(r['foff']-start)
        if r['container']!=container or r['foff']!=cursor or r['size']!=rows[home]['size']:
            hold('site_geometry', row=rid, expected=cursor, actual=r['foff']);return result
        cursor+=r['size']
    result['size']=cursor-start
    by_home=defaultdict(list);by_slot=defaultdict(list)
    # Registry census is independent of the indexed subset; missing link rows
    # must not silently turn a partial cohort into a complete one.
    for rid,r in sorted(rows.items()):
        try:
            home=ultimate_home(rid,rows)
        except ValueError:
            continue
        if home not in homes:
            continue
        if rid not in entries:
            # A real unindexed own home can be accounted by its exact proven
            # rowbase. Copies still need an explicit link-list binding.
            if rid!=home:
                hold('unindexed_use', row=rid, home=home);continue
            mapped=[reg for reg in regions.get(L.family(r['container']), [])
                    if reg[3]=='proven' and reg[0]<=r['foff'] and r['foff']+r['size']<=reg[1]]
            if len(mapped)!=1:
                hold('unindexed_home', row=rid, home=home);continue
            lo,hi,delta,_,name=mapped[0]
            e=dict(row=rid,home=home,container=L.family(r['container']), image='rowbase:'+name,
                   foff=r['foff'],vma=r['foff']+delta,size=r['size'])
        else:
            e=entries[rid]
            if e['home']!=home or e['size']!=r['size'] or e['foff']!=r['foff']:
                hold('registry_link_disagreement', row=rid);continue
        by_home[home].append(e)
    # Index actual slots independently of home so another function at the
    # expected offset is distinguished from an entirely absent row.
    for e in entries.values():
        by_slot[(e['image'],e['foff'])].append(e)
    cohorts={}
    for home,offset in zip(homes,offsets):
        for e in by_home[home]:
            key=(e['image'],e['foff']-offset,e['vma']-e['foff'])
            cohorts.setdefault(key,{})[home]=e
    for (image,base,delta),hits in sorted(cohorts.items()):
        record=dict(image=image,foff=base,delta=delta,members=[],missing=[],state='complete')
        for home,offset in zip(homes,offsets):
            e=hits.get(home)
            if e is None:
                at=by_slot.get((image,base+offset),[])
                record['missing'].append(dict(home=home,foff=base+offset,
                    occupants=[x['row'] for x in at], settle='prove this sibling at the exact slot, or supply evidence that cuts the inferred file'))
            else:
                record['members'].append(dict(home=home,row=e['row']))
        if record['missing']:
            record['state']='partial'
            hold('partial_cohort', image=image, foff=base, missing=record['missing'])
        else:
            cont=L.family(rows[record['members'][0]['row']]['container'])
            need=[(hits[h]['foff'],hits[h]['foff']+hits[h]['size']) for h in homes]
            if not S.covered(regions.get(cont,[]),need,delta):
                record['state']='no_rowbase';hold('no_rowbase',image=image,foff=base,delta=delta)
        result['cohorts'].append(record)
    home_rows=[rows[h] for h in homes]
    home_container=home_rows[0]['container'];home_start=home_rows[0]['foff']
    if any(r['container']!=home_container or r['foff']!=home_start+off for r,off in zip(home_rows,offsets)):
        hold('home_relocation_required', detail='canonical homes do not form this ordered file; a reviewed rehome transaction is required')
    result['geometry_complete']=not result['holds']
    return result


def home_spec(spec, facts):
    """Normalize one complete shared cohort to existing definitions, once each.

    Does not authorize installation: draft/prove/install and complete placement
    reviews still apply. The evidence sites survive separately in the spec.
    """
    if not facts.get('geometry_complete'):
        raise ValueError('shared cohort has unresolved facts')
    if len(spec['modules'])!=1 or spec['modules'][0]['members']!=facts['sites']:
        raise ValueError('spec does not match the ordered evidence sites')
    out=copy.deepcopy(spec)
    out['modules'][0]['members']=facts['homes']
    out['container']=facts['homes'][0].split('/')[0]
    out['placement_sites']=facts['sites']
    return out


def write_details(facts, path, limit=1500000):
    """Bounded, lossless proof pages; no large search-visible JSON dumps."""
    payload=json.dumps(facts,indent=1)+'\n'
    if len(payload.encode())<=limit:
        path.write_text(payload);return
    summary={k:v for k,v in facts.items() if k not in ('cohorts','holds')}
    summary['pages']=[]
    for kind in ('cohorts','holds'):
        batch=[];used=2
        def flush():
            nonlocal batch,used
            if not batch:return
            name=path.stem+'.'+kind+'.%03d.json'%len(summary['pages'])
            (path.parent/name).write_text(json.dumps(batch,indent=1)+'\n')
            summary['pages'].append(dict(kind=kind,path=name,records=len(batch)))
            batch=[];used=2
        for record in facts[kind]:
            size=len(json.dumps(record,indent=1).encode())+4
            if size>limit:raise ValueError('one proof record exceeds page limit')
            if used+size>limit:flush()
            batch.append(record);used+=size
        flush()
    path.write_text(json.dumps(summary,indent=1)+'\n')


def census(root, groups, details=None):
    images,_,entries,_=L.load(root)
    rows={r['id']:r for r in S.jl(Path(root)/'ledger/rows.jsonl')}
    regions={c:S.rowbase(root,c) for c in ('main','town','dungeon','ovmovie')}
    out=[]
    for g in groups:
        facts=plan(g['member_rows'].split(';'),images,entries,rows,regions)
        if details:
            details.mkdir(parents=True,exist_ok=True)
            write_details(facts,details/(g['group_id']+'.json'))
        counts=defaultdict(int)
        for h in facts['holds']:counts[h['reason']]+=1
        out.append(dict(group=g['group_id'],member_rows=g['member_rows'],
                        home_rows=';'.join(facts['homes']),
                        complete_cohorts=sum(c['state']=='complete' for c in facts['cohorts']),
                        partial_cohorts=sum(c['state']=='partial' for c in facts['cohorts']),
                        geometry_complete='yes' if facts.get('geometry_complete') else 'no',
                        holds=','.join('%s:%d'%x for x in sorted(counts.items()))))
    return out


def main():
    ap=argparse.ArgumentParser(description=__doc__)
    ap.add_argument('--root',type=Path,default=HERE.parents[1])
    select=ap.add_mutually_exclusive_group(required=True)
    select.add_argument('--groups',type=Path)
    select.add_argument('--spec',type=Path)
    ap.add_argument('--spec-out',type=Path)
    ap.add_argument('--out',type=Path,required=True)
    ap.add_argument('--details',type=Path)
    args=ap.parse_args()
    if args.spec:
        if not args.spec_out:ap.error('--spec needs --spec-out')
        spec=json.loads(args.spec.read_text())
        if len(spec['modules'])!=1:ap.error('normalize one module at a time')
        images,_,entries,_=L.load(args.root)
        rows={r['id']:r for r in S.jl(args.root/'ledger/rows.jsonl')}
        regions={c:S.rowbase(args.root,c) for c in ('main','town','dungeon','ovmovie')}
        facts=plan(spec['modules'][0]['members'],images,entries,rows,regions)
        write_details(facts,args.out)
        normalized=home_spec(spec,facts)
        args.spec_out.write_text(json.dumps(normalized,indent=2)+'\n')
        print(json.dumps(dict(geometry_complete=True,sites=facts['sites'],homes=facts['homes'])))
        return
    if args.spec_out:ap.error('--spec-out needs --spec')
    with args.groups.open() as f:
        out=census(args.root,list(csv.DictReader(f,delimiter='\t')),args.details)
    S.write(out,args.out)
    print(json.dumps(dict(groups=len(out),geometry_complete=sum(r['geometry_complete']=='yes' for r in out))))


if __name__=='__main__':
    main()
