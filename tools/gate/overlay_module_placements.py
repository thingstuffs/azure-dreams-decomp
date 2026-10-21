"""Complete native TU placements. Descriptors are intent; only fresh shards grant rows.

The production format admits uniform-recipe contiguous native TUs, including
their complete owned rodata heads. Separated allocation/BSS placements fail
closed until every allocation has a destination model.
"""
from __future__ import annotations

import dataclasses
import fcntl
import hashlib
import json
import os
from pathlib import Path
import re
import shutil
import struct
import sys
import tempfile

import linklist

SCHEMA = 'azure-clean.module-placements.v1'
SHARD_SCHEMA = 'azure-clean.module-placement-proof.v1'
MANIFEST = 'config/overlays/module_placements.json'


def authority():
    import overlay_module_gate
    return overlay_module_gate


def review_complete(review):
    return (isinstance(review, dict) and set(review) == {'membership', 'types', 'ownership', 'reviewer'}
            and all(review[k] == 'reviewed' for k in ('membership', 'types', 'ownership'))
            and isinstance(review['reviewer'], str) and bool(review['reviewer'].strip())
            and review['reviewer'] != 'pending')


def review_descriptor(p):
    return {k: v for k, v in p.items() if k not in ('container', 'projected')}


def review_reason(p, root):
    """Production review must name this exact tuple, not only a reused key."""
    G = authority()
    records = []
    for name in p['review_inputs']:
        if not name.endswith('.json'):
            continue
        doc = G.read_json(G.local(root, name))
        if doc.get('schema') == 'azure-clean.module-placement-review.v2':
            records.append(doc)
    if len(records) != 1:
        return 'module placement needs one explicit v2 destination review record'
    doc = records[0]
    if (doc.get('placement_descriptor') != review_descriptor(p) or doc.get('review') != p['review']
            or doc.get('module') != p['module'] or doc.get('placement') != p['key'] or not doc.get('basis')):
        return 'module placement destination review tuple differs'
    return None


def load(root, modules=None):
    import overlay_scoped_fingerprint as S
    G=authority(); root=Path(root).absolute()
    return S.memo(('module-placements',str(root),None if modules is None else G.hashed(modules)),
                  lambda:_load(root,modules))


