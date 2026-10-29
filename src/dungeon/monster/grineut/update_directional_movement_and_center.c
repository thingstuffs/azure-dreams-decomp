#include "shared/actor_status_flags.h"
#include "common.h"
#include "dungeon/monster/grineut.h"
#include "shared/sprite_frame_state.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"
#include "shared/entity.h"
#include "records/Rec_D_80082E80.h"
#include "dungeon/player/object.h"

typedef struct S_80161238_1 {
    u8 pad_00[0x8C];
    u8 * unk_8C;
    u8 pad_90[0x6];
    union { s16 s; u16 u; } unk_96;   /* accessed as both */
    u8 pad_98[0x3];
    u8 unk_9B;
} S_80161238_1;   /* arg0 in update_directional_movement_and_center */

extern void select_sprite_entry(void *, s32, s32);

extern u8 grineut_slot_d_action_callback;
extern u8 grineut_frame_set_10[];
extern u8 D_80162178[];

/* Updates directional movement and settles the actor at its tile center. */
void update_directional_movement_and_center(ActorRecord *action, ObjectPosition *motion, SpriteFrameState *actor, ActorRecord *entity) {
    s32 state;
    s32 direction;
    s16 timer;
    s32 tracked_entity;

    direction = (entity->movement_facing >> 9) & 7;
    state = action->action_phase.u;
    switch (state) {
    case 0:
        apply_clamped_actor_value_delta(entity);
        motion->velocity_x = ((s16 *)((s8 *)dir_step_x))[direction] << 18;
        motion->velocity_y = ((s16 *)((s8 *)dir_step_y))[direction] << 18;
        action->action_phase.u++;

        if (entity->hp == 0) {
            motion->velocity_z = 0;
            motion->velocity_y = 0;
            motion->velocity_x = 0;
            begin_actor_display_action(action, motion, actor, D_80162178);
            break;
        }
        if (actor->flags & 0x8000) {
            action->action_timer.s = 0;
            action->action_phase.u = 3;
            break;
        }

        if (((u32)entity->flags1C) & (ACTOR_MP_EMPTY | ACTOR_PARALYZED | ACTOR_ASLEEP)) {
            timer = 8;
        } else {
            timer = -1;
        }
        action->action_timer.s = timer;

        motion->velocity_x -= motion->velocity_x / 4;
        motion->velocity_y -= motion->velocity_y / 4;
                        /* fall through */
    case 1:
        motion->velocity_x -= ((s16 *)((s8 *)dir_step_x))[direction] << 14;
        motion->velocity_y -= ((s16 *)((s8 *)dir_step_y))[direction] << 14;

        if (action->action_timer.s > 0) {
            action->action_timer.s = action->action_timer.u - 1;
        } else if (actor->flags & 0x6000) {
            action->action_timer.s = 0;
        }

        if (action->action_timer.s != 0) {
            break;
        }
        if (entity->hp == 0) {
            motion->velocity_z = 0;
            motion->velocity_y = 0;
            motion->velocity_x = 0;
            begin_actor_display_action(action, motion, actor, D_80162178);
            break;
        }
        actor->frameTable = grineut_frame_set_10;
        select_sprite_entry(
            actor,
            grineut_frame_set_10[((g_game_work.view.camera_rotation.parts.viewAngle + entity->facing + 0x100) >> 9) & 7],
            0);
        action->action_phase.u++;
        return;
        break;
    case 2:
        motion->velocity_x -= ((s16 *)((s8 *)dir_step_x))[direction] << 14;
        motion->velocity_y -= ((s16 *)((s8 *)dir_step_y))[direction] << 14;
        if (!(actor->flags & 0x6000)) {
            break;
        }

        actor->frameTable = grineut_frame_set_10;
        select_sprite_entry(
            actor,
            grineut_frame_set_10[((g_game_work.view.camera_rotation.parts.viewAngle + entity->facing + 0x100) >> 9) & 7],
            0);
        action->action_timer.s = 8;
        action->action_phase.u++;
        break;
        break;
    case 3:
        timer = action->action_timer.s;
        if (timer != 0) {
            {
                s32 tile_x = actor->tile_x << 6;
                s32 offset_x = motion->x.w.i - 0x20;
                motion->velocity_x = ((tile_x - offset_x) << 15) / timer;
            }
            {
                s32 tile_y = actor->tile_y << 6;
                s32 offset_y = motion->y.w.i - 0x20;
                motion->velocity_y =
                    ((tile_y - offset_y) << 15) / action->action_timer.s;
            }
        }

        timer = action->action_timer.u - 1;
        action->action_timer.s = timer;
        if ((s32)(timer << 16) > 0) {
            return;
        }

        motion->velocity_z = 0;
        motion->velocity_y = 0;
        motion->velocity_x = 0;
        motion->x.v = ((actor->tile_x << 6) + 0x20) << 16;
        motion->y.v = ((actor->tile_y << 6) + 0x20) << 16;
        set_record_integer_tile_center(motion, actor->tile_x, actor->tile_y);

        tracked_entity = ((s32)g_dungeon_status.pending_display_owner);
        if (tracked_entity == (s32)((u8 *)entity - 0x20)) {
            g_dungeon_status.pending_display_owner = tracked_entity & 0x7FFFFFFF;
        }
        action->unk_8C.address = &grineut_slot_d_action_callback;
        break;
    }
}
