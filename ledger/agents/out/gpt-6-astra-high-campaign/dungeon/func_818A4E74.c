#include "common.h"

#define FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern s32 rand(void);

/* Increment the object counter and store a random remainder modulo 4096 in the target. */
void func_818A4E74(void **object_ref, s32 unused, void *target) {
    s32 random_value;
    s32 random_quotient;
    void *object;

    object = *object_ref;
    FIELD(object, u16 *, 0x14) = (u16)(FIELD(object, u16 *, 0x14) + 1);
    random_value = rand();
    random_quotient = random_value / 0x1000;
    FIELD(target, s16 *, 0x1A) = (s16)(random_value - (random_quotient << 12));
}
