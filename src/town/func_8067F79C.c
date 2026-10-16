/* Relinked copy of town/func_804712E0 (func_804712E0.c); retail differs only at relocation sites. */
#include "common.h"

extern s32 func_80016A4C(void *entries, s32 value);
extern s32 D_800188C8;
extern s32 D_800188D0[];

/* Stores the result of func_80016A4C for D_800188D0 in D_800188C8. */
void func_8001679C(void) {
    D_800188C8 = func_80016A4C(D_800188D0, 1);
}
