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


def tier_lane(root, name, rows, model=None, launched=True, cluster=None):
    d = Path(root) / "work/native_lane" / name
    for rid, text in rows.items():
        c, n = rid.split("/")
        (d / "base" / c).mkdir(parents=True, exist_ok=True)
        (d / "base" / c / (n + ".c")).write_text(text)
    if launched:
        (d / "codex.log").write_text(("model: %s\n" % model) if model else "")
    if cluster:
        import json
        (d / "cluster.json").write_text(json.dumps(cluster))
    return d


def sha(t):
    import hashlib
    return hashlib.sha256(t.encode()).hexdigest()


class TierServed(unittest.TestCase):
    """Round 76: the guard keyed on (tier, kit era, text sha, scope) instead of 'ever served'."""

    def setUp(self):
        served._CACHE.clear()
        served._RECS.clear()

    def test_tier_from_model_or_lane_name(self):
        with tempfile.TemporaryDirectory() as td:
            self.assertEqual(served.lane_tier(tier_lane(td, "r73_opus_s1", {"c/a": "x"}, "claude-opus-5-5[1m]"))[0], "opus")
            self.assertEqual(served.lane_tier(tier_lane(td, "r73_opus_s11_arms", {"c/a": "x"}, launched=False))[0], "opus")
            self.assertEqual(served.lane_tier(tier_lane(td, "r74_sol6v3_a1", {"c/a": "x"}, "gpt-6-sol"))[0], "sol6")
            self.assertEqual(served.lane_tier(tier_lane(td, "r70_kit_astra1", {"c/a": "x"}))[0], "astra")

    def test_same_tier_same_text_refused_other_tier_or_text_passes(self):
        with tempfile.TemporaryDirectory() as td:
            tier_lane(td, "r73_astra_a1", {"c/a": "old", "c/b": "cur-b"}, "gpt-6-astra")
            tier_lane(td, "r73_luna6_a1", {"c/c": "cur-c"}, "gpt-6-luna")
            tier_lane(td, "r73_astra_x9", {"c/d": "cur-d"}, "gpt-6-astra", launched=False)   # never ran
            texts = {"c/a": sha("new"), "c/b": sha("cur-b"), "c/c": sha("cur-c"), "c/d": sha("cur-d")}
            ids = ["c/a", "c/b", "c/c", "c/d"]
            with self.assertRaises(SystemExit) as cm:
                served.assert_unserved(ids, root=Path(td), mode="tier", tier="astra", texts=texts)
            self.assertIn("c/b  r73_astra_a1", str(cm.exception))
            self.assertNotIn("c/a", str(cm.exception))        # text changed since: a new experiment
            self.assertNotIn("c/d", str(cm.exception))        # built, never launched: served no model
            with self.assertRaises(SystemExit):
                served.assert_unserved(["c/c"], root=Path(td), mode="tier", tier="luna6", texts=texts)
            self.assertEqual(served.assert_unserved(["c/c"], root=Path(td), mode="tier", tier="opus", texts=texts), [])
            self.assertEqual(served.assert_unserved(ids, root=Path(td), mode="tier", tier="astra", texts=texts,
                                                    repack=True), [("c/b", ["r73_astra_a1"])])
            with self.assertRaises(SystemExit):                # the old notion is still there and stricter
                served.assert_unserved(["c/a"], root=Path(td), mode="ever")
            self.assertEqual(served.assert_unserved(["c/a"], root=Path(td), mode="off"), [])

    def test_cluster_scope_is_part_of_the_key(self):
        with tempfile.TemporaryDirectory() as td:
            tier_lane(td, "r75_astra_p1", {"c/big": "T"}, "gpt-6-astra")              # whole function
            tier_lane(td, "r76_astra_k1", {"c/big": "T"}, "gpt-6-astra",
                      cluster={"c/big": {"sites": [[10, "ASM_REG", "$4"], [12, "ASM_KEEP", "x"]]}})
            texts = {"c/big": sha("T")}
            k1 = served.cluster_scope([[12, "ASM_KEEP", "x"], [10, "ASM_REG", "$4"]])
            k2 = served.cluster_scope([[30, "ASM_KEEP", "y"]])
            with self.assertRaises(SystemExit):                # same cluster, same tier, same text
                served.assert_unserved(["c/big"], root=Path(td), mode="tier", tier="astra", texts=texts,
                                       scopes={"c/big": k1})
            self.assertEqual(served.assert_unserved(["c/big"], root=Path(td), mode="tier", tier="astra",
                                                    texts=texts, scopes={"c/big": k2}), [])

    def test_strong_kit_pool(self):
        with tempfile.TemporaryDirectory() as td:
            tier_lane(td, "r73_opus_s1", {"c/a": "A", "c/b": "B-old"}, "claude-opus-5-5[1m]")
            tier_lane(td, "r60_astra_q1", {"c/c": "C"}, "gpt-6-astra")                # pre-kit era
            tier_lane(td, "r73_sol6_a1", {"c/d": "D"}, "gpt-6-sol")                   # not a strong tier
            texts = {"c/a": (sha("A"), 3, "dungeon"), "c/b": (sha("B"), 9, "dungeon"), "c/c": (sha("C"), 1, "town"),
                     "c/d": (sha("D"), 2, "town"), "c/e": (sha("E"), 0, "town"), "c/f": (sha("F"), 4, "ovmovie")}
            pool = {p["row"]: p for p in served.strong_kit_pool(Path(td), texts)}
            self.assertEqual(sorted(pool), ["c/b", "c/c", "c/d"])
            self.assertEqual(pool["c/b"]["status"], "older-text")
            self.assertEqual(pool["c/b"]["band"], "8+")
            self.assertEqual(pool["c/c"]["status"], "never")
            self.assertEqual(served.band_of(3), "3-7")


if __name__ == "__main__":
    unittest.main()
