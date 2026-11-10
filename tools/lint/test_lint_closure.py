"""lint_closure: the TU closure of a change and the per-group site gate.

    python3 -m unittest tools.lint.test_lint_closure
"""
from pathlib import Path
import json
import os
import shutil
import subprocess
import sys
import tempfile
import unittest
from contextlib import redirect_stderr, redirect_stdout
from unittest.mock import patch
import io

HERE = Path(__file__).resolve().parent
sys.path.insert(0, str(HERE))
import lint_closure as C  # noqa: E402


def git(root, *args):
    env = dict(os.environ, GIT_AUTHOR_NAME='t', GIT_AUTHOR_EMAIL='t@invalid',
               GIT_COMMITTER_NAME='t', GIT_COMMITTER_EMAIL='t@invalid')
    return subprocess.run(['git', *args], cwd=root, env=env, check=True,
                          capture_output=True, text=True).stdout.strip()


def gcc_multilib():
    if not shutil.which('gcc'):
        return False
    probe = subprocess.run(['gcc', '-m32', '-fsyntax-only', '-x', 'c', '-'], input='int x;\n',
                           capture_output=True, text=True)
    return probe.returncode == 0


class TextTests(unittest.TestCase):
    def test_signature_change_is_detected_but_spacing_is_not(self):
        old = 'void f(void *p);\nint g(int a) { return a; }\n'
        self.assertEqual(C.changed_signatures(old, 'void f(struct S *p);\nint g(int a) { return a; }\n'), {'f'})
        self.assertEqual(C.changed_signatures(old, 'void  f( void * p );\nint g(int a)\n{ return a; }\n'), set())
        self.assertEqual(C.changed_signatures(old, old + 'extern void h(void);\n'), {'h'})

    def test_comments_calls_and_initializers_are_not_declarations(self):
        text = ('/* void fake(int); */\nstatic void (*const slot)(int) = real;\n'
                'void body(void) { call(1); }\n')
        self.assertEqual(set(C.function_signatures(text)), {'body'})

    def test_declared_identifiers(self):
        self.assertEqual(C.declared_identifiers('    s16 facing;'), {'facing'})
        self.assertEqual(C.declared_identifiers('#define NODE_HEADER(p) ((X *)(p) - 1)'), {'NODE_HEADER'})
        self.assertEqual(C.declared_identifiers('void f(ActorRecord *motion, s32 x);'), {'f'})
        self.assertEqual(C.declared_identifiers('void (*const entry)(u8 *, Motion *) = follow;'), {'entry'})
        self.assertEqual(C.declared_identifiers('} ActorRecord; /* x */'), {'ActorRecord'})


class ClosureTests(unittest.TestCase):
    def setUp(self):
        self.tmp = tempfile.TemporaryDirectory()
        self.addCleanup(self.tmp.cleanup)
        root = self.root = Path(self.tmp.name)
        for d in ('src/m', 'include/m'):
            (root / d).mkdir(parents=True)
        self.files = {
            'include/m/api.h': '#ifndef API\n#define API\nstruct S {\n    int a;\n    int field;\n};\nvoid f(void *p);\n#endif\n',
            'include/m/wrap.h': '#include "m/api.h"\n',
            'include/m/macro.h': '#define CALL_F(x) f(x)\n',
            'src/m/def.c': '#include "m/api.h"\nvoid f(void *p) { (void)p; }\n',
            'src/m/via_wrap.c': '#include "m/wrap.h"\nint w(struct S *s) { return s->a; }\n',
            'src/m/caller.c': 'extern void f(void *);\nvoid c(int *x) { f(x); }\n',
            'src/m/macro_user.c': '#include "m/macro.h"\nvoid m(int *x) { CALL_F(x); }\n',
            'src/m/field_user.c': '#include "m/wrap.h"\nint u(struct S *s) { return s->field; }\n',
            'src/m/other.c': 'int o(void)\n{\n    int a = 1;\n    int b = 2;\n    int c = 3;\n    return a + b + c;\n}\n',
        }
        for path, text in self.files.items():
            (root / path).write_text(text)
        git(root, 'init', '-q')
        git(root, 'add', '-A')
        git(root, 'commit', '-qm', 'base')
        self.base = git(root, 'rev-parse', 'HEAD')
        self.registered = [p for p in self.files if p.startswith('src/')]

    def test_prototype_change_pulls_includers_callers_and_macro_users(self):
        header = self.root / 'include/m/api.h'
        header.write_text(self.files['include/m/api.h'].replace('void f(void *p);', 'void f(struct S *p);'))
        plan = C.compute_closure(self.root, self.base, None, self.registered)
        self.assertEqual(plan['functions'], ['f'])
        self.assertEqual(set(plan['closure']), {'src/m/def.c', 'src/m/via_wrap.c', 'src/m/caller.c',
                                                 'src/m/macro_user.c', 'src/m/field_user.c'})
        self.assertIn('src/m/caller.c', plan['callers'])        # untouched, no include: identifier
        self.assertIn('src/m/macro_user.c', plan['callers'])    # through a macro body in a header
        self.assertNotIn('src/m/other.c', plan['closure'])

    def test_cap_keeps_only_includers_using_changed_identifiers(self):
        header = self.root / 'include/m/api.h'
        header.write_text(self.files['include/m/api.h'].replace('int field;', 'short field;'))
        out = io.StringIO()
        plan = C.compute_closure(self.root, self.base, None, self.registered, cap=1)
        self.assertEqual(plan['functions'], [])
        self.assertEqual(set(plan['closure']), {'src/m/field_user.c'})
        self.assertEqual(plan['capped'][0]['includers'], 3)
        C.print_plan(plan, out)
        self.assertIn('capped include/m/api.h: 3 including TUs -> 1', out.getvalue())
        uncapped = C.compute_closure(self.root, self.base, None, self.registered)
        self.assertEqual(set(uncapped['closure']), {'src/m/def.c', 'src/m/via_wrap.c', 'src/m/field_user.c'})

    def test_changed_tu_and_rename(self):
        git(self.root, 'mv', 'src/m/other.c', 'src/m/renamed.c')
        (self.root / 'src/m/renamed.c').write_text(self.files['src/m/other.c'].replace('3;', '4;'))
        plan = C.compute_closure(self.root, self.base, None, self.registered + ['src/m/renamed.c'])
        self.assertEqual(plan['changed'], ['src/m/renamed.c'])
        self.assertEqual(plan['renames'], {'src/m/renamed.c': 'src/m/other.c'})

    def test_materialize_extracts_only_sources(self):
        dest = C.materialize(self.root, self.base, self.root / 'out/base')
        self.assertTrue((dest / 'include/m/api.h').is_file())
        self.assertFalse((dest / '.git').exists())


