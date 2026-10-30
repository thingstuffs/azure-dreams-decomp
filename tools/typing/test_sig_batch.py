"""Unit tests for batch transactions (sig_batch.py) and the merged writer / visibility repairs (sig_txn.py).

    python3 -m unittest tools/typing/test_sig_batch.py
"""
from pathlib import Path
import shutil
import sys
import tempfile
import types
import unittest

HERE = Path(__file__).resolve().parent
sys.path[:0] = [str(HERE), str(HERE.parent), str(HERE.parent / 'headers'), str(HERE.parent / 'lint')]
import sig_batch as B  # noqa: E402
import sig_census as C  # noqa: E402
import sig_txn as T  # noqa: E402

COMMON = '''#ifndef COMMON_H
#define COMMON_H
typedef unsigned char  u8;
typedef signed char    s8;
typedef unsigned short u16;
typedef short          s16;
typedef unsigned int   u32;
typedef int            s32;
#endif
'''

FILES = {
    'include/common.h': COMMON,
    'include/feat/a.h': '#ifndef FEAT_A_H\n#define FEAT_A_H\n#include "common.h"\ns32 a_keep(void);\n#endif\n',
    'include/feat/b.h': '#ifndef FEAT_B_H\n#define FEAT_B_H\n#include "common.h"\nvoid b_keep(void);\n#endif\n',
    'include/shared/thing.h': '#ifndef SHARED_THING_H\n#define SHARED_THING_H\ntypedef struct Thing { int v; } Thing;\n'
                              '#endif\n',
    'src/feat/a/a_def.c': '#include "common.h"\n\ns32 a_fn(s32 x) {\n    return x + 1;\n}\n',
    'src/feat/b/b_def.c': '#include "common.h"\n#include "shared/thing.h"\n\nvoid b_fn(Thing *t, s32 w) {\n}\n',
    # one consumer of both headers: both transactions edit it
    'src/other/user.c': '#include "common.h"\n\nextern s32 a_fn();\nextern void b_fn(void *, s32);\n\n'
                        'void use(void) {\n    b_fn(0, a_fn(3));\n}\n',
    # a TU that spells its own base typedefs instead of including common.h
    'src/other/bare.c': 'typedef unsigned char u8;\ntypedef signed int s32;\n\nextern s32 a_fn(s32 x);\n\n'
                        's32 bare(void) {\n    return a_fn(1);\n}\n',
}


def decision(name, ret, params, path, owner):
    return dict(name=name, owner=owner, status='unified', choice='D', ret=ret, narrowing=None,
                definition=dict(path=path, proto='%s %s(%s)' % (ret, name, params), ret=ret, params=params))


class Tree:
    def __init__(self, files=FILES):
        self.root = Path(tempfile.mkdtemp(prefix='sigbatch_'))
        for rel, text in files.items():
            p = self.root / rel
            p.parent.mkdir(parents=True, exist_ok=True)
            p.write_text(text)

    def close(self):
        shutil.rmtree(self.root, ignore_errors=True)


class MergedPlanTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.tree = Tree()
        cls.census = C.Census(cls.tree.root)

    @classmethod
    def tearDownClass(cls):
        cls.tree.close()

    def batch(self, **kw):
        datas = [dict(header='include/feat/a.h', decisions=[
                          decision('a_fn', 's32', 's32 x', 'src/feat/a/a_def.c', 'include/feat/a.h')]),
                 dict(header='include/feat/b.h', decisions=[
                          decision('b_fn', 'void', 'Thing *t, s32 w', 'src/feat/b/b_def.c', 'include/feat/b.h')])]
        return B.Batch(self.tree.root, datas, self.census, log=lambda m: None, **kw)

    def test_two_headers_edit_one_consumer(self):
        texts, reports, file_names, held = self.batch().plan({'a_fn', 'b_fn'})
        self.assertEqual(held, {})
        user = texts['src/other/user.c']
        self.assertIn('#include "feat/a.h"', user)
        self.assertIn('#include "feat/b.h"', user)
        self.assertNotIn('extern', user)
        self.assertEqual(sorted(file_names['src/other/user.c']), ['a_fn', 'b_fn'])
        self.assertIn('s32 a_fn(s32 x);', texts['include/feat/a.h'])
        # the owner header names a shared type: it includes that type header itself
        self.assertIn('#include "shared/thing.h"', texts['include/feat/b.h'])
        self.assertIn('void b_fn(Thing *t, s32 w);', texts['include/feat/b.h'])

    def test_common_h_repair_for_a_tu_with_own_typedefs(self):
        texts, reports, _, held = self.batch().plan({'a_fn'})
        bare = texts['src/other/bare.c']
        self.assertTrue(bare.startswith('#include "common.h"\n#include "feat/a.h"\n'), bare)
        self.assertEqual(bare.count('#include "common.h"'), 1)
        self.assertNotIn('typedef', bare)
        self.assertNotIn('extern', bare)
        kinds = {(r['kind'], r['path']) for r in reports['include/feat/a.h']['repairs']}
        self.assertIn(('include_common_h', 'src/other/bare.c'), kinds)

    def test_common_h_takes_the_typedef_slot_after_a_file_comment(self):
        tree = Tree(dict(FILES, **{'src/other/bare.c': '/* Bare unit. */\n\ntypedef unsigned char u8;\n'
                                                       'typedef int s32;\n\nextern s32 a_fn(s32 x);\n\n'
                                                       's32 bare(void) {\n    return a_fn(1);\n}\n'}))
        try:
            census = C.Census(tree.root)
            datas = [dict(header='include/feat/a.h', decisions=[
                decision('a_fn', 's32', 's32 x', 'src/feat/a/a_def.c', 'include/feat/a.h')])]
            b = B.Batch(tree.root, datas, census, log=lambda m: None)
            texts, reports, _, held = b.plan({'a_fn'})
            self.assertTrue(texts['src/other/bare.c'].startswith(
                '/* Bare unit. */\n\n#include "common.h"\n#include "feat/a.h"\n'), texts['src/other/bare.c'])
        finally:
            tree.close()

    def test_without_repair_the_name_holds_or_respells(self):
        texts, reports, _, held = self.batch(repair=False).plan({'a_fn'})
        # the TU keeps its own declaration, respelled to the canonical prototype (already canonical here)
        self.assertNotIn('#include "feat/a.h"', texts.get('src/other/bare.c', FILES['src/other/bare.c']))
        self.assertEqual(reports['include/feat/a.h']['repairs'], [])

    def test_scope_guard_holds_names_editing_other_headers(self):
        b = self.batch(scope=['include/feat/a'])
        texts, reports, file_names, held = b.plan({'a_fn', 'b_fn'})
        self.assertEqual(held, {})          # owners are always in scope
        out = b._out_of_scope({'include/elsewhere.h': '', 'include/feat/b.h': ''},
                              {'include/elsewhere.h': ['a_fn']})
        self.assertEqual(out, {'a_fn': 'out_of_scope_header:include/elsewhere.h'})

    def test_overlapping_spans_hold_the_later_header(self):
        b = self.batch()
        t1 = types.SimpleNamespace(header='include/feat/a.h')
        t2 = types.SimpleNamespace(header='include/feat/b.h')
        ep1 = dict(edits={'src/other/user.c': [(20, 40, '')]}, file_names={'src/other/user.c': ['a_fn']})
        ep2 = dict(edits={'src/other/user.c': [(30, 50, 'x')]}, file_names={'src/other/user.c': ['b_fn']})
        self.assertEqual(b._overlaps([(t1, ep1), (t2, ep2)]), {'b_fn': 'batch_overlap:src/other/user.c'})


