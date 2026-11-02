#include "shared/sprite_frame_state.h"
#include "shared/entity.h"
#include "common.h"

#include "common.h"
#include "shared/vector.h"
#include "engine/node.h"
#include "engine/graphics.h"
#include "engine/effect.h"

extern u8 color_fade_visual_data[0x10];
struct ObjectPosition;
struct SpriteFrameState;

/* Initialize object state, callbacks, settings, and vector values. */
void init_color_fade_effect(CdCueEffectNode *object, struct Controller *context)
{
    CdCueEffectBody *state;
    SpriteFrameState *settings;
    ObjectPosition *vector;

    object->header.update_callback = update_color_fade_effect;
    state = &object->body;
    state->owner.controller = context;
    state->state.s = 0;
    state->timer.s = 0;
    state->index = 0;
    state->completion = 0;

    settings = object->header.sprite;
    settings->source = color_fade_visual_data;
    settings->color.word = 0;
    settings->scale_y = 0x1000;
    settings->scale_x = 0x1000;

    register_node(&object->header, draw_linked_sprites);

    vector = object->header.position;
    vector->x.v = 0x980000;
    vector->y.v = 0x800000;
    vector->z.v = 0xA00000;
}
