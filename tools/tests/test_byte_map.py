"""Whole-image byte maps: conservation, honest labels, legacy compatibility and user-disc extraction."""
import copy
import hashlib
import json
import os
from pathlib import Path
import struct
import sys
import tempfile
import unittest

TOOLS = Path(__file__).resolve().parents[1]
sys.path[:0] = [str(TOOLS), str(TOOLS/"gate")]
import byte_map as B
import linklist as L
from disc_slice import Disc
from extract_assets import extract


def meta(kind, off, size, **kw):
    return dict(kind=kind, foff=off, size=size, evidence="synthetic test witness", **kw)


def doc(entries, size=16, name="main/test", vma=None, **kw):
    counts = dict.fromkeys(L.CENSUS_LABELS, 0)
    for e in entries:
        if e.get("kind") != "image":
            counts[L.census_label(e)] += e["size"]
    return dict(schema=L.MAP_SCHEMA, image=name, container=name.split('/')[0], foff=0, size=size,
                vma=vma, entries=entries, census=kw.pop('census', counts), **kw)


class Fixture(unittest.TestCase):
    def setUp(self):
        self.tmp = tempfile.TemporaryDirectory(dir=os.environ.get('TMPDIR'))
        self.addCleanup(self.tmp.cleanup)
        self.root = Path(self.tmp.name)
        self.cp = self.root/'ledger/coverage_regions.jsonl'
        self.cp.parent.mkdir()
        self.cp.write_text('')

    def write(self, *docs):
        for d in docs:
            p = B.image_path(self.root, d['image'])
            p.parent.mkdir(parents=True, exist_ok=True)
            p.write_text(json.dumps(d))

    def labels(self, d, spans, children=None):
        h = {k: d[k] for k in ('image', 'container', 'foff', 'size', 'vma', 'census')}
        h.update(schema=B.INPUT_SCHEMA, evidence='synthetic census')
        if children:
            h['children'] = children
        return [h, *(dict(s, image=d['image']) for s in spans)]

    def export(self, records):
        p = self.root/'labels.jsonl'
        p.write_text(''.join(json.dumps(r)+'\n' for r in records))
        return p


