"""Tests of the v5 rule changes of the ownership check, on synthetic words and synthetic worlds only (no retail bytes):
member functions of module objects, chunk-wise target mapping, calls to other programs, noload table clipping,
paired-word D1 runs, exact D4, Shift-JIS D5 runs and open D5 classes, stale lines, load evidence, the startup call
to main, pointer headers, and the bootstrap's stale runs and code-line retyping.

    python3 -m unittest tools.lint.test_closure_v5
"""
import json
import struct
import sys
import unittest
from pathlib import Path

HERE = Path(__file__).resolve().parent
sys.path.insert(0, str(HERE))
import closure as C  # noqa: E402
import closure_bootstrap as B  # noqa: E402
import closure_detect as D  # noqa: E402
from test_closure import SIZE, VMA, World, base_world, sha  # noqa: E402
from test_closure_detect import DATA, JR_RA, NOP, A0, V0, addiu, frame_fn, jal, leaf_fn, lw, pack, sw  # noqa: E402


def base_lines(w):
    w.line('town', 0x400, 0x420, 'own:data')
    w.line('town', 0x500, 0x514, 'own:vendor')


def link_map(path, pieces):
    """A linker map with one `.piece_N` output section per entry: {N: [(section, address, size)]}."""
    lines = ['Linker script and memory map']
    for n, sections in pieces.items():
        lines.append('.piece_%d 0x%08x 0x%x' % (n, sections[0][1], sum(s[2] for s in sections)))
        for name, address, size in sections:
            lines.append(' %s 0x%08x 0x%x build/obj/%d.o' % (name, address, size, n))
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_text('\n'.join(lines) + '\n')


