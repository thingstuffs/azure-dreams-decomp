#include "common.h"


/* Clear object fields and set its state to 0x2D when mode is zero, otherwise 0x2C. */
void func_8008D344(s8 *object, s32 unused_1, s32 unused_2, s32 mode) {
    s32 state;

    state = 0x2C;
    object[0x9A] = state;
    object[0x9B] = 0;
    *(s32 *)(object + 0x8C) = 0;
    if (mode == 0) {
        ASM_KEEP(state);
        state++;
        object[0x9A] = state;
    }
}
