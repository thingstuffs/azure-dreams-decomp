#include "common.h"

typedef struct S_func_818A4E74_0 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_func_818A4E74_0;

typedef struct S_func_818A4E74_1 {
    u8 pad_00[0x1A];
    s16 unk_1A;
} S_func_818A4E74_1;

extern s32 rand(void);

/* Increment the object counter and store a random remainder modulo 4096 in the target. */
void func_818A4E74(void **object_ref, s32 unused, S_func_818A4E74_1 *target) {
    s32 random_value;
    s32 random_quotient;
    S_func_818A4E74_0 *object;

    object = *object_ref;
    object->unk_14 = (u16)(object->unk_14 + 1);
    random_value = rand();
    random_quotient = random_value / 0x1000;
    target->unk_1A = (s16)(random_value - (random_quotient << 12));
}
