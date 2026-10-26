"""A replayed merge needs layout and byte-bound provenance for every member."""
import hashlib
import json
from pathlib import Path
import sys
import tempfile
import unittest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
from gate import source_layout as L


class MergedLayoutTests(unittest.TestCase):
    def test_evidenced_data_shares_its_inlined_owner_and_wrapper(self):
        for kind in ('function_table', 'descriptor_table', 'native_prefix'):
            with self.subTest(kind=kind), tempfile.TemporaryDirectory() as directory:
                root = Path(directory)
                target, rows, _ = self.fixture(root)
                data = dict(id='town/D_choices', container='town',
                    c_path='overlays/town/D_choices.c', row_kind='data',
                    data_kind=kind, ownership_status='evidenced', owner=rows[0]['id'])
                self.write(root, 'rows', rows + [data])
                self.write(root, 'layout', [dict(id=r['id'], path=target) for r in rows + [data]])
                self.write(root, 'tu_layout', [dict(old='src/town/modules/list.c', new=target)])
                self.assertEqual(L.validate(root), 4)

                data['ownership_status'] = 'pending'
                self.write(root, 'rows', rows + [data])
                with self.assertRaises(ValueError):
                    L.validate(root)

    def test_inlined_descriptor_cannot_claim_a_different_source(self):
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            target, rows, _ = self.fixture(root)
            other = 'src/town/scene/other.c'
            (root / other).write_text('int choices[4];\n')
            data = dict(id='town/D_choices', container='town',
                c_path='overlays/town/D_choices.c', row_kind='data',
                data_kind='descriptor_table', ownership_status='evidenced', owner=rows[0]['id'])
            self.write(root, 'rows', rows + [data])
            self.write(root, 'layout', [dict(id=r['id'], path=target) for r in rows]
                + [dict(id=data['id'], path=other)])
            with self.assertRaisesRegex(ValueError, 'source differs from code owner'):
                L.validate(root)


    def fixture(self, root):
        target = 'src/town/scene/object/list.c'
        (root / 'ledger').mkdir()
        (root / target).parent.mkdir(parents=True)
        pieces = [b'int prepend(void) { return 1; }\n',
                  b'int append(void) { return 2; }\n',
                  b'int initialize(void) { return 3; }\n']
        (root / target).write_bytes(b''.join(pieces))
        rows, layout, inline = [], [], []
        offset = 0
        for order, piece in enumerate(pieces, 1):
            rid = 'town/member' + str(order)
            old = 'src/town/member' + str(order) + '.c'
            rows.append(dict(id=rid, container='town', c_path=old))
            layout.append(dict(id=rid, path=target))
            inline.append(dict(tu_old=target, tu_new=target, member=old,
                member_id=rid, manifest_key='list', order=order, offset=offset,
                source_sha256=hashlib.sha256(piece).hexdigest(), bytes=len(piece),
                inlined_bytes=len(piece), original_includes=[]))
            offset += len(piece)
        for name, records in [('rows', rows), ('layout', layout), ('layout_inline', inline)]:
            self.write(root, name, records)
        return target, rows, inline

    def write(self, root, name, records):
        (root / ('ledger/' + name + '.jsonl')).write_text(
            ''.join(json.dumps(record) + '\n' for record in records))

    def test_three_rows_share_only_their_proven_physical_tu(self):
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            target, rows, inline = self.fixture(root)
            self.assertEqual(L.inline_records(root), inline)
            self.assertEqual([L.row_relative(row, root) for row in rows], [target] * 3)
            for row in rows:
                projection = L.member_projection(row['id'], root)
                self.assertEqual(projection.count(b'int '), 1)

    def test_layout_without_every_inline_member_refuses_the_reported_collision(self):
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            _, _, inline = self.fixture(root)
            self.write(root, 'layout_inline', inline[:-1])
            with self.assertRaisesRegex(ValueError, 'two rows share a source path'):
                L.mapping(root)

    def test_provenance_alone_does_not_authorize_changed_source(self):
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            target, _, _ = self.fixture(root)
            path = root / target
            path.write_bytes(path.read_bytes().replace(b'return 2', b'return 9'))
            with self.assertRaisesRegex(ValueError, 'inline source_sha256 mismatch'):
                L.inline_records(root)


if __name__ == '__main__':
    unittest.main()
