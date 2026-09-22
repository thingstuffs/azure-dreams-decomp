"""The L3/L4 tail-jump ladder (owner rulings 2026-09-22 evening,
docs/PIN_CAMPAIGN_CHARTER.md "Rulings 2026-09-22 (evening)" section):

  - L3 additionally requires every tail-jump dependency of a row -- a noreturn pseudo-call in the
    text, or a call to a symbol in the row's container sibcall/noreturn list -- to carry a
    ledger/split_audit.jsonl record whose kind is neither "intra" (mis-split) nor "unresolved"
    (a missing record counts as unaudited, same as "unresolved").
  - L4 = the module criterion AND pins == 0 (strict) AND zero tail-jump dependency of any kind,
    audited or not.

Synthetic rows/text only; no filesystem writes, no compiler, no real ledger/config files read
except the real (committed) config/decomp_audit_baseline.json, which does not mention any
synthetic row id used here and so contributes no fidelity sites.  container_tail_syms()'s cache is
pre-seeded empty so no test result depends on the live content of config/sibcall_syms*.txt /
config/noreturn_syms*.txt.

    ./.venv/bin/python3 -m pytest tools/tests/test_levels.py -q
"""
import os, sys, unittest

sys.path.insert(0, os.path.join(os.path.dirname(__file__), ".."))
import levels as L  # noqa: E402


def row(id="dungeon/func_80091234", size=64, container="dungeon", kind="overlay",
        true_name=None, func=None, defs=None):
    return {"id": id, "size": size, "container": container, "kind": kind,
            "true_name": true_name, "func": func or id.split("/")[-1], "defs": defs}


# func_80098765 is far outside [0x80091234, 0x80091234+64): a real extern tail-jump target, not
# the row's own body (so levels.intra_tail_calls -- the narrower mis-split heuristic -- reads 0).
TEXT_TAILJUMP = '''#include "common.h"
extern void func_80098765(void) __attribute__((noreturn));
s32 {name}(s32 a) {{
    if (a) {{
        return func_80098765();
    }}
    return a + 1;
}}
'''


