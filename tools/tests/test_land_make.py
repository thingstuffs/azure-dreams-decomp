"""Real Git failure boundaries for the make lander, without a disc."""
import contextlib
import io
import json
from pathlib import Path
import subprocess
import tempfile
import unittest
from unittest.mock import patch

from tools.build import land_make as L


class LandMakeTests(unittest.TestCase):
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
