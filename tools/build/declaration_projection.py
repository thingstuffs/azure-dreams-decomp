"""Conservative declaration-use digest for preprocessed C translation units.

Clang supplies top-level ranges, but reachability is deliberately lexical: an
identifier spelling is treated as a possible reference even in a context where
Clang knows it is not one. This can retain extra declarations, never remove a
declaration whose spelling is used by retained text.
"""
import hashlib
import json
import re
import subprocess


IDENTIFIER = re.compile(rb'[A-Za-z_][A-Za-z_0-9]*')
SPACE = re.compile(rb'\s*')
RISK = re.compile(rb'\b(?:asm|__asm(?:__)?|__attribute(?:__)?|__declspec|'
                  rb'__extension(?:__)?|_Pragma)\b')
TOP_LEVEL = {'FunctionDecl', 'VarDecl', 'TypedefDecl', 'RecordDecl', 'EnumDecl',
             'FileScopeAsmDecl', 'EmptyDecl'}


def _names(node):
    result = set()
    if node.get('name'):
        result.add(node['name'].encode())
    pending = list(node.get('inner', []))
    while pending:
        child = pending.pop()
        if child.get('kind') in {'RecordDecl', 'EnumDecl', 'EnumConstantDecl', 'TypedefDecl'}:
            if child.get('name'):
                result.add(child['name'].encode())
        pending.extend(child.get('inner', []))
    return result


def _candidate(node):
    kind = node['kind']
    if kind in {'TypedefDecl', 'RecordDecl', 'EnumDecl'}:
        return True
    if kind == 'FunctionDecl':
        return (node.get('storageClass') != 'static' and
                not any(child.get('kind') == 'CompoundStmt' for child in node.get('inner', [])))
    if kind == 'VarDecl':
        return node.get('storageClass') == 'extern' and not node.get('init')
    return False


def project(expanded, clang='clang'):
    """Return projected bytes, or None when a complete safe partition is unavailable."""
    # Directives can change compilation outside their own range or encode a
    # line-sensitive state. Keep the full compiler text for those TUs.
    if re.search(rb'(?m)^\s*#', expanded):
        return None
    try:
        parsed = subprocess.run([clang, '-x', 'c', '-std=gnu89', '-fsyntax-only',
                                 '-Wno-everything', '-Xclang', '-ast-dump=json', '-'],
                                input=expanded, capture_output=True)
    except OSError:
        return None
    if parsed.returncode:
        return None
    try:
        nodes = [node for node in json.loads(parsed.stdout)['inner']
                 if not node.get('isImplicit')]
        spans = []
        for node in nodes:
            if node['kind'] not in TOP_LEVEL:
                return None
            begin = node['range']['begin']['offset']
            endinfo = node['range']['end']
            end = endinfo['offset'] + endinfo['tokLen']
            if not (0 <= begin < end <= len(expanded)):
                return None
            # Clang excludes the semicolon from declaration ranges.
            after = SPACE.match(expanded, end).end()
            if expanded[after:after+1] == b';':
                end = after + 1
            spans.append((begin, end, node))
    except (ValueError, KeyError, TypeError, IndexError):
        return None
    spans.sort(key=lambda row: (row[0], row[1]))
    groups = []
    for begin, end, node in spans:
        if groups and begin < groups[-1][1]:
            if begin != groups[-1][0]:
                # Nested ranges in one typedef are okay; all other overlaps
                # need an unambiguous shared beginning.
                if not all(n['kind'] in {'RecordDecl', 'EnumDecl', 'TypedefDecl'}
                           for n in groups[-1][2] + [node]):
                    return None
            groups[-1][1] = max(groups[-1][1], end)
            groups[-1][2].append(node)
        else:
            groups.append([begin, end, [node]])
    previous = 0
    for begin, end, _ in groups:
        if expanded[previous:begin].strip():
            return None
        previous = end
    if expanded[previous:].strip():
        return None
    candidates, kept = [], set()
    for i, (begin, end, declarations) in enumerate(groups):
        segment = expanded[begin:end]
        names = set().union(*(_names(node) for node in declarations))
        if (names and all(_candidate(node) for node in declarations)
                and not RISK.search(segment)):
            candidates.append((i, names, set(IDENTIFIER.findall(segment))))
        else:
            kept.add(i)
    # A retained definition or static declaration seeds reachability. Each
    # reached declaration contributes its own type and identifier references.
    referenced = set().union(*(set(IDENTIFIER.findall(expanded[b:e]))
                               for i, (b, e, _) in enumerate(groups) if i in kept))
    changed = True
    while changed:
        changed = False
        for i, names, references in candidates:
            if i not in kept and names & referenced:
                kept.add(i)
                referenced.update(references)
                changed = True
    return b'\n'.join(expanded[groups[i][0]:groups[i][1]]
                      for i in sorted(kept))


def digest(expanded, clang='clang'):
    projection = project(expanded, clang)
    return hashlib.sha256(expanded if projection is None else projection).hexdigest(), projection is not None
