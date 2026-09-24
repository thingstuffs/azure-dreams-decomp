"""tools/fidelity/land_recipe_move.py - the step-4 recipe-move lander (overlay AND slus rows) - and its isolated
SLUS link (tools/fidelity/slus_iso.py).

Every landing test runs the lander against a THROWAWAY copy of the tree (--root / Lander(root=...)): the ledger
tables, the split tables, tools/build/configure.py, the pinned slus recipe and the touched src files are copies;
build_slus/ is a view whose tools/ and src/ point into the copy.  The gates are replaced by LAND_MOVE_GATE_OVL /
LAND_MOVE_GATE_SLUS (`true` = MATCH, `false` = NO MATCH).  Each test asserts the real tree is untouched.

    python3 -m unittest tools/tests/test_land_recipe_move.py
"""
import hashlib, json, os, shutil, subprocess, sys, tempfile, unittest
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools")); sys.path.insert(0, str(ROOT / "tools/fidelity"))
import land_recipe_move as L  # noqa: E402
from slus_iso import set_tu_recipe  # noqa: E402
from common import sha_text, read_jsonl  # noqa: E402

OVL_ROW = "town/func_8032DE74"          # registered 2.7.2 (non-splitting), module census 2.7.2-cdk-G0
SLUS_ROW = "slus/w_8005A1D0"            # registered 2.7.2-cdk (landed ca253080); exact at 2.8.1 as well
REAL_FILES = ["ledger/rows.jsonl", "ledger/recipe_trades.jsonl", "ledger/splits/town.jsonl", "ledger/splits/slus.jsonl",
              "ledger/splits/slus.build.ninja", "tools/build/configure.py", "src/town/func_8032DE74.c",
              "src/slus/w_8005A1D0.c", "build_slus/build.ninja"]


def real_state():
    return {f: hashlib.sha256((ROOT / f).read_bytes()).hexdigest() for f in REAL_FILES if (ROOT / f).exists()}


def make_tree():
    """A throwaway tree the lander can write: copies of every file it touches, symlinks for the rest."""
    T = Path(tempfile.mkdtemp(prefix="recipe_move_"))
    (T / "ledger/splits").mkdir(parents=True)
    for f in ("rows.jsonl", "recipe_trades.jsonl", "gate_slus.jsonl"):
        shutil.copy(ROOT / "ledger" / f, T / "ledger" / f)
    for f in ("town.jsonl", "slus.jsonl", "slus.build.ninja"):
        shutil.copy(ROOT / "ledger/splits" / f, T / "ledger/splits" / f)
    (T / "src/town").mkdir(parents=True)
    shutil.copy(ROOT / "src/town/func_8032DE74.c", T / "src/town/func_8032DE74.c")
    (T / "src/slus").mkdir(parents=True)
    for f in (ROOT / "src/slus").iterdir():
        if f.name == "w_8005A1D0.c":
            shutil.copy(f, T / "src/slus" / f.name)
        else:
            (T / "src/slus" / f.name).symlink_to(f)
    (T / "tools/build").mkdir(parents=True)
    for f in (ROOT / "tools/build").iterdir():
        if f.name == "configure.py":
            shutil.copy(f, T / "tools/build" / f.name)
        elif f.name != "__pycache__":
            (T / "tools/build" / f.name).symlink_to(f)
    b = T / "build_slus"; b.mkdir()
    for d in ("asm", "assets"):
        (b / d).symlink_to(ROOT / "build_slus" / d)
    shutil.copytree(ROOT / "build_slus/config", b / "config", symlinks=True)
    (b / "src").symlink_to(T / "src/slus")
    (b / "tools").symlink_to(T / "tools/build")
    (b / "include").symlink_to(ROOT / "include")
    shutil.copy(ROOT / "build_slus/build.ninja", b / "build.ninja")
    return T


def stage(T, entries):
    """A lane dir with out/ + cells.jsonl: entries [(row_id, to, text or None=current)]."""
    lane = T / "lane"
    for rid, to, text in entries:
        c, n = rid.split("/")
        cur = (T / "src" / c / (n + ".c")).read_text()
        p = lane / "out" / c / (n + ".c"); p.parent.mkdir(parents=True, exist_ok=True)
        p.write_text(text if text is not None else cur)
        p.with_name(p.name + ".base_sha").write_text(sha_text(cur) + "\n")
    with open(lane / "cells.jsonl", "w") as f:
        for rid, to, _t in entries:
            f.write(json.dumps({"id": rid, "to": to, "coherence": "test", "evidence": {"census_recipe": "retail-proven"}}) + "\n")
    return lane