class TailJumpLadder(unittest.TestCase):
    def setUp(self):
        L._CONTAINER_SYMS["dungeon"] = set()   # isolate from the real config/*_syms*.txt content

    def _row_ready_for_l3(self, extra_sweeps=None):
        r = row()
        text = TEXT_TAILJUMP.format(name=r["func"])
        raw_text = "not the same text"          # landed Layer-2 body differs from the pinned text
        promoted = {r["id"]}
        sweeps = {"l4_modules": {r["id"]: {}}}
        if extra_sweeps: sweeps.update(extra_sweeps)
        return r, text, raw_text, promoted, sweeps

    def test_tail_jump_targets_found_outside_own_extent(self):
        r, text, _, _, _ = self._row_ready_for_l3()
        self.assertEqual(L.tail_jump_targets(r, text), ["func_80098765"])
        self.assertEqual(L.intra_tail_calls(r, text), 0)

    def test_noreturn_macro_spelling_is_a_tail_jump_dependency(self):
        """dungeon/func_81988E48 pre-landing (found 2026-09-22): a target declared noreturn via
        the portable `#define NORETURN __attribute__((noreturn)) / #else #define NORETURN` idiom
        -- not the literal `__attribute__((noreturn))` spelling -- must be recognised exactly like
        the literal spelling.  tools/gate/gen_noreturn_syms.py already treats the two as
        equivalent (`_NORETURN_MACRO_RE`); _noreturn_call_targets did not, so a row whose only
        spelling of a target's noreturn-ness was the macro token got no split_audit.jsonl record
        at all, regardless of container sibcall/noreturn list membership."""
        r = row()
        text = ("#ifdef __GNUC__\n"
                "#define NORETURN __attribute__((noreturn))\n"
                "#else\n"
                "#define NORETURN\n"
                "#endif\n"
                "extern void func_80098765(void) NORETURN;\n"
                "s32 %s(s32 a) {\n"
                "    if (a) {\n"
                "        func_80098765();\n"
                "    }\n"
                "    return a + 1;\n"
                "}\n" % r["func"])
        self.assertEqual(L.tail_jump_targets(r, text), ["func_80098765"])
        self.assertEqual(L.intra_tail_calls(r, text), 0)

    def test_noreturn_macro_spelling_in_extent_is_an_intra_tail_call(self):
        """Same idiom, but the target address (base + 0x2C0) falls inside the row's own extent --
        the func_81988E48/func_80024908 shape exactly: a `j` to a label inside the row, spelled as
        a NORETURN-macro-declared pseudo-call.  This is the mis-split/pseudo-call detector
        (intra_tail_call_targets), which shares _noreturn_call_targets with tail_jump_targets."""
        r = row(id="dungeon/func_80024648", size=1116, true_name="func_80024648")
        text = ("#ifdef __GNUC__\n"
                "#define NORETURN __attribute__((noreturn))\n"
                "#else\n"
                "#define NORETURN\n"
                "#endif\n"
                "extern void func_80024908(void) NORETURN;\n"
                "s32 func_80024648(s32 a) {\n"
                "    if (a) {\n"
                "        func_80024908();\n"
                "        return a;\n"
                "    }\n"
                "    return a + 1;\n"
                "}\n")
        self.assertEqual(L.tail_jump_targets(r, text), ["func_80024908"])
        self.assertEqual(L.intra_tail_calls(r, text), 1)

    def test_noreturn_macro_declared_but_never_called_is_not_a_dependency(self):
        """A NORETURN-macro-declared extern with no tail-call statement in the text is not a
        dependency -- same rule the literal `__attribute__((noreturn))` spelling already gets."""
        r = row()
        text = ("#define NORETURN __attribute__((noreturn))\n"
                "extern void func_80098765(void) NORETURN;\n"
                "s32 %s(s32 a) {\n    return a + 1;\n}\n" % r["func"])
        self.assertEqual(L.tail_jump_targets(r, text), [])

    def test_noreturn_lookalike_macro_name_does_not_match(self):
        """A macro whose name merely CONTAINS `NORETURN` as a substring (not the bare token) must
        not be mistaken for the idiom -- \\bNORETURN\\b requires a word boundary on both sides."""
        r = row()
        text = ("#define NORETURN_HINT 1\n"
                "extern void func_80098765(void) NORETURN_HINT;\n"
                "s32 %s(s32 a) {\n    return func_80098765();\n}\n" % r["func"])
        self.assertEqual(L.tail_jump_targets(r, text), [])

    def test_own_definition_header_is_not_a_tail_jump_dependency(self):
        """A row whose own name is in its container's noreturn/sibcall list (a genuine noreturn
        function or j-only dispatcher defined in-tree) must not list itself off its own
        `void func_X(...) {` header alone -- only an actual call counts."""
        r = row()
        L._CONTAINER_SYMS["dungeon"] = {r["func"]}   # this row's own name is "tail-listed"
        text = "s32 %s(s32 a) {\n    return a + 1;\n}\n" % r["func"]
        self.assertEqual(L.tail_jump_targets(r, text), [])

    def test_container_list_call_is_a_tail_jump_dependency(self):
        """A plain call of a symbol in the row's container sibcall/noreturn list is a tail-jump
        dependency even with no noreturn attribute or asm alias in the C at all."""
        r = row()
        L._CONTAINER_SYMS["dungeon"] = {"func_80099999"}
        text = "s32 %s(s32 a) {\n    return func_80099999(a);\n}\n" % r["func"]
        self.assertEqual(L.tail_jump_targets(r, text), ["func_80099999"])

    def test_intra_audit_record_caps_at_l2(self):
        """A split_audit record of kind 'intra' (a confirmed mis-split) blocks L3 even though the
        target sits outside this row's own address range by levels.py's own narrower heuristic --
        the ledger's classification is the authoritative one."""
        r, text, raw_text, promoted, sweeps = self._row_ready_for_l3()
        split_idx = {(r["id"], "func_80098765"): "intra"}
        rec = L.evaluate_row(r, text, raw_text, promoted, sweeps, split_idx)
        self.assertEqual(rec["level"], 2)
        self.assertEqual(rec["tail_jumps"], 1)
        self.assertEqual(rec["split_audit"], ["intra"])

    def test_unresolved_audit_record_also_caps_at_l2(self):
        r, text, raw_text, promoted, sweeps = self._row_ready_for_l3()
        split_idx = {(r["id"], "func_80098765"): "unresolved"}
        rec = L.evaluate_row(r, text, raw_text, promoted, sweeps, split_idx)
        self.assertEqual(rec["level"], 2)

    def test_missing_audit_record_caps_at_l2(self):
        """No ledger/split_audit.jsonl at all: every tail-jump dependency is unaudited."""
        r, text, raw_text, promoted, sweeps = self._row_ready_for_l3()
        rec = L.evaluate_row(r, text, raw_text, promoted, sweeps, {})
        self.assertEqual(rec["level"], 2)
        self.assertEqual(rec["split_audit"], ["missing"])

    def test_extern_jal_record_reaches_l3_but_not_l4(self):
        r, text, raw_text, promoted, sweeps = self._row_ready_for_l3()
        split_idx = {(r["id"], "func_80098765"): "extern-jal"}
        rec = L.evaluate_row(r, text, raw_text, promoted, sweeps, split_idx)
        self.assertEqual(rec["level"], 3)              # audited, not intra/unresolved: L3 clears
        self.assertEqual(rec["split_audit"], ["extern-jal"])
        self.assertIn("tail_jump", rec["l4_residue"])  # L4 tolerates NO tail-jump dependency at all
        self.assertNotIn("pins", rec["l4_residue"])
        self.assertNotIn("not_in_module", rec["l4_residue"])

    def test_no_tail_jump_dependency_reaches_l4(self):
        r = row()
        text = "s32 %s(s32 a) { return a + 1; }" % r["func"]
        rec = L.evaluate_row(r, text, "different", {r["id"]},
                              {"l4_modules": {r["id"]: {}}}, {})
        self.assertEqual(rec["tail_jumps"], 0)
        self.assertEqual(rec["level"], 5)              # nothing else blocking either

    def test_cross_segment_record_reaches_l3_but_not_l4(self):
        """`cross-segment` (tools/split_audit.py, 2026-09-22): the target address is not inside the
        declaring row's own segment run, so the container cannot say what is there and no foreign
        segment's jumps may be attributed to it.  That is a decided verdict -- NOT a mis-split of
        this row -- so it clears L3 exactly like `extern-jal`, and like every tail-jump dependency
        it still blocks L4.  Evidence: docs/evidence/split_fragments_20260922.md §4."""
        r, text, raw_text, promoted, sweeps = self._row_ready_for_l3()
        split_idx = {(r["id"], "func_80098765"): "cross-segment"}
        kinds, ok = L.audit_gate(r["id"], ["func_80098765"], split_idx)
        self.assertEqual((kinds, ok), (["cross-segment"], True))
        rec = L.evaluate_row(r, text, raw_text, promoted, sweeps, split_idx)
        self.assertEqual(rec["level"], 3)
        self.assertEqual(rec["split_audit"], ["cross-segment"])
        self.assertIn("tail_jump", rec["l4_residue"])

    def test_pins_block_l4_even_when_swept_for_l1(self):
        """PLAN.md: 'a row can sit at L3 with pins' -- the t2_pins sweep lets a pinned row still
        clear L1.  L4 must not inherit that loophole: pins == 0 is strict there."""
        r = row()
        text = '#include "common.h"\ns32 %s(s32 a) {\n    ASM_KEEP(a);\n    return a + 1;\n}\n' % r["func"]
        sweeps = {"l4_modules": {r["id"]: {}}, "t2_pins": {r["id"]: {}}}
        rec = L.evaluate_row(r, text, "different", {r["id"]}, sweeps, {})
        self.assertGreater(rec["pins_left"], 0)
        self.assertEqual(rec["level"], 3)              # L1 (swept)/L2/L3 all clear; L4 does not
        self.assertIn("pins", rec["l4_residue"])


