#!/usr/bin/env python3
"""Prove declared SLUS data ownership without granting module-cleanup placement.

The complete image, object section bytes, symbol offsets/VMAs and selected
owners' unmasked genuine-ASPSX comparisons must agree. Connected owners require
complete physical-TU proof; collector records retain their full logical scope.
This receipt does not certify L4.
Run under the shared landing lock when recording authoritative evidence.
"""
from __future__ import annotations
import argparse
import hashlib
import inspect
import json
from pathlib import Path
import subprocess
import sys
import tempfile
import time

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / 'tools'))
from common import clean_path, rows
from slus_module_context import modules, fingerprint
from slus_module_evidence import (verifier_fingerprint, physical_descriptor, check_physical_record,
                                  check_data_piece_record, check_partition_record)
from slus_modules import data_sections
from fidelity.slus_iso import SlusView
from fidelity import aspsx_diff as A


COMPILER_MODEL = 't272'


def compiler_model_code():
    """Fingerprint the accepted compiler model, including its rewrite function."""
    from fidelity import epilogue_model as E
    path = Path(E.__file__).resolve()
    return {'path': str(path.relative_to(ROOT)),
            'source_sha256': hashlib.sha256(path.read_bytes()).hexdigest(),
            'rewrite_sha256': hashlib.sha256(inspect.getsource(E.rewrite).encode()).hexdigest()}


def selected_model_rows(selected, requested):
    """A model is allowed only for explicitly named members of selected modules."""
    requested = list(requested)
    if len(requested) != len(set(requested)):
        raise ValueError('duplicate compiler-model row')
    known = {member['id'] for module in selected for member in module['members']}
    unknown = set(requested) - known
    if unknown:
        raise ValueError('compiler-model row is not a selected member: ' + ', '.join(sorted(unknown)))
    return set(requested)


def check_member_record(record, member, expected_fingerprint, modeled=False):
    """Keep every existing pipeline and retail gate for both proof modes."""
    expected = {'diff': 0, 'masked': 0, 'checked': len(member['functions'])}
    if (record.get('status') != 'ok' or record.get('maspsx_exact') is not True
            or record.get('selfcheck') is not True or record.get('maspsx_retail') != expected
            or record.get('module_fingerprint') != expected_fingerprint):
        raise ValueError('member pipeline/retail proof failed: ' + json.dumps(record))
    genuine = record.get('genuine', {}).get('2.79', {})
    if modeled:
        retail = genuine.get('retail')
        if (genuine.get('exact') is not False or 'err' in genuine
                or genuine.get('missing') or genuine.get('lnk_unknown')
                or not isinstance(genuine.get('diff'), int) or genuine['diff'] <= 0
                or not isinstance(retail, list) or len(retail) != 2
                or not isinstance(retail[0], int) or retail[0] <= 0 or retail[1] != 0):
            raise ValueError('compiler-model row lacks an unmasked measured direct discrepancy: '
                             + json.dumps(record))
    elif genuine.get('exact') is not True or genuine.get('retail') != [0, 0]:
        raise ValueError('member direct-genuine proof failed: ' + json.dumps(record))


def rewrite_selected_functions(source, functions, model=COMPILER_MODEL):
    """Apply t272 to the selected member's functions, never its module neighbours."""
    if model != COMPILER_MODEL:
        raise ValueError('unsupported compiler model: ' + model)
    from fidelity import epilogue_model as E
    wanted = set(functions)
    if not wanted or len(wanted) != len(functions):
        raise ValueError('empty or duplicate modeled function list')
    spans = E.functions_s(source)
    names = [name for name, _, _ in spans]
    if any(names.count(name) != 1 for name in wanted):
        raise ValueError('modeled function missing or ambiguous in compiler stream')
    chunks, last = [], 0
    for name, start, end in spans:
        chunks.append(source[last:start])
        body = source[start:end]
        chunks.append(E.rewrite(body, model) if name in wanted else body)
        last = end
    chunks.append(source[last:])
    result = ''.join(chunks)
    if result == source:
        raise ValueError('compiler model changed no selected function')
    return result


