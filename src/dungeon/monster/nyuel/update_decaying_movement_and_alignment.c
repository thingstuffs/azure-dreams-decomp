#include "shared/actor_status_flags.h"
#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"
#include "shared/entity.h"
#include "records/Rec_D_80082E80.h"
#include "dungeon/actor.h"
#include "dungeon/player/object.h"

extern s32 nyuel_action_resume_address;
extern s32 nyuel_frame_set;

/* Updates decaying movement and tile alignment before advancing or finishing the action. */
void update_decaying_movement_and_alignment(ActorRecord *action, ObjectPosition *motion, SpriteFrameState *tile_state, ActorRecord *actor_data) {
    s16 timer;
    s32 tracked_actor;

    switch (action->action_phase.u) {
    case 0:
        apply_clamped_actor_value_delta(actor_data);
        motion->velocity_x =
            *(s16 *)((u8 *)((s8 *)dir_step_x) +
                     ((actor_data->movement_facing >> 8) & 0xE)) << 19;
        motion->velocity_y =
            *(s16 *)((u8 *)((s8 *)dir_step_y) +
                     ((actor_data->movement_facing >> 8) & 0xE)) << 19;
        action->action_phase.u++;

        if (actor_data->hp == 0) {
            motion->velocity_z = 0;
            motion->velocity_y = 0;
            motion->velocity_x = 0;
            begin_actor_display_action(action, motion, tile_state, &nyuel_frame_set);
            return;
        }
        if (tile_state->flags & 0x8000) {
            action->action_timer.s = 0;
            action->action_phase.s = 2;
            return;
        }
        if (actor_data->flags1C & (ACTOR_MP_EMPTY | ACTOR_PARALYZED | ACTOR_ASLEEP)) {
            timer = 8;
        } else {
            timer = -1;
        }
        action->action_timer.s = timer;
                        /* fall through */

    case 1:
    {
        s32 velocity_x = motion->velocity_x;
        motion->velocity_x = velocity_x - velocity_x / 4;
    }
        {
            s32 velocity_y = motion->velocity_y;
            motion->velocity_y = velocity_y - velocity_y / 4;
        }
        if (action->action_timer.s > 0) {
            action->action_timer.s = action->action_timer.u - 1;
        } else if (tile_state->flags & 0x6000) {
            action->action_timer.s = 0;
        }
        if (action->action_timer.s != 0) {
            return;
        }
        if (actor_data->hp != 0) {
            action->action_timer.s = 8;
            action->action_phase.u++;
            return;
        }
        motion->velocity_z = 0;
        motion->velocity_y = 0;
        motion->velocity_x = 0;
        begin_actor_display_action(action, motion, tile_state, &nyuel_frame_set);
        return;

    case 2:
        timer = action->action_timer.s;
        if (timer > 0) {
            {
                s32 target_pos = tile_state->tile_x << 6;
                s32 current_pos = motion->x.w.i - 0x20;
                motion->velocity_x =
                    ((target_pos - current_pos) << 16) / timer;
            }
            {
                s32 target_pos = tile_state->tile_y << 6;
                s32 current_pos = motion->y.w.i - 0x20;
                motion->velocity_y =
                    ((target_pos - current_pos) << 16) / action->action_timer.s;
            }
        }
        timer = action->action_timer.u - 1;
        action->action_timer.s = timer;
        if ((s32)(timer << 16) > 0) {
            return;
        }
        if ((tile_state->flags & 0x6000) &&
            actor_data->hp == 0) {
            motion->velocity_z = 0;
            motion->velocity_y = 0;
            motion->velocity_x = 0;
            begin_actor_display_action(action, motion, tile_state, &nyuel_frame_set);
            return;
        } else {
            motion->velocity_z = 0;
            motion->velocity_y = 0;
            motion->velocity_x = 0;
            set_record_integer_tile_center(motion, tile_state->tile_x, tile_state->tile_y);

            tracked_actor = ((s32)g_dungeon_status.pending_display_owner);
            if (tracked_actor == (s32)((u8 *)actor_data - 0x20)) {
                g_dungeon_status.pending_display_owner = tracked_actor & 0x7FFFFFFF;
            }
            action->unk_8C.address = &nyuel_action_resume_address;
            return;
        }

    default:
        return;
    }
}
