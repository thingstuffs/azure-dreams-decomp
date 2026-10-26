#include "dungeon/effect/mesh.h"
#include "shared/audio_commands.h"
/* Timed target tinting, source-relative arcing motion, and linked effect setup. */
#include "shared/sprite_frame_state.h"
#include "modules/dungeon_ovl_19ba800.h"
#include "common.h"
#include "shared/tile_object.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/object_flags.h"
#include "shared/dungeon_status.h"

#define U8_AT(p, off) (*(u8 *)((u8 *)(p) + (off)))
#define U16_AT(p, off) (*(u16 *)((u8 *)(p) + (off)))
#define U32_AT(p, off) (*(u32 *)((u8 *)(p) + (off)))
#define S16_AT(p, off) (*(s16 *)((u8 *)(p) + (off)))
#define PTR_AT(p, off) (*(void **)((u8 *)(p) + (off)))

extern u8 D_80024A64[];
extern u16 D_80024A70[];

extern s32 read_sound_mode_blocking_status(s32);
extern void draw_textured_ellipse(void *, void *, s32, s32);
extern u8 resident_globals_page[];

#define MANAGER_PTR() ((void *)(u32)U32_AT(((u8 *)(&primary_actor_record)), 0))



/* The module's entry pointer: the first word of its read-only data, at the row's own address
 * (retail 0x80024000, the row symbol add_flag_adjusted_target_value).  The phase table of the switch below follows
 * it at 0x80024008 (gcc's .align 3 for jump tables), and the code starts after the table. */
void (*const dungeon_19ba800_entry)(TargetTintWork *) = update_directional_actor_effect;

/* Advances a timed effect sequence, updates the entry tint, and draws the animation. */
void update_directional_actor_effect(TargetTintWork *state_data)
{
    TargetTintWork *state = state_data;
    GameWork *effect_flags;
    s32 phase;
    s32 result;
    ActorRecord *entry;
    SpriteFrameState *child;

    state->elapsed++;
    phase = state->phase.s;
    effect_flags = &g_game_work;
    switch (phase) {
    case 0:
        U32_AT(MANAGER_PTR(), 0xF4) = (u32)D_80024A64;
        create_linked_effect_controller((ObjectNodeHeader *)((u8 *)state->owner - 0x20), state->animation);
        result = state->phase.u;
        result++;
        state->phase.u = result;
    case 1:
        result = (s32)state->animation;
        if ((U16_AT((void *)result, 0) & 0x80) == 0) {
            break;
        }
        {
            void *manager =
                *(void **)(resident_globals_page + 0x14A8);

            state->timer.u = 0x12;
            result = U16_AT(manager, 0xA6) - 1;
            U16_AT(manager, 0xA6) = result;
        }
        result = read_sound_mode_blocking_status(4);
        if (result != 2) {
            play_sound_if_enabled(AUDIO_PLAY_CD_CUE);
        } else {
            play_sound_if_enabled(AUDIO_RESUME_CD);
        }
        U8_AT(MANAGER_PTR(), 0xA8) = state->variant;
        state->facing = U16_AT(MANAGER_PTR(), 0x2A);
        state->phase.u++;
        break;

    case 2:
        state->timer.u--;
        if ((s16)state->timer.u > 0) {
            break;
        }
        state->timer.u = 0x10;
        state->phase.u++;
        break;

    case 3:
        entry = PTR_AT(MANAGER_PTR(), 0x60);
        if (entry != 0) {
            s32 entry_flags = entry->flags1C | 0x10000000;
            u32 tint = 0;

            entry->flags1C = entry_flags;
            child = ((ObjectNodeHeader *)((u8 *)entry - 0x20))->sprite;
            if ((effect_flags->unk_004 & 1) != 0) {
                tint = 0x0080FF80;
            }
            child->color.word = tint;
        }
        if ((reference_tile_object.sprite_flags & 0x8000) == 0) {
            state->timer.u--;
            if ((s16)state->timer.u >= 0) {
                break;
            }
        }
        entry = PTR_AT(MANAGER_PTR(), 0x60);
        if (entry != 0) {
            u32 clear_effect_mask = 0xEFFFFFFF;
            u32 tint = 0x00808080;
            s32 entry_flags;

            child = ((ObjectNodeHeader *)((u8 *)entry - 0x20))->sprite;
            entry_flags = entry->flags1C & clear_effect_mask;
            entry->flags1C = entry_flags;
            child->color.word = tint;
        }
        state->phase.u++;
        break;

    case 4:
        if (S16_AT(D_80024A70, 0) == 0) {
            {
                DungeonGlobalStatus *sequence_state = &g_dungeon_status;
                (*(u16 *)&sequence_state->activity_counts.parts.pending_action_count)--;
                sequence_state->active_actor = 0;
            }
            U16_AT(state, -2) |= NODE_REMOVE;
            object_flag_block.flags |= OBJECT_REMOVE_PENDING;
        }
    }
    if (state->phase.s >= 2) {
        u8 *draw_data = (u8 *)&D_80024A70[2];
        s32 draw_params[2];

        draw_params[0] = 0x01000360;
        draw_params[1] = 0x00200020;
        draw_textured_ellipse(draw_data, draw_params, 1, 0);
        U8_AT(draw_data, 8) += 0x10;
    }
    D_80024A70[0] = 0;
}

