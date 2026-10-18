#!/usr/bin/env python3
"""Reproducible conservative B13 byte maps and LL6 leftovers, without retail payloads.

Production config/link remains the compilation catalogue. The public link/ catalogue
extends every placement view to v1 and adds physical roots, without moving sources or
changing compilation inputs. The B13 census supplies all seven disjoint labels.
"""
from __future__ import annotations

import argparse
from bisect import bisect_right
from collections import Counter, defaultdict
import csv
import hashlib
import heapq
import json
from pathlib import Path
import re
import struct
import sys

sys.path.insert(0, str(Path(__file__).resolve().parent))
import byte_map as B
import byte_map_format as F
import leftover_audit
L = B.L
EVIDENCE = 'docs/evidence/r121w_ll6/LEFTOVERS_REPORT.md'
CLASSES = ('c', 'placement', 'library_asm', 'other_proven_code', 'strongly_code', 'data_asset',
           'padding', 'leftover', 'unresolved')
ROOTS = ['main/main_bin', 'town/town_bin', 'dungeon/dungeon_bin',
         'ovmovie/ovmovie_bin', 'slus/slus_bin']


def write_json(path, value):
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_text(json.dumps(value, indent=1, sort_keys=True)+'\n')


def records(path):
    return list(B.read_jsonl(path))


def digest(blob):
    return hashlib.sha256(blob).hexdigest()


def union(intervals):
    out = []
    for a, b in sorted(intervals):
        if out and a <= out[-1][1]:
            out[-1] = (out[-1][0], max(b, out[-1][1]))
        elif a < b:
            out.append((a, b))
    return out


def intersects(intervals, a, b):
    return any(x < b and a < y for x, y in intervals)


def partition(size, candidates):
    """Highest-priority positive witness wins, deterministically, at every boundary."""
    events = defaultdict(list)
    for i, s in enumerate(candidates):
        a, b = s['foff'], s['foff']+s['size']
        if not 0 <= a < b <= size:
            raise ValueError('witness outside physical file: '+str(s))
        events[a].append(i)
        events[b]  # ensure expired witnesses are removed at this boundary
    events[size]
    heap, out = [], []
    for a, b in zip(sorted(events), sorted(events)[1:]):
        for i in events[a]:
            heapq.heappush(heap, (-candidates[i]['priority'], i, candidates[i]['foff']+candidates[i]['size']))
        while heap and heap[0][2] <= a:
            heapq.heappop(heap)
        if not heap:
            raise ValueError('missing physical witness')
        s = candidates[heap[0][1]]
        current = dict(s, foff=a, size=b-a)
        if out and {k:v for k,v in out[-1].items() if k not in ('foff','size')} == {k:v for k,v in current.items() if k not in ('foff','size')}:
            out[-1]['size'] += b-a
        else:
            out.append(current)
    return out


class SpanIndex(list):
    """Sorted immutable interval snapshot with a reusable binary-search index."""
    def __init__(self, spans):
        super().__init__(spans)
        self.starts = [s['foff'] for s in self]


def bounded(spans, a, b):
    starts = spans.starts if isinstance(spans, SpanIndex) else [s['foff'] for s in spans]
    i = max(0, bisect_right(starts, a)-1)
    while i < len(spans) and spans[i]['foff'] < b:
        s = spans[i]
        x, y = max(a, s['foff']), min(b, s['foff']+s['size'])
        if x < y:
            yield dict(s, foff=x, size=y-x)
        i += 1


