"""tools/fidelity/aspsx_diff.py: the opt-in OLD genuine ASPSX (2.21 = PsyQ 3.3, 2.34 = PsyQ 3.5/3.6) run under dosemu2.
Command construction and absence reporting are mocked; one real assembly runs only where dosemu and the binary exist."""
import os
import shutil
import subprocess
import sys
import tempfile
import unittest
from pathlib import Path
from unittest import mock

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools/fidelity"))
sys.path.insert(0, str(ROOT / "tools"))
import aspsx_diff as A  # noqa: E402
from objread import read_lnk  # noqa: E402


class OldAspsxBase(unittest.TestCase):
    def setUp(self):
        self._env = os.environ.get("AZURE_OLD_ASPSX")
        self._vers = list(A.VERSIONS)
        self.addCleanup(self._restore)

    def _restore(self):
        A.use_old_aspsx("off")
        A.VERSIONS[:] = self._vers
        if self._env is None:
            os.environ.pop("AZURE_OLD_ASPSX", None)
        else:
            os.environ["AZURE_OLD_ASPSX"] = self._env


class Table(OldAspsxBase):
    def test_default_is_wibo_only(self):
        A.use_old_aspsx("off")
        self.assertEqual(A.VERSIONS, ["2.56", "2.67", "2.77", "2.79", "2.81", "2.86"])
        self.assertFalse(set(A.OLD_VERSIONS) & set(A.ASPSX))
        self.assertEqual(sorted(A.OLD_ASPSX), ["2.21", "2.34"])
        self.assertIsNone(A.old_aspsx_record())

    def test_bad_mode_rejected(self):
        with self.assertRaises(ValueError):
            A.use_old_aspsx("maybe")


class Command(OldAspsxBase):
    def test_dosemu_command(self):
        cmd = A.dosemu_command("/t/x", ["-q", "-G0", "-0"])
        self.assertEqual(cmd[:len(A.NICE)], A.NICE)
        self.assertEqual(cmd[len(A.NICE):], [A.DOSEMU, "-dumb", "-K", "/t/x", "-E", "ASPSX.EXE -q -G0 -0 -o OUT.OBJ IN.S"])

    def test_run_builds_command_and_reads_lowercased_object(self):
        with tempfile.TemporaryDirectory() as tmp:
            tmp = Path(tmp)
            exe = tmp / "old" / "psyq3.5/psyq3.5/ASPSX.EXE"
            exe.parent.mkdir(parents=True)
            exe.write_bytes(b"MZ")
            seen = {}

            def fake_run(argv, **kw):
                seen["argv"], seen["kw"] = argv, kw
                d = Path(kw["cwd"])
                seen["files"] = sorted(p.name for p in d.iterdir())
                seen["src"] = (d / "IN.S").read_bytes()
                (d / "out.obj").write_bytes(b"LNK\x02")          # dosemu lowercases DOS names
                return subprocess.CompletedProcess(argv, 0, b"", b"")
            with mock.patch.object(A, "OLD_GENUINE", tmp / "old"), mock.patch.object(A, "TMP", tmp / "rows"), \
                    mock.patch.object(A.shutil, "which", return_value="/usr/bin/dosemu"), \
                    mock.patch.object(A.subprocess, "run", fake_run):
                obj, err = A.run_aspsx(b"\tli\t$2,0\r\n", "2.34", ["-q", "-G0"], str(tmp))
        self.assertEqual((obj, err), (b"LNK\x02", None))
        self.assertEqual(seen["files"], ["ASPSX.EXE", "IN.S"])
        self.assertEqual(seen["src"], b"\tli\t$2,0\r\n")
        self.assertEqual(seen["argv"][-5:-1], ["-dumb", "-K", seen["kw"]["cwd"], "-E"])
        self.assertEqual(seen["argv"][-1], "ASPSX.EXE -q -G0 -o OUT.OBJ IN.S")
        self.assertEqual(seen["kw"]["stdin"], subprocess.DEVNULL)

    def test_no_object_is_an_error_string(self):
        with tempfile.TemporaryDirectory() as tmp:
            tmp = Path(tmp)
            (tmp / "old/psyq3.3/psyq3.3").mkdir(parents=True)
            (tmp / "old/psyq3.3/psyq3.3/ASPSX.EXE").write_bytes(b"MZ")
            out = b"ERROR: /dev/kvm\nIN.S(3) : Error : Syntax error in expression\n"
            with mock.patch.object(A, "OLD_GENUINE", tmp / "old"), mock.patch.object(A, "TMP", tmp / "rows"), \
                    mock.patch.object(A.shutil, "which", return_value="/usr/bin/dosemu"), \
                    mock.patch.object(A.subprocess, "run", lambda argv, **kw: subprocess.CompletedProcess(argv, 0, out, b"")):
                obj, err = A.run_aspsx(b"x", "2.21", [], str(tmp))
        self.assertIsNone(obj)
        self.assertIn("Syntax error", err)
        self.assertNotIn("kvm", err.lower())


