"""rebase_placeholder_rows rewrites columns 1 and 2 of a names.tsv row and keeps the rest, the 5th (scope) included."""
import json
import sys
import tempfile
import unittest
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / 'tools/headers'))
import rebase_placeholder_rows as R  # noqa: E402


class RebaseKeepsScope(unittest.TestCase):
    def test_five_column_row_keeps_its_scope(self):
        with tempfile.TemporaryDirectory() as td:
            root = Path(td)
            for d in ('config/overlays', 'ledger/splits', 'src/town'):
                (root / d).mkdir(parents=True)
            (root / 'config/overlays/town.rowbase.jsonl').write_text('')
            (root / 'src/town/body.c').write_text('void body(void) {}\n')
            split = dict(func_vram='func_AAAA', result='MATCH', c_path='src/town/body.c', foff=0x1000, size=0x40)
            (root / 'ledger/splits/town.jsonl').write_text(json.dumps(split) + '\n')
            (root / 'config/names.tsv').write_text(
                '# header\n'
                '0x80016000\tfunc_AAAA\tplaced_body\tev text\ttown:0x1000\n'
                '0x80016100\tfunc_80016100\tother_body\tev text\n')
            classes = root / 'classes.tsv'
            classes.write_text('name\tclass\tdetail\n'
                               'placed_body\tC_PLACEHOLDER\tfunc_80016000 linked at 0x80016000 (row town/func_AAAA, '
                               'canonical placed_body); true address 0x80018000 in region 0x1000@0x80018000\n')
            R.main(['--classes', str(classes), '--root', str(root)])
            lines = (root / 'config/names.tsv').read_text().split('\n')
        cols = lines[1].split('\t')
        self.assertEqual(cols, ['0x80018000', 'func_80018000', 'placed_body', 'ev text', 'town:0x1000'])
        self.assertEqual(lines[2].split('\t')[4:], [])


if __name__ == '__main__':
    unittest.main()
