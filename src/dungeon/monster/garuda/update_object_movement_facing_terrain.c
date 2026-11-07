#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/dir_step.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "dungeon/monster/garuda.h"
#include "dungeon/level.h"
#include "dungeon/item.h"
#include "engine/texture.h"
#include "dungeon/actor.h"
#include "sdk/libgte.h"

typedef void (*Callback)(void *, void *, void *, void *);

extern u8 garuda_walk_direction_frames[9];
extern Callback garuda_callbacks[];

extern void advance_sprite_animation_and_textures(void *);
extern s32 refresh_actor_facing_and_lifecycle(void *, void *, void *, void *);

/* Updates object callbacks, movement, facing, and terrain-relative height. */
void update_object_movement_facing_terrain(ActorRecord *body, ObjectPosition *motion, SpriteFrameState *sprite)
{
    ActorRecord *state = body;
    s32 mode_or_dir;
    s32 direction;
    u32 value_bits;
    u32 state_mask_a;
    u32 state_mask_b;
    ActorActionHandler callback;
    s32 height_offset;
    s16 floor_delta;
    u16 part_flags;
    u16 bob_phase;
    s32 bob_offset;
    u8 direction_flag;
    s16 saved_mode;

    if (g_dungeon_status.flags & 0x2000) {
        callback = body->unk_8C.handler;
        if (callback == update_creature_animation_action) {
            void *entry_obj = body;
            callback(entry_obj, motion, sprite, entry_obj);
            return;
        } else {
            (body->movement_queue_state) &= 0x7F;
            return;
        }
    }

    saved_mode = body->pending_turn_updates;
    if (refresh_actor_facing_and_lifecycle(body, motion, sprite, body) != 0) {
        return;
    }

    {
        ActorActionHandler update_callback;
        update_callback = body->unk_8C.handler;
        if (update_callback != 0) {
            update_callback(body, motion, sprite, body);
        }
    }
    garuda_callbacks[(body->action_id)](body, motion, sprite, body);
    if (saved_mode != (body->pending_turn_updates)) {
        try_move_actor_to_valid_position(body, motion, sprite, body);
    }

    {
        s32 old_x = motion->x.v;
        s32 velocity_x = motion->velocity_x;
        s32 old_y = motion->y.v;
        s32 velocity_y = motion->velocity_y;
        motion->x.v = old_x + velocity_x;
        motion->y.v = old_y + velocity_y;

        if (!((body->flags1C) & 0x40000) &&
            !((body->action_state_flags) & 8)) {
            motion->velocity_z += ((s8)(body->unk_9D)) * 0x14000;
            (body->unk_9D) += 1;
        } else {
            (body->unk_9D) = 0;
        }
    }

    (body->unk_90.value) += motion->velocity_z;
    part_flags = sprite->flags;
    if (!(part_flags & 0x8000)) {
        value_bits = *(s16 *)(((u8 *)(&g_dungeon_status)) - 0x238) +
            state->facing + 0x100;
        direction = ((s32)value_bits >> 9) & 7;
        mode_or_dir = (u16)direction;
        mode_or_dir = (s16)mode_or_dir;
        if ((body->unk_94) != mode_or_dir) {
            select_indirect_table_entry(sprite,
                *(*(u8 **)&sprite->frameTable + mode_or_dir),
                sprite->unk_04);
            (body->unk_94) = direction;
        }
        value_bits = (u32)&dir_sprite_flag[mode_or_dir];
        direction_flag = *(u8 *)value_bits;
        if (direction_flag != 0) {
            value_bits = sprite->flags | 1;
        } else {
            value_bits = sprite->flags & 0xFFFE;
        }

        sprite->flags = value_bits;

        apply_monster_koyaw_data(state->flags1C, (u8 *)sprite + 0xC);
        if (!(state->flags1C & 0x20)) {
            if (!(sprite->flags & 0x40)) {
                advance_sprite_animation_and_textures(sprite);
            }
        } else {
            sprite->flags |= 0x7000;
            state->flags1C &= 0xFFFBFFFF;
        }
        state_mask_a = 0xF7FFFFFF;
        mode_or_dir = (state->flags1C &= state_mask_a);
        if (!(mode_or_dir & 0x40000)) {
            s16 landing_delta;
            s32 landing_offset;
            landing_offset = (body->unk_A4.value);
            (body->unk_B0.halves.high.u) = 0;
            (body->unk_A4.value) = 0;
            (body->unk_90.value) -= landing_offset;
            if (!((body->action_state_flags) & 8)) {
                landing_delta = sample_terrain_surface_height(motion->x.unsigned_parts.integer,
                    motion->y.unsigned_parts.integer,
                            (s16)(((u16)state->ground_height) - 0x20)) -
                        ((u16)state->ground_height);
                if (landing_delta < (body->unk_90.parts.high.s)) {
                    (body->unk_90.parts.high.s) = landing_delta;
                    (body->unk_9D) = 0;
                    motion->velocity_z = 0;
                    state->flags1C |= 0x08000000;
                }
            }
        } else {

            if (!(sprite->flags & 0x40) &&
                sprite->frameTable == garuda_walk_direction_frames) {
                bob_phase = (body->unk_B0.halves.high.u);
                (body->unk_B0.halves.high.u) = bob_phase + 1;
                (body->unk_A4.value) += rsin((s16)bob_phase * 0xAA) << 5;
            }
            if (!((body->action_state_flags) & 8)) {
                floor_delta = sample_terrain_surface_height(motion->x.unsigned_parts.integer,
                    motion->y.unsigned_parts.integer,
                            (s16)(((u16)state->ground_height) - 0x20)) -
                        ((u16)state->ground_height);
                height_offset = (body->unk_90.parts.high.s);
                if (height_offset > floor_delta - 0x18) {
                    (body->unk_90.parts.high.s) =
                        (body->unk_90.parts.high.s) - 8;
                } else if (height_offset < floor_delta - 0x20) {
                    (body->unk_90.parts.high.s) =
                        (body->unk_90.parts.high.u) + 8;
                }
            }
        }
    } else {
        if (part_flags & 0x800) {
            sprite->flags = part_flags & 0x8FFF;
        } else {
            sprite->flags = part_flags | 0x7000;
        }
        state_mask_b = 0xF7FFFFFF;
        mode_or_dir = (state->flags1C &= state_mask_b);
        if (!(mode_or_dir & 0x40000)) {
            bob_offset = (body->unk_A4.value);
            (body->unk_B0.halves.high.u) = 0;
            (body->unk_A4.value) = 0;
            (body->unk_90.value) -= bob_offset;
            if (!((body->action_state_flags) & 8)) {
                floor_delta = sample_terrain_surface_height(motion->x.unsigned_parts.integer,
                    motion->y.unsigned_parts.integer,
                            (s16)(((u16)state->ground_height) - 0x20)) -
                        ((u16)state->ground_height);
                if (floor_delta < (body->unk_90.parts.high.s)) {
                    (body->unk_90.parts.high.s) = floor_delta;
                    (body->unk_9D) = 0;
                    motion->velocity_z = 0;
                    state->flags1C |= 0x08000000;
                }
            }
        } else {
            if (!(sprite->flags & 0x40) &&
                sprite->frameTable == garuda_walk_direction_frames) {
                u16 wave_phase;
                wave_phase = (body->unk_B0.halves.high.u);
                (body->unk_B0.halves.high.u) = wave_phase + 1;
                (body->unk_A4.value) += rsin((s16)wave_phase * 0xAA) << 5;
            }
            if (!((body->action_state_flags) & 8)) {
                floor_delta = sample_terrain_surface_height(motion->x.unsigned_parts.integer,
                    motion->y.unsigned_parts.integer,
                            (s16)(((u16)state->ground_height) - 0x20)) -
                        ((u16)state->ground_height);
                height_offset = (body->unk_90.parts.high.s);
                if (height_offset > floor_delta - 0x18) {
                    (body->unk_90.parts.high.s) =
                        (body->unk_90.parts.high.s) - 8;
                } else if (height_offset < floor_delta - 0x20) {
                    (body->unk_90.parts.high.s) =
                        (body->unk_90.parts.high.u) + 8;
                }
            }
        }

    }
    if (state->flags1C & 0x40000000) {
        state->flags1C &= 0xBFFFFFFF;
        floor_delta = sample_terrain_surface_height((sprite->tile_x << 6) | 0x20,
            (sprite->tile_y << 6) | 0x20,
            (s16)(((u16)state->ground_height) - 0x20));
        if ((s16)floor_delta < 0x200) {
            (body->unk_90.parts.high.s) += ((u16)state->ground_height) - floor_delta;
            state->ground_height = floor_delta;
        }
    }
    motion->z.w.i = ((u16)state->ground_height) +
        (body->unk_90.parts.high.u)
            - (body->unk_A4.halves.high.u);
    sprite->flags |= 0x40;
}
