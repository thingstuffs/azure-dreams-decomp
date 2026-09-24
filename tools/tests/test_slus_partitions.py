"""Contract tests for the SLUS collector partition planner and renderer."""

from __future__ import annotations

import copy
import hashlib
import json
import tempfile
import unittest
from pathlib import Path

import sys
sys.path.insert(0, str(Path(__file__).resolve().parents[1] / "build"))
import slus_partitions as P

A = "func_80030000"
B = "func_80030010"
C = "func_80030020"
OTHER_A = "func_80031000"
OTHER_B = "func_80032000"
D = "func_80030030"
E = "func_80030040"
F = "func_80030050"
OTHER_G = "func_80033000"
OTHER_D = "func_80034000"
RECIPE = {"ccver": "2.7.2-cdk", "ccflags": "", "asflags": ""}
SOURCE = f'''#include "common.h"
/* A fake function: int {A}(void) {{ return 99; }}; #include "phantom.c" */
const char *message = "braces {{ }} and {B}(void)";
int {A}(int x);
int named_second(void);
int {C}(void);

int {A}(
    int x
)
{{
    return x + 1;
}}

int named_second(
    void
)
{{
    return 2;
}}

int {C}(void)
{{
    return 3;
}}
'''


def parent(source: str = SOURCE) -> dict:
    return {
        "id": "slus/code", "source": "src/code.c",
        "raw_sha256": hashlib.sha256(source.encode()).hexdigest(),
        "recipe": dict(RECIPE), "functions": [A, B, C],
        "parts": [{"module": "alpha", "functions": [A]},
                  {"module": "beta", "functions": [B]}],
    }


def modules() -> list[dict]:
    return [
        {"name": "alpha", "source": "src/alpha.c", "recipe": dict(RECIPE),
         "headers": ["include/common.h"],
         "members": [{"id": "slus/a", "source": "src/a.c", "functions": [OTHER_A]}]},
        {"name": "beta", "source": "src/beta.c", "recipe": dict(RECIPE),
         "headers": ["include/common.h"],
         "members": [{"id": "slus/b", "source": "src/b.c", "functions": [OTHER_B]}]},
    ]


def connected_fixture():
    """code -> alpha/beta -> code2 -> gamma; delta is disconnected."""
    second = {
        "id": "slus/code2", "source": "src/code2.c", "raw_sha256": "0" * 64,
        "recipe": dict(RECIPE), "functions": [D, E, F],
        "parts": [{"module": "beta", "functions": [D]},
                  {"module": "gamma", "functions": [E]}],
    }
    owners = modules()
    owners[0]["recipe"] = {"ccver": "2.7.2", "ccflags": "", "asflags": ""}
    owners[1]["recipe"] = {"ccver": "2.8.1", "ccflags": "-G0", "asflags": ""}
    owners.extend([
        {"name": "gamma", "source": "src/gamma.c", "recipe":
         {"ccver": "2.95.2", "ccflags": "", "asflags": "-q"},
         "headers": ["include/other.h"],
         "members": [{"id": "slus/g", "source": "src/g.c", "functions": [OTHER_G]}]},
        {"name": "delta", "source": "src/delta.c", "recipe": dict(RECIPE),
         "headers": ["include/disconnected.h"],
         "members": [{"id": "slus/d", "source": "src/d.c", "functions": [OTHER_D]}]},
    ])
    return [parent(), second], owners


def edge() -> dict:
    return {"src": "src/code.c", "out": "build/src/code.o", **RECIPE}


