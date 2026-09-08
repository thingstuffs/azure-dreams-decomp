#include "common.h"

extern s32 D_80018E44;
extern s32 D_80018E48;

/* Store the supplied values in D_80018E44 and D_80018E48. */
void func_804B791C(s32 value_18e44, s32 value_18e48) {
    D_80018E44 = value_18e44;
    D_80018E48 = value_18e48;
}
