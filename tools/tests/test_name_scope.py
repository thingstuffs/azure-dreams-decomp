"""name_scope: the scope grammar, the location of an object, the lookup by address + scope, and that every
config/names.tsv reader and writer that must carry the optional 5th column does."""
import sys
import tempfile
import unittest
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / 'tools'))
sys.path.insert(0, str(ROOT / 'tools/lint'))
import name_scope as S  # noqa: E402

L = S.Location


def row(rid, container, foff, size, true_name, source_row=None):
    r = dict(id=rid, container=container, foff=foff, size=size, true_name=true_name, func=rid.split('/')[1])
    if source_row:
        r['source_row'] = source_row
    return r


class Grammar(unittest.TestCase):
    def test_parse_and_format_round_trip(self):
        self.assertEqual(S.parse_scope(''), ())
        self.assertEqual(S.parse_scope('town:0x51E0F8'), (L('town', 0x51E0F8),))
        two = S.parse_scope('dungeon:0x188E87C,dungeon:0x191E87C')
        self.assertEqual(two, (L('dungeon', 0x188E87C), L('dungeon', 0x191E87C)))
        self.assertEqual(S.format_scope(reversed(two)), 'dungeon:0x188E87C,dungeon:0x191E87C')
        self.assertEqual(S.format_scope([L('town', 255), L('town', 255)]), 'town:0xFF')

    def test_malformed_cells_refuse(self):
        for bad in ('town:51E0F8', 'town:0x', 'disc:0x10', 'town:0x10, town:0x20', 'town:0x10,', ',town:0x10',
                    'town:0x20,town:0x10', 'town:0x10,town:0x10', 'town:0x10#x', ' town:0x10'):
            with self.subTest(bad):
                with self.assertRaises(S.ScopeError):
                    S.parse_scope(bad)


class Fixture(unittest.TestCase):
    """Two scene images load at 0x80016000 (as the town scenes do); a third places a copy of the first one's body."""

    def setUp(self):
        self.rows = [
            row('town/func_A', 'town', 0x100000, 0x40, 'func_80016000'),
            row('town/func_B', 'town', 0x200000, 0x40, 'func_80016000'),
            row('town/func_C', 'town', 0x300000, 0x40, 'func_80016000', source_row='town/func_A'),
            row('town/func_D', 'town', 0x400040, 0x10, 'func_80016040'),
            row('slus/code', 'slus', None, 0x100, None),
        ]
        self.g = S.Geometry('.', rows=self.rows)

    def test_location_of_normalises_a_placement_to_its_home(self):
        self.assertEqual(self.g.location_of('town/func_A', 0x80016010), L('town', 0x100010))
        self.assertEqual(self.g.location_of('town/func_B', 0x80016010), L('town', 0x200010))
        self.assertEqual(self.g.location_of('town/func_C', 0x80016010), L('town', 0x100010))
        self.assertIsNone(self.g.location_of('town/func_A', 0x80016040))         # outside the row
        self.assertIsNone(self.g.location_of('slus/code', 0x80016010))           # the slus container has no offset

    def test_owner_is_the_home_row_holding_the_location(self):
        self.assertEqual(self.g.owner(L('town', 0x100010)), ('town/func_A', 'town/func_A'))
        self.assertEqual(self.g.owner(L('town', 0x200000)), ('town/func_B', 'town/func_B'))
        self.assertIsNone(self.g.owner(L('town', 0x300000)))     # a placement is not a home row
        self.assertIsNone(self.g.owner(L('dungeon', 0x100000)))

    def test_objects_at_counts_homes_not_placements(self):
        self.assertEqual(self.g.objects_at(0x80016000), {'town/func_A', 'town/func_B'})
        self.assertTrue(self.g.multi_object(0x80016000))
        self.assertFalse(self.g.multi_object(0x80016040))

    def test_name_at_is_per_location_and_never_another_images_name(self):
        text = ('# comment\n'
                '0x80016000\tfunc_80016000\tfirst_body\tev\ttown:0x100000\n'
                '0x80016000\tfunc_80016000\tsecond_body\tev\ttown:0x200000\n'
                '0x80016040\tfunc_80016040\tonly_body\tev\n')
        t = S.NameTable.parse(text)
        self.assertEqual(t.name_at('func_80016000', L('town', 0x100000), self.g), 'first_body')
        self.assertEqual(t.name_at('func_80016000', L('town', 0x200000), self.g), 'second_body')
        self.assertIsNone(t.name_at('func_80016000', L('town', 0x999999), self.g))
        self.assertEqual(t.name_at('func_80016040', L('town', 0x400040), self.g), 'only_body')

    def test_unscoped_row_at_a_multi_object_address_answers_unknown(self):
        t = S.NameTable.parse('0x80016000\tfunc_80016000\tfirst_body\tev\n')
        self.assertIsNone(t.name_at('func_80016000', L('town', 0x100000), self.g))
        self.assertEqual(t.name_at('func_80016000', L('town', 0x100000)), 'first_body')    # no geometry given

    def test_a_malformed_scope_is_kept_as_an_error_not_raised(self):
        t = S.NameTable.parse('0x80016000\tfunc_80016000\tn\tev\ttown:100000\n')
        self.assertEqual(len(t.errors), 1)
        self.assertEqual(t.rows[0].scope, ())


