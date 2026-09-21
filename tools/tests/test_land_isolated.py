"""The isolated landing switch (round 68): LAND_ISOLATED=1 in tools/lanes/land_lanes.sh and
tools/lanes/land_gap.sh, and the view-root / journal environment of tools/build/gate_all.py.

Every shell test runs a COPY of the script in a temp tree (the scripts cd to their own ../..), with
a fake `pgrep` on PATH, so the live machine is never consulted and the real land lock is never taken.
"""
import contextlib, fcntl, os, shutil, subprocess, sys, tempfile, threading, time, unittest
from concurrent.futures import ThreadPoolExecutor
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]


def fake_pgrep(bindir, mode, pid=""):
    """A `pgrep` that answers for the patterns land_lanes.sh uses.

    mode 'codex'  : a codex lane is running, no sweep
    mode 'sweep'  : a sweep whose pid is `pid` (a foreign process)
    mode 'self'   : a sweep whose pid is the land_lanes.sh shell itself (the wrapper self-match)
    mode 'dead'   : a sweep pid that has already exited
    mode 'idle'   : nothing is running
    """
    p = Path(bindir) / "pgrep"
    p.write_text(f"""#!/bin/bash
mode={mode}; want="$2"
# the callers use the bracket trick ("[c]odex exec", "[s]weep.py "), so match on the tail
case "$want" in
  *odex*) [ "$mode" = codex ] && {{ echo 4242; exit 0; }}; exit 1;;
  *weep*)
    case "$mode" in
      sweep) echo {pid or 0}; exit 0;;
      self)
        # the land_lanes.sh shell that invoked us: the OLDEST ancestor whose command line is the
        # script (the nearer one is the short-lived command-substitution subshell, whose command
        # line is the same); that pid is the landing's own shell, alive, and must not count
        hit=""; p=$PPID
        for _ in 1 2 3 4 5; do
          grep -qa land_lanes.sh /proc/$p/cmdline 2>/dev/null && hit=$p
          p=$(ps -o ppid= -p $p 2>/dev/null | tr -d ' '); [ -n "$p" ] || break
        done
        [ -n "$hit" ] && {{ echo $hit; exit 0; }}
        exit 1;;
      dead)
        # a pid that has already exited: never a running sweep
        ( exit 0 ) & d=$!; wait $d 2>/dev/null; echo $d; exit 0;;
      *) exit 1;;
    esac;;
esac
exit 1
""")
    p.chmod(0o755)


def tree(scripts=("land_lanes.sh",)):
    d = Path(tempfile.mkdtemp(prefix="land_iso_"))
    (d / "tools/lanes").mkdir(parents=True)
    (d / "bin").mkdir()
    for s in scripts:
        shutil.copy(ROOT / "tools/lanes" / s, d / "tools/lanes" / s)
    return d


def run_land(d, env_extra, args=("tag", "lane1"), timeout=60):
    env = dict(os.environ, PATH=f"{d}/bin:" + os.environ["PATH"], LAND_GUARD_ONLY="1")
    env.update(env_extra)
    return subprocess.run(["bash", str(d / "tools/lanes/land_lanes.sh"), *args],
                          capture_output=True, text=True, env=env, timeout=timeout)


