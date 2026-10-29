#!/usr/bin/env python3
"""Capture/compare every physical TU in a layout map at its registered recipe.

Run --snapshot FILE on the B17 source tree, apply the reviewed layout transaction,
then run --compare FILE.  Objects stay in a temporary build directory; the JSONL
receipt records only hashes and relative paths.  Non-home native members are
refused so that one physical TU is never silently proved as two row compiles.
"""
from __future__ import annotations

import argparse
import hashlib
import json
import os
import re
from pathlib import Path
import subprocess
import sys
import tempfile
from contextlib import contextmanager

from layout_apply import path, rows, plan
from layout_dependencies import consumer_paths, include_parents
from layout_identity import canonical, digest, reassemble
from source_layout import ROOT, registry, row_relative, slus_source


def maps(table, inline=False):
    data = rows(table)
    if not data:
        raise ValueError('empty tree')
    first = data[0]
    if {'current_path', 'proposed_path'} <= first.keys():
        old_key, new_key = 'current_path', 'proposed_path'
    elif {'source_tu', 'proposed_tu'} <= first.keys():
        old_key, new_key = 'source_tu', 'proposed_tu'
    else:
        raise ValueError('tree needs current_path/proposed_path or source_tu/proposed_tu')
    result = {}
    for row in data:
        old, new = row.get(old_key, ''), row.get(new_key, '')
        # An in-place inline (layout_apply --inline) names its TU with an identity row.
        if not old or not new or (old == new and not inline):
            continue
        path(old, 'src'); path(new, 'src')
        if old in result and result[old] != new:
            raise ValueError('conflicting source path: ' + old)
        result[old] = new
    if not result:
        raise ValueError('tree has no moves')
    return result


def recipes(root):
    root = Path(root).resolve()
    from gate import overlay_module_gate as G
    from slus_module_context import modules as slus_modules
    reg = registry(root)
    physical = {}
    member_paths = set()
    for module in G.load_modules(root):
        cell, flags = G.module_recipe(module)
        physical[module['source']] = {'kind': 'overlay_module', 'container': module['container'],
                                      'cell': cell, 'flags': list(flags), 'asflags': []}
        # An inlined member's source is the physical TU itself, not a separate native fragment.
        member_paths.update(x['source'] for x in G.all_members(module) if x['source'] != module['source'])
    from slus_module_context import module_anchor, partition_context
    from slus_partitions import load_plan
    partition_plan = load_plan(root / 'config/slus_partitions.json')
    partition_parents = {p['id']: p for p in partition_plan}
    partition_owners = {part['module'] for p in partition_plan for part in p['parts']}
    for module in slus_modules(root):
        source = slus_source(module['source'], root).relative_to(root).as_posix()
        row = reg[module_anchor(module, root)['id']]
        recipe = module['recipe']
        physical[source] = {'kind': 'slus_module', 'container': 'slus', 'cell': row['cell'],
                            'flags': row['flags'].split(), 'asflags': (row.get('row_asflags') or '').split(),
                            'row_id': row['id']}
        if module['name'] in partition_owners:
            physical[source].update(cell=recipe['ccver'], flags=recipe['ccflags'].split(),
                                    asflags=recipe['asflags'].split(), slus_unit=module['source'])
        member_paths.update(slus_source(x['source'], root).relative_to(root).as_posix()
                            for x in module['members']
                            if slus_source(x['source'], root).relative_to(root).as_posix() != source)
    for rid, row in reg.items():
        if row.get('source_row'):
            continue
        source = row_relative(row, root)
        if source in member_paths or source in physical:
            continue
        physical[source] = {'kind': 'row', 'container': row['container'], 'cell': row['cell'],
                            'flags': row['flags'].split(), 'asflags': (row.get('row_asflags') or '').split(),
                            'row_id': rid}
        if rid in partition_parents:
            physical[source]['slus_unit'] = partition_parents[rid]['source']
    return physical, member_paths


