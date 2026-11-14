#include "common.h"
#include "dungeon/monster/metal.h"
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

extern u8 metal_action_resume_address[];
extern u8 D_801742F0[];



/* Advance the timed actor animation sequence and restore actor state on completion. */
void advance_metal_attack_animation(ActorRecord *action, ObjectPosition *motion, SpriteFrameState *sprite, ActorRecord *actor) {
    u8 state;

    state = action->action_phase;
    switch (state) {
    case 0:
        if (sprite->flags & 0x8000) {
            action->action_phase = 4;
            sprite->flags |= 0x6000;
            resolve_attack_damage_and_effects(actor, sprite, actor->facing, 1);
            return;
        }
        motion->velocity_z = 0;
        motion->velocity_y = 0;
        motion->velocity_x = 0;
        action->action_timer = 0;
        action->action_phase++;
        return;

    case 1:
        if (++action->action_timer == 4 ||
            (sprite->flags & 0x8000)) {
            sprite->frameTable = D_801742F0;
            select_sprite_entry(sprite,
                D_801742F0[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
                0);
            sprite->flags |= 0x0800;
        }
        if (action->action_timer == 7 ||
            (sprite->flags & 0x8000)) {
            sprite->flags &= 0xF7FF;
            action->action_timer = 0;
            action->action_phase++;
            return;
        }
        return;

    case 2:
        if (++action->action_timer == 2) {
            sprite->flags |= 0x0800;
        }
        if (action->action_timer == 8 ||
            (sprite->flags & 0x8000)) {
            sprite->flags &= 0xF7FF;
            play_sound_if_enabled(0x808);
            action->action_timer = 0;
            action->action_phase++;
            return;
        }
        return;

    case 3:
        if (++action->action_timer == 2) {
            resolve_attack_damage_and_effects(actor, sprite, actor->facing, 1);
            action->action_phase++;
        }

    case 4:
        if (sprite->flags & 0xE000) {
            spend_actor_mp(actor, 0x100);
            action->unk_8C.address = metal_action_resume_address;
            g_dungeon_status.active_actor = 0;
            advance_status_timers(actor);
            actor->action_flags &= ACTOR_ACTION_CLEAR_PENDING_MASK;
        }
    }
}
