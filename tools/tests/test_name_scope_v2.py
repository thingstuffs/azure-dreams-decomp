"""name_scope v2: real load addresses, the real images, placement normalisation, renormalise, the lint rules and the
ratchet, on a synthetic tree (no retail bytes)."""
import json
import subprocess
import sys
import tempfile
import unittest
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / 'tools'))
sys.path.insert(0, str(ROOT / 'tools/lint'))
import name_scope as S  # noqa: E402
import name_scope_check as C  # noqa: E402

L = S.Location


def row(rid, foff, size, true_name, source_row=None, container='town', **extra):
    r = dict(id=rid, container=container, foff=foff, size=size, true_name=true_name, func=rid.split('/')[1])
    if source_row:
        r['source_row'] = source_row
    r.update(extra)
    return r


def view(name, foff, size, vma, entries=(), container='town'):
    return dict(schema='azure-clean.linklist.v1', image=name, container=container, foff=hex(foff), size=hex(size),
                vma=hex(vma), entries=list(entries))


def entry(rid, home, foff, vma, size, **extra):
    return dict(row=rid, home=home, tu='src/x.c', foff=hex(foff), vma=hex(vma), size=size, **extra)


ROWS = [
    row('town/func_A', 0x100000, 0x40, 'func_80016000'),
    row('town/func_B', 0x200000, 0x40, 'func_80016000'),
    row('town/func_C', 0x300000, 0x40, 'func_80016000', source_row='town/func_A'),
    row('town/func_N', 0x500010, 0x20, None),                       # no true name: the image gives its address
    row('town/func_S', 0x510000, 0x20, 'func_7FFE0000'),            # a row-space spelling is no load address
    row('town/func_H', 0x400000, 0x100, 'func_80017000'),           # body offset home (its own entry)
    row('town/func_P', 0x410000, 0x20, 'func_80017000', source_row='town/func_H'),
    row('town/func_Z', 0x420000, 0x20, 'func_80016040'),
    row('town/D_obj', 0x600010, 0x10, None, data_kind='words'),
]
VIEWS = [
    view('town/img_A', 0x100000, 0x1000, 0x80016000, [entry('town/func_A', 'town/func_A', 0x100000, 0x80016000, 0x40)]),
    view('town/img_B', 0x200000, 0x1000, 0x80016000, [entry('town/func_B', 'town/func_B', 0x200000, 0x80016000, 0x40)]),
    view('town/img_C', 0x300000, 0x1000, 0x80016000, [entry('town/func_C', 'town/func_A', 0x300000, 0x80016000, 0x40)]),
    view('town/img_N', 0x500000, 0x1000, 0x80016100),
    view('town/img_S', 0x510000, 0x1000, 0x7FFE0000 + 0x510000 - 0x500000 + 0x1000),   # pseudo: row space
    view('town/img_H', 0x400000, 0x1000, 0x80017000, [
        entry('town/func_H', 'town/func_H', 0x400000, 0x80017000, 0x100, body_offset=0x10),
        entry('town/func_P', 'town/func_H', 0x410000, 0x80017010, 0xF0)]),
    view('town/img_D', 0x700000, 0x1000, 0x80090000),
    view('town/img_Z', 0x420000, 0x1000, 0x80016040, [entry('town/func_Z', 'town/func_Z', 0x420000, 0x80016040, 0x20)]),
]
REGIONS = [dict(container='town', foff=0x600000, size=0x1000, base=0x80090000)]
LAYOUT = {'town/func_A': 'src/a.c', 'town/func_B': 'src/b.c', 'town/func_Z': 'src/z.c', 'town/func_H': 'src/h.c'}
SOURCES = {'src/a.c': 'void alpha(void)\n{\n}\n', 'src/b.c': 'void beta(void)\n{\n}\nvoid beta2(void)\n{\n}\n',
           'src/z.c': 'void zed(void)\n{\n}\n', 'src/h.c': 'void hh(void)\n{\n}\n'}


