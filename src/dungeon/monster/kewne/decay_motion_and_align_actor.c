#include "common.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"
#include "dungeon/player/object.h"
#include "shared/sprite_frame_state.h"
#include "dungeon/actor.h"
#include "dungeon/monster/kewne.h"

extern s32 kewne_action_resume_address[];
extern u8 D_80175E90[];

/* Decays motion, then aligns the actor with its grid position. */
void decay_motion_and_align_actor(ActorRecord *action, ObjectPosition *motion, SpriteFrameState *sprite, ActorRecord *actor) {
    s32 state;
    s32 x_velocity;
    s32 z_velocity;
    s32 x_rounding;
    s32 z_rounding;
    s32 tile_coord;
    s32 center_offset;
    s16 motion_frames;
    s32 align_frames;
    s16 next_frames;

    switch (action->action_phase.u) {
    case 0:
        apply_clamped_actor_value_delta(actor);
        action->action_phase.u = action->action_phase.u + 1;
        if (actor->hp == 0) {
            motion->velocity_z = 0;
            motion->velocity_y = 0;
            motion->velocity_x = 0;
            begin_actor_display_action(action, motion, sprite, D_80175E90);
            return;
        }
        if (sprite->flags & 0x8000) {
            action->action_timer.s = 0;
            action->action_phase.u = 2;
            return;
        }
        motion->velocity_x =
            (-*(s16 *)((u8 *)dir_step_x + ((actor->movement_facing >> 8) & 0xE))) << 15;
        motion->velocity_y =
            (-*(s16 *)((u8 *)dir_step_y + ((actor->movement_facing >> 8) & 0xE))) << 15;
        motion_frames = -1;
        if (actor->flags1C & 0x228) {
            motion_frames = 8;
        }
        action->action_timer.s = motion_frames;


    case 1:
        x_velocity = motion->velocity_x;
        x_rounding = x_velocity;
        if (x_velocity < 0) {
            x_rounding = x_velocity + 3;
        }
        z_velocity = motion->velocity_y;
        motion->velocity_x = x_velocity - (x_rounding >> 2);
        z_rounding = z_velocity;
        motion->velocity_y = z_velocity - (z_rounding / 4);
        if (action->action_timer.s > 0) {
            next_frames = action->action_timer.u - 1;
            action->action_timer.s = next_frames;
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
            begin_actor_display_action(action, motion, sprite, D_80175E90);
            return;
        }
        state = action->action_phase.u;
        motion_frames = 8;
        action->action_timer.s = motion_frames;
        action->action_phase.u = state + 1;
        return;

    case 2:
        align_frames = action->action_timer.s;
        if (align_frames != 0) {
            tile_coord = sprite->tile_x;
            tile_coord <<= 6;
            center_offset = motion->x.w.i - 0x20;

            motion->velocity_x = ((tile_coord - center_offset) << 15) /
                                   align_frames;
            center_offset = motion->y.w.i - 0x20;
            motion->velocity_y = ((((sprite->tile_y) << 6) - center_offset) << 15) /
                                    action->action_timer.s;
        }
        next_frames = (u16)action->action_timer.s - 1;
        action->action_timer.s = next_frames;
        if ((next_frames << 16) > 0) {
            return;
        }
        motion->velocity_z = 0;
        motion->velocity_y = 0;
        motion->velocity_x = 0;
        set_record_integer_tile_center(motion, sprite->tile_x, sprite->tile_y);
        if ((g_dungeon_status.pending_display_owner) == (u8 *)actor - 0x20) {
            *(s32 *)&g_dungeon_status.pending_display_owner &= 0x7FFFFFFF;
        }
        action->unk_8C.address = kewne_action_resume_address;
        return;

    default:
        return;
    }
}
