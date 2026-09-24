"""A module member's scope is its definitions, even when it declares sibling prototypes."""

import contextlib
import io
import os
import sys
import tempfile
import unittest
from pathlib import Path
from unittest.mock import patch

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))
sys.path.insert(0, str(ROOT / "tools/fidelity"))

import aspsx_diff as A
import registry
import row_db
import slus_module_context as context
from objread import Obj
from verify import DEF_SYM


OWNED = "func_8003C634"
EXTERNAL = "func_8003C758"
SOURCE = (
    f"extern int {EXTERNAL}(void);\n"
    f"int {OWNED}(void) {{ return {EXTERNAL}(); }}\n"
)


def module(functions):
    return {
        "name": "directory",
        "members": [{"id": "slus/w_8003C634", "source": "src/w_8003C634.c",
                     "functions": functions}],
    }


class RowDatabaseMemberScope(unittest.TestCase):
    def setUp(self):
        self.temp = tempfile.TemporaryDirectory()
        self.addCleanup(self.temp.cleanup)
        self.root = Path(self.temp.name)
        (self.root / "raw/slus").mkdir(parents=True)
        (self.root / "ledger/splits").mkdir(parents=True)
        (self.root / "raw/slus/w_8003C634.c").write_text(SOURCE)
        (self.root / "ledger/splits/slus.build.ninja").write_text("")

    def check(self, functions):
        # The registry may list a prototype as a def. The module contract is checked
        # against actual raw C definitions rather than that derived metadata.
        row = {"id": "slus/w_8003C634", "defs": [OWNED, EXTERNAL]}
        with patch.object(row_db, "ROOT", self.root), \
             patch.object(row_db, "RAW", self.root / "raw"), \
             patch.object(row_db, "SPLITS", self.root / "ledger/splits"), \
             patch.object(row_db, "CONTAINERS", ()), \
             patch.object(row_db, "slus_edges", return_value=[]), \
             patch.object(row_db, "read_jsonl", return_value=[]), \
             patch.object(row_db, "window_map", return_value={}), \
             patch.object(context, "modules", return_value=[module(functions)]), \
             patch.object(context, "input_paths", return_value=[]), \
             patch.object(registry, "slus_rows", return_value=[row]), \
             contextlib.redirect_stdout(io.StringIO()) as output:
            with self.assertRaises(SystemExit) as exc:
                row_db.cmd_check(None)
        return exc.exception.code, output.getvalue()

    def test_external_prototype_is_not_a_member_definition(self):
        self.assertEqual(DEF_SYM.findall(SOURCE), [OWNED])
        self.assertEqual(self.check([OWNED])[0], 0)

    def test_manifest_must_name_the_actual_definition(self):
        for claimed in ([OWNED, EXTERNAL], [EXTERNAL]):
            with self.subTest(claimed=claimed):
                status, output = self.check(claimed)
                self.assertEqual(status, 1)
                self.assertIn("module member definitions differ", output)


class DifferentialMemberScope(unittest.TestCase):
    def setUp(self):
        self.temp = tempfile.TemporaryDirectory()
        self.addCleanup(self.temp.cleanup)
        self.root = Path(self.temp.name)
        self.source = self.root / "w_8003C634.c"
        self.source.write_text(SOURCE)
        self.row = {"id": "slus/w_8003C634", "container": "slus", "kind": "slus",
                    "cfg": "2.7.2-cdk", "defs": [OWNED, EXTERNAL]}

    def run_row(self, functions):
        obj = Obj("elf")
        obj.sections[".text"] = b"\x08\x00\xe0\x03\x00\x00\x00\x00"
        obj.symbols[OWNED] = (".text", 0, "func", 8)
        ctx = {"kind": "slus", "as_args": ["as"] * 7, "cell": "2.7.2-cdk",
               "maspsx_exact": True, "proof": "object", "env": {}, "m_in": b"",
               "pipeline_obj": b"object", "g_src": b"", "flags": []}
        scopes = []

        def run_maspsx(_source, _args, _out, _env, trace):
            Path(trace).write_text('{"fired": []}')
            return b"object", None

        def retail_compare(_view, scope, _kind, _ctx):
            scopes.append(scope)
            return {"diff": 0, "masked": 0, "checked": len(scope)}

        with patch.object(A, "TMP", self.root), \
             patch.object(tempfile, "tempdir", tempfile.tempdir), \
             patch.dict(os.environ, {}), \
             patch.object(A, "prepare_slus", return_value=(ctx, None)), \
             patch.object(A, "run_maspsx", side_effect=run_maspsx), \
             patch.object(A, "read_elf", return_value=obj), \
             patch.object(A, "retail_compare", side_effect=retail_compare), \
             patch.object(A, "aspsx_input", return_value=b""), \
             patch.object(A, "aliases", return_value={}), \
             patch.object(A, "genuine_modes", return_value=([], False)), \
             patch.object(A, "VERSIONS", []), \
             patch.object(context, "membership", return_value=module(functions)), \
             patch.object(context, "fingerprint", return_value="module-fingerprint"):
            result = A.process_row(self.row, cfile=self.source)
        return result, scopes

    def test_comparison_scopes_only_manifest_member_functions(self):
        result, scopes = self.run_row([OWNED])
        self.assertEqual(result["status"], "ok", result.get("err"))
        self.assertEqual(result["funcs"], 1)
        self.assertEqual(result["words"], 2)
        self.assertEqual(scopes, [[OWNED]])
        self.assertEqual(result["module_fingerprint"], "module-fingerprint")

    def test_missing_manifest_function_is_still_an_error(self):
        result, scopes = self.run_row([EXTERNAL])
        self.assertEqual(result["status"], "error")
        self.assertIn("module member symbols missing", result["err"])
        self.assertIn(EXTERNAL, result["err"])
        self.assertEqual(scopes, [])


if __name__ == "__main__":
    unittest.main()
