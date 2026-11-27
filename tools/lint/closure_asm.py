#!/usr/bin/env python3
"""Assembler uses in C units, read from the preprocessed text of every unit of the build plan.

"C code" in the ownership check means compiler output. A function whose body is assembler text in a .c file (a
file-scope asm block with directives around an include of bytes, or word lines) builds the same object shape as a
compiled function, so the object cannot tell them apart. This check reads the macro-expanded text of EVERY unit
(the same `gcc -E` expansion the object cache key already binds, so a keyword spelled through a token-pasting macro
is a plain keyword here) and classifies each assembler use:

  (a) rename   `... __asm__("name")` after a declarator, no operands, a bare symbol or register name: allowed
  (b) template `asm` statement inside a function body whose string holds instructions only (no token that starts
               with a dot) and whose exact text is listed in config/asm_templates.tsv: allowed
  (c) anything else is REFUSED: a file-scope block (except the exact listed lines whose included file is bound by
      hash), a directive in a template, a template text that is not listed, a section attribute.

It reads no object, changes no built byte and is not an input of the object cache key. It runs for every unit of
every route: ordinary overlay recipes (build/.state/recipes, including module recipes and the movie overlay), the
executable's recipes (build/.state/slus-recipes) and the decoded images' units.

    python3 tools/lint/closure_asm.py check [--census OUT.json] [--jobs N] [--write-templates]
    exit 0 = no refusal, 1 = a refusal (each printed as `file:line: refused: ...`), 2 = an input is missing.
"""
import argparse
import ast
import bisect
import concurrent.futures
import hashlib
import json
import os
import re
import shlex
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
TEMPLATES = 'config/asm_templates.tsv'

SCAN = re.compile(r'"(?:\\.|[^"\\\n])*"|\'(?:\\.|[^\'\\\n])*\'|[{}]|\b(?:asm|__asm__|__asm)\b|'
                  r'\b__attribute(?:__)?\b')
QUALIFIER = re.compile(r'\s*(?:volatile|__volatile__|__volatile|const|__const__|__const)\b')
STRING = re.compile(r'(?:L?"(?:\\.|[^"\\\n])*"\s*)+')
LITERAL = re.compile(r'"(?:\\.|[^"\\\n])*"')
# a directive: a token that starts with a dot at the start of an instruction statement or after a label
DIRECTIVE = re.compile(r'(?:^|[\s;:,])\.[A-Za-z_]')
SYMBOL = re.compile(r'\*?[A-Za-z_$.][A-Za-z0-9_$.]*|\$[0-9a-z]+')
SECTION = re.compile(r'\b(?:__)?section(?:__)?\s*\(\s*("(?:\\.|[^"\\])*")?')
LINE_MARKER = re.compile(r'^#\s*(\d+)\s+"((?:\\.|[^"\\])*)"')


def sha256(data):
    return hashlib.sha256(data).hexdigest()


def decode(literals):
    out = []
    for lit in literals:
        try:
            out.append(ast.literal_eval(lit.lstrip('L')))
        except (ValueError, SyntaxError):
            out.append(lit.strip('"'))
    return ''.join(out)


def lines_of(expanded):
    """(text without line markers, line start offsets, [(file, line)] per kept line)."""
    kept, where, file, number = [], [], '<stdin>', 1
    for raw in expanded.split('\n'):
        marker = LINE_MARKER.match(raw)
        if marker:
            number, file = int(marker.group(1)), marker.group(2)
            continue
        if raw.startswith('#'):
            kept.append('')
        else:
            kept.append(raw)
        where.append((file, number))
        number += 1
    starts, offset = [], 0
    for line in kept:
        starts.append(offset)
        offset += len(line) + 1
    return '\n'.join(kept), starts, where


