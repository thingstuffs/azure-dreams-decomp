"""An explicit include tree wins over the live headers in both verifier compilers."""
import json
import shlex
import subprocess
import sys
import tempfile
import unittest
from pathlib import Path
from types import SimpleNamespace
from unittest import mock

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))
import verify  # noqa: E402


class IncludeRootTests(unittest.TestCase):
    def setUp(self):
        self.tmp = tempfile.TemporaryDirectory()
        self.addCleanup(self.tmp.cleanup)
        self.root = Path(self.tmp.name)
        for name, value in (("live", 1), ("changed", 2)):
            inc = self.root / name
            inc.mkdir()
            (inc / "choice.h").write_text(f"#define CHOICE {value}\n")
        (self.root / "include").symlink_to(self.root / "live")
        self.source = self.root / "candidate.c"
        self.source.write_text('#include "choice.h"\nint chosen = CHOICE;\n')

    def test_overlay_explicit_root_wins_and_none_uses_live(self):
        row = {"func": "func_80000000", "container": "town", "cfg": "2.7.2-G0"}
        real_run = subprocess.run
        seen = []

        def score(command, **kwargs):
            cfg = command[command.index("--configs") + 1]
            flags = shlex.split(cfg)[1:]
            gcc = verify.COMPILERS / "gcc-2.7.2/gcc"
            run = real_run([str(gcc), "-E", "-P", f"-I{self.root / 'include'}", *flags,
                            str(self.source)], capture_output=True, text=True, check=True)
            seen.append(run.stdout.strip())
            best = {"exact": "int chosen = 2;" in run.stdout, "build_status": "ok"}
            record = {"schema": "aligned-score.v1", "results": [{"best": best}]}
            return SimpleNamespace(stdout=json.dumps(record), stderr="")

        with mock.patch.object(verify, "canonical_spelling", side_effect=lambda p: p), \
             mock.patch.object(verify, "gate_root", return_value=self.root), \
             mock.patch.object(verify.subprocess, "run", side_effect=score):
            for spelling in ('"choice.h"', '<choice.h>'):
                self.source.write_text(f"#include {spelling}\nint chosen = CHOICE;\n")
                self.assertFalse(verify.verify_overlay(row, self.source)["exact"])
                self.assertTrue(verify.verify_overlay(row, self.source,
                                                     include_root=self.root / "changed")["exact"])
        self.assertEqual(seen, ["int chosen = 1;", "int chosen = 2;"] * 2)

    def test_slus_compiler_explicit_root_precedes_row_include_flags(self):
        # The real 2.7.2 preprocessor selects the changed header from the same
        # include order _compile_slus_source passes to it.
        row = {"cell": "2.7.2", "flags": f"-I{self.root / 'live'}"}
        gcc = verify.COMPILERS / "gcc-2.7.2/gcc"
        for selected, expected in ((self.root / "live", 1), (self.root / "changed", 2)):
            cmd = [str(gcc), "-E", "-P", "-I", str(selected), *row["flags"].split(),
                   self.source.name]
            got = subprocess.run(cmd, cwd=self.source.parent, capture_output=True, text=True, check=True)
            self.assertIn(f"int chosen = {expected};", got.stdout)

        captured = []

        def fake_run(command, **kwargs):
            captured.append(command)
            return SimpleNamespace(returncode=1, stderr="stopped after command capture", stdout="")

        with mock.patch.object(verify.subprocess, "run", side_effect=fake_run):
            verify._compile_slus_source(row, self.source, self.root / "out", self.root / "changed")
        command = captured[0]
        self.assertLess(command.index("-I"), command.index(row["flags"]))
        self.assertEqual(command[command.index("-I") + 1], str(self.root / "changed"))

    def test_slus_none_keeps_current_and_historical_include_defaults(self):
        import slus_module_context as context
        raw = self.root / "raw.c"
        raw.write_text(self.source.read_text())
        row = {"id": "slus/func_80000000"}
        selected = []

        def compile_one(row, source, outdir, inc):
            selected.append(inc)
            return self.root / "dummy.o", None

        with mock.patch.object(verify, "raw_path", return_value=raw), \
             mock.patch.object(context, "membership", return_value=None), \
             mock.patch.object(context, "compilation_source", side_effect=lambda r, p, o: p), \
             mock.patch.object(verify, "_compile_slus_source", side_effect=compile_one):
            verify.compile_slus(row, self.source, self.root / "out")
            verify.compile_slus(row, raw, self.root / "out")
            verify.compile_slus(row, self.source, self.root / "out", self.root / "changed")
        self.assertEqual(selected, [verify.ROOT / "include", verify.RAW / "include",
                                    (self.root / "changed").resolve()])


if __name__ == "__main__":
    unittest.main()
