#include "common.h"
#include "m2c_compat.h"

s32 func_8008C180();                        /* extern */

typedef struct S_800AAE98_0 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
} S_800AAE98_0;   /* arg0 in func_800AAE98 */

/* Returns 0x18 for lookup codes in three special ranges, or 0x60 otherwise. */
s32 func_800AAE98(S_800AAE98_0 *coordinates) {
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
    ASM_KEEP(lookupCode);   /* MATCH pin: load-bearing for the whole function shape */
    return 0x60;
}