def finding(file, function, warning, sites, count=None):
    return dict(file=file, function=function, warning=warning, count=count or len(sites),
                sites=';'.join(sites), messages='m')


class GateTests(unittest.TestCase):
    def test_new_site_fails_but_extra_observation_of_same_site_does_not(self):
        base = [finding('include/h.h', 'inl', '-Wshadow', ['include/h.h:3:1'], 4)]
        head = [finding('include/h.h', 'inl', '-Wshadow', ['include/h.h:3:1'], 6),
                finding('src/a.c', 'a', '-Wincompatible-pointer-types', ['src/a.c:9:3'])]
        rising = C.increases(base, head)
        self.assertEqual([(r['file'], r['base_sites'], r['head_sites']) for r in rising], [('src/a.c', 0, 1)])

    def test_rename_maps_base_groups(self):
        base = [finding('src/old.c', 'a', '-Wshadow', ['src/old.c:1:1'])]
        head = [finding('src/new.c', 'a', '-Wshadow', ['src/new.c:2:1'])]
        self.assertEqual(C.increases(base, head, {'src/new.c': 'src/old.c'}), [])
        self.assertEqual(len(C.increases(base, head)), 1)

    def test_report_exit_codes(self):
        with redirect_stdout(io.StringIO()) as out:
            self.assertEqual(C.report([], [], [], [], {}, 0), 0)
            failure = dict(tu='src/a.c', mode='m32', phase='syntax', first_error='x')
            self.assertEqual(C.report([], [], [failure], [failure], {}, 0), 0)
            self.assertEqual(C.report([], [], [], [failure], {}, 0), 1)
        self.assertIn('NEW COMPILE FAILURE', out.getvalue())


