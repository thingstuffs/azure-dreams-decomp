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
        text = ('/* void f(int); */\nvoid g(void) {\n    int x = f(1);\n    f(2);\n    return f(3);\n'
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

    def test_function_pointer_parameters_compare_by_shape(self):
        a = self.sig('void f(void (*cb)(struct Actor *a, s32 n), int x);')
        b = self.sig('void f(void (*)(Actor *, int), int);')
        c = self.sig('extern void f( void ( * handler )( Actor* p , int ) , s32 y );')
        self.assertEqual(a, b)
        self.assertEqual(a, c)
        self.assertNotEqual(a, self.sig('void f(void (*cb)(Rec *a, s32 n), int x);'))
        self.assertNotEqual(a, self.sig('void f(int (*cb)(Actor *a, s32 n), int x);'))

    def test_function_pointer_typedef_resolves(self):
        with tempfile.TemporaryDirectory() as td:
            (Path(td) / 'include').mkdir()
            (Path(td) / 'include/cb.h').write_text('typedef void (*ActorCallback)(struct Actor *a, s32 n);\n')
            aliases = D.scalar_aliases(td)
        spelled = [D.show_signature(e) for e in D.declarations('void f(void (*cb)(Actor *, int));', {'f'}, aliases)]
        named = [D.show_signature(e) for e in D.declarations('void f(ActorCallback cb);', {'f'}, aliases)]
        self.assertEqual(spelled, named)

    def test_unprototyped_function_pointer_agrees(self):
        entry = lambda t: D.declarations(t, {'f'}, ALIASES)[0]
        self.assertTrue(D.agrees(entry('void f(void (*cb)());'), entry('void f(void (*cb)(Actor *a)) {}')))
        self.assertFalse(D.agrees(entry('void f(void (*cb)(Rec *));'), entry('void f(void (*cb)(Actor *a)) {}')))

    def test_void_stale_params(self):
        entry = lambda t: D.declarations(t, {'f'}, ALIASES)[0]
        self.assertEqual(D.void_stale_params(entry('void f(void *a, int b);'), entry('void f(Rec *a, int b) {}')), [0])
        self.assertEqual(D.void_stale_params(entry('void f(Rec *a);'), entry('void f(Rec *a) {}')), [])
        self.assertEqual(D.void_stale_params(entry('void f(void *a);'), entry('void f(void *a) {}')), [])
        self.assertEqual(D.void_stale_params(entry('void f();'), entry('void f(Rec *a) {}')), [])


class DataTests(unittest.TestCase):
    """Data objects: extern declarations and definitions grouped by name."""

    def scan(self, files, symbols=''):
        with tempfile.TemporaryDirectory() as td:
            root = Path(td)
            (root / 'include').mkdir()
            (root / 'config').mkdir()
            (root / 'config/slus_006.14.symbols.txt').write_text(symbols)
            for path, text in files.items():
                (root / path).parent.mkdir(parents=True, exist_ok=True)
                (root / path).write_text(text)
            return D.data_census(root)[0]

    def test_incomplete_array_and_spelling_agree(self):
        found = self.scan({
            'src/m/a.c': 'extern u8 tab[32];\nextern struct Foo foo;\nextern unsigned int w[];\n',
            'src/m/b.c': 'void g(void) {\n    extern unsigned char tab[];\n    extern Foo foo;\n}\nextern u32 w[4];\n',
            'include/m/c.h': 'extern const u8 tab[0x20];\nextern int fn(int);\nextern void (*cb)(int);\n',
        })
        self.assertEqual(found, {})

    def test_classes(self):
        found = self.scan({
            'src/m/a.c': 'extern u8 sized[3];\nextern u8 sign[4];\nextern u32 words[8];\nextern MATRIX mat;\n'
                         'extern int *ptr;\nextern int arr[];\n',
            'src/m/b.c': 'extern u8 sized[32];\nextern s8 sign[4];\nextern u8 words[32];\nextern u8 mat[3];\n'
                         'extern int arr[];\n',
            'include/m/c.h': 'extern int ptr[];\n',
        })
        self.assertEqual({n: r['klass'] for n, r in found.items()},
                         {'sized': 'size mismatch', 'sign': 'element type only', 'words': 'incompatible type',
                          'mat': 'incompatible type', 'ptr': 'incompatible type'})
        self.assertEqual(len(found['sized']['rows']), 2)

    def test_definition_is_a_reference_and_static_is_local(self):
        found = self.scan({
            'src/m/def.c': 'u8 table[16] = {0};\nstatic u8 local[4];\n',
            'src/m/use.c': 'extern u8 table[8];\nextern s32 local[2];\nstatic u16 local[9];\n',
        })
        self.assertEqual(list(found), ['table'])
        self.assertEqual([r[0] for r in found['table']['rows']], ['def', 'decl'])

    def test_symbol_size_is_the_reference_without_definition(self):
        found = self.scan({'src/m/a.c': 'extern u8 sym[16];\nextern u8 ok[8];\nextern u8 open[];\n'},
                          'sym = 0x80010000; // type:u8 size:0x20\nok = 0x80010020; // type:u8 size:8\n'
                          'open = 0x80010030; // type:u8 size:0x20\n')
        self.assertEqual(list(found), ['sym'])
        self.assertIn(('symbol', 'config/slus_006.14.symbols.txt', '32 bytes'), found['sym']['rows'])

    def test_overlay_address_names_are_per_image(self):
        found = self.scan({'src/town/a.c': 'extern u8 D_80010000[4];\n', 'src/dungeon/a.c': 'extern int D_80010000;\n'})
        self.assertEqual(found, {})

    def test_new_disagreement_vs_base_and_tsv(self):
        base = self.scan({'src/m/a.c': 'extern u8 a[4];\nextern u8 b[4];\n', 'src/m/b.c': 'extern u16 b[2];\n'})
        head = self.scan({'src/m/a.c': 'extern u8 a[4];\nextern u8 b[4];\n',
                          'src/m/b.c': 'extern u16 b[2];\nextern u32 b[1];\n',
                          'src/m/c.c': 'extern u8 a[5];\n'})
        self.assertEqual(D.new_data_disagreements(head, base), ['a', 'b'])
        self.assertEqual(D.new_data_disagreements(base, base), [])

    def test_check_data_reports_and_writes_list(self):
        with tempfile.TemporaryDirectory() as td:
            root = Path(td)
            for sub, text in (('base', 'extern u8 m[32];\n'), ('head', 'extern u8 m[32];\n')):
                (root / sub / 'src/m').mkdir(parents=True)
                (root / sub / 'src/m/a.c').write_text(text)
            (root / 'head/src/m/b.c').write_text('extern u8 m[3];\n')
            (root / 'head/config').mkdir()
            (root / 'head/config/names.tsv').write_text('0x8006CD10\tD_8006CD10\tm\tnote\n')
            with redirect_stdout(io.StringIO()) as out:
                self.assertEqual(D.check_data(root / 'head', root / 'head', root / 'base'), 1)
                self.assertEqual(D.check_data(root / 'base', root / 'base', root / 'base'), 0)
            self.assertIn('data declaration agreement FAIL: 1 new', out.getvalue())
            rows = (root / 'head/build/decl_data.tsv').read_text().splitlines()
            self.assertEqual(len(rows), 3)
            self.assertTrue(rows[1].startswith('m\t0x8006CD10\tsize mismatch\tdecl\tsrc/m/a.c:1\t'))


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

    def test_sdk_prototype_is_the_reference_for_a_library_function(self):
        (self.root / 'include/sdk').mkdir()
        (self.root / 'include/sdk/libgte.h').write_text('s32 rcos(s32);\n')
        (self.root / 'include/m/old.h').write_text('s32 rcos(s32, ...);\n')        # a stale module copy
        (self.root / 'src/m/trig.c').write_text('s32 rcos(s32, ...);\nint f(void) { return rcos(1, 2); }\n')
        problems = D.check_tree(self.root, {'rcos'})
        self.assertEqual({p['file'] for p in problems}, {'include/m/old.h', 'src/m/trig.c'})
        self.assertTrue(all(p['expected_at'].startswith('include/sdk/libgte.h') for p in problems))
        (self.root / 'include/sdk/libgte.h').unlink()           # without an SDK header every include/ prototype counts
        self.assertEqual(D.check_tree(self.root, {'rcos'}), [])

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

    def test_void_pointer_stale_is_reported_not_failing_by_default(self):
        (self.root / 'src/m/voidp.c').write_text('s32 pick(void *a, s32 n);\n')
        git(self.root, 'add', '-A')
        git(self.root, 'commit', '-qm', 'void decl')
        base = git(self.root, 'rev-parse', 'HEAD')
        self.retype()
        base_tree = D.C.materialize(self.root, base, self.root / 'out/base')
        self.assertEqual(D.check_tree(self.root, {'pick'}) and [p['file'] for p in D.check_tree(self.root, {'pick'})],
                         ['src/m/block.c', 'src/m/local.c'])
        stale = D.void_pointer_stale(base_tree, self.root, {'pick'})
        self.assertEqual([p['file'] for p in stale], ['src/m/voidp.c'])
        with redirect_stdout(io.StringIO()) as out:
            code = D.check_change(self.root, base, self.root, {'pick'}, base_tree=base_tree)
        self.assertIn('VOID POINTER STALE src/m/voidp.c:1', out.getvalue())
        self.assertIn('void_pointer_stale 1 (report-only)', out.getvalue())
        self.assertEqual(code, 1)         # the two plain disagreements still fail
        for path in ('src/m/local.c', 'src/m/block.c'):
            f = self.root / path
            f.write_text(f.read_text().replace('struct Actor *a', 'Rec *a'))
        with redirect_stdout(io.StringIO()):
            self.assertEqual(D.check_change(self.root, base, self.root, {'pick'}, base_tree=base_tree), 0)
            self.assertEqual(D.check_change(self.root, base, self.root, {'pick'}, base_tree=base_tree,
                                            fail_void=True), 1)
            self.assertEqual(D.main([base, '--root', str(self.root), '--fail-void']), 1)
            self.assertEqual(D.main([base, '--root', str(self.root)]), 0)

    def test_unchanged_void_declaration_is_not_reported(self):
        (self.root / 'src/m/voidp.c').write_text('s32 pick(void *a, s32 n);\n')
        self.retype()
        git(self.root, 'add', '-A')
        git(self.root, 'commit', '-qm', 'retyped with stale void decl')
        later = git(self.root, 'rev-parse', 'HEAD')
        (self.root / 'src/m/def.c').write_text(
            (self.root / 'src/m/def.c').read_text() + '/* comment only */\n')
        git(self.root, 'commit', '-qam', 'comment')
        base_tree = D.C.materialize(self.root, later, self.root / 'out/later')
        self.assertEqual(D.void_pointer_stale(base_tree, self.root, {'pick'}), [])

    def test_base_tree_is_reused_not_rematerialised(self):
        self.retype()
        base_tree = D.C.materialize(self.root, self.base, self.root / 'out/base')
        calls = []
        original = D.C.materialize
        D.C.materialize = lambda *a, **k: calls.append(a) or original(*a, **k)
        try:
            with redirect_stdout(io.StringIO()):
                D.check_change(self.root, self.base, self.root, {'pick'}, base_tree=base_tree)
                self.assertEqual(calls, [])
                D.check_change(self.root, self.base, self.root, {'pick'})
        finally:
            D.C.materialize = original
        self.assertEqual(len(calls), 1)

    def test_renamed_file_keeps_existing_disagreement_existing(self):
        self.retype()
        git(self.root, 'commit', '-qam', 'retype')
        base = git(self.root, 'rev-parse', 'HEAD')
        base_tree = D.C.materialize(self.root, base, self.root / 'out/renamed_base')
        git(self.root, 'mv', 'src/m/local.c', 'src/m/local_moved.c')
        git(self.root, 'commit', '-qm', 'rename')
        new, existing = D.new_problems(base_tree, self.root, {'pick'}, {'src/m/local_moved.c': 'src/m/local.c'})
        self.assertEqual(sorted(p['file'] for p in existing), ['src/m/block.c', 'src/m/local_moved.c'])
        self.assertEqual(new, [])
        new, existing = D.new_problems(base_tree, self.root, {'pick'})        # rename unknown: looks new
        self.assertEqual([p['file'] for p in new], ['src/m/local_moved.c'])

    def test_edited_callback_declaration_does_not_fail(self):
        (self.root / 'include/m/api.h').write_text(
            (self.root / 'include/m/api.h').read_text() + 'void on(void (*cb)(Actor *a, s32 n), s32 k);\n')
        (self.root / 'src/m/on.c').write_text('void on(void (*handler)(struct Actor *, int), int count) {}\n')
        self.assertEqual(D.check_tree(self.root, {'on'}), [])

    def test_main_exit_codes(self):
        self.retype()
        with redirect_stdout(io.StringIO()) as out:
            self.assertEqual(D.main([self.base, '--root', str(self.root), '--fail-new']), 1)
            self.assertEqual(D.main([self.base, '--root', str(self.root)]), 0)
        self.assertIn('STALE DECLARATION src/m/local.c:1', out.getvalue())
        self.assertIn('declaration agreement FAIL: 2 new', out.getvalue())


if __name__ == '__main__':
    unittest.main()
