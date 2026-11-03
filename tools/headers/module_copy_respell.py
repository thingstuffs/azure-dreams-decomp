#!/usr/bin/env python3
"""Review module copy calls, preserving import addresses and recertifying whole modules.

Input is address_names.py's copy_holds.tsv. Only module_caller pairs qualify.
The same-image copy rule must hold in every caller image. Existing bindings of
the canonical home symbol, prototype floors and ambiguous families are held.
The source edit uses address_names.py's declaration and compiler screen rules.
An applied module must pass its normal retail and genuine-assembler gates.
Run module_member_rekey.py on the application before the full image proof: ordinary
placements of individual members retain their own reviewed import bindings.
"""
from __future__ import annotations

import argparse
import collections
import copy
import csv
import json
from pathlib import Path
import re
import sqlite3
import subprocess
import sys


def revised_imports(module, pairs, undefined):
    """Change only reviewed X -> H symbols; preserve all imported addresses."""
    original = {entry['symbol']: entry for entry in module['imports']}
    additions = {}
    old_symbols = set()
    for pair in pairs:
        home, target = pair['link'].split('>')
        old = original.get(target)
        if old is None or old['kind'] != 'function' or old['vma'] != int(target[-8:], 16):
            raise ValueError('old import is not a function at the reviewed address')
        if any(member['function'] == home for member in module['members']):
            raise ValueError('home symbol is defined in the module')
        previous = original.get(home) or additions.get(home)
        if previous and (previous['kind'] != 'function' or previous['vma'] != old['vma']):
            raise ValueError('home symbol is already bound elsewhere')
        if home not in undefined:
            raise ValueError('respelled home symbol is not imported')
        entry = dict(old, symbol=home)
        entry['basis'] = ('same-image copy of %s: home %s, original import %s at 0x%08X; '
                          'whole-module recertification preserves this address' %
                          (pair['new'], home, target, old['vma']))
        additions[home] = entry
        old_symbols.add(target)
    allowed = set(original) | set(additions)
    if undefined - allowed or set(original) - undefined - old_symbols:
        raise ValueError('unexpected import inventory change')
    result = []
    added = set()
    for entry in module['imports']:
        symbol = entry['symbol']
        if symbol in undefined:
            result.append(copy.deepcopy(entry))
            added.add(symbol)
        if symbol in old_symbols:
            for home, replacement in additions.items():
                if replacement['vma'] == entry['vma'] and home not in added:
                    result.append(replacement)
                    added.add(home)
    if {entry['symbol'] for entry in result} != undefined:
        raise ValueError('incomplete reviewed inventory')
    before = {entry['vma'] for entry in module['imports'] if entry['kind'] == 'function'}
    after = {entry['vma'] for entry in result if entry['kind'] == 'function'}
    if before != after:
        raise ValueError('function import address set changed')
    return result


