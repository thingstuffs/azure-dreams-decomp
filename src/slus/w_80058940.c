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

/* Scans forward from a0 through D_80085FA4's buffer (bounded by D_800869B0), looking
 * for a 3-byte match against D_800737D0. Returns the index just past a found match
 * (index + 3), or -1 if no match is found within the bound. */
s32 func_80058940(s32 a0)
{
    s32 v0;

    do {
        v0 = func_80058800(D_800737D0, (u8 *)D_80085FA4[0] + a0, 3);
        if (v0 == 0) {
            return a0 + 3;
        }
        a0++;
    } while ((u32)a0 <= (u32)D_800869B0[0]);
    return -1;
}
