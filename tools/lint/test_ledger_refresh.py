"""ledger_refresh: stored paths, lines, callers, names and spellings re-derived after renames.

    python3 -m unittest tools.lint.test_ledger_refresh
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
import ledger_refresh as R  # noqa: E402

HEADER = '# names\n'
STAMP = '# BASE copy sha256: none (written by --write-accepted)\n'


def git(root, *args):
    env = dict(os.environ, GIT_AUTHOR_NAME='t', GIT_AUTHOR_EMAIL='t@invalid',
               GIT_COMMITTER_NAME='t', GIT_COMMITTER_EMAIL='t@invalid')
    return subprocess.run(['git', *args], cwd=root, env=env, check=True, capture_output=True, text=True).stdout


def names_text(rows):
    return HEADER + ''.join('\t'.join(row) + '\n' for row in rows)


def fn(name, body='    helper();\n'):
    return f'void {name}(void)\n{{\n{body}}}\n'


class Fixture(unittest.TestCase):
    """BASE: old_fn in src/town/old_fn.c, a caller, ledgers citing both.  HEAD: old_fn renamed new_fn and its
    file renamed after it (git mv), a per-image split and a merged file; the ledgers are left as BASE wrote them."""

    def setUp(self):
        self.tmp = tempfile.TemporaryDirectory()
        self.root = Path(self.tmp.name)
        git(self.root, 'init', '-q')
        self.write('src/town/old_fn.c', '#include "common.h"\n\n' + fn('old_fn'))
        self.write('src/town/caller.c', '#include "common.h"\n\nvoid caller(void)\n{\n    old_fn();\n    x();\n'
                   '    old_fn();\n}\n')
        self.write('src/town/twin.c', fn('shared_name'))
        self.write('src/dungeon/twin.c', fn('shared_name'))
        self.write('src/dungeon/piece_a.c', fn('piece_a'))
        self.write('src/dungeon/piece_b.c', fn('piece_b'))
        self.write('include/town/old.h', 'void old_fn(void);\n')
        self.write('config/names.tsv', names_text([
            ('0x80010000', 'func_80010000', 'old_fn', 'src/town/old_fn.c:4: calls helper'),
            ('0x80010100', 'func_80010100', 'caller', 'src/town/caller.c: calls old_fn twice (old_fn at '
             'src/town/old_fn.c:3-5)'),
            ('0x80020000', 'func_80020000', 'shared_name', 'src/town/twin.c: one name, two images'),
            ('0x80030000', 'func_80030000', 'piece_a', 'src/dungeon/piece_a.c: a piece'),
            ('0x80030100', 'func_80030100', 'piece_b', 'src/dungeon/piece_b.c: another piece'),
        ]))
        self.ledgers()
        git(self.root, 'add', '-A')
        git(self.root, 'commit', '-qm', 'base')
        self.base = git(self.root, 'rev-parse', 'HEAD').strip()
        # HEAD: rename old_fn -> new_fn with its file; split shared_name per image; merge the two pieces.
        git(self.root, 'mv', 'src/town/old_fn.c', 'src/town/new_fn.c')
        self.write('src/town/new_fn.c', '#include "common.h"\n\n' + fn('new_fn'))
        self.write('src/town/caller.c', '#include "common.h"\n\n/* comment */\nvoid caller(void)\n{\n    new_fn();\n'
                   '    x();\n    new_fn();\n}\n')
        self.write('include/town/old.h', 'void new_fn(void);\n')
        self.write('src/town/twin.c', fn('town_twin'))
        self.write('src/dungeon/twin.c', fn('dungeon_twin'))
        git(self.root, 'rm', '-q', 'src/dungeon/piece_a.c', 'src/dungeon/piece_b.c')
        self.write('src/dungeon/pieces.c', fn('piece_a') + '\n' + fn('piece_b'))
        self.write('config/names.tsv', names_text([
            ('0x80010000', 'func_80010000', 'new_fn', 'src/town/new_fn.c:4: calls helper (renamed from old_fn)'),
            ('0x80010100', 'func_80010100', 'caller', 'src/town/caller.c: calls old_fn twice (old_fn at '
             'src/town/old_fn.c:3-5)'),
            ('0x80020000', 'func_80020000', 'town_twin', 'src/town/twin.c: the town one; previously shared_name'),
            ('0x80020000', 'func_80020000', 'dungeon_twin', 'src/dungeon/twin.c: the dungeon one'),
            ('0x80030000', 'func_80030000', 'piece_a', 'src/dungeon/piece_a.c: a piece'),
            ('0x80030100', 'func_80030100', 'piece_b', 'src/dungeon/piece_b.c: another piece'),
        ]))
        git(self.root, 'add', '-A')
        git(self.root, 'commit', '-qm', 'head')

    def tearDown(self):
        self.tmp.cleanup()

    def write(self, rel, text):
        path = self.root / rel
        path.parent.mkdir(parents=True, exist_ok=True)
        path.write_text(text)

    def read(self, rel):
        return (self.root / rel).read_text()

    def jsonl(self, rel):
        return [json.loads(line) for line in self.read(rel).splitlines() if line.strip()]

    def ledgers(self):
        floor = dict(name='old_fn', definition=dict(path='src/town/old_fn.c', proto='void old_fn(void);'),
                     blocking=[dict(declaration='include/town/old.h', path='include/town/old.h',
                                    spelling='void old_fn(void)')],
                     arity_evidence=[dict(args=0, caller='caller', line=5, path='src/town/caller.c'),
                                     dict(args=0, caller='caller', line=7, path='src/town/caller.c')])
        self.write(R.FLOORS, json.dumps(floor) + '\n')
        bridges = [dict(cast_text='(void *)p', evidence='e', file='src/town/old_fn.c', function='old_fn',
                        legacy_line='4', ordinal=1, reason='r', retired_by='x', status='retired',
                        site_id='src/town/old_fn.c::old_fn@0123456789ab'),
                   dict(cast_text='(void *)q', evidence='e', file='src/dungeon/twin.c', function='shared_name',
                        legacy_line='2', ordinal=1, reason='r', retired_by='x', status='retired',
                        site_id='src/dungeon/twin.c::shared_name@ba9876543210')]
        self.write(R.BRIDGES, ''.join(json.dumps(b, sort_keys=True) + '\n' for b in bridges))
        self.write(R.ACCEPTED, '# accepted\n' + STAMP + 'warning\tfile\tfunction\tsites\tcallees\n'
                   '-Wincompatible-pointer-types\tsrc/town/old_fn.c\told_fn\t1\told_fn\n')
        self.write(R.PROTO_BASELINE, json.dumps(dict(candidate_sites=[
            'old_fn::src/town/old_fn.c::include/town/old.h::arity']), indent=2) + '\n')
        self.write(R.IDENTITIES, json.dumps(dict(contract='void old_fn(void);', contract_file='include/town/old.h',
                                                 contract_symbol='old_fn', file='src/town/caller.c',
                                                 symbol='func_80010000'), sort_keys=True) + '\n')

    def refresh(self, *only, write=False, base=None):
        with redirect_stdout(io.StringIO()):
            return R.run(self.root, base=base, only=list(only) or None, write=write)


class NameTests(Fixture):
    def test_stale_name_resolves_through_the_recorded_rename(self):
        r, _ = self.refresh('names')
        self.assertTrue(r.names.stale('old_fn'))
        self.assertEqual(r.names.resolve('old_fn'), ('new_fn', None))
        self.assertFalse(r.names.stale('new_fn'))

    def test_old_name_that_now_means_two_functions_needs_a_cited_file(self):
        r, _ = self.refresh('names')
        name, reason = r.names.resolve('shared_name')
        self.assertIsNone(name)
        self.assertIn('several live names', reason)
        self.assertEqual(r.names.resolve('shared_name', ['src/dungeon/twin.c']), ('dungeon_twin', None))

    def test_names_evidence_paths_lines_and_names(self):
        self.refresh('names', write=True)
        rows = {cols[2]: cols[3] for cols in (l.split('\t') for l in self.read(R.NAMES).splitlines())
                if len(cols) == 4}
        # the range was old_fn's definition (respelled, so not an unchanged line): it moves onto new_fn's
        self.assertEqual(rows['caller'], 'src/town/caller.c: calls new_fn twice (new_fn at src/town/new_fn.c:3-5)')
        # the rename record and `previously X` keep the old name
        self.assertTrue(rows['new_fn'].endswith('(renamed from old_fn)'))
        self.assertTrue(rows['town_twin'].endswith('previously shared_name'))
        # a deleted file follows its functions into the one file that defines them now
        self.assertEqual(rows['piece_a'], 'src/dungeon/pieces.c: a piece')

    def test_moved_line_that_changed_is_dropped_not_guessed(self):
        r, _ = self.refresh('names')
        new, how, old = r.paths.resolve('src/town/old_fn.c')
        self.assertEqual((new, how), ('src/town/new_fn.c', 'git rename'))
        self.assertEqual(r.paths.map_line(old, new, 1), 1)      # `#include` line: unchanged
        self.assertIsNone(r.paths.map_line(old, new, 3))        # the definition line was respelled
        self.assertEqual(r.paths.map_definition(old, new, 3), [3])   # ... but it is old_fn's definition
        self.assertIsNone(r.paths.map_definition(old, new, 5))       # a body line is no definition
        self.write('src/town/new_fn.c', '#include "common.h"\n/* moved */\n\n' + fn('new_fn', '    other();\n'))
        r, _ = self.refresh('names')
        self.assertIsNone(r.paths.map_line(old, new, 5))        # respelled, not a definition: dropped
        self.assertEqual(r.paths.map_definition(old, new, 3, 5), [4, 6])


class InPlaceLineTests(Fixture):
    """--base: line citations of files that still exist follow the batch's own edits."""

    EDIT_BASE = ('#include "common.h"\n\nvoid edit_me(s32 a)\n{\n    helper();\n    other();\n}\n\n'
                 'void second(void)\n{\n    helper();\n}\n')
    EDIT_HEAD = ('#include "common.h"\n#include "town/new.h"\n\nvoid edit_me(void *a)\n{\n    helper();\n'
                 '    changed();\n}\n\nvoid second(void)\n{\n    helper();\n}\n')

    def rows(self, second, third, fourth):
        return [
            ('0x80040400', 'func_80040400', 'fourth', fourth),
            ('0x80040000', 'func_80040000', 'edit_me', 'src/town/edit.c:3-7 defines it; helper at src/town/edit.c:5'),
            ('0x80040100', 'func_80040100', 'second', second),
            ('0x80040200', 'func_80040200', 'third', third),
            ('0x80040300', 'func_80040300', 'new_fn_alias',
             'src/town/new_fn.c: the alias (renamed from old_fn, earlier older_fn)'),
        ]

    def setUp(self):
        super().setUp()
        self.head_rows = self.read(R.NAMES)
        self.write('src/town/edit.c', self.EDIT_BASE)
        self.write(R.NAMES, self.head_rows + ''.join('\t'.join(row) + '\n' for row in self.rows(
            'src/town/edit.c:6 calls other; src/town/edit.c:9 is it', 'src/town/edit.c:5 and src/town/twin.c:1',
            'src/town/old_fn.c:4 opens it')))
        git(self.root, 'add', '-A')
        git(self.root, 'commit', '-qm', 'batch start')
        self.start = git(self.root, 'rev-parse', 'HEAD').strip()
        # the batch: edits edit.c in place (an include, a respelled definition, an edited body line); one row
        # was already rewritten against the new text (third's first citation); a refresh at the batch start
        # moved fourth's citation of a file renamed before it onto the renamed file's text at the start, and
        # then the batch edited that file too
        self.write('src/town/edit.c', self.EDIT_HEAD)
        self.write('src/town/new_fn.c', '/* the batch */\n' + self.read('src/town/new_fn.c'))
        self.write(R.NAMES, self.head_rows + ''.join('\t'.join(row) + '\n' for row in self.rows(
            'src/town/edit.c:6 calls other; src/town/edit.c:9 is it', 'src/town/edit.c:6 and src/town/twin.c:1',
            'src/town/new_fn.c:4 opens it')))

    def evidence(self):
        return {cols[2]: cols[3] for cols in (l.split('\t') for l in self.read(R.NAMES).splitlines())
                if len(cols) == 4}

    def test_lines_follow_the_line_diff_of_an_edited_file(self):
        self.refresh('names', write=True, base=self.start)
        rows = self.evidence()
        # a respelled definition line moves onto the definition's span; an unchanged line follows the diff
        self.assertEqual(rows['edit_me'], 'src/town/edit.c:4-8 defines it; helper at src/town/edit.c:6')
        # an edited body line is dropped (the path kept), the definition line of `second` follows the diff
        self.assertEqual(rows['second'], 'src/town/edit.c calls other; src/town/edit.c:10 is it')
        # a citation the batch already rewrote is left alone; an unchanged file keeps its lines
        self.assertEqual(rows['third'], 'src/town/edit.c:6 and src/town/twin.c:1')
        # a citation a refresh wrote against the batch start's text follows the batch's edits too
        self.assertEqual(rows['fourth'], 'src/town/new_fn.c:5 opens it')

    def test_without_base_in_place_lines_are_not_carried(self):
        self.refresh('names', write=True)
        self.assertEqual(self.evidence()['second'], 'src/town/edit.c:6 calls other; src/town/edit.c:9 is it')

    def test_several_name_rename_record_is_frozen(self):
        self.refresh('names', write=True, base=self.start)
        self.assertEqual(self.evidence()['new_fn_alias'],
                         'src/town/new_fn.c: the alias (renamed from old_fn, earlier older_fn)')
        r, _ = self.refresh('names', base=self.start)
        self.assertEqual(r.names.resolve('older_fn'), ('new_fn_alias', None))

    def test_write_is_a_fixpoint_after_the_commit(self):
        args = ['--root', str(self.root), '--only', 'names', '--base', self.start]
        with redirect_stdout(io.StringIO()):
            self.assertEqual(R.main(args + ['--check']), 1)
            self.assertEqual(R.main(args + ['--write']), 0)
            self.assertEqual(R.main(args + ['--check']), 0)
            git(self.root, 'add', '-A')
            git(self.root, 'commit', '-qm', 'refresh')
            self.assertEqual(R.main(args + ['--check']), 0)


