#include "common.h"
#include "dungeon/effect/motion.h"
#include "shared/dungeon_effect_state.h"


/*
 * Dispatches effect type 3 to concentric layers, 4 to draw_static_cylinder_pair, and 5 to func_80024EF8;
 * other types draw nothing, and all paths return zero.
 */
s32 dispatch_effect_rendering(B22_81893474_EffectState *effect, s32 position, s32 render_param)
{
    s32 dispatch_index;

    dispatch_index = effect->state.s;
    switch (dispatch_index) {
    case 3:
        draw_concentric_effect_layers(effect, position, render_param);
        return 0;
    case 4:
        draw_static_cylinder_pair(effect, position, render_param);
        return 0;
    case 5:
        draw_counter_rotating_cylinders(effect, position, render_param);
        return 0;
    case 6:
    case 2:
    case 1:
    case 0:
    default:
        return 0;
    }
}
