"""Tests for tools/lint/ledger_rekey.py: one test group per ledger grammar, collisions, --check, atomic writes."""
import contextlib
import io
import json
import os
import subprocess
import sys
import tempfile
import unittest
from pathlib import Path
from unittest.mock import patch

HERE = Path(__file__).resolve().parent
sys.path.insert(0, str(HERE))
sys.path.insert(0, str(HERE.parent))
import atomic_io  # noqa: E402
import ledger_rekey as K  # noqa: E402

MEMBER_ROWS = 'record\theader\told_member\tnew_member\toffset\tstatus\n' \
              'Rec\tinclude/h.h\tunk_04\tstate\t0x4\trenamed\n' \
              'Rec\tinclude/h.h\tunk_08\tmode\t0x8\tskipped\n'
SYMBOL_ROWS = 'id\told_name\tnew_name\tscope_files\tmode\n' \
              'R1\tfunc_80001000\tspawn_thing\t\tspelling_func\n' \
              'D1\tshared_old\tper_image_new\tsrc/b.c\tper_image\n'


def dump(row):
    return json.dumps(row, sort_keys=True)


class Base(unittest.TestCase):
    def setUp(self):
        self._td = tempfile.TemporaryDirectory()
        self.root = Path(self._td.name)
        for d in ('src', 'include', 'ledger', 'tools/lint'):
            (self.root / d).mkdir(parents=True)

    def tearDown(self):
        self._td.cleanup()

    def put(self, rel, text):
        path = self.root / rel
        path.parent.mkdir(parents=True, exist_ok=True)
        path.write_text(text)
        return path

    def tables(self, members=MEMBER_ROWS, symbols=SYMBOL_ROWS):
        m = self.put('members.tsv', members)
        s = self.put('symbols.tsv', symbols)
        return K.Tables(K.read_members(m), K.read_symbols(s))

    def run_rekey(self, tables=None, base=None, only=None):
        rk = K.Rekey(self.root, tables or self.tables(), base, only)
        rk.run()
        return rk

    def baseline(self, by_file=None, bad=()):
        import debt_check as D
        record = {'by_class': {k: 0 for k in D.CLASSES}, 'by_file': by_file or {}, 'classes': list(D.CLASSES),
                  'bad_label_sites': list(bad), 'schema_version': D.SCHEMA}
        for directory in record['by_file'].values():
            for packed in directory.values():
                for row in packed[1].values():
                    for cls, n in zip(D.CLASSES, row[1:]):
                        record['by_class'][cls] += n
        self.put('tools/lint/debt_baseline.json', D.baseline_text(record))


class Tables(Base):
    def test_member_rows_keep_only_renamed_status(self):
        t = self.tables()
        self.assertEqual([(m.record, m.old, m.new, m.offset) for m in t.members], [('Rec', 'unk_04', 'state', 4)])

    def test_member_pack_row_format_follows_the_batch_tool_skip_rules(self):
        path = self.put('pack.tsv', 'record\theader\toffset\tmember\tkind\ttype\tnew_member\taction\tconfidence\n')
        # columns the pack uses: old name from `old_member`/`old`; this one has none -> refused loudly
        with self.assertRaises(SystemExit):
            K.read_members(path)
        path = self.put('pack.tsv', 'record\theader\told_member\tnew_member\taction\ttype\tconfidence\n'
                        'Rec\tinclude/h.h\tunk_04\tstate\trename\t-\tproven\n'
                        'Rec\tinclude/h.h\tunk_08\tmode\tkeep\t-\tproven\n'
                        'Rec\tinclude/h.h\tunk_0C\tflag\trename\ts32\tproven\n'
                        'Rec\tinclude/h.h\tunk_10\tx\trename\t-\tguess\n')
        self.assertEqual([m.old for m in K.read_members(path)], ['unk_04'])

    def test_symbol_tables_both_formats(self):
        t = self.tables()
        self.assertEqual(t.symbol_new['func_80001000'], {'spawn_thing'})
        names = self.put('names.tsv', '0x80002000\tfunc_80002000\tnew_fn\tevidence text\n')
        self.assertEqual(K.read_symbols(names), [('func_80002000', 'new_fn', ())])


