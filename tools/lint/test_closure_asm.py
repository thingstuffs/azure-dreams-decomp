"""Synthetic tests of tools/lint/closure_asm.py. No retail bytes, words or disassembly."""
import contextlib
import hashlib
import io
import json
import shutil
import subprocess
import tempfile
import unittest
from unittest import mock
from pathlib import Path

from tools.lint import closure_asm as A

LISTED = frozenset({'nop;nop;sync_a', 'nop;sync_b %0'})
BLOCKS = frozenset({'.include "include/labels.inc"\n', '.size table_a, 644'})
SECTIONS = frozenset({'.text.table_a'})


def kinds(text, templates=LISTED, blocks=BLOCKS, sections=SECTIONS):
    return [u['kind'] for u in A.classify(text, templates, blocks, sections)]


class ClassifyTest(unittest.TestCase):
    def test_rename_suffix_allowed(self):
        self.assertEqual(kinds('int f(int a) __asm__("func_80123456");\n'), ['rename'])
        self.assertEqual(kinds('extern int x __asm__("D_80012345");\n'), ['rename'])
        self.assertEqual(kinds('void g(void) { register int r __asm__("$5"); }\n'), ['rename'])

    def test_rename_with_directive_or_operands_refused(self):
        self.assertEqual(kinds('int f(int a) __asm__(".incbin \\"x\\"");\n'), ['refused-rename'])
        self.assertEqual(kinds('int f(void) __asm__("a" : "r"(b));\n'), ['refused-rename'])
        self.assertEqual(kinds('int f(void) __asm__("two words");\n'), ['refused-rename'])
        self.assertEqual(kinds('int f(void) __asm__ volatile ("name");\n'), ['refused-rename'])

    def test_file_scope_block_refused(self):
        text = 'int a;\n__asm__(".ent f\\n.incbin \\"x\\", 4, 8\\n.end f\\n");\nint b;\n'
        self.assertEqual(kinds(text), ['refused-block'])
        self.assertEqual(kinds('__asm__("nop");\n'), ['refused-block'])
        self.assertEqual(kinds('void f(void) {}\nasm("nop");\n'), ['refused-block'])
        # first token of the file, and after a closing brace
        self.assertEqual(kinds('asm(".word 1");\n'), ['refused-block'])

    def test_listed_block_is_exact(self):
        self.assertEqual(kinds('__asm__(".include \\"include/labels.inc\\"\\n");\n'), ['block-listed'])
        self.assertEqual(kinds('__asm__(".size table_a, 644");\n'), ['block-listed'])
        self.assertEqual(kinds('__asm__(".size table_a, 645");\n'), ['refused-block'])
        self.assertEqual(kinds('__asm__(".include \\"include/labels.inc\\"\\n" : : );\n'), ['refused-block'])

    def test_template_in_body(self):
        body = 'void f(int *p) {\n  __asm__ __volatile__("nop;nop;sync_a");\n}\n'
        self.assertEqual(kinds(body), ['template'])
        body = 'void f(int *p) {\n  if (p) asm volatile ("nop;sync_b %0" :: "r"(p) : "memory");\n}\n'
        self.assertEqual(kinds(body), ['template'])

    def test_template_not_listed_refused(self):
        body = 'void f(void) {\n  __asm__ volatile("nop;sync_c");\n}\n'
        self.assertEqual(kinds(body), ['refused-template'])

    def test_directive_in_template_refused(self):
        for text in ('.word 0x12345678', 'nop;.word 1', 'nop\n.incbin "x"', 'lab: .ent f', '.set noreorder;nop'):
            body = 'void f(void) {\n  __asm__ volatile("%s");\n}\n' % text.replace('"', '\\"').replace('\n', '\\n')
            self.assertEqual(kinds(body, templates=frozenset({text})), ['refused-directive'], text)

    def test_listing_never_admits_a_directive(self):
        body = 'void f(void) {\n  __asm__ volatile(".word 1");\n}\n'
        self.assertEqual(kinds(body, templates=frozenset({'.word 1'})), ['refused-directive'])

    def test_joined_string_literals(self):
        body = 'void f(void) {\n  __asm__ volatile("nop;nop;" "sync_a");\n}\n'
        self.assertEqual(kinds(body), ['template'])

    def test_text_in_strings_and_comment_free_names_ignored(self):
        self.assertEqual(kinds('const char *s = "asm(\\"x\\")";\nint asmx; int _asm_;\n'), [])
        self.assertEqual(kinds('void f(void) { const char *s = "{"; }\n__asm__(".size table_a, 644");\n'), ['block-listed'])

    def test_brace_depth_after_function(self):
        text = 'void f(void) {\n  int x;\n}\n__asm__("nop");\n'
        self.assertEqual(kinds(text), ['refused-block'])

    def test_section_attribute(self):
        self.assertEqual(kinds('int a[4] __attribute__((section(".text.table_a"))) = {1};\n'), [])
        self.assertEqual(kinds('int a[4] __attribute__((section(".text.table_b"))) = {1};\n'), ['refused-section'])
        self.assertEqual(kinds('int a[4] __attribute__((section(".text"))) = {1};\n'), ['refused-section'])
        self.assertEqual(kinds('extern int a __attribute__((section(".data")));\n'), [])
        self.assertEqual(kinds('extern int a __attribute__((section(".sdata")));\n'), [])
        self.assertEqual(kinds('int a __attribute__((__section__(".text.zzz")));\n'), ['refused-section'])
        self.assertEqual(kinds('int a __attribute__((aligned(8)));\n'), [])

    def test_file_and_line_from_markers(self):
        text = '# 1 "a.c"\nint a;\n# 40 "inc/h.h" 1\nint b;\n__asm__(".word 1");\n# 3 "a.c" 2\nint c;\n'
        use = A.classify(text)[0]
        self.assertEqual((use['file'], use['line']), ('inc/h.h', 41))

    def test_token_pasted_spelling_after_expansion(self):
        cc = shutil.which('cc') or shutil.which('gcc')
        if not cc:
            self.skipTest('no host preprocessor')
        source = '#define GLUE(a, b) a##b\nGLUE(__as, m__)(".word 1");\n'
        expanded = subprocess.run([cc, '-E', '-x', 'c', '-'], input=source, capture_output=True, text=True).stdout
        self.assertEqual(kinds(expanded), ['refused-block'])
        # the source text alone shows no keyword: that is the hole the expansion closes
        self.assertEqual(kinds(source), [])


