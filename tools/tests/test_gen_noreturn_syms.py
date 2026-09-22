"""tools/gate/gen_noreturn_syms.py: deterministic regeneration of the four
per-container noreturn censuses.

The load-bearing invariants, all of which broke silently at least once
(docs/HANDOVER.md section 0, docs/evidence/split_fragments_20260922.md 7.7):

  1. ROOT must resolve to the REPO from BOTH copies of the script -- the tracked
     ``tools/gate/`` one and the real-file copy mk_ovl_root.sh installs at
     ``build_ovl/tools/``. It used to be ``parents[1]``, i.e. ``<repo>/tools``
     and ``build_ovl``, neither of which holds ``raw/``.
  2. The census is scanned from the FROZEN ``raw/<container>/*.c`` corpus, not
     the live ``src/``: the transform layers strip the noreturn declarations out
     of src/. ``test_src_adds_no_symbol_beyond_raw`` holds the other half of that
     decision -- if a future declaration ever appears under ``src/`` that raw/
     does not have, this test fails and someone has to decide what it means,
     rather than the two corpora silently diverging.
  3. Each family's tracked file must equal a fresh regeneration BYTE FOR BYTE
     (header, sort order and trailing newline included), which is what
     ``--check`` gates in CI and what the 2026-09-22 fix restored.
  4. A ``work/`` scan glob is a refusal, not a filter.
  5. A WRITE that would prune a populated census fails closed (shrink guard).

This test reads the real repo (census files, false members, raw/ and src/ C) but
writes NOTHING and runs no compiler. Roughly 20 s: the raw corpus is 6.7k files.

    ./.venv/bin/python3 -m pytest tools/tests/test_gen_noreturn_syms.py -q
"""
import importlib.util
import os
import unittest
from pathlib import Path

REPO = Path(__file__).resolve().parents[2]
TRACKED_COPY = REPO / "tools/gate/gen_noreturn_syms.py"
VIEW_COPY = REPO / "build_ovl/tools/gen_noreturn_syms.py"


def _load(path: Path, name: str):
    spec = importlib.util.spec_from_file_location(name, path)
    mod = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(mod)
    return mod


G = _load(TRACKED_COPY, "gen_noreturn_syms_tracked")


class RootResolution(unittest.TestCase):
    """Invariant 1: the repo, from either copy."""

    def test_tracked_copy_resolves_to_the_repo(self):
        self.assertEqual(G.ROOT, REPO)

    def test_view_root_copy_resolves_to_the_repo(self):
        """build_ovl/tools/ is a REAL file (mk_ovl_root.sh does `cp -rL`) whose
        own parents are build_ovl/tools and build_ovl -- neither holds raw/, so
        the walk has to continue up to the repo."""
        if not VIEW_COPY.exists():
            self.skipTest("no build_ovl view root in this checkout")
        self.assertEqual(_load(VIEW_COPY, "gen_noreturn_syms_view").ROOT, REPO)

    def test_the_two_copies_are_byte_identical(self):
        """They must not drift: the view-root copy is what a landing runs
        (overlay_land_function.regenerate_census)."""
        if not VIEW_COPY.exists():
            self.skipTest("no build_ovl view root in this checkout")
        self.assertEqual(TRACKED_COPY.read_bytes(), VIEW_COPY.read_bytes())

    def test_a_tree_without_the_markers_is_a_refusal(self):
        """No marker pair anywhere above -> SystemExit naming the markers, never
        a silent ROOT that makes every family match 0 sources."""
        with self.assertRaises(SystemExit) as cm:
            G._find_root(Path(os.sep) / "definitely_not_a_checkout" / "x.py")
        msg = str(cm.exception)
        self.assertIn("raw/", msg)
        self.assertIn(G.FALSE_MEMBERS_PATH, msg)


