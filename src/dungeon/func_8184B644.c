#include "common.h"

extern s32 func_80024930();

/* Draw two cylindrical effect layers with opposing rotation. */
s32 func_80024E44(void *effect, s32 position, s32 render_param) {
    s32 height = 0x140;
    u16 phase;

    phase = *(u16 *)((u8 *)effect + 0x14);
    func_80024930(effect, position, render_param, (s16)(phase << 5), height, 0x20, 3, 0x40);

    phase = *(u16 *)((u8 *)effect + 0x14);
    func_80024930(effect, position, render_param, (s16)-(phase << 6), height, 0x18, 1, 0xFF);

    return 0;
}