def prove_compiler_model(row, member, model=COMPILER_MODEL):
    """Fresh compiler stream -> selected t272 rewrite -> genuine ASPSX 2.79.

    The comparison reference is the actual pipeline object from that same fresh
    compile. Both objects must independently resolve to retail without masks.
    """
    if model != COMPILER_MODEL:
        raise ValueError('unsupported compiler model: ' + model)
    scope = sorted(member['functions'])
    old_tmp = A.TMP
    try:
        with tempfile.TemporaryDirectory(prefix='slus_ownership_model_') as temp:
            td = Path(temp)
            A.TMP = td / 'aspsx'
            A.TMP.mkdir()
            ctx, error = A.prepare_slus(row, clean_path(row), row['cfg'], row.get('row_asflags') or '', td)
            if ctx is None:
                raise ValueError('fresh compiler stream failed: ' + str(error))
            if ctx['maspsx_exact'] is not True:
                raise ValueError('fresh pipeline object is not retail-exact')
            original = ctx['g_src']
            modeled = rewrite_selected_functions(original, scope, model)
            pipeline_bytes = ctx['pipeline_obj']
            pipeline_obj = A.read_elf(pipeline_bytes)
            if pipeline_obj.unknown:
                raise ValueError('unknown records in pipeline object: ' + str(pipeline_obj.unknown[:2]))
            pipeline = A.View(pipeline_obj)
            missing = set(scope) - set(pipeline.funcs)
            if missing:
                raise ValueError('named functions missing from pipeline object: ' + str(sorted(missing)))
            expected = {'diff': 0, 'masked': 0, 'checked': len(scope)}
            pipeline_retail = A.retail_compare(pipeline, scope, 'slus')
            if pipeline_retail != expected:
                raise ValueError('fresh pipeline object is masked or not retail-exact: ' + str(pipeline_retail))
            modes, _ = A.genuine_modes(modeled, ctx['flags'])
            attempts = []
            for flags, equ in modes:
                src = A.aspsx_input(modeled, equ=equ)
                lnk, error = A.run_aspsx(src, '2.79', flags, td)
                label = ' '.join(flags + (['equ'] if equ else []))
                if lnk is None:
                    attempts.append({'mode': label, 'error': error})
                    continue
                genuine_obj = A.read_lnk(lnk)
                if genuine_obj.unknown:
                    attempts.append({'mode': label, 'unknown': genuine_obj.unknown[:2]})
                    continue
                genuine = A.View(genuine_obj, pipeline, A.aliases(modeled))
                for func in scope:
                    genuine.add_unit(func, pipeline)
                comparison = A.compare_units(pipeline, genuine, scope)
                retail = A.retail_compare(genuine, scope, 'slus')
                if comparison['exact'] and not comparison['missing'] and retail == expected:
                    return {'model': model, 'functions': scope, 'aspsx_version': '2.79',
                            'aspsx_mode': label, 'source_sha256': hashlib.sha256(Path(clean_path(row)).read_bytes()).hexdigest(),
                            'original_stream_sha256': hashlib.sha256(original.encode()).hexdigest(),
                            'modeled_stream_sha256': hashlib.sha256(modeled.encode()).hexdigest(),
                            'pipeline_object_sha256': hashlib.sha256(pipeline_bytes).hexdigest(),
                            'genuine_object_sha256': hashlib.sha256(lnk).hexdigest(),
                            'comparison': comparison, 'pipeline_retail': pipeline_retail,
                            'genuine_retail': retail, 'unknown_records': []}
                attempts.append({'mode': label, 'comparison': {k: comparison[k] for k in
                                 ('exact', 'diff', 'len_m', 'len_g', 'missing')}, 'retail': retail})
            raise ValueError('compiler model did not prove named functions: ' + json.dumps(attempts))
    finally:
        A.TMP = old_tmp


