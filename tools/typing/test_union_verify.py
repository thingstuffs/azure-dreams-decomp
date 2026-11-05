import unittest

from tools.typing.union_verify import verify


class UnionVerifyTests(unittest.TestCase):
    def test_keeps_reviewed_proof_and_normalizes_byte_hold(self):
        template = {
            'kind': 'sign_pun',
            'members': [{'name': 's'}, {'name': 'u'}],
            'uses': {'s': {'src': 1, 'include': 0}, 'u': {'src': 0, 'include': 0}},
        }
        rows = [
            dict(template, status='proven-by-bytes', evidence='Byte diff at +0x12'),
            dict(template, status='proven', evidence='UNION: creator and reader use one object'),
            dict(template, status='unproven', evidence=''),
        ]
        reviewed = list(verify(rows))
        self.assertEqual([row['status'] for row, _, _ in reviewed],
                         ['unproven', 'proven', 'retire'])
        self.assertEqual(reviewed[0][0]['hold_reason'], 'bytes')
        self.assertEqual(reviewed[0][0]['evidence'], 'Byte diff at +0x12')


    def test_keeps_manual_retirement_of_a_historical_row(self):
        row = {
            'kind': 'sign_pun', 'count_basis': 'retired_historical',
            'members': [{'name': 's'}, {'name': 'u'}],
            'uses': {'s': {'src': 1, 'include': 0}, 'u': {'src': 1, 'include': 0}},
            'status': 'retire', 'evidence': 'Entire typedef was unreferenced.'
        }
        (reviewed, _, verdict), = list(verify([row]))
        self.assertEqual(reviewed['status'], 'retire')
        self.assertEqual(reviewed['evidence'], 'Entire typedef was unreferenced.')
        self.assertEqual(verdict, 'retire')


    def test_keeps_manual_unproven_initializer_review(self):
        row = {
            'kind': 'packed', 'members': [{'name': 'pairs'}, {'name': 'bytes'}],
            'uses': {'pairs': {'src': 0, 'include': 0}, 'bytes': {'src': 1, 'include': 0}},
            'status': 'unproven', 'evidence': 'UNION: positional initializer uses pairs.'
        }
        (reviewed, _, verdict), = list(verify([row]))
        self.assertEqual(reviewed['status'], 'unproven')
        self.assertEqual(verdict, 'unproven')


    def test_keeps_manual_retirement_hold(self):
        row = {
            'kind': 'packed', 'members': [{'name': 'word'}, {'name': 'halves'}],
            'uses': {'word': {'src': 0, 'include': 0}, 'halves': {'src': 1, 'include': 0}},
            'status': 'retire', 'evidence': 'UNION: graph projection needs repair.'
        }
        (reviewed, _, verdict), = list(verify([row]))
        self.assertEqual(reviewed['status'], 'retire')
        self.assertEqual(verdict, 'retire')
        self.assertEqual(reviewed['evidence'], row['evidence'])


if __name__ == '__main__':
    unittest.main()
