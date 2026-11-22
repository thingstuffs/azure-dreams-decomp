#!/usr/bin/env python3
"""Plan and prove conservative cast removals in one allowed folder.

The census is only a candidate index. Every edit is derived from fresh MIPS
Clang facts, source hashes and debt-matcher locations. --discover-all scans
all cast-bearing files instead of the four census candidate categories.
Complete folder batch/native/debt proof remains mandatory after this tool.
"""
from __future__ import annotations

import argparse
from collections import Counter, defaultdict
from concurrent.futures import ProcessPoolExecutor
import csv
import gzip
import hashlib
import json
from pathlib import Path
import re
import subprocess
import sys

HERE = Path(__file__).resolve().parent
ROOT = HERE.parents[2]
sys.path[:0] = [str(HERE), str(ROOT / 'tools'), str(ROOT / 'tools/typing'), str(ROOT / 'tools/lint')]
import census
import cast_ast as A
import cast_census as CC
import cast_fold as F
import field_census as C
import debt_check as D
import layout_compile_identity as L


def setup_root(root):
    global ROOT
    ROOT = Path(root).resolve()
    census.setup(ROOT)


setup_root(ROOT)

ROUTES = ('redundant', 'node_body', 'numeric_member', 'qualified_argument')
# address_member is opt-in (--route address_member): it never runs in a default plan.
OPT_IN_ROUTES = ('address_member',)
ALL_ROUTES = ROUTES + OPT_IN_ROUTES
# Overlap precedence: the address rewrite replaces a whole expression, so it wins over a prefix-cast removal.
ROUTE_ORDER = OPT_IN_ROUTES + ROUTES
CATEGORIES = {'redundant', 'node_body', 'union_pun', 'call_arg'}
HASH_KEYS = ('raw_sha256', 'canonical_assembly_sha256', 'canonical_object_sha256', 'variant_raw_sha256')


def digest(text):
    return hashlib.sha256(text.encode()).hexdigest()


def write_edits(path, rows):
    # Quoted TSV preserves tabs in source spans for exact guarded replay.
    fields=['file','function','line','route','start','end','old','new','casts','reason','source_sha256','tu']
    with path.open('w',newline='') as output:
        writer=csv.DictWriter(output,fields,delimiter='\t',lineterminator='\n')
        writer.writeheader();writer.writerows(rows)


def context(parents, node, declaration, unit):
    top, holder = node, parents.get(id(node))
    while holder and holder.get('kind') in ('ParenExpr', 'ImplicitCastExpr'):
        top, holder = holder, parents.get(id(holder))
    dest = ''
    if holder:
        kind = holder.get('kind')
        if kind == 'VarDecl':
            dest = C.qtype(holder)
        elif kind == 'BinaryOperator' and holder.get('opcode') == '=' and A.kids(holder)[1] is top:
            dest = C.qtype(A.kids(holder)[0])
        elif kind == 'ReturnStmt':
            dest = C.qtype(declaration).split('(', 1)[0].strip()
        elif kind == 'CallExpr' and top in A.kids(holder)[1:]:
            callee = A.strip_implicit(A.kids(holder)[0])
            signature = census.canonical(C.qtype(callee), unit.typedefs)
            if '...' not in signature and not re.search(r'\(\s*\)\s*$', signature):
                dest = C.qtype(top)
    return top, holder, census.canonical(dest, unit.typedefs)


def stable_integer_expression(node, unit):
    """A stable integer RHS for a compound statement with a repeated pure lvalue."""
    scalars = {'char', 'signed char', 'unsigned char', 'short', 'unsigned short', 'int', 'unsigned int'}
    if unit.canon(C.qtype(node)) not in scalars:
        return False
    for item, _ in A.walk(node):
        if unit.volatile(C.qtype(item)):
            return False
        kind = item.get('kind')
        if kind in A.PURE_KINDS:
            continue
        if kind == 'UnaryOperator' and item.get('opcode') in ('+', '-', '~', '!', '*', '&'):
            continue
        if kind == 'BinaryOperator' and item.get('opcode') in ('+', '-', '*', '/', '%', '&', '|', '^', '<<', '>>', '<', '>', '<=', '>=', '==', '!=', '&&', '||'):
            continue
        if kind == 'CStyleCastExpr' and unit.canon(C.qtype(item)) in scalars:
            continue
        return False
    return True


def typed_node_access(holder):
    return bool(holder and (holder.get('kind') in ('MemberExpr', 'ArraySubscriptExpr') or
                           (holder.get('kind') == 'UnaryOperator' and holder.get('opcode') == '*')))


