#include "shared/audio_commands.h"
/* Effect texture loading, target tinting, and spiraling model effects with completion tracking. */
#include "dungeon/effect/motion/update_directional_actor_effect.h"
#include "shared/object_node.h"
#include "shared/sprite_frame_state.h"
#include "dungeon/effect/motion/update_directional_actor_effect.h"
#include "common.h"
#include "shared/tile_object.h"
#include "shared/record_ptrs.h"
#include "shared/object_flags.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"
#include "dungeon/effect/motion.h"

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

/* Loads effect textures, launches a model effect, darkens and restores its target, and waits for
   completion. */
void update_directional_actor_effect(void *effect, void *color_data) {
    GpuRectBuffer upload_rect;
    s16 delay_left;
    s16 fade_left;
    s32 stage;
    S_8195281C_5 *model;
    SpriteFrameState *model_colors;
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
        upload_rect.words[0] = 0x01000340;
        upload_rect.words[1] = 0x200020;
        draw_textured_ellipse(D_800DF334, &upload_rect.rect, 1, 0);
        upload_rect.words[0] = 0x01000360;
        draw_textured_ellipse(D_80024980, &upload_rect.rect, 1, 0);
        ((S_8195281C_10 *)(((S_8195281C_1 *)((int *)(&primary_actor_record)))->unk_00.i))->unk_F4 = directional_effect_sprite_data;
        create_timed_model_effect(((S_8195281C_0 *)effect)->unk_00 - 0x20, ((S_8195281C_0 *)effect)->unk_04, 0, 0);
        ((S_8195281C_0 *)effect)->unk_0A.s = (s16) ((u16) ((S_8195281C_0 *)effect)->unk_0A.s + 1);
    case 1:
        actor_slot = (void **) ((int *)(&primary_actor_record));
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
            play_sound_if_enabled(AUDIO_PLAY_CD_CUE);
        }
        delay_left = (u16) ((S_8195281C_0 *)effect)->unk_18 - 1;
        ((S_8195281C_0 *)effect)->unk_18 = delay_left;
        if ((delay_left << 0x10) > 0) {
            break;
        }
        model_owner = ((S_8195281C_1 *)((int *)(&primary_actor_record)))->unk_00.p;
        ((S_8195281C_0 *)effect)->unk_18 = 0x20;
        allocate_and_initialize_effect_object(effect - 0x20, ((S_8195281C_0 *)effect)->unk_14.s, ((S_8195281C_0 *)effect)->unk_09,
            model_owner->unk_60);
        ((S_8195281C_0 *)effect)->unk_0A.s = (u16) ((S_8195281C_0 *)effect)->unk_0A.s + 1;
        break;
    case 3:
        model = ((S_8195281C_10 *)(((S_8195281C_1 *)((int *)(&primary_actor_record)))->unk_00.i))->unk_60;
        if (model != 0) {
            model_colors = NODE_HEADER(model)->sprite;
            model->unk_1C = (s32) (model->unk_1C | 0x10000000);
            model_colors->color.c.r = (u8) (model_colors->color.c.r - 4);
            model_colors->color.c.g = (u8) (model_colors->color.c.g - 4);
            model_colors->color.c.b = (u8) (model_colors->color.c.b - 4);
            if ((u8) model_colors->color.c.r < 0x20U) {
                model_colors->color.c.r = 0x20U;
            }
            if ((u8) model_colors->color.c.g < 0x20U) {
                model_colors->color.c.g = 0x20U;
            }
            if ((u8) model_colors->color.c.b < 0x20U) {
                model_colors->color.c.b = 0x20U;
            }
        }
        if (!(reference_tile_object.sprite_flags & 0x8000)) {
            fade_left = (u16) ((S_8195281C_0 *)effect)->unk_18 - 1;
            ((S_8195281C_0 *)effect)->unk_18 = fade_left;
            if ((fade_left << 0x10) >= 0) {
                break;
            }
        }
        model = dungeon_actor_ring_anchor->target;
        if (model != 0) {
            model_colors = NODE_HEADER(model)->sprite;
            model_colors->color.word = 0x808080;
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
        object_flag_block.flags =
            (s32) (object_flag_block.flags | 0x8000);
    }
    D_800249A6[0] = 0;
    return;
}


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
void update_spiraling_effect_growth_and_fade(SpiralingBody *effect, ObjectPosition *position, SpriteFrameState *sprite_arg)
{
    SpriteFrameState *sprite = sprite_arg;
    s16 state;
    s16 radius;
    s16 frames_left;
    s32 velocity_x;
    s32 velocity_y;
    s32 global_flags;
    u16 scale;
    u8 brightness;

    D_800249A6[0]++;

    if (D_800249A4 != 0 && effect->unk_24.s < 2) {
        effect->unk_00 =
            rcos(effect->unk_28.s) *
            effect->unk_34 * 8;
        effect->unk_04 =
            rsin(effect->unk_28.s) *
            effect->unk_34 * 8;
        effect->unk_24.s = 2;
    }

    ((S_81952B4C_1 *)position)->unk_0E = position->x.unsigned_parts.integer;
    ((S_81952B4C_1 *)position)->unk_12 = position->y.unsigned_parts.integer;
    ((S_81952B4C_1 *)position)->unk_16 = position->z.unsigned_parts.integer;

    state = effect->unk_24.s;
    switch (state) {
    case 0:
        scale = sprite->scale_y;
        scale += (0x1000 - scale) / effect->unk_2C;
        sprite->scale_y = scale;
        sprite->scale_x = scale;
        if (scale >= 0x801) {
            sprite->scale_y = 0x800;
            sprite->scale_x = 0x800;
        }

        brightness = sprite->color.c.b + 2;
        sprite->color.c.b = brightness;
        sprite->color.c.g = brightness;
        sprite->color.c.r = brightness;
        if (brightness >= 0x81) {
            sprite->color.word = 0x00808080;
        }

        position->x.v =
            (effect->unk_10 << 16) +
            rcos(effect->unk_28.s) *
            effect->unk_34 * 8;
        position->y.v =
            (effect->unk_12 << 16) +
            rsin(effect->unk_28.s) *
            effect->unk_34 * 8;

        effect->unk_08 -= 0x5000;
        radius = (u16)effect->unk_34 + 4;
        effect->unk_34 = radius;
        if (radius >= 0x41) {
            effect->unk_34 = 0x40;
        }

        effect->unk_28.u += 0x180;
        frames_left = (u16)effect->unk_2C - 1;
        effect->unk_2C = frames_left;
        if ((frames_left << 16) <= 0) {
            effect->unk_24.u++;
        }

        break;
    case 1:
        break;
    case 2:
        velocity_x = effect->unk_00;
        velocity_y = effect->unk_04;
        effect->unk_00 = velocity_x + (velocity_x >> 1);
        effect->unk_04 = velocity_y + (velocity_y >> 1);
        effect->unk_08 += 0x10000;

        brightness = sprite->color.c.b - 4;
        sprite->color.c.b = brightness;
        sprite->color.c.g = brightness;
        sprite->color.c.r = brightness;
        if ((s8)brightness <= 0) {
            (*(u16 *)((u8 *)effect + -2)) |= NODE_REMOVE;
            global_flags = object_flag_block.flags | OBJECT_REMOVE_PENDING;
            effect->unk_24.u++;
            object_flag_block.flags = global_flags;
            return;
        }

        break;
    }

    effect->unk_2A++;
    position->x.v += effect->unk_00;
    position->y.v += effect->unk_04;
    position->z.v += effect->unk_08;
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
    node = allocate_list_node(0x212, (ObjectNodeHeader **)anchor);
    if (node == 0) return;
    node->header.callback = (void (*)(void *, void *, void *))update_spiraling_effect_growth_and_fade;
    register_node(node, linked_mesh_processor_address);
    position = node->header.position;
    sprite = node->header.sprite;
    sprite->source = directional_effect_sprite_data;
    sprite->tpage_abr = 0x20;
    sprite->flags |= 0xC;
    state = &node->state;
    state->angle = angle;
    if (mirrored != 0) state->angle = angle + 0x800;
    state->reverse_angle = 0x1000 - state->angle;
    if (target == 0) {
        origin = &reference_tile_object;
        offset = ((u32)angle >> 9) & 7;
        coordinate = ((origin->tile_position.parts.tile_x + dir_step_x[offset]) << 6) + 0x20;
        position->x = coordinate;
        state->x = coordinate;
        coordinate_y = ((origin->tile_position.parts.tile_y + dir_step_y[offset]) << 6) + 0x20;
        position->y = coordinate_y;
        state->y = coordinate_y;
        state->z = position->z.bits = (u16)primary_actor_record->ground_height;
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
    AndInitializeEffectObjectBody *effect_state = state;
    u8 * object_addr;
    u16 countdown;
    u16 *counter_base = D_800249A6;
    object_addr = (u8 *)state - 0x20;
    spawn_spiraling(object_addr, effect_state->unk_26, effect_state->unk_30,
        primary_actor_record->target, (counter_base[0]++, 0));
    spawn_spiraling(object_addr, effect_state->unk_26, effect_state->unk_30,
        primary_actor_record->target, 1);
    countdown = effect_state->unk_2C - 1;
    effect_state->unk_2C = countdown;
    if ((((s16) countdown) < 0) || (D_800249A4 != 0)) {
        *((u16 *) (((u8 *) state) - 2)) = (*((u16 *) (((u8 *) state) - 2))) | NODE_REMOVE;
        object_flag_block.flags = object_flag_block.flags | OBJECT_REMOVE_PENDING;
    }
}

/* cfail-repair: tf7-phase1-cache-v3 */


/* Allocate an object and initialize its handler and state fields. */
void allocate_and_initialize_effect_object(s32 alloc_arg, s16 value_26, s16 value_30, ActorRecord *value_0c) {
    ObjectNodeHeader *object;
    AndInitializeEffectObjectBody *state;

    object = allocate_list_node(0x200, (ObjectNodeHeader **)alloc_arg);
    if (object != 0) {
        object->update_callback = process_effect_modes_and_completion;
        state = NODE_BODY(object);
        state->unk_26 = value_26;
        state->unk_0C = value_0c;
        state->unk_30 = value_30;
        state->unk_2C = 0x40;
    }
}