def write_tree(root, names, rows=ROWS, views=VIEWS, regions=REGIONS, layout=LAYOUT, extra=None):
    root = Path(root)
    for d in ('config/link/town', 'ledger/modules', 'config/link_graph', 'src', 'config', 'tools/lint'):
        (root / d).mkdir(parents=True, exist_ok=True)
    (root / 'ledger/rows.jsonl').write_text(''.join(json.dumps(r) + '\n' for r in rows))
    for v in views:
        (root / 'config/link/town' / (v['image'].split('/')[1] + '.json')).write_text(json.dumps(v))
    (root / 'ledger/instance_load_regions.jsonl').write_text(''.join(json.dumps(r) + '\n' for r in regions))
    (root / 'ledger/layout.jsonl').write_text(''.join(json.dumps(dict(id=k, path=v)) + '\n' for k, v in layout.items()))
    for p, text in SOURCES.items():
        (root / p).write_text(text)
    (root / 'config/names.tsv').write_text(names)
    for p, text in (extra or {}).items():
        (root / p).parent.mkdir(parents=True, exist_ok=True)
        (root / p).write_text(text)
    return root


class Real(unittest.TestCase):
    def setUp(self):
        self.td = tempfile.TemporaryDirectory()
        self.root = write_tree(self.td.name, '')
        self.g = S.Geometry(self.root)

    def tearDown(self):
        self.td.cleanup()

    def test_base_is_the_real_entry_then_the_image_delta_then_the_true_name(self):
        base = lambda rid: self.g.base_of(self.g.rows[rid])
        self.assertEqual(base('town/func_A'), 0x80016000)
        self.assertEqual(base('town/func_N'), 0x80016110)        # no entry, no true name: the image's delta
        self.assertEqual(base('town/D_obj'), 0x80090010)         # the region's delta
        self.assertIsNone(base('town/func_S'))                   # a row-space spelling is never used
        self.assertIsNone(S.Geometry('.', rows=[row('town/func_80123456', 0x10, 8, None)]).base_of(
            row('town/func_80123456', 0x10, 8, None)))           # nor is the spelling of the id

    def test_pseudo_images_are_not_real(self):
        names = {im.name for im in self.g.images.real}
        self.assertNotIn('town/img_S', names)
        self.assertIn('region:town:0x600000', names)

    def test_location_of_applies_the_body_shift_of_a_body_only_copy(self):
        self.assertEqual(self.g.location_of('town/func_P', 0x80017010), L('town', 0x400010))
        self.assertEqual(self.g.location_of('town/func_P', 0x80017014), L('town', 0x400014))
        self.assertEqual(self.g.location_of('town/func_N', 0x80016110), L('town', 0x500010))

    def test_normalise_maps_a_location_in_a_placed_copy_to_its_home(self):
        self.assertEqual(self.g.normalise(L('town', 0x300010)), L('town', 0x100010))
        self.assertEqual(self.g.normalise(L('town', 0x410004)), L('town', 0x400014))
        self.assertEqual(self.g.normalise(L('town', 0x100010)), L('town', 0x100010))
        self.assertTrue(self.g.in_placement(L('town', 0x300000)))
        self.assertFalse(self.g.in_placement(L('town', 0x200000)))

    def test_data_objects_are_image_locations(self):
        locs = self.g.images.locations_of(0x80090010)
        self.assertEqual(set(locs), {L('town', 0x600010), L('town', 0x700010)})
        self.assertTrue(self.g.multi_object(0x80090010, 'data'))
        self.assertFalse(self.g.multi_object(0x80017800, 'data'))

    def test_name_at_normalises_and_requires_an_entry_at_the_address(self):
        t = S.NameTable.parse('0x80016040\tfunc_80016040\tzed_name\tev\n'
                              '0x80016000\tfunc_80016000\tfirst\tev\ttown:0x100000\n')
        self.assertEqual(t.name_at('func_80016000', L('town', 0x300000), self.g), 'first')     # via the placement
        self.assertEqual(t.name_at('func_80016040', L('town', 0x420000), self.g), 'zed_name')
        self.assertIsNone(t.name_at('func_80016040', L('town', 0x420004), self.g))             # no entry starts there
        scoped_elsewhere = S.NameTable.parse('0x80016040\tfunc_80016040\ta\tev\n'
                                             '0x80016040\tfunc_80016040\tb\tev\ttown:0x999999\n')
        self.assertIsNone(scoped_elsewhere.name_at('func_80016040', L('town', 0x420000), self.g))


