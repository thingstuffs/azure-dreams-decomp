#include "common.h"
#include "shared/object_flags.h"
#include "dungeon/actor/effect.h"
#include "dungeon/monster/barong.h"

/* Sparse views for fields not covered by the existing record types. */
typedef struct { u16 flags; } MotionFieldView_80E64FF0Prefix;


   /* arg0 in update_motion_and_terrain_collision */

typedef struct S_801747F0_1 {
    union {
        struct { s32 v; } at00;
        struct { u8 pad[0x2]; s16 v; } at02;
        struct { u8 pad[0x2]; u16 v; } at02u;
    } unk_00;   /* overlapping accesses */
    union {
        struct { s32 v; } at00;
        struct { u8 pad[0x2]; s16 v; } at02;
        struct { u8 pad[0x2]; u16 v; } at02u;
    } unk_04;   /* overlapping accesses */
    union {
        struct { s32 v; } at00;
        struct { s16 v; } at00u;
        struct { u8 pad[0x2]; s16 v; } at02;
        struct { u8 pad[0x2]; u16 v; } at02u;
        struct { u8 pad[0x2]; u16 v; } at02p;
    } unk_08;   /* overlapping accesses */
    u8 pad_0C[0x2];
    s16 unk_0E;
    u8 pad_10[0x2];
    s16 unk_12;
    u8 pad_14[0x2];
    s16 unk_16;
} S_801747F0_1;   /* arg1 in update_motion_and_terrain_collision */

typedef struct S_801747F0_3 {
    s16 unk_00;
    s16 unk_02;
} S_801747F0_3;   /* tile in update_motion_and_terrain_collision */


extern u8 barong_direction_vectors[16];

s32 check_left_tile_and_center_height(s32 x, s32 y, s32 z);
extern s16 sample_terrain_surface_height(s32, s32, s16);

/* Update motion and terrain collisions, then settle at a target or finish falling. */
/* Moves an item through terrain checks, settles it using four saved item bytes, or shrinks its falling
 * sprite. */
