"""name_scope_oracle on synthetic objects and containers: keys by masked bytes, refusals, no bytes in the report."""
import hashlib
import json
import struct
import sys
import tempfile
import unittest
from pathlib import Path

HERE = Path(__file__).resolve().parent
ROOT = HERE.parents[1]
sys.path.insert(0, str(ROOT / 'tools'))
sys.path.insert(0, str(HERE))
import name_scope as S  # noqa: E402
import name_scope_oracle as O  # noqa: E402
import test_name_scope_v2 as T  # noqa: E402

L = S.Location
BODY = bytes.fromhex('27bdffe8' '0000000c' 'afbf0010' '8fbf0010' '03e00008' '27bd0018' '00000000' '00000000')
SECRET = BODY.hex()


def elf(symbols, text, relocs=(), data_syms=()):
    """A minimal ELF32 MIPS object: .text and its relocations; symbols = [(name, value, size, type, bind)]
    (section 1); relocs = [(offset, type, symbol name)]."""
    names = [''] + [s[0] for s in symbols] + [r[2] for r in relocs]
    strtab = b'\0' + b''.join(n.encode() + b'\0' for n in dict.fromkeys(n for n in names if n))
    def stroff(n):
        return 0 if not n else strtab.index(b'\0' + n.encode() + b'\0') + 1
    syms = [(0, 0, 0, 0, 0, 0)]
    index = {}
    for name, value, size, typ, bind in symbols:
        index[name] = len(syms)
        syms.append((stroff(name), value, size, (bind << 4) | typ, 0, 1))
    for _o, _t, name in relocs:
        if name not in index:
            index[name] = len(syms)
            syms.append((stroff(name), 0, 0, 1 << 4, 0, 0))
    symtab = b''.join(struct.pack('<IIIBBH', *s) for s in syms)
    rel = b''.join(struct.pack('<II', o, (index[n] << 8) | t) for o, t, n in relocs)
    shstr = b'\0.text\0.rel.text\0.symtab\0.strtab\0.shstrtab\0'
    def so(n):
        return shstr.index(b'\0' + n.encode() + b'\0') + 1
    blobs = [b'', text, rel, symtab, strtab, shstr]
    offs, pos = [], 0x34
    for b in blobs:
        offs.append(pos)
        pos += len(b)
    shoff = pos
    heads = [(0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
             (so('.text'), 1, 6, 0, offs[1], len(text), 0, 0, 4, 0),
             (so('.rel.text'), 9, 0, 0, offs[2], len(rel), 3, 1, 4, 8),
             (so('.symtab'), 2, 0, 0, offs[3], len(symtab), 4, 1, 4, 16),
             (so('.strtab'), 3, 0, 0, offs[4], len(strtab), 0, 0, 1, 0),
             (so('.shstrtab'), 3, 0, 0, offs[5], len(shstr), 0, 0, 1, 0)]
    header = b'\x7fELF\x01\x01\x01' + b'\0' * 9 + struct.pack('<HHIIIIIHHHHHH', 1, 8, 1, 0, 0, shoff, 0, 0x34, 0, 0, 40, 6, 5)
    return header.ljust(0x34, b'\0') + b''.join(blobs) + b''.join(struct.pack('<10I', *h) for h in heads)


class Fixture(unittest.TestCase):
    """Rows A and B (two images at one address) and Z; objects for alpha (func_80016000) built from src/a.c."""

    def setUp(self):
        self.td = tempfile.TemporaryDirectory()
        self.addCleanup(self.td.cleanup)
        self.root = T.write_tree(self.td.name, '')
        self.obj = Path(self.td.name) / 'obj'
        self.obj.mkdir()
        self.disc = Path(self.td.name) / 'disc'
        self.disc.mkdir()
        # the retail container: BODY at town:0x100000 (A) and at town:0x200000 (B); the jal field differs
        blob = bytearray(0x800000)
        for off, jal in ((0x100000, 0x0C001234), (0x200000, 0x0C005678)):
            blob[off:off + len(BODY)] = BODY
            blob[off + 4:off + 8] = struct.pack('<I', jal)
        (self.disc / 'TOWN_TOWN.BIN').write_bytes(bytes(blob))
        self.sha_good = hashlib.sha256((self.root / 'src/a.c').read_bytes()).hexdigest()

    def add_object(self, name, symbol, source, sha=None, body=BODY, size=len(BODY)):
        (self.obj / name).write_bytes(elf([(symbol, 0, size, 2, 1)], body, [(4, 4, 'callee')]))
        (self.obj / name.replace('.o', '.proof.json')).write_text(json.dumps(
            dict(inputs={source: sha or hashlib.sha256((self.root / source).read_bytes()).hexdigest()})))

    def oracle(self):
        objects = O.Objects(self.obj, self.root)
        return O.Oracle(self.root, objects, O.Containers(self.disc))


class Functions(Fixture):
    def test_a_defining_object_keys_the_home_location_and_masks_relocations(self):
        self.add_object('alpha.o', 'func_80016000', 'src/a.c')
        res = self.oracle().function_keys(0x80016000, 'func_80016000', 'alpha')
        self.assertEqual((res['status'], res['keys']), ('keyed', [L('town', 0x100000)]))
        self.assertEqual(res['detail']['keys']['town:0x100000']['home'], 'town/func_A')

    def test_the_report_holds_no_retail_bytes(self):
        self.add_object('alpha.o', 'func_80016000', 'src/a.c')
        res = self.oracle().function_keys(0x80016000, 'func_80016000', 'alpha')
        text = json.dumps(res, default=str)
        self.assertNotIn(SECRET, text)
        self.assertNotIn(SECRET[:16], text)
        self.assertEqual(set(res['detail']['keys']['town:0x100000']), {'home', 'size', 'sha256', 'objects'})
        self.assertEqual(len(res['detail']['keys']['town:0x100000']['sha256']), 64)

    def test_refusals(self):
        o = self.oracle()
        self.assertEqual(o.function_keys(0x80016000, 'func_80016000', 'alpha')['reason'], 'no_current_object')
        self.add_object('alpha.o', 'func_80016000', 'src/a.c', sha='0' * 64)            # stale receipt
        self.assertEqual(self.oracle().function_keys(0x80016000, 'func_80016000', 'alpha')['reason'], 'no_current_object')
        self.add_object('alpha.o', 'func_80016000', 'src/a.c', body=BODY[:-4] + b'\x11\x22\x33\x44')
        self.assertEqual(self.oracle().function_keys(0x80016000, 'func_80016000', 'alpha')['reason'], 'source_without_key')
        self.add_object('alpha.o', 'func_80016000', 'src/a.c')
        self.assertEqual(self.oracle().function_keys(0x80016000, 'func_80016000', 'zzz')['reason'], 'no_current_object')

    def test_a_source_spelled_by_two_homes_keys_both_or_refuses(self):
        # beta is defined by src/b.c whose home is town/func_B at town:0x200000: also the same bytes there
        self.add_object('beta.o', 'func_80016000', 'src/b.c')
        res = self.oracle().function_keys(0x80016000, 'func_80016000', 'beta')
        self.assertEqual(res['keys'], [L('town', 0x200000)])

    def test_two_locations_in_one_image_refuse(self):
        views = [dict(T.VIEWS[0]), T.view('town/img_wide', 0x100000, 0x200000, 0x80016000)]
        rows = T.ROWS + [T.row('town/func_A2', 0x200000, 0x40, 'func_80016000')]
        layout = dict(T.LAYOUT, **{'town/func_A2': 'src/a.c'})
        root = T.write_tree(tempfile.mkdtemp(), '', rows=rows, views=views + T.VIEWS[1:2], layout=layout)
        (root / 'src/a.c').write_text(T.SOURCES['src/a.c'])
        sha = hashlib.sha256((root / 'src/a.c').read_bytes()).hexdigest()
        obj = Path(tempfile.mkdtemp())
        (obj / 'alpha.o').write_bytes(elf([('func_80016000', 0, len(BODY), 2, 1)], BODY, [(4, 4, 'callee')]))
        (obj / 'alpha.proof.json').write_text(json.dumps(dict(inputs={'src/a.c': sha})))
        res = O.Oracle(root, O.Objects(obj, root), O.Containers(self.disc)).function_keys(0x80016000, 'func_80016000', 'alpha')
        self.assertEqual(res['reason'], 'two_locations_in_one_image')

    def test_collisions_are_reported_for_every_claimant(self):
        k = lambda n: dict(status='keyed', reason='', keys=[L('town', 0x100000)], detail={})
        clash = O.location_collisions({(1, 'func_1', 'one'): k('one'), (1, 'func_1', 'two'): k('two')})
        self.assertEqual(clash, {L('town', 0x100000): ['one', 'two']})
        self.assertEqual(O.location_collisions({(1, 'func_1', 'one'): k('one')}), {})

    def test_check_command_reproduces_a_batch(self):
        self.add_object('alpha.o', 'func_80016000', 'src/a.c')
        batch = Path(self.td.name) / 'b.tsv'
        batch.write_text('address\tsymbol\tnew_name\tscope\n0x80016000\tfunc_80016000\talpha\ttown:0x100000\n')
        argv = ['--root', str(self.root), '--obj', str(self.obj), '--containers', str(self.disc), 'check', str(batch)]
        self.assertEqual(O.main(argv), 0)
        batch.write_text('address\tsymbol\tnew_name\tscope\n0x80016000\tfunc_80016000\talpha\ttown:0x200000\n')
        self.assertEqual(O.main(argv), 1)


class Data(Fixture):
    """A function at town:0x100000 (address 0x80016000) loads D_80090010 through lui/addiu."""

    def setUp(self):
        super().setUp()
        views = [T.view('town/img_big', 0x100000, 0x100000, 0x80016000,
                        [T.entry('town/func_A', 'town/func_A', 0x100000, 0x80016000, 0x40)])]
        self.root = T.write_tree(self.td.name, '', views=views, regions=[])
        blob = bytearray((self.disc / 'TOWN_TOWN.BIN').read_bytes())
        blob[0x100000:0x100008] = struct.pack('<II', 0x3C088009, 0x25080010)          # lui t0, 0x8009; addiu t0, t0, 0x10
        (self.disc / 'TOWN_TOWN.BIN').write_bytes(bytes(blob))
        text = struct.pack('<II', 0x3C080000, 0x25080000) + b'\0' * 8
        (self.obj / 'alpha.o').write_bytes(elf([('func_80016000', 0, 16, 2, 1)], text,
                                               [(0, 5, 'D_80090010'), (4, 6, 'D_80090010')]))
        (self.obj / 'alpha.proof.json').write_text(json.dumps(dict(inputs={'src/a.c': self.sha_good})))
        (self.root / 'src/a.c').write_text('void alpha(void)\n{\n  /* uses obj */ (void)obj;\n}\n')
        (self.obj / 'alpha.proof.json').write_text(json.dumps(dict(inputs={
            'src/a.c': hashlib.sha256((self.root / 'src/a.c').read_bytes()).hexdigest()})))

    def test_a_decoded_reference_keys_the_data_location_in_the_image(self):
        res = self.oracle().data_keys(0x80090010, 'D_80090010', 'obj')
        self.assertEqual((res['status'], res['keys']), ('keyed', [L('town', 0x100000 + 0x80090010 - 0x80016000)]))

    def test_a_rebound_reference_claims_nothing(self):
        res = self.oracle().data_keys(0x80090020, 'D_80090020', 'obj')
        self.assertEqual(res['status'], 'refused')


if __name__ == '__main__':
    unittest.main()
