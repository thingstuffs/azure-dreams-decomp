"""r81_opus_kitgap: partitioned slus rows in the kit screen/dumps, the noreorder branch mark and `la` token in
`screen.normalise`, and the cellscore cells line.  No compiler is run: compile steps are mocked."""
import contextlib
import json
import sys
import tempfile
import unittest
from pathlib import Path
from types import SimpleNamespace
from unittest import mock

ROOT = next(p for p in Path(__file__).resolve().parents if (p / "tools/common.py").is_file())
for sub in (ROOT / "tools", ROOT / "tools/xform", ROOT / "tools/lanes", ROOT / "tools/lanes/lanekit"):
    sys.path.insert(0, str(sub))

import kitlib  # noqa: E402
import lab  # noqa: E402
import screen  # noqa: E402
import slus_module_context as context  # noqa: E402
import variant_screen  # noqa: E402

ROW = {"id": "slus/w_part", "kind": "slus", "container": "slus", "func": "w_part", "c_path": "src/w_part.c",
       "cfg": "2.7.2-cdk -G32", "cell": "2.7.2-cdk", "flags": "-G32"}


class PartitionedRows(unittest.TestCase):
    def setUp(self):
        self.td = tempfile.TemporaryDirectory(prefix="kitgap_")
        self.addCleanup(self.td.cleanup)
        self.d = Path(self.td.name)

    @contextlib.contextmanager
    def partition(self, units):
        def sources(row, candidate, outdir, *_a, **_k):
            out = []
            for i, (fns, recipe) in enumerate(units):
                f = Path(outdir) / "partition_context" / ("unit%d.c" % i)
                f.parent.mkdir(parents=True, exist_ok=True)
                f.write_text("/* unit %d */\n" % i + Path(candidate).read_text())
                out.append({"source": "src/u%d.c" % i, "recipe": recipe, "functions": fns, "role": "module", "cfile": f})
            return out
        with contextlib.ExitStack() as st:
            st.enter_context(mock.patch.object(context, "partition_context", lambda row, *a, **k: ([{"id": "p"}], [], {})))
            st.enter_context(mock.patch.object(context, "compilation_sources", sources))
            st.enter_context(mock.patch.object(variant_screen, "fingerprint", lambda row, *a, **k: "fp"))
            st.enter_context(mock.patch.object(variant_screen, "compilation_source",
                                               mock.Mock(side_effect=AssertionError("singular path used"))))
            st.enter_context(mock.patch.object(kitlib, "module_fingerprint", lambda row: "fp"))
            yield

    def test_screen_sources_uses_the_plural_context_at_the_unit_recipe(self):
        cand = self.d / "w_part.c"; cand.write_text("int f;\n")
        with self.partition([(["func_part"], {"ccver": "2.7.2-cdk", "ccflags": "-G32", "asflags": ""}),
                             ([], {"ccver": "2.8.1", "ccflags": "", "asflags": ""})]):
            got = variant_screen.screen_sources(ROW, cand, self.d)
        self.assertEqual([(p.name, c) for p, c in got], [("unit0.c", "2.7.2-cdk -G32")])   # empty unit skipped

    def test_screen_listing_compiles_each_unit_with_its_recipe(self):
        seen = []

        def compile_s(row, text):
            seen.append((row["cfg"], text.splitlines()[0]))
            return ["x " + row["cfg"]]
        with self.partition([(["a"], {"ccver": "2.7.2-cdk", "ccflags": "-G32"}), (["b"], {"ccver": "2.8.1", "ccflags": ""})]), \
                mock.patch.object(variant_screen.screen, "compile_s", side_effect=compile_s):
            sc = variant_screen.Screen(ROW, "int f;\n")
            self.assertEqual(sc.target, ["x 2.7.2-cdk -G32", "x 2.8.1"])
            self.assertEqual(sc.distance("int g;\n"), 0)
            self.assertEqual(variant_screen.row_listing(ROW, "int f;\n"), ["x 2.7.2-cdk -G32", "x 2.8.1"])
        self.assertEqual(seen[:2], [("2.7.2-cdk -G32", "/* unit 0 */"), ("2.8.1", "/* unit 1 */")])

    def test_dumps_compile_the_unit_source_from_its_directory(self):
        seen = []

        def fake_run(argv, *, cwd, **_k):
            if "-E" in argv:
                src = Path(cwd) / argv[argv.index("-w") + 1]
                seen.append((src.name, src.read_text().splitlines()[0], " ".join(argv)))
                Path(argv[argv.index("-o") + 1]).write_text("pre\n")
            else:
                (Path(cwd) / "f.s").write_text("asm %d\n" % len(seen))
                (Path(cwd) / "f.i.sched").write_text("sched %d\n" % len(seen))
            return SimpleNamespace(returncode=0, stdout="", stderr="")
        with self.partition([(["a"], {"ccver": "2.7.2-cdk", "ccflags": "-G32"}), (["b"], {"ccver": "2.8.1", "ccflags": ""})]), \
                mock.patch.object(kitlib.subprocess, "run", side_effect=fake_run):
            got = kitlib.dumps(ROW, "int f;\n")
        self.assertIsNone(got["error"])
        self.assertEqual([s[:2] for s in seen], [("unit0.c", "/* unit 0 */"), ("unit1.c", "/* unit 1 */")])
        self.assertIn("gcc-2.7.2-cdk/gcc", seen[0][2])
        self.assertIn("-G32", seen[0][2])
        self.assertIn("gcc-2.8.1/gcc", seen[1][2])
        self.assertEqual(got["asm"], "asm 1\nasm 2\n")
        self.assertEqual(got["sched"], "sched 1\nsched 2\n")

    def test_cfg_trial_on_a_partitioned_row_says_so(self):
        with self.partition([(["a"], {"ccver": "2.7.2-cdk", "ccflags": "-G32"})]):
            with self.assertRaisesRegex(SystemExit, "partitioned slus row"):
                kitlib.row_at_cfg(ROW, "2.8.1")
            with self.assertRaisesRegex(ValueError, "partitioned slus row"):
                variant_screen.Screen(ROW, "int f;\n", cfg="2.8.1")


