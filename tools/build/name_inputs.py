"""Content witnesses for the name lookups made by ccproc, including misses.

Tokens come from GCC's assembly, before canonicalization. Source scanning cannot
stand in for this: preprocessing can paste identifiers or expand include macros.
These witnesses are compile products, not configure checkpoints or gate proofs.
"""
import json
from pathlib import Path
import re


def table(path):
    result = {}
    try:
        text = Path(path).read_text()
    except FileNotFoundError:
        return result
    for raw in text.splitlines():
        cols = raw.split('#', 1)[0].split('\t')
        if len(cols) >= 3:
            old, new = cols[1].strip(), cols[2].strip()
            if old and new and new != old:
                if not re.fullmatch(r'[A-Za-z_][A-Za-z0-9_]*', new):
                    raise ValueError('invalid name-table identifier: ' + new)
                result[new] = old
    return result


def project(tokens, names):
    return {n: names[n] for n in tokens if n in names}


def symbols(path):
    try:
        lines = Path(path).read_text().splitlines()
    except FileNotFoundError:
        return set()
    values = {line.split('#', 1)[0].strip() for line in lines if line.split('#', 1)[0].strip()}
    if any(not re.fullmatch(r'[A-Za-z_][A-Za-z0-9_]*', n) for n in values):
        raise ValueError('unsupported config symbol: ' + str(path))
    return values


def project_sets(tokens, names, evidence):
    canonical = {names.get(n, n) for n in tokens}
    return {path: sorted(canonical & set(values)) for path, values in evidence.items()}


def evidence_at(root, paths):
    if paths and root is None:
        raise ValueError('config witness requires its build root')
    result = {}
    for path in paths:
        if Path(path).is_absolute() or '..' in Path(path).parts:
            raise ValueError('unsafe config witness path: ' + path)
        result[path] = symbols(Path(root)/path)
    return result


def witness(lines, names, evidence=None, sections=True):
    # Exactly ccproc's word-boundary substitution domain. String directives are
    # opaque; comments and assembler directives are deliberately included.
    tokens = {n for line in lines
              if not re.match(r'\s*\.(ascii|asciz|string)\b', line)
              for n in re.findall(r'\b\w+\b', line)}
    if sections:
        # ccproc consults the table once more for the canonicalized .ent name
        # when choosing a section. Bind that lookup's miss as well: a later row
        # whose new spelling equals an old symbol can affect this second read.
        for line in lines:
            match = re.match(r'\s*\.ent\s+(\S+)', line)
            if match:
                canonical = re.sub(r'\b\w+\b', lambda m: names.get(m[0], m[0]), match[1])
                tokens.add(canonical)
    tokens = sorted(tokens)
    return dict(schema=1, tokens=tokens, rows=project(tokens, names),
                sets=project_sets(tokens, names, evidence or {}))


def write(path, value):
    path = Path(path)
    blob = json.dumps(value, sort_keys=True, separators=(',', ':')).encode() + b'\n'
    path.parent.mkdir(parents=True, exist_ok=True)
    if not path.exists() or path.read_bytes() != blob:
        temporary = path.with_name(path.name + '.tmp')
        temporary.write_bytes(blob)
        temporary.replace(path)


def read(path):
    value = json.loads(Path(path).read_text())
    if (value.get('schema') != 1 or not isinstance(value.get('tokens'), list)
            or any(not isinstance(n, str) for n in value['tokens'])
            or value['tokens'] != sorted(set(value['tokens']))
            or not isinstance(value.get('rows'), dict)
            or not isinstance(value.get('sets', {}), dict)
            or any(not isinstance(p, str) or not isinstance(v, list)
                   or any(not isinstance(s, str) for s in v) or v != sorted(set(v))
                   for p, v in value.get('sets', {}).items())):
        raise ValueError('invalid name-input witness: ' + str(path))
    return value


def refresh(path, names, root=None):
    try:
        value = read(path)
    except FileNotFoundError:
        value = dict(schema=1, tokens=[], rows={}, sets={})
    value['rows'] = project(value['tokens'], names)
    value['sets'] = project_sets(value['tokens'], names, evidence_at(root, value.get('sets', {})))
    write(path, value)


def verify(path, names, root=None):
    value = read(path)
    if value['rows'] != project(value['tokens'], names):
        raise ValueError('stale name-input witness: ' + str(path))
    if value.get('sets', {}) != project_sets(value['tokens'], names,
                                           evidence_at(root, value.get('sets', {}))):
        raise ValueError('stale config-input witness: ' + str(path))
    return value
