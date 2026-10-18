#include "common.h"

extern void update_actor_action_state_machine(void);

/* jump_table; owner: dungeon/func_80F05D14. */
const u32 D_8014C870[5] __attribute__((aligned(4))) = {
    (u32)((u8 *)update_actor_action_state_machine + 0x48),
    (u32)((u8 *)update_actor_action_state_machine + 0xD4),
    (u32)((u8 *)update_actor_action_state_machine + 0x118),
    (u32)((u8 *)update_actor_action_state_machine + 0x178),
    (u32)((u8 *)update_actor_action_state_machine + 0x23C)
};
