import hashlib
from pathlib import Path
import tempfile
import unittest

from tools.lint import retail_text


class TextLintTests(unittest.TestCase):
    def test_invented_literals_and_integer_encodings(self):
        source = r'''
#include "some-header.h"
const char *one = "Cloud " /* gap */ "soap";
const char *two = "\x6d\x69\x6e\x74";
const char three[] = {'m','i','n','t',0};
const u8 four[] = {0x6d, 0151, 110, 116, 0};
const u32 five[] = {0x746e696d, 0};
const u32 point[] = {0x00020001, 0, 7};
const char *short_fragment = "bps";
// "Comment example"
'''
        self.assertEqual([(kind, data.rstrip(b'\0')) for _, kind, data in retail_text.candidates(source)],
                         [('literal', b'Cloud soap'), ('literal', b'mint'),
                          ('integer array', b'mint'), ('integer array', b'mint'),
                          ('integer array', b'mint')])

    def test_nested_integer_initializer(self):
        source = "const unsigned char grid[2][2] = {{'{', 'a'}, {',', 'b'}};"
        self.assertEqual([(kind, data) for _,kind,data in retail_text.candidates(source)],
                         [('integer array', b'{a,b')])

    def test_word_array_with_encoded_fullwidth_text(self):
        data = 'Ｐｌｕｍ'.encode('shift_jis')
        words = [int.from_bytes(data[i:i+4], 'little') for i in range(0, len(data), 4)]
        source = 'const u32 example[] = {' + ', '.join(map(str, words)) + '};'
        self.assertEqual([payload for _, _, payload in retail_text.candidates(source)], [data])

    def test_aliases_records_and_described_quotes(self):
        source = '''
typedef unsigned char PixelCode;
typedef struct TestRecord {
    PixelCode a;
    PixelCode b;
} TestRecord;
const TestRecord items[] = {{'m','i'}, {'n','t'}};
const PixelCode symbols[] = {'p','l','u','m'};
/* The on-screen text says "Woven clocks". */
'''
        self.assertEqual(sorted((kind, data) for _, kind, data in retail_text.candidates(source)),
                         [('integer array', b'plum'), ('quoted display text', b'Woven clocks'),
                          ('record array', b'mint')])

    def test_document_encodings(self):
        cases = {
            '.json': ('{"kind":"typed_string","text":"Fern Quilt"}', b'Fern Quilt'),
            '.jsonl': ('{}\n{"encoded_bytes":[109,105,110,116]}', b'mint'),
            '.tsv': ('id\tencoded_text\n1\t6D 69 6E 74\n', b'mint'),
            '.md': ('The encoded message uses the bytes `6d 69 6e 74`.', b'mint'),
        }
        for suffix, (source, expected) in cases.items():
            with self.subTest(suffix=suffix):
                found = retail_text.document_candidates(Path('example' + suffix), source, strict=True)
                self.assertEqual([payload for _, _, payload in found], [expected])

    def test_allow_list_is_specific_and_does_not_echo_text(self):
        with tempfile.TemporaryDirectory() as temp:
            root = Path(temp)
            (root/'src').mkdir()
            (root/'config/lint').mkdir(parents=True)
            allow = root/'config/lint/retail_text.allow'
            path = root/'src/example.c'
            digest = hashlib.sha256(b'paper kite').hexdigest()
            allow.write_text(f'src/example.c\t{digest}\tInvented diagnostic\n')
            path.write_text('const char *value = "paper kite";\n')
            self.assertEqual(retail_text.check(root), [])
            path.write_text('const char *value = "green drum";\n')
            problems = retail_text.check(root)
            self.assertEqual(len(problems), 2)
            self.assertNotIn('green drum', '\n'.join(problems))
