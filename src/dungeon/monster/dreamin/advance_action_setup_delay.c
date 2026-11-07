#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "dungeon/actor/status.h"
#include "dungeon/player/object.h"
#include "dungeon/actor/spell_resource_ids_g01008.h"
#include "engine/graphics.h"
#include "dungeon/system.h"
#include "dungeon/actor.h"
#include "dungeon/effect/screen.h"
#include "dungeon/monster/dreamin.h"

extern void *actor_update_node_cursor;
extern u8 dreamin_action_continuation_address;
extern u8 D_80173894[];

/* Advances an actor action through animation setup, a delay, and completion. */
void advance_action_setup_delay(ActorRecord *body, ObjectPosition *motion, SpriteFrameState *sprite, ActorRecord *actor)
{
    s32 phase;
    s32 loaded_phase;
    u16 delay_ticks;

    phase = body->action_phase;
    switch (phase) {
    case 0:
        if (sprite->flags & 0x8000) {
            body->action_phase = 2;
            sprite->flags |= 0x6000;
            resolve_attack_damage_and_effects(actor, sprite, actor->facing, 1);
            return;
        }

        motion->velocity_z = 0;
        motion->velocity_y = 0;
        motion->velocity_x = 0;
        sprite->frameTable = D_80173894;
        select_sprite_entry(sprite,
            D_80173894[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
            0);
        loaded_phase = body->action_phase;
        body->action_timer.u = 0;
        body->action_phase = loaded_phase + 1;
        return;

    case 1:
        delay_ticks = body->action_timer.u + 1;
        body->action_timer.u = delay_ticks;
        if ((s16)delay_ticks != 10) {
            return;
        }
        play_sound_if_enabled(0x808);
        resolve_attack_damage_and_effects(actor, sprite, actor->facing, 1);
        loaded_phase = body->action_phase;

        body->action_phase = loaded_phase + 1;
        return;

    case 2:
        if (!(sprite->flags & 0xE000)) {
            return;
        }
        set_record_integer_tile_center(motion, sprite->tile_x, sprite->tile_y);
        spend_actor_mp(actor, 0x100);
        body->unk_8C.address = &dreamin_action_continuation_address;
        g_dungeon_status.active_actor = 0;
        advance_status_timers(actor);
        if (actor->pending_turn_updates == 0) {
            actor->action_flags &= 0x7FFF;
        } else {
            actor_update_node_cursor = NODE_HEADER(actor);
        }

        return;
    }
}
