#!/usr/bin/env python3
"""Consensus over probed sites: one canonical prototype per function name, or a recorded floor.

Pure (no compiler, no files): input is the definition's spellings and, per TU that defines or uses the
name, which candidate spellings left its object identical (sig_solver.py fills these from sig_probe).

Candidates (owner rulings 2026-10-29):
  * 'D' - the definition's own prototype (most specific: its parameter and return types);
  * 'W' - the width rule: an ABI-wide `s32` (or `u32`) return when the definition returns a narrow integer,
          the narrowing moved into the definition body (`return (s16)index;`).
Choice: the first candidate neutral at every site (D before W).  Parameter types are always the
definition's (a prototype that disagrees with the definition does not compile), so a site that needs a
different parameter width blocks every candidate.

A refusal is a floor record for ledger/prototype_floors.jsonl: name, owner, floor class, the callee ABI
facts, the sites partitioned by the spelling they accept, and each blocking site with its reason.
Floor classes:
  phantom_arguments    sites declare/pass more arguments than the callee reads (m2c register artefacts)
  varying_arity        sites disagree with the definition's arity and the callee reads them
  param_width          a site's argument conversion depends on its own (narrow) parameter spelling
  return_width         a site needs a narrow return the definition cannot publish (or vice versa) and
                       the wide prototype is not neutral there either
  unprobeable          a site could not be probed (no recipe, included fragment, uncalibrated control)
  name_hold            the planner holds the name itself (no single definition, K&R, varargs, ...)
"""
from __future__ import annotations

from collections import defaultdict

FLOOR_ORDER = ('name_hold', 'unprobeable', 'phantom_arguments', 'varying_arity', 'param_width', 'return_width',
               'compile_error')
WIDE = {'s8': 's32', 's16': 's32', 'u8': 'u32', 'u16': 'u32', 'char': 's32'}


def wide_return(ret):
    """ABI-wide spelling for a narrow integer return type, else None."""
    return WIDE.get(ret.strip())


def site_reason(site, choice, def_arity, callee_arity):
    """Why `choice` is not neutral at one probed site."""
    if site.get('blocked'):
        return site['blocked']
    if not site.get('calibrated', False):
        return 'unprobeable:uncalibrated'
    res = site.get('results', {})
    err = str((site.get('detail') or {}).get(choice, ''))
    if res.get(choice) == 'error' and 'too many arguments' in err:
        return 'phantom_arguments'
    if res.get(choice) == 'error' and 'too few arguments' in err:
        return 'varying_arity'
    if res.get(choice) == 'error':
        if site.get('arity') is not None and site['arity'] != def_arity:
            return 'phantom_arguments' if callee_arity is not None and site['arity'] > callee_arity \
                else 'varying_arity'
        return 'compile_error'
    if site.get('arity') is not None and site['arity'] != def_arity:
        return 'phantom_arguments' if callee_arity is not None and site['arity'] > callee_arity \
            else 'varying_arity'
    par_ok = res.get('par_D', 'same') in ('same', 'neutral')
    if not par_ok:
        return 'param_width'
    return 'return_width'


def decide(name, owner, definition, sites, abi=None, hold=None, candidates=('D', 'W')):
    """Decision record for one name.

    definition: {'path', 'proto', 'ret', 'params', 'arity'}; sites: [{'path', 'is_def', 'calibrated',
    'blocked', 'arity', 'spelling', 'results': {variant: 'neutral'|'changed'|'error'|'same'}}];
    abi: abi_facts.Facts.summary() of the callee (optional)."""
    rec = dict(name=name, owner=owner, definition=definition, abi=abi or {}, sites=len(sites),
               unbuilt=sorted(s['path'] for s in sites if s.get('unbuilt')))
    sites = [s for s in sites if not s.get('unbuilt')]
    if hold:
        rec.update(status='refused', floor_class='name_hold', reason=hold, blocking=[], partitions=[])
        return rec
    callee_arity = None
    if abi and abi.get('arity') and len(abi['arity']) == 1:
        callee_arity = abi['arity'][0]
    avail = [c for c in candidates if c == 'D' or (c == 'W' and wide_return(definition['ret']))]
    for c in avail:
        if all(s.get('calibrated') and not s.get('blocked') and s.get('results', {}).get(c) == 'neutral'
               for s in sites):
            rec.update(status='unified', choice=c, narrowing=definition['ret'] if c == 'W' else None,
                       ret=definition['ret'] if c == 'D' else wide_return(definition['ret']))
            return rec
    # refusal: partition the sites by the candidates they accept, name the blockers of the best candidate
    parts = defaultdict(list)
    for s in sites:
        ok = tuple(c for c in avail if s.get('calibrated') and not s.get('blocked')
                   and s.get('results', {}).get(c) == 'neutral')
        parts[ok].append(s)
    best = max(avail, key=lambda c: sum(1 for s in sites if s.get('results', {}).get(c) == 'neutral'))
    blocking = []
    for s in sites:
        if s.get('calibrated') and not s.get('blocked') and s.get('results', {}).get(best) == 'neutral':
            continue
        blocking.append(dict(path=s['path'], is_def=s.get('is_def', False), spelling=s.get('spelling'),
                             reason=site_reason(s, best, definition.get('arity'), callee_arity),
                             detail=s.get('detail', {}).get(best)))
    classes = {b['reason'].split(':')[0] for b in blocking}
    castable = [b for b in blocking if b['reason'] in ('param_width', 'return_width')]
    # owner trade-off: call-site casts are not allowed (casts must not increase); count what they would buy
    rec['casts_would_unify'] = dict(sites=len(castable), sufficient=len(castable) == len(blocking) > 0,
                                    kinds=sorted({b['reason'] for b in castable}))
    floor = next((c for c in FLOOR_ORDER if c in classes), 'return_width')
    rec.update(status='refused', floor_class=floor, best=best, blocking=blocking,
               partitions=[dict(accepts=list(k) or ['none'], sites=sorted(s['path'] for s in v),
                                spellings=sorted({s.get('spelling') or '' for s in v}))
                           for k, v in sorted(parts.items(), key=lambda kv: -len(kv[1]))])
    return rec


def floor_record(rec, evidence):
    """ledger/prototype_floors.jsonl row for a refused decision."""
    return dict(schema='azure-clean.prototype-floor.v1', name=rec['name'], owner=rec.get('owner'),
                status=rec.get('status', 'refused'), floor_class=rec['floor_class'], reason=rec.get('reason'),
                definition=dict(path=rec['definition'].get('path'), proto=rec['definition'].get('proto')),
                abi={k: rec['abi'][k] for k in ('arity', 'returns', 'ret_fits', 'v0_use', 'args_set_up')
                     if k in rec.get('abi', {})},
                partitions=rec.get('partitions', []), casts_would_unify=rec.get('casts_would_unify'),
                blocking=[{k: v for k, v in b.items() if k != 'detail'} for b in rec.get('blocking', [])],
                evidence=evidence)


def load_floors(path):
    """{name: record} from a floors ledger (missing file -> empty)."""
    import json
    from pathlib import Path
    out = {}
    p = Path(path)
    if p.is_file():
        for line in p.read_text().splitlines():
            if line.strip():
                r = json.loads(line)
                out[r['name']] = r
    return out
