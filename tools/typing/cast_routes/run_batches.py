#!/usr/bin/env python3
"""Run one-folder batches, preserving proof receipts and full-index patches."""
from __future__ import annotations

import argparse
import csv
import json
import os
from pathlib import Path
import re
import subprocess
import sys

from baseline_backup import BaselineBackup

HERE = Path(__file__).resolve().parent
ROOT = HERE.parents[2]
OUT = None
OPTIONS = None


def git(*args):
    return subprocess.check_output(['git',*args],cwd=ROOT,text=True).strip()


def run(command, log, env=None):
    print('running',log.relative_to(ROOT),flush=True)
    with log.open('w') as output:
        rc = subprocess.run(command,cwd=ROOT,stdout=output,stderr=subprocess.STDOUT,env=env).returncode
    print('finished',log.relative_to(ROOT),'rc',rc,flush=True)
    if rc:
        print(log.read_text()[-3500:],flush=True)
    return rc


def save_map(rows):
    with (OUT/'replay.tsv').open('w',newline='') as output:
        fields=['batch','folder','start','commit','patch','casts_removed','files','status']
        writer=csv.DictWriter(output,fields,delimiter='\t',lineterminator='\n')
        writer.writeheader();writer.writerows(rows)


def batch(name, folder, rows, max_files=0, after_file='', prepared=False):
    assert not git('diff','HEAD','--name-only') or prepared, 'uncommitted tracked edits before batch'
    start=git('rev-parse','HEAD')
    directory=OUT/name
    directory.mkdir(parents=True,exist_ok=True)
    if not prepared:
        command=['nice','-n','10',sys.executable,str(HERE/'guarded_routes.py'),'--folder',folder,
                 '--root',str(ROOT),'--out',str(directory),'--workers',str(OPTIONS.workers),'--apply']
        if OPTIONS.census:
            command += ['--census',str(OPTIONS.census)]
        if OPTIONS.discover_all:
            command += ['--discover-all']
        for route in OPTIONS.route or []:
            command += ['--route',route]
        for reason in getattr(OPTIONS, 'reason', None) or []:
            command += ['--reason',reason]
        if max_files:
            command+=['--max-files',str(max_files)]
        if after_file:
            command+=['--after-file',after_file]
        if run(command,directory/'planner.log'):
            raise RuntimeError('planner failed: '+name)
    summary=json.loads((directory/'summary.json').read_text())
    casts=sum(summary.get('accepted_casts',{}).values())
    if not casts:
        rows.append(dict(batch=name,folder=folder,start=start,commit='',patch='',casts_removed=0,files=0,status='NO_ACCEPTED_EDITS'))
        save_map(rows)
        return summary
    changed=git('diff','HEAD','--name-only').splitlines()
    headers=set(summary.get('published_headers',[]))
    assert all(h.startswith('include/') and '..' not in Path(h).parts for h in headers)
    assert changed and all(f.startswith(folder+'/') or f in headers for f in changed), changed
    env=dict(os.environ)
    assert env.get('AZURE_NATIVE_PORT'), 'set AZURE_NATIVE_PORT for the local proof environment'
    prefix=directory/'proof'
    command=['nice','-n','10','bash','tools/lanes/prove_batch.sh',start,str(prefix.relative_to(ROOT)),str(OPTIONS.workers)]
    try:
        baseline=BaselineBackup.for_sources(ROOT,directory/'baseline_backup',changed)
    except Exception as error:
        (directory/'baseline_error.txt').write_text(str(error)+'\n')
        subprocess.run(['git','restore','--source='+start,'--staged','--worktree','--',*changed,'ledger/layout_inline.jsonl'],cwd=ROOT,check=True)
        rows.append(dict(batch=name,folder=folder,start=start,commit='',patch='',casts_removed=0,files=0,status='HELD_BASELINE_NOT_FRESH'))
        save_map(rows)
        return summary
    attempt=0
    proof_rc=run(command,directory/'proof.batch.log',env)
    while proof_rc:
        native_log=directory/'proof.natcheck.log'
        anchors=set(re.findall(r'ADAPTATION (src/[^\s:]+):',native_log.read_text())) if native_log.exists() else set()
        anchors &= set(changed)
        if not anchors:
            break
        baseline.restore()
        orphan_headers={h for h in headers if ('src/'+Path(h).relative_to('include').with_suffix('.c').as_posix()) in anchors}
        attempt+=1
        trial=directory/f'native_attempt{attempt}'
        trial.mkdir()
        (trial/'candidate.trial.patch').write_text(subprocess.check_output(['git','diff','--full-index',start],cwd=ROOT,text=True))
        for log in list(directory.glob('proof*')):
            log.rename(trial/log.name)
        subprocess.run(['git','restore','--source='+start,'--worktree','--',*sorted(anchors|orphan_headers)],cwd=ROOT,check=True)
        subprocess.run(['git','restore','--source='+start,'--staged','--worktree','--','ledger/layout_inline.jsonl'],cwd=ROOT,check=True)
        applied_path=directory/'applied.tsv'
        with applied_path.open() as input_file:
            reader=csv.DictReader(input_file,delimiter='\t');fields=reader.fieldnames;applied=list(reader)
        applied=[p for p in applied if p['file'] not in anchors|orphan_headers]
        with applied_path.open('w',newline='') as output:
            writer=csv.DictWriter(output,fields,delimiter='\t',lineterminator='\n');writer.writeheader();writer.writerows(applied)
        summary['accepted_casts']={r:sum(int(p['casts']) for p in applied if p['route']==r) for r in summary['accepted_casts']}
        summary['accepted_files']=len({p['file'] for p in applied})
        summary.setdefault('native_anchor_files',[]).extend(sorted(anchors))
        headers-=orphan_headers
        if 'published_headers' in summary:
            summary['published_headers']=sorted(headers)
        summary['holds']['native_adaptation_file_retained']=len(summary['native_anchor_files'])
        with (directory/'holds.tsv').open('a',newline='') as output:
            writer=csv.writer(output,delimiter='\t',lineterminator='\n')
            for file in sorted(anchors):
                writer.writerow([file,'combined','','native_adaptation_file_retained'])
        (directory/'summary.json').write_text(json.dumps(summary,indent=2)+'\n')
        print('retaining native adaptation source anchors',sorted(anchors),flush=True)
        changed=git('diff','HEAD','--name-only').splitlines()
        casts=sum(summary['accepted_casts'].values())
        if not changed:
            rows.append(dict(batch=name,folder=folder,start=start,commit='',patch='',casts_removed=0,files=0,status='HELD_NATIVE_ADAPTATION'))
            save_map(rows)
            return summary
        proof_rc=run(command,directory/'proof.batch.log',env)
    if proof_rc:
        baseline.restore()
        # Preserve failed candidate as a trial patch, then restore only our own
        # source edits and the derived ledger before continuing to another folder.
        (directory/'failed.trial.patch').write_text(subprocess.check_output(['git','diff','--full-index',start],cwd=ROOT,text=True))
        subprocess.run(['git','restore','--source='+start,'--staged','--worktree','--',*changed,'ledger/layout_inline.jsonl'],cwd=ROOT,check=True)
        rows.append(dict(batch=name,folder=folder,start=start,commit='',patch='',casts_removed=0,files=0,status='HELD_BATCH_PROOF_FAILED'))
        summary['batch_status']='HELD_BATCH_PROOF_FAILED'
        save_map(rows)
        return summary
    subprocess.run(['git','add','--',*changed,'ledger/layout_inline.jsonl'],cwd=ROOT,check=True)
    subprocess.run(['git','commit','-qm',f'Prune proven pointer casts in {name}'],cwd=ROOT,check=True)
    commit=git('rev-parse','HEAD')
    patch=directory/'batch.patch'
    patch.write_text(subprocess.check_output(['git','diff','--full-index',start,commit],cwd=ROOT,text=True))
    source_files=sum(f.startswith('src/') for f in changed)
    rows.append(dict(batch=name,folder=folder,start=start,commit=commit,patch=str(patch.relative_to(OUT)),
                     casts_removed=casts,files=source_files,status='PASS'))
    save_map(rows)
    print('accepted',name,casts,'casts',source_files,'source files',flush=True)
    return summary


