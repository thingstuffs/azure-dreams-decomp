#include "dungeon/player/object.h"
#include "dungeon/item/get_actor_height_difference_api.h"
#include "dungeon/item/actor_target.h"
#include "common.h"
#include "shared/actor_action_flags.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
#include "records/Rec_func_800A9E70_arg0.h"
#include "dungeon/monster/u_boat.h"
#include "dungeon/effect.h"

struct Ent *prepare_directional_attack(void *, void *, s16, s32, void *);
extern u8 resident_globals_page[];


/*
 * Checks a compatible neighbor within 64 height units, then starts U-Boat's normal attack or
 * exclusive action mode.
 */
s32 try_turn_actor_toward_target(ActorRecord *action_state, ObjectPosition *action_context, SpriteFrameState *target, ActorRecord *actor) {
    ActorRecord *nearby_actor;
    u16 relative_height;
    u16 result;
    u16 *global_flags;

    result = actor->movement_queue_state & 0x7F;
    actor->movement_queue_state = result;
    {

        global_flags = (u16 *)(resident_globals_page + 0x3460);
    }
    result = 0;
    if (global_flags[1] & 0x2000) {
        return -1;
    }

    nearby_actor = probe_directional_neighbor(actor, target->tile_x,
        target->tile_y, actor->facing);
    if ((check_entity_interaction_compatibility(actor, nearby_actor) << 0x10) == 0) {
        return result;
    }

    if (global_flags[1] & 0x2000) {
        return -1;
    }
    if (!(actor->action_flags & ACTOR_ACTION_PENDING) && (global_flags[1] & 8)) {
        return -1;
    }
    relative_height = -get_actor_height_difference(nearby_actor, actor);
    if ((u16)(relative_height + 0x40) < 0x81U) {
        result = 1;
        if ((try_claim_dungeon_action_slot(actor) << 0x10) != 0) {
            return -1;
        }
        apply_camera_offset_and_select_target(NODE_HEADER(actor), action_context, 8, 0x300);
        if ((try_claim_dungeon_action_slot(actor) << 0x10) != 0) {
            return -1;
        }

        action_state->action_phase = 0;
        if (action_state->unk_B4.bytes[1] == 0) {
            action_state->action_id = 0x11;
            action_state->unk_8C.word = 0;
            actor->accuracy = 0x7C;
            actor->attack_bonus = 0;
            action_state->action_state_flags =
                (u16)(action_state->action_state_flags | 8);
            prepare_directional_attack(actor, target, actor->facing, 1, 0);
            actor->pending_turn_updates--;
        } else {
            begin_actor_exclusive_action(action_state, action_context, target, 1, 1);
        }
    }
    return result;
}
