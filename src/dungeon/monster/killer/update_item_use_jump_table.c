#include "common.h"

extern void update_item_use(void);

/* Exact jump_table span; dispatch consumer dungeon/func_80FDD1A0. */
const u32 killer_slot_g_item_targets[7] __attribute__((aligned(4))) = {
    (u32)((u8 *)update_item_use + 0x124),
    (u32)((u8 *)update_item_use + 0x11C),
    (u32)((u8 *)update_item_use + 0x114),
    (u32)((u8 *)update_item_use + 0x12C),
    (u32)((u8 *)update_item_use + 0xD4),
    (u32)((u8 *)update_item_use + 0xCC),
    (u32)((u8 *)update_item_use + 0xC4)
};
