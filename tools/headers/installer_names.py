#!/usr/bin/env python3
"""Expose data-alias callback installs as function designators.

Input is a reviewed hidden-edges TSV, not an address-wide rename authority.
`plan` checks every compiled installer image against its linked function starts;
`apply` adds the existing owner header, removes local alias declarations and
rewrites code tokens only. Missing owner prototypes and unproved images hold.
Acceptance still requires prove_batch.sh, native compilation and make check.
"""
from __future__ import annotations

import argparse
from collections import Counter, defaultdict
import csv
import gzip
import json
from pathlib import Path
import re
import sqlite3
import sys

HERE = Path(__file__).resolve().parent
sys.path[:0] = [str(HERE), str(HERE.parent / 'codemap'), str(HERE.parent / 'gate')]
import address_names as A
import cscan
import model as M
import plan as P

FIELDS = ['file', 'installer', 'old', 'new', 'callback_file', 'address', 'kind',
          'header', 'prototype', 'type_headers', 'tags', 'images', 'link', 'rows', 'evidence']
EXCLUDED = ('src/dungeon/monster/', 'src/dungeon/actor/',
            'src/dungeon/player/', 'src/dungeon/modules/')


def read_tsv(path):
    with Path(path).open() as stream:
        return list(csv.DictReader(stream, delimiter='\t'))


def write_tsv(path, rows, fields=FIELDS):
    with Path(path).open('w') as stream:
        writer = csv.DictWriter(stream, fields, delimiter='\t', lineterminator='\n')
        writer.writeheader()
        writer.writerows(rows)


def current_spelling(text, installer, old, callback, names):
    """Follow a frozen data spelling through a later semantic data rename.

    Require the same canonical symbol and exactly one candidate in the named
    installer's body. An already visible callback stays outside this rewrite.
    """
    if re.search(A.TOKEN.format(re.escape(old)), cscan.mask(text)):
        return old
    symbol = names.get(old, old)
    tokens = set()
    scan = cscan.scan(text)
    for item in scan.items:
        if item.kind == 'def' and item.decls[0].name == installer:
            tokens.update(re.findall(r'\b[A-Za-z_]\w*\b', scan.masked[item.body[0]:item.body[1]]))
    matches = {token for token in tokens if token != callback and names.get(token, token) == symbol}
    return matches.pop() if len(matches) == 1 else old


def declarations(text, name):
    """Remove single-name external declarations, preserving actual storage."""
    scan = cscan.scan(text)
    result = []
    for item in scan.items:
        external_function = (item.kind == 'decl' and len(item.decls) == 1 and item.decls[0].is_function
                             and not {'static', 'typedef'} & set(item.storage))
        if (item.kind == 'decl' and ('extern' in item.storage or external_function) and len(item.decls) == 1
                and item.decls[0].name == name and '=' not in scan.masked[item.start:item.end]):
            result.append((item.start, item.end))
    return result


def address_pattern(name):
    token = A.TOKEN.format(re.escape(name))
    atom = token + r'(?:\s*\[\s*0\s*\])?(?!\s*\[)'
    return r'(?<![&])&(?![&])\s*(?:\(\s*' + atom + r'\s*\)|' + atom + r')'


def rewrite(text, pairs):
    """Return text and counts. Pairs are (old, new, owner header).

    An array data alias decays to its address; a scalar alias must be addressed.
    Bare scalar uses (loads) are held by the planner. Both &alias and & (alias)
    become the function designator. Existing destination casts are preserved.
    """
    edits, headers, counts = [], set(), {}
    masked = cscan.mask(text)
    for old, new, header in pairs:
        spans = declarations(text, old)
        use_mask = list(masked)
        for start, end in spans:
            edits.append((start, end, ''))
            use_mask[start:end] = ' ' * (end - start)
        body = ''.join(use_mask)
        token = A.TOKEN.format(re.escape(old))
        addressed = list(re.finditer(address_pattern(old), body))
        covered = [(m.start(), m.end()) for m in addressed]
        for match in addressed:
            edits.append((match.start(), match.end(), new))
        bare = [m for m in re.finditer(token, body)
                if not any(start <= m.start() < end for start, end in covered)]
        edits.extend((m.start(), m.end(), new) for m in bare)
        count = len(addressed) + len(bare)
        if count:
            headers.add(header)
            counts[old] = count
    for start, end, value in sorted(set(edits), reverse=True):
        text = text[:start] + value + text[end:]
    for header in sorted(headers):
        line = '#include "%s"\n' % P.include_token(header)
        if line in text:
            continue
        includes = list(re.finditer(r'^\s*#include[^\n]*\n', text, re.M))
        at = includes[-1].end() if includes else 0
        text = text[:at] + line + text[at:]
    return text, counts


