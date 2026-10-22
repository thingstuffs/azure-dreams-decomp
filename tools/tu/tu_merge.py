#!/usr/bin/env python3
"""Merge proven original-TU members into native overlay modules.

One spec = one proven TU span (or proven parts of one TU) of one image, as listed
by boundary_map.py.  Three steps, each re-runnable:

  draft    freeze the member sources, extract each member's single definition
           (verbatim, retail order, with the comment block above it), reconcile
           the member preambles into one shared header (identical declarations
           deduplicated, compatible variants kept, every TU-defined function
           given its definition's prototype), write one source per module and
           compile it.  Conflicts the compiler rejects are written to
           conflicts.json; resolve them by editing DRAFT/tree/ by hand.
  prove    complete-TU object identity per module: the module object's code
           bytes and relocations must equal the in-order concatenation of the
           frozen compilation units at their registered recipes. An explicitly
           absorbed native module is compiled once as a complete TU. Switch
           table bytes and relocations must also match exactly.
  install  re-prove, then apply to the root: sources/header, member removal,
           ledger/layout.jsonl, ledger/layout_inline.jsonl, ledger/modules.jsonl,
           config/overlays/modules.json (imports classified from the module
           object), evidence documents, path rewrites in config/link and link,
           the physical build graph (overlay_module_gate.py --graph) and the
           module gate (retail + genuine ASPSX whole-TU) per module.  Every
           touched file is first frozen under --base; install.patch is written.

usage:
  tu_merge.py run SPEC.json --work DIR [--dry-run] [--base DIR] [--evidence EVDIR]
  tu_merge.py draft SPEC.json --work DIR [--evidence EVDIR]
  tu_merge.py own --work DIR      (72(f): a complete file owns its string pool; after draft, before prove)
  tu_merge.py prove --work DIR
  tu_merge.py install --work DIR --base DIR [--no-gate]
  tu_merge.py restore --work DIR --base DIR      (undo an install from the frozen copies)
  tu_merge.py spec OUT.json --span SPAN_ID --evidence EVDIR --work DIR   (spec skeleton for a lane)
  tu_merge.py spec OUT.json --group GID --groups groups.tsv --work DIR  (inferred group, decision 72(b))

SPEC.json:
  {"container": "town", "span": "town/engine#g1058",            (optional)
   "header": "include/town/shop/stat_display.h", "header_title": "...",
   "reviewer": "codex-lane-x", "basis": ["..."],                  (optional)
   "group": "G00520", "evidence_level": "inferred-strong",        (optional; 72(b) header line)
   "evidence": ["CL:town/func_8008D988", ...],
   "modules": [{"key": "town_shop_stat_display", "source": "src/town/shop/stat_display.c",
                "title": "...", "members": ["town/func_800B7CEC", ...]}, ...]}
A destination module may list absorb_modules: [existing_key, ...]. It must
include each complete old cohort. The old descriptors, declaration/evidence
hashes and inline records survive in the new absorption proof; allocated-data
modules and modules with existing placement descriptors require a separate
allocation/placement consolidation and are refused.
Optional evidence_level/evidence_ids fields are emitted in each source's opening
comment. runtime_anchors maps individually evidenced D_XXXXXXXX imports to a
declaration, basis and review_inputs (or evidence). Address-only views default
to one byte; explicit view_bytes records a bounded declaration view without
retail storage or allocation claims. They are never inferred from a range.
Exit codes: 0 ok, 2 draft conflicts, 3 identity differs, 4 install refused.
"""
from __future__ import annotations

import argparse
import difflib
import hashlib
import json
import os
import re
import shutil
import struct
import subprocess
import sys
import tempfile
from pathlib import Path

HERE = Path(__file__).resolve().parent
ROOT = HERE.parents[1]
# Compiler helpers may import through the shared toolchain symlink.
os.environ.setdefault('PYTHONDONTWRITEBYTECODE', '1')
RECIPES = {  # same closed table as tools/gate/overlay_module_gate.module_recipe
    '2.7.2-cdk-G0': ('2.7.2-cdk', ('-O2', '-G0')),
    '2.7.2-G0': ('2.7.2', ('-O2', '-G0')),
    '2.7.2-cdk-G0 -O1': ('2.7.2-cdk', ('-O2', '-G0', '-O1')),
    '2.6.3-G0': ('2.6.3', ('-O2', '-G0')),        # MAIN devkit card files (tu7; module gate table too)
}
# per-member cells a module may be re-attributed FROM (decision 72(c)); compiled only on the member side
MEMBER_CELLS = dict(RECIPES, **{
    '2.7.2': ('2.7.2', ('-O2',)),
    '2.6.3': ('2.6.3', ('-O2',)),
    '2.7.2-cdk': ('2.7.2-cdk', ('-O2',)),
})
SLUS_RESIDENT = (0x8002D000, 0x80088760)
# SLUS-managed runtime storage below the overlay window: the fixed game-state region that SLUS
# func_8003D468 clears and restores (precedent import: module dungeon_floor_spawns, 8340 B view)
SLUS_MANAGED = ((0x80010000, 0x80010000 + 8340),)
CONTAINER_BIN = {'main': 'MAIN_MAIN.BIN', 'town': 'TOWN_TOWN.BIN', 'dungeon': 'DUNGEON_DUNGEON.BIN',
                 'ovmovie': 'OVMOVIE.BIN'}


class Refused(Exception):
    pass


def jl(path):
    return [json.loads(l) for l in Path(path).read_text().splitlines() if l.strip() and not l.lstrip().startswith('#')]


def wjl(path, records, compact=True):
    sep = (',', ':') if compact else None
    Path(path).write_text(''.join(json.dumps(r, separators=sep) + '\n' for r in records))


def sha256(b):
    return hashlib.sha256(b if isinstance(b, bytes) else b.encode()).hexdigest()


# ------------------------------------------------------------------ C text

def mask(source):
    """Blank comments, literals and directives (offsets kept)."""
    sys.path.insert(0, str(ROOT / 'tools/build'))
    from slus_partitions import lexical_mask
    return lexical_mask(source)


DEF = re.compile(r'^[ \t]*[A-Za-z_][A-Za-z0-9_ \t\n*]*?\b([A-Za-z_][A-Za-z0-9_]*)\s*\([^;{}]*\)\s*\{', re.M)


# C89 identifier-list definitions can narrow a promoted word argument in the
# parameter declaration. A shared typed prototype still specifies the ABI.
KR_DEF = re.compile(r'^[ \t]*[A-Za-z_][A-Za-z0-9_ \t\n*]*?\b([A-Za-z_]\w*)\s*'
                    r'\(([A-Za-z_]\w*(?:\s*,\s*[A-Za-z_]\w*)*)\)\s*'
                    r'((?:[A-Za-z_][A-Za-z0-9_ \t*,]*;\s*)+)\{', re.M)


def definitions(source):
    masked, directives = mask(source)
    depth, level = [], 0
    for c in masked:
        depth.append(level)
        level += (c == '{') - (c == '}')
    out = []
    matches = list(DEF.finditer(masked))
    for m in KR_DEF.finditer(masked):
        params = [x.strip() for x in m[2].split(',')]
        declared = [re.search(r'(\w+)\s*$', declarator.strip())[1]
                    for declaration in m[3].split(';') if declaration.strip()
                    for declarator in declaration.split(',')]
        if len(params) == len(set(params)) and sorted(params) == sorted(declared):
            matches.append(m)
    for m in sorted(matches, key=lambda x: x.start()):
        if depth[m.start()]:
            continue
        brace = m.end() - 1
        end, bal = brace + 1, 1
        while bal:
            bal += (masked[end] == '{') - (masked[end] == '}')
            end += 1
        out.append((m.group(1), m.start(), brace, end))
    return out, masked, directives


def split_statements(pre):
    """Top-level statements of a preamble: (comment, text) pairs, comments attached forward."""
    masked, directives = mask(pre)
    stmts, pending, i, n = [], [], 0, len(pre)
    dir_at = {a: (a, b) for a, b, _ in directives}
    while i < n:
        if pre[i].isspace():
            i += 1
            continue
        if i in dir_at:
            a, b = dir_at[i]
            if re.match(r'#\s*if', pre[a:b]):
                # keep a conditional block whole, up to its matching #endif
                level, order = 0, sorted(dir_at.values())
                for x, y in order:
                    if x < a:
                        continue
                    d = pre[x:y]
                    level += bool(re.match(r'#\s*if', d)) - bool(re.match(r'#\s*endif', d))
                    if level == 0:
                        b = y
                        break
            stmts.append((''.join(pending), pre[a:b]))
            pending = []
            i = b
            continue
        if pre.startswith('/*', i) or pre.startswith('//', i):
            end = pre.find('*/', i + 2) + 2 if pre.startswith('/*', i) else pre.find('\n', i)
            end = n if end < 2 else end
            pending.append(pre[i:end] + '\n')
            i = end
            continue
        # declaration: up to ';' at brace/paren depth 0 in masked text
        j, depth = i, 0
        while j < n:
            c = masked[j]
            if c in '{(':
                depth += 1
            elif c in '})':
                depth -= 1
            elif c == ';' and depth == 0:
                break
            j += 1
        stmts.append((''.join(pending), pre[i:j + 1]))
        pending = []
        i = j + 1
    if pending:
        stmts.append((''.join(pending), ''))
    return stmts


def strip_comments(text):
    if text.lstrip().startswith('#'):
        return ' '.join(text.split())
    return ' '.join(mask(text)[0].split())


def param_types(proto):
    """Return type and parameter types of a prototype, parameter names dropped."""
    t = ' '.join(mask(proto)[0].replace('extern', ' ').split()).rstrip(';')
    m = re.match(r'(.*?)\b(\w+)\s*\((.*)\)\s*$', t)
    if not m:
        return t
    params = []
    for p in [x.strip() for x in m[3].split(',')]:
        q = re.sub(r'\s*\*\s*', '*', p)
        words = q.replace('*', '* ').split()
        if len(words) > 1 and re.fullmatch(r'[A-Za-z_]\w*', words[-1]) and words[-1] not in (
                'int', 'char', 'short', 'long', 'void', 'unsigned', 'signed', 'float', 'double'):
            words = words[:-1]
        params.append(''.join(words))
    params = [x for x in params if x not in ('', 'void')]
    return (re.sub(r'\s*\*\s*', '*', m[1].strip()).replace(' ', ''), tuple(params))


def classify(text):
    """(kind, keys) of one statement."""
    t = text.strip()
    if not t:
        return 'comment', ()
    if t.startswith('#'):
        m = re.match(r'#\s*include\s*([<"][^>"]+[>"])', t)
        if m:
            return 'include', (m[1],)
        m = re.fullmatch(r'#\s*ifndef\s+(\w+)\s*\n\s*#\s*define\s+\1\b[^\n]*\n\s*#\s*endif\b.*', t, re.S)
        if m:
            return 'define', (m[1],)
        m = re.match(r'#\s*define\s+(\w+)', t)
        if m:
            return 'define', (m[1],)
        return 'directive', (t,)
    body = ' '.join(mask(t)[0].split())
    flat = re.sub(r'\{.*\}', '{}', body)
    if flat.startswith('typedef'):
        m = re.search(r'\(\s*\*\s*(\w+)\s*\)', flat) or re.search(r'(\w+)\s*(\[[^\]]*\]\s*)*;$', flat)
        return 'type', (m[1] if m else flat,)
    m = re.match(r'(struct|union|enum)\s+(\w+)\s*\{', flat)
    if m:
        return 'type', (m[1] + ' ' + m[2],)
    m = re.match(r'(struct|union|enum)\s+(\w+)\s*;$', flat)
    if m:
        return 'fwd', (m[1] + ' ' + m[2],)
    flat = re.sub(r'__attribute__\s*\(\(.*?\)\)', '', flat)
    keys = []
    for decl in re.split(r',(?![^()]*\))', flat.rstrip(';')):
        m = re.search(r'\(\s*\*\s*(\w+)\s*\)', decl)
        if not m:
            m = re.search(r'(\w+)\s*\(', decl)
        if not m:
            m = re.search(r'(\w+)\s*(\[[^\]]*\]\s*)*(=.*)?$', decl.strip())
        if m:
            keys.append(m[1])
    head = flat.split('=')[0]
    if 'extern' in head.split() or ('(' in head and '=' not in flat):
        return 'decl', tuple(keys)
    return 'data_definition', tuple(keys)


