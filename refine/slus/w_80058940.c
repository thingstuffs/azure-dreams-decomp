#include "common.h"

/* D_80085FA4: accessed via %hi/%lo (not gp_rel) in this and sibling funcs
 * (func_800589B8, func_800599B0, func_80058850, func_80058B70) -> declare size > 8 bytes.
 * Holds a byte-pointer value (base address of a working buffer). */
extern s32 D_80085FA4[4];

/* D_800869B0: accessed via %hi/%lo (not gp_rel) in this and sibling funcs
 * (func_800589B8, func_80058850, func_80058B70) -> declare size > 8 bytes.
 * Holds an integer bound/limit, compared unsigned against the loop index. */
extern s32 D_800869B0[4];

/* D_800737D0: hi/lo *address-of* (la, not lw) -> size must be > 8 bytes. Fixed byte
 * buffer compared against via func_80058800 (strncmp-like helper), 3 bytes at a time. */
extern u8 D_800737D0[12];

/* strncmp-like byte comparator: compares a2 bytes of a0/a1, returns 0 on full match,
 * else the difference of the first mismatching byte pair (or -1 if a2==0). */
extern s32 func_80058800(u8 *a0, u8 *a1, s32 a2);

/* Scans the working buffer for a three-byte match, returning its end offset or -1. */
s32 func_80058940(s32 offset)
{
    s32 comparison;

    do {
        comparison = func_80058800(D_800737D0, (u8 *)D_80085FA4[0] + offset, 3);
        if (comparison == 0) {
            return offset + 3;
        }
        offset++;
    } while ((u32)offset <= (u32)D_800869B0[0]);
    return -1;
}
