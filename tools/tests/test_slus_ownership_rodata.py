"""Jump-table (.rodata) owners: ownership proof branch and placement-certificate boundary."""

import copy
import sys
import tempfile
import unittest
from pathlib import Path
from unittest.mock import patch

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))
from fidelity import prove_slus_ownership as prover  # noqa: E402
from fidelity import certify_slus_module as certifier  # noqa: E402
from fidelity.objread import Obj  # noqa: E402
from fidelity import aspsx_diff as A  # noqa: E402

TABLE_VMA = 0x8002D010          # file 0x810
FUNC_VMA = 0x8002D100           # file 0x900
FUNC = "func_8002D100"
ARMS = [0x10, 0x18, 0x20]       # label offsets inside the function
CASES = [0, 1, 2, 1, 0, 2, 2]   # 7-entry table -> 28 bytes, then .align 3 pad, then a 2-entry table
SECOND = [2, 0]


def word(v):
    return v.to_bytes(4, "little")


class RodataFixture:
    def __init__(self, cases=CASES, second=SECOND, retail_cases=CASES):
        first = [ARMS[c] for c in cases]
        tail = [ARMS[c] for c in second]
        self.offsets = list(range(0, 28, 4)) + [32, 36]
        addends = first + tail
        span = 40
        self.obj = Obj("elf")
        self.obj.sections = {".rodata": bytes(span), f".text.{FUNC}": bytes(0x40)}
        self.obj.symbols = {FUNC: (f".text.{FUNC}", 0, "func", 0x40)}
        self.obj.relocs = [(".rodata", o, "32", ("sec", f".text.{FUNC}"), a) for o, a in zip(self.offsets, addends)]
        # the function addresses its table: lui at,%hi(.rodata) @+0 ; lw v0,%lo(.rodata)(at) @+8
        self.obj.relocs += [(f".text.{FUNC}", 0, "HI16", ("sec", ".rodata"), 0),
                            (f".text.{FUNC}", 8, "LO16", ("sec", ".rodata"), 0)]
        self.image = bytearray(0x1000)
        linked = [FUNC_VMA + a for a in addends]
        for o, v in zip(self.offsets, linked):
            self.image[0x810 + o:0x814 + o] = word(v)
        hi, lo = (TABLE_VMA + 0x8000) >> 16, TABLE_VMA & 0xFFFF
        self.image[0x900:0x904] = word(0x3C010000 | hi)
        self.image[0x908:0x90C] = word(0x8C220000 | lo)
        retail = bytearray(self.image[0x810:0x810 + span])
        for i, c in enumerate(retail_cases):
            retail[4 * i:4 * i + 4] = word(FUNC_VMA + ARMS[c])
        self.module = {"name": "jtbl_8002D100", "members": [{"id": "slus/w_8002D100", "functions": [FUNC]}],
                       "data": [{"symbol": "jtbl_8002D010", "asset": "assets/800.bin", "offset": 0x10, "size": 32,
                                 "vram": TABLE_VMA, "bytes": bytes(retail[:32]).hex(), "section": ".rodata"},
                                {"symbol": "jtbl_8002D030", "asset": "assets/800.bin", "offset": 0x30, "size": 8,
                                 "vram": TABLE_VMA + 32, "bytes": bytes(retail[32:]).hex(), "section": ".rodata"}]}
        self.linked = {FUNC: {"address": FUNC_VMA, "kind": "T"}}
        self.context = {"undefined_syms": "jtbl_8002E000 = 0x8002E000;\n", "placement": (TABLE_VMA, span)}

    def prove(self):
        return prover.prove_data(self.module, self.obj, self.linked, bytes(self.image), rodata=self.context)


