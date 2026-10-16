#!/usr/bin/env python3
"""Trial or switch one complete SLUS physical TU recipe, with an unchanged image gate.

--row lists the physical owners. --tu selects exactly one owner, including a
partition remainder or a partition-only owner. --to accepts an era compiler
recipe. A trial restores registered inputs even on failure. --apply records a
trade and re-derives references only after the full SHA-1 gate passes.
No gate replacement environment variables or masked byte comparisons are used.
"""
from __future__ import annotations
import argparse
import contextlib
import fcntl
import hashlib
import json
import os
from pathlib import Path
import re
import shutil
import subprocess
import sys
import time

ROOT = Path(__file__).resolve().parents[2]
sys.path[:0] = [str(ROOT / 'tools'), str(ROOT / 'tools/build')]
from common import parse_cfg, read_jsonl, sha_file, write_jsonl
from source_layout import slus_source as layout_slus_source
from row_db import edges_of, slus_edges
from slus_module_context import modules, partition_context
from slus_modules import module_for_row
from fidelity.land_recipe_move import set_cc_ver, recipe_diff_ok

ERA_CELLS = {'2.6.3', '2.7.2', '2.7.2-cdk'}
LIVE = Path(os.environ.get('LAND_LIVE_ROOT', str(Path.home() / 'azure-clean'))).resolve()

def digest(data):
    return hashlib.sha256(data).hexdigest()

def json_write(path, value):
    path.parent.mkdir(parents=True, exist_ok=True)
    temp = path.with_name(path.name + '.tmp')
    temp.write_text(json.dumps(value, indent=2, sort_keys=True) + '\n')
    os.replace(temp, path)

def source_path(root, source):
    return layout_slus_source(source, root)

def tu_catalog(root):
    """Physical owners from the registered recipe; never invent a logical row."""
    root = Path(root)
    rows = {r['id']: r for r in read_jsonl(root / 'ledger/rows.jsonl')}
    owners = {m['source']: m for m in modules(root)}
    parents = json.loads((root / 'config/slus_partitions.json').read_text()).get('parents', [])
    parent_by_source = {p['source']: p for p in parents}
    result = {}
    for edge in edges_of((root / 'ledger/splits/slus.build.ninja').read_text()):
        stem = Path(edge['out']).stem
        logical = 'src/' + stem + '.c'
        module = owners.get(logical)
        parent = parent_by_source.get(logical)
        recipe = {k: edge[k] for k in ('ccver', 'ccflags', 'asflags')}
        contributors = [m['id'] for m in module['members']] if module else ['slus/' + stem]
        if module:
            contributors.extend(p['id'] for p in parents if any(x['module'] == module['name'] for x in p['parts']))
        if any(rid not in rows for rid in contributors):
            raise ValueError('physical TU has an unregistered contributor: ' + stem)
        if (module or parent) and (module or parent)['recipe'] != recipe:
            raise ValueError('registered recipe disagrees with physical edge: ' + stem)
        result[stem] = dict(stem=stem, source=logical, input=edge['src'], recipe=recipe,
                            module=module, parent=parent, contributors=sorted(set(contributors)))
    # Validate the complete current plural ownership contract before any trial.
    for parent in parents:
        partition_context(rows[parent['id']], root)
    return result

def select(root, row=None, tu=None):
    catalog = tu_catalog(root)
    available = [v for v in catalog.values() if row is None or row in v['contributors']]
    if row and not available:
        raise ValueError('not a registered SLUS row: ' + row)
    if tu is None:
        return available
    if tu not in {v['stem'] for v in available}:
        raise ValueError('TU is not an owner of the requested row: ' + tu)
    return catalog[tu]

def target_recipe(cfg, current):
    cell, flags = parse_cfg(cfg)
    if cell not in ERA_CELLS or any(re.fullmatch(r'-G[08]', f) is None for f in flags):
        raise ValueError('target must use an era compiler and only a plain -G0/-G8 setting')
    if len(flags) > 1:
        raise ValueError('duplicate G settings')
    return dict(ccver=cell, ccflags=' '.join(flags), asflags=current['asflags'])

