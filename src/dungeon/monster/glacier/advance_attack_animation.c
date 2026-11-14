#include "engine/graphics/select_sprite_entry_api.h"
#include "common.h"
#include "dungeon/monster/glacier.h"
#include "shared/sprite_frame_state.h"
#include "shared/game_work.h"
#include "records/Rec_D_80082E80.h"
#include "dungeon/actor/status.h"
#include "dungeon/actor.h"
#include "dungeon/effect/screen.h"
#include "dungeon/system.h"

extern u8 resident_globals_page[];


typedef struct S_80172F04_4 {
    u8 unk_00;
    u8 pad_01[0x3227];
    s16 unk_3228;
    u8 pad_322A[0x242];
    s32 unk_346C;
} S_80172F04_4;   /* (u8 *)work in advance_attack_animation */

#include "dungeon/actor/spend_actor_mp_api.h"

extern u8 D_801760CC[];

/* Advances a timed actor animation sequence and resets its action on completion. */
void advance_attack_animation(ActorRecord *action, ObjectPosition *motion, SpriteFrameState *animation, void *actor_ptr)
{
    ActorRecord *actor;
    s32 state;
    u8 current_state;
    u16 timer;
    u32 work;
    void *call_actor;

    state = action->action_phase;
    actor = actor_ptr;
    switch (state) {
    case 0:
        if (animation->flags & 0x8000) {
            action->action_phase = 3;
            animation->flags |= 0x6000;
            resolve_attack_damage_and_effects(actor, animation, actor->facing, 1);
            return;
        }
        motion->velocity_z = 0;
        motion->velocity_y = 0;
        motion->velocity_x = 0;
        current_state = action->action_phase;
        action->action_timer = 0;
        action->action_phase = current_state + 1;
        return;
    case 1:
        timer = action->action_timer + 1;
        action->action_timer = timer;
        if (((s16)timer == 4) || (animation->flags & 0x8000)) {
            animation->frameTable = D_801760CC;
            work = g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100;
            work = ((s32)work >> 9) & 7;
            work += (u32)D_801760CC;
            select_sprite_entry(animation,
                ((S_80172F04_4 *)((u8 *)work))->unk_00,
                0);
            play_sound_if_enabled(0x809);
            current_state = action->action_phase;
            action->action_timer = 0;
            action->action_phase = current_state + 1;
            return;
        }
        return;
    case 2:
        timer = action->action_timer + 1;
        action->action_timer = timer;
        if (((s16)timer == 4) || (animation->flags & 0x8000)) {
            resolve_attack_damage_and_effects(actor, animation, actor->facing, 1);
            current_state = action->action_phase;
            action->action_timer = 0;
            action->action_phase = current_state + 1;
            return;
        }
        return;
    case 3:
        if (animation->flags & 0xE000) {
            spend_actor_mp(actor, 0x140);
            call_actor = actor;
            action->unk_8C.byte_ptr = (u8 *)(update_glacier_actor_behavior);
            ((S_80172F04_4 *)resident_globals_page)->unk_346C = 0;
            advance_status_timers(call_actor);
            actor->action_flags &= 0x7FFF;
        }
        return;
    default:
        return;
    }
}
