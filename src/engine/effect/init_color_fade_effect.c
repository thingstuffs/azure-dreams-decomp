#include "shared/sprite_frame_state.h"
#include "shared/entity.h"
#include "common.h"

#include "common.h"
#include "shared/vector.h"
#include "engine/node.h"
#include "engine/graphics.h"

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
    ObjectNodeHeader header;
    S_800520B4_Sub sub;
} S_800520B4;

extern u8 color_fade_visual_data[0x10];
extern void update_color_fade_effect(void);
struct ObjectPosition;
struct SpriteFrameState;

/* Initialize object state, callbacks, settings, and vector values. */
void init_color_fade_effect(S_800520B4 *object, void *context)
{
    s16 *state_words;
    SpriteFrameState *settings;
    ObjectPosition *vector;

    object->header.update_callback = update_color_fade_effect;
    state_words = (s16 *)((u8 *)object + 0x20);
    object->sub.field_0x00 = context;
    state_words[2] = 0;
    state_words[3] = 0;
    state_words[5] = 0;
    state_words[6] = 0;

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
