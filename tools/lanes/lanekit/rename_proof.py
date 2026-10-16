#!/usr/bin/env python3
"""Prove local/member spelling changes and comments, then optionally stage.

    rename_proof.py ROW after.c [--before FILE] [--renames map.json] [--stage]
    rename_proof.py --check-only before.c after.c [--renames map.json]

Header overlays: --headers maps include-relative names to {before, after} paths.
Shared-header population coverage and batch gates remain landing obligations.
"""
from __future__ import annotations

import argparse
import importlib.util
import json
import os
from pathlib import Path
import shutil
import shlex
import subprocess
import sys
import tempfile

import kitlib

_spec = importlib.util.spec_from_file_location('azure_rename_proof_core', kitlib.ROOT / 'tools/rename_proof.py')
RP = importlib.util.module_from_spec(_spec)
_spec.loader.exec_module(RP)


def read_source(path):
    # Preserve exact bytes (including CRLF) in the source hash and staged file.
    return Path(path).read_bytes().decode('utf-8')


def safe_header(name):
    p = Path(name)
    if not name or p.is_absolute() or '..' in p.parts or p.suffix != '.h':
        raise RP.Refusal('header must be an include-relative .h path: ' + name)
    dest = kitlib.ROOT / 'include' / p
    if dest.is_symlink() or not dest.resolve().is_relative_to((kitlib.ROOT / 'include').resolve()):
        raise RP.Refusal('header escapes include tree: ' + name)
    return dest


def input_state(row):
    """Bind tree/recipe inputs; module authority binds sibling physical context.

    These deliberately small, named trees never scan work/ or raw/ dumps.
    Both exported and repository tools are bound: overlays compile through the
    standing production view, while SLUS uses verify.py directly.
    """
    root = kitlib.ROOT
    paths = [root / 'config/names.tsv', root / 'ledger/rows.jsonl',
        root / 'config/overlays/modules.json', root / 'config/slus_modules.json',
        root / 'config/slus_partitions.json', root / 'config/overlay_modules_disabled',
        root / 'tools/toolchain.lock.json', root / 'tools/verify.py',
        root / 'tools/rename_proof.py', Path(__file__),
        root / 'tools/lanes/lanekit/native_member.py',
        root / 'tools/slus_module_context.py', root / 'tools/build/ccproc.py',
        root / 'tools/build/cc.sh', root / 'build_ovl/tools/cc.sh',
        root / 'build_ovl/work/g3/overlay_func_compare.py',
        root / 'build_ovl/config/names.tsv']
    for folder, pattern in [('include', '**/*'), ('tools/gate', '*.py'),
            ('build_ovl/tools', '*.py'), ('config', '*.txt'), ('config', '*as*flags*')]:
        paths.extend(p for p in (root / folder).glob(pattern) if p.is_file())
    if row.get('gate_config') and row.get('kind') == 'overlay':
        paths.extend([root / row['gate_config'],
            root / 'build_ovl' / row['gate_config'],
            root / ('config/overlays/' + row['container'] + '.rowbase.jsonl'),
            root / ('ledger/splits/' + row['container'] + '.jsonl')])
        paths.extend([root / 'config/overlays/abs_syms.txt',
                      root / 'build_ovl/config/overlays/abs_syms.txt'])
    # Executable content, not just a lockfile, is part of the recipe.
    cell = row['cell']
    paths.extend(root / ('toolchain/compilers/gcc-' + cell) / n for n in ('gcc', 'cc1', 'cpp'))
    paths.extend([root / 'tools/maspsx/maspsx.py', root / 'toolchain/maspsx/maspsx.py'])
    from common import clean_path
    paths.append(clean_path(row))
    state = {str(p.relative_to(root)): RP.sha(p.read_bytes()) if p.is_file() else None
             for p in sorted(set(paths))}
    state['@row'] = RP.sha(json.dumps(row, sort_keys=True).encode())
    state['@module'] = kitlib.module_fingerprint(row)
    return state


