"""Tests for type_flow.py (graph extraction) and type_flow_solve.py (components, evidence, verdicts)."""
from __future__ import annotations

import gzip
import json
from pathlib import Path
import shutil
import subprocess
import sys

import pytest

HERE = Path(__file__).resolve().parent
sys.path[:0] = [str(HERE), str(HERE.parent)]
import cast_ast as A  # noqa: E402
import type_flow as F  # noqa: E402
import type_flow_solve as S  # noqa: E402

pytestmark = pytest.mark.skipif(shutil.which('clang') is None, reason='clang not installed')

HEADER = r'''
typedef int s32;
typedef unsigned char u8;
typedef struct Body { s32 hp; s32 speed; struct Body *target; } Body;
typedef struct Owner { Body *body; s32 handle; void (*cb)(Body *b, s32 n); } Owner;
extern Owner owner_table;
'''

SOURCE = r'''
#include "flow.h"
static s32 shared_count;
void callee(s32 value) { shared_count = *(s32 *)((u8 *)value + 4); }
void handler(Body *b, s32 n) { b->hp = n; }
void viewer(void *p) { ((Body *)p)->speed = 1; }
void caller(Body *body) {
    s32 holder = (s32)body;
    callee(holder);
    owner_table.handle = (s32)body;
    owner_table.cb = handler;
    owner_table.cb(body, 3);
    viewer(body);
}
'''


def extract(tmp_path):
    (tmp_path / 'include').mkdir()
    (tmp_path / 'include' / 'flow.h').write_text(HEADER)
    (tmp_path / 'src').mkdir()
    (tmp_path / 'src' / 'flow.c').write_text(SOURCE)
    unit, err = A.clang_unit(tmp_path, 'src/flow.c')
    assert unit is not None, err
    return F.Extract(unit).run().dump()


def test_extract_edges_uses(tmp_path):
    d = extract(tmp_path)
    edges = {(e['k'], e['dst'], e['src']) for e in d['edges']}
    assert ('init', 'L:caller:holder@8', 'P:caller#0') in edges
    assert ('arg', 'P:callee#0', 'L:caller:holder@8') in edges
    assert ('assign', 'F:Owner.handle', 'P:caller#0') in edges            # integer field holding a pointer
    assert ('assign', 'F:Owner.cb', 'FN:handler') in edges               # slot install
    assert ('arg', 'F:Owner.cb#0', 'P:caller#0') in edges                # indirect call through the slot
    raw = [u for u in d['uses'] if u['ctx'] == 'raw']
    assert raw and raw[0]['node'] == 'P:callee#0' and raw[0]['off'] == 4 and raw[0]['wtype'] == 's32'
    member = [u for u in d['uses'] if u['ctx'] == 'member']
    assert member and member[0]['node'] == 'P:viewer#0' and member[0]['cast'] == 'Body *'
    macc = [u for u in d['uses'] if u['ctx'] == 'macc' and u['node'] == 'P:handler#0']
    assert macc and macc[0]['off'] == 0 and macc[0]['member'] == 'hp'
    assert d['records']['Body']['size'] == 12
    statics = [f for f in d['functions'] if f['static']]
    assert not statics                                                  # no static functions in the sample


def test_fn_types():
    assert F.fn_param_types('int (void *, int)') == ['void *', 'int']
    assert F.fn_param_types('void (void)') == []
    assert F.fn_param_types('void ()') is None
    assert F.fn_param_types('void (void (*)(int, int), s32)') == ['void (*)(int, int)', 's32']
    assert F.fnptr_arity('void (*)(Body *, s32)') == 2


def write_graph(tmp_path, d):
    g = tmp_path / 'graph' / 'tu'
    g.mkdir(parents=True)
    with gzip.open(g / 'flow.json.gz', 'wt') as fh:
        json.dump(d, fh)
    return tmp_path / 'graph'


def write_rt(tmp_path, rows, kinds=()):
    rt = tmp_path / 'rt'
    rt.mkdir()
    lines = ['file\tfunction\tcalls\tnparams\targ\tparam_type\tobservations\theap_kinds\tvalues']
    for fn, arg, values in rows:
        lines.append('src/flow.c\t%s\t10\t\t%d\t\t10\t1\t%s' % (fn, arg, values))
    (rt / 'fn_args.tsv').write_text('\n'.join(lines) + '\n')
    (rt / 'kinds_rt.json').write_text(json.dumps({'kinds': list(kinds)}))
    return rt


