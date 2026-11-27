#include "common.h"
#include "dungeon/monster/maximum_frames.h"
#include "shared/dungeon_status.h"
#include "shared/object_node.h"
#include "shared/dir_step.h"
#include "dungeon/player/object.h"
#include "dungeon/actor.h"

typedef struct {
    u8 pad_00_8c[0x8c];
    u8 *action_handler;
    u8 pad_90_96[6];
    u16 action_timer;
    u8 pad_98_9b[3];
    u8 action_phase;
} S810AF65C_0;

typedef struct {
    u8 pad_00_02[2];
    s16 field_02;
    u8 pad_04_06[2];
    s16 field_06;
    u8 pad_08_0c[4];
    s32 field_0c;
    s32 field_10;
    s32 field_14;
} S810AF65C_1;

typedef struct {
    u8 pad_00_14[0x14];
    u16 flags;
    u8 pad_16_24[0x0e];
    u8 tile_x;
    u8 tile_y;
} S810AF65C_2;

typedef struct {
    u8 pad_00_1c[0x1c];
    s32 state_flags;
    u8 pad_20_28[8];
    u8 hp;
    u8 pad_29_6a[0x41];
    u16 movement_facing;
} S810AF65C_3;

extern u8 maximum_action_continuation_address[];

/* Updates directional movement, then returns the actor to its tile position. */
void decelerate_maximum_actor_to_tile(S810AF65C_0 *animation, ObjectPosition *motion,
                   SpriteFrameState *tile, S810AF65C_3 *actor) {
    s32 timer;
    s32 direction;
    s32 state;
    s32 move_ticks;
    s32 biased_x;
    s32 velocity_x;
    s32 velocity_y;
    s32 biased_y;

    timer = animation->action_timer - 1;
    direction = ((u16)actor->movement_facing >> 9) & 7;
    state = animation->action_phase;
    animation->action_timer = timer;

    switch (state) {
    case 0:
        apply_clamped_actor_value_delta(actor);
        animation->action_timer = 2;
        animation->action_phase = animation->action_phase + 1;
        if (actor->hp == 0) {
            motion->velocity_z = 0;
            motion->velocity_y = 0;
            motion->velocity_x = 0;
            animation->action_timer = 0;
            begin_actor_display_action(animation, motion, tile, maximum_frame_set_3);
            return;
        }
        if ((tile->flags & 0x8000) != 0) {
            animation->action_phase = 3;
            return;
        }
                        /* fall through */
    case 1:
        if ((s16)animation->action_timer > 0) {
            return;
        }
        motion->velocity_x = (s16)dir_step_x[direction] << 18;
        motion->velocity_y = (s16)dir_step_y[direction] << 18;
        move_ticks = 5;
        if ((actor->state_flags & 0x228) != 0) {
            move_ticks = 8;
        }
        animation->action_timer = move_ticks;
        velocity_x = motion->velocity_x;
        biased_x = velocity_x;
        if (velocity_x < 0) {
            biased_x = velocity_x + 3;
        }
        velocity_y = motion->velocity_y;
        motion->velocity_x = velocity_x - (biased_x >> 2);
        biased_y = velocity_y;
        motion->velocity_y = velocity_y - (biased_y / 4);
        animation->action_phase = animation->action_phase + 1;
        break;
    case 2:
        motion->velocity_x = motion->velocity_x - ((s16)dir_step_x[direction] << 15);
        motion->velocity_y = motion->velocity_y - ((s16)dir_step_y[direction] << 15);
        if ((s16)animation->action_timer != 0) {
            return;
        }
        if (actor->hp == 0) {
            motion->velocity_z = 0;
            motion->velocity_y = 0;
            motion->velocity_x = 0;
            begin_actor_display_action(animation, motion, tile, maximum_frame_set_3);
            return;
        }
        animation->action_timer = 4;
        animation->action_phase = animation->action_phase + 1;
        break;
    case 3:
        if ((timer << 16) != 0) {
            s32 tile_x;
            s32 origin_x;
            s32 tile_y;
            s32 origin_y;

            tile_x = tile->tile_x << 6;
            origin_x = motion->x.w.i - 0x20;
            motion->velocity_x = (tile_x - origin_x) << 15;
            tile_y = tile->tile_y << 6;
            origin_y = motion->y.w.i - 0x20;
            motion->velocity_y = (tile_y - origin_y) << 15;
            if ((s16)animation->action_timer > 0) {
                return;
            }
        }
        motion->velocity_z = 0;
        motion->velocity_y = 0;
        motion->velocity_x = 0;
        set_record_integer_tile_center(motion, tile->tile_x, tile->tile_y);
        if (g_dungeon_status.pending_display_owner == NODE_HEADER(actor)) {
            g_dungeon_status.pending_display_owner = ((s32)g_dungeon_status.pending_display_owner) & 0x7fffffff;
        }
        animation->action_handler = maximum_action_continuation_address;
        break;
    }
}
