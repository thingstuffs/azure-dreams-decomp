#include "common.h"
#include "shared/game_work.h"

extern s32 D_800A51CC;
extern s32 D_800A5340;

/* Initialize paired state values and install the two callbacks. */
void func_800A5178(void *state) {
    u16 initial_ac;
    u16 initial_ae;

    initial_ac = ((u16)gameWork.unk_0AC);
    *(u16 *) ((u8 *) state + 0) = initial_ac;
    *(u16 *) ((u8 *) state + 0x10) = initial_ac;

    initial_ae = ((u16)gameWork.unk_0AE);
    *(u16 *) ((u8 *) state + 2) = initial_ae;
    *(u16 *) ((u8 *) state + 0x12) = initial_ae;

    gameWork.unk_0B0 = 0x400;
    *(s16 *) ((u8 *) state + 4) = 0x400;
    *(s16 *) ((u8 *) state + 0x14) = 0x400;
    *(void **) ((u8 *) state + 0x1C) = &D_800A5340;
    *(void **) ((u8 *) state + 0x20) = &D_800A51CC;
}
