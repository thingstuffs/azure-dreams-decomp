"""Flag-off identity pin for the shared MASPSX CLI.

All eight authenticated MAIN per-function closures are gone: seven went on
2026-09-07 with the rest of the dial family (bridge burn-down Phase 2), and
the last one -- the func_8000F774 preloop dial -- went the same day (Phase 2d)
once its row was re-landed at a stock cell.  maspsx has no per-function option
left, so nothing here may name a function again.

What survives is general: with no flags at all, the CLI must turn a real
main-EXE first-pass fixture into one pinned byte stream.
"""

from __future__ import annotations

import hashlib
import os
from pathlib import Path
import subprocess
import sys
import unittest


HERE = Path(__file__).resolve().parent
ROOT = HERE.parents[2]
SHARED = ROOT / "toolchain/maspsx/maspsx.py"
FIXTURE = HERE / "fixtures/firstpass_80011390_2.7.2.gcc.s"   # gcc 2.7.2 -S output of main-EXE func_80011390 (vendored)

os.environ.setdefault("MASPSX_SIBCALL_FILE", str(ROOT / "config/sibcall_syms.txt"))
os.environ.setdefault("MASPSX_NORETURN_FILE", str(ROOT / "config/noreturn_syms.txt"))
sys.path.insert(0, str(HERE.parent))

from maspsx import MaspsxProcessor  # noqa: E402


class CombinedIntegrationTests(unittest.TestCase):
    def test_cli_offers_no_per_function_option(self):
        # The CLI surface itself is the assertion: no `--retail-*` dial and no
        # function name may appear in it again.  (`parse_known_args` forwards
        # anything unknown to gnu-as, so --help is the honest check.)
        run = subprocess.run(
            [sys.executable, str(SHARED), "--help"], cwd=ROOT, text=True,
            stdout=subprocess.PIPE, stderr=subprocess.PIPE,
        )
        self.assertEqual(run.returncode, 0, run.stderr)
        self.assertNotIn("--retail", run.stdout)
        self.assertNotIn("func_", run.stdout)
        # ...while every general, name-free option is still offered.
        for opt in ("--expand-div", "--macro-inc", "--dont-expand-li",
                    "--preserve-casesi-at", "--preserve-return-delay",
                    "--fill-shadowed-return-delay", "--retain-tail-frame",
                    "--allow-noreturn-epilogue", "--preserve-live-sibcall-tail",
                    "--prefer-target-arg-setup",
                    "--preserve-immediate-funcaddr-la", "--aspsx-version"):
            self.assertIn(opt, run.stdout, opt)

    def test_aggregate_flag_off_identity(self):
        raw = FIXTURE.read_bytes()
        env = os.environ.copy()
        shared = subprocess.run(
            [sys.executable, str(SHARED), "--force-stdin"], cwd=ROOT,
            input=raw, stdout=subprocess.PIPE, stderr=subprocess.PIPE, env=env,
        )
        combined = subprocess.run(
            [sys.executable, str(SHARED), "--force-stdin"], cwd=ROOT,
            input=raw, stdout=subprocess.PIPE, stderr=subprocess.PIPE, env=env,
        )
        self.assertEqual(shared.returncode, 0, shared.stderr.decode())
        self.assertEqual(combined.returncode, 0, combined.stderr.decode())
        self.assertEqual(combined.stdout, shared.stdout)
        self.assertEqual(
            hashlib.sha256(combined.stdout).hexdigest(),
            "9e5c2f3f4a469228c91b1dc7baef59961227db693ece943a71d7ddb8230f753b",   # golden output; the fixture's .file path was neutralised when vendored (the directive passes through)
        )


if __name__ == "__main__":
    unittest.main()
