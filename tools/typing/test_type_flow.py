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


def test_nested_anonymous_members(tmp_path):
    (tmp_path / 'include').mkdir()
    (tmp_path / 'include' / 'flow.h').write_text('''
typedef union Fixed {
    int value;
    struct { unsigned short fraction; short integer; } parts;
} Fixed;
typedef struct Body {
    Fixed position;
    union { unsigned short u; short s; } timer;
} Body;
''')
    (tmp_path / 'src').mkdir()
    (tmp_path / 'src' / 'flow.c').write_text('#include "flow.h"\nvoid use(Body *b) { b->timer.u = 1; }\n')
    unit, err = A.clang_unit(tmp_path, 'src/flow.c')
    assert unit is not None, err
    graph = S.Graph(write_graph(tmp_path, F.Extract(unit).run().dump()))
    assert graph.size('Fixed') == 4
    assert graph.member_at('Body', 2, 'short') == 'position.parts.integer'
    assert graph.member_at('Body', 4, 'unsigned short') == 'timer.u'
    assert graph.member_at('Body', 4, 'short') == 'timer.s'


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


def test_whole_array_member_and_elements(tmp_path):
    (tmp_path / 'include').mkdir()
    (tmp_path / 'include' / 'flow.h').write_text("""
typedef union Scratch {
    int value;
    unsigned char bytes[4];
} Scratch;
typedef struct Body { Scratch scratch; short path[8]; } Body;
""")
    (tmp_path / 'src').mkdir()
    (tmp_path / 'src' / 'flow.c').write_text(
        '#include "flow.h"\nvoid use(Body *b) { b->scratch.bytes[2] = 1; }\n')
    unit, err = A.clang_unit(tmp_path, 'src/flow.c')
    assert unit is not None, err
    graph = S.Graph(write_graph(tmp_path, F.Extract(unit).run().dump()))
    assert graph.member_at('Body', 0, 'unsigned char[4]') == 'scratch.bytes'
    assert graph.member_at('Body', 2, 'unsigned char') == 'scratch.bytes[2]'
    assert graph.member_at('Body', 4, 'short[8]') == 'path'
    assert graph.member_at('Body', 6, 'short') == 'path[1]'
    leaves = [(p, t) for p, t, _ in unit.leaves_at('Body', 0)]
    assert ('scratch.bytes', 'unsigned char[4]') in leaves
    assert ('scratch.bytes[0]', 'unsigned char') in leaves


def test_colliding_record_names_do_not_vote(tmp_path):
    data = extract(tmp_path)
    gdir = write_graph(tmp_path, data)
    other = dict(data)
    other['records'] = dict(data['records'])
    other['records']['Body'] = dict(data['records']['Body'], file='src/other.c', size=16)
    with gzip.open(gdir / 'tu' / 'other.json.gz', 'wt') as fh:
        json.dump(other, fh)
    graph = S.Graph(gdir)
    assert 'Body' in graph.ambiguous_records
    assert graph.cls('Body *') == 'private'
    runtime = S.Runtime(write_rt(tmp_path, [('handler', 0, 'rk1+0x20=10')]), graph)
    assert runtime.winner(('heap', 'rk1', 0x20)) == (None, 0.0)
    seed = {'target': 'Body *'}
    assert S.seed_target(graph, runtime, seed, 'P:callee#0') == ''


def test_unlabelled_cell_does_not_hide_contradicted_cast(tmp_path):
    data = extract(tmp_path)
    graph = S.Graph(write_graph(tmp_path, data))
    runtime = S.Runtime(write_rt(tmp_path, [('handler', 0, 'rk1+0x20=10')]), graph)
    known = ('heap', 'rk1', 0x20)
    unknown = ('heap', 'unobserved', 0x20)
    assert runtime.cast_ok([unknown, known], 0, 'Owner *') == 'wrong'
    assert runtime.cast_ok([known, unknown], 0, 'Owner *') == 'wrong'
    assert runtime.cast_ok([unknown, known], 0, 'Body *') == 'unproven'
    assert runtime.cast_ok([unknown], 0, 'Body *') == 'unproven'


