"""decl_agreement: stale declarations of retyped functions.

    python3 -m unittest tools.lint.test_decl_agreement
"""
from pathlib import Path
import io
import os
import subprocess
import sys
import tempfile
import unittest
from contextlib import redirect_stdout

HERE = Path(__file__).resolve().parent
sys.path.insert(0, str(HERE))
import decl_agreement as D  # noqa: E402

ALIASES = D.scalar_aliases(HERE.parents[1])


def git(root, *args):
    env = dict(os.environ, GIT_AUTHOR_NAME='t', GIT_AUTHOR_EMAIL='t@invalid',
               GIT_COMMITTER_NAME='t', GIT_COMMITTER_EMAIL='t@invalid')
    return subprocess.run(['git', *args], cwd=root, env=env, check=True,
                          capture_output=True, text=True).stdout.strip()


class NormalizeTests(unittest.TestCase):
    def sig(self, text, name='f'):
        return [D.show_signature(e) for e in D.declarations(text, {name}, ALIASES)]

    def test_names_whitespace_tags_and_aliases_do_not_matter(self):
        a = self.sig('extern s32 f(struct Actor *a, u8 b, unsigned int c);')
        b = self.sig('int f( Actor* , unsigned char x,unsigned  );')
        self.assertEqual(a, b)
        self.assertEqual(self.sig('void f(int a[4]);'), self.sig('void f(int *a);'))

    def test_different_types_differ(self):
        self.assertNotEqual(self.sig('void f(struct Actor *a);'), self.sig('void f(ActorRecord *a);'))
        self.assertNotEqual(self.sig('s16 f(void);'), self.sig('s32 f(void);'))
        self.assertNotEqual(self.sig('void f(const char *a);'), self.sig('void f(char *a);'))

    def test_calls_comments_and_initializers_are_not_declarations(self):
        text = ('/* void f(int); */\\nvoid g(void) {\n    int x = f(1);\n    f(2);\n    return f(3);\n'
                '    if (x) f(4);\n    else f(5);\n}\n')
        self.assertEqual(D.declarations(text, {'f'}, ALIASES), [])

    def test_block_scope_declaration_is_found(self):
        text = 'void g(void) {\n    extern s32 f(struct Actor *a);\n    f(0);\n}\n'
        found = D.declarations(text, {'f'}, ALIASES)
        self.assertEqual([(e[0], e[1], e[2]) for e in found], [('f', 2, 'decl')])

    def test_unprototyped_and_void_pointer_agree(self):
        entry = lambda t: D.declarations(t, {'f'}, ALIASES)[0]
        self.assertTrue(D.agrees(entry('void f();'), entry('void f(Actor *a) {}')))
        self.assertTrue(D.agrees(entry('void f(void *a);'), entry('void f(Actor *a) {}')))
        self.assertFalse(D.agrees(entry('void f(Actor *a, int b);'), entry('void f(Actor *a) {}')))


