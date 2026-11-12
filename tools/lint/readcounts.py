#!/usr/bin/env python3
"""Report-only readability and prototype-gap counts for `debt_check.py --summary`.

None of these counts is a ratchet or has a baseline; they say how far the tree is from one
canonical signature per function and from code a reader can follow:

  1. declared function names with more than one distinct normalised signature
     (decl_agreement's normalisation), and declaration sites per declared name;
  2. function names defined more than once, split into identical and differing bodies;
  3. address-named tokens (func_8xxxxxxx, D_8xxxxxxx) and unk_/pad_ member tokens;
  4. struct typedefs in .c files: exact-duplicate bodies, names with several bodies, and the local views
     with at most two non-pad members (casts spelled as structs: `{ u8 pad_00[0x2A]; u16 unk_2A; }`);
  5. duplicate #include lines, stale tool comments, placeholder identifiers (argN, var_, temp_).

Everything is lexical (comments and string contents never count) and cached per file by
content hash; the whole aggregate is cached again by the hash of every input, so an unchanged
tree costs one read-and-hash pass.  Per-item lists go to a directory outside the tracked tree.
"""
from __future__ import annotations

import bisect
import collections
import csv
import hashlib
import json
from pathlib import Path
import re

import decl_agreement as DA

TOP = 5
STR = re.compile(r'"(?:\\.|[^"\\\n])*"|\'(?:\\.|[^\'\\\n])*\'')
COMMENT_OR_STRING = re.compile(r'/\*.*?\*/|//[^\n]*|"(?:\\.|[^"\\\n])*"|\'(?:\\.|[^\'\\\n])*\'', re.S)
CALLISH = re.compile(r'\b([A-Za-z_]\w*)\s*\(')
BRACE = re.compile(r'[{}]')
NOT_FUNCTIONS = frozenset('if while for switch return sizeof defined typeof __typeof__ __attribute__ '
                          'else do case default goto typedef void int char short long unsigned signed '
                          'float double _Alignof __alignof__ asm __asm__'.split())
INCLUDE = re.compile(r'^[ \t]*#[ \t]*include[ \t]*([<"][^>"\n]+[>"])', re.M)
TOKENS = re.compile(r'\b(?:(func_8[0-9A-Fa-f]{7})|(D_8[0-9A-Fa-f]{7})|(unk_\w*)|(pad_\w*)'
                    r'|(arg\d+)|(var_\w+)|(temp_\w+))\b')
TYPEDEF_STRUCT = re.compile(r'\btypedef\s+struct\b\s*(?:[A-Za-z_]\w*\s*)?\{')
KNR_TAIL = re.compile(r'(?:[A-Za-z_][^;{}()]*;\s*)+\{')
ALIAS_AFTER = re.compile(r'\s*([A-Za-z_]\w*)\s*;')
# Tool and lane stamps left in comments: (tag, pattern).  A comment counts once per tag.
TOOL_TAGS = (
    ('cfail-repair/tf7-phase', re.compile(r'cfail-repair|tf7-phase')),
    ('evidence banner', re.compile(r'Original-file evidence|inferred-(?:strong|weak)\b|Evidence: inferred')),
    ('tool-written header note', re.compile(r'\btools/(?:headers|gen_records|gen_noreturn_syms)\b|Provenance:')),
    # CL:, PD:, PR:, J1: and XB: label evidence kinds in decision-72(b) evidence lists (tools/tu/tu_merge.py writes
    # them); they are part of the evidence banner, not group ids.
    ('cohort/group id', re.compile(r'\bG\d{5}\b')),
    ('lane receipt/ledger', re.compile(r'\blane receipt\b|\breceipt\b|\bledger/')),
    ('review pending', re.compile(r'Review pending')),
    ('MECHANISM note', re.compile(r'\bMECHANISM:')),
)
PLACEHOLDERS = ('arg', 'var_', 'temp_')
PAD_MEMBER = re.compile(r'_?(?:pad|reserved)', re.I)
SMALL_VIEW = 2          # non-pad members at most
CACHE_SUBDIR = 'readcounts'


def _hash(text):
    return hashlib.sha256(text.encode('utf-8', 'surrogateescape')).hexdigest()


def _squash(text):
    return ' '.join(text.split())


