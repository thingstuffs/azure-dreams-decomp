#include "common.h"

extern u8 D_8006DE24[];

/* Returns the last byte of the selected 20-byte table entry. */
u8 func_800A3820(s16 entry_index) {
    int entry_offset = entry_index * 0x14;
    return D_8006DE24[entry_offset + 0x13];
}
