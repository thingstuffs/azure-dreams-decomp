"""sign_trial: the opposite-sign compile trial and the per-cast removal trial, with a stand-in compiler.

    python3 -m unittest tools.typing.test_sign_trial
"""
from pathlib import Path
import re
import sys
import tempfile
import unittest

HERE = Path(__file__).resolve().parent
sys.path.insert(0, str(HERE))
import sign_trial as T  # noqa: E402

HEADER = '''typedef struct Rec {
    int pad;
    u16 timer;   /* the field under trial */
    u16 other;
} Rec;
'''


def fake_compile(root):
    """Stand-in 'compiler': a function's code is a lh when its field read is signed (field declared s16
    or a (s16) cast is present) and an lhu otherwise; a compare of the field always needs the sign."""
    def compile_tus(tus):
        out = {}
        header = (Path(root) / 'include/rec.h').read_text()
        declared = 's16' if re.search(r's16\s+timer;', header) else 'u16'
        for tu in tus:
            text = (Path(root) / tu).read_text()
            funcs = {}
            for m in re.finditer(r'(\w+)\(Rec \*r\)\s*\{(.*?)\n\}', text, re.S):
                lines = []
                for stmt in m[2].split(';'):
                    if 'timer' not in stmt:
                        continue
                    cast = '(s16)' in stmt
                    signed = declared == 's16' or cast
                    if '<' in stmt:                       # a compare needs a signed load whatever the declaration
                        lines.append('lh' if signed else 'lhu')
                    else:                                 # a copy is sign-neutral
                        lines.append('lhu')
                funcs[m[1]] = lines
            out[tu] = funcs
        return out
    return compile_tus


class Base(unittest.TestCase):
    def setUp(self):
        self.tmp = tempfile.TemporaryDirectory()
        self.addCleanup(self.tmp.cleanup)
        self.root = Path(self.tmp.name)
        (self.root / 'include').mkdir()
        (self.root / 'src').mkdir()
        (self.root / 'include/rec.h').write_text(HEADER)

    def source(self, name, text):
        (self.root / 'src' / name).write_text('#include "rec.h"\n' + text)
        return 'src/' + name


TWO = '''typedef struct Inner { u16 timer; } Inner;
typedef struct Rec {
    int pad;
    u16 timer;
    Inner inner;
    struct Rec *next;
} Rec;
typedef struct Other { int pad; u16 timer; } Other;
'''


def two_record_compile(root):
    """Code of a function: its statements on Rec.timer follow Rec's declared sign (or a cast); statements on
    any other record's timer are a fixed opaque marker plus whether a (s16) cast sits on them."""
    def compile_tus(tus):
        out = {}
        header = (Path(root) / 'include/rec.h').read_text()
        rec = header.split('} Rec;')[0]
        declared = 's16' if re.search(r's16\s+timer;', rec) else 'u16'
        for tu in tus:
            text = (Path(root) / tu).read_text()
            funcs = {}
            for m in re.finditer(r'(\w+)\([^)]*\)\s*\{(.*?)\n\}', text, re.S):
                lines = []
                for stmt in m[2].split(';'):
                    if 'timer' not in stmt:
                        continue
                    if re.search(r'\bo->timer|\bi->timer', stmt):
                        lines.append('other' + (' cast' if '(s16)' in stmt else ''))
                    else:
                        lines.append('lh' if (declared == 's16' or '(s16)' in stmt) and '<' in stmt else 'lhu')
                funcs[m[1]] = lines
            out[tu] = funcs
        return out
    return compile_tus


