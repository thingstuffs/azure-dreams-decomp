#!/usr/bin/env python3
"""Admit native lane members as one guarded package, proving each module TU once.

Usage: native_package.py LANE [LANE ...] [--output DIRECTORY]
A single lane defaults to LANE/delivery and LANE/plan.json. With --if-native,
exit 3 means no manifest-native outputs; every native refusal is an error.
"""
import argparse
import hashlib
import json
import os
from pathlib import Path
import shutil
import subprocess
import sys
import tempfile

ROOT = Path(__file__).resolve().parents[2]
sys.path[:0] = [str(ROOT/'tools/lanes/lanekit'), str(ROOT/'tools/lanes'), str(ROOT/'tools')]
import kitlib
import native_member as N
import lane_admission as A


def sha(path):
    return hashlib.sha256(path.read_bytes()).hexdigest() if path.is_file() else None


def safe(root, name):
    p = Path(name)
    if p.is_absolute() or '..' in p.parts or not name:
        raise ValueError('unsafe relative path: ' + str(name))
    dest = root/p
    if dest.is_symlink() or not dest.parent.resolve().is_relative_to(root):
        raise ValueError('path escapes root: ' + str(name))
    return dest


def lane_path(name):
    p = Path(name)
    if not p.is_absolute():
        p = ROOT/p if len(p.parts) > 1 else ROOT/'work/native_lane'/p
    p = p.resolve()
    if not p.is_relative_to(ROOT/'work/native_lane') or not p.is_dir():
        raise ValueError('lane must exist under work/native_lane: ' + str(name))
    return p


def collect(lanes):
    """Manifest membership is authoritative even when native validation is disabled."""
    path = ROOT/'config/overlays/modules.json'
    modules = json.loads(path.read_text())['modules'] if path.exists() else []
    owners = {}
    for m in modules:
        for a in m['members'] + m.get('data_members', []):
            owners.setdefault(a['id'], []).append(m['key'])
    rows, policy = A.context(ROOT)
    groups = {}; rejected = []; ordinary = []; seen = set(); native_seen = False
    for lane in lanes:
        for f in sorted((lane/'out').glob('*/*.c')):
            rid = f.parent.name+'/'+f.stem
            if rid not in owners:
                ordinary.append(rid); continue
            native_seen = True
            if len(owners[rid]) != 1:
                raise ValueError('ambiguous native module membership: ' + rid)
            if rid in seen:
                raise ValueError('duplicate staged native row across lanes: ' + rid)
            seen.add(rid)
            if f.is_symlink() or not f.resolve().is_relative_to(lane):
                raise ValueError('staged native source escapes lane: ' + rid)
            row = rows[rid]; m = N.membership(row)
            if m is None:
                raise ValueError('native manifest membership unavailable: ' + rid)
            text = f.read_text(); source = safe(ROOT, 'src/'+rid+'.c'); cur = source.read_text()
            base = safe(lane, f.relative_to(lane).as_posix()+'.base_sha')
            outcome = A.assess(row, text, cur, base.read_text().strip() if base.exists() else '', lane.name, **policy)
            if not outcome['accepted']:
                rejected.append(dict(row=rid, lane=lane.name, **outcome)); continue
            group = groups.setdefault(m['key'], dict(module=m, rows=[], texts={}, records=[]))
            group['rows'].append(row); group['texts'][rid] = text
            group['records'].append(dict(path='src/'+rid+'.c', file='sources/src/'+rid+'.c',
                before=sha(source), after=hashlib.sha256(text.encode()).hexdigest(), admission=outcome))
    return groups, rejected, ordinary, native_seen