def _brace_end(clean, start):
    """Index just past the '}' matching the '{' at clean[start], or len(clean)."""
    depth = 0
    for m in BRACE.finditer(clean, start):
        depth += 1 if m[0] == '{' else -1
        if depth == 0:
            return m.end()
    return len(clean)


def split_text(text):
    """(comments [(pos, text)], text without comments, text without comments or string contents)."""
    comments, parts, last = [], [], 0
    for m in COMMENT_OR_STRING.finditer(text):
        if m[0][0] in '"\'':
            continue
        comments.append((m.start(), m[0]))
        parts.append(text[last:m.start()])
        parts.append('\n' * m[0].count('\n') or ' ')
        last = m.end()
    parts.append(text[last:])
    nocomment = ''.join(parts)
    return comments, nocomment, STR.sub(lambda m: m[0][0] + m[0][-1], nocomment)


def scan_declarations(clean):
    """[name, line, kind, head, params, static, body hash or ''] for every declaration or definition.

    Same acceptance rule as decl_agreement.declarations (head of type words only, `;` or `{`
    after the parameter list) but for every name; K&R definitions are recorded without a
    parameter list.  Bodies are not scanned for further declarations."""
    code = '\n'.join(' ' * len(l) if l.lstrip().startswith('#') else l
                     for l in clean.replace('\\\n', ' \n').split('\n'))
    newlines = None
    found, pos = [], 0
    while True:
        m = CALLISH.search(code, pos)
        if m is None:
            break
        pos = m.end()
        name = m[1]
        if name in NOT_FUNCTIONS:
            continue
        begin = max(code.rfind(c, 0, m.start()) for c in ';{}')
        head = code[begin + 1:m.start()].strip()
        if not head:
            continue
        words = DA.TOKEN.findall(head)
        if (any(w in DA.KEYWORD_HEADS for w in words) or any(c in head for c in '=(:,?!+-/&|')
                or not any(re.match(r'[A-Za-z_]', w) and w not in DA.STORAGE for w in words)):
            continue
        open_paren = m.end() - 1
        close = DA.find_matching(code, open_paren)
        if close < 0:
            continue
        tail = code[close + 1:close + 200].lstrip()
        tail = re.sub(r'^(?:__attribute__\s*\(\(.*?\)\)\s*)+', '', tail)
        if not tail:
            continue
        params = _squash(code[open_paren + 1:close])
        body = ''
        if tail[0] == '{' or (tail[0] not in ';' and KNR_TAIL.match(code, close + 1, close + 600)):
            if tail[0] == '{':
                brace = code.index('{', close)
            else:
                brace = KNR_TAIL.match(code, close + 1, close + 600).end() - 1
                params = None
            end = _brace_end(code, brace)
            body = hashlib.sha1(_squash(head + ' ' + code[close:end]).encode()).hexdigest()[:16]
            pos = max(pos, end)
            kind = 'def'
        elif tail[0] == ';':
            kind = 'decl'
        else:
            continue
        if newlines is None:
            newlines = [i for i, ch in enumerate(code) if ch == '\n']
        line = bisect.bisect_left(newlines, m.start()) + 1
        found.append([name, line, kind, _squash(head), params, 'static' in words, body])
    return found


def _top_split(text, sep):
    """text split at `sep` outside (), [] and {}."""
    parts, depth, last = [], 0, 0
    for i, ch in enumerate(text):
        if ch in '([{':
            depth += 1
        elif ch in ')]}':
            depth -= 1
        elif ch == sep and depth == 0:
            parts.append(text[last:i])
            last = i + 1
    parts.append(text[last:])
    return parts


