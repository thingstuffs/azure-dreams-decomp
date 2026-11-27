#include "shared/entity.h"
#include "dungeon/monster/kewne.h"
#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"
#include "dungeon/actor/status.h"
#include "dungeon/player/object.h"
#include "dungeon/actor/spell_resource_ids_g01008.h"
#include "engine/graphics.h"
#include "dungeon/system.h"
#include "dungeon/actor.h"
#include "dungeon/effect/screen.h"

extern u8 kewne_leap_attack_direction_frames[];
extern u8 kewne_turn_frames[];

/* Updates the actor's directional motion and animation across three action states. */
void advance_kewne_leap_attack(ActorRecord *action, ObjectPosition *motion, SpriteFrameState *sprite, ActorRecord *actor) {
    s32 delta_x;
    s32 delta_y;
    s32 direction;
    u16 timer;
    u16 flags;

    switch (action->action_phase) {
    case 0:
        flags = sprite->flags;
        if (flags & 0x8000) {
            sprite->flags = flags | 0x6000;
            action->action_phase = 2;
            resolve_attack_damage_and_effects(actor, sprite, actor->facing, 1);
            return;
        }
        if ((flags & 0x6000) == 0) {
            return;
        }
        if (action->unk_90.parts.high != 0) {
            return;
        }
        sprite->frameTable = kewne_leap_attack_direction_frames;
        select_sprite_entry(sprite, kewne_leap_attack_direction_frames[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7], 0);
        action->action_timer = 0;
        play_sound_if_enabled(0x808);
        action->action_phase++;
        return;

    case 1:
        timer = action->action_timer;
        action->action_timer = timer + 1;
        direction = (actor->facing >> 9) & 7;
        delta_x = -dir_step_x[direction] << 16;
        delta_y = -dir_step_y[direction] << 16;
        if (timer >= 3 && timer < 11) {
            motion->velocity_x -= delta_x;
            motion->velocity_y -= delta_y;
        } else if (action->action_timer < 18) {
            motion->velocity_x += delta_x;
            motion->velocity_y += delta_y;
        } else {
            motion->velocity_z = 0;
            motion->velocity_y = 0;
            motion->velocity_x = 0;
        }
        if ((sprite->unk_04 == 5 && (sprite->flags & 0x1000)) || (sprite->flags & 0x8000)) {
            resolve_attack_damage_and_effects(actor, sprite, actor->facing, 1);
        }
        if ((sprite->flags & 0xE000) == 0) {
            return;
        }
        sprite->frameTable = kewne_turn_frames;
        select_sprite_entry(sprite, kewne_turn_frames[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7], 0);
        motion->velocity_z = 0;
        motion->velocity_y = 0;
        motion->velocity_x = 0;
        set_record_integer_tile_center(motion, sprite->tile_x, sprite->tile_y);
        action->action_phase++;
        return;

    case 2:
        if ((sprite->flags & 0xE000) == 0) {
            return;
        }
        spend_actor_mp(actor, 0x100);
        action->unk_8C.address = update_actor_animation_and_behavior;
        g_dungeon_status.active_actor = 0;
        actor->action_flags &= 0x7FFF;
        advance_status_timers(actor);
    }
}
