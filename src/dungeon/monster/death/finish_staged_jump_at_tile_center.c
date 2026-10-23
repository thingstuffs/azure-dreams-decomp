#include "common.h"
#include "dungeon/monster/death.h"
#include "shared/actor_action_flags.h"
#include "shared/sprite_frame_state.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"
#include "records/Rec_D_80082E80.h"
#include "shared/entity.h"

extern void select_sprite_entry(void *, s32, s32);
extern void resolve_attack_damage_and_effects(void *attacker_in, void *tile_in, s16 direction, s16 distance);
extern void advance_status_timers(void *);
extern void play_sound_if_enabled(s32);
extern void spend_actor_mp(void *, s32);

extern s32 death_action_resume_address;
extern u8 D_8017464C[8];
extern u8 D_80174654[8];
extern u8 D_8017465C[8];
extern u8 D_80174664[8];

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
void finish_staged_jump_at_tile_center(void *action, ObjectPosition *motion, SpriteFrameState *sprite, ActorRecord *actor)
{
    u8 state;

    state = ((S_80172DB0_0 *)action)->unk_9B;
    switch (state) {

    case 0:
        if (sprite->flags & 0x8000) {
            ((S_80172DB0_0 *)action)->unk_9B = 5;
            ((S_80172DB0_0 *)action)->unk_96.u = 0;
            sprite->flags |= 0x6000;
            resolve_attack_damage_and_effects(actor, sprite, actor->facing, 1);
            return;
        }
        motion->velocity_z = 0;
        motion->velocity_y = 0;
        motion->velocity_x = 0;
        if (((S_80172DB0_0 *)action)->unk_A4 != 0) {
            return;
        }
        sprite->frameTable = D_8017464C;
        select_sprite_entry(sprite,
            D_8017464C[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
            0);
        ((S_80172DB0_0 *)action)->unk_96.u = 8;
        ((S_80172DB0_0 *)action)->unk_9B++;
        return;

    case 1:
    {
        u16 timer = ((S_80172DB0_0 *)action)->unk_96.u;

        ((S_80172DB0_0 *)action)->unk_96.u = timer - 1;
        if ((s16)timer > 0 && !(sprite->flags & 0xE000)) {
            return;
        }
    }
        sprite->frameTable = D_80174654;
        select_sprite_entry(sprite,
            D_80174654[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
            0);
        play_sound_if_enabled(0x707);
        ((S_80172DB0_0 *)action)->unk_96.u = 6;
        ((S_80172DB0_0 *)action)->unk_AC = 0x80000;
        ((S_80172DB0_0 *)action)->unk_B0 = (s32)0xFFFE0000;
        ((S_80172DB0_0 *)action)->unk_9B++;
        motion->velocity_x =
            -*(s16 *)(((s8 *)dir_step_x) + (((u16)actor->facing >> 8) & 0xE)) << 18;
        motion->velocity_y =
            -*(s16 *)(((s8 *)dir_step_y) + (((u16)actor->facing >> 8) & 0xE)) << 18;
        return;

    case 2:
        ((S_80172DB0_0 *)action)->unk_A4 += ((S_80172DB0_0 *)action)->unk_AC;
        ((S_80172DB0_0 *)action)->unk_AC += ((S_80172DB0_0 *)action)->unk_B0;
        if (((S_80172DB0_0 *)action)->unk_96.s < 2) {
            motion->velocity_x =
                *(s16 *)(((s8 *)dir_step_x) + (((u16)actor->facing >> 8) & 0xE)) << 19;
            motion->velocity_y =
                *(s16 *)(((s8 *)dir_step_y) + (((u16)actor->facing >> 8) & 0xE)) << 19;
        }
        {
            u16 timer = ((S_80172DB0_0 *)action)->unk_96.u;

            ((S_80172DB0_0 *)action)->unk_96.u = timer - 1;
            if ((s16)timer > 0 && !(sprite->flags & 0xE000)) {
                return;
            }
        }
        resolve_attack_damage_and_effects(actor, sprite, actor->facing, 1);
        ((S_80172DB0_0 *)action)->unk_9B++;
        play_sound_if_enabled(0x804);
        return;

    case 3:
        ((S_80172DB0_0 *)action)->unk_A4 += ((S_80172DB0_0 *)action)->unk_AC;
        ((S_80172DB0_0 *)action)->unk_AC += ((S_80172DB0_0 *)action)->unk_B0;
        if (!(sprite->flags & 0xE000)) {
            return;
        }
        sprite->frameTable = D_8017465C;
        select_sprite_entry(sprite,
            D_8017465C[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
            0);
        ((S_80172DB0_0 *)action)->unk_9B++;
        motion->velocity_y = 0;
        motion->velocity_x = 0;
        ((S_80172DB0_0 *)action)->unk_A4 = 0;
        return;

    case 4:
        if (!(sprite->flags & 0xE000)) {
            return;
        }
        sprite->frameTable = D_80174664;
        select_sprite_entry(sprite,
            D_80174664[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
            0);
        ((S_80172DB0_0 *)action)->unk_96.u = 4;
        ((S_80172DB0_0 *)action)->unk_A4 = 0;
        ((S_80172DB0_0 *)action)->unk_9B++;
        {
            s32 target_x = sprite->unk_24 << 6;
            s32 current_x = motion->x.w.i - 0x20;

            motion->velocity_x = ((target_x - current_x) << 16)
            / ((S_80172DB0_0 *)action)->unk_96.s;
        }
        {
            s32 target_y = sprite->unk_25 << 6;
            s32 current_y = motion->y.w.i - 0x20;

            motion->velocity_y = ((target_y - current_y) << 16)
            / ((S_80172DB0_0 *)action)->unk_96.s;
        }
        return;

    case 5:
    {
        s16 timer = ((S_80172DB0_0 *)action)->unk_96.s;

        if (timer != 0) {
            {
                s32 target_x = sprite->unk_24 << 6;
                s32 current_x = motion->x.w.i - 0x20;

                motion->velocity_x = ((target_x - current_x) << 16) / timer;
            }
            {
                s32 target_y = sprite->unk_25 << 6;
                s32 current_y = motion->y.w.i - 0x20;

                motion->velocity_y = ((target_y - current_y) << 16)
                / ((S_80172DB0_0 *)action)->unk_96.s;
            }
        }
    }
        ((S_80172DB0_0 *)action)->unk_96.u--;
        if (!(sprite->flags & 0xE000)) {
            return;
        }
        spend_actor_mp(actor, 0x100);
        ((S_80172DB0_0 *)action)->unk_8C = &death_action_resume_address;
        g_dungeon_status.active_actor = 0;
        advance_status_timers(actor);
        motion->velocity_y = 0;
        motion->velocity_x = 0;
        motion->x.w.i = (sprite->unk_24 << 6) + 0x20;
        motion->y.w.i = (sprite->unk_25 << 6) + 0x20;
        actor->action_flags &= ACTOR_ACTION_CLEAR_PENDING_MASK;
    }
}
