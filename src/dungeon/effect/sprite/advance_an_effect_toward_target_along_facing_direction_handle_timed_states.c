#include "shared/entity.h"
#include "shared/object_node.h"
#include "shared/sprite_frame_state.h"
#include "shared/audio_commands.h"
#include "shared/entity_height_offsets.h"
#include "common.h"
#include "shared/object_flags.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"
extern int abs(int);

typedef struct MotionWork {
    ObjectPosition destination;
    s16 probe_delta[3];
} MotionWork;

typedef struct Position16 {
    u16 pad0;
    s16 x;
    u16 pad4;
    s16 y;
    u16 pad8;
    s16 z;
} Position16;

typedef struct EffectState {
    ActorRecord *owner;
    void *image;
    u8 unk8;
    u8 id;
    s16 state;
    s16 unkC;
    s16 direction;
    s16 timer;
    s16 duration;
    s16 done;
    s16 unk16;
    void *target;
} EffectState;

#define U8_AT(p, n) (*(u8 *)((u8 *)(p) + (n)))
#define S16_AT(p, n) (*(s16 *)((u8 *)(p) + (n)))
#define U16_AT(p, n) (*(u16 *)((u8 *)(p) + (n)))


extern s32 resolve_record_orientation_or_fallback(void *, void *, void *, s32);
extern s32 check_layer_offset_height(s32, s32, s32, s32);
extern u16 sample_terrain_surface_height(s32 x, s32 y, s16 min_height);
extern void func_80025344(EffectState *, ObjectPosition *);
extern void advance_grayscale_fade(EffectState *, ObjectPosition *);
extern void play_sound_if_enabled(s32);
extern void interpolate_view_parameters(void *, u8, void *);


