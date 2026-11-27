"""Tests of the v6 declared-class tests and landing visibility of the ownership check, on synthetic words and
synthetic worlds only (no retail bytes).

    python3 -m unittest tools.lint.test_closure_v6
"""
import json
import struct
import subprocess
import sys
import tempfile
import unittest
from pathlib import Path
from types import SimpleNamespace

HERE = Path(__file__).resolve().parent
sys.path.insert(0, str(HERE))
import closure as C  # noqa: E402
import closure_detect as D  # noqa: E402
import closure_v6 as V  # noqa: E402
from test_closure_detect import DATA, JR_RA, NOP, A0, V0, addiu, frame_fn, jal, lw, pack, sw  # noqa: E402

SHA = '0' * 64
GOOD = 'docs/e.md#jump_table'


def unit_with(data, lines, kind='file', key='town'):
    unit = SimpleNamespace(key=key, kind=kind, data=data, lines=[], funcs=[], proof=dict(functions=[]))
    unit.lines = [C.Line(key, a, b, cls, ev, SHA, 'x:%d' % n) for n, (a, b, cls, ev) in enumerate(lines)]
    return unit


def run_tests(unit, streams=None, base=None, root='.', known=frozenset()):
    findings = []
    result = V.declared_tests(root, {unit.key: unit}, streams or {}, base, findings, known)
    return sorted(k for k, _ in findings), result


class RegionTests(unittest.TestCase):
    def setUp(self):
        self.tmp = tempfile.TemporaryDirectory()
        self.addCleanup(self.tmp.cleanup)
        self.root = Path(self.tmp.name)
        (self.root / 'config').mkdir()

    def test_unreached_needs_a_ruling_row(self):
        unit = unit_with(bytes(64), [(0, 16, 'region:unreached:frag', 'config/closure_rulings.tsv#R7')])
        self.assertEqual(run_tests(unit, root=self.root)[0], ['region_unreached'])
        (self.root / V.RULINGS).write_text('# id\tsubject\ttext\nR7\tfrag\tthe owner ruled it unreached\n')
        self.assertEqual(run_tests(unit, root=self.root)[0], [])
        # a ruling id that is only a substring of a row, another file, or no key at all
        for ev in ('config/closure_rulings.tsv#R', 'docs/CLOSURE.md#R7', 'config/closure_rulings.tsv', 'x#R7'):
            unit = unit_with(bytes(64), [(0, 16, 'region:unreached:frag', ev)])
            self.assertEqual(run_tests(unit, root=self.root)[0], ['region_unreached'], ev)

    def test_other_region_lines_need_no_ruling(self):
        unit = unit_with(bytes(64), [(0, 16, 'region:other:old', 'docs/e.md'), (16, 32, 'region:stale:town:0', 'docs/e.md')])
        self.assertEqual(run_tests(unit, root=self.root)[0], [])

    def test_region_line_in_a_decoded_image_is_refused(self):
        for cls in ('region:other:x', 'region:stale:town:0', 'region:unreached:x'):
            unit = unit_with(bytes(64), [(0, 16, cls, 'docs/e.md')], kind='decoded', key='decoded:dungeon/menu')
            self.assertIn('region_decoded', run_tests(unit, root=self.root)[0], cls)
        unit = unit_with(bytes(64), [(0, 16, 'own:data', 'docs/e.md')], kind='decoded', key='decoded:dungeon/menu')
        self.assertEqual(run_tests(unit, root=self.root)[0], [])