class LedgerTests(Fixture):
    def test_floor_name_definition_blocking_and_call_lines(self):
        self.refresh('floors', write=True)
        row = self.jsonl(R.FLOORS)[0]
        self.assertEqual(row['name'], 'new_fn')
        self.assertEqual(row['definition'], dict(path='src/town/new_fn.c', proto='void new_fn(void);'))
        self.assertEqual(row['blocking'][0]['spelling'], 'void new_fn(void)')
        self.assertEqual([e['line'] for e in row['arity_evidence']], [6, 8])

    def test_call_lines_are_not_guessed_when_the_counts_differ(self):
        self.write('src/town/caller.c', 'void caller(void)\n{\n    new_fn();\n}\n')
        r, _ = self.refresh('floors')
        self.assertTrue(any('1 calls of new_fn' in u[3] for u in r.unresolved))

    def test_moved_blocking_declaration_follows_its_spelling(self):
        self.write('include/town/moved.h', 'void new_fn(s32 a);\n')
        floor = dict(name='new_fn', definition=dict(path='src/town/new_fn.c', proto='void new_fn(void);'),
                     blocking=[dict(declaration='src/town/caller.c', path='src/town/caller.c', is_def=False,
                                    spelling='void new_fn(s32)'),
                               dict(declaration='src/town/caller.c', path='src/town/caller.c', is_def=False,
                                    spelling='s32 new_fn(char *)')])
        self.write(R.FLOORS, json.dumps(floor) + '\n')
        r, _ = self.refresh('floors', write=True)
        blocking = self.jsonl(R.FLOORS)[0]['blocking']
        self.assertEqual((blocking[0]['declaration'], blocking[0]['path']), ('include/town/moved.h', 'src/town/caller.c'))
        self.assertEqual(blocking[1]['declaration'], 'src/town/caller.c')
        self.assertTrue(any('no file declares this spelling' in u[3] for u in r.unresolved))

    def test_several_declaring_files_narrow_to_the_one_the_unit_includes(self):
        self.write('include/town/a.h', 'void new_fn(s32 a);\n')
        self.write('include/town/b.h', 'void new_fn(s32 b);\n')
        self.write('src/town/caller.c', '#include "town/b.h"\n' + self.read('src/town/caller.c'))
        floor = dict(name='new_fn', blocking=[dict(declaration='src/town/gone.c', path='src/town/caller.c',
                                                   is_def=False, spelling='void new_fn(s32)')])
        self.write(R.FLOORS, json.dumps(floor) + '\n')
        self.refresh('floors', write=True)
        self.assertEqual(self.jsonl(R.FLOORS)[0]['blocking'][0]['declaration'], 'include/town/b.h')

    def test_bridge_site_id_follows_and_legacy_line_is_frozen(self):
        self.refresh('bridges', write=True)
        rows = self.jsonl(R.BRIDGES)
        self.assertEqual((rows[0]['file'], rows[0]['function'], rows[0]['site_id'], rows[0]['legacy_line']),
                         ('src/town/new_fn.c', 'new_fn', 'src/town/new_fn.c::new_fn@0123456789ab', '4'))
        # per-image: the live name the dungeon file does not define becomes the address's dungeon name
        self.assertEqual((rows[1]['function'], rows[1]['site_id']),
                         ('dungeon_twin', 'src/dungeon/twin.c::dungeon_twin@ba9876543210'))

    def test_accepted_rows_keep_the_stamp(self):
        self.refresh('accepted', write=True)
        text = self.read(R.ACCEPTED)
        self.assertIn(STAMP, text)
        self.assertIn('-Wincompatible-pointer-types\tsrc/town/new_fn.c\tnew_fn\t1\tnew_fn\n', text)

    def test_baselines_and_identities(self):
        self.refresh('proto', 'identities', write=True)
        self.assertEqual(json.loads(self.read(R.PROTO_BASELINE))['candidate_sites'],
                         ['new_fn::src/town/new_fn.c::include/town/old.h::arity'])
        row = self.jsonl(R.IDENTITIES)[0]
        self.assertEqual((row['contract'], row['contract_symbol'], row['symbol']),
                         ('void new_fn(void);', 'new_fn', 'func_80010000'))

    def test_unchanged_rows_keep_their_bytes(self):
        extra = '{"b": 1, "a": "src/town/caller.c"}'
        self.write(R.BRIDGES, self.read(R.BRIDGES) + extra + '\n')
        self.refresh('bridges', write=True)
        self.assertTrue(self.read(R.BRIDGES).endswith(extra + '\n'))

    def test_check_exit_code_and_idempotence(self):
        with redirect_stdout(io.StringIO()):
            self.assertEqual(R.main(['--root', str(self.root), '--check', '--only',
                                     'names,floors,bridges,accepted,proto,identities']), 1)
            self.assertEqual(R.main(['--root', str(self.root), '--write', '--only',
                                     'names,floors,bridges,accepted,proto,identities']), 0)
            self.assertEqual(R.main(['--root', str(self.root), '--check', '--only',
                                     'names,floors,bridges,accepted,proto,identities']), 0)


