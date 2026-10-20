#include "common.h"

extern void advance_item_action_variant_b(void);

/* jump_table; owner: dungeon/func_80FA1240. */
const u32 D_80158838[7] __attribute__((aligned(4))) = {
    (u32)((u8 *)advance_item_action_variant_b + 0x11C),
    (u32)((u8 *)advance_item_action_variant_b + 0x114),
    (u32)((u8 *)advance_item_action_variant_b + 0x10C),
    (u32)((u8 *)advance_item_action_variant_b + 0x124),
    (u32)((u8 *)advance_item_action_variant_b + 0xCC),
    (u32)((u8 *)advance_item_action_variant_b + 0xC4),
    (u32)((u8 *)advance_item_action_variant_b + 0xBC)
};