class AckDataTests(unittest.TestCase):
    def plain_return(self):
        # words that do not look like a function: a lookup table that happens to hold a return word
        return pack([0x00010002, 0x00030004, JR_RA, 0x00050006])

    def test_data_ack_over_a_return_needs_a_listed_reason(self):
        data = self.plain_return()
        for evidence, expected in ((GOOD, []), ('docs/e.md#because', ['ack_data_reason']), ('docs/e.md', ['ack_data_reason'])):
            unit = unit_with(data, [(0, 16, 'ack:D1:data', evidence)])
            found, result = run_tests(unit)
            self.assertEqual(found, expected, evidence)
            self.assertEqual(sum(len(v) for v in result['ack_data'].values()), 1)

    def test_data_ack_over_a_function_shape_is_refused_whatever_the_reason(self):
        frame = pack(frame_fn())
        unit = unit_with(frame, [(0, len(frame), 'ack:D1:data', GOOD)])
        self.assertIn('ack_data_function', run_tests(unit)[0])
        restored = pack([addiu(29, 29, -8), 0x8fbf0004, NOP, JR_RA, addiu(29, 29, 8)])
        unit = unit_with(restored, [(0, len(restored), 'ack:D1:data', GOOD)])
        self.assertIn('ack_data_function', run_tests(unit)[0])
        calls = pack([jal(0x80020000), NOP, jal(0x80020040), NOP, JR_RA, NOP])
        unit = unit_with(calls, [(0, len(calls), 'ack:D1:data', GOOD)])
        self.assertIn('ack_data_function', run_tests(unit, known={0x80020000, 0x80020040})[0])
        # one call to a known start and one to an unknown address is not the shape
        self.assertNotIn('ack_data_function', run_tests(unit, known={0x80020000})[0])

    def test_other_verdicts_and_rules_are_not_this_test(self):
        data = self.plain_return()
        unit = unit_with(data, [(0, 16, 'ack:D1:other_program', 'docs/e.md')])
        self.assertEqual(run_tests(unit)[0], [])
        words = pack([0x00010002, 0x00030004, 0x00050006, 0x00070008])
        unit = unit_with(words, [(0, 16, 'ack:D5:data', 'docs/e.md')])      # no return word, not D1
        self.assertEqual(run_tests(unit)[0], [])


class StreamTests(unittest.TestCase):
    def test_short_streams_and_unproven_streams(self):
        proven = {('town', 0x100): (0x20, 0x100, SHA, [5, 16, 20, 0, 0, 0, 0, 0])}
        unit = unit_with(bytes(0x400), [(0x100, 0x120, 'own:stream:x', 'docs/e.md')])
        self.assertEqual(run_tests(unit, proven)[0], ['stream_short'])      # 0x20 is below the minimum
        proven = {('town', 0x100): (0x30, 0x100, SHA, [5, 16, 20, 0, 0, 0, 0, 0])}
        self.assertEqual(run_tests(unit_with(bytes(0x400), [(0x100, 0x130, 'own:stream:x', 'e')]), proven)[0], ['stream_short'])
        proven = {('town', 0x100): (0x80, 0x400, SHA, [5, 16, 20, 0, 0, 0, 0, 0])}
        self.assertEqual(run_tests(unit_with(bytes(0x400), [(0x100, 0x180, 'own:stream:x', 'e')]), proven)[0], [])
        # a row of streams.tsv has no recompression proof: it needs 0x200 compressed bytes
        row = {('town', 0x100): (0x10, 0xc, SHA, None)}
        self.assertEqual(run_tests(unit_with(bytes(0x400), [(0x100, 0x110, 'own:stream:x', 'e')]), row)[0], ['stream_short'])
        row = {('town', 0x100): (0x100, 0x300, SHA, None)}
        self.assertEqual(run_tests(unit_with(bytes(0x400), [(0x100, 0x200, 'own:stream:x', 'e')]), row)[0], ['stream_short'])
        row = {('town', 0x100): (0x300, 0x800, SHA, None)}
        self.assertEqual(run_tests(unit_with(bytes(0x400), [(0x100, 0x400, 'own:stream:x', 'e')]), row)[0], [])
        # a stream that decodes to far fewer bytes than it holds
        row = {('town', 0x100): (0x300, 0x40, SHA, None)}
        self.assertEqual(run_tests(unit_with(bytes(0x400), [(0x100, 0x400, 'own:stream:x', 'e')]), row)[0], ['stream_short'])


