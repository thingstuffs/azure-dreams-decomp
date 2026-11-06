import unittest
import json
import tempfile
from collections import Counter
from pathlib import Path

from view_match import rank, signature, kind_edges, candidates, apply_retail_signatures, shared_shadow_rows


class ViewMatchTests(unittest.TestCase):
    def test_signedness_and_size_are_part_of_shape(self):
        view = {'size': 8, 'signature': signature([(0, 1, 'unsigned char'), (4, 2, 'short')])}
        good = {'size': 8, 'signature': signature([(0, 1, 'unsigned char'), (4, 2, 'short')])}
        bad = {'size': 8, 'signature': signature([(0, 1, 'signed char'), (4, 2, 'short')])}
        short = {'size': 5, 'signature': good['signature']}
        self.assertEqual(rank(view, good), (1, 2))
        self.assertEqual(rank(view, bad), (0.5, 1))
        self.assertEqual(rank(view, short), (0, 0))

    def test_creator_evidence_is_attached_to_view_only(self):
        data = {'kinds': [{'kind': 'example', 'views': ['src/a.c:S_12345678_0'],
                           'creators': [{'alloc': 'allocate_list_node'}],
                           'callbacks': [{'func': 'tick'}], 'extent': 8}]}
        with tempfile.TemporaryDirectory() as td:
            path = Path(td) / 'kinds.json'
            path.write_text(json.dumps(data))
            edges = kind_edges(path)
        view = {'name': 'S_12345678_0', 'file': 'src/a.c', 'size': 8,
                'signature': {(0, 4, 's'), (4, 4, 's')}}
        record = {'name': 'NamedRecord', 'file': 'include/named.h', 'size': 8,
                  'signature': view['signature']}
        row = candidates([view], [record], Counter(), edges)[0]
        self.assertEqual(row[10:14], ('creator_site', 'example', 1, 1))

    def test_retail_load_replaces_declared_sign_at_observed_offset(self):
        view = {'name': 'S_12345678_0', 'file': 'src/a.c',
                'signature': {(2, 2, 's'), (4, 1, 'u')}}
        with tempfile.TemporaryDirectory() as td:
            path = Path(td) / 'sites.tsv'
            path.write_text('status\tbase_kind\tdirection\tbase_type\tretail_sign\toffset\tdeclared_width\n'
                            'mapped\tview\tr\tsrc/a.c:S_12345678_0\tu\t2\t2\n')
            apply_retail_signatures([view], path)
        self.assertEqual(view['signature'], {(2, 2, 'u'), (4, 1, 'u')})
        self.assertEqual(view['retail_sites'], 1)

    def test_shared_shadow_is_only_an_unproven_candidate(self):
        view = {'name': 'S_12345678_0', 'file': 'src/a.c', 'size': 160,
                'signature': {(150, 2, 'u'), (154, 1, 'u')}}
        record = {'name': 'ActorRecord', 'file': 'include/actor.h', 'size': 160,
                  'signature': view['signature']}
        ranked = candidates([view], [record], Counter())
        access = {'status': 'mapped', 'base_kind': 'view', 'direction': 'r',
                  'opcode': 'lhu', 'base_type': 'src/a.c:S_12345678_0',
                  'offset': '150', 'declared_width': '2', 'member_path': 'timer'}
        rows = shared_shadow_rows(ranked, [access], [('ActorRecord', 'action_timer', 150, 2)])
        self.assertEqual(len(rows), 1)
        self.assertEqual(rows[0][2:6], ('ActorRecord', 'action_timer', 150, 2))
        self.assertEqual(rows[0][-7:], (0, 0, 0, 1, 0, 'unsigned', 'unproven'))


if __name__ == '__main__':
    unittest.main()