def check_entry(contexts, entries, callback_file, callback, address, before,
                after, tables, link_index):
    """Prove entry identity AND new-symbol reachability for all installer units.

    entries: image -> {address: (source files, function name)} from actual maps
    and object section symbols. Reused addresses in other images cannot help.
    """
    import linklist as L
    if not contexts:
        return 'no_installer_image', '', []
    copy_rows = set()
    evidence = []
    for image, rows, rebind in contexts:
        placement = [link_index[r] for r in rows if r in link_index]
        if rebind and len(placement) != 1:
            return 'unknown_installer_placement', '', []
        try:
            old_target = L._binding(tables, placement[0], before) if rebind else before
            new_target = L._binding(tables, placement[0], after) if rebind else after
            if not rebind and before != after:
                # A home unit reaches a placed copy only with the opt-in record.
                new_target = L.copy_link_target(tables, image, after)
                if new_target == old_target:
                    copy_rows.update(rows)
        except ValueError:
            return 'unproved_copy_binding', '', []
        target = entries.get(image, {}).get(old_target)
        if not target or callback_file not in target[0] or target[1] != callback:
            return 'callback_not_entry_in_installer_image', '', []
        if new_target != old_target:
            return 'new_symbol_binds_elsewhere', '', []
        evidence.append('%s:0x%08X=%s' % (image, old_target, callback))
    if before != address:
        return 'alias_address_differs_from_review', '', []
    return '', ' | '.join(sorted(set(evidence))), sorted(copy_rows)


