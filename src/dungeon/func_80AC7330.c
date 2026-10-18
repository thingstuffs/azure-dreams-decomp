#include "common.h"

extern s32 update_actor_movement_to_tile(void);
extern void reduce_actor_food_meter(s32, s32);
extern void advance_status_timers(s32);
extern s32 check_actor_floor_trap(s32, s32);
extern s32 D_80171728;

/* Updates the actor and resets the entity state when the checks succeed. */
void reset_eligible_entity_state(void *entity_arg, s32 unused, s32 check_arg, s32 actor_arg) {
    void *entity = entity_arg;
    s32 check_value = check_arg;
    s32 actor = actor_arg;

    if (update_actor_movement_to_tile() != 0) {
        reduce_actor_food_meter(actor, 4);
        advance_status_timers(actor);
        if ((check_actor_floor_trap(check_value, actor) << 16) > 0) {
            do {
                *(s32 **)((u8 *)entity + 0x8C) = &D_80171728;
            } while (0);
            *(s32 *)((u8 *)entity + 0x90) = 0;
        }
    }
}
