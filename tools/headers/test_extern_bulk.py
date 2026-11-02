"""Unit coverage for extern_bulk.py (screen selection, blame) and extern_classes.py (site classes)."""
import sys
import tempfile
import unittest
from collections import defaultdict
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import extern_bulk as B      # noqa: E402
import extern_classes as X   # noqa: E402


class FakeGraph:
    def __init__(self, recipes):
        self.recipes = recipes

    def real(self, f):
        return '/abs/' + f

    def dependency_names(self, spec):
        return set(spec.get('dependencies', ())) | {spec['src']}

    def own_source(self, spec):
        return self.real(spec['src'])

    def own_recipes(self, f):
        return {rid for rid, s in self.recipes.items() if s['src'] == f}


class FakePlanTu:
    def __init__(self, append):
        self.append = append


class FakeBulk(B.Bulk):
    def __init__(self, root, jobs, appends):
        self.root = Path(root)
        self.log = lambda m: None
        self.jobs = jobs
        self.holds, self.held, self.restored = [], set(), {}
        self._base = {}
        self.plan = type('P', (), {'tus': {rel: FakePlanTu(a) for rel, a in appends.items()}})()


class ScreenTests(unittest.TestCase):
    def test_one_per_source_family_and_all_own(self):
        g = FakeGraph({
            'own': dict(src='src/a.c', _family='row'),
            'own_copy1': dict(src='src/a.c', _family='placement', projection={'owner': 'src/a.c'}),
            'own_copy2': dict(src='src/a.c', _family='placement', projection={'owner': 'src/a.c'}),
            'c1': dict(src='src/b.c', _family='placement', projection={'owner': 'src/b.c'}),
            'c2': dict(src='src/b.c', _family='placement', projection={'owner': 'src/b.c'}),
            'm1': dict(src='src/b.c', _family='module'),
        })
        p = B.Prover.__new__(B.Prover)
        got = p.screen(list(g.recipes), g, ['src/a.c', 'include/x.h'])
        self.assertIn('own', got)
        self.assertEqual(len([r for r in got if r.startswith('own_copy')]), 1)
        self.assertEqual(len([r for r in got if r in ('c1', 'c2')]), 1)
        self.assertIn('m1', got)


class BlameTests(unittest.TestCase):
    def setUp(self):
        self.td = tempfile.TemporaryDirectory()
        self.addCleanup(self.td.cleanup)
        root = Path(self.td.name)
        (root / 'src').mkdir()
        (root / 'src/user.c').write_text('void f(void) { appended_a(); }\n')
        self.root = root
        self.graph = FakeGraph({
            'edited_tu': dict(src='src/t1.c', dependencies=['include/h.h']),
            'consumer': dict(src='src/user.c', dependencies=['include/h.h']),
        })
        self.prover = type('Pr', (), {'graph': self.graph})()

    def bulk(self):
        jobs = {'src/t1.c': ('old', {'add': ['include/h.h'], 'remove': []}),
                'src/t2.c': ('old', {'add': ['include/h.h'], 'remove': []})}
        return FakeBulk(self.root, jobs, {'src/t1.c': {'include/h.h': ['appended_a']},
                                          'src/t2.c': {'include/h.h': ['appended_b']}})

    def test_edited_tu_failure_restores_that_tu(self):
        b = self.bulk()
        rep = dict(recipes={'edited_tu': dict(verdict='CHANGED', source='src/t1.c')}, images={})
        n = B.blame(b, self.prover, rep, {'src/t1.c': 'x', 'src/t2.c': 'y', 'include/h.h': 'z'})
        self.assertEqual(n, 1)
        self.assertIn('src/t1.c', b.restored)
        self.assertNotIn('src/t2.c', b.restored)

    def test_header_only_failure_holds_mentioned_names(self):
        b = self.bulk()
        rep = dict(recipes={'consumer': dict(verdict='ERROR', source='src/user.c', error='')}, images={})
        B.blame(b, self.prover, rep, {'src/t1.c': 'x', 'src/t2.c': 'y', 'include/h.h': 'z'})
        self.assertIn(('src/t1.c', 'include/h.h'), b.held)       # needs appended_a, which user.c mentions
        self.assertNotIn(('src/t2.c', 'include/h.h'), b.held)
        self.assertEqual(b.accepted(), {'src/t1.c': [], 'src/t2.c': ['include/h.h']})

    def test_error_located_in_the_header_holds_the_name_on_that_line(self):
        b = self.bulk()
        rep = dict(recipes={'consumer': dict(verdict='ERROR', source='src/user.c',
                                             error="build_ovl/include/h.h:2: syntax error before `s16'")}, images={})
        B.blame(b, self.prover, rep, {'src/t1.c': 'x', 'src/t2.c': 'y',
                                      'include/h.h': 'int old(void);\nvoid appended_b(s16 v);\n'})
        self.assertIn(('src/t2.c', 'include/h.h'), b.held)
        self.assertNotIn(('src/t1.c', 'include/h.h'), b.held)


