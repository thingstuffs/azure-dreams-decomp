#include "common.h"

typedef struct {
    s32 value;
    s32 pad[2];
} D800D0E44;

extern D800D0E44 D_800D0E44;

/* Stores and returns the supplied value. */
s32 func_800A8408(s32 new_value) {
    s32 value = new_value;

    D_800D0E44.value = value;
    return value;
}
