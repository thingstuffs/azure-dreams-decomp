#include "dungeon/player/object.h"
#include "dungeon/item/get_actor_height_difference_api.h"
#include "shared/sprite_frame_state.h"
#include "common.h"
#include "shared/actor_action_flags.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "m2c_compat.h"
#include "shared/entity.h"
#include "records/Rec_D_80082E80.h"
#include "dungeon/monster/nyuel.h"
#include "engine/graphics.h"
#include "dungeon/item.h"
#include "dungeon/effect.h"


typedef struct Ent Ent;
Ent *prepare_directional_attack(); /* extern */
extern u8 nyuel_frame_set_8;

/* Check movement conditions and initialize the actor action and directional animation. */
/* Starts Nyuel's attack against a compatible neighbor within 63 height units; returns 1, 0 if unsuitable,
 * or -1 if busy. */
s32 check_movement_and_initialize_action(ActorRecord *action_state, ObjectPosition *action_ctx, SpriteFrameState *sprite, ActorRecord *actor) {
    s32 unused[2]; /* never accessed: retail's frame reserves 8 bytes for this unused local */
    u8 *direction_table;
    ActorRecord *nearby_actor;
    u16 relative_height;
    u16 flags;

    actor->movement_queue_state = actor->movement_queue_state & 0x7F;
    if (g_dungeon_status.flags & 0x2000) {
        return -1;
    }
    nearby_actor = probe_directional_neighbor(actor, sprite->tile_x, sprite->tile_y,
        actor->facing);
    if ((check_entity_interaction_compatibility(actor, nearby_actor) << 0x10) == 0) {
        return 0;
    }
    flags = g_dungeon_status.flags;
    if (flags & 0x2000) {
        return -1;
    }
    if (!(actor->action_flags & ACTOR_ACTION_PENDING)) {
        if (flags & 8) {
            return -1;
        }
    }
    relative_height = -get_actor_height_difference(nearby_actor, actor);
    if ((u16)(relative_height + 0x3F) >= 0x7FU) {
        return 0;
    }
    if ((try_claim_dungeon_action_slot(actor) << 0x10) != 0) {
        return -1;
    }
    apply_camera_offset_and_select_target(NODE_HEADER(actor), action_ctx, 8, 0x300);
    if ((try_claim_dungeon_action_slot(actor) << 0x10) == 0) {
        action_state->action_id = 0x11;
        action_state->action_phase = 0;
        action_state->unk_8C.word = 0;
        actor->accuracy = 0x7C;
        actor->attack_bonus = 0;
        direction_table = &nyuel_frame_set_8;
        (sprite->frameTable) = direction_table;
        select_sprite_entry(sprite, direction_table[((s32) (g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7], 0);
        actor->pending_turn_updates = actor->pending_turn_updates - 1;
        prepare_directional_attack(actor, sprite, actor->facing, 1, 0);
        return 1;
    }
    return -1;
}
