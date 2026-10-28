#include "common.h"
#include "dungeon/monster/death.h"
#include "shared/actor_action_flags.h"
#include "shared/sprite_frame_state.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"
#include "records/Rec_D_80082E80.h"
#include "shared/entity.h"
#include "dungeon/actor/status.h"

extern void select_sprite_entry(void *, s32, s32);
extern void resolve_attack_damage_and_effects(void *attacker_in, void *tile_in, s16 direction, s16 distance);
extern void play_sound_if_enabled(s32);
extern void spend_actor_mp(void *, s32);

extern s32 death_action_resume_address;
extern u8 D_8017464C[8];
extern u8 death_frame_set_4[8];
extern u8 death_frame_set_5[8];
extern u8 death_frame_set_6[8];

typedef struct S_80172DB0_0 {
    u8 pad_00[0x8C];
    s32 * unk_8C;
    u8 pad_90[0x6];
    union { u16 u; s16 s; } unk_96;   /* accessed as both */
    u8 pad_98[0x3];
    u8 unk_9B;
    u8 pad_9C[0x8];
    s32 unk_A4;
    u8 pad_A8[0x4];
    s32 unk_AC;
    s32 unk_B0;
} S_80172DB0_0;   /* arg0 in finish_staged_jump_at_tile_center */


/* Updates a staged jump animation and returns the actor to its tile center. */
void finish_staged_jump_at_tile_center(ActorRecord *action, ObjectPosition *motion, SpriteFrameState *sprite, ActorRecord *actor) {
    u8 state;

    state = action->action_phase.u;
    switch (state) {

    case 0:
        if (sprite->flags & 0x8000) {
            action->action_phase.u = 5;
            action->action_timer.u = 0;
            sprite->flags |= 0x6000;
            resolve_attack_damage_and_effects(actor, sprite, actor->facing, 1);
            return;
        }
        motion->velocity_z = 0;
        motion->velocity_y = 0;
        motion->velocity_x = 0;
        if (action->unk_A4 != 0) {
            return;
        }
        sprite->frameTable = D_8017464C;
        select_sprite_entry(sprite,
            D_8017464C[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
            0);
        action->action_timer.u = 8;
        action->action_phase.u++;
        return;

    case 1:
    {
        u16 timer = action->action_timer.u;

        action->action_timer.u = timer - 1;
        if ((s16)timer > 0 && !(sprite->flags & 0xE000)) {
            return;
        }
    }
        sprite->frameTable = death_frame_set_4;
        select_sprite_entry(sprite,
            death_frame_set_4[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
            0);
        play_sound_if_enabled(0x707);
        action->action_timer.u = 6;
        ((S_80172DB0_0 *)action)->unk_AC = 0x80000;
        ((S_80172DB0_0 *)action)->unk_B0 = (s32)0xFFFE0000;
        action->action_phase.u++;
        motion->velocity_x =
            -*(s16 *)(((s8 *)dir_step_x) + (((u16)actor->facing >> 8) & 0xE)) << 18;
        motion->velocity_y =
            -*(s16 *)(((s8 *)dir_step_y) + (((u16)actor->facing >> 8) & 0xE)) << 18;
        return;

    case 2:
        action->unk_A4 += ((S_80172DB0_0 *)action)->unk_AC;
        ((S_80172DB0_0 *)action)->unk_AC += ((S_80172DB0_0 *)action)->unk_B0;
        if (action->action_timer.s < 2) {
            motion->velocity_x =
                *(s16 *)(((s8 *)dir_step_x) + (((u16)actor->facing >> 8) & 0xE)) << 19;
            motion->velocity_y =
                *(s16 *)(((s8 *)dir_step_y) + (((u16)actor->facing >> 8) & 0xE)) << 19;
        }
        {
            u16 timer = action->action_timer.u;

            action->action_timer.u = timer - 1;
            if ((s16)timer > 0 && !(sprite->flags & 0xE000)) {
                return;
            }
        }
        resolve_attack_damage_and_effects(actor, sprite, actor->facing, 1);
        action->action_phase.u++;
        play_sound_if_enabled(0x804);
        return;

    case 3:
        action->unk_A4 += ((S_80172DB0_0 *)action)->unk_AC;
        ((S_80172DB0_0 *)action)->unk_AC += ((S_80172DB0_0 *)action)->unk_B0;
        if (!(sprite->flags & 0xE000)) {
            return;
        }
        sprite->frameTable = death_frame_set_5;
        select_sprite_entry(sprite,
            death_frame_set_5[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
            0);
        action->action_phase.u++;
        motion->velocity_y = 0;
        motion->velocity_x = 0;
        action->unk_A4 = 0;
        return;

    case 4:
        if (!(sprite->flags & 0xE000)) {
            return;
        }
        sprite->frameTable = death_frame_set_6;
        select_sprite_entry(sprite,
            death_frame_set_6[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
            0);
        action->action_timer.u = 4;
        action->unk_A4 = 0;
        action->action_phase.u++;
        {
            s32 target_x = sprite->tile_x << 6;
            s32 current_x = motion->x.w.i - 0x20;

            motion->velocity_x = ((target_x - current_x) << 16)
            / action->action_timer.s;
        }
        {
            s32 target_y = sprite->tile_y << 6;
            s32 current_y = motion->y.w.i - 0x20;

            motion->velocity_y = ((target_y - current_y) << 16)
            / action->action_timer.s;
        }
        return;

    case 5:
    {
        s16 timer = action->action_timer.s;

        if (timer != 0) {
            {
                s32 target_x = sprite->tile_x << 6;
                s32 current_x = motion->x.w.i - 0x20;

                motion->velocity_x = ((target_x - current_x) << 16) / timer;
            }
            {
                s32 target_y = sprite->tile_y << 6;
                s32 current_y = motion->y.w.i - 0x20;

                motion->velocity_y = ((target_y - current_y) << 16)
                / action->action_timer.s;
            }
        }
    }
        action->action_timer.u--;
        if (!(sprite->flags & 0xE000)) {
            return;
        }
        spend_actor_mp(actor, 0x100);
        action->unk_8C.address = &death_action_resume_address;
        g_dungeon_status.active_actor = 0;
        advance_status_timers(actor);
        motion->velocity_y = 0;
        motion->velocity_x = 0;
        motion->x.w.i = (sprite->tile_x << 6) + 0x20;
        motion->y.w.i = (sprite->tile_y << 6) + 0x20;
        actor->action_flags &= ACTOR_ACTION_CLEAR_PENDING_MASK;
    }
}
