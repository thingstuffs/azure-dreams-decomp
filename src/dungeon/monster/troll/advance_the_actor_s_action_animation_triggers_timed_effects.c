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
#include "engine/graphics.h"
#include "dungeon/system.h"
#include "dungeon/actor.h"
#include "dungeon/effect/screen.h"



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

    state = action->action_phase;
    switch (state) {

    case 0:
        motion->velocity_z = 0;
        motion->velocity_y = 0;
        motion->velocity_x = 0;
        action->action_timer = 0;
        action->action_phase++;
        if (!(anim->flags & 0x8000)) {
            return;
        }

    case 1:
        timer = action->action_timer + 1;
        action->action_timer = timer;
        if ((timer != 4) && !(anim->flags & 0x8000)) {
            return;
        }
        action->action_timer = 0;
        action->action_phase++;
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
            action->action_phase = 5;
            play_sound_if_enabled(0x60C);
            return;
        default:
            return;
        }

    case 2:
        timer = action->action_timer + 1;
        action->action_timer = timer;
        if ((timer == 5) || (anim->flags & 0x8000)) {
            resolve_attack_damage_and_effects(actor, anim, actor->facing, 1);
            action->action_timer = 0;
            action->action_phase++;
        }
        if ((s16)action->action_timer == 3) {
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
        timer = action->action_timer + 1;
        action->action_timer = timer;
        if ((timer == 10) || (anim->flags & 0x8000)) {
            anim->flags |= 0x0800;
            play_sound_if_enabled(0x804);
            create_targeted_motion_effect(action, motion, anim, actor);
            create_actor_action_effect(action, motion, anim, actor);
        }
        if (((s16)action->action_timer == 12) ||
            (anim->flags & 0x8000)) {
            resolve_attack_damage_and_effects(actor, anim, actor->facing,
                action->unk_AA);
        }
        if (((s16)action->action_timer == 20) ||
            (anim->flags & 0x8000)) {
            anim->flags &= 0xF7FF;
            action->action_timer = 0;
            action->action_phase = 3;
        }
    case 4:
    default:
        return;
    }
}
