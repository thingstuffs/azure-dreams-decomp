#include "shared/audio_commands.h"
#include "common.h"
#include "shared/object_flags.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"
#include "dungeon/level.h"
#include "engine/scene.h"
#include "dungeon/effect/shade.h"
#include "sdk/libc.h"
#include "dungeon/system.h"

typedef union Fixed32 {
    s32 val;
    struct {
        u16 lo;
        s16 hi;
    } h;
} Fixed32;


typedef struct Owner {
    u8 pad0[0x2A];
    u16 flags;
    u8 pad2C[0x34];
    void *target;
    u8 pad64[0x24];
    s16 z;
} Owner;

typedef struct State {
    Owner *owner;
    void *field4;
    u8 pad8;
    u8 byte9;
    s16 state;
    s16 fieldC;
    s16 fieldE;
    s16 angle;
    s16 timer;
    s16 duration;
} State;

typedef struct Lookup {
    u8 pad0[8];
    void *field8;
    u8 padC[8];
    u16 flags;
    u8 pad16[14];
    u8 x;
    u8 y;
} Lookup;

typedef struct OwnerPrefix {
    u8 pad0[8];
    ObjectPosition *position;
    Lookup *lookup;
} OwnerPrefix;

typedef struct LargeInt {
    s32 value;
    s32 pad[2];
} LargeInt;

typedef struct StackLocals {
    ObjectPosition local;
    s16 diffs[3];
} StackLocals;


extern s32 create_random_variant_effect(State *, ObjectPosition *);
extern s32 check_layer_offset_height(s32, s32, s16, s32);
extern s32 create_scaled_rotation_effect(State *, ObjectPosition *);
extern void *create_motion_copy_sprite(State *, ObjectPosition *);
extern void interpolate_view_parameters(void *, u8, Owner *);


