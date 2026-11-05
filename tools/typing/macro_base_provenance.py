#!/usr/bin/env python3
"""Conservative provenance index for held file-local offset macro uses.

Consumes offset_macro_retire.py's inventory, scans only src C files, and writes
one row per held use plus a creator/callback-family queue.  It reports evidence,
not a type verdict: an allocator flag or an offset match alone never promotes
a candidate.  Duplicate function names stay file-qualified.

    python3 tools/typing/macro_base_provenance.py \
      --inventory build/offset_macros.tsv \
      --out build/macro_provenance
"""
from __future__ import annotations

import argparse
from collections import Counter, defaultdict
import csv
from dataclasses import dataclass
from pathlib import Path
import re
import sqlite3


ALLOC = re.compile(r'\b(allocate_list_node|allocate_flagged_object_node|initialize_scene_object_in_buffer|allocate_\w*node)\s*\(')
IDENT = re.compile(r'\b[A-Za-z_]\w*\b')
CALLBACK_STORE = re.compile(r'\bupdate_callback\s*=\s*&?\s*([A-Za-z_]\w*)\b')
GENERIC_STORE = re.compile(r'(?:\.|->)\s*(\w*(?:callback|handler|update|draw)\w*)\s*=\s*&?\s*([A-Za-z_]\w*)\b')
TYPED_BODY = re.compile(r'\b(?:struct\s+)?([A-Za-z_]\w*)\s*\*\s*([A-Za-z_]\w*)\s*(?:;|=\s*NODE_BODY\s*\()')
FN_END = re.compile(r'([A-Za-z_]\w*)\s*\((.*)\)\s*$', re.S)
TYPE_EXCLUDE = {'void', 'char', 'u8', 's8', 'u16', 's16', 'u32', 's32', 'long', 'short', 'int', 'const'}
SITE_FIELDS = ['file', 'function', 'line', 'macro', 'use', 'base_expr', 'class', 'reason', 'body_arg', 'family',
               'reach', 'reach_paths', 'installer', 'creator', 'creator_candidates', 'allocator',
               'record_type', 'confidence', 'evidence']
FAMILY_FIELDS = ['family', 'uses', 'body_uses', 'functions', 'callbacks', 'creator', 'allocator', 'record_type',
                 'confidence', 'reach', 'evidence', 'files']


def mask_noncode(text: str) -> str:
    """Keep character and newline positions while excluding comments and literals."""
    out = list(text)
    i = 0
    state = 'code'
    while i < len(text):
        ch = text[i]
        nxt = text[i + 1] if i + 1 < len(text) else ''
        if state == 'code':
            if ch == '/' and nxt == '*':
                state = 'block'
                out[i] = out[i + 1] = ' '
                i += 2
                continue
            if ch == '/' and nxt == '/':
                state = 'line'
                out[i] = out[i + 1] = ' '
                i += 2
                continue
            if ch in ('"', "'"):
                state = ch
                out[i] = ' '
        elif state == 'block':
            if ch == '*' and nxt == '/':
                out[i] = out[i + 1] = ' '
                state = 'code'
                i += 2
                continue
            if ch != '\n':
                out[i] = ' '
        elif state == 'line':
            if ch == '\n':
                state = 'code'
            else:
                out[i] = ' '
        else:
            if ch == '\\' and nxt:
                out[i] = ' '
                if nxt != '\n':
                    out[i + 1] = ' '
                i += 2
                continue
            if ch == state:
                state = 'code'
            out[i] = ' ' if ch != '\n' else '\n'
        i += 1
    return ''.join(out)


@dataclass(frozen=True)
class Function:
    file: str
    name: str
    params: str
    body: str
    start_line: int

    @property
    def key(self) -> str:
        return self.name + '@' + self.file