def compile_row(row, source, out, include_root=None):
    """Use existing physical-TU adapters; never the listing screen or raw fallback."""
    out.mkdir(parents=True)
    inc = Path(include_root or kitlib.ROOT / 'include').resolve()
    if row['kind'] == 'slus':
        from verify import compile_slus_units
        units, error = compile_slus_units(row, source, out, include_root=inc)
        if error:
            raise RP.Refusal(error)
        if len({u['source'] for u in units}) != len(units):
            raise RP.Refusal('duplicate physical compilation unit')
        deps = {}
        for unit in units:
            recipe = unit['recipe']
            physical = dict(row, cell=recipe['ccver'], flags=recipe['ccflags'])
            deps.update(dependency_state(physical, unit['cfile'], inc))
        (out / 'dependencies.json').write_text(json.dumps(deps, indent=2) + '\n')
        return {u['source']: u['object'] for u in units}
    import native_member as N
    module = N.membership(row)
    if module:
        if inc != (kitlib.ROOT / 'include').resolve():
            raise RP.Refusal('native header overlays require a complete TU batch; no isolated member waiver')
        N.compile_object(row, read_source(source), module, out)
        deps = dependency_state(row, out / 'candidate.c', inc)
        (out / 'dependencies.json').write_text(json.dumps(deps, indent=2) + '\n')
        # Inspect the untrimmed object too: preparation must not hide a drift.
        return {module['source']: out / 'module.untrimmed.o'}
    from verify import gate_root
    from overlay_data_baseline import _gate, _segment
    import dataclasses
    gate = _gate(gate_root(False))
    cfg, _, _, seg = _segment(row, source, gate)
    # Match verify.py's include-root precedence. The live -I is demoted so a
    # before/after snapshot wins for quoted AND angle shared-header includes.
    if include_root is not None:
        if any(c.isspace() for c in str(inc)):
            raise RP.Refusal('include snapshot path contains whitespace')
        flags = f' -isystem{gate.ROOT / "include"} -iquote{inc} -I{inc}'
        seg = dataclasses.replace(seg, match=dataclasses.replace(seg.match, config=seg.match.config + flags))
    env = gate.evidence_env(cfg['name'])
    env.update(AZURE_MASPSX='', AZURE_MASPSX_COMPANION='', TMPDIR=str(out))
    try:
        objects = gate.compile_c_segments([seg], out / 'objects', env=env, overlay=cfg['name'])
    except SystemExit as exc:
        (out / 'compile.error.txt').write_text(str(exc))
        raise RP.Refusal(str(exc)) from exc
    if len(objects) != 1:
        raise RP.Refusal('production compile did not emit exactly one object')
    (out / 'dependencies.json').write_text(json.dumps(dependency_state(row, source, inc), indent=2) + '\n')
    return {row['id']: objects[0]}


def dependency_state(row, source, inc):
    """Ask the registered preprocessor for the actual consumed file closure.

    Includes through macros and nested headers must not escape receipt hashes.
    System/external source dependencies outside the private checkout refuse.
    No recursive source search participates in dependency discovery.
    """
    from common import NICE
    from verify import _env
    compiler = kitlib.ROOT / 'toolchain/compilers' / ('gcc-' + row['cell'])
    command = NICE + [str(compiler / 'gcc'), '-B' + str(compiler) + '/', '-M', '-O2',
        '-I' + str(inc), *shlex.split(row.get('flags') or ''), '-w', source.name]
    proc = subprocess.run(command, cwd=source.parent, env=_env(), capture_output=True, text=True, timeout=120)
    if proc.returncode or ':' not in proc.stdout:
        raise RP.Refusal('dependency preprocessing failed: ' + (proc.stderr or proc.stdout)[-1000:])
    body = proc.stdout.split(':', 1)[1].replace('\\\n', ' ')
    result = {}
    for name in shlex.split(body):
        path = Path(os.path.abspath(source.parent / name))
        if not path.is_relative_to(kitlib.ROOT):
            raise RP.Refusal('compiler dependency outside private checkout: ' + str(path))
        result[str(path.relative_to(kitlib.ROOT))] = RP.sha(path.read_bytes())
    if not result:
        raise RP.Refusal('empty compiler dependency closure')
    return result


def dependencies_fresh(state):
    for name, expected in state.items():
        path = kitlib.ROOT / name
        if Path(name).is_absolute() or '..' in Path(name).parts or RP.sha(path.read_bytes()) != expected:
            raise RP.Refusal('compiler dependency changed: ' + name)


