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
#include "dungeon/actor/spell_resource_ids_g01008.h"
#include "engine/graphics.h"
#include "dungeon/system.h"
#include "dungeon/actor.h"
#include "dungeon/effect/screen.h"
#include "dungeon/data.h"

extern s32 death_action_resume_address;
extern u8 D_8017464C[8];

/* Updates a staged jump animation and returns the actor to its tile center. */
void finish_staged_jump_at_tile_center(ActorRecord *action, ObjectPosition *motion, SpriteFrameState *sprite, ActorRecord *actor) {
    u8 state;

    state = action->action_phase;
    switch (state) {

    case 0:
        if (sprite->flags & 0x8000) {
            action->action_phase = 5;
            action->action_timer = 0;
            sprite->flags |= 0x6000;
            resolve_attack_damage_and_effects(actor, sprite, actor->facing, 1);
            return;
        }
        motion->velocity_z = 0;
        motion->velocity_y = 0;
        motion->velocity_x = 0;
        if (action->unk_A4.value != 0) {
            return;
        }
        sprite->frameTable = D_8017464C;
        select_sprite_entry(sprite,
            D_8017464C[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
            0);
        action->action_timer = 8;
        action->action_phase++;
        return;

    case 1:
    {
        u16 timer = action->action_timer;

        action->action_timer = timer - 1;
        if ((s16)timer > 0 && !(sprite->flags & 0xE000)) {
            return;
        }
    }
        sprite->frameTable = death_frame_set_4;
        select_sprite_entry(sprite,
            death_frame_set_4[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
            0);
        play_sound_if_enabled(0x707);
        action->action_timer = 6;
        action->unk_AC.value = 0x80000;
        action->unk_B0.value = (s32)0xFFFE0000;
        action->action_phase++;
        motion->velocity_x =
            -dir_step_x[((u16)actor->facing >> 9) & 7] << 18;
        motion->velocity_y =
            -dir_step_y[((u16)actor->facing >> 9) & 7] << 18;
        return;

    case 2:
        action->unk_A4.value += action->unk_AC.value;
        action->unk_AC.value += action->unk_B0.value;
        if ((s16)(action->action_timer) < 2) {
            motion->velocity_x =
                dir_step_x[((u16)actor->facing >> 9) & 7] << 19;
            motion->velocity_y =
                dir_step_y[((u16)actor->facing >> 9) & 7] << 19;
        }
        {
            u16 timer = action->action_timer;

            action->action_timer = timer - 1;
            if ((s16)timer > 0 && !(sprite->flags & 0xE000)) {
                return;
            }
        }
        resolve_attack_damage_and_effects(actor, sprite, actor->facing, 1);
        action->action_phase++;
        play_sound_if_enabled(0x804);
        return;

    case 3:
        action->unk_A4.value += action->unk_AC.value;
        action->unk_AC.value += action->unk_B0.value;
        if (!(sprite->flags & 0xE000)) {
            return;
        }
        sprite->frameTable = death_frame_set_5;
        select_sprite_entry(sprite,
            death_frame_set_5[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
            0);
        action->action_phase++;
        motion->velocity_y = 0;
        motion->velocity_x = 0;
        action->unk_A4.value = 0;
        return;

    case 4:
        if (!(sprite->flags & 0xE000)) {
            return;
        }
        sprite->frameTable = death_frame_set_6;
        select_sprite_entry(sprite,
            death_frame_set_6[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
            0);
        action->action_timer = 4;
        action->unk_A4.value = 0;
        action->action_phase++;
        {
            s32 target_x = sprite->tile_x << 6;
            s32 current_x = motion->x.w.i - 0x20;

            motion->velocity_x = ((target_x - current_x) << 16)
            / (s16)(action->action_timer);
        }
        {
            s32 target_y = sprite->tile_y << 6;
            s32 current_y = motion->y.w.i - 0x20;

            motion->velocity_y = ((target_y - current_y) << 16)
            / (s16)(action->action_timer);
        }
        return;

    case 5:
    {
        s16 timer = (action->action_timer);

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
                / (s16)(action->action_timer);
            }
        }
    }
        action->action_timer--;
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
