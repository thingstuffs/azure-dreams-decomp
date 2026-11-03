"""Binding re-keys must preserve targets and refuse ambiguous callee families."""
import json
import sqlite3
import sys
import tempfile
import unittest
from pathlib import Path
from types import SimpleNamespace
from unittest.mock import patch

sys.path.insert(0, str(Path(__file__).resolve().parent))
import copy_place as C


class RekeyTest(unittest.TestCase):
    def setUp(self):
        self.tmp = tempfile.TemporaryDirectory()
        self.addCleanup(self.tmp.cleanup)
        self.root = Path(self.tmp.name)
        self.db = self.root / 'map.db'
        db = sqlite3.connect(self.db)
        db.executescript('CREATE TABLE recipe(source,id,output,kind); '
                         'CREATE TABLE image_unit(recipe,image,rows,rebind);')
        db.execute('INSERT INTO recipe VALUES (?,?,?,?)', ('src/a.c', 'r', 'r.o', 'row'))
        db.execute('INSERT INTO image_unit VALUES (?,?,?,?)', ('r', 'town/copy', '["copy"]', 1))
        db.commit()
        db.close()
        self.entry = dict(row='copy', home='home', image='town/copy', vma=0x80001000,
                          container='town', foff=0x1000,
                          bindings={0x80000200: 0x80001200})
        self.tables = ({}, {}, {'copy': self.entry, 'home': dict(vma=0x80000100)}, {})
        self.pair = dict(file='src/a.c', evidence='caller_placement_binds_elsewhere',
                         link='func_80000300>func_80000200')
        self.doc_path = self.root / 'config/link/town/copy.json'
        self.doc_path.parent.mkdir(parents=True)
        self.doc_path.write_text(json.dumps(dict(entries=[dict(row='copy', bindings={
            '0x80000200': '0x80001200'})])))
        self.addCleanup(patch.stopall)
        patch.object(C.L, 'load', return_value=self.tables).start()
        patch.object(C.L, 'caller_images', return_value=['town/copy']).start()
        self.target = patch.object(C.L, 'copy_link_target', return_value=0x80001200).start()
        patch.object(C.L, '_binding', side_effect=lambda _t, e, a: e['bindings'].get(a, a)).start()
        self.nm = patch.object(C.subprocess, 'run', return_value=SimpleNamespace(stdout='')).start()

    def test_adds_real_key_and_keeps_old_key(self):
        result = C.rekey_calls([self.pair], self.db, self.root, apply=True)
        self.assertEqual(result[0]['status'], 'ready')
        bindings = json.loads(self.doc_path.read_text())['entries'][0]['bindings']
        self.assertEqual(bindings, {'0x80000200': '0x80001200', '0x80000300': '0x80001200'})

    def test_ambiguous_family_never_gets_override(self):
        self.target.side_effect = ValueError('image holds 2 instances')
        before = self.doc_path.read_bytes()
        result = C.rekey_calls([self.pair], self.db, self.root, apply=True)
        self.assertEqual(result[0]['status'], 'hold')
        self.assertEqual(self.doc_path.read_bytes(), before)

    def test_existing_import_cannot_change_target(self):
        self.nm.return_value.stdout = '         U func_80000300\n'
        result = C.rekey_calls([self.pair], self.db, self.root, apply=True)
        self.assertIn('already imported', result[0]['reason'])
        self.assertNotIn('0x80000300', self.doc_path.read_text())

    def test_old_reference_must_reach_unique_copy(self):
        self.target.return_value = 0x80001204
        result = C.rekey_calls([self.pair], self.db, self.root, apply=True)
        self.assertIn('old binding', result[0]['reason'])

    def test_dry_run_does_not_write(self):
        before = self.doc_path.read_bytes()
        result = C.rekey_calls([self.pair], self.db, self.root)
        self.assertEqual(result[0]['status'], 'ready')
        self.assertEqual(self.doc_path.read_bytes(), before)

    def test_later_ambiguous_image_holds_whole_pair(self):
        db = sqlite3.connect(self.db)
        db.execute('INSERT INTO image_unit VALUES (?,?,?,?)', ('r', 'town/ambiguous', '["copy"]', 1))
        db.commit()
        db.close()
        self.target.side_effect = [0x80001200, ValueError('image holds 2 instances')]
        before = self.doc_path.read_bytes()
        result = C.rekey_calls([self.pair], self.db, self.root, apply=True)
        self.assertEqual(result[0]['status'], 'hold')
        self.assertEqual(self.doc_path.read_bytes(), before)


if __name__ == '__main__':
    unittest.main()