def previous_token(text, position):
    """The last significant character or word before `position` ('' at the start)."""
    index = position
    while index > 0 and text[index - 1].isspace():
        index -= 1
    if index == 0:
        return ''
    if text[index - 1].isalnum() or text[index - 1] in '_$':
        start = index
        while start > 0 and (text[start - 1].isalnum() or text[start - 1] in '_$'):
            start -= 1
        return text[start:index]
    return text[index - 1]


def matching_close(text, open_index):
    """Index of the `)` that closes the `(` at open_index (strings skipped), or -1."""
    depth = 0
    for match in re.finditer(r'"(?:\\.|[^"\\\n])*"|\'(?:\\.|[^\'\\\n])*\'|[()]', text[open_index:open_index + 20000]):
        token = match.group(0)
        if token == '(':
            depth += 1
        elif token == ')':
            depth -= 1
            if depth == 0:
                return open_index + match.end() - 1
    return -1


def classify(expanded, allowed_templates=frozenset(), allowed_blocks=frozenset(), allowed_sections=frozenset()):
    """List of uses: dict(kind, file, line, template, reason). kind is rename, template, block, refused-*."""
    text, starts, where = lines_of(expanded)
    uses, depth = [], 0

    def place(position):
        return where[max(0, bisect.bisect_right(starts, position) - 1)]

    for match in SCAN.finditer(text):
        token = match.group(0)
        if token == '{':
            depth += 1
        elif token == '}':
            depth = max(0, depth - 1)
        elif token[0] in '"\'':
            continue
        elif token.startswith('__attribute'):
            open_index = text.find('(', match.end())
            if open_index < 0:
                continue
            close = matching_close(text, open_index)
            for named in (SECTION.finditer(text[open_index:close]) if close > 0 else ()):
                name = decode([named.group(1)]) if named.group(1) else ''
                # data sections only; a section that holds code (.text...) must be listed by exact name
                if name.startswith('.') and not name.startswith('.text') or name in allowed_sections:
                    continue
                file, line = place(match.start())
                uses.append(dict(kind='refused-section', file=file, line=line, template=name, full=name,
                                 reason='section attribute names a code section (or none) that is not listed in ' + TEMPLATES))
        else:
            position = match.start()
            file, line = place(position)
            after = match.end()
            qualified = False
            while True:
                q = QUALIFIER.match(text, after)
                if not q:
                    break
                qualified, after = True, q.end()
            rest = re.compile(r'\s*\(').match(text, after)
            if not rest:
                uses.append(dict(kind='refused-syntax', file=file, line=line, template='',
                                 reason='assembler keyword not followed by a parenthesis'))
                continue
            open_index = rest.end() - 1
            close = matching_close(text, open_index)
            if close < 0:
                uses.append(dict(kind='refused-syntax', file=file, line=line, template='',
                                 reason='unterminated assembler statement'))
                continue
            inside = text[open_index + 1:close]
            literal = STRING.match(inside.lstrip())
            template = decode(LITERAL.findall(literal.group(0))) if literal else ''
            operands = inside.lstrip()[literal.end():].strip() if literal else inside
            before = previous_token(text, position)
            statement = before in ('', ';', '}', '{') or (depth > 0 and before in (')', ':', 'else', 'do'))
            if depth == 0 and statement:
                kind = 'block'
                if template in allowed_blocks and not operands:
                    uses.append(dict(kind='block-listed', file=file, line=line, template=template, reason=''))
                else:
                    uses.append(dict(kind='refused-block', file=file, line=line, template=template[:200], full=template,
                                     reason='file-scope assembler block'))
            elif not statement:
                if (not qualified and not operands and SYMBOL.fullmatch(template) is not None
                        and not DIRECTIVE.search(template)):
                    uses.append(dict(kind='rename', file=file, line=line, template=template, reason=''))
                else:
                    uses.append(dict(kind='refused-rename', file=file, line=line, template=template[:200], full=template,
                                     reason='assembler label that is not a plain symbol or register name'))
            else:
                if DIRECTIVE.search(template):
                    uses.append(dict(kind='refused-directive', file=file, line=line, template=template[:200], full=template,
                                     reason='assembler directive inside a function body template'))
                elif template not in allowed_templates:
                    uses.append(dict(kind='refused-template', file=file, line=line, template=template[:200], full=template,
                                     reason='template text not listed in ' + TEMPLATES))
                else:
                    uses.append(dict(kind='template', file=file, line=line, template=template, reason=''))
    return uses