class GuardTests(unittest.TestCase):
    def tearDown(self):
        for d in getattr(self, "_dirs", []):
            shutil.rmtree(d, ignore_errors=True)

    def mktree(self, **kw):
        d = tree(**kw); self._dirs = getattr(self, "_dirs", []) + [d]; return d

    def test_default_still_refuses_while_a_codex_lane_runs(self):
        d = self.mktree(); fake_pgrep(d / "bin", "codex")
        r = run_land(d, {})
        self.assertEqual(r.returncode, 1)
        self.assertIn("a codex lane is running", r.stdout)

    def test_default_still_refuses_while_a_sweep_runs(self):
        d = self.mktree(); fake_pgrep(d / "bin", "sweep", pid=4243)
        r = run_land(d, {})
        self.assertEqual(r.returncode, 1)
        self.assertIn("a sweep is running", r.stdout)

    def test_isolated_ignores_codex_lanes(self):
        d = self.mktree(); fake_pgrep(d / "bin", "codex")
        r = run_land(d, {"LAND_ISOLATED": "1"})
        self.assertEqual(r.returncode, 0, r.stdout + r.stderr)
        self.assertIn("LAND_GUARD_OK iso=1", r.stdout)
        self.assertNotIn("codex lane is running", r.stdout)

    def test_isolated_ignores_its_own_shell_matching_the_sweep_pattern(self):
        """The wrapper self-match: a sweep pid that IS this landing's own shell is not foreign."""
        d = self.mktree(); fake_pgrep(d / "bin", "self")
        r = run_land(d, {"LAND_ISOLATED": "1", "LAND_POLL": "0", "LAND_WAIT_MAX": "2"})
        self.assertEqual(r.returncode, 0, r.stdout + r.stderr)
        self.assertIn("LAND_GUARD_OK iso=1", r.stdout)

    def test_isolated_ignores_a_sweep_pid_that_has_already_exited(self):
        d = self.mktree(); fake_pgrep(d / "bin", "dead")
        r = run_land(d, {"LAND_ISOLATED": "1", "LAND_POLL": "0", "LAND_WAIT_MAX": "2"})
        self.assertEqual(r.returncode, 0, r.stdout + r.stderr)
        self.assertIn("LAND_GUARD_OK iso=1", r.stdout)

    def test_isolated_waits_for_a_foreign_sweep_instead_of_refusing(self):
        sleeper = subprocess.Popen(["sleep", "30"])
        try:
            d = self.mktree(); fake_pgrep(d / "bin", "sweep", pid=sleeper.pid)
            r = run_land(d, {"LAND_ISOLATED": "1", "LAND_POLL": "0", "LAND_WAIT_MAX": "2"})
            self.assertEqual(r.returncode, 1)
            self.assertIn("queued (this landing waits, it does not refuse)", r.stdout)
            self.assertIn("outlasted LAND_WAIT_MAX", r.stdout)
            self.assertNotIn("a sweep is running: wait for it", r.stdout)
        finally:
            sleeper.kill(); sleeper.wait()

    def test_isolated_proceeds_once_the_foreign_sweep_ends(self):
        d = self.mktree(); fake_pgrep(d / "bin", "idle")
        flag = d / "busy_calls"
        busy = f'n=$(cat {flag} 2>/dev/null || echo 0); echo $((n+1)) > {flag}; [ "$n" -lt 2 ]'
        r = run_land(d, {"LAND_ISOLATED": "1", "LAND_POLL": "0", "LAND_BUSY_CMD": busy})
        self.assertEqual(r.returncode, 0, r.stdout + r.stderr)
        self.assertIn("queued", r.stdout)
        self.assertIn("LAND_GUARD_OK iso=1", r.stdout)
        self.assertGreaterEqual(int(flag.read_text()), 3)

    def test_a_second_landing_queues_on_the_land_lock(self):
        d = self.mktree(); fake_pgrep(d / "bin", "idle")
        lock = d / "build_ovl/work/land.lock"; lock.parent.mkdir(parents=True)
        fh = open(lock, "w"); fcntl.flock(fh, fcntl.LOCK_EX)
        threading.Timer(1.5, lambda: (fcntl.flock(fh, fcntl.LOCK_UN), fh.close())).start()
        t0 = time.time()
        r = run_land(d, {"LAND_ISOLATED": "1"})
        waited = time.time() - t0
        self.assertEqual(r.returncode, 0, r.stdout + r.stderr)
        self.assertGreater(waited, 1.0, "the second landing did not wait on the land lock")


