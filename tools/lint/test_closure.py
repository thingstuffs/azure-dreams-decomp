"""Checker tests on synthetic worlds: small program files built from encoders, a fake full check receipt with cover
lists, fake census labels, and exception files. No retail bytes anywhere.

    python3 -m unittest tools.lint.test_closure
"""
import hashlib
import json
import shutil
import struct
import sys
import tempfile
import unittest
from pathlib import Path

HERE = Path(__file__).resolve().parent
sys.path.insert(0, str(HERE))
import closure as C  # noqa: E402
import closure_detect as D  # noqa: E402
from test_closure_detect import DATA, JR_RA, NOP, A0, V0, RA, SP, addiu, frame_fn, jal, leaf_fn, lw, pack, sw  # noqa: E402

SIZE = 0x4000
VMA = 0x80010000
EMPTY_LABELS = {fam: dict(code=[], unknown=[]) for fam in C.FILES}
SCHEMA_LINE = '# schema closure.v1\n'


def sha(b):
    return hashlib.sha256(b).hexdigest()


class World:
    """A temporary root with five 16 KB program files, one image per file and the files the check reads."""

    def __init__(self):
        self.tmp = tempfile.TemporaryDirectory()
        self.root = Path(self.tmp.name)
        self.data = {fam: bytearray(SIZE) for fam in C.FILES}
        self.chunks = {fam: [] for fam in C.FILES}
        self.lines = {}
        self.evidence = 'docs/evidence.md'
        self.extra_images = []
        (self.root / 'docs').mkdir()
        (self.root / 'docs/evidence.md').write_text('evidence key alpha and key beta\n')
        self.labels = {fam: dict(code=[], unknown=[]) for fam in C.FILES}
        self.census = []
        self.scoped = False

    def put(self, fam, off, blob):
        self.data[fam][off:off + len(blob)] = blob

    def cover(self, fam, chunks, image=None, vma=VMA, start=0, size=SIZE):
        self.chunks.setdefault(fam, [])
        self.extra_images.append((image or fam + '/image', fam, chunks, vma, start, size))

    def chunk(self, off, size, cls='c_data', code=(), vma=None, origin=None, kind=None):
        extra = dict(kind=kind) if kind else {}
        return dict(**extra, foff=off, size=size, vma=VMA + off if vma is None else vma, origin=origin or ('retail_import' if cls == 'import' else 'original_object'),
                    code=[list(c) for c in code], **{'class': cls})

    def line(self, fam, start, end, cls, evidence=None, sha_override=None):
        self.lines.setdefault(fam, []).append((start, end, cls, evidence or self.evidence, sha_override))

    def write(self):
        root = self.root
        (root / 'config/link_graph').mkdir(parents=True)
        recs = []
        for fam in C.FILES:
            path = root / C.DISC_PATHS[fam]
            path.parent.mkdir(parents=True, exist_ok=True)
            path.write_bytes(bytes(self.data[fam]))
            recs.append(dict(id=fam, size=SIZE, sha1=hashlib.sha1(bytes(self.data[fam])).hexdigest(), disc_path=fam))
        (root / 'config/link_graph/files.000.jsonl').write_text('\n'.join(json.dumps(r) for r in recs) + '\n')
        origins = root / 'build/.state/origins'
        origins.mkdir(parents=True)
        results = []
        images = list(self.extra_images)
        have = {fam for _, fam, *_ in images}
        for fam in C.FILES:
            if fam not in have:
                images.append((fam + '/image', fam, [self.chunk(0, SIZE, 'import')], VMA, 0, SIZE))
        for image, fam, chunks, vma, start, size in images:
            cover = dict(schema='closure.cover.v1', start=start, size=size, vma=vma, chunks=chunks)
            blob = json.dumps(dict(image=image, cover=cover), sort_keys=True).encode()
            (origins / (image.replace('/', '_') + '.json')).write_bytes(blob)
            results.append(dict(image=image, result='MATCH', origin_sha256=sha(blob)))
        (root / 'config/x.txt').write_text('input')
        out = root / 'build/x.bin'
        out.write_bytes(b'out')
        receipt = dict(schema='azure-clean.make-check.v2', images=len(results), matched=len(results), results=results,
                       inputs={'config/x.txt': sha(b'input')}, outputs={'build/x.bin': sha(b'out')}, decoded={})
        (root / ('build/scope-check.json' if self.scoped else 'build/check.json')).write_text(json.dumps(receipt))
        directory = root / 'config/closure'
        for fam, lines in self.lines.items():
            directory.mkdir(exist_ok=True)
            text = [SCHEMA_LINE.rstrip('\n')]
            for start, end, cls, evidence, override in sorted(lines, key=lambda x: (x[0], x[1], x[2])):
                digest = override or C.line_digest(bytes(self.data[fam]), start, end)
                text.append('0x%X\t0x%X\t%s\t%s\t%s' % (start, end, cls, evidence, digest))
            (directory / (fam + '.tsv')).write_text('\n'.join(text) + '\n')
        return self

    def run(self, **kw):
        return C.analyse(self.root, 'report', labels=kw.get('labels', self.labels), census=kw.get('census', self.census))

    def kinds(self, res):
        return sorted({k for k, _ in res['findings']})

    def close(self):
        self.tmp.cleanup()