def evidence_line(spec):
    """Decision 72(b): the file's evidence level and evidence ids, stated in its header comment."""
    lvl = spec.get('evidence_level')
    if not lvl:
        return ''
    kind = {'proven': 'proven (string literals)'}.get(lvl, 'inferred (adjacency/recipe/locality), %s' % lvl)
    if spec.get('group'):
        kind += ' - group ' + spec['group']
    ids = spec.get('evidence') or []
    shown = ', '.join(ids[:8]) + (' (+%d more)' % (len(ids) - 8) if len(ids) > 8 else '')
    return 'Original-file evidence: %s%s.' % (kind, (' - ' + shown) if shown else '')


# --------------------------------------------------------------- compiling

def compile_obj(root, src, cfg, work, name, includes=()):
    cell, flags = MEMBER_CELLS[cfg]
    cc = root / 'toolchain/compilers' / ('gcc-' + cell)
    s = work / (name + '.s')
    r = subprocess.run([str(cc / 'gcc'), '-B' + str(cc) + '/', '-S', *flags, *['-I' + str(i) for i in includes],
                        '-I' + str(root / 'include'), '-I' + str(Path(src).parent), '-w', str(src), '-o', str(s)],
                       capture_output=True, text=True)
    if r.returncode:
        return None, r.stderr
    proc = subprocess.run([sys.executable, str(root / 'tools/gate/ccproc.py'), '--names-tsv',
                           str(root / 'config/names.tsv')], input=s.read_bytes(), check=True,
                          capture_output=True).stdout
    o = work / (name + '.o')
    r = subprocess.run([str(root / '.venv/bin/python'), str(root / 'toolchain/maspsx/maspsx.py'),
                        '--aspsx-version=2.79', '--run-assembler', '--gnu-as-path=mipsel-linux-gnu-as',
                        '-I' + str(root), '-I' + str(root / 'include'), '-EL', '-march=r3000', '-G0', '-o', str(o)],
                       input=proc, capture_output=True)
    if r.returncode:
        return None, r.stderr.decode(errors='replace')
    return o, ''


IGNORED = ('.reginfo', '.MIPS.abiflags', '.pdr', '.gnu.attributes', '.comment', '.mdebug')


def text_and_relocs(o):
    hdr = subprocess.run(['mipsel-linux-gnu-objdump', '-h', str(o)], check=True, capture_output=True,
                         text=True).stdout
    secs = []
    for line in hdr.splitlines():
        p = line.split()
        if len(p) >= 3 and p[0].isdigit():
            secs.append((p[1], int(p[2], 16)))
    data, relocs, other = b'', [], {}
    for name, size in secs:
        if not (name == '.text' or name.startswith('.text.')):
            if size and name not in IGNORED:
                other[name] = size
            continue
        if not size:
            continue
        raw = o.with_suffix('.sec.bin')
        subprocess.run(['mipsel-linux-gnu-objcopy', '-O', 'binary', '--only-section=' + name, str(o), str(raw)],
                       check=True, capture_output=True)
        chunk = raw.read_bytes()
        rel = subprocess.run(['mipsel-linux-gnu-objdump', '-r', '-j', name, str(o)], check=True,
                             capture_output=True, text=True).stdout
        for line in rel.splitlines():
            m = re.match(r'^([0-9a-f]{8})\s+(\S+)\s+(\S+)$', line)
            if m:
                relocs.append((int(m[1], 16) + len(data), m[2], m[3]))
        data += chunk
    return data, relocs, other


def section_data(o, name):
    """(bytes, relocations) of one named section of an object (b'', [] when absent)."""
    raw = o.with_suffix('.%s.bin' % name.strip('.'))
    r = subprocess.run(['mipsel-linux-gnu-objcopy', '-O', 'binary', '--only-section=' + name, str(o), str(raw)],
                       capture_output=True)
    if r.returncode or not raw.exists():
        return b'', []
    rel = subprocess.run(['mipsel-linux-gnu-objdump', '-r', '-j', name, str(o)], capture_output=True,
                         text=True).stdout
    relocs = [(int(m[1], 16), m[2], m[3]) for m in
              (re.match(r'^([0-9a-f]{8})\s+(\S+)\s+(\S+)$', l) for l in rel.splitlines()) if m]
    return raw.read_bytes(), relocs


# ------------------------------------------------------------------ draft

def load_repo(root):
    rows = {r['id']: r for r in jl(root / 'ledger/rows.jsonl')}
    layout = {r['id']: r['path'] for r in jl(root / 'ledger/layout.jsonl')}
    return rows, layout


def absorption_plan(root, spec):
    """Explicit, whole-module absorption. Never silently split an installed TU.

    The caller lists absorb_modules on the destination module. Its members must
    already include the complete old cohort, so the original-file evidence still
    describes the whole requested span. Allocated data and module placements need
    their own allocation/placement proof and are refused here.
    """
    path = root / 'config/overlays/modules.json'
    modules = json.loads(path.read_text())['modules'] if path.exists() else []
    old = {m['key']: m for m in modules}
    requested = {}
    all_ids = set()
    for mod in spec['modules']:
        ids = set(mod['members'])
        if len(ids) != len(mod['members']) or ids & all_ids:
            raise Refused('duplicate member in merge specification')
        all_ids |= ids
        keys = mod.get('absorb_modules', [])
        for key in keys:
            if key not in old or key in requested:
                raise Refused('unknown or repeated absorbed module: ' + key)
            entry = old[key]
            cohort = {a['id'] for a in entry['members']}
            if not cohort <= ids or entry['container'] != spec['container']:
                raise Refused('absorption must include the complete module: ' + key)
            if entry.get('owned_data') or entry.get('allocations') or entry.get('data_members'):
                raise Refused('absorbed module owns allocated data: ' + key)
            requested[key] = entry
        overlaps = {m['key'] for m in modules if ids & {a['id'] for a in m['members']}}
        if overlaps != set(keys):
            raise Refused('existing module overlap needs explicit absorb_modules: ' + ', '.join(sorted(overlaps)))
    placements = root / 'config/overlays/module_placements.json'
    if placements.exists():
        doc = json.loads(placements.read_text())
        for placement in doc.get('placements', []):
            if placement['module'] in requested:
                raise Refused('absorbed module has existing placements: ' + placement['module'])
    return requested


def absorbed_preamble(root, text, headers, new_header):
    """Move private native contracts through the normal declaration reconciler.

    Leaving an absorbed header as an opaque include would retain the obsolete
    function prototypes alongside their freshly reconciled definitions. Shared
    contracts remain includes; relative includes retain their original target.
    """
    def expand(match):
        token = match[1]
        rel = 'include/' + token
        if rel not in headers:
            return match[0]
        source = (root / rel).read_text()
        source = re.sub(r'\A\s*#ifndef\s+(\w+)\s*\n\s*#define\s+\1\s*\n', '', source)
        source = re.sub(r'\n\s*#endif\s*(?:/\*[^\n]*\*/)?\s*\Z', '\n', source)
        def include(m):
            local = Path(os.path.normpath(Path(rel).parent / m[1]))
            target = local if (root / local).is_file() else Path('include') / m[1]
            token = str(target.relative_to('include')) if target.parts[0] == 'include' else os.path.relpath(target, Path(new_header).parent)
            return '#include "%s"' % token
        return re.sub(r'#\s*include\s*"([^"]+)"', include, source)
    return re.sub(r'#\s*include\s*"([^"]+)"', expand, text)