class DataFileTests(Fixture):
    def test_deleted_data_file_follows_its_tables_in_the_same_commit(self):
        self.write('src/town/tables.c', 'static u32 town_table[2] = { 1, 2 };\nu8 *town_cursor = 0;\n')
        git(self.root, 'add', '-A')
        git(self.root, 'commit', '-qm', 'tables')
        git(self.root, 'rm', '-q', 'src/town/tables.c')
        self.write('src/town/caller.c', self.read('src/town/caller.c') +
                   '\nstatic u32 town_table[2] = { 1, 2 };\nu8 *town_cursor = 0;\n')
        git(self.root, 'add', '-A')
        git(self.root, 'commit', '-qm', 'fold tables')
        r, _ = self.refresh('names')
        self.assertEqual(r.paths.resolve('src/town/tables.c')[:2], ('src/town/caller.c', 'its data moved'))


class DebtTests(Fixture):
    def test_dead_rows_drop_with_their_class_counts_and_renamed_rows_move(self):
        import debt_check as D
        row = lambda n: [10, {'<global>': [10, n]}]                       # one local extern each
        record = dict(schema_version=D.SCHEMA, classes=list(D.CLASSES),
                      by_class=dict(dict.fromkeys(D.CLASSES, 0), local_externs=6),
                      by_file={'src/town': {'old_fn.c': row(1), 'caller.c': row(2)},
                               'src/dungeon': {'piece_a.c': row(3)}},
                      bad_label_sites=[])
        self.write(R.DEBT, D.baseline_text(record))
        self.refresh('debt', write=True)
        data = json.loads(self.read(R.DEBT))
        self.assertEqual(data['by_file'], {'src/town': {'caller.c': row(2), 'new_fn.c': row(1)}})
        self.assertEqual(data['by_class']['local_externs'], 3)
        D.validate_baseline(data)


