"""Negative proofs for `make check`: each mutation must FAIL, a byte-neutral one must pass.

Fast synthetic tests always run. The tree tests mutate THIS checkout and need a completed,
passing build (`make -j && make check`); they are opt-in because they rebuild:

    AZURE_MAKE_NEGATIVE=1    tree tests, about 15 min at -j12 (each restores its file and the
                             final test re-proves 1490/1490)
    AZURE_MAKE_NEGATIVE=full adds the slow ones: the linker-catalog edit (~16 min: two relinks of
                             every image) and the shared-header edit (~50 min: two full C rebuilds)
    AZURE_MAKE_JOBS=N        make parallelism (default 8)

A test whose fixture text has moved skips with the reason instead of passing.
Run from the checkout root: PYTHONPATH=tools:tools/tests:. python3 -m unittest tools.tests.test_make_negative
"""
import contextlib
import json
import os
from pathlib import Path
import re
import subprocess
import tempfile
import time
import unittest
from unittest.mock import patch

from tools.build import mkbuild as B
from tools.build import land_make as L

ROOT = Path(__file__).resolve().parents[2]
MODE = os.environ.get('AZURE_MAKE_NEGATIVE', '')
JOBS = os.environ.get('AZURE_MAKE_JOBS', '8')


class StampAndDebtUnits(unittest.TestCase):
    """Synthetic: no disc, no build."""

    def test_stamp_digest_follows_content_not_mtime(self):
        with tempfile.TemporaryDirectory() as td:
            root = Path(td); state = root/'build/.state'; state.mkdir(parents=True)
            (root/'h.h').write_text('int a;\n')
            (state/'headers.list').write_text(json.dumps(['h.h']))
            with patch.object(B, 'ROOT', root), patch.object(B, 'STATE', state):
                B.write_stamp('headers'); first = (state/'headers.ok').read_text()
                st = (root/'h.h').stat()
                (root/'h.h').write_text('int b;\n')
                os.utime(root/'h.h', ns=(st.st_atime_ns, st.st_mtime_ns))   # same mtime, new bytes
                B.INPUT_DIGESTS.clear()
                self.assertNotEqual(B.stamp('headers'), first)

    def test_debt_scan_blocks_new_goto_and_asm_but_not_comments(self):
        with tempfile.TemporaryDirectory() as td:
            root = Path(td)
            def git(*a):
                return subprocess.check_output(['git', *a], cwd=root, stderr=subprocess.DEVNULL)
            git('init', '-q'); git('config', 'user.name', 'T'); git('config', 'user.email', 't@example.invalid')
            (root/'src').mkdir(); f = root/'src/a.c'
            f.write_text('void f(void) { }\n'); git('add', '.'); git('commit', '-qm', 'b')
            f.write_text('/* goto volatile asm( */\nvoid f(void) { }\n')
            self.assertEqual(L.debt_scan(root)['after']['goto'], 0)
            f.write_text('void f(void) { goto x; x: ; }\n')
            with self.assertRaisesRegex(ValueError, 'goto 0->1'):
                L.debt_scan(root)
            L.debt_scan(root, ['goto'])
            f.write_text('void f(void) { __asm__("nop"); }\n')
            with self.assertRaisesRegex(ValueError, 'asm 0->1'):
                L.debt_scan(root, ['goto', 'volatile'])

    def test_lander_refuses_binary_files(self):
        with tempfile.TemporaryDirectory() as td:
            root = Path(td)
            def git(*a):
                return subprocess.check_output(['git', *a], cwd=root, stderr=subprocess.DEVNULL)
            git('init', '-q'); git('config', 'user.name', 'T'); git('config', 'user.email', 't@example.invalid')
            (root/'note.txt').write_text('x\n'); git('add', '.'); git('commit', '-qm', 'b')
            (root/'blob.dat').write_bytes(b'ab\0cd')
            with self.assertRaisesRegex(ValueError, 'binary file'):
                L.scrub(root)

    def test_clean_removes_every_object_and_image(self):
        with tempfile.TemporaryDirectory() as td:
            root = Path(td)
            for p in ('build/obj/x.o', 'build/a_b.bin', 'build/.state/link/t/image.ld',
                      'build/.state/origins/t.json', 'build_slus/build/src/y.o', 'build_slus/build/slus_006.14'):
                (root/p).parent.mkdir(parents=True, exist_ok=True); (root/p).write_text('x')
            (root/'build/.state/index.json').write_text('{}')
            L.clean(root)
            self.assertEqual(sorted(str(p.relative_to(root)) for p in root.rglob('*') if p.is_file()),
                             ['build/.state/index.json'])


