#include "common.h"
#include "shared/entity.h"
#include "shared/object_node.h"
#include "shared/sprite_frame_state.h"
#include "shared/tile_object.h"
#include "shared/entity_objects.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/object_flags.h"
#include "dungeon/effect/sprite.h"
#include "engine/node.h"
#include "engine/scene.h"
#include "sdk/libc.h"

typedef struct {
    s16 x;
    s16 y;
    s16 z;
} Vec3s;

typedef struct {
    s32 x;
    s32 y;
    s32 z;
} Vec3i;

/* Callback work after the object header. Angles retain both access signs;
 * target coordinates are reached over steps updates before the final fade. */
typedef struct FollowingColorEffect {
    u8 pad_00[8];
    ObjectNodeHeader *node;
    union { s16 s; u16 u; } angle_x, angle_y, angle_z;
    u8 pad_12[2];
    union { s16 s; u16 u; } target_x, target_y, target_z;
    u8 pad_1A[0x12];
    union { s16 s; u16 u; } phase;
    s16 chase_phase;
    union { s16 s; u16 u; } steps;
    u8 pad_32[2];
    u16 frame;
    u8 pad_36[2];
    s16 brightness_bias;
    s16 speed;
} FollowingColorEffect;

typedef struct FollowingColorPrefix { u16 flags; } FollowingColorPrefix;

extern void interpolate_view_parameters(void *, s16, Vec3i *);
extern void spawn_spiraling(s16 from_x, s16 from_y, s16 from_z, s16 to_x, s16 to_y, s16 to_z, s16 *angles);
extern s32 func_80025344(s16, s16, s16, s16);

extern u16 sprite_effect_update_count;
extern s32 linked_mesh_processor_address;
extern s32 *actor_direction_sprites;