class Debt(Base):
    def files(self):
        self.put('src/a.c', 'void spawn_thing(void) {\n}\n')
        self.put('src/b.c', 'void per_image_new(void) {\n}\nvoid other(void){}\n')
        self.put('src/c.c', 'void shared_old(void) {\n}\n')        # another image keeps the old name

    def test_function_keys_move_only_in_files_that_spell_the_new_name(self):
        self.files()
        self.baseline({'src': {'a.c': [10, {'func_80001000#1': [10, 0, 0, 0, 0, 0, 3]}],
                               'b.c': [10, {'shared_old#1': [10, 0, 0, 0, 0, 0, 2]}],
                               'c.c': [10, {'shared_old#1': [10, 0, 0, 0, 0, 0, 1]}]}})
        rk = self.run_rekey()
        data = json.loads(rk.out['tools/lint/debt_baseline.json'])
        self.assertEqual(list(data['by_file']['src']['a.c'][1]), ['spawn_thing#1'])
        self.assertEqual(list(data['by_file']['src']['b.c'][1]), ['per_image_new#1'])
        self.assertEqual(list(data['by_file']['src']['c.c'][1]), ['shared_old#1'])     # old name still lives there
        self.assertEqual(rk.report.stats['debt']['migrated'], 2)

    def test_a_different_row_under_the_new_key_is_a_collision(self):
        self.files()
        self.baseline({'src': {'a.c': [10, {'func_80001000#1': [10, 0, 0, 0, 0, 0, 3],
                                            'spawn_thing#1': [5, 0, 0, 0, 0, 0, 1]}]}})
        rk = self.run_rekey()
        self.assertEqual(rk.report.stats['debt']['collisions'], 1)
        self.assertNotIn('tools/lint/debt_baseline.json', rk.out)

    def test_equal_row_under_the_new_key_is_dropped_not_a_collision(self):
        self.files()
        self.baseline({'src': {'a.c': [10, {'func_80001000#1': [10, 0, 0, 0, 0, 0, 3],
                                            'spawn_thing#1': [10, 0, 0, 0, 0, 0, 3]}]}})
        rk = self.run_rekey()
        self.assertEqual(rk.report.stats['debt']['collisions'], 0)

    def test_occurrence_numbers_follow_definition_position_with_a_base_revision(self):
        env = dict(os.environ, GIT_AUTHOR_NAME='t', GIT_AUTHOR_EMAIL='t@t', GIT_COMMITTER_NAME='t',
                   GIT_COMMITTER_EMAIL='t@t')
        run = lambda *a: subprocess.run(['git', *a], cwd=self.root, check=True, capture_output=True, env=env)
        run('init', '-q')
        self.put('src/a.c', 'void spawn_thing(void) {\n}\nvoid func_80001000(void) {\n}\n')
        run('add', '-A')
        run('commit', '-qm', 'base')
        # the second definition is renamed; spawn_thing already exists once, so the renamed one becomes #2
        self.put('src/a.c', 'void spawn_thing(void) {\n}\nvoid spawn_thing(void) {\n}\n')
        self.baseline({'src': {'a.c': [20, {'func_80001000#1': [10, 0, 0, 0, 0, 0, 3]}]}})
        rk = self.run_rekey(base='HEAD')
        data = json.loads(rk.out['tools/lint/debt_baseline.json'])
        self.assertEqual(list(data['by_file']['src']['a.c'][1]), ['spawn_thing#2'])

    def test_old_key_with_no_new_definition_is_reported_untouched(self):
        self.put('src/a.c', 'void unrelated(void) {\n}\n')
        self.baseline({'src': {'a.c': [10, {'func_80001000#1': [10, 0, 0, 0, 0, 0, 3]}]}})
        rk = self.run_rekey()
        self.assertEqual(rk.report.stats['debt']['untouched'], 1)

    def test_bad_label_site_moves_with_a_member_rename(self):
        self.put('include/h.h', 'typedef struct Rec {\n    u8 pad[4];\n    union { u16 s; s16 u; } state;\n} Rec;\n')
        self.baseline({}, bad=['include/h.h::Rec.unk_04#1'])
        rk = self.run_rekey()
        data = json.loads(rk.out['tools/lint/debt_baseline.json'])
        self.assertEqual(data['bad_label_sites'], ['include/h.h::Rec.state#1'])