def symbols(path, wanted):
    result = subprocess.check_output(['mipsel-linux-gnu-nm', '-n', '--defined-only', str(path)], text=True)
    found = {}
    for line in result.splitlines():
        parts = line.split()
        if len(parts) != 3 or parts[2] not in wanted:
            continue
        if parts[2] in found:
            raise ValueError('ambiguous linked owned symbol: ' + parts[2])
        found[parts[2]] = {'address': int(parts[0], 16), 'kind': parts[1]}
    return found


RDATA_VMA, RDATA_FILE = 0x8002D000, 0x800


def rodata_placement(link_map, obj_rel):
    """(VMA, size) of one owner object's .rodata input section in an ld -Map listing, or None."""
    import re
    found = re.findall(r'^ \.rodata\s+0x([0-9a-f]+)\s+0x([0-9a-f]+) ' + re.escape(obj_rel) + r'$', link_map, re.M)
    if len(found) > 1:
        raise ValueError('ambiguous .rodata placement: ' + obj_rel)
    return (int(found[0][0], 16), int(found[0][1], 16)) if found else None


def prove_rodata(module, records, parsed_obj, linked_nm, image, undefined_syms, placement):
    """A compiler-emitted jump-table owner (docs/evidence/slus_rodata_migration.md).

    The table is a compiler-local label and its object bytes are unrelocated, so the
    initialized-data proof does not apply.  Instead: the object's .rodata is exactly the owned
    span with no symbol; every relocation is R_MIPS_32 into one of the member functions (within
    its extent) and every other word is .align 3 zero padding; the linker map places the section
    at the first record's VMA; the owner's own text addresses its table there (HI16/LO16 against
    .rodata, resolved from the linked image); each relocated word, recomputed from the linked
    function address plus its addend, equals the image word; the image bytes equal the retail
    record bytes; and the absolute jtbl_ assignment is gone, with no linked symbol of that name.
    """
    name = module['name']
    funcs = {f for member in module['members'] for f in member['functions']}
    base = records[0]['vram']
    span = records[-1]['vram'] + records[-1]['size'] - base
    body = parsed_obj.sections.get('.rodata')
    if body is None or len(body) != span:
        raise ValueError('owner .rodata size differs from the owned span: ' + name)
    if any(sym[0] == '.rodata' for sym in parsed_obj.symbols.values()):
        raise ValueError('owner .rodata defines a symbol; expected a compiler-local table: ' + name)
    for datum in records:
        symbol = datum['symbol']
        if symbol in linked_nm or any(line.split('=')[0].strip() == symbol
                                      for line in undefined_syms.splitlines() if '=' in line):
            raise ValueError('absolute or linked table symbol survives: ' + symbol)
    table = {}
    for section, offset, rtype, target, addend in parsed_obj.relocs:
        if section != '.rodata':
            continue
        func = target[1][len('.text.'):] if target[0] == 'sec' and target[1].startswith('.text.') else None
        extent = parsed_obj.symbols.get(func) if func else None
        if (rtype != '32' or func not in funcs or offset % 4 or offset in table
                or not extent or not 0 <= addend - extent[1] < extent[3]):
            raise ValueError(f'owner .rodata+{offset:#x} is not a table word into a member function: {name}')
        table[offset] = (func, addend - extent[1])
    if 0 not in table:
        raise ValueError('owner .rodata does not start with a table word: ' + name)
    for word in range(0, span, 4):
        if word in table:
            continue
        following = [o for o in table if o > word]
        if body[word:word + 4] != bytes(4) or not following or min(following) % 8 or min(following) - word > 4:
            raise ValueError(f'unrelocated word at .rodata+{word:#x} is not .align 3 padding: {name}')
    if placement != (base, span):
        raise ValueError('linker map placement differs from the owned VMA/span: ' + name + ' ' + str(placement))
    image_at = lambda vma: base_foff + (vma - base)
    base_foff = base - RDATA_VMA + RDATA_FILE
    resolved = 0
    for offset, (func, delta) in sorted(table.items()):
        got = int.from_bytes(image[image_at(base + offset):image_at(base + offset) + 4], 'little')
        entry = linked_nm.get(func)
        if not entry or got != entry['address'] + delta:
            raise ValueError(f'linked table word .rodata+{offset:#x} does not resolve into {func}: {name}')
        resolved += 1
    refs = 0
    for section, offset, rtype, target, addend in parsed_obj.relocs:
        if target != ('sec', '.rodata') or rtype != 'HI16' or not section.startswith('.text.'):
            continue
        func = section[len('.text.'):]
        los = [r for r in parsed_obj.relocs if r[0] == section and r[2] == 'LO16'
               and r[3] == ('sec', '.rodata') and r[1] > offset]
        if func not in funcs or func not in linked_nm or not los:
            raise ValueError('unpaired or foreign table reference: ' + section)
        lo_off = min(r[1] for r in los)
        text = linked_nm[func]['address'] - RDATA_VMA + RDATA_FILE
        hi = int.from_bytes(image[text + offset:text + offset + 4], 'little') & 0xFFFF
        lo = int.from_bytes(image[text + lo_off:text + lo_off + 4], 'little') & 0xFFFF
        value = ((hi << 16) + (lo - 0x10000 if lo & 0x8000 else lo)) & 0xFFFFFFFF
        if (value - addend) & 0xFFFFFFFF != base:
            raise ValueError(f'{func} addresses its table at {(value - addend) & 0xFFFFFFFF:#x}, not {base:#x}')
        refs += 1
    if not refs:
        raise ValueError('no member function addresses the owned table: ' + name)
    proofs = []
    for datum in records:
        foff = int(Path(datum['asset']).stem, 16) + datum['offset']
        if image[foff:foff + datum['size']] != bytes.fromhex(datum['bytes']):
            raise ValueError('linked table bytes differ: ' + datum['symbol'])
        proofs.append(dict(datum, object_offset=datum['vram'] - base, object_binding='compiler-local'))
    return {'size': span, 'bytes': body.hex(), 'symbols': proofs, 'placement': [base, span],
            'table_words': resolved, 'align_pads': [w for w in range(0, span, 4) if w not in table],
            'text_references': refs}


