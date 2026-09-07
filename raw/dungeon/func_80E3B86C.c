#include "common.h"

extern s32 func_8009A350(s16, s16, s16, u16 *);
extern s16 func_800BCB04(s32, s32, s16);
extern s16 D_8006CCD8[];
extern s16 D_8006CCE8[];

s32 func_8017506C(s16 arg0, s16 arg1, s32 arg2, s16 arg3, s16 *arg4) {
    u16 flags;
    s16 result;

    if ((func_8009A350(arg0, arg1, arg3, &flags) << 16) == 0) {
        return 0;
    }
    if (flags & 0xB700) {
        goto fail;
    }

    result = func_800BCB04(
        ((arg0 + D_8006CCD8[arg3]) << 6) + 0x20 & 0xFFE0,
        ((arg1 + D_8006CCE8[arg3]) << 6) + 0x20 & 0xFFE0,
        (s16)(arg2 - 0x20));
    *arg4 = result;
    if (result < 0x200) {
        return 1;
    }

fail:
    return 0;
}