def _load(root, modules=None):
    """Validate the whole intended roster, never infer a sparse member placement."""
    G = authority(); root = Path(root)
    import overlay_scoped_fingerprint as S
    if S._exists(root/'config/overlay_modules_disabled') or not S._exists(root / MANIFEST):
        return []
    # linklist has its own identity cache. Observe its cached inputs explicitly
    # so a cached decode cannot conceal a changed binding or image namespace.
    S.observe(linklist.link_dir(root))
    if linklist.link_dir(root).is_dir():
        for d in linklist.link_dir(root).iterdir():
            S.observe(d)
    for path in linklist.files(root):
        S.observe(path)
    doc = G.read_json(root / MANIFEST)
    if set(doc) != {'schema', 'placements'} or doc['schema'] != SCHEMA:
        raise ValueError('unsupported module placement manifest')
    mods = {m['key']: m for m in (G.load_modules(root) if modules is None else modules)}
    reg = G.rows(root); tables = linklist.load(root); images, _, entries, _ = tables
    used = set(); keys = set(); out = []
    splits = {}
    home_members = {a['id'] for m in mods.values() for a in G.all_members(m)}
    occupied = [(m['container'], lo, hi) for m in mods.values() for lo, hi in G.module_extents(m)]
    for raw in doc['placements']:
        if set(raw) - {'allocations'} != {'key', 'module', 'image', 'home_image', 'recipe', 'members', 'imports', 'review', 'review_inputs'}:
            raise ValueError('module placement descriptor keys differ')
        key = raw['key']
        if not isinstance(key, str) or not re.fullmatch('[a-z][a-z0-9_]*', key) or key in keys or key in mods:
            raise ValueError('duplicate/invalid module placement key')
        keys.add(key)
        m = mods[raw['module']]; img = images[raw['image']]
        if G.Z.enabled(m) and (m.get('allocation_model') != G.Z.MODEL or G.Z.switches(m)):
            raise ValueError('module placement switch-allocation/BSS model not supported')
        if G.Z.enabled(m) != ('allocations' in raw):
            raise ValueError('module placement complete allocation inventory required')
        if m['owned_data']:
            G.validate_owned_layout(m)
        elif m.get('data_members') or any(a.get('body_offset') for a in m['members']):
            raise ValueError('module placement prefix lacks owned native payload')
        if img['container'] != m['container']:
            raise ValueError('cross-container module placement not supported')
        if raw['recipe'] != m['recipe']:
            raise ValueError('module placement recipe differs')
        if not raw['review_inputs'] or len(set(raw['review_inputs'])) != len(raw['review_inputs']):
            raise ValueError('module placement missing/duplicate evidence')
        for name in raw['review_inputs']:
            G.local(root, name).read_bytes()
        if [x.get('home') for x in raw['members']] != [a['id'] for a in G.all_members(m)]:
            raise ValueError('module placement missing/reordered siblings')
        projected = []; anchors = []; displacement = None
        for a, x in zip(G.all_members(m), raw['members']):
            if set(x) != {'home', 'row'}:
                raise ValueError('module placement member keys differ')
            rid = x['row']; r = reg[rid]; e = entries[rid]; h = entries[a['id']]
            if rid in used or rid in home_members or rid == a['id']:
                raise ValueError('duplicate module placement ownership')
            used.add(rid)
            if (e['home'] != a['id'] or e['image'] != img['image'] or r.get('source_row') != a['id']
                    or e['tu'] != a['source'] or e['size'] != a['size']
                    or (r['container'], r['foff'], r['size']) != (img['container'], e['foff'], e['size'])
                    or r['cfg'] != m['recipe']['cfg'] or (r.get('row_asflags') or '') != m['recipe']['row_asflags']
                    or (h['foff'], h['vma'], h['size'], h['tu']) != (a['foff'], a['vma'], a['size'], a['source'])):
                raise ValueError('module placement registry/link/home identity differs: ' + rid)
            delta = (e['foff'] - a['foff'], e['vma'] - a['vma'])
            if displacement is not None and delta != displacement:
                raise ValueError('module placement natural member layout differs')
            displacement = delta
            projected.append(dict(a, id=rid, foff=e['foff'], vma=e['vma']))
            anchors.append(e)
            fam = img['container']
            if fam not in splits:
                by_id = {}
                for s in G.read_records(root / 'ledger/splits' / (fam + '.jsonl')):
                    if not s.get('rerun'):
                        by_id.setdefault(fam + '/' + str(s.get('func_vram')), []).append(s)
                splits[fam] = by_id
            live = splits[fam].get(rid, [])
            if (len(live) != 1 or live[0].get('result') != 'MATCH' or live[0].get('source_kind', 'c') != 'c'
                    or (live[0]['foff'], live[0]['size'], linklist.split_vma(live[0])) != (e['foff'], e['size'], e['vma'])):
                raise ValueError('module placement split identity differs: ' + rid)
        first = projected[0]; end = projected[-1]['foff'] + projected[-1]['size']
        if not img['foff'] <= first['foff'] < end <= img['foff'] + img['size']:
            raise ValueError('complete module outside placement image')
        extents = [(a['foff'], a['foff'] + a['size']) for a in projected]
        if G.Z.enabled(m):
            expected = [dict(a, foff=a['foff'] + displacement[0], vma=a['vma'] + displacement[1]) for a in m['allocations']]
            if raw['allocations'] != expected:
                raise ValueError('module placement complete native allocations differ')
            extents = [(a['foff'], a['foff'] + a['size']) for a in expected]
            if any(not img['foff'] <= lo < hi <= img['foff'] + img['size'] for lo, hi in extents):
                raise ValueError('native allocation outside placement image')
        if any(c == img['container'] and lo < stop and start < hi for lo, hi in extents for c, start, stop in occupied):
            raise ValueError('overlapping module placement native ownership')
        occupied.extend((img['container'], lo, hi) for lo, hi in extents)
        # Every byte of every member must have proven load-map coverage, even
        # when a fragmented rowbase ledger uses several adjacent regions.
        regions = G.ranges(root, img['container'])
        for start, stop in extents:
            cursor = start
            for r in sorted(regions, key=lambda r: linklist.num(r['foff_start'])):
                lo, hi = (linklist.num(r[k]) for k in ('foff_start', 'foff_end'))
                if hi <= cursor or lo >= stop:
                    continue
                if lo > cursor or r['base_confidence'] != 'proven' or linklist.num(r['delta']) != img['vma'] - img['foff']:
                    raise ValueError('module placement rowbase differs')
                cursor = min(hi, stop)
            if cursor != stop:
                raise ValueError('module placement rowbase incomplete')
        himg=images[raw['home_image']]
        for a in G.all_members(m):
            if (himg['container']!=m['container'] or not himg['foff']<=a['foff']<a['foff']+a['size']<=himg['foff']+himg['size']
                    or a['vma']-a['foff']!=himg['vma']-himg['foff']):
                raise ValueError('explicit module home image extent/load differs')
        if G.Z.enabled(m) and any(not himg['foff'] <= a['foff'] < a['foff'] + a['size'] <= himg['foff'] + himg['size']
                                 or a['vma'] - a['foff'] != himg['vma'] - himg['foff'] for a in m['allocations']):
            raise ValueError('explicit home image omits native allocation')
        if [d['symbol'] for d in raw['imports']] != [d['symbol'] for d in m['imports']]:
            raise ValueError('module placement import inventory differs')
        for old, new in zip(m['imports'], raw['imports']):
            targets = {linklist._binding(tables, e, old['vma'], raw['home_image']) for e in anchors}
            if len(targets) != 1 or new.get('vma') != next(iter(targets)) or new.get('kind') != old['kind']:
                raise ValueError('module placement external bindings disagree')
            if old['kind'] == 'function':
                if set(new) != {'symbol', 'kind', 'vma'}:
                    raise ValueError('module placement function import keys differ')
            else:
                if new.get('view_bytes') != old['view_bytes']:
                    raise ValueError('module placement storage view extent differs')
                if new['kind'] == 'runtime_data':
                    if new != old:
                        raise ValueError('runtime storage cannot move with module')
                    G.validate_runtime(root, new)
                else:
                    # A shifted address is not an ownership/extent proof.
                    if new.get('evidence') not in raw['review_inputs']:
                        raise ValueError('module placement storage evidence not bound')
                    validate_storage(root, new, raw, images=images)
        out.append(dict(raw, container=img['container'], projected=projected))
    return out


