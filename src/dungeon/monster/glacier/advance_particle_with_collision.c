#include "shared/sprite_frame_state.h"
#include "shared/entity.h"
#include "common.h"
#include "shared/object_flags.h"
#include "dungeon/monster/glacier/advance_particle_with_collision.h"
#include "slus.h"
#include "dungeon/monster/glacier.h"

extern s32 check_left_tile_and_center_height(s32 x, s32 y, s32 z);
extern s16 sample_terrain_surface_height();

/* Advance motion, resolve collisions, and flag expired movement. */
void advance_particle_with_collision(DirectionalEffectBody *motion, ObjectPosition *position_arg, SpriteFrameState *update_arg) {
    ObjectPosition *position = position_arg;
    s32 height;

    motion->remaining_ticks.unsigned_value = motion->remaining_ticks.unsigned_value - 1;
    advance_sprite_animation_and_textures(update_arg);
    position->x.v += motion->velocity_x;
    motion->velocity_x += motion->acceleration_x;
    if ((check_left_tile_and_center_height(position->x.unsigned_parts.integer, position->y.unsigned_parts.integer,
        position->z.w.i) << 16) != 0) {
        position->x.v -= motion->velocity_x;
        motion->velocity_x = 0;
        motion->acceleration_x = 0;
    }
    position->y.v += motion->velocity_y;
    motion->velocity_y += motion->acceleration_y;
    if ((check_left_tile_and_center_height(position->x.unsigned_parts.integer, position->y.unsigned_parts.integer,
        position->z.w.i) << 16) != 0) {
        position->y.v -= motion->velocity_y;
        motion->velocity_y = 0;
        motion->acceleration_y = 0;
    }
    position->z.v += motion->velocity_z;
    motion->velocity_z += motion->acceleration_z;
    height = position->z.w.i;
    if ((sample_terrain_surface_height(position->x.unsigned_parts.integer, position->y.unsigned_parts.integer,
                       (s16)((u16)position->z.w.i - 4)) - 0x10) < height) {
        motion->velocity_z = 0;
        motion->velocity_y = 0;
        motion->velocity_x = 0;
        position->z.w.i = sample_terrain_surface_height(position->x.unsigned_parts.integer,
            position->y.unsigned_parts.integer,
                                               (s16)((u16)position->z.w.i - 4)) - 0x11;
        position->z.w.frac = 0;
        motion->remaining_ticks.unsigned_value = 0;
    }
    if ((s16)motion->remaining_ticks.unsigned_value <= 0) {
        (*(u16 *)((u8 *)motion + -2)) |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
}
