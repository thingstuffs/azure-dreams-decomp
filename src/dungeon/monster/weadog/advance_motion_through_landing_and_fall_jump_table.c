#include "common.h"

extern void advance_motion_through_landing_and_fall(void);

/* jump_table; owner: dungeon/func_80EF7000. */
const void *const D_80158828[5] __attribute__((aligned(4))) = {
    ((u8 *)advance_motion_through_landing_and_fall + 0x12C),
    ((u8 *)advance_motion_through_landing_and_fall + 0x134),
    ((u8 *)advance_motion_through_landing_and_fall + 0x13C),
    ((u8 *)advance_motion_through_landing_and_fall + 0x144),
    ((u8 *)advance_motion_through_landing_and_fall + 0x14C)
};
