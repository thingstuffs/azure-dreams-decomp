#include "dungeon/effect/motion/update_directional_actor_effect.h"
#include "shared/sprite_frame_state.h"
#include "dungeon/effect/motion/update_directional_actor_effect.h"
#include "common.h"
#include "shared/tile_object.h"
#include "shared/record_ptrs.h"
#include "shared/object_flags.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"

typedef struct S_8195281C_0_pre {
    u16 unk_00;
} S_8195281C_0_pre;   /* the 0x2 bytes before arg0 in func_8195281C, addressed as arg0[-1] */

typedef struct S_8195281C_0 {
    s32 unk_00;
    u16 * unk_04;
    u8 unk_08;
    u8 unk_09;
    union { s16 s; u16 u; } unk_0A;   /* accessed as both */
    u8 pad_0C[0x8];
    union { u16 u; s16 s; } unk_14;   /* accessed as both */
    u16 unk_16;
    s16 unk_18;
} S_8195281C_0;   /* arg0 in func_8195281C */

typedef struct S_8195281C_1 {
    union { s32 i; void * p; } unk_00;   /* accessed as both */
} S_8195281C_1;   /* D_800814A8 in func_8195281C */

typedef struct S_8195281C_2 {
    u8 pad_00[0xA6];
    u16 unk_A6;
    u8 unk_A8;
} S_8195281C_2;

typedef struct S_8195281C_3 {
    u8 pad_00[0x2A];
    u16 unk_2A;
    u8 pad_2C[0x7D];
    u8 unk_A9;
} S_8195281C_3;

typedef struct S_8195281C_4 {
    u8 pad_00[0x60];
    void * unk_60;
} S_8195281C_4;

typedef struct S_8195281C_5_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_8195281C_5_pre;

typedef struct S_8195281C_5 {
    u8 pad_00[0x1C];
    s32 unk_1C;
} S_8195281C_5;

typedef struct S_8195281C_6 {
    u8 pad_00[0xC];
    union {
        struct { u8 v; } at00;
        struct { s32 v; } at00u;
        struct { u8 pad[0x1]; u8 v; } at01;
        struct { u8 pad[0x2]; u8 v; } at02;
    } unk_0C;   /* overlapping accesses */
} S_8195281C_6;

typedef struct S_8195281C_7 {
    u8 pad_00[0x60];
    void * unk_60;
} S_8195281C_7;   /* D_800E3D7C[0] in func_8195281C */

typedef struct S_8195281C_9 {
    s32 unk_00;
} S_8195281C_9;   /* D_800814A0 in func_8195281C */

typedef struct S_8195281C_10 {
    u8 pad_00[0x60];
    void * unk_60;
    u8 pad_64[0x90];
    s32 * unk_F4;
} S_8195281C_10;   /* ((S_8195281C_1 *)D_800814A8)->unk_00.i in func_8195281C */

/* The module's entry pointer: the first word of its read-only data, at the row's own address
 * (retail 0x80024000, the row symbol add_flag_adjusted_target_value).  The switch table follows it at 0x80024008
 * (gcc's .align 3 for jump tables), and the code starts after the table. */

void (*const dungeon_1972800_entry)(void *, void *) = update_directional_actor_effect;

/* Advances a timed effect sequence, fading model colors and marking completion. */
extern void process_effect_modes_and_completion(void *state);