class DetectorRuleTests(unittest.TestCase):
    def test_a_run_of_paired_words_is_a_table_and_a_stub_or_a_real_function_is_not(self):
        paired = [0x24420001, 0x24420001, JR_RA, JR_RA]
        self.assertTrue(D.table_run(paired))
        self.assertTrue(D.table_run(paired + [0x24420002]))
        self.assertFalse(D.table_run([JR_RA, NOP]))                       # a bare stub is a function
        self.assertFalse(D.table_run([lw(V0, 0, A0), JR_RA, sw(V0, 0, A0)]))
        self.assertFalse(D.table_run([lw(V0, 0, A0), addiu(V0, V0, 1), JR_RA, sw(V0, 0, A0)]))   # four-word accessor
        few = [lw(V0, 0, A0), addiu(V0, V0, 1), lw(V0, 0, A0), addiu(V0, V0, 1), JR_RA, NOP]
        self.assertTrue(D.table_run(few))                                  # six words with 2 distinct instructions
        self.assertFalse(D.table_run(leaf_fn(1) + [addiu(V0, V0, 9)]))

    def test_d1_skips_a_paired_table_run_and_keeps_a_function(self):
        table = pack(DATA * 2, [0x24420001, 0x24420001, JR_RA, JR_RA], DATA * 2)
        self.assertEqual(D.d1_hits(table, [[0, len(table)]]), [])
        func = pack(DATA * 2, leaf_fn(3), DATA * 2)
        self.assertEqual([h[2] for h in D.d1_hits(func, [[0, len(func)]])], ['D1'])

    def test_d4_is_exact(self):
        data = pack([VMA + 0x40, VMA + 0x44, 0, 0])
        for ptr, expect in ((0x40, 1), (0x44, 1), (0x48, 0), (0x3c, 0)):
            hits = D.d4_hits(data, [[0, 16]], [ptr], lambda pos: [VMA])
            self.assertEqual(len(hits), expect, hex(ptr))
        # a pointer 4 bytes before a run start is not a hit any more
        self.assertEqual(D.d4_hits(pack([VMA + 0x3c]), [[0, 4]], [0x40], lambda pos: [VMA]), [])

    def dense(self, op_word):
        return [lw(V0, 0, A0), addiu(V0, V0, 1), sw(V0, 4, A0)] + [op_word] * 10 + [0x1000fffb] + [addiu(V0, V0, 2)] * 3

    def test_shift_jis_text_is_not_a_dense_run_unless_it_calls_a_known_start(self):
        code = self.dense(addiu(V0, V0, 1))
        data = pack(code)
        self.assertEqual(len(D.d5_hits(data, [[0, len(data)]])), 1)
        text = [0x88a38140 | (k & 3) for k in range(len(code))]            # every halfword carries a lead byte
        self.assertTrue(D.sjis_text(text))
        self.assertFalse(D.sjis_text(code))
        self.assertEqual(D.d5_hits(pack(text), [[0, 4 * len(text)]]), [])
        # a text-like run that the same code reads as dense (loads, a branch) is rescued by a call to a known start
        mixed = [w if k < 20 else 0x88a38140 for k, w in enumerate(code + [0x88a38140] * 40)]
        blob = pack(mixed)
        self.assertEqual(len(D.d5_hits(blob, [[0, len(blob)]])), 0 if D.sjis_text(mixed) else 1)
        if D.sjis_text(mixed):
            self.assertEqual(len(D.d5_hits(blob, [[0, len(blob)]], rescue=lambda a, b: True)), 1)

    def test_d3_target_through_the_chunk_that_is_loaded_there_and_calls_to_other_programs(self):
        fn = pack(frame_fn([VMA + 0x400, VMA + 0x104]))
        data = bytes(0x100) + fn + bytes(0x800)
        funcs = [(0x100, 0x100 + len(fn))]
        alloc = D.Allocation(0x100, VMA + 0x100, len(fn), 0, len(data), 'img')

        def classify(pos):
            return 'c_code' if 0x100 <= pos < 0x100 + len(fn) else 'noncode'
        hits, notes, _ = D.d3_hits(data, [alloc], funcs, classify, {0x100})
        self.assertEqual([h[3].split(':')[0] for h in hits], ['call_into_noncode'])
        # no chunk of the image is loaded at the target: the call is outside, not judged
        hits, notes, _ = D.d3_hits(data, [alloc], funcs, classify, {0x100}, resolve=lambda a, tv: None)
        self.assertEqual(hits, [])
        self.assertEqual(notes['outside'], 2)
        # a call to a start of another program loaded at the target is cross_image, not judged
        hits, notes, _ = D.d3_hits(data, [alloc], funcs, classify, {0x100}, cross=lambda a, kind, tv: True)
        self.assertEqual(hits, [])
        self.assertEqual(notes['cross_image'], 1)           # the call into data; the one inside its own body is a local jump