def draft(root, spec, work, evidence=None, force=False):
    rows, layout = load_repo(root)
    absorbed = absorption_plan(root, spec)
    by_member = {a['id']: old for old in absorbed.values() for a in old['members']}
    container = spec['container']
    members = []
    for m in spec['modules']:
        for rid in m['members']:
            r = rows[rid]
            if r['container'] != container or r.get('row_kind') == 'data':
                raise Refused('member %s is not a %s function row' % (rid, container))
            if r.get('source_row') or not r.get('exists', True):
                raise Refused('member %s is a twin without its own source' % rid)
            members.append(dict(id=rid, path=layout.get(rid) or r['c_path'], cfg=r['cfg'],
                                row_asflags=r.get('row_asflags') or '', foff=r['foff'], size=r['size'],
                                function=r.get('true_name') or r['func'], module=m['key']))
            if rid in by_member:
                old = by_member[rid]
                if members[-1]['path'] != old['source'] or r['cfg'] != old['recipe']['cfg']:
                    raise Refused('absorbed source/recipe disagrees with registry: ' + rid)
                members[-1]['absorbed_module'] = old['key']
    order = sorted(members, key=lambda x: x['foff'])
    if order != members:
        raise Refused('members must be listed in retail order')
    for a, b in zip(members, members[1:]):
        if a['module'] == b['module'] and a['foff'] + a['size'] != b['foff']:
            raise Refused('module members are not contiguous: %s -> %s' % (a['id'], b['id']))
    for path in {m['path'] for m in members}:
        same = [m for m in members if m['path'] == path]
        if len(same) > 1 and any('absorbed_module' not in m for m in same):
            raise Refused('a member file holds several members without registered absorption: ' + path)
    for key in {m['module'] for m in members}:
        cfgs = {(m['cfg'], m['row_asflags']) for m in members if m['module'] == key}
        override = spec.get('recipe')
        if override:
            # decision 72(c): one recipe per file; prove() requires the merged file under it to equal
            # the members compiled at their registered cells
            if override not in RECIPES:
                raise Refused('recipe override %r not supported by the module gate' % override)
            if any(asf for _, asf in cfgs) or any(c not in MEMBER_CELLS for c, _ in cfgs):
                raise Refused('member cells %s cannot be compiled for the 72(c) proof' % sorted(cfgs))
            for m in members:
                if m['module'] == key:
                    m['registered_cfg'] = m['cfg']
            continue
        if len(cfgs) != 1:
            raise Refused('mixed registered recipes in module %s: %s (decision 72(c): set spec "recipe")'
                          % (key, sorted(cfgs)))
        cfg, asf = cfgs.pop()
        if cfg not in RECIPES or asf:
            raise Refused('module recipe %r/%r not supported by the module gate' % (cfg, asf))
    if work.exists():
        if not force:
            raise Refused('work directory exists (hand edits in tree/ would be lost); pass --force to re-draft')
        shutil.rmtree(work)
    (work / 'pre').mkdir(parents=True)
    (work / 'tree').mkdir()
    (work / 'spec.json').write_text(json.dumps(spec, indent=1) + '\n')
    # Freeze the old descriptor and every declaration/evidence input. The proof
    # compiles the complete old source once, rather than recompiling extracted
    # functions as if they had been independent TUs.
    frozen = {}
    for old in absorbed.values():
        for rel in set(old['headers'] + old['review_inputs'] + header_closure(root, old['source'])):
            if (root / rel).is_file():
                frozen[rel] = sha256((root / rel).read_bytes())
                dst = work / 'pre' / rel
                dst.parent.mkdir(parents=True, exist_ok=True)
                shutil.copy2(root / rel, dst)
                # Rebased private headers may include source-relative contracts.
                # Make the draft tree self-contained under the same paths too.
                target = work / 'tree' / rel
                target.parent.mkdir(parents=True, exist_ok=True)
                shutil.copy2(root / rel, target)
    (work / 'absorption.json').write_text(json.dumps(dict(modules=list(absorbed.values()), inputs=frozen), indent=1) + '\n')
    groups = []  # (kind, keys, comment, text, member index)
    bodies, defs, used = [], [], []
    conflicts = []
    for mi, m in enumerate(members):
        src = (root / m['path']).read_text()
        dst = work / 'pre' / m['path']
        dst.parent.mkdir(parents=True, exist_ok=True)
        dst.write_text(src)
        found, masked, directives = definitions(src)
        if not found:
            raise Refused('%s: no function definition' % m['path'])
        public = [f for f in found if not re.match(r'\s*static\b', src[f[1]:f[2]])]
        all_found = found
        all_public = public
        if 'absorbed_module' in m:
            # Names in native manifests are canonical assembler symbols; C may
            # use the readable spelling registered for the same address.
            aliases = {}
            for line in (root / 'config/names.tsv').read_text().splitlines():
                f = line.split('\t')
                if len(f) >= 3:
                    aliases[f[2]] = f[1]
            expected = [a['function'] for a in absorbed[m['absorbed_module']]['members']]
            if [aliases.get(f[0], f[0]) for f in public] != expected:
                raise Refused('absorbed complete definition inventory differs: ' + m['path'])
            public = [f for f in public if aliases.get(f[0], f[0]) == m['function']]
            # Helpers preceding this public definition stay with it. Deduplication
            # and complete-object identity still reject changed emission/locality.
            pidx = all_found.index(public[0])
            prev = max((all_found.index(f) for f in all_public if all_found.index(f) < pidx), default=-1)
            found = all_found[prev + 1:pidx + 1]
        if len(public) != 1:
            raise Refused('%s: expected one non-static definition, found %s' % (m['path'], [f[0] for f in public]))
        start, end = found[0][1], found[-1][3]
        # Only reviewed, verbatim function-local macros may remain in place.
        # Conditional directives require a separate reconstruction.
        for a, b, _ in directives:
            if start < a < end:
                directive = src[a:b].strip()
                if not (re.match(r'#\s*(define|undef)\b', directive)
                        and directive in spec.get('body_directives', [])):
                    raise Refused('%s: preprocessor directive inside the definitions' % m['path'])
        for (_, _, _, e1), (_, s2, _, _) in zip(found, found[1:]):
            between = src[e1:s2]
            if mask(between)[0].strip():
                raise Refused('%s: declarations between definitions' % m['path'])
        head = src[:start]
        hit = re.search(r'(/\*(?:[^*]|\*(?!/))*\*/\s*)$', head)
        cut = hit.start() if hit else start
        name, _, brace, pend = public[0]
        pieces = []
        for k, (fname, fs, fb, fe) in enumerate(found):
            ps = cut if k == 0 else found[k - 1][3]
            static = fname != name
            pieces.append(dict(name=fname, static=static, text=src[ps:fe].strip('\n') + '\n',
                               norm=' '.join(mask(src[fs:fe])[0].split())))
        pi = found.index(public[0])
        pre_public = src[cut if pi == 0 else found[pi - 1][3]:public[0][1]].lstrip('\n')
        bodies.append([pre_public, src[public[0][1]:brace + 1], src[brace + 1:pend], pieces])
        used.append(set(re.findall(r'[A-Za-z_]\w*', masked[start:end])))
        proto = ' '.join(src[public[0][1]:brace].split()) + ';'
        defs.append((name, proto, m))
        m['name'] = name
        m['first'] = found[0][0]
        tail = all_found[-1][3] if 'absorbed_module' in m else end
        if src[tail:].strip() and mask(src[tail:])[0].strip():
            raise Refused('%s: code after the definitions' % m['path'])
        preamble = src[:all_found[0][1]] if 'absorbed_module' in m else head[:cut]
        private_headers = {h for old in absorbed.values() for h in old['headers']
                           if h.startswith('include/') and h != 'include/common.h'}
        preamble = absorbed_preamble(root, preamble, private_headers, spec['header'])
        for comment, text in split_statements(preamble):
            kind, keys = classify(text)
            groups.append((kind, keys, comment, text, mi))
    defined = {n for n, _, _ in defs}
    defs_all = defs
    aliases = {}
    for line in (root / 'config/names.tsv').read_text().splitlines():
        f = line.split('\t')
        if len(f) >= 3 and f[1].startswith('func_'):
            aliases[f[2]] = f[1]
    defined_canon = defined | {aliases[n] for n in defined if n in aliases}
    # declarations: key -> variants -> declaring members
    decl_variants, decl_text = {}, {}
    seen, out = {}, {'include': [], 'define': [], 'type': [], 'decl': []}
    block = [[] for _ in members]   # per-member block-scope declarations
    placement = []
    for kind, keys, comment, text, mi in groups:
        mid = members[mi]['id']
        if kind == 'comment':
            continue
        if kind == 'directive':
            conflicts.append(dict(kind='conditional_or_other_directive', text=text.strip(), member=mid))
            continue
        if kind == 'data_definition':
            conflicts.append(dict(kind='data_definition_in_member', text=text.strip(), member=mid))
            continue
        if kind == 'decl' and set(keys) & defined_canon:
            if len(keys) > 1:
                conflicts.append(dict(kind='mixed_declaration_of_tu_function', text=text.strip(), member=mid))
            else:
                own = next((pr for n_, pr, _ in defs_all if n_ in keys or aliases.get(n_) in keys), None)
                if own and param_types(own) != param_types(text):
                    conflicts.append(dict(kind='tu_function_prototype_differs', key=list(keys), member=mid,
                                          member_declaration=' '.join(text.split()), definition=own))
            continue  # replaced by the definition's own prototype
        norm = strip_comments(text)
        if kind == 'decl':
            for k in keys:
                decl_variants.setdefault(k, {}).setdefault(norm, set()).add(mi)
            decl_text.setdefault(norm, (comment, text.strip(), keys))
            continue
        sk = (kind if kind != 'fwd' else 'type', keys)
        variants = seen.setdefault(sk, [])
        if norm in variants:
            continue
        if variants and kind in ('define', 'type'):
            conflicts.append(dict(kind='redefinition', key=list(keys), text=text.strip(), member=mid))
        variants.append(norm)
        out['type' if kind == 'fwd' else kind].append((comment, text.strip()))
    # A declaration goes to the shared header only when every member that declares it
    # agrees and every member body that uses it declared it; otherwise each declaring
    # member that uses it keeps its own view at block scope (codegen unchanged).
    shared_norms, emitted = set(), set()
    for norm, (comment, text, keys) in decl_text.items():
        stmt_ok = True
        for k in keys:
            vs = decl_variants[k]
            declarers = set().union(*vs.values())
            users = {i for i in range(len(members)) if k in used[i]}
            if len(vs) != 1 or not users <= declarers:
                stmt_ok = False
                undeclared = sorted(members[i]['id'] for i in users - declarers)
                if undeclared:
                    conflicts.append(dict(kind='implicit_user', key=k, members=undeclared))
        if stmt_ok:
            shared_norms.add(norm)
            out['decl'].append((comment, text))
            placement.append(dict(decl=text, scope='file'))
    for kind, keys, comment, text, mi in groups:
        if kind != 'decl' or set(keys) & defined_canon:
            continue
        norm = strip_comments(text)
        if norm in shared_norms or (mi, norm) in emitted:
            continue
        emitted.add((mi, norm))
        if set(keys) & used[mi]:
            block[mi].append(text.strip())
            placement.append(dict(decl=text.strip(), scope='block', member=members[mi]['id']))
    seen_static = {}
    assembled = []
    for i, (c, h, b, pieces) in enumerate(bodies):
        decls = block[i]
        if decls:
            b = '\n' + ''.join('    %s\n' % d for d in decls) + b.lstrip('\n')
        parts = []
        for pc in pieces:
            if pc['static']:
                prev = seen_static.get(pc['name'])
                if prev == pc['norm']:
                    continue  # identical static helper already defined earlier in the TU
                if prev is not None:
                    conflicts.append(dict(kind='redefinition', key=[pc['name']], member=members[i]['id'],
                                          text='static helper with a different body'))
                seen_static[pc['name']] = pc['norm']
                parts.append(pc['text'])
            else:
                parts.append((c + h + b).strip('\n') + '\n')
        assembled.append('\n'.join(parts))
    bodies = assembled
    (work / 'placement.json').write_text(json.dumps(placement, indent=1) + '\n')
    inc = out['include']
    inc.sort(key=lambda x: 0 if x[1].endswith('"common.h"') else 1)
    hdr = spec['header']
    guard = re.sub(r'[^A-Z0-9]', '_', hdr[len('include/'):].upper())
    lines = ['#ifndef ' + guard, '#define ' + guard, '/* %s */' % spec.get('header_title', 'Shared declarations.')]
    if evidence_line(spec):
        lines.append('/* %s */' % evidence_line(spec))
    for sec in ('include', 'define', 'type', 'decl'):
        if not out[sec]:
            continue
        lines.append('')
        for comment, text in out[sec]:
            if comment.strip():
                lines.append(comment.rstrip('\n'))
            lines.append(text)
            if sec == 'type':
                lines.append('')
    lines += ['', '/* Functions defined in this translation unit. */']
    lines += [p for _, p, _ in defs]
    lines += ['', '#endif', '']
    text = re.sub(r'\n{3,}', '\n\n', '\n'.join(lines))
    (work / 'tree' / hdr).parent.mkdir(parents=True, exist_ok=True)
    (work / 'tree' / hdr).write_text(text)
    for mod in spec['modules']:
        ms = [b for b, m in zip(bodies, members) if m['module'] == mod['key']]
        comment = '/* %s' % mod.get('title', mod['key'])
        if spec.get('evidence_level'):
            comment += '\n * ' + evidence_line(spec)
            for eid in spec.get('evidence_ids', []):
                comment += '\n * %s' % eid
        elif evidence_line(spec):
            comment += '\n * %s' % evidence_line(spec)
        comment += '\n */' if '\n' in comment else ' */'
        src = comment + '\n#include "%s"\n\n' % hdr[len('include/'):] + '\n'.join(ms)
        (work / 'tree' / mod['source']).parent.mkdir(parents=True, exist_ok=True)
        (work / 'tree' / mod['source']).write_text(src)
    (work / 'members.json').write_text(json.dumps(members, indent=1) + '\n')
    # compile check
    with tempfile.TemporaryDirectory(prefix='tu-draft-') as td:
        for mod in spec['modules']:
            cfg = spec.get('recipe') or next(m['cfg'] for m in members if m['module'] == mod['key'])
            o, err = compile_obj(root, work / 'tree' / mod['source'], cfg, Path(td), mod['key'],
                                 includes=[work / 'tree/include'])
            if o is None:
                lines = [l.strip() for l in err.splitlines() if l.strip() and 'In function' not in l] or ['failed']
                for line in lines:
                    conflicts.append(dict(kind='compiler', module=mod['key'], message=line))
    (work / 'conflicts.json').write_text(json.dumps(conflicts, indent=1) + '\n')
    blocking = [c for c in conflicts if c['kind'] in ('compiler', 'conditional_or_other_directive', 'redefinition',
                                                      'data_definition_in_member', 'mixed_declaration_of_tu_function')]
    return members, conflicts, blocking


# ------------------------------------------------------------- 72(f) literals

def c_string(b):
    """A C string literal for retail bytes (octal escapes: no hex-digit run-on)."""
    out = []
    for c in b:
        if c == 0x22:
            out.append('\\"')
        elif c == 0x5C:
            out.append('\\\\')
        elif 0x20 <= c < 0x7F:
            out.append(chr(c))
        elif c == 10:
            out.append('\\n')
        else:
            out.append('\\%03o' % c)
    return '"' + ''.join(out) + '"'


def proven_region(root, container, lo, hi):
    regions = [r for r in jl(root / ('config/overlays/%s.rowbase.jsonl' % container)) if r['base_confidence'] == 'proven']
    reg = [r for r in regions if int(r['foff_start'], 0) <= lo and hi <= int(r['foff_end'], 0)]
    if len(reg) != 1:
        raise Refused('no unique proven load region holds 0x%X-0x%X (%d)' % (lo, hi, len(reg)))
    return reg[0]


