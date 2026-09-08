#include "common.h"

extern u8 D_80083498[];
extern s32 D_800A5638;
extern s32 D_800A5A98;
extern s32 D_800A58CC;
extern s32 D_800A5340;

/* Set the record parameters and handler when the global handlers do not match. */
void func_800A5440(void *record) {
    u8 *base = D_80083498;

    if ((*(s32 **) (base + 0x10) != &D_800A5638) ||
        ((*(s32 **) (base + 0x20) != &D_800A5A98) &&
         (*(s32 **) (base + 0x20) != &D_800A58CC))) {
        *(s16 *) ((u8 *) record + 2) = 0x20;
        *(s16 *) ((u8 *) record + 4) = 0x400;
        *(void **) ((u8 *) record + 0x1C) = &D_800A5340;
    }
}
