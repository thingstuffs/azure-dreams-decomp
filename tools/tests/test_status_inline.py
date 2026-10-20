"""Status shape attribution follows LL7 row spans, including placement bytes."""
import sys
import tempfile
import unittest
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import status
from tools.tests.test_levels_inline import build, TU, CALLEE


class StatusInlineTests(unittest.TestCase):
    def test_sibling_constructs_do_not_leak_into_row_facts(self):
        members = [
            ("dungeon/func_80098000", '#include "common.h"\n', '#include "common.h"\n', "void clean(void) { return; }\n"),
            ("dungeon/func_80091234", '#include "common.h"\n', '#include "common.h"\n', "void branch(void) { goto done; done:; }\n"),
            ("dungeon/func_80092000", '#include "common.h"\n', '#include "common.h"\n', 'void barrier(void) { do { __asm__("nop"); } while (0); }\n'),
        ]
        with tempfile.TemporaryDirectory() as td:
            root = Path(td)
            rows = build(root, members)
            texts = [status.current_shape_text(r, root) for r in rows.values()]
            self.assertEqual(texts, [m[1] + m[3] for m in members])
            self.assertNotIn("goto", texts[0])
            self.assertNotIn("__asm__", texts[1])
            placement = dict(next(iter(rows.values())), id="dungeon/func_80093000",
                             source_row=members[0][0])
            self.assertIsNone(status.current_shape_text(placement, root))
            facts = {rid: {"gotos": int("goto" in t)} for rid, t in zip(rows, texts)}
            rows[placement["id"]] = placement
            self.assertEqual(status.placed_shapes(lambda c: c["gotos"], facts, rows), [])
            placement["source_row"] = members[1][0]
            self.assertEqual(status.placed_shapes(lambda c: c["gotos"], facts, rows), [placement])

    def test_whole_file_and_missing_file_keep_existing_behavior(self):
        with tempfile.TemporaryDirectory() as td:
            root = Path(td)
            rows = build(root, (CALLEE,))
            (root / "ledger/layout_inline.jsonl").write_text("")
            row = next(iter(rows.values()))
            self.assertEqual(status.current_shape_text(row, root), (root / TU).read_text())
            (root / TU).unlink()
            self.assertIsNone(status.current_shape_text(row, root))


if __name__ == "__main__":
    unittest.main()