class LabelAsCallExemption(unittest.TestCase):
    """Owner ruling 2026-09-22 (afternoon, docs/PIN_CAMPAIGN_CHARTER.md "Rulings 2026-09-22
    (afternoon, goal round)"): a LABEL_AS_CALL site whose target carries a DECIDED
    cross-segment/cross-image split_audit record for THIS row is a real inter-module jump, not
    scaffolding for this row, so it no longer counts toward `blocking` (L0) -- L4 is unchanged, the
    same target is still a tail-jump dependency (tail_jumps counts it) so it still blocks L4.  The
    real row this fixed: town/func_8047E0D8 (target func_80016120, kind cross-segment).

    census.audit_sites() caches the baseline site list in a module-level `_SITES` dict; there is no
    real baseline entry for the synthetic row id these tests use, so a fake one is injected here
    (same pattern as L._CONTAINER_SYMS elsewhere in this file) and restored in tearDown so it
    cannot leak into SpellingShims/TailJumpLadder, which read the real file through the same row id."""

    def setUp(self):
        L._CONTAINER_SYMS["dungeon"] = set()
        import census
        self._census = census
        self._orig_sites = census._SITES
        # target shared with TEXT_TAILJUMP: the same call also makes it a tail_jump_targets member
        # (noreturn declared + called), so tail_jumps == 1 and the L4 gate is exercised for real.
        census._SITES = {"dungeon/func_80091234": ["LABEL_AS_CALL|func_80098765|0"]}

    def tearDown(self):
        self._census._SITES = self._orig_sites

    def _row_ready_for_l3(self):
        r = row()
        text = TEXT_TAILJUMP.format(name=r["func"])
        raw_text = "not the same text"
        promoted = {r["id"]}
        sweeps = {"l4_modules": {r["id"]: {}}}
        return r, text, raw_text, promoted, sweeps

    def test_cross_segment_record_exempts_the_site_reaches_l3_not_l4(self):
        r, text, raw_text, promoted, sweeps = self._row_ready_for_l3()
        split_idx = {(r["id"], "func_80098765"): "cross-segment"}
        rec = L.evaluate_row(r, text, raw_text, promoted, sweeps, split_idx)
        self.assertFalse(rec["blocking"])
        self.assertEqual(rec["level"], 3)
        self.assertEqual(rec["tail_jumps"], 1)
        self.assertIn("tail_jump", rec["l4_residue"])

    def test_intra_record_on_the_same_site_still_blocks(self):
        """The ledger's classification is authoritative (same principle as
        test_intra_audit_record_caps_at_l2 above): `intra` is a confirmed mis-split, not a decided
        inter-module jump, so the LABEL_AS_CALL site keeps blocking and the row stays at L0."""
        r, text, raw_text, promoted, sweeps = self._row_ready_for_l3()
        split_idx = {(r["id"], "func_80098765"): "intra"}
        rec = L.evaluate_row(r, text, raw_text, promoted, sweeps, split_idx)
        self.assertTrue(rec["blocking"])
        self.assertEqual(rec["level"], 0)

    def test_unresolved_record_on_the_same_site_still_blocks(self):
        r, text, raw_text, promoted, sweeps = self._row_ready_for_l3()
        split_idx = {(r["id"], "func_80098765"): "unresolved"}
        rec = L.evaluate_row(r, text, raw_text, promoted, sweeps, split_idx)
        self.assertTrue(rec["blocking"])
        self.assertEqual(rec["level"], 0)

    def test_missing_record_on_the_same_site_still_blocks(self):
        """No split_audit record at all for this target: the exemption never fires on a bare
        LABEL_AS_CALL site, only on a DECIDED cross-segment/cross-image one."""
        r, text, raw_text, promoted, sweeps = self._row_ready_for_l3()
        rec = L.evaluate_row(r, text, raw_text, promoted, sweeps, {})
        self.assertTrue(rec["blocking"])
        self.assertEqual(rec["level"], 0)


