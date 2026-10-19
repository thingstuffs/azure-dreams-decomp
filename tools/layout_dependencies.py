"""Quoted include dependencies used by layout planning and object receipts."""
from __future__ import annotations
import re


def conditional_depths(text):
    """Inline include depths; -1 marks lines without a real include directive."""
    # Preprocessing removes spliced newlines before recognizing directives;
    # quoted comment markers must not hide a real conditional.
    tokens = re.compile(r'"(?:\\.|[^"\\])*"|\'(?:\\.|[^\'\\])*\'|/\*.*?\*/|//[^\n]*', re.S)
    lines = text.splitlines(keepends=True)
    logical, widths, pending, width = [], [], '', 0
    for line in lines:
        width += 1
        if line.endswith('\\\n') or line.endswith('\\\r\n'):
            pending += line.rstrip('\r\n')[:-1]
            continue
        logical.append(pending + line)
        widths.append(width)
        pending, width = '', 0
    if width:
        logical.append(pending)
        widths.append(width)
    joined = ''.join(logical)
    clean = tokens.sub(lambda m: ''.join('\n' if c == '\n' else ' ' for c in m[0]), joined)
    depth, result = 0, []
    for line, count in zip(clean.splitlines(), widths):
        is_include = re.match(r'\s*#\s*include\b', line) is not None
        result.extend([depth if is_include else -1] * count)
        directive = re.match(r'\s*#\s*(if|ifdef|ifndef|endif)\b', line)
        if directive:
            depth += -1 if directive[1] == 'endif' else 1
            if depth < 0:
                raise ValueError('unbalanced conditional directives')
    if depth:
        raise ValueError('unbalanced conditional directives')
    return result


def include_parents(root):
    from layout_apply import scan_files, resolve, INCLUDE
    parents = {}
    for p in scan_files(root, ('src', 'include'), {'.c', '.h'}):
        rel = p.relative_to(root).as_posix()
        for hit in INCLUDE.finditer(p.read_text(errors='surrogateescape')):
            target = resolve(root, rel, hit[2], angled=hit[1].endswith('<'))
            if target:
                parents.setdefault(target, set()).add(rel)
    return parents


def consumer_paths(root, affected, *, transitive=True, parents=None):
    """All source/header users of resolved targets, including physical parents."""
    if parents is None:
        parents = include_parents(root)
    result, pending = set(affected), list(affected)
    while pending:
        for parent in parents.get(pending.pop(), ()):
            if parent not in result:
                result.add(parent)
                if transitive:
                    pending.append(parent)
    return result