def edit_registration(root, tu, target):
    """Update the entire physical owner's recipe in all authoritative inputs."""
    cfg = root / 'tools/build/configure.py'
    sources = [tu['source']]
    if tu['module']:
        sources.extend(m['source'] for m in tu['module']['members'])
        path = root / 'config/slus_modules.json'
        data = json.loads(path.read_text())
        module = next(m for m in data['modules'] if m['name'] == tu['module']['name'])
        if module['recipe'] != tu['recipe']:
            raise ValueError('module recipe changed during trial')
        module['recipe'] = target
        json_write(path, data)
    if tu['parent']:
        path = root / 'config/slus_partitions.json'
        data = json.loads(path.read_text())
        parent = next(p for p in data['parents'] if p['id'] == tu['parent']['id'])
        if parent['recipe'] != tu['recipe']:
            raise ValueError('parent recipe changed during trial')
        parent['recipe'] = target
        json_write(path, data)
    text = cfg.read_text()
    for source in sources:
        text = set_cc_ver(text, Path(source).stem, target['ccver'], target['ccflags'], 'SLUS physical TU recipe alignment')
    cfg.write_text(text)

def run(command, root, log):
    env = dict(os.environ, PYTHONDONTWRITEBYTECODE='1')
    for key in ('AZURE_MASPSX', 'AZURE_MASPSX_COMPANION', 'LAND_MOVE_GATE_SLUS', 'LAND_MOVE_GATE_OVL'):
        env.pop(key, None)
    with log.open('w') as f:
        proc = subprocess.run(command, cwd=root, env=env, stdout=f, stderr=subprocess.STDOUT)
    return proc.returncode

def stage(root, tu, target, out):
    """Generate and pin only this owner's ccver/ccflags; regenerate logical rows."""
    old = (root / 'ledger/splits/slus.build.ninja').read_text()
    old_logical = read_jsonl(root / 'ledger/splits/slus.jsonl')
    if slus_edges(old, root) != old_logical:
        raise ValueError('logical split ledger differs from the pinned physical recipe')
    edit_registration(root, tu, target)
    rc = run([sys.executable, 'tools/configure.py'], root / 'build_slus', out / 'configure.log')
    if rc:
        raise ValueError('configure failed; see configure.log')
    new = (root / 'build_slus/build.ninja').read_text()
    bad = recipe_diff_ok(old, new, {tu['stem']})
    if bad:
        raise ValueError('recipe changed outside selected TU: ' + repr(bad[:5]))
    edge = next(e for e in edges_of(new) if Path(e['out']).stem == tu['stem'])
    if {k: edge[k] for k in target} != target:
        raise ValueError('generated edge does not carry target recipe')
    new_logical = slus_edges(new, root)
    # Module whole members and parent remainder can change logical recipes;
    # partition contributors assigned to another owner retain their row recipes.
    allowed = {tu['source']}
    if tu['module']:
        allowed.update(m['source'] for m in tu['module']['members'])
    if len(old_logical) != len(new_logical):
        raise ValueError('logical edge count changed')
    for before, after in zip(old_logical, new_logical):
        if before != after and (before['src'] not in allowed or any(before[k] != after[k] for k in ('src', 'out', 'asflags'))):
            raise ValueError('logical edge changed outside selected owner')
    (root / 'ledger/splits/slus.build.ninja').write_text(new)
    write_jsonl(root / 'ledger/splits/slus.jsonl', new_logical)
    for script in ('registry.py', 'gen_src_index.py'):
        if run([sys.executable, 'tools/' + script], root, out / (script + '.log')):
            raise ValueError(script + ' failed')
    missing = [r['id'] for r in read_jsonl(root / 'ledger/rows.jsonl') if not r.get('gate_config')]
    if missing:
        raise ValueError('rows without a production gate window: ' + repr(missing))
    return old, new