def census_spans(root, blobs, census_dir):
    """Replay a current, hashed census; reject stale, sparse or overlapping input."""
    lane = Path(census_dir)
    receipt = json.loads((lane/'receipt.json').read_text())
    base = json.loads((root/'config/census/snapshot.json').read_text())['base']
    if receipt['base'] != base:
        raise ValueError('census input receipt has a different base')
    for paths, directory in ((receipt['inputs'], root), (receipt['outputs'], lane)):
        for path, sha in paths.items():
            if B.sha256(directory/path) != sha:
                raise ValueError('census input/output changed: '+path)
    if receipt.get('retail') != {c:digest(b) for c,b in blobs.items()}:
        raise ValueError('census retail identity changed')
    summary = json.loads((lane/'census.json').read_text())
    if summary['ledger_rev'] != base:
        raise ValueError('census summary has a different base')
    registry = json.loads((root/'config/census/rules.json').read_text())['rules']
    rule_ids = {(v['kind'],v['label']):k for k,v in registry.items()}
    physical = {}
    for c, blob in blobs.items():
        path = lane/'spans'/(c+'.spans.json')
        raw = json.loads(path.read_text())
        spans = []
        for key, rows in raw.items():
            label = key.split(' ', 1)[1]
            if label not in L.CENSUS_LABELS:
                raise ValueError('unsupported census class: '+key)
            for a,b,kind in rows:
                if type(a) is not int or type(b) is not int or not 0 <= a < b <= len(blob):
                    raise ValueError('census extent outside physical file')
                evidence = rule_ids[(kind,label)]
                if registry[evidence]['label'] != label:
                    raise ValueError('census rule contradicts label: '+evidence)
                category = {'proven_code':'other_proven_code', 'library_code':'library_asm',
                            'strongly_code':'strongly_code', 'proven_data':'data_asset',
                            'noncode_typing_pending':'data_asset', 'padding_leftover':'padding',
                            'unknown':'unresolved'}[label]
                span = dict(foff=a,size=b-a,label=label,category=category,priority=10,evidence=evidence)
                if label == 'proven_data':
                    # Some census data witnesses establish only non-code or link
                    # ownership. An opaque hashed asset preserves that distinction;
                    # it does not invent a C type or an allocation boundary.
                    span.update(kind='asset', format='census data slice: '+kind,
                                sha256=digest(blob[a:b]), extractor='container-slice-v1')
                elif label == 'padding_leftover':
                    if 'stale_or_prior_image' in kind:
                        span.update(kind='leftover',reason='Census ledger stale/prior image witness: '+kind)
                        span['category']='leftover'
                    else:
                        span['kind']='padding'
                spans.append(span)
        spans.sort(key=lambda s:s['foff'])
        end = 0
        for span in spans:
            if span['foff'] != end:
                raise ValueError('census gap or overlap in '+c+' at '+hex(end))
            end += span['size']
        expected = {key.split(' ',1)[1]:n for key,n in summary['census'][c]['labels'].items()}
        if end != len(blob) or B.totals(spans) != L._totals(expected):
            raise ValueError('census byte totals differ in '+c)
        physical[c] = SpanIndex(spans)
    return physical, receipt


def leftover_catalogue(root, town, splits, disc_path=None):
    from gate.disc_slice import Disc
    with Disc(disc_path or root/'bin/Azure Dreams.bin') as disc:
        town_lba, size = disc.locate('TOWN/TOWN.BIN')
    if size != len(town):
        raise ValueError('disc TOWN length differs')
    groups = defaultdict(list)
    def add(group, key, off, length, reason, **extra):
        if not 0 <= off < off+length <= len(town):
            raise ValueError('leftover outside TOWN')
        groups[group].append(dict(id=key, container='town', foff=off, size=length,
                                  sha256=digest(town[off:off+length]), evidence=EVIDENCE,
                                  reason=reason, **extra))
    for i in range(25):
        word, sector = struct.unpack_from('<II', town, 0x564a0+8*i)
        length = (word >> 23)*2048
        off = (sector-town_lba)*2048
        if word & 0x7fffff != 0x16000 or not length:
            raise ValueError('unexpected scene descriptor')
        add('town/scene_drafts', 'scene_record_%02d'%i, off, length,
            'Writing-room draft; only S_flgtst reaches this table; no shipped-script call in the cited static analysis.',
            descriptor_foff=0x564a0+8*i, linked_vma='0x80700000', runtime_placement='unproven')
    # These three starts are proved; only their witnessed code envelope is bounded here.
    # Do not infer all 24 twin extents from the prose or declare alternate builds identical.
    for name, start, limit in [('a',0x834800,0x839000),('b',0x83a800,0x83c000),('c',0x844000,0x845000)]:
        ends = [r['foff']+r['size'] for r in splits if r.get('result')=='MATCH' and start <= r['foff'] < limit]
        if not ends:
            raise ValueError('missing bounded zero-base code evidence')
        add('town/scene_drafts', 'zero_base_'+name, start, max(ends)-start,
            'Decision 52 zero-base alternate scene build; footprint ends at last existing MATCH row, not an inferred full image end.',
            linked_vma='0x0', runtime_placement='unproven', extent='witnessed prefix; full extent pending')
    for group, offsets in [('town/debug_npc',[0x84e000,0x868000]),('town/test_shop',[0x80b800,0x84c000])]:
        hashes = []
        for off in offsets:
            add(group, 'slice_%x'%off, off, 0x800,
                'Unused debug/test unit in the cited static reachability analysis; sector-bounded verified duplicate slice.',
                extent='verified 2048-byte slice; enclosing unit extent pending')
            hashes.append(groups[group][-1]['sha256'])
        if len(set(hashes)) != 1:
            raise ValueError('reported identical slice differs: '+group)
    add('devkit','symbol_dump',0x80c000,0x82b914-0x80c000,
        'Developer symbol-name/value dump; 678 and 2909 validated 36-byte records separated by 168 opaque bytes; see link/leftovers/evidence/audit.json.',
        format='two symbol arrays; char name[32] plus little-endian u32 value; opaque separator')
    add('devkit','debug_type_info',0x862b00,0x1100,
        'Psy-Q developer struct/type information, cited bounded extent.',format='Psy-Q debug type tables; detailed typing pending')
    add('devkit','scenario_paths',0x7f877c,0x7f8894-0x7f877c,
        'Build-root scenario path table inside a draft image; no opener found in the cited analysis.',format='path table; detailed typing pending')
    for key, start in [('assembler_source',0x82e800),('link_line',0x832838)]:
        end = town.find(b'\0',start,min(start+0x4000,len(town)))
        if end < 0 or end == start:
            raise ValueError('unbounded developer text anchor: '+key)
        add('devkit',key,start,end+1-start,
            'Developer assembler/linker text residue at the cited anchor; bounded by its first NUL.',format='NUL-terminated developer text')
    return dict(groups)



