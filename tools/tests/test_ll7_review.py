"""Regression probes for R1 review findings LL7-1 through LL7-8."""
import hashlib
import json
from pathlib import Path
import sys
import unittest
from unittest.mock import patch

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import byte_map_format as B
import guarded_package as P
import layout_apply as A
import layout_compile_identity as I
import source_layout as L
import test_layout_apply as fixture
import test_layout_compile_identity as identity_fixture


class ReviewTests(fixture.TreeApplyTest):
    def install(self, changes):
        package = Path(self.tmp.name) / 'review-package'
        P.export(package, self.root, changes)
        P.apply(package, self.root, live=True)

    def test_ll7_1_skipped_chain_destination_refused(self):
        self.write('src/slus/second.c', '/* Relink of matched slus/member */\n')
        self.tree.write_text('current_path\tproposed_path\n'
                             'src/slus/group.c\tsrc/slus/second.c\n'
                             'src/slus/second.c\tsrc/engine/second.c\n')
        with self.assertRaisesRegex(ValueError, 'destination exists'):
            A.plan(self.root, self.tree)
        self.assertIn('Relink', (self.root / 'src/slus/second.c').read_text())

    def test_ll7_2_moved_tu_header_shadow_refused(self):
        self.write('src/engine/audio/shared.h', '#error wrong header\n')
        with self.assertRaisesRegex(ValueError, 'include target'):
            A.plan(self.root, self.tree)

    def test_ll7_2_stationary_consumer_shadow_refused(self):
        self.write('src/slus/engine/audio/shared.h', '#error wrong header\n')
        with self.assertRaisesRegex(ValueError, 'include target'):
            A.plan(self.root, self.tree, headers=self.headers)

    def test_ll7_2_angle_header_rebased_without_local_shadow(self):
        self.write('src/slus/group.c', '#include <shared.h>\n')
        self.write('src/engine/audio/shared.h', '#error quoted lookup only\n')
        changes, _ = A.plan(self.root, self.tree, headers=self.headers)
        self.assertIn(b'#include <engine/audio/shared.h>', changes['src/engine/audio/group.c'])

    def test_ll7_2_macro_include_requires_preprocessor_review(self):
        self.write('src/slus/group.c', '#define HEADER "shared.h"\n#include HEADER\n')
        with self.assertRaisesRegex(ValueError, 'unsupported include'):
            A.plan(self.root, self.tree)

    def test_ll7_4_commented_jsonl_keeps_prose(self):
        old = 'src/slus/group.c'
        self.write('config/overlays/refs.jsonl', '# historical ' + old + '\n' +
                   json.dumps({'source': old, 'evidence': old}) + '\n')
        changes, _ = A.plan(self.root, self.tree)
        lines = changes['config/overlays/refs.jsonl'].decode().splitlines()
        self.assertEqual(lines[0], '# historical ' + old)
        self.assertEqual(json.loads(lines[1]), {'source': 'src/engine/audio/group.c', 'evidence': old})

    def test_ll7_4_only_live_exact_fields_rewritten(self):
        old = 'src/slus/group.c'
        self.write('config/overlays/refs.json', json.dumps({
            'source': old, 'review_inputs': [old], 'declaration': old, 'c_path': old,
            'evidence': old + ' was reviewed', 'history': [{'source': old}],
            'other': 'prefix/' + old, 'path': old + '.backup'}))
        self.write('docs/evidence/history.md', 'Previously compiled ' + old + '\n')
        changes, _ = A.plan(self.root, self.tree)
        value = json.loads(changes['config/overlays/refs.json'])
        self.assertEqual(value['source'], 'src/engine/audio/group.c')
        self.assertEqual(value['declaration'], 'src/engine/audio/group.c')
        self.assertEqual(value['review_inputs'], ['src/engine/audio/group.c'])
        self.assertEqual(value['c_path'], old)
        self.assertEqual(value['evidence'], old + ' was reviewed')
        self.assertEqual(value['history'][0]['source'], old)
        self.assertEqual(value['other'], 'prefix/' + old)
        self.assertEqual(value['path'], old + '.backup')
        self.assertNotIn('docs/evidence/history.md', changes)

    def test_ll7_4_yaml_comments_and_tsv_history_preserved(self):
        old = 'src/slus/group.c'
        self.write('config/overlays/refs.yaml', '# history ' + old + '\nsource: ' + old + '\n'
                   'evidence: "' + old + ' was reviewed"\n')
        self.write('config/overlays/refs.tsv', 'evidence\tsource\n' + old + '\t' + old + '\n')
        changes, _ = A.plan(self.root, self.tree)
        self.assertEqual(changes['config/overlays/refs.yaml'].decode(), '# history ' + old +
                         '\nsource: src/engine/audio/group.c\nevidence: "' + old + ' was reviewed"\n')
        self.assertEqual(changes['config/overlays/refs.tsv'].decode(),
                         'evidence\tsource\n' + old + '\tsrc/engine/audio/group.c\n')

    def test_ll7_4_manifest_evidence_live_declaration_rewritten(self):
        self.write('config/overlays/modules.json', json.dumps({'modules': [
            {'key': 'group', 'source': 'src/slus/group.c', 'headers': [], 'review_inputs': [],
             'imports': [{'evidence': 'docs/evidence/group.json', 'declaration': 'include/shared.h'}]}]}))
        self.write('docs/evidence/group.json', json.dumps({
            'runtime_views': {'count': {'declaration': 'include/shared.h'}},
            'evidence': 'Previously used include/shared.h', 'history': {'source': 'src/slus/group.c'}}))
        changes, _ = A.plan(self.root, self.tree, headers=self.headers)
        doc = json.loads(changes['docs/evidence/group.json'])
        self.assertEqual(doc['runtime_views']['count']['declaration'], 'include/engine/audio/shared.h')
        self.assertEqual(doc['evidence'], 'Previously used include/shared.h')
        self.assertEqual(doc['history']['source'], 'src/slus/group.c')

    def test_ll7_6_inline_row_identity_must_match_member_file(self):
        self.inline.write_text(self.inline.read_text().replace('slus/member\tgroup', 'slus/missing\tgroup'))
        with self.assertRaisesRegex(ValueError, 'inline row identity'):
            A.plan(self.root, self.tree, inline=self.inline)

    def test_ll7_5_implicit_byte_map_tu_rewritten(self):
        self.tree.write_text('current_path\tproposed_path\n'
                             'src/slus/member.c\tsrc/engine/audio/member.c\n')
        entry = dict(row='slus/member', home='slus/member', tu='src/slus/member.c',
                     foff=0, size=4, vma=0, evidence='historical src/slus/member.c')
        doc = dict(schema='azure-clean.linklist.v1', image='slus/sample', container='slus',
                   foff=0, size=4, vma=0, entries=[entry], census=dict.fromkeys(B.LABELS, 0))
        B.write(self.root / 'link/slus', doc)
        self.write('config/link/slus/sample.json', json.dumps(doc))
        changes, _ = A.plan(self.root, self.tree)
        self.assertIn('link/slus/sample.tsv', changes)
        self.install(changes)
        decoded = B.read_parts([self.root / 'link/slus/sample.tsv'], self.root)
        self.assertEqual(decoded['entries'][0]['tu'], 'src/engine/audio/member.c')
        self.assertEqual(decoded['entries'][0]['evidence'], entry['evidence'])
        self.assertEqual(json.loads((self.root / 'config/link/slus/sample.json').read_text())['entries'][0]['tu'],
                         'src/engine/audio/member.c')

    def test_ll7_6_inline_retires_member_repoints_row_and_checks_hash(self):
        changes, _ = A.plan(self.root, self.tree, headers=self.headers, inline=self.inline)
        self.install(changes)
        self.assertFalse((self.root / 'src/slus/member.c').exists())
        self.assertEqual(L.row_relative('slus/member', self.root), 'src/engine/audio/group.c')
        self.assertEqual(L.validate(self.root), 1)
        target = self.root / 'src/engine/audio/group.c'
        target.write_text(target.read_text().replace('return 1;', 'return 2;'))
        with self.assertRaisesRegex(ValueError, 'source_sha256'):
            L.validate(self.root)

    def test_ll7_6_inline_rejects_actual_conditional_even_with_zero_tsv_depth(self):
        self.write('src/slus/group.c', '#if 1\n#include "member.c"\n#endif\n')
        with self.assertRaisesRegex(ValueError, 'conditional'):
            A.plan(self.root, self.tree, inline=self.inline)

    def test_ll7_6_spliced_conditional_with_quoted_comment_markers_refused(self):
        self.write('src/slus/group.c', 'char *marker = "/*";\n#i\\\nf 1\n#include "member.c"\n#endif\nchar *end = "*/";\n')
        self.inline.write_text(self.inline.read_text().replace('group.c\t2\tmember.c', 'group.c\t4\tmember.c'))
        with self.assertRaisesRegex(ValueError, 'conditional'):
            A.plan(self.root, self.tree, inline=self.inline)

    def test_ll7_6_commented_include_is_not_an_inline_site(self):
        self.write('src/slus/group.c', '/*\n#include "member.c"\n*/\n')
        with self.assertRaisesRegex(ValueError, 'conditional'):
            A.plan(self.root, self.tree, inline=self.inline)

    def test_ll7_6_inlined_rows_follow_another_wrapper_move(self):
        changes, _ = A.plan(self.root, self.tree, inline=self.inline)
        self.install(changes)
        next_tree = self.root / 'next.tsv'
        next_tree.write_text('current_path\tproposed_path\n'
                             'src/engine/audio/group.c\tsrc/engine/sound/group.c\n')
        changes, report = A.plan(self.root, next_tree)
        A.apply_reviewed(self.root, changes, report, report['plan_sha256'])
        self.assertEqual(L.validate(self.root), 1)
        self.assertEqual(L.row_relative('slus/member', self.root), 'src/engine/sound/group.c')
        record = json.loads((self.root / 'ledger/layout_inline.jsonl').read_text())
        self.assertEqual(record['tu_new'], 'src/engine/sound/group.c')

    def test_ll7_7_wrapper_destination_cannot_collide_with_row(self):
        self.write('ledger/tu_layout.jsonl', json.dumps({
            'old': 'src/slus/group.c', 'new': 'src/slus/member.c'}) + '\n')
        with self.assertRaisesRegex(ValueError, 'collid'):
            L.validate(self.root)

    def test_ll7_7_check_refuses_wrapper_on_relocated_row_alias(self):
        self.write('src/slus/group.c', 'int group(void) { return 0; }\n')
        self.write('src/engine/member.c', (self.root / 'src/slus/member.c').read_text())
        (self.root / 'src/slus/member.c').unlink()
        self.write('ledger/layout.jsonl', json.dumps({'id': 'slus/member', 'path': 'src/engine/member.c'}) + '\n')
        self.tree.write_text('current_path\tproposed_path\nsrc/slus/group.c\tsrc/slus/member.c\n')
        with self.assertRaisesRegex(ValueError, 'collid'):
            A.plan(self.root, self.tree)
        self.assertTrue((self.root / 'src/slus/group.c').exists())

    def test_ll7_7_check_rejects_invalid_row_container_before_apply(self):
        self.tree.write_text('current_path\tproposed_path\nsrc/slus/member.c\tsrc/town/member.c\n')
        with self.assertRaisesRegex(ValueError, 'unsafe source path'):
            A.plan(self.root, self.tree)
        self.assertTrue((self.root / 'src/slus/member.c').exists())

    def test_ll7_7_revision_tracks_wrapper_map(self):
        before = L.revision(self.root)
        self.write('ledger/tu_layout.jsonl', json.dumps({
            'old': 'src/slus/group.c', 'new': 'src/engine/audio/group.c'}) + '\n')
        self.assertNotEqual(before, L.revision(self.root))

    def test_ll7_8_consumer_certificate_in_renewal_list(self):
        self.write('config/overlays/modules.json', json.dumps({'modules': [
            {'key': 'consumer', 'source': 'src/slus/consumer.c', 'headers': [], 'review_inputs': []}]}))
        self.write('ledger/modules/overlay_consumer.json', '{}\n')
        _, report = A.plan(self.root, self.tree)
        self.assertIn('ledger/modules/overlay_consumer.json', report['certificates_requiring_renewal'])

    def test_ll7_8_peer_window_certificate_in_renewal_list(self):
        self.write('src/slus/peer.c', 'int peer(void) { return 0; }\n')
        self.write('config/overlays/modules.json', json.dumps({'modules': [
            {'key': 'group', 'source': 'src/slus/group.c', 'headers': [], 'review_inputs': [],
             'container': 'town', 'members': [{'foff': 0, 'size': 4}]},
            {'key': 'peer', 'source': 'src/slus/peer.c', 'headers': [], 'review_inputs': [],
             'container': 'town', 'members': [{'foff': 4, 'size': 4}]}]}))
        self.write('config/overlays/sample.overlay.yaml',
                   'standalone_build:\n  split_results: overlays/town/rows.json\n'
                   '  window: {file_start: 0, file_end: 8}\n')
        self.write('ledger/modules/overlay_peer.json', json.dumps({
            'fingerprint': {'required_windows': ['config/overlays/sample.overlay.yaml']}}))
        _, report = A.plan(self.root, self.tree)
        self.assertIn('ledger/modules/overlay_peer.json', report['certificates_requiring_renewal'])
        fingerprints = report['renewal_input_fingerprints']['ledger/modules/overlay_peer.json']
        self.assertNotEqual(fingerprints['before'], fingerprints['after'])

    def test_ll7_8_unchanged_dependency_guard_rechecked_at_install(self):
        changes, report = A.plan(self.root, self.tree)
        self.write('include/shared.h', 'int changed(void);\n')
        with self.assertRaisesRegex(ValueError, 'protected input guard'):
            A.apply_reviewed(self.root, changes, report, report['plan_sha256'])
        self.assertTrue((self.root / 'src/slus/group.c').exists())

    def test_ll7_8_apply_requires_matching_reviewed_hash(self):
        changes, report = A.plan(self.root, self.tree)
        self.assertRegex(report['plan_sha256'], r'^[0-9a-f]{64}$')
        with self.assertRaisesRegex(ValueError, 'plan'):
            A.apply_reviewed(self.root, changes, report, None)
        self.write('src/slus/group.c', 'int changed(void) { return 9; }\n')
        changes2, report2 = A.plan(self.root, self.tree)
        with self.assertRaisesRegex(ValueError, 'plan'):
            A.apply_reviewed(self.root, changes2, report2, report['plan_sha256'])
        self.assertTrue((self.root / 'src/slus/group.c').exists())

    def test_ll7_8_hash_binds_unchanged_include_inputs(self):
        _, report = A.plan(self.root, self.tree)
        self.write('include/shared.h', 'int another(void);\n')
        _, changed = A.plan(self.root, self.tree)
        self.assertNotEqual(report['plan_sha256'], changed['plan_sha256'])

    def test_ll7_8_rollback_removes_created_directories(self):
        changes, _ = A.plan(self.root, self.tree)
        package = Path(self.tmp.name) / 'broken-package'
        P.export(package, self.root, changes)
        original = Path.replace
        def fail(source, destination):
            if str(destination).endswith('engine/audio/group.c'):
                raise OSError('injected failure')
            return original(source, destination)
        with patch.object(Path, 'replace', fail), self.assertRaises(OSError):
            P.apply(package, self.root, live=True)
        self.assertTrue((self.root / 'src/slus/group.c').exists())
        self.assertFalse((self.root / 'src/engine').exists())