/* Updates an owner-directed movement sequence and its timed action states. */
void update_directed_movement_sequence(State *action, ObjectPosition *motion, ObjectPosition *aux_arg)
{
    ObjectPosition *aux_motion = aux_arg;
    OwnerPrefix *prefix;
    Owner *owner;
    s32 dispatch_state;
    s32 index;
    s32 next_state;
    StackLocals stack;
    ObjectPosition *position;
    u16 position_z;
    dispatch_state = action->state;
    owner = action->owner;
    action->timer++;
    switch (dispatch_state) {
    case 0:
        action->timer = 0;
        action->state++;
        action->angle = (owner->flags >> 9) & 7;
        aux_motion->velocity_x = 0x00808080;

    case 1:
        prefix = (OwnerPrefix *)((u8 *)owner - 0x20);
        if (resolve_record_orientation_or_fallback(prefix->lookup->field8, prefix->lookup, stack.diffs, 0) == 0 &&
            !(prefix->lookup->flags & 0x8000)) {
            break;
        }

        position = prefix->position;
        motion->x.w.i = position->x.w.i;
        motion->y.w.i = position->y.w.i;
        position_z = position->z.w.i;
        motion->z.w.i = position_z;

        if (!(prefix->lookup->flags & 0x8000)) {
            s16 adjusted_z;
            motion->x.w.i += stack.diffs[0];
            motion->y.w.i += stack.diffs[1];
            adjusted_z = (u16)motion->z.w.i;
            adjusted_z += (u16)stack.diffs[2];
            motion->z.w.i = adjusted_z;
        } else {
            motion->z.w.i = position_z - 64;
        }

        if (*(u16 *)action->field4 & 0x80) {
            ObjectPosition *target;
            if (owner->target != 0) {
                s32 x_delta;
                u8 *delta_iter;

                index = 1;

                target = *(ObjectPosition **)((u8 *)owner->target - 24);
                stack.diffs[0] = x_delta = abs(target->x.w.i - motion->x.w.i);
                stack.diffs[1] = abs(target->y.w.i - motion->y.w.i);
                stack.diffs[2] = abs(*(s16 *)((u8 *)owner->target + 0x88) - motion->z.w.i);

                action->duration = x_delta;
                do {
                    s32 signed_delta;
                    u32 delta_bits;

                    delta_iter = (u8 *)&stack.local + index * 2;
                    signed_delta = *(s16 *)(delta_iter + 24);
                    delta_bits = *(u16 *)(delta_iter + 24);
                    if (signed_delta > action->duration) {
                        action->duration = delta_bits;
                    }
                    index++;
                } while (index < 3);
                action->duration = action->duration >> 4;
                if (action->duration == 0) {
                    action->duration = 1;
                }

                motion->velocity_x = (target->x.v - motion->x.v) / action->duration;
                motion->velocity_y = (target->y.v - motion->y.v) / action->duration;
                motion->velocity_z =
                    ((*(s16 *)((u8 *)owner->target + 0x88) << 16) - motion->z.v) /
                    action->duration;
                create_random_variant_effect(action, motion);
                next_state = (u16)action->state + 1;
            } else {
                u16 path_x;
                u16 path_y;
                s16 grid_x;
                s16 grid_y;
                u16 last_x;
                u16 saved_y;
                s32 probe_z;
                s16 *step_y;
                s32 floor_height;
                s32 dest_x;
                s32 dest_y;

                index = 0;
                path_x = prefix->lookup->x;
                path_y = prefix->lookup->y;
                last_x = path_x;
                saved_y = path_y;
                while (index < 8) {
                    grid_x = (s16)path_x;
                    grid_y = (s16)path_y;
                    if ((s16)check_layer_offset_height((grid_x << 6) & 0xFFC0, (grid_y << 6) & 0xFFC0, owner->z,
                            (s16)(action->angle << 9)) != 0) {
                        break;
                    }
                    position = (ObjectPosition *)&dir_step_x[action->angle];
                    probe_z = (u16)owner->z;
                    probe_z -= 32;
                    probe_z = (u32)probe_z << 16;
                    probe_z >>= 16;
                    step_y = &dir_step_y[action->angle];
                    floor_height = sample_terrain_surface_height(((grid_x + *(s16 *)position) << 6) + 32 & 0xFFE0,
                        ((grid_y + *step_y) << 6) + 32 & 0xFFE0, probe_z);
                    if ((s16)floor_height >= 513 || (s16)(floor_height - owner->z) < -63) {
                        break;
                    }
                    index++;
                    path_x += dir_step_x[action->angle];
                    path_y += dir_step_y[action->angle];
                    saved_y = path_y;
                    last_x = path_x;
                }

                target = &stack.local;
                index = 1;
                dest_x = ((last_x << 16) >> 10) + ((dir_step_x[action->angle] + 1) << 5);
                target->x.w.i = dest_x;
                dest_y = ((saved_y << 16) >> 10) + ((dir_step_y[action->angle] + 1) << 5);
                target->y.w.i = dest_y;
                target->z.w.i = motion->z.w.i + 32;
                stack.diffs[0] = abs(target->x.w.i - motion->x.w.i);
                stack.diffs[1] = abs(target->y.w.i - motion->y.w.i);
                stack.diffs[2] = abs(target->z.w.i - motion->z.w.i);

                action->duration = stack.diffs[0];
                do {
                    s32 signed_delta;
                    u32 delta_bits;
                    u8 *delta_iter;

                    delta_iter = (u8 *)&stack.local + index * 2;
                    signed_delta = *(s16 *)(delta_iter + 24);
                    delta_bits = *(u16 *)(delta_iter + 24);
                    if (signed_delta > action->duration) {
                        action->duration = delta_bits;
                    }
                    index++;
                } while (index < 3);
                action->duration = action->duration >> 4;
                if (action->duration == 0) {
                    action->duration = 1;
                }

                motion->velocity_x = (target->x.v - motion->x.v) / action->duration;
                motion->velocity_y = (target->y.v - motion->y.v) / action->duration;
                motion->velocity_z = (target->z.v - motion->z.v) / action->duration;
                create_scaled_rotation_effect(action, motion);
                next_state = 6;
            }
            action->state = next_state;
            action->timer = 0;
        }
        break;

    case 2:
        motion->x.v += motion->velocity_x;
        motion->y.v += motion->velocity_y;
        motion->z.v += motion->velocity_z;
        if (action->timer >= action->duration) {
            play_sound_if_enabled(AUDIO_PLAY_CD_CUE);
            action->timer = 0;
            action->state++;
        }
        break;

    case 3:
        if (action->timer >= 12) {
            create_motion_copy_sprite(action, motion);
            action->timer = 0;
            action->state++;
        }
        break;

    case 4:
        if (action->timer >= 49) {
            interpolate_view_parameters(owner->target, action->byte9, owner);
            action->timer = 0;
            action->state++;
        }
        break;

    case 5:
        if (action->fieldC == 0) {
            g_dungeon_status.active_actor = 0;
            *(u16 *)((u8 *)action - 2) |= NODE_REMOVE;
            object_flag_block.flags |= OBJECT_REMOVE_PENDING;
        }
        break;

    case 6:
        motion->x.v += motion->velocity_x;
        motion->y.v += motion->velocity_y;
        motion->z.v += motion->velocity_z;
        if (action->timer >= action->duration) {
            action->state = 5;
            action->timer = 0;
        }
    }
    action->fieldC = 0;
}

