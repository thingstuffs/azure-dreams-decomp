"""Real Git failure boundaries for the make lander, without a disc."""
import contextlib
import io
import json
import os
from pathlib import Path
import shutil
import subprocess
import sys
import tempfile
import time
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

    def test_cast_regression_stops_at_baseline_check_before_configure(self):
        (L.ROOT/'build_ovl').mkdir(exist_ok=True)
        with tempfile.TemporaryDirectory(dir=L.ROOT/'build_ovl') as td:
            root=Path(td)
            def git(*args):
                return subprocess.check_output(['git',*args],cwd=root,stderr=subprocess.DEVNULL)
            git('init','-q');git('config','user.name','Fixture');git('config','user.email','fixture.invalid')
            (root/'.gitignore').write_text('build/\n*.patch\n')
            (root/'src').mkdir()
            before='int f(void *p) { return 0; }\n'
            (root/'src/a.c').write_text(before)
            for name in ('tools/lint/debt_check.py', 'tools/readability/score.py'):
                target=root/name
                target.parent.mkdir(parents=True,exist_ok=True)
                shutil.copyfile(L.ROOT/name,target)
            subprocess.run([sys.executable,'tools/lint/debt_check.py','--write-baseline',
                            '--out','build/debt'],cwd=root,check=True,stdout=subprocess.DEVNULL)
            git('add','.');git('commit','-qm','baseline');head=git('rev-parse','HEAD')
            import difflib
            q=root/'cast.patch'
            q.write_text(''.join(difflib.unified_diff(before.splitlines(True),
                ['int f(void *p) { return *(int *)p; }\n'],
                fromfile='a/src/a.c',tofile='b/src/a.c')))
            with self.assertRaisesRegex(ValueError,'step failed: debt-baseline'):
                L.main(['--message','must not commit',str(q)],root=root)
            self.assertEqual(git('rev-parse','HEAD'),head)
            self.assertIn('*(int *)p',(root/'src/a.c').read_text())
            steps=[s['step'] for s in json.loads((root/'build/landing/timings.json').read_text())['steps']]
            self.assertEqual(steps[-2:],['debt','debt-baseline'])
            self.assertNotIn('configure',steps)
            self.assertNotIn('build',steps)
            self.assertIn('pointer_casts 1 > baseline 0',
                          (root/'build/landing/debt-baseline.log').read_text())