def exact_stub(result=True, rule2=True):
    def ov(row, text, cfg):
        return {"exact": result if text != (ROOT / "src" / row["container"] / Path(row["c_path"]).name).read_text() else rule2}
    def sl(changes):
        return {"result": "MATCH" if result else "NO MATCH", "detail": ""}
    return ov, sl


class PureTextTests(unittest.TestCase):
    CFG = 'x = 1\nCC_VER = {\n    "src/a.c": ("2.8.1", ""),\n    "src/b.c": ("2.7.2", "-G0"),\n}\nDEFAULT_CC = ("2.7.2", "")\n'

    def test_set_cc_ver_replaces_the_tus_line(self):
        out = L.set_cc_ver(self.CFG, "b", "2.7.2-cdk", "-G0", "note")
        self.assertIn('"src/b.c": ("2.7.2-cdk", "-G0"),  # note', out)
        self.assertEqual(out.count('"src/b.c"'), 1)
        self.assertIn('"src/a.c": ("2.8.1", ""),', out)

    def test_set_cc_ver_adds_a_line_for_a_default_tu(self):
        out = L.set_cc_ver(self.CFG, "c", "2.7.2-cdk", "", "note")
        lines = out.split("\n")
        self.assertEqual(lines[lines.index("}") - 1], '    "src/c.c": ("2.7.2-cdk", ""),  # note')

    def test_set_cc_ver_refuses_a_duplicate_entry(self):
        with self.assertRaises(ValueError):
            L.set_cc_ver(self.CFG.replace('"src/a.c"', '"src/b.c"'), "b", "2.8.1", "", "n")

    NINJA = ("build build/src/a.o: cc src/a.c | tools/cc.sh\n  ccver = 2.7.2\n  ccflags = \n  asflags = \n\n"
             "build build/src/b.o: cc src/b.c | tools/cc.sh\n  ccver = 2.8.1\n  ccflags = -G0\n  asflags = \n")

    def test_recipe_diff_only_on_the_moved_tus_lines(self):
        new = set_tu_recipe(self.NINJA, "a", "2.7.2-cdk", "-G0")
        self.assertEqual(L.recipe_diff_ok(self.NINJA, new, {"a"}), [])
        self.assertTrue(L.recipe_diff_ok(self.NINJA, new, {"b"}))                     # a changed but b was moved
        self.assertTrue(L.recipe_diff_ok(self.NINJA, new.replace("asflags = \n\nbuild", "asflags = x\n\nbuild"), {"a"}))
        self.assertTrue(L.recipe_diff_ok(self.NINJA, new + "build extra: cc x\n", {"a"}))

    def test_set_tu_recipe_needs_a_cc_edge(self):
        with self.assertRaises(ValueError):
            set_tu_recipe(self.NINJA, "zz", "2.8.1", "")

    def test_edges_diff(self):
        from row_db import edges_of
        a = edges_of(self.NINJA); b = edges_of(set_tu_recipe(self.NINJA, "b", "2.7.2-cdk", ""))
        self.assertEqual(L.edges_diff_ok(a, b, {"b"}), [])
        self.assertTrue(L.edges_diff_ok(a, b, {"a"}))

    def test_target_must_split(self):
        self.assertTrue(L.splits("2.7.2-cdk-G0"))
        self.assertTrue(L.splits("2.8.1 -G0"))
        self.assertFalse(L.splits("2.7.2-cdk -mmips-as -G0"))
        self.assertFalse(L.splits("2.7.2"))


