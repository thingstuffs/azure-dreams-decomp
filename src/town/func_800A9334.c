#include "common.h"
#ifndef NULL
#define NULL 0
#endif

extern void *create_town_effect_object(s32, s32, void *, s32);
extern void *initialize_object_transform_and_state(void *, void *, s32);
extern s32 D_800A6B10;

/* Creates an object and initializes its model scale, color, and flags. */
void create_colored_scaled_effect(s32 object_id) {
    s8 *model;
    s8 *object;

    object = (s8 *) create_town_effect_object(0, object_id, &D_800A6B10, 0);
    if (object != NULL) {
        model = *(s8 **)(object + 0xC);
        initialize_object_transform_and_state(object + 0x20, model, 0x3A1);
        *(s16 *)(model + 0x20) = 0xC00;
        *(s16 *)(model + 0x1E) = 0xC00;
        *(s16 *)(model + 0x1C) = 0xC00;
        *(u8 *)(model + 0xE) = 0xFF;
        *(u8 *)(model + 0xD) = 0xFF;
        *(u8 *)(model + 0xC) = 0xFF;
        *(u16 *)(model + 0x14) = (u16) (*(u16 *)(model + 0x14) | 0x1C);
    }
}
