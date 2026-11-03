"""Run with python3 -m unittest discover -s tools/typing/cast_routes."""
from pathlib import Path
import sys
import tempfile
import unittest

HERE = Path(__file__).resolve().parent
sys.path.insert(0, str(HERE))
import guarded_routes as G
from baseline_backup import BaselineBackup
from reapply import prepare

SOURCE = r'''
#include "common.h"
#include "shared/entity.h"
#include "shared/object_node.h"
typedef struct GuardRecord {
    short value;
    volatile short changing;
    const short fixed;
    int wide;
} GuardRecord;
extern void accept_const(const void *);
extern void accept_variadic(int, ...);
static int global_value;
static int *global_pointer = (int *)&global_value;
void *same_pointer(void *p) { return (void *)p; }
void *implicit_pointer(int *p) { return (u8 *)p; }
void qualified_pointer(int *p) { accept_const((u8 *)p); }
void variadic_pointer(int *p) { accept_variadic(0, (void *)p); }
void *discard_qualification(const int *p) { return (void *)p; }
u8 *scaled_arithmetic(int *p) { return (u8 *)p + 32; }
void *body_value(ObjectNodeHeader *p) { return (u8 *)p + 32; }
ObjectNodeHeader *header_value(ActorRecord *p) { return (ObjectNodeHeader *)((u8 *)p - 32); }
ObjectNodeHeader *legacy_header(EntityRec *p) { return (ObjectNodeHeader *)((u8 *)p - 32); }
int body_dereference(ObjectNodeHeader *p) { return *(int *)((u8 *)p + 32); }
unsigned short member_load(GuardRecord *p) { return *(u16 *)&p->value; }
void member_store(GuardRecord *p, int x) { *(u16 *)&p->value = x; }
int consumed_store(GuardRecord *p, int x) { return (*(u16 *)&p->value = x); }
void compound_store(GuardRecord *p, int x) { *(u16 *)&p->value += x; }
void increment_store(GuardRecord *p) { (*(u16 *)&p->value)++; }
int volatile_member(GuardRecord *p) { return *(u16 *)&p->changing; }
void const_member(GuardRecord *p) { *(u16 *)&p->fixed = 1; }
int unequal_width(GuardRecord *p) { return *(u16 *)&p->wide; }
#define GUARD_ACCESS(p) (*(u16 *)&(p)->value)
int macro_member(GuardRecord *p) { return GUARD_ACCESS(p); }
int reverse_access(ActorRecord *p) { return ((ObjectNodeHeader *)((u8 *)p - 32))->flags; }
int reverse_other_access(ActorRecord *p) { return ((GuardRecord *)((u8 *)p - 32))->wide; }
int unknown_reverse_access(EntityRec *p) { return ((ObjectNodeHeader *)((u8 *)p - 32))->flags; }
int body_array_access(ObjectNodeHeader *p) { return ((int *)((u8 *)p + 32))[1]; }
int body_byte_access(ObjectNodeHeader *p) { return *((u8 *)p + 32); }
int consumed_compound(GuardRecord *p) { return (*(u16 *)&p->value += 1); }
extern int next_value(void);
void compound_call(GuardRecord *p) { *(u16 *)&p->value += next_value(); }
void compound_volatile_base(GuardRecord * volatile p) { *(u16 *)&p->value += 1; }
void compound_float(GuardRecord *p) { *(u16 *)&p->value += 1.5f; }
void compound_const(GuardRecord *p) { *(u16 *)&p->fixed += 1; }
void compound_bitwise(GuardRecord *p, unsigned short x) { *(u16 *)&p->value ^= x; }
void compound_shift(GuardRecord *p, int x) { *(u16 *)&p->value >>= x; }
#define GUARD_INCREMENT(p) (*(u16 *)&(p)->value += 1)
void compound_macro(GuardRecord *p) { GUARD_INCREMENT(p); }
typedef void (*GuardVariadic)(int, ...);
typedef void (*GuardUnprototyped)();
void alias_variadic(GuardVariadic cb, int *p) { cb(0, (void *)p); }
void alias_unprototyped(GuardUnprototyped cb, int *p) { cb((void *)p); }
typedef union GuardUnion { short signed_value; unsigned short unsigned_value; } GuardUnion;
typedef union GuardOffsets {
    struct { short low, high; } signed_parts;
    struct { unsigned short low, high; } unsigned_parts;
} GuardOffsets;
typedef union GuardVolatileAlias { short value; volatile unsigned short changing; } GuardVolatileAlias;
unsigned short union_load(GuardUnion *p) { return *(u16 *)&p->signed_value; }
void union_store(GuardUnion *p, int x) { *(u16 *)&p->signed_value = x; }
void union_compound(GuardOffsets *p, int x) { *(u16 *)&p->signed_parts.high += x; }
unsigned short nested_union_load(GuardOffsets *p) { return *(u16 *)&p->signed_parts.high; }
unsigned short volatile_alias(GuardVolatileAlias *p) { return *(u16 *)&p->value; }



'''