class ConsumerProofTests(identity_fixture.SnapshotTest):
    def test_ll7_3_header_consumers_are_captured_and_compared(self):
        header = self.root / 'include/shared.h'
        header.parent.mkdir()
        header.write_text('int f(void);\n')
        (self.root / 'src/slus/old.c').write_text('#include "shared.h"\nint f(void) { return 1; }\n')
        consumer = self.root / 'src/slus/consumer.c'
        consumer.write_text('#include "shared.h"\nint g(void) { return f(); }\n')
        headers = self.root / 'headers.tsv'
        headers.write_text('current_path\tproposed_path\tdisposition\n'
                           'include/shared.h\tinclude/engine/shared.h\tmove proposed\n')
        recipe = dict(self.recipe, row_id='slus/consumer')
        before = {'src/slus/old.c': self.recipe, 'src/slus/consumer.c': recipe}
        receipt = self.root / 'receipt.jsonl'
        with patch.object(I, 'recipes', return_value=(before, set())), \
             patch.object(I, 'capture_one', side_effect=self.fake) as capture:
            result = I.run(self.root, self.tree, headers=headers, snapshot=receipt)
        self.assertEqual(result['physical_tus'], 2)
        self.assertEqual({call.args[1] for call in capture.call_args_list}, set(before))
        (self.root / 'src/engine').mkdir()
        (self.root / 'src/slus/old.c').rename(self.root / 'src/engine/new.c')
        after = {'src/engine/new.c': self.recipe, 'src/slus/consumer.c': recipe}
        def changed(root, rel, rec):
            data = self.fake(root, rel, rec)
            if rel == 'src/slus/consumer.c':
                data['canonical_object_sha256'] = 'changed'
            return data
        with patch.object(I, 'recipes', return_value=(after, set())), \
             patch.object(I, 'capture_one', side_effect=changed), \
             self.assertRaisesRegex(ValueError, 'object changed.*consumer'):
            I.run(self.root, self.tree, headers=headers, compare=receipt)


if __name__ == '__main__':
    unittest.main()
