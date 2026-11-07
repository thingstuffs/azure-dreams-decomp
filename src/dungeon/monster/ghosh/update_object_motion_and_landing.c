#include "common.h"
#include "dungeon/monster/ghosh.h"
#include "shared/object_flags.h"
#include "m2c_compat.h"
#include "dungeon/actor/effect.h"
#include "shared/object_node.h"

s32 check_left_tile_and_center_height(s32 x, s32 y, s32 z);
s16 sample_terrain_surface_height();


   /* the 0x2 bytes before arg0 in update_object_motion_and_landing, addressed as arg0[-1] */


typedef struct S_8016E528_1 {
    u8 pad_00[0x6];
    s16 unk_06;
    s32 unk_08;
    u8 pad_0C[0x8];
    u16 unk_14;
    u8 pad_16[0x6];
    u16 unk_1C;
    u16 unk_1E;
} S_8016E528_1;   /* arg2 in update_object_motion_and_landing */

typedef struct S_8016E528_2 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_04;   /* overlapping accesses */
    union {
        struct { s32 v; } at00;
        struct { s16 v; } at00u;
        struct { u8 pad[0x2]; s16 v; } at02;
        struct { u8 pad[0x2]; u16 v; } at02u;
    } unk_08;   /* overlapping accesses */
    u8 pad_0C[0x2];
    s16 unk_0E;
    u8 pad_10[0x2];
    s16 unk_12;
    u8 pad_14[0x2];
    s16 unk_16;
} S_8016E528_2;   /* arg1 in update_object_motion_and_landing */

typedef struct S_8016E528_3 {
    s16 unk_00;
    s16 unk_02;
} S_8016E528_3;

typedef struct S_8016E528_4 {
    u8 pad_00[0x2];
    u8 unk_02;
} S_8016E528_4;   /* ((motion->unk_18 * 4) + table_base) in update_object_motion_and_landing */

/* Updates object motion, landing interpolation, and removal. */
/* Waits before moving Ghosh's item, checks terrain, then places it using saved item bytes or shrinks its
 * falling sprite. */