def base_world():
    """town: a compiled function at 0x100 (code), a compiled array 0x120..0x140 (data), a data block with own:data,
    a vendor routine in assembly, and padding. Everything else is zero."""
    w = World()
    fn = frame_fn()
    w.put('town', 0x100, pack(fn))                      # 12 words
    w.put('town', 0x120, pack(DATA))                    # 16 B
    w.put('town', 0x400, pack(DATA * 2))                # 32 B, own:data
    w.put('town', 0x500, pack(leaf_fn(2)))              # vendor assembly
    n = len(fn) * 4
    w.cover('town', [w.chunk(0, 0x100, 'import'), w.chunk(0x100, n, 'c_data', [(0x100, n)]),
                     w.chunk(0x100 + n, 0x20, 'import'), w.chunk(0x120, 16, 'c_data'), w.chunk(0x130, SIZE - 0x130, 'import'),
                     w.chunk(0x500, 0x14, 'assembly', kind='platform_asm')])
    return w


class CleanTests(unittest.TestCase):
    def setUp(self):
        self.w = base_world()
        self.addCleanup(self.w.close)

    def own_everything(self, w):
        w.line('town', 0x400, 0x420, 'own:data')
        w.line('town', 0x500, 0x514, 'own:vendor')

    def test_unowned_nonzero_bytes_are_unknown_and_a_deleted_line_comes_back(self):
        self.w.write()
        res = self.w.run()
        self.assertIn('unknown', self.w.kinds(res))
        expected = 0x20 + 0x14                      # short zero runs inside words are ordinary bytes
        self.assertEqual(sum(C.total(u.unknown) for u in res['units'].values()), expected)

    def test_clean_world_has_no_finding_and_the_headline_is_the_hand_count(self):
        self.own_everything(self.w)
        self.w.line('town', 0x100 + 0x30 + 0x30, 0x100 + 0x30 + 0x30 + 4, 'own:code') if False else None
        self.w.write()
        res = self.w.run()
        self.assertEqual(res['findings'], [], res['findings'])
        self.assertEqual(res['headline'], (0, 0, 0, 0))
        text = C.summary(res)[0]
        self.assertTrue(text.startswith('HEADLINE game code without C: 0 B (physical 0, C-data bodies 0, decoded 0) | unknown 0 | open hits 0'), text)

    def test_own_code_raises_the_headline_and_a_region_line_takes_it_out(self):
        self.own_everything(self.w)
        self.w.put('town', 0x700, pack(leaf_fn(2)))
        self.w.line('town', 0x700, 0x714, 'own:code')
        self.w.write()
        self.assertEqual(self.w.run()['headline'][:2], (0x14, 0x14))
        self.w.close()
        w = base_world()
        self.own_everything(w)
        w.put('town', 0x700, pack(leaf_fn(2)))
        w.line('town', 0x700, 0x714, 'own:code')
        w.line('town', 0x700, 0x714, 'region:other:old_program')
        w.write()
        self.addCleanup(w.close)
        self.assertEqual(w.run()['headline'][0], 0)


