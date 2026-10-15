"""r120: lanes in private repo copies OUTSIDE the live root never make the isolated lander busy (fake /proc)."""
import importlib.util
import os
from pathlib import Path
import tempfile
import unittest

TOOLS = Path(__file__).resolve().parents[1]
spec = importlib.util.spec_from_file_location('external_lane_lander', TOOLS/'lanes/land_packages.py')
G = importlib.util.module_from_spec(spec); spec.loader.exec_module(G)

CODEX = ['codex', 'exec', '-C', '{lane}', '--dangerously-bypass-approvals-and-sandbox', '-m', 'gpt-6.1-sol']


class ExternalLaneTests(unittest.TestCase):
    def setUp(self):
        self.temp = tempfile.TemporaryDirectory(dir=os.environ.get('TMPDIR'))
        self.addCleanup(self.temp.cleanup)
        self.base = Path(self.temp.name).resolve()
        self.root = self.base/'repo'
        for d in ('src', 'ledger', 'toolchain/bin', 'work/native_lane/inroot'):
            (self.root/d).mkdir(parents=True)
        (self.root/'src/a.c').write_text('x\n'); (self.root/'toolchain/bin/cc1').write_text('x\n')
        self.ext = self.base/'azure-lanes/l1/root'
        self.lane = self.ext/'work/native_lane/l1'; self.lane.mkdir(parents=True)
        (self.ext/'src').mkdir(); (self.ext/'src/a.c').write_text('y\n')
        (self.ext/'toolchain').symlink_to(self.root/'toolchain')
        self.proc_root = self.base/'proc'; self.proc_root.mkdir()
        self.codex = self.proc_at(100, self.lane, [a.format(lane=self.lane) for a in CODEX])

    def proc_at(self, pid, cwd, argv, parent=1, env=(), fds=()):
        proc = self.proc_root/str(pid); proc.mkdir()
        (proc/'cwd').symlink_to(cwd, target_is_directory=True)
        (proc/'cmdline').write_bytes(b'\0'.join(os.fsencode(a) for a in argv)+b'\0')
        (proc/'stat').write_text(f'{pid} (fixture) S {parent} 0 0')
        (proc/'environ').write_bytes(b'\0'.join(os.fsencode(s) for s in env)+b'\0')
        (proc/'fd').mkdir()
        for i, target in enumerate(fds): (proc/'fd'/str(i)).symlink_to(target)
        return proc

    def busy(self, isolated=True):
        return {r['pid'] for r in G.busy_processes(self.root, False, isolated, self.proc_root)}

    def test_external_codex_with_inline_python_child_is_not_busy(self):
        self.proc_at(101, self.lane, ['bash', '-lc', 'python3 - <<EOF\nprint(1)\nEOF'], parent=100,
                     fds=[self.lane/'x.log'])
        self.proc_at(102, self.lane, ['python3', '-c', 'import json; open("out/r.json","w")'], parent=101,
                     fds=[self.ext/'src/a.c'])
        (self.lane/'x.log').write_text('')
        self.assertEqual(self.busy(), set())

    def test_default_mode_unchanged_for_external_codex(self):
        self.assertEqual(self.busy(False), {100})

    def test_external_gate_in_its_own_root_is_not_busy(self):
        gate = self.ext/'tools/build/gate_all.py'; gate.parent.mkdir(parents=True); gate.write_text('')
        self.proc_at(103, self.ext, ['python3', str(gate)], fds=[self.ext/'src/a.c'])
        self.assertEqual(self.busy(), set())

    def test_shared_readonly_toolchain_reads_are_allowed(self):
        self.proc_at(101, self.lane, ['/ext/cc1', str(self.ext/'toolchain/bin/cc1'), '-quiet'], parent=100,
                     fds=[self.ext/'toolchain/bin/cc1'])
        self.assertEqual(self.busy(), set())

    def test_external_fd_into_live_src_is_busy(self):
        self.proc_at(101, self.lane, ['python3', '-c', 'pass'], parent=100, fds=[self.root/'src/a.c'])
        self.assertEqual(self.busy(), {100})

    def test_external_fd_into_live_ledger_via_symlink_is_busy(self):
        link = self.base/'alias'; link.symlink_to(self.root/'ledger')
        self.proc_at(101, self.lane, ['python3', '-c', 'pass'], parent=100, fds=[link])
        self.assertEqual(self.busy(), {100})

    def test_external_arg_naming_a_live_path_is_busy(self):
        self.proc_at(101, self.lane, ['cat', str(self.root/'src/a.c')], parent=100)
        self.assertEqual(self.busy(), {100})

    def test_inline_text_naming_the_live_root_is_busy(self):
        self.proc_at(101, self.lane, ['bash', '-lc', f'cp x "{self.root}/src/a.c"'], parent=100)
        self.assertEqual(self.busy(), {100})

    def test_relative_arg_escaping_into_live_root_is_busy(self):
        rel = os.path.relpath(self.root/'src/a.c', self.lane)
        self.proc_at(101, self.lane, ['cat', rel], parent=100)
        self.assertEqual(self.busy(), {100})

    def test_cwd_inside_live_root_is_not_external(self):
        self.proc_at(101, self.root/'src', ['python3', '-c', 'pass'], parent=100)
        self.assertEqual(self.busy(), {100})

    def test_cwd_above_live_root_is_busy(self):
        self.proc_at(101, self.base, ['python3', '-c', 'pass'], parent=100)
        self.assertEqual(self.busy(), {100})

    def test_gate_override_env_into_live_root_is_busy(self):
        self.proc_at(101, self.lane, ['python3', '-c', 'pass'], parent=100,
                     env=[f'GATE_BUILD_ROOT={self.root}/build_ovl'])
        self.assertEqual(self.busy(), {100})

    def test_pythonpath_into_live_tools_is_busy(self):
        self.proc_at(101, self.lane, ['python3', '-c', 'pass'], parent=100, env=[f'PYTHONPATH={self.root}/tools'])
        self.assertEqual(self.busy(), {100})

    def test_env_var_expansion_into_live_root_is_busy(self):
        self.proc_at(101, self.lane, ['bash', '-lc', 'cat $LIVE/src/a.c'], parent=100, env=[f'LIVE={self.root}'])
        self.assertEqual(self.busy(), {100})

    def test_deep_descendant_with_live_fd_blocks_the_whole_tree(self):
        self.proc_at(101, self.lane, ['bash', '-lc', 'x'], parent=100)
        self.proc_at(102, self.lane, ['bash', '-lc', 'y'], parent=101)
        self.proc_at(103, self.lane, ['python3', '-c', 'pass'], parent=102, fds=[self.root/'ledger'])
        self.assertEqual(self.busy(), {100})

    def test_unreadable_fd_dir_of_a_live_child_is_busy(self):
        child = self.proc_at(101, self.lane, ['python3', '-c', 'pass'], parent=100)
        (child/'fd').rmdir(); (child/'fd').write_text('not a dir')
        self.assertEqual(self.busy(), {100})

    def test_sibling_directory_sharing_the_root_prefix_is_not_the_root(self):
        sibling = self.base/'repo-lanes/l/root'; sibling.mkdir(parents=True)
        self.proc_at(104, sibling, ['codex', 'exec', '-C', str(sibling)])
        self.assertEqual(self.busy(), set())

    def test_inside_root_lane_behaviour_is_unchanged(self):
        inlane = self.root/'work/native_lane/inroot'
        self.proc_at(110, inlane, ['codex', 'exec', '-C', str(inlane)])
        self.assertEqual(self.busy(), set())
        self.proc_at(111, self.root, ['codex', 'exec', '-C', str(inlane)])
        self.assertEqual(self.busy(), {111})
        self.proc_at(112, inlane, ['python3', str(self.root/'tools/build/gate_all.py')])
        self.assertEqual(self.busy(), {111, 112})


if __name__ == '__main__':
    unittest.main()
