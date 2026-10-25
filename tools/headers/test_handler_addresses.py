"""Entry-address resolution must respect banks and exact starts."""
import sys
from pathlib import Path
import unittest
import json
sys.path.insert(0, str(Path(__file__).resolve().parent))
from test_headers import mkroot, COMMON
import model as M
from handler_addresses import AddressIndex


class AddressTests(unittest.TestCase):
    def index(self, files):
        td, root = mkroot({'include/common.h': COMMON, **files})
        self.addCleanup(td.cleanup)
        corpus = M.Corpus(root)
        defs, sites, data = M.collect(corpus, M.TypeIndex(corpus))
        return AddressIndex(corpus, defs)

    def banks(self, other_offset):
        rows = [dict(id='dungeon/func_80024000', container='dungeon', func='func_80024000',
                     c_path='a.c', foff=0x1000),
                dict(id='dungeon/func_80025000', container='dungeon', func='func_80025000',
                     c_path='b.c', foff=other_offset)]
        return self.index({
            'ledger/rows.jsonl': ''.join(json.dumps(r) + '\n' for r in rows),
            'src/dungeon/a.c': '#include "common.h"\nvoid func_80024000(void *p) {}\n',
            'src/dungeon/b.c': '#include "common.h"\nextern u8 D_80024000[];\n'
                               'void func_80025000(void *p) {}\n'})

    def test_same_container_other_bank_is_data(self):
        index = self.banks(0x9000)
        self.assertEqual(index.targets('src/dungeon/b.c', 'D_80024000'), [])

    def test_same_bank_entry_is_function(self):
        index = self.banks(0x2000)
        self.assertEqual(index.targets('src/dungeon/b.c', 'D_80024000')[0][0].name, 'func_80024000')

    def test_reused_overlay_function_name_does_not_merge_addresses(self):
        rows = [dict(id='dungeon/func_80024000', container='dungeon', func='func_80024000',
                     c_path='a.c', foff=0x1000),
                dict(id='dungeon/func_80025000', container='dungeon', func='func_80025000',
                     c_path='b.c', foff=0x9000)]
        index = self.index({
            'config/names.tsv': '0x80024000\tfunc_80024000\tupdate\tone bank\n'
                                '0x80025000\tfunc_80025000\tupdate\tother bank\n',
            'ledger/rows.jsonl': ''.join(json.dumps(r) + '\n' for r in rows),
            'src/dungeon/a.c': '#include "common.h"\nvoid update(void *p) {}\n',
            'src/dungeon/b.c': '#include "common.h"\nextern u8 D_80024000[];\n'
                               'void update(void *p) {}\n'})
        self.assertEqual(index.targets('src/dungeon/b.c', 'D_80024000'), [])
        self.assertEqual([d.path for d, ev in index.targets('src/dungeon/b.c', 'update')],
                         ['src/dungeon/b.c'])

    def test_missing_bank_metadata_does_not_turn_a_number_into_ownership(self):
        index = self.index({
            'src/dungeon/a.c': '#include "common.h"\nvoid func_80024000(void *p) {}\n',
            'src/dungeon/b.c': '#include "common.h"\nextern u8 D_80024000[];\n'})
        self.assertEqual(index.targets('src/dungeon/b.c', 'D_80024000'), [])

    def test_interior_address_is_not_entry(self):
        index = self.banks(0x2000)
        self.assertEqual(index.targets('src/dungeon/b.c', 'D_80024004'), [])

    def test_link_image_resolves_a_relocated_exact_start(self):
        image = dict(image='town/example', container='town', vma='0x80090000', size=0x1000,
                     entries=[dict(row='town/func_80011100', home='town/func_80011100',
                                   tu='src/town/a.c', vma='0x80090040'),
                              dict(row='town/func_80011200', home='town/func_80011200',
                                   tu='src/town/b.c', vma='0x80090080')])
        index = self.index({
            'config/link/town/example.json': json.dumps(image),
            'src/town/a.c': '#include "common.h"\nvoid func_80011100(void *p) {}\n',
            'src/town/b.c': '#include "common.h"\nvoid func_80011200(void *p) {}\n'})
        self.assertEqual(index.targets('src/town/b.c', 'D_80090040')[0][0].name, 'func_80011100')
        self.assertEqual(index.targets('src/town/b.c', 'D_80090044'), [])

    def test_linked_data_prefix_is_not_the_function_entry(self):
        image = dict(image='town/prefixed', container='town', vma='0x80090000', size=0x1000,
                     entries=[dict(row='town/func_80011100', home='town/func_80011100',
                                   tu='src/town/a.c', vma='0x80090040', body_offset=16),
                              dict(row='town/func_80011200', home='town/func_80011200',
                                   tu='src/town/b.c', vma='0x80090080')])
        index = self.index({
            'config/link/town/prefixed.json': json.dumps(image),
            'src/town/a.c': '#include "common.h"\nvoid func_80011100(void *p) {}\n',
            'src/town/b.c': '#include "common.h"\nvoid func_80011200(void *p) {}\n'})
        self.assertEqual(index.targets('src/town/b.c', 'D_80090040'), [])
        self.assertEqual(index.targets('src/town/b.c', 'D_80090050')[0][0].name, 'func_80011100')

    def test_binding_prefers_the_importers_home_image(self):
        def entry(row, home, source, address):
            return dict(row=row, home=home, tu=source, vma=hex(address))
        a, b, c = 'town/func_80011100', 'town/func_80022200', 'town/func_80033300'
        pa, pb, pc = 'src/town/a.c', 'src/town/b.c', 'src/town/c.c'
        images = {
            'config/link/town/a.json': dict(image='town/a', container='town', vma='0x80100000', size=0x1000,
                entries=[entry(a, a, pa, 0x80100040)]),
            'config/link/town/b.json': dict(image='town/b', container='town', vma='0x80100000', size=0x1000,
                entries=[entry(b, b, pb, 0x80100040), entry(c, c, pc, 0x80100080)]),
            'config/link/town/copy.json': dict(image='town/copy', container='town', vma='0x80110000', size=0x1000,
                entries=[entry('town/copy_a', a, pa, 0x80110040),
                         entry('town/copy_b', b, pb, 0x80110080),
                         entry('town/copy_c', c, pc, 0x801100C0)])}
        files = {p: json.dumps(image) for p, image in images.items()}
        files.update({p: '#include "common.h"\nvoid ' + name + '(void *p) {}\n'
                      for p, name in [(pa, 'func_80011100'), (pb, 'func_80022200'), (pc, 'func_80033300')]})
        index = self.index(files)
        index.placements[pc] = [(im, e) for im, e in index.placements[pc] if im['image'] == 'town/copy']
        self.assertEqual([d.name for d, ev in index.targets(pc, 'D_80100040')], ['func_80022200'])


if __name__ == '__main__':
    unittest.main()