class Renormalise(unittest.TestCase):
    def setUp(self):
        self.g = S.Geometry('.', rows=ROWS, images=S.Images.read(self.fixture()))

    def fixture(self):
        self.td = tempfile.TemporaryDirectory()
        self.addCleanup(self.td.cleanup)
        return write_tree(self.td.name, '')

    def test_moves_only_column_five_and_keeps_every_other_byte(self):
        text = ('# head\n0x80016000\tfunc_80016000\tfirst\tev; text\ttown:0x200010,town:0x300010\textra\n'
                '0x80016100\tfunc_80016100\tplain\tev\n')
        new, changes, refusals = S.renormalise_text(text, self.g)
        self.assertEqual(refusals, [])
        self.assertEqual(changes, [(2, 'town:0x200010,town:0x300010', 'town:0x100010,town:0x200010')])
        self.assertEqual(new.split('\n')[1], '0x80016000\tfunc_80016000\tfirst\tev; text\t'
                                              'town:0x100010,town:0x200010\textra')
        self.assertEqual(new.split('\n')[2], text.split('\n')[2])

    def test_refuses_a_home_location_that_carries_another_name(self):
        text = ('0x80016000\tfunc_80016000\tfirst\tev\ttown:0x300000\n'
                '0x80016000\tfunc_80016000\tsecond\tev\ttown:0x100000\n')
        new, changes, refusals = S.renormalise_text(text, self.g)
        self.assertEqual(new, text)
        self.assertEqual(changes, [])
        self.assertEqual(refusals, [(1, L('town', 0x300000), L('town', 0x100000), 'second')])

    def test_a_clean_table_is_unchanged(self):
        text = '0x80016000\tfunc_80016000\tfirst\tev\ttown:0x100000\n'
        self.assertEqual(S.renormalise_text(text, self.g), (text, [], []))

    def test_command_writes_only_with_write(self):
        with tempfile.TemporaryDirectory() as td:
            root = write_tree(td, '0x80016000\tfunc_80016000\tfirst\tev\ttown:0x300000\n')
            tool = str(ROOT / 'tools/name_scope.py')
            out = subprocess.run([sys.executable, tool, '--root', str(root), 'renormalise'], capture_output=True, text=True)
            self.assertIn('1 changed', out.stdout)
            self.assertTrue((root / 'config/names.tsv').read_text().endswith('town:0x300000\n'))
            subprocess.run([sys.executable, tool, '--root', str(root), 'renormalise', '--write'], check=True,
                           capture_output=True, text=True)
            self.assertTrue((root / 'config/names.tsv').read_text().endswith('town:0x100000\n'))