@unittest.skipUnless((ROOT / 'ledger/rows.jsonl').is_file() and (ROOT / 'config/names.tsv').is_file(), 'no ledger')
class WorkedExamples(unittest.TestCase):
    """The worked examples of the name-scope design, against the tree's own ledger."""

    @classmethod
    def setUpClass(cls):
        cls.g = S.Geometry(ROOT)
        cls.t = S.NameTable.read(ROOT)

    def test_town_scene_address_six_homes(self):
        want = {'town/func_806CF0F8': 0x64F0F8, 'town/func_806CB0F8': 0x64B0F8, 'town/func_8074C8F8': 0x6CC8F8,
                'town/func_806010F8': 0x5810F8, 'town/func_8067F0F8': 0x5FF0F8, 'town/func_8059E0F8': 0x51E0F8}
        for rid, foff in want.items():
            with self.subTest(rid):
                loc = self.g.location_of(rid, 0x800160F8)
                self.assertEqual(loc, L('town', foff))
                self.assertEqual(self.g.owner(loc)[0], rid)
        self.assertGreaterEqual(len(self.t.by_addr[0x800160F8]), 6)
        self.assertTrue(self.g.multi_object(0x800160F8))

    def test_placed_copy_resolves_to_its_home(self):
        # town/func_806CD0F8 (a placement at 0x800160F8) is a copy of town/func_806CB0F8
        self.assertEqual(self.g.location_of('town/func_806CD0F8', 0x800160F8), L('town', 0x64B0F8))
        # a placement of a body whose home sits at another load address keeps the offset within the body
        self.assertEqual(self.g.location_of('town/func_805000F8', 0x800160F8),
                         L('town', self.g.home('town/func_805000F8')['foff']))

    def test_selector_images_three_locations(self):
        for off in (0x188E87C, 0x191E87C, 0x198A87C):
            with self.subTest(hex(off)):
                self.assertIsNotNone(self.g.owner(L('dungeon', off)))
        self.assertTrue(self.g.multi_object(0x8002407C))

    def test_monster_bank_slots_five_locations(self):
        for off in (0xB6307C, 0xA6707C, 0xABB07C, 0xCB307C, 0xC5F07C):
            with self.subTest(hex(off)):
                self.assertIsNotNone(self.g.owner(L('dungeon', off)))
        self.assertTrue(self.g.multi_object(0x8017087C))

    def test_two_resident_engines(self):
        self.assertEqual(self.g.owner(L('town', 0x229F0))[0], 'town/func_800A29F0')
        self.assertEqual(self.g.owner(L('dungeon', 0xBA9F0))[0], 'dungeon/func_8009A9F0')
        self.assertTrue(self.g.multi_object(0x800A0150))

    def test_devkit_card_server_row_spells_another_address(self):
        # the row id spells 0x8001B3C4; the code runs at 0x804023C4 and sits at main:0x26B3C4
        self.assertEqual(self.g.location_of('main/func_8001B3C4', 0x804023C4), L('main', 0x26B3C4))

    def test_name_at_with_scopes_built_from_the_geometry(self):
        # the three functions the dragon placed-copy case names at 0x80170A44, each given the scope of a home row
        homes = [r for r in self.g.rows_containing(0x80170A44) if self.g.base_of(r) == 0x80170A44][:3]
        locs = sorted({self.g.location_of(self.g.home(r['id'])['id'], 0x80170A44) or
                       L(self.g.home(r['id'])['container'], self.g.home(r['id'])['foff']) for r in homes})
        text = ''.join('0x80170A44\tfunc_80170A44\tname_%d\tev\t%s\n' % (i, loc) for i, loc in enumerate(locs))
        t = S.NameTable.parse(text)
        for i, loc in enumerate(locs):
            self.assertEqual(t.name_at('func_80170A44', loc, self.g), 'name_%d' % i)


