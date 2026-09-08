#include "common.h"
#include "m2c_compat.h"

s32 func_8025E01C();                          /* extern */

typedef struct S_8080E534_0 {
    u8 pad_00[0xA];
    s16 unk_0A;
    u8 pad_0C[0x8];
    s32 unk_14;
} S_8080E534_0;   /* arg1 in func_8080E534 */

/* Advance the accumulator and reset it when lowering the stored value. */
void func_8080E534(s32 unused, S_8080E534_0 *object) {
    s32 shifted_value;
    s32 new_value;

    shifted_value = func_8025E01C(object) << 0x10;
    object->unk_14 = (s32) (object->unk_14 + 0x1D000);
    new_value = shifted_value >> 0x10;
    if (new_value < object->unk_0A) {
        object->unk_0A = (s16) new_value;
        object->unk_14 = 0;
    }
}

/* MECHANISM: The unused first parameter puts the object pointer in $a1, held in $s0
   across func_8025E01C; this restores both the pre-save move and call-slot a0 copy.
   The seed's 24-byte frame, signed halfword compare, and RMW body were already exact. */