def functions(file: str, text: str) -> list[Function]:
    code = mask_noncode(text)
    out = []
    depth = 0
    start = 0
    open_at = -1
    header = None
    for i, ch in enumerate(code):
        if ch == '{':
            if depth == 0:
                # A definition header begins after the previous top-level item.
                segment = re.sub(r'(?m)^\s*#.*$', '', code[start:i])
                m = FN_END.search(segment.strip())
                header = m
                if header and header.group(1) in ('if', 'while', 'switch', 'for'):
                    header = None
                open_at = i
            depth += 1
        elif ch == '}' and depth:
            depth -= 1
            if depth == 0:
                if header:
                    out.append(Function(file, header.group(1), header.group(2), code[open_at + 1:i],
                                        code.count('\n', 0, open_at) + 1))
                start = i + 1
                header = None
        elif ch == ';' and depth == 0:
            start = i + 1
    return out


def first_param(params: str) -> tuple[str, str]:
    first = params.split(',', 1)[0].strip()
    m = re.search(r'\b(?:struct\s+)?([A-Za-z_]\w*)\s*\*\s*([A-Za-z_]\w*)\s*$', first)
    return (m.group(1) if m and m.group(1) not in TYPE_EXCLUDE else '', m.group(2) if m else '')


def body_types(fn: Function) -> dict[str, str]:
    """Types explicitly bound to NODE_BODY, never guessed from offsets."""
    result = {}
    body_sources = {var for var in re.findall(r'\b([A-Za-z_]\w*)\s*=\s*NODE_BODY\s*\(', fn.body)}
    # A common recovered spelling first saves header+1 into void storage.
    body_sources.update(re.findall(r'\b([A-Za-z_]\w*)\s*=\s*[A-Za-z_]\w*\s*\+\s*1\s*;', fn.body))
    for _ in range(3):
        for dest, src in re.findall(r'\b([A-Za-z_]\w*)\s*=\s*([A-Za-z_]\w*)\s*;', fn.body):
            if src in body_sources:
                body_sources.add(dest)
    for typ, var in TYPED_BODY.findall(fn.body):
        cast_from_body = re.search(r'\b' + re.escape(var) + r'\s*=\s*\(\s*' + re.escape(typ) +
                                   r'\s*\*\s*\)\s*\(\s*\(\s*u8\s*\*\s*\)\s*\w+\s*\+\s*0x20\s*\)',
                                   fn.body)
        if typ not in TYPE_EXCLUDE and (var in body_sources or cast_from_body):
            result[var] = typ
    return result


def read_inventory(path: Path) -> list[dict]:
    with path.open(newline='') as fh:
        return list(csv.DictReader(fh, delimiter='\t'))


def source_index(root: Path, names: set[str]):
    """Read each src C file once; only record references to inventory functions."""
    by_key = {}
    by_name = defaultdict(list)
    references = defaultdict(list)
    pattern = re.compile(r'\b(?:' + '|'.join(re.escape(n) for n in sorted(names, key=len, reverse=True)) + r')\b')
    for path in sorted((root / 'src').rglob('*.c')):
        if path.stat().st_size > 4_000_000:
            continue
        rel = path.relative_to(root).as_posix()
        code = mask_noncode(path.read_text(errors='replace'))
        funcs = functions(rel, code)
        for fn in funcs:
            by_key[fn.key] = fn
            by_name[fn.name].append(fn)
            for m in pattern.finditer(fn.body):
                name = m.group()
                tail = fn.body[m.end():]
                before = fn.body[max(0, m.start() - 90):m.start()]
                if re.match(r'\s*\(', tail):
                    reach = 'direct_call'
                elif re.search(r'(?:update_callback|callback|handler|draw|\[\s*\d+\s*\])\s*=\s*&?\s*$', before):
                    reach = 'callback_store'
                elif re.search(r'\bregister_node\s*\([^;]*,\s*&?\s*$', before):
                    reach = 'draw_registration'
                elif re.search(r'=\s*&?\s*$', before):
                    assigned = re.search(r'\b([A-Za-z_]\w*)\s*=\s*&?\s*$', before)
                    slot = assigned.group(1) if assigned else ''
                    if slot and re.search(r'\bregister_node\s*\([^;]*,\s*' + re.escape(slot) +
                                          r'\s*\)', fn.body):
                        reach = 'draw_registration_alias'
                    else:
                        reach = 'assigned_reference'
                else:
                    reach = 'dispatcher_table'
                references[name].append((fn, reach, code.count('\n', 0, code.find(fn.body[:40])) + fn.body.count('\n', 0, m.start()) + 1))
        # Table references outside function bodies, including designated initializers.
        if pattern.search(code):
            for m in pattern.finditer(code):
                # A top-level name followed by '(' is a declaration/definition,
                # not a dispatcher table entry (including multiline headers).
                if re.match(r'\s*\(', code[m.end():]):
                    continue
                # Only top-level initializer braces; avoid duplicating function-body references.
                line = code.count('\n', 0, m.start()) + 1
                if not any(f.start_line <= line <= f.start_line + f.body.count('\n') + 1 for f in funcs):
                    references[m.group()].append((Function(rel, '<table>', '', '', line), 'dispatcher_table', line))
    # Codemap's physical-TU call sites cover calls hidden behind declarations
    # that the lexical source scan may fail to classify. Read it, never refresh
    # it from this tool; the provenance inventory is otherwise source-only.
    db_path = root / 'build/codemap.db'
    if db_path.is_file():
        with sqlite3.connect(db_path.as_uri() + '?mode=ro', uri=True) as db:
            wanted = ','.join('?' for _ in names)
            if wanted:
                query = ('SELECT caller, callee, file, line FROM call_site WHERE callee IN (' + wanted + ')')
                for caller, callee, file, line in db.execute(query, sorted(names)):
                    fn = by_key.get(caller + '@' + file)
                    if fn and not any(f.key == fn.key and kind == 'direct_call'
                                      for f, kind, _ in references[callee]):
                        references[callee].append((fn, 'direct_call_codemap', line))
    return by_key, by_name, references