class GitTests(unittest.TestCase):
    def setUp(self):
        self.tmp = tempfile.TemporaryDirectory()
        self.addCleanup(self.tmp.cleanup)
        self.root = Path(self.tmp.name)
        for d in ('ledger', 'config/link/x', 'tools/lint', 'config/closure'):
            (self.root / d).mkdir(parents=True, exist_ok=True)

    def git(self, *argv):
        return subprocess.run(['git', '-c', 'user.name=t', '-c', 'user.email=t@invalid', *argv], cwd=self.root, check=True,
                              capture_output=True, text=True).stdout.strip()

    def commit(self):
        self.git('init', '-q') if not (self.root / '.git').exists() else None
        self.git('add', '-A')
        self.git('commit', '-q', '-m', 'c')
        return self.git('rev-parse', 'HEAD')

    def test_an_sdk_row_added_in_the_landing_is_refused_for_a_vendor_line(self):
        (self.root / 'ledger/sdk_objects.jsonl').write_text(json.dumps(dict(id='a/old', object='x')) + '\n')
        (self.root / 'ledger/coverage_residue.jsonl').write_text(json.dumps(dict(id='a/old', size=4)) + '\n')
        base = self.commit()
        (self.root / 'ledger/sdk_objects.jsonl').write_text(
            json.dumps(dict(id='a/old', object='x')) + '\n' + json.dumps(dict(id='a/new', object='y')) + '\n')
        (self.root / 'ledger/coverage_residue.jsonl').write_text(
            json.dumps(dict(id='a/old', size=8)) + '\n' + json.dumps(dict(id='a/new', size=4)) + '\n')
        unit = unit_with(bytes(64), [(0, 16, 'own:vendor', 'ledger/sdk_objects.jsonl#a/new'),
                                     (16, 32, 'own:vendor', 'ledger/sdk_objects.jsonl#a/old')])
        found, _ = run_tests(unit, base=base, root=self.root)
        self.assertEqual(found, ['vendor_row_new'] * 3)     # the new id, its residue row, and the old id's changed residue row
        delta = V.ledger_delta(self.root, base)
        self.assertEqual(delta['ledger/sdk_objects.jsonl']['added'], {'a/new'})
        self.assertEqual(delta['ledger/coverage_residue.jsonl']['changed'], {'a/old'})
        self.assertNotEqual(delta['ledger/sdk_objects.jsonl']['sha'], delta['ledger/sdk_objects.jsonl']['base_sha'])

    def test_an_unchanged_ledger_passes(self):
        (self.root / 'ledger/sdk_objects.jsonl').write_text(json.dumps(dict(id='a/old', object='x')) + '\n')
        (self.root / 'ledger/coverage_residue.jsonl').write_text(json.dumps(dict(id='a/old', size=4)) + '\n')
        base = self.commit()
        unit = unit_with(bytes(64), [(0, 16, 'own:vendor', 'ledger/sdk_objects.jsonl#a/old')])
        self.assertEqual(run_tests(unit, base=base, root=self.root)[0], [])

    def test_a_demoted_load_record_is_a_refusal_line_and_a_region_over_it_is_too(self):
        record = json.dumps(dict(container='town', foff=0x100, size=0x40, base=0x80100000))
        (self.root / 'ledger/instance_load_regions.jsonl').write_text(record + '\n')
        base = self.commit()
        demoted = json.dumps(dict(container='town', foff=0x100, size=0x40, base=0x80100000,
                                  placement_kind='link evidence only; retail load not asserted'))
        (self.root / 'ledger/instance_load_regions.jsonl').write_text(demoted + '\n')
        regions = C.load_regions(self.root)
        self.assertEqual(regions, [])
        unit = unit_with(bytes(0x200), [(0x100, 0x140, 'region:other:devkit', 'docs/e.md')])
        findings = []
        demoted_lines, linkdocs = V.load_changes(self.root, base, regions, {'town': unit}, findings)
        self.assertEqual(sorted(k for k, _ in findings), ['load_demoted', 'region_demoted'])
        self.assertIn('load record', demoted_lines[0][3])
        self.assertIn('"foff": 256', demoted_lines[0][3])        # the record itself is printed
        self.assertEqual(linkdocs, [])

    def test_an_unchanged_or_added_load_record_is_not_a_demotion(self):
        record = json.dumps(dict(container='town', foff=0x100, size=0x40, base=0x80100000))
        (self.root / 'ledger/instance_load_regions.jsonl').write_text(record + '\n')
        base = self.commit()
        added = json.dumps(dict(container='town', foff=0x200, size=0x40, base=0x80100000))
        (self.root / 'ledger/instance_load_regions.jsonl').write_text(record + '\n' + added + '\n')
        findings = []
        V.load_changes(self.root, base, C.load_regions(self.root), {'town': unit_with(bytes(0x400), [])}, findings)
        self.assertEqual(findings, [])

    def test_a_changed_link_document_is_listed_with_its_keys(self):
        doc = dict(container='town', foff=0, size=16, vma=0x80100000)
        (self.root / 'config/link/x/a.json').write_text(json.dumps(doc))
        base = self.commit()
        (self.root / 'config/link/x/a.json').write_text(json.dumps(dict(doc, vma=0x80200000)))
        _, linkdocs = V.load_changes(self.root, base, [], {}, [])
        self.assertEqual(linkdocs, ['LINKDOC changed config/link/x/a.json: vma'])
        (self.root / 'config/link/x/a.json').write_text(json.dumps(doc))
        self.assertEqual(V.load_changes(self.root, base, [], {}, [])[1], [])

    def test_tool_files_and_rule_constants(self):
        (self.root / 'tools/lint/closure_detect.py').write_text('REPORT_ONLY_RULES = {"D5"}\nOTHER = 1\n')
        (self.root / 'config/closure/town.tsv').write_text('a\n')
        base = self.commit()
        self.assertEqual(V.tool_changes(self.root, base), ([], []))
        (self.root / 'tools/lint/closure_detect.py').write_text('REPORT_ONLY_RULES = {"D1", "D5"}\nOTHER = 1\n')
        (self.root / 'config/closure/town.tsv').write_text('b\n')
        (self.root / 'tools/lint/test_closure_x.py').write_text('x = 1\n')
        files, constants = V.tool_changes(self.root, base)
        self.assertEqual(files, ['config/closure/town.tsv', 'tools/lint/closure_detect.py', 'tools/lint/test_closure_x.py'])
        self.assertEqual(constants, ['+ closure_detect.py:REPORT_ONLY_RULES', '- closure_detect.py:REPORT_ONLY_RULES'])

    def test_allowlist_rows_print_in_full_under_their_tags(self):
        (self.root / 'config/asm_templates.tsv').write_text('# h\ntemplate\t"nop"\nsection\t".text.a"\nblock\t".size a, 4"\t-\t-\n')
        (self.root / 'config/closure_rulings.tsv').write_text('# h\nR1\ta\told text\n')
        base = self.commit()
        (self.root / 'config/asm_templates.tsv').write_text(
            '# h\ntemplate\t"nop"\ntemplate\t"nop;nop"\nsection\t".text.a"\nsection\t".text.b"\nblock\t".size a, 5"\t-\t-\n')
        (self.root / 'config/closure_rulings.tsv').write_text('# h\nR1\ta\tnew text\nR2\tb\tmore\n')
        t = V.row_changes(self.root, base, 'config/asm_templates.tsv', 'TEMPLATE')
        self.assertIn('TEMPLATE added template\t"nop;nop"', t)
        self.assertIn('TEMPLATE added section\t".text.b"', t)
        self.assertEqual(sum(1 for l in t if l.startswith('TEMPLATE changed')), 0)
        self.assertEqual(sum(1 for l in t if l.startswith('TEMPLATE removed')), 1)
        r = V.row_changes(self.root, base, V.RULINGS, 'RULING')
        self.assertEqual(sorted(l.split(' ')[1] for l in r), ['added', 'changed'])
        self.assertTrue(any('old text' in l and 'new text' in l for l in r))
        res = dict(units={}, delta=([], [], 0), headline=(0, 0, 0, 0), base_headline=0, region_delta=([], []), findings=[],
                   template_rows=t, ruling_rows=r)
        out = V.landing_lines(res)
        self.assertTrue(all(l in out for l in t + r))

    def test_text_delta(self):
        (self.root / 'config/closure/streams.tsv').write_text('# h\na\nb\n')
        base = self.commit()
        (self.root / 'config/closure/streams.tsv').write_text('# h\nb\nc\n')
        self.assertEqual(V.text_delta(self.root, base, 'config/closure/streams.tsv'), (['c'], ['a']))