class UnionTests(Fixture):
    def test_union_id_moves_with_its_header_everywhere(self):
        self.write('include/town/old_view.h', 'typedef union { s16 s; u16 u; } V;\n')
        rid = 'include/town/old_view.h::V.x'
        self.write(R.UNIONS, json.dumps(dict(id=rid, file='include/town/old_view.h', owner='V', path='x',
                                             retired_to_cast=[], example_sites={'s': ['src/town/old_fn.c:4']},
                                             evidence='read by old_fn'), sort_keys=True) + '\n')
        self.write(R.UNION_BASELINE, json.dumps(dict(count=1, ids=[rid], reason='r', schema=1), indent=1) + '\n')
        git(self.root, 'add', '-A')
        git(self.root, 'commit', '-qm', 'union')
        git(self.root, 'mv', 'include/town/old_view.h', 'include/town/view.h')
        git(self.root, 'commit', '-qm', 'rename header')
        self.refresh('unions', write=True)
        row = self.jsonl(R.UNIONS)[0]
        self.assertEqual((row['id'], row['file'], row['owner'], row['path']),
                         ('include/town/view.h::V.x', 'include/town/view.h', 'V', 'x'))
        self.assertEqual(row['example_sites'], {'s': ['src/town/new_fn.c:4']})    # `{`: an unchanged line
        self.assertEqual(row['evidence'], 'read by new_fn')
        self.assertEqual(json.loads(self.read(R.UNION_BASELINE))['ids'], ['include/town/view.h::V.x'])


