#include "common.h"

extern void advance_sequence_action(void);

/* jump_table; owner: dungeon/func_80ACD7D8. */
const u32 saber_slot_f_action_targets_b[5] __attribute__((aligned(4))) = {
    (u32)((u8 *)advance_sequence_action + 0x48),
    (u32)((u8 *)advance_sequence_action + 0x98),
    (u32)((u8 *)advance_sequence_action + 0x10C),
    (u32)((u8 *)advance_sequence_action + 0x180),
    (u32)((u8 *)advance_sequence_action + 0x1F8)
};
