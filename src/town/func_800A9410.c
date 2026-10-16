/* Recovered retail twin; complete-function proof is in the lane receipt. */
#include "common.h"
#ifndef NULL
#define NULL 0
#endif

extern void *townCreateTownEffectObject(s32, s32, void *, s32);
extern void *townInitializeObjectTransformAndState(void *, void *, s32);
extern s32 D_800A6BEC;

void func_800A6B70(s32 object_id) {
    s8 *model;
    s8 *object;

    object = (s8 *) townCreateTownEffectObject(0, object_id, &D_800A6BEC, 0);
    if (object != NULL) {
        model = *(s8 **)(object + 0xC);
        townInitializeObjectTransformAndState(object + 0x20, model, 0x3A1);
        *(s16 *)(model + 0x20) = 0x1800;
        *(s16 *)(model + 0x1E) = 0x1800;
        *(s16 *)(model + 0x1C) = 0x1800;
        *(u8 *)(model + 0xE) = 0xFF;
        *(u8 *)(model + 0xD) = 0xFF;
        *(u8 *)(model + 0xC) = 0xFF;
        *(u16 *)(model + 0x14) = (u16) (*(u16 *)(model + 0x14) | 0x1C);
    }
}
