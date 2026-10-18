#include "common.h"

extern void advance_action_sequence_variant_d(void);

/* jump_table; owner: dungeon/func_80AEB7D8. */
const u32 D_8014C838[5] __attribute__((aligned(4))) = {
    (u32)((u8 *)advance_action_sequence_variant_d + 0x48),
    (u32)((u8 *)advance_action_sequence_variant_d + 0x98),
    (u32)((u8 *)advance_action_sequence_variant_d + 0x10C),
    (u32)((u8 *)advance_action_sequence_variant_d + 0x180),
    (u32)((u8 *)advance_action_sequence_variant_d + 0x1F8)
};
