#include "shared/actor_status_flags.h"
#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"
#include "shared/entity.h"
#include "records/Rec_D_80082E80.h"
#include "dungeon/actor.h"
#include "dungeon/player/object.h"

extern s32 ifrit_action_resume_address;
extern s32 D_80174838;

/* Updates directional motion and settles the entity at its grid position. */
void update_directional_motion_and_settle(ActorRecord *body, ObjectPosition *motion, SpriteFrameState *sprite, void *source)
{
    s16 timer;
    s32 direction;
    s32 tracked_addr;

    direction = (((EntityRec *)source)->unk_6A >> 9) & 7;
    switch (body->action_phase.u) {
    case 0:
        apply_clamped_actor_value_delta(source);
        motion->velocity_x =
            *(s16 *)((u8 *)((s8 *)dir_step_x) + (direction * 2)) << 18;
        motion->velocity_y =
            *(s16 *)((u8 *)((s8 *)dir_step_y) + (direction * 2)) << 18;
        body->action_phase.u++;

        if (((EntityRec *)source)->unk_28 == 0) {
            motion->velocity_z = 0;
            motion->velocity_y = 0;
            motion->velocity_x = 0;
            begin_actor_display_action(body, motion, sprite, &D_80174838);
            return;
        }
        if (sprite->flags & 0x8000) {
            body->action_timer.s = 0;
            body->action_phase.u = 2;
            return;
        }
        if (((EntityRec *)source)->flags1C & (ACTOR_MP_EMPTY | ACTOR_PARALYZED | ACTOR_ASLEEP)) {
            timer = 8;
        } else {
            timer = -1;
        }
        body->action_timer.s = timer;
        motion->velocity_x -= motion->velocity_x / 4;
        motion->velocity_y -= motion->velocity_y / 4;
                        /* fall through */

    case 1:
        motion->velocity_x -=
            *(s16 *)((u8 *)((s8 *)dir_step_x) + (direction * 2)) << 14;
        motion->velocity_y -=
            *(s16 *)((u8 *)((s8 *)dir_step_y) + (direction * 2)) << 14;
        if (body->action_timer.s > 0) {
            body->action_timer.s = body->action_timer.u - 1;
        } else if (sprite->flags & 0x6000) {
            body->action_timer.s = 0;
        }
        if (body->action_timer.s != 0) {
            return;
        }
        if (((EntityRec *)source)->unk_28 == 0) {
            motion->velocity_z = 0;
            motion->velocity_y = 0;
            motion->velocity_x = 0;
            begin_actor_display_action(body, motion, sprite, &D_80174838);
            return;
        } else {
            body->action_timer.s = 8;
            body->action_phase.u++;
        }
        return;

    case 2:
        if (body->action_timer.s != 0) {
            {
                s32 target_x = sprite->tile_x << 6;
                s32 current_x = motion->x.w.i - 0x20;

                motion->velocity_x = ((target_x - current_x) << 15) >> 1;
            }
            {
                s32 target_y = sprite->tile_y << 6;
                s32 current_y = motion->y.w.i - 0x20;

                motion->velocity_y = ((target_y - current_y) << 15) >> 1;
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
        set_record_integer_tile_center(motion, sprite->tile_x, sprite->tile_y);

        tracked_addr = ((s32)g_dungeon_status.pending_display_owner);
        if (tracked_addr == (s32)((u8 *)source - 0x20)) {
            g_dungeon_status.pending_display_owner = tracked_addr & 0x7FFFFFFF;
        }
        body->unk_8C.address = &ifrit_action_resume_address;
        return;

    default:
        return;
    }
}
