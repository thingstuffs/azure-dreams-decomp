#!/usr/bin/env python3
"""Recover real C prototypes without guessing overlay address ownership.

Run from a provisioned source checkout (Python standard library only):
  python3 tools/proto/prototypes.py --check
  python3 tools/proto/prototypes.py --scope src/frontend --out work/prototypes
  python3 tools/proto/prototypes.py --scope src/frontend --apply --out work/prototypes

The default is a dry run. Every apply writes a symbol/anchor replay map. It is
NOT a proof: compile diagnostics and complete-TU / scoped retail identity must
be reviewed before accepting edits. Conflicting placements are holds, never
resolved by picking the first function at a coincident address in another bank.
"""
from __future__ import annotations

import argparse
from bisect import bisect_right
from collections import Counter, defaultdict
from dataclasses import asdict, dataclass, replace
import csv
import hashlib
import json
from pathlib import Path
import re
import sys

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT))
sys.path.insert(0, str(ROOT / 'tools'))
from tools.headers import cscan, model as M, plan as P


def compact(text):
    return ' '.join(text.split())


def balanced(text, start):
    depth = 0
    for pos in range(start, len(text)):
        if text[pos] == '(':
            depth += 1
        elif text[pos] == ')':
            depth -= 1
            if not depth:
                return pos
    raise ValueError('unbalanced parameter list')


def identifier_list(params, types):
    return bool(params) and all(len(p) == 1 and cscan.IDENT.fullmatch(p[0])
                                and p[0] not in cscan.BASE_TYPES
                                and p[0] not in types for p in params)


def unprototyped(site, types):
    return site.params is None or identifier_list(site.params, types.visible(site.path))


def params_text(definition):
    match = re.search(r'\b' + re.escape(definition.name) + r'\s*\(', definition.proto)
    if not match:
        raise ValueError('definition has no simple parameter list')
    start = match.end() - 1
    return definition.proto[start + 1:balanced(definition.proto, start)].strip() or 'void'


def prototype_key(site, types):
    vis = types.visible(site.path)
    return (M.canon(site.ret_spec, site.ret_ptr, vis),
            tuple(M.canon(*M.param_parts(p)[:2], vis) for p in site.params or []),
            any(p == ['...'] for p in site.params or []))


def number(value):
    return value if isinstance(value, int) else int(value, 0)


def table(path):
    if not path.exists():
        return []
    with path.open(newline='') as handle:
        return list(csv.DictReader(handle, delimiter='\t'))


def write_table(path, records, fields):
    path.parent.mkdir(parents=True, exist_ok=True)
    with path.open('w', newline='') as handle:
        writer = csv.DictWriter(handle, fields, delimiter='\t', lineterminator='\n',
                                extrasaction='ignore')
        writer.writeheader()
        writer.writerows(records)


