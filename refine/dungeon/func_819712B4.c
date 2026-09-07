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

/* Advance a timed effect, update its intensity and motion, and flag completion. */
void func_819712B4(Obj *effect, Motion *motion, s8 *render_data)
{
    s32 intensity;
    u16 phase;

    D_80025FF4 = 1;
    effect->timer--;
    phase = effect->phase + 1;
    effect->phase = phase;
    if ((s16)phase == 2) {
        effect->phase = 0;
        func_800478B8(render_data);
    }
    intensity = (effect->timer << 7) / effect->divisor;
    render_data[14] = intensity;
    render_data[13] = intensity;
    render_data[12] = intensity;
    motion->value += motion->delta;
    if (effect->timer <= 0) {
        ((u16 *)effect)[-1] |= 0x8000;
        D_800814A0[0] |= 0x8000;
    }
}