class UnionIds(Base):
    HEADER = 'typedef struct Rec {\n    u8 pad[4];\n    union { s16 s; u16 u; } state;\n    union { s16 s; u16 u; } unk_08;\n} Rec;\n'

    def row(self, ident, **extra):
        owner, _, path = ident.partition('::')[2].partition('.')
        return dict(dict(count_basis='x', evidence='e', example_sites={}, file='include/h.h', id=ident, kind='other',
                         line=3, loads={}, members=[{'name': 's', 'type': 's16'}], owner=owner, path=path,
                         retired_to_cast=[], status='unproven', uses={}), **extra)

    def setup_ledgers(self, ids=('include/h.h::Rec.unk_04', 'include/h.h::Rec.unk_08')):
        self.put('include/h.h', self.HEADER)
        self.put('ledger/unions.jsonl', ''.join(dump(self.row(i)) + '\n' for i in ids))
        self.put('tools/lint/union_baseline.json', json.dumps({'count': len(ids), 'ids': sorted(ids), 'reason': 'r',
                                                                'schema': 1}, indent=1) + '\n')

    def test_ids_owner_and_path_move_in_the_ledger_and_the_baseline(self):
        self.setup_ledgers()
        rk = self.run_rekey()
        rows = [json.loads(line) for line in rk.out['ledger/unions.jsonl'].splitlines()]
        self.assertEqual(rows[0]['id'], 'include/h.h::Rec.state')
        self.assertEqual((rows[0]['owner'], rows[0]['path']), ('Rec', 'state'))
        self.assertEqual(rows[1]['id'], 'include/h.h::Rec.unk_08')                 # skipped row: not renamed
        base = json.loads(rk.out['tools/lint/union_baseline.json'])
        self.assertEqual(base['ids'], ['include/h.h::Rec.state', 'include/h.h::Rec.unk_08'])
        self.assertEqual(rk.report.stats['union_ids']['migrated'], 2)

    def test_member_of_another_record_is_not_used(self):
        other = 'record\theader\told_member\tnew_member\toffset\tstatus\nOther\tinclude/h.h\tunk_04\tstate\t0x4\trenamed\n'
        self.setup_ledgers()
        rk = self.run_rekey(self.tables(members=other))
        self.assertEqual(rk.report.stats['union_ids']['migrated'], 0)
        self.assertEqual(rk.report.stats['union_ids']['untouched'], 1)

    def test_struct_tag_owner_matches_the_typedef_record(self):
        self.put('include/h.h', 'typedef struct RecTag {\n    union { s16 s; u16 u; } state;\n} Rec;\n')
        self.put('ledger/unions.jsonl', dump(self.row('include/h.h::RecTag.unk_04')) + '\n')
        rk = self.run_rekey()
        self.assertEqual(json.loads(rk.out['ledger/unions.jsonl'])['id'], 'include/h.h::RecTag.state')

    def test_existing_new_id_is_a_collision(self):
        self.setup_ledgers(('include/h.h::Rec.unk_04', 'include/h.h::Rec.state'))
        rk = self.run_rekey()
        self.assertEqual(rk.report.stats['union_ids']['collisions'], 1)

    def retired(self, ident, site):
        return self.row(ident, status='retired', retired_to_cast=[site])

    def test_retired_row_follows_the_rename_when_its_cast_lines_spell_the_new_member(self):
        self.put('include/h.h', 'typedef struct Rec {\n    u8 pad[4];\n    s16 state;\n} Rec;\n')
        self.put('src/a.c', 'void f(Rec *r) {\n    r->state = (s16) 3;\n}\n')
        self.put('ledger/unions.jsonl', dump(self.retired('include/h.h::Rec.unk_04', 'src/a.c:2 (s16)')) + '\n')
        rk = self.run_rekey()
        self.assertEqual(json.loads(rk.out['ledger/unions.jsonl'])['id'], 'include/h.h::Rec.state')

    def test_retired_row_citing_another_records_member_of_the_old_name_stays(self):
        self.put('include/h.h', 'typedef struct Rec {\n    u8 pad[4];\n    s16 state;\n} Rec;\n'
                 'typedef struct Other {\n    s16 unk_04;\n} Other;\n')
        self.put('src/a.c', 'void f(Other *o) {\n    o->unk_04 = (s16) 3;\n}\n')
        self.put('ledger/unions.jsonl', dump(self.retired('include/h.h::Rec.unk_04', 'src/a.c:2 (s16)')) + '\n')
        rk = self.run_rekey()
        self.assertNotIn('ledger/unions.jsonl', rk.out)
        rk = K.Rekey(self.root, self.tables(), None, None, retired=False)
        rk.run()
        self.assertNotIn('ledger/unions.jsonl', rk.out)


