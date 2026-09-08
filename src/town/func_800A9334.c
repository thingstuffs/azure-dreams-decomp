#include "common.h"
#ifndef NULL
#define NULL 0
#endif

extern void *func_8009C390(s32, s32, void *, s32);
extern void *func_8009CD18(void *, void *, s32);
extern s32 D_800A6B10;

/* Creates an object and initializes its model scale, color, and flags. */
void func_800A6A94(s32 object_id) {
    s8 *model;
    s8 *object;

    object = (s8 *) func_8009C390(0, object_id, &D_800A6B10, 0);
    if (object != NULL) {
        model = *(s8 **)(object + 0xC);
        func_8009CD18(object + 0x20, model, 0x3A1);
        *(s16 *)(model + 0x20) = 0xC00;
        *(s16 *)(model + 0x1E) = 0xC00;
        *(s16 *)(model + 0x1C) = 0xC00;
        *(u8 *)(model + 0xE) = 0xFF;
        *(u8 *)(model + 0xD) = 0xFF;
        *(u8 *)(model + 0xC) = 0xFF;
        *(u16 *)(model + 0x14) = (u16) (*(u16 *)(model + 0x14) | 0x1C);
    }
}