def test_local_in_duplicate_function_is_ambiguous(tmp_path):
    graph = S.Graph(write_graph(tmp_path, extract(tmp_path)))
    graph.functions['caller'].append(dict(graph.functions['caller'][0], file='src/other.c'))
    runtime = S.Runtime(write_rt(tmp_path, [('handler', 0, 'rk1+0x20=10')]), graph)
    solver = S.Solver(graph, runtime)
    node = 'L:caller:holder@8'
    comp = {node: dict(t='Body *', st='retype', seed='P:caller#0', **{'from': 's32'})}
    result = solver.evaluate(comp, [])
    assert 'ambiguous_definition' in result['node_reasons'][node]


def test_ambiguous_function_does_not_supply_runtime_votes(tmp_path):
    graph = S.Graph(write_graph(tmp_path, extract(tmp_path)))
    graph.functions['handler'].append(dict(graph.functions['handler'][0], file='src/other.c'))
    kinds = [dict(id='rk1', role='pool', receivers=[dict(function='handler', arg=0, offset=32)])]
    runtime = S.Runtime(write_rt(tmp_path, [('handler', 0, 'rk1+0x20=10')], kinds), graph)
    assert not runtime.pointer_cells('P:handler#0')
    assert runtime.winner(('heap', 'rk1', 32)) == (None, 0.0)


def test_named_runtime_target_precedes_generated_seed_view(tmp_path):
    graph = S.Graph(write_graph(tmp_path, extract(tmp_path)))
    graph.typedefs['Rec_func_80000000_arg0'] = 'Body'
    runtime = S.Runtime(write_rt(tmp_path, [('handler', 0, 'rk1+0x20=10'),
                                          ('callee', 0, 'rk1+0x20=10')]), graph)
    seed = dict(target='Rec_func_80000000_arg0 *')
    assert graph.cls(seed['target']) == 'gen'
    assert S.seed_target(graph, runtime, seed, 'P:callee#0') == 'Body *'


# --------------------------------------------------------------------------- H8/H9 runtime tables

SLOT_SOURCE = r'''
#include "flow.h"
void handler(Body *b, s32 n) { b->hp = n; }
void handler2(void *b, s32 n) { ((Body *)b)->speed = n; }
void install(Owner *o) {
    o->cb = &handler;
}
void dispatch(Owner *o, Body *b) {
    o->cb(b, 1);
}
static s32 cell;
void take(void *p) { cell = (s32)p; }
void use_addr(void) { take(&cell); }
void generic(void *p) { cell = 1; }
void caller_a(Body *b) { void *v = b; generic(v); }
void caller_b(Owner *o) { void *w = o; generic(w); }
void *g_body;
void chase(Body *b) { void *t = b->target; g_body = t; }
'''


def slot_graph(tmp_path):
    (tmp_path / 'include').mkdir()
    (tmp_path / 'include' / 'flow.h').write_text(HEADER)
    (tmp_path / 'src').mkdir()
    (tmp_path / 'src' / 'flow.c').write_text(SLOT_SOURCE)
    unit, err = A.clang_unit(tmp_path, 'src/flow.c')
    assert unit is not None, err
    return S.Graph(write_graph(tmp_path, F.Extract(unit).run().dump()))


def write_ext(rt, pointees=(), sites=()):
    with gzip.open(rt / 'pointees.tsv.gz', 'wt') as fh:
        fh.write('file\tline\tfunction\taccess\tclass\ttarget\toffset\tvalue_class\tvalue_target\tvalue_offset\tcount\n')
        for row in pointees:
            fh.write('\t'.join(map(str, row)) + '\n')
    with gzip.open(rt / 'callsite_args.tsv.gz', 'wt') as fh:
        fh.write('callee_file\tcallee\targ\tcaller_file\tcaller\tline\tcells\tcalls\n')
        for row in sites:
            fh.write('\t'.join(map(str, row)) + '\n')


