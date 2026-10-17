#include "common.h"

extern s32 D_80019170;
extern s32 D_80019174;

/* Store the supplied values in D_80019170 and D_80019174. */
void func_8051E8C0(s32 value_18e44, s32 value_18e48) {
    D_80019170 = value_18e44;
    D_80019174 = value_18e48;
}