class ScanText(unittest.TestCase):
    """The declaration parser and the corpus-proven ZERO-ARG firing rule."""

    def test_extern_declaration(self):
        self.assertEqual(
            G.scan_text("extern void func_80012345(void) __attribute__((noreturn));"),
            {"func_80012345"})

    def test_definition_signature_is_isolated_from_its_body(self):
        text = ("void __attribute__((noreturn)) func_80012345(void) {\n"
                "    other_call(1, 2);\n"
                "    while (1) {}\n"
                "}\n")
        self.assertEqual(G.scan_text(text), {"func_80012345"})

    def test_noreturn_macro_form(self):
        self.assertEqual(G.scan_text("NORETURN void func_80012345(void);"),
                         {"func_80012345"})

    def test_empty_parameter_list_counts(self):
        self.assertEqual(G.scan_text("extern void func_80012345() __attribute__((noreturn));"),
                         {"func_80012345"})

    def test_arg_taking_noreturn_callee_is_excluded(self):
        """66/66 corpus rule: the one arg-taking noreturn callee keeps `jal` at
        every site, so it must never enter the census."""
        self.assertEqual(
            G.scan_text("extern void func_8007BEF0(s32 code) __attribute__((noreturn));"),
            set())

    def test_a_plain_declaration_is_not_a_member(self):
        self.assertEqual(G.scan_text("extern void func_80012345(void);"), set())

    def test_the_define_of_the_macro_itself_is_not_a_symbol(self):
        self.assertEqual(
            G.scan_text("#define NORETURN __attribute__((noreturn))\n"), set())

    def test_a_backslash_continued_directive_does_not_eat_the_next_decl(self):
        """func_818BC9CC, 2026-09-02: the continuation line merged into the
        following `;`-statement and silently deleted the decl after it."""
        text = ("#define TWO_LINE(x) do { \\\n"
                "    (x)++; } while (0)\n"
                "extern void func_80012345(void) __attribute__((noreturn));\n")
        self.assertEqual(G.scan_text(text), {"func_80012345"})

    def test_function_pointer_parameter_is_still_arg_taking(self):
        self.assertEqual(
            G.scan_text("extern void func_80012345(void (*fn)(void)) "
                        "__attribute__((noreturn));"),
            set())


class UntrackedGlobRefusal(unittest.TestCase):
    """Invariant 4. Three landed byte-exact rows broke on this."""

    def test_work_glob_is_refused_with_an_actionable_message(self):
        with self.assertRaises(SystemExit) as cm:
            G.collect(["work/overlay_wave/candidates_dungeon/*.c"], label="[t]")
        msg = str(cm.exception)
        self.assertIn("work", msg)
        self.assertIn("func_80024948", msg)

    def test_raw_is_a_tracked_root(self):
        self.assertIn("raw", G.TRACKED_SOURCE_ROOTS)
        G.collect([], label="[t]")  # no raise

    def test_every_configured_glob_is_rooted_in_a_tracked_tree(self):
        for fam, cfg in G.CONTAINERS.items():
            G._assert_tracked_source_globs(f"[{fam}]", list(cfg["globs"]))


class _Plans(unittest.TestCase):
    """plan_family() over the real repo, computed once for the whole class."""

    @classmethod
    def setUpClass(cls):
        cls.plans = {fam: G.plan_family(fam) for fam in G.CONTAINERS}


class TrackedFilesAreReproducible(_Plans):
    """Invariant 3: byte-for-byte, not set-equal."""

    def test_each_family_regenerates_its_tracked_file_exactly(self):
        for fam, plan in self.plans.items():
            with self.subTest(family=fam):
                self.assertIsNotNone(plan["tracked_text"],
                                     f"{plan['out']} is missing")
                self.assertEqual(plan["new_text"], plan["tracked_text"])

    def test_no_family_would_fail_closed(self):
        for fam, plan in self.plans.items():
            with self.subTest(family=fam):
                self.assertIsNone(G._fail_closed_reason(
                    plan, allow_empty_scan=False, allow_empty=False))

    def test_every_family_has_a_real_evidence_base(self):
        for fam, plan in self.plans.items():
            with self.subTest(family=fam):
                self.assertGreater(plan["n_sources"], 0)

    def test_the_main_evidence_file_is_present_and_contributes_its_seven(self):
        """config/noreturn_evidence.main.c is declaration-only and NEVER
        compiled; it went missing once and silently un-matched seven rows."""
        ev = G.ROOT / "config/noreturn_evidence.main.c"
        self.assertTrue(ev.is_file(), f"{ev} missing")
        self.assertEqual(
            G.scan_text(ev.read_text()),
            {"func_8002515C", "func_80025E18", "func_80027B6C", "func_804021F4",
             "func_80405B5C", "func_80405C0C", "func_8040680C"})

    def test_every_false_member_carries_a_proof(self):
        for fam in G.CONTAINERS:
            G.false_members(fam)  # SystemExit on a missing/empty proof


