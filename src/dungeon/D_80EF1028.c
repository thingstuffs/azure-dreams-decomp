#include "common.h"

extern void dungeonUpdateFlightLandingAndFall(void);

/* jump_table; owner: dungeon/func_80EF1000. */
const u32 D_8015E828[5] __attribute__((aligned(4))) = {
    (u32)((u8 *)dungeonUpdateFlightLandingAndFall + 0x12C),
    (u32)((u8 *)dungeonUpdateFlightLandingAndFall + 0x134),
    (u32)((u8 *)dungeonUpdateFlightLandingAndFall + 0x13C),
    (u32)((u8 *)dungeonUpdateFlightLandingAndFall + 0x144),
    (u32)((u8 *)dungeonUpdateFlightLandingAndFall + 0x14C)
};
