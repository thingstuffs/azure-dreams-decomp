"""Tests for type_flow_static.py: anchors, admission, runtime precedence, installer respelling, static verdicts."""
from __future__ import annotations

import collections
import shutil
import sys
from pathlib import Path

import pytest

HERE = Path(__file__).resolve().parent
sys.path[:0] = [str(HERE), str(HERE.parent)]
import cast_ast as A  # noqa: E402
import type_flow as F  # noqa: E402
import type_flow_solve as S  # noqa: E402
import type_flow_static as T  # noqa: E402
from test_type_flow import write_graph, write_rt  # noqa: E402

pytestmark = pytest.mark.skipif(shutil.which('clang') is None, reason='clang not installed')

HEADER = r'''
typedef int s32;
typedef unsigned char u8;
typedef struct Body { s32 hp; s32 speed; struct Body *target; } Body;
typedef struct Other { s32 a; s32 b; s32 c; s32 d; } Other;
typedef struct S_80001000 { s32 unk_00; s32 unk_04; } S_80001000;
typedef struct Owner { Body *body; s32 handle; void (*cb)(Body *b, s32 n); void *any; } Owner;
extern Owner owner_table;
extern s32 cb_alias_address;
'''

SOURCE = r'''
#include "flow.h"
static s32 sink;
void never_run(void *p) { ((S_80001000 *)p)->unk_04 = 1; }
void typed_caller_a(Body *b) { never_run(b); }
void typed_caller_b(Body *b) { never_run(b); }
void mixed(void *p) { ((S_80001000 *)p)->unk_00 = 2; }
void mixed_a(Body *b) { mixed(b); }
void mixed_b(Other *o) { mixed(o); }
void cb_open(void *p, s32 n) { ((S_80001000 *)p)->unk_04 = n; }
void install(void) { owner_table.cb = (void (*)(Body *, s32))cb_open; }
void observed(void *p) { ((S_80001000 *)p)->unk_00 = 3; }
void observed_caller(Other *o) { observed(o); }
void one_caller(void *p) { ((S_80001000 *)p)->unk_04 = 4; }
void one_caller_a(Body *b, s32 k) { one_caller(b); one_caller((void *)k); }
void cb_alias(void *p, s32 n) { ((S_80001000 *)p)->unk_00 = n; }
void install_alias(void) { owner_table.any = &cb_alias_address; }
'''


def graph(tmp_path):
    (tmp_path / 'include').mkdir()
    (tmp_path / 'include' / 'flow.h').write_text(HEADER)
    (tmp_path / 'src').mkdir()
    (tmp_path / 'src' / 'flow.c').write_text(SOURCE)
    unit, err = A.clang_unit(tmp_path, 'src/flow.c')
    assert unit is not None, err
    return S.Graph(write_graph(tmp_path, F.Extract(unit).run().dump()))


def setup(tmp_path, rows=()):
    g = graph(tmp_path)
    rt = T.StaticRuntime(write_rt(tmp_path, list(rows)), g)
    solver = S.Solver(g, rt)
    labels, out = T.install_static(g, rt, solver)
    return g, rt, solver, labels, {r['node']: r for r in out}


def test_every_typed_caller_admits_a_strong_label(tmp_path):
    g, rt, solver, labels, rows = setup(tmp_path)
    r = rows['P:never_run#0']
    assert r['status'] == 'admitted' and r['type'] == 'Body *' and 'caller_all' in r['reason']
    assert rt.pointer_cells('P:never_run#0') == collections.Counter({('static', 'rec:Body*', 0): 2})
    assert rt.cast_ok(rt.pointer_cells('P:never_run#0'), 0, 'Body *') == 'static_ok'
    assert rt.cast_ok(rt.pointer_cells('P:never_run#0'), 0, 'Other *') == 'wrong'


def test_disagreeing_anchors_are_mixed_and_polymorphic(tmp_path):
    g, rt, solver, labels, rows = setup(tmp_path)
    assert rows['P:mixed#0']['status'] == 'mixed'
    t, share, cells = rt.node_type('P:mixed#0')
    assert len(cells) == 2 and share < 0.75 and solver.polymorphic('P:mixed#0')


def test_typed_slot_labels_an_installed_callback(tmp_path):
    g, rt, solver, labels, rows = setup(tmp_path)
    r = rows['P:cb_open#0']
    assert r['status'] == 'admitted' and r['type'] == 'Body *' and r['kind'] == 'slot_typed'


def test_runtime_cells_always_win(tmp_path):
    g, rt, solver, labels, rows = setup(tmp_path, rows=[('observed', 0, 'rk1+0x20=10'), ('observed_caller', 0, 'rk1+0x20=10')])
    assert 'P:observed#0' not in rows                     # runtime-labelled: never statically labelled
    assert all(c[0] == 'heap' for c in rt.pointer_cells('P:observed#0'))


