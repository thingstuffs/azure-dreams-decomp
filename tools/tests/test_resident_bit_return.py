"""A real caller must receive the resident-bit helper's return in each native compiler."""
from pathlib import Path
import shutil
import subprocess
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[2]


class ResidentBitReturnTest(unittest.TestCase):
    def test_caller_observes_forwarded_result(self):
        scratch = ROOT / 'build' / 'test-tmp'
        scratch.mkdir(parents=True, exist_ok=True)
        for compiler, optimization in [('gcc', '-O0'), ('gcc', '-O2'), ('clang', '-O2')]:
            if not shutil.which(compiler):
                continue
            with self.subTest(compiler=compiler, optimization=optimization):
                with tempfile.TemporaryDirectory(dir=scratch) as directory:
                    folder = Path(directory)
                    caller = folder / 'caller.c'
                    caller.write_text('''#include "engine/runtime.h"
static int calls;
s32 test_resident_bitmap_bit(s32 value)
{
    calls++;
    return value ^ 0x13572468;
}
int main(void)
{
    if (test_resident_bit(0) != 0x13572468) return 1;
    if (test_resident_bit(0x7fff) != (0x7fff ^ 0x13572468)) return 2;
    if (test_resident_bit(-3) != (-3 ^ 0x13572468)) return 3;
    return calls == 3 ? 0 : 4;
}
''')
                    executable = folder / 'caller'
                    command = [compiler, '-m32', optimization, '-fwrapv', '-DM2CTX',
                               '-DNON_MATCHING', '-fno-pie', '-no-pie',
                               '-I', str(ROOT / 'include'), str(caller),
                               str(ROOT / 'src/engine/runtime/test_resident_bit.c'),
                               '-o', str(executable)]
                    result = subprocess.run(['nice', '-n', '10', *command],
                                            capture_output=True, text=True)
                    self.assertEqual(result.returncode, 0, result.stderr)
                    result = subprocess.run([str(executable)], capture_output=True, text=True)
                    self.assertEqual(result.returncode, 0, result.stderr)


if __name__ == '__main__':
    unittest.main()
