"""Source relocation, flat gate projections, cache freshness, and guarded moves."""
import hashlib
import importlib.util
import json
import os
from pathlib import Path
import subprocess
import sys
import tempfile
import unittest
from unittest.mock import patch

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))
import source_layout as L
import guarded_package as P


class LayoutTest(unittest.TestCase):
    def setUp(self):
        self.tmp = tempfile.TemporaryDirectory()
        self.addCleanup(self.tmp.cleanup)
        self.root = Path(self.tmp.name)
        (self.root / "ledger").mkdir()
        self.rows = [{"id": "dungeon/func_A", "container": "dungeon", "c_path": "overlays/old/func_A.c"},
                     {"id": "slus/w_B", "container": "slus", "c_path": "src/w_B.c"}]
        (self.root / "ledger/rows.jsonl").write_text("".join(json.dumps(r) + "\n" for r in self.rows))
        for r in self.rows:
            p = self.root / L.flat_relative(r)
            p.parent.mkdir(parents=True, exist_ok=True)
            p.write_text(r["id"] + "\n")

    def layout(self, records):
        (self.root / "ledger/layout.jsonl").write_text("".join(json.dumps(r) + "\n" for r in records))

    def move(self):
        old = L.row_path(self.rows[0], self.root)
        new = self.root / "src/dungeon/banks/sel_21/test/func_A.c"
        new.parent.mkdir(parents=True)
        old.rename(new)
        self.layout([{"id": self.rows[0]["id"], "path": new.relative_to(self.root).as_posix()}])
        return new

    def test_identity_absent_sparse_and_explicit(self):
        for records in (None, [], [{"id": r["id"], "path": L.flat_relative(r)} for r in self.rows]):
            if records is not None:
                self.layout(records)
            for r in self.rows:
                self.assertEqual(L.row_path(r, self.root), self.root / L.flat_relative(r))
                self.assertEqual(L.row_path(r["id"], self.root), L.row_path(r, self.root))
            self.assertEqual(L.validate(self.root), 2)
            self.assertEqual(L.materialize_flat(self.root / "projection", self.root), self.root / "src")
            self.assertFalse((self.root / "projection").exists())

    def test_moved_file_live_projection_and_scans(self):
        new = self.move()
        self.assertEqual(L.row_path(self.rows[0], self.root), new)
        self.assertEqual(L.source_files("dungeon", self.root), [new])
        projection = L.materialize_flat(self.root / "projection", self.root)
        facade = projection / "dungeon/func_A.c"
        self.assertTrue(facade.is_symlink())
        self.assertEqual(facade.read_bytes(), new.read_bytes())
        new.write_text("updated candidate\n")
        self.assertEqual(facade.read_text(), "updated candidate\n")
        self.assertEqual(L.materialize_flat(projection, self.root), projection)
        with patch("common.ROOT", self.root):
            from common import clean_path
            self.assertEqual(clean_path(self.rows[0]), new)
        from lanes.ledger import tree_path
        self.assertEqual(tree_path(self.root, self.rows[0]), new)

    def test_inverse_and_lane_cache_follow_layout_revision(self):
        from lanes.ledger import row_paths
        old = L.row_path(self.rows[0], self.root)
        self.assertEqual(row_paths(self.root)[self.rows[0]["id"]], old)
        new = self.move()
        self.assertEqual(row_paths(self.root)[self.rows[0]["id"]], new)
        self.assertEqual(L.row_path({"id": self.rows[0]["id"]}, self.root), new)
        self.assertEqual(L.row_ids_for_paths([new.relative_to(self.root).as_posix(),
                                             L.flat_relative(self.rows[0])], self.root),
                         [self.rows[0]["id"]])
        self.assertEqual(L.row_ids_for_paths(["src/dungeon/modules/aux.c"], self.root), [])

    def test_context_oracle_reads_the_supplied_roots_layout(self):
        from lanes.lanekit.context_oracle import Oracle
        new = self.move()
        new.write_text("void func_80010000(void) {}\n")
        self.rows[0].update(foff=0, size=8, true_name="func_80010000")
        (self.root / "ledger/rows.jsonl").write_text("".join(json.dumps(r) + "\n" for r in self.rows))
        image = self.root / "work/disc/containers/DUNGEON_DUNGEON.BIN"
        image.parent.mkdir(parents=True)
        image.write_bytes(bytes.fromhex("0800e00300000000"))
        oracle = Oracle(self.root)
        self.assertEqual(oracle.by_row[self.rows[0]["id"]][0]["source"], new.relative_to(self.root).as_posix())

    def test_nested_auxiliary_wrapper_is_projected(self):
        self.move()
        wrapper = self.root / "src/slus/core/wrapper.c"
        wrapper.parent.mkdir(parents=True)
        wrapper.write_text("/* wrapper */\n")
        flat = L.materialize_flat(self.root / "projection", self.root)
        self.assertEqual((flat / "slus/core/wrapper.c").read_bytes(), wrapper.read_bytes())

    def test_cache_freshness_and_split_record(self):
        before = L.row_path(self.rows[0], self.root)
        p = self.root / "ledger/layout.jsonl"
        self.layout([{"id": self.rows[0]["id"], "path": "src/dungeon/moved/func_A.c"}])
        moved = L.row_path(self.rows[0], self.root)
        self.assertNotEqual(before, moved)
        split = {"container": "dungeon", "c_path": self.rows[0]["c_path"]}
        self.assertEqual(L.row_path(split, self.root), moved)
        self.layout([])
        self.assertEqual(L.row_path(self.rows[0], self.root), before)

    def test_unsafe_unknown_duplicate_and_stem_change(self):
        for records in ([{"id": "dungeon/unknown", "path": "src/dungeon/unknown.c"}],
                        [{"id": self.rows[0]["id"], "path": "src/dungeon/../func_A.c"}],
                        [{"id": self.rows[0]["id"], "path": "src/slus/func_A.c"}],
                        [{"id": self.rows[0]["id"], "path": "src/dungeon/renamed.c"}],
                        [{"id": self.rows[0]["id"], "path": "/src/dungeon/func_A.c"}],
                        [{"id": self.rows[0]["id"], "path": "src/dungeon/func_A.c"}] * 2):
            self.layout(records)
            with self.assertRaises(ValueError):
                L.mapping(self.root)

    def test_symlink_escape_and_unmanaged_projection(self):
        directory = self.root / "src/dungeon/escape"
        directory.symlink_to(self.root / "ledger", target_is_directory=True)
        self.layout([{"id": self.rows[0]["id"], "path": "src/dungeon/escape/func_A.c"}])
        with self.assertRaises(ValueError):
            L.row_path(self.rows[0], self.root)
        directory.unlink()
        self.layout([])
        self.move()
        projection = self.root / "projection"
        projection.mkdir()
        (projection / "manual.c").write_text("manual")
        with self.assertRaises(ValueError):
            L.materialize_flat(projection, self.root)
        self.assertEqual((projection / "manual.c").read_text(), "manual")

    def test_raw_and_experiment_projection_passthrough(self):
        self.move()
        alternate = self.root / "experiment"
        self.assertEqual(L.materialize_flat(self.root / "projection", self.root, alternate), alternate)
        self.assertFalse((self.root / "projection").exists())

    def test_nested_experiment_uses_candidate_bytes(self):
        new = self.move()
        alternate = self.root / "experiment"
        candidate = alternate / new.relative_to(self.root / "src")
        candidate.parent.mkdir(parents=True)
        candidate.write_text("experimental candidate\n")
        flat = L.materialize_flat(self.root / "experiment_projection", self.root, alternate)
        self.assertEqual((flat / "dungeon/func_A.c").read_text(), "experimental candidate\n")
        self.assertNotEqual((flat / "dungeon/func_A.c").read_bytes(), new.read_bytes())

    def test_slus_export_token_resolves_tree_map(self):
        self.layout([{"id": "slus/w_B", "path": "src/slus/core/runtime/w_B.c"}])
        self.assertEqual(L.slus_source("src/w_B.c", self.root), self.root / "src/slus/core/runtime/w_B.c")
        with self.assertRaises(ValueError):
            L.slus_source("src/../w_B.c", self.root)