def own_literals(root, work):
    """Decision 72(f): a COMPLETE file owns its .rdata string pool as C literals.  The draft's
    imported string symbols D_<addr> become `static const char D_<addr>[] = "...";` definitions in
    the module source (address order; bodies untouched).  The import variant stays in
    tree_imports/ for the member identity proof; the owned pool must tile one contiguous retail
    run exactly (each string at the next 4-byte boundary, zero gaps) - any unowned byte refuses."""
    spec = json.loads((work / 'spec.json').read_text())
    if not spec.get('complete_evidence'):
        raise Refused('72(f) applies to complete files only: spec "complete_evidence" must cite both proven edges')
    if len(spec['modules']) != 1:
        raise Refused('literal ownership needs the whole file in one module')
    members = json.loads((work / 'members.json').read_text())
    mod = spec['modules'][0]
    container = spec['container']
    region = proven_region(root, container, members[0]['foff'], members[-1]['foff'] + members[-1]['size'])
    delta = int(region['delta'], 0)
    blob = (root / {'main': 'work/disc/containers/MAIN_MAIN.BIN', 'town': 'work/disc/containers/TOWN_TOWN.BIN',
                    'dungeon': 'work/disc/containers/DUNGEON_DUNGEON.BIN',
                    'ovmovie': 'work/disc/containers/OVMOVIE.BIN'}[container]).read_bytes()
    if not (work / 'tree_imports').exists():
        shutil.copytree(work / 'tree', work / 'tree_imports')
    cfg = spec.get('recipe') or members[0]['cfg']
    with tempfile.TemporaryDirectory(prefix='tu-own-') as td:
        o, err = compile_obj(root, work / 'tree_imports' / mod['source'], cfg, Path(td), 'm',
                             includes=[work / 'tree_imports/include'])
        if o is None:
            raise Refused('import variant does not compile: ' + err[-300:])
        nm = subprocess.run(['mipsel-linux-gnu-nm', str(o)], check=True, capture_output=True, text=True).stdout
    undefined = sorted(l.split()[1] for l in nm.splitlines() if l.split()[0] == 'U')
    owned = []
    for sym in undefined:
        m_ = re.fullmatch(r'D_([0-9A-F]{8})', sym)
        if not m_:
            continue
        vma = int(m_[1], 16)
        foff = vma - delta
        if not int(region['foff_start'], 0) <= foff < int(region['foff_end'], 0):
            continue
        end = blob.find(b'\0', foff, foff + 512)
        text = blob[foff:end]
        if end <= foff or any(c < 0x20 and c not in (9, 10) for c in text):
            continue
        owned.append(dict(symbol=sym, vma=vma, foff=foff, size=end - foff + 1, text=text))
    if not owned:
        raise Refused('the file imports no string literal of its own region')
    owned.sort(key=lambda x: x['foff'])
    lo = owned[0]['foff']
    cursor = 0
    for x in owned:
        off = x['foff'] - lo
        if off != (cursor + 3) & ~3 or any(blob[lo + cursor:lo + off]):
            raise Refused('owned strings do not tile one pool: %s at +0x%X (expected +0x%X, gap %s)' % (
                x['symbol'], off, (cursor + 3) & ~3, blob[lo + cursor:lo + off].hex()))
        x['offset'] = off
        cursor = off + x['size']
    hdr = spec['header']
    names = {x['symbol'] for x in owned}
    # drop every declaration of an owned symbol (file scope in the header, block scope in bodies)
    for rel in (hdr, mod['source']):
        p = work / 'tree' / rel
        lines = p.read_text().splitlines(True)
        keep = []
        for line in lines:
            keys = set(re.findall(r'\bD_[0-9A-F]{8}\b', line))
            if keys & names and re.match(r'\s*extern\b', line):
                if keys - names:
                    raise Refused('declaration mixes owned and imported symbols: ' + line.strip())
                continue
            keep.append(line)
        p.write_text(''.join(keep))
    src = (work / 'tree' / mod['source']).read_text()
    inc = re.search(r'^#include "[^"]+"\n', src, re.M)
    defs = '\n/* .rdata string pool owned by this complete file (decision 72(f)). */\n' + ''.join(
        'static const char %s[] = %s;\n' % (x['symbol'], c_string(x['text'])) for x in owned)
    src = src[:inc.end()] + defs + src[inc.end():]
    (work / 'tree' / mod['source']).write_text(src)
    pool = dict(foff=lo, vma=lo + delta, size=cursor, region=region['region'],
                slots=[dict(symbol=x['symbol'], offset=x['offset'], size=x['size'], kind='typed_string',
                            source=mod['source']) for x in owned])
    (work / 'literals.json').write_text(json.dumps(pool, indent=1) + '\n')
    return pool


# ------------------------------------------------------------------ prove

def switch_payload_bytes(data, relocations):
    """Separate only zero GNU end alignment after a complete R_MIPS_32 table."""
    size = 4 * len(relocations)
    if (size and [(off, typ) for off, typ, _ in relocations] ==
            [(off, 'R_MIPS_32') for off in range(0, size, 4)]
            and size <= len(data) < size + 16 and not any(data[size:])):
        return size
    return len(data)


def prove(root, work):
    spec = json.loads((work / 'spec.json').read_text())
    members = json.loads((work / 'members.json').read_text())
    results = {}
    ok = True
    with tempfile.TemporaryDirectory(prefix='tu-identity-') as td:
        tdp = Path(td)
        for mod in spec['modules']:
            ms = [m for m in members if m['module'] == mod['key']]
            cfg = spec.get('recipe') or ms[0]['cfg']
            concat, crel, per = b'', [], []
            rodata, rodata_rel, switches = b'', [], []
            compiled_paths = set()
            for i, m in enumerate(ms):
                if m['path'] in compiled_paths:
                    continue
                compiled_paths.add(m['path'])
                unit = [x for x in ms if x['path'] == m['path']]
                # every member at its own registered cell (byte-exact rows); the merged file at the
                # module recipe - equal objects prove the one-recipe attribution of 72(c)
                o, err = compile_obj(root, work / 'pre' / m['path'], m.get('registered_cfg', m['cfg']), tdp,
                                     '%s_m%02d' % (mod['key'], i), includes=[work / 'pre/include'])
                if o is None:
                    raise Refused('member %s does not compile: %s' % (m['id'], err[-400:]))
                t, r, sec = text_and_relocs(o)
                size = sum(x['size'] for x in unit)
                if len(t) != size:
                    raise Refused('member %s complete object text %d != registered size %d' % (m['id'], len(t), size))
                crel += [(off + len(concat), typ, sym) for off, typ, sym in r]
                concat += t
                if set(sec) == {'.rodata'}:
                    # a compiler switch table: compared byte- and relocation-exact below (tu7)
                    rb, rr = section_data(o, '.rodata')
                    rodata_rel += [(off + len(rodata), typ, sym) for off, typ, sym in rr]
                    rodata += rb
                    payload = switch_payload_bytes(rb, rr)
                    switches.append(dict(id=m['id'], bytes=len(rb), payload_bytes=payload,
                                         end_padding=len(rb) - payload))
                    sec = {}
                per.append(dict(id=m['id'], members=[x['id'] for x in unit], text=len(t),
                                source=m['path'], other_sections=sec))
            tree = work / ('tree_imports' if (work / 'literals.json').exists() else 'tree')
            o, err = compile_obj(root, tree / mod['source'], cfg, tdp, mod['key'], includes=[tree / 'include'])
            if o is None:
                raise Refused('module %s does not compile: %s' % (mod['key'], err[-600:]))
            t, r, sec = text_and_relocs(o)
            if switches and set(sec) == {'.rodata'}:
                mb, mr = section_data(o, '.rodata')
                if mb == rodata and mr == rodata_rel:
                    sec = {}
                else:
                    sec = dict(sec, rodata_differs=True)
            res = dict(module=mod['key'], recipe=cfg, members=len(ms), member_text_bytes=len(concat),
                       switch_tables=switches,
                       switch_rodata_sha256=sha256(rodata) if switches else None,
                       switch_relocations=[list(x) for x in rodata_rel],
                       member_cells=sorted({m.get('registered_cfg', m['cfg']) for m in ms}),
                       merged_text_bytes=len(t), text_equal=t == concat, relocations_equal=r == crel,
                       relocations=len(r), merged_other_sections=sec,
                       member_other_sections=[p for p in per if p['other_sections']],
                       proof_units=per,
                       text_sha256=sha256(t))
            if r != crel:
                res['first_reloc_diff'] = next(([list(a), list(b)] for a, b in zip(r, crel) if a != b),
                                               ['length', len(r), len(crel)])
            if t != concat:
                res['first_text_diff'] = next((i for i in range(min(len(t), len(concat))) if t[i] != concat[i]),
                                              min(len(t), len(concat)))
            res['equal'] = bool(res['text_equal'] and res['relocations_equal'] and not sec
                                and not res['member_other_sections'])
            if (work / 'literals.json').exists():
                res['owned_literals'] = owned_pool_check(root, work, spec, mod, cfg, tdp)
                res['equal'] = res['equal'] and res['owned_literals']['rodata_equal_retail']
            ok &= res['equal']
            results[mod['key']] = res
            (work / ('identity_%s.json' % mod['key'])).write_text(json.dumps(res, indent=1) + '\n')
    return ok, results


def owned_pool_check(root, work, spec, mod, cfg, tdp):
    """The owning source compiles; its .rodata is exactly the retail pool (GNU zero end padding allowed)."""
    pool = json.loads((work / 'literals.json').read_text())
    o, err = compile_obj(root, work / 'tree' / mod['source'], cfg, tdp, mod['key'] + '_own', includes=[work / 'tree/include'])
    if o is None:
        raise Refused('owning module does not compile: ' + err[-600:])
    rb, rr = section_data(o, '.rodata')
    blob = (root / {'main': 'work/disc/containers/MAIN_MAIN.BIN', 'town': 'work/disc/containers/TOWN_TOWN.BIN',
                    'dungeon': 'work/disc/containers/DUNGEON_DUNGEON.BIN',
                    'ovmovie': 'work/disc/containers/OVMOVIE.BIN'}[spec['container']]).read_bytes()
    retail = blob[pool['foff']:pool['foff'] + pool['size']]
    return dict(pool_foff='0x%X' % pool['foff'], pool_bytes=pool['size'], strings=len(pool['slots']),
                compiled_rodata=len(rb), rodata_relocations=len(rr),
                rodata_equal_retail=rb[:pool['size']] == retail and not any(rb[pool['size']:]) and not rr)


# ---------------------------------------------------------------- install

class Freezer:
    def __init__(self, root, base):
        self.root, self.base = root, base
        self.touched = []
        base.mkdir(parents=True, exist_ok=True)
        lst = base / 'touched.json'
        self.absent = set(json.loads(lst.read_text())['absent']) if lst.exists() else set()
        if lst.exists():
            self.touched = json.loads(lst.read_text())['touched']

    def freeze(self, rel):
        if rel in self.touched:
            return
        self.touched.append(rel)
        src = self.root / rel
        if src.exists():
            dst = self.base / 'files' / rel
            dst.parent.mkdir(parents=True, exist_ok=True)
            shutil.copy2(src, dst)
        else:
            self.absent.add(rel)
        self.save()

    def save(self):
        (self.base / 'touched.json').write_text(json.dumps(dict(touched=self.touched, absent=sorted(self.absent)),
                                                           indent=1) + '\n')

    def write(self, rel, text):
        self.freeze(rel)
        p = self.root / rel
        p.parent.mkdir(parents=True, exist_ok=True)
        p.write_text(text)

    def remove(self, rel):
        self.freeze(rel)
        (self.root / rel).unlink()

    def patch(self):
        out = []
        for rel in sorted(self.touched):
            old = '' if rel in self.absent else (self.base / 'files' / rel).read_text()
            p = self.root / rel
            new = p.read_text() if p.exists() else ''
            if old == new:
                continue
            a = '/dev/null' if rel in self.absent else 'a/' + rel
            b = 'b/' + rel if p.exists() else '/dev/null'
            out.append('diff --git a/%s b/%s\n' % (rel, rel))
            out.extend(difflib.unified_diff(old.splitlines(True), new.splitlines(True), a, b, n=3))
        return ''.join(x if x.endswith('\n') else x + '\n\\ No newline at end of file\n' for x in out)


def resolve_function(root, sym, names):
    if re.fullmatch(r'func_[0-9A-F]{8}', sym):
        return int(sym[5:], 16)
    if sym in names:
        return names[sym]
    return None


def data_address(sym):
    """Address-named storage views may carry registered aliases such as _R."""
    match = re.fullmatch(r'D_([0-9A-F]{8})(?:_[A-Za-z0-9]+)*', sym)
    return int(match[1], 16) if match else None


def header_closure(root, hdr):
    seen, todo = [], [hdr]
    while todo:
        h = todo.pop(0)
        if h in seen or not (root / h).is_file():
            continue
        seen.append(h)
        for m in re.finditer(r'#\s*include\s*"([^"]+)"', (root / h).read_text()):
            options = [Path(h).parent / m[1], Path('include') / m[1], Path(m[1])]
            for option in options:
                rel = Path(os.path.normpath(option))
                if not rel.is_absolute() and '..' not in rel.parts and (root / rel).is_file():
                    todo.append(rel.as_posix())
                    break
    return seen


def rewrite_include_facade(text, facade, old_paths):
    """An optional natural-order include TU includes each new merged source once."""
    emitted, lines = set(), []
    parent = Path(facade).parent
    for line in text.splitlines(keepends=True):
        hit = re.match(r'\s*#\s*include\s*"([^"]+)"\s*$', line)
        target = os.path.normpath(parent / hit[1]) if hit else None
        if target not in old_paths:
            lines.append(line)
            continue
        new = old_paths[target]
        if new not in emitted:
            lines.append('#include "%s"\n' % os.path.relpath(new, parent))
            emitted.add(new)
    return ''.join(lines)