class Floors(Base):
    def test_name_callers_and_spellings_follow_the_new_name(self):
        self.put('src/a.c', 'void spawn_thing(void) {\n}\n')
        self.put('src/caller.c', 'void shared_old(void) {\n}\n')
        self.put('src/b.c', 'void per_image_new(void) {\n  spawn_thing();\n}\n')
        row = {'arity_evidence': [{'args': 1, 'caller': 'shared_old', 'line': 2, 'outcome': 'held',
                                   'path': 'src/b.c'}, {'args': 1, 'caller': 'shared_old', 'line': 9, 'outcome': 'held',
                                                        'path': 'src/caller.c'}],
               'blocking': [{'declaration': 'src/a.c', 'is_def': False, 'path': 'src/a.c', 'reason': 'x',
                             'spelling': 'void func_80001000(void *)'}],
               'definition': {'path': 'src/a.c', 'proto': 'void func_80001000(void *);'}, 'name': 'func_80001000',
               'owner': 'src/a.c', 'reason': 'r', 'schema': 's', 'status': 'open', 'floor_class': 'k',
               'evidence': {}}
        self.put('ledger/prototype_floors.jsonl', dump(row) + '\n')
        rk = self.run_rekey()
        new = json.loads(rk.out['ledger/prototype_floors.jsonl'])
        self.assertEqual(new['name'], 'spawn_thing')
        self.assertEqual(new['blocking'][0]['spelling'], 'void spawn_thing(void *)')
        self.assertEqual(new['definition']['proto'], 'void spawn_thing(void *);')
        self.assertEqual([e['caller'] for e in new['arity_evidence']], ['per_image_new', 'shared_old'])

    def test_existing_row_of_the_new_name_is_a_collision(self):
        self.put('src/a.c', 'void spawn_thing(void) {\n}\n')
        base = {'blocking': [], 'definition': {'path': 'src/a.c', 'proto': ''}, 'owner': 'o', 'reason': 'r',
                'schema': 's', 'status': 'open', 'floor_class': 'k', 'evidence': {}}
        self.put('ledger/prototype_floors.jsonl',
                 dump(dict(base, name='func_80001000')) + '\n' + dump(dict(base, name='spawn_thing')) + '\n')
        rk = self.run_rekey()
        self.assertEqual(rk.report.stats['floors']['collisions'], 1)

    def test_proto_baseline_candidate_sites(self):
        self.put('src/a.c', 'void spawn_thing(void) {\n}\n')
        self.put('src/d.c', 'extern void func_80001000(void);\n')
        sites = ['func_80001000::src/a.c::src/d.c::arity', 'keep_me::src/a.c::src/d.c::arity']
        self.put('tools/lint/proto_baseline.json', json.dumps({'candidate_sites': sorted(sites)}, indent=2) + '\n')
        rk = self.run_rekey()
        data = json.loads(rk.out['tools/lint/proto_baseline.json'])
        self.assertEqual(data['candidate_sites'], ['keep_me::src/a.c::src/d.c::arity',
                                                   'spawn_thing::src/a.c::src/d.c::arity'])


