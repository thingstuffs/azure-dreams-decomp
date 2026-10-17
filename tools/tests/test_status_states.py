"""STATUS.md module tables and the "At a glance" block: short state words, no exception text or paths, counts derived."""
import sys
import unittest
from pathlib import Path

TOOLS = Path(__file__).resolve().parents[1]
sys.path[:0] = [str(TOOLS), str(TOOLS / 'gate')]
import status as S

DENOM = dict(rows=10, bytes=1234, exact=10, exact_bytes=1234, unverified=0)
COV = dict(containers=['main', 'town'], c_pct=76.14, copy_pct=95.01, code_bytes=999)
LEVELS = {0: 100.0, 1: 100.0, 2: 100.0, 3: 99.1, 4: 0.0, 5: 0.0}


class CertState(unittest.TestCase):
    def test_reasons_map_to_states(self):
        cases = [
            (None, 'current'),
            ("certificate missing/invalid: FileNotFoundError: [Errno 2] No such file or directory: 'ledger/modules/overlay_town_ovl_2d3f0c.json'", 'missing'),
            ("certificate missing/invalid: FileNotFoundError: [Errno 2] No such file or directory: 'toolchain/compilers/gcc-2.7.2/cc1'", 'unchecked'),
            ("certificate missing/invalid: JSONDecodeError: Expecting value", 'attention'),
            ('source/recipe/graph/tool/review/window inputs changed', 'stale'),
            ('module sources, headers or manifest changed', 'stale'),
            ('verification inputs changed', 'stale'),
            ('certificate physical contributors or destination changed', 'stale'),
            ('module receipt changed or stale', 'stale'),
            ('reviewer differs', 'stale'),
            ('window does not equal retail', 'attention'),
            ('resolved module proof differs from retail', 'attention'),
            ('wrong certificate identity', 'attention'),
            ('manifest invalid: ValueError: x', 'attention'),
            ('some reason nobody has written yet', 'attention'),
        ]
        for reason, want in cases:
            self.assertEqual(S.cert_state(reason), want, reason)

    def test_every_state_has_a_word_and_a_meaning(self):
        for key, (word, meaning) in S.CERT_STATES.items():
            self.assertTrue(word and meaning, key)
            self.assertNotIn('/', word)

    def test_headers_are_names_without_the_universal_four(self):
        self.assertEqual(S._short_headers(['include/common.h', 'include/game.h', 'include/slus/x.h']), '`slus/x.h`')
        self.assertEqual(S._short_headers(['include/common.h']), '-')


class Rendering(unittest.TestCase):
    def render(self, ov, slus):
        return S.at_a_glance(DENOM, ['slus', 'main'], slus, ov, COV, 0, 0, 25918, LEVELS)

    def test_pending_certificates_are_counted_not_hard_coded(self):
        text = self.render({'stale': [('a', 2)] * 3, 'missing': [('b', 1)]}, {'missing': [('c', 1)] * 2})
        self.assertIn('0 of 6 current, 3 stale, 3 not certified yet', text)
        self.assertIn('6 of 6 module certificates are not current', text)
        self.assertIn('L4 and L5', text)

    def test_all_current_has_no_gap_paragraph(self):
        text = self.render({'current': [('a', 2)]}, {})
        self.assertIn('1 of 1 current', text)
        self.assertNotIn('Current proof state', text)   # shown only when something is not current
        self.assertNotIn('not current', text)

    def test_nothing_leaks_exception_text_or_paths(self):
        text = self.render({'attention': [('a', 1)]}, {})
        table = '\n'.join(S._state_table({'stale': [('a', 1)], 'attention': [('b', 1)]}))
        for out in (text, table):
            for bad in ('Errno', 'FileNotFoundError', 'Traceback', '/ho' + 'me/', "'ledger/"):
                self.assertNotIn(bad, out)

    def test_state_table_omits_empty_states_but_keeps_current(self):
        table = S._state_table({'stale': [('a', 2)]})
        self.assertEqual(len(table), 2 + 2)   # header + separator + current + stale
        self.assertIn('| current | 0 | 0 |', table[2])

    def test_details_block_has_blank_lines_for_markdown(self):
        block = S._details('s', ['| m |', '|---|'], ['| a |'])
        self.assertEqual(block[0], '')
        self.assertTrue(block[1].startswith('<details><summary>'))
        self.assertEqual(block[2], '')
        self.assertEqual(block[-2:], ['', '</details>'])


class NotYetC(unittest.TestCase):
    """Synthetic ledger: 1 C row, 1 proven copy, 1 raw split segment inside a window, 1 sdk region, 1 heuristic span; every byte once."""
    def setUp(self):
        import json, shutil, tempfile
        self.tmp = tempfile.TemporaryDirectory()
        self.addCleanup(self.tmp.cleanup)
        r = Path(self.tmp.name)
        (r / 'ledger/splits').mkdir(parents=True); (r / 'tools').mkdir(); (r / 'config/overlays').mkdir(parents=True)
        shutil.copy(TOOLS / 'coverage.py', r / 'tools/coverage.py')
        w = lambda name, recs: (r / 'ledger' / name).write_text(''.join(json.dumps(x) + '\n' for x in recs))
        w('containers.jsonl', [{'container': 'town', 'file': 'TOWN.BIN', 'bytes': 4096}, {'container': 'slus', 'file': 'S', 'bytes': 1}])
        w('rows.jsonl', [{'container': 'town', 'func': 'func_80010000', 'foff': 0, 'size': 64}])
        w('instances.jsonl', [{'container': 'town', 'foff': 64, 'size': 32, 'result': 'proven'}])
        w('coverage_regions.jsonl', [{'container': 'town', 'foff': 0, 'size': 4096, 'category': 'window'},
                                     {'container': 'town', 'foff': 128, 'size': 16, 'category': 'sdk_asm'},
                                     {'container': 'town', 'foff': 144, 'size': 8, 'category': 'estimated_code'},
                                     {'container': 'town', 'foff': 64, 'size': 32, 'category': 'estimated_code'}])
        w('splits/town.jsonl', [{'container': 'town', 'foff': 96, 'size': 32, 'result': 'M2C_FAIL'},
                                {'container': 'town', 'foff': 0, 'size': 64, 'result': 'MATCH'}])
        self.root = r

    def test_every_byte_is_in_one_class(self):
        res = S.not_yet_c(self.root)
        self.assertEqual(res, {'town': dict(in_c=64, copies=32, split=32, sdk=16, unported=0, heuristic=8)})   # the 32 B estimate under the copy is not counted twice

    def test_section_has_totals_and_slus_note(self):
        text = S.not_yet_c_section(self.root)
        self.assertIn('| `town` (TOWN overlays) | 152 | 64 | 42.1% | 32 | 32 | 16 | 0 | 8 | 72 |', text)
        self.assertIn('decision 55', text)
        self.assertIn('`slus` = SLUS_006.14 executable', text)
        self.assertIn('needs a SLUS build', text)   # no build_slus in the synthetic tree
        self.assertNotIn('/ho' + 'me/', text)


if __name__ == '__main__':
    unittest.main()
