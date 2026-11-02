#include "common.h"
#include "dungeon/actor.h"
#include "dungeon/actor/status.h"

typedef struct ObjA0 ObjA0;
typedef struct Motion Motion;
typedef struct TilePos TilePos;
#include "shared/entity.h"
#include "dungeon/actor/position.h"
#include "dungeon/monster/nyuel.h"

extern void spend_actor_mp(s32, s32);

extern s32 nyuel_action_resume_address;

/* Updates an eligible actor and conditionally resets the entity state. */
void update_eligible_actor_and_reset_entity(ActorRecord *body, ObjectPosition *position, s32 value_arg, s32 actor_arg) {
    ActorRecord *entity = body;
    s32 check_value = value_arg;
    s32 actor = actor_arg;

    if (update_actor_movement_to_tile(body, position, value_arg, actor_arg) != 0) {
        spend_actor_mp(actor, 3);
        advance_status_timers(actor);
        if ((check_actor_floor_trap(check_value, actor) << 16) > 0) {
            entity->unk_8C.word_ptr = &nyuel_action_resume_address;
            entity->unk_90.value = 0;
        }
    }
}
