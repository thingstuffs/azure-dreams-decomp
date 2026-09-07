#include "common.h"

typedef struct DungeonFade {
    u8 r;
    u8 g;
    u8 b;
    u8 pad03;
    s8 scaled_r;
    s8 scaled_g;
    s8 scaled_b;
    u8 pad07;
    s32 value;
    u8 pad0C[0x26];
    s16 step;
    s16 divisor;
} DungeonFade;

extern s32 D_800814A0[3];

void func_80171CC0(DungeonFade *arg0, void *arg1) {
    s16 step;

    *(s32 *)((u8 *)arg1 + 8) += 0x10000;
    arg0->scaled_r = (arg0->r * arg0->step) / arg0->divisor;
    arg0->scaled_g = (arg0->g * arg0->step) / arg0->divisor;
    arg0->scaled_b = (arg0->b * arg0->step) / arg0->divisor;
    step = (u16)arg0->step - 1;
    arg0->step = step;
    arg0->value = *(s32 *)&arg0->scaled_r;
    if ((step << 16) <= 0) {
        *(u16 *)((u8 *)arg0 - 2) |= 0x8000;
        D_800814A0[0] |= 0x8000;
    }
}
