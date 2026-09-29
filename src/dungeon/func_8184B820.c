#include "common.h"

extern s32 func_80024CFC(void *, s32, s32);
extern s32 func_80024E44(void *, s32, s32);
extern s32 func_80024EF8(void *, s32, s32);

/* Dispatch effect rendering by effect type. */
s32 func_80025020(void *effect, s32 position, s32 render_param)
{
    s32 dispatch_index;

    dispatch_index = *(s16 *)((u8 *)effect + 0xA);
    switch (dispatch_index) {
    case 0:
        func_80024CFC(effect, position, render_param);
        return 0;
    case 1:
        func_80024E44(effect, position, render_param);
        return 0;
    case 2:
        func_80024EF8(effect, position, render_param);
        return 0;
    case 3:
    case 4:
    case 5:
    case 6:
    default:
        return 0;
    }
}
