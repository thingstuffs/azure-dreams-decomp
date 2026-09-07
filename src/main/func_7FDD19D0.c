#include "common.h"
#include "m2c_compat.h"

s32 func_7004EE30();                          /* extern */
extern M2C_UNK D_800888D0;

typedef struct S_7FDD19D0_0 {
    u8 pad_00[0x10];
    M2C_UNK * unk_10;
} S_7FDD19D0_0;   /* temp_s0 in func_7FDD19D0 */

void func_7FDD19D0(s32 arg0) {
    S_7FDD19D0_0 *temp_s0;

    temp_s0 = arg0 - 0x20;
    if (func_7004EE30(temp_s0) != 0) {
        temp_s0->unk_10 = &D_800888D0;
    }
}