void update_directional_actor_effect(void *effect, void *color_data) {
    s32 upload_rect[2];
    s16 delay_left;
    s16 fade_left;
    s32 stage;
    void *model;
    S_8195281C_6 *model_colors;
    S_8195281C_3 *actor_state;
    u16 ready_stage;
    u16 actor_param;
    S_8195281C_4 *model_owner;
    u16 fade_stage;
    S_8195281C_2 *actor_counters;
    void **actor_slot;

    model_colors = color_data;
    stage = ((S_8195281C_0 *)effect)->unk_0A.s;
    ((S_8195281C_0 *)effect)->unk_16 = (u16) (((S_8195281C_0 *)effect)->unk_16 + 1);
    switch (stage) {
    case 0:
        upload_rect[0] = 0x01000340;
        upload_rect[1] = 0x200020;
        draw_textured_ellipse(D_800DF334, upload_rect, 1, 0);
        upload_rect[0] = 0x01000360;
        draw_textured_ellipse(D_80024980, upload_rect, 1, 0);
        ((S_8195281C_10 *)(((S_8195281C_1 *)((int *)(&D_800814A8)))->unk_00.i))->unk_F4 = D_80024998;
        create_timed_model_effect(((S_8195281C_0 *)effect)->unk_00 - 0x20, ((S_8195281C_0 *)effect)->unk_04, 0, 0);
        ((S_8195281C_0 *)effect)->unk_0A.s = (s16) ((u16) ((S_8195281C_0 *)effect)->unk_0A.s + 1);
    case 1:
        actor_slot = (void **) ((int *)(&D_800814A8));
        if (!(*((S_8195281C_0 *)effect)->unk_04 & 0x80)) {
            break;
        }
        actor_counters = *actor_slot;
        ((S_8195281C_0 *)effect)->unk_18 = 0x12;
        actor_counters->unk_A6 = (u16) (actor_counters->unk_A6 - 1);
        actor_counters->unk_A8 = (u8) ((S_8195281C_0 *)effect)->unk_08;
        actor_state = *actor_slot;
        actor_state->unk_A9 = (u8) ((S_8195281C_0 *)effect)->unk_09;
        actor_state = *actor_slot;
        D_800249A4 = 0;
        ready_stage = ((S_8195281C_0 *)effect)->unk_0A.u;
        actor_param = actor_state->unk_2A;
        ((S_8195281C_0 *)effect)->unk_0A.u = ready_stage + 1;
        ((S_8195281C_0 *)effect)->unk_14.u = actor_param;
        break;
    case 2:
        if (((S_8195281C_0 *)effect)->unk_18 == 8) {
            play_sound_if_enabled(0x300);
        }
        delay_left = (u16) ((S_8195281C_0 *)effect)->unk_18 - 1;
        ((S_8195281C_0 *)effect)->unk_18 = delay_left;
        if ((delay_left << 0x10) > 0) {
            break;
        }
        model_owner = ((S_8195281C_1 *)((int *)(&D_800814A8)))->unk_00.p;
        ((S_8195281C_0 *)effect)->unk_18 = 0x20;
        allocate_and_initialize_effect_object(effect - 0x20, ((S_8195281C_0 *)effect)->unk_14.s, ((S_8195281C_0 *)effect)->unk_09,
            model_owner->unk_60);
        ((S_8195281C_0 *)effect)->unk_0A.s = (u16) ((S_8195281C_0 *)effect)->unk_0A.s + 1;
        break;
    case 3:
        model = ((S_8195281C_10 *)(((S_8195281C_1 *)((int *)(&D_800814A8)))->unk_00.i))->unk_60;
        if (model != 0) {
            model_colors = ((S_8195281C_5_pre *)model)[-1].unk_00;
            ((S_8195281C_5 *)model)->unk_1C = (s32) (((S_8195281C_5 *)model)->unk_1C | 0x10000000);
            model_colors->unk_0C.at00.v = (u8) (model_colors->unk_0C.at00.v - 4);
            model_colors->unk_0C.at01.v = (u8) (model_colors->unk_0C.at01.v - 4);
            model_colors->unk_0C.at02.v = (u8) (model_colors->unk_0C.at02.v - 4);
            if ((u8) model_colors->unk_0C.at00.v < 0x20U) {
                model_colors->unk_0C.at00.v = 0x20U;
            }
            if ((u8) model_colors->unk_0C.at01.v < 0x20U) {
                model_colors->unk_0C.at01.v = 0x20U;
            }
            if ((u8) model_colors->unk_0C.at02.v < 0x20U) {
                model_colors->unk_0C.at02.v = 0x20U;
            }
        }
        if (!(D_80082E80.sprite_flags & 0x8000)) {
            fade_left = (u16) ((S_8195281C_0 *)effect)->unk_18 - 1;
            ((S_8195281C_0 *)effect)->unk_18 = fade_left;
            if ((fade_left << 0x10) >= 0) {
                break;
            }
        }
        model = ((S_8195281C_7 *)(((u8 *)D_800E3D7C)))->unk_60;
        if (model != 0) {
            model_colors = ((S_8195281C_5_pre *)model)[-1].unk_00;
            model_colors->unk_0C.at00u.v = 0x808080;
        }
        fade_stage = ((S_8195281C_0 *)effect)->unk_0A.u;
        D_800249A4 = 1;
        ((S_8195281C_0 *)effect)->unk_0A.u = fade_stage + 1;
        break;
    case 4:
        if ((s16)D_800249A6[0] != 0) {
            break;
        }
        g_dungeon_status.active_actor = 0;
        g_dungeon_status.activity_counts.parts.pending_action_count = (u16) (((u16)g_dungeon_status.activity_counts.parts.pending_action_count) - 1);
        ((S_8195281C_0_pre *)effect)[-1].unk_00 = (u16) (((S_8195281C_0_pre *)effect)[-1].unk_00 | 0x8000);
        ((S_8195281C_9 *)((s32 *)(&object_flag_block)))->unk_00 =
            (s32) (((S_8195281C_9 *)((s32 *)(&object_flag_block)))->unk_00 | 0x8000);
    }
    D_800249A6[0] = 0;
    return;
}

