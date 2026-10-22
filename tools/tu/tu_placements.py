#!/usr/bin/env python3
"""Module placements for merged files whose members are linked into other images (tu7).

A home module made by tools/tu/tu_merge.py install is ONE object.  Every other image that
links that object places ALL its members, contiguous, in order, at one displacement (link
lists, docs/LINK_LISTS.md).  This tool writes the LL5 placement descriptors for those images
(config/overlays/module_placements.json, docs/LL5_MODULE_PLACEMENTS.md) with:

  * members  [{home, row}] from the link-list entries (registry source_row == home);
  * imports  the home inventory with destination values by the link-list binding rules
             (linklist._binding); a data view of the home image's own region becomes a
             `link_image` view of the destination image (same view_bytes);
  * review   pending (computational rehearsal only; production issuance needs the
             explicit v2 destination review record, which this tool writes as a pending
             evidence file the reviewer completes).

It then runs the placement validator (overlay_module_placements.load) and reports per
placement OK or the validator's reason.  An image that places only part of the module, or
out of order, is reported as cross_image_partial and gets no descriptor.

usage: tu_placements.py --module KEY --base DIR [--root ROOT] [--dry-run]
"""
from __future__ import annotations

import argparse
import json
import re
import sys
from pathlib import Path

HERE = Path(__file__).resolve().parent
sys.path.insert(0, str(HERE))
import tu_merge as M  # noqa: E402


def unindexed_home_image(module, images, rows):
    """A census code range may omit home entries; never hide registered copies."""
    members = module.get('data_members', []) + module['members']
    homes = {a['id'] for a in members}
    copies = [r['id'] for r in rows.values() if r.get('source_row') in homes]
    if copies:
        raise ValueError('unindexed home has registered foreign copies: %s' % ', '.join(sorted(copies)))
    candidates = [key for key, image in images.items()
                  if key.split('/', 1)[0] == module['container'] and image.get('vma') is not None and all(
                      image['foff'] <= a['foff'] and a['foff'] + a['size'] <= image['foff'] + image['size']
                      and image['vma'] - image['foff'] == a['vma'] - a['foff'] for a in members)]
    if not candidates:
        raise ValueError('unindexed home has no catalogue image matching its verified geometry')
    return min(candidates, key=lambda key: (images[key]['size'], '/image_' not in key, key))


def plan(root, key):
    sys.path[:0] = [str(root / 'tools'), str(root / 'tools/gate')]
    import linklist
    mods = {m['key']: m for m in json.loads((root / 'config/overlays/modules.json').read_text())['modules']}
    m = mods[key]
    images, _, by_row, local = tables = linklist.load(root)
    rows = {r['id']: r for r in M.jl(root / 'ledger/rows.jsonl')}
    homes = [a['id'] for a in m.get('data_members', []) + m['members']]
    if any(h not in by_row for h in homes):
        if any(e['home'] in homes and rid not in homes for rid, e in by_row.items()):
            raise ValueError('unindexed home still has indexed foreign placements')
        home_image = unindexed_home_image(m, images, rows)
        return m, home_image, images, tables, [], []
    home_image = by_row[homes[0]]['image']
    # every placement row of each home, by image
    per_image, duplicates = {}, {}
    for rid, e in by_row.items():
        if e['home'] in homes and rid not in homes:
            if e['home'] in per_image.get(e['image'], {}):
                duplicates.setdefault(e['image'], []).append(e['home'])
            per_image.setdefault(e['image'], {})[e['home']] = e
    out, partial = [], []
    for img, hits in sorted(per_image.items()):
        if img in duplicates:
            partial.append(dict(image=img, reason='multiple placements of the same home need explicit cohorts: ' +
                                ', '.join(sorted(set(duplicates[img])))))
            continue
        es = [hits.get(h) for h in homes]
        if None in es:
            partial.append(dict(image=img, reason='places %d of %d members' % (len(hits), len(homes))))
            continue
        disp = {(e['foff'] - by_row[h]['foff'], e['vma'] - by_row[h]['vma']) for e, h in zip(es, homes)}
        if len(disp) != 1:
            partial.append(dict(image=img, reason='members not at one displacement (reordered/non-contiguous)'))
            continue
        if any(rows[e['row']].get('source_row') != h for e, h in zip(es, homes)):
            partial.append(dict(image=img, reason='registry source_row differs'))
            continue
        dimg = images[img]
        need = [(e['foff'], e['foff'] + e['size']) for e in es]
        if not covered(root, m['container'], need, dimg['vma'] - dimg['foff']):
            partial.append(dict(image=img, reason='destination rowbase incomplete (no proven load map at delta '
                                                  '0x%X over the members)' % (dimg['vma'] - dimg['foff'])))
            continue
        out.append((img, es))
    return m, home_image, images, tables, out, partial


