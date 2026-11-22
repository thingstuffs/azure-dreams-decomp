"""Unit tests for the address_member route of guarded_routes.py.

Run with python3 -m unittest tools/typing/cast_routes/test_address_member_route.py.  They need MIPS Clang and
a `build/` directory under the repository root (created when missing, ignored by git) but no build tree."""
from pathlib import Path
import re
import subprocess
import sys
import tempfile
import unittest

HERE = Path(__file__).resolve().parent
sys.path.insert(0, str(HERE))
import guarded_routes as G

SOURCE = r'''
#include "common.h"
typedef struct AddrInner { u8 first; u8 second; } AddrInner;
typedef struct AddrRecord {
    s32 head;              /* 0 */
    s16 half;              /* 4 */
    u16 uhalf;             /* 6 */
    s8 flag;               /* 8 */
    u8 tail[3];            /* 9 */
    AddrInner inner;       /* 12 */
    s16 words[3];          /* 14 */
    volatile u8 changing;  /* 20 */
    const u8 fixed;        /* 21 */
    u8 padding[2];         /* 22 */
    union { s32 a; s32 b; } u; /* 24 */
    void (*callback)(void);    /* 28 */
    u32 bits : 4;          /* 32 */
    long wide;             /* 36 */
} AddrRecord;
typedef struct AddrAnon { s32 lead; union { s32 x; s16 y[2]; }; u8 grid[2][2]; } AddrAnon;
typedef struct AddrRow { AddrRecord *rec; } AddrRow;
typedef struct AddrTable { AddrRow rows[2]; } AddrTable;
typedef struct S_80123456 { s32 a; s32 b; } S_80123456;
typedef struct AddrHolder { AddrRecord *rec; } AddrHolder;
extern void use_void(void *);
extern void use_variadic(int, ...);
extern int next_index(void);

s16 *accept_exact(AddrRecord *p) { return (s16 *)((u8 *)p + 4); }
void *accept_void_value(AddrRecord *p) { return (u8 *)p + 6; }
void *accept_void_cast(AddrRecord *p) { return (void *)((u8 *)p + 6); }
s8 *accept_signed_byte(AddrRecord *p) { return (s8 *)p + 8; }
u8 *accept_array_start(AddrRecord *p) { return (u8 *)p + 9; }
u8 *accept_array_element(AddrRecord *p) { return (u8 *)p + 10; }
u8 *accept_subscript_spelling(AddrRecord *p) { return &((u8 *)p)[11]; }
s16 *accept_word_element(AddrRecord *p) { return (s16 *)((u8 *)p + 16); }
AddrInner *accept_nested_struct(AddrRecord *p) { return (AddrInner *)((u8 *)p + 12); }
u8 *accept_nested_first(AddrRecord *p) { return (u8 *)p + 12; }
u8 *accept_nested_second(AddrRecord *p) { return (u8 *)p + 13; }
void *accept_nested_void(AddrRecord *p) { return (u8 *)p + 12; }
void accept_call_argument(AddrRecord *p) { use_void((u8 *)p + 6); }
s16 *accept_declaration(AddrRecord *p) { s16 *q = (s16 *)((u8 *)p + 4); return q; }
s16 *accept_chained_arithmetic(AddrRecord *p) { return (s16 *)((u8 *)p + 2 + 2); }
void *accept_union_void(AddrRecord *p) { return (u8 *)p + 24; }
s16 *accept_member_chain_base(AddrHolder *h) { return (s16 *)((u8 *)h->rec + 4); }
void *accept_array_void(AddrRecord *p) { return (u8 *)p + 9; }
s16 *keep_cast_signedness(AddrRecord *p) { return (s16 *)((u8 *)p + 6); }
s16 *excluded_by_offset(AddrRecord *p) { return (s16 *)((u8 *)p + 4); }

void *refuse_untyped_base(void *p) { return (u8 *)p + 4; }
void *refuse_anonymous_union_void(AddrAnon *p) { return (u8 *)p + 4; }
u8 *refuse_multidimensional(AddrAnon *p) { return (u8 *)p + 8; }
s16 *refuse_impure_base(AddrTable *t) { return (s16 *)((u8 *)t->rows[next_index()].rec + 4); }
#define ROW_RECORD(t) ((t)->rows[0].rec)
s16 *refuse_macro_base(AddrTable *t) { return (s16 *)((u8 *)ROW_RECORD(t) + 4); }
s32 *refuse_long_for_int(AddrRecord *p) { return (s32 *)((u8 *)p + 36); }
char *refuse_char_for_signed_char(AddrRecord *p) { return (char *)p + 8; }
s16 *refuse_byte_base(u8 *p) { return (s16 *)(p + 4); }
s16 *refuse_object_address(void) { AddrRecord rec; return (s16 *)((u8 *)&rec + 4); }
AddrRecord *global_table_base(void);
s16 refuse_dereference(AddrRecord *p) { return *(s16 *)((u8 *)p + 4); }
s16 refuse_dereference_index(AddrRecord *p) { return ((s16 *)((u8 *)p + 4))[0]; }
u8 *refuse_zero_offset(AddrRecord *p) { return (u8 *)p + 0; }
u8 *refuse_variable_offset(AddrRecord *p, int i) { return (u8 *)p + i; }
u8 *refuse_call_offset(AddrRecord *p) { return (u8 *)p + next_index(); }
u8 *refuse_negative(AddrRecord *p) { return (u8 *)p - 4; }
u8 *refuse_beyond(AddrRecord *p) { return (u8 *)p + 40; }
u8 *refuse_inside_scalar(AddrRecord *p) { return (u8 *)p + 5; }
u8 *refuse_inside_array(AddrRecord *p) { return (u8 *)p + 17; }
u8 *refuse_padding(AddrRecord *p) { return (u8 *)p + 22; }
u8 *refuse_bitfield(AddrRecord *p) { return (u8 *)p + 32; }
u8 *refuse_volatile_member(AddrRecord *p) { return (u8 *)p + 20; }
void *refuse_const_member(AddrRecord *p) { return (u8 *)p + 21; }
void *refuse_function_pointer(AddrRecord *p) { return (u8 *)p + 28; }
s32 *refuse_union_ambiguous(AddrRecord *p) { return (s32 *)((u8 *)p + 24); }
u8 *refuse_pointee_mismatch(AddrRecord *p) { u8 *q = (u8 *)p + 4; return q; }
u16 *refuse_signedness_mismatch(AddrRecord *p) { return (u16 *)((u8 *)p + 4); }
void refuse_variadic_context(AddrRecord *p) { use_variadic(0, (u8 *)p + 6); }
void *refuse_qualified_base(const AddrRecord *p) { return (void *)((u8 *)p + 4); }
void *refuse_generated_record(S_80123456 *p) { return (u8 *)p + 4; }
#define MEMBER_ADDRESS(p) ((u8 *)(p) + 4)
s16 *refuse_macro(AddrRecord *p) { return (s16 *)MEMBER_ADDRESS(p); }
'''

