"""sched1 call edges, flow loop weights, induction summaries and allocation views.

Pure tests use compiler-format records; tools/fixture_proof.py records real dump runs.
"""
import io
import json
import sys
import tempfile
import unittest
from contextlib import redirect_stdout
from pathlib import Path
from unittest import mock

ROOT = Path(__file__).resolve().parents[2]
for sub in ['tools', 'tools/xform', 'tools/lanes', 'tools/lanes/lanekit']:
    sys.path.insert(0, str(ROOT/sub))
import alloc_need as A
import checks as C
import diff as D
import lab as L
import loopsum as LS
import pin_evidence as PE
import duck_brief as DB

def insn(uid, pat):
    return '(insn %d 0 0 %s -1 (nil) (nil))\n' % (uid, pat)

class CallDependence(unittest.TestCase):
    def test_parameter_and_zero_call_pseudo_have_distinct_levers(self):
        sched = (insn(1, '(set (reg/v:SI 83) (reg:SI 7 a3))')
                 .replace('(nil) (nil)', '(nil) (expr_list:REG_EQUIV (mem:SI (reg:SI 0 $0)) (nil))')
                 + insn(2, '(set (reg/v:SI 83) (plus:SI (reg/v:SI 83) (const_int 52)))'))
        d = {'sched': sched, 'flow': 'Register 83 used 20 times across 80 insns; crosses 2 calls.\n'}
        facts = '; '.join(C.call_facts(d, 2))
        self.assertIn('flow calls crossed 2', facts)
        self.assertIn('REG_EQUIV-MEM present', facts)
        self.assertIn('Walk the parameter itself', facts)
        d['sched'] = insn(2, '(set (reg:SI 83) (const_int 52))')
        d['flow'] = 'Register 83 used 2 times across 5 insns.\n'
        facts = '; '.join(C.call_facts(d, 2))
        self.assertIn('flow calls crossed 0', facts)
        self.assertIn('REG_EQUIV-MEM not found', facts)

    def test_hard_set_quirk_is_distinct_from_use(self):
        facts = C.call_facts({'sched': insn(2, '(set (reg:SI 22 s6) (reg:SI 22 s6))')}, 2)
        self.assertIn('call_used_regs[i]', facts[0])
        self.assertIn('loop-index', facts[0])

    def test_only_crossing_mapped_call_gets_verdict(self):
        class Pass:
            recs = {2: {'kind': 'insn', 'links': []}, 3: {'kind': 'call_insn'}}
            def block_of(self, uid): return {'n': 1}
            def uids(self, blk): return {2, 3}
        d = {'sched': insn(2, '(set (reg:SI 83) (const_int 52))')}
        gen, ret = {2: 1, 3: 2}, {2: 3, 3: 2}
        r = C.check_call_dependence(Pass(), 2, gen.get, ret.get, d)
        self.assertEqual(r[0], 'CALL-DEPENDENCE')
        self.assertIn('call -> insn', r[1])
        self.assertIsNone(C.check_call_dependence(Pass(), 2, gen.get, gen.get, d))
        self.assertIsNone(C.check_call_dependence(Pass(), 2, gen.get, {2: 3}.get, d))

class DepthAndLoop(unittest.TestCase):
    def test_loop_notes_not_backedges_change_weight(self):
        f = insn(1, '(set (reg:SI 83) (reg:SI 84))')
        f += '(note 2 0 0 "" NOTE_INSN_LOOP_BEG)\n'
        f += insn(3, '(set (reg:SI 83) (reg:SI 84))')
        f += '(note 4 0 0 "" NOTE_INSN_LOOP_BEG)\n'
        f += insn(5, '(set (reg:SI 83) (reg:SI 84))')
        self.assertEqual(dict(A.ref_depths(f)[83]), {1: 1, 2: 1, 3: 1})
        self.assertIn('reaches', A.loop_threshold({'refs':30,'ref_depths':{1:15}},34))
        self.assertIn('short', A.loop_threshold({'refs':30,'ref_depths':{3:10}},44))
        self.assertIn('UNKNOWN', A.loop_threshold({'refs':30,'ref_depths':{1:1,2:2}},34))

    def test_summary_last_base_reduction_and_missing_init(self):
        f = ('Loop from 617 to 835: 87 real insns.\nReg 83: biv verified\n'
             'Reg 84: biv discarded\ngiv at 766 combined with giv at 772\n'
             'giv at 772 reduced to (reg:SI 263)\nCannot eliminate biv 83: biv used in insn 778.\n')
        s = '\n'.join(LS.summary(f))
        for want in ['biv verified','biv discarded','base giv 772: LAST access','loop_start',
                     'init not present','biv used in insn 778']:
            self.assertIn(want, s)
        s = '\n'.join(LS.summary(f+insn(900, '(set (reg:SI 263) (plus:SI (reg:SI 83) (const_int 49)))')))
        self.assertIn('init uid 900', s)

