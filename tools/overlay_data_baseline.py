"""Byte baselines for registered data rows, using the production window linker.

This is a row measurement, never a replacement for gate_all or placement proof.
The caller supplies a normal exported gate view and a candidate C file. No raw
fallback, relocation masking, or retail substitution participates in the link.
"""
import dataclasses
import hashlib
import importlib.util
import json
import os
from pathlib import Path
import subprocess
import sys
import tempfile
import threading
import time

_GATES = {}
_LOCK = threading.RLock()


def _gate(view):
    view = Path(view).resolve()
    with _LOCK:
        if view not in _GATES:
            path = view / 'tools/overlay_local_gate.py'
            # Flat gate imports carry ROOT derived from __file__. Reusing a
            # canonical tools/gate import here would select the wrong evidence.
            for dependency in ('overlay_evidence', 'overlay_as_flags',
                               'rowbase_naming_debt', 'gate_read_cache', 'match'):
                old = sys.modules.get(dependency)
                if old is not None and Path(old.__file__).resolve().parent != path.parent:
                    raise ValueError('gate dependency loaded from another root: ' + dependency)
            sys.path.insert(0, str(path.parent))
            name = 'azure_data_gate_' + hashlib.sha256(str(view).encode()).hexdigest()[:12]
            spec = importlib.util.spec_from_file_location(name, path)
            gate = importlib.util.module_from_spec(spec)
            sys.modules[name] = gate
            spec.loader.exec_module(gate)
            _GATES[view] = gate
        return _GATES[view]


def word_comparison(generated, target):
    """Count differing 4-byte storage words; length is always part of equality."""
    got = [generated[i:i+4] for i in range(0, len(generated), 4)]
    want = [target[i:i+4] for i in range(0, len(target), 4)]
    subs = sum(a != b for a, b in zip(got, want))
    indels = abs(len(got) - len(want))
    return dict(exact=generated == target, subs=subs, indels=indels,
                total=subs + indels, gen_words=len(got), tgt_words=len(want),
                **{'class': 'match' if generated == target else
                   'length-drift' if len(generated) != len(target) else 'data-diff'})


def _segment(row, source, gate):
    if row.get('kind') != 'overlay' or not row.get('gate_config'):
        raise ValueError('object baseline requires a registered production window')
    config = gate.cfg_path('config/overlays/' + Path(row['gate_config']).name)
    cfg = gate.load_yaml(config)
    sb = cfg['standalone_build']
    w = sb['window']
    start, end, vram = (gate.parse_int(w[k], 'window.' + k)
                        for k in ('file_start', 'file_end', 'vram_start'))
    if not start <= row['foff'] < row['foff'] + row['size'] <= end:
        raise ValueError('row is not wholly inside its production window')
    family = cfg['name'].split('_')[0]
    splits = gate.load_split_rows(sb, start, end)
    selected = [r for r in splits if r['foff'] == row['foff'] and r['size'] == row['size']
                and r.get('func_vram') == row['func']]
    if len(selected) != 1:
        raise ValueError('row geometry/identity disagrees with the exported split')
    matches, _ = gate.load_matches(sb, start, end, family=family)
    match = matches.get((row['foff'], row['size']))
    if match is None or match.source_kind != 'c' or match.config != row['cfg']:
        raise ValueError('no production C match at the registered recipe')
    # The production path's stem is the registered row ID used by link-list
    # rebinding. Keep it when measuring that same canonical file: resolving a
    # readable-name symlink would turn the segment ID into the readable name.
    # A distinct candidate still replaces the source, as before.
    if Path(source).resolve() != match.source.resolve():
        match = dataclasses.replace(match, source=source)
    segs = gate.build_segments(selected, {(row['foff'], row['size']): match},
                               row['foff'], row['foff'] + row['size'], vram - start)
    if len(segs) != 1 or segs[0].kind != 'c':
        raise ValueError('row does not produce exactly one C segment')
    return cfg, sb, family, segs[0]


def text_link_base(row, seg, gate, family):
    """Use a proven rowbase, or an existing placement at the window's address.

    Legacy link-list placements are linked directly in the production window;
    load_matches deliberately leaves their link_vram unset. This measurement
    uses that same address without promoting their placement confidence.
    """
    if seg.match.link_vram is not None:
        return seg.match.link_vram
    import linklist
    entry = linklist.placement(gate.ROOT, family, row['foff'], row=row['id'])
    if (entry is None or entry['home'] == entry['row']
            or entry['size'] != row['size'] or entry['vma'] != seg.vram
            or row.get('true_name') != 'func_%08X' % entry['vma']):
        raise ValueError('text refresh requires proven rowbase or matching production link-list placement')
    return seg.vram