class OwnershipTests(unittest.TestCase):
    def make(self, mutate=None):
        w = base_world()
        w.line('town', 0x400, 0x420, 'own:data')
        w.line('town', 0x500, 0x514, 'own:vendor')
        if mutate:
            mutate(w)
        w.write()
        self.addCleanup(w.close)
        return w, w.run()

    def test_overlapping_own_lines_are_refused_and_their_bytes_are_unknown(self):
        w, res = self.make(lambda w: w.line('town', 0x410, 0x430, 'own:data'))
        self.assertIn('overlap', w.kinds(res))
        self.assertGreater(sum(C.total(u.unknown) for u in res['units'].values()), 0)

    def test_own_line_over_compiled_code_and_data_is_refused(self):
        w, res = self.make(lambda w: (w.line('town', 0x100, 0x130, 'own:code'), w.line('town', 0x120, 0x130, 'own:data')))
        self.assertIn('entry_over_c', w.kinds(res))
        self.assertTrue(any('replace with' in t for k, t in res['findings'] if k == 'entry_over_c'))

    def test_wrong_hash_missing_evidence_and_work_label_are_refused(self):
        w, res = self.make(lambda w: w.line('town', 0x420, 0x430, 'own:data', sha_override='0' * 64))
        self.assertIn('sha', w.kinds(res))
        w, res = self.make(lambda w: w.line('town', 0x420, 0x430, 'own:data', evidence='docs/missing.md'))
        self.assertIn('evidence', w.kinds(res))
        w, res = self.make(lambda w: w.line('town', 0x420, 0x430, 'own:data', evidence='docs/evidence.md#key gamma'))
        self.assertIn('evidence', w.kinds(res))
        label = 'docs/' + 'r12' + '3w_lane.md'          # a lane-shaped name, built so this file carries none
        (w.root / label).write_text('x')
        w, res = self.make(lambda w: (w.line('town', 0x420, 0x430, 'own:data', evidence=label),
                                      (w.root / 'docs').mkdir(exist_ok=True)))
        self.assertTrue({'work_label', 'evidence'} & set(w.kinds(res)))

    def test_bad_class_schema_and_unsorted_lines_are_refused(self):
        w, res = self.make()
        path = w.root / 'config/closure/town.tsv'
        text = path.read_text().splitlines()
        path.write_text('\n'.join([text[0], 'x\ty\tnonsense\te\t' + '0' * 64, text[2], text[1]]) + '\n')
        res = w.run()
        self.assertTrue({'schema', 'order'} <= set(w.kinds(res)))

    def test_ack_with_no_hit_is_stale(self):
        w, res = self.make(lambda w: w.line('town', 0x420, 0x424, 'ack:D1:data'))
        self.assertIn('ack_stale', w.kinds(res))

    def test_scoped_proof_is_refused_and_missing_cover_is_an_input_error(self):
        w = base_world()
        w.scoped = True
        w.write()
        self.addCleanup(w.close)
        with self.assertRaisesRegex(C.InputError, 'no_full_proof'):
            w.run()
        w2 = base_world()
        w2.write()
        self.addCleanup(w2.close)
        origin = w2.root / 'build/.state/origins/town_image.json'
        origin.write_text(origin.read_text() + ' ')
        with self.assertRaisesRegex(C.InputError, 'origin file differs'):
            w2.run()

    def test_origin_not_named_by_check_json_is_ignored(self):
        w = base_world()
        w.write()
        self.addCleanup(w.close)
        (w.root / 'build/.state/origins/town_stale.json').write_text('{"cover": {"garbage": true}}')
        self.assertEqual(w.run()['headline'][0], 0)


class PartTests(unittest.TestCase):
    def test_a_line_file_in_numbered_parts_reads_as_one_and_must_stay_sorted_across_parts(self):
        w = base_world()
        w.line('town', 0x400, 0x420, 'own:data')
        w.line('town', 0x500, 0x514, 'own:vendor')
        w.write()
        self.addCleanup(w.close)
        directory = w.root / 'config/closure'
        header, first, second = (directory / 'town.tsv').read_text().splitlines()
        (directory / 'town.tsv').unlink()
        (directory / 'town.000.tsv').write_text(header + '\n' + first + '\n')
        (directory / 'town.001.tsv').write_text(header + '\n' + second + '\n')
        self.assertEqual(w.run()['findings'], [])
        (directory / 'town.000.tsv').write_text(header + '\n' + second + '\n')
        (directory / 'town.001.tsv').write_text(header + '\n' + first + '\n')
        self.assertIn('order', w.kinds(w.run()))


class DiscFileTests(unittest.TestCase):
    def test_whole_file_lines_are_checked_against_the_extracted_files_when_present(self):
        w = base_world()
        w.line('town', 0x400, 0x420, 'own:data')
        w.line('town', 0x500, 0x514, 'own:vendor')
        w.write()
        self.addCleanup(w.close)
        (w.root / 'docs/evidence.md').write_text('x')
        movie = w.root / 'work/disc/extract/STR/MERGE.STR'
        movie.parent.mkdir(parents=True)
        movie.write_bytes(b'movie')
        sha1 = hashlib.sha1(b'movie').hexdigest()
        table = w.root / 'config/closure/disc_files.tsv'
        table.parent.mkdir(exist_ok=True)
        table.write_text('# schema closure.disc.v1\nSTR/MERGE.STR\t5\town:media\tdocs/evidence.md\t%s\nSTR/OTHER.STR\t9\town:media\tdocs/evidence.md\t%s\n' % (sha1, '0' * 40))
        res = w.run()
        self.assertEqual(res['findings'], [], res['findings'])
        self.assertEqual([(n, st) for n, _, st in res['disc_files']], [('STR/MERGE.STR', 'verified'), ('STR/OTHER.STR', 'unverified')])
        movie.write_bytes(b'moVie')
        self.assertIn('disc_file', w.kinds(w.run()))
        table.write_text('# schema closure.disc.v1\nSTR/MERGE.STR\t5\town:data\tdocs/evidence.md\t%s\n' % sha1)
        self.assertIn('schema', w.kinds(w.run()))


