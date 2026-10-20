#!/usr/bin/env python3
"""Run bounded production window checks with validated immutable recipe tables.

No gate source or authority file is edited. GateAll.run_window still computes
its ordinary pre/post input digests, compiles and compares the complete window.
An additional whole-preparation dependency digest brackets the snapshot.
"""
import argparse
import hashlib
import json
import os
from pathlib import Path
import re
import sys

try:
    from .combined import preparation_digest
    from .prepare import load_gate, linklist_snapshot
except ImportError:
    from combined import preparation_digest
    from prepare import load_gate, linklist_snapshot


def main():
    root = Path(__file__).resolve().parents[2]
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--window', action='append', required=True)
    parser.add_argument('--output', type=Path, required=True)
    args = parser.parse_args()
    windows = list(dict.fromkeys(args.window))
    if not 1 <= len(windows) <= 60 or any(not re.fullmatch('[a-z0-9_]+', w) for w in windows):
        raise ValueError('select 1..60 production window names')
    output = args.output.resolve()
    if output == root or not output.is_relative_to(root):
        raise ValueError('output must be a private subdirectory')
    output.mkdir(parents=True, exist_ok=True)
    (output/'.ignore').write_text('*\n')
    sys.path.insert(0, str(root/'tools'))
    from build import gate_all
    gate = load_gate(root)
    if gate_all.ROOT != root or gate_all.B != gate.ROOT:
        raise ValueError('gate view must be this private root')
    gate_all._GATE_WORKER = gate
    gate_all.JOURNAL = output/'gate.jsonl'
    original = gate_all.worker_output
    def snapshot_output(path):
        with linklist_snapshot(gate):
            lines = original(path)
        (output/(path.name.removesuffix('.overlay.yaml')+'.log')).write_text('\n'.join(lines)+'\n')
        return lines
    gate_all.worker_output = snapshot_output
    before = preparation_digest(root, None)
    results = []
    try:
        os.chdir(gate_all.B)
        for window in windows:
            path = gate_all.B/'config/overlays'/(window+'.overlay.yaml')
            if not path.is_file():
                raise ValueError('production window missing: '+window)
            record = gate_all.run_window(path, in_process=True)
            results.append(record)
            gate_all.journal(record)
            print(window,record['result'],record['secs'],flush=True)
    finally:
        gate_all.worker_output = original
    after = preparation_digest(root, None)
    proof = dict(method='unchanged GateAll.run_window and worker_output; validated immutable link/module tables',
                 inputs_before_sha256=before, inputs_after_sha256=after,
                 wrapper_sha256=hashlib.sha256(Path(__file__).read_bytes()).hexdigest(),
                 windows=results, result='MATCH' if before == after and all(r['result']=='MATCH' for r in results) else 'ERROR')
    (output/'snapshot_proof.json').write_text(json.dumps(proof,indent=2)+'\n')
    if proof['result'] != 'MATCH':
        raise RuntimeError('production window checks or snapshot input binding failed')


if __name__ == '__main__':
    main()
