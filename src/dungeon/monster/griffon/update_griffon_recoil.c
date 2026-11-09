#include "shared/actor_status_flags.h"
#include "common.h"
#include "dungeon/monster/griffon.h"
#include "shared/sprite_frame_state.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"
#include "shared/entity.h"
#include "records/Rec_D_80082E80.h"
#include "dungeon/player/object.h"
#include "dungeon/monster/griffon_frames.h"



extern void select_sprite_entry(void *, s32, s32);

extern u8 griffon_slot_f_action_callback;
extern u8 D_8016EC74[];

/* Updates directional motion and animation, then settles the entity at its tile center. */
void update_griffon_recoil(ActorRecord *action, ObjectPosition *motion, SpriteFrameState *sprite, ActorRecord *entity)
{
    s32 state;
    s16 timer;
    s32 tracked_entity;

    state = action->action_phase;
    switch (state) {
    case 0:
        apply_clamped_actor_value_delta(entity);
        motion->velocity_x =
            -((s16 *)((s8 *)dir_step_x))[(entity->movement_facing >> 9) & 7] << 15;
        motion->velocity_y =
            -((s16 *)((s8 *)dir_step_y))[(entity->movement_facing >> 9) & 7] << 15;
        action->action_phase++;

        if (entity->hp == 0) {
            motion->velocity_z = 0;
            motion->velocity_y = 0;
            motion->velocity_x = 0;
            begin_actor_display_action(action, motion, sprite, D_8016EC74);
            return;
        }
        if (sprite->flags & 0x8000) {
            action->action_timer = 0;
            action->action_phase = 3;
            return;
        }

        if (((u32)entity->flags1C) & (ACTOR_MP_EMPTY | ACTOR_PARALYZED | ACTOR_ASLEEP)) {
            timer = 8;
        } else {
            timer = -1;
        }
        action->action_timer = timer;

        motion->velocity_x -= motion->velocity_x / 4;
        motion->velocity_y -= motion->velocity_y / 4;
                        /* fall through */

    case 1:
        motion->velocity_x +=
            ((s16 *)((s8 *)dir_step_x))[(entity->movement_facing >> 9) & 7] << 14;
        motion->velocity_y +=
            ((s16 *)((s8 *)dir_step_y))[(entity->movement_facing >> 9) & 7] << 14;

        if (action->action_timer > 0) {
            action->action_timer = action->action_timer - 1;
        } else if (sprite->flags & 0x6000) {
            action->action_timer = 0;
        }

        if (action->action_timer != 0) {
            return;
        }
        if (entity->hp == 0) {
            motion->velocity_z = 0;
            motion->velocity_y = 0;
            motion->velocity_x = 0;
            begin_actor_display_action(action, motion, sprite, D_8016EC74);
            return;
        }
        sprite->frameTable = griffon_frame_set_12;
        select_sprite_entry(
            sprite,
            griffon_frame_set_12[((g_game_work.view.camera_rotation.parts.viewAngle + entity->facing + 0x100) >> 9) & 7],
            0);
        action->action_phase++;
        return;

    case 2:
        motion->velocity_x +=
            ((s16 *)((s8 *)dir_step_x))[(entity->movement_facing >> 9) & 7] << 14;
        motion->velocity_y +=
            ((s16 *)((s8 *)dir_step_y))[(entity->movement_facing >> 9) & 7] << 14;
        if (!(sprite->flags & 0x6000)) {
            return;
        }

        sprite->frameTable = griffon_frame_set_12;
        select_sprite_entry(
            sprite,
            griffon_frame_set_12[((g_game_work.view.camera_rotation.parts.viewAngle + entity->facing + 0x100) >> 9) & 7],
            0);
        action->action_timer = 8;
        action->action_phase++;
        return;

    case 3:
        timer = (action->action_timer);
        if (timer != 0) {
            {
                s32 target_x = sprite->tile_x << 6;
                s32 current_x = motion->x.w.i - 0x20;
                motion->velocity_x = ((target_x - current_x) << 15) / timer;
            }
            {
                s32 target_y = sprite->tile_y << 6;
                s32 current_y = motion->y.w.i - 0x20;
                motion->velocity_y =
                    ((target_y - current_y) << 15) / action->action_timer;
            }
        }

        timer = action->action_timer - 1;
        action->action_timer = timer;
        if ((s32)(timer << 16) > 0) {
            return;
        }

        motion->velocity_z = 0;
        motion->velocity_y = 0;
        motion->velocity_x = 0;
        motion->x.v = ((sprite->tile_x << 6) + 0x20) << 16;
        motion->y.v = ((sprite->tile_y << 6) + 0x20) << 16;
        set_record_integer_tile_center(motion, sprite->tile_x, sprite->tile_y);

        tracked_entity = ((s32)g_dungeon_status.pending_display_owner);
        if (tracked_entity == (s32)((u8 *)entity - 0x20)) {
            g_dungeon_status.pending_display_owner = tracked_entity & 0x7FFFFFFF;
        }
        action->unk_8C.byte_ptr = &griffon_slot_f_action_callback;
    }
}
