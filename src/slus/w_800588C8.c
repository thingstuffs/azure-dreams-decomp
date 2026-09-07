#include "common.h"

/* Searches a byte table (base D_80085FA4[0], length D_800869B0[0]) starting at
 * byte index `a0`, looking for a run of 4 bytes matching D_80033104. Returns
 * (match index + 4) on success, or -1 if the search runs off the end of the
 * table without finding a match. Twin of func_80058850. */
/* D_80085FA4: [0] = base address of a byte table; accessed via %hi/%lo (forced size>8) */
extern s32 D_80085FA4[4];

/* D_800869B0: [0] = table length/bound; accessed via %hi/%lo (forced size>8) */
extern s32 D_800869B0[4];

/* Fixed 4-byte data blob compared against entries in the D_80085FA4[0] table. */
extern s8 D_80033104[];

extern s32 func_80058800(s8 *a0, s8 *a1, s32 a2);

s32 func_800588C8(s32 a0)
{
    s32 s0 = a0;

    do {
        if (func_80058800(D_80033104, (s8 *)D_80085FA4[0] + s0, 4) == 0) {
            return s0 + 4;
        }
        s0 = s0 + 1;
    } while ((u32)D_800869B0[0] >= (u32)s0);

    return -1;
}
