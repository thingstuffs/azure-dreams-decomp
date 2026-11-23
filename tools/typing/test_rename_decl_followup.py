"""Tests for tools/typing/rename_decl_followup.py (fake trees; the compiler pass needs clang and is skipped without it)."""
import shutil
import sys
import tempfile
import unittest
from pathlib import Path

HERE = Path(__file__).resolve().parent
sys.path.insert(0, str(HERE))
import rename_decl_followup as F  # noqa: E402

TYPES = 'typedef int s32;\ntypedef unsigned char u8;\ntypedef struct Pos { int x; } Pos;\n'


class Tree(unittest.TestCase):
    def setUp(self):
        self._td = tempfile.TemporaryDirectory()
        self.root = Path(self._td.name)
        self.put('include/types.h', TYPES)

    def tearDown(self):
        self._td.cleanup()

    def put(self, rel, text):
        path = self.root / rel
        path.parent.mkdir(parents=True, exist_ok=True)
        path.write_text(text)

    def read(self, rel):
        return (self.root / rel).read_text()

    def run_followup(self, names, **kw):
        kw.setdefault('use_clang', False)
        edits, extra = F.run(self.root, names, log=lambda s: None, **kw)
        return edits


class Rewrites(Tree):
    def test_stale_declaration_takes_the_definitions_signature(self):
        self.put('include/stale.h', '#include "types.h"\nextern void spawn_thing(void *a, s32 b, void *c);\n')
        self.put('src/a.c', '#include "types.h"\nvoid spawn_thing(void *a, Pos *b, void *c) {\n}\n')
        edits = self.run_followup({'spawn_thing'})
        self.assertEqual([(e.status, e.klass) for e in edits], [('applied', 'neutral')])
        self.assertIn('extern void spawn_thing(void *a, Pos *b, void *c);', self.read('include/stale.h'))
        self.assertEqual(self.read('src/a.c').count('spawn_thing'), 1)            # the definition is not touched

    def test_a_void_stand_in_follows_the_record_pointer(self):
        self.put('include/stale.h', '#include "types.h"\nvoid spawn_thing(void *a);\n')
        self.put('src/a.c', '#include "types.h"\nvoid spawn_thing(Pos *a) {\n}\n')
        edits = self.run_followup({'spawn_thing'})
        self.assertEqual([e.status for e in edits], ['applied'])
        self.assertIn('void spawn_thing(Pos *a);', self.read('include/stale.h'))

    def test_empty_declaration_of_a_definition_with_parameters_stays_unprototyped(self):
        self.put('include/stale.h', 'void spawn_thing(void);\nint caller(void);\n')
        self.put('src/a.c', 'void spawn_thing(void *a, void *b) {\n}\n')
        edits = self.run_followup({'spawn_thing'})
        self.assertEqual([(e.status, e.klass) for e in edits], [('applied', 'neutral')])
        self.assertIn('void spawn_thing();', self.read('include/stale.h'))
        self.assertIn('int caller(void);', self.read('include/stale.h'))

    def test_width_changing_rewrite_is_held_unless_allowed(self):
        self.put('include/stale.h', '#include "types.h"\nvoid spawn_thing(u8 a);\n')
        self.put('src/a.c', '#include "types.h"\nvoid spawn_thing(s32 a) {\n}\n')
        before = self.read('include/stale.h')
        edits = self.run_followup({'spawn_thing'})
        self.assertEqual([(e.status, e.klass) for e in edits], [('held', 'width-risk')])
        self.assertEqual(before, self.read('include/stale.h'))
        edits = self.run_followup({'spawn_thing'}, allow_width=True)
        self.assertEqual([e.status for e in edits], ['applied'])
        self.assertIn('void spawn_thing(s32 a);', self.read('include/stale.h'))

    def test_block_scope_declaration_and_comments_inside_are_handled(self):
        self.put('src/b.c', '#include "types.h"\nvoid user(void) {\n    extern void spawn_thing(void *, s32);\n'
                 '    spawn_thing(0, 1);\n}\nextern void spawn_thing(void * /* a */, s32);\n')
        self.put('src/a.c', '#include "types.h"\nvoid spawn_thing(Pos *a, s32 b) {\n}\n')
        edits = self.run_followup({'spawn_thing'})
        by_line = {e.line: e for e in edits}
        self.assertEqual(by_line[3].status, 'applied')
        self.assertEqual(by_line[6].status, 'held')
        self.assertIn('a comment sits inside', by_line[6].reason)
        self.assertIn('    extern void spawn_thing(Pos *a, s32 b);', self.read('src/b.c'))
        self.assertIn('spawn_thing(0, 1);', self.read('src/b.c'))

    def test_dry_run_changes_nothing(self):
        self.put('include/stale.h', '#include "types.h"\nvoid spawn_thing(void *a);\n')
        self.put('src/a.c', '#include "types.h"\nvoid spawn_thing(Pos *a) {\n}\n')
        before = self.read('include/stale.h')
        edits, _ = F.run(self.root, {'spawn_thing'}, dry_run=True, log=lambda s: None)
        self.assertEqual(before, self.read('include/stale.h'))
        self.assertEqual([e.status for e in edits], ['planned'])

    def test_agreeing_declarations_are_not_touched(self):
        self.put('include/ok.h', '#include "types.h"\nvoid spawn_thing(Pos *a);\nvoid other();\n')
        self.put('src/a.c', '#include "types.h"\nvoid spawn_thing(Pos *a) {\n}\n')
        self.assertEqual(self.run_followup({'spawn_thing'}), [])


@unittest.skipUnless(shutil.which('clang'), 'clang not installed')
class CompilerPass(Tree):
    def test_a_rewrite_that_breaks_a_consumer_is_put_back_and_held(self):
        # declared `int *` against a definition that takes `long`: same register class, so the edit is
        # byte-neutral on paper, but the consumer passes a pointer and the compiler rejects the new prototype
        self.put('include/stale.h', 'extern int spawn_thing(int *p);\n')
        self.put('src/a.c', 'int spawn_thing(long x) {\n    return 0;\n}\n')
        self.put('src/user.c', '#include "stale.h"\nint v;\nint use(void) {\n    return spawn_thing(&v);\n}\n')
        before = self.read('include/stale.h')
        edits = self.run_followup({'spawn_thing'}, use_clang=True, explicit_tus=['src/user.c'])
        self.assertEqual([e.status for e in edits], ['held'])
        self.assertIn('compiler: new error', edits[0].reason)
        self.assertEqual(before, self.read('include/stale.h'))

    def test_a_rewrite_the_consumers_accept_is_kept(self):
        self.put('include/stale.h', '#include "types.h"\nextern void spawn_thing(void *a);\n')
        self.put('src/a.c', '#include "types.h"\nvoid spawn_thing(Pos *a) {\n}\n')
        self.put('src/user.c', '#include "stale.h"\nint v;\nvoid use(void) {\n    spawn_thing(&v);\n}\n')
        edits = self.run_followup({'spawn_thing'}, use_clang=True, explicit_tus=['src/user.c'])
        # passing int * where Pos * is expected is a warning (-w hides it), not an error: kept
        self.assertEqual([e.status for e in edits], ['applied'])
        self.assertIn('Pos *a', self.read('include/stale.h'))


if __name__ == '__main__':
    unittest.main()
