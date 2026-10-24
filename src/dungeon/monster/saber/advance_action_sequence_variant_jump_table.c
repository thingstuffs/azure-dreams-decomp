#include "common.h"

extern void advance_action_sequence_variant_d(void);

/* jump_table; owner: dungeon/func_80AEB7D8. */
const void *const saber_slot_a_action_targets[5] __attribute__((aligned(4))) = {
    ((u8 *)advance_action_sequence_variant_d + 0x48),
    ((u8 *)advance_action_sequence_variant_d + 0x98),
    ((u8 *)advance_action_sequence_variant_d + 0x10C),
    ((u8 *)advance_action_sequence_variant_d + 0x180),
    ((u8 *)advance_action_sequence_variant_d + 0x1F8)
};
