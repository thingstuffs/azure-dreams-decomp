#include "common.h"
#include "shared/object_node.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct {
    s16 x;
    s16 y;
    s16 z;
    s16 pad;
} Vec3s;

typedef struct {
    u8 r;
    u8 g;
    u8 b;
    u8 code;
} Color;

typedef struct {
    u8 pad20[4];
    s32 field24;
    Vec3s vectors[2];
    Color colors[2];
} EffectSub;

typedef struct {
    u8 pad0[0x10];
    s32 field10;
    u8 pad14[0xC];
    EffectSub sub;
} Effect;

extern void *allocate_list_node(s32, void *);
extern void register_node(void *, void *);
extern void D_8002222C(void);

/* Creates an effect with two vectors, two colors, and the supplied parameters. */
void create_paired_vector_color_effect(s32 effect_param, Vec3s *vectors, Color *colors, s32 sub_param)
{
    Effect *effect;
    EffectSub *sub;
    s32 pair_index;

    effect = allocate_list_node(1, &scene_object_list_anchor.next);
    if (effect != NULL) {
        sub = &effect->sub;
        sub->field24 = sub_param;
        for (pair_index = 1; pair_index >= 0; pair_index--) {
            sub->vectors[pair_index] = vectors[pair_index];
            sub->colors[pair_index] = colors[pair_index];
        }
        effect->field10 = effect_param;
        register_node(effect, D_8002222C);
    }
}
