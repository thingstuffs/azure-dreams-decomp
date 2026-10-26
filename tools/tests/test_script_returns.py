"""The census must catch a formerly returning body or a newly consuming poll."""
import importlib.util
from pathlib import Path
import tempfile
import unittest

SPEC = importlib.util.spec_from_file_location('script_returns', Path(__file__).resolve().parents[1] / 'check_script_returns.py')
M = importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(M)


class ScriptReturnTests(unittest.TestCase):
    def site(self, **updates):
        row = dict(container='town', block='m00', file_offset='20', op='call_native',
                   callee='80016000', reads='fd@30', how='self', resolved='f:void:town/f', candidates='f:void:town/f')
        row.update(updates)
        return row

    def audit(self, text, site=None, services=()):
        with tempfile.TemporaryDirectory() as name:
            root = Path(name)
            (root/'f.c').write_text(text)
            return M.audit(root, [site or self.site()], services, lambda rid: 'f.c')

    def test_current_definition_overrides_stale_table_type(self):
        self.assertEqual(self.audit('int f(void) { return 1; }')[0], [])
        self.assertEqual(self.audit('void f(void) {}')[0][0]['reason'], 'void')

    def test_void_pointer_is_value(self):
        self.assertEqual(self.audit('void *f(void) { return 0; }')[0], [])

    def test_attributes_do_not_hide_the_return_type(self):
        for text in ('void __attribute__((unused)) f(void) {}',
                     '__attribute__((unused)) void f(void) {}',
                     'static void f(void) __attribute__((unused)) {}'):
            with self.subTest(text=text):
                self.assertEqual(self.audit(text)[0][0]['reason'], 'void')
        self.assertEqual(self.audit('void * __attribute__((unused)) f(void) {return 0;}')[0], [])

    def test_dead_residue_ignored(self):
        self.assertEqual(self.audit('void f(void) {}', self.site(reads=''))[0], [])

    def test_poll_consumes_without_later_read(self):
        site = self.site(op='poll_service', callee='svc1', resolved='', reads='')
        services = [dict(callee='svc1', source='f.c', function='f')]
        self.assertEqual(self.audit('void f(void) {}', site, services)[0][0]['reason'], 'void')

    def test_unresolved_and_missing_fail(self):
        self.assertEqual(self.audit('int f(void) {return 1;}', self.site(resolved='', how='ambiguous'))[0][0]['reason'], 'ambiguous_callee')
        self.assertEqual(self.audit('int g(void) {return 1;}')[0][0]['reason'], 'missing_definition')

    def test_hold_cannot_cover_another_site_or_candidate(self):
        issue = self.audit('void f(void) {}', self.site(resolved='', how='ambiguous'))[0][0]
        holds = [dict(issue=issue['issue'], evidence='unresolved load image')]
        self.assertEqual(M.check_holds([issue], holds), ([], []))
        changed = self.audit('void f(void) {}', self.site(file_offset='21', resolved='', how='ambiguous'))[0]
        self.assertEqual(len(M.check_holds(changed, holds)[0]), 1)
        changed = self.audit('void f(void) {}', self.site(candidates='f:void:town/g', resolved='', how='ambiguous'))[0]
        self.assertEqual(len(M.check_holds(changed, holds)[0]), 1)
        self.assertEqual(len(M.check_holds([], holds)[1]), 1)

    def test_discarding_indexed_handler_is_ignored(self):
        self.assertFalse(M.consumes(self.site(op='call_indexed_handler')))

    def test_multiple_resolved_placements_are_all_checked(self):
        site = self.site(resolved='f:s32:town/a|g:s32:town/b')
        self.assertEqual(self.audit('int f(void) {return 1;} void g(void) {}', site)[0][0]['reason'], 'void')

    def test_native_fragment_and_module_are_both_checked(self):
        with tempfile.TemporaryDirectory() as name:
            root = Path(name)
            (root/'native.c').write_text('void f(void) {}')
            (root/'module.c').write_text('int f(void) {return 1;}')
            issues, _ = M.audit(root, [self.site()], [], lambda rid: ['native.c', 'module.c'])
            self.assertEqual(issues[0]['reason'], 'void')

    def test_unresolved_placement_cannot_hide_a_confirmed_void_sibling(self):
        with tempfile.TemporaryDirectory() as name:
            root = Path(name)
            (root/'z_void.c').write_text('void f(void) {}')
            site = self.site(resolved='g:s32:town/g|f:s32:town/f')
            for missing in ([], ['a_missing.c']):
                with self.subTest(missing=missing):
                    source_for = lambda rid: missing if rid == 'town/g' else ['z_void.c']
                    issues, _ = M.audit(root, [site], [], source_for)
                    self.assertEqual(issues[0]['reason'], 'void')

    def test_confirmed_void_cannot_be_suppressed_by_a_hold(self):
        issue = self.audit('void f(void) {}')[0][0]
        unknown, _ = M.check_holds([issue], [dict(issue=issue['issue'], evidence='attempted suppression')])
        self.assertEqual(unknown, [issue])

    def test_hold_requires_evidence(self):
        with self.assertRaises(ValueError):
            M.check_holds([], [dict(issue='x', evidence='')])


if __name__ == '__main__':
    unittest.main()