class Resolver:
    """Resolve names in source and numeric symbols in EVERY loading image.

    config/link is the lossless public projection of config/link_graph. Like
    bank_arity_census, use a caller's bindings and its own image's entry VMA.
    Unlike the original census, there is no global by-VMA fallback, and all
    placements must resolve and agree. Resident addresses use the pinned SLUS
    symbol map; names.tsv alone cannot select an overlay's owner.
    """
    def __init__(self, root, corpus, types, definitions):
        self.root, self.corpus, self.types, self.defs = root, corpus, types, definitions
        self.definition_keys, self.numeric_cache, self.site_address_cache = {}, {}, {}
        self.signature_cache = {}
        self.member_import_cache = {}
        self.by_path = defaultdict(list)
        for ds in definitions.values():
            for d in ds:
                self.by_path[d.path].append(d)
        self.aliases = defaultdict(set)
        self.named_addresses = defaultdict(set)
        aliases = root / 'config/names.tsv'
        if aliases.exists():
            for line in aliases.read_text().splitlines():
                cols = line.split('\t')
                if len(cols) >= 3 and not line.startswith('#'):
                    self.aliases[cols[1]].add(cols[2])
                    numeric = re.fullmatch(r'func_([\da-fA-F]{8})', cols[1])
                    if numeric:
                        self.named_addresses[cols[2]].add(int(numeric[1], 16))
        self.resident_addresses = defaultdict(list)
        symbols = root / 'config/slus_006.14.symbols.txt'
        if symbols.exists():
            for match in re.finditer(r'(?m)^\s*(\w+)\s*=\s*(0x[\da-fA-F]+)\s*;', symbols.read_text()):
                names = {match[1]} | self.aliases[match[1]]
                for name in names:
                    for d in definitions.get(name, []):
                        if d.container == 'slus' and not d.static:
                            self.resident_addresses[number(match[2])].append(d)
        self.images, self.callers = {}, defaultdict(list)
        for path in sorted((root / 'config/link').glob('*/*.json')):
            doc = json.loads(path.read_text())
            name = doc['image']
            entries = defaultdict(list)
            for entry in doc.get('entries', []):
                if entry.get('row') and 'vma' in entry and entry['vma'] is not None:
                    entries[number(entry['vma'])].append(entry)
                if entry.get('tu'):
                    self.callers[entry['tu']].append((name, entry))
            self.images[name] = (doc, entries)
        # Production lists carry schemas and can use the linker's complete
        # rebinding implementation (self entry, explicit bindings, same-image
        # homes, layout displacement, image symbols, resident fallback).
        # The schema-free branch permits small isolated resolver fixtures.
        self.binding_tables = None
        if self.images and all(doc.get('schema') for doc, _ in self.images.values()):
            from tools.gate import linklist
            self.binding_tables = linklist.load(root)
        self.load_regions = {}
        grouped = defaultdict(list)
        for image, (doc, entries) in self.images.items():
            if all(doc.get(k) is not None for k in ('container', 'foff', 'size', 'vma')):
                begin = number(doc['foff'])
                grouped[doc['container']].append((begin, begin + number(doc['size']),
                                                  number(doc['vma']), image, entries))
        for container, regions in grouped.items():
            regions.sort(key=lambda item: (item[0], item[1], item[3]))
            maximum, ends = 0, []
            for region in regions:
                maximum = max(maximum, region[1])
                ends.append(maximum)
            self.load_regions[container] = ([item[0] for item in regions], ends, regions)
        self.rows = {}
        ledger = root / 'ledger/rows.jsonl'
        if ledger.exists():
            self.rows = {r['id']: r for r in map(json.loads, ledger.read_text().splitlines()) if r}
        # Resident C entry points are also registered directly, including
        # aliases absent from the public SLUS export-symbol file. Require a
        # resident ROW and its actual source home; a names.tsv address alone
        # cannot turn an overlay function into a resident import.
        layout = root / 'ledger/layout.jsonl'
        homes = {r['id']: r.get('path') for r in map(json.loads, layout.read_text().splitlines())
                 if r.get('path')} if layout.exists() else {}
        inline = root / 'ledger/layout_inline.jsonl'
        if inline.exists():
            homes.update({r['member_id']: r['tu_new'] for r in
                          map(json.loads, inline.read_text().splitlines())})
        # Link lists explicitly enumerate shared placements. Native own-file
        # rows may be omitted even inside those same proven load regions. They
        # link without rebinding: locate them by their physical interval and
        # the region's load base, never by an address in an unrelated bank.
        placed = {entry['row'] for _, entries in self.images.values()
                  for group in entries.values() for entry in group if entry.get('row')}
        for rid, row in self.rows.items():
            if row.get('source_row') or row.get('foff') is None:
                continue
            source = homes.get(rid)
            if not source:
                continue
            offset, size = number(row['foff']), number(row.get('size') or 0)
            if size <= 0:
                continue
            for begin, end, vma, image, entries in self.regions_containing(
                    row.get('container'), offset, offset + size):
                address = vma + offset - begin
                if any(entry.get('row') == rid for entry in entries.get(address, ())):
                    continue
                entry = dict(row=rid, home=rid, tu=source, vma=address,
                             foff=offset, size=size, _unrebound=True)
                entries[address].append(entry)
                # A row registered in a sibling window is still a physical
                # target in every containing region. Its explicit caller
                # placements remain authoritative: do not add an unrebound
                # caller that would bypass their import rules.
                if rid not in placed:
                    self.callers[source].append((image, entry))
        for rid, row in self.rows.items():
            if row.get('container') != 'slus':
                continue
            source = homes.get(rid) or row.get('c_path', '')
            # Native resident rows have func=null and enumerate their entry
            # points in defs. Each enumerated address must match its own
            # definition in the registered home; a multi-function TU's first
            # definition is not the owner of every address in that TU.
            entries = set(row.get('defs') or ())
            entries.update(filter(None, (row.get('func'), row.get('true_name'))))
            for symbol in entries:
                match = re.fullmatch(r'func_([\da-fA-F]{8})', symbol)
                if not match:
                    continue
                names = {symbol} | self.aliases.get(symbol, set())
                ds = [d for name in names for d in definitions.get(name, ())
                      if not d.static and d.container == 'slus' and d.path == source]
                if not ds and row.get('func') == symbol:
                    owned = [d for d in self.by_path.get(source, ())
                             if not d.static and d.container == 'slus']
                    if len(owned) == 1:
                        ds = owned
                self.resident_addresses[int(match[1], 16)].extend(ds)
        self.row_cache, self.consumer_cache = {}, {}
        self.identities = defaultdict(list)
        identity_path = root / 'ledger/prototype_identities.jsonl'
        if identity_path.exists():
            for line in identity_path.read_text().splitlines():
                record = json.loads(line)
                self.identities[record['file'], record['symbol']].append(record)
        self.identity_contracts = None
        self.address_witnesses = defaultdict(list)
        for image, (doc, entries) in self.images.items():
            for address, group in entries.items():
                self.address_witnesses[doc.get('container'), address].extend(
                    (image, entry) for entry in group)

    def regions_containing(self, container, begin, end):
        """Find physical containment without scanning every unrelated bank."""
        starts, ends, regions = self.load_regions.get(container, ([], [], []))
        index = bisect_right(starts, begin) - 1
        while index >= 0 and ends[index] >= end:
            if regions[index][1] >= end:
                yield regions[index]
            index -= 1

    def choose(self, candidates):
        unique = {(d.path, d.name): d for d in candidates}
        if not unique:
            return None, 'no_definition'
        ds = list(unique.values())
        for d in ds:
            if id(d) not in self.definition_keys:
                self.definition_keys[id(d)] = M.def_key(d, self.types)
        if len({self.definition_keys[id(d)] for d in ds}) != 1:
            return None, 'conflicting_definitions'
        return sorted(ds, key=lambda d: (d.path, d.name))[0], ''

    def qualifier_key(self, definition):
        """Retain pointee qualifiers and pointer levels through typedefs."""
        visible = self.types.visible(definition.path)
        parts = [list(definition.ret_spec) + ['*'] * definition.ret_ptr]
        for param in definition.params:
            name = M.param_parts(param)[2]
            tokens = list(param)
            if name:
                tokens.pop(max(i for i, token in enumerate(tokens) if token == name))
            parts.append(tokens)
        result = []
        for tokens in parts:
            for _ in range(12):
                expanded = []
                for index, token in enumerate(tokens):
                    # Tags occupy a separate C namespace. In particular,
                    # typedef struct Record Record must stop at the tag.
                    tag = index > 0 and tokens[index - 1] in ('struct', 'union', 'enum')
                    typedef = None if tag else visible.get(token)
                    if typedef is None:
                        expanded.append(token)
                    else:
                        spec = list(typedef.spec)
                        # A tag body is not part of this declarator's qualifiers.
                        if '{' in spec:
                            spec = spec[:spec.index('{')]
                        expanded.extend(spec + ['*'] * typedef.ptr)
                if expanded == tokens:
                    break
                tokens = expanded
            else:
                return None
            level, qualifiers = 0, []
            for token in tokens:
                if token == '*':
                    level += 1
                if token in cscan.QUALIFIERS:
                    qualifiers.append((level, token))
            result.append(tuple(qualifiers))
        return tuple(result)

    def common_contract(self, candidates):
        """Compare contracts without asserting that one body owns every call.

        Equal private tag spellings in different files do not establish C type
        identity. Require shared type ownership for a multi-body consensus.
        """
        ds = list({(d.path, d.name): d for d in candidates}.values())
        d, why = self.choose(ds)
        if not d or len(ds) == 1:
            return d, why
        owners, qualifications = [], []
        for item in ds:
            headers, tags, _, problem = P.type_needs(item, self.types)
            if problem:
                return None, 'signature_type_ownership_unproved'
            key = M.def_key(item, self.types)
            if (item.knr or item.complex
                    or any(M.param_parts(p)[3] for p in item.params)
                    or any(part[0] == 'fnptr' or part[2] == 'unknown'
                           for part in (key[0], *key[1]))):
                return None, 'signature_type_ownership_unproved'
            qualification = self.qualifier_key(item)
            if qualification is None:
                return None, 'signature_type_ownership_unproved'
            qualifications.append(qualification)
            records = [part[0] for part in (key[0], *key[1])
                       if part[0].startswith(('struct ', 'union '))]
            provenance = []
            for tag in records:
                shared = sorted(h for h in self.types.tag_defs.get(tag, ())
                                if h in self.corpus.closure(item.path))
                if len(shared) != 1:
                    return None, 'signature_type_ownership_unproved'
                provenance.append((tag, shared[0]))
            owners.append(tuple(provenance))
        if len(set(owners)) != 1 or len(set(qualifications)) != 1:
            return None, 'signature_type_ownership_unproved'
        return d, ''

    def signature_only(self, path, name, address):
        """Recover a named contract, never an owner, outside a sparse image.

        Consider EVERY registered candidate at the resulting address in this
        container and resident SLUS. At least one must bear the called name or
        its explicit alias: a coincident address alone is not a name binding.
        Different signatures or private record identities remain holds.
        """
        key = path, name, address
        if key not in self.signature_cache:
            ds = [d for _, entry in self.address_witnesses.get(
                (M.container_of(path), address), ()) for d in self.row_definitions(entry)]
            ds.extend(self.resident_addresses.get(address, ()))
            names = {name} | self.aliases.get(name, set())
            named = any(d.name in names for d in ds)
            d, why = self.common_contract(ds) if named else (None, 'unbound_name')
            evidence = 'signature_consensus[' + ','.join(sorted(
                {item.path + ':' + item.name for item in ds})) + ']'
            self.signature_cache[key] = (d, why, evidence)
        return self.signature_cache[key]

    def row_definitions(self, entry):
        rid = entry.get('row', '')
        key = (rid, entry.get('home', ''), entry.get('tu', ''))
        if key in self.row_cache:
            return self.row_cache[key]
        row = self.rows.get(rid) or self.rows.get(entry.get('home', ''), {})
        names = {row.get('func'), row.get('true_name'), rid.split('/')[-1]}
        for name in list(names):
            names.update(self.aliases.get(name, ()))
        source = entry.get('tu')
        ds = [d for name in names for d in self.defs.get(name, ())
              if not d.static and (not source or d.path == source)]
        # A placement may name its home, whose entry-point has a different ID.
        if not ds and entry.get('home') in self.rows:
            home = self.rows[entry['home']]
            names = {home.get('func'), home.get('true_name')}
            for name in list(names):
                names.update(self.aliases.get(name, ()))
            ds = [d for name in names for d in self.defs.get(name, ())
                  if not d.static and (not source or d.path == source)]
        if not ds and source:
            owned = [d for d in self.by_path.get(source, ()) if not d.static]
            if len(owned) == 1:
                ds = owned
        self.row_cache[key] = ds
        return ds

    def consumers(self, path):
        if path not in self.consumer_cache:
            self.consumer_cache[path] = [c for c in self.corpus.c_files if path in self.corpus.closure(c)]
        return self.consumer_cache[path]

    def numeric_in_tu(self, path, name, address):
        key = path, name, address
        if key not in self.numeric_cache:
            self.numeric_cache[key] = self._numeric_in_tu(path, name, address)
        return self.numeric_cache[key]

    def _numeric_in_tu(self, path, name, address):
        placements = self.callers.get(path, [])
        users = [caller for caller in placements if self.caller_uses_symbol(path, caller[1], name)]
        if users:
            placements = users
        resolved, evidence = [], []
        for image, caller in placements:
            doc, entries = self.images[image]
            bindings = {number(k): number(v) for k, v in (caller.get('bindings') or {}).items()}
            symbols = doc.get('symbols') or {}
            if caller.get('_unrebound'):
                target = address
            elif self.binding_tables is not None:
                from tools.gate.linklist import _binding
                entry = self.binding_tables[2].get(caller['row'])
                if entry is None:
                    return None, 'caller_absent_from_binding_census:' + image, ''
                try:
                    target = _binding(self.binding_tables, entry, address)
                except ValueError as exc:
                    return None, 'ambiguous_image_binding:' + str(exc), ''
            else:
                target = bindings.get(address, number(symbols[name]) if name in symbols else address)
            targets = entries.get(target, [])
            target_images = []
            # A validated list can describe only a subwindow of a larger
            # load region. Imports outside that window may be supplied by a
            # containing region with the identical file-to-VMA mapping.
            # Requiring containment and equal displacement rules out another
            # bank that merely happens to use the same virtual address.
            if not targets and all(doc.get(k) is not None for k in ('foff', 'size', 'vma')):
                begin, end = number(doc['foff']), number(doc['foff']) + number(doc['size'])
                displacement = number(doc['vma']) - begin
                for outer, _, vma, other_image, other_entries in self.regions_containing(
                        doc.get('container'), begin, end):
                    if (other_image != image and vma - outer == displacement and other_entries.get(target)):
                        targets.extend(other_entries[target])
                        target_images.append(other_image)
            ds = [d for entry in targets for d in self.row_definitions(entry)]
            if not ds and not targets:
                ds = self.resident_addresses.get(target, [])
            d, why = self.common_contract(ds)
            if ds and not d:
                owners = ','.join(sorted({d.path + ':' + d.name for d in ds}))
                return None, 'ambiguous_image_callee:' + image, owners
            consensus = ''
            if not d and not targets:
                d, _, consensus = self.signature_only(path, name, target)
            if not d:
                # Report possible owners outside the proved loading context
                # as evidence only. In particular, an engine entry existing
                # at an unchanged address does not establish that this bank
                # imports that engine in every placement.
                elsewhere = sorted({other + ':' + item.path + ':' + item.name
                                    for other, entry in self.address_witnesses.get(
                                        (doc.get('container'), target), ())
                                    if other != image
                                    for item in self.row_definitions(entry)})
                if elsewhere:
                    return None, 'unresolved_image_binding:' + image + ':owner_outside_loading_image', (
                        f'{image}:{address:08X}->{target:08X}; unproved owners=' + ';'.join(elsewhere[:12])
                        + (f'; {len(elsewhere) - 12} more owners' if len(elsewhere) > 12 else ''))
                return None, 'unresolved_image_binding:' + image + ':' + why, ''
            resolved.append(d)
            mode = ':own_file' if caller.get('_unrebound') else ''
            if target_images:
                mode += ':within=' + ','.join(sorted(target_images))
            if consensus:
                mode += ':' + consensus
            if len({(item.path, item.name) for item in ds}) > 1:
                mode += ':same_image_signature_consensus[' + ','.join(sorted(
                    {item.path + ':' + item.name for item in ds})) + ']'
            evidence.append(f'{image}:{address:08X}->{target:08X}:{d.name}{mode}')
        if not placements:
            d, why = self.common_contract(self.resident_addresses.get(address, []))
            if d:
                return d, '', 'resident_symbol_map'
            d, why, evidence = self.signature_only(path, name, address)
            if d:
                return d, '', 'unplaced_consumer:' + evidence
            return None, 'no_loading_image_or_resident_owner', 'resident_symbol_map'
        d, why = self.common_contract(resolved)
        return d, ('placement_signature_conflict' if why else ''), ';'.join(sorted(set(evidence)))

    def caller_uses_symbol(self, path, entry, name):
        """An inline member's import does not belong to every sibling member.

        Keep unknown/macro and file-scope uses conservative. Only exclude a
        registered, uniquely identified function whose body omits the symbol.
        """
        definitions = self.row_definitions(entry)
        if len(definitions) != 1 or definitions[0].path != path:
            return True
        pattern = r'\b' + re.escape(name) + r'\b'
        key = path, name
        if key not in self.member_import_cache:
            uncertain = False
            for rel in self.corpus.closure(path):
                scan = self.corpus.scan(rel)
                # A header macro, initializer or inline body can hide a use
                # from the physical member body. Unknown includes can too.
                unknown_include = any(d.kind == 'include' and (
                    not d.arg.startswith('"') or
                    not self.corpus.resolve_include(rel, d.arg.split('"')[1]))
                    for d in scan.directives)
                directives = re.sub(r'\\\r?\n', '', self.corpus.text(rel))
                if unknown_include or re.search(r'(?m)^\s*#.*(?:' + pattern + r'|##)', directives):
                    uncertain = True
                    break
                for item in scan.items:
                    initializer = item.kind == 'decl' and '=' in item.text
                    header_body = rel != path and item.kind == 'def'
                    if (initializer or header_body) and re.search(pattern, scan.masked[item.start:item.end]):
                        uncertain = True
                        break
                if uncertain:
                    break
            self.member_import_cache[key] = uncertain
        if self.member_import_cache[key]:
            return True
        scan = self.corpus.scan(path)
        bodies = [item for item in scan.items if item.kind == 'def'
                  and any(d.name == definitions[0].name for d in item.decls)]
        return len(bodies) != 1 or bool(re.search(pattern, scan.masked[bodies[0].body[0]:bodies[0].end]))

    def address_at_site(self, site, address):
        key = site.path, site.in_header, site.name, address
        if key not in self.site_address_cache:
            self.site_address_cache[key] = self._address_at_site(site, address)
        return self.site_address_cache[key]

    def _address_at_site(self, site, address):
        if site.in_header:
            consumers = self.consumers(site.path)
            if not consumers:
                return None, 'header_has_no_consumers', ''
            ds, evidence = [], []
            for path in consumers:
                d, why, ev = self.numeric_in_tu(path, site.name, address)
                if not d:
                    return None, why, ev
                ds.append(d)
                evidence.append(ev)
            d, why = self.common_contract(ds)
            return d, why, ';'.join(sorted(set(evidence)))
        return self.numeric_in_tu(site.path, site.name, address)

    def named_in_tu(self, path, name, candidates):
        """Choose an unmapped spelling from the consumer's own placements."""
        placements = self.callers.get(path, ())
        chosen, evidence = [], []
        for image, _ in placements:
            _, entries = self.images[image]
            available = {(d.path, d.name) for group in entries.values()
                         for entry in group for d in self.row_definitions(entry)}
            local = [d for d in candidates if (d.path, d.name) in available]
            d, why = self.common_contract(local)
            if not d:
                return None, 'unresolved_named_image_binding:' + image, why
            chosen.append(d)
            evidence.append(image + ':' + d.path + ':' + d.name)
        d, why = self.common_contract(chosen)
        return d, why or ('no_loading_image_or_resident_owner' if not d else ''), ';'.join(sorted(set(evidence)))

    def resolve(self, site):
        records = self.identities.get((site.path, site.name), ())
        if records:
            return self.documented_identity(site, records)
        # Static prototypes refer only to their own TU, never another bank.
        local = [d for d in self.defs.get(site.name, ()) if d.path == site.path and d.static]
        if local:
            d, why = self.choose(local)
            return d, why, 'same_tu_static'
        numeric = re.fullmatch(r'func_([\da-fA-F]{8})', site.name)
        if numeric:
            return self.address_at_site(site, int(numeric[1], 16))
        # ccproc restores address-derived names before the linker rebinds the
        # call. A readable alias therefore has the same image-specific owner
        # as its numeric spelling, even when an unrelated bank defines that
        # readable name. Do not fall back to that unrelated definition.
        addresses = self.named_addresses.get(site.name, set())
        if len(addresses) > 1:
            return None, 'ambiguous_named_address', ';'.join(f'{a:08X}' for a in sorted(addresses))
        if addresses:
            return self.address_at_site(site, next(iter(addresses)))
        cands = [d for d in self.defs.get(site.name, ()) if not d.static]
        if not site.in_header:
            own = [d for d in cands if d.container == M.container_of(site.path)]
            resident = [d for d in cands if d.container == 'slus']
            if cands and not own and not resident:
                return None, 'cross_container_binding_unproved', ';'.join(sorted(d.path for d in cands))
            cands = own or resident
        if not cands and self.defs.get(site.name):
            return None, 'static_definition_not_routed', ';'.join(sorted(d.path for d in self.defs[site.name]))
        d, why = self.common_contract(cands)
        if not d and len(cands) > 1:
            consumers = self.consumers(site.path) if site.in_header else [site.path]
            selected, evidence = [], []
            for path in consumers:
                item, reason, ev = self.named_in_tu(path, site.name, cands)
                if not item:
                    return None, reason, ev
                selected.append(item)
                evidence.append(ev)
            d, why = self.common_contract(selected)
            return d, why, ';'.join(sorted(set(evidence)))
        return d, why, 'definition:' + (d.path if d else site.name)

    def documented_identity(self, site, records):
        """Use a reviewed contract without rebinding a historical numeric call.

        This is site-specific signature evidence, not placement or execution
        evidence. The canonical declaration and hashed review must stay current.
        """
        if len(records) != 1 or not re.fullmatch(r'func_[0-9A-F]{8}', site.name):
            return None, 'documented_identity_ambiguous', ''
        record = records[0]
        evidence = record.get('evidence', '')
        review = (self.root / evidence).resolve()
        if (record.get('schema') != 'azure-clean.prototype-identity.v1'
                or not evidence.startswith('docs/evidence/')
                or not review.is_relative_to(self.root.resolve())
                or not review.is_file()
                or hashlib.sha256(review.read_bytes()).hexdigest() != record.get('evidence_sha256')):
            return None, 'documented_identity_stale_review', evidence
        if self.identity_contracts is None:
            _, sites, _ = M.collect(self.corpus, self.types)
            self.identity_contracts = sites
        contracts = [s for s in self.identity_contracts
                     if s.path == record.get('contract_file') and s.name == record.get('contract_symbol')
                     and s.params is not None and not s.complex
                     and compact(s.text) == compact(record.get('contract', ''))]
        if len(contracts) != 1:
            return None, 'documented_identity_stale_contract', evidence
        contract = contracts[0]
        definition = M.FuncDef(contract.name, contract.path, contract.line, False,
                               contract.ret_spec, contract.ret_ptr, contract.params,
                               contract.text.strip().rstrip(';'), M.container_of(contract.path))
        if contract.storage == 'static' or definition.varargs or any(p == ['...'] for p in contract.params):
            return None, 'documented_identity_invalid_contract', evidence
        return definition, '', 'documented_identity:' + evidence + ':' + contract.path + ':' + contract.name


