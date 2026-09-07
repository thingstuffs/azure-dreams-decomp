#include "common.h"
#include "m2c_compat.h"

s32 func_80033B2C();                         /* extern */
extern M2C_UNK D_800A6EE4;

typedef struct S_800A6EA4_0 {
    u8 pad_00[0x50];
    M2C_UNK * unk_50;
    u8 pad_54[0x3C];
    s16 unk_90;
} S_800A6EA4_0;   /* arg0 in func_800A6EA4 */

void func_800A6EA4(S_800A6EA4_0 *arg0) {
    if (func_80033B2C(0x99) != 0) {
        arg0->unk_90 = 0;
        arg0->unk_50 = &D_800A6EE4;
    }
}