class GuardedRoutesTest(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.scratch = tempfile.TemporaryDirectory(prefix='cast-route-test-', dir=G.ROOT / 'build')
        cls.file = Path(cls.scratch.name) / 'guard_fixture.c'
        cls.file.write_text(SOURCE)
        rel = cls.file.relative_to(G.ROOT).as_posix()
        cls.result = G.scan((str(G.ROOT), rel, None, [rel]))
        if cls.result['error']:
            raise AssertionError(cls.result['error'])
        cls.by_function = {}
        for plan in cls.result['plans']:
            cls.by_function.setdefault(plan['function'], []).append(plan)

    @classmethod
    def tearDownClass(cls):
        cls.scratch.cleanup()

    def test_accepted_routes(self):
        expected = {
            '<global>': 'redundant', 'same_pointer': 'redundant',
            'implicit_pointer': 'redundant', 'qualified_pointer': 'qualified_argument',
            'body_value': 'node_body', 'header_value': 'node_body',
            'member_load': 'numeric_member', 'member_store': 'numeric_member',
            'compound_store': 'numeric_member', 'body_dereference': 'node_body',
            'reverse_access': 'node_body', 'reverse_other_access': 'node_body',
            'body_array_access': 'node_body', 'compound_bitwise': 'numeric_member', 'compound_shift': 'numeric_member',
            'union_load': 'numeric_member', 'union_store': 'numeric_member', 'nested_union_load': 'numeric_member', 'union_compound': 'numeric_member',
        }
        for function, route in expected.items():
            with self.subTest(function=function):
                self.assertTrue(any(p['route'] == route for p in self.by_function.get(function, [])))
        self.assertTrue(any('NODE_HEADER' in p['new'] for p in self.by_function['header_value']))

    def test_refused_contexts(self):
        for function in ('variadic_pointer', 'discard_qualification', 'scaled_arithmetic',
                         'legacy_header', 'consumed_store',
                         'increment_store', 'volatile_member', 'const_member', 'unequal_width', 'macro_member',
                         'unknown_reverse_access', 'body_byte_access', 'consumed_compound', 'compound_call',
                         'compound_volatile_base', 'compound_float', 'compound_const', 'compound_macro',
                         'alias_variadic', 'alias_unprototyped'):
            with self.subTest(function=function):
                self.assertFalse(self.by_function.get(function))

    def test_extension_net_counts_and_conversion(self):
        for function, reduction in (('body_dereference', 1), ('reverse_access', 2), ('reverse_other_access', 1), ('compound_store', 1)):
            with self.subTest(function=function):
                plans = self.by_function[function]
                self.assertTrue(any(p['casts'] == reduction for p in plans))
        plan = next(p for p in self.by_function['compound_store'] if p['route'] == 'numeric_member')
        self.assertIn('(u16)', plan['new'])
        self.assertEqual(plan['new'].count('x'), 1)
        self.assertEqual(plan['reason'], 'same_width_integer_member_compound_statement')

    def test_rewritten_extension_fixture_parses(self):
        plans = {}
        for plan in self.result['plans']:
            if plan['reason'].endswith(('typed_access', 'compound_statement', 'union_member_load', 'union_member_store')):
                plans[(plan['start'], plan['end'])] = plan
        text = SOURCE
        for plan in sorted(plans.values(), key=lambda p: -p['start']):
            self.assertEqual(text[plan['start']:plan['end']], plan['old'])
            text = text[:plan['start']] + plan['new'] + text[plan['end']:]
        file = Path(self.scratch.name) / 'rewritten_fixture.c'
        file.write_text(text)
        unit, error = G.A.clang_unit(G.ROOT, file.relative_to(G.ROOT).as_posix())
        self.assertIsNotNone(unit)
        self.assertFalse(error, error)

    def test_exact_integer_union_views(self):
        for function, suffix in (('union_load', 'load'), ('union_store', 'store')):
            with self.subTest(function=function):
                plan = self.by_function[function][0]
                self.assertEqual(plan['reason'], 'same_width_integer_union_member_'+suffix)
                self.assertEqual(plan['new'], '(p)->unsigned_value')
                self.assertEqual(plan['casts'], 1)
        self.assertEqual(self.by_function['union_compound'][0]['new'], '(p)->unsigned_parts.high += (x)')
        self.assertEqual(self.by_function['union_compound'][0]['reason'], 'same_width_integer_union_member_compound_statement')
        self.assertEqual(self.by_function['nested_union_load'][0]['new'], '(p)->unsigned_parts.high')
        self.assertEqual(self.by_function['volatile_alias'][0]['reason'], 'same_width_integer_member_load')

    def test_baseline_rollback(self):
        root = Path(self.scratch.name)
        (root / 'object.o').write_bytes(b'original object')
        (root / 'object.proof.json').write_text('original receipt')
        backup = BaselineBackup(root, root / 'backup', ['object.o', 'object.proof.json', 'new_witness.json'])
        (root / 'object.o').write_bytes(b'adopted object')
        (root / 'object.proof.json').write_text('adopted receipt')
        (root / 'new_witness.json').write_text('adopted witness')
        backup.restore()
        self.assertEqual((root / 'object.o').read_bytes(), b'original object')
        self.assertEqual((root / 'object.proof.json').read_text(), 'original receipt')
        self.assertFalse((root / 'new_witness.json').exists())

    def test_replay_guards(self):
        root = Path(self.scratch.name)
        (root / 'src').mkdir(exist_ok=True)
        file = root / 'src/fixture.c'
        text = 'int *p = (int *)q;\n'
        file.write_text(text)
        row = dict(file='src/fixture.c', source_sha256=G.digest(text), start=9, end=16, old='(int *)', new='')
        self.assertEqual(prepare(root, [row])[file], 'int *p = q;\n')
        self.assertEqual(file.read_text(), text)
        for bad in (dict(row, source_sha256='stale'), dict(row, old='wrong'), dict(row, file='../outside'), dict(row, start=-1)):
            with self.subTest(bad=bad):
                with self.assertRaises(ValueError):
                    prepare(root, [bad])
        with self.assertRaises(ValueError):
            prepare(root, [row, row])
        adjacent = 'xx'
        file.write_text(adjacent)
        rows = [dict(row, source_sha256=G.digest(adjacent), start=0, end=1, old='x', new='a'),
                dict(row, source_sha256=G.digest(adjacent), start=1, end=2, old='x', new='b')]
        self.assertEqual(prepare(root, rows)[file], 'ab')



if __name__ == '__main__':
    unittest.main()
