"""Grouped SLUS rows retain their module context in lane diagnostics."""

import contextlib
import json
import sys
import tempfile
import unittest
from pathlib import Path
from types import SimpleNamespace
from unittest import mock

ROOT = Path(__file__).resolve().parents[2]
for sub in (ROOT / "tools", ROOT / "tools/xform", ROOT / "tools/lanes/lanekit"):
    sys.path.insert(0, str(sub))

import kitlib  # noqa: E402
import lab  # noqa: E402
import slus_module_context as context  # noqa: E402
import variant_screen  # noqa: E402


class ModuleLaneTest(unittest.TestCase):
    def setUp(self):
        self.tmp = tempfile.TemporaryDirectory(prefix="slus_module_lanes_")
        self.addCleanup(self.tmp.cleanup)
        self.root = Path(self.tmp.name)
        for directory in ("src/slus", "include", "config"):
            (self.root / directory).mkdir(parents=True)
        self.member = "int func_a(void) { return shared; }\n"
        (self.root / "src/slus/row_a.c").write_text(self.member)
        (self.root / "src/slus/row_b.c").write_text("int func_b(void) { return shared + 1; }\n")
        (self.root / "src/slus/group.c").write_text(
            '#include "shared.h"\nint shared = 4;\n#include "row_a.c"\n#include "row_b.c"\n')
        (self.root / "include/shared.h").write_text("extern int shared;\n")
        manifest = {"version": 1, "modules": [{
            "name": "group", "source": "src/group.c",
            "members": [{"id": "slus/row_a", "source": "src/row_a.c", "functions": ["func_a"]},
                        {"id": "slus/row_b", "source": "src/row_b.c", "functions": ["func_b"]}],
            "headers": ["include/shared.h"],
            "recipe": {"ccver": "2.7.2", "ccflags": "", "asflags": ""},
            "data": [], "evidence": "docs/evidence/group.md",
        }]}
        (self.root / "config/slus_modules.json").write_text(json.dumps(manifest))
        self.row = {"id": "slus/row_a", "kind": "slus", "container": "slus", "func": "row_a",
                    "c_path": "src/row_a.c", "cfg": "2.7.2", "cell": "2.7.2", "flags": ""}

    @contextlib.contextmanager
    def module_context(self):
        originals = {name: getattr(context, name) for name in
                     ("membership", "fingerprint", "compilation_source", "require_individual_recipe")}

        def member(row, *_args, **_kwargs):
            return originals["membership"](row, root=self.root)

        def fp(row, *_args, **_kwargs):
            return originals["fingerprint"](row, root=self.root)

        def compile_source(row, candidate, outdir, *_args, **_kwargs):
            return originals["compilation_source"](row, candidate, outdir, root=self.root)

        def require(row, *_args, **_kwargs):
            return originals["require_individual_recipe"](row, root=self.root)

        with contextlib.ExitStack() as stack:
            for name, function in (("membership", member), ("fingerprint", fp),
                                   ("compilation_source", compile_source),
                                   ("require_individual_recipe", require)):
                stack.enter_context(mock.patch.object(context, name, function))
            for name, function in (("fingerprint", fp), ("compilation_source", compile_source),
                                   ("require_individual_recipe", require)):
                stack.enter_context(mock.patch.object(variant_screen, name, function))
            yield

    def test_listing_compiles_aggregator_with_siblings_and_detects_stale_context(self):
        seen = []

        def compile_listing(row, text):
            seen.append(text)
            return ["normalised listing"]

        with self.module_context(), mock.patch.object(variant_screen.screen, "compile_s", side_effect=compile_listing):
            screen = variant_screen.Screen(self.row, self.member)
            self.assertEqual(screen.distance(self.member.replace("shared;", "shared + 2;")), 0)
            self.assertEqual(len(seen), 2)
            for source in seen:
                self.assertIn("int shared = 4;", source)
                self.assertIn('row_b.c"', source)
                self.assertIn("row_a.c", source)
            (self.root / "src/slus/row_b.c").write_text("int func_b(void) { return shared + 2; }\n")
            with self.assertRaisesRegex(RuntimeError, "module context changed"):
                screen.listing(self.member)

    def test_rtl_dump_preprocesses_module_wrapper_but_ungrouped_keeps_f_c(self):
        seen = []

        def fake_run(argv, *, cwd, **_kwargs):
            cwd = Path(cwd)
            if "-E" in argv:
                source = cwd / argv[argv.index("-w") + 1]
                seen.append((source.name, source.read_text()))
                (cwd / "f.i").write_text("preprocessed\n")
            else:
                (cwd / "f.s").write_text("assembly\n")
            return SimpleNamespace(returncode=0, stdout="", stderr="")

        with self.module_context(), mock.patch.object(kitlib.subprocess, "run", side_effect=fake_run):
            got = kitlib.dumps(self.row, self.member)
            self.assertEqual(got["asm"], "assembly\n")
            self.assertEqual(seen[0][0], "group.c")
            self.assertIn("int shared = 4;", seen[0][1])
            self.assertIn("row_b.c", seen[0][1])
            ordinary = dict(self.row, id="dungeon/func_a", container="dungeon", kind="overlay")
            kitlib.dumps(ordinary, self.member)
            self.assertEqual(seen[1], ("f.c", self.member))

    def test_rtl_dump_refuses_context_changed_during_preprocessing(self):
        def fake_run(argv, *, cwd, **_kwargs):
            if "-E" in argv:
                (self.root / "include/shared.h").write_text("extern int shared; /* changed */\n")
                (Path(cwd) / "f.i").write_text("preprocessed\n")
            return SimpleNamespace(returncode=0, stdout="", stderr="")

        with self.module_context(), mock.patch.object(kitlib.subprocess, "run", side_effect=fake_run):
            got = kitlib.dumps(self.row, self.member)
        self.assertIn("module context changed", got["error"])

    def test_cross_recipe_refused_before_scoring(self):
        with self.module_context():
            with self.assertRaisesRegex(ValueError, "change the module recipe"):
                kitlib.row_at_cfg(self.row, "2.8.1")
            with self.assertRaisesRegex(ValueError, "change the module recipe"):
                variant_screen.Screen(self.row, self.member, cfg="2.8.1")
            with mock.patch.object(kitlib, "score_at", side_effect=AssertionError("scorer called")):
                with self.assertRaisesRegex(ValueError, "change the module recipe"):
                    lab.cellscore(self.row, self.member, "2.8.1", self.root)
            ordinary = dict(self.row, id="dungeon/func_a", kind="overlay")
            self.assertEqual(kitlib.row_at_cfg(ordinary, "2.8.1")["cell"], "2.8.1")

    def test_log_identity_and_publication_refuse_changed_context(self):
        with self.module_context():
            fp = kitlib.module_fingerprint(self.row)
            instance = lab.Lab.__new__(lab.Lab)
            instance.lane, instance.id, instance.row = self.root, self.row["id"], self.row
            instance.context_fingerprint = fp
            instance.log({"variant": "candidate", "status": "measured"})
            records = kitlib.log_read(self.root)
            self.assertEqual(records[0]["module_fingerprint"], fp)
            kitlib.log_append(self.root, {"row": self.row["id"], "variant": "older",
                                          "module_fingerprint": "stale"})
            self.assertEqual(kitlib.variant_count(kitlib.log_read(self.root), self.row["id"]), 2)
            self.assertEqual(instance.count(), 2)
            (self.root / "include/shared.h").write_text("extern int shared; /* changed */\n")
            with self.assertRaisesRegex(RuntimeError, "remeasure before publication"):
                instance.publish("candidate", self.member)
            self.assertFalse((self.root / "out").exists())


if __name__ == "__main__":
    unittest.main()