class Absence(OldAspsxBase):
    def test_missing_dosemu_and_binary_reported(self):
        with tempfile.TemporaryDirectory() as tmp, mock.patch.object(A, "OLD_GENUINE", Path(tmp)), \
                mock.patch.object(A.shutil, "which", return_value=None):
            why = A.old_aspsx_unavailable()
            self.assertIn("dosemu not found", why)
            self.assertIn("ASPSX 2.21 binary missing", why)
            self.assertIn("ASPSX 2.34 binary missing", why)
            with self.assertRaises(SystemExit) as cm:                 # on: a clear error, never a silent skip
                A.use_old_aspsx("on")
            self.assertIn("dosemu not found", str(cm.exception))
            with self.assertRaises(RuntimeError) as cm:               # the runner itself refuses too
                A.run_aspsx(b"x", "2.34", [], tmp)
            self.assertIn("unavailable", str(cm.exception))

    def test_auto_skips_with_recorded_reason(self):
        with tempfile.TemporaryDirectory() as tmp, mock.patch.object(A, "OLD_GENUINE", Path(tmp)), \
                mock.patch.object(A.shutil, "which", return_value=None):
            st = A.use_old_aspsx("auto")
            self.assertEqual(st["enabled"], [])
            self.assertIn("skipped", st["skipped"])
            self.assertEqual(A.VERSIONS, A.BASE_VERSIONS)             # existing users unaffected
            self.assertEqual(A.old_aspsx_record()["skipped"], st["skipped"])

    def test_on_and_fingerprint_include_binary_sha(self):
        with tempfile.TemporaryDirectory() as tmp:
            tmp = Path(tmp)
            for rel, body in (("psyq3.3/psyq3.3", b"A"), ("psyq3.5/psyq3.5", b"B")):
                (tmp / rel).mkdir(parents=True)
                (tmp / rel / "ASPSX.EXE").write_bytes(body)
            with mock.patch.object(A, "OLD_GENUINE", tmp), mock.patch.object(A.shutil, "which", return_value="/x/dosemu"):
                st = A.use_old_aspsx("on")
                self.assertEqual(st["enabled"], ["2.21", "2.34"])
                self.assertEqual(A.VERSIONS[-2:], ["2.21", "2.34"])
                rec = A.old_aspsx_record()
                self.assertEqual(rec["exe_sha256"]["2.34"], A._sha(b"B"))
                self.assertEqual(os.environ["AZURE_OLD_ASPSX"], "on")


@unittest.skipUnless(shutil.which(A.DOSEMU) and A.old_aspsx_exe("2.34").is_file(),
                     "dosemu or the genuine ASPSX 2.34 binary (toolchain/genuine/psyq_old) is absent")
class RealAssembly(unittest.TestCase):
    def test_expnd_li_is_ori_under_2_34(self):
        """EXPND_LI.S line 1 (`li $2,0`): ASPSX < 2.50 expands to `ori $v0,$zero,0` (0x34020000), >= 2.56 to addiu."""
        with tempfile.TemporaryDirectory() as tmp, mock.patch.object(A, "TMP", Path(tmp)):
            for ver in ("2.21", "2.34"):
                if A.old_aspsx_unavailable(ver):
                    continue
                lnk, err = A.run_aspsx(b"\tli\t$2,0\r\n", ver, ["-q"], tmp)
                self.assertIsNotNone(lnk, err)
                text = read_lnk(lnk).sections[".text"]
                self.assertEqual(int.from_bytes(text[:4], "little"), 0x34020000, ver)


if __name__ == "__main__":
    unittest.main()
