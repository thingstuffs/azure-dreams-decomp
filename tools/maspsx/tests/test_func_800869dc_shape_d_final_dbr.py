import os
import tempfile
import unittest
from unittest import mock

from maspsx import MaspsxProcessor


CALLER = "func_8008C13C"
CALLEE = "func_8008C438"
SITE0 = "0x80086C28"


def marker_body(marker=True, target=CALLEE, delay="nop"):
    lines = [".ent\tfunc_8008C13C"]
    if marker:
        lines.append(f"#maspsx_shape_d_pin {CALLER},{SITE0},{CALLEE}")
    lines += [f"jal\t{target}", delay, "addu\t$4,$18,$zero",
              "jal\tfunc_8009F644", "nop", ".end\tfunc_8008C13C"]
    return lines


class TestFunc800869dcShapeDFinalDbr(unittest.TestCase):
    def processor(self):
        processor = MaspsxProcessor([])
        processor.sibcall_syms = frozenset((CALLEE,))
        return processor

    def test_marker_authenticates_and_retains_delay(self):
        result = self.processor()._rewrite_marked_shape_d_sibcall(
            marker_body(delay="sw\t$2,140($19)"))
        self.assertIn("j\tfunc_8008C438\t# maspsx: marked SHAPE-D jal->j", result)
        self.assertEqual(result[3], "sw\t$2,140($19)")

    def test_marker_missing_or_wrong_target_fails_closed(self):
        processor = self.processor()
        self.assertIn("jal\tfunc_8008C438",
                      processor._rewrite_marked_shape_d_sibcall(
                          marker_body(marker=False)))
        self.assertIn("jal\tfunc_8009F644",
                      processor._rewrite_marked_shape_d_sibcall(
                          marker_body(target="func_8009F644")))

    def test_sidecar_duplicate_and_bad_rows_fail_closed(self):
        with tempfile.NamedTemporaryFile(mode="w", delete=False) as stream:
            stream.write(f"{CALLER} {SITE0} {CALLEE}\n")
            stream.write(f"{CALLER} {SITE0} {CALLEE}\n")
            path = stream.name
        try:
            with mock.patch.dict(os.environ,
                                 {"MASPSX_SHAPE_D_MANIFEST": path}, clear=False):
                processor = MaspsxProcessor([])
                self.assertEqual(processor.shape_d_manifest, ())
        finally:
            os.unlink(path)


if __name__ == "__main__":
    unittest.main()