class SpellingShims(unittest.TestCase):
    """levels.resolve_spellings: the three ways the pre-preprocessor scans used to be fooled
    (docs/evidence/split_fragments_20260922.md).  Every one of these was measured on a real row
    before being fixed; the rows are named in each docstring."""

    def setUp(self):
        L._CONTAINER_SYMS["dungeon"] = set()

    def test_define_alias_is_expanded_to_the_true_spelling(self):
        """src/dungeon/func_80BD3BA8.c: a true-base landing left `#define func_<legacy>
        func_<true>` shims.  The legacy spelling is 0x12000 above the real label, so the target
        looked external (and tools/split_audit.py resolved it into a FOREIGN overlay segment and
        reported that segment's jumps).  Expanded, it is a label inside the row's own extent, i.e.
        an intra pseudo-call -- which is what blocks L1."""
        # a SYNTHETIC id (this file reads the real config/decomp_audit_baseline.json through
        # live_audit; a real row id would pull that row's live fidelity sites into the result).
        # intra_tail_calls keys on true_name, which is the real one, so the extent check is real.
        r = row(id="dungeon/func_80BD0000", size=0x634, true_name="func_8015F3A8")
        text = ("#define func_801717E4 func_8015F7E4\n"
                "extern void func_801717E4() __attribute__((noreturn));\n"
                "extern void func_8015F7E4() __attribute__((noreturn));\n"
                "void func_8015F3A8(s32 a) {\n"
                "    func_801717E4(a);\n"
                "}\n")
        self.assertEqual(L.tail_jump_targets(r, text), ["func_8015F7E4"])
        self.assertEqual(L.intra_tail_calls(r, text), 1)          # 0x8015F7E4 is inside the row
        # and the pseudo-call to its own label is what caps the row below L1
        rec = L.evaluate_row(r, text, "different", {r["id"]}, {"l4_modules": {r["id"]: {}}},
                             {(r["id"], "func_8015F7E4"): "intra"})
        self.assertTrue(rec["blocking"])
        self.assertEqual(rec["level"], 0)

    def test_returning_shim_no_longer_hides_a_container_list_dependency(self):
        """src/dungeon/func_80CEB850.c (`#define`) and src/dungeon/func_81898B70.c (`__asm__(".set
        …")`): `func_X_returning(` never matches `func_[0-9A-F]{8}\\s*\\(`, so a call of a symbol on
        the container's noreturn list demanded no split_audit record at all.  Both spellings of the
        shim must resolve to the symbol they really call."""
        r = row()
        L._CONTAINER_SYMS["dungeon"] = {"func_80099999"}
        define_form = ("#define func_80099999_returning func_80099999\n"
                       "extern s32 func_80099999_returning();\n"
                       "s32 %s(s32 a) {\n    return func_80099999_returning(a);\n}\n" % r["func"])
        set_form = ('__asm__(".set func_80099999_returning, func_80099999");\n'
                    "extern s32 func_80099999_returning();\n"
                    "s32 %s(s32 a) {\n    return func_80099999_returning(a);\n}\n" % r["func"])
        for name, text in (("#define", define_form), (".set", set_form)):
            with self.subTest(shim=name):
                self.assertEqual(L.tail_jump_targets(r, text), ["func_80099999"])

    def test_function_pointer_table_entry_is_not_a_call(self):
        """src/dungeon/func_818FE800.c: a `(*const NAME[])(void)` jump table lists the ADDRESSES of
        casesi labels, and in an overlay those routinely land inside another row's function
        (func_80025DF4 is func_80024F10's shared epilogue).  A table entry is not a call, so it
        must never become a tail-jump dependency -- not even when the symbol is on the container's
        noreturn/sibcall list."""
        r = row()
        L._CONTAINER_SYMS["dungeon"] = {"func_80025DF4", "func_80025D90"}
        text = ("extern void func_80025DF4(void);\n"
                "extern void func_80025D90(void);\n"
                "static void (*const bank[])(void)\n"
                "    __attribute__((section(\".text.func_80024000\"))) = {\n"
                "    func_80025DF4, func_80025D90,\n"
                "};\n"
                "s32 %s(s32 a) {\n    return a + 1;\n}\n" % r["func"])
        self.assertEqual(L.tail_jump_targets(r, text), [])
        # a real call of the same symbol still counts -- the table blank must not swallow the body
        called = text.replace("    return a + 1;", "    func_80025DF4();\n    return a + 1;")
        self.assertEqual(L.tail_jump_targets(r, called), ["func_80025DF4"])

    def test_resolve_spellings_preserves_line_count(self):
        """Every caller zips this text against pin_census.arm_labels(text), which is per-line, so
        a rewrite that dropped or added a line would silently misattribute preprocessor arms."""
        text = ("#define func_801717E4 func_8015F7E4\n"
                "static void (*const bank[])(void) = {\n"
                "    func_80025DF4,\n"
                "    func_80025D90,\n"
                "};\n"
                "void f(void) { func_801717E4(); }\n")
        out = L.resolve_spellings(text)
        self.assertEqual(len(out.splitlines()), len(text.splitlines()))
        self.assertIn("func_8015F7E4", out)
        self.assertNotIn("func_801717E4", out)


