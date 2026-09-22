"""The `cross-image` split-audit kind (tools/split_audit.py, 2026-09-22).

A tail-jump target that does NOT land inside the declaring container's image under the row's own
delta used to be `unresolved`, which blocks L3.  Three things can still decide it, and all are
`cross-image`:

  image "slus"    it is a function of the SLUS base executable (baserom/slus_006.14), which is
                  co-resident with every overlay -- so the retail `j`/`jal` is an inter-image call.
  image "absent"  retail CALLS it with a `jal` -- in the row's own retail bytes, or at least
                  inside the row's own segment run -- while its code is on no image in the tree.
                  A `jal` is a call and a call HAS a C producer; a retail `j` is what has none,
                  which is this audit's whole premise.  So it is not a mis-split of this row.
  image "kernel"  the target is a fixed PlayStation kernel RAM address (`kernel_verdict()`,
                  [0x80000000, 0x80010000)) and the row's OWN retail bytes carry a `j`/`jal` word
                  decoding to it.  Unlike "absent", a plain `j` decides here: the address window
                  itself -- never part of any overlay or of SLUS -- is the evidence, and decoding
                  needs only the row's link address's top nibble (fixed at 0x8 for KSEG0-mapped
                  overlay/RAM code at every candidate base), so this needs no rowbase record.

For `slus`/`absent`, a `j` with no `jal` anywhere and no image to read the target's bytes in stays
`unresolved`.  The three town devkit-blob rows (`func_808B8184`, `func_808B85F0`, `func_808BB138`)
used to land there -- their own bytes carry only a `j`, never a `jal` -- until `kernel_verdict()`
was added: their targets are all inside the kernel window, so they are `cross-image`/`kernel` now.

WHAT THE REAL TREE SAYS, and why "slus" is NOT the answer for `func_8007BEF0`
(docs/HANDOVER.md section 3.1 and the town `row_2714dc_804084dc` rowbase proof both claim it is a
SLUS function; they are wrong and are pinned here by test):
  * 0x8007BEF0 is SLUS file offset 0x4F6F0 -- the middle of the libgte string
    "Error: Can't push matrix,stack(max 20) is full!", inside the `bin` resident-data block.
  * no `j`/`jal` word anywhere in baserom/slus_006.14 targets it, and no symbol names it.
  * it is the `exit` of the DECLARING module's own linked runtime, whose text was never carved
    into MAIN.BIN (docs/evidence/konami_assertion_sites.md sections 7-8,
    docs/evidence/void_callees_20260922.md).

The verdict function offimage_verdict() is pure, so the classification tests need no images at
all; the handful that do read baserom/slus_006.14 or config/slus_006.14.yaml skip without them.

    ./.venv/bin/python3 -m pytest tools/tests/test_split_audit_cross_image.py -q
"""
import os, sys, unittest

_TOOLS = os.path.join(os.path.dirname(__file__), "..")
sys.path.insert(0, _TOOLS)
sys.path.insert(0, os.path.join(_TOOLS, "gate"))
import split_audit as SA  # noqa: E402
import levels as L  # noqa: E402

# main/func_800207D4's real geometry, as tools/split_audit.py resolved it on 2026-09-22.
TA = 0x8007BEF0                     # the tail-jump target
DELTA = 0x80197000                  # the declaring row's own link delta
TOFF = (TA - DELTA) & 0xFFFFFFFF    # 0xFFEE4EF0 -- nowhere near the image
IMGSIZE = 0x275800                  # MAIN_MAIN.BIN
RUN = (0x26A0F0, 0x2713A0, DELTA)   # the row's own merged segment run
OWN_JAL = [("jal", 0x804077F8)]     # the `jal` inside the row's own retail bytes
OWN_J = [("j", 0x804077F8)]


def slus(resident=False, in_text=False, jal=(), js=(), symbol=None, foff=0x4F6F0):
    """A synthetic slus_lookup() result -- the same shape the real one returns."""
    d = {"resident": resident, "seg": (0x8002D000, 0x54800),
         "foff": foff if resident else None, "in_text": in_text,
         "js": list(js), "jal": list(jal), "symbol": symbol}
    d["decided"] = bool(in_text and (jal or symbol))
    return d


