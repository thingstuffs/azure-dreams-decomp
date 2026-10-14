#!/usr/bin/env python3
"""Relative JP source referee; compile only in --workspace, never update the tree.

Single: jp_dual.py --repo ROOT --workspace LANE --pairs pairs.jsonl ROW A.c B.c
Batch:  jp_dual.py --repo ROOT --workspace LANE --pairs pairs.jsonl --batch jobs.jsonl
Each pairing supplies row, symbol, jp_bin and confidence. Batch objects contain
row and texts [{label, path}] (or textA/textB). Paths are relative to workspace.
This measures masked instruction similarity, not source authenticity or US exactness.
"""
from __future__ import annotations
import argparse
import concurrent.futures
import fcntl
import hashlib
import json
import os
from pathlib import Path
import shlex
import subprocess
import sys
import threading
import time
sys.dont_write_bytecode = True
try:
    from .jp_dual_core import c89_comments, distance, masked, words
except ImportError:
    from jp_dual_core import c89_comments, distance, masked, words

VERSION = 'jp-dual-1-mask4'
CELLS = {'272': ('2.7.2', '2.56'), '263': ('2.6.3', '2.21')}
MEMORY_WIDTH = {32: 1, 36: 1, 40: 1, 33: 2, 37: 2, 41: 2,
                35: 4, 43: 4, 49: 4, 57: 4, 34: 4, 38: 4, 42: 4, 46: 4}


def sha(data):
    return hashlib.sha256(data).hexdigest()


def ranges(bs):
    result = []
    for b in sorted(bs):
        if result and result[-1][1] == b:
            result[-1][1] = b + 1
        else:
            result.append([b, b + 1])
    return result


def frame_metrics(ws):
    frame = next((0x10000 - (w & 65535) for w in ws
                  if w >> 16 == 0x27bd and w & 0x8000), 0)
    cov = set()
    addresses = []
    for i, w in enumerate(ws):
        op, rs, rt, imm = w >> 26, (w >> 21) & 31, (w >> 16) & 31, w & 65535
        imm = imm - 65536 if imm & 32768 else imm
        if rs == 29 and op in MEMORY_WIDTH:
            cov.update(range(max(0, imm), min(frame, imm + MEMORY_WIDTH[op])))
        if op == 9 and rs == 29 and rt != 29:
            addresses.append({'instruction': i, 'offset': imm, 'register': rt})
    unref = set(range(frame)) - cov
    orphan = {b for b in unref if b >= 16}
    return {'frame_size': frame, 'instruction_count': len(ws),
            'unreferenced_frame_bytes': len(unref), 'unreferenced_layout': ranges(unref),
            'unreferenced_ge16': len(orphan), 'unreferenced_ge16_layout': ranges(orphan),
            'stack_addresses_taken': addresses,
            'orphan_interpretation': 'upper_bound_address_taken_locals' if addresses else 'direct_sp_reference_scan'}


