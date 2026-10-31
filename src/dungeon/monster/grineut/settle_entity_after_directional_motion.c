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


extern void select_sprite_entry(void *, s32, s32);

extern u8 D_80152E54;
extern u8 grineut_frame_set_8[];
extern u8 D_80156178[];

/* Updates directional motion and animation, then settles the entity at its tile center. */
void settle_entity_after_directional_motion(ActorRecord *body, ObjectPosition *motion, SpriteFrameState *sprite, void *entity)
{
    s32 state;
    s32 direction;
    s16 timer;
    s32 tracked_addr;

    direction = (((EntityRec *)entity)->unk_6A >> 9) & 7;
    state = body->action_phase.u;
    switch (state) {
    case 0:
        apply_clamped_actor_value_delta(entity);
        motion->velocity_x = ((s16 *)((s8 *)dir_step_x))[direction] << 18;
        motion->velocity_y = ((s16 *)((s8 *)dir_step_y))[direction] << 18;
        body->action_phase.u++;

        if (((EntityRec *)entity)->unk_28 == 0) {
            motion->velocity_z = 0;
            motion->velocity_y = 0;
            motion->velocity_x = 0;
            begin_actor_display_action(body, motion, sprite, D_80156178);
            return;
        }
        if (sprite->flags & 0x8000) {
            body->action_timer.s = 0;
            body->action_phase.u = 3;
            return;
        }

        if (((u32)((EntityRec *)entity)->flags1C) & (ACTOR_MP_EMPTY | ACTOR_PARALYZED | ACTOR_ASLEEP)) {
            timer = 8;
        } else {
            timer = -1;
        }
        body->action_timer.s = timer;

        motion->velocity_x -= motion->velocity_x / 4;
        motion->velocity_y -= motion->velocity_y / 4;

    case 1:
        motion->velocity_x -= ((s16 *)((s8 *)dir_step_x))[direction] << 14;
        motion->velocity_y -= ((s16 *)((s8 *)dir_step_y))[direction] << 14;

        if (body->action_timer.s > 0) {
            body->action_timer.s = body->action_timer.u - 1;
        } else if (sprite->flags & 0x6000) {
            body->action_timer.s = 0;
        }

        if (body->action_timer.s != 0) {
            return;
        }
        if (((EntityRec *)entity)->unk_28 == 0) {
            motion->velocity_z = 0;
            motion->velocity_y = 0;
            motion->velocity_x = 0;
            begin_actor_display_action(body, motion, sprite, D_80156178);
            return;
        } else {
            sprite->frameTable = grineut_frame_set_8;
            select_sprite_entry(
                sprite,
                grineut_frame_set_8[((g_game_work.view.camera_rotation.parts.viewAngle + ((EntityRec *)entity)->facing + 0x100) >> 9) & 7],
                0);
            body->action_phase.u++;
            return;
        }

    case 2:
        motion->velocity_x -= ((s16 *)((s8 *)dir_step_x))[direction] << 14;
        motion->velocity_y -= ((s16 *)((s8 *)dir_step_y))[direction] << 14;
        if (!(sprite->flags & 0x6000)) {
            return;
        }

        sprite->frameTable = grineut_frame_set_8;
        select_sprite_entry(
            sprite,
            grineut_frame_set_8[((g_game_work.view.camera_rotation.parts.viewAngle + ((EntityRec *)entity)->facing + 0x100) >> 9) & 7],
            0);
        body->action_timer.s = 8;
        body->action_phase.u++;
        return;

    case 3:
        timer = body->action_timer.s;
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
                    ((tile_y - offset_y) << 15) / body->action_timer.s;
            }
        }

        timer = body->action_timer.u - 1;
        body->action_timer.s = timer;
        if ((s32)(timer << 16) > 0) {
            return;
        }

        motion->velocity_z = 0;
        motion->velocity_y = 0;
        motion->velocity_x = 0;
        motion->x.v = ((sprite->tile_x << 6) + 0x20) << 16;
        motion->y.v = ((sprite->tile_y << 6) + 0x20) << 16;
        set_record_integer_tile_center(motion, sprite->tile_x, sprite->tile_y);

        tracked_addr = ((s32)g_dungeon_status.pending_display_owner);
        if (tracked_addr == (s32)((u8 *)entity - 0x20)) {
            g_dungeon_status.pending_display_owner = tracked_addr & 0x7FFFFFFF;
        }
        body->unk_8C.byte_ptr = &D_80152E54;

        return;
    default:
        return;
    }
}
