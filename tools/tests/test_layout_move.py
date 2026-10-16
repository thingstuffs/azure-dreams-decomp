"""A move changes layout/physical references together; export itself is read-only."""
import json
from pathlib import Path
import sys
import tempfile
import unittest
from unittest.mock import patch
ROOT = Path(__file__).resolve().parents[2]
sys.path[:0] = [str(ROOT / "tools"), str(ROOT / "tools/lanes")]
import source_layout as L
import guarded_package as P
import layout_move as M
import package_preflight as F


class MoveTest(unittest.TestCase):
    def setUp(self):
        self.tmp = tempfile.TemporaryDirectory()
        self.addCleanup(self.tmp.cleanup)
        self.root = Path(self.tmp.name) / "root"
        self.package = Path(self.tmp.name) / "package"
        self.rows = [{"id": "dungeon/func_A", "container": "dungeon", "c_path": "overlays/x/func_A.c"},
                     {"id": "dungeon/func_B", "container": "dungeon", "c_path": "overlays/x/func_B.c"}]
        self.module = {"key": "sample", "name": "sample.c", "container": "dungeon",
                       "source": "src/dungeon/modules/sample.c", "headers": ["include/modules/sample.h"],
                       "members": [{"id": r["id"], "source": L.flat_relative(r)} for r in self.rows],
                       "review": {"reviewer": "fixture"}}
        files = {
            "ledger/rows.jsonl": "".join(json.dumps(r) + "\n" for r in self.rows),
            "ledger/layout.jsonl": "".join(json.dumps({"id": r["id"], "path": L.flat_relative(r)}) + "\n" for r in self.rows),
            "config/overlays/modules.json": json.dumps({"modules": [self.module]}),
            "ledger/modules/overlay_sample.json": "{}",
            "config/layout_proposal.tsv": "container\tmodule_group\tproposed_dir\ndungeon\tsample.c\tsrc/dungeon/banks/sel_21/sample\n",
            "src/dungeon/func_A.c": '#include "modules/sample.h"\nvoid a(void) {}\n',
            "src/dungeon/func_B.c": '#include "modules/sample.h"\nvoid b(void) {}\n',
            "src/dungeon/modules/sample.c": '#include "../func_A.c"\n#include "../func_B.c"\n',
            "include/modules/sample.h": "/* shared contract */\n",
        }
        for name, text in files.items():
            p = self.root / name
            p.parent.mkdir(parents=True, exist_ok=True)
            p.write_text(text)
        self.addCleanup(patch.stopall)
        patch("gate.overlay_module_gate.load_modules", return_value=[self.module]).start()
        patch("overlay_module_evidence.certificate_reason", return_value=None).start()

    def snapshot(self):
        return {p.relative_to(self.root).as_posix(): p.read_bytes()
                for p in self.root.rglob("*") if p.is_file()}

    def test_plan_export_dry_run_and_apply(self):
        before = self.snapshot()
        changes, meta = M.plan("sample", self.root)
        self.assertEqual(before, self.snapshot())
        self.assertEqual(meta["certificates_requiring_renewal"], ["sample"])
        P.export(self.package, self.root, changes, meta)
        self.assertEqual(before, self.snapshot())
        self.assertGreater(F.lint_inventory(self.package / "apply.py", self.root)["sources"], 5)
        P.apply(self.package, self.root, live=True, dry_run=True)
        self.assertEqual(before, self.snapshot())
        P.apply(self.package, self.root, live=True)
        self.assertFalse((self.root / "src/dungeon/func_A.c").exists())
        new = L.row_path(self.rows[0], self.root)
        self.assertEqual(new, self.root / "src/dungeon/banks/sel_21/sample/func_A.c")
        self.assertIn('"dungeon/banks/sel_21/sample/sample.h"', new.read_text())
        self.assertEqual((new.parent / "sample.c").read_text(), '#include "func_A.c"\n#include "func_B.c"\n')
        self.assertEqual(L.validate(self.root), 2)
        module = json.loads((self.root / "config/overlays/modules.json").read_text())["modules"][0]
        self.assertEqual(module["members"][0]["source"], new.relative_to(self.root).as_posix())
        projection = L.materialize_flat(self.root / "projection", self.root)
        self.assertEqual((projection / "dungeon/func_A.c").read_bytes(), new.read_bytes())

    def test_relative_unmoved_header_is_rebased(self):
        (self.root / "include/shared.h").write_text("typedef int Shared;\n")
        (self.root / "src/dungeon/func_A.c").write_text('#include "../../include/shared.h"\nvoid a(void) {}\n')
        changes, _ = M.plan("sample", self.root)
        relocated = changes["src/dungeon/banks/sel_21/sample/func_A.c"].decode()
        self.assertIn('#include "shared.h"', relocated)
        self.assertEqual((self.root / "src/dungeon/func_A.c").read_text(), '#include "../../include/shared.h"\nvoid a(void) {}\n')

    def test_stale_certificate_refused(self):
        with patch("overlay_module_evidence.certificate_reason", return_value="stale"):
            with self.assertRaisesRegex(ValueError, "certification"):
                M.plan("sample", self.root)

    def test_outside_consumer_refused_without_changes(self):
        p = self.root / "src/dungeon/consumer.c"
        p.write_text('#include "modules/sample.h"\n')
        before = self.snapshot()
        with self.assertRaisesRegex(ValueError, "outside consumer"):
            M.plan("sample", self.root)
        self.assertEqual(before, self.snapshot())

    def test_collision_and_file_macro_refused(self):
        target = self.root / "src/dungeon/banks/sel_21/sample/func_A.c"
        target.parent.mkdir(parents=True)
        target.write_text("collision")
        with self.assertRaisesRegex(ValueError, "destination exists"):
            M.plan("sample", self.root)
        target.unlink()
        (self.root / "src/dungeon/func_A.c").write_text("char *file = __FILE__;\n")
        with self.assertRaisesRegex(ValueError, "__FILE__"):
            M.plan("sample", self.root)

    def test_canonical_contract_and_protected_inputs(self):
        changes, meta = M.plan("sample", self.root)
        meta["protected_inputs"] = {"ledger/modules/overlay_sample.json": P.sha(self.root / "ledger/modules/overlay_sample.json")}
        P.export(self.package, self.root, changes, meta)
        with patch.dict("os.environ", {"LAND_LIVE_ROOT": str(self.root)}):
            with self.assertRaisesRegex(ValueError, "requires --live"):
                P.apply(self.package, self.root, dry_run=True)
            self.assertEqual(P.apply(self.package, self.root, live=True, dry_run=True)["status"], "dry-run")
        (self.root / "ledger/modules/overlay_sample.json").write_text('{"changed":true}')
        with self.assertRaisesRegex(ValueError, "protected input"):
            P.apply(self.package, self.root, live=True)


if __name__ == "__main__":
    unittest.main()