class ClassTests(unittest.TestCase):
    def facts(self):
        f = X.Facts.__new__(X.Facts)
        f.headers_of = {'src/a.c': {'include/a.h'}}
        f.hdecl = defaultdict(list, {
            'seen': [('include/a.h', 'proto', 'int(int)', 1, 'int')],
            'elsewhere': [('include/b.h', 'proto', 'int(int)', 1, 'int')],
            'sdkfn': [('include/sdk/libgte.h', 'proto', 'int(int)', 1, 'int')],
        })
        f.cdecl = defaultdict(list, {'lonely': [('src/a.c', 'proto', 'void(void)', 1)],
                                     'split': [('src/a.c', 'proto', 'void(int)', 1),
                                               ('src/b.c', 'proto', 'void(short)', 1)]})
        f.defs = defaultdict(set, {'seen': {'int(int)'}, 'elsewhere': {'int(int)'}, 'lonely': {'void(void)'},
                                   'split': {'void(int)'}})
        return f

    def test_classes(self):
        f = self.facts()
        c = lambda n, cn, hp=1, k='proto': X.classify_decl(f, 'src/a.c', n, k, cn, hp)  # noqa: E731
        self.assertEqual(c('seen', 'int(int)'), 'fn.dup_visible_same')
        self.assertEqual(c('seen', 'int()', 0), 'fn.dup_visible_unproto')
        self.assertEqual(c('seen', 'short(int)'), 'fn.dup_visible_differs')
        self.assertEqual(c('elsewhere', 'int(int)'), 'fn.header_elsewhere_same')
        self.assertEqual(c('lonely', 'void(void)'), 'fn.no_header_consistent')
        self.assertEqual(c('split', 'void(int)'), 'fn.no_header_disagree')
        self.assertEqual(c('sdkfn', 'int(int)'), 'fn.no_c_def_sdk')
        self.assertEqual(c('nowhere', 'int(int)'), 'fn.no_c_def')
        self.assertEqual(c('D_80001234', 'int', k='data'), 'data.D_.no_header_consistent')

    def test_rank_takes_least_removable(self):
        self.assertGreater(X.rank('fn.no_c_def'), X.rank('fn.dup_visible_same'))



class AnchorTests(unittest.TestCase):
    def test_port_anchors_parse_literals_only(self):
        with tempfile.TemporaryDirectory() as td:
            f = Path(td) / 'adapt.py'
            f.write_text("import os\nFIXES = {'src/a.c': [('s32 rsin(s16);', 's32 rsin(s32);', 'why')]}\n"
                         "FIXES.update({'src/b.c': [('old', 'new', 'why')]})\n"
                         "FIXES['src/c.c'] = [('x;', 'y;', 'why')]\nraise SystemExit('never imported')\n")
            a = B.port_anchors(f)
        self.assertEqual(a['src/a.c'], ['s32 rsin(s16);'])
        self.assertEqual(a['src/b.c'], ['old'])
        self.assertEqual(a['src/c.c'], ['x;'])


class HeaderTextTests(unittest.TestCase):
    def test_rounds_append_to_the_committed_header_not_the_disk(self):
        import subprocess
        td = tempfile.TemporaryDirectory()
        self.addCleanup(td.cleanup)
        root = Path(td.name)
        (root / 'include').mkdir()
        h = root / 'include/h.h'
        h.write_text('#ifndef H_H\n#define H_H\nint old(void);\n#endif\n')
        subprocess.run(['git', 'init', '-q', str(root)], check=True)
        subprocess.run(['git', '-C', str(root), 'add', '-A'], check=True)
        subprocess.run(['git', '-C', str(root), '-c', 'user.email=test', '-c', 'user.name=test', 'commit', '-qm', 'b'],
                       check=True)
        b = FakeBulk(root, {}, {})
        h.write_text('#ifndef H_H\n#define H_H\nint old(void);\nint stale(void);\n#endif\n')   # a round's output
        self.assertEqual(b.base_text('include/h.h'), '#ifndef H_H\n#define H_H\nint old(void);\n#endif\n')

if __name__ == '__main__':
    unittest.main()