def row_verify(row, candidate, include_root=None):
    if include_root is None:
        return kitlib.score_at(row, read_source(candidate))
    if row['kind'] == 'overlay':
        from verify import gate_root, verify_overlay
        # A private, small gate view makes header precedence independent of
        # old GCC's treatment of duplicate -I/-isystem directories. All gate
        # inputs except include/ and writable work/ retain the standing view.
        standing = gate_root(False)
        view = candidate.parent / 'verify_view'
        view.mkdir()
        for child in standing.iterdir():
            if child.name not in ('include', 'tools', 'work'):
                (view / child.name).symlink_to(child.resolve(), target_is_directory=child.is_dir())
        shutil.copytree(standing / 'tools', view / 'tools', ignore=shutil.ignore_patterns('__pycache__'))
        (view / 'include').symlink_to(Path(include_root).resolve(), target_is_directory=True)
        (view / 'work').mkdir()
        # The scorer's exported entry point lives at this historical location;
        # copy it so its ROOT also points at the private include snapshot.
        # Container/asm extraction inputs are immutable symlinks, not build dirs.
        if (standing / 'work/g3/overlay_func_compare.py').is_file():
            (view / 'work/g3').mkdir()
            shutil.copy2(standing / 'work/g3/overlay_func_compare.py', view / 'work/g3/overlay_func_compare.py')
        for name in ('s3_splat', 'roundtrip', 'overlay_recon', 'disc'):
            original = standing / 'work' / name
            if original.is_dir():
                (view / 'work' / name).mkdir()
                for child in original.iterdir():
                    (view / 'work' / name / child.name).symlink_to(child.resolve(), target_is_directory=child.is_dir())
        return verify_overlay(row, candidate, include_root=include_root, scorer_root=view)
    from verify import verify
    return verify(row, candidate, include_root=include_root)


def _stage(lane, row, before, after, receipt):
    """Publish only after checks; standard out/.base_sha plus a proof receipt."""
    if receipt['headers']:
        raise RP.Refusal('header overlays are proof-only; package the entire dependent population together')
    from common import clean_path
    if clean_path(row).read_bytes() != before:
        raise RP.Refusal('live base changed before staging')
    dest = lane / 'out' / row['container'] / Path(row['c_path']).name
    dest.parent.mkdir(parents=True, exist_ok=True)
    # Do not overwrite an unrelated existing staged result.
    if dest.exists() and dest.read_bytes() not in (before, after):
        raise RP.Refusal('different candidate already staged: ' + str(dest))
    dest.write_bytes(after)
    dest.with_name(dest.name + '.base_sha').write_text(RP.sha(before) + '\n')
    dest.with_name(dest.name + '.rename_proof.json').write_text(json.dumps(receipt, indent=2) + '\n')
    return str(dest.relative_to(lane))


