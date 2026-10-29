#!/usr/bin/env python3
"""Neutral-set prober: compile one TU at its production recipe once per candidate spelling of a function.

A probe never edits a tracked file.  The variant text is written next to the TU as
`.sigprobe_<pid>_<file>.c` (so quoted includes resolve exactly as for the TU), compiled by the root's own
`tools/build/mkbuild.compile_uncached` with the recipe's args, environment, evidence and live noreturn
derivation, into `build/.sigprobe/<pid>/`, and deleted.  Objects compiled from a sibling path differ from
the production object only in metadata (STT_FILE), so the comparison is `abi_facts.object_difference`:
allocated section bytes, relocations and the global symbol set.

Every variant uses the "hide" construction: each `#include` directive is wrapped in
`#define NAME __sigprobe_NAME` / `#undef NAME`, so every header declaration of NAME is renamed away,
the TU's own declarations of NAME are removed, and the candidate prototype is inserted once before the
first top-level item that mentions NAME.  The control variant re-inserts the spelling the TU sees today
(its own declarations, else the first header declaration in its include closure, else none), and must
itself equal the production object (`calibrated`); a variant is neutral when it equals the control.

    sig_probe.py --root R --recipe RID --name NAME --decl 's32 NAME(s32 a, s32 b)' [--decl ...]

Workers: at most 8, nice 10, one variant file per worker at a time.
"""
from __future__ import annotations

import argparse
import json
import os
from pathlib import Path
import queue
import re
import shutil
import subprocess
import sys
import threading
import time

HERE = Path(__file__).resolve()
TOOLS = HERE.parents[1]
for p in (str(TOOLS), str(TOOLS / 'headers'), str(HERE.parent)):
    if p not in sys.path:
        sys.path.insert(0, p)

import cscan  # noqa: E402

HIDDEN = '__sigprobe_'
_SCANS = {}


def scan(text):
    """cscan.scan memoised by text (a TU is scanned once for all its variants)."""
    key = hash(text)
    hit = _SCANS.get(key)
    if hit is None or hit[0] != text:
        if len(_SCANS) > 256:
            _SCANS.clear()
        hit = _SCANS[key] = (text, cscan.scan(text))
    return hit[1]
INT_RANGE = {'s8': (-0x80, 0x7f), 'u8': (0, 0xff), 's16': (-0x8000, 0x7fff), 'u16': (0, 0xffff),
             's32': (-0x80000000, 0x7fffffff), 'u32': (0, 0xffffffff)}


# ------------------------------------------------------------------------------------- text variants

def _line_span(text, start, end):
    """Whole lines when the item stands alone on them (a trailing `/* extern */` marker included)."""
    ls = text.rfind('\n', 0, start) + 1
    le = text.find('\n', end)
    le = len(text) if le < 0 else le + 1
    if text[ls:start].strip() == '' and re.fullmatch(r'\s*(/\*[^\n]*?\*/\s*)?', text[end:le]):
        return ls, le
    return start, end


def mentions(masked, name):
    return re.search(r'(?<![\w$])' + re.escape(name) + r'(?![\w$])', masked) is not None


def insertion_point(text, name, removed=(), sc=None):
    """Offset (a line start) before the first top-level item that mentions `name` (or the first removed
    declaration), and after every include directive that precedes it."""
    sc = sc or scan(text)
    first = None
    for it in sc.items:
        if mentions(sc.masked[it.start:it.end], name):
            first = it.start
            break
    cands = [x for x in [first] + [s for s, e in removed] if x is not None]
    pos = min(cands) if cands else len(text)
    return text.rfind('\n', 0, pos) + 1 if pos else 0


def split_proto(text, name):
    """('ret part before the name', 'parameter list text') of a single-declarator declaration text."""
    m = re.search(r'(?<![\w$])' + re.escape(name) + r'\s*\(', text)
    if not m:
        raise ValueError('no declarator for %s in %r' % (name, text[:80]))
    depth, i = 0, m.end() - 1
    for j in range(i, len(text)):
        if text[j] == '(':
            depth += 1
        elif text[j] == ')':
            depth -= 1
            if depth == 0:
                return text[:m.start()], text[i + 1:j]
    raise ValueError('unbalanced parameter list for ' + name)


STORAGE = ('extern', 'static', 'inline', '__inline__', 'register')


