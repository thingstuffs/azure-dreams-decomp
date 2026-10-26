#include "common.h"
#include "shared/actor_action_flags.h"
#include "shared/sprite_frame_state.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_D_80082E80.h"
#include "shared/entity.h"
#include "shared/position_views.h"
#include "dungeon/actor/status.h"

extern void select_sprite_entry(void *, s32, s32);
extern void resolve_attack_damage_and_effects(void *attacker_in, void *tile_in, s16 direction, s16 distance);
extern void play_sound_if_enabled(s32);
extern void spend_actor_mp(void *, s32);

extern s32 weadog_action_resume_address;
extern u8 weadog_frame_set_2[];

typedef struct S_80173514_0 {
    u8 pad_00[0x8C];
    s32 * unk_8C;
    u8 pad_90[0x6];
    union { u16 u; s16 s; } unk_96;   /* accessed as both */
    u8 pad_98[0x3];
    u8 unk_9B;
} S_80173514_0;   /* arg0 in advance_timed_sprite_flashing_sequence */

   /* arg1 in advance_timed_sprite_flashing_sequence */

/* Advance a timed sprite flashing sequence and clean up the actor when it finishes. */
/* Times Weadog's attack animation and damage around sprite pauses, then spends MP and restores the action
 * callback. */
void advance_timed_sprite_flashing_sequence(ActorRecord *action, ObjectPosition *motion, SpriteFrameState *sprite, ActorRecord *actor) {
    u8 state;
    ActorRecord *call_actor;
    SpriteFrameState *call_sprite;

    state = action->action_phase;
    switch (state) {
    default:
        return;

    case 0:
    {
        call_actor = actor;
        if (sprite->flags & 0x8000) {
            action->action_phase = 4;
            call_sprite = sprite;
            call_sprite->flags |= 0x6000;
            resolve_attack_damage_and_effects(call_actor, call_sprite, call_actor->facing, 1);
            return;
        }
        ((MotionDeltaView *)motion)->velocity_z = 0;
        ((MotionDeltaView *)motion)->velocity_y = 0;
        ((MotionDeltaView *)motion)->velocity_x = 0;
        sprite->frameTable = weadog_frame_set_2;
        select_sprite_entry(sprite,
            weadog_frame_set_2[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
            0);
        ((S_80173514_0 *)action)->unk_96.u = 0;
        action->action_phase++;
        return;
    }

    case 1:
        if ((s16)++((S_80173514_0 *)action)->unk_96.u == 5) {
            ((S_80173514_0 *)action)->unk_96.u = 0;
            action->action_phase++;
            sprite->flags |= 0x0800;
            return;
        }
        return;

    case 2:
        if ((s16)++((S_80173514_0 *)action)->unk_96.u == 6 ||
            (sprite->flags & 0xE000)) {
            ((S_80173514_0 *)action)->unk_96.u = 0;
            action->action_phase++;
            sprite->flags &= 0xF7FF;
            play_sound_if_enabled(0x804);
            return;
        }
        return;

    case 3:
        if ((s16)++((S_80173514_0 *)action)->unk_96.u == 5 ||
            (sprite->flags & 0xE000)) {
            sprite->flags |= 0x0800;
        }
        if (((S_80173514_0 *)action)->unk_96.s == 12 ||
            (sprite->flags & 0xE000)) {
            ((S_80173514_0 *)action)->unk_96.u = 0;
            action->action_phase++;
            sprite->flags &= 0xF7FF;
        }
        call_actor = actor;
        if (((S_80173514_0 *)action)->unk_96.s == 1 ||
            (sprite->flags & 0xE000)) {
            call_sprite = sprite;
            resolve_attack_damage_and_effects(call_actor, call_sprite, call_actor->facing, 1);
            return;
        }
        return;

    case 4:
        if (sprite->flags & 0xE000) {
            spend_actor_mp(actor, 0x100);
            ((S_80173514_0 *)action)->unk_8C = &weadog_action_resume_address;
            g_dungeon_status.active_actor = 0;
            advance_status_timers(actor);
            actor->action_flags &= ACTOR_ACTION_CLEAR_PENDING_MASK;
        }
    }
}