def owner(root, row, modules=None):
    """Physical TU identity; row_relative continues to name the logical member."""
    G = authority(); mods = G.load_modules(root) if modules is None else modules
    for m in mods:
        if row in {a['id'] for a in G.all_members(m)}:
            return m
    for p in load(root, mods):
        if row in {a['id'] for a in p['projected']}:
            return next(m for m in mods if m['key'] == p['module'])
    return None


def validate_storage(root, view, placement, *, images=None):
    """Explicit destination views, with a current load image and bounded extent.

    This proves a declared view's map, not its types or ownership review. Those
    remain separately mandatory at production issuance and in the reader.
    """
    G = authority(); proof = G.read_json(G.local(root, view['evidence']))
    mp = proof['maps'][view['map']]
    if mp.get('kind') != 'link_image':
        return G.validate_asset(root, view)
    images = linklist.load(root)[0] if images is None else images
    image = images[mp['image']]
    code_image = images[placement['image']]
    path = str(Path(image['path']).relative_to(root))
    asset = 'work/disc/containers/' + G.CONTAINERS[image['container']]
    if (proof['views'].get(view['symbol']) != view or not mp.get('basis')
            or image['container'] != code_image['container']
            or image['vma'] - image['foff'] != code_image['vma'] - code_image['foff']
            or not image['foff'] <= code_image['foff'] < code_image['foff'] + code_image['size'] <= image['foff'] + image['size']
            or mp['link_list'] != path or mp['asset'] != asset or view['asset'] != asset
            or view['owner'] != 'retail_asset:' + asset or view['view_bytes'] <= 0
            or (mp['file_start'], mp['file_end'], mp['delta']) != (image['foff'], image['foff'] + image['size'], image['vma'] - image['foff'])
            or view['vma'] != view['foff'] + mp['delta']
            or not mp['file_start'] <= view['foff'] < view['foff'] + view['view_bytes'] <= mp['file_end']):
        raise ValueError('module placement destination storage view/load image differs')


def windows(p, root):
    m = dict(container=p['container'], members=p['projected'], owned_data=[])
    if 'allocations' in p:
        m.update(allocation_model=authority().Z.MODEL, allocations=p['allocations'])
    return authority().affected_windows(m, root)


def intersects(p, start, end):
    return any(start < a['foff'] + a['size'] and a['foff'] < end for a in p.get('allocations', p['projected']))


def affected_windows(m, root):
    G = authority()
    return sorted(set(G.affected_windows(m, root)) | {w for p in load(root) if p['module'] == m['key'] for w in windows(p, root)})


def inputs(p, root):
    """No certificate/window dependencies here: this value can enter window digests."""
    G = authority(); root = Path(root)
    names = set(p['review_inputs']) | set(linklist.window_files(root, [a['id'] for a in p['projected']]))
    home_image=linklist.load(root)[0][p['home_image']]
    names.add(str(Path(home_image['path']).relative_to(root)))
    names.add('config/overlays/' + p['container'] + '.rowbase.jsonl')
    storage = {}
    for d in p['imports']:
        if d['kind'] != 'data':
            continue
        proof = G.read_json(G.local(root, d['evidence']))
        mapping = proof['maps'][d['map']]
        if mapping.get('kind') == 'link_image':
            names.add(mapping['link_list'])
        with G.local(root, d['asset']).open('rb') as f:
            f.seek(d['foff']); blob = f.read(d['view_bytes'])
        if len(blob) != d['view_bytes']:
            raise ValueError('truncated module placement storage view')
        storage[d['symbol']] = hashlib.sha256(blob).hexdigest()
    return {'descriptor': p, 'inputs': {n: G.sha(G.local(root, n)) for n in sorted(names)}, 'storage': storage}


def fingerprint(p, m, root, with_windows=True):
    import overlay_scoped_fingerprint as S
    G=authority();root=Path(root).absolute()
    return S.memo(('module-placement-fingerprint',str(root),G.hashed(p),G.hashed(m),with_windows),
                  lambda:_fingerprint(p,m,root,with_windows))


def _fingerprint(p, m, root, with_windows):
    G = authority(); import overlay_scoped_fingerprint as S
    root = Path(root); result = inputs(p, root)
    result['artifact'] = G.fingerprint(m, root, windows=False)
    result['registry'] = [G.rows(root)[a['id']] for a in p['projected']]
    result['retail'] = hashlib.sha256(retail(p, root)).hexdigest()
    if with_windows:
        reg, assign, splits, regions, owners, mods, physical, wins = S.validate(root, G)
        levels = {r['id']: r for r in G.read_jsonl(root / 'ledger/levels.jsonl')}
        baseline = {r['id']: r for r in G.read_jsonl(root / 'ledger/baseline.jsonl')}
        result['windows'] = {wn: S.memo(('module-placement-window',str(root),wn,G.__name__),
                             lambda wn=wn:S._window_digest(root, wn, wins, splits, reg, physical, assign, regions,
                             owners, mods, levels, baseline, p['container'], G)) for wn in windows(p, root)}
    return {'schema': SHARD_SCHEMA, 'sha256': G.hashed(result), 'inputs': result}


def retail(p, root):
    G = authority()
    if 'allocations' in p:
        spans = [(a['foff'], a['size']) for a in sorted(p['allocations'], key=lambda a: a['foff'])]
    else:
        spans = [(p['projected'][0]['foff'], sum(a['size'] for a in p['projected']))]
    result = bytearray()
    with (Path(root) / 'work/disc/containers' / G.CONTAINERS[p['container']]).open('rb') as f:
        for start, size in spans:
            f.seek(start); blob = f.read(size)
            if len(blob) != size:
                raise ValueError('truncated complete module placement')
            result.extend(blob)
    return bytes(result)


