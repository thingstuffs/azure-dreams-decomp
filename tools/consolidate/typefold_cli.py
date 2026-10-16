"""Census and package commands for consolidate.py's type-fold extension."""
from __future__ import annotations
import argparse
from collections import Counter, defaultdict
import csv
import json
from pathlib import Path
import re
import shutil
import sys

from typefold import Catalog, LOCAL, Refuse, mask, sha


def selected_sources(catalog, args):
    row_ids = set(args.row or [])
    modules = set(args.module or [])
    known = set(catalog.rows)
    if row_ids-known: raise Refuse('unknown rows: '+','.join(sorted(row_ids-known)))
    found = 0
    for cont in ('dungeon', 'town', 'main', 'slus', 'ovmovie'):
        for p in sorted((catalog.root/'src'/cont).glob('*.c')):
            row = cont+'/'+p.stem
            if row_ids and row not in row_ids: continue
            if modules and cont+'/'+catalog.modules.get(row, '') not in modules: continue
            if args.limit is not None and found >= args.limit: return
            found += 1
            yield row, p


def census(catalog, args):
    out = args.out; out.mkdir(parents=True, exist_ok=True)
    (out/'.ignore').write_text('*\n')
    groups = defaultdict(list); rows_scanned = 0
    # Streaming details stay in an ignored directory, never an agent-searchable work dump.
    with (out/'candidates.jsonl').open('w') as detail:
        for row, p in selected_sources(catalog, args):
            rows_scanned += 1
            for item in catalog.analyze(p.read_text(), row):
                detail.write(json.dumps(item, sort_keys=True)+'\n')
                groups[item['class']].append(item)
    with (out/'classes.tsv').open('w') as f:
        w = csv.writer(f, delimiter='\t', lineterminator='\n')
        w.writerow(['merged_class','local_types','rows','eligible_local_types','candidate_rows','unambiguous_rows','hard_conflicts','targets','modules','holds'])
        for cls, items in sorted(groups.items(), key=lambda x:(-sum(bool(i['candidates']) for i in x[1]),x[0])):
            cand = [i for i in items if i['candidates']]
            targets = Counter(c['type'] for i in cand for c in i['candidates'])
            holds = Counter(h['reason'] for i in items for h in i.get('holds', []))
            w.writerow([cls,len(items),len({i['row'] for i in items}),len(cand),len({i['row'] for i in cand}),
                        len({i['row'] for i in cand if len(i['candidates']) == 1}),
                        catalog.groups.get(cls, {}).get('hard_conflicts',''),
                        json.dumps(targets, sort_keys=True),json.dumps(Counter(i['row'].split('/')[0]+'/'+i['module'] for i in items),sort_keys=True),json.dumps(holds,sort_keys=True)])
    summary = {'source_files':rows_scanned, 'local_types':sum(len(i) for i in groups.values()),
               'merged_classes':len(groups), 'candidate_local_types':sum(bool(i['candidates']) for v in groups.values() for i in v),
               'candidate_rows':len({i['row'] for v in groups.values() for i in v if i['candidates']}),
               'unambiguous_local_types':sum(len(i['candidates']) == 1 for v in groups.values() for i in v),
               'catalog_targets':len(catalog.targets), 'catalog_holds':catalog.errors}
    (out/'summary.json').write_text(json.dumps(summary,indent=2,sort_keys=True)+'\n')
    return summary


def emit_package(root, out, changes, metadata, guards=(), expected_before=None):
    if out.exists(): raise Refuse('package destination already exists: '+str(out))
    out.mkdir(parents=True); (out/'.ignore').write_text('*\n')
    entries = []
    for rel, after in sorted(changes.items()):
        before_path = root/rel
        before = before_path.read_bytes() if before_path.exists() else None
        if expected_before is not None and rel in expected_before:
            actual = sha(before) if before is not None else None
            if actual != expected_before[rel]: raise Refuse('source changed during generation: '+rel)
        data = after.encode() if isinstance(after,str) else after
        if before == data: continue
        payload = Path('payload')/rel
        p = out/payload; p.parent.mkdir(parents=True,exist_ok=True); p.write_bytes(data)
        entries.append({'path':rel,'before_sha256':sha(before) if before is not None else None,
                        'after_sha256':sha(data),'payload':payload.as_posix()})
    guard_entries = []
    for rel in sorted(set(guards)-set(changes)):
        p = root/rel
        guard_entries.append({'path':rel,'sha256':sha(p.read_bytes()) if p.exists() else None})
    manifest = {'schema':'typefold-package-v1','files':entries,'guards':guard_entries,
                'validation':'candidate; per-row verify and scoped window gates required before landing', **metadata}
    (out/'manifest.json').write_text(json.dumps(manifest,indent=2,sort_keys=True)+'\n')
    shutil.copyfile(Path(__file__).with_name('guarded_apply.py'),out/'apply.py')
    return {'package':str(out),'files':len(entries),'guards':len(guard_entries), 'rows':metadata.get('rows',[])}