@dataclass
class Edit:
    file: str
    symbol: str
    before: str
    after: str
    header: str
    definition: str
    evidence: str
    action: str = 'prototype'
    type_headers: str = ''
    tags: str = ''
    occurrences: int = 1


MAP_FIELDS = list(Edit.__dataclass_fields__)
HOLD_FIELDS = ['file', 'symbol', 'reason', 'definition', 'evidence']


def promoted_formals(formals, names, types, path):
    declared = {}
    if not formals.strip() or any(t in formals for t in ('=', '}', '#')):
        return None
    for item in cscan.scan(formals).items:
        if item.kind != 'decl' or item.has_body_braces:
            return None
        for decl in item.decls:
            if decl.name not in names or decl.name in declared or decl.complex or decl.is_function:
                return None
            ptr = decl.ptr + int(decl.suffix.startswith('['))
            spelling = ' '.join(item.spec) + ' ' + '*' * ptr
            canon = M.canon(item.spec, ptr, types.visible(path))
            if not ptr and canon[0] in ('char', 's8', 'u8', 's16', 'u16'):
                spelling = 'int '
            elif not ptr and canon[0] == 'f32':
                spelling = 'double '
            declared[decl.name] = compact(spelling + ' ' + decl.name)
    return [declared[n] for n in names] if set(declared) == set(names) else None


