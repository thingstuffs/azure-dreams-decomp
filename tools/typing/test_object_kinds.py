"""Object-kind linking over synthetic per-function facts (no clang): installs, chains, wrappers, refusals."""
import gzip
import json
from pathlib import Path
import tempfile
import unittest

from tools.typing import object_kinds as K


def fn(name, file='src/town/a.c', params=1, **ev):
    rec = dict(file=file, func=name, tu=file, line=1, stores=[], calls=[], sites=[], casts=[], returns=[],
               typed=[], params=[{'name': 'p%d' % i, 'type': 'void *', 'canon': 'void*'} for i in range(params)])
    rec.update(ev)
    return rec


def site(root, off, w=2, s='s', view=''):
    return {'line': 1, 'ref': [root, off], 'w': w, 's': s, 'rw': 'r', 'view': view, 'field': None,
            'spell': 'member_view' if view else 'raw_cast', 'const': None}


def alloc(cid):
    return {'line': 1, 'callee': 'allocate_list_node', 'res': cid, 'args': [None, None], 'consts': [1, None]}


def store(root, off, rhs, text='x'):
    return {'line': 2, 'lhs': [root, off], 'rhs': rhs, 'text': text, 'const': None}


class LinkTests(unittest.TestCase):
    def run_report(self, funcs):
        with tempfile.TemporaryDirectory() as tmp:
            out = Path(tmp) / 'out'
            out.mkdir()
            with gzip.open(out / 'facts.jsonl.gz', 'wt') as fh:
                for f in funcs:
                    fh.write(json.dumps(f) + '\n')
            (out / 'extract.json').write_text(json.dumps({'header_types': ['ObjectNodeHeader']}))
            K.main(['report', '--root', tmp, '--out', str(out)])
            data = json.loads((out / 'kinds.json').read_text())
            return {k['kind']: k for k in data['kinds']}, data['summary']

    def test_creator_store_and_chain_make_one_kind(self):
        c = 'c:1:allocate_list_node'
        creator = fn('make_thing', calls=[alloc(c)],
                     stores=[store(c, 0x10, ['fn:thing_a', 0], 'object->update_callback')],
                     sites=[site(c, 0x20, view='src/town/a.c:S_80001000_0')])
        a = fn('thing_a', stores=[store('p:thing_a:0', -0x10, ['fn:thing_b', 0])],
               sites=[site('p:thing_a:0', 0), site('p:thing_a:0', 2, view='src/town/a.c:S_80002000_0')])
        b = fn('thing_b', sites=[site('p:thing_b:0', 0)])
        kinds, summary = self.run_report([creator, a, b])
        self.assertEqual(summary['chains'], 1)
        (kind,) = kinds.values()
        self.assertEqual(sorted(x['func'] for x in kind['callbacks']), ['thing_a', 'thing_b'])
        self.assertEqual([x['func'] for x in kind['creators']], ['make_thing'])
        self.assertEqual(sorted(v.split(':')[-1] for v in kind['views']), ['S_80001000_0', 'S_80002000_0'])
        self.assertEqual(kind['conflicts'], [])

    def test_wrapper_parameter_carries_the_callback(self):
        c = 'c:2:allocate_list_node'
        wrapper = fn('spawn', params=2, calls=[alloc(c)], returns=[[c, 0]],
                     stores=[store(c, 0x10, ['p:spawn:0', 0], 'object->update_callback')])
        caller = fn('caller', calls=[{'line': 3, 'callee': 'spawn', 'res': 'c:3:spawn',
                                      'args': [['fn:tick', 0], None], 'consts': [None, None]}],
                    sites=[site('c:3:spawn', 0x24, w=4)])
        tick = fn('tick', sites=[site('p:tick:0', 4, w=4)])
        kinds, summary = self.run_report([wrapper, caller, tick])
        self.assertEqual(summary['carriers'], 1)
        kind = kinds['tick']
        self.assertEqual([x['func'] for x in kind['creators']], ['caller'])
        self.assertEqual([r['off'] for r in kind['layout']], [4])

    def test_conflicting_chain_is_refused_and_marks_the_bridge_shared(self):
        a = fn('pointer_user', stores=[store('p:pointer_user:0', -0x10, ['fn:generic', 0])],
               sites=[site('p:pointer_user:0', 4, w=4, s='p'), site('p:pointer_user:0', 8, w=4, s='p')])
        b = fn('int_user', stores=[store('p:int_user:0', -0x10, ['fn:generic', 0])],
               sites=[site('p:int_user:0', 4, w=4, s='s')])
        g = fn('generic', sites=[])
        c1, c2 = 'c:4:allocate_list_node', 'c:5:allocate_list_node'
        mk = fn('mk', calls=[alloc(c1), alloc(c2)],
                stores=[store(c1, 0x10, ['fn:pointer_user', 0]), store(c2, 0x10, ['fn:int_user', 0])])
        kinds, summary = self.run_report([a, b, g, mk])
        self.assertEqual(summary['refused_unions'], {'chain': 1})
        self.assertIn('generic', summary['shared_callbacks'])
        self.assertNotEqual(K.UF, None)
        homes = [k for k in kinds.values() if any(x['func'] == 'int_user' for x in k['callbacks'])]
        self.assertFalse(any(x['func'] == 'pointer_user' for x in homes[0]['callbacks']))


if __name__ == '__main__':
    unittest.main()