@contextmanager
def compilation_input(root, rel, recipe, workspace):
    """Select the registered physical stream, including generated SLUS partitions."""
    root = Path(root).resolve()
    if 'slus_unit' not in recipe:
        yield root / rel
        return
    from slus_module_context import compilation_sources
    row = registry(root)[recipe['row_id']]
    # A partition-only destination is anchored by its real logical parent.
    candidate = root / row_relative(row, root)
    units = compilation_sources(row, candidate, workspace, root)
    selected = [u for u in units if u['source'] == recipe['slus_unit']]
    if len(selected) != 1:
        raise ValueError('missing or ambiguous physical partition: ' + rel)
    unit = selected[0]
    expected = dict(ccver=recipe['cell'], ccflags=' '.join(recipe['flags']), asflags=' '.join(recipe['asflags']))
    if unit['recipe'] != expected:
        raise ValueError('physical partition recipe drift: ' + rel)
    yield unit['cfile']


def command(args, *, cwd, data=None, env=None):
    result = subprocess.run(list(map(str, args)), cwd=cwd, input=data, capture_output=True, env=env)
    if result.returncode:
        raise ValueError('compile command failed: ' + result.stderr.decode(errors='replace')[-500:])
    return result.stdout


LOCAL_LABEL = re.compile(rb'\$L[0-9]+\b')


def normalize_local_labels(stream):
    """Rename every compiler-local `$L<n>` label to `$L`; nothing else changes."""
    return LOCAL_LABEL.sub(b'$L', stream)


_PRODUCTION = {}
EVIDENCE_ENV = ('MASPSX_NORETURN_FILE', 'MASPSX_SIBCALL_FILE')


def production_recipes(root):
    """{physical source: [linked production compile]} from the root's generated build graph, else None.

    One entry per current overlay recipe that an image links and that compiles the source itself through
    cc.sh (row TUs and native modules; placement copies compile a derived file and SLUS rows have their own
    capture path): recipe id, cell, cc flags, maspsx flags, maspsx evidence files (the recipe's noreturn /
    sibcall tables) and the registry rows its image units place.
    Cached per process until build/.state/index.json changes."""
    root = Path(root).resolve()
    index = root / 'build/.state/index.json'
    if not index.is_file():
        return None
    st = index.stat()
    stamp = (st.st_mtime_ns, st.st_size)
    hit = _PRODUCTION.get(root)
    if hit and hit[0] == stamp:
        return hit[1]
    build_tools = str(Path(__file__).resolve().parent / 'build')
    if build_tools not in sys.path:
        sys.path.insert(0, build_tools)
    import affected
    graph = affected.Graph(root)
    linked = set()
    for spec in graph.images.values():
        linked.update(spec['recipes'])
    table = {}
    for rid, spec in sorted(graph.recipes.items()):
        if spec['_family'] != 'overlay' or spec.get('projection') or rid not in linked \
                or not spec.get('wrapper', '').endswith('cc.sh') or not spec.get('source'):
            continue
        args = list(spec.get('args') or ()) + ['', '', '']
        table.setdefault(spec['source'], []).append(dict(
            id=rid, cell=args[0], flags=args[1].split(), asflags=args[2].split(),
            evidence={k: v for k, v in sorted((spec.get('env') or {}).items()) if k in EVIDENCE_ENV},
            rows=sorted(graph.recipe_rows.get(rid, ())), module='module' in spec))
    _PRODUCTION[root] = (stamp, table)
    return table


def production_compiles(root, rel, recipe):
    """The compiles a capture of `rel` must reproduce: [{id, ids, cell, flags, asflags, evidence}], primary first.

    The build links every linked production recipe of the source; each distinct (cell, cc flags, maspsx
    flags) is one compile.  The primary is the recipe placing the proof map's own row (a native module:
    its module recipe).  A source without a linked production recipe (no built graph, an unlinked facade)
    falls back to the proof map's registry recipe."""
    table = production_recipes(root)
    linked = (table or {}).get(rel, [])
    if recipe['kind'] == 'overlay_module':
        linked = [r for r in linked if r['module']] or linked
    if not linked:
        return [dict(id=None, ids=[], cell=recipe['cell'], flags=list(recipe['flags']),
                     asflags=list(recipe['asflags']), evidence={})]
    row = recipe.get('row_id')
    linked = sorted(linked, key=lambda r: (row not in r['rows'], r['module'] != (recipe['kind'] == 'overlay_module'),
                                           r['id']))
    out = {}
    for r in linked:
        evidence = r.get('evidence') or {}
        key = (r['cell'], tuple(r['flags']), tuple(r['asflags']), tuple(sorted(evidence.items())))
        if key not in out:
            out[key] = dict(id=r['id'], ids=[], cell=r['cell'], flags=list(r['flags']), asflags=list(r['asflags']),
                            evidence=dict(evidence))
        out[key]['ids'].append(r['id'])
    return list(out.values())


