#include "common.h"

s32 func_80033B2C();                         /* extern */
void func_800A99C8();                               /* extern */
extern s16 D_800D1054[];

s32 func_800A9970(s32 arg0) {
    s16 *indices;
    u8 *page;
    s32 index;

    indices = D_800D1054;
    index = indices[arg0];
    page = (u8 *) 0x80010000;
    if (page[(index * 4) + 0x35C4] >= 3U) {
        func_800A99C8();
        return 1;
    }
    if (arg0 == 3) {
        return func_80033B2C(0x4FB) == 0;
    }
    return 0;
}

/* MECHANISM: Separate short-table and fixed-page pointer locals encode the
   retail $v1 base reuse around a signed-halfword index; the frame is ra-only.
   Path-local returns keep the zero/helper result in $v0; literal one is SHAPE-C. */
