#include "dungeon/player/object.h"
#include "dungeon/item/get_actor_height_difference_api.h"
#include "dungeon/item/actor_target.h"
#include "shared/sprite_frame_state.h"
#include "common.h"
#include "shared/actor_action_flags.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"
#include "records/Rec_D_80082E80.h"
#include "dungeon/effect.h"
#include "dungeon/monster/death.h"






extern struct Ent *prepare_directional_attack(void *, void *, s16, s32, void *);

/*
 * Starts Death's attack against a compatible neighbor within 64 height units; returns 1, 0 if
 * unsuitable, or -1 if busy.
 */
s32 try_death_attack(ActorRecord *action_state, ObjectPosition *effect_arg, SpriteFrameState *target, ActorRecord *actor) {
    s32 unused[2]; /* never accessed: retail's frame reserves 8 bytes for this unused local */
    ActorRecord *neighbor;
    u16 relative_height;

    actor->movement_queue_state &= 0x7F;

    if (g_dungeon_status.flags & 0x2000) {
        return -1;
    }

    neighbor = probe_directional_neighbor(
        actor,
        target->tile_x,
        target->tile_y,
        actor->facing);

    if ((check_entity_interaction_compatibility(actor, neighbor) << 16) == 0) {
        return 0;
    }

    if (g_dungeon_status.flags & 0x2000) {
        return -1;
    }

    if (!(actor->action_flags & ACTOR_ACTION_PENDING) &&
        (g_dungeon_status.flags & 8)) {
        return -1;
    }

    relative_height = -get_actor_height_difference(neighbor, actor);
    if ((u16)(relative_height + 0x40) >= 0x81U) {
        return 0;
    }

    if ((try_claim_dungeon_action_slot(actor) << 16) != 0) {
        return -1;
    }

    apply_camera_offset_and_select_target(NODE_HEADER(actor), effect_arg, 8, 0x300);

    if ((try_claim_dungeon_action_slot(actor) << 16) == 0) {
        action_state->action_id = 0x11;
        action_state->action_phase = 0;
        action_state->unk_8C.run = 0;
        actor->unk_84 = 0x7C;
        actor->unk_85 = 4;
        actor->pending_turn_updates--;

        prepare_directional_attack(actor, target, actor->facing, 1, 0);
        return 1;
    }

    return -1;
}
