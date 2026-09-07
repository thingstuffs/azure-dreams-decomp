#include "common.h"

extern u8 D_80080B28[16];
extern u8 D_80080B2C[16];
extern void bzero(void *, s32);

void *func_800499E8(u8 *p, u8 *src, u8 *col)
{
    u8 c0[4];
    u8 c1[4];
    u32 w0;
    u32 w2;
    u32 w1;
    u32 w3;
    u8 *ret;

    memcpy(c0, D_80080B28, 4);
    memcpy(c1, D_80080B2C, 4);
    bzero(p, 0x14);

    if ((*(s32 *)col & 0xFFFFFF) != 0x808080) {
        c0[0] = (c0[0] * col[0]) >> 7;
        c0[1] = (c0[1] * col[1]) >> 7;
        c0[2] = (c0[2] * col[2]) >> 7;
        if ((*(s32 *)col & 0xFFFFFF) != 0x808080) {
            c1[0] = (c1[0] * col[0]) >> 7;
            c1[1] = (c1[1] * col[1]) >> 7;
            c1[2] = (c1[2] * col[2]) >> 7;
        }
    }

    p[1] = 0x38;
    w0 = *(u32 *)c0;
    w1 = *(u32 *)c1;
    *(u32 *)(p + 4) = w0;
    *(u32 *)(p + 0xC) = w0;
    *(u32 *)(p + 0x10) = w1;
    *(u32 *)(p + 0x14) = w1;
    p[2] = src[0];
    p[3] = src[2];
    p[0xA] = src[4];
    p[0xB] = *(s16 *)(src + 6) / 4;

    p += 0x18;
    p[1] = 0x28;
    *(u32 *)(p + 4) = *(u32 *)c1;
    p[2] = src[0];
    p[3] = src[2] + *(s16 *)(src + 6) / 4;
    p[0xA] = src[4];
    p[0xB] = *(s16 *)(src + 6) / 2;

    p += 0xC;
    p[1] = 0x38;
    w3 = *(u32 *)c1;
    w2 = *(u32 *)c0;
    *(u32 *)(p + 4) = w3;
    *(u32 *)(p + 0xC) = w3;
    *(u32 *)(p + 0x10) = w2;
    *(u32 *)(p + 0x14) = w2;
    p[2] = src[0];
    p[3] = src[2] + *(s16 *)(src + 6) / 4 + *(s16 *)(src + 6) / 2;
    p[0xA] = src[4];
    p[0xB] = src[6] - *(s16 *)(src + 6) / 4 - *(s16 *)(src + 6) / 2;

    p += 0x18;
    ret = p - 0x3C;
    ASM_USE_NV(ret);
    p[1] = 0x81;
    *(u16 *)(p + 4) = 0x10;
    *(u16 *)(p + 6) = 1;
    p[0] |= 0x80;

    return ret;
}
