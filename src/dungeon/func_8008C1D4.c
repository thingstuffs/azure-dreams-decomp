#include "common.h"

#define FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

/* Sets object state bytes from the mode and clears its state word. */
void func_80091934(void *object, s32 unused_1, s32 unused_2, s32 mode) {
    FIELD(object, s8 *, 0x9A) = 0x2B;
    if (mode == 0) {
        FIELD(object, s8 *, 0x9B) = 0x10;
    } else {
        FIELD(object, s8 *, 0x9B) = 0;
    }
    FIELD(object, s32 *, 0x8C) = 0;
    return;
}
