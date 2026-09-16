"""Guard the pair discovery and prototype/unscored-arm boundaries (no compiler)."""
import sys
import unittest
from pathlib import Path
sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
from xform.t70_copywidth import candidates, pairs, T
from pin_census import sites_of


def narrow(text):
    return next(t for label,t in candidates(text) if label.endswith(':s16'))


class CopyWidths(unittest.TestCase):
    def test_bound_initializer_and_same_file_prototype(self):
        t = ('extern void f(s32 input);\nvoid f(s32 input) {\n'
             '    register s32 saved ASM_REG("$18") = input;\n'
             '    use((s16)saved);\n}\n')
        q = narrow(t)
        self.assertIn('extern void f(s16 input);', q)
        self.assertIn('void f(s16 input)', q)
        self.assertIn('s16 saved = input;', q)
        self.assertEqual(len(sites_of(q)), 0)

    def test_split_copy_and_shared_keep(self):
        t = ('void f(s32 input) {\n    s32 saved;\n    s32 other;\n'
             '    saved = input;\n    ASM_KEEP2(saved, other);\n'
             '    use((s16)saved, other);\n}\n')
        self.assertEqual(pairs(t), [('f','saved','input')])
        self.assertIn('s16 saved;', narrow(t))
        self.assertEqual(len(sites_of(narrow(t))), 0)

    def test_sweep_cannot_land_an_unreviewed_signature_change(self):
        t = ('void f(s32 input) {\n    s32 saved = input;\n'
             '    ASM_KEEP(saved);\n    use((s16)saved);\n}\n')
        def vf(candidate):
            self.assertIn('void f(s32 input)', candidate)
            return {'exact': False}
        result, info = T.apply_verified(t, {}, {}, vf)
        self.assertIsNone(result)
        self.assertGreater(info['requires_caller_review'], 0)

    def test_excludes_pointer_array_and_cast_copies(self):
        t = ('void f(void *input, s32 n) {\n'
             '    register void *saved ASM_REG("$18") = input;\n'
             '    register s32 values[2] ASM_REG("$19");\n'
             '    s32 count;\n    count = (s16)n;\n    ASM_KEEP(count);\n}\n')
        self.assertEqual(pairs(t), [])

    def test_never_edits_unscored_parameter_declaration(self):
        t = ('#ifdef NON_MATCHING\nvoid f(s32 input) {\n    s32 saved = input;\n'
             '    use(saved);\n}\n#else\nvoid f(s32 input) {\n'
             '    register s32 copy ASM_REG("$18") = input;\n'
             '    use((s16)copy);\n}\n#endif\n')
        self.assertEqual(candidates(t), [])

if __name__ == '__main__':
    unittest.main()