def member_names(body):
    """Top-level member names of a struct body (comments removed); an anonymous struct/union member is ''
    (it names fields), an unnamed bit-field None (padding)."""
    names = []
    for statement in _top_split(body, ';'):
        statement = statement.strip()
        if not statement or statement.startswith('#'):
            continue
        aggregate = '{' in statement
        for k, decl in enumerate(_top_split(statement, ',')):
            pointer = re.search(r'\(\s*\*+\s*([A-Za-z_]\w*)', decl)
            if pointer:
                names.append(pointer[1])
                continue
            if k == 0 and aggregate:
                head, _, after = decl.rpartition('}')
                ids = re.findall(r'[A-Za-z_]\w*', re.sub(r'\[[^\]]*\]', ' ', after).split(':')[0])
                if ids:
                    names.append(ids[-1])
                else:
                    # `union { ... };` is an anonymous member (its fields are named inside);
                    # `struct Tag { ... };` only declares a nested type
                    tag = re.findall(r'[A-Za-z_]\w*', head.split('{', 1)[0])
                    names.append('' if tag in (['struct'], ['union']) else None)
                continue
            flat = re.sub(r'\[[^\]]*\]', ' ', decl).split(':')[0]
            ids = re.findall(r'[A-Za-z_]\w*', flat)
            if k == 0 and len(ids) <= 1:
                names.append(None)          # unnamed bit-field
            else:
                names.append(ids[-1] if ids else None)
    return names


def non_pad_members(body):
    return sum(1 for n in member_names(body) if n is not None and not PAD_MEMBER.match(n))


def struct_typedefs(clean):
    """[alias, body hash, line, non-pad members] for `typedef struct [tag] { ... } alias;`."""
    out = []
    for m in TYPEDEF_STRUCT.finditer(clean):
        opening = m.end() - 1
        end = _brace_end(clean, opening)
        alias = ALIAS_AFTER.match(clean, end)
        if alias:
            body = clean[opening + 1:end - 1]
            out.append([alias[1], hashlib.sha1(_squash(body).encode()).hexdigest()[:16],
                        clean.count('\n', 0, m.start()) + 1, non_pad_members(body)])
    return out


def file_facts(text, is_c):
    comments, nocomment, clean = split_text(text)
    counts = collections.Counter()
    names = {1: collections.Counter(), 2: collections.Counter()}
    for m in TOKENS.finditer(clean):
        group = m.lastindex
        counts[group] += 1
        if group in names:
            names[group][m[0]] += 1
    placeholders = {PLACEHOLDERS[g - 5]: counts[g] for g in (5, 6, 7) if counts[g]}
    seen = collections.Counter(INCLUDE.findall(nocomment))
    tags, in_comments = [], collections.Counter()
    for pos, body in comments:
        for m in TOKENS.finditer(body):
            in_comments[m.lastindex] += 1
        hit = [tag for tag, pattern in TOOL_TAGS if pattern.search(body)]
        if hit:
            tags.append([text.count('\n', 0, pos) + 1, hit])
    return dict(decls=scan_declarations(clean),
                func=dict(names[1]), data=dict(names[2]), unk=counts[3], pad=counts[4],
                placeholders=placeholders,
                comment_tokens=dict(func=in_comments[1], data=in_comments[2],
                                    placeholders=sum(in_comments[g] for g in (5, 6, 7))),
                structs=struct_typedefs(clean) if is_c else [],
                include_dups=sorted([name, n - 1] for name, n in seen.items() if n > 1),
                tags=tags)



def source_paths(root):
    root = Path(root)
    out = []
    for top, suffixes in (('src', ('.c', '.h')), ('include', ('.h',))):
        base = root / top
        if base.is_dir():
            out += sorted(p for p in base.rglob('*') if p.suffix in suffixes and p.is_file())
    return out


def tool_hash():
    h = hashlib.sha256()
    for path in (Path(__file__), Path(DA.__file__)):
        h.update(path.read_bytes())
    return h.hexdigest()


def collect(root):
    """({rel: facts}, aggregate key).  Per-file facts are cached by content hash."""
    root = Path(root)
    tool = tool_hash()
    facts, keys = {}, hashlib.sha256(tool.encode())
    pending = {}
    for path in source_paths(root):
        rel = path.relative_to(root).as_posix()
        if path.is_symlink() or path.stat().st_size > 4 * 1024 * 1024:
            raise ValueError('unsupported symlink or file over 4 MiB: ' + rel)
        text = path.read_text(errors='replace')
        key = hashlib.sha256(tool.encode() + text.encode('utf-8', 'surrogateescape')).hexdigest()
        keys.update(rel.encode())
        keys.update(key.encode())
        pending[rel] = (key, text)
    return pending, keys.hexdigest(), tool


def file_result(rel, key, text, cache_dir, cache_value):
    def calculate():
        return file_facts(text, rel.endswith('.c'))
    if cache_dir is None:
        return calculate()
    return cache_value(cache_dir / CACHE_SUBDIR, rel, key, calculate)