ACCEPT = {
    'accept_exact': ('&p->half', 'exact_member_address', 2),
    'accept_void_value': ('&p->uhalf', 'untyped_void_context_member_address', 1),
    'accept_void_cast': ('&p->uhalf', 'untyped_void_context_member_address', 2),
    'accept_signed_byte': ('&p->flag', 'exact_member_address', 1),
    'accept_array_start': ('p->tail', 'exact_member_address', 1),
    'accept_array_element': ('&p->tail[1]', 'exact_member_address', 1),
    'accept_subscript_spelling': ('&p->tail[2]', 'exact_member_address', 1),
    'accept_word_element': ('&p->words[1]', 'exact_member_address', 2),
    'accept_nested_struct': ('&p->inner', 'exact_member_address', 2),
    'accept_nested_first': ('&p->inner.first', 'exact_member_address', 1),
    'accept_nested_second': ('&p->inner.second', 'exact_member_address', 1),
    'accept_nested_void': ('&p->inner', 'untyped_void_context_member_address', 1),
    'accept_call_argument': ('&p->uhalf', 'untyped_void_context_member_address', 1),
    'accept_declaration': ('&p->half', 'exact_member_address', 2),
    'accept_chained_arithmetic': ('&p->half', 'exact_member_address', 2),
    'accept_union_void': ('&p->u', 'untyped_void_context_member_address', 1),
    'accept_member_chain_base': ('&h->rec->half', 'exact_member_address', 2),
    'accept_array_void': ('p->tail', 'untyped_void_context_member_address', 1),
}

