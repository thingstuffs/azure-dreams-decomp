#!/usr/bin/env python3
"""Fast, ledger-only whole-container coverage. No binary reads or rebuilds.

Code denominator includes explicitly recorded heuristic code, labelled as such.
Unclassified bytes stay unknown; the result is never a claim that every file
byte is code or that an overlay retail-fill gate establishes ownership.
"""
from __future__ import annotations
import argparse, json
from pathlib import Path

RETAIL_RESIDUE_CATEGORIES = {
    'stale_town_copy', 'foreign_program_fragment', 'formatter_remnant',
    'formatter_build_string', 'older_dungeon_head_bank',
}

def records(p):
    return [json.loads(s) for s in Path(p).read_text().splitlines() if s.strip() and not s.startswith('#')] if Path(p).exists() else []
def merge(iv):
    out=[]
    for a,b in sorted(iv):
        if a>=b: continue
        if out and a<=out[-1][1]: out[-1][1]=max(b,out[-1][1])
        else: out.append([a,b])
    return out
def subtract(a,b):
    out=[]; b=merge(b); j=0
    for start,end in merge(a):
        while j<len(b) and b[j][1]<=start: j+=1
        cur=start; k=j
        while k<len(b) and b[k][0]<end:
            lo,hi=b[k]
            if lo>cur: out.append([cur,lo])
            cur=max(cur,hi); k+=1
            if cur>=end: break
        if cur<end: out.append([cur,end])
    return out
def intersection(a,b): return subtract(a,subtract(a,b))
def size(iv): return sum(b-a for a,b in merge(iv))
def extent(r): return [int(r['foff']),int(r['foff'])+int(r['size'])]

def retail_residue_regions(regions):
    """Read the current, disjoint retail residue attestations."""
    latest = {}
    for row in regions:
        if row['category'] in RETAIL_RESIDUE_CATEGORIES:
            key = (row['container'], *extent(row))
            latest[key] = row
    active = [latest[key] for key in sorted(latest) if latest[key].get('active', True)]
    for first, second in zip(active, active[1:]):
        if first['container'] == second['container'] and extent(first)[1] > extent(second)[0]:
            raise ValueError('overlapping retail residue classifications')
    return active

def coverage(root):
    root=Path(root); led=root/'ledger'; rows=records(led/'rows.jsonl'); instances=records(led/'instances.jsonl'); regions=records(led/'coverage_regions.jsonl')
    containers={r['container']:r for r in records(led/'containers.jsonl')}
    residue=retail_residue_regions(regions)
    latest_regions={}
    for r in regions:latest_regions[(r['container'],r['foff'],r['size'],r['category'])]=r
    regions=[r for r in latest_regions.values() if r.get('active',True)]
    # One current owner decision per physical span; alternate template trials are
    # resolved by the publisher before an outcome enters this event ledger.
    latest={}
    for r in instances: latest[(r['container'],r['foff'],r['size'])]=r
    blocked={(r['container'],r['foff'],r['size']) for r in regions if r['category']=='instance_excluded'}
    proven=[r for r in latest.values() if r.get('result')=='proven' and (r['container'],r['foff'],r['size']) not in blocked]
    report={'schema':'azure-clean.whole-image-coverage.v1','basis':'ledger attestations; no rebuild; heuristics explicitly separated','containers':{}}
    for c,meta in sorted(containers.items()):
        if c=='slus': continue  # SLUS needs linked-section ownership, not stale row sizes.
        n=int(meta['bytes']); whole=[[0,n]]; window=[]; cats={}
        for r in regions:
            if r['container']!=c: continue
            iv=extent(r)
            if not 0<=iv[0]<iv[1]<=n: raise ValueError('coverage region outside '+c)
            if r['category']=='window': window.append(iv)
            else: cats.setdefault(r['category'],[]).append(iv)
        code_rows=[extent(r) for r in rows if r['container']==c and r.get('foff') is not None and r.get('func','').startswith('func_')]
        data_rows=[extent(r) for r in rows if r['container']==c and r.get('foff') is not None and not r.get('func','').startswith('func_')]
        for iv in code_rows+data_rows+[extent(r) for r in proven if r['container']==c]:
            if not 0<=iv[0]<iv[1]<=n: raise ValueError('row or instance outside '+c)
        residue_by_class = {}
        for row in residue:
            if row['container'] == c:
                residue_by_class.setdefault(row['category'], []).append(extent(row))
        excluded = [iv for spans in residue_by_class.values() for iv in spans]
        code_rows=subtract(code_rows,excluded)
        inst=subtract([extent(r) for r in proven if r['container']==c],
                      excluded+code_rows+data_rows+cats.get('data_excluded',[]))
        # Verified residue takes precedence over diagnostic C reproductions.
        partitions={'retail_residue':excluded,'c_rows':code_rows,'proven_instances':inst}
        occupied=merge(excluded+code_rows+inst)
        for key,ivs in [('data_excluded',cats.get('data_excluded',[])+data_rows),('sdk_asm',cats.get('sdk_asm',[])),('unported',cats.get('unported',[])),('estimated_code',cats.get('estimated_code',[]))]:
            partitions[key]=subtract(ivs,occupied); occupied=merge(occupied+partitions[key])
        partitions['unknown']=subtract(whole,occupied)
        def measure(scope):
            b={k:size(intersection(v,scope)) for k,v in partitions.items()}
            denominator=sum(b[k] for k in ['c_rows','proven_instances','sdk_asm','unported','estimated_code'])
            before_inst=b['proven_instances']; numerator=b['c_rows']+before_inst
            b.update(code_bytes_classified_or_estimated=denominator,c_coverage_before_pct=round(100*b['c_rows']/denominator,4) if denominator else None,c_coverage_after_pct=round(100*numerator/denominator,4) if denominator else None,scope_bytes=size(scope),partition_bytes=sum(b.values()))
            assert b['partition_bytes']==b['scope_bytes'],(c,b)
            b['retail_residue_by_class'] = {
                category: size(intersection(spans, scope))
                for category, spans in sorted(residue_by_class.items())
            }
            return b
        report['containers'][c]={'file_bytes':n,'whole_image':measure(whole),'windows':measure(merge(window)),'denominator_complete':size(partitions['unknown'])==0,'proven_instance_records':sum(r['container']==c for r in proven),'note':'Before/after share the final denominator; unknown bytes prevent a complete whole-image code percentage.'}
    return report

def main():
    ap=argparse.ArgumentParser(description=__doc__);ap.add_argument('--root',type=Path,default=Path(__file__).resolve().parents[1]);ap.add_argument('--out',type=Path);a=ap.parse_args()
    text=json.dumps(coverage(a.root),indent=2)+'\n'
    if a.out:a.out.write_text(text)
    else:print(text,end='')
if __name__=='__main__':main()
