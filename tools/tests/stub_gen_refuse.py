"""A generator that refuses every row, for tools/tests/test_gen_drive_flags.py.

gen_drive.py imports a generator as `xform.<name>` and falls back to `<name>`, so this module is
picked up with PYTHONPATH=tools/tests.  It is not a test module (unittest discovers `test_*.py`).
Refusing everything keeps the test free of compiles: gen_drive's todo list stays empty.
"""


class T:
    @staticmethod
    def eligible(text, row, census):
        return "stub: this generator refuses every row"

    @staticmethod
    def apply_verified(text, row, census, vf):        # never reached
        return None, {}