def _measure(row, source, view, out):
    gate = _gate(view)
    cfg, sb, family, seg = _segment(row, source, gate)
    owner = gate.rodata_owner(family, row['foff'])
    is_data = row.get('row_kind') == 'data'
    if is_data and (owner is None or int(owner['rodata_size']) != row['size']):
        raise ValueError('data row lacks exact rodata ownership')
    container, _ = gate.ensure_container(cfg, sb)
    with container.open('rb') as stream:
        stream.seek(row['foff'])
        target = stream.read(row['size'])
    if len(target) != row['size']:
        raise ValueError('retail container does not cover the row extent')
    source_sha = hashlib.sha256(source.read_bytes()).hexdigest()
    env = gate.evidence_env(cfg['name'])
    # gate.run merges overrides over os.environ; empty values force cc.sh's
    # registered default even when the invoking shell has a companion hook.
    env['AZURE_MASPSX'] = ''
    env['AZURE_MASPSX_COMPANION'] = ''
    objects = gate.compile_c_segments([seg], out / 'obj', env=env, overlay=cfg['name'])
    if len(objects) != 1:
        raise ValueError('row compile did not emit exactly one object')
    obj = objects[0]
    gate.check_bare_text_empty(objects)
    gate.assert_unique_globals(objects, 'data baseline mini-link', expect_count=1)
    symbol_files = [gate.cfg_path('config/slus_006.14.symbols.txt')]
    if cfg['options'].get('symbol_addrs_path'):
        symbol_files.append(gate.cfg_path(cfg['options']['symbol_addrs_path']))
    symbol_files.append(gate.cfg_path(gate.ABS_SYMS_FILE))
    gp = gate.parse_int(cfg['options'].get('gp_value', 0), 'options.gp_value')
    if owner is not None:
        generated = gate.rodata_first_link(obj, seg, owner, gp, symbol_files, out / 'linked')
        base = gate.rodata_link_base(obj, seg, owner)
    else:
        # Use the production mini-link, including the direct window address of
        # a registered legacy link-list placement. No placement grant is added.
        if is_data:
            raise ValueError('data row requires exact rodata ownership')
        base = text_link_base(row, seg, gate, family)
        match = gate._match_mod()
        placements = match._local_section_placements(str(obj), seg.match.func,
                                                      base, target)
        if gate.local_table_mismatches(obj, placements, seg, base,
                                      container, gp, symbol_files, out / 'tables', seg.match.func):
            raise ValueError('compiler-local data differs from retail')
        mini = dataclasses.replace(seg, index=0, vram=base)
        ld, elf, binary = (out / ('linked.' + ext) for ext in ('ld', 'elf', 'bin'))
        gate.write_linker_script([mini], objects, gp, symbol_files, ld,
                                 placements=placements, obj_paths={0: obj})
        gate.run([gate.LD, '-EL', '--no-check-sections', '-T', str(ld), '-o', str(elf), str(obj)])
        gate.run([gate.OBJCOPY, '-O', 'binary', str(elf), str(binary)])
        generated = binary.read_bytes()
        if len(generated) < seg.size or any(generated[seg.size:]):
            raise ValueError('linked object does not exactly cover the current carve')
        generated = generated[:seg.size]  # production gate permits a zero section-end tail
    if source_sha != hashlib.sha256(source.read_bytes()).hexdigest():
        raise ValueError('source changed during measurement')
    if seg.match.source.resolve() != source:
        raise ValueError('production source path changed during measurement')
    (out / 'generated.bin').write_bytes(generated)
    (out / 'retail.bin').write_bytes(target)
    return dict(word_comparison(generated, target), status='ok',
                proof='compiled-object-bytes', src_sha=source_sha,
                bytes=len(generated), target_bytes=len(target), link_vram=base,
                placement='proven' if seg.match.link_vram is not None else 'unproven',
                generated_sha=hashlib.sha256(generated).hexdigest(),
                retail_sha=hashlib.sha256(target).hexdigest(),
                object_sha=hashlib.sha256(obj.read_bytes()).hexdigest(),
                gate_config=row['gate_config'], relocations='resolved; none masked')


def verify_object_row(row, cfile, view, out_dir=None):
    """Measure data or a proven current text carve, retaining optional artifacts."""
    t0 = time.monotonic()
    source = Path(cfile).resolve()
    try:
        if out_dir is None:
            with tempfile.TemporaryDirectory(prefix='data-baseline-') as td:
                rec = _measure(row, source, view, Path(td))
        else:
            out = Path(out_dir).resolve()
            out.mkdir(parents=True, exist_ok=False)
            rec = _measure(row, source, view, out)
    except (OSError, ValueError, KeyError, TypeError, SystemExit, subprocess.SubprocessError) as exc:
        rec = dict(status='failed', exact=False, err=str(exc))
    rec['secs'] = round(time.monotonic() - t0, 2)
    return rec


def measure_object_row(row, cfile, view):
    """Use a fresh interpreter: normal tools may already import canonical gates.

    The flat production view must own every gate import and its evidence root.
    This also isolates the module caches when --baseline mixes SLUS and data
    in its worker threads. The worker performs the complete unmasked byte link.
    """
    t0 = time.monotonic()
    try:
        env = dict(os.environ, PYTHONDONTWRITEBYTECODE='1')
        env.pop('AZURE_MASPSX', None)
        env.pop('AZURE_MASPSX_COMPANION', None)
        result = subprocess.run([sys.executable, str(Path(__file__).resolve()),
                                 '--row-json', json.dumps(row), '--source', str(Path(cfile).resolve()),
                                 '--view', str(Path(view).resolve())],
                                capture_output=True, text=True, env=env, timeout=900)
        if result.returncode:
            raise ValueError('object baseline worker failed: ' + result.stderr[-500:])
        rec = json.loads(result.stdout)
        if not isinstance(rec, dict) or not isinstance(rec.get('exact'), bool):
            raise ValueError('invalid object baseline worker receipt')
    except (OSError, ValueError, subprocess.SubprocessError) as exc:
        rec = dict(status='failed', exact=False, err=str(exc))
    rec['secs'] = round(time.monotonic() - t0, 2)
    return rec


if __name__ == '__main__':
    import argparse
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument('--row-json', required=True)
    ap.add_argument('--source', required=True)
    ap.add_argument('--view', required=True)
    args = ap.parse_args()
    print(json.dumps(verify_object_row(json.loads(args.row_json), args.source, args.view)))