class LandingLinesTests(unittest.TestCase):
    def line(self, unit, a, b, cls, ev='e'):
        return C.Line(unit, a, b, cls, ev, SHA, 'x:1')

    def result(self, added, removed, units, base_h, h):
        return dict(units=units, delta=(added, removed, 0), headline=(h, h, 0, 0), base_headline=base_h,
                    region_delta=([], []), findings=[])

    def test_every_added_changed_and_removed_line_is_listed_in_full(self):
        old = self.line('town', 0, 16, 'own:data', 'old')
        new = self.line('town', 0, 16, 'own:untyped', 'new')
        lone_add = self.line('town', 32, 48, 'own:data')
        lone_gone = self.line('town', 64, 80, 'own:data')
        res = self.result([new, lone_add], [old, lone_gone], {}, 10, 10)
        lines = V.landing_lines(res)
        self.assertEqual([l.split()[0] for l in lines], ['ADDED', 'CHANGED', 'REMOVED'])
        self.assertIn('own:data\told', [l for l in lines if l.startswith('CHANGED')][0])
        self.assertEqual(len(V.changed_pairs([new, lone_add], [old, lone_gone])), 1)

    def test_a_removed_own_code_line_lists_the_functions_that_gained_c(self):
        unit = SimpleNamespace(key='decoded:dungeon/menu', kind='decoded', funcs=[(0x20, 0x40), (0x100, 0x140)],
                               proof=dict(functions=[dict(offset=0x20, name='update_menu', size=0x20)]))
        removed = self.line('decoded:dungeon/menu', 0x20, 0x40, 'own:code')
        res = self.result([], [removed], {'decoded:dungeon/menu': unit}, 100, 68)
        lines = V.landing_lines(res)
        self.assertTrue(any(l.startswith('GAINED C') and '1 functions, 32 B' in l for l in lines))
        self.assertIn('GAINED decoded:dungeon/menu 0x20 32 B update_menu', lines)
        self.assertFalse(any('UNMATCHED' in l for l in lines))

    def test_a_fall_with_no_function_over_the_removed_line_is_marked(self):
        unit = SimpleNamespace(key='town', kind='file', funcs=[(0x400, 0x440)], proof=None)
        removed = self.line('town', 0x20, 0x40, 'own:code')
        res = self.result([], [removed], {'town': unit}, 100, 68)
        self.assertTrue(any('UNMATCHED' in l for l in V.landing_lines(res)))

    def test_refusal_class_findings_and_load_lines_are_printed(self):
        res = self.result([], [], {}, 5, 5)
        res['findings'] = [('region_unreached', 'region_unreached town x'), ('hit', 'hit D1 open'), ('load_demoted', 'load_demoted town a..b rec')]
        res['demoted'] = [('town', 0, 16, 'load_demoted town a..b rec')]
        res['region_delta'] = (['load record town 0x0+0x10'], ['load record town 0x20+0x10'])
        res['linkdocs'] = ['LINKDOC changed config/link/x/a.json: vma']
        lines = V.landing_lines(res)
        self.assertEqual(sum(1 for l in lines if l.startswith('REFUSAL')), 2)
        res['findings'].append(('unknown', 'unknown town +10..+14 4 B: no C, no line'))
        self.assertIn('REFUSAL unknown town +10..+14 4 B: no C, no line', V.landing_lines(res))
        res['findings'].pop()
        self.assertIn('REFUSAL region_unreached town x', lines)
        self.assertFalse(any('hit D1' in l for l in lines))
        self.assertIn('LOADREGION added: load record town 0x0+0x10', lines)
        self.assertIn('LOADREGION removed: load record town 0x20+0x10', lines)
        self.assertIn('LINKDOC changed config/link/x/a.json: vma', lines)


