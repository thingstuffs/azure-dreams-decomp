#include "common.h"

typedef struct {
    u8 pad00[0x11];
    u8 unk11;
    u8 pad12[0x6];
    s32 unk18;
} S_80043868;

extern s32 func_8004383C(S_80043868 *arg0, s16 arg1);

s32 func_80043868(S_80043868 *arg0)
{
    s32 lo;
    s32 hi;
    register s32 range ASM_REG("$4");   /* UNRESOLVED C shape (pin): slus-diff; the source shape that makes it unnecessary has not been found */
    register s32 ret ASM_REG("$4");   /* UNRESOLVED C shape (pin): slus-diff; the source shape that makes it unnecessary has not been found */

    lo = func_8004383C(arg0, -1);
    hi = func_8004383C(arg0, 0);
    range = hi - lo;
    lo = arg0->unk18 - lo;
    ret = (lo * 20) / range;
    if (ret >= 21) {
        ret = 20;
    }
    return ret;
}