def verdict(results, labels):
    """A strict dual-cell winner; disagreement and failures remain inconclusive."""
    if len(labels) < 2:
        return {'preference': None, 'status': 'metrics_only'}
    if len(labels) > 2:
        per_cell = {}
        winners = set(labels)
        totals = {label: 0 for label in labels}
        for cell in CELLS:
            if any(results[label].get(cell, {}).get('status') != 'ok' for label in labels):
                return {'preference': None, 'status': 'incomplete_cells', 'cell_verdicts': per_cell}
            distances = {label: results[label][cell]['distance'] for label in labels}
            best = min(distances.values())
            cell_winners = {label for label in labels if distances[label] == best}
            winners &= cell_winners
            per_cell[cell] = {'preferences': sorted(cell_winners), 'distances': distances}
            for label in labels:
                totals[label] += distances[label]
        if not winners:
            return {'preference': 'tie', 'status': 'compiler_disagreement', 'margin': 0,
                    'cell_verdicts': per_cell, 'aggregate_distances': totals}
        if len(winners) > 1:
            return {'preference': 'tie', 'status': 'tie', 'margin': 0,
                    'cell_verdicts': per_cell, 'aggregate_distances': totals}
        winner = next(iter(winners))
        return {'preference': winner, 'status': 'agreement',
                'margin': min(total for label, total in totals.items() if label != winner) - totals[winner],
                'cell_verdicts': per_cell, 'aggregate_distances': totals}
    a, b = labels
    per_cell, margins = {}, []
    for cell in CELLS:
        aa, bb = results[a].get(cell, {}), results[b].get(cell, {})
        if aa.get('status') != 'ok' or bb.get('status') != 'ok':
            return {'preference': None, 'status': 'incomplete_cells', 'cell_verdicts': per_cell}
        margin = bb['distance'] - aa['distance']
        margins.append(margin)
        per_cell[cell] = {'preference': a if margin > 0 else b if margin < 0 else 'tie',
                          'margin_A_over_B': margin,
                          'normalized_margin': margin / max(aa['target_words'], 1)}
    if min(margins) < 0 < max(margins):
        return {'preference': 'tie', 'status': 'compiler_disagreement', 'margin': 0,
                'signed_margin_A_over_B': sum(margins), 'cell_verdicts': per_cell}
    margin = sum(margins)
    return {'preference': a if margin > 0 else b if margin < 0 else 'tie',
            'status': 'agreement' if margin else 'tie', 'margin': abs(margin),
            'signed_margin_A_over_B': margin, 'cell_verdicts': per_cell}