def test_a_caller_passing_an_integer_keeps_the_label_single(tmp_path):
    g, rt, solver, labels, rows = setup(tmp_path)
    r = rows['P:one_caller#0']
    assert r['status'] == 'single' and 'caller_all' not in r['reason']   # one typed anchor, one untyped caller
    assert 'P:one_caller#0' not in rt.static_cells


def test_respelled_alias_couples_the_callback(tmp_path, monkeypatch):
    g = graph(tmp_path)
    rows = [{'installer_file': 'src/flow.c', 'installer': 'install_alias', 'callback_file': 'src/flow.c',
             'callback': 'cb_alias', 'source_spelling': 'data_alias', 'name_used': 'cb_alias_address'}]
    done, matched = T.respell_installs(g, rows)
    assert done == 1 and matched == 1
    assert any(e['src'] == '&FN:cb_alias' and e['dst'] == 'F:Owner.any' for e in g.edges)
    rt = T.StaticRuntime(write_rt(tmp_path, [('cb_alias', 1, 'scalar=3')]), g)
    solver = S.Solver(g, rt)
    assert 'P:cb_alias#0' in {m for _, _, m in solver.adj['F:Owner.any#0']}


def test_admission_rules():
    one = [('rec:Body*', 'P:a#0', 'callee', 0, 0)]
    assert T.admit(None, one)[0] == 'single'
    two_fn = one + [('rec:Body*', 'P:b#0', 'callee', 0, 1)]
    assert T.admit(None, two_fn)[0] == 'admitted'
    same_fn_same_kind = one + [('rec:Body*', 'L:a:x@3', 'callee', 0, 0)]
    assert T.admit(None, same_fn_same_kind)[0] == 'single'
    strong = [('rec:Body*', 'F:Owner.cb#0', 'slot_typed', 0, 0)]
    assert T.admit(None, strong)[0] == 'admitted'
    weak = [('rec:Body*', 'P:a#0', 'cmp', 0, 0), ('rec:Body*', 'P:b#0', 'cmp', 0, 0)]
    assert T.admit(None, weak)[0] == 'weak'
    assert T.admit(None, two_fn + [('rec:Other*', 'P:c#0', 'callee', 0, 0)])[0] == 'mixed'


def test_static_component_is_static_whole(tmp_path):
    g, rt, solver, labels, rows = setup(tmp_path)
    seeds = [s for s in T.static_seeds(g, rt, list(rows.values())) if s['node_key'] == 'P:never_run#0']
    assert seeds
    solver2, comps = S.solve_all(g, rt, seeds, solver)
    verdict = T.static_verdict(S.verdict_of)
    out = [verdict(g, rt, sh, comp, res)[0] for cid, sh, comp, b, res in comps]
    assert out == ['static_whole']


def test_select_batches_skip_baseline_whole_and_members(tmp_path):
    import json as J
    solve = tmp_path / 'solve'
    (solve / 'components').mkdir(parents=True)
    base = tmp_path / 'base'
    base.mkdir()
    (base / 'seeds.tsv').write_text('node\toutcome\nP:a#0\twhole\n')
    (solve / 'seeds.tsv').write_text('component\tnode\nC1\tP:a#0\nC2\tP:b#0\nC3\tP:c#0\nC4\tP:d#0\n')
    rows = ['component\tverdict\tnet']
    comps = {'C1': ('static_whole', -5, {'P:a#0'}, ['src/x/a.c']),
             'C2': ('static_whole', -4, {'P:b#0'}, ['src/x/b.c', 'include/x.h']),
             'C3': ('static_whole', -3, {'F:Rec.m'}, ['src/x/c.c']),
             'C4': ('static_bridge', 2, {'P:d#0'}, ['src/x/d.c'])}
    for cid, (v, net, nodes, files) in comps.items():
        rows.append('%s\t%s\t%d' % (cid, v, net))
        (solve / 'components' / (cid + '.json')).write_text(J.dumps(
            {'comp': {n: {'st': 'retype', 't': 'Body *'} for n in nodes}, 'result': {'files': files}}))
    (solve / 'components.tsv').write_text('\n'.join(rows) + '\n')
    out = tmp_path / 'batches.txt'
    T.main(['select', '--solve', str(solve), '--baseline', str(base), '--out', str(out)])
    assert out.read_text().split() == ['C2']
    T.main(['select', '--solve', str(solve), '--baseline', str(base), '--members', '--out', str(out)])
    assert sorted(out.read_text().split()) == ['C2', 'C3']
