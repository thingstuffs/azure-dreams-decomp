#include "common.h"

extern void update_item_use_effect_and_idle_return(void);

/* jump_table; owner: dungeon/func_80FE31A0. */
const void *const killer_slot_f_action_targets[7] __attribute__((aligned(4))) = {
    ((u8 *)update_item_use_effect_and_idle_return + 0x124),
    ((u8 *)update_item_use_effect_and_idle_return + 0x11C),
    ((u8 *)update_item_use_effect_and_idle_return + 0x114),
    ((u8 *)update_item_use_effect_and_idle_return + 0x12C),
    ((u8 *)update_item_use_effect_and_idle_return + 0xD4),
    ((u8 *)update_item_use_effect_and_idle_return + 0xCC),
    ((u8 *)update_item_use_effect_and_idle_return + 0xC4)
};