class AllocationView(unittest.TestCase):
    def test_renames_zero_display_distance_still_not_exact(self):
        v = {'exact':False,'total':2,'text':'[0] move s0,a0 | move s1,a0\n[1] addu s0,s0,v0 | addu s1,s1,v0\n'}
        with mock.patch.object(D.kitlib, 'score_at', return_value=v):
            raw, lines, dist = D.allocation_view({}, 'x')
        self.assertEqual(dist,0)
        self.assertFalse(raw['exact'])
        self.assertTrue(D.allocation_pins('int x ASM_REG("$16");'))
        self.assertFalse(D.allocation_pins('int x; ASM_KEEP(x);'))

    def test_lab_reports_far_candidate_without_staging(self):
        with tempfile.TemporaryDirectory() as td:
            lab = object.__new__(L.Lab)
            lab.dir = Path(td); lab.cfg = None; lab.xscreen = None; lab.raw_only = False
            lab.base = 'int x ASM_REG("$16");'; lab.sites = [1]; lab.no_jtbl = False
            lab.stage = True; lab.id = 'dungeon/test'
            lab.screen = mock.Mock(row={'id':lab.id})
            lab.screen.diff.return_value = ['+x']*250
            lab.check_cap = lambda: None; lab.log = lambda r: r
            lab.publish = mock.Mock()
            with mock.patch.object(lab, 'guards', return_value=[]), \
                 mock.patch.object(L.kitlib, 'sites', return_value=[]), \
                 mock.patch.object(D, 'allocation_view', return_value=({'exact':False,'total':125},['+x'],1)), \
                 redirect_stdout(io.StringIO()) as stdout:
                rec = lab.test('candidate','int x;',score=False)
            self.assertEqual(rec['distance'],250)
            self.assertEqual(rec['normalised_distance'],1)
            self.assertIsNone(rec['score'])
            lab.publish.assert_not_called()
            self.assertIn('--scorer --norm-regs',stdout.getvalue())

class MechanismRecords(unittest.TestCase):
    def test_duck_reaches_pass_record_and_drops_unknown_for_current_site(self):
        text = 'void f(void) {\n register s32 zero ASM_REG("$0");\n use(zero);\n}\n'
        site = list(DB.sites_of(text))[0]
        row = {'id':'dungeon/test','container':'dungeon','func':'f','c_path':'f.c','cfg':'2.7.2-cdk-G0','size':4}
        rec = dict(id=row['id'],site=0,macro=site[1],arg=site[2],line=site[5],current=True,
                   detail={'deciding_pass':'combine','variable':'zero'},hint='reload_cse negative',
                   verdict='open',found_by='research',reviewer='pending')
        with mock.patch.object(PE,'for_row',return_value=[rec]), \
             mock.patch.object(DB,'all_rows',return_value=[row]), \
             mock.patch.object(DB.screen,'compile_s',return_value=['.ent','f:','nop']), \
             mock.patch.object(DB,'sweep_verdicts',return_value={}), \
             mock.patch.object(DB,'journal_bests',return_value=[]), \
             mock.patch.object(DB,'served_by_lines',return_value=[]), \
             mock.patch.object(DB,'lane_reports',return_value=[]), \
             mock.patch.object(DB,'alloc_verdict',return_value=None):
            duck = DB.duck(row['id'],row=row,text=text)
        self.assertIn('reload_cse negative',duck)
        self.assertIn('Recorded deciding pass: combine',duck)
        self.assertNotIn('UNKNOWN: pin(s)',duck)

    def test_pass_evidence_survives_rederive_and_marks_stale(self):
        rec = dict(id='dungeon/test',in_sha='older',site=0,op='delete',macro='ASM_REG',arg='0',line=1,
                   detail={'deciding_pass':'combine','negative':True},hint='reload_cse negative',
                   verdict='open',found_by='research',reviewer='pending')
        with tempfile.TemporaryDirectory() as td:
            out = Path(td)/'pin_evidence.jsonl'; out.write_text(json.dumps(rec)+'\n')
            with mock.patch.object(PE,'OUT',out), mock.patch.object(PE,'_derive',return_value=[]), \
                 mock.patch.object(PE,'rows',return_value=[]):
                self.assertEqual(PE.build(),[rec])
                text = '\n'.join(PE.mechanism_lines('dungeon/test','new text'))
                self.assertIn('earlier text',text)
                self.assertIn('reload_cse negative',text)
                self.assertIn('Review: pending',text)

if __name__ == '__main__':
    unittest.main()
