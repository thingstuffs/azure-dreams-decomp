#include "common.h"
#include "dungeon/actor/motion.h"
#include "dungeon/actor.h"
#include "shared/dungeon_status.h"
#include "dungeon/actor/status.h"





#include "dungeon/monster/u_boat.h"
#include "dungeon/actor/spell_resource_ids_g01008.h"

/* Updates actor behavior and state fields according to mode and input. */
void update_actor_movement_state(ActorRecord *body, ObjectPosition *motion, SpriteFrameState *sprite, ActorRecord *actor_arg)
{
    void *action_data = sprite;
    void *actor = actor_arg;

    if (update_actor_movement_to_tile(body, motion, action_data, actor) != 0) {
        if (body->unk_B4.bytes[1] == 0) {
            spend_actor_mp(actor, 4);
            advance_status_timers(actor);
            if ((check_actor_floor_trap(action_data, actor) << 16) <= 0) {
                return;
            }
        } else {
            spend_actor_mp(actor, 0x10);
            advance_status_timers(actor);
        }
        body->unk_8C.address = uboat_behavior_entry;
    }

    if (g_dungeon_status.flags & 0x80) {
        body->unk_90.parts.high.s = -0x20;
        if (body->unk_B4.bytes[1] != 0) {
            body->unk_90.parts.high.s = 0;
        }
    }
}
