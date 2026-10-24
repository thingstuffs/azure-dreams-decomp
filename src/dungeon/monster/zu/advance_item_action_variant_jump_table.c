#include "common.h"

extern void advance_item_action_variant_b(void);

/* jump_table; owner: dungeon/func_80FA1240. */
const void *const zu_slot_c_action_targets[7] __attribute__((aligned(4))) = {
    ((u8 *)advance_item_action_variant_b + 0x11C),
    ((u8 *)advance_item_action_variant_b + 0x114),
    ((u8 *)advance_item_action_variant_b + 0x10C),
    ((u8 *)advance_item_action_variant_b + 0x124),
    ((u8 *)advance_item_action_variant_b + 0xCC),
    ((u8 *)advance_item_action_variant_b + 0xC4),
    ((u8 *)advance_item_action_variant_b + 0xBC)
};