class RodataOwnershipProof(unittest.TestCase):
    def test_exact_owner_is_proven(self):
        proof = RodataFixture().prove()["sections"][".rodata"]
        self.assertEqual(proof["table_words"], 9)
        self.assertEqual(proof["align_pads"], [28])
        self.assertEqual(proof["placement"], [TABLE_VMA, 40])
        self.assertEqual(proof["text_references"], 1)
        self.assertEqual([s["object_binding"] for s in proof["symbols"]], ["compiler-local"] * 2)

    def test_case17_style_table_is_refused(self):
        # the candidate routes a different case to a different arm: it links, resolves into its own
        # function, but the linked table no longer equals the retail record bytes
        f = RodataFixture(cases=[0, 2, 2, 1, 0, 2, 2])
        with self.assertRaisesRegex(ValueError, "linked table bytes differ"):
            f.prove()

    def test_link_context_is_required(self):
        f = RodataFixture()
        with self.assertRaisesRegex(ValueError, "requires link context"):
            prover.prove_data(f.module, f.obj, f.linked, bytes(f.image))

    def test_surviving_absolute_or_linked_table_symbol_is_refused(self):
        f = RodataFixture()
        f.context["undefined_syms"] += "jtbl_8002D010 = 0x8002D010;\n"
        with self.assertRaisesRegex(ValueError, "survives"):
            f.prove()
        f = RodataFixture()
        f.linked["jtbl_8002D030"] = {"address": TABLE_VMA + 32, "kind": "D"}
        with self.assertRaisesRegex(ValueError, "survives"):
            f.prove()

    def test_object_shape_is_enforced(self):
        f = RodataFixture()
        f.obj.sections[".rodata"] = bytes(44)            # untrimmed GNU-as padding
        with self.assertRaisesRegex(ValueError, "size differs"):
            f.prove()
        f = RodataFixture()
        f.obj.symbols["jtbl_8002D010"] = (".rodata", 0, "global", 32)
        with self.assertRaisesRegex(ValueError, "compiler-local"):
            f.prove()
        f = RodataFixture()
        f.obj.relocs[3] = (".rodata", 12, "32", ("sec", ".text.func_other"), 0x10)
        with self.assertRaisesRegex(ValueError, "member function"):
            f.prove()
        f = RodataFixture()
        f.obj.relocs[3] = (".rodata", 12, "32", ("sec", f".text.{FUNC}"), 0x40)   # outside the function
        with self.assertRaisesRegex(ValueError, "member function"):
            f.prove()
        f = RodataFixture()
        del f.obj.relocs[2]                               # an unrelocated nonpad word
        with self.assertRaisesRegex(ValueError, "padding"):
            f.prove()

    def test_placement_resolution_and_text_reference_are_enforced(self):
        f = RodataFixture()
        f.context["placement"] = (TABLE_VMA + 4, 40)
        with self.assertRaisesRegex(ValueError, "placement"):
            f.prove()
        f = RodataFixture()
        f.linked[FUNC] = {"address": FUNC_VMA + 4, "kind": "T"}
        with self.assertRaisesRegex(ValueError, "does not resolve"):
            f.prove()
        f = RodataFixture()
        f.image[0x908:0x90C] = word(0x8C220000 | ((TABLE_VMA + 8) & 0xFFFF))
        with self.assertRaisesRegex(ValueError, "addresses its table"):
            f.prove()
        f = RodataFixture()
        f.obj.relocs = [r for r in f.obj.relocs if r[0] == ".rodata"]
        with self.assertRaisesRegex(ValueError, "no member function addresses"):
            f.prove()

    def test_map_placement_parser(self):
        text = (" build/src/w_X_jtbl_owned.o(.rodata)\n"
                " .rodata        0x8003327c       0x3c build/src/w_X_jtbl_owned.o\n")
        self.assertEqual(prover.rodata_placement(text, "build/src/w_X_jtbl_owned.o"), (0x8003327C, 0x3C))
        self.assertIsNone(prover.rodata_placement(text, "build/src/w_Y_jtbl_owned.o"))
        with self.assertRaisesRegex(ValueError, "ambiguous"):
            prover.rodata_placement(text * 2, "build/src/w_X_jtbl_owned.o")


class RodataRetailAnchor(unittest.TestCase):
    """aspsx_diff resolves a symbol-less owned .rodata through the owner's manifest VMA."""

    class View:
        def __init__(self, symbols):
            self.obj = Obj("elf")
            self.obj.symbols = symbols

        def tokens(self, fname):
            return [(0x3C010000, "HI16", ("sec", ".rodata", 0x20)),
                    (0x00220821, None, None),
                    (0x8C220000, "LO16", ("sec", ".rodata", 0x20))]

    def test_anchor_resolves_and_is_derived_from_the_manifest(self):
        module = {"data": [{"section": ".rodata", "vram": 0x8003327C}, {"section": ".rodata", "vram": 0x8003329C}]}
        anchors = A.rodata_anchors(module)
        self.assertEqual(anchors, {".rodata": 0x8003327C})
        self.assertIsNone(A.rodata_anchors({"data": [{"section": ".sdata", "vram": 0x80080000}]}))
        words, masked = A.resolve_tokens(self.View({}), "f", 0x80000000, lambda n: None, 0, section_anchors=anchors)
        self.assertEqual(masked, [])
        self.assertEqual(words, [0x3C018003, 0x00220821, 0x8C22329C])
        _, masked = A.resolve_tokens(self.View({}), "f", 0x80000000, lambda n: None, 0)
        self.assertEqual(masked, [0, 2])

    def test_disagreeing_named_anchor_stays_masked(self):
        view = self.View({"D_X": (".rodata", 0, "local", 4)})
        _, masked = A.resolve_tokens(view, "f", 0x80000000, lambda n: 0x80040000 if n == "D_X" else None, 0,
                                     section_anchors={".rodata": 0x8003327C})
        self.assertEqual(masked, [0, 2])