def rewrite_tu_aliases(records, retired):
    """Keep historical physical-TU aliases pointed at the surviving source."""
    out = [dict(r, new=retired.get(r['new'], r['new'])) for r in records]
    if len({r['new'] for r in out}) != len(out):
        raise Refused('absorption would combine multiple physical TU aliases; alias consolidation proof required')
    return out


def refresh_link_graph(root, work, fr):
    """Capture the physical graph through its producer, never edit its shards."""
    if not (root / 'config/link_graph/graph.json').exists():
        return None
    with tempfile.TemporaryDirectory(prefix='link-graph-', dir=work) as td:
        directory = Path(td)
        r = subprocess.run([sys.executable, str(root / 'tools/link/graph.py'), '--root', str(root),
                            '--graph', str(directory), 'capture'], capture_output=True, text=True)
        if r.returncode:
            raise Refused('physical link graph capture failed: ' + r.stderr[-1200:])
        old = {p.name for p in (root / 'config/link_graph').iterdir() if p.is_file()}
        new = {p.name for p in directory.iterdir() if p.is_file()}
        for name in sorted(old - new):
            fr.remove('config/link_graph/' + name)
        for name in sorted(new):
            fr.write('config/link_graph/' + name, (directory / name).read_text())
        receipt = json.loads(r.stdout)
        (work / 'link_graph_refresh.json').write_text(json.dumps(receipt, indent=1) + '\n')
        return receipt


def view_bytes(root, sym, header, cfg, blob, foff, limit, includes):
    """sizeof(sym) through the shared header; else retail string length; else 4."""
    with tempfile.TemporaryDirectory(prefix='tu-sizeof-') as td:
        c = Path(td) / 'probe.c'
        c.write_text('#include "%s"\nunsigned int tu_sizeof_probe = sizeof(%s);\n' % (header[len('include/'):], sym))
        cell, flags = RECIPES[cfg]
        cc = root / 'toolchain/compilers' / ('gcc-' + cell)
        r = subprocess.run([str(cc / 'gcc'), '-B' + str(cc) + '/', '-S', *flags, *['-I' + str(i) for i in includes],
                            '-I' + str(root / 'include'), '-w', str(c), '-o', str(Path(td) / 'p.s')],
                           capture_output=True, text=True)
        if r.returncode == 0:
            m = re.search(r'\.word\s+(\d+)', (Path(td) / 'p.s').read_text())
            if m and int(m[1]) > 0:
                return int(m[1]), 'sizeof'
    if blob is not None and foff is not None:
        end = blob.find(b'\0', foff, min(limit, foff + 512))
        if end > foff:
            return end - foff + 1, 'retail_string'
    return 4, 'word_default'


def install(root, work, base, gate=True, reviewer=None, evidence_dir=None, gate_out=None):
    """Transactional: a refusal after the first write restores every file this call touched."""
    before = []
    if (base / 'touched.json').exists():
        before = json.loads((base / 'touched.json').read_text())['touched']
    # files a previous install into this base already froze are snapshotted as they are NOW
    snap = {rel: ((root / rel).read_bytes() if (root / rel).exists() else None) for rel in before}
    try:
        return _install(root, work, base, gate, reviewer, evidence_dir, gate_out)
    except Exception:
        for rel, data in snap.items():
            p = root / rel
            if data is None:
                if p.exists():
                    p.unlink()
            elif not p.exists() or p.read_bytes() != data:
                p.parent.mkdir(parents=True, exist_ok=True)
                p.write_bytes(data)
        if (base / 'touched.json').exists():
            lst = json.loads((base / 'touched.json').read_text())
            mine = [r for r in lst['touched'] if r not in before]
            for rel in mine:
                p = root / rel
                if rel in lst['absent']:
                    if p.exists():
                        p.unlink()
                else:
                    shutil.copy2(base / 'files' / rel, p)
            lst['touched'] = before
            lst['absent'] = [a for a in lst['absent'] if a in before]
            (base / 'touched.json').write_text(json.dumps(lst, indent=1) + '\n')
        raise


