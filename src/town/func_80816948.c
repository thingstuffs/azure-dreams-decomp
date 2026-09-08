#include "common.h"

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

extern void *func_8003FD64(s32, void *);
extern void func_8004491C(void *, void *);
extern u8 D_80083498[];
extern void D_8002222C(void);

__asm__(".set D_8002222C, 0x8002222C");

/* Creates an effect with two vectors, two colors, and the supplied parameters. */
void func_80020948(s32 effect_param, Vec3s *vectors, Color *colors, s32 sub_param)
{
    Effect *effect;
    EffectSub *sub;
    s32 pair_index;

    effect = func_8003FD64(1, D_80083498);
    if (effect != NULL) {
        sub = &effect->sub;
        sub->field24 = sub_param;
        for (pair_index = 1; pair_index >= 0; pair_index--) {
            sub->vectors[pair_index] = vectors[pair_index];
            sub->colors[pair_index] = colors[pair_index];
        }
        effect->field10 = effect_param;
        func_8004491C(effect, D_8002222C);
    }
}