class ColumnCarried(unittest.TestCase):
    """Each reader or writer of config/names.tsv that must keep the 5th column keeps it."""

    LINE4 = '0x80016000\tfunc_80016000\tcopy_name\tsrc/town/a.c: does it\n'
    LINE5 = LINE4.rstrip('\n') + '\ttown:0x100000\n'

    def test_clone_names_keeps_the_scope(self):
        sys.path.insert(0, str(ROOT / 'tools/typing'))
        import clone_names
        out = clone_names.names_row(self.LINE5, '0x80016000'.replace('0x', 'func_'), 'copy_name', 'new_name',
                                    'func_80016040', 12, 'src/town/b.c')
        cols = out.rstrip('\n').split('\t')
        self.assertEqual(len(cols), 5)
        self.assertEqual(cols[4], 'town:0x100000')
        self.assertTrue(cols[3].startswith('copy_of=0x80016040;'))
        four = clone_names.names_row(self.LINE4, 'func_80016000', 'copy_name', 'new_name', 'func_80016040', 12,
                                     'src/town/b.c')
        self.assertEqual(len(four.rstrip('\n').split('\t')), 4)

    def test_apply_names_reads_and_writes_the_scope(self):
        import apply_names
        with tempfile.TemporaryDirectory() as td:
            path = Path(td) / 'names.tsv'
            path.write_text(self.LINE4 + self.LINE5.replace('copy_name', 'other'))
            real, apply_names.NAMES = apply_names.NAMES, path
            try:
                rows = apply_names.read_names()
            finally:
                apply_names.NAMES = real
        self.assertEqual([r[4] for r in rows], ['', 'town:0x100000'])
        self.assertEqual(apply_names.names_line('0x1', 'a', 'b', 'e'), '0x1\ta\tb\te\n')
        self.assertEqual(apply_names.names_line('0x1', 'a', 'b', 'e', 'town:0x10'), '0x1\ta\tb\te\ttown:0x10\n')

    def test_ledger_refresh_reads_five_column_rows(self):
        import ledger_refresh as R
        rows = R.read_names(self.LINE5)
        self.assertEqual(rows, [('0x80016000', 'func_80016000', 'copy_name', 'src/town/a.c: does it')])

    def test_ledger_refresh_rewrites_evidence_and_keeps_the_scope(self):
        import ledger_refresh as R

        class Tree:
            defined = {}

        class Run:
            tree = Tree()
            notes = []

            def text(self, ledger, where, evidence, own, name, base):
                return evidence + ' (refreshed)'

            def base_evidence(self, cols):
                return None

            def note(self, *args):
                self.notes.append(args)

        class Files:
            written = None

            def read(self, path):
                return '# header\n' + ColumnCarried.LINE4 + ColumnCarried.LINE5.replace('copy_name', 'other')

            def set(self, path, text):
                self.written = text

        files = Files()
        R.names_ledger(Run(), files)
        lines = files.written.split('\n')
        self.assertEqual(lines[1].split('\t')[3], 'src/town/a.c: does it (refreshed)')
        cols = lines[2].split('\t')
        self.assertEqual((len(cols), cols[3], cols[4]), (5, 'src/town/a.c: does it (refreshed)', 'town:0x100000'))

    def test_address_names_keeps_the_scope(self):
        sys.path.insert(0, str(ROOT / 'tools/headers'))
        import address_names
        with tempfile.TemporaryDirectory() as td:
            root = Path(td)
            (root / 'config').mkdir()
            (root / 'config/names.tsv').write_text(self.LINE5)
            row = dict(kind='home_self', new='copy_name', link='func_800160F8>func_80016000', evidence='', file='x.c',
                       old='o', symbol='s', calls='', images='', new_header='')
            address_names.link_records(root, [row])
            text = (root / 'config/names.tsv').read_text()
        cols = text.rstrip('\n').split('\t')
        self.assertEqual(cols[:3], ['0x80016000', 'func_80016000', 'copy_name'])
        self.assertEqual(cols[-1], 'town:0x100000')
        self.assertEqual(len(cols), 5)


if __name__ == '__main__':
    unittest.main()
