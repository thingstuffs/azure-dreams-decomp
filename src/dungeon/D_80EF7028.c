#include "common.h"

extern void advanceMotionThroughLandingAndFall(void);

/* jump_table; owner: dungeon/func_80EF7000. */
const u32 D_80158828[5] __attribute__((aligned(4))) = {
    (u32)((u8 *)advanceMotionThroughLandingAndFall + 0x12C),
    (u32)((u8 *)advanceMotionThroughLandingAndFall + 0x134),
    (u32)((u8 *)advanceMotionThroughLandingAndFall + 0x13C),
    (u32)((u8 *)advanceMotionThroughLandingAndFall + 0x144),
    (u32)((u8 *)advanceMotionThroughLandingAndFall + 0x14C)
};
