#include "common.h"
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

#include "dungeon/monster/saber.h"
#include "dungeon/actor.h"
#include "dungeon/effect/screen.h"

extern u8 D_80174E1C[];



/* Advances an actor's timed animation sequence and performs its final cleanup. */
void advance_timed_animation_and_cleanup(ActorRecord *sequence, ObjectPosition *motion, SpriteFrameState *sprite, ActorRecord *actor) {
    u8 state;

    state = sequence->action_phase;
    switch (state) {
    case 0:
        if (sprite->flags & 0x8000) {
            sequence->action_phase = 4;
            sprite->flags |= 0x6000;
            resolve_attack_damage_and_effects(actor, sprite, actor->facing, 1);
            return;
        }
        motion->velocity_z = 0;
        motion->velocity_y = 0;
        motion->velocity_x = 0;
        sequence->action_timer = 0;
        sequence->action_phase++;
        return;

    case 1:
        if (++sequence->action_timer == 4 ||
            (sprite->flags & 0x8000)) {
            sprite->frameTable = D_80174E1C;
            select_sprite_entry(sprite,
                D_80174E1C[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
                0);
            sequence->action_timer = 0;
            sequence->action_phase++;
            return;
        }
        return;

    case 2:
        if (++sequence->action_timer == 9 ||
            (sprite->flags & 0x8000)) {
            resolve_attack_damage_and_effects(actor, sprite, actor->facing, 1);
            sequence->action_timer = 0;
            sequence->action_phase++;
        }
        if (sequence->action_timer == 6) {
            play_sound_if_enabled(0x808);
            return;
        }
        return;

    case 3:
        if (++sequence->action_timer == 6) {
            sprite->flags |= 0x0800;
        }
        if (sequence->action_timer == 15 ||
            (sprite->flags & 0x8000)) {
            sprite->flags &= 0xF7FF;
            sequence->action_timer = 0;
            sequence->action_phase++;
            return;
        }
        return;

    case 4:
        if (sprite->flags & 0xE000) {
            spend_actor_mp(actor, 0x100);
            sequence->unk_8C.address = &saber_behavior_entry;
            g_dungeon_status.active_actor = 0;
            advance_status_timers(actor);
            actor->action_flags &= ACTOR_ACTION_CLEAR_PENDING_MASK;
        }
    default:
        return;
    }
}
