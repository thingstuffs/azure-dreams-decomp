"""Regression cases for declaration safety and bank-specific ownership."""
import json
import contextlib
import io
from pathlib import Path
import tempfile
import unittest

from tools.proto import prototypes as P


class Fixture(unittest.TestCase):
    def setUp(self):
        temporary_root = P.ROOT / 'build' / 'prototype-tests'
        temporary_root.mkdir(parents=True, exist_ok=True)
        self.tmp = tempfile.TemporaryDirectory(dir=temporary_root)
        self.addCleanup(self.tmp.cleanup)
        self.root = Path(self.tmp.name)
        self.put('include/common.h', 'typedef int s32; typedef short s16;\n')

    def put(self, path, text):
        target = self.root / path
        target.parent.mkdir(parents=True, exist_ok=True)
        target.write_text(text)

    def image(self, name, entries):
        self.put('config/link/' + name + '.json', json.dumps(dict(image=name, entries=entries)))

    def rows(self, *rows):
        self.put('ledger/rows.jsonl', ''.join(json.dumps(r) + '\n' for r in rows))

    def plan(self, scope=()):
        return P.candidates(self.root, scope)


class PrototypeTests(Fixture):
    def cli(self, *args):
        with contextlib.redirect_stdout(io.StringIO()):
            return P.main(['--root', str(self.root), *args])

    def test_check_threshold_and_baseline_reject_new_site_at_same_count(self):
        self.put('src/town/a.c', 'void f();\n')
        out = self.root / 'audit'
        self.assertEqual(self.cli('--check', '--out', str(out)), 1)
        self.assertEqual(self.cli('--check', '--max-remaining', '1'), 0)
        self.assertEqual(self.cli('--check', '--baseline', str(out / 'remaining.tsv')), 0)
        self.put('src/town/a.c', 'void g();\n')
        self.assertEqual(self.cli('--check', '--baseline', str(out / 'remaining.tsv')), 1)
        self.put('src/town/a.c', 'void g(void);\n')
        self.assertEqual(self.cli('--check', '--baseline', str(out / 'remaining.tsv')), 0)

    def test_pointer_slots_are_separate_from_direct_declarations(self):
        self.put('include/slot.h', 'void (*callback)();\n')
        out = self.root / 'audit'
        self.assertEqual(self.cli('--check', '--out', str(out)), 0)
        count = json.loads((out / 'count.json').read_text())
        self.assertEqual(count['remaining'], 0)
        self.assertEqual(count['untyped_function_pointer_slots'], 1)

    def test_void_and_named_parameters(self):
        self.put('src/town/a.c', '#include "common.h"\ns32 f();\nvoid z();\n')
        self.put('src/town/b.c', '#include "common.h"\ns32 f(s32 a, s32 b) { return a+b; }\nvoid z() {}\n')
        _, _, remaining, edits, holds = self.plan()
        self.assertEqual(len(remaining), 2)
        self.assertFalse(holds)
        self.assertEqual([e.after for e in edits], ['s32 f(s32 a, s32 b);', 'void z(void);'])

    def test_knr_declaration_is_typed_but_typedef_is_not_identifier_list(self):
        self.put('src/town/a.c', '#include "common.h"\ns32 f(a,b);\ns32 typed(s32);\n')
        self.put('src/town/b.c', '#include "common.h"\ns32 f(s32 a, s32 b) { return a+b; }\n')
        _, _, remaining, edits, holds = self.plan()
        self.assertEqual([s.name for s in remaining], ['f'])
        self.assertFalse(holds)
        self.assertEqual(len(edits), 1)

    def test_old_style_definition_promotes_formals_and_is_not_counted(self):
        self.put('src/town/a.c', '#include "common.h"\ns32 f();\n')
        self.put('src/town/b.c', '#include "common.h"\ns32 f(x,y)\ns16 x,y;\n{ return x+y; }\n')
        _, _, remaining, edits, holds = self.plan()
        self.assertEqual(len(remaining), 1)
        self.assertFalse(holds)
        self.assertEqual(edits[0].after, 's32 f(int x, int y);')

    def test_established_parent_folder_header_owns_nested_definition(self):
        self.put('src/town/a.c', '#include "common.h"\nextern void f();\n')
        self.put('src/town/person/object/f.c', '#include "common.h"\nvoid f(s32 n) {}\n')
        self.put('include/town/person.h', '#include "common.h"\nvoid f(s32 n);\n')
        _, _, _, edits, holds = self.plan(['src/town/a.c'])
        self.assertFalse(holds)
        self.assertEqual(len(edits), 1)
        self.assertEqual((edits[0].action, edits[0].header), ('include', 'include/town/person.h'))

    def test_parent_folder_header_with_different_contract_is_not_selected(self):
        self.put('src/town/a.c', '#include "common.h"\nextern void f();\n')
        self.put('src/town/person/object/f.c', '#include "common.h"\nvoid f(s32 n) {}\n')
        self.put('include/town/person.h', '#include "common.h"\nvoid f(s32 n, s32 other);\n')
        _, _, _, edits, holds = self.plan(['src/town/a.c'])
        self.assertFalse(holds)
        self.assertEqual(edits[0].action, 'prototype')

    def test_reviewed_in_place_plan_recovers_the_same_owner_contract(self):
        self.put('src/town/a.c', 'typedef int s32;\nextern s32 f(); /* keep */\n')
        self.put('src/town/shop/b.c', '#include "common.h"\ns32 f(s32 x) { return x; }\n')
        self.put('include/town/shop.h', '#include "common.h"\ns32 f(s32 x);\n')
        out = self.root / 'in-place'
        self.assertEqual(self.cli('--scope', 'src/town/a.c', '--in-place', '--out', str(out)), 0)
        row, = P.table(out / 'replay.tsv')
        self.assertEqual(row['action'], 'prototype')
        self.assertEqual(row['after'], 'extern s32 f(s32 x);')
        self.assertEqual(row['definition'], 'src/town/shop/b.c:f')
        self.assertFalse(row['header'] or row['type_headers'])
        P.apply_edits(self.root, [P.Edit(**{**row, 'occurrences': int(row['occurrences'])})])
        self.assertEqual((self.root / 'src/town/a.c').read_text(),
                         'typedef int s32;\nextern s32 f(s32 x); /* keep */\n')

    def test_file_scope_asm_is_not_a_declaration(self):
        self.put('include/asm.h', '__asm__("payload");\n')
        self.assertFalse(self.plan()[2])

    def test_existing_owner_header_wins(self):
        self.put('src/town/a.c', '#include "common.h"\nextern s32 f(); /* extern */\n')
        self.put('src/town/shop/b.c', '#include "common.h"\ns32 f(s32 x) { return x; }\n')
        self.put('include/town/shop.h', '#include "common.h"\ns32 f(s32 x);\n')
        _, _, _, edits, holds = self.plan()
        self.assertFalse(holds)
        self.assertEqual(edits[0].action, 'include')
        P.apply_edits(self.root, edits)
        self.assertEqual((self.root / 'src/town/a.c').read_text(),
                         '#include "common.h"\n#include "town/shop.h"\n')

    def test_documented_callback_exception_is_preserved(self):
        self.put('src/town/a.c', 'void hook(); /* Unprototyped: shared callback accepts one or two arguments. */\n')
        self.put('src/town/b.c', 'void hook(void) {}\n')
        _, _, remaining, edits, holds = self.plan()
        self.assertEqual(len(remaining), 1)
        self.assertFalse(edits)
        self.assertEqual(holds[0]['reason'], 'documented_varying_arguments')

    def test_wide_only_also_filters_owning_header_route(self):
        self.put('src/town/a.c', '#include "common.h"\nvoid f();\n')
        self.put('src/town/shop/b.c', '#include "common.h"\nvoid f(s16 x) {}\n')
        self.put('include/town/shop.h', '#include "common.h"\nvoid f(s16 x);\n')
        _, _, _, edits, holds = P.candidates(self.root, wide_only=True)
        self.assertFalse(edits)
        self.assertEqual(holds[0]['reason'], 'deferred_narrow_or_aggregate_parameter')

    def test_comments_strings_calls_and_definitions_are_not_declarations(self):
        self.put('src/town/a.c', '/* void hidden(); */\nchar *s="void hidden();";\nvoid z() { z(); }\n')
        self.assertFalse(self.plan()[2])

    def test_static_forward_is_same_tu(self):
        self.put('src/town/a.c', '#include "common.h"\nstatic s32 f();\nstatic s32 f(s32 x) { return x; }\n')
        self.put('src/town/b.c', 'void f(void) {}\n')
        _, _, _, edits, holds = self.plan()
        self.assertFalse(holds)
        self.assertEqual(edits[0].after, 'static s32 f(s32 x);')

    def test_tagged_return_definition_supplies_a_real_prototype(self):
        self.put('src/town/a.c', 'struct Item *lookup();\n')
        self.put('src/town/b.c', 'struct Item { int x; };\n'
                 'struct Item *lookup(struct Item *p) { return p; }\n')
        edits, holds = self.plan()[3:]
        self.assertFalse(holds)
        self.assertEqual(edits[0].after, 'struct Item *lookup(struct Item *p);')

    def test_knr_module_retains_distinct_later_definitions(self):
        self.put('src/town/a.c', 'int first();\nint second();\n')
        self.put('src/town/b.c', 'int first(value)\nshort value;\n{ return value; }\n'
                 'int second(int a, int b) { return a+b; }\n')
        edits, holds = self.plan()[3:]
        self.assertFalse(holds)
        self.assertEqual([e.after for e in edits],
                         ['int first(int value);', 'int second(int a, int b);'])

    def test_knr_array_formal_decays_instead_of_promoting_its_element(self):
        self.put('src/town/a.c', 'int first();\n')
        self.put('src/town/b.c', 'int first(text)\nchar text[];\n{ return text[0]; }\n')
        edits, holds = self.plan()[3:]
        self.assertFalse(holds)
        self.assertEqual(edits[0].after, 'int first(char * text);')

    def test_cross_container_definition_is_not_reported_missing(self):
        self.put('src/dungeon/a.c', 'void f();\n')
        self.put('src/town/b.c', 'void f(void) {}\n')
        self.assertEqual(self.plan()[4][0]['reason'], 'cross_container_binding_unproved')

    def test_static_definition_in_another_file_is_a_distinct_hold(self):
        self.put('src/town/a.c', 'void f();\n')
        self.put('src/town/b.c', 'static void f(void) {}\n')
        self.assertEqual(self.plan()[4][0]['reason'], 'static_definition_not_routed')

    def test_return_contract_is_recovered_for_byte_proof(self):
        self.put('src/town/a.c', '#include "common.h"\ns16 f();\n')
        self.put('src/town/b.c', '#include "common.h"\ns32 f(s32 x) { return x; }\n')
        self.assertEqual(self.plan()[3][0].after, 's32 f(s32 x);')

    def test_private_tag_is_declared_at_file_scope(self):
        self.put('src/town/a.c', '#include "common.h"\nvoid f();\n')
        self.put('src/town/b.c', 'typedef struct Private { int x; } Private;\nvoid f(Private *x) {}\n')
        _, _, _, edits, holds = self.plan()
        self.assertFalse(holds)
        P.apply_edits(self.root, edits)
        self.assertIn('struct Private;\nvoid f(struct Private *x);',
                      (self.root / 'src/town/a.c').read_text())

    def test_missing_private_type_is_not_guessed(self):
        self.put('src/town/a.c', '#include "common.h"\nvoid f();\n')
        self.put('src/town/b.c', 'typedef struct { int x; } Private;\nvoid f(Private *x) {}\n')
        self.assertIn('local_type_anonymous', self.plan()[4][0]['reason'])

    def test_replay_ignores_line_movement_and_preserves_comment(self):
        edit = P.Edit('src/town/a.c', 'f', 'void f();', 'void f(void);', '', '', '')
        text = '// moved\n\nvoid f(); /* contract */\nvoid g() { f(); }\n'
        out = P.rewrite(text, [edit])
        self.assertIn('void f(void); /* contract */', out)
        self.assertIn('void g() { f(); }', out)

    def test_rewrite_trims_only_its_declaration_padding(self):
        edit = P.Edit('src/town/a.c', 'f', 'void f();', 'void f(void);', '', '', '')
        text = 'void f();   \nvoid untouched();  \n'
        self.assertEqual(P.rewrite(text, [edit]), 'void f(void);\nvoid untouched();  \n')

    def test_stale_anchor_rejected_atomically(self):
        self.put('src/town/a.c', 'void f();\n')
        self.put('src/town/b.c', 'void g(int x);\n')
        edits = [P.Edit('src/town/a.c', 'f', 'void f();', 'void f(void);', '', '', ''),
                 P.Edit('src/town/b.c', 'g', 'void g();', 'void g(void);', '', '', '')]
        with self.assertRaises(ValueError):
            P.apply_edits(self.root, edits)
        self.assertEqual((self.root / 'src/town/a.c').read_text(), 'void f();\n')

    def test_duplicate_anchor_rejected(self):
        edit = P.Edit('src/town/a.c', 'f', 'void f();', 'void f(void);', '', '', '')
        with self.assertRaises(ValueError):
            P.rewrite('void f();\nvoid f();\n', [edit])

    def test_repeated_declarations_have_explicit_replay_multiplicity(self):
        self.put('src/town/a.c', 'void f();\nvoid f();\n')
        self.put('src/town/b.c', 'void f(void) {}\n')
        _, _, remaining, edits, holds = self.plan()
        self.assertEqual(len(remaining), 2)
        self.assertFalse(holds)
        self.assertEqual(len(edits), 1)
        self.assertEqual(edits[0].occurrences, 2)
        P.apply_edits(self.root, edits)
        self.assertEqual((self.root / 'src/town/a.c').read_text().count('f(void)'), 2)

    def test_path_escape_rejected(self):
        with self.assertRaises(ValueError):
            P.apply_edits(self.root, [P.Edit('../a.c', 'f', '', '', '', '', '')])


