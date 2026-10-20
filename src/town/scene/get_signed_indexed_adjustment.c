#include "common.h"

extern s32 D_00003F54[];
extern s32 D_00004114[];
extern s8 D_00004120[];
extern s32 D_000045F8[];

/* Return the base value plus the signed-index table adjustment. */
s32 get_signed_indexed_adjustment(void) {
    return D_000045F8[0] + D_00004114[D_00004120[D_00003F54[0]]];
}
