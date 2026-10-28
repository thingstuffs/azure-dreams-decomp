#include "shared/actor_status_flags.h"
#include "dungeon/monster/cyclone.h"
#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"
#include "shared/entity.h"
#include "records/Rec_D_80082E80.h"
#include "dungeon/player/object.h"


extern void begin_actor_display_action(void *actor, void *unused, SpriteFrameState *display, u8 *facing_variants);
extern void apply_clamped_actor_value_delta(void *);

extern u8 D_801764B0;

/* Slows directional motion, then aligns the entity to its tile and finishes the motion state. */
void slow_and_align_motion(ActorRecord *motion_state, ObjectPosition *motion, SpriteFrameState *tile, ActorRecord *entity) {
    s16 frames_left;
    s32 velocity_or_entity;
    s32 y_velocity;
    s32 division_bias;
    s32 state;
    s32 next_timer;

    state = motion_state->action_phase.u;
    switch (state) {
    case 0:
        apply_clamped_actor_value_delta(entity);
        motion->velocity_x =
            *(s16 *)((u8 *)((s8 *)dir_step_x) +
                ((entity->movement_facing >> 8) & 0xE)) << 19;
        motion->velocity_y =
            *(s16 *)((u8 *)((s8 *)dir_step_y) +
                ((entity->movement_facing >> 8) & 0xE)) << 19;
        motion_state->action_phase.u++;

        if (entity->hp == 0) {
            motion->velocity_z = 0;
            motion->velocity_y = 0;
            motion->velocity_x = 0;
            begin_actor_display_action(motion_state, motion, tile, &D_801764B0);
            return;
        }
        if (tile->flags & 0x8000) {
            motion_state->action_timer.s = 0;
            motion_state->action_phase.s = 2;
            return;
        }
        frames_left = -1;
        if (entity->flags1C & (ACTOR_MP_EMPTY | ACTOR_PARALYZED | ACTOR_ASLEEP)) {
            frames_left = 8;
        }
        motion_state->action_timer.s = frames_left;
    case 1:
        velocity_or_entity = motion->velocity_x;
        division_bias = velocity_or_entity;
        if (velocity_or_entity < 0) {
            division_bias = velocity_or_entity + 3;
        }
        y_velocity = motion->velocity_y;
        motion->velocity_x = velocity_or_entity - (division_bias >> 2);

        division_bias = y_velocity;
        motion->velocity_y = y_velocity - (division_bias / 4);

        if (motion_state->action_timer.s > 0) {
            motion_state->action_timer.s = motion_state->action_timer.u - 1;
        } else if (tile->flags & 0x6000) {
            motion_state->action_timer.s = 0;
        }

        if (motion_state->action_timer.s != 0) {
            return;
        }
        if (entity->hp == 0) {
            motion->velocity_z = 0;
            motion->velocity_y = 0;
            motion->velocity_x = 0;
            begin_actor_display_action(motion_state, motion, tile, &D_801764B0);
            return;
        } else {
            motion_state->action_timer.s = 8;
            motion_state->action_phase.u++;
            return;
        }
    case 2:
        frames_left = motion_state->action_timer.s;
        if (frames_left > 0) {
            s32 tile_coord;
            s32 coord_offset;

            tile_coord = tile->tile_x << 6;
            coord_offset = motion->x.w.i;
            coord_offset -= 0x20;
            motion->velocity_x = ((tile_coord - coord_offset) << 16) / frames_left;

            coord_offset = motion->y.w.i;
            coord_offset -= 0x20;
            tile_coord = tile->tile_y << 6;
            motion->velocity_y =
                ((tile_coord - coord_offset) << 16) / motion_state->action_timer.s;
        }

        next_timer = motion_state->action_timer.u - 1;
        motion_state->action_timer.s = next_timer;
        if ((next_timer << 16) > 0) {
            return;
        }

        motion->velocity_z = 0;
        motion->velocity_y = 0;
        motion->velocity_x = 0;
        set_record_integer_tile_center(motion, tile->tile_x,
            tile->tile_y);
        {

            velocity_or_entity = ((s32)g_dungeon_status.pending_display_owner);
            if (velocity_or_entity == (s32)((u8 *)entity - 0x20)) {
                g_dungeon_status.pending_display_owner = velocity_or_entity & 0x7FFFFFFF;
            }
        }
        motion_state->unk_8C.handler = update_actor_animation;
    default:
        return;
    }
}
