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
        self.assertIn('All 1 module certificates are current.', text)
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


if __name__ == '__main__':
    unittest.main()
