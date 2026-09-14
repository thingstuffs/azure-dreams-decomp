"""A same-register pin family is one erasure unit, and only a family that verifies is kept."""
import os
import sys
import unittest
from pathlib import Path
from unittest.mock import patch
sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
from pin_census import sites_of, unscored_text
from xform.t62_regfamily import T, families, hard_register, reg_sites

FAMILY = ('s32 f(s32 n) {\n'
          ' register s32 first ASM_REG("$7"); /* MATCH: hold the product register. */\n'
          ' register s32 second ASM_REG("$a3");\n'
          ' register s32 other ASM_REG("$3");\n'
          ' first = n * 3;\n second = n * 5;\n other = first + second;\n'
          ' return other; /* Useful explanation. */\n}\n')

PORTED = ('s32 f(s32 n) {\n'
          '#ifdef NON_MATCHING\n'
          ' register s32 ported ASM_REG("$8");\n'
          ' ported = n;\n'
          '#else\n'
          ' register s32 a ASM_REG("$4");\n'
          ' register s32 b ASM_REG("$4");\n'
          ' a = n; b = n + 1;\n'
          '#endif\n'
          ' return n;\n}\n')

ROW = {"id": "dungeon/test", "cfg": "2.7.2"}


class Stub:
    """A byte verifier standing in for vf: exact when the candidate text satisfies `pred`."""
    def __init__(self, pred):
        self.pred, self.calls, self.texts = pred, 0, []

    def __call__(self, text):
        self.calls += 1
        self.texts.append(text)
        return {"exact": bool(self.pred(text)), "status": "ok"}


def freed(reg, held=None):
    """Exact once no pin names `reg`, and only while a pin still names `held` (the sibling on
    another register that this stub refuses to release)."""
    def pred(text):
        return 'ASM_REG("%s")' % reg not in text and (held is None or 'ASM_REG("%s")' % held in text)
    return pred


class FamilyTests(unittest.TestCase):
    def test_register_spellings_normalise_to_one_family(self):
        self.assertEqual(hard_register('$a3'), hard_register('7'))
        self.assertEqual(hard_register('$s0'), 16)
        self.assertEqual(hard_register('"$ra"'), 31)
        self.assertEqual(hard_register('$weird'), 'weird')      # kept, never merged with a number

    def test_families_group_by_register_largest_first(self):
        text = ('void f(void) {\n register s32 a ASM_REG("$16");\n register s32 b ASM_REG("$s0");\n'
                ' register s32 c ASM_REG("$7");\n register s32 d ASM_REG("$a3");\n'
                ' register s32 e ASM_REG("$a3");\n register s32 lone ASM_REG("$2");\n}\n')
        got = [(k, [s[6].split()[-1] for s in g]) for k, g in families(text)]
        self.assertEqual(got, [(7, ['c', 'd', 'e']), (16, ['a', 'b']), (2, ['lone'])])
        self.assertEqual(T.eligible(text, ROW, {}), None)

    def test_a_lone_register_is_not_eligible(self):
        text = 'void f(void) {\n register s32 a ASM_REG("$16");\n register s32 b ASM_REG("$7");\n}\n'
        self.assertEqual([len(g) for _, g in families(text)], [1, 1])
        self.assertEqual(T.eligible(text, ROW, {}), 'no same-register pin family')
        self.assertEqual(T.eligible(FAMILY, {}, {}), 'missing compiler recipe')

    def test_the_family_falls_together_and_rewrites_its_declarations(self):
        vf = Stub(freed('$7', held='$3'))
        new, info = T.apply_verified(FAMILY, ROW, {}, vf)
        self.assertIsNotNone(new)
        self.assertIn(' s32 first;\n', new)                     # register + ASM_REG gone, type kept
        self.assertIn(' s32 second;\n', new)
        self.assertNotIn('ASM_REG("$7")', new)
        self.assertNotIn('ASM_REG("$a3")', new)
        self.assertNotIn('MATCH:', new)                         # the erased pin's own note went too
        self.assertIn('Useful explanation', new)
        self.assertIn('register s32 other ASM_REG("$3")', new)  # the sibling that did not verify
        self.assertEqual(len(sites_of(new)), 1)
        self.assertEqual([r['exact'] for r in info['families']], [True])
        self.assertEqual(info['families'][0]['n'], 2)
        self.assertEqual(info['families'][0]['vars'], ['first', 'second'])
        self.assertEqual(info['families'][0]['reg'], '$7')
        self.assertEqual((info['pins_in'], info['pins_out'], info['pins_removed']), (3, 1, 2))
        self.assertEqual(info['singles_fallen'], 0)
        self.assertEqual([r['var'] for r in info['singles']], ['other'])

    def test_members_are_never_erased_one_at_a_time(self):
        """Every family candidate erases the whole group; no single-member text is ever scored."""
        vf = Stub(freed('$7', held='$3'))
        T.apply_verified(FAMILY, ROW, {}, vf)
        for text in vf.texts:
            self.assertNotEqual(text.count('ASM_REG("$7")') + text.count('ASM_REG("$a3")'), 1)

    def test_singles_run_only_after_a_family_falls(self):
        vf = Stub(lambda text: False)                           # nothing verifies
        new, info = T.apply_verified(FAMILY, ROW, {}, vf)
        self.assertIsNone(new)
        self.assertEqual(info['singles'], [])
        self.assertEqual(vf.calls, 1)                           # the one family, and nothing else

    def test_verify_budget_caps_the_calls(self):
        text = FAMILY.replace('register s32 other ASM_REG("$3");',
                              'register s32 other ASM_REG("$3");\n register s32 more ASM_REG("$2");'
                              '\n register s32 last ASM_REG("$5");')
        with patch.dict(os.environ, {"T62_VERIFY": "2"}):
            vf = Stub(freed('$7'))
            new, info = T.apply_verified(text, ROW, {}, vf)
        self.assertEqual(vf.calls, 2)
        self.assertEqual(info['tried'], 2)
        self.assertIsNotNone(new)
        self.assertEqual(info['families_fallen'], 1)

    def test_a_port_arm_pin_is_neither_a_site_nor_edited(self):
        vf = Stub(freed('$4'))
        self.assertEqual([s[2] for s in reg_sites(PORTED)], ['4', '4'])
        new, info = T.apply_verified(PORTED, ROW, {}, vf)
        self.assertIsNotNone(new)
        self.assertEqual(unscored_text(new), unscored_text(PORTED))
        self.assertIn('register s32 ported ASM_REG("$8");', new)
        self.assertEqual(info['pins_out'], 0)


if __name__ == '__main__':
    unittest.main()
