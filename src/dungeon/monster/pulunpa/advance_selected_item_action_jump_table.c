#include "common.h"

extern void advance_selected_item_action(void);

/* jump_table; owner: dungeon/func_80CBEF98. */
const void *const pulunpa_slot_g_item_targets[7] __attribute__((aligned(4))) = {
    ((u8 *)advance_selected_item_action + 0x11C),
    ((u8 *)advance_selected_item_action + 0x114),
    ((u8 *)advance_selected_item_action + 0x10C),
    ((u8 *)advance_selected_item_action + 0x124),
    ((u8 *)advance_selected_item_action + 0xCC),
    ((u8 *)advance_selected_item_action + 0xC4),
    ((u8 *)advance_selected_item_action + 0xBC)
};
