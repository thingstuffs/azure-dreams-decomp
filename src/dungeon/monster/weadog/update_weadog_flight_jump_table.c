#include "common.h"

extern void advance_item_flight_to_floor(void);

/* jump_table; owner: dungeon/func_80EDF000. */
const u32 D_80170828[5] __attribute__((aligned(4))) = {
    (u32)((u8 *)advance_item_flight_to_floor + 0x12C),
    (u32)((u8 *)advance_item_flight_to_floor + 0x134),
    (u32)((u8 *)advance_item_flight_to_floor + 0x13C),
    (u32)((u8 *)advance_item_flight_to_floor + 0x144),
    (u32)((u8 *)advance_item_flight_to_floor + 0x14C)
};
