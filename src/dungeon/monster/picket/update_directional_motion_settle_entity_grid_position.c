#include "shared/actor_status_flags.h"
#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"
#include "shared/entity.h"
#include "records/Rec_D_80082E80.h"
#include "shared/actor_action.h"
#include "dungeon/actor.h"
#include "dungeon/player/object.h"

   /* arg0 in update_directional_motion_settle_entity_grid_position */

extern void begin_actor_display_action(void *actor, void *unused, SpriteFrameState *display, u8 *facing_variants);

extern u8 picket_action_resume_address[];
extern u8 picket_frame_set[];

/* Update directional motion, then settle the entity at its grid position. */
void update_directional_motion_settle_entity_grid_position(ActorActionTimerView *action, ObjectPosition *motion, SpriteFrameState *grid_pos, EntityRec *entity)
{
    s16 *direction_y;
    s32 velocity_y;
    s32 decel_offset;
    s32 direction;
    s32 launch_offset;
    s32 velocity_x;
    s32 biased_velocity_x;
    s32 biased_velocity_y;
    s32 tracked_entity;
    s16 *directions_x;
    s32 ticks_left;
    s32 phase;
    u16 duration;
    s32 target_x;
    s32 current_x;
    s32 target_y;
    s32 current_y;

    ticks_left = action->timer.u - 1;
    direction = (entity->unk_6A >> 9) & 7;
    phase = action->phase;
    action->timer.u = ticks_left;
    switch (phase) {
    case 0:
        apply_clamped_actor_value_delta(entity);
        directions_x = (s16 *)((s8 *)dir_step_x);
        launch_offset = direction * 2;
        motion->velocity_x =
            *(s16 *)((u8 *)directions_x + launch_offset) << 0x12;
        motion->velocity_y =
            *(s16 *)((u8 *)((s8 *)dir_step_y) + launch_offset) << 0x12;
        action->phase++;

        if (entity->unk_28 == 0) {
            motion->velocity_z = 0;
            motion->velocity_y = 0;
            motion->velocity_x = 0;
            begin_actor_display_action(action, motion, grid_pos, picket_frame_set);
            return;
        }
        if (grid_pos->flags & 0x8000) {
            action->timer.u = 0;
            action->phase = 2;
            return;
        }

        duration = 6;
        if (entity->flags1C & (ACTOR_MP_EMPTY | ACTOR_PARALYZED | ACTOR_ASLEEP)) {
            duration = 8;
        }
        action->timer.u = duration;

        velocity_x = motion->velocity_x;
        biased_velocity_x = velocity_x;
        if (velocity_x < 0) {
            biased_velocity_x = velocity_x + 3;
        }
        velocity_y = motion->velocity_y;
        motion->velocity_x = velocity_x - (biased_velocity_x >> 2);
        biased_velocity_y = velocity_y;
        motion->velocity_y = velocity_y - (biased_velocity_y / 4);
                        /* fall through */
    case 1:
        directions_x = (s16 *)((s8 *)dir_step_x);
        decel_offset = direction * 2;
        direction_y = (s16 *)((u8 *)((s8 *)dir_step_y) + decel_offset);
        motion->velocity_x -=
            *(s16 *)((u8 *)directions_x + decel_offset) << 0xE;
        motion->velocity_y -= *direction_y << 0xE;

        if (action->timer.s != 0) {
            return;
        }
        if (entity->unk_28 == 0) {
            motion->velocity_z = 0;
            motion->velocity_y = 0;
            motion->velocity_x = 0;
            begin_actor_display_action(action, motion, grid_pos, picket_frame_set);
        } else {
            action->timer.u = 6;
            action->phase++;
        }
        return;
    case 2:
        if ((ticks_left << 0x10) != 0) {
            target_x = grid_pos->tile_x << 6;
            current_x = motion->x.w.i - 0x20;
            motion->velocity_x = (target_x - current_x) << 0x10 >> 1;
            target_y = grid_pos->tile_y << 6;
            current_y = motion->y.w.i - 0x20;
            motion->velocity_y = (target_y - current_y) << 0x10 >> 1;

            if (action->timer.s > 0) {
                return;
            }
        }

        motion->velocity_z = 0;
        motion->velocity_y = 0;
        motion->velocity_x = 0;
        set_record_integer_tile_center(motion, grid_pos->tile_x, grid_pos->tile_y);

        tracked_entity = ((s32)g_dungeon_status.pending_display_owner);
        if (tracked_entity == (s32)((u8 *)entity - 0x20)) {
            g_dungeon_status.pending_display_owner = tracked_entity & 0x7FFFFFFF;
        }
        action->next_action = picket_action_resume_address;
        break;
    default:
        return;
    }
}
