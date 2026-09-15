"""The served-row guard: no pack may re-serve a row a lane already had (round 25's six wasted packs)."""
import sys
import tempfile
import unittest
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / "lanes"))
import served


def fake_root(td, files):
    root = Path(td)
    for rel in files:
        p = root / rel
        p.parent.mkdir(parents=True, exist_ok=True)
        p.write_text("void f(void) {}\n")
    return root


FILES = ["work/native_lane/x/base/c/a.c",
         "work/native_lane/x/base/c/a.c.base_sha",   # not a row: the glob must skip it
         "work/native_lane/y/base/c/a.c",
         "work/native_lane/x/base/c/b.c"]


class ServedRows(unittest.TestCase):
    def test_mapping(self):
        with tempfile.TemporaryDirectory() as td:
            root = fake_root(td, FILES)
            self.assertEqual(served.served_rows(root), {"c/a": ["x", "y"], "c/b": ["x"]})

    def test_empty_root(self):
        with tempfile.TemporaryDirectory() as td:
            self.assertEqual(served.served_rows(Path(td)), {})


class AssertUnserved(unittest.TestCase):
    def test_raises_and_lists_every_overlapping_row(self):
        with tempfile.TemporaryDirectory() as td:
            root = fake_root(td, FILES)
            with self.assertRaises(SystemExit) as cm:
                served.assert_unserved(["c/a", "c/new", "c/b"], root=root)
            msg = str(cm.exception)
            self.assertIn("c/a  x,y", msg)
            self.assertIn("c/b  x", msg)
            self.assertNotIn("c/new", msg)
            self.assertIn("--repack", msg)

    def test_clean_pack_passes(self):
        with tempfile.TemporaryDirectory() as td:
            root = fake_root(td, FILES)
            self.assertEqual(served.assert_unserved(["c/new", "c/other"], root=root), [])

    def test_repack_returns_the_overlap_without_raising(self):
        with tempfile.TemporaryDirectory() as td:
            root = fake_root(td, FILES)
            self.assertEqual(served.assert_unserved(["c/a", "c/new"], repack=True, root=root),
                             [("c/a", ["x", "y"])])

    def test_duplicate_ids_reported_once(self):
        with tempfile.TemporaryDirectory() as td:
            root = fake_root(td, FILES)
            self.assertEqual(served.assert_unserved(["c/a", "c/a"], repack=True, root=root),
                             [("c/a", ["x", "y"])])


if __name__ == "__main__":
    unittest.main()
