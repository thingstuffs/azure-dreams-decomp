"""Diagnostic overlay member scores through the complete native TU.

This is a candidate measurement, never a module certificate. The ordinary
module compiler/ccproc/maspsx/link recipe is retained, with extent and equality
assertions replaced by per-member measurements. No bytes or relocations are masked.
"""
from __future__ import annotations

import difflib
import hashlib
import importlib.util
import json
import os
import re
import struct
import subprocess
import sys
import tempfile
from pathlib import Path

import kitlib

_MATCH = None


def gate():
    kitlib.add_paths()
    from gate import overlay_module_gate
    return overlay_module_gate


def membership(row):
    """Validated manifest membership (including its strong ledger cohort).

    A ledger guess alone does not invent a TU or a recipe. Cache validation only
    while every input consumed by the validator retains its file identity.
    """
    if row.get('kind') != 'overlay':
        return None
    root = kitlib.ROOT
    path = root / 'config/overlays/modules.json'
    if not path.exists() or (root / 'config/overlay_modules_disabled').exists():
        return None
    # Read this small manifest first; ordinary rows avoid the full validator.
    doc = json.loads(path.read_text())
    matches = [m for m in doc['modules'] if any(a['id'] == row['id']
               for a in m['members'] + m.get('data_members', []))]
    if not matches:
        return None
    if len(matches) != 1:
        raise ValueError('ambiguous native module membership')
    m = matches[0]
    # Validate through the existing manifest authority, without writing a graph.
    g = gate()
    valid = next(x for x in g.load_modules(root) if x['key'] == m['key'])
    if valid['recipe']['cfg'] != row['cfg']:
        raise ValueError('native member recipe differs; per-member --cfg is unsupported')
    if row['id'] in {a['id'] for a in valid.get('data_members', [])}:
        raise ValueError('native prefix data edits require a complete TU candidate')
    return valid


def fingerprint(row):
    m = membership(row)
    # Listing/score context is the physical TU, not unrelated production-window
    # neighbours. The existing authority binds TU, headers, recipe, imports,
    # membership, load map, toolchain, assembler and retail inputs here.
    return None if m is None else gate().fingerprint(m, kitlib.ROOT, windows=False)['sha256']


def source_text(m, member_source, candidate):
    """Relocate the physical TU's quoted file includes, replacing exactly one member."""
    root = kitlib.ROOT
    src = root / m['source']
    replaced = 0
    def include(hit):
        nonlocal replaced
        name = hit[1]
        dest = (src.parent / name).resolve()
        if dest.is_file():
            if not dest.is_relative_to(root):
                raise ValueError('native TU include escapes root')
            if dest == root / member_source:
                replaced += 1
                dest = candidate
            return '#include ' + json.dumps(str(dest))
        return hit[0]  # shared headers resolve through root/include
    text = re.sub(r'^\s*#\s*include\s+"([^"]+)"\s*$', include,
                  src.read_text(), flags=re.M)
    if replaced != 1:
        raise ValueError('member must occur exactly once in its physical TU')
    return text


def listing(row, text, m=None):
    """Normalised listing of the selected function, compiled with all siblings."""
    m = m or membership(row)
    a = next(a for a in m['members'] if a['id'] == row['id'])
    import screen
    with tempfile.TemporaryDirectory(prefix='native_screen_') as td:
        d = Path(td); cand = d / 'member.c'; cand.write_text(text)
        raw = screen._listing(row, source_text(m, a['source'], cand))
    if raw is None:
        return None
    start = next((i for i, s in enumerate(raw)
                  if re.match(r'\s*\.ent\s+' + re.escape(a['function']) + r'\s*$', s)), None)
    if start is None:
        return None
    end = next((i for i in range(start + 1, len(raw))
                if re.match(r'\s*\.end\s+' + re.escape(a['function']) + r'\s*$', raw[i])), None)
    if end is None:
        return None
    kr, lt = screen.options_for(row)
    return screen.normalise(raw[start:end + 1], keep_reorder=kr, la_token=lt)


class Screen:
    def __init__(self, row, pinned):
        self.row = dict(row)
        self.module = membership(row)
        self.context_fingerprint = fingerprint(row)
        self.target = self._listing(pinned)

    def _fresh(self):
        if fingerprint(self.row) != self.context_fingerprint:
            raise RuntimeError('native module context changed; rebuild the target')

    def _listing(self, text):
        self._fresh()
        result = listing(self.row, text, self.module)
        self._fresh()
        return result

    listing = _listing

    def diff(self, text, context=0):
        got = self._listing(text)
        if got is None or self.target is None:
            return None
        return [s for s in difflib.unified_diff(self.target, got, n=context, lineterm='')
                if not s.startswith(('---', '+++'))]

    def distance(self, text):
        d = self.diff(text)
        return None if d is None else sum(s[:1] in '+-' for s in d)

    def exact(self, text):
        self._fresh()
        result = score(self.row, text, self.module)
        self._fresh()
        return result


