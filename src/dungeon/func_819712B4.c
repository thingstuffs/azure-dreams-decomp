#include "common.h"

typedef struct {
    u8 pad[0x38];
    s16 timer;
    s16 divisor;
    u16 phase;
} Obj;

typedef struct {
    u8 pad0[8];
    s32 value;
    u8 padC[8];
    s32 delta;
} Motion;

extern s16 D_80025FF4;
extern s32 D_800814A0[3];
extern void func_800478B8(void *arg0);

void func_819712B4(Obj *arg0, Motion *arg1, s8 *arg2)
{
    s32 level;
    u16 phase;

    D_80025FF4 = 1;
    arg0->timer--;
    phase = arg0->phase + 1;
    arg0->phase = phase;
    if ((s16)phase == 2) {
        arg0->phase = 0;
        func_800478B8(arg2);
    }
    level = (arg0->timer << 7) / arg0->divisor;
    arg2[14] = level;
    arg2[13] = level;
    arg2[12] = level;
    arg1->value += arg1->delta;
    if (arg0->timer <= 0) {
        ((u16 *)arg0)[-1] |= 0x8000;
        D_800814A0[0] |= 0x8000;
    }
}
