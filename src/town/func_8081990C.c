#include "common.h"

/* Increment the object's 16-bit field at offset 0x18 by 0x20. */
void func_8002390C(s32 unused_0, s32 unused_1, u8 *object) {
    *(u16 *)(object + 0x18) += 0x20;
}
