"""ledger_integrity: union ledger loads, retired_to_cast sites and their re-derivation.

    python3 -m unittest tools.lint.test_ledger_integrity
"""
from contextlib import redirect_stdout
import io
import json
import os
from pathlib import Path
import subprocess
import sys
import tempfile
import unittest

HERE = Path(__file__).resolve().parent
sys.path.insert(0, str(HERE))
import ledger_integrity as I  # noqa: E402


def git(root, *args):
    env = dict(os.environ, GIT_AUTHOR_NAME='t', GIT_AUTHOR_EMAIL='t@invalid',
               GIT_COMMITTER_NAME='t', GIT_COMMITTER_EMAIL='t@invalid')
    return subprocess.run(['git', *args], cwd=root, env=env, check=True,
                          capture_output=True, text=True).stdout.strip()


def loads(**members):
    zero = dict(lb=0, lbu=0, lh=0, lhu=0, lw=0, sb=0, sh=0, sw=0, unmapped=0)
    return {name: dict(zero, **counts) for name, counts in members.items()}


def row(rid, sites=(), status='retired', path='f', member_loads=None):
    return dict(id=rid, status=status, path=path, members=[dict(name='s', type='s16'), dict(name='u', type='u16')],
                retired_to_cast=list(sites), loads=member_loads or loads(s={}, u={}))


class ParseTests(unittest.TestCase):
    def test_forms(self):
        p = I.parse_entry('src/a.c:12 (s16)')
        self.assertEqual((p['kind'], p['line'], p['second'], p['cast']), ('site', 12, None, '(s16)'))
        p = I.parse_entry('src/a.c:289,291 *(u8 *)& width casts of x and y')
        self.assertEqual((p['line'], p['second'], I.squash(p['cast'])), (289, 291, '*(u8*)&'))
        p = I.parse_entry('src/a.c:226,3 (u16)')
        self.assertEqual((p['second'], p['extra']), (None, 3))
        self.assertEqual(I.parse_entry('src/a.c:9 (S_8017_0 *)')['cast'], '(S_8017_0 *)')
        self.assertEqual(I.parse_entry('src/a.c:9 (u8 *)&effect->x')['cast'], '(u8 *)')
        self.assertEqual(I.parse_entry('src/a.c (former member sites)')['kind'], 'note')
        self.assertEqual(I.parse_entry('src/a.c (u16) (cast gone)')['kind'], 'note')
        self.assertEqual(I.parse_entry('src/a.c:46')['kind'], 'nocast')
        p = I.parse_entry(dict(site='src/a.c:5', cast='(Handler)run', to='handler'))
        self.assertEqual((p['kind'], p['line'], p['cast']), ('site', 5, '(Handler)'))

    def test_cast_fields(self):
        self.assertEqual(I.cast_fields('x = (s16)p->a + (s16)q.b;', '(s16)'), {'a', 'b'})
        self.assertEqual(I.cast_fields('((S_1 *)p)->unk_96 = 0;', '(S_1*)'), {'unk_96'})


class SiteTests(unittest.TestCase):
    def setUp(self):
        self.tmp = tempfile.TemporaryDirectory()
        self.addCleanup(self.tmp.cleanup)
        self.root = Path(self.tmp.name)
        (self.root / 'src').mkdir()
        (self.root / 'src/a.c').write_text('int a;\nx = (s16)p->f;\ny = *(u8 *)&p->g;\nz = *(u8 *)&p->h;\n')
        self.texts = I.Texts(self.root)

    def test_check_entry(self):
        check = lambda e: I.check_entry(e, self.texts)  # noqa: E731
        self.assertEqual(check('src/a.c:2 (s16)'), 'ok')
        self.assertEqual(check('src/a.c:2 ( s16 ) value cast'), 'ok')
        self.assertEqual(check('src/a.c:1 (s16)'), 'stale')
        self.assertEqual(check('src/a.c:9 (s16)'), 'noline')
        self.assertEqual(check('src/b.c:1 (s16)'), 'nofile')
        self.assertEqual(check('src/a.c:3,4 *(u8 *)& both'), 'ok')
        self.assertEqual(check('src/a.c:2,4 *(u8 *)& both'), 'stale')     # second line checked too
        self.assertEqual(check('src/a.c:2,1 (s16)'), 'ok')                # small n is a count
        self.assertEqual(check('src/a.c:4'), 'ok')
        self.assertEqual(check('src/a.c (former member sites)'), 'note')