class DataPieceRodataAnchors(unittest.TestCase):
    """A data-piece owner that also owns .rodata (slus/w_8003E758, module cd_command_state): its
    jump-table address words resolve to the manifest VMA and are compared against retail in every
    scope - member, physical TU and genuine - so the masked-0 proof gates need no exemption."""

    LOAD = 0x80010000
    FUNC = 0x80010100
    TABLE = 0x8002D5C0

    class View:
        def __init__(self, tokens):
            self.obj = Obj("elf")
            self.funcs = {"f": None}
            self._tokens = tokens

        def tokens(self, fname):
            return list(self._tokens)

    def image(self, words):
        data = bytearray(0x800 + (self.FUNC - self.LOAD) + 4 * len(words))
        for i, w in enumerate(words):
            o = 0x800 + (self.FUNC - self.LOAD) + 4 * i
            data[o:o + 4] = word(w)
        return ({"f": self.FUNC}, 0, bytes(data), self.LOAD)

    def compare(self, tokens, retail, anchors):
        with patch.object(A, "slus_image", return_value=self.image(retail)):
            return A.retail_compare(self.View(tokens), ["f"], "slus", section_anchors=anchors)

    def jtbl_tokens(self, section=".rodata"):
        return [(0x3C010000, "HI16", ("sec", section, 0)), (0x00220821, None, None),
                (0x8C220000, "LO16", ("sec", section, 0))]

    def retail(self, vma):
        return [0x3C010000 | (((vma + 0x8000) >> 16) & 0xFFFF), 0x00220821, 0x8C220000 | (vma & 0xFFFF)]

    def test_owned_rodata_relocations_are_compared_not_masked(self):
        anchors = {".rodata": self.TABLE}
        self.assertEqual(self.compare(self.jtbl_tokens(), self.retail(self.TABLE), anchors),
                         {"diff": 0, "masked": 0, "checked": 1})
        # without the owner's anchor the same words are masked, which every proof gate rejects
        self.assertEqual(self.compare(self.jtbl_tokens(), self.retail(self.TABLE), None),
                         {"diff": 0, "masked": 2, "checked": 1})

    def test_wrong_table_address_is_a_difference(self):
        result = self.compare(self.jtbl_tokens(), self.retail(self.TABLE + 8), {".rodata": self.TABLE})
        self.assertEqual(result, {"diff": 1, "masked": 0, "checked": 1})      # %lo differs, %hi agrees

    def test_relocation_against_another_section_stays_masked(self):
        result = self.compare(self.jtbl_tokens(".sdata"), self.retail(self.TABLE), {".rodata": self.TABLE})
        self.assertEqual(result, {"diff": 0, "masked": 2, "checked": 1})

    def test_measured_anchor_owner_selection(self):
        owner = {"source": "src/x_owned.c", "data": [{"section": ".sdata.D_1", "vram": 0x80080000},
                                                     {"section": ".rodata", "vram": self.TABLE}]}
        other = {"source": "src/y_owned.c", "data": [{"section": ".rodata", "vram": 0x80030000}]}
        plain = {"source": "src/z_owned.c", "data": [{"section": ".sdata.D_2", "vram": 0x80080010}]}
        pick = A.measured_section_anchors
        self.assertEqual(pick({"kind": "slus", "data_piece_module": owner}), {".rodata": self.TABLE})
        self.assertEqual(pick({"kind": "slus", "owner_module": owner}), {".rodata": self.TABLE})
        self.assertEqual(pick({"kind": "slus", "owner_module": other, "data_piece_module": owner}, owner),
                         {".rodata": self.TABLE})                               # the member module wins
        self.assertIsNone(pick({"kind": "slus", "data_piece_module": plain}))
        self.assertIsNone(pick({"kind": "slus"}))
        self.assertIsNone(pick({"kind": "overlay", "data_piece_module": owner}))


class RodataPlacementCertificate(unittest.TestCase):
    """certify_slus_module grants L4 placement and checks no data bytes; a jump-table owner (only
    include/common.h) is refused there, so its data ownership rests on prove_slus_ownership alone."""

    def test_jump_table_owner_has_no_placement_grant(self):
        module = {"name": "jtbl_80054F9C", "source": "src/w_80054F9C_jtbl_owned.c",
                  "members": [{"id": "slus/w_80054F9C", "source": "src/w_80054F9C.c", "functions": ["func_80054F9C"]}],
                  "headers": ["include/common.h"], "evidence": "docs/evidence/slus_rodata_migration.md",
                  "recipe": {"ccver": "2.7.2-cdk", "ccflags": "", "asflags": ""},
                  "data": [{"symbol": "jtbl_80032E14", "asset": "assets/800.bin", "offset": 24084, "size": 144,
                            "vram": 0x80032E14, "bytes": "00" * 144, "section": ".rodata"}]}
        with tempfile.TemporaryDirectory() as td:
            (Path(td) / "docs/evidence").mkdir(parents=True)
            (Path(td) / module["evidence"]).write_text("review\n")
            with patch.object(certifier, "modules", return_value=[copy.deepcopy(module)]), \
                    patch.object(certifier, "ROOT", Path(td)):
                with self.assertRaisesRegex(ValueError, "own shared header"):
                    certifier.certify("jtbl_80054F9C", "reviewer")


if __name__ == "__main__":
    unittest.main()