class PartitionTest(unittest.TestCase):
    def setUp(self) -> None:
        self.temp = tempfile.TemporaryDirectory()
        self.addCleanup(self.temp.cleanup)
        self.root = Path(self.temp.name)
        self.plan_file = self.root / "plan.json"
        self.raw = self.root / "raw/slus"
        self.raw.mkdir(parents=True)
        (self.raw / "code.c").write_text(SOURCE)

    def load(self, parents=None):
        self.plan_file.write_text(json.dumps({"version": 1, "parents":
                                               [parent()] if parents is None else parents}))
        return P.load_plan(self.plan_file)

    def test_missing_optional_plan_and_valid_partition(self):
        self.assertEqual(P.load_plan(self.plan_file), [])
        self.assertEqual(self.load(), [parent()])

    def test_load_plan_rejects_schema_identity_and_ownership_ambiguity(self):
        cases = {}
        x = parent(); x["unexpected"] = 1; cases["extra parent key"] = [x]
        x = parent(); del x["raw_sha256"]; cases["missing parent key"] = [x]
        x = parent(); x["id"] = "slus/other"; cases["mismatched ID"] = [x]
        x = parent(); x["source"] = "src/../code.c"; cases["unsafe source"] = [x]
        x = parent(); x["functions"] = [A, A, C]; cases["duplicate original function"] = [x]
        x = parent(); x["functions"] = [A, "named_second", C]; cases["noncanonical function"] = [x]
        x = parent(); x["parts"] = []; cases["no owners"] = [x]
        x = parent(); x["parts"][0]["functions"] = ["func_80039999"]
        cases["unknown owned function"] = [x]
        x = parent(); x["parts"][0]["functions"] = [A, A]
        cases["duplicate inside owner"] = [x]
        x = parent(); x["parts"][1]["functions"] = [A]
        cases["duplicate across owners"] = [x]
        x = parent(); x["parts"][1]["module"] = "alpha"
        cases["duplicate owner module"] = [x]
        x = parent(); x["parts"][0]["functions"] = [A, C]
        cases["empty remainder"] = [x]
        cases["duplicate row ID"] = [parent(), parent()]
        x = parent(); x["id"] = "slus/other"; x["source"] = "src/other.c"
        x["functions"] = [A, "func_80039999"]
        x["parts"] = [{"module": "alpha", "functions": ["func_80039999"]}]
        cases["same original function across parents"] = [parent(), x]
        for label, parents in cases.items():
            with self.subTest(label=label), self.assertRaises(P.PartitionError):
                self.load(parents)

    def test_context_accepts_frozen_row_and_rejects_drift_or_overlap(self):
        plan = self.load()
        self.assertTrue(P.validate_context(plan, modules(), [edge()], self.raw, aliases={"named_second": B}))
        for original_functions in ([A, B], [A, B, C, "func_80039999"]):
            changed = copy.deepcopy(plan)
            changed[0]["functions"] = original_functions
            with self.subTest(frozen_functions=original_functions), self.assertRaisesRegex(
                    P.PartitionError, "frozen definitions"):
                P.validate_context(changed, modules(), [edge()], self.raw, aliases={"named_second": B})
        changed = copy.deepcopy(plan)
        changed[0]["recipe"]["ccver"] = "2.8.1"
        with self.assertRaisesRegex(P.PartitionError, "recipe drift"):
            P.validate_context(changed, modules(), [edge()], self.raw, aliases={"named_second": B})
        (self.raw / "code.c").write_text(SOURCE + "\n")
        with self.assertRaisesRegex(P.PartitionError, "frozen source mismatch"):
            P.validate_context(plan, modules(), [edge()], self.raw, aliases={"named_second": B})
        (self.raw / "code.c").write_text(SOURCE)
        changed = copy.deepcopy(plan)
        changed[0]["parts"][0]["module"] = "unknown"
        with self.assertRaisesRegex(P.PartitionError, "unknown destination"):
            P.validate_context(changed, modules(), [edge()], self.raw, aliases={"named_second": B})
        claimed = modules()
        claimed[0]["members"].append({"id": "slus/code", "source": "src/code.c",
                                        "functions": [C]})
        with self.assertRaisesRegex(P.PartitionError, "whole module member"):
            P.validate_context(plan, claimed, [edge()], self.raw, aliases={"named_second": B})
        claimed = modules()
        claimed[0]["members"][0]["functions"] = [A]
        with self.assertRaisesRegex(P.PartitionError, "also owned"):
            P.validate_context(plan, claimed, [edge()], self.raw, aliases={"named_second": B})
        claimed = modules()
        claimed[0]["source"] = "src/code.c"
        with self.assertRaisesRegex(P.PartitionError, "also a module aggregator"):
            P.validate_context(plan, claimed, [edge()], self.raw, aliases={"named_second": B})
        claimed = modules()
        claimed[0]["members"][0]["functions"] = [C]
        with self.assertRaisesRegex(P.PartitionError, "also owned"):
            P.validate_context(plan, claimed, [edge()], self.raw, aliases={"named_second": B})

    def test_render_preserves_nonfunctions_and_partitions_two_groups(self):
        with self.assertRaisesRegex(P.PartitionError, "coverage differs"):
            P.render_parent(parent(), SOURCE)
        rendered = P.render_parent(parent(), SOURCE, aliases={"named_second": B})
        self.assertEqual(set(rendered["parts"]), {"alpha", "beta"})
        self.assertEqual(set(P.spans(rendered["remainder"], {"named_second": B})), {C})
        self.assertEqual(set(P.spans(rendered["parts"]["alpha"])), {A})
        self.assertEqual(set(P.spans(rendered["parts"]["beta"], {"named_second": B})), {B})
        self.assertIn("A fake function", rendered["remainder"])
        self.assertIn('const char *message = "braces { }', rendered["remainder"])
        self.assertIn(f"int {A}(int x);", rendered["remainder"])
        self.assertIn("int named_second(void);", rendered["remainder"])
        self.assertEqual(rendered["remainder"].count("\n"), SOURCE.count("\n"))
        self.assertNotIn("A fake function", rendered["parts"]["alpha"])

    def test_render_rejects_missing_extra_duplicate_or_unsupported_C(self):
        cases = {
            "missing": SOURCE.replace(f"int {C}(void)\n{{\n    return 3;\n}}", ""),
            "extra": SOURCE + "\nint func_80030030(void) { return 4; }\n",
            "duplicate": SOURCE + f"\nint {A}(int y) {{ return y; }}\n",
            "conditional": "#if 1\n" + SOURCE + "#endif\n",
            "directive in body": SOURCE.replace("    return x + 1;", "#define X 1\n    return x + X;"),
            "nested C include": SOURCE + '\n#include "fragment.c"\n',
            "macro definition": SOURCE.replace(f"int {C}(void)\n{{\n    return 3;\n}}",
                                               f"#define MAKE_C() int {C}(void) {{ return 3; }}\nMAKE_C()"),
        }
        for label, source in cases.items():
            with self.subTest(label=label), self.assertRaises(P.PartitionError):
                P.render_parent(parent(), source, aliases={"named_second": B})

    def test_emitted_exact_coverage_and_fail_closed_controls(self):
        expected = P.expected_units([parent()], modules())
        self.assertEqual(expected, {"src/alpha.c": {OTHER_A, A},
                                    "src/beta.c": {OTHER_B, B}, "src/code.c": {C}})
        emitted = {unit: sorted(functions) for unit, functions in expected.items()}
        owners = P.check_emitted(expected, emitted)
        self.assertEqual(owners[A], "src/alpha.c")
        self.assertEqual(owners[C], "src/code.c")
        cases = {}
        x = copy.deepcopy(emitted); del x["src/code.c"]; cases["missing unit"] = x
        x = copy.deepcopy(emitted); x["src/extra.c"] = []; cases["extra unit"] = x
        x = copy.deepcopy(emitted); x["src/alpha.c"].remove(A); cases["missing function"] = x
        x = copy.deepcopy(emitted); x["src/alpha.c"].append(C); cases["extra function"] = x
        x = copy.deepcopy(emitted); x["src/alpha.c"].append(A); cases["duplicate in unit"] = x
        for label, actual in cases.items():
            with self.subTest(label=label), self.assertRaises(P.PartitionError):
                P.check_emitted(expected, actual)
        conflicting = {"src/alpha.c": {A}, "src/beta.c": {A}}
        with self.assertRaisesRegex(P.PartitionError, "multiple physical owners"):
            P.check_emitted(conflicting, {k: list(v) for k, v in conflicting.items()})

    def test_fingerprint_covers_sibling_header_recipe_and_partition(self):
        plan = [parent()]
        mod = modules()
        sources = {"src/code.c": SOURCE, "src/alpha.c": "owner A", "src/beta.c": "owner B",
                   "src/a.c": "member A", "src/b.c": "member B"}
        headers = {"include/common.h": "typedef int s32;"}
        before = P.fingerprint(plan, mod, sources, headers)
        self.assertEqual(before, P.fingerprint(copy.deepcopy(plan), copy.deepcopy(mod),
                                               dict(reversed(list(sources.items()))), dict(headers)))
        changed = dict(sources, **{"src/beta.c": "owner B changed"})
        self.assertNotEqual(before, P.fingerprint(plan, mod, changed, headers))
        self.assertNotEqual(before, P.fingerprint(plan, mod, sources,
                                                  {"include/common.h": "typedef long s32;"}))
        changed = copy.deepcopy(mod); changed[1]["recipe"]["ccver"] = "2.8.1"
        self.assertNotEqual(before, P.fingerprint(plan, changed, sources, headers))
        changed = copy.deepcopy(plan); changed[0]["parts"][1]["functions"] = [C]
        self.assertNotEqual(before, P.fingerprint(changed, mod, sources, headers))
        for missing in sources:
            with self.subTest(missing_source=missing), self.assertRaisesRegex(
                    P.PartitionError, "closure is incomplete"):
                P.fingerprint(plan, mod, {k: v for k, v in sources.items() if k != missing}, headers)
        with self.assertRaisesRegex(P.PartitionError, "closure is incomplete"):
            P.fingerprint(plan, mod, sources, {})
        alias = {"named_second": B}
        self.assertNotEqual(P.fingerprint(plan, mod, sources, headers, aliases=alias),
                            P.fingerprint(plan, mod, sources, headers,
                                          aliases={"named_second": C}))
        self.assertEqual(P.fingerprint(plan, mod, sources, headers, aliases=alias),
                         P.fingerprint(plan, mod, sources, headers,
                                       aliases=dict(reversed(list(alias.items())))))

    def test_connected_context_includes_transitive_parents_and_owners_only(self):
        plan, owners = connected_fixture()
        for row_id in ("slus/code", "slus/code2", "slus/b", "slus/g"):
            with self.subTest(row_id=row_id):
                parents, context = P.connected_context(row_id, plan, owners)
                self.assertEqual([p["id"] for p in parents], ["slus/code", "slus/code2"])
                self.assertEqual([m["name"] for m in context], ["alpha", "beta", "gamma"])
        self.assertEqual(P.connected_context("slus/unknown", plan, owners), ([], []))
        self.assertEqual(P.connected_context("slus/d", plan, owners), ([], [owners[3]]))

    def test_row_units_preserves_distinct_physical_recipes_and_scopes(self):
        plan, owners = connected_fixture()
        units = P.row_units("slus/code", plan, owners)
        self.assertEqual(units, [
            {"source": "src/code.c", "recipe": RECIPE, "functions": [C], "role": "remainder"},
            {"source": "src/alpha.c", "recipe": owners[0]["recipe"],
             "functions": [A], "role": "module", "module": "alpha"},
            {"source": "src/beta.c", "recipe": owners[1]["recipe"],
             "functions": [B], "role": "module", "module": "beta"},
        ])
        self.assertEqual(P.row_units("slus/code2", plan, owners), [
            {"source": "src/code2.c", "recipe": RECIPE, "functions": [F], "role": "remainder"},
            {"source": "src/beta.c", "recipe": owners[1]["recipe"],
             "functions": [D], "role": "module", "module": "beta"},
            {"source": "src/gamma.c", "recipe": owners[2]["recipe"],
             "functions": [E], "role": "module", "module": "gamma"},
        ])
        self.assertEqual(P.row_units("slus/b", plan, owners), [
            {"source": "src/beta.c", "recipe": owners[1]["recipe"],
             "functions": [OTHER_B], "role": "module", "module": "beta"},
        ])
        self.assertEqual(P.row_units("slus/unknown", plan, owners), [])



