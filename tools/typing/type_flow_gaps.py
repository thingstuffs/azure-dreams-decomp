#!/usr/bin/env python3
"""Classify every unproven/contradicted cast in type-flow bridge components.

    type_flow_gaps.py --graph G --solve SOLVE --rt MERGE --out GAPS

Optional --linemap lines.json.gz diagnoses drift before rekeying. --ledger adds
coverage status to capture gaps. Keys include defining files; H9 cells already
include argument arithmetic. Outputs are gaps.tsv, ranked gap_keys.tsv and
summary.json. They are analysis artifacts, never source transactions.
"""
from __future__ import annotations

import argparse
import collections
import csv
import json
from pathlib import Path

from rt_linemap import LineMap
from rt_rekey import table_rows
import type_flow_solve as flow

GAP_COLUMNS = ['component', 'comp_net', 'comp_unproven', 'comp_wrong', 'cause', 'node', 'function', 'file',
               'line', 'edge', 'dst', 'off', 'cast', 'new', 'observation', 'detail']
KEY_COLUMNS = ['observation', 'cause', 'casts_proved', 'components', 'sole_gap_of', 'net_if_whole',
               'blocked_net', 'component_list']
BLOCKING = {'unproven', 'wrong', 'view_member_missing'}


def node_function(node):
    if node.startswith('P:'):
        return node[2:].rpartition('#')[0]
    if node.startswith('L:'):
        return node[2:].split(':')[0]
    return ''


