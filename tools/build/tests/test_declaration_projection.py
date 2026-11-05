"""Semantic boundaries of the conservative C declaration projection."""
import shutil
import unittest

from tools.build import declaration_projection as D


@unittest.skipUnless(shutil.which('clang'), 'clang is unavailable')
class ProjectionTests(unittest.TestCase):
    def test_unused_prototype_extern_and_type_do_not_change_digest(self):
        base = b'int f(void) { return 7; }\n'
        extra = (b'extern int unused(void);\nextern int unused_value;\n'
                 b'typedef struct Idle { int field; } Idle;\n' + base)
        self.assertEqual(D.digest(base), D.digest(extra))
        self.assertTrue(D.digest(extra)[1])

    def test_transitive_references_are_retained(self):
        base = (b'typedef struct Needed { int field; } Needed;\n'
                b'extern Needed *get_needed(void);\n'
                b'int f(void) { return get_needed()->field; }\n')
        self.assertNotEqual(D.digest(base)[0], D.digest(base.replace(b'int field', b'long field'))[0])
        self.assertNotEqual(D.digest(base)[0], D.digest(base.replace(b'get_needed(void)', b'get_needed(int x)'))[0])

    def test_nested_enum_constant_keeps_containing_declaration(self):
        base = (b'struct X { enum { TOKEN = 1 } x; };\n'
                b'int f(void) { return TOKEN; }\n')
        self.assertEqual(D.project(base), base.strip())
        self.assertNotEqual(D.digest(base)[0], D.digest(base.replace(b'TOKEN = 1', b'TOKEN = 2'))[0])

    def test_definitions_and_static_declarations_stay(self):
        base = b'int f(void) { return 7; }\n'
        self.assertNotEqual(D.digest(base)[0], D.digest(b'int value;\n' + base)[0])
        self.assertNotEqual(D.digest(base)[0], D.digest(b'static int helper(void);\n' + base)[0])

    def test_annotated_unused_declaration_stays(self):
        base = b'int f(void) { return 7; }\n'
        annotated = b'extern int weak_value __attribute((weak));\n' + base
        self.assertNotEqual(D.digest(base)[0], D.digest(annotated)[0])

    def test_unparsed_text_falls_back_to_whole_input(self):
        text = b'#pragma pack(push, 1)\nextern int unused(void);\n'
        self.assertEqual(D.digest(text), (D.digest(text, clang='missing-clang')[0], False))
