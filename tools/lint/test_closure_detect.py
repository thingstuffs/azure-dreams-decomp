"""Detector tests on synthetic words only: encoders below build every instruction; no retail bytes.

    python3 -m unittest tools.lint.test_closure_detect
"""
import struct
import sys
import unittest
from pathlib import Path

HERE = Path(__file__).resolve().parent
sys.path.insert(0, str(HERE))
import closure_detect as D  # noqa: E402

SP, RA, A0, V0 = 29, 31, 4, 2


def addiu(rt, rs, imm):
    return 0x24000000 | rs << 21 | rt << 16 | imm & 0xffff


def sw(rt, off, base):
    return 0xac000000 | base << 21 | rt << 16 | off & 0xffff


def lw(rt, off, base):
    return 0x8c000000 | base << 21 | rt << 16 | off & 0xffff


def jal(address):
    return 0x0c000000 | (address >> 2) & 0x3ffffff


def jump(address):
    return 0x08000000 | (address >> 2) & 0x3ffffff


def beq(rs, rt, off):
    return 0x10000000 | rs << 21 | rt << 16 | off & 0xffff


JR_RA = D.JR
NOP = 0


def leaf_fn(extra=0):
    return [lw(V0, 0, A0)] + [addiu(V0, V0, 1)] * extra + [JR_RA, sw(V0, 0, A0)]


def frame_fn(calls=(), tail=True):
    body = [addiu(SP, SP, -32), sw(RA, 28, SP), lw(A0, 0, A0)] + [jal(c) for c in calls] + [NOP] * 0
    body += [addiu(V0, V0, 1), sw(V0, 0, A0)]
    if tail:
        body += [lw(RA, 28, SP), JR_RA, addiu(SP, SP, 32)]
    return body


def pack(*parts):
    words = [w for p in parts for w in p]
    return struct.pack('<%dI' % len(words), *words)


DATA = [0x00000001, 0x00000005, 0x0000000b, 0x0000000f]   # SPECIAL functions 1, 5, 11, 15 are not R3000 instructions


class ValidityTests(unittest.TestCase):
    def test_encoders_are_valid_instructions(self):
        for w in leaf_fn(2) + frame_fn((0x80011000,)):
            self.assertTrue(D.valid(w), hex(w))
        for w in DATA:
            self.assertFalse(D.valid(w), hex(w))

    def test_frame_and_branch_helpers(self):
        self.assertTrue(D.is_frame(addiu(SP, SP, -32)))
        self.assertFalse(D.is_frame(addiu(SP, SP, 32)))
        self.assertTrue(D.is_branch(beq(1, 2, 3)))


class D1Tests(unittest.TestCase):
    def test_return_word_found_with_its_body(self):
        data = pack(DATA * 4, leaf_fn(3), DATA * 4)
        hits = D.d1_hits(data, [[0, len(data)]])
        self.assertEqual(len(hits), 1)
        a, b, rule = hits[0]
        self.assertEqual(rule, 'D1')
        self.assertEqual((a, b), (16 * 4, 16 * 4 + 6 * 4))   # lw, 3 addiu, jr, delay slot

    def test_headless_tail_has_no_prologue_and_is_still_found(self):
        data = pack([0] * 8, [addiu(V0, V0, 1), sw(V0, 4, A0), lw(V0, 8, A0), JR_RA, NOP], DATA)
        (hit,) = D.d1_hits(data, [[0, len(data)]])
        self.assertEqual(hit[0], 8 * 4)      # leading zero words are not part of the body
        self.assertEqual(hit[1], (8 + 5) * 4)

    def test_previous_return_and_zero_run_stop_the_walk(self):
        data = pack(leaf_fn(), leaf_fn())
        hits = D.d1_hits(data, [[0, len(data)]])
        self.assertEqual(len(hits), 2)
        self.assertEqual(hits[1][0], len(leaf_fn()) * 4)    # starts after the first function's delay slot

    def test_nothing_outside_the_scan_set(self):
        data = pack(leaf_fn(), DATA)
        self.assertEqual(D.d1_hits(data, [[len(leaf_fn()) * 4 + 4, len(data)]]), [])

    def test_clean_data_gives_no_hit(self):
        self.assertEqual(D.d1_hits(pack(DATA * 50), [[0, 200 * 4]]), [])


class D2D5Tests(unittest.TestCase):
    def test_frame_without_return(self):
        data = pack(DATA, frame_fn(tail=False), [addiu(V0, V0, 2)] * 4, DATA)
        (hit,) = D.d2_hits(data, [[0, len(data)]])
        self.assertEqual(hit[2], 'D2')
        self.assertEqual(hit[0], 4 * 4)

    def test_frame_with_return_is_d1_not_d2(self):
        data = pack(DATA, frame_fn(), DATA)
        self.assertEqual(D.d2_hits(data, [[0, len(data)]]), [])
        self.assertEqual(len(D.d1_hits(data, [[0, len(data)]])), 1)

    def test_dense_run_needs_memory_access_and_a_branch(self):
        body = [lw(V0, 0, A0), addiu(V0, V0, 1), sw(V0, 4, A0)] + [addiu(V0, V0, 1)] * 10 + [beq(0, 0, -5)] + [addiu(V0, V0, 2)] * 3
        data = pack(DATA, body, DATA)
        self.assertEqual(len(D.d5_hits(data, [[0, len(data)]])), 1)
        short = pack(DATA, body[:12], DATA)
        self.assertEqual(D.d5_hits(short, [[0, len(short)]]), [])
        no_branch = pack(DATA, [w for w in body if w >> 26 != 4], DATA)
        self.assertEqual(D.d5_hits(no_branch, [[0, len(no_branch)]]), [])