#include "modules/dungeon_ovl_19ba800.h"
#include "common.h"
#include "shared/entity.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/object_flags.h"
#include "shared/dungeon_moving_views.h"
#include "shared/dungeon_delay_views.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct S_8199AAD4_0 {
    void * unk_00;
    void * unk_04;
    void * unk_08;
    void * unk_0C;
    union { s32 s; u8 * u; } unk_10;   /* accessed as both */
    s32 unk_14;
    u8 pad_18[0x10];
    union { s16 s; volatile u16 u; u16 p; } unk_28;   /* accessed as both */
    u8 pad_2A[0x4];
    union { volatile s16 s; s16 u; u16 p; } unk_2E;   /* accessed as both */
    union { s16 s; u16 u; } unk_30;   /* accessed as both */
    u8 pad_32[0x6];
    s16 unk_38;
} S_8199AAD4_0;   /* self in update_source_relative_position_delays_movement_advances_arc_toward_target */

typedef struct S_8199AAD4_1 {
    u8 pad_00[0x8];
    void * unk_08;
    u8 pad_0C[0x8];
    u16 unk_14;
} S_8199AAD4_1;   /* source in update_source_relative_position_delays_movement_advances_arc_toward_target */

typedef struct S_8199AAD4_2 {
    union {
        struct { s32 v; } at00;
        struct { u8 pad[0x2]; u16 v; } at02;
        struct { u8 pad[0x2]; s16 v; } at02u;
    } unk_00;   /* overlapping accesses */
    union {
        struct { s32 v; } at00;
        struct { u8 pad[0x2]; u16 v; } at02;
        struct { u8 pad[0x2]; s16 v; } at02u;
    } unk_04;   /* overlapping accesses */
    union {
        struct { s32 v; } at00;
        struct { u8 pad[0x2]; u16 v; } at02;
        struct { u8 pad[0x2]; s16 v; } at02u;
    } unk_08;   /* overlapping accesses */
} S_8199AAD4_2;   /* coords in update_source_relative_position_delays_movement_advances_arc_toward_target */

   /* position in update_source_relative_position_delays_movement_advances_arc_toward_target */

typedef struct S_8199AAD4_4 {
    u8 pad_00[0x14A0];
    s32 unk_14A0;
} S_8199AAD4_4;   /* global_flags in update_source_relative_position_delays_movement_advances_arc_toward_target */

typedef struct S_8199AAD4_5 {
    void * unk_00;
    u8 pad_04[0x4];
    void * unk_08;
} S_8199AAD4_5;   /* entry in update_source_relative_position_delays_movement_advances_arc_toward_target */

typedef struct S_8199AAD4_6 {
    s32 unk_00;
    s32 unk_04;
} S_8199AAD4_6;   /* target_node in update_source_relative_position_delays_movement_advances_arc_toward_target */

typedef struct S_8199AAD4_8 {
    u8 pad_00[0xC];
    void * unk_0C;
} S_8199AAD4_8;   /* call_node in update_source_relative_position_delays_movement_advances_arc_toward_target */

typedef struct S_8199AAD4_10 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
} S_8199AAD4_10;   /* ((S_8199AAD4_0 *)self)->unk_00 in update_source_relative_position_delays_movement_advances_arc_toward_target */

#define source source_or_step

typedef struct Vec3s {
    s16 x;
    s16 y;
    s16 z;
} Vec3s;

extern u8 D_80024AE0;
extern u16 D_80024A70[];
extern void *actor_direction_sprites;

/* Ordinary declaration: the private selector authenticates this one
 * returning tail by qid/geometry/context instead of using an asm symbol alias. */
extern void *create_positioned(void *, s32, s32, s32, void *, s32, s32, s32, void *);
extern s32 resolve_record_orientation_or_fallback(void *, void *, void *, s32);
extern s32 rsin(s32);
extern void spawn_blinking_sprite_flash(s16, s16, s16);

