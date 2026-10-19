"""No-region placements require exact load evidence and cannot bypass solved rowbase."""
import hashlib
import json
from test_linklist import Fixture, image, HOME, COPY, K


class LoadAddress(Fixture):
    def setUp(self):
        super().setUp()
        self.record = dict(schema="azure-clean.instance-load-region.v1", container="dungeon",
                           foff=0xFAD000, size=0x6000, base=0x8016A800,
                           delta=0x8016A800-0xFAD000, method="validated synthetic loader witness",
                           evidence="synthetic fixture")
        (self.root / "ledger").mkdir()
        self.proof = dict(path="ledger/instance_load_regions.jsonl", record_sha256=self.digest(self.record))
        self.put_record(self.record)
        self.pair(load_evidence=self.proof)

    def digest(self, r):
        return hashlib.sha256(json.dumps(r, sort_keys=True, separators=(",", ":")).encode()).hexdigest()

    def put_record(self, r):
        (self.root / "ledger/instance_load_regions.jsonl").write_text(json.dumps(r)+"\n")

    def vma(self, **kw):
        return K.placement_vma(self.root, "dungeon", 0xFB0664, 56, COPY["row"], **kw)

    def test_checked_image_base(self):
        self.assertEqual(self.vma(), 0x8016DE64)
        self.assertIn("ledger/instance_load_regions.jsonl", K.window_files(self.root, [COPY["row"]]))

    def test_stale_or_missing_record_refused(self):
        self.put_record(dict(self.record, base=self.record["base"]+4))
        with self.assertRaisesRegex(ValueError, "missing or stale"):
            self.vma()
        self.put_record({})
        with self.assertRaisesRegex(ValueError, "missing or stale"):
            self.vma()

    def test_wrong_geometry_refused_even_with_fresh_digest(self):
        for change in ({"base":self.record["base"]+4}, {"container":"town"}, {"size":0x100}, {"delta":0}):
            with self.subTest(change=change):
                bad = dict(self.record, **change)
                self.put_record(bad)
                self.pair(load_evidence=dict(self.proof, record_sha256=self.digest(bad)))
                with self.assertRaisesRegex(ValueError, "disagrees"):
                    self.vma()

    def test_unrecognised_record_method_refused(self):
        for method in ("heuristic guess", "", None):
            with self.subTest(method=method):
                bad = dict(self.record, method=method)
                self.put_record(bad)
                self.pair(load_evidence=dict(self.proof, record_sha256=self.digest(bad)))
                with self.assertRaisesRegex(ValueError, "disagrees"):
                    self.vma()
        for method in ("validated dungeon loader arithmetic", "internal link-evidence; coherent table"):
            with self.subTest(method=method):
                good = dict(self.record, method=method)
                self.put_record(good)
                self.pair(load_evidence=dict(self.proof, record_sha256=self.digest(good)))
                self.assertEqual(self.vma(), 0x8016DE64)

    def test_free_form_evidence_cannot_supply_base(self):
        self.pair(evidence="unverified claim")
        with self.assertRaisesRegex(ValueError, "no checked load evidence"):
            self.vma()

    def test_solved_region_requires_promotion(self):
        (self.root / "config/overlays").mkdir()
        (self.root / "config/overlays/dungeon.rowbase.jsonl").write_text(json.dumps(dict(
            foff_start="0xFAD000", foff_end="0xFB3000", delta="0x7F1BD800", base_confidence="solved"))+"\n")
        with self.assertRaisesRegex(ValueError, "promotion"):
            self.vma()

    def test_proven_region_must_agree(self):
        self.assertEqual(self.vma(proven_delta=0x8016DE64-0xFB0664), 0x8016DE64)
        with self.assertRaisesRegex(ValueError, "disagrees with proven"):
            self.vma(proven_delta=0)
        with self.assertRaisesRegex(ValueError, "extent"):
            K.placement_vma(self.root, "dungeon", 0xFB0664, 52, COPY["row"])

    def test_own_file_and_home_do_not_gain_a_base(self):
        self.assertIsNone(K.placement_vma(self.root, "dungeon", 0, 8, "dungeon/func_00000000"))
        self.assertIsNone(K.placement_vma(self.root, "dungeon", 0xFAA664, 56, HOME["row"]))

    def test_legacy_loader_keeps_existing_link_behavior(self):
        self.pair()
        self.assertIsNone(self.vma(allow_legacy=True))
        with self.assertRaisesRegex(ValueError, "no checked load evidence"):
            self.vma()