class SegmentRuns(unittest.TestCase):
    """tools/split_audit.py Segments.run(): a row's delta is only valid inside its own merged
    same-delta run.  Outside it the same file offset belongs to a different overlay segment, which
    is what the `cross-segment` kind records instead of that other segment's jumps."""

    def _segments(self, spans):
        import split_audit as SA
        s = SA.Segments.__new__(SA.Segments)        # no config/ or image read
        s.known = spans
        s.kstarts = [x[0] for x in spans]
        s.starts = [x[0] for x in spans]
        s.spans = [tuple(x) for x in spans]
        return s

    def test_run_is_none_outside_every_span_and_delta_agrees(self):
        s = self._segments([(0x1000, 0x2000, 0x70000000), (0x5000, 0x6000, 0x71000000)])
        self.assertEqual(s.run(0x1000), (0x1000, 0x2000, 0x70000000))
        self.assertEqual(s.run(0x1FFF), (0x1000, 0x2000, 0x70000000))
        self.assertIsNone(s.run(0x2000))            # the gap between two different-delta runs
        self.assertEqual(s.run(0x5500), (0x5000, 0x6000, 0x71000000))
        self.assertIsNone(s.run(0x9999))
        for foff in (0x1000, 0x1FFF, 0x2000, 0x5500, 0x9999):
            r = s.run(foff)
            self.assertEqual(s.delta(foff), None if r is None else r[2])

    def test_a_target_in_another_run_is_not_in_the_rows_own_run(self):
        """The dungeon/func_80BD3BA8 shape: the row's run and the arithmetic target offset are in
        two different runs with two different deltas, so the code at that offset links at a
        different address entirely and none of its jumps belong to the target."""
        row_run, other = (0xBF3060, 0xBF6E34, 0x7F56B800), (0xC05060, 0xC08E34, 0x7F547800)
        s = self._segments([row_run, other])
        target_foff = (0x801717E4 - row_run[2]) & 0xFFFFFFFF
        self.assertEqual(s.run(0xBF3BA8), row_run)                 # the declaring row
        self.assertFalse(row_run[0] <= target_foff < row_run[1])   # -> cross-segment
        self.assertEqual(s.run(target_foff), other)
        self.assertEqual((target_foff + other[2]) & 0xFFFFFFFF, 0x8014D7E4)   # not 0x801717E4


if __name__ == "__main__":
    unittest.main()
