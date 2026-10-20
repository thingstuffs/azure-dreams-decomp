#!/usr/bin/env python3
"""Plan exact source-range family folds from a census and Clang's typed AST.

Clang dumps remain in memory. This module only plans edits; callers must prove
complete physical TU identity before retaining them. Parameters with external
prototypes keep their declarations and use explicit shared-type casts.
"""
from __future__ import annotations

import collections
import re
import sys
from pathlib import Path

HERE = Path(__file__).resolve().parent
sys.path[:0] = [str(HERE), str(HERE.parent)]
import field_census as C
import retype_family as R


def base_expression(expr):
    """Find the pointer expression, without crossing a pointer load."""
    e = C.strip(expr)
    while e and e.get('kind') == 'MemberExpr':
        if e.get('isArrow'):
            e = C.strip(e['inner'][0])
            break
        e = C.strip(e['inner'][0])
    if e and e.get('kind') == 'UnaryOperator' and e.get('opcode') == '*':
        e = C.strip(e['inner'][0])
    if e and e.get('kind') == 'ArraySubscriptExpr':
        e = C.strip(e['inner'][0])
        # An embedded array is part of the containing object. A pointer field
        # instead loads a separate object's base and must remain a boundary.
        if e and e.get('kind') == 'MemberExpr' and '[' in C.qtype(e):
            while e and e.get('kind') == 'MemberExpr':
                arrow = e.get('isArrow')
                e = C.strip(e['inner'][0])
                if arrow:
                    break
    if e and e.get('kind') == 'BinaryOperator' and e.get('opcode') in ('+', '-'):
        a, b = e['inner']
        e = C.strip(a if C.int_value(b) is not None else b)
    return e


def access_base(expr):
    e = base_expression(expr)
    if e and e.get('kind') == 'DeclRefExpr':
        d = e['referencedDecl']
        if d.get('kind') in ('VarDecl', 'ParmVarDecl'):
            return d['name'], d.get('type', {}).get('qualType', ''), d['kind']
    return None


def expression_range(expr, text):
    rng = expr.get('range', {})
    a, b = rng.get('begin', {}), rng.get('end', {})
    macro = 'expansionLoc' in a
    a, b = a.get('expansionLoc', a), b.get('expansionLoc', b)
    if 'offset' not in a or 'offset' not in b:
        return None
    start, end = a['offset'], b['offset'] + b.get('tokLen', 1)
    # Clang ranges count UTF-8 bytes; Python source slices count characters.
    if not text.isascii():
        encoded = text.encode()
        start = len(encoded[:start].decode())
        end = len(encoded[:end].decode())
    if macro:
        m = re.match(r'[A-Za-z_]\w*\s*\(', text[start:])
        if not m:
            return None
        close = R.match_close(text, start + m.end() - 1)
        if close < 0:
            return None
        end = close + 1
    return start, end


def key(site):
    return tuple(site.get(k) for k in ('func', 'line', 'spell', 'base', 'field', 'width', 'sign', 'rw'))


