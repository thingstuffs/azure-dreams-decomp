#include "common.h"

extern void update_three_action_records(void);

/* jump_table; owner: dungeon/func_80ACDA30. */
const void *const D_8016A850[5] __attribute__((aligned(4))) = {
    ((u8 *)update_three_action_records + 0x6C),
    ((u8 *)update_three_action_records + 0x29C),
    ((u8 *)update_three_action_records + 0x2E4),
    ((u8 *)update_three_action_records + 0x514),
    ((u8 *)update_three_action_records + 0x59C)
};
