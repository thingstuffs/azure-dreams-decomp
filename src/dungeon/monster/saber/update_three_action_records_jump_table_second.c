#include "common.h"

extern void update_three_action_records(void);

/* jump_table; owner: dungeon/func_80ACDA30. */
const u32 saber_slot_f_extra_action_targets[7] __attribute__((aligned(4))) = {
    (u32)((u8 *)update_three_action_records + 0x11C),
    (u32)((u8 *)update_three_action_records + 0x114),
    (u32)((u8 *)update_three_action_records + 0x10C),
    (u32)((u8 *)update_three_action_records + 0x124),
    (u32)((u8 *)update_three_action_records + 0xC8),
    (u32)((u8 *)update_three_action_records + 0xC0),
    (u32)((u8 *)update_three_action_records + 0xB8)
};
