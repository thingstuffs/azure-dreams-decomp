#include "common.h"

extern void advance_selected_item_action(void);

/* jump_table; owner: dungeon/func_80CBEF98. */
const u32 pulunpa_slot_g_item_targets[7] __attribute__((aligned(4))) = {
    (u32)((u8 *)advance_selected_item_action + 0x11C),
    (u32)((u8 *)advance_selected_item_action + 0x114),
    (u32)((u8 *)advance_selected_item_action + 0x10C),
    (u32)((u8 *)advance_selected_item_action + 0x124),
    (u32)((u8 *)advance_selected_item_action + 0xCC),
    (u32)((u8 *)advance_selected_item_action + 0xC4),
    (u32)((u8 *)advance_selected_item_action + 0xBC)
};
