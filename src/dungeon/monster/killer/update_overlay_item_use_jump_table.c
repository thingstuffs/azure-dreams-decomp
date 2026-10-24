#include "common.h"

extern void update_overlay_item_use(void);

/* jump_table; owner: dungeon/func_80FE91A0. */
const void *const D_80164838[7] __attribute__((aligned(4))) = {
    ((u8 *)update_overlay_item_use + 0x124),
    ((u8 *)update_overlay_item_use + 0x11C),
    ((u8 *)update_overlay_item_use + 0x114),
    ((u8 *)update_overlay_item_use + 0x12C),
    ((u8 *)update_overlay_item_use + 0xD4),
    ((u8 *)update_overlay_item_use + 0xCC),
    ((u8 *)update_overlay_item_use + 0xC4)
};