REFUSE = {
    'refuse_untyped_base': 'base_not_record_pointer',
    'refuse_byte_base': 'base_not_record_pointer',
    'refuse_object_address': 'base_not_record_pointer',
    'refuse_dereference': 'dereferenced_use_is_cast_fold',
    'refuse_dereference_index': 'dereferenced_use_is_cast_fold',
    'refuse_negative': 'negative_offset',
    'refuse_beyond': 'beyond_struct',
    'refuse_inside_scalar': 'inside_scalar_member',
    'refuse_inside_array': 'inside_array_member',
    'refuse_padding': 'pad_member',
    'refuse_bitfield': 'bitfield_member',
    'refuse_volatile_member': 'qualified_member',
    'refuse_const_member': 'qualified_member',
    'refuse_function_pointer': 'function_pointer_or_multidimensional_member',
    'refuse_union_ambiguous': 'ambiguous_members',
    'refuse_anonymous_union_void': 'no_member_at_offset',  # the layout reader sizes no anonymous union
    'refuse_multidimensional': 'function_pointer_or_multidimensional_member',
    'refuse_impure_base': 'impure_base',
    'refuse_macro_base': 'macro_or_missing_source_range',
    'refuse_long_for_int': 'pointee_type_mismatch',
    'refuse_char_for_signed_char': 'pointee_type_mismatch',
    'refuse_pointee_mismatch': 'pointee_type_mismatch',
    'refuse_signedness_mismatch': 'pointee_type_mismatch',
    'refuse_variadic_context': 'pointee_type_mismatch',
    'refuse_qualified_base': 'qualified_base',
    'refuse_generated_record': 'generated_record_view',
}
SILENT = ('refuse_zero_offset', 'refuse_variable_offset', 'refuse_call_offset', 'refuse_macro')