def test_function_address_install_couples_slot(tmp_path):
    g = slot_graph(tmp_path)
    edges = {(e['k'], e['dst'], e['src']) for e in g.edges}
    assert ('assign', 'F:Owner.cb', '&FN:handler') in edges      # `&fn` is recorded as an address-of
    assert ('arg', 'P:take#0', '&G:cell') in edges                # an object address stays an object address
    rt = S.Runtime(write_rt(tmp_path, [('handler', 0, 'rk1+0x20=10')]), g)
    solver = S.Solver(g, rt)
    assert ('P:handler#0') in {m for _, _, m in solver.adj['F:Owner.cb#0']}
    assert 'R:handler' in {m for _, _, m in solver.adj['F:Owner.cb#ret']}
    assert not any(m.startswith('P:') for _, _, m in solver.adj['&G:cell#0'])
    assert S.is_fn('&FN:handler') and S.fn_of('&FN:handler') == 'handler' and not S.is_fn('&G:cell')


def test_runtime_installed_callback_couples_call_through_slot(tmp_path):
    g = slot_graph(tmp_path)
    rt_dir = write_rt(tmp_path, [('handler', 0, 'rk1+0x20=10'), ('handler2', 0, 'rk1+0x20=4')])
    write_ext(rt_dir, pointees=[('src/flow.c', 9, 'dispatch', 'load', 'heap', 'rk2', '0x28', 'func',
                                 'src/flow.c:handler2', '', 4)])
    rt = S.Runtime(rt_dir, g)
    solver = S.Solver(g, rt)
    assert solver.slots['F:Owner.cb'] == {'handler2': 4}
    assert 'P:handler2#0' in {m for _, _, m in solver.adj['F:Owner.cb#0']}
    seeds, notes = S.rt_seeds(g, rt, solver)
    slot = [s for s in seeds if s['src'] == 'rt_slot']
    assert slot and slot[0]['node_key'] == 'P:handler2#0' and slot[0]['target'] == 'Body *'


def test_callsite_cells_label_holders_and_split_generic_params(tmp_path):
    g = slot_graph(tmp_path)
    rt_dir = write_rt(tmp_path, [('handler', 0, 'rk1+0x20=10'), ('dispatch', 0, 'rk2+0x20=3'),
                                 ('generic', 0, 'rk1+0x20=5, rk2+0x20=5')])
    write_ext(rt_dir, sites=[('src/flow.c', 'generic', 0, 'src/flow.c', 'caller_a', 15, 'rk1+0x20=5', 5),
                             ('src/flow.c', 'generic', 0, 'src/flow.c', 'caller_b', 16, 'rk2+0x20=5', 5)])
    rt = S.Runtime(rt_dir, g)
    assert S.parse_site_label('D_80132000+0x440') == ('ram', 'D_80132000', 0x440)
    assert S.parse_site_label('src/a.c:fn') == ('func', 'fn', 0)
    va = [n for n in rt.derived if n.startswith('L:caller_a:v@')]
    assert va and rt.pointer_cells(va[0]) == {('heap', 'rk1', 0x20): 5}
    solver = S.Solver(g, rt)
    seeds, _ = S.rt_seeds(g, rt, solver)
    split = {s['node_key']: s['target'] for s in seeds if s['src'] == 'rt_split'}
    assert split.get(va[0]) == 'Body *'
    wb = [n for n in split if n.startswith('L:caller_b:w@')]
    assert wb and split[wb[0]] == 'Owner *'


def test_integer_parameter_with_pointer_at_every_site_is_seeded(tmp_path):
    d = extract(tmp_path)
    g = S.Graph(write_graph(tmp_path, d))
    rt_dir = write_rt(tmp_path, [('caller', 0, 'rk1+0x20=10'), ('callee', 0, 'rk1+0x20=10'),
                                 ('handler', 0, 'rk1+0x20=10')])
    write_ext(rt_dir, sites=[('src/flow.c', 'callee', 0, 'src/flow.c', 'caller', 9, 'rk1+0x20=10', 10)])
    rt = S.Runtime(rt_dir, g)
    seeds, _ = S.rt_seeds(g, rt, S.Solver(g, rt))
    assert [(s['node_key'], s['target']) for s in seeds if s['src'] == 'rt_intptr'] == [('P:callee#0', 'Body *')]
    # a scalar at any call site keeps the integer
    write_ext(rt_dir, sites=[('src/flow.c', 'callee', 0, 'src/flow.c', 'caller', 9, 'rk1+0x20=9, scalar=1', 10)])
    rt = S.Runtime(rt_dir, g)
    seeds, notes = S.rt_seeds(g, rt, S.Solver(g, rt))
    assert not [s for s in seeds if s['src'] == 'rt_intptr']