def artifact(m, root):
    """Content addressed, locked, independently revalidated whole-home artifact."""
    G = authority(); root = Path(root).absolute()
    from overlay_module_evidence import receipt_reason
    before = G.fingerprint(m, root, windows=False)
    out = root / 'work/module_artifacts' / m['key'] / before['sha256']
    out.parent.mkdir(parents=True, exist_ok=True)
    with out.with_suffix('.lock').open('a') as lock:
        fcntl.flock(lock, fcntl.LOCK_EX)
        try:
            receipt = json.loads((out / 'receipt.json').read_text())
            if receipt.get('fingerprint') != before or receipt_reason(m, receipt, root, str(out.relative_to(root))):
                raise ValueError('stale artifact')
        except (OSError, ValueError, KeyError, TypeError):
            if out.exists():
                shutil.rmtree(out)
            receipt, _ = G.build(m, out, root, artifact_only=True)
            reason = receipt_reason(m, receipt, root, str(out.relative_to(root)))
            if reason:
                raise ValueError(reason)
        if before != G.fingerprint(m, root, windows=False):
            raise ValueError('module inputs changed during artifact reuse')
    return out


def home_build(m, out, root):
    """Use the same verified compile artifact for home and destination windows.

    The existing home certificate still binds its full home-window fingerprint;
    only its actual source/recipe build is shared with the placement shards.
    """
    G = authority(); root=Path(root).absolute(); out=Path(out).absolute()
    before=G.fingerprint(m,root)
    source=artifact(m,root)
    shutil.copytree(source,out,dirs_exist_ok=True)
    receipt=json.loads((out/'receipt.json').read_text())
    receipt['fingerprint']=before
    if G.fingerprint(m,root)!=before:
        raise ValueError('home module inputs changed during artifact adoption')
    (out/'receipt.json').write_text(json.dumps(receipt,indent=2)+'\n')
    return receipt,out/'module.bin'


def placed_views(root, obj, genuine):
    """Keep external symbol AND the reader's paired HI16/LO16 addend intact."""
    sys.path.insert(0, str(Path(root) / 'tools/fidelity'))
    import aspsx_diff as A
    class PlacedView(A.View):
        def canon(self, target, addend):
            kind, name = target
            s = self.obj.symbols.get(name)
            if kind == 'sym' and (s is None or s[0] is None) and name not in self.absmap:
                return ('sym', name, addend)
            return super().canon(target, addend)
    ma = PlacedView(A.read_elf(obj)); ge = PlacedView(A.read_lnk(genuine), ref=ma)
    if ma.obj.unknown or ge.obj.unknown or not A.compare_units(ma, ge)['exact']:
        raise ValueError('symbolic whole-TU genuine mismatch')
    return A, ma, ge


def placement_model(p, m):
    """Keep every native allocation and its home symbol spelling."""
    delta = p['projected'][0]['vma'] - first_member(m)['vma']
    model = dict(m, members=[a for a in p['projected'] if 'function' in a],
                 owned_data=[dict(d, vma=d['vma'] + delta,
                                  foff=d['foff'] + p['projected'][0]['foff'] - first_member(m)['foff']) for d in m['owned_data']])
    if 'allocations' in p:
        model['allocations'] = p['allocations']
    return model


def first_member(m):
    return authority().module_first(m)


def resolve_native(p, m, out, root):
    """Independently resolve BOTH real object legs at the destination."""
    G = authority(); model = placement_model(p, m); first = p['projected'][0]
    addresses = {d['symbol']: d['vma'] for d in p['imports']}
    addresses.update({a['function']: a['vma'] + a.get('body_offset', 0) for a in model['members']})
    addresses.update({d['symbol']: d['vma'] for d in model['owned_data'] if d.get('symbol')})
    A, ma, ge = placed_views(root, (out/'artifact/module.o').read_bytes(), (out/'artifact/OUT.OBJ').read_bytes())
    if 'allocations' in p:
        G.Z.check_views(model, ma, ge, addresses)
        anchors = {a['section']: a['vma'] for a in p['allocations'] if a['section'] != '.text.*'}
    else:
        anchors = {'.rodata': first['vma']} if model['owned_data'] else {}
    results = []
    for view in (ma, ge):
        data = bytearray()
        if 'allocations' in p:
            for allocation in sorted(p['allocations'], key=lambda a: a['foff']):
                if allocation['section'] != '.text.*':
                    section = '.rdata' if view is ge and allocation['section'] == '.rodata' else allocation['section']
                    if any(r[0] == section for r in view.obj.relocs):
                        raise ValueError('literal destination allocation contains relocation')
                    payload = view.obj.sections[section]
                    if len(payload) != allocation['size']:
                        raise ValueError('destination literal allocation extent differs')
                    data.extend(payload)
                else:
                    for a in model['members']:
                        words, masked = A.resolve_tokens(view, a['function'], a['vma'], addresses.get, 0x80080994, section_anchors=anchors)
                        if masked:
                            raise ValueError('unresolved destination allocation relocation')
                        data.extend(struct.pack('<' + 'I' * len(words), *words))
        else:
            prefix = sum(d['size'] for d in model['owned_data'])
            rosec = next((k for k in ('.rdata', '.rodata') if view.obj.sections.get(k)), None)
            if bool(rosec) != bool(prefix) or (rosec and len(view.obj.sections[rosec]) != prefix):
                raise ValueError('complete destination native head extent differs')
            if rosec:
                view.funcs['__owned_rodata'] = (rosec, 0, prefix)
                words, masked = A.resolve_tokens(view, '__owned_rodata', first['vma'], addresses.get, 0x80080994, section_anchors=anchors)
                if masked:
                    raise ValueError('unresolved destination native-head relocation')
                data.extend(struct.pack('<' + 'I' * len(words), *words))
            for a in model['members']:
                words, masked = A.resolve_tokens(view, a['function'], a['vma'] + a.get('body_offset', 0), addresses.get, 0x80080994, section_anchors=anchors)
                if masked:
                    raise ValueError('unresolved destination relocation')
                data.extend(struct.pack('<' + 'I' * len(words), *words))
        results.append(bytes(data))
    if results[0] != results[1] or len(results[0]) != G.module_size(m):
        raise ValueError('resolved complete destination genuine/ELF differs')
    return results[0]