class SmallLedgers(Base):
    def test_accepted_warning_rows_function_and_callees(self):
        self.put('src/a.c', 'void spawn_thing(void) {\n}\nvoid x(void){ spawn_thing(); }\n')
        self.put('tools/lint/accepted_warning_sites.tsv',
                 '# c\nwarning\tfile\tfunction\tsites\tcallees\n-Wx\tsrc/a.c\tfunc_80001000\t3\tRotTransPers,func_80001000\n')
        rk = self.run_rekey()
        self.assertIn('-Wx\tsrc/a.c\tspawn_thing\t3\tRotTransPers,spawn_thing', rk.out['tools/lint/accepted_warning_sites.tsv'])

    def test_soundness_identities(self):
        self.put('src/a.c', 'void spawn_thing(void) {\n}\n')
        data = {'identities': [['src/a.c', 'func_80001000', 'x']], 'schema': 2}
        self.put('tools/lint/soundness_gcc_baseline.json', json.dumps(data, indent=2) + '\n')
        rk = self.run_rekey()
        self.assertEqual(json.loads(rk.out['tools/lint/soundness_gcc_baseline.json'])['identities'][0][:2],
                         ['src/a.c', 'spawn_thing'])

    def bridge(self, **kw):
        return dict(dict(cast_text='(T *)rec->unk_04', evidence='e', file='src/a.c', function='func_80001000',
                         ordinal=1, reason='r', retired_by=None, site_id='src/a.c::func_80001000@abc123',
                         status='open'), **kw)

    def test_bridge_function_site_id_and_member_spelling(self):
        self.put('src/a.c', 'void spawn_thing(void) {\n  x = (T *)rec->state;\n}\n')
        self.put('ledger/bridge_casts.jsonl', dump(self.bridge()) + '\n')
        rk = self.run_rekey()
        row = json.loads(rk.out['ledger/bridge_casts.jsonl'])
        self.assertEqual((row['function'], row['site_id'], row['cast_text']),
                         ('spawn_thing', 'src/a.c::spawn_thing@abc123', '(T *)rec->state'))

    def test_bridge_member_not_in_source_is_left_alone(self):
        self.put('src/a.c', 'void spawn_thing(void) {\n  x = (T *)rec->other;\n}\n')
        self.put('ledger/bridge_casts.jsonl', dump(self.bridge(function='spawn_thing',
                                                              site_id='src/a.c::spawn_thing@abc')) + '\n')
        rk = self.run_rekey()
        self.assertNotIn('ledger/bridge_casts.jsonl', rk.out)

    def test_fields_census_row_and_site_row(self):
        census = {'census': {}, 'ctype': 'int', 'decided': 'd', 'evidence': [], 'level': 'low', 'name': 'unk_04',
                  'off': '0x04', 'owner_confirmed': False, 'status': 'declared_unnamed', 'type': 'Rec'}
        site = {'kind': 'refusal', 'reason': 'r', 'site': 'src/a.c:func_80001000:rec', 'type': 'Rec'}
        self.put('src/a.c', 'void spawn_thing(void) {\n}\n')
        self.put('ledger/fields.jsonl', dump(census) + '\n' + dump(site) + '\n')
        rk = self.run_rekey()
        rows = [json.loads(line) for line in rk.out['ledger/fields.jsonl'].splitlines()]
        self.assertEqual((rows[0]['name'], rows[0]['previous_name']), ('state', 'unk_04'))
        self.assertEqual(rows[1]['site'], 'src/a.c:spawn_thing:rec')

    def test_fields_collision_with_an_existing_name(self):
        base = {'census': {}, 'ctype': 'int', 'decided': 'd', 'evidence': [], 'level': 'low', 'owner_confirmed': False,
                'status': 's', 'type': 'Rec'}
        self.put('ledger/fields.jsonl', dump(dict(base, name='unk_04', off='0x04')) + '\n'
                 + dump(dict(base, name='state', off='0x20')) + '\n')
        rk = self.run_rekey()
        self.assertEqual(rk.report.stats['fields']['collisions'], 1)


