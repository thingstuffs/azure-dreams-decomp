#!/usr/bin/env python3
"""Unit tests for floor_arity.py (pure interval and route logic)."""
from pathlib import Path
import sys
import unittest

sys.path.insert(0, str(Path(__file__).resolve().parent))
import floor_arity as F  # noqa: E402


def site(*kinds, stack=(), in_block=None):
    """A decoded call site; by default every register with a concrete definition was written in the block."""
    if in_block is None:
        in_block = [r for r, k in zip(F.ARG_REGS, kinds) if k not in ('stale', 'none', 'entry')]
    return dict(args=dict(zip(F.ARG_REGS, kinds)), stack_args=list(stack), set_in_block=in_block)


def call(nargs, lo, hi, positions='', sites=1, file='a.c', line=1, callback_contract=False):
    return dict(nargs=nargs, lo=lo, hi=hi, positions=positions, sites=sites,
                file=file, line=line, callback_contract=callback_contract)


class Interval(unittest.TestCase):
    def test_passthrough_extra_args_are_byte_compatible(self):
        lo, hi, _ = F.call_interval(4, [site('entry', 'entry', 'entry', 'entry')])
        self.assertEqual((lo, hi), (0, 4))

    def test_set_registers_keep_their_argument(self):
        lo, hi, _ = F.call_interval(3, [site('wide', 'const:0', 'u16', 'stale')])
        self.assertEqual((lo, hi), (3, 3))

    def test_register_set_beyond_the_c_arguments_is_not_attributed(self):
        lo, hi, _ = F.call_interval(2, [site('wide', 'wide', 'wide', 'wide')])
        self.assertEqual((lo, hi), (2, 2))

    def test_omitted_passthrough_extends_upper_bound(self):
        lo, hi, _ = F.call_interval(1, [site('wide', 'entry', 'stale', 'none')])
        self.assertEqual((lo, hi), (1, 2))

    def test_stack_argument(self):
        lo, hi, _ = F.call_interval(6, [site('wide', 'wide', 'wide', 'wide', stack=(0, 1))])
        self.assertEqual(lo, 6)

    def test_value_from_an_earlier_block_is_not_set_up(self):
        lo, hi, pos = F.call_interval(1, [site('entry|wide', 'stale', in_block=[])])
        self.assertEqual(lo, 0)
        self.assertEqual(pos[0], 'unknown')

    def test_any_site_setting_the_register_wins(self):
        lo, hi, _ = F.call_interval(2, [site('wide', 'entry'), site('wide', 'const:1')])
        self.assertEqual(lo, 2)


class Route(unittest.TestCase):
    def test_drop(self):
        self.assertEqual(F.route('f', 2, 2, [call(3, 1, 3, 'set,set,stale'),
                                               call(2, 2, 2, 'set,set')], {})[0], 'drop_phantom_args')

    def test_entry_forwarding_is_held_even_when_byte_compatible(self):
        r = F.route('f', 2, 2, [call(3, 1, 3, 'set,set,entry'),
                                call(2, 2, 2, 'set,set')], {})
        self.assertEqual((r[0], r[2]), ('hold_entry_forwarding', ''))

    def test_unknown_provenance_is_not_dropped(self):
        self.assertEqual(F.route('f', 2, 2, [call(3, 1, 3, 'set,set,unknown'),
                                               call(2, 2, 2, 'set,set')], {})[0], 'hold_unproven_arity')

    def test_extend(self):
        r = F.route('f', 3, 3, [call(4, 4, 4, 'set,set,set,set'),
                               call(4, 4, 4, 'set,set,set,set')], {})
        self.assertEqual(r[0], 'extend_definition')
        self.assertEqual(r[2], 4)

    def test_extend_requires_explicit_setup(self):
        self.assertEqual(F.route('f', 3, 3, [call(4, 3, 4, 'set,set,set,entry')], {})[0],
                         'hold_entry_forwarding')

    def test_mixed(self):
        self.assertEqual(F.route('f', 0, 0, [call(0, 0, 0), call(1, 1, 1)], {})[0], 'mixed_real_arity')

    def test_trim_needs_unused_parameters(self):
        self.assertEqual(F.route('f', 3, 2, [call(2, 1, 2), call(3, 1, 3)], {}, used=2)[0], 'hold_unproven_arity')
        self.assertEqual(F.route('f', 3, 2, [call(2, 1, 2), call(3, 1, 3)], {}, used=3)[0], 'mixed_real_arity')

    def test_decoder_over_read_is_capped(self):
        self.assertEqual(F.route('f', 0, 2, [call(2, 2, 2, 'set,set')], {})[0], 'extend_definition')

    def test_extend_and_drop(self):
        r = F.route('f', 0, 0, [call(2, 2, 2, 'set,set'), call(4, 2, 4, 'set,set,stale,none')], {})
        self.assertEqual((r[0], r[2]), ('hold_unproven_arity', ''))
        r = F.route('f', 0, 0, [call(2, 2, 2, 'set,set', callback_contract=True),
                               call(4, 2, 4, 'set,set,stale,none', callback_contract=True)], {})
        self.assertEqual((r[0], r[2]), ('extend_and_drop', 2))

    def test_passthrough_add(self):
        self.assertEqual(F.route('f', 1, 1, [call(0, 0, 1, 'entry', callback_contract=True),
                                               call(1, 1, 1, 'set', callback_contract=True)], {})[0],
                         'add_passthrough_args')

    def test_passthrough_without_contract_is_held(self):
        self.assertEqual(F.route('f', 1, 1, [call(0, 0, 1, 'entry'),
                                               call(1, 1, 1, 'set')], {})[0], 'hold_entry_forwarding')

    def test_unmatched_and_no_calls(self):
        self.assertEqual(F.route('f', 1, 1, [call(2, 2, 2, sites=0)], {})[0], 'unmatched')
        self.assertEqual(F.route('f', 1, 1, [], {})[0], 'no_direct_calls')


if __name__ == '__main__':
    unittest.main()