# cc1 2.91.66 text of dungeon/func_800C379C around the one pin (r80_opus_cl_addiu): the slot filled vs not
FILLED = """\t.ent\tf
\tandi\t$3,$3,0x4000
\t.set\tnoreorder
\t.set\tnomacro
\tbeq\t$3,$0,$L8
\tmove\t$4,$16
\t.set\tmacro
\t.set\treorder
\t.set\tnoreorder
\t.set\tnomacro
\tjal\tfunc_80099734
\tnop
\t.set\tmacro
\t.set\treorder
$L8:
\t.end\tf""".splitlines()
UNFILLED = """\t.ent\tf
\tandi\t$3,$3,0x4000
\tbeq\t$3,$0,$L8
\tmove\t$4,$16
\t.set\tnoreorder
\t.set\tnomacro
\tjal\tfunc_80099734
\tnop
\t.set\tmacro
\t.set\treorder
$L8:
\t.end\tf""".splitlines()
# the abssi2 template closes its region before `subu`, a hand-written negate after the label: same bytes
ABS_TEMPLATE = ["\t.ent\tf", "\t.set\tnoreorder", "\tbgez\t$3,1f", "\tmove\t$19,$3", "\t.set\treorder",
                "\tsubu\t$19,$0,$19", "1:", "\tsubu\t$2,$2,$4", "\t.end\tf"]
ABS_HAND = ["\t.ent\tf", "\t.set\tnoreorder", "\tbgez\t$3,$L24", "\tmove\t$19,$3", "\tsubu\t$19,$0,$19", "$L24:",
            "\t.set\treorder", "\tsubu\t$2,$2,$4", "\t.end\tf"]


class NoreorderAndLa(unittest.TestCase):
    def test_filled_slot_differs_from_unfilled(self):
        self.assertEqual(screen.sdiff(screen.normalise(FILLED), screen.normalise(UNFILLED)), 0)   # the old blind spot
        a, b = screen.normalise(FILLED, keep_reorder=True), screen.normalise(UNFILLED, keep_reorder=True)
        self.assertEqual(screen.sdiff(a, b), 2)
        self.assertIn("beq $3,$0,L0 [nr]", a)
        self.assertIn("jal func_80099734 [nr]", b)

    def test_region_end_is_not_a_difference(self):
        self.assertEqual(screen.sdiff(screen.normalise(ABS_TEMPLATE, keep_reorder=True),
                                      screen.normalise(ABS_HAND, keep_reorder=True)), 0)

    def test_residue_fingerprint_ignores_marks_but_names_a_slot_only_residue(self):
        import residue
        a, b = screen.normalise(FILLED, keep_reorder=True), screen.normalise(UNFILLED, keep_reorder=True)
        fp = residue.fingerprint(a, b)
        self.assertEqual((fp["cls"], fp["band"], fp["shape"]), ("SLOT", "1-2", "-beq +beq"))
        old = residue.fingerprint(screen.normalise(ABS_TEMPLATE), screen.normalise(ABS_HAND))
        new = residue.fingerprint(screen.normalise(ABS_TEMPLATE, keep_reorder=True),
                                  screen.normalise(ABS_HAND, keep_reorder=True))
        self.assertEqual(old, new)

    def test_break_is_not_a_branch(self):
        out = screen.normalise(["\t.ent\tf", "\t.set\tnoreorder", "\tbreak\t7", "\t.set\treorder", "\t.end\tf"],
                               keep_reorder=True)
        self.assertEqual(out, [".ent", "break 7"])

    def test_la_token(self):
        la = ["\t.ent\tf", "\tla\t$8,D_8002744C", "\t.end\tf"]
        split = ["\t.ent\tf", "\tlui\t$8,%hi(D_8002744C)", "\taddiu\t$8,$8,%lo(D_8002744C)", "\t.end\tf"]
        self.assertEqual(screen.sdiff(screen.normalise(la), screen.normalise(split)), 0)
        self.assertEqual(screen.normalise(la, la_token=True), [".ent", "la $8,0x8002744C"])
        self.assertEqual(screen.sdiff(screen.normalise(la, la_token=True), screen.normalise(split, la_token=True)), 3)
        self.assertEqual(screen.normalise(["\t.ent\tf", "\tla\t$8,D_80027440+12", "\t.end\tf"], la_token=True),
                         [".ent", "la $8,0x8002744C"])

    def test_defaults_and_environment(self):
        row = {"cfg": "2.7.2-cdk-G0"}
        with mock.patch.dict("os.environ", {}, clear=False):
            for k in ("SCREEN_KEEP_REORDER", "SCREEN_LA_TOKEN"):
                __import__("os").environ.pop(k, None)
            self.assertEqual(screen.options_for(row), ("*" in screen.REORDER_CELLS or "2.7.2-cdk" in screen.REORDER_CELLS,
                                                       screen.LA_TOKEN))
            with mock.patch.dict("os.environ", {"SCREEN_KEEP_REORDER": "0", "SCREEN_LA_TOKEN": "1"}):
                self.assertEqual(screen.options_for(row), (False, True))
            self.assertEqual(screen.options_for(row, keep_reorder=True, la_token=False), (True, False))