class SrcAddsNothing(_Plans):
    """Invariant 2. Deliberately a TEST, not a scan glob: if a declaration ever
    lands under src/ that raw/ does not carry, this fails and a human decides."""

    SRC_GLOBS = {
        "main": ["src/main/*.c", "src/slus/*.c"],
        "town": ["src/town/*.c"],
        "dungeon": ["src/dungeon/*.c"],
        "ovmovie": ["src/ovmovie/*.c"],
    }

    def test_src_adds_no_symbol_beyond_raw(self):
        for fam, globs in self.SRC_GLOBS.items():
            with self.subTest(family=fam):
                raw = G.collect([g for g in G.CONTAINERS[fam]["globs"]],
                                label=f"[{fam}]")
                src = G.collect(globs, label=f"[{fam}-src]")
                self.assertEqual(
                    sorted(src - raw), [],
                    f"src/ now declares a zero-arg noreturn symbol the frozen "
                    f"raw/ corpus does not have, for family {fam}. The census "
                    f"is scanned from raw/ only (see the module docstring); "
                    f"decide whether this symbol belongs in the census before "
                    f"relaxing this test.")


class ShrinkGuard(unittest.TestCase):
    """Invariant 5: a partial prune is the same defect class as an empty one."""

    @staticmethod
    def plan(tracked_syms, n_names, fam="dungeon"):
        names = [f"func_{i:08X}" for i in range(n_names)]
        return {"fam": fam, "out": Path("/nonexistent"), "names": names,
                "excluded": [], "new_text": G.render(names), "n_sources": 100,
                "tracked_text": "#\n", "tracked_syms": tracked_syms}

    def test_limit_is_the_smaller_of_five_percent_and_twenty(self):
        self.assertEqual(G.shrink_limit(1015), 20.0)   # 5% = 50.75 -> the flat 20
        self.assertEqual(G.shrink_limit(32), 1.6)      # 5% of a small census
        self.assertEqual(G.shrink_limit(0), 0.0)

    def test_a_large_drop_refuses_a_write(self):
        reason = G._fail_closed_reason(self.plan(1015, 990),
                                       allow_empty_scan=False, allow_empty=False)
        self.assertIsNotNone(reason)
        self.assertIn("dungeon", reason)
        self.assertIn("1015", reason)
        self.assertIn("990", reason)
        self.assertIn("--allow-shrink", reason)

    def test_a_drop_inside_the_limit_is_allowed(self):
        """The func_80171BEC removal: one symbol off 1,015."""
        self.assertIsNone(G._fail_closed_reason(
            self.plan(1015, 1014), allow_empty_scan=False, allow_empty=False))

    def test_allow_shrink_overrides(self):
        self.assertIsNone(G._fail_closed_reason(
            self.plan(1015, 990), allow_empty_scan=False, allow_empty=False,
            allow_shrink=True))

    def test_check_is_never_gated_by_the_shrink_guard(self):
        """--check writes nothing; it reports DRIFT instead."""
        self.assertIsNone(G._fail_closed_reason(
            self.plan(1015, 990), allow_empty_scan=False, allow_empty=False,
            writing=False))

    def test_a_small_census_is_held_to_its_own_five_percent(self):
        self.assertIsNotNone(G._fail_closed_reason(
            self.plan(32, 30, fam="main"),
            allow_empty_scan=False, allow_empty=False))
        self.assertIsNone(G._fail_closed_reason(
            self.plan(32, 31, fam="main"),
            allow_empty_scan=False, allow_empty=False))

    def test_the_empty_census_guard_still_fires_first(self):
        reason = G._fail_closed_reason(self.plan(1015, 0),
                                       allow_empty_scan=False, allow_empty=False)
        self.assertIn("--allow-empty", reason)


if __name__ == "__main__":
    unittest.main()