class GapTests(unittest.TestCase):
    """land_gap.sh: LAND_ISOLATED=1 lands at once; without it, the old wait-for-a-gap loop."""

    def setUp(self):
        self.d = tree(scripts=("land_gap.sh",))
        (self.d / "tools/lanes/land_lanes.sh").write_text("#!/bin/bash\necho STUB_LANDING \"$@\"\n")
        fake_pgrep(self.d / "bin", "codex")

    def tearDown(self):
        shutil.rmtree(self.d, ignore_errors=True)

    def run_gap(self, env_extra):
        env = dict(os.environ, PATH=f"{self.d}/bin:" + os.environ["PATH"],
                   LAND_GAP_ROOT=str(self.d), EXTRA_T="", GAP_ARMS="0",
                   GAP_MAX_WAIT="2", GAP_POLL="1")
        env.update(env_extra)
        return subprocess.run(["bash", str(self.d / "tools/lanes/land_gap.sh"), "tag", "lane1"],
                              capture_output=True, text=True, env=env, timeout=60)

    def test_isolated_lands_without_waiting_for_a_gap(self):
        r = self.run_gap({"LAND_ISOLATED": "1"})
        self.assertIn("STUB_LANDING tag lane1", r.stdout)
        self.assertIn("LAND_GAP_END tag", r.stdout)

    def test_default_still_waits_for_the_gap(self):
        r = self.run_gap({})
        self.assertNotIn("STUB_LANDING", r.stdout)     # the codex lane still blocks the landing
        self.assertNotEqual(r.returncode, 0)


class GateRootEnvTests(unittest.TestCase):
    """gate_all.py / container_check.py read their view root from GATE_BUILD_ROOT (default build_ovl)."""

    def constants(self, module, env_extra):
        code = ("import importlib.util,sys;"
                f"spec=importlib.util.spec_from_file_location('m',r'{ROOT}/tools/build/{module}');"
                "m=importlib.util.module_from_spec(spec);spec.loader.exec_module(m);"
                "print(m.B);print(getattr(m,'JOURNAL',''))")
        env = dict(os.environ); env.pop("GATE_BUILD_ROOT", None); env.pop("GATE_JOURNAL", None)
        env.update(env_extra)
        out = subprocess.run([sys.executable, "-c", code], capture_output=True, text=True,
                             env=env, cwd=str(ROOT), timeout=120)
        self.assertEqual(out.returncode, 0, out.stderr)
        return out.stdout.splitlines()

    def test_gate_all_defaults_unchanged(self):
        b, j = self.constants("gate_all.py", {})
        self.assertEqual(b, str(ROOT / "build_ovl"))
        self.assertEqual(j, str(ROOT / "ledger/gate.jsonl"))

    def test_gate_all_follows_the_environment(self):
        b, j = self.constants("gate_all.py", {"GATE_BUILD_ROOT": "build_ovl_gate",
                                              "GATE_JOURNAL": "/tmp/gate_proof.jsonl"})
        self.assertEqual(b, str(ROOT / "build_ovl_gate"))
        self.assertEqual(j, "/tmp/gate_proof.jsonl")

    def test_gate_journal_relative_is_repo_relative(self):
        _, j = self.constants("gate_all.py", {"GATE_JOURNAL": "work/x.jsonl"})
        self.assertEqual(j, str(ROOT / "work/x.jsonl"))

    def test_gate_all_locks_windows_only_in_an_isolated_root(self):
        code = ("import importlib.util,sys;"
                f"spec=importlib.util.spec_from_file_location('m',r'{ROOT}/tools/build/gate_all.py');"
                "m=importlib.util.module_from_spec(spec);spec.loader.exec_module(m);print(m.ISOLATED)")
        env = dict(os.environ); env.pop("GATE_BUILD_ROOT", None); env.pop("GATE_JOURNAL", None)
        r = subprocess.run([sys.executable, "-c", code], capture_output=True, text=True, env=env, cwd=str(ROOT))
        self.assertEqual(r.stdout.strip(), "False", r.stderr)
        env["GATE_BUILD_ROOT"] = "build_ovl_gate"
        r = subprocess.run([sys.executable, "-c", code], capture_output=True, text=True, env=env, cwd=str(ROOT))
        self.assertEqual(r.stdout.strip(), "True", r.stderr)

    def test_container_check_follows_the_same_root(self):
        self.assertEqual(self.constants("container_check.py", {})[0], str(ROOT / "build_ovl"))
        self.assertEqual(self.constants("container_check.py", {"GATE_BUILD_ROOT": "build_ovl_gate"})[0],
                         str(ROOT / "build_ovl_gate"))