def byte_stats(got, target):
    """Use the scorer's strict aligned-word metric; equality remains raw bytes."""
    global _MATCH
    if _MATCH is None:
        from verify import gate_root
        view = gate_root(False)
        sys.path.insert(0, str(view / 'tools'))
        spec = importlib.util.spec_from_file_location('lanekit_native_metric', view / 'tools/match.py')
        _MATCH = importlib.util.module_from_spec(spec)
        spec.loader.exec_module(_MATCH)
    if len(got) % 4 or len(target) % 4:
        raise ValueError('native member extent is not word aligned')
    subs, indels = _MATCH.aligned_word_stats(got, target, mask_relocations=False)
    return {'exact': got == target, 'total': subs + indels,
            'subs': subs, 'indels': indels,
            'generated_bytes': len(got), 'target_bytes': len(target),
            'generated_sha256': hashlib.sha256(got).hexdigest(),
            'retail_sha256': hashlib.sha256(target).hexdigest()}


def compile_object(row, text, m, out):
    """The same whole-TU GNU pipeline as overlay_module_gate.build."""
    g = gate(); root = kitlib.ROOT
    from common import NICE, parse_cfg
    a = next(a for a in m['members'] if a['id'] == row['id'])
    cand = out / 'member.c'; cand.write_text(text)
    source = out / 'candidate.c'; source.write_text(source_text(m, a['source'], cand))
    env = dict(os.environ, TMPDIR=str(out), PYTHONDONTWRITEBYTECODE='1')
    for k in ('AZURE_MASPSX', 'AZURE_MASPSX_COMPANION', 'MASPSX_NORETURN_FILE', 'MASPSX_SIBCALL_FILE'):
        env.pop(k, None)
    suffix = '.' + m['container'] if m['container'] != 'main' else ''
    for kind in ('NORETURN', 'SIBCALL'):
        env['MASPSX_' + kind + '_FILE'] = str(root / 'config' / (kind.lower() + '_syms' + suffix + '.txt'))
    if m['container'] in ('town', 'dungeon'):
        from gate import gen_noreturn_syms as census
        names = set(census.scoped_census(m['container'], g.module_first(m)['foff'], root=root)['names'])
        names.update(census.scan_text(source.read_text()))
        for member in m['members']:
            names.update(census.scan_text(text if member['id'] == row['id'] else (root / member['source']).read_text()))
        evidence = out / 'noreturn_syms.bank.txt'; evidence.write_text(census.render(sorted(names)))
        env['MASPSX_NORETURN_FILE'] = str(evidence)
    cell, flags = parse_cfg(row['cfg']); gcc = root / 'toolchain/compilers' / ('gcc-' + cell)
    def run(args, log, stdin=None):
        return g.command(NICE + list(args), out, env, out / log, stdin=stdin,
                         timeout=float(os.environ.get('PIN_CC_TIMEOUT', '60')))
    asm = out / 'module.s'; obj = out / 'module.o'
    run([gcc / 'gcc', '-B' + str(gcc) + '/', '-S', '-O2', *flags,
         '-I' + str(root / 'include'), '-w', source, '-o', asm], 'compile.log')
    proc = run([sys.executable, g.gate_tool(root, 'ccproc.py'), '--names-tsv', root / 'config/names.tsv'],
               'ccproc.log', asm.read_bytes())
    (out / 'sectioned.s').write_bytes(proc)
    run([root / '.venv/bin/python', root / 'toolchain/maspsx/maspsx.py', '--aspsx-version=2.79',
         '--dont-force-G0', '--run-assembler', '--gnu-as-path=mipsel-linux-gnu-as',
         '-I' + str(root), '-I' + str(root / 'include'), '-EL', '-march=r3000', '-G8', '-o', obj], 'assemble.log', proc)
    (out / 'module.untrimmed.o').write_bytes(obj.read_bytes())
    cooked, trim = g.N.prepare_object(m, obj.read_bytes(), root / 'tools/build/slus_rodata_trim.py')
    obj.write_bytes(cooked)
    secs = g.sections(obj)
    payload = [s for s in secs if s['flags'] & 2 and s['size'] and s['name'] not in g.META]
    allowed = {s for s, _ in g.payload_spec(m)}
    if {s['name'] for s in payload} != allowed:
        raise ValueError('unaccounted native allocated sections')
    nm = run(['mipsel-linux-gnu-nm', '-S', obj], 'object_symbols.log').decode()
    if any(l.split()[-2].upper() == 'C' for l in nm.splitlines() if len(l.split()) >= 2):
        raise ValueError('native candidate creates COMMON')
    imports = {d['symbol']: d['vma'] for d in m['imports']}
    # Natural link with no per-function placement and no fixed extent assertion.
    ld = out / 'module.ld'
    ld.write_text('OUTPUT_FORMAT("elf32-tradlittlemips")\nOUTPUT_ARCH(mips)\n_gp = 0x80080994;\n'
                  + ''.join(f'{s} = 0x{v:X};\n' for s, v in imports.items())
                  + 'SECTIONS {\n' + f' .module 0x{g.module_first(m)["vma"]:X} : {{ {g.link_inputs(m, obj)} }}\n'
                  + ' /DISCARD/ : { *(.text) *(.reginfo) *(.MIPS.abiflags) *(.pdr) *(.comment) *(.note*) *(.mdebug*) *(.gnu.attributes) }\n}\n')
    elf = out / 'module.elf'; binary = out / 'module.bin'
    run(['mipsel-linux-gnu-ld', '-EL', '-T', ld, '-Map', out / 'module.map', '-o', elf, obj], 'link.log')
    run(['mipsel-linux-gnu-objcopy', '-O', 'binary', elf, binary], 'objcopy.log')
    syms = run(['mipsel-linux-gnu-nm', '-n', '-S', elf], 'linked_symbols.log').decode()
    placed = {p[-1]: (int(p[0], 16), int(p[1], 16)) for l in syms.splitlines()
              if len(p := l.split()) == 4}
    return binary.read_bytes(), placed, trim


