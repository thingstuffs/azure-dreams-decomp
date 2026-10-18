#include "common.h"

extern void update_item_use_effect_and_idle_return(void);

/* jump_table; owner: dungeon/func_80FE31A0. */
const u32 D_8016A838[7] __attribute__((aligned(4))) = {
    (u32)((u8 *)update_item_use_effect_and_idle_return + 0x124),
    (u32)((u8 *)update_item_use_effect_and_idle_return + 0x11C),
    (u32)((u8 *)update_item_use_effect_and_idle_return + 0x114),
    (u32)((u8 *)update_item_use_effect_and_idle_return + 0x12C),
    (u32)((u8 *)update_item_use_effect_and_idle_return + 0xD4),
    (u32)((u8 *)update_item_use_effect_and_idle_return + 0xCC),
    (u32)((u8 *)update_item_use_effect_and_idle_return + 0xC4)
};
