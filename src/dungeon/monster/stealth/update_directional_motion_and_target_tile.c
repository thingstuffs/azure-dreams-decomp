#include "shared/actor_status_flags.h"
#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"
#include "shared/entity.h"
#include "records/Rec_D_80082E80.h"
#include "dungeon/actor.h"
#include "dungeon/player/object.h"

#include "dungeon/monster/stealth.h"
extern u8 D_80173D60[];

/* Updates directional movement and returns the entity to its target tile. */
void update_directional_motion_and_target_tile(ActorRecord *body, ObjectPosition *motion, SpriteFrameState *target, void *entity)
{
    s16 return_timer;
    s16 next_timer;
    s16 initial_timer;
    s32 velocity_y;
    s32 direction;
    s32 velocity_x;
    s32 biased_x;
    s32 biased_y;
    s32 target_x;
    s32 origin_x;
    s32 target_y;
    s32 origin_y;
    u8 state;

    state = body->action_phase.u;
    direction = (((EntityRec *)entity)->unk_6A >> 9) & 7;

    switch (state) {
    case 0:
        apply_clamped_actor_value_delta(entity);
        motion->velocity_x =
            ((s16 *)((s8 *)dir_step_x))[direction] << 16;
        motion->velocity_y =
            ((s16 *)((s8 *)dir_step_y))[direction] << 16;
        body->action_phase.u++;

        if (((EntityRec *)entity)->unk_28 == 0) {
            motion->velocity_z = 0;
            motion->velocity_y = 0;
            motion->velocity_x = 0;
            begin_actor_display_action(body, motion, target, D_80173D60);
            return;
        }
        if (target->flags & 0x8000) {
            body->action_timer.s = 0;
            body->action_phase.u = 2;
            return;
        }

        initial_timer = -1;
        if (((u32)((EntityRec *)entity)->flags1C) & (ACTOR_MP_EMPTY | ACTOR_PARALYZED | ACTOR_ASLEEP)) {
            initial_timer = 8;
        }
        body->action_timer.s = initial_timer;

        velocity_x = motion->velocity_x;
        biased_x = velocity_x;
        motion->velocity_x = velocity_x - (biased_x / 4);

        velocity_y = motion->velocity_y;
        biased_y = velocity_y;
        motion->velocity_y = velocity_y - (biased_y / 4);

    case 1:
        motion->velocity_x -=
            ((s16 *)((s8 *)dir_step_x))[direction] << 13;
        motion->velocity_y -=
            ((s16 *)((s8 *)dir_step_y))[direction] << 13;

        if (body->action_timer.s > 0) {
            body->action_timer.u = body->action_timer.u - 1;
        } else if (target->flags & 0x6000) {
            body->action_timer.s = 0;
        }

        if (body->action_timer.s != 0) {
            return;
        }
        if (((EntityRec *)entity)->unk_28 == 0) {
            motion->velocity_z = 0;
            motion->velocity_y = 0;
            motion->velocity_x = 0;
            begin_actor_display_action(body, motion, target, D_80173D60);
        } else {
            body->action_timer.s = 8;
            body->action_phase.u++;
        }
        return;

    case 2:
        return_timer = body->action_timer.s;
        if (return_timer != 0) {
            target_x = target->tile_x << 6;
            origin_x = motion->x.w.i - 0x20;
            motion->velocity_x =
                ((target_x - origin_x) << 15) / return_timer;
            target_y = target->tile_y << 6;
            origin_y = motion->y.w.i - 0x20;
            motion->velocity_y =
                ((target_y - origin_y) << 15) /
                body->action_timer.s;
        }

        next_timer = body->action_timer.u - 1;
        body->action_timer.u = next_timer;
        if (next_timer > 0) {
            return;
        }

        motion->velocity_z = 0;
        motion->velocity_y = 0;
        motion->velocity_x = 0;
        set_record_integer_tile_center(motion, target->tile_x, target->tile_y);

        if (((s32)g_dungeon_status.pending_display_owner) == (s32)entity - 0x20) {
            *(s32 *)&g_dungeon_status.pending_display_owner &= 0x7FFFFFFF;
        }
        body->unk_8C.address = stealth_behavior_entry;

        return;
    default:
        return;
    }
}

/* MECHANISM: The natural long-lived arguments preserve the retail 0x28 frame and s1/s0/s2/s3/s4 roles.
   Typed s16 array indexing materializes each table base before its direction shift.
   Split expression-form s32 coordinate temps block fold reassociation and schedule the second lh over the first divide result. */
