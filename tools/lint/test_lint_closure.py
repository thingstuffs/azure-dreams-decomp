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


class AcceptedSitesTests(unittest.TestCase):
    """tools/lint/accepted_warning_sites.tsv: groups a change records are accepted once, by that change."""

    def repo(self, base_text=None):
        tmp = tempfile.TemporaryDirectory()
        self.addCleanup(tmp.cleanup)
        root = Path(tmp.name)
        (root / 'tools/lint').mkdir(parents=True)
        git(root, 'init', '-q')
        (root / 'f').write_text('x\n')
        if base_text is not None:
            (root / C.ACCEPTED).write_text(base_text)
        git(root, 'add', '-A')
        git(root, 'commit', '-qm', 'base')
        return root

    SDK = frozenset({'RotTransPers', 'SetRotMatrix'})
    PTR = '-Wincompatible-pointer-types'

    @staticmethod
    def sdk_finding(file, function, per_site):
        """A finding with per-site messages {site: [message]} (lint_build's site_messages column)."""
        row = finding(file, function, AcceptedSitesTests.PTR, sorted(per_site))
        row['messages'] = ' | '.join(sorted({m for ms in per_site.values() for m in ms}))
        row['site_messages'] = json.dumps({k: sorted(v) for k, v in sorted(per_site.items())})
        return row

    @staticmethod
    def arg(n, f):
        return f"passing argument {n} of '{f}' from incompatible pointer type"

    def stamped(self, root, rows, base_text=None):
        (root / C.ACCEPTED).write_text('# header\n' + C.STAMP + C.stamp_of(base_text) + '\n' + C.ACCEPTED_HEADER
                                       + '\n' + ''.join(r + '\n' for r in rows))

    def gate(self, base, head, root):
        with redirect_stdout(io.StringIO()) as out:
            code = C.report(base, head, [], [], {}, 0, accepted=C.accepted_rows(root, 'HEAD'), sdk=self.SDK)
        return code, out.getvalue()

    def test_added_row_without_stamp_fails(self):
        # The old code honoured any row absent from BASE's copy (a mute): this must now fail the closure.
        root = self.repo()
        (root / C.ACCEPTED).write_text(C.ACCEPTED_HEADER + '\n' + self.PTR + '\tsrc/a.c\ta\t2\tSetRotMatrix\n')
        head = [self.sdk_finding('src/a.c', 'a', {'src/a.c:1:1': [self.arg(1, 'SetRotMatrix')],
                                                  'src/a.c:2:1': [self.arg(1, 'SetRotMatrix')]})]
        code, out = self.gate([], head, root)
        self.assertEqual(code, 1, out)
        self.assertIn('ACCEPTED ROW REFUSED', out)
        self.assertEqual(self.gate([], [], root)[0], 1)          # growth fails even when nothing rises

    def test_raised_row_without_stamp_fails_and_lowered_row_is_inert(self):
        text = '# old\n' + C.ACCEPTED_HEADER + '\n' + self.PTR + '\tsrc/a.c\ta\t2\t\n'
        root = self.repo(text)
        (root / C.ACCEPTED).write_text(text.replace('\t2\t', '\t3\t'))
        self.assertEqual(C.accepted_rows(root, 'HEAD')[0], {})
        self.assertEqual(len(C.accepted_rows(root, 'HEAD')[1]), 1)
        (root / C.ACCEPTED).write_text(text.replace('\t2\t', '\t1\t'))     # lowering is allowed
        self.assertEqual(C.accepted_rows(root, 'HEAD'), ({}, []))
        rising = [self.sdk_finding('src/a.c', 'a', {'src/a.c:1:1': [self.arg(1, 'RotTransPers')]})]
        self.assertEqual(self.gate([], rising, root)[0], 1)       # a BASE row honours nothing

    def test_stamped_row_honours_sdk_passing_argument_sites_up_to_its_count(self):
        root = self.repo()
        self.stamped(root, [self.PTR + '\tsrc/a.c\ta\t2\tRotTransPers', '-Wint-conversion\tsrc/a.c\ta\t5\t'])
        honoured, refused = C.accepted_rows(root, 'HEAD')
        self.assertEqual(honoured, {('src/a.c', 'a', self.PTR): 2})
        self.assertEqual(len(refused), 1)                         # class cannot be accepted
        self.stamped(root, [self.PTR + '\tsrc/a.c\ta\t2\tRotTransPers'])
        sdk2 = {'src/a.c:1:1': [self.arg(1, 'RotTransPers')], 'src/a.c:2:1': [self.arg(2, 'RotTransPers')]}
        code, out = self.gate([], [self.sdk_finding('src/a.c', 'a', sdk2)], root)
        self.assertEqual(code, 0, out)
        self.assertIn(f'accepted {self.PTR} src/a.c a: sites 0 -> 2', out)
        three = dict(sdk2, **{'src/a.c:3:1': [self.arg(1, 'RotTransPers')]})
        self.assertEqual(self.gate([], [self.sdk_finding('src/a.c', 'a', three)], root)[0], 1)

    def test_stamp_for_another_base_is_refused(self):
        root = self.repo()
        self.stamped(root, [self.PTR + '\tsrc/a.c\ta\t1\t'], base_text='an older copy\n')
        honoured, refused = C.accepted_rows(root, 'HEAD')
        self.assertEqual(honoured, {})
        self.assertIn('no --write-accepted stamp', refused[0])

    def test_assignment_initialization_and_return_sites_are_never_honoured(self):
        root = self.repo()
        self.stamped(root, [self.PTR + '\tsrc/a.c\ta\t2\t'])
        for message in ("assignment to 'ActorRecord *' from incompatible pointer type 'u8 *'",
                        "initialization of 'S *' from incompatible pointer type 'u8 *'",
                        "returning 'u8 *' from a function with incompatible return type 'S *'"):
            head = [self.sdk_finding('src/a.c', 'a', {'src/a.c:1:1': [self.arg(1, 'RotTransPers')],
                                                      'src/a.c:2:1': [message]})]
            code, out = self.gate([], head, root)
            self.assertEqual(code, 1, out)
            self.assertIn('not accepted', out)

    def test_non_sdk_callee_is_never_honoured(self):
        root = self.repo()
        self.stamped(root, [self.PTR + '\tsrc/a.c\ta\t1\t'])
        head = [self.sdk_finding('src/a.c', 'a', {'src/a.c:1:1': [self.arg(1, 'update_object_animation')]})]
        self.assertEqual(self.gate([], head, root)[0], 1)

    def test_pre_existing_other_sites_do_not_block_an_sdk_rise(self):
        root = self.repo()
        self.stamped(root, [self.PTR + '\tsrc/a.c\ta\t2\t'])
        assign = "assignment to 'S *' from incompatible pointer type 'u8 *'"
        base = [self.sdk_finding('src/a.c', 'a', {'src/a.c:5:1': [assign]})]
        head = [self.sdk_finding('src/a.c', 'a', {'src/a.c:6:1': [assign],              # shifted by an edit
                                                  'src/a.c:1:1': [self.arg(1, 'RotTransPers')]})]
        self.assertEqual(self.gate(base, head, root)[0], 0)
        old = dict(base[0]); old.pop('site_messages')                                   # a census without the column
        self.assertEqual(self.gate([old], head, root)[0], 0)

    def test_write_accepted_stamps_sdk_groups_and_drops_stale_rows(self):
        root = self.repo()
        (root / C.ACCEPTED).write_text(C.ACCEPTED_HEADER + '\n' + self.PTR + '\tsrc/z.c\tz\t4\t\n')  # no longer rises
        head = [self.sdk_finding('src/b.c', 'b', {'src/b.c:1:1': [self.arg(1, 'SetRotMatrix')]}),
                self.sdk_finding('src/c.c', 'c', {'src/c.c:1:1': ["assignment to 'S *' from incompatible pointer type 'u8 *'"]}),
                finding('src/b.c', 'b', '-Wshadow', ['src/b.c:2:1'])]
        with redirect_stdout(io.StringIO()):
            self.assertEqual(C.report([], head, [], [], {}, 0, write_root=root, base='HEAD', sdk=self.SDK), 1)
        rows = (root / C.ACCEPTED).read_text().splitlines()
        self.assertIn(self.PTR + '\tsrc/b.c\tb\t1\tSetRotMatrix', rows)
        self.assertFalse(any('src/c.c' in r or 'src/z.c' in r for r in rows), rows)
        self.assertEqual(C.accepted_rows(root, 'HEAD'), ({('src/b.c', 'b', self.PTR): 1}, []))
        self.assertEqual(self.gate([], head[:1], root)[0], 0)

    def test_row_rekeyed_to_a_recorded_rename_is_carried_not_added(self):
        text = '# old\n' + C.ACCEPTED_HEADER + '\n' + self.PTR + '\tsrc/old.c\told_name\t2\tStoreImage\n'
        root = self.repo(text)
        rekeyed = text.replace('src/old.c\told_name', 'src/new.c\tnew_name')
        (root / C.ACCEPTED).write_text(rekeyed)
        names = {'old_name': {'0x80025ffc'}, 'new_name': {'0x80025ffc'}, 'other': {'0x80010000'}}
        renames = {'src/new.c': 'src/old.c'}
        self.assertEqual(C.accepted_rows(root, 'HEAD', names, renames), ({}, []))
        # without the rename record, an unrelated name, a file that git does not record renamed, or a raised
        # count, the new key is an added row and is refused
        self.assertEqual(len(C.accepted_rows(root, 'HEAD', dict(names, new_name={'0x80010004'}), renames)[1]), 1)
        (root / C.ACCEPTED).write_text(rekeyed.replace('\t2\t', '\t3\t'))
        self.assertEqual(len(C.accepted_rows(root, 'HEAD', names, renames)[1]), 1)
        # a row left behind by a file rename that landed before BASE (BASE has no src/old.c) carries too
        self.assertFalse((root / 'src/old.c').exists())
        (root / C.ACCEPTED).write_text(rekeyed)
        self.assertEqual(C.accepted_rows(root, 'HEAD', names, {}), ({}, []))
        (root / 'src').mkdir()
        (root / 'src/old.c').write_text('int x;\n')
        git(root, 'add', 'src/old.c'); git(root, 'commit', '-qm', 'old.c exists at BASE')
        (root / C.ACCEPTED).write_text(rekeyed)
        self.assertEqual(len(C.accepted_rows(root, 'HEAD', names, {})[1]), 1)
        # the old key still present: the new key is a second row, not a carry
        (root / C.ACCEPTED).write_text(text + self.PTR + '\tsrc/new.c\tnew_name\t1\t\n')
        self.assertEqual(len(C.accepted_rows(root, 'HEAD', names, renames)[1]), 1)
        # a carried row honours nothing: its group rising still fails
        (root / C.ACCEPTED).write_text(rekeyed)
        with patch.object(C, 'recorded_renames', return_value=names), \
                patch.object(C, 'accepted_renames', return_value=renames):
            rising = [self.sdk_finding('src/new.c', 'new_name', {'src/new.c:1:1': [self.arg(1, 'RotTransPers')]})]
            self.assertEqual(self.gate([], rising, root)[0], 1)
            self.assertEqual(self.gate([], [], root)[0], 0)
            # --write-accepted keeps the carried row (it is BASE's record), as it keeps BASE's own rows
            with redirect_stdout(io.StringIO()):
                C.report([], [], [], [], {}, 0, write_root=root, base='HEAD', sdk=self.SDK)
            self.assertIn(self.PTR + '\tsrc/new.c\tnew_name\t2\tStoreImage',
                          (root / C.ACCEPTED).read_text().splitlines())

    def test_sdk_functions_reads_include_sdk(self):
        root = self.repo()
        (root / 'include/sdk').mkdir(parents=True)
        (root / 'include/sdk/libgte.h').write_text('/* RotX(void); */\n#define setXY(p) ((p)->x = 0)\n'
                                                   'struct MATRIX * RotMatrix(struct SVECTOR *, struct MATRIX *);\n'
                                                   'typedef void (*Callback)(void);\n')
        self.assertEqual(C.sdk_functions(root), {'RotMatrix'})