class AddressMapping(unittest.TestCase):
    def test_slus_delta_is_vram_minus_file_offset(self):
        self.assertEqual(SA.SLUS_DELTA, SA.SLUS_VRAM - SA.SLUS_OFF)
        self.assertEqual(SA.SLUS_VRAM - SA.SLUS_DELTA, SA.SLUS_OFF)

    def test_target_address_maps_to_its_slus_file_offset(self):
        """0x8007BEF0 -> 0x4F6F0: the arithmetic the lookup does, on its own."""
        self.assertEqual(TA - SA.SLUS_DELTA, 0x4F6F0)

    @unittest.skipUnless(SA.SLUS.exists(), "baserom/slus_006.14 not present")
    def test_real_header_gives_the_resident_segment(self):
        self.assertEqual(SA.slus_segment(), (SA.SLUS_VRAM, 0x54800))

    @unittest.skipUnless(SA.SLUS.exists() and SA.SLUS_YAML.exists(), "SLUS image/yaml not present")
    def test_func_8007BEF0_is_resident_but_is_rodata_and_undecided(self):
        """The finding that overturns HANDOVER section 3.1: resident, yes; SLUS code, no."""
        got = SA.slus_lookup(TA)
        self.assertTrue(got["resident"])
        self.assertEqual(got["foff"], 0x4F6F0)
        self.assertFalse(got["in_text"])       # the `bin` resident-data block at 0x3E018
        self.assertEqual(got["jal"], [])
        self.assertEqual(got["js"], [])
        self.assertIsNone(got["symbol"])
        self.assertFalse(got["decided"])
        # and the bytes there really are the libgte error string, not instructions
        self.assertTrue(SA._image(SA.SLUS)[0x4F6F0:0x4F6F8].startswith(b"Error: "))

    @unittest.skipUnless(SA.SLUS_YAML.exists(), "config/slus_006.14.yaml not present")
    def test_code_spans_hold_the_c_segment_and_not_the_resident_data(self):
        spans = SA.slus_code_spans()
        self.assertTrue(any(st <= 0x102C4 < en for st, en in spans))     # [0x102c4, c, code]
        self.assertFalse(any(st <= 0x4F6F0 < en for st, en in spans))    # [0x3e018, bin]

    @unittest.skipUnless(SA.SLUS_SYMS.exists(), "config/slus_006.14.symbols.txt not present")
    def test_overlay_self_define_stubs_are_not_slus_symbols(self):
        """`func_8007BFE0 = 0x8007BFE0; // overlay self-define (func_80019E34 callee)` names an
        OVERLAY address so an overlay TU can link; reading it as SLUS code is the false positive
        this audit has to avoid.  A real `// type:func` symbol still comes through."""
        syms = SA.slus_symbols()
        self.assertNotIn(0x8007BFE0, syms)
        self.assertNotIn(0x8007C040, syms)
        self.assertEqual(syms.get(0x800339D0), "__main")


