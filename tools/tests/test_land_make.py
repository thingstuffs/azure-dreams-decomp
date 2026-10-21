"""Real Git failure boundaries for the make lander, without a disc."""
import contextlib
import io
import json
import os
from pathlib import Path
import subprocess
import tempfile
import unittest
from unittest.mock import patch

from tools.build import land_make as L


class LandMakeTests(unittest.TestCase):
    def test_verified_configuration_avoids_repeating_make_generation(self):
        with tempfile.TemporaryDirectory() as td:
            root=Path(td);(root/'build/.state').mkdir(parents=True)
            (root/'Makefile').write_text('.DEFAULT_GOAL := images\ninclude build/build.mk\n'
                'build/build.mk: tool.py\n\t@echo cache-hit >> calls\n'
                'images: object\nobject: source.c\n\t@echo unexpected-compile >> calls\n')
            files={'build/build.mk':'# verified projection\n','tool.py':'tool',
                   'source.c':'source','object':'object','object.proof.json':'proof',
                   'build/.state/headers.ok':'digest'}
            for name,data in files.items():(root/name).write_text(data)
            for name,mtime in [('build/build.mk',10),('source.c',20),('tool.py',30),('object',40)]:
                os.utime(root/name,(mtime,mtime))
            def make():
                subprocess.run(['make'],cwd=root,check=True,stdout=subprocess.DEVNULL,stderr=subprocess.PIPE)
            make();self.assertEqual((root/'calls').read_text(),'cache-hit\n')
            L.acknowledge_configuration(root)
            make();self.assertEqual((root/'calls').read_text(),'cache-hit\n')
            self.assertEqual((root/'object').stat().st_mtime,40)
            for name,data in files.items():self.assertEqual((root/name).read_text(),data)

    def test_configuration_acknowledgement_refuses_missing_or_symlink_output(self):
        with tempfile.TemporaryDirectory() as td:
            root=Path(td)/'root';(root/'build').mkdir(parents=True)
            with self.assertRaisesRegex(ValueError,'missing or unsafe'):
                L.acknowledge_configuration(root)
            outside=Path(td)/'outside.mk';outside.write_text('outside')
            (root/'build/build.mk').symlink_to(outside)
            st=outside.stat()
            with self.assertRaisesRegex(ValueError,'missing or unsafe'):
                L.acknowledge_configuration(root)
            self.assertEqual(outside.stat().st_mtime_ns,st.st_mtime_ns)

    def test_accounting_cache_verifies_proof_inputs_and_outputs(self):
        with tempfile.TemporaryDirectory() as td:
            root=Path(td)
            for name in ('src','ledger','build/landing'):(root/name).mkdir(parents=True)
            source=root/'src/a.c';source.write_text('int a;')
            calls=[]
            def step(name, argv=None, action=None):
                if action:return action()
                calls.append(name)
                if name=='levels':(root/'ledger/levels.jsonl').write_text('levels')
                if name=='status':(root/'STATUS.md').write_text('status')
            with patch('tools.build.make_evidence.checked_receipt') as proof:
                L.accounting(root,step);self.assertEqual(calls,['levels','status'])
                calls.clear();L.accounting(root,step);self.assertEqual(calls,[])
                self.assertIn('SKIP:',(root/'build/landing/levels.log').read_text())
                (root/'STATUS.md').write_text('tampered')
                L.accounting(root,step);self.assertEqual(calls,['levels','status'])
                calls.clear();st=source.stat();source.write_text('int b;')
                os.utime(source,ns=(st.st_atime_ns,st.st_mtime_ns))
                L.accounting(root,step);self.assertEqual(calls,['levels','status'])
                self.assertEqual(proof.call_count,7)
                calls.clear();proof.side_effect=ValueError('stale make check proof')
                with self.assertRaisesRegex(ValueError,'stale make check proof'):
                    L.accounting(root,step)
                self.assertEqual(calls,[])

    def test_privacy_failure_preserves_patch_and_never_commits(self):
        with tempfile.TemporaryDirectory() as td:
            root=Path(td)
            def git(*args):
                return subprocess.check_output(['git',*args],cwd=root,stderr=subprocess.DEVNULL)
            git('init','-q');git('config','user.name','Test');git('config','user.email','test@example.invalid')
            (root/'.gitignore').write_text('build/\n*.patch\n');(root/'docs').mkdir();(root/'docs/note.md').write_text('before\n')
            git('add','.');git('commit','-qm','baseline');before=git('rev-parse','HEAD')
            import difflib
            patch_files=[]
            for i,(old,new) in enumerate((('before\n','intermediate\n'),('intermediate\n','/'+'home/private\n'))):
                q=root/('sample'+str(i)+'.patch')
                q.write_text(''.join(difflib.unified_diff(old.splitlines(True),new.splitlines(True),fromfile='a/docs/note.md',tofile='b/docs/note.md')))
                patch_files.append(str(q))
            with self.assertRaisesRegex(ValueError,'privacy scrub failed'):
                L.main(['--message','must not commit',*patch_files],root=root)
            self.assertEqual(git('rev-parse','HEAD'),before)
            self.assertIn('private',(root/'docs/note.md').read_text())
            self.assertTrue((root/'build/landing/timings.json').exists())

    def test_new_debt_stops_before_build_and_never_commits(self):
        with tempfile.TemporaryDirectory() as td:
            root=Path(td)
            def git(*args):
                return subprocess.check_output(['git',*args],cwd=root,stderr=subprocess.DEVNULL)
            git('init','-q');git('config','user.name','Test');git('config','user.email','test@example.invalid')
            (root/'.gitignore').write_text('build/\n*.patch\n');(root/'src').mkdir()
            (root/'src/a.c').write_text('void f(void) {\n}\n')
            git('add','.');git('commit','-qm','baseline');before=git('rev-parse','HEAD')
            import difflib
            q=root/'debt.patch'
            q.write_text(''.join(difflib.unified_diff(['void f(void) {\n','}\n'],['void f(void) {\n','    goto x; x: ;\n','}\n'],fromfile='a/src/a.c',tofile='b/src/a.c')))
            with self.assertRaisesRegex(ValueError,'new debt in changed C: goto 0->1'):
                L.main(['--message','must not commit',str(q)],root=root)
            self.assertEqual(git('rev-parse','HEAD'),before)
            self.assertTrue((root/'build/landing/debt.json').exists())
            steps=[s['step'] for s in json.loads((root/'build/landing/timings.json').read_text())['steps']]
            self.assertEqual(steps[-1],'debt')
            self.assertNotIn('build',steps)

    def test_dirty_tree_stops_before_applying_patch(self):
        with tempfile.TemporaryDirectory() as td:
            root=Path(td)
            with patch.object(L,'command',return_value=b' M docs/note.md\n'):
                with self.assertRaisesRegex(ValueError,'clean worktree'):
                    L.main(['--message','blocked','missing.patch'],root=root)
            self.assertFalse((root/'build').exists())
