#include "common.h"
#include "dungeon/actor/motion.h"
#include "dungeon/actor.h"
#include "dungeon/actor/status.h"


extern void spend_actor_mp(s32, s32);

#include "dungeon/monster/saber.h"

/* Updates the actor and resets the entity state when the checks succeed. */
void reset_eligible_entity_state(void *entity_arg, void *motion, void *check_arg, void *actor_arg) {
    void *entity = entity_arg;
    void *check_value = check_arg;
    void *actor = actor_arg;

    if (update_actor_movement_to_tile(entity, motion, check_value, actor) != 0) {
        spend_actor_mp(actor, 4);
        advance_status_timers(actor);
        if ((check_actor_floor_trap(check_value, actor) << 16) > 0) {
            /* BYTES: local/global alloc priority: the loop note adds loop-weighted refs (REG_N_REFS) to a value; unwrap swaps callee-saved registers (ledger/onetrip_loadbearing.jsonl: dungeon/func_80AC7330). */
            do {
                *(s32 **)((u8 *)entity + 0x8C) = &saber_behavior_entry;
            } while (0);
            *(s32 *)((u8 *)entity + 0x90) = 0;
        }
    }
}