def coalesce(entries, blob):
    """Merge adjacent metadata with identical kind, rule and attributes; rehash assets.

    TU and image-reference boundaries are retained. Category refinements are a
    reporting concern and cannot multiply otherwise identical map intervals.
    """
    out = []
    def identity(e):
        return {k:v for k,v in e.items() if k not in ('foff','size','sha256')}
    for entry in entries:
        e = dict(entry)
        if 'kind' in e:
            e['foff'] = L.num(e['foff'])
        if out and e.get('kind') not in (None, 'image') and identity(out[-1]) == identity(e) and L.num(out[-1]['foff'])+L.num(out[-1]['size']) == L.num(e['foff']):
            out[-1]['size'] = L.num(out[-1]['size'])+L.num(e['size'])
        else:
            out.append(e)
    for e in out:
        if e.get('kind') == 'asset':
            a = L.num(e['foff'])
            e['sha256'] = digest(blob[a:a+L.num(e['size'])])
    return out

def build(root, output, census_dir=None, bin_root=None, disc_path=None, link_out=None):
    root = Path(root).resolve()
    output = Path(output)
    output.mkdir(parents=True, exist_ok=True)
    bin_root = Path(bin_root or root)
    link_out = Path(link_out or root/'link')
    census_dir = Path(census_dir or output/'census')
    blobs = {c:(bin_root/p).read_bytes() for c,p in B.RETAIL.items()}
    sizes = {c:len(b) for c,b in blobs.items()}
    expected = {r['container']:r['bytes'] for r in records(root/'ledger/containers.jsonl')}
    expected['slus'] = 524288
    if sizes != expected:
        raise ValueError('physical file lengths differ from container ledger')
    originals = {d['image']:d for d in (json.loads(p.read_text()) for p in L.files(root))}
    baseline = L.load(root)
    splits = {c:records(root/'ledger/splits'/f'{c}.jsonl') for c in B.RETAIL if c!='slus'}
    groups = leftover_catalogue(root,blobs['town'],splits['town'],disc_path)
    leftover_proof = leftover_audit.audit(root,blobs['town'],blobs['slus'],disc_path)
    for entries in groups.values():
        for entry in entries:
            for load in leftover_proof['optional_loads']:
                if entry['foff']==load['foff']:
                    entry.update(extent='complete descriptor-bounded 2048-byte load',
                                 descriptor_container='slus',descriptor_foff=load['descriptor_foff'],
                                 descriptor_evidence='link/leftovers/evidence/audit.json')
    footprints = {c:union([(e['foff'],e['foff']+e['size']) for g in groups.values() for e in g if e['container']==c]) for c in B.RETAIL}
    physical, census_receipt = census_spans(root, blobs, census_dir)
    # Category refinements retain the authoritative census label. Only existing
    # registered code can enter C/placement; census code alone never registers C.
    candidates = defaultdict(list)
    for c, spans in physical.items():
        candidates[c].extend(spans)
    def refine(c, a, n, label, category, priority, evidence):
        for s in bounded(physical[c], a, a+n):
            if s['label'] != label:
                raise ValueError('census contradicts existing witness: '+evidence+' at '+hex(s['foff']))
            candidates[c].append(dict(s, category=category, priority=priority,
                                      evidence=s['evidence']))
    for rid,e in baseline[2].items():
        refine(e['container'], e['foff'], e['size'], 'proven_code',
               'c' if e['home']==rid else 'placement', 100, 'config/link:'+rid+' retained B13 TU entry')
    for c, rows in splits.items():
        for r in rows:
            if r.get('result')=='MATCH' and not r.get('rerun') and not r.get('data_segment') and r.get('row_kind')!='data' and r.get('source_kind')!='platform_asm':
                refine(c, r['foff'], r['size'], 'proven_code', 'c', 90,
                       f"ledger/splits/{c}.jsonl:{r['func_vram']} MATCH")
    for c, intervals in footprints.items():
        for a,b in intervals:
            for s in bounded(physical[c],a,b):
                if s['label']=='padding_leftover':
                    candidates[c].append(dict(s, category='leftover', priority=30,
                                              kind='leftover', reason='Bounded development residue; see '+EVIDENCE))
    physical = {c:SpanIndex(partition(n,candidates[c])) for c,n in sizes.items()}
    # Each refinement can cut a data asset, so hash the exact final slice.
    for c, spans in physical.items():
        for s in spans:
            if s.get('kind')=='asset':
                s['sha256']=digest(blobs[c][s['foff']:s['foff']+s['size']])
    docs = {k:dict(v) for k,v in originals.items()}
    for c,n in sizes.items():
        key = next(k for k in ROOTS if k.startswith(c+'/'))
        docs.setdefault(key,dict(image=key,container=c,foff=0,size=n,vma=None,entries=[],evidence='Physical container root; no runtime address asserted.'))
    # Include every current exported load/link image, including the 54 town
    # modules that do not all have production placement lists yet. These views
    # never fabricate TU entries or infer data from a load extent.
    load_regions = records(root/'ledger/instance_load_regions.jsonl')
    for r in load_regions:
        for c in ('town','slus'):
            expected_hash = r.get('input_'+c+'_sha256')
            if expected_hash and expected_hash != digest(blobs[c]):
                raise ValueError('load-image evidence input differs: '+c)
        c,a,n = r['container'],L.num(r['foff']),L.num(r['size'])
        if not 0 <= a < a+n <= sizes[c]:
            raise ValueError('load-image export outside container')
        key = c+'/load_%x_%x'%(a,n)
        docs[key] = dict(image=key,container=c,foff=a,size=n,
                         vma=r['base'] if r['method'].startswith('validated ') else None,
                         entries=[],evidence='ledger/instance_load_regions.jsonl: '+r['method']+'; '+r['evidence'])
    for group,entries in groups.items():
        for e in entries:
            key = 'town/leftover_'+e['id']
            docs[key] = dict(image=key,container='town',foff=e['foff'],size=e['size'],vma=None,entries=[],evidence=e['evidence']+':'+e['id'])
            e['image'] = key
    witnesses = {str(p.relative_to(root)):B.sha256(p) for p in [root/'tools/byte_map.py',root/'tools/byte_map_rollout.py',root/'tools/leftover_audit.py',root/'tools/gate/linklist.py',root/EVIDENCE,root/'config/slus_006.14.yaml',root/'ledger/rows.jsonl',root/'ledger/instances.jsonl',root/'ledger/instance_load_regions.jsonl',root/'ledger/coverage_regions.jsonl',root/'ledger/containers.jsonl',*[root/'ledger/splits'/f'{c}.jsonl' for c in splits]]}
    for p in L.files(root):
        witnesses[str(p.relative_to(root))] = B.sha256(p)
    witnesses.update(census_receipt['inputs'])
    witnesses.update({
        'config/census/'+p.name:B.sha256(p) for p in sorted((root/'config/census').iterdir()) if p.is_file()
    })
    witnesses.update({
        'tools/census/'+p.name:B.sha256(p) for p in sorted((root/'tools/census').glob('*.py'))
    })
    witnesses['tools/byte_map_format.py'] = B.sha256(root/'tools/byte_map_format.py')
    source_sha = digest(json.dumps(witnesses,sort_keys=True,separators=(',',':')).encode())
    # Bind the complete physical classification, independently of how many views overlap it.
    physical_sha = digest(json.dumps(physical,sort_keys=True,separators=(',',':')).encode())
    for key,doc in docs.items():
        c, a, n = doc['container'], L.num(doc['foff']), L.num(doc['size'])
        protected = [dict(e) for e in doc['entries'] if L.is_code(e) or e.get('kind')=='image']
        protected.sort(key=lambda e:L.num(e['foff']))
        entries, last = [], a
        def fill(start,end):
            out = []
            for s in bounded(physical[c],start,end):
                if s.get('kind')=='asset':
                    actual = digest(blobs[c][s['foff']:s['foff']+s['size']])
                    if actual != s['sha256']:
                        s.update(sha256=actual)
                out.append(B.metadata(s))
            return out
        for e in protected:
            x, sz = L.num(e['foff']),L.num(e['size'])
            entries.extend(fill(last,x))
            entries.append(e)
            last = x+sz
        entries.extend(fill(last,a+n))
        entries = coalesce(entries, blobs[c])
        if 'work/' in doc.get('evidence',''):
            doc['evidence'] = 'census:registered_image' if key in originals else 'census:load_view'
        for entry in entries:
            if entry.get('kind') == 'image':
                entry['evidence'] = 'census:load_image'
        doc.update(schema=L.MAP_SCHEMA,entries=entries,census=B.totals(list(bounded(physical[c],a,a+n))),
                   provenance=dict(labels_sha256=physical_sha,coverage_sha256=witnesses['ledger/coverage_regions.jsonl'],source='LL6 B13 census replay and retained TU entries sha256:'+source_sha))
    images = {k:L.validate_image(d) for k,d in docs.items()}
    L.coverage(images)
    B.describe(images,list(images),ROOTS)
    for key,old in originals.items():
        oldcode = [e for e in old['entries'] if L.is_code(e)]
        if oldcode != [e for e in docs[key]['entries'] if L.is_code(e)]:
            raise ValueError('code entry changed: '+key)
        for field in ('foff','size','vma','layout','symbols'):
            if docs[key].get(field)!=old.get(field):
                raise ValueError('binding geometry changed: '+key)
    link_out.mkdir(parents=True, exist_ok=True)
    # Publish only after all in-memory documents pass validation.
    for old in link_out.glob('*/*.tsv'):
        old.unlink()
    for old in link_out.glob('*/*.json'):
        old.unlink()
    map_paths = []
    for k,d in docs.items():
        map_paths.extend(F.write(link_out/k.split('/')[0], d))
    write_json(link_out/'physical_roots.json',ROOTS)
    loaded = B.load_maps(root, link_out)
    # Full production indices and rule-3 tables, apart from document paths, are identical.
    for i in (1,2,3):
        if loaded[i] != baseline[i]:
            raise ValueError('public maps change production placement indices')
    coverage = []
    for key,doc in sorted(docs.items()):
        c,a,n = doc['container'],L.num(doc['foff']),L.num(doc['size'])
        counts = dict.fromkeys(CLASSES,0)
        left = Counter()
        for s in bounded(physical[c],a,a+n):
            counts[s['category']] += s['size']
            for x,y in footprints[c]:
                left[s['category']] += max(0,min(s['foff']+s['size'],y)-max(s['foff'],x))
        assert sum(counts.values())==n
        coverage.append(dict(image=key,container=c,foff=hex(a),bytes=n,physical_root=int(key in ROOTS),
                             **counts,**{k:v for k,v in doc['census'].items() if k not in counts},
                             leftover_footprint_bytes=sum(left.values()),leftover_code_bytes=sum(left[k] for k in CLASSES[:5]),
                             game_code_bytes=sum(counts[k]-left[k] for k in CLASSES[:5]),unaccounted_bytes=counts['unresolved']))
    with (output/'coverage.tsv').open('w') as f:
        w=csv.DictWriter(f,fieldnames=list(coverage[0]),delimiter='\t',lineterminator='\n');w.writeheader();w.writerows(coverage)
    scratch = output/'scratch'
    scratch.mkdir(exist_ok=True)
    (scratch/'.ignore').write_text('*\n')
    span_export = scratch/'physical_spans.tsv'
    with span_export.open('w') as f:
        fields=['container','foff','size','label','class','evidence']
        w=csv.DictWriter(f,fieldnames=fields,delimiter='\t',lineterminator='\n');w.writeheader()
        for c,spans in sorted(physical.items()):
            for s in spans:w.writerow(dict(container=c,foff=hex(s['foff']),size=s['size'],label=s['label'],**{'class':s['category']},evidence=s['evidence']))
    for group,entries in groups.items():
        write_json(link_out/'leftovers'/group/'placements.json',dict(schema='azure-clean.leftover-slices.v1',group=group,entries=entries))
    write_json(link_out/'leftovers/evidence/audit.json',leftover_proof)
    stale = []
    for c,spans in physical.items():
        for s in spans:
            if s.get('kind')=='leftover' and 'stale_or_prior_image' in s['evidence']:
                a,n=s['foff'],s['size']
                stale.append(dict(container=c,foff=a,size=n,sha256=digest(blobs[c][a:a+n]),
                                  evidence=s['evidence'],physical_root=next(k for k in ROOTS if k.startswith(c+'/'))))
    write_json(link_out/'leftovers/stale_images/intervals.json',
               dict(schema='azure-clean.leftover-intervals.v1',group='stale_images',entries=stale,
                    scope='Only disjoint census ledger stale/prior intervals; no enclosing image extent or additional runtime deadness is inferred.'))
    totals = {k:sum(r[k] for r in coverage if r['physical_root']) for k in ['bytes',*CLASSES,'leftover_footprint_bytes','leftover_code_bytes','game_code_bytes','unaccounted_bytes']}
    write_json(output/'span_export_receipt.json',dict(path='scratch/physical_spans.tsv',
               sha256=B.sha256(span_export),bytes=span_export.stat().st_size,
               rows=sum(len(v) for v in physical.values()),summary=totals,
               reproduction='python3 tools/census/regenerate.py --disc DISC --output TEMP --check; raw spans stay ignored'))
    receipt = dict(schema='azure-clean.ll6-rollout.v1',base=census_receipt['base'],
                   images=len(docs),original_images=len(originals),new_images=len(docs)-len(originals),
                   exported_load_views=len(load_regions),
                   code_entries_preserved=len(baseline[2]),placement_indices_identical=True,
                   production_catalogue_unchanged=True,physical_roots=ROOTS,totals=totals,
                   census_replayed=True,census_totals={c:B.totals(v) for c,v in physical.items()},
                   physical_classification_sha256=physical_sha,witness_manifest_sha256=source_sha,
                   containers={r['container']:r for r in coverage if r['physical_root']},
                   leftovers={k:dict(slices=len(v),union_bytes=sum(b-a for a,b in union([(e['foff'],e['foff']+e['size']) for e in v]))) for k,v in groups.items()},
                   link_bytes=sum(p.stat().st_size for p in map_paths),compact_parts=len(map_paths))
    write_json(output/'rollout_receipt.json',receipt)
    write_json(output/'witness_manifest.json',witnesses)
    return receipt


def main():
    p=argparse.ArgumentParser(description=__doc__)
    p.add_argument('--root',type=Path,default=Path(__file__).resolve().parents[1])
    p.add_argument('--out',type=Path,default=Path('work/census'))
    p.add_argument('--census-dir', type=Path)
    p.add_argument('--bin-root', type=Path)
    p.add_argument('--disc', type=Path)
    p.add_argument('--link-out', type=Path)
    a=p.parse_args()
    try:
        r=build(a.root,a.root/a.out,a.census_dir,a.bin_root,a.disc,a.link_out)
        print(json.dumps({k:r[k] for k in ('images','original_images','code_entries_preserved','totals','leftovers')},indent=2))
    except (ValueError,OSError,KeyError,TypeError) as e:p.exit(1,'byte-map rollout: '+str(e)+'\n')


if __name__=='__main__':main()
