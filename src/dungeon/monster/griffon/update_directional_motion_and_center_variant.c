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

typedef struct S_8014F234_0 {
    u8 pad_00[0x8C];
    u8 * unk_8C;
    u8 pad_90[0x6];
    union { s16 s; u16 u; } unk_96;   /* accessed as both */
    u8 pad_98[0x3];
    u8 unk_9B;
} S_8014F234_0;   /* arg0 in update_directional_motion_and_center_variant */

extern void select_sprite_entry(void *, s32, s32);

extern u8 griffon_slot_a_action_callback;
extern u8 griffon_frame_set_7[];
extern u8 D_80150C74[];

/* Updates directional motion and animation, then settles the entity at its tile center. */
void update_directional_motion_and_center_variant(ActorRecord *controller, ObjectPosition *motion, SpriteFrameState *sprite, ActorRecord *entity) {
    s32 state;
    s16 timer;
    s32 tracked_entity;

    state = controller->action_phase.u;
    switch (state) {
    case 0:
        apply_clamped_actor_value_delta(entity);
        motion->velocity_x =
            -((s16 *)((s8 *)dir_step_x))[(entity->movement_facing >> 9) & 7] << 15;
        motion->velocity_y =
            -((s16 *)((s8 *)dir_step_y))[(entity->movement_facing >> 9) & 7] << 15;
        controller->action_phase.u++;

        if (entity->hp == 0) {
            motion->velocity_z = 0;
            motion->velocity_y = 0;
            motion->velocity_x = 0;
            begin_actor_display_action(controller, motion, sprite, D_80150C74);
            return;
        }
        if (sprite->flags & 0x8000) {
            controller->action_timer.s = 0;
            controller->action_phase.u = 3;
            return;
        }

        if (((u32)entity->flags1C) & (ACTOR_MP_EMPTY | ACTOR_PARALYZED | ACTOR_ASLEEP)) {
            timer = 8;
        } else {
            timer = -1;
        }
        controller->action_timer.s = timer;

        motion->velocity_x -= motion->velocity_x / 4;
        motion->velocity_y -= motion->velocity_y / 4;

    case 1:
        motion->velocity_x +=
            ((s16 *)((s8 *)dir_step_x))[(entity->movement_facing >> 9) & 7] << 14;
        motion->velocity_y +=
            ((s16 *)((s8 *)dir_step_y))[(entity->movement_facing >> 9) & 7] << 14;

        if (controller->action_timer.s > 0) {
            controller->action_timer.s = controller->action_timer.u - 1;
        } else if (sprite->flags & 0x6000) {
            controller->action_timer.s = 0;
        }

        if (controller->action_timer.s != 0) {
            return;
        }
        if (entity->hp == 0) {
            motion->velocity_z = 0;
            motion->velocity_y = 0;
            motion->velocity_x = 0;
            begin_actor_display_action(controller, motion, sprite, D_80150C74);
            return;
        }
        sprite->frameTable = griffon_frame_set_7;
        select_sprite_entry(
            sprite,
            griffon_frame_set_7[((g_game_work.view.camera_rotation.parts.viewAngle + entity->facing + 0x100) >> 9) & 7],
            0);
        controller->action_phase.u++;
        return;
    case 2:
        motion->velocity_x +=
            ((s16 *)((s8 *)dir_step_x))[(entity->movement_facing >> 9) & 7] << 14;
        motion->velocity_y +=
            ((s16 *)((s8 *)dir_step_y))[(entity->movement_facing >> 9) & 7] << 14;
        if (!(sprite->flags & 0x6000)) {
            return;
        }

        sprite->frameTable = griffon_frame_set_7;
        select_sprite_entry(
            sprite,
            griffon_frame_set_7[((g_game_work.view.camera_rotation.parts.viewAngle + entity->facing + 0x100) >> 9) & 7],
            0);
        controller->action_timer.s = 8;
        controller->action_phase.u++;
        return;
    case 3:
        timer = controller->action_timer.s;
        if (timer != 0) {
            {
                s32 tile_x = sprite->tile_x << 6;
                s32 offset_x = motion->x.w.i - 0x20;
                motion->velocity_x = ((tile_x - offset_x) << 15) / timer;
            }
            {
                s32 tile_y = sprite->tile_y << 6;
                s32 offset_y = motion->y.w.i - 0x20;
                motion->velocity_y =
                    ((tile_y - offset_y) << 15) / controller->action_timer.s;
            }
        }

        timer = controller->action_timer.u - 1;
        controller->action_timer.s = timer;
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
        controller->unk_8C.address = &griffon_slot_a_action_callback;

        return;
    default:
        return;
    }
}
