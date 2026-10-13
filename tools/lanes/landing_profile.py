#!/usr/bin/env python3
"""Summarize existing landing JSONL logs without executing any repository tool.

Command completion events are the timing authority. Diagnostic gate-timing
events repeat the same duration and must not be charged twice. Uninstrumented
snapshot/quarantine and rollback intervals are reported as bounds, never as
measurements of one operation. Partial and failed runs remain visible.
"""
import argparse
from collections import defaultdict
from datetime import datetime
import json
import math
from pathlib import Path
import re
import statistics

TERMINALS = {'COMMITTED', 'PROVED_NO_COMMIT', 'PREFLIGHT_PASS', 'STOP', 'PREVIEW_INCOMPLETE'}
SUCCESS = {'COMMITTED', 'PROVED_NO_COMMIT', 'PREFLIGHT_PASS'}


def stamp(event):
    value = event.get('at')
    return datetime.fromisoformat(value.replace('Z', '+00:00')) if value else None


def category(step):
    if step in {'admission', 'snapshot', 'quarantine', 'restore', 'transaction-cleanup'}:
        return step
    if step == 'gate-all':
        return 'gate_all'
    if step.startswith('timing-'):
        return 'timing_windows'
    if step == 'certify-all':
        return 'certify_batch'
    if step == 'certificate-final-validation':
        return 'certificate_final_validation'
    if step.startswith('unit-'):
        return 'unit_tests'
    if step in {'levels', 'fast-levels'}:
        return 'levels'
    if step in {'status', 'fast-status'}:
        return 'status'
    if step.startswith('SLUS-'):
        return 'SLUS'
    if step in {'registry', 'index', 'graph', 'fast-graph', 'mk-ovl', 'mk-gate'}:
        return 'regeneration'
    if step == 'commit':
        return 'commit'
    return 'mutation_and_other_commands'


def read_output(log, event):
    # Relocated logs work without touching the original checkout/log directory.
    path = log.parent / Path(event.get('output', '')).name
    if path.is_file() and path.stat().st_size <= 4 * 1024 * 1024:
        return path.read_text(errors='replace')
    return ''


def profile(log):
    log = Path(log)
    events, warnings = [], []
    for number, line in enumerate(log.read_text().splitlines(), 1):
        if not line.lstrip().startswith('{'):
            continue
        try:
            event = json.loads(line)
            if not isinstance(event, dict):
                raise ValueError('event is not an object')
            events.append(event)
        except ValueError as exc:
            warnings.append(f'line {number}: {exc}')
    terminal = next((e for e in reversed(events) if e.get('step') in TERMINALS), {})
    timed = [e for e in events if 'seconds' in e and 'rc' in e]
    totals = defaultdict(float)
    for event in timed:
        value = event['seconds']
        if isinstance(value, bool) or not isinstance(value, (int, float)) or not math.isfinite(value) or value < 0:
            raise ValueError('invalid command seconds: ' + str(event.get('step')))
        totals[category(event['step'])] += value
    dated = [e for e in events if stamp(e)]
    wall = (stamp(dated[-1]) - stamp(dated[0])).total_seconds() if len(dated) > 1 else None
    gate = next((e for e in reversed(events) if e.get('step') == 'gate-timing'), {})
    bounds = {}
    starts = [e for e in events if e.get('step') == 'preflight']
    ends = [e for e in events if e.get('step') == 'certificate-proof-preservation']
    if starts and ends and stamp(starts[0]) and stamp(ends[0]):
        bounds['snapshot_plus_quarantine'] = (stamp(ends[0]) - stamp(starts[0])).total_seconds()
    if terminal.get('step') == 'STOP' and isinstance(terminal.get('rollback'), dict):
        preceding = [e for e in events if e is not terminal and 'rc' in e and stamp(e)]
        if preceding and stamp(terminal):
            bounds['post_command_diagnostics_plus_restore'] = (stamp(terminal) - stamp(preceding[-1])).total_seconds()
    gate_counts, certificate = None, None
    for event in events:
        if 'command' not in event:
            continue
        output = read_output(log, event)
        if event.get('step') == 'gate-all':
            match = re.search(r'(\d+) windows to gate \((\d+) up to date\), (\d+) workers', output)
            if match:
                gate_counts = dict(zip(('built', 'cached', 'workers'), map(int, match.groups())))
        if event.get('step') == 'certify-all':
            for line in output.splitlines():
                try:
                    value = json.loads(line)
                except ValueError:
                    continue
                if value.get('result') == 'PASS' and 'certificates' in value:
                    certificate = {'renewed': len(value['certificates']), 'retained': len(value.get('retained', [])),
                                   'validated': value.get('validated'), 'workers': value.get('workers')}
    return {'log': log.name, 'terminal': terminal.get('step', 'INCOMPLETE'),
            'complete': terminal.get('step') in SUCCESS and not warnings,
            'gate_mode': gate.get('mode'), 'gate_reasons': gate.get('reasons', []),
            'observed_wall_seconds': wall, 'command_seconds': round(sum(totals.values()), 3),
            'unattributed_seconds': round(wall - sum(totals.values()), 3) if wall is not None else None,
            'seconds_by_category': {k: round(v, 3) for k, v in sorted(totals.items())},
            'steps': [{'step': e['step'], 'seconds': e['seconds'], 'rc': e['rc']} for e in timed],
            'interval_bounds_seconds': bounds, 'gate_windows': gate_counts, 'certificates': certificate,
            'head': terminal.get('head'), 'warnings': warnings}


def markdown(runs):
    successful = [r for r in runs if r['complete'] and r['gate_mode']]
    out = ['# Landing timings', '', 'Seconds from command completions; wall starts at the first logged event.', '',
           '| log | mode | wall min | gate min | cert min | levels/status min | terminal |',
           '|---|---|---:|---:|---:|---:|---|']
    for run in runs:
        seconds = run['seconds_by_category']
        wall = run['observed_wall_seconds']
        out.append('| {} | {} | {} | {:.2f} | {:.2f} | {:.2f} | {} |'.format(
            run['log'], run['gate_mode'] or 'screen/unknown', f'{wall / 60:.2f}' if wall is not None else 'unknown',
            seconds.get('gate_all', 0) / 60, seconds.get('certify_batch', 0) / 60,
            (seconds.get('levels', 0) + seconds.get('status', 0)) / 60, run['terminal']))
    for mode in sorted({r['gate_mode'] for r in successful}):
        selected = [r for r in successful if r['gate_mode'] == mode]
        out.extend(['', f'## {mode}: {len(selected)} completed runs', '',
                    '| category | median sec | range sec |', '|---|---:|---:|'])
        for key in sorted({k for r in selected for k in r['seconds_by_category']}):
            values = [r['seconds_by_category'].get(key, 0) for r in selected]
            out.append(f'| {key} | {statistics.median(values):.3f} | {min(values):.3f}–{max(values):.3f} |')
    return '\n'.join(out) + '\n'


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('logs', nargs='+', type=Path)
    parser.add_argument('--json', type=Path)
    parser.add_argument('--markdown', type=Path)
    args = parser.parse_args()
    runs = [profile(path) for path in args.logs]
    if args.json:
        args.json.write_text(json.dumps({'schema': 1, 'runs': runs}, indent=2) + '\n')
    result = markdown(runs)
    if args.markdown:
        args.markdown.write_text(result)
    else:
        print(result, end='')


if __name__ == '__main__':
    main()
