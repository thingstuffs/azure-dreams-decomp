#include "engine/graphics/select_sprite_entry_api.h"
#include "shared/object_node.h"
#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"
#include "dungeon/player/object.h"







extern u8 barong_action_resume_address[];
#include "dungeon/monster/barong.h"
#include "dungeon/actor.h"
#include "dungeon/data.h"
extern u8 D_8017558C[];

/* Updates timed movement, returns the actor to its tile, and resets its action state. */
void reset_actor_after_timed_movement(ActorRecord *action_arg, ObjectPosition *motion_arg, SpriteFrameState *sprite_arg, ActorRecord *entity_arg)
{
    ActorRecord *action = action_arg;
    ObjectPosition *motion = motion_arg;
    SpriteFrameState *sprite= sprite_arg;
    ActorRecord *entity = entity_arg;
    s16 timer;
    u16 old_timer;
    s32 display_owner_addr;

    switch (action->action_phase) {
    case 0:
        apply_clamped_actor_value_delta(entity);
        action->action_timer = 4;
        action->action_phase++;
        if (entity->hp == 0) {
            motion->velocity_z = 0;
            motion->velocity_y = 0;
            motion->velocity_x = 0;
            begin_actor_display_action(action, motion, sprite, D_8017558C);
            return;
        }
        if (!(sprite->flags & 0x8000)) {
            return;
        }
        action->action_timer = 0;
        action->action_phase = 3;
        return;

    case 1:
        timer = action->action_timer - 1;
        action->action_timer = timer;
        if (timer > 0) {
            motion->velocity_x =
                dir_step_x[(entity->movement_facing >> 9) & 7] << 19;
            motion->velocity_y =
                dir_step_y[(entity->movement_facing >> 9) & 7] << 19;
            return;
        }
        if (timer != 0) {
            return;
        }
        motion->velocity_x =
            dir_step_x[(entity->movement_facing >> 9) & 7] << 18;
        motion->velocity_y =
            dir_step_y[(entity->movement_facing >> 9) & 7] << 18;
        action->action_timer = 6;
        action->action_phase++;
        return;

    case 2:
        if (entity->hp == 0) {
            motion->velocity_z = 0;
            motion->velocity_y = 0;
            motion->velocity_x = 0;
            begin_actor_display_action(action, motion, sprite, D_8017558C);
            return;
        }

        timer = (action->action_timer);
        if (timer != 0) {
            {
                s32 target_coord = sprite->tile_x << 6;
                s32 current_coord = motion->x.w.i - 0x20;

                motion->velocity_x =
                    ((target_coord - current_coord) << 16) / timer;
            }
            {
                s32 target_coord = sprite->tile_y << 6;
                s32 current_coord = motion->y.w.i - 0x20;

                motion->velocity_y =
                    ((target_coord - current_coord) << 16) /
                    action->action_timer;
            }
        }
        old_timer = action->action_timer;
        action->action_timer = old_timer - 1;
        if ((s32)(old_timer << 16) > 0) {
            return;
        }
        motion->velocity_z = 0;
        motion->velocity_y = 0;
        motion->velocity_x = 0;
        action->action_phase++;
        return;

    case 3:
        motion->velocity_z = 0;
        motion->velocity_y = 0;
        motion->velocity_x = 0;
        set_record_integer_tile_center(motion, sprite->tile_x, sprite->tile_y);
        if (sprite->frameTable == barong_frame_set_4) {
            (sprite->frameTable) = barong_direction_frames;
            select_sprite_entry(sprite,
                barong_direction_frames[((g_game_work.view.camera_rotation.parts.viewAngle + entity->facing + 0x100)
                    >> 9) & 7], 0);
        }
        display_owner_addr = ((s32)g_dungeon_status.pending_display_owner);
        if (display_owner_addr == (s32)NODE_HEADER(entity)) {
            g_dungeon_status.pending_display_owner = display_owner_addr & 0x7FFFFFFF;
        }
        action->unk_8C.address = barong_action_resume_address;
        action->action_id = 0xE;
        return;

    default:
        return;
    }
}

/* MECHANISM: Ordered $s0-$s3 argument locals reproduce the retail save/move prologue.
   Duplicated state increments keep the predecessor-local lbu alive, while scoped
   coord/current temporaries expose the second lh to fill the mflo hazard slot.
   The paired +1/-1 shapes cancel the displacement cascade at 2.8.1-G0. */
