"""Tests for caller_types.py: a small clang-parsed tree reconstructing the reviewed cases.

Run: python3 -m unittest tools/typing/test_caller_types.py   (needs clang; skipped without it)
"""
import shutil
import sys
import tempfile
import textwrap
import unittest
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import caller_types as CT  # noqa: E402

COMMON = '''
typedef signed char s8; typedef unsigned char u8; typedef short s16; typedef unsigned short u16;
typedef int s32; typedef unsigned int u32;
'''
OBJECT_NODE = '''
struct ObjectPosition; struct SpriteFrameState;
typedef struct ObjectNodeHeader {
    struct ObjectNodeHeader *next; struct ObjectNodeHeader **pprev;
    struct ObjectPosition *position; struct SpriteFrameState *sprite;
    void *update_callback; struct ObjectNodeHeader *draw_prev; struct ObjectNodeHeader *chain_next;
    unsigned short draw_slot; unsigned short flags;
} ObjectNodeHeader;
#define NODE_BODY(node) ((void *)((ObjectNodeHeader *)(node) + 1))
#define NODE_HEADER(body) ((ObjectNodeHeader *)(body) - 1)
void *allocate_flagged_object_node(int flags);
s32 register_node(void *objectPtr, void (*callback)(void));
'''
ENTITY = '''
typedef union Fixed1616 { int v; struct { unsigned short frac; short i; } w; } Fixed1616;
typedef struct ObjectPosition {
    Fixed1616 x; Fixed1616 y; Fixed1616 z; int velocity_x; int velocity_y; int velocity_z;
} ObjectPosition;
typedef struct ActorRecord {
    unsigned char unk_00[0x1C];
    int flags1C;                        /* 0x1C */
    unsigned char pad_20[0xA];
    short facing;                       /* 0x2A */
    unsigned char unk_2C[0x6A];
    short action_timer;                 /* 0x96 */
    unsigned short action_state_flags;  /* 0x98 */
    unsigned char unk_9A;
    unsigned char action_phase;         /* 0x9B */
    unsigned char unk_9C[0x20];
} ActorRecord;                          /* 0xBC */
'''
SPRITE = '''
typedef struct SpriteFrameState {
    void *unk_00; signed char unk_04; unsigned char frame_ticks; short depth_bias; void *source;
    int color; unsigned short tpage_abr; unsigned short clut; unsigned short flags;
} SpriteFrameState;
'''
# A record whose shape matches the negative view exactly, while callers pass ActorRecord.
DECOY = '''
typedef struct WaveTimer {
    unsigned char pad_00[0x1C];
    short period;                       /* 0x1C */
    unsigned char pad_1E[0xA];
    int phase;                          /* 0x28 */
} WaveTimer;
'''
HEADS = '#include "common.h"\n#include "shared/entity.h"\n#include "shared/sprite_frame_state.h"\n'