class RecordedRenamePairTests(unittest.TestCase):
    """A small file renamed with its function changes too much for git -M; names.tsv pairs it."""

    def test_deleted_and_added_files_pair_through_one_address(self):
        tmp = tempfile.TemporaryDirectory()
        self.addCleanup(tmp.cleanup)
        root = Path(tmp.name)
        (root / 'config').mkdir()
        (root / 'src/a').mkdir(parents=True)
        (root / 'config/names.tsv').write_text(
            '0x80016530\tfunc_80016530\tget_value\tx\n0x80016530\tfunc_80016530\tset_flag_19\ty\n'
            '0x80016288\tfunc_80016288\tcount_down\tx\n0x80016288\tfunc_80016288\tset_flag_00\ty\n')
        (root / 'src/a/get_value_b.c').write_text('/* Calls f. */\ns32 get_value(void) { return f(19); }\n')
        (root / 'src/a/count_down_second.c').write_text('/* Calls g. */\ns32 count_down(void)\n{\n    return f(0);\n}\n')
        (root / 'src/a/keep.c').write_text('int keep(void) { return 0; }\n')
        git(root, 'init', '-q'); git(root, 'add', '-A'); git(root, 'commit', '-qm', 'base')
        git(root, 'mv', 'src/a/get_value_b.c', 'src/a/set_flag_19.c')
        git(root, 'mv', 'src/a/count_down_second.c', 'src/a/set_flag_00.c')
        (root / 'src/a/set_flag_19.c').write_text('/* Sets flag 19. */\ns32 set_flag_19(void) { return f(19); }\n')
        (root / 'src/a/set_flag_00.c').write_text('/* Sets flag 0. */\ns32 set_flag_00(void) { return f(0); }\n')
        (root / 'src/a/unrelated.c').write_text('int unrelated(void) { return 1; }\n')
        git(root, 'add', '-A'); git(root, 'commit', '-qm', 'renamed')
        rows = C.changes(root, 'HEAD~1', 'HEAD')
        self.assertIn(('R', 'src/a/get_value_b.c', 'src/a/set_flag_19.c'), rows)
        self.assertIn(('R', 'src/a/count_down_second.c', 'src/a/set_flag_00.c'), rows)
        self.assertIn(('A', None, 'src/a/unrelated.c'), rows)
        # two added files at the deleted function's address: ambiguous, left unpaired
        (root / 'config/names.tsv').write_text((root / 'config/names.tsv').read_text()
                                               + '0x80016530\tfunc_80016530\tunrelated\tz\n')
        git(root, 'add', '-A'); git(root, 'commit', '-qm', 'ambiguous')
        rows = C.changes(root, 'HEAD~2', 'HEAD')
        self.assertIn(('D', 'src/a/get_value_b.c', None), rows)
        self.assertIn(('R', 'src/a/count_down_second.c', 'src/a/set_flag_00.c'), rows)


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
        shifted = lambda path, line: line + 5                       # an edit above moved the function down
        with redirect_stdout(io.StringIO()):
            self.assertEqual(C.report(base, moved, [], [], {}, 0, names, shifted), 0)
        edited = lambda path, line: None                            # the site's own line was edited
        with redirect_stdout(io.StringIO()):
            self.assertEqual(C.report(base, moved, [], [], {}, 0, names, edited), 1)

    def test_two_renames_in_one_file_with_equal_site_counts_are_not_new(self):
        base = [finding('src/a.c', 'old_one', '-Wshadow', ['src/a.c:4:1']),
                finding('src/a.c', 'old_two', '-Wshadow', ['src/a.c:9:1'])]
        head = [finding('src/a.c', 'new_one', '-Wshadow', ['src/a.c:4:1']),
                finding('src/a.c', 'new_two', '-Wshadow', ['src/a.c:9:1'])]
        names = {'old_one': {'0x80024050'}, 'new_one': {'0x80024050'},
                 'old_two': {'0x80024100'}, 'new_two': {'0x80024100'}}
        with redirect_stdout(io.StringIO()) as out:
            self.assertEqual(C.report(base, head, [], [], {}, 0, names), 0)
        self.assertIn('renamed -Wshadow src/a.c old_one -> new_one', out.getvalue())
        self.assertIn('renamed -Wshadow src/a.c old_two -> new_two', out.getvalue())
        with redirect_stdout(io.StringIO()) as out:                 # without the rows both stay new, hinted
            self.assertEqual(C.report(base, head, [], [], {}, 0, {}), 1)
        self.assertIn('hint: possibly old_one or old_two renamed', out.getvalue())

    def test_recorded_renames_reads_base_rows(self):
        with tempfile.TemporaryDirectory() as tmp:
            root = Path(tmp)
            git(root, 'init', '-q')
            (root / 'config').mkdir()
            (root / 'config/names.tsv').write_text('0x80024050\tfunc_80024050\told_name\tboth images\n')
            git(root, 'add', '-A')
            git(root, 'commit', '-qm', 'base')
            (root / 'config/names.tsv').write_text('0x80024050\tfunc_80024050\tnew_name\tthis image\n')
            self.assertNotIn('old_name', C.recorded_renames(root))
            self.assertEqual(C.recorded_renames(root, 'HEAD')['old_name'], {'0x80024050'})
            self.assertEqual(C.recorded_renames(root, 'HEAD')['new_name'], {'0x80024050'})

    def test_rename_in_renamed_file_is_not_new(self):
        base = [finding('src/old.c', 'old_name', '-Wshadow', ['src/old.c:4:1'])]
        head = [finding('src/new.c', 'new_name', '-Wshadow', ['src/new.c:7:1'])]
        names = {'old_name': {'0x80024050'}, 'new_name': {'0x80024050'}}
        renames = {'src/new.c': 'src/old.c'}
        shifted = lambda path, line: line + 3 if path == 'src/new.c' else None
        with redirect_stdout(io.StringIO()) as out:
            self.assertEqual(C.report(base, head, [], [], renames, 0, names, shifted), 0)
        self.assertIn('renamed -Wshadow src/new.c old_name -> new_name', out.getvalue())
        with redirect_stdout(io.StringIO()):                        # without the file rename the group is new
            self.assertEqual(C.report(base, head, [], [], {}, 0, names, shifted), 1)

    def test_diff_line_map_follows_a_renamed_file(self):
        with tempfile.TemporaryDirectory() as tmp:
            root = Path(tmp)
            git(root, 'init', '-q')
            (root / 'src').mkdir()
            (root / 'src/old.c').write_text(''.join(f'line{i}\n' for i in range(1, 11)))
            git(root, 'add', '-A')
            git(root, 'commit', '-qm', 'base')
            git(root, 'mv', 'src/old.c', 'src/new.c')
            text = (root / 'src/new.c').read_text().replace('line2\n', 'a\nb\nc\n')
            (root / 'src/new.c').write_text(text)
            line_map = C.diff_line_map(root, 'HEAD', {'src/new.c': 'src/old.c'})
            self.assertEqual(line_map('src/new.c', 5), 7)
            self.assertIsNone(line_map('src/new.c', 2))

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
