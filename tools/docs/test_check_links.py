"""Small synthetic repositories exercise the documented link-checking contract."""
import contextlib
import importlib.util
import io
from pathlib import Path
import sys
import tempfile
import unittest

spec = importlib.util.spec_from_file_location('docs_check_links', Path(__file__).with_name('check_links.py'))
checker = importlib.util.module_from_spec(spec)
sys.modules[spec.name] = checker
spec.loader.exec_module(checker)


class LinkTests(unittest.TestCase):
    def setUp(self):
        self.tmp = tempfile.TemporaryDirectory(dir=Path(__file__).resolve().parent)
        self.addCleanup(self.tmp.cleanup)
        self.root = Path(self.tmp.name)

    def write(self, name, text):
        path = self.root / name
        path.parent.mkdir(parents=True, exist_ok=True)
        path.write_text(text)
        return path

    def test_relative_encoded_directory_query_and_fragments(self):
        self.write('src/unit.c', 'int unit(void) {\n    return 1;\n}\n')
        self.write('docs/a b.md', '# Start `here`!\n\n## Start here!\n\n## Café\n')
        page = self.write('docs/index.md',
                          '[space](a%20b.md#start-here)\n[duplicate](<a b.md#start-here-1>)\n'
                          '[unicode](a%20b.md#caf%C3%A9)\n[source](../src/unit.c?plain=1#L1-L3)\n'
                          '[directory](../src/)\n[web](https://example.invalid/absent)\n')
        count, problems = checker.check(self.root, [page])
        self.assertEqual((count, problems), (5, []))

    def test_inline_reference_image_and_html_links(self):
        self.write('asset.txt', 'asset')
        page = self.write('README.md',
                          '[full][asset]\n[asset][]\n[asset]\n![pic](asset.txt "title")\n'
                          '<a href="asset.txt">asset</a>\n[asset]: asset.txt\n')
        self.assertEqual(checker.check(self.root, [page]), (6, []))

    def test_missing_targets_anchors_lines_and_reference(self):
        self.write('unit.c', 'void unit(void) {}\n')
        self.write('page.md', '# Existing\n')
        page = self.write('README.md', '[no](absent.c)\n[anchor](page.md#absent)\n'
                          '[line](unit.c#L2)\n[bad][undefined]\n')
        count, problems = checker.check(self.root, [page])
        self.assertEqual(count, 3)
        self.assertEqual({p.reason for p in problems},
                         {'missing target', 'missing anchor', 'source line out of range', 'undefined reference'})
        self.assertEqual({p.line for p in problems}, {1, 2, 3, 4})

    def test_code_comments_and_external_urls_are_ignored(self):
        page = self.write('README.md', '```md\n[bad](absent)\n```\n~~~\n[bad](absent)\n~~~\n'
                          '    [bad](absent)\n`[bad](absent)`\n<!-- [bad](absent) -->\n'
                          '[external](urn:example:resource)\n[web](//example.invalid/a)\n')
        self.assertEqual(checker.check(self.root, [page]), (0, []))

    def test_explicit_anchor_and_setext(self):
        page = self.write('README.md', 'Title\n=====\n\n<a id="custom"></a>\n'
                          '[title](#title)\n[custom](#custom)\n')
        self.assertEqual(checker.check(self.root, [page]), (2, []))

    def test_image_references_and_undefined_images(self):
        self.write('asset.txt', 'asset')
        page = self.write('README.md', '![image][asset]\n![missing][undefined]\n[asset]: asset.txt\n')
        count, problems = checker.check(self.root, [page])
        self.assertEqual(count, 2)
        self.assertEqual([(p.line, p.reason) for p in problems], [(2, 'undefined reference')])

    def test_escaping_paths_and_symlinks_fail(self):
        self.root.joinpath('escape').symlink_to(self.root.parent, target_is_directory=True)
        page = self.write('README.md', '[escape](../outside)\n[symlink](escape/)\n')
        self.assertEqual([p.reason for p in checker.check(self.root, [page])[1]],
                         ['target escapes repository', 'target escapes repository'])

    def test_parentheses_and_inline_code_label(self):
        self.write('a(b).md', '# Heading\n')
        page = self.write('README.md', '[`call()`](a(b).md#heading)\n')
        self.assertEqual(checker.check(self.root, [page]), (1, []))

    def test_cli_defaults_and_failure_exit(self):
        self.write('README.md', '[guide](docs/guide/README.md)\n')
        self.write('docs/README.md', '# Docs\n')
        self.write('docs/guide/README.md', '[bad](absent.md)\n')
        with contextlib.redirect_stdout(io.StringIO()) as output:
            result = checker.main(['--root', str(self.root)])
        self.assertEqual(result, 1)
        self.assertIn('3 Markdown files; 2 local links; 1 errors', output.getvalue())

    def test_oversized_inputs_fail_without_reading(self):
        page = self.write('README.md', 'x' * (checker.MAX_BYTES + 1))
        self.assertIn('over 4 MiB', checker.check(self.root, [page])[1][0].reason)


if __name__ == '__main__':
    unittest.main()
