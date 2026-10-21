"""Byte decision for planned TU edits: compile the TU before and after at its registered recipe (gcc -S
only) and accept a header include only when the assembly is identical.  Failing headers are isolated per
TU (each header alone, then the passing set together, then greedy) and become (TU, header) holds with the
mechanism ('bytes_changed' or the compiler's first error line).

This is the fast in-loop filter.  The formal proof remains tools/typing/tu_identity.py (raw object +
canonical assembly + canonical object over the -MM closure), run separately before and after.
"""
from __future__ import annotations

import hashlib
import os
import subprocess
import sys
import tempfile
from concurrent.futures import ProcessPoolExecutor
from pathlib import Path

HERE = Path(__file__).resolve().parent
sys.path[:0] = [str(HERE), str(HERE.parent)]


def _gcc_s(root, rel, recipe, text):
    """Assembly text for `text` compiled as TU `rel` (written under build_ovl with the same basename)."""
    root = Path(root)
    cc = root / 'toolchain/compilers' / ('gcc-' + recipe['cell'])
    flags = list(recipe['flags'])
    if '-O2' not in flags:
        flags = ['-O2'] + flags
    (root / 'build_ovl').mkdir(exist_ok=True)
    with tempfile.TemporaryDirectory(prefix='hdr-', dir=root / 'build_ovl') as td:
        src = Path(td) / Path(rel).name
        src.write_bytes(text.encode('utf-8', 'surrogateescape'))
        out = Path(td) / 'a.s'
        cmd = ['nice', '-n', '10', str(cc / 'gcc'), '-B' + str(cc) + '/', '-S', *flags,
               '-I' + str(root / 'include'), '-I' + str((root / rel).parent), '-w', src.name, '-o', str(out)]
        r = subprocess.run(cmd, cwd=td, capture_output=True, text=True)
        if r.returncode:
            lines = [l for l in (r.stderr or '').splitlines()
                     if l.strip() and not l.startswith('In file included') and not l.lstrip().startswith('from ')
                     and 'In function' not in l and 'At top level' not in l]
            err = [l for l in lines if 'error' in l.lower() or 'conflict' in l.lower()] or lines
            msg = (err[0] if err else r.stderr[-200:]).replace(td + '/', '').replace(str(root) + '/', '')
            return None, msg
        return out.read_bytes(), ''


def mechanism(before, after):
    """Short label for an assembly change caused by a prototype coming into scope."""
    import difflib
    a = before.decode(errors='replace').splitlines()
    b = after.decode(errors='replace').splitlines()
    changed = [l[1:].strip() for l in difflib.unified_diff(a, b, lineterm='', n=0)
               if l[:1] in '+-' and not l.startswith(('+++', '---'))]
    ops = {l.split()[0] for l in changed if l and not l.startswith(('.', '$', '#'))}
    if ops & {'andi', 'sll', 'sra', 'srl'}:
        return 'bytes_changed:argument_or_return_conversion'
    if ops & {'lh', 'lhu', 'lb', 'lbu'}:
        return 'bytes_changed:argument_load_width_or_sign'
    if not ops:
        return 'bytes_changed:directives_only'
    return 'bytes_changed:codegen(' + ','.join(sorted(ops))[:40] + ')'


def _digest(b):
    return hashlib.sha256(b).hexdigest() if b is not None else None


def decide(args):
    """Worker: (root, rel, recipe, original text, edit) -> verdict dict."""
    from rewrite import edit_tu
    root, rel, recipe, orig, edit = args
    order = list(edit['add'])
    full = edit_tu(orig, edit)
    base, err = _gcc_s(root, rel, recipe, orig)
    if base is None:
        return {'tu': rel, 'baseline_error': err, 'accept': [], 'holds': {h: 'baseline_error' for h in order}}
    bd = _digest(base)
    s, err = _gcc_s(root, rel, recipe, full)
    if s is not None and _digest(s) == bd:
        return {'tu': rel, 'accept': list(order), 'holds': {}, 'base': bd}
    holds, good = {}, []
    if len(order) == 1:
        holds[order[0]] = mechanism(base, s) if s is not None else 'compile_error: ' + err
        return {'tu': rel, 'accept': [], 'holds': holds, 'base': bd}
    for h in order:
        s1, e1 = _gcc_s(root, rel, recipe, edit_tu(orig, edit, [h]))
        if s1 is not None and _digest(s1) == bd:
            good.append(h)
        else:
            holds[h] = mechanism(base, s1) if s1 is not None else 'compile_error: ' + e1
    if len(good) <= 1:
        return {'tu': rel, 'accept': good, 'holds': holds, 'base': bd}
    s, err = _gcc_s(root, rel, recipe, edit_tu(orig, edit, good))
    if s is not None and _digest(s) == bd:
        return {'tu': rel, 'accept': good, 'holds': holds, 'base': bd}
    acc = []
    for h in good:                       # greedy, deterministic order
        trial = acc + [h]
        s, e = _gcc_s(root, rel, recipe, edit_tu(orig, edit, trial))
        if s is not None and _digest(s) == bd:
            acc = trial
        else:
            holds[h] = 'interaction_' + ('bytes_changed' if s is not None else 'compile_error: ' + e)
    return {'tu': rel, 'accept': acc, 'holds': holds, 'base': bd}


def run(root, jobs_in, recipes, workers=6, log=print):
    """jobs_in: {tu: (original text, edit)}.  Returns {tu: verdict}."""
    jobs, verdicts = [], {}
    for rel, (orig, edit) in sorted(jobs_in.items()):
        if not edit['add']:
            continue
        rec = recipes.get(rel)
        if rec is None or 'slus_unit' in rec:
            reason = 'not_a_physical_tu' if rec is None else 'slus_partition_unit'
            verdicts[rel] = {'tu': rel, 'accept': [], 'holds': {h: reason for h in edit['add']}}
            continue
        jobs.append((str(root), rel, rec, orig, edit))
    with ProcessPoolExecutor(max_workers=workers) as ex:
        for i, v in enumerate(ex.map(decide, jobs, chunksize=2)):
            verdicts[v['tu']] = v
            if (i + 1) % 200 == 0:
                log(f'  decided {i + 1}/{len(jobs)}')
                sys.stdout.flush()
    return verdicts


def explain(root, rel, recipe, orig, edit, header):
    """Human detail for one (TU, header) decision: compiler stderr or an assembly diff."""
    import difflib
    from rewrite import edit_tu
    base, err0 = _gcc_s(root, rel, recipe, orig)
    if base is None:
        return 'baseline does not compile: ' + err0
    new_text = edit_tu(orig, edit, [header])
    s, err = _gcc_s(root, rel, recipe, new_text)
    if s is None:
        return 'compile error: ' + err
    if s == base:
        return 'identical'
    d = difflib.unified_diff(base.decode(errors='replace').splitlines(), s.decode(errors='replace').splitlines(),
                             'before.s', 'after.s', lineterm='', n=2)
    return '\n'.join(list(d)[:80])