def prove_data(module, parsed_obj, linked_nm, image, rodata=None):
    """Verify real section storage, including zero-filled NOBITS, and linked bytes.

    `rodata` = {'undefined_syms': text, 'placement': (VMA, size) or None} for a jump-table owner.
    """
    groups = data_sections(module)
    if not groups:
        raise ValueError('module has no owned data: ' + module['name'])
    sections = {}
    for section, records in groups.items():
        if section == '.rodata':
            if rodata is None:
                raise ValueError('a .rodata owner requires link context: ' + module['name'])
            sections[section] = prove_rodata(module, records, parsed_obj, linked_nm, image,
                                             rodata['undefined_syms'], rodata['placement'])
            continue
        actual = parsed_obj.sections.get(section)
        expected = b''.join(bytes.fromhex(d['bytes']) for d in records)
        if actual != expected:
            raise ValueError('object section bytes or size differ: ' + module['name'] + ' ' + section)
        offset = 0
        proofs = []
        for datum in records:
            name = datum['symbol']
            own = parsed_obj.symbols.get(name)
            if (not own or own[0] != section or own[1] != offset
                    or own[2] not in ('global', 'local')):
                raise ValueError('object ownership/section/offset differs: ' + name)
            linked = linked_nm.get(name)
            if (not linked or linked['kind'].upper() in ('A', 'C', 'U')
                    or linked['address'] != datum['vram']):
                raise ValueError('linked ownership/address differs: ' + name)
            foff = int(Path(datum['asset']).stem, 16) + datum['offset']
            if image[foff:foff + datum['size']] != bytes.fromhex(datum['bytes']):
                raise ValueError('linked data bytes differ: ' + name)
            proofs.append(dict(datum, object_offset=offset, object_binding=own[2],
                               linked_kind=linked['kind']))
            offset += datum['size']
        sections[section] = {'size': len(actual), 'bytes': actual.hex(), 'symbols': proofs}
    return {'sections': sections}


