#include "common.h"
#include "dungeon/actor/motion.h"
#include "dungeon/actor.h"
#include "dungeon/actor/status.h"




#include "dungeon/monster/saber.h"
#include "dungeon/actor/spell_resource_ids_g01008.h"

/* Updates the actor and resets the entity state when the checks succeed. */
void reset_eligible_entity_state(ActorRecord *entity_arg, ObjectPosition *motion, SpriteFrameState *check_arg, ActorRecord *actor_arg) {
    ActorRecord *entity = entity_arg;
    void *check_value = check_arg;
    void *actor = actor_arg;

    if (update_actor_movement_to_tile(entity, motion, check_value, actor) != 0) {
        spend_actor_mp(actor, 4);
        advance_status_timers(actor);
        if ((check_actor_floor_trap(check_value, actor) << 16) > 0) {
            /* BYTES: local/global alloc priority: the loop note adds loop-weighted refs (REG_N_REFS) to a value; unwrap swaps callee-saved registers (ledger/onetrip_loadbearing.jsonl: dungeon/func_80AC7330). */
            do {
                entity->unk_8C.word_ptr = &saber_behavior_entry;
            } while (0);
            entity->unk_90.value = 0;
        }
    }
}
