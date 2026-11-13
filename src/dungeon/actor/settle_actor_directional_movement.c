#include "shared/actor_status_flags.h"
#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"
#include "shared/entity.h"
#include "records/Rec_D_80082E80.h"
#include "dungeon/actor.h"
#include "dungeon/player/object.h"

extern u8 actor_action_resume_address[];

/* Updates directional movement, decelerates it, and settles the entity at its tile. */
void settle_actor_directional_movement(ActorRecord *controller, ObjectPosition *motion, SpriteFrameState *entity, EntityRec *source)
{
    s16 ticks_left;
    s32 direction;
    s32 tracked_entity;

    direction = (source->unk_6A >> 9) & 7;
    switch (controller->action_phase) {
    case 0:
        apply_clamped_actor_value_delta(source);
        motion->velocity_x =
            dir_step_x[direction] << 18;
        motion->velocity_y =
            dir_step_y[direction] << 18;
        controller->action_phase++;

        if (source->unk_28 == 0) {
            motion->velocity_z = 0;
            motion->velocity_y = 0;
            motion->velocity_x = 0;
            begin_actor_display_action(controller, motion, entity, 0);
            return;
        }
        if (entity->flags & 0x8000) {
            controller->action_timer = 0;
            controller->action_phase = 2;
            return;
        }
        if (source->flags1C & (ACTOR_MP_EMPTY | ACTOR_PARALYZED | ACTOR_ASLEEP)) {
            ticks_left = 8;
        } else {
            ticks_left = -1;
        }
        controller->action_timer = ticks_left;
        motion->velocity_x -= motion->velocity_x / 4;
        motion->velocity_y -= motion->velocity_y / 4;
                /* fall through */

    case 1:
        motion->velocity_x -=
            dir_step_x[direction] << 14;
        motion->velocity_y -=
            dir_step_y[direction] << 14;
        if (controller->action_timer > 0) {
            controller->action_timer = controller->action_timer - 1;
        } else if (entity->flags & 0x6000) {
            controller->action_timer = 0;
        }
        if (controller->action_timer != 0) {
            return;
        }
        if (source->unk_28 == 0) {
            motion->velocity_z = 0;
            motion->velocity_y = 0;
            motion->velocity_x = 0;
            begin_actor_display_action(controller, motion, entity, 0);
            return;
        }
        controller->action_timer = 8;
        controller->action_phase++;
        return;

    case 2:
        if (controller->action_timer != 0) {
            {
                s32 target_x = entity->tile_x << 6;
                s32 current_x = motion->x.w.i - 0x20;

                motion->velocity_x = ((target_x - current_x) << 15) >> 1;
            }
            {
                s32 target_y = entity->tile_y << 6;
                s32 current_y = motion->y.w.i - 0x20;

                motion->velocity_y = ((target_y - current_y) << 15) >> 1;
            }
        }
        ticks_left = controller->action_timer - 1;
        controller->action_timer = ticks_left;
        if ((s32)(ticks_left << 16) > 0) {
            return;
        }
        motion->velocity_z = 0;
        motion->velocity_y = 0;
        motion->velocity_x = 0;
        set_record_integer_tile_center(motion, entity->tile_x, entity->tile_y);

        tracked_entity = ((s32)g_dungeon_status.pending_display_owner);
        if (tracked_entity == (s32)NODE_HEADER(source)) {
            g_dungeon_status.pending_display_owner = tracked_entity & 0x7FFFFFFF;
        }
        controller->unk_8C.address = actor_action_resume_address;
        return;

    default:
        return;
    }
}