class Classifier:
    def __init__(self, graph, runtime, runtime_dir, mapping=None, ledger=None):
        self.g, self.rt = graph, runtime
        self.mapping = mapping or LineMap()
        self.args = collections.defaultdict(list)
        self.calls = collections.defaultdict(list)
        self.ran, self.accesses = set(), set()
        directory = Path(runtime_dir)
        for row in table_rows(directory / 'fn_args.tsv'):
            identity = (row['file'], row['function'])
            self.args[identity].append(row)
            self.ran.add(identity)
        path = directory / 'callsite_args.tsv.gz'
        if path.exists():
            for row in table_rows(path):
                row['nline'] = self.mapping.line(row['caller_file'], int(row['line'] or 0))
                identity = (row['caller_file'], row['caller'])
                self.calls[identity].append(row)
                self.ran.add(identity)
                self.ran.add((row['callee_file'], row['callee']))
        path = directory / 'pointees.tsv.gz'
        if path.exists():
            for row in table_rows(path):
                self.ran.add((row['file'], row['function']))
                self.accesses.add((row['file'], self.mapping.line(row['file'], int(row['line'] or 0))))
        self.ledger = {}
        if ledger:
            for row in table_rows(Path(ledger)):
                self.ledger[(row.get('file', ''), row['function'])] = row.get('status', '')
        self.arg_edges = collections.defaultdict(list)
        for edge in graph.edges:
            if edge['k'] == 'arg' and edge.get('src'):
                self.arg_edges[edge['src']].append(edge)

    def identity(self, key, fallback=''):
        definition = self.g.fn_def(key)
        if definition:
            return definition['file'], definition['name']
        name, _, file = (key or '').partition('@')
        return file or fallback, name

    def coverage(self, identity):
        return self.ledger.get(identity, self.ledger.get(('', identity[1]), ''))

    def cells(self, cast, component):
        site = self.rt.edge_cells(dict(k=cast['edge'], dst=cast['dst'], fn=cast['fn'], line=cast['line']))
        site = collections.Counter({cell: n for cell, n in (site or {}).items() if cell[0] in ('heap', 'ram')})
        cells = site or self.rt.pointer_cells(cast['src'])
        if not cells and cast['src'] in component:
            seed = component[cast['src']].get('seed')
            cells = collections.Counter()
            for node, info in component.items():
                if info['st'] in ('ok', 'retype') and info.get('seed') == seed:
                    cells.update(self.rt.pointer_cells(node))
        offset = cast.get('cell_off', 0 if site else cast['off']) or 0
        return cells, offset

    def classify(self, cast, component):
        source = cast['src']
        function = node_function(source) or cast['fn']
        identity = self.identity(function, cast['file'])
        if cast['evidence'] != 'unproven':
            return 'contradicted', cast['evidence'], identity
        cells, offset = self.cells(cast, component)
        if cells:
            missing = [cell[:2] + (cell[2] + offset,) for cell in cells
                       if not self.rt.cell_votes(cell[:2] + (cell[2] + offset,))
                       and not (cell[0] == 'heap' and cell[1] in self.rt.pooled and cell[2] + offset == 0
                                and self.g.same(cast['cast'], 'ObjectNodeHeader *'))]
            if missing:
                detail = cast['cast'] + ' at ' + ', '.join('%s:%s%+d' % cell for cell in missing)
                return 'vote_gap', detail, identity
            return 'evidence_mismatch', 're-solve with the current graph and runtime tables', identity
        callee, arg = '', None
        if cast['edge'] == 'arg' and cast['dst'].startswith('P:'):
            callee, _, index = cast['dst'][2:].rpartition('#')
            if index.isdigit():
                arg = int(index)
        ambiguous = [key for key in (function, cast['fn'], callee) if self.g.ambiguous_function(key)]
        if ambiguous:
            return 'ambiguous_name', ', '.join(sorted(set(ambiguous))), identity
        caller_id = self.identity(cast['fn'], cast['file'])
        if arg is not None:
            rows = [row for row in self.calls[caller_id] if int(row['arg']) == arg]
            callee_id = self.identity(callee)
            same = [row for row in rows if (row['callee_file'], row['callee']) == callee_id]
            line = cast['line'] or 0
            if any(row['nline'] is not None and abs(row['nline'] - line) <= flow.SITE_LINE_SLACK for row in same):
                return 'line_drift', 'H9 old lines ' + ','.join(sorted({row['line'] for row in same})), identity
            other = [row for row in rows if row['nline'] is not None and abs(row['nline'] - line) <= 1
                     and (row['callee_file'], row['callee']) != callee_id]
            if other:
                return 'respell', 'H9 callee ' + ','.join(sorted({row['callee'] for row in other})), identity
        if source.startswith('P:'):
            index = source.rpartition('#')[2]
            rows = [row for row in self.args[identity] if row['arg'] == index]
            if rows and not any(cell[0] in ('heap', 'ram') for row in rows for cell, _ in flow.parse_values(row['values'])):
                return 'observed_scalar', rows[0]['values'][:120], identity
            if rows:
                return 'holder_unlabelled', 'entry rows have pointers but the graph has no matching holder', identity
            # File drift/port implementations may share a unique name; never count a duplicate in another file as execution.
            others = [(file, name) for file, name in self.args if name == identity[1] and (file, name) != identity]
            if others and not self.g.ambiguous_function(identity[1]):
                cause = 'port_impl' if all(not file.startswith('src/') for file, _ in others) else 'respell'
                return cause, 'entry rows under ' + ','.join(file for file, _ in others), identity
        if identity[1] and not identity[1].startswith('<') and identity not in self.ran:
            return 'fn_never_run', 'ledger:' + self.coverage(identity), identity
        if source.startswith('L:') and not self.arg_edges.get(source):
            return 'local_unlabelled', 'no argument edge labels this local', identity
        if (cast['file'], cast['line']) in self.accesses:
            return 'holder_unlabelled', 'accesses on the line do not identify one holder', identity
        return 'site_not_reached', '%s:%s' % (cast['file'], cast['line']), identity


