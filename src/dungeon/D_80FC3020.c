#include "common.h"

extern void update_actor_action_sequence_and_recovery(void);

/* jump_table; owner: dungeon/func_80FC376C. */
const u32 D_8015E820[12] __attribute__((aligned(4))) = {
    (u32)((u8 *)update_actor_action_sequence_and_recovery + 0x828),
    (u32)((u8 *)update_actor_action_sequence_and_recovery + 0x828),
    (u32)((u8 *)update_actor_action_sequence_and_recovery + 0x828),
    (u32)((u8 *)update_actor_action_sequence_and_recovery + 0x854),
    (u32)((u8 *)update_actor_action_sequence_and_recovery + 0x7D4),
    (u32)((u8 *)update_actor_action_sequence_and_recovery + 0x7D4),
    (u32)((u8 *)update_actor_action_sequence_and_recovery + 0x7D4),
    (u32)((u8 *)update_actor_action_sequence_and_recovery + 0x76C),
    (u32)((u8 *)update_actor_action_sequence_and_recovery + 0x76C),
    (u32)((u8 *)update_actor_action_sequence_and_recovery + 0x854),
    (u32)((u8 *)update_actor_action_sequence_and_recovery + 0x854),
    (u32)((u8 *)update_actor_action_sequence_and_recovery + 0x818)
};