FILES = {
    'include/common.h': COMMON,
    'include/shared/object_node.h': OBJECT_NODE,
    'include/shared/entity.h': ENTITY,
    'include/shared/sprite_frame_state.h': SPRITE,
    'include/shared/wave_timer.h': DECOY,
    # AC131 review B1 as it stood before the fix: the 4th parameter is a per-function view {+0x1C s32,
    # +0x2A s16} while the only caller passes the ActorRecord it also passes (through a void * local) first.
    'src/ghosh/update_boss_timed_animation.c': HEADS + '''
typedef struct S_801740F8_2 { u8 pad_00[0x1C]; s32 unk_1C; u8 pad_20[0xA]; s16 unk_2A; } S_801740F8_2;
void update_boss_timed_animation(ActorRecord *actor, ObjectPosition *transform, SpriteFrameState *animation,
                                 struct S_801740F8_2 *motion)
{
    if (motion->unk_2A + transform->x.v > 3) {
        motion->unk_1C &= 0xF7FFFFFF;
    }
    animation->flags |= 1;
    actor->action_phase++;
}
''',
    'src/ghosh/advance_boss_command_stream.c': HEADS + '''
struct S_801740F8_2;
void update_boss_timed_animation(ActorRecord *, ObjectPosition *, SpriteFrameState *, struct S_801740F8_2 *);
s32 advance_boss_command_stream(void *object_arg, void *context_arg, void *entity_arg)
{
    void *call_obj;
    ActorRecord *obj;
    SpriteFrameState *entity;

    call_obj = object_arg;
    entity = entity_arg;
    obj = object_arg;
    obj->facing = 3;
    update_boss_timed_animation(call_obj, context_arg, entity, obj);
    return 0;
}
''',
    'src/ghosh/update_boss_actor_action.c': HEADS + '''
s32 advance_boss_command_stream(void *object_arg, void *context_arg, void *entity_arg);
void update_boss_actor_action(ActorRecord *actor, ObjectPosition *context, SpriteFrameState *sprite)
{
    advance_boss_command_stream(actor, context, sprite);
}
''',
    # Weadog/kewne: action handlers reached only through data (no C reference); the views are ActorRecord
    # slices (+0x96 action_timer, +0x98 action_state_flags, +0x9B action_phase; arg3 +0x1C/+0x2A).
    'src/weadog/advance_timed_hop_and_recover.c': HEADS + '''
typedef struct S_801670E0_0 { u8 pad_00[0x96]; u16 unk_96; u16 unk_98; u8 pad_9A[1]; u8 unk_9B; } S_801670E0_0;
typedef struct S_801670E0_1 { u8 pad_00[0x1C]; u32 unk_1C; u8 pad_20[0xA]; s16 unk_2A; } S_801670E0_1;
void advance_timed_hop_and_recover(S_801670E0_0 *motion_state, void *motion, SpriteFrameState *sprite, void *actor)
{
    if (motion_state->unk_96 != 0) {
        motion_state->unk_98 |= 8;
        motion_state->unk_9B++;
    }
    ((S_801670E0_1 *)actor)->unk_1C |= 0x10;
    ((S_801670E0_1 *)actor)->unk_2A = 0;
}
''',
    # Negative (B1 pattern): the shape fits WaveTimer exactly, but the callers pass ActorRecord, where
    # +0x1C is a word and +0x28 straddles facing.  No fold may be proposed.
    'src/neg/shape_only.c': HEADS + '''
#include "shared/wave_timer.h"
void reset_wave_timer(WaveTimer *timer)
{
    timer->phase = timer->period;
}
typedef struct S_80100000_1 { u8 pad_00[0x1C]; s16 unk_1C; u8 pad_1E[0xA]; s32 unk_28; } S_80100000_1;
void tick_shape_only(S_80100000_1 *state)
{
    state->unk_28 += state->unk_1C;
}
void call_shape_only(ActorRecord *actor)
{
    tick_shape_only((S_80100000_1 *)actor);
}
''',
    # Node callbacks: installed at the header update slot (direct and through an installer parameter);
    # dispatch passes (body, ObjectPosition *, SpriteFrameState *).
    'src/fx/create_fx.c': HEADS + '''
#include "shared/object_node.h"
typedef struct MotionView { s32 x; s32 y; s32 z; } MotionView;
void update_fx(void *body, MotionView *motion, SpriteFrameState *sprite)
{
    motion->x += motion->z;
    sprite->flags = 0;
}
void update_other(void *body, u8 *motion, SpriteFrameState *sprite)
{
    *(s32 *)(motion + 8) = 0;
    *(s32 *)(motion + 0xC) = 1;
}
ObjectNodeHeader *spawn_node(void *callback)
{
    ObjectNodeHeader *node = allocate_flagged_object_node(0x157);
    node->update_callback = callback;
    return node;
}
void create_fx(void)
{
    ObjectNodeHeader *node = allocate_flagged_object_node(0x157);
    node->update_callback = update_fx;
    spawn_node(update_other);
}
''',
    # The declaration names the shared record; the caller holds a module-local named record (a narrower
    # view of the same actor).  Retyping the shared declaration to the caller's view is the wrong direction.
    'include/dungeon/golem_work.h': '''
typedef struct GolemActionWork { unsigned char pad_00[0x8C]; int unk_8C; unsigned char pad_90[0xB]; unsigned char unk_9B; } GolemActionWork;
''',
    'src/golem/attempt_action.c': HEADS + '''
#include "dungeon/golem_work.h"
s32 attempt_actor_action(ActorRecord *action_out)
{
    return action_out->action_phase;
}
void update_golem(GolemActionWork *actor)
{
    attempt_actor_action(actor);
}
''',
    # A view word read where the record declares a pointer (same width): matched, noted as ptr/int.
    # TileRef duplicates SpriteFrameState's flags in another shared header: a shared-record swap.
    'include/shared/tile_ref.h': '''
typedef struct TileRef { unsigned char pad_00[0x14]; unsigned short flags; } TileRef;
''',
    'src/town/countdown.c': HEADS + '''
#include "shared/tile_ref.h"
typedef struct S_80300000_2 { u8 pad_00[0x8]; s32 unk_08; u8 pad_0C[0x8]; u16 unk_14; } S_80300000_2;
void set_countdown(S_80300000_2 *state)
{
    state->unk_08 = 14;
    state->unk_14 = 0;
}
void clear_tile_flags(TileRef *tile)
{
    tile->flags = 0;
}
void start_countdown(SpriteFrameState *sprite)
{
    set_countdown(sprite);
    clear_tile_flags(sprite);
}
''',
    # A typed slot whose parameter types differ from the definition (AC130 review B1 class).
    'src/fx/slot_entry.c': HEADS + '''
typedef struct MotionView2 { s32 x; s32 y; } MotionView2;
void follow_entry(u8 *body, MotionView2 *motion, SpriteFrameState *sprite)
{
    motion->x = motion->y;
}
void (*const fx_entry)(u8 *, u8 *, SpriteFrameState *) = follow_entry;
''',
}


