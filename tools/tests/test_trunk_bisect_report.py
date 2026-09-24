"""tools/fidelity/trunk_bisect_report.py: the retail-exact verdict (gated on the scorer-exact maspsx leg), the
compiled test, the pin detector and the label ordering, on synthetic journal records."""
import sys
import unittest
from pathlib import Path
from unittest import mock

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools/fidelity"))
import trunk_bisect_report as T  # noqa: E402


def rec(exact=True, maspsx=True, status="ok", tag="psyq", same=False, err=None):
    r = {"row": "x/func_1", "status": status, "maspsx_exact": maspsx,
         "res": {tag: {"2.79": {"exact": exact, "diff": 0 if exact else 3}}}}
    if same:
        r["res"][tag]["same_as_input"] = True
    if err:
        r["psyq_err"] = err
    return r


class Exact(unittest.TestCase):
    def test_exact_needs_scorer_exact_maspsx_leg(self):
        self.assertTrue(T.exact(rec()))
        # genuine == maspsx but the maspsx leg is not retail: never counted (the trial-cell trap)
        self.assertFalse(T.exact(rec(maspsx=False)))
        self.assertFalse(T.exact(rec(maspsx=None)))

    def test_not_exact_and_errors(self):
        self.assertFalse(T.exact(rec(exact=False)))
        self.assertFalse(T.exact(rec(status="error")))
        self.assertFalse(T.exact({}))
        self.assertFalse(T.exact(None))

    def test_same_as_input_marker_ignored(self):
        self.assertTrue(T.exact(rec(tag="psyq_t272", same=True), "psyq_t272"))
        self.assertFalse(T.exact(rec(tag="psyq_t272"), "psyq"))

    def test_compiled(self):
        self.assertTrue(T.compiled(rec()))
        self.assertFalse(T.compiled(rec(err="gcc: cc1: Invalid option `-fno-gcse'")))
        self.assertFalse(T.compiled(rec(status="error")))
        self.assertFalse(T.compiled({"status": "ok", "res": {"base": {}}}))


class Pinned(unittest.TestCase):
    def check(self, text):
        T.PIN = {"_by": {"x/f": {"id": "x/f"}}, "_cp": lambda r: "unused"}
        with mock.patch.object(Path, "read_text", return_value=text):
            return T.pinned("x/f")

    def test_pin_macros_and_asm(self):
        self.assertTrue(self.check("void f(void) { int v; ASM_KEEP(v); }"))
        self.assertTrue(self.check("register int v ASM_REG(\"$2\");"))
        self.assertTrue(self.check("__asm__ volatile(\"\");"))
        self.assertTrue(self.check("asm (\"\" : : \"r\"(x));"))

    def test_plain_c_is_pin_free(self):
        self.assertFalse(self.check("int f(int asmx) { return asmx + ASMLIKE; }"))

    def tearDown(self):
        T.PIN = None


class Order(unittest.TestCase):
    def test_labels_sort_by_svn_revision_with_cdk_first(self):
        labs = ["r14410", "rel280", "cdk", "r13838noeh", "r13838", "r9999"]
        self.assertEqual(sorted(labs, key=T.order_key), ["cdk", "r9999", "r13838", "r13838noeh", "r14410", "rel280"])


if __name__ == "__main__":
    unittest.main()