class Lint(unittest.TestCase):
    def run_lint(self, names, **kw):
        td = tempfile.TemporaryDirectory()
        self.addCleanup(td.cleanup)
        root = write_tree(td.name, names, **kw)
        report, need, problems, table = C.analyse(root)
        return root, report, need, {p[0] for p in problems}, problems

    def test_unresolved_location_is_reported_not_raised(self):
        _, _, _, kinds, problems = self.run_lint('0x80016000\tfunc_80016000\tfirst\tev\ttown:0x999999\n')
        self.assertIn('location', kinds)
        self.assertIn('town:0x999999 lies inside no home row', ' '.join(p[2] for p in problems))

    def test_need_set_has_the_function_and_the_data_image_rule(self):
        names = ('0x80016000\tfunc_80016000\tfirst\tev\n0x80016000\tfunc_80016000\tsecond\tev\n'
                 '0x80090010\tD_80090010\tobj\tev\n0x80017000\tfunc_80017000\thome\tev\n')
        _, report, need, _, _ = self.run_lint(names)
        self.assertEqual({r.new for r in need.values()}, {'first', 'second', 'obj'})
        self.assertEqual((report['need_function_rows'], report['need_data_rows']), (2, 1))

    def test_a_clean_scoped_table_reports_nothing(self):
        names = ('0x80016000\tfunc_80016000\talpha\tev\ttown:0x100000\n'
                 '0x80016000\tfunc_80016000\tbeta\tev\ttown:0x200000\n'
                 '0x80090010\tD_80090010\tobj\tev\ttown:0x600010,town:0x700010\n')
        _, _, _, kinds, problems = self.run_lint(names)
        self.assertEqual(problems, [])

    def test_alignment_definition_and_placement_rules(self):
        names = ('0x80016004\tfunc_80016004\talpha\tev\ttown:0x100000\n'          # the location holds 0x80016000
                 '0x80016000\tfunc_80016000\tunknown_name\tev\ttown:0x200000\n'    # b.c defines neither name
                 '0x80016000\tfunc_80016000\tgamma\tev\ttown:0x300000\n')          # inside a placed copy
        _, _, _, kinds, _ = self.run_lint(names)
        self.assertIn('alignment', kinds)
        self.assertIn('definition', kinds)
        self.assertIn('renormalise', kinds)

    def test_module_and_unit_sources_count_as_definitions(self):
        extra = {'config/link_graph/tus.000.jsonl': json.dumps(dict(id='module/m1', source='src/mod.c')) + '\n',
                 'ledger/modules/m1.json': json.dumps(dict(module='m1', members=['town/func_Z'])),
                 'src/mod.c': 'void in_module(void)\n{\n}\n'}
        names = '0x80016040\tfunc_80016040\tin_module\tev\ttown:0x420000\n'
        _, _, _, kinds, _ = self.run_lint(names, extra=extra)
        self.assertNotIn('definition', kinds)

    def test_data_rules(self):
        names = ('0x80090010\tD_80090010\tone\tev\ttown:0x600010,town:0x700010\n'
                 '0x80090010\tD_80090010\ttwo\tev\ttown:0x700010\n'               # a second name on a location
                 '0x80090010\tD_80090010\tthree\tev\ttown:0x123456\n'              # in no image
                 '0x80016000\tD_80016000\tfour\tev\ttown:0x100000\n')              # the first byte of a code row
        _, _, _, kinds, problems = self.run_lint(names)
        self.assertTrue({'duplicate', 'location', 'entry'} <= kinds, kinds)

    def test_two_locations_in_one_image_delta_fail(self):
        # two images of one delta (0x700000 -> 0x80090000 and 0x700800 -> 0x80090800) both map 0x80090810 only once
        views = VIEWS + [view('town/img_E', 0x800000, 0x1000, 0x80090000)]
        names = '0x80090010\tD_80090010\tobj\tev\ttown:0x600010,town:0x700010\n'
        _, _, _, kinds, _ = self.run_lint(names, views=views)
        self.assertNotIn('image', kinds)                      # 0x600000 and 0x700000 differ in delta
        views = VIEWS + [view('town/img_F', 0x800000, 0x1000, 0x80190000)]
        names = '0x80090010\tD_80090010\tobj\tev\ttown:0x700010\n'
        _, _, _, kinds, _ = self.run_lint(names, views=views, regions=[dict(container='town', foff=0x700800, size=0x800,
                                                                          base=0x80090800)])
        self.assertNotIn('image', kinds)
        # one image delta spanning one address twice cannot happen; two locations that map to one address in one
        # delta are reported when a scope lists both
        two = VIEWS + [view('town/img_G', 0x720000, 0x1000, 0x80090000 + 0x20000)]
        names = '0x80090010\tD_80090010\tobj\tev\ttown:0x700010,town:0x700010\n'
        _, _, _, kinds, _ = self.run_lint(names, views=two)
        self.assertIn('grammar', kinds)

    def test_ratchet(self):
        names = ('0x80016000\tfunc_80016000\talpha\tev\n0x80016000\tfunc_80016000\tbeta\tev\n')
        root, _, need, _, _ = self.run_lint(names)
        base = C.baseline_document(need, S.NameTable.parse(names).rows)
        self.assertEqual(base['counts']['unscoped_need_rows'], 2)
        self.assertEqual(C.ratchet(need, base), ([], []))
        # scoping one row shrinks the set; a scoped row that loses its scope is a new unscoped need row
        scoped = '0x80016000\tfunc_80016000\talpha\tev\ttown:0x100000\n0x80016000\tfunc_80016000\tbeta\tev\n'
        report, need2, _, _ = C.analyse(write_tree(tempfile.mkdtemp(), scoped))
        new, gone = C.ratchet(need2, base)
        self.assertEqual((new, gone), ([], [['0x80016000', 'func_80016000', 'alpha']]))
        base2 = C.baseline_document(need2, S.NameTable.parse(scoped).rows)
        new, gone = C.ratchet(need, base2)
        self.assertEqual([r.new for r in new], ['alpha'])

    def test_fail_new_exit_codes_and_write_baseline(self):
        with tempfile.TemporaryDirectory() as td:
            root = write_tree(td, '0x80016000\tfunc_80016000\talpha\tev\n0x80016000\tfunc_80016000\tbeta\tev\n')
            self.assertEqual(C.main(['--root', str(root), '--fail-new']), 1)          # no baseline file
            self.assertEqual(C.main(['--root', str(root), '--write-baseline']), 0)
            self.assertEqual(C.main(['--root', str(root), '--fail-new']), 0)
            (root / 'config/names.tsv').write_text(
                '0x80016000\tfunc_80016000\talpha\tev\n0x80016000\tfunc_80016000\tbeta\tev\n'
                '0x80016000\tfunc_80016000\tnewcomer\tev\n')
            self.assertEqual(C.main(['--root', str(root), '--fail-new']), 1)
            self.assertEqual(C.main(['--root', str(root)]), 0)                        # report-only exits 0


