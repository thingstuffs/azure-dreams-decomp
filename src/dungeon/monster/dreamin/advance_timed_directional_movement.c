#include "shared/actor_status_flags.h"
#include "common.h"
#include "dungeon/monster/dreamin.h"
#include "shared/sprite_frame_state.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"
#include "shared/entity.h"
#include "records/Rec_D_80082E80.h"
#include "engine/graphics.h"
#include "dungeon/actor.h"
#include "dungeon/player/object.h"

extern u8 dreamin_action_continuation_address;
extern u8 dreamin_frame_set_1[];

/* Updates timed directional movement and settles the entity at its grid position. */
void advance_timed_directional_movement(ActorRecord *body, ObjectPosition *motion, SpriteFrameState *sprite, void *entity)
{
    s16 *direction_y;
    s16 *direction_x_table;
    s16 frames_left;
    s16 timer_or_state;
    s16 duration;
    s32 decel_offset;
    s32 velocity_y;
    s32 direction;
    s32 launch_offset;
    s32 velocity_x;
    s32 rounded_velocity_x;
    s32 rounded_velocity_y;
    s32 target_x;
    s32 position_x;
    s32 target_y;
    s32 position_y;
    s32 tracked_entity;
    u8 state;

    direction = (((EntityRec *)entity)->unk_6A >> 9) & 7;
    state = body->action_phase.u;

    switch (state) {
    case 0:
        apply_clamped_actor_value_delta(entity);
        if (((EntityRec *)entity)->unk_28 == 0) {
            motion->velocity_z = 0;
            motion->velocity_y = 0;
            motion->velocity_x = 0;
            begin_actor_display_action(body, motion, sprite, dreamin_frame_set_1);
            return;
        }
        if (sprite->flags & 0x8000) {
            body->action_timer.u = 0;
            body->action_phase.u = 3;
            return;
        }
        body->action_timer.u = 12;
        body->action_phase.u++;
    case 1:
        timer_or_state = body->action_timer.u - 1;
        body->action_timer.u = timer_or_state;
        if ((timer_or_state << 16) != 0) {
            return;
        }

        sprite->frameTable = dreamin_frame_set_1;
        select_sprite_entry(sprite,
            dreamin_frame_set_1[((g_game_work.view.camera_rotation.parts.viewAngle + ((EntityRec *)entity)->facing + 0x100) >> 9) & 7],
            0);

        direction_x_table = (s16 *)((s8 *)dir_step_x);
        launch_offset = direction * 2;
        motion->velocity_x =
            *(s16 *)((u8 *)direction_x_table + launch_offset) << 19;
        motion->velocity_y =
            *(s16 *)((u8 *)((s8 *)dir_step_y) + launch_offset) << 19;

        duration = -1;
        if (((EntityRec *)entity)->flags1C & (ACTOR_MP_EMPTY | ACTOR_PARALYZED | ACTOR_ASLEEP)) {
            duration = 8;
        }
        body->action_timer.u = duration;

        velocity_x = motion->velocity_x;
        rounded_velocity_x = velocity_x;
        if (velocity_x < 0) {
            rounded_velocity_x = velocity_x + 3;
        }
        velocity_y = motion->velocity_y;
        motion->velocity_x = velocity_x - (rounded_velocity_x >> 2);
        rounded_velocity_y = velocity_y;
        motion->velocity_y = velocity_y - (rounded_velocity_y / 4);
        timer_or_state = body->action_phase.u + 1;
        body->action_phase.u = timer_or_state;
        return;
    case 2:
        direction_x_table = (s16 *)((s8 *)dir_step_x);
        decel_offset = direction * 2;
        direction_y = (s16 *)((u8 *)((s8 *)dir_step_y) + decel_offset);
        motion->velocity_x -=
            *(s16 *)((u8 *)direction_x_table + decel_offset) << 16;
        motion->velocity_y -= *direction_y << 16;

        if (body->action_timer.s > 0) {
            body->action_timer.u--;
        } else if (sprite->flags & 0x6000) {
            body->action_timer.u = 0;
        }
        if (body->action_timer.s != 0) {
            return;
        }
        if (((EntityRec *)entity)->unk_28 == 0) {
            motion->velocity_z = 0;
            motion->velocity_y = 0;
            motion->velocity_x = 0;
            begin_actor_display_action(body, motion, sprite, dreamin_frame_set_1);
        } else {
            duration = 8;
            timer_or_state = body->action_phase.u + 1;
            body->action_timer.u = duration;
            body->action_phase.u = timer_or_state;
        }
        return;
    case 3:
        frames_left = body->action_timer.s;
        if (frames_left != 0) {
            target_x = sprite->tile_x << 6;
            position_x = motion->x.w.i - 0x20;
            motion->velocity_x = ((target_x - position_x) << 15) / frames_left;

            target_y = sprite->tile_y << 6;
            position_y = motion->y.w.i - 0x20;
            motion->velocity_y =
                ((target_y - position_y) << 15) / body->action_timer.s;
        }

        timer_or_state = body->action_timer.u - 1;
        body->action_timer.u = timer_or_state;
        if ((timer_or_state << 16) > 0) {
            return;
        }

        motion->velocity_z = 0;
        motion->velocity_y = 0;
        motion->velocity_x = 0;
        set_record_integer_tile_center(motion, sprite->tile_x, sprite->tile_y);

        tracked_entity = ((s32)g_dungeon_status.pending_display_owner);
        if (tracked_entity == (s32)((u8 *)entity - 0x20)) {
            g_dungeon_status.pending_display_owner = tracked_entity & 0x7FFFFFFF;
        }
        body->unk_8C.address = &dreamin_action_continuation_address;
        break;
    default:
        return;
    }
}