class MemoTests(unittest.TestCase):
    """The per-unit memo: what its key binds, and that a refusal is never kept as a pass."""

    def setUp(self):
        self.tmp = tempfile.TemporaryDirectory()
        self.addCleanup(self.tmp.cleanup)
        self.root = Path(self.tmp.name)
        for d in ('include', 'src', 'config', 'build/.state'):
            (self.root / d).mkdir(parents=True, exist_ok=True)
        (self.root / 'include/labels.inc').write_text('labels\n')
        for name in ('a', 'b'):
            (self.root / ('src/%s.c' % name)).write_text('int %s;\n' % name)
        (self.root / 'include/h1.h').write_text('int h1;\n')
        (self.root / 'include/h2.h').write_text('int h2;\n')
        (self.root / A.TEMPLATES).write_text('template\t"nop"\n')
        self.log = self.root / 'calls.log'
        self.text = {'a': 'int a;\n', 'b': 'int b;\n'}
        self.plan = [self.unit('a', ['include/h1.h']), self.unit('b', ['include/h1.h', 'include/h2.h'])]
        outer = self
        def fake_units(root):
            return outer.plan
        def fake_preprocess(root, unit):
            with open(outer.log, 'a') as fh:
                fh.write(unit['name'] + '\n')
            return [outer.text[unit['name'][4]]]
        self.patches = [mock.patch.object(A, 'units', fake_units), mock.patch.object(A, 'preprocess', fake_preprocess)]
        for p in self.patches:
            p.start()
            self.addCleanup(p.stop)

    def unit(self, name, deps):
        return dict(route='overlay', name='src/%s.c' % name, version='2.7.2', flags=['-G0'], sources=['src/%s.c' % name],
                    include=str(self.root / 'include'), projection=None, deps=deps, extra=[])

    def run_check(self, **kw):
        kw.setdefault('jobs', 1)
        out = io.StringIO()
        with contextlib.redirect_stdout(out):
            code = A.run(self.root, **kw)
        return code, out.getvalue()

    def calls(self):
        return self.log.read_text().split() if self.log.exists() else []

    def key(self, unit, templates='x'):
        h = A.Hasher({})
        return A.memo_key(self.root, unit, h, 'tool', templates, {})

    def test_key_binds_source_every_dependency_and_the_tool_and_templates(self):
        a, b = self.plan
        base = (self.key(a), self.key(b))
        (self.root / 'include/h2.h').write_text('int h2 changed;\n')
        self.assertEqual(self.key(a), base[0])
        self.assertNotEqual(self.key(b), base[1])
        (self.root / 'include/h1.h').write_text('int h1 changed;\n')
        self.assertNotEqual(self.key(a), base[0])
        self.assertNotEqual(self.key(a), self.key(a, templates='other'))
        h = A.Hasher({})
        self.assertNotEqual(A.memo_key(self.root, a, h, 'tool', 'x', {}), A.memo_key(self.root, a, A.Hasher({}), 'tool2', 'x', {}))
        (self.root / 'src/a.c').write_text('int a2;\n')
        self.assertNotEqual(self.key(a), A.memo_key(self.root, a, A.Hasher({}), 'tool', 'x', {}) and 'x')

    def test_a_new_header_in_the_include_tree_or_the_source_directory_changes_the_key(self):
        a = self.plan[0]
        before = self.key(a)
        (self.root / 'include/new.h').write_text('shadow\n')
        self.assertNotEqual(self.key(a), before)
        before = self.key(a)
        (self.root / 'src/local.h').write_text('shadow\n')
        self.assertNotEqual(self.key(a), before)

    def test_unit_without_recipe_dependencies_has_no_key(self):
        u = self.unit('a', [])
        u['deps'] = None
        self.assertIsNone(self.key(u))

    def test_unchanged_units_are_not_preprocessed_again_and_a_header_edit_rechecks_its_includers(self):
        self.assertEqual(self.run_check()[0], 0)
        self.assertEqual(sorted(self.calls()), ['src/a.c', 'src/b.c'])
        self.run_check()
        self.assertEqual(len(self.calls()), 2)                      # nothing re-run
        (self.root / 'include/h2.h').write_text('int h2 again;\n')
        self.run_check()
        self.assertEqual(self.calls()[2:], ['src/b.c'])             # only the unit that includes h2
        (self.root / 'include/h1.h').write_text('int h1 again;\n')
        self.run_check()
        self.assertEqual(sorted(self.calls()[3:]), ['src/a.c', 'src/b.c'])

    def test_a_refusal_is_never_memoized_as_a_pass(self):
        self.text['a'] = '__asm__(".word 1");\n'
        code, out = self.run_check()
        self.assertEqual(code, 1)
        self.assertIn('refused', out)
        code, out = self.run_check()                                  # the same tree again: still refused, a was checked again
        self.assertEqual(code, 1)
        self.assertEqual(self.calls().count('src/a.c'), 2)
        self.assertEqual(self.calls().count('src/b.c'), 1)          # the passing unit was memoized
        memo = json.loads((self.root / A.MEMO).read_text())
        self.assertNotIn('overlay|src/a.c', memo['units'])
        self.assertIn('overlay|src/b.c', memo['units'])

    def test_changed_templates_or_no_memo_check_everything(self):
        self.run_check()
        (self.root / A.TEMPLATES).write_text('template\t"nop"\ntemplate\t"nop;nop"\n')
        self.run_check()
        self.assertEqual(len(self.calls()), 4)
        self.run_check(memo=False)
        self.assertEqual(len(self.calls()), 6)

    def test_no_memo_writes_nothing(self):
        self.run_check(memo=False)
        self.assertFalse((self.root / A.MEMO).exists())


