#include "common.h"

extern s32 func_800644B8(s32);
extern void func_80024930(void *, s32, s32, s32, s32, s32, s32, s32);

/* Draw two concentric effect layers with phase-scaled height and radii. */
s32 func_80024CFC(void *effect, s32 position, s32 render_param) {
    s32 inner_radius;
    s32 outer_radius;
    s32 height;
    s32 outer_brightness;

    outer_brightness = *(u8 *)((u8 *)effect + 0x10) * 0x10;
    if (outer_brightness & 0xFF) {
        outer_brightness = 0xFF;
    }
    height = ((func_800644B8(*(s16 *)((u8 *)effect + 0x10) << 6) >> 4) * 0x140) >> 8;
    inner_radius = (func_800644B8(*(s16 *)((u8 *)effect + 0x10) << 6) * 2) >> 8;
    outer_radius = ((func_800644B8(*(s16 *)((u8 *)effect + 0x10) << 6) >> 4) * 0x18) >> 8;
    func_80024930(effect, position, render_param, (s16)(*(u16 *)((u8 *)effect + 0x14) << 5), (s16)height,
                  (s16)inner_radius, 3, 0x40);
    func_80024930(effect, position, render_param, (s16)((-( *(u16 *)((u8 *)effect + 0x14) << 0x16)) >> 0x10),
                  (s16)height, (s16)outer_radius, 1, outer_brightness & 0xFF);
    return 0;
}
