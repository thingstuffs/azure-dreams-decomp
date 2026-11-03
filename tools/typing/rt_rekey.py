#!/usr/bin/env python3
"""Re-key a runtime merge onto current source identities in a NEW directory.

    rt_rekey.py --graph GRAPH --rt OLD_MERGE --linemap lines.json.gz --out NEW_MERGE
    rt_rekey.py --root CURRENT --old-root FROZEN --graph GRAPH --rt OLD_MERGE --out NEW_MERGE

Line maps come from rt_linemap.py. Use --linemap none only for current-source
recordings. Counts and cell labels are preserved. Unmapped lines keep their old
number and are counted in rekey_summary.json; this is identity repair, not new
runtime evidence. Unchanged files are linked to the original merge, which must
remain available. Existing output directories are always refused.
"""
from __future__ import annotations

import argparse
import collections
import csv
import gzip
import json
import os
from pathlib import Path
import shutil
import tempfile
import sys

sys.path.insert(0, str(Path(__file__).resolve().parents[2]))
from tools.headers import cscan

from rt_linemap import LineMap, build
import type_flow_solve as flow

csv.field_size_limit(1 << 30)


def table_rows(path):
    op = gzip.open if path.suffix == '.gz' else open
    with op(path, 'rt') as stream:
        yield from csv.DictReader(stream, delimiter='\t')


class Rekey:
    def __init__(self, graph, mapping, runtime):
        self.graph, self.mapping = graph, mapping
        self.stats = collections.Counter()
        self.current = set()
        self.definitions = collections.defaultdict(list)
        self.files = collections.defaultdict(set)
        for definitions in graph.functions.values():
            for definition in definitions:
                file, name = definition['file'], definition['name']
                self.current.add((file, name))
                self.definitions[file].append((definition['line'], name))
                self.files[name].add(file)
        for definitions in self.definitions.values():
            definitions.sort()
        self.anchors = collections.defaultdict(set)
        sites = runtime / 'sites.tsv'
        if sites.exists():
            for row in table_rows(sites):
                line = mapping.line(row['file'], int(row['line'] or 0))
                if line:
                    self.anchors[(row['file'], row['function'])].add(line)
        self.renames = {}
        self.spans = {}
        self.calls = collections.defaultdict(set)
        self.indirect = set()
        for call in graph.calls:
            key = (call['file'], call['caller'].split('@')[0], call['line'])
            if call['mode'] == 'direct':
                self.calls[key].add(call['callee'])
            else:
                self.indirect.add(key)

    def line(self, file, old, table):
        new = self.mapping.line(file, old)
        if new is None:
            self.stats[table + '_lines_unmapped'] += 1
            return old
        if new != old:
            self.stats[table + '_lines_moved'] += 1
        return new

    def function(self, file, name):
        key = (file, name)
        if key in self.current or not file.startswith(('src/', 'include/')):
            return name
        if key not in self.renames:
            candidates = set()
            if file not in self.spans:
                self.spans[file] = []
                root = getattr(self.graph, 'root', None)
                source = root / file if root else None
                if source and source.is_file():
                    for item in cscan.scan(source.read_text(errors='replace')).items:
                        if item.body:
                            for declaration in item.decls:
                                if declaration.is_function and (file, declaration.name) in self.current:
                                    self.spans[file].append((item.line, item.end_line, declaration.name))
            matched = True
            for line in self.anchors.get(key, ()):
                enclosing = {function for first, last, function in self.spans[file] if first <= line <= last}
                if len(enclosing) != 1:
                    matched = False
                candidates.update(enclosing)
            # Every mapped anchor must lie inside the same current function body.
            replacement = next(iter(candidates)) if matched and len(candidates) == 1 else name
            self.renames[key] = replacement
            if replacement != name:
                self.stats['renamed_functions'] += 1
        return self.renames[key]

    def fn_arg(self, row):
        row['function'] = self.function(row['file'], row['function'])
        return row

    def site(self, row):
        self.fn_arg(row)
        row['line'] = str(self.line(row['file'], int(row['line'] or 0), 'site'))
        return row

    def callsite(self, row):
        file = row['caller_file']
        row['caller'] = self.function(file, row['caller'])
        row['callee'] = self.function(row['callee_file'], row['callee'])
        line = self.line(file, int(row['line'] or 0), 'callsite')
        row['line'] = str(line)
        keys = [(file, row['caller'], line + delta) for delta in (0, -1, 1)]
        near = set().union(*(self.calls.get(key, set()) for key in keys))
        if any(key in self.indirect for key in keys):
            return row
        recorded = flow.fn_key(self.graph, row['callee'], row['callee_file'])
        if near and recorded not in near:
            if len(near) == 1:
                replacement = next(iter(near))
                name, _, defining_file = replacement.partition('@')
                files = {defining_file} if defining_file else self.files.get(name, set())
                if len(files) == 1:
                    row['callee'], row['callee_file'] = name, next(iter(files))
                    self.stats['callsite_callee_respelled'] += 1
                else:
                    self.stats['callsite_callee_unmatched'] += 1
            else:
                self.stats['callsite_callee_unmatched'] += 1
        return row

    def pointee(self, row):
        self.site(row)
        if row['value_class'] == 'func':
            file, separator, name = row['value_target'].rpartition(':')
            if separator:
                row['value_target'] = file + ':' + self.function(file, name)
        return row

    def kinds(self, value):
        if isinstance(value, list):
            return [self.kinds(item) for item in value]
        if not isinstance(value, dict):
            return value
        result = {key: self.kinds(item) for key, item in value.items()}
        if 'file' in value and 'function' in value:
            result['function'] = self.function(value['file'], value['function'])
            if value.get('line') is not None:
                result['line'] = self.line(value['file'], int(value['line']), 'kind')
        return result


