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



def lui(rt, value):
    return (0x0F << 26) | (rt << 16) | (((value + 0x8000) >> 16) & 0xFFFF)


def lo(op, rs, rt, value):
    return (op << 26) | (rs << 21) | (rt << 16) | (value & 0xFFFF)


LW, ADDIU = 0x23, 0x09
JR_RA, NOP = 0x03E00008, 0


def body(target, extra=None):
    """lui v0,%hi(target); lw v1,%lo(target)(v0); jr ra; nop (an optional extra target read through a0)."""
    words = [lui(2, target), lo(LW, 2, 3, target)]
    if extra is not None:
        words += [lui(4, extra), lo(LW, 4, 5, extra)]
    return words + [JR_RA, NOP]


class Relocations(unittest.TestCase):
    A, B = 0x8014C000, 0x80152000          # one module linked at two bases: delta 0x6000

    def test_lo_use_is_paired_with_its_lui_across_a_branch_and_an_index_add(self):
        words = [lui(2, 0x8014C040),                 # 0 lui v0
                 (4 << 26) | (4 << 21) | 2,          # 1 beq a0, zero, +2 (to 4)
                 NOP,                                # 2 delay slot
                 (0 << 26) | (2 << 21) | (5 << 16) | (2 << 11) | 0x21,   # 3 addu v0, v0, a1 (indexed)
                 lo(LW, 2, 3, 0x8014C040),           # 4 lw v1, %lo(v0)  (reached from 3 and from the branch)
                 JR_RA, NOP]
        sources = P.hi_sources(words, self.A)
        self.assertEqual(sources[4][2], frozenset([0]))
        moved = list(words)
        moved[0], moved[4] = lui(2, 0x80152040), lo(LW, 2, 3, 0x80152040)
        problems, pairs = P.relocations(words, moved, self.A, self.B)
        self.assertEqual(problems, [])
        self.assertEqual(pairs, [('hilo', 4, 0x8014C040, 0x80152040)])

    def test_a_call_ends_a_hi_part_in_a_caller_saved_register(self):
        words = [lui(2, 0x8014C040), (3 << 26) | 0x100, NOP, lo(LW, 2, 3, 0x8014C040), JR_RA, NOP]
        self.assertNotIn(2, P.hi_sources(words, self.A)[3])

    def test_one_non_relocation_word_refuses(self):
        canonical = body(self.A + 0x40) + [lo(ADDIU, 0, 4, 5)]
        copy = body(self.B + 0x40) + [lo(ADDIU, 0, 4, 6)]       # li a0, 5 / li a0, 6: a constant, not a field
        problems, _ = P.relocations(canonical, copy, self.A, self.B)
        self.assertEqual(len(problems), 1)
        self.assertIn('word 4: 24040005 != 24040006 is not a relocated field', problems[0])

    def test_a_lui_without_a_lo_use_refuses(self):
        canonical = [lui(2, 0x80150000), lo(0x0D, 2, 2, 0x1234), JR_RA, NOP]   # lui/ori: a constant
        copy = [lui(2, 0x80160000), lo(0x0D, 2, 2, 0x1234), JR_RA, NOP]
        problems, _ = P.relocations(canonical, copy, self.A, self.B)
        self.assertTrue(any('has no %lo use' in p for p in problems))

    def judge(self, canonical, copy, shift):
        problems, pairs = P.relocations(canonical, copy, self.A, self.B)
        self.assertEqual(problems, [])
        return P.judge(pairs, self.A, self.B, 4 * len(canonical), lambda *_: False, lambda kind, a, b: kind == 'jump',
                       shift, lambda code, a, b: [])

    def test_a_consistent_base_shift_is_accepted(self):
        self.assertEqual(self.judge(body(self.A + 0x40, self.A + 0x80), body(self.B + 0x40, self.B + 0x80), 0x6000), [])

    def test_an_inconsistent_shift_refuses(self):
        problems = self.judge(body(self.A + 0x40, self.A + 0x80), body(self.B + 0x40, self.B + 0x84), 0x6000)
        self.assertEqual(len(problems), 1)
        self.assertIn('shifts by +0x6004, not the base delta +0x6000', problems[0])

    def test_a_shift_without_a_base_relation_refuses(self):
        problems = self.judge(body(self.A + 0x40), body(self.B + 0x40), None)
        self.assertIn('no base shift applies', problems[0])

    def test_a_many_to_one_map_refuses(self):
        # the canonical reads two objects; the copy reads one object twice
        problems = self.judge(body(self.A + 0x40, self.A + 0x80), body(self.B + 0x40, self.B + 0x40), 0x6000)
        self.assertEqual(len(problems), 1)
        self.assertIn('is not one-to-one', problems[0])

    def test_a_shifted_target_whose_bytes_differ_refuses(self):
        problems, pairs = P.relocations(body(self.A + 0x40), body(self.B + 0x40), self.A, self.B)
        problems = P.judge(pairs, self.A, self.B, 16, lambda *_: False, lambda *_: False, 0x6000,
                           lambda code, a, b: ['the data differs'])
        self.assertIn('moves with the base delta but the data differs', problems[0])


