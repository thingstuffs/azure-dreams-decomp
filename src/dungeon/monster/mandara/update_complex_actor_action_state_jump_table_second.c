#include "common.h"

extern void update_complex_actor_action_state(void);

/* jump_table; owner: dungeon/func_80FB776C. */
const u32 D_8016A820[12] __attribute__((aligned(4))) = {
    (u32)((u8 *)update_complex_actor_action_state + 0x828),
    (u32)((u8 *)update_complex_actor_action_state + 0x828),
    (u32)((u8 *)update_complex_actor_action_state + 0x828),
    (u32)((u8 *)update_complex_actor_action_state + 0x854),
    (u32)((u8 *)update_complex_actor_action_state + 0x7D4),
    (u32)((u8 *)update_complex_actor_action_state + 0x7D4),
    (u32)((u8 *)update_complex_actor_action_state + 0x7D4),
    (u32)((u8 *)update_complex_actor_action_state + 0x76C),
    (u32)((u8 *)update_complex_actor_action_state + 0x76C),
    (u32)((u8 *)update_complex_actor_action_state + 0x854),
    (u32)((u8 *)update_complex_actor_action_state + 0x854),
    (u32)((u8 *)update_complex_actor_action_state + 0x818)
};
