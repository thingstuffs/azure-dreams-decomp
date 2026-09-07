#include "common.h"

extern void func_80047784(void *arg0, s32 arg1, s32 arg2);
extern s16 D_80083228;
extern u8 D_801760B4;

/* Initializes display state and selects a sprite frame from the combined facing angles. */
void func_801725C8(void *object, void *unused, void *sprite, void *orientationSource) {
    *((s8 *)object + 0x9A) = 0x10;
    *((s8 *)object + 0x9B) = 0;
    *(s16 *)((u8 *)sprite + 0x1C) = 0x1400;
    *(s16 *)((u8 *)sprite + 0x1E) = 0xC00;
    *(u8 **)((u8 *)sprite + 0x2C) = &D_801760B4;
    func_80047784(
        sprite,
        *(&D_801760B4 + (((D_80083228 + *(s16 *)((u8 *)orientationSource + 0x2A) + 0x100) >> 9) & 7)),
        0);
}
