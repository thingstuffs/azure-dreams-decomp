#!/usr/bin/env python3
"""Whole-container ledger coverage and decoded registry totals. No binary reads or rebuilds.

Code denominator includes explicitly recorded heuristic code, labelled as such.
Unclassified bytes stay unknown; the result is never a claim that every file
byte is code or that an overlay retail-fill gate establishes ownership.
"""
from __future__ import annotations
import argparse, json
from pathlib import Path

RETAIL_RESIDUE_CATEGORIES = {
    'stale_town_copy', 'foreign_program_fragment', 'formatter_remnant',
    'formatter_build_string', 'older_dungeon_head_bank', 'imported_retail_text', 'prior_town_image', 'bank_pointer_table',
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

def decoded_stream_coverage(root, regions, containers):
    """Require matching physical coverage rows for every regenerated stream."""
    source_containers = {meta['file']: name for name, meta in containers.items() if 'file' in meta}
    expected, decoded = {}, {}
    for path in sorted((root / 'config/decoded').glob('*.json')):
        manifest = json.loads(path.read_text())
        if manifest['proof_mode'] != 'recompress':
            continue
        name = manifest['image']
        if name in decoded:
            raise ValueError(f'duplicate decoded image {name}')
        origin = path.relative_to(root).as_posix()
        totals = manifest['coverage']
        decoded[name] = dict(
            manifest=origin, functions=totals['functions'],
            bytes_with_c=totals['text_bytes'] + totals['data_bytes'],
            text_bytes=totals['text_bytes'], data_bytes=totals['data_bytes'],
            imported_bytes=totals['imported_bytes'], import_classes=manifest['import_classes'],
            stream_bytes=totals['stream_bytes'],
        )
        for stream in manifest['streams']:
            container = source_containers.get(Path(stream['container']).name)
            if container is None:
                raise ValueError(f'{name}: decoded stream container is unregistered')
            offset = stream['offset']
            start = int(offset, 0) if isinstance(offset, str) else int(offset)
            key = container, start, int(stream['used'])
            if key in expected:
                raise ValueError(f'{name}: repeated decoded stream extent')
            expected[key] = origin, stream['source_sha256']
    actual = {(r['container'], r['foff'], r['size']): (r['decoded_manifest'], r['retail_sha256'])
              for r in regions if r['category'] == 'compressed_code_stream'}
    if actual != expected:
        mismatched = sorted(key for key in actual.keys() | expected.keys()
                            if actual.get(key) != expected.get(key))
        raise ValueError(f'compressed code coverage differs from decoded manifest at {mismatched}')
    return decoded


def latest_regions(regions):
    latest = {(r['container'], r['foff'], r['size'], r['category']): r for r in regions}
    return {key: r for key, r in latest.items() if r.get('active', True)}


def module_data_ranges(root):
    """File-backed native allocations by container, including alignment."""
    path = Path(root) / 'config/overlays/modules.json'
    if not path.is_file():
        return {}
    by_container = {}
    for module in json.loads(path.read_text())['modules']:
        native = by_container.setdefault(module['container'], [])
        native.extend(module.get('owned_data', []))
        native.extend(dict(record, kind='data') for record in module.get('allocations', [])
                      if record['section'] in {'.data', '.rodata', '.rdata', '.sdata'})
    return by_container


def overlay_c_ranges(rows, container, native):
    """Split registered C into instructions, data, and native alignment."""
    text, data, alignment = [], [], []
    for row in rows:
        if row['container'] != container or row.get('foff') is None:
            continue
        destination = (text if row.get('row_kind') != 'data' and (row.get('func') or '').startswith('func_')
                       else data)
        destination.append(extent(row))
    for allocation in native.get(container, []):
        raw = [allocation[k] for k in ('foff', 'size')]
        start, size = [int(v, 0) if isinstance(v, str) else int(v) for v in raw]
        destination = alignment if allocation['kind'] == 'alignment' else data
        destination.append([start, start+size])
    return subtract(text, data+alignment), subtract(data, alignment), merge(alignment)


def coverage(root):
    root=Path(root); led=root/'ledger'; rows=records(led/'rows.jsonl'); instances=records(led/'instances.jsonl'); regions=records(led/'coverage_regions.jsonl')
    containers={r['container']:r for r in records(led/'containers.jsonl')}
    residue=retail_residue_regions(regions)
    regions=list(latest_regions(regions).values())
    decoded = decoded_stream_coverage(root, regions, containers)
    native=module_data_ranges(root)
    # One current owner decision per physical span; alternate template trials are
    # resolved by the publisher before an outcome enters this event ledger.
    latest={}
    for r in instances: latest[(r['container'],r['foff'],r['size'])]=r
    blocked={(r['container'],r['foff'],r['size']) for r in regions if r['category']=='instance_excluded'}
    proven=[r for r in latest.values() if r.get('result')=='proven' and (r['container'],r['foff'],r['size']) not in blocked]
    report={'schema':'azure-clean.whole-image-coverage.v1','basis':'ledger attestations; no rebuild; heuristics explicitly separated','containers':{},'decoded_images':decoded}
    for c,meta in sorted(containers.items()):
        if c=='slus': continue  # SLUS needs linked-section ownership, not stale row sizes.
        n=int(meta['bytes']); whole=[[0,n]]; window=[]; cats={}
        for r in regions:
            if r['container']!=c: continue
            iv=extent(r)
            if not 0<=iv[0]<iv[1]<=n: raise ValueError('coverage region outside '+c)
            if r['category']=='window': window.append(iv)
            else: cats.setdefault(r['category'],[]).append(iv)
        code_rows,data_rows,alignment=overlay_c_ranges(rows,c,native)
        for iv in code_rows+data_rows+[extent(r) for r in proven if r['container']==c]:
            if not 0<=iv[0]<iv[1]<=n: raise ValueError('row or instance outside '+c)
        residue_by_class = {}
        for row in residue:
            if row['container'] == c:
                residue_by_class.setdefault(row['category'], []).append(extent(row))
        excluded = [iv for spans in residue_by_class.values() for iv in spans]
        code_rows=subtract(code_rows,excluded)
        inst=subtract([extent(r) for r in proven if r['container']==c],
                      excluded+code_rows+data_rows+alignment+cats.get('data_excluded',[]))
        # Verified residue takes precedence over diagnostic C reproductions.
        partitions={'retail_residue':excluded,'c_rows':code_rows,'proven_instances':inst}
        occupied=merge(excluded+code_rows+inst)
        for key,ivs in [('data_excluded',cats.get('data_excluded',[])+data_rows+alignment),('sdk_asm',cats.get('sdk_asm',[])),('unported',cats.get('unported',[])),('estimated_code',cats.get('estimated_code',[]))]:
            partitions[key]=subtract(ivs,occupied); occupied=merge(occupied+partitions[key])
        streams = cats.get('compressed_code_stream', [])
        if size(streams) != sum(end - start for start, end in streams) or intersection(streams, occupied):
            raise ValueError('compressed code stream overlaps classified coverage in ' + c)
        partitions['compressed_code_stream'] = streams
        partitions['unknown']=subtract(whole,occupied + streams)
        def measure(scope):
            b={k:size(intersection(v,scope)) for k,v in partitions.items()}
            denominator=sum(b[k] for k in ['c_rows','proven_instances','sdk_asm','unported','estimated_code'])
            before_inst=b['proven_instances']; numerator=b['c_rows']+before_inst
            b.update(code_bytes_classified_or_estimated=denominator,c_coverage_before_pct=round(100*b['c_rows']/denominator,4) if denominator else None,c_coverage_after_pct=round(100*numerator/denominator,4) if denominator else None,scope_bytes=size(scope),partition_bytes=sum(b.values()))
            assert b['partition_bytes']==b['scope_bytes'],(c,b)
            b['c_data_bytes'] = size(intersection(intersection(data_rows, partitions['data_excluded']), scope))
            b['native_alignment_bytes'] = size(intersection(intersection(alignment, partitions['data_excluded']), scope))
            b['retail_residue_by_class'] = {
                category: size(intersection(spans, scope))
                for category, spans in sorted(residue_by_class.items())
            }
            return b
        report['containers'][c]={'file_bytes':n,'whole_image':measure(whole),'windows':measure(merge(window)),'denominator_complete':size(partitions['unknown'])==0,'proven_instance_records':sum(r['container']==c for r in proven),'note':'Before/after share the final denominator; unknown bytes prevent a complete whole-image code percentage.'}
    return report

def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--root', type=Path, default=Path(__file__).resolve().parents[1])
    parser.add_argument('--out', type=Path)
    parser.add_argument('--check-streams', action='store_true', help='verify decoded stream coverage records')
    args = parser.parse_args()
    report = coverage(args.root)
    if args.check_streams:
        print(f"compressed code coverage OK: {len(report['decoded_images'])} decoded images")
    else:
        text = json.dumps(report, indent=2) + '\n'
        if args.out:
            args.out.write_text(text)
        else:
            print(text, end='')
if __name__=='__main__':main()