def image_evidence(root, prior_count):
    """A newly emitted MATCH, exact pin, real SHA-1, retail equality and stamp."""
    recs = read_jsonl(root / 'ledger/gate_slus.jsonl')
    if len(recs) <= prior_count:
        raise ValueError('no fresh full-image gate record')
    g = recs[-1]
    pinned = root / 'ledger/splits/slus.build.ninja'
    if g.get('result') != 'MATCH' or g.get('recipe_vs_pinned') != 'identical' or g.get('recipe_sha256') != sha_file(pinned):
        raise ValueError('full image gate did not MATCH the pinned recipe')
    if (root / 'build_slus/build.ninja').read_bytes() != pinned.read_bytes():
        raise ValueError('generated recipe differs from pin')
    image = root / 'build_slus/build/slus_006.14'
    expected = (root / 'config/slus_006.14.sha1').read_text().split()[0]
    data = image.read_bytes()
    if hashlib.sha1(data).hexdigest() != expected or data != (root / 'baserom/slus_006.14').read_bytes():
        raise ValueError('linked image fails independent SHA-1 / retail-byte check')
    stamp = root / 'build_slus/build/slus_006.14.ok'
    if not stamp.is_file() or stamp.stat().st_mtime_ns < image.stat().st_mtime_ns:
        raise ValueError('image is newer than SHA-1 stamp')
    return dict(gate=g, image_sha1=expected, image_sha256=digest(data))

def reference_inputs(root, stem):
    """Bind the complete owner, all contributors, shared headers and pipeline."""
    tu = select(root, tu=stem)
    sources = {tu['source'], *('src/' + rid.split('/')[1] + '.c' for rid in tu['contributors'])}
    paths = [source_path(root, source) for source in sources]
    paths.extend(p for p in (root / 'include').rglob('*') if p.is_file())
    paths.extend(root / n for n in ('config/names.tsv', 'tools/build/cc.sh', 'tools/build/ccproc.py',
                                    'tools/build/slus_partitions.py', 'tools/build/slus_modules.py',
                                    'tools/fidelity/slus_recipe.py'))
    h = hashlib.sha256(json.dumps(tu, sort_keys=True).encode())
    for path in sorted(paths):
        h.update(path.relative_to(root).as_posix().encode() + b'\0' + path.read_bytes())
    return h.hexdigest()

def rederive(root, tu, proof, out):
    """Save a whole physical TU reference compiled and linked by the SHA-1 gate."""
    stem = tu['stem']
    obj = root / 'build_slus/build/src' / (stem + '.o')
    stamp = root / 'build_slus/build/slus_006.14.ok'
    if not obj.is_file() or stamp.stat().st_mtime_ns < obj.stat().st_mtime_ns:
        raise ValueError('physical object is absent or newer than gated image')
    directory = root / 'ledger/cache/slus_tu'
    directory.mkdir(parents=True, exist_ok=True)
    shutil.copy2(obj, directory / (stem + '.o'))
    rec = dict(tu=stem, source=tu['source'], contributors=tu['contributors'],
               recipe=select(root, tu=stem)['recipe'], inputs_sha256=reference_inputs(root, stem),
               object_sha256=sha_file(obj), proof=proof, reviewer='pending')
    json_write(directory / (stem + '.json'), rec)
    if not tu['module'] and not tu['parent']:
        # Keep the existing ordinary-row verifier useful after a recipe switch.
        from verify import rebaseline_slus
        result = rebaseline_slus(tu['contributors'])
        json_write(out / 'rebaseline.json', result)
        if any(r['outcome'] != 'rebaselined' for r in result):
            raise ValueError('ordinary row rebaseline refused: ' + repr(result))
    return rec