typedef struct S_81952B4C_0 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    u8 pad_0C[0x4];
    s16 unk_10;
    s16 unk_12;
    u8 pad_14[0x10];
    union { s16 s; u16 u; } unk_24;   /* accessed as both */
    u8 pad_26[0x2];
    union { s16 s; u16 u; } unk_28;   /* accessed as both */
    u16 unk_2A;
    s16 unk_2C;
    u8 pad_2E[0x6];
    s16 unk_34;
} S_81952B4C_0;   /* arg0 in update_spiraling_effect_growth_and_fade */

typedef struct S_81952B4C_1 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_08;   /* overlapping accesses */
    u8 pad_0C[0x2];
    u16 unk_0E;
    u8 pad_10[0x2];
    u16 unk_12;
    u8 pad_14[0x2];
    u16 unk_16;
} S_81952B4C_1;   /* arg1 in update_spiraling_effect_growth_and_fade */

typedef struct S_81952B4C_2 {
    u8 pad_00[0xC];
    union {
        struct { u8 v; } at00;
        struct { s32 v; } at00u;
        struct { u8 pad[0x1]; u8 v; } at01;
        struct { u8 pad[0x2]; u8 v; } at02;
    } unk_0C;   /* overlapping accesses */
    u8 pad_10[0xC];
    u16 unk_1C;
    u16 unk_1E;
} S_81952B4C_2;   /* arg2 in update_spiraling_effect_growth_and_fade */