class LanderTests(unittest.TestCase):
    def setUp(self):
        self.real = real_state()
        self.T = make_tree()
        self.env = {k: os.environ.get(k) for k in ("LAND_MOVE_GATE_OVL", "LAND_MOVE_GATE_SLUS")}

    def tearDown(self):
        for k, v in self.env.items():
            if v is None: os.environ.pop(k, None)
            else: os.environ[k] = v
        shutil.rmtree(self.T, ignore_errors=True)
        self.assertEqual(real_state(), self.real, "the real tree changed")

    def tree_state(self):
        out = {}
        for p in sorted(self.T.rglob("*")):
            # Imported build helpers may create disposable Python bytecode; rollback
            # must restore source/recipe/ledger state, not delete interpreter caches.
            if p.is_file() and not p.is_symlink() and not {"lane", "build_ovl", "__pycache__"}.intersection(p.parts):
                out[str(p.relative_to(self.T))] = hashlib.sha256(p.read_bytes()).hexdigest()
        return out

    def lander(self, lane, **kw):
        logs = []
        ov, sl = kw.pop("stubs", exact_stub())
        return L.Lander(self.T, "t", lane, round_="test", verify_overlay=ov, verify_slus=sl, log=lambda *a: logs.append(" ".join(map(str, a)))), logs

    def test_dry_run_writes_nothing(self):
        cur = (self.T / "src/town/func_8032DE74.c").read_text()
        lane = stage(self.T, [(OVL_ROW, "2.7.2-cdk-G0", cur + "\n/* cand */\n"), (SLUS_ROW, "2.8.1", None)])
        before = self.tree_state()
        lz, logs = self.lander(lane)
        res = lz.run(apply=False)
        self.assertEqual(sorted(res["plan"]), sorted([OVL_ROW, SLUS_ROW]))
        self.assertEqual(self.tree_state(), before)

    def test_apply_switches_both_row_kinds_and_records_trades(self):
        os.environ["LAND_MOVE_GATE_OVL"] = "true"; os.environ["LAND_MOVE_GATE_SLUS"] = "true"
        cur = (self.T / "src/town/func_8032DE74.c").read_text()
        cand = cur + "\n/* cand */\n"
        lane = stage(self.T, [(OVL_ROW, "2.7.2-cdk-G0", cand), (SLUS_ROW, "2.8.1", None)])
        pinned0 = (self.T / "ledger/splits/slus.build.ninja").read_text()
        cfg0 = (self.T / "tools/build/configure.py").read_text()
        trades0 = len(read_jsonl(self.T / "ledger/recipe_trades.jsonl"))
        lz, logs = self.lander(lane, stubs=exact_stub(True, rule2=False))
        res = lz.run(apply=True)
        self.assertEqual(sorted(res["moved"]), sorted([OVL_ROW, SLUS_ROW]), logs)
        rows = {r["id"]: r for r in read_jsonl(self.T / "ledger/rows.jsonl")}
        self.assertEqual((rows[OVL_ROW]["cfg"], rows[OVL_ROW]["cell"], rows[OVL_ROW]["flags"]), ("2.7.2-cdk-G0", "2.7.2-cdk", "-G0"))
        self.assertEqual((rows[SLUS_ROW]["cfg"], rows[SLUS_ROW]["cell"], rows[SLUS_ROW]["flags"]), ("2.8.1", "2.8.1", ""))
        split = [r for r in read_jsonl(self.T / "ledger/splits/town.jsonl") if r.get("func_vram") == "func_8032DE74"]
        self.assertEqual(split[0]["config"], "2.7.2-cdk-G0")
        # the recipe: configure.py changed on the TU's line only; the pinned copy only on its ccver line
        import difflib
        d = [l for l in difflib.unified_diff(cfg0.splitlines(), (self.T / "tools/build/configure.py").read_text().splitlines(), n=0, lineterm="")
             if l[:1] in "+-" and not l.startswith(("+++", "---"))]
        self.assertEqual(len(d), 2, d); self.assertIn('"src/w_8005A1D0.c": ("2.8.1", "")', d[1])
        pinned = (self.T / "ledger/splits/slus.build.ninja").read_text()
        self.assertEqual(L.recipe_diff_ok(pinned0, pinned, {"w_8005A1D0"}), [])
        self.assertNotEqual(pinned0, pinned)
        self.assertEqual(pinned, (self.T / "build_slus/build.ninja").read_text())
        edge = [e for e in read_jsonl(self.T / "ledger/splits/slus.jsonl") if e["src"] == "src/w_8005A1D0.c"][0]
        self.assertEqual((edge["ccver"], edge["ccflags"]), ("2.8.1", ""))
        self.assertEqual((self.T / "src/town/func_8032DE74.c").read_text(), cand)
        trades = read_jsonl(self.T / "ledger/recipe_trades.jsonl")[trades0:]
        self.assertEqual({t["id"]: t["kind"] for t in trades}, {OVL_ROW: "coherence", SLUS_ROW: "recipe-switch"})
        self.assertEqual({t["id"]: (t["cfg_from"], t["cfg_to"]) for t in trades},
                         {OVL_ROW: ("2.7.2", "2.7.2-cdk-G0"), SLUS_ROW: ("2.7.2-cdk", "2.8.1")})
        j = read_jsonl(self.T / "ledger/sweeps/recipe_move_t.jsonl")
        self.assertEqual({r["id"]: r["outcome"] for r in j}, {OVL_ROW: "applied", SLUS_ROW: "noop"})

    def test_gate_failure_restores_everything(self):
        os.environ["LAND_MOVE_GATE_OVL"] = "true"; os.environ["LAND_MOVE_GATE_SLUS"] = "false"
        cur = (self.T / "src/town/func_8032DE74.c").read_text()
        lane = stage(self.T, [(OVL_ROW, "2.7.2-cdk-G0", cur + "\n/* cand */\n"), (SLUS_ROW, "2.8.1", None)])
        before = self.tree_state()
        lz, logs = self.lander(lane)
        res = lz.run(apply=True)
        self.assertEqual(res["moved"], [])
        self.assertIn("SLUS gate failed", res["failed"])
        self.assertEqual(self.tree_state(), before)

    def test_overlay_gate_failure_restores_too(self):
        os.environ["LAND_MOVE_GATE_OVL"] = "false"
        cur = (self.T / "src/town/func_8032DE74.c").read_text()
        lane = stage(self.T, [(OVL_ROW, "2.7.2-cdk-G0", cur + "\n/* cand */\n")])
        before = self.tree_state()
        lz, logs = self.lander(lane)
        res = lz.run(apply=True)
        self.assertIn("overlay window gate failed", res["failed"])
        self.assertEqual(self.tree_state(), before)

    def test_refusals_before_any_write(self):
        cur = (self.T / "src/town/func_8032DE74.c").read_text()
        lane = stage(self.T, [(OVL_ROW, "2.7.2-cdk-G0", cur + "\n/* cand */\n")])
        # stale: the row changed after the candidate was cut
        (self.T / "src/town/func_8032DE74.c").write_text(cur + "\n")
        lz, logs = self.lander(lane)
        self.assertEqual(lz.plan(), [])
        self.assertTrue(any("skip stale" in l for l in logs), logs)
        (self.T / "src/town/func_8032DE74.c").write_text(cur)
        # a non-splitting target
        lane = stage(self.T, [(OVL_ROW, "2.8.1-G0 -mno-split-addresses", cur + "\n/* c */\n")])
        lz, logs = self.lander(lane)
        self.assertEqual(lz.plan(), [])
        self.assertTrue(any("not a stock splitting" in l for l in logs), logs)
        # not exact at the target
        lane = stage(self.T, [(OVL_ROW, "2.7.2-cdk-G0", cur + "\n/* c */\n")])
        lz, logs = self.lander(lane, stubs=exact_stub(False))
        self.assertEqual(lz.plan(), [])
        self.assertTrue(any("not exact at target" in l for l in logs), logs)