class RenderTests(unittest.TestCase):
    def test_identical_spans_apply_once_and_includes_merge(self):
        text = '#include "common.h"\n\nextern s32 f();\nextern s32 g();\n\ns32 h(void) { return f() + g(); }\n'
        a = text.index('extern s32 f')
        b = text.index('extern s32 g')
        t1 = types.SimpleNamespace(header='include/x.h')
        t2 = types.SimpleNamespace(header='include/y.h')
        rep = dict(names={'f': {}})
        ep1 = dict(edits={'s.c': [(a, a + 15, '')]}, need_include={'s.c': {'f'}}, extra_includes={},
                   drop_includes={}, def_rewrites=[], h_lines=[], report=rep, file_names={'s.c': {'f'}})
        ep2 = dict(edits={'s.c': [(b, b + 15, ''), (a, a + 15, '')]}, need_include={'s.c': {'g'}},
                   extra_includes={}, drop_includes={}, def_rewrites=[], h_lines=['s32 g(void);'], report=rep,
                   file_names={'s.c': {'g'}})
        texts, names = T.render([(t1, ep1), (t2, ep2)], lambda p: text if p == 's.c' else
                                '#ifndef Y\n#define Y\n#endif\n')
        self.assertIn('#include "x.h"\n#include "y.h"\n', texts['s.c'])
        self.assertNotIn('extern', texts['s.c'])
        self.assertIn('s32 g(void);', texts['include/y.h'])
        self.assertEqual(names['s.c'], ['f', 'g'])

    def test_base_spelling(self):
        self.assertEqual(T.base_spelling(['signed', 'int']), 'int')
        self.assertEqual(T.base_spelling(['short', 'int']), 'short')
        self.assertEqual(T.base_spelling(['signed', 'char']), 'signed char')
        self.assertEqual(T.base_spelling(['char']), 'char')
        self.assertEqual(T.base_spelling(['unsigned']), 'unsigned int')

    def test_failing_source_of_a_slus_recipe(self):
        rec = dict(source='tools/cc.sh src/w_800492B0.c build/src/w_800492B0.o 2.7.2-cdk "" ""')
        self.assertEqual(T.failing_source(rec), 'src/w_800492B0.c')
        self.assertEqual(T.failing_source(dict(source='src/a.c', owner='src/b.c')), 'src/b.c')
        err = "src/w.c:23: too many arguments to function `consume_pending_event_flag'"
        self.assertEqual(T.ARITY.findall(err), ['consume_pending_event_flag'])


class CulpritTests(unittest.TestCase):
    def setUp(self):
        self.root = Path(tempfile.mkdtemp(prefix='sigbatch_culprit_'))
        (self.root / 'src').mkdir()
        (self.root / 'src/u.c').write_text('void use(void) {\n    x = a_fn(b_fn(1));\n}\n')

    def tearDown(self):
        shutil.rmtree(self.root, ignore_errors=True)

    def test_compiler_named_names_and_error_lines(self):
        proof = dict(recipes={
            'r1': dict(verdict='ERROR', source='src/u.c', error="src/u.c:9: too many arguments to function `c_fn'"),
            'r2': dict(verdict='ERROR', source='src/u.c', error='src/u.c:2: void value not ignored as it ought to be'),
            'r3': dict(verdict='PASS', source='src/v.c')})
        certain, drop, stop, refuse = B.batch_culprits(proof, {}, self.root, {'a_fn', 'b_fn', 'c_fn', 'd_fn'}, {}, {})
        self.assertEqual(certain, {'c_fn'})
        self.assertEqual(drop, {'a_fn', 'b_fn'})

    def test_conflict_in_a_new_owner_type_include_is_refused_at_the_owner(self):
        reports = {'include/x.h': dict(header_includes=['include/shared/node.h'], includes_added=[])}
        proof = dict(recipes={'r': dict(verdict='ERROR', source='src/t.c',
                                        error="build_ovl/include/shared/node.h:34: previous declaration of `anchor'")})
        certain, drop, stop, refuse = B.batch_culprits(proof, {}, self.root, {'a_fn'}, reports, {})
        self.assertEqual(refuse, [('include/x.h', 'include/shared/node.h')])
        self.assertEqual((certain, drop, stop), (set(), set(), []))

    def test_unexplained_failure_falls_back_to_file_names(self):
        proof = dict(recipes={'r': dict(verdict='CHANGED', source='src/t.c', difference={'kind': 'bytes'})})
        certain, drop, stop, refuse = B.batch_culprits(proof, {'src/t.c': ['a_fn', 'z_fn']}, self.root,
                                                       {'a_fn', 'b_fn'}, {}, {})
        self.assertEqual(drop, {'a_fn'})


# ---------------------------------------------------------------- bisection with a fake batch and prover

class FakeBatch:
    """Each name edits its own file plus a shared consumer; the plan is a pure function of the name set."""

    def __init__(self, root, names, headers):
        self.root = root
        self.cands = {n: headers[n] for n in names}
        self.txns = {}
        self.originals = {}

    def state(self):
        return ()

    def text(self, rel):
        self.originals.setdefault(rel, None)
        return None

    def plan(self, names):
        texts = {'src/%s.c' % n: '/* %s */\n' % n for n in names}
        texts['src/shared.c'] = ''.join(sorted('/* %s */\n' % n for n in names))
        fn = {p: [p[4:-2]] for p in texts if p != 'src/shared.c'}
        fn['src/shared.c'] = sorted(names)
        return texts, {}, fn, {}