class MemberFunctionTests(unittest.TestCase):
    def world(self, with_map=True):
        # one module object (chunk 1) holds two member functions; a caller image calls the second one
        first, second = pack(frame_fn()), pack(frame_fn())
        caller = pack(frame_fn([VMA + 0x100 + len(first)]))
        w = World()
        base_lines(w)
        w.put('town', 0x100, first + second)
        w.put('town', 0x600, caller)
        n = len(first) + len(second)
        w.cover('town', [w.chunk(0, 0x100, 'import'), w.chunk(0x100, n, 'c_data', [(0x100, n)]),
                         w.chunk(0x100 + n, SIZE - 0x100 - n, 'import')], image='town/module')
        w.cover('town', [w.chunk(0, 0x600, 'import'), w.chunk(0x600, len(caller), 'c_data', [(0x600, len(caller))]),
                         w.chunk(0x600 + len(caller), SIZE - 0x600 - len(caller), 'import')], image='town/caller')
        w.put('town', 0x400, pack(DATA * 2))
        w.put('town', 0x500, pack(leaf_fn(2)))
        w.write()
        self.addCleanup(w.close)
        if with_map:
            link_map(w.root / 'build/.state/link/town_module/image.map',
                     {1: [('.text.first', VMA + 0x100, len(first)), ('.text.second', VMA + 0x100 + len(first), len(second))]})
        return w, len(first), n

    def test_member_functions_are_read_from_the_link_map_and_a_call_to_the_second_is_not_midbody(self):
        w, half, n = self.world()
        res = w.run()
        town = res['units']['town']
        self.assertIn(0x100 + half, town.starts)
        self.assertEqual(town.members['split'], 1)
        self.assertEqual(sum(1 for a, b in town.funcs if 0x100 <= a < 0x100 + n), 2)
        self.assertEqual([h for h in res['open']['town'] if h[2] == 'D3'], [])

    def test_without_the_map_the_module_is_one_range_and_the_call_is_a_midbody_hit(self):
        w, half, n = self.world(with_map=False)
        res = w.run()
        self.assertEqual(sum(1 for a, b in res['units']['town'].funcs if 0x100 <= a < 0x100 + n), 1)
        self.assertEqual([h[3].split(':')[0] for h in res['open']['town'] if h[2] == 'D3'], ['call_midbody'])

    def test_sections_that_do_not_tile_the_code_range_leave_the_chunk_whole(self):
        w, half, n = self.world(with_map=False)
        link_map(w.root / 'build/.state/link/town_module/image.map', {1: [('.text.first', VMA + 0x100, half)]})
        res = w.run()
        self.assertEqual(res['units']['town'].members['whole'], 1)
        self.assertEqual(sum(1 for a, b in res['units']['town'].funcs if 0x100 <= a < 0x100 + n), 1)

    def test_a_stale_link_script_is_an_input_error(self):
        w, half, n = self.world()
        path = w.root / 'build/.state/origins/town_module.json'
        doc = json.loads(path.read_text())
        doc['linker_script_sha256'] = sha(b'other')
        blob = json.dumps(doc, sort_keys=True).encode()
        path.write_bytes(blob)
        receipt = json.loads((w.root / 'build/check.json').read_text())
        for r in receipt['results']:
            if r['image'] == 'town/module':
                r['origin_sha256'] = sha(blob)
        (w.root / 'build/check.json').write_text(json.dumps(receipt))
        (w.root / 'build/.state/link/town_module/image.ld').write_text('script')
        with self.assertRaises(C.InputError):
            w.run()