def plan_file(root, file, sites, family):
    """Return independent per-variable plans, or explicit static refusals."""
    text = (Path(root) / file).read_text()
    if re.search(r'(?i)relink(?:ed)? (?:of|copy)|r121_nodonor relink|LL4', text[:1500]) or 'NON_MATCHING' in text:
        return {'file': file, 'plans': [], 'refused': [{'var': '*', 'reason': 'relink_or_non_matching'}]}
    old_site = C.FunctionFacts.site

    def record(self, expr, rw, const=None):
        n = len(self.sites)
        old_site(self, expr, rw, const)
        if len(self.sites) != n:
            self.sites[-1]['source_range'] = expression_range(expr, self.src)
            self.sites[-1]['variable'] = access_base(expr)
            if self.sites[-1]['variable'] is None:
                base = base_expression(expr)
                rng = expression_range(base, self.src) if base else None
                load = base and (base.get('kind') in ('MemberExpr', 'ArraySubscriptExpr') or
                                 base.get('kind') == 'UnaryOperator' and base.get('opcode') == '*')
                if rng and load:
                    a, b = rng
                    self.sites[-1]['variable'] = (self.src[a:b], '<expression>', 'Expression')

    C.FunctionFacts.site = record
    try:
        facts = C.extract_tu((str(root), file))
    finally:
        C.FunctionFacts.site = old_site
    if facts.get('error'):
        return {'file': file, 'plans': [], 'refused': [{'var': '*', 'reason': 'clang_parse_error:' + facts['error']}]}
    reference = {key(s): s for s in sites}
    by_var = collections.defaultdict(list)
    all_accesses = collections.defaultdict(list)
    for fn in facts['functions']:
        if str(Path(fn['file'])) != file:
            continue
        for s in fn['sites']:
            var = s.get('variable')
            if not var:
                continue
            k = fn['func'], var[0]
            all_accesses[k].append(s)
            census = reference.get(key(s))
            if census and census.get('label') in family['labels']:
                by_var[k].append((s, census))
    result = {'file': file, 'plans': [], 'refused': []}
    for (func, var), accesses in by_var.items():
        replacements, why, counts = [], None, collections.Counter()
        preserved_ranges = []
        for s, census in accesses:
            off, width = census['off'], census['width']
            if s.get('delta') != off:
                why = 'base_offset_not_zero'
                break
            field_key = '%#x:%d' % (off, width)
            field = family['fields'].get(field_key)
            if field_key in family.get('preserve_accesses', []):
                # Exact short aggregate copies retain their original copy type.
                # Other accesses can fold, but their local view must survive.
                if s.get('source_range'):
                    a, b = s['source_range']
                    # An explicit copy cast already preserves its own extent
                    # independently of the local pointer's declaration.
                    if not re.match(r'\*\s*\(\s*[A-Za-z_]\w*\s*\*\s*\)', text[a:b]):
                        preserved_ranges.append((a, b))
                continue
            reinterpret = family.get('reinterpret_fields', {}).get(field_key)
            aggregate = off == 0 and width == family.get('aggregate_size')
            if reinterpret:
                field = reinterpret + ':' + census['sign']
            if aggregate:
                field = '*:record'
            if not field:
                why = 'unmapped_field:%#x:%d' % (off, width)
                break
            if not s.get('source_range'):
                why = 'source_range_unavailable'
                break
            a, b = s['source_range']
            path, sign = field.split(':')
            # Keep pointer representation on loads. Pointer/integer stores have
            # the same word width, while table indexing needs its original type.
            rep = '((%s *)%s)->%s' % (family['type'], var, path)
            if aggregate:
                rep = '*(%s *)%s' % (family['type'], var)
            elif reinterpret:
                rep = '*(%s *)&%s' % (R.CTYPE[(census['sign'], width)], rep)
            elif census['rw'] in ('r', 'rw', 'addr'):
                if census['sign'] in ('s', 'u') and census['sign'] != sign:
                    rep = '*(%s *)&%s' % (R.CTYPE[(census['sign'], width)], rep)
                elif census['sign'] == 'p' and sign == 'p' and R.norm(census['ctype']) != 'void*':
                    rep = '*(%s *)&%s' % (census['ctype'], rep)
            if text[a:b] != rep:
                replacements.append((a, b, R.access_spelling(rep, text[b:])))
                counts['S2' if census['spell'] in ('raw_cast', 'raw_index', 'macro', 'F_macro') else 'S4'] += 1
        # Every direct access through this base must have a family identity.
        # A pointee reached through a pointer field is a different object.
        mapped = {key(s) for s, _ in accesses}
        for s in all_accesses[(func, var)]:
            if key(s) not in mapped and not s.get('chain'):
                why = why or 'non_family_access'
        if why:
            result['refused'].append({'func': func, 'var': var, 'reason': why, 'sites': len(accesses)})
            continue
        if not replacements:
            continue
        preserved_access = any(not any(a <= x and y <= b for a, b, _ in replacements)
                               for x, y in preserved_ranges)
        replacements.sort()
        if any(a[1] > b[0] for a, b in zip(replacements, replacements[1:])):
            result['refused'].append({'func': func, 'var': var, 'reason': 'overlapping_accesses', 'sites': len(accesses)})
            continue
        # Retype simple locals. Leave explicit casts on parameters until their
        # declaration closure and caller agreement can be edited together.
        span = R.func_span(text, func)
        decl_type, decl_kind = accesses[0][0]['variable'][1:]
        local_typed = False
        if span and decl_kind == 'VarDecl':
            body = text[span[0]:span[1]]
            pat = re.compile(r'(?m)^(\s*(?:register\s+)?)([A-Za-z_]\w*(?:\s+[A-Za-z_]\w*)*\s*\*)\s*' + re.escape(var) + r'\s*;')
            declarations = list(pat.finditer(body))
            decl = declarations[0] if len(declarations) == 1 else None
            # Pointer arithmetic requires a separate proof of its byte stride.
            bare = re.sub(r'\([^()]*\*\)\s*' + re.escape(var) + r'\b', 'CAST_BASE', body)
            arithmetic = re.search(r'\b' + re.escape(var) + r'\s*(?:\[|\+\+|--|\+(?!>)|-(?!>))', bare)
            if decl:
                bare = bare.replace(decl.group(0), '', 1)
            arithmetic = arithmetic or re.search(r'\*\s*' + re.escape(var) + r'\b', bare)
            if decl and not arithmetic and not preserved_access and R.norm(decl_type) != family['type'] + '*':
                a = span[0] + decl.start(2)
                b = span[0] + decl.end(2)
                replacements.append((a, b, family['type'] + ' *'))
                local_typed = True
        if local_typed or R.norm(decl_type) == family['type'] + '*':
            replacements = [(a, b, rep.replace('((%s *)%s)->' % (family['type'], var), var + '->')) for a, b, rep in replacements]
        # Existing shared member spellings are already recovered. Do not claim
        # parenthesizing them as a field rewrite.
        kept = []
        for a, b, rep in replacements:
            if R.norm(text[a:b]) == R.norm(R.strip_parens(rep)):
                continue
            kept.append((a, b, rep))
        replacements = kept
        if not replacements:
            continue
        retained_ranges = {(a, b) for a, b, _ in replacements}
        counts = collections.Counter('S2' if c['spell'] in ('raw_cast', 'raw_index', 'macro', 'F_macro') else 'S4' for s, c in accesses if s['source_range'] and tuple(s['source_range']) in retained_ranges)
        result['plans'].append({'func': func, 'var': var, 'edits': replacements,
                                'sites': dict(counts), 'local_typed': local_typed,
                                'parameter': decl_kind == 'ParmVarDecl'})
    result['family_sites'] = sum(len(v) for v in by_var.values())
    return result