class NativeCheckHookTests(unittest.TestCase):
    """The optional native compile check: skipped unless configured, fail-fast when it fails."""

    def checkout(self, folder, code, output):
        script = Path(folder)/'port'/L.NATIVE_CHECKER
        script.parent.mkdir(parents=True)
        script.write_text('import json, sys\n'
                          'open(sys.argv[0] + ".argv", "w").write(json.dumps(sys.argv[1:]))\n'
                          'print(' + repr(output) + ')\n'
                          'sys.exit(' + str(code) + ')\n')
        return {L.NATIVE_PORT_ENV: str(Path(folder)/'port')}, Path(str(script)+'.argv')

    def test_unconfigured_check_is_recorded_as_skipped_or_refused_when_required(self):
        with tempfile.TemporaryDirectory() as td:
            root = Path(td)
            with contextlib.redirect_stdout(io.StringIO()):
                self.assertEqual(L.native_check(root, environ={}), 'skipped')
            self.assertIn('SKIP: no native port checkout configured', (root/'build/landing/native-check.log').read_text())
            with contextlib.redirect_stdout(io.StringIO()):
                with self.assertRaisesRegex(ValueError, 'native check required'):
                    L.native_check(root, require=True, environ={})

    def test_configured_checker_reads_this_root_with_at_most_four_jobs(self):
        with tempfile.TemporaryDirectory() as td:
            root = Path(td)/'game'
            root.mkdir()
            env, argv_file = self.checkout(td, 0, 'NATCHECK PASS: 2 native units')
            self.assertEqual(L.native_check(root, jobs=8, environ=env), 'pass')
            argv = json.loads(argv_file.read_text())
            self.assertEqual(argv[:4], ['--root', str(root.resolve()), '--jobs', '4'])
            self.assertEqual(argv[4:], ['--report', str(root/'build/landing/native-check.json')])
            self.assertIn('NATCHECK PASS', (root/'build/landing/native-check.log').read_text())

    def test_unit_failure_names_the_units(self):
        with tempfile.TemporaryDirectory() as td:
            root = Path(td)/'game'
            root.mkdir()
            env, _ = self.checkout(td, 1, 'natcheck: UNIT game src/dungeon/func_800A4F54.c\n'
                                          '    src/dungeon/func_800A4F54.c:17:23: error: incompatible types\n'
                                          'NATCHECK FAIL: 1 unit(s)')
            with self.assertRaisesRegex(ValueError, r'native check failed \(see build/landing/native-check.log\)\n'
                                                    r'  natcheck: UNIT game src/dungeon/func_800A4F54.c\n'
                                                    r'      src/dungeon/func_800A4F54.c:17:23: error'):
                L.native_check(root, environ=env, allow_pin_drift=True)

    def test_stale_port_pins_fail_unless_explicitly_accepted(self):
        with tempfile.TemporaryDirectory() as td:
            root = Path(td)/'game'
            root.mkdir()
            env, _ = self.checkout(td, L.NATIVE_PIN_DRIFT, 'natcheck: PIN source-owners: hash differs\nNATCHECK FAIL (pins only)')
            with self.assertRaisesRegex(ValueError, 'pins only: --allow-native-pin-drift'):
                L.native_check(root, environ=env)
            self.assertEqual(L.native_check(root, environ=env, allow_pin_drift=True), 'pin-drift')
            self.assertIn('ACCEPTED', (root/'build/landing/native-check.log').read_text())

    def test_missing_checker_is_an_error_not_a_skip(self):
        with tempfile.TemporaryDirectory() as td:
            with self.assertRaisesRegex(ValueError, 'does not contain port/tools/natcheck.py'):
                L.native_check(Path(td), environ={L.NATIVE_PORT_ENV: td})

    def test_native_failure_stops_before_configure_and_never_commits(self):
        with tempfile.TemporaryDirectory() as td:
            root = Path(td)/'game'
            root.mkdir()
            def git(*args):
                return subprocess.check_output(['git',*args],cwd=root,stderr=subprocess.DEVNULL)
            git('init','-q');git('config','user.name','Test');git('config','user.email','test@example.invalid')
            (root/'.gitignore').write_text('build/\n*.patch\n');(root/'include').mkdir()
            (root/'include/entity.h').write_text('unsigned char action_id;\n')
            git('add','.');git('commit','-qm','baseline');before=git('rev-parse','HEAD')
            import difflib
            q=root/'header.patch'
            q.write_text(''.join(difflib.unified_diff(['unsigned char action_id;\n'],
                ['union { unsigned char u; signed char s; } action_id;\n'],
                fromfile='a/include/entity.h',tofile='b/include/entity.h')))
            env, _ = self.checkout(td, 1, 'natcheck: UNIT runtime port/core/control_actions.c\nNATCHECK FAIL: 1 unit(s)')
            real_run = subprocess.run
            def run(argv, *a, **k):  # the retail tools are not part of this fixture
                if any(str(v).endswith('natcheck.py') or v == 'git' for v in argv):
                    return real_run(argv, *a, **k)
                return subprocess.CompletedProcess(argv, 0)
            with patch.dict(os.environ, env), patch.object(L.subprocess, 'run', side_effect=run):
                with self.assertRaisesRegex(ValueError, 'port/core/control_actions.c'):
                    L.main(['--message','must not commit',str(q)],root=root)
            self.assertEqual(git('rev-parse','HEAD'),before)
            steps=[s['step'] for s in json.loads((root/'build/landing/timings.json').read_text())['steps']]
            self.assertEqual(steps[-1],'native-check')
            self.assertNotIn('configure',steps)


