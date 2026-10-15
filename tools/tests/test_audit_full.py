"""Quiet-time scheduling, failure localization and infrastructure holds."""
import json
import os
from pathlib import Path
import sys
import tempfile
import unittest
from unittest.mock import patch

sys.path.insert(0,str(Path(__file__).resolve().parents[1]))
import audit_full as A


class Audits(unittest.TestCase):
    def test_cadence_dedup_and_queue_without_a_worker(self):
        with tempfile.TemporaryDirectory(dir=os.environ.get('TMPDIR')) as td,patch.object(A,'git',side_effect=lambda root,*args:args[-1].removesuffix('^{commit}')),patch.object(A,'run_commit') as run:
            root=Path(td);queue=root/'queue'
            results=[A.record_landing(root,str(i),every=5,queue=queue) for i in range(1,6)]
            self.assertEqual([r['queued'] for r in results],[False]*4+[True])
            self.assertIsNone(A.record_landing(root,'5',every=5,queue=queue))
            self.assertEqual(len(list((queue/'requests').glob('*.json'))),1)
            run.assert_not_called()
            with self.assertRaises(ValueError):A.record_landing(root,'6',every=0,queue=queue)

    def test_bisect_finds_first_bad_even_with_repairs(self):
        commits=[str(i) for i in range(12)]
        results={c:'PASS' if int(c)<3 or 4<=int(c)<=8 else 'FAIL' for c in commits}
        result=A.bisect_first(commits,results.__getitem__)
        self.assertEqual(result['first_bad'],'3');self.assertEqual(result['last_good'],'2')
        self.assertTrue(result['first_parent_prefix_verified'])

    def test_infrastructure_error_is_hold_not_first_bad(self):
        result=A.bisect_first(['good','error','bad'],lambda c:'ERROR')
        self.assertEqual(result['result'],'HOLD');self.assertNotIn('first_bad',result)

    def test_full_audit_explicitly_uses_cold_full_gate_and_final_validation(self):
        stages=dict(A.stages(Path('/isolated'),8))
        self.assertIn('--all',stages['gate-all'])
        self.assertIn('--validate-only',stages['certificate-validation'])
        self.assertEqual(stages['row-db-final'][-1],'check')
        self.assertIn('cold-levels',stages);self.assertIn('cold-status',stages)

    def test_snapshot_failure_writes_error_report_and_does_not_audit_live(self):
        with tempfile.TemporaryDirectory(dir=os.environ.get('TMPDIR')) as td,patch.object(A,'snapshot',side_effect=ValueError('linked tracked input')),patch.object(A.subprocess,'run') as run:
            root=Path(td);result=A.run_commit(root,'commit',root/'out')
            self.assertEqual(result['result'],'ERROR');run.assert_not_called()
            self.assertEqual(json.loads((root/'out/result.json').read_text())['result'],'ERROR')

if __name__=='__main__':unittest.main()


class ArchiveLinks(unittest.TestCase):
    def archive(self,escape=False):
        import io,tarfile
        stream=io.BytesIO()
        with tarfile.open(fileobj=stream,mode='w') as tar:
            data=b'print("snapshot")\n';m=tarfile.TarInfo('tools/build/tool.py');m.size=len(data);tar.addfile(m,io.BytesIO(data))
            link=tarfile.TarInfo('tools/gate/tool.py');link.type=tarfile.SYMTYPE
            link.linkname='../../../../escape' if escape else '../build/tool.py';tar.addfile(link)
        return stream.getvalue()

    def test_internal_tool_shims_resolve_inside_snapshot(self):
        with tempfile.TemporaryDirectory(dir=os.environ.get('TMPDIR')) as td:
            root=Path(td);source=root/'source';dest=root/'snapshot';source.mkdir();dest.mkdir()
            for name in ('containers','extract'):(source/'work/disc'/name).mkdir(parents=True)
            with patch.object(A.subprocess,'check_output',return_value=self.archive()):A.snapshot(source,'commit',dest)
            self.assertEqual((dest/'tools/gate/tool.py').resolve(),dest/'tools/build/tool.py')
            self.assertEqual((dest/'tools/gate/tool.py').read_text(),'print("snapshot")\n')

    def test_escaping_tracked_links_refuse_before_extraction(self):
        with tempfile.TemporaryDirectory(dir=os.environ.get('TMPDIR')) as td:
            root=Path(td);source=root/'source';dest=root/'snapshot';source.mkdir();dest.mkdir()
            with patch.object(A.subprocess,'check_output',return_value=self.archive(escape=True)),self.assertRaisesRegex(ValueError,'escapes snapshot'):
                A.snapshot(source,'commit',dest)
            self.assertEqual(list(dest.iterdir()),[])


