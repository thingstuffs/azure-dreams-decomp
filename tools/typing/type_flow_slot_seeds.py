#!/usr/bin/env python3
"""Seeds for one lane's share of the runtime slot families (type_flow_solve slot_plan.tsv).

    type_flow_slot_seeds.py --graph G --plan SOLVE_DIR/slot_plan.tsv --scope src/dungeon/effect ... --out seeds.tsv

For every slot family whose prototype position was runtime-voted, each installed callback declared under one of the
scope prefixes whose parameter is still a placeholder becomes a seed (file, function, arg, target = the proposed
parameter type).  Solve them with `type_flow.py dryrun --seed-tsv seeds.tsv --scope <same prefixes>` so callbacks
owned by other lanes stay boundaries, then apply with type_flow_apply.py (--allow-zero: a settled prototype that
removes no cast is still the family's one prototype).
"""
import argparse
import csv
from pathlib import Path
import re
import sys

HERE = Path(__file__).resolve().parent
sys.path[:0] = [str(HERE)]
import type_flow as F  # noqa: E402
import type_flow_solve as S  # noqa: E402


def seeds(g, plan_rows, scope):
    out = []
    for p in plan_rows:
        m = re.match(r'^(.*?)\(\*\)\((.*)\)$', p['proposed'])
        params = F.fn_param_types('x(' + m.group(2) + ')') if m else None
        basis = p['basis'].split(',')
        for item in p['retype'].split():
            fn, _, j = item.partition('#')
            j = int(j)
            if not params or j >= len(params) or j >= len(basis) or basis[j] != 'runtime':
                continue
            ds = g.functions.get(fn) or []
            if len(ds) != 1 or not ds[0]['file'].startswith(tuple(scope)):
                continue
            out.append(dict(src='rt_slot_plan', file=ds[0]['file'], function=fn, arg=j, target=params[j], hold='slot',
                            reason='slot %s proposed %s' % (p['holder'], p['proposed'])))
    return out


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('--graph', required=True)
    ap.add_argument('--plan', type=Path, required=True)
    ap.add_argument('--scope', nargs='+', required=True)
    ap.add_argument('--out', type=Path, required=True)
    a = ap.parse_args()
    g = S.Graph(a.graph)
    rows = seeds(g, list(csv.DictReader(open(a.plan), delimiter='\t')), a.scope)
    S.write_tsv(a.out, rows, ['src', 'file', 'function', 'arg', 'target', 'hold', 'reason'])
    print('%d seeds -> %s' % (len(rows), a.out))


if __name__ == '__main__':
    main()
