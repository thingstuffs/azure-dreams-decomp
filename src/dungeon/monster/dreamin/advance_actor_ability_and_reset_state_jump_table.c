#include "common.h"

extern void advance_actor_ability_and_reset_state(void);

/* jump_table; owner: dungeon/func_80DA3070. */
const void *const dreamin_slot_d_action_targets[7] __attribute__((aligned(4))) = {
    ((u8 *)advance_actor_ability_and_reset_state + 0x11C),
    ((u8 *)advance_actor_ability_and_reset_state + 0x114),
    ((u8 *)advance_actor_ability_and_reset_state + 0x10C),
    ((u8 *)advance_actor_ability_and_reset_state + 0x124),
    ((u8 *)advance_actor_ability_and_reset_state + 0xCC),
    ((u8 *)advance_actor_ability_and_reset_state + 0xC4),
    ((u8 *)advance_actor_ability_and_reset_state + 0xBC)
};
