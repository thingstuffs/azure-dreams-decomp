#include "common.h"
#define F(p,t,o) (*(t *)((u8 *)(p) + (o)))
extern s32 func_80099194();
extern s32 func_800992E8();
extern s32 D_800DD72C[];
extern s32 D_800DD784[];
extern u8 *D_800E3D7C[];
s32 func_8009955C(void *a, s32 b) {
    u8 c;
    s32 d, x, y, r;
    if (!(F(D_800E3D7C[0], s32, 0x1C) & 0x10)) {
        c = F(a, u8, 1); x = D_800DD72C[c];
        if (x && (c != 15 || F(a, u8, 0) < 14)) b = func_80099194(x, b, c);
    }
    r = func_800992E8(a, b);
    if (!(F(D_800E3D7C[0], s32, 0x1C) & 0x10)) {
        d = F(a, u8, 1); y = D_800DD784[d];
        if (y) {
            if (d == 15 && F(a, u8, 0) >= 14) {
                return r;
            }
            r = func_80099194(y, r, d);
        }
    }
    return r;
}

/* MECHANISM: Pointer-array declaration preserves hi/lo access while loading D_800E3D7C's stored base.
   Full-width ABI plus the restored middle helper argument removes preservation/truncation code.
   The second rejection is an early return; its s32 index keeps the lbu directly in $a2. */