class CallTargetTests(unittest.TestCase):
    def caller_world(self, first_vma):
        """town/caller calls VMA+0x400 (own:data at the caller's own delta); the image's first chunk loads at first_vma."""
        caller = pack(frame_fn([VMA + 0x400]))
        w = base_world()
        base_lines(w)
        w.put('town', 0x600, caller)
        w.cover('town', [w.chunk(0, 0x600, 'import', vma=first_vma), w.chunk(0x600, len(caller), 'c_data', [(0x600, len(caller))]),
                         w.chunk(0x600 + len(caller), SIZE - 0x600 - len(caller), 'import')], image='town/caller')
        w.write()
        self.addCleanup(w.close)
        return w

    def test_target_inside_a_chunk_loaded_at_the_callers_delta_is_judged(self):
        w = self.caller_world(VMA)
        self.assertEqual([h[3] for h in w.run()['open']['town'] if h[2] == 'D3'], ['call_into_noncode'])

    def test_target_in_no_chunk_of_the_image_is_not_judged(self):
        w = self.caller_world(0x80200000)         # the first chunk loads elsewhere: nothing is loaded at VMA+0x400
        res = w.run()
        self.assertEqual([h for h in res['open']['town'] if h[2] == 'D3'], [])
        self.assertGreaterEqual(res['notes']['town']['outside'], 1)

    def test_midbody_call_to_a_start_of_another_program_at_that_address_is_not_judged(self):
        caller = pack(frame_fn([VMA + 0x104]))
        w = base_world()
        base_lines(w)
        w.put('town', 0x600, caller)
        w.cover('town', [w.chunk(0, 0x600, 'import'), w.chunk(0x600, len(caller), 'c_data', [(0x600, len(caller))]),
                         w.chunk(0x600 + len(caller), SIZE - 0x600 - len(caller), 'import')], image='town/caller')
        fn = pack(frame_fn())
        w.put('dungeon', 0x104, fn)
        w.cover('dungeon', [w.chunk(0, 0x104, 'import'), w.chunk(0x104, len(fn), 'c_data', [(0x104, len(fn))]),
                            w.chunk(0x104 + len(fn), SIZE - 0x104 - len(fn), 'import')], image='dungeon/other')
        w.write()
        self.addCleanup(w.close)
        res = w.run()
        self.assertEqual([h for h in res['open']['town'] if h[2] == 'D3'], [])
        self.assertEqual(res['notes']['town']['cross_image'], 1)

    def test_executable_call_into_the_engine_load_range_is_judged_against_the_engine_images(self):
        engine_vma = 0x80100000
        w = base_world()
        base_lines(w)
        # the executable: file offset 0x400 loads at 0x80100200 (the delta puts its own bytes under an engine address)
        delta = 0x80100200 - 0x400
        call = pack(frame_fn([0x80100200]))
        w.put('slus', 0x400, pack(DATA * 2))
        w.put('slus', 0x600, call)
        w.line('slus', 0x400, 0x420, 'own:data')
        w.cover('slus', [w.chunk(0, 0x600, 'import', vma=delta), w.chunk(0x600, len(call), 'c_data', [(0x600, len(call))], vma=delta + 0x600),
                         w.chunk(0x600 + len(call), SIZE - 0x600 - len(call), 'import', vma=delta + 0x600 + len(call))],
                image='slus/slus_bin', vma=delta)
        fn = pack(frame_fn())
        w.put('town', 0x200, fn)
        w.cover('town', [w.chunk(0, 0x200, 'import', vma=engine_vma), w.chunk(0x200, len(fn), 'c_data', [(0x200, len(fn))], vma=engine_vma + 0x200),
                         w.chunk(0x200 + len(fn), SIZE - 0x200 - len(fn), 'import', vma=engine_vma + 0x200 + len(fn))],
                image='town/engine', vma=engine_vma)
        w.write()
        self.addCleanup(w.close)
        res = w.run()
        self.assertEqual([h for h in res['open']['slus'] if h[2] == 'D3'], [])
        self.assertEqual(res['notes']['slus']['cross_image'], 1)
        # an engine-range target that is not a function start of an engine image stays a hit
        w.close()
        w = base_world()
        base_lines(w)
        w.put('slus', 0x400, pack(DATA * 2))
        w.put('slus', 0x600, pack(frame_fn([0x80100200])))
        w.line('slus', 0x400, 0x420, 'own:data')
        w.cover('slus', [w.chunk(0, 0x600, 'import', vma=delta), w.chunk(0x600, len(call), 'c_data', [(0x600, len(call))], vma=delta + 0x600),
                         w.chunk(0x600 + len(call), SIZE - 0x600 - len(call), 'import', vma=delta + 0x600 + len(call))],
                image='slus/slus_bin', vma=delta)
        w.put('town', 0x204, fn)
        w.cover('town', [w.chunk(0, 0x204, 'import', vma=engine_vma), w.chunk(0x204, len(fn), 'c_data', [(0x204, len(fn))], vma=engine_vma + 0x204),
                         w.chunk(0x204 + len(fn), SIZE - 0x204 - len(fn), 'import', vma=engine_vma + 0x204 + len(fn))],
                image='town/engine', vma=engine_vma)
        w.write()
        self.addCleanup(w.close)
        self.assertEqual([h[3] for h in w.run()['open']['slus'] if h[2] == 'D3'], ['call_into_noncode'])

    def test_a_call_into_data_from_inside_a_region_line_is_resolved_by_it(self):
        w = self.caller_world(VMA)
        w.close()
        caller = pack(frame_fn([VMA + 0x400]))
        w = base_world()
        base_lines(w)
        w.put('town', 0x600, caller)
        w.cover('town', [w.chunk(0, 0x600, 'import'), w.chunk(0x600, len(caller), 'c_data', [(0x600, len(caller))]),
                         w.chunk(0x600 + len(caller), SIZE - 0x600 - len(caller), 'import')], image='town/caller')
        w.line('town', 0x600, 0x600 + len(caller), 'region:other:old_program')
        w.write()
        self.addCleanup(w.close)
        res = w.run()
        self.assertEqual([h for h in res['open']['town'] if h[2] == 'D3'], [])
        self.assertTrue(any(r[2] == 'D3' for r in res['resolved']['town']))