def census(root):
    corpus = M.Corpus(root)
    types = M.TypeIndex(corpus)
    definitions, sites, _ = M.collect(corpus, types)
    for name, ds in definitions.items():
        for index, definition in enumerate(ds):
            if not definition.knr:
                continue
            item = next((it for it in corpus.scan(definition.path).items
                         if it.kind == 'def' and it.line == definition.line), None)
            if item is None:
                continue
            masked = corpus.scan(definition.path).masked
            match = re.search(r'\b' + re.escape(name) + r'\s*\(', masked[item.start:item.body[0]])
            start = item.start + match.end() - 1
            close = balanced(masked, start)
            args = promoted_formals(masked[close + 1:item.body[0]],
                                    [p[0] for p in definition.params], types, definition.path)
            if args is not None:
                ret = compact(' '.join(definition.ret_spec) + ' ' + '*' * definition.ret_ptr)
                ds[index] = replace(definition, params=[cscan.tokens(a) for a in args],
                                    proto=f'{ret} {name}({", ".join(args)})', knr=False)
    actual_sites = []
    for site in sites:
        if site.name in ('asm', '__asm__'):
            continue  # file-scope assembler statements are not C declarations
        # The shared top-level scanner stops at the first K&R formal's ';'.
        # Recover that definition separately, and do not count its header as
        # an identifier-list DECLARATION. A prototype for an old-style
        # definition must use default-promoted formal types (C89 3.5.4.3).
        if identifier_list(site.params, types.visible(site.path)):
            masked = corpus.scan(site.path).masked
            match = re.search(r'\b' + re.escape(site.name) + r'\s*\(', masked[site.start:])
            start = site.start + match.end() - 1
            close = balanced(masked, start)
            rest = masked[close + 1:]
            if not rest.lstrip().startswith(';'):
                brace = rest.find('{')
                formals = rest[:brace] if brace >= 0 else ''
                names = [p[0] for p in site.params]
                promoted = promoted_formals(formals, names, types, site.path)
                if promoted is not None:
                    args = ', '.join(promoted)
                    ret = compact(' '.join(site.ret_spec) + ' ' + '*' * site.ret_ptr)
                    proto = f'{ret} {site.name}({args})'
                    d = M.FuncDef(site.name, site.path, site.line, site.storage == 'static',
                                  site.ret_spec, site.ret_ptr, [cscan.tokens(a) for a in promoted],
                                  proto, M.container_of(site.path))
                    definitions[site.name].append(d)
                    continue
        actual_sites.append(site)
    return corpus, types, definitions, actual_sites