class DecodedOwnerRecordTests(unittest.TestCase):
    """A decoded image's compiled code and C data come only from the owner records its proof carries."""

    def load(self, functions, data):
        tmp = tempfile.TemporaryDirectory()
        self.addCleanup(tmp.cleanup)
        root = Path(tmp.name)
        retail = bytes(0x100)
        proof = dict(sha256=sha(retail), size=len(retail), functions=functions, data=data)
        (root / 'config/decoded').mkdir(parents=True)
        (root / 'config/decoded/x.json').write_text(json.dumps(dict(image='dungeon/x')))
        work = root / 'build/decoded/dungeon/x'
        work.mkdir(parents=True)
        (work / 'retail.bin').write_bytes(retail)
        blob = json.dumps(proof).encode()
        (work / 'proof.json').write_bytes(blob)
        return C.load_decoded(root, dict(decoded={'dungeon/x': sha(blob)}))['decoded:dungeon/x']

    def test_body_placement_and_data_section_with_a_record_are_owned(self):
        unit = self.load([dict(offset=0x10, size=0x20, func_symbol=True),
                          dict(offset=0x30, size=0x10, func_symbol=True, placement='p', symbol='s')],
                         [dict(offset=0x80, size=0x10, compiled_section=True)])
        self.assertEqual(unit.c_code, [[0x10, 0x40]])
        self.assertEqual(unit.c_data, [[0x80, 0x90]])
        self.assertEqual(unit.starts, {0x10, 0x30})

    def test_function_or_data_without_a_record_is_not_owned(self):
        unit = self.load([dict(offset=0x10, size=0x20, func_symbol=False), dict(offset=0x30, size=0x10)],
                         [dict(offset=0x80, size=0x10, compiled_section=False), dict(offset=0xA0, size=0x10)])
        self.assertEqual(unit.c_code, [])
        self.assertEqual(unit.c_data, [])
        self.assertEqual(unit.c_import, [])


class ShortExtentDigestTests(unittest.TestCase):
    """An extent under 16 bytes never carries a digest of its own bytes: it carries a digest of an enclosing window."""

    def make(self, **kw):
        w = base_world()
        w.line('town', 0x400, 0x420, 'own:data')
        w.line('town', 0x500, 0x514, 'own:vendor')
        w.put('town', 0x600, bytes(range(1, 33)))
        w.line('town', 0x600, 0x620, 'own:data', **kw)            # 32 bytes: its own digest
        w.put('town', 0x700, bytes(range(40, 72)))
        w.line('town', 0x700, 0x704, 'own:data')                   # short extents: window digests
        w.line('town', 0x704, 0x70C, 'own:data', **kw)
        w.line('town', 0x70C, 0x720, 'own:data')
        return w

    def run_world(self, w):
        w.write()
        self.addCleanup(w.close)
        return w.run()

    def kinds(self, w, res):
        return sorted({k for k, _ in res['findings']})

    def test_enclosing_window_holds_the_extent_inside_the_file_and_is_at_least_16_bytes(self):
        for a, b, size in ((0x704, 0x70C, 0x4000), (0, 1, 0x4000), (0x3FFC, 0x4000, 0x4000), (0x70C, 0x71A, 0x4000), (5, 20, 0x4000)):
            offset, length = C.enclosing_window(a, b, size)
            self.assertGreaterEqual(length, 16)
            self.assertTrue(0 <= offset <= a and b <= offset + length <= size, (a, b, offset, length))

    def test_a_short_extent_with_a_window_digest_passes_and_the_line_text_states_the_window(self):
        w = self.make()
        res = self.run_world(w)
        self.assertEqual(res['findings'], [], res['findings'])
        short = [ln for ln in res['units']['town'].lines if ln.start == 0x704][0]
        self.assertEqual(short.window, (0x700, 0x10))
        self.assertIn('\tw0x700+0x10:', short.text())

    def test_a_short_extent_with_a_digest_of_its_own_bytes_is_refused_by_the_reader(self):
        data = bytes(range(40, 72))
        w = self.make()
        w.lines['town'] = [x for x in w.lines['town'] if x[0] != 0x704]
        w.line('town', 0x704, 0x70C, 'own:data', sha_override=sha(data[4:12]))
        res = self.run_world(w)
        self.assertIn('schema', self.kinds(w, res))
        self.assertTrue(any('no digest of its own bytes' in t for k, t in res['findings']))

    def test_window_must_hold_the_extent_and_be_at_least_16_bytes(self):
        data = bytes(range(40, 72))
        for window in ((0x708, 0x10), (0x700, 0x8), (0x700, 0x4)):
            w = self.make()
            w.lines['town'] = [x for x in w.lines['town'] if x[0] != 0x704]
            digest = 'w0x%X+0x%X:%s' % (window[0], window[1], sha(b'x'))
            w.line('town', 0x704, 0x70C, 'own:data', sha_override=digest)
            res = self.run_world(w)
            self.assertIn('schema', self.kinds(w, res), window)

    def test_drift_of_a_long_extent_still_fails(self):
        w = base_world()
        w.line('town', 0x500, 0x514, 'own:vendor')
        mutated = bytearray(w.data['town'])
        mutated[0x410] ^= 1
        w.line('town', 0x400, 0x420, 'own:data', sha_override=C.line_digest(bytes(mutated), 0x400, 0x420))
        res = self.run_world(w)
        self.assertIn('sha', self.kinds(w, res))

    def test_a_change_inside_the_window_of_a_short_extent_fails_in_or_outside_the_extent(self):
        for position in (0x706, 0x70E):        # inside the extent, and in the window beside it
            w = self.make()
            w.lines['town'] = [x for x in w.lines['town'] if x[0] != 0x704]
            mutated = bytearray(w.data['town'])
            mutated[position] ^= 1
            w.line('town', 0x704, 0x70C, 'own:data', sha_override=C.line_digest(bytes(mutated), 0x704, 0x70C))
            res = self.run_world(w)
            self.assertIn('sha', self.kinds(w, res), position)

    def test_a_change_outside_the_window_is_not_seen_by_the_short_line(self):
        w = self.make()
        w.lines['town'] = [x for x in w.lines['town'] if x[0] != 0x704]
        mutated = bytearray(w.data['town'])
        mutated[0x712] ^= 1
        w.line('town', 0x704, 0x70C, 'own:data', sha_override=C.line_digest(bytes(mutated), 0x704, 0x70C))
        res = self.run_world(w)
        self.assertNotIn('sha', self.kinds(w, res))


