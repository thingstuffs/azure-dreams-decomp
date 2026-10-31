#include "common.h"
#include "dungeon/monster/troll.h"
#include "shared/actor_action_flags.h"
#include "shared/sprite_frame_state.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_D_80082E80.h"
#include "shared/entity.h"
#include "records/Rec_func_8017121C_arg1.h"
#include "dungeon/actor/status.h"
#include "dungeon/actor/spell_resource_ids_g01008.h"
#include "engine/graphics.h"
#include "dungeon/system.h"
#include "dungeon/actor.h"
#include "dungeon/effect/screen.h"

extern void create_targeted_motion_effect(ActorRecord *, ObjectPosition *, void *, void *);
void create_actor_action_effect(ActorRecord *source_object, ObjectPosition *source_pos, SpriteFrameState *sprite_template, ActorRecord *actor);

extern u8 troll_action_dispatch_address[];
extern u8 D_80175DDC[8];
extern u8 D_80175DE4[8];
extern u8 D_80175DEC[8];

/* Advance a timed action sequence with directional animation and sound effects. */
void advance_timed_directional_action(ActorRecord *action, ObjectPosition *motion, SpriteFrameState *sprite, ActorRecord *entity) {
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
        if (!(sprite->flags & 0x8000)) {
            return;
        }

    case 1:
        timer = action->action_timer.u + 1;
        action->action_timer.u = timer;
        if ((timer != 4) && !(sprite->flags & 0x8000)) {
            return;
        }
        action->action_timer.u = 0;
        action->action_phase.u++;
        switch (entity->unk_48) {
        case 13:
            sprite->frameTable = D_80175DDC;
            select_sprite_entry(sprite,
                D_80175DDC[((g_game_work.view.camera_rotation.parts.viewAngle + entity->facing + 0x100) >> 9) & 7],
                0);
            return;
        case 14:
            sprite->frameTable = D_80175DE4;
            select_sprite_entry(sprite,
                D_80175DE4[((g_game_work.view.camera_rotation.parts.viewAngle + entity->facing + 0x100) >> 9) & 7],
                0);
            return;
        case 15:
            sprite->frameTable = D_80175DEC;
            select_sprite_entry(sprite,
                D_80175DEC[((g_game_work.view.camera_rotation.parts.viewAngle + entity->facing + 0x100) >> 9) & 7],
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
        if ((timer == 5) || (sprite->flags & 0x8000)) {
            resolve_attack_damage_and_effects(entity, sprite, entity->facing, 1);
            action->action_timer.u = 0;
            action->action_phase.u++;
        }
        if (action->action_timer.s == 3) {
            play_sound_if_enabled(0x804);
            return;
        }
        return;

    case 3:
        if (sprite->flags & 0xE000) {
            spend_actor_mp(entity, 0x100);
            action->unk_8C.address = troll_action_dispatch_address;
            g_dungeon_status.active_actor = 0;
            advance_status_timers(entity);
            entity->action_flags &= ACTOR_ACTION_CLEAR_PENDING_MASK;
        }
        return;

    case 5:
        timer = action->action_timer.u + 1;
        action->action_timer.u = timer;
        if ((timer == 10) || (sprite->flags & 0x8000)) {
            sprite->flags |= 0x0800;
            play_sound_if_enabled(0x804);
            create_targeted_motion_effect(action, motion, sprite, entity);
            create_actor_action_effect(action, motion, sprite, entity);
        }
        if ((action->action_timer.s == 12) ||
            (sprite->flags & 0x8000)) {
            resolve_attack_damage_and_effects(entity, sprite, entity->facing,
                action->unk_AA);
        }
        if ((action->action_timer.s == 20) ||
            (sprite->flags & 0x8000)) {
            sprite->flags &= 0xF7FF;
            action->action_timer.u = 0;
            action->action_phase.u = 3;
        }
    case 4:
    default:
        return;
    }
}