def choose_reference(row: dict, refs: list[tuple[Function, str, int]]):
    file = row['file']
    # Prefer a local installer, then a local caller, then same-folder evidence.
    rank = {'callback_store': 0, 'draw_registration_alias': 1, 'draw_registration': 2,
            'assigned_reference': 3, 'direct_call': 4, 'direct_call_codemap': 4, 'dispatcher_table': 5}
    def order(ref):
        fn, reach, _ = ref
        locality = 0 if fn.file == file else (1 if Path(fn.file).parent == Path(file).parent else 2)
        alloc = 0 if ALLOC.search(fn.body) else 1
        return (rank[reach], alloc, locality, fn.file, fn.name)
    return sorted(refs, key=order)[0] if refs else None


def classify(row: dict, fn: Function | None, refs: list[tuple[Function, str, int]], by_name):
    chosen = choose_reference(row, refs)
    installer, reach, _ = chosen if chosen else (None, 'unresolved', 0)
    installed_reaches = {'callback_store', 'draw_registration_alias', 'draw_registration'}
    callback_installers = {f.key for f, k, _ in refs if k in installed_reaches}
    ambiguous = len(callback_installers) > 1
    # A draw callback is often shared. One creator with an allocated, typed body
    # is evidence; multiple registrants are an explicit ambiguity.
    creator = installer if installer and reach in installed_reaches and ALLOC.search(installer.body) and not ambiguous else None
    allocator = ALLOC.search(creator.body).group(1) if creator else ''
    base = row.get('base_expr') or row.get('leaf_expr') or ''
    base = base.strip()
    _, arg0 = first_param(fn.params) if fn else ('', '')
    body_arg = int(bool(arg0 and base == arg0))
    types = set()
    creator_types = set(body_types(creator).values()) if creator else set()
    if creator and fn and creator.key == fn.key and base in body_types(creator):
        types.add(body_types(creator)[base])
    if fn and creator and reach in installed_reaches:
        # Sibling callback signatures only describe arg0 of the installed callback.
        own_type, arg0 = first_param(fn.params)
        if base == arg0:
            types.update(creator_types)
            if own_type:
                types.add(own_type)
            siblings = set(CALLBACK_STORE.findall(creator.body))
            siblings.update(cb for _, cb in GENERIC_STORE.findall(creator.body))
            for sibling in siblings:
                for other in by_name.get(sibling, ()):
                    if other.file == fn.file or Path(other.file).parent == Path(fn.file).parent:
                        sibling_type, _ = first_param(other.params)
                        if sibling_type:
                            types.add(sibling_type)
    # A type conflict is an explicit hold, not a majority vote.
    typ = next(iter(types)) if len(types) == 1 else ''
    if creator and typ and typ in creator_types and reach in installed_reaches:
        confidence = 'installer+creator typed'
    elif installer and reach in installed_reaches | {'assigned_reference'}:
        confidence = 'installer only'
    else:
        confidence = 'none'
    if creator:
        family = creator.key
    elif installer and confidence != 'none':
        family = installer.key
    else:
        family = (fn.key if fn else row['function'] + '@' + row['file'])
    evidence = []
    if installer:
        evidence.append(reach + ':' + installer.key)
    if creator:
        evidence.append('alloc:' + allocator)
    if types:
        evidence.append('body_types:' + ','.join(sorted(types)))
    if len(refs) > 1:
        evidence.append('references:' + str(len(refs)))
    if ambiguous:
        evidence.append('ambiguous_installers:' + ','.join(sorted(callback_installers)))
    reach_paths = ';'.join(sorted({kind + ':' + f.key for f, kind, _ in refs}))
    creator_candidates = ','.join(sorted({f.key for f, kind, _ in refs
                                          if kind in installed_reaches and ALLOC.search(f.body)}))
    return dict(family=family, body_arg=body_arg, reach=reach, reach_paths=reach_paths,
                installer=installer.key if installer else '', creator=creator.key if creator else '',
                creator_candidates=creator_candidates, allocator=allocator, record_type=typ,
                confidence=confidence, evidence=';'.join(evidence))


