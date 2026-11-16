#!/usr/bin/env python3
"""Regression tests for tools/typing/clone_transplant.py and tools/lint/clone_sources.py
(python3 -m unittest tools.typing.test_clone_transplant -v).

The masked compare, the symbol map and the text rewrite run on fixtures; the compile and identity stages are the
existing tools' (layout_compile_identity.capture_one, tu_identity) and are not repeated here."""
from pathlib import Path
import sys
import unittest

HERE = Path(__file__).resolve().parent
sys.path[:0] = [str(HERE), str(HERE.parent), str(HERE.parents[1]), str(HERE.parent / 'lint')]
import clone_transplant as T  # noqa: E402
import clone_sources as S  # noqa: E402
import clone_names as N  # noqa: E402

LUI, ADDIU, JAL, NOP = 0x3C020000, 0x24420000, 0x0C000000, 0


def view(words, relocs):
    return list(words), sorted(relocs)


class MaskedCompare(unittest.TestCase):
    def test_relocated_fields_are_masked(self):
        a = view([LUI | 0x8016, ADDIU | 0x26A0, JAL | 0x100, NOP],
                 [(0, 'HI16', ('sym', 'D_801626A0'), 0x801626A0), (4, 'LO16', ('sym', 'D_801626A0'), 0x26A0),
                  (8, '26', ('sym', 'func_80000400'), 0)])
        b = view([LUI | 0x8015, ADDIU | 0xC6A0, JAL | 0x100, NOP],
                 [(0, 'HI16', ('sym', 'D_8015C6A0'), 0x8015C6A0), (4, 'LO16', ('sym', 'D_8015C6A0'), -0x3960),
                  (8, '26', ('sym', 'func_80000400'), 0)])
        self.assertEqual(T.masked_compare(a, b), [])

    def test_unrelocated_word_or_layout_differs(self):
        a = view([LUI | 0x8016, NOP], [(0, 'HI16', ('sym', 'D_1'), 0)])
        b = view([LUI | 0x8016, 0x00000001], [(0, 'HI16', ('sym', 'D_2'), 0)])
        self.assertTrue(T.masked_compare(a, b))
        c = view([LUI | 0x8016, NOP], [(4, 'LO16', ('sym', 'D_1'), 0)])
        self.assertEqual(T.masked_compare(a, c), ['relocation layout differs'])
        self.assertTrue(T.masked_compare(a, view([LUI], [(0, 'HI16', ('sym', 'D_1'), 0)])))

    def test_register_field_is_not_masked(self):
        a = view([ADDIU | 0x10], [(0, 'LO16', ('sym', 'D_1'), 0x10)])
        b = view([(ADDIU ^ 0x00010000) | 0x10], [(0, 'LO16', ('sym', 'D_2'), 0x10)])
        self.assertTrue(T.masked_compare(a, b))


class SymbolMap(unittest.TestCase):
    def rel(self, *targets):
        return view([NOP] * len(targets), [(4 * k, 'HI16', t, a) for k, (t, a) in enumerate(targets)])

    def test_map_pairs_named_targets_and_own_sections(self):
        a = self.rel((('sym', 'D_801626A0'), 0), (('sec', '.text.func_80160000'), 0), (('sym', 'rand'), 0),
                     (('sec', '.rodata'), 0x40))
        b = self.rel((('sym', 'D_8015C6A0'), 0), (('sec', '.text.func_8015A000'), 0), (('sym', 'rand'), 0),
                     (('sec', '.rodata'), 0x80))
        m = T.symbol_map(a, b, 'func_80160000', 'func_8015A000')
        self.assertEqual(m, {'func_80160000': 'func_8015A000', 'D_801626A0': 'D_8015C6A0', 'rand': 'rand'})

    def test_not_one_to_one_refuses(self):
        a = self.rel((('sym', 'D_1'), 0), (('sym', 'D_1'), 0))
        b = self.rel((('sym', 'D_2'), 0), (('sym', 'D_3'), 0))
        with self.assertRaises(ValueError):
            T.symbol_map(a, b, 'func_A', 'func_B')
        c = self.rel((('sym', 'D_1'), 0), (('sym', 'D_2'), 0))
        d = self.rel((('sym', 'D_3'), 0), (('sym', 'D_3'), 0))
        with self.assertRaises(ValueError):
            T.symbol_map(c, d, 'func_A', 'func_B')

    def test_addend_mismatch_static_data_and_kind_mismatch_refuse(self):
        with self.assertRaises(ValueError):
            T.symbol_map(self.rel((('sym', 'D_1'), 4)), self.rel((('sym', 'D_2'), 8)), 'func_A', 'func_B')
        with self.assertRaises(ValueError):
            T.symbol_map(self.rel((('sec', '.bss'), 0)), self.rel((('sec', '.bss'), 0)), 'func_A', 'func_B')
        with self.assertRaises(ValueError):
            T.symbol_map(self.rel((('sym', 'D_1'), 0)), self.rel((('sec', '.rodata'), 0)), 'func_A', 'func_B')