class Schema(Fixture):
    def test_all_metadata_kinds_are_ignored_by_build_indices(self):
        es = [meta('data',0,2,type='u16'), meta('data',2,2,type='typing pending'), meta('padding',4,2),
              meta('leftover',6,2,reason='independent overwrite witness'), meta('unresolved',8,2),
              meta('code_region',10,2,census_label='library_code'),
              meta('asset',12,4,format='opaque',sha256='a'*64,extractor='container-slice-v1',census_label='noncode_typing_pending')]
        self.write(doc(es))
        imgs, by_place, by_row, local = L.load(self.root)
        self.assertEqual((by_place, by_row, local), ({}, {}, {}))
        self.assertEqual(L.check(self.root, {}, {}, lambda _: None), [])
        self.assertIsNone(L.placement(self.root, 'main', 12))
        self.assertEqual(L.window_files(self.root, ['main/arbitrary']), [])
        self.assertEqual(sum(imgs['main/test']['census'].values()), 16)

    def test_code_entry_shape_and_binding_survive_v1(self):
        code = dict(row='main/func_80000004', home='main/func_80000004', tu='src/main/home.c', foff=4, vma=0x80000004, size=4)
        d = doc([meta('padding',0,4),code,meta('unresolved',8,8)],vma=0x80000000)
        self.write(d)
        images, placements, rows, _ = L.load(self.root)
        self.assertEqual(list(rows), [code['row']])
        self.assertEqual(L.binding(self.root, rows[code['row']], 0x80000100), 0x80000100)
        self.assertEqual(len(placements),1)
        self.assertEqual(images[d['image']]['census']['proven_code'],4)

    def test_gaps_overlaps_order_and_bounds_fail(self):
        good=doc([meta('unresolved',0,8),meta('padding',8,8)])
        for changes, message in [({'foff':9,'size':7},'gap'), ({'foff':7,'size':9},'overlapping'),
                                 ({'size':7},'trailing gap'), ({'size':9},'outside'), ({'size':0},'outside')]:
            with self.subTest(changes=changes):
                d=copy.deepcopy(good);d['entries'][1].update(changes)
                with self.assertRaisesRegex(ValueError,message):L.validate_image(d)
        d=copy.deepcopy(good);d['entries'].reverse()
        with self.assertRaisesRegex(ValueError,'gap'):L.validate_image(d)

    def test_stale_census_fails_in_production_loader(self):
        d=doc([meta('unresolved',0,16)]);d['census']['unknown']-=1
        self.write(d)
        self.assertTrue(any('census totals differ' in x for x in L.check(self.root,{}, {},lambda _:None)))

    def test_metadata_requires_v1(self):
        d=doc([meta('unresolved',0,16)],vma=0);d['schema']=L.SCHEMA;del d['census']
        with self.assertRaisesRegex(ValueError,'requires'):L.validate_image(d)

    def test_assets_and_leftovers_need_evidence_and_required_fields(self):
        asset=meta('asset',0,16,format='opaque',sha256='a'*64,extractor='container-slice-v1',census_label='noncode_typing_pending')
        for field,value in [('sha256','0'),('format',''),('extractor','shell-command'),('census_label','unknown'),('evidence','')]:
            with self.subTest(field=field):
                e=dict(asset,**{field:value})
                with self.assertRaises(ValueError):L.validate_image(doc([asset])|{'entries':[e]})
        with self.assertRaises(ValueError):L.validate_image(doc([meta('leftover',0,16,reason='')]))
        e=dict(asset,tu='src/should_never_compile.c')
        with self.assertRaises(ValueError):L.validate_image(doc([asset])|{'entries':[e]})

    def test_image_references_are_single_ownership_and_require_exact_extent(self):
        child=doc([meta('unresolved',0,16)])
        parent=doc([meta('image',0,16,ref='main/test')],name='main/container',census=child['census'])
        self.write(child,parent)
        self.assertEqual(B.check(self.root)['root_bytes'],16)
        parent['entries'][0]['ref']='town/test';self.write(parent)
        with self.assertRaisesRegex(ValueError,'reference extent'):L.load(self.root)

    def test_cycle_and_sparse_child_fail(self):
        a=doc([meta('image',0,16,ref='main/b')],name='main/a')
        b=doc([meta('image',0,16,ref='main/a')],name='main/b')
        self.write(a,b)
        with self.assertRaisesRegex(ValueError,'cycle'):L.load(self.root)
        b=dict(b,schema=L.SCHEMA,entries=[],vma=0);del b['census'];self.write(b)
        with self.assertRaisesRegex(ValueError,'v1 child'):L.load(self.root)

    def test_overlapping_root_images_cannot_be_added_to_the_denominator(self):
        self.write(doc([meta('unresolved',0,16)]),doc([meta('unresolved',0,16)],name='main/alias'))
        with self.assertRaisesRegex(ValueError,'root images overlap'):B.check(self.root)

    def test_complete_container_mode_refuses_partial_rollout(self):
        self.write(doc([meta('unresolved',0,16)]))
        (self.root/'ledger/containers.jsonl').write_text(json.dumps({'container':'main','bytes':32})+'\n')
        with self.assertRaisesRegex(ValueError,'incomplete'):B.check(self.root,complete=True)