class RenameAndFullTests(unittest.TestCase):
    def test_rename_hint(self):
        base = [finding('src/a.c', 'old_name', '-Wshadow', ['src/a.c:4:1'])]
        head = [finding('src/a.c', 'new_name', '-Wshadow', ['src/a.c:4:1'])]
        with redirect_stdout(io.StringIO()) as out:
            self.assertEqual(C.report(base, head, [], [], {}, 0), 1)
        self.assertIn('hint: possibly old_name renamed', out.getvalue())

    def test_rename_recorded_in_names_is_not_new(self):
        base = [finding('src/a.c', 'old_name', '-Wshadow', ['src/a.c:4:1'])]
        head = [finding('src/a.c', 'new_name', '-Wshadow', ['src/a.c:4:1'])]
        names = {'old_name': {'0x80024050'}, 'new_name': {'0x80024050'}}
        with redirect_stdout(io.StringIO()) as out:
            self.assertEqual(C.report(base, head, [], [], {}, 0, names), 0)
        self.assertIn('renamed -Wshadow src/a.c old_name -> new_name', out.getvalue())
        moved = [finding('src/a.c', 'new_name', '-Wshadow', ['src/a.c:9:1'])]
        with redirect_stdout(io.StringIO()):
            self.assertEqual(C.report(base, moved, [], [], {}, 0, names), 1)   # a different site is new
        with redirect_stdout(io.StringIO()):
            self.assertEqual(C.report(base, head, [], [], {}, 0, {'new_name': {'0x1'}}), 1)  # no names.tsv row

    def census(self, directory, findings, **summary):
        directory.mkdir(parents=True, exist_ok=True)
        fields = ['finding', 'file', 'function', 'warning', 'subsystem', 'count', 'tu_count',
                  'modes', 'phases', 'sites', 'messages']
        rows = [dict(finding='L', subsystem='m', tu_count=1, modes='m32', phases='flow', **f) for f in findings]
        C.lint_build.write_tsv(directory / 'lint_findings.tsv', fields, rows)
        C.lint_build.write_tsv(directory / 'lint_compile_failures.tsv',
                               ['tu', 'mode', 'phase', 'returncode', 'first_error', 'log'], [])
        (directory / 'lint_units.tsv').write_text('tu\trows\n')
        base = dict(schema_version=1, compiler='gcc x', modes=['m32', 'm64'], phases=['syntax', 'flow'],
                    flags=['-O1'], units=2, limited=False)
        base.update(summary)
        (directory / 'lint_summary.json').write_text(json.dumps(base))

    def run_full(self, base_findings, head_findings, base_summary=None, save=False):
        tmp = tempfile.TemporaryDirectory()
        self.addCleanup(tmp.cleanup)
        root = Path(tmp.name)
        git(root, 'init', '-q')
        (root / 'f').write_text('x\n')
        git(root, 'add', '-A')
        git(root, 'commit', '-qm', 'base')
        self.census(root / 'basecensus', base_findings, **(base_summary or {}))

        def fake_lint(argv):
            self.census(Path(argv[argv.index('--out') + 1]), head_findings)
            return 0
        args = ['HEAD', '--root', str(root), '--port', str(root), '--full', '--out', str(root / 'out'),
                '--base-census', str(root / 'basecensus')] + (['--save-census', str(root / 'saved')] if save else [])
        with patch.object(C.lint_build, 'units', return_value={}), \
                patch.object(C.lint_build, 'main', side_effect=fake_lint), \
                redirect_stdout(io.StringIO()) as out, redirect_stderr(io.StringIO()) as err:
            code = C.main(args)
        return code, out.getvalue() + err.getvalue(), root

    def test_full_mode(self):
        same = [finding('src/a.c', 'a', '-Wshadow', ['src/a.c:1:1'])]
        more = same + [finding('src/b.c', 'b', '-Wint-conversion', ['src/b.c:2:1'])]
        code, out, root = self.run_full(same, same, save=True)
        self.assertEqual(code, 0, out)
        self.assertTrue((root / 'saved/lint_findings.tsv').is_file())
        code, out, _ = self.run_full(same, more)
        self.assertEqual(code, 1)
        self.assertIn('NEW -Wint-conversion src/b.c b', out)
        self.assertEqual(self.run_full(same, same, dict(limited=True))[0], 2)
        code, out, _ = self.run_full(same, same, dict(flags=['-O2']))
        self.assertEqual(code, 2)
        self.assertIn('flags differs', out)


@unittest.skipUnless(gcc_multilib(), 'needs gcc with -m32 and -m64')
class EndToEndTest(unittest.TestCase):
    """An untouched caller of a retyped prototype: the AC131 B1 shape."""

    def test_untouched_caller_gets_new_incompatible_pointer(self):
        tmp = tempfile.TemporaryDirectory()
        self.addCleanup(tmp.cleanup)
        root, port = Path(tmp.name) / 'game', Path(tmp.name) / 'port'
        for d in ('src/slus', 'include/slus', 'ledger', 'out'):
            (root / d).mkdir(parents=True)
        for d in ('tools', 'include'):
            (port / d).mkdir(parents=True)
        (port / 'tools/build.py').write_text('CFLAGS = ["-O1", "-I" + str(GEN / "include")]\n')
        (root / 'include/slus/b.h').write_text('struct Actor { int x; };\nvoid take(void *motion);\n')
        (root / 'src/slus/a.c').write_text('#include "slus/b.h"\nvoid take(void *motion) { (void)motion; }\n')
        (root / 'src/slus/caller.c').write_text('#include "slus/b.h"\nvoid g(struct Actor *a) { take(a); }\n')
        rows = [dict(id='slus/a', container='slus', c_path='a.c'),
                dict(id='slus/caller', container='slus', c_path='caller.c')]
        (root / 'ledger/rows.jsonl').write_text(''.join(json.dumps(r) + '\n' for r in rows))
        (root / '.gitignore').write_text('out/\n')
        git(root, 'init', '-q')
        git(root, 'add', '-A')
        git(root, 'commit', '-qm', 'base')
        (root / 'include/slus/b.h').write_text('struct Actor { int x; };\nstruct View;\nvoid take(struct View *motion);\n')
        (root / 'src/slus/a.c').write_text('#include "slus/b.h"\nvoid take(struct View *motion) { (void)motion; }\n')
        with redirect_stdout(io.StringIO()) as out:
            code = C.main(['HEAD', '--root', str(root), '--port', str(port), '--out', str(root / 'out')])
        self.assertEqual(code, 1, out.getvalue())
        self.assertIn('NEW -Wincompatible-pointer-types src/slus/caller.c g', out.getvalue())
        with redirect_stdout(io.StringIO()):
            self.assertEqual(C.main(['HEAD', '--root', str(root), '--port', str(port),
                                     '--out', str(root / 'out'), '--plan']), 0)


if __name__ == '__main__':
    unittest.main()
