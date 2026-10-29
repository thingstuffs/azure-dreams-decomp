"""Build-graph proof universe: affected-set joins, object comparison and verdicts on a fake build state."""
import hashlib
import json
import os
from pathlib import Path
import shutil
import subprocess
import sys
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[3]
sys.path.insert(0, str(ROOT))
from tools.build import affected as A   # noqa: E402

SHA = lambda b: hashlib.sha256(b).hexdigest()   # noqa: E731


def put(path, value):
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_text(value if isinstance(value, str) else json.dumps(value))


class FakeTree:
    """A minimal generated build graph: three source rows, one placement copy, one SLUS partition."""

    def __init__(self, base):
        self.root = Path(base)
        r = self.root
        put(r / 'src/a.c', '#include "x.h"\nint a(void) { return 1; }\n')
        put(r / 'src/b.c', '#include "y.h"\nint b(void) { return 2; }\n')
        put(r / 'src/owner.c', 'int home(void) { return 3; }\n')
        put(r / 'src/slus/code.c', 'int c(void) { return 4; }\n')
        put(r / 'include/x.h', 'int a(void);\n')
        put(r / 'include/y.h', '#include "x.h"\n')
        put(r / 'include/z.h', '/* consumed by nobody */\n')
        (r / 'build_slus').mkdir(parents=True)
        os.symlink('../include', r / 'build_slus/include')
        state = r / 'build/.state'
        recipe = lambda rid, source, deps, **kw: put(state / 'recipes' / (rid + '.json'), dict(  # noqa: E731
            source=source, output='build/obj/%s.o' % rid, args=['2.7.2', '-G0', ''], env={},
            wrapper='build_ovl/tools/cc.sh', dependencies=sorted(deps), **kw))
        recipe('ra', 'src/a.c', ['src/a.c', 'include/x.h', 'build/.state/recipes/ra.json'])
        recipe('rb', 'src/b.c', ['src/b.c', 'include/y.h', 'include/x.h'])
        recipe('rown', 'src/owner.c', ['src/owner.c'])
        # A placement copy: its source is generated; its owner is a dependency (as emit_recipe writes it).
        recipe('rcopy', 'build/.state/enumerate/f.member/home.c', ['src/owner.c', 'include/x.h'],
               projection=dict(home='dungeon/home', owner='src/owner.c'))
        put(state / 'slus-recipes/s1.json', dict(
            command='tools/cc.sh build/partition_sources/code.c build/src/code.o 2.7.2 "" ""',
            output='build_slus/build/src/code.o', config_tables={},
            dependencies=['build_slus/build/partition_sources/code.c', 'build_slus/include/x.h']))
        put(state / 'slus-recipes/s2.json', dict(
            command='tools/as.sh asm/p.s build/asm/p.o', output='build_slus/build/asm/p.o',
            dependencies=['build_slus/asm/p.s']))
        image = lambda tag, name, recipes: put(state / 'images' / (tag + '.json'), dict(  # noqa: E731
            tag=tag, image=name, output='build/%s.bin' % tag, units=[dict(recipe=x) for x in recipes]))
        image('bank_1', 'dungeon/bank_1', ['ra', 'rcopy'])
        image('bank_2', 'dungeon/bank_2', ['rcopy', 'rb'])
        image('home', 'dungeon/home_img', ['rown'])
        image('stale', 'dungeon/stale', ['ra'])        # not registered in index.json
        put(state / 'index.json', dict(images=[dict(image=n) for n in (
            'slus/slus_bin', 'dungeon/bank_1', 'dungeon/bank_2', 'dungeon/home_img')],
            slus_recipes=['build/.state/slus-recipes/s1.json', 'build/.state/slus-recipes/s2.json']))
        recipe('rgone', 'src/deleted.c', ['src/deleted.c', 'include/x.h'])   # stale: no make rule
        rules = ''.join('build/obj/%s.o: x\n\t@true\n\n' % rid for rid in ('ra', 'rb', 'rown', 'rcopy'))
        put(r / 'build/build.mk', rules +
            'build_slus/build/partition_sources/code.c build_slus/build/partition_sources/code2.c &: '
            'build_slus/src/code.c build_slus/config/names.tsv\n\t@echo render\n')
        (r / 'build_slus/src').mkdir()
        os.symlink('../../src/slus/code.c', r / 'build_slus/src/code.c')

    def objects(self, blobs):
        for rid, blob in blobs.items():
            path = self.root / 'build/obj' / (rid + '.o')
            path.parent.mkdir(parents=True, exist_ok=True)
            path.write_bytes(blob)
            deps = json.loads((self.root / 'build/.state/recipes' / (rid + '.json')).read_text())['dependencies']
            inputs = {d: SHA((self.root / d).read_bytes()) for d in deps if (self.root / d).is_file()}
            put(path.with_suffix('.proof.json'), dict(object_sha256=SHA(blob), inputs=inputs))