def integer_union_member(unit, value, want, text):
    """An existing nonvolatile integer union view at precisely the same byte offset."""
    if unit.canon(want) == unit.canon(C.qtype(value)):
        return None
    names = []
    current = A.strip_implicit(value)
    while current.get('kind') == 'MemberExpr' and A.kids(current):
        names.insert(0, current.get('name', ''))
        owner = A.strip_implicit(A.kids(current)[0])
        arrow = current.get('isArrow', False)
        record = unit.record_of_pointer(C.qtype(owner)) if arrow else unit.T.record(C.qtype(owner))
        layout = unit.layouts.get(record, {})
        if layout.get('kind') == 'union':
            leaves = []
            stack = [(node, '') for node in layout['kids']]
            while stack:
                node, prefix = stack.pop()
                path = '.'.join(p for p in (prefix, node['name']) if p)
                if node['bits']:
                    continue
                if node['kids']:
                    stack.extend((child, path) for child in node['kids'])
                else:
                    leaves.append((path, node))
            original = next((node for path, node in leaves if path == '.'.join(names)), None)
            span = A.node_range(owner, text)
            if original and span:
                for path, node in sorted(leaves, key=lambda pair: pair[0]):
                    if (path != '.'.join(names) and re.fullmatch(r'[A-Za-z_]\w*(?:\.[A-Za-z_]\w*)*', path) and
                        node['off'] == original['off'] and census.canonical(node['type'], unit.typedefs) == census.canonical(want, unit.typedefs) and
                        unit.size(node['type']) == unit.size(want) and not unit.volatile(node['type'])):
                        return '('+text[span[0]:span[1]]+')'+('->' if arrow else '.')+path
        current = owner
    return None


SIMPLE_PATH = re.compile(r'[A-Za-z_]\w*(?:(?:->|\.)[A-Za-z_]\w*)*')
DEREFERENCE_HOLDERS = ('MemberExpr', 'ArraySubscriptExpr')


def parse_exclusions(specs):
    """`RECORD:OFFSET[,OFFSET...]` (decimal or 0x) or `RECORD:*` -> {record: set of offsets | None (every offset)}."""
    rules = {}
    for spec in specs or ():
        record, sep, offsets = spec.partition(':')
        if not record or not sep or not offsets:
            raise ValueError('exclusion must be RECORD:OFFSET[,OFFSET...] or RECORD:*: ' + spec)
        if offsets.strip() == '*':
            rules[record] = None
            continue
        if record in rules and rules[record] is None:
            continue
        rules.setdefault(record, set()).update(int(o, 0) for o in offsets.split(',') if o.strip())
    return rules


def excluded(rules, record, offset):
    if record not in rules:
        return False
    return rules[record] is None or offset in rules[record]


# Spellings of one C type; unlike cast_ast.SCALAR_ALIAS, `long` stays distinct from `int`
# (gcc warns on a long * / int * mix, so an "exact" member type must not merge them).
STRICT_ALIAS = {
    'signed short': 'short', 'short int': 'short', 'signed short int': 'short',
    'unsigned short int': 'unsigned short', 'signed int': 'int', 'signed': 'int', 'unsigned': 'unsigned int',
    'long int': 'long', 'signed long': 'long', 'signed long int': 'long',
    'unsigned long int': 'unsigned long',
}


def strict_canon(unit, spelling):
    resolved = unit.T.resolve(spelling)
    core = resolved.rstrip('*')
    return STRICT_ALIAS.get(core, core) + '*' * (len(resolved) - len(core))


def address_chain(unit, e):
    """(leaf, constant byte offset | None, variable) of an address expression, also through `&p[K]`."""
    total = 0
    while True:
        leaf, off, var = CC.chain_leaf(unit, e, A, C)
        if var or off is None:
            return leaf, None, True
        total += off
        if leaf.get('kind') == 'UnaryOperator' and leaf.get('opcode') == '&' and A.kids(leaf):
            sub = A.strip_parens(A.kids(leaf)[0])
            if sub.get('kind') == 'ArraySubscriptExpr' and len(A.kids(sub)) == 2:
                array, index = A.kids(sub)
                n = C.int_value(index)
                pointee = unit.T.pointee(C.qtype(array))
                scale = 1 if pointee in (None, 'void') else (unit.size(pointee) or 0)
                if n is None or not scale:
                    return leaf, None, True
                total += n * scale
                e = A.strip_parens(array)
                continue
        return leaf, total, False


