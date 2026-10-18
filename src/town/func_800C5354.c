#include "common.h"
#include "m2c_compat.h"

extern s32 D_800834B8;
extern M2C_UNK D_80097D2C;
extern s32 D_800CFCC4;

/* Check whether both the requested identifier and the global pointer match. */
s32 check_transform_identifier_and_hook(s32 requested_id) {
    s32 matches;

    matches = 0;
    if (D_800CFCC4 == requested_id) {
        matches = D_800834B8 == (s32) &D_80097D2C;
    }
    return matches;
}
