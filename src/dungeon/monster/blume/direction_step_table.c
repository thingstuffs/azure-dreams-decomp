#include "common.h"



/* Exact numeric span; owner-unresolved. */
const u32 blume_slot_g_direction_steps[8] __attribute__((aligned(4))) = {
    0x00000001,
    0x00020002,
    0x00010000,
    0x0002FFFE,
    0x0000FFFF,
    0xFFFEFFFE,
    0xFFFF0000,
    0xFFFE0002
};
