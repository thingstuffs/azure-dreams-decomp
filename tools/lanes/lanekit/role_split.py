"""Explicit source-line role splits; candidates still pass Lab's normal scorer."""
import re

IDENT = re.compile(r'^[A-Za-z_]\w*$')
KEYWORDS = set('auto break case char const continue default do double else enum extern float for goto if int long register return short signed sizeof static struct switch typedef union unsigned void volatile while'.split())


def code_mask(text):
    """Mask non-code without moving any line or character offsets."""
    rx = r'"(?:\\.|[^"\\])*"|\'(?:\\.|[^\'\\])*\'|//[^\n]*|/\*.*?\*/|^[ \t]*#(?:[^\n]*\\\n)*[^\n]*'
    return re.sub(rx, lambda m: ''.join('\n' if c == '\n' else ' ' for c in m[0]), text, flags=re.S | re.M)


def split_roles(text, symbol, mapping):
    if not IDENT.fullmatch(symbol) or not isinstance(mapping, dict) or not mapping:
        raise ValueError('a scalar symbol and nonempty role mapping are required')
    mask = code_mask(text)
    lines = text.splitlines(keepends=True)
    masked = mask.splitlines(keepends=True)
    # One uninitialized declaration, or one ASM_REG declaration. Preserve its
    # pin when any role still uses the original variable; new locals are plain C.
    decl_rx = re.compile(r'^(\s*)(?:ASM_REG\(\s*([A-Za-z_]\w*)\s*,\s*' + re.escape(symbol) +
                         r'\s*,\s*\d+\s*\)|(?:register\s+)?([A-Za-z_]\w*)\s+' + re.escape(symbol) +
                         r'(?:\s+ASM_REG\(\s*\))?)\s*;\s*$')
    declarations = [(i, decl_rx.fullmatch(line)) for i, line in enumerate(masked) if decl_rx.fullmatch(line)]
    if len(declarations) != 1:
        raise ValueError('need exactly one standalone uninitialized scalar declaration of ' + symbol)
    decl, match = declarations[0]
    typ = match[2] or match[3]
    if typ in ('volatile', 'const', 'static', 'extern', 'register', 'void'):
        raise ValueError('unsupported local type: ' + typ)
    occurrence = re.compile(r'\b' + re.escape(symbol) + r'\b')
    def uses(line):
        return [m for m in occurrence.finditer(line) if not line[:m.start()].rstrip().endswith(('.', '->'))]
    assigned = {}
    for name, numbers in mapping.items():
        if not isinstance(name, str) or not IDENT.fullmatch(name) or name in KEYWORDS or re.search(r'\b' + re.escape(name) + r'\b', mask):
            raise ValueError('invalid or colliding role variable: ' + str(name))
        if not isinstance(numbers, list) or not numbers:
            raise ValueError('each role needs a nonempty source-line list')
        for number in numbers:
            if type(number) is not int or not 1 <= number <= len(lines) or number - 1 == decl:
                raise ValueError('invalid use line: ' + str(number))
            if number in assigned or not uses(masked[number - 1]):
                raise ValueError('overlapping or stale use line: ' + str(number))
            assigned[number] = name
    for number, name in assigned.items():
        i = number - 1
        for use in reversed(uses(masked[i])):
            lines[i] = lines[i][:use.start()] + name + lines[i][use.end():]
    remaining = [i + 1 for i, line in enumerate(masked) if i != decl and i + 1 not in assigned and uses(line)]
    indent = re.match(r'[ \t]*', lines[decl])[0]
    newline = '\r\n' if lines[decl].endswith('\r\n') else '\n'
    declarations = ''.join(indent + typ + ' ' + name + ';' + newline for name in mapping)
    lines[decl] = declarations + (lines[decl] if remaining else '')
    return ''.join(lines), remaining


def variants(text, spec):
    """{symbol, roles:{role:[lines]}, variants:{variant:{newvar:[roles]}}}."""
    if not isinstance(spec, dict) or set(spec) != {'symbol', 'roles', 'variants'}:
        raise ValueError('role-split spec requires symbol, roles and variants')
    if not isinstance(spec['roles'], dict) or not isinstance(spec['variants'], dict) or not spec['variants']:
        raise ValueError('roles and variants must be nonempty objects')
    if any(not isinstance(lines, list) or not lines for lines in spec['roles'].values()):
        raise ValueError('each named role needs a nonempty source-line list')
    for variant, groups in spec['variants'].items():
        if not IDENT.fullmatch(variant) or not isinstance(groups, dict):
            raise ValueError('invalid variant name or grouping')
        mapping = {}
        for variable, roles in groups.items():
            if not isinstance(roles, list) or not roles or any(not isinstance(role, str) or role not in spec['roles'] for role in roles):
                raise ValueError('unknown or empty named role group')
            mapping[variable] = [n for role in roles for n in spec['roles'][role]]
        candidate, remaining = split_roles(text, spec['symbol'], mapping)
        yield variant, candidate, remaining