def report(root: Path, inventory: Path, out: Path):
    rows = read_inventory(inventory)
    names = {r['function'] for r in rows if r.get('function')}
    by_key, by_name, references = source_index(root, names)
    sites = []
    for row in rows:
        fn = by_key.get(row['function'] + '@' + row['file'])
        refs = [(f, k, n) for f, k, n in references.get(row['function'], ()) if f.key != (fn.key if fn else '')]
        fields = classify(row, fn, refs, by_name)
        sites.append({k: row.get(k, '') for k in SITE_FIELDS if k in row} | fields)
    groups = defaultdict(list)
    for site in sites:
        groups[site['family']].append(site)
    families = []
    priority = {'installer+creator typed': 0, 'installer only': 1, 'none': 2}
    for family, entries in groups.items():
        best = min(entries, key=lambda e: priority[e['confidence']])
        families.append(dict(family=family, uses=len(entries),
                             body_uses=sum(int(e['body_arg']) for e in entries),
                             functions=len({e['function'] + '@' + e['file'] for e in entries}),
                             callbacks=','.join(sorted({e['function'] for e in entries})),
                             creator=best['creator'], allocator=best['allocator'],
                             record_type=best['record_type'], confidence=best['confidence'],
                             reach=','.join(sorted({e['reach'] for e in entries})),
                             evidence=';'.join(sorted({e['evidence'] for e in entries if e['evidence']})),
                             files=','.join(sorted({e['file'] for e in entries}))))
    families.sort(key=lambda e: (priority[e['confidence']], -e['body_uses'], -e['uses'], e['family']))
    out.mkdir(parents=True, exist_ok=True)
    for path, data, fields in ((out / 'provenance_sites.tsv', sites, SITE_FIELDS),
                               (out / 'provenance_families.tsv', families, FAMILY_FIELDS)):
        with path.open('w', newline='') as fh:
            writer = csv.DictWriter(fh, fieldnames=fields, delimiter='\t', extrasaction='ignore')
            writer.writeheader()
            writer.writerows(data)
    return Counter(s['confidence'] for s in sites), len(families)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--root', type=Path, default=Path(__file__).resolve().parents[2])
    parser.add_argument('--inventory', type=Path, required=True)
    parser.add_argument('--out', type=Path, required=True)
    args = parser.parse_args()
    counts, families = report(args.root, args.inventory, args.out)
    print(f'{sum(counts.values())} sites, {families} families: ' + ', '.join(f'{k}={v}' for k, v in sorted(counts.items())))


if __name__ == '__main__':
    main()