def verify_reference(root, stem):
    select(root, tu=stem)  # constrain reference paths to a registered physical TU
    directory = root / 'ledger/cache/slus_tu'
    rec = json.loads((directory / (stem + '.json')).read_text())
    if rec['inputs_sha256'] != reference_inputs(root, stem):
        raise ValueError('physical TU reference inputs are stale')
    if rec['recipe'] != select(root, tu=stem)['recipe']:
        raise ValueError('physical TU reference recipe is stale')
    for obj in (directory / (stem + '.o'), root / 'build_slus/build/src' / (stem + '.o')):
        if sha_file(obj) != rec['object_sha256']:
            raise ValueError('physical TU reference object differs')
    # Cached bytes alone are never an image proof.
    image_evidence(root, len(read_jsonl(root / 'ledger/gate_slus.jsonl')) - 1)
    return dict(result='MATCH', tu=stem, object_sha256=rec['object_sha256'])

def snapshot(paths):
    if any(p.is_symlink() for p in paths):
        raise ValueError('refusing to mutate symlinked authoritative inputs')
    return {p: p.read_bytes() if p.exists() else None for p in paths}

def restore(saved):
    for path, data in saved.items():
        if data is None:
            path.unlink(missing_ok=True)
        else:
            path.parent.mkdir(parents=True, exist_ok=True)
            path.write_bytes(data)

