#include "common.h"
#include "shared/actor_action_flags.h"
#include "shared/sprite_frame_state.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_D_80082E80.h"
#include "shared/entity.h"
#include "dungeon/actor/status.h"
#include "dungeon/actor/spell_resource_ids_g01008.h"

extern u8 blume_action_resume_address[];
extern void resolve_attack_damage_and_effects(void *attacker_in, void *tile_in, s16 direction, s16 distance);
extern void play_sound_if_enabled(s32);

extern void select_sprite_entry(void *, u8, s32);
extern u8 D_801753E4[];

typedef struct S_801735E8_0 {
    u8 pad_00[0x8C];
    u8 * unk_8C;
    u8 pad_90[0x6];
    u16 unk_96;
    u8 pad_98[0x3];
    u8 unk_9B;
} S_801735E8_0;   /* base0 in advance_actor_staged_animation */

typedef struct S_801735E8_3 {
    u8 pad_00[0xC];
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_801735E8_3;   /* arg1 in advance_actor_staged_animation */

/* Advances the actor's staged animation sequence and handles completion. */
void advance_actor_staged_animation(ActorRecord *action_data, ObjectPosition *motion, SpriteFrameState *animation, ActorRecord *actor) {
    ActorRecord *action;
    u16 phase_value;
    u16 elapsed_ticks;
    s32 phase;
    action = action_data;

    phase = action->action_phase.u;
    switch (phase) {
    case 0:
        if (animation->flags & 0x8000) {
            action->action_phase.u = 3U;
            animation->flags = (u16) (animation->flags | 0x6000);
            resolve_attack_damage_and_effects(actor, animation, actor->facing, 1);
            return;
        }
        motion->velocity_z = 0;
        motion->velocity_y = 0;
        motion->velocity_x = 0;
        phase_value = action->action_phase.u;
        action->action_timer.u = 0U;
        action->action_phase.u = (u8) (phase_value + 1);
        return;

    case 1:
        elapsed_ticks = action->action_timer.u + 1;
        action->action_timer.u = elapsed_ticks;
        if ((s16) elapsed_ticks != 4 && !(animation->flags & 0xE000)) {
            return;
        }
        animation->frameTable = &D_801753E4;
        select_sprite_entry(animation, D_801753E4[(((s32) (g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7)], 0);
        play_sound_if_enabled(0x808);
        phase_value = action->action_phase.u;
        action->action_timer.u = 0U;
        action->action_phase.u = (u8) (phase_value + 1);
        return;

    case 2:
        phase_value = action->action_timer.u + 1;
        action->action_timer.u = phase_value;
        if ((s16) phase_value != 4 && !(animation->flags & 0xE000)) {
            return;
        }
        resolve_attack_damage_and_effects(actor, animation, actor->facing, 1);
        phase_value = action->action_phase.u;
        action->action_timer.u = 0U;
        action->action_phase.u = (u8) (phase_value + 1);
        return;

    case 3:
        if (animation->flags & 0xE000) {
            spend_actor_mp(actor, 0x100);
            action->unk_8C.address = blume_action_resume_address;
            g_dungeon_status.active_actor = 0;
            advance_status_timers(actor);
            actor->action_flags = (u16) (actor->action_flags & ACTOR_ACTION_CLEAR_PENDING_MASK);
        }
    }
}