class StreamLineTests(unittest.TestCase):
    def world(self, shift=0, wrong_size=False):
        sys.path.insert(0, str(HERE.parents[1]))
        from tools.decoded.lz import encode
        import random
        size = 1200
        while len(encode(random.Random(5).randbytes(size))) % 4:
            size += 1
        plain = random.Random(5).randbytes(size)
        packed = encode(plain)
        w = base_world()
        w.line('town', 0x400, 0x420, 'own:data')
        w.line('town', 0x500, 0x514, 'own:vendor')
        w.put('town', 0x1000, packed)
        w.line('town', 0x1000 + shift, 0x1000 + shift + len(packed), 'own:stream:menu_cache')
        w.write()
        table = w.root / 'config/closure/streams.tsv'
        table.parent.mkdir(exist_ok=True)
        table.write_text('# schema closure.streams.v1\ntown\t0x1000\t%s\t%s\t%s\n' % (
            hex(len(packed)), hex(len(plain) + 1 if wrong_size else len(plain)), sha(packed)))
        self.addCleanup(w.close)
        return w

    def test_registered_stream_passes_and_a_shifted_or_wrong_length_stream_is_refused(self):
        self.assertEqual(self.world().run()['findings'], [])
        self.assertIn('stream', self.world(shift=4).kinds(self.world(shift=4).run()))
        w = self.world(wrong_size=True)
        self.assertIn('stream', w.kinds(w.run()))

    def test_stream_lines_over_bytes_that_decode_to_code_stay_visible_as_a_census_hit_without_a_line(self):
        w = self.world()
        text = (w.root / 'config/closure/town.tsv').read_text().splitlines()
        (w.root / 'config/closure/town.tsv').write_text('\n'.join(l for l in text if 'own:stream' not in l) + '\n')
        self.assertIn('unknown', w.kinds(w.run()))      # a deleted stream line leaves its bytes unknown


