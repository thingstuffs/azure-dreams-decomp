#include "common.h"

/* D_80085FA4: [0] = base address of a byte table; accessed via %hi/%lo (forced size>8) */
extern s32 D_80085FA4[4];

/* D_800869B0: [0] = table length/bound; accessed via %hi/%lo (forced size>8) */
extern s32 D_800869B0[4];

/* Fixed 4-byte data blob compared against entries in the D_80085FA4[0] table. */
extern s8 D_80033104[];

extern s32 func_80058800(s8 *a0, s8 *a1, s32 a2);

/* Searches the byte table for D_80033104's four bytes, returning the index after the match or -1. */
s32 func_800588C8(s32 start_index)
{
    s32 index = start_index;

    do {
        if (func_80058800(D_80033104, (s8 *)D_80085FA4[0] + index, 4) == 0) {
            return index + 4;
        }
        index = index + 1;
    } while ((u32)D_800869B0[0] >= (u32)index);

    return -1;
}
