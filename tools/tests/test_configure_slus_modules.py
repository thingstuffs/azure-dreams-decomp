"""Focused configure.py contracts for optional SLUS C modules."""

import json
import shutil
import subprocess
import tempfile
import unittest
from pathlib import Path


REPO = Path(__file__).resolve().parents[2]
CONFIGURE = REPO / "tools/build/configure.py"
TOOLS = REPO / "tools/build"
MEMBER_STEMS = ("konami_runtime_w_8003C634", "konami_runtime_w_8003C758",
                "konami_runtime_w_8003C920")


class ConfigureSlusModulesTest(unittest.TestCase):
    def setUp(self):
        self.tmp = tempfile.TemporaryDirectory(prefix="configure_slus_modules_")
        self.addCleanup(self.tmp.cleanup)
        self.root = Path(self.tmp.name)
        (self.root / "tools").symlink_to(TOOLS, target_is_directory=True)
        for directory in ("src", "assets", "config/generated", "include/slus", "build"):
            (self.root / directory).mkdir(parents=True, exist_ok=True)
        for stem in MEMBER_STEMS:
            (self.root / f"src/{stem}.c").write_text("/* fixture */\n")
        (self.root / "src/konami_runtime_directory.c").write_text("/* fixture */\n")
        (self.root / "include/slus/runtime_directory.h").write_text("/* fixture */\n")
        (self.root / "assets/54240.bin").write_bytes(b"\x00" * 44 + b"\x04\x00\x00\x00" + b"\x11" * 8)
        (self.root / "build/slus_006.14.ld").write_text(
            "SECTIONS\n{\n  .data : {\n        build/assets/54240.o(.data);\n  }\n}\n")
        (self.root / "config/generated/slus_006.14.undefined_funcs.txt").write_text("")
        (self.root / "config/generated/slus_006.14.undefined_syms.txt").write_text(
            "D_OTHER = 0x80080000;\nD_80080A6C = 0x80080A6C;\n")
        self.module = {
            "name": "runtime_directory", "source": "src/konami_runtime_directory.c",
            "members": [{"id": f"slus/{stem}", "source": f"src/{stem}.c",
                         "functions": [f"func_{stem.rsplit('_', 1)[1]}"]} for stem in MEMBER_STEMS],
            "headers": ["include/slus/runtime_directory.h"],
            "recipe": {"ccver": "2.7.2-cdk", "ccflags": "", "asflags": ""},
            "data": [{"symbol": "D_80080A6C", "asset": "assets/54240.bin", "offset": 44,
                      "size": 4, "vram": 0x80080A6C, "bytes": "04000000", "section": ".sdata"}],
            "evidence": "docs/evidence/runtime_directory.md",
        }

    def manifest(self):
        (self.root / "config/slus_modules.json").write_text(
            json.dumps({"version": 1, "modules": [self.module]}))

    def configure(self, *args, check=True):
        return subprocess.run(("python3", "tools/configure.py", *args), cwd=self.root,
                              capture_output=True, text=True, check=check)

    def test_active_manifest_emits_physical_edges_and_private_link_inputs(self):
        self.manifest()
        self.configure()
        ninja = (self.root / "build.ninja").read_text()
        self.assertIn("build build/src/konami_runtime_directory.o: cc src/konami_runtime_directory.c", ninja)
        for stem in MEMBER_STEMS:
            self.assertNotIn(f"build build/src/{stem}.o: cc", ninja)
            self.assertIn(f"src/{stem}.c", ninja)
        self.assertIn("include/slus/runtime_directory.h config/slus_modules.json", ninja)
        self.assertIn("build build/module_assets/54240_000000_00002C.bin", ninja)
        self.assertIn("build build/module_assets/54240_000030_000038.o: objbin", ninja)
        self.assertNotIn("build build/assets/54240.o: objbin", ninja)
        self.assertIn("--input $out --output $out --out-dir build/module_assets", ninja)
        self.assertIn("-T build/slus_006.14.undefined_syms.modules.txt", ninja)
        self.assertIn("build build/slus_006.14.undefined_syms.modules.txt: module_syms", ninja)
        self.assertIn("| tools/slus_modules.py config/slus_modules.json", ninja)
        self.assertIn("build build/slus_006.14_ordered.ld: orderld build/slus_006.14.ld"
                      " | tools/slus_modules.py config/slus_modules.json assets/54240.bin", ninja)

    @unittest.skipUnless(shutil.which("ninja") and shutil.which("mipsel-linux-gnu-ld"),
                         "Ninja or MIPS binary linker unavailable")
    def test_active_generated_assets_and_scripts_run_without_compiling(self):
        self.manifest()
        self.configure()
        targets = ("build/module_assets/54240_000000_00002C.bin",
                   "build/module_assets/54240_000000_00002C.o",
                   "build/module_assets/54240_000030_000038.o",
                   "build/slus_006.14_ordered.ld", "build/slus_006.14.undefined_syms.modules.txt")
        subprocess.run(("ninja", "-f", "build.ninja", *targets), cwd=self.root,
                       capture_output=True, text=True, check=True)
        self.assertEqual((self.root / targets[0]).read_bytes(), b"\x00" * 44)
        self.assertTrue((self.root / targets[1]).is_file())
        self.assertTrue((self.root / targets[2]).is_file())
        ordered = (self.root / targets[3]).read_text()
        self.assertNotIn("build/assets/54240.o(.data);", ordered)
        self.assertLess(ordered.index("54240_000000_00002C.o(.data)"),
                        ordered.index("konami_runtime_directory.o(.sdata)"))
        self.assertLess(ordered.index("konami_runtime_directory.o(.sdata)"),
                        ordered.index("54240_000030_000038.o(.data)"))
        self.assertEqual((self.root / targets[4]).read_text(), "D_OTHER = 0x80080000;\n")

    def test_recipe_mismatch_and_nm_are_refused(self):
        self.module["recipe"]["ccver"] = "2.8.1"
        self.manifest()
        result = self.configure(check=False)
        self.assertNotEqual(result.returncode, 0)
        self.assertIn("module member recipe differs", result.stderr)
        self.module["recipe"]["ccver"] = "2.7.2-cdk"
        self.module["recipe"]["asflags"] = "--expand-div"
        self.manifest()
        result = self.configure(check=False)
        self.assertNotEqual(result.returncode, 0)
        self.assertIn("module member recipe differs", result.stderr)
        self.module["recipe"]["asflags"] = ""
        self.manifest()
        result = self.configure("--non-matching", check=False)
        self.assertNotEqual(result.returncode, 0)
        self.assertIn("not supported in --non-matching", result.stderr)

    def test_missing_aggregator_member_or_header_is_refused(self):
        self.manifest()
        for path, message in (("src/konami_runtime_directory.c", "aggregator"),
                              (f"src/{MEMBER_STEMS[0]}.c", "member"),
                              ("include/slus/runtime_directory.h", "header")):
            target = self.root / path
            target.rename(target.with_suffix(target.suffix + ".hidden"))
            result = self.configure(check=False)
            self.assertNotEqual(result.returncode, 0)
            self.assertIn(message, result.stderr)
            target.with_suffix(target.suffix + ".hidden").rename(target)

    @unittest.skipUnless((REPO / "build_slus/build.ninja").is_file(), "pinned SLUS build unavailable")
    def test_no_manifest_matches_pinned_ninja_byte_for_byte(self):
        pinned = REPO / "build_slus"
        other = Path(tempfile.mkdtemp(prefix="configure_slus_identity_"))
        self.addCleanup(shutil.rmtree, other)
        for name in ("src", "asm", "assets", "config"):
            (other / name).symlink_to(pinned / name, target_is_directory=True)
        (other / "tools").symlink_to(TOOLS, target_is_directory=True)
        subprocess.run(("python3", "tools/configure.py"), cwd=other,
                       capture_output=True, text=True, check=True)
        self.assertEqual((other / "build.ninja").read_bytes(), (pinned / "build.ninja").read_bytes())


if __name__ == "__main__":
    unittest.main()