class Referee:
    def __init__(self, repo, workspace, pairs, include=None, timeout=120):
        self.repo = Path(repo).resolve()
        self.workspace = Path(workspace).resolve()
        self.workspace.mkdir(parents=True, exist_ok=True)
        self.include = Path(include).resolve() if include else self.repo / 'include'
        self.tmp = self.workspace / 'tmp'
        self.tmp.mkdir(exist_ok=True)
        self.cache = self.workspace / 'out_big/jp_dual_cache'
        self.cache.mkdir(parents=True, exist_ok=True)
        (self.cache.parent / '.ignore').write_text('*\n')
        self.pairs = pairs
        self.timeout = timeout
        self.env = dict(os.environ, PYTHONDONTWRITEBYTECODE='1', TMPDIR=str(self.tmp))
        for k in ('AZURE_MASPSX', 'AZURE_MASPSX_COMPANION'):
            self.env.pop(k, None)
        sys.path.insert(0, str(self.repo / 'tools'))
        from fidelity.objread import read_elf
        self.read_elf = read_elf
        # Include closure and executables participate in cache identity.
        self.include_sha = sha(b''.join(str(p.relative_to(self.include)).encode() + b'\0' +
                                       p.read_bytes() for p in sorted(self.include.rglob('*')) if p.is_file()))
        self.identities = {}
        for cell, (compiler, assembler) in CELLS.items():
            d = self.repo / 'toolchain/compilers' / ('gcc-' + compiler)
            files = [d / 'gcc', d / 'cpp', d / 'cc1', self.repo / 'tools/build/ccproc.py']
            files += sorted((self.repo / 'tools/maspsx').glob('*.py'))
            self.identities[cell] = sha(b''.join(str(p).encode() + b'\0' + p.read_bytes() for p in files))
        gas = subprocess.run(['mipsel-linux-gnu-as', '--version'], cwd=self.workspace,
                             env=self.env, capture_output=True, text=True, check=True).stdout
        self.gas_identity = gas
        self._thread_locks = {}
        self._guard = threading.Lock()

    def path(self, p):
        p = Path(p)
        return p if p.is_absolute() else self.workspace / p

    def run(self, argv, cwd, input=None):
        p = subprocess.run(['nice', '-n', '10', *map(str, argv)], cwd=cwd, env=self.env,
                           input=input, text=True, capture_output=True, timeout=self.timeout,
                           errors='replace')
        with (cwd / 'build.log').open('a') as f:
            f.write(p.stdout + p.stderr)
        if p.returncode:
            raise RuntimeError((p.stderr or p.stdout)[-2000:])
        return p.stdout

    def compile(self, row, source, cell):
        compiler, assembler = CELLS[cell]
        # Overlay JP cells always use -O2 -G0. Resident SLUS carries recorded
        # row flags, including -fno-strength-reduce where used by the A/B harness.
        flags = row.get('jp_flags') or ['-G0']
        if isinstance(flags, str):
            flags = shlex.split(flags)
        asflags = shlex.split(row.get('row_asflags') or '')
        if any(x.startswith('--retail-') for x in asflags):
            return {'status': 'error', 'error': 'keyed assembler controls are not JP-family cells'}
        dropped_asflags = [x for x in asflags if x.startswith('--aspsx-version=')]
        asflags = [x for x in asflags if x not in dropped_asflags]
        key = sha(json.dumps([VERSION, source, row['symbol'], flags, asflags, compiler, assembler,
                              self.include_sha, self.identities[cell], self.gas_identity,
                              sha(Path(__file__).read_bytes()),
                              sha(Path(__file__).with_name('jp_dual_core.py').read_bytes())]).encode())
        out = self.cache / key
        with self._guard:
            lock = self._thread_locks.setdefault(key, threading.Lock())
        with lock:
            out.mkdir(exist_ok=True)
            with (out / 'lock').open('w') as fd:
                fcntl.flock(fd, fcntl.LOCK_EX)
                receipt = out / 'compile.json'
                if receipt.exists() and (out / 'function.bin').exists():
                    rec = json.loads(receipt.read_text())
                    if rec.get('status') == 'ok' and rec.get('key') == key:
                        rec['cache_hit'] = True
                        return rec
                t0 = time.monotonic()
                text = c89_comments(source)
                (out / 'input.c').write_text(text)
                d = self.repo / 'toolchain/compilers' / ('gcc-' + compiler)
                commands = []
                def run(argv, inp=None):
                    commands.append(list(map(str, argv)))
                    return self.run(argv, out, inp)
                rec = {'status': 'error', 'key': key, 'cell': cell, 'compiler': compiler,
                       'flags': flags, 'aspsx': assembler, 'source_sha256': sha(source.encode()),
                       'include_sha256': self.include_sha, 'toolchain_sha256': self.identities[cell],
                       'cache_dir': str(out.relative_to(self.workspace)),
                       'comment_normalization': source != text, 'cache_hit': False,
                       'row_aspsx_version_replaced': dropped_asflags}
                try:
                    run([d / 'gcc', '-B' + str(d) + '/', '-E', '-O2', *flags,
                         '-I' + str(self.include), '-w', 'input.c', '-o', 'input.i'])
                    run([d / 'cc1', 'input.i', '-quiet', '-O2', *flags, '-w', '-o', 'cc1.s'])
                    proc = run([sys.executable, self.repo / 'tools/build/ccproc.py'],
                               (out / 'cc1.s').read_text())
                    (out / 'sectioned.s').write_text(proc)
                    run([self.repo / '.venv/bin/python', self.repo / 'tools/maspsx/maspsx.py',
                         '--aspsx-version=' + assembler, '--dont-force-G0', '--run-assembler',
                         '--gnu-as-path=mipsel-linux-gnu-as', '-I' + str(self.include.parent), '-I' + str(self.repo),
                         '-I' + str(self.include), '-EL', '-march=r3000', '-G8', *asflags,
                         '-o', 'output.o'], proc)
                    obj = self.read_elf((out / 'output.o').read_bytes())
                    sym = obj.symbols.get(row['symbol'])
                    emitted_symbol = row['symbol']
                    if not sym:
                        # Older trade texts can predate the current symbol rename.
                        # Only an explicitly registered alias may replace it.
                        for alias in (row.get('symbol_before_repair'), row.get('func'), row['row'].split('/')[-1]):
                            if alias and obj.symbols.get(alias, (None, None, None, 0))[2] == 'func':
                                sym = obj.symbols[alias]
                                emitted_symbol = alias
                                break
                    if not sym:
                        funcs = [(name, value) for name, value in obj.symbols.items() if value[2] == 'func' and value[3]]
                        if len(funcs) == 1:
                            emitted_symbol, sym = funcs[0]
                    if not sym or sym[2] != 'func' or not sym[3]:
                        raise RuntimeError('expected function symbol absent: ' + row['symbol'])
                    if obj.unknown:
                        raise RuntimeError('unknown ELF relocations: ' + repr(obj.unknown))
                    sec, start, _, size = sym
                    blob = obj.sections[sec][start:start + size]
                    if len(blob) != size or size % 4:
                        raise RuntimeError('truncated or unaligned function')
                    rs = [(off - start, typ) for sn, off, typ, target, add in obj.relocs
                          if sn == sec and start <= off < start + size]
                    seq, why = masked(words(blob), rs)
                    (out / 'function.bin').write_bytes(blob)
                    rec.update(status='ok', binary_sha256=sha(blob), symbol=emitted_symbol,
                               symbol_resolution='registered' if emitted_symbol == row['symbol'] else 'registered_alias_or_sole_emitted_function',
                               masked_words=seq, mask_reasons=why, relocations=rs,
                               **frame_metrics(words(blob)))
                except (RuntimeError, ValueError, OSError, subprocess.TimeoutExpired) as e:
                    rec['error'] = str(e)[-2000:]
                rec['seconds'] = round(time.monotonic() - t0, 3)
                (out / 'commands.json').write_text(json.dumps(commands, indent=2) + '\n')
                receipt.write_text(json.dumps(rec) + '\n')
                return rec

    def metric(self, row, source, cell):
        rec = self.compile(row, source, cell)
        result = {k: v for k, v in rec.items() if k not in ('masked_words', 'mask_reasons', 'relocations')}
        if rec['status'] == 'ok':
            jp = self.path(row['jp_bin']).read_bytes()
            if sha(jp) != row['jp_sha256']:
                raise ValueError('JP window hash changed for ' + row['row'])
            result.update(distance(rec['masked_words'], masked(words(jp))[0]))
            result['jp_metrics'] = frame_metrics(words(jp))
        return result

    def comparison_key(self, job):
        row = self.pairs[job['row']]
        if row.get('jp_bin') and sha(self.path(row['jp_bin']).read_bytes()) != row['jp_sha256']:
            raise ValueError('JP window hash changed for ' + job['row'])
        texts = job.get('texts') or [{'label': 'A', 'path': job['textA']},
                                    {'label': 'B', 'path': job['textB']}]
        sources = []
        for i, item in enumerate(texts):
            source = item['text'] if 'text' in item else self.path(item['path']).read_text()
            sources.append([item.get('label', chr(65 + i)), sha(source.encode())])
        return sha(json.dumps([VERSION, job['row'], row.get('jp_sha256'), row.get('symbol'),
                               row.get('jp_flags'), row.get('row_asflags'), sources,
                               self.include_sha, self.identities, self.gas_identity,
                               sha(Path(__file__).read_bytes()),
                               sha(Path(__file__).with_name('jp_dual_core.py').read_bytes())], sort_keys=True).encode())

    def compare(self, job, executor):
        rid = job['row']
        row = self.pairs[rid]
        if row.get('status') not in ('paired', 'structural_hold'):
            return dict(job, status='unpaired', verdict={'preference': None, 'status': 'unpaired'})
        texts = job.get('texts') or [{'label': 'A', 'path': job['textA']},
                                    {'label': 'B', 'path': job['textB']}]
        labels = [x.get('label', chr(65 + i)) for i, x in enumerate(texts)]
        if len(set(labels)) != len(labels) or 'tie' in labels:
            raise ValueError('text labels must be unique and may not be tie')
        tasks, sources = {}, []
        for label, item in zip(labels, texts):
            source = item.get('text') if 'text' in item else self.path(item['path']).read_text()
            sources.append({'label': label, 'path': item.get('path'), 'sha256': sha(source.encode())})
            for cell in CELLS:
                tasks[label, cell] = executor.submit(self.metric, row, source, cell)
        results = {label: {} for label in labels}
        for (label, cell), future in tasks.items():
            try:
                results[label][cell] = future.result()
            except Exception as e:
                results[label][cell] = {'status': 'error', 'error': str(e)}
        return {'row': rid, 'job_id': job.get('job_id'), 'kind': job.get('kind'), 'status': 'measured',
                'comparison_key': self.comparison_key(job),
                'pairing_confidence': row['confidence'], 'pairing_method': row['method'],
                'structural_flags': row.get('structural_flags', []), 'sources': sources,
                'texts': results, 'verdict': verdict(results, labels)}


