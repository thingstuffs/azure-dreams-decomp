#include "common.h"
#include "dungeon/effect/motion.h"

extern s32 func_80024EF8(void *, s32, s32);

/*
 * Dispatches effect type 3 to concentric layers, 4 to draw_cylindrical, and 5 to func_80024EF8;
 * other types draw nothing, and all paths return zero.
 */
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
