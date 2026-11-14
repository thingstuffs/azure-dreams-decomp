#include "dungeon/player/object.h"
#include "dungeon/monster/baloon_frames.h"
#include "shared/sprite_frame_state.h"
#include "common.h"
#include "shared/actor_action_flags.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"
#include "records/Rec_D_80082E80.h"
#include "records/Rec_func_800A9E70_arg0.h"
#include "engine/graphics.h"
#include "dungeon/item.h"
#include "dungeon/effect.h"
#include "dungeon/monster/baloon.h"
#include "dungeon/data.h"

typedef struct Ent Ent;

Ent *prepare_directional_attack();
#include "dungeon/item/get_actor_height_difference_api.h"
s32 check_entity_interaction_compatibility();

/* Checks action readiness and initializes the actor state and directional animation. */
s32 try_baloon_attack(ActorRecord *action_state, ObjectPosition *action_param, SpriteFrameState *sprite, ActorRecord *actor) {
    s32 result;
    s32 action_ready;
    ActorRecord *neighbor;
    s32 action_flags;
    u8 *anim_table;

    actor->movement_queue_state &= 0x7F;
    action_ready = 0;
    if (g_dungeon_status.flags & 0x2000) {
        return -1;
    }

    neighbor = probe_directional_neighbor(actor, sprite->tile_x,
                         sprite->tile_y,
                         actor->facing);
    result = 0;
    if ((check_entity_interaction_compatibility(actor, neighbor) << 16) == 0) {
        return 0;
    }

    result = -1;
    action_flags = g_dungeon_status.flags;
    if (action_flags & 0x2000) {
        return result;
    }
    if (!(actor->action_flags & ACTOR_ACTION_PENDING)) {
        if (action_flags & 8) {
            return result;
        }
    }

    if ((u16)((0 - get_actor_height_difference(neighbor, actor)) + 0x40) >= 0x81U) {
        return action_ready;
    }

    action_ready = 1;
    if (!(actor->action_flags & ACTOR_ACTION_PENDING)) {
        if (g_dungeon_status.flags & 8) {
            return -1;
        }
    }
    if ((try_claim_dungeon_action_slot(actor) << 16) != 0) {
        return -1;
    }

    apply_camera_offset_and_select_target(NODE_HEADER(actor), action_param, 8, 0x300);
    if ((try_claim_dungeon_action_slot(actor) << 16) != 0) {
        return -1;
    }

    result = action_ready;
    action_state->action_phase = 0;
    if (result != 0) {
        action_state->action_id = 0x11;
        action_state->unk_8C.word = 0;
        actor->unk_84 = 0x7C;
        actor->unk_85 = 0;
        action_state->action_state_flags &= 0xFFF7;
        actor->flags1C &= 0xFFFBFFFF;
        anim_table = baloon_attack_frames;
        sprite->frameTable = anim_table;
        select_sprite_entry(sprite,
                      anim_table[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
                      0);
        actor->pending_turn_updates--;
        prepare_directional_attack(actor, sprite, actor->facing, 1, 0);
    }
    return result;
}