class LoadsTests(unittest.TestCase):
    def test_zeroed_rows_and_count_drop_fail(self):
        base = [row('a', member_loads=loads(s=dict(lh=3), u=dict(lhu=1))), row('b')]
        head = [row('a'), row('b')]                      # the AC131 B2 shape: regenerated all-zero
        result = I.check_loads(base, head)
        self.assertEqual(result['zeroed'], ['a'])
        self.assertEqual(len(result['problems']), 2)

    def test_missing_loads_key_counts_as_zero(self):
        base = [dict(id='a', status='retired')]
        head = [row('a', member_loads=loads(s=dict(lh=2)))]
        self.assertEqual(I.check_loads(base, head)['problems'], [])

    def test_weak_evidence_counts_loads_not_stores(self):
        rows = [row('a', member_loads=loads(s=dict(lh=1, sh=9))),
                row('b', member_loads=loads(s=dict(lh=4), u=dict(lhu=3))),
                row('c', member_loads=loads(s=dict(lh=2), u=dict(lhu=2))),
                row('d'), row('e', status='unproven', member_loads=loads(s=dict(lh=1)))]
        weak = I.weak_evidence(rows, [row('c')])
        self.assertEqual(weak['all'], dict(rows=3, under5=2, one=1))
        self.assertEqual(weak['no_load_data'], 1)
        self.assertEqual(weak['newly_retired'], dict(rows=2, under5=1, one=1))


class RepoTests(unittest.TestCase):
    """BASE/HEAD comparisons and re-derivation through the file's history."""

    def setUp(self):
        self.tmp = tempfile.TemporaryDirectory()
        self.addCleanup(self.tmp.cleanup)
        root = self.root = Path(self.tmp.name)
        (root / 'src').mkdir()
        (root / 'ledger').mkdir()
        self.source = root / 'src/a.c'
        self.source.write_text('void f(S *p)\n{\n    x = (s16)p->f;\n    y = (u16)p->g;\n}\n')
        rows = [row('r1', ['src/a.c:3 (s16)'], path='f'),
                row('r2', ['src/a.c:4 (u16)', 'src/a.c:1 (u16) stale already'], path='g')]
        self.write(rows)
        git(root, 'init', '-q')
        git(root, 'add', '-A')
        git(root, 'commit', '-qm', 'base')

    def write(self, rows):
        (self.root / I.LEDGER).write_text(''.join(json.dumps(r, sort_keys=True) + '\n' for r in rows))

    def run_main(self, *args):
        with redirect_stdout(io.StringIO()) as out:
            code = I.main(['HEAD', '--root', str(self.root), *args])
        return code, out.getvalue()

    def test_fail_new_ignores_entries_already_stale_on_base(self):
        self.source.write_text('/* moved */\n' + self.source.read_text())
        code, out = self.run_main('--fail-new')
        self.assertEqual(code, 1)
        self.assertIn('NEW STALE r1: src/a.c:3 (s16)', out)
        self.assertNotIn('stale already', out)
        code, out = self.run_main('--fail-all')
        self.assertIn('stale already', out)
        self.assertEqual(self.run_main()[0], 0)          # report-only by default

    def test_loads_regression_always_fails(self):
        rows = [row('r1', ['src/a.c:3 (s16)'], path='f', member_loads=loads(s=dict(lh=2)))]
        self.write(rows)
        git(self.root, 'commit', '-qam', 'loads')
        self.write([row('r1', ['src/a.c:3 (s16)'], path='f')])
        code, out = self.run_main()
        self.assertEqual(code, 1)
        self.assertIn('LOADS loads zeroed: r1', out)

    def test_rederive_follows_history_and_marks_gone(self):
        self.source.write_text('/* header */\n#include "x.h"\n' +
                               self.source.read_text().replace('    y = (u16)p->g;\n', '    y = p->g;\n'))
        git(self.root, 'commit', '-qam', 'edit')
        code, out = self.run_main('--rederive', '--write')
        self.assertEqual(code, 0, out)
        rows = I.read_ledger((self.root / I.LEDGER).read_text())
        self.assertEqual(rows[0]['retired_to_cast'], ['src/a.c:5 (s16)'])
        self.assertEqual(rows[1]['retired_to_cast'][0], 'src/a.c (u16) (cast gone)')
        self.assertIn('history', out)
        self.assertEqual(self.run_main('--fail-all')[0], 0)

    def test_rederive_without_history_needs_the_rows_field(self):
        self.source.write_text('void f(S *p)\n{\n    w = (u16)p->other;\n    x = (s16)p->f;\n    y = (u16)p->g;\n}\n')
        rows = [row('r2', ['src/a.c:2 (u16) branch line'], path='g')]   # never true on any commit
        self.write(rows)
        self.run_main('--rederive', '--write')
        rows = I.read_ledger((self.root / I.LEDGER).read_text())
        self.assertEqual(rows[0]['retired_to_cast'], ['src/a.c:5 (u16) branch line'])

    def test_duplicates_share_a_line_and_status_is_untouched(self):
        self.source.write_text('\n\n' + self.source.read_text())
        rows = [row('r1', ['src/a.c:3 (s16)', 'src/a.c:3 (s16)'], path='f')]
        rows[0]['evidence'] = 'prose stays'
        self.write(rows)
        self.run_main('--rederive', '--write')
        out = I.read_ledger((self.root / I.LEDGER).read_text())[0]
        self.assertEqual(out['retired_to_cast'], ['src/a.c:5 (s16)', 'src/a.c:5 (s16)'])
        self.assertEqual((out['status'], out['evidence']), ('retired', 'prose stays'))


if __name__ == '__main__':
    unittest.main()