class BuildProjectionTest(unittest.TestCase):
    def test_projection_preserves_identity_and_rejects_bypass_drift_or_absence(self):
        plan=[parent()];paths=P.output_paths(plan)
        self.assertEqual(paths['remainders'],{'src/code.c':'build/partition_sources/code.c'})
        physical=dict(edge(),src=paths['remainders']['src/code.c'])
        self.assertEqual(P.project_edges([physical],plan),[edge()])
        for bad in ([],[edge()],[physical,physical],
                    [dict(physical,ccver='2.8.1')],
                    [dict(physical,out='build/src/renamed.o')]):
            with self.subTest(edges=bad),self.assertRaises(P.PartitionError):
                P.project_edges(bad,plan)
        for directory in ('src','build/../src','/tmp/out','build','build//parts'):
            with self.subTest(directory=directory),self.assertRaises(P.PartitionError):
                P.output_paths(plan,directory)

    def test_render_files_preserves_canonical_input_and_rejects_output_escape(self):
        with tempfile.TemporaryDirectory() as td, tempfile.TemporaryDirectory() as other:
            root=Path(td);(root/'src').mkdir();source=root/'src/code.c';source.write_text(SOURCE)
            paths=P.render_files([parent()],root,aliases={'named_second':B})
            self.assertEqual(source.read_text(),SOURCE)
            remainder=root/paths['remainders']['src/code.c']
            self.assertEqual(set(P.spans(remainder.read_text(),{'named_second':B})),{C})
            before=remainder.stat().st_mtime_ns
            P.render_files([parent()],root,aliases={'named_second':B})
            self.assertEqual(remainder.stat().st_mtime_ns,before)
            remainder.unlink();external=Path(other)/'victim.c';external.write_text('keep')
            remainder.symlink_to(external)
            with self.assertRaisesRegex(P.PartitionError,'escapes'):
                P.render_files([parent()],root,aliases={'named_second':B})
            self.assertEqual(external.read_text(),'keep')
            remainder.unlink()
            source.write_text(SOURCE.replace('return 3;','return 4;'))
            # Invalid source coverage prevents all writes, even to the first view.
            source.write_text(source.read_text()+f'\nint {C}(void) {{ return 8; }}\n')
            with self.assertRaises(P.PartitionError):
                P.render_files([parent()],root,aliases={'named_second':B})
            self.assertFalse(remainder.exists())

    def test_alias_reader_rejects_ambiguous_function_names(self):
        with tempfile.TemporaryDirectory() as td:
            p=Path(td)/'names.tsv';p.write_text(f'slus\t{A}\talpha\nslus\t{B}\tbeta\n')
            self.assertEqual(P.read_aliases(p),{'alpha':A,'beta':B})
            p.write_text(p.read_text()+f'slus\t{C}\talpha\n')
            with self.assertRaises(P.PartitionError):P.read_aliases(p)

    def test_malformed_path_and_alias_targets_fail_closed(self):
        with self.assertRaises(P.PartitionError):
            P.path('.', 'parent.source', 'src', '.c')
        with tempfile.TemporaryDirectory() as td:
            path = Path(td) / 'names.tsv'
            for target in ('', 'not a name', '1bad', B):
                with self.subTest(target=target):
                    path.write_text(f'slus\t{A}\t{target}\n')
                    with self.assertRaises(P.PartitionError):
                        P.read_aliases(path)
            path.write_text(f'slus\t{A}\t{A}\n')
            self.assertEqual(P.read_aliases(path), {})

if __name__ == "__main__":
    unittest.main()