def make(*args):
    r = subprocess.run(['nice', '-n', '10', 'make', *args], cwd=ROOT, capture_output=True, text=True)
    return r.returncode, r.stdout + r.stderr


def build_and_check():
    code, out = make('-j' + JOBS)
    if code:
        return code, out
    code2, out2 = make('check')
    return code2, out + out2


@contextlib.contextmanager
def mutated(rel, old, new, keep_mtime=False):
    """Replace one exact text; always restore the bytes. A kept mtime is restored too (nothing rebuilt)."""
    path = ROOT/rel
    if not path.is_file():
        raise unittest.SkipTest('fixture moved: ' + rel)
    data = path.read_bytes(); st = path.stat()
    text = data.decode()
    if text.count(old) != 1:
        raise unittest.SkipTest('fixture text moved in ' + rel)
    path.write_text(text.replace(old, new))
    if keep_mtime:
        os.utime(path, ns=(st.st_atime_ns, st.st_mtime_ns))
    try:
        yield path
    finally:
        path.write_bytes(data)
        if keep_mtime:
            os.utime(path, ns=(st.st_atime_ns, st.st_mtime_ns))


def image_with_row(row):
    for p in (ROOT/'build/.state/images').glob('*.json'):
        spec = json.loads(p.read_text())
        if any(row in u.get('rows', []) for u in spec['units']):
            return spec
    raise unittest.SkipTest('no image places ' + row)


def image_with_source(source):
    for p in (ROOT/'build/.state/images').glob('*.json'):
        spec = json.loads(p.read_text())
        for u in spec['units']:
            if json.loads((ROOT/'build/.state/recipes'/(u['recipe']+'.json')).read_text())['source'] == source:
                return spec
    raise unittest.SkipTest('no image compiles ' + source)