def test_extension_can_be_switched_off(tmp_path, monkeypatch):
    g = slot_graph(tmp_path)
    rt_dir = write_rt(tmp_path, [('handler', 0, 'rk1+0x20=10')])
    write_ext(rt_dir, sites=[('src/flow.c', 'generic', 0, 'src/flow.c', 'caller_a', 15, 'rk1+0x20=5', 5)])
    monkeypatch.setenv('TYPE_FLOW_RT_EXT', '0')
    rt = S.Runtime(rt_dir, g)
    assert not rt.ext and not rt.derived


def test_pointer_values_label_member_and_global_holders(tmp_path):
    g = slot_graph(tmp_path)
    rt_dir = write_rt(tmp_path, [('handler', 0, 'rk1+0x20=10')])
    write_ext(rt_dir, pointees=[
        ('src/flow.c', 18, 'chase', 'load', 'heap', 'rk1', '0x28', 'heap', 'rk1', '0x20', 5),
        ('src/flow.c', 18, 'chase', 'store', 'ram', 'g_body+0x0', '', 'heap', 'rk1', '0x20', 5),
        ('src/flow.c', 18, 'chase', 'load', 'ram', 'g_body+0x4', '', 'heap', 'rk9', '0x20', 1)])
    rt = S.Runtime(rt_dir, g)
    assert rt.pointer_cells('F:Body.target') == {('heap', 'rk1', 0x20): 5}
    assert rt.pointer_cells('G:g_body') == {('heap', 'rk1', 0x20): 5}       # only the global's own word
    # the member's declared Body * votes for the cell its values carry
    assert 'F:Body.target' in rt.votes[('heap', 'rk1', 0x20)]['rec:Body*']


def test_global_root_votes_for_unvoted_ram_cells(tmp_path):
    g = slot_graph(tmp_path)
    g.decl['G:body_table']['Body[4]'] += 1
    g.decl['G:owner_one']['Owner'] += 1
    rt_dir = write_rt(tmp_path, [('generic', 0, 'ram:body_table+0x18=3, ram:owner_one+0x0=2, ram:body_table+0x4=1')])
    write_ext(rt_dir)
    rt = S.Runtime(rt_dir, g)
    assert rt.winner(('ram', 'body_table', 0x18))[0] == 'rec:Body*'      # element 2 of Body[4]
    assert rt.winner(('ram', 'owner_one', 0))[0] == 'rec:Owner*'
    assert rt.winner(('ram', 'body_table', 0x4)) == (None, 0.0)          # inside an element
    assert rt.global_root_type('body_table', 0x30) is None               # past the end


def test_slot_plan_proposes_one_prototype_per_family(tmp_path):
    g = slot_graph(tmp_path)
    rt_dir = write_rt(tmp_path, [('handler', 0, 'rk1+0x20=10'), ('handler2', 0, 'rk1+0x20=4')])
    write_ext(rt_dir, pointees=[('src/flow.c', 9, 'dispatch', 'load', 'heap', 'rk2', '0x28', 'func',
                                 'src/flow.c:handler2', '', 4),
                                ('src/flow.c', 9, 'dispatch', 'load', 'heap', 'rk2', '0x28', 'func',
                                 'src/flow.c:handler', '', 6)])
    rt = S.Runtime(rt_dir, g)
    solver = S.Solver(g, rt)
    plan = S.slot_plan(g, rt, solver)
    assert len(plan) == 1 and plan[0]['holder'] == 'F:Owner.cb'
    assert plan[0]['proposed'].startswith('void (*)(Body *, ') and plan[0]['basis'].startswith('runtime')
    assert plan[0]['retype'] == 'handler2#0' and plan[0]['contradicting_callbacks'] == 0


def test_scope_keeps_other_lanes_nodes_as_boundaries(tmp_path):
    d = extract(tmp_path)
    g = S.Graph(write_graph(tmp_path, d))
    rt = S.Runtime(write_rt(tmp_path, [('caller', 0, 'rk1+0x20=10'), ('callee', 0, 'rk1+0x20=10'),
                                       ('handler', 0, 'rk1+0x20=10')]), g)
    solver = S.Solver(g, rt)
    solver.scope = ('src/other/',)
    comp, boundary, _ = solver.expand('P:callee#0', 'Body *')
    assert 'L:caller:holder@8' not in comp and any(r == 'scope' for _, _, r in boundary)
    solver.scope = ('src/',)
    comp, boundary, _ = solver.expand('P:callee#0', 'Body *')
    assert comp['L:caller:holder@8']['st'] == 'retype'