def ret_text(prefix):
    """The return type spelling of a declaration prefix (storage classes and comments dropped)."""
    prefix = re.sub(r'/\*.*?\*/', ' ', prefix, flags=re.S)
    toks = [t for t in re.findall(r'[A-Za-z_]\w*|\*', prefix) if t not in STORAGE]
    out = ' '.join(t for t in toks if t != '*') + (' ' + '*' * toks.count('*') if '*' in toks else '')
    return out.strip()


def proto(ret, name, params):
    sep = '' if ret.endswith('*') else ' '
    return '%s%s%s(%s)' % (ret, sep, name, params.strip())


def narrow_returns(body_text, body_masked, narrow):
    """Wrap each `return EXPR;` of a body in `(narrow)` unless EXPR is an in-range integer constant or
    already that cast.  Returns (new body, count of casts added)."""
    lo, hi = INT_RANGE[narrow]
    edits = []
    for m in re.finditer(r'(?<![\w$])return(?![\w$])', body_masked):
        j, depth = m.end(), 0
        while j < len(body_masked):
            c = body_masked[j]
            if c in '([{':
                depth += 1
            elif c in ')]}':
                depth -= 1
            elif c == ';' and depth == 0:
                break
            j += 1
        expr = body_text[m.end():j]
        e = expr.strip()
        if not e:
            continue
        lit = re.fullmatch(r'\(?\s*(-?)\s*(0[xX][0-9a-fA-F]+|\d+)[uUlL]*\s*\)?', e)
        if lit:
            v = int(lit.group(2), 0) * (-1 if lit.group(1) else 1)
            if lo <= v <= hi:
                continue
        if re.match(r'\(\s*' + narrow + r'\s*\)', e):
            continue
        simple = re.fullmatch(r'[A-Za-z_]\w*|-?(0[xX][0-9a-fA-F]+|\d+)[uUlL]*', e) or (e.startswith('(') and _balanced_whole(e))
        new = ' (%s)%s' % (narrow, e if simple else '(' + e + ')')
        edits.append((m.end(), j, new))
    out = body_text
    for s, e, new in reversed(edits):
        out = out[:s] + new + out[e:]
    return out, len(edits)


def _balanced_whole(e):
    depth = 0
    for i, c in enumerate(e):
        if c == '(':
            depth += 1
        elif c == ')':
            depth -= 1
            if depth == 0 and i != len(e) - 1:
                return False
    return depth == 0


def retype_definition(text, name, new_ret, narrow=None, sc=None):
    """Definition of `name` respelled with return type `new_ret`; when `narrow` is given every returned
    value is narrowed in the body (the width rule: ABI-wide prototype, narrowing kept in the callee).
    Returns (text, casts added) or raises ValueError when there is no single definition."""
    sc = sc or scan(text)
    defs = [it for it in sc.items if it.kind == 'def' and it.decls and it.decls[0].name == name]
    if len(defs) != 1:
        raise ValueError('expected one definition of %s, found %d' % (name, len(defs)))
    it = defs[0]
    head_m = sc.masked[it.start:it.body[0]]
    m = re.search(r'(?<![\w$])' + re.escape(name) + r'\s*\(', head_m)
    toks = list(re.finditer(r'[A-Za-z_]\w*|\*', head_m[:m.start()]))
    keep = [t for t in toks if t.group(0) in STORAGE]
    typ = [t for t in toks if t.group(0) not in STORAGE]
    if not typ:
        raise ValueError('definition of %s has no return type' % name)
    a, b = it.start + typ[0].start(), it.start + typ[-1].end()
    gap = text[b:it.start + m.start()]
    new_head = new_ret + ('' if new_ret.endswith('*') else (gap if gap.strip() == '' and gap else ' '))
    added = 0
    body_s, body_e = it.body
    body = text[body_s:body_e]
    if narrow:
        body, added = narrow_returns(body, sc.masked[body_s:body_e], narrow)
    del keep
    return text[:a] + new_head + text[it.start + m.start():body_s] + body + text[body_e:], added