class OffImageVerdict(unittest.TestCase):
    def verdict(self, own=(), run_jal=(), run_js=(), sl=None):
        return SA.offimage_verdict("main", TA, DELTA, TOFF, IMGSIZE, list(own), RUN,
                                   list(run_jal), list(run_js), sl or slus())

    def test_slus_index_hit_gives_cross_image_slus(self):
        """A synthetic SLUS index hit: the target is in a SLUS code subsegment and a `jal` there
        reaches it -- a real function of the co-resident executable."""
        got = self.verdict(sl=slus(resident=True, in_text=True, jal=[0x8003AB00], foff=0xE300))
        self.assertEqual(got["kind"], "cross-image")
        self.assertEqual(got["image"], "slus")
        self.assertEqual(got["target_foff"], "0xe300")
        self.assertEqual(got["jal_callers"], ["0x8003ab00"])
        self.assertTrue(got["byte_verified"])
        self.assertIn("base executable", got["proof"])
        self.assertIn("Clears L3, blocks L4", got["proof"])

    def test_slus_named_function_symbol_also_decides(self):
        got = self.verdict(sl=slus(resident=True, in_text=True, symbol="CdReadSync", foff=0x36990))
        self.assertEqual((got["kind"], got["image"]), ("cross-image", "slus"))

    def test_slus_rodata_hit_does_not_decide_on_its_own(self):
        """Resident but NOT in a code subsegment: the SLUS path must not fire.  With no `jal`
        anywhere else either, the record stays unresolved."""
        got = self.verdict(sl=slus(resident=True, in_text=False))
        self.assertEqual(got["kind"], "unresolved")

    def test_own_row_jal_gives_cross_image_absent(self):
        """The three real func_8007BEF0 records: the row's own retail bytes carry the `jal`."""
        got = self.verdict(own=OWN_JAL, run_jal=[0x80403000, 0x804077F8],
                           sl=slus(resident=True, in_text=False))
        self.assertEqual(got["kind"], "cross-image")
        self.assertEqual(got["image"], "absent")
        self.assertIsNone(got["target_foff"])
        self.assertTrue(got["byte_verified"])
        self.assertEqual(got["jal_callers"], ["0x80403000", "0x804077f8"])
        self.assertIn("the row's OWN retail bytes carry jal", got["proof"])
        self.assertIn("DATA subsegment", got["proof"])        # names why SLUS did not decide
        self.assertIn("Clears L3, blocks L4", got["proof"])

    def test_run_jal_without_an_own_row_jal_still_decides_but_is_not_byte_verified(self):
        got = self.verdict(run_jal=[0x80403000], sl=slus(resident=True, in_text=False))
        self.assertEqual((got["kind"], got["image"]), ("cross-image", "absent"))
        self.assertFalse(got["byte_verified"])

    def test_no_hit_anywhere_stays_unresolved(self):
        got = self.verdict()
        self.assertEqual(got["kind"], "unresolved")
        self.assertNotIn("image", got)
        self.assertFalse(got["byte_verified"])
        self.assertIn("Stays unresolved", got["proof"])

    def test_own_row_j_only_stays_unresolved(self):
        """A `j` to a non-kernel address on no image we hold decides nothing -- that is exactly
        the mis-split question this audit exists to ask.  (Before kernel_verdict() existed, the
        three real town devkit-blob rows landed here too; their targets are all inside the kernel
        window now, so they take the KernelVerdict path below instead.)"""
        got = self.verdict(own=OWN_J, run_js=[0x804077F8])
        self.assertEqual(got["kind"], "unresolved")
        self.assertIn("j at 0x804077F8", got["proof"])


