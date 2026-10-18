#include "common.h"
#include "m2c_compat.h"

s32 test_resident_bitmap_bit();                         /* extern */
extern M2C_UNK D_800A6EE4;

typedef struct S_800A6EA4_0 {
    u8 pad_00[0x50];
    M2C_UNK * unk_50;
    u8 pad_54[0x3C];
    s16 unk_90;
} S_800A6EA4_0;   /* arg0 in reset_counter_after_check_99 */

/* Reset the object counter and select its next state when check 0x99 succeeds. */
void reset_counter_after_check_99(S_800A6EA4_0 *object) {
    if (test_resident_bitmap_bit(0x99) != 0) {
        object->unk_90 = 0;
        object->unk_50 = &D_800A6EE4;
    }
}
