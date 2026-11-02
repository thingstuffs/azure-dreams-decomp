#include "shared/sprite_frame_state.h"
#include "shared/entity.h"
#include "common.h"
#include "shared/vector.h"
#include "engine/node.h"
#include "engine/graphics.h"
#include "engine/effect.h"

/* Element of the D_80071A68 lookup table indexed by an object's "kind" field. */
typedef struct S_80071A68 {
    /* 0x00 */ void *field_0x00;
} S_80071A68;

extern S_80071A68 fade_effect_visual_table[];

struct ObjectPosition;
struct SpriteFrameState;

/* Struct pointed to by S_80051E94.ptr (offset 0xC). */
/* Sub-object embedded at offset 0x20 of S_80051E94 ("Entity"-style object). */
/* Struct pointed to by S_80051E94.vecPtr (offset 0x8); populated by
 * register_node as a side effect and then filled in here with three
 * 16.16-fixed-point constants (integer part only, low half zero). */


/* Common "Entity"/"Obj" object layout used across code.c: update_func at 0x10. */
/* Initialize an object's update callback, sub-object, lookup defaults, and fixed-point vector. */
void init_fade_in_out_effect(CdCueEffectNode *object, struct Controller *owner)
{
    CdCueEffectBody *sub_state;
    SpriteFrameState *render_state;
    ObjectPosition *render_vector;
    void *kind_value;

    object->header.update_callback = update_fade_in_out_effect;
    sub_state = &object->body;
    sub_state->owner.controller = owner;
    sub_state->state.s = 0;
    sub_state->timer.s = 0;
    sub_state->index = 0;
    sub_state->completion = 0;

    render_state = object->header.sprite;
    render_state->color.word = 0;
    kind_value = fade_effect_visual_table[sub_state->index].field_0x00;
    render_state->scale_y = 0x1000;
    render_state->scale_x = 0x1000;
    render_state->source = kind_value;

    register_node(&object->header, draw_linked_sprites);

    render_vector = object->header.position;
    render_vector->x.v = 0x380000;
    render_vector->y.v = 0x280000;
    render_vector->z.v = 0x900000;
}
