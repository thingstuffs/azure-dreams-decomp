import sys
import unittest
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import tu_reference as R


class ReferenceTests(unittest.TestCase):
    def group(self, gid, sites):
        return dict(group_id=gid, container='town', level='inferred-weak', member_rows=sites)

    def reference(self, reason):
        return dict(gid='old', category='placed_or_unavailable_members', reason=reason)

    def test_unregistered_diagnostic_suffix_does_not_become_an_anchor(self):
        reason = R.PREFIX + 'unregistered@9C0054,unregistered@9C0E6C; unregistered member unregistered@9C0054'
        groups = [dict(self.group('new', 'town/a;unregistered@9C0054;town/b;unregistered@9C0E6C'), container='dungeon')]
        found = R.match([self.reference(reason)], groups)
        self.assertEqual(found[0]['status'], 'unique_fresh_candidate')
        self.assertEqual(found[0]['anchors'], 'unregistered@9C0054;unregistered@9C0E6C')
        self.assertEqual(found[0]['historical_membership'], 'unavailable')

    def test_nested_candidates_remain_ambiguous(self):
        groups = [self.group('short', 'town/a;town/b'), self.group('long', 'town/a;town/b;town/c')]
        found = R.match([self.reference(R.PREFIX + 'town/a,town/b; placements=town/a->town/h')], groups)
        self.assertEqual([r['fresh_group'] for r in found], ['short', 'long'])
        self.assertTrue(all(r['status'] == 'ambiguous_fresh_candidates' for r in found))

    def test_order_and_duplicate_occurrences_are_not_sets(self):
        self.assertFalse(R.ordered_within(['town/b', 'town/a'], ['town/a', 'town/b']))
        self.assertFalse(R.ordered_within(['town/a', 'town/a'], ['town/a', 'town/b']))
        self.assertTrue(R.ordered_within(['town/a', 'town/a'], ['town/a', 'town/b', 'town/a']))

    def test_numeric_id_supplies_no_anchors(self):
        found = R.match([self.reference('Missing original ordered member list; old numeric ID cannot establish membership.')],
                        [self.group('old', 'town/a;town/b')])
        self.assertEqual(found[0]['status'], 'no_reference_anchors')
        self.assertEqual(found[0]['fresh_group'], '')

    def test_tuple_digest_survives_group_renumbering(self):
        ref = self.reference(R.PREFIX + 'town/a')
        one = R.match([ref], [self.group('one', 'town/a;town/b')])[0]
        two = R.match([ref], [self.group('two', 'town/a;town/b')])[0]
        self.assertEqual(one['tuple_sha256'], two['tuple_sha256'])
        self.assertNotEqual(one['tuple_sha256'], R.tuple_key('town', ['town/b', 'town/a']))
        self.assertNotEqual(one['tuple_sha256'], R.tuple_key('dungeon', ['town/a', 'town/b']))

    def test_bad_clause_refuses_instead_of_matching_a_subset(self):
        for text in [R.PREFIX + 'town/a,', R.PREFIX + 'town/a,garbage']:
            with self.assertRaises(ValueError):
                R.anchors(text)

    def test_byte_snapshot_binds_the_order_load_map_and_payload(self):
        group = dict(self.group('fresh', 'town/a;unregistered@4'), image='town/img',
                     foff_first='0', foff_end='8', evidence='CL:town/a')
        unit = dict(summary=dict(container='town', image='town/img', unit='town/img', delta='0x80000000'),
                    functions=[dict(row='town/a', home='town/a', foff=0, end=4),
                               dict(row=None, home=None, foff=4, end=8)])
        one = R.freeze(group, unit, b'abcdefgh')
        renumbered = R.freeze(dict(group, group_id='different'), unit, b'abcdefgh')
        changed = R.freeze(group, unit, b'abcdefgx')
        self.assertEqual(one['content_sha256'], renumbered['content_sha256'])
        self.assertNotEqual(one['content_sha256'], changed['content_sha256'])
        self.assertEqual(one['members'][1]['site'], 'unregistered@4')
        with self.assertRaisesRegex(ValueError, 'membership'):
            R.freeze(dict(group, member_rows='unregistered@4;town/a'), unit, b'abcdefgh')
        with self.assertRaisesRegex(ValueError, 'range'):
            R.freeze(group, unit, b'abc')


if __name__ == '__main__':
    unittest.main()