class RefreshStep(unittest.TestCase):
    """ledger_refresh's names step renormalises scope cells and reports each change and refusal."""

    def run_step(self, names):
        import ledger_refresh as R
        td = tempfile.TemporaryDirectory()
        self.addCleanup(td.cleanup)
        geometry = S.Geometry(write_tree(td.name, ''))

        class Run:
            tree = type('T', (), {'defined': {}})()

            def __init__(self):
                self.notes, self.failed = [], []

            def text(self, ledger, where, evidence, own, name, base):
                return evidence

            def base_evidence(self, cols):
                return None

            def note(self, *args):
                self.notes.append(args)

            def fail(self, *args):
                self.failed.append(args)

            def geometry(self):
                return geometry

        class Files:
            written = None

            def read(self, path):
                return names

            def set(self, path, text):
                self.written = text

        run, files = Run(), Files()
        R.names_ledger(run, files)
        return run, files

    def test_a_scope_in_a_placed_copy_moves_home(self):
        run, files = self.run_step('0x80016000\tfunc_80016000\tfirst\tev\ttown:0x300000\n')
        self.assertEqual(files.written, '0x80016000\tfunc_80016000\tfirst\tev\ttown:0x100000\n')
        self.assertEqual(run.notes[0][1:], ('config/names.tsv:1', 'town:0x300000', 'town:0x100000', 'scope renormalised'))

    def test_a_collision_is_refused_and_unscoped_tables_are_untouched(self):
        run, files = self.run_step('0x80016000\tfunc_80016000\tfirst\tev\ttown:0x300000\n'
                                   '0x80016000\tfunc_80016000\tsecond\tev\ttown:0x100000\n')
        self.assertIsNone(files.written)
        self.assertEqual(len(run.failed), 1)
        run, files = self.run_step('0x80016000\tfunc_80016000\tfirst\tev\n')
        self.assertIsNone(files.written)


if __name__ == '__main__':
    unittest.main()
