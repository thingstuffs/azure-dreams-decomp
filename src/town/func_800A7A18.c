#include "common.h"

typedef struct {
    u8 pad[0xAC];
    u16 f_AC;
    u16 f_AE;
    s16 f_B0;
} S_80083160;

extern S_80083160 D_80083160;
extern s32 D_800A51CC;
extern s32 D_800A5340;

void func_800A5178(void *arg0) {
    u16 cache0;
    u16 cache1;

    cache0 = D_80083160.f_AC;
    *(u16 *) ((u8 *) arg0 + 0) = cache0;
    *(u16 *) ((u8 *) arg0 + 0x10) = cache0;

    cache1 = D_80083160.f_AE;
    *(u16 *) ((u8 *) arg0 + 2) = cache1;
    *(u16 *) ((u8 *) arg0 + 0x12) = cache1;

    D_80083160.f_B0 = 0x400;
    *(s16 *) ((u8 *) arg0 + 4) = 0x400;
    *(s16 *) ((u8 *) arg0 + 0x14) = 0x400;
    *(void **) ((u8 *) arg0 + 0x1C) = &D_800A5340;
    *(void **) ((u8 *) arg0 + 0x20) = &D_800A51CC;
}