class TypeResolutionTests(Base):
    def setUp(self):
        super().setUp()
        (self.root / 'include/rec.h').write_text(TWO)
        self.index = T.TypeIndex(self.root)

    def kind(self, text, base, field='timer', owner='Rec'):
        offset = text.index(base + '->' + field) if base + '->' + field in text else text.index(base)
        return self.index.resolver(owner)(text, offset, base)

    def test_locals_params_globals_chains_and_casts(self):
        text = ('static Other *gother;\nRec *grec;\n'
                'void f(Rec *r, Other *o, void *v)\n{\n    Rec *l;\n    x = r->timer + o->timer + l->timer;\n'
                '    y = l->next->timer + r->inner.timer + gother->timer + grec->timer;\n'
                '    z = ((Rec *)v)->timer + ((Other *)v)->timer + w->timer;\n}\n')
        self.assertEqual(self.kind(text, 'r'), 'match')
        self.assertEqual(self.kind(text, 'o'), 'other')
        self.assertEqual(self.kind(text, 'l'), 'match')
        self.assertEqual(self.kind(text, 'l->next'), 'match')
        self.assertEqual(self.kind(text, 'r->inner'), 'other')          # Inner.timer is another record's member
        self.assertEqual(self.kind(text, 'gother'), 'other')
        self.assertEqual(self.kind(text, 'grec'), 'match')
        self.assertEqual(self.kind(text, '((Rec *)v)'), 'match')
        self.assertEqual(self.kind(text, '((Other *)v)'), 'other')
        self.assertEqual(self.kind(text, 'w'), 'unresolved')           # undeclared: skipped, not stripped

    def test_bare_local_named_like_the_field_is_not_a_member_cast(self):
        self.assertEqual(T.field_casts('x = (s16)timer; y = (s16)r->timer;', T.SPELLINGS['s16'], 'timer'),
                         [(20, 5, 'r', 'match')])

    def test_tag_and_typedef_names_are_one_record(self):
        self.index.add('typedef struct RecTag { int a; u16 timer; } RecAlias;\n', 'x.h')
        self.assertTrue(self.index.same('RecTag', 'RecAlias'))
        self.assertFalse(self.index.same('Rec', 'RecAlias'))

    def test_base_before_walks_primaries(self):
        text = 'v = (s16)a->b[i + 1].timer;'
        pos = text.index('.timer')
        self.assertEqual(text[T.base_before(text, pos):pos], 'a->b[i + 1]')
        text = 'v = ((Rec *)p)->timer;'
        pos = text.index('->timer')
        self.assertEqual(text[T.base_before(text, pos):pos], '((Rec *)p)')


class TwoRecordTrialTests(Base):
    def setUp(self):
        super().setUp()
        (self.root / 'include/rec.h').write_text(TWO)

    def test_only_the_named_records_casts_are_stripped(self):
        self.source('a.c', 'void f(Rec *r)\n{\n    if ((s16)r->timer < 0) g();\n}\n'
                           'void h(Other *o)\n{\n    x = (s16)o->timer;\n}\n')
        self.source('b.c', 'void k(Other *o)\n{\n    y = (s16)o->timer;\n}\n')
        result = T.trial(self.root, 'include/rec.h::Rec.timer', two_record_compile(self.root))
        self.assertEqual(result['tus'], ['src/a.c'])                     # b.c never touches Rec.timer
        self.assertEqual((result['casts_now'], result['differing']), (1, 0))
        self.assertEqual(result['recommendation'], 'FLIP_CLEAN')
        self.assertEqual(result['unresolved'], [])
        self.assertIn('(s16)o->timer', (self.root / 'src/a.c').read_text())

    def test_unresolved_sites_are_reported_and_not_stripped(self):
        self.source('a.c', 'void f(Rec *r)\n{\n    if ((s16)r->timer < 0) g();\n    x = (s16)mystery->timer;\n}\n')
        result = T.trial(self.root, 'include/rec.h::Rec.timer', two_record_compile(self.root))
        self.assertEqual(result['casts_now'], 1)
        self.assertEqual([(u['file'], u['base']) for u in result['unresolved']], [('src/a.c', 'mystery')])
        self.assertIn('unresolved base types', T.format_trial(result))

    def test_check_removal_ignores_other_records_casts(self):
        self.source('a.c', 'void f(Rec *r)\n{\n    if ((s16)r->timer < 0) g();\n}\n'
                           'void h(Other *o)\n{\n    x = (s16)o->timer;\n}\n')
        result = T.check_removal(self.root, 'include/rec.h::Rec.timer', two_record_compile(self.root))
        self.assertEqual([(r['line'], r['verdict']) for r in result['casts']], [(4, 'NEEDED')])


class DeclarationTests(unittest.TestCase):
    def test_spec_and_declaration(self):
        self.assertEqual(T.parse_spec('include/x.h::Rec.timer'), ('include/x.h', 'Rec', 'timer'))
        with self.assertRaises(ValueError):
            T.parse_spec('timer')
        start, declared = T.field_declaration(HEADER, 'Rec', 'timer')
        self.assertEqual(declared, 'u16')
        flipped, _ = T.flip_declaration(HEADER, 'Rec', 'timer')
        self.assertIn('s16 timer;', flipped)
        self.assertIn('u16 other;', flipped)
        with self.assertRaises(ValueError):
            T.field_declaration(HEADER, 'Rec', 'pad')            # an int, out of scope

    def test_casts_on_the_field_only(self):
        text = ('a = (s16)r->timer; b = (s16)(r->timer); c = (s16)r->other; d = (s16)r->timer + 1;\n'
                'e = (s16)(r->timer + 1); f = (u16)r->timer; g = (short)p->q[2].timer;\n')
        stripped, count = T.strip_casts(text, T.SPELLINGS['s16'], 'timer')
        self.assertEqual(count, 4)
        self.assertEqual(stripped, 'a = r->timer; b = (r->timer); c = (s16)r->other; d = r->timer + 1;\n'
                                   'e = (s16)(r->timer + 1); f = (u16)r->timer; g = p->q[2].timer;\n')

    def test_split_functions_normalises_labels(self):
        asm = '\t.file "a.c"\nf:\n\tlhu $2,4($4)\n$L12:\n\tb $L12\ng:\n\tjr $31\n'
        self.assertEqual(T.split_functions(asm), {'f': ['\tlhu $2,4($4)', '$L:', '\tb $L'], 'g': ['\tjr $31']})