def covered(root, container, extents, delta):
    """The validator's rule: every member byte lies in proven rowbase regions at the image delta."""
    regs = sorted((int(r['foff_start'], 0), int(r['foff_end'], 0), int(r['delta'], 0), r['base_confidence'])
                  for r in M.jl(root / ('config/overlays/%s.rowbase.jsonl' % container)))
    for start, stop in extents:
        cursor = start
        for lo, hi, d, conf in regs:
            if hi <= cursor or lo >= stop:
                continue
            if lo > cursor or conf != 'proven' or d != delta:
                return False
            cursor = min(hi, stop)
        if cursor != stop:
            return False
    return True


def unify_bindings(root, fr, m, home_image, tables, img, es):
    """One object, one symbol table: a merged module's members must bind each import alike in a
    destination image.  Member entries carried their own per-TU `bindings`; the union of the
    explicit ones (when they agree) is written to every member entry of this image's link list."""
    import linklist
    changes = {}
    for d in m['imports']:
        a = d['vma']
        targets = {linklist._binding(tables, e, a, home_image) for e in es}
        if len(targets) <= 1:
            continue
        explicit = {e['bindings'][a] for e in es if a in e['bindings']}
        if len(explicit) != 1:
            raise ValueError('members bind %s differently in %s: %s' % (d['symbol'], img, sorted(map(hex, targets))))
        changes[a] = explicit.pop()
    if not changes:
        return {}
    rel = 'config/link/%s.json' % img
    doc = json.loads((root / rel).read_text())
    rows = {e['row'] for e in es}
    for e in doc['entries']:
        if e.get('row') in rows:
            b = e.setdefault('bindings', {})
            for a, v in changes.items():
                b['0x%08X' % a] = '0x%08X' % v
            e.setdefault('evidence', 'tu7: bindings unified for merged module %s' % m['key'])
    fr.write(rel, json.dumps(doc, indent=2) + '\n')
    return {hex(a): hex(v) for a, v in changes.items()}


def storage_image(images, code, foff, size):
    """The destination image if it holds the view, else the smallest link image of the same
    container and load delta holding both the whole code image and the view (a tiny code-only
    image does not establish a surrounding storage map)."""
    def holds(i, lo, hi):
        return i['foff'] <= lo and hi <= i['foff'] + i['size']
    if holds(code, foff, foff + size):
        return code
    delta = code['vma'] - code['foff']
    cands = [i for i in images.values() if i['container'] == code['container'] and i['vma'] - i['foff'] == delta
             and holds(i, code['foff'], code['foff'] + code['size']) and holds(i, foff, foff + size)]
    if not cands:
        raise ValueError('no link image of %s holds the view at 0x%X' % (code['image'], foff))
    return min(cands, key=lambda i: i['size'])


