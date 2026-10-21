#include "common.h"
#include "shared/vector.h"
#include "engine/node.h"

/* Element of the D_80071A68 lookup table indexed by an object's "kind" field. */
typedef struct S_80071A68 {
    /* 0x00 */ s32 field_0x00;
} S_80071A68;

extern S_80071A68 fade_effect_visual_table[];

extern void update_fade_in_out_effect(void);
extern void draw_linked_sprites(void);

/* Struct pointed to by S_80051E94.ptr (offset 0xC). */
typedef struct S_80051E94_Ptr {
    /* 0x00 */ u8 unk00[0x8];
    /* 0x08 */ s32 field_0x08;
    /* 0x0C */ s32 field_0x0C;
    /* 0x10 */ u8 pad10[0xC];
    /* 0x1C */ s16 field_0x1C;
    /* 0x1E */ s16 field_0x1E;
} S_80051E94_Ptr;

/* Sub-object embedded at offset 0x20 of S_80051E94 ("Entity"-style object). */
typedef struct S_80051E94_Sub {
    /* 0x00 */ s32 field_0x00;
    /* 0x04 */ s16 field_0x04;
    /* 0x06 */ s16 field_0x06;
    /* 0x08 */ u8 pad_0x08[2];
    /* 0x0A */ s16 field_0x0A;
    /* 0x0C */ s16 field_0x0C;
} S_80051E94_Sub;

/* Struct pointed to by S_80051E94.vecPtr (offset 0x8); populated by
 * register_node as a side effect and then filled in here with three
 * 16.16-fixed-point constants (integer part only, low half zero). */


/* Common "Entity"/"Obj" object layout used across code.c: update_func at 0x10. */
typedef struct S_80051E94 {
    /* 0x00 */ u8 unk00[0x8];
    /* 0x08 */ IntVector3 *vecPtr;
    /* 0x0C */ S_80051E94_Ptr *ptr;
    /* 0x10 */ void (*update_func)(void);
    /* 0x14 */ u8 unk14[0xC];
    /* 0x20 */ S_80051E94_Sub sub;
} S_80051E94;

/* Initialize an object's update callback, sub-object, lookup defaults, and fixed-point vector. */
void init_fade_in_out_effect(S_80051E94 *object, s32 sub_value)
{
    S_80051E94_Sub *sub_state;
    S_80051E94_Ptr *render_state;
    IntVector3 *render_vector;
    s32 kind_value;

    object->update_func = update_fade_in_out_effect;
    sub_state = &object->sub;
    sub_state->field_0x00 = sub_value;
    sub_state->field_0x04 = 0;
    sub_state->field_0x06 = 0;
    sub_state->field_0x0A = 0;
    sub_state->field_0x0C = 0;

    render_state = object->ptr;
    render_state->field_0x0C = 0;
    kind_value = fade_effect_visual_table[sub_state->field_0x0A].field_0x00;
    render_state->field_0x1E = 0x1000;
    render_state->field_0x1C = 0x1000;
    render_state->field_0x08 = kind_value;

    register_node(object, draw_linked_sprites);

    render_vector = object->vecPtr;
    render_vector->x = 0x380000;
    render_vector->y = 0x280000;
    render_vector->z = 0x900000;
}
