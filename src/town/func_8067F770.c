/* Relinked copy of town/func_804712B4 (func_804712B4.c); retail differs only at relocation sites. */
#include "common.h"

extern s32 func_80016A4C(void *, s32);
extern s32 D_800188C8;
extern s32 D_800188D0[];

/* Store the result of calling func_80016A4C with D_800188D0 and zero. */
void func_80016770(void) {
    D_800188C8 = func_80016A4C(D_800188D0, 0);
}