/* Advance an effect toward its target or along its facing direction, then handle its timed states. */
void advance_an_effect_toward_target_along_facing_direction_handle_timed_states(EffectState *state, ObjectPosition *motion, register SpriteFrameState *part) {
    ActorRecord *owner;
    u8 *color_part;
    ObjectNodeHeader *owner_meta;
    SpriteFrameState *owner_node;
    void *source_motion;
    ObjectPosition *target_pos;
    Position16 *table_x_entry;
    MotionWork work;
    s32 index;
    s32 state_index;
    u16 timer_value;
    s32 motion_x;
    s32 z_distance;
    s32 next_state;
    u32 color;
    s32 x_distance;
    s16 source_z;
    u16 ground_z;
    u16 tile_x;
    u16 tile_y;
    s16 grid_x;
    s16 grid_y;
    s16 *table_y_entry;
    s32 probe_z;
    s32 dest_x;
    s32 dest_y;
    u16 end_tile_x;
    u16 end_tile_y;
    timer_value = state->timer;
    state_index = state->state;
    timer_value++;
    owner = state->owner;
    state->timer = timer_value;

    switch (state_index) {
    case 0:
    color = 0x00808080;
    state->timer = 0;
    state->state++;
    state->direction = ((u16)owner->facing >> 9) & 7;
    part->color.word = color;

    case 1:
    owner_meta = (ObjectNodeHeader *)((u8 *)owner - 0x20);
    owner_node = owner_meta->sprite;
    if (!resolve_record_orientation_or_fallback(owner_node->source, owner_node, work.probe_delta, 0)) {
        if (!(owner_meta->sprite->flags & 0x8000)) {
            break;
        }
    }

    source_motion = owner_meta->position;
    table_x_entry = (Position16 *)source_motion;
    motion->x.w.i = table_x_entry->x;
    motion->y.w.i = table_x_entry->y;
    source_z = table_x_entry->z;
    motion->z.w.i = source_z;

    if (!(owner_meta->sprite->flags & 0x8000)) {
        motion->x.w.i += work.probe_delta[0];
        motion->y.w.i += work.probe_delta[1];
        motion->z.w.i = motion->z.w.i + work.probe_delta[2];
    } else {
        motion->z.w.i = source_z - 0x40;
    }
    if (!(U16_AT(state->image, 0) & 0x80)) {
        break;
    }

    index = 1;
    if (owner->target != 0) {
        state->target = owner->target;
        target_pos = ((ObjectNodeHeader *)((u8 *)owner->target - 0x20))->position;

        motion_x = motion->x.w.i;
        x_distance = target_pos->x.w.i - motion_x;
        x_distance = abs(x_distance);
        work.probe_delta[0] = x_distance;

        {
            s32 y_delta = target_pos->y.w.i;
            s32 motion_y = motion->y.w.i;
            color_part = (u8 *)&work.destination + 2;
            y_delta -= motion_y;
            y_delta = abs(y_delta);
            work.probe_delta[1] = y_delta;
        }

        z_distance = target_pos->z.w.i -
                entity_height_offsets[U8_AT(state->target, 0x13)] - motion->z.w.i;
        z_distance = abs(z_distance);
        work.probe_delta[2] = z_distance;

        state->duration = x_distance;
        for (; index < 3; index++, color_part += 2) {
            if (S16_AT(color_part, 0x18) > state->duration) {
                state->duration = (u16)S16_AT(color_part, 0x18);
            }
        }
        state->duration = (s16)state->duration >> 4;
        if (state->duration == 0) {
            state->duration = 1;
        }

        motion->velocity_x = (target_pos->x.v - motion->x.v) / state->duration;
        motion->velocity_y = (target_pos->y.v - motion->y.v) / state->duration;
        motion->velocity_z = (target_pos->z.v -
                      (((entity_height_offsets[U8_AT(state->target, 0x13)] >> 1) * 3) << 16) -
                      motion->z.v) / state->duration;
        func_80025344(state, motion);
        next_state = (u16)state->state + 1;
    } else {
        index = 0;
        {
            SpriteFrameState *tile_node;
            tile_node = owner_meta->sprite;
            tile_x = tile_node->tile_x;
            tile_y = tile_node->tile_y;
        }
        end_tile_x = tile_x;
        end_tile_y = tile_y;

        while (index < 8) {
            grid_x = (s16)tile_x;
            grid_y = (s16)tile_y;
            if ((s16)check_layer_offset_height((grid_x << 6) & 0xFFC0,
                                   (grid_y << 6) & 0xFFC0,
                                   owner->ground_height,
                                   (s16)(state->direction << 9)) != 0) {
                break;
            }
            table_x_entry = (Position16 *)&dir_step_x[state->direction];
            probe_z = (u16)owner->ground_height;
            probe_z -= 0x20;
            probe_z = (u32)probe_z << 16;
            probe_z >>= 16;
            table_y_entry = &dir_step_y[state->direction];
            ground_z = sample_terrain_surface_height(
                ((grid_x + *((s16 *)table_x_entry)) << 6) + 0x20 & 0xFFE0,
                ((grid_y + *table_y_entry) << 6) + 0x20 & 0xFFE0,
                probe_z);
            if ((s16)ground_z >= 0x201 || (s16)(ground_z - (u16)owner->ground_height) < -0x3F) {
                break;
            }
            index++;
            tile_x += dir_step_x[state->direction];
            tile_y += dir_step_y[state->direction];
            end_tile_y = tile_y;
            end_tile_x = tile_x;
        }

        target_pos = &work.destination;
        index = 1;
        color_part = (u8 *)&work.destination + 2;
        dest_x = ((end_tile_x << 16) >> 10) + ((dir_step_x[state->direction] + 1) << 5);
        target_pos->x.w.i = dest_x;
        dest_y = ((end_tile_y << 16) >> 10) + ((dir_step_y[state->direction] + 1) << 5);
        target_pos->y.w.i = dest_y;
        target_pos->z.w.i = motion->z.w.i + 0x20;
        work.probe_delta[0] = abs(target_pos->x.w.i - motion->x.w.i);
        work.probe_delta[1] = abs(target_pos->y.w.i - motion->y.w.i);
        work.probe_delta[2] = abs(target_pos->z.w.i - motion->z.w.i);

        state->duration = work.probe_delta[0];
        for (; index < 3; index++, color_part += 2) {
            if (S16_AT(color_part, 0x18) > state->duration) {
                state->duration = (u16)S16_AT(color_part, 0x18);
            }
        }
        state->duration = (s16)state->duration >> 4;
        if (state->duration == 0) {
            state->duration = 1;
        }

        motion->velocity_x = (target_pos->x.v - motion->x.v) / state->duration;
        motion->velocity_y = (target_pos->y.v - motion->y.v) / state->duration;
        motion->velocity_z = (target_pos->z.v - motion->z.v) / state->duration;
        advance_grayscale_fade(state, motion);
        next_state = 6;
    }
    state->state = next_state;
    state->timer = 0;
    break;

    case 2:
    motion->x.v += motion->velocity_x;
    motion->y.v += motion->velocity_y;
    motion->z.v += motion->velocity_z;
    if (state->timer < state->duration) {
        break;
    }
    play_sound_if_enabled(AUDIO_PLAY_CD_CUE);
    state->state++;
    state->timer = 0;
    break;

    case 3:
    if (state->timer < 0x10) {
        break;
    }
    state->state++;
    state->timer = 0;
    break;

    case 4:
    if (state->timer < 0x30) {
        break;
    }
    interpolate_view_parameters(owner->target, state->id, owner);
    state->state++;
    state->timer = 0;
    break;

    case 5:
    if (state->done != 0) {
        break;
    }
    g_dungeon_status.active_actor = 0;
    U16_AT(state, -2) |= NODE_REMOVE;
    object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    break;

    case 6:
    motion->x.v += motion->velocity_x;
    motion->y.v += motion->velocity_y;
    motion->z.v += motion->velocity_z;
    if (state->timer >= state->duration) {
        state->state = 5;
        state->timer = 0;
    }
    break;

    default:
        break;
    }
    state->done = 0;
}
