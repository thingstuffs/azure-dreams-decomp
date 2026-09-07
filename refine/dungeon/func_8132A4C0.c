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

/* Update the fade color and mark completion when its countdown ends. */
void func_80171CC0(DungeonFade *fade, void *progress) {
    s16 steps_left;

    *(s32 *)((u8 *)progress + 8) += 0x10000;
    fade->scaled_r = (fade->r * fade->step) / fade->divisor;
    fade->scaled_g = (fade->g * fade->step) / fade->divisor;
    fade->scaled_b = (fade->b * fade->step) / fade->divisor;
    steps_left = (u16)fade->step - 1;
    fade->step = steps_left;
    fade->value = *(s32 *)&fade->scaled_r;
    if ((steps_left << 16) <= 0) {
        *(u16 *)((u8 *)fade - 2) |= 0x8000;
        D_800814A0[0] |= 0x8000;
    }
}