void update_object_motion_and_landing(ConditionalSourceEffectBody *motion, S_8016E528_2 *position, void *object_arg) {
    S_8016E528_1 *object = object_arg;
    u8 item_data[4];
    s32 fall_height;
    s16 move_height;
    s32 world_x;
    s32 world_y;
    s32 y_distance;
    s32 settle_ticks;
    s32 x_distance;
    s32 next_tile;
    s32 tile_y;
    s32 target_y;
    u16 delay_ticks;
    s16 ticks_left;
    u16 scale;
    u16 probe_height;
    u32 tile_distance;
    S_8016E528_3 *direction_step;
    u8 *direction_table;

    if (motion->unk_12 == 3) {
        delay_ticks = motion->unk_1A;
        motion->unk_1A = (u16) (delay_ticks + 1);
        if ((s16) delay_ticks >= 0x38) {
            motion->unk_12 = 0;
            object->unk_14 = (u16) (object->unk_14 & 0xFF7F);
            motion->unk_1A = 0U;
            motion->unk_60 = 0x14900;
        }
    }
repeat_settling:
    if (motion->unk_12 != 1) {
        goto check_falling;
    }
    if (motion->unk_14 == 0) {
        motion->unk_14 = (s16) ((u16) motion->unk_14 + 1);
        tile_y = motion->unk_49;
        x_distance = position->unk_0E - motion->unk_48;
        target_y = position->unk_12;
        if (x_distance < 0) {
            x_distance = 0 - x_distance;
        }
        y_distance = target_y - tile_y;
        if (y_distance < 0) {
            y_distance = 0 - y_distance;
        }
        tile_distance = x_distance + y_distance;
        switch (tile_distance) {
        case 0:
            settle_ticks = 4;
            break;
        case 1:
            settle_ticks = 8;
            break;
        case 2:
            settle_ticks = 0xC;
            break;
        case 3:
            settle_ticks = 0xE;
            break;
        case 4:
        default:
            settle_ticks = 0x10;
            break;
        }
        motion->unk_1A = settle_ticks;
    }
    ticks_left = motion->unk_1A - 1;
    motion->unk_1A = ticks_left;
    if ((s16) ticks_left != 0) {
        {
            s32 interp_target;
            s32 interp_current;
            interp_target = position->unk_0E << 6;
            interp_current = position->unk_00.at02.v - 0x20;
            position->unk_00.at02.v = (s16) ((u16) position->unk_00.at02.v
                + (interp_target - interp_current) / (s16) ticks_left);
        }
        {
            s32 interp_target;
            s32 interp_current;
            interp_target = position->unk_12 << 6;
            interp_current = position->unk_04.at02.v - 0x20;
            position->unk_04.at02.v = (s16) ((u16) position->unk_04.at02.v
                + (interp_target - interp_current) / (s16) motion->unk_1A);
        }
        position->unk_08.at02.v = (s16) ((u16) position->unk_08.at02.v
            + ((s32) (position->unk_16
            - position->unk_08.at02.v) / (s16) motion->unk_1A));
    }
    if ((s16) motion->unk_1A <= 0) {
        item_data[0] = motion->unk_44;
        item_data[1] = motion->unk_45;
        item_data[2] = motion->unk_46;
        item_data[3] = motion->unk_47;
        place_item_at_valid_floor_position(position->unk_0E, position->unk_12,
            position->unk_16, object->unk_08, item_data);
        goto mark_removed;
    }
    if (object->unk_14 & 0x8000) {
        goto repeat_settling;
    }
    do {
check_falling:
        if (motion->unk_12 != 2) {
            break;
        }
        position->unk_08.at00.v = (s32) (position->unk_08.at00.v
            + motion->unk_54);
        motion->unk_54 = (s32) (motion->unk_54 + motion->unk_60);
        scale = object->unk_1E - 0xC8;
        object->unk_1E = scale;
        object->unk_1C = scale;
        probe_height = position->unk_08.at02u.v;
        fall_height = position->unk_08.at02.v;
        if ((sample_terrain_surface_height((motion->unk_48 << 6) & 0xFFC0,
            (motion->unk_49 << 6) & 0xFFC0, (s16) (probe_height - 0x20)) - 7) >= fall_height) {
            continue;
        }
        position->unk_08.at02.v = sample_terrain_surface_height((motion->unk_48 << 6) & 0xFFC0,
            (motion->unk_49 << 6) & 0xFFC0, (s16) ((u16) position->unk_08.at02.v
            - 0x20));
        position->unk_08.at00u.v = 0;
mark_removed:
        NODE_HEADER(motion)->flags = (u16) (NODE_HEADER(motion)->flags | 0x8000);
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
        return;
    } while (object->unk_14 & 0x8000);
    do {
            if (motion->unk_12 != 0) {
                return;
            }
            position->unk_00.at00.v = (s32) (position->unk_00.at00.v
                + motion->unk_4C);
            motion->unk_4C = (s32) (motion->unk_4C + motion->unk_58);
            position->unk_04.at00.v = (s32) (position->unk_04.at00.v
                + motion->unk_50);
            {
                void *table_data = ghosh_effect_direction_offsets;
                direction_table = table_data;
            }
            motion->unk_50 = (s32) (motion->unk_50 + motion->unk_5C);
            direction_step = (S_8016E528_3 *)((motion->unk_18 * 4) + direction_table);
            next_tile = motion->unk_48 + direction_step->unk_00;
            world_x = position->unk_00.at02.v;
            if (next_tile == (world_x / 64)) {
                next_tile = motion->unk_49 + direction_step->unk_02;
                world_y = position->unk_04.at02.v;
                if (next_tile == (world_y / 64)) {
                    if (((check_left_tile_and_center_height((u16) position->unk_00.at02.v,
                        (u16) position->unk_04.at02.v, position->unk_08.at02.v) << 0x10) != 0) ||
                        sample_terrain_surface_height((u16) position->unk_00.at02.v,
                        (u16) position->unk_04.at02.v, position->unk_08.at02.v) >= 0x200) {
                        position->unk_00.at00.v = (s32) (position->unk_00.at00.v
                            - motion->unk_4C);
                        motion->unk_4C = 0;
                        motion->unk_58 = 0;
                        position->unk_04.at00.v = (s32) (position->unk_04.at00.v
                            - motion->unk_50);
                        motion->unk_50 = 0;
                        motion->unk_5C = 0;
                    } else {
                        motion->unk_48 = (s8) ((u8) motion->unk_48
                            + *((motion->unk_18 * 4) + direction_table));
                        motion->unk_49 = (s8) ((u8) motion->unk_49
                            + ((S_8016E528_4 *)(((motion->unk_18 * 4) + direction_table)))->unk_02);
                    }
                    object->unk_06 = 0;
                }
            }
            position->unk_08.at00.v = (s32) (position->unk_08.at00.v
                + motion->unk_54);
            motion->unk_54 = (s32) (motion->unk_54 + motion->unk_60);
            move_height = position->unk_08.at02.v;
            if ((sample_terrain_surface_height(((motion->unk_48 << 6) + 0x20) & 0xFFE0,
                ((motion->unk_49 << 6) + 0x20) & 0xFFE0, move_height) - 0x10) < move_height) {
                position->unk_08.at02.v = sample_terrain_surface_height(((motion->unk_48 << 6)
                    + 0x20) & 0xFFE0, ((motion->unk_49 << 6) + 0x20) & 0xFFE0,
                    position->unk_08.at02.v);
                position->unk_08.at00u.v = 0;
                motion->unk_5C = 0;
                motion->unk_50 = 0;
                motion->unk_58 = 0;
                motion->unk_4C = 0;
                motion->unk_12 = (s16) ((u16) motion->unk_12 + 1);
                if ((find_valid_floor_item_position(motion->unk_48, motion->unk_49,
                    (s16) ((u16) position->unk_08.at02.v - 0x20), &position->unk_0E, &position->unk_12,
                    &position->unk_16) << 0x10) == 0) {
                    motion->unk_12 = 2;
                    motion->unk_54 = 0xFFF80000;
                }
            }
    } while (object->unk_14 & 0x8000);
    return;
}
