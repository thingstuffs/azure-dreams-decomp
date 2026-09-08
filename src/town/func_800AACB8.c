#include "common.h"

extern s32 D_800D0E44;

/* washed_dish_suu_inc: Decrement the washed dish count, clamp it to zero, and return it. */
s32 func_800A8418(void) {
    D_800D0E44--;
    if (D_800D0E44 < 0) {
        D_800D0E44 = 0;
    }
    return D_800D0E44;
}
