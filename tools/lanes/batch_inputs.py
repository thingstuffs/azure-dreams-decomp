#!/usr/bin/env python3
"""Verify coherence cells and promotion bodies in one private input stage.

The caller owns the enclosing Snapshot transaction, final production gates and
certificate renewal. This stage never certifies or commits and cannot replace
those proofs. Refusals fail the entire batch, including preceding packages.
"""
import argparse
import json
import os
from pathlib import Path
import shutil
import subprocess
import sys
import tempfile

sys.path.insert(0,str(Path(__file__).resolve().parent))
import land_packages as G

def execute(root,base,spec):
    # The genuine assembler has a DOS working-path limit. The enclosing
    # transaction's .git/land_transaction_*/tmp can be too long in lane clones.
    scratch=root/'tmp';scratch.mkdir(exist_ok=True)
    with tempfile.TemporaryDirectory(prefix='batch-',dir=scratch) as temp:
        proof=Path(temp)/'b'
        subprocess.run(['git','clone','--shared','--',str(root),str(proof)],check=True,stdout=subprocess.DEVNULL)
        for rel in G.MANAGED:
            G.remove(proof/rel)
            if (root/rel).exists():shutil.copytree(root/rel,proof/rel,symlinks=True,ignore=shutil.ignore_patterns('__pycache__','cache'))
        G.copy_preflight_inputs(root,proof)
        for rel in ('bin','work/disc/extract'):
            src=root/rel;dst=proof/rel
            if src.is_dir() and not dst.exists():
                if rel=='bin':dst.symlink_to(src.resolve(),target_is_directory=True)
                else:shutil.copytree(src,dst,symlinks=False)
        env=dict(os.environ,TMPDIR=str(proof/'tmp'),GATE_BUILD_ROOT='build_ovl_gate',PYTHONDONTWRITEBYTECODE='1')
        # Exactly the same build/row verifier used by the standalone landers.
        subprocess.run(['bash','tools/build/build_slus.sh','--fresh','-j','4'],cwd=proof,env=env,check=True)
        subprocess.run(['bash','tools/build/mk_ovl_root.sh'],cwd=proof,env=env,check=True)
        subprocess.run(['bash','tools/build/mk_ovl_root.sh'],cwd=proof,env=dict(env,EXP='gate',SRCROOT=str(proof/'src')),check=True)
        before=G.inventory(proof,G.MANAGED,G.GENERATED)
        for n,item in enumerate(spec.get('coherence',[])):
            # A supplied lane may be an external directory alias. Resolve that
            # read-only source once; writes still target the private real copy.
            lane=G.resolve_source(base,item['lane']).resolve(strict=True)
            dst=proof/'work/native_lane/batch'/str(n)
            dst.mkdir(parents=True)
            shutil.copy2(lane/'cells.jsonl',dst/'cells.jsonl')
            cells=G.records(lane/'cells.jsonl')
            if len({r['id'] for r in cells})!=len(cells):raise G.Stop('duplicate coherence row')
            for rec in cells:
                container,name=rec['id'].split('/')
                for suffix in ('.c','.c.base_sha','.c.port_ref'):
                    rel=Path('out')/container/(name+suffix)
                    src=G.safe(lane,rel)
                    if src.exists():
                        out=G.safe(dst,rel);out.parent.mkdir(parents=True,exist_ok=True);shutil.copy2(src,out)
            subprocess.run(['bash','tools/lanes/land_coherence.sh','--transaction-inputs',item['tag'],'batch/'+str(n)],cwd=proof,env=env,check=True)
        if spec.get('promotions'):
            # Import the unchanged promote.py under the proof root. Its scorer,
            # refusal rules and window gates remain authoritative.
            sys.path.insert(0,str(proof/'tools'))
            import common
            import promote
            by={r['id']:r for r in common.rows()}
            for item in spec['promotions']:
                row=by.get(item['id'])
                if row is None:raise G.Stop('promotion row missing: '+item['id'])
                path=common.clean_path(row)
                if G.digest(path)!=item['before']:raise G.Stop('promotion base SHA mismatch: '+item['id'])
                text=G.resolve_source(base,item['body']).read_text()
                rec=promote.promote_text(row,text,item.get('source','batch'))
                if rec['outcome'] not in ('landed','noop'):raise G.Stop('promotion refused: '+json.dumps(rec))
                if rec['outcome']=='landed':common.append_jsonl(promote.JOURNAL,rec)
        after=G.inventory(proof,G.MANAGED,G.GENERATED)
        # Only source/recipe/promotion journals may emerge from this stage.
        changes={r for r in before.keys()|after.keys() if before.get(r)!=after.get(r)}
        files=[]
        for rel in sorted(changes):
            entry=after.get(rel)
            if entry and entry[0]=='dir':continue
            if not rel.startswith(('src/','ledger/','config/')):raise G.Stop('unexpected batch output: '+rel)
            if not entry or entry[0]!='file':raise G.Stop('batch removed or linked an input: '+rel)
            dst=G.safe(root,rel);src=proof/rel
            prior=before.get(rel)
            expected=prior[2] if prior and prior[0]=='file' else None
            if G.digest(dst)!=expected:raise G.Stop('batch target changed: '+rel)
            files.append((src,dst))
        for src,dst in files:dst.parent.mkdir(parents=True,exist_ok=True);shutil.copy2(src,dst)
        print(json.dumps({'step':'BATCH_INPUTS_MATCH','files':[p.relative_to(root).as_posix() for _,p in files],
                          'certificate_renewals':0,'final_production_gates':'required'}),flush=True)

def main():
    ap=argparse.ArgumentParser(description=__doc__);ap.add_argument('--root',required=True,type=Path)
    ap.add_argument('--plan-dir',required=True,type=Path);ap.add_argument('--spec',required=True)
    a=ap.parse_args();execute(a.root.resolve(),a.plan_dir.resolve(),json.loads(a.spec))
if __name__=='__main__':main()
