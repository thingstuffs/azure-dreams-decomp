/* Recovered retail twin; complete-function proof is in the lane receipt. */
#include "common.h"
#include "town.h"
#include "shared/object_node.h"
#include "shared/sprite_frame_state.h"
#ifndef NULL
#define NULL 0
#endif

extern void *create_town_effect_object(s32, s32, void *, s32);
extern void *initialize_object_transform_and_state(void *, void *, s32);

/* Creates a white effect with scale 0x1800 and installs its fade-and-shrink callback. */
void update_sine_pulse_color(s32 object_id) {
    SpriteFrameState *model;
    ObjectNodeHeader *object;

    object = (s8 *) create_town_effect_object(0, object_id, fade_effect_and_mark_cleanup, 0);
    if (object != NULL) {
        model = object->sprite;
        initialize_object_transform_and_state(((s8 *)object) + 0x20, model, 0x3A1);
        model->offset_x = 0x1800;
        model->scale_y = 0x1800;
        model->scale_x = 0x1800;
        model->color.c.b = 0xFF;
        model->color.c.g = 0xFF;
        model->color.c.r = 0xFF;
        model->flags = (u16) (model->flags | 0x1C);
    }
}
