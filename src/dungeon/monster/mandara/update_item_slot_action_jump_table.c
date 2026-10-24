#include "common.h"

extern void update_item_slot_action(void);

/* jump_table; owner: dungeon/func_80FCB5EC. */
const void *const D_80158850[7] __attribute__((aligned(4))) = {
    ((u8 *)update_item_slot_action + 0x11C),
    ((u8 *)update_item_slot_action + 0x114),
    ((u8 *)update_item_slot_action + 0x10C),
    ((u8 *)update_item_slot_action + 0x124),
    ((u8 *)update_item_slot_action + 0xCC),
    ((u8 *)update_item_slot_action + 0xC4),
    ((u8 *)update_item_slot_action + 0xBC)
};