def test_slot_seeds_follow_the_plan_and_the_scope(tmp_path):
    import type_flow_slot_seeds as SS
    g = slot_graph(tmp_path)
    plan = [{'holder': 'F:Owner.cb', 'proposed': 'void (*)(Body *, s32)', 'basis': 'runtime,declared',
             'retype': 'handler2#0 handler2#1'}]
    rows = SS.seeds(g, plan, ['src/'])
    assert [(r['function'], r['arg'], r['target']) for r in rows] == [('handler2', 0, 'Body *')]
    assert SS.seeds(g, plan, ['src/other/']) == []


def test_unvoted_cells_inherit_the_type_they_arrive_with(tmp_path):
    g = slot_graph(tmp_path)
    rt_dir = write_rt(tmp_path, [('handler', 0, 'rk1+0x20=10'),
                                 ('generic', 0, 'rk1+0x20=6, ram:actor_array+0x40=2'),
                                 ('take', 0, 'rk1+0x20=1, rk7+0x20=9')])
    write_ext(rt_dir)
    rt = S.Runtime(rt_dir, g)
    assert rt.winner(('ram', 'actor_array', 0x40))[0] == 'rec:Body*'       # arrives with Body cells
    assert rt.winner(('heap', 'rk7', 0x20)) == (None, 0.0)                  # the voted cell is the minority there


def test_slot_parameters_carry_their_callbacks_cells(tmp_path):
    g = slot_graph(tmp_path)
    rt_dir = write_rt(tmp_path, [('handler', 0, 'rk1+0x20=10'), ('handler2', 0, 'rk2+0x20=10')])
    write_ext(rt_dir, pointees=[('src/flow.c', 9, 'dispatch', 'load', 'heap', 'rk3', '0x28', 'func',
                                 'src/flow.c:handler2', '', 4)])
    rt = S.Runtime(rt_dir, g)
    solver = S.Solver(g, rt)
    # handler (static install) and handler2 (runtime) both feed F:Owner.cb#0: two kinds -> polymorphic slot
    assert set(rt.pointer_cells('F:Owner.cb#0')) == {('heap', 'rk1', 0x20), ('heap', 'rk2', 0x20)}


def test_member_retype_text_respells_members_and_slot_parameters():
    import type_flow_apply as TA
    text = ('typedef struct Owner {\n    /* 0x00 */ void *body; /* the body */\n    s32 handle;\n'
            '    void (*cb)(void *b, s32 n);\n    s16 pair[2];\n    u8 a, b;\n} Owner;\n'
            'typedef struct {\n    s32 value;\n} Anonymous;\n')
    out = TA.member_retype_text(text, 'Owner', 'body', 'Body *')
    assert '/* 0x00 */ Body *body; /* the body */' in out
    out = TA.member_retype_text(text, 'Owner', 'handle', 'Body *')
    assert '    Body *handle;\n' in out
    out = TA.member_retype_text(text, 'Owner', 'cb', 'Body *', slot=0)
    assert 'void (*cb)(Body *b, s32 n);' in out
    assert TA.member_retype_text(text, 'Owner', 'pair', 'Body *') is None       # array
    assert TA.member_retype_text(text, 'Owner', 'b', 'Body *') is None          # two declarators
    assert '    Body *value;' in TA.member_retype_text(text, 'Anonymous', 'value', 'Body *')


def test_functions_with_match_notes_are_not_folded():
    import type_flow_apply as TA
    text = ('void keep(Body *b) {\n    /* MATCH: retain these views for production byte identity. */\n'
            '    x = *(u16 *)((u8 *)b + 2);\n}\nvoid fold(Body *b) {\n    x = *(u16 *)((u8 *)b + 2);\n}\n')
    assert TA.match_note(text, 'keep') and not TA.match_note(text, 'fold') and not TA.match_note(text, 'absent')
