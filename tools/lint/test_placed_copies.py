"""placed_copies: a recorded copy must be the same words, a jump within its own body aside."""
import sys
import unittest
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import placed_copies as P  # noqa: E402

A, B = 0x80024B3C, 0x8002512C


def j(op, target):
    return (op << 26) | ((target >> 2) & 0x03FFFFFF)


class Compare(unittest.TestCase):
    def test_identical_words_and_self_relative_jumps_are_one_function(self):
        canonical = [0x27BDFFE8, j(2, A + 8), 0x00000000, j(3, 0x80060000)]
        copy = [0x27BDFFE8, j(2, B + 8), 0x00000000, j(3, 0x80060000)]
        self.assertEqual(P.compare(canonical, copy, A, B), [])

    def test_any_other_difference_refuses(self):
        canonical = [0x27BDFFE8, j(2, A + 8), 0x00000000, j(3, 0x80060000)]
        cases = {
            'other instruction': [0x27BDFFE0, j(2, B + 8), 0x00000000, j(3, 0x80060000)],
            'jump to another offset': [0x27BDFFE8, j(2, B + 12), 0x00000000, j(3, 0x80060000)],
            'call to another target': [0x27BDFFE8, j(2, B + 8), 0x00000000, j(3, 0x80060010)],
            'jump outside the body': [0x27BDFFE8, j(2, B + 64), 0x00000000, j(3, 0x80060000)],
            'size': [0x27BDFFE8, j(2, B + 8), 0x00000000],
        }
        for label, copy in cases.items():
            with self.subTest(label):
                self.assertTrue(P.compare(canonical, copy, A, B))

    def test_definition_finder_skips_declarations_and_calls(self):
        text = P.strip_comments('s32 f(void);\n/* s32 f(void) { */\nvoid g(void) {\n    x = f();\n}\n')
        self.assertFalse(P.defines(text, 'f'))
        self.assertTrue(P.defines(text + 's32 f(void) {\n    return 1;\n}\n', 'f'))
        self.assertTrue(P.defines('s32 f(a)\n    s32 a;\n{\n    return a;\n}\n', 'f'))


    def test_definition_body_is_found_for_the_placement_rule(self):
        text = P.strip_comments('void f(void);\nvoid g(void) {\n    f();\n}\nvoid f(void) {\n    if (x) { y(); }\n}\n')
        self.assertEqual(P.definition(text, 'g'), '{\n    f();\n}')
        self.assertEqual(P.definition(text, 'f'), '{\n    if (x) { y(); }\n}')
        self.assertIsNone(P.definition(text, 'h'))


class Check(unittest.TestCase):
    NAMES = ('0x80040000\tfunc_80040000\tfirst\tcanonical\n'
             '0x80016000\tfunc_80016000\tfirst\tcopy_of=0x80040000; same\n')

    def fixture(self, root, containers=True, words=None):
        import json
        for d in ('config/overlays', 'ledger', 'src'):
            (root / d).mkdir(parents=True, exist_ok=True)
        if containers:
            (root / P.CONTAINER_DIR).mkdir(parents=True, exist_ok=True)
            for c in P.CONTAINERS.values():
                (root / P.CONTAINER_DIR / c).write_bytes(words or bytes(64))
        (root / 'config/names.tsv').write_text(self.NAMES)
        rows = [dict(id='dungeon/func_A', true_name='func_80040000', container='dungeon', foff=0, size=8),
                dict(id='dungeon/func_B', true_name='func_80016000', container='dungeon', foff=16, size=8)]
        (root / 'ledger/rows.jsonl').write_text(''.join(json.dumps(r) + '\n' for r in rows))
        (root / 'ledger/layout.jsonl').write_text(json.dumps(dict(id='dungeon/func_A', path='src/a.c')) + '\n'
                                                  + json.dumps(dict(id='dungeon/func_B', path='src/b.c')) + '\n')
        (root / 'src/a.c').write_text('void first(void) {\n}\n')
        (root / 'src/b.c').write_text('void first(void) {\n}\n')
        modules = dict(modules=[dict(members=[dict(id='dungeon/func_A', foff=0, size=8)])])
        (root / 'config/overlays/modules.json').write_text(json.dumps(modules))
        return modules

    def add_member(self, root, modules):
        import json
        modules['modules'][0]['members'].append(dict(id='dungeon/func_B', foff=16, size=8))
        (root / 'config/overlays/modules.json').write_text(json.dumps(modules))

    def test_a_copy_that_is_not_a_native_module_entry_is_refused(self):
        import tempfile
        with tempfile.TemporaryDirectory() as td:
            root = Path(td)
            modules = self.fixture(root)
            notes = []
            report, problems = P.check(root, notes)
            self.assertEqual(len(problems), 1)
            self.assertIn('not a native module entry', problems[0])
            self.assertEqual(notes, [])
            self.add_member(root, modules)
            self.assertEqual(P.check(root)[1], [])

    def test_with_the_containers_differing_words_refuse(self):
        import tempfile
        with tempfile.TemporaryDirectory() as td:
            root = Path(td)
            modules = self.fixture(root, words=bytes(16) + bytes([1]) + bytes(47))
            self.add_member(root, modules)
            problems = P.check(root)[1]
            self.assertEqual(len(problems), 1)
            self.assertIn('differs from func_80040000: word 0', problems[0])

    def test_without_the_containers_words_are_skipped_and_structure_still_checked(self):
        import tempfile
        with tempfile.TemporaryDirectory() as td:
            root = Path(td)
            modules = self.fixture(root, containers=False)
            notes = []
            report, problems = P.check(root, notes)
            # structural refusal still runs in a public checkout
            self.assertEqual(len(problems), 1)
            self.assertIn('not a native module entry', problems[0])
            self.assertEqual(len(notes), 1)
            self.assertIn(P.SKIPPED, notes[0])
            self.add_member(root, modules)
            notes = []
            report, problems = P.check(root, notes)
            self.assertEqual(problems, [])
            self.assertIn(P.SKIPPED, notes[0])
            self.assertEqual(report['first'], [('func_80040000', 'src/a.c', 8), ('func_80016000', 'src/b.c', 8)])
            # a row at a family address that does not define the name is a problem without containers too
            (root / 'src/b.c').write_text('void other(void) {\n}\n')
            self.assertIn('0 rows at func_80016000 define it', P.check(root)[1][0])

    def test_a_malformed_copy_record_is_refused(self):
        import tempfile
        with tempfile.TemporaryDirectory() as td:
            root = Path(td)
            (root / 'config').mkdir()
            for bad in ('copy_of=0x80040abc; lowercase', 'copy_of=80040000; no 0x', 'copy_of=0x8004000; seven'):
                (root / 'config/names.tsv').write_text('0x80040000\tfunc_80040000\tfirst\tcanonical\n'
                                                       '0x80016000\tfunc_80016000\tfirst\t' + bad + '\n')
                with self.subTest(bad=bad):
                    problems = P.check(root)[1]
                    self.assertEqual(len(problems), 1)
                    self.assertIn('names.tsv:2: malformed copy_of record', problems[0])

    def test_without_families_nothing_is_noted(self):
        import tempfile
        with tempfile.TemporaryDirectory() as td:
            root = Path(td)
            (root / 'config').mkdir()
            (root / 'config/names.tsv').write_text('0x80040000\tfunc_80040000\tfirst\tcanonical\n')
            notes = []
            self.assertEqual(P.check(root, notes), ({}, []))
            self.assertEqual(notes, [])


if __name__ == '__main__':
    unittest.main()