class TrialTests(Base):
    def test_clean_flip_when_every_cast_drops_and_code_is_identical(self):
        tu = self.source('a.c', 'void f(Rec *r) {\n    if ((s16)r->timer < 0) g();\n}\nvoid h(Rec *r) {\n    x = r->timer;\n}\n')
        result = T.trial(self.root, 'include/rec.h::Rec.timer', fake_compile(self.root))
        self.assertEqual(result['declared'], 'u16')
        self.assertEqual((result['casts_now'], result['differing']), (1, 0))
        self.assertEqual(result['recommendation'], 'FLIP_CLEAN')
        self.assertEqual(result['recommended_type'], 's16')
        self.assertEqual({(f['function'], f['status']) for f in result['functions']},
                         {('f', 'identical'), ('h', 'identical')})
        # everything is restored
        self.assertIn('u16 timer;', (self.root / 'include/rec.h').read_text())
        self.assertIn('(s16)r->timer', (self.root / tu).read_text())

    def test_keep_when_the_flip_needs_more_casts(self):
        # a declared u16 field compared unsigned: a signed declaration changes the code in every function
        # that compares it with no (s16) cast to strip
        self.source('a.c', 'void f(Rec *r) {\n    if (r->timer < 9) g();\n}\nvoid h(Rec *r) {\n    if (r->timer < 3) g();\n}\n')
        result = T.trial(self.root, 'include/rec.h::Rec.timer', fake_compile(self.root))
        self.assertEqual((result['casts_now'], result['differing']), (0, 2))
        self.assertEqual(result['recommendation'], 'KEEP')
        self.assertEqual({f['status'] for f in result['functions']}, {'differs'})
        self.assertEqual(result['recommended_type'], 'u16')

    def test_flip_better_when_fewer_functions_differ_than_casts_drop(self):
        self.source('a.c', 'void f(Rec *r) {\n    if ((s16)r->timer < 0) g();\n    if ((s16)r->timer < 1) g();\n}\n'
                           'void h(Rec *r) {\n    if (r->timer < 3) g();\n}\n')
        result = T.trial(self.root, 'include/rec.h::Rec.timer', fake_compile(self.root))
        self.assertEqual((result['casts_now'], result['differing']), (2, 1))
        self.assertEqual(result['recommendation'], 'FLIP_BETTER')

    def test_no_users(self):
        self.source('a.c', 'void f(Rec *r) {\n    x = r->other;\n}\n')
        result = T.trial(self.root, 'include/rec.h::Rec.timer', fake_compile(self.root), tus=['src/a.c'])
        self.assertEqual(result['recommendation'], 'NO_TUS')

    def test_restores_files_when_the_compile_fails(self):
        self.source('a.c', 'void f(Rec *r) {\n    x = (s16)r->timer;\n}\n')
        calls = []

        def broken(tus):
            calls.append(1)
            if len(calls) > 1:
                raise ValueError('boom')
            return fake_compile(self.root)(tus)
        with self.assertRaises(ValueError):
            T.trial(self.root, 'include/rec.h::Rec.timer', broken)
        self.assertIn('u16 timer;', (self.root / 'include/rec.h').read_text())
        self.assertIn('(s16)r->timer', (self.root / 'src/a.c').read_text())


class RemovalTests(Base):
    def test_noop_casts_are_found_one_at_a_time(self):
        self.source('a.c', 'void f(Rec *r) {\n    x = (s16)r->timer;\n}\n'
                           'void h(Rec *r) {\n    if ((s16)r->timer < 0) g();\n}\n')
        result = T.check_removal(self.root, 'include/rec.h::Rec.timer', fake_compile(self.root))
        self.assertEqual([(r['line'], r['verdict']) for r in result['casts']], [(3, 'NO-OP'), (6, 'NEEDED')])
        self.assertEqual(result['noops'], 1)
        self.assertEqual(result['casts'][1]['functions'], ['h'])
        self.assertIn('(s16)r->timer', (self.root / 'src/a.c').read_text().split('void h')[0])

    def test_main_formats(self):
        text = T.format_trial(dict(spec='s', declared='u16', flipped='s16', status='ok', tus=['a.c'],
                                   stripped={'a.c': 2}, casts_now=2, differing=0, functions=[], recommendation='FLIP_CLEAN',
                                   recommended_type='s16'))
        self.assertIn('recommendation: FLIP_CLEAN -> declare s16', text)


if __name__ == '__main__':
    unittest.main()
