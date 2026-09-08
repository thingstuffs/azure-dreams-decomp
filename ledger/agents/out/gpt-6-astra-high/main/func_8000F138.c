#include "common.h"

extern s32 D_800287CC;
extern u8 D_80084120;

/* Returns the first or second word according to D_800287CC. */
s32 func_80022138(void) {
    s32 *selected_word;

    selected_word = &D_80084120;
    if (D_800287CC != 0) {
        selected_word = &D_80084120 + 4;
    }
    return *selected_word;
}
