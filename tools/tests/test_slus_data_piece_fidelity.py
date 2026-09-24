"""Portable data-piece projection and proof-record tests."""

from __future__ import annotations

from copy import deepcopy
import hashlib
from pathlib import Path
import shutil
import subprocess
import sys
import tempfile
import unittest
from unittest.mock import patch

ROOT = Path(__file__).resolve().parents[2]
sys.path[:0] = [str(ROOT / "tools"), str(ROOT / "tools/build"), str(ROOT / "tools/fidelity")]
from fidelity import aspsx_diff as A  # noqa: E402
from fidelity.objread import Obj  # noqa: E402
from slus_data_pieces import apply_data_pieces, split_elf  # noqa: E402
from slus_module_evidence import check_data_piece_record  # noqa: E402
from slus_modules import data_piece_plan  # noqa: E402


ASM = """.set noreorder
.text
.globl probe
.type probe,@function
.ent probe
probe:
lw $2,%gp_rel(alpha)($28)
lw $3,%gp_rel(beta+4)($28)
lui $4,%hi(beta+4)
addiu $4,$4,%lo(beta+4)
jr $31
nop
.size probe,.-probe
.end probe
.sdata
.align 2
.globl alpha
.type alpha,@object
alpha: .word 0x12345678
.size alpha,4
.space 4
.globl beta
.type beta,@object
beta: .word 0x90abcdef,0x76543210
.size beta,8
.data
.globl pointer
pointer: .word alpha
"""


def module():
    return {
        "name": "synthetic_piece_owner", "source": "src/synthetic_piece_owned.c",
        "members": [{"id": "slus/w_00000000", "source": "src/w_00000000.c",
                     "functions": ["probe"]}],
        "headers": [], "recipe": {"ccver": "2.7.2-cdk", "ccflags": "", "asflags": ""},
        "data": [
            {"symbol": "alpha", "asset": "assets/1000.bin", "offset": 0,
             "vram": 0x80010000, "size": 4, "bytes": "78563412", "section": ".sdata.alpha"},
            {"symbol": "beta", "asset": "assets/1000.bin", "offset": 8,
             "vram": 0x80010008, "size": 8, "bytes": "efcdab9010325476", "section": ".sdata.beta"}],
        "data_pieces": [
            {"symbol": "alpha", "source_section": ".sdata", "alignment": 4},
            {"symbol": "beta", "source_section": ".sdata", "alignment": 4}],
        "evidence": "docs/evidence/synthetic_piece_owner.md",
    }


def controlled_lnk_obj(elf):
    """Model the decoded Obj returned by read_lnk with section-base targets.

    A genuine LNK can name the original section and addend where ELF names a
    global. The view must project both descriptions onto the declared piece.
    """
    relocations = []
    for section, offset, kind, target, addend in elf.relocs:
        if target[0] == "sym" and target[1] in ("alpha", "beta"):
            addend += elf.symbols[target[1]][1]
            target = ("sec", ".sdata")
        relocations.append((section, offset, kind, target, addend))
    return Obj(fmt="lnk", sections=deepcopy(elf.sections),
               symbols=deepcopy(elf.symbols), relocs=relocations,
               func_extents={"probe": (".text", 0, 24)})


def complete_record(receipt):
    expected = {"diff": 0, "masked": 0, "checked": 1}
    return {"data_piece_transform": receipt, "data_piece_functions": ["probe"],
            "maspsx_physical_retail": expected,
            "genuine": {"2.79": {"lnk_unknown": [], "missing": [],
                                   "physical": {"exact": True, "diff": 0, "missing": [],
                                                "retail": expected, "len_m": 6, "len_g": 6}}}}