def _install(root, work, base, gate=True, reviewer=None, evidence_dir=None, gate_out=None):
    spec = json.loads((work / 'spec.json').read_text())
    members = json.loads((work / 'members.json').read_text())
    for m in members:
        cur = root / m['path']
        if not cur.is_file() or cur.read_bytes() != (work / 'pre' / m['path']).read_bytes():
            raise Refused('member source changed since draft: %s; re-draft' % m['path'])
    ok, results = prove(root, work)
    if not ok:
        raise Refused('identity differs: ' + json.dumps({k: v['equal'] for k, v in results.items()}))
    rows, layout = load_repo(root)
    switch_rows = {key: switch_row(root, work, spec, members, key, res, rows)
                   for key, res in results.items() if res.get('switch_tables')}
    absorbed = absorption_plan(root, spec)
    absorption = json.loads((work / 'absorption.json').read_text()) if (work / 'absorption.json').exists() else {}
    if list(absorbed.values()) != absorption.get('modules', []):
        raise Refused('absorbed descriptor changed since draft; re-draft')
    for rel, expected in absorption.get('inputs', {}).items():
        if not (root / rel).is_file() or sha256((root / rel).read_bytes()) != expected:
            raise Refused('absorbed proof input changed since draft: ' + rel)
    container = spec['container']
    sys.path[:0] = [str(root / 'tools'), str(root / 'tools/gate')]
    # levels screen (the module gate repeats it)
    levels = {r['id']: r for r in jl(root / 'ledger/levels.jsonl')}
    for m in members:
        lv = levels.get(m['id'])
        if not lv or lv['level'] < 3 or lv['pins_left'] or lv['tail_jumps'] or set(lv['l4_residue']) - {'not_in_module'}:
            raise Refused('L3/placement screen fails for %s: %s' % (m['id'], lv and {k: lv[k] for k in (
                'level', 'pins_left', 'tail_jumps', 'l4_residue')}))
    mods_doc = json.loads((root / 'config/overlays/modules.json').read_text())
    mods_doc['modules'] = [x for x in mods_doc['modules'] if x['key'] not in absorbed]
    taken = {a['id'] for x in mods_doc['modules'] for a in x['members'] + x.get('data_members', [])}
    if taken & {m['id'] for m in members}:
        raise Refused('a member already belongs to a module')
    if taken & {r['id'] for r in switch_rows.values()}:
        raise Refused('a switch data row already belongs to a module')
    regions = [r for r in jl(root / ('config/overlays/%s.rowbase.jsonl' % container)) if r['base_confidence'] == 'proven']
    lo, hi = members[0]['foff'], members[-1]['foff'] + members[-1]['size']
    reg = [r for r in regions if int(r['foff_start'], 0) <= lo and hi <= int(r['foff_end'], 0)]
    if len(reg) != 1:
        raise Refused('no unique proven load region holds the span (%d)' % len(reg))
    region = reg[0]
    delta = int(region['delta'], 0)
    rlo, rhi = int(region['foff_start'], 0), int(region['foff_end'], 0)
    for m in members:
        tn = rows[m['id']].get('true_name') or ''
        if re.fullmatch(r'func_[0-9A-F]{8}', tn) and int(tn[5:], 16) != m['foff'] + delta:
            raise Refused('member %s true name disagrees with region delta' % m['id'])
    names = {}
    for line in (root / 'config/names.tsv').read_text().splitlines():
        f = line.split('\t')
        if len(f) >= 3 and f[0].startswith('0x'):
            names[f[2]] = int(f[0], 16)
    for line in (root / 'config/slus_006.14.symbols.txt').read_text().splitlines():
        m = re.match(r'\s*([A-Za-z_]\w*)\s*=\s*(0x[0-9A-Fa-f]+)\s*;', line)
        if m:
            names.setdefault(m[1], int(m[2], 16))
    for line in (root / 'config/overlays/abs_syms.txt').read_text().splitlines():
        m = re.match(r'\s*([A-Za-z_]\w*)\s*=\s*(0x[0-9A-Fa-f]+)\s*;', line)
        if m:
            names.setdefault(m[1], int(m[2], 16))
    blob = (root / {'main': 'work/disc/containers/MAIN_MAIN.BIN', 'town': 'work/disc/containers/TOWN_TOWN.BIN',
                    'dungeon': 'work/disc/containers/DUNGEON_DUNGEON.BIN',
                    'ovmovie': 'work/disc/containers/OVMOVIE.BIN'}[container]).read_bytes()
    hdr = spec['header']
    reviewer = reviewer or spec.get('reviewer') or 'tu-merge'
    # Explicit address-only runtime anchors may live outside the loaded SLUS
    # bytes (for example the CD image scratch buffers).  Keep these reviewed
    # claims separate from inferred data views and never claim retail storage.
    anchors = {sym: dict(anchor, declaration=anchor.get('declaration', hdr),
                        review_inputs=anchor.get('review_inputs', anchor.get('evidence', [])))
               for sym, anchor in spec.get('runtime_anchors', {}).items()}
    for old in absorbed.values():
        for d in old['imports']:
            if d['kind'] == 'runtime_data':
                anchors.setdefault(d['symbol'], dict(declaration=d['declaration'], view_bytes=d['view_bytes'],
                    basis='Reviewed runtime view retained from absorbed module ' + old['key'],
                    review_inputs=[d['evidence']]))
    for sym, anchor in anchors.items():
        if (not re.fullmatch(r'D_[0-9A-F]{8}', sym) or not anchor.get('basis')
                or not isinstance(anchor.get('view_bytes', 1), int) or anchor.get('view_bytes', 1) <= 0):
            raise Refused('runtime anchor needs an address symbol and basis: ' + sym)
        if not (root / anchor.get('declaration', '')).is_file() and anchor.get('declaration') != hdr:
            raise Refused('runtime anchor declaration missing: ' + sym)
        for path in anchor.get('review_inputs', []):
            if Path(path).is_absolute() or '..' in Path(path).parts or not (root / path).is_file():
                raise Refused('runtime anchor evidence missing: ' + path)
    fr = Freezer(root, base)
    # 1. header and module sources
    for p in [hdr] + [m['source'] for m in spec['modules']]:
        if (root / p).exists() and p != hdr:
            raise Refused('module source already exists: ' + p)
    if not (root / hdr).exists():
        fr.write(hdr, (work / 'tree' / hdr).read_text())
    elif (root / hdr).read_text() != (work / 'tree' / hdr).read_text():
        raise Refused('header exists with different content: ' + hdr)
    assign = jl(root / 'ledger/modules.jsonl')
    inline = jl(root / 'ledger/layout_inline.jsonl')
    previous_inline = [r for r in inline if r['tu_new'] in {m['source'] for m in absorbed.values()}]
    inline = [r for r in inline if r not in previous_inline]
    lay = jl(root / 'ledger/layout.jsonl')
    index = max(r['module_index'] for r in assign) + 1
    span_ev = span_evidence(evidence_dir, spec, members) if evidence_dir else None
    receipts = {}
    retired_data = {}
    for mod in spec['modules']:
        key, srcp = mod['key'], mod['source']
        ms = [m for m in members if m['module'] == key]
        cfg = spec.get('recipe') or ms[0]['cfg']
        text = (work / 'tree' / srcp).read_text()
        fr.write(srcp, text)
        ev = 'docs/evidence/' + key
        # 2. inline provenance: each member's piece = its comment + definition
        found, _, _ = definitions(text)
        starts = []
        for m in ms:
            f = [x for x in found if x[0] == m.get('first', m['name'])]
            if len(f) != 1:
                f = [x for x in found if x[0] == m['name']]
            if len(f) != 1:
                raise Refused('module source lost member %s' % m['name'])
            head = text[:f[0][1]]
            hit = re.search(r'(/\*(?:[^*]|\*(?!/))*\*/\s*)$', head)
            starts.append(hit.start() if hit else f[0][1])
        ends = starts[1:] + [len(text)]
        for i, (m, s, e) in enumerate(zip(ms, starts, ends)):
            piece = text[s:e].rstrip('\n') + '\n'
            inline.append(dict(tu_old=srcp, tu_new=srcp, member=m['path'], member_id=m['id'], manifest_key=key,
                               order=i + 1, offset=s, source_sha256=sha256(piece), bytes=len(piece.encode()),
                               inlined_bytes=len(piece.encode()), original_includes=[]))
        # 3. layout + member removal
        ids = {m['id'] for m in ms}
        for r in lay:
            if r['id'] in ids:
                r['path'] = srcp
        for path in dict.fromkeys(m['path'] for m in ms):
            fr.remove(path)
        # 4. imports from the module object
        with tempfile.TemporaryDirectory(prefix='tu-imports-') as td:
            o, err = compile_obj(root, root / srcp, cfg, Path(td), key)
            if o is None:
                raise Refused('installed module does not compile: ' + err[-400:])
            nm = subprocess.run(['mipsel-linux-gnu-nm', str(o)], check=True, capture_output=True, text=True).stdout
        undefined = sorted(l.split()[1] for l in nm.splitlines() if l.split()[0] == 'U')
        imports, runtime, sizes = [], {}, {}
        xviews, xmaps = {}, {}
        all_regions = [r for r in jl(root / ('config/overlays/%s.rowbase.jsonl' % container))
                       if r['base_confidence'] == 'proven']
        decl_headers = header_closure(root, hdr)
        for sym in undefined:
            fv = resolve_function(root, sym, names)
            vma = data_address(sym)
            if vma is None:
                if fv is None:
                    raise Refused('unresolved function import %s' % sym)
                imports.append(dict(symbol=sym, kind='function', vma=fv))
                continue
            if rlo + delta <= vma < rhi + delta:
                foff = vma - delta
                vb, how = view_bytes(root, sym, hdr, cfg, blob, foff, rhi, [])
                vb = min(vb, rhi - foff)
                sizes[sym] = how
                imports.append(dict(symbol=sym, kind='data', vma=vma, foff=foff, view_bytes=vb,
                                    owner='retail_asset:%s:%s' % (container, region['region'])))
            elif sym in anchors or SLUS_RESIDENT[0] <= vma < SLUS_RESIDENT[1] or any(a <= vma < b for a, b in SLUS_MANAGED):
                anchor = anchors.get(sym)
                vb, how = (anchor.get('view_bytes', 1), 'address_only_runtime_anchor') if anchor else view_bytes(
                    root, sym, hdr, cfg, None, None, 0, [])
                sizes[sym] = how
                decl = anchor['declaration'] if anchor else next((h for h in decl_headers
                    if re.search(r'\bextern\b[^;]*\b%s\b' % sym, mask((root / h).read_text())[0])), hdr)
                d = dict(symbol=sym, kind='runtime_data', vma=vma, view_bytes=vb, owner='resident_runtime:slus',
                         evidence=ev + '.imports.json', declaration=decl)
                runtime[sym] = d
                imports.append(d)
            else:
                # tu7: a view of another proven region of this container that is the ONLY region
                # mapping this vma (resident engines; overlapping views/banks stay ambiguous)
                hits = [r for r in all_regions if int(r['foff_start'], 0) + int(r['delta'], 0) <= vma <
                        int(r['foff_end'], 0) + int(r['delta'], 0) and r['region'] != region['region']]
                if len(hits) != 1:
                    raise Refused('data import %s outside the proven region and SLUS residency (%d other regions '
                                  'map it)' % (sym, len(hits)))
                xr = hits[0]
                xd, xlo, xhi = int(xr['delta'], 0), int(xr['foff_start'], 0), int(xr['foff_end'], 0)
                foff = vma - xd
                vb, how = view_bytes(root, sym, hdr, cfg, blob, foff, xhi, [])
                vb = min(vb, xhi - foff)
                sizes[sym] = how
                asset = 'work/disc/containers/' + CONTAINER_BIN[container]
                mapname = 'resident_' + re.sub(r'[^a-z0-9_]', '_', xr['region'].lower())
                d = dict(symbol=sym, kind='data', vma=vma, foff=foff, view_bytes=vb, owner='retail_asset:' + asset,
                         asset=asset, map=mapname, evidence=ev + '.imports.json')
                xmaps[mapname] = dict(asset=asset, file_start=xlo, file_end=xhi, delta=xd, kind='rowbase',
                                      region=xr['region'], container=container,
                                      basis='config/overlays/%s.rowbase.jsonl %s proven load-map record.'
                                            % (container, xr['region']))
                xviews[sym] = d
                imports.append(d)
        # a fallback-sized view never runs into the next imported object of the region
        local = sorted(((d['vma'], d) for d in imports if d['kind'] == 'data'), key=lambda item: item[0])
        for (v, d), (v2, _) in zip(local, local[1:]):
            if sizes.get(d['symbol']) != 'sizeof' and v < v2 < v + d['view_bytes']:
                d['view_bytes'] = v2 - v
        evidence_files = [ev + '.md', ev + '.membership.json', ev + '.recipe.json']
        old_modules = [absorbed[k] for k in mod.get('absorb_modules', [])]
        if old_modules:
            evidence_files.append(ev + '.absorption.json')
            evidence_files += [p for old in old_modules for p in old['review_inputs'] if p != old['source']]
            evidence_files = list(dict.fromkeys(evidence_files))
            fr.write(ev + '.absorption.json', json.dumps(dict(
                module=key, retired_modules=old_modules, frozen_inputs=absorption.get('inputs', {}),
                previous_inline=[r for r in previous_inline if r['tu_new'] in {x['source'] for x in old_modules}],
                identity=results[key], basis='Complete old TUs compiled once and compared to the merged TU; '
                'old descriptors and their evidence retained as the retirement proof chain.'), indent=2) + '\n')
        anchor_claims = {sym: anchors[sym] for sym in runtime if sym in anchors}
        evidence_files += sorted({p for a in anchor_claims.values() for p in a.get('review_inputs', [])})
        if runtime or xviews:
            evidence_files.append(ev + '.imports.json')
            fr.write(ev + '.imports.json', json.dumps(dict(module=key, runtime_views=runtime, views=xviews,
                                                           maps=xmaps, basis=[
                'Existing runtime objects and explicitly reviewed address anchors referenced by this TU; '
                'external runtime views, no allocation claim.',
                'Views of other proven resident load regions (engine) of this container; no ownership claim.'],
                view_bytes_method=sizes, address_only_anchors=anchor_claims), indent=2) + '\n')
        group = dict(container=container, module=Path(srcp).name, module_index=index)
        index += 1
        assign = [r for r in assign if r['id'] not in ids] + [dict(id=m['id'], **group, confidence='strong') for m in ms]
        recipe = dict(cfg=cfg, row_asflags='')
        entry = dict(
            key=key, container=container, name=Path(srcp).name, region=region['region'], source=srcp,
            headers=[hdr, 'include/common.h'], recipe=recipe,
            members=[dict(id=m['id'], source=srcp, function=m['function'], foff=m['foff'], vma=m['foff'] + delta,
                          size=m['size']) for m in ms],
            owned_data=[], imports=imports,
            review=dict(membership='reviewed', types='reviewed', ownership='reviewed', reviewer=reviewer),
            review_inputs=evidence_files, membership_evidence=ev + '.membership.json',
            genuine_aspsx=dict(flags=['-0'], evidence=ev + '.recipe.json'))
        if key in switch_rows:
            data = switch_rows[key]
            dpath = layout.get(data['id']) or data['c_path']
            entry.update(switch_allocation(data, ms, srcp, delta))
            entry['review_inputs'].append(srcp)
            for row in lay:
                if row['id'] == data['id']:
                    row['path'] = srcp
            if dpath != srcp:
                fr.remove(dpath)
                retired_data[dpath] = srcp
            assign = [r for r in assign if r['id'] != data['id']] + [dict(id=data['id'], **group, confidence='strong')]
            if not rlo <= data['foff'] < data['foff'] + data['size'] <= rhi:
                raise Refused('switch allocation outside the module load region: ' + data['id'])
            evidence_files.append(ev + '.switch.json')
            fr.write(ev + '.switch.json', json.dumps(dict(module=key, data_row=data['id'], owner=data['owner'],
                identity=results[key], basis='Compiler-emitted table bytes and relocations identical to '
                'frozen members; evidenced registered table retained with its owner.'), indent=2) + '\n')
        if (work / 'literals.json').exists():
            # 72(f): the file's string pool is its own .rodata allocation (separated-literal-allocations-v1)
            pool = json.loads((work / 'literals.json').read_text())
            if pool['region'] != region['region']:
                raise Refused('owned pool lies in another load region')
            entry['allocation_model'] = 'separated-literal-allocations-v1'
            entry['allocations'] = [
                dict(section='.rodata', foff=pool['foff'], vma=pool['vma'], size=pool['size'], link_alignment=4,
                     slots=pool['slots']),
                dict(section='.text.*', foff=ms[0]['foff'], vma=ms[0]['foff'] + delta,
                     size=sum(m['size'] for m in ms), link_alignment=4)]
            entry['section_order'] = ['.rodata'] + ['.text.' + m['function'] for m in ms]
            if srcp not in entry['review_inputs']:
                entry['review_inputs'].append(srcp)
        mods_doc['modules'].append(entry)
        basis = list(spec.get('basis') or [])
        if span_ev:
            basis.insert(0, span_ev)
        elif evidence_line(spec):
            basis.insert(0, evidence_line(spec) + ' Grouping by tools/tu/infer_groups.py (group %s); every '
                         'join is a byte fact read with a model (call locality, private data, cross-image '
                         'order), never decisive alone.' % spec.get('group', '?'))
        basis.append('Members are the contiguous registered home rows 0x%X..0x%X at one uniform recipe; '
                     'tools/tu/tu_merge.py proved the module object equal to the in-order concatenation of the '
                     'members compiled one by one (code bytes and relocations).' % (ms[0]['foff'],
                                                                                     ms[-1]['foff'] + ms[-1]['size']))
        fr.write(ev + '.membership.json', json.dumps(dict(
            module=key, ledger_group=group,
            members=([switch_rows[key]['id']] if key in switch_rows else []) + [m['id'] for m in ms], confidence='strong',
            coverage_complete=True, basis=basis, private_functions=[],
            source_facades='Members are inlined; no standalone member files remain.'), indent=2) + '\n')
        fr.write(ev + '.recipe.json', json.dumps(dict(module=key, scope='whole_tu', flags=['-q', '-G0', '-0'],
                                                      recipe=recipe, basis=[
            'Uniform registered member recipe; merged TU compiles to the in-order concatenation of the member '
            'objects (text bytes and relocations identical).']), indent=2) + '\n')
        fr.write(ev + '.md', '# %s\n\n%s\n\n%d functions (foff 0x%X-0x%X) of one original translation unit. %s\n\n'
                 'Definitions retain retail order; declarations are reconciled in `%s` to one true prototype, '
                 'with explicit caller/data-view casts and parameter or live-argument corrections where required '
                 '(decision 72(d)), preserving object bytes and relocations '
                 '(proved by tools/tu/tu_merge.py). String literals stay retail imports until '
                 'the whole TU and its pool extent are recovered (decision 72(f)).\n' % (
                     mod.get('title', key), mod.get('description', ''), len(ms), ms[0]['foff'],
                     ms[-1]['foff'] + ms[-1]['size'], span_ev or evidence_line(spec), hdr))
        receipts[key] = dict(members=len(ms), imports=len(imports), runtime=len(runtime))
    for rel, records, compact in (('ledger/layout_inline.jsonl', inline, True), ('ledger/layout.jsonl', lay, True)):
        fr.freeze(rel)
        wjl(root / rel, records, compact)
    fr.freeze('ledger/modules.jsonl')
    (root / 'ledger/modules.jsonl').write_text(''.join(json.dumps(r) + '\n' for r in assign))
    # Other modules may list a retired member file as review evidence; point them at the merged file (the
    # make build depends on every review input, so a dangling path breaks the build).
    retired = {m['path']: next(x['source'] for x in spec['modules'] if x['key'] == m['module']) for m in members}
    retired.update(retired_data)
    alias_path = 'ledger/tu_layout.jsonl'
    if (root / alias_path).exists():
        aliases = jl(root / alias_path)
        rewritten = rewrite_tu_aliases(aliases, retired)
        if rewritten != aliases:
            fr.write(alias_path, ''.join(json.dumps(r, separators=(',', ':')) + '\n' for r in rewritten))
    for entry in mods_doc['modules']:
        ri = entry.get('review_inputs')
        if ri and any(p in retired for p in ri):
            entry['review_inputs'] = list(dict.fromkeys(retired.get(p, p) for p in ri))
    fr.freeze('config/overlays/modules.json')
    (root / 'config/overlays/modules.json').write_text(json.dumps(mods_doc, indent=2) + '\n')
    # 4b. decision 72(c): one recipe per file - re-attribute the members' registered cells
    if spec.get('recipe'):
        reattribute(root, fr, container, members, spec['recipe'], spec.get('group') or spec.get('span') or '?')
    # 5. path rewrites in the link catalogues (TU paths of homes and placements)
    old_paths = {m['path']: next(x['source'] for x in spec['modules'] if x['key'] == m['module']) for m in members}
    old_paths.update(retired_data)
    for rel in spec.get('include_facades', []):
        p = Path(rel)
        if p.is_absolute() or '..' in p.parts or not (root / p).is_file():
            raise Refused('invalid include facade: ' + rel)
        fr.write(rel, rewrite_include_facade((root / p).read_text(), rel, old_paths))
    for pat in ('config/link/*/*.json', 'link/*/*.tsv'):
        for path in sorted(root.glob(pat)):
            t = path.read_text()
            if not any('"%s"' % p in t for p in old_paths):
                continue
            rel = path.relative_to(root).as_posix()
            fr.freeze(rel)
            for p, n in old_paths.items():
                t = t.replace('"%s"' % p, '"%s"' % n)
            path.write_text(t)
    # 6. physical build graph, then the module gate
    fr.freeze('ledger/splits/overlay_modules.build.json')
    r = subprocess.run([sys.executable, str(root / 'tools/gate/overlay_module_gate.py'), '--root', str(root),
                        '--graph'], capture_output=True, text=True)
    if r.returncode:
        raise Refused('build graph regeneration failed: ' + r.stderr[-800:])
    refresh_link_graph(root, work, fr)
    gate_results = {}
    if gate:
        for mod in spec['modules']:
            out = (gate_out or work / 'gate') / mod['key']
            if out.exists():
                shutil.rmtree(out)
            r = subprocess.run(['nice', '-n', '10', sys.executable, str(root / 'tools/gate/overlay_module_gate.py'),
                                '--root', str(root), '--module', mod['key'], '--out', str(out)],
                               capture_output=True, text=True)
            if r.returncode:
                gate_results[mod['key']] = dict(error=r.stderr[-1500:])
                continue
            g = json.loads(r.stdout[r.stdout.index('{'):])
            gate_results[mod['key']] = g
    (work / 'install.patch').write_text(fr.patch())
    receipt = dict(modules=receipts, identity={k: v['equal'] for k, v in results.items()}, gate=gate_results,
                   touched=fr.touched)
    (work / 'install_receipt.json').write_text(json.dumps(receipt, indent=1) + '\n')
    bad = [k for k, g in gate_results.items() if 'error' in g or g['gate']['result'] != 'MATCH'
           or g['genuine']['result'] != 'MATCH']
    return receipt, bad


