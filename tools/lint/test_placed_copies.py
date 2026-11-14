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
    def test_a_copy_that_is_not_a_native_module_entry_is_refused(self):
        import json, tempfile
        with tempfile.TemporaryDirectory() as td:
            root = Path(td)
            for d in ('config/overlays', 'ledger', 'work/disc/containers', 'src'):
                (root / d).mkdir(parents=True)
            for c in P.CONTAINERS.values():
                (root / 'work/disc/containers' / c).write_bytes(bytes(64))
            (root / 'config/names.tsv').write_text('0x80040000\tfunc_80040000\tfirst\tcanonical\n'
                                                   '0x80016000\tfunc_80016000\tfirst\tcopy_of=0x80040000; same\n')
            rows = [dict(id='dungeon/func_A', true_name='func_80040000', container='dungeon', foff=0, size=8),
                    dict(id='dungeon/func_B', true_name='func_80016000', container='dungeon', foff=16, size=8)]
            (root / 'ledger/rows.jsonl').write_text(''.join(json.dumps(r) + '\n' for r in rows))
            (root / 'ledger/layout.jsonl').write_text(json.dumps(dict(id='dungeon/func_A', path='src/a.c')) + '\n'
                                                      + json.dumps(dict(id='dungeon/func_B', path='src/b.c')) + '\n')
            (root / 'src/a.c').write_text('void first(void) {\n}\n')
            (root / 'src/b.c').write_text('void first(void) {\n}\n')
            modules = dict(modules=[dict(members=[dict(id='dungeon/func_A', foff=0, size=8)])])
            (root / 'config/overlays/modules.json').write_text(json.dumps(modules))
            report, problems = P.check(root)
            self.assertEqual(len(problems), 1)
            self.assertIn('not a native module entry', problems[0])
            modules['modules'][0]['members'].append(dict(id='dungeon/func_B', foff=16, size=8))
            (root / 'config/overlays/modules.json').write_text(json.dumps(modules))
            self.assertEqual(P.check(root)[1], [])

    def test_a_family_without_retail_containers_is_a_problem_not_a_crash(self):
        import tempfile
        with tempfile.TemporaryDirectory() as td:
            root = Path(td)
            (root / 'config').mkdir()
            (root / 'config/names.tsv').write_text('0x80040000\tfunc_80040000\tfirst\tcanonical\n'
                                                   '0x80016000\tfunc_80016000\tfirst\tcopy_of=0x80040000; same\n')
            report, problems = P.check(root)
            self.assertEqual(report, {})
            self.assertEqual(len(problems), 1)
            self.assertIn('retail containers are missing', problems[0])
            (root / 'config/names.tsv').write_text('0x80040000\tfunc_80040000\tfirst\tcanonical\n')
            self.assertEqual(P.check(root), ({}, []))


if __name__ == '__main__':
    unittest.main()