def apply(text, plans, header):
    edits = sorted((e for p in plans for e in p['edits']), reverse=True)
    for a, b, rep in edits:
        text = text[:a] + rep + text[b:]
    if edits:
        text = remove_unused_views(text)
    return R.ensure_include(text, header) if edits else text


def remove_unused_views(text):
    """Drop only local address views whose name has no remaining use."""
    pattern = re.compile(r'typedef\s+struct\s+([A-Za-z_]\w*)\s*\{')
    for match in reversed(list(pattern.finditer(text))):
        name = match.group(1)
        if not re.search(r'(?:^|_)S_(?:[0-9A-Fa-f]{8}|func_)', name):
            continue
        opened = match.end() - 1
        depth = 0
        end = None
        for pos in range(opened, len(text)):
            depth += text[pos] == '{'
            depth -= text[pos] == '}'
            if depth == 0:
                tail = re.match(r'\s*' + re.escape(name) + r'\s*;[ \t]*(?:(?:/\*.*?\*/|//[^\n]*)[ \t]*)?\n?', text[pos + 1:], re.S)
                if tail:
                    end = pos + 1 + tail.end()
                break
        if end is None:
            continue
        outside = text[:match.start()] + text[end:]
        if not re.search(r'\b' + re.escape(name) + r'\b', outside):
            text = outside
    return re.sub(r'\n(?:[ \t]*\n){2,}', '\n\n', text)
