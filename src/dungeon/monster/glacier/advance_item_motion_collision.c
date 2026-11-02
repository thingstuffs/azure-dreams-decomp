#include "shared/sprite_frame_state.h"
#include "shared/entity.h"
#include "common.h"
#include "shared/object_flags.h"
#include "dungeon/monster/glacier/advance_item_motion_collision.h"
#include "slus.h"
#include "dungeon/monster/glacier.h"

typedef struct S_80174300_1 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    union {
        struct { s32 v; } at00;
        struct { s16 v; } at00u;
        struct { u8 pad[0x2]; s16 v; } at02;
        struct { u8 pad[0x2]; s16 v; } at02u;
    } unk_08;   /* overlapping accesses */
} S_80174300_1;   /* arg1 in advance_item_motion_collision */


extern s32 check_left_tile_and_center_height(s32 x, s32 y, s32 z);
extern s16 sample_terrain_surface_height();

/* Advance motion, resolve collisions, and flag expired movement. */
void advance_item_motion_collision(DirectionalEffectBody *motion, void *position_arg, SpriteFrameState *update_arg) {
    S_80174300_1 *position = position_arg;
    s32 height;

    motion->remaining_ticks.unsigned_value = motion->remaining_ticks.unsigned_value - 1;
    advance_sprite_animation_and_textures(update_arg);
    position->unk_00.at00.v += motion->velocity_x;
    motion->velocity_x += motion->acceleration_x;
    if ((check_left_tile_and_center_height(position->unk_00.at02.v, position->unk_04.at02.v,
        position->unk_08.at02.v) << 16) != 0) {
        position->unk_00.at00.v -= motion->velocity_x;
        motion->velocity_x = 0;
        motion->acceleration_x = 0;
    }
    position->unk_04.at00.v += motion->velocity_y;
    motion->velocity_y += motion->acceleration_y;
    if ((check_left_tile_and_center_height(position->unk_00.at02.v, position->unk_04.at02.v,
        position->unk_08.at02.v) << 16) != 0) {
        position->unk_04.at00.v -= motion->velocity_y;
        motion->velocity_y = 0;
        motion->acceleration_y = 0;
    }
    position->unk_08.at00.v += motion->velocity_z;
    motion->velocity_z += motion->acceleration_z;
    height = position->unk_08.at02.v;
    if ((sample_terrain_surface_height(position->unk_00.at02.v, position->unk_04.at02.v,
                       (s16)((u16)position->unk_08.at02u.v - 4)) - 0x10) < height) {
        motion->velocity_z = 0;
        motion->velocity_y = 0;
        motion->velocity_x = 0;
        position->unk_08.at02.v = sample_terrain_surface_height(position->unk_00.at02.v,
            position->unk_04.at02.v,
                                               (s16)((u16)position->unk_08.at02.v - 4)) - 0x11;
        position->unk_08.at00u.v = 0;
        motion->remaining_ticks.unsigned_value = 0;
    }
    if ((s16)motion->remaining_ticks.unsigned_value <= 0) {
        (*(u16 *)((u8 *)motion + -2)) |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
}
