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

void func_80020948(s32 arg0, Vec3s *vectors, Color *colors, s32 arg3)
{
    Effect *effect;
    EffectSub *sub;
    s32 i;

    effect = func_8003FD64(1, D_80083498);
    if (effect != NULL) {
        sub = &effect->sub;
        sub->field24 = arg3;
        for (i = 1; i >= 0; i--) {
            sub->vectors[i] = vectors[i];
            sub->colors[i] = colors[i];
        }
        effect->field10 = arg0;
        func_8004491C(effect, D_8002222C);
    }
}