# ---- the build plan ----

def load_templates(root, path=None):
    """({template text}, {file-scope block text}, {section name}, [problems]) from config/asm_templates.tsv; a block row names the
    file its text includes and that file's sha256, which must match."""
    templates, blocks, sections, problems = set(), set(), set(), []
    path = Path(path) if path else root / TEMPLATES
    if not path.is_file():
        return templates, blocks, sections, ['missing ' + TEMPLATES]
    for number, raw in enumerate(path.read_text().splitlines(), 1):
        if not raw or raw.startswith('#'):
            continue
        cells = raw.split('\t')
        try:
            if cells[0] == 'template':
                templates.add(json.loads(cells[1]))
            elif cells[0] == 'block':
                text, name, digest = json.loads(cells[1]), cells[2], cells[3]
                actual = sha256((root / name).read_bytes()) if name != '-' and (root / name).is_file() else None
                if name == '-':
                    blocks.add(text)
                elif actual != digest:
                    problems.append('%s:%d: block row binds %s sha256 %s but the file is %s' % (
                        TEMPLATES, number, name, digest[:12], (actual or 'missing')[:12]))
                else:
                    blocks.add(text)
            elif cells[0] == 'section':
                sections.add(json.loads(cells[1]))
            else:
                problems.append('%s:%d: unknown row kind' % (TEMPLATES, number))
        except (ValueError, IndexError):
            problems.append('%s:%d: unreadable row' % (TEMPLATES, number))
    return templates, blocks, sections, problems


def units(root):
    """Every C unit of the build plan: [dict(route, name, version, flags, sources, include, projection)]."""
    found = []
    plan = root / 'build/build.mk'
    if not plan.is_file():
        return []
    # build.mk names the recipes the build runs; recipe files of an earlier configuration may linger beside them
    live = set(re.findall(r'mkbuild\.py (?:slus_)?compile (build/\.state/[a-z-]+/[0-9a-f]+\.json)', plan.read_text()))
    for path in sorted(root / name for name in live if name.startswith('build/.state/recipes/')):
        spec = json.loads(path.read_text())
        if not spec.get('source', '').endswith('.c') or not spec.get('wrapper', '').endswith('cc.sh'):
            continue
        sources = [spec['source']] + [m['source'] for m in spec.get('module', {}).get('members', [])]
        flags = shlex.split(spec['args'][1])
        if 'module' in spec:
            flags += ['-I' + str((root / n).parent) for n in sources]
        found.append(dict(route='module' if 'module' in spec else 'overlay', name=spec['source'], version=spec['args'][0],
                          flags=flags, sources=sources, include=str(root / 'include'),
                          projection=spec.get('projection'), deps=spec.get('dependencies', []),
                          extra=[spec.get('projection_input')] + ([spec['projection']['owner']] if spec.get('projection') else [])))
    for path in sorted(root / name for name in live if name.startswith('build/.state/slus-recipes/')):
        spec = json.loads(path.read_text())
        if 'command' not in spec:
            continue
        argv = shlex.split(spec['command'])
        if len(argv) < 6 or not argv[0].endswith('/cc.sh'):
            continue
        found.append(dict(route='executable', name='build_slus/' + argv[1], version=argv[3], flags=shlex.split(argv[4]),
                          sources=['build_slus/' + argv[1]], include=str(root / 'build_slus/include'), projection=None,
                          deps=spec.get('dependencies', []), extra=[]))
    sys.path.insert(0, str(root))
    sys.path.insert(0, str(root / 'tools'))
    from tools import decoded_images
    for image in decoded_images.manifests(root):
        for unit in image['units']:
            found.append(dict(route='decoded', name=unit['source'], version=unit['compiler'],
                              flags=shlex.split(unit['flags']), sources=[unit['source']],
                              include=str(root / 'include'), projection=None, deps=None, extra=[]))
    return found


