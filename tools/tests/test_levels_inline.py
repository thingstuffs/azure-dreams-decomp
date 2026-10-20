"""LL7 inlined fragments: a member of a merged TU is evaluated on ITS OWN fragment (plus the module
context levels.main appends), and the void-callee exemption finds a (void) callee defined in a
merged/moved TU by layout identity, not by the TU's file stem.

Regression: dungeon/func_800A204C (update_floor_object_motion) fell L3 -> L0 at the LL7 landing:
its byte-derived PASSTHRU_NO_ARGS site (callee find_first_empty_floor_item_slot, func_800A71F4,
reached through the module header's `free_entry_short(void) __asm__("func_800A71F4")`) stopped
being exempt because census.void_exact_targets keyed the callee's baseline verdict by
`<container>/<file stem>` = `dungeon/effect`, and row_view read the whole 21-member TU.

Synthetic temporary root only; no repository file is read or written.
    python3 -m unittest tools.tests.test_levels_inline
"""
import hashlib, json, os, sys, tempfile, unittest
from pathlib import Path
from unittest.mock import patch

sys.path.insert(0, os.path.join(os.path.dirname(__file__), ".."))
import levels as L        # noqa: E402
import census as C        # noqa: E402
import call_arity as A    # noqa: E402

TU = "src/dungeon/actor/fx/fx.c"
CALLEE = ("dungeon/func_80098000", '#include "dungeon/actor/fx/fx.h"\n', '#include "fx_old.h"\n',
          "/* the free-slot finder */\ns32 find_empty_slot(void) {\n    return -1;\n}\n")
CALLER = ("dungeon/func_80091234", '#include "common.h"\n', '#include "common.h"\n',
          "void update_motion(s32 *p) {\n    s32 slot;\n    slot = free_entry_short();\n"
          "    if (slot >= 0) {\n        *p = slot;\n    }\n}\n")
SIBLING = ("dungeon/func_80092000", '#include "common.h"\n', '#include "common.h"\n',
           "void spin_wait(void) {\n    __asm__ volatile(\"nop\");\n}\n")
# levels.main appends the module's shared headers: the abi alias gives the empty call its identity
CONTEXT = 's16 free_entry_short(void) __asm__("func_80099000");\n'
SITE = "PASSTHRU_NO_ARGS|func_80099000|0"


def build(root, members=(CALLEE, CALLER, SIBLING)):
    for d in ("config", "ledger", "src/dungeon/actor/fx"):
        (root / d).mkdir(parents=True, exist_ok=True)
    data, inline, rows, layout, frozen, base = b"", [], [], [], [], []
    for order, (rid, include, original_include, body) in enumerate(members):
        func = rid.split("/")[1]
        piece = (include + body).encode()
        first = (original_include + body).encode()
        inline.append({"tu_old": "src/dungeon/modules/fx.c", "tu_new": TU, "member": f"src/dungeon/{func}.c",
                       "member_id": rid, "manifest_key": "fx", "order": order, "offset": len(data),
                       "source_sha256": hashlib.sha256(first).hexdigest(), "bytes": len(first),
                       "inlined_bytes": len(piece), "original_includes": [original_include.split('"')[1]]})
        data += piece
        rows.append({"id": rid, "container": "dungeon", "kind": "overlay", "func": func,
                     "true_name": "func_80099000" if rid == CALLEE[0] else None, "defs": None,
                     "size": 64, "c_path": f"overlays/dungeon/first_pass_matched/{func}.c", "stock": True})
        layout.append({"id": rid, "path": TU})
        # the caller's landed body differs from its first pass; the others are first-pass text
        frozen.append({"path": f"raw/dungeon/{func}.c", "size": 0, "sha256": hashlib.sha256(
            first if rid != CALLER[0] else b"first pass").hexdigest()})
        base.append({"id": rid, "exact": True})
    (root / TU).write_bytes(data)
    for name, recs in (("ledger/rows.jsonl", rows), ("ledger/layout.jsonl", layout),
                       ("ledger/layout_inline.jsonl", inline), ("config/frozen_raw.jsonl", frozen),
                       ("ledger/baseline.jsonl", base)):
        (root / name).write_text("".join(json.dumps(r) + "\n" for r in recs))
    (root / "config/names.tsv").write_text("0x80099000\tfunc_80099000\tfind_empty_slot\ttest\n")
    return {r["id"]: r for r in rows}


class InlinedFragments(unittest.TestCase):
    def _run(self, fn):
        with tempfile.TemporaryDirectory() as td:
            root = Path(td)
            by_id = build(root)
            with patch.multiple(C, ROOT=root, LEDGER=root / "ledger", _VOID_EXACT_TARGETS=None,
                                _DECLARED_VOID=None, _SITES={"dungeon/func_80091234": [SITE]}), \
                 patch.multiple(A, ROOT=root, _NAMES=None, _DEFIDX=None), \
                 patch.object(A, "rows", return_value=[]), \
                 patch.object(L, "ROOT", root), \
                 patch.object(L, "_CONTAINER_SYMS", {"dungeon": set()}), \
                 patch.object(L, "_FID", (set(), {})):
                return fn(root, by_id)

    @staticmethod
    def _level(root, by_id, rid, context=""):
        er, text, raw = L.row_view(by_id[rid], by_id, root=root)
        if context:
            text += "\n" + context; raw += "\n" + context
        return text, raw, L.evaluate_row(er, text, raw, set(by_id), {}, {})

    def test_void_callee_in_merged_tu_clears_passthru_no_args(self):
        def check(root, by_id):
            self.assertIn("func_80099000", C.void_exact_targets())   # by layout identity, not stem "fx"
            _, _, rec = self._level(root, by_id, CALLER[0], CONTEXT)
            self.assertFalse(rec["blocking"])
            self.assertEqual(rec["level"], 3)
        self._run(check)

    def test_member_text_is_its_own_fragment(self):
        def check(root, by_id):
            text, raw, rec = self._level(root, by_id, CALLER[0], CONTEXT)
            self.assertNotIn("spin_wait", text)                    # no sibling body
            self.assertNotIn("find_empty_slot", text)
            self.assertIn("update_motion", text)
            # a sibling's inline asm is not this row's residue
            text, raw, rec = self._level(root, by_id, CALLEE[0])
            self.assertNotIn("inline_asm", rec["l5_residue"])
            text, raw, rec = self._level(root, by_id, SIBLING[0])
            self.assertIn("inline_asm", rec["l5_residue"])
        self._run(check)

    def test_first_pass_equality_restores_include_spelling(self):
        def check(root, by_id):
            # the callee's fragment is its untouched first pass under a relocated include spelling
            text, raw, rec = self._level(root, by_id, CALLEE[0])
            self.assertEqual(text, raw)
            self.assertEqual(rec["level"], 2)                    # no Layer-2 pass: stays L2
            text, raw, rec = self._level(root, by_id, CALLER[0], CONTEXT)
            self.assertNotEqual(text, raw)
        self._run(check)

    def test_non_void_or_inexact_callee_still_blocks(self):
        def check(root, by_id):
            base = [{"id": CALLEE[0], "exact": False}, {"id": CALLER[0], "exact": True}]
            (root / "ledger/baseline.jsonl").write_text("".join(json.dumps(b) + "\n" for b in base))
            self.assertNotIn("func_80099000", C.void_exact_targets())
            _, _, rec = self._level(root, by_id, CALLER[0], CONTEXT)
            self.assertTrue(rec["blocking"])
            self.assertEqual(rec["level"], 0)
        self._run(check)


if __name__ == "__main__":
    unittest.main()
