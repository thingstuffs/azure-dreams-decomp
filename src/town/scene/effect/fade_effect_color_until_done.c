#include "common.h"
#include "town/scene/effect.h"
#include "town/data.h"
#include "town/scene/score_sprite_data.h"

/* Waits for linked flag 8, then decreases field +8 until the object is marked for removal. */
void fade_effect_color_until_done(RisingScoreFade *effect) {
    TownScoreCounterView *controller;
    s32 state;
    s32 value;

    state = effect->state;
    controller = effect->controller;
    switch (state) {
    case 0:
        if (controller->flags & 8) {
            effect->state++;
        }
        break;
    case 1:
        value = effect->color - 0x80808;
        effect->color = value;
        if (value <= 0x80808) {
            u16 *flags = &NODE_HEADER(effect)->flags;
            *flags |= 0x8000;
            scene_object_flags |= 0x8000;
        }
        break;
    }
}