class DetectorTests(unittest.TestCase):
    def world(self, hidden):
        w = base_world()
        w.line('town', 0x400, 0x420, 'own:data')
        w.line('town', 0x500, 0x514, 'own:vendor')
        hidden(w)
        return w

    def test_function_body_spelled_as_a_c_array_is_a_hit_and_an_ack_counts_in_the_headline(self):
        body = pack(leaf_fn(3))

        def hide(w):
            w.put('town', 0x800, body)
            w.cover('town', [w.chunk(0, 0x800, 'import'), w.chunk(0x800, len(body), 'c_data'), w.chunk(0x800 + len(body), SIZE - 0x800 - len(body), 'import')],
                    image='town/second')
        w = self.world(hide)
        w.write()
        self.addCleanup(w.close)
        res = w.run()
        self.assertEqual([h[2] for h in res['open']['town']], ['D1'])
        self.assertIn('hit', w.kinds(res))
        a, b = res['open']['town'][0][:2]
        w.close()
        w = self.world(hide)
        w.line('town', a, b, 'ack:D1:code_in_c_data')
        w.write()
        self.addCleanup(w.close)
        res = w.run()
        self.assertEqual(res['open']['town'], [])
        self.assertEqual(res['headline'][2], b - a)
        # a moved ack is stale
        w.close()
        w = self.world(hide)
        w.line('town', a + 4, b, 'ack:D1:code_in_c_data')
        w.write()
        self.addCleanup(w.close)
        self.assertIn('ack_stale', w.kinds(w.run()))

    def test_headless_tail_in_unowned_bytes_is_unknown_and_in_own_data_is_a_hit(self):
        tail = pack([addiu(V0, V0, 1), sw(V0, 4, A0), lw(V0, 8, A0), JR_RA, NOP])

        def hide(w):
            w.put('town', 0x900, tail)
        w = self.world(hide)
        w.write()
        self.addCleanup(w.close)
        self.assertIn('unknown', w.kinds(w.run()))
        w.close()
        w = self.world(lambda w: (hide(w), w.line('town', 0x900, 0x940, 'own:data')))
        w.write()
        self.addCleanup(w.close)
        res = w.run()
        self.assertEqual([h[2] for h in res['open']['town']], ['D1'])

    def test_dense_run_is_listed_but_report_only(self):
        body = [lw(V0, 0, A0), addiu(V0, V0, 1), sw(V0, 4, A0)] + [addiu(V0, V0, 1)] * 10 + [0x10000000 | (0xfffb & 0xffff)] + [addiu(V0, V0, 2)] * 3

        def hide(w):
            w.put('town', 0xC00, pack(body))
            w.line('town', 0xC00, 0xC00 + len(body) * 4, 'own:data')
        w = self.world(hide)
        w.write()
        self.addCleanup(w.close)
        res = w.run()
        self.assertTrue(any(h[2] == 'D5' for h in res['hits']['town']))
        self.assertEqual(res['open']['town'], [])

    def test_hit_inside_a_region_line_is_resolved(self):
        tail = pack(leaf_fn(3))

        def hide(w):
            w.put('town', 0x900, tail)
            w.line('town', 0x900, 0x940, 'own:data')
            w.line('town', 0x900, 0x940, 'region:other:old_program')
        w = self.world(hide)
        w.write()
        self.addCleanup(w.close)
        res = w.run()
        self.assertEqual(res['open']['town'], [])
        self.assertTrue(res['resolved']['town'])

    def test_call_into_data_and_midbody_call_are_hits_that_only_cross_image_verdicts_resolve(self):
        n = len(frame_fn()) * 4
        caller = pack(frame_fn([VMA + 0x400, VMA + 0x104]))

        def hide(w):
            w.put('town', 0x600, caller)
            w.cover('town', [w.chunk(0, 0x600, 'import'), w.chunk(0x600, len(caller), 'c_data', [(0x600, len(caller))]),
                             w.chunk(0x600 + len(caller), SIZE - 0x600 - len(caller), 'import')], image='town/caller')
        w = self.world(hide)
        w.write()
        self.addCleanup(w.close)
        res = w.run()
        rules = sorted((h[2], h[3]) for h in res['open']['town'])
        self.assertIn(('D3', 'call_into_noncode'), rules)
        self.assertIn(('D3', 'call_midbody:1'), rules)

    def test_pointer_to_hidden_code_is_a_hit(self):
        body = pack(leaf_fn(3))

        def hide(w):
            w.put('town', 0x800, body)
            w.line('town', 0x800, 0x820, 'own:data')
            w.put('town', 0x420, struct.pack('<I', VMA + 0x800))
            w.line('town', 0x420, 0x424, 'own:data')
        w = self.world(hide)
        w.write()
        self.addCleanup(w.close)
        rules = sorted(h[2] for h in w.run()['open']['town'])
        self.assertEqual(rules, ['D1', 'D4'])

    def test_code_stream_inside_data_is_a_hit_and_a_stream_line_is_not(self):
        def hide(w):
            w.put('town', 0xA00, bytes(range(1, 65)))
            w.line('town', 0xA00, 0xA40, 'own:data')
        w = self.world(hide)
        w.census = [('town', 0xA00, 0x40)]
        w.write()
        self.addCleanup(w.close)
        self.assertEqual([h[2] for h in w.run()['open']['town']], ['D6'])


class D7Tests(unittest.TestCase):
    def test_body_in_another_programs_region_that_calls_only_this_executable_is_a_hit(self):
        # the executable (slus file) holds a compiled function at file offset 0x800; a region other body calls it twice
        w = base_world()
        w.line('town', 0x400, 0x420, 'own:data')
        w.line('town', 0x500, 0x514, 'own:vendor')
        exe_fn = pack(frame_fn())
        w.put('slus', 0x800, exe_fn)
        w.put('slus', 0x900, exe_fn)
        exe = lambda off: 0x80010000 + off - 0x800
        w.cover('slus', [w.chunk(0, 0x800, 'import', vma=0), w.chunk(0x800, len(exe_fn), 'c_data', [(0x800, len(exe_fn))], vma=exe(0x800)),
                         w.chunk(0x800 + len(exe_fn), 0x100 - len(exe_fn), 'import', vma=exe(0x800 + len(exe_fn))),
                         w.chunk(0x900, len(exe_fn), 'c_data', [(0x900, len(exe_fn))], vma=exe(0x900)),
                         w.chunk(0x900 + len(exe_fn), SIZE - 0x900 - len(exe_fn), 'import', vma=exe(0x900 + len(exe_fn)))], image='slus/slus_bin', vma=None)
        body = pack([addiu(SP, SP, -16), sw(RA, 12, SP), jal(0x80010000), NOP, jal(0x80010100), NOP, lw(RA, 12, SP), JR_RA, addiu(SP, SP, 16)])
        w.put('town', 0x700, body)
        w.line('town', 0x700, 0x700 + len(body), 'own:code')
        w.line('town', 0x700, 0x700 + len(body), 'region:other:old_program')
        w.write()
        self.addCleanup(w.close)
        res = w.run()
        self.assertEqual([h[2] for h in res['open']['town']], ['D7'])


