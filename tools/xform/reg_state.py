"""Temporary compiler observations; patterns are diagnostics, never byte scores.

From the reg_astra lane (2026-09-13). observe(phases=...) parses only the named passes: a t53 candidate
needs its base's deciding pass, combine and greg (metrics), and parsing all 13-16 dumps of a large
function costs ~0.5 s of pure Python per compile, which the sweep's worker threads share under one GIL.
"""
import collections
import os
from pathlib import Path
import re
import subprocess
import sys
import tempfile

ROOT = next(p for p in Path(__file__).resolve().parents if (p / 'tools/common.py').is_file())
sys.path.insert(0, str(ROOT / 'tools'))
from common import parse_cfg
from xform.sched_trace import instructions, normalize, distance, close_paren

PHASES = ('rtl', 'jump', 'cse', 'loop', 'cse2', 'flow', 'combine', 'sched',
          'lreg', 'greg', 'sched2', 'jump2', 'dbr')
ANON = re.compile(r'\(reg(?:/\w+)?:([A-Z0-9]+) \d+(?: [^)]+)?\)')
ASM = re.compile('asm_operands|asm_input')
COPY = re.compile(r'^\(set \(reg:\w+\) \(reg:\w+\)\)$')
START = re.compile(r'^\((?:insn|jump_insn|call_insn)(?:/\w+)?\s+\d+\s+[-\d]+\s+[-\d]+\s+',re.M)
REG = re.compile(r'\(reg(?:/\w+)?:([A-Z0-9]+) (\d+)(?: [^)]+)?\)')
WS = re.compile(r'\s+')
LREF = re.compile(r'\(label_ref(?::\w+)? \d+\)')


def features(src):
    # Same instruction patterns and rename convention as phase_census.feats,
    # without repeatedly parsing notes/links or counting preceding newlines.
    raw,ab,regs = [],[],{}
    def rename(m):
        return '(reg:'+m[1]+' '+regs.setdefault(m[2],'R%d'%len(regs))+')'
    for m in START.finditer(src):
        a=m.end()
        if src[a:a+1]!='(': continue
        end=close_paren(src,a)
        if end is None: continue
        pat=WS.sub(' ',src[a:end])
        pat=LREF.sub('(label_ref LABEL)',pat)
        renamed=REG.sub(rename,pat)
        if not ASM.search(pat):
            raw.append(pat);ab.append(renamed)
    ops = [ANON.sub(r'(reg:\1)', x) for x in raw]
    nc = [x for x in ops if not COPY.match(x)]
    return dict(raw=raw, abs=ab, seq=nc, ms=collections.Counter(nc), copies=len(ops)-len(nc))


def observe(row, text, retain=None, phases=None):
    """Use only an automatically deleted temporary directory, including gcc -da dumps.

    TMPDIR is controlled by the caller (the lane evaluator sets it under scratch).
    retain is an analysis-only export directory, never used by the generator.
    phases: parse only these passes (None = all).
    """
    cell, flags = parse_cfg(row['cfg'])
    cc = ROOT / 'toolchain/compilers' / ('gcc-' + cell)
    with tempfile.TemporaryDirectory(prefix='t53_') as td:
        d = Path(td)
        f = d / Path(row['c_path']).name
        f.write_text(text)
        cmd = [str(cc / 'gcc'), '-B' + str(cc) + '/', '-S', '-O2', *flags,
               '-I' + str(ROOT / 'include'), '-w', '-da', f.name, '-o', 'f.s']
        try:
            p = subprocess.run(cmd, cwd=d, capture_output=True, text=True,
                               timeout=float(os.getenv('T53_TIMEOUT', '45')))
        except subprocess.TimeoutExpired:
            return dict(assembly=None, features={}, error='compiler-timeout')
        if p.returncode or not (d / 'f.s').exists():
            return dict(assembly=None, features={}, error=(p.stderr or p.stdout)[-1000:])
        raw = (d / 'f.s').read_text(errors='replace')
        want = PHASES if phases is None else tuple(phases)
        dumps = {p.suffix[1:]: p.read_text(errors='replace') for p in d.iterdir()
                 if p.suffix[1:] in want}
        if retain is not None:
            retain = Path(retain)
            retain.mkdir(parents=True, exist_ok=True)
            (retain / 'source.c').write_text(text)
            (retain / 'assembly.s').write_text(raw)
            for phase, src in dumps.items():
                (retain / ('dump.' + phase)).write_text(src)
        return dict(assembly=normalize(raw), features={p: features(s) for p, s in dumps.items()}, error=None)


def comparison(a, b):
    phases = {}
    for p in PHASES:
        if p not in a['features'] or p not in b['features']:
            continue
        x, y = a['features'][p], b['features'][p]
        phases[p] = {k: x[k] == y[k] for k in ('abs', 'seq', 'ms', 'raw')}
        phases[p].update(ops=[len(x['seq']), len(y['seq'])], copies=[x['copies'], y['copies']])
    first = {k: next((p for p in PHASES if p in phases and not phases[p][k]), None)
             for k in ('abs', 'seq', 'ms', 'raw')}
    c = phases.get('combine')
    cl = ('unknown' if c is None else 'ops' if not c['ms'] else 'order' if not c['seq']
          else 'wiring' if not c['abs'] else 'late')
    return dict(phases=phases, first=first, cls=cl, asm_distance=distance(a['assembly'], b['assembly']))


def mismatch(a, b):
    return sum(x != y for x, y in zip(a, b)) + abs(len(a)-len(b))


def metrics(target, cand, phase):
    result = {'asm': distance(target['assembly'], cand['assembly']), 'phase': phase}
    for label, p, key in [('p', phase, 'abs'), ('combine', 'combine', 'abs'),
                          ('greg', 'greg', 'abs'), ('greg_raw', 'greg', 'raw')]:
        a, b = target['features'].get(p), cand['features'].get(p)
        result[label] = mismatch(a[key], b[key]) if a is not None and b is not None else None
    return result
