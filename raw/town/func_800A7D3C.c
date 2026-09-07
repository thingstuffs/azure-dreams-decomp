#include "common.h"

extern u8 D_80100D98[];
extern s32 D_800A5340;

extern s32 func_8003BD84(s32 a0, s32 a1);

void func_800A549C(void *arg0) {
    u8 *base = D_80100D98;

    if (func_8003BD84(*(s32 *) (base + 0xC), *(s32 *) (base + 0x10)) <= 0xDFFFF) {
        *(s16 *) ((u8 *) arg0 + 4) = 0x400;
        *(void **) ((u8 *) arg0 + 0x1C) = &D_800A5340;
    }
}
