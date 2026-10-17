"""Fresh proof obligations cannot be satisfied by a historical MATCH."""
import contextlib
import importlib.util
import io
import json
import os
from pathlib import Path
import sys
import tempfile
import unittest
from unittest.mock import patch

TOOLS=Path(__file__).resolve().parents[1]
spec=importlib.util.spec_from_file_location('required_gate',TOOLS/'build/gate_all.py')
G=importlib.util.module_from_spec(spec);sys.modules[spec.name]=G  # plan_shas pickles its task by module name
spec.loader.exec_module(G)


class RequiredWindows(unittest.TestCase):
    def setUp(self):
        self.tmp=tempfile.TemporaryDirectory(dir=os.environ.get('TMPDIR'))
        self.addCleanup(self.tmp.cleanup)
        self.root=Path(self.tmp.name);self.config=self.root/'config/overlays';self.config.mkdir(parents=True)
        self.journal=self.root/'gate.jsonl'
        for stem in ['main_a','main_b']:(self.config/(stem+'.overlay.yaml')).write_text('name: '+stem+'\n')
        self.prior=[dict(window=stem,result='MATCH',inputs_sha='same',detail='') for stem in ['main_a','main_b']]
        self.journal.write_text(''.join(json.dumps(r)+'\n' for r in self.prior))
        self.calls=[]

    def run_gate(self, *args):
        def run(path, in_process=False):
            self.calls.append(path.name)
            return dict(window=path.name.replace('.overlay.yaml',''),result='MATCH',inputs_sha='same',detail='')
        with patch.object(G,'ROOT',self.root),patch.object(G,'B',self.root),patch.object(G,'JOURNAL',self.journal), \
             patch.object(G,'superseded',return_value=set()),patch.object(G,'inputs_snapshot',side_effect=contextlib.nullcontext), \
             patch.object(G,'inputs_sha',return_value='same'),patch.object(G,'run_window',side_effect=run), \
             patch.object(sys,'argv',['gate_all.py','--workers','1','--worker-mode','subprocess',*args]), \
             contextlib.redirect_stdout(io.StringIO()),contextlib.redirect_stderr(io.StringIO()):G.main()

    def test_incremental_retains_current_windows_and_required_window_is_fresh(self):
        self.run_gate();self.assertEqual(self.calls,[])
        self.run_gate('--require-window','config/overlays/main_b.overlay.yaml')
        self.assertEqual(self.calls,['main_b.overlay.yaml'])
        final={r['window']:r for r in map(json.loads,self.journal.read_text().splitlines())}
        self.assertEqual(final,{r['window']:r for r in self.prior})

    def test_missing_superseded_or_truncated_obligation_refuses(self):
        for args in [('--require-window','config/overlays/missing.overlay.yaml'),
                     ('--require-window','config/overlays/main_a.overlay.yaml','--limit','1')]:
            with self.subTest(args=args),self.assertRaises(SystemExit):self.run_gate(*args)
        self.assertEqual(self.calls,[])

    def test_full_and_incremental_final_verdicts_are_equal(self):
        self.run_gate();first=self.journal.read_text().splitlines()
        self.run_gate('--all');self.assertEqual(len(self.calls),2)
        last={r['window']:r['result'] for r in map(json.loads,self.journal.read_text().splitlines())}
        self.assertEqual(last,{r['window']:r['result'] for r in map(json.loads,first)})

    def test_cached_failure_remains_fatal(self):
        self.journal.write_text(json.dumps(dict(self.prior[0],result='NO MATCH'))+'\n'+json.dumps(self.prior[1])+'\n')
        with self.assertRaises(SystemExit):self.run_gate()
        self.assertEqual(self.calls,[])

    def test_journal_is_compacted_to_last_verdict_per_window(self):
        # history order, a duplicate and an out-of-order window: the run leaves one line per window, sorted
        old=dict(self.prior[1],result='NO MATCH',inputs_sha='old')
        self.journal.write_text(''.join(json.dumps(r,separators=(',',':'))+'\n' for r in [old,self.prior[1],self.prior[0]]))
        self.run_gate()
        lines=self.journal.read_text().splitlines()
        self.assertEqual([json.loads(l)['window'] for l in lines],['main_a','main_b'])
        self.assertEqual([json.loads(l) for l in lines],self.prior)
        self.assertEqual(self.calls,[])
        before=self.journal.stat().st_mtime_ns;self.run_gate()
        self.assertEqual(self.journal.stat().st_mtime_ns,before)   # already compact: not rewritten

    def test_parallel_plan_equals_serial_plan(self):
        yamls=sorted(self.config.glob('*.overlay.yaml'))
        with patch.object(G,'ROOT',self.root),patch.object(G,'inputs_snapshot',side_effect=contextlib.nullcontext), \
             patch.object(G,'inputs_sha',side_effect=lambda y:'sha:'+y.name), \
             contextlib.redirect_stdout(io.StringIO()):
            serial=G.plan_shas(yamls,1);parallel=G.plan_shas(yamls,2)
        self.assertEqual(serial,parallel);self.assertEqual(serial,{y.name:'sha:'+y.name for y in yamls})

    def test_planned_error_is_raised_where_the_serial_sweep_raised_it(self):
        yamls=sorted(self.config.glob('*.overlay.yaml'))
        def boom(y):
            if y.name=='main_b.overlay.yaml':raise ValueError('unmodelled input')
            return 'ok'
        with patch.object(G,'ROOT',self.root),patch.object(G,'inputs_snapshot',side_effect=contextlib.nullcontext), \
             patch.object(G,'inputs_sha',side_effect=boom),contextlib.redirect_stdout(io.StringIO()):
            for workers in (1,2):
                plan=G.plan_shas(yamls,workers)
                self.assertEqual(G.planned_sha(plan,yamls[0]),'ok')
                with self.assertRaisesRegex(ValueError,'unmodelled input'):G.planned_sha(plan,yamls[1])

if __name__=='__main__':unittest.main()
