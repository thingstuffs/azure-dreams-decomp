"""Focused coverage for the signed/unsigned 32-bit OR-zero rewrite."""
from pathlib import Path
import sys
import unittest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import orzero_aspsx as orzero


class OrZeroTypeTests(unittest.TestCase):
    def test_unsigned_declaration_and_or_use_are_rewritten(self):
        source = '''void f(void)
{
    register u32 zero ASM_REG("$0");
    sink(zero | 0x2F);
}
'''
        self.assertEqual(orzero.rewrite(source), '''void f(void)
{
    sink(0x2F);
}
''')

    def test_unsigned_statement_expression_is_rewritten(self):
        source = 'sink(({ register u32 z ASM_REG("$0"); ASM_KEEP(z); z | (47); }));\n'
        self.assertEqual(orzero.rewrite(source), 'sink(47);\n')

    def test_signed_declaration_remains_supported(self):
        source = '''register s32 zero ASM_REG("$0");
value = zero | 47;
'''
        self.assertEqual(orzero.rewrite(source), 'value = 47;\n')

    def test_variable_used_outside_or_refuses_the_whole_declaration_rewrite(self):
        source = '''register u32 zero ASM_REG("$0");
sink(zero | 47);
observe(zero);
'''
        self.assertEqual(orzero.rewrite(source), source)

    def test_scored_only_rewrite_preserves_unsigned_port_fallback(self):
        source = '''#ifndef NON_MATCHING
register u32 zero ASM_REG("$0");
#else
u32 zero = 0;
#endif
sink(zero | 47);
'''
        self.assertEqual(orzero.rewrite(source, scored_only=True), '''#ifndef NON_MATCHING
#else
u32 zero = 0;
#endif
sink(47);
''')

    def test_scored_only_does_not_rewrite_an_or_expression_in_the_port_arm(self):
        source = '''#ifndef NON_MATCHING
register u32 zero ASM_REG("$0");
sink(zero | 47);
#else
u32 zero = 0;
sink(zero | 99);
#endif
'''
        self.assertEqual(orzero.rewrite(source, scored_only=True), '''#ifndef NON_MATCHING
sink(47);
#else
u32 zero = 0;
sink(zero | 99);
#endif
''')

    def test_scored_only_does_not_rewrite_a_port_statement_expression(self):
        source = '''#ifdef NON_MATCHING
sink(({ register u32 zero ASM_REG("$0"); zero | (99); }));
#else
sink(47);
#endif
'''
        self.assertEqual(orzero.rewrite(source, scored_only=True), source)

    def test_full_rewrite_folds_consistent_unsigned_conditional(self):
        source = '''#ifdef NON_MATCHING
u32 zero = 0;
#else
register u32 zero ASM_REG("$0");
#endif
sink(zero | 47);
'''
        self.assertEqual(orzero.rewrite(source), 'sink(47);\n')

    def test_full_rewrite_folds_unsigned_define_fallback(self):
        source = '''#ifndef NON_MATCHING
register u32 zero ASM_REG("$0");
#else
#define zero 0
#endif
sink(zero | 47);
'''
        self.assertEqual(orzero.rewrite(source), 'sink(47);\n')

    def test_mismatched_conditional_types_are_not_folded(self):
        source = '''#ifdef NON_MATCHING
s32 zero = 0;
#else
register u32 zero ASM_REG("$0");
#endif
sink(zero | 47);
'''
        self.assertEqual(orzero.rewrite(source), source)

    def test_unsigned_ifndef_conditional_with_non_or_use_is_preserved(self):
        source = '''#ifndef NON_MATCHING
register u32 zero ASM_REG("$0");
#else
u32 zero = 0;
#endif
sink(zero | 47);
observe(zero);
'''
        self.assertEqual(orzero.rewrite(source), source)
        self.assertEqual(orzero.rewrite(source, scored_only=True), source)

    def test_signed_ifdef_conditional_with_non_or_use_is_preserved(self):
        source = '''#ifdef NON_MATCHING
s32 zero = 0;
#else
register s32 zero ASM_REG("$0");
#endif
sink(zero | 47);
observe(zero);
'''
        self.assertEqual(orzero.rewrite(source), source)
        self.assertEqual(orzero.rewrite(source, scored_only=True), source)


if __name__ == "__main__":
    unittest.main()
