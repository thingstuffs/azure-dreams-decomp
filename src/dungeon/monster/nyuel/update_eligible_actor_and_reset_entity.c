#include "common.h"

typedef struct ObjA0 ObjA0;
typedef struct Motion Motion;
typedef struct TilePos TilePos;
#include "shared/entity.h"

extern s32 update_actor_movement_to_tile(ObjA0 *move_state, Motion *motion, TilePos *target_tile, ActorRecord *actor);
extern void spend_actor_mp(s32, s32);
extern void advance_status_timers(s32);
extern s32 check_actor_floor_trap(s32, s32);
extern s32 D_80170E9C;

/* Updates an eligible actor and conditionally resets the entity state. */
void update_eligible_actor_and_reset_entity(void *entity_arg, s32 check_context, s32 value_arg, s32 actor_arg) {
    void *entity = entity_arg;
    s32 check_value = value_arg;
    s32 actor = actor_arg;

    if (update_actor_movement_to_tile(entity_arg, check_context, value_arg, actor_arg) != 0) {
        spend_actor_mp(actor, 3);
        advance_status_timers(actor);
        if ((check_actor_floor_trap(check_value, actor) << 16) > 0) {
            *(s32 **)((u8 *)entity + 0x8C) = &D_80170E9C;
            *(s32 *)((u8 *)entity + 0x90) = 0;
        }
    }
}