def dependencies(catalog, texts):
    seen = set(); todo = []
    for text in texts:
        todo += re.findall(r'^\s*#\s*include\s*"([^"]+)"', text,re.M)
    while todo:
        rel = 'include/'+todo.pop()
        if rel in seen: continue
        seen.add(rel); p = catalog.root/rel
        if p.exists(): todo += re.findall(r'^\s*#\s*include\s*"([^"]+)"',p.read_text(),re.M)
    return seen


def generate(catalog,args):
    choices = json.loads(args.select.read_text()) if args.select else {}
    changes = {}; rows = []; notes = []; holds = []; texts = []; expected = {}
    for row,p in selected_sources(catalog,args):
        local_choices = {k.split('|',1)[-1]:v for k,v in choices.items() if '|' not in k or k.split('|',1)[0] == row}
        old = p.read_text(); new, ns, hs = catalog.fold(old,row,local_choices)
        if old != new:
            rel = p.relative_to(catalog.root).as_posix()
            changes[rel] = new; expected[rel] = sha(old.encode())
            rows.append(row); notes += [{'row':row,**n} for n in ns]; texts += [old,new]
        if hs: holds += [{'row':row,**h} for h in hs]
    guards = dependencies(catalog,texts) | {'config/names.tsv','ledger/rows.jsonl','ledger/levels.jsonl','ledger/modules.jsonl',
                                            'config/overlays/modules.json','config/slus_modules.json'}
    return emit_package(catalog.root,args.out,changes,{'operation':'fold-types','rows':rows,'folds':notes,'holds':holds},guards,expected)


def record_consumers(catalog, old):
    """Include reverse closure, including indirect header and module consumers."""
    reverse = defaultdict(set)
    for h in sorted((catalog.root/'include').rglob('*.h')):
        if h.stat().st_size > 4*1024*1024: raise Refuse('oversized include: '+str(h))
        rel=h.relative_to(catalog.root/'include').as_posix()
        for inc in re.findall(r'^\s*#\s*include\s*"([^"]+)"',h.read_text(),re.M):
            reverse[inc].add(rel)
    affected={'records/'+old+'.h'};todo=list(affected)
    while todo:
        for parent in reverse[todo.pop()]-affected:
            affected.add(parent);todo.append(parent)
    rows=[];unregistered=[];sources=[]
    for row,p in selected_sources(catalog,argparse.Namespace(row=None,module=None,limit=None)):
        includes=set(re.findall(r'^\s*#\s*include\s*"([^"]+)"',p.read_text(),re.M))
        if not includes & affected:continue
        sources.append(p.relative_to(catalog.root).as_posix())
        (rows if row in catalog.rows else unregistered).append(row)
    modules=[]
    manifest=catalog.root/'config/overlays/modules.json'
    if manifest.exists():
        for mod in json.loads(manifest.read_text()).get('modules',[]):
            if any(h.removeprefix('include/') in affected for h in mod.get('headers',[])) or any(a.get('source') in sources for a in mod.get('members',[])):
                modules.append(mod['key']);rows += [a['id'] for a in mod.get('members',[])]
    return sorted(set(rows)),unregistered,modules


