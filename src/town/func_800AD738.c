#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_800AAE98_arg0.h"

s32 func_8008C180();                        /* extern */


/* Returns 0x18 for lookup codes in three special ranges, or 0x60 otherwise. */
s32 func_800AAE98(Rec_func_800AAE98_arg0 *coordinates) {
    s32 lookupCode;

    lookupCode = func_8008C180(coordinates->unk_02, coordinates->unk_06) & 0xFFFF;
    if ((u32) (lookupCode - 0xC0) < 3U) {
        return 0x18;
    }
    if ((u32) (lookupCode - 0xC7) < 3U) {
        return 0x18;
    }
    if ((u32) (lookupCode - 0xCE) < 3U) {
        return 0x18;
    }
    lookupCode = 0;
    return 0x60;
}