void update_motion_and_terrain_collision(TossedItemMotionBody *motion, S_801747F0_1 *position, SpriteFrameState *object_arg)
{
    SpriteFrameState *object = object_arg;
    u8 colors[4];
    s32 move_frames;
    s32 fall_height;
    s32 flight_height;
    s32 x;
    s32 y;
    s32 dx;
    s32 dy;
    s32 cell_y;
    s16 frames_left;
    u16 next_scale;
    u16 height;
    u16 height_2;
    u32 tile_distance;
    S_801747F0_3 *direction;
    u8 *directions;
    s32 target_cell_y;
    s32 next_cell_x;
    s32 next_cell_y;

settle:
    if (motion->phase.s == 1) {
        if (motion->settle_started.s == 0) {
            motion->settle_started.u = (u16)(motion->settle_started.u + 1);
            cell_y = motion->cell_y.s;
            dx = position->unk_0E - motion->cell_x.s;
            target_cell_y = position->unk_12;
            if (dx < 0) {
                dx = -dx;
            }
            dy = target_cell_y - cell_y;
            if (dy < 0) {
                dy = -dy;
            }
            tile_distance = dx + dy;
            switch (tile_distance) {
            case 0:
                move_frames = 4;
                break;
            case 1:
                move_frames = 8;
                break;
            case 2:
                move_frames = 0xC;
                break;
            case 3:
                move_frames = 0xE;
                break;
            case 4:
            default:
                move_frames = 0x10;
                break;
            }
            motion->settle_frames.u = move_frames;
        }
        frames_left = motion->settle_frames.u - 1;
        motion->settle_frames.u = frames_left;
        if (frames_left != 0) {
            {
                s32 step_x;
                s32 offset_x;
                step_x = position->unk_0E << 6;
                offset_x = position->unk_00.at02.v - 0x20;
                position->unk_00.at02.v = (u16)position->unk_00.at02.v + (step_x
                    - offset_x) / frames_left;
            }
            {
                s32 step_y;
                s32 offset_y;
                step_y = position->unk_12 << 6;
                offset_y = position->unk_04.at02.v - 0x20;
                position->unk_04.at02.v = (u16)position->unk_04.at02.v + (step_y
                    - offset_y) / motion->settle_frames.s;
            }
            position->unk_08.at02.v = (u16)position->unk_08.at02.v +
                ((position->unk_16
                    - position->unk_08.at02.v) / motion->settle_frames.s);
        }
        if (motion->settle_frames.s <= 0) {
            colors[0] = motion->arg.index;
            colors[1] = motion->arg.group;
            colors[2] = motion->arg.param;
            colors[3] = motion->arg.flags;
            place_item_at_valid_floor_position(position->unk_0E, position->unk_12,
                          position->unk_16, (s32)(unsigned long)object->source, colors);
            (((MotionFieldView_80E64FF0Prefix *)motion)[-1].flags) |= 0x8000;
            object_flag_block.flags |= OBJECT_REMOVE_PENDING;
            return;
        }
        if (object->flags & 0x8000) {
            goto settle;
        }
    }
fall:
    if (motion->phase.s == 2) {
        position->unk_08.at00.v += motion->velocity_z;
        motion->velocity_z += motion->acceleration_z;
        next_scale = object->scale_y - 0xC8;
        object->scale_y = next_scale;
        object->scale_x = next_scale;
        {
            s32 fall_cell_x;
            s32 fall_cell_y;
            fall_cell_x = motion->cell_x.s;
            fall_cell_y = motion->cell_y.s;
            height = position->unk_08.at02u.v;
            fall_height = position->unk_08.at02.v;
            if ((sample_terrain_surface_height((fall_cell_x << 6) & 0xFFC0,
                               (fall_cell_y << 6) & 0xFFC0,
                               (s16)(height - 0x20)) - 7) < fall_height) {
                position->unk_08.at02.v = sample_terrain_surface_height(
                    (motion->cell_x.s << 6) & 0xFFC0,
                    (motion->cell_y.s << 6) & 0xFFC0,
                    (s16)(position->unk_08.at02p.v - 0x20));
                position->unk_08.at00u.v = 0;
                (((MotionFieldView_80E64FF0Prefix *)motion)[-1].flags) |= 0x8000;
                object_flag_block.flags |= OBJECT_REMOVE_PENDING;
                return;
            }
        }
        if (object->flags & 0x8000) {
            goto fall;
        }
    }

    do {
        if (motion->phase.s != 0) {
            return;
        }
        position->unk_00.at00.v += motion->velocity_x;
        motion->velocity_x += motion->acceleration_x;
        position->unk_04.at00.v += motion->velocity_y;
        {
            s32 velocity_y;
            s32 accel_y;
            velocity_y = motion->velocity_y;
            accel_y = motion->acceleration_y;
            velocity_y += accel_y;
            directions = barong_direction_vectors;
            motion->velocity_y = velocity_y;
        }
        direction = (motion->direction.s * 4) + directions;
        next_cell_x = motion->cell_x.s + direction->unk_00;
        x = position->unk_00.at02.v;
        if (next_cell_x == (x / 64)) {
            next_cell_y = motion->cell_y.s + direction->unk_02;
            y = position->unk_04.at02.v;
            if (next_cell_y == (y / 64)) {
                if (((check_left_tile_and_center_height(position->unk_00.at02u.v,
                    position->unk_04.at02u.v,
                                   position->unk_08.at02.v) << 16) != 0) ||
                    sample_terrain_surface_height(position->unk_00.at02u.v,
                        position->unk_04.at02u.v,
                                  position->unk_08.at02.v) >= 0x200) {
                    position->unk_00.at00.v -= motion->velocity_x;
                    motion->velocity_x = 0;
                    motion->acceleration_x = 0;
                    position->unk_04.at00.v -= motion->velocity_y;
                    motion->velocity_y = 0;
                    motion->acceleration_y = 0;
                } else {
                    motion->cell_x.u += *((motion->direction.s * 4) + directions);
                    motion->cell_y.u += *((motion->direction.s * 4) + directions
                        + 2);
                }
                object->depth_bias = 0;
            }
        }
        position->unk_08.at00.v += motion->velocity_z;
        motion->velocity_z += motion->acceleration_z;
        height_2 = position->unk_08.at02u.v;
        flight_height = position->unk_08.at02.v;
        if ((sample_terrain_surface_height((motion->cell_x.s << 6) & 0xFFC0,
                           (motion->cell_y.s << 6) & 0xFFC0,
                           (s16)(height_2 - 0x20)) - 0x10) < flight_height) {
            position->unk_08.at02.v = sample_terrain_surface_height(
                (motion->cell_x.s << 6) & 0xFFC0,
                (motion->cell_y.s << 6) & 0xFFC0,
                (s16)(position->unk_08.at02p.v - 0x20));
            position->unk_08.at00u.v = 0;
            motion->acceleration_y = 0;
            motion->velocity_y = 0;
            motion->acceleration_x = 0;
            motion->velocity_x = 0;
            motion->phase.u = motion->phase.u + 1;
            if ((find_valid_floor_item_position(motion->cell_x.s, motion->cell_y.s,
                               (s16)(position->unk_08.at02p.v - 0x20),
                               &position->unk_0E,
                               &position->unk_12,
                               &position->unk_16) << 16) == 0) {
                motion->phase.s = 2;
                motion->velocity_z = 0xFFF80000;
            }
        }
    } while (object->flags & 0x8000);
}
