#include "common.h"

typedef struct {
    s32 value;
    s32 pad[2];
} D800D0E44;

extern D800D0E44 D_800D0E44;

/* washed_dish_suu_set: Set and return the washed dish count. */
s32 func_800A8408(s32 new_count) {
    s32 dish_count = new_count;

    D_800D0E44.value = dish_count;
    return dish_count;
}
