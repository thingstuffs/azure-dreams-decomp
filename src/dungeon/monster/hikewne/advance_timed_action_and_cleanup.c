#include "common.h"
#include "dungeon/monster/hikewne.h"
#include "shared/sprite_frame_state.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_D_80082E80.h"
#include "dungeon/actor/status.h"
#include "dungeon/actor.h"
#include "dungeon/effect/screen.h"
#include "dungeon/system.h"
#include "dungeon/data.h"

extern void select_sprite_entry(void *, s32, s32);
extern void spend_actor_mp(void *, s32);

/* Advances a timed action through animation setup, execution, and cleanup. */
void advance_timed_action_and_cleanup(ActorRecord *action_data, ObjectPosition *position, SpriteFrameState *sprite, ActorRecord *actor_data)
{
    register ActorRecord *action = action_data;
    register ActorRecord *actor = actor_data;
    u8 state;
    u16 timer;

    state = action->action_phase;
    if ((u32)state >= 5) {
        return;
    }
    switch (state) {
    case 0:
        timer = action->action_timer;
        action->action_timer = timer + 1;
        if ((s16)timer < 4 && !(sprite->flags & 0x8000)) {
            return;
        }
        state = action->action_phase;
        action->action_timer = 0;
        action->action_phase = state + 1;
        return;

    case 1:
        if ((s16)action->unk_A0.parts.high != 0 &&
            !(sprite->flags & 0x8000)) {
            return;
        }
        sprite->frameTable = hikewne_frame_set_16;
        select_sprite_entry(
            sprite,
            hikewne_frame_set_16[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
            0);
        state = action->action_phase;
        action->action_timer = 0;
        action->unk_A0.parts.high = 0;
        action->unk_9E = 0;
        action->action_phase = state + 1;
        return;

    case 2:
        timer = action->action_timer + 1;
        action->action_timer = timer;
        if ((s16)timer == 9 || (sprite->flags & 0x8000)) {
            resolve_attack_damage_and_effects(actor, sprite, actor->facing, 1);
            action->action_timer = 0;
            action->action_phase++;
        }
        if ((s16)action->action_timer != 6) {
            return;
        }
        play_sound_if_enabled(0x808);
        return;

    case 3:
        state = action->action_phase;
        action->action_timer = 0;
        action->action_phase = state + 1;
    case 4:
        if (!(sprite->flags & 0xE000)) {
            return;
        }
        spend_actor_mp(actor, 0x100);
        action->unk_8C.address = update_actor_behavior_animation_and_facing;
        g_dungeon_status.active_actor = 0;
        advance_status_timers(actor);
        actor->action_flags &= 0x7FFF;

        return;
    }
}