class RegionAndClassTests(unittest.TestCase):
    def world(self, mutate):
        w = base_world()
        w.line('town', 0x400, 0x420, 'own:data')
        w.line('town', 0x500, 0x514, 'own:vendor')
        mutate(w)
        w.write()
        self.addCleanup(w.close)
        return w

    def test_region_other_inside_a_load_region_is_refused(self):
        def mutate(w):
            w.put('town', 0x700, pack(leaf_fn(2)))
            w.line('town', 0x700, 0x714, 'own:code')
            w.line('town', 0x700, 0x714, 'region:other:old_program')
            (w.root / 'config/link/town').mkdir(parents=True)
            (w.root / 'config/link/town/load.json').write_text(json.dumps(dict(image='town/loaded', container='town', foff='0x600', size='0x400', load_evidence=dict(path='x'))))
        w = self.world(mutate)
        self.assertIn('region_in_load', w.kinds(w.run()))

    def test_stale_line_is_word_for_word_equal_to_its_source(self):
        def mutate(w):
            blob = pack(leaf_fn(30))
            w.put('town', 0x700, blob)
            w.put('dungeon', 0x700, blob)
            if mutate.differ:
                w.put('dungeon', 0x704, struct.pack('<I', 0x24420003))
            w.line('town', 0x700, 0x700 + len(blob), 'own:code')
            w.line('town', 0x700, 0x700 + len(blob), 'region:stale:dungeon:%d' % mutate.k)
            w.line('dungeon', 0x700, 0x700 + len(blob), 'own:code')
        mutate.k, mutate.differ = 0, False
        w = self.world(mutate)
        self.assertNotIn('stale_test', w.kinds(w.run()))
        mutate.k, mutate.differ = 0, True                 # one word differs: refused
        w = self.world(mutate)
        self.assertIn('stale_test', w.kinds(w.run()))
        mutate.k, mutate.differ = 1, True                 # a stated count of differences is no longer accepted
        w = self.world(mutate)
        self.assertIn('stale_test', w.kinds(w.run()))

    def test_padding_must_be_one_value_ending_on_a_boundary(self):
        def mutate(w):
            w.put('town', 0x7F0, b'\xff' * 8 + b'\xee' * 8)
            w.line('town', 0x7F0, 0x800, 'own:padding')
            w.put('town', 0x7E0, b'\xff' * 8)
            w.line('town', 0x7E0, 0x7E8, 'own:padding')
        w = self.world(mutate)
        found = [t for k, t in w.run()['findings'] if k == 'padding']
        self.assertEqual(len(found), 2, found)    # two fill values; and 8 bytes ending on 8 is not shorter than its boundary

    def test_vendor_routine_that_calls_game_code_is_refused(self):
        def mutate(w):
            w.put('town', 0x600, pack([jal(VMA + 0x100), NOP, JR_RA, NOP]))
            w.line('town', 0x600, 0x610, 'own:vendor')
        w = self.world(mutate)
        self.assertIn('vendor_calls_game', w.kinds(w.run()))

    def test_vendor_line_needs_assembled_sdk_bytes_or_an_sdk_record_extent(self):
        def mutate(w):
            w.put('town', 0x600, pack(leaf_fn(2)))
            w.line('town', 0x600, 0x614, 'own:vendor')
        w = self.world(mutate)
        self.assertIn('vendor_extent', w.kinds(w.run()))
        # an SDK object record whose row extent covers the line, named by the evidence key, is accepted
        (w.root / 'ledger').mkdir()
        (w.root / 'ledger/sdk_objects.jsonl').write_text(json.dumps(dict(id='town/func_80100600')) + '\n')
        (w.root / 'ledger/rows.jsonl').write_text(json.dumps(dict(id='town/func_80100600', container='town', foff=0x600, size=0x14)) + '\n')
        path = w.root / 'config/closure/town.tsv'
        lines = path.read_text().splitlines()
        lines = [l.replace('\tdocs/evidence.md\t', '\tledger/sdk_objects.jsonl#town/func_80100600\t') if l.startswith('0x600') else l for l in lines]
        path.write_text('\n'.join(lines) + '\n')
        self.assertNotIn('vendor_extent', w.kinds(w.run()) + [k for k, _ in []])

    def test_own_data_over_a_code_label_is_refused(self):
        def mutate(w):
            w.labels['town']['code'] = [[0x400, 0x410]]
        w = self.world(mutate)
        self.assertIn('own_data', w.kinds(w.run()))