/* Per-frame update for a following color effect: blend its position and shade toward a target node or a palette color, then fade it out over its lifetime. */
void update_following_color_blend_effect(FollowingColorEffect *state, ObjectPosition *pos, SpriteFrameState *tint) {
    Vec3s effect;
    Vec3i delta;
    Vec3s color;
    s32 diff;
    s32 iter;
    s16 steps;
    u16 fade;
    u16 raw;
    s16 phase;
    ObjectNodeHeader *node;
    ObjectPosition *target;
    SpriteFrameState *child;

    sprite_effect_update_count++;
    state->frame++;
    phase = state->phase.s;

    switch (phase) {
    case 0:
        register_node((u8 *)state - 0x20, &linked_mesh_processor_address);
        state->phase.u++;
    case 1:
        node = state->node;
        if (node == 0) {
            phase = state->chase_phase;
            if (phase == 0) {
                spawn_spiraling(
                    pos->x.w.i,
                    pos->y.w.i,
                    pos->z.w.i,
                    state->target_x.s,
                    state->target_y.s,
                    state->target_z.s,
                    &color);

                {
                    u16 value;
                    raw = state->angle_x.u;
                    value = (raw & 0x800) ? (raw | 0xF800) : (raw & 0x7FF);
                    state->angle_x.u = value;
                }
                {
                    u16 value;
                    raw = state->angle_y.u;
                    value = (raw & 0x800) ? (raw | 0xF800) : (raw & 0x7FF);
                    state->angle_y.u = value;
                }
                {
                    u16 value;
                    raw = state->angle_z.u;
                    value = (raw & 0x800) ? (raw | 0xF800) : (raw & 0x7FF);
                    state->angle_z.u = value;
                }
                {
                    u16 value;
                    raw = (u16)color.x;
                    value = (raw & 0x800) ? (raw | 0xF800) : (raw & 0x7FF);
                    color.x = value;
                }
                {
                    u16 value;
                    raw = (u16)color.y;
                    value = (raw & 0x800) ? (raw | 0xF800) : (raw & 0x7FF);
                    color.y = value;
                }
                {
                    u16 value;
                    raw = (u16)color.z;
                    value = (raw & 0x800) ? (raw | 0xF800) : (raw & 0x7FF);
                    color.z = value;
                }

                {
                    s32 currentValue;
                    s32 isClose;

                    diff = color.x;
                    currentValue = state->angle_x.s;
                    diff = diff - currentValue;
                    diff = abs(diff);
                    isClose = diff < 0x801;
                    currentValue = (u16)color.x;
                    if (!isClose) {
                        color.x = (state->angle_x.u & 0xF000) | (currentValue & 0xFFF);
                    }
                }

                {
                    s32 currentValue;
                    s32 isClose;

                    diff = color.y;
                    currentValue = state->angle_y.s;
                    diff = diff - currentValue;
                    diff = abs(diff);
                    isClose = diff < 0x801;
                    currentValue = (u16)color.y;
                    if (!isClose) {
                        color.y = (state->angle_y.u & 0xF000) | (currentValue & 0xFFF);
                    }
                }

                {
                    s32 isClose;

                    diff = color.z - state->angle_z.s;
                    diff = abs(diff);
                    isClose = diff < 0x801;
                    {
                        s32 rawValue;
                        s32 newValue;

                        rawValue = state->angle_z.u;
                        if (!isClose) {
                            newValue = rawValue & 0xF000;
                            newValue |= ((u16)color.z & 0xFFF);
                            color.z = newValue;
                        }
                    }
                }

                state->angle_x.u += (color.x - state->angle_x.s) >> 2;
                state->angle_y.u += (color.y - state->angle_y.s) >> 2;
                state->angle_z.u += (color.z - state->angle_z.s) >> 2;

                interpolate_view_parameters(&state->angle_x, state->speed, &delta);
                pos->x.v += delta.x;
                pos->y.v += delta.y;
                pos->z.v += delta.z;

                state->speed = 0xA0;
                state->steps.u--;
                if (state->steps.s <= 0) {
                    ObjectPosition *base = &view_reference_entity;
                    s32 tableAddress;
                    color.x = *(u16 *)&base->x.w.i;
                    color.y = *(u16 *)&base->y.w.i;
                    color.z = (u16)dungeon_actor_ring_anchor->ground_height - 0x50;
                    tableAddress =
                        ((g_game_work.view.camera_rotation.parts.viewAngle + dungeon_actor_ring_anchor->facing + 0x100) >> 7) & 0x1C;
                    tableAddress += (s32)actor_direction_sprites;
                    resolve_record_orientation_or_fallback(
                        *(s32 *)tableAddress,
                        ((u8 *)(&reference_tile_object)),
                        &effect,
                        0);
                    color.x += effect.x;
                    state->target_x.s = color.x;
                    color.y += effect.y;
                    state->target_y.s = color.y;
                    color.z += effect.z;
                    state->target_z.s = color.z;
                    state->chase_phase = 1;
                    state->steps.s = 8;
                }
                {
                    u32 shade;
                    shade = tint->color.c.r;
                    if (shade < 0x80) {
                        tint->color.word += 0x00080808;
                    }
                }
            } else if (phase == 1) {
                steps = state->steps.s;
                if (steps > 0) {
                    pos->x.w.i += (state->target_x.s - pos->x.w.i) / steps;
                    pos->y.w.i += (state->target_y.s - pos->y.w.i) / state->steps.s;
                    pos->z.w.i += (state->target_z.s - pos->z.w.i) / state->steps.s;
                }
                state->steps.u--;
                if (state->steps.s <= 0) {
                    state->steps.s = 0;
                    pos->x.w.i = state->target_x.u;
                    pos->y.w.i = state->target_y.u;
                    pos->z.w.i = state->target_z.u;
                    if (func_80025344(
                            state->target_x.s,
                            state->target_y.s,
                            (s16)(state->target_z.u + 0x10),
                            0)) {
                        iter = 3;
                        do {
                            func_80025344(
                                state->target_x.s,
                                state->target_y.s,
                                (s16)(state->target_z.u + 0x10),
                                (s16)iter);
                            iter--;
                        } while (iter >= 2);
                        state->steps.s = 8;
                        state->phase.u++;
                    }
                }
            }
            if (state->frame & 1) {
                pos->velocity_x += (pos->x.v - pos->velocity_x) >> 2;
                pos->velocity_y += (pos->y.v - pos->velocity_y) >> 2;
                pos->velocity_z += (pos->z.v - pos->velocity_z) >> 2;
            }
            return;
        }
        if (node->flags & 0x8000) {
            state->steps.s = 2;
            state->phase.u++;
        }
        node = state->node;
        target = node->position;
        pos->x.v += (target->x.v - pos->x.v) >> 2;
        pos->y.v += (target->y.v - pos->y.v) >> 2;
        pos->z.v += (target->z.v - pos->z.v) >> 2;

        if (state->frame & 1) {
            pos->velocity_x += (pos->x.v - pos->velocity_x) >> 2;
            pos->velocity_y += (pos->y.v - pos->velocity_y) >> 2;
            pos->velocity_z += (pos->z.v - pos->velocity_z) >> 2;
        }

        node = state->node;
        child = node->sprite;
        if (child->color.c.r < tint->color.c.r) {
            tint->color.c.r = child->color.c.r;
        }
        if (child->color.c.g < tint->color.c.g) {
            tint->color.c.g = child->color.c.g;
        }
        if (child->color.c.b < tint->color.c.b) {
            tint->color.c.b = child->color.c.b;
        }
        if ((s32)tint->color.c.r < 0x80 - (state->brightness_bias * 8)) {
            tint->color.word += 0x00080808;
        }
        return;
    case 2:
        if (state->frame & 1) {
            pos->velocity_x += (pos->x.v - pos->velocity_x) >> 2;
            pos->velocity_y += (pos->y.v - pos->velocity_y) >> 2;
            pos->velocity_z += (pos->z.v - pos->velocity_z) >> 2;
        }
        fade = tint->color.c.r;
        fade -= fade / state->steps.s;
        tint->color.c.r = fade;
        tint->color.c.g = fade;
        tint->color.c.b = fade;
        state->steps.u--;
        if (state->steps.s <= 0) {
            ((FollowingColorPrefix *)state)[-1].flags |= 0x8000;
            object_flag_block.flags |= OBJECT_REMOVE_PENDING;
        }
    }
}