class TemplatesFileTest(unittest.TestCase):
    def make_root(self, text, labels=b'labels\n'):
        root = Path(tempfile.mkdtemp())
        self.addCleanup(shutil.rmtree, root, True)
        (root / 'config').mkdir()
        (root / 'include').mkdir()
        (root / 'include/labels.inc').write_bytes(labels)
        (root / A.TEMPLATES).write_text(text)
        return root

    def row(self, digest):
        return 'block\t%s\tinclude/labels.inc\t%s\n' % (json.dumps('.include "include/labels.inc"\n'), digest)

    def test_hash_bound_block(self):
        digest = hashlib.sha256(b'labels\n').hexdigest()
        templates, blocks, sections, problems = A.load_templates(self.make_root(self.row(digest)))
        self.assertEqual((len(blocks), problems), (1, []))
        # the included file changed: the row no longer admits the line
        root = self.make_root(self.row(digest), labels=b'labels\n.incbin "x"\n')
        templates, blocks, sections, problems = A.load_templates(root)
        self.assertEqual(len(blocks), 0)
        self.assertEqual(len(problems), 1)

    def test_rows_and_unknown_kind(self):
        text = 'template\t"nop"\nsection\t".text.a"\nblock\t".size a, 4"\t-\t-\nbogus\t1\n'
        templates, blocks, sections, problems = A.load_templates(self.make_root(text))
        self.assertEqual((templates, blocks, sections), ({'nop'}, {'.size a, 4'}, {'.text.a'}))
        self.assertEqual(len(problems), 1)

    def test_missing_file_is_a_problem(self):
        root = Path(tempfile.mkdtemp())
        self.addCleanup(shutil.rmtree, root, True)
        self.assertTrue(A.load_templates(root)[3])


if __name__ == '__main__':
    unittest.main()
