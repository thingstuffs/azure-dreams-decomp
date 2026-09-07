#include "common.h"

extern u8 D_80083498[];
extern s32 D_800A5638;
extern s32 D_800A5A98;
extern s32 D_800A58CC;
extern s32 D_800A5340;

void func_800A5440(void *arg0) {
    u8 *base = D_80083498;

    if ((*(s32 **) (base + 0x10) != &D_800A5638) ||
        ((*(s32 **) (base + 0x20) != &D_800A5A98) &&
         (*(s32 **) (base + 0x20) != &D_800A58CC))) {
        *(s16 *) ((u8 *) arg0 + 2) = 0x20;
        *(s16 *) ((u8 *) arg0 + 4) = 0x400;
        *(void **) ((u8 *) arg0 + 0x1C) = &D_800A5340;
    }
}
