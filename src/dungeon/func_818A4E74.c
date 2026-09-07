#include "common.h"

#define FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern s32 rand(void);

void func_818A4E74(void **arg0, s32 arg1, void *arg2) {
    s32 value;
    s32 quotient;
    void *object;

    object = *arg0;
    FIELD(object, u16 *, 0x14) = (u16)(FIELD(object, u16 *, 0x14) + 1);
    value = rand();
    quotient = value / 0x1000;
    FIELD(arg2, s16 *, 0x1A) = (s16)(value - (quotient << 12));
}
