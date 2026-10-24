#include "common.h"

extern void advance_actor_item_use_alt(void);

/* jump_table; owner: dungeon/func_810011A0. */
const void *const killer_slot_a_action_targets[7] __attribute__((aligned(4))) = {
    ((u8 *)advance_actor_item_use_alt + 0x124),
    ((u8 *)advance_actor_item_use_alt + 0x11C),
    ((u8 *)advance_actor_item_use_alt + 0x114),
    ((u8 *)advance_actor_item_use_alt + 0x12C),
    ((u8 *)advance_actor_item_use_alt + 0xD4),
    ((u8 *)advance_actor_item_use_alt + 0xCC),
    ((u8 *)advance_actor_item_use_alt + 0xC4)
};