def prove(row, before_path, after_path, lane, *, renames=None, headers=None, stage=False):
    """Always token check + object equality + per-row verify; no gate invocation.

    A rejected run still retains its inputs and available compiler artifacts.
    The result is relative neutrality at the recorded recipe, not retail proof
    by itself. 'exact' is true only when the mandatory row verifier agrees.
    """
    lane = Path(lane).resolve()
    kitlib.add_paths()
    from common import clean_path
    before_data, after_data = Path(before_path).read_bytes(), Path(after_path).read_bytes()
    before, after = before_data.decode('utf-8'), after_data.decode('utf-8')
    check = RP.check_renames(before, after, renames)
    if clean_path(row).read_bytes() != before_data:
        raise RP.Refusal('stale base: before must equal the current landed source')
    if headers is not None and (not isinstance(headers, dict) or any(not isinstance(name, str)
            or not isinstance(pair, dict) or set(pair) != {'before', 'after'}
            or any(not isinstance(pair[k], str) for k in pair) for name, pair in headers.items())):
        raise RP.Refusal('headers must map include-relative names to before/after path strings')
    header_data = {}; header_checks = {}
    for name, pair in (headers or {}).items():
        live = safe_header(name)
        old, new = Path(pair['before']).read_bytes(), Path(pair['after']).read_bytes()
        if live.read_bytes() != old:
            raise RP.Refusal('stale header base: ' + name)
        header_checks[name] = RP.check_renames(old.decode('utf-8'), new.decode('utf-8'))
        header_data[name] = (old, new)
    if stage and headers:
        raise RP.Refusal('--stage with header overlays is unsupported; prove/package every dependent row')
    # A fresh directory is never reused as evidence for another candidate.
    artifact = Path(tempfile.mkdtemp(prefix='rename_proof_', dir=lane / 'tmp'))
    result = dict(schema='azure-clean.rename-proof.v1', row=row['id'], cfg=row['cfg'],
        exact=False, neutral=False, token_check=check, headers=header_checks,
        before_sha256=RP.sha(before_data), after_sha256=RP.sha(after_data),
        artifacts=str(artifact.relative_to(lane)), batch_gate='deferred',
        certificate_renewal='required if certified inputs change')
    (artifact / 'before').mkdir(); (artifact / 'after').mkdir()
    inputs = []
    for tag, data in [('before', before_data), ('after', after_data)]:
        source = artifact / tag / Path(row['c_path']).name
        source.write_bytes(data)
        inputs.append(source)
    try:
        state = input_state(row)
        result['inputs'] = state
        incs = [None, None]
        if headers:
            for i, tag in enumerate(('before', 'after')):
                inc = artifact / tag / 'include'
                shutil.copytree(kitlib.ROOT / 'include', inc)
                for name, data in header_data.items():
                    (inc / name).write_bytes(data[i])
                incs[i] = inc
        objects = [compile_row(row, source, artifact / tag / 'build', inc)
                   for tag, source, inc in zip(('before', 'after'), inputs, incs)]
        result['dependencies'] = {}
        for tag in ('before', 'after'):
            deps = json.loads((artifact / tag / 'build/dependencies.json').read_text())
            for name, digest in deps.items():
                if name in result['dependencies'] and result['dependencies'][name] != digest:
                    raise RP.Refusal('dependency changed between compiles: ' + name)
                result['dependencies'][name] = digest
        if objects[0].keys() != objects[1].keys() or not objects[0]:
            raise RP.Refusal('physical compilation unit set changed or is empty')
        result['objects'] = {name: RP.compare_objects(objects[0][name].read_bytes(), objects[1][name].read_bytes())
                             for name in objects[0]}
        result['object_paths'] = {name: {tag: str(objects[i][name].relative_to(artifact))
            for i, tag in enumerate(('before', 'after'))} for name in objects[0]}
        result['neutral'] = all(obj['equal'] for obj in result['objects'].values())
        if not result['neutral']:
            raise RP.Refusal('compiled object identity differs')
        # Check the landed baseline as well as the candidate. A rename cannot
        # upgrade an unproven base to exact solely by equal compiled bytes.
        result['verify_before'] = row_verify(row, inputs[0], incs[0])
        result['verify_after'] = row_verify(row, inputs[1], incs[1])
        if not all(result[k].get('exact') is True for k in ('verify_before', 'verify_after')):
            raise RP.Refusal('per-row verification is not exact on both sides')
        if input_state(row) != state:
            raise RP.Refusal('compilation inputs changed during proof')
        dependencies_fresh(result['dependencies'])
        if Path(before_path).read_bytes() != before_data or Path(after_path).read_bytes() != after_data:
            raise RP.Refusal('candidate inputs changed during proof')
        if inputs[0].read_bytes() != before_data or inputs[1].read_bytes() != after_data:
            raise RP.Refusal('compiler source snapshots changed during proof')
        for name, pair in (headers or {}).items():
            if tuple(Path(pair[k]).read_bytes() for k in ('before', 'after')) != header_data[name]:
                raise RP.Refusal('header candidate changed during proof: ' + name)
        result['exact'] = True
        if stage:
            result['staged'] = _stage(lane, row, before_data, after_data, result)
    except (ValueError, OSError, RuntimeError, KeyError, SystemExit, subprocess.SubprocessError) as exc:
        result.update(exact=False, refused=str(exc))
    (artifact / 'proof.json').write_text(json.dumps(result, indent=2) + '\n')
    kitlib.log_append(lane, dict(row=row['id'], kind='rename-proof', source='rename_proof.py',
        variant=Path(after_path).stem, registered_cfg=row['cfg'], status='exact' if result['exact'] else 'refused',
        score=dict(exact=result['exact']), artifacts=result['artifacts'], refused=result.get('refused'),
        before_sha256=result['before_sha256'], after_sha256=result['after_sha256']))
    return result


