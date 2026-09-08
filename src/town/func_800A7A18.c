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

/* Initialize paired state values and install the two callbacks. */
void func_800A5178(void *state) {
    u16 initial_ac;
    u16 initial_ae;

    initial_ac = D_80083160.f_AC;
    *(u16 *) ((u8 *) state + 0) = initial_ac;
    *(u16 *) ((u8 *) state + 0x10) = initial_ac;

    initial_ae = D_80083160.f_AE;
    *(u16 *) ((u8 *) state + 2) = initial_ae;
    *(u16 *) ((u8 *) state + 0x12) = initial_ae;

    D_80083160.f_B0 = 0x400;
    *(s16 *) ((u8 *) state + 4) = 0x400;
    *(s16 *) ((u8 *) state + 0x14) = 0x400;
    *(void **) ((u8 *) state + 0x1C) = &D_800A5340;
    *(void **) ((u8 *) state + 0x20) = &D_800A51CC;
}