def execute(root, tu, target, out, apply=False, candidate=None, base_sha=None):
    for name in ('src', 'raw', 'include', 'config', 'ledger', 'tools'):
        protected = root / name
        if out == protected or out.is_relative_to(protected):
            raise ValueError('proof output overlaps authoritative inputs')
    if select(root, tu=tu['stem']) != tu:
        raise ValueError('physical owner changed after selection')
    out.mkdir(parents=True, exist_ok=False)
    if apply and target == tu['recipe'] and candidate is None:
        raise ValueError('already at target recipe')
    paths = [root / n for n in ('tools/build/configure.py', 'config/slus_modules.json', 'config/slus_partitions.json',
                               'ledger/splits/slus.build.ninja', 'ledger/splits/slus.jsonl', 'ledger/rows.jsonl',
                               'ledger/recipe_trades.jsonl', 'ledger/cache/slus_obj.json')]
    paths.extend((root / 'src').glob('*/INDEX.md'))
    paths.extend(root / 'ledger/cache/slus_tu' / (tu['stem'] + ext) for ext in ('.json', '.o'))
    paths.extend(root / 'ledger/cache/slus_dis' / (rid.split('/')[1] + '.txt') for rid in tu['contributors'])
    source = source_path(root, tu['source'])
    if candidate:
        if tu['module'] or tu['parent']:
            raise ValueError('candidate source replacement requires an ordinary whole TU; edit canonical contributors separately')
        if base_sha is None or sha_file(source) != base_sha:
            raise ValueError('candidate requires a current source SHA-256 guard')
        from pin_census import landing_refusal
        bad = landing_refusal(candidate.read_text(), source.read_text(), source.relative_to(root).as_posix(),
                              row=next(r for r in read_jsonl(root / 'ledger/rows.jsonl') if r['id'] == tu['contributors'][0]))
        if bad:
            raise ValueError('candidate landing screen: ' + str(bad))
        paths.append(source)
    saved = snapshot(paths)
    original = sha_file(source)
    commit = False
    result = dict(tu=tu['stem'], contributors=tu['contributors'], recipe_from=tu['recipe'], recipe_to=target,
                  reviewer='pending', applied=False)
    try:
        control_count = len(read_jsonl(root / 'ledger/gate_slus.jsonl'))
        if run(['bash', 'tools/build/build_slus.sh', '-j', '4'], root, out / 'control.log'):
            raise ValueError('registered control build failed')
        result['control'] = image_evidence(root, control_count)
        if candidate:
            source.write_bytes(candidate.read_bytes())
        old, new = stage(root, tu, target, out)
        (out / 'recipe.before.ninja').write_text(old)
        (out / 'recipe.after.ninja').write_text(new)
        # Compile the whole selected physical owner even for an era-recipe control.
        (root / 'build_slus/build/src' / (tu['stem'] + '.o')).unlink(missing_ok=True)
        n0 = len(read_jsonl(root / 'ledger/gate_slus.jsonl'))
        rc = run(['bash', 'tools/build/build_slus.sh', '-j', '4'], root, out / 'gate.log')
        # Durable artifacts before rollback, including complete TU and whole image.
        for relative, name in [('build_slus/build/src/' + tu['stem'] + '.o', 'candidate.o'),
                               ('build_slus/build/slus_006.14', 'candidate.image'),
                               ('build_slus/build/slus_006.14.elf', 'candidate.elf'),
                               ('build_slus/ninja.log', 'ninja.log')]:
            path = root / relative
            if path.is_file():
                shutil.copy2(path, out / name)
        if rc:
            result.update(result='NO MATCH', detail='full SHA-1 build failed; see gate.log and ninja.log')
        else:
            result['proof'] = image_evidence(root, n0)
            result.update(result='MATCH', detail='full image SHA-1 and retail bytes match')
            if apply:
                result['reference'] = rederive(root, tu, result['proof'], out)
                result['reference_check'] = verify_reference(root, tu['stem'])
                record = dict(scope='physical-tu', id=tu['contributors'][0] if not tu['module'] and not tu['parent'] else None,
                              ids=tu['contributors'], tu=tu['stem'], date=time.strftime('%Y-%m-%d', time.gmtime()),
                              cfg_from=tu['recipe']['ccver'] + (' ' + tu['recipe']['ccflags'] if tu['recipe']['ccflags'] else ''),
                              cfg_to=target['ccver'] + (' ' + target['ccflags'] if target['ccflags'] else ''),
                              kind='coherence' if candidate and original != sha_file(source) else 'recipe-switch',
                              rule2=True if not candidate or original == sha_file(source) else None, source_sha_before=original,
                              candidate_sha=sha_file(source), proof=result['proof'], reviewer='pending',
                              lander='tools/fidelity/slus_recipe.py', how='complete physical TU + full SLUS SHA-1 gate')
                with (root / 'ledger/recipe_trades.jsonl').open('a') as f:
                    f.write(json.dumps(record, separators=(',', ':')) + '\n')
                json_write(out / 'trade.json', record)
                commit = True
                result['applied'] = True
    except BaseException as exc:
        result.update(result='ERROR', detail=str(exc))
        if isinstance(exc, (KeyboardInterrupt, SystemExit)):
            raise
    finally:
        if not commit:
            restore(saved)
            # Restore the production recipe and image before another trial.
            rc = run([sys.executable, 'tools/configure.py'], root / 'build_slus', out / 'restore-configure.log')
            count = len(read_jsonl(root / 'ledger/gate_slus.jsonl'))
            rc = rc or run(['bash', 'tools/build/build_slus.sh', '-j', '4'], root, out / 'restore-gate.log')
            if rc:
                result['restore'] = 'FAILED'
            else:
                try:
                    result['restore'] = image_evidence(root, count)
                except ValueError as exc:
                    result['restore'] = 'FAILED: ' + str(exc)
            if not isinstance(result['restore'], dict):
                result.update(result='ERROR', detail=result.get('detail', '') + '; rollback image failed')
        json_write(out / 'result.json', result)
    return result

def refresh_reference(root, tu, out):
    """Recompile one registered whole owner and gate it before reference refresh."""
    for name in ('src', 'raw', 'include', 'config', 'ledger', 'tools'):
        if out == root / name or out.is_relative_to(root / name):
            raise ValueError('proof output overlaps authoritative inputs')
    out.mkdir(parents=True, exist_ok=False)
    paths = [root / 'ledger/cache/slus_tu' / (tu['stem'] + ext) for ext in ('.json', '.o')]
    paths.append(root / 'ledger/cache/slus_obj.json')
    paths.extend(root / 'ledger/cache/slus_dis' / (rid.split('/')[1] + '.txt') for rid in tu['contributors'])
    saved = snapshot(paths)
    try:
        before = reference_inputs(root, tu['stem'])
        (root / 'build_slus/build/src' / (tu['stem'] + '.o')).unlink(missing_ok=True)
        count = len(read_jsonl(root / 'ledger/gate_slus.jsonl'))
        if run(['bash', 'tools/build/build_slus.sh', '-j', '4'], root, out / 'gate.log'):
            raise ValueError('registered full-image gate failed; reference unchanged')
        proof = image_evidence(root, count)
        if reference_inputs(root, tu['stem']) != before:
            raise ValueError('complete owner inputs changed during reference compilation')
        rec = rederive(root, tu, proof, out)
        result = dict(result='MATCH', reference=rec, reference_check=verify_reference(root, tu['stem']), reviewer='pending')
        json_write(out / 'result.json', result)
        return result
    except BaseException:
        restore(saved)
        raise