# ------------------------------------------------------------------ aggregation

def _normalised(aliases):
    memo = {}

    def signature(head, params):
        key = (head, params)
        if key not in memo:
            inner = None if params is None else DA.normalize_params(params, aliases)
            memo[key] = (DA.normalize_type(head, aliases), None if inner is None else tuple(inner))
        return memo[key]
    return signature


def _show(sig):
    ret, params = sig
    return ret + ' (' + ('?' if params is None else ', '.join(params) or 'void') + ')'


def aggregate(per_file, aliases):
    """The report dict (counts plus the item lists) for {rel: facts}."""
    signature = _normalised(aliases)
    sites = collections.defaultdict(list)            # name -> [(rel, line, kind, sig)]
    defs = collections.defaultdict(list)             # name -> [(rel, line, body, static)]
    func, data = collections.Counter(), collections.Counter()
    func_files, data_files = collections.defaultdict(set), collections.defaultdict(set)
    unk = pad = 0
    unk_files, pad_files = {}, {}
    placeholders = collections.Counter()
    placeholder_files = collections.defaultdict(collections.Counter)
    structs = []
    include_dups = []
    tags = collections.Counter()
    tag_sites = []
    tag_comments = 0
    comment_tokens = collections.Counter()
    for rel, f in sorted(per_file.items()):
        for name, line, kind, head, params, static, body in f['decls']:
            if static:
                continue
            sites[name].append((rel, line, kind, signature(head, params)))
            if kind == 'def':
                defs[name].append((rel, line, body))
        func.update(f['func'])
        data.update(f['data'])
        for name in f['func']:
            func_files[name].add(rel)
        for name in f['data']:
            data_files[name].add(rel)
        comment_tokens.update(f['comment_tokens'])
        unk += f['unk']
        pad += f['pad']
        if f['unk']:
            unk_files[rel] = f['unk']
        if f['pad']:
            pad_files[rel] = f['pad']
        for kind, n in f['placeholders'].items():
            placeholders[kind] += n
            placeholder_files[rel][kind] += n
        structs += [(alias, body, rel, line, fields) for alias, body, line, fields in f['structs']]
        include_dups += [(rel, name, n) for name, n in f['include_dups']]
        for line, hit in f['tags']:
            tag_comments += 1
            tag_sites.append((rel, line, hit))
            tags.update(hit)

    # 1. signatures
    total_sites = sum(len(v) for v in sites.values())
    multi_site = [name for name, v in sites.items() if len(v) > 1]
    conflicts, incompatible = [], 0
    for name, v in sorted(sites.items()):
        sigs = collections.Counter(s for _, _, _, s in v if s[1] is not None)
        if len(sigs) > 1:
            items = list(sigs)
            hard = any(not DA.agrees((name, 0, '', a[0], list(a[1]), False), (name, 0, '', b[0], list(b[1]), False))
                       for i, a in enumerate(items) for b in items[i + 1:])
            incompatible += hard
            conflicts.append(dict(name=name, sites=len(v), signatures=len(sigs), incompatible=hard,
                                  forms=[(_show(s), n) for s, n in sigs.most_common()]))
    conflicts.sort(key=lambda r: (-r['sites'], r['name']))
    top_names = sorted(((len(v), name) for name, v in sites.items()), key=lambda t: (-t[0], t[1]))[:TOP]

    # 2. definitions
    dup_defs = []
    identical = differing = 0
    for name, v in sorted(defs.items()):
        if len(v) < 2:
            continue
        bodies = {b for _, _, b in v}
        same = len(bodies) == 1
        identical += same
        differing += not same
        dup_defs.append(dict(name=name, definitions=len(v), distinct_bodies=len(bodies),
                             files=[f'{r}:{l}' for r, l, _ in v]))
    dup_defs.sort(key=lambda r: (r['distinct_bodies'] == 1, -r['definitions'], r['name']))

    # 4. struct typedefs
    by_body = collections.defaultdict(list)
    by_name = collections.defaultdict(set)
    fields_of = {}
    for alias, body, rel, line, fields in structs:
        by_body[body].append((alias, rel, line))
        by_name[alias].add(body)
        fields_of[body] = fields
    dup_bodies = {b: v for b, v in by_body.items() if len(v) > 1}
    several = {n: bs for n, bs in by_name.items() if len(bs) > 1}
    small = collections.Counter(fields for *_, fields in structs if fields <= SMALL_VIEW)
    small_dups = {b: v for b, v in dup_bodies.items() if fields_of[b] <= SMALL_VIEW}

    return dict(
        signatures=dict(
            declared_names=len(sites), sites=total_sites,
            mean_sites=round(total_sites / max(1, len(sites)), 2),
            names_in_several_sites=len(multi_site),
            names_multi_signature=len(conflicts), sites_of_those=sum(r['sites'] for r in conflicts),
            names_incompatible=incompatible,
            top=[[name, n] for n, name in top_names]),
        definitions=dict(names=len(defs), multiple=len(dup_defs), definitions=sum(r['definitions'] for r in dup_defs),
                         identical=identical, differing=differing),
        addresses=dict(func_tokens=sum(func.values()), func_distinct=len(func),
                       data_tokens=sum(data.values()), data_distinct=len(data),
                       unk=unk, pad=pad, func_in_comments=comment_tokens['func'],
                       data_in_comments=comment_tokens['data']),
        structs=dict(total=len(structs), duplicate_copies=sum(len(v) for v in dup_bodies.values()),
                     duplicate_bodies=len(dup_bodies), names_with_several_bodies=len(several),
                     bodies_of_those=sum(len(v) for v in several.values()),
                     small_views=sum(small.values()), small_by_fields={str(k): small[k] for k in sorted(small)},
                     small_duplicate_copies=sum(len(v) for v in small_dups.values()),
                     small_duplicate_bodies=len(small_dups)),
        hygiene=dict(include_dups=sum(n for _, _, n in include_dups),
                     include_dup_files=len({r for r, _, _ in include_dups}),
                     tag_comments=tag_comments, tags=dict(tags),
                     placeholders=dict(placeholders, total=sum(placeholders.values()),
                                           in_comments=comment_tokens['placeholders'])),
        lists=dict(
            conflicts=conflicts, dup_defs=dup_defs,
            func=sorted(((n, c, len(func_files[n])) for n, c in func.items()), key=lambda t: (-t[1], t[0])),
            data=sorted(((n, c, len(data_files[n])) for n, c in data.items()), key=lambda t: (-t[1], t[0])),
            unk=sorted(unk_files.items(), key=lambda t: (-t[1], t[0])),
            pad=sorted(pad_files.items(), key=lambda t: (-t[1], t[0])),
            struct_dups=sorted(([len(v), body, [f'{a}@{r}:{l}' for a, r, l in v]] for body, v in dup_bodies.items()),
                               key=lambda t: (-t[0], t[1])),
            struct_names=sorted(([name, len(bs)] for name, bs in several.items()), key=lambda t: (-t[1], t[0])),
            include_dups=sorted(include_dups, key=lambda t: (-t[2], t[0], t[1])),
            tag_sites=tag_sites,
            placeholder_files=sorted(([rel, sum(c.values()), dict(c)] for rel, c in placeholder_files.items()),
                                     key=lambda t: (-t[1], t[0]))))