def capture_one(root, rel, recipe):
    root = Path(root).resolve()
    source = root / rel
    if not source.is_file():
        raise ValueError('missing physical TU: ' + rel)
    if b'__FILE__' in source.read_bytes() or b'__LINE__' in source.read_bytes():
        raise ValueError('path-sensitive C macro: ' + rel)
    (root / 'build_ovl').mkdir(exist_ok=True)
    with tempfile.TemporaryDirectory(prefix='layout-compile-', dir=root / 'build_ovl') as td:
        workspace = Path(td)
        if recipe['container'] == 'slus':
            import verify
            row = registry(root)[recipe['row_id']]
            row = dict(row, cell=recipe['cell'], flags=' '.join(recipe['flags']),
                       row_asflags=' '.join(recipe['asflags']))
            with compilation_input(root, rel, recipe, workspace / 'context') as cfile:
                out, error = verify._compile_slus_source(row, cfile, workspace / 'raw', root / 'include', root)
            if error:
                raise ValueError(rel + ': ' + error)
            raw = out.read_bytes()
            stream = (out.parent / 'a.proc.s').read_bytes()
            asflags, evidence, variants, others = recipe['asflags'], {}, None, []
        else:
            # The build's own compiles of this source (cell, cc flags, maspsx flags and evidence tables of each
            # linked production recipe): proving a different object than the one linked proves nothing.
            compiles = production_compiles(root, rel, recipe)
            streams, objects = {}, {}
            for n, c in enumerate(compiles):
                key = (c['cell'], tuple(c['flags']))
                if key not in streams:
                    cc = root / 'toolchain/compilers' / ('gcc-' + c['cell'])
                    asm = workspace / ('source%d.s' % n)
                    flags = c['flags']
                    if '-O2' not in flags:
                        flags = ['-O2', *flags]
                    command([cc / 'gcc', '-B' + str(cc) + '/', '-S', *flags,
                             '-I' + str(root / 'include'), '-w', source, '-o', asm], cwd=root)
                    streams[key] = command([sys.executable, root / 'tools/build/ccproc.py',
                                            '--names-tsv', root / 'config/names.tsv'], cwd=root,
                                           data=asm.read_bytes())
                raw_dir = workspace / ('raw%d' % n)
                raw_dir.mkdir()
                # A stable family census is sufficient for before/after object
                # identity; the scoped gate remains responsible for retail MATCH.
                reassemble(root, streams[key], raw_dir, recipe['container'], c['asflags'], c['evidence'])
                objects[n] = (raw_dir / 'canonical.o').read_bytes()
            primary = compiles[0]
            stream, raw = streams[(primary['cell'], tuple(primary['flags']))], objects[0]
            asflags, evidence = primary['asflags'], primary['evidence']
            variants = None
            if len(compiles) > 1:
                variants = {rid: digest(objects[n]) for n, c in enumerate(compiles) for rid in c['ids']}
            others = [streams[k] for k in sorted(streams) if streams[k] is not stream]
        canonical_stream = canonical(stream)
        # Another cell/cc flags compiles another stream: the assembly digests cover every stream.
        listed = [canonical_stream] + [canonical(s) for s in others]
        clean_dir = workspace / 'normalized'
        clean_dir.mkdir()
        clean_sha = reassemble(root, canonical_stream, clean_dir,
                               recipe['container'] if recipe['container'] != 'slus' else 'main',
                               asflags if recipe['container'] != 'slus' else (), evidence)
    result = {'source': rel, 'kind': recipe['kind'], 'recipe': recipe,
              'raw_sha256': digest(raw), 'canonical_assembly_sha256': digest(b''.join(listed)),
              'label_normalized_assembly_sha256': digest(b''.join(map(normalize_local_labels, listed))),
              'canonical_object_sha256': clean_sha}
    if variants:
        # Several distinct production compiles: each linked recipe's raw object (recipe id -> sha).  raw_sha256
        # is the primary's; one stream through different maspsx flags is covered by the assembly digests.
        result['variant_raw_sha256'] = variants
    return result