def candidates(root, scope=(), skip=(), wide_only=False, symbols=(), prefer_headers=True):
    corpus, types, definitions, sites = census(root)
    resolver = Resolver(root, corpus, types, definitions)
    typed = {(s.path, s.name): s for s in sites if s.params is not None}
    contracts_per_header = Counter(path for path, name in typed)
    collectors = {'include/' + path.removeprefix('src/').removesuffix('.c') + '.h'
                  for path in corpus.c_files}
    edits, holds = [], []
    skipped = {(r['file'], r['symbol']): r['reason'] for r in skip}
    remaining = [s for s in sites if unprototyped(s, types)]
    anchors = Counter((s.path, s.name, compact(s.text)) for s in remaining)
    visited = set()
    for site in remaining:
        if scope and not any(site.path == p or site.path.startswith(p.rstrip('/') + '/') for p in scope):
            continue
        if symbols and site.name not in symbols:
            continue
        hold = dict(file=site.path, symbol=site.name, definition='', evidence='')
        anchor = (site.path, site.name, compact(site.text))
        if anchor in visited:
            continue
        visited.add(anchor)
        occurrences = anchors[anchor]
        text = corpus.text(site.path)
        line_end = text.find('\n', site.end)
        tail = text[site.end:line_end if line_end >= 0 else len(text)]
        exception = re.search(r'/\*\s*Unprototyped:\s*(.*?)\s*\*/', tail)
        if exception:
            holds.append(dict(hold, reason='documented_varying_arguments', evidence=exception[1]))
            continue
        why = skipped.get((site.path, site.name), '')
        if why:
            holds.append(dict(hold, reason=why))
            continue
        if site.complex or site.ndecl != 1:
            holds.append(dict(hold, reason='complex_or_multiple_declarators'))
            continue
        d, why, evidence = resolver.resolve(site)
        hold.update(definition=d.path + ':' + d.name if d else '', evidence=evidence)
        if not d:
            holds.append(dict(hold, reason=why))
            continue
        if d.knr or d.complex:
            holds.append(dict(hold, reason='old_style_or_complex_definition'))
            continue
        if d.varargs:
            holds.append(dict(hold, reason='genuine_variadic_definition'))
            continue
        if wide_only:
            vis = types.visible(d.path)
            ps = [M.canon(*M.param_parts(p)[:2], vis) for p in d.params if p != ['...']]
            if any(M.abi(p) not in ('w', 'p') for p in ps):
                holds.append(dict(hold, reason='deferred_narrow_or_aggregate_parameter'))
                continue
        # A nested implementation may still belong to an established parent
        # folder API (for example town/person/object -> town/person.h).
        # Search only its folder ancestry, and require the exact contract.
        owners = [d.path]
        if d.path.startswith('src/'):
            folders = d.path.split('/')[1:-1]
            owners = ['include/' + '/'.join(folders[:n]) + '.h'
                      for n in range(len(folders), 0, -1)]
        # A folder API may re-export a smaller shared feature header. Prefer
        # its actual declaration so importing allocation need not expose the
        # independent draw-registration contracts from node.h.
        exported = []
        for folder in owners:
            exported.append(folder)
            if folder in corpus.h_files:
                exported.extend(h for h in corpus.closure(folder)
                                if h.startswith(folder.removesuffix('.h') + '/'))
        # An implementation can include a shared feature API without exposing
        # it to every user of the broad folder header. Require multiple named
        # contracts, actual definition-side inclusion and folder ownership;
        # source collectors are not public feature APIs.
        if d.path.startswith('src/'):
            feature_dir = owners[0].removesuffix('.h') + '/'
            exported.extend(sorted(h for h in corpus.closure(d.path)
                                   if h.startswith(feature_dir) and h not in collectors
                                   and contracts_per_header[h] >= 2))
        owner = next((h for h in exported if (h, site.name) in typed
                      and prototype_key(typed[h, site.name], types) == M.def_key(d, types)), '')
        use_header = (prefer_headers and not d.static and bool(owner) and site.path != owner
                      and site.path not in corpus.closure(owner))
        if use_header:
            edits.append(Edit(site.path, site.name, site.text, '', owner,
                              d.path + ':' + d.name, evidence, 'include', occurrences=occurrences))
            continue
        th, tags, subst, why = P.type_needs(d, types)
        if why:
            holds.append(dict(hold, reason=why))
            continue
        # Private tagged pointer types can be spelled with their C tag. Never
        # invent a void* or scalar substitute for a record passed by value.
        proto = P.substituted_proto(d, subst)
        d_proto = replace(d, proto=proto)
        args = re.sub(r'\bregister\s+', '', params_text(d_proto))
        # Pull shared type headers into the caller when needed, and declare
        # private tagged records at file scope so they do not become C's
        # prototype-scope tags. Anonymous private records stay held above.
        vis = types.visible(site.path)
        missing = [h for h in th if h not in corpus.closure(site.path)]
        missing_tags = [tag for tag in tags if tag not in set().union(
            *(M.file_tags(corpus, p) for p in corpus.closure(site.path)))
            and not re.search(r'\b' + re.escape(tag) + r'\s*;', corpus.scan(site.path).masked)]
        # Preserve attributes/asm aliases at the declaration site. Replacing
        # only the parameter span does not alter address identity annotations.
        original = site.text
        masked = cscan.mask(original)
        m = re.search(r'\b' + re.escape(site.name) + r'\s*\(', masked)
        if not m:
            holds.append(dict(hold, reason='no_simple_anchor'))
            continue
        start = m.end() - 1
        end = balanced(masked, start)
        # Recover the return type too. If its use changes generated bytes or
        # exposes an invalid use of a void result, proof must reject the edit.
        ret = M.canon(site.ret_spec, site.ret_ptr, vis)
        real_ret = M.def_key(d, types)[0]
        after = original[:start + 1] + args + original[end:]
        if ret != real_ret:
            ret_match = re.search(r'\b' + re.escape(d.name) + r'\s*\(', proto)
            real_spelling = re.sub(r'\b(?:static|extern|inline|__inline__)\b\s*', '',
                                   proto[:ret_match.start()]).strip()
            head_end = m.start()
            storage = site.storage + ' ' if site.storage else ''
            after = storage + real_spelling + ' ' + after[head_end:]
        if len(re.findall(r'\bvolatile\b', after)) > len(re.findall(r'\bvolatile\b', original)):
            holds.append(dict(hold, reason='volatile_contract_requires_review'))
            continue
        edits.append(Edit(site.path, site.name, original, after, '', d.path + ':' + d.name, evidence,
                          type_headers=';'.join(missing), tags=';'.join(missing_tags), occurrences=occurrences))
    return corpus, types, remaining, edits, holds