def member_candidates(unit, record, offset):
    """[(path, expression type pointee, is_array)] of every non-padding member path starting at `offset`."""
    found = []
    for path, member_type, _ in unit.leaves_at(record, offset):
        if F.PAD.search(path):
            continue
        member_type = member_type.strip()
        match = A.ARRAY.match(member_type)
        if match:
            element = match.group(1).strip()
            found.append((path, element, True, member_type))
        else:
            found.append((path, member_type, False, member_type))
    return found


def outermost(paths):
    """Paths that do not extend another candidate (`a` outranks `a.b` and `a[0]`)."""
    return [p for p in paths if not any(q != p and (p.startswith(q + '.') or p.startswith(q + '[')) for q in paths)]


def choose_member(unit, record, offset, top_type, dest, keep_cast):
    """(path, is_array, reason) for the member whose address is `(u8 *)p + offset`, or (None, None, hold_reason).

    top_type / dest are canonical spellings: the type of the whole replaced expression and the type
    its context converts it to ('' when the context performs no implicit conversion)."""
    size = unit.layouts.get(record, {}).get('size') or 0
    if offset >= size:
        return None, None, 'beyond_struct'
    found = member_candidates(unit, record, offset)
    if not found:
        if any(True for _ in unit.leaves_at(record, offset)):
            return None, None, 'pad_member'
        for node in unit.layouts[record]['kids']:
            if node['bits'] and node['off'] <= offset < node['off'] + (unit.size(node['type']) or 0):
                return None, None, 'bitfield_member'
        inside = CC._inside(unit, record, offset)
        return None, None, {'array_member': 'inside_array_member', 'array_of_struct': 'inside_array_member',
                            'inside_scalar': 'inside_scalar_member', 'inside_substruct': 'inside_scalar_member'
                            }.get(inside, 'no_member_at_offset')
    if any(re.search(r'\b(?:const|volatile)\b', member_type) for _, _, _, member_type in found):
        return None, None, 'qualified_member'
    if any('(*' in member_type or '[' in element for _, element, _, member_type in found):
        return None, None, 'function_pointer_or_multidimensional_member'
    by_path = {path: (element, is_array) for path, element, is_array, _ in found}
    # `a[0]` and `a` are one address; keep the shorter spelling.
    drop = {p for p in by_path if p.endswith('[0]') and p[:-3] in by_path and by_path[p[:-3]][1]}
    exact = [p for p, (element, _) in by_path.items()
             if p not in drop and strict_canon(unit, element + '*') == top_type]
    if len(exact) > 1:
        return None, None, 'ambiguous_members'
    if exact:
        return exact[0], by_path[exact[0]][1], 'exact_member_address'
    top_paths = outermost([p for p in by_path if p not in drop])
    if top_type in ('void*', 'const void*') and dest == top_type:
        if len(top_paths) != 1:
            return None, None, 'ambiguous_members'
        return top_paths[0], by_path[top_paths[0]][1], 'untyped_void_context_member_address'
    if keep_cast:
        if len(top_paths) != 1:
            return None, None, 'ambiguous_members'
        return top_paths[0], by_path[top_paths[0]][1], 'member_address_cast_kept'
    return None, None, 'pointee_type_mismatch'


def member_expression(base_text, path, is_array):
    base = base_text if SIMPLE_PATH.fullmatch(base_text) else '(' + base_text + ')'
    return (base + '->' + path) if is_array else ('&' + base + '->' + path)