/* Updates a spiraling effect's growth, motion, and fade-out. */
void update_spiraling_effect_growth_and_fade(void *effect, void *position, void *sprite)
{
    s16 state;
    s16 radius;
    s16 frames_left;
    s32 velocity_x;
    s32 velocity_y;
    s32 global_flags;
    u16 scale;
    u8 brightness;

    D_800249A6[0]++;

    if (D_800249A4 != 0 && ((S_81952B4C_0 *)effect)->unk_24.s < 2) {
        ((S_81952B4C_0 *)effect)->unk_00 =
            func_80064584(((S_81952B4C_0 *)effect)->unk_28.s) *
            ((S_81952B4C_0 *)effect)->unk_34 * 8;
        ((S_81952B4C_0 *)effect)->unk_04 =
            func_800644B8(((S_81952B4C_0 *)effect)->unk_28.s) *
            ((S_81952B4C_0 *)effect)->unk_34 * 8;
        ((S_81952B4C_0 *)effect)->unk_24.s = 2;
    }

    ((S_81952B4C_1 *)position)->unk_0E = ((S_81952B4C_1 *)position)->unk_00.at02.v;
    ((S_81952B4C_1 *)position)->unk_12 = ((S_81952B4C_1 *)position)->unk_04.at02.v;
    ((S_81952B4C_1 *)position)->unk_16 = ((S_81952B4C_1 *)position)->unk_08.at02.v;

    state = ((S_81952B4C_0 *)effect)->unk_24.s;
    switch (state) {
    case 0:
        scale = ((S_81952B4C_2 *)sprite)->unk_1E;
        scale += (0x1000 - scale) / ((S_81952B4C_0 *)effect)->unk_2C;
        ((S_81952B4C_2 *)sprite)->unk_1E = scale;
        ((S_81952B4C_2 *)sprite)->unk_1C = scale;
        if (scale >= 0x801) {
            ((S_81952B4C_2 *)sprite)->unk_1E = 0x800;
            ((S_81952B4C_2 *)sprite)->unk_1C = 0x800;
        }

        brightness = ((S_81952B4C_2 *)sprite)->unk_0C.at02.v + 2;
        ((S_81952B4C_2 *)sprite)->unk_0C.at02.v = brightness;
        ((S_81952B4C_2 *)sprite)->unk_0C.at01.v = brightness;
        ((S_81952B4C_2 *)sprite)->unk_0C.at00.v = brightness;
        if (brightness >= 0x81) {
            ((S_81952B4C_2 *)sprite)->unk_0C.at00u.v = 0x00808080;
        }

        ((S_81952B4C_1 *)position)->unk_00.at00.v =
            (((S_81952B4C_0 *)effect)->unk_10 << 16) +
            func_80064584(((S_81952B4C_0 *)effect)->unk_28.s) *
            ((S_81952B4C_0 *)effect)->unk_34 * 8;
        ((S_81952B4C_1 *)position)->unk_04.at00.v =
            (((S_81952B4C_0 *)effect)->unk_12 << 16) +
            func_800644B8(((S_81952B4C_0 *)effect)->unk_28.s) *
            ((S_81952B4C_0 *)effect)->unk_34 * 8;

        ((S_81952B4C_0 *)effect)->unk_08 -= 0x5000;
        radius = (u16)((S_81952B4C_0 *)effect)->unk_34 + 4;
        ((S_81952B4C_0 *)effect)->unk_34 = radius;
        if (radius >= 0x41) {
            ((S_81952B4C_0 *)effect)->unk_34 = 0x40;
        }

        ((S_81952B4C_0 *)effect)->unk_28.u += 0x180;
        frames_left = (u16)((S_81952B4C_0 *)effect)->unk_2C - 1;
        ((S_81952B4C_0 *)effect)->unk_2C = frames_left;
        if ((frames_left << 16) <= 0) {
            ((S_81952B4C_0 *)effect)->unk_24.u++;
        }

        break;
    case 1:
        break;
    case 2:
        velocity_x = ((S_81952B4C_0 *)effect)->unk_00;
        velocity_y = ((S_81952B4C_0 *)effect)->unk_04;
        ((S_81952B4C_0 *)effect)->unk_00 = velocity_x + (velocity_x >> 1);
        ((S_81952B4C_0 *)effect)->unk_04 = velocity_y + (velocity_y >> 1);
        ((S_81952B4C_0 *)effect)->unk_08 += 0x10000;

        brightness = ((S_81952B4C_2 *)sprite)->unk_0C.at02.v - 4;
        ((S_81952B4C_2 *)sprite)->unk_0C.at02.v = brightness;
        ((S_81952B4C_2 *)sprite)->unk_0C.at01.v = brightness;
        ((S_81952B4C_2 *)sprite)->unk_0C.at00.v = brightness;
        if ((s8)brightness <= 0) {
            (*(u16 *)((u8 *)effect + -2)) |= 0x8000;
            global_flags = object_flag_block.flags | 0x8000;
            ((S_81952B4C_0 *)effect)->unk_24.u++;
            object_flag_block.flags = global_flags;
            return;
        }

        break;
    }

    ((S_81952B4C_0 *)effect)->unk_2A++;
    ((S_81952B4C_1 *)position)->unk_00.at00.v += ((S_81952B4C_0 *)effect)->unk_00;
    ((S_81952B4C_1 *)position)->unk_04.at00.v += ((S_81952B4C_0 *)effect)->unk_04;
    ((S_81952B4C_1 *)position)->unk_08.at00.v += ((S_81952B4C_0 *)effect)->unk_08;
}

typedef struct SpawnPosition {
    u16 pad_00, x, pad_04, y, pad_08;
    union { u16 bits; s16 signed_value; } z;
} SpawnPosition;

typedef struct SpawnSprite {
    u8 pad_00[8];
    void *frames;
    u8 pad_0C[4];
    s16 size;
    u8 pad_12[2];
    u16 flags;
} SpawnSprite;

typedef struct SpiralState {
    u8 pad_00[0x0C];
    void *target;
    u16 x, y, z;
    u8 pad_16[0x10];
    u16 angle, reverse_angle;
    u8 pad_2A[2];
    s16 lifetime;
    u8 pad_2E[4];
    s16 mirrored;
} SpiralState;

/* The 0x20-byte object-list header that precedes an effect's record. */
typedef struct SpawnHeader {
    u8 pad_00[8];
    SpawnPosition *position;
    SpawnSprite *sprite;
    void (*callback)(void *, void *, void *);
    u8 pad_14[0xC];
} SpawnHeader;

typedef struct SpawnNode {
    SpawnHeader header;
    SpiralState state;
} SpawnNode;

typedef struct GridOrigin {
    u8 pad_00[0x24];
    u8 x, y;
} GridOrigin;

typedef struct OriginHeight {
    u8 pad_00[0x88];
    u16 height;
} OriginHeight;