def load_pairs(path):
    text = Path(path).read_text()
    rows = json.loads(text) if text.lstrip().startswith('[') else [json.loads(s) for s in text.splitlines() if s.strip()]
    return {r.get('row', r.get('id')): r for r in rows}


def summary(result):
    lines = [result['row']]
    for label, cells in result.get('texts', {}).items():
        for cell, r in cells.items():
            if r['status'] == 'ok':
                lines.append(f"  {label} {cell}: distance={r['distance']} normalized={r['normalized_distance']:.4f} "
                             f"frame={r['frame_size']} unreferenced>=16={r['unreferenced_ge16']} "
                             f"layout={r['unreferenced_ge16_layout']} instructions={r['instruction_count']}")
            else:
                lines.append(f"  {label} {cell}: ERROR {r.get('error')}")
    v = result['verdict']
    lines.append(f"JP prefers {v.get('preference') or 'undetermined'} | margin={v.get('margin', 'n/a')} "
                 f"| {v['status']}")
    return '\n'.join(lines)


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument('--repo', type=Path, required=True)
    ap.add_argument('--workspace', type=Path, default=Path.cwd())
    ap.add_argument('--pairs', type=Path, required=True)
    ap.add_argument('--include', type=Path)
    ap.add_argument('--batch', type=Path)
    ap.add_argument('--out', type=Path, help='JSONL output inside workspace (incremental, resumable)')
    ap.add_argument('--jobs', type=int, default=6)
    ap.add_argument('--timeout', type=int, default=120)
    ap.add_argument('--resume', action='store_true')
    ap.add_argument('row', nargs='?')
    ap.add_argument('texts', nargs='*')
    args = ap.parse_args()
    if not 1 <= args.jobs <= 6:
        ap.error('--jobs must be between 1 and 6')
    pairs = load_pairs(args.pairs)
    referee = Referee(args.repo, args.workspace, pairs, args.include, args.timeout)
    if args.batch:
        jobs = [json.loads(s) for s in args.batch.read_text().splitlines() if s.strip()]
    elif args.row and args.texts:
        jobs = [{'row': args.row, 'texts': [{'label': chr(65 + i), 'path': p}
                                           for i, p in enumerate(args.texts)]}]
    else:
        ap.error('supply ROW TEXT... or --batch')
    output = referee.path(args.out).resolve() if args.out else None
    if output and not output.is_relative_to(referee.workspace):
        ap.error('--out must be inside workspace')
    seen = set()
    if args.resume and output and output.exists():
        for s in output.read_text().splitlines():
            r = json.loads(s)
            if r.get('comparison_key'):
                seen.add(((r.get('job_id') or r['row']), r['comparison_key']))
    if output:
        output.parent.mkdir(parents=True, exist_ok=True)
    def resumable(job):
        try:
            return ((job.get('job_id') or job['row']), referee.comparison_key(job)) in seen
        except (KeyError, ValueError, OSError):
            return False
    # Coordinators never execute compilers themselves; the shared worker pool
    # caps active compiler pipelines at --jobs, even across overlapping rows.
    with concurrent.futures.ThreadPoolExecutor(max_workers=args.jobs) as executor, \
            concurrent.futures.ThreadPoolExecutor(max_workers=3) as coordinators:
        with output.open('a' if args.resume else 'w') if output else open(os.devnull, 'w') as f:
            pending = {coordinators.submit(referee.compare, job, executor): job for job in jobs
                       if not resumable(job)}
            for future in concurrent.futures.as_completed(pending):
                job = pending[future]
                try:
                    result = future.result()
                except Exception as e:
                    result = {'row': job['row'], 'job_id': job.get('job_id'), 'status': 'error',
                              'error': str(e), 'verdict': {'preference': None, 'status': 'error'}}
                if output:
                    f.write(json.dumps(result) + '\n')
                    f.flush()
                print(summary(result), flush=True)


if __name__ == '__main__':
    main()