def lui(rt, imm):
    return (15 << 26) | (rt << 16) | (imm & 0xffff)


def jump(address):
    return (2 << 26) | ((address >> 2) & 0x3ffffff)


def jr(rs):
    return (rs << 21) | 8


SP, T0, T1, S0 = 29, 8, 9, 16


class DataflowAndD8Tests(unittest.TestCase):
    def test_grounded_accesses(self):
        self.assertEqual(D.grounded_memory_ops([lw(V0, 4, SP), sw(V0, 8, SP)]), 2)
        self.assertEqual(D.grounded_memory_ops([lw(V0, 0, 28)]), 1)                        # global pointer
        self.assertEqual(D.grounded_memory_ops([lw(V0, 0, A0), sw(V0, 4, A0)]), 2)         # incoming argument
        # an argument register written in the run no longer holds the argument
        self.assertEqual(D.grounded_memory_ops([addiu(A0, A0, 0), lw(V0, 0, A0)]), 0)
        # an address built by lui and used as a base, or derived from a grounded base
        self.assertEqual(D.grounded_memory_ops([lui(T0, 0x8001), lw(V0, 0, T0), sw(V0, 4, T0)]), 2)
        self.assertEqual(D.grounded_memory_ops([lw(T0, 8, SP), lw(V0, 0, T0)]), 2)         # pointer loaded from the frame
        self.assertEqual(D.grounded_memory_ops([addiu(T0, SP, 16), lw(V0, 0, T0)]), 1)    # address of a frame slot
        # a base register nothing in the run grounds
        self.assertEqual(D.grounded_memory_ops([lw(V0, 0, S0), sw(V0, 4, T1)]), 0)
        # a grounded register overwritten by a plain value stops being an address
        self.assertEqual(D.grounded_memory_ops([lui(T0, 0x8001), addiu(T0, 0, 5), lw(V0, 0, T0)]), 0)

    def unit(self, words, starts=()):
        blob = pack(words)
        return SimpleNamespace(key='town', kind='file', data=blob, images=[], vma_starts=set(starts)), len(blob)

    def test_a_run_in_no_image_opens_only_with_dataflow_or_a_call_to_a_start(self):
        ungrounded = [lw(V0, 0, S0), sw(V0, 4, T1), lw(V0, 8, S0)] + [addiu(V0, V0, 1)] * 10 + [0x1000fffb] + [addiu(V0, V0, 2)] * 3
        grounded = [lw(V0, 0, A0), sw(V0, 4, A0), lw(V0, 8, SP)] + [addiu(V0, V0, 1)] * 10 + [0x1000fffb] + [addiu(V0, V0, 2)] * 3
        unit, size = self.unit(ungrounded)
        self.assertEqual(C.d5_note(unit, {'town': unit}, 0, size), 'no_image_ungrounded')
        unit, size = self.unit(grounded)
        self.assertEqual(C.d5_note(unit, {'town': unit}, 0, size), 'no_image')
        called = ungrounded[:-4] + [jal(0x80020000), NOP] + ungrounded[-2:]
        unit, size = self.unit(called, starts={0x80020000})
        self.assertEqual(C.d5_note(unit, {'town': unit}, 0, size), 'call_to_start,no_image')

    def test_ungrounded_runs_stay_report_only_and_the_others_open(self):
        self.assertTrue(C.report_only((0, 64, 'D5', 'no_image_ungrounded')))
        self.assertFalse(C.report_only((0, 64, 'D5', 'no_image')))
        self.assertFalse(C.report_only((0, 64, 'D5', 'call_to_start')))
        self.assertTrue(C.report_only((0, 64, 'D5', '')))
        self.assertTrue(C.report_only((0, 64, 'D8', '')))

    def body(self, ending):
        return [addiu(V0, V0, 1), lw(T0, 4, SP), addiu(T0, T0, 2), sw(T0, 8, SP), addiu(V0, V0, 3)] + ending

    def test_d8_sees_a_body_that_ends_in_a_tail_jump(self):
        data = pack(DATA * 2, self.body([jump(0x80020000), NOP]), DATA * 2)
        hits = D.d8_hits(data, [[0, len(data)]])
        self.assertEqual([(a, b, r) for a, b, r in hits], [(8 * 4, (8 + 7) * 4, 'D8')])
        data = pack(DATA * 2, self.body([jr(2), NOP]), DATA * 2)             # jr on a register that is not $31
        self.assertEqual(len(D.d8_hits(data, [[0, len(data)]])), 1)

    def test_d8_does_not_see_a_return_a_short_body_or_a_body_without_dataflow(self):
        data = pack(DATA * 2, self.body([JR_RA, NOP]), DATA * 2)             # D1 sees returns
        self.assertEqual(D.d8_hits(data, [[0, len(data)]]), [])
        data = pack(DATA * 2, [lw(T0, 4, SP), jump(0x80020000), NOP], DATA * 2)
        self.assertEqual(D.d8_hits(data, [[0, len(data)]]), [])
        ungrounded = [addiu(V0, V0, 1), lw(T0, 4, S0), addiu(T0, T0, 2), sw(T0, 8, T1), addiu(V0, V0, 3), jump(0x80020000), NOP]
        data = pack(DATA * 2, ungrounded, DATA * 2)
        self.assertEqual(D.d8_hits(data, [[0, len(data)]]), [])
        nomem = [addiu(V0, V0, n) for n in range(1, 7)] + [jump(0x80020000), NOP]
        data = pack(DATA * 2, nomem, DATA * 2)
        self.assertEqual(D.d8_hits(data, [[0, len(data)]]), [])

    def test_d8_with_known_starts_wants_a_tail_call_to_one(self):
        data = pack(DATA * 2, self.body([jump(0x80020000), NOP]), DATA * 2)
        self.assertEqual(len(D.d8_hits(data, [[0, len(data)]], starts={0x80020000})), 1)
        self.assertEqual(D.d8_hits(data, [[0, len(data)]], starts={0x80020040}), [])
        data = pack(DATA * 2, self.body([jr(2), NOP]), DATA * 2)               # an indirect jump has no known target
        self.assertEqual(D.d8_hits(data, [[0, len(data)]], starts={0x80020000}), [])
        self.assertEqual(D.d8_hits(data, [[0, len(data)]], starts=set()), [])

    def test_d8_skips_what_another_rule_took_and_is_report_only(self):
        data = pack(DATA * 2, self.body([jump(0x80020000), NOP]), DATA * 2)
        self.assertEqual(D.d8_hits(data, [[0, len(data)]], taken=[[8 * 4, 15 * 4]]), [])
        self.assertIn('D8', D.REPORT_ONLY_RULES)
        self.assertIn('D8', D.RULES)


if __name__ == '__main__':
    unittest.main()