def run(root, table, *, snapshot=None, compare=None, headers=None, inline=None, results=None):
    root = Path(root).resolve()
    mapping = maps(table, inline=bool(inline))
    physical, members = recipes(root)
    prior = {}
    tables_sha256 = [digest(Path(p).read_bytes()) if p else None for p in (table, headers, inline)]
    reviewed_sha = None
    if compare:
        for line in Path(compare).read_text().splitlines():
            record = json.loads(line)
            if record['old'] in prior:
                raise ValueError('duplicate snapshot TU: ' + record['old'])
            prior[record['old']] = record
        if not prior or any(record.get('move_map') != mapping or
                            record.get('tables_sha256') != tables_sha256 for record in prior.values()):
            raise ValueError('snapshot map differs')
        mapping = {old: record['new'] for old, record in prior.items()}
    else:
        requested = dict(mapping)
        changes, report = plan(root, table, headers=headers, inline=inline)
        reviewed_sha = report['plan_sha256']
        mapping = {old: new for old, new in report['moves'].items() if old.startswith('src/')}
        parents = include_parents(root)
        affected = consumer_paths(root, set(changes), parents=parents)
        for consumer in report['include_rewritten_consumers']:
            if consumer.endswith('.c') and not (consumer_paths(root, {consumer}, parents=parents) & physical.keys()):
                raise ValueError('no registered physical recipe for include-rewritten consumer: ' + consumer)
        for rel in sorted(affected & physical.keys()):
            mapping.setdefault(rel, rel)
        # Refuse a requested native fragment rather than silently proving no TU.
        for old in requested:
            if old in members and old not in report['skipped_nonhome']:
                raise ValueError('non-home native member in tree: ' + old)
    records = []
    for old, new in sorted(mapping.items()):
        rel = new if compare else old
        if not (root / rel).is_file():
            raise ValueError('expected ' + ('post-move' if compare else 'pre-move') + ' physical TU: ' + rel)
        if rel in members:
            raise ValueError('non-home native member in tree: ' + rel)
        recipe = physical.get(rel)
        if recipe is None:
            raise ValueError('no registered physical recipe: ' + rel)
        current = capture_one(root, rel, recipe)
        record = {'old': old, 'new': new, **current,
                  'move_map': prior[old]['move_map'] if compare else requested,
                  'tables_sha256': tables_sha256,
                  'plan_sha256': prior[old]['plan_sha256'] if compare else reviewed_sha}
        if compare:
            before = prior[old]
            if before['new'] != new:
                raise ValueError('destination changed since snapshot: ' + old)
            if before['recipe'] != record['recipe']:
                raise ValueError('recipe changed: ' + old)
            record['raw_equal'] = before['raw_sha256'] == record['raw_sha256']
            record['canonical_assembly_equal'] = before['canonical_assembly_sha256'] == record['canonical_assembly_sha256']
            record['canonical_object_equal'] = before['canonical_object_sha256'] == record['canonical_object_sha256']
            if not record['canonical_assembly_equal'] or not record['canonical_object_equal']:
                raise ValueError('object changed beyond file metadata: ' + old)
        records.append(record)
    if snapshot:
        dest = Path(snapshot)
        if dest.exists():
            raise ValueError('snapshot already exists: ' + str(dest))
        dest.parent.mkdir(parents=True, exist_ok=True)
        dest.write_text(''.join(json.dumps(x, separators=(',', ':')) + '\n' for x in records))
    if results:
        Path(results).write_text(''.join(json.dumps(x, separators=(',', ':')) + '\n' for x in records))
    return {'physical_tus': len(records), 'canonical_equal': sum(x.get('canonical_object_equal', False) for x in records),
            'raw_equal': sum(x.get('raw_equal', False) for x in records),
            'receipt_sha256': digest(Path(snapshot).read_bytes()) if snapshot else None}


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument('tree', type=Path)
    ap.add_argument('--root', type=Path, default=ROOT)
    mode = ap.add_mutually_exclusive_group(required=True)
    mode.add_argument('--snapshot', type=Path)
    mode.add_argument('--compare', type=Path)
    ap.add_argument('--headers', type=Path)
    ap.add_argument('--inline', type=Path)
    ap.add_argument('--results', type=Path, help='write detailed compare receipt')
    args = ap.parse_args()
    print(json.dumps(run(args.root, args.tree, snapshot=args.snapshot, compare=args.compare,
                         headers=args.headers, inline=args.inline, results=args.results), sort_keys=True))


if __name__ == '__main__':
    main()