class CellscoreLine(unittest.TestCase):
    def test_cellscore_line_carries_the_kind(self):
        pinned, cand = "int a; /* KEEP */\n", "int a;\n"
        verify = lambda row, f, include_root=None, diff=False: {"exact": True, "total": 0, "status": "ok"}  # noqa: E731
        with tempfile.TemporaryDirectory() as td:
            row = {"id": "dungeon/func_80000000", "container": "dungeon", "c_path": "src/dungeon/func_80000000.c",
                   "cfg": "2.8.1-G0", "cell": "2.8.1", "flags": "-G0", "kind": "overlay"}
            rec = lab.cellscore(row, cand, "2.7.2-cdk-G0", td, base=pinned, verify=verify, out=lambda *a: None)
        line = json.loads(rec["cells_line"])
        self.assertEqual((line["kind"], line["rule2"]), ("recipe-switch", True))


class RowCensus(unittest.TestCase):
    def test_census_map_and_summary(self):
        import io
        from contextlib import redirect_stdout
        import row_census as RC
        with tempfile.TemporaryDirectory() as td:
            d = Path(td)
            (d / "c.jsonl").write_text(json.dumps({"container": "dungeon", "module": "m.c", "best_recipe": "2.7.2-cdk-G0"}) + "\n")
            (d / "m.jsonl").write_text(json.dumps({"id": "dungeon/func_1", "container": "dungeon", "module": "m.c"}) + "\n"
                                       + json.dumps({"id": "dungeon/func_2", "container": "dungeon", "module": "x.c"}) + "\n")
            with mock.patch.object(RC, "CENSUS", d / "c.jsonl"), mock.patch.object(RC, "MODULES", d / "m.jsonl"), \
                    mock.patch.dict(RC._CACHE, {}, clear=True):
                self.assertEqual(RC.census_map(), {"dungeon/func_1": ("m.c", "2.7.2-cdk-G0")})
            recs = [{"id": "dungeon/func_1", "pins": 2, "cfg": "2.8.1-G0", "census_cfg": "2.7.2-cdk-G0",
                     "at": {"2.8.1-G0": {"exact": False, "total": 3, "classes": {"ORDER": 1, "COLOUR": 2, "OPCODE": 0, "COUNT": 0}},
                            "2.7.2-cdk-G0": {"exact": True, "total": 0}}, "pinned_at_census": {"exact": True, "total": 0}},
                    {"id": "dungeon/func_3", "pins": 1, "cfg": "2.7.2-cdk-G0", "census_cfg": None,
                     "at": {"2.7.2-cdk-G0": {"exact": False, "total": None, "err": "jtbl: local .rodata ..."}}}]
            (d / "o.jsonl").write_text("".join(json.dumps(r) + "\n" for r in recs))
            buf = io.StringIO()
            with redirect_stdout(buf):
                RC.summary(d / "o.jsonl")
        out = buf.getvalue()
        self.assertIn("'1-4': 1", out)
        self.assertIn("'jtbl-mismatch': 1", out)
        self.assertIn("closer at the module census recipe: 1", out)
        self.assertIn("pinned exact there: True", out)


if __name__ == "__main__":
    unittest.main()