def switch_proposal(root, work, spec, members, key, res, rows):
    """Switch tables are proven (prove: .rodata bytes and relocations equal).  The module gate's
    separated-switch-allocations-v1 model needs ONE compiler switch per module and an evidenced
    registered jump_table data row owned by its member; write the allocation fragment a lane
    would install and return the refusal reason."""
    ms = [m for m in members if m['module'] == key]
    tables = []
    for sw in res['switch_tables']:
        payload = sw.get('payload_bytes', sw['bytes'])
        owned = [r for r in rows.values() if r.get('row_kind') == 'data' and r.get('data_kind') in
                 ('jump_table', 'compiler_switch_table') and r.get('owner') == sw['id']]
        tables.append(dict(owner=sw['id'], bytes=payload, compiled_bytes=sw['bytes'], rows=[dict(id=r['id'], foff=r['foff'], size=r['size'],
                                                                        status=r.get('ownership_status'))
                                                                   for r in owned]))
    frag = dict(module=key, allocation_model='separated-switch-allocations-v1', switch_tables=tables,
                text=dict(foff=ms[0]['foff'], size=sum(m['size'] for m in ms)),
                section_order_hint='.text.<members up to the switch owner>, .rodata, .text.<rest>')
    (work / ('switch_%s.json' % key)).write_text(json.dumps(frag, indent=1) + '\n')
    why = []
    if len(tables) != 1:
        why.append('%d switch tables (the gate model owns exactly one per module)' % len(tables))
    for t in tables:
        if not any(r['status'] == 'evidenced' and r['size'] == t['bytes'] for r in t['rows']):
            why.append('no evidenced registered jump_table row of %d bytes owned by %s (found %s)'
                       % (t['bytes'], t['owner'], t['rows'] or 'none'))
    return ('switch tables proven identical; install needs the separated switch allocation: ' +
            ('; '.join(why) or 'eligible - descriptor fragment written, install by a lane (tu7 did not automate it)')
            + ' [%s]' % (work / ('switch_%s.json' % key)))



def switch_allocation(data, members, source, delta):
    """Descriptor for the existing single compiler-switch allocation model."""
    owner = next(m for m in members if m['id'] == data['owner'])
    cut = members.index(owner) + 1
    sections = ['.text.' + m['function'] for m in members]
    return dict(
        data_members=[dict(id=data['id'], source=source, symbol=data.get('true_name') or data['func'],
                           foff=data['foff'], vma=data['foff'] + delta, size=data['size'])],
        allocation_model='separated-switch-allocations-v1',
        allocations=[
            dict(section='.rodata', foff=data['foff'], vma=data['foff'] + delta, size=data['size'],
                 link_alignment=4, slots=[dict(kind='switch_table', offset=0, size=data['size'],
                                              owner=owner['function'], source=source)]),
            dict(section='.text.*', foff=members[0]['foff'], vma=members[0]['foff'] + delta,
                 size=sum(m['size'] for m in members), link_alignment=4)],
        section_order=sections[:cut] + ['.rodata'] + sections[cut:])


def switch_row(root, work, spec, members, key, res, rows):
    """Only the existing, evidenced single-table model is admitted automatically."""
    switches = res['switch_tables']
    candidates = [r for r in rows.values() if len(switches) == 1 and r.get('row_kind') == 'data'
                  and r.get('data_kind') == 'jump_table' and r.get('ownership_status') == 'evidenced'
                  and r.get('owner') == switches[0]['id']
                  and r['size'] == switches[0].get('payload_bytes', switches[0]['bytes'])]
    if len(candidates) != 1:
        raise Refused(switch_proposal(root, work, spec, members, key, res, rows))
    return candidates[0]


def reattribute(root, fr, container, members, recipe, why):
    """72(c): members whose registered cell differs take the file's one recipe, in the split ledger
    (authoritative; config_was/config_note keep the history) and in the derived registry rows."""
    changed = {m['id'] for m in members if m.get('registered_cfg', m['cfg']) != recipe}
    if not changed:
        return []
    cell = RECIPES[recipe][0]
    flags = ' '.join(f for f in RECIPES[recipe][1] if f != '-O2')
    note = ('decision 72(c): file %s compiles byte-identical as one TU under %s (tools/tu/tu_merge.py prove: '
            'merged object == members at their registered cells); the per-row cell was an artefact' % (why, recipe))
    rel = 'ledger/splits/%s.jsonl' % container
    recs = jl(root / rel)
    for r in recs:
        if '%s/%s' % (container, r.get('func_vram')) in changed and not r.get('rerun') and r.get('result') == 'MATCH':
            r['config_was'], r['config'], r['config_note'] = r.get('config'), recipe, note
    fr.freeze(rel)
    (root / rel).write_text(''.join(json.dumps(r, separators=(',', ':')) + '\n' for r in recs))
    rows = jl(root / 'ledger/rows.jsonl')
    for r in rows:
        if r['id'] in changed:
            r['cfg'], r['cell'], r['flags'] = recipe, cell, flags
    fr.freeze('ledger/rows.jsonl')
    wjl(root / 'ledger/rows.jsonl', rows)
    return sorted(changed)


def make_group_spec(root, group_id, groups_tsv):
    """Spec skeleton for an inferred group of tools/tu/infer_groups.py (one module per own-home run)."""
    import csv
    csv.field_size_limit(1 << 24)
    row = next((r for r in csv.DictReader(open(groups_tsv), delimiter='\t') if r['group_id'] == group_id), None)
    if row is None:
        raise Refused('group %s not in %s' % (group_id, groups_tsv))
    runs = [x.split(';') for x in row['mergeable_runs'].split('|') if x]
    if not runs:
        raise Refused('group %s has no run of >= 2 home rows in its image' % group_id)
    _, layout = load_repo(root)
    rows = {r['id']: r for r in jl(root / 'ledger/rows.jsonl')}
    mods = []
    common_all = None
    for run in runs:
        dirs = [os.path.dirname(layout.get(i) or rows[i]['c_path']) for i in run]
        common = os.path.commonpath(dirs)
        common_all = common if common_all is None else os.path.commonpath([common_all, common])
        tag = 'tu_%X' % rows[run[0]]['foff']
        mods.append(dict(key='%s_%s' % (row['container'], tag.lower()), source='%s/%s.c' % (common, tag),
                         title='REPLACE: one-line feature description.', members=run))
    evidence = [x for x in row['evidence'].split(',') if x and not x.startswith(' (+')]
    sub = common_all[len('src/'):] if common_all.startswith('src/') else common_all
    return dict(container=row['container'], group=group_id, evidence_level=row['level'], evidence=evidence,
                header='include/%s/%s.h' % (sub, mods[0]['source'].rsplit('/', 1)[1][:-2]),
                header_title='Shared declarations of one original file (rename to the feature).',
                reviewer='REPLACE-lane-id', basis=[], modules=mods)


def make_spec(root, span_id, evdir, ranked):
    import csv
    row = next((r for r in csv.DictReader(open(ranked), delimiter='\t') if r['span_id'] == span_id), None)
    if row is None:
        raise Refused('span %s not in %s' % (span_id, ranked))
    unit = span_id.split('#')[0]
    d = json.loads((Path(evdir) / 'units' / (unit.replace('/', '__') + '.json')).read_text())
    lo, hi = int(row['foff_first'], 16), int(row['foff_end'], 16)
    ids = [f['row'] for f in d['functions'] if lo <= f['foff'] < hi]
    if None in ids:
        raise Refused('span holds unregistered code; not installable as listed')
    _, layout = load_repo(root)
    dirs = [os.path.dirname(layout.get(i, '')) for i in ids]
    common = os.path.commonpath(dirs) if all(dirs) else 'src'
    container = d['summary']['container']
    tag = 'tu_%X' % lo
    return dict(container=container, span=span_id,
                header='include/%s/%s.h' % (common[len('src/'):] if common.startswith('src/') else common, tag),
                header_title='Shared declarations of one original translation unit (rename to the feature).',
                reviewer='REPLACE-lane-id', basis=[],
                modules=[dict(key='%s_%s' % (container, tag.lower()), source='%s/%s.c' % (common, tag),
                              title='REPLACE: one-line feature description.', members=ids)])


def data_hypothesis_slice(root, image, record, lo, hi):
    """A solved code-base hypothesis cannot defeat an audited non-code census slice.

    This is opt-in, never applies to a proven record, and cannot touch any registered
    row. Preserve the original hypothesis in the resulting region's evidence.
    """
    if record['base_confidence'] != 'solved':
        raise Refused('only solved hypotheses may be superseded by proven data')
    sys.path.insert(0, str(root / 'tools'))
    from byte_map_format import read_parts
    container, stem = image.split('/', 1)
    parts = sorted((root / 'link' / container).glob(stem + '*.tsv'))
    if not parts:
        raise Refused('superseding a solved hypothesis requires a typed byte map')
    doc = read_parts(parts, root)
    if doc['image'] != image:
        raise Refused('data hypothesis byte-map image differs')
    for row in jl(root / 'ledger/rows.jsonl'):
        if (row['container'] == container and isinstance(row.get('foff'), int)
                and row['foff'] < hi and lo < row['foff'] + row['size']):
            raise Refused('a registered row overlaps the proposed data-hypothesis slice: ' + row['id'])
    p = root / 'config/overlays/modules.json'
    if p.exists() and any(m['container'] == container and m['region'] == record['region']
                          for m in json.loads(p.read_text())['modules']):
        raise Refused('a live module references the proposed solved hypothesis')
    cursor, evidence = lo, []
    number = lambda x: int(x, 0) if isinstance(x, str) else x
    for entry in sorted(doc['entries'], key=lambda e: number(e['foff'])):
        a, b = number(entry['foff']), number(entry['foff']) + entry['size']
        if b <= cursor or a >= hi:
            continue
        if (a > cursor or entry.get('kind') not in ('data', 'asset')
                or entry.get('census_label') != 'proven_data'):
            raise Refused('the foreign solved hypothesis is not tiled by proven data')
        evidence.append(dict(entry))
        cursor = min(hi, b)
        if cursor == hi:
            break
    if cursor != hi:
        raise Refused('typed byte map does not cover the foreign solved hypothesis')
    return dict(original_hypothesis=record, superseded_extent=['0x%X' % lo, '0x%X' % hi],
                byte_map=[p.relative_to(root).as_posix() for p in parts], proven_data_entries=evidence,
                basis='Decision 72(h) image load region; the conflicting solved code hypothesis overlaps '
                      'only audited proven_data and no registered row. Original hypothesis retained verbatim; '
                      'any portion outside this image remains a solved record.')


