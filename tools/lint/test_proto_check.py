"""Return and arity candidate policy tests."""
import unittest

from proto_check import M, check, mismatch


class ProtoPolicyTests(unittest.TestCase):
    def test_alias_normalization(self):
        vis = {
            's16': M.TypedefInfo('s16', 'include/common.h', ('short',), 0, '', False),
            's32': M.TypedefInfo('s32', 'include/common.h', ('int',), 0, '', False),
            'Point': M.TypedefInfo('Point', 'include/point.h', ('struct', 'Point'), 0, '', False),
        }
        self.assertEqual(M.canon(('s16',), 0, vis), M.canon(('short',), 0, vis))
        self.assertEqual(M.canon(('s32',), 0, vis), M.canon(('int',), 0, vis))
        self.assertEqual(M.canon(('Point',), 1, vis), M.canon(('struct', 'Point'), 1, vis))

    def test_return_and_explicit_arity(self):
        definition = (('s32', 0, 'int'), (('s16', 0, 'int'),), False)
        self.assertEqual(mismatch(definition, definition), '')
        self.assertEqual(mismatch(definition, (('s32', 0, 'int'), None, False)), '')
        self.assertEqual(mismatch(definition, (('u32', 0, 'int'), (), False)), 'return_type+arity')

    def test_pointer_integer_parameter_kind(self):
        ret = ('void', 0, 'void')
        pointer = ('u16', 1, 'ptr')
        integer = ('s32', 0, 'int')
        other_pointer = ('void', 1, 'ptr')
        self.assertEqual(mismatch((ret, (pointer,), False), (ret, (integer,), False)), 'param_kind')
        self.assertEqual(mismatch((ret, (pointer,), False), (ret, (other_pointer,), False)), '')
        self.assertEqual(mismatch((ret, (pointer,), False), (ret, None, False)), '')
        self.assertEqual(mismatch((ret, (pointer,), False), (ret, (), False)), 'arity')
        self.assertEqual(mismatch((ret, (pointer, integer), False),
                                  (ret, (integer, integer), False)), 'param_kind')

    def test_ratcheted_sites(self):
        baseline = {'candidate_sites': ['a']}
        report = {'candidates': [{'site_id': 'a'}, {'site_id': 'b'}]}
        self.assertEqual(check(report, baseline), ['b'])