def hide_variant(text, name, remove=(), decl=None, def_rewrite=None, type_headers=(), tags=()):
    """Probe text: header declarations of `name` renamed away, `remove` spans deleted, `decl` (a
    prototype without ';') inserted, and optionally the definition respelled (def_rewrite =
    (new_ret, narrow)).  Pure."""
    sc = scan(text)
    edits = []          # (start, end, replacement)
    for d in sc.directives:
        if d.kind == 'include':
            line = text[d.start:d.end]
            if not line.endswith('\n'):
                line += '\n'
            edits.append((d.start, d.end, '#define %s %s%s\n%s#undef %s\n' % (name, HIDDEN, name, line, name)))
    spans = sorted({_line_span(text, s, e) for s, e in remove})
    for s, e in spans:
        edits.append((s, e, ''))
    if decl is not None:
        at = insertion_point(text, name, spans, sc)
        if any(s < at < e for s, e, _ in edits):
            raise ValueError('insertion point inside an edited span')
        # the types the owning header's prototype needs (its type includes and tag declarations), as the
        # transaction's #include of that header would bring them
        pre = ''.join('#define %s %s%s\n#include "%s"\n#undef %s\n' % (name, HIDDEN, name, h, name)
                      for h in type_headers) + ''.join('%s;\n' % t for t in tags)
        edits.append((at, at, pre + ('extern %s;\n' % decl if not decl.lstrip().startswith('extern')
                                     else decl + ';\n')))
    out = text
    for s, e, rep in sorted(edits, key=lambda x: (x[0], x[1]), reverse=True):
        out = out[:s] + rep + out[e:]
    if def_rewrite:
        out, _ = retype_definition(out, name, def_rewrite[0], def_rewrite[1])
    return out


def local_decls(text, name, sc=None):
    """[(start, end, ndecl, text)] of the file-scope function declarations of `name` in a text."""
    sc = sc or scan(text)
    out = []
    for it in sc.items:
        if it.kind != 'decl' or 'typedef' in it.storage:
            continue
        for d in it.decls:
            if d.is_function and d.name == name:
                out.append((it.start, it.end, len(it.decls), it.text))
    return out


# --------------------------------------------------------------------------------------------- workers

WORKER_BOOT = r'''
import os, sys
root = sys.argv[1]; sys.path.insert(0, root); os.chdir(root)
import importlib.util
spec = importlib.util.spec_from_file_location('sigprobe_worker', sys.argv[2])
module = importlib.util.module_from_spec(spec); spec.loader.exec_module(module)
module.worker_loop(root)
'''


def worker_loop(root):
    import contextlib
    import io
    import tempfile
    from tools.build import mkbuild as mk
    if mk.ROOT != Path(root).resolve():
        raise SystemExit('worker imported mkbuild from another root: ' + str(mk.ROOT))
    tmp = mk.STATE / 'tmp'
    tmp.mkdir(parents=True, exist_ok=True)
    os.environ['TMPDIR'] = str(tmp)
    tempfile.tempdir = str(tmp)
    run = Path('build/.sigprobe') / str(os.getpid())
    (mk.ROOT / run).mkdir(parents=True, exist_ok=True)
    out = sys.stdout
    for line in sys.stdin:
        task = json.loads(line)
        started = time.monotonic()
        sink = io.StringIO()
        try:
            with contextlib.redirect_stdout(sink), contextlib.redirect_stderr(sink):
                result = _compile_variant(mk, run, task)
        except Exception as exc:
            result = dict(error=(type(exc).__name__ + ': ' + str(exc))[-1200:])
        result.update(key=task['key'], seconds=round(time.monotonic() - started, 3))
        out.write(json.dumps(result) + '\n')
        out.flush()


def _compile_variant(mk, run, task):
    spec = mk.read(mk.STATE / 'recipes' / (task['recipe'] + '.json'))
    if spec.get('projection'):
        raise ValueError('placement copies are proven by the transaction, not probed')
    src = Path(spec['source'])
    tag = re.sub(r'[^\w.-]', '_', task['key'])[-80:]
    obj = run / (tag + '.o')
    if spec.get('assembler') == 'genuine_aspsx_verified':
        # Native (genuine ASPSX) modules: the probe compares gcc's code through the ordinary
        # maspsx pipeline at the same compiler args (`proxy`): identical gcc output is identical under
        # either assembler, so control-vs-variant neutrality carries over.  The native builder itself
        # re-validates its manifest entry and retail bytes and is left to the transaction proof.
        spec.pop('assembler', None)
        spec.pop('module', None)
    if task.get('text') is None:
        shadow = None
    else:
        shadow = src.parent / ('.sigprobe_%d_%s' % (os.getpid(), src.name))
        (mk.ROOT / shadow).write_text(task['text'], encoding='utf-8', errors='surrogateescape')
        spec['source'] = str(shadow)
    spec['output'] = str(obj)
    if spec.get('name_input'):
        spec['name_input'] = str(run / (tag + '.names.json'))
    path = mk.ROOT / run / (tag + '.json')
    mk.put(path, spec)
    try:
        mk.compile_uncached(path)
    finally:
        if shadow is not None:
            (mk.ROOT / shadow).unlink(missing_ok=True)
        path.unlink(missing_ok=True)
        for extra in (obj.with_suffix('.proof.json'), obj.with_suffix('.noreturn.txt'),
                      run / (tag + '.names.json')):
            (mk.ROOT / extra).unlink(missing_ok=True)
    return dict(object=str(obj))


