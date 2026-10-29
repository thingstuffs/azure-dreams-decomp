#include "common.h"
#include "town/scene.h"

extern s32 D_000045F8[];
extern s32 D_00004144[];

/* Return the sum of the first entries in the two global arrays. */
s32 sum_global_array_entries(void) {
    return D_000045F8[0] + D_00004144[0];
}