def rewrite_table(source, target, transform):
    op = gzip.open if source.suffix == '.gz' else open
    with op(source, 'rt') as reader, op(target, 'wt') as output:
        rows = csv.DictReader(reader, delimiter='\t')
        writer = csv.DictWriter(output, rows.fieldnames, delimiter='\t', lineterminator='\n')
        writer.writeheader()
        count = 0
        for row in rows:
            writer.writerow(transform(row))
            count += 1
    return count


def rekey(graph, mapping, runtime, output):
    runtime, output = Path(runtime).resolve(), Path(output).absolute()
    if output.exists() or output.is_symlink():
        raise ValueError('output must be a new directory')
    if output.resolve().is_relative_to(runtime):
        raise ValueError('output must be outside the input merge')
    output.parent.mkdir(parents=True, exist_ok=True)
    temporary = Path(tempfile.mkdtemp(prefix=output.name + '.tmp-', dir=output.parent))
    try:
        mapper = Rekey(graph, mapping, runtime)
        for name, transform in (('fn_args.tsv', mapper.fn_arg), ('sites.tsv', mapper.site),
                                ('callsite_args.tsv.gz', mapper.callsite), ('pointees.tsv.gz', mapper.pointee)):
            if (runtime / name).exists():
                mapper.stats[name + '_rows'] = rewrite_table(runtime / name, temporary / name, transform)
        kinds = runtime / 'kinds_rt.json'
        if kinds.exists():
            with kinds.open() as stream:
                data = mapper.kinds(json.load(stream))
            (temporary / kinds.name).write_text(json.dumps(data))
        for source in runtime.iterdir():
            target = temporary / source.name
            if not target.exists() and source.name != 'rekey_summary.json':
                target.symlink_to(source.resolve(), target_is_directory=source.is_dir())
        summary = dict(version=1, source=str(runtime), stats=dict(mapper.stats),
                       changed_files=len(mapping.maps), missing_files=sorted(mapping.missing))
        (temporary / 'rekey_summary.json').write_text(json.dumps(summary, indent=2) + '\n')
        # rename is atomic; do not overwrite an output created during this run.
        if output.exists():
            raise ValueError('output appeared during rekey')
        os.rename(temporary, output)
        return summary
    except BaseException:
        shutil.rmtree(temporary)
        raise


def main(argv=None):
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--root', type=Path, default=Path(__file__).resolve().parents[2])
    parser.add_argument('--graph', required=True, type=Path)
    parser.add_argument('--rt', required=True, type=Path)
    parser.add_argument('--out', required=True, type=Path)
    source = parser.add_mutually_exclusive_group(required=True)
    source.add_argument('--linemap', help='rt_linemap JSON[.gz], or none for current-source rows')
    source.add_argument('--old-root', type=Path)
    args = parser.parse_args(argv)
    mapping = (build(args.old_root, args.root) if args.old_root else
               LineMap() if args.linemap == 'none' else LineMap.read(args.linemap))
    print(json.dumps(rekey(flow.Graph(args.graph), mapping, args.rt, args.out), indent=2))


if __name__ == '__main__':
    main()