class AddressMemberTest(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        (G.ROOT / 'build').mkdir(exist_ok=True)
        cls.scratch = tempfile.TemporaryDirectory(prefix='address-member-test-', dir=G.ROOT / 'build')
        cls.file = Path(cls.scratch.name) / 'address_fixture.c'
        cls.file.write_text(SOURCE)
        cls.rel = cls.file.relative_to(G.ROOT).as_posix()
        cls.options = dict(address_member=True)
        cls.result = cls.scan(cls.options)
        cls.plans = cls.by_function(cls.result['plans'])
        cls.holds = cls.by_line(cls.result['holds'])

    @classmethod
    def tearDownClass(cls):
        cls.scratch.cleanup()

    @classmethod
    def scan(cls, options):
        result = G.scan((str(G.ROOT), cls.rel, None, [cls.rel], options))
        if result['error']:
            raise AssertionError(result['error'])
        return result

    @classmethod
    def by_function(cls, plans):
        found = {}
        for plan in plans:
            if plan['route'] == 'address_member':
                found.setdefault(plan['function'], []).append(plan)
        return found

    @classmethod
    def by_line(cls, holds):
        lines = SOURCE.splitlines()
        found = {}
        for hold in holds:
            if hold['route'] != 'address_member':
                continue
            text = lines[hold['line'] - 1]
            name = re.search(r'(\w+)\(', text).group(1)
            found.setdefault(name, []).append(hold['reason'])
        return found

    def test_accepted_sites(self):
        for function, (new, reason, casts) in ACCEPT.items():
            with self.subTest(function=function):
                plans = self.plans.get(function, [])
                self.assertEqual(len(plans), 1, plans)
                self.assertEqual((plans[0]['new'], plans[0]['reason'], plans[0]['casts']), (new, reason, casts))

    def test_refused_sites_and_reasons(self):
        for function, reason in REFUSE.items():
            with self.subTest(function=function):
                self.assertNotIn(function, self.plans)
                self.assertEqual(self.holds.get(function), [reason])

    def test_silent_sites_are_not_candidates(self):
        for function in SILENT:
            with self.subTest(function=function):
                self.assertNotIn(function, self.plans)
                self.assertNotIn(function, self.holds)

    def test_every_function_is_classified(self):
        names = {line.split('(')[0].split()[-1].lstrip('*') for line in SOURCE.splitlines()
                 if line.startswith(('s16 ', 's8 ', 'u8 ', 'u16 ', 's32 ', 'void ', 'AddrInner ')) and '(' in line}
        known = set(ACCEPT) | set(REFUSE) | set(SILENT) | {'keep_cast_signedness', 'excluded_by_offset', 'use_void', 'use_variadic',
                                                           'next_index', 'global_table_base'}
        self.assertEqual(names - known, set())

    def test_route_is_opt_in(self):
        default = self.scan({})
        self.assertFalse([p for p in default['plans'] if p['route'] == 'address_member'])
        self.assertFalse([h for h in default['holds'] if h['route'] == 'address_member'])
        self.assertNotIn('address_member', G.ROUTES)
        self.assertEqual(G.ROUTE_ORDER[0], 'address_member')

    def test_keep_cast_needs_a_net_reduction(self):
        result = self.scan(dict(address_member=True, keep_cast=True))
        plans = self.by_function(result['plans'])
        plan = plans['keep_cast_signedness'][0]
        self.assertEqual((plan['new'], plan['reason'], plan['casts']), ('(s16 *)&p->uhalf', 'member_address_cast_kept', 1))
        # two casts become one: kept.  One cast kept for one removed is not a reduction: refused by the net guard.
        self.assertEqual(plans['refuse_signedness_mismatch'][0]['new'], '(u16 *)&p->half')
        self.assertEqual(plans['refuse_signedness_mismatch'][0]['casts'], 1)
        self.assertNotIn('refuse_pointee_mismatch', plans)
        self.assertEqual(self.by_line(result['holds'])['refuse_pointee_mismatch'], ['no_net_cast_reduction'])
        # keep_cast never turns an exact or void-context site into a kept cast
        self.assertEqual(plans['accept_exact'][0]['new'], '&p->half')

    def test_exclusion_by_record_offset(self):
        result = self.scan(dict(address_member=True, exclude_member=['AddrRecord:4,0x8']))
        plans = self.by_function(result['plans'])
        for function in ('accept_exact', 'accept_declaration', 'accept_signed_byte', 'excluded_by_offset'):
            with self.subTest(function=function):
                self.assertNotIn(function, plans)
        self.assertIn('accept_array_start', plans)
        reasons = self.by_line(result['holds'])
        self.assertEqual(reasons['accept_exact'], ['excluded_member'])
        everything = self.scan(dict(address_member=True, exclude_member=['AddrRecord:*']))
        self.assertFalse(self.by_function(everything['plans']))
        other = self.scan(dict(address_member=True, exclude_member=['OtherRecord:4']))
        self.assertEqual(set(self.by_function(other['plans'])), set(self.plans))

    def test_outermost_paths(self):
        self.assertEqual(G.outermost(['x', 'y', 'y[0]', 'y[0].z']), ['x', 'y'])
        self.assertEqual(G.outermost(['inner', 'inner.first']), ['inner'])

    def test_exclusion_parser(self):
        self.assertEqual(G.parse_exclusions(['ActorRecord:8,0xB,0xE', 'ActorRecord:0x10']),
                         {'ActorRecord': {8, 11, 14, 16}})
        self.assertEqual(G.parse_exclusions(['A:*', 'A:4']), {'A': None})
        for bad in ('ActorRecord', 'ActorRecord:', ':8', 'ActorRecord:x'):
            with self.subTest(bad=bad), self.assertRaises(ValueError):
                G.parse_exclusions([bad])

    def test_plan_spans_are_exact_and_non_overlapping(self):
        spans = sorted((p['start'], p['end'], p['old']) for plans in self.plans.values() for p in plans)
        for (a, b, old), (c, d, _) in zip(spans, spans[1:]):
            self.assertLessEqual(b, c)
        for start, end, old in spans:
            self.assertEqual(SOURCE[start:end], old)

    def test_replay_accepts_address_member_rows(self):
        from reapply import prepare
        plan = self.plans['accept_exact'][0]
        with tempfile.TemporaryDirectory(prefix='address-member-replay-') as td:
            root = Path(td)
            (root / 'src').mkdir()
            (root / 'src/fixture.c').write_text(SOURCE)
            row = dict(plan, file='src/fixture.c')
            text = prepare(root, [row])[(root / 'src/fixture.c').resolve()]
            self.assertIn('return &p->half;', text)
            self.assertEqual(text.count('&p->half'), 1)
            with self.assertRaises(ValueError):
                prepare(root, [dict(row, source_sha256='stale')])

    def compile(self, text, name, *flags):
        source = Path(self.scratch.name) / name
        source.write_text(text)
        done = subprocess.run([G.C.CLANG, '--target=mipsel-unknown-none', '-I', 'include', '-w', *flags,
                               source.relative_to(G.ROOT).as_posix()], cwd=G.ROOT, capture_output=True, text=True)
        self.assertEqual(done.returncode, 0, done.stderr[-2000:])
        return done.stdout

    def test_rewrite_compiles_and_keeps_the_assembly(self):
        text = SOURCE
        for plan in sorted((p for plans in self.plans.values() for p in plans), key=lambda p: -p['start']):
            text = text[:plan['start']] + plan['new'] + text[plan['end']:]
        self.assertNotEqual(text, SOURCE)
        # the rewrite introduces no incompatible pointer conversion
        self.compile(text, 'rewritten_types.c', '-fsyntax-only', '-Werror=incompatible-pointer-types',
                     '-Werror=int-conversion', '-Werror=incompatible-pointer-types-discards-qualifiers')
        # and no instruction changes (the stand-in for the production byte-identity gate)
        before = self.compile(SOURCE, 'identity_before.c', '-O2', '-S', '-o', '-')
        after = self.compile(text, 'identity_after.c', '-O2', '-S', '-o', '-')
        strip = lambda asm: [l for l in asm.splitlines() if not l.lstrip().startswith(('.file', '.ident'))]
        self.assertGreater(len(strip(before)), 100)
        self.assertEqual(strip(before), strip(after))


if __name__ == '__main__':
    unittest.main()
