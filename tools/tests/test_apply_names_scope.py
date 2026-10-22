import hashlib
import contextlib
import io
import json
from pathlib import Path
import re
import sys
import tempfile
import unittest
from unittest.mock import patch

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
from apply_names_batch import scoped_rewrites, validate_renamed_alias_consumers
from apply_names_data import inline_plan
import apply_names as N


class ScopedNamesTests(unittest.TestCase):
    def test_existing_alias_and_legacy_definition_replay_together(self):
        with tempfile.TemporaryDirectory() as td:
            root = Path(td)
            for folder in ('config', 'ledger', 'include/dungeon', 'src/dungeon'):
                (root / folder).mkdir(parents=True)
            source = root / 'src/dungeon/a.c'
            other = root / 'src/dungeon/b.c'
            header = root / 'include/dungeon/a.h'
            source.write_text('void func_80024020(void) {}\n')
            other.write_text('void func_80024020(void) { return; }\n')
            header.write_text('void old_alias(void);\n')
            table = root / 'config/names.tsv'
            table.write_text('0x80024020\tfunc_80024020\told_alias\told evidence\n')
            proposal = root / 'proposal.tsv'
            proposal.write_text('0x80024020\tfunc_80024020\tnew_alias\tnew evidence\n')
            identity = root / 'identity.json'
            identity.write_text(json.dumps({'func_80024020': {'row': 'dungeon/a', 'symbol': 'func_80024020'}}))
            scope = root / 'scope.json'
            scope.write_text(json.dumps({'func_80024020': ['src/dungeon/a.c', 'include/dungeon/a.h']}))
            rows = [dict(id='dungeon/a', func='func_80024020', container='dungeon', c_path=str(source))]
            argv = ['apply_names.py', str(proposal), '--batch', '--defer-verification',
                    '--rename-existing', '--identity-map', str(identity), '--scope-map', str(scope)]
            with patch.multiple(N, ROOT=root, NAMES=table, JOURNAL=root/'ledger/names.jsonl', INCLUDE=root/'include'), \
                 patch.object(N, 'rows', return_value=rows), \
                 patch.object(N, 'load_tree', side_effect=lambda: ({p:p.read_text() for p in (source, other)}, {'old_alias','func_80024020'})), \
                 patch('apply_names_batch.own_source', side_effect=lambda *_: (source.read_text(), None)), \
                 patch('apply_names_batch.consumer_paths', return_value=set()), \
                 patch.object(sys, 'argv', argv), contextlib.redirect_stdout(io.StringIO()):
                N.main()
                N.main()
            self.assertEqual(source.read_text(), 'void new_alias(void) {}\n')
            self.assertEqual(header.read_text(), 'void new_alias(void);\n')
            self.assertIn('func_80024020', other.read_text())
            self.assertEqual(table.read_text().count('\tnew_alias\t'), 1)

    def test_shared_address_only_changes_selected_bank_and_header(self):
        root = Path('/repo')
        a, b, h = [root / p for p in ('src/dungeon/a.c', 'src/dungeon/b.c', 'include/dungeon/a.h')]
        source = '/* func_80024020 */\nvoid func_80024020(void) {}\nchar *s="func_80024020";\n'
        texts = {a: source, b: source, h: 'void func_80024020(void);\n'}
        changed, _ = scoped_rewrites(root, texts, {'func_80024020': 'advance_arc'},
            {'func_80024020': ['src/dungeon/a.c', 'include/dungeon/a.h']})
        self.assertNotIn(b, changed)
        self.assertIn('void advance_arc(void)', changed[a])
        self.assertIn('/* func_80024020 */', changed[a])
        self.assertIn('"func_80024020"', changed[a])
        self.assertEqual(changed[h], 'void advance_arc(void);\n')

    def test_existing_readable_alias_outside_scope_refuses(self):
        root = Path('/repo')
        a, b = [root / p for p in ('src/dungeon/a.c', 'src/dungeon/b.c')]
        with self.assertRaisesRegex(ValueError, 'existing readable consumers outside scope'):
            validate_renamed_alias_consumers(root,
                {a: 'void func_80024020(void) {}\n', b: 'void old_alias(void) {}\n'},
                {'func_80024020': ('old_alias', 'advance_arc')},
                {'func_80024020': ['src/dungeon/a.c']})

    def test_legacy_alias_in_comments_and_strings_does_not_hold(self):
        root = Path('/repo')
        a, b = [root / p for p in ('src/dungeon/a.c', 'src/dungeon/b.c')]
        validate_renamed_alias_consumers(root,
            {a: 'void old_alias(void) {}\n', b: '/* old_alias */ char *s="old_alias";\n'},
            {'func_80024020': ('old_alias', 'advance_arc')},
            {'func_80024020': ['src/dungeon/a.c']})

    def test_missing_or_escaping_scope_refuses(self):
        root = Path('/repo')
        for scope in ({}, {'func_80024020': []}, {'func_80024020': ['../src/a.c']},
                      {'func_80024020': ['/src/a.c']}, {'func_80024020': ['src/missing.c']}):
            with self.assertRaises(ValueError):
                scoped_rewrites(root, {}, {'func_80024020': 'advance_arc'}, scope)

    def test_inline_rebase_uses_only_the_bank_scope(self):
        with tempfile.TemporaryDirectory() as td:
            root = Path(td)
            (root / 'ledger').mkdir()
            path = root / 'src/dungeon/a.c'
            old = 'void func_80024020(void) { func_80024064(); }\n'
            new = old.replace('func_80024020', 'advance_arc')
            record = dict(member_id='dungeon/a', tu_new='src/dungeon/a.c', offset=0,
                          inlined_bytes=len(old), bytes=len(old), original_includes=[],
                          source_sha256=hashlib.sha256(old.encode()).hexdigest())
            (root / 'ledger/layout_inline.jsonl').write_text(json.dumps(record) + '\n')
            mapping = {'func_80024020': 'advance_arc', 'func_80024064': 'different_bank'}
            metadata, updates = inline_plan(root, {path: old}, {path: new},
                re.compile(r'\b(?:func_80024020|func_80024064)\b'), mapping,
                path_mappings={path: {'func_80024020': 'advance_arc'}})
            self.assertEqual(len(updates), 1)
            fresh = json.loads(metadata[root / 'ledger/layout_inline.jsonl'][1])
            self.assertEqual(fresh['source_sha256'], hashlib.sha256(new.encode()).hexdigest())


if __name__ == '__main__':
    unittest.main()
