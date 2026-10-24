#include "common.h"

extern void update_actor_item_action(void);

/* jump_table; owner: dungeon/func_80F05FB0. */
const void *const D_8014C888[5] __attribute__((aligned(4))) = {
    ((u8 *)update_actor_item_action + 0x60),
    ((u8 *)update_actor_item_action + 0x298),
    ((u8 *)update_actor_item_action + 0x2E0),
    ((u8 *)update_actor_item_action + 0x434),
    ((u8 *)update_actor_item_action + 0x448)
};