class GuardedPackageTest(unittest.TestCase):
    def setUp(self):
        self.tmp = tempfile.TemporaryDirectory()
        self.addCleanup(self.tmp.cleanup)
        self.root = Path(self.tmp.name) / "root"
        self.root.mkdir()
        (self.root / "old.c").write_bytes(b"old\n")
        self.package = Path(self.tmp.name) / "package"
        P.export(self.package, self.root, {"old.c": None, "nested/new.c": b"new\n"})

    def test_flags_delete_create_and_idempotency(self):
        before = (self.root / "old.c").read_bytes()
        result = P.apply(self.package, self.root, live=True, dry_run=True)
        self.assertEqual(result["status"], "dry-run")
        self.assertEqual((self.root / "old.c").read_bytes(), before)
        self.assertFalse((self.root / "nested").exists())
        with self.assertRaises(ValueError):
            P.apply(self.package, self.root)
        P.apply(self.package, self.root, live=True)
        self.assertFalse((self.root / "old.c").exists())
        self.assertEqual((self.root / "nested/new.c").read_bytes(), b"new\n")
        self.assertEqual(P.apply(self.package, self.root, live=True)["status"], "already-applied")

    def test_stale_guard_prevents_all_writes(self):
        (self.root / "old.c").write_bytes(b"foreign")
        with self.assertRaises(ValueError):
            P.apply(self.package, self.root, live=True)
        self.assertFalse((self.root / "nested").exists())

    def test_payload_tamper_and_symlink_refused(self):
        payload = self.package / "records/nested/new.c"
        payload.write_bytes(b"tampered")
        with self.assertRaises(ValueError):
            P.apply(self.package, self.root, live=True)
        payload.write_bytes(b"new\n")
        (self.root / "nested").symlink_to(self.package, target_is_directory=True)
        with self.assertRaises(ValueError):
            P.apply(self.package, self.root, live=True)
        self.assertTrue((self.root / "old.c").exists())

    def test_partial_application_refused(self):
        (self.root / "nested").mkdir()
        (self.root / "nested/new.c").write_bytes(b"new\n")
        with self.assertRaisesRegex(ValueError, "partially"):
            P.apply(self.package, self.root, live=True)

    def test_failure_rolls_back_all_file_bytes(self):
        original = Path.replace
        def broken(path, destination):
            if Path(destination).name == "new.c":
                raise OSError("injected write failure")
            return original(path, destination)
        with patch.object(Path, "replace", broken):
            with self.assertRaises(OSError):
                P.apply(self.package, self.root, live=True)
        self.assertEqual((self.root / "old.c").read_bytes(), b"old\n")
        self.assertFalse((self.root / "nested/new.c").exists())


if __name__ == "__main__":
    unittest.main()
