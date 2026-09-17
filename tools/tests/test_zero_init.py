"""Guard and frozen-winner coverage for xform.zero_init."""
from pathlib import Path
import hashlib
import json
import sys
import unittest


TOOLS = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(TOOLS))
from xform import zero_init


class ZeroInitGuardTests(unittest.TestCase):
    def candidate(self, source):
        candidates = zero_init.zero_init_candidates(source)
        self.assertEqual(len(candidates), 1)
        return candidates[0][1]

    def test_direct_zero_names_are_initialized_in_one_candidate(self):
        source = '''void f(void)
{
    register s32 first ASM_REG("$0"); /* keep this comment */
#ifdef NON_MATCHING
    first = 0;
#endif
    consume = first;
    {
        register s32 second ASM_REG("$zero");
        consume += second;
    }
}
'''
        expected = '''void f(void)
{
    s32 first = 0; /* keep this comment */
#ifdef NON_MATCHING
    first = 0;
#endif
    consume = first;
    {
        s32 second = 0;
        consume += second;
    }
}
'''
        self.assertEqual(self.candidate(source), expected)

    def test_exact_zero_assignment_is_allowed(self):
        source = '''s32 f(void)
{
    register s32 zero ASM_REG("$0");
    zero = 0;
    return zero;
}
'''
        self.assertIn("s32 zero = 0;", self.candidate(source))

    def test_direct_declaration_may_share_a_line_with_the_function_body(self):
        source = 's32 f(void) { register s32 z ASM_REG("$0"); return z; }\n'
        expected = 's32 f(void) { s32 z = 0; return z; }\n'
        self.assertEqual(self.candidate(source), expected)

    def test_initializer_or_wrong_type_is_not_admitted(self):
        sources = (
            's32 f(void) { register s32 z ASM_REG("$0") = 0; return z; }\n',
            's32 f(void) { register u32 z ASM_REG("$0"); return z; }\n',
        )
        for source in sources:
            with self.subTest(source=source):
                self.assertEqual(zero_init.zero_init_candidates(source), [])

    def test_nonzero_unknown_compound_and_increment_writes_are_refused(self):
        statements = ("z = 1;", "z = value;", "z += 0;", "z <<= 1;", "z++;", "--z;")
        for statement in statements:
            with self.subTest(statement=statement):
                source = f'''s32 f(void)
{{
    register s32 z ASM_REG("$0");
    {statement}
    return z;
}}
'''
                self.assertEqual(zero_init.zero_init_candidates(source), [])

    def test_address_escape_is_refused(self):
        for expression in ("&z", "&(z)", "& ( ( ( ( z ) ) ) )"):
            with self.subTest(expression=expression):
                source = f'''s32 f(void)
{{
    register s32 z ASM_REG("$0");
    sink({expression});
    return z;
}}
'''
                self.assertEqual(zero_init.zero_init_candidates(source), [])

    def test_parenthesized_lvalue_assignment_is_refused(self):
        statements = ("(z) = 0;", "(z) = 7;", "++(z);", "--((z));", "(z)++;")
        for statement in statements:
            with self.subTest(statement=statement):
                source = f'''s32 f(void)
{{
    register s32 z ASM_REG("$0");
    {statement}
    return z;
}}
'''
                self.assertEqual(zero_init.zero_init_candidates(source), [])

    def test_macro_and_asm_outputs_are_refused(self):
        uses = (
            "ASM_SET(z);",
            "READ_ZERO(z);",
            "UNKNOWN_MACRO(z);",
            '__asm__("" : "=r"(z));',
        )
        for use in uses:
            with self.subTest(use=use):
                source = f'''s32 f(void)
{{
    register s32 z ASM_REG("$0");
    {use}
    return z;
}}
'''
                self.assertEqual(zero_init.zero_init_candidates(source), [])

    def test_lowercase_locally_defined_macro_touching_value_is_refused(self):
        source = '''#define set_output(x) ((x) = 0)
s32 f(void)
{
    register s32 z ASM_REG("$0");
    set_output(z);
    return z;
}
'''
        self.assertEqual(zero_init.zero_init_candidates(source), [])

    def test_unknown_lowercase_call_argument_is_refused(self):
        source = '''s32 f(void)
{
    register s32 z ASM_REG("$0");
    mutate_from_included_header(z);
    return z;
}
'''
        self.assertEqual(zero_init.zero_init_candidates(source), [])

    def test_language_keyword_parentheses_are_reads(self):
        source = '''s32 f(void)
{
    register s32 z ASM_REG("$0");
    if (z) {
        return sizeof(z);
    }
    return z;
}
'''
        self.assertEqual(len(zero_init.zero_init_candidates(source)), 1)

    def test_variable_name_defined_as_macro_is_refused(self):
        source = '''#define z 0
s32 f(void)
{
    register s32 z ASM_REG("$0");
    return z;
}
'''
        self.assertEqual(zero_init.zero_init_candidates(source), [])

    def test_comments_and_strings_do_not_create_uses_or_sites(self):
        source = '''s32 f(void)
{
    register s32 z ASM_REG("$0");
    /* z = 9; ASM_SET(z); register s32 fake ASM_REG("$0"); */
    note("z++; READ_ZERO(z); register s32 fake ASM_REG(\\"$zero\\");");
    return z;
}
'''
        candidate = self.candidate(source)
        self.assertIn("s32 z = 0;", candidate)
        self.assertIn("z = 9; ASM_SET(z)", candidate)

        mentions_only = '''void f(void)
{
    /* register s32 z ASM_REG("$0"); */
    note("register s32 z ASM_REG(\\"$zero\\");");
}
'''
        self.assertEqual(zero_init.zero_init_candidates(mentions_only), [])

    def test_macro_definition_site_is_refused(self):
        source = '''#define DECL_ZERO() \\
    register s32 z ASM_REG("$0");
s32 f(void)
{
    DECL_ZERO();
    return z;
}
'''
        self.assertEqual(zero_init.zero_init_candidates(source), [])

    def test_live_site_inside_port_arm_is_refused(self):
        source = '''s32 f(void)
{
#ifdef NON_MATCHING
    register s32 z ASM_REG("$0");
    return z;
#else
    return 0;
#endif
}
'''
        self.assertEqual(zero_init.zero_init_candidates(source), [])

    def test_ambiguous_shadow_in_same_scope_is_refused(self):
        source = '''s32 f(s32 cond)
{
    register s32 z ASM_REG("$0");
    if (cond) {
        s32 z = 1;
        sink(z);
    }
    return z;
}
'''
        self.assertEqual(zero_init.zero_init_candidates(source), [])

    def test_unknown_typedef_shadow_is_refused(self):
        source = '''s32 f(s32 cond)
{
    register s32 z ASM_REG("$0");
    if (cond) {
        mystery_type z = 1;
        sink(z);
    }
    return z;
}
'''
        self.assertEqual(zero_init.zero_init_candidates(source), [])

    def test_later_identifier_label_is_refused(self):
        source = '''s32 f(void)
{
    goto done;
    register s32 z ASM_REG("$0");
    if (z) done: return z;
    return 0;
}
'''
        self.assertEqual(zero_init.zero_init_candidates(source), [])

    def test_post_initializer_goto_in_same_scope_is_allowed(self):
        source = '''s32 f(s32 again)
{
    register s32 z ASM_REG("$0");
loop:
    if (again) {
        again = 0;
        goto loop;
    }
    return z;
}
'''
        self.assertEqual(len(zero_init.zero_init_candidates(source)), 1)

    def test_case_prefixed_ordinary_label_is_not_a_switch_label(self):
        source = '''s32 f(s32 again)
{
    register s32 z ASM_REG("$0");
case_named:
    if (again) {
        again = 0;
        goto case_named;
    }
    return z;
}
'''
        self.assertEqual(len(zero_init.zero_init_candidates(source)), 1)

    def test_goto_from_outside_initializer_scope_is_refused(self):
        source = '''s32 f(s32 enter)
{
    if (enter) {
        goto done;
    }
    {
        register s32 z ASM_REG("$0");
done:
        return z;
    }
}
'''
        self.assertEqual(zero_init.zero_init_candidates(source), [])

    def test_nested_switch_after_initializer_is_conservatively_refused(self):
        source = '''s32 f(s32 selector)
{
    register s32 z ASM_REG("$0");
    switch (selector) {
    case 1:
        return z;
    default:
        return 0;
    }
}
'''
        self.assertEqual(zero_init.zero_init_candidates(source), [])

    def test_nested_compound_case_can_bypass_initializer(self):
        source = '''s32 f(s32 selector)
{
    switch (selector) {
        register s32 z ASM_REG("$0");
        {
        case 1:
            return z;
        }
    }
    return 0;
}
'''
        self.assertEqual(zero_init.zero_init_candidates(source), [])

    def test_multiline_case_can_bypass_initializer(self):
        source = '''s32 f(s32 selector)
{
    switch (selector) {
        register s32 z ASM_REG("$0");
    case
        1:
        return z;
    }
    return 0;
}
'''
        self.assertEqual(zero_init.zero_init_candidates(source), [])

    def test_later_switch_case_is_refused(self):
        source = '''s32 f(s32 selector)
{
    switch (selector) {
        register s32 z ASM_REG("$0");
    case 1:
        return z;
    default:
        return 0;
    }
}
'''
        self.assertEqual(zero_init.zero_init_candidates(source), [])

    def test_sweep_plugin_submits_only_guarded_candidate(self):
        source = '''s32 f(void)
{
    register s32 z ASM_REG("$0");
    return z;
}
'''
        seen = []

        def exact(candidate):
            seen.append(candidate)
            return {"exact": True, "total": 0}

        self.assertIsNone(zero_init.T.eligible(source, {}, {}))
        candidate, info = zero_init.T.apply_verified(source, {}, {}, exact)
        self.assertEqual(candidate, self.candidate(source))
        self.assertEqual(seen, [candidate])
        self.assertEqual(info["sites"], 1)


class FrozenWinnerTests(unittest.TestCase):
    def test_all_nine_reviewed_winners_reproduce(self):
        fixture_dir = TOOLS / "fixtures" / "zero_init"
        manifest = json.loads((fixture_dir / "manifest.json").read_text())
        self.assertEqual(len(manifest["rows"]), 9)
        for row in manifest["rows"]:
            with self.subTest(row=row["row"]):
                source = (fixture_dir / row["fixture"]).read_text()
                self.assertEqual(hashlib.sha256(source.encode()).hexdigest(),
                                 row["baseline_sha256"])
                candidates = zero_init.zero_init_candidates(source)
                self.assertEqual(len(candidates), 1)
                label, candidate = candidates[0]
                self.assertEqual(label.count("@"), row["bindings"])
                self.assertEqual(hashlib.sha256(candidate.encode()).hexdigest(),
                                 row["candidate_sha256"])


if __name__ == "__main__":
    unittest.main()