class Workers:
    def __init__(self, root, n=8, nice=10):
        if not 1 <= n <= 8:
            raise ValueError('between 1 and 8 workers on this host')
        self.root = Path(root).resolve()
        boot = [sys.executable, '-c', WORKER_BOOT, str(self.root), str(HERE)]
        pre = (lambda: os.nice(nice)) if nice else None
        self.procs = [subprocess.Popen(boot, cwd=self.root, stdin=subprocess.PIPE, stdout=subprocess.PIPE,
                                       text=True, preexec_fn=pre) for _ in range(n)]
        self.free = queue.Queue()
        for p in self.procs:
            self.free.put(p)
        self.compiles = 0
        self.seconds = 0.0
        self._lock = threading.Lock()
        self._locks = {}

    def call(self, task):
        lock = None
        if task.get('lock'):
            with self._lock:
                lock = self._locks.setdefault(task['lock'], threading.Lock())
            lock.acquire()
        try:
            return self._call(task)
        finally:
            if lock is not None:
                lock.release()

    def _call(self, task):
        proc = self.free.get()
        try:
            proc.stdin.write(json.dumps(task) + '\n')
            proc.stdin.flush()
            line = proc.stdout.readline()
            if not line:
                raise RuntimeError('probe worker %d exited' % proc.pid)
            res = json.loads(line)
        finally:
            self.free.put(proc)
        with self._lock:
            self.compiles += 1
            self.seconds += res.get('seconds', 0)
        if 'object' in res:
            path = self.root / res['object']
            res['blob'] = path.read_bytes()
            path.unlink(missing_ok=True)
        return res

    def map(self, tasks):
        from concurrent.futures import ThreadPoolExecutor
        with ThreadPoolExecutor(max_workers=len(self.procs)) as ex:
            return list(ex.map(self.call, tasks))

    def close(self):
        for p in self.procs:
            try:
                p.stdin.close()
                p.wait(timeout=60)
            except Exception:
                if p.poll() is None:
                    p.kill()          # our own child, by its handle
        for p in self.procs:
            shutil.rmtree(self.root / 'build/.sigprobe' / str(p.pid), ignore_errors=True)


def compare(control, variant):
    """None when equivalent (see abi_facts.object_difference), else the difference / error."""
    import abi_facts
    if 'error' in variant:
        return dict(kind='error', detail=variant['error'][-300:])
    if 'error' in control:
        return dict(kind='control_error', detail=control['error'][-300:])
    return abi_facts.object_difference(control['blob'], variant['blob'])


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument('--root', type=Path, default=HERE.parents[2])
    ap.add_argument('--recipe', required=True)
    ap.add_argument('--name', required=True)
    ap.add_argument('--decl', action='append', default=[])
    args = ap.parse_args(argv)
    root = args.root.resolve()
    spec = json.loads((root / 'build/.state/recipes' / (args.recipe + '.json')).read_text())
    text = (root / spec['source']).read_text(encoding='utf-8', errors='surrogateescape')
    tasks = [dict(key='production', recipe=args.recipe, text=None),
             dict(key='control', recipe=args.recipe, text=hide_variant(text, args.name))]
    spans = [(a, b) for a, b, n, _ in local_decls(text, args.name)]
    for n, d in enumerate(args.decl):
        tasks.append(dict(key='decl%d' % n, recipe=args.recipe,
                          text=hide_variant(text, args.name, remove=spans, decl=d)))
    pool = Workers(root, min(8, len(tasks)))
    try:
        res = pool.map(tasks)
    finally:
        pool.close()
    prod, ctrl = res[0], res[1]
    print('control vs production:', compare(prod, ctrl))
    for t, r in zip(tasks[2:], res[2:]):
        print(t['key'], args.decl[int(t['key'][4:])], '->', compare(ctrl, r) or 'NEUTRAL')
    return 0


if __name__ == '__main__':
    sys.exit(main())