def plan(root, db_path, edge_path, scope):
    import bind
    import linklist as L
    db = sqlite3.connect('file:%s?mode=ro' % db_path, uri=True)
    names = A.names_table(root)
    lower = lambda n: names.get(n, n)
    tables = L.load(root)
    candidates = [r for r in read_tsv(edge_path) if r['source_spelling'] == 'data_alias'
                  and A.in_scope(r['installer_file'], scope)
                  and not r['installer_file'].startswith(EXCLUDED)]
    for row in candidates:
        text = (root / row['installer_file']).read_text()
        row['name_used'] = ','.join(current_spelling(text, row['installer'], old, row['callback'], names)
                                    for old in row['name_used'].split(','))
    contexts = defaultdict(list)
    files_of = defaultdict(set)
    for rid, source, physical in db.execute('select id,source,physical from recipe'):
        files_of[rid].update(f for f in (source, physical) if f)
    for rid, dep in db.execute("select recipe,path from tu_dep where path like '%.c'"):
        files_of[rid].add(dep)
    for image, rid, rows, reb in db.execute('select image,recipe,rows,rebind from image_unit'):
        for file in files_of[rid]:
            contexts[file].append((image, json.loads(rows or '[]'), reb))
    wanted_images = {image for r in candidates for image, *_ in contexts[r['installer_file']]}
    image_rows = [r for r in db.execute('select name,tag,output from image') if r[0] in wanted_images]
    layouts = bind.load_layouts(root, image_rows, bind.object_sections(root))
    definitions = defaultdict(set)
    for name, file in db.execute('select name,file from defn'):
        definitions[(file, lower(name))].add(name)
    entries = {}
    for image, layout in layouts.items():
        entries[image] = {}
        if layout.errors:
            continue
        for address, (rid, symbol, _) in layout.functions.items():
            found = {(f, name) for f in files_of[rid] for name in definitions[(f, symbol)]}
            if len({name for f, name in found}) == 1:
                entries[image][address] = ({f for f, name in found}, next(iter(found))[1])
    headers = defaultdict(set)
    header_types = defaultdict(set)
    definition_types = defaultdict(set)
    for name, file, canonical in db.execute('select name,file,canon_norm from defn'):
        definition_types[(name, file)].add(canonical)
    for name, header, canonical in db.execute("select name,file,canon_norm from decl where kind='proto' and file like 'include/%'"):
        headers[name].add(header)
        header_types[(name, header)].add(canonical)
    # A previously unpublished definition may gain its exact prototype in its
    # folder's interface. Reuse the header tool's type-visibility rules rather
    # than copying private typedefs into an interface.
    corpus = M.Corpus(root, files=sorted({r['callback_file'] for r in candidates}))
    tindex = M.TypeIndex(corpus)
    function_defs, _, _ = M.collect_files(corpus, tindex, corpus.c_files)
    # Only data aliases with a single agreed target per installer are eligible.
    targets = defaultdict(set)
    for r in candidates:
        for old in r['name_used'].split(','):
            targets[(r['installer_file'], old)].add((r['callback_file'], r['callback'], r['address']))
    out, holds = [], []
    seen = set()
    for r in candidates:
        file, new = r['installer_file'], r['callback']
        text = (root / file).read_text()
        masked = cscan.mask(text)
        for old in r['name_used'].split(','):
            key = (file, r['installer'], old, new)
            if key in seen:
                continue
            seen.add(key)
            row = dict(file=file, installer=r['installer'], old=old, new=new,
                       callback_file=r['callback_file'], address=r['address'],
                       kind='data_alias_install', header='', prototype='', type_headers='', tags='',
                       images='', link='', rows='', evidence='')
            reason = ''
            if len(targets[(file, old)]) != 1:
                reason = 'ambiguous_review_target'
            symbol, new_symbol = lower(old), lower(new)
            before, after = A.ADDR.fullmatch(symbol), A.ADDR.fullmatch(new_symbol)
            if not reason and (not before or not after):
                reason = 'unknown_canonical_symbol'
            owner = P.header_for(r['callback_file'])
            exact = {h for h in headers[new]
                     if header_types[(new, h)] == definition_types[(new, r['callback_file'])]
                     and definition_types[(new, r['callback_file'])]}
            available = {h for h in exact if h.startswith('include/' + r['callback_file'].split('/')[1] + '/')}
            if not available:
                available = exact
            header = owner if owner in available else next(iter(available)) if len(available) == 1 else ''
            row['header'] = header
            if not reason and not header and owner in headers[new]:
                reason = 'owner_prototype_conflict'
            if not reason and not header:
                definitions_here = [d for d in function_defs[new] if d.path == r['callback_file'] and not d.static]
                if len(definitions_here) != 1:
                    reason = 'missing_owner_prototype:no_unique_definition'
                else:
                    definition = definitions_here[0]
                    th, tags, subst, problem = P.type_needs(definition, tindex)
                    if definition.knr or definition.complex or definition.varargs:
                        problem = 'complex_definition'
                    if re.search(r'\bM2C_\w*', P.substituted_proto(definition, subst)):
                        problem = 'legacy_placeholder_type'
                    if problem:
                        reason = 'missing_owner_prototype:' + problem
                    else:
                        row['header'] = owner
                        row['prototype'] = P.substituted_proto(definition, subst) + ';'
                        row['type_headers'] = ','.join(th)
                        row['tags'] = ','.join(tags)
            spans = declarations(text, old)
            if not reason:
                for item in cscan.scan(text).items:
                    if (item.kind == 'decl' and any(d.name == old for d in item.decls)
                            and (item.start, item.end) not in spans):
                        reason = 'nonremovable_alias_declaration'
            body = list(masked)
            for start, end in spans:
                body[start:end] = ' ' * (end - start)
            body = ''.join(body)
            if not reason and not re.search(A.TOKEN.format(re.escape(old)), body):
                reason = 'alias_no_longer_used'
            # Bare scalar data names would load data rather than materialise an address.
            if not reason:
                types = [sig for sig, in db.execute('select signature from decl where file=? and name=?', (file, old))]
                addressed = re.sub(address_pattern(old), '', body)
                if re.search(A.TOKEN.format(re.escape(old)) + r'\s*\[', addressed):
                    reason = 'data_or_interior_index_use'
                if re.search(A.TOKEN.format(re.escape(old)), addressed) and not any('[' in t or '(' in t for t in types):
                    # A declaration can be supplied transitively by a header.
                    types += [sig for sig, in db.execute('select signature from decl where name=?', (old,))]
                    if not types or not all('[' in t or '(' in t for t in types):
                        reason = 'bare_scalar_or_untyped_use'
            if not reason:
                reason, evidence, copies = check_entry(contexts[file], entries, r['callback_file'], new,
                                                       int(r['address'], 0), int(before[1], 16), int(after[1], 16),
                                                       tables, tables[2])
                row['evidence'] = evidence
                row['images'] = ','.join(sorted({i for i, *_ in contexts[file]}))
                if copies:
                    row['link'] = '%s>%s' % (new_symbol, 'func_%s' % before[1].upper())
                    row['rows'] = ' '.join(copies)
            if reason:
                row['evidence'] = reason
                holds.append(row)
            else:
                out.append(row)
    db.close()
    return out, holds