/* Spawn the spiraling effect unless the shared bank stop flag is set.
 * The third ABI argument is unused in retail. The final argument mirrors
 * the direction and is retained in the spawned state.
 */
void spawn_spiraling(void *anchor, s16 angle, s16 unused, void *target, s32 mirrored)
{
    SpawnNode *node;
    SpiralState *state;
    SpawnPosition *position;
    SpawnPosition *target_position;
    SpriteFrameState *sprite;
    s32 height;
    s32 coordinate;
    s32 coordinate_y;
    TileObject *origin;
    s32 offset;

    if (D_800249A4 != 0) return;
    node = (SpawnNode *)allocate_list_node(0x212, (ObjectNodeHeader **)anchor);
    if (node == 0) return;
    node->header.callback = update_spiraling_effect_growth_and_fade;
    register_node(node, (s32)D_800CEEFC);
    position = node->header.position;
    sprite = node->header.sprite;
    sprite->source = D_80024998;
    sprite->tpage_abr = 0x20;
    sprite->flags |= 0xC;
    state = &node->state;
    state->angle = angle;
    if (mirrored != 0) state->angle = angle + 0x800;
    state->reverse_angle = 0x1000 - state->angle;
    if (target == 0) {
        origin = &D_80082E80;
        offset = ((u32)angle >> 9) & 7;
        coordinate = ((origin->tile_position.parts.tile_x + dir_step_x[offset]) << 6) + 0x20;
        position->x = coordinate;
        state->x = coordinate;
        coordinate_y = ((origin->tile_position.parts.tile_y + dir_step_y[offset]) << 6) + 0x20;
        position->y = coordinate_y;
        state->y = coordinate_y;
        state->z = position->z.bits = (u16)D_800814A8->ground_height;
    } else {
        target_position = ((SpawnHeader *)target - 1)->position;
        state->x = position->x = target_position->x;
        state->y = position->y = target_position->y;
        state->z = target_position->z.bits;
        height = sample_terrain_surface_height(position->x, position->y, target_position->z.signed_value);
        if ((s16)height > 0x200) height = target_position->z.bits;
        position->z.bits = height;
    }
    state->target = target;
    state->lifetime = 0x40;
    state->mirrored = mirrored;
}

/* Processes both modes and sets completion flags on countdown expiry or an override. */
void process_effect_modes_and_completion(void *state)
{
    s32 object_addr;
    u16 countdown;
    u16 *counter_base = D_800249A6;
    object_addr = ((s32) state) - 0x20;
    spawn_spiraling(object_addr, *((s16 *) (((u8 *) state) + 0x26)), *((s16 *) (((u8 *) state) + 0x30)),
        D_800814A8->target, (counter_base[0]++, 0));
    spawn_spiraling(object_addr, *((s16 *) (((u8 *) state) + 0x26)), *((s16 *) (((u8 *) state) + 0x30)),
        D_800814A8->target, 1);
    countdown = (*((u16 *) (((u8 *) state) + 0x2C))) - 1;
    *((u16 *) (((u8 *) state) + 0x2C)) = countdown;
    if ((((s16) countdown) < 0) || (D_800249A4 != 0)) {
        *((u16 *) (((u8 *) state) - 2)) = (*((u16 *) (((u8 *) state) - 2))) | 0x8000;
        object_flag_block.flags = object_flag_block.flags | 0x8000;
    }
}

/* cfail-repair: tf7-phase1-cache-v3 */

typedef struct S_80024908_0 {
    u8 pad_00[0x10];
    void (*unk_10)(void *);
} S_80024908_0;

typedef struct S_80024908_1 {
    u8 pad_00[0xC];
    s32 unk_0C;
    u8 pad_10[0x16];
    s16 unk_26;
    u8 pad_28[0x4];
    s16 unk_2C;
    u8 pad_2E[0x2];
    s16 unk_30;
} S_80024908_1;

/* Allocate an object and initialize its handler and state fields. */
void allocate_and_initialize_effect_object(s32 alloc_arg, s16 value_26, s16 value_30, s32 value_0c) {
    void *object;
    S_80024908_1 *state;

    object = allocate_list_node(0x200, (ObjectNodeHeader **)alloc_arg);
    if (object != 0) {
        ((S_80024908_0 *)object)->unk_10 = process_effect_modes_and_completion;
        state = object + 0x20;
        state->unk_26 = value_26;
        state->unk_0C = value_0c;
        state->unk_30 = value_30;
        state->unk_2C = 0x40;
    }
}