class CallTests(unittest.TestCase):
    def setUp(self):
        # one image at file offset 0, load address 0x80010000: a caller at 0x100, a callee function at 0x200,
        # a data word block at 0x300
        self.vma = 0x80010000
        callee = frame_fn()
        self.callee_len = len(callee) * 4
        self.caller_calls = [self.vma + 0x200, self.vma + 0x204, self.vma + 0x300, self.vma + 0x2000000]
        caller = frame_fn(self.caller_calls)
        buf = bytearray(0x400)
        buf[0x100:0x100 + len(caller) * 4] = pack(caller)
        buf[0x200:0x200 + self.callee_len] = pack(callee)
        buf[0x300:0x310] = pack(DATA)
        self.data = bytes(buf)
        self.code = [(0x100, 0x100 + len(caller) * 4), (0x200, 0x200 + self.callee_len)]
        self.alloc = [D.Allocation(0x100, self.vma + 0x100, 0x300, 0, 0x400, 'town/x')]
        self.starts = {0x100, 0x200}

    def classify(self, pos):
        if any(a <= pos < b for a, b in self.code):
            return 'c_code'
        if 0x300 <= pos < 0x310:
            return 'noncode'
        return 'other'

    def test_call_kinds(self):
        hits, notes, weak = D.d3_hits(self.data, self.alloc, self.code, self.classify, self.starts)
        kinds = sorted((h[3]) for h in hits)
        self.assertEqual(kinds, ['call_into_noncode', 'call_midbody:1'])
        self.assertEqual([h[0] for h in hits if h[3].startswith('call_midbody')], [0x204])   # keyed by the entry word
        self.assertEqual(notes['calls'], 4)
        self.assertEqual(notes['outside'], 1)        # the call far outside the image is counted, not judged
        self.assertEqual(notes['to_start'], 1)
        self.assertEqual(weak, [])

    def test_wrong_delta_makes_every_call_miss_its_start(self):
        alloc = [D.Allocation(0x100, self.vma + 0x100 + 0x40, 0x300, 0, 0x400, 'town/x')]
        hits, notes, weak = D.d3_hits(self.data, alloc, self.code, self.classify, self.starts)
        self.assertEqual(notes['to_start'], 0)
        self.assertEqual(weak, ['town/x'])

    def test_pointer_to_a_run_start(self):
        runs = [0x200]
        buf = bytearray(self.data)
        buf[0x320:0x324] = struct.pack('<I', self.vma + 0x200)
        buf[0x324:0x328] = struct.pack('<I', self.vma + 0x2f0)   # points at nothing
        hits = D.d4_hits(bytes(buf), [[0x320, 0x330]], runs, lambda pos: [self.vma])
        self.assertEqual([(a, r) for a, b, r in hits], [(0x320, 'D4')])

    def test_other_program_body_with_resident_calls_all_on_starts(self):
        exe = {0x80011000, 0x80011100}
        body = [addiu(SP, SP, -16), sw(RA, 12, SP), jal(0x80011000), NOP, jal(0x80011100), NOP, lw(RA, 12, SP), JR_RA, addiu(SP, SP, 16)]
        data = pack(body)
        hit = (0, len(data), 'D1')
        self.assertEqual(len(D.d7_hits(data, [hit], (0x80010000, 0x80200000), exe)), 1)
        self.assertEqual(D.d7_hits(data, [hit], (0x80010000, 0x80200000), {0x80011000}), [])


class StreamTests(unittest.TestCase):
    def test_stream_inside_data_but_not_inside_a_stream_line(self):
        streams = [('town', 0x1000, 0x40), ('town', 0x4000, 0x40)]
        hits = D.d6_hits(streams, {'town': [[0x800, 0x2000]]}, {'town': []})
        self.assertEqual([h[1] for h in hits], [0x1000])
        hits = D.d6_hits(streams, {'town': [[0x800, 0x2000]]}, {'town': [[0x1000, 0x1040]]})
        self.assertEqual(hits, [])


class IntervalTests(unittest.TestCase):
    def test_subtract_and_intersect(self):
        self.assertEqual(D.subtract([[0, 10]], [[2, 4], [6, 8]]), [[0, 2], [4, 6], [8, 10]])
        self.assertEqual(D.intersect([[0, 10]], [[5, 20]]), [[5, 10]])


if __name__ == '__main__':
    unittest.main()
