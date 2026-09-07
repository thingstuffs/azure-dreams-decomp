#include "common.h"

typedef struct {
    s32 value;
    s32 pad[2];
} D800D0E44;

extern D800D0E44 D_800D0E44;

s32 func_800A8408(s32 arg0) {
    s32 value = arg0;

    D_800D0E44.value = value;
    return value;
}