/* Updates source-relative position, delays movement, and advances an arc toward the target. */
void update_source_relative_position_delays_movement_advances_arc_toward_target(void *self, void *coords)
{
    u16 delta[3];
    s32 target[3];
    s32 start_x;
    s32 start_y;
    s32 start_z;
    s16 state;
    void *source_or_step;
    void *iteration;
    S_8199AAD4_6 *target_node;
    S_8199AAD4_8 *call_node;
    MovingPosition *position;
    void *entry_base;
    S_8199AAD4_5 *object_entry;
    DelayMotionZ *created;
    u8 *table_end;
    u8 *table_start;
    u8 *table_start_2;
    s32 entry_offset;
    s32 arc_height;
    s32 flags_value;
    u16 count;
    u32 position_z;
    u16 tail_z;
    u16 tail_z_2;
    s32 *global_flags;
    void *delta_out;
    D_80024A70[0]++;

    state = ((S_8199AAD4_0 *)self)->unk_28.s;
    switch (state) {
    case 0:
        source = ((S_8199AAD4_10 *)(((S_8199AAD4_0 *)self)->unk_00))->unk_0C;
        if ((((S_8199AAD4_1 *)source)->unk_14 & 0x8000) ||
            resolve_record_orientation_or_fallback(((S_8199AAD4_1 *)source)->unk_08, source, delta, 0)) {
            position = ((S_8199AAD4_10 *)(((S_8199AAD4_0 *)self)->unk_00))->unk_08;
            ((S_8199AAD4_2 *)coords)->unk_00.at02.v = position->x;
            ((S_8199AAD4_2 *)coords)->unk_04.at02.v = position->y;
            position_z = position->z;
            ((S_8199AAD4_2 *)coords)->unk_08.at02.v = position_z;

            if (!(((S_8199AAD4_1 *)source)->unk_14 & 0x8000)) {
                ((S_8199AAD4_2 *)coords)->unk_00.at02.v += delta[0];
                ((S_8199AAD4_2 *)coords)->unk_04.at02.v += delta[1];
                tail_z_2 = ((S_8199AAD4_2 *)coords)->unk_08.at02.v;
                tail_z_2 += delta[2];
                ((S_8199AAD4_2 *)coords)->unk_08.at02.v = tail_z_2;
            } else {
                tail_z = position_z - 0x20;

                ((S_8199AAD4_2 *)coords)->unk_08.at02.v = tail_z;
            }
        }

        if (((u16 *)(((S_8199AAD4_0 *)self)->unk_0C))[0] & 0x80) {
            ((S_8199AAD4_0 *)self)->unk_2E.s = 8;
            tail_z = ((S_8199AAD4_0 *)self)->unk_28.u;
            target_node = 9;
            ((S_8199AAD4_0 *)self)->unk_30.s = target_node;
            ((S_8199AAD4_0 *)self)->unk_28.p = tail_z + 1;
        }
        return;
    case 1:
        count = ((S_8199AAD4_0 *)self)->unk_30.u - 1;
        ((S_8199AAD4_0 *)self)->unk_30.u = count;
        if ((s16)count > 0) {
            return;
        }
        tail_z = ((S_8199AAD4_0 *)self)->unk_28.u;
        ((S_8199AAD4_0 *)self)->unk_28.p = tail_z + 1;
        return;
finish:
        ((S_8199AAD4_2 *)coords)->unk_00.at00.v = target[0];
        ((S_8199AAD4_2 *)coords)->unk_04.at00.v = target[1];
        ((S_8199AAD4_2 *)coords)->unk_08.at00.v = target[2];
        spawn_blinking_sprite_flash(((S_8199AAD4_2 *)coords)->unk_00.at02u.v, ((S_8199AAD4_2 *)coords)->unk_04.at02u.v,
                      ((S_8199AAD4_2 *)coords)->unk_08.at02u.v);
        tail_z = ((u16 *)self)[-1];
        global_flags = (s32 *)0x80080000;
        ((u16 *)self)[-1] = tail_z | 0x8000;
        count = ((S_8199AAD4_0 *)self)->unk_28.p;
        flags_value = ((S_8199AAD4_4 *)global_flags)->unk_14A0;
        count++;
        flags_value |= 0x8000;
        ((S_8199AAD4_0 *)self)->unk_28.p = count;
        ((S_8199AAD4_4 *)global_flags)->unk_14A0 = flags_value;
        return;

    case 2:
        iteration = NULL;
        table_end = &D_80024AE0;
        table_start_2 = table_end - 0x54;
loop_top:
        object_entry = ((S_8199AAD4_0 *)self)->unk_04;
        start_x = ((S_8199AAD4_2 *)coords)->unk_00.at02u.v;
        start_y = ((S_8199AAD4_2 *)coords)->unk_04.at02u.v;
        target_node = object_entry->unk_08;
        start_z = ((S_8199AAD4_2 *)coords)->unk_08.at02u.v;
        target[0] = target_node->unk_00;
        target[1] = target_node->unk_04;
        target[2] = (((S_8199AAD4_0 *)self)->unk_38 - 0x50) << 16;

        entry_offset = (g_game_work.view.camera_rotation.parts.viewAngle + primary_actor_record->facing + 0x100) >> 7;
        delta_out = delta;
        entry_base = actor_direction_sprites;
        entry_offset &= 0x1C;
        call_node = ((S_8199AAD4_0 *)self)->unk_04;
        if (resolve_record_orientation_or_fallback(((S_8199AAD4_5 *)(entry_offset + (long)entry_base))->unk_00, call_node->unk_0C, delta_out,
            0)) {
            target[0] += (s32)(s16)delta[0] << 16;
            target[1] += (s32)(s16)delta[1] << 16;
            target[2] += (s32)(s16)delta[2] << 16;
        }

        ((S_8199AAD4_2 *)coords)->unk_00.at00.v +=
            (target[0] - ((S_8199AAD4_2 *)coords)->unk_00.at00.v) / ((S_8199AAD4_0 *)self)->unk_2E.u;
        ((S_8199AAD4_2 *)coords)->unk_04.at00.v +=
            (target[1] - ((S_8199AAD4_2 *)coords)->unk_04.at00.v) / ((S_8199AAD4_0 *)self)->unk_2E.u;
        arc_height = rsin(((S_8199AAD4_0 *)self)->unk_2E.u * 170);
        ((S_8199AAD4_2 *)coords)->unk_08.at00.v +=
            (target[2] - ((S_8199AAD4_2 *)coords)->unk_08.at00.v) / ((S_8199AAD4_0 *)self)->unk_2E.u -
            (arc_height << 7);

        created = create_positioned(((S_8199AAD4_0 *)self)->unk_08, start_x, start_y, start_z,
                                coords, ((S_8199AAD4_0 *)self)->unk_10.s, 4,
                                ((S_8199AAD4_0 *)self)->unk_14, iteration);
        if (created != NULL) {
            ((S_8199AAD4_0 *)self)->unk_08 = created;
            ((S_8199AAD4_0 *)self)->unk_14 = created->unk_08;
        }

        count = ((S_8199AAD4_0 *)self)->unk_2E.p - 1;
        ((S_8199AAD4_0 *)self)->unk_2E.p = count;
        if ((s16)count <= 0) {
            goto finish;
        }

        ((S_8199AAD4_0 *)self)->unk_10.u += 0xC;
        if (((S_8199AAD4_0 *)self)->unk_10.u >= table_end) {
            ((S_8199AAD4_0 *)self)->unk_10.u = table_start_2;
        }
        iteration = (u8 *)iteration + 1;
        goto loop_top;
    }
}

