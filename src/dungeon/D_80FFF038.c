#include "common.h"

extern void advance_actor_item_use_alt(void);

/* jump_table; owner: dungeon/func_810011A0. */
const u32 D_8014C838[7] __attribute__((aligned(4))) = {
    (u32)((u8 *)advance_actor_item_use_alt + 0x124),
    (u32)((u8 *)advance_actor_item_use_alt + 0x11C),
    (u32)((u8 *)advance_actor_item_use_alt + 0x114),
    (u32)((u8 *)advance_actor_item_use_alt + 0x12C),
    (u32)((u8 *)advance_actor_item_use_alt + 0xD4),
    (u32)((u8 *)advance_actor_item_use_alt + 0xCC),
    (u32)((u8 *)advance_actor_item_use_alt + 0xC4)
};
