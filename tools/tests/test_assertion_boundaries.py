"""Scheduled prologues must not become phantom functions or hide real stubs."""
import csv
import hashlib
import io
import json
import struct
import sys
import tempfile
import unittest
from pathlib import Path
from unittest.mock import patch

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import assertion_boundaries as boundaries
import evidence
import modules


class BoundaryTests(unittest.TestCase):
    def fixture(self):
        data = bytearray(0x180)
        words = {0: 0x0C000008, 0x18: 0x03E00008, 0x1C: 0xAC430000,
                 0x20: 0x3C028070, 0x24: 0x8C420740, 0x28: 0x27BDFFE8,
                 0x2C: 0x10400012, 0x30: 0xAFBF0010,
                 0x40: 0x0040F809, 0x44: 0x3406004B,
                 0x78: 0x03E00008, 0x7C: 0x27BD0018}
        for at, w in words.items(): struct.pack_into("<I", data, at, w)
        fmt = b'Example check in %s at %d\n\0'
        data[0x100:0x100 + len(fmt)] = fmt
        data[0x128:0x132] = b'example.c\0'
        source = "TOWN.BIN+0x128/10"
        spec = {"site_foff": "0x40", "entry_foff": "0x20", "size": 96, "line": 75,
                "scan_start": "0x0", "scan_end": "0x80", "source_name_ref": source,
                "pool_sha256": hashlib.sha256(data[0x100:0x140]).hexdigest(),
                "range_sha256": hashlib.sha256(data[0x18:0x80]).hexdigest()}
        site = {"container": "TOWN.BIN", "source_file": source, "kind": "assert", "line": "75",
                "containing_func_foff": "0x28", "containing_func_size": "88",
                "derived_base": "0x80000000", "site_foff": "0x40", "chunk_pool_foff": "0x100", "notes": ""}
        return data, spec, site

    def test_hoisted_flag_load_is_part_of_entry_and_repair_is_idempotent(self):
        data, spec, site = self.fixture()
        corrected, receipt = boundaries.audit(site, spec, io.BytesIO(data), {})
        self.assertEqual(corrected["containing_func_foff"], "0x20")
        self.assertEqual(corrected["containing_func_size"], "96")
        self.assertEqual(receipt["flag_object_address"], "0x80700740")
        again, receipt = boundaries.audit(corrected, spec, io.BytesIO(data), {})
        self.assertEqual(again, corrected)
        self.assertTrue(receipt["already_corrected"])

    def test_genuine_eight_byte_return_stub_is_rejected(self):
        data, spec, site = self.fixture()
        struct.pack_into("<II", data, 0x20, 0x03E00008, 0)
        with self.assertRaisesRegex(ValueError, "expected flag address"):
            boundaries.audit(site, spec, io.BytesIO(data), {})

    def test_changed_pool_refuses_the_assertion_witness(self):
        data, spec, site = self.fixture()
        data[0x13f] ^= 1
        with self.assertRaisesRegex(ValueError, "pool differ"):
            boundaries.audit(site, spec, io.BytesIO(data), {})

    def test_flag_clobber_before_branch_is_rejected(self):
        words = [0x3C028070, 0x8C420740, 0x27BDFFE8, 0x24020000, 0x10400012]
        with self.assertRaisesRegex(ValueError, "not proven live"):
            boundaries.scheduled_flag_prefix(struct.pack("<5I", *words), 0)

    def test_stack_stores_and_argument_saves_preserve_flag(self):
        words = [0x3C028070, 0x8C42309C, 0x27BDFFE0, 0xAFB10014,
                 0x00808821, 0xAFB00010, 0x00A08021, 0x10400012]
        result = boundaries.scheduled_flag_prefix(struct.pack("<8I", *words), 0)
        self.assertEqual(result["branch_offset"], 28)

    def test_incoming_transfer_to_plus_eight_prevents_automatic_repair(self):
        data, spec, site = self.fixture()
        struct.pack_into("<I", data, 4, 0x0800000A)
        with self.assertRaisesRegex(ValueError, "direct calls"):
            boundaries.audit(site, spec, io.BytesIO(data), {})

    def test_line_and_registered_extent_are_checked(self):
        data, spec, site = self.fixture()
        with self.assertRaisesRegex(ValueError, "different extent"):
            boundaries.audit(site, spec, io.BytesIO(data), {0x20: {"size": 88}})
        struct.pack_into("<I", data, 0x44, 0x3406004C)
        with self.assertRaisesRegex(ValueError, "line constant"):
            boundaries.audit(site, spec, io.BytesIO(data), {})

    def test_j_targets_compare_encoded_bits_across_object_address_views(self):
        data = struct.pack("<II", 0x0C000F7C, 0x08000F7E)
        refs = boundaries.direct_xrefs(data, 0x838100, 0x7F7CB800, 0x8385F0, 0x8385F8)
        self.assertEqual([r["target"] for r in refs], ["entry", "stack"])