def report(root, cache_dir, cache_value):
    """Aggregate report for the tree under root; the whole aggregate is cached by input hash."""
    pending, key, tool = collect(root)
    def calculate():
        per_file = {rel: file_result(rel, k, text, cache_dir, cache_value) for rel, (k, text) in pending.items()}
        return aggregate(per_file, DA.scalar_aliases(root))
    if cache_dir is None:
        return calculate()
    return cache_value(cache_dir / CACHE_SUBDIR / 'total', 'aggregate', key, calculate)


def summary_lines(rep):
    s, d, a, t, h = (rep[k] for k in ('signatures', 'definitions', 'addresses', 'structs', 'hygiene'))
    top = ', '.join(f'{n} {c}' for n, c in s['top'])
    tags = ', '.join(f'{k} {v}' for k, v in sorted(h['tags'].items(), key=lambda kv: (-kv[1], kv[0])))
    ph = h['placeholders']
    return [
        f'prototype names multi-signature (report only)\t{s["names_multi_signature"]}\t{s["sites_of_those"]} sites'
        f'\t{s["names_incompatible"]} incompatible beyond () and void *',
        f'declaration sites per declared name (report only)\t{s["mean_sites"]} mean\t{s["sites"]} sites'
        f' / {s["declared_names"]} names\t{s["names_in_several_sites"]} names in several sites\ttop {top}',
        f'duplicate function definitions (report only)\t{d["multiple"]} names\t{d["definitions"]} definitions'
        f'\t{d["identical"]} identical bodies\t{d["differing"]} differing bodies',
        f'address-named tokens (report only)\tfunc_8 {a["func_tokens"]} ({a["func_distinct"]} distinct)'
        f'\tD_8 {a["data_tokens"]} ({a["data_distinct"]} distinct)'
        f'\tin comments: func_8 {a["func_in_comments"]} D_8 {a["data_in_comments"]}',
        f'unk_/pad_ member tokens (report only)\tunk_ {a["unk"]}\tpad_ {a["pad"]}',
        f'struct typedefs in .c files (report only)\t{t["total"]}\t{t["duplicate_copies"]} copies of '
        f'{t["duplicate_bodies"]} exact-duplicate bodies\t{t["names_with_several_bodies"]} names with several bodies',
        f'local views with <={SMALL_VIEW} non-pad fields (report only)\t{t["small_views"]}\t'
        + ', '.join(f'{k} fields {v}' for k, v in sorted(t['small_by_fields'].items()))
        + f'\t{t["small_duplicate_copies"]} copies of {t["small_duplicate_bodies"]} exact-duplicate bodies',
        f'duplicate #include lines (report only)\t{h["include_dups"]}\t{h["include_dup_files"]} files',
        f'stale tool comments (report only)\t{h["tag_comments"]}\t{tags}',
        f'placeholder identifiers (report only)\t{ph["total"]}\targN {ph.get("arg", 0)}'
        f'\tvar_ {ph.get("var_", 0)}\ttemp_ {ph.get("temp_", 0)}\tnamed in comments {ph["in_comments"]}',
    ]