@unittest.skipUnless(shutil.which("mipsel-linux-gnu-as"), "GNU MIPS assembler unavailable")
class DataPieceFidelityTest(unittest.TestCase):
    def setUp(self):
        self.tmp = tempfile.TemporaryDirectory()
        self.addCleanup(self.tmp.cleanup)
        self.path = Path(self.tmp.name) / "synthetic.o"
        source = self.path.with_suffix(".s")
        source.write_text(ASM)
        result = subprocess.run(["mipsel-linux-gnu-as", "-EL", "-march=r3000", "-G8",
                                 "-o", str(self.path), str(source)], capture_output=True, text=True)
        self.assertEqual(result.returncode, 0, result.stdout + result.stderr)
        self.raw = self.path.read_bytes()
        self.module = module()
        self.obj = A.read_elf(self.raw)

    def views(self):
        original = A.data_piece_view(self.obj, self.module)
        split, proof = split_elf(self.raw, data_piece_plan(self.module))
        placed = A.data_piece_view(A.read_elf(split), self.module)
        lnk = A.data_piece_view(controlled_lnk_obj(self.obj), self.module, original)
        return original, placed, lnk, proof

    def test_original_split_and_lnk_shape_have_complete_equal_tokens(self):
        original, placed, lnk, proof = self.views()
        for view in (original, placed, lnk):
            self.assertEqual(set(view.funcs), {"probe"})
            self.assertEqual(len(view.tokens("probe")), 6)
        self.assertEqual(original.tokens("probe"), placed.tokens("probe"))
        self.assertEqual(original.tokens("probe"), lnk.tokens("probe"))
        self.assertEqual(original.loc(".sdata", 8), ("sym", "beta", 0))
        self.assertEqual(original.loc(".sdata", 12), ("sym", "beta", 4))
        self.assertEqual(placed.loc(".sdata.beta", 4), ("sym", "beta", 4))
        self.assertEqual(proof["emptied_source_sections"][".sdata"]["discarded_alignment_bytes"], 4)
        self.assertEqual(proof["relocation_entries_unchanged"], True)

    def test_uncovered_target_gap_and_wrong_payload_are_rejected(self):
        broken = deepcopy(self.obj)
        index = next(i for i, reloc in enumerate(broken.relocs)
                     if reloc[3] == ("sym", "alpha"))
        section, offset, kind, target, _ = broken.relocs[index]
        broken.relocs[index] = (section, offset, kind, target, 4)
        with self.assertRaisesRegex(ValueError, "outside a declared piece"):
            A.data_piece_view(broken, self.module)

        gap = deepcopy(self.obj)
        body = bytearray(gap.sections[".sdata"])
        body[4] = 7
        gap.sections[".sdata"] = bytes(body)
        with self.assertRaisesRegex(ValueError, "nonzero unowned"):
            A.data_piece_view(gap, self.module)

        payload = deepcopy(self.obj)
        body = bytearray(payload.sections[".sdata"])
        body[0] ^= 1
        payload.sections[".sdata"] = bytes(body)
        with self.assertRaisesRegex(ValueError, "initializer or extent differs"):
            A.data_piece_view(payload, self.module)

    def test_local_label_unknown_relocation_and_mixed_layout_are_rejected(self):
        extra = deepcopy(self.obj)
        extra.symbols["unselected"] = (".sdata", 4, "local", 0)
        with self.assertRaisesRegex(ValueError, "unselected labels"):
            A.data_piece_view(extra, self.module)

        local = deepcopy(self.obj)
        section, offset, _, size = local.symbols["alpha"]
        local.symbols["alpha"] = (section, offset, "local", size)
        with self.assertRaisesRegex(ValueError, "defined global"):
            A.data_piece_view(local, self.module)

        unknown = deepcopy(self.obj)
        unknown.unknown = ["unsupported patch"]
        with self.assertRaisesRegex(ValueError, "decoded relocations"):
            A.data_piece_view(unknown, self.module)

        split, _ = split_elf(self.raw, data_piece_plan(self.module))
        mixed = A.read_elf(split)
        section, _, kind, size = mixed.symbols["beta"]
        self.assertEqual(section, ".sdata.beta")
        mixed.symbols["beta"] = (".sdata", 8, kind, size)
        mixed.sections[".sdata"] = self.obj.sections[".sdata"]
        with self.assertRaisesRegex(ValueError, "mixed original and split"):
            A.data_piece_view(mixed, self.module)

        tail = A.read_elf(split)
        tail.sections[".sdata.alpha"] += b"\0"
        with self.assertRaisesRegex(ValueError, "trailing data"):
            A.data_piece_view(tail, self.module)

    def test_legacy_view_is_unchanged_without_piece_module(self):
        legacy = A.data_piece_view(self.obj)
        self.assertIs(type(legacy), A.View)
        self.assertEqual(legacy.tokens("probe"), A.View(self.obj).tokens("probe"))

    def test_attribution_uses_unsplit_baseline_for_unchanged_variants(self):
        split, _ = split_elf(self.raw, data_piece_plan(self.module))
        directory = self.path.parent
        (directory / "m.o").write_bytes(split)
        (directory / "m.unsplit.o").write_bytes(self.raw)
        view = A.data_piece_view(A.read_elf(split), self.module)
        genuine = A.data_piece_view(controlled_lnk_obj(self.obj), self.module, view)
        ctx = {"kind": "slus", "m_in": "", "data_piece_module": self.module,
               "as_args": ["--aspsx-version=2.79", "--dont-force-G0", "-I.", "-I.",
                           "-EL", "-march=r3000", "-G8"]}
        with patch.object(A, "run_maspsx", return_value=(self.raw, None)) as assemble, \
             patch.object(A, "data_piece_view", side_effect=AssertionError("unchanged variant reprojected")):
            result = A.attribute(ctx, {}, [], view,
                                 {"2.79": (genuine, {"diff": 1})},
                                 {"2.79": [genuine]}, ["2.79"], ["probe"], directory)
        self.assertGreater(assemble.call_count, 0)
        self.assertEqual(len(result["_nochange"]), assemble.call_count)
        self.assertEqual(result["2.79"], {"base": 1, "fix": []})

    def test_complete_proof_record_and_scoped_physical_unit(self):
        receipt = apply_data_pieces(self.path, self.module)
        record = complete_record(receipt)
        self.assertIsNone(check_data_piece_record(self.module, record))
        descriptor = {"source": self.module["source"], "functions": ["probe"]}
        outer = {"physical_units": [dict(record, source=self.module["source"])]}
        self.assertIsNone(check_data_piece_record(self.module, outer, descriptor))

    def test_missing_stale_wrong_scope_and_malformed_nested_proofs_are_rejected(self):
        receipt = apply_data_pieces(self.path, self.module)
        baseline = complete_record(receipt)
        descriptor = {"source": self.module["source"], "functions": ["probe"]}
        cases = []
        missing = deepcopy(baseline)
        missing.pop("data_piece_transform")
        cases.append(("missing", missing, None))
        stale = deepcopy(baseline)
        stale["data_piece_transform"]["plan"][0]["size"] += 1
        cases.append(("stale plan", stale, None))
        stale_core = deepcopy(baseline)
        stale_core["data_piece_transform"]["core_sha256"] = "0" * 64
        cases.append(("core hash invalidated", stale_core, None))
        stale_hash = deepcopy(baseline)
        stale_hash["data_piece_transform"]["pre_object_sha256"] = "0" * 64
        cases.append(("unbound object hash", stale_hash, None))
        wrong_scope = deepcopy(baseline)
        wrong_scope["data_piece_functions"] = ["other"]
        cases.append(("wrong function scope", wrong_scope, None))
        nested = deepcopy(baseline)
        nested["data_piece_transform"]["split_elf"] = []
        cases.append(("malformed split proof", nested, None))
        nested_flags = deepcopy(baseline)
        nested_flags["data_piece_transform"]["split_elf"]["relocation_entries_unchanged"] = False
        cases.append(("altered relocation proof", nested_flags, None))
        physical = deepcopy(baseline)
        physical["genuine"]["2.79"]["physical"]["missing"] = ["probe"]
        cases.append(("incomplete genuine", physical, None))
        ambiguous = {"physical_units": [dict(baseline, source=self.module["source"]),
                                        dict(baseline, source=self.module["source"])]}
        cases.append(("ambiguous physical", ambiguous, descriptor))
        wrong_source = {"physical_units": [dict(baseline, source="src/other.c")]}
        cases.append(("wrong physical source", wrong_source, descriptor))
        for label, record, scope in cases:
            with self.subTest(label=label), self.assertRaises(ValueError):
                check_data_piece_record(self.module, record, scope)
        self.assertEqual(receipt["core_sha256"], hashlib.sha256(
            (ROOT / "tools/build/slus_data_pieces.py").read_bytes()).hexdigest())


if __name__ == "__main__":
    unittest.main()