class Generator(Fixture):
    def test_deterministic_generation_preserves_code_dict_and_reproduces_labels(self):
        code=dict(row='main/func_80000004',home='main/func_80000004',tu='src/main/home.c',foff=4,vma=0x80000004,size=4)
        old=dict(schema=L.SCHEMA,image='main/test',container='main',foff=0,size=16,vma=0x80000000,entries=[code])
        self.write(old)
        spans=[dict(foff=0,size=4,label='unknown',evidence='unknown'),dict(foff=4,size=8,label='proven_code',evidence='MATCH'),
               dict(foff=12,size=4,label='padding_leftover',kind='padding',evidence='zero fill')]
        h=dict(old,census=B.totals(spans))
        p=self.export(self.labels(h,spans))
        docs,_=B.generate(self.root,p,self.cp)
        self.assertIn(code,docs['main/test']['entries'])
        self.assertEqual(B.generate(self.root,p,self.cp)[0],docs)
        self.write(*docs.values())
        self.assertEqual(B.check(self.root,p)['root_bytes'],16)

    def test_census_input_must_tile_and_match_its_declared_totals(self):
        spans=[dict(foff=0,size=16,label='unknown',evidence='held')]
        d=doc([meta('unresolved',0,16)])
        for change in [dict(foff=1),dict(size=15),dict(size=17),dict(size=-1),dict(label='made_up')]:
            with self.subTest(change=change):
                p=self.export(self.labels(d,[dict(spans[0],**change)]))
                with self.assertRaises(ValueError):B.read_labels(p)

    def test_existing_code_conflict_fails_without_writing(self):
        code=dict(row='main/func_80000000',home='main/func_80000000',tu='src/main/a.c',foff=0,vma=0x80000000,size=16)
        d=doc([code],vma=0x80000000);self.write(d)
        spans=[dict(foff=0,size=16,label='unknown',evidence='stale snapshot')]
        h=dict(d,census=B.totals(spans));p=self.export(self.labels(h,spans))
        with self.assertRaisesRegex(ValueError,'contradicts existing code'):B.generate(self.root,p,self.cp)
        self.assertEqual(json.loads(B.image_path(self.root,d['image']).read_text()),d)

    def test_unknown_never_becomes_leftover_or_typed_data(self):
        for label,kw in [('proven_data',{}),('padding_leftover',{}),('unknown',{'kind':'leftover','reason':'guess'})]:
            with self.subTest(label=label):
                with self.assertRaises(ValueError):B.metadata(dict(foff=0,size=4,label=label,evidence='witness',**kw))
        pending=B.metadata(dict(foff=0,size=4,label='noncode_typing_pending',evidence='noncode detector'))
        self.assertEqual(pending['type'],'typing pending')

    def test_references_conserve_all_seven_labels(self):
        labels=list(L.CENSUS_LABELS)
        spans=[dict(foff=i*4,size=4,label=label,evidence='witness',**({'type':'u32'} if label=='proven_data' else {}),
                    **({'kind':'padding'} if label=='padding_leftover' else {})) for i,label in enumerate(labels)]
        child=doc([],size=28,census=B.totals(spans))
        parent=doc([],size=28,name='main/container',census=child['census'])
        p=self.export(self.labels(child,spans)+self.labels(parent,spans,children=['main/test']))
        docs,_=B.generate(self.root,p,self.cp)
        self.write(*docs.values())
        result=B.check(self.root,p)
        self.assertEqual(result['root_bytes'],28)
        self.assertEqual(result['images']['main/container']['census'],dict.fromkeys(labels,4))

    def test_asset_in_referenced_child_keeps_its_extent_and_hash(self):
        span=dict(foff=0,size=16,label='noncode_typing_pending',kind='asset',format='opaque',sha256='a'*64,
                  extractor='container-slice-v1',evidence='physical noncode blob')
        child=doc([],census=B.totals([span]))
        parent=doc([],name='main/container',census=child['census'])
        p=self.export(self.labels(child,[span])+self.labels(parent,[span],children=['main/test']))
        docs,_=B.generate(self.root,p,self.cp)
        self.assertEqual(docs['main/test']['entries'][0]['sha256'],span['sha256'])
        self.assertEqual(docs['main/container']['entries'][0]['kind'],'image')

    def test_empty_export_and_malformed_provenance_fail(self):
        with self.assertRaises(ValueError):B.read_labels(self.export([]))
        d=doc([meta('unresolved',0,16)],provenance={'labels_sha256':'x'})
        with self.assertRaisesRegex(ValueError,'provenance'):L.validate_image(d)

    def test_checker_finds_boundary_change_even_when_totals_match(self):
        spans=[dict(foff=0,size=8,label='unknown',evidence='held'),dict(foff=8,size=8,label='proven_code',evidence='MATCH')]
        d=doc([],census=B.totals(spans));p=self.export(self.labels(d,spans))
        docs,_=B.generate(self.root,p,self.cp);self.write(*docs.values())
        spans[0]['label'],spans[1]['label']=spans[1]['label'],spans[0]['label']
        self.export(self.labels(d,spans))
        with self.assertRaisesRegex(ValueError,'provenance'):B.check(self.root,p)
        docs['main/test']['provenance']['labels_sha256']=B.sha256(p);self.write(*docs.values())
        with self.assertRaisesRegex(ValueError,'label differs'):B.check(self.root,p)

    def test_unsafe_image_id_and_negative_census_totals_fail(self):
        d=doc([meta('unresolved',0,16)])
        rows=self.labels(d,[dict(foff=0,size=16,label='unknown',evidence='held')])
        rows[0]['image']='main/../../escape'
        with self.assertRaisesRegex(ValueError,'unsafe'):B.read_labels(self.export(rows))
        with self.assertRaises(ValueError):L._totals({'unknown':-1})
        with self.assertRaises(ValueError):L._totals({'unknown':True})

    def test_coverage_categories_are_independent_overlapping_witnesses(self):
        self.cp.write_text(''.join(json.dumps(dict(container='main',foff=a,size=b-a,category=c))+'\n'
                                   for a,b,c in [(0,12,'window'),(4,16,'window'),(0,4,'data_excluded')]))
        counts=B.coverage_summary(self.cp,{'main/test':dict(container='main',foff=0,size=16)})
        self.assertEqual(counts['main/test'],{'window':16,'data_excluded':4})


def record(name,lba,size,directory=False):
    name=name.encode('ascii') if isinstance(name,str) else name
    n=33+len(name);n+=n%2
    out=bytearray(n);out[0]=n;out[25]=2 if directory else 0;out[32]=len(name);out[33:33+len(name)]=name
    struct.pack_into('<I',out,2,lba);struct.pack_into('>I',out,6,lba)
    struct.pack_into('<I',out,10,size);struct.pack_into('>I',out,14,size)
    return out