class Isolation(unittest.TestCase):
    def test_stage_cwd_and_log_descriptors_are_outside_live_source(self):
        with tempfile.TemporaryDirectory(dir=os.environ.get('TMPDIR')) as td:
            source=Path(td)/'source';source.mkdir();out=source/'reports/result'
            calls=[]
            def execute(argv,root,env,stream):
                self.assertFalse(root.is_relative_to(source))
                self.assertFalse(Path(stream.name).is_relative_to(source))
                self.assertEqual(env['AZURE_ROW_CACHE'],'0');calls.append(argv);return 0
            with patch.object(A,'snapshot'),patch.object(A,'execute',side_effect=execute):result=A.run_commit(source,'commit',out)
            self.assertEqual(result['result'],'PASS');self.assertEqual(len(calls),9)
            self.assertTrue((out/'gate-all.log').is_file())

    def test_timed_out_stage_cancels_its_private_process_group(self):
        import signal,subprocess
        from unittest.mock import Mock
        child=Mock(pid=123456);child.wait.side_effect=[subprocess.TimeoutExpired('audit',1),0]
        with patch.object(A.subprocess,'Popen',return_value=child) as spawn,patch.object(A.os,'killpg') as kill:
            with self.assertRaises(subprocess.TimeoutExpired):A.execute(['tool'],Path('/snapshot'),{},None,timeout=1)
            self.assertTrue(spawn.call_args.kwargs['start_new_session'])
            kill.assert_called_once_with(child.pid,signal.SIGTERM)


class AuditEnvironment(unittest.TestCase):
    def test_snapshot_uses_audited_assembler_source_and_shared_compiler_binaries(self):
        import io,tarfile
        stream=io.BytesIO()
        with tarfile.open(fileobj=stream,mode='w') as tar:
            data=b'audited assembler';m=tarfile.TarInfo('tools/maspsx/maspsx.py');m.size=len(data);tar.addfile(m,io.BytesIO(data))
        with tempfile.TemporaryDirectory(dir=os.environ.get('TMPDIR')) as td:
            root=Path(td);source=root/'source';dest=root/'snapshot';source.mkdir();dest.mkdir()
            for name in ('containers','extract'):(source/'work/disc'/name).mkdir(parents=True)
            (source/'toolchain/compilers').mkdir(parents=True);(source/'toolchain/maspsx').mkdir()
            (source/'toolchain/maspsx/maspsx.py').write_text('live assembler')
            with patch.object(A.subprocess,'check_output',return_value=stream.getvalue()):A.snapshot(source,'commit',dest)
            self.assertEqual((dest/'toolchain/maspsx/maspsx.py').read_text(),'audited assembler')
            self.assertEqual((dest/'toolchain/compilers').resolve(),source/'toolchain/compilers')

    def test_changed_environment_cannot_be_bisected_as_a_source_regression(self):
        with tempfile.TemporaryDirectory(dir=os.environ.get('TMPDIR')) as td:
            root=Path(td);queue=root/'queue';(queue/'requests').mkdir(parents=True)
            (queue/'requests/bad.json').write_text(json.dumps(dict(commit='bad')))
            (queue/'last-good.json').write_text(json.dumps(dict(commit='good')))
            def git(root,*args):
                if args[0]=='rev-parse':return 'bad'
                return 'bad' if '--reverse' in args else 'bad\ngood'
            with patch.object(A,'git',side_effect=git),patch.object(A,'run_commit',side_effect=[dict(result='FAIL'),dict(result='FAIL')]),patch.object(A,'bisect_first') as bisect:
                result=A.drain(root,queue)
            bisect.assert_not_called();self.assertEqual(result[0]['bisect']['result'],'HOLD')
            self.assertIn('current environment',result[0]['bisect']['reason'])


class AuditExitStatus(unittest.TestCase):
    def test_scheduled_worker_returns_failure_if_any_audit_fails(self):
        import contextlib,io
        with tempfile.TemporaryDirectory(dir=os.environ.get('TMPDIR')) as td:
            root=Path(td)
            for result,rc in [([dict(result='FAIL')],1),([dict(result='ERROR')],1),([dict(result='PASS')],0),([],0)]:
                with patch.object(A,'drain',return_value=result),contextlib.redirect_stdout(io.StringIO()):
                    self.assertEqual(A.main(['--root',str(root),'--queue',str(root/'queue'),'--drain']),rc)
