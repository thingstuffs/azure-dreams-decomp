#include "common.h"

s32 printf(); /* extern, called with varying arg counts (2/5/8) - old-style unprototyped decl */
extern u32 D_8017683C;
extern u32 D_80176864;
extern u32 D_8017689C;
extern s32 *D_8017834C;
extern volatile u32 *D_80178354;
extern s32 *D_80178358;
extern u32 *D_80178360;
extern u32 *D_80178380;

s32 func_80041508(u32 arg0) {
    u32 temp_s0;
    u32 arg2;
    u32 arg3;
    s32 ret;

    printf(&D_8017689C, arg0);
    temp_s0 = *(volatile u32 *) D_80178380;
    arg2 = (*D_80178354 >> 0x18) & 1;
    arg3 = (*(volatile u32 *) D_80178360 >> 0x18) & 1;
    printf(&D_8017683C, arg2, arg3, *D_8017834C, *D_80178358);
    printf(&D_80176864, (u32) ~temp_s0 >> 0x1F, (temp_s0 >> 0x1E) & 1, (temp_s0 >> 0x1D) & 1, (temp_s0 >> 0x1C) & 1, (temp_s0 >> 0x1B) & 1, (temp_s0 >> 0x19) & 1, (temp_s0 >> 0x17) & 1);
    *D_80178380 = 0x80000000;
    *D_80178354 = 0;
    *D_80178360 = 0;
    ret = 0;
    (void) *(volatile u32 *) D_80178360;
    *D_80178380 = 0x60000000;
    return ret;
}