@unittest.skipUnless(MODE in ('1', 'full'), 'set AZURE_MAKE_NEGATIVE=1 (tree tests rebuild this checkout)')
class TreeNegatives(unittest.TestCase):
    """Order matters only for speed; every test restores what it touched and the last re-proves the tree."""
    OVL = 'src/town/scene/get_pointer_selector_lookup_id.c'
    OVL_OLD, OVL_NEW = 'switch (data_selector - 12)', 'switch (data_selector - 13)'

    @classmethod
    def setUpClass(cls):
        receipt = ROOT/'build/check.json'
        if not receipt.exists():
            raise unittest.SkipTest('needs a completed make check')
        code, out = build_and_check()
        if code:
            raise AssertionError('tree is not green before the negative suite:\n' + out[-3000:])

    def settle(self):
        """Rebuild what earlier restores left pending, so a tamper is not overwritten by a relink."""
        code, out = build_and_check()
        self.assertEqual(code, 0, out[-2000:])

    def expect_fail(self, pattern):
        code, out = build_and_check()
        self.assertNotEqual(code, 0, 'mutation passed make check')
        self.assertRegex(out, pattern)
        return out

    def test_a_overlay_constant_names_image(self):
        image = image_with_source(self.OVL)['image']
        with mutated(self.OVL, self.OVL_OLD, self.OVL_NEW):
            self.expect_fail(r'DIFF ' + re.escape(image) + r' offset=0x[0-9A-F]+ disc=0x[0-9A-F]+ symbol=')

    def test_b_slus_constant_names_executable(self):
        with mutated('src/slus/w_8004DF8C.c', 'D_8008154C = 0x2300040C;', 'D_8008154C = 0x2300050C;'):
            self.expect_fail(r'DIFF slus/slus_bin offset=0x[0-9A-F]+ .*symbol=func_8004DF8C')

    def test_d_comment_only_edit_passes(self):
        with mutated(self.OVL, self.OVL_OLD, self.OVL_OLD + ' /* byte-neutral */'):
            code, out = build_and_check()
            self.assertEqual(code, 0, out[-2000:])
            self.assertRegex(out, r'CHECK (\d+)/\1 images SHA-1 MATCH')

    def test_e_tampered_image_fails(self):
        self.settle()
        spec = image_with_source(self.OVL)
        path = ROOT/spec['output']; st = path.stat(); data = bytearray(path.read_bytes())
        data[100] ^= 0xFF; path.write_bytes(bytes(data)); os.utime(path, ns=(st.st_atime_ns, st.st_mtime_ns))
        try:
            self.expect_fail(r'DIFF ' + re.escape(spec['image']))
        finally:
            path.unlink()

    def test_e_tampered_object_fails(self):
        self.settle()
        spec = image_with_source(self.OVL)
        recipe = json.loads((ROOT/'build/.state/recipes'/(spec['units'][0]['recipe']+'.json')).read_text())
        path = ROOT/recipe['output']; st = path.stat(); data = bytearray(path.read_bytes())
        data[60] ^= 0xFF; path.write_bytes(bytes(data)); os.utime(path, ns=(st.st_atime_ns, st.st_mtime_ns))
        try:
            self.expect_fail(r'stale compile proof')
        finally:
            path.unlink()

    def test_e_unlinked_image_fails(self):
        spec = image_with_source(self.OVL)
        with mutated(self.OVL, self.OVL_OLD, self.OVL_NEW):
            later = time.time() + 3600
            os.utime(ROOT/spec['output'], (later, later))   # newer than the rebuilt object: make skips the link
            self.expect_fail(r'stale image: ' + re.escape(spec['image']))
        (ROOT/spec['output']).unlink()

    def test_h_switch_table_contents_compared(self):
        old = '    case 13:\n        return D_8001C018;\n    case 12:\n        return D_800227FB;'
        new = '    case 12:\n        return D_8001C018;\n    case 13:\n        return D_800227FB;'
        with mutated('src/town/scene/select_data_for_selector.c', old, new):
            self.expect_fail(r'compiler-local table differs from retail in \S+: \S+: local \.rodata')

    def test_i_included_c_file_is_a_dependency(self):
        target = None
        for p in sorted((ROOT/'build/.state/recipes').glob('*.json')):
            r = json.loads(p.read_text())
            extra = [d for d in r.get('dependencies', []) if d.startswith('src/') and d.endswith('.c') and d != r['source']]
            if extra:
                target = (r, extra[0]); break
        if target is None:
            self.skipTest('no recipe includes another .c file')
        recipe, included = target
        print('\n  test_i: editing', included, 'included by', recipe['source'], flush=True)
        path = ROOT/included; data = path.read_bytes()
        path.write_bytes(data + b'\nint make_negative_probe = 1;\n')   # a new definition changes the object
        try:
            self.expect_fail(r'retail mismatch|differs|ASSERT|source/import extent|payload differs|import inventory')
        finally:
            path.write_bytes(data)

    def test_j_header_edit_with_old_mtime_is_stale(self):
        self.settle()   # nothing may compile against the edit
        with mutated('include/shared/game_work.h', 'unsigned char pad_006[0x2];', 'unsigned char pad_006[0x6];', keep_mtime=True):
            code, out = make('check')
            self.assertNotEqual(code, 0)
            self.assertRegex(out, r'stale headers stamp')

    def test_k_projected_span_follows_its_owner(self):
        inline = [json.loads(l) for l in (ROOT/'ledger/layout_inline.jsonl').read_text().splitlines() if l.strip()]
        projected = {}
        for p in (ROOT/'build/.state/recipes').glob('*.json'):
            r = json.loads(p.read_text())
            if r.get('projection'):
                projected.setdefault(r['projection']['home'], r)
        rec = next((x for x in inline if x['member_id'] in projected), None)
        if rec is None:
            self.skipTest('no projected placement recipe')
        owner = ROOT/rec['tu_new']; data = owner.read_bytes()
        cut = rec['offset'] + data[rec['offset']:].index(b'\n') + 1   # after the span's first line
        owner.write_bytes(data[:cut] + b'/* edit inside an inlined span */\n' + data[cut:])
        try:
            self.expect_fail(r'inline source_sha256 mismatch|inline extent')
        finally:
            owner.write_bytes(data)

    @unittest.skipUnless(MODE == 'full', 'slow (~16 min): AZURE_MAKE_NEGATIVE=full')
    def test_g_linker_catalog_edit_relinks(self):
        line = 'D_80100E24_R = 0x80100E24;'
        with mutated('config/overlays/abs_syms.txt', line, line.replace('E24;', 'E28;')):
            self.expect_fail(r'DIFF town/')

    @unittest.skipUnless(MODE == 'full', 'slow (~50 min): AZURE_MAKE_NEGATIVE=full')
    def test_c_shared_header_edit_rebuilds_dependants(self):
        with mutated('include/shared/game_work.h', 'unsigned char pad_006[0x2];', 'unsigned char pad_006[0x6];'):
            code, out = make('-n', '-j' + JOBS)
            self.assertGreater(out.count('mkbuild.py compile'), 1000)
            self.expect_fail(r'retail mismatch|DIFF ')

    def test_z_tree_is_green_again(self):
        code, out = build_and_check()
        self.assertEqual(code, 0, out[-3000:])
        self.assertRegex(out, r'CHECK (\d+)/\1 images SHA-1 MATCH')


if __name__ == '__main__':
    unittest.main()
