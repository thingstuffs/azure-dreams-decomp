#include "common.h"

extern s32 D_80100E18[3];

/* Stores the value in the first element of D_80100E18. */
void func_800A488C(s32 value) {
    *D_80100E18 = value;
}
