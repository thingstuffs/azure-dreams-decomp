#include "common.h"

extern s32 D_801781D8;
extern s32 D_801781DC;

/* Stores two signed values in the movie state globals. */
void func_8004033C(s16 value_d8, s16 value_dc) {
    D_801781D8 = (s32) value_d8;
    D_801781DC = (s32) value_dc;
}