DONOR = """#include "common.h"
#include "dungeon/actor.h"

typedef ActorActionHandler Callback;

extern s32 D_801659DC;
extern Callback D_801686A0[];
extern s32 unused_in_donor;

/* donor comment */
void run_callbacks(ActorRecord *body, ObjectPosition *motion)
{
    Callback entry = body->unk_8C.handler;
    /* reads D_801686A0 */
    if (entry == (Callback)&D_801659DC) {
        entry(body, motion, 0, body);
        return;
    }
    D_801686A0[body->action_id](body, motion, 0, body);
    body->D_801659DC = 0;
}
"""

RECIPIENT = """#include "common.h"

typedef void (*Callback)(void *, void *, void *, void *);

typedef struct S_8015F3A8_2 {
    u8 pad_00[0x1C];
    s32 unk_1C;
} S_8015F3A8_2;   /* base in update_copy */

extern s32 D_8015F9DC;
extern Callback D_801626A0[];

/* recipient comment */
void update_copy(void *entity, ObjectPosition *motion)
{
    S_8015F3A8_2 *base = entity;
    Callback entry = *(Callback *)((u8 *)entity + 0x8C);
    if (entry == (Callback)&D_8015F9DC) {
        entry(entity, motion, 0, entity);
        return;
    }
    D_801626A0[*((u8 *)entity + 0x6C)](entity, motion, 0, entity);
    base->unk_1C = 0;
}
"""

SYMMAP = {'func_80165000': 'func_8015F000', 'D_801659DC': 'D_8015F9DC', 'D_801686A0': 'D_801626A0'}
TABLE = {'run_callbacks': 'func_80165000', 'update_copy': 'func_8015F000'}


class Rewrite(unittest.TestCase):
    def test_rename_whole_identifiers_never_members(self):
        text = 'x = D_801626A0 + D_801626A04; y->D_801626A0 = s.D_801626A0; /* D_801626A0 */'
        self.assertEqual(T.rename(text, {'D_801626A0': 'D_8015C6A0'}),
                         'x = D_8015C6A0 + D_801626A04; y->D_801626A0 = s.D_801626A0; /* D_8015C6A0 */')

    def test_transplant_maps_symbols_carries_and_drops_declarations(self):
        new, mapping = T.transplant(DONOR, 'run_callbacks', RECIPIENT, 'update_copy', SYMMAP, TABLE)
        self.assertEqual(mapping['run_callbacks'], 'update_copy')
        self.assertEqual(mapping['D_801686A0'], 'D_801626A0')
        self.assertIn('void update_copy(ActorRecord *body, ObjectPosition *motion)', new)
        self.assertIn('D_801626A0[body->action_id]', new)
        self.assertIn('/* reads D_801626A0 */', new)
        self.assertIn('body->D_801659DC = 0;', new)          # a member keeps its name
        self.assertIn('/* recipient comment */', new)         # the recipient keeps its own comment
        self.assertNotIn('S_8015F3A8_2', new)                 # the view served only the old definition
        self.assertNotIn('unused_in_donor', new)              # an unused donor declaration is not carried
        self.assertIn('extern s32 D_8015F9DC;', new)

    def test_conflicting_declaration_with_other_users_refuses(self):
        other = RECIPIENT + '\nvoid other(void) { Callback f = 0; f(0, 0, 0, 0); }\n'
        with self.assertRaises(T.Refused):
            T.transplant(DONOR, 'run_callbacks', other, 'update_copy', SYMMAP, TABLE)

    def test_conflicting_declaration_used_only_by_old_definition_is_replaced(self):
        new, _ = T.transplant(DONOR, 'run_callbacks', RECIPIENT, 'update_copy', SYMMAP, TABLE)
        self.assertIn('typedef ActorActionHandler Callback;', new)
        self.assertNotIn('typedef void (*Callback)', new)

    def test_storage_reference_refuses(self):
        donor = DONOR.replace('extern s32 D_801659DC;', 's32 D_801659DC = 3;')
        with self.assertRaises(T.Refused):
            T.transplant(donor, 'run_callbacks', RECIPIENT, 'update_copy', SYMMAP, TABLE)

    def test_unit_items(self):
        unit = T.Unit(RECIPIENT)
        kinds = {frozenset(it['names']): it['kind'] for it in unit.items}
        self.assertEqual(kinds[frozenset({'Callback'})], 'typedef')
        self.assertEqual(kinds[frozenset({'S_8015F3A8_2', 'tag:S_8015F3A8_2'})], 'typedef')
        self.assertEqual(kinds[frozenset({'D_801626A0'})], 'declaration')
        self.assertEqual(kinds[frozenset({'update_copy'})], 'definition')
        self.assertEqual(T.Unit('static s32 count = 0;\n').items[0]['kind'], 'storage')
        self.assertEqual(T.Unit('s32 f(s32 a);\n').items[0]['kind'], 'declaration')