def synthetic_disc(path,raw=False,mode1=False):
    data=bytearray(25*2048)
    data[16*2048:16*2048+7]=b'\x01CD001\x01'
    data[16*2048+156:16*2048+190]=record(b'\x00',20,2048,True)
    root=record('DUNGEON',21,2048,True);data[20*2048:20*2048+len(root)]=root
    child=record('DUNGEON.BIN;1',22,4096);data[21*2048:21*2048+len(child)]=child
    payload=bytes(range(256))*16;data[22*2048:24*2048]=payload
    if raw:
        offset=16 if mode1 else 24
        sectors=[]
        for i in range(25):
            s=bytearray(2352);s[offset:offset+2048]=data[i*2048:(i+1)*2048];sectors.append(s)
        data=b''.join(sectors)
    path.write_bytes(data)
    return payload


class Extraction(Fixture):
    def asset_map(self,bad_hash=False):
        self.disc=self.root/'synthetic.bin'
        payload=synthetic_disc(self.disc,raw=True)
        sha='0'*64 if bad_hash else hashlib.sha256(payload[2040:2072]).hexdigest()
        e=meta('asset',2040,32,format='synthetic-opaque',sha256=sha,extractor='container-slice-v1',census_label='noncode_typing_pending')
        d=doc([e],size=32,name='dungeon/asset');d['foff']=2040;self.write(d)
        return payload

    def test_iso_mode1_and_mode2_slices_cross_sector_boundaries(self):
        for raw,mode1 in [(False,False),(True,False),(True,True)]:
            with self.subTest(raw=raw,mode1=mode1):
                p=self.root/'disc.bin';payload=synthetic_disc(p,raw,mode1)
                with Disc(p) as disc:
                    self.assertEqual(disc.slice('DUNGEON/DUNGEON.BIN',2040,32),payload[2040:2072])
                    with self.assertRaisesRegex(ValueError,'outside'):disc.slice('DUNGEON/DUNGEON.BIN',4090,32)

    def test_extraction_publishes_only_verified_bytes_under_ignored_directory(self):
        payload=self.asset_map()
        receipt=extract(self.root,self.disc)
        self.assertEqual(receipt['count'],1)
        target=self.root/receipt['assets'][0]['path']
        self.assertEqual(target.read_bytes(),payload[2040:2072])
        self.assertEqual(extract(self.root,self.disc),receipt)
        self.assertTrue((self.root/'work/assets/.gitignore').read_text().startswith('*\n'))

    def test_wrong_hash_leaves_no_blob_or_temp_file(self):
        self.asset_map(bad_hash=True)
        with self.assertRaisesRegex(ValueError,'SHA-256 differs'):extract(self.root,self.disc)
        directory=self.root/'work/assets/dungeon'
        self.assertEqual(list(directory.iterdir()),[])

    def test_extract_refuses_output_escape_and_symlink_escape(self):
        self.asset_map()
        with self.assertRaises(ValueError):extract(self.root,self.disc,output=self.root/'src')
        escape=self.root/'outside-assets';escape.mkdir()
        base=self.root/'work/assets';base.mkdir(parents=True)
        (base/'dungeon').symlink_to(escape,target_is_directory=True)
        with self.assertRaises(ValueError):extract(self.root,self.disc)

    def test_disc_reader_refuses_wrong_disc_and_truncated_data(self):
        p=self.root/'bad.bin';p.write_bytes(b'not a disc')
        with self.assertRaisesRegex(ValueError,'not a supported'):Disc(p)
        synthetic_disc(p)
        with p.open('r+b') as f:f.truncate(23*2048)
        with Disc(p) as disc:
            with self.assertRaisesRegex(ValueError,'truncated'):disc.slice('DUNGEON/DUNGEON.BIN',2040,32)

    def test_generator_verifies_asset_hash_against_retail(self):
        self.asset_map()
        d=json.loads(B.image_path(self.root,'dungeon/asset').read_text())
        p=self.root/B.RETAIL['dungeon'];p.parent.mkdir(parents=True)
        p.write_bytes(bytes(range(256))*16)
        e=d['entries'][0]
        span={k:v for k,v in e.items() if k!='census_label'};span['label']=e['census_label']
        labels=self.export(self.labels(d,[span]))
        B.generate(self.root,labels,self.cp,verify_retail=True)
        span['sha256']='0'*64;labels=self.export(self.labels(d,[span]))
        with self.assertRaisesRegex(ValueError,'sha256 differs'):B.generate(self.root,labels,self.cp,verify_retail=True)


if __name__=='__main__':unittest.main()
