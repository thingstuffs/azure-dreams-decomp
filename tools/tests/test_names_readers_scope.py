"""Readers of config/names.tsv take the evidence from column 4 alone, so a scope cell (column 5) never joins it."""
import sys
import tempfile
import unittest
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / 'tools'))
sys.path.insert(0, str(ROOT / 'tools/typing'))
import access_census  # noqa: E402


class SymbolAliases(unittest.TestCase):
    def test_five_column_rows_read_like_four_column_rows(self):
        with tempfile.TemporaryDirectory() as td:
            (Path(td) / 'config').mkdir()
            (Path(td) / 'config/names.tsv').write_text(
                '# h\n0x80016000\tfunc_80016000\tfirst\tev\ttown:0x100000\n0x80016100\tfunc_80016100\tsecond\tev\n')
            access_census.symbol_aliases.cache_clear()
            got = access_census.symbol_aliases(td)
        self.assertEqual(got, {'first': 'func_80016000', 'second': 'func_80016100'})


if __name__ == '__main__':
    unittest.main()
