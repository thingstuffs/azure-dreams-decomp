"""Compact maps retain build semantics and reject incomplete or corrupt storage."""
import json
from pathlib import Path
import sys
import unittest
from unittest.mock import patch
sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import byte_map as B
import byte_map_format as F
import byte_map_rollout as R
from test_byte_map import Fixture, doc, meta, synthetic_disc
from extract_assets import extract


class CompactMaps(Fixture):
    def public(self, document):
        return F.write(self.root/'link'/document['container'], document)

    def test_all_seven_labels_profiles_and_tu_fields_round_trip(self):
        code = dict(row='main/func_80000000', home='main/func_80000000', tu='src/main/home.c',
                    foff='0x0', vma='0x80000000', size=4, evidence='unchanged placement', bindings={})
        entries = [code,
            meta('code_region',4,4,census_label='library_code'),
            meta('code_region',8,4,census_label='strongly_code'),
            meta('asset',12,4,census_label='proven_data',format='opaque',sha256='a'*64,extractor='container-slice-v1'),
            meta('data',16,4,type='typing pending'),meta('padding',20,4),meta('unresolved',24,4)]
        d = doc(entries,size=28,vma='0x80000000',symbols={'0x80000000':'0x80000000'},layout='same')
        paths = self.public(d)
        self.assertEqual(F.read_parts(paths),d)
        loaded = B.load_maps(self.root,'link')
        self.assertEqual(loaded[0]['main/test']['census'],dict.fromkeys(F.LABELS,4))
        self.assertEqual(loaded[2][code['row']]['tu'],code['tu'])
        self.assertEqual(len(paths[0].read_text().splitlines()),len(entries)+2)

    def test_legacy_tu_evidence_is_recovered_from_committed_config_only(self):
        code=dict(row='main/func_80000000',home='main/func_80000000',tu='src/main/other.c',
                  foff=0,vma=0x80000000,size=16,evidence='work/old_lane/proof.json')
        d=doc([code],vma=0x80000000)
        self.write(d)
        paths=self.public(d)
        self.assertNotIn('work/',paths[0].read_text())
        self.assertEqual(F.read_parts(paths,self.root),d)
        self.assertEqual(B.load_maps(self.root,'link')[2][code['row']]['evidence'],code['evidence'])
        with self.assertRaisesRegex(ValueError,'source root'):F.read_parts(paths)

    def test_split_reassembly_and_missing_or_duplicate_parts_are_refused(self):
        entries=[meta('unresolved',i*4,4) for i in range(20)]
        d=doc(entries,size=80)
        with patch.object(F,'PART_BYTES',100):paths=self.public(d)
        self.assertGreater(len(paths),1)
        self.assertTrue(all(p.stat().st_size<F.MAX_BYTES for p in paths))
        self.assertEqual(F.read_parts(paths),d)
        with self.assertRaisesRegex(ValueError,'part'):F.read_parts(paths[:-1])
        with self.assertRaisesRegex(ValueError,'part'):F.read_parts(paths+[paths[0]])

    def test_exact_tiling_uses_production_validation_after_decode(self):
        paths=self.public(doc([meta('unresolved',0,16)]))
        text=paths[0].read_text().replace('0\t16\tu\t','1\t16\tu\t')
        paths[0].write_text(text)
        with self.assertRaisesRegex(ValueError,'outside|gap'):B.load_maps(self.root,'link')

    def test_parts_must_agree_on_census_and_provenance(self):
        d=doc([meta('unresolved',i*4,4) for i in range(20)],size=80)
        with patch.object(F,'PART_BYTES',100):paths=self.public(d)
        lines=paths[1].read_text().splitlines(True)
        h=json.loads(lines[0][1:]);h['d']['t'][-1]=79
        lines[0]='#'+F.compact(h)+'\n';paths[1].write_text(''.join(lines))
        with self.assertRaisesRegex(ValueError,'disagree'):F.read_parts(paths)

    def test_profile_cannot_overwrite_the_rule_extent_or_kind(self):
        paths=self.public(doc([meta('unresolved',0,16)]))
        lines=paths[0].read_text().splitlines(True)
        h=json.loads(lines[0][1:]);h['p'][0]['foff']=5
        lines[0]='#'+F.compact(h)+'\n';paths[0].write_text(''.join(lines))
        with self.assertRaisesRegex(ValueError,'overwrites'):F.read_parts(paths)

    def test_duplicate_images_and_placements_are_rejected(self):
        d=doc([meta('unresolved',0,16)]);self.public(d)
        self.write(d)
        # A mixed catalogue cannot silently choose one encoding over another.
        directory=self.root/'link/main';(directory/'test.json').write_text(json.dumps(d))
        with self.assertRaisesRegex(ValueError,'duplicate image'):B.load_maps(self.root,'link')

    def test_adjacent_same_rule_merges_and_asset_hash_covers_the_new_extent(self):
        entries=[meta('asset',0,4,census_label='proven_data',format='opaque',sha256='a'*64,extractor='container-slice-v1'),
                 meta('asset',4,4,census_label='proven_data',format='opaque',sha256='b'*64,extractor='container-slice-v1'),
                 meta('unresolved',8,4),dict(meta('unresolved',12,4),evidence='other rule')]
        result=R.coalesce(entries,bytes(range(16)))
        self.assertEqual([(B.L.num(e['foff']),e['size']) for e in result],[(0,8),(8,4),(12,4)])
        self.assertEqual(result[0]['sha256'],R.digest(bytes(range(8))))
        self.assertEqual(len(entries),4)

    def test_coalescing_preserves_tu_and_census_label_boundaries(self):
        entries=[meta('code_region',0,4,census_label='proven_code'),
                 meta('code_region',4,4,census_label='strongly_code')]
        self.assertEqual(R.coalesce(entries,b'x'*8),entries)

    def test_asset_extractor_reads_the_compact_catalogue(self):
        disc=self.root/'disc.iso';payload=synthetic_disc(disc)
        entry=meta('asset',0,16,census_label='proven_data',format='opaque',sha256=R.digest(payload[:16]),extractor='container-slice-v1')
        d=doc([entry],name='dungeon/test',size=16);d['container']='dungeon'
        self.public(d)
        result=extract(self.root,disc,output=self.root/'work/assets',catalogue='link')
        self.assertEqual(result['count'],1)
        self.assertEqual((self.root/result['assets'][0]['path']).read_bytes(),payload[:16])


if __name__=='__main__':unittest.main()