def preprocess(root, unit):
    compiler = root / 'toolchain/compilers' / ('gcc-' + unit['version'])
    texts = []
    for source in unit['sources']:
        path = root / source
        argv = [str(compiler / 'gcc'), '-B' + str(compiler) + '/', '-E', '-O2', *unit['flags'],
                '-I' + unit['include'], '-w']
        stdin = None
        if unit.get('projection') and source == unit['name']:
            sys.path.insert(0, str(root / 'tools'))
            from gate.source_layout import member_projection
            text = member_projection(unit['projection']['home'], root)
            if text is None:
                raise ValueError('member projection vanished: ' + unit['projection']['home'])
            # the generated text goes in through stdin: this check writes nothing into the tree it reads
            argv += ['-x', 'c', '-I' + str(path.parent), '-']
            stdin = text if isinstance(text, bytes) else text.encode()
        else:
            argv.append(str(path))
        try:
            done = subprocess.run(argv, cwd=root, capture_output=True, input=stdin)
        finally:
            pass
        if done.returncode:
            raise ValueError('preprocessor failed on %s: %s' % (source, done.stderr.decode(errors='replace')[:300]))
        texts.append(done.stdout.decode(errors='replace'))
    return texts


def check_unit(args):
    root, unit, templates, blocks, sections = args
    try:
        uses = []
        for text in preprocess(root, unit):
            uses += classify(text, templates, blocks, sections)
        return unit, uses, None
    except (ValueError, OSError) as error:
        return unit, [], str(error)


MEMO = 'build/.state/asm_check_memo.json'


class Hasher:
    """Content hashes of files, remembered across runs by (size, mtime_ns): a file whose size and mtime did not change is not read again."""

    def __init__(self, known):
        self.known, self.fresh, self.done = known, {}, {}

    def __call__(self, path):
        path = str(path)
        if path in self.done:
            return self.done[path]
        self.done[path] = self.read(path)
        return self.done[path]

    def read(self, path):
        try:
            st = os.stat(path)
        except OSError:
            return 'missing'
        sig = [st.st_size, st.st_mtime_ns]
        old = self.known.get(path)
        if old and old[:2] == sig:
            self.fresh[path] = old
            return old[2]
        with open(path, 'rb') as handle:
            digest = sha256(handle.read())
        self.fresh[path] = sig + [digest]
        return digest


def listing_digest(directory, cache):
    if directory not in cache:
        try:
            names = sorted(os.listdir(directory))
        except OSError:
            names = []
        cache[directory] = sha256('\0'.join(names).encode())
    return cache[directory]


def tree_listing(root, cache):
    """Digest of the names of every file under include/ (a header added in front of another one shadows it)."""
    key = 'tree:' + str(root)
    if key not in cache:
        names = []
        for base, _dirs, files in os.walk(root / 'include'):
            names += [os.path.join(base, f) for f in files]
        cache[key] = sha256('\0'.join(sorted(names)).encode())
    return cache[key]