def rodata_link_map(dest):
    """Relink the calibrated view with -Map (same command, side output); the ELF must not change."""
    command = subprocess.check_output(['ninja', '-t', 'commands', 'build/slus_006.14.elf'], cwd=dest,
                                      text=True).strip().splitlines()[-1]
    if ' -o build/slus_006.14.elf ' not in command + ' ':
        raise ValueError('unexpected link command: ' + command)
    probe = command.replace('-o build/slus_006.14.elf', '-o build/ownership_map.elf -Map build/ownership.map')
    subprocess.run(probe, shell=True, cwd=dest, check=True)
    if (dest / 'build/ownership_map.elf').read_bytes() != (dest / 'build/slus_006.14.elf').read_bytes():
        raise ValueError('map relink differs from the gated ELF')
    return (dest / 'build/ownership.map').read_text()


def prove(names, compiler_model_rows=()):
    declared = {m['name']: m for m in modules()}
    selected = [declared[name] for name in names]
    modeled_ids = selected_model_rows(selected, compiler_model_rows)
    physical = {module['name']: descriptor for module in selected
                if (descriptor := physical_descriptor(module)) is not None}
    for module in selected:
        if module['name'] in physical and any(member['id'] in modeled_ids for member in module['members']):
            raise ValueError('connected physical owner requires direct genuine proof; '
                             'an individual compiler-model row is insufficient: ' + module['name'])
    model_code_before = compiler_model_code() if modeled_ids else None
    by_id = {r['id']: r for r in rows()}
    ids = [member['id'] for module in selected for member in module['members']]
    part_only = [module for module in selected if module.get('partition_only')]
    for module in part_only:
        descriptor = physical.get(module['name'])
        if not descriptor or any(c['kind'] != 'part' for c in descriptor['contributors']):
            raise ValueError('partition-only owner lacks complete contributor context: ' + module['name'])
        ids.extend(c['row'] for c in descriptor['contributors'])
    ids = list(dict.fromkeys(ids))
    initial = {rid: fingerprint(by_id[rid]) for rid in ids}
    tool_fp = verifier_fingerprint()
    data = {}
    with tempfile.TemporaryDirectory(prefix='slus_ownership_') as temp:
        view = SlusView(Path(temp) / 'build')
        gate = view.calibrate()
        if gate['result'] != 'MATCH':
            raise ValueError('full retail gate failed: ' + str(gate))
        recipe = (view.dest / 'build.ninja').read_bytes()
        if recipe != (ROOT / 'ledger/splits/slus.build.ninja').read_bytes():
            raise ValueError('generated recipe differs from the pinned build')
        image = (view.dest / 'build/slus_006.14').read_bytes()
        wanted = {d['symbol'] for m in selected for d in m['data']}
        owners = [m for m in selected if any(d['section'] == '.rodata' for d in m['data'])]
        # A jump-table owner is proven through its member functions' linked addresses.
        wanted |= {f for m in owners for member in m['members'] for f in member['functions']}
        linked = symbols(view.dest / 'build/slus_006.14.elf', wanted)
        link_map = rodata_link_map(view.dest) if owners else ''
        undefined_syms = ((view.dest / 'build/slus_006.14.undefined_syms.modules.txt').read_text()
                          if owners else '')
        for module in selected:
            obj = view.dest / 'build' / Path(module['source']).with_suffix('.o')
            # Reject ambiguous object names before the reader's keyed symbol
            # view can discard a duplicate entry.
            symbols(obj, {d['symbol'] for d in module['data']})
            # The ELF reader materializes NOBITS from its recorded section size,
            # so an absent section cannot pass as a zero-length binary dump.
            parsed = A.read_elf(obj.read_bytes())
            context = None
            if module in owners:
                context = {'undefined_syms': undefined_syms,
                           'placement': rodata_placement(link_map, str(obj.relative_to(view.dest)))}
            data[module['name']] = prove_data(module, parsed, linked, image, rodata=context)
            if module.get('data_pieces'):
                from slus_data_pieces import verify_data_pieces
                data[module['name']]['transformation'] = verify_data_pieces(obj, module)
    old_versions = A.VERSIONS
    A.VERSIONS = ['2.79']
    try:
        results = {}
        modeled_results = {}
        for module in selected:
            if module.get('partition_only'):
                descriptor = physical[module['name']]
                for contributor in descriptor['contributors']:
                    rid = contributor['row']
                    if rid not in results:
                        results[rid] = A.process_row(by_id[rid])
                    record = results[rid]
                    check_partition_record(record, contributor, descriptor, initial[rid])
                    check_data_piece_record(module, record, descriptor)
                    print(module['name'] + ' via ' + rid + ': full owner direct genuine and retail exact', flush=True)
                continue
            for member in module['members']:
                rid = member['id']
                record = A.process_row(by_id[rid])
                check_data_piece_record(module, record, physical.get(module['name']))
                if module['name'] in physical:
                    check_physical_record(record, member, physical[module['name']], initial[rid])
                else:
                    check_member_record(record, member, initial[rid], modeled=rid in modeled_ids)
                results[rid] = record
                if rid in modeled_ids:
                    modeled_results[rid] = prove_compiler_model(by_id[rid], member)
                    # A.process_row traces the whole module. Its fired list is
                    # preserved in the direct record, not attributed to this row.
                    print(rid + ': retail exact; genuine exact after explicit t272 model', flush=True)
                else:
                    print(rid + ': direct genuine and retail exact', flush=True)
    finally:
        A.VERSIONS = old_versions
    if verifier_fingerprint() != tool_fp or any(fingerprint(by_id[rid]) != initial[rid] for rid in ids):
        raise ValueError('verification inputs changed while proving ownership')
    if modeled_ids and compiler_model_code() != model_code_before:
        raise ValueError('compiler-model code changed while proving ownership')
    receipt = {'schema': 2, 'at': time.strftime('%Y-%m-%dT%H:%M:%SZ', time.gmtime()),
            'purpose': 'data ownership only; no L4/L5 placement certificate',
            'modules': names, 'module_fingerprints': initial, 'tool_fingerprint': tool_fp,
            'recipe_sha256': hashlib.sha256(recipe).hexdigest(),
            'image_sha1': hashlib.sha1(image).hexdigest(), 'gate': gate, 'data': data, 'rows': results}
    if modeled_ids:
        receipt['schema'] = 3
        receipt['purpose'] = ('data ownership with explicit accepted compiler epilogue model; '
                              'genuine equality is after that model, not direct; no L4/L5 certificate')
        receipt['compiler_model'] = {'name': COMPILER_MODEL, 'explicit_rows': sorted(modeled_ids),
                                     'code': model_code_before, 'code_after': compiler_model_code(),
                                     'fired_passes_scope': 'A.process_row traces whole module; not row attribution'}
        receipt['modeled_rows'] = modeled_results
    if physical:
        receipt['schema'] = 4
        receipt['physical_modules'] = physical
        receipt['purpose'] = ('data ownership with direct full-TU genuine proof for connected owners; '
                              'any legacy compiler-model rows remain explicitly labelled; no L4/L5 certificate')
    if part_only:
        receipt['schema'] = 5
        receipt['partition_only_modules'] = [module['name'] for module in part_only]
        receipt['purpose'] += ('; collector records preserve full logical coverage, but direct genuine '
                               'equality is required only for selected complete physical owners')
    return receipt


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('modules', nargs='+')
    parser.add_argument('--output', type=Path, required=True)
    parser.add_argument('--compiler-model-row', action='append', default=[], metavar='ROW',
                        help='explicit selected member ID allowed the accepted t272 compiler epilogue model')
    args = parser.parse_args()
    receipt = prove(args.modules, compiler_model_rows=args.compiler_model_row)
    args.output.parent.mkdir(parents=True, exist_ok=True)
    pending = args.output.with_suffix('.tmp')
    pending.write_text(json.dumps(receipt, indent=2) + '\n')
    pending.replace(args.output)
    print(json.dumps({'modules': len(receipt['modules']), 'rows': len(receipt['rows']),
                      'gate': receipt['gate'], 'image_sha1': receipt['image_sha1']}))


if __name__ == '__main__':
    main()