class RealVerifyTests(unittest.TestCase):
    """The lander's own verification on real bytes (no stubs), dry run only."""

    def setUp(self):
        self.real = real_state(); self.T = make_tree()

    def tearDown(self):
        shutil.rmtree(self.T, ignore_errors=True)
        self.assertEqual(real_state(), self.real, "the real tree changed")

    def test_slus_recipe_switch_verified_by_isolated_link(self):
        # w_8005A1D0's landed C links retail-exact at 2.8.1 too (step-4 measurement): a byte-neutral switch
        lane = stage(self.T, [(SLUS_ROW, "2.8.1", None)])
        logs = []
        lz = L.Lander(self.T, "t", lane, round_="test", log=lambda *a: logs.append(" ".join(map(str, a))))
        plan = lz.plan()
        self.assertEqual([p[1]["id"] for p in plan], [SLUS_ROW], logs)
        self.assertTrue(plan[0][4])                                   # rule 2 holds: text unchanged

    def test_slus_candidate_not_exact_is_refused(self):
        cur = (self.T / "src/slus/w_8005A1D0.c").read_text()
        broken = cur.replace("{", "{ volatile int zz = 1; (void)zz;", 1) if "{" in cur else cur
        lane = stage(self.T, [(SLUS_ROW, "2.8.1", broken)])
        logs = []
        lz = L.Lander(self.T, "t", lane, round_="test", log=lambda *a: logs.append(" ".join(map(str, a))))
        self.assertEqual(lz.plan(), [])
        self.assertTrue(any("not exact at target" in l for l in logs), logs)


if __name__ == "__main__":
    unittest.main()
