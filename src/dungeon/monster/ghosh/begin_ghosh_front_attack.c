#include "common.h"
#include "dungeon/monster/ghosh.h"
#include "dungeon/item/actor_target.h"
#include "dungeon/player/object.h"
#include "shared/actor_action_flags.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
#include "dungeon/item.h"

/* Starts Ghosh's front attack against a compatible neighbour within 64 height
 * units; returns 1 when started, 0 if no target suits, -1 while busy. */
s32 begin_ghosh_front_attack(ActorRecord *body, ObjectPosition *position, SpriteFrameState *sprite, ActorRecord *actor)
{
    s32 unused[2]; /* never accessed: retail's frame reserves 8 bytes for this unused local, as in its Beldo twin */
    ActorRecord *target;
    void *node_body;

    actor->movement_queue_state &= 0x7F;

    if (g_dungeon_status.flags & 0x2000) {
        return -1;
    }

    target = probe_directional_neighbor(actor, sprite->tile_x, sprite->tile_y, actor->facing);

    if ((check_entity_interaction_compatibility(actor, target) << 16) == 0) {
        return 0;
    }

    if (g_dungeon_status.flags & 0x2000) {
        return -1;
    }

    if (!(actor->action_flags & ACTOR_ACTION_PENDING) && (g_dungeon_status.flags & 8)) {
        return -1;
    }

    if ((u32)(((0 - get_actor_height_difference(target, actor)) + 0x40) & 0xFFFF) >= 0x81U) {
        return 0;
    }

    if (try_claim_dungeon_action_slot(actor) != 0) {
        return -1;
    }

    node_body = actor; /* object dispatch passes the body that follows the 0x20-byte node header */
    apply_camera_offset_and_select_target(node_body - 0x20, position, 8, 0x300);

    if (try_claim_dungeon_action_slot(actor) == 0) {
        body->action_id.u = 0x11;
        body->action_phase.u = 0;
        body->unk_8C.handler = 0;
        actor->unk_84 = 0x7C;
        actor->unk_85 = 6;
        actor->pending_turn_updates--;

        prepare_directional_attack(actor, sprite, actor->facing, 1, 0);
        return 1;
    }

    return -1;
}