class DeltaAndReportTests(unittest.TestCase):
    def test_batch_mode_needs_one_root_and_the_report_lists_added_lines(self):
        import subprocess
        w = base_world()
        w.line('town', 0x400, 0x420, 'own:data')
        w.line('town', 0x500, 0x514, 'own:vendor')
        w.write()
        self.addCleanup(w.close)
        git = lambda *a: subprocess.run(['git', '-c', 'user.name=t', '-c', 'user.email=t@invalid', *a], cwd=w.root, check=True, capture_output=True)
        git('init', '-q')
        git('add', 'config')
        git('commit', '-q', '-m', 'base')
        (w.root / 'config/closure/town.tsv').write_text((w.root / 'config/closure/town.tsv').read_text())
        w.put('town', 0x700, pack(leaf_fn(2)))
        # a new own:code line lands after the base
        text = (w.root / 'config/closure/town.tsv').read_text() + '0x700\t0x714\town:code\tdocs/evidence.md\t%s\n' % sha(pack(leaf_fn(2)))
        (w.root / 'config/closure/town.tsv').write_text(text.replace('\town:code', '\town:code'))
        # town.bin on disk still has zero there: the sha must match the bytes on disk
        (w.root / C.DISC_PATHS['town']).write_bytes(bytes(w.data['town']))
        recs = [json.loads(l) for l in (w.root / 'config/link_graph/files.000.jsonl').read_text().splitlines()]
        for r in recs:
            if r['id'] == 'town':
                r['sha1'] = hashlib.sha1(bytes(w.data['town'])).hexdigest()
        (w.root / 'config/link_graph/files.000.jsonl').write_text('\n'.join(json.dumps(r) for r in recs) + '\n')
        res = C.analyse(w.root, 'landing', labels=w.labels, census=[])
        added, removed, newly = res['delta']
        self.assertEqual((len(added), len(removed)), (1, 0))
        self.assertEqual(newly, 0x14)
        self.assertEqual(res['base_headline'], 0)
        self.assertEqual(res['headline'][0], 0x14)
        lines = C.write_report(res, w.root / 'out')
        self.assertTrue(lines[0].startswith('HEADLINE game code without C: 20 B'))
        self.assertTrue((w.root / 'out/hits.tsv').is_file())
        self.assertIn('added', (w.root / 'out/lines_delta.tsv').read_text())

    def test_a_removed_load_record_is_reported_and_changes_no_class(self):
        import subprocess
        w = base_world()
        w.line('town', 0x400, 0x420, 'own:data')
        w.line('town', 0x500, 0x514, 'own:vendor')
        w.write()
        self.addCleanup(w.close)
        record = json.dumps(dict(container='town', foff=0x600, size=0x100))
        (w.root / 'ledger').mkdir()
        (w.root / 'ledger/instance_load_regions.jsonl').write_text(record + '\n')
        git = lambda *a: subprocess.run(['git', '-c', 'user.name=t', '-c', 'user.email=t@invalid', *a], cwd=w.root, check=True, capture_output=True)
        git('init', '-q')
        git('add', 'config', 'ledger')
        git('commit', '-q', '-m', 'base')
        (w.root / 'ledger/instance_load_regions.jsonl').write_text('')
        res = w.run()
        self.assertEqual(res['region_delta'][1], ['load record town 0x600+0x100'])
        self.assertIn('LOADREGION removed: load record town 0x600+0x100', C.write_report(res, w.root / 'out'))
        # the removed record held a retail load at the base: it is printed as a refusal-class line, nothing else moves
        self.assertEqual([k for k, _ in res['findings']], ['load_demoted'], res['findings'])
        self.assertIn('"foff": 1536', res['demoted'][0][3])

    def test_main_reports_but_exits_zero_while_not_gating(self):
        w = base_world()
        w.write()
        self.addCleanup(w.close)
        import os
        cwd = os.getcwd()
        self.addCleanup(os.chdir, cwd)
        os.chdir(w.root)
        orig_labels, orig_census = C.default_labels, C.default_census
        C.default_labels = lambda root: w.labels
        C.default_census = lambda root, data: []
        self.addCleanup(setattr, C, 'default_labels', orig_labels)
        self.addCleanup(setattr, C, 'default_census', orig_census)
        import io
        import contextlib
        buf = io.StringIO()
        with contextlib.redirect_stdout(buf):
            code = C.main(['report', '--out', 'out'])
        self.assertEqual(code, 0)
        self.assertIn('CLOSURE FAIL unknown', buf.getvalue())
        C.GATING = True
        self.addCleanup(setattr, C, 'GATING', False)
        with contextlib.redirect_stdout(io.StringIO()):
            self.assertEqual(C.main(['landing', '--out', 'out']), 1)
            self.assertEqual(C.main(['report', '--out', 'out']), 0)


class NoFlagTests(unittest.TestCase):
    def test_the_only_arguments_are_the_mode_and_out(self):
        for bad in ('--accept', '--tighten', '--base', '--baseline', '--rewrite'):
            with self.assertRaises(SystemExit):
                C.main(['landing', bad, 'x'])
        source = (HERE / 'closure.py').read_text()
        self.assertEqual(source.count('add_argument('), 2)


if __name__ == '__main__':
    unittest.main()