class Signatures(unittest.TestCase):
    def test_parameter_names_do_not_change_a_signature(self):
        a = 'void f(ActorRecord *body, void *x, unsigned int n) { }'
        b = 'void f(ActorRecord *self, void *y, unsigned int count)\n{\n}'
        self.assertEqual(T.signature(a, 'f'), T.signature(b, 'f'))
        self.assertNotEqual(T.signature(a, 'f'), T.signature(a.replace('void *x', 'ObjectPosition *x'), 'f'))
        self.assertEqual(T.definition_head(b, 'f'), 'void f(ActorRecord *self, void *y, unsigned int count)')

    def test_missing_includes_added_once(self):
        donor = '#include "a.h"\n#include "b.h"\n#include "a.h"\n#include "c.h"\n#include "b.h"\nint x;\n'
        text = '#include "a.h"\nvoid f(void) {\n}\n'
        out = T.add_missing_includes(donor, text)
        self.assertEqual(out, '#include "a.h"\n#include "b.h"\n#include "c.h"\nvoid f(void) {\n}\n')

    def test_added_includes_kept_only_when_needed(self):
        without = '#include "a.h"\nvoid f(void) {\n}\n'
        added = ['#include "b.h"\n', '#include "c.h"\n', '#include "d.h"\n', '#include "e.h"\n']
        with_includes = '#include "a.h"\n' + ''.join(added) + 'void f(void) {\n}\n'
        # the unit stays identical only while c.h is included; a.h was the copy's own and is never dropped
        out = T.drop_unneeded_includes(without, with_includes, lambda text: '"c.h"' in text and '"a.h"' in text)
        self.assertEqual(out, '#include "a.h"\n#include "c.h"\nvoid f(void) {\n}\n')

    def test_signature_change_refused_when_prototype_header_is_held(self):
        original = 'void f(void *body) {\n}\n'
        new = 'void f(ActorRecord *body) {\n}\n'
        m = dict(name='f', file='src/a.c')
        sites, held = T.prototype_sites, set(T._SKIP)
        try:
            T.prototype_sites = lambda root, name, own: [('include/a.h', 0, 10)]
            T._SKIP.clear()
            T._SKIP.add('include/a.h')
            with self.assertRaises(T.Refused) as ctx:
                T.check_prototypes('.', m, original, new, {})
            self.assertIn('prototype_header_held', str(ctx.exception))
            T.check_prototypes('.', m, original, original, {})  # no signature change: nothing to refuse
        finally:
            T.prototype_sites = sites
            T._SKIP.clear()
            T._SKIP.update(held)