class UnionCastTests(Fixture):
    """--base: retired_to_cast entries follow their cast inside the function that held it at the batch start."""

    BASE = ('#include "common.h"\n\nvoid walk(Half *h, Spell *s)\n{\n    s->a = (u16)h[0] + 1;\n'
            '    s->b = (u16)h[1];\n    s->c = (u16)h[2];\n    s->d = (s16)h[3];\n}\n')

    def row(self, entries):
        return json.dumps(dict(id='include/town/half.h::Half.x', file='include/town/half.h', owner='Half', path='x',
                               retired_to_cast=entries, evidence='e'), sort_keys=True) + '\n'

    def start(self, entries, head):
        self.write('include/town/half.h', 'typedef s16 Half;\n')
        self.write('src/town/walk.c', self.BASE)
        self.write(R.UNIONS, self.row(entries))
        git(self.root, 'add', '-A')
        git(self.root, 'commit', '-qm', 'batch start')
        base = git(self.root, 'rev-parse', 'HEAD').strip()
        self.write('src/town/walk.c', head)
        git(self.root, 'add', '-A')
        git(self.root, 'commit', '-qm', 'batch')
        return base

    def casts(self, base):
        self.refresh('unions', write=True, base=base)
        return self.jsonl(R.UNIONS)[0]['retired_to_cast']

    def test_cast_moved_one_line_follows(self):
        base = self.start(['src/town/walk.c:8 (s16)'],
                          self.BASE.replace('#include "common.h"\n', '#include "common.h"\n#include "town/half.h"\n'))
        self.assertEqual(self.casts(base), ['src/town/walk.c:9 (s16)'])

    def test_several_identical_casts_pair_in_order(self):
        # every (u16) line moves down one; the line an old number now names still holds a (u16), so a check of the
        # cited line alone would keep the wrong one
        base = self.start(['src/town/walk.c:5 (u16)', 'src/town/walk.c:6 (u16)', 'src/town/walk.c:7 (u16)'],
                          self.BASE.replace('#include "common.h"\n', '#include "common.h"\n#include "town/half.h"\n'))
        self.assertEqual(self.casts(base), ['src/town/walk.c:6 (u16)', 'src/town/walk.c:7 (u16)',
                                            'src/town/walk.c:8 (u16)'])

    def test_cast_really_gone_is_marked(self):
        base = self.start(['src/town/walk.c:6 (u16)', 'src/town/walk.c:8 (s16)'],
                          self.BASE.replace('(s16)h[3]', 'h[3]'))
        self.assertEqual(self.casts(base), ['src/town/walk.c:6 (u16)', 'src/town/walk.c (s16) (cast gone)'])

    def test_carry_is_a_fixpoint_after_the_commit(self):
        base = self.start(['src/town/walk.c:6 (u16)'],
                          self.BASE.replace('#include "common.h"\n', '#include "common.h"\n\n'))
        args = ['--root', str(self.root), '--only', 'unions', '--base', base]
        with redirect_stdout(io.StringIO()):
            self.assertEqual(R.main(args + ['--check']), 1)
            self.assertEqual(R.main(args + ['--write']), 0)
            git(self.root, 'add', '-A')
            git(self.root, 'commit', '-qm', 'refresh')
            self.assertEqual(R.main(args + ['--check']), 0)
        self.assertEqual(self.jsonl(R.UNIONS)[0]['retired_to_cast'], ['src/town/walk.c:7 (u16)'])


class NoHistoryTests(Fixture):
    def test_head_table_only(self):
        r = R.Refresher(self.root, history=False)
        self.assertFalse(r.names.history)
        self.assertEqual(r.names.resolve('old_fn'), ('new_fn', None))      # from `(renamed from old_fn)`
        self.assertEqual(r.paths.resolve('src/town/old_fn.c')[0], None)


if __name__ == '__main__':
    unittest.main()