class LazyCacheRaceTests(unittest.TestCase):
    """The window tables are built by threads (gate_all's workers, the sweeps).  A cache published
    before it is filled hands a peer a HALF table, and gate_all then journals a window's verdict
    under an inputs_sha that covers none of its src files - a later gate skips that window as
    "up to date" although its C changed (found on 1,850 of 2,175 windows, 2026-09-21)."""

    def build(self, threads):
        sys.path.insert(0, str(ROOT / "tools")); sys.path.insert(0, str(ROOT / "tools/build"))
        import importlib.util, common
        spec = importlib.util.spec_from_file_location("gate_all_t", ROOT / "tools/build/gate_all.py")
        g = importlib.util.module_from_spec(spec); spec.loader.exec_module(g)
        common._WM = None; g._WROWS = None
        out = []
        with ThreadPoolExecutor(max_workers=threads) as ex:
            for r in ex.map(lambda _: dict(g.window_rows()), range(threads)):
                out.append(r)
        return out

    def test_every_thread_sees_the_whole_window_table(self):
        complete = self.build(1)[0]
        self.assertGreater(len(complete), 1000)
        for seen in self.build(8):
            self.assertEqual(len(seen), len(complete))
            self.assertEqual(sorted(seen), sorted(complete))


class GateCandidateRestoreTests(unittest.TestCase):
    """verify.gate_candidate restores the row it swapped out - but never over a newer text a
    concurrent landing wrote (the isolated landing runs while lanes gate)."""

    def setUp(self):
        sys.path.insert(0, str(ROOT / "tools"))
        import verify, common
        self.verify, self.common = verify, common
        self.d = Path(tempfile.mkdtemp(prefix="gate_cand_"))
        self.cp = self.d / "func_80000000.c"; self.cp.write_text("BEFORE\n")
        self.cand = self.d / "cand.c"; self.cand.write_text("CANDIDATE\n")
        self.row = {"kind": "overlay", "container": "town", "foff": 0, "size": 4,
                    "c_path": "town/func_80000000.c", "func": "func_80000000",
                    "gate_config": "config/overlays/town_x.overlay.yaml"}
        self._saved = (common.clean_path, common.covering_windows, verify.window_lock, verify.run_window_gate)
        common.clean_path = lambda row: self.cp
        common.covering_windows = lambda *a, **k: []
        verify.window_lock = lambda *a, **k: contextlib.nullcontext()

    def tearDown(self):
        (self.common.clean_path, self.common.covering_windows,
         self.verify.window_lock, self.verify.run_window_gate) = self._saved
        shutil.rmtree(self.d, ignore_errors=True)

    def test_the_row_is_restored_when_nothing_else_touched_it(self):
        self.verify.run_window_gate = lambda *a, **k: ("MATCH", "")
        res = self.verify.gate_candidate(self.row, self.cand)
        self.assertEqual(res["gate"], "MATCH")
        self.assertEqual(self.cp.read_text(), "BEFORE\n")

    def test_a_landing_that_wrote_the_row_meanwhile_is_not_reverted(self):
        def gate(*a, **k):
            self.cp.write_text("LANDED BY THE CASCADE\n")   # apply_candidates / sweep.py
            return ("MATCH", "")
        self.verify.run_window_gate = gate
        self.verify.gate_candidate(self.row, self.cand)
        self.assertEqual(self.cp.read_text(), "LANDED BY THE CASCADE\n")


if __name__ == "__main__":
    unittest.main()