def have_clang():
    return shutil.which(CT.os.environ.get('FIELD_CENSUS_CLANG', 'clang')) is not None


@unittest.skipUnless(have_clang(), 'clang not installed')
class FixtureTree(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.tmp = tempfile.TemporaryDirectory()
        root = Path(cls.tmp.name)
        for rel, text in FILES.items():
            p = root / rel
            p.parent.mkdir(parents=True, exist_ok=True)
            p.write_text(textwrap.dedent(text))
        tus = sorted(str(p.relative_to(root)) for p in (root / 'src').rglob('*.c'))
        flows, errors = CT.extract_flows(root, tus)
        assert not errors, errors
        cls.model, cls.rows = CT.analyze(flows)

    @classmethod
    def tearDownClass(cls):
        cls.tmp.cleanup()

    def row(self, function, param):
        got = [r for r in self.rows if r['function'] == function and r['param'] == param]
        return got[0] if got else None

    def test_ghosh_prefix_view_is_class_a_actor_record(self):
        r = self.row('update_boss_timed_animation', 3)
        self.assertIsNotNone(r)
        self.assertEqual(r['cls'], 'A')
        self.assertEqual(r['proposed'], 'ActorRecord *')
        self.assertEqual(r['kind'], 'generated')
        self.assertEqual(r['verdict'], 'full')
        paths = sorted(p for _a, p in r['sm']['fields'])
        self.assertEqual(paths, ['facing', 'flags1C'])
        text = textwrap.dedent(FILES['src/ghosh/advance_boss_command_stream.c']).splitlines()
        line = 1 + next(i for i, x in enumerate(text) if x.strip().startswith('update_boss_timed_animation('))
        self.assertEqual(r['items'][0]['site'], 'src/ghosh/advance_boss_command_stream.c:%d' % line)

    def test_void_entry_param_through_alias_locals(self):
        r = self.row('advance_boss_command_stream', 0)
        self.assertEqual((r['cls'], r['proposed']), ('A', 'ActorRecord *'))
        self.assertIn((0x2A, 2, 's'), [a[:3] for a in r['accesses']])
        # forwarded only: identity agrees but no field is observed
        r1 = self.row('advance_boss_command_stream', 1)
        self.assertEqual((r1['cls'], r1['proposed']), ('B', 'ObjectPosition *'))
        self.assertIn('no_fields_observed', r1['reason'])

    def test_transitive_param_resolves_and_matches_declaration(self):
        # arg 0 of update_boss_timed_animation is call_obj (void *) = the caller's void * parameter, whose
        # caller passes ActorRecord: consistent with the declaration, so no row.
        self.assertIsNone(self.row('update_boss_timed_animation', 0))

    def test_weadog_kewne_slices_flagged_without_callers(self):
        r = self.row('advance_timed_hop_and_recover', 0)
        self.assertEqual(r['cls'], 'C')
        self.assertIn('no_evidence', r['reason'])
        self.assertEqual(r['proposed'], '')
        self.assertEqual(r['shape'][0], 'ActorRecord')
        r3 = self.row('advance_timed_hop_and_recover', 3)
        self.assertEqual(r3['kind'], 'void')
        self.assertEqual(sorted(a[:2] for a in r3['accesses']), [(0x1C, 4), (0x2A, 2)])
        self.assertIn('ActorRecord', r3['shape'])
        self.assertNotIn('WaveTimer', r3['shape'])

    def test_shape_only_match_never_proposed(self):
        r = self.row('tick_shape_only', 0)
        self.assertEqual(r['cls'], 'C')
        self.assertEqual(r['proposed'], '')
        self.assertIn('slice_conflict', r['reason'])
        self.assertIn('shape_only_conflict', r['reason'])
        self.assertIn('WaveTimer', r['shape'])
        self.assertEqual(r['items'][0]['label'], 'ActorRecord')

    def test_node_callbacks_get_dispatch_convention(self):
        r = self.row('update_fx', 1)
        self.assertEqual((r['cls'], r['proposed']), ('A', 'ObjectPosition *'))
        self.assertEqual(r['kinds'], {'dispatch': 1})
        body = self.row('update_fx', 0)
        self.assertEqual(body['cls'], 'C')
        self.assertEqual(body['items'][0]['how'], 'dispatch_body')
        other = self.row('update_other', 1)       # installed through spawn_node's parameter
        self.assertEqual((other['cls'], other['proposed']), ('A', 'ObjectPosition *'))
        self.assertEqual(sorted(a[:2] for a in other['accesses']), [(8, 4), (0xC, 4)])

    def test_typed_slot_mismatch_is_noted_not_counted(self):
        r = self.row('follow_entry', 1)
        self.assertEqual(r['cls'], 'C')
        self.assertTrue(r['slot_notes'] and r['slot_notes'][0].endswith('slot u8 *'), r['slot_notes'])


    def test_wrong_direction_is_not_proposed(self):
        r = self.row('attempt_actor_action', 0)
        self.assertEqual(r['cls'], 'C')
        self.assertEqual(r['proposed'], '')
        self.assertIn('callers_hold_non_shared_record', r['reason'])

    def test_pointer_read_as_integer_is_noted_not_conflict(self):
        r = self.row('set_countdown', 0)
        self.assertEqual((r['cls'], r['proposed']), ('A', 'SpriteFrameState *'))
        self.assertEqual(r['sm']['conflicts'], [])
        self.assertEqual([(a[0], p, k) for a, p, k in r['sm']['sign']], [(8, 'source', 'p')])

    def test_shared_record_swap_is_tagged(self):
        r = self.row('clear_tile_flags', 0)
        self.assertEqual((r['cls'], r['proposed']), ('A', 'SpriteFrameState *'))
        self.assertIn('shared_record_swap', r['reason'])


class SliceMatch(unittest.TestCase):
    def setUp(self):
        self.records = {
            'Rec': {'size': 12, 'kind': 'struct', 'file': 'include/shared/r.h', 'fields': [
                ['a', 0, 'int', False], ['b', 4, 'short', False], ['c', 6, 'unsigned short', False],
                ['pad_08', 8, 'unsigned char[4]', False]]},
        }
        self.T = CT.Types({}, self.records)

    def test_full_partial_conflict_and_sign(self):
        m = CT.slice_match([(0, 4, 's'), (4, 2, 'u')], 'Rec', self.records, self.T)
        self.assertEqual(m['verdict'], 'full')
        self.assertEqual(len(m['sign']), 1)
        self.assertEqual(CT.slice_match([(8, 4, 's')], 'Rec', self.records, self.T)['verdict'], 'partial')
        self.assertEqual(CT.slice_match([(4, 4, 's')], 'Rec', self.records, self.T)['verdict'], 'conflict')
        self.assertEqual(CT.slice_match([(10, 4, 's')], 'Rec', self.records, self.T)['verdict'], 'conflict')

    def test_record_kinds(self):
        self.assertEqual(CT.record_kind('S_801740F8_2', 'src/a.c'), 'generated')
        self.assertEqual(CT.record_kind('Row_8192365C_S_80024E5C_4_pre', 'include/x.h'), 'generated')
        self.assertEqual(CT.record_kind('OutView', 'src/a.c'), 'file_local')
        self.assertEqual(CT.record_kind('EntityRec', 'include/shared/entity.h'), 'not_target')
        self.assertEqual(CT.record_kind('ActorRecord', 'include/shared/entity.h'), 'named')

    def test_split_params(self):
        self.assertEqual(CT.split_params('void (*)(u8 *, struct X *, int)'), (['u8 *', 'struct X *', 'int'], True))
        self.assertEqual(CT.split_params('void (*)(void)'), ([], True))
        self.assertEqual(CT.split_params('void ()'), ([], False))


def rt_arg(file, function, arg, cells):
    total = sum(int(c.rpartition('=')[2]) for c in cells.split(', '))
    return dict(file=file, function=function, arg=arg, observations=total, cells=cells, cur_file=file,
                cur_function=function, how='address+file', address='', images='')


def rt_kind(kid, creator, allocator='allocate_flagged_object_node', flags='0x157', size=0x124):
    return dict(id=kid, role='pool', size=size, flags=flags, allocator=allocator, creator=creator,
                layout=CT.kind_layout(allocator, flags, size))


@unittest.skipUnless(have_clang(), 'clang not installed')
class RuntimeEvidence(unittest.TestCase):
    """Runtime heap kinds as parameter evidence (codemap rt_* tables, joined by address)."""

    @classmethod
    def setUpClass(cls):
        cls.tmp = tempfile.TemporaryDirectory()
        root = Path(cls.tmp.name)
        for rel, text in FILES.items():
            p = root / rel
            p.parent.mkdir(parents=True, exist_ok=True)
            p.write_text(textwrap.dedent(text))
        tus = sorted(str(p.relative_to(root)) for p in (root / 'src').rglob('*.c'))
        flows, errors = CT.extract_flows(root, tus)
        assert not errors, errors
        creator = 'src/fx/create_fx.c:create_fx'
        args = [
            # rk1: an actor kind; its typed receiver (ActorRecord *) names the body record
            rt_arg('src/ghosh/update_boss_actor_action.c', 'update_boss_actor_action', 0, 'rk1+0x20=9'),
            rt_arg('src/weadog/advance_timed_hop_and_recover.c', 'advance_timed_hop_and_recover', 0, 'rk1+0x20=4'),
            rt_arg('src/weadog/advance_timed_hop_and_recover.c', 'advance_timed_hop_and_recover', 1, 'rk1+0xDC=4'),
            # rk2: receivers declare two different records: nothing is proposed
            rt_arg('src/golem/attempt_action.c', 'attempt_actor_action', 0, 'rk2+0x20=3'),
            rt_arg('src/golem/attempt_action.c', 'update_golem', 0, 'rk2+0x20=3'),
            rt_arg('src/neg/shape_only.c', 'tick_shape_only', 0, 'rk2+0x20=3'),
            # rk3: a 0x40-byte body typed as the 0xBC-byte ActorRecord by its receiver: a finding, no proposal
            rt_arg('src/neg/shape_only.c', 'call_shape_only', 0, 'rk3+0x20=2'),
            rt_arg('src/town/countdown.c', 'set_countdown', 0, 'rk3+0x20=2'),
            # rk4: the static callers pass ActorRecord, the runtime kind's receivers say GolemActionWork
            rt_arg('src/ghosh/update_boss_timed_animation.c', 'update_boss_timed_animation', 3, 'rk4+0x20=5'),
            rt_arg('src/golem/attempt_action.c', 'update_golem', 0, 'rk4+0x20=1'),
            # one kind plus other values: observed, not promoted
            rt_arg('src/fx/create_fx.c', 'update_fx', 0, 'rk1+0x20=2, null=1'),
            # rk5: created by the native port itself
            rt_arg('src/fx/slot_entry.c', 'follow_entry', 0, 'rk5+0x20=2'),
            rt_arg('src/ghosh/update_boss_actor_action.c', 'update_boss_actor_action', 0, 'rk5+0x20=1'),
        ]
        kinds = {'rk1': rt_kind('rk1', creator), 'rk2': rt_kind('rk2', creator),
                 'rk3': rt_kind('rk3', creator, 'initialize_scene_object_in_buffer', '0x0', 0x60),
                 'rk4': rt_kind('rk4', creator), 'rk5': rt_kind('rk5', 'port:core/debug.c:force_entities')}
        cls.model, cls.rows = CT.analyze(flows, rt=dict(args=args, kinds=kinds))

    @classmethod
    def tearDownClass(cls):
        cls.tmp.cleanup()

    def row(self, function, param):
        got = [r for r in self.rows if r['function'] == function and r['param'] == param]
        return got[0] if got else None

    def test_kind_layout_follows_the_allocator(self):
        lay = CT.kind_layout('allocate_list_node', '0x157', 0x124)
        self.assertEqual(lay, {0: ('header', 0x20), 0x20: ('body', 0xBC), 0xF4: ('sprite', 0x30),
                               0xDC: ('position', 0x18)})
        self.assertEqual(CT.kind_layout('allocate_flagged_object_node', '0x12', 0x124)[0x20], ('body', 0xC8))
        self.assertEqual(CT.kind_layout('initialize_scene_object_in_buffer', '0x0', 0x88),
                         {0: ('header', 0x20), 0x20: ('body', 0x68)})
        self.assertIsNone(CT.kind_layout('malloc', '0x0', 0x40))

    def test_one_kind_promotes_a_callback_without_callers(self):
        static = self.model.runtime['static']
        key = ('src/weadog/advance_timed_hop_and_recover.c', 'advance_timed_hop_and_recover', 0)
        self.assertEqual(static[key]['cls'], 'C')
        r = self.row('advance_timed_hop_and_recover', 0)
        self.assertEqual((r['cls'], r['proposed']), ('A', 'ActorRecord *'))
        self.assertEqual([(i['kind'], i['caller']) for i in r['items']], [('runtime', 'src/fx/create_fx.c:create_fx')])
        self.assertEqual(CT.evidence_kinds(r['items']), 'runtime')

    def test_carved_position_is_object_position(self):
        r = self.row('advance_timed_hop_and_recover', 1)
        self.assertEqual(r['proposed'], 'ObjectPosition *')
        self.assertEqual(self.model.runtime['kinds'][('rk1', 0xDC)]['role'], 'position')

    def test_disagreeing_receivers_propose_nothing(self):
        self.assertEqual(self.model.runtime['kinds'][('rk2', 0x20)]['verdict'], 'receivers_disagree')
        r = self.row('tick_shape_only', 0)
        self.assertNotIn('runtime', CT.evidence_kinds(r['items']))

    def test_record_larger_than_the_body_is_a_finding(self):
        k = self.model.runtime['kinds'][('rk3', 0x20)]
        self.assertEqual((k['verdict'], k['wanted'], k['region']), ('record_larger_than_body', 'ActorRecord', 0x40))
        self.assertNotIn('runtime', CT.evidence_kinds(self.row('set_countdown', 0)['items']))

    def test_static_evidence_contradiction_keeps_class_c(self):
        static = self.model.runtime['static']
        self.assertEqual(static[('src/ghosh/update_boss_timed_animation.c', 'update_boss_timed_animation', 3)]['cls'], 'A')
        r = self.row('update_boss_timed_animation', 3)
        self.assertEqual(r['cls'], 'C')
        self.assertIn('conflicting_records', r['reason'])

    def test_other_values_and_port_creators_are_not_promoted(self):
        obs = self.model.runtime['observed']
        self.assertEqual(obs[('src/fx/create_fx.c::update_fx', 0)]['outcome'], 'one_kind_plus_other_values')
        self.assertEqual(self.row('update_fx', 0)['cls'], 'C')
        self.assertEqual(self.model.runtime['kinds'][('rk5', 0x20)]['verdict'], 'creator_outside_tree')
        self.assertNotIn('runtime', CT.evidence_kinds(self.row('follow_entry', 0)['items']))

    def test_parse_cells(self):
        self.assertEqual(CT.parse_cells('rk3+0x20=5, null=2, ram:x+0x0=1'),
                         ([('rk3', 0x20, 5)], ['null=2', 'ram:x+0x0=1'], 8))


if __name__ == '__main__':
    unittest.main()