def analyze(graph, runtime, runtime_dir, solve_dir, output, mapping=None, ledger=None, verdicts=('bridge',)):
    classifier = Classifier(graph, runtime, runtime_dir, mapping, ledger)
    rows, components = [], {}
    solve_dir, output = Path(solve_dir), Path(output)
    output.mkdir(parents=True, exist_ok=True)
    for row in table_rows(solve_dir / 'components.tsv'):
        if row['verdict'] not in verdicts:
            continue
        cid = row['component']
        data = json.loads((solve_dir / 'components' / (cid + '.json')).read_text())
        casts = [cast for cast in data['casts'] if cast['evidence'] in BLOCKING]
        wrong = sum(cast['evidence'] != 'unproven' for cast in casts)
        components[cid] = dict(net=int(row['net']), wrong=wrong, gaps=len(casts))
        for cast in casts:
            cause, detail, identity = classifier.classify(cast, data['comp'])
            if cause == 'fn_never_run':
                observation = 'run %s::%s' % identity
            elif cause == 'site_not_reached':
                observation = 'reach %s:%s' % (cast['file'], cast['line'])
            elif cause == 'vote_gap':
                observation = 'typed view ' + detail
            elif cause == 'local_unlabelled':
                observation = 'label ' + cast['src']
            else:
                observation = 'tool:' + cause
            rows.append(dict(component=cid, comp_net=row['net'], comp_unproven=len(casts) - wrong, comp_wrong=wrong,
                             cause=cause, node=cast['src'], function=identity[1], file=cast['file'], line=cast['line'],
                             edge=cast['edge'], dst=cast['dst'], off=cast['off'], cast=cast['cast'],
                             new=int(bool(cast['new'])), observation=observation, detail=detail))
    flow.write_tsv(output / 'gaps.tsv', rows, GAP_COLUMNS)
    keys = collections.defaultdict(list)
    per_component = collections.defaultdict(set)
    for row in rows:
        keys[row['observation']].append(row)
        per_component[row['component']].add(row['observation'])
    ranked = []
    for observation, group in keys.items():
        ids = {row['component'] for row in group}
        sole = {cid for cid in ids if not components[cid]['wrong'] and per_component[cid] == {observation}}
        ranked.append(dict(observation=observation, cause=group[0]['cause'], casts_proved=len(group), components=len(ids),
                           sole_gap_of=len(sole), net_if_whole=sum(components[cid]['net'] for cid in sole),
                           blocked_net=sum(components[cid]['net'] for cid in ids), component_list=' '.join(sorted(ids))))
    ranked.sort(key=lambda row: (row['net_if_whole'], -row['casts_proved'], row['observation']))
    flow.write_tsv(output / 'gap_keys.tsv', ranked, KEY_COLUMNS)
    falling = {cid for cid, value in components.items() if value['net'] < 0}
    summary = dict(components=len(components), falling_components=len(falling), blocking_casts=len(rows),
                   casts_by_cause=dict(collections.Counter(row['cause'] for row in rows)),
                   falling_casts_by_cause=dict(collections.Counter(row['cause'] for row in rows if row['component'] in falling)))
    (output / 'summary.json').write_text(json.dumps(summary, indent=2) + '\n')
    return summary


def main(argv=None):
    parser = argparse.ArgumentParser(description=__doc__)
    for option in ('graph', 'solve', 'rt', 'out'):
        parser.add_argument('--' + option, required=True, type=Path)
    parser.add_argument('--linemap', help='rt_linemap JSON[.gz]; omitted/none means current lines')
    parser.add_argument('--ledger', type=Path)
    parser.add_argument('--verdicts', nargs='+', default=['bridge'])
    args = parser.parse_args(argv)
    mapping = LineMap.read(args.linemap) if args.linemap and args.linemap != 'none' else LineMap()
    graph = flow.Graph(args.graph)
    print(json.dumps(analyze(graph, flow.Runtime(args.rt, graph), args.rt, args.solve, args.out,
                             mapping, args.ledger, args.verdicts), indent=2))


if __name__ == '__main__':
    main()
