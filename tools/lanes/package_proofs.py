"""Explicit package-proof deferral to a production land_packages transaction.

Packages call run_proof for an independently reviewed, named proof. Guards,
source/ledger writes and lane receipts always remain in apply.py. Unknown kinds,
standalone use, previews and bare LAND_SKIP_PACKAGE_PROOF=1 run the original
command. There is no subprocess interception or command guessing.
"""
import hashlib
import json
import os
from pathlib import Path
import subprocess

SKIP_ENV = 'LAND_SKIP_PACKAGE_PROOF'
CONTEXT_ENV = 'LAND_PACKAGE_PROOF_CONTEXT'
KINDS = {'overlay-window', 'overlay-module', 'slus-image', 'levels'}


def sha(path):
    return hashlib.sha256(Path(path).read_bytes()).hexdigest()


def validate_claim(kind, target):
    if kind not in KINDS:
        return False
    if not isinstance(target, str) or not target:
        raise ValueError('proof target must be a nonempty string')
    if kind == 'overlay-window':
        p = Path(target)
        if len(p.parts) != 3 or p.parts[:2] != ('config', 'overlays') or not p.name.endswith('.overlay.yaml'):
            raise ValueError('deferred window is not a production config: ' + target)
    elif kind == 'overlay-module':
        if any(c not in 'abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_-' for c in target):
            raise ValueError('invalid deferred module key: ' + target)
    elif target != {'slus-image': 'slus', 'levels': 'ledger/levels.jsonl'}[kind]:
        raise ValueError('invalid deferred proof target: ' + target)
    return True


def defer_proof(root, package, kind, target, lane_receipts=(), *, dry_run=False):
    """True only after recording an obligation that the lander must discharge.

    lane_receipts are package-relative immutable lane evidence; their current
    hashes are recorded for audit, never accepted as production certificates.
    """
    if dry_run:return False
    # Proof-carrying packages can reuse their complete canonical evidence in
    # preflight/standalone applies as well as production. Old packages have no
    # sealed index and retain their original command. A diagnostic is not a
    # window or module proof, and a stale receipt always falls back.
    production=os.environ.get(SKIP_ENV)=='1' and bool(os.environ.get(CONTEXT_ENV))
    if not production and kind in ('overlay-window','overlay-module'):
        import proof_receipts as P
        for candidate in P.package_receipts(package):
            if (candidate['kind'],candidate['target'])!=(kind,target):continue
            try:
                with P.input_snapshot():
                    P.verify(root,candidate['directory'],expected_kind=kind,expected_target=target)
                    if kind=='overlay-module':P.import_module(root,candidate['directory'])
                return True
            except (OSError,ValueError,KeyError,TypeError,subprocess.SubprocessError):
                pass
    if os.environ.get(SKIP_ENV) != '1' or not os.environ.get(CONTEXT_ENV):return False
    if not validate_claim(kind, target):
        return False
    root, package = Path(root).resolve(), Path(package).resolve()
    context_path = Path(os.environ[CONTEXT_ENV])
    context = json.loads(context_path.read_text())
    if (context.get('schema') != 1 or context.get('mode') != 'production'
            or context.get('root') != str(root) or context.get('package') != str(package)
            or not context.get('transaction')):
        raise ValueError('package proof context differs from this invocation')
    entry = Path(context['entry'])
    if entry.parent != package or sha(entry) != context['entry_sha256']:
        raise ValueError('package entry changed during proof deferral')
    receipts = {}
    for name in lane_receipts:
        rel = Path(name)
        if rel.is_absolute() or '..' in rel.parts or not rel.parts:
            raise ValueError('unsafe lane receipt path')
        p = package / rel
        if not p.resolve().is_relative_to(package):
            raise ValueError('lane receipt escapes package')
        receipts[name] = sha(p)
    claim = dict(kind=kind, target=target, lane_receipts=receipts)
    path = context_path.parent / 'deferred.json'
    doc = json.loads(path.read_text())
    if doc.get('context_sha256') != sha(context_path) or not isinstance(doc.get('proofs'), list):
        raise ValueError('package proof receipt context changed')
    if claim not in doc['proofs']:
        doc['proofs'].append(claim)
        temp = path.with_suffix('.tmp')
        temp.write_text(json.dumps(doc, sort_keys=True) + '\n')
        temp.replace(path)
    return True


def run_proof(root, package, kind, target, argv, *, lane_receipts=(), env=None):
    # Guard/write/dry-run decisions belong to the caller, before reaching here.
    if defer_proof(root, package, kind, target, lane_receipts):
        return None
    return subprocess.run(argv, cwd=root, env=env, check=True)