def build(p, m, out, root):
    G = authority(); root = Path(root).absolute(); out = Path(out).absolute(); out.mkdir(parents=True, exist_ok=True)
    current = next(x for x in load(root) if x['key'] == p['key'])
    if current != p:
        raise ValueError('stale placement descriptor')
    before = fingerprint(p, m, root); home = artifact(m, root)
    shutil.copytree(home, out / 'artifact', dirs_exist_ok=True)
    obj = out / 'artifact/module.o'; first = p['projected'][0]
    addresses = {d['symbol']: d['vma'] for d in p['imports']}
    addresses.update({a['function']: a['vma'] + a.get('body_offset', 0) for a in p['projected'] if 'function' in a})
    displacement = first['vma'] - G.module_first(m)['vma']
    addresses.update({d['symbol']: d['vma'] + displacement for d in m['owned_data'] if d.get('symbol')})
    ld = out / 'placement.ld'
    script = 'OUTPUT_FORMAT("elf32-tradlittlemips")\nOUTPUT_ARCH(mips)\n_gp = 0x80080994;\n'
    script += ''.join(f'{d["symbol"]} = 0x{d["vma"]:X};\n' for d in p['imports']) + 'SECTIONS {\n'
    if 'allocations' in p:
        for i, a in enumerate(sorted(p['allocations'], key=lambda a: a['foff'])):
            script += f'.allocation_{i} 0x{a["vma"]:X} : SUBALIGN(4) {{ "{obj}"({a["section"]}) }}\nASSERT(SIZEOF(.allocation_{i}) == {a["size"]}, "complete allocation extent")\n'
    else:
        script += f'.module 0x{first["vma"]:X} : {{ {G.link_inputs(m, obj)} }}\nASSERT(SIZEOF(.module) == {G.module_size(m)}, "complete placement extent")\n'
    ld.write_text(script + '/DISCARD/ : { *(.text) *(.reginfo) *(.MIPS.abiflags) *(.pdr) *(.comment) *(.note*) *(.mdebug*) *(.gnu.attributes) }\n}\n')
    env = dict(os.environ, PYTHONDONTWRITEBYTECODE='1', TMPDIR=str(out))
    G.command(['mipsel-linux-gnu-ld', '-EL', '-T', ld, '-o', out / 'placement.elf', obj], root, env, out / 'link.log')
    if 'allocations' in p:
        packed = bytearray()
        for i, a in enumerate(sorted(p['allocations'], key=lambda a: a['foff'])):
            target = out / f'allocation_{i}.bin'
            G.command(['mipsel-linux-gnu-objcopy', '-O', 'binary', '-j', f'.allocation_{i}', out/'placement.elf', target], root, env, out/f'objcopy_{i}.log')
            part = target.read_bytes()
            if len(part) != a['size']:
                raise ValueError('linked destination allocation extent differs')
            packed.extend(part)
        (out/'placement.bin').write_bytes(packed)
    else:
        G.command(['mipsel-linux-gnu-objcopy', '-O', 'binary', out / 'placement.elf', out / 'placement.bin'], root, env, out / 'objcopy.log')
    nm = G.command(['mipsel-linux-gnu-nm', '-n', '-S', out / 'placement.elf'], root, env, out / 'symbols.log').decode()
    syms = {s[-1]: int(s[0], 16) for line in nm.splitlines() if len(s := line.split()) >= 3}
    if (any(syms.get(a['function']) != a['vma'] + a.get('body_offset', 0) for a in p['projected'] if 'function' in a)
            or any(syms.get(d['symbol']) != d['vma'] + displacement for d in m['owned_data'] if d.get('symbol'))):
        raise ValueError('natural complete-TU destination addresses differ')
    if 'allocations' in p and any(syms.get(slot['symbol']) != a['vma'] + slot['offset'] for a in p['allocations'] for slot in a.get('slots', [])):
        raise ValueError('natural destination storage symbol addresses differ')
    blob = (out / 'placement.bin').read_bytes()
    if blob != retail(p, root):
        raise ValueError('whole placement retail mismatch')
    data = resolve_native(p, m, out, root)
    if data != blob:
        raise ValueError('resolved destination genuine/ELF differs')
    (out / 'genuine.bin').write_bytes(data)
    if before != fingerprint(p, m, root):
        raise ValueError('placement inputs changed during build')
    receipt = dict(schema=SHARD_SCHEMA, module=m['key'], placement=p['key'], image=p['image'],
                   members=p['members'], fingerprint=before, artifact_sha256=G.sha(obj),
                   artifact_receipt_sha256=G.sha(out / 'artifact/receipt.json'),
                   gate=dict(result='MATCH', bytes=len(blob), masked=0, raw_substitution_bytes=0),
                   artifacts={n: G.sha(out / n) for n in ('placement.ld', 'placement.elf', 'placement.bin', 'genuine.bin')})
    (out / 'receipt.json').write_text(json.dumps(receipt, indent=2) + '\n')
    return receipt, out / 'placement.bin'


