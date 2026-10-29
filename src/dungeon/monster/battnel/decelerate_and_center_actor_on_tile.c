#include "shared/actor_status_flags.h"
#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"
#include "shared/entity.h"
#include "records/Rec_D_80082E80.h"
#include "dungeon/actor.h"
#include "dungeon/player/object.h"

typedef struct S_80172EF4_1 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x6];
    union { s16 s; u16 u; } unk_96;   /* accessed as both */
    u8 pad_98[0x3];
    u8 unk_9B;
} S_80172EF4_1;   /* arg0 in decelerate_and_center_actor_on_tile */

extern u8 battnel_action_resume_address[];
#include "dungeon/monster/battnel.h"
#include "engine/graphics.h"
extern s32 D_80173D24;

/* Apply directional movement, slow it down, and return the actor to its tile center. */
void decelerate_and_center_actor_on_tile(ActorRecord *action, ObjectPosition *motion, SpriteFrameState *sprite, ActorRecord *actor) {
    s16 timer;
    s16 *x_steps;
    s16 *y_step;
    s32 direction;
    s32 initial_step_offset;
    s32 velocity_x;
    s32 velocity_y;
    s32 brake_step_offset;
    s32 biased_velocity_x;
    s32 biased_velocity_y;
    s32 target_x;
    s32 offset_x;
    s32 target_y;
    s32 offset_y;
    s32 actor_ref;

    direction = (actor->movement_facing >> 9) & 7;

    switch (action->action_phase.u) {
    case 0:
        apply_clamped_actor_value_delta(actor);
        x_steps = (s16 *)((s8 *)dir_step_x);
        initial_step_offset = direction * 2;
        motion->velocity_x =
            *(s16 *)((u8 *)x_steps + initial_step_offset) << 0x12;
        motion->velocity_y =
            *(s16 *)((u8 *)((s8 *)dir_step_y) + initial_step_offset) << 0x12;
        action->action_phase.u++;

        if (actor->hp == 0) {
            motion->velocity_z = 0;
            motion->velocity_y = 0;
            motion->velocity_x = 0;
            begin_actor_display_action(action, motion, sprite, &D_80173D24);
            return;
        }
        if (sprite->flags & 0x8000) {
            action->action_timer.s = 0;
            action->action_phase.u = 2;
            return;
        }

        timer = -1;
        if (actor->flags1C & (ACTOR_MP_EMPTY | ACTOR_PARALYZED | ACTOR_ASLEEP)) {
            timer = 8;
        }
        action->action_timer.s = timer;

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
        x_steps = (s16 *)((s8 *)dir_step_x);
        brake_step_offset = direction * 2;
        y_step = (s16 *)((u8 *)((s8 *)dir_step_y) + brake_step_offset);
        motion->velocity_x -=
            *(s16 *)((u8 *)x_steps + brake_step_offset) << 0xF;
        motion->velocity_y -= *y_step << 0xF;

        if (action->action_timer.s > 0) {
            action->action_timer.s = action->action_timer.u - 1;
        } else if (sprite->flags & 0x6000) {
            action->action_timer.s = 0;
        }
        if (action->action_timer.s != 0) {
            return;
        }
        if (actor->hp == 0) {
            motion->velocity_z = 0;
            motion->velocity_y = 0;
            motion->velocity_x = 0;
            begin_actor_display_action(action, motion, sprite, &D_80173D24);
            return;
        }
        action->action_timer.s = 4;
        action->action_phase.u++;
        return;

    case 2:
        if (action->action_timer.s != 0) {
            target_x = sprite->tile_x << 6;
            offset_x = motion->x.w.i - 0x20;
            motion->velocity_x = (target_x - offset_x) << 0x10 >> 1;
            target_y = sprite->tile_y << 6;
            offset_y = motion->y.w.i - 0x20;
            motion->velocity_y = (target_y - offset_y) << 0x10 >> 1;
        }

        timer = action->action_timer.u - 1;
        action->action_timer.s = timer;
        if ((s32)(timer << 16) > 0) {
            return;
        }

        motion->velocity_z = 0;
        motion->velocity_y = 0;
        motion->velocity_x = 0;
        set_record_integer_tile_center(motion, sprite->tile_x, sprite->tile_y);

        sprite->frameTable = battnel_direction_frames;
        select_sprite_entry(sprite,
            battnel_direction_frames[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
            0);

        actor_ref = ((s32)g_dungeon_status.pending_display_owner);
        if (actor_ref == (s32)((u8 *)actor - 0x20)) {
            g_dungeon_status.pending_display_owner = actor_ref & 0x7FFFFFFF;
        }
        action->unk_8C.address = battnel_action_resume_address;
        return;

    default:
        return;
    }
}
