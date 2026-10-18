/* Relinked copy of town/func_804712B4 (func_804712B4.c); retail differs only at relocation sites. */
#include "common.h"

extern s32 run_operation(void *, s32);
extern s32 D_800188C8;
extern s32 D_800188D0[];

/* Store the result of calling run_operation with D_800188D0 and zero. */
void store_calling_zero(void) {
    D_800188C8 = run_operation(D_800188D0, 0);
}
