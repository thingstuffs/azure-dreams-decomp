#include "common.h"
#include "dungeon/actor.h"

extern s32 update_actor_movement_to_tile(void);
extern void spend_actor_mp(s32, s32);
extern void advance_status_timers(s32);

#include "dungeon/monster/saber.h"

/* Updates the actor and resets the entity state when the checks succeed. */
void reset_eligible_entity_state(void *entity_arg, s32 unused, s32 check_arg, s32 actor_arg) {
    void *entity = entity_arg;
    s32 check_value = check_arg;
    s32 actor = actor_arg;

    if (update_actor_movement_to_tile() != 0) {
        spend_actor_mp(actor, 4);
        advance_status_timers(actor);
        if ((check_actor_floor_trap(check_value, actor) << 16) > 0) {
            do {
                *(s32 **)((u8 *)entity + 0x8C) = &saber_behavior_entry;
            } while (0);
            *(s32 *)((u8 *)entity + 0x90) = 0;
        }
    }
}
