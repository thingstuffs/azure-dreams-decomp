#include "common.h"
#include "dungeon/actor/motion.h"
#include "dungeon/actor.h"
#include "shared/dungeon_status.h"



void advance_status_timers();

void spend_actor_mp();

extern s32 beldo_action_dispatch_address;

typedef struct S_80172474_0 {
    u8 pad_00[0x8C];
    s32 * unk_8C;
    u8 pad_90[0x2];
    s16 unk_92;
} S_80172474_0;   /* entity in run_actor_callbacks_and_adjust_global_flag */

/* Runs actor callbacks, updates entity state on success, and applies the global flag adjustment. */
void run_actor_callbacks_and_adjust_global_flag(void *entity_ptr, void *motion, void *check_arg, void *actor_arg)
{
    S_80172474_0 *entity = entity_ptr;
    void *check_value = check_arg;
    void *actor = actor_arg;

    if (update_actor_movement_to_tile(entity_ptr, motion, check_value, actor) != 0) {
        spend_actor_mp(actor, 0);
        advance_status_timers(actor);
        if ((check_actor_floor_trap(check_value, actor) << 0x10) <= 0) {
            return;
        }
        /* BYTES: local/global alloc priority: the loop note adds loop-weighted refs (REG_N_REFS) to a value; unwrap swaps callee-saved registers (ledger/onetrip_loadbearing.jsonl: dungeon/func_81252C74). */
        do {
            entity->unk_8C = &beldo_action_dispatch_address;
        } while (0);
    }
    if (g_dungeon_status.flags & 0x80) {
        entity->unk_92 = -0x20;
    }
}
