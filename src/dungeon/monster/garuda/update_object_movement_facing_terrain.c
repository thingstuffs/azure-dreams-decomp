#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/dir_step.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "dungeon/monster/garuda.h"
#include "dungeon/level.h"
#include "dungeon/item.h"
#include "engine/texture.h"

/* Sparse views for fields not covered by the existing record types. */
typedef struct {
    u8 pad_00[0x1C];
    s32 field_1C;
    u8 pad_20[0x4D];
    s8 field_6D;
    u8 pad_6E[0x3];
    u8 field_71;
    u8 pad_72[0x1E];
    union {
        s32 s32;
        struct { u8 pad[0x2]; s16 value; } s16_at_2;
        struct { u8 pad[0x2]; u16 value; } u16_at_2;
    } field_90;
    s16 field_94;
    u8 pad_96[0x2];
    u16 field_98;
    u8 field_9A;
    u8 pad_9B[0x2];
    union {
        s8 s8;
        u8 u8;
    } field_9D;
    u8 pad_9E[0x6];
    union {
        s32 s32;
        struct { u8 pad[0x2]; u16 value; } u16_at_2;
    } field_A4;
    u8 pad_A8[0xA];
    u16 field_B2;
} ObjFieldView_81005278;

typedef void (*Callback)(void *, void *, void *, void *);

extern u8 garuda_walk_direction_frames[9];
extern Callback garuda_callbacks[];

extern void advance_sprite_animation_and_textures(void *);
extern s32 rsin(s32);
extern s32 refresh_actor_facing_and_lifecycle(void *, void *, void *, void *);
extern void try_move_actor_to_valid_position(void *, void *, void *, void *);

typedef struct S_80170A78_0 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    u8 pad_08[0x2];
    s16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_80170A78_0;   /* arg1 in update_object_movement_facing_terrain */

typedef struct S_80170A78_2 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x5C];
    u16 unk_88;
} S_80170A78_2;   /* state in update_object_movement_facing_terrain */

/* Updates object callbacks, movement, facing, and terrain-relative height. */
void update_object_movement_facing_terrain(ActorRecord *body, ObjectPosition *motion, SpriteFrameState *sprite)
{
    S_80170A78_2 *state = (S_80170A78_2 *)body;
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
    garuda_callbacks[(body->action_id.u)](body, motion, sprite, body);
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
            motion->velocity_z += (body->unk_9D.s) * 0x14000;
            (body->unk_9D.u) += 1;
        } else {
            (body->unk_9D.u) = 0;
        }
    }

    (body->unk_90.value) += motion->velocity_z;
    part_flags = sprite->flags;
    if (!(part_flags & 0x8000)) {
        value_bits = *(s16 *)(((u8 *)(&g_dungeon_status)) - 0x238) +
            state->unk_2A + 0x100;
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

        apply_monster_koyaw_data(state->unk_1C, (u8 *)sprite + 0xC);
        if (!(state->unk_1C & 0x20)) {
            if (!(sprite->flags & 0x40)) {
                advance_sprite_animation_and_textures(sprite);
            }
        } else {
            sprite->flags |= 0x7000;
            state->unk_1C &= 0xFFFBFFFF;
        }
        state_mask_a = 0xF7FFFFFF;
        mode_or_dir = (state->unk_1C &= state_mask_a);
        if (!(mode_or_dir & 0x40000)) {
            s16 landing_delta;
            s32 landing_offset;
            landing_offset = (body->unk_A4.value);
            (body->unk_B0.halves.high.u) = 0;
            (body->unk_A4.value) = 0;
            (body->unk_90.value) -= landing_offset;
            if (!((body->action_state_flags) & 8)) {
                landing_delta = sample_terrain_surface_height(((S_80170A78_0 *)motion)->unk_00.at02.v,
                    ((S_80170A78_0 *)motion)->unk_04.at02.v,
                            (s16)(state->unk_88 - 0x20)) -
                        state->unk_88;
                if (landing_delta < (body->unk_90.parts.high.s)) {
                    (body->unk_90.parts.high.s) = landing_delta;
                    (body->unk_9D.u) = 0;
                    motion->velocity_z = 0;
                    state->unk_1C |= 0x08000000;
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
                floor_delta = sample_terrain_surface_height(((S_80170A78_0 *)motion)->unk_00.at02.v,
                    ((S_80170A78_0 *)motion)->unk_04.at02.v,
                            (s16)(state->unk_88 - 0x20)) -
                        state->unk_88;
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
        mode_or_dir = (state->unk_1C &= state_mask_b);
        if (!(mode_or_dir & 0x40000)) {
            bob_offset = (body->unk_A4.value);
            (body->unk_B0.halves.high.u) = 0;
            (body->unk_A4.value) = 0;
            (body->unk_90.value) -= bob_offset;
            if (!((body->action_state_flags) & 8)) {
                floor_delta = sample_terrain_surface_height(((S_80170A78_0 *)motion)->unk_00.at02.v,
                    ((S_80170A78_0 *)motion)->unk_04.at02.v,
                            (s16)(state->unk_88 - 0x20)) -
                        state->unk_88;
                if (floor_delta < (body->unk_90.parts.high.s)) {
                    (body->unk_90.parts.high.s) = floor_delta;
                    (body->unk_9D.u) = 0;
                    motion->velocity_z = 0;
                    state->unk_1C |= 0x08000000;
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
                floor_delta = sample_terrain_surface_height(((S_80170A78_0 *)motion)->unk_00.at02.v,
                    ((S_80170A78_0 *)motion)->unk_04.at02.v,
                            (s16)(state->unk_88 - 0x20)) -
                        state->unk_88;
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
    if (state->unk_1C & 0x40000000) {
        state->unk_1C &= 0xBFFFFFFF;
        floor_delta = sample_terrain_surface_height((sprite->tile_x << 6) | 0x20,
            (sprite->tile_y << 6) | 0x20,
            (s16)(state->unk_88 - 0x20));
        if ((s16)floor_delta < 0x200) {
            (body->unk_90.parts.high.s) += state->unk_88 - floor_delta;
            state->unk_88 = floor_delta;
        }
    }
    motion->z.w.i = state->unk_88 +
        (body->unk_90.parts.high.u)
            - (body->unk_A4.halves.high.u);
    sprite->flags |= 0x40;
}
