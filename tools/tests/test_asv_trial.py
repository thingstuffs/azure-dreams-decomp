"""tools/fidelity/asv_trial.py: the maspsx version -> behaviour table it relies on, its attribution and
verdict classifiers, the static predictor, and (when GNU as is installed) one synthetic positive control
per version-gated behaviour, run through the real tools/maspsx."""
import hashlib
import shutil
import subprocess
import sys
import tempfile
import unittest
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools/fidelity"))
sys.path.insert(0, str(ROOT / "tools"))
import asv_trial as T  # noqa: E402

HEAD = "\t.text\n\t.align\t2\n\t.globl\tf\n\t.ent\tf\nf:\n\t.frame\t$sp,0,$31\n"
TAIL = "\tj\t$31\n\t.end\tf\n"
# one construct per version-gated behaviour
SLTU = HEAD + "\tsltu\t$2,$4,-5\n" + TAIL                                        # sltu_at      (2.60)
COMM = "\t.comm\tD_c,8\n" + HEAD + "\tlw\t$2,0($4)\n\tsw\t$2,D_c+4\n" + TAIL     # gp_allow_offset (2.7x)
LA = "\t.extern\tD_e, 4\n" + HEAD + "\tla\t$5,D_e\n\tsw\t$0,D_e\n" + TAIL         # gp_allow_la  (2.8x)


class VersionTable(unittest.TestCase):
    def test_277_equals_279(self):
        self.assertEqual(T.version_config("2.77"), T.version_config("2.79"))

    def test_deltas(self):
        self.assertEqual(set(T.config_delta("2.56", "2.79")), {"sltu_at", "gp_allow_offset"})
        self.assertEqual(set(T.config_delta("2.56", "2.60")), {"sltu_at"})
        self.assertEqual(set(T.config_delta("2.79", "2.81")), {"gp_allow_la"})
        self.assertEqual(set(T.config_delta("2.40", "2.56")), {"expand_li"})
        self.assertEqual(T.config_delta("2.34", "2.40"), {})


class Classifiers(unittest.TestCase):
    def test_attribution(self):
        A = T.attribute_change
        self.assertEqual(A({"2.60": False, "2.77": False, "2.79": False, "2.81": False}), "none")
        self.assertEqual(A({"2.60": True, "2.79": True, "2.81": True}), "sltu_at")
        self.assertEqual(A({"2.60": False, "2.79": True, "2.81": True}), "gp_allow_offset")
        self.assertEqual(A({"2.60": False, "2.79": False, "2.81": True}), "gp_allow_la")
        self.assertEqual(A({"2.60": True, "2.79": False, "2.81": False}), "sltu_at+non-monotone@2.79")

    def test_verdicts(self):
        V = T.verdict_class
        self.assertEqual(V(True, True, None), "same")
        self.assertEqual(V(True, False, True), "changed-exact")
        self.assertEqual(V(True, False, False), "stops-matching")
        self.assertEqual(V(False, False, True), "starts-matching")
        self.assertEqual(V(False, False, False), "changed-nonexact")

    def test_predictor(self):
        self.assertEqual(T.predict(SLTU), {"sltu_neg": 1, "comm_off": 0, "la_small": 0})
        self.assertEqual(T.predict(COMM), {"sltu_neg": 0, "comm_off": 1, "la_small": 0})
        self.assertEqual(T.predict(LA), {"sltu_neg": 0, "comm_off": 0, "la_small": 1})

    def test_swap_keeps_row_dial(self):
        args = ["--aspsx-version=2.56", "--dont-force-G0", "-I.", "-I.", "-EL", "-march=r3000", "-G8",
                "--aspsx-version=2.40"]
        self.assertEqual(T.swap_version(args, "2.79")[0], "--aspsx-version=2.79")
        self.assertEqual(T.swap_version(args, "2.79")[-1], "--aspsx-version=2.40")
        self.assertNotIn("--aspsx-version=2.40", T.drop_dial(args, "2.79"))


@unittest.skipUnless(shutil.which("mipsel-linux-gnu-as") and (ROOT / ".venv/bin/python").exists(), "GNU as / venv")
class PositiveControls(unittest.TestCase):
    def sha(self, src, ver):
        with tempfile.TemporaryDirectory() as td:
            o = Path(td) / "o.o"
            subprocess.run([str(ROOT / ".venv/bin/python"), str(ROOT / "tools/maspsx/maspsx.py"),
                            f"--aspsx-version={ver}", "--dont-force-G0", "--run-assembler",
                            "--gnu-as-path=mipsel-linux-gnu-as", "-EL", "-march=r3000", "-G8", "-o", str(o)],
                           input=src, text=True, capture_output=True, check=True)
            return hashlib.sha256(o.read_bytes()).hexdigest()

    def moved(self, src):
        s = {v: self.sha(src, v) for v in ("2.56", "2.60", "2.77", "2.79", "2.81")}
        self.assertEqual(s["2.77"], s["2.79"])
        return T.attribute_change({v: s[v] != s["2.56"] for v in ("2.60", "2.79", "2.81")})

    def test_each_behaviour_moves_its_object(self):
        self.assertEqual(self.moved(SLTU), "sltu_at")
        self.assertEqual(self.moved(COMM), "gp_allow_offset")
        self.assertEqual(self.moved(LA), "gp_allow_la")


if __name__ == "__main__":
    unittest.main()