class AffectedSetTests(unittest.TestCase):
    def setUp(self):
        parent = ROOT / 'tmp'
        parent.mkdir(exist_ok=True)
        self.tmp = tempfile.mkdtemp(dir=parent)
        self.tree = FakeTree(self.tmp)

    def tearDown(self):
        shutil.rmtree(self.tmp, ignore_errors=True)

    def scope(self, *files):
        return A.affected_set(self.tree.root, list(files))

    def test_own_source_and_single_image(self):
        s = self.scope('src/a.c')
        self.assertEqual(s['recipes'], ['ra'])
        self.assertEqual(s['own'], {'src/a.c': ['ra']})
        self.assertEqual(s['images'], ['dungeon/bank_1'])     # the unregistered 'stale' image is ignored

    def test_header_reaches_direct_and_transitive_consumers_and_copies(self):
        s = self.scope('include/x.h')
        self.assertEqual(s['recipes'], ['ra', 'rb', 'rcopy'])     # never the stale 'rgone'
        self.assertEqual(s['slus_recipes'], ['s1'])            # through the build_slus/include symlink view
        self.assertEqual(s['images'], ['dungeon/bank_1', 'dungeon/bank_2', 'slus/slus_bin'])
        self.assertEqual(s['kinds'], {'row': 2, 'placement_copy': 1, 'slus': 1})

    def test_owner_edit_reaches_every_placement_copy_and_its_banks(self):
        s = self.scope('src/owner.c')
        self.assertEqual(s['recipes'], ['rcopy', 'rown'])
        self.assertEqual(sorted(s['own']['src/owner.c']), ['rcopy', 'rown'])
        self.assertEqual(s['images'], ['dungeon/bank_1', 'dungeon/bank_2', 'dungeon/home_img'])

    def test_partition_parent_reaches_rendered_slus_recipe(self):
        s = self.scope('src/slus/code.c')
        self.assertEqual(s['slus_recipes'], ['s1'])
        self.assertEqual(s['images'], ['slus/slus_bin'])

    def test_unconsumed_and_authority(self):
        s = self.scope('include/z.h', 'tools/build/mkbuild.py')
        self.assertEqual(s['unconsumed'], ['include/z.h'])
        self.assertEqual(s['authority'], ['tools/build/mkbuild.py'])
        self.assertEqual(s['recipes'], [])
        report = A.prove(self.tree.root, ['tools/build/mkbuild.py'], compile_tasks=lambda t: {})
        self.assertEqual(report['verdict'], 'ERROR')

    def test_paths_outside_root_refused(self):
        with self.assertRaises(ValueError):
            self.scope('/etc/passwd')


