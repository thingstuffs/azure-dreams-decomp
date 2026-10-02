import os
import subprocess
import sys
import unittest
from pathlib import Path

from maspsx import MaspsxProcessor

from .util import strip_comments


# func_8004A6C0's cc1 stream (stock 2.7.2): a bare `la` seed, two 0/2-offset loads, +4 self-increment.
BODY = [
    "\tla\t$3,SYM",
    "\tmove\t$6,$0",
    "$L5:",
    "\tlh\t$2,0($3)",
    "\tbne\t$2,$4,$L4",
    "\tlh\t$2,2($3)",
    "\tbeq\t$2,$5,$L3",
    "$L4:",
    "\taddu\t$6,$6,1",
    "\tslt\t$2,$6,20",
    "\tbne\t$2,$0,$L5",
    "\taddu\t$3,$3,4",
    "$L3:",
]


class TestSelfincLaFoldSwitch(unittest.TestCase):
    """r86_opus_selfinc: genuine ASPSX 2.56-2.86 never rewrites a bare `la` into a %hi-only
    self-incremented base with %lo folded into the accesses; the retail shape is cc1's own output
    for integer-address source.  --no-selfinc-la-fold / MASPSX_NO_SELFINC_LA_FOLD=1 (processor:
    fold_selfinc_la=False) skips `_fold_selfinc_la`, leaving the `la` for the assembler to expand
    as ASPSX does."""

    @classmethod
    def setUpClass(cls):
        cls.repo_root = Path(__file__).resolve().parents[1]

    def test_processor_switch_keeps_la(self):
        res = strip_comments(MaspsxProcessor(list(BODY), sdata_limit=8, fold_selfinc_la=False).process_lines())
        self.assertTrue(any(l.startswith("la\t$3,SYM") for l in res))
        self.assertIn("lh\t$2,0($3)", res)
        self.assertIn("lh\t$2,2($3)", res)
        self.assertFalse(any("%lo(SYM" in l for l in res))
        res = strip_comments(MaspsxProcessor(list(BODY), sdata_limit=8, fold_selfinc_la=True).process_lines())
        self.assertIn("lui\t$3,%hi(SYM)", res)
        self.assertIn("lh\t$2,%lo(SYM+2)($3)", res)

    def _run(self, *args, env_value=None):
        env = dict(os.environ)
        env.pop("MASPSX_NO_SELFINC_LA_FOLD", None)
        if env_value is not None:
            env["MASPSX_NO_SELFINC_LA_FOLD"] = env_value
        r = subprocess.run([sys.executable, str(self.repo_root / "maspsx.py"), *args],
                           input="\n".join(["\t.text"] + BODY) + "\n", capture_output=True, text=True, env=env)
        self.assertEqual(r.returncode, 0, r.stderr)
        return r.stdout

    def test_cli_switch(self):
        self.assertNotIn("%lo(SYM+2)", self._run())                            # default: pass skipped
        self.assertIn("%lo(SYM+2)", self._run("--selfinc-la-fold"))              # opt back in
        self.assertIn("%lo(SYM+2)", self._run(env_value="0"))
        self.assertNotIn("%lo(SYM+2)", self._run("--no-selfinc-la-fold"))
        self.assertNotIn("%lo(SYM+2)", self._run(env_value="1"))
