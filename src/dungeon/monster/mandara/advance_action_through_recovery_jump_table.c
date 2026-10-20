#include "common.h"

extern void advance_action_through_recovery(void);

/* Exact jump_table span; dispatch consumer dungeon/func_80FB35EC. */
const u32 D_80170850[7] __attribute__((aligned(4))) = {
    (u32)((u8 *)advance_action_through_recovery + 0x11C),
    (u32)((u8 *)advance_action_through_recovery + 0x114),
    (u32)((u8 *)advance_action_through_recovery + 0x10C),
    (u32)((u8 *)advance_action_through_recovery + 0x124),
    (u32)((u8 *)advance_action_through_recovery + 0xCC),
    (u32)((u8 *)advance_action_through_recovery + 0xC4),
    (u32)((u8 *)advance_action_through_recovery + 0xBC)
};