class Driver(Base):
    def setup_tree(self):
        self.put('src/a.c', 'void spawn_thing(void) {\n}\n')
        self.put('tools/lint/accepted_warning_sites.tsv', 'warning\tfile\tfunction\tsites\tcallees\n-Wx\tsrc/a.c\tfunc_80001000\t3\tz\n')
        self.put('members.tsv', MEMBER_ROWS)
        self.put('symbols.tsv', SYMBOL_ROWS)

    def main(self, *args):
        out = io.StringIO()
        with contextlib.redirect_stdout(out), contextlib.redirect_stderr(io.StringIO()):
            rc = K.main(['--root', str(self.root), '--members', str(self.root / 'members.tsv'), '--symbols',
                         str(self.root / 'symbols.tsv'), *args])
        return rc, out.getvalue()

    def test_check_writes_nothing_and_exits_1(self):
        self.setup_tree()
        before = (self.root / 'tools/lint/accepted_warning_sites.tsv').read_bytes()
        rc, out = self.main('--check')
        self.assertEqual(rc, 1)
        self.assertEqual(before, (self.root / 'tools/lint/accepted_warning_sites.tsv').read_bytes())
        self.assertIn('accepted', out)

    def test_write_goes_through_the_atomic_helper_and_a_second_run_is_clean(self):
        self.setup_tree()
        with patch.object(atomic_io, 'write_text', wraps=atomic_io.write_text) as spy:
            rc, _ = self.main('--write')
        self.assertEqual(rc, 0)
        self.assertEqual(spy.call_count, 1)
        self.assertIn('spawn_thing', (self.root / 'tools/lint/accepted_warning_sites.tsv').read_text())
        rc, out = self.main('--check')
        self.assertEqual(rc, 0)
        self.assertEqual([p.name for p in (self.root / 'tools/lint').glob('.*')], [], 'no temp file left behind')

    def test_collision_refuses_and_writes_nothing(self):
        self.setup_tree()
        self.put('ledger/fields.jsonl', dump({'census': {}, 'name': 'unk_04', 'off': '0x04', 'type': 'Rec'}) + '\n'
                 + dump({'census': {}, 'name': 'state', 'off': '0x20', 'type': 'Rec'}) + '\n')
        before = (self.root / 'tools/lint/accepted_warning_sites.tsv').read_bytes()
        rc, out = self.main('--write')
        self.assertEqual(rc, 2)
        self.assertEqual(before, (self.root / 'tools/lint/accepted_warning_sites.tsv').read_bytes())
        rc, out = self.main('--write', '--skip-collisions')
        self.assertEqual(rc, 0)
        self.assertIn('spawn_thing', (self.root / 'tools/lint/accepted_warning_sites.tsv').read_text())


class Between(Base):
    def test_member_and_symbol_pairs_from_two_revisions(self):
        env = dict(os.environ, GIT_AUTHOR_NAME='t', GIT_AUTHOR_EMAIL='t@t', GIT_COMMITTER_NAME='t',
                   GIT_COMMITTER_EMAIL='t@t')
        run = lambda *a: subprocess.run(['git', *a], cwd=self.root, check=True, capture_output=True, env=env)
        run('init', '-q')
        self.put('src/a.c', 'void func_1(void) {\n  rec->unk_04 = 1; /* func_1 */\n  other.unk_08 = "unk_04";\n}\n')
        run('add', '-A')
        run('commit', '-qm', 'a')
        self.put('src/a.c', 'void spawn_thing(void) {\n  rec->state = 1; /* spawn_thing */\n  other.mode = "unk_04";\n}\n')
        run('add', '-A')
        run('commit', '-qm', 'b')
        tables, lines = K.derive_between(self.root, 'HEAD~1', 'HEAD')
        self.assertEqual(sorted((m.old, m.new) for m in tables.members), [('unk_04', 'state'), ('unk_08', 'mode')])
        self.assertEqual([(o, n) for o, n, _ in tables.symbols], [('func_1', 'spawn_thing')])

    def test_files_with_different_token_counts_are_skipped_and_reported(self):
        env = dict(os.environ, GIT_AUTHOR_NAME='t', GIT_AUTHOR_EMAIL='t@t', GIT_COMMITTER_NAME='t',
                   GIT_COMMITTER_EMAIL='t@t')
        run = lambda *a: subprocess.run(['git', *a], cwd=self.root, check=True, capture_output=True, env=env)
        run('init', '-q')
        self.put('src/a.c', 'int f(void) { return 1; }\n')
        run('add', '-A')
        run('commit', '-qm', 'a')
        self.put('src/a.c', 'int g(void) { int x; return 1; }\n')
        run('add', '-A')
        run('commit', '-qm', 'b')
        tables, lines = K.derive_between(self.root, 'HEAD~1', 'HEAD')
        self.assertFalse(tables.any())
        self.assertIn('1 files with different token streams skipped', lines[0])


if __name__ == '__main__':
    unittest.main()
