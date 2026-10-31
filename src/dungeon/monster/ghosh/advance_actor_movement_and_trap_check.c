#include "common.h"
#include "dungeon/actor.h"
#include "dungeon/actor/status.h"
#include "dungeon/actor/position.h"
#include "dungeon/monster/ghosh.h"

extern s32 ghosh_action_resume_address;

/* Initializes the state fields when the availability and value checks pass. */
void advance_actor_movement_and_trap_check(ActorRecord *body, ObjectPosition *position, SpriteFrameState *sprite, ActorRecord *actor) {
    if (update_actor_movement_to_tile(body, position, sprite, actor) != 0) {
        advance_status_timers(actor);
        if ((check_actor_floor_trap(sprite, actor) << 16) > 0) {
            body->unk_8C.address = &ghosh_action_resume_address;
            body->unk_90.value = 0;
        }
    }
}