/* MECHANISM: The census baseline holds the 0x68 sibling-local frame and retail saved-register set.
   Register pins encode the surviving bases and late call operands; residual work starts at word 120. */
#include "modules/dungeon_ovl_19ba800.h"
#include "common.h"
#include "shared/object_node.h"
#include "shared/record_ptrs.h"
#include "shared/entity.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct Node {
    char pad00[0x10];
    void *field10;
    char pad14[0xC];
    void *field20;
} Node;

typedef struct Child {
    char pad00[4];
    void *field04;
    void *field08;
    void *field0C;
    void *field10;
    char pad14[0x24];
    u16 field38;
} Child;

#define D_800242D4 ((char *)update_source_relative_position_delays_movement_advances_arc_toward_target)
extern char D_80024A8C[];

/* Allocate a node and initialize its child with supplied values and shared source data. */
void create_linked_effect_controller(ObjectNodeHeader *node_value, void *child_value)
{
    Node *node;
    Child *child;
    ActorRecord *source;
    void *callback;
    u16 source_value;

    node = allocate_list_node(0x10, &scene_object_list_anchor.next);
    if (node != NULL) {
        child = (Child *)((char *)node + 0x20);
        node->field10 = D_800242D4;
        callback = D_80024A8C;
        source = primary_actor_record;
        child->field10 = callback;
        node->field20 = node_value;
        child->field04 = &scene_object_list_anchor.next;
        source_value = ((u16)source->ground_height);
        child->field0C = child_value;
        child->field08 = node;
        child->field38 = source_value;
    }
}
