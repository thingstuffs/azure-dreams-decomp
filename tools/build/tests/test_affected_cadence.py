"""Lane cadence on affected.py: edit classes (authority / derived layout_inline / non-build), new-TU refusal and
baseline promotion (--adopt) across batches, on the fake build state of test_affected."""
import json
import os
from pathlib import Path
import re
import shutil
import subprocess
import sys
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[3]
sys.path.insert(0, str(ROOT))
sys.path.insert(0, str(Path(__file__).resolve().parent))
from tools.build import affected as A          # noqa: E402
from test_affected import FakeTree, SHA, put     # noqa: E402


def git(root, *args):
    subprocess.run(['git', '-C', str(root), *args], check=True, capture_output=True)


def commit(root, message):
    git(root, 'add', '-A', 'src', 'include', 'ledger', 'tools')
    git(root, '-c', 'user.name=t', '-c', 'user.email=t@invalid', 'commit', '-qm', message)
    return subprocess.run(['git', '-C', str(root), 'rev-parse', 'HEAD'], capture_output=True, text=True).stdout.strip()


class CadenceTests(unittest.TestCase):
    def setUp(self):
        parent = ROOT / 'tmp'
        parent.mkdir(exist_ok=True)
        self.tmp = tempfile.mkdtemp(dir=parent)
        self.tree = FakeTree(Path(self.tmp) / 'lane')
        self.root = self.tree.root
        self.blobs = {'ra': b'A' * 64, 'rb': b'B' * 64, 'rown': b'O' * 64, 'rcopy': b'C' * 64}
        put(self.root / 'ledger/layout_inline.jsonl', ''.join(json.dumps(r) + '\n' for r in [
            dict(member_id='dungeon/home', tu_new='src/owner.c', offset=0, inlined_bytes=10),
            dict(member_id='dungeon/bee', tu_new='src/b.c', offset=0, inlined_bytes=10)]))
        put(self.root / 'ledger/prototype_floors.jsonl', '{}\n')
        put(self.root / 'ledger/rows.jsonl', '{}\n')
        put(self.root / 'tools/typing/param_retype.py', '# tool\n')
        git(self.root, 'init', '-q')
        self.base = commit(self.root, 'base')
        self.tree.objects(self.blobs)
        self.produced = {}

    def tearDown(self):
        shutil.rmtree(self.tmp, ignore_errors=True)

    def compiler(self, task):
        rel = '%s/obj/%s.o' % (task['run'], task['id'])
        path = self.root / rel
        path.parent.mkdir(parents=True, exist_ok=True)
        path.write_bytes(self.produced.get(task['id'], self.blobs.get(task['id'], b'')))
        return dict(object=rel, sha256=SHA(path.read_bytes()), seconds=0)

    def prove(self, rev, **kw):
        files = A.edited_from_git(self.root, rev)
        return A.prove(self.root, files, compile_tasks=self.compiler, rev=rev, ledger_rev=rev, **kw)

    def edit(self, name, text):
        (self.root / name).parent.mkdir(parents=True, exist_ok=True)
        (self.root / name).write_text(text)

    def bump_inline(self, tu):
        rows = [json.loads(l) for l in (self.root / 'ledger/layout_inline.jsonl').read_text().splitlines()]
        for r in rows:
            if r['tu_new'] == tu:
                r['offset'] += 1
        self.edit('ledger/layout_inline.jsonl', ''.join(json.dumps(r) + '\n' for r in rows))

    # -- edit classes ------------------------------------------------------------------------------------
    def test_classes(self):
        c = lambda n: A.classify(self.root, n, set())     # noqa: E731
        self.assertEqual(c('tools/typing/param_retype.py'), 'non-build')
        self.assertEqual(c('ledger/prototype_floors.jsonl'), 'non-build')
        self.assertEqual(c('ledger/layout_inline.jsonl'), 'derived')
        self.assertEqual(c('ledger/rows.jsonl'), 'authority')
        self.assertEqual(c('tools/build/mkbuild.py'), 'authority')
        self.assertEqual(A.classify(self.root, 'tools/x.py', {'tools/x.py'}), 'authority')   # configure read it

    def test_tool_and_floor_edits_do_not_block(self):
        self.edit('src/a.c', '#include "x.h"\nint a(void) { return 1; } /* typed */\n')
        self.edit('tools/typing/param_retype.py', '# tool v2\n')
        self.edit('ledger/prototype_floors.jsonl', '{"x": 1}\n')
        r = self.prove(self.base)
        self.assertEqual(r['verdict'], 'PASS', r.get('error'))
        self.assertEqual(r['scope']['non_build'], ['ledger/prototype_floors.jsonl', 'tools/typing/param_retype.py'])

    def test_layout_inline_of_edited_tu_is_accepted(self):
        self.edit('src/owner.c', 'int home(void) { return 3; } /* typed */\n')
        self.bump_inline('src/owner.c')
        r = self.prove(self.base)
        self.assertEqual(r['verdict'], 'PASS', r.get('error'))
        self.assertEqual(r['layout_inline_owners'], ['src/owner.c'])
        self.assertIn('rcopy', r['recipes'])      # the placement copy is re-projected and compared

    def test_layout_inline_of_unedited_tu_is_authority(self):
        self.edit('src/owner.c', 'int home(void) { return 3; } /* typed */\n')
        self.bump_inline('src/b.c')
        r = self.prove(self.base)
        self.assertEqual(r['verdict'], 'ERROR')
        self.assertIn('src/b.c', r['error'])

    def test_ledger_authority_still_refused(self):
        self.edit('ledger/rows.jsonl', '{"id": 1}\n')
        self.assertEqual(self.prove(self.base)['verdict'], 'ERROR')

    def test_new_translation_unit_is_refused(self):
        self.edit('src/new_tu.c', 'int n(void) { return 0; }\n')
        r = self.prove(self.base)
        self.assertEqual(r['verdict'], 'ERROR')
        self.assertIn('src/new_tu.c', r['error'])

    # -- baseline promotion ----------------------------------------------------------------------------
    def test_header_batch_then_next_batch_without_make(self):
        # Batch 1 edits a header; batch 2 edits a TU that includes it (STALE_BASE today without a make).
        self.edit('include/y.h', '#include "x.h"\n/* batch 1 */\n')
        r1 = self.prove(self.base, adopt=True)
        self.assertEqual(r1['verdict'], 'PASS', r1.get('error'))
        self.assertEqual(r1['adopted']['refreshed'], 1)
        b1 = commit(self.root, 'batch 1')
        self.edit('src/b.c', '#include "y.h"\nint b(void) { return 2; } /* batch 2 */\n')
        r2 = self.prove(b1, adopt=True)
        self.assertEqual(r2['verdict'], 'PASS', [(k, v.get('error')) for k, v in r2['recipes'].items()])

    def test_without_adopt_next_batch_is_stale(self):
        self.edit('include/y.h', '#include "x.h"\n/* batch 1 */\n')
        self.assertEqual(self.prove(self.base)['verdict'], 'PASS')
        b1 = commit(self.root, 'batch 1')
        self.edit('src/b.c', '#include "y.h"\nint b(void) { return 2; } /* batch 2 */\n')
        self.assertEqual(self.prove(b1)['verdict'], 'STALE_BASE')

    def test_changed_objects_are_never_adopted(self):
        self.edit('src/a.c', '#include "x.h"\nint a(void) { return 9; }\n')
        before = (self.root / 'build/obj/ra.proof.json').read_text()
        self.produced['ra'] = b'Z' * 64
        r = self.prove(self.base, adopt=True)
        self.assertNotEqual(r['verdict'], 'PASS')
        self.assertIn('skipped', r['adopted'])
        self.assertEqual((self.root / 'build/obj/ra.proof.json').read_text(), before)

    def test_adopt_keeps_object_bytes_and_mtime(self):
        obj = self.root / 'build/obj/ra.o'
        os.utime(obj, ns=(1, 1_000_000_000))
        self.edit('src/a.c', '#include "x.h"\nint a(void) { return 1; } /* respelled */\n')
        r = self.prove(self.base, adopt=True)
        self.assertEqual(r['adopted']['refreshed'], 1)
        self.assertEqual(obj.stat().st_mtime_ns, 1_000_000_000)    # make still sees src/a.c newer -> recompiles
        proof = json.loads(obj.with_suffix('.proof.json').read_text())
        self.assertEqual(proof['inputs']['src/a.c'], SHA((self.root / 'src/a.c').read_bytes()))


class NonBuildLedgersAreUnread(unittest.TestCase):
    def test_no_build_tool_mentions_them(self):
        names = [n.split('/', 1)[1] for n in A.NON_BUILD_LEDGERS]
        sources = [p for d in ('tools/build', 'tools/gate', 'tools/link', 'tools/fidelity') for p in (ROOT / d).rglob('*')
                   if p.suffix in ('.py', '.sh') and 'tests' not in p.parts]
        sources += [ROOT / f for f in A.AUTHORITY_FILES if (ROOT / f).is_file()]
        for path in sources:
            if path.name == 'affected.py':
                continue
            text = path.read_text(errors='replace')
            for name in names:
                self.assertIsNone(re.search(re.escape(name), text), '%s reads %s' % (path, name))


if __name__ == '__main__':
    unittest.main()
