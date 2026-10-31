#include "common.h"
#include "dungeon/monster/garuda.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "dungeon/actor/status.h"
#include "dungeon/actor.h"
#include "dungeon/effect/screen.h"

extern void *actor_update_node_cursor;

extern u8 D_801748B8[];

void select_sprite_entry(void *, u8, s32);
void set_record_integer_tile_center(void *, u8, u8);
void play_sound_if_enabled(s32);
void spend_actor_mp(void *, s32);

/* Advances the actor animation sequence and resets its action state on completion. */
void advance_actor_animation_sequence(ActorRecord *body, ObjectPosition *motion, SpriteFrameState *sprite,
    ActorRecord *actor) {
    u16 delay_ticks;

    switch (body->action_phase.u) {
    case 0:
        body->action_phase.u = 1;
    case 1:
        if (sprite->flags & 0x8000) {
            body->action_phase.u = 3;
            sprite->flags |= 0x6000;
            resolve_attack_damage_and_effects(actor, sprite, actor->facing, 1);
            break;
        }
        motion->velocity_z = 0;
        motion->velocity_y = 0;
        motion->velocity_x = 0;
        sprite->frameTable = D_801748B8;
        select_sprite_entry(sprite,
            D_801748B8[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
            0);
        body->action_phase.u++;
        body->action_timer.u = 0;
        break;
    case 2:
        delay_ticks = body->action_timer.u + 1;
        body->action_timer.u = delay_ticks;
        if ((s16)delay_ticks != 2) {
            break;
        }
        play_sound_if_enabled(0x808);
        resolve_attack_damage_and_effects(actor, sprite, actor->facing, 1);
        body->action_phase.u++;
        break;
    case 3:
        if (!(sprite->flags & 0xE000)) {
            break;
        }
        set_record_integer_tile_center(motion, sprite->tile_x, sprite->tile_y);
        spend_actor_mp(actor, 0x100);
        body->unk_8C.address = update_creature_animation_action;
        g_dungeon_status.active_actor = 0;
        advance_status_timers(actor);
        if (actor->pending_turn_updates == 0) {
            actor->action_flags &= 0x7FFF;
            break;
        }
        actor_update_node_cursor = (u8 *)actor - 0x20;
        break;
    }
}