def write_lists(out, rep):
    """Per-item lists for later lanes to pick work from; never part of the tracked tree."""
    out = Path(out)
    out.mkdir(parents=True, exist_ok=True)
    (out / '.ignore').write_text('*\n')
    L = rep['lists']

    def tsv(name, header, rows):
        with (out / name).open('w', newline='') as stream:
            writer = csv.writer(stream, delimiter='\t', lineterminator='\n')
            writer.writerow(header)
            writer.writerows(rows)

    tsv('signature_conflicts.tsv', ['name', 'sites', 'signatures', 'incompatible', 'forms'],
        [[r['name'], r['sites'], r['signatures'], int(r['incompatible']),
          ' | '.join(f'{form} x{n}' for form, n in r['forms'])] for r in L['conflicts']])
    tsv('duplicate_definitions.tsv', ['name', 'definitions', 'distinct_bodies', 'sites'],
        [[r['name'], r['definitions'], r['distinct_bodies'], ' '.join(r['files'])] for r in L['dup_defs']])
    tsv('address_func_tokens.tsv', ['name', 'tokens', 'files'], L['func'])
    tsv('address_data_tokens.tsv', ['name', 'tokens', 'files'], L['data'])
    tsv('unk_tokens_by_file.tsv', ['file', 'tokens'], L['unk'])
    tsv('pad_tokens_by_file.tsv', ['file', 'tokens'], L['pad'])
    tsv('struct_duplicate_bodies.tsv', ['copies', 'body', 'sites'], [[n, b, ' '.join(v)] for n, b, v in L['struct_dups']])
    tsv('struct_names_with_several_bodies.tsv', ['name', 'bodies'], L['struct_names'])
    tsv('duplicate_includes.tsv', ['file', 'include', 'extra_copies'], L['include_dups'])
    tsv('stale_tool_comments.tsv', ['file', 'line', 'tags'], [[r, l, ','.join(h)] for r, l, h in L['tag_sites']])
    tsv('placeholder_identifiers_by_file.tsv', ['file', 'tokens', 'by_kind'],
        [[r, n, json.dumps(c, sort_keys=True)] for r, n, c in L['placeholder_files']])
    summary = {k: v for k, v in rep.items() if k != 'lists'}
    (out / 'summary.json').write_text(json.dumps(summary, indent=2, sort_keys=True) + '\n')
