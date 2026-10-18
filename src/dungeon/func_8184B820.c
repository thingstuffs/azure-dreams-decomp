#include "common.h"

extern s32 draw_concentric_effect_layers(void *, s32, s32);
extern s32 draw_cylindrical(void *, s32, s32);
extern s32 func_80024EF8(void *, s32, s32);

/* Dispatch effect rendering by effect type. */
s32 dispatch_effect_rendering(void *effect, s32 position, s32 render_param)
{
    s32 dispatch_index;

    dispatch_index = *(s16 *)((u8 *)effect + 0xA);
    switch (dispatch_index) {
    case 3:
        draw_concentric_effect_layers(effect, position, render_param);
        return 0;
    case 4:
        draw_cylindrical(effect, position, render_param);
        return 0;
    case 5:
        func_80024EF8(effect, position, render_param);
        return 0;
    case 6:
    case 2:
    case 1:
    case 0:
    default:
        return 0;
    }
}
