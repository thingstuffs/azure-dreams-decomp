#include "common.h"

/* S_80085FA4: array whose element 0 is a base address (cast to byte pointer for
 * pointer arithmetic in func_80058850, and set from a literal 0x80080000 address
 * value in func_800587B4). */
extern s32 D_80085FA4[4];

/* S_800869B0: array whose element 0 is a size/count value (unsigned compare
 * against a running index in func_80058850; set to 0xC000 in func_800587B4). */
extern s32 D_800869B0[4];

/* Fixed 4-byte data blob compared against entries in the D_80085FA4[0] table. */
extern s8 D_800330FC[];

extern s32 func_80058800(s8 *a0, s8 *a1, s32 a2);

/* Searches from start_index for D_800330FC's four bytes, returning the index after the match or -1. */
s32 func_80058850(s32 start_index)
{
    s32 byte_index = start_index;

    do {
        if (func_80058800(D_800330FC, (s8 *)D_80085FA4[0] + byte_index, 4) == 0) {
            return byte_index + 4;
        }
        byte_index = byte_index + 1;
    } while ((u32)D_800869B0[0] >= (u32)byte_index);

    return -1;
}
