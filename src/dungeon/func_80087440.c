#include "common.h"
#include "m2c_compat.h"

typedef struct S_8008CBA0_0 {
    u8 pad_00[0x28];
    u8 unk_28;
    u8 unk_29;
    u8 pad_2A[0x3A];
    union { u8 u8; u16 u16; } unk_64;   /* accessed as both */
} S_8008CBA0_0;   /* arg3 in func_8008CBA0 */


/* Apply the pending increase, clamp to the limit, and clear the pending value. */
void func_8008CBA0(s32 unused_0, s32 unused_1, s32 unused_2, S_8008CBA0_0 *object) {
    u8 updated_value;
    u8 value_limit;

    updated_value = object->unk_28 + object->unk_64.u8;
    value_limit = object->unk_29;
    object->unk_28 = updated_value;
    if (value_limit < (u32) (updated_value & 0xFF)) {
        object->unk_28 = value_limit;
    }
    object->unk_64.u16 = 0;
}
