#include "common.h"

extern void advance_sequence_action(void);

/* jump_table; owner: dungeon/func_80ACD7D8. */
const void *const saber_slot_f_action_targets[5] __attribute__((aligned(4))) = {
    ((u8 *)advance_sequence_action + 0x48),
    ((u8 *)advance_sequence_action + 0x98),
    ((u8 *)advance_sequence_action + 0x10C),
    ((u8 *)advance_sequence_action + 0x180),
    ((u8 *)advance_sequence_action + 0x1F8)
};
