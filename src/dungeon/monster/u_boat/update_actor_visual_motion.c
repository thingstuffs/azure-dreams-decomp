#include "common.h"
#include "shared/dir_step.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/sprite_frame_state.h"
#include "dungeon/level.h"

typedef void (*Callback)(void *, void *, void *, void *);

extern u8 uboat_default_frames[];
#include "dungeon/monster/u_boat.h"
#include "dungeon/actor.h"
#include "dungeon/item.h"
#include "engine/texture.h"
#include "sdk/libgte.h"
#include "slus.h"
extern Callback uboat_callbacks[];

extern s32 refresh_actor_facing_and_lifecycle(void *, void *, void *, void *);

   /* part in update_actor_visual_motion */

typedef struct S_801711B0_2 {
    u8 pad_00[0x1C];
    u32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x5C];
    u16 unk_88;
} S_801711B0_2;   /* base in update_actor_visual_motion */

/* Update object callbacks, motion, facing, and ground-relative height. */
/* Runs U-Boat's callbacks, facing, and motion, adds idle bobbing, and resolves falling and
 * terrain-relative height. */
void update_actor_visual_motion(ActorRecord *body, ObjectPosition *motion_arg, SpriteFrameState *sprite)
{
    S_801711B0_2 *base = (S_801711B0_2 *)body;
    s16 state_or_dir;
    s32 direction;
    s32 prior_state;
    s32 update_value_2;
    void *check_obj;
    void *check_motion;
    void *check_part;
    void *check_context;
    u16 part_flags;
    ActorActionHandler paused_callback;
    ActorActionHandler callback;
    s32 new_state;
    s16 ground_height;
    s32 flags;
    s32 normal_flags;
    s32 special_flags;
    u16 new_part_flags;
    u16 bob_step;
    s32 bob_phase;

    if (g_dungeon_status.flags & 0x2000) {
        paused_callback = body->unk_8C.handler;
        if (paused_callback == (Callback)uboat_behavior_entry) {
            void *callback_obj = body;

            paused_callback(callback_obj, motion_arg, sprite, callback_obj);
            return;
        }
        body->movement_queue_state &= 0x7F;
        return;
    }

    check_obj = body;
    check_motion = motion_arg;
    check_part = sprite;
    update_value_2 = (*((u8 *)body + (0x6D)));
    check_context = body;
    state_or_dir = (s8)update_value_2;
    if (refresh_actor_facing_and_lifecycle(check_obj, check_motion, check_part, check_context) != 0) {
        return;
    }

    callback = body->unk_8C.handler;
    if (callback != 0) {
        callback(body, motion_arg, sprite, body);
    }
    uboat_callbacks[body->action_id.u](body, motion_arg, sprite, body);

    prior_state = (s32)state_or_dir << 16;
    new_state = body->pending_turn_updates;
    prior_state >>= 16;
    if (prior_state != new_state) {
        try_move_actor_to_valid_position(body, motion_arg, sprite, body);
    }

    motion_arg->x.v += motion_arg->velocity_x;
    motion_arg->y.v += motion_arg->velocity_y;

    if (!((*(u32 *)((u8 *)body + (0x1C))) & 0x40000) &&
        !(body->action_state_flags & 8)) {
        motion_arg->velocity_z += body->unk_9D.s * 0x14000;
        body->unk_9D.u++;
    } else {
        body->unk_9D.u = 0;
    }
    body->unk_90.value += motion_arg->velocity_z;
    part_flags = sprite->flags;

    if (!(part_flags & 0x8000)) {
        u16 facing_flags;

        direction = ((g_game_work.view.camera_rotation.parts.viewAngle + base->unk_2A + 0x100) >> 9) & 7;
        state_or_dir = direction;
        if (body->unk_94 != state_or_dir) {
            select_indirect_table_entry(sprite,
                (*((u8 *)(*(unsigned char **)&sprite->frameTable) + (state_or_dir))),
                sprite->unk_04);
            body->unk_94 = direction;
        }

        if (dir_sprite_flag[state_or_dir] != 0) {
            facing_flags = sprite->flags;
            facing_flags |= 1;
        } else {
            facing_flags = sprite->flags & 0xFFFE;
        }
        sprite->flags = facing_flags;

        apply_monster_koyaw_data(base->unk_1C, (u8 *)sprite + 0xC);
        if (!(base->unk_1C & 0x20)) {
            if (!(sprite->flags & 0x40)) {
                advance_sprite_animation_and_textures(sprite);
            }
        } else {
            sprite->flags |= 0x7000;
            base->unk_1C &= 0xFFFBFFFF;
        }

        normal_flags = base->unk_1C & 0xF7FFFFFF;
        base->unk_1C = normal_flags;
        if (normal_flags & 0x40000) {
            if (!(sprite->flags & 0x40) &&
                *(unsigned char **)&sprite->frameTable == uboat_default_frames) {
                s32 bob_signed;

                bob_step = body->unk_9E.u++;
                bob_signed = (s32)bob_step << 16;
                bob_signed >>= 16;
                bob_phase = bob_signed * 0x55;
                body->unk_A0.value +=
                    rsin(bob_phase) << 4;
            }

            ground_height = -0x20;
            if (!(body->action_state_flags & 8)) {
                if (ground_height < body->unk_90.parts.high.s) {
                    body->unk_90.parts.high.u = body->unk_90.parts.high.u - 8;
                } else {
                    if (body->unk_90.parts.high.s < -0x28) {
                        body->unk_90.parts.high.u = body->unk_90.parts.high.u + 8;
                    }
                }
            }
        } else {
            s32 bob_offset = body->unk_A0.value;
            body->unk_9E.u = 0;
            body->unk_A0.value = 0;
            body->unk_90.value -= bob_offset;
            if (!(body->action_state_flags & 8)) {
                ground_height = sample_terrain_surface_height(((u16) motion_arg->x.w.i),
                                      ((u16) motion_arg->y.w.i),
                                      (s16)(base->unk_88 - 0x20)) -
                        base->unk_88;
                if (ground_height < body->unk_90.parts.high.s) {
                    body->unk_90.parts.high.s = ground_height;
                    body->unk_9D.u = 0;
                    motion_arg->velocity_z = 0;
                    base->unk_1C |= 0x08000000;
                }
            }
        }
    } else {
        new_part_flags = part_flags & 0x800;
        if (new_part_flags) {
            sprite->flags = part_flags & 0x8FFF;
        } else {
            sprite->flags = part_flags | 0x7000;
        }

        special_flags = base->unk_1C & 0xF7FFFFFF;
        base->unk_1C = special_flags;
        if (!(special_flags & 0x40000)) {
            s32 bob_offset = body->unk_A0.value;
            body->unk_9E.u = 0;
            body->unk_A0.value = 0;
            body->unk_90.value -= bob_offset;
            if (!(body->action_state_flags & 8)) {
                ground_height = sample_terrain_surface_height(((u16) motion_arg->x.w.i),
                                      ((u16) motion_arg->y.w.i),
                                      (s16)(base->unk_88 - 0x20)) -
                        base->unk_88;
                if (ground_height < body->unk_90.parts.high.s) {
                    body->unk_90.parts.high.s = ground_height;
                    body->unk_9D.u = 0;
                    motion_arg->velocity_z = 0;
                    base->unk_1C |= 0x08000000;
                }
            }
        } else {
            if (!(sprite->flags & 0x40) &&
                *(unsigned char **)&sprite->frameTable == uboat_default_frames) {
                s32 bob_signed;

                bob_step = body->unk_9E.u++;
                bob_signed = (s32)bob_step << 16;
                bob_signed >>= 16;
                bob_phase = bob_signed * 0x55;
                body->unk_A0.value +=
                    rsin(bob_phase) << 4;
            }

            ground_height = -0x20;
            if (!(body->action_state_flags & 8)) {
                if (ground_height < body->unk_90.parts.high.s) {
                    body->unk_90.parts.high.u = body->unk_90.parts.high.u - 8;
                } else if (body->unk_90.parts.high.s < -0x28) {
                    body->unk_90.parts.high.u = body->unk_90.parts.high.u + 8;
                }
            }
        }

        if (body->unk_B4.bytes[1] != 0) {
            body->unk_90.parts.high.u = 0;
        }
    }

    flags = base->unk_1C;
    if (flags & 0x40000000) {
        base->unk_1C = flags & 0xBFFFFFFF;
        ground_height = sample_terrain_surface_height(
            (sprite->tile_x << 6) | 0x20,
            (sprite->tile_y << 6) | 0x20,
            (s16)(base->unk_88 - 0x20));
        if (ground_height < 0x200) {
            body->unk_90.parts.high.u += base->unk_88 - ground_height;
            base->unk_88 = ground_height;
        }
    }

    motion_arg->z.w.i = base->unk_88 +
        body->unk_90.parts.high.u - body->unk_A0.parts.high;
    sprite->flags |= 0x40;
}