def rewrite(text, edits, *, ensure_headers=()):
    """Replay by unique declaration symbol AND normalised statement, never line.

    Validate all anchors before producing output. A moved, merged, already
    typed or conflicting site is refused instead of applying a stale span.
    """
    scan = cscan.scan(text)
    replacements, headers, tags = [], set(ensure_headers), set()
    for edit in edits:
        matches = [it for it in scan.items if it.kind == 'decl'
                   and any(d.name == edit.symbol and d.is_function for d in it.decls)
                   and compact(it.text) == compact(edit.before)]
        expected = int(edit.occurrences)
        if expected < 1 or len(matches) != expected:
            raise ValueError(f'{edit.file}:{edit.symbol}: expected {expected} declaration anchors, got {len(matches)}')
        headers.update(filter(None, edit.type_headers.split(';')))
        tags.update(filter(None, edit.tags.split(';')))
        for it in matches:
            start, end, after = it.start, it.end, edit.after
            if edit.action == 'include':
                headers.add(edit.header)
                # Consume a whole line only for a standalone declaration and
                # its generated extern marker; preserve meaningful comments.
                ls = text.rfind('\n', 0, start) + 1
                le = text.find('\n', end)
                le = len(text) if le < 0 else le + 1
                tail = text[end:le].strip()
                if not text[ls:start].strip() and tail in ('', '/* extern */'):
                    start, end = ls, le
            else:
                # Do not carry old padding at the end of a rewritten
                # declaration onto a newly changed line.
                le = text.find('\n', end)
                le = len(text) if le < 0 else le
                if not text[end:le].strip():
                    end = le
            replacements.append((start, end, after))
    is_header = bool(edits) and edits[0].file.endswith('.h')
    includes = [d for d in scan.directives if d.kind == 'include' and d.depth <= int(is_header)]
    first_use = min((it.start for it in scan.items), default=len(text))
    requested = {'\"' + h.removeprefix('include/') + '\"' for h in headers}
    late = [d for d in includes if d.end > first_use and d.arg.strip() in requested]
    replacements.extend((d.start, d.end, '') for d in late)
    existing = {d.arg.strip() for d in includes if d not in late}
    added = [f'#include "{h[len("include/"):]}"\n' for h in sorted(headers)
             if f'"{h[len("include/"):]}"' not in existing]
    additions = ''.join(added) + ''.join(t + ';\n' for t in sorted(tags))
    if additions:
        guard = [d for d in scan.directives if d.kind == 'define' and d.depth == 1]
        # Concatenated TUs can have includes after earlier function bodies.
        # The imported contract must be visible at every removed declaration.
        leading = [d for d in includes if d.end <= first_use]
        at = leading[-1].end if leading else guard[0].end if is_header and guard else 0
        replacements.append((at, at, additions))
    pos, pieces = 0, []
    for start, end, after in sorted(replacements):
        if start < pos:
            raise ValueError('overlapping prototype transaction')
        pieces.extend((text[pos:start], after))
        pos = end
    return ''.join(pieces) + text[pos:]