class ModuleTags(unittest.TestCase):
    def test_module_view_spellings_follow_the_copy_module(self):
        self.assertEqual(T.module_tag('src/dungeon/modules/ovl_cb9000.c'), 'CB9000')
        self.assertIsNone(T.module_tag('src/dungeon/monster/block/block.c'))
        text = 'CL_CB9000_80174B3C_S_0 *s; s->CL_CB9000_80174B3C_handler = 0; XCL_CB9000_y;'
        self.assertEqual(T.retag(text, 'CB9000', 'CCB000'),
                         'CL_CCB000_80174B3C_S_0 *s; s->CL_CCB000_80174B3C_handler = 0; XCL_CB9000_y;')
        d = S.definition_tokens('void f(CL_CB9000_S *s) { s->CL_CB9000_h = 0; }', 'f')
        c = S.definition_tokens('void g(CL_CCB000_S *s) { s->CL_CCB000_h = 0; }', 'g')
        self.assertEqual(S.compare(d, c, 'f', 'g', {}, {}, ('CB9000', 'CCB000')), [])
        self.assertTrue(S.compare(d, c, 'f', 'g', {}, {}))

    def test_text_score_prefers_fewer_casts_then_fewer_fences(self):
        plain = 'void f(ActorRecord *a) { a->x = 0; }\n'
        cast = 'void f(void *a) { ((ActorRecord *)a)->x = 0; }\n'
        fence = 'void f(ActorRecord *a) { do { a->x = 0; } while (0); }\n'
        score = [T.text_score('x.c', t, 'f')[2] for t in (plain, cast, fence)]
        self.assertLess(score[0], score[1])
        self.assertLess(score[0], score[2])
        self.assertLess(score[2], score[1])


class LowerTextRefused(unittest.TestCase):
    """A donor whose text reads generated members, raw offsets or casts where the copy names the record's members
    (the AC160 update_block_hop_slot_f, draw_shaded_point_chain and grineut facing copies) is refused."""

    def test_named_member_replaced_by_generated_member_or_offset_refuses(self):
        copy = ('void f(ActorRecord *a, SpriteFrameState *p) {\n    s16 old;\n    a->action_phase = 1;\n'
                '    old = a->pending_turn_updates;\n    if (old != a->pending_turn_updates) a->unk_9D = 0;\n}\n')
        donor = ('void f(CL_CB9000_S_0 *a, SpriteFrameState *p) {\n    s16 old;\n    a->unk_9B = 1;\n'
                 '    old = (s8)(*((u8 *)a + 0x6D));\n    if (old != a->pending_turn_updates) a->unk_9D = 0;\n}\n')
        lost = T.lost_members(copy, donor, 'f')
        self.assertIn(('action_phase', 'unk_9B'), lost)
        self.assertIn(('pending_turn_updates', '( u8 * )'), lost)
        glob = ('s32 g(void) {\n    GpuContext *ctx = g_game_work.draw_buffer;\n'
                '    ((GpuLinkTag *)&ctx->tag)->len = 2;\n    return 0;\n}\n')
        raw = ('s32 g(void) {\n    GpuContext **state = (GpuContext **)&g_game_work;\n    GpuContext *ctx = *state;\n'
               '    ((u8 *)ctx)[3] = 2;\n    return 0;\n}\n')
        self.assertEqual({m for m, _ in T.lost_members(glob, raw, 'g')}, {'draw_buffer', 'len', 'tag'})

    def test_member_spelled_another_named_way_or_view_renamed_is_kept(self):
        copy = 'void f(ActorRecord *a) {\n    a->flags = a->flags & 0x7F;\n    a->unk_8C.handler = h;\n}\n'
        donor = 'void f(ActorRecord *body) {\n    body->flags &= 0x7F;\n    body->unk_8C.address = &h;\n}\n'
        self.assertEqual(T.lost_members(copy, donor, 'f'), [])
        # members of the copy's own address-named or file-local view, replaced by a shared record's names
        view = ('typedef struct Scratch { u8 *current; } Scratch;\n'
                's32 g(R10_8017092C_Packet *p) {\n    Scratch *s = (Scratch *)0x1F800000;\n'
                '    s->current = (u8 *)p;\n    p->data.link = 0;\n    return 0;\n}\n')
        shared = ('s32 g(TILE_1 *p) {\n    PointTileScratch *s = (PointTileScratch *)0x1F800000;\n'
                  '    s->packet_cursor = p;\n    *(u32 *)&p->r0 = 0;\n    return 0;\n}\n')
        self.assertEqual(T.lost_members(view, shared, 'g'), [])

    def test_typed_parameter_swapped_for_generated_layout_refuses(self):
        copy = 'void f(ActorRecord *action, ObjectPosition *motion, void *spare) { }\n'
        donor = 'void f(CL_CB9000_80172458_S_80172458_0 *action, ObjectPosition *motion, ActorRecord *spare) { }\n'
        self.assertEqual(T.weakened_parameters(copy, donor, 'f'),
                         [(0, 'ActorRecord *', 'CL_CB9000_80172458_S_80172458_0 *')])
        self.assertEqual(T.weakened_parameters(copy, copy.replace('void *spare', 'ActorRecord *spare'), 'f'), [])
        self.assertEqual(T.weakened_parameters(copy, copy.replace('action', 'body'), 'f'), [])