def scan(job):
    root, tu, recipe, files = job[:4]
    options = job[4] if len(job) > 4 else {}
    exclusions = parse_exclusions(options.get('exclude_member'))
    setup_root(root)
    unit, error = A.clang_unit(ROOT, tu, recipe)
    result = dict(tu=tu, plans=[], holds=[], error=error or '')
    if unit is None or error:
        return result
    lexical_cache = {}
    accepted_files=set(files)
    declarations=list(unit.functions(accepted_files))
    declarations.extend((d.get('_f') or tu,d) for d in unit.tree.get('inner',[]) if
                        d.get('kind')=='VarDecl' and (d.get('_f') or tu) in accepted_files)
    for file, declaration in declarations:
        text = unit.text(file)
        if file not in lexical_cache:
            lexical_cache[file] = {int(r['start']): r for r in census.lexical(ROOT, file)}
        lexical = lexical_cache[file]
        parents = {id(n): p for n, p in A.walk(declaration)}
        address_seen = set()

        def hold(route, node, reason):
            span = A.node_range(node, text)
            result['holds'].append(dict(file=file, route=route, line=text.count('\n', 0, span[0])+1 if span else '', reason=reason))

        def emit(route, node, replacement, reason, prefix=False):
            span = A.node_range(node, text)
            if not span:
                hold(route, node, 'macro_or_missing_source_range')
                return
            a, b = span
            covered = [r for start, r in lexical.items() if a <= start and int(r['cast_end']) <= b]
            if prefix:
                if a not in lexical:
                    return
                b = int(lexical[a]['cast_end'])
                covered = [lexical[a]]
            if not covered:
                return
            if '\n' in text[a:b] or '\n' in replacement:
                hold(route, node, 'multiline_expression')
                return
            # Some node access rewrites retain the final typed pointer cast.
            # Receipts record the net counted reduction, including casts kept in RHSs.
            replacement_casts = sum(scope['counts']['pointer_casts'] for scope in
                                    D.analyze(file, replacement + ';')['scopes'].values())
            net_casts = len(covered) - replacement_casts
            if net_casts <= 0:
                hold(route, node, 'no_net_cast_reduction')
                return
            result['plans'].append(dict(file=file, function=declaration['name'] if declaration.get('kind')=='FunctionDecl' else '<global>', line=text.count('\n',0,a)+1,
                                        route=route, start=a, end=b, old=text[a:b], new=replacement,
                                        casts=net_casts, reason=reason, source_sha256=digest(text), tu=tu))


        def address_member_site(node):
            """`(u8 *)p + K` / `&((u8 *)p)[K]` used as an address -> the address of p's member at K."""
            top, holder = CC.climb(parents, node, A, C)
            if id(top) in address_seen:
                return
            address_seen.add(id(top))
            if not CC.is_pointer(C.qtype(top)):
                return
            leaf, offset, variable = address_chain(unit, top)
            if variable or offset is None or offset == 0 or not leaf:
                return
            if not any(n.get('kind') == 'CStyleCastExpr' for n, _ in A.walk(top)):
                return
            if typed_node_access(holder):
                hold('address_member', top, 'dereferenced_use_is_cast_fold')
                return
            base = A.strip_implicit(leaf)
            record = unit.record_of_pointer(C.qtype(base)) if base.get('kind') in ('DeclRefExpr', 'MemberExpr') else None
            if not record:
                hold('address_member', top, 'base_not_record_pointer')
                return
            if offset < 0:
                hold('address_member', top, 'negative_offset')
                return
            if CC.GENERATED.search(record):
                hold('address_member', top, 'generated_record_view')
                return
            base_type = census.canonical(C.qtype(base), unit.typedefs)
            if re.search(r'\b(?:const|volatile)\b', base_type + ' ' + C.qtype(base)) or unit.volatile(C.qtype(base)):
                hold('address_member', top, 'qualified_base')
                return
            if excluded(exclusions, record, offset):
                hold('address_member', top, 'excluded_member')
                return
            if not A.pure(base):
                hold('address_member', top, 'impure_base')
                return
            bspan = A.node_range(base, text)
            if not bspan:
                hold('address_member', top, 'macro_or_missing_source_range')
                return
            _, _, dest = context(parents, top, declaration, unit)
            top_type = strict_canon(unit, C.qtype(top))
            path, is_array, reason = choose_member(unit, record, offset, top_type, strict_canon(unit, dest) if dest else '',
                                                   options.get('keep_cast', False))
            if path is None:
                hold('address_member', top, reason)
                return
            replacement = member_expression(text[bspan[0]:bspan[1]], path, is_array)
            if reason == 'member_address_cast_kept':
                replacement = '(' + C.qtype(top) + ')' + replacement
            emit('address_member', top, replacement, reason)

        for node, parent in A.walk(declaration):
            kind = node.get('kind')
            if options.get('address_member') and not A.in_macro(node) and (
                    (kind == 'CStyleCastExpr' and CC.is_pointer(C.qtype(node)) and A.kids(node)) or
                    (kind == 'UnaryOperator' and node.get('opcode') == '&' and A.kids(node) and
                     A.strip_parens(A.kids(node)[0]).get('kind') == 'ArraySubscriptExpr')):
                address_member_site(node)
            if kind == 'CStyleCastExpr' and CC.is_pointer(C.qtype(node)) and A.kids(node):
                span = A.node_range(node, text)
                if not span or span[0] not in lexical:
                    if A.in_macro(node):
                        hold('redundant', node, 'macro_location')
                    continue
                operand = A.kids(node)[0]
                source = census.canonical(C.qtype(operand), unit.typedefs)
                target = census.canonical(C.qtype(node), unit.typedefs)
                top, holder, dest = context(parents, node, declaration, unit)
                unqualified = not re.search(r'\b(?:const|volatile|restrict)\b', source+' '+target)
                objects = source.endswith('*') and target.endswith('*') and '(*' not in source+target
                implicit = bool(dest) and objects and unqualified and (
                    (dest == target and 'void*' in (source, target)) or
                    dest == source or dest == 'void*')
                null = node.get('castKind') == 'NullToPointer' and dest == target
                if source == target or implicit or null:
                    emit('redundant', node, '', 'same_type' if source == target else 'implicit_value_conversion', True)
                elif (holder and holder.get('kind') == 'CallExpr' and dest == 'const void*' and
                      objects and unqualified):
                    emit('qualified_argument', node, '', 'compatible_const_void_argument', True)

                address_top, address_holder = CC.climb(parents, node, A, C)
                base, offset, variable = CC.chain_leaf(unit, address_top, A, C)
                if (offset in (32, -32) and not variable and base and A.pure(base) and
                    unit.layouts.get('ObjectNodeHeader',{}).get('size') == 32):
                    record = unit.record_of_pointer(C.qtype(base))
                    _, _, address_dest = context(parents, address_top, declaration, unit)
                    bspan = A.node_range(base, text)
                    if offset == 32 and record == 'ObjectNodeHeader' and bspan:
                        # The native turn observer matches this callback's exact
                        # source spelling. Keep that proven compatibility anchor.
                        _, call, _ = context(parents, address_top, declaration, unit)
                        native_anchor = (file == 'src/dungeon/player/update_player_and_actor_turns.c' and
                                         call and call.get('kind') == 'CallExpr')
                        if native_anchor:
                            hold('node_body', node, 'native_adaptation_anchor')
                            continue
                        if (address_dest.endswith('*') and '(*' not in address_dest and
                            not re.search(r'\b(?:const|volatile)\b', census.canonical(C.qtype(base), unit.typedefs))):
                            emit('node_body', address_top, 'NODE_BODY('+text[bspan[0]:bspan[1]]+')', 'header_plus_0x20_value')
                        elif (typed_node_access(address_holder) and CC.is_pointer(C.qtype(address_top)) and
                              '(*' not in C.qtype(address_top) and
                              not re.search(r'\b(?:const|volatile)\b', census.canonical(C.qtype(base), unit.typedefs))):
                            target_type = C.qtype(address_top)
                            emit('node_body', address_top, '(('+target_type+')NODE_BODY('+text[bspan[0]:bspan[1]]+'))',
                                 'header_plus_0x20_typed_access')
                        else:
                            hold('node_body', node, 'dereference_or_nonpointer_value_context')
                    elif (offset == -32 and record in ('ActorRecord', 'PlayerRecord') and bspan and
                          address_dest in ('struct ObjectNodeHeader*', 'void*') and
                          not re.search(r'\b(?:const|volatile)\b', census.canonical(C.qtype(base), unit.typedefs))):
                        # shared/entity.h identifies these two records as bodies
                        # immediately after an ObjectNodeHeader. Legacy EntityRec
                        # overlaps unrelated storage and is deliberately excluded.
                        emit('node_body', address_top, 'NODE_HEADER('+text[bspan[0]:bspan[1]]+')', 'known_actor_body_minus_0x20_value')
                    elif (offset == -32 and record in ('ActorRecord', 'PlayerRecord') and bspan and
                          typed_node_access(address_holder) and CC.is_pointer(C.qtype(address_top)) and
                          '(*' not in C.qtype(address_top) and
                          not re.search(r'\b(?:const|volatile)\b', census.canonical(C.qtype(base), unit.typedefs))):
                        replacement = 'NODE_HEADER('+text[bspan[0]:bspan[1]]+')'
                        if census.canonical(C.qtype(address_top), unit.typedefs) != 'struct ObjectNodeHeader*':
                            replacement = '(('+C.qtype(address_top)+')'+replacement+')'
                        emit('node_body', address_top, replacement, 'known_actor_body_minus_0x20_typed_access')
                    elif offset == -32:
                        # A numerical -0x20 alone does not establish body ownership.
                        hold('node_body', node, 'reverse_body_ownership_unproven')

            if kind != 'UnaryOperator' or node.get('opcode') != '*' or A.in_macro(node):
                continue
            cast = A.strip_parens(A.kids(node)[0])
            if cast.get('kind') != 'CStyleCastExpr' or A.in_macro(cast):
                continue
            addr = A.strip_implicit(A.kids(cast)[0])
            if addr.get('kind') != 'UnaryOperator' or addr.get('opcode') != '&':
                continue
            value = A.kids(addr)[0]
            want, have = C.qtype(node), C.qtype(value)
            scalars = {'char','signed char','unsigned char','short','unsigned short','int','unsigned int'}
            if unit.canon(want) not in scalars or unit.canon(have) not in scalars or unit.size(want) != unit.size(have):
                hold('numeric_member', node, 'not_same_width_supported_integer')
                continue
            if unit.volatile(want) or unit.volatile(have) or not A.pure(value):
                hold('numeric_member', node, 'volatile_or_impure_value')
                continue
            if A.strip_implicit(value).get('kind') != 'MemberExpr':
                hold('numeric_member', node, 'not_a_direct_member')
                continue
            vspan = A.node_range(value, text)
            if not vspan:
                hold('numeric_member', node, 'macro_member')
                continue
            top, holder = node, parent
            while holder and holder.get('kind') == 'ParenExpr':
                top, holder = holder, parents.get(id(holder))
            store = bool(holder and holder.get('kind') == 'BinaryOperator' and holder.get('opcode') == '=' and A.kids(holder)[0] is top)
            union_member = integer_union_member(unit, value, want, text)
            if holder and holder.get('kind') == 'CompoundAssignOperator':
                above = parents.get(id(holder))
                lhs, rhs = A.kids(holder)
                if lhs is not top or not above or above.get('kind') != 'CompoundStmt':
                    hold('numeric_member', node, 'consumed_compound_assignment')
                    continue
                if re.search(r'\bconst\b', census.canonical(have, unit.typedefs)):
                    hold('numeric_member', node, 'const_member_store')
                    continue
                if (any(unit.volatile(C.qtype(item)) for item, _ in A.walk(value)) or
                    not stable_integer_expression(rhs, unit)):
                    hold('numeric_member', node, 'unstable_or_noninteger_compound_rhs')
                    continue
                rspan = A.node_range(rhs, text)
                if not rspan or A.in_macro(holder):
                    hold('numeric_member', node, 'macro_compound_assignment')
                    continue
                operator = holder.get('opcode', '')
                if operator not in ('+=', '-=', '*=', '/=', '%=', '&=', '|=', '^=', '<<=', '>>='):
                    hold('numeric_member', node, 'unsupported_compound_operator')
                    continue
                member = text[vspan[0]:vspan[1]]
                replacement = member+' = ('+want+')(('+want+')('+member+') '+operator[:-1]+' ('+text[rspan[0]:rspan[1]]+'))'
                if union_member:
                    replacement = union_member+' '+operator+' ('+text[rspan[0]:rspan[1]]+')'
                reason = 'same_width_integer_union_member_compound_statement' if union_member else 'same_width_integer_member_compound_statement'
                emit('numeric_member', holder, replacement, reason)
                continue
            if store:
                if re.search(r'\bconst\b', census.canonical(have, unit.typedefs)):
                    hold('numeric_member', node, 'const_member_store')
                    continue
                above = parents.get(id(holder))
                if not above or above.get('kind') != 'CompoundStmt':
                    hold('numeric_member', node, 'consumed_assignment_value')
                    continue
                if unit.volatile(C.qtype(A.kids(holder)[1])):
                    hold('numeric_member', node, 'volatile_rhs')
                    continue
                replacement = union_member or text[vspan[0]:vspan[1]]
            else:
                if holder and holder.get('kind') == 'UnaryOperator' and holder.get('opcode') in ('++','--','&'):
                    hold('numeric_member', node, 'mutating_or_address_context')
                    continue
                # C's same-width unsigned conversion preserves bits. A conversion
                # back to signed is implementation-defined; production proof gates it.
                replacement = union_member or '(('+want+')('+text[vspan[0]:vspan[1]]+'))'
            reason = ('same_width_integer_union_member_' if union_member else 'same_width_integer_member_') + ('store' if store else 'load')
            emit('numeric_member', node, replacement, reason)
    return result