def project(segments, build_dir, overlay, root):
    G = authority(); receipts = []; mods = G.load_modules(root)
    for p in load(root, mods):
        if p['container'] != overlay.split('_')[0]:
            continue
        hits = [(i, s, a) for i, s in enumerate(segments) for a in p['projected']
                if s.start < a['foff'] + a['size'] and a['foff'] < s.end]
        model = placement_model(p, next(m for m in mods if m['key'] == p['module']))
        storage_hits = 'allocations' in p and any(intersects(p, s.start, s.end) for s in segments)
        if not hits and not storage_hits:
            continue
        m = next(m for m in mods if m['key'] == p['module'])
        for _, s, a in hits:
            if s.start != a['foff'] or s.size != a['size'] or s.kind != 'c' or not s.match:
                raise ValueError('module placement missing/raw/partial member')
            if s.match.config not in (m['recipe']['cfg'], m['recipe']['cfg'].replace('-G0', ' -G0')):
                raise ValueError('module placement window recipe differs')
            if Path(s.match.source).resolve() != (Path(root) / a['source']).resolve():
                raise ValueError('fileless module placement cannot stage member edits')
        receipt, binary = build(p, m, Path(build_dir) / 'modules' / p['key'], root)
        blob = binary.read_bytes()
        for i, s, a in hits:
            offset = G.Z.offset(model, a['foff'], a['size']) if 'allocations' in p else a['foff'] - p['projected'][0]['foff']
            target = binary.parent / (a.get('function', a.get('symbol')) + '.bin')
            target.write_bytes(blob[offset:offset + a['size']])
            segments[i] = dataclasses.replace(s, kind='rowbase', bytes_path=target, module_key=m['key'], module_placement=p['key'], module_artifact_sha256=receipt['artifact_sha256'], section=f'.ovlseg_{s.index:04d}')
        projected_allocations = []
        if 'allocations' in p:
            projected_allocations = G.Z.project_storage(model, segments, blob, binary.parent, root)
            for i, segment in enumerate(segments):
                if segment.module_key == m['key'] and segment.module_placement is None:
                    segments[i] = dataclasses.replace(segment, module_placement=p['key'], module_artifact_sha256=receipt['artifact_sha256'])
        receipts.append(dict(module=m['key'], placement=p['key'], image=p['image'], receipt=str(binary.parent / 'receipt.json'),
                             receipt_sha256=G.sha(binary.parent / 'receipt.json'), fingerprint=receipt['fingerprint']['sha256'],
                             artifact_sha256=receipt['artifact_sha256'], projected_rows=[a['id'] for _, _, a in hits], projected_allocations=projected_allocations))
    return receipts


def verify_projections(receipts, root):
    G = authority(); mods = {m['key']: m for m in G.load_modules(root)}
    ps = {p['key']: p for p in load(root, list(mods.values()))}
    for projection in receipts:
        p = ps[projection['placement']]; path = Path(projection['receipt'])
        r = json.loads(path.read_text())
        if G.sha(path) != projection['receipt_sha256'] or r['fingerprint'] != fingerprint(p, mods[p['module']], root):
            raise ValueError('module placement inputs changed during window gate')
        reason = receipt_reason(p, mods[p['module']], r, path.parent, root)
        if reason:
            raise ValueError(reason)


def receipt_reason(p, m, r, directory, root):
    G = authority(); out = Path(directory)
    from overlay_module_evidence import receipt_reason as home_reason
    if (r.get('schema') != SHARD_SCHEMA or r.get('module') != m['key'] or r.get('placement') != p['key']
            or r.get('image') != p['image'] or r.get('members') != p['members']
            or r.get('gate') != dict(result='MATCH', bytes=G.module_size(m), masked=0, raw_substitution_bytes=0)):
        return 'incomplete placement receipt identity'
    if r.get('artifact_sha256') != G.sha(out / 'artifact/module.o') or r.get('artifact_receipt_sha256') != G.sha(out / 'artifact/receipt.json'):
        return 'placement TU artifact changed'
    hr = json.loads((out / 'artifact/receipt.json').read_text())
    if hr.get('fingerprint') != G.fingerprint(m, root, windows=False):
        return 'placement artifact source/recipe/census changed'
    reason = home_reason(m, hr, Path(root), str((out / 'artifact').relative_to(Path(root))))
    if reason:
        return reason
    if set(r.get('artifacts', {})) != {'placement.ld', 'placement.elf', 'placement.bin', 'genuine.bin'}:
        return 'incomplete placement artifact inventory'
    for name, h in r['artifacts'].items():
        if G.sha(out / name) != h:
            return 'placement artifact changed: ' + name
    digest = hashlib.sha256(retail(p, root)).hexdigest()
    if any(r['artifacts'][n] != digest for n in ('placement.bin', 'genuine.bin')):
        return 'complete placement differs from retail'
    if resolve_native(p, m, out, root) != (out/'placement.bin').read_bytes():
        return 'destination symbolic object replay differs'
    return None


