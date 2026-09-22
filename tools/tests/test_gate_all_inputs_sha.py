"""tools/build/gate_all.py: inputs_sha must hash the container's maspsx census files, not just
the window YAML, split records and src/*.c.

Bug: config/noreturn_syms[.<container>].txt and config/sibcall_syms[.<container>].txt (main family
un-suffixed, every other family '.<family>.txt') drive maspsx's LEAD 18/22 tail-call passes and
flip jal<->j family-wide, but inputs_sha never hashed them.  A census edit left every window's
cached sha unchanged, so gate_all.py silently treated every window as up to date and re-gated
nothing (measured 2026-09-22: after a census edit, `gate_all.py --container dungeon` gated 0
windows; `--retry` gated 1,458).

Hermetic: split_records and window_rows are monkeypatched to return nothing (real ledger/ data is
never read) and gate_all.ROOT is monkeypatched to a throwaway temp tree, so no real repo file is
read or written.

    ./.venv/bin/python3 -m pytest tools/tests/test_gate_all_inputs_sha.py -q
"""
import importlib.util
import tempfile
import unittest
from pathlib import Path

REPO = Path(__file__).resolve().parents[2]
_spec = importlib.util.spec_from_file_location("gate_all_under_test", REPO / "tools/build/gate_all.py")
gate_all = importlib.util.module_from_spec(_spec)
_spec.loader.exec_module(gate_all)


class InputsShaCensusFiles(unittest.TestCase):
    def setUp(self):
        self._root = gate_all.ROOT
        self._split_records = gate_all.split_records
        self._window_rows = gate_all.window_rows
        # hermetic: no real ledger/ read for the split-record or row-table contributions --
        # this test is only about the new census-file contribution
        gate_all.split_records = lambda cont, name: []
        gate_all.window_rows = lambda: {}
        self._tmpdir = tempfile.TemporaryDirectory()
        self.tmp = Path(self._tmpdir.name)
        (self.tmp / "config" / "overlays").mkdir(parents=True)
        gate_all.ROOT = self.tmp
        self.addCleanup(self._tmpdir.cleanup)
        self.addCleanup(lambda: setattr(gate_all, "ROOT", self._root))
        self.addCleanup(lambda: setattr(gate_all, "split_records", self._split_records))
        self.addCleanup(lambda: setattr(gate_all, "window_rows", self._window_rows))

    def _write(self, name, text):
        (self.tmp / "config" / name).write_text(text)

    def _yaml(self, stem):
        p = self.tmp / "config/overlays" / f"{stem}.overlay.yaml"
        p.write_text(f"name: {stem}\n")
        return p

    # -- census_files: family mapping, matching tools/gate/overlay_evidence.py:evidence_env --

    def test_main_family_reads_the_unsuffixed_files(self):
        self._write("noreturn_syms.txt", "sym_a\n")
        self._write("sibcall_syms.txt", "sym_b\n")
        self.assertEqual([p.name for p in gate_all.census_files("main")],
                          ["noreturn_syms.txt", "sibcall_syms.txt"])

    def test_dungeon_engine_folds_into_the_dungeon_family_file(self):
        self._write("noreturn_syms.dungeon.txt", "sym_a\n")
        self._write("sibcall_syms.dungeon.txt", "sym_b\n")
        self.assertEqual([p.name for p in gate_all.census_files("dungeon_engine")],
                          ["noreturn_syms.dungeon.txt", "sibcall_syms.dungeon.txt"])

    def test_town_family_reads_its_own_suffixed_files(self):
        self._write("noreturn_syms.town.txt", "sym_a\n")
        self._write("sibcall_syms.town.txt", "sym_b\n")
        self.assertEqual([p.name for p in gate_all.census_files("town")],
                          ["noreturn_syms.town.txt", "sibcall_syms.town.txt"])

    def test_missing_family_override_is_skipped_not_an_error(self):
        # no config/ files written for this family: maspsx would load an empty, inert set
        self.assertEqual(gate_all.census_files("ovmovie"), [])

    # -- inputs_sha: the sha actually reacts to census content --

    def test_sha_changes_when_the_family_census_content_changes(self):
        self._write("noreturn_syms.txt", "sym_a\n")
        self._write("sibcall_syms.txt", "sym_b\n")
        y = self._yaml("main_boot")
        before = gate_all.inputs_sha(y)
        self._write("noreturn_syms.txt", "sym_a\nsym_c\n")
        after = gate_all.inputs_sha(y)
        self.assertNotEqual(before, after)

    def test_sha_unaffected_by_a_different_familys_census(self):
        self._write("noreturn_syms.txt", "sym_a\n")
        self._write("sibcall_syms.txt", "sym_b\n")
        self._write("noreturn_syms.town.txt", "unrelated\n")
        y = self._yaml("main_boot")
        before = gate_all.inputs_sha(y)
        self._write("noreturn_syms.town.txt", "unrelated\nchanged\n")
        after = gate_all.inputs_sha(y)
        self.assertEqual(before, after, "main's sha must not depend on the town family's census")

    def test_sha_stable_when_nothing_changes(self):
        self._write("noreturn_syms.dungeon.txt", "sym_a\n")
        self._write("sibcall_syms.dungeon.txt", "sym_b\n")
        y = self._yaml("dungeon_deep_0a68")
        self.assertEqual(gate_all.inputs_sha(y), gate_all.inputs_sha(y))


if __name__ == "__main__":
    unittest.main()
