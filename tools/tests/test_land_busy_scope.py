"""Isolation admission uses real filesystem aliases and a private proc facade."""
import importlib.util
import os
from pathlib import Path
import tempfile
import unittest

TOOLS = Path(__file__).resolve().parents[1]
spec = importlib.util.spec_from_file_location('busy_scope_lander', TOOLS/'lanes/land_packages.py')
G = importlib.util.module_from_spec(spec); spec.loader.exec_module(G)


class LaneProcessScopeTests(unittest.TestCase):
    def setUp(self):
        self.temp = tempfile.TemporaryDirectory(dir=os.environ.get('TMPDIR'))
        self.addCleanup(self.temp.cleanup)
        self.base = Path(self.temp.name).resolve()
        self.root = self.base/'repo'; self.root.mkdir()
        self.lane = self.root/'work/native_lane/r115_opus_town'
        self.scratch = self.lane/'b'; self.scratch.mkdir(parents=True)
        self.proc_root = self.base/'proc'; self.proc_root.mkdir()
        self.gate = self.put(self.scratch/'tools/build/gate_all.py')
        self.real_gate = self.put(self.root/'tools/build/gate_all.py')
        self.argv = ['/usr/bin/python3', str(self.gate), '--workers', '12']
        self.proc = self.proc_at(424242, self.scratch, self.argv)

    def put(self, path, text='pass\n'):
        path.parent.mkdir(parents=True, exist_ok=True); path.write_text(text); return path

    def proc_at(self, pid, cwd, argv, parent=1, env=(), fds=()):
        proc = self.proc_root/str(pid); proc.mkdir()
        (proc/'cwd').symlink_to(cwd, target_is_directory=True)
        (proc/'cmdline').write_bytes(b'\0'.join(os.fsencode(a) for a in argv)+b'\0')
        (proc/'stat').write_text(f'{pid} (fixture) S {parent} 0 0')
        (proc/'environ').write_bytes(b'\0'.join(os.fsencode(s) for s in env)+b'\0')
        (proc/'fd').mkdir()
        for i, target in enumerate(fds): (proc/'fd'/str(i)).symlink_to(target)
        return proc

    def set_args(self, argv):
        (self.proc/'cmdline').write_bytes(b'\0'.join(os.fsencode(a) for a in argv)+b'\0')

    def busy(self, isolated=True, scratch=False):
        return {r['pid'] for r in G.busy_processes(self.root, scratch, isolated, self.proc_root)}

    def test_1225_agent_command_without_receipt_or_pid_is_isolated(self):
        # Preserve the reported command exactly, only transplant its checkout
        # prefix so this test never reads or gates a canonical tree.
        canonical = Path.home()/'azure-clean'
        reported = ['/usr/bin/python3', str(canonical/'work/native_lane/r115_opus_town/b/tools/build/gate_all.py'), '--workers', '12']
        transplanted = [s.replace(str(canonical), str(self.root)) for s in reported]
        self.assertEqual(transplanted, self.argv)
        self.assertFalse((self.lane/'lane.pid').exists())
        self.assertFalse((self.lane/'isolation.json').exists())
        self.assertTrue(G.isolated_lane(self.proc, self.root, self.proc_root))
        self.assertEqual(self.busy(), set())

    def test_default_mode_still_refuses_the_private_gate(self):
        self.assertEqual(self.busy(False), {424242})

    def test_canonical_cwd_and_canonical_gate_are_busy(self):
        (self.proc/'cwd').unlink(); (self.proc/'cwd').symlink_to(self.root)
        self.set_args(['/usr/bin/python3', str(self.real_gate), '--workers', '12'])
        self.assertEqual(self.busy(), {424242})

    def test_lane_cwd_does_not_exempt_a_canonical_script(self):
        self.set_args(['/usr/bin/python3', str(self.real_gate)])
        self.assertEqual(self.busy(), {424242})

    def test_canonical_cwd_is_busy_even_if_all_paths_name_its_lane(self):
        (self.proc/'cwd').unlink(); (self.proc/'cwd').symlink_to(self.root)
        self.assertEqual(self.busy(), {424242})

    def test_relative_script_inside_lane_is_isolated(self):
        self.set_args(['python3', 'tools/build/gate_all.py', '--workers', '12'])
        self.assertEqual(self.busy(), set())

    def test_direct_script_inside_lane_is_isolated(self):
        self.set_args([str(self.gate), '--workers', '12'])
        self.assertEqual(self.busy(), set())

    def test_direct_canonical_script_is_busy(self):
        self.set_args([str(self.real_gate), '--workers', '12'])
        self.assertEqual(self.busy(), {424242})

    def test_nested_round_root_scratch_is_isolated(self):
        cwd = self.root/'work/native_lane/_r116/root/work/native_lane/agent/scratch'
        cwd.mkdir(parents=True)
        script = self.put(self.root/'work/native_lane/_r116/root/tools/build/gate_all.py')
        (self.proc/'cwd').unlink(); (self.proc/'cwd').symlink_to(cwd)
        self.set_args(['/usr/bin/python3', str(script), '--workers', '12'])
        self.assertEqual(self.busy(), set())

    def test_absolute_output_can_be_not_yet_created_inside_lane(self):
        self.set_args(self.argv+['--receipts', str(self.scratch/'new/output')])
        self.assertEqual(self.busy(), set())

    def test_each_canonical_mutable_root_argument_stays_busy(self):
        for name in ('build_ovl', 'build_ovl_gate', 'build_slus', 'src'):
            with self.subTest(root=name):
                self.set_args(self.argv+['--root', str(self.root/name)])
                self.assertEqual(self.busy(), {424242})

    def test_option_equals_canonical_output_is_busy(self):
        self.set_args(self.argv+['--receipts='+str(self.root/'build_ovl_gate/result')])
        self.assertEqual(self.busy(), {424242})

    def test_short_concatenated_canonical_path_is_busy(self):
        self.set_args(self.argv+['-B'+str(self.root/'build_slus')])
        self.assertEqual(self.busy(), {424242})

    def test_absolute_input_from_a_different_lane_is_busy(self):
        other = self.root/'work/native_lane/other/source.c'
        self.put(other)
        self.set_args(self.argv+['--source', str(other)])
        self.assertEqual(self.busy(), {424242})

    def test_relative_argument_escaping_the_lane_is_busy(self):
        relative = os.path.relpath(self.root/'src/row.c', self.scratch)
        self.set_args(self.argv+['--source', relative])
        self.assertEqual(self.busy(), {424242})

    def test_script_symlink_into_canonical_tools_is_busy(self):
        self.gate.unlink(); self.gate.symlink_to(self.real_gate)
        self.assertEqual(self.busy(), {424242})

    def test_output_parent_symlink_into_canonical_build_is_busy(self):
        target = self.root/'build_ovl_gate'; target.mkdir()
        (self.scratch/'aliased-output').symlink_to(target, target_is_directory=True)
        self.set_args(self.argv+['--out', str(self.scratch/'aliased-output/not-created')])
        self.assertEqual(self.busy(), {424242})

    def test_canonical_source_alias_into_lane_does_not_hide_shared_ownership(self):
        source = self.scratch/'shared-source'; source.mkdir()
        (self.root/'src').symlink_to(source)
        self.set_args(self.argv+['--root', str(self.root/'src')])
        self.assertEqual(self.busy(), {424242})

    def test_canonical_binary_executable_is_not_a_system_launcher_exception(self):
        binary = self.put(self.root/'build_slus/gate_all.py.bin')
        self.set_args([str(binary)])
        self.assertFalse(G.isolated_lane(self.proc, self.root, self.proc_root))

    def test_cwd_alias_into_canonical_source_is_busy(self):
        target = self.root/'src'; target.mkdir()
        (self.lane/'aliased-cwd').symlink_to(target)
        (self.proc/'cwd').unlink(); (self.proc/'cwd').symlink_to(self.lane/'aliased-cwd')
        self.assertEqual(self.busy(), {424242})

    def test_codex_parent_and_same_lane_child_are_isolated_without_receipts(self):
        self.set_args(['codex', 'exec', '-C', str(self.lane), '-o', str(self.lane/'last_message.txt'), 'task'])
        child = self.proc_at(424243, self.scratch, self.argv, parent=424242)
        self.assertEqual(self.busy(), set())

    def mcp_helper(self, argv=None, fds=(), env=(), cwd=None):
        """codex's global ghidra-mcp bridge: an interpreter + script in a sibling checkout, cwd inherited from the lane."""
        self.set_args(['codex', 'exec', '-C', str(self.lane), '-o', str(self.lane/'last_message.txt'), '-'])
        sibling = self.base/'sibling-checkout'; sibling.mkdir(exist_ok=True)
        bridge = self.put(sibling/'.venv/bin/bridge-mcp-ghidra')
        argv = argv or [str(sibling/'.venv/bin/python3'), str(bridge), '--transport', 'stdio']
        return self.proc_at(424243, cwd or self.lane, argv, parent=424242, fds=fds, env=env)

    def test_codex_global_mcp_helper_with_the_lane_cwd_is_isolated(self):
        self.mcp_helper(fds=('pipe:[7]', str(self.base/'sibling-checkout/log.txt'), str(self.lane/'mcp.log')))
        self.assertEqual(self.busy(), set())

    def test_codex_global_mcp_helper_with_an_outside_cwd_is_isolated(self):
        self.mcp_helper(cwd=self.base)
        self.assertEqual(self.busy(), set())

    def test_mcp_helper_running_inline_code_stays_busy(self):
        self.mcp_helper(argv=['/usr/bin/python3', '-c', 'import os'], cwd=self.base)
        self.assertEqual(self.busy(), {424242})

    def test_helper_with_a_canonical_relative_path_stays_busy(self):
        self.mcp_helper(argv=['/usr/bin/cat', '../../../ledger/rows.jsonl'])
        self.assertEqual(self.busy(), {424242})

    def test_mcp_helper_with_a_root_fd_stays_busy(self):
        self.mcp_helper(fds=(str(self.root/'ledger/rows.jsonl'),))
        self.assertEqual(self.busy(), {424242})

    def test_mcp_helper_naming_the_root_stays_busy(self):
        self.mcp_helper(argv=['/bin/bash', str(self.base/'sibling-checkout/x.sh'), '--repo', str(self.root)+'/'])
        self.assertEqual(self.busy(), {424242})

    def test_mcp_helper_with_a_canonical_gate_override_stays_busy(self):
        self.mcp_helper(env=('SRCROOT='+str(self.root/'src'),))
        self.assertEqual(self.busy(), {424242})

    def test_child_of_an_outside_helper_in_the_root_stays_busy(self):
        self.mcp_helper()
        self.proc_at(424244, self.root, ['sleep', '60'], parent=424243)
        self.assertEqual(self.busy(), {424242})

    def test_outside_cwd_symlinked_into_the_root_stays_busy(self):
        alias = self.base/'alias'; alias.symlink_to(self.root/'src', target_is_directory=True)
        (self.root/'src').mkdir(exist_ok=True)
        self.set_args(['codex', 'exec', '-C', str(self.lane), 'task'])
        self.proc_at(424243, alias, ['sleep', '60'], parent=424242)
        self.assertEqual(self.busy(), {424242})

    def test_codex_child_with_canonical_cwd_is_ambiguous_and_stays_busy(self):
        self.set_args(['codex', 'exec', '-C', str(self.lane), '-o', str(self.lane/'last_message.txt'), 'task'])
        self.proc_at(424243, self.root, self.argv, parent=424242)
        self.assertEqual(self.busy(), {424242, 424243})

    def test_busy_child_does_not_inherit_a_parent_exemption(self):
        self.set_args(['codex', 'exec', '-C', str(self.lane), 'task'])
        self.proc_at(424243, self.scratch, self.argv+['--root', str(self.root/'src')], parent=424242)
        self.assertEqual(self.busy(), {424242, 424243})

    def test_child_in_another_lane_blocks_its_parent(self):
        self.set_args(['codex', 'exec', '-C', str(self.lane), 'task'])
        other = self.root/'work/native_lane/other'; other.mkdir()
        script = self.put(other/'tools/build/gate_all.py')
        self.proc_at(424243, other, ['python3', str(script)], parent=424242)
        self.assertEqual(self.busy(), {424242})

    def test_unmarked_child_with_canonical_cwd_still_blocks_its_parent(self):
        self.proc_at(424243, self.root, ['sleep', '60'], parent=424242)
        self.assertEqual(self.busy(), {424242})

    def test_unmarked_same_lane_binary_child_is_isolated(self):
        self.proc_at(424243, self.scratch, ['/usr/bin/ninja', '-C', str(self.scratch/'build')], parent=424242)
        self.assertEqual(self.busy(), set())

    def test_shared_readonly_toolchain_inputs_are_isolated(self):
        # r118: no lander writes toolchain/.venv/baserom (scratch roots symlink them); other canonical inputs stay busy.
        self.proc_at(424243, self.scratch, ['/usr/bin/gcc', '-B'+str(self.root/'toolchain'), '-o', str(self.scratch/'x.o')], parent=424242)
        self.assertEqual(self.busy(), set())

    def test_shared_canonical_tool_inputs_stay_busy(self):
        self.proc_at(424243, self.scratch, ['/usr/bin/gcc', '-B'+str(self.root/'tools'), '-o', str(self.scratch/'x.o')], parent=424242)
        self.assertEqual(self.busy(), {424242})

    def codex_child(self, argv, cwd=None, env=()):
        self.set_args(['codex', 'exec', '-C', str(self.lane), '-o', str(self.lane/'last_message.txt'), '-'])
        return self.proc_at(424243, cwd or self.scratch, argv, parent=424242, env=env)

    def test_codex_shell_wrapper_with_lane_paths_is_isolated(self):
        self.codex_child(['/bin/bash', '-lc', "mkdir -p fixtures && cp -a %s/work/native_lane/other/x.json fixtures/ && "
                          "PYTHONDONTWRITEBYTECODE=1 python3 ../../tools/lanes/lanekit/oracle_search.py --out evidence/v > evidence/v.log 2>&1"
                          % self.root])
        self.assertEqual(self.busy(), set())

    def test_codex_shell_wrapper_naming_the_canonical_tree_stays_busy(self):
        for text in ('python3 %s/tools/build/gate_all.py' % self.root, 'ls %s/src/dungeon/*.c' % self.root,
                     'cd ../../../.. && python3 tools/build/gate_all.py', 'cat ../../../../ledger/rows.jsonl'):
            with self.subTest(text=text):
                self.codex_child(['bash', '-lc', text])
                try: self.assertIn(424242, self.busy())
                finally:
                    import shutil; shutil.rmtree(self.proc_root/'424243')

    def test_shell_wrapper_reading_the_shared_toolchain_is_isolated(self):
        self.codex_child(['bash', '-lc', '%s/toolchain/gcc/cc1 -quiet x.i -o x.s' % self.root])
        self.assertEqual(self.busy(), set())

    def test_stdin_python_inside_a_lane_owned_kit_root_is_isolated(self):
        self.put(self.scratch/'tools/common.py')
        self.codex_child(['python3', '-'], env=('PYTHONPATH='+str(self.scratch/'tools/lanes/lanekit'),))
        self.assertEqual(self.busy(), set())

    def test_stdin_python_whose_kit_root_is_canonical_stays_busy(self):
        self.put(self.root/'tools/common.py')
        self.codex_child(['python3', '-'], cwd=self.lane)
        self.assertEqual(self.busy(), {424242})

    def test_inline_python_with_a_canonical_pythonpath_stays_busy(self):
        self.put(self.scratch/'tools/common.py')
        self.codex_child(['python3', '-c', 'import lab'], env=('PYTHONPATH='+str(self.root/'tools/lanes/lanekit'),))
        self.assertEqual(self.busy(), {424242})

    def test_module_form_descendant_stays_busy(self):
        self.put(self.scratch/'tools/common.py')
        self.codex_child(['python3', '-m', 'gate_all'])
        self.assertIn(424242, self.busy())

    def test_each_canonical_mutable_root_fd_stays_busy(self):
        for name in ('build_ovl', 'build_ovl_gate', 'build_slus', 'src'):
            with self.subTest(root=name):
                fd = self.proc/'fd/3'; fd.symlink_to(self.root/name/'result')
                self.assertEqual(self.busy(), {424242}); fd.unlink()

    def test_hidden_canonical_metadata_descriptor_is_ambiguous(self):
        for name in ('ledger/rows.jsonl','config/names.tsv','tmp/shared.o'):
            with self.subTest(path=name):
                fd = self.proc/'fd/3'; fd.symlink_to(self.root/name)
                self.assertEqual(self.busy(), {424242}); fd.unlink()

    def test_shared_toolchain_fd_is_isolated(self):
        # r118: gdb holds the shared cc1 open while a lane runs the oracle
        (self.proc/'fd/3').symlink_to(self.root/'toolchain/compilers/gcc-2.7.2-cdk/cc1')
        self.assertEqual(self.busy(), set())

    def test_deleted_canonical_fd_is_still_busy(self):
        (self.proc/'fd/3').symlink_to(str(self.root/'build_slus/result')+' (deleted)')
        self.assertEqual(self.busy(), {424242})

    def test_pipe_and_lane_output_fds_are_isolated(self):
        (self.proc/'fd/1').symlink_to('pipe:[123]')
        (self.proc/'fd/2').symlink_to(self.lane/'gate.log')
        self.assertEqual(self.busy(), set())

    def test_canonical_environment_override_stays_busy(self):
        for key in ('GATE_BUILD_ROOT','GATE_JOURNAL','SRCROOT'):
            with self.subTest(key=key):
                (self.proc/'environ').write_bytes(os.fsencode(key+'='+str(self.root/'build_ovl_gate'))+b'\0')
                self.assertEqual(self.busy(), {424242})

    def test_private_relative_environment_override_is_isolated(self):
        (self.proc/'environ').write_bytes(b'GATE_BUILD_ROOT=build_ovl_gate\0GATE_JOURNAL=work/gate.jsonl\0')
        self.assertEqual(self.busy(), set())

    def test_canonical_environment_alias_does_not_hide_shared_ownership(self):
        source = self.scratch/'shared-source'; source.mkdir()
        (self.root/'src').symlink_to(source)
        (self.proc/'environ').write_bytes(os.fsencode('SRCROOT='+str(self.root/'src'))+b'\0')
        self.assertEqual(self.busy(), {424242})

    def test_prompt_with_an_embedded_path_is_ambiguous(self):
        self.set_args(['codex', 'exec', 'run '+str(self.root/'src/row.c')])
        self.assertEqual(self.busy(), {424242})

    def test_unmodelled_path_assignment_or_uri_is_ambiguous(self):
        for value in ('output='+str(self.root/'src/result'), 'file:'+str(self.root/'src/result')):
            with self.subTest(value=value):
                self.set_args(self.argv+[value]); self.assertEqual(self.busy(), {424242})

    def test_path_with_spaces_inside_the_lane_is_isolated(self):
        self.set_args(self.argv+['--receipts', str(self.scratch/'output receipts/report.json')])
        self.assertEqual(self.busy(), set())

    def test_unknown_inline_python_and_shell_commands_stay_busy(self):
        for argv in (['python3', '-c', 'run("tools/build/gate_all.py")'],
                     ['bash', '-lc', 'python3 tools/build/gate_all.py']):
            with self.subTest(argv=argv):
                self.set_args(argv); self.assertEqual(self.busy(), {424242})

    def test_module_form_gate_is_ambiguous_and_stays_busy(self):
        self.set_args(['python3', '-m', 'tools.build.gate_all', '--workers', '12'])
        self.assertEqual(self.busy(), {424242})
        self.assertEqual(self.busy(False), set(), 'default recognition remains unchanged')

    def test_attached_module_form_gate_is_ambiguous_and_stays_busy(self):
        self.set_args(['python3', '-mgate_all', '--workers', '12'])
        self.assertEqual(self.busy(), {424242})
        self.assertEqual(self.busy(False), set())

    def test_inline_module_reference_without_a_file_suffix_stays_busy(self):
        self.set_args(['python3', '-c', 'from tools.build import gate_all; gate_all.main()'])
        self.assertEqual(self.busy(), {424242})

    def test_private_certificate_batch_is_isolated_but_canonical_batch_is_busy(self):
        script = self.put(self.scratch/'tools/lanes/certify_batch.py')
        self.set_args(['python3', str(script), '--root', str(self.scratch)])
        self.assertEqual(self.busy(), set())
        self.set_args(['python3', str(script), '--root', str(self.root)])
        self.assertEqual(self.busy(), {424242})

    def test_missing_script_is_ambiguous(self):
        self.gate.unlink(); self.assertEqual(self.busy(), {424242})

    def test_missing_cwd_or_stat_stays_busy_in_isolated_mode(self):
        for filename in ('cwd','stat'):
            with self.subTest(filename=filename):
                saved = self.proc/(filename+'.saved'); (self.proc/filename).rename(saved)
                self.assertEqual(self.busy(), {424242}); saved.rename(self.proc/filename)

    def test_missing_fd_inventory_stays_busy(self):
        (self.proc/'fd').rmdir(); self.assertEqual(self.busy(), {424242})

    def test_missing_environment_stays_busy(self):
        (self.proc/'environ').unlink(); self.assertEqual(self.busy(), {424242})

    def test_malformed_single_blob_argv_is_not_proof(self):
        (self.proc/'cmdline').write_bytes((' '.join(self.argv)).encode()+b'\0')
        self.assertEqual(self.busy(), {424242})

    def test_lane_base_directory_without_a_lane_is_busy(self):
        (self.proc/'cwd').unlink(); (self.proc/'cwd').symlink_to(self.root/'work/native_lane')
        self.assertEqual(self.busy(), {424242})

    def test_scratch_filter_still_ignores_unrelated_checkouts(self):
        outside = self.base/'unrelated'; outside.mkdir()
        script = self.put(outside/'tools/build/gate_all.py')
        (self.proc/'cwd').unlink(); (self.proc/'cwd').symlink_to(outside)
        self.set_args(['python3', str(script)])
        self.assertEqual(self.busy(scratch=True), set())
        self.assertEqual(self.busy(scratch=False), {424242})


if __name__ == '__main__':
    unittest.main()
