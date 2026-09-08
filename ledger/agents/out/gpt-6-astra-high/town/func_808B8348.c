#include "common.h"

extern s32 D_000045F8[];
extern s32 D_00004144[];

/* Return the sum of the first entries in the two global arrays. */
s32 func_808B8348(void) {
    return D_000045F8[0] + D_00004144[0];
}