def apply(root, rows):
    import rewrite as R
    from types import SimpleNamespace
    corpus = M.Corpus(root, files=[])
    by_header = defaultdict(dict)
    for row in rows:
        if row.get('prototype'):
            by_header[row['header']][row['new']] = row
    for header, functions in sorted(by_header.items()):
        specs = [SimpleNamespace(name=r['new'], proto=r['prototype'].rstrip(';'),
                                 type_headers=tuple(filter(None, r['type_headers'].split(','))),
                                 tags=tuple(filter(None, r['tags'].split(',')))) for r in functions.values()]
        owner_plan = SimpleNamespace(headers={header: specs}, corpus=corpus)
        path = root / header
        if not path.is_file():
            path.parent.mkdir(parents=True, exist_ok=True)
            guard = P.guard_for(header)
            path.write_text('#ifndef %s\n#define %s\n#include "common.h"\n\n#endif\n' % (guard, guard))
        path.write_text(R.append_text(owner_plan, header, list(functions), path.read_text()))
    grouped = defaultdict(dict)
    for row in rows:
        grouped[row['file']][row['old']] = (row['old'], row['new'], row['header'])
    changed = []
    for file, pairs in sorted(grouped.items()):
        path = root / file
        before = path.read_text()
        after, counts = rewrite(before, list(pairs.values()))
        if before != after:
            path.write_text(after)
            changed.append(dict(file=file, replacements=counts))
    copies = [dict(row, kind='placed_copy', evidence='same-image entry; rows ' + row['rows'])
              for row in rows if row['link']]
    if copies:
        A.link_records(root, copies)
    module_imports(root, rows)
    return changed


def module_imports(root, rows):
    """Project address respellings onto native modules' explicit import inventory.

    Self addresses cease being imports. External function addresses replace
    the data view at the proven entry, retaining the old import if another
    spelling still uses it. The module gate verifies the resulting inventory.
    """
    path = root / 'config/overlays/modules.json'
    if not path.is_file():
        return
    document = json.loads(path.read_text())
    names = A.names_table(root)
    lower = lambda n: names.get(n, n)
    changed = False
    for module in document['modules']:
        relevant = [r for r in rows if r['file'] == module.get('source')]
        if not relevant:
            continue
        text = cscan.mask((root / module['source']).read_text())
        # Unused extern declarations do not contribute undefined symbols.
        for item in cscan.scan(text).items:
            if item.kind == 'decl' and 'extern' in item.storage:
                text = text[:item.start] + ' ' * (item.end - item.start) + text[item.end:]
        used = {lower(token) for token in re.findall(r'\b[A-Za-z_]\w*\b', text)}
        owned = {m['function'] for m in module['members']}
        imports = {r['symbol']: r for r in module['imports']}
        before = dict(imports)
        for row in relevant:
            old, new = lower(row['old']), lower(row['new'])
            if old not in imports:
                continue
            address = imports[old]['vma']
            if old not in used:
                del imports[old]
            if new not in owned and new in used:
                imports.setdefault(new, dict(symbol=new, kind='function', vma=address))
        if imports != before:
            module['imports'] = sorted(imports.values(), key=lambda r: r['symbol'])
            changed = True
    if changed:
        path.write_text(json.dumps(document, indent=2) + '\n')


def retire(root, rows, write=True):
    """Remove extern-only dead aliases and their names rows, never real data storage.

    An alias used by an excluded folder remains. A still-used raw D_ symbol
    does not keep an unused readable alias alive; these are distinct C names.
    """
    sources = {p.relative_to(root).as_posix(): p.read_text() for top in ('src', 'include')
               for p in (root / top).rglob('*') if p.suffix in ('.c', '.h', '.inc') and p.is_file()}
    removed, changed_files, retained = [], set(), {}
    for old in sorted({r['old'] for r in rows}):
        removable = {}
        token = re.compile(A.TOKEN.format(re.escape(old)))
        for file, text in sources.items():
            if old not in text:
                continue
            masked = cscan.mask(text)
            spans = declarations(text, old)
            for start, end in spans:
                masked = masked[:start] + ' ' * (end - start) + masked[end:]
            if token.search(masked):
                retained[old] = dict(reason='live_reference_or_definition', file=file)
                break
            if spans:
                removable[file] = spans
        else:
            # Preserve all source text outside the selected lane scope. An
            # excluded source declaration by itself is a reason to keep it.
            if any(file.startswith(EXCLUDED) for file in removable):
                retained[old] = dict(reason='excluded_source_declaration',
                                     file=next(f for f in removable if f.startswith(EXCLUDED)))
                continue
            for file, spans in removable.items():
                text = sources[file]
                for start, end in sorted(spans, reverse=True):
                    text = text[:start] + text[end:]
                sources[file] = text
                changed_files.add(file)
                if write:
                    (root / file).write_text(text)
            removed.append(old)
    path = root / 'config/names.tsv'
    lines = path.read_text().splitlines(keepends=True)
    retired = []
    kept = []
    for line in lines:
        cols = line.rstrip('\n').split('\t')
        if len(cols) >= 3 and cols[2] in removed and cols[1].startswith('D_'):
            retired.append(cols[2])
        else:
            kept.append(line)
    if write:
        path.write_text(''.join(kept))
    if retired:
        changed_files.add('config/names.tsv')
    return dict(dead_aliases=removed, names_retired=retired, files_changed=sorted(changed_files), retained=retained)


