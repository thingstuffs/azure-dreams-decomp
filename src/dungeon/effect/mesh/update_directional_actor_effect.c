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
#include "dungeon/effect/screen.h"
#include "engine/scene.h"
#include "sdk/libgte.h"
#include "slus.h"
#include "dungeon/system.h"

#define U8_AT(p, off) (*(u8 *)((u8 *)(p) + (off)))
#define U16_AT(p, off) (*(u16 *)((u8 *)(p) + (off)))
#define U32_AT(p, off) (*(u32 *)((u8 *)(p) + (off)))
#define S16_AT(p, off) (*(s16 *)((u8 *)(p) + (off)))
#define PTR_AT(p, off) (*(void **)((u8 *)(p) + (off)))

extern u8 D_80024A64[];
extern u16 D_80024A70[];

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
        create_linked_effect_controller(NODE_HEADER(state->owner), state->animation);
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
            child = NODE_HEADER(entry)->sprite;
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

            child = NODE_HEADER(entry)->sprite;
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
        GpuRectBuffer draw_params;

        draw_params.words[0] = 0x01000360;
        draw_params.words[1] = 0x00200020;
        draw_textured_ellipse(draw_data, &draw_params.rect, 1, 0);
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

    state = ((LinkedEffectControllerBody *)self)->field28.s;
    switch (state) {
    case 0:
        source = ((S_8199AAD4_10 *)(((LinkedEffectControllerBody *)self)->field00))->unk_0C;
        if ((((S_8199AAD4_1 *)source)->unk_14 & 0x8000) ||
            resolve_record_orientation_or_fallback(((S_8199AAD4_1 *)source)->unk_08, source, delta, 0)) {
            position = ((S_8199AAD4_10 *)(((LinkedEffectControllerBody *)self)->field00))->unk_08;
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

        if (((u16 *)(((LinkedEffectControllerBody *)self)->field0C))[0] & 0x80) {
            ((LinkedEffectControllerBody *)self)->field2E.s = 8;
            tail_z = ((LinkedEffectControllerBody *)self)->field28.u;
            target_node = 9;
            ((LinkedEffectControllerBody *)self)->field30.s = target_node;
            ((LinkedEffectControllerBody *)self)->field28.p = tail_z + 1;
        }
        return;
    case 1:
        count = ((LinkedEffectControllerBody *)self)->field30.u - 1;
        ((LinkedEffectControllerBody *)self)->field30.u = count;
        if ((s16)count > 0) {
            return;
        }
        tail_z = ((LinkedEffectControllerBody *)self)->field28.u;
        ((LinkedEffectControllerBody *)self)->field28.p = tail_z + 1;
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
        count = ((LinkedEffectControllerBody *)self)->field28.p;
        flags_value = ((S_8199AAD4_4 *)global_flags)->unk_14A0;
        count++;
        flags_value |= 0x8000;
        ((LinkedEffectControllerBody *)self)->field28.p = count;
        ((S_8199AAD4_4 *)global_flags)->unk_14A0 = flags_value;
        return;

    case 2:
        iteration = NULL;
        table_end = &D_80024AE0;
        table_start_2 = table_end - 0x54;
loop_top:
        object_entry = ((LinkedEffectControllerBody *)self)->field04;
        start_x = ((S_8199AAD4_2 *)coords)->unk_00.at02u.v;
        start_y = ((S_8199AAD4_2 *)coords)->unk_04.at02u.v;
        target_node = object_entry->unk_08;
        start_z = ((S_8199AAD4_2 *)coords)->unk_08.at02u.v;
        target[0] = target_node->unk_00;
        target[1] = target_node->unk_04;
        target[2] = (((LinkedEffectControllerBody *)self)->field38 - 0x50) << 16;

        entry_offset = (g_game_work.view.camera_rotation.parts.viewAngle + primary_actor_record->facing + 0x100) >> 7;
        delta_out = delta;
        entry_base = actor_direction_sprites;
        entry_offset &= 0x1C;
        call_node = ((LinkedEffectControllerBody *)self)->field04;
        if (resolve_record_orientation_or_fallback(((S_8199AAD4_5 *)(entry_offset + (long)entry_base))->unk_00, call_node->unk_0C, delta_out,
            0)) {
            target[0] += (s32)(s16)delta[0] << 16;
            target[1] += (s32)(s16)delta[1] << 16;
            target[2] += (s32)(s16)delta[2] << 16;
        }

        ((S_8199AAD4_2 *)coords)->unk_00.at00.v +=
            (target[0] - ((S_8199AAD4_2 *)coords)->unk_00.at00.v) / ((LinkedEffectControllerBody *)self)->field2E.u;
        ((S_8199AAD4_2 *)coords)->unk_04.at00.v +=
            (target[1] - ((S_8199AAD4_2 *)coords)->unk_04.at00.v) / ((LinkedEffectControllerBody *)self)->field2E.u;
        arc_height = rsin(((LinkedEffectControllerBody *)self)->field2E.u * 170);
        ((S_8199AAD4_2 *)coords)->unk_08.at00.v +=
            (target[2] - ((S_8199AAD4_2 *)coords)->unk_08.at00.v) / ((LinkedEffectControllerBody *)self)->field2E.u -
            (arc_height << 7);

        created = create_positioned(((LinkedEffectControllerBody *)self)->field08, start_x, start_y, start_z,
                                coords, ((LinkedEffectControllerBody *)self)->field10.s, 4,
                                ((LinkedEffectControllerBody *)self)->field14, iteration);
        if (created != NULL) {
            ((LinkedEffectControllerBody *)self)->field08 = created;
            ((LinkedEffectControllerBody *)self)->field14 = created->unk_08;
        }

        count = ((LinkedEffectControllerBody *)self)->field2E.p - 1;
        ((LinkedEffectControllerBody *)self)->field2E.p = count;
        if ((s16)count <= 0) {
            goto finish;
        }

        ((LinkedEffectControllerBody *)self)->field10.u += 0xC;
        if (((LinkedEffectControllerBody *)self)->field10.u >= table_end) {
            ((LinkedEffectControllerBody *)self)->field10.u = table_start_2;
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

#define D_800242D4 ((char *)update_source_relative_position_delays_movement_advances_arc_toward_target)
extern char D_80024A8C[];

/* Allocate a node and initialize its child with supplied values and shared source data. */
void create_linked_effect_controller(ObjectNodeHeader *node_value, void *child_value)
{
    Node *node;
    LinkedEffectControllerBody *child;
    ActorRecord *source;
    void *callback;
    u16 source_value;

    node = allocate_list_node(0x10, &scene_object_list_anchor.next);
    if (node != NULL) {
        child = (LinkedEffectControllerBody *)((char *)node + 0x20);
        node->field10 = D_800242D4;
        callback = D_80024A8C;
        source = primary_actor_record;
        child->field10.u = callback;
        node->field20 = node_value;
        child->field04 = &scene_object_list_anchor.next;
        source_value = ((u16)source->ground_height);
        child->field0C = child_value;
        child->field08 = node;
        child->field38 = source_value;
    }
}
