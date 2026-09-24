"""tools/verify.py rebaseline_slus: re-derive the slus reference of named rows from the LANDED src at the LANDED
recipe, only when the SLUS gate proved that object (fidelity step 4, part A2).

Fixture: slus/w_8005A1D0 - a 39-word .word paste landed as C at 2.7.2-cdk (ca253080).  Its cached reference was
built from the raw .word text, so verify_slus reads the landed C as `length-drift` although the SLUS SHA-1 gate
matches.  Every test works on a COPY of the cache (verify.CACHE is pointed at a temp dir); ledger/cache is never
written.

    python3 -m unittest tools/tests/test_verify_rebaseline_slus.py
"""
import hashlib, json, os, shutil, sys, tempfile, time, unittest
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))
import verify  # noqa: E402
from common import rows, clean_path  # noqa: E402

ROW = "slus/w_8005A1D0"
REAL_CACHE = ROOT / "ledger/cache"


def cache_state():
    fs = [REAL_CACHE / "slus_obj.json", REAL_CACHE / "slus_dis/w_8005A1D0.txt"]
    return {str(f): hashlib.sha256(f.read_bytes()).hexdigest() for f in fs if f.exists()}


class RebaselineTests(unittest.TestCase):
    def setUp(self):
        self.real = cache_state()
        self.d = Path(tempfile.mkdtemp(prefix="rebase_slus_"))
        self.cache = self.d / "cache"; (self.cache / "slus_dis").mkdir(parents=True)
        shutil.copy(REAL_CACHE / "slus_obj.json", self.cache / "slus_obj.json")
        for f in (REAL_CACHE / "slus_dis").glob("w_8005A*.txt"):
            shutil.copy(f, self.cache / "slus_dis" / f.name)
        self.old = verify.CACHE
        verify.CACHE = self.cache; verify._slus_base = None
        self.row = {r["id"]: r for r in rows()}[ROW]

    def tearDown(self):
        verify.CACHE = self.old; verify._slus_base = None
        shutil.rmtree(self.d, ignore_errors=True)
        self.assertEqual(cache_state(), self.real, "ledger/cache changed")

    def landed_verdict(self):
        verify._slus_base = None
        return verify.verify_slus(self.row, clean_path(self.row).resolve(), include_root=ROOT / "include")

    def test_landed_row_reads_stale_before_and_exact_after(self):
        if not (ROOT / "build_slus/build/src/w_8005A1D0.o").exists():
            self.skipTest("no gated build_slus tree")
        self.assertFalse(self.landed_verdict().get("exact"))
        res = verify.rebaseline_slus([ROW], cache=self.cache)
        self.assertEqual([r["outcome"] for r in res], ["rebaselined"], res)
        v = self.landed_verdict()
        self.assertTrue(v.get("exact"), v)
        ent = json.load(open(self.cache / "slus_obj.json"))[ROW]
        self.assertEqual(ent["rebaselined"]["cfg"], self.row["cfg"])
        self.assertIn("gate_at", ent["rebaselined"])

    def test_dry_run_writes_nothing(self):
        before = {p.name: p.read_bytes() for p in self.cache.rglob("*") if p.is_file()}
        res = verify.rebaseline_slus([ROW], cache=self.cache, dry_run=True)
        self.assertEqual(res[0]["outcome"], "dry-run", res)
        self.assertEqual({p.name: p.read_bytes() for p in self.cache.rglob("*") if p.is_file()}, before)

    def test_refused_without_a_matching_gate(self):
        g = self.d / "gate.jsonl"
        recs = [json.loads(l) for l in (ROOT / "ledger/gate_slus.jsonl").read_text().splitlines() if l.strip()]
        g.write_text(json.dumps(dict(recs[-1], result="NO MATCH")) + "\n")
        res = verify.rebaseline_slus([ROW], cache=self.cache, gate_log=g)
        self.assertEqual(res[0]["outcome"], "refused"); self.assertIn("NO MATCH", res[0]["detail"])
        g.write_text(json.dumps(dict(recs[-1], recipe_vs_pinned="DIFFERS")) + "\n")
        self.assertEqual(verify.rebaseline_slus([ROW], cache=self.cache, gate_log=g)[0]["outcome"], "refused")

    def test_refused_when_the_pinned_recipe_moved_after_the_gate(self):
        p = self.d / "pinned.ninja"
        p.write_text((ROOT / "ledger/splits/slus.build.ninja").read_text() + "\n# changed\n")
        res = verify.rebaseline_slus([ROW], cache=self.cache, pinned=p)
        self.assertEqual(res[0]["outcome"], "refused"); self.assertIn("recipe", res[0]["detail"])

    def _build_root(self, obj_from):
        b = self.d / "b"; (b / "build/src").mkdir(parents=True)
        shutil.copy(ROOT / "build_slus/build.ninja", b / "build.ninja")
        shutil.copy(obj_from, b / "build/src/w_8005A1D0.o")
        time.sleep(0.01)
        (b / "build/slus_006.14.ok").write_text("")
        return b

    def test_refused_when_the_gated_object_is_not_the_landed_text(self):
        other = ROOT / "build_slus/build/src/w_8005A26C.o"
        if not other.exists():
            self.skipTest("no gated build_slus tree")
        res = verify.rebaseline_slus([ROW], cache=self.cache, build_root=self._build_root(other))
        self.assertEqual(res[0]["outcome"], "refused"); self.assertIn("not the object the gate linked", res[0]["detail"])

    def test_refused_when_the_object_is_newer_than_the_sha1_stamp(self):
        gobj = ROOT / "build_slus/build/src/w_8005A1D0.o"
        if not gobj.exists():
            self.skipTest("no gated build_slus tree")
        b = self._build_root(gobj)
        t = time.time()
        os.utime(b / "build/slus_006.14.ok", (t - 100, t - 100))
        res = verify.rebaseline_slus([ROW], cache=self.cache, build_root=b)
        self.assertEqual(res[0]["outcome"], "refused"); self.assertIn("sha1 stamp", res[0]["detail"])

    def test_refused_for_an_overlay_row(self):
        res = verify.rebaseline_slus(["town/func_8032DE74"], cache=self.cache)
        self.assertEqual(res[0]["outcome"], "refused")


if __name__ == "__main__":
    unittest.main()
