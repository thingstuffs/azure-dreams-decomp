#include "common.h"

extern void update_actor_special_action(void);

/* jump_table; owner: dungeon/func_80FC976C. */
const void *const mandara_slot_c_behavior_targets[5] __attribute__((aligned(4))) = {
    ((u8 *)update_actor_special_action + 0x1C0),
    ((u8 *)update_actor_special_action + 0x22C),
    ((u8 *)update_actor_special_action + 0x300),
    ((u8 *)update_actor_special_action + 0x490),
    ((u8 *)update_actor_special_action + 0x4D8)
};