class EvidenceTests(unittest.TestCase):
    def fixture(self):
        row = {"id": "town/func_80878A78", "container": "town", "func": "func_80878A78",
               "foff": 0x7F8A78, "size": 304, "true_name": "func_80702A78"}
        site = {"container": "TOWN.BIN", "source_file": "TOWN.BIN+0x128/10", "line": "226", "kind": "assert",
                "expression_or_null": "", "distinct_id": "D067", "site_vram": "0x80702ABC",
                "containing_func_foff": "0x7F8A78", "containing_function": "func_80878A78",
                "attribution": "direct", "true_name": "", "func_status": "MATCH", "containing_func_size": "304"}
        return row, site

    def test_corrected_offset_gives_direct_ownership(self):
        row, site = self.fixture()
        aggregates, unowned, per = evidence.assertion_evidence([row], [site])
        self.assertEqual(unowned, [])
        self.assertEqual(aggregates[0]["source_files"], [site["source_file"]])
        self.assertTrue(per[row["id"]]["assert_sites"][0]["own_copy"])

    def test_an_interior_offset_stays_unowned_without_audited_correction(self):
        row, site = self.fixture(); site["containing_func_foff"] = "0x7F8A80"
        aggregates, unowned, per = evidence.assertion_evidence([row], [site])
        self.assertEqual(aggregates, [])
        self.assertEqual(len(unowned), 1)

    def test_retired_copy_still_resolves_by_true_name(self):
        row, site = self.fixture()
        site.update(containing_func_foff="0x1110", true_name=row["true_name"])
        aggregates, unowned, per = evidence.assertion_evidence([row], [site])
        self.assertEqual(unowned, [])
        self.assertEqual(aggregates[0]["id"], row["id"])
        self.assertFalse(per[row["id"]]["assert_sites"][0]["own_copy"])

    def test_module_check_uses_disc_source_name(self):
        row, site = self.fixture()
        proposal = {"container": "town", "modules": [{"name": "example.c", "rows": [row["id"]]}]}
        site["source_file"] = "TOWN.BIN+0x4/10"
        with tempfile.TemporaryDirectory() as tmp:
            root = Path(tmp)
            container = root / "work/disc/containers"
            container.mkdir(parents=True)
            (container / "TOWN_TOWN.BIN").write_bytes(b"xxxxexample.c\0")
            with patch.object(modules, "ROOT", root), patch.object(modules, "rows", return_value=[row]), \
                 patch.object(modules, "load_bases", return_value={}), \
                 patch.object(modules, "assertion_files", return_value={row["id"]: {site["source_file"]}}):
                self.assertEqual(modules.check(proposal), [])
                proposal["modules"][0]["name"] = "different.c"
                errors = modules.check(proposal)
                self.assertEqual(len(errors), 1)
                self.assertIn(site["source_file"], errors[0])

    def test_catalogue_rejects_literal_expression_text(self):
        row, site = self.fixture()
        site["expression_or_null"] = "invented expression"
        with self.assertRaisesRegex(ValueError, "must be a disc location"):
            evidence.assertion_evidence([row], [site])

    def test_scoped_refresh_preserves_unrelated_evidence_and_is_idempotent(self):
        row, site = self.fixture()
        other = {**row, "id": "town/other", "func": "other", "foff": 0x100}
        other_evidence = {"id": other["id"], "container": "town", "func": "other", "knowledge": [{"doc": "keep me"}],
                          "assert_sites": [], "assert_copies": 0, "identifiers": []}
        with tempfile.TemporaryDirectory() as tmp:
            root = Path(tmp); ev = root / "evidence"; ev.mkdir(); source = root / "sites.csv"
            with source.open("w", newline="") as f:
                writer = csv.DictWriter(f, list(site)); writer.writeheader(); writer.writerow(site)
            evidence.write_jsonl(ev / "assertions.jsonl", [])
            evidence.write_jsonl(ev / "rows.jsonl", [other_evidence])
            with patch.object(evidence, "EV", ev), patch.object(evidence, "CSV", source), patch.object(evidence, "rows", return_value=[row, other]):
                evidence.refresh_assertions([row["id"]])
                first = {p.name: p.read_bytes() for p in ev.iterdir()}
                records = {r["id"]: r for r in evidence.read_jsonl(ev / "rows.jsonl")}
                self.assertEqual(records[other["id"]], other_evidence)
                self.assertEqual(records[row["id"]]["assert_sites"][0]["source_file"], site["source_file"])
                evidence.refresh_assertions([row["id"]])
                self.assertEqual(first, {p.name: p.read_bytes() for p in ev.iterdir()})
                with patch.object(evidence, "rows", return_value=[row]):
                    evidence.refresh_assertions()
                records = {r["id"]: r for r in evidence.read_jsonl(ev / "rows.jsonl")}
                self.assertEqual(records[other["id"]]["knowledge"], other_evidence["knowledge"])


if __name__ == "__main__":
    unittest.main()