class NoloadTableTests(unittest.TestCase):
    def world(self, table_origin):
        fn = pack(frame_fn())
        w = World()
        base_lines(w)
        w.put('town', 0x100, fn)
        w.put('town', 0x400, pack(DATA * 2))
        w.put('town', 0x500, pack(leaf_fn(2)))
        w.cover('town', [w.chunk(0, 0xF0, 'import'), w.chunk(0xF0, 0x14, 'c_data', origin=table_origin, vma=VMA + 0xF0),
                         w.chunk(0x100, len(fn), 'c_data', [(0x100, len(fn))]),
                         w.chunk(0x100 + len(fn), SIZE - 0x100 - len(fn), 'import'), w.chunk(0x500, 0x14, 'assembly', kind='platform_asm')])
        w.write()
        self.addCleanup(w.close)
        return w, len(fn)

    def test_a_table_record_stops_at_the_next_compiled_function(self):
        w, n = self.world('noload_table')
        town = w.run()['units']['town']
        self.assertEqual(town.conflicts, [])
        self.assertEqual(C.total(town.c_code), n)
        self.assertEqual(C.total(town.table_clipped), 4)

    def test_other_compiled_data_that_overlaps_code_is_still_a_conflict(self):
        w, n = self.world('original_object')
        town = w.run()['units']['town']
        self.assertEqual(C.total(town.conflicts), 4)