class CodemapRefreshHookTests(unittest.TestCase):
    """The post-landing code map refresh: niced, bounded, skippable and never fatal."""

    def fixture(self, td, body, db=True):
        root = Path(td)
        tool = root/'tools/codemap/codemap.py'
        tool.parent.mkdir(parents=True)
        tool.write_text('import json, os, sys, time\n'
                        'open(os.path.join(os.path.dirname(__file__), "argv.json"), "w").write('
                        'json.dumps([os.nice(0)] + sys.argv[1:]))\n' + body)
        if db:
            (root/'build').mkdir()
            (root/'build/codemap.db').write_bytes(b'')
        return root, tool.parent/'argv.json'

    def run_hook(self, root, environ, timeout=None):
        with contextlib.redirect_stdout(io.StringIO()) as out:
            result = L.codemap_refresh(root, environ=environ, timeout=timeout)
        return result, out.getvalue(), (root/'build/landing/codemap.log').read_text()

    def test_refresh_runs_niced_against_this_root(self):
        with tempfile.TemporaryDirectory() as td:
            root, argv_file = self.fixture(td, 'print("refresh: ok")\n')
            result, out, log = self.run_hook(root, {})
            self.assertEqual(result, 'pass')
            argv = json.loads(argv_file.read_text())
            self.assertEqual(argv[0], min(19, os.nice(0) + 10))                   # nice -n 10
            self.assertEqual(argv[1:], ['refresh', '--root', str(root.resolve())])
            self.assertIn('refresh: ok', log)
            self.assertIn('PASS', out)

    def test_skips(self):
        with tempfile.TemporaryDirectory() as td:
            root, argv_file = self.fixture(td, '')
            self.assertEqual(self.run_hook(root, {L.CODEMAP_ENV: '0'})[0], 'skipped')
            self.assertFalse(argv_file.exists())
        with tempfile.TemporaryDirectory() as td:
            root, argv_file = self.fixture(td, '', db=False)
            result, _, log = self.run_hook(root, {})
            self.assertEqual(result, 'skipped')
            self.assertIn('no build/codemap.db', log)
            self.assertFalse(argv_file.exists())
            self.assertEqual(self.run_hook(root, {L.CODEMAP_ENV: '1'})[0], 'pass')   # 1 builds a missing map

    def test_failure_is_a_warning_not_an_error(self):
        with tempfile.TemporaryDirectory() as td:
            root, _ = self.fixture(td, 'sys.exit("broken map")\n')
            result, out, log = self.run_hook(root, {})
            self.assertEqual(result, 'warning')
            self.assertIn('WARNING: refresh exited 1', out)
            self.assertIn('broken map', log)
        with tempfile.TemporaryDirectory() as td:
            root = Path(td)
            (root/'build').mkdir()
            (root/'build/codemap.db').write_bytes(b'')
            self.assertEqual(self.run_hook(root, {})[0], 'warning')                  # tool missing
            self.assertEqual(self.run_hook(root, {L.CODEMAP_TIMEOUT_ENV: 'soon'})[0], 'warning')

    def test_timeout_stops_the_refresh_process_group(self):
        with tempfile.TemporaryDirectory() as td:
            root, _ = self.fixture(td, 'import subprocess\n'
                                       'child = subprocess.Popen([sys.executable, "-c", "import time; time.sleep(60)"])\n'
                                       'open(os.path.join(os.path.dirname(__file__), "child"), "w").write(str(child.pid))\n'
                                       'time.sleep(60)\n')
            started = time.monotonic()
            result, out, _ = self.run_hook(root, {}, timeout=2)
            self.assertEqual(result, 'warning')
            self.assertIn('exceeded', out)
            self.assertLess(time.monotonic() - started, 30)
            child = int((root/'tools/codemap/child').read_text())
            for _ in range(50):          # the worker the refresh started went with it
                try:
                    os.kill(child, 0)
                except ProcessLookupError:
                    break
                with open('/proc/%d/stat' % child) as fh:
                    if fh.read().split(') ')[-1].startswith('Z'):
                        break
                time.sleep(0.1)
            else:
                self.fail('refresh worker survived the timeout')
