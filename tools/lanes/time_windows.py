#!/usr/bin/env python3
"""Time unchanged production gates concurrently, retaining MATCH and deadlines.

Run as a helper in a private process group, like certify_batch. A failure stops
the entire group before its caller can roll back. This does not publish gate
receipts, update a journal, certify modules, or replace gate_all.
"""
import argparse
from concurrent.futures import ThreadPoolExecutor, as_completed
import json
import os
from pathlib import Path
import re
import signal
import subprocess
import sys
import threading
import time
import yaml


def prove(root, configs, workers, timeout, log_dir):
    if not configs or len(set(configs)) != len(configs):
        raise ValueError('nonempty, unique timing configs required')
    if not 1 <= workers <= 4 or timeout <= 0:
        raise ValueError('one to four workers and a positive timeout required')
    destinations = set()
    for config in configs:
        path = Path(config)
        if path.is_absolute() or '..' in path.parts or not str(path).startswith('config/overlays/') or not str(path).endswith('.overlay.yaml'):
            raise ValueError('production timing config required: ' + config)
        if not (root / path).is_file():
            raise ValueError('missing timing config: ' + config)
        cfg = yaml.safe_load((root / path).read_text())
        destination = (root / cfg['standalone_build']['work_dir'] / cfg['name']).resolve()
        if not destination.is_relative_to(root.resolve()) or any(
                destination.is_relative_to(other) or other.is_relative_to(destination)
                for other in destinations):
            raise ValueError('timing gate output escapes or overlaps: ' + config)
        destinations.add(destination)
    # The basename names the gate's work directory; never schedule it twice.
    if len({Path(c).name for c in configs}) != len(configs):
        raise ValueError('duplicate timing window basename')
    log_dir.mkdir(parents=True, exist_ok=True)
    launching = threading.Lock()
    stopping = threading.Event()
    started = time.monotonic()

    def run(config):
        output = log_dir / (Path(config).stem + '.log')
        command = [sys.executable, 'tools/overlay_local_gate.py', '--config', config, '--clean']
        start = time.monotonic()
        print(json.dumps({'step': 'timing-window-start', 'config': config, 'command': command,
                          'output': str(output)}), flush=True)
        with output.open('w') as f:
            with launching:
                if stopping.is_set():
                    raise RuntimeError('timing gates cancelled before launch')
                child = subprocess.Popen(command, cwd=root, stdout=f, stderr=subprocess.STDOUT)
            rc = child.wait(timeout=timeout)
        elapsed = time.monotonic() - start
        result = {'config': config, 'seconds': round(elapsed, 3), 'rc': rc, 'log': str(output)}
        print(json.dumps({'step': 'timing-window-result', **result}), flush=True)
        if rc:
            raise RuntimeError('timed window failed: ' + config)
        if elapsed >= timeout:
            raise RuntimeError('window exceeds certification timeout: ' + config)
        if not re.search(r'^MATCH\b', output.read_text(), re.M):
            raise RuntimeError('timed window lacks MATCH: ' + config)
        return result

    with ThreadPoolExecutor(max_workers=workers) as pool:
        futures = [pool.submit(run, config) for config in configs]
        try:
            results = [future.result() for future in as_completed(futures)]
        except BaseException as exc:
            for future in futures:
                future.cancel()
            print(json.dumps({'step': 'timing-window-refusal', 'error': str(exc)}), file=sys.stderr, flush=True)
            with launching:
                stopping.set()
                signal.signal(signal.SIGTERM, signal.SIG_DFL)
                os.killpg(os.getpgrp(), signal.SIGTERM)
            raise
    result = {'result': 'PASS', 'workers': workers, 'timeout': timeout,
              'seconds': round(time.monotonic() - started, 3), 'windows': sorted(results, key=lambda r: r['config'])}
    (log_dir / 'summary.json').write_text(json.dumps(result, indent=2) + '\n')
    print(json.dumps(result), flush=True)
    return result


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--root', required=True, type=Path)
    parser.add_argument('--config', action='append', required=True)
    parser.add_argument('--workers', type=int, default=2)
    parser.add_argument('--timeout', type=int, default=1800)
    parser.add_argument('--log-dir', required=True, type=Path)
    args = parser.parse_args()
    if not 1 <= args.workers <= 4 or args.timeout < 1:
        parser.error('one to four workers and a positive timeout required')
    if os.getpgrp() != os.getpid():
        os.setsid()

    def interrupted(signum, frame):
        raise RuntimeError('timing interrupted by signal ' + str(signum))

    signal.signal(signal.SIGTERM, interrupted)
    try:
        prove(args.root.resolve(), args.config, args.workers, args.timeout, args.log_dir.resolve())
    except Exception as exc:
        print(str(exc), file=sys.stderr, flush=True)
        signal.signal(signal.SIGTERM, signal.SIG_DFL)
        os.killpg(os.getpgrp(), signal.SIGTERM)
        return 1
    return 0


if __name__ == '__main__':
    raise SystemExit(main())