def apply_edits(root, edits):
    by_file = defaultdict(list)
    for edit in edits:
        path = Path(edit.file)
        if path.is_absolute() or '..' in path.parts or not edit.file.startswith(('src/', 'include/')):
            raise ValueError('unsafe source path')
        if not (root / path).resolve().is_relative_to(root):
            raise ValueError('source path escapes checkout')
        by_file[edit.file].append(edit)
    # Preflight the whole transaction before writing ANY source.
    outputs = {p: rewrite((root / p).read_text(), es) for p, es in by_file.items()}
    for path, text in outputs.items():
        (root / path).write_text(text)
    return sorted(outputs)


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument('--root', type=Path, default=ROOT)
    ap.add_argument('--scope', nargs='+', default=[])
    ap.add_argument('--out', type=Path)
    ap.add_argument('--check', action='store_true', help='exit 1 if declarations exceed --max-remaining')
    ap.add_argument('--max-remaining', type=int)
    ap.add_argument('--baseline', type=Path, help='remaining.tsv; --check also refuses every new declaration site')
    ap.add_argument('--apply', action='store_true')
    ap.add_argument('--wide-only', action='store_true', help='defer narrow scalar and by-value aggregate parameters')
    ap.add_argument('--in-place', action='store_true', help='recover the local declaration when importing its owner requires separate type cleanup')
    ap.add_argument('--skip', type=Path, help='reviewed holds TSV (file, symbol, reason)')
    ap.add_argument('--symbols', nargs='+', default=[], help='limit proposals to these symbols')
    args = ap.parse_args(argv)
    root = args.root.resolve()
    for option in ('skip', 'baseline'):
        path = getattr(args, option)
        if path is not None and not path.is_file():
            ap.error('--' + option + ' must name an existing TSV')
    if args.check:
        if args.apply:
            ap.error('--check and --apply are mutually exclusive')
        corpus, types, _, sites = census(root)
        remaining = [s for s in sites if unprototyped(s, types)]
        rows = [dict(file=s.path, symbol=s.name,
                     kind='empty' if s.params is None else 'identifier_list') for s in remaining]
        summary = dict(remaining=len(rows), empty=sum(r['kind'] == 'empty' for r in rows),
                       identifier_list=sum(r['kind'] == 'identifier_list' for r in rows),
                       by_subsystem=dict(sorted(Counter('/'.join(r['file'].split('/')[:2]) for r in rows).items())))
        baseline = table(args.baseline) if args.baseline else []
        key = lambda r: (r['file'], r['symbol'], r['kind'])
        new = Counter(map(key, rows)) - Counter(map(key, baseline)) if args.baseline else Counter()
        if args.baseline:
            summary['new_declarations'] = sum(new.values())
        limit = args.max_remaining if args.max_remaining is not None else len(baseline)
        slots = []
        for path in corpus.c_files + corpus.h_files:
            for match in re.finditer(r'\(\s*\*+\s*([A-Za-z_]\w*)\s*(?:\[[^\]]*\])?\s*\)\s*\(\s*\)',
                                     corpus.scan(path).masked):
                slots.append(dict(file=path, symbol=match[1], reason='callback_signature_analysis'))
        summary['untyped_function_pointer_slots'] = len(slots)
        if args.out:
            args.out.mkdir(parents=True, exist_ok=True)
            write_table(args.out / 'remaining.tsv', rows, ['file', 'symbol', 'kind'])
            write_table(args.out / 'function_pointer_slots.tsv', slots, ['file', 'symbol', 'reason'])
            (args.out / 'count.json').write_text(json.dumps(summary, indent=2, sort_keys=True) + '\n')
        print(json.dumps(summary, sort_keys=True))
        return int(len(rows) > limit or bool(new))
    if args.apply and not args.out:
        ap.error('--apply requires --out to preserve its replay map')
    corpus, types, remaining, edits, holds = candidates(root, args.scope,
        table(args.skip) if args.skip else (), args.wide_only, args.symbols,
        prefer_headers=not args.in_place)
    if args.out:
        args.out.mkdir(parents=True, exist_ok=True)
        write_table(args.out / 'replay.tsv', [asdict(e) for e in edits], MAP_FIELDS)
        write_table(args.out / 'holds.tsv', holds, HOLD_FIELDS)
    files = apply_edits(root, edits) if args.apply else sorted({e.file for e in edits})
    summary = dict(remaining_before=len(remaining), proposed=len(edits), holds=len(holds),
                   declarations=sum(int(e.occurrences) for e in edits), files=len(files),
                   actions=dict(Counter(e.action for e in edits)), applied=args.apply)
    if args.out:
        (args.out / 'summary.json').write_text(json.dumps(summary, indent=2, sort_keys=True) + '\n')
        (args.out / 'files.txt').write_text(''.join(p + '\n' for p in files))
    print(json.dumps(summary, sort_keys=True))
    return 0


if __name__ == '__main__':
    raise SystemExit(main())
