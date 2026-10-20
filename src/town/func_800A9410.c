/* Recovered retail twin; complete-function proof is in the lane receipt. */
#include "common.h"
#include "shared/sprite_frame_state.h"
#ifndef NULL
#define NULL 0
#endif

extern void *create_town_effect_object(s32, s32, void *, s32);
extern void *initialize_object_transform_and_state(void *, void *, s32);
extern s32 D_800A6BEC;

void update_sine_pulse_color(s32 object_id) {
    s8 *model;
    s8 *object;

    object = (s8 *) create_town_effect_object(0, object_id, &D_800A6BEC, 0);
    if (object != NULL) {
        model = *(s8 **)(object + 0xC);
        initialize_object_transform_and_state(object + 0x20, model, 0x3A1);
        ((SpriteFrameState *)model)->unk_20 = 0x1800;
        ((SpriteFrameState *)model)->scale_y = 0x1800;
        ((SpriteFrameState *)model)->scale_x = 0x1800;
        ((SpriteFrameState *)model)->color.c.b = 0xFF;
        ((SpriteFrameState *)model)->color.c.g = 0xFF;
        ((SpriteFrameState *)model)->color.c.r = 0xFF;
        ((SpriteFrameState *)model)->flags = (u16) (((SpriteFrameState *)model)->flags | 0x1C);
    }
}
