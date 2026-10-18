#include "common.h"

extern void update_movement_destination_and_recovery(void);

/* jump_table; owner: dungeon/func_80E94C28. */
const u32 D_8016A8F0[6] __attribute__((aligned(4))) = {
    (u32)((u8 *)update_movement_destination_and_recovery + 0x90),
    (u32)((u8 *)update_movement_destination_and_recovery + 0x130),
    (u32)((u8 *)update_movement_destination_and_recovery + 0x1C0),
    (u32)((u8 *)update_movement_destination_and_recovery + 0x24C),
    (u32)((u8 *)update_movement_destination_and_recovery + 0x2BC),
    (u32)((u8 *)update_movement_destination_and_recovery + 0x39C)
};
