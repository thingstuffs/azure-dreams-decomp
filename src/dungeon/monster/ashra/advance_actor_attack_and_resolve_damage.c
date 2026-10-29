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

typedef struct S_80172620_0 {
    u8 pad_00[0x8C];
    s32 * unk_8C;
    u8 pad_90[0x6];
    u16 unk_96;
    u8 pad_98[0x3];
    u8 unk_9B;
} S_80172620_0;   /* arg0 in advance_actor_attack_and_resolve_damage */


void *resolve_attack_damage_and_effects(void *attacker_in, void *tile_in, s16 direction, s16 distance);
extern void set_record_integer_tile_center(ObjectPosition *, s32, s32);



extern void *actor_update_node_cursor;
extern s32 ashra_action_continuation_address;
extern u8 ashra_frame_set_3[];

/* Advance the actor's animation state and clean up when it finishes. */
void advance_actor_attack_and_resolve_damage(ActorRecord *action, ObjectPosition *actor_id, SpriteFrameState *sprite, ActorRecord *actor) {
    s32 state;

    state = action->action_phase.u;
    action->action_timer.u--;
    switch (state) {
    case 0:
        if (sprite->flags & 0x8000) {
            action->action_phase.u = 0xFF;
            sprite->flags |= 0x6000;
            resolve_attack_damage_and_effects(actor, sprite, actor->facing, 1);
            return;
        }
        sprite->frameTable = ashra_frame_set_3;
        select_sprite_entry(sprite,
            ashra_frame_set_3[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
            0);
        action->action_phase.u++;
        return;

    case 1:
        if (((sprite->unk_04 == 6) &&
             (sprite->flags & 0x1000)) ||
            (sprite->flags & 0x8000)) {
            play_sound_if_enabled(0x808);
            resolve_attack_damage_and_effects(actor, sprite, actor->facing, 1);
            action->action_phase.u = 0xFF;
        }
        return;

    case 0xFF:
        if (sprite->flags & 0xE000) {
            set_record_integer_tile_center(actor_id, sprite->tile_x, sprite->tile_y);
            spend_actor_mp(actor, 0x100);
            action->unk_8C.address = &ashra_action_continuation_address;
            g_dungeon_status.active_actor = 0;
            advance_status_timers(actor);
            if (actor->pending_turn_updates == 0) {
                actor->action_flags &= ACTOR_ACTION_CLEAR_PENDING_MASK;
                return;
            }
            actor_update_node_cursor = (u8 *)actor - 0x20;
        }
        return;
    }
}