def main():
    global ROOT, OUT, OPTIONS
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument('--root', type=Path, default=ROOT)
    ap.add_argument('--out', type=Path, required=True)
    ap.add_argument('--folder', action='append', required=True)
    ap.add_argument('--workers', type=int, default=4)
    ap.add_argument('--census', type=Path)
    ap.add_argument('--discover-all', action='store_true')
    ap.add_argument('--route', action='append', choices=('redundant', 'node_body', 'numeric_member', 'qualified_argument'))
    ap.add_argument('--reason', action='append', help='restrict to exact planner guard reasons')
    ap.add_argument('--resume', action='store_true')
    args = ap.parse_args()
    ROOT = args.root.resolve()
    OUT = args.out.resolve()
    OPTIONS = args
    assert 1 <= args.workers <= 6
    assert OUT.is_relative_to(ROOT) and not OUT.is_relative_to(HERE)
    for folder in args.folder:
        path = Path(folder)
        assert not path.is_absolute() and path.parts[0] == 'src' and '..' not in path.parts
    OUT.mkdir(parents=True, exist_ok=True)
    (OUT / '.ignore').write_text('*\n')
    rows = []
    if args.resume and (OUT / 'replay.tsv').exists():
        rows = list(csv.DictReader((OUT / 'replay.tsv').open(), delimiter='\t'))
    done = {r['batch'] for r in rows}
    for folder in args.folder:
        name = folder.removeprefix('src/').replace('/', '_')
        if name not in done:
            batch(name, folder, rows)
    print('all requested folders processed', flush=True)


if __name__ == '__main__':
    main()
