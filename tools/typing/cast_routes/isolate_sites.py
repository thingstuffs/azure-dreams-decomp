#!/usr/bin/env python3
"""Prove guarded sites cumulatively so one byte-changing site need not park a TU."""
import argparse,csv,gzip,json
from collections import Counter
from pathlib import Path
import subprocess,sys
from types import SimpleNamespace


def main(argv=None):
    ap=argparse.ArgumentParser();ap.add_argument('--root',type=Path,default=Path.cwd());ap.add_argument('--out',type=Path,required=True)
    ap.add_argument('--workers',type=int,default=4);ap.add_argument('--folder',required=True);ap.add_argument('--name',required=True);ap.add_argument('--file',required=True);ap.add_argument('--reason',action='append')
    a=ap.parse_args(argv);root=a.root.resolve();out=a.out.resolve();directory=out/a.name
    assert 1 <= a.workers <= 6
    assert out.is_relative_to(root) and a.file.startswith(a.folder+'/') and '..' not in Path(a.file).parts
    assert not subprocess.check_output(['git','diff','HEAD','--name-only'],cwd=root).strip()
    directory.mkdir(parents=True,exist_ok=True);(out/'.ignore').write_text('*\n')
    sys.path.insert(0,str(root/'tools/typing/cast_routes'))
    import guarded_routes as G
    import run_batches as R
    G.setup_root(root);tus,_=G.F.physical_for(root,[a.file]);original=(root/a.file).read_text()
    assert tus, 'source is outside the production graph'
    plans={};holds=[]
    for use_union in (True, False):
        helper = G.integer_union_member
        if not use_union:
            G.integer_union_member = lambda *args: None
        try:
            for tu,recipe in sorted(tus.items()):
                result=G.scan((str(root),tu,recipe,[a.file]));assert not result['error'],result['error']
                if use_union:holds.extend(result['holds'])
                for p in result['plans']:
                    if not a.reason or p['reason'] in a.reason:
                        plans.setdefault((p['start'],p['end'],p['new']),p)
        finally:
            G.integer_union_member = helper
    plans=sorted(plans.values(),key=lambda p:(p['start'], 0 if 'union_member' in p['reason'] else 1));G.write_edits(directory/'plan.tsv',plans)
    before={tu:G.L.capture_one(str(root),tu,recipe) for tu,recipe in sorted(tus.items())}
    kept=[];receipts=[]
    def render(rows):
        text=original
        for p in sorted(rows,key=lambda p:-p['start']):
            assert text[p['start']:p['end']]==p['old']
            text=text[:p['start']]+p['new']+text[p['end']:]
        return text
    try:
        for p in plans:
            if any(p['start']<q['end'] and q['start']<p['end'] for q in kept):
                continue
            text=render(kept+[p]);G.check_debt(a.file,original,text,sum(q['casts'] for q in kept+[p]));(root/a.file).write_text(text)
            after={tu:G.capture((str(root),tu,recipe)) for tu,recipe in sorted(tus.items())}
            passed=all('error' not in after[tu] and all(before[tu].get(k,{})==after[tu].get(k,{}) for k in G.HASH_KEYS) for tu in tus)
            for tu in tus:receipts.append(dict(tu=tu,line=p['line'],equal=passed,before=before[tu],after=after[tu]))
            print('site',a.file,p['line'],p['reason'],'PASS' if passed else 'HELD_BYTE_CHANGE',flush=True)
            if passed:kept.append(p)
            else:
                holds.append(dict(file=a.file,route=p['route'],line=p['line'],reason='individual_production_identity_failed'))
                (root/a.file).write_text(render(kept))
    except BaseException:
        (root/a.file).write_text(original);raise
    G.write_edits(directory/'applied.tsv',kept)
    G.census.write_tsv(directory/'holds.tsv',['file','route','line','reason'],holds)
    (directory/'identity.json.gz').write_bytes(gzip.compress(json.dumps(receipts,separators=(',',':')).encode()))
    (directory/'errors.json').write_text('[]\n')
    summary=dict(folder=a.folder,files_scanned=1,last_file=a.file,plans=len(plans),selected_files=int(bool(plans)),selected_casts={r:sum(p['casts'] for p in plans if p['route']==r) for r in G.ROUTES},holds=dict(Counter(h['reason'] for h in holds)),errors=0,applied=True,accepted_files=int(bool(kept)),accepted_casts={r:sum(p['casts'] for p in kept if p['route']==r) for r in G.ROUTES},rejected_files=[a.file] if not kept and plans else [])
    (directory/'summary.json').write_text(json.dumps(summary,indent=2)+'\n')
    R.ROOT=root;R.OUT=out;R.OPTIONS=SimpleNamespace(workers=a.workers,census=None,discover_all=True,route=None)
    rows=list(csv.DictReader((out/'replay.tsv').open(),delimiter='\t')) if (out/'replay.tsv').exists() else []
    R.batch(a.name,a.folder,rows,prepared=True)


if __name__ == '__main__':
    main()