def rename_record(catalog,args):
    old = args.old; new = args.name
    if not re.fullmatch(r'Rec_D_[0-9A-Fa-f]{8}',old): raise Refuse('expected Rec_D_<addr>')
    if not re.fullmatch(r'[A-Z][A-Za-z0-9]*',new): raise Refuse('semantic type must be PascalCase')
    if new in catalog.types: raise Refuse('type name already exists: '+new)
    evidence = args.evidence
    ev = Path(evidence)
    if ev.is_absolute() or '..' in ev.parts or not evidence.startswith('knowledge/') or not (catalog.root/ev).is_file():
        raise Refuse('evidence must name an existing root-relative knowledge/ file')
    oldrel = 'include/records/'+old+'.h'; newrel = 'include/records/'+new+'.h'
    if (catalog.root/newrel).exists(): raise Refuse('semantic header already exists')
    text = (catalog.root/oldrel).read_text()
    if old not in catalog.targets: raise Refuse('record definition is not a supported aggregate')
    # Replace code identifiers, leaving the original provenance comments intact.
    from typefold import LEX, apply_edits
    edits = [(m.start(),m.end(),new) for m in LEX.finditer(mask(text)) if m[0] == old]
    renamed = apply_edits(text,edits)
    oldguard = old.upper()+'_H'; newguard = 'RECORDS_'+new.upper()+'_H'
    renamed = re.sub(r'(?m)^(#(?:ifndef|define)\s+)'+re.escape(oldguard)+r'\b',lambda m:m[1]+newguard,renamed)
    if oldguard in renamed: raise Refuse('unrecognised header guard')
    renamed = '/* Semantic name evidence: '+evidence+' ('+args.confidence+'). */\n'+renamed
    shim = ('/* Compatibility include and tag alias; canonical definition: '+new+'.h. */\n'
            '#ifndef '+oldguard+'\n#define '+oldguard+'\n#include "records/'+new+'.h"\n'
            '#define '+old+' '+new+'\n#endif\n')
    changes = {oldrel:shim,newrel:renamed}
    journalrel = 'ledger/type_unification.jsonl'; journal = catalog.root/journalrel
    entry = {'operation':'rename-record','old':old,'type':new,'header':'records/'+new+'.h',
             'shim':'records/'+old+'.h','evidence':evidence,'confidence':args.confidence}
    prior = journal.read_text() if journal.exists() else ''
    if prior and not prior.endswith('\n'): raise Refuse('journal lacks terminal newline')
    changes[journalrel] = prior+json.dumps(entry,separators=(',',':'))+'\n'
    # Preserve the historical record key and member-path evidence. The generator
    # must retain the canonical definition and shim rather than overwrite either.
    records = dict(catalog.records)
    records[old] = {**records.get(old, {}), 'header':'records/'+old+'.h',
                    'sha256':sha(shim.encode()), 'canonical_type':new,
                    'canonical_header':'records/'+new+'.h', 'canonical_sha256':sha(renamed.encode())}
    changes['ledger/records.json'] = json.dumps(records, indent=0)+'\n'
    rows,unregistered,modules = record_consumers(catalog,old)
    return emit_package(catalog.root,args.out,changes,{'operation':'rename-record','rows':rows,'unregistered_sources':unregistered,'certified_modules':modules,'rename':entry},
                        dependencies(catalog,[text]) | {evidence,'ledger/records.json'})


def main(argv=None):
    p=argparse.ArgumentParser(description=__doc__)
    p.add_argument('--root',type=Path,default=Path(__file__).resolve().parents[2])
    sub=p.add_subparsers(dest='command',required=True)
    for cmd in ('census','generate'):
        s=sub.add_parser(cmd); s.add_argument('--out',required=True,type=Path)
        s.add_argument('--row',action='append'); s.add_argument('--module',action='append',help='container/module.c (repeatable)')
        s.add_argument('--limit',type=int)
        if cmd == 'generate': s.add_argument('--select',type=Path,help='JSON mapping [row|]local type -> shared type')
    s=sub.add_parser('rename-record'); s.add_argument('old'); s.add_argument('name')
    s.add_argument('--evidence',required=True); s.add_argument('--confidence',choices=('high','medium'),default='high')
    s.add_argument('--out',required=True,type=Path)
    args=p.parse_args(argv)
    if args.command == 'generate' and not (args.row or args.module): p.error('generate requires --row or --module')
    if getattr(args,'limit',None) is not None and args.limit <= 0: p.error('--limit must be positive')
    try:
        catalog=Catalog(args.root.resolve())
        result={'census':census,'generate':generate,'rename-record':rename_record}[args.command](catalog,args)
    except (Refuse,ValueError,OSError) as e: p.exit(1,str(e)+'\n')
    print(json.dumps(result,sort_keys=True))

if __name__ == '__main__': main()