class SameSymbol(unittest.TestCase):
    """Rows.same_symbol resolves a name per image: names.tsv keys by address, an address differs per image."""
    A, B = 0x8014C854, 0x80158854

    def rows(self, symbols, symbol_rows=None, functions=None, defined=None):
        r = P.Rows.__new__(P.Rows)
        r.symbols = symbols
        r.symbol_rows = symbol_rows or {k: 1 for k in symbols}
        r.paths, r.members = {}, {}
        r.texts = {}
        for row_id, text in (defined or {}).items():
            r.paths[row_id] = row_id + '.c'
            r.texts[row_id + '.c'] = text
        funcs = functions or {}
        r.function_at = lambda row, address: funcs.get((row['id'], address))
        return r

    def test_a_name_from_another_image_is_refused(self):
        # spawn_dragon names both addresses, but the canonical's image holds spawn_battnel_slot_a at 0x8014C854
        symbols = {('code', self.A): {'spawn_battnel_slot_a', 'spawn_dragon'}, ('code', self.B): {'spawn_dragon'}}
        battnel, dragon = dict(id='battnel'), dict(id='dragon')
        r = self.rows(symbols, functions={('canon', self.A): battnel, ('copy', self.B): dragon},
                      defined={'battnel': 'void spawn_battnel_slot_a(void) {\n}\n',
                               'dragon': 'void spawn_dragon(void) {\n}\n'})
        self.assertFalse(r.same_symbol('code', self.A, self.B, dict(id='canon'), dict(id='copy')))
        # and without the images it cannot resolve, so it does not accept
        self.assertFalse(r.same_symbol('code', self.A, self.B))

    def test_a_same_name_match_in_both_images_is_accepted(self):
        symbols = {('code', self.A): {'spawn_dragon'}, ('code', self.B): {'spawn_dragon'}}
        one, two = dict(id='one'), dict(id='two')
        r = self.rows(symbols, functions={('canon', self.A): one, ('copy', self.B): two},
                      defined={'one': 'void spawn_dragon(void) {\n}\n', 'two': 'void spawn_dragon(void) {\n}\n'})
        self.assertTrue(r.same_symbol('code', self.A, self.B, dict(id='canon'), dict(id='copy')))
        # an address no image function starts at is not accepted
        r.function_at = lambda row, address: None
        self.assertFalse(r.same_symbol('code', self.A, self.B, dict(id='canon'), dict(id='copy')))

    def test_a_data_name_counts_only_for_a_single_row_address(self):
        symbols = {('data', 0x8014FC7C): {'frames'}, ('data', 0x8015BC7C): {'frames'}}
        self.assertTrue(self.rows(symbols).same_symbol('data', 0x8014FC7C, 0x8015BC7C))
        several = {('data', 0x8014FC7C): 2, ('data', 0x8015BC7C): 1}
        self.assertFalse(self.rows(symbols, several).same_symbol('data', 0x8014FC7C, 0x8015BC7C))
        self.assertFalse(self.rows(symbols, {('data', 0x8014FC7C): 1, ('data', 0x8015BC7C): 3})
                         .same_symbol('data', 0x8014FC7C, 0x8015BC7C))

    def test_the_base_shift_decides_before_a_name_and_is_still_accepted(self):
        pairs = [('jump', 0, self.A + 0x40, self.A + 0x40 + 0x6000)]
        start_a, start_b = self.A, self.A + 0x6000
        named = lambda kind, a, b: True            # a name match must not rescue a shifted pair whose bytes differ
        problems = P.judge(pairs, start_a, start_b, 16, named, lambda *_: True, 0x6000, lambda code, a, b: ['body differs'])
        self.assertIn('moves with the base delta but body differs', problems[0])
        self.assertEqual(P.judge(pairs, start_a, start_b, 16, lambda *_: False, lambda *_: True, 0x6000,
                                 lambda code, a, b: []), [])
        # off the base delta the name rule still applies
        other = [('jump', 0, self.A + 0x40, self.A + 0x80)]
        self.assertEqual(P.judge(other, start_a, start_b, 16, named, lambda *_: True, 0x6000, lambda *_: ['no']), [])


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

    def shifted_fixture(self, root, copy_words, copy_data=b'\x11\x22\x33\x44' * 4):
        """Two one-member native modules with one layout: the canonical at 0x8014C000 (file 0x000, its data at
        +0x40) and the copy at 0x80152000 (file 0x100, its data at +0x40)."""
        import json
        import struct
        for d in ('config/overlays', 'ledger', 'src', P.CONTAINER_DIR):
            (root / d).mkdir(parents=True, exist_ok=True)
        image = bytearray(0x200)
        image[0x000:0x010] = struct.pack('<4I', *body(0x8014C040))
        image[0x040:0x050] = b'\x11\x22\x33\x44' * 4
        image[0x100:0x110] = struct.pack('<4I', *copy_words)
        image[0x140:0x150] = copy_data
        for c in P.CONTAINERS.values():
            (root / P.CONTAINER_DIR / c).write_bytes(bytes(image))
        (root / 'config/names.tsv').write_text('0x8014C000\tfunc_8014C000\tfirst\tcanonical\n'
                                               '0x80152000\tfunc_80152000\tfirst\tcopy_of=0x8014C000; same\n')
        rows = [dict(id='dungeon/func_A', true_name='func_8014C000', container='dungeon', foff=0, size=16),
                dict(id='dungeon/func_B', true_name='func_80152000', container='dungeon', foff=0x100, size=16)]
        (root / 'ledger/rows.jsonl').write_text(''.join(json.dumps(r) + '\n' for r in rows))
        (root / 'ledger/layout.jsonl').write_text(json.dumps(dict(id='dungeon/func_A', path='src/a.c')) + '\n'
                                                  + json.dumps(dict(id='dungeon/func_B', path='src/b.c')) + '\n')
        (root / 'src/a.c').write_text('void first(void) {\n}\n')
        (root / 'src/b.c').write_text('void first(void) {\n}\n')
        modules = [dict(key='a', members=[dict(id='dungeon/func_A', source='src/a.c', function='func_8014C000',
                                                foff=0, size=16)]),
                   dict(key='b', members=[dict(id='dungeon/func_B', source='src/b.c', function='func_80152000',
                                                foff=0x100, size=16)])]
        (root / 'config/overlays/modules.json').write_text(json.dumps(dict(modules=modules)))

    def test_a_copy_whose_data_moved_with_its_module_is_accepted(self):
        import tempfile
        with tempfile.TemporaryDirectory() as td:
            root = Path(td)
            self.shifted_fixture(root, body(0x80152040))
            details = {}
            report, problems = P.check(root, [], details)
            self.assertEqual(problems, [])
            self.assertEqual(details[('first', 'func_80152000')],
                             'words differing in relocated fields: 1, base delta +0x6000')

    def test_a_copy_whose_shifted_data_differs_is_refused(self):
        import tempfile
        with tempfile.TemporaryDirectory() as td:
            root = Path(td)
            self.shifted_fixture(root, body(0x80152040), copy_data=b'\x99' * 16)
            problems = P.check(root)[1]
            self.assertEqual(len(problems), 1)
            self.assertIn('moves with the base delta but the data differs', problems[0])

    def test_a_copy_reading_another_object_is_refused(self):
        import tempfile
        with tempfile.TemporaryDirectory() as td:
            root = Path(td)
            self.shifted_fixture(root, body(0x80152044))
            problems = P.check(root)[1]
            self.assertIn('shifts by +0x6004, not the base delta +0x6000', problems[0])

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