def descriptor(root, m, home_image, images, tables, img, es):
    import linklist
    tail = re.sub(r'[^a-z0-9_]', '_', img.split('/', 1)[1].lower())
    pkey = '%s_%s' % (m['key'], tail)
    ev = 'docs/evidence/%s.placement.json' % pkey
    dimg = images[img]
    delta = dimg['vma'] - dimg['foff']
    asset = 'work/disc/containers/' + {'town': 'TOWN_TOWN.BIN', 'dungeon': 'DUNGEON_DUNGEON.BIN',
                                       'main': 'MAIN_MAIN.BIN', 'ovmovie': 'OVMOVIE.BIN'}[m['container']]
    imports, views, maps = [], {}, {}
    for d in m['imports']:
        targets = {linklist._binding(tables, e, d['vma'], home_image) for e in es}
        if len(targets) != 1:
            raise ValueError('ambiguous binding for %s in %s' % (d['symbol'], img))
        v = targets.pop()
        if d['kind'] == 'function':
            imports.append(dict(symbol=d['symbol'], kind='function', vma=v))
        elif d['kind'] == 'runtime_data':
            imports.append(dict(d))
        elif 'asset' in d:
            # A resident engine view is not storage of the destination bank.
            # Preserve its existing, validated map; a moved external view needs
            # a separate destination proof rather than a guessed bank offset.
            if v != d['vma']:
                raise ValueError('resident asset view moves without a destination proof: ' + d['symbol'])
            proof = json.loads((root / d['evidence']).read_text())
            mname = d['map']
            mp = proof['maps'][mname]
            if mname in maps and maps[mname] != mp:
                raise ValueError('resident asset map name collision: ' + mname)
            maps[mname] = dict(mp)
            nd = dict(d, evidence=ev)
            imports.append(nd)
            views[d['symbol']] = nd
        else:
            mimg = storage_image(images, dimg, v - delta, d['view_bytes'])
            mname = 'destination_image' if mimg is dimg else 'image_' + re.sub(r'[^a-z0-9_]', '_', mimg['image'].split('/', 1)[1].lower())
            maps[mname] = dict(kind='link_image', image=mimg['image'], link_list='config/link/%s.json' % mimg['image'],
                               asset=asset, file_start=mimg['foff'], file_end=mimg['foff'] + mimg['size'], delta=delta,
                               basis=mimg.get('evidence') or 'link list load image')
            nd = dict(symbol=d['symbol'], kind='data', vma=v, foff=v - delta, view_bytes=d['view_bytes'],
                      owner='retail_asset:' + asset, asset=asset, map=mname, evidence=ev)
            imports.append(nd)
            views[d['symbol']] = nd
    desc = dict(key=pkey, module=m['key'], image=img, home_image=home_image, recipe=m['recipe'],
                members=[dict(home=e['home'], row=e['row']) for e in es], imports=imports,
                review=dict(membership='pending', types='pending', ownership='pending', reviewer='pending'),
                review_inputs=[ev])
    evidence = dict(
        schema='azure-clean.module-placement-review.v2', module=m['key'], placement=pkey, review=desc['review'],
        basis='tu7 computational candidate: the merged home object %s is linked whole into %s (all %d members, '
              'contiguous, one displacement; link lists). Destination types/storage/ownership review pending.'
              % (m['key'], img, len(es)),
        views=views,
        maps=maps,
        placement_descriptor={k: v for k, v in desc.items()})
    return desc, ev, evidence


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument('--root', type=Path, default=HERE.parents[1])
    ap.add_argument('--module', required=True)
    ap.add_argument('--base', type=Path, required=True)
    ap.add_argument('--dry-run', action='store_true')
    args = ap.parse_args(argv)
    root = args.root.resolve()
    m, home_image, images, tables, ok, partial = plan(root, args.module)
    fr = M.Freezer(root, args.base.resolve())
    manifest_rel = 'config/overlays/module_placements.json'
    doc = json.loads((root / manifest_rel).read_text())
    made = []
    unified = {}
    for img, es in ok:
        u = unify_bindings(root, fr, m, home_image, tables, img, es) if not args.dry_run else {}
        if u:
            unified[img] = u
    if unified:
        m, home_image, images, tables, ok, partial = plan(root, args.module)   # reload the link lists
    for img, es in ok:
        try:
            desc, ev, evidence = descriptor(root, m, home_image, images, tables, img, es)
        except ValueError as exc:
            partial.append(dict(image=img, reason='destination import view unavailable: %s' % exc))
            continue
        if any(p['key'] == desc['key'] for p in doc['placements']):
            continue
        doc['placements'].append(desc)
        made.append(desc['key'])
        if not args.dry_run:
            fr.write(ev, json.dumps(evidence, indent=2) + '\n')
    if not args.dry_run and made:
        fr.write(manifest_rel, json.dumps(doc, indent=1) + '\n')
    report = dict(module=args.module, home_image=home_image, placements=made, partial=partial,
                  unified_bindings=unified)
    if not args.dry_run:
        sys.path[:0] = [str(root / 'tools/gate')]
        import overlay_module_placements as P
        try:
            loaded = P._load(root)
            report['validator'] = 'OK: %d placements load (%d for this module)' % (
                len(loaded), sum(1 for p in loaded if p['module'] == args.module))
        except Exception as e:  # the validator's reason is the result
            report['validator'] = 'REFUSED: %s' % e
        if made or unified:
            M.refresh_link_graph(root, args.base.resolve(), fr)
    print(json.dumps(report, indent=1))
    return 0


if __name__ == '__main__':
    sys.exit(main())