def proof_path(root, name):
    G = authority(); path = G.local(Path(root), name)
    if not path.resolve().is_relative_to(Path(root).resolve()):
        raise ValueError('module placement proof escapes root')
    return path


def certificate_reason(p, cert, root, *, scratch=False):
    """Recompute roster, artifact, shard and ALL exact destination window proofs."""
    G = authority(); root = Path(root).absolute()
    mods = G.load_modules(root); current = next(x for x in load(root, mods) if x['key'] == p['key'])
    if current != p:
        return 'module placement descriptor changed'
    m = next(m for m in mods if m['key'] == p['module'])
    kind = 'overlay_module_link_placement_scratch' if scratch else 'overlay_module_link_placement'
    if not scratch and (not review_complete(p['review']) or not review_complete(m['review'])):
        return 'module placement membership/type/ownership review incomplete'
    if not scratch:
        reason = review_reason(p, root)
        if reason:
            return reason
    if (cert.get('schema') != SHARD_SCHEMA or cert.get('kind') != kind or cert.get('placement') != p['key']
            or cert.get('module') != p['module'] or cert.get('image') != p['image'] or cert.get('members') != p['members']
            or cert.get('reviewer') != p['review']['reviewer']):
        return 'wrong module placement certificate identity'
    before = fingerprint(p, m, root)
    if cert.get('fingerprint') != before:
        return 'module placement source/header/recipe/import/map/census/window inputs changed'
    directory = proof_path(root, cert['proof_dir'])
    receipt = json.loads((directory / 'receipt.json').read_text())
    if (cert.get('receipt_sha256') != G.sha(directory / 'receipt.json') or receipt.get('fingerprint') != before
            or cert.get('artifact_sha256') != receipt.get('artifact_sha256')):
        return 'module placement receipt changed/stale'
    reason = receipt_reason(p, m, receipt, directory, root)
    if reason:
        return reason
    required = windows(p, root)
    if [w['config'] for w in cert.get('windows', [])] != required:
        return 'not every module placement destination window was gated'
    import yaml
    for w in cert['windows']:
        cfg = yaml.safe_load((root / w['config']).read_text()); scope = cfg['standalone_build']['window']
        fs, fe = (linklist.num(scope[k]) for k in ('file_start', 'file_end'))
        if w.get('digest') != before['inputs']['windows'][w['config']]['sha256'] or w.get('result') != 'MATCH':
            return 'module placement window digest/result differs'
        wp = proof_path(root, w['proof_dir'])
        if set(w.get('artifacts', {})) != {'window.bin', 'manifest.json', 'projection.json', 'gate.log', 'module/receipt.json'}:
            return 'incomplete module placement window artifact inventory'
        for name, h in w['artifacts'].items():
            if G.sha(wp / name) != h:
                return 'module placement window artifact changed'
        with (root / 'work/disc/containers' / G.CONTAINERS[p['container']]).open('rb') as f:
            f.seek(fs); expected = f.read(fe - fs)
        if len(expected) != fe - fs or (wp / 'window.bin').read_bytes() != expected:
            return 'module placement window differs from retail'
        pr = json.loads((wp / 'projection.json').read_text())
        selected = [a for a in p['projected'] if fs < a['foff'] + a['size'] and a['foff'] < fe]
        if (pr.get('module') != m['key'] or pr.get('placement') != p['key'] or pr.get('image') != p['image']
                or pr.get('projected_rows') != [a['id'] for a in selected] or pr.get('fingerprint') != before['sha256']
                or pr.get('artifact_sha256') != cert['artifact_sha256']
                or pr.get('receipt_sha256') != G.sha(wp / 'module/receipt.json')):
            return 'incomplete/shuffled module placement window projection'
        wr = json.loads((wp / 'module/receipt.json').read_text())
        if wr.get('fingerprint') != before:
            return 'module placement window TU proof stale'
        reason = receipt_reason(p, m, wr, wp / 'module', root)
        if reason:
            return reason
        manifest = json.loads((wp / 'manifest.json').read_text())
        expected_spans = [(a['foff'], a['size']) for a in selected]
        storage = G.Z.expected_storage_projection(placement_model(p, m), fs, fe) if 'allocations' in p else []
        if pr.get('projected_allocations', []) != storage:
            return 'module placement native allocation projection incomplete'
        expected_spans.extend((a['foff'], a['size']) for a in storage)
        starts = {start for start, size in expected_spans}
        spans = [(linklist.num(s['file_start']), s['size']) for s in manifest['c_segments']
                 if s.get('module') == m['key'] and linklist.num(s['file_start']) in starts]
        if spans != sorted(expected_spans):
            return 'module placement native window provenance incomplete'
        native=[s for s in manifest['c_segments'] if s.get('module')==m['key'] and linklist.num(s['file_start']) in starts]
        if any(s.get('module_placement')!=p['key'] or s.get('module_artifact_sha256')!=cert['artifact_sha256'] for s in native):
            return 'module placement window TU/placement identity differs'
    if fingerprint(p, m, root) != before:
        return 'module placement inputs changed during certificate validation'
    return None


def statuses(root):
    """The manifest is the intended index; an absent/failed shard grants nothing."""
    root = Path(root); result = []
    try:
        ps = load(root)
    except (OSError, ValueError, KeyError, TypeError, IndexError) as e:
        return [dict(placement=None, valid=False, reason=str(e))]
    for p in ps:
        cert = None
        try:
            cert = json.loads((root / 'ledger/modules' / ('placement_' + p['key'] + '.json')).read_text())
            reason = certificate_reason(p, cert, root)
        except (OSError, ValueError, KeyError, TypeError, IndexError) as e:
            reason = 'module placement certificate missing/invalid: ' + str(e)
        result.append(dict(placement=p, certificate=cert, valid=reason is None, reason=reason))
    return result