class KernelVerdict(unittest.TestCase):
    """SA.kernel_verdict() -- the `image: "kernel"` path, checked in main() before the `d is
    None` refusal (tools/split_audit.py) so it needs no rowbase record at all.  PURE like
    offimage_verdict(), so no images/rows/filesystem are needed to test it."""

    # town/func_808B8184's real geometry (tools/split_audit.py, 2026-09-22): a `j` at row +0x34
    # to 0x800039C8, well inside the fixed kernel RAM window.
    KTA = 0x800039C8
    KBASE = 0x808B8184
    KFOFF = 0x838184
    KHITS = [("j", 0x808B81B8)]                # row +0x34

    def test_kernel_address_with_own_row_j_gives_cross_image_kernel(self):
        got = SA.kernel_verdict(self.KTA, self.KBASE, self.KHITS, self.KFOFF)
        self.assertEqual(got["kind"], "cross-image")
        self.assertEqual(got["image"], "kernel")
        self.assertTrue(got["byte_verified"])
        self.assertEqual(got["row_jump_offsets"], ["j@row+0x34"])
        self.assertIn("kernel", got["proof"])
        self.assertIn("Clears L3, blocks L4", got["proof"])

    def test_kernel_address_with_own_row_jal_also_decides(self):
        """Unlike the `absent` cross-image kind, a plain `j` is enough here -- but a `jal` hit
        decides it too, the same way."""
        got = SA.kernel_verdict(self.KTA, self.KBASE, [("jal", 0x808B81B8)], self.KFOFF)
        self.assertEqual((got["kind"], got["image"]), ("cross-image", "kernel"))
        self.assertTrue(got["byte_verified"])

    def test_kernel_address_with_no_own_row_word_stays_unresolved(self):
        """The window alone does not decide it -- only the row's OWN bytes do."""
        got = SA.kernel_verdict(self.KTA, self.KBASE, [], self.KFOFF)
        self.assertEqual(got["kind"], "unresolved")
        self.assertFalse(got["byte_verified"])
        self.assertNotIn("image", got)
        self.assertIn("kernel RAM window", got["proof"])

    def test_non_kernel_address_is_unaffected_by_the_kernel_window(self):
        """main's real func_8007BEF0 (0x8007BEF0) is well outside [0x80000000, 0x80010000) -- the
        kernel window must not swallow ordinary cross-image/absent targets."""
        self.assertFalse(SA.KERNEL_LO <= TA < SA.KERNEL_HI)
        # kernel_verdict() is never even called for it in main() (the `elif` guard checks the
        # window first); offimage_verdict() still owns it, unaffected by kernel_verdict existing:
        got = SA.offimage_verdict("main", TA, DELTA, TOFF, IMGSIZE, list(OWN_JAL), RUN,
                                  [0x80403000, 0x804077F8], [], slus(resident=True, in_text=False))
        self.assertEqual((got["kind"], got["image"]), ("cross-image", "absent"))


class LadderReadsTheNewKind(unittest.TestCase):
    """levels.audit_gate is the L3 predicate (the ledger-kind gate): a record must exist and its
    kind must be none of intra/unresolved/missing.  It is the "not undecided" form, so a new
    DECIDED kind needs no change there -- assert that, in both directions."""

    def test_audit_gate_accepts_cross_image_for_l3(self):
        for kind in ("cross-image", "cross-segment", "extern-jal"):
            kinds, ok = L.audit_gate("main/func_800207D4", ["func_8007BEF0"],
                                     {("main/func_800207D4", "func_8007BEF0"): kind})
            self.assertEqual((kinds, ok), ([kind], True), kind)

    def test_audit_gate_still_blocks_the_undecided_kinds(self):
        for kind in ("intra", "unresolved", "missing"):
            _, ok = L.audit_gate("main/func_800207D4", ["func_8007BEF0"],
                                 {("main/func_800207D4", "func_8007BEF0"): kind})
            self.assertFalse(ok, kind)

    def test_cross_image_row_reaches_l3_but_not_l4(self):
        """End to end through evaluate_row, in tools/tests/test_levels.py's shape: a tail-jump
        dependency with a `cross-image` record clears L3 and still blocks L4."""
        L._CONTAINER_SYMS["main"] = set()
        r = {"id": "main/func_800207D4", "size": 92, "container": "main", "kind": "overlay",
             "true_name": "func_804077D4", "func": "func_800207D4", "defs": None}
        text = ('#include "common.h"\n'
                'extern void func_8007BEF0(s32 arg0) __attribute__((noreturn));\n'
                'void func_800207D4(s32 card_slot) {\n'
                '    if (card_slot == 0) {\n'
                '        func_8007BEF0(1);\n'
                '    }\n'
                '}\n')
        split_idx = {(r["id"], "func_8007BEF0"): "cross-image"}
        rec = L.evaluate_row(r, text, "the pinned text", {r["id"]},
                             {"l4_modules": {r["id"]: {}}}, split_idx)
        self.assertEqual(rec["split_audit"], ["cross-image"])
        self.assertEqual(rec["tail_jumps"], 1)
        self.assertEqual(rec["level"], 3)
        self.assertIn("tail_jump", rec["l4_residue"])


if __name__ == "__main__":
    unittest.main()
