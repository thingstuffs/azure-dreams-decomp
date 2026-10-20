"""Lossless projection, fail-closed graph edges and the GNU overlay contract."""
import copy
import hashlib
import json
from pathlib import Path
import shutil
import subprocess
import sys
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / 'tools'))
from link.graph import (Graph, SCHEMA, TABLES, canonical, compare, digest, emit_global,
                        key_order, qualification, shard, write_json)
from link.combined import differences, slus_origins


class LinkGraphTests(unittest.TestCase):
    def setUp(self):
        (ROOT/'work').mkdir(exist_ok=True)
        self.tmp = tempfile.TemporaryDirectory(dir=ROOT/'work', prefix='test-link-graph-')
        self.addCleanup(self.tmp.cleanup)
        self.root = Path(self.tmp.name)
        self.tables = {k: [] for k in TABLES}
        self.tables['files'] = [dict(id='main', disc_path='MAIN/MAIN.BIN', size=1000)]
        self.tables['tus'] = [dict(id='main/home', source='src/main/renamed.c', source_sha256='0'*64)]

    def add_doc(self, doc):
        image = doc['image']
        view = dict(id=image, file=doc['container'], phase='view:'+image,
                    attributes={k:v for k,v in doc.items() if k not in ('image','container','entries','symbols')})
        def owners(scope, values):
            ids = []
            for name, value in values.items():
                oid = scope+'::'+name
                ids.append(oid)
                self.tables['owners'].append(dict(id=oid, scope=scope, symbol=name, address=value, kind='address_witness'))
            return ids
        if 'symbols' in doc:
            view['symbol_owners'] = owners(image, doc['symbols'])
        self.tables['views'].append(view)
        for n, e in enumerate(doc['entries']):
            entry = dict(id=image+'@'+str(n), view=image, order=n, kind=e.get('kind','tu'),
                         attributes={k:v for k,v in e.items() if k not in ('tu','home','symbols')})
            if 'tu' in e:
                entry['tu'] = e['home']
            if 'symbols' in e:
                entry['symbol_owners'] = owners(entry['id'], e['symbols'])
            self.tables['entries'].append(entry)
        return view

    def graph(self):
        directory = self.root/'graph'
        directory.mkdir(exist_ok=True)
        manifest = dict(schema=SCHEMA, base='fixture', tables={})
        for name in TABLES:
            manifest['tables'][name] = shard(directory, name, self.tables[name])
        write_json(directory/'graph.json', manifest)
        return Graph(directory)

    def fixture(self):
        evidence = 'independent fixture evidence'
        entries = [dict(row='main/row', home='main/home', tu='src/main/renamed.c',
                        foff='0x0', vma='0x80010000', size=4, bindings={}, evidence='home proof')]
        entries += [dict(kind='unresolved', foff=4, size=4, evidence=evidence),
                    dict(kind='padding', foff='0x8', size=4, evidence=evidence,
                         sha256='0'*64, extractor='container-slice-v1', symbols={'D_80010008':'0x80010008'}),
                    dict(kind='code_region', foff=12, size=4, evidence=evidence, census_label='library_code'),
                    dict(kind='data', foff=16, size=4, evidence=evidence, type='typing pending'),
                    dict(kind='asset', foff=20, size=4, evidence=evidence, format='opaque', sha256='0'*64,
                         extractor='container-slice-v1', census_label='noncode_typing_pending'),
                    dict(kind='leftover', foff=24, size=4, evidence=evidence, reason='independently proved unused')]
        doc = dict(schema='azure-clean.linklist.v1', image='main/fixture', container='main',
                   foff=0, size='0x1c', vma='0x80010000', entries=entries, evidence=evidence,
                   layout='fixture', symbols={}, load_evidence=dict(path='ledger/instance_load_regions.jsonl', record_sha256='0'*64),
                   provenance=dict(labels_sha256='1'*64, coverage_sha256='2'*64, source='fixture'),
                   census=dict(proven_code=4, unknown=4, padding_leftover=8, library_code=4, noncode_typing_pending=8))
        self.add_doc(doc)
        parent = dict(schema='azure-clean.linklist.v1', image='main/file', container='main',
                      foff=0, size=28, vma=None, entries=[dict(kind='image', ref='main/fixture', foff=0, size=28, evidence=evidence)],
                      census=copy.deepcopy(doc['census']))
        self.add_doc(parent)
        return {doc['image']:doc, parent['image']:parent}

    def test_every_kind_optional_presence_and_numeric_spelling(self):
        docs = self.fixture()
        graph = self.graph()
        self.assertEqual(graph.documents(validate=True), docs)
        graph.generate(self.root/'output')
        for image, doc in docs.items():
            self.assertEqual(json.loads((self.root/'output'/f'{image}.json').read_text()), doc)
        self.assertNotIn('symbols', graph.documents()['main/file'])
        self.assertEqual(graph.documents()['main/fixture']['symbols'], {})

    def test_census_hashed_serialization_survives_sorted_shards(self):
        docs = self.fixture()
        doc = docs['main/fixture']
        text = json.dumps(doc, indent=2)+'\n'
        self.tables['views'][0]['serialization'] = dict(indent=2, order=key_order(doc), sha256=digest(text.encode()))
        graph = self.graph()
        graph.generate(self.root/'output')
        self.assertEqual((self.root/'output/main/fixture.json').read_text(), text)

    def test_missing_tu_and_cross_scope_owner_are_rejected(self):
        self.fixture()
        self.tables['entries'][0]['tu'] = 'main/missing'
        with self.assertRaisesRegex(ValueError, 'unknown TU'):
            self.graph()
        self.tables['entries'][0]['tu'] = 'main/home'
        self.tables['owners'][0]['scope'] = 'main/file'
        with self.assertRaisesRegex(ValueError, 'cross-scope'):
            self.graph()

    def test_duplicate_order_and_v1_gaps_are_rejected(self):
        self.fixture()
        self.tables['entries'][1]['order'] = 0
        with self.assertRaisesRegex(ValueError, 'identity/order'):
            self.graph()
        self.tables['entries'][1]['order'] = 1
        self.tables['entries'][1]['attributes']['foff'] = 5
        with self.assertRaisesRegex(ValueError, 'gap'):
            self.graph().documents(validate=True)

    def test_graph_hash_and_path_escape_fail_closed(self):
        self.fixture()
        graph = self.graph()
        part = graph.directory/'tus.000.jsonl'
        part.write_text(part.read_text()+'\n')
        with self.assertRaisesRegex(ValueError, 'hash mismatch'):
            Graph(graph.directory)
        self.tables['tus'][0]['source'] = '../elsewhere.c'
        with self.assertRaisesRegex(ValueError, 'unsafe relative path'):
            self.graph()

    def test_compare_classifies_entry_difference(self):
        docs = self.fixture()
        graph = self.graph()
        for image, doc in docs.items():
            write_json(self.root/'lists'/f'{image}.json', doc)
        summary, holds = compare(graph, self.root/'lists')
        self.assertEqual(summary['lists_equal'], 2)
        docs['main/fixture']['entries'][1]['evidence'] = 'changed witness'
        write_json(self.root/'lists/main/fixture.json', docs['main/fixture'])
        summary, holds = compare(graph, self.root/'lists')
        self.assertEqual(summary['held_by_kind']['unresolved'], 1)
        self.assertEqual(holds[0]['image'], 'main/fixture')

    def test_sparse_v0_and_empty_bindings_stay_sparse(self):
        doc = dict(schema='azure-clean.linklist.v0', image='main/sparse', container='main',
                   foff=0, size=100, vma='0x80010000', entries=[dict(row='main/row',home='main/home',
                   tu='src/main/renamed.c',foff=20,vma='0x80010014',size=4)])
        self.add_doc(doc)
        self.assertEqual(self.graph().documents(validate=True)['main/sparse'], doc)

    def test_qualification_uses_home_and_image_and_avoids_sanitizing_collisions(self):
        prefix = qualification('town/one','town/home')
        self.assertEqual(prefix, qualification('town/one','town/home'))
        self.assertNotEqual(prefix, qualification('town/two','town/home'))
        self.assertNotEqual(qualification('town/a-b','town/home'), qualification('town/a_b','town/home'))
        self.assertNotEqual(qualification('town/one','town/home','town/row1'),
                            qualification('town/one','town/home','town/row2'))
        self.assertRegex(prefix, r'^[A-Za-z_][A-Za-z0-9_]*$')

    def test_emitter_groups_arbitrary_shared_vmas(self):
        script = emit_global('', [], [('dungeon/a',0x80152800,4,['. = 4;']),
                                      ('town/b',0x80016000,8,['. = 8;']),
                                      ('town/a',0x80016000,12,['. = 12;'])])
        self.assertEqual(script.count(' : NOCROSSREFS AT('), 2)
        self.assertIn('OVERLAY 0x80152800', script)
        self.assertLess(script.index('.town_a'), script.index('.town_b'))
        self.assertEqual(script.count('ASSERT(SIZEOF('), 3)

    def test_generator_refuses_authority_directory(self):
        self.fixture()
        with self.assertRaisesRegex(ValueError, 'no authority switch'):
            self.graph().generate(ROOT/'config/link')

    def test_map_summary_excludes_discards_and_supports_wrapped_sections(self):
        text = (' .text 0x0 0x100 build_slus/build/src/discarded.o\n'
                'Linker script and memory map\n.header 0x0 0x4\n'
                ' .data 0x0 0x4 build_slus/build/asm/header.o\n'
                '._800 0x8002d000 0x10\n .text.func_example\n'
                '                0x8002d000 0x8 build_slus/build/src/example.o\n'
                '.town_a 0x80016000 0x10\n .text 0x80016000 0x10 other.o\n')
        counts = slus_origins(text, ['.header','._800'], 20)
        self.assertEqual(counts, dict(C=8, imported_objects=4, linker_fill=8))

    def test_truncated_baseline_cannot_report_zero_differences(self):
        self.assertEqual(differences(b'abc', b'ab'), 1)
        self.assertEqual(differences(b'ab', b'abc'), 1)
        self.assertEqual(differences(b'abc', b'axd'), 2)

    @unittest.skipUnless(shutil.which('mipsel-linux-gnu-as') and shutil.which('mipsel-linux-gnu-ld'), 'MIPS binutils unavailable')
    def test_global_script_nocrossrefs_rejects_cross_bank_relocation(self):
        for name, body in [('a', '.globl a\na:\n.word b\n'), ('b', '.globl b\nb:\n.word 0\n')]:
            (self.root/f'{name}.s').write_text('.section .text\n'+body)
            subprocess.run(['mipsel-linux-gnu-as','-o',str(self.root/f'{name}.o'),str(self.root/f'{name}.s')], check=True)
        script = emit_global('', [], [('town/a',0x80016000,16,['KEEP(a.o(.text))', '. = 16;']),
                                      ('town/b',0x80016000,16,['KEEP(b.o(.text))', '. = 16;'])])
        (self.root/'global.ld').write_text(script)
        result = subprocess.run(['mipsel-linux-gnu-ld','-EL','-T','global.ld','-o','combined.elf','a.o','b.o'],
                                cwd=self.root, capture_output=True, text=True)
        self.assertNotEqual(result.returncode, 0)
        self.assertIn('prohibited cross reference', result.stderr)


if __name__ == '__main__':
    unittest.main()