def validate_receipt(row, before_path, after_path, lane, receipt_path):
    """Recheck hashes, tokens, retained objects and current inputs without compiling.

    This detects stale evidence; it does not grant a production batch-gate or
    certificate waiver and is not a signature on an untrusted receipt.
    """
    lane = Path(lane).resolve()
    result = json.loads(Path(receipt_path).read_text())
    if result.get('schema') != 'azure-clean.rename-proof.v1' or result.get('row') != row['id'] or result.get('cfg') != row['cfg']:
        raise RP.Refusal('receipt schema, row or recipe differs')
    if result.get('exact') is not True or result.get('neutral') is not True:
        raise RP.Refusal('receipt is not an exact rename proof')
    if result.get('headers'):
        raise RP.Refusal('header receipts require population packaging, not a single-row reuse')
    before, after = Path(before_path).read_bytes(), Path(after_path).read_bytes()
    if RP.sha(before) != result.get('before_sha256') or RP.sha(after) != result.get('after_sha256'):
        raise RP.Refusal('receipt source hashes are stale')
    if RP.check_renames(before.decode('utf-8'), after.decode('utf-8')) != result.get('token_check'):
        raise RP.Refusal('receipt token evidence differs')
    if input_state(row) != result.get('inputs'):
        raise RP.Refusal('receipt compilation inputs are stale')
    if not result.get('dependencies'):
        raise RP.Refusal('receipt lacks compiler dependency evidence')
    dependencies_fresh(result['dependencies'])
    def local(base, name):
        path = (base / name).resolve()
        if not path.is_relative_to(base) or path == base:
            raise RP.Refusal('receipt artifact path escapes its directory')
        return path
    artifact = local(lane, result['artifacts'])
    paths = result.get('object_paths', {})
    if not paths or paths.keys() != result.get('objects', {}).keys():
        raise RP.Refusal('receipt physical object set differs')
    for name, pair in paths.items():
        comparison = RP.compare_objects(local(artifact, pair['before']).read_bytes(),
                                         local(artifact, pair['after']).read_bytes())
        if comparison != result['objects'][name] or not comparison['equal']:
            raise RP.Refusal('receipt object evidence changed: ' + name)
    if any(result.get(k, {}).get('exact') is not True for k in ('verify_before', 'verify_after')):
        raise RP.Refusal('receipt lacks exact per-row verdicts')
    return result


def main(argv=None):
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('row_or_before')
    parser.add_argument('after', type=Path)
    parser.add_argument('--check-only', action='store_true')
    parser.add_argument('--before', type=Path)
    parser.add_argument('--renames', type=Path)
    parser.add_argument('--headers', type=Path)
    parser.add_argument('--stage', action='store_true')
    parser.add_argument('--receipt', type=Path, help='validate a retained proof without recompiling')
    args = parser.parse_args(argv)
    try:
        renames = json.loads(args.renames.read_text()) if args.renames else None
        if args.check_only:
            if args.before or args.stage or args.headers or args.receipt:
                parser.error('--check-only does not accept --before, --stage, --headers or --receipt')
            result = dict(schema='azure-clean.rename-token-check.v1', token_only=True,
                          **RP.check_renames(read_source(args.row_or_before), read_source(args.after), renames))
            print(json.dumps(result, indent=2)); return 0
        lane = kitlib.bootstrap()
        row = kitlib.row_of(args.row_or_before)
        before = args.before or kitlib.base_path(row, lane)
        headers = json.loads(args.headers.read_text()) if args.headers else None
        if args.receipt:
            if args.stage or args.headers or args.renames:
                parser.error('--receipt does not accept --stage, --headers or --renames')
            result = validate_receipt(row, before, args.after, lane, args.receipt)
        else:
            result = prove(row, before, args.after, lane, renames=renames, headers=headers, stage=args.stage)
        print(json.dumps({k: result[k] for k in ('schema', 'row', 'exact', 'neutral', 'token_check',
            'artifacts', 'refused', 'staged') if k in result}, indent=2))
        return 0 if result['exact'] else 1
    except (ValueError, OSError, KeyError, UnicodeError) as exc:
        print(json.dumps(dict(exact=False, refused=str(exc))))
        return 1


if __name__ == '__main__':
    sys.exit(main())
