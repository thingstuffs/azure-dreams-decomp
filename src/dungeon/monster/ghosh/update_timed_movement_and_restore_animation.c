#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"
#include "dungeon/actor.h"
#include "dungeon/player/object.h"

extern u8 ghosh_action_resume_address[];
extern u8 ghosh_frame_set_3[];
extern u8 ghosh_frame_set_4[];
#include "dungeon/monster/ghosh.h"
#include "engine/graphics.h"
extern u8 D_801746CC[];

/* Updates timed movement, returns the entity to its tile, and restores its animation. */
/* Applies Ghosh's pending HP change, animates damped recoil, then recenters it and updates its action
 * state. */
void update_timed_movement_and_restore_animation(ActorRecord *body, ObjectPosition *motion, SpriteFrameState *sprite,
    ActorRecord *actor) {
    s32 state;
    s16 timer;
    s16 next_timer;
    u16 timer_bits;
    s32 facing;
    s32 anim_addr;
    s32 timer_ending;
    s32 velocity_x;
    s32 velocity_y;
    s32 tile_x;
    s32 offset_x;
    s32 tile_y;
    s32 offset_y;
    u8 *final_state;
    s32 state_bits;
    u16 saved_timer;
    s32 shifted_timer;
    u8 *anim_table;

    state = body->action_phase.u;
    switch (state) {
    case 0:
        apply_clamped_actor_value_delta(actor);
        body->action_timer.s = 12;
        body->action_phase.u = (u8)(body->action_phase.u + 1);
        if (actor->hp == 0) {
            motion->velocity_z = 0;
            motion->velocity_y = 0;
            motion->velocity_x = 0;
            if (body->unk_B4.bytes[0] != 0) {
                body->action_phase.u = 0;
                body->unk_8C.address = ghosh_action_resume_address;
                return;
            }
            body->action_phase.u = 0;
            begin_actor_display_action(body, motion, sprite, D_801746CC);
            return;
        }
        final_state = (u8 *)3;
        if (!(sprite->flags & 0x8000)) {
            return;
        }
        body->action_timer.s = 0;
        body->action_phase.u = (u32)final_state;
        return;

    case 1:
        timer_bits = body->action_timer.u;
        timer_bits--;
        body->action_timer.u = timer_bits;
        timer = (s16)timer_bits;
        if (timer >= 11) {
            motion->velocity_x =
            *(s16 *)((u8 *)dir_step_x + ((actor->movement_facing >> 8) & 0xE)) << 20;
            motion->velocity_y =
            *(s16 *)((u8 *)dir_step_y + ((actor->movement_facing >> 8) & 0xE)) << 20;
            sprite->flags |= 0x800;
            return;
        }
        if (timer >= 7) {
            velocity_x = motion->velocity_x;
            if (velocity_x < 0) {
                velocity_x += 3;
            }
            velocity_y = motion->velocity_y;
            motion->velocity_x = velocity_x >> 2;
            motion->velocity_y = (velocity_y / 4);
            return;
        }
        timer_ending = timer < 2;
        if (!timer_ending) {
            motion->velocity_y = 0;
            motion->velocity_x = 0;
            return;
        }
        if (timer == state) {
            sprite->flags &= 0xF7FF;
            return;
        }
        if (timer != 0) {
            return;
        }
        timer = 4;
        state_bits = body->action_phase.u;
        body->action_timer.s = timer;
        body->action_phase.u = (u8)(state_bits + 1);
        return;
    case 2:
        timer = body->action_timer.s;
        if (timer != 0) {
            tile_x = sprite->tile_x << 6;
            offset_x = motion->x.w.i - 32;
            motion->velocity_x = ((tile_x - offset_x) << 16) / timer;
            tile_y = sprite->tile_y << 6;
            offset_y = motion->y.w.i - 32;
            motion->velocity_y =
            ((tile_y - offset_y) << 16) / body->action_timer.s;
        }
        saved_timer = body->action_timer.u;
        next_timer = (s16)(saved_timer - 1);
        shifted_timer = (s32)saved_timer << 16;
        body->action_timer.s = next_timer;
        if (shifted_timer > 0) {
            return;
        }
        motion->velocity_z = 0;
        motion->velocity_y = 0;
        motion->velocity_x = 0;
        state_bits = body->action_phase.u;
        body->action_phase.u = (u8)(state_bits + 1);
        return;

    case 3:
        motion->velocity_z = 0;
        motion->velocity_y = 0;
        motion->velocity_x = 0;
        set_record_integer_tile_center(motion, sprite->tile_x, sprite->tile_y);
        if (actor->hp == 0) {
            motion->velocity_z = 0;
            motion->velocity_y = 0;
            motion->velocity_x = 0;
            if (body->unk_B4.bytes[0] == 0) {
                body->action_phase.u = 0;
                begin_actor_display_action(body, motion, sprite, D_801746CC);
                return;
            } else {
                u8 *result_bits = ghosh_action_resume_address;
                body->action_phase.u = 0;
                body->unk_8C.address = result_bits;
                return;
            }
        }
        anim_addr = *(s32 *)&sprite->frameTable;
        if (anim_addr == (s32)ghosh_ready_action_frames) {
            if (body->unk_B0.bytes[3] == 0) {
                anim_table = ghosh_frame_set_3;
            } else {
                anim_table = ghosh_frame_set_4;
            }
            if (anim_addr != (s32)anim_table) {
                sprite->frameTable = anim_table;
                facing = g_game_work.view.camera_rotation.parts.viewAngle + actor->facing;
                select_sprite_entry(sprite, *(u8 *)((u32)(((facing + 0x100) >> 9) & 7) + (unsigned long)anim_table), 0);
            }
        }
        if ((g_dungeon_status.pending_display_owner) == (u8 *)actor - 0x20) {
            *(s32 *)&g_dungeon_status.pending_display_owner &= 0x7FFFFFFF;
        }
        body->unk_8C.address = ghosh_action_resume_address;
        return;
    }
}