def consolidate_region(root, base, image, lo=None, hi=None, name=None, basis='',
                       supersede_data_hypotheses=False):
    """MAIN owner model (tu7): one proven load region over a link image's code AND its own
    .rdata/.data, so a merged file's imports of its own literals/data are retail views of
    that region. Every rowbase record inside the extent must share the image's load delta,
    except explicitly superseded solved hypotheses over audited data without registered rows;
    they are replaced by one record that embeds them verbatim (no proof is dropped).  A single
    covering record is widened in place and keeps its name (modules cite region names)."""
    container, _ = image.split('/', 1)
    catalogue = root / 'config/link' / (image + '.json')
    if catalogue.exists():
        doc = json.loads(catalogue.read_text())
    else:
        sys.path.insert(0, str(root / 'tools'))
        from byte_map_format import read_parts
        parts = sorted((root / 'link' / container).glob(image.split('/', 1)[1] + '*.tsv'))
        if not parts:
            raise Refused('no link catalogue for ' + image)
        doc = read_parts(parts, root)
        if doc['image'] != image:
            raise Refused('file-view identity differs: ' + image)
        catalogue = parts[0]
    ifoff, isize = (int(doc[k], 0) if isinstance(doc[k], str) else doc[k] for k in ('foff', 'size'))
    ivma = doc.get('vma')
    if ivma is None:
        if lo is None or hi is None:
            raise Refused('file view without a load vma requires --extent')
        deltas = {int(r['delta'], 0) for r in jl(root / ('config/overlays/%s.rowbase.jsonl' % container))
                  if r['base_confidence'] == 'proven' and int(r['foff_start'], 0) < hi
                  and lo < int(r['foff_end'], 0)}
        if len(deltas) != 1:
            raise Refused('file view has no unique proven delta in its explicit extent')
        delta = deltas.pop()
        ivma = ifoff + delta
    else:
        ivma = int(ivma, 0) if isinstance(ivma, str) else ivma
        delta = ivma - ifoff
    lo = ifoff if lo is None else lo
    hi = ifoff + isize if hi is None else hi
    if not ifoff <= lo < hi <= ifoff + isize:
        raise Refused('extent 0x%X-0x%X is outside link image %s' % (lo, hi, image))
    rel = 'config/overlays/%s.rowbase.jsonl' % container
    lines = (root / rel).read_text().splitlines()
    keep, inside, superseded = [], [], []
    for line in lines:
        if not line.strip().startswith('{'):
            keep.append(line)
            continue
        r = json.loads(line)
        a, b = int(r['foff_start'], 0), int(r['foff_end'], 0)
        if a < hi and lo < b:
            if int(r['delta'], 0) != delta:
                if not supersede_data_hypotheses:
                    raise Refused('region %s inside the image has delta %s, not 0x%X' % (r['region'], r['delta'], delta))
                cut_lo, cut_hi = max(lo, a), min(hi, b)
                superseded.append(data_hypothesis_slice(root, image, r, cut_lo, cut_hi))
                remnants = [(a, cut_lo), (cut_hi, b)]
                remnants = [(x, y) for x, y in remnants if x < y]
                for i, (x, y) in enumerate(remnants):
                    remnant = dict(r, foff_start='0x%X' % x, foff_end='0x%X' % y,
                                   hypothesis_clipped_by=dict(image=image, extent=['0x%X' % cut_lo, '0x%X' % cut_hi]))
                    if len(remnants) > 1:
                        remnant['region'] += '_part%d' % i
                    keep.append(json.dumps(remnant))
                continue
            if a < lo or b > hi:
                lo, hi = min(lo, a), max(hi, b)
            inside.append(r)
        else:
            keep.append(line)
    if not any(r['base_confidence'] == 'proven' for r in inside):
        raise Refused('no proven region at delta 0x%X inside %s' % (delta, image))
    proof = ('tu7 owner model for merged files (decision 72): link catalogue %s describes file '
             '0x%X..0x%X; selected extent 0x%X..0x%X uses vma 0x%X at its start (delta 0x%X; %s). '
             'The selected image text, .rdata and .data load as one unit; '
             '%d byte-exact region proofs at this delta lie inside and are embedded below unchanged. %s' % (
                 catalogue.relative_to(root).as_posix(), ifoff, ifoff + isize, lo, hi, lo + delta,
                 delta, doc.get('evidence', ''),
                 len(inside), basis)).strip()
    if len(inside) == 1:
        rec = dict(inside[0])
        rec['proof'] = rec['proof'] + '; WIDENED ' + proof
        rec['widened_from'] = [inside[0]['foff_start'], inside[0]['foff_end']]
    else:
        modules_path = root / 'config/overlays/modules.json'
        referenced = set()
        if modules_path.exists():
            old_names = {r['region'] for r in inside}
            referenced = {m['region'] for m in json.loads(modules_path.read_text())['modules']
                          if m['container'] == container and m['region'] in old_names}
        if len(referenced) > 1:
            raise Refused('consolidation would retire multiple live module regions: %s' % sorted(referenced))
        if referenced:
            if name and name not in referenced:
                raise Refused('consolidation name would retire a live module region')
            name = next(iter(referenced))
        rec = dict(schema='azure-clean.rowbase.v1', region=name or 'link_%s' % image.split('/', 1)[1],
                   foff_start='0x%X' % lo, foff_end='0x%X' % hi, delta='0x%X' % delta, base_confidence='proven',
                   proof=proof, consolidated=inside)
    rec['foff_start'], rec['foff_end'] = '0x%X' % lo, '0x%X' % hi
    if superseded:
        rec['superseded_data_hypotheses'] = rec.get('superseded_data_hypotheses', []) + superseded
    out = [l for l in keep] + [json.dumps(rec)]
    fr = Freezer(root, base)
    fr.write(rel, '\n'.join(out) + '\n')
    return dict(region=rec['region'], foff_start=rec['foff_start'], foff_end=rec['foff_end'], delta=rec['delta'],
                consolidated=[r['region'] for r in inside],
                superseded_data_hypotheses=[r['original_hypothesis']['region'] for r in superseded])


def restore(root, base):
    lst = json.loads((base / 'touched.json').read_text())
    restored, removed = 0, 0
    for rel in lst['touched']:
        p = root / rel
        if rel in lst['absent']:
            if p.exists():
                p.unlink()
                removed += 1
            d = p.parent
            while d != root and d.is_dir() and not any(d.iterdir()):
                d.rmdir()
                d = d.parent
        else:
            p.parent.mkdir(parents=True, exist_ok=True)
            shutil.copy2(base / 'files' / rel, p)
            restored += 1
    return dict(restored=restored, removed=removed)


def span_evidence(evdir, spec, members):
    """One-sentence literal-pool basis from the tu_evidence unit holding these members."""
    want = {m['id'] for m in members}
    for p in sorted(Path(evdir, 'units').glob('*.json')):
        d = json.loads(p.read_text())
        byrow = {f['row']: f for f in d['functions'] if f['row']}
        if not want <= set(byrow):
            continue
        gs = {byrow[i]['group'] for i in want}
        if len(gs) != 1 or not next(iter(gs)):
            continue
        g = next(x for x in d['groups'] if x['gid'] == next(iter(gs)))
        fn = d['functions']
        lits = ', '.join('0x' + x for x in g['literals'][:8]) + (' (+%d)' % (len(g['literals']) - 8)
                                                                 if len(g['literals']) > 8 else '')
        return ('Literal-pool ownership (%s, %s): string literals %s are each referenced by two or more functions '
                'of 0x%X..0x%X; gcc 2.7.2 shares an anonymous literal only inside one translation unit, so every '
                'function between the first and last user is one TU.' % (
                    d['summary']['unit'], g['gid'], lits, fn[g['first']]['foff'], fn[g['last']]['end']))
    return None


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument('command', choices=['spec', 'run', 'draft', 'own', 'prove', 'install', 'restore', 'region'])
    ap.add_argument('--image', help='region: link image (e.g. main/ll34_269000_80400000)')
    ap.add_argument('--extent', help='region: LO,HI file offsets (default: the whole link image)')
    ap.add_argument('--supersede-data-hypotheses', action='store_true',
                    help='region: retain but supersede solved foreign-base hypotheses only over audited proven data')
    ap.add_argument('--span', help='spec: span id from spans_ranked.tsv / boundary_map.tsv')
    ap.add_argument('--ranked', type=Path, help='spec: spans_ranked.tsv (default: next to --evidence)')
    ap.add_argument('--group', help='spec: inferred group id from groups.tsv (tools/tu/infer_groups.py)')
    ap.add_argument('--groups', type=Path, help='spec: groups.tsv written by infer_groups.py')
    ap.add_argument('spec', nargs='?', type=Path)
    ap.add_argument('--root', type=Path, default=ROOT)
    ap.add_argument('--work', type=Path)
    ap.add_argument('--base', type=Path)
    ap.add_argument('--evidence', type=Path)
    ap.add_argument('--dry-run', action='store_true', help='draft and prove only; never touch the root')
    ap.add_argument('--no-gate', action='store_true')
    ap.add_argument('--force', action='store_true', help='draft: replace an existing work directory')
    ap.add_argument('--reviewer')
    args = ap.parse_args(argv)
    root = args.root.resolve()
    work = args.work.resolve() if args.work else None
    try:
        if args.command == 'spec':
            if args.group:
                sp = make_group_spec(root, args.group, args.groups)
            else:
                sp = make_spec(root, args.span, args.evidence,
                               args.ranked or args.evidence.parent / 'spans_ranked.tsv')
            args.spec.write_text(json.dumps(sp, indent=1) + '\n')
            print(json.dumps(dict(spec=str(args.spec), members=len(sp['modules'][0]['members']))))
            return 0
        if args.command == 'own':
            print(json.dumps(own_literals(root, work)))
            return 0
        if args.command == 'region':
            lo = hi = None
            if args.extent:
                lo, hi = (int(x, 0) for x in args.extent.split(','))
            print(json.dumps(consolidate_region(root, args.base.resolve(), args.image, lo, hi,
                                               supersede_data_hypotheses=args.supersede_data_hypotheses)))
            return 0
        if args.command == 'restore':
            if not args.base:
                raise Refused('--base DIR is required')
            print(json.dumps(restore(root, args.base.resolve())))
            return 0
        if args.command in ('run', 'draft'):
            spec = json.loads(args.spec.read_text())
            members, conflicts, blocking = draft(root, spec, work, args.evidence, force=args.force)
            print(json.dumps(dict(step='draft', members=len(members), conflicts=len(conflicts),
                                  blocking=len(blocking))))
            if blocking:
                print(json.dumps(blocking, indent=1))
                return 2
            if args.command == 'draft':
                return 0
        if args.command in ('run', 'prove'):
            ok, results = prove(root, work)
            print(json.dumps(dict(step='prove', ok=ok, modules={k: {x: v[x] for x in (
                'members', 'member_text_bytes', 'merged_text_bytes', 'text_equal', 'relocations_equal',
                'relocations', 'merged_other_sections')} for k, v in results.items()})))
            if not ok:
                return 3
            if args.command == 'prove' or args.dry_run:
                return 0
        if args.command in ('run', 'install'):
            if args.dry_run:
                return 0
            if not args.base:
                raise Refused('--base DIR is required to install (pristine copies of every touched file)')
            receipt, bad = install(root, work, args.base.resolve(), gate=not args.no_gate, reviewer=args.reviewer,
                                   evidence_dir=args.evidence)
            print(json.dumps(dict(step='install', **{k: v for k, v in receipt.items() if k != 'touched'}), indent=1))
            return 1 if bad else 0
    except Refused as e:
        print(json.dumps(dict(refused=str(e))))
        return 4
    return 0


if __name__ == '__main__':
    sys.exit(main())
