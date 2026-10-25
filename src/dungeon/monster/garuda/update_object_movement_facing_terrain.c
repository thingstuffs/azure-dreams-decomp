#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/dir_step.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "dungeon/monster/garuda.h"

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

extern u8 garuda_action_resume_address[];
extern u8 garuda_walk_direction_frames[9];
extern Callback garuda_callbacks[];

extern void select_indirect_table_entry(void *, u8, s8);
extern void advance_sprite_animation_and_textures(void *);
extern s32 rsin(s32);
extern void apply_monster_koyaw_data(s32, void *);
extern s32 refresh_actor_facing_and_lifecycle(void *, void *, void *, void *);
extern void try_move_actor_to_valid_position(void *, void *, void *, void *);
extern s32 sample_terrain_surface_height(s32 x, s32 y, s16 min_height);

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
void update_object_movement_facing_terrain(void *obj, void *input_motion, SpriteFrameState *input_part)
{
    void *state = obj;
    s32 mode_or_dir;
    s32 direction;
    u32 value_bits;
    u32 state_mask_a;
    u32 state_mask_b;
    Callback callback;
    s32 height_offset;
    s16 floor_delta;
    u16 part_flags;
    u16 bob_phase;
    s32 bob_offset;
    u8 direction_flag;
    s16 saved_mode;

    if (g_dungeon_status.flags & 0x2000) {
        callback = (*(Callback *)((u8 *)obj + 0x8C));
        if (callback == (Callback)garuda_action_resume_address) {
            void *entry_obj = obj;
            callback(entry_obj, input_motion, input_part, entry_obj);
            return;
        } else {
            (((ObjFieldView_81005278 *)obj)->field_71) &= 0x7F;
            return;
        }
    }

    saved_mode = ((ObjFieldView_81005278 *)obj)->field_6D;
    if (refresh_actor_facing_and_lifecycle(obj, input_motion, input_part, obj) != 0) {
        return;
    }

    {
        Callback update_callback;
        update_callback = (*(Callback *)((u8 *)obj + 0x8C));
        if (update_callback != 0) {
            update_callback(obj, input_motion, input_part, obj);
        }
    }
    garuda_callbacks[(((ObjFieldView_81005278 *)obj)->field_9A)](obj, input_motion, input_part, obj);
    if (saved_mode != (((ObjFieldView_81005278 *)obj)->field_6D)) {
        try_move_actor_to_valid_position(obj, input_motion, input_part, obj);
    }

    {
        s32 old_x = ((S_80170A78_0 *)input_motion)->unk_00.at00.v;
        s32 velocity_x = ((S_80170A78_0 *)input_motion)->unk_0C;
        s32 old_y = ((S_80170A78_0 *)input_motion)->unk_04.at00.v;
        s32 velocity_y = ((S_80170A78_0 *)input_motion)->unk_10;
        ((S_80170A78_0 *)input_motion)->unk_00.at00.v = old_x + velocity_x;
        ((S_80170A78_0 *)input_motion)->unk_04.at00.v = old_y + velocity_y;

        if (!((((ObjFieldView_81005278 *)obj)->field_1C) & 0x40000) &&
            !((((ObjFieldView_81005278 *)obj)->field_98) & 8)) {
            ((S_80170A78_0 *)input_motion)->unk_14 += (((ObjFieldView_81005278 *)obj)->field_9D.s8) * 0x14000;
            (((ObjFieldView_81005278 *)obj)->field_9D.u8) += 1;
        } else {
            (((ObjFieldView_81005278 *)obj)->field_9D.u8) = 0;
        }
    }

    (((ObjFieldView_81005278 *)obj)->field_90.s32) += ((S_80170A78_0 *)input_motion)->unk_14;
    part_flags = input_part->flags;
    if (!(part_flags & 0x8000)) {
        value_bits = *(s16 *)((u8 *)((u8 *)(&g_dungeon_status)) - 0x238) +
            ((S_80170A78_2 *)state)->unk_2A + 0x100;
        direction = ((s32)value_bits >> 9) & 7;
        mode_or_dir = (u16)direction;
        mode_or_dir = (s16)mode_or_dir;
        if ((((ObjFieldView_81005278 *)obj)->field_94) != mode_or_dir) {
            select_indirect_table_entry(input_part,
                *(u8 *)(*(u8 **)&input_part->frameTable + mode_or_dir),
                input_part->unk_04);
            (((ObjFieldView_81005278 *)obj)->field_94) = direction;
        }
        value_bits = (u32)&dir_sprite_flag[mode_or_dir];
        direction_flag = *(u8 *)value_bits;
        if (direction_flag != 0) {
            value_bits = input_part->flags | 1;
        } else {
            value_bits = input_part->flags & 0xFFFE;
        }

        input_part->flags = value_bits;

        apply_monster_koyaw_data(((S_80170A78_2 *)state)->unk_1C, (u8 *)input_part + 0xC);
        if (!(((S_80170A78_2 *)state)->unk_1C & 0x20)) {
            if (!(input_part->flags & 0x40)) {
                advance_sprite_animation_and_textures(input_part);
            }
        } else {
            input_part->flags |= 0x7000;
            ((S_80170A78_2 *)state)->unk_1C &= 0xFFFBFFFF;
        }
        state_mask_a = 0xF7FFFFFF;
        mode_or_dir = (((S_80170A78_2 *)state)->unk_1C &= state_mask_a);
        if (!(mode_or_dir & 0x40000)) {
            s16 landing_delta;
            s32 landing_offset;
            landing_offset = (((ObjFieldView_81005278 *)obj)->field_A4.s32);
            (((ObjFieldView_81005278 *)obj)->field_B2) = 0;
            (((ObjFieldView_81005278 *)obj)->field_A4.s32) = 0;
            (((ObjFieldView_81005278 *)obj)->field_90.s32) -= landing_offset;
            if (!((((ObjFieldView_81005278 *)obj)->field_98) & 8)) {
                landing_delta = sample_terrain_surface_height(((S_80170A78_0 *)input_motion)->unk_00.at02.v,
                    ((S_80170A78_0 *)input_motion)->unk_04.at02.v,
                            (s16)(((S_80170A78_2 *)state)->unk_88 - 0x20)) -
                        ((S_80170A78_2 *)state)->unk_88;
                if (landing_delta < (((ObjFieldView_81005278 *)obj)->field_90.s16_at_2.value)) {
                    (((ObjFieldView_81005278 *)obj)->field_90.s16_at_2.value) = landing_delta;
                    (((ObjFieldView_81005278 *)obj)->field_9D.u8) = 0;
                    ((S_80170A78_0 *)input_motion)->unk_14 = 0;
                    ((S_80170A78_2 *)state)->unk_1C |= 0x08000000;
                }
            }
        } else {

            if (!(input_part->flags & 0x40) &&
                input_part->frameTable == garuda_walk_direction_frames) {
                bob_phase = (((ObjFieldView_81005278 *)obj)->field_B2);
                (((ObjFieldView_81005278 *)obj)->field_B2) = bob_phase + 1;
                (((ObjFieldView_81005278 *)obj)->field_A4.s32) += rsin((s16)bob_phase * 0xAA) << 5;
            }
            if (!((((ObjFieldView_81005278 *)obj)->field_98) & 8)) {
                floor_delta = sample_terrain_surface_height(((S_80170A78_0 *)input_motion)->unk_00.at02.v,
                    ((S_80170A78_0 *)input_motion)->unk_04.at02.v,
                            (s16)(((S_80170A78_2 *)state)->unk_88 - 0x20)) -
                        ((S_80170A78_2 *)state)->unk_88;
                height_offset = (((ObjFieldView_81005278 *)obj)->field_90.s16_at_2.value);
                if (height_offset > floor_delta - 0x18) {
                    (((ObjFieldView_81005278 *)obj)->field_90.s16_at_2.value) =
                        (((ObjFieldView_81005278 *)obj)->field_90.s16_at_2.value) - 8;
                } else if (height_offset < floor_delta - 0x20) {
                    (((ObjFieldView_81005278 *)obj)->field_90.s16_at_2.value) =
                        (((ObjFieldView_81005278 *)obj)->field_90.u16_at_2.value) + 8;
                }
            }
        }
    } else {
        if (part_flags & 0x800) {
            input_part->flags = part_flags & 0x8FFF;
        } else {
            input_part->flags = part_flags | 0x7000;
        }
        state_mask_b = 0xF7FFFFFF;
        mode_or_dir = (((S_80170A78_2 *)state)->unk_1C &= state_mask_b);
        if (!(mode_or_dir & 0x40000)) {
            bob_offset = (((ObjFieldView_81005278 *)obj)->field_A4.s32);
            (((ObjFieldView_81005278 *)obj)->field_B2) = 0;
            (((ObjFieldView_81005278 *)obj)->field_A4.s32) = 0;
            (((ObjFieldView_81005278 *)obj)->field_90.s32) -= bob_offset;
            if (!((((ObjFieldView_81005278 *)obj)->field_98) & 8)) {
                floor_delta = sample_terrain_surface_height(((S_80170A78_0 *)input_motion)->unk_00.at02.v,
                    ((S_80170A78_0 *)input_motion)->unk_04.at02.v,
                            (s16)(((S_80170A78_2 *)state)->unk_88 - 0x20)) -
                        ((S_80170A78_2 *)state)->unk_88;
                if (floor_delta < (((ObjFieldView_81005278 *)obj)->field_90.s16_at_2.value)) {
                    (((ObjFieldView_81005278 *)obj)->field_90.s16_at_2.value) = floor_delta;
                    (((ObjFieldView_81005278 *)obj)->field_9D.u8) = 0;
                    ((S_80170A78_0 *)input_motion)->unk_14 = 0;
                    ((S_80170A78_2 *)state)->unk_1C |= 0x08000000;
                }
            }
        } else {
            if (!(input_part->flags & 0x40) &&
                input_part->frameTable == garuda_walk_direction_frames) {
                u16 wave_phase;
                wave_phase = (((ObjFieldView_81005278 *)obj)->field_B2);
                (((ObjFieldView_81005278 *)obj)->field_B2) = wave_phase + 1;
                (((ObjFieldView_81005278 *)obj)->field_A4.s32) += rsin((s16)wave_phase * 0xAA) << 5;
            }
            if (!((((ObjFieldView_81005278 *)obj)->field_98) & 8)) {
                floor_delta = sample_terrain_surface_height(((S_80170A78_0 *)input_motion)->unk_00.at02.v,
                    ((S_80170A78_0 *)input_motion)->unk_04.at02.v,
                            (s16)(((S_80170A78_2 *)state)->unk_88 - 0x20)) -
                        ((S_80170A78_2 *)state)->unk_88;
                height_offset = (((ObjFieldView_81005278 *)obj)->field_90.s16_at_2.value);
                if (height_offset > floor_delta - 0x18) {
                    (((ObjFieldView_81005278 *)obj)->field_90.s16_at_2.value) =
                        (((ObjFieldView_81005278 *)obj)->field_90.s16_at_2.value) - 8;
                } else if (height_offset < floor_delta - 0x20) {
                    (((ObjFieldView_81005278 *)obj)->field_90.s16_at_2.value) =
                        (((ObjFieldView_81005278 *)obj)->field_90.u16_at_2.value) + 8;
                }
            }
        }

    }
    if (((S_80170A78_2 *)state)->unk_1C & 0x40000000) {
        ((S_80170A78_2 *)state)->unk_1C &= 0xBFFFFFFF;
        floor_delta = sample_terrain_surface_height((input_part->tile_x << 6) | 0x20,
            (input_part->tile_y << 6) | 0x20,
            (s16)(((S_80170A78_2 *)state)->unk_88 - 0x20));
        if ((s16)floor_delta < 0x200) {
            (((ObjFieldView_81005278 *)obj)->field_90.s16_at_2.value) += ((S_80170A78_2 *)state)->unk_88 - floor_delta;
            ((S_80170A78_2 *)state)->unk_88 = floor_delta;
        }
    }
    ((S_80170A78_0 *)input_motion)->unk_0A = ((S_80170A78_2 *)state)->unk_88 +
        (((ObjFieldView_81005278 *)obj)->field_90.u16_at_2.value)
            - (((ObjFieldView_81005278 *)obj)->field_A4.u16_at_2.value);
    input_part->flags |= 0x40;
}
