"""The data alias path runs entirely against a temporary source/config tree."""
import contextlib
import io
import json
import sys
import tempfile
import unittest
from pathlib import Path
from unittest import mock

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))
import apply_names as names  # noqa: E402


class DataNamesTests(unittest.TestCase):
    def setUp(self):
        self.tmp = tempfile.TemporaryDirectory()
        self.addCleanup(self.tmp.cleanup)
        self.root = Path(self.tmp.name)
        for sub in ("config", "include", "ledger", "src/town"):
            (self.root / sub).mkdir(parents=True)
        self.table = self.root / "config/names.tsv"
        self.table.write_text("# aliases\n")
        self.journal = self.root / "ledger/names.jsonl"
        self.source = self.root / "src/town/func_80000000.c"
        self.source.write_text("extern int D_80001234;\nint func_80000000(void) { return D_80001234; }\n")
        self.proposed = self.root / "proposed.tsv"
        self.proposed.write_text("0x80001234\tD_80001234\treadableData\tevidence\n")
        self.row = {"id": "town/func_80000000", "container": "town",
                    "func": "func_80000000", "c_path": str(self.source)}

    def run_names(self, *args, verdict=True):
        verified = []

        def check(row, path, include_root=None):
            verified.append((row["id"], Path(path), include_root))
            return {"exact": verdict, "status": "ok", "total": 0 if verdict else 1}

        with mock.patch.object(names, "ROOT", self.root), \
             mock.patch.object(names, "NAMES", self.table), \
             mock.patch.object(names, "INCLUDE", self.root / "include"), \
             mock.patch.object(names, "JOURNAL", self.journal), \
             mock.patch.object(names, "rows", return_value=[self.row]), \
             mock.patch.object(names, "verify", side_effect=check), \
             mock.patch.object(sys, "argv", ["apply_names.py", str(self.proposed), "--data", *args]), \
             contextlib.redirect_stdout(io.StringIO()):
            names.main()
        return verified

    def test_data_alias_appends_without_rewrite(self):
        before = self.source.read_text()
        self.assertEqual(self.run_names(), [])
        self.assertIn("D_80001234\treadableData\tevidence", self.table.read_text())
        self.assertEqual(self.source.read_text(), before)

    def test_rewrite_verifies_each_touched_row(self):
        verified = self.run_names("--rewrite")
        self.assertEqual(verified, [(self.row["id"], self.source, self.root / "include")])
        self.assertIn("return readableData;", self.source.read_text())
        self.assertNotIn("D_80001234", self.source.read_text())

    def test_failed_verification_reverts_source_and_alias(self):
        before = self.source.read_text()
        self.run_names("--rewrite", verdict=False)
        self.assertEqual(self.source.read_text(), before)
        self.assertNotIn("readableData", self.table.read_text())
        self.assertEqual(json.loads(self.journal.read_text())["outcome"], "reverted")

    def test_collision_and_mismatched_address_are_refused(self):
        self.table.write_text("0x80005678\tD_80005678\treadableData\tfirst\n")
        self.run_names("--rewrite")
        self.assertEqual(len(self.table.read_text().splitlines()), 1)
        self.proposed.write_text("0x80005678\tD_80001234\totherData\tevidence\n")
        self.run_names("--rewrite")
        self.assertEqual(len(self.table.read_text().splitlines()), 1)
        self.assertIn("D_80001234", self.source.read_text())

    def test_identifier_used_in_source_is_refused(self):
        self.source.write_text("int alreadyUsed;\n" + self.source.read_text())
        self.proposed.write_text("0x80001234\tD_80001234\talreadyUsed\tevidence\n")
        self.assertEqual(self.run_names("--rewrite"), [])
        self.assertNotIn("alreadyUsed\tevidence", self.table.read_text())
        self.assertIn("D_80001234", self.source.read_text())

    def test_scoped_data_batch_keeps_other_source_and_header(self):
        other = self.root / 'src/dungeon/consumer.c'
        other.parent.mkdir()
        other.write_text('extern int D_80001234;\nint other(void){return D_80001234;}\n')
        header = self.root / 'include/other.h'
        header.write_text('extern int D_80001234;\n')
        original = {p: p.read_bytes() for p in (other, header)}
        self.proposed.write_text('0x80001234\tD_80001234\treadable_data\tevidence\n')
        self.run_names('--batch', '--rewrite', '--defer-verification', '--path-prefix', 'src/town')
        self.assertIn('return readable_data;', self.source.read_text())
        self.assertIn('D_80001234\treadable_data', self.table.read_text())
        for p, text in original.items():
            self.assertEqual(p.read_bytes(), text)

    def scoped_proposals(self, scopes):
        other = self.root / 'src/town/second.c'
        other.write_text('extern int D_80001234;\nint second(void){return D_80001234;}\n')
        self.proposed.write_text('0x80001234\tD_80001234\tfirst_data\tfirst object\n'
                                 '0x80001234\tD_80001234\tsecond_data\tsecond object\n')
        path = self.root / 'scopes.json'
        path.write_text(json.dumps(scopes))
        return other, path

    def test_reused_data_address_has_independent_scopes_and_replays(self):
        other, path = self.scoped_proposals({'first_data': ['src/town/func_80000000.c'],
                                            'second_data': ['src/town/second.c']})
        for option in ('--symbol-scope-map', '--scope-map'):
            self.run_names('--batch', '--rewrite', '--defer-verification', option, str(path))
        self.assertIn('return first_data;', self.source.read_text())
        self.assertIn('return second_data;', other.read_text())
        self.assertEqual(self.table.read_text().count('\tD_80001234\t'), 2)

    def test_reused_address_with_overlapping_or_missing_scopes_refuses_atomically(self):
        for scopes in ({}, {'D_80001234': ['src/town/second.c']},
                       {'first_data': ['src/town/func_80000000.c'],
                        'second_data': ['src/town/func_80000000.c']}):
            other, path = self.scoped_proposals(scopes)
            before = {p:p.read_bytes() for p in (self.table, self.source, other)}
            with self.assertRaises(ValueError):
                self.run_names('--batch', '--rewrite', '--defer-verification', '--symbol-scope-map', str(path))
            self.assertEqual(before, {p:p.read_bytes() for p in before})

    def test_limit_keeps_the_other_overlay_untouched(self):
        other, path = self.scoped_proposals({'first_data': ['src/town/func_80000000.c'],
                                            'second_data': ['src/town/second.c']})
        before = other.read_bytes()
        self.run_names('--batch', '--rewrite', '--defer-verification', '--limit', '1',
                       '--symbol-scope-map', str(path))
        self.assertIn('return first_data;', self.source.read_text())
        self.assertEqual(other.read_bytes(), before)
        self.assertNotIn('\tsecond_data\t', self.table.read_text())

    def test_limit_does_not_hide_an_ambiguous_unscoped_address(self):
        self.scoped_proposals({})
        with self.assertRaisesRegex(ValueError, 'explicit scopes'):
            self.run_names('--batch', '--rewrite', '--defer-verification', '--limit', '1')

    def test_data_scope_refuses_unknown_escaping_and_empty_paths(self):
        self.proposed.write_text('0x80001234\tD_80001234\tfirst_data\tevidence\n')
        path = self.root / 'scopes.json'
        for paths in ([], ['../src/a.c'], ['/src/a.c'], ['src/missing.c']):
            path.write_text(json.dumps({'first_data': paths}))
            with self.assertRaises(ValueError):
                self.run_names('--batch', '--rewrite', '--defer-verification', '--symbol-scope-map', str(path))

    def test_ordinary_data_receipt_keeps_the_original_map_field(self):
        self.proposed.write_text('0x80001234\tD_80001234\tfirst_data\tevidence\n')
        proof = self.root / 'proof.json'
        self.run_names('--batch', '--rewrite', '--defer-verification', '--proof-log', str(proof))
        self.assertEqual(json.loads(proof.read_text())['map'], {'D_80001234': 'first_data'})

    def test_reused_address_receipt_does_not_pick_an_arbitrary_global_alias(self):
        _, path = self.scoped_proposals({'first_data': ['src/town/func_80000000.c'],
                                        'second_data': ['src/town/second.c']})
        proof = self.root / 'proof.json'
        self.run_names('--batch', '--rewrite', '--defer-verification', '--proof-log', str(proof),
                       '--symbol-scope-map', str(path))
        receipt = json.loads(proof.read_text())
        self.assertIsNone(receipt['map'])
        self.assertEqual(receipt['aliases'], {'first_data': 'D_80001234', 'second_data': 'D_80001234'})


if __name__ == "__main__":
    unittest.main()