def fake_prover(bad, attribute=True):
    calls = []

    def prove(files, texts):
        names = {f[4:-2] for f in files if f != 'src/shared.c'}
        calls.append(names)
        guilty = names & bad
        if not guilty:
            return dict(verdict='PASS', recipes={})
        # the failing recipe compiles the shared consumer: attribution names every name editing it
        rec = dict(verdict='ERROR', source='src/shared.c' if not attribute else 'src/%s.c' % sorted(guilty)[0],
                   error='boom')
        return dict(verdict='ERROR', recipes={'r1': rec})
    return prove, calls


class SettleTests(unittest.TestCase):
    def setUp(self):
        self.root = Path(tempfile.mkdtemp(prefix='sigbatch_settle_'))
        (self.root / 'src').mkdir()

    def tearDown(self):
        shutil.rmtree(self.root, ignore_errors=True)

    def run_batch(self, names, bad, attribute=True, headers=None):
        headers = headers or {n: 'include/h%d.h' % (i % 3) for i, n in enumerate(sorted(names))}
        batch = FakeBatch(self.root, names, headers)
        prove, calls = fake_prover(bad, attribute)
        r = B.Runner(self.root, batch, self.root, prover=prove, log=lambda m: None, refresh=False)
        final, entry, nat = r.run()
        return r, final, entry, calls

    def test_clean_batch_is_one_proof(self):
        names = {'n%02d' % i for i in range(20)}
        r, final, entry, calls = self.run_batch(names, set())
        self.assertEqual(final, names)
        self.assertEqual(len(calls), 1)

    def test_attributed_culprit_backs_off_alone(self):
        names = {'n%02d' % i for i in range(20)}
        r, final, entry, calls = self.run_batch(names, {'n07'})
        self.assertEqual(final, names - {'n07'})
        self.assertEqual(len(calls), 2)
        self.assertEqual([b['name'] for b in r.backoffs], ['n07'])
        # the accepted state is one whole-set proof of exactly the survivors, and it is on disk
        self.assertEqual(calls[-1], final)
        self.assertEqual(entry[3]['verdict'], 'PASS')
        self.assertTrue((self.root / 'src/n00.c').is_file())
        self.assertFalse((self.root / 'src/n07.c').exists())

    def test_unattributed_failures_are_bisected(self):
        names = {'n%02d' % i for i in range(32)}
        r, final, entry, calls = self.run_batch(names, {'n03', 'n20'}, attribute=False)
        self.assertEqual(final, names - {'n03', 'n20'})
        self.assertEqual(sorted(b['name'] for b in r.backoffs), ['n03', 'n20'])
        self.assertLess(len(calls), 25)            # bisection, not one proof per name
        self.assertEqual(calls[-1], final)

    def test_greedy_flow_would_lose_innocent_names(self):
        # every name edits src/shared.c: the old back-off drops all 12; settle keeps 11
        names = {'n%02d' % i for i in range(12)}
        r, final, entry, calls = self.run_batch(names, {'n05'}, attribute=False)
        self.assertEqual(final, names - {'n05'})

    def test_budget_keeps_the_best_proven_set(self):
        names = {'n%02d' % i for i in range(16)}
        headers = {n: 'include/h.h' for n in names}
        batch = FakeBatch(self.root, names, headers)
        prove, calls = fake_prover({'n01', 'n09'}, attribute=False)
        r = B.Runner(self.root, batch, self.root, prover=prove, log=lambda m: None, refresh=False, max_proofs=3)
        final, entry, nat = r.run()
        self.assertTrue(final <= names - {'n01', 'n09'})
        self.assertEqual(len(calls), 3)
        if final:
            self.assertEqual(entry[3]['verdict'], 'PASS')
        self.assertTrue(any(b['why'] == 'proof_budget' for b in r.backoffs))

    def test_split_by_header_first(self):
        cands = {'a1': 'A', 'a2': 'A', 'a3': 'A', 'b1': 'B', 'c1': 'C'}
        x, y = B.split(set(cands), cands)
        self.assertEqual(x, {'a1', 'a2', 'a3'})
        self.assertEqual(y, {'b1', 'c1'})
        x, y = B.split({'a1', 'a2', 'a3'}, cands)
        self.assertEqual((len(x), len(y)), (1, 2))


if __name__ == '__main__':
    unittest.main()
