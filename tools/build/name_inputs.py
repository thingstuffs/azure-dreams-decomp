"""Content witnesses for the name lookups made by ccproc, including misses.

Tokens come from GCC's assembly, before canonicalization. Source scanning cannot
stand in for this: preprocessing can paste identifiers or expand include macros.
These witnesses are compile products, not configure checkpoints or gate proofs.
"""
import json
from pathlib import Path
import re


# A placed-copy row: the same function (same words, relocated fields aside) placed at a second address in
# another image keeps its address row but spells the family's one name, and its evidence starts with
# `copy_of=0x<canonical address>`. The canonical row is the name's ordinary row. The new -> old table below
# never lets a copy row shadow the canonical address; a build step that compiles the copy binds the name to
# the copy's own address inside that TU (tools/gate/overlay_module_gate.bind_native_entries).
COPY_OF = re.compile(r'copy_of=0x([0-9A-F]{8})(?:;|\s|$)')


def copy_of(evidence):
    """Canonical func_<addr> a row's evidence records it as a placed copy of, or None."""
    match = COPY_OF.match(evidence.strip())
    return 'func_' + match[1] if match else None


def _rows(text):
    for raw in text.splitlines():
        cols = raw.split('#', 1)[0].split('\t')
        if len(cols) >= 3:
            old, new = cols[1].strip(), cols[2].strip()
            if old and new and new != old:
                if not re.fullmatch(r'[A-Za-z_][A-Za-z0-9_]*', new):
                    raise ValueError('invalid name-table identifier: ' + new)
                yield old, new, copy_of(cols[3]) if len(cols) >= 4 else None


def _read(path):
    try:
        return Path(path).read_text()
    except FileNotFoundError:
        return ''


def table(path):
    result = {}
    for old, new, canonical in _rows(_read(path)):
        if canonical is None:
            result[new] = old
    return result


def copies(path):
    """name -> {'canonical': func_<addr>, 'copies': sorted func_<addr>} for every recorded placed-copy family.

    Fails closed: a copy row must name the address its name's ordinary row binds (so table() and this agree),
    may not be its own canonical, and an address cannot be a copy of two families under one name."""
    text = _read(path)
    names = {}
    found = {}
    for old, new, canonical in _rows(text):
        if canonical is None:
            names[new] = old
        else:
            found.setdefault(new, set()).add((old, canonical))
    result = {}
    for new, members in sorted(found.items()):
        canonical = {c for _, c in members}
        if len(canonical) != 1 or names.get(new) not in canonical:
            raise ValueError('placed copy does not name its canonical row: ' + new)
        canonical = canonical.pop()
        olds = sorted(old for old, _ in members)
        if canonical in olds or len(set(olds)) != len(olds):
            raise ValueError('invalid placed-copy family: ' + new)
        result[new] = dict(canonical=canonical, copies=olds)
    return result


def family(name, families):
    """Every address one name binds through recorded placed copies (empty when it has none)."""
    value = families.get(name)
    return {value['canonical'], *value['copies']} if value else set()


def project(tokens, names):
    return {n: names[n] for n in tokens if n in names}


def reverse_symbols(module):
    """Native storage validation queries all aliases of each allocation symbol."""
    return sorted({slot['symbol'] for allocation in module.get('allocations', ())
                   for slot in allocation.get('slots', ()) if 'symbol' in slot})


def project_reverse(tokens, root):
    # Bind every raw row alias native source_symbol_pattern may choose from,
    # including aliases shadowed by later rows with the same new spelling (when a
    # symbol has several, the pattern picks the one its slot source spells, and
    # that source is a fingerprinted review input). Empty queries bind misses.
    result = {n: set() for n in tokens}
    if not result:
        return {}
    if root is None:
        raise ValueError('reverse name witness requires its build root')
    try:
        lines = (Path(root)/'config/names.tsv').read_text().splitlines()
    except FileNotFoundError:
        lines = []
    for raw in lines:
        cols = raw.split('#', 1)[0].rstrip().split('\t')
        if len(cols) >= 3:
            old, new = cols[1].strip(), cols[2].strip()
            if old in result and new and old != new:
                result[old].add(new)
    return {n: sorted(values) for n, values in result.items()}


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


def merge(path, value, names, evidence=None):
    """Union sequential passes within ONE compile, retaining section lookups."""
    try:
        previous = read(path)
    except FileNotFoundError:
        write(path, value)
        return
    if (previous['rows'] != project(previous['tokens'], names)
            or previous.get('sets', {}) != project_sets(previous['tokens'], names, evidence or {})):
        raise ValueError('name/config inputs changed between traces')
    value['tokens'] = sorted(set(previous['tokens']) | set(value['tokens']))
    value['rows'] = project(value['tokens'], names)
    value['sets'] = project_sets(value['tokens'], names, evidence or {})
    if 'reverse' in previous:
        value['reverse'] = previous['reverse']
    write(path, value)


def read(path):
    value = json.loads(Path(path).read_text())
    if (not isinstance(value, dict) or value.get('schema') != 1 or not isinstance(value.get('tokens'), list)
            or any(not isinstance(n, str) for n in value['tokens'])
            or value['tokens'] != sorted(set(value['tokens']))
            or not isinstance(value.get('rows'), dict)
            or any(not isinstance(value.get(field, {}), dict)
                   or any(not isinstance(p, str) or not isinstance(v, list)
                          or any(not isinstance(s, str) for s in v) or v != sorted(set(v))
                          for p, v in value.get(field, {}).items())
                   for field in ('sets', 'reverse'))):
        raise ValueError('invalid name-input witness: ' + str(path))
    return value


def refresh(path, names, root=None):
    try:
        value = read(path)
    except FileNotFoundError:
        value = dict(schema=1, tokens=[], rows={}, sets={})
    value['rows'] = project(value['tokens'], names)
    value['sets'] = project_sets(value['tokens'], names, evidence_at(root, value.get('sets', {})))
    if 'reverse' in value:
        value['reverse'] = project_reverse(value['reverse'], root)
    write(path, value)


def verify(path, names, root=None):
    value = read(path)
    if value['rows'] != project(value['tokens'], names):
        raise ValueError('stale name-input witness: ' + str(path))
    if value.get('sets', {}) != project_sets(value['tokens'], names,
                                           evidence_at(root, value.get('sets', {}))):
        raise ValueError('stale config-input witness: ' + str(path))
    if 'reverse' in value and value['reverse'] != project_reverse(value['reverse'], root):
        raise ValueError('stale reverse-name witness: ' + str(path))
    return value
