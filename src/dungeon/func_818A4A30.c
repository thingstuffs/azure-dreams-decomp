#include "common.h"

s32 func_800478B8();

/* Increment the object counter and pass the low 32 bits of the value to the helper. */
void func_818A4A30(void **object_ref, long long value) {
    void *object;
    u16 *counter;
    u32 low_value;

    object = *object_ref;
    counter = (u16 *)((s8 *)object + 0x14);
    low_value = value;
    *counter = (u16)(*counter + 1);
    func_800478B8(low_value);
}
