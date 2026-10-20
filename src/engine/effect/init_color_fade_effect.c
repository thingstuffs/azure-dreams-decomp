#include "common.h"

#include "common.h"
#include "shared/vector.h"

typedef struct S_800520B4_Sub {
    void *field_0x00;
    s16 field_0x04;
    s16 field_0x06;
    u8 pad_0x08[2];
    s16 field_0x0A;
    s16 field_0x0C;
} S_800520B4_Sub;

typedef struct S_800520B4_Ptr {
    u8 pad_0x00[8];
    void *field_0x08;
    s32 field_0x0C;
    u8 pad_0x10[0xC];
    s16 field_0x1C;
    s16 field_0x1E;
} S_800520B4_Ptr;


typedef struct S_800520B4 {
    u8 pad_0x00[8];
    IntVector3 *vec;
    S_800520B4_Ptr *ptr;
    void (*update_func)(void);
    u8 pad_0x14[0xC];
    S_800520B4_Sub sub;
} S_800520B4;

extern u8 D_80071FF0[0x10];
extern void update_color_fade_effect(void);
extern void draw_linked_sprites(void);
extern void register_node(S_800520B4 *a0, void (*a1)(void));

/* Initialize object state, callbacks, settings, and vector values. */
void init_color_fade_effect(S_800520B4 *object, void *context)
{
    s16 *state_words;
    S_800520B4_Ptr *settings;
    IntVector3 *vector;

    object->update_func = update_color_fade_effect;
    state_words = (s16 *)((u8 *)object + 0x20);
    object->sub.field_0x00 = context;
    state_words[2] = 0;
    state_words[3] = 0;
    state_words[5] = 0;
    state_words[6] = 0;

    settings = object->ptr;
    settings->field_0x08 = D_80071FF0;
    settings->field_0x0C = 0;
    settings->field_0x1E = 0x1000;
    settings->field_0x1C = 0x1000;

    register_node(object, draw_linked_sprites);

    vector = object->vec;
    vector->x = 0x980000;
    vector->y = 0x800000;
    vector->z = 0xA00000;
}
