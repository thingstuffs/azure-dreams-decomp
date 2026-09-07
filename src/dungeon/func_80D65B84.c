#include "common.h"

typedef struct {
    s32 x;
    s32 y;
    s32 z;
    s32 dx;
    s32 dy;
    s32 dz;
} Motion;

extern s32 D_800814A0;

void func_80D65B84(void *arg0, Motion *arg1, void *arg2) {
    s32 quotient;
    s16 count;

    arg1->x += arg1->dx;
    arg1->y += arg1->dy;
    arg1->z += arg1->dz;
    arg1->dx /= 2;
    arg1->dy /= 2;
    arg1->dz /= 2;

    quotient = (*(s16 *)((u8 *)arg0 + 0xC) << 7) /
               *(s16 *)((u8 *)arg0 + 0xE);
    *(s8 *)((u8 *)arg2 + 0xE) = quotient;
    *(s8 *)((u8 *)arg2 + 0xD) = quotient;
    *(s8 *)((u8 *)arg2 + 0xC) = quotient;

    count = *(u16 *)((u8 *)arg0 + 0xC) - 1;
    *(s16 *)((u8 *)arg0 + 0xC) = count;
    if ((count << 16) <= 0) {
        *(u16 *)((u8 *)arg0 - 2) |= 0x8000;
        D_800814A0 |= 0x8000;
    }
}
