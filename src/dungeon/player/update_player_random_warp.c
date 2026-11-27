#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/dungeon_status.h"
#include "dungeon/level.h"
#include "dungeon/player/object.h"
#include "dungeon/player.h"

typedef struct {
    u8 pad0[0x92];
    s16 height_offset;
    u8 pad94[2];
    u16 action_timer;
    u16 action_state_flags;
    u8 pad9A;
    u8 state;
    u8 pad9C[6];
    u16 flagsA2;
} FuncArg0;

typedef struct {
    u8 pad0[2];
    u16 x_int;
    u8 pad4[2];
    u16 y_int;
    u8 pad8[0xC];
    s32 velocity_z;
} FuncArg1;

typedef struct {
    u8 pad0[0x1C];
    s32 state_flags;
    u8 pad20[0xA];
    u16 facing;
    u8 pad2C[0x3E];
    u16 movement_facing;
    u8 pad6C[0x1C];
    s16 ground_height;
} FuncArg3;

extern u8 D_800DCF58[9];

/* Updates a spinning movement sequence and restores the actor's original rotation. */
void update_player_random_warp(FuncArg0 *motion, FuncArg1 *position, SpriteFrameState *tile, FuncArg3 *actor_arg) {
    FuncArg3 *actor;
    register s32 flags_mask;
    s32 state;
    s32 height_offset;
    s32 actor_flags;
    u16 ticks_left;

    actor = actor_arg;
    state = motion->state;
    switch (state) {
    case 0:
        actor->movement_facing = actor->facing & 0xFFF;
        actor->state_flags &= 0xFFFEFFFF;
        motion->state++;
    case 1:
        actor->facing += 0x200;
        position->velocity_z += 0xFFFF0000;
        ticks_left = motion->action_timer - 1;
        motion->action_timer = ticks_left;
        if ((ticks_left << 16) > 0) {
            return;
        }
        position->velocity_z = 0;
        set_record_integer_tile_center(position, tile->tile_x, tile->tile_y);
        height_offset = -0x400;
        actor->ground_height = sample_terrain_surface_height(position->x_int, position->y_int,
                                       (D_800DCF58[0] = 1, height_offset));
        motion->height_offset = -0x200;
        motion->action_timer = 0x10;
        motion->action_state_flags &= 0xFFF7;
        motion->state++;
        return;
    case 2:
        actor->facing += 0x200;
        if (motion->flagsA2 & 0x10) {
            motion->action_timer = 0x20;
            motion->state++;
        }
        return;
    case 3:
        actor->facing += 0x200;
        if ((actor->facing & 0xFFF) != (actor->movement_facing & 0xFFF)) {
            return;
        }
        cycle_map_cell_flags(tile->tile_x, tile->tile_y,
                      (actor->state_flags & 0x2000) ? 0x300 : 0x3000);
        flags_mask = 0xFFFEFFFF;
        g_dungeon_status.activity_counts.parts.pending_action_count--;
        actor_flags = actor->state_flags & flags_mask;
        actor->facing = actor->movement_facing;
        actor->state_flags = actor_flags;
        restore_player_control_callback(motion, actor);

        return;
    default:
        return;
    }
}