def capture(job):
    root, tu, recipe = job
    setup_root(root)
    try:
        return L.capture_one(str(ROOT), tu, recipe)
    except Exception as exc:
        return dict(source=tu, error=str(exc)[-500:])


def check_debt(file, before, after, expected):
    b, a = D.analyze(file,before), D.analyze(file,after)
    assert not a['errors'], (file,a['errors'])
    assert set(b['scopes']) == set(a['scopes']), (file,'scope_change')
    for key, row in a['scopes'].items():
        for debt, count in row['counts'].items():
            assert count <= b['scopes'][key]['counts'][debt], (file,key,debt)
    delta = sum(s['counts']['pointer_casts'] for s in b['scopes'].values()) - sum(s['counts']['pointer_casts'] for s in a['scopes'].values())
    assert delta == expected, (file,delta,expected)


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument('--root', type=Path, default=ROOT)
    ap.add_argument('--folder', required=True)
    ap.add_argument('--census', type=Path, help='optional candidate index; otherwise discover fresh casts')
    ap.add_argument('--out', type=Path, required=True)
    ap.add_argument('--workers', type=int, default=4)
    ap.add_argument('--max-files', type=int, default=0)
    ap.add_argument('--after-file', default='')
    ap.add_argument('--discover-all', action='store_true')
    ap.add_argument('--file', action='append', help='restrict discovery to an explicit source in the allowed folder')
    ap.add_argument('--route', action='append', choices=ALL_ROUTES,
                    help='restrict to selected routes; address_member runs only when named here')
    ap.add_argument('--exclude-member', action='append', default=[], metavar='RECORD:OFFSET[,OFFSET...]',
                    help='address_member: leave sites whose base record is RECORD and byte offset is listed '
                         '(decimal or 0x; RECORD:* excludes the record), e.g. ActorRecord:8,0xB,0xE')
    ap.add_argument('--keep-cast', action='store_true',
                    help='address_member: when the member type differs from the site type keep one outer cast '
                         '(accepted only when casts still drop)')
    ap.add_argument('--reason', action='append', help='restrict to exact guard reasons for isolated trials')
    ap.add_argument('--apply', action='store_true')
    args = ap.parse_args()
    setup_root(args.root)
    folder = Path(args.folder)
    assert not folder.is_absolute() and folder.parts[0] == 'src' and '..' not in folder.parts
    assert (ROOT / folder).resolve().is_relative_to(ROOT)
    assert 1 <= args.workers <= 6
    parse_exclusions(args.exclude_member)
    options = dict(address_member='address_member' in (args.route or ()), exclude_member=args.exclude_member,
                   keep_cast=args.keep_cast)
    if (args.exclude_member or args.keep_cast) and not options['address_member']:
        ap.error('--exclude-member and --keep-cast need --route address_member')
    out = args.out.resolve()
    assert out.is_relative_to(ROOT) and not out.is_relative_to(HERE)
    out.mkdir(parents=True,exist_ok=True)
    (out/'.ignore').write_text('*\n')
    if args.census:
        with gzip.open(args.census, 'rt') as input_file:
            rows = [r for r in csv.DictReader(input_file, delimiter='\t') if r['file'].startswith(args.folder+'/')]
        files = sorted({r['file'] for r in rows if args.discover_all or r['category'] in CATEGORIES})
    else:
        files = sorted(p.relative_to(ROOT).as_posix() for p in (ROOT / folder).rglob('*.c')
                       if census.lexical(ROOT, p.relative_to(ROOT).as_posix()))
    if args.file:
        assert all(f.startswith(args.folder+'/') and '..' not in Path(f).parts for f in args.file)
        files=sorted(set(args.file))
    files = [f for f in files if f > args.after_file]
    if args.max_files:
        files = files[:args.max_files]
    original = {f:(ROOT/f).read_text() for f in files}
    tus, _ = F.physical_for(ROOT, files)
    print('scan',args.folder,len(files),'files',len(tus),'TUs',flush=True)
    plans, holds, errors = [], [], []
    with ProcessPoolExecutor(max_workers=args.workers) as pool:
        for res in pool.map(scan,[(str(ROOT),t,r,files,options) for t,r in sorted(tus.items())]):
            plans.extend(res['plans']); holds.extend(res['holds'])
            if res['error']:
                errors.append(dict(tu=res['tu'],reason='clang_diagnostic',detail=res['error']))
    unique = {}
    for p in plans:
        if p['route'] not in (args.route or ROUTES):
            continue
        if args.reason and p['reason'] not in args.reason:
            continue
        key = (p['file'],p['start'],p['end'],p['new'],p['route'])
        unique.setdefault(key,p)
    selected = defaultdict(list)
    for p in sorted(unique.values(),key=lambda p:(ROUTE_ORDER.index(p['route']),p['file'],p['start'],-p['end'])):
        if any(p['start'] < q['end'] and q['start'] < p['end'] for q in selected[p['file']]):
            holds.append(dict(file=p['file'],route=p['route'],line=p['line'],reason='overlap_with_earlier_route'))
            continue
        assert digest(original[p['file']]) == p['source_sha256']
        selected[p['file']].append(p)
    proposed = {}
    for file, edits in selected.items():
        text = original[file]
        for p in sorted(edits,key=lambda p:-p['start']):
            assert text[p['start']:p['end']] == p['old']
            text = text[:p['start']]+p['new']+text[p['end']:]
        check_debt(file, original[file], text, sum(p['casts'] for p in edits))
        proposed[file] = text
    write_edits(out/'plan.tsv', [p for f in sorted(selected) for p in selected[f]])
    census.write_tsv(out/'holds.tsv',['file','route','line','reason'],holds)
    (out/'errors.json').write_text(json.dumps(errors,indent=2)+'\n')
    summary = dict(folder=args.folder,files_scanned=len(files),last_file=files[-1] if files else '',plans=len(unique),selected_files=len(selected),selected_casts=dict(Counter({route:sum(p['casts'] for edits in selected.values() for p in edits if p['route']==route) for route in ALL_ROUTES})),holds=dict(Counter(p['reason'] for p in holds)),errors=len(errors),applied=False)
    print('plan',json.dumps(summary,sort_keys=True),flush=True)
    if args.apply and proposed:
        touched,_ = F.physical_for(ROOT,sorted(proposed))
        file_tus = {f:{t for t in touched if t==f or Path(f).name in (ROOT/t).read_text()} for f in proposed}
        assert all(file_tus.values()), 'unregistered source'
        before, after = {}, {}
        with ProcessPoolExecutor(max_workers=args.workers) as pool:
            before = {r['source']:r for r in pool.map(capture,[(str(ROOT),t,r) for t,r in sorted(touched.items())])}
        try:
            for file,text in proposed.items():
                assert (ROOT/file).read_text() == original[file], ('stale_plan',file)
                (ROOT/file).write_text(text)
            with ProcessPoolExecutor(max_workers=args.workers) as pool:
                after = {r['source']:r for r in pool.map(capture,[(str(ROOT),t,r) for t,r in sorted(touched.items())])}
            passed = {t for t in touched if 'error' not in before[t] and 'error' not in after[t] and
                      all(k in before[t] and before[t][k]==after[t].get(k) for k in HASH_KEYS[:3]) and
                      before[t].get(HASH_KEYS[3],{}) == after[t].get(HASH_KEYS[3],{})}
            accepted = {f for f in proposed if file_tus[f] <= passed}
            # Shared physical TUs are atomic: any rejected member also rejects
            # the other proposed members in that compilation stream.
            while True:
                rejected_tus = set().union(*(file_tus[f] for f in set(proposed)-accepted)) if set(proposed)-accepted else set()
                narrowed = {f for f in accepted if not file_tus[f] & rejected_tus}
                if narrowed == accepted:
                    break
                accepted = narrowed
            for file in set(proposed)-accepted:
                (ROOT/file).write_text(original[file])
                holds.append(dict(file=file,route='combined',line='',reason='production_identity_failed'))
            receipts = [dict(tu=t,equal=t in passed,before=before[t],after=after[t]) for t in sorted(touched)]
            (out/'identity.json.gz').write_bytes(gzip.compress(json.dumps(receipts,separators=(',',':')).encode()))
            accepted_plans = [p for f in sorted(accepted) for p in selected[f]]
            write_edits(out/'applied.tsv',accepted_plans)
            summary.update(applied=True,accepted_files=len(accepted),accepted_casts={r:sum(p['casts'] for p in accepted_plans if p['route']==r) for r in ALL_ROUTES},rejected_files=sorted(set(proposed)-accepted))
        except BaseException:
            for file in proposed:
                (ROOT/file).write_text(original[file])
            raise
    summary['holds']=dict(Counter(p['reason'] for p in holds))
    census.write_tsv(out/'holds.tsv',['file','route','line','reason'],holds)
    (out/'summary.json').write_text(json.dumps(summary,indent=2)+'\n')
    print('result',json.dumps(summary,sort_keys=True),flush=True)


if __name__ == '__main__':
    main()
