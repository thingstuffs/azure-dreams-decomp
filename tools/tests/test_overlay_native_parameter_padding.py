"""Real object and adversarial checks for explicit five-u16 storage padding."""
import unittest
from tools.tests import test_overlay_native_extended_kinds as fixtures
N = fixtures.N

class ParameterPaddingTests(unittest.TestCase):
    def fixture(self):
        fixtures.ObjectTests.fixture(self, 'u16_parameter_record5', 2)
        self.explicit = self.asm.replace('.half 5120\n.align 2', '.half 5120\n.space 2\n.align 2')
        self.assertNotEqual(self.asm, self.explicit)

    def test_explicit_tail_keeps_complete_object_validation(self):
        self.fixture()
        N.validate_layout(self.m)
        N.validate_switch_assembly(self.m, self.explicit)
        N.validate_relocations(self.m, self.view)

    def test_arbitrary_duplicate_or_code_space_rejected(self):
        self.fixture()
        bad = [self.explicit.replace('.space 2', '.space 4'),
               self.explicit.replace('.space 2', '.space 2\n.space 2'),
               self.explicit.replace('entry0:\n', 'entry0:\n.space 2\n'),
               self.explicit.replace('func_test:\n', 'func_test:\n.rdata\n.space 2\n.text\n')]
        for assembly in bad:
            with self.subTest(assembly=assembly):
                with self.assertRaises(ValueError):N.validate_switch_assembly(self.m, assembly)
