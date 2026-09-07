#include "common.h"



extern s32 D_80083460[3];

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

typedef struct S_800A2BDC_0 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x4];
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
} S_800A2BDC_0;   /* p in func_800A2BDC */

s32 func_800A2BDC(void) {
    s32 *p = D_80083460;

    if (((S_800A2BDC_0 *)p)->unk_0C != 0) {
        goto ret_one;
    }
    if (((S_800A2BDC_0 *)p)->unk_10 != 0) {
        goto ret_one;
    }
    if (((S_800A2BDC_0 *)p)->unk_08 != 0) {
        goto ret_one;
    }
    if ((((S_800A2BDC_0 *)p)->unk_02 & 0x2008) != 0) {
        goto ret_one;
    }
    goto ret_zero;

ret_one:
    return 1;

ret_zero:
    return 0;
}
