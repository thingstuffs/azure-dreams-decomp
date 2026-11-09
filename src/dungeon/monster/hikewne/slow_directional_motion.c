#include "shared/actor_status_flags.h"
#include "dungeon/monster/hikewne.h"
#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"
#include "shared/entity.h"
#include "records/Rec_D_80082E80.h"
#include "dungeon/actor.h"
#include "dungeon/player/object.h"


extern u8 hikewne_motion_frame_set;

/* Slows directional motion, then recenters the entity on its tile. */
void slow_directional_motion(ActorRecord *motion_state, ObjectPosition *motion, Rec_D_80082E80 *tile_state, void *entity)
{
    s16 timer;
    s32 x_speed_or_entity;
    s32 velocity_z;
    s32 rounded_velocity;
    s32 state;
    s32 countdown;

    switch (motion_state->action_phase) {
    case 0:
        apply_clamped_actor_value_delta(entity);
        motion->velocity_x =
            -dir_step_x[(((EntityRec *)entity)->unk_6A >> 9) & 7] << 15;
        motion->velocity_y =
            -dir_step_y[(((EntityRec *)entity)->unk_6A >> 9) & 7] << 15;
        motion_state->action_phase++;

        if (((EntityRec *)entity)->unk_28 == 0) {
            motion->velocity_z = 0;
            motion->velocity_y = 0;
            motion->velocity_x = 0;
            begin_actor_display_action(motion_state, motion, tile_state, &hikewne_motion_frame_set);
            return;
        }
        if (tile_state->unk_14.at00_u16.v & 0x8000) {
            motion_state->action_timer = 0;
            motion_state->action_phase = 2;
            return;
        }
        timer = -1;
        if (((EntityRec *)entity)->flags1C & (ACTOR_MP_EMPTY | ACTOR_PARALYZED | ACTOR_ASLEEP)) {
            timer = 8;
        }
        motion_state->action_timer = timer;
                        /* fall through */

    case 1:
        x_speed_or_entity = motion->velocity_x;
        rounded_velocity = x_speed_or_entity;
        if (x_speed_or_entity < 0) {
            rounded_velocity = x_speed_or_entity + 3;
        }
        velocity_z = motion->velocity_y;
        motion->velocity_x = x_speed_or_entity - (rounded_velocity >> 2);

        rounded_velocity = velocity_z;
        motion->velocity_y = velocity_z - (rounded_velocity / 4);

        if (motion_state->action_timer > 0) {
            motion_state->action_timer = motion_state->action_timer - 1;
        } else if (tile_state->unk_14.at00_u16.v & 0x6000) {
            motion_state->action_timer = 0;
        }

        if (motion_state->action_timer != 0) {
            return;
        }
        if (((EntityRec *)entity)->unk_28 == 0) {
            motion->velocity_z = 0;
            motion->velocity_y = 0;
            motion->velocity_x = 0;
            begin_actor_display_action(motion_state, motion, tile_state, &hikewne_motion_frame_set);
            return;
        }
        motion_state->action_timer = 8;
        motion_state->action_phase++;
        return;

    case 2:
        timer = (motion_state->action_timer);
        if (timer != 0) {
            s32 tile_coord;
            s32 offset_coord;

            tile_coord = tile_state->unk_24 << 6;
            offset_coord = motion->x.w.i;
            offset_coord -= 0x20;
            motion->velocity_x = ((tile_coord - offset_coord) << 15) / timer;

            offset_coord = motion->y.w.i;
            offset_coord -= 0x20;
            tile_coord = tile_state->unk_25 << 6;
            motion->velocity_y =
                ((tile_coord - offset_coord) << 15) / motion_state->action_timer;
        }

        countdown = (u16)motion_state->action_timer - 1;
        motion_state->action_timer = countdown;
        if ((countdown << 16) > 0) {
            return;
        }

        motion->velocity_z = 0;
        motion->velocity_y = 0;
        motion->velocity_x = 0;
        set_record_integer_tile_center(motion, tile_state->unk_24,
            tile_state->unk_25);
        {

            x_speed_or_entity = ((s32)g_dungeon_status.pending_display_owner);
            if (x_speed_or_entity == (s32)((u8 *)entity - 0x20)) {
                g_dungeon_status.pending_display_owner = x_speed_or_entity & 0x7FFFFFFF;
            }
        }
        motion_state->unk_8C.address = update_actor_behavior_animation_and_facing;
        return;

    default:
        return;
    }
}