def measure(db_path, rows):
    """Count FN-source install facts by installer identity; comparisons stay separate."""
    db = sqlite3.connect('file:%s?mode=ro' % db_path, uri=True)
    files = {r['file'] for r in rows}
    tus = set(files)
    for rid, source, physical in db.execute('select id,source,physical from recipe'):
        if source in files:
            tus.add(physical or source)
    if files:
        for physical, in db.execute("select distinct r.physical from recipe r join tu_dep d on d.recipe=r.id "
                                    "where d.path in (%s)" % ','.join('?' * len(files)), sorted(files)):
            if physical:
                tus.add(physical)
    facts = defaultdict(set)
    for tu in sorted(tus):
        result = db.execute('select blob from flow_tu where tu=?', (tu,)).fetchone()
        if not result:
            continue
        for edge in json.loads(gzip.decompress(result[0])).get('edges', []):
            values = [edge.get('src') or '']
            if edge['k'] == 'cmp':
                values.append(edge.get('dst') or '')
            for source in values:
                if not source.startswith(('FN:', '&FN:')):
                    continue
                function = source.split('FN:', 1)[1].split('@', 1)[0]
                key = (edge.get('file'), (edge.get('fn') or '').split('@', 1)[0], function)
                facts[key].add((edge.get('line'), edge['k'], edge.get('dst')))
    out = []
    for file, installer, new in sorted({(r['file'], r['installer'], r['new']) for r in rows}):
        sites = facts[(file, installer, new)]
        installs = [s for s in sites if s[1] in ('assign', 'init', 'arg', 'ret')]
        comparisons = [s for s in sites if s[1] == 'cmp']
        out.append(dict(file=file, installer=installer, callback=new,
                        install_sites=len(installs), comparison_sites=len(comparisons)))
    db.close()
    return out


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument('--root', type=Path, default=HERE.parents[1])
    sub = ap.add_subparsers(dest='command', required=True)
    p = sub.add_parser('plan')
    p.add_argument('--edges', type=Path, required=True)
    p.add_argument('--codemap', type=Path)
    p.add_argument('--scope', nargs='+', required=True)
    p.add_argument('--out', type=Path, required=True)
    for command in ('apply', 'retire', 'measure'):
        p = sub.add_parser(command)
        p.add_argument('--plan', type=Path, required=True)
        p.add_argument('--out', type=Path, required=True)
        if command == 'measure':
            p.add_argument('--codemap', type=Path)
        if command == 'retire':
            p.add_argument('--dry-run', action='store_true')
    a = ap.parse_args()
    root = a.root.resolve()
    a.out.mkdir(parents=True, exist_ok=True)
    if a.command == 'plan':
        rows, holds = plan(root, a.codemap or root / 'build/codemap.db', a.edges, a.scope)
        write_tsv(a.out / 'plan.tsv', rows)
        write_tsv(a.out / 'holds.tsv', holds)
        summary = dict(planned=len(rows), holds=dict(Counter(r['evidence'] for r in holds)))
    else:
        rows = read_tsv(a.plan)
        if a.command == 'measure':
            facts = measure(a.codemap or root / 'build/codemap.db', rows)
            write_tsv(a.out / 'visible.tsv', facts,
                      ['file', 'installer', 'callback', 'install_sites', 'comparison_sites'])
            summary = dict(reviewed_edges=len(facts), install_edges=sum(bool(r['install_sites']) for r in facts),
                           install_sites=sum(r['install_sites'] for r in facts),
                           comparison_edges=sum(bool(r['comparison_sites']) for r in facts))
        else:
            summary = apply(root, rows) if a.command == 'apply' else retire(root, rows, write=not a.dry_run)
    (a.out / (a.command + '.json')).write_text(json.dumps(summary, indent=2, sort_keys=True) + '\n')
    print(json.dumps(summary, sort_keys=True))


if __name__ == '__main__':
    main()