def local_prototype(text, name):
    """A call statement is not a file-scope declaration that can be renamed."""
    import foreign_imports
    found, _scan = foreign_imports.local_sites(text, {name})
    return bool(found.get(name))


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--root', type=Path, default=Path(__file__).resolve().parents[2])
    parser.add_argument('--pairs', type=Path, required=True)
    parser.add_argument('--out', type=Path, required=True)
    parser.add_argument('--workers', type=int, default=4)
    parser.add_argument('--apply', action='store_true')
    args = parser.parse_args()
    root = args.root.resolve()
    out = args.out.resolve()
    out.mkdir(parents=True, exist_ok=True)
    sys.path[:0] = [str(root/'tools/headers'), str(root/'tools/gate')]
    import address_names as names
    import linklist
    import overlay_module_gate as gate
    tables = linklist.load(str(root))
    canonical = names.names_table(root)
    db = sqlite3.connect('file:'+str(root/'build/codemap.db')+'?mode=ro', uri=True)
    manifest_path = root/'config/overlays/modules.json'
    manifest_text = manifest_path.read_text()
    modules = {module['key']: module for module in gate.load_modules(root)}
    placement_path = root/'config/overlays/module_placements.json'
    placed_modules = {item['module'] for item in json.loads(placement_path.read_text())['placements']} if placement_path.exists() else set()
    floors = set()
    for line in (root/'ledger/prototype_floors.jsonl').read_text().splitlines():
        record = json.loads(line)
        floors.update((block['path'], record['name']) for block in record.get('blocking', []))
    reviews, candidates = [], []
    for pair in csv.DictReader(args.pairs.open(), delimiter='\t'):
        pair = dict(pair)
        why = None
        if pair.get('evidence') != 'module_caller':
            why = 'not_module_caller'
        home, target = pair['link'].split('>')
        if canonical.get(pair['old'], pair['old']) != target or canonical.get(pair['new'], pair['new']) != home:
            why = 'name_mapping_changed'
        owners = [module for module in modules.values() if pair['file'] in
                  {module['source'], *(member['source'] for member in module['members'])}]
        if len(owners) != 1:
            why = 'module_owner_not_unique'
        elif owners[0]['key'] in placed_modules:
            why = 'module_placement_inventory_requires_review'
        if (pair['file'], pair['old']) in floors or (pair['file'], pair['new']) in floors:
            why = 'prototype_floor'
        if why is None:
            module = owners[0]
            pair['module'] = module['key']
            try:
                revised_imports(module, [pair], {entry['symbol'] for entry in module['imports']} | {home})
                recipes = [r for r, in db.execute('select id from recipe where source=?', (pair['file'],))]
                images = {image for recipe in recipes for image, in
                          db.execute('select image from image_unit where recipe=?', (recipe,))}
                if not images:
                    raise ValueError('no production images')
                pair['images_reviewed'] = sorted(images)
                for image in images:
                    if linklist.copy_link_target(tables, image, int(home[-8:], 16)) != int(target[-8:], 16):
                        raise ValueError('copy is elsewhere in a caller image')
            except ValueError as error:
                why = str(error)
        if why is None:
            text = (root/pair['file']).read_text()
            visible = names.visible_declares(root, pair['file'], pair['new'], text)
            local = local_prototype(text, pair['old'])
            if not visible and not local:
                why = 'no_visible_prototype'
        pair['status'] = why or 'candidate'
        reviews.append(pair)
        if why is None:
            candidates.append(pair)
    (out/'review.json').write_text(json.dumps(reviews, indent=1)+'\n')
    print('review:', dict(collections.Counter(pair['status'] for pair in reviews)), flush=True)
    if not args.apply or not candidates:
        return
    fields = list(candidates[0])
    with (out/'plan.tsv').open('w') as file:
        writer = csv.DictWriter(file, fields, delimiter='\t', extrasaction='ignore')
        writer.writeheader()
        writer.writerows(candidates)
    names.screen(root, root/'build/codemap.db', out/'plan.tsv', out/'screen', min(4, args.workers))
    passed = {(row['file'], row['old']) for row in csv.DictReader((out/'screen/screen.tsv').open(), delimiter='\t')
              if row['verdict'] == 'pass'}
    groups = collections.defaultdict(list)
    for pair in candidates:
        if (pair['file'], pair['old']) in passed:
            groups[pair['module']].append(pair)
    results = []
    for key, pairs in sorted(groups.items()):
        module = modules[key]
        before = {pair['file']: (root/pair['file']).read_text() for pair in pairs}
        previous_manifest = manifest_path.read_text()
        module_out = out/'modules'/key
        try:
            by_file = collections.defaultdict(list)
            for pair in pairs:
                by_file[pair['file']].append((pair['old'], pair['new'], pair['new_header']))
            for file, edits in by_file.items():
                log = []
                if not names.apply_one(root, file, edits, log):
                    raise ValueError('source edit was empty')
                if any(row[-1].startswith('hold:') for row in log):
                    raise ValueError('source editor held a screened pair')
            try:
                gate.build(module, module_out/'inventory', root)
            except ValueError as error:
                if not (str(error).startswith('import inventory differs:') or
                        str(error) == 'exact import inventory differs'):
                    raise
            else:
                raise ValueError('module inventory did not change')
            symbols = subprocess.check_output(['mipsel-linux-gnu-nm', str(module_out/'inventory/module.o')], text=True)
            undefined = {columns[1] for line in symbols.splitlines() if len(columns := line.split()) == 2 and columns[0] == 'U'}
            new_module = copy.deepcopy(module)
            new_module['imports'] = revised_imports(module, pairs, undefined)
            current = json.loads(previous_manifest)
            index = next(i for i, item in enumerate(current['modules']) if item['key'] == key)
            current['modules'][index]['imports'] = new_module['imports']
            indent = next((n for n in (1, 2, 4) if json.dumps(json.loads(previous_manifest), indent=n)+'\n' == previous_manifest), 2)
            manifest_path.write_text(json.dumps(current, indent=indent)+'\n')
            receipt, binary = gate.build(new_module, module_out/'certified', root)
            if receipt['gate']['result'] != 'MATCH' or receipt['genuine']['result'] != 'MATCH':
                raise ValueError('module recertification did not match')
            result = dict(module=key, status='applied', pairs=len(pairs), gate=receipt['gate'], genuine=receipt['genuine'])
        except Exception as error:
            for file, text in before.items():
                (root/file).write_text(text)
            manifest_path.write_text(previous_manifest)
            result = dict(module=key, status='held', pairs=len(pairs), reason=str(error))
        results.append(result)
        (out/'results.json').write_text(json.dumps(results, indent=1)+'\n')
        print(key, result['status'], result.get('reason', ''), flush=True)


if __name__ == '__main__':
    main()