class ClassTestTests(unittest.TestCase):
    def test_load_evidence_is_a_retail_load_inside_retail_ram(self):
        self.assertTrue(C.establishes_load(dict(base=0x80016000, method='validated packed-CD loader record')))
        self.assertTrue(C.establishes_load(dict(base=0x80020000, placement_kind='retail loader destination; execution not newly established')))
        self.assertFalse(C.establishes_load(dict(base=0x80016000, placement_kind='linked base only; retail load/execution not established')))
        self.assertFalse(C.establishes_load(dict(base=0x80016000, placement_kind='link-evidence; runtime loading not asserted')))
        self.assertFalse(C.establishes_load(dict(base=0x80700000)))
        self.assertFalse(C.establishes_load(dict(base=0x80003000)))
        self.assertFalse(C.establishes_load(dict(base=0xa0700000)))

    def test_load_regions_keep_only_records_that_establish_a_load_and_follow_a_documents_record(self):
        import tempfile
        with tempfile.TemporaryDirectory() as tmp:
            root = Path(tmp)
            (root / 'ledger').mkdir()
            (root / 'config/link/town').mkdir(parents=True)
            good = json.dumps(dict(container='town', foff=0x100, size=0x100, base=0x80016000, method='validated loader record'))
            weak = json.dumps(dict(container='town', foff=0x300, size=0x100, base=0x80016000, placement_kind='linked base only; x'))
            high = json.dumps(dict(container='town', foff=0x500, size=0x100, base=0x80700000))
            (root / 'ledger/instance_load_regions.jsonl').write_text('\n'.join([good, weak, high]) + '\n')
            doc = lambda foff, line: dict(image='town/x', container='town', foff=foff, size='0x100', vma='0x80016000',
                                          load_evidence=dict(path='ledger/instance_load_regions.jsonl', record_sha256=sha(line.encode())))
            (root / 'config/link/town/a.json').write_text(json.dumps(doc('0x100', good)))
            (root / 'config/link/town/b.json').write_text(json.dumps(doc('0x700', weak)))
            dropped = []
            regions = C.load_regions(root, dropped)
            self.assertEqual(sorted(regions), [('town', 0x100, 0x200), ('town', 0x100, 0x200)])
            self.assertEqual(sorted(dropped), [('town', 0x300, 0x400), ('town', 0x500, 0x600), ('town', 0x700, 0x800)])

    def test_startup_call_to_main_is_the_one_vendor_exception(self):
        class U:
            pass
        u = U()
        u.key, u.data = 'slus', pack([jal(0x80010100), NOP, jal(0x80010200), NOP])
        u.pages = {0: {0x80010000}}
        u.starts = {0x100, 0x200}
        u.named = {'main': 0x100}
        findings = []
        C.vendor_test(u, C.Line('slus', 0, 16, 'own:vendor', 'x', 'y', 'w'), findings)
        self.assertEqual(len(findings), 1)          # the call to 0x200 is not main
        self.assertIn('0x200', findings[0][1])
        u.named = {}
        findings = []
        C.vendor_test(u, C.Line('slus', 0, 16, 'own:vendor', 'x', 'y', 'w'), findings)
        self.assertEqual(len(findings), 2)

    def test_pointer_words_to_function_starts_and_the_zero_word_beside_them(self):
        class U:
            pass
        u = U()
        u.vma_starts = {0x80010100, 0x80010124}
        u.data = pack([0x80010100, 0x80010124, 0, 0x24420001, 0x80010100, 0, 0, 0])
        self.assertEqual(C.pointer_edges(u, 0, 32), [[0, 12], [16, 32]])   # the leading and the trailing header
        self.assertEqual(C.pointer_words(u, 0, 32), [[0, 12], [16, 24]])
        u.data = pack([0x24420001, 0x80010100, 0])
        self.assertEqual(C.pointer_edges(u, 0, 12), [[4, 12]])        # a trailing header
        u.data = pack([0x24420001, 0x24420002])
        self.assertEqual(C.pointer_edges(u, 0, 8), [])
        u.data = pack([0, 0, 0x24420002])
        self.assertEqual(C.pointer_edges(u, 0, 12), [])                # zero words alone are not a pointer header

    def test_own_data_over_a_pointer_header_is_not_a_code_label_finding_but_other_words_are(self):
        w = base_world()
        base_lines(w)
        w.put('town', 0x700, struct.pack('<III', VMA + 0x100, 0, VMA + 0x100))
        w.line('town', 0x700, 0x70C, 'own:data')
        w.labels['town']['code'] = [[0x700, 0x70C]]
        w.write()
        self.addCleanup(w.close)
        self.assertNotIn('own_data', w.kinds(w.run()))
        w.put('town', 0x700, struct.pack('<III', VMA + 0x100, 0, 0x24420001))
        (w.root / C.DISC_PATHS['town']).write_bytes(bytes(w.data['town']))
        path = w.root / 'config/closure/town.tsv'
        text = path.read_text().splitlines()
        text = [l if not l.startswith('0x700') else '0x700\t0x70C\town:data\t%s\t%s' % (w.evidence, C.line_digest(bytes(w.data['town']), 0x700, 0x70C)) for l in text]
        path.write_text('\n'.join(text).replace('\\x0b', '') + '\n')
        recs = (w.root / 'config/link_graph/files.000.jsonl').read_text().splitlines()
        import hashlib
        out = []
        for r in recs:
            d = json.loads(r)
            if d['id'] == 'town':
                d['sha1'] = hashlib.sha1(bytes(w.data['town'])).hexdigest()
            out.append(json.dumps(d))
        (w.root / 'config/link_graph/files.000.jsonl').write_text('\n'.join(out) + '\n')
        self.assertIn('own_data', w.kinds(w.run()))

    def test_a_dense_run_in_no_image_is_open_and_one_inside_an_image_is_report_only(self):
        body = [lw(V0, 0, A0), addiu(V0, V0, 1), sw(V0, 4, A0)] + [addiu(V0, V0, 1)] * 10 + [0x1000fffb] + [addiu(V0, V0, 2)] * 3
        w = base_world()
        base_lines(w)
        w.put('town', 0xC00, pack(body))
        w.line('town', 0xC00, 0xC00 + len(body) * 4, 'own:data')
        w.write()
        self.addCleanup(w.close)
        res = w.run()
        self.assertEqual(res['open']['town'], [])                      # the base world's image covers the whole file
        w.close()
        w = World()
        base_lines(w)
        w.put('town', 0x100, pack(frame_fn()))
        w.put('town', 0x400, pack(DATA * 2))
        w.put('town', 0x500, pack(leaf_fn(2)))
        n = len(frame_fn()) * 4
        w.cover('town', [w.chunk(0, 0x100, 'import'), w.chunk(0x100, n, 'c_data', [(0x100, n)]), w.chunk(0x100 + n, 0x600 - 0x100 - n, 'import'),
                         w.chunk(0x500, 0x14, 'assembly', kind='platform_asm')], size=0x600)
        w.put('town', 0xC00, pack(body))
        w.line('town', 0xC00, 0xC00 + len(body) * 4, 'own:data')
        w.write()
        self.addCleanup(w.close)
        res = w.run()
        self.assertEqual([(h[2], h[3]) for h in res['open']['town']], [('D5', 'no_image')])
        self.assertTrue(any('code_fragment_in_no_image' in line for line in C.summary(res)))


