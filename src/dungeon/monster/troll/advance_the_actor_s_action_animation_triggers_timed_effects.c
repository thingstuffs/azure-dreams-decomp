#include "common.h"
#include "dungeon/monster/troll.h"
#include "shared/actor_action_flags.h"
#include "shared/sprite_frame_state.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_D_80082E80.h"
#include "shared/entity.h"
#include "dungeon/actor/status.h"
#include "dungeon/actor/spell_resource_ids_g01008.h"

typedef struct S_8016E3C4_0 {
    u8 pad_00[0x8C];
    u8 * unk_8C;
    u8 pad_90[0x6];
    union { u16 s; s16 u; } unk_96;   /* accessed as both */
    u8 pad_98[0x3];
    u8 unk_9B;
    u8 pad_9C[0xE];
    s16 unk_AA;
} S_8016E3C4_0;   /* arg0 in advance_the_actor_s_action_animation_triggers_timed_effects */


extern void select_sprite_entry(void *, s32, s32);
extern void resolve_attack_damage_and_effects(void *attacker_in, void *tile_in, s16 direction, s16 distance);
extern void play_sound_if_enabled(s32);

extern void func_8016B21C(void *, void *, void *, void *);
extern void func_8016B4FC(ActorRecord *source_object, ObjectPosition *source_pos, SpriteFrameState *sprite_template, ActorRecord *actor);

extern u8 D_8016C4BC[];
extern u8 D_8016FDDC[8];
extern u8 D_8016FDE4[8];
extern u8 D_8016FDEC[8];

/*
 * Stops motion and selects directional attack frames for action codes 13, 14, or 15. Schedules
 * sounds, damage, and the extra action-15 effects by tick or animation completion, then charges
 * MP, advances status timers, and releases the active actor.
 */
void advance_the_actor_s_action_animation_triggers_timed_effects(ActorRecord *action, ObjectPosition *motion, SpriteFrameState *anim, ActorRecord *actor) {
    s16 timer;
    u8 state;

    state = action->action_phase.u;
    switch (state) {

    case 0:
        motion->velocity_z = 0;
        motion->velocity_y = 0;
        motion->velocity_x = 0;
        action->action_timer.u = 0;
        action->action_phase.u++;
        if (!(anim->flags & 0x8000)) {
            return;
        }

    case 1:
        timer = action->action_timer.u + 1;
        action->action_timer.u = timer;
        if ((timer != 4) && !(anim->flags & 0x8000)) {
            return;
        }
        action->action_timer.u = 0;
        action->action_phase.u++;
        switch (actor->unk_48) {
        case 13:
            anim->frameTable = D_8016FDDC;
            select_sprite_entry(anim,
                D_8016FDDC[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
                0);
            return;
        case 14:
            anim->frameTable = D_8016FDE4;
            select_sprite_entry(anim,
                D_8016FDE4[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
                0);
            return;
        case 15:
            anim->frameTable = D_8016FDEC;
            select_sprite_entry(anim,
                D_8016FDEC[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
                0);
            action->action_phase.u = 5;
            play_sound_if_enabled(0x60C);
            return;
        default:
            return;
        }

    case 2:
        timer = action->action_timer.u + 1;
        action->action_timer.u = timer;
        if ((timer == 5) || (anim->flags & 0x8000)) {
            resolve_attack_damage_and_effects(actor, anim, actor->facing, 1);
            action->action_timer.u = 0;
            action->action_phase.u++;
        }
        if (action->action_timer.s == 3) {
            play_sound_if_enabled(0x804);
            return;
        }
        return;

    case 3:
        if (anim->flags & 0xE000) {
            spend_actor_mp(actor, 0x100);
            action->unk_8C.address = D_8016C4BC;
            g_dungeon_status.active_actor = 0;
            advance_status_timers(actor);
            actor->action_flags &= ACTOR_ACTION_CLEAR_PENDING_MASK;
        }
        return;

    case 5:
        timer = action->action_timer.u + 1;
        action->action_timer.u = timer;
        if ((timer == 10) || (anim->flags & 0x8000)) {
            anim->flags |= 0x0800;
            play_sound_if_enabled(0x804);
            func_8016B21C(action, motion, anim, actor);
            func_8016B4FC(action, motion, anim, actor);
        }
        if ((action->action_timer.s == 12) ||
            (anim->flags & 0x8000)) {
            resolve_attack_damage_and_effects(actor, anim, actor->facing,
                action->unk_AA);
        }
        if ((action->action_timer.s == 20) ||
            (anim->flags & 0x8000)) {
            anim->flags &= 0xF7FF;
            action->action_timer.u = 0;
            action->action_phase.u = 3;
        }
    case 4:
    default:
        return;
    }
}