def memo_key(root, unit, hasher, tool_digest, templates_digest, lists):
    """What the memo key binds: the checker file, the templates file and the files it binds by hash, the unit's route, compiler
    version, flags and include path, the unit's sources, every file its recipe lists as a dependency (the include closure the build
    keeps and regenerates when a source or header set changes; for a projected unit also its projection input and owner source),
    the names of the files under include/ and the names in each source's directory (shadowing by a new header). Units with no
    recipe dependencies (the decoded images' units) have no key and are always checked."""
    if unit.get('deps') is None:
        return None
    parts = [tool_digest, templates_digest, unit['route'], unit['version'], ' '.join(unit['flags']), unit['include']]
    base = str(root) + '/'
    parts += [hasher(base + 'include/labels.inc')]
    for source in unit['sources']:
        parts += [source, hasher(base + source), listing_digest(os.path.dirname(base + source), lists)]
    parts.append(tree_listing(root, lists))
    for name in list(unit['deps']) + [e for e in unit.get('extra', []) if e]:
        parts.append(name + ':' + hasher(base + name))
    return sha256('\n'.join(parts).encode())


def run(root, jobs=4, census=None, write_templates=False, templates_file=None, memo=True):
    root = Path(root).resolve()
    templates, blocks, sections, problems = load_templates(root, templates_file)
    if write_templates:
        templates, blocks, sections, problems = set(), set(), set(), []
    plan = units(root)
    if not plan:
        print('closure_asm: no unit in the build plan (run make configure first)')
        return 2
    seen_templates, counts, refusals, errors, per_route = {}, {}, [], [], {}
    memo = memo and not write_templates
    state = {}
    if memo and (root / MEMO).is_file():
        try:
            state = json.loads((root / MEMO).read_text())
        except ValueError:
            state = {}
    hasher = Hasher(state.get('files', {}))
    lists = {}
    tfile = Path(templates_file) if templates_file else root / TEMPLATES
    tool_digest = sha256(Path(__file__).read_bytes())
    templates_digest = sha256(tfile.read_bytes()) if tfile.is_file() else 'none'
    stored = state.get('units', {})
    if state.get('schema') != 'closure_asm.memo.v1':
        stored = {}
    keys = [memo_key(root, u, hasher, tool_digest, templates_digest, lists) if memo else None for u in plan]
    hits, todo = {}, []
    for index, (u, key) in enumerate(zip(plan, keys)):
        entry = stored.get(u['route'] + '|' + u['name'])
        if key is not None and entry and entry[0] == key:
            hits[index] = entry[1]
        else:
            todo.append(index)
    computed = {}
    if todo:
        with concurrent.futures.ProcessPoolExecutor(max_workers=jobs) as pool:
            for index, result in zip(todo, pool.map(check_unit, [(root, plan[i], templates, blocks, sections) for i in todo], chunksize=16)):
                computed[index] = result
    results = []
    for index, u in enumerate(plan):
        if index in hits:
            results.append((u, hits[index], None))
        else:
            results.append(computed[index])
    newunits = {}
    for index, (u, uses, error) in enumerate(results):
        if memo and keys[index] is not None and error is None and not any(x['kind'].startswith('refused') for x in uses):
            newunits[u['route'] + '|' + u['name']] = [keys[index], [dict(kind=x['kind'], file=x['file'], line=x['line'], template=x.get('full', x['template'])) for x in uses]]
    if memo:
        try:
            (root / MEMO).parent.mkdir(parents=True, exist_ok=True)
            tmp = (root / MEMO).with_suffix('.tmp')
            tmp.write_text(json.dumps(dict(schema='closure_asm.memo.v1', units=newunits, files=hasher.fresh)))
            tmp.replace(root / MEMO)
        except OSError:
            pass
    if True:
        for unit, uses, error in results:
            per_route[unit['route']] = per_route.get(unit['route'], 0) + 1
            if error:
                errors.append((unit['name'], error))
            for use in uses:
                kind = use['kind']
                key = (kind, use['template'] if kind in ('template', 'block-listed') else '')
                if kind in ('template', 'block-listed', 'rename') or kind.startswith('refused'):
                    pass
                if kind in ('template', 'block-listed', 'refused-template'):
                    entry = seen_templates.setdefault((kind, use.get('full', use['template'])), dict(units=set(), uses=0))
                    entry['units'].add(unit['name'])
                    entry['uses'] += 1
                counts[kind] = counts.get(kind, 0) + 1
                if kind.startswith('refused'):
                    refusals.append((use['file'], use['line'], unit['name'], use['reason'], use['template'], kind, use))
    if write_templates:
        lines = ['# Assembler text a C unit of the build may carry; see docs/CLOSURE.md "Assembler in C units".',
                 '# template <json string>: an instruction-only template of an asm statement inside a function body.',
                 '# block <json string> <file> <sha256>: a file-scope block, exact text, whose included file is bound by hash;',
                 '#   a `.size name, N` block (no bytes) has - - instead.',
                 '# section <json string>: a code section name (.text...) that a section attribute may name.']
        for (kind, text), entry in sorted(seen_templates.items(), key=lambda kv: (kv[0][0], kv[0][1])):
            if kind in ('template', 'refused-template'):
                lines.append('template\t' + json.dumps(text))
        for refusal in refusals:
            if refusal[5] == 'refused-section' and refusal[4].startswith('.text'):
                lines.append('section\t' + json.dumps(refusal[4]))
            if refusal[5] == 'refused-block' and re.fullmatch(r'\.size [A-Za-z_0-9]+, \d+', refusal[6].get('full', '')):
                lines.append('block\t' + json.dumps(refusal[6]['full']) + '\t-\t-')
            if refusal[5] == 'refused-block':
                text = refusal[6].get('full', refusal[6]['template'])
                match = re.search(r'\.include "([^"]+)"', text)
                if match and (root / match.group(1)).is_file():
                    row = 'block\t' + json.dumps(text) + '\t' + match.group(1) + '\t' + sha256((root / match.group(1)).read_bytes())
                    if row not in lines:
                        lines.append(row)
        (root / TEMPLATES).write_text('\n'.join(dict.fromkeys(lines)) + '\n')
    refusals = sorted(set((f, l, n, r, t, k) for f, l, n, r, t, k, _ in refusals))
    for file, line, unit, reason, template, kind in refusals[:200]:
        print('%s:%s: refused: %s%s [unit %s]' % (file, line, reason, (' `' + template + '`') if template else '', unit))
    for item in problems:
        print('refused: ' + item)
    for name, error in errors[:20]:
        print('closure_asm: input error %s: %s' % (name, error))
    summary = dict(units=len(plan), per_route=per_route, counts=counts, refusals=len(refusals) + len(problems),
                   errors=len(errors),
                   templates=[dict(kind=k, text=t, units=len(e['units']), uses=e['uses'])
                              for (k, t), e in sorted(seen_templates.items())])
    print('closure_asm: %d units (%s); uses: %s; refusals %d%s' % (
        len(plan), ', '.join('%s %d' % kv for kv in sorted(per_route.items())),
        ', '.join('%s %d' % kv for kv in sorted(counts.items())) or 'none', len(refusals) + len(problems),
        '; input errors %d' % len(errors) if errors else ''))
    if census:
        Path(census).parent.mkdir(parents=True, exist_ok=True)
        Path(census).write_text(json.dumps(summary, indent=1) + '\n')
    if errors:
        return 2
    return 1 if refusals or problems else 0


def main(argv=None):
    sys.dont_write_bytecode = True
    parser = argparse.ArgumentParser(description=__doc__.split('\n')[0])
    parser.add_argument('mode', choices=['check'])
    parser.add_argument('--census')
    parser.add_argument('--jobs', type=int, default=4)
    parser.add_argument('--write-templates', action='store_true')
    parser.add_argument('--root', default=str(ROOT))
    parser.add_argument('--templates', help='templates file (default: config/asm_templates.tsv of --root)')
    parser.add_argument('--no-memo', action='store_true', help='check every unit; read and write no memo')
    options = parser.parse_args(argv)
    return run(options.root, min(options.jobs, 4), options.census, options.write_templates, options.templates, not options.no_memo)


if __name__ == '__main__':
    sys.exit(main())
