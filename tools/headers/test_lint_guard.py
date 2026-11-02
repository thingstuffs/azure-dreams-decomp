"""lint_guard --restore: the restored TU's own declarations leave the header's append block."""
import subprocess
import sys
import tempfile
import unittest
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import lint_guard as G      # noqa: E402
from rewrite import APPEND_MARK  # noqa: E402

HEAD = '#ifndef H\n#define H\n\ns32 VSync(s32);\n\n#endif\n'


class RestoreTest(unittest.TestCase):
    def test_restore_trims_conflicting_appends(self):
        with tempfile.TemporaryDirectory() as d:
            root = Path(d)
            git = lambda *a: subprocess.run(['git', '-C', d, *a], check=True, capture_output=True)  # noqa: E731
            git('init', '-q')
            (root / 'include').mkdir()
            (root / 'src').mkdir()
            (root / 'include/a.h').write_text(HEAD)
            (root / 'include/b.h').write_text(HEAD)
            (root / 'src/x.c').write_text('#include "a.h"\nextern void erase(void *);\nvoid f(void) { erase(0); }\n')
            git('add', '-A')
            git('-c', 'user.email=t@t', '-c', 'user.name=t', 'commit', '-qm', 'base')
            base = subprocess.run(['git', '-C', d, 'rev-parse', 'HEAD'], capture_output=True, text=True).stdout.strip()
            (root / 'include/a.h').write_text(HEAD.replace('#endif', APPEND_MARK + '\ns32 TestEvent(s32);\ns32 erase(char *);\n\n#endif'))
            (root / 'include/b.h').write_text(HEAD.replace('#endif', APPEND_MARK + '\nvoid erase(char *);\n\n#endif'))
            (root / 'src/x.c').write_text('#include "a.h"\nvoid f(void) { erase(0); }\n')
            G.restore(root, base, ['src/x.c'])
            self.assertIn('extern void erase(void *);', (root / 'src/x.c').read_text())
            a = (root / 'include/a.h').read_text()
            self.assertIn('s32 TestEvent(s32);', a)
            self.assertNotIn('erase', a)
            self.assertEqual((root / 'include/b.h').read_text(), HEAD)


if __name__ == '__main__':
    unittest.main()