def valid_placements(root):
    result = {}
    for s in statuses(root):
        if not s['valid']:
            continue
        p = s['placement']; cert = s['certificate']
        for a in p['projected']:
            result[a['id']] = dict(outcome='applied', module=p['module'], placement=p['key'], image=p['image'],
                                   module_fingerprint=cert['fingerprint']['sha256'], artifact_sha256=cert['artifact_sha256'],
                                   placement_proof_sha256=cert['receipt_sha256'], window_proof_sha256=authority().hashed(cert['windows']))
    return result


def recorded_statuses(root):
    """Only already issued production shards are renewal obligations.

    Structurally valid pending intent does not revoke an unchanged home or
    force issuance. Removing an issued descriptor requires retiring its shard.
    """
    root=Path(root);paths=sorted((root/'ledger/modules').glob('placement_*.json'))
    if not paths:
        return []
    by_key={p['key']:p for p in load(root)};result=[]
    for path in paths:
        cert=json.loads(path.read_text());key=cert.get('placement')
        if key not in by_key or path.name!='placement_'+str(key)+'.json':
            raise ValueError('recorded placement absent from intended roster: '+path.name)
        p=by_key[key]
        try:
            reason=certificate_reason(p,cert,root)
        except (OSError,ValueError,KeyError,TypeError,IndexError) as e:
            reason='module placement certificate invalid: '+str(e)
        result.append(dict(placement=p,certificate=cert,valid=reason is None,reason=reason))
    return result


def certify(key, root, gate_receipts, transaction, *, output=None, scratch=False):
    """Adopt fresh canonical window receipts. Never run an implicit extra gate.

    Scratch mode checks the identical computational proof, writes only the
    caller's output, and is deliberately rejected by every production reader.
    """
    G = authority(); view = Path(root).absolute(); root = (view/'ledger').resolve().parent
    import overlay_scoped_fingerprint as S
    S.reject_environment()
    sys.path.insert(0, str(root / 'tools/fidelity'))
    from certify_overlay_module import fresh_window_source
    mods = G.load_modules(root); p = next(p for p in load(root, mods) if p['key'] == key)
    m = next(m for m in mods if m['key'] == p['module'])
    if not scratch and (not review_complete(p['review']) or not review_complete(m['review'])):
        raise ValueError('module placement review incomplete')
    if not scratch:
        reason = review_reason(p, root)
        if reason:
            raise ValueError(reason)
    if scratch and output is None:
        raise ValueError('scratch certificate requires an explicit output')
    before = fingerprint(p, m, root)
    # Unique content paths prevent a failed renewal from damaging an existing shard.
    parent = root / 'work/module_placement_proofs' / key
    parent.mkdir(parents=True,exist_ok=True)
    out = Path(tempfile.mkdtemp(prefix=before['sha256'][:16]+'-',dir=parent)); proofs = []
    for wn in windows(p, root):
        source = fresh_window_source(view, wn, gate_receipts, transaction)
        if source is None:
            raise ValueError('fresh canonical placement window receipt missing: ' + wn)
        records = json.loads((source / 'modules.json').read_text())
        matches = [r for r in records if r.get('placement') == key and r.get('module') == m['key']]
        if len(matches) != 1:
            raise ValueError('fresh window lacks exact module placement projection')
        pr = matches[0]; dest = out / 'windows' / source.name; dest.mkdir(parents=True, exist_ok=True)
        for name in ('window.bin', 'manifest.json', 'gate.log'):
            shutil.copy2(source / name, dest / name)
        (dest / 'projection.json').write_text(json.dumps(pr, indent=2) + '\n')
        shutil.copytree(source / 'modules' / key, dest / 'module', dirs_exist_ok=True)
        proofs.append(dict(config=wn, result='MATCH', digest=before['inputs']['windows'][wn]['sha256'],
                           proof_dir=str(dest.relative_to(root)), artifacts={n: G.sha(dest / n) for n in
                           ('window.bin', 'manifest.json', 'projection.json', 'gate.log', 'module/receipt.json')}))
    shutil.copytree(proof_path(root, proofs[0]['proof_dir']) / 'module', out / 'module', dirs_exist_ok=True)
    r = json.loads((out / 'module/receipt.json').read_text())
    cert = dict(schema=SHARD_SCHEMA, kind='overlay_module_link_placement_scratch' if scratch else 'overlay_module_link_placement',
                module=m['key'], placement=key, image=p['image'], members=p['members'], reviewer=p['review']['reviewer'],
                fingerprint=before, artifact_sha256=r['artifact_sha256'], receipt_sha256=G.sha(out / 'module/receipt.json'),
                proof_dir=str((out / 'module').relative_to(root)), windows=proofs)
    reason = certificate_reason(p, cert, root, scratch=scratch)
    if reason:
        raise ValueError(reason)
    target = Path(output) if output is not None else root / 'ledger/modules' / ('placement_' + key + '.json')
    target.parent.mkdir(parents=True, exist_ok=True); tmp = target.with_suffix('.tmp')
    tmp.write_text(json.dumps(cert, indent=2) + '\n'); tmp.replace(target)
    return cert, target