def test_component_solves_caller_local_and_callee_together(tmp_path):
    d = extract(tmp_path)
    g = S.Graph(write_graph(tmp_path, d))
    rt = S.Runtime(write_rt(tmp_path, [('caller', 0, 'rk1+0x20=10'), ('callee', 0, 'rk1+0x20=10'),
                                       ('handler', 0, 'rk1+0x20=10')]), g)
    assert rt.winner(('heap', 'rk1', 0x20))[0] == 'rec:Body*'
    seeds = [{'src': 't', 'file': 'src/flow.c', 'function': 'callee', 'arg': '0', 'target': 'Body *', 'hold': 'h'}]
    solver, comps = S.solve_all(g, rt, seeds)
    assert len(comps) == 1
    cid, seeds_here, comp, boundary, res = comps[0]
    changed = {n for n, v in comp.items() if v['st'] == 'retype'}
    # the callee's parameter and the caller's integer holder change together
    assert changed == {'P:callee#0', 'L:caller:holder@8'}
    # (s32)body cast into the holder disappears and the raw read folds to a member (2 casts)
    assert res['removed'] >= 2
    verdict, _ = S.verdict_of(g, rt, seeds_here, comp, res)
    assert verdict == 'whole'


def test_cast_evidence(tmp_path):
    d = extract(tmp_path)
    g = S.Graph(write_graph(tmp_path, d))
    rt = S.Runtime(write_rt(tmp_path, [('caller', 0, 'rk1+0x20=10'), ('handler', 0, 'rk1+0x20=10'),
                                       ('viewer', 0, 'rk1+0x20=10')]), g)
    cells = rt.pointer_cells('P:viewer#0')
    assert rt.cast_ok(cells, 0, 'Body *') == 'correct'
    assert rt.cast_ok(cells, 0, 'u8 *') == 'neutral'
    assert rt.cast_ok(cells, 4, 'Body *') == 'unproven'
    # a second voter for another type makes a minority view still correct only above 25%
    assert rt.cast_ok(cells, 0, 'Owner *') == 'wrong'


def test_merge_components_sharing_a_node(tmp_path):
    d = extract(tmp_path)
    g = S.Graph(write_graph(tmp_path, d))
    rt = S.Runtime(write_rt(tmp_path, [('caller', 0, 'rk1+0x20=10'), ('callee', 0, 'rk1+0x20=10')]), g)
    seeds = [{'src': 't', 'file': 'src/flow.c', 'function': 'callee', 'arg': '0', 'target': 'Body *', 'hold': 'h'},
             {'src': 't', 'file': 'src/flow.c', 'function': 'callee', 'arg': '0', 'target': 'Body *', 'hold': 'h2'}]
    _, comps = S.solve_all(g, rt, seeds)
    assert len(comps) == 1 and len(comps[0][1]) == 2


def test_macro_casts_are_not_debt(tmp_path):
    d = extract(tmp_path)
    gdir = write_graph(tmp_path, d)
    (gdir / 'index.json').write_text(json.dumps({'root': str(tmp_path), 'tus': {}}))
    g = S.Graph(gdir)
    # line 4 of flow.c spells two pointer casts; a line without casts caps any AST count at zero
    assert g.lexical_casts('src/flow.c', 4) == 2
    assert S.lexical_cap(g, {'file': 'src/flow.c', 'line': 2}, 3) == 0
    assert S.lexical_cap(g, {'file': 'src/flow.c', 'line': 4, 'macro': 1}, 2) == 0


def test_pruned_seed_is_held_and_pieces_split(tmp_path):
    d = extract(tmp_path)
    g = S.Graph(write_graph(tmp_path, d))
    rt = S.Runtime(write_rt(tmp_path, [('caller', 0, 'rk1+0x20=10'), ('callee', 0, 'rk1+0x20=10')]), g)
    # an extra call that omits the parameter: the seed's own node is pruned (arity) and the row is held
    g.calls_to['callee'].append({'caller': 'x', 'callee': 'callee', 'mode': 'direct', 'nargs': 0, 'nparams': 1,
                                 'file': 'src/x.c', 'line': 1})
    seeds = [{'src': 't', 'file': 'src/flow.c', 'function': 'callee', 'arg': '0', 'target': 'Body *', 'hold': 'h'}]
    solver, comps = S.solve_all(g, rt, seeds)
    pieces = S.split_pieces(solver, comps)
    held = [p for p in pieces if p[0].endswith('.held') or not any(v['st'] == 'retype' for v in p[2].values())]
    assert held and seeds[0]['node'] in comps[0][4]['pruned']