class TreeTests(unittest.TestCase):
    def setUp(self):
        self.tmp = tempfile.TemporaryDirectory()
        self.addCleanup(self.tmp.cleanup)
        self.root = Path(self.tmp.name)
        (self.root / 'src/m').mkdir(parents=True)
        (self.root / 'include/m').mkdir(parents=True)
        files = {
            'include/m/api.h': 'typedef struct Actor Actor;\ntypedef struct Rec Rec;\ns32 pick(Actor *a, s32 n);\n',
            'src/m/def.c': '#include "m/api.h"\ns32 pick(Actor *a, s32 n) { return n; }\n',
            'src/m/local.c': 's32 pick(struct Actor *a, s32 n);\nint use(struct Actor *a) { return pick(a, 1); }\n',
            'src/m/block.c': 'int use2(void *a) {\n    extern s32 pick(struct Actor *a, s32 n);\n    return pick(a, 1);\n}\n',
            'src/m/static_a.c': 'static void helper(int a) {}\n',
            'src/m/static_b.c': 'static void helper(Rec *a) {}\nvoid helper(Rec *a);\n',
        }
        for path, text in files.items():
            (self.root / path).write_text(text)
        git(self.root, 'init', '-q')
        git(self.root, 'add', '-A')
        git(self.root, 'commit', '-qm', 'base')
        self.base = git(self.root, 'rev-parse', 'HEAD')

    def retype(self):
        for path in ('include/m/api.h', 'src/m/def.c'):
            f = self.root / path
            f.write_text(f.read_text().replace('Actor *a', 'Rec *a').replace('pick(Actor', 'pick(Rec'))

    def test_consistent_tree_is_clean(self):
        self.assertEqual(D.check_tree(self.root, {'pick', 'helper'}), [])

    def test_retyped_definition_flags_stale_local_and_block_declarations(self):
        self.retype()
        problems = D.check_tree(self.root, {'pick'})
        self.assertEqual({(p['file'], p['line']) for p in problems},
                         {('src/m/local.c', 1), ('src/m/block.c', 2)})
        self.assertIn('Actor*', problems[0]['declared'])
        self.assertIn('Rec*', problems[0]['expected'])

    def test_changed_names_and_new_vs_existing(self):
        self.retype()
        self.assertEqual(D.changed_function_names(self.root, self.base, None), {'pick'})
        base_tree = D.C.materialize(self.root, self.base, self.root / 'out/base')
        new, existing = D.new_problems(base_tree, self.root, {'pick'})
        self.assertEqual(len(new), 2)
        self.assertEqual(existing, [])
        # an already-disagreeing declaration that does not change is not new
        git(self.root, 'commit', '-qam', 'retype')
        new2, existing2 = D.new_problems(base_tree, self.root, {'pick'})
        self.assertEqual(len(new2), 2)          # BASE agreed, so still new relative to BASE
        later = D.C.materialize(self.root, 'HEAD', self.root / 'out/later')
        new3, existing3 = D.new_problems(later, self.root, {'pick'})
        self.assertEqual((len(new3), len(existing3)), (0, 2))

    def test_fixing_the_declaration_passes(self):
        self.retype()
        for path in ('src/m/local.c', 'src/m/block.c'):
            f = self.root / path
            f.write_text(f.read_text().replace('struct Actor *a', 'Rec *a'))
        self.assertEqual(D.check_tree(self.root, {'pick'}), [])

    def test_static_definitions_are_per_file(self):
        self.assertEqual(D.check_tree(self.root, {'helper'}), [])
        f = self.root / 'src/m/static_b.c'
        f.write_text('static void helper(Actor *a) {}\nvoid helper(Rec *a);\n')
        problems = D.check_tree(self.root, {'helper'})
        self.assertEqual([(p['file'], p['line']) for p in problems], [('src/m/static_b.c', 2)])

    def test_lint_closure_hook_fails_on_stale_declaration(self):
        import argparse
        import lint_closure
        self.retype()
        args = argparse.Namespace(base=self.base)
        with redirect_stdout(io.StringIO()) as out:
            self.assertEqual(lint_closure.decl_check(args, self.root, self.root, ['pick'], {}), 1)
            self.assertEqual(lint_closure.decl_check(args, self.root, self.root, [], {}), 0)
        self.assertIn('declaration agreement FAIL', out.getvalue())

    def test_main_exit_codes(self):
        self.retype()
        with redirect_stdout(io.StringIO()) as out:
            self.assertEqual(D.main([self.base, '--root', str(self.root), '--fail-new']), 1)
            self.assertEqual(D.main([self.base, '--root', str(self.root)]), 0)
        self.assertIn('STALE DECLARATION src/m/local.c:1', out.getvalue())
        self.assertIn('declaration agreement FAIL: 2 new', out.getvalue())


if __name__ == '__main__':
    unittest.main()
