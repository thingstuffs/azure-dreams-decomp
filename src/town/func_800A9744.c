#include "common.h"
#include "m2c_compat.h"

s32 testResidentBitmapBit();                         /* extern */
extern M2C_UNK D_800A6EE4;

typedef struct S_800A6EA4_0 {
    u8 pad_00[0x50];
    M2C_UNK * unk_50;
    u8 pad_54[0x3C];
    s16 unk_90;
} S_800A6EA4_0;   /* arg0 in townResetCounterAfterCheck99 */

/* Reset the object counter and select its next state when check 0x99 succeeds. */
void townResetCounterAfterCheck99(S_800A6EA4_0 *object) {
    if (testResidentBitmapBit(0x99) != 0) {
        object->unk_90 = 0;
        object->unk_50 = &D_800A6EE4;
    }
}
