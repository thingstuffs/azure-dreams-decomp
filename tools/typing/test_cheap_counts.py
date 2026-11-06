import unittest

from cheap_counts import local_typedefs


class CheapCountsTests(unittest.TestCase):
    def test_nested_callback_is_not_typedef_name(self):
        text = 'typedef struct { void (*handler)(void *); } Body;\nBody *x;\n'
        self.assertEqual(local_typedefs(text)[0]['name'], 'Body')
        self.assertEqual(local_typedefs(text)[0]['users'], 1)

    def test_function_pointer_alias(self):
        text = 'typedef void (*Callback)(void *);\n'
        self.assertEqual(local_typedefs(text)[0]['name'], 'Callback')
        self.assertEqual(local_typedefs(text)[0]['users'], 0)


if __name__ == '__main__':
    unittest.main()
