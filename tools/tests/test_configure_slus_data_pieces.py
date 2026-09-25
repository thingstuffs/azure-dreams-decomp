"""Configure contracts for opt-in named SLUS data-piece objects."""

from __future__ import annotations

import json
import shutil
import subprocess
import sys
import tempfile
import unittest
from pathlib import Path


ROOT = Path(__file__).resolve().parents[2]
BUILD_TOOLS = ROOT / "tools/build"
sys.path[:0] = [str(ROOT / "tools"), str(BUILD_TOOLS)]
import slus_modules  # noqa: E402
from row_db import edges_of  # noqa: E402


ASM = """.set noreorder
.text
.globl func_8003E758
.ent func_8003E758
func_8003E758:
lw $2,%gp_rel(D_DATA)($28)
jr $31
nop
.end func_8003E758
.sdata
.globl D_DATA
.type D_DATA,@object
D_DATA: .byte 1,2,3,4
.size D_DATA,4
"""


class ConfigureSlusDataPiecesTest(unittest.TestCase):
    def setUp(self):
        self.tmp = tempfile.TemporaryDirectory(prefix="configure_slus_pieces_")
        self.addCleanup(self.tmp.cleanup)
        self.root = Path(self.tmp.name)
        for directory in ("tools", "src", "assets", "config", "input"):
            (self.root / directory).mkdir()
        for tool in ("configure.py", "slus_modules.py", "slus_partitions.py",
                     "slus_data_pieces.py"):
            shutil.copy2(BUILD_TOOLS / tool, self.root / "tools" / tool)
        (self.root / "tools/ccproc.py").touch()
        # The graph uses its normal cc edge. The fixture's cc driver supplies a
        # real GNU MIPS relocatable object so the production split CLI can run.
        cc = self.root / "tools/cc.sh"
        cc.write_text('#!/bin/sh\nset -eu\nmkdir -p "$(dirname "$2")"\n'
                      'cp input/owned.o "$2"\n')
        cc.chmod(0o755)
        for source in ("tiny_owner", "w_8003E758", "ordinary"):
            (self.root / f"src/{source}.c").write_text("/* graph fixture */\n")
        (self.root / "assets/54240.bin").write_bytes(b"abcd" + bytes.fromhex("01020304") + b"ijkl")
        self.module = {
            "name": "tiny_owner", "source": "src/tiny_owner.c",
            "members": [{"id": "slus/w_8003E758", "source": "src/w_8003E758.c",
                         "functions": ["func_8003E758"]}],
            "headers": [],
            "recipe": {"ccver": "2.7.2-cdk",
                       "ccflags": "-G32", "asflags": ""},
            "data": [], "evidence": "docs/evidence/tiny_owner.md",
        }

    def manifest(self):
        (self.root / "config/slus_modules.json").write_text(
            json.dumps({"version": 1, "modules": [self.module]}))

    def configure(self) -> str:
        result = subprocess.run((sys.executable, "tools/configure.py"), cwd=self.root,
                                capture_output=True, text=True)
        self.assertEqual(result.returncode, 0, result.stdout + result.stderr)
        return (self.root / "build.ninja").read_text()

    def test_legacy_module_keeps_original_cc_rule_and_edges(self):
        self.manifest()
        ninja = self.configure()
        self.assertIn('rule cc\n  command = tools/cc.sh $in $out $ccver '
                      '"$ccflags" "$asflags"\n  description = CC $in '
                      '(gcc $ccver $ccflags $asflags)\n', ninja)
        self.assertNotIn("data_piece_step", ninja)
        self.assertNotIn("data_piece_verify", ninja)
        physical = edges_of(ninja)
        self.assertEqual(physical, [
            {"src": "src/ordinary.c", "out": "build/src/ordinary.o",
             "ccver": "2.7.2", "ccflags": "", "asflags": ""},
            {"src": "src/tiny_owner.c", "out": "build/src/tiny_owner.o",
             "ccver": "2.7.2-cdk", "ccflags": "-G32",
             "asflags": ""},
        ])
        self.assertEqual(slus_modules.logical_edges(physical, [self.module]), [
            physical[0],
            {"src": "src/w_8003E758.c", "out": "build/src/w_8003E758.o",
             "ccver": "2.7.2-cdk", "ccflags": "-G32",
             "asflags": ""},
        ])

    def test_named_carve_slots_preserve_every_gap(self):
        module = {"name": "pieces", "source": "src/tiny_owner.c",
                  "data": [
                      {"symbol": "D_FIRST", "asset": "assets/54240.bin", "offset": 1,
                       "size": 1, "vram": 0x80080001, "bytes": "62",
                       "section": ".sdata.D_FIRST"},
                      {"symbol": "D_SECOND", "asset": "assets/54240.bin", "offset": 4,
                       "size": 2, "vram": 0x80080004, "bytes": "0102",
                       "section": ".sdata.D_SECOND"},
                  ],
                  "data_pieces": [
                      {"symbol": "D_FIRST", "source_section": ".sdata", "alignment": 1},
                      {"symbol": "D_SECOND", "source_section": ".sdata", "alignment": 2},
                  ]}
        plan = slus_modules.plan_asset_carves([module], root=self.root)[0]
        slots = plan["slots"]
        self.assertEqual([(s["kind"], s["start"], s["end"]) for s in slots],
                         [("chunk", 0, 1), ("module_data", 1, 2),
                          ("chunk", 2, 4), ("module_data", 4, 6),
                          ("chunk", 6, 12)])
        self.assertEqual([s["section"] for s in slots if s["kind"] == "module_data"],
                         [".sdata.D_FIRST", ".sdata.D_SECOND"])
        rewritten = slus_modules.rewrite_ordered_linker_script(
            "  build/assets/54240.o(.data);\n", [plan])
        for slot in slots:
            self.assertIn(f"{slot['object']}({slot['section']});", rewritten)
        raw = (self.root / "assets/54240.bin").read_bytes()
        for chunk in slus_modules.materialize_asset_chunks([plan], root=self.root):
            self.assertEqual((self.root / chunk["input"]).read_bytes(),
                             raw[chunk["start"]:chunk["end"]])

    @unittest.skipUnless(shutil.which("ninja") and shutil.which("mipsel-linux-gnu-as"),
                         "Ninja or GNU MIPS assembler unavailable")
    def test_opted_edge_transforms_and_missing_sidecar_fails_verification(self):
        (self.root / "input/owned.s").write_text(ASM)
        assembled = subprocess.run(("mipsel-linux-gnu-as", "-EL", "-march=r3000", "-G8",
                                    "-o", "input/owned.o", "input/owned.s"),
                                   cwd=self.root, capture_output=True, text=True)
        self.assertEqual(assembled.returncode, 0, assembled.stdout + assembled.stderr)
        self.manifest()
        legacy_physical = edges_of(self.configure())
        legacy_logical = slus_modules.logical_edges(legacy_physical, [self.module])
        self.module["data"] = [{
            "symbol": "D_DATA", "asset": "assets/54240.bin", "offset": 4,
            "size": 4, "vram": 0x80080004, "bytes": "01020304",
            "section": ".sdata.D_DATA"}]
        self.module["data_pieces"] = [{"symbol": "D_DATA", "source_section": ".sdata",
                                      "alignment": 4}]
        self.manifest()
        ninja = self.configure()
        owner = "build/src/tiny_owner.o"
        stamp = "build/src/tiny_owner.data-pieces.ok"
        owner_edge = ninja.split(f"build {owner}: cc ", 1)[1].split("\n\n", 1)[0]
        other_edge = ninja.split("build build/src/ordinary.o: cc ", 1)[1].split("\n\n", 1)[0]
        self.assertIn("tools/slus_data_pieces.py tools/slus_modules.py", owner_edge)
        self.assertIn("config/slus_modules.json", owner_edge)
        self.assertIn("--module tiny_owner --object " + owner, owner_edge)
        self.assertNotIn("slus_data_pieces.py", other_edge)
        self.assertNotIn("data_piece_step", other_edge)
        self.assertIn(f"build {stamp}: data_piece_verify {owner}", ninja)
        self.assertIn("build build/src/tiny_owner.unsplit.o: phony\n", ninja)
        self.assertIn("build build/src/tiny_owner.data-pieces.json: phony\n", ninja)
        link = ninja.split("build build/slus_006.14.elf: link ", 1)[1].splitlines()[0]
        self.assertIn(stamp, link)
        physical = edges_of(ninja)
        self.assertEqual(physical, legacy_physical)
        self.assertEqual(slus_modules.logical_edges(physical, [self.module]), legacy_logical)
        commands = subprocess.run(("ninja", "-f", "build.ninja", "-t", "commands", stamp),
                                  cwd=self.root, capture_output=True, text=True, check=True).stdout
        self.assertIn("&& python3 tools/slus_data_pieces.py --manifest", commands)
        self.assertIn("python3 tools/slus_data_pieces.py --verify", commands)
        built = subprocess.run(("ninja", "-f", "build.ninja", stamp), cwd=self.root,
                               capture_output=True, text=True)
        self.assertEqual(built.returncode, 0, built.stdout + built.stderr)
        for suffix in (".o", ".unsplit.o", ".data-pieces.json", ".data-pieces.ok"):
            self.assertTrue((self.root / "build/src" / ("tiny_owner" + suffix)).is_file())
        self.assertEqual((self.root / "build/src/tiny_owner.unsplit.o").read_bytes(),
                         (self.root / "input/owned.o").read_bytes())
        self.assertEqual(json.loads((self.root / "build/src/tiny_owner.data-pieces.json").read_text())
                         ["module"], "tiny_owner")
        (self.root / "build/src/tiny_owner.data-pieces.json").unlink()
        failed = subprocess.run(("ninja", "-f", "build.ninja", stamp), cwd=self.root,
                                capture_output=True, text=True)
        self.assertNotEqual(failed.returncode, 0)
        self.assertNotIn("no work to do", failed.stdout)


if __name__ == "__main__":
    unittest.main()