class ProveVerdictTests(unittest.TestCase):
    """prove() with an injected compiler: object verdicts, image roll-up and baseline freshness."""

    def setUp(self):
        parent = ROOT / 'tmp'
        parent.mkdir(exist_ok=True)
        self.tmp = tempfile.mkdtemp(dir=parent)
        self.base = FakeTree(Path(self.tmp) / 'base')
        self.cand = FakeTree(Path(self.tmp) / 'cand')
        self.blobs = {'ra': b'A' * 64, 'rb': b'B' * 64, 'rown': b'O' * 64, 'rcopy': b'C' * 64}
        self.base.objects(self.blobs)

    def tearDown(self):
        shutil.rmtree(self.tmp, ignore_errors=True)

    def compiler(self, produced):
        def compile_task(task):
            rel = '%s/obj/%s.o' % (task['run'], task['id'])
            path = self.cand.root / rel
            path.parent.mkdir(parents=True, exist_ok=True)
            path.write_bytes(produced.get(task['id'], self.blobs.get(task['id'], b'')))
            return dict(object=rel, sha256=SHA(path.read_bytes()), seconds=0)
        return compile_task

    def prove(self, files, produced, edit=None):
        if edit:
            for name, text in edit.items():
                (self.cand.root / name).write_text(text)
        return A.prove(self.cand.root, files, self.base.root, compile_tasks=self.compiler(produced))

    def test_identical_objects_pass_without_relink(self):
        r = self.prove(['include/y.h'], {}, {'include/y.h': '#include "x.h"\n/* comment */\n'})
        self.assertEqual(r['verdict'], 'PASS', r)
        self.assertEqual(r['recipes']['rb']['verdict'], 'PASS')
        self.assertEqual(r['images']['dungeon/bank_2']['verdict'], 'PASS')

    def test_changed_copy_marks_every_bank_changed(self):
        r = self.prove(['src/owner.c'], {'rcopy': b'C' * 63 + b'D'})
        self.assertEqual(r['verdict'], 'CHANGED')
        self.assertEqual(r['recipes']['rown']['verdict'], 'PASS')
        self.assertEqual(r['recipes']['rcopy']['verdict'], 'CHANGED')
        self.assertEqual(r['recipes']['rcopy']['owner'], 'src/owner.c')
        self.assertEqual(r['images']['dungeon/bank_1']['changed_recipes'], ['rcopy'])
        self.assertEqual(r['images']['dungeon/bank_2']['verdict'], 'CHANGED')
        self.assertEqual(r['images']['dungeon/home_img']['verdict'], 'PASS')
        self.assertTrue(any('rcopy' in line for line in A.summary(r)))

    def test_stale_baseline_is_never_pass(self):
        (self.base.root / 'include/y.h').write_text('/* base moved on */\n')
        r = self.prove(['include/y.h'], {})
        self.assertEqual(r['recipes']['rb']['verdict'], 'STALE_BASE')
        self.assertEqual(r['verdict'], 'STALE_BASE')

    def test_object_receipt_mismatch_is_stale(self):
        (self.base.root / 'build/obj/ra.o').write_bytes(b'tampered')
        r = self.prove(['src/a.c'], {})
        self.assertEqual(r['recipes']['ra']['verdict'], 'STALE_BASE')


AS = shutil.which('mipsel-linux-gnu-as')


@unittest.skipUnless(AS, 'mipsel-linux-gnu-as not installed')
class ObjectDifferenceTests(unittest.TestCase):
    def assemble(self, text):
        with tempfile.TemporaryDirectory(dir=ROOT / 'tmp') as td:
            src, out = Path(td) / 'x.s', Path(td) / 'x.o'
            src.write_text('.set noreorder\n.section .text.f,"ax"\n.globl f\nf:\n' + text + '\n.size f, .-f\n')
            subprocess.run([AS, '-EL', '-march=r3000', '-o', str(out), str(src)], check=True)
            return out.read_bytes()

    def setUp(self):
        (ROOT / 'tmp').mkdir(exist_ok=True)

    def test_identical(self):
        a = self.assemble('jr $ra\nnop')
        self.assertIsNone(A.object_difference(a, a))

    def test_instruction_change_names_symbol(self):
        a = self.assemble('addiu $v0, $zero, 1\njr $ra\nnop')
        b = self.assemble('addiu $v0, $zero, 2\njr $ra\nnop')
        d = A.object_difference(a, b)
        self.assertEqual((d['kind'], d['section'], d['symbol']), ('bytes', '.text.f', 'f+0x0'))

    def test_relocation_change(self):
        a = self.assemble('jal g\nnop\njr $ra\nnop')
        b = self.assemble('jal h\nnop\njr $ra\nnop')
        d = A.object_difference(a, b)
        self.assertEqual(d['kind'], 'relocation')
        self.assertEqual((d['before'][2], d['after'][2]), ('g', 'h'))


class RepositoryInvariants(unittest.TestCase):
    def test_src_and_include_hold_no_symlinks(self):
        # Graph.real() trusts src/ and include/ paths without a stat walk.
        for top in ('src', 'include'):
            for dirpath, dirnames, filenames in os.walk(ROOT / top):
                for name in dirnames + filenames:
                    self.assertFalse(os.path.islink(os.path.join(dirpath, name)), os.path.join(dirpath, name))


if __name__ == '__main__':
    unittest.main()