class BootstrapTests(unittest.TestCase):
    def test_stale_runs_are_the_maximal_word_for_word_equal_runs_inside_the_windows(self):
        words = 40
        town = bytearray(pack([0x24420001 + k for k in range(words)]))
        dung = bytearray(town)
        dung[4 * 20:4 * 20 + 4] = struct.pack('<I', 0x24420fff)            # one word differs in the middle
        runs = B.stale_runs(bytes(dung), bytes(town), [(0, 160)], least_words=4)
        self.assertEqual(runs, [[0, 80], [84, 160]])
        self.assertEqual(B.stale_runs(bytes(dung), bytes(town), [(0, 160)], least_words=21), [])
        self.assertEqual(B.stale_runs(bytes(dung), bytes(town), [(88, 160)], least_words=4), [[88, 160]])
        # zero words at the ends are trimmed and a run is never reported outside a window
        zero = bytes(16) + bytes(town[:64]) + bytes(16)
        self.assertEqual(B.stale_runs(zero, zero, [(0, len(zero))], least_words=4), [[16, 80]])

    def unit(self, words):
        class U:
            pass
        u = U()
        u.vma_starts = {0x80010100}
        u.data = pack(words)
        u.size = len(u.data)
        return u

    def test_a_census_code_label_that_is_not_whole_words_or_is_a_pointer_header_is_not_code(self):
        u = self.unit([0x24420001, 0x24420002, 0x80010100, 0, 0x24420003, 0x24420004, 0x24420005])
        plan = B.Plan(u)
        plan.lines = [(0, 2, 'own:code', 'link/town/x.tsv'),               # shorter than a word
                      (2, 14, 'own:code', 'link/town/x.tsv'),              # unaligned both ends, a header inside
                      (16, 28, 'own:code', 'link/town/x.tsv'),
                      (0, 0 + 0, 'own:vendor', 'e')]
        plan.lines = plan.lines[:3]
        B.retype_code_lines(u, plan)
        classes = sorted((a, b, c) for a, b, c, _ in plan.lines)
        self.assertEqual(classes, [(0, 2, 'own:untyped'), (2, 4, 'own:untyped'), (4, 8, 'own:code'), (8, 12, 'own:data'),
                                   (12, 14, 'own:untyped'), (16, 28, 'own:code')])
        # a header of pointers at the start of an aligned line becomes data
        u = self.unit([0x80010100, 0, 0x24420003, 0x24420004])
        plan = B.Plan(u)
        plan.lines = [(0, 16, 'own:code', 'link/town/x.tsv'), (0, 0, 'own:code', 'ledger/rows.jsonl')][:1]
        B.retype_code_lines(u, plan)
        self.assertEqual(sorted((a, b, c) for a, b, c, _ in plan.lines), [(0, 8, 'own:data'), (8, 16, 'own:code')])
        # assembly evidence is not touched
        plan = B.Plan(u)
        plan.lines = [(1, 6, 'own:code', 'ledger/rows.jsonl')]
        B.retype_code_lines(u, plan)
        self.assertEqual(plan.lines, [(1, 6, 'own:code', 'ledger/rows.jsonl')])


if __name__ == '__main__':
    unittest.main()