class Ledger(unittest.TestCase):
    def test_families_recorded_under_two_donors_merge_with_composed_maps(self):
        rows = {'r/A': dict(donor='func_A', row='r/A', copies=[
                    dict(address='func_B', row='r/B', map={'func_A': 'func_B', 'D_1': 'D_2'}),
                    dict(address='func_C', row='r/C', map={'func_A': 'func_C', 'D_1': 'D_3'})]),
                'r/B': dict(donor='func_B', row='r/B', copies=[
                    dict(address='func_E', row='r/E', map={'func_B': 'func_E', 'D_2': 'D_5'})])}
        out = T.merge_families(rows)
        self.assertEqual(list(out), ['r/A'])
        maps = {c['row']: c['map'] for c in out['r/A']['copies']}
        self.assertEqual(maps['r/E'], {'func_A': 'func_E', 'D_1': 'D_5'})
        self.assertEqual(maps['r/C'], {'func_A': 'func_C', 'D_1': 'D_3'})


class Names(unittest.TestCase):
    def test_rename_word_keeps_members_and_longer_names(self):
        text = 'a = slot_c; b->slot_c = slot_c_x; slot_c(1);'
        self.assertEqual(N.rename_word(text, 'slot_c', 'canon'), 'a = canon; b->slot_c = slot_c_x; canon(1);')

    def test_names_row_records_the_copy(self):
        tsv = ('0x80172944\tfunc_80172944\tfinish_linked_motion_and_trap\tAdvances linked motion.\n'
               '0x8015A944\tfunc_8015A944\tfinish_block_linked_motion_slot_c\tsrc/dungeon/modules/ovl_ccb000.c; '
               'runs linked motion\n')
        out = N.names_row(tsv, 'func_8015A944', 'finish_block_linked_motion_slot_c', 'finish_linked_motion_and_trap',
                          'func_80172944', 25, 'src/dungeon/monster/block/block.c')
        row = out.splitlines()[1].split('\t')
        self.assertEqual(row[2], 'finish_linked_motion_and_trap')
        self.assertTrue(row[3].startswith('copy_of=0x80172944; src/dungeon/modules/ovl_ccb000.c: runs linked motion'))
        self.assertIn('(renamed from finish_block_linked_motion_slot_c)', row[3])
        with self.assertRaises(ValueError):
            N.names_row(tsv, 'func_8015A944', 'other_name', 'x', 'func_80172944', 25, 'b.c')


class Drift(unittest.TestCase):
    def test_copy_equal_under_map_and_drift_detected(self):
        new, _ = T.transplant(DONOR, 'run_callbacks', RECIPIENT, 'update_copy', SYMMAP, TABLE)
        d = S.definition_tokens(DONOR, 'run_callbacks')
        c = S.definition_tokens(new, 'update_copy')
        self.assertEqual(S.compare(d, c, 'run_callbacks', 'update_copy', SYMMAP, TABLE), [])
        drifted = new.replace('return;', 'body->flags = 1;\n        return;')
        self.assertTrue(S.compare(d, S.definition_tokens(drifted, 'update_copy'), 'run_callbacks', 'update_copy',
                                  SYMMAP, TABLE))
        renamed = new.replace('D_801626A0[', 'D_80999999[')
        self.assertTrue(S.compare(d, S.definition_tokens(renamed, 'update_copy'), 'run_callbacks', 'update_copy',
                                  SYMMAP, TABLE))

    def test_names_table_spellings_agree(self):
        # the copy may spell a symbol by its config/names.tsv name; the donor by its address
        table = dict(TABLE, death_frames='D_801626A0')
        new, _ = T.transplant(DONOR, 'run_callbacks', RECIPIENT, 'update_copy', SYMMAP, TABLE)
        spelled = new.replace('D_801626A0[body', 'death_frames[body')
        d = S.definition_tokens(DONOR, 'run_callbacks')
        self.assertEqual(S.compare(d, S.definition_tokens(spelled, 'update_copy'), 'run_callbacks', 'update_copy',
                                   SYMMAP, table), [])


if __name__ == '__main__':
    unittest.main()