def generate(lanes, output, proof_root=None):
    groups, rejected, ordinary, native_seen = collect(lanes)
    if not native_seen:
        return 3
    if not groups:
        raise ValueError('no admitted native members: ' + json.dumps(rejected))
    output = output.resolve()
    if not output.is_relative_to(ROOT/'work/native_lane'):
        raise ValueError('output must stay under work/native_lane')
    if (output/'delivery').exists() or (output/'plan.json').exists():
        raise ValueError('output already exists; use a fresh output directory')
    output.mkdir(parents=True, exist_ok=True)
    kitlib.bootstrap(output)
    records = []; scores = {}; protected = {}; windows = []; fingerprints = {}
    # Bind guard inputs before scoring; require exactly the same context afterwards.
    for key, group in groups.items():
        m = group['module']; g = N.gate()
        certificate = safe(ROOT, 'ledger/modules/overlay_'+key+'.json')
        if not certificate.is_file():
            raise ValueError('missing certificate for renewal: ' + key)
        cert = json.loads(certificate.read_text())
        if cert.get('module') != key or not cert.get('reviewer') or cert['reviewer'] == 'pending':
            raise ValueError('native module needs orchestrator certification first: ' + key)
        fingerprints[key] = N.fingerprint(group['rows'][0])
        starts = [m['source'], *m['headers'], *(a['source'] for a in g.all_members(m)),
                  *(d['declaration'] for d in m['imports'] if d['kind']=='runtime_data')]
        names = set(g.closure(ROOT, starts)) | set(m['review_inputs'])
        names.update(['config/overlays/modules.json', 'ledger/rows.jsonl',
            'ledger/modules.jsonl', 'ledger/splits/overlay_modules.build.json',
            'config/overlays/'+m['container']+'.rowbase.jsonl', 'config/names.tsv',
            'tools/gate/overlay_module_gate.py', 'tools/lanes/native_package_apply.py',
            'tools/lanes/package_proofs.py',
            'tools/lanes/lane_admission.py', 'tools/lanes/lanekit/native_member.py',
            'tools/lanes/land_packages.py', 'tools/build/gate_all.py',
            'tools/fidelity/certify_overlay_module.py', 'tools/lanes/certify_batch.py',
            str(certificate.relative_to(ROOT))])
        wins = g.affected_windows(m, ROOT)
        if not wins:
            raise ValueError('native module has no production window: ' + key)
        names.update(wins); windows.extend(wins)
        protected.update({name:sha(safe(ROOT,name)) for name in sorted(names)})
        result = N.score_batch(group['rows'], group['texts'], m)
        scores[key] = {k:v for k,v in result.items() if k != 'artifacts'}
        print(json.dumps(dict(module=key, exact=result.get('exact'), artifacts=result.get('artifacts'))), flush=True)
        if not result.get('exact') or not result.get('module_exact') or not result.get('owned_data_exact') or result.get('other_members_changed'):
            raise ValueError('native TU refused: ' + key + '; evidence: ' + str(result.get('artifacts')))
        if N.fingerprint(group['rows'][0]) != fingerprints[key]:
            raise ValueError('native context changed during packaging: ' + key)
        records.extend(group['records'])
    # Selected sources are separately guarded before/after in files.json.
    for rec in records:
        protected.pop(rec['path'], None)
    if any(sha(safe(ROOT,name)) != value for name,value in protected.items()):
        raise ValueError('protected inputs changed during packaging')
    if any(sha(safe(ROOT,rec['path'])) != rec['before'] for rec in records):
        raise ValueError('selected source changed during packaging')
    head = subprocess.check_output(['git','rev-parse','HEAD'],cwd=ROOT,text=True).strip()
    with tempfile.TemporaryDirectory(prefix='native_delivery_',dir=output) as temp:
        delivery = Path(temp)/'delivery'; delivery.mkdir()
        for group in groups.values():
            for rec in group['records']:
                dest = delivery/rec['file']; dest.parent.mkdir(parents=True,exist_ok=True)
                rid = rec['path'][4:-2]; dest.write_text(group['texts'][rid])
        shutil.copy2(ROOT/'tools/lanes/native_package_apply.py',delivery/'apply.py')
        manifest = dict(schema='azure-clean.lane-package.v1', package='native_members', head=head,
            reviewer='pending', mutates=[r['path'] for r in records],
            certificates_requiring_renewal=sorted(groups), production_windows=sorted(set(windows)),
            module_fingerprints=fingerprints, protected_inputs=protected,
            admission=[dict(row=r['path'][4:-2], **r['admission']) for r in records],
            rejected=rejected, deferred_ordinary=ordinary)
        def write(name, doc):
            (delivery/name).write_text(json.dumps(doc,indent=2,sort_keys=True)+'\n')
        write('files.json',[{k:v for k,v in r.items() if k != 'admission'} for r in records])
        write('manifest.json',manifest); write('scores.json',scores)
        if proof_root is not None:
            from proof_receipts import export_module
            proof_root=Path(proof_root).resolve()
            # The lane may prepare a complete post-apply proof root separately;
            # never substitute scorer diagnostics for canonical certificates.
            for rec in records:
                if sha(safe(proof_root,rec['path']))!=rec['after']:raise ValueError('proof-root candidate differs: '+rec['path'])
            proofs=[]
            for key in sorted(groups):
                name='diagnostics/portable_proofs/'+key
                export_module(proof_root,key,delivery/name)
                proofs.append(dict(kind='overlay-module',target=key,directory=name))
            write('proofs.json',proofs)
        write('tests.json',dict(unit_modules=['tools.tests.test_land_packages'],
                               discover_patterns=['test_land_packages.py','test_native_package.py']))
        paths = [p for p in delivery.rglob('*') if p.is_file()]
        write('package.sha256.json',{str(p.relative_to(delivery)):sha(p) for p in paths})
        delivery.rename(output/'delivery')
    plan = dict(version=1, reviewer='pending', commit=False, isolated=True,
        commit_message='Admit native members through complete module TUs: '+', '.join(sorted(groups)),
        packages=[dict(entry='delivery/apply.py', args=[], live_flag=True)],
        unit_modules=['tools.tests.test_land_packages'], discover_patterns=['test_land_packages.py','test_native_package.py'],
        certificate_timeout=1800, allow_census_change=False)
    (output/'plan.json').write_text(json.dumps(plan,indent=2)+'\n')
    print(json.dumps(dict(result='NATIVE_PACKAGE_READY', output=str(output), modules=sorted(groups),
                         members=len(records), reviewer='pending', deferred_ordinary=ordinary)),flush=True)
    return 0


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument('lanes', nargs='+'); ap.add_argument('--output', type=Path)
    ap.add_argument('--proof-root',type=Path,help='already applied and canonically certified lane root; carry its full module proofs')
    ap.add_argument('--if-native', action='store_true')
    args = ap.parse_args(argv)
    try:
        lanes = [lane_path(name) for name in args.lanes]
        if len(lanes) > 1 and args.output is None:
            raise ValueError('multiple lanes require --output')
        result = generate(lanes, args.output or lanes[0], args.proof_root)
        if result == 3 and not args.if_native:
            raise ValueError('no staged native module members')
        return result
    except (OSError, ValueError, KeyError, RuntimeError, subprocess.SubprocessError) as e:
        print('NATIVE_PACKAGE_REFUSED: '+str(e),file=sys.stderr,flush=True)
        return 1


if __name__ == '__main__':
    raise SystemExit(main())
