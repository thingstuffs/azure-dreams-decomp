#!/usr/bin/env python3
"""Private lifecycle tests for the active SLUS source exporter.

This file can be copied unchanged to tools/tests/test_slus_partition_export.py.
"""

from __future__ import annotations

import shutil
import subprocess
import tempfile
import unittest
from pathlib import Path


HERE = Path(__file__).resolve().parent
PROJECT = next(p for p in HERE.parents if (p / "tools/build/mk_slus_root.sh").is_file())
CANDIDATE = HERE / "mk_slus_root.sh"
EXPORTER = CANDIDATE if CANDIDATE.is_file() else PROJECT / "tools/build/mk_slus_root.sh"


class ExportFixture(unittest.TestCase):
    def setUp(self) -> None:
        self.temp = tempfile.TemporaryDirectory(prefix="slus_partition_export_")
        self.addCleanup(self.temp.cleanup)
        self.root = Path(self.temp.name)
        script = self.root / "tools/build/mk_slus_root.sh"
        script.parent.mkdir(parents=True)
        script.write_bytes(EXPORTER.read_bytes())
        for path in (
            "toolchain/compilers/gcc-2.7.2/cc1",
            ".venv/bin/splat",
            "baserom/slus_006.14",
            "tools/maspsx/maspsx.py",
        ):
            target = self.root / path
            target.parent.mkdir(parents=True, exist_ok=True)
            target.touch()
        for name in ("raw/slus", "src/slus", "include", "config"):
            (self.root / name).mkdir(parents=True, exist_ok=True)
        for name in (
            "slus_006.14.yaml", "slus_006.14.symbols.txt", "slus_006.14.sha1",
            "names.tsv", "slus_modules.json",
        ):
            (self.root / "config" / name).write_text("fixture\n")
        (self.root / "src/slus/owner.c").write_text(
            '#include "../build/partition_sources/part.c"\n'
            "int cursor_value = CURSOR_VALUE;\n"
        )
        (self.root / "src/slus/other.c").write_text("int other = 1;\n")
        self.export = self.root / "build_slus/src"

    def run_exporter(self, success: bool = True) -> subprocess.CompletedProcess[str]:
        result = subprocess.run(
            ["bash", "tools/build/mk_slus_root.sh"], cwd=self.root,
            capture_output=True, text=True,
        )
        if success:
            self.assertEqual(result.returncode, 0, result.stdout + result.stderr)
        else:
            self.assertNotEqual(result.returncode, 0, result.stdout + result.stderr)
        return result

    def set_plan(self, active: bool) -> None:
        plan = self.root / "config/slus_partitions.json"
        if active:
            plan.write_text('{"version": 1, "parents": []}\n')
        elif plan.exists():
            plan.unlink()

    def assert_source_links(self, *names: str) -> None:
        self.assertTrue(self.export.is_dir())
        self.assertFalse(self.export.is_symlink())
        self.assertEqual({p.name for p in self.export.iterdir() if p.suffix == ".c"}, set(names))
        for name in names:
            entry = self.export / name
            self.assertTrue(entry.is_symlink(), name)
            self.assertEqual(entry.resolve(), (self.root / "src/slus" / name).resolve())


class SlusPartitionExportTests(ExportFixture):
    def test_absent_active_resync_absent_and_relative_include(self) -> None:
        self.run_exporter()
        self.assertTrue(self.export.is_symlink())
        self.assertEqual(self.export.resolve(), (self.root / "src/slus").resolve())

        self.set_plan(True)
        self.run_exporter()
        self.assert_source_links("owner.c", "other.c")
        self.assertTrue((self.root / "build_slus/config/slus_partitions.json").is_symlink())

        part = self.root / "build_slus/build/partition_sources/part.c"
        part.parent.mkdir(parents=True)
        part.write_text("#define CURSOR_VALUE 37\n")
        cc = shutil.which("cc")
        self.assertIsNotNone(cc, "host C preprocessor is required for include-path evidence")
        preprocessed = subprocess.run(
            [cc, "-E", "-P", "-x", "c", str(self.export / "owner.c")],
            cwd=self.root, capture_output=True, text=True,
        )
        self.assertEqual(preprocessed.returncode, 0, preprocessed.stderr)
        self.assertIn("int cursor_value = 37;", preprocessed.stdout)

        (self.root / "src/slus/other.c").unlink()
        (self.root / "src/slus/new.c").write_text("int fresh = 2;\n")
        self.run_exporter()
        self.assert_source_links("owner.c", "new.c")
        self.assertFalse((self.export / "other.c").exists())
        self.assertFalse((self.export / "other.c").is_symlink())

        self.set_plan(False)
        self.run_exporter()
        self.assertTrue(self.export.is_symlink())
        self.assertEqual(self.export.resolve(), (self.root / "src/slus").resolve())
        self.assertFalse((self.root / "build_slus/config/slus_partitions.json").exists())
        self.assertFalse((self.root / "build_slus/config/slus_partitions.json").is_symlink())

    def test_refuses_unmanaged_src_directory_and_preserves_entry(self) -> None:
        self.set_plan(True)
        self.export.mkdir(parents=True)
        unsafe = self.export / "keep.c"
        unsafe.write_text("int must_survive = 9;\n")
        self.run_exporter(success=False)
        self.assertTrue(self.export.is_dir())
        self.assertFalse(self.export.is_symlink())
        self.assertEqual(unsafe.read_text(), "int must_survive = 9;\n")

    def test_refuses_unmanaged_file_inside_managed_src(self) -> None:
        self.set_plan(True)
        self.run_exporter()
        self.assert_source_links("owner.c", "other.c")
        unsafe = self.export / "other.c"
        unsafe.unlink()
        unsafe.write_text("int must_survive = 17;\n")
        self.run_exporter(success=False)
        self.assertEqual(unsafe.read_text(), "int must_survive = 17;\n")
        self.assertFalse(unsafe.is_symlink())

    def test_refuses_retargeted_file_symlink_and_preserves_it(self) -> None:
        self.set_plan(True)
        self.run_exporter()
        unsafe = self.export / "other.c"
        unsafe.unlink()
        outside = self.root / "outside.c"
        outside.write_text("int must_survive = 23;\n")
        unsafe.symlink_to(outside)
        self.run_exporter(success=False)
        self.assertTrue(unsafe.is_symlink())
        self.assertEqual(unsafe.resolve(), outside)
        self.assertEqual(outside.read_text(), "int must_survive = 23;\n")


if __name__ == "__main__":
    unittest.main()