def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument('--root', type=Path, default=ROOT)
    ap.add_argument('--row', help='logical row used to constrain/list physical owners')
    ap.add_argument('--tu', help='physical source stem, not a function subset')
    ap.add_argument('--to', help='era recipe, e.g. "2.7.2-cdk -G0"')
    ap.add_argument('--out', type=Path)
    ap.add_argument('--candidate', type=Path)
    ap.add_argument('--base-sha')
    ap.add_argument('--apply', action='store_true')
    ap.add_argument('--dry-run', action='store_true')
    ap.add_argument('--live', action='store_true')
    ap.add_argument('--verify-reference', action='store_true')
    ap.add_argument('--rebaseline-tu', action='store_true', help='force a registered whole-owner compile and image gate, then refresh its references')
    a = ap.parse_args(argv)
    root = a.root.resolve()
    if root == LIVE and not a.live:
        ap.error('canonical live root requires --live (including trials)')
    if root != ROOT:
        ap.error('run the installed tool in --root so sibling imports resolve there')
    try:
        if a.rebaseline_tu:
            if not a.tu or not a.out:
                raise ValueError('--tu and --out required for whole-TU rebaseline')
            if a.apply or a.to or a.candidate:
                raise ValueError('whole-TU rebaseline only uses the registered recipe/text')
            tu = select(root, a.row, a.tu)
            if a.dry_run:
                result = dict(tu=tu['stem'], contributors=tu['contributors'], recipe=tu['recipe'])
            else:
                lock = root / 'build_ovl/work/land.lock';lock.parent.mkdir(parents=True, exist_ok=True)
                with lock.open('w') as f:
                    fcntl.flock(f, fcntl.LOCK_EX)
                    if select(root, tu=tu['stem']) != tu:
                        raise ValueError('physical owner changed after selection')
                    result = refresh_reference(root, tu, a.out.resolve())
        elif a.verify_reference:
            if not a.tu:
                raise ValueError('--tu required')
            result = verify_reference(root, a.tu)
        elif not a.to:
            result = select(root, a.row, a.tu)
        else:
            if not a.tu:
                raise ValueError('--tu is required for recipe trials, even for a one-owner row')
            tu = select(root, a.row, a.tu)
            target = target_recipe(a.to, tu['recipe'])
            if a.dry_run:
                result = dict(tu=tu['stem'], contributors=tu['contributors'], recipe_from=tu['recipe'], recipe_to=target)
            else:
                if not a.out:
                    raise ValueError('--out required (new proof directory)')
                lock = root / 'build_ovl/work/land.lock'
                lock.parent.mkdir(parents=True, exist_ok=True)
                with lock.open('w') as f:
                    fcntl.flock(f, fcntl.LOCK_EX)
                    result = execute(root, tu, target, a.out.resolve(), a.apply, a.candidate, a.base_sha)
        print(json.dumps(result, indent=2))
        return 0 if isinstance(result, list) or result.get('result', 'MATCH') == 'MATCH' else 1
    except (OSError, ValueError) as exc:
        print(json.dumps({'result': 'ERROR', 'detail': str(exc)}))
        return 1
if __name__ == '__main__':
    raise SystemExit(main())