def score(row, text, m=None, diff=False):
    m = m or membership(row); g = gate(); root = kitlib.ROOT
    before = fingerprint(row)
    # Keep evidence for every score, including compiler/linker failures.
    lane = kitlib.bootstrap()
    out = Path(tempfile.mkdtemp(prefix='native_score_', dir=lane / 'tmp'))
    try:
        data, placed, trim = compile_object(row, text, m, out)
        first = g.module_first(m)
        members = []
        with (root / 'work/disc/containers' / g.CONTAINERS[m['container']]).open('rb') as f:
            for a in g.all_members(m):
                if 'function' in a:
                    addr, size = placed[a['function']]
                    offset = addr - first['vma']
                    body = a.get('body_offset', 0)
                    got = data[offset - body:offset + size]
                    natural = addr == a['vma'] + body
                else:
                    offset = a['foff'] - first['foff']; got = data[offset:offset + a['size']]; natural = True
                f.seek(a['foff']); retail = f.read(a['size'])
                rec = dict(byte_stats(got, retail), id=a['id'], address_exact=natural)
                members.append(rec)
                if a['id'] == row['id']:
                    (out / 'member.bin').write_bytes(got); (out / 'retail.bin').write_bytes(retail)
            prefix = sum(d['size'] for d in m['owned_data'])
            f.seek(first['foff']); head = f.read(prefix)
        selected = next(a for a in members if a['id'] == row['id'])
        collateral = [a for a in members if a['id'] != row['id'] and (not a['exact'] or not a['address_exact'])]
        data_exact = data[:prefix] == head
        exact = selected['exact'] and selected['address_exact'] and not collateral and data_exact
        result = dict(selected, exact=exact, member_exact=selected['exact'],
                      status='ok' if exact or not selected['exact'] else 'native-collateral-change',
                      module=m['key'], module_fingerprint=before,
                      kind='NATIVE_MEMBER_DIAGNOSTIC', other_members_changed=collateral,
                      members=members, owned_data_exact=data_exact, masked=0,
                      raw_substitution_bytes=0, trim=trim, artifacts=str(out))
        if diff:
            result['text'] = json.dumps(members, indent=2)
    except (OSError, ValueError, KeyError, RuntimeError, subprocess.TimeoutExpired) as e:
        result = {'exact': False, 'status': 'native-build-failed', 'err': str(e),
                  'module': m['key'], 'module_fingerprint': before, 'artifacts': str(out)}
    if fingerprint(row) != before:
        raise RuntimeError('native module context changed during score; remeasure')
    (out / 'score.json').write_text(json.dumps(result, indent=2) + '\n')
    return result
