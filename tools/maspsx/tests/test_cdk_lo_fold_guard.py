import importlib.util
import os
import subprocess
import sys
import unittest
from pathlib import Path

from maspsx import MaspsxProcessor

from .util import strip_comments


CDK_BANNER = " # GNU C version cygnus-2.7.2-970404 SN32.3.7.0004 (SonyPSX) compiled by CC."
BODY = [
    "\tlui\t$3,%hi(SYM)",
    "\taddiu\t$3,$3,%lo(SYM)",
    "\tsll\t$2,$4,2",
    "\taddu\t$2,$2,$3",
    "\tsh\t$0,0($2)",
    "\tsh\t$0,2($2)",
]


class TestCdkLoFoldGuard(unittest.TestCase):
    """r85_opus_lofold: genuine ASPSX never folds %lo into accesses; on cdk-cell output the
    fold turns a symbol spelling into the bytes of an integer-address source.  The guard
    (--no-cdk-lo-fold / MASPSX_NO_CDK_LO_FOLD=1) skips `_fold_lo_into_accesses` for a TU
    whose cc1 banner is the cygnus-2.7.2-970404 one, and only for such a TU."""

    @classmethod
    def setUpClass(cls):
        cls.repo_root = Path(__file__).resolve().parents[1]
        spec = importlib.util.spec_from_file_location("maspsx_cli_lofold", cls.repo_root / "maspsx.py")
        cls.cli = importlib.util.module_from_spec(spec)
        spec.loader.exec_module(cls.cli)

    def test_banner_detection(self):
        self.assertTrue(self.cli.cc1_is_cdk([" # -G value = 8, Cpu = 3000, ISA = 1", CDK_BANNER]))
        self.assertFalse(self.cli.cc1_is_cdk([" # GNU C 2.7.2 [AL 1.1, MM 40] Sony Playstation compiled by GNU C"]))
        self.assertFalse(self.cli.cc1_is_cdk(["\t.file\t1 \"x.c\""] + BODY))

    def test_processor_switch_keeps_addiu(self):
        res = strip_comments(MaspsxProcessor(list(BODY), sdata_limit=8, fold_lo_into_accesses=False).process_lines())
        self.assertIn("addiu\t$3,$3,%lo(SYM)", res)
        self.assertIn("sh\t$0,0($2)", res)
        res = strip_comments(MaspsxProcessor(list(BODY), sdata_limit=8).process_lines())
        self.assertNotIn("addiu\t$3,$3,%lo(SYM)", res)

    def _run(self, lines, *args, env_value=None):
        env = dict(os.environ)
        env.pop("MASPSX_NO_CDK_LO_FOLD", None)
        if env_value is not None:
            env["MASPSX_NO_CDK_LO_FOLD"] = env_value
        r = subprocess.run([sys.executable, str(self.repo_root / "maspsx.py"), *args],
                           input="\n".join(lines) + "\n", capture_output=True, text=True, env=env)
        self.assertEqual(r.returncode, 0, r.stderr)
        return r.stdout

    def test_cli_guard_only_on_cdk_output(self):
        cdk = [CDK_BANNER, "\t.text"] + BODY
        other = ["\t.text"] + BODY
        self.assertNotIn("%lo(SYM+2)", self._run(cdk))                           # default: guard active
        self.assertIn("%lo(SYM+2)", self._run(cdk, "--cdk-lo-fold"))              # opt back in
        self.assertIn("%lo(SYM+2)", self._run(cdk, env_value="0"))
        self.assertNotIn("%lo(SYM+2)", self._run(cdk, "--no-cdk-lo-fold"))
        self.assertNotIn("%lo(SYM+2)", self._run(cdk, env_value="1"))
        self.assertIn("%lo(SYM+2)", self._run(other, "--no-cdk-lo-fold"))        # non-cdk cells untouched