class BankTests(Fixture):
    def setUp(self):
        super().setUp()
        self.put('src/town/caller.c', '#include "common.h"\ns32 func_80016000();\n')
        self.put('src/town/one.c', '#include "common.h"\ns32 one(s32 x) { return x; }\n')
        self.put('src/town/two.c', '#include "common.h"\ns32 two(s32 x, s32 y) { return x+y; }\n')
        self.rows(dict(id='town/func_80100000', func='func_80100000', true_name='one'),
                  dict(id='town/func_80200000', func='func_80200000', true_name='two'))

    def target(self, which, vma='0x80016000'):
        return dict(row='town/func_80' + ('100000' if which == 'one' else '200000'),
                    tu='src/town/' + which + '.c', vma=vma)

    def caller(self, bindings=None):
        return dict(row='town/func_80300000', tu='src/town/caller.c', vma='0x80018000',
                    bindings=bindings or {})

    def named_caller(self):
        self.put('src/town/caller.c', '#include "common.h"\ns32 one();\n')
        self.put('config/names.tsv', '0x80016000\tfunc_80016000\tone\tfixture\n')

    def test_named_alias_resolves_loading_image_instead_of_unrelated_definition(self):
        self.named_caller()
        self.image('town/a', [self.caller(), self.target('two')])
        edits, holds = self.plan()[3:]
        self.assertFalse(holds)
        self.assertEqual(edits[0].after, 's32 one(s32 x, s32 y);')
        self.assertIn('80016000->80016000:two', edits[0].evidence)

    def test_named_alias_does_not_fall_back_when_its_image_has_no_owner(self):
        self.named_caller()
        self.image('town/a', [self.caller()])
        edits, holds = self.plan()[3:]
        self.assertFalse(edits)
        self.assertIn('unresolved_image_binding:town/a', holds[0]['reason'])

    def test_named_alias_requires_every_placement_to_agree(self):
        self.named_caller()
        self.image('town/a', [self.caller(), self.target('one')])
        self.image('town/b', [self.caller(), self.target('two')])
        edits, holds = self.plan()[3:]
        self.assertFalse(edits)
        self.assertEqual(holds[0]['reason'], 'placement_signature_conflict')

    def test_named_header_alias_requires_every_consumer_to_agree(self):
        self.named_caller()
        self.put('include/alias.h', '#include "common.h"\ns32 one();\n')
        self.put('src/town/caller.c', '#include "alias.h"\n')
        self.put('src/town/other.c', '#include "alias.h"\n')
        other = dict(row='town/func_80400000', tu='src/town/other.c', vma='0x80018000')
        self.image('town/a', [self.caller(), self.target('one')])
        self.image('town/b', [other, self.target('two')])
        edits, holds = self.plan()[3:]
        self.assertFalse(edits)
        self.assertEqual(holds[0]['reason'], 'conflicting_definitions')

    def test_ambiguous_named_address_is_a_hold(self):
        self.named_caller()
        with (self.root / 'config/names.tsv').open('a') as handle:
            handle.write('0x80017000\tfunc_80017000\tone\tfixture\n')
        self.assertEqual(self.plan()[4][0]['reason'], 'ambiguous_named_address')

    def own_file_rows(self, *, caller_offset=0x1020, target_offset=0x1100):
        self.rows(dict(id='town/caller', func='func_80018000', container='town',
                       foff=caller_offset, size=16),
                  dict(id='town/target', func='func_80018100', true_name='two',
                       container='town', foff=target_offset, size=16))
        self.put('ledger/layout.jsonl', '\n'.join(json.dumps(r) for r in [
            dict(id='town/caller', path='src/town/caller.c'),
            dict(id='town/target', path='src/town/two.c')]) + '\n')
        self.put('config/link/town/a.json', json.dumps(dict(image='town/a', container='town',
                 foff='0x1000', size='0x200', vma='0x80016000', entries=[])))
        self.put('src/town/caller.c', '#include "common.h"\ns32 func_80016100();\n')

    def test_own_file_caller_and_target_use_the_containing_load_image(self):
        self.own_file_rows()
        edits, holds = self.plan()[3:]
        self.assertFalse(holds)
        self.assertEqual(edits[0].after, 's32 func_80016100(s32 x, s32 y);')
        self.assertIn(':two:own_file', edits[0].evidence)

    def test_own_file_target_outside_region_is_not_an_address_fallback(self):
        self.own_file_rows(target_offset=0x1300)
        edits, holds = self.plan()[3:]
        self.assertFalse(edits)
        self.assertIn('unresolved_image_binding:town/a', holds[0]['reason'])

    def test_own_file_caller_must_fit_inside_the_load_region(self):
        self.own_file_rows(caller_offset=0x11fc)
        edits, holds = self.plan()[3:]
        self.assertFalse(edits)
        self.assertEqual(holds[0]['reason'], 'no_loading_image_or_resident_owner')

    def test_partial_window_import_uses_its_containing_load_region(self):
        self.own_file_rows()
        self.put('config/link/town/partial.json', json.dumps(dict(image='town/partial', container='town',
                 foff='0x1000', size='0x80', vma='0x80016000', entries=[])))
        edits, holds = self.plan()[3:]
        self.assertFalse(holds)
        self.assertIn('within=town/a', edits[0].evidence)

    def test_partial_window_import_refuses_a_different_load_displacement(self):
        self.own_file_rows()
        self.put('config/link/town/partial.json', json.dumps(dict(image='town/partial', container='town',
                 foff='0x1000', size='0x80', vma='0x80015000', entries=[])))
        edits, holds = self.plan()[3:]
        self.assertFalse(edits)
        self.assertIn('unresolved_image_binding:town/partial', holds[0]['reason'])

    def test_registered_sibling_target_is_visible_in_an_overlapping_load_region(self):
        self.own_file_rows()
        self.put('config/link/town/b.json', json.dumps(dict(image='town/b', container='town',
                 foff='0x1080', size='0x200', vma='0x80016080', entries=[
                     dict(row='town/target', home='town/target', tu='src/town/two.c',
                          foff='0x1100', size=16, vma='0x80016100')])))
        edits, holds = self.plan()[3:]
        self.assertFalse(holds)
        self.assertEqual(edits[0].after, 's32 func_80016100(s32 x, s32 y);')

    def test_sibling_target_index_does_not_add_unrebound_caller_placements(self):
        self.own_file_rows()
        self.put('src/town/two.c', '#include "common.h"\ns32 func_80016120();\n'
                 's32 two(s32 x, s32 y) { return x+y; }\n')
        self.put('config/link/town/b.json', json.dumps(dict(image='town/b', container='town',
                 foff='0x1080', size='0x200', vma='0x80016080', entries=[
                     dict(row='town/target', home='town/target', tu='src/town/two.c',
                          foff='0x1100', size=16, vma='0x80016100',
                          bindings={'0x80016120': '0x80016100'})])))
        edits, holds = self.plan()[3:]
        self.assertFalse(holds)
        self.assertEqual(len(edits), 2)
        self.assertTrue(all('(s32 x, s32 y)' in edit.after for edit in edits))

    def test_same_image_binding_selects_right_bank(self):
        self.image('town/a', [self.caller({'0x80016000': '0x80017000'}),
                              self.target('one', '0x80017000')])
        self.image('town/b', [self.target('two')])
        edits, holds = self.plan()[3:]
        self.assertFalse(holds)
        self.assertEqual(edits[0].after, 's32 func_80016000(s32 x);')
        self.assertIn('80016000->80017000:one', edits[0].evidence)

    def test_never_falls_back_to_coincident_address_in_other_image(self):
        self.image('town/a', [self.caller()])
        self.image('town/b', [self.target('two')])
        edits, holds = self.plan()[3:]
        self.assertFalse(edits)
        self.assertIn('unresolved_image_binding:town/a', holds[0]['reason'])
        self.assertIn('owner_outside_loading_image', holds[0]['reason'])
        self.assertIn('town/b:src/town/two.c:two', holds[0]['evidence'])

    def test_two_same_signature_callees_at_one_target_remain_ambiguous(self):
        self.put('src/town/two.c', '#include "common.h"\ns32 two(s32 x) { return x; }\n')
        self.image('town/a', [self.caller(), self.target('one'), self.target('two')])
        edits, holds = self.plan()[3:]
        self.assertFalse(edits)
        self.assertEqual(holds[0]['reason'], 'ambiguous_image_callee:town/a')

    def test_every_placement_must_agree(self):
        self.image('town/a', [self.caller(), self.target('one')])
        self.image('town/b', [self.caller(), self.target('two')])
        edits, holds = self.plan()[3:]
        self.assertFalse(edits)
        self.assertEqual(holds[0]['reason'], 'placement_signature_conflict')

    def test_same_signature_different_bank_callees_stay_unprototyped(self):
        self.put('src/town/two.c', '#include "common.h"\ns32 two(s32 x) { return x; }\n')
        self.image('town/a', [self.caller(), self.target('one')])
        self.image('town/b', [self.caller(), self.target('two')])
        edits, holds = self.plan()[3:]
        self.assertFalse(edits)
        self.assertEqual(holds[0]['reason'], 'placement_callee_conflict')

    def test_header_same_signature_different_consumers_stay_unprototyped(self):
        self.put('src/town/two.c', '#include "common.h"\ns32 two(s32 x) { return x; }\n')
        self.put('include/alias.h', '#include "common.h"\ns32 func_80016000();\n')
        self.put('src/town/caller.c', '#include "alias.h"\n')
        self.put('src/town/other.c', '#include "alias.h"\n')
        other = dict(row='town/func_80400000', tu='src/town/other.c', vma='0x80018000')
        self.image('town/a', [self.caller(), self.target('one')])
        self.image('town/b', [other, self.target('two')])
        edits, holds = self.plan()[3:]
        self.assertFalse(edits)
        self.assertEqual(holds[0]['reason'], 'consumer_callee_conflict')

    def test_one_unresolved_placement_is_a_hold(self):
        self.image('town/a', [self.caller(), self.target('one')])
        self.image('town/b', [self.caller()])
        self.assertIn('unresolved_image_binding:town/b', self.plan()[4][0]['reason'])

    def test_numeric_resident_alias_uses_pinned_symbol_map(self):
        self.put('src/engine/util/real.c', '#include "common.h"\ns32 resident(s32 x) { return x; }\n')
        self.put('config/slus_006.14.symbols.txt', 'resident = 0x80016000;\n')
        edits, holds = self.plan()[3:]
        self.assertFalse(holds)
        self.assertIn('(s32 x)', edits[0].after)

    def test_numeric_resident_row_uses_actual_home_after_rename(self):
        self.put('src/engine/util/real.c', '#include "common.h"\ns32 renamed(s32 x) { return x; }\n')
        self.put('ledger/layout.jsonl', json.dumps(dict(id='slus/w_80016000', path='src/engine/util/real.c')) + '\n')
        self.rows(dict(id='slus/w_80016000', container='slus', func='func_80016000'))
        edits, holds = self.plan()[3:]
        self.assertFalse(holds)
        self.assertEqual(edits[0].after, 's32 func_80016000(s32 x);')

    def test_native_resident_row_resolves_each_enumerated_definition(self):
        self.put('src/engine/util/real.c', '#include "common.h"\n'
                 's32 first(s32 x) { return x; }\ns32 second(void) { return 0; }\n')
        self.put('config/names.tsv', '0x80016000\tfunc_80016000\tfirst\tfixture\n'
                 '0x80016040\tfunc_80016040\tsecond\tfixture\n')
        self.put('ledger/layout.jsonl', json.dumps(dict(id='slus/w_80016000',
                 path='src/engine/util/real.c')) + '\n')
        self.rows(dict(id='slus/w_80016000', container='slus', func=None,
                       defs=['func_80016000', 'func_80016040']))
        self.put('src/town/caller.c', '#include "common.h"\n'
                 's32 func_80016000();\ns32 func_80016040();\n')
        edits, holds = self.plan()[3:]
        self.assertFalse(holds)
        self.assertEqual([e.after for e in edits],
                         ['s32 func_80016000(s32 x);', 's32 func_80016040(void);'])

    def test_native_resident_entry_requires_its_registered_source_home(self):
        self.put('src/engine/util/real.c', '#include "common.h"\n'
                 's32 func_80016000(s32 x) { return x; }\n')
        self.put('ledger/layout.jsonl', json.dumps(dict(id='slus/w_80016000',
                 path='src/engine/util/other.c')) + '\n')
        self.rows(dict(id='slus/w_80016000', container='slus', func=None,
                       defs=['func_80016000']))
        edits, holds = self.plan()[3:]
        self.assertFalse(edits)
        self.assertEqual(holds[0]['reason'], 'no_loading_image_or_resident_owner')

    def test_production_binding_rules_rebind_same_image_homes_and_self_first(self):
        self.put('src/town/one.c', '#include "common.h"\ns32 func_80016000();\ns32 one(s32 x) { return x; }\n')
        def entry(row, home, source, offset, vma, bindings=None):
            return dict(row='town/' + row, home='town/' + home, tu=source,
                        foff=offset, vma=vma, size=4, bindings=bindings or {})
        home_entries = [entry('func_80100000', 'func_80100000', 'src/town/one.c', 0, 0x80016000),
                        entry('func_80300000', 'func_80300000', 'src/town/caller.c', 0x40, 0x80016040)]
        load_entries = [entry('func_80500000', 'func_80100000', 'src/town/one.c', 0x200, 0x80017000,
                              {'0x80016000': '0x80017080'}),
                        entry('func_80600000', 'func_80300000', 'src/town/caller.c', 0x240, 0x80017040)]
        for image, offset, vma, entries in [('town/home', 0, 0x80016000, home_entries),
                                             ('town/load', 0x200, 0x80017000, load_entries)]:
            doc = dict(schema='azure-clean.linklist.v0', image=image, container='town',
                       foff=offset, vma=vma, size=0x100, entries=entries)
            self.put('config/link/' + image + '.json', json.dumps(doc))
        edits, holds = self.plan()[3:]
        self.assertFalse(holds)
        self.assertEqual(len(edits), 2)
        self.assertTrue(all('(s32 x)' in e.after for e in edits))
        self.assertTrue(all('80016000->80017000:one' in e.evidence for e in edits))


if __name__ == '__main__':
    unittest.main()
